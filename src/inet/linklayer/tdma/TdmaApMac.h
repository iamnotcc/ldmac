/*
 * TdmaApMac.h
 *
 *  Created on: 2017��3��8��
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
//�ṹ�壺����HOST��req��Ϣ
struct HostReqOfTDMA
{
    int HostId;//id
    string HostPath;//·��
    Coord HostPosition;//λ��
    double Distance;//����
};

//�ṹ�壺����AP�ķ�����Ϣ
struct HostAllocationOfTDMA
{
    int Index;//host�ĵ�һ��ʱ϶
    int SlotNum;//host����ʱ϶��
};

class TdmaApMac: public cSimpleModule
{
private:
    //����
    //����req�����ʱ϶��
    int m_nReqSlotNum;
    //�ܵ�ʱ϶��
    int m_nSlotNum;
    //ʱ϶����
    simtime_t m_stSlotLength;
    //����Ϣ�����ͷ����
    cMessage *m_msgSelfAllocation;
    //ʸ��������host������req��Ϣ
    vector<HostReqOfTDMA> m_vecHost;

    //�ź�����ͳ���յ������ݰ������Լ��������뵵�յ������ݰ�
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
    //���ͷ����
    void sendAllocationPacket();
    //��ȡ������HOST�ľ���
    double getDistanceToHost(Coord cdHostPosition);
    //��HOST���վ�������
    void sortVecByDistance(vector<HostReqOfTDMA> &vec);

public:
    TdmaApMac();
    ~TdmaApMac();
};
}

*/

#endif /* INET_LINKLAYER_TDMA_TdmaApMac_H_ */
