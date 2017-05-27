//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ldmac.inet.linklayer.csa;
import ldmac.inet.linklayer.contract.IHostMac;

simple CsaHostMac like IHostMac
{
	parameters:
	    @display("i=block/ifcard");
	    //����
	    //ʱ϶����
	    double slotTime @unit(s);
	    //һ֡��ʱ϶����
	    int slotNum;
	    //����ȷ�ϵ�ʱ϶����
	    int ackSlotNum;
		
		//ͳ��
	    //�ɹ����ͳ�ȥ�İ�ƽ���Ŷ�ʱ��
	    @signal[queueTime](type=simtime_t);
	    @statistic[queueTime](title="queueTime";source=queueTime;record=mean);
	    //�����İ��ĸ���
	    @signal[discardPkCount](type=long);
	    @statistic[discardPkCount](title="discardPkCount";source=discardPkCount;record=count;interpolationmode=node);	    
	    //ͳ�Ʒ����˶��ٸ����ݰ�
	    @signal[sendPkCount](type=long);
	    @statistic[sendPkCount](title="pkCount";source=sendPkCount;record=count;interpolationmode=node); 
	    
	    @class(CsaHostMac);   
	gates:
	    input inFromHost;
	    input inFromApp;
}