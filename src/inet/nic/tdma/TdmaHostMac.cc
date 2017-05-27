/*
 * TdmaHostMac.cc
 *
 *  Created on: 2017年3月15日
 *      Author: wh
 */

#include "inet/nic/tdma/TdmaHostMac.h"
#include "inet/nic/common/NicCommon.h"
#include "inet/common/PacketKind.h"

namespace inet
{
Define_Module(TdmaHostMac);

TdmaHostMac::TdmaHostMac()
{
    m_selfMsgReq=nullptr;
    m_selfMsgData=nullptr;
}

TdmaHostMac::~TdmaHostMac()
{
    cancelAndDelete(m_selfMsgReq);
    cancelAndDelete(m_selfMsgData);
}

void TdmaHostMac::initialize()
{
    //发现ap模块
    m_ap=getModuleByPath("ap");
    if(!m_ap)
    {
        throw cRuntimeError("TDMA: ap not found");
    }
    else
    {
        EV_DEBUG<<this->getName()<<" found ap: "<<m_ap->getName()<<endl;
    }

    //获取父模块
    m_parent=getParentModule();
    if(!m_parent)
    {
        throw cRuntimeError("TDMA: parent module not found");
    }

    //参数初始化
    m_txRate=par("txRate");;
    m_communicationRange=par("communicationRange");
    m_slotLength=par("slotLength");
    m_slotNum=par("slotNum");
    m_reqSlotNum=par("reqSlotNum");

    //注册信号量
    //排队等待时间
    m_ssQueueTime=registerSignal("queueTime");
    m_queuetime=0;
    //被丢弃的数据包个数
    m_ssDiscardPkCount=registerSignal("discardPkCount");
    //总共发送的数据包个数
    m_ssSentPkCount=registerSignal("sentPkCount");

    //自消息初始化
    m_selfMsgReq=new cMessage("SlefMsg-Req");
    m_selfMsgData=new cMessage("SlefMsg-Data");
    scheduleAt(0,m_selfMsgReq);
}

void TdmaHostMac::handleMessage(cMessage *msg)
{
    //自消息
    if(msg->isSelfMessage())
    {
        //自消息m_selfMsgReq：发送req，每隔一帧发送
        if(msg==m_selfMsgReq)
        {
            scheduleAt(simTime()+m_slotLength*m_slotNum,m_selfMsgReq);

            //如果还在通信范围内，则发送req
            if(getDistance()<m_communicationRange)
            {
                sendReq();
            }
            //超出通信范围，则
            else
            {
                EV_DEBUG<<"Host is out of ap' communication range."<<endl;
                //清空应用数据包队列
                m_appQueue.clear();
            }

        }
        else
        {
            //data自消息
            if(msg==m_selfMsgData)
            {
                sendData();
            }
            else
            {
                throw cRuntimeError("Error self message.");
            }
        }
    }
    //非自消息
    else
    {
        //来自应用层的消息
        if(msg->getKind()==PacketKind_Application)
        {
            //如果队列已满，则丢弃；没满，则加入队列
            if(m_appQueue.getLength()==QUEUE_CAPACITY)
            {
                emit(m_ssDiscardPkCount,1l);
                delete msg;
                EV_DEBUG<<"TDMA: appQueue is full, new arriving packet is discard."<<endl;
            }
            else
            {
                msg->setArrivalTime(simTime());
                m_appQueue.insert(msg);
                EV_DEBUG<<"TDMA: A new application packet arrived. The length of queue now is "<<m_appQueue.getLength()<<endl;
            }
        }
        else
        {
            if(msg->getKind()==PacketKind_Ap_ACK)
            {
                EV_DEBUG<<m_parent->getFullName()<<" received a packet from "<<msg->getSenderModule()->getFullName()<<endl;
                TdmaAck *pk=dynamic_cast<TdmaAck *>(msg);
                //获取ack的信息
                m_dataSlotIndex=pk->getNIndex();
                m_dataSlotNum=pk->getNSlotNum();
                delete pk;

                //发送data自消息
                m_dataTransmitTime=simTime()+m_slotLength*(m_dataSlotIndex-(m_reqSlotNum-2));
                EV_DEBUG<<m_parent->getFullName()<<" will send data in "<<m_dataSlotIndex<<"th slot("<<m_dataTransmitTime<<"), and number of slots is: "<<m_dataSlotNum<<endl;
                scheduleAt(m_dataTransmitTime,m_selfMsgData);
            }
            else
            {
                throw cRuntimeError("Error msg type.");
            }
        }
    }
}

void TdmaHostMac::sendReq()
{
    EV_DEBUG<<"Host now is sending a req at "<<simTime()<<endl;
    //新建一个req
    TdmaReq *pk=new TdmaReq();
    pk->setKind(PacketKind_Host_Request);
    cModule *mdParent=getParentModule();
    int ParentId=mdParent->getId();
    pk->setNHostId(ParentId);
    pk->setStrHostPath(mdParent->getFullPath().c_str());
    Coord cdPosition=getCurrentPosition();
    pk->setCdHostPosition(cdPosition);
    simtime_t stPropagation=m_slotLength*getPropagationSlot();
    sendDirect(pk,stPropagation,0,m_ap->gate("in"));
}

void TdmaHostMac::sendData()
{
    int nPropagationSlots=getPropagationSlot();
    for(int i=0;i<(m_dataSlotNum-nPropagationSlots);i++)
    {
        //如果队列不为空
        if(!m_appQueue.isEmpty())
        {
            cPacket *pk=dynamic_cast<cPacket *>(m_appQueue.pop());
            pk->setKind(PacketKind_Host_Data);
            m_queuetime=simTime()-pk->getArrivalTime();
            EV_DEBUG<<"Current time is: "<<simTime()<<", pk's arrival time is: "<<pk->getArrivalTime()<<", and the queue time is: "<<m_queuetime<<endl;
            emit(m_ssQueueTime,m_queuetime);
            emit(m_ssSentPkCount,1l);
            sendDirect(pk,m_ap->gate("in"));
        }
        else
        {
            EV_DEBUG<<"m_appQueue is empty, no data packet is to send."<<endl;
        }
    }
}

//基础函数
//获取当前位置
Coord TdmaHostMac::getCurrentPosition()
{
    cModule *mdMobility=m_parent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    return mdMovingMobility->getCurrentPosition();
}
//获取AP位置
Coord TdmaHostMac::getApPosition()
{
    cModule *mdMobilityOfAp=m_ap->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
    return mdMovingMobilityOfAp->getCurrentPosition();
}
//计算和AP的距离
double TdmaHostMac::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdAp=getApPosition();
    Coord cdDistance=cdHost-cdAp;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
}
//根据时隙长度，计算无线电传播所需的时隙数
int TdmaHostMac::getPropagationSlot()
{
    double dDistance=getDistance();
    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_slotLength);
}

}


