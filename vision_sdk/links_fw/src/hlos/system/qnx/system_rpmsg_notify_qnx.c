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

/**
 *******************************************************************************
 * \file system_ipc_notify.c
 *
 * \brief  This file implements the function for the IPC notify functionality
 *
 *         Notify is no more part of IPC 3.x, function names still use notify
 *         to keep compatibility with bios side notify mechanism.
 *
 *         On linux side these APIs use socket based implementation of RPMSG
 *
 * \version 0.0 (Apr 2014) : [YM] First version implemeted using RPMSG
 * \version 0.0 (Mar 2015) : [YM] Removed init de-init, implemented messaging
 *                                based on message types
 *
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "system_priv_ipc.h"

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


System_IpcNotifyObj gSystem_ipcNotifyObj;

/**
 *******************************************************************************
 *
 * \brief Function to register notify callback for links.
 *
 *        Links register its notify handler. This file registers a single call
 *        back function with the notify sub-system. Form that callback
 *        it invokes the callback registered by links based on the linkId
 *        passed with  notify callback.
 *
 * \param   linkId      [IN] linkID of the registering link.
 * \param   notifyCb    [IN] callback function of the link to be registered
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcRegisterNotifyCb(UInt32 linkId, System_ipcNotifyCb notifyCb)
{
    linkId = SYSTEM_GET_LINK_ID(linkId);
    OSA_assert(linkId < SYSTEM_LINK_ID_MAX);

    gSystem_ipcNotifyObj.notifyCb[linkId] = notifyCb;

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Utility function to invoke the notify to remote processor.
 *
 *        This function generates the notify event. It takes linkId as input
 *        maps linkId with procId and generates notify event on that processor
 *
 * \param   linkId      [IN] Link Id to which notify needs to be generated.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcSendNotify(UInt32 linkId)
{
    Int32 err;
    UInt32 procId = SYSTEM_GET_PROC_ID(linkId);

    if(procId == SYSTEM_PROC_EVE1 ||
       procId == SYSTEM_PROC_EVE2 ||
       procId == SYSTEM_PROC_EVE3 ||
       procId == SYSTEM_PROC_EVE4)
    {
        SYSTEM_LINK_ID_SET_ROUTE_BIT(linkId);
        procId = SYSTEM_IPU_PROC_PRIMARY;
    }

    err = write(gSystem_ipcNotifyObj.sockFdTx[procId],
                (Ptr)&linkId,
                sizeof(linkId));
    if (err < 0) {
        Vps_printf(" SYSTEM: IPC: [%s] Notify send failed (%s, %d) !!!\n",
                System_getProcName(procId), strerror(errno), errno);
        return -1;
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This fuction generates unblock event and unblocks select()
 *        Mainly used in shutdown sequence
 *
 *
 *******************************************************************************
 */
Void System_ipcNotifyUnblock(void)
{
    uint64_t     buf = 1;

    /* Write 8 bytes to shutdown */
    write(gSystem_ipcNotifyObj.unblockFd, &buf, sizeof(buf));
}


/**
 *******************************************************************************
 *
 * \brief System wide notify handler function.
 *
 *        This function blocks on recvfrom() UNIX API to get messages from the
 *        kernel based on the message received it calls appropriate registered
 *        call back
 *
 * \return  NULL.
 *
 *******************************************************************************
 */
