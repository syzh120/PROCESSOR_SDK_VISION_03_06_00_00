/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
#ifndef _NETWORK_API_H_
#define _NETWORK_API_H_

#include <osa.h>
#include <unistd.h>
#include <strings.h>
#include <tfdtp_api.h>

#if defined(linux)
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define getError() (errno)
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define closesocket(s) close(s)
/* these are not needed for Linux */
#define socketsShutdown()
#define socketsStartup()
typedef int SOCKET;
#else
#include <winsock.h>
#define getError() WSAGetLastError()
#define socketsShutdown() WSACleanup()
#define sleep(x) Sleep(1000 * x)
#endif

typedef struct {

    SOCKET clientSocketId;
    UInt32 serverPort;
    char ipAddr[32];
    TFDTP_Obj *pTfdtpObj;

} Network_SockObj;


typedef enum {
    TFDTP_TRANSMIT_OK      = 0x1U,
    TFDTP_TRANSMIT_FAIL    = 0x2U,
    TFDTP_TRANSMIT_INVALID = 0xFFU
} NetworkTfdtp_TransmitAck;


/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

int Network_connect(Network_SockObj *pObj, char *ipAddr, UInt32 port);
int Network_close(Network_SockObj *pObj);
int Network_read(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize);
int Network_readString(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 maxDataSize);
int Network_write(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize);
int Network_init();
int Network_deInit();

int Network_tfdtpOpen(Network_SockObj *pObj, TFDTP_CreateParams *pParam);
int Network_tfdtpRead(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize);
int Network_tfdtpWrite(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize);
int Network_tfdtpSendParams(Network_SockObj *pObj, char *myIpAddr, UInt32 retry);
int Network_tfdtpSendAck(Network_SockObj *pObj, UInt32 ack);
UInt32 Network_tfdtpWaitAck(Network_SockObj *pObj);

#endif
