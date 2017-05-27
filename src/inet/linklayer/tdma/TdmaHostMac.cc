/*
 * TdmaHostMac.cc
 *
 *  Created on: 2017��3��8��
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
    //Ѱ��apģ��
    m_mdAp=getModuleByPath("ap");
    if(!m_mdAp)
    {
        throw cRuntimeError(" Tdma Ap not found");
    }
    else
    {
        EV<<"Tdma found ap:"<<m_mdAp->getFullPath()<<endl;
    }

    //�����������ʱ�򶪰�
    m_dRandom=dblrand();
    EV<<"m_dRandom="<<m_dRandom<<endl;

    //��ȡ����ֵ
    m_dTxRate=par("txRate");
    m_nSlotNum=par("slotNum");
    m_stSlotLength=par("slotLength");

    m_nReqLength=&par("reqPktLength");

    //���ö�������
    m_qAppQueue.setName("AppDataQueue");
    m_qReTransmitQueue.setName("ReTransmitQueue");

    //��ʼ������Ϣ
    //m_msgSelfReq�������Լ���֪ͨ�÷���req��Ϣ��
    m_msgSelfReq=new cMessage("SelfReqMsg");
    scheduleAt(0,m_msgSelfReq);

    //m_msgSelfData�������Լ���֪ͨ�÷���data������
    m_msgSelfData=new cMessage("SelfDataMsg");

    //ap�����host��ʱ϶��Ϣ,��ʼʱ϶����Լ�ʱ϶����
    m_nTransmitSlotIndex=-1;
    m_nTransmitSlotNum=-1;

    //ע���ź���
    //�Ŷӵȴ�ʱ��
    m_ssQueueTime=registerSignal("queueTime");
    m_stQueueTime=0;
    //�����������ݰ�����
    m_ssDiscardPkCount=registerSignal("discardPkCount");
    //�ܹ����͵����ݰ�����
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

//host������Ϣ
void TdmaHostMac::handleMessage(cMessage *msg)
{
    //�ܹ�4����Ϣ���ͣ�
    //��������Ϣ��m_msgSelfReq�����ѷ���req; m_msgSelfData���������ѷ���data
    //����Ӧ�ò����Ϣ��PacketKind_Application
    //����AP����Ϣ��PacketKind_Ap_Allocation
    if(msg->isSelfMessage())
    {
        //��������ѷ���req
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
            //��һ֡ʱ��������
            scheduleAt(simTime()+m_stSlotLength*m_nSlotNum,m_msgSelfReq);

            //����req��
            sendReqPacket();
        }
        else
        {
            //���ѷ�������
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
            //���������Ӧ�ò�����ݰ�
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
            //���������AP�ķ�����Ϣ
            case PacketKind_Ap_Allocation :
            {
                //��������ap�����ݰ�
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

//��������
void TdmaHostMac::sendDataPacket()
{
    //�˷ѵ�ʱ϶��Ϊ�����ӳٵ��µ�ʱ��
    m_nWasteSlotNum=getPropagationSlot();

    //����һ����ʱ���У�����������Ͷ�ʧ�����ݰ�
    cQueue qTmep;

    //һ֡�ڿ��Է���m_nTransmitSlotNum-m_nWasteSlotNum�����ݰ�
    for(int i=0;i<m_nTransmitSlotNum-m_nWasteSlotNum;i++)
    {
        //�����ж��Ƿ����ش������ݰ�
        //������ش������ݰ�
        if(!m_qReTransmitQueue.isEmpty())
        {
            //ȡ�����ݰ�
            cPacket *pk=dynamic_cast<cPacket *>(m_qReTransmitQueue.pop());
            //���ô���ʱ��ʹ����ӳ�
            simtime_t stDuration=pk->getBitLength()/m_dTxRate;
            simtime_t stPropagation=getDistance()/SPEED_OF_LIGHT;

            //�����Ŷ��ӳ�
            m_stQueueTime=simTime()-pk->getArrivalTime();
            //ͳ����Ϣ
            //�Ŷ��ӳ�
            emit(m_ssQueueTime,m_stQueueTime);
            //�ɹ����͵ĸ���
            emit(m_ssSendPkCount,1l);
            //pk������������
            pk->setSrcProcId(setDistanceFlag());

            sendDirect(pk,stPropagation,stDuration,m_mdAp->gate("in"));
        }
        //û���ش������ݰ�
        else
        {
            //������ݶ��в�Ϊ��
            if(!m_qAppQueue.isEmpty())
            {
                //ȡ��һ������
                cPacket *pk=dynamic_cast<cPacket *>(m_qAppQueue.pop());
                pk->setKind(PacketKind_Host_Data);


                //�����Ƿ�ᶪʧ
                m_dRandom=dblrand();
                EV<<"random value----m_dRandom="<<m_dRandom<<endl;
                if(m_dRandom> PACKET_LOSS_RATE)//�ɹ�����
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

//����req,����host�Ĵ��ڣ�������û�����ݣ�ap�����host����ʱ϶���̶�����
void TdmaHostMac::sendReqPacket()
{
    //�½�һ�����ݰ�req
    HostReqPkOfTDMA *pk=new HostReqPkOfTDMA();
    pk->setKind(PacketKind_Host_Request);

    //��ȡ���ڵ�hostָ��
    cModule *mdParent=getParentModule();
    //����host��id
    int nParentId=mdParent->getId();
    pk->setNHostId(nParentId);
    //����host��·��
    pk->setStrHostPath(mdParent->getFullPath().c_str());
    //���ýڵ��λ������
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

//��ȡ����ap�ķ�����Ϣ
void TdmaHostMac::getApAllocation(ApAllocationPkOfTDMA *pk)
{
    m_nTransmitSlotIndex=pk->getNIndex();
    m_nTransmitSlotNum=pk->getNSlotNum();

    EV_DEBUG<<"Host gets allocation infomation from Ap:"<<endl;
    EV_DEBUG<<"slot index:"<< m_nTransmitSlotIndex<<endl;
    EV_DEBUG<<"slot num:"<< m_nTransmitSlotNum<<endl;

    return;
}

//��������
//��ȡ��ǰλ��
Coord TdmaHostMac::getCurrentPosition()
{
    cModule *mdParent=getParentModule();
    cModule *mdMobility=mdParent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    return mdMovingMobility->getCurrentPosition();
}
//��ȡAPλ��
Coord TdmaHostMac::getApPosition()
{
    cModule *mdMobilityOfAp=m_mdAp->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
    return mdMovingMobilityOfAp->getCurrentPosition();
}
//�����AP�ľ���
double TdmaHostMac::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdAp=getApPosition();
    Coord cdDistance=cdHost-cdAp;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
}
//����ʱ϶���ȣ��������ߵ紫�������ʱ϶��
int TdmaHostMac::getPropagationSlot()
{
    double dDistance=getDistance();
    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_stSlotLength);

}
//���þ����־�����ݾ���Զ��������1~10
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


