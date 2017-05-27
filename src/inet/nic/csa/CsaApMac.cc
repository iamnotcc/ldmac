/*
 * CsaApMac.cc
 *
 *  Created on: 2017��4��15��
 *      Author: LiuXinyun
 */

#include "inet/nic/csa/CsaApMac.h"

namespace inet
{
Define_Module(CsaApMac);

CsaApMac::CsaApMac()
{

}

CsaApMac::~CsaApMac()
{

}

void CsaApMac::initialize()
{
    initParameters();
    initStatistic();
}

void CsaApMac::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        handleSelfMsg(msg);
    }
    else
    {
        handleNonSelfMsg(msg);
    }
}

//��ʼ������
void CsaApMac::initParameters()
{
    m_slotLength=par("slotLength");
    m_slotNum=par("slotNum");
    EV_DEBUG<<"Parameter values:"<<endl;
    EV_DEBUG<<"******slot length: "<<m_slotLength<<endl;
    EV_DEBUG<<"******slot number: "<<m_slotNum<<endl;

    m_selfMsgHandleHostData=new cMessage("selfMsgHandleHostData");
    scheduleAt(0,m_selfMsgHandleHostData);
}
//��ʼ��ͳ�Ʋ���
void CsaApMac::initStatistic()
{

}

//��������Ϣ
void CsaApMac::handleSelfMsg(cMessage *msg)
{
    if(msg==m_selfMsgHandleHostData)
    {
        scheduleAt(simTime()+m_slotNum*m_slotLength,m_selfMsgHandleHostData);
        EV_DEBUG<<msg->getFullName()<<" will be scheduled at time: "<<(simTime()+m_slotNum*m_slotLength)<<endl;
        if(vecHostPks.size()!=0)
        {
            handleHostData();
        }

    }
}

void CsaApMac::handleHostData()
{
    EV_DEBUG<<"vecHostPks's size: "<<vecHostPks.size()<<endl;
    for(int i=0;i<vecHostPks.size();i++)
    {
        EV_DEBUG<<vecHostPks[i]->getFullName()<<": "<<vecHostPks[i]->getTimestamp()<<endl;
    }

    vector<CsaHostPk *> cleanDataVec;
    int cleanPks=1;
    simtime_t currentTimeStamp;
    for(int itertimes=0;itertimes<vecHostPks.size();itertimes++)
    {
        EV_DEBUG<<"iteration times: "<<itertimes<<endl;
        for(int i=0;i<vecHostPks.size();i++)
        {

            if(vecHostPks[i]->getIsRecovery()==false)
            {
                EV_DEBUG<<"The ["<<i<<"] packet is not recovery."<<endl;
                currentTimeStamp=vecHostPks[i]->getTimestamp();
                for(int j=i+1;j<vecHostPks.size();j++)
                {
                    if(vecHostPks[j]->getTimestamp()==currentTimeStamp)
                    {
                        cleanPks++;
                        EV_DEBUG<<"cleanpks="<<cleanPks<<endl;
                    }
                }
                if(cleanPks==1)
                {

                    for(int k=0;k<vecHostPks.size();k++)
                    {
                        if(vecHostPks[k]->getPkId()==vecHostPks[i]->getPkId())
                        {
                            EV_DEBUG<<i<<"hostid="<<vecHostPks[i]->getPkId()<<endl;
                            EV_DEBUG<<k<<"hostid="<<vecHostPks[k]->getHostId()<<endl;
                            vecHostPks[k]->setIsRecovery(true);
                            EV_DEBUG<<"The ["<<k<<"] packet is recoverying."<<endl;
                        }
                    }
                    cleanDataVec.push_back(vecHostPks[i]);

                }
                else
                {
                    cleanPks=1;
                }
            }
        }
    }
    EV_DEBUG<<"Output pks: "<<endl;
    EV_DEBUG<<"The size of cleandatavec is: "<<cleanDataVec.size()<<endl;
    for(int i=0;i<cleanDataVec.size();i++)
    {
        EV_DEBUG<<"["<<i<<"]:"<<cleanDataVec[i]->getFullName()<<endl;
    }
    vecHostPks.clear();
}



//���������Ϣ
void CsaApMac::handleNonSelfMsg(cMessage *msg)
{
    switch(msg->getKind())
    {
    //����host��data
    case PacketKind_Host_Data:
    {
        CsaHostPk *pk=dynamic_cast<CsaHostPk *>(msg);
        pk->setTimestamp();

        vecHostPks.push_back(pk);
        EV_DEBUG<<"Ap received a packet: "<<pk->getFullName()<<endl;

        break;
    }
    default:
    {
        EV_DEBUG<<"Ap received a wrong type message."<<endl;
        break;
    }

    }
}


}


