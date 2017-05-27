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

package ldmac.simulations.test.cApplicationTest;
import ldmac.inet.mobility.contract.IMobility;
import ldmac.inet.application.IPkGenerator;
//���Բ�����
import ldmac.inet.common.queue.Sink;


module Host
{
    parameters:
        @display("i=device/airplane_s");

        //�ƶ�ģ�����
        string mobilityType = default("RandomWPMobility");
        //Ӧ�ò����
        string appType = default("BurstGenerator");

    submodules:
        mobility: <mobilityType> like IMobility {
            @display("p=20,42");
        }
        app: <appType> like IPkGenerator {
            @display("p=104,125");
        }

        //���Բ�����
        sink: Sink {
            @display("p=104,50");
        }
	connections:
	    app.out --> sink.in++;
}