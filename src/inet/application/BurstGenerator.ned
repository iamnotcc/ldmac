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

package ldmac.inet.application;

simple BurstGenerator like IPkGenerator
{
	parameters:
	    
	    double startTime @unit("s")=default(0s);
	    
	    volatile double burstInterval @unit("s")=default(1s);
	    volatile int burstNum=default(10);
	    volatile int packetLength @unit("b");
	    
	    @signal[appPkCount](type=long);
	    @statistic[appPkCount](title="appPkCount";source=appPkCount;record=count;interpolationmode=node);
	    
	    //统计异常情况
	    @signal[errorCount](type=long);
	    @statistic[errorCount](title="errorCount";source=errorCount;record=count;interpolationmode=node);
	    
	    
	    @display("i=block/source");
	    
	    @class(BurstGenerator);
	    
	gates:
	    output out;
	    
}

