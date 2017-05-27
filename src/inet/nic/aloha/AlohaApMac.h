/*
 * AlohaApMac.h
 *
 *  Created on: 2017��3��17��
 *      Author: wh
 */

#ifndef INET_NIC_ALOHA_ALOHAAPMAC_H_
#define INET_NIC_ALOHA_ALOHAAPMAC_H_

#include "common/INETDefs.h"
#include "common/PacketKind.h"

namespace inet
{
class AlohaApMac:public cSimpleModule
{
private:
    //��������ini��ȡ
    simtime_t m_slotLength;

    int m_pkNumInSlot=0;
    //����Ϣ
    cMessage *m_selfMsg;

    //ͳ����
    simsignal_t m_ssPkCount;

public:
    AlohaApMac();
    ~AlohaApMac();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void receiveData();
};
}




#endif /* INET_NIC_ALOHA_ALOHAAPMAC_H_ */
