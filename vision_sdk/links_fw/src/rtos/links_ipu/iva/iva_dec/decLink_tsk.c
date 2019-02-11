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
 * \file DecLink_tsk.c
 *
 * \brief  This file has the implementation of Decode Link Init and Run API
 *
 *         This file implements the state machine logic for this link.
 *         DecodeLink_init() get calls from system_init and the same create
 *         the link task and basic messaging interfaces. Once the link is
 *         initiated it waits for the create cmd. This create cmd creates the
 *         complete link infrastructure.  Then waits for various data and
 *         control cmds.
 *
 *         This file also implements the Decode link tear down functionality
 *
 * \version 0.0 (Jun 2013) : [SS] First version
 * \version 0.1 (Jul 2013) : [SS] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "decLink_priv.h"

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gDecLink_tskStack, 32)
#pragma DATA_SECTION(gDecLink_tskStack, ".bss:taskStackSection")
UInt8 gDecLink_tskStack[DEC_LINK_OBJ_MAX][DEC_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Decode Link object, stores all link related information
 *******************************************************************************
 */
#pragma DATA_ALIGN(gDecLink_obj, 32)
#pragma DATA_SECTION(gDecLink_obj, ".bss:gDecLink_objSection")
DecLink_Obj gDecLink_obj[DEC_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function implements the START/RUN state of Decode Link.
 *
 *        In this state link gets commands to
 *         - Create the codec instance
 *         - Allocate output buffers
 *         - Moves to RUN state
 *        In this state link gets commands to
 *         - Stop/delete of link
 *         - Data events/cmds
 *         - All dynamic cmds that the link supports
 *         - All stats/status cmds
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Void DecLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status;
    DecLink_Obj *pObj;
    UInt32 flushCmds[2];
    UInt32 originalCmd;

    pObj = (DecLink_Obj *) pTsk->appData;

    /*
     * At this stage only create command is the expected command.
     * If other message gets received Ack with error status
     */
    if (cmd != SYSTEM_CMD_CREATE)
    {
        Utils_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EFAIL);
        return;
    }

    /*
     * Create command received, create the codec
     */
    status = DecLink_codecCreate(pObj, Utils_msgGetPrm(pMsg));

    Utils_tskAckOrFreeMsg(pMsg, status);

    if (status != SYSTEM_LINK_STATUS_SOK)
        return;

    Utils_encdecHdvicpPrfInit();
    done = FALSE;
    ackMsg = FALSE;
    pObj->pMsgTmp = NULL;
    pObj->lateAckStatus = SYSTEM_LINK_STATUS_SOK;

    /*
     * This while loop implements RUN state. All the run time commands for
     * ackMsg Link are received and serviced in this while loop.
     * Control remains in this loop until delete commands arrives.
     */
    while (!done)
    {
        status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
        if (status != SYSTEM_LINK_STATUS_SOK)
            break;

        cmd = Utils_msgGetCmd(pMsg);

        /*
         * Different commands are serviced via this switch case. For each
         * command, after servicing, ACK or free message is sent before
         * proceeding to next state.
         */
        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:
                Utils_tskAckOrFreeMsg(pMsg, status);

                flushCmds[0] = SYSTEM_CMD_NEW_DATA;
                Utils_tskFlushMsg(pTsk, flushCmds, 1);

                DecLink_codecProcessData(pObj);
                break;

            case DEC_LINK_CMD_GET_PROCESSED_DATA:
                Utils_tskAckOrFreeMsg(pMsg, status);

                flushCmds[0] = DEC_LINK_CMD_GET_PROCESSED_DATA;
                Utils_tskFlushMsg(pTsk, flushCmds, 1);

                DecLink_codecGetProcessedDataMsgHandler(pObj);
                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                DecLink_printStatistics(pObj, TRUE);
                Utils_encdecHdvicpPrfPrint();
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                Utils_tskAckOrFreeMsg(pMsg, status);
                DecLink_printBufferStatus(pObj);
                break;

            case DEC_LINK_CMD_CREATE_CHANNEL:
                {
                    DecLink_CreateChannelInfo *params;

                    params = (DecLink_CreateChannelInfo*) Utils_msgGetPrm(pMsg);
                    if (DEC_LINK_S_SUCCESS ==
                        DecLink_codecCreateChannelHandler(pObj, params))
                    {
                        Utils_tskAckOrFreeMsg(pMsg, status);
                    }
                    else
                    {
                        UTILS_assert(pObj->pMsgTmp == NULL);
                        pObj->pMsgTmp = pMsg;
                        pObj->lateAckStatus = SYSTEM_LINK_STATUS_EFAIL;
                    }
                }
                break;

            case DEC_LINK_CMD_DELETE_CHANNEL:
                {
                    DecLink_ChannelInfo *params;

                    params = (DecLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                    DecLink_codecDeleteChannelHandler(pObj, params);
                    UTILS_assert(pObj->pMsgTmp == NULL);
                    pObj->pMsgTmp = pMsg;
                    pObj->lateAckStatus = SYSTEM_LINK_STATUS_SOK;
                }
                break;

            case DEC_LINK_CMD_LATE_ACK:
                UTILS_assert(pObj->pMsgTmp != NULL);
                originalCmd = Utils_msgGetCmd(pObj->pMsgTmp);
                Utils_tskAckOrFreeMsg(pMsg, status);
                UTILS_assert((originalCmd == DEC_LINK_CMD_DELETE_CHANNEL) ||
                             ((originalCmd == DEC_LINK_CMD_CREATE_CHANNEL) &&
                              (pObj->lateAckStatus == SYSTEM_LINK_STATUS_EFAIL)));
                if (pObj->pMsgTmp != NULL)
                {
                    Utils_tskAckOrFreeMsg(pObj->pMsgTmp, pObj->lateAckStatus);
                }
                pObj->pMsgTmp = NULL;
                break;

            case DEC_LINK_CMD_DISABLE_CHANNEL:
                {
                    DecLink_ChannelInfo *params;

                    params = (DecLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                    DecLink_codecDisableChannel(pObj, params);
                    Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
            case DEC_LINK_CMD_ENABLE_CHANNEL:
                {
                    DecLink_ChannelInfo *params;

                    params = (DecLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                    DecLink_codecEnableChannel(pObj, params);
                    Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;

            case DEC_LINK_CMD_SET_TRICKPLAYCONFIG:
                {
                    DecLink_TPlayConfig * params;
                    params = (DecLink_TPlayConfig *) Utils_msgGetPrm(pMsg);
                    DecLink_setTPlayConfig(pObj, params);
                    Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;

            case SYSTEM_CMD_STOP:
                DecLink_codecStop(pObj);
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;

            case SYSTEM_CMD_DELETE:
                DecLink_codecStop(pObj);
                done = TRUE;
                ackMsg = TRUE;
                break;
            case DEC_LINK_CMD_GET_BUFFER_STATISTICS:
            {
                DecLink_BufferStats * params;

                params = (DecLink_BufferStats *) Utils_msgGetPrm(pMsg);
                DecLink_getBufferStatus(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;
            }
            default:
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    DecLink_codecDelete(pObj);

    if (ackMsg && pMsg != NULL)
        Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *******************************************************************************
 *
 *   \brief Decode link register and init function
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    DecLink_Obj *pObj;
    UInt32 objId;

    Utils_encdecInit();

    for (objId = 0; objId < DEC_LINK_OBJ_MAX; objId++)
    {
        pObj = &gDecLink_obj[objId];

        memset(pObj, 0, sizeof(*pObj));
        pObj->linkId = SYSTEM_LINK_ID_VDEC_0 + objId;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = DecLink_getFullFrames;
        linkObj.linkPutEmptyBuffers = DecLink_putEmptyFrames;
        linkObj.getLinkInfo = DecLink_getInfo;

        snprintf(pObj->name, 32U, "DEC%d   ", objId);

        System_registerLink(pObj->linkId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * DecodeLink_tskMain is called when a message command is received.
         */
        status = Utils_tskCreate(&pObj->tsk,
                                 DecLink_tskMain,
                                 DEC_LINK_TSK_PRI,
                                 gDecLink_tskStack[objId],
                                 DEC_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 *   \brief Decode link de-register and de-init function
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_deInit(void)
{
    UInt32 objId;
    DecLink_Obj *pObj;

    for (objId = 0; objId < DEC_LINK_OBJ_MAX; objId++)
    {
        pObj = &gDecLink_obj[objId];

        Utils_tskDelete(&pObj->tsk);
    }

    Utils_encdecDeInit();

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function return the channel info to the next link
 *
 * \param  pTsk     [IN]  Task Handle
 * \param  info     [OUT] channel info
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DecLink_getInfo(Void * pTsk, System_LinkInfo * info)
{
    Utils_TskHndl * pTskHndl = (Utils_TskHndl *)pTsk;
    DecLink_Obj *pObj = (DecLink_Obj *) pTskHndl->appData;

    /* 'info' structure is set with valid values during 'create' phase */
    memcpy(info, &pObj->info, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * Dec link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from Dec link
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
Int32 DecLink_getFullFrames(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    DecLink_Obj *pObj = (DecLink_Obj *) pTsk->appData;

    UTILS_assert(queId < DEC_LINK_MAX_OUT_QUE);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    return Utils_bufGetFullExt(&pObj->outObj.bufOutQue, pBufList,
                               BSP_OSAL_NO_WAIT);
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
Int32 DecLink_putEmptyFrames(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    DecLink_Obj *pObj = (DecLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(queId < DEC_LINK_MAX_OUT_QUE);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    status =  DecLink_codecFreeProcessedFrames(pObj, pBufList);

    return status;
}

/* Nothing beyond this point */

