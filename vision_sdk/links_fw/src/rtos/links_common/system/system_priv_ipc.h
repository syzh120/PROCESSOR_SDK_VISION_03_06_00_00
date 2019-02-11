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
 * \brief  Private header file IPC implementation
 *
 * \version 0.0 (Jun 2013) : [KC] First version taken from DVR RDK and
 *                                cleaned up for Vision_sdk
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 *
 *******************************************************************************
 */
#ifndef SYSTEM_PRIV_IPC_H_
#define SYSTEM_PRIV_IPC_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/links_common/system/system_priv_common.h>
#include <src/rtos/links_common/system/system_priv_openvx.h>
#include <src/rtos/links_common/system/system_work_queue_if_priv.h>
#include <include/link_api/system_ipc_if.h>
#include <src/rtos/utils_common/include/file_api.h>


/* #define SYSTEM_IPC_MSGQ_DEBUG */

/*******************************************************************************
 *  Max elements in local que used for message's
 *******************************************************************************
 */
#define SYSTEM_IPC_MSGQ_MAX_ELEMENTS            (20U)

/*******************************************************************************
 *  declaration for ipc notify callback function
 *******************************************************************************
 */
typedef Void(*System_ipcNotifyCb) (const Utils_TskHndl * pTsk);

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

    BspOsal_SemHandle msgQLock;
    /**< Lock to protect messageQ Q elements across threads */

    BspOsal_SemHandle msgQAck;
    /**< ACK for a sent message */

    BspOsal_TaskHandle msgQTask;
    /**< Handle to task handing IPC message queues */

    Utils_QueHandle msgQLocalQ;
    /**< MessageQ to get messages for this task */

    UInt32 msgQLocalQueMem[SYSTEM_IPC_MSGQ_MAX_ELEMENTS];
    /**< Memory for local QUE */

    System_ipcNotifyCb notifyCb[SYSTEM_LINK_ID_MAX];
    /**< Callback function for the IPC notify */

} System_IpcObj;

/**
 *******************************************************************************
 * \brief IPC object extern declaration
 *******************************************************************************
 */
extern System_IpcObj gSystem_ipcObj;

Int32 System_ipcInit(void);
Int32 System_ipcDeInit(void);

Void  System_ipcHandler(UInt32 payload);

Void  System_ipcStart(void);
Void  System_ipcStop(void);

Int32 System_ipcSendNotify(UInt32 linkId);
Int32 System_ipcSendMsg(UInt32 linkId, UInt32 cmd, Void * pPrm,
                            UInt32 prmSize, Bool waitAck);

Int32 System_ipcRegisterNotifyCb(UInt32 linkId, System_ipcNotifyCb notifyCb);

void  System_ipcMsgQHandler(UInt32 payload);

Int32 System_ipcNotifyInit(void);
Int32 System_ipcNotifyDeInit(void);

Int32 System_ipcNotifyRegister(void);
Int32 System_ipcNotifySendEvent(UInt32 linkId);
Int32 System_ipcNotifyUnregister(void);
Void System_ipcNotifyReset(UInt32 procId);

Int32 System_ipcMsgQInit(void);
Int32 System_ipcMsgQDeInit(void);

Void System_ipcMsgQTaskMain(UArg arg0, UArg arg1);
Int32 System_ipcMsgQSendMsg(UInt32 linkId, UInt32 cmd, Void * pPrm,
                            UInt32 prmSize, Bool waitAck);

Void System_ipcAttach(void);
Void System_ipcDetach(void);

Int32 System_rpmsgSendNotify(UInt32 linkId);

Int32 System_rpmsgInit(void);
Int32 System_rpmsgDeInit(void);

#endif

/* @} */
