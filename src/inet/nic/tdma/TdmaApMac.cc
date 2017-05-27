/*
 * TdmaApMac.cc
 *
 *  Created on: 2017��3��15��
 *      Author: wh
 */
#include "inet/nic/tdma/TdmaApMac.h"
#include "inet/common/PacketKind.h"

namespace inet
{
Define_Module(TdmaApMac);


TdmaApMac::TdmaApMac()
{
    m_selfMsg=nullptr;
}

TdmaApMac::~TdmaApMac()
{
    cancelAndDelete(m_selfMsg);
}

void TdmaApMac::initialize()
{
    //��ʼ������
    m_slotNum=par("slotNum");
    m_slotLength=par("slotLength");
    m_reqSlotNum=par("reqSlotNum");

    m_ssPkCount=registerSignal("pkCount");

    //��ʼ������Ϣ
    m_selfMsg=new cMessage("selfMsg");
    //�ھ���ʱ϶���������ʱ϶����
    scheduleAt(0+m_slotLength*(m_reqSlotNum-2),m_selfMsg);
}


void TdmaApMac::handleMessage(cMessage *msg)
{
    //���������Ϣ
    if(msg->isSelfMessage())
    {
        sendAck();
        m_reqQueue.clear();
        scheduleAt(simTime()+m_slotLength*m_slotNum,m_selfMsg);
    }
    //��������Ϣ
    else
    {
        //req��Ϣ
        if(msg->getKind()==PacketKind_Host_Request)
        {
            EV_DEBUG<<"Ap received a req from "<<msg->getSenderModule()->getFullPath()<<" at "<<simTime() <<endl;
            //TODO:��һ�ֻ�������֤������data section�յ�req
            //��msg������еȴ�����
            m_reqQueue.insert(msg);
        }
        else
        {
            if(msg->getKind()==PacketKind_Host_Data)
            {
                emit(m_ssPkCount,1l);
                EV_DEBUG<<"Ap received a packet:"<<msg->getName()<<endl;
                delete msg;
            }
            else
            {
                throw cRuntimeError("Ap received a error type msg.");
            }
        }
    }
}

void TdmaApMac::sendAck()
{
    EV_DEBUG<<"Ap is broadcasting allocation information..."<<endl;
    outputQueue();

    int nHostNum=m_reqQueue.getLength();
    EV_DEBUG<<"There are "<<nHostNum<<" hosts in reqQueue."<<endl;
    if(nHostNum!=0)
    {
        int nAverageSlotNum=(m_slotNum-m_reqSlotNum)/nHostNum;
        int nLeftSlotNum=(m_slotNum-m_reqSlotNum)%nHostNum;
        EV_DEBUG<<"Average slot num: "<<nAverageSlotNum<<",and left slot num: "<<nLeftSlotNum<<endl;

        int nIndex=m_reqSlotNum;
        int nSlotNum=0;
        cModule *mdHost;
        for(int i=0;i<nHostNum;i++)
        {
            TdmaAck *pk=new TdmaAck();
            pk->setKind(PacketKind_Ap_ACK);
            pk->setNIndex(nIndex);
            if(i<nLeftSlotNum)
            {
                nSlotNum=nAverageSlotNum+1;
            }
            else
            {
                nSlotNum=nAverageSlotNum;
            }
            pk->setNSlotNum(nSlotNum);
            EV_DEBUG<<i<<" of "<<nHostNum<<" ---- index: "<<nIndex<<" and slot num: "<<nSlotNum<<endl;
            nIndex=nIndex+nSlotNum;

            mdHost=getModuleByPath((dynamic_cast<TdmaReq *>(m_reqQueue.get(i)))->getStrHostPath());
            EV_DEBUG<<"Allocation packet is sending to "<<mdHost->getFullName()<<endl;
            sendDirect(pk,0,0,mdHost->gate("in"));
        }

    }


}

void TdmaApMac::outputQueue()
{
    EV_DEBUG<<"Elements in m_reqQueue:"<<endl;
    for(int i=0;i<m_reqQueue.getLength();i++)
    {
        EV_DEBUG<<i<<" of "<<m_reqQueue.getLength()<<" : "<<(dynamic_cast<TdmaReq *>(m_reqQueue.get(i)))->getStrHostPath()<<endl;
    }
}
}



