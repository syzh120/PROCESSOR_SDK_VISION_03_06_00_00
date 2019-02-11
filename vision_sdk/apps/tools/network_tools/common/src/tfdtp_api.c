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
*  \file tfdtp_api.c
*
*  \brief TFDTP API source file.
*/

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include "../inc/tfdtp_api.h"
#include "../inc/networkCtrl_if.h"

#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#if !defined(linux)
#define _WIN32_WINNT 0x0601
#include <ws2tcpip.h>
#include <conio.h>
#include <iphlpapi.h>
#endif

#ifdef __unix__
# include <unistd.h>
#define CLOCK CLOCK_MONOTONIC
#elif defined _WIN32
#define WIN32_LEAN_AND_MEAN
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/
#define socketsShutdown()
#define socketsStartup()
#define getError() (errno)
#define DEBUG_PRINT 0
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
    int value;
    int status = 0;
    struct sockaddr_in s;
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

            pObj->pendBufDes.bufAddr = malloc(pParam->frameSize);
            if (pObj->pendBufDes.bufAddr == NULL)
            {
                fprintf(stderr, "Failed to allocate frame buffer.\n");
                status = -1;
                goto OPEN_EXIT;
            }
            pObj->pendBufDes.bufSize = pParam->frameSize;
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
#if 0
    for (i = 0; i < 2; i++)
    {
        if (pObj->bufDes[i].bufAddr)
        {
            free(pObj->bufDes[i].bufAddr);
        }
    }
#endif
    if (pObj->pendBufDes.bufAddr)
    {
        free(pObj->pendBufDes.bufAddr);
    }

    free(pObj);
}

int GetMACAddress(SOCKET fd, char *pSrcIpAddr, char *pMACAddr, uint32_t *pMACAddrSize)
{
    int status = 0;

#if defined(linux)
    struct ifaddrs *ifaddr, *ifa;
    int i, family, match = 0;
    struct sockaddr_in * s;
    char host[NI_MAXHOST];
    struct ifreq ifr;

    status = getifaddrs(&ifaddr);
    if ( status == -1)
    {
        fprintf(stderr, "getifaddrs failed\n");
    }

    /* Walk through the address list to find the adapter. */
    for (ifa = ifaddr, i = 0; ifa != NULL ; ifa = ifa->ifa_next, i++)
    {
        if (ifa->ifa_addr == NULL)
        {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        /* For an AF_INET* interface address, display the address */
        if (family == AF_INET)
        {
            s = (struct sockaddr_in *)ifa->ifa_addr;
            if(!strcmp(pSrcIpAddr, inet_ntoa(s->sin_addr)))
            {
                strcpy(host, ifa->ifa_name);
                match = 1;
                printf("TFDTP: Adapter Name: %s\n", host);
                break;
            }
        }
    }

    freeifaddrs(ifaddr);

    if (match)
    {
        ifr.ifr_addr.sa_family = AF_INET;
        strcpy(ifr.ifr_name , host);
        ioctl(fd, SIOCGIFHWADDR, &ifr);

        *pMACAddrSize = 6;
        memcpy(pMACAddr, (unsigned char *)ifr.ifr_hwaddr.sa_data, 6);

        printf("TFDTP: MAC Address: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n" ,
                pMACAddr[0], pMACAddr[1], pMACAddr[2],
                pMACAddr[3], pMACAddr[4], pMACAddr[5]);
        status = 0;
    }
    else
    {
        status = -1;
    }

#else
    PIP_ADAPTER_ADDRESSES pAdapterAddr = NULL;
    PIP_ADAPTER_ADDRESSES pAddr = NULL;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicastAddr = NULL;
    struct sockaddr_in *sockaddr = NULL;
    uint32_t size = 15000;
    bool addrFound = false;
    int i, j;

    pAdapterAddr = (IP_ADAPTER_ADDRESSES *)malloc(size);
    if (pAdapterAddr == NULL)
    {
        status = -1;
        goto ERREXIT;
    }
    status = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, pAdapterAddr, (PULONG)&size);
    if (status != 0)
    {
        goto ERREXIT;
    }
    pAddr = pAdapterAddr;
    while ((pAddr != NULL) && (addrFound == false))
    {
        printf("TFDTP: Adapter name: %s\n", pAddr->AdapterName);

        pUnicastAddr = pAddr->FirstUnicastAddress;
        if (pUnicastAddr != NULL)
        {
            for (i = 0; pUnicastAddr != NULL; i++)
            {
                sockaddr = (struct sockaddr_in *) pUnicastAddr->Address.lpSockaddr;
                printf("\tIP Address: %s\n", inet_ntoa(sockaddr->sin_addr));
                if (!strcmp(inet_ntoa(sockaddr->sin_addr), pSrcIpAddr))
                {
                    printf("\tAdapter IP Address matches Source IP Address.\n");
                    if (pAddr->PhysicalAddressLength != 0)
                    {
                        *pMACAddrSize = pAddr->PhysicalAddressLength;
                        memcpy(pMACAddr, pAddr->PhysicalAddress, pAddr->PhysicalAddressLength);
                        printf("\tMAC address: ");
                        for (j = 0; j < (int)pAddr->PhysicalAddressLength; j++)
                        {
                            if (j == (pAddr->PhysicalAddressLength - 1))
                                printf("%.2X\n", (int)pAddr->PhysicalAddress[j]);
                            else
                                printf("%.2X-", (int)pAddr->PhysicalAddress[j]);
                        }
                        addrFound = true;
                        break;
                    }
                    else
                    {
                        fprintf(stderr, "\tNo Valid MAC Address for this adapter\n");
                        status = -1;
                        goto ERREXIT;
                    }
                }
                pUnicastAddr = pUnicastAddr->Next;
            }
        }
        else
        {
            printf("\tNo Unicast Addresses\n");
        }
        pAddr = pAddr->Next;
    }

ERREXIT:
    if (pAdapterAddr)
    {
        free(pAdapterAddr);
    }

#endif

    return status;

}

