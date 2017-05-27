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

package ldmac.inet.nic.csa;
import ldmac.inet.nic.contract.IApMac;

simple CsaApMac like IApMac
{
	parameters:
	    double slotLength @unit(s);
	    int slotNum;
	    @display("i=block/ifcard");
	    @class(CsaApMac);
	    
	gates:
	    input inFromAp;
	    
}