Void* System_ipcNotifyRecvFxn(Void * prm)
{

    UInt32 payload;
    UInt32 linkProcId;
    UInt32 linkId;
    UInt32 procId;
    UInt32 type;
    OSA_TskHndl * pTsk;
    Int32 maxfd;
    Int32 nfds;
    Int32 retVal;
    fd_set rfds;
    Int32 i;
    Int32 status;
    Int32 done;

#ifdef QNX_BUILD
    pthread_setname_np(pthread_self(), "Ipc Notify Recv thread");
#endif

    done = FALSE;
    while(!done)
    {
        maxfd  = 0;
        retVal = 0;

        /* Wait (with timeout) and retreive message from socket: */
        FD_ZERO(&rfds);

        /* Initialize read fds for communication */
        i = 0;
        while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
        {
            procId = gSystem_ipcEnableProcId[i];
            if ((procId != System_getSelfProcId()) &&
                (procId != SYSTEM_PROC_INVALID)    &&
                (procId != SYSTEM_PROC_EVE1)       &&
                (procId != SYSTEM_PROC_EVE2)       &&
                (procId != SYSTEM_PROC_EVE3)       &&
                (procId != SYSTEM_PROC_EVE4))
            {
                maxfd = MAX(maxfd, gSystem_ipcNotifyObj.sockFdRx[procId]);
                FD_SET(gSystem_ipcNotifyObj.sockFdRx[procId], &rfds);
            }
            i++;
        }

        /* Wait on the event fd, which may be written by System_ipcNotifyUnblock(): */
        FD_SET(gSystem_ipcNotifyObj.unblockFd, &rfds);

        /* Add one to last fd created, this is mandated by select() */
        nfds = MAX(maxfd, gSystem_ipcNotifyObj.unblockFd) + 1;

        retVal = select(nfds, &rfds, NULL, NULL, NULL);

        if (retVal)  {

            if (FD_ISSET(gSystem_ipcNotifyObj.unblockFd, &rfds))  {
                /*
                 * Our event was signalled by System_ipcNotifyUnblock().
                 *
                 * This is typically done during a shutdown sequence, where
                 * the intention of the client would be to ignore (i.e. not fetch)
                 * any pending messages in the transport's queue.
                 * Thus, we shall not check for nor return any messages.
                 */
                done = TRUE;
            }
            else {

                /* Process all messages received on different Rx sockets */
                i = 0;
                while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
                {
                    procId = gSystem_ipcEnableProcId[i];
                    if ((procId != System_getSelfProcId()) &&
                        (procId != SYSTEM_PROC_INVALID)    &&
                        (procId != SYSTEM_PROC_EVE1)       &&
                        (procId != SYSTEM_PROC_EVE2)       &&
                        (procId != SYSTEM_PROC_EVE3)       &&
                        (procId != SYSTEM_PROC_EVE4)       &&
                         FD_ISSET(gSystem_ipcNotifyObj.sockFdRx[procId], &rfds))
                    {
                        status = read(gSystem_ipcNotifyObj.sockFdRx[procId],
                                      &payload, sizeof(UInt32));
                        if (status < 0) {
                            Vps_printf(" SYSTEM: IPC: [%s] Notify recvfrom failed "
                                       "(%s, %d) !!!\n",
                                System_getProcName(procId), strerror(errno), errno);

                            continue;
                        }

                        type = SYSTEM_LINK_ID_GET_NOTIFY_TYPE(payload);

                        if(type==SYSTEM_LINK_ID_NOTIFY_TYPE_LINK_ID)
                        {
                            linkProcId = SYSTEM_GET_PROC_ID(payload);
                            linkId = SYSTEM_GET_LINK_ID(payload);

                            OSA_assert(linkId < SYSTEM_LINK_ID_MAX);

                            OSA_assert(System_getSelfProcId() == linkProcId);

                            if (gSystem_ipcNotifyObj.notifyCb[linkId])
                            {
                                pTsk = System_getLinkTskHndl(linkId);

                                OSA_assert(pTsk!=NULL);
                                gSystem_ipcNotifyObj.notifyCb[linkId] (pTsk);
                            }
                        }
                        else
                        {
                            System_ipcMsgQHandler(payload);
                        }
                    }
                    i++;
                } /* while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX) */
            }
        } /* if (retVal)  { */
    }   /* while(! done) */

    return(NULL);

}