int TFDTP_setChConfig(TFDTP_Obj *pObj, char *pSelfIpAddr, uint32_t retry)
{
    NetworkTfdtp_channelParams params;
    uint32_t size = sizeof(params);
    char MACAddr[16] = { 0 };
    uint32_t MACAddrSize = 0;
    int status = 0;

    status = GetMACAddress(pObj->tcpSocket, pSelfIpAddr, MACAddr, &MACAddrSize);

    if (status == 0)
    {
        memset(&params, 0, size);
        /* Prepare Command Buffer */
        MACAddrSize = sizeof (params.MACAddr);
        printf("TFDTP: MAC address Size %d\n", MACAddrSize);

        memcpy(params.MACAddr, MACAddr, MACAddrSize);
        params.IPAddress = ntohl(inet_addr((const char *) pSelfIpAddr));
        params.channelId = pObj->chanId;
        params.thruput = pObj->chanId;
        params.retryCount = retry;

        /* Send Channel Config params */
        printf("TFDTP: Send TFDTP Channel Config Params, IP 0x%x\n", params.IPAddress);
        status = send(pObj->tcpSocket, (void*) &params, size, 0);
        if (status == size)
        {
            status = 0;
        }
        else
        {
            status = -1;
            fprintf(stderr, "Failed to send TFDTP channel parameters\n");
        }
    }
    else
    {
        fprintf(stderr, "Failed to get Adapter MAC address\n");
    }

    return status;
}

int TFDTP_send(TFDTP_Obj *pObj)
{
    TFDTP_Buffer *pBuf = &pObj->curBufDes;
    tfdtp_packet_t txPacket;
    uint32_t payload_size = pObj->maxPayloadSize;
    uint32_t udelayPerPck;
    uint16_t seq_num;
    uint32_t c, frame_offset;
    int status = 0;
    int byte_sent = 0;

    /* Compute delay per packet for required throughput */
    /* For 1000Mbps throughput each packet takes 8 us to transmit (1000Mbps ->83000pck/s -> 83packets/ms ->1pck/12uS
     * so multiple by 12 to get delay val in micro second for req. throughput */
    udelayPerPck = (uint32_t)( (float)((float)ETH_MAX_THROUGHPUT/(float)pObj->thruput) * 12 );
    txPacket.header.channel_id = pObj->chanId;
#if (1 == DEBUG_PRINT)
    printf("TFDTP: Sending to channel channel_id = %d\n",txPacket.header.channel_id);
#endif
    txPacket.header.total_seq_num = (pBuf->frameSize + payload_size - 1) / payload_size;
    txPacket.header.frame_id = pObj->txFrameId;
#if (1 == DEBUG_PRINT)
    printf("TFDTP: Delay val = %d\n", udelayPerPck);
#endif
    for (c = 0; c < pBuf->bufSize; c += pBuf->frameSize)
    {
#if (1 == DEBUG_PRINT)
    printf("TFDTP: Frame id = %d, total seq no =%d\n", pObj->txFrameId, txPacket.header.total_seq_num);
#endif
        for (seq_num = 0, frame_offset = 0; seq_num < txPacket.header.total_seq_num; seq_num++, frame_offset += payload_size)
        {
            txPacket.header.flags = TFDTP_VER;
            txPacket.header.seq_num = seq_num;
            txPacket.header.frame_offset = frame_offset;
            if (seq_num == 0)
            {
                txPacket.header.flags |= TFDTP_SOF;
            }
            if (seq_num == (txPacket.header.total_seq_num - 1))
            {
                /* Remaining data in the file */
                payload_size = pBuf->frameSize - frame_offset;
                txPacket.header.flags |= TFDTP_EOF;
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
                printf("TFDTP: send failed (%d)\n", getError());
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
    TFDTP_Buffer *pBuf = &pObj->curBufDes;
    TFDTP_Buffer *pPendingBuf = &pObj->pendBufDes;
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
    uint32_t recvSize = (ETH_MAX_FRAME_LEN - ETH_HDR_SIZE -  IP_HDR_SIZE - UDP_HDR_SIZE);

    pObj->pendingPackets = 0;
    pPendingBuf->frameSize = 0;
    while (!done)
    {
        /* Blocking call until data is received or RX timeout reached */
        byte_read = recvfrom(pObj->udpSocket, (char *)&rxPacket, recvSize, 0,(struct sockaddr *) &senderAddr, &senderLen);
        if (byte_read <= 0)
        {
            status = -1;
            done = 1;
        }
        else
        {
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
                #if (1 == DEBUG_PRINT)
                printf("TFDTP: Packet from New fid =%d \n", rxPacket.header.frame_id);
                #endif

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
                #if (1 == DEBUG_PRINT)
                printf("TFDTP: Packet from Pending buffer -Fid=%d \n", rxPacket.header.frame_id);
                #endif
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
                #if (1 == DEBUG_PRINT)
                fprintf(stderr, "Unexpected Frame: Frame Received= %d\n", rxPacket.header.frame_id);
                #endif
                pObj->stats.unexpectedFrameID++;
                drop_packet_cnt++;
                status = -1;
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
                    printf("TFDTP: Frame [%d]: No. Packets received[%d] for Total [%d]\n",
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

    if (status != 0)
    {
        printf("# ERROR: TFDTP_recv failed/not complete\n");
    }


RECV_QUIT:
    pObj->rxFrameCnt++;
    pObj->pendingPackets = pending_packet_cnt;

    return status;
}
