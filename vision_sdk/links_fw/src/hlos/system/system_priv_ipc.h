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
 *
 * \ingroup SYSTEM_IMPL
 * \defgroup SYSTEM_IPC_IMPL   System implementation related to IPC
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file system_priv_ipc.h
 *
 * \brief  Private header file RPMessage based ipc implementation
 *
 * \version 0.0 (APR 2014) : [YM] First version implemented
 *
 *******************************************************************************
 */
#ifndef _SYSTEM_PRIV_IPC_H_
#define _SYSTEM_PRIV_IPC_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <links_fw/src/hlos/system/system_priv_common.h>
#include <links_fw/src/hlos/osa/include/osa_thr.h>
#include <links_fw/src/hlos/osa/include/osa_mutex.h>
#include <links_fw/src/hlos/osa/include/osa_que.h>
#include <links_fw/src/hlos/osa/include/osa_tsk.h>
#include <links_fw/src/hlos/osa/include/osa_debug.h>
#include <links_fw/src/hlos/osa/include/osa_mem.h>
#include <links_fw/src/hlos/osa/include/osa_buf.h>
#include <links_fw/src/hlos/osa/include/osa_sem.h>
#include <links_fw/src/hlos/utils/multiproc/_MultiProc.h>
#include <ti/ipc/MultiProc.h>
#include <stdint.h>
#include <include/link_api/system_ipc_if.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Max elements in local que used for message's
 *******************************************************************************
 */
#define SYSTEM_IPC_MSGQ_MAX_ELEMENTS            (20)

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })



/*******************************************************************************
 *  Enums
 *******************************************************************************
 */


 /**
 *******************************************************************************
 *
 *  \brief These types distinguish between different type of RPMessages channels
 *
 *
 *******************************************************************************
 */
typedef enum
{
    SYSTEM_RPMSG_RX_CHANNEL = 0,
    /**< Used to create RP Message endpoint to receive messages from
         remote core */

    SYSTEM_RPMSG_TX_CHANNEL,
    /**< Used to create RP Message endpoint to transmit messages to
         remote core */

} SYSTEM_RPMSG_SOCKETTYPE;


/*******************************************************************************
 *  declaration for ipc notify callback function
 *******************************************************************************
 */
typedef Void(*System_ipcNotifyCb) (OSA_TskHndl * pTthread);


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure for book keeping IPC message queue handling.
 *
 *******************************************************************************
*/


typedef struct {
    OSA_MutexHndl msgQLock;
    /**< Lock to protect messageQ Q elements across threads */

    OSA_SemHndl msgQAck;
    /**< Ack semaphore */

    OSA_QueHndl msgQLocalQ;
    /**< local Command que */

    OSA_ThrHndl thrHndl;
    /**< receive thread handle */

} System_IpcMsgQObj;

typedef struct {

    Int32 sockFdRx[SYSTEM_PROC_MAX];
    /**< socket fds for Rx channels */

    Int32 sockFdTx[SYSTEM_PROC_MAX];
    /**< socket fds for Tx channels */

    Int32 unblockFd;
    /**< descriptor unblocking select()  */

    OSA_ThrHndl thrHndl;
    /**< receive thread handle */

    System_ipcNotifyCb notifyCb[SYSTEM_LINK_ID_MAX];

} System_IpcNotifyObj;

/**
 *******************************************************************************
 * \brief IPC object extern declaration
 *******************************************************************************
 */

Int32 System_ipcInit(void);
Int32 System_ipcDeInit(void);

Int32 System_ipcNotifyInit(void);
Int32 System_ipcNotifyDeInit(void);
Int32 System_ipcRegisterNotifyCb(UInt32 linkId, System_ipcNotifyCb notifyCb);
Int32 System_ipcSendNotify(UInt32 linkId);


Int32 System_ipcMsgQInit(void);
Int32 System_ipcMsgQDeInit(void);
Int32 System_ipcMsgQSendMsg(UInt32 linkId, UInt32 cmd, Void * pPrm,
                            UInt32 prmSize, Bool waitAck);

void System_ipcMsgQHandler(UInt32 payload);

Int32 System_ipcCreateChannel(UInt32 procId, UInt32 endpt, UInt32 channelType);
Int32 System_ipcDeleteChannel(Int32 fd);

/* System_ipcMemAlloc returns physical address to allocated buffer */
UInt32 System_ipcMemAlloc(UInt32 heapId, UInt32 memSize, UInt32 memAlign);
/* System_ipcMemFree expects physical address of the buffer to be freed*/
Void   System_ipcMemFree(UInt32 heapId, UInt32 addr, UInt32 memSize);


#endif

/* @} */
