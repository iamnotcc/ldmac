/*
 * AlohaApMac.cc
 *
 *  Created on: 2016年6月7日
 *      Author: Administrator
 */

#include "linklayer/aloha/AlohaApMac.h"

namespace inet
{
//Define_Module(AlohaApMac);
//
//AlohaApMac::AlohaApMac()
//{
//    m_msgSelfEndRx=nullptr;
//    m_pkTemp=nullptr;
//}
//
//AlohaApMac::~AlohaApMac()
//{
//    cancelAndDelete(m_msgSelfEndRx);
//}
//
//void AlohaApMac::initialize()
//{
//    m_ssChannelStateSignal=registerSignal("channelState");
//    m_msgSelfEndRx=new cMessage("ap-end-reception");
//    m_bChannelBusy=false;
//    emit(m_ssChannelStateSignal,IDLE);
//    m_lCurrentCollisionNumFrames=0;
//
//    //注册信号量
//    m_ssPkCount=registerSignal("pkCount");
//    m_ssPkCount1=registerSignal("pkCount1");
//    m_ssPkCount2=registerSignal("pkCount2");
//    m_ssPkCount3=registerSignal("pkCount3");
//    m_ssPkCount4=registerSignal("pkCount4");
//    m_ssPkCount5=registerSignal("pkCount5");
//    m_ssPkCount6=registerSignal("pkCount6");
//    m_ssPkCount7=registerSignal("pkCount7");
//    m_ssPkCount8=registerSignal("pkCount8");
//    m_ssPkCount9=registerSignal("pkCount9");
//    m_ssPkCount10=registerSignal("pkCount10");
//
//}
//
//void AlohaApMac::handleMessage(cMessage *msg)
//{
//    if(msg==m_msgSelfEndRx)
//    {
//        EV_DEBUG<<getFullPath()<<" handle message: "<<msg->getName()<<endl;
//        EV_DEBUG<<getFullPath()<<" reception finish. "<<endl;
//
//        m_bChannelBusy=false;
//        emit(m_ssChannelStateSignal,IDLE);
//
//        if(m_lCurrentCollisionNumFrames==0)
//        {
//            EV_DEBUG<<"Ap successfully received packet---"<<m_pkTemp->getName()<<endl;
//            emit(m_ssPkCount,1l);
//            switch(m_pkTemp->getSrcProcId())
//            {
//                case 1:
//                {
//                    emit(m_ssPkCount1,1l);
//                    break;
//                }
//                case 2:
//                {
//                    emit(m_ssPkCount2,1l);
//                    break;
//                }
//                case 3:
//                {
//                    emit(m_ssPkCount3,1l);
//                    break;
//                }
//                case 4:
//                {
//                    emit(m_ssPkCount4,1l);
//                    break;
//                }
//                case 5:
//                {
//                    emit(m_ssPkCount5,1l);
//                    break;
//                }
//                case 6:
//                {
//                    emit(m_ssPkCount6,1l);
//                    break;
//                }
//                case 7:
//                {
//                    emit(m_ssPkCount7,1l);
//                    break;
//                }
//                case 8:
//                {
//                    emit(m_ssPkCount8,1l);
//                    break;
//                }
//                case 9:
//                {
//                    emit(m_ssPkCount9,1l);
//                    break;
//                }
//                case 10:
//                {
//                    emit(m_ssPkCount10,1l);
//                    break;
//                }
//                default:
//                {
//                    throw cRuntimeError("AP receive error distance flag.");
//                    break;
//                }
//            }
//            delete m_pkTemp;
//            m_pkTemp=nullptr;
//
//        }
//
//        m_lCurrentCollisionNumFrames=0;
//
//    }
//    else
//    {
//        if(msg->getKind()==PacketKind_Host_Data)
//        {
//            EV_DEBUG<<getFullPath()<<" handle message: "<<msg->getName()<<endl;
//
//            cPacket *pk=dynamic_cast<cPacket *>(msg);
//
//
//            EV_DEBUG<<" pk's duration: "<<pk->getDuration()<<endl;
//            simtime_t stEndReceptionTime=simTime()+pk->getDuration();
//
//            if(!m_bChannelBusy)//信道空闲
//            {
//                EV_DEBUG<<"Ap Starts to receive packet."<<endl;
//                m_pkTemp=pk->dup();
//                m_stRecvStartTime=simTime();
//                m_bChannelBusy=true;
//                emit(m_ssChannelStateSignal,TRANSMISSION);
//                scheduleAt(stEndReceptionTime,m_msgSelfEndRx);
//            }
//            else //信道忙
//            {
//                EV_DEBUG<<"Another packet arrives while receiving --- collision!"<<endl;
//                emit(m_ssChannelStateSignal,COLLISION);
//
//                if(m_lCurrentCollisionNumFrames==0)
//                {
//                    m_lCurrentCollisionNumFrames=2;
//                }
//                else
//                {
//                    m_lCurrentCollisionNumFrames++;
//                }
//
//                if(stEndReceptionTime > m_msgSelfEndRx->getArrivalTime())
//                {
//                    cancelEvent(m_msgSelfEndRx);
//                    scheduleAt(stEndReceptionTime,m_msgSelfEndRx);
//                }
//            }
//            m_bChannelBusy=true;
//            delete pk;
//        }
//        else
//        {
//            throw cRuntimeError("Ap received error type message.");
//        }
//    }
//}

}


