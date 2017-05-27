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
	    //参数
	    //时隙长度
	    double slotTime @unit(s);
	    //一帧的时隙个数
	    int slotNum;
	    //用于确认的时隙个数
	    int ackSlotNum;
		
		//统计
	    //成功发送出去的包平均排队时间
	    @signal[queueTime](type=simtime_t);
	    @statistic[queueTime](title="queueTime";source=queueTime;record=mean);
	    //丢弃的包的个数
	    @signal[discardPkCount](type=long);
	    @statistic[discardPkCount](title="discardPkCount";source=discardPkCount;record=count;interpolationmode=node);	    
	    //统计发送了多少个数据包
	    @signal[sendPkCount](type=long);
	    @statistic[sendPkCount](title="pkCount";source=sendPkCount;record=count;interpolationmode=node); 
	    
	    @class(CsaHostMac);   
	gates:
	    input inFromHost;
	    input inFromApp;
}
