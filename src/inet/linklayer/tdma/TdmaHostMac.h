/*
 * TdmaHostMac.h
 *
 *  Created on: 2017��3��8��
 *      Author: wh
 */

#ifndef INET_LINKLAYER_TDMA_TdmaHostMac_H_
#define INET_LINKLAYER_TDMA_TdmaHostMac_H_
/*
#include "inet/common/INETDefs.h"
#include "linklayer/common/LinklayerCommon.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/linklayer/tdma/HostReqPkOfTDMA_m.h"
#include "inet/linklayer/tdma/ApAllocationPkOfTDMA_m.h"
#include "inet/mobility/contract/IMobility.h"


namespace inet
{
class TdmaHostMac: public cSimpleModule
{
private:
    //����
    double m_dTxRate;
    int m_nSlotNum;
    simtime_t m_stSlotLength;
    cPar *m_nReqLength;

    //apģ��
    cModule *m_mdAp;

    //���У���������app�����ݰ�
    cQueue m_qAppQueue;
    cQueue m_qReTransmitQueue;

    //����Ϣ
    cMessage *m_msgSelfReq;
    cMessage *m_msgSelfData;

    //������Լ��Ŀ�ʼʱ϶������ʱ϶����
    int m_nTransmitSlotIndex;
    int m_nTransmitSlotNum;

    int m_nWasteSlotNum;

    //������������Ƿ񶪰�
    double m_dRandom;

    simsignal_t m_ssQueueTime;
    simtime_t m_stQueueTime;

    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSendPkCount;

    //��ĳ�������ʱ��
    simtime_t m_stTime;
    simsignal_t m_ssTime0;
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


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendReqPacket();
    void sendDataPacket();
    void getApAllocation(ApAllocationPkOfTDMA *pk);

    //���þ����־�����ݾ���Զ��������1~10
    int setDistanceFlag();

    //�������������ߵ�ǰλ�ã���ȡapλ�ã�������룬����ʱ϶
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlot();


public:
    TdmaHostMac();
    ~TdmaHostMac();
};
}

*/

#endif /* INET_LINKLAYER_TDMA_TdmaHostMac_H_ */
