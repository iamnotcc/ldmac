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

package ldmac.inet.nic.tdma;
import ldmac.inet.nic.contract.IHostMac;


simple TdmaHostMac like IHostMac
{
	parameters:
	    @display("i=block/ifcard");
	    
	    //参数
	    //发送速率
	    double txRate @unit(bps);
	    //时隙长度
	    double slotLength @unit("s");
	    //每一帧时隙个数
	    int slotNum;
	    //用于发送req的时隙数
	    int reqSlotNum;
	    //req数据包长度
	    int reqPktLength @unit(b);
	    //通信范围
	    double communicationRange @unit(m);
	    
	    //统计
	    //成功发送出去的包平均排队时间
	    @signal[queueTime](type=simtime_t);
	    @statistic[queueTime](title="queueTime";source=queueTime;record=mean);
	    //丢弃的包的个数
	    @signal[discardPkCount](type=long);
	    @statistic[discardPkCount](title="discardPkCount";source=discardPkCount;record=count;interpolationmode=node);	    
	    //统计发送了多少个数据包
	    @signal[sentPkCount](type=long);
	    @statistic[sentPkCount](title="pkCount";source=sentPkCount;record=count;interpolationmode=node);

	    
	    @class(TdmaHostMac);
	    
	 gates:
	     input inFromApp;
	     input inFromHost;
}
