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
 * \file vpeLink_tsk.c
 *
 * \brief  This file has the implementation of VPE Link Init and Run API
 *
 *         This file implements the state machine logic for this link.
 *         VpeLink_init() get calls from system_init and the same create
 *         the link task and basic messaging interfaces. Once the link is
 *         initiated it waits for the create cmd. This create cmd creates the
 *         complete link infrastructure.  Then waits for various data and
 *         control cmds.
 *
 *         This file also implements the vpe link tear down functionality
 *
 * \version 0.0 (Sept 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "vpeLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */

Void VpeLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl * pMsg);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gVpeLink_tskStack, 32)
#pragma DATA_SECTION(gVpeLink_tskStack, ".bss:taskStackSection")
UInt8 gVpeLink_tskStack[VPE_LINK_OBJ_MAX][VPE_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief VPE Link object, stores all link related information
 *******************************************************************************
 */
VpeLink_Obj gVpeLink_obj[VPE_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function implements the VPE link Create, Run/Steady state
 *
 *        In this state link gets commands to
 *         - Create the VPE Driver
 *         - Stop/delete of link
 *         - Data events/cmds
 *         - All dynamic cmds that the link supports
 *         - All stats/status cmds
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Void VpeLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done, stopDone;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    VpeLink_ChannelInfo * channelInfo;
    VpeLink_Obj *pObj;
    UInt32 flushCmds[2];

    pObj = (VpeLink_Obj *) pTsk->appData;

    /*
     * At this stage only create command is the expected command.
     * If other message gets received Ack with error status
     */
    if (cmd != SYSTEM_CMD_CREATE)
    {
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the driver   */
        status = VpeLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

        Utils_tskAckOrFreeMsg(pMsg, status);
    }

    if (status == SYSTEM_LINK_STATUS_SOK)
    {

        done = (Bool)FALSE;
        ackMsg = (Bool)FALSE;
        stopDone = (Bool)FALSE;

        /*
        * This while loop implements RUN state. All the run time commands for
        * ackMsg Link are received and serviced in this while loop.
        * Control remains in this loop until delete commands arrives.
        */
        while (!done)
        {
            status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }

            cmd = Utils_msgGetCmd(pMsg);

            if ((stopDone == (Bool)TRUE) && (cmd != SYSTEM_CMD_DELETE))
            {
                /* once stop is done, only DELETE command should be accepted */
                Utils_tskAckOrFreeMsg(pMsg, status);
            }
            else
            {

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
                        Utils_tskFlushMsg(pTsk, flushCmds, 1U);

                        VpeLink_drvProcessData(pObj);
                        break;

                    case SYSTEM_CMD_PRINT_STATISTICS:
                        VpeLink_printStatistics(pObj, (Bool)TRUE);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                        VpeLink_printBufferStatus(pObj);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case VPE_LINK_CMD_GET_OUTPUTRESOLUTION:
                        {
                            VpeLink_ChDynamicSetOutRes *params;

                            params = (VpeLink_ChDynamicSetOutRes *) Utils_msgGetPrm(pMsg);
                            VpeLink_drvGetChDynamicOutputRes(pObj, params);
                            Utils_tskAckOrFreeMsg(pMsg, status);
                        }
                        break;

                    case VPE_LINK_CMD_SET_OUTPUTRESOLUTION:
                        {
                            VpeLink_ChDynamicSetOutRes *params;

                            params = (VpeLink_ChDynamicSetOutRes *) Utils_msgGetPrm(pMsg);
                            VpeLink_drvSetChDynamicOutputRes(pObj, params);
                            Utils_tskAckOrFreeMsg(pMsg, status);
                        }
                        break;

                    case VPE_LINK_CMD_SET_FRAME_RATE:
                        {
                            VpeLink_ChFpsParams *params;

                            params = (VpeLink_ChFpsParams *) Utils_msgGetPrm(pMsg);
                            VpeLink_drvSetFrameRate(pObj, params);
                            Utils_tskAckOrFreeMsg(pMsg, status);
                        }
                        break;

                    case VPE_LINK_CMD_ENABLE_CHANNEL:

                        channelInfo = (VpeLink_ChannelInfo *) Utils_msgGetPrm(pMsg);

                        VpeLink_drvSetChannelInfo(pObj,channelInfo);

                        Utils_tskAckOrFreeMsg(pMsg, status);

                        break;

                    case SYSTEM_CMD_STOP:
                        VpeLink_drvStop(pObj);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        stopDone = (Bool)TRUE;
                        break;

                    case SYSTEM_CMD_DELETE:
                        done = (Bool)TRUE;
                        ackMsg = (Bool)TRUE;
                        break;

                    default:
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;
                }
            }
        }

        VpeLink_drvDelete(pObj);

        if ((ackMsg != (Bool)FALSE) && (pMsg != NULL))
        {
            Utils_tskAckOrFreeMsg(pMsg, status);
        }
    }
    return;
}

