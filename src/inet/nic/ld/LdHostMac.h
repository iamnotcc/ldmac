/*
 * LdHostMac.h
 *
 *  Created on: 2017��3��23��
 *      Author: wh
 */

#ifndef INET_NIC_LD_LDHOSTMAC_H_
#define INET_NIC_LD_LDHOSTMAC_H_
#define MAX_REQUEST_SLOTS 2000
#include "inet/common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/mobility/contract/IMobility.h"

namespace inet
{
class LdHostMac: public cSimpleModule
{
private:

    //��������ini�ļ���ȡ
    double m_txRate=0;
    int m_slotNum=0;
    int m_reqSlotNum=0;
    simtime_t m_slotLength=0;
    int m_reqLength=0;
    double m_communicationRange=0;

    bool m_isSendReq=true;
    int m_reqCounter=0;

    int m_dataSlotIndex=-1;
    int m_dataSlotNum=-1;
    simtime_t m_dataTransmitTime;

    //Apģ��
    cModule *m_ap;
    //��ģ��
    cModule *m_parent;

    //���У�����Ӧ�ò����ݰ�
    cQueue m_appQueue;

    //ͳ����
    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSentPkCount;
    simsignal_t m_ssQueueTime;
    simtime_t m_queuetime;
    //��ĳ�������ʱ��
    simtime_t m_stTime;
    simsignal_t m_ssTotalTime;
    simsignal_t m_ssTime1;
    simsignal_t m_ssTime2;
    simsignal_t m_ssTime3;
    simsignal_t m_ssTime4;
    simsignal_t m_ssTime5;
    simsignal_t m_ssTime6;
    simsignal_t m_ssTime7;
    simsignal_t m_ssTime8;
    simsignal_t m_ssTime9;
    simsignal_t m_ssTime10;

    //����Ϣ
    cMessage *m_selfMsgReq;
    cMessage *m_selfMsgData;


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    //����req
    void sendReq();
    //����data
    void sendData();
    //�������������ߵ�ǰλ�ã���ȡapλ�ã�������룬����ʱ϶
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlot();
    //���þ����־�����ݾ���Զ��������1~10
    int setDistanceFlag();

public:
    //���캯������������
    LdHostMac();
    ~LdHostMac();

};
}



#endif /* INET_NIC_LD_LDHOSTMAC_H_ */
