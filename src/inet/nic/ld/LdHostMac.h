/*
 * LdHostMac.h
 *
 *  Created on: 2017年3月23日
 *      Author: wh
 */

#ifndef INET_NIC_LD_LDHOSTMAC_H_
#define INET_NIC_LD_LDHOSTMAC_H_
#define MAX_REQUEST_SLOTS 2000
#include "inet/common/INETDefs.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/mobility/contract/IMobility.h"

namespace inet
{
class LdHostMac: public cSimpleModule
{
private:

    //参数，从ini文件获取
    double m_txRate=0;
    int m_slotNum=0;
    int m_reqSlotNum=0;
    simtime_t m_slotLength=0;
    int m_reqLength=0;
    double m_communicationRange=0;

    bool m_isSendReq=true;
    int m_reqCounter=0;

    int m_dataSlotIndex=-1;
    int m_dataSlotNum=-1;
    simtime_t m_dataTransmitTime;

    //Ap模块
    cModule *m_ap;
    //父模块
    cModule *m_parent;

    //队列，保存应用层数据包
    cQueue m_appQueue;

    //统计量
    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSentPkCount;
    simsignal_t m_ssQueueTime;
    simtime_t m_queuetime;
    //在某个区域的时间
    simtime_t m_stTime;
    simsignal_t m_ssTotalTime;
    simsignal_t m_ssTime1;
    simsignal_t m_ssTime2;
    simsignal_t m_ssTime3;
    simsignal_t m_ssTime4;
    simsignal_t m_ssTime5;
    simsignal_t m_ssTime6;
    simsignal_t m_ssTime7;
    simsignal_t m_ssTime8;
    simsignal_t m_ssTime9;
    simsignal_t m_ssTime10;

    //自消息
    cMessage *m_selfMsgReq;
    cMessage *m_selfMsgData;


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    //发送req
    void sendReq();
    //发送data
    void sendData();
    //基础函数：或者当前位置，获取ap位置，计算距离，计算时隙
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlot();
    //设置距离标志，根据距离远近来设置1~10
    int setDistanceFlag();

public:
    //构造函数和析构函数
    LdHostMac();
    ~LdHostMac();

};
}



#endif /* INET_NIC_LD_LDHOSTMAC_H_ */
