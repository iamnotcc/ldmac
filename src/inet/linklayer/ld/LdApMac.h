/*
 * ldApMac.h
 *
 *  Created on: 2016��6��14��
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
////�ṹ�屣��host��req��Ϣ
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
//    //ʸ��������req��Ϣ
//    vector<HostReqInfo> m_vecHostReqs;
//
//    //������ʱ϶���ȣ�
//    simtime_t m_stSlotLength;
//    int m_nRequestSlotNum;
//    int m_nAllocateSlotNum;
//    int m_nTransmitSlotNum;
//
//    //����Ϣ�����ѹ㲥������Ϣ
//    cMessage *m_msgSelfAllocation;
//
//    //�ź�����ͳ���յ������ݰ������Լ��������뵵�յ������ݰ�
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
