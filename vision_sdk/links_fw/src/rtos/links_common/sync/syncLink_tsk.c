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
 * \file syncLink_tsk.c
 *
 * \brief  This file has the implementation of Sync Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "syncLink_priv.h"


/*******************************************************************************
 *  Function prototype's
 *******************************************************************************
 */
Void SyncLink_addBuffersToDropListFromLocalQue(SyncLink_Obj * pObj, UInt32 chId);
Int32 SyncLink_addBuffersToDropListLesserThanThreshold(SyncLink_Obj * pObj);
Int32 SyncLink_computeDecisionParams(SyncLink_Obj * pObj,
                                                   Bool *syncDone);
Int32 SyncLink_fillLocalQueues(SyncLink_Obj * pObj);
Int32 SyncLink_makeCompositeBuffer(SyncLink_Obj * pObj, System_Buffer *pSysBuf);
Void SyncLink_dropBuffers(SyncLink_Obj * pObj);
Bool SyncLink_computeMasterTimeStamp(SyncLink_Obj * pObj);
Int32 SyncLink_drvCreate(SyncLink_Obj * pObj, const SyncLink_CreateParams *pPrm);
Int32 SyncLink_drvDelete(SyncLink_Obj *pObj);
Int32 SyncLink_start(SyncLink_Obj * pObj);
Int32 SyncLink_stop(SyncLink_Obj * pObj);
Int32 SyncLink_drvPrintStatistics(SyncLink_Obj *pObj);
Int32 SyncLink_drvProcessData(SyncLink_Obj * pObj);
Int32 SyncLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList);
Int32 SyncLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList);
Void SyncLink_timerCallback(UInt32 arg);
Int32 SyncLink_getLinkInfo(Void * ptr, System_LinkInfo * info);

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Utility macro that returns
 *  0 if x is in between a and b
 *  1 if x is greater than b
 * -1 if x is lesser than a
 *
 *******************************************************************************
*/
static Int32 INRANGE(UInt64 a, UInt64 b, UInt64 x);
static Int32 INRANGE(UInt64 a, UInt64 b, UInt64 x)
{
    Int32 value;

    if( (x >= a) && (x <= b) )
    {
        value = 0;
    }
    else
    if(x > b)
    {
        value = 1;
    }
    else
    {
        value = -(Int32)1;
    }

    return value;
}



/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
SyncLink_Obj gSyncLink_obj[SYNC_LINK_OBJ_MAX];

Void SyncLink_timerCallback(UInt32 arg)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic implementation which supports all dataTypes.
     * This typecasting is necessary.
     */
    SyncLink_Obj *pObj = (SyncLink_Obj *) arg;

    Utils_tskSendCmd(&pObj->tsk, SYSTEM_CMD_NEW_DATA, NULL);

    pObj->linkStatsInfo->linkStats.notifyEventCount++;
}

