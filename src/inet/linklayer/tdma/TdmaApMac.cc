/*
 * TdmaApMac.cc
 *
 *  Created on: 2017年3月8日
 *      Author: wh
 */
/*
#include "TdmaApMac.h"

namespace inet
{
Define_Module(TdmaApMac);


TdmaApMac::TdmaApMac()
{
    m_msgSelfAllocation=nullptr;
}

TdmaApMac::~TdmaApMac()
{
    cancelAndDelete(m_msgSelfAllocation);
}

void TdmaApMac::initialize()
{
    //从ini获取参数值
    m_nReqSlotNum=par("reqSlotNum");
    m_nSlotNum=par("slotNum");
    m_stSlotLength=par("slotLength");

    //注册信号量
    m_ssPkCount=registerSignal("pkCount");
    m_ssPkCount1=registerSignal("pkCount1");
    m_ssPkCount2=registerSignal("pkCount2");
    m_ssPkCount3=registerSignal("pkCount3");
    m_ssPkCount4=registerSignal("pkCount4");
    m_ssPkCount5=registerSignal("pkCount5");
    m_ssPkCount6=registerSignal("pkCount6");
    m_ssPkCount7=registerSignal("pkCount7");
    m_ssPkCount8=registerSignal("pkCount8");
    m_ssPkCount9=registerSignal("pkCount9");
    m_ssPkCount10=registerSignal("pkCount10");

    //新建一个自消息
    m_msgSelfAllocation=new cMessage("msgSelfAllocation");
    scheduleAt(0+m_stSlotLength*m_nReqSlotNum,m_msgSelfAllocation);
}

//AP处理各类消息
void TdmaApMac::handleMessage(cMessage *msg)
{
    //AP可能收到以下3类消息：
    //自消息：提醒发送分配包
    //来自HOST的REQ包
    //来自HOST的DATA包
    if(msg->isSelfMessage())
    {
        //收到自消息
        if(msg==m_msgSelfAllocation)
        {
            //发送分配包
            sendAllocationPacket();
            //清空host队列
            m_vecHost.clear();
            //调度下一次自消息
            scheduleAt(simTime()+m_stSlotLength*m_nSlotNum,m_msgSelfAllocation);
        }
        else
        {
            throw cRuntimeError("AP receive error self message.");
        }
    }
    else
    {
        switch(msg->getKind())
        {
            //来自HOST的req
            case PacketKind_Host_Request :
            {
                HostReqPkOfTDMA *pk=dynamic_cast<HostReqPkOfTDMA *>(msg);
                int nHostId=pk->getNHostId();
                string strHostPath=pk->getStrHostPath();
                Coord cdHostPosition=pk->getCdHostPosition();
                double dDistance=getDistanceToHost(cdHostPosition);
                HostReqOfTDMA structHostReq={nHostId,strHostPath,cdHostPosition,dDistance};
                m_vecHost.push_back(structHostReq);

                delete pk;

                break;
            }
            //来自host的data
            case PacketKind_Host_Data :
            {
                //处理来自Host的数据包
                emit(m_ssPkCount,1l);
                EV<<"Ap successfully received a packet from"<<msg->getSenderModule()->getName()<<endl;
                switch(msg->getSrcProcId())
                {
                    case 1:
                    {
                        emit(m_ssPkCount1,1l);
                        delete msg;
                        break;
                    }
                    case 2:
                    {
                        emit(m_ssPkCount2,1l);
                        delete msg;
                        break;
                    }
                    case 3:
                    {
                        emit(m_ssPkCount3,1l);
                        delete msg;
                        break;
                    }
                    case 4:
                    {
                        emit(m_ssPkCount4,1l);
                        delete msg;
                        break;
                    }
                    case 5:
                    {
                        emit(m_ssPkCount5,1l);
                        delete msg;
                        break;
                    }
                    case 6:
                    {
                        emit(m_ssPkCount6,1l);
                        delete msg;
                        break;
                    }
                    case 7:
                    {
                        emit(m_ssPkCount7,1l);
                        delete msg;
                        break;
                    }
                    case 8:
                    {
                        emit(m_ssPkCount8,1l);
                        delete msg;
                        break;
                    }
                    case 9:
                    {
                        emit(m_ssPkCount9,1l);
                        delete msg;
                        break;
                    }
                    case 10:
                    {
                        emit(m_ssPkCount10,1l);
                        delete msg;
                        break;
                    }
                    default:
                    {
                        throw cRuntimeError("AP receive error distance flag.");
                        delete msg;
                        break;
                    }
                }
                break;
            }
            default :
            {
                throw cRuntimeError("AP receive error message.");
                break;
            }
        }
    }
}
//发送分配包
void TdmaApMac::sendAllocationPacket()
{
    EV_DEBUG<<"Ap is broadcasting allocation information..."<<endl;

    int nHostNum=m_vecHost.size();

    sortVecByDistance(m_vecHost);

    int nAverageSlotNum=(m_nSlotNum-m_nReqSlotNum)/nHostNum;
    int nMoreSlotNum=(m_nSlotNum-m_nReqSlotNum)%nHostNum;

    EV_DEBUG<<"Ap allocation:"<<endl;
    EV_DEBUG<<"size of vecHost:"<<nHostNum <<endl;
    EV_DEBUG<<"average slot num:"<< nAverageSlotNum<<endl;
    EV_DEBUG<<"left slot num"<< nMoreSlotNum<<endl;

    int nIndex=m_nReqSlotNum;
    int nSlotNum=0;
    cModule *mdHost;
    for(int i=0;i<nHostNum;i++)
    {
        ApAllocationPkOfTDMA *pk= new ApAllocationPkOfTDMA();
        pk->setKind(PacketKind_Ap_Allocation);
        pk->setNIndex(nIndex);
        if(i<nMoreSlotNum)
        {
            nSlotNum=nAverageSlotNum+1;
        }
        else
        {
            nSlotNum=nAverageSlotNum;
        }
        pk->setNSlotNum(nSlotNum);
        nIndex=nIndex+nSlotNum;
        mdHost=getModuleByPath(m_vecHost[i].HostPath.c_str());

        EV_DEBUG<<"Allocation information for "<<mdHost->getFullPath()<<" is:"<<endl;
        EV_DEBUG<<"index of slot:"<<pk->getNIndex() <<endl;
        EV_DEBUG<<"num of slots:"<< pk->getNSlotNum()<<endl;

        sendDirect(pk,mdHost->gate("in"));
    }


}
void TdmaApMac::sortVecByDistance(vector<HostReqOfTDMA> &vec)
{
    HostReqOfTDMA structTemp;
    for(int i=0;i<vec.size();i++)
    {
        for(int j=i;j<vec.size()-1;j++)
        {
            if(vec[j].Distance<vec[j+1].Distance)
            {
                structTemp=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=structTemp;
            }
        }
    }
}

//计算与host的距离
double TdmaApMac::getDistanceToHost(Coord cdHostPosition)
{
    cModule *mdParent=getParentModule();
    cModule *mdMobility=mdParent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    Coord cdThisPosition=mdMovingMobility->getCurrentPosition();
    return cdThisPosition.distance(cdHostPosition);
}
}

*/




