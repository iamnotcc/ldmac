/*
 * CsaApMac.cc
 *
 *  Created on: 2017Äê3ÔÂ9ÈÕ
 *      Author: wh
 */
#include "inet/linklayer/csa/CsaApMac.h"

namespace inet
{
//Define_Module(CsaApMac);
//
//CsaApMac::CsaApMac()
//{
//    m_msgSelfHandleData=nullptr;
//}
//
//CsaApMac::~CsaApMac()
//{
//    cancelAndDelete(m_msgSelfHandleData);
//}
//
//void CsaApMac::initialize()
//{
//    m_nSlotNum=par("slotNum");
//    m_nAckSlotNum=par("ackSlotNum");
//    m_stSlotTime=par("slotTime");
//    m_bIsPkArrival=false;
//
//    m_msgSelfHandleData=new cMessage("SelfMsg");
//    scheduleAt((m_nSlotNum-m_nAckSlotNum)*m_stSlotTime,m_msgSelfHandleData);
//}
//
//void CsaApMac::handleMessage(cMessage *msg)
//{
//    if(msg->isSelfMessage())
//    {
//        if(msg==m_msgSelfHandleData)
//        {
//            handleHostData();
//            cModule *mdHost;
//            for(int i=0;i<vecACK.size();i++)
//            {
//                mdHost=getModuleByPath(vecACK[i]->getStrHostPath());
//                cMessage *ack=new cMessage("ack");
//                ack->setKind(PacketKind_Ap_ACK);
//                sendDirect(ack,mdHost->gate("in"));
//            }
//
//            for(int i=0;i<vecData.size();i++)
//            {
//                delete vecData[i];
//            }
//
//            vecData.clear();
//            m_bIsPkArrival=false;
//            vecACK.clear();
//            scheduleAt(simTime()+m_nSlotNum*m_stSlotTime,m_msgSelfHandleData);
//        }
//        else
//        {
//            throw cRuntimeError("Error self message type.");
//        }
//    }
//    else
//    {
//        if(msg->getKind()==PacketKind_Self_CSA_Host_Data)
//        {
//            CsaHostData *pk=dynamic_cast<CsaHostData *>(msg);
//            vecData.push_back(pk);
//            m_bIsPkArrival=true;
//            EV<<"ap received msg:"<<pk->getName()<<endl;
//        }
//        else
//        {
//            throw cRuntimeError("Error message type.");
//        }
//    }
//}
//
//bool CsaApMac::isDataExist(int hostId)
//{
//    if(vecData.empty())
//    {
//        return false;
//    }
//    else
//    {
//        for(int i=0;i<vecData.size();i++)
//        {
//            if(vecData[i]->getNHostId()==hostId)
//            {
//                return true;
//            }
//        }
//        return false;
//    }
//}
//
//void CsaApMac::handleHostData()
//{
//    CsaHostData *temp;
//
//    while(true)
//    {
//        temp=iteration(vecData);
//        if(temp!=nullptr)
//        {
//            vecACK.push_back(temp);
//        }
//        else
//        {
//            if((m_bIsPkArrival==true)&&(isAllRecovery()))
//            {
//                EV<<"All packets resolved!!!"<<endl;
//            }
//            else
//            {
//                if(m_bIsPkArrival==false)
//                {
//                    EV<<"No packets arrive."<<endl;
//                }
//                else
//                {
//                    EV<<"Some packets unresolved!!!"<<endl;
//                    EV<<"There are "<<vecACK.size()<<" packets resolved!!!"<<endl;
//                }
//            }
//            return;
//        }
//    }
//}
//
//CsaHostData *CsaApMac::iteration(vector<CsaHostData *> &vec)
//{
//    CsaHostData *returnMsg=nullptr;
//    int arr[m_nSlotNum];
//
//    for(int i=0;i<m_nSlotNum;i++)
//    {
//        arr[i]=0;
//    }
//
//    int j=0;
//    for(int i=0;i<vec.size();i++)
//    {
//        j=vec[i]->getNSlotIndex();
//        if(vec[i]->getBIsRecovery()==false)
//        {
//            arr[j]++;
//        }
//    }
//
//    for(int i=0;i<m_nSlotNum;i++)
//    {
//        if(arr[i]==1)
//        {
//            for(int k=0;k<vec.size();k++)
//            {
//                if((vec[k]->getNSlotIndex()==i)&&(vec[k]->getBIsRecovery()==false))
//                {
//                    returnMsg=vec[k];
//                }
//            }
//            EV<<"Successfully decode one packet:"<<returnMsg->getName()<<endl;
//            EV<<"hostID:"<<returnMsg->getNHostId()<<endl;
//
//            vector<CsaHostData *>::iterator it=vec.begin();
//
//            do
//            {
//                if(((*it)->getNHostId()==returnMsg->getNHostId())&&((*it)->getBIsRecovery()==false))
//                {
//                    (*it)->setBIsRecovery(true);
//                }
//                else
//                {
//                    it++;
//                }
//            }while(it!=vecData.end());
//
//            return returnMsg;
//        }
//
//    }
//    return returnMsg;
//
//}
//
//bool CsaApMac::isAllRecovery()
//{
//    for(int i=0;i<vecData.size();i++)
//    {
//        if(vecData[i]->getBIsRecovery()==false)
//        {
//            return false;
//        }
//    }
//    return true;
//}
}



