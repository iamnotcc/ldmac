/*
 * AlohaApMac.cc
 *
 *  Created on: 2017年3月17日
 *      Author: wh
 */
#include "nic/aloha/AlohaApMac.h"
#include "inet/common/PacketKind.h"

namespace inet
{
Define_Module(AlohaApMac);

AlohaApMac::AlohaApMac()
{
    m_selfMsg=nullptr;
}

AlohaApMac::~AlohaApMac()
{
    cancelAndDelete(m_selfMsg);
}

void AlohaApMac::initialize()
{
    //初始化参数
    m_slotLength=par("slotLength");

    m_ssPkCount=registerSignal("pkCount");

    //自消息初始化
    m_selfMsg=new cMessage("selfMsg");
    scheduleAt(0+m_slotLength/2,m_selfMsg);
}

void AlohaApMac::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        scheduleAt(simTime()+m_slotLength,m_selfMsg);
        receiveData();
    }
    else
    {
        if(msg->getKind()==PacketKind_Host_Data)
        {
            EV_DEBUG<<"ALOHA: a packet:"<<msg->getName()<<" arrived at ap"<<endl;
            m_pkNumInSlot++;
            delete msg;
        }
        else
        {
            throw cRuntimeError("Ap received a error type msg.");
        }
    }
}
void AlohaApMac::receiveData()
{
    if(m_pkNumInSlot==1)
    {
        emit(m_ssPkCount,1l);
        EV_DEBUG<<"Ap received a packet successfully."<<endl;
    }
    else
    {
        EV_DEBUG<<m_pkNumInSlot<<" packets arrived. FAILURE!"<<endl;
    }
    m_pkNumInSlot=0;
}
}

