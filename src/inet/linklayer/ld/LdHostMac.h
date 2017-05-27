/*
 * ldHostMac.h
 *
 *  Created on: 2016年6月14日
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
////结构体，保存来自AP的信息，发送时隙的序号以及时隙个数
//struct HostTransmitInfo
//{
//    int nIndex;
//    int nSlotNum;
//};
//
//class LdHostMac: public cSimpleModule
//{
//private:
//    //参数，在ned文件中定义
//    simtime_t m_stSlotLength;
//    int m_nRequestSlotNum;
//    int m_nAllocateSlotNum;
//    int m_nTransmitSlotNum;
//    double m_dTxRate;
//    cPar *m_nReqPktLength;
//
//    //ldAp模块
//    cModule *m_mdAp;
//
//    //自消息，发送request和data自消息
//    cMessage *m_msgSelfReq;
//    cMessage *m_msgSelfData;
//
//    //队列：保存应用层数据包
//    cQueue m_qAppPacketList;
//    cQueue m_qReTransmitQueue;
//
//    //随机数，决定是否丢包
//    double m_dRandom;
//
//    //计数器，记录当前申请的slot还有多少个
//    int m_nSlotLeftCounter;
//
//    //host数据传输信息，来自ap
//    HostTransmitInfo m_hostTransmitInfo;
//
//    //信号量，指示丢弃的包数量
//    simsignal_t m_ssDiscardPkCount;
//    //信号量，指示成功发送的包数量
//    simsignal_t m_ssSendPkCount;
//
//    //排队时间
//    simtime_t m_stQueueTime;
//    //信号量，指示每个成功发送的数据包等待的时间
//    simsignal_t m_ssQueueTime;
//
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
//protected:
//    //函数：初始化
//    virtual void initialize() override;
//    //函数：处理各类消息
//    virtual void handleMessage(cMessage *msg) override;
//    //函数：生成host的req包
//    HostReqPacket *generateReqPacket();
//    //函数：从AP的广播包中获取host的传输信息
//    HostTransmitInfo getHostTransmitInfo(ApAllocationPacket *pk);
//    //函数：发送req包
//    void sendReqPacket(HostReqPacket *pk);
//    //函数：发送数据包
//    void sendDataPacket(HostTransmitInfo structTransmitInfo);
//
//
//    //基础函数
//    //函数：获取当前位置
//    Coord getCurrentPosition();
//    //函数：获取AP的位置
//    Coord getApPosition();
//    //函数：计算host和AP之间的距离
//    double getDistance();
//    //函数：将距离转化为时隙个数
//    int getPropagationSlotNum(double dDistance,simtime_t stSlotLength);
//    //设置距离标志，根据距离远近来设置1~10
//    int setDistanceFlag();
//public:
//    //构造函数和析构函数
//    LdHostMac();
//    virtual ~LdHostMac();
//
//};
}



#endif /* SRC_LINKLAYER_LD_LDHOSTMAC_H_ */
