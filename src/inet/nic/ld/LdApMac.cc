/*
 * LdApMac.cc
 *
 *  Created on: 2017年3月23日
 *      Author: wh
 */

#include "nic/ld/LdApMac.h"
#include "inet/common/PacketKind.h"
#include "inet/nic/ld/LdReq_m.h"
#include "inet/nic/ld/LdAck_m.h"

namespace inet
{
Define_Module(LdApMac);

LdApMac::LdApMac()
{
    m_selfMsg=nullptr;
}

LdApMac::~LdApMac()
{
    cancelAndDelete(m_selfMsg);
}

void LdApMac::initialize()
{
    //初始化参数
    m_slotNum=par("slotNum");
    m_slotLength=par("slotLength");
    m_reqSlotNum=par("reqSlotNum");
    m_ssPkTotalCount=registerSignal("pkTotalCount");
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


    EV_DEBUG<<this->getFullPath()<<" initialize parameters: "<<endl;
    EV_DEBUG<<"m_slotNum: "<<m_slotNum<<endl;
    EV_DEBUG<<"m_reqSlotNum: "<<m_reqSlotNum<<endl;
    EV_DEBUG<<"m_slotLength: "<<m_slotLength<<endl;

    //初始化自消息
    m_selfMsg=new cMessage("selfMsg");
    scheduleAt(0+m_slotLength*(m_reqSlotNum-2),m_selfMsg);
    EV_DEBUG<<"The first self message scheduled at : "<<m_slotLength*(m_reqSlotNum-2)<<endl;
}

void LdApMac::handleMessage(cMessage *msg)
{
    EV<<"FUNCTION: LdApMac::handleMessage()"<<endl;
    if(msg->isSelfMessage())
    {
        EV_DEBUG<<"Self message arrived: "<<msg->getName()<<", preparing to send a ack."<<endl;

        scheduleAt(simTime()+m_slotLength*m_slotNum,m_selfMsg);
        EV_DEBUG<<"The next self message scheduled at : "<<(simTime()+m_slotLength*m_slotNum)<<endl;

        sendAck();
    }
    else
    {
        if(msg->getKind()==PacketKind_Host_Request)
        {
            EV_DEBUG<<"A request packet "<< msg->getName()<< " from "<<(msg->getSenderModule())->getFullPath()<<" arrived."<<endl;
            LdReq *reqPk=dynamic_cast<LdReq *>(msg);
            HostReq structHostReq={reqPk->getNHostId(),reqPk->getStrHostPath(),reqPk->getNRequestSlotNum(),reqPk->getNPropagationSlotNum(),false};
            EV_DEBUG<<"Req information: "<<endl;
            EV_DEBUG<<"host id: "<<structHostReq.nHostId<< endl;
            EV_DEBUG<<"host path: "<<structHostReq.strHostPath<< endl;
            EV_DEBUG<<"req slot num: "<<structHostReq.nReqSlotNum<< endl;
            EV_DEBUG<<"propagation slot num: "<<structHostReq.nPropagationSlotNum<< endl;

            m_reqVec.push_back(structHostReq);
            EV_DEBUG<<"A req information is inserted into m_reqVec.";
            EV_DEBUG<<", and the length of m_reqVec is: "<<m_reqVec.size()<<endl;
        }
        else
        {
            if(msg->getKind()==PacketKind_Host_Data)
            {
                EV_DEBUG<<"Ap received a packet:"<<msg->getName()<<endl;
                emit(m_ssPkTotalCount,1l);
                switch(msg->getSrcProcId())
                 {
                     case 1:
                     {
                         emit(m_ssPkCount1,1l);
                         break;
                     }
                     case 2:
                     {
                         emit(m_ssPkCount2,1l);
                         break;
                     }
                     case 3:
                     {
                         emit(m_ssPkCount3,1l);
                         break;
                     }
                     case 4:
                     {
                         emit(m_ssPkCount4,1l);
                         break;
                     }
                     case 5:
                     {
                         emit(m_ssPkCount5,1l);
                         break;
                     }
                     case 6:
                     {
                         emit(m_ssPkCount6,1l);
                         break;
                     }
                     case 7:
                     {
                         emit(m_ssPkCount7,1l);
                         break;
                     }
                     case 8:
                     {
                         emit(m_ssPkCount8,1l);
                         break;
                     }
                     case 9:
                     {
                         emit(m_ssPkCount9,1l);
                         break;
                     }
                     case 10:
                     {
                         emit(m_ssPkCount10,1l);
                         break;
                     }
                     default:
                     {
                         throw cRuntimeError("AP receive error distance flag.");
                         break;
                     }
                 }
                delete msg;
            }
            else
            {
                throw cRuntimeError("LD: ap received a error type message!");
            }
        }
    }

}

void LdApMac::sendAck()
{
    EV<<"FUNCTION: LdApMac::sendAck()"<<endl;
    //如果vector为空，没什么发送
    if(m_reqVec.empty())
    {
        EV_DEBUG<<"m_reqVec is empty, no ack will be sent."<<endl;
    }
    //不为空，为节点分配时隙
    else
    {
        //按照传播时隙排序
        sortReqVec(m_reqVec);

        const int nReqVecLength=m_reqVec.size();
        //slotNum，保存给每个host分配多少时隙
        int slotNum[nReqVecLength];
        for(int i=0;i<nReqVecLength;i++)
        {
            slotNum[i]=0;
        }
        const int nDataSlotNum=m_slotNum-m_reqSlotNum;
        int nAvaiableDataSlotNum=m_slotNum-m_reqSlotNum;
        EV_DEBUG<<"reqVecLength: "<<nReqVecLength<<endl;
        EV_DEBUG<<"dataSlotNum: "<<nDataSlotNum<<endl;


        //给所有host分配时隙
        bool bFinish=false;
        bool bTemp;
        while(!bFinish)
        {
            EV_DEBUG<<"Start a loop, bFinish="<<bFinish<<endl;
            for(int i=0;i<nReqVecLength;i++)
            {
                EV_DEBUG<<"m_reqVec["<<i<<"]:"<<endl;
                EV_DEBUG<<"reqSlotNum: "<<m_reqVec[i].nReqSlotNum<<endl;
                if(slotNum[i]<m_reqVec[i].nReqSlotNum)
                {
                    if(slotNum[i]<(nDataSlotNum-m_reqVec[i].nPropagationSlotNum))
                    {
                        if(nAvaiableDataSlotNum>0)
                        {
                            slotNum[i]++;
                            nAvaiableDataSlotNum--;
                            EV_DEBUG<<"A slot is allocated to "<<i<<", and total slots for it are: "<<slotNum[i]<<endl;
                            EV_DEBUG<<"nAvaiableDataSlotNum= "<<nAvaiableDataSlotNum<<endl;
                        }
                        else
                        {
                            bFinish=true;
                            EV_DEBUG<<"No data slots available."<<endl;
                        }
                    }
                    else
                    {
                        m_reqVec[i].bFinish=true;
                        EV_DEBUG<<"slotNum["<<i<<"]==nDataSlotNum-nPropagationSlotNum."<<endl;
                    }
                }
                else
                {
                    m_reqVec[i].bFinish=true;
                    EV_DEBUG<<"slotNum["<<i<<"]==reqSlotNum"<<endl;
                }
            }

            bTemp=m_reqVec[0].bFinish;
            for(int i=1;i<nReqVecLength;i++)
            {
                bTemp=bTemp&&m_reqVec[i].bFinish;
            }

            if(bTemp || bFinish)
            {
                bFinish=true;
                EV_DEBUG<<"Allocation finishes."<<endl;
            }
        }


        int arrivalSlotIndex[nReqVecLength];
        for(int i=0;i<nReqVecLength;i++)
        {
            arrivalSlotIndex[i]=0;
        }
        EV_DEBUG<<"The arrival slot index:  ";
        for(int i=0;i<nReqVecLength;i++)
        {
            if(i==0)
            {
                arrivalSlotIndex[i]= m_reqVec[i].nPropagationSlotNum;
                EV_DEBUG<<arrivalSlotIndex[i]<<", ";
            }
            else
            {
                arrivalSlotIndex[i]=arrivalSlotIndex[i-1]+slotNum[i-1];
                if(arrivalSlotIndex[i]<m_reqVec[i].nPropagationSlotNum)
                {
                    arrivalSlotIndex[i]=m_reqVec[i].nPropagationSlotNum;
                }
                EV_DEBUG<<arrivalSlotIndex[i]<<", ";
            }
        }
        EV_DEBUG<<endl;

        int slotIndex[nReqVecLength];
        EV_DEBUG<<"********The start transmit slot index:  ";
        for(int i=0;i<nReqVecLength;i++)
        {
            slotIndex[i]=arrivalSlotIndex[i]-m_reqVec[i].nPropagationSlotNum;
            EV_DEBUG<<slotIndex[i]<<", ";
            if(slotIndex[i]<0)
            {
                throw cRuntimeError("slotIndex<0, slotIndex=%d,arrivalSlotIndex=%d,PropagationSlotNum=%d",slotIndex[i],arrivalSlotIndex[i],m_reqVec[i].nPropagationSlotNum);
            }
        }
        EV_DEBUG<<endl;

        EV_DEBUG<<"********The transmit slot number:  ";
        for(int i=0;i<nReqVecLength;i++)
        {
            if(slotNum[i]<0)
            {
                throw cRuntimeError("slotNum<0, slotNum==%d",slotNum[i]);
            }
            EV_DEBUG<<slotNum[i]<<", ";
        }
        EV_DEBUG<<endl;

        //更新m_reqVec
        vector<HostReq> temp;
        for(int i=0;i<nReqVecLength;i++)
        {
            m_reqVec[i].nReqSlotNum=m_reqVec[i].nReqSlotNum-slotNum[i];
            if(m_reqVec[i].nReqSlotNum!=0)
            {
                temp.push_back(m_reqVec[i]);
            }
        }

        cModule *mdHost;
        for(int i=0;i<nReqVecLength;i++)
        {
            EV_DEBUG<<"AP send an ack packet to "<<m_reqVec[i].strHostPath<<endl;
            LdAck *ackPk=new LdAck("ack");
            ackPk->setKind(PacketKind_Ap_ACK);
            ackPk->setNIndexSlot(slotIndex[i]);
            ackPk->setNSlotNum(slotNum[i]);
            if(m_reqVec[i].nReqSlotNum==0)
            {
                ackPk->setBIsOver(true);
            }
            else
            {
                ackPk->setBIsOver(false);
            }
            mdHost=getModuleByPath(m_reqVec[i].strHostPath.c_str());
            sendDirect(ackPk,0,0,mdHost->gate("in"));
        }


        if(m_reqVec.size()!=temp.size())
        {
            m_reqVec.clear();
            m_reqVec=temp;
        }
    }
}

void LdApMac::sortReqVec(vector<HostReq> &vec)
{
    EV_DEBUG<<"FUNCTION: LdApMac::sortReqVec"<<endl;
    EV_DEBUG<<"Original vector:"<<endl;
    for(int i=0;i<vec.size();i++)
    {
        EV_DEBUG<<vec[i].nPropagationSlotNum<<", ";
    }
    EV_DEBUG<<endl;

    HostReq structTemp;
    for(int i=0;i<vec.size();i++)
    {
        for(int j=i;j<vec.size()-1;j++)
        {
            if(vec[j].nPropagationSlotNum > vec[j+1].nPropagationSlotNum)
            {
                structTemp=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=structTemp;
            }
        }
    }
    EV_DEBUG<<"Sorted vector:"<<endl;
    for(int i=0;i<vec.size();i++)
    {
        EV_DEBUG<<vec[i].nPropagationSlotNum<<", ";
    }
    EV_DEBUG<<endl;
}


}


