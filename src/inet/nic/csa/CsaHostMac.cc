/*
 * CsaHostMac.cc
 *
 *  Created on: 2017��4��15��
 *      Author: LiuXinyun
 */
#include "inet/nic/csa/CsaHostMac.h"


namespace inet
{
Define_Module(CsaHostMac);

CsaHostMac::CsaHostMac()
{
    m_selfMsgSendData=nullptr;
}

CsaHostMac::~CsaHostMac()
{

}

void CsaHostMac::initialize()
{
    //find ap
    findAp();
    //find parent module
    findParentModule();
    //initialize parameters
    initParameters();
    //initialize statistic
    initStatistic();
    //initialize self message
    initSelfMsg();
}
//����APģ��
void CsaHostMac::findAp()
{
    m_ap=getModuleByPath("ap");
    if(!m_ap)
    {
        throw cRuntimeError("CSA: ap not found.");
    }
    else
    {
        EV_DEBUG<<this->getFullName()<<" found ap: "<< m_ap->getFullName()<<endl;
    }
}

//���ָ�ģ��
void CsaHostMac::findParentModule()
{
    m_parent=getParentModule();
    if(!m_parent)
    {
        throw cRuntimeError("CSA: parent module not found.");
    }
}

//��ʼ������
void CsaHostMac::initParameters()
{
    m_communicationRange=par("communicationRange");
    m_slotLength=par("slotLength");
    m_slotNum=par("slotNum");

    EV<<"Parameter values:"<<endl;
    EV<<"******communication range="<<m_communicationRange<<endl;
    EV<<"******slot length="<<m_slotLength<<endl;
    EV<<"******slot number="<<m_slotNum<<endl;

    m_appQueue.setName("AppQueue");
}

//��ʼ��ͳ����
void CsaHostMac::initStatistic()
{
//TODO
}

//��ʼ������Ϣ
void CsaHostMac::initSelfMsg()
{
    m_selfMsgSendData=new cMessage("SelfMsgSendData");
    scheduleAt(0,m_selfMsgSendData);
}

//������Ϣ
void CsaHostMac::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        EV_DEBUG<<this->getFullName()<<" received a self message: "<<msg->getFullName()<<endl;
        handleSelfMsg(msg);
    }
    else
    {
        EV_DEBUG<<this->getFullName()<<" received a non-self message: "<<msg->getFullName()<<endl;
        handleNonSelfMsg(msg);
    }
}

//��������Ϣ
void CsaHostMac::handleSelfMsg(cMessage *msg)
{
    if(msg==m_selfMsgSendData)
    {
        EV_DEBUG<<"A self message arrived: "<<msg->getFullName()<<", and will be schedule next at time:"<<(simTime()+m_slotNum*m_slotLength)<<endl;
        scheduleAt(simTime()+m_slotNum*m_slotLength,m_selfMsgSendData);
        handleSelfMsgSendData(msg);
    }
    else
    {
        if(msg->getKind()==PacketKind_Self_CSA_Host_Data)
        {
            msg->setKind(PacketKind_Host_Data);
            sendDirect(msg,getPropagationSlot()*m_slotLength,0,m_ap->gate("in"));
            EV_DEBUG<<msg->getFullName()<<" has been sent to ap."<<endl;
        }
    }
}

//���������Ϣ
void CsaHostMac::handleNonSelfMsg(cMessage *msg)
{
//��Ϣ���ͣ�Ӧ�ò���Ϣ
    switch(msg->getKind())
    {
    case PacketKind_Application:
    {
        //����Ӧ�ò���Ϣ
        EV_DEBUG<<m_parent->getFullName()<<" received a packet from "<<msg->getSenderModule()->getFullName()<<endl;
        handleAppMsg(msg);
        break;
    }
    default:
    {
        throw cRuntimeError("CSA: Host received a wrong type message.");
    }
    }
}

//����Ӧ�ò���Ϣ
void CsaHostMac::handleAppMsg(cMessage *msg)
{
    if(m_appQueue.getLength()==QUEUE_CAPACITY)
    {
        EV_DEBUG<<"AppQueue is full, the new message has been deleted."<<endl;
        delete msg;
    }
    else
    {
        m_appQueue.insert(msg);
        EV_DEBUG<<msg->getFullName()<<" has been inserted into appQueue."<<endl;
        EV_DEBUG<<"AppQueue's length now is: "<<m_appQueue.getLength()<<endl;
    }
}

//�����������ݡ�����Ϣ
void CsaHostMac::handleSelfMsgSendData(cMessage *msg)
{
    if(getDistance()<m_communicationRange)
    {
        //��������
        sendData();
    }
    else
    {
        EV<<m_parent->getFullName()<<" is out of ap communication range."<<endl;
        m_appQueue.clear();
    }
}

