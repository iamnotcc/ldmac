/*
 * TdmaHostMac.h
 *
 *  Created on: 2017��3��15��
 *      Author: wh
 */

#ifndef INET_NIC_TDMA_TDMAHOSTMAC_H_
#define INET_NIC_TDMA_TDMAHOSTMAC_H_

#include "inet/common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/nic/tdma/TdmaReq_m.h"
#include "inet/nic/tdma/TdmaAck_m.h"


namespace inet
{
class TdmaHostMac: public cSimpleModule
{
private:
    //��ini��ȡ�Ĳ���
    double m_txRate;
    double m_communicationRange;
    simtime_t m_slotLength;
    int m_slotNum;
    int m_reqSlotNum;

    //��������������ack����Ϣ
    int m_dataSlotNum;
    int m_dataSlotIndex;
    simtime_t m_dataTransmitTime;
    //apģ��ָ��
    cModule *m_ap;
    //��ģ��
    cModule *m_parent;

    //Ӧ�ò����ݶ���
    cQueue m_appQueue;

    //ͳ����
    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSentPkCount;
    simsignal_t m_ssQueueTime;
    simtime_t m_queuetime;

    //����Ϣ
    cMessage *m_selfMsgReq;
    cMessage *m_selfMsgData;

protected:
    //��ʼ������
    virtual void initialize() override;

    //��Ϣ������
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

public:
    TdmaHostMac();
    ~TdmaHostMac();
};
}




#endif /* INET_NIC_TDMA_TDMAHOSTMAC_H_ */
