/*
 * BurstGenerator.cc
 *
 *  Created on: 2016年11月23日
 *      Author: wh
 */

#include "BurstGenerator.h"
#include "common/PacketKind.h"

namespace inet
{
Define_Module(BurstGenerator);

BurstGenerator::BurstGenerator()
{
    //初始化
    m_stBurstInterval=nullptr;
    m_nBurstNum=nullptr;
    m_nPacketLength=nullptr;

    m_msgTimer=nullptr;
}

BurstGenerator::~BurstGenerator()
{
    //删除变量
    cancelAndDelete(m_msgTimer);
}

void BurstGenerator::initialize()
{
    //从ini文件获取参数
    m_stStartTime=par("startTime");
    m_stBurstInterval=&par("burstInterval");
    m_nBurstNum=&par("burstNum");
    m_nPacketLength=&par("packetLength");

    //实例化一个自消息
    m_msgTimer=new cMessage("sendTimer");

    //注册信号量
    m_ssAppPkCount=registerSignal("appPkCount");
    m_ssErrorCount=registerSignal("errorCount");

    m_pkNo=0;

    //初始化burst调度
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
    //stPrevious：上一次生成burst的时间
    //stNext:这一次生成burst的时间
    simtime_t stNext;

    double dBurstInterval=m_stBurstInterval->doubleValue();
    //如果之前还没生成过数据（stPrevious=-1），那么开始时间取当前时间（0s）或者设置的参数m_stStartTime
    if(stPrevious==-1)
    {
        stNext=simTime()<=m_stStartTime ? m_stStartTime : simTime();
        stNext=stNext+dBurstInterval;
        EV_DEBUG<<"stNext="<<stNext<<endl;
    }
    else
    {
        //这次的时间=上一次时间+时间间隔
        stNext=stPrevious+dBurstInterval;

        //异常情况，下一次时间比现在的时间还前，正常情况是不会这样的
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


