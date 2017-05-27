/*
 * BurstGenerator.cc
 *
 *  Created on: 2016��11��23��
 *      Author: wh
 */

#include "BurstGenerator.h"
#include "common/PacketKind.h"

namespace inet
{
Define_Module(BurstGenerator);

BurstGenerator::BurstGenerator()
{
    //��ʼ��
    m_stBurstInterval=nullptr;
    m_nBurstNum=nullptr;
    m_nPacketLength=nullptr;

    m_msgTimer=nullptr;
}

BurstGenerator::~BurstGenerator()
{
    //ɾ������
    cancelAndDelete(m_msgTimer);
}

void BurstGenerator::initialize()
{
    //��ini�ļ���ȡ����
    m_stStartTime=par("startTime");
    m_stBurstInterval=&par("burstInterval");
    m_nBurstNum=&par("burstNum");
    m_nPacketLength=&par("packetLength");

    //ʵ����һ������Ϣ
    m_msgTimer=new cMessage("sendTimer");

    //ע���ź���
    m_ssAppPkCount=registerSignal("appPkCount");
    m_ssErrorCount=registerSignal("errorCount");

    m_pkNo=0;

    //��ʼ��burst����
    scheduleNextBurst(-1);
}

void BurstGenerator::handleMessage(cMessage *msg)
{
    if(msg==m_msgTimer)
    {
        sendBurst();
        scheduleNextBurst(simTime());
    }
}

void BurstGenerator::scheduleNextBurst(simtime_t stPrevious)
{
    //stPrevious����һ������burst��ʱ��
    //stNext:��һ������burst��ʱ��
    simtime_t stNext;

    double dBurstInterval=m_stBurstInterval->doubleValue();
    //���֮ǰ��û���ɹ����ݣ�stPrevious=-1������ô��ʼʱ��ȡ��ǰʱ�䣨0s���������õĲ���m_stStartTime
    if(stPrevious==-1)
    {
        stNext=simTime()<=m_stStartTime ? m_stStartTime : simTime();
        stNext=stNext+dBurstInterval;
        EV_DEBUG<<"stNext="<<stNext<<endl;
    }
    else
    {
        //��ε�ʱ��=��һ��ʱ��+ʱ����
        stNext=stPrevious+dBurstInterval;

        //�쳣�������һ��ʱ������ڵ�ʱ�仹ǰ����������ǲ���������
        if(stNext<simTime())
        {
            stNext=simTime();
            EV_ERROR<<"stNext< simTime()"<<endl;
            emit(m_ssErrorCount,1l);
        }
        EV<<"stPrevious="<<stPrevious<<", stInterval="<<dBurstInterval<<", stNext="<<stNext<<endl;

    }
    scheduleAt(stNext,m_msgTimer);
    EV<<"schedule next burst at "<<stNext<<endl;
}

void BurstGenerator::sendBurst()
{
    long lnBurstNum=m_nBurstNum->longValue();

    for(int i=0; i<lnBurstNum;i++)
    {
        m_pkNo++;
        char pkName[40];
        sprintf(pkName,"appData-%d",m_pkNo);
        cPacket *pk=new cPacket(pkName);
        pk->setBitLength(m_nPacketLength->longValue());
        pk->setKind(PacketKind_Application);
        emit(m_ssAppPkCount,1l);
        send(pk,"out");
        EV_DEBUG<<"Sent a packet "<< pk->getName() <<" at "<<pk->getSendingTime()<<endl;

     }
}

}


