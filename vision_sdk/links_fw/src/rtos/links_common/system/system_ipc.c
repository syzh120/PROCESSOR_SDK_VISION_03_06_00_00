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
 * \file system_ipc.c
 *
 * \brief  Wrapper around IPC components calls.
 *
 *         This file implements wrapper around IPC calls. It also groups
 *         multiple ipc calls in one wrapper function wherever required.
 *
 * \version 0.0 (Jun 2013) : [KC] First version taken from DVR RDK and
 *                            cleaned up for Vision_sdk
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "system_priv_ipc.h"

/**
 *******************************************************************************
 * \brief Global object for storing IPC related information..
 *
 *        Handle stores IPC related information like messageQ handles,
 *        Base address to message memories etc.
 *******************************************************************************
 */
System_IpcObj gSystem_ipcObj;

#ifndef BUILD_A15
#pragma DATA_SECTION(gSystem_ipcSharedMemObj,".bss:extMemNonCache:ipcShm");
#pragma DATA_ALIGN(gSystem_ipcSharedMemObj, 4);
#endif
System_IpcSharedMemObj  gSystem_ipcSharedMemObj
#ifdef BUILD_A15
__attribute__ ((section(".bss:extMemNonCache:ipcShm")))
__attribute__ ((aligned(4)))
#endif
;

#ifndef BUILD_A15
#pragma DATA_SECTION(gSystem_autosarIpcSharedMemObj,".bss:extMemNonCache:autosarIpcShm");
#pragma DATA_ALIGN(gSystem_autosarIpcSharedMemObj, 4);
#endif
System_IpcSharedMemObj  gSystem_autosarIpcSharedMemObj
#ifdef BUILD_A15
__attribute__ ((section(".bss:extMemNonCache:autosarIpcShm")))
__attribute__ ((aligned(4)))
#endif
;

Void System_ipcHandler(UInt32 payload)
{
    UInt32 linkId, type;

#ifdef SYSTEM_IPC_MSGQ_DEBUG
    UTILS_assert(System_getSelfProcId() == SYSTEM_GET_PROC_ID(payload));

    Vps_printf(" SYSTEM: NOTIFY: Recevied notify (type=%d, payload=0x%08x) !!!\n", type, payload);
#endif

    type = SYSTEM_LINK_ID_GET_NOTIFY_TYPE(payload);

    #ifdef WORKQ_INCLUDE
    if (type == SYSTEM_LINK_ID_NOTIFY_TYPE_WORK_QUEUE)
    {
        System_workMsgHandler(payload);
    }
    else
    #endif
    if(type==SYSTEM_LINK_ID_NOTIFY_TYPE_LINK_ID)
    {
        linkId = SYSTEM_GET_LINK_ID(payload);

        if (linkId < SYSTEM_LINK_ID_MAX)
        {
            Utils_TskHndl *pTsk;

            if (gSystem_ipcObj.notifyCb[linkId])
            {
                pTsk = System_getLinkTskHndl(linkId);

                gSystem_ipcObj.notifyCb[linkId] (pTsk);
            }
        }
    }
    else
    if (type == SYSTEM_LINK_ID_NOTIFY_TYPE_OPENVX)
    {
        System_openVxIpcHandler(payload, NULL);
    }
    else
    {
        System_ipcMsgQHandler(payload);
    }
}

