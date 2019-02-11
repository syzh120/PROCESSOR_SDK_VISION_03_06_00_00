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
 * \file nullSrcLink_tsk.c
 *
 * \brief   This file has the implementation of Null Source Link API
 **
 *         This file implements Null Source link as alternate of capture link.
 *         It currently supports - YUV420sp, YUV422i and bitstream data.
 *         This link will submit preloaded frames to the next links Or for
           testing purpose in conjunction with CCS, circulates data from file.
 *         This file implements the state machine logic for this link.
 *
 * \version 0.0 (Dec 2013) : [VT] First version
 * \version 0.0 (Dec 2015) : [YM] Added file I/O
 *
 ******************************************************************************
 */

/*****************************************************************************
 *  INCLUDE FILES
 *****************************************************************************
 */
#include "nullSrcLink_priv.h"

/*****************************************************************************
 *  DEFINES
 *****************************************************************************
 */
#define NULLSRC_MAX_FRAMES (256000U)
#define NULLSRC_MAX_META_FRAME_SIZE     (2U*1024U*1024U)

/*****************************************************************************
 *  Function declarations
 *****************************************************************************
 */
Int32 NullSrcLink_create(NullSrcLink_Obj * pObj,
                         const NullSrcLink_CreateParams * pPrm);
Int32 NullSrcLink_start(NullSrcLink_Obj * pObj);

