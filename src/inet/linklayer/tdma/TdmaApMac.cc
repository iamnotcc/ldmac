/*
 * TdmaApMac.cc
 *
 *  Created on: 2017��3��8��
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
    //��ini��ȡ����ֵ
    m_nReqSlotNum=par("reqSlotNum");
    m_nSlotNum=par("slotNum");
    m_stSlotLength=par("slotLength");

    //ע���ź���
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

    //�½�һ������Ϣ
    m_msgSelfAllocation=new cMessage("msgSelfAllocation");
    scheduleAt(0+m_stSlotLength*m_nReqSlotNum,m_msgSelfAllocation);
}

//AP���������Ϣ
void TdmaApMac::handleMessage(cMessage *msg)
{
    //AP�����յ�����3����Ϣ��
    //����Ϣ�����ѷ��ͷ����
    //����HOST��REQ��
    //����HOST��DATA��
    if(msg->isSelfMessage())
    {
        //�յ�����Ϣ
        if(msg==m_msgSelfAllocation)
        {
            //���ͷ����
            sendAllocationPacket();
            //���host����
            m_vecHost.clear();
            //������һ������Ϣ
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
            //����HOST��req
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
            //����host��data
            case PacketKind_Host_Data :
            {
                //��������Host�����ݰ�
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
//���ͷ����
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

//������host�ľ���
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




