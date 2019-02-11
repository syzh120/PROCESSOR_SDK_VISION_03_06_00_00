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
*  \file tfdtp_test_client.c
*
*  \brief TFDTP Test Client source file.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"
#include "tfdtp_api.h"
#include "../common/test_common.h"
#include "tfdtp_test_client.h"

int GetMACAddress(SOCKET fd, char *pSrcIpAddr, char *pMACAddr, uint32_t *pMACAddrSize)
{
    int status = 0;

#if defined(__GNUC__) && defined(linux)
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
                printf("Adapter Name: %s\n", host);
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

        printf("MAC Address: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n" ,
                pMACAddr[0], pMACAddr[1], pMACAddr[2],
                pMACAddr[3], pMACAddr[4], pMACAddr[5]);
        status = 0;
    }
    else
    {
        status = -1;
    }

#elif defined(__MINGW32__) || defined(_MSC_VER)
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
        printf("Adapter name: %s\n", pAddr->AdapterName);

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

#else
#error "Unrecognized compiler"
#endif

    return status;

}

int TFDTP_TestClient_sendCmd(TFDTP_Obj *pObj, TestCmdID cmdId, uint32_t *cmdBuf)
{
    int status = 0;
    uint8_t recvBuf[MAX_CMD_LENGTH];
    uint32_t cmdSize = 4U;

    uint32_t buf[2U] = {0};
    buf[0] = htonl(cmdId);
    if(NULL != cmdBuf)
    {
        /* If command needs parameter */
        memcpy (&buf[1], cmdBuf, sizeof(uint32_t));
        cmdSize += 4U;
    }

#if (1 == DEBUG_PRINT)
    printf("Sending Command\n");
#endif
    status = send(pObj->tcpSocket, (const char *)buf, cmdSize, 0);

    if (status != cmdSize)
    {
        printf("Send Command failed\n ");
        return -1;
    }

    /* Wait for ACK */
    status = recv(pObj->tcpSocket, (char *)recvBuf, (size_t)MAX_CMD_LENGTH, 0);

    if (status != cmdSize)
    {
        printf("Command Ack Failed\n ");
        return -1;
    }

    status = memcmp(buf, recvBuf, cmdSize);
#if (1 == DEBUG_PRINT)
    printf("TFDTP_TestClient_sendCmd done. [%d]\n", status);
#endif
    return status;
}

int tfdtp_testClient_InitServer(TFDTP_Obj *pObj, uint8_t *buf, uint32_t size)
{
    int status = 0;
    uint8_t recvBuf[MAX_CMD_LENGTH];
    //getchar();
    if ((size < 4) || (size > MAX_CMD_LENGTH))
    {
        status = -1;
    }
    else
    {
#if (1 == DEBUG_PRINT)
        printf("Sending Command\n");
#endif
        status = send(pObj->tcpSocket, (const char *)buf, size, 0);
    }

    if (status == size)
    {
        /* Wait for ACK */
        status = recv(pObj->tcpSocket, (char *)recvBuf, (size_t)MAX_CMD_LENGTH, 0);
    }
    else
    {
        printf("Send Command failed\n ");
        status = -1;
    }

    if (status == size)
    {
        status = memcmp(buf, recvBuf, size);
    }
    else
    {
        printf("Command Ack Failed\n ");
    }
#if (1 == DEBUG_PRINT)
    printf("TFDTP_TestClient_sendCmd done. [%d]\n", status);
#endif
    return status;
}

int tfdtp_testClient_start(TFDTP_Obj *pObj, char *pSrcIpAddr)
{
    uint32_t cmdId = TEST_CMD_START_TFDTP;
    uint8_t cmdBuf[MAX_CMD_LENGTH];
    TestStartCmdParams cmdParams;
    uint32_t size;
    char MACAddr[16] = { 0 };
    uint32_t MACAddrSize = 0;
    int status = 0;

    status = GetMACAddress(pObj->tcpSocket, pSrcIpAddr, MACAddr, &MACAddrSize);

    if (status == 0)
    {
        /* Prepare Command Buffer */
        memcpy(cmdParams.MACAddress, MACAddr, MACAddrSize);
        strcpy(cmdParams.IPAddress, pSrcIpAddr);
        cmdParams.enableDataValFlag = pObj->enableDataValFlag;
        cmdParams.numRxFrame = pObj->numRxFrame;
        cmdParams.thruput = pObj->thruput;
        cmdParams.chanId = pObj->chanId;
        *(uint32_t *)cmdBuf = htonl(cmdId);
        memcpy(&cmdBuf[4], &cmdParams, sizeof(TestStartCmdParams));
        size = 4 + sizeof(TestStartCmdParams);

        /* Send START command */
        printf("Start TFDTP Server\n");
        status = tfdtp_testClient_InitServer(pObj, cmdBuf, size);
    }
    else
    {
        fprintf(stderr, "Failed to get Adapter MAC address\n");
    }

    return status;
}
