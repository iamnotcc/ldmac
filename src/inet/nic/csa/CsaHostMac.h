/*
 * CsaHostMac.h
 *
 *  Created on: 2017��4��15��
 *      Author: LiuXinyun
 */

#ifndef INET_NIC_CSA_CSAHOSTMAC_H_
#define INET_NIC_CSA_CSAHOSTMAC_H_

#include "inet/common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/nic/common/NicCommon.h"
#include "inet/common/PacketKind.h"
#include <vector>
#include "inet/nic/csa/CsaHostPk_m.h"
using namespace std;

namespace inet
{
class CsaHostMac: public cSimpleModule
{
private:
    //����
    double m_communicationRange;
    simtime_t m_slotLength;
    int m_slotNum;

    //���У���������app������
    cQueue m_appQueue;

    //����Ϣ
    cMessage *m_selfMsgSendData;


    cModule *m_ap;
    cModule *m_parent;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

public:
    CsaHostMac();
    ~CsaHostMac();

private:
    void findAp();
    void findParentModule();
    void initParameters();
    void initStatistic();
    void initSelfMsg();
    void handleSelfMsg(cMessage *msg);
    void handleSelfMsgSendData(cMessage *msg);
    void sendData();
    int getNumOfTransmittingPks();
    int getNumOfRepetions();


    void handleNonSelfMsg(cMessage *msg);
    void handleAppMsg(cMessage *msg);




    //�������������ߵ�ǰλ�ã���ȡapλ�ã�������룬����ʱ϶
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlot();


};
}



#endif /* INET_NIC_CSA_CSAHOSTMAC_H_ */
