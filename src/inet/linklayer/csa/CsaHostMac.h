/*
 * CsaHostMac.h
 *
 *  Created on: 2017��3��9��
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
//    //����
//    //ʱ϶����
//    simtime_t m_stSlotTime;
//    //һ֡��ʱ϶����
//    int m_nSlotNum;
//    //һ֡������ȷ�ϵ�ʱ϶��
//    int m_nAckSlotNum;
//
//    //apģ��ָ��
//    cModule *m_mdAp;
//
//    //��������app���ݵĶ���
//    cQueue m_qApp;
//    //���У�������Ҫ�ط������ݰ�
//    cQueue m_qReSend;
//
//    //��ǰ���͵���Ϣ
//    CsaHostData *m_msgCurrent;
//
//    //����Ϣ:��������
//    cMessage *m_msgSelfSendData;
//    //����Ϣ��
//    cMessage *m_msgSelfDataTimer;
//    //����Ϣ�����·���
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
