/*
* Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

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
#include "../../../packages/ti/nsp/drv/inc/tfdtp_types.h"

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
    uint32_t   bufState;
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
    TFDTP_Buffer    bufDes[2];
    uint32_t        curBufIndex;
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

#endif /* TFDTP_API_H_ */
