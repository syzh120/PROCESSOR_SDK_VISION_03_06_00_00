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
  ******************************************************************************
 * \file mergeLink_tsk.c
 *
 * \brief  This file has the implementation of MERGE Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Apr 2016) : [YM] Ported to HLOS
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "mergeLink_priv.h"

/*******************************************************************************
 *  Function declarations
 *******************************************************************************
 */
Int32 MergeLink_drvCreate(MergeLink_Obj * pObj,
                          const MergeLink_CreateParams * pPrm);
Int32 MergeLink_drvProcessData(MergeLink_Obj * pObj);
Int32 MergeLink_drvDelete(MergeLink_Obj * pObj);
Int32 MergeLink_getLinkInfo(Void * ptr, System_LinkInfo * info);
Int32 MergeLink_getFullBuffers(Void * ptr, UInt16 queId,
                                System_BufferList * pBufList);
Int32 MergeLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                System_BufferList * pBufList);


/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
MergeLink_Obj gMergeLink_obj[MERGE_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief MERGE Link collects incoming buffers from multiple links and merges
 *     them into single output queue. There is no driver involved in merging the
 *     buffers. To keep code across all links consistent we use the same
 *     convention as MergeLink_drvCreate. This function does the following,
 *
 *     - Copies the user passed create params into the link object create params
 *     - Prepares output queue
 *
 * \param  pObj     [IN]  MERGE link instance handle
 * \param  pPrm     [IN]  Create params for MERGE link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 MergeLink_drvCreate(MergeLink_Obj * pObj,
                          const MergeLink_CreateParams * pPrm)
{
    Int32 status;
    System_LinkQueInfo *pInQueInfo, *pOutQueInfo;
    UInt32 inQue, numOutCh, chId;

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    OSA_assert(pPrm->numInQue <= MERGE_LINK_MAX_IN_QUE);

    status = OSA_bufCreate(&pObj->outBufQue, FALSE, FALSE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = OSA_mutexCreate(&(pObj->lock));
    OSA_assert(status == OSA_SOK);

    numOutCh = 0U;

    pOutQueInfo = &pObj->info.queInfo[0];

    for (inQue = 0U; inQue < pPrm->numInQue; inQue++)
    {
        status =
            System_linkGetInfo(pPrm->inQueParams[inQue].prevLinkId,
                               &pObj->inTskInfo[inQue]);
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
        OSA_assert(pPrm->inQueParams[inQue].prevLinkQueId < pObj->inTskInfo[inQue].numQue);

        pInQueInfo = &pObj->inTskInfo[inQue].queInfo
            [pPrm->inQueParams[inQue].prevLinkQueId];

        OSA_assert(pInQueInfo->numCh <= SYSTEM_MAX_CH_PER_OUT_QUE);
        for (chId = 0; chId < pInQueInfo->numCh; chId++)
        {
            OSA_assert(chId < SYSTEM_MAX_CH_PER_OUT_QUE);
            OSA_assert(numOutCh < SYSTEM_MAX_CH_PER_OUT_QUE);

            memcpy(&pOutQueInfo->chInfo[numOutCh],
                   &pInQueInfo->chInfo[chId],
                   sizeof(pOutQueInfo->chInfo[numOutCh]));

            pObj->inQueChNumMap[inQue][chId] = numOutCh;
            pObj->outQueChToInQueMap[numOutCh] = inQue;
            pObj->outQueChMap[numOutCh] = chId;

            numOutCh++;
        }

        pObj->inQueMaxCh[inQue] = pInQueInfo->numCh;
    }

    pObj->info.numQue = 1;
    pOutQueInfo->numCh = numOutCh;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function to delete MERGE link. This will simply delete the output
 *    queue and the semaphore
 *
 * \param  pObj     [IN]  MERGE link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 MergeLink_drvDelete(MergeLink_Obj * pObj)
{
    Int32 status;

    status = OSA_bufDelete(&pObj->outBufQue);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    OSA_mutexDelete(&pObj->lock);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to MERGE link to get output queue
 *    Information of MERGE link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queue information of MERGE link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 MergeLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;
    MergeLink_Obj *pObj = (MergeLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->info, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to MERGE link to get data from
 *    the output queue of MERGE link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 MergeLink_getFullBuffers(Void * ptr, UInt16 queId,
                                System_BufferList * pBufList)
{
    Int32 status;
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;
    MergeLink_Obj *pObj = (MergeLink_Obj *) pTsk->appData;

    status =  OSA_bufGetFull(&pObj->outBufQue, pBufList, OSA_TIMEOUT_NONE);
    if (status == 0)
    {
        pObj->stats.forwardCount += pBufList->numBuf;
    }
    return status;
}

/**
 *******************************************************************************
 * \brief MERGE Link collects incoming buffers and sends to single output queue.
 *     This function does the following,
 *
 *     - Merge buffers and sends across it's output queue
 *     - Send SYSTEM_CMD_NEW_DATA to it's connected link
 *
 * \param  pObj     [IN]  MERGE link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 MergeLink_drvProcessData(MergeLink_Obj * pObj)
{
    MergeLink_CreateParams *pCreateArgs;
    UInt32 inQue, bufId;
    Int32 status;
    System_Buffer *pBuf;
    Bool newDataAvailable;

    newDataAvailable = (Bool)FALSE;

    pCreateArgs = &pObj->createArgs;

    for (inQue = 0; inQue < pCreateArgs->numInQue; inQue++)
    {
        System_getLinksFullBuffers(pCreateArgs->inQueParams[inQue].prevLinkId,
                                  pCreateArgs->inQueParams[inQue].prevLinkQueId,
                                  &pObj->inBufList);

        if (pObj->inBufList.numBuf)
        {
            pObj->stats.recvCount[inQue] += pObj->inBufList.numBuf;
            for (bufId = 0; bufId < pObj->inBufList.numBuf; bufId++)
            {
                /* remap channel number */
                pBuf = pObj->inBufList.buffers[bufId];

                OSA_assert(pBuf->chNum < pObj->inQueMaxCh[inQue]);

                pBuf->chNum =
                    pObj->inQueChNumMap[inQue][pBuf->chNum];
            }

            status = OSA_bufPutFull(&pObj->outBufQue, &pObj->inBufList);
            OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

            newDataAvailable = (Bool)TRUE;
        }
    }

    if (((Bool)TRUE == pCreateArgs->notifyNextLink) &&
        ((Bool)TRUE == newDataAvailable))
    {
        System_sendLinkCmd(pCreateArgs->outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA, NULL);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to MERGE link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to MERGE link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 MergeLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                System_BufferList * pBufList)
{
    /* MISRA.PPARAM.NEEDS.CONST
     * MISRAC_2004 Rule_16.7
     * MISRAC_WAIVER:
     * Generic function prototype.
     */

    UInt32 bufId, inQue;
    MergeLink_CreateParams *pCreateArgs;
    System_Buffer *pBuf;
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;
    MergeLink_Obj *pObj = (MergeLink_Obj *) pTsk->appData;

    OSA_mutexLock(&(pObj->lock));

    pCreateArgs = &pObj->createArgs;

    for (inQue = 0; inQue < pCreateArgs->numInQue; inQue++)
    {
        pObj->freeBufList[inQue].numBuf = 0;
    }

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];

        OSA_assert(pBuf != NULL);

        inQue = pObj->outQueChToInQueMap[pBuf->chNum];

        pBuf->chNum = pObj->outQueChMap[pBuf->chNum];


        OSA_assert(inQue < pCreateArgs->numInQue);

        pObj->freeBufList[inQue].buffers
            [pObj->freeBufList[inQue].numBuf] = pBuf;

        pObj->freeBufList[inQue].numBuf++;
        pObj->stats.releaseCount[inQue]++;
    }

    for (inQue = 0; inQue < pCreateArgs->numInQue; inQue++)
    {
        if (pObj->freeBufList[inQue].numBuf)
        {
            System_putLinksEmptyBuffers(pCreateArgs->inQueParams[inQue].
                                       prevLinkId,
                                       pCreateArgs->inQueParams[inQue].
                                       prevLinkQueId,
                                       &pObj->freeBufList[inQue]);
        }
    }

    OSA_mutexUnlock(&(pObj->lock));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating MERGE link
 *     - Arrival of new data
 *     - Deleting MERGE link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void MergeLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    /* MISRA.PPARAM.NEEDS.CONST
     * MISRAC_2004 Rule_16.7
     * MISRAC_WAIVER:
     * Generic function prototype.
     */

    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Int32 status = 0;
    MergeLink_Obj *pObj = (MergeLink_Obj *) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                status = MergeLink_drvCreate(pObj, OSA_msgGetPrm(pMsg));
                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    pObj->state = SYSTEM_LINK_STATE_RUNNING;
                }
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;
        case SYSTEM_CMD_DELETE:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                MergeLink_drvDelete(pObj);
                pObj->state = SYSTEM_LINK_STATE_IDLE;
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;
        case SYSTEM_CMD_NEW_DATA:
            OSA_tskAckOrFreeMsg(pMsg, status);

            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                MergeLink_drvProcessData(pObj);
            }
            break;
        default:
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for MERGE link. This function does the following for
 *   each MERGE link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 MergeLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 mergeId;
    MergeLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for (mergeId = 0U; mergeId < MERGE_LINK_OBJ_MAX; mergeId++)
    {
        pObj = &gMergeLink_obj[mergeId];

        memset(pObj, 0, sizeof(MergeLink_Obj));

        pObj->tskId =
            SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_MERGE_0 + mergeId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &MergeLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &MergeLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &MergeLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        status = MergeLink_tskCreate(mergeId);
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for MERGE link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 MergeLink_deInit(void)
{
    UInt32 mergeId;

    for (mergeId = 0U; mergeId < MERGE_LINK_OBJ_MAX; mergeId++)
    {
        OSA_tskDelete(&gMergeLink_obj[mergeId].tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
             gMergeLink_obj[mergeId].tskName, gMergeLink_obj[mergeId].linkId);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
