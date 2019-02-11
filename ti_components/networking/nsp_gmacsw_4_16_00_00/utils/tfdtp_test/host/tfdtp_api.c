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
*  \file tfdtp_api.c
*
*  \brief TFDTP API source file.
*/

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "sockets.h"
#include "tfdtp_api.h"
#include "tfdtp_utils.h"

#ifdef __unix__
# include <unistd.h>
#define CLOCK CLOCK_MONOTONIC
#elif defined _WIN32
#define WIN32_LEAN_AND_MEAN
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#include <math.h>
#include "../common/test_common.h"

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
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                           Interface Function Definitions                        |
\*---------------------------------------------------------------------------*/
TFDTP_Obj *TFDTP_open(TFDTP_CreateParams * pParam)
{
    TFDTP_Obj *pObj = NULL;
    char portString[10];
    struct addrinfo hints;
    struct addrinfo *results = NULL;
    int value, i;
    int status = 0;
    struct sockaddr_in s, cmdserver;

    uint32_t optValue;
    uint32_t optLen = sizeof (uint32_t);

    if (pParam != NULL)
    {
        pObj = malloc(sizeof(TFDTP_Obj));
        if (pObj == NULL)
        {
            fprintf(stderr, "Failed to allocate TFDTP_Obj\n");
        }
        else
        {
            memset(pObj, 0, sizeof(TFDTP_Obj));

            pObj->chanId = pParam->chId;
            pObj->thruput = pParam->thruput;
            pObj->numRxFrame = pParam->numRxFrame;
            if(true == pParam->enableDataValFlag)
            {
                pObj->enableDataValFlag = pParam->enableDataValFlag;
            }

            /* convert the port into string format in order to pass it to getaddrinfo */
            sprintf(portString, "%d", pParam->udpPort);

            /* initialize sockets environment */
            socketsStartup();

            /* Create UDP socket */
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_DGRAM;
            hints.ai_protocol = IPPROTO_UDP;

            /*
            * getaddrinfo() fills in the results struct for us appropriately
            * depending on whether the IP address is v4 or v6
            *
            */
            value = getaddrinfo(pParam->destIpAddr, portString, &hints, &results);

            if (value != 0)
            {
                fprintf(stderr, "getaddrinfo failed: %d\n", value);
                if (value == -2 || value == 11004)
                {
                    fprintf(stderr, "unrecognized IP address\n");
                }
                status = -1;
                goto OPEN_EXIT;
            }

            pObj->pUdpIpAddr = results;

            /* set max UDP payload accordingly for IPv4/IPv6 to avoid fragmentation */
            if (results->ai_family == AF_INET)
            {
                pObj->maxPayloadSize = TFDTP_MAX_STREAM_PAYLOAD_SIZE;
            }
            else if (results->ai_family == AF_INET6)
            {
                fprintf(stderr, "IPv6 address not supported!\n");
                status = -1;
                goto OPEN_EXIT;
            }
            else
            {
                fprintf(stderr, "error: unknown protocol family: %d\n",
                    results->ai_family);
                status = -1;
                goto OPEN_EXIT;
            }

            /* create UDP socket. ai_family determined for us via getaddrinfo() call */
            if ((pObj->udpSocket = socket(results->ai_family, results->ai_socktype, IPPROTO_UDP)) < 0)
            {
                fprintf(stderr, "Failed to open UDP socket (%d)\n", getError());
                freeaddrinfo(results);
                status = -1;
                goto OPEN_EXIT;
            }

            if (pParam->direction == DIR_RX)
            {
                s.sin_family = results->ai_family;
                s.sin_addr.s_addr = INADDR_ANY;
                s.sin_port = htons(pParam->udpPort);
                /* For RX, socket should be bound to ip address */
                status = bind(pObj->udpSocket, (struct sockaddr *) &s, sizeof(s));
                if (status == -1)
                {
                    fprintf(stderr, "bind failed with error: %d\n", getError());
                    goto OPEN_EXIT;
                }
#if __unix__
                struct timeval tv;
                tv.tv_sec = 0;
                tv.tv_usec = 500000;
#else
                char tv;
                /* timeout in miliseconds */
                tv = 200;
#endif
                if (setsockopt(pObj->udpSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(tv)) < 0)
                {
                    fprintf(stderr, "setsockopt for SO_RCVTIMEO failed with error: %u\n", getError());
                }

                optValue = pParam->frameSize*2;
                status = setsockopt(pObj->udpSocket, SOL_SOCKET, SO_RCVBUF, (char *)&optValue, optLen);
                if (status == -1)
                {
                    fprintf(stderr, "setsockopt for SO_RCVBUF failed with error: %u\n", getError());
                    goto OPEN_EXIT;
                }
            }
            FD_ZERO(&pObj->fds);
            FD_SET(pObj->udpSocket, &pObj->fds);

            /* Create TCP socket and open TCP connection */
            if ((pObj->tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            {
                fprintf(stderr, "Failed to open TCP socket (%d)\n", getError());
                freeaddrinfo(results);
                status = -1;
                goto OPEN_EXIT;
            }

            cmdserver.sin_family = AF_INET;
            cmdserver.sin_addr.s_addr = inet_addr(pParam->destIpAddr);
            cmdserver.sin_port = htons(pParam->cmdPort);

            if (connect(pObj->tcpSocket, (struct sockaddr *) &cmdserver, sizeof(cmdserver)) == -1)
            {
                fprintf(stderr, "Failed to connect TCP (%d)\n", getError());
                status = -1;
                goto OPEN_EXIT;
            }

            /* Initialize buffer descriptor and Allocate buffers */
            for (i = 0; i < 2; i++)
            {
                pObj->bufDes[i].bufAddr = malloc(pParam->frameSize);
                if (pObj->bufDes[i].bufAddr == NULL)
                {
                    fprintf(stderr, "Failed to allocate frame buffer.\n");
                    status = -1;
                    goto OPEN_EXIT;
                }
                memset(pObj->bufDes[i].bufAddr, 0, pParam->frameSize);
                pObj->bufDes[i].bufSize = pParam->frameSize;
                if (pParam->direction == DIR_TX)
                {
                    pObj->bufDes[i].frameSize = pParam->frameSize;
                }
                else
                {
                    pObj->bufDes[i].frameSize = 0;
                }
                pObj->bufDes[i].flags = 0;
                pObj->bufDes[i].frameId = 0;
            }
        }
    }

OPEN_EXIT:
    if (status != 0)
    {
        TFDTP_close(pObj);
        pObj = NULL;
    }
    return pObj;
}

void TFDTP_close(TFDTP_Obj *pObj)
{
    int i;

    if (pObj->pUdpIpAddr)
    {
        freeaddrinfo(pObj->pUdpIpAddr);
    }
    if (pObj->udpSocket >= 0)
    {
        (void)closesocket(pObj->udpSocket);
    }
    if (pObj->tcpSocket >= 0)
    {
        (void)closesocket(pObj->tcpSocket);
    }
    socketsShutdown();

    for (i = 0; i < 2; i++)
    {
        if (pObj->bufDes[i].bufAddr)
        {
            free(pObj->bufDes[i].bufAddr);
        }
    }
    free(pObj);
}

int TFDTP_send(TFDTP_Obj *pObj)
{
    TFDTP_Buffer *pBuf = &pObj->bufDes[pObj->curBufIndex];
    tfdtp_packet_t txPacket;
    uint32_t payload_size = pObj->maxPayloadSize;
    uint32_t udelayPerPck;
    uint16_t seq_num;
    uint32_t c, k, frame_offset;
    int status = 0;
    int byte_sent = 0;

    /* Compute delay per packet for required throughput */
    /* For 1000Mbps throughput each packet takes 8 us to transmit (1000Mbps ->83000pck/s -> 83packets/ms ->1pck/12uS
     * so multiple by 12 to get delay val in micro second for req. throughput */
    udelayPerPck = (uint32_t)( (float)((float)ETH_MAX_THROUGHPUT/(float)pObj->thruput) * 12 );
    txPacket.header.channel_id = pObj->chanId;
#if (1 == DEBUG_PRINT)
    printf("Sending to channel channel_id = %d\n",txPacket.header.channel_id);
#endif
    txPacket.header.total_seq_num = (pBuf->frameSize + payload_size - 1) / payload_size;
    txPacket.header.frame_id = pObj->txFrameId;
#if (1 == DEBUG_PRINT)
    printf("Delay val = %d\n", udelayPerPck);
#endif
    for (c = 0; c < pBuf->bufSize; c += pBuf->frameSize)
    {
#if (1 == DEBUG_PRINT)
    printf("Frame id = %d, total seq no =%d\n", pObj->txFrameId, txPacket.header.total_seq_num);
#endif
        for (seq_num = 0, frame_offset = 0; seq_num < txPacket.header.total_seq_num; seq_num++, frame_offset += payload_size)
        {
            txPacket.header.flags = TFDTP_VER;
            txPacket.header.seq_num = seq_num;
            txPacket.header.frame_offset = frame_offset;
            if (seq_num == 0)
            {
                txPacket.header.flags |= TFDTP_SOF;
                uint32_t *dataPtr = (uint32_t*) &pBuf->bufAddr[0];
                for(k=0; k <TEST_DATA_SIZE; k+= 4)
                {
                    *dataPtr = ( pObj->txFrameId  + (TEST_DATA_PATTERN * k) );
                    dataPtr++;
                }
            }
            if (seq_num == (txPacket.header.total_seq_num - 1))
            {
                /* Remaining data in the file */
                payload_size = pBuf->frameSize - frame_offset;
                txPacket.header.flags |= TFDTP_EOF;
                uint32_t *dataPtr = (uint32_t *)(&pBuf->bufAddr[pBuf->frameSize]);
                for (k = 0; k < TEST_DATA_SIZE; k+= 4)
                {
                    dataPtr--;
                    *dataPtr = ( pObj->txFrameId + (TEST_DATA_PATTERN * k) );
                }
            }
            txPacket.header.length = payload_size;

            memcpy(&txPacket.payload, &pBuf->bufAddr[frame_offset], payload_size);
            /* Delay for flow control*/
#if __unix__
            /* The delay implementation using clock_gettime */
            struct timespec reqStart, reqEnd;
            double elapsed;
            clock_gettime(CLOCK, &reqStart);
            do
            {
                clock_gettime(CLOCK, &reqEnd);
                elapsed = ( reqEnd.tv_sec - reqStart.tv_sec ) / 1e-6
                 + ( reqEnd.tv_nsec - reqStart.tv_nsec ) / 1e3;
            } while (elapsed <  udelayPerPck);
#else
#if 0
            /* Delay from Windows is not working, need to fix */
            struct timeval reqStart, reqEnd;
            double elapsed;
            my_gettimeofday(&reqStart);
            do
            {
                my_gettimeofday(&reqEnd);
                elapsed = ( reqEnd.tv_sec - reqStart.tv_sec ) / 1e-6
                 + ( reqEnd.tv_usec - reqStart.tv_usec );
            }while (elapsed <  udelayPerPck);

#endif
#endif
            txPacket.header.seq_num++;

            if ((byte_sent = sendto(pObj->udpSocket, (char *)&txPacket, (payload_size + sizeof(tfdtp_header_t)),
                0, pObj->pUdpIpAddr->ai_addr, pObj->pUdpIpAddr->ai_addrlen)) < 0)
            {
                printf("send failed (%d)\n", getError());
                status = errno;
                goto SEND_QUIT;
            }
        }
        txPacket.header.frame_id++;
    }
    pObj->txFrameId = txPacket.header.frame_id;

SEND_QUIT:
    return status;
}

int TFDTP_recv(TFDTP_Obj *pObj)
{
    TFDTP_Buffer *pBuf = &pObj->bufDes[pObj->curBufIndex];
    TFDTP_Buffer *pPendingBuf = &pObj->bufDes[(pObj->curBufIndex + 0x1) & 0x1];
    int status = 0;
    int byte_read;
    tfdtp_packet_t rxPacket;
    bool done = false;
    uint32_t payload_size;
    struct sockaddr_in senderAddr;
    socklen_t senderLen = sizeof(senderAddr);
    uint32_t packet_count = pObj->pendingPackets;
    uint32_t pending_packet_cnt = 0;
    uint32_t drop_packet_cnt = 0;
    uint32_t retry = 0;
    uint32_t recvSize = (ETH_MAX_FRAME_LEN - ETH_HDR_SIZE -  IP_HDR_SIZE - UDP_HDR_SIZE);

    pObj->pendingPackets = 0;
    pPendingBuf->frameSize = 0;
    while (!done)
    {
        /* Blocking call until data is received or RX timeout reached */
        byte_read = recvfrom(pObj->udpSocket, (char *)&rxPacket, recvSize, 0,
                                        (struct sockaddr *) &senderAddr, &senderLen);
        if (byte_read <= 0)
        {
            retry++;
            fprintf(stderr, "Recv Fail, retrying \n");
            pObj->stats.invalidPacketSizeError++;
            if (retry > 2)
            {
                if (packet_count == 0)
                {
                    fprintf(stderr, "No packet received\n");
                }
                status = -1;
                goto RECV_QUIT;
            }
        }
        else
        {
            retry = 0;
            if (pBuf->frameSize == 0)
            {
                pBuf->frameId = rxPacket.header.frame_id;
            }
            if (rxPacket.header.frame_id == pBuf->frameId)
            {
                payload_size = byte_read - sizeof(tfdtp_header_t);
                if ((rxPacket.header.frame_offset + payload_size) <= pBuf->bufSize)
                {
                    pBuf->frameSize += payload_size;
                    memcpy((char *)&pBuf->bufAddr[rxPacket.header.frame_offset],
                        (char *)&rxPacket.payload, payload_size);
                }
                else
                {
                    pObj->stats.insufficientSizeError++;
                    fprintf(stderr, "Frame offset overflow\n");
                    status = -1;
                    goto RECV_QUIT;
                }
                packet_count++;
                pObj->stats.packetCnt++;
            }
            else if (pPendingBuf->frameSize == 0)
            {
                pPendingBuf->frameId = rxPacket.header.frame_id;
                payload_size = byte_read - sizeof(tfdtp_header_t);
                if ((rxPacket.header.frame_offset + payload_size) <= pPendingBuf->bufSize)
                {
                    pPendingBuf->frameSize += payload_size;
                    memcpy((char *)&pPendingBuf->bufAddr[rxPacket.header.frame_offset],
                        (char *)&rxPacket.payload, payload_size);
                }
                else
                {
                    pObj->stats.insufficientSizeError++;
                    fprintf(stderr, "Frame offset overflow\n");
                    status = -1;
                    goto RECV_QUIT;
                }
                pending_packet_cnt++;
                pObj->stats.packetCnt++;
                pObj->stats.outOfSequenceError++;
            }
            else if (rxPacket.header.frame_id == pPendingBuf->frameId)
            {
                payload_size = byte_read - sizeof(tfdtp_header_t);
                if ((rxPacket.header.frame_offset + payload_size) <= pPendingBuf->bufSize)
                {
                    pPendingBuf->frameSize += payload_size;
                    memcpy((char *)&pPendingBuf->bufAddr[rxPacket.header.frame_offset],
                        (char *)&rxPacket.payload, payload_size);
                }
                else
                {
                    pObj->stats.insufficientSizeError++;
                    fprintf(stderr, "Frame offset overflow\n");
                    status = -1;
                    goto RECV_QUIT;
                }
                pending_packet_cnt++;
                pObj->stats.packetCnt++;
                pObj->stats.outOfSequenceError++;
            }
            else
            {
                fprintf(stderr, "Unexpected Frame: Frame Received= %d\n", rxPacket.header.frame_id);
                pObj->stats.unexpectedFrameID++;
                drop_packet_cnt++;
                //status = -1;
                //goto RECV_QUIT;
            }

            if (((rxPacket.header.flags & TFDTP_EOF_MASK) == TFDTP_EOF) ||
                (pending_packet_cnt > MAX_PENDING_PACKETS) ||
                (drop_packet_cnt > MAX_DROPPED_PACKETS))
            {
                if ((rxPacket.header.flags & TFDTP_EOF_MASK) == TFDTP_EOF)
                {
                    pObj->stats.numEOFMarkers++;
                }
                else
                {
                    pObj->stats.missedEOFError++;
                }
                done = true;
                if (rxPacket.header.total_seq_num != packet_count)
                {
                    pObj->stats.ignoredPacketCnt += (rxPacket.header.total_seq_num - packet_count);
                    #if (1 ==  DEBUG_PRINT)
                    printf("Frame [%d]: No. Packets received[%d] for Total [%d]\n",
                                        pBuf->frameId, (packet_count), rxPacket.header.total_seq_num);
                    #endif
                    status = -1;
                }
            }
            else if ((rxPacket.header.flags & TFDTP_SOF_MASK) == TFDTP_SOF)
            {
                pObj->stats.numSOFMarkers++;
            }
        }
    }

RECV_QUIT:
    pObj->rxFrameCnt++;
    pObj->curBufIndex = (pObj->curBufIndex + 0x1) & 0x1;
    pObj->pendingPackets = pending_packet_cnt;

    return status;
}
