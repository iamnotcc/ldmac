/*
 * AlohaHostMac.h
 *
 *  Created on: 2016��6��1��
 *      Author: Administrator
 */

#ifndef SRC_LINKLAYER_ALOHA_ALOHAHOSTMAC_H_
#define SRC_LINKLAYER_ALOHA_ALOHAHOSTMAC_H_
#include "common/INETDefs.h"
#include "common/geometry/common/Coord.h"
#include "common/ModuleAccess.h"
#include "Mobility/contract/IMobility.h"
#include "linklayer/common/LinklayerCommon.h"
#include "common/PacketKind.h"


namespace inet
{
class AlohaHostMac:public cSimpleModule
{
//private:
//
//    //����
//    //��������
//    double m_dTxRate;
//    //ʱ϶���ȣ����Ϊ0����Ϊpure aloha
//    simtime_t m_stSlotTime;
//    //bool������ָ���Ƿ���slotted
//    bool m_bIsSlotted;
//    //bool������ָ���Ƿ����
//    bool m_bIsIDLE;
//    //apģ��ָ��
//    cModule *m_mdAp;
//
//    //���У���������Ӧ�ò�����ݰ�
//    cQueue m_qPacketQueue;
//
//    //��Ϣ��
//    //��������
//    cMessage *m_msgEndTxEvent;
//    //Ӧ�ò�����Ϣ����
//    cMessage *m_msgPkArrival;
//    //����Ϣ��ÿ��һ��ʱ��㱨�Լ���λ��
//    cMessage *m_msgSelf;
//
//    //���¶���ͳ����
//    simsignal_t m_ssQueueTime;
//    simtime_t m_stQueueTime;
//    simsignal_t m_ssDiscardPkCount;
//    simsignal_t m_ssSendPkCount;
//    //��ĳ�������ʱ��
//    simtime_t m_stTime;
//    simsignal_t m_ssTime0;
//    simsignal_t m_ssTime1;
//    simsignal_t m_ssTime2;
//    simsignal_t m_ssTime3;
//    simsignal_t m_ssTime4;
//    simsignal_t m_ssTime5;
//    simsignal_t m_ssTime6;
//    simsignal_t m_ssTime7;
//    simsignal_t m_ssTime8;
//    simsignal_t m_ssTime9;
//    simsignal_t m_ssTime10;
//
//public:
//    AlohaHostMac();
//    virtual ~AlohaHostMac();
//
//protected:
//    virtual void initialize() override;
//    virtual void handleMessage(cMessage *msg) override;
//    simtime_t getTransmissionTime(simtime_t t);
//    double getDistance();
//    Coord getCurrentPosition();
//    Coord getApPosition();
//    //���þ����־�����ݾ���Զ��������1~10
//    int setDistanceFlag();

};
}



#endif /* SRC_LINKLAYER_ALOHA_ALOHAHOSTMAC_H_ */
