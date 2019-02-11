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
#include <src/rtos/utils_common/include/network_api.h>

/* TFDTP Dependencies */
#include <ti/nsp/drv/inc/tfdtp.h>

#define NETWORK_INVALID_SOCKET 0xFFFFFFFFU

Int32 Network_read(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize)
{
    Int32 status = NETWORK_SUCCESS;

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    UInt32 tmpDataSize;
    Int32 actDataSize = 0;

    tmpDataSize = *dataSize;

    while(tmpDataSize > 0U)
    {

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
         * State: Defer -> Waiver -> Case by case
         * connectedSockFd is defined based on type in NDK package
         */
        actDataSize = recv(pObj->connectedSockFd, (void *)dataBuf, tmpDataSize, 0);
        if(actDataSize <= 0)
        {
            *dataSize = 0U;
            status = NETWORK_ERROR;
            break;
        }
        else
        {
            dataBuf += actDataSize;
            tmpDataSize -= (UInt32)actDataSize;
        }
    }

#endif

    return status;
}


Int32 Network_write(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize)
{
    Int32 status = NETWORK_SUCCESS;

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )
    Int32 actDataSize=0;

    while(dataSize > 0 ) {
        actDataSize = (Int32)send(pObj->connectedSockFd, dataBuf, (size_t)dataSize, 0);

        if(actDataSize <= 0)
        {
            break;
        }
        else
        {
            dataBuf += actDataSize;
            dataSize -= (UInt32)actDataSize;
        }
    }

    if( dataSize > 0 ) {
        status = NETWORK_ERROR;
    }
#endif

    return status;
}

Int32 Network_open(Network_SockObj *pObj, UInt32 port)
{
    Int32 status = NETWORK_SUCCESS;

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    struct sockaddr_in   sin1;
    Int32 option = 1;

    pObj->connectedSockFd = (SOCKET)NETWORK_INVALID_SOCKET;
    pObj->port = port;
    pObj->sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( pObj->sockFd == (SOCKET)NETWORK_INVALID_SOCKET)
    {
        Vps_printf(" NETWORK: Unable to open socket (port=%d)!!!\n", port);
        status = NETWORK_ERROR;
    }
    else
    {
        /* Bind to the specified Server port */
        bzero( &sin1, sizeof(struct sockaddr_in) );
        sin1.sin_family     = AF_INET;
        sin1.sin_addr.s_addr = INADDR_ANY;
        sin1.sin_port       = (UInt16)(htons((UInt16)(pObj->port)));

        setsockopt ( pObj->sockFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof( option ) );

        if( bind( pObj->sockFd,(struct sockaddr *)&sin1, sizeof(sin1) ) < 0 )
        {
            Vps_printf(" NETWORK: Unable to bind() (port=%d) !!!\n", port);
            fdClose( pObj->sockFd );
            pObj->sockFd = (SOCKET)NETWORK_INVALID_SOCKET;
            status = NETWORK_ERROR;
        }
        else
        {
            if( listen( pObj->sockFd, 5 ) < 0 )
            {
                fdClose( pObj->sockFd );
                pObj->sockFd = (SOCKET)NETWORK_INVALID_SOCKET;
                status = NETWORK_ERROR;
            }
        }
    }

#endif

    return status;
}

Int32 Network_close(Network_SockObj *pObj, Bool closeServerSock)
{
#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    if(pObj->connectedSockFd != (SOCKET)NETWORK_INVALID_SOCKET)
    {
        fdClose( pObj->connectedSockFd );
        pObj->connectedSockFd = (SOCKET)NETWORK_INVALID_SOCKET;
    }

    if(closeServerSock)
    {
        if(pObj->sockFd != (SOCKET)NETWORK_INVALID_SOCKET)
        {
            fdClose( pObj->sockFd );
            pObj->sockFd = (SOCKET)NETWORK_INVALID_SOCKET;
        }
    }
#endif

    return 0;
}

Int32 Network_waitConnect(Network_SockObj *pObj, UInt32 timeout)
{
    Int32 status = NETWORK_SUCCESS;

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    pObj->pollitem[0].fd = pObj->sockFd;
    pObj->pollitem[0].eventsRequested = POLLIN;

    if( fdPoll( pObj->pollitem, 1U, timeout ) == SOCKET_ERROR )
    {
        Vps_printf(" NETWORK: fdPoll() failed with SOCKET_ERROR (port=%d) !!!\n", pObj->port);
        status =  NETWORK_ERROR;
    }
    else
    {

        if( pObj->pollitem[0].eventsDetected == FALSE)
        {
            /* NO connection, retry */
            status = NETWORK_SUCCESS;
        }
        else
        {
            if( (UInt32)(pObj->pollitem[0].eventsDetected) & (UInt32)POLLNVAL )
            {
                Vps_printf(" NETWORK: fdPoll() failed with POLLNVAL (port=%d) !!!\n", pObj->port);
                status = NETWORK_ERROR;
            }
            else
            {

                if( (UInt32)(pObj->pollitem[0].eventsDetected) & (UInt32)POLLIN )
                {
                    pObj->connectedSockFd = accept( pObj->sockFd, 0, 0 );

                    if( pObj->connectedSockFd != (SOCKET)NETWORK_INVALID_SOCKET )
                    {
                        status = 1;
                    }
                }
            }
        }
    }
#endif
    /* NO connection, retry */
    return status;
}

Int32 Network_sessionOpen(BspOsal_TaskHandle handle)
{
#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    if(handle==NULL)
    {
        handle = Task_self();
    }

    /* Allocate the file environment for this task */
    fdOpenSession( handle );
#endif

    return 0;
}

Int32 Network_sessionClose(BspOsal_TaskHandle handle)
{
#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    if(handle==NULL)
    {
        handle = Task_self();
    }

    fdCloseSession( handle );

#endif

    return 0;
}

