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

package ldmac.inet.node;
import ldmac.inet.mobility.contract.IMobility;
import ldmac.inet.nic.contract.IApMac;


module Ap
{
    parameters:
        @display("i=device/antennatower_l;bgb=178,169");

        //移动模块参数
        string mobilityType = default("StationaryMobility");
        //mac层参数
        string macType = default("");

    gates:
        input in @directIn;

    submodules:
        mobility: <mobilityType> like IMobility {
            @display("p=24,24");
        }
        mac: <macType> like IApMac {
            @display("p=66,92");
        }

    connections:
        in --> mac.inFromAp;
}
