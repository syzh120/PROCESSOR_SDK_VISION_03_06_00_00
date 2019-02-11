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

/**
*  \file tfdtp_api.h
*
*  \brief TFDTP APIs header file.
*/

#ifndef TFDTP_API_H_
#define TFDTP_API_H_

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>
#include <stdbool.h>
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

#define closesocket(s) close(s)
/* these are not needed for Linux */
#define socketsShutdown()
#define socketsStartup()
typedef int SOCKET;
#else
#include <winsock2.h>
#endif
#include <ti/nsp/drv/inc/tfdtp_types.h>

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define DIR_TX 0
#define DIR_RX 1
#define MAX_PENDING_PACKETS 5
#define MAX_DROPPED_PACKETS 5
#define ETH_MAX_THROUGHPUT 1000

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct
{
    char destIpAddr[16];
    uint32_t cmdPort;
    uint32_t udpPort;
    uint16_t  chId;
    uint32_t direction;
    uint32_t frameSize;
    uint32_t thruput;
    uint32_t numRxFrame;
    uint32_t enableDataValFlag;
} TFDTP_CreateParams;

typedef struct
{
    /*! Number of stream data packets successfully parsed and processed by TFDTP stack */
    uint32_t packetCnt;
    /*! Number of ignored data packets that are dropped by TFDTP stack */
    uint32_t ignoredPacketCnt;
    /*! Number of parser errors encountered by TFDTP stack */
    uint32_t errorCnt;
    /*! Number of control packets received */
    uint32_t controlPacketCnt;
    /*! Number of packets tagged with a frame ID which does not refer to any registered listener */
    uint32_t unexpectedFrameID;
    /*! Number of packets with zero size or bigger than the maximum allowed TFDTP payload */
    uint32_t invalidPacketSizeError;
    /*! Number of times the parser encountered an out-of-sequence packet (either from packet loss or truly out of sequence) */
    uint32_t outOfSequenceError;
    /*! Number of times the parser could not find a free buffer to write into */
    uint32_t noBuffersAvailable;
    /*! Number of times the parser ran out of buffer space while assembling an output frame */
    uint32_t insufficientSizeError;
    /*! Number of times the parser encountered a SOF marker before an EOF marker */
    uint32_t missedEOFError;
    /*! Number of times the parser encountered a SOF marker */
    uint32_t numSOFMarkers;
    /*! Number of times the parser encountered a EOF marker */
    uint32_t numEOFMarkers;
    /*! Number of times the data check failed for receive */
    uint32_t dataMatchFailCnt;
    /*! Number of partial frames received */
    uint32_t partialFrameCnt;
} TFDTP_stats;

typedef struct
{
    char        *bufAddr;
    uint32_t    bufState;
    uint32_t    bufSize;
    uint32_t    frameSize;
    uint32_t    flags;
    uint32_t    frameId;
} TFDTP_Buffer;

typedef struct
{
    SOCKET          tcpSocket;
    SOCKET          udpSocket;
    struct addrinfo *pUdpIpAddr;
    fd_set          fds;
    uint32_t        maxPayloadSize;
    uint16_t         chanId;
    uint32_t        thruput;
    uint32_t        numRxFrame;
    uint32_t        enableDataValFlag;
    uint16_t        txFrameId;
    uint16_t        rxFrameCnt;
    TFDTP_Buffer    curBufDes;
    TFDTP_Buffer    pendBufDes;
    uint32_t        pendingPackets;
    TFDTP_stats     stats;
} TFDTP_Obj;

/*---------------------------------------------------------------------------*\
|                          Global Function Prototypes                         |
\*---------------------------------------------------------------------------*/

TFDTP_Obj *TFDTP_open(TFDTP_CreateParams *pParam);
void TFDTP_close(TFDTP_Obj *pObj);
int TFDTP_send(TFDTP_Obj *pObj);
int TFDTP_recv(TFDTP_Obj *pObj);
int TFDTP_setChConfig(TFDTP_Obj *pObj, char *pSelfIpAddr, uint32_t retry);

#endif /* TFDTP_API_H_ */
