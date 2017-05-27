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

package ldmac.inet.nic.aloha;
import ldmac.inet.nic.contract.IApMac;

simple AlohaApMac like IApMac
{
	parameters:
	    
	    double slotLength @unit(s);
	    @display("i=block/ifcard");
	    @signal[channelState](type="long");
	    @signal[receiveBegin](type="long");
	    @signal[receive](type="long");
	    @signal[collision](type="long");
	    @signal[collisionLength](type="simtime_t");
	    	    
	    //统计
	    //统计总共接收到的数据包数
	    @signal[pkCount](type=long);
	    @statistic[pkCount](title="pkCount";source=pkCount;record=count;interpolationmode=node);
	    
	gates:
	    input inFromAp;

	    
}