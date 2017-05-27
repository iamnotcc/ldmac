/*
 * ldHostMac.cc
 *
 *  Created on: 2016��6��14��
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
////��������ʼ��
//void LdHostMac::initialize()
//{
//    //����apģ��
//    m_mdAp=getModuleByPath("ap");
//    EV<<"found ap: "<<m_mdAp->getFullPath()<<endl;
//    if(!m_mdAp)
//    {
//        throw cRuntimeError("LdAp not found");
//    }
//
//    //������ʼ��
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
//    //���ö��е�����
//    m_qAppPacketList.setName("AppPacketQueue");
//
//    //��ʼ��host�������ݵ�ʱ϶index��ʱ϶����
//    m_hostTransmitInfo={-1,-1};
//
//    //��ʼ��request����Ϣ
//    m_msgSelfReq=new cMessage("msgSelfReq");
//    scheduleAt(0,m_msgSelfReq);
//
//    m_msgSelfData=new cMessage("msgSelfData");
//
//    //�ź���ע��
//    //�����������ݰ�����
//    m_ssDiscardPkCount=registerSignal("discardPkCount");
//    //�ܹ����͵����ݰ�����
//    m_ssSendPkCount=registerSignal("sendPkCount");
//    //�Ŷ�ʱ��
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
////���������������Ϣ
//void LdHostMac::handleMessage(cMessage *msg)
//{
//    //����4����Ϣ
//    //����Ϣ��m_msgSelfReq�����ѷ���req;m_msgSelfData�����ѷ���data
//    //PacketKind_Ap_Allocation��ap�Ĺ㲥��Ϣ
//    //PacketKind_Application��Ӧ�ò���Ϣ
//
//    //���������Ϣ
//    if(msg->isSelfMessage())
//    {
//        //����Ϣ�����ѷ���req
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
//            //����������һ������Ϣ
//            scheduleAt(simTime()+m_stSlotLength*(m_nRequestSlotNum+m_nAllocateSlotNum+m_nTransmitSlotNum),m_msgSelfReq);
//
//            //��AP�����ʱ϶���Ѿ�������
//            if(m_nSlotLeftCounter==0)
//            {
//                if(!m_qAppPacketList.isEmpty())
//                {
//                    EV_DEBUG<<"m_nSlotLeftCounter="<<m_nSlotLeftCounter<<", ready to generate a new Request packet."<<endl;
//                    //�½�һ��req��
//                    HostReqPacket *pk=generateReqPacket();
//
//                    //�������Pk����Ϣ
//                    EV_DEBUG<<"A new Request packet is generated.Detailed information:"<<endl;
//                    EV_DEBUG<<"Request packet kind: "<< pk->getKind()<<endl;
//                    EV_DEBUG<<"Request packet bitLength: "<< pk->getBitLength()<<endl;
//                    EV_DEBUG<<"Request packet host_Id: "<< pk->getNHostId()<<endl;
//                    EV_DEBUG<<"Request packet host_path: "<< pk->getStrHostPath()<<endl;
//                    EV_DEBUG<<"Request packet request_slot_num: "<< pk->getNRequestSlotNum()<<endl;
//                    EV_DEBUG<<"Request packet host_position: "<< pk->getCdHostPosition()<<endl;
//                    EV_DEBUG<<"Request packet propagation_slot_num: "<< pk->getNPropagationSlotNum()<<endl;
//
//                    //m_nSlotLeftCounter ���¸�ֵ��
//                    m_nSlotLeftCounter=pk->getNRequestSlotNum();
//
//                    //���㷢��ʱ�䣬
//                    simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//                    //���㴫���ӳ�
//                    simtime_t stPropagationDelay=getDistance()/SPEED_OF_LIGHT;
//                    //�����ݰ����͸�AP
//                    sendDirect(pk,stPropagationDelay,stDuration,m_mdAp->gate("in"));
//                }
//            }
//        }
//        else
//        {
//            //�������Ϣ�����ѷ�������
//            if(msg==m_msgSelfData)
//            {
//                //��������
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
//                    //���ݶ�����ʱ���������ݰ�
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
////����������host��req��
//HostReqPacket *LdHostMac::generateReqPacket()
//{
//    HostReqPacket *pk=new HostReqPacket();
//    //����req�Ĳ���
//    //����
//    pk->setKind(PacketKind_Host_Request);
//    //����
//    pk->setBitLength(m_nReqPktLength->longValue());
//    //HOST �� ID
//    cModule *mdParent=this->getParentModule();
//    int nParentModuleID=mdParent->getId();
//    pk->setNHostId(nParentModuleID);
//    //HOST��·��
//    string strParentPath=mdParent->getFullPath();
//    pk->setStrHostPath(strParentPath.c_str());
//    //��Ҫ�����ʱ϶��
//    //TODO:��������ʱ϶��Ӧ��Ҫ����
//    int nQueueSize=m_qAppPacketList.getLength();
//    pk->setNRequestSlotNum(nQueueSize);
//    //����λ��
//    pk->setCdHostPosition(getCurrentPosition());
//    //����ʱ϶����
//    double dDistanceToAp=getDistance();
//    int nPropagationSlotNum=getPropagationSlotNum(dDistanceToAp,m_stSlotLength);
//    pk->setNPropagationSlotNum(nPropagationSlotNum);
//
//    return pk;
//}
//
////����������req��
//void LdHostMac::sendReqPacket(HostReqPacket *pk)
//{
//    simtime_t stDuration=pk->getBitLength()/m_dTxRate;
//    simtime_t stPropagationDelay=getDistance()/SPEED_OF_LIGHT;
//    //TODO:������Ҫ�޸�gate�Ĳ���
//    sendDirect(pk,stPropagationDelay,stDuration,m_mdAp->gate("in"));
//}
//
////��������AP�Ĺ㲥���л�ȡhost�Ĵ�����Ϣ
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
////�������������ݰ�
//void LdHostMac::sendDataPacket(HostTransmitInfo structTransmitInfo)
//{
//    int nQueueSizeBefor=m_qAppPacketList.getLength();
//
//    //����һ����ʱ���У����汾�ζ�ʧ�����ݰ�
//    cQueue qTemp;
//
//    for(int i=0;i<structTransmitInfo.nSlotNum;i++)
//    {
//        //�����ж����ش������ݰ�
//        //������ش��İ�
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
//            //�ɹ�����һ�����ݰ�
//            emit(m_ssSendPkCount,1l);
//        }
//        //���û���ش�
//        else
//        {
//            //������ݶ��в�Ϊ��
//            if(!m_qAppPacketList.isEmpty())
//            {
//                //ȡ��һ�����ݰ�
//                cPacket *pk=dynamic_cast<cPacket*>(m_qAppPacketList.pop());
//                pk->setKind(PacketKind_Host_Data);
//
//                //�����Ƿ�ᶪʧ
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
//                    //�ɹ�����һ�����ݰ�
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
//    //����ʧ�����ݰ����浽m_qReTransmitQueue
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
////��������
////��������ȡ��ǰλ��
//Coord LdHostMac::getCurrentPosition()
//{
//    cModule *mdParent=getParentModule();
//    cModule *mdMobility=mdParent->getSubmodule("mobility");
//    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
//    return mdMovingMobility->getCurrentPosition();
//}
//
////��������ȡAP��λ��
//Coord LdHostMac::getApPosition()
//{
//    cModule *mdMobilityOfAp=m_mdAp->getSubmodule("mobility");
//    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
//    return mdMovingMobilityOfAp->getCurrentPosition();
//}
//
////����������host��AP֮��ľ���
//double LdHostMac::getDistance()
//{
//    Coord cdHost=getCurrentPosition();
//    Coord cdAp=getApPosition();
//    Coord cdDistance=cdHost-cdAp;
//
//    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
//}
//
////������������ת��Ϊʱ϶����
//int LdHostMac::getPropagationSlotNum(double dDistance,simtime_t stSlotLength)
//{
//    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
//    return ceil(stPropagationTime/stSlotLength);
//}
//
////���þ����־�����ݾ���Զ��������1~10
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