/**
 *******************************************************************************
 *
 * \brief Utility to initialize notify sub-system for links and chains
 *        work.
 *
 *        Initialize the notify event for local processor. It also registers
 *        callback with notify sub-system to get notify events from remote
 *        processor.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyInit(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 i;
    UInt32 procId;
    Int32 firsttime = 1;
    Int32 saveFdRx = 0;

    Vps_printf(" SYSTEM: IPC: Notify init in progress !!!\n");

    memset(&gSystem_ipcNotifyObj, 0, sizeof(gSystem_ipcNotifyObj));

    /* Create Tx and Rx sockets for sending and receiving messages  */
    i = 0;
    while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
    {
        procId = gSystem_ipcEnableProcId[i];
        if ((procId != System_getSelfProcId()) &&
            (procId != SYSTEM_PROC_INVALID)    &&
            (procId != SYSTEM_PROC_EVE1)       &&
            (procId != SYSTEM_PROC_EVE2)       &&
            (procId != SYSTEM_PROC_EVE3)       &&
            (procId != SYSTEM_PROC_EVE4))
        {
            /* host side Rx end point - same for all remote core */
            if (firsttime)
            {
                gSystem_ipcNotifyObj.sockFdRx[procId] =
                        System_ipcCreateChannel(procId,
                                    SYSTEM_RPMSG_NOTIFY_ENDPT_HOST,
                                    SYSTEM_RPMSG_RX_CHANNEL);

                saveFdRx = gSystem_ipcNotifyObj.sockFdRx[procId];
            }
            else
            {
                gSystem_ipcNotifyObj.sockFdRx[procId] = saveFdRx;
            }
            if(gSystem_ipcNotifyObj.sockFdRx[procId] < 0)
            {
                Vps_printf(" SYSTEM: IPC: [%s] Notify RX channel create failed"
                           " (endpoint = %d) !!!\n",
                         System_getProcName(procId),
                         SYSTEM_RPMSG_NOTIFY_ENDPT_HOST);
                return -1;
            }
            firsttime = 0;

            /* host side Tx end point */
            gSystem_ipcNotifyObj.sockFdTx[procId] =
                System_ipcCreateChannel(procId,
                                SYSTEM_RPMSG_ENDPT_REMOTE,
                                SYSTEM_RPMSG_TX_CHANNEL);

            if(gSystem_ipcNotifyObj.sockFdTx[procId] < 0)
            {
                Vps_printf(" SYSTEM: IPC: [%s] Notify TX channel create failed"
                           " (endpoint = %d) !!!\n",
                         System_getProcName(procId),
                         SYSTEM_RPMSG_ENDPT_REMOTE);
                return -1;
            }
        }

        i++;
    }

    /*
     * To support System_ipcNotifyUnblock() functionality, create an event object.
     * Writing to this event will unblock the select() call in MessageQ_get().
     */
    if (pipe(&gSystem_ipcNotifyObj.unblockFd) == -1) {
        Vps_printf(" SYSTEM: IPC: Notify unblock event create failed (%s, %d) !!!\n",
                strerror(errno), errno);
        return -1;
    }

    /* Create a thread that blocks on socket to receive message from kernel */
    status = OSA_thrCreate(
                &gSystem_ipcNotifyObj.thrHndl,
                System_ipcNotifyRecvFxn,
                SYSTEM_RPMSG_NOTIFY_TSK_PRI,
                OSA_THR_STACK_SIZE_DEFAULT,
                NULL);
    OSA_assertSuccess(status);

    Vps_printf(" SYSTEM: IPC: Notify init DONE !!!\n");

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Utility to de-initialize notify sub-system for links and chains
 *        work.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyDeInit(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 i;
    UInt32 procId;
    Int32 firsttime = 1;

    Vps_printf(" SYSTEM: IPC: Notify de-init in progress !!!\n");

    System_ipcNotifyUnblock();

    OSA_thrDelete(&gSystem_ipcNotifyObj.thrHndl);

    /* Initialize Endpoints for communication */
    i = 0;
    while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
    {
        procId = gSystem_ipcEnableProcId[i];
        if ((procId != System_getSelfProcId()) &&
            (procId != SYSTEM_PROC_INVALID)    &&
            (procId != SYSTEM_PROC_EVE1)       &&
            (procId != SYSTEM_PROC_EVE2)       &&
            (procId != SYSTEM_PROC_EVE3)       &&
            (procId != SYSTEM_PROC_EVE4))
        {
            if (firsttime)
            {
                System_ipcDeleteChannel(gSystem_ipcNotifyObj.sockFdRx[procId]);
            }
            firsttime = 0;
            System_ipcDeleteChannel(gSystem_ipcNotifyObj.sockFdTx[procId]);
        }
        i++;
    }

    close(gSystem_ipcNotifyObj.unblockFd);

    Vps_printf(" SYSTEM: IPC: Notify de-init DONE !!!\n");

    return status;
}
