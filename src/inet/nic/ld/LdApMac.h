/*
 * LdApMac.h
 *
 *  Created on: 2017年3月23日
 *      Author: wh
 */

#ifndef INET_NIC_LD_LDAPMAC_H_
#define INET_NIC_LD_LDAPMAC_H_

#include "inet/common/INETDefs.h"
#include <vector>
using namespace std;

namespace inet
{
struct HostReq
{
    int nHostId;
    string strHostPath;
    int nReqSlotNum;
    int nPropagationSlotNum;
    bool bFinish;
};
class LdApMac:public cSimpleModule
{
private:
    //参数
    int m_slotNum;
    int m_reqSlotNum;
    simtime_t m_slotLength;

    //矢量，保存req
    vector<HostReq> m_reqVec;

    cMessage *m_selfMsg;

    //统计量
    simsignal_t m_ssPkTotalCount;
    //信号量，统计收到的数据包数，以及各个距离档收到的数据包
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
public:
    LdApMac();
    ~LdApMac();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendAck();
    void sortReqVec(vector<HostReq> &vec);

};

}



#endif /* INET_NIC_LD_LDAPMAC_H_ */
