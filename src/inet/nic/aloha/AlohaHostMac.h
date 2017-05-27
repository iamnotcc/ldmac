/*
 * AlohaHostMac.h
 *
 *  Created on: 2017��3��17��
 *      Author: wh
 */

#ifndef INET_NIC_ALOHA_ALOHAHOSTMAC_H_
#define INET_NIC_ALOHA_ALOHAHOSTMAC_H_

#include "common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"

namespace inet
{
class AlohaHostMac:public cSimpleModule
{
private:
    //��������Ini�ļ���ȡ
    simtime_t m_slotLength;
    double m_txRate;
    double m_communicationRange;

    //apģ��
    cModule *m_ap=nullptr;
    //��ģ��
    cModule *m_parent=nullptr;

    //���У�����Ӧ�ò����ݰ�
    cQueue m_appQueue=NULL;

    //ͳ����
    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSentPkCount;
    simsignal_t m_ssQueueTime;
    simtime_t m_queuetime;

    //����Ϣ
    cMessage *m_selfMsgData;



public:
    //���캯��
    AlohaHostMac();
    //��������
    ~AlohaHostMac();

protected:
    //��ʼ������
    virtual void initialize() override;
    //��Ϣ������
    virtual void handleMessage(cMessage *msg) override;
    void sendData();
    //�������������ߵ�ǰλ�ã���ȡapλ�ã�������룬����ʱ϶
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlot();
};
}


#endif /* INET_NIC_ALOHA_ALOHAHOSTMAC_H_ */
