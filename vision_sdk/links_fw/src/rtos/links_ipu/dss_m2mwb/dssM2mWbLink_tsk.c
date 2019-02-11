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
 * \file dssM2mWbLink_tsk.c
 *
 * \brief  This file has the implementation of DSSM2MWB Link Init and Run API
 *
 *         This file implements the state machine logic for this link.
 *         DssM2mWbLink_init() get calls from system_init and the same create
 *         the link task and basic messaging interfaces. Once the link is
 *         initiated it waits for the create cmd. This create cmd creates the
 *         complete link infrastructure.  Then waits for various data and
 *         control cmds.
 *
 *         This file also implements the dssm2mwb link tear down functionality
 *
 * \version 0.0 (Sept 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "dssM2mWbLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */

Void DssM2mWbLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl * pMsg);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gDssM2mWbLink_tskStack, 32)
#pragma DATA_SECTION(gDssM2mWbLink_tskStack, ".bss:taskStackSection")
UInt8 gDssM2mWbLink_tskStack[DSSM2MWB_LINK_OBJ_MAX][DSSM2MWB_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief DSSM2MWB Link object, stores all link related information
 *******************************************************************************
 */
DssM2mWbLink_Obj gDssM2mWbLink_obj[DSSM2MWB_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function implements the DSSM2MWB link Create, Run/Steady state
 *
 *        In this state link gets commands to
 *         - Create the DSSM2MWB Driver
 *         - Stop/delete of link
 *         - Data events/cmds
 *         - All dynamic cmds that the link supports
 *         - All stats/status cmds
 *
 *          DES_ID: DOX_DES_TAG(DES_DssM2mWb_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1264)
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Void DssM2mWbLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done, stopDone;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    DssM2mWbLink_ChannelInfo * channelInfo;
    DssM2mWbLink_Obj *pObj;
    UInt32 flushCmds[2];

    pObj = (DssM2mWbLink_Obj *) pTsk->appData;

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
        status = DssM2mWbLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

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

                        DssM2mWbLink_drvProcessData(pObj);
                        break;

                    case SYSTEM_CMD_PRINT_STATISTICS:
                        DssM2mWbLink_printStatistics(pObj, (Bool)TRUE);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                        DssM2mWbLink_printBufferStatus(pObj);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case DSSM2MWB_LINK_CMD_ENABLE_CHANNEL:
                        channelInfo = (DssM2mWbLink_ChannelInfo *) Utils_msgGetPrm(pMsg);
                        DssM2mWbLink_drvSetChannelInfo(pObj,channelInfo);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case SYSTEM_CMD_STOP:
                        /* stop RUN loop and goto READY state */
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        stopDone = (Bool) TRUE;
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

        DssM2mWbLink_drvDelete(pObj);

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
 *   \brief DSSM2MWB link register and init function
 *
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *          DES_ID: DOX_DES_TAG(DES_DssM2mWb_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1264)
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DssM2mWbLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    DssM2mWbLink_Obj *pObj;

    UInt32 objId;

    for (objId = 0U; objId < DSSM2MWB_LINK_OBJ_MAX; objId++)
    {
        pObj = &gDssM2mWbLink_obj[objId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId = SYSTEM_LINK_ID_DSSM2MWB_0 + objId;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &DssM2mWbLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &DssM2mWbLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &DssM2mWbLink_getLinkInfo;

        snprintf(pObj->name, 32U, "DSSM2MWB%d    ", (Int32) objId);

        System_registerLink(pObj->linkId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * DssM2mWbLink_tskMain is called when a message command is received.
         */
        status = Utils_tskCreate(&pObj->tsk,
                                 DssM2mWbLink_tskMain,
                                 DSSM2MWB_LINK_TSK_PRI,
                                 gDssM2mWbLink_tskStack[objId],
                                 DSSM2MWB_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 *   \brief DSSM2MWB link de-register and de-init function
 *
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *          DES_ID: DOX_DES_TAG(DES_DssM2mWb_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1264)
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DssM2mWbLink_deInit(void)
{
    UInt32 objId;
    DssM2mWbLink_Obj *pObj;

    for (objId = 0U; objId < DSSM2MWB_LINK_OBJ_MAX; objId++)
    {
        pObj = &gDssM2mWbLink_obj[objId];

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
Int32 DssM2mWbLink_getLinkInfo(Void *pTsk, System_LinkInfo *info)
{
    Utils_TskHndl *pTskHndl = (Utils_TskHndl *)pTsk;
    DssM2mWbLink_Obj *pObj = (DssM2mWbLink_Obj *)pTskHndl->appData;

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
 * DSSM2MWB link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from DSSM2MWB link
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
Int32 DssM2mWbLink_getFullBuffers(
                        Void *ptr,
                        UInt16 queId,
                        System_BufferList *pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *)ptr;
    DssM2mWbLink_Obj *pObj = (DssM2mWbLink_Obj *) pTsk->appData;

    UTILS_assert(queId == 0U);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    return Utils_bufGetFull(&pObj->bufOutQue, pBufList, BSP_OSAL_NO_WAIT);
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
Int32 DssM2mWbLink_putEmptyBuffers(
                        Void *ptr,
                        UInt16 queId,
                        System_BufferList *pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *)ptr;
    DssM2mWbLink_Obj *pObj = (DssM2mWbLink_Obj *)pTsk->appData;

    UTILS_assert(queId == 0U);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.putEmptyBufCount++;

    return Utils_bufPutEmpty(&pObj->bufOutQue, pBufList);
}

/* Nothing beyond this point */

