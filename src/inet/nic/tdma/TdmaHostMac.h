/*
 * TdmaHostMac.h
 *
 *  Created on: 2017年3月15日
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
    //从ini获取的参数
    double m_txRate;
    double m_communicationRange;
    simtime_t m_slotLength;
    int m_slotNum;
    int m_reqSlotNum;

    //参数：保存来自ack的信息
    int m_dataSlotNum;
    int m_dataSlotIndex;
    simtime_t m_dataTransmitTime;
    //ap模块指针
    cModule *m_ap;
    //父模块
    cModule *m_parent;

    //应用层数据队列
    cQueue m_appQueue;

    //统计量
    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSentPkCount;
    simsignal_t m_ssQueueTime;
    simtime_t m_queuetime;

    //自消息
    cMessage *m_selfMsgReq;
    cMessage *m_selfMsgData;

protected:
    //初始化函数
    virtual void initialize() override;

    //消息处理函数
    virtual void handleMessage(cMessage *msg) override;

    //发送req
    void sendReq();
    //发送data
    void sendData();

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




#endif /* INET_NIC_TDMA_TDMAHOSTMAC_H_ */