/**
 *******************************************************************************
 * \brief Sync link is a connector link. Sync Link is particularly targeted to
 *   a set of specific use cases where there is a need for a set of video
 *   frames from multiple channels to be in sync (Frames captured at
 *   approximately at the same time). This function does the following,
 *
 *    - Copies the user passed create params into the link object create params
 *    - Each composite buffer is tied up with a system buffer
 *    - Prepares output queue
 *
 * \param  pObj     [IN]  Sync link instance handle
 * \param  pPrm     [IN]  Create params for Sync link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SyncLink_drvCreate(SyncLink_Obj * pObj, const SyncLink_CreateParams *pPrm)
{
    UInt32 outId, chId, bufId;
    Int32 status;
    SyncLink_ChObj *chObj;
    System_Buffer *pSysBuf;
    System_VideoFrameCompositeBuffer *sysCompBuf;
    SyncLink_OrgBufferPtr *pOrgBufPtr;
    char                 tskName[32];

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    status = System_linkGetInfo(
                   pObj->createArgs.inQueParams.prevLinkId, &pObj->prevLinkInfo);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->prevLinkInfo.numQue);

    pObj->linkInfo.numQue = 1;
    memcpy(&pObj->linkInfo.queInfo[0],
           &pObj->prevLinkInfo.queInfo
                [pObj->createArgs.inQueParams.prevLinkQueId],
           sizeof(pObj->linkInfo.queInfo[0])
          );

    pObj->numCh =
           pObj->prevLinkInfo.queInfo
                  [pObj->createArgs.inQueParams.prevLinkQueId].numCh;
    UTILS_assert(pObj->numCh <= SYNC_LINK_MAX_CHANNELS);

    /*
     *  Initialize each channel
    */

    for (chId = 0; chId < pObj->numCh; chId++)
    {
        chObj = &pObj->chObj[chId];

        status = Utils_queCreate(&chObj->localQueHandle,
                                  UTILS_ARRAYSIZE(chObj->queMem),
                                  chObj->queMem,
                                  UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Associate each composite buffer with a system buffer
    */

    for (outId = 0; outId < SYNC_LINK_MAX_FRAMES_PER_OUT_QUE; outId++)
    {
       pSysBuf = &pObj->outBuf[outId];
       sysCompBuf = &pObj->compBuf[outId];
       pOrgBufPtr = &pObj->orgBufPtr[outId];

       pSysBuf->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
       pSysBuf->chNum = 0;
       pSysBuf->payload = sysCompBuf;
       pSysBuf->payloadSize = sizeof(System_VideoFrameCompositeBuffer);
       pSysBuf->pSyncLinkOrgBufferPtr = pOrgBufPtr;
    }

    status = Utils_bufCreate(&pObj->outFrameQue, FALSE, FALSE);

    for (bufId = 0; bufId < SYNC_LINK_MAX_FRAMES_PER_OUT_QUE; bufId++)
    {
        pSysBuf = &pObj->outBuf[bufId];
        status = Utils_bufPutEmptyBuffer(&pObj->outFrameQue, pSysBuf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    snprintf(tskName, sizeof(tskName), "SYNC_%u", pObj->linkInstId);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, tskName);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrame = (Bool)FALSE;
    pObj->outputFrmCnt = 0U;

    pObj->timer = BspOsal_clockCreate(
                            &SyncLink_timerCallback,
                            33U, (Bool)FALSE, pObj);
    UTILS_assert(pObj->timer != NULL);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief This function drops buffers in the local queues which are older than
 *        the user specified threshold
 *
 * \param  pObj     [IN]  Sync link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SyncLink_addBuffersToDropListLesserThanThreshold(SyncLink_Obj * pObj)
{
    UInt32 chId;
    Bool droppedBuffer;
    UInt64 curTime, diffTime;

    SyncLink_ChObj *chObj;
    System_Buffer *pBuffer;

    /* only if syncThreshold is < 10000, consider for dropping
     * else assume user did not want any buffer to be dropped
     */
    if(pObj->createArgs.syncThreshold < 10000)
    {
        do
        {
            droppedBuffer = (Bool)FALSE;

            for (chId = 0; chId < pObj->numCh; chId++)
            {
                chObj = &pObj->chObj[chId];

                /* MISRA.CAST.PTR
                 * MISRAC_2004 Rule_11.4
                 * MISRAC_WAIVER:
                 * This is a generic queue implementation which supports all dataTypes.
                 * This typecasting is necessary.
                 */
                Utils_quePeek(&chObj->localQueHandle, (Ptr *) &pBuffer);
                if ( pBuffer != NULL )
                {
                    /* diffTime is in msec's */
                    curTime = Utils_getCurGlobalTimeInUsec();

                    if(curTime < pBuffer->srcTimestamp)
                    {
                        diffTime = 0xFFFFFFFFU;
                    }
                    else
                    {
                        diffTime = (curTime - pBuffer->srcTimestamp)/1000U;
                    }

                    if (diffTime >= pObj->createArgs.syncThreshold)
                    {
                        SyncLink_addBuffersToDropListFromLocalQue(pObj, chId);
                        droppedBuffer = (Bool)TRUE;
                    }
                }
            }
        }
        while(droppedBuffer == (Bool)TRUE);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief For each top most buffer in the queue this function computes whether
 *        the timestamp of buffer is in the range specified by user.
 *
 * \param  pObj     [IN]  Sync link instance handle
 * \param  synDone  [OUT] Indicates whether sync is true or not
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 SyncLink_computeDecisionParams(SyncLink_Obj * pObj,
                                                   Bool *syncDone)
{
    UInt64 higherTimeStamp, lowerTimeStamp, syncDelta;
    UInt32 chId;
    Bool higherFlag;
    Int32 status;
    System_Buffer *pBuffer;
    Int32 inRange[SYNC_LINK_MAX_CHANNELS];

    *syncDone = (Bool)TRUE;

    /* if syncDelta is >= 1000, then user did not want any frames to
     * be dropped and any available frame to be synced
     * Hence in this case timestamp compare logic is skipped
     */
    if(pObj->createArgs.syncDelta<1000)
    {
        higherFlag = (Bool)FALSE;

        for (chId = 0; chId < pObj->numCh; chId++)
        {
            inRange[chId] = 0;
        }

        syncDelta = (UInt64)pObj->createArgs.syncDelta*1000UL; /* convert to in usec's */

        higherTimeStamp = pObj->masterTimeStamp + syncDelta;

        if(pObj->masterTimeStamp < syncDelta)
        {
            lowerTimeStamp = 0;
        }
        else
        {
            lowerTimeStamp  = pObj->masterTimeStamp - syncDelta;
        }

        for (chId = 0; chId < pObj->numCh; chId++)
        {
            /* MISRA.CAST.PTR
             * MISRAC_2004 Rule_11.4
             * MISRAC_WAIVER:
             * This is a generic queue implementation which supports all dataTypes.
             * This typecasting is necessary.
             */
            status = Utils_quePeek(
                            &pObj->chObj[chId].localQueHandle,
                            (Ptr *) &pBuffer
                            );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            if(pBuffer != NULL)
            {
                inRange[chId] = INRANGE(
                                    lowerTimeStamp,
                                    higherTimeStamp,
                                    pBuffer->srcTimestamp
                                    );
                if (inRange[chId] == -(Int32)1)
                {
                   SyncLink_addBuffersToDropListFromLocalQue(pObj, chId);
                   *syncDone = (Bool)FALSE;
                }
                else
                if (inRange[chId] == 1)
                {
                   higherFlag = (Bool)TRUE;
                   *syncDone = (Bool)FALSE;
                }
                else
                {
                    /* for MISRA-C */
                }
            }
        }
        if (higherFlag)
        {
            /*
             * Drop all channels who are in range also
             */
            for (chId = 0; chId < pObj->numCh; chId++)
            {
                if (inRange[chId] == 0)
                {
                    SyncLink_addBuffersToDropListFromLocalQue(pObj, chId);
                }
            }
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Void SyncLink_addBuffersToDropListFromLocalQue(SyncLink_Obj * pObj, UInt32 chId)
{
    Int32 status;
    System_Buffer *pBuffer;

    if(chId<pObj->numCh)
    {
        /* MISRA.CAST.PTR
         * MISRAC_2004 Rule_11.4
         * MISRAC_WAIVER:
         * This is a generic queue implementation which supports all dataTypes.
         * This typecasting is necessary.
         */
        status = Utils_queGet(&pObj->chObj[chId].localQueHandle,
                               (Ptr *) &pBuffer,
                               1U,
                               BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        pObj->dropBufList.buffers[pObj->dropBufList.numBuf] = pBuffer;
        pObj->dropBufList.numBuf++;

        pObj->linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufDropCount++;
    }
}

/**
 *******************************************************************************
 * \brief This function dequeus buffers from previous link and puts in local
 *        queues based on the channel number.
 *
 * \param  pObj     [IN]  Sync link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SyncLink_fillLocalQueues(SyncLink_Obj * pObj)
{
    UInt32 bufId;
    System_BufferList inputBufList;
    System_Buffer *pBuffer;
    System_LinkInQueParams *pInQueParams = &pObj->createArgs.inQueParams;
    Int32 status;

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId,
                               &inputBufList);

    for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
    {
        pBuffer = inputBufList.buffers[bufId];

        if ( (pBuffer == NULL)
             || (pBuffer->chNum >= pObj->numCh) )
        {
            pObj->linkStatsInfo->linkStats.inBufErrorCount++;
        }
        else
        {
            pBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

            pObj->linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufRecvCount++;

            status = Utils_quePut(&pObj->chObj[pBuffer->chNum].localQueHandle,
                                 pBuffer, BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief This function creates composite buffer when buffers from all local
 *        queues are available and are in sync
 *
 * \param  pObj     [IN]  Sync link instance handle
 * \param  pSysBuf  [OUT] System Buffer which hold pointer to composite buffer
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SyncLink_makeCompositeBuffer(SyncLink_Obj * pObj, System_Buffer *pSysBuf)
{
    Int32 status;
    UInt32 chId, i;
    System_Buffer *pBuf;
    System_VideoFrameCompositeBuffer *pSysCompBuf;
    SyncLink_OrgBufferPtr *pOrgBufPtr;

    UTILS_assert(pSysBuf != NULL);

    pOrgBufPtr = (SyncLink_OrgBufferPtr *)pSysBuf->pSyncLinkOrgBufferPtr;

    pSysBuf->srcTimestamp = pObj->masterTimeStamp;

    pSysCompBuf = (System_VideoFrameCompositeBuffer *)pSysBuf->payload;

    pSysCompBuf->numFrames = 0;

    memset(pOrgBufPtr, 0, sizeof(SyncLink_OrgBufferPtr));

    for (chId = 0; chId < pObj->numCh; chId++)
    {
        /* MISRA.CAST.PTR
         * MISRAC_2004 Rule_11.4
         * MISRAC_WAIVER:
         * This is a generic queue implementation which supports all dataTypes.
         * This typecasting is necessary.
         */
        status = Utils_queGet(&pObj->chObj[chId].localQueHandle,
                               (Ptr *) &pBuf,
                               1U,
                               BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        UTILS_assert(pBuf != NULL);

        pObj->linkStatsInfo->linkStats.chStats[pBuf->chNum].inBufProcessCount++;

        if(pBuf->bufType==SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
        {
            System_VideoFrameBuffer *pVidBuf;

            pVidBuf = (System_VideoFrameBuffer*) pBuf->payload;

            for (i=0; i < SYSTEM_MAX_PLANES; i++)
            {
                pSysCompBuf->bufAddr[i][pSysCompBuf->numFrames] =
                                                        pVidBuf->bufAddr[i];
            }
            pSysCompBuf->metaBufAddr[pSysCompBuf->numFrames] =
                                                       pVidBuf->metaBufAddr;

            if(chId==0)
            {
                /* Other fields of Composite buffer can be anything,
                 * so we arbitarily
                 * choose the first channel
                 */
                pSysCompBuf->metaBufSize = pVidBuf->metaBufSize;
                pSysCompBuf->metaFillLength = pVidBuf->metaFillLength;
                pSysCompBuf->chInfo = pVidBuf->chInfo;
                pSysCompBuf->flags = pVidBuf->flags;
            }
        }
        else
        if(pBuf->bufType==SYSTEM_BUFFER_TYPE_METADATA)
        {
            System_MetaDataBuffer *pMetaBuf;

            pMetaBuf = (System_MetaDataBuffer*) pBuf->payload;

            for (i=0; i < SYSTEM_MAX_PLANES; i++)
            {
                pSysCompBuf->bufAddr[i][pSysCompBuf->numFrames] =
                                                     pMetaBuf->bufAddr[i];
            }
            pSysCompBuf->metaBufAddr[pSysCompBuf->numFrames] = NULL;

            if(chId==0)
            {
                /* Other fields of Composite buffer can be anything,
                 * so we arbitarily
                 * choose the first channel
                 */
                pSysCompBuf->metaBufSize = pMetaBuf->metaBufSize[0];
                pSysCompBuf->metaFillLength = pMetaBuf->metaFillLength[0];
                memset(&pSysCompBuf->chInfo,
                        0,
                        sizeof(pSysCompBuf->chInfo));
                pSysCompBuf->flags = pMetaBuf->flags;
            }
        }
        else
        {
            Vps_printf(" SYNC: Unsupported buffer type (%d)\n", pBuf->bufType);
            UTILS_assert((Bool)FALSE);
        }

        pSysCompBuf->numFrames++;
        pOrgBufPtr->pOrgBuf[chId] = pBuf;

        Utils_updateLatency(&pObj->linkStatsInfo->linkLatency,
                        pBuf->linkLocalTimestamp);
    }
    pOrgBufPtr->numCh = pObj->numCh;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief This function drops all buffers present in the drop list and gives
 *        them back to the next link.
 *
 * \param  pObj     [IN]  Sync link instance handle
 *
 *******************************************************************************
*/
Void SyncLink_dropBuffers(SyncLink_Obj * pObj)
{
    if (pObj->dropBufList.numBuf)
    {
        System_putLinksEmptyBuffers(
                                     pObj->createArgs.inQueParams.prevLinkId,
                                     pObj->createArgs.inQueParams.prevLinkQueId,
                                     &pObj->dropBufList
                                   );
    }
    pObj->dropBufList.numBuf = 0;
    return;
}

/**
 *******************************************************************************
 * \brief This function computes the master timestamp only when all active
 *        channels have buffers
 *
 * \param  pObj     [IN]  Sync link instance handle
 * \return FALSE if masterTimeStamp is valid
 *         TRUE if masterTimeStamp is not  valid if an active channel has
 *         no buffer
 *
 *******************************************************************************
*/
Bool SyncLink_computeMasterTimeStamp(SyncLink_Obj * pObj)
{
    UInt32 chId;
    UInt64 sumOfAllTimestamps = 0;
    System_Buffer *pBuffer;
    Bool localQueEmptyFlag = (Bool)FALSE;

    for (chId = 0; chId < pObj->numCh; chId++)
    {
        /* MISRA.CAST.PTR
         * MISRAC_2004 Rule_11.4
         * MISRAC_WAIVER:
         * This is a generic queue implementation which supports all dataTypes.
         * This typecasting is necessary.
         */
         Utils_quePeek(
                        &pObj->chObj[chId].localQueHandle,
                        (Ptr *) &pBuffer
                      );
        if (pBuffer)
        {
            sumOfAllTimestamps += pBuffer->srcTimestamp;
        }
        else
        {
            localQueEmptyFlag = (Bool)TRUE;
        }
    }

    pObj->masterTimeStamp = sumOfAllTimestamps / pObj->numCh;

    return localQueEmptyFlag;
}

/**
 *******************************************************************************
 * \brief This function does the following,
 *
 *     - For each local queue check buffers have become too old, based on the
 *       threshold
 *     - Fill each local queue with the buffers got from previous link
 *     - If all local queues have buffers, then
 *        - Dequeue from local queues
 *        - Apply sync logic
 *        - If sync logic is successful, construct a composite buffer
 *            - Get a system buffer from Empty Queue
 *            - Get the composite buffer from the system buffer
 *            - Fill composite buffer with buffers dequeued from local queues
 *            - Get SyncLink_OrigBufferPtr from system byffer and fill it
 *              with the addresses of dequeued buffers
 *        - Send next link that data is available
 *
 *          DES_ID: DOX_DES_TAG(DES_SYNC_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1518)
 *
 * \param  pObj     [IN]  DUP link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/

Int32 SyncLink_drvProcessData(SyncLink_Obj * pObj)
{
    Bool syncDone;
    Bool localQueEmptyFlag;
    System_Buffer *pBuffer;
    Int32 status;
    UInt32 chId;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstFrame==FALSE)
    {
        pObj->isFirstFrame = (Bool)TRUE;

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);

        Utils_resetLinkStatistics(
                              &linkStatsInfo->linkStats,
                              pObj->numCh,
                              1U
                             );
    }

    linkStatsInfo->linkStats.newDataCmdCount++;
    pObj->dropBufList.numBuf = 0;

    SyncLink_addBuffersToDropListLesserThanThreshold(pObj);

    SyncLink_dropBuffers(pObj);

    SyncLink_fillLocalQueues(pObj);

    SyncLink_dropBuffers(pObj);

    do{
        localQueEmptyFlag = SyncLink_computeMasterTimeStamp(pObj);

        if (localQueEmptyFlag==(Bool)TRUE)
        {
            break;
        }

        SyncLink_computeDecisionParams(pObj, &syncDone);

        if(syncDone == (Bool)TRUE)
        {
            status = Utils_bufGetEmptyBuffer(&pObj->outFrameQue,
                        &pBuffer, BSP_OSAL_NO_WAIT);
            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                UTILS_assert(pBuffer != NULL);

                SyncLink_makeCompositeBuffer(pObj, pBuffer);

                linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

                Utils_updateLatency(&pObj->linkStatsInfo->srcToLinkLatency,
                                        pBuffer->srcTimestamp);

                pBuffer->frameId = pObj->outputFrmCnt;
                status = Utils_bufPutFullBuffer(&pObj->outFrameQue, pBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                                SYSTEM_CMD_NEW_DATA, NULL);
                pObj->outputFrmCnt = pObj->outputFrmCnt + 1U;
            }
            else
            {
                /*
                 * As output queue is not having any free the buffers,
                 * We can free the input buffer at this stage.
                 */
                for (chId = 0; chId < pObj->numCh; chId++)
                {
                    SyncLink_addBuffersToDropListFromLocalQue(pObj, chId);
                }
            }
        }
        SyncLink_dropBuffers(pObj);
    }while(1);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Sync link to get output queue
 *    Information of DUP link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of DUP link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SyncLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    SyncLink_Obj *pObj = (SyncLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Sync link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to DUP link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SyncLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{
    Uint32 bufId, i;
    Int32 status;
    System_Buffer *pBuf, *pOrgBuf;
    SyncLink_OrgBufferPtr *pOrgPtr;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    SyncLink_Obj *pObj = (SyncLink_Obj *) pTsk->appData;
    System_BufferList freeBufferList;

    pObj->linkStatsInfo->linkStats.putEmptyBufCount++;

    freeBufferList.numBuf = 0;

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];

        if (pBuf != NULL)
        {
            pOrgPtr = (SyncLink_OrgBufferPtr *)pBuf->pSyncLinkOrgBufferPtr;

            if(pOrgPtr!=NULL)
            {
                for (i = 0; i < pOrgPtr->numCh; i++)
                {
                    pOrgBuf = pOrgPtr->pOrgBuf[i];
                    if (pOrgBuf)
                    {
                        freeBufferList.buffers[freeBufferList.numBuf] = pOrgBuf;
                        freeBufferList.numBuf++;
                    }
                }
            }
        }
    }

    System_putLinksEmptyBuffers(pObj->createArgs.inQueParams.prevLinkId,
                               pObj->createArgs.inQueParams.prevLinkQueId,
                               &freeBufferList);
    status = Utils_bufPutEmpty(&pObj->outFrameQue, pBufList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Sync link to get data from
 *    the output queue of DUP link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SyncLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Int32 status;
    SyncLink_Obj *pObj;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    pObj = (SyncLink_Obj *) pTsk->appData;

    pObj->linkStatsInfo->linkStats.getFullBufCount++;
    status = Utils_bufGetFull(&pObj->outFrameQue, pBufList,
                              BSP_OSAL_NO_WAIT);
    return status;
}

/**
 *******************************************************************************
 * \brief Deletes all allocated structures in create phase
 *
 * \param  pObj     [IN]  link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SyncLink_drvDelete(SyncLink_Obj *pObj)
{
    Int32 status, chId;
    SyncLink_ChObj *chObj;

    status = Utils_bufDelete(&pObj->outFrameQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (chId = 0; chId < pObj->numCh; chId++)
    {
        chObj = &pObj->chObj[chId];

        status = Utils_queDelete(&chObj->localQueHandle);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    BspOsal_clockDelete(&pObj->timer);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print Sync link related statistics
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 SyncLink_drvPrintStatistics(SyncLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char  tskName[32];

    snprintf(tskName, sizeof(tskName), "SYNC_LINK_%u", pObj->linkInstId);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, tskName, (Bool)TRUE);

    Utils_printLatency(tskName,
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                        (Bool)TRUE
                       );

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Function to start the link.
 *
 * This function starts the timer, which will be used to send buffers at a
 * fixed interval on output queue
 *
 * \param  pObj           [IN] Null Src link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 SyncLink_start(SyncLink_Obj * pObj)
{
    BspOsal_clockStart(pObj->timer);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Function to stop the link.
 *
 * Post this call, buffers will not be sent to output queue
 *
 * \param  pObj           [IN] Null Src link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 SyncLink_stop(SyncLink_Obj * pObj)
{
    BspOsal_clockStop(pObj->timer);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating Sync link
 *     - Arrival of new data
 *     - Deleting Sync link
 *
 *          DES_ID: DOX_DES_TAG(DES_SYNC_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1518)
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void SyncLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Int32 status = 0;
    UInt32 flushCmds[1];
    SyncLink_Obj *pObj = (SyncLink_Obj*) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                status = SyncLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));
                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    pObj->state = SYSTEM_LINK_STATE_CREATED;
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
                status = SyncLink_drvProcessData(pObj);
            }
            break;

        case SYSTEM_CMD_START:
            if(pObj->state==SYSTEM_LINK_STATE_CREATED)
            {
                status = SyncLink_start(pObj);
                pObj->state = SYSTEM_LINK_STATE_RUNNING;
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_STOP:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                status = SyncLink_stop(pObj);
                pObj->state = SYSTEM_LINK_STATE_CREATED;
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_DELETE:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                status = SyncLink_stop(pObj);
                pObj->state = SYSTEM_LINK_STATE_CREATED;
            }
            if(pObj->state==SYSTEM_LINK_STATE_CREATED)
            {
                status = SyncLink_drvDelete(pObj);
                pObj->state = SYSTEM_LINK_STATE_IDLE;
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                status = SyncLink_drvPrintStatistics(pObj);
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        default:
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

    }
    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for Sync link. This function does the following for each
 *   Sync link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SyncLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 syncId;
    SyncLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for(syncId = 0; syncId < SYNC_LINK_OBJ_MAX; syncId++)
    {
        pObj = &gSyncLink_obj[syncId];

        memset(pObj, 0, sizeof(SyncLink_Obj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_SYNC_0 + syncId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers = &SyncLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &SyncLink_putEmptyBuffers;
        linkObj.getLinkInfo = &SyncLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        pObj->linkInstId = syncId;

        /*
         * Create link task, task remains in IDLE state.
         * DisplayLink_tskMain is called when a message command is received.
         */
        status = SyncLink_tskCreate(syncId);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for DUP link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SyncLink_deInit(void)
{
    UInt32 syncId;

    for (syncId = 0; syncId < SYNC_LINK_OBJ_MAX; syncId++)
    {
        Utils_tskDelete(&gSyncLink_obj[syncId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}


