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

#include <networkCtrl_if.h>
#include <network_api.h>

#if !defined(linux)
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

int Network_init()
{
    socketsStartup();

    return 0;
}

int Network_deInit()
{
    socketsShutdown();

    return 0;
}

int Network_connect(Network_SockObj *pObj, char *ipAddr, UInt32 port)
{
    int sin_size;
    struct hostent *host;
    struct sockaddr_in server;

    host = gethostbyname(ipAddr);

    strcpy(pObj->ipAddr, ipAddr);

    pObj->serverPort = port;

    pObj->clientSocketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (pObj->clientSocketId == INVALID_SOCKET ) {
        printf("# ERROR: NETWORK: Socket open failed (%s:%d)!!!\n", pObj->ipAddr, pObj->serverPort);
        return OSA_EFAIL;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr = *((struct in_addr *)host->h_addr);
    memset(&(server.sin_zero), 0, 8);

    sin_size = sizeof(server);

    if (connect(pObj->clientSocketId, (struct sockaddr *)&server, sin_size) == -1)
    {
        printf("# ERROR: NETWORK: Server connect Failed (%s:%d)!!!\n", pObj->ipAddr, pObj->serverPort);
        return OSA_EFAIL;
    }

    OSA_printf("# NETWORK: Connected to Server (%s:%d)!!!\n", pObj->ipAddr, pObj->serverPort);

    return OSA_SOK;
}

int Network_close(Network_SockObj *pObj)
{
  int ret;

  if(pObj->clientSocketId < 0)
    return OSA_EFAIL;

  ret = close(pObj->clientSocketId);

  return ret;
}

int Network_read(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize)
{
    int actDataSize = 0;
    UInt32 tmpDataSize;

    tmpDataSize = *dataSize;

    while(tmpDataSize > 0)
    {
        actDataSize = recv(pObj->clientSocketId, (void*)dataBuf, tmpDataSize, 0);
        if(actDataSize<=0)
        {
            *dataSize = 0;
            printf ("ERROR: recv failed in Network_read!\n");
            return -1;
        }
        dataBuf += actDataSize;
        tmpDataSize -= actDataSize;
    }

    return 0;
}

int Network_readString(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 maxDataSize)
{
    int actDataSize = 0;

    memset(dataBuf, 0, maxDataSize);

    actDataSize = recv(pObj->clientSocketId, (void*)dataBuf, maxDataSize-1, 0);
    if(actDataSize<=0)
    {
        dataBuf[0] = 0;
        printf ("ERROR: recv failed in Network_readString!\n");
        return -1;
    }

    return 0;
}

int Network_tfdtpRead(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize)
{
    int status;

    pObj->pTfdtpObj->curBufDes.bufAddr = (char *)dataBuf;
    pObj->pTfdtpObj->curBufDes.bufSize = *dataSize;
    pObj->pTfdtpObj->curBufDes.frameSize = 0;
    status = TFDTP_recv(pObj->pTfdtpObj);

    return status;
}

int Network_tfdtpWrite(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize)
{
    int status;

    pObj->pTfdtpObj->curBufDes.bufAddr = (char *)dataBuf;
    pObj->pTfdtpObj->curBufDes.bufSize = dataSize;
    pObj->pTfdtpObj->curBufDes.frameSize = dataSize;
    /* Send one frame to target via TFDTP */
    status = TFDTP_send(pObj->pTfdtpObj);

    return status;
}

int Network_write(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize)
{
    int actDataSize=0;

    while(dataSize > 0 ) {
        actDataSize = send(pObj->clientSocketId, (void*)dataBuf, dataSize, 0);

        if(actDataSize<=0)
            break;
        dataBuf += actDataSize;
        dataSize -= actDataSize;
    }

    if( dataSize > 0 )
    {
        printf ("ERROR: send failed in Network_write!\n");
        return -1;
    }

    return 0;
}

int Network_tfdtpOpen(Network_SockObj *pObj, TFDTP_CreateParams *pParam)
{
    int status;

    pParam->enableDataValFlag = 0;

    pObj->pTfdtpObj = TFDTP_open(pParam);

    if (pObj->pTfdtpObj == NULL)
    {
        printf("# ERROR: NETWORK: TFDTP_open() Failed (%s:%d)!!!\n", pParam->destIpAddr, pParam->udpPort);
        status = OSA_EFAIL;
    }
    else
    {
        pObj->pTfdtpObj->tcpSocket = pObj->clientSocketId;
        OSA_printf("# NETWORK: TFDTP_open() Done (%s:%d)!!!\n", pParam->destIpAddr, pParam->udpPort);
        status = OSA_SOK;
    }
    return status;
}

int Network_tfdtpSendParams(Network_SockObj *pObj, char *myIpAddr, UInt32 retry)
{
    int status = OSA_SOK;

    status = TFDTP_setChConfig(pObj->pTfdtpObj, myIpAddr, retry);
    if (status != 0)
    {
        printf("# ERROR: NETWORK: TFDTP_setChConfig() Failed (%d)!!!\n", status);
        status = OSA_EFAIL;
    }

    return status;
}

int Network_tfdtpSendAck(Network_SockObj *pObj, UInt32 ack)
{
    int bytes;

    bytes = send(pObj->clientSocketId, (void*) &ack, sizeof(UInt32), 0);

    if(bytes != sizeof(UInt32))
    {
        printf("# ERROR: NETWORK: Network_tfdtpSendAck() Failed (%d)!!!\n", bytes);
        return -1;
    }

    return 0;
}

UInt32 Network_tfdtpWaitAck(Network_SockObj *pObj)
{
    UInt32 cmd = 0U;
    int bytes;

    bytes = recv(pObj->clientSocketId, (void*) &cmd, sizeof(UInt32), 0);

    if(bytes != sizeof(UInt32))
    {
        printf("# ERROR: NETWORK: Network_tfdtpWaitAck() Failed (%d)!!!\n", bytes);
        cmd = TFDTP_TRANSMIT_INVALID;
    }

    return cmd;
}
