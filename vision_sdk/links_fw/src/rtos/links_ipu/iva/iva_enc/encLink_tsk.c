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
 * \file encLink_tsk.c
 *
 * \brief  This file has the implementation of Encode Link Init and Run API
 *
 *         This file implements the state machine logic for this link.
 *         EncodeLink_init() get calls from system_init and the same create
 *         the link task and basic messaging interfaces. Once the link is
 *         initiated it waits for the create cmd. This create cmd creates the
 *         complete link infrastructure.  Then waits for various data and
 *         control cmds.
 *
 *         This file also implements the Encode link tear down functionality
 *
 * \version 0.0 (April 2014) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "encLink_priv.h"

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gEncLink_tskStack, 32)
#pragma DATA_SECTION(gEncLink_tskStack, ".bss:taskStackSection")
UInt8 gEncLink_tskStack[ENC_LINK_OBJ_MAX][ENC_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Encode Link object, stores all link related information
 *******************************************************************************
 */
#pragma DATA_ALIGN(gEncLink_obj, 32)
#pragma DATA_SECTION(gEncLink_obj, ".bss:gEncLink_objSection")
EncLink_Obj gEncLink_obj[ENC_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function implements the START/RUN state of Encode Link.
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
Void EncLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    EncLink_Obj *pObj;
    UInt32 flushCmds[2];
    UInt32 originalCmd;

    pObj = (EncLink_Obj *) pTsk->appData;

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
    status = EncLink_codecCreate(pObj, Utils_msgGetPrm(pMsg));

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

                EncLink_codecProcessData(pObj);
                break;

            case ENC_LINK_CMD_GET_PROCESSED_DATA:
                Utils_tskAckOrFreeMsg(pMsg, status);

                flushCmds[0] = ENC_LINK_CMD_GET_PROCESSED_DATA;
                Utils_tskFlushMsg(pTsk, flushCmds, 1);

                EncLink_codecGetProcessedDataMsgHandler(pObj);
                break;

            case ENC_LINK_CMD_GET_CODEC_PARAMS:
                {
                EncLink_GetDynParams *params = {0};

                params = (EncLink_GetDynParams *) Utils_msgGetPrm(pMsg);

                params->inputHeight
                    = pObj->chObj[params->chId].algObj.algDynamicParams.inputHeight;
                params->inputWidth
                    = pObj->chObj[params->chId].algObj.algDynamicParams.inputWidth;
                params->targetBitRate
                    = pObj->chObj[params->chId].algObj.algDynamicParams.targetBitRate;
                params->targetFps
                    = pObj->chObj[params->chId].algObj.algDynamicParams.targetFrameRate;
                params->intraFrameInterval
                    = pObj->chObj[params->chId].algObj.algDynamicParams.intraFrameInterval;

                Utils_tskAckOrFreeMsg(pMsg, status);

                EncLink_codecGetDynParams(pObj, params);
                }
                break;

            case ENC_LINK_CMD_SET_CODEC_BITRATE:
                {
                EncLink_ChBitRateParams *params;

                params = (EncLink_ChBitRateParams *) Utils_msgGetPrm(pMsg);
                status = EncLink_codecSetBitrate(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;

           case ENC_LINK_CMD_SET_CODEC_INPUT_FPS:
                {
                EncLink_ChInputFpsParam *params;

                params = (EncLink_ChInputFpsParam *) Utils_msgGetPrm(pMsg);
                EncLink_codecInputSetFps(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;

            case ENC_LINK_CMD_SET_CODEC_FPS:
                {
                EncLink_ChFpsParams *params;

                params = (EncLink_ChFpsParams *) Utils_msgGetPrm(pMsg);
                status = EncLink_codecSetFps(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
            case ENC_LINK_CMD_SET_CODEC_INTRAI:
                {
                EncLink_ChIntraFrIntParams *params;

                params = (EncLink_ChIntraFrIntParams *) Utils_msgGetPrm(pMsg);
                EncLink_codecSetIntraIRate(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
            case ENC_LINK_CMD_SET_CODEC_FORCEI:
                {
                EncLink_ChannelInfo *params;

                params = (EncLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                EncLink_codecSetForceIDR(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
            case ENC_LINK_CMD_SET_CODEC_RCALGO:
                {
                    EncLink_ChRcAlgParams *params;

                    params = (EncLink_ChRcAlgParams *) Utils_msgGetPrm(pMsg);
                    EncLink_codecSetrcAlg(pObj, params);
                    Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
            case ENC_LINK_CMD_SET_CODEC_QP_I:
               {
               EncLink_ChQPParams *params;

               params = (EncLink_ChQPParams *) Utils_msgGetPrm(pMsg);
               EncLink_codecSetqpParamI(pObj, params);
               Utils_tskAckOrFreeMsg(pMsg, status);
               }
               break;
            case ENC_LINK_CMD_SET_CODEC_QP_P:
               {
               EncLink_ChQPParams *params;

               params = (EncLink_ChQPParams *) Utils_msgGetPrm(pMsg);
               EncLink_codecSetqpParamP(pObj, params);
               Utils_tskAckOrFreeMsg(pMsg, status);
               }
               break;
            case ENC_LINK_CMD_SET_CODEC_SNAPSHOT:
               {
                  EncLink_ChannelInfo *params;
                  params = (EncLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                  EncLink_codecForceDumpFrame(pObj, params);
                  Utils_tskAckOrFreeMsg(pMsg, status);
               }
               break;
            case ENC_LINK_CMD_SET_CODEC_VBRD:
               {
               EncLink_ChCVBRDurationParams *params;

               params = (EncLink_ChCVBRDurationParams *) Utils_msgGetPrm(pMsg);
               EncLink_codecSetVBRDuration(pObj, params);
               Utils_tskAckOrFreeMsg(pMsg, status);
               }
               break;
            case ENC_LINK_CMD_SET_CODEC_VBRS:
               {
               EncLink_ChCVBRSensitivityParams *params;

               params = (EncLink_ChCVBRSensitivityParams *) Utils_msgGetPrm(pMsg);
               EncLink_codecSetVBRSensitivity(pObj, params);
               Utils_tskAckOrFreeMsg(pMsg, status);
               }
               break;
           case ENC_LINK_CMD_SET_CODEC_ROI:
               {
               EncLink_ChROIParams *params;

               params = (EncLink_ChROIParams *) Utils_msgGetPrm(pMsg);
               EncLink_codecSetROIPrms(pObj, params);
               Utils_tskAckOrFreeMsg(pMsg, status);
               }
               break;

            case ENC_LINK_CMD_DISABLE_CHANNEL:
                {
                EncLink_ChannelInfo *params;

                params = (EncLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                EncLink_codecDisableChannel(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
            case ENC_LINK_CMD_ENABLE_CHANNEL:
                {
                EncLink_ChannelInfo *params;

                params = (EncLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                EncLink_codecEnableChannel(pObj, params);
                Utils_tskAckOrFreeMsg(pMsg, status);
                }
                break;
           case ENC_LINK_CMD_SWITCH_CODEC_CHANNEL:
                {
                    EncLink_ChSwitchCodecTypeParams *params;

                    params = (EncLink_ChSwitchCodecTypeParams *) Utils_msgGetPrm(pMsg);
                    EncLink_codecSwitchCodec(pObj, params);
                    UTILS_assert(pObj->pMsgTmp == NULL);
                    pObj->pMsgTmp = pMsg;
                    pObj->lateAckStatus = SYSTEM_LINK_STATUS_SOK;
                }
                break;
            case ENC_LINK_CMD_LATE_ACK:
                UTILS_assert(pObj->pMsgTmp != NULL);
                originalCmd = Utils_msgGetCmd(pObj->pMsgTmp);
                Utils_tskAckOrFreeMsg(pMsg, status);
                UTILS_assert(originalCmd == ENC_LINK_CMD_SWITCH_CODEC_CHANNEL);
                if (pObj->pMsgTmp != NULL)
                {
                    Utils_tskAckOrFreeMsg(pObj->pMsgTmp, pObj->lateAckStatus);
                }
                pObj->pMsgTmp = NULL;
                break;
            case SYSTEM_CMD_PRINT_STATISTICS:
                EncLink_printStatistics(pObj, TRUE);
                Utils_encdecHdvicpPrfPrint();
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                Utils_tskAckOrFreeMsg(pMsg, status);
                EncLink_printBufferStatus(pObj);
                break;

            case SYSTEM_CMD_STOP:
                EncLink_codecStop(pObj);
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;

            case SYSTEM_CMD_DELETE:
                EncLink_codecStop(pObj);
                done = TRUE;
                ackMsg = TRUE;
                break;

            default:
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    EncLink_codecDelete(pObj);

    if (ackMsg && pMsg != NULL)
        Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *******************************************************************************
 *
 *   \brief Encode link register and init function
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    EncLink_Obj *pObj;
    UInt32 objId;

    Utils_encdecInit();

    for (objId = 0; objId < ENC_LINK_OBJ_MAX; objId++)
    {
        pObj = &gEncLink_obj[objId];

        memset(pObj, 0, sizeof(*pObj));
        pObj->linkId = SYSTEM_LINK_ID_VENC_0 + objId;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = EncLink_getFullFrames;
        linkObj.linkPutEmptyBuffers = EncLink_putEmptyFrames;
        linkObj.getLinkInfo = EncLink_getInfo;

        snprintf(pObj->name, 32U, "ENC%d   ", objId);

        System_registerLink(pObj->linkId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * EncodeLink_tskMain is called when a message command is received.
         */
        status = Utils_tskCreate(&pObj->tsk,
                                 EncLink_tskMain,
                                 ENC_LINK_TSK_PRI,
                                 gEncLink_tskStack[objId],
                                 ENC_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 *   \brief Encode link de-register and de-init function
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_deInit(void)
{
    UInt32 objId;
    EncLink_Obj *pObj;

    for (objId = 0; objId < ENC_LINK_OBJ_MAX; objId++)
    {
        pObj = &gEncLink_obj[objId];

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
Int32 EncLink_getInfo(Void * pTsk, System_LinkInfo * info)
{
    Utils_TskHndl * pTskHndl = (Utils_TskHndl *)pTsk;
    EncLink_Obj *pObj = (EncLink_Obj *) pTskHndl->appData;

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
Int32 EncLink_getFullFrames(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    EncLink_Obj *pObj = (EncLink_Obj *) pTsk->appData;

    UTILS_assert(queId < ENC_LINK_MAX_OUT_QUE);
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
Int32 EncLink_putEmptyFrames(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    EncLink_Obj *pObj = (EncLink_Obj *) pTsk->appData;

    UTILS_assert(queId < ENC_LINK_MAX_OUT_QUE);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    return Utils_bufPutEmptyExt(&pObj->outObj.bufOutQue, pBufList);
}

/* Nothing beyond this point */

