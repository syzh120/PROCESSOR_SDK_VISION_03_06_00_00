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
 * \file autosar_ipcInLink_tsk.c
 *
 * \brief  This file has the implementation of AUTOSAR IPC IN Link API
 *
 * \version 0.0 (Aug 2018) : [AKG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "autosar_ipcInLink_priv.h"

/*******************************************************************************
 *  Function Prototype's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#pragma DATA_ALIGN(gAutosarIpcInLink_tskStack, 32)
/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#pragma DATA_SECTION(gAutosarIpcInLink_tskStack, ".bss:taskStackSection:ipc")

UInt8 gAutosarIpcInLink_tskStack[AUTOSAR_IPC_IN_LINK_OBJ_MAX][SYSTEM_TSK_STACK_SIZE_SMALL];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */

AutosarIpcInLink_obj gAutosarIpcInLink_obj[AUTOSAR_IPC_IN_LINK_OBJ_MAX];

/**
 ******************************************************************************
 * \ Global IPC Shared Memory Object
 ******************************************************************************
 */
extern System_IpcSharedMemObj  gSystem_autosarIpcSharedMemObj;

/**
 *******************************************************************************
 *
 * \brief Create task for this link
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 AutosarIpcInLink_tskCreate(UInt32 instId)
{
    Int32                status;
    AutosarIpcInLink_obj        *pObj;

    pObj = &gAutosarIpcInLink_obj[instId];

    snprintf(pObj->name, 32U, "Autosar_Ipc_In_%d",  (UInt32)instId);
    /*
     * Create link task, task remains in IDLE state.
     * AutosarIpcInLink_tskMain is called when a message command is received.
     */
    status = Utils_tskCreate(&pObj->tsk,
                             AutosarIpcInLink_tskMain,
                             IPC_LINK_TSK_PRI,
                             gAutosarIpcInLink_tskStack[instId],
                             SYSTEM_TSK_STACK_SIZE_SMALL,
                             pObj,
                             pObj->name,
                             UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Idle state.
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Void AutosarIpcInLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32           cmd = Utils_msgGetCmd(pMsg);
    Int32            status = SYSTEM_LINK_STATUS_SOK;
    AutosarIpcInLink_obj    *pObj;
    UInt32          flushCmds[1];

    pObj = (AutosarIpcInLink_obj *) pTsk->appData;

    /*
     * Different commands are serviced via this switch case. For each
     * command, after servicing, ACK or free message is sent before
     * proceeding to next state.
     */
    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:

            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                /*
                 * Create command received, create the IPC related data structure's
                 */
                status = AutosarIpcInLink_drvCreate(pObj);

                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    pObj->state = SYSTEM_LINK_STATE_RUNNING;
                }
            }

            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_NEW_DATA:

            Utils_tskAckOrFreeMsg(pMsg, status);

            flushCmds[0] = SYSTEM_CMD_NEW_DATA;
            Utils_tskFlushMsg(pTsk, flushCmds, 1U);

            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                /* if STOP state then dont handle buffers */
                status  = AutosarIpcInLink_drvProcessBuffers(pObj);
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:

            if(pObj->state!=SYSTEM_LINK_STATE_IDLE)
            {
                status = AutosarIpcInLink_drvPrintStatistics(pObj);
            }

            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_DELETE:
        {
            status = SYSTEM_LINK_STATUS_SOK;
            status = AutosarIpcInLink_drvDelete(pObj);
            pObj->state = SYSTEM_LINK_STATE_IDLE;

            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is error situation and should never execute.
            */
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
            }

            Utils_tskAckOrFreeMsg(pMsg, status);
        }
            break;

        /*
         * Invalid command for this state.  ACK it and continue RUN
         */
        default:
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;
    }

    return;
}
/**
 *******************************************************************************
 *
 * \brief Init function for IPC Lib.
 *
 *******************************************************************************
*/
Void AutosarIpcInLink_ipcLibInit(void)
{
    Int32 status = IPCLIB_SOK;
    UInt32 numprocs = 0U;

    IpcLib_InterruptInitPrms initPrm;
    IpcLib_interruptSetDefaultInitPrm(&initPrm);

    initPrm.validProcIds[numprocs] = IPCLIB_IPU1_0_ID;
    numprocs++;
    initPrm.validProcIds[numprocs] = IPCLIB_IPU2_0_ID;
    numprocs++;

    initPrm.numValidProcs   = numprocs;
    initPrm.msgTimeOut      = 0xFFFF;

    status = IpcLib_interruptInit(&initPrm);
    UTILS_assert(status == IPCLIB_SOK);
}
/**
 *******************************************************************************
 *
 * \brief Fuction for registering interrupt callback
 *
 * \param  pObj     [IN]  Link object
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 AutosarIpcInLink_registerInterruptCallback(AutosarIpcInLink_obj *pObj)
{
    Int32 status = IPCLIB_SOK;

    /* register notify handler with system framework */
    status = IpcLib_interruptRegisterEvent(
                IPCLIB_IPU2_0_ID,
                AUTOSAR_IPC_IN_NEW_BUFF_IPC_EVENT_ID,
                (IpcLib_InterruptCallback) (&AutosarIpcInLink_drvNotifyCb),
                pObj);
    UTILS_assert(status==IPCLIB_SOK);
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Fuction for unregistering interrupt callback
 *
 * \param  pObj     [IN]  Link object
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 AutosarIpcInLink_unRegisterInterruptCallback(AutosarIpcInLink_obj *pObj)
{
    Int32 status = IPCLIB_SOK;

    /* unregister notify handler with system framework */
    status = IpcLib_interruptUnregisterEvent(
                IPCLIB_IPU2_0_ID,
                AUTOSAR_IPC_IN_NEW_BUFF_IPC_EVENT_ID);
    UTILS_assert(status==IPCLIB_SOK);
    return status;
}
/**
 *******************************************************************************
 *
 * \brief Init function for IPC In link. BIOS task for
 *        link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 AutosarIpcInLink_init(void)
{
    Int32                status;
    UInt32               instId;
    System_LinkObj       linkObj;
    AutosarIpcInLink_obj        *pObj;
    UInt32               procId = System_getSelfProcId();

    for(instId = 0; instId<AUTOSAR_IPC_IN_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gAutosarIpcInLink_obj[instId];

        memset(pObj, 0, sizeof(AutosarIpcInLink_obj));

        pObj->linkId =
            SYSTEM_MAKE_LINK_ID(procId,
                                SYSTEM_LINK_ID_AUTOSAR_IPC_IN_0 + instId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        pObj->linkInstId = instId;

        memset(&linkObj, 0, sizeof(linkObj));

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = NULL;
        linkObj.linkPutEmptyBuffers = NULL;
        linkObj.getLinkInfo         = NULL;

        System_registerLink(pObj->linkId, &linkObj);

        status = AutosarIpcInLink_tskCreate(instId);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        /* Initialization should not be done when IPC Lib is included as it will already be done by system */
#ifndef IPC_LIB_INCLUDE
        /* Initializing IPC Lib */
        if (gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.ipcInitDone != IPC_INIT_DONE)
        {
            gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.ipcInitDone = IPC_INIT_DONE;
            AutosarIpcInLink_ipcLibInit();
        }
#endif
        /*
         * Register the interrupt callback
         */
        status = AutosarIpcInLink_registerInterruptCallback(pObj);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for IPC In link. BIOS task for
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AutosarIpcInLink_deInit(void)
{
    AutosarIpcInLink_obj *pObj;
    UInt32 instId;
    Int32 status;

    for(instId = 0; instId<AUTOSAR_IPC_IN_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gAutosarIpcInLink_obj[instId];

        Utils_tskDelete(&pObj->tsk);

        /*
         * Un-register the interrupt callback
         */
        status = AutosarIpcInLink_unRegisterInterruptCallback(pObj);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

#ifndef IPC_LIB_INCLUDE
        /* Deinitializing IPC Lib */
        if (gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.ipcInitDone == IPC_INIT_DONE)
        {
            gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.ipcInitDone = 0;
            IpcLib_interruptDeInit();
        }
#endif
    }
    return status;
}
