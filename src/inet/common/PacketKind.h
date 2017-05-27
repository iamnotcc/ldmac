/*
 * PacketKind.h
 *
 *  Created on: 2016Äê11ÔÂ23ÈÕ
 *      Author: wh
 */

#ifndef COMMON_PACKETKIND_H_
#define COMMON_PACKETKIND_H_

namespace inet
{
enum PacketKind
{
PacketKind_Application = 100,

PacketKind_Host_Request=101,

PacketKind_Host_Data =102,

PacketKind_Ap_ACK=103,

PacketKind_Self_CSA_Host_Data=104,

};
}



#endif /* COMMON_PACKETKIND_H_ */
