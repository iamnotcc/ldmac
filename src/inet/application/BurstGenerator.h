/*
 * BurstGenerator.h
 *
 *  Created on: 2016年11月23日
 *      Author: wh
 */

#ifndef APPLICATIONS_BURSTGENERATOR_H_
#define APPLICATIONS_BURSTGENERATOR_H_

#include "inet/common/INETDefs.h"
namespace inet
{
class BurstGenerator: public cSimpleModule
{
private:
    //参数
    //开始生成数据包的时间
    simtime_t m_stStartTime;
    //批量数据包生成间隔
    cPar *m_stBurstInterval;
    //每次生成的数据包个数
    cPar *m_nBurstNum;
    //每个数据包的长度
    cPar *m_nPacketLength;

    //自消息
    cMessage *m_msgTimer;

    //信号量：统计数据包个数,统计异常情况
    simsignal_t m_ssAppPkCount;
    simsignal_t m_ssErrorCount;

    long m_pkNo;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
public:
    BurstGenerator();
    virtual ~BurstGenerator();
    //把数据包发送出去，到MAC层
    void sendBurst();
    //调度下一个burst的时间
    void scheduleNextBurst(simtime_t stPrevious);
};
}



#endif /* APPLICATIONS_BURSTGENERATOR_H_ */
