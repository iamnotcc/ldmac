/*
 * AlohaHostMac.cc
 *
 *  Created on: 2016��6��1��
 *      Author: Administrator
 */


#include "AlohaHostMac.h"
#include "mobility/base/MovingMobilityBase.h"

namespace inet
{
//Define_Module(AlohaHostMac);
//
//AlohaHostMac::AlohaHostMac()
//{
//    m_msgEndTxEvent=nullptr;
//    m_msgPkArrival=nullptr;
//}
//
//AlohaHostMac::~AlohaHostMac()
//{
//
//    cancelAndDelete(m_msgEndTxEvent);
//    cancelAndDelete(m_msgPkArrival);
//}
////��������ʼ��
//void AlohaHostMac::initialize()
//{
//    //��ȡapģ��ָ��
//    m_mdAp=getModuleByPath("ap");
//    EV<<"ap's name: "<<m_mdAp->getName()<<endl;
//
//    if(!m_mdAp)
//    {
//        throw cRuntimeError("AP not found");
//    }
//
//    //��ini��ȡ����
//    m_dTxRate=par("txRate");
//    m_stSlotTime=par("slotTime");
//    m_bIsSlotted=m_stSlotTime>0;
//    m_bIsIDLE=true;
//
//    m_msgEndTxEvent=new cMessage("selfMessage---host end transmit");
//
//    m_msgPkArrival=new cMessage("selfMessage---app packet arrive");
//
//    m_msgSelf=new cMessage("selfMessage");
//    scheduleAt(0,m_msgSelf);
//
//    //ע���ź���
//    //�Ŷӵȴ�ʱ��
//    m_ssQueueTime=registerSignal("queueTime");
//    m_stQueueTime=0;
//    //�����������ݰ�����
//    m_ssDiscardPkCount=registerSignal("discardPkCount");
//    //�ܹ����͵����ݰ�����
//    m_ssSendPkCount=registerSignal("sendPkCount");
//
//    m_ssTime0=registerSignal("time0");
//    m_ssTime1=registerSignal("time1");
//    m_ssTime2=registerSignal("time2");
//    m_ssTime3=registerSignal("time3");
//    m_ssTime4=registerSignal("time4");
//    m_ssTime5=registerSignal("time5");
//    m_ssTime6=registerSignal("time6");
//    m_ssTime7=registerSignal("time7");
//    m_ssTime8=registerSignal("time8");
//    m_ssTime9=registerSignal("time9");
//    m_ssTime10=registerSignal("time10");
//
//}
//
////���������������Ϣ
//void AlohaHostMac::handleMessage(cMessage *msg)
//{
//    //����յ�m_msgPkArrival����˵�����µ����ݰ�������ѷ���
//    if(msg==m_msgPkArrival)
//    {
//        EV_DEBUG<<getFullPath()<<" received message: "<<msg->getName()<<endl;
//        //������ڿ��У�����Է���
//        if(m_bIsIDLE)
//        {
//            m_bIsIDLE=false;
//
//            cPacket *pk=check_and_cast<cPacket *>(m_qPacketQueue.pop());
//            pk->setKind(PacketKind_Host_Data);
//            //���þ����־
//            pk->setSrcProcId(setDistanceFlag());
//            //�����Ŷ��ӳ�
//            m_stQueueTime=simTime()-pk->getArrivalTime();
//            //�����źţ����͵İ������Լ��Ŷ��ӳ�
//            emit(m_ssQueueTime,m_stQueueTime);
//            emit(m_ssSendPkCount,1l);
//            double dDistance=getDistance();
//            simtime_t stRadioDelay=dDistance/SPEED_OF_LIGHT;
//            simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//            pk->setDuration(stDuration);
//
//            sendDirect(pk,stRadioDelay,stDuration,m_mdAp->gate("in"));
//
//            scheduleAt(simTime()+stDuration,m_msgEndTxEvent);
//        }
//    }
//    else
//    {
//        if(msg==m_msgEndTxEvent)
//        {
//            EV_DEBUG<<getFullPath()<<" received message: "<<msg->getName()<<endl;
//
//            m_bIsIDLE=true;
//
//            if(!m_qPacketQueue.isEmpty())
//            {
//                m_bIsIDLE=false;
//
//                cPacket *pk=check_and_cast<cPacket *>(m_qPacketQueue.pop());
//                pk->setKind(PacketKind_Host_Data);
//                //���þ����־
//                pk->setSrcProcId(setDistanceFlag());
//                //�����Ŷ��ӳ�
//                m_stQueueTime=simTime()-pk->getArrivalTime();
//                //�����źţ����͵İ������Լ��Ŷ��ӳ�
//                emit(m_ssQueueTime,m_stQueueTime);
//                emit(m_ssSendPkCount,1l);
//                double dDistance=getDistance();
//                simtime_t stRadioDelay=dDistance/SPEED_OF_LIGHT;
//                simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//                pk->setDuration(stDuration);
//
//                sendDirect(pk,stRadioDelay,stDuration,m_mdAp->gate("in"));
//
//                scheduleAt(simTime()+stDuration,m_msgEndTxEvent);
//            }
//        }
//        else
//        {
//            if(msg->getKind()==PacketKind_Application)
//            {
//                if(m_qPacketQueue.getLength()==QUEUE_CAPACITY)
//                {
//                    emit(m_ssDiscardPkCount,1l);
//                    delete msg;
//                    EV<<"Queue is full, new message is deleted."<<endl;
//                }
//                else
//                {
//                    EV_DEBUG<<getFullPath()<<" received message: "<<msg->getName()<<endl;
//                    msg->setArrivalTime(simTime());
//                    if(m_qPacketQueue.isEmpty())
//                    {
//                        scheduleAt(getTransmissionTime(simTime()),m_msgPkArrival);
//                    }
//                    m_qPacketQueue.insert(msg);
//                }
//            }
//            else
//            {
//                if(msg==m_msgSelf)
//                {
//                    m_stTime=1;
////                    if(m_bIsSlotted)
////                    {
////                        m_stTime=m_stSlotTime;
////                    }
////                    else
////                    {
////                        m_stTime=1;
////                    }
//                    scheduleAt(simTime()+m_stTime,m_msgSelf);
//                    emit(m_ssTime0,m_stTime);
//                    switch(setDistanceFlag())
//                    {
//                        case 1:
//                        {
//                            emit(m_ssTime1,m_stTime);
//                            break;
//                        }
//                        case 2:
//                        {
//                            emit(m_ssTime2,m_stTime);
//                            break;
//                        }
//                        case 3:
//                        {
//                            emit(m_ssTime3,m_stTime);
//                            break;
//                        }
//                        case 4:
//                        {
//                            emit(m_ssTime4,m_stTime);
//                            break;
//                        }
//                        case 5:
//                        {
//                            emit(m_ssTime5,m_stTime);
//                            break;
//                        }
//                        case 6:
//                        {
//                            emit(m_ssTime6,m_stTime);
//                            break;
//                        }
//                        case 7:
//                        {
//                            emit(m_ssTime7,m_stTime);
//                            break;
//                        }
//                        case 8:
//                        {
//                            emit(m_ssTime8,m_stTime);
//                            break;
//                        }
//                        case 9:
//                        {
//                            emit(m_ssTime9,m_stTime);
//                            break;
//                        }
//                        case 10:
//                        {
//                            emit(m_ssTime10,m_stTime);
//                            break;
//                        }
//                    }
//                }
//                else
//                {
//                    throw cRuntimeError("Error msg type");
//                }
//
//            }
//        }
//    }
//}
//
//simtime_t AlohaHostMac::getTransmissionTime(simtime_t t)
//{
//    if (!m_bIsSlotted)
//    {
//       return t;
//    }
//    else
//    {
//        return m_stSlotTime * ceil(t/m_stSlotTime);
//    }
//}
//
//Coord AlohaHostMac::getCurrentPosition()
//{
//    cModule *mdParent= getParentModule();
//    cModule *mdMobility=mdParent->getSubmodule("mobility");
//    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
//    return mdMovingMobility->getCurrentPosition();
//}
//
//Coord AlohaHostMac::getApPosition()
//{
//    cModule *mdMobility=m_mdAp->getSubmodule("mobility");
//    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
//    return mdMovingMobility->getCurrentPosition();
//}
//
//double AlohaHostMac::getDistance()
//{
//    Coord cdHost=getCurrentPosition();
//    Coord cdAp=getApPosition();
//    Coord cdDistance=cdHost-cdAp;
//    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
//}
//int AlohaHostMac::setDistanceFlag()
//{
//    double dDistance=getDistance();
//    int nReturn= ceil(10*dDistance/COMMUNICATION_RANGE);
//    if(nReturn <=0)
//    {
//        nReturn =1;
//    }
//    if(nReturn>10)
//    {
//        nReturn=10;
//    }
//    return nReturn;
//}
}

