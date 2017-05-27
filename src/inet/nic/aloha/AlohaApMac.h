/*
 * AlohaApMac.h
 *
 *  Created on: 2017年3月17日
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
    //参数，从ini获取
    simtime_t m_slotLength;

    int m_pkNumInSlot=0;
    //自消息
    cMessage *m_selfMsg;

    //统计量
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
