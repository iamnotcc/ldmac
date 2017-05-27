/*
 * TdmaHostMac.cc
 *
 *  Created on: 2017年3月8日
 *      Author: wh
 */
/*
#include "TdmaHostMac.h"
#include "common/PacketKind.h"

namespace inet
{
Define_Module(TdmaHostMac);

TdmaHostMac::TdmaHostMac()
{
    m_msgSelfData=nullptr;
    m_msgSelfReq=nullptr;
}

TdmaHostMac::~TdmaHostMac()
{
    cancelAndDelete(m_msgSelfData);
    cancelAndDelete(m_msgSelfReq);
}

void TdmaHostMac::initialize()
{
    //寻找ap模块
    m_mdAp=getModuleByPath("ap");
    if(!m_mdAp)
    {
        throw cRuntimeError(" Tdma Ap not found");
    }
    else
    {
        EV<<"Tdma found ap:"<<m_mdAp->getFullPath()<<endl;
    }

    //随机数，决定时候丢包
    m_dRandom=dblrand();
    EV<<"m_dRandom="<<m_dRandom<<endl;

    //获取参数值
    m_dTxRate=par("txRate");
    m_nSlotNum=par("slotNum");
    m_stSlotLength=par("slotLength");

    m_nReqLength=&par("reqPktLength");

    //设置队列名称
    m_qAppQueue.setName("AppDataQueue");
    m_qReTransmitQueue.setName("ReTransmitQueue");

    //初始化自消息
    //m_msgSelfReq：发给自己，通知该发送req消息了
    m_msgSelfReq=new cMessage("SelfReqMsg");
    scheduleAt(0,m_msgSelfReq);

    //m_msgSelfData：发给自己，通知该发送data数据了
    m_msgSelfData=new cMessage("SelfDataMsg");

    //ap分配给host的时隙信息,开始时隙编号以及时隙个数
    m_nTransmitSlotIndex=-1;
    m_nTransmitSlotNum=-1;

    //注册信号量
    //排队等待时间
    m_ssQueueTime=registerSignal("queueTime");
    m_stQueueTime=0;
    //被丢弃的数据包个数
    m_ssDiscardPkCount=registerSignal("discardPkCount");
    //总共发送的数据包个数
    m_ssSendPkCount=registerSignal("sendPkCount");

    m_ssTime0=registerSignal("time0");
    m_ssTime1=registerSignal("time1");
    m_ssTime2=registerSignal("time2");
    m_ssTime3=registerSignal("time3");
    m_ssTime4=registerSignal("time4");
    m_ssTime5=registerSignal("time5");
    m_ssTime6=registerSignal("time6");
    m_ssTime7=registerSignal("time7");
    m_ssTime8=registerSignal("time8");
    m_ssTime9=registerSignal("time9");
    m_ssTime10=registerSignal("time10");
}

//host处理消息
void TdmaHostMac::handleMessage(cMessage *msg)
{
    //总共4种消息类型：
    //两个自消息：m_msgSelfReq，提醒发送req; m_msgSelfData：用于提醒发送data
    //来自应用层的消息：PacketKind_Application
    //来自AP的消息：PacketKind_Ap_Allocation
    if(msg->isSelfMessage())
    {
        //如果是提醒发送req
        if(msg==m_msgSelfReq)
        {
            m_stTime=m_stSlotLength*m_nSlotNum;
            emit(m_ssTime0,m_stTime);
            switch(setDistanceFlag())
            {
                case 1:
                {
                    emit(m_ssTime1,m_stTime);
                    break;
                }
                case 2:
                {
                    emit(m_ssTime2,m_stTime);
                    break;
                }
                case 3:
                {
                    emit(m_ssTime3,m_stTime);
                    break;
                }
                case 4:
                {
                    emit(m_ssTime4,m_stTime);
                    break;
                }
                case 5:
                {
                    emit(m_ssTime5,m_stTime);
                    break;
                }
                case 6:
                {
                    emit(m_ssTime6,m_stTime);
                    break;
                }
                case 7:
                {
                    emit(m_ssTime7,m_stTime);
                    break;
                }
                case 8:
                {
                    emit(m_ssTime8,m_stTime);
                    break;
                }
                case 9:
                {
                    emit(m_ssTime9,m_stTime);
                    break;
                }
                case 10:
                {
                    emit(m_ssTime10,m_stTime);
                    break;
                }
            }
            //过一帧时间再提醒
            scheduleAt(simTime()+m_stSlotLength*m_nSlotNum,m_msgSelfReq);

            //发送req包
            sendReqPacket();
        }
        else
        {
            //提醒发送数据
            if(msg==m_msgSelfData)
            {
                sendDataPacket();
            }
            else
            {
                throw cRuntimeError("Error message type");
            }
        }
    }
    else
    {
        switch(msg->getKind())
        {
            //如果是来自应用层的数据包
            case PacketKind_Application :
            {
                if(m_qAppQueue.getLength()==QUEUE_CAPACITY)
                {
                    emit(m_ssDiscardPkCount,1l);
                    delete msg;
                    EV<<"Queue is full, new message is deleted."<<endl;
                }
                else
                {
                    msg->setArrivalTime(simTime());
                    m_qAppQueue.insert(msg);
                    EV<<"AppQueue length is "<<m_qAppQueue.getLength()<<endl;
                }
                break;
            }
            //如果是来自AP的分配信息
            case PacketKind_Ap_Allocation :
            {
                //处理来自ap的数据包
                ApAllocationPkOfTDMA *pk=dynamic_cast<ApAllocationPkOfTDMA *>(msg);
                getApAllocation(pk);
                delete pk;
                scheduleAt(simTime()+m_stSlotLength*m_nTransmitSlotIndex,m_msgSelfData);
                break;
            }

            default:
            {
                throw cRuntimeError("Error message type");
                break;
            }
        }
    }
}

//发送数据
void TdmaHostMac::sendDataPacket()
{
    //浪费的时隙数为传播延迟导致的时间
    m_nWasteSlotNum=getPropagationSlot();

    //设置一个临时队列，保存这个发送丢失的数据包
    cQueue qTmep;

    //一帧内可以发送m_nTransmitSlotNum-m_nWasteSlotNum个数据包
    for(int i=0;i<m_nTransmitSlotNum-m_nWasteSlotNum;i++)
    {
        //首先判断是否有重传的数据包
        //如果有重传的数据包
        if(!m_qReTransmitQueue.isEmpty())
        {
            //取出数据包
            cPacket *pk=dynamic_cast<cPacket *>(m_qReTransmitQueue.pop());
            //设置传输时间和传输延迟
            simtime_t stDuration=pk->getBitLength()/m_dTxRate;
            simtime_t stPropagation=getDistance()/SPEED_OF_LIGHT;

            //计算排队延迟
            m_stQueueTime=simTime()-pk->getArrivalTime();
            //统计信息
            //排队延迟
            emit(m_ssQueueTime,m_stQueueTime);
            //成功发送的个数
            emit(m_ssSendPkCount,1l);
            //pk设置所在区域
            pk->setSrcProcId(setDistanceFlag());

            sendDirect(pk,stPropagation,stDuration,m_mdAp->gate("in"));
        }
        //没有重传的数据包
        else
        {
            //如果数据队列不为空
            if(!m_qAppQueue.isEmpty())
            {
                //取出一个数据
                cPacket *pk=dynamic_cast<cPacket *>(m_qAppQueue.pop());
                pk->setKind(PacketKind_Host_Data);


                //设置是否会丢失
                m_dRandom=dblrand();
                EV<<"random value----m_dRandom="<<m_dRandom<<endl;
                if(m_dRandom> PACKET_LOSS_RATE)//成功发送
                {
                    EV<<"Host data send successfully."<<endl;
                    simtime_t stDuration=pk->getBitLength()/m_dTxRate;
                    simtime_t stPropagation=getDistance()/SPEED_OF_LIGHT;
                    pk->setSrcProcId(setDistanceFlag());
                    m_stQueueTime=simTime()-pk->getArrivalTime();
                    emit(m_ssQueueTime,m_stQueueTime);
                    emit(m_ssSendPkCount,1l);

                    EV_DEBUG<<i<<" of "<<(m_nTransmitSlotNum-m_nWasteSlotNum) <<" is sending..., detailed parameters:"<<endl;
                    EV_DEBUG<<"packet kind:"<<pk->getKind()<<endl;
                    EV_DEBUG<<"duration:"<<stDuration <<endl;
                    EV_DEBUG<<"propagation:"<<stPropagation <<endl;

                    sendDirect(pk,stPropagation,stDuration,m_mdAp->gate("in"));
                }
                else
                {
                    EV<<"Host data is lost, and will retransmit."<<endl;
                    qTmep.insert(pk);
                }
            }
            else
            {
                EV_DEBUG<<"m_qAppQueue is empty, no data packet is sending."<<endl;
            }
        }
    }
    for(int i=0;i<qTmep.getLength();i++)
    {
        m_qReTransmitQueue.insert(qTmep.pop());
    }
}

//发送req,告诉host的存在，不管有没有数据，ap都会给host分配时隙。固定分配
void TdmaHostMac::sendReqPacket()
{
    //新建一个数据包req
    HostReqPkOfTDMA *pk=new HostReqPkOfTDMA();
    pk->setKind(PacketKind_Host_Request);

    //获取父节点host指针
    cModule *mdParent=getParentModule();
    //设置host的id
    int nParentId=mdParent->getId();
    pk->setNHostId(nParentId);
    //设置host的路径
    pk->setStrHostPath(mdParent->getFullPath().c_str());
    //设置节点的位置坐标
    Coord cdPostition=getCurrentPosition();
    pk->setCdHostPosition(cdPostition);

    simtime_t stDuration=m_nReqLength->longValue()/m_dTxRate;
    simtime_t stPropagation=getDistance()/SPEED_OF_LIGHT;

    EV_DEBUG<<"Request packet of "<< mdParent->getFullPath()<<" is sending..., detailed parameters:"<<endl;
    EV_DEBUG<<"packet kind:"<<pk->getKind() <<endl;
    EV_DEBUG<<"host id:"<<pk->getNHostId() <<endl;
    EV_DEBUG<<"host path:"<< pk->getStrHostPath()<<endl;
    EV_DEBUG<<"host position:"<<pk->getCdHostPosition() <<endl;
    EV_DEBUG<<"duration:"<< stDuration<<endl;
    EV_DEBUG<<"propagation:"<< stPropagation<<endl;

    sendDirect(pk,stPropagation,stDuration,m_mdAp->gate("in"));

}

//获取来自ap的分配信息
void TdmaHostMac::getApAllocation(ApAllocationPkOfTDMA *pk)
{
    m_nTransmitSlotIndex=pk->getNIndex();
    m_nTransmitSlotNum=pk->getNSlotNum();

    EV_DEBUG<<"Host gets allocation infomation from Ap:"<<endl;
    EV_DEBUG<<"slot index:"<< m_nTransmitSlotIndex<<endl;
    EV_DEBUG<<"slot num:"<< m_nTransmitSlotNum<<endl;

    return;
}

//基础函数
//获取当前位置
Coord TdmaHostMac::getCurrentPosition()
{
    cModule *mdParent=getParentModule();
    cModule *mdMobility=mdParent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    return mdMovingMobility->getCurrentPosition();
}
//获取AP位置
Coord TdmaHostMac::getApPosition()
{
    cModule *mdMobilityOfAp=m_mdAp->getSubmodule("mobility");
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
    return ceil(stPropagationTime/m_stSlotLength);

}
//设置距离标志，根据距离远近来设置1~10
int TdmaHostMac::setDistanceFlag()
{
    double dDistance=getDistance();
    int nReturn= ceil(10*dDistance/COMMUNICATION_RANGE);
    if(nReturn <=0)
    {
        nReturn =1;
    }
    if(nReturn>10)
    {
        nReturn=10;
    }
    return nReturn;
}

}

*/


