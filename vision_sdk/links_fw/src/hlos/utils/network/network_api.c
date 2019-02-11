/*
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
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "network_api.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include <osa.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


Int32 Network_read(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize)
{
    Int32 status = 0;
    UInt32 tmpDataSize;
    Int32 actDataSize = 0;

    tmpDataSize = *dataSize;

    while(tmpDataSize > 0U)
    {
        actDataSize = recv(pObj->connectedSockFd, (void *)dataBuf, tmpDataSize, 0);
        if(actDataSize <= 0)
        {
            *dataSize = 0U;
            status = -1;
            break;
        }
        else
        {
            dataBuf += actDataSize;
            tmpDataSize -= (UInt32)actDataSize;
        }
    }

    return status;
}


Int32 Network_write(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize)
{
    Int32 status = 0;
    Int32 actDataSize=0;

    while (dataSize > 0) {
        actDataSize = (Int32)send(pObj->connectedSockFd, dataBuf,
            (size_t)dataSize, 0);

        if (actDataSize <= 0)
        {
            break;
        }
        else
        {
            dataBuf += actDataSize;
            dataSize -= (UInt32)actDataSize;
        }
    }

    if (dataSize > 0) {
        status = -1;
    }

    return status;
}

Int32 Network_open(Network_SockObj *pObj, UInt32 port)
{
    Int32 status = 0;
    struct sockaddr_in   sin1;
    Int32 option = 1;

    pObj->connectedSockFd = -1;
    pObj->port = port;
    pObj->sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if( pObj->sockFd < 0)
    {
        Vps_printf(" NETWORK: Unable to open socket (port=%d)!!!\n", port);
        status = -1;
    }
    else
    {
        /* Bind to the specified Server port */
        bzero( &sin1, sizeof(struct sockaddr_in) );
        sin1.sin_family      = AF_INET;
        sin1.sin_addr.s_addr = INADDR_ANY;
        sin1.sin_port        = (UInt16)(htons((UInt16)(pObj->port)));

        setsockopt(pObj->sockFd, SOL_SOCKET, SO_REUSEADDR, &option,
            sizeof(option));

        if (bind(pObj->sockFd, (struct sockaddr *)&sin1, sizeof(sin1)) < 0)
        {
            Vps_printf(" NETWORK: Unable to bind() (port=%d) !!!\n", port);
            close(pObj->sockFd);
            pObj->sockFd = -1;
            status = -1;
        }
        else
        {
            if(listen(pObj->sockFd, 5) < 0)
            {
                close(pObj->sockFd);
                pObj->sockFd = -1;
                status = -1;
            }
        }
    }

    return status;
}

Int32 Network_close(Network_SockObj *pObj, Bool closeServerSock)
{
    if(pObj->connectedSockFd != -1)
    {
        close(pObj->connectedSockFd);
        pObj->connectedSockFd = -1;
    }

    if(closeServerSock)
    {
        if (pObj->sockFd != -1)
        {
            close(pObj->sockFd);
            pObj->sockFd = -1;
        }
    }

    return 0;
}

Int32 Network_waitConnect(Network_SockObj *pObj, UInt32 timeout)
{
    int             status;
    struct timeval  timeout1;
    fd_set          master_set;

    FD_ZERO(&master_set);
    FD_SET(pObj->sockFd, &master_set);

    timeout1.tv_sec  = timeout;
    timeout1.tv_usec = 0;

    status = select(pObj->sockFd + 1, &master_set, NULL, NULL, &timeout1);
    if (status < 0)
    {
        Vps_printf(" NETWORK: Select Failed\n");
        status = -1;
    }
    else if (status == 0)
    {
        Vps_printf(" NETWORK: Timeout\n");
        status = 0;
    }
    else
    {
        if (FD_ISSET(pObj->sockFd, &master_set))
        {
            pObj->connectedSockFd = accept(pObj->sockFd, 0, 0);

            if (pObj->connectedSockFd < 0)
            {
                status = 1;
            }
        }
    }

    /* NO connection, retry */
    return status;
}

Int32 Network_sessionOpen(void *handle)
{
    return 0;
}

Int32 Network_sessionClose(void *handle)
{
    return 0;
}

