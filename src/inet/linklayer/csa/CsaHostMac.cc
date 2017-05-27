/*
 * CsaHostMac.cc
 *
 *  Created on: 2017年3月9日
 *      Author: wh
 */

#include "inet/linklayer/csa/CsaHostMac.h"

namespace inet
{
//Define_Module(CsaHostMac);
//
//CsaHostMac::CsaHostMac()
//{
//    m_msgSelfSendData=nullptr;
//    m_msgSelfDataTimer=nullptr;
//    m_msgSelfReSend=nullptr;
//}
//
//CsaHostMac::~CsaHostMac()
//{
//    cancelAndDelete(m_msgSelfSendData);
//    cancelAndDelete(m_msgSelfDataTimer);
//    cancelAndDelete(m_msgSelfReSend);
//}
//
//void CsaHostMac::initialize()
//{
//    //获取ap指针
//    m_mdAp=getModuleByPath("ap");
//    EV<<"ap's name: "<<m_mdAp->getName()<<endl;
//
//    if(!m_mdAp)
//    {
//        throw cRuntimeError("AP not found");
//    }
//
//    //从ini获取参数
//    m_stSlotTime=par("slotTime");
//    m_nSlotNum=par("slotNum");
//    m_nAckSlotNum=par("ackSlotNum");
//
//    m_qApp.setName("appQueue");
//    m_qReSend.setName("reSendQueue");
//
//    //建立新的自消息
//    m_msgSelfSendData=new cMessage("SelfSendData");
//    m_msgSelfDataTimer=new cMessage("SelfDataTimer");
//    m_msgSelfReSend=new cMessage("SelfReSendData");
//    //0时刻开始发送数据
//    scheduleAt(0,m_msgSelfSendData);
//
//}
//
//void CsaHostMac::handleMessage(cMessage *msg)
//{
//    //如果是自消息
//    if(msg->isSelfMessage())
//    {
//        //自消息提醒该发送数据包了
//        if(msg==m_msgSelfSendData)
//        {
//            //调度下一次数据发送
//            scheduleAt(simTime()+m_stSlotTime*m_nSlotNum,m_msgSelfSendData);
//            //收到m_msgSelfSendData后就开始数据发送
//            //如果队列不为空
//            if(!m_qApp.isEmpty())
//            {
//                CsaHostData *pk=generateCSAPacket();
//                sendDataPacket(pk);
//            }
//            //队列为空，
//            else
//            {
//                EV<<m_qApp.getName()<<" is empty!"<<endl;
//            }
//        }
//        else
//        {
//            if(msg->getKind()==PacketKind_Self_CSA_Host_Data)
//            {
//                sendDirect(msg,m_mdAp->gate("in"));
//            }
//            else
//            {
//                if(msg==m_msgSelfDataTimer)
//                {
//                    scheduleAt(simTime()+m_stSlotTime,m_msgSelfReSend);
//                }
//                else
//                {
//                    if(msg==m_msgSelfReSend)
//                    {
//                        CsaHostData *pk=generateCSAPacket();
//                        sendDataPacket(pk);
//                        scheduleAt((m_nSlotNum-1)*m_stSlotTime+simTime(),m_msgSelfDataTimer);
//                    }
//                    else
//                    {
//                        throw cRuntimeError("Error self message type.");
//                    }
//                }
//            }
//
//        }
//    }
//    else
//    {
//        switch(msg->getKind())
//        {
//            case PacketKind_Application:
//            {
//                if(m_qApp.getLength()==QUEUE_CAPACITY)
//                {
//                    delete msg;
//                    EV<<"Queue is full, new message is deleted."<<endl;
//                }
//                else
//                {
//                    m_qApp.insert(msg);
//                    EV<<"AppQueue length is "<<m_qApp.getLength()<<endl;
//                }
//                break;
//            }
//            case PacketKind_Ap_ACK:
//            {
//                cancelEvent(m_msgSelfDataTimer);
//                //scheduleAt(simTime()+m_nAckSlotNum*m_stSlotTime,m_msgSelfSendData);
//                delete msg;
//                break;
//            }
//            default:
//            {
//                throw cRuntimeError("Error message type.");
//            }
//        }
//    }
//}
//
//int CsaHostMac::getCopyNum()
//{
//    //0.5631x3+0.0436x3+0.3933x5
//    int nCopyNum=0;
//    double dRandom=dblrand();
//    if(dRandom<0.5631)
//    {
//        nCopyNum=2;
//    }
//    else
//    {
//        if(dRandom<0.6067)
//        {
//            nCopyNum=3;
//        }
//        else
//        {
//            nCopyNum=5;
//        }
//    }
//    return nCopyNum;
//}
//
//void CsaHostMac::selectSlots(std::vector<int> &vec, int nSlotNum)
//{
//    //随机选择时隙
//    int temp[nSlotNum];
//    int i,j;
//    int nRandom;
//
//    double dDistance=getDistance();
//    int nPropagationSlotNum=getPropagationSlotNum(dDistance,m_stSlotTime);
//    EV<<"Propagation slot num: "<<nPropagationSlotNum<<endl;
//
//    for(i=0;i<nSlotNum; )
//    {
//        nRandom=nPropagationSlotNum+intrand(m_nSlotNum-m_nAckSlotNum-nPropagationSlotNum);
//
//        temp[i]=nRandom;
//        for(j=0;j<i;j++)
//        {
//            if(temp[j]==temp[i])
//            {
//                break;
//            }
//        }
//        if(j==i)
//        {
//            EV<<"nRandom: "<<nRandom<<endl;
//            i++;
//        }
//    }
//    for(i=0;i<nSlotNum;i++)
//    {
//        vec.push_back(temp[i]);
//    }
//
//    //按照距离来选择时隙。
////    int temp[nSlotNum];
////    int i,j;
////    int nRandom;
////    double dDistance=getDistance();
////    int nPropagationSlotNum=getPropagationSlotNum(dDistance,m_stSlotTime);
////    EV<<"Propagation slot num: "<<nPropagationSlotNum<<endl;
////
////    for(i=0; i<nSlotNum; )
////    {
////        if(i==0)
////        {
////            temp[i]=nPropagationSlotNum;
////            i++;
////        }
////        else
////        {
////            nRandom=nPropagationSlotNum+intrand(m_nSlotNum-m_nAckSlotNum-nPropagationSlotNum);
////
////            temp[i]=nRandom;
////            for(j=0;i<i;j++)
////            {
////                if(temp[j]==temp[i])
////                {
////                    break;
////                }
////            }
////
////            if(j==i)
////            {
////                EV<<"nRandom:"<<nRandom<<endl;
////                i++;
////            }
////        }
////    }
////
////    for(i=0;i<nSlotNum;i++)
////    {
////        vec.push_back(temp[i]);
////    }
//}
//
//CsaHostData* CsaHostMac::generateCSAPacket()
//{
//     CsaHostData *pk=new CsaHostData("CsaHostData");
//     cModule *mdParent=getParentModule();
//
//     pk->setNHostId(mdParent->getId());
//     pk->setStrHostPath(mdParent->getFullPath().c_str());
//
//     int nCopyNum=getCopyNum();
//     pk->setNSlotNum(nCopyNum);
//     vector<int> vecPoint;
//     selectSlots(vecPoint,nCopyNum);
//
//     pk->setPoint(vecPoint);
//     pk->setBIsRecovery(false);
//
//     return pk;
//
//}
//
//void CsaHostMac::sendDataPacket(CsaHostData *msg)
//{
//    vector<int> vec=msg->getPoint();
//    for(int i=0;i<vec.size();i++)
//    {
//        CsaHostData *newDup=msg->dup();
//        newDup->setNSlotIndex(vec[i]);
//        newDup->setKind(PacketKind_Self_CSA_Host_Data);
//        scheduleAt(simTime()+vec[i]*m_stSlotTime,newDup);
//    }
//}
//
//Coord CsaHostMac::getCurrentPosition()
//{
//    cModule *mdParent=getParentModule();
//    cModule *mdMobility=mdParent->getSubmodule("mobility");
//    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
//    return mdMovingMobility->getCurrentPosition();
//}
//
//Coord CsaHostMac::getApPosition()
//{
//    cModule *mdMobilityOfAp=m_mdAp->getSubmodule("mobility");
//    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
//    return mdMovingMobilityOfAp->getCurrentPosition();
//}
//
//double CsaHostMac::getDistance()
//{
//    Coord cdHost=getCurrentPosition();
//    Coord cdAp=getApPosition();
//    Coord cdDistance=cdHost-cdAp;
//
//    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
//}
//
//int CsaHostMac::getPropagationSlotNum(double dDistance,simtime_t stSlotLength)
//{
//    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
//    return ceil(stPropagationTime/stSlotLength);
//}

}


