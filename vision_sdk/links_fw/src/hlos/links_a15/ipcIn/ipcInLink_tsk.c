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
 * \file ipcInLink_tsk.c
 *
 * \brief  This file has the implementation of IPC IN Link API
 *
 *         This file implements the state machine logic for this link.
 *         A message command will cause the state machine to take some
 *         action and then move to a different state.
 *         IPC IN link follows the below state machine
 *
 *            Cmds| CREATE | STOP | ALL OTHER COMMANDS | DELETE |
 *         States |========|======|====================|========|
 *           IDLE | RUN    | -    | -                  | -      |
 *           RUN  | -      | STOP | -                  | -      |
 *           STOP | -      | -    | -                  | IDLE   |
 *
 * \version 0.0 (Aug 2013) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ipcInLink_priv.h"

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
IpcInLink_obj gIpcInLink_obj[IPC_IN_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function return the channel info to the next link
 *
 * \param  pTsk     [IN]  Task Handle
 * \param  pTsk     [OUT] channel info
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_getLinkInfo(Void *pTsk,
                             System_LinkInfo *info)
{
    OSA_TskHndl * pTskHndl = (OSA_TskHndl *)pTsk;
    IpcInLink_obj * pObj = (IpcInLink_obj * )pTskHndl->appData;

    /* 'info' structure is set with valid values during 'create' phase */

    memcpy(info, &pObj->linkInfo, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * ipcIn link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from ipcIn
 * output queue.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/

Int32 IpcInLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    IpcInLink_obj *pObj = (IpcInLink_obj *) pTsk->appData;

    return IpcInLink_drvGetFullBuffers(pObj, pBufList);
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IpcInLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    IpcInLink_obj *pObj = (IpcInLink_obj *) pTsk->appData;

    return IpcInLink_drvPutEmptyBuffers(pObj, pBufList);
}

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Run and stop state.
 *
 *        In this state link gets commands to process incoming frames from
 *        previous link and release processed frames from next link to previous
 *        link
 *
 * \param  pTsk     [IN] Task Handle
 * \param  pObj     [IN] Link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_tskRun(IpcInLink_obj * pObj, OSA_TskHndl * pTsk)
{
    Int32          status  = SYSTEM_LINK_STATUS_SOK;
    Bool           runDone = FALSE, stopDone = FALSE;
    OSA_MsgHndl *pRunMsg;
    UInt32         cmd;

    /*
     * This while loop implements RUN state. All the commands for IPC IN
     * are received and serviced in this while loop. Control remains
     * in this loop until delete commands arrives.
     */
    while (!runDone)
    {
        /*
         * Wait for message indefinitely here. Once message arrives, extract
         * the command.
         */
        status = OSA_tskWaitMsg(pTsk, &pRunMsg);
        if (status != OSA_SOK)
            break;
        cmd = OSA_msgGetCmd(pRunMsg);

        /*
         * Different commands are serviced via this switch case. For each
         * command, after servicing, ACK or free message is sent before
         * proceeding to next state.
         */
        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:

                OSA_tskAckOrFreeMsg(pRunMsg, status);

                if(!stopDone)
                {
                    /* if STOP state then dont handle buffers */
                    status  = IpcInLink_drvProcessBuffers(pObj);
                }
                break;

            case SYSTEM_CMD_STOP:

                if(!stopDone)
                {
                    status = IpcInLink_drvStop(pObj);

                    stopDone = TRUE;
                }

                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_STATISTICS:

                status = IpcInLink_drvPrintStatistics(pObj);

                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_DELETE:

                if(!stopDone)
                {
                    status = IpcInLink_drvStop(pObj);
                }

                status |= IpcInLink_drvDelete(pObj);

                OSA_tskAckOrFreeMsg(pRunMsg, status);

                runDone = TRUE;
                break;

            /*
             * Start is made as dummy for this link, since there is
             * no need.
             */
            case SYSTEM_CMD_START:
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            /*
             * Invalid command for this state.  ACK it and continue RUN
             */
            default:
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }
    }

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
Int32 IpcInLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    UInt32           cmd = OSA_msgGetCmd(pMsg);
    Int32            status;
    IpcInLink_obj    *pObj;

    pObj = (IpcInLink_obj *) pTsk->appData;

    /*
     * At this stage only create command is the expected command.
     * If other message gets received Ack with error status
     */
    if (cmd != SYSTEM_CMD_CREATE)
    {
        OSA_tskAckOrFreeMsg(pMsg, OSA_EFAIL);
        return OSA_EFAIL;
    }

    /*
     * Create command received, create the IPC related data structure's
     */
    status = IpcInLink_drvCreate(pObj, OSA_msgGetPrm(pMsg));

    OSA_tskAckOrFreeMsg(pMsg, status);

    /*
     * If create status is error then remain in IDLE state
     */
    if (status != SYSTEM_LINK_STATUS_SOK)
        return OSA_SOK;

    /*
     * Entering RUN state
     */
    status = IpcInLink_tskRun(pObj, pTsk);

    /*
     * Entering IDLE state
     */
    return OSA_SOK;
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
Int32 IpcInLink_init(void)
{
    Int32                status;
    UInt32               instId;
    System_LinkObj       linkObj;
    IpcInLink_obj        *pObj;
    UInt32               procId = System_getSelfProcId();

    for(instId = 0; instId<IPC_IN_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIpcInLink_obj[instId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId =
            SYSTEM_MAKE_LINK_ID(procId,
                                SYSTEM_LINK_ID_IPC_IN_0 + instId);

        pObj->linkInstId = instId;

        memset(&linkObj, 0, sizeof(linkObj));

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = IpcInLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = IpcInLink_putEmptyBuffers;
        linkObj.getLinkInfo         = IpcInLink_getLinkInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /* register notify handler with system framework */
        System_ipcRegisterNotifyCb(pObj->linkId, IpcInLink_drvNotifyCb);


        /*
         * Create link task, task remains in IDLE state.
         * IpcInLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "IPC_IN_%u", (unsigned int)instId);
        status = OSA_tskCreate(&pObj->tsk,
                                 IpcInLink_tskMain,
                                 IPC_LINK_TSK_PRI,
                                 IPC_IN_LINK_TSK_STACK_SIZE,
                                 0,
                                 pObj,
                                 pObj->tskName);
        OSA_assert(status == OSA_SOK);
        Vps_printf(" %s : Init done - linkid-0x%x\n", pObj->tskName, pObj->linkId);

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
Int32 IpcInLink_deInit(void)
{
    IpcInLink_obj *pObj;
    UInt32 instId;

    for(instId = 0; instId<IPC_IN_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIpcInLink_obj[instId];

        OSA_tskDelete(&pObj->tsk);

        System_ipcRegisterNotifyCb(pObj->linkId, NULL);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n", pObj->tskName, pObj->linkId);
    }

    return SYSTEM_LINK_STATUS_SOK;
}
