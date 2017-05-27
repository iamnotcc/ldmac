/*
 * AlohaHostMac.h
 *
 *  Created on: 2016年6月1日
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
//    //参数
//    //发送速率
//    double m_dTxRate;
//    //时隙长度，如果为0，则为pure aloha
//    simtime_t m_stSlotTime;
//    //bool变量，指明是否是slotted
//    bool m_bIsSlotted;
//    //bool变量，指明是否空闲
//    bool m_bIsIDLE;
//    //ap模块指针
//    cModule *m_mdAp;
//
//    //队列：保存来自应用层的数据包
//    cQueue m_qPacketQueue;
//
//    //消息：
//    //结束发送
//    cMessage *m_msgEndTxEvent;
//    //应用层有消息发来
//    cMessage *m_msgPkArrival;
//    //自消息，每个一段时间汇报自己的位置
//    cMessage *m_msgSelf;
//
//    //以下都是统计量
//    simsignal_t m_ssQueueTime;
//    simtime_t m_stQueueTime;
//    simsignal_t m_ssDiscardPkCount;
//    simsignal_t m_ssSendPkCount;
//    //在某个区域的时间
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
//    //设置距离标志，根据距离远近来设置1~10
//    int setDistanceFlag();

};
}



#endif /* SRC_LINKLAYER_ALOHA_ALOHAHOSTMAC_H_ */
