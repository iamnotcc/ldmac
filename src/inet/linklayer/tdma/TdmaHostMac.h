/*
 * TdmaHostMac.h
 *
 *  Created on: 2017年3月8日
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
    //参数
    double m_dTxRate;
    int m_nSlotNum;
    simtime_t m_stSlotLength;
    cPar *m_nReqLength;

    //ap模块
    cModule *m_mdAp;

    //队列，保存来自app的数据包
    cQueue m_qAppQueue;
    cQueue m_qReTransmitQueue;

    //自消息
    cMessage *m_msgSelfReq;
    cMessage *m_msgSelfData;

    //分配给自己的开始时隙索引和时隙个数
    int m_nTransmitSlotIndex;
    int m_nTransmitSlotNum;

    int m_nWasteSlotNum;

    //随机数，决定是否丢包
    double m_dRandom;

    simsignal_t m_ssQueueTime;
    simtime_t m_stQueueTime;

    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSendPkCount;

    //在某个区域的时间
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

    //设置距离标志，根据距离远近来设置1~10
    int setDistanceFlag();

    //基础函数：或者当前位置，获取ap位置，计算距离，计算时隙
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
