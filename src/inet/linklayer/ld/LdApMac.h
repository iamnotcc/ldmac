/*
 * ldApMac.h
 *
 *  Created on: 2016年6月14日
 *      Author: Administrator
 */

#ifndef SRC_LINKLAYER_LD_LDAPMAC_H_
#define SRC_LINKLAYER_LD_LDAPMAC_H_

#include "inet/common/INETDefs.h"
#include <vector>
#include "common/PacketKind.h"
#include "linklayer/ld/HostReqPacket_m.h"
#include "linklayer/ld/ApAllocationPacket_m.h"
using namespace std;

namespace inet
{
////结构体保存host的req信息
//struct HostReqInfo
//{
//    int nHostId;
//    string strHostPath;
//    int nReqSlotNum;
//    int nPropagationSlotNum;
//};
//
//class LdApMac:public cSimpleModule
//{
//private:
//    //矢量：保存req信息
//    vector<HostReqInfo> m_vecHostReqs;
//
//    //参数：时隙长度，
//    simtime_t m_stSlotLength;
//    int m_nRequestSlotNum;
//    int m_nAllocateSlotNum;
//    int m_nTransmitSlotNum;
//
//    //自消息：提醒广播分配消息
//    cMessage *m_msgSelfAllocation;
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
//    LdApMac();
//    ~LdApMac();
//
//protected:
//    virtual void initialize() override;
//    virtual void handleMessage(cMessage *msg) override;
//    void broadcastAllocationInfo();
//    void sortVec(vector<HostReqInfo> &vec);
//    void outputVec(vector<HostReqInfo> vec);
//
//};

}




#endif /* SRC_LINKLAYER_LD_LDAPMAC_H_ */
