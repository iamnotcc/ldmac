/*
 * ldHostMac.cc
 *
 *  Created on: 2016年6月14日
 *      Author: Administrator
 */

#include "LdHostMac.h"
#include "common/geometry/common/Coord.h"
#include "mobility/contract/IMobility.h"
#include "common/INETMath.h"
#include <string>

namespace inet
{
//Define_Module(LdHostMac);
//
//LdHostMac::LdHostMac()
//{
//    m_msgSelfReq=nullptr;
//    m_msgSelfData=nullptr;
//}
//
//LdHostMac::~LdHostMac()
//{
//    cancelAndDelete(m_msgSelfReq);
//    cancelAndDelete(m_msgSelfData);
//}
//
////函数：初始化
//void LdHostMac::initialize()
//{
//    //发现ap模块
//    m_mdAp=getModuleByPath("ap");
//    EV<<"found ap: "<<m_mdAp->getFullPath()<<endl;
//    if(!m_mdAp)
//    {
//        throw cRuntimeError("LdAp not found");
//    }
//
//    //参数初始化
//    m_nRequestSlotNum=par("requestSlotNum");
//    m_nAllocateSlotNum=par("allocateSlotNum");
//    m_nTransmitSlotNum=par("transmitSlotNum");
//    m_stSlotLength=par("slotLength");
//
//    m_dTxRate=par("txRate");
//    m_nReqPktLength=&par("reqPktLength");
//
//    m_nSlotLeftCounter=0;
//
//    //DEBUG INFO
//    EV_DEBUG<<"LdHostMac's parameters: "<<endl;
//    EV_DEBUG<<"m_nRequestSlotNum: "<<m_nRequestSlotNum<<endl;
//    EV_DEBUG<<"m_nAllocateSlotNum: "<<m_nAllocateSlotNum<<endl;
//    EV_DEBUG<<"m_nTransmitSlotNum: "<<m_nTransmitSlotNum<<endl;
//    EV_DEBUG<<"m_stSlotLength: "<<m_stSlotLength<<endl;
//    EV_DEBUG<<"m_dTxRate: "<<m_dTxRate<<endl;
//    EV_DEBUG<<"m_nReqPktLength: "<<m_nReqPktLength<<endl;
//
//    //设置队列的名称
//    m_qAppPacketList.setName("AppPacketQueue");
//
//    //初始化host发送数据的时隙index和时隙个数
//    m_hostTransmitInfo={-1,-1};
//
//    //初始化request自消息
//    m_msgSelfReq=new cMessage("msgSelfReq");
//    scheduleAt(0,m_msgSelfReq);
//
//    m_msgSelfData=new cMessage("msgSelfData");
//
//    //信号量注册
//    //被丢弃的数据包个数
//    m_ssDiscardPkCount=registerSignal("discardPkCount");
//    //总共发送的数据包个数
//    m_ssSendPkCount=registerSignal("sendPkCount");
//    //排队时间
//    m_ssQueueTime=registerSignal("queueTime");
//    m_stQueueTime=0;
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
//}
//
////函数：处理各类消息
//void LdHostMac::handleMessage(cMessage *msg)
//{
//    //处理4类消息
//    //自消息：m_msgSelfReq，提醒发送req;m_msgSelfData，提醒发送data
//    //PacketKind_Ap_Allocation：ap的广播信息
//    //PacketKind_Application：应用层消息
//
//    //如果是自消息
//    if(msg->isSelfMessage())
//    {
//        //自消息：提醒发送req
//        if(msg==m_msgSelfReq)
//        {
//            m_stTime=m_stSlotLength*(m_nRequestSlotNum+m_nAllocateSlotNum+m_nTransmitSlotNum);
//            emit(m_ssTime0,m_stTime);
//            switch(setDistanceFlag())
//            {
//                case 1:
//                {
//                    emit(m_ssTime1,m_stTime);
//                    break;
//                }
//                case 2:
//                {
//                    emit(m_ssTime2,m_stTime);
//                    break;
//                }
//                case 3:
//                {
//                    emit(m_ssTime3,m_stTime);
//                    break;
//                }
//                case 4:
//                {
//                    emit(m_ssTime4,m_stTime);
//                    break;
//                }
//                case 5:
//                {
//                    emit(m_ssTime5,m_stTime);
//                    break;
//                }
//                case 6:
//                {
//                    emit(m_ssTime6,m_stTime);
//                    break;
//                }
//                case 7:
//                {
//                    emit(m_ssTime7,m_stTime);
//                    break;
//                }
//                case 8:
//                {
//                    emit(m_ssTime8,m_stTime);
//                    break;
//                }
//                case 9:
//                {
//                    emit(m_ssTime9,m_stTime);
//                    break;
//                }
//                case 10:
//                {
//                    emit(m_ssTime10,m_stTime);
//                    break;
//                }
//                default:
//                {
//                    throw cRuntimeError("Error location");
//                }
//            }
//            //立即调度下一次自消息
//            scheduleAt(simTime()+m_stSlotLength*(m_nRequestSlotNum+m_nAllocateSlotNum+m_nTransmitSlotNum),m_msgSelfReq);
//
//            //向AP申请的时隙都已经用完了
//            if(m_nSlotLeftCounter==0)
//            {
//                if(!m_qAppPacketList.isEmpty())
//                {
//                    EV_DEBUG<<"m_nSlotLeftCounter="<<m_nSlotLeftCounter<<", ready to generate a new Request packet."<<endl;
//                    //新建一个req包
//                    HostReqPacket *pk=generateReqPacket();
//
//                    //调试输出Pk的信息
//                    EV_DEBUG<<"A new Request packet is generated.Detailed information:"<<endl;
//                    EV_DEBUG<<"Request packet kind: "<< pk->getKind()<<endl;
//                    EV_DEBUG<<"Request packet bitLength: "<< pk->getBitLength()<<endl;
//                    EV_DEBUG<<"Request packet host_Id: "<< pk->getNHostId()<<endl;
//                    EV_DEBUG<<"Request packet host_path: "<< pk->getStrHostPath()<<endl;
//                    EV_DEBUG<<"Request packet request_slot_num: "<< pk->getNRequestSlotNum()<<endl;
//                    EV_DEBUG<<"Request packet host_position: "<< pk->getCdHostPosition()<<endl;
//                    EV_DEBUG<<"Request packet propagation_slot_num: "<< pk->getNPropagationSlotNum()<<endl;
//
//                    //m_nSlotLeftCounter 重新赋值，
//                    m_nSlotLeftCounter=pk->getNRequestSlotNum();
//
//                    //计算发送时间，
//                    simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//                    //计算传播延迟
//                    simtime_t stPropagationDelay=getDistance()/SPEED_OF_LIGHT;
//                    //把数据包发送给AP
//                    sendDirect(pk,stPropagationDelay,stDuration,m_mdAp->gate("in"));
//                }
//            }
//        }
//        else
//        {
//            //如果自消息是提醒发送数据
//            if(msg==m_msgSelfData)
//            {
//                //发送数据
//                 sendDataPacket(m_hostTransmitInfo);
//            }
//            else
//            {
//                throw cRuntimeError("Error message type");
//            }
//        }
//    }
//    else
//    {
//        if(msg->getKind()==PacketKind_Ap_Allocation)
//        {
//            ApAllocationPacket *pk=dynamic_cast<ApAllocationPacket *>(msg);
//            m_hostTransmitInfo=getHostTransmitInfo(pk);
//            delete pk;
//            m_nSlotLeftCounter=m_nSlotLeftCounter-m_hostTransmitInfo.nSlotNum;
//            scheduleAt(simTime()+m_stSlotLength*m_nAllocateSlotNum+(m_hostTransmitInfo.nIndex)*m_stSlotLength,m_msgSelfData);
//        }
//        else
//        {
//            if(msg->getKind()==PacketKind_Application)
//            {
//                if(m_qAppPacketList.getLength()==QUEUE_CAPACITY)
//                {
//                    //数据队列满时，丢弃数据包
//                    EV_DEBUG<<"m_qAppPacketList is full, and delete "<<msg->getName()<<endl;
//                    delete msg;
//                    emit(m_ssDiscardPkCount,1l);
//                }
//                else
//                {
//                    msg->setArrivalTime(simTime());
//                    m_qAppPacketList.insert(msg);
//                    EV_DEBUG<<"Queue length is: "<<m_qAppPacketList.getLength()<<endl;
//                }
//            }
//            else
//            {
//                throw cRuntimeError("Error Message Type");
//            }
//        }
//    }
//}
//
//
////函数：生成host的req包
//HostReqPacket *LdHostMac::generateReqPacket()
//{
//    HostReqPacket *pk=new HostReqPacket();
//    //设置req的参数
//    //类型
//    pk->setKind(PacketKind_Host_Request);
//    //长度
//    pk->setBitLength(m_nReqPktLength->longValue());
//    //HOST 的 ID
//    cModule *mdParent=this->getParentModule();
//    int nParentModuleID=mdParent->getId();
//    pk->setNHostId(nParentModuleID);
//    //HOST的路径
//    string strParentPath=mdParent->getFullPath();
//    pk->setStrHostPath(strParentPath.c_str());
//    //需要申请的时隙数
//    //TODO:最大申请的时隙数应该要控制
//    int nQueueSize=m_qAppPacketList.getLength();
//    pk->setNRequestSlotNum(nQueueSize);
//    //地理位置
//    pk->setCdHostPosition(getCurrentPosition());
//    //传播时隙个数
//    double dDistanceToAp=getDistance();
//    int nPropagationSlotNum=getPropagationSlotNum(dDistanceToAp,m_stSlotLength);
//    pk->setNPropagationSlotNum(nPropagationSlotNum);
//
//    return pk;
//}
//
////函数：发送req包
//void LdHostMac::sendReqPacket(HostReqPacket *pk)
//{
//    simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//    simtime_t stPropagationDelay=getDistance()/SPEED_OF_LIGHT;
//    //TODO:可能需要修改gate的参数
//    sendDirect(pk,stPropagationDelay,stDuration,m_mdAp->gate("in"));
//}
//
////函数：从AP的广播包中获取host的传输信息
//HostTransmitInfo LdHostMac::getHostTransmitInfo(ApAllocationPacket *pk)
//{
//    int nColSlotNum=pk->getNColSlotNum();
//    int nRowSlotNum=pk->getNRowSlotNum();
//    vector<vector<int> > allocationMatrix=pk->getOmAllocationMatrix();
//
//    int nHostId=-1;
//    for(int i=0;i<nRowSlotNum;i++)
//    {
//        if(allocationMatrix[i][nColSlotNum-1]==this->getParentModule()->getId())
//        {
//            nHostId=i;
//            break;
//        }
//    }
//
//    vector<int> vecHost;
//    for(int i=0;i<nColSlotNum;i++)
//    {
//        vecHost.push_back(allocationMatrix[nHostId][i]);
//    }
//
//    HostTransmitInfo structReturn;
//    int nIndex=0;
//    int nSlotNum=0;
//
//    for(int i=0;i<vecHost.size();i++)
//    {
//        if(vecHost[i]==1)
//        {
//            if(nSlotNum==0)
//            {
//                nIndex=i;
//            }
//            nSlotNum++;
//        }
//    }
//
//    structReturn.nIndex=nIndex;
//    structReturn.nSlotNum=nSlotNum;
//    return structReturn;
//}
//
////函数：发送数据包
//void LdHostMac::sendDataPacket(HostTransmitInfo structTransmitInfo)
//{
//    int nQueueSizeBefor=m_qAppPacketList.getLength();
//
//    //设置一个临时队列，保存本次丢失的数据包
//    cQueue qTemp;
//
//    for(int i=0;i<structTransmitInfo.nSlotNum;i++)
//    {
//        //首先判断有重传的数据包
//        //如果有重传的包
//        if(!m_qReTransmitQueue.isEmpty())
//        {
//            cPacket *pk=dynamic_cast<cPacket*>(m_qReTransmitQueue.pop());
//            pk->setKind(PacketKind_Host_Data);
//            pk->setSrcProcId(setDistanceFlag());
//            simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//            simtime_t stPropagationDelay=getDistance()/SPEED_OF_LIGHT;
//
//            m_stQueueTime=simTime()-pk->getArrivalTime();
//            emit(m_ssQueueTime,m_stQueueTime);
//            sendDirect(pk,stPropagationDelay,stDuration,m_mdAp->gate("in"));
//            //成功发送一个数据包
//            emit(m_ssSendPkCount,1l);
//        }
//        //如果没有重传
//        else
//        {
//            //如果数据队列不为空
//            if(!m_qAppPacketList.isEmpty())
//            {
//                //取出一个数据包
//                cPacket *pk=dynamic_cast<cPacket*>(m_qAppPacketList.pop());
//                pk->setKind(PacketKind_Host_Data);
//
//                //设置是否会丢失
//                m_dRandom=dblrand();
//                if(m_dRandom> PACKET_LOSS_RATE)
//                {
//                    simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//                    simtime_t stPropagationDelay=getDistance()/SPEED_OF_LIGHT;
//                    pk->setSrcProcId(setDistanceFlag());
//                    m_stQueueTime=simTime()-pk->getArrivalTime();
//                    emit(m_ssQueueTime,m_stQueueTime);
//
//                    sendDirect(pk,stPropagationDelay,stDuration,m_mdAp->gate("in"));
//                    //成功发送一个数据包
//                    emit(m_ssSendPkCount,1l);
//                }
//                else
//                {
//                    EV<<"Host data is lost, and will retransmit."<<endl;
//                    qTemp.insert(pk);
//                }
//            }
//        }
//    }
//    //将丢失的数据包保存到m_qReTransmitQueue
//    for(int i=0;i<qTemp.getLength();i++)
//    {
//        m_qReTransmitQueue.insert(qTemp.pop());
//    }
//    int nQueueSizeAfter=m_qAppPacketList.getLength();
//    int nReTransmitQueueSize=m_qReTransmitQueue.getLength();
//    EV_DEBUG<<"Queue length before: "<<nQueueSizeBefor<<endl;
//    EV_DEBUG<<"Queue length after: "<<nQueueSizeAfter<<endl;
//    EV_DEBUG<<getFullPath()<<" sent "<<(nQueueSizeBefor-nQueueSizeAfter)<<" packets"<<endl;
//    EV_DEBUG<<getFullPath()<<" totally is allocated "<<structTransmitInfo.nSlotNum<<" slots."<<endl;
//}
//
//
////基础函数
////函数：获取当前位置
//Coord LdHostMac::getCurrentPosition()
//{
//    cModule *mdParent=getParentModule();
//    cModule *mdMobility=mdParent->getSubmodule("mobility");
//    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
//    return mdMovingMobility->getCurrentPosition();
//}
//
////函数：获取AP的位置
//Coord LdHostMac::getApPosition()
//{
//    cModule *mdMobilityOfAp=m_mdAp->getSubmodule("mobility");
//    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
//    return mdMovingMobilityOfAp->getCurrentPosition();
//}
//
////函数：计算host和AP之间的距离
//double LdHostMac::getDistance()
//{
//    Coord cdHost=getCurrentPosition();
//    Coord cdAp=getApPosition();
//    Coord cdDistance=cdHost-cdAp;
//
//    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
//}
//
////函数：将距离转化为时隙个数
//int LdHostMac::getPropagationSlotNum(double dDistance,simtime_t stSlotLength)
//{
//    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
//    return ceil(stPropagationTime/stSlotLength);
//}
//
////设置距离标志，根据距离远近来设置1~10
//int LdHostMac::setDistanceFlag()
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


