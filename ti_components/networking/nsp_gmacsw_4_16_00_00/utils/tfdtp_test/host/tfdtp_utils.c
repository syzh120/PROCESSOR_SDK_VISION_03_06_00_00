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
*  \file tfdtp_utils.c
*
*  \brief TFDTP utils source file.
*/


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"
#include "tfdtp_api.h"
#include "../common/test_common.h"
#include "tfdtp_test_client.h"
#include "tfdtp_utils.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Function Definitions                        |
\*---------------------------------------------------------------------------*/

#if defined(__MINGW32__) || defined(_MSC_VER)
int my_gettimeofday(struct timeval * tp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

void socketsStartup()
{
    WORD         wVersionRequested;
    WSADATA      wsaData;

    wVersionRequested = MAKEWORD(1, 1);
    if (WSAStartup(wVersionRequested, &wsaData)) {
        printf("\r\nUnable to initialize WinSock for host info");
        exit(EXIT_FAILURE);
    }
}
#endif


void print_stats(App_Obj *pAppObj)
{
    print_loadStats(pAppObj);
    print_tfdtpStats(pAppObj);
#if (1 == PRINT_HW_STATS)
    print_ethHWErrors(pAppObj);
    print_ethHWStats(pAppObj);
#endif
}

void print_tfdtpStats(App_Obj *pAppObj)
{
    struct tfdtp_stats stats;
    int status = EXIT_SUCCESS;
    uint32_t recvBuf[MAX_CMD_LENGTH], fullFrameCnt;

    printf("Target Load Info\n");
    /* Send get load command */
    uint32_t cmdParam = 0;
    status = TFDTP_TestClient_sendCmd(pAppObj->tfdtpObj, TEST_CMD_GET_TFDTP_STATS, &cmdParam);
    status = recv(pAppObj->tfdtpObj->tcpSocket, (char *)recvBuf, (size_t)MAX_CMD_LENGTH, 0);
    if(0 < status)
    {
        fullFrameCnt                    = (htonl(recvBuf[0]));
        stats.packetCount                 = (htonl(recvBuf[1]));
        stats.ignoredPacketCnt          = (htonl(recvBuf[2]));
        stats.errorCnt                  = (htonl(recvBuf[3]));
        stats.invalidPacketSizeError    = (htonl(recvBuf[4]));
        stats.outOfSequenceError        = (htonl(recvBuf[5]));
        stats.noBuffersAvailable        = (htonl(recvBuf[6]));
        stats.insufficientSizeError     = (htonl(recvBuf[7]));
#if 0U
        /* Not supported currently */
        stats.missedEOFError            = (htonl(recvBuf[8]));
        stats.numSOFMarkers             = (htonl(recvBuf[9]));
        stats.numEOFMarkers             = (htonl(recvBuf[10]));
#endif
    }

    printf("TFDTP Target statistics\n");
    printf("\tTotal Frames                 :  %u\n", fullFrameCnt);
    printf("\tFrame Errors                 :  %u\n", stats.errorCnt);
    printf("\tTotal Packets                :  %u\n", stats.packetCount);
    printf("\tIgnored packets              :  %u\n", stats.ignoredPacketCnt);
    printf("\tInvalidPacketSizeError       :  %u\n", stats.invalidPacketSizeError);
    printf("\tOutOfSequenceError           :  %u\n", stats.outOfSequenceError);
    printf("\tBuffer Underflow             :  %u\n", stats.noBuffersAvailable);
    printf("\tInsufficientSizeError        :  %u\n", stats.insufficientSizeError);

    /* Clear server stats now that we have printed */
    status = TFDTP_TestClient_sendCmd(pAppObj->tfdtpObj, TEST_CMD_CLEAR_TFDTP_STATS, &cmdParam);
}

void print_ethHWErrors(App_Obj *pAppObj)
{
    struct EthernetHWErrors ethHwErrors;
    int status = EXIT_SUCCESS;
    uint32_t recvBuf[MAX_CMD_LENGTH];

    printf("Target GMAC HW Errors Info\n");
    /* Send get load command */
    status = TFDTP_TestClient_sendCmd(pAppObj->tfdtpObj, TEST_CMD_GET_HW_ERRORS, NULL);
    status = recv(pAppObj->tfdtpObj->tcpSocket, (char *)recvBuf, (size_t)MAX_CMD_LENGTH, 0);
    if(0 < status)
    {
        ethHwErrors.RxSOFOverruns     = (htonl(recvBuf[0]));
        ethHwErrors.RxMOFOverruns     = (htonl(recvBuf[1]));
        ethHwErrors.RxDMAOverruns     = (htonl(recvBuf[2]));
        ethHwErrors.RxCRCErrors       = (htonl(recvBuf[3]));
        ethHwErrors.RxAlignCodeErrors = (htonl(recvBuf[4]));
        ethHwErrors.RxOversized       = (htonl(recvBuf[5]));
        ethHwErrors.RxJabber          = (htonl(recvBuf[6]));
        ethHwErrors.RxUndersized      = (htonl(recvBuf[7]));
        ethHwErrors.RxFragments       = (htonl(recvBuf[8]));
    }

    printf("\tEth Errors:RxSOFOverruns      :%u\n", ethHwErrors.RxSOFOverruns);
    printf("\tEth Errors:RxMOFOverruns      :%u\n", ethHwErrors.RxMOFOverruns);
    printf("\tEth Errors:RxDMAOverruns      :%u\n", ethHwErrors.RxDMAOverruns);
    printf("\tEth Errors:RxCRCErrors        :%u\n", ethHwErrors.RxCRCErrors);
    printf("\tEth Errors:RxAlignCodeErrors  :%u\n", ethHwErrors.RxAlignCodeErrors);
    printf("\tEth Errors:RxOversized        :%u\n", ethHwErrors.RxOversized);
    printf("\tEth Errors:RxJabber           :%u\n", ethHwErrors.RxJabber);
    printf("\tEth Errors:RxUndersized       :%u\n", ethHwErrors.RxUndersized);
    printf("\tEth Errors:RxFragments        :%u\n", ethHwErrors.RxFragments);
}

void print_ethHWStats(App_Obj *pAppObj)
{
    struct EthernetHWStats stats;
    int status = EXIT_SUCCESS;
    uint32_t recvBuf[MAX_CMD_LENGTH];

    printf("Target GMAC HW Stats\n");
    /* Send get load command */
    status = TFDTP_TestClient_sendCmd(pAppObj->tfdtpObj, TEST_CMD_GET_HW_STATS, NULL);
    status = recv(pAppObj->tfdtpObj->tcpSocket, (char *)recvBuf, (size_t)MAX_CMD_LENGTH, 0);

    if(0 < status)
    {
        stats.RxGoodFrames  = (htonl(recvBuf[0]));
        stats.RxBCastFrames = (htonl(recvBuf[1]));
        stats.RxMCastFrames = (htonl(recvBuf[2]));
        stats.RxPauseFrames = (htonl(recvBuf[3]));
        stats.RxOctets      = (htonl(recvBuf[4]));
        stats.TxGoodFrames  = (htonl(recvBuf[5]));
        stats.TxBCastFrames = (htonl(recvBuf[6]));
        stats.TxMCastFrames = (htonl(recvBuf[7]));
        stats.TxPauseFrames = (htonl(recvBuf[8]));
        stats.TxOctets      = (htonl(recvBuf[9]));
    }

    printf("\tEth Stats:RxGoodFrames   :%u\n", stats.RxGoodFrames);
    printf("\tEth Stats:RxBCastFrames  :%u\n", stats.RxBCastFrames);
    printf("\tEth Stats:RxMCastFrames  :%u\n", stats.RxMCastFrames);
    printf("\tEth Stats:RxPauseFrames  :%u\n", stats.RxPauseFrames);
    printf("\tEth Stats:RxOctets       :%u\n", stats.RxOctets);
    printf("\tEth Stats:TxGoodFrames   :%u\n", stats.TxGoodFrames);
    printf("\tEth Stats:TxBCastFrames  :%u\n", stats.TxBCastFrames);
    printf("\tEth Stats:TxMCastFrames  :%u\n", stats.TxMCastFrames);
    printf("\tEth Stats:TxPauseFrames  :%u\n", stats.TxPauseFrames);
    printf("\tEth Stats:TxOctets       :%u\n", stats.TxOctets);

    /* Clear server stats now that we have printed */
    status = TFDTP_TestClient_sendCmd(pAppObj->tfdtpObj, TEST_CMD_CLEAR_HW_STATS, NULL);
}

void print_loadStats(App_Obj *pAppObj)
{
    struct LoadStats stats;
    int status = EXIT_SUCCESS;
    uint32_t recvBuf[MAX_CMD_LENGTH];

    printf("Target Load Info\n");
    /* Send get load command */
    status = TFDTP_TestClient_sendCmd(pAppObj->tfdtpObj, TEST_CMD_GET_LOAD_INFO, NULL);
    status = recv(pAppObj->tfdtpObj->tcpSocket, (char *)recvBuf, (size_t)MAX_CMD_LENGTH, 0);
    if(0 < status)
    {
        stats.cpuLoad           = (htonl(recvBuf[0]));
        stats.hwiLoad           = (htonl(recvBuf[1]));
        stats.tfdtp2nspRxLoad   = (htonl(recvBuf[2]));
        stats.tfdtp2nspTxLoad   = (htonl(recvBuf[3]));
    }
    printf("\tCPU Load         :  %u\n", stats.cpuLoad);
    printf("\tHWI Load         :  %u\n", stats.hwiLoad);
    printf("\tTFDTP Rx Load    :  %u\n", stats.tfdtp2nspRxLoad);
    printf("\tTFDTP Tx Load    :  %u\n", stats.tfdtp2nspTxLoad);
}

void print_appStats(App_Obj *pAppObj)
{
    printf("TFDTP Host Receiver statistics\n");
    printf("\tTotal Packets                :  %u\n", pAppObj->tfdtpObj->stats.packetCnt);
    printf("\tIgnored packets              :  %u\n", pAppObj->tfdtpObj->stats.ignoredPacketCnt);
    printf("\tMissed Frames                :  %u\n", pAppObj->tfdtpObj->stats.errorCnt);
    printf("\tPartial Frames received      :  %u\n", pAppObj->tfdtpObj->stats.partialFrameCnt);
    printf("\tData Check Fail              :  %u\n", pAppObj->tfdtpObj->stats.dataMatchFailCnt);
    printf("\tUnexpected FrameId error(RX) :  %u\n", pAppObj->tfdtpObj->stats.unexpectedFrameID);
    printf("\tInvalidPacketSizeError(RX)   :  %u\n", pAppObj->tfdtpObj->stats.invalidPacketSizeError);
    printf("\tOutOfSequenceError(RX)       :  %u\n", pAppObj->tfdtpObj->stats.outOfSequenceError);
    printf("\tInsufficientSizeError(RX)    :  %u\n", pAppObj->tfdtpObj->stats.insufficientSizeError);
    printf("\tmissedEOFError(RX)           :  %u\n", pAppObj->tfdtpObj->stats.missedEOFError);
    printf("\tnumSOFMarkers(RX)            :  %u\n", pAppObj->tfdtpObj->stats.numSOFMarkers);
    printf("\tnumEOFMarkers(RX)            :  %u\n", pAppObj->tfdtpObj->stats.numEOFMarkers);
}
