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
 * \brief  This file has the implementation of Null Src Link
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Dec 2015) : [BJ] First version ported to Linux
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "nullSrcLink_priv.h"


/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
NullSrcLink_Obj gNullSrcLink_obj[NULL_SRC_LINK_OBJ_MAX];


Int32 NullSrcLink_create(NullSrcLink_Obj * pObj,
                         const NullSrcLink_CreateParams * pPrm);
Int32 NullSrcLink_start(NullSrcLink_Obj * pObj);

Int32 NullSrcLink_processData(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_populateQueue(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_stop(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_delete(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_tskRun(NullSrcLink_Obj * pObj, OSA_TskHndl * pTsk,
                         OSA_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);
Int32 NullSrcLink_printBufferStatus(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_printLinkStats(NullSrcLink_Obj * pObj);
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
Void NullSrcLink_timerCallback(union sigval arg);

int NullSrcLink_tskMain(struct OSA_TskHndl *pTsk, OSA_MsgHndl *pMsg, Uint32 curState );
Int32 NullSrcLink_pause(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_resume(NullSrcLink_Obj * pObj);
Int32 NullSrcLink_restartFiles(
            NullSrcLink_Obj *pObj,
            NullSrcLink_RestartFileParams *pPrm);
Int32 NullSrcLink_getBufInfo(NullSrcLink_Obj *pObj,
                        NullSrcLink_GetBufInfoParams *pBufInfoPrm);

#define VpsUtils_floor(val, align) (((val) / (align)) * (align))
#define VpsUtils_align(val, align) VpsUtils_floor(((val) + ((align) - 1U)), (align))

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
void NullSrcLink_timerCallback(union sigval arg)
{
    /* Only one Null Src Link instance is supported on Linux */
    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) arg.sival_ptr;

    if(FALSE == pObj->createArgs.pauseLink)
    {
        System_sendLinkCmd(pObj->tskId, SYSTEM_CMD_NEW_DATA, NULL);
        pObj->numPendingCmds++;

        pObj->linkStats.notifyEventCount++;
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
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 frameLength = 0, bufSize=0, i;
    System_VideoDataFormat dataFormat;
    System_VideoFrameBuffer *videoFrame;
    System_BitstreamBuffer *bitstreamBuf;
    UInt8 *bufPtr = NULL;

    /*If end of file is reached return error*/
    if(((Int32)TRUE == feof(pObj->fpDataStream[channelId])) ||
       ((Int32)TRUE == feof(pObj->fpIndexFile[channelId])))
    {
        if(pObj->createArgs.channelParams[channelId].fileReadMode
            == NULLSRC_LINK_FILEREAD_RUN_TIME)
        {
            rewind(pObj->fpDataStream[channelId]);
            rewind(pObj->fpIndexFile[channelId]);
        }
        {
            status = SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS;
        }
    }

    if(SYSTEM_LINK_STATUS_SOK == status)
    {
        /*Read length of current frame from Index file*/
        fscanf(pObj->fpIndexFile[channelId], "%u", &frameLength);

        if (0 == frameLength)
        {
            rewind(pObj->fpIndexFile[channelId]);

            /*Read length of current frame from Index file*/
            fscanf(pObj->fpIndexFile[channelId], "%u", &frameLength);

            OSA_assert(0 != frameLength);
        }

        switch(pBuffer->bufType)
        {
            case SYSTEM_BUFFER_TYPE_BITSTREAM:
                bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

                /*If buffer is of bitstream type then fillLength contains sizeof
                * valid data inside the buffer.
                */
                OSA_assert(frameLength < bitstreamBuf->bufSize);

                bitstreamBuf->fillLength = fread(bitstreamBuf->bufAddr, 1U,
                                        frameLength, pObj->fpDataStream[channelId]);

                if (0 == bitstreamBuf->fillLength)
                {
                    rewind(pObj->fpDataStream[channelId]);

                    bitstreamBuf->fillLength = fread(bitstreamBuf->bufAddr, 1U,
                                            frameLength, pObj->fpDataStream[channelId]);
                    OSA_assert(0 != bitstreamBuf->fillLength);
                }
                OSA_memCacheWb(
                    (UInt32)bitstreamBuf->bufAddr,
                    (UInt32)bitstreamBuf->bufAddr + frameLength);
                break;

            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                videoFrame = (System_VideoFrameBuffer*)pBuffer->payload;
                dataFormat = (System_VideoDataFormat)
                 System_Link_Ch_Info_Get_Flag_Data_Format(videoFrame->chInfo.flags);

                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                {
                    bufSize =
                    (videoFrame->chInfo.pitch[0] * videoFrame->chInfo.height) +
                    (videoFrame->chInfo.pitch[1] * (videoFrame->chInfo.height/2U));
                    OSA_assert(frameLength <= bufSize);

                    /*For YUV420sp data filedata needs to be read into 2 buffers
                    *corresponding to Y plane and UV plane.
                    */
                    bufPtr = videoFrame->bufAddr[0];
                    for(i = 0; i < videoFrame->chInfo.height; i++)
                    {
                        fread(bufPtr, 1U, videoFrame->chInfo.width,
                             pObj->fpDataStream[channelId]);

                        OSA_memCacheWb(
                            (UInt32)bufPtr,
                            (UInt32)bufPtr +
                            videoFrame->chInfo.width);

                        bufPtr += videoFrame->chInfo.pitch[0];
                    }

                    bufPtr = videoFrame->bufAddr[1];
                    for(i = 0; i < (videoFrame->chInfo.height/2U); i++)
                    {
                        fread(bufPtr,
                              1U,
                              videoFrame->chInfo.width,
                              pObj->fpDataStream[channelId]);

                        OSA_memCacheWb(
                            (UInt32)bufPtr,
                            (UInt32)bufPtr +
                            videoFrame->chInfo.width);
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
                        OSA_assert(frameLength <= bufSize);

                        bufPtr = videoFrame->bufAddr[0];
                        for(i = 0; i < videoFrame->chInfo.height; i++)
                        {
                            fread(bufPtr,
                                  1U,
                                  videoFrame->chInfo.width * 2U,
                                  pObj->fpDataStream[channelId]);
                            OSA_memCacheWb(
                                (UInt32)bufPtr,
                                (UInt32)bufPtr +
                                videoFrame->chInfo.width * 2U);
                            bufPtr += videoFrame->chInfo.pitch[0];
                        }
                    }
                    else
                    {
                        status = SYSTEM_LINK_STATUS_EFAIL;
                        break; /* Break from switch case */
                    }
                }
                break;

            default:
                /*return error for unsupported format*/
                status = SYSTEM_LINK_STATUS_EFAIL;
                break; /* Break from switch case */
        }
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
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

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
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    OSA_assert(queId < NULL_SRC_LINK_MAX_OUT_QUE);
    OSA_assert(pBufList != NULL);

    status =  OSA_bufGetFull(&pObj->outBufQue, pBufList, OSA_TIMEOUT_NONE);
    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        pObj->linkStats.getFullBufCount++;
    }

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
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    NullSrcLink_Obj *pObj = (NullSrcLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    OSA_assert(queId < NULL_SRC_LINK_MAX_OUT_QUE);
    OSA_assert(pBufList != NULL);
    OSA_assert(pBufList->numBuf <= NULL_SRC_LINK_MAX_OUT_BUFFERS);

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        OSA_assert(bufId < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

        chId = pBufList->buffers[bufId]->chNum;
        OSA_assert(chId < NULL_SRC_LINK_MAX_CH);

        OSA_assert(
            OSA_ARRAYISVALIDENTRY(
                pBufList->buffers[bufId], pObj->buffers[chId]));
    }

    status = OSA_bufPutEmpty(&pObj->outBufQue, pBufList);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    pObj->linkStats.putEmptyBufCount += pBufList->numBuf;

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
    UInt32 chId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 numBuf;


    if(pObj->isFirstBufferSent==FALSE)
    {
        pObj->isFirstBufferSent = TRUE;

        /*
        * Reset the null src link statistics when first buffer is ready to be
        * sent to next link.
        */
        OSA_resetLinkStatistics(&pObj->linkStats,
                            pObj->linkInfo.queInfo[0].numCh, 1);

        OSA_resetLatency(&pObj->linkLatency);
        OSA_resetLatency(&pObj->srcToLinkLatency);
    }

    pObj->linkStats.newDataCmdCount++;

    pOutQueInfo = &pObj->createArgs.outQueInfo;

    numBuf = 0;

    for (chId = 0; chId < pOutQueInfo->numCh; chId++)
    {
        status = OSA_bufGetEmptyBuffer(&pObj->outBufQue, &pBuffer, OSA_TIMEOUT_NONE);

        pObj->linkStats.chStats[chId].inBufRecvCount++;

        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            /*
            * If for this channel buffer is not available then update stats
            * for dropped buffer and continue for other channels
            */
            pObj->linkStats.chStats[chId].inBufDropCount++;
            continue;
        }

        OSA_assert(pBuffer != NULL);

        if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
        {
            status = SYSTEM_LINK_STATUS_SOK;

            /*
             * If file data has to read into system buffers in Run state
             * then fill pBuffer with valid filedata before sending
             * to next link
             */
            if(pObj->createArgs.channelParams[chId].fileReadMode
                       == NULLSRC_LINK_FILEREAD_RUN_TIME)
            {
                status = NullSrcLink_fillData(pObj, chId, pBuffer);
            }
        }
        else
        {
            /* Invalid mode, return output buffer back to empty queue */
            status = SYSTEM_LINK_STATUS_EFAIL;
        }

        pBuffer->srcTimestamp = OSA_getCurGlobalTimeInUsec();
        // TODO : uncomment this on 2.8+
        //pBuffer->frameId      = 0;

        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            /* return output buffer back to empty que */
            OSA_bufPutEmptyBuffer(&pObj->outBufQue, pBuffer);

            pObj->linkStats.chStats[chId].outBufDropCount[0]++;
            continue;
        }

        numBuf++;

        /*
        *Putting the buffer onto the Full Queue
        */
        status = OSA_bufPutFullBuffer(&pObj->outBufQue, pBuffer);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pObj->linkStats.chStats[chId].inBufProcessCount++;
        pObj->linkStats.chStats[chId].outBufCount[0]++;
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
    Int32 status;
    pObj->timerHndl.period = 33;
    status = OSA_timerStart(&pObj->timerHndl);
    OSA_assert(status == OSA_SOK);

    return status;
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
    Int32 status;
    status = OSA_timerStop(&pObj->timerHndl);
    return status;
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
    pBaseAddr = OSA_memAllocSR(
            OSA_HEAPID_DDR_CACHED_SR1,
            bufferSize * pObj->createArgs.channelParams[channelID].numBuffers,
            32U);
    OSA_assert(pBaseAddr != NULL);
    pObj->allocatedAddr[channelID][0U] = pBaseAddr;

    for(bufId = 0U;
        bufId < pObj->createArgs.channelParams[channelID].numBuffers;
        bufId++)
    {
        /*Initialising System_BitstreamBuffer for every buffer on this channel*/
        bitstreamBuf = &pObj->bitstreamBuf[channelID][bufId];
        bitstreamBuf->bufAddr = pBaseAddr;
        bitstreamBuf->bufSize = bufferSize;

        pObj->bufferAddr[bufId] = pBaseAddr;

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

        if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
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
                status = NullSrcLink_fillData(pObj, channelID, buffer);
                if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                {
                    /* For unsupported format or buftype EFAIL is returned,
                     * then assert */
                    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
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
            status = SYSTEM_LINK_STATUS_EFAIL;
        }

        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            /* Put the frame on empty queue*/
            status = OSA_bufPutEmptyBuffer(&pObj->outBufQue, buffer);
            OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
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
            frameSize = VpsUtils_align(frameSize, 32U);

            /*Allocating memory for all the frames (buffers) on this channel*/
            pBaseAddr = OSA_memAllocSR(
                OSA_HEAPID_DDR_CACHED_SR1,
                frameSize * pObj->createArgs.channelParams[channelID].numBuffers,
                32U);
            OSA_assert(pBaseAddr != NULL);
            pObj->allocatedAddr[channelID][0U] = pBaseAddr;

            for(frameId = 0;
                frameId < pObj->createArgs.channelParams[channelID].numBuffers;
                frameId++)
            {
                videoFrame = &pObj->videoFrames[channelID][frameId];

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
                        status = NullSrcLink_fillData(pObj, channelID, buffer);
                        if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                        {
                            /* For unsupported format or buftype EFAIL is
                             * returned, then assert
                             */
                            OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            breakForLoop = (Bool)TRUE;
                        }
                    }
                    else
                    {
                        status = SYSTEM_LINK_STATUS_EFAIL;
                        breakForLoop = (Bool)TRUE;
                    }
                }
                else
                {
                    status = SYSTEM_LINK_STATUS_EFAIL;
                    breakForLoop = (Bool)TRUE;
                }

                if(breakForLoop)
                {
                    break;
                }

                /* Put the frame on empty queue*/
                status = OSA_bufPutEmptyBuffer(&pObj->outBufQue, buffer);
                OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            break;

        case SYSTEM_DF_YUV422I_YUYV:
            /* for a single plane for Y, U and V*/
            pChInfo->height = VpsUtils_align(pChInfo->height, 2U);
            frameSize = pChInfo->pitch[0] * pChInfo->height;

            /* align frameSize to minimum required buffer alignment */
            frameSize = VpsUtils_align(frameSize, 32U);

            /*Allocating memory for all the frames (buffers) on this channel*/
            pBaseAddr = OSA_memAllocSR(
                OSA_HEAPID_DDR_CACHED_SR1,
                frameSize * pObj->createArgs.channelParams[channelID].numBuffers,
                32U);
            OSA_assert(pBaseAddr != NULL);
            pObj->allocatedAddr[channelID][0U] = pBaseAddr;

            for(frameId = 0;
                frameId < pObj->createArgs.channelParams[channelID].numBuffers;
                frameId++)
            {
                videoFrame = &pObj->videoFrames[channelID][frameId];

                videoFrame->bufAddr[0] = pBaseAddr;
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
                        status = NullSrcLink_fillData(pObj, channelID, buffer);
                        if (status != SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS)
                        {
                            /* For unsupported format or buftype EFAIL
                             * is returned, then assert
                             */
                            OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        status = SYSTEM_LINK_STATUS_EFAIL;
                    }
                }
                else
                {
                        status = SYSTEM_LINK_STATUS_EFAIL;
                }
                /* Put the frame on empty queue*/
                status = OSA_bufPutEmptyBuffer(&pObj->outBufQue, buffer);
                OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            break;

        default:
            status = SYSTEM_LINK_STATUS_EFAIL;
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
                status = NullSrcLink_allocAndQueueBitstreamBufs(pObj, chId);
                break;
            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                status = NullSrcLink_allocAndQueueVideoFrames(pObj, chId);
                break;
            default:
                OSA_assert(
                    (bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM) ||
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
    union sigval sigevValue;

    /*
    * Validating the create params
    * TODO: Extend to validate width, height and pitch params also
    */
    /* Only one channel is supported as of now */
    OSA_assert(pPrm->outQueInfo.numCh == 1U);
    OSA_assert(pPrm->timerPeriodMilliSecs != 0);
    /* No support for Network RX Mode */
    OSA_assert(pPrm->dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE);

    /*
    *Copying Create arguments into Link object from the parametes passed by app
    */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* Block on Get, but not on put */
    status = OSA_bufCreate(&pObj->outBufQue, TRUE, FALSE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

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
                OSA_assert(
                    (pPrm->channelParams[chId].nameDataFile[0]  != (char)'\0') &&
                    (pPrm->channelParams[chId].nameIndexFile[0] != (char)'\0'));

                pObj->fpDataStream[chId] =
                        fopen(pPrm->channelParams[chId].nameDataFile, "rb");
                OSA_assert(pObj->fpDataStream[chId] != NULL);

                pObj->fpIndexFile[chId] =
                        fopen(pPrm->channelParams[chId].nameIndexFile, "r");
                OSA_assert(pObj->fpIndexFile[chId] != NULL);
            }
        }
        else
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
        OSA_assert(pPrm->channelParams[chId].numBuffers<=
                        NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH);
    }

    /*Populate the queue with buffers*/
    status = NullSrcLink_populateQueue(pObj);

    /*This flag is set when first buffer is sent to next link.
    * Resetting it at create time.
    */
    pObj->isFirstBufferSent = (Bool)FALSE;

    sigevValue.sival_ptr = pObj;

    status += OSA_timerCreate(&pObj->timerHndl,NullSrcLink_timerCallback,sigevValue);

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
Int32 NullSrcLink_delete(NullSrcLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, size;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType;
    System_VideoDataFormat dataFormat;

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
            OSA_memFreeSR(OSA_HEAPID_DDR_CACHED_SR1,
                        pObj->allocatedAddr[chId][0U],
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
                    size = VpsUtils_align(size, 32U);
                    /* Free memory for all buffers on this channel*/
                    OSA_memFreeSR(OSA_HEAPID_DDR_CACHED_SR1,
                        pObj->allocatedAddr[chId][0U],
                        size * pObj->createArgs.channelParams[chId].numBuffers);
                    break;

                case SYSTEM_DF_YUV422I_YUYV:
                    /* for a single plane for Y, U and V*/
                    size = pChInfo->pitch[0] * pChInfo->height;
                    /* align size to minimum required buffer alignment */
                    size = VpsUtils_align(size, 32U);
                    /* Free memory for all buffers on this channel*/
                    OSA_memFreeSR(OSA_HEAPID_DDR_CACHED_SR1,
                        pObj->allocatedAddr[chId][0U],
                        size * pObj->createArgs.channelParams[chId].numBuffers);
                    break;

                default:
                    status = SYSTEM_LINK_STATUS_EFAIL;
                    break;
            }

        }
        else
        {
            OSA_assert((bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM) ||
                         (bufferType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME));
        }
    }
    status = OSA_bufDelete(&pObj->outBufQue);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = OSA_timerDelete(&pObj->timerHndl);
    OSA_assert(status == OSA_SOK);

    if(pObj->createArgs.dataRxMode == NULLSRC_LINK_DATA_RX_MODE_FILE)
    {
        if(pObj->fpDataStream[chId])
        {
            fclose(pObj->fpDataStream[chId]);
        }
        if(pObj->fpIndexFile[chId])
        {
            fclose(pObj->fpIndexFile[chId]);
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
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
 * \brief Rewind Input files
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_restartFiles(
            NullSrcLink_Obj *pObj,
            NullSrcLink_RestartFileParams *pPrm)
{
    UInt32 chId = pPrm->chId;

    if(NULL != pObj->fpDataStream[chId])
    {
        fclose(pObj->fpDataStream[chId]);
    }

    if(NULL != pObj->fpIndexFile[chId])
    {
        fclose(pObj->fpIndexFile[chId]);
    }

    pObj->fpDataStream[chId] =
            fopen(pPrm->nameDataFile, "rb");
    OSA_assert(NULL != pObj->fpDataStream[chId]);

    pObj->fpIndexFile[chId] =
            fopen(pPrm->nameIndexFile, "r");
    OSA_assert(NULL != pObj->fpIndexFile[chId]);

    return SYSTEM_LINK_STATUS_SOK;
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
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Null Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullSrcLink_printLinkStats(NullSrcLink_Obj * pObj)
{
    OSA_printLinkStatistics(&pObj->linkStats,
                              "NULL_SRC",
                              (Bool)TRUE);

    OSA_printLatency("NULL_SRC",
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );
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
Int32 NullSrcLink_tskRun(NullSrcLink_Obj * pObj, OSA_TskHndl * pTsk,
                         OSA_MsgHndl ** pMsg, Bool * done, Bool * ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone, runAckMsg;
    OSA_MsgHndl *pRunMsg;
    UInt32 cmd;

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
        status = OSA_tskWaitMsg(pTsk, &pRunMsg);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }

        /* extract message command from message */
        cmd = OSA_msgGetCmd(pRunMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:
                /* ACK or free message before proceding */
                OSA_tskAckOrFreeMsg(pRunMsg, status);

                /* TODO: Do we require this? */
                #if 0
                flushCmds[0] = SYSTEM_CMD_NEW_DATA;
                OSA_tskFlushMsg(pTsk, flushCmds, 1U);
                #endif

                #if 0
                oldIntState = Hwi_disable();
                if(pObj->numPendingCmds)
                {
                    pObj->numPendingCmds--;
                }
                Hwi_restore(oldIntState);
                #else
                /* Hwi enable/disable cannot be called from App space */
                if(pObj->numPendingCmds)
                {
                    pObj->numPendingCmds--;
                }
                #endif


                /* new data needs to be processed*/
                status = NullSrcLink_processData(pObj);
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
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                /* print the null source link output buffer queue status*/
                NullSrcLink_printBufferStatus(pObj);
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NULL_SRC_LINK_CMD_PAUSE:
                NullSrcLink_pause(pObj);
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NULL_SRC_LINK_CMD_RESUME:
                NullSrcLink_resume(pObj);
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NULL_SRC_LINK_CMD_RESTARTFILES:
                NullSrcLink_restartFiles(
                    pObj,
                    ((NullSrcLink_RestartFileParams*)OSA_msgGetPrm(pRunMsg)));
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NULL_SRC_LINK_CMD_GET_BUF_INFO:
                NullSrcLink_getBufInfo(pObj,\
                    (NullSrcLink_GetBufInfoParams*)OSA_msgGetPrm(pRunMsg));
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            default:

                /* invalid command for this state ACK it, continue RUN loop */
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop the link */
    NullSrcLink_stop(pObj);

    /* ACK message if not ACKed earlier */
    if (runAckMsg)
    {
        OSA_tskAckOrFreeMsg(pRunMsg, status);
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
int NullSrcLink_tskMain(struct OSA_TskHndl *pTsk, OSA_MsgHndl *pMsg, Uint32 curState )
{
    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Bool ackMsg, done = (Bool)FALSE;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    NullSrcLink_Obj *pObj;

    /* IDLE state */

    pObj = (NullSrcLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
        * with error status */
        OSA_tskAckOrFreeMsg(pMsg, OSA_EFAIL);
        return OSA_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the link */
        status = NullSrcLink_create(pObj, OSA_msgGetPrm(pMsg));

        /* ACK based on create status */
        OSA_tskAckOrFreeMsg(pMsg, status);

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
            status = OSA_tskWaitMsg(pTsk, &pMsg);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }

            /* extract message command from message */
            cmd = OSA_msgGetCmd(pMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_START:
                    /* Start mull source driver */
                    status = NullSrcLink_start(pObj);

                    /* ACK based on create status */
                    OSA_tskAckOrFreeMsg(pMsg, status);

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
                    NullSrcLink_getBufInfo(pObj,\
                        (NullSrcLink_GetBufInfoParams*)OSA_msgGetPrm(pMsg));
                    OSA_tskAckOrFreeMsg(pMsg, status);
                    break;

                default:
                    /* invalid command for this state ACK it and continue READY
                     * loop */
                    OSA_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        /* exiting READY state, delete link */
        NullSrcLink_delete(pObj);

        /* ACK message if not previously ACK'ed */
        if ((pMsg != NULL) && ((Bool)TRUE == ackMsg))
        {
            OSA_tskAckOrFreeMsg(pMsg, status);
        }
    }

    /* entering IDLE state */
    return OSA_SOK;
}



Int32 NullSrcLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 nullSrcId;
    NullSrcLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for (nullSrcId = 0U; nullSrcId < NULL_SRC_LINK_OBJ_MAX; nullSrcId ++)
    {
        pObj = &gNullSrcLink_obj[nullSrcId];

        memset(pObj, 0U, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_NULL_SRC_0 +
            nullSrcId);

        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &NullSrcLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &NullSrcLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &NullSrcLink_getInfo;

        System_registerLink(pObj->tskId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * ipcOutLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "NULL_SRC_%u", (unsigned int)nullSrcId);
        status = OSA_tskCreate(&pObj->tsk,
                               NullSrcLink_tskMain,
                               NULL_SRC_LINK_TSK_PRI,
                               NULL_SRC_LINK_TSK_STACK_SIZE,
                               0,
                               pObj,
                               pObj->tskName);
        OSA_assert(status == OSA_SOK);
        Vps_printf(" %s : Init done - linkid-0x%x\n", pObj->tskName, pObj->tskId);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for Null link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NullSrcLink_deInit(void)
{
    UInt32 nullSrcId;

    for (nullSrcId = 0; nullSrcId < NULL_SRC_LINK_OBJ_MAX; nullSrcId++)
    {
        OSA_tskDelete(&gNullSrcLink_obj[nullSrcId].tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
            gNullSrcLink_obj[nullSrcId].tskName, gNullSrcLink_obj[nullSrcId].tskId);
    }
    return SYSTEM_LINK_STATUS_SOK;
}



