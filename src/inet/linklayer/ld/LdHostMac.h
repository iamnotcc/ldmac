/*
 * ldHostMac.h
 *
 *  Created on: 2016��6��14��
 *      Author: Administrator
 */

#ifndef SRC_LINKLAYER_LD_LDHOSTMAC_H_
#define SRC_LINKLAYER_LD_LDHOSTMAC_H_

#include "inet/common/INETDefs.h"
#include "linklayer/ld/HostReqPacket_m.h"
#include "linklayer/ld/ApAllocationPacket_m.h"
#include "common/PacketKind.h"
#include <vector>
#include "linklayer/common/LinklayerCommon.h"
using namespace std;

namespace inet
{
////�ṹ�壬��������AP����Ϣ������ʱ϶������Լ�ʱ϶����
//struct HostTransmitInfo
//{
//    int nIndex;
//    int nSlotNum;
//};
//
//class LdHostMac: public cSimpleModule
//{
//private:
//    //��������ned�ļ��ж���
//    simtime_t m_stSlotLength;
//    int m_nRequestSlotNum;
//    int m_nAllocateSlotNum;
//    int m_nTransmitSlotNum;
//    double m_dTxRate;
//    cPar *m_nReqPktLength;
//
//    //ldApģ��
//    cModule *m_mdAp;
//
//    //����Ϣ������request��data����Ϣ
//    cMessage *m_msgSelfReq;
//    cMessage *m_msgSelfData;
//
//    //���У�����Ӧ�ò����ݰ�
//    cQueue m_qAppPacketList;
//    cQueue m_qReTransmitQueue;
//
//    //������������Ƿ񶪰�
//    double m_dRandom;
//
//    //����������¼��ǰ�����slot���ж��ٸ�
//    int m_nSlotLeftCounter;
//
//    //host���ݴ�����Ϣ������ap
//    HostTransmitInfo m_hostTransmitInfo;
//
//    //�ź�����ָʾ�����İ�����
//    simsignal_t m_ssDiscardPkCount;
//    //�ź�����ָʾ�ɹ����͵İ�����
//    simsignal_t m_ssSendPkCount;
//
//    //�Ŷ�ʱ��
//    simtime_t m_stQueueTime;
//    //�ź�����ָʾÿ���ɹ����͵����ݰ��ȴ���ʱ��
//    simsignal_t m_ssQueueTime;
//
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
//protected:
//    //��������ʼ��
//    virtual void initialize() override;
//    //���������������Ϣ
//    virtual void handleMessage(cMessage *msg) override;
//    //����������host��req��
//    HostReqPacket *generateReqPacket();
//    //��������AP�Ĺ㲥���л�ȡhost�Ĵ�����Ϣ
//    HostTransmitInfo getHostTransmitInfo(ApAllocationPacket *pk);
//    //����������req��
//    void sendReqPacket(HostReqPacket *pk);
//    //�������������ݰ�
//    void sendDataPacket(HostTransmitInfo structTransmitInfo);
//
//
//    //��������
//    //��������ȡ��ǰλ��
//    Coord getCurrentPosition();
//    //��������ȡAP��λ��
//    Coord getApPosition();
//    //����������host��AP֮��ľ���
//    double getDistance();
//    //������������ת��Ϊʱ϶����
//    int getPropagationSlotNum(double dDistance,simtime_t stSlotLength);
//    //���þ����־�����ݾ���Զ��������1~10
//    int setDistanceFlag();
//public:
//    //���캯������������
//    LdHostMac();
//    virtual ~LdHostMac();
//
//};
}



#endif /* SRC_LINKLAYER_LD_LDHOSTMAC_H_ */
