/*
 * AlohaHostMac.cc
 *
 *  Created on: 2017��3��17��
 *      Author: wh
 */

#include "nic/aloha/AlohaHostMac.h"
#include "inet/common/PacketKind.h"
#include "inet/nic/common/NicCommon.h"
#include "inet/mobility/contract/IMobility.h"

namespace inet
{
Define_Module(AlohaHostMac);

AlohaHostMac::AlohaHostMac()
{
    m_selfMsgData=nullptr;
}

AlohaHostMac::~AlohaHostMac()
{
    cancelAndDelete(m_selfMsgData);
}

void AlohaHostMac::initialize()
{
    //��ȡapģ��ָ��
    m_ap=getModuleByPath("ap");
    if(!m_ap)
    {
        throw cRuntimeError("Aloha: AP not found");
    }
    else
    {
        EV_DEBUG<<"Aloha: found ap: "<<m_ap->getFullName()<<endl;
    }

    //��ȡ��ģ��
    m_parent=getParentModule();
    if(!m_parent)
    {
        throw cRuntimeError("ALOHA: parent module not found");
    }

    //��ʼ������
    m_txRate=par("txRate");
    m_slotLength=par("slotLength");
    m_communicationRange=par("communicationRange");

    //ע���ź���
    //�Ŷӵȴ�ʱ��
    m_ssQueueTime=registerSignal("queueTime");
    m_queuetime=0;
    //�����������ݰ�����
    m_ssDiscardPkCount=registerSignal("discardPkCount");
    //�ܹ����͵����ݰ�����
    m_ssSentPkCount=registerSignal("sentPkCount");

    //����Ϣ��ʼ��
    m_selfMsgData=new cMessage("SlefMsg-Data");
    scheduleAt(0,m_selfMsgData);
}

void AlohaHostMac::handleMessage(cMessage *msg)
{
    //����Ϣ
    if(msg->isSelfMessage())
    {
        scheduleAt(simTime()+m_slotLength,m_selfMsgData);
        //TODO:�ж��Ƿ���ͨ�ŷ�Χ��
        if(getDistance()<m_communicationRange)
        {
           sendData();
        }
        else
        {
            EV_DEBUG<<"ALOHA:Host is out of ap' communication range."<<endl;
            //���Ӧ�����ݰ�����
            m_appQueue.clear();
        }
    }
    //������Ϣ
    else
    {
        //Ӧ�ò���Ϣ
        if(msg->getKind()==PacketKind_Application)
        {
            if(m_appQueue.getLength()==QUEUE_CAPACITY)
            {
                emit(m_ssDiscardPkCount,1l);
                delete msg;
                EV_DEBUG<<"ALOHA: appQueue is full, new arriving packet is discard."<<endl;
            }
            else
            {
                msg->setArrivalTime(simTime());
                m_appQueue.insert(msg);
                EV_DEBUG<<"ALOHA: A new application packet arrived. The length of queue now is "<<m_appQueue.getLength()<<endl;
            }
        }
        else
        {
            throw cRuntimeError("Error msg type.");
        }
    }
}

void AlohaHostMac::sendData()
{
    if(!m_appQueue.isEmpty())
    {
        cPacket *pk=dynamic_cast<cPacket *>(m_appQueue.pop());
        pk->setKind(PacketKind_Host_Data);
        m_queuetime=simTime()-pk->getArrivalTime();
        emit(m_ssQueueTime,m_queuetime);
        emit(m_ssSentPkCount,1l);
        simtime_t stPropagation=m_slotLength*getPropagationSlot();
        EV_DEBUG<<m_parent->getFullName()<<" send a packet "<< pk->getFullName()<<" to Ap."<<endl;
        sendDirect(pk,stPropagation,0,m_ap->gate("in"));
    }
    else
    {
        EV_DEBUG<<"ALOHA: m_appQueue is empty, no data packet is to send."<<endl;
    }
}

//��������
//��ȡ��ǰλ��
Coord AlohaHostMac::getCurrentPosition()
{
    cModule *mdMobility=m_parent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    return mdMovingMobility->getCurrentPosition();
}
//��ȡAPλ��
Coord AlohaHostMac::getApPosition()
{
    cModule *mdMobilityOfAp=m_ap->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
    return mdMovingMobilityOfAp->getCurrentPosition();
}
//�����AP�ľ���
double AlohaHostMac::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdAp=getApPosition();
    Coord cdDistance=cdHost-cdAp;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
}
//����ʱ϶���ȣ��������ߵ紫�������ʱ϶��
int AlohaHostMac::getPropagationSlot()
{
    double dDistance=getDistance();
    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_slotLength);
}
}


