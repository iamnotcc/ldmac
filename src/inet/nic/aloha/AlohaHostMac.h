/*
 * AlohaHostMac.h
 *
 *  Created on: 2017年3月17日
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
    //参数，从Ini文件获取
    simtime_t m_slotLength;
    double m_txRate;
    double m_communicationRange;

    //ap模块
    cModule *m_ap=nullptr;
    //父模块
    cModule *m_parent=nullptr;

    //队列，保存应用层数据包
    cQueue m_appQueue=NULL;

    //统计量
    simsignal_t m_ssDiscardPkCount;
    simsignal_t m_ssSentPkCount;
    simsignal_t m_ssQueueTime;
    simtime_t m_queuetime;

    //自消息
    cMessage *m_selfMsgData;



public:
    //构造函数
    AlohaHostMac();
    //析构函数
    ~AlohaHostMac();

protected:
    //初始化函数
    virtual void initialize() override;
    //消息处理函数
    virtual void handleMessage(cMessage *msg) override;
    void sendData();
    //基础函数：或者当前位置，获取ap位置，计算距离，计算时隙
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlot();
};
}


#endif /* INET_NIC_ALOHA_ALOHAHOSTMAC_H_ */
