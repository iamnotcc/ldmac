/*
 * TdmaApMac.h
 *
 *  Created on: 2017��3��15��
 *      Author: wh
 */

#ifndef INET_NIC_TDMA_TDMAAPMAC_H_
#define INET_NIC_TDMA_TDMAAPMAC_H_

#include "inet/common/INETDefs.h"
#include "inet/nic/tdma/TdmaReq_m.h"
#include "inet/nic/tdma/TdmaAck_m.h"
using namespace std;


namespace inet
{
class TdmaApMac: public cSimpleModule
{
private:
    //����
    int m_reqSlotNum;
    int m_slotNum;
    simtime_t m_slotLength;

    //����Ϣ
    cMessage *m_selfMsg;

    // ���У�����req
    //cQueue<TdmaReq *> m_reqQueue;
    cQueue m_reqQueue;

    //ͳ����
    simsignal_t m_ssPkCount;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendAck();
    void outputQueue();

public:
    TdmaApMac();
    ~TdmaApMac();
};
}



#endif /* INET_NIC_TDMA_TDMAAPMAC_H_ */