Int32 NullSrcLink_processData(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_populateQueue(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_stop(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_drvDelete(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_tskRun(NullSrcLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);
Int32 NullSrcLink_printBufferStatus(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_printLinkStats(const NullSrcLink_Obj * pObj);
Int32 NullSrcLink_allocAndQueueVideoFrames(NullSrcLink_Obj * pObj,
                                           UInt32 channelID);
Int32 NullSrcLink_allocAndQueueBitstreamBufs(NullSrcLink_Obj * pObj,
                                             UInt32 channelID);
Int32 NullSrcLink_fillData(NullSrcLink_Obj * pObj, UInt32 channelId,
                           const System_Buffer *pBuffer);
Int32 NullSrcLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 NullSrcLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList* pBufList);
Int32 NullSrcLink_getInfo(Void * ptr, System_LinkInfo * info);
Void NullSrcLink_timerCallback(UArg arg);
Int32 NullSrcLink_getBufInfo(NullSrcLink_Obj *pObj,
                        NullSrcLink_GetBufInfoParams *pBufInfoPrm);
Int32 NullSrcLink_pause(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_resume(NullSrcLink_Obj * pObj);

/**
 ******************************************************************************
 * \brief Link Stack
 ******************************************************************************
 */
#pragma DATA_ALIGN(gNullSrcLink_tskStack, 32)
#pragma DATA_SECTION(gNullSrcLink_tskStack, ".bss:taskStackSection")
UInt8 gNullSrcLink_tskStack[NULL_SRC_LINK_OBJ_MAX][NULL_SRC_LINK_TSK_STACK_SIZE];

#define NUL_STR_SZ (32U)
/**
 ******************************************************************************
 * \brief Link object, stores all link related information
 ******************************************************************************
 */
NullSrcLink_Obj gNullSrcLink_obj[NULL_SRC_LINK_OBJ_MAX];

/**
 ******************************************************************************
 * \brief This is a callback function, invoked whenever the timer is triggered.
 * This function then sends a 'New data' command to Null Src itself so that
 * data can be sent to the Full buffer.
 *
 * \param  arg  [IN]  Null source link instance handle
 *
 ******************************************************************************
*/
Void NullSrcLink_timerCallback(UArg arg)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic prototype which supports all dataTypes.
     * This typecasting is necessary.
     */
    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) arg;

    if(FALSE == pObj->createArgs.pauseLink)
    {
        Utils_tskSendCmd(&pObj->tsk, SYSTEM_CMD_NEW_DATA, NULL);
        pObj->numPendingCmds++;

        pObj->linkStatsInfo->linkStats.notifyEventCount++;
    }
}

/**
 ******************************************************************************
 * \brief This function is called to fill data from file into System Buffer
 * It is used when file read option is enabled for debugging with CCS.
 *
 * \param  pObj [IN] NullSrcLink_Obj
 * \param  channelId [IN] Channel ID for which Fill data is called
 * \param  pBuffer [IN] System Buffer in which data has to be filled
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 NullSrcLink_fillData(NullSrcLink_Obj * pObj, UInt32 channelId,
                           const System_Buffer *pBuffer)
{
    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * MISRAC_WAIVER:
     * File i/o is a required feature - applies for entire function
     */

    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufSize=0, i;
    UInt32 frameLength = 0U;
    System_VideoDataFormat dataFormat;
    System_VideoFrameBuffer *videoFrame;
    System_BitstreamBuffer *bitstreamBuf;
    UInt8 *bufPtr = NULL;
    UInt32 bytesRead;

    switch(pBuffer->bufType)
    {
        case SYSTEM_BUFFER_TYPE_BITSTREAM:
            bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

            /* Rewind if all frames are done */
            if(pObj->curFrameId >= pObj->numFrames)
            {
                pObj->curFrameId = 0;
                File_seek(pObj->fpDataStream[channelId], 0);
            }

            /* Read length of current frame from Index file */
            frameLength = pObj->frameSizes[pObj->curFrameId];

            /*If buffer is of bitstream type then fillLength contains sizeof
            * valid data inside the buffer.
            */
            UTILS_assert(frameLength < bitstreamBuf->bufSize);
            File_read(pObj->fpDataStream[channelId], bitstreamBuf->bufAddr, frameLength, &(bitstreamBuf->fillLength));
            pObj->curFrameId++;
            break;

        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
            /* MISRA.BITS.NOT_UNSIGNED
             * MISRAC_2004 Rule_12.7
             * MISRAC_WAIVER:
             * RTS library by TI CodeGen Tools uses int instead of uint for macros -
             * Issue cannot be fixed.
             */

            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is hw error situation and should never execute.
            */
            /*If end of file is reached return error*/
            if((Int32)TRUE == File_eof(pObj->fpDataStream[channelId]))
            {
                /* Rewind to the start of the file */
                File_seek(pObj->fpDataStream[channelId], 0);

                /* Notify application when EOF is reached */
                if(NULL != pObj->createArgs.inEofCb)
                {
                    pObj->createArgs.inEofCb(pObj->curFrameId);
                }

                pObj->curFrameId = 0;
            }
            else
            {
                videoFrame = (System_VideoFrameBuffer*)pBuffer->payload;
                dataFormat = (System_VideoDataFormat)
                    System_Link_Ch_Info_Get_Flag_Data_Format(
                                                    videoFrame->chInfo.flags);

                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                {
                    bufSize =
                    (videoFrame->chInfo.pitch[0] * videoFrame->chInfo.height) +
                    (videoFrame->chInfo.pitch[1] * (videoFrame->chInfo.height/2U));
                    UTILS_assert(videoFrame->chInfo.width <= bufSize);

                    /*For YUV420sp data filedata needs to be read into 2 buffers
                    *corresponding to Y plane and UV plane.
                    */
                    bufPtr = videoFrame->bufAddr[0];
                    for(i = 0; i < videoFrame->chInfo.height; i++)
                    {
                        File_read(pObj->fpDataStream[channelId], bufPtr, videoFrame->chInfo.width, &bytesRead);

                        /* MISRA.PTR.ARITH
                         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                         * MISRAC_WAIVER:
                         * Increment is within allocated size of
                         * (videoFrame->chInfo.pitch[0] *
                         *  videoFrame->chInfo.height * 1.5) which is size of a
                         * YUV420 frame.
                         */
                        bufPtr += videoFrame->chInfo.pitch[0];
                    }

                    bufPtr = videoFrame->bufAddr[1];
                    for(i = 0; i < (videoFrame->chInfo.height/2U); i++)
                    {

                        File_read(pObj->fpDataStream[channelId], bufPtr, videoFrame->chInfo.width, &bytesRead);

                        /* MISRA.PTR.ARITH
                         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                         * MISRAC_WAIVER:
                         * Increment is within allocated size of
                         * (videoFrame->chInfo.pitch[0] *
                         *  videoFrame->chInfo.height * 1.5) which is size of a
                         * YUV420 frame.
                         */
                        bufPtr += videoFrame->chInfo.pitch[1];
                    }
                }
                else
                {
                    if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
                    {
                        bufSize =
                            videoFrame->chInfo.pitch[0] *
                            videoFrame->chInfo.height;
                        UTILS_assert((videoFrame->chInfo.width * 2U) <= bufSize);

                        bufPtr = videoFrame->bufAddr[0];
                        for(i = 0; i < videoFrame->chInfo.height; i++)
                        {

                            File_read(pObj->fpDataStream[channelId], bufPtr, videoFrame->chInfo.width * 2U, &bytesRead);
                            /* MISRA.PTR.ARITH
                             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                             * MISRAC_WAIVER:
                             * Increment is within allocated size of
                             * videoFrame->chInfo.pitch[0] *
                             * videoFrame->chInfo.height * 2 which is size of a
                             * YUV422 frame
                             */
                            bufPtr += videoFrame->chInfo.pitch[0];
                        }
                    }
                    else if((dataFormat == SYSTEM_DF_RGB24_888) ||
                            (dataFormat == SYSTEM_DF_BGR24_888))
                    {
                        bufSize =
                            videoFrame->chInfo.pitch[0] *
                            videoFrame->chInfo.height;
                        UTILS_assert((videoFrame->chInfo.width * 3U) <= bufSize);

                        bufPtr = videoFrame->bufAddr[0];
                        for(i = 0; i < videoFrame->chInfo.height; i++)
                        {
                            File_read(pObj->fpDataStream[channelId], bufPtr, videoFrame->chInfo.width * 3U, &bytesRead);
                            /* MISRA.PTR.ARITH
                             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                             * MISRAC_WAIVER:
                             * Increment is within allocated size of
                             * videoFrame->chInfo.pitch[0] *
                             * videoFrame->chInfo.height * 2 which is size of a
                             * YUV422 frame
                             */
                            bufPtr += videoFrame->chInfo.pitch[0];
                        }
                    }
                    else
                    {
                        status += SYSTEM_LINK_STATUS_EFAIL;
                        break; /* Break from switch case */
                    }
                }
                if(SYSTEM_LINK_STATUS_SOK == status)
                {
                    pObj->curFrameId++;
                }
            }
            break;

        default:
            /*return error for unsupported format*/
            status += SYSTEM_LINK_STATUS_EFAIL;
            break; /* Break from switch case */
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Get the buffer and queue information about source link.
 *
 * \param  ptr  [IN] Task Handle
 * \param  info [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 NullSrcLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Callback function to give full buffers to the next link
 *
 * Null Source link sends message to next link about availability of buffers.
 * Next link calls this function to get full buffers from its o/p queue
 *
 * \param  ptr          [IN] Task Handle
 * \param  queId        [IN] queId from which buffers are required.
 * \param  pBufList     [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 NullSrcLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    UInt32 bufId;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(queId < NULL_SRC_LINK_MAX_OUT_QUE);
    UTILS_assert(pBufList != NULL);

    /* NullSrcLink_Obj uses a single queue. queId is still passed as this
    * function is common to all the links. Here we just ignore the queId.
    */
    for (bufId = 0; bufId < NULL_SRC_LINK_MAX_OUT_BUFFERS; bufId++)
    {
        if(bufId < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST)
        {
            /* MISRA.CAST.PTR
             * MISRAC_2004 Rule_11.4
             * MISRAC_WAIVER:
             * This is a generic queue implementation which supports all dataTypes.
             * This typecasting is necessary.
             */
            status += Utils_queGet(&pObj->fullOutBufQue,
                                  (Ptr *)&pBufList->buffers[bufId],
                                  1U,
                                  BSP_OSAL_NO_WAIT);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
        }
        else
        {
            UTILS_assert((Bool) FALSE);
            status += SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    pBufList->numBuf = bufId;

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Callback function link to get empty buffers from next link.
 *
 *
 * \param  ptr          [IN] Task Handle
 * \param  queId        [IN] queId from which buffers are required.
 * \param  pBufList     [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 NullSrcLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList* pBufList)
{
    UInt32 bufId, chId;

    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(queId < NULL_SRC_LINK_MAX_OUT_QUE);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= NULL_SRC_LINK_MAX_OUT_BUFFERS);

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        UTILS_assert(bufId < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

        chId = pBufList->buffers[bufId]->chNum;
        UTILS_assert(chId < NULL_SRC_LINK_MAX_CH);

        UTILS_assert(
            UTILS_ARRAYISVALIDENTRY(
                pBufList->buffers[bufId], pObj->buffers[chId]));
        status += Utils_quePut(&pObj->emptyOutBufQue[chId],
                              pBufList->buffers[bufId],
                              BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    pObj->linkStatsInfo->linkStats.putEmptyBufCount++;

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Process the buffer data in response to a callback.
 *
 * This function gets called in response to a callback. It puts buffers into
 * link output queue and sends message to next link
 *
 * \param  pObj          [IN] Null source link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullSrcLink_processData(NullSrcLink_Obj * pObj)
{
    System_LinkQueInfo *pOutQueInfo;
    System_Buffer *pBuffer;
    UInt32 chId,queId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 numBuf;
    System_LinkStatistics *linkStatsInfo;
    System_LinkChInfo *pChInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstBufferSent==FALSE)
    {
        pObj->isFirstBufferSent = TRUE;

        /*
        * Reset the null src link statistics when first buffer is ready to be
        * sent to next link.
        */
        Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                            pObj->linkInfo.queInfo[0].numCh, 1);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    pOutQueInfo = &pObj->createArgs.outQueInfo;

    numBuf = 0;

    for (chId = 0; chId < pOutQueInfo->numCh; chId++)
    {
        status = Utils_queGet(&pObj->emptyOutBufQue[chId], (Ptr *)&pBuffer, 1,
                              BSP_OSAL_NO_WAIT);

        linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;

        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            /*
            * If for this channel buffer is not available then update stats
            * for dropped buffer and continue for other channels
            */
            linkStatsInfo->linkStats.chStats[chId].inBufDropCount++;
            continue;
        }

        UTILS_assert(pBuffer != NULL);

        if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
        {
            status += SYSTEM_LINK_STATUS_SOK;

            /*
             * If file data has to read into system buffers in Run state
             * then fill pBuffer with valid filedata before sending
             * to next link
             */
            if(pObj->createArgs.channelParams[chId].fileReadMode
                       == NULLSRC_LINK_FILEREAD_RUN_TIME)
            {
                status += NullSrcLink_fillData(pObj, chId, pBuffer);
            }
        }
        else if (pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_CUSTOM)
        {
            /* Read the file data from call back function */
            queId = 0;
            for (chId = 0; chId < pObj->linkInfo.queInfo[queId].numCh; chId++)
            {
                pChInfo = &pObj->linkInfo.queInfo[queId].chInfo[chId];
                if (NULL != pObj->createArgs.appCb)
                {
                    pObj->createArgs.appCb(
                                    pChInfo,
                                    (Void*)pBuffer,
                                    pObj->createArgs.appCbArg);
                }
                else
                {
                    UTILS_assert(NULL != pObj->createArgs.appCb);
                }
            }
        }
        else
        {
            /* Invalid mode, return output buffer back to empty queue */
            status += SYSTEM_LINK_STATUS_EFAIL;
        }

        pBuffer->srcTimestamp = Utils_getCurGlobalTimeInUsec();
        pBuffer->frameId      = pObj->curFrameId;

        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            /* return output buffer back to empty que */
            status += Utils_quePut(
                        &pObj->emptyOutBufQue[chId],
                        pBuffer, BSP_OSAL_NO_WAIT);

            linkStatsInfo->linkStats.chStats[chId].outBufDropCount[0]++;
            continue;
        }

        numBuf++;

        /*
        *Putting the buffer onto the Full Queue
        */
        status += Utils_quePut(&pObj->fullOutBufQue, pBuffer, BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        linkStatsInfo->linkStats.chStats[chId].inBufProcessCount++;
        linkStatsInfo->linkStats.chStats[chId].outBufCount[0]++;
    }

    if(numBuf)
    {
        /*
        *Notify the next link of data on Full Queue
        */
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA, NULL);
    }
    return SYSTEM_LINK_STATUS_SOK;
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
Int32 NullSrcLink_start(NullSrcLink_Obj * pObj)
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
Int32 NullSrcLink_stop(NullSrcLink_Obj * pObj)
{
    BspOsal_clockStop(pObj->timer);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Allocate and Queue Bitstream buffers for a specific channel for null
 * source link
 *
 *  \param pObj         [IN] Null Source link object
 *  \param channelID    [IN] Channel Number for which bitstream buffers need to
 *                          be queued
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */

Int32 NullSrcLink_allocAndQueueBitstreamBufs(NullSrcLink_Obj * pObj,
                                             UInt32 channelID)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId, bufferSize;
    System_LinkChInfo *pChInfo;
    System_Buffer *buffer;
    System_BitstreamCodingType bitstreamFormat;
    System_BitstreamBuffer *bitstreamBuf;
    void *pBaseAddr;

    /*
    * Null Src link has a single output queue
    */
    pChInfo = &pObj->linkInfo.queInfo[0U].chInfo[channelID];

    /*
    * Assumtion is bitstream format would be SYSTEM_BITSTREAM_CODING_TYPE_MJPEG
    * Implementation should work for any bitstream format
    */
    bitstreamFormat = (System_BitstreamCodingType)
        System_Link_Ch_Info_Get_Flag_Bitstream_Format(pChInfo->flags);

    bufferSize = pChInfo->width * pChInfo->height;

    /*Allocating memory for all the buffers on this channel*/
    pBaseAddr = Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            bufferSize * pObj->createArgs.channelParams[channelID].numBuffers,
            VPS_BUFFER_ALIGNMENT);
    UTILS_assert(pBaseAddr != NULL);

    for(bufId = 0U;
        bufId < pObj->createArgs.channelParams[channelID].numBuffers;
        bufId++)
    {
        /*Initialising System_BitstreamBuffer for every buffer on this channel*/
        bitstreamBuf = &pObj->bitstreamBuf[channelID][bufId];
        bitstreamBuf->bufAddr = pBaseAddr;
        bitstreamBuf->bufSize = bufferSize;

        bitstreamBuf->flags = System_Bitstream_Buffer_Flag_Set_Bitstream_Format
                                        (bitstreamBuf->flags,bitstreamFormat);
        /**< For MJPEG every frame is key frame */
        if(bitstreamFormat == SYSTEM_BITSTREAM_CODING_TYPE_MJPEG)
        {
            bitstreamBuf->flags = System_Bitstream_Buffer_Flag_Set_Is_Keyframe
                                        (bitstreamBuf->flags, 1U);
        }

        /**< Dimensions of frame encoded inside the bitstream */
        bitstreamBuf->width = pChInfo->width;
        bitstreamBuf->height = pChInfo->height;
        bitstreamBuf->fillLength = 0U;

        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * MISRAC_WAIVER:
         * Increment is within allocated size of
         * bufferSize * pObj->createArgs.channelParams[channelID].numBuffers
         */
        pBaseAddr = (void *)((char*)pBaseAddr + bufferSize);

        /*
         * Initialize System Buffer using the Bitstream buffer information and
         * associate the System_BitstreamBuffer as its payload.
        */
        buffer = &pObj->buffers[channelID][bufId];
        buffer->bufType = SYSTEM_BUFFER_TYPE_BITSTREAM;
        buffer->chNum = channelID;
        buffer->payloadSize = sizeof(System_BitstreamBuffer);
        buffer->payload = bitstreamBuf;

        if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_CUSTOM)
        {
            status += SYSTEM_LINK_STATUS_SOK;
        }
        else if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
        {
            if(pObj->createArgs.channelParams[channelID].fileReadMode ==
               NULLSRC_LINK_FILEREAD_CREATE_TIME)
            {
               /*
                * If file data has to read in Create state then fill buffer
                * with valid file data before putting it onto empty queue.
                * This logic assumes subsequent links will only consume data
                * and not alter it
                */
                status += NullSrcLink_fillData(pObj, channelID, buffer);

                /* INVARIANT_CONDITION.UNREACH
                * MISRAC_2004_Rule_13.7
                * MISRAC_WAIVER:
                * Code is currently unreachable.
                * This is kept to ensure future updates by the called function.
                */
                if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                {
                    /* For unsupported format or buftype EFAIL is returned,
                     * then assert */
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                else
                {
                    break;
                }
            }
            else
            {
                /*Initialise buffer with dummy data*/
                if(bitstreamBuf->bufAddr != NULL)
                {
                    memset(bitstreamBuf->bufAddr, 0, bufferSize);
                    bitstreamBuf->fillLength = bufferSize;
                }
            }
        }
        else
        {
            status += SYSTEM_LINK_STATUS_EFAIL;
        }

        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            /* Put the buffer on empty queue*/
            status += Utils_quePut(&pObj->emptyOutBufQue[channelID], buffer,
                                  BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Allocate and Queue Video frames for a channel for null source link
 *
 *  \param pObj             [IN] Null Source link object
 *  \param channelID    [IN] Channel Number for which frames need to be queued
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullSrcLink_allocAndQueueVideoFrames(NullSrcLink_Obj * pObj,
                                           UInt32 channelID)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 frameId, frameSize;
    System_LinkChInfo *pChInfo;
    System_Buffer *buffer;
    System_VideoFrameBuffer *videoFrame;
    System_VideoDataFormat dataFormat;
    void *pBaseAddr;
    Bool breakForLoop = (Bool)FALSE;

    /*
    * Null Src link has a single output queue
    */
    pChInfo = &pObj->linkInfo.queInfo[0].chInfo[channelID];

    dataFormat = (System_VideoDataFormat)
        System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

    switch(dataFormat)
    {
        case SYSTEM_DF_YUV420SP_UV:
            /* for Y plane and UV plane*/
            pChInfo->height = VpsUtils_align(pChInfo->height, 2U);
            frameSize = (pChInfo->pitch[0] * pChInfo->height) +
                        (pChInfo->pitch[1] * (pChInfo->height/2U));

            /* align frameSize to minimum required buffer alignment */
            frameSize = VpsUtils_align(frameSize, VPS_BUFFER_ALIGNMENT);

            /*Allocating memory for all the frames (buffers) on this channel*/
            pBaseAddr = Utils_memAlloc(
               UTILS_HEAPID_DDR_CACHED_SR,
               frameSize * pObj->createArgs.channelParams[channelID].numBuffers,
               VPS_BUFFER_ALIGNMENT);
            UTILS_assert(pBaseAddr != NULL);

            for(frameId = 0;
                frameId < pObj->createArgs.channelParams[channelID].numBuffers;
                frameId++)
            {
                videoFrame = &pObj->videoFrames[channelID][frameId];

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Increment is within allocated size of
                 * frameSize * pObj->createArgs.channelParams[chId].numBuffers
                 */
                videoFrame->bufAddr[0] = pBaseAddr;
                videoFrame->bufAddr[1] =
                        (void *)((char*)pBaseAddr +
                                 (pChInfo->pitch[0] * pChInfo->height));
                pBaseAddr = (void *)((char*)pBaseAddr + frameSize);

                /*
                *Initialise Channel Info within video frame data structure with
                *channel's info
                */
                memcpy(&videoFrame->chInfo, pChInfo, sizeof(System_LinkChInfo));

                /* 0 indicates progrssive*/
                videoFrame->flags = System_Video_Frame_Set_Flag_Fid(videoFrame->flags, 0U);

                /*
                *Initialize System Buffer using the Video frame information and
                * associate the System_VideoFrameBuffer as its payload.
                */
                buffer = &pObj->buffers[channelID][frameId];
                buffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                buffer->chNum = channelID;
                buffer->payloadSize = sizeof(System_VideoFrameBuffer);
                buffer->payload = videoFrame;

                if(pObj->createArgs.dataRxMode ==
                        NULLSRC_LINK_DATA_RX_MODE_FILE)
                {
                    if(pObj->createArgs.
                       channelParams[channelID].fileReadMode ==
                       NULLSRC_LINK_FILEREAD_DISABLE)
                    {
                        /*Store dummy data in Y plane*/
                        memset(videoFrame->bufAddr[0],
                               0x10,
                               pChInfo->pitch[0] * pChInfo->height);
                        /*Store black frame data in UV plane*/
                        memset(videoFrame->bufAddr[1],
                               0x80,
                               pChInfo->pitch[1] * (pChInfo->height/2U));
                    }
                    else if(pObj->createArgs.
                            channelParams[channelID].fileReadMode ==
                            NULLSRC_LINK_FILEREAD_CREATE_TIME)
                    {
                        /*
                         * If file data has to read in Create state then fill
                         * buffer with valid filedata before putting it onto
                         * empty queue. This logic assumes subsequent links
                         * will only consume data and not alter it
                         */
                        status += NullSrcLink_fillData(pObj, channelID, buffer);

                        /* INVARIANT_CONDITION.UNREACH
                        * MISRAC_2004_Rule_13.7
                        * MISRAC_WAIVER:
                        * Code is currently unreachable.
                        * This is kept to ensure future updates by the called function.
                        */
                        if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                        {
                            /* For unsupported format or buftype EFAIL is
                             * returned, then assert
                             */
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            breakForLoop = (Bool)TRUE;
                        }
                    }
                    else if(pObj->createArgs.
                            channelParams[channelID].fileReadMode ==
                            NULLSRC_LINK_FILEREAD_RUN_TIME)
                    {
                        status += SYSTEM_LINK_STATUS_SOK;
                    }
                    else
                    {
                        status += SYSTEM_LINK_STATUS_EFAIL;
                        breakForLoop = (Bool)TRUE;
                    }
                }
                else if(pObj->createArgs.dataRxMode ==
                        NULLSRC_LINK_DATA_RX_MODE_CUSTOM)
                {
                    status += SYSTEM_LINK_STATUS_SOK;
                }
                else
                {
                    status += SYSTEM_LINK_STATUS_EFAIL;
                    breakForLoop = (Bool)TRUE;
                }

                if(breakForLoop)
                {
                    break;
                }

                /* Put the frame on empty queue*/
                status += Utils_quePut(&pObj->emptyOutBufQue[channelID],
                                      buffer,
                                      BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            break;

        case SYSTEM_DF_BAYER_RAW:
        case SYSTEM_DF_BAYER_GRBG:
        case SYSTEM_DF_BAYER_RGGB:
        case SYSTEM_DF_BAYER_BGGR:
        case SYSTEM_DF_BAYER_GBRG:
        case SYSTEM_DF_YUV422I_YUYV:
            /* for a single plane for Y, U and V*/
            pChInfo->height = VpsUtils_align(pChInfo->height, 2U);
            frameSize = pChInfo->pitch[0] * pChInfo->height;

            /* align frameSize to minimum required buffer alignment */
            frameSize = VpsUtils_align(frameSize, VPS_BUFFER_ALIGNMENT);

            /*Allocating memory for all the frames (buffers) on this channel*/
            pBaseAddr = Utils_memAlloc(
               UTILS_HEAPID_DDR_CACHED_SR,
               frameSize * pObj->createArgs.channelParams[channelID].numBuffers,
               VPS_BUFFER_ALIGNMENT);
            UTILS_assert(pBaseAddr != NULL);

            for(frameId = 0;
                frameId < pObj->createArgs.channelParams[channelID].numBuffers;
                frameId++)
            {
                videoFrame = &pObj->videoFrames[channelID][frameId];

                videoFrame->bufAddr[0] = pBaseAddr;
                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Increment is within allocated size of
                 * frameSize * pObj->createArgs.channelParams[chId].numBuffers
                 */
                pBaseAddr = (void *)((char*)pBaseAddr + frameSize);

                memcpy(&videoFrame->chInfo, pChInfo,sizeof(System_LinkChInfo));

                /* 0 indicates progressive*/
                videoFrame->flags = System_Video_Frame_Set_Flag_Fid(videoFrame->flags, 0U);

                /*
                * Initialize System Buffer using the Video frame information
                * and associate the System_VideoFrameBuffer as its payload.
                */
                buffer = &pObj->buffers[channelID][frameId];
                buffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                buffer->chNum = channelID;
                buffer->payloadSize = sizeof(System_VideoFrameBuffer);
                buffer->payload = videoFrame;

                if(pObj->createArgs.dataRxMode ==
                        NULLSRC_LINK_DATA_RX_MODE_FILE)
                {
                    if(pObj->createArgs.channelParams[channelID].fileReadMode
                                == NULLSRC_LINK_FILEREAD_DISABLE)
                    {
                        /* Fill frame with dummy data, displays pink on LCD*/
                        memset(videoFrame->bufAddr[0], 0xD0,
                               pChInfo->pitch[0] * pChInfo->height);
                    }
                    else if(pObj->createArgs.channelParams[channelID].fileReadMode
                                == NULLSRC_LINK_FILEREAD_CREATE_TIME)
                    {
                        /*
                        * If file data has to read in Create state then fill buffer
                        * with valid filedata before putting it onto empty queue.
                        * This logic assumes subsequent links will only consume data
                        * and not alter it
                        */
                        status += NullSrcLink_fillData(pObj, channelID, buffer);

                        /* INVARIANT_CONDITION.UNREACH
                        * MISRAC_2004_Rule_13.7
                        * MISRAC_WAIVER:
                        * Code is currently unreachable.
                        * This is kept to ensure future updates by the called function.
                        */
                        if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                        {
                            /* For unsupported format or buftype EFAIL
                             * is returned, then assert
                             */
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        status += SYSTEM_LINK_STATUS_EFAIL;
                    }
                }
                else if(pObj->createArgs.dataRxMode ==
                        NULLSRC_LINK_DATA_RX_MODE_CUSTOM)
                {
                    status += SYSTEM_LINK_STATUS_SOK;
                }
                else
                {
                    status += SYSTEM_LINK_STATUS_EFAIL;
                }
                /* Put the frame on empty queue*/
                status += Utils_quePut(&pObj->emptyOutBufQue[channelID], buffer,
                              BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            break;

        case SYSTEM_DF_RGB24_888:
        case SYSTEM_DF_BGR24_888:
            /* for a single plane for Y, U and V*/
            pChInfo->height = VpsUtils_align(pChInfo->height, 2U);
            frameSize = pChInfo->pitch[0] * pChInfo->height;

            /* align frameSize to minimum required buffer alignment */
            frameSize = VpsUtils_align(frameSize, VPS_BUFFER_ALIGNMENT);

            /*Allocating memory for all the frames (buffers) on this channel*/
            pBaseAddr = Utils_memAlloc(
               UTILS_HEAPID_DDR_CACHED_SR,
               frameSize * pObj->createArgs.channelParams[channelID].numBuffers,
               VPS_BUFFER_ALIGNMENT);
            UTILS_assert(pBaseAddr != NULL);

            for(frameId = 0;
                frameId < pObj->createArgs.channelParams[channelID].numBuffers;
                frameId++)
            {
                videoFrame = &pObj->videoFrames[channelID][frameId];

                videoFrame->bufAddr[0] = pBaseAddr;
                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Increment is within allocated size of
                 * frameSize * pObj->createArgs.channelParams[chId].numBuffers
                 */
                pBaseAddr = (void *)((char*)pBaseAddr + frameSize);

                memcpy(&videoFrame->chInfo, pChInfo,sizeof(System_LinkChInfo));

                /* 0 indicates progressive*/
                videoFrame->flags = System_Video_Frame_Set_Flag_Fid(videoFrame->flags, 0U);

                /*
                * Initialize System Buffer using the Video frame information
                * and associate the System_VideoFrameBuffer as its payload.
                */
                buffer = &pObj->buffers[channelID][frameId];
                buffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                buffer->chNum = channelID;
                buffer->payloadSize = sizeof(System_VideoFrameBuffer);
                buffer->payload = videoFrame;

                if(pObj->createArgs.dataRxMode ==
                        NULLSRC_LINK_DATA_RX_MODE_FILE)
                {
                    if(pObj->createArgs.channelParams[channelID].fileReadMode
                                == NULLSRC_LINK_FILEREAD_DISABLE)
                    {
                        /* Fill frame with dummy data, displays pink on LCD*/
                        memset(videoFrame->bufAddr[0], 0xD0,
                               pChInfo->pitch[0] * pChInfo->height);
                    }
                    else if(pObj->createArgs.channelParams[channelID].fileReadMode
                                == NULLSRC_LINK_FILEREAD_CREATE_TIME)
                    {
                        /*
                        * If file data has to read in Create state then fill buffer
                        * with valid filedata before putting it onto empty queue.
                        * This logic assumes subsequent links will only consume data
                        * and not alter it
                        */
                        status += NullSrcLink_fillData(pObj, channelID, buffer);

                        /* INVARIANT_CONDITION.UNREACH
                        * MISRAC_2004_Rule_13.7
                        * MISRAC_WAIVER:
                        * Code is currently unreachable.
                        * This is kept to ensure future updates by the called function.
                        */
                        if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                        {
                            /* For unsupported format or buftype EFAIL
                             * is returned, then assert
                             */
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        /* Fill frame with dummy data, displays pink on LCD*/
                        memset(videoFrame->bufAddr[0], 0xD0,
                               pChInfo->pitch[0] * pChInfo->height);
                    }
                }
                else if(pObj->createArgs.dataRxMode ==
                        NULLSRC_LINK_DATA_RX_MODE_CUSTOM)
                {
                    status += SYSTEM_LINK_STATUS_SOK;
                }
                else
                {
                    status += SYSTEM_LINK_STATUS_EFAIL;
                }
                /* Put the frame on empty queue*/
                status += Utils_quePut(&pObj->emptyOutBufQue[channelID], buffer,
                              BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            break;

        default:
            status += SYSTEM_LINK_STATUS_EFAIL;
            break;
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Polulates the queue with buffers for null source link
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullSrcLink_populateQueue(NullSrcLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType;

    /*
    * All buffers are contiguous Initializing them here.
    */
    memset(&pObj->buffers, 0,
                sizeof(System_Buffer)*NULL_SRC_LINK_MAX_OUT_BUFFERS);
    memset(&pObj->videoFrames, 0,
                sizeof(System_VideoFrameBuffer)*NULL_SRC_LINK_MAX_OUT_BUFFERS);
    memset(&pObj->bitstreamBuf, 0,
                sizeof(System_BitstreamBuffer)*NULL_SRC_LINK_MAX_OUT_BUFFERS);

    /*
    * Null Src link has a single output queue. Hence index 0 is used for queInfo
    */
    for (chId = 0; chId < pObj->linkInfo.queInfo[0].numCh; chId++)
    {
        pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];
        bufferType = (System_BufferType)
            System_Link_Ch_Info_Get_Flag_Buf_Type(pChInfo->flags);
        /*
        *Buffer Type indicates whether the channel contains compreseed bitstream
        *or video frame (YUV) data.
        */
        switch(bufferType)
        {
            case SYSTEM_BUFFER_TYPE_BITSTREAM:
                status += NullSrcLink_allocAndQueueBitstreamBufs(pObj, chId);
                break;
            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                status += NullSrcLink_allocAndQueueVideoFrames(pObj, chId);
                break;
            default:
                UTILS_assert(
                    (bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM) ||
                    (bufferType == SYSTEM_BUFFER_TYPE_METADATA) ||
                    (bufferType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME));
                break;
        }
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Null Src API for link. Link gets created using this function.
 *
 * Sets up link data structure, allocates and queue buffers. Makes link ready
 * for operation.
 *
 * \param  pObj     [IN] Null Src link global handle
 * \param  pPrm    [IN] Null Src link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullSrcLink_create(NullSrcLink_Obj * pObj,
                         const NullSrcLink_CreateParams * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;
    UInt32 bytesRead;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType;

    /*
    * Validating the create params
    * TODO: Extend to validate width, height and pitch params also
    */
    UTILS_assert(pPrm->outQueInfo.numCh <= NULL_SRC_LINK_MAX_CH);
    UTILS_assert(pPrm->timerPeriodMilliSecs != 0);

    /*
    *Copying Create arguments into Link object from the parametes passed by app
    */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    status += Utils_queCreate(&pObj->fullOutBufQue,
         NULL_SRC_LINK_MAX_OUT_BUFFERS,
         pObj->pBufferOnFullQ,
         UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Null Src link has a single queue.
     * Initializing it.
     */
    pObj->linkInfo.numQue = 1;
    pObj->linkInfo.queInfo[0].numCh = pPrm->outQueInfo.numCh;
    for (chId = 0; chId < pPrm->outQueInfo.numCh; chId++)
    {
        memcpy(&pObj->linkInfo.queInfo[0].chInfo[chId],
               &pPrm->outQueInfo.chInfo[chId],
               sizeof(System_LinkChInfo));

        if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
        {
            if(pPrm->channelParams[chId].fileReadMode!=
                        NULLSRC_LINK_FILEREAD_DISABLE)
            {
                pChInfo = &pObj->linkInfo.queInfo[0].chInfo[chId];
                bufferType = (System_BufferType)\
                        System_Link_Ch_Info_Get_Flag_Buf_Type(pChInfo->flags);

                /* MISRA.STDLIB.STDIO
                 * MISRAC_2004 Rule_20.9
                 * MISRAC_WAIVER:
                 * File i/o is a required feature.
                 */
                UTILS_assert(
                    (pPrm->channelParams[chId].nameDataFile[0]  != (char)'\0'));

                pObj->fpDataStream[chId] =
                        File_open((Char *)pPrm->channelParams[chId].nameDataFile, "r");
                UTILS_assert(pObj->fpDataStream[chId] != SYSTEM_LINK_STATUS_EFAIL);

                pObj->curFrameId = 0;

                if(SYSTEM_BUFFER_TYPE_BITSTREAM == bufferType)
                {
                    /*
                     *  Bit stream data file is accompanied by index file having
                     *  the sizes of the bitstream chunks.
                     */
                    UTILS_assert(
                        (pPrm->channelParams[chId].nameIndexFile[0] != (char)'\0'));

                    /* Index file is assumed to be binary conisting readable of frame sizes
                     *
                     * This single command can be used to convert text file of sizes to binary readable in Little Endean
                     * $>cat test_size.txt | perl -n -e 'printf("%08x\n",$_)' |
                     *   sed 's/\(..\)\(..\)\(..\)\(..\)/0x\4\n0x\3\n0x\2\n0x\1/' |
                     *   xxd -r -p > test.bin && du -b test.bin
                     *
                     * Rename test.bin as inHeader and use it as index file.
                     */
                    pObj->frameSizes = Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            (sizeof(UInt32) * NULLSRC_MAX_FRAMES),
                            VPS_BUFFER_ALIGNMENT);
                    UTILS_assert(pObj->frameSizes != NULL);

                    status += Utils_fileReadFile((Char*)pPrm->channelParams[chId].nameIndexFile,
                                                (UInt8 *)pObj->frameSizes,
                                                (sizeof(UInt32) * NULLSRC_MAX_FRAMES),
                                                &bytesRead);
                    UTILS_assert(status == 0);

                    pObj->numFrames = bytesRead / sizeof(UInt32);
                }
           }
        }
        else if (pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_CUSTOM)
        {
            status += SYSTEM_LINK_STATUS_SOK;
        }
        else
        {
            status += SYSTEM_LINK_STATUS_EFAIL;
        }
        UTILS_assert(pPrm->channelParams[chId].numBuffers<=
                        NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH);

        status += Utils_queCreate(&pObj->emptyOutBufQue[chId],
             NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH,
             pObj->pBufferOnEmptyQ[chId],
             UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*Populate the queue with buffers*/
    status += NullSrcLink_populateQueue(pObj);

    /*This flag is set when first buffer is sent to next link.
    * Resetting it at create time.
    */
    pObj->isFirstBufferSent = (Bool)FALSE;

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "NULL_SRC");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    /* MISRA.CAST.FUNC_PTR
     * MISRAC_2004 Rule_11.1
     * MISRAC_WAIVER:
     * Valid type-casting from function pointer to function pointer.
     */
    /* Creating timer and setting timer callback function*/
    pObj->timer = BspOsal_clockCreate(
                        (BspOsal_ClockFuncPtr) &NullSrcLink_timerCallback,
                        pPrm->timerPeriodMilliSecs,
                        (Bool)FALSE,
                        pObj);
    UTILS_assert(pObj->timer != NULL);

    pObj->createArgs.pauseLink = FALSE;

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Delete null source link
 *
 *
 * \param  pObj         [IN] Null source link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullSrcLink_drvDelete(NullSrcLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, size;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType = SYSTEM_BUFFER_TYPE_FORCE32BITS;
    System_VideoDataFormat dataFormat;

    status += Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Null Src - there is a single queue */
    queId = 0;
    for (chId = 0; chId < pObj->linkInfo.queInfo[queId].numCh; chId++)
    {
        pChInfo = &pObj->linkInfo.queInfo[queId].chInfo[chId];
        bufferType = (System_BufferType)
            System_Link_Ch_Info_Get_Flag_Buf_Type(pChInfo->flags);
        /*
        *Buffer Type indicates whether the channel contains compreseed bitstream
        *or video frame (YUV) data.
        */
        if(bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM)
        {
            /* We had assumed WxH while allocating */
            size = pChInfo->width * pChInfo->height;

            /* Free memory for all buffers on this channel*/
            Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->bitstreamBuf[chId][0].bufAddr,
                        size * pObj->createArgs.channelParams[chId].numBuffers);
        }
        else if(bufferType == SYSTEM_BUFFER_TYPE_METADATA)
        {
            /* We had assumed WxH while allocating */
            size = NULLSRC_MAX_META_FRAME_SIZE;

            /* Free memory for all buffers on this channel*/
            Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->metaDataBuf[chId][0].bufAddr[0],
                        size * pObj->createArgs.channelParams[chId].numBuffers);
        }
        else if (bufferType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
        {
            dataFormat = (System_VideoDataFormat)
                        System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);
            switch(dataFormat)
            {
                case SYSTEM_DF_YUV420SP_UV:
                    /* for Y plane and UV plane*/
                    size = (pChInfo->pitch[0] * pChInfo->height) +
                           (pChInfo->pitch[1] * (pChInfo->height/2U));
                    /* align size to minimum required buffer alignment */
                    size = VpsUtils_align(size, VPS_BUFFER_ALIGNMENT);
                    /* Free memory for all buffers on this channel*/
                    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->videoFrames[chId][0].bufAddr[0],
                        size * pObj->createArgs.channelParams[chId].numBuffers);
                    break;

                case SYSTEM_DF_BAYER_RAW:
                case SYSTEM_DF_BAYER_GRBG:
                case SYSTEM_DF_BAYER_RGGB:
                case SYSTEM_DF_BAYER_BGGR:
                case SYSTEM_DF_BAYER_GBRG:
                case SYSTEM_DF_YUV422I_YUYV:
                    /* for a single plane for Y, U and V*/
                    size = pChInfo->pitch[0] * pChInfo->height;
                    /* align size to minimum required buffer alignment */
                    size = VpsUtils_align(size, VPS_BUFFER_ALIGNMENT);
                    /* Free memory for all buffers on this channel*/
                    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->videoFrames[chId][0].bufAddr[0],
                        size * pObj->createArgs.channelParams[chId].numBuffers);
                    break;

                case SYSTEM_DF_RGB24_888:
                case SYSTEM_DF_BGR24_888:
                    /* for a single plane for Y, U and V*/
                    size = pChInfo->pitch[0] * pChInfo->height;
                    /* align size to minimum required buffer alignment */
                    size = VpsUtils_align(size, VPS_BUFFER_ALIGNMENT);
                    /* Free memory for all buffers on this channel*/
                    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->videoFrames[chId][0].bufAddr[0],
                        size * pObj->createArgs.channelParams[chId].numBuffers);
                    break;

                default:
                    status += SYSTEM_LINK_STATUS_EFAIL;
                    break;
            }

        }
        else
        {
            UTILS_assert((bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM) ||
                         (bufferType == SYSTEM_BUFFER_TYPE_METADATA) ||
                         (bufferType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME));
        }

        status += Utils_queDelete(&pObj->emptyOutBufQue[chId]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    status += Utils_queDelete(&pObj->fullOutBufQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    BspOsal_clockDelete(&pObj->timer);

    if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
    {
        for (chId = 0; chId < pObj->linkInfo.queInfo[queId].numCh; chId++)
        {
            if(pObj->createArgs.channelParams[chId].fileReadMode != \
                                                NULLSRC_LINK_FILEREAD_DISABLE)
            {
                /* MISRA.STDLIB.STDIO
                 * MISRAC_2004 Rule_20.9
                 * MISRAC_WAIVER:
                 * File i/o is a required feature.
                 */
                if(pObj->fpDataStream[chId])
                {
                    File_close(pObj->fpDataStream[chId]);
                }

                if(bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM)
                {
                    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->frameSizes,
                        (sizeof(UInt32) * NULLSRC_MAX_FRAMES));
                }
            }
        }
    }
    else
    {
        status += SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Get the Buffer Information
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_getBufInfo(NullSrcLink_Obj *pObj,
                        NullSrcLink_GetBufInfoParams *pBufInfoPrm)
{
    UInt32 bufCnt;

    pBufInfoPrm->numBuf = \
        pObj->createArgs.channelParams[pBufInfoPrm->chId].numBuffers;

    for (bufCnt = 0;bufCnt < pBufInfoPrm->numBuf;bufCnt++)
    {
        memcpy(&pBufInfoPrm->buffer[bufCnt],
            &pObj->buffers[pBufInfoPrm->chId][bufCnt],
            sizeof (System_Buffer));
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Pause Null Source
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_pause(NullSrcLink_Obj *pObj)
{
    pObj->createArgs.pauseLink = TRUE;
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Resume Null Source
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_resume(NullSrcLink_Obj *pObj)
{
    pObj->createArgs.pauseLink = FALSE;
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_printLinkStats(const NullSrcLink_Obj * pObj)
{
    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
                              "NULL_SRC",
                              (Bool)TRUE);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print null source link buffer statistics
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_printBufferStatus(NullSrcLink_Obj * pObj)
{
    System_LinkQueInfo *pOutQueInfo;
    UInt32 chId;

    pOutQueInfo = &pObj->createArgs.outQueInfo;

    Vps_printf(" [%s] Buffer Q Status,\n", "NULL SOURCE");

    for (chId = 0; chId < pOutQueInfo->numCh; chId++)
    {
        Vps_printf(" Empty Q :"
                   " Elements in Q = %3d, Write Idx = %3d, Read Idx = %3d\n",
                    pObj->emptyOutBufQue[chId].count,
                    pObj->emptyOutBufQue[chId].curWr,
                    pObj->emptyOutBufQue[chId].curRd);
    }

    Vps_printf(" Full  Q :"
               " Elements in Q = %3d, Write Idx = %3d, Read Idx = %3d\n",
                pObj->fullOutBufQue.count,
                pObj->fullOutBufQue.curWr,
                pObj->fullOutBufQue.curRd);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief This function is the implementation of Run state of link.
 *
 * In this state link waits for command from application or next link.
 * Basically all are control commands except the new_data command where link
 * puts data in
 * output queue. After that it sends command to next link.
 *
 * \param  pObj     [IN] Null Src link object
 * \param  pTsk     [IN] Null Src link Task handle
 * \param  pMsg     [IN] Message for the link. Contains command and args.
 * \param  done     [IN] Flag to exit idle state.
 * \param  ackMsg   [IN] Flag to decide whether to send ack message or not
 *                          to caller
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullSrcLink_tskRun(NullSrcLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone, runAckMsg;
    Utils_MsgHndl *pRunMsg;
    UInt32 cmd, oldIntState, flushCmds[1];

    /* READY loop done and ackMsg status */
    *done = (Bool)FALSE;
    *ackMsg = (Bool)FALSE;
    *pMsg = NULL;

    /* RUN loop done and ackMsg status */
    runDone = (Bool)FALSE;
    runAckMsg = (Bool)FALSE;

    /* RUN state loop */
    while (!runDone)
    {
        /* wait for message */
        status += Utils_tskRecvMsg(pTsk, &pRunMsg, BSP_OSAL_WAIT_FOREVER);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }

        /* extract message command from message */
        cmd = Utils_msgGetCmd(pRunMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                flushCmds[0] = SYSTEM_CMD_NEW_DATA;
                Utils_tskFlushMsg(pTsk, flushCmds, 1U);

                oldIntState = Hwi_disable();
                if(pObj->numPendingCmds)
                {
                    pObj->numPendingCmds--;
                }
                Hwi_restore(oldIntState);


                /* new data needs to be processed*/
                status += NullSrcLink_processData(pObj);
                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    /* in case of error exit RUN loop */
                    runDone = (Bool)TRUE;

                    /* since message is already ACK'ed or free'ed do not ACK
                                    * or free it again */
                    runAckMsg = (Bool)FALSE;
                }
                break;

            case SYSTEM_CMD_STOP:
                /* stop RUN loop and goto READY state */
                runDone = (Bool)TRUE;

                /* ACK message after actually stopping outside the RUN loop */
                runAckMsg = (Bool)TRUE;
                break;

            case SYSTEM_CMD_DELETE:

                /* stop RUN loop and goto IDLE state */

                /* exit RUN loop */
                runDone = (Bool)TRUE;

                /* exit READY loop */
                *done = (Bool)TRUE;

                /* ACK message after exiting READY loop */
                *ackMsg = (Bool)TRUE;

                /* Pass the received message to the READY loop */
                *pMsg = pRunMsg;

                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                /* print the null source link statistics*/
                NullSrcLink_printLinkStats(pObj);
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                /* print the null source link output buffer queue status*/
                NullSrcLink_printBufferStatus(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NULL_SRC_LINK_CMD_PAUSE:
                NullSrcLink_pause(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NULL_SRC_LINK_CMD_RESUME:
                NullSrcLink_resume(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            default:

                /* invalid command for this state ACK it, continue RUN loop */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop the link */
    NullSrcLink_stop(pObj);

    /* ACK message if not ACKed earlier */
    if (runAckMsg)
    {
        Utils_tskAckOrFreeMsg(pRunMsg, status);
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief This function is the implementation of Idle state.
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 ******************************************************************************
 */
Void NullSrcLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl *pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done = (Bool)FALSE;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    NullSrcLink_Obj *pObj;

    /* IDLE state */

    pObj = (NullSrcLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
        * with error status */
        Utils_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EUNSUPPORTED_CMD);
        status += SYSTEM_LINK_STATUS_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the link */
        status += NullSrcLink_create(pObj, Utils_msgGetPrm(pMsg));

        /* ACK based on create status */
        Utils_tskAckOrFreeMsg(pMsg, status);

        /* create success, entering READY state */
        done = (Bool)FALSE;
        ackMsg = (Bool)FALSE;
    }

    /* READY state loop */
    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        while (!done)
        {
            /* wait for message */
            status += Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }

            /* extract message command from message */
            cmd = Utils_msgGetCmd(pMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_START:
                    /* Start mull source driver */
                    status += NullSrcLink_start(pObj);

                    /* ACK based on create status */
                    Utils_tskAckOrFreeMsg(pMsg, status);

                    /* if start status is error then remain in READY state */
                    if (status == SYSTEM_LINK_STATUS_SOK)
                    {
                        /* start success, entering RUN state */
                        status =
                            NullSrcLink_tskRun(
                                pObj, pTsk, &pMsg, &done, &ackMsg);
                    }

                    break;
                case SYSTEM_CMD_DELETE:
                    /* exit READY state */
                    done = (Bool)TRUE;
                    ackMsg = (Bool)TRUE;
                    break;
                case NULL_SRC_LINK_CMD_GET_BUF_INFO:
                    status += NullSrcLink_getBufInfo(pObj,\
                        (NullSrcLink_GetBufInfoParams*)Utils_msgGetPrm(pMsg));
                    /* ACK based on create status */
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;

                default:
                    /* invalid command for this state ACK it and continue READY
                     * loop */
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        /* exiting READY state, delete link */
        NullSrcLink_drvDelete(pObj);

        /* ACK message if not previously ACK'ed */
        if ((pMsg != NULL) && ((Bool)TRUE == ackMsg))
        {
            Utils_tskAckOrFreeMsg(pMsg, status);
        }
    }

    /* entering IDLE state */
    return;
}

/**
 ******************************************************************************
 *
 * \brief Init function for null source link. BIOS task for link gets
 * created/registered here.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 NullSrcLink_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkObj linkObj;
    UInt32 nullSrcId;
    NullSrcLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for (nullSrcId = 0U; nullSrcId < NULL_SRC_LINK_OBJ_MAX; nullSrcId++)
    {
        /* register link with system API */

        pObj = &gNullSrcLink_obj[nullSrcId];

        memset(pObj, 0, sizeof(NullSrcLink_Obj));

        pObj->tskId =
            SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_NULL_SRC_0) + nullSrcId;

        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &NullSrcLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &NullSrcLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &NullSrcLink_getInfo;

        System_registerLink(pObj->tskId, &linkObj);

        snprintf(pObj->name, NUL_STR_SZ, "NULL_SRC%u   ", nullSrcId);

        /* Create link task, task remains in IDLE state
       * NullSrcLink_tskMain is called when a message command is received
       */
        status += Utils_tskCreate(&pObj->tsk,
                                 NullSrcLink_tskMain,
                                 NULL_SRC_LINK_TSK_PRI,
                                 gNullSrcLink_tskStack[nullSrcId],
                                 NULL_SRC_LINK_TSK_STACK_SIZE,
                                 pObj, pObj->name, UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief De-Init function for null source link. BIOS task for null src link
 * gets deleted in here.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 NullSrcLink_deInit(void)
{
    UInt32 nullSrcId;

    for (nullSrcId = 0U; nullSrcId < NULL_SRC_LINK_OBJ_MAX; nullSrcId++)
    {
        Utils_tskDelete(&gNullSrcLink_obj[nullSrcId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
