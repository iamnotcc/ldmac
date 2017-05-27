/*
 * ldApMac.cc
 *
 *  Created on: 2016年6月14日
 *      Author: Administrator
 */
#include "LdApMac.h"

namespace inet
{
//Define_Module(LdApMac);
//
//LdApMac::LdApMac()
//{
//    m_msgSelfAllocation=nullptr;
//}
//
//LdApMac::~LdApMac()
//{
//    cancelAndDelete(m_msgSelfAllocation);
//}
//
////函数：初始化
//void LdApMac::initialize()
//{
//    //从Ini获取参数
//    m_nRequestSlotNum=par("requestSlotNum");
//    m_nAllocateSlotNum=par("allocateSlotNum");
//    m_nTransmitSlotNum=par("transmitSlotNum");
//    m_stSlotLength=par("slotLength");
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
//    //新建自消息
//    m_msgSelfAllocation=new cMessage("msgSelfAllocation");
//    scheduleAt(0+m_stSlotLength*m_nRequestSlotNum,m_msgSelfAllocation);
//}
//
////函数：处理各类消息
//void LdApMac::handleMessage(cMessage *msg)
//{
//    //需要处理3类消息：
//    //自消息：m_msgSelfAllocation 提醒广播分配消息
//    //来自host的req消息 PacketKind_Host_Request
//    //来自host的data消息 PacketKind_Host_Data
//
//    //如果是自消息
//    if(msg==m_msgSelfAllocation)
//    {
//        EV_DEBUG<<"AP is ready to broadcast allocation information.... "<<endl;
//        broadcastAllocationInfo();
//        scheduleAt(simTime()+m_stSlotLength*(m_nRequestSlotNum+m_nAllocateSlotNum+m_nTransmitSlotNum),m_msgSelfAllocation);
//    }
//    else
//    {
//        //
//        if(msg->getKind()==PacketKind_Host_Request)
//        {
//            EV_DEBUG<<"Ap received a request packet from "<<msg->getSenderModule()->getFullPath().c_str()<<endl;
//            HostReqPacket *pk=dynamic_cast<HostReqPacket *>(msg);
//            EV_DEBUG<<"Request packet detailed information: "<<endl;
//            EV_DEBUG<<"host_id: "<<pk->getNHostId()<<endl;
//            EV_DEBUG<<"host_path: "<<pk->getStrHostPath()<<endl;
//            EV_DEBUG<<"request_slot_num: "<<pk->getNRequestSlotNum()<<endl;
//            EV_DEBUG<<"propagation_slot_num: "<<pk->getNPropagationSlotNum()<<endl;
//            if(pk->getNRequestSlotNum()>0)
//            {
//                HostReqInfo structHostReqInfo={pk->getNHostId(),pk->getStrHostPath(),pk->getNRequestSlotNum(),pk->getNPropagationSlotNum()};
//                m_vecHostReqs.push_back(structHostReqInfo);
//                EV_DEBUG<<"A new element is added into m_vecHostReqs"<<endl;
//                EV_DEBUG<<"m_vecHostReqs size:"<<m_vecHostReqs.size()<<endl;
//                EV_DEBUG<<"m_vecHostReqs capacity:"<<m_vecHostReqs.capacity()<<endl;
//                outputVec(m_vecHostReqs);
//            }
//            else
//            {
//                EV_DEBUG<<"A invalid request packet is received, request_slot_num="<<pk->getNRequestSlotNum()<<endl;
//                throw cRuntimeError("A invalid request packet is received.");
//            }
//            delete pk;
//        }
//        else
//        {
//            if(msg->getKind()==PacketKind_Host_Data)
//            {
//                EV<<"ap received a data packet."<<endl;
//                emit(m_ssPkCount,1l);
//                switch(msg->getSrcProcId())
//                {
//                    case 1:
//                    {
//                        emit(m_ssPkCount1,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 2:
//                    {
//                        emit(m_ssPkCount2,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 3:
//                    {
//                        emit(m_ssPkCount3,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 4:
//                    {
//                        emit(m_ssPkCount4,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 5:
//                    {
//                        emit(m_ssPkCount5,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 6:
//                    {
//                        emit(m_ssPkCount6,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 7:
//                    {
//                        emit(m_ssPkCount7,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 8:
//                    {
//                        emit(m_ssPkCount8,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 9:
//                    {
//                        emit(m_ssPkCount9,1l);
//                        delete msg;
//                        break;
//                    }
//                    case 10:
//                    {
//                        emit(m_ssPkCount10,1l);
//                        delete msg;
//                        break;
//                    }
//                    default:
//                    {
//                        throw cRuntimeError("AP receive error distance flag.");
//                        delete msg;
//                        break;
//                    }
//                }
//            }
//            else
//            {
//                throw cRuntimeError("AP receive error message.");
//            }
//        }
//    }
//
//}
////函数：输出矢量
//void LdApMac::outputVec(vector<HostReqInfo> vec)
//{
//    EV_DEBUG<<"There are "<<vec.size()<<" elements in the vector."<<endl;
//    if(vec.size()!=0)
//    {
//        for(int i=0;i<vec.size();i++)
//        {
//            EV_DEBUG<<"host_id="<<vec[i].nHostId<<", host_path="<<vec[i].strHostPath.c_str()<<", request_slot_num="<<vec[i].nReqSlotNum<<", propagation_slot_num="<<vec[i].nPropagationSlotNum<<endl;
//        }
//    }
//}
//
////函数：广播分配消息
//void LdApMac::broadcastAllocationInfo()
//{
//    //如果没有host申请消息，
//    if(m_vecHostReqs.empty())
//    {
//        EV_DEBUG<<"host_request_queue is empty. No allocation packet sent."<<endl;
//    }
//    //如果有，要先给这些节点分配时隙，然后再依次广播给他们
//    else
//    {
//        EV_DEBUG<<"Ap is generating allocation packet, and is broadcasting..."<<endl;
//
//        EV_DEBUG<<"***************m_vecHostReqs capacity:"<<m_vecHostReqs.capacity()<<endl;
//
//        vector<HostReqInfo> vecTemp(m_vecHostReqs);
//
//        int nVecSize=vecTemp.size();
//
//        sortVec(vecTemp);
//
//        vector<vector<int> > A;
//        vector<vector<int> > B;
//        A.resize(nVecSize);
//        B.resize(nVecSize);
//        for(int i=0;i<nVecSize;i++)
//        {
//            A[i].resize(m_nTransmitSlotNum);
//            B[i].resize(m_nTransmitSlotNum);
//        }
//
//        for(int i=0;i<nVecSize;i++)
//        {
//            for(int j=0;j<m_nTransmitSlotNum;j++)
//            {
//                B[i][j]=0;
//            }
//        }
//
//        vector<int> vecAllocatedSlotNum(nVecSize);
//        for(int i=0;i<nVecSize;i++)
//        {
//            vecAllocatedSlotNum[i]=0;
//        }
//
//        int nTotalSlot=m_nTransmitSlotNum-vecTemp[0].nPropagationSlotNum;
//
//        while(nTotalSlot>0)
//        {
//            for(int i=0;i<nVecSize;i++)
//            {
//                if((vecAllocatedSlotNum[i]<vecTemp[i].nReqSlotNum)&&(vecAllocatedSlotNum[i]<(m_nTransmitSlotNum-vecTemp[i].nPropagationSlotNum))&&(nTotalSlot>0))
//                {
//                    vecAllocatedSlotNum[i]++;
//                    nTotalSlot--;
//                }
//                else
//                {
//                    nTotalSlot--;
//                }
//            }
//        }
//
//        int nIndexOfAllocatedSlot=vecTemp[0].nPropagationSlotNum;
//        for(int i=0;i<nVecSize;i++)
//        {
//            for(int j=0;j<vecAllocatedSlotNum[i];j++)
//            {
//                B[i][nIndexOfAllocatedSlot]=1;
//                nIndexOfAllocatedSlot++;
//            }
//        }
//
//        for(int i=0;i<nVecSize;i++)
//        {
//            for(int j=0;j<m_nTransmitSlotNum;j++)
//            {
//                if(B[i][j]==1)
//                {
//                    A[i][j-vecTemp[i].nPropagationSlotNum]=1;
//                }
//            }
//        }
//
//        vector<vector<int> > C;
//        C.resize(nVecSize);
//        for(int i=0;i<nVecSize;i++)
//        {
//            C[i].resize(m_nTransmitSlotNum+1);
//        }
//        for(int i=0;i<nVecSize;i++)
//        {
//            for(int j=0;j<=m_nTransmitSlotNum;j++)
//            {
//                if(j==m_nTransmitSlotNum)
//                {
//                    C[i][j]=vecTemp[i].nHostId;
//                }
//                else
//                {
//                    C[i][j]=A[i][j];
//                }
//            }
//        }
//
//        ApAllocationPacket *pk=new ApAllocationPacket();
//        pk->setKind(PacketKind_Ap_Allocation);
//        pk->setOmAllocationMatrix(C);
//        pk->setNColSlotNum(m_nTransmitSlotNum+1);
//        pk->setNRowSlotNum(nVecSize);
//
//        cModule *mdHost;
//        for(int i=0;i<nVecSize;i++)
//        {
//            mdHost=getModuleByPath(vecTemp[i].strHostPath.c_str());
//            sendDirect(i==nVecSize-1?pk:pk->dup(),0,0,mdHost->gate("in"));
//        }
//
//        m_vecHostReqs.clear();
//        for(int i=0;i<nVecSize;i++)
//        {
//            vecTemp[i].nReqSlotNum=vecTemp[i].nReqSlotNum-vecAllocatedSlotNum[i];
//            if(vecTemp[i].nReqSlotNum>0)
//            {
//                m_vecHostReqs.push_back(vecTemp[i]);
//            }
//        }
//    }
//
//
//}
//
//void LdApMac::sortVec(vector<HostReqInfo> &vec)
//{
//    HostReqInfo structTemp;
//    for(int i=0;i<vec.size();i++)
//    {
//        for(int j=i;j<vec.size()-1;j++)
//        {
//            if(vec[j].nPropagationSlotNum > vec[j+1].nPropagationSlotNum)
//            {
//                structTemp=vec[j];
//                vec[j]=vec[j+1];
//                vec[j+1]=structTemp;
//            }
//        }
//    }
//}
}