//��������
void CsaHostMac::sendData()
{
//ѡ��һ֡��Ҫ�����ٸ����ݰ�->ÿ�����ݰ����ٸ�����->ѡ��ʱ϶->����
    //���η��͵����ݰ�����
    int numOfPks=getNumOfTransmittingPks();
    EV_DEBUG<<numOfPks<<" application packets will be sent to "<<m_ap->getFullName()<<endl;

    //��һ����������ʶ�������������ݰ���ʱ϶
    int propagationSlots=getPropagationSlot();
    EV_DEBUG<<"Propagation slots is: "<<propagationSlots<<endl;

    bool AvaiableSlot[m_slotNum];
    for(int i=0;i<m_slotNum;i++)
    {
        if(i<(m_slotNum-propagationSlots))
        {
            AvaiableSlot[i]=true;
        }
        else
        {
            AvaiableSlot[i]=false;
        }
    }
    for(int i=0;i<m_slotNum;i++)
    {
        EV_DEBUG<<AvaiableSlot[i]<<' ';
        if((i+1)%100==0)
        {
            EV_DEBUG<<endl;
        }
    }

    int randomSlotIndex;
    while((numOfPks!=0)&&(m_appQueue.getLength()!=0))
    {
        //CsaHostPk *appMsg=dynamic_cast<CsaHostPk *>(m_appQueue.pop());
        cMessage *appMsg=dynamic_cast<cMessage *>(m_appQueue.pop());
        EV_DEBUG<<"A packet is popped: "<<appMsg->getFullName()<<endl;

        CsaHostPk *appPk=new CsaHostPk();
        appPk->setName(appMsg->getFullName());
        delete appMsg;
        EV_DEBUG<<"appMsg is converted to CsaHostPk: "<<appPk->getFullName()<<endl;


        //������Ҫ���Ͷ��ٸ�����
        int numOfRepetions=getNumOfRepetions();
        EV_DEBUG<<numOfRepetions<<" repetitions are generated."<<endl;

        vector<int> slotIndexVec;
        slotIndexVec.clear();
        //��������Щʱ϶���ͣ��ҵ�һ���ͷ���
        for(int i=0;i<numOfRepetions;i++)
        {
            randomSlotIndex=intrand(m_slotNum-propagationSlots);
            while(!AvaiableSlot[randomSlotIndex])
            {
                randomSlotIndex=intrand(m_slotNum-propagationSlots);
            }
            AvaiableSlot[randomSlotIndex]=false;
            EV_DEBUG<<randomSlotIndex<<" slot is selected."<<endl;
            slotIndexVec.push_back(randomSlotIndex);
        }
        //���
        for(int i=0;i<m_slotNum;i++)
        {
            EV_DEBUG<<AvaiableSlot[i]<<' ';
            if((i+1)%100==0)
            {
                EV_DEBUG<<endl;
            }
        }
        //�������ݰ�
        appPk->setPkId(appPk->getId());
        appPk->setHostId(m_parent->getId());
        appPk->setHostPath(m_parent->getFullPath().c_str());
        appPk->setNumOfRepetions(numOfRepetions);
        appPk->setPoint(slotIndexVec);
        appPk->setIsRecovery(false);
        //�������ݰ�
        for(int i=0;i<slotIndexVec.size();i++)
        {
            CsaHostPk *newDup=appPk->dup();
            newDup->setSlotIndex(slotIndexVec[i]);
            newDup->setKind(PacketKind_Self_CSA_Host_Data);
            scheduleAt(simTime()+slotIndexVec[i]*m_slotLength,newDup);
            EV_DEBUG<<"A CsaHostPk will be sent to AP at time: "<< simTime()+slotIndexVec[i]*m_slotLength<<endl;
        }

        EV_DEBUG<<"numOfpks="<<numOfPks<<endl;
        numOfPks--;
    }
}



//����Ҫ���Ͷ��ٸ����ݰ�
int CsaHostMac::getNumOfTransmittingPks()
{
    int numOfPks=0;
    if(m_appQueue.getLength()==0)
    {
        numOfPks=0;
    }
    else
    {
        numOfPks=13;
    }
    return numOfPks;
}

//����ÿ�����ݰ��ĸ�����
int CsaHostMac::getNumOfRepetions()
{
    //�ֲ�������0.5631x3+0.0436x3+0.3933x5
    int numOfRepetion=0;
    double dRandom=dblrand();
    if(dRandom<0.5631)
    {
        numOfRepetion=2;
    }
    else
    {
        if(dRandom<0.6067)
        {
            numOfRepetion=3;
        }
        else
        {
            numOfRepetion=5;
        }
    }
    return numOfRepetion;
}



//��������
//��ȡ��ǰλ��
Coord CsaHostMac::getCurrentPosition()
{
    cModule *mdMobility=m_parent->getSubmodule("mobility");
    IMobility *mdMovingMobility=dynamic_cast<IMobility *>(mdMobility);
    return mdMovingMobility->getCurrentPosition();
}
//��ȡAPλ��
Coord CsaHostMac::getApPosition()
{
    cModule *mdMobilityOfAp=m_ap->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfAp=dynamic_cast<IMobility *>(mdMobilityOfAp);
    return mdMovingMobilityOfAp->getCurrentPosition();
}
//�����AP�ľ���
double CsaHostMac::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdAp=getApPosition();
    Coord cdDistance=cdHost-cdAp;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);
}
//����ʱ϶���ȣ��������ߵ紫�������ʱ϶��
int CsaHostMac::getPropagationSlot()
{
    double dDistance=getDistance();
    simtime_t stPropagationTime=dDistance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_slotLength);
}

}



