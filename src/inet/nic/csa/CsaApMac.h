/*
 * CsaApMac.h
 *
 *  Created on: 2017��4��15��
 *      Author: LiuXinyun
 */

#ifndef INET_NIC_CSA_CSAAPMAC_H_
#define INET_NIC_CSA_CSAAPMAC_H_
#include "inet/common/INETDefs.h"
#include "inet/common/PacketKind.h"
#include "inet/nic/csa/CsaHostPk_m.h"
#include <vector>
using namespace std;

namespace inet
{
class CsaApMac:public cSimpleModule
{
private:
    //����
    int m_slotNum;
    simtime_t m_slotLength;
    vector<CsaHostPk *> vecHostPks;

    cMessage *m_selfMsgHandleHostData;

    //ͳ����
    simsignal_t m_ssPkCount;

protected:
    void initParameters();
    void initStatistic();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleNonSelfMsg(cMessage *msg);
    void handleSelfMsg(cMessage *msg);
    void handleHostData();

public:
    CsaApMac();
    ~CsaApMac();

};
}




#endif /* INET_NIC_CSA_CSAAPMAC_H_ */
