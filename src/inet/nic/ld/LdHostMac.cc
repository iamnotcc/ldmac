/*
 * LdHostMac.cc
 *
 *  Created on: 2017��3��23��
 *      Author: wh
 */

#include "nic/ld/LdHostMac.h"
#include "inet/common/PacketKind.h"
#include "inet/nic/common/NicCommon.h"
#include "inet/nic/ld/LdReq_m.h"
#include "inet/nic/ld/LdAck_m.h"

namespace inet
{
Define_Module(LdHostMac);

LdHostMac::LdHostMac()
{
    m_selfMsgReq=nullptr;
    m_selfMsgData=nullptr;
}

LdHostMac::~LdHostMac()
{
    cancelAndDelete(m_selfMsgReq);
    cancelAndDelete(m_selfMsgData);
}

//��������ʼ��
void LdHostMac::initialize()
{
    //����apģ��
    m_ap=getModuleByPath("ap");
    if(!m_ap)
    {
        throw cRuntimeError("LD: ap not found");
    }
    else
    {
        EV_DEBUG<<this->getFullPath()<<" found ap: "<<m_ap->getFullPath()<<endl;
    }

    //���ָ�ģ��
    m_parent=getParentModule();
    if(!m_parent)
    {
        throw cRuntimeError("LD: parent module not found");
    }
    else
    {
        EV_DEBUG<<this->getFullPath()<<" found parent module: "<<m_parent->getFullPath()<<endl;
    }

    //��ini�ļ���ȡ����
    m_txRate=par("txRate");
    m_slotNum=par("slotNum");
    m_reqSlotNum=par("reqSlotNum");
    m_slotLength=par("slotLength");
    m_reqLength=par("reqLength");
    m_communicationRange=par("communicationRange");
    EV_DEBUG<<this->getFullPath()<<" initialize parameters: "<<endl;
    EV_DEBUG<<"m_txRate: "<<m_txRate<<endl;
    EV_DEBUG<<"m_slotNum: "<<m_slotNum<<endl;
    EV_DEBUG<<"m_reqSlotNum: "<<m_reqSlotNum<<endl;
    EV_DEBUG<<"m_slotLength: "<<m_slotLength<<endl;
    EV_DEBUG<<"m_reqLength: "<<m_reqLength<<endl;
    EV_DEBUG<<"m_communicationRange: "<<m_communicationRange<<endl;

    //ע���ź���
    //�Ŷӵȴ�ʱ��
    m_ssQueueTime=registerSignal("queueTime");
    m_queuetime=0;
    //�����������ݰ�����
    m_ssDiscardPkCount=registerSignal("discardPkCount");
    //�ܹ����͵����ݰ�����
    m_ssSentPkCount=registerSignal("sentPkCount");
    m_ssTotalTime=registerSignal("totaltime");
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
    //��ʼ������Ϣ
    m_selfMsgReq=new cMessage("selfMsgReq");
    scheduleAt(0,m_selfMsgReq);
    m_selfMsgData=new cMessage("selfMsgData");
}

void LdHostMac::handleMessage(cMessage *msg)
{
    EV<<"FUNCTION: LdHostMac::handleMessage()"<<endl;
    //����Ϣ
    if(msg->isSelfMessage())
    {
        if(msg==m_selfMsgReq)
        {
            //����Ϣm_selfMsgReq������req��ÿ��һ֡����
            EV_DEBUG<<"Self message arrived: "<<msg->getName()<<", preparing to send a request."<<endl;

            scheduleAt(simTime()+m_slotLength*m_slotNum,m_selfMsgReq);

            //�������ͨ�ŷ�Χ�ڣ�����req
            if(getDistance()<m_communicationRange)
            {
                EV_DEBUG<<"Host is communicating with ap.";
                m_stTime=m_slotLength*m_slotNum;
                emit(m_ssTotalTime,m_stTime);
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
                    default:
                    {
                        throw cRuntimeError("Error location");
                    }
                }
                if(m_isSendReq)
                {
                    EV_DEBUG<<"m_isSendReq="<<m_isSendReq<<", it is ready to send a request."<<endl;

                    sendReq();
                }
                else
                {
                    EV_DEBUG<<"m_isSendReq="<<m_isSendReq<<", it is no need to send a request."<<endl;
                }
            }
            //����ͨ�ŷ�Χ����
            else
            {
                EV_DEBUG<<"Host is out of ap' communication range."<<endl;
                //���Ӧ�����ݰ�����
                m_appQueue.clear();
            }
        }
        else
        {
            if(msg==m_selfMsgData)
            {
                EV_DEBUG<<"Self message arrived: "<<msg->getName()<<", preparing to send data."<<endl;

                sendData();
            }
            else
            {
                throw cRuntimeError("LD: Error self message type.");
            }
        }
    }
    //������Ϣ
    else
    {
        if(msg->getKind()==PacketKind_Application)
        {
            EV_DEBUG<<"Non-self message arrived: "<<msg->getName()<<", it is an application packet."<<endl;
            //�������������������û������������
            if(m_appQueue.getLength()==QUEUE_CAPACITY)
            {
                EV_DEBUG<<"The queue length is: "<<m_appQueue.getLength();
                EV_DEBUG<<"The queue is full, new packet will be dropped."<<endl;
                emit(m_ssDiscardPkCount,1l);
                delete msg;
            }
            else
            {
                msg->setArrivalTime(simTime());
                m_appQueue.insert(msg);
                EV_DEBUG<<"LD: A new application packet arrived and will be inserted into queue. The length of queue now is "<<m_appQueue.getLength()<<endl;
            }
        }
        else
        {
            if(msg->getKind()==PacketKind_Ap_ACK)
            {
                EV_DEBUG<<"Non-self message arrived: "<<msg->getName()<<", it is a packet from ap."<<endl;
                LdAck *pk=dynamic_cast<LdAck *>(msg);
                m_dataSlotIndex=pk->getNIndexSlot();
                m_dataSlotNum=pk->getNSlotNum();
                m_isSendReq=pk->getBIsOver();
                EV_DEBUG<<"The ACK information from ap is:"<<endl;
                EV_DEBUG<<"m_dataSlotIndex: "<<m_dataSlotIndex<<endl;
                EV_DEBUG<<"m_dataSlotNum: "<<m_dataSlotNum<<endl;
                EV_DEBUG<<"m_isSendReq:"<<m_isSendReq<<endl;
                delete pk;

                m_dataTransmitTime=simTime()+m_slotLength*(m_dataSlotIndex+2);
                if(m_dataTransmitTime<simTime())
                {
                    throw cRuntimeError("m_dataTransmitTime-%s,simTime()-%s!",m_dataTransmitTime.str().c_str(),simTime().str().c_str());
                }
                EV_DEBUG<<"***** The time to send data is "<<m_dataTransmitTime<<endl;
                scheduleAt(m_dataTransmitTime,m_selfMsgData);
            }
            else
            {
                throw cRuntimeError("LD: Error message type.");
            }
        }
    }
}

