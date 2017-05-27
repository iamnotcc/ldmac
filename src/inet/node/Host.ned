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
import ldmac.inet.application.IPkGenerator;
import ldmac.inet.nic.contract.IHostMac;



module Host
{
    parameters:
        @display("i=device/airplane_s;bgb=152,189");

        //移动模块参数
        string mobilityType = default("RandomWPMobility");
        //应用层参数
        string appType = default("BurstGenerator");
        //mac层参数
        string macType = default("");

    gates:
        input in @directIn;

    submodules:
        mobility: <mobilityType> like IMobility {
            @display("p=29,42");
        }
        app: <appType> like IPkGenerator {
            @display("p=77,50");
        }
        mac: <macType> like IHostMac {
            @display("p=77,129");
        }

    connections:
        in --> mac.inFromHost;
        app.out --> mac.inFromApp;

}
