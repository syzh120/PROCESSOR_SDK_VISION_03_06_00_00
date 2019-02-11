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
 * \file ipcOutLink_tsk.c
 *
 * \brief  This file has the implementataion of IPC OUT Link API
 *
 *         This file implements the state machine logic for this link.
 *         A message command will cause the state machine to take some
 *         action and then move to a different state.
 *         IPC OUT link follows the below state machine
 *
 *            Cmds| CREATE | STOP | ALL OTHER COMMANDS | DELETE |
 *         States |========|======|====================|========|
 *           IDLE | RUN    | -    | -                  | -      |
 *           RUN  | -      | STOP | -                  | -      |
 *           STOP | -      | -    | -                  | IDLE   |
 *
 *
 * \version 0.0 (May 2014) : [YM] First version ported to linux
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ipcOutLink_priv.h"

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
IpcOutLink_Obj gIpcOutLink_obj[IPC_OUT_LINK_OBJ_MAX];


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
Int32 IpcOutLink_getLinkInfo(Void *pTsk,
                             System_LinkInfo *info)
{
    OSA_TskHndl * pTskHndl = (OSA_TskHndl *)pTsk;
    IpcOutLink_Obj * pObj = (IpcOutLink_Obj * )pTskHndl->appData;

    /* 'info' structure is set with valid values during 'create' phase
     * Simply pass on previous link info to next link
     */

    memcpy(info, &pObj->linkInfo, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
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
Int32 IpcOutLink_tskRun(IpcOutLink_Obj * pObj, OSA_TskHndl * pTsk)
{
    Int32          status  = SYSTEM_LINK_STATUS_SOK;
    Bool           runDone = FALSE, stopDone = FALSE;
    OSA_MsgHndl *pRunMsg;
    UInt32         cmd;

    /*
     * This while loop implements RUN state. All the commands for IPC OUT
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
                    status  = IpcOutLink_drvProcessBuffers(pObj);
                }
                break;

            case IPC_OUT_LINK_CMD_RELEASE_FRAMES:

                OSA_tskAckOrFreeMsg(pRunMsg, status);

                if(!stopDone)
                {
                    /* if STOP state then dont handle buffers */
                    status = IpcOutLink_drvReleaseBuffers(pObj);
                }
                break;

            case SYSTEM_CMD_STOP:

                if(!stopDone)
                {
                    status = IpcOutLink_drvStop(pObj);

                    stopDone = TRUE;
                }

                OSA_tskAckOrFreeMsg(pRunMsg, status);

                break;

            case IPC_OUT_LINK_CMD_SET_FRAME_RATE:

                status = IpcOutLink_drvSetFrameRate(
                                        pObj,
                                        OSA_msgGetPrm(pRunMsg));

                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_STATISTICS:

                status = IpcOutLink_drvPrintStatistics(pObj);

                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_DELETE:

                if(!stopDone)
                {
                    status = IpcOutLink_drvStop(pObj);
                }

                status |= IpcOutLink_drvDelete(pObj);

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
Int32 IpcOutLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    UInt32               cmd = OSA_msgGetCmd(pMsg);
    Int32                status;
    IpcOutLink_Obj      *pObj;

    pObj = (IpcOutLink_Obj *) pTsk->appData;

    /*
     * At this stage only create command is the expected command.
     * If other message gets received Ack with error status
     */
    if (cmd != SYSTEM_CMD_CREATE)
    {
        OSA_tskAckOrFreeMsg(pMsg, OSA_EFAIL);
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    /*
     * Create command received, create the IPC related data structure's
     */
    status = IpcOutLink_drvCreate(pObj, OSA_msgGetPrm(pMsg));

    OSA_tskAckOrFreeMsg(pMsg, status);

    /*
     * If create status is error then remain in IDLE state
     */
    if (status != SYSTEM_LINK_STATUS_SOK)
        return SYSTEM_LINK_STATUS_EFAIL;

    /*
     * Entering RUN state
     */
    status = IpcOutLink_tskRun(pObj, pTsk);

    /*
     * Entering IDLE state
     */
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Init function for IPC Out link. OSA_tsk for
 *        link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 IpcOutLink_init(void)
{
    Int32                status;
    UInt32               instId;
    System_LinkObj       linkObj;
    IpcOutLink_Obj      *pObj;
    UInt32               procId = System_getSelfProcId();

    for(instId = 0; instId < IPC_OUT_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIpcOutLink_obj[instId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId =
            SYSTEM_MAKE_LINK_ID(procId,
                                SYSTEM_LINK_ID_IPC_OUT_0) + instId;

        pObj->linkInstId = instId;

        memset(&linkObj, 0, sizeof(linkObj));

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = NULL;
        linkObj.linkPutEmptyBuffers = NULL;
        linkObj.getLinkInfo         = IpcOutLink_getLinkInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /* register notify handler with system framework */
        System_ipcRegisterNotifyCb(pObj->linkId, IpcOutLink_drvNotifyCb);


        /* allocate shared memory for IPC queue */
        pObj->ipcOut2InSharedMemBaseAddr =
            System_ipcGetIpcOut2InQue(pObj->linkId);
        OSA_assert(pObj->ipcOut2InSharedMemBaseAddr!=NULL);

        /* Translate to virtual */
        pObj->ipcIn2OutSharedMemBaseAddr =
            System_ipcGetIpcIn2OutQue(pObj->linkId);
        OSA_assert(pObj->ipcIn2OutSharedMemBaseAddr!=NULL);

        /* create IPC queue's */
        status = OSA_ipcQueCreate(
                            &pObj->ipcOut2InQue,
                            SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1,
                            pObj->ipcOut2InSharedMemBaseAddr,
                            sizeof(UInt32)
                        );
        OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

        status = OSA_ipcQueCreate(
                            &pObj->ipcIn2OutQue,
                            SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1,
                            pObj->ipcIn2OutSharedMemBaseAddr,
                            sizeof(UInt32)
                        );
        OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

        /*
         * Create link task, task remains in IDLE state.
         * ipcOutLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "IPC_OUT_%u", (unsigned int)instId);
        status = OSA_tskCreate(&pObj->tsk,
                               IpcOutLink_tskMain,
                               IPC_LINK_TSK_PRI,
                               IPC_OUT_LINK_TSK_STACK_SIZE,
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
 * \brief De-Init function for IPC Out link. BIOS task for
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IpcOutLink_deInit(void)
{
    IpcOutLink_Obj *pObj;
    UInt32 instId;

    for(instId = 0; instId<IPC_OUT_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIpcOutLink_obj[instId];

        OSA_tskDelete(&pObj->tsk);

        System_ipcRegisterNotifyCb(pObj->linkId, NULL);

        OSA_ipcQueDelete(&pObj->ipcIn2OutQue);
        OSA_ipcQueDelete(&pObj->ipcOut2InQue);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n", pObj->tskName, pObj->linkId);
    }

    return SYSTEM_LINK_STATUS_SOK;
}