void LdHostMac::sendReq()
{
    EV<<"FUNCTION: LdHostMac::sendReq()"<<endl;

    if(!m_appQueue.isEmpty())
    {
        m_reqCounter++;
        char reqPkName[50];
        sprintf(reqPkName,"%s-req-%d",m_parent->getFullName(),m_reqCounter);
        //����һ���µ�req��
        LdReq *pk=new LdReq(reqPkName);
        pk->setKind(PacketKind_Host_Request);
        pk->setBitLength(m_reqLength);
        pk->setNHostId(m_parent->getId());
        pk->setStrHostPath(m_parent->getFullPath().c_str());
        //������Ҫ�������ʱ϶
        int nQueueSize=m_appQueue.getLength();
        if(nQueueSize>MAX_REQUEST_SLOTS)
        {
            nQueueSize=MAX_REQUEST_SLOTS;
        }
        pk->setNRequestSlotNum(nQueueSize);
        pk->setCdHostPosition(getCurrentPosition());
        int nPropagationSlots=getPropagationSlot();
        pk->setNPropagationSlotNum(nPropagationSlots);
        simtime_t stPropagation=nPropagationSlots*m_slotLength;

        EV_DEBUG<<m_parent->getFullName()<<" send a req packet:"<<endl;
        EV_DEBUG<<"pk name: "<<pk->getName()<<endl;
        EV_DEBUG<<"pk hostId: "<<pk->getNHostId()<<endl;
        EV_DEBUG<<"pk hostPath: "<<pk->getStrHostPath()<<endl;
        EV_DEBUG<<"pk reqSlotNum: "<<pk->getNRequestSlotNum()<<",and queue length is: "<<nQueueSize<<endl;
        EV_DEBUG<<"pk propagationSlotNum: "<<pk->getNPropagationSlotNum()<<endl;

        sendDirect(pk,stPropagation,0,m_ap->gate("in"));

    }
    else
    {
        EV_DEBUG<<"LD: app queue is empty, no req is ready to send."<<endl;
    }

}

void LdHostMac::sendData()
{
    EV<<"FUNCTION: LdHostMac::sendData()"<<endl;
    for(int i=0;i<m_dataSlotNum;i++)
    {
        //������в�Ϊ��
        if(!m_appQueue.isEmpty())
        {
            cPacket *pk=dynamic_cast<cPacket *>(m_appQueue.pop());
            pk->setKind(PacketKind_Host_Data);
            pk->setSrcProcId(setDistanceFlag());
            m_queuetime=simTime()-pk->getArrivalTime();
            EV_DEBUG<<"Current time is: "<<simTime()<<", pk's arrival time is: "<<pk->getArrivalTime()<<", and the queue time is: "<<m_queuetime<<endl;
            emit(m_ssQueueTime,m_queuetime);
            emit(m_ssSentPkCount,1l);
            sendDirect(pk,0,0,m_ap->gate("in"));
        }
        else
        {
            EV_DEBUG<<"m_appQueue is empty, no data packet is to send."<<endl;
        }
    }
}

//��������
//��ȡ��ǰλ��
Coord LdHostMac::getCurrentPosition()
{
    cModule *mdMobility=m_parent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    return mdMovingMobility->getCurrentPosition();
}
//��ȡAPλ��
Coord LdHostMac::getApPosition()
{
    cModule *mdMobilityOfAp=m_ap->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
    return mdMovingMobilityOfAp->getCurrentPosition();
}
//�����AP�ľ���
double LdHostMac::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdAp=getApPosition();
    Coord cdDistance=cdHost-cdAp;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
}
//����ʱ϶���ȣ��������ߵ紫�������ʱ϶��
int LdHostMac::getPropagationSlot()
{
    double dDistance=getDistance();
    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_slotLength);
}

//���þ����־�����ݾ���Զ��������1~10
int LdHostMac::setDistanceFlag()
{
    double dDistance=getDistance();
    int nReturn= ceil(10*dDistance/m_communicationRange);
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