/**
 *******************************************************************************
 *
 * \brief Wrapper to initialize IPC sub-system.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_ipcInit(void)
{
    UInt32 procId = System_getSelfProcId();

    Vps_printf(" SYSTEM: IPC init in progress !!!\n");

    System_ipcNotifyInit();

    Vps_printf(" SYSTEM: Notify init done !!!\n");

    System_ipcMsgQInit();

    Vps_printf(" SYSTEM: MsgQ init done !!!\n");

	#ifdef WORKQ_INCLUDE
    System_workInit();
    Vps_printf(" SYSTEM: Work Queue init done !!!\n");
	#endif

#ifndef ROBUST_RVC_INCLUDE
    #ifdef A15_TARGET_OS_LINUX
    #ifndef BUILD_ARP32
    System_rpmsgInit();
    #endif
    #endif
#endif

    Vps_printf(" SYSTEM: IPC init DONE !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}
/**
 *******************************************************************************
 *
 * \brief Wrapper to de-initialize IPC sub-system.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_ipcDeInit(void)
{
    UInt32 procId = System_getSelfProcId();

    Vps_printf(" SYSTEM: IPC de-init in progress !!!\n");

#ifndef ROBUST_RVC_INCLUDE
    #ifdef A15_TARGET_OS_LINUX
    #ifndef BUILD_ARP32
    System_rpmsgDeInit();
    #endif
    #endif
#endif

    #ifdef WORKQ_INCLUDE
    System_workDeInit();
    Vps_printf(" SYSTEM: Work Queue deinit done !!!\n");
	#endif

    System_ipcNotifyDeInit();

    System_ipcMsgQDeInit();

    Vps_printf(" SYSTEM: IPC de-init DONE !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}

Bool System_isProcEnabled(UInt32 procId)
{
    UInt32 i;
    Bool isEnabled;

    i = 0;
    isEnabled = (Bool)FALSE;

    while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
    {
        if(procId == gSystem_ipcEnableProcId[i])
        {
            isEnabled = (Bool)TRUE;
            break;
        }

        i++;
    }

    return isEnabled;
}

char *System_getProcName(UInt32 procId)
{
    char * retVal = SYSTEM_IPC_PROC_NAME_INVALID;
    if(procId==SYSTEM_PROC_DSP1)
    {
        retVal = SYSTEM_IPC_PROC_NAME_DSP1;
    }
    if(procId==SYSTEM_PROC_DSP2)
    {
        retVal = SYSTEM_IPC_PROC_NAME_DSP2;
    }
    if(procId==SYSTEM_PROC_EVE1)
    {
        retVal = SYSTEM_IPC_PROC_NAME_EVE1;
    }
    if(procId==SYSTEM_PROC_EVE2)
    {
        retVal = SYSTEM_IPC_PROC_NAME_EVE2;
    }
    if(procId==SYSTEM_PROC_EVE3)
    {
        retVal = SYSTEM_IPC_PROC_NAME_EVE3;
    }
    if(procId==SYSTEM_PROC_EVE4)
    {
        retVal = SYSTEM_IPC_PROC_NAME_EVE4;
    }
    if(procId==SYSTEM_PROC_IPU1_0)
    {
        retVal = SYSTEM_IPC_PROC_NAME_IPU1_0;
    }
    if(procId==SYSTEM_PROC_IPU1_1)
    {
        retVal = SYSTEM_IPC_PROC_NAME_IPU1_1;
    }
    if(procId==SYSTEM_PROC_IPU2)
    {
        retVal = SYSTEM_IPC_PROC_NAME_IPU2;
    }
    if(procId==SYSTEM_PROC_A15_0)
    {
        retVal = SYSTEM_IPC_PROC_NAME_A15_0;
    }

    return retVal;
}

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
    UTILS_assert(linkId < SYSTEM_LINK_ID_MAX);

    gSystem_ipcObj.notifyCb[linkId] = notifyCb;

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
    #ifdef A15_TARGET_OS_LINUX
    #ifndef BUILD_ARP32
    {
        UInt32 dstProcId = SYSTEM_GET_PROC_ID(linkId);

        if(dstProcId==SYSTEM_PROC_A15_0)
        {
            return System_rpmsgSendNotify(linkId);
        }
    }
    #endif
    #endif

    return System_ipcNotifySendEvent(linkId);
}

/**
 *******************************************************************************
 *
 * \brief   Helper function to send messages to other links.
 *
 *          Allocates the message from free queue and send it to the link
 *          also waits for the acknowledgement for the message.
 *
 * \param  linkId    [IN] LinkId for which message is intended
 * \param  cmd       [IN] Command for message
 * \param  pPrm       [IN] Message parameter
 * \param  prmSize   [IN] Size of parameter
 * \param  waitAck   [IN] If True wait till ack is received, else proceed
 *                        without ack.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcSendMsg(UInt32 linkId, UInt32 cmd, Void * pPrm,
                            UInt32 prmSize, Bool waitAck)
{
    return System_ipcMsgQSendMsg(linkId, cmd, pPrm, prmSize, waitAck);
}

System_IpcMsg *System_ipcGetMsg(uint32_t procId)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;
    System_IpcMsg *pPrm = NULL;

    if(procId < SYSTEM_PROC_MAX)
    {
        pPrm = &pObj->ipcMsgObj.procMsg[procId];
    }

    return pPrm;
}

System_IpcQueObj *System_ipcGetIpcOut2InQue(uint32_t ipcOutLinkId)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;
    System_IpcQueObj *pPrm = NULL;
    UInt32 procId = SYSTEM_GET_PROC_ID(ipcOutLinkId);
    UInt32 linkId = SYSTEM_GET_LINK_ID(ipcOutLinkId);
    UInt32 linkInstId;

    if((procId < SYSTEM_PROC_MAX)
        &&  (linkId < SYSTEM_LINK_ID_MAX)
        &&  ((Int32)linkId >= SYSTEM_LINK_ID_IPC_OUT_0))
    {
        linkInstId = linkId - SYSTEM_LINK_ID_IPC_OUT_0;

        if(linkInstId < SYSTEM_IPC_OUT_LINK_MAX)
        {
            pPrm =
                &pObj->ipcQueObj.ipcQueProcObj[procId].queOut2InObj[linkInstId];
        }
    }

    return pPrm;
}

System_IpcQueObj *System_ipcGetIpcIn2OutQue(uint32_t ipcOutLinkId)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;
    System_IpcQueObj *pPrm = NULL;
    UInt32 procId = SYSTEM_GET_PROC_ID(ipcOutLinkId);
    UInt32 linkId = SYSTEM_GET_LINK_ID(ipcOutLinkId);
    UInt32 linkInstId;

    if((procId < SYSTEM_PROC_MAX)
        &&  (linkId < SYSTEM_LINK_ID_MAX)
        &&  ((Int32)linkId >= SYSTEM_LINK_ID_IPC_OUT_0))
    {
        linkInstId = linkId - SYSTEM_LINK_ID_IPC_OUT_0;

        if(linkInstId < SYSTEM_IPC_OUT_LINK_MAX)
        {
            pPrm =
                &pObj->ipcQueObj.ipcQueProcObj[procId].queIn2OutObj[linkInstId];
        }
    }

    return pPrm;
}

System_IpcBuffer *System_ipcGetIpcBuffer(uint32_t ipcOutLinkId, uint32_t idx)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;
    System_IpcBuffer *pPrm = NULL;
    UInt32 procId = SYSTEM_GET_PROC_ID(ipcOutLinkId);
    UInt32 linkId = SYSTEM_GET_LINK_ID(ipcOutLinkId);
    UInt32 linkInstId;

    if((procId < SYSTEM_PROC_MAX)
        &&  (linkId < SYSTEM_LINK_ID_MAX)
        &&  (idx  < SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS)
        &&  ((Int32)linkId >= SYSTEM_LINK_ID_IPC_OUT_0)
        )
    {
        linkInstId = linkId - SYSTEM_LINK_ID_IPC_OUT_0;

        if(linkInstId < SYSTEM_IPC_OUT_LINK_MAX)
        {
            pPrm =
                &pObj->ipcQueObj.ipcQueProcObj[procId].queElements[linkInstId][idx];
        }
    }

    return pPrm;
}

NetworkCons_RxShm *System_networkConsGetRxQue(void)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;

    return &pObj->networkConsRxShm;
}

NetworkCons_TxShm *System_networkConsGetTxQue(void)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;

    return &pObj->networkConsTxShm;
}

System_WorkIpcObj *System_workQGetIpcObj(void)
{
    System_IpcSharedMemObj *pObj = &gSystem_ipcSharedMemObj;

    return &pObj->workIpcObj;
}