/**
 *******************************************************************************
 *
 *   \brief VPE link register and init function
 *
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VpeLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    VpeLink_Obj *pObj;

    UInt32 objId;

    for (objId = 0U; objId < VPE_LINK_OBJ_MAX; objId++)
    {
        pObj = &gVpeLink_obj[objId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId = SYSTEM_LINK_ID_VPE_0 + objId;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &VpeLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &VpeLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &VpeLink_getLinkInfo;

        snprintf(pObj->name, 32U, "VPE%d    ", (Int32) objId);

        System_registerLink(pObj->linkId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * VpeLink_tskMain is called when a message command is received.
         */
        status = Utils_tskCreate(&pObj->tsk,
                                 VpeLink_tskMain,
                                 VPE_LINK_TSK_PRI,
                                 gVpeLink_tskStack[objId],
                                 VPE_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 *   \brief VPE link de-register and de-init function
 *
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VpeLink_deInit(void)
{
    UInt32 objId;
    VpeLink_Obj *pObj;

    for (objId = 0U; objId < VPE_LINK_OBJ_MAX; objId++)
    {
        pObj = &gVpeLink_obj[objId];

        Utils_tskDelete(&pObj->tsk);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

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
Int32 VpeLink_getLinkInfo(Void * pTsk, System_LinkInfo * info)
{
    Utils_TskHndl * pTskHndl = (Utils_TskHndl *)pTsk;
    VpeLink_Obj *pObj = (VpeLink_Obj *) pTskHndl->appData;

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
 * VPE link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from VPE link
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
Int32 VpeLink_getFullBuffers(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    VpeLink_Obj *pObj = (VpeLink_Obj *) pTsk->appData;

    UTILS_assert(queId < VPE_LINK_OUT_QUE_ID_MAX);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    return Utils_bufGetFull(&pObj->outObj[queId].bufOutQue, pBufList,
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
Int32 VpeLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{
    UInt32 idx;
    UInt32 chId;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    VpeLink_Obj *pObj = (VpeLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(queId < VPE_LINK_OUT_QUE_ID_MAX);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);
    VpeLink_OutObj *pOutObj = &pObj->outObj[queId];

    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.putEmptyBufCount++;

    for (idx = 0U; idx < pBufList->numBuf; idx++)
    {
        chId = pBufList->buffers[idx]->chNum;
        UTILS_assert(chId < VPE_LINK_MAX_CH);
        UTILS_assert(UTILS_ARRAYISVALIDENTRY(pBufList->buffers[idx],
                                             pOutObj->buffers[chId]));
        /* MISRA.PTR.ARITH
        * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
        *                       arithmetic or array index expression
        * KW State: Ignore -> Waiver -> Case by case
        *
        * Pointer arithmetic is required for performance like auto increment in loop.
        * The harmful side effect of violating this rule (accessing outside valid memory)
        * shall be checked by another code checker like Klocwork.
        */
        status = Utils_quePut(&pOutObj->emptyBufQue[chId],
                              pBufList->buffers[idx], BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/* Nothing beyond this point */

