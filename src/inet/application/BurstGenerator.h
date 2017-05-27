/*
 * BurstGenerator.h
 *
 *  Created on: 2016��11��23��
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
    //����
    //��ʼ�������ݰ���ʱ��
    simtime_t m_stStartTime;
    //�������ݰ����ɼ��
    cPar *m_stBurstInterval;
    //ÿ�����ɵ����ݰ�����
    cPar *m_nBurstNum;
    //ÿ�����ݰ��ĳ���
    cPar *m_nPacketLength;

    //����Ϣ
    cMessage *m_msgTimer;

    //�ź�����ͳ�����ݰ�����,ͳ���쳣���
    simsignal_t m_ssAppPkCount;
    simsignal_t m_ssErrorCount;

    long m_pkNo;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
public:
    BurstGenerator();
    virtual ~BurstGenerator();
    //�����ݰ����ͳ�ȥ����MAC��
    void sendBurst();
    //������һ��burst��ʱ��
    void scheduleNextBurst(simtime_t stPrevious);
};
}



#endif /* APPLICATIONS_BURSTGENERATOR_H_ */
