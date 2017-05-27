/*
 * TdmaApMac.h
 *
 *  Created on: 2017年3月8日
 *      Author: wh
 */

#ifndef INET_LINKLAYER_TDMA_TdmaApMac_H_
#define INET_LINKLAYER_TDMA_TdmaApMac_H_
/*
#include "inet/common/INETDefs.h"
#include "common/PacketKind.h"
#include "inet/common/geometry/common/Coord.h"
#include <vector>
#include "inet/linklayer/tdma/HostReqPkOfTDMA_m.h"
#include "inet/linklayer/tdma/ApAllocationPkOfTDMA_m.h"
#include "inet/mobility/contract/IMobility.h"
using namespace std;


namespace inet
{
//结构体：保存HOST的req信息
struct HostReqOfTDMA
{
    int HostId;//id
    string HostPath;//路径
    Coord HostPosition;//位置
    double Distance;//距离
};

//结构体：保存AP的分配信息
struct HostAllocationOfTDMA
{
    int Index;//host的第一个时隙
    int SlotNum;//host的总时隙数
};

class TdmaApMac: public cSimpleModule
{
private:
    //参数
    //用于req申请的时隙数
    int m_nReqSlotNum;
    //总的时隙数
    int m_nSlotNum;
    //时隙长度
    simtime_t m_stSlotLength;
    //自消息：发送分配包
    cMessage *m_msgSelfAllocation;
    //矢量，保存host发来的req信息
    vector<HostReqOfTDMA> m_vecHost;

    //信号量，统计收到的数据包数，以及各个距离档收到的数据包
    simsignal_t m_ssPkCount;
    simsignal_t m_ssPkCount1;
    simsignal_t m_ssPkCount2;
    simsignal_t m_ssPkCount3;
    simsignal_t m_ssPkCount4;
    simsignal_t m_ssPkCount5;
    simsignal_t m_ssPkCount6;
    simsignal_t m_ssPkCount7;
    simsignal_t m_ssPkCount8;
    simsignal_t m_ssPkCount9;
    simsignal_t m_ssPkCount10;


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    //发送分配包
    void sendAllocationPacket();
    //获取距离与HOST的距离
    double getDistanceToHost(Coord cdHostPosition);
    //对HOST按照距离排序
    void sortVecByDistance(vector<HostReqOfTDMA> &vec);

public:
    TdmaApMac();
    ~TdmaApMac();
};
}

*/

#endif /* INET_LINKLAYER_TDMA_TdmaApMac_H_ */
