/*
 * AlohaApMac.h
 *
 *  Created on: 2016年6月7日
 *      Author: Administrator
 */

#ifndef SRC_LINKLAYER_ALOHA_ALOHAAPMAC_H_
#define SRC_LINKLAYER_ALOHA_ALOHAAPMAC_H_

#include "common/INETDefs.h"
#include "common/PacketKind.h"

namespace inet
{
class AlohaApMac:public cSimpleModule
{
//private:
//    bool m_bChannelBusy;
//    cMessage *m_msgSelfEndRx;
//
//    simtime_t m_stRecvStartTime;
//    long m_lCurrentCollisionNumFrames;
//
//    enum {IDLE=0,TRANSMISSION=1,COLLISION=2};
//    simsignal_t m_ssChannelStateSignal;
//
//    cPacket *m_pkTemp;
//
//    //信号量，统计收到的数据包数，以及各个距离档收到的数据包
//    simsignal_t m_ssPkCount;
//    simsignal_t m_ssPkCount1;
//    simsignal_t m_ssPkCount2;
//    simsignal_t m_ssPkCount3;
//    simsignal_t m_ssPkCount4;
//    simsignal_t m_ssPkCount5;
//    simsignal_t m_ssPkCount6;
//    simsignal_t m_ssPkCount7;
//    simsignal_t m_ssPkCount8;
//    simsignal_t m_ssPkCount9;
//    simsignal_t m_ssPkCount10;
//
//public:
//    AlohaApMac();
//    virtual ~AlohaApMac();
//
//protected:
//    virtual void initialize() override;
//    virtual void handleMessage(cMessage *msg) override;

};
}



#endif /* SRC_LINKLAYER_ALOHA_ALOHAAPMAC_H_ */
