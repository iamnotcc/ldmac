/*
 * CsaHostMac.h
 *
 *  Created on: 2017年3月9日
 *      Author: wh
 */

#ifndef INET_LINKLAYER_CSA_CsaHostMac_H_
#define INET_LINKLAYER_CSA_CsaHostMac_H_

#include "inet/common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/common/PacketKind.h"
#include "inet/linklayer/common/LinklayerCommon.h"
#include "inet/mobility/contract/IMobility.h"

#include <vector>
using namespace std;

namespace inet
{
//class CsaHostMac : public cSimpleModule
//{
//private:
//    //参数
//    //时隙长度
//    simtime_t m_stSlotTime;
//    //一帧的时隙个数
//    int m_nSlotNum;
//    //一帧中用于确认的时隙数
//    int m_nAckSlotNum;
//
//    //ap模块指针
//    cModule *m_mdAp;
//
//    //保存来自app数据的队列
//    cQueue m_qApp;
//    //队列：保存需要重发的数据包
//    cQueue m_qReSend;
//
//    //当前发送的消息
//    CsaHostData *m_msgCurrent;
//
//    //自消息:发送数据
//    cMessage *m_msgSelfSendData;
//    //自消息：
//    cMessage *m_msgSelfDataTimer;
//    //自消息：重新发送
//    cMessage *m_msgSelfReSend;
//
//
//protected:
//    virtual void initialize() override;
//    virtual void handleMessage(cMessage *msg) override;
//    virtual int getCopyNum();
//    virtual void selectSlots(std::vector<int> &vec, int nSlotNum);
//    virtual CsaHostData *generateCSAPacket();
//    virtual void sendDataPacket(CsaHostData *msg);
//
//    Coord getCurrentPosition();
//    Coord getApPosition();
//    double getDistance();
//    int getPropagationSlotNum(double dDistance,simtime_t stSlotLength);
//
//public:
//    CsaHostMac();
//    virtual ~CsaHostMac();
//
//};
}



#endif /* INET_LINKLAYER_CSA_CsaHostMac_H_ */
