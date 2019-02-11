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
 * \file networkRxLink_tsk.c
 *
 * \brief   This file has the implementation of Network Rx Link API
 **
 *         This file implements Network Rx link as alternate of capture link.
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
#include "networkRxLink_priv.h"

/*****************************************************************************
 *  DEFINES
 *****************************************************************************
 */
#define NETWORK_RX_MAX_FRAMES (256000U)
#define NETWORK_RX_MAX_META_FRAME_SIZE     (2U*1024U*1024U)

/*****************************************************************************
 *  Function declarations
 *****************************************************************************
 */
Int32 NetworkRxLink_create(NetworkRxLink_Obj * pObj,
                         const NetworkRxLink_CreateParams * pPrm);
Int32 NetworkRxLink_start(NetworkRxLink_Obj * pObj);

Int32 NetworkRxLink_processData(NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_populateQueue(NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_stop(NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_Delete(NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_tskRun(NetworkRxLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);
Int32 NetworkRxLink_printBufferStatus(NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_printLinkStats(const NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_allocAndQueueVideoFrames(NetworkRxLink_Obj * pObj,
                                           UInt32 channelID);
Int32 NetworkRxLink_allocAndQueueBitstreamBufs(NetworkRxLink_Obj * pObj,
                                             UInt32 channelID);
Int32 NetworkRxLink_allocAndQueueMetadataFrames(NetworkRxLink_Obj * pObj,
                                             UInt32 channelID);
Int32 NetworkRxLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 NetworkRxLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList* pBufList);
Int32 NetworkRxLink_getInfo(Void * ptr, System_LinkInfo * info);
Void NetworkRxLink_timerCallback(UArg arg);
Int32 NetworkRxLink_getBufInfo(const NetworkRxLink_Obj *pObj,
                        NetworkRxLink_GetBufInfoParams *pBufInfoPrm);
Int32 NetworkRxLink_pause(NetworkRxLink_Obj * pObj);
Int32 NetworkRxLink_resume(NetworkRxLink_Obj * pObj);

/**
 ******************************************************************************
 * \brief Link Stack
 ******************************************************************************
 */
#pragma DATA_ALIGN(gNetworkRxLink_tskStack, 32)
#pragma DATA_SECTION(gNetworkRxLink_tskStack, ".bss:taskStackSection")
UInt8 gNetworkRxLink_tskStack[NETWORK_RX_LINK_OBJ_MAX][NETWORK_RX_LINK_TSK_STACK_SIZE];

#define NUL_STR_SZ (32U)
/**
 ******************************************************************************
 * \brief Link object, stores all link related information
 ******************************************************************************
 */
NetworkRxLink_Obj gNetworkRxLink_obj[NETWORK_RX_LINK_OBJ_MAX];

/**
 ******************************************************************************
 * \brief This is a callback function, invoked whenever the timer is triggered.
 * This function then sends a 'New data' command to Network Rx itself so that
 * data can be sent to the Full buffer.
 *
 * \param  arg  [IN]  Network Rx link instance handle
 *
 ******************************************************************************
*/
Void NetworkRxLink_timerCallback(UArg arg)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic prototype which supports all dataTypes.
     * This typecasting is necessary.
     */
    NetworkRxLink_Obj *pObj = (NetworkRxLink_Obj *) arg;

    if(FALSE == pObj->createArgs.pauseLink)
    {
        Utils_tskSendCmd(&pObj->tsk, SYSTEM_CMD_NEW_DATA, NULL);
        pObj->numPendingCmds++;

        pObj->linkStatsInfo->linkStats.notifyEventCount++;
    }
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
Int32 NetworkRxLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    NetworkRxLink_Obj *pObj = (NetworkRxLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Callback function to give full buffers to the next link
 *
 * Network Rx link sends message to next link about availability of buffers.
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
Int32 NetworkRxLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    UInt32 bufId;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    NetworkRxLink_Obj *pObj = (NetworkRxLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(queId < NETWORK_RX_LINK_MAX_OUT_QUE);
    UTILS_assert(pBufList != NULL);

    /* NetworkRxLink_Obj uses a single queue. queId is still passed as this
    * function is common to all the links. Here we just ignore the queId.
    */
    for (bufId = 0; bufId < NETWORK_RX_LINK_MAX_OUT_BUFFERS; bufId++)
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
Int32 NetworkRxLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList* pBufList)
{
    UInt32 bufId, chId;

    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    NetworkRxLink_Obj *pObj = (NetworkRxLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(queId < NETWORK_RX_LINK_MAX_OUT_QUE);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= NETWORK_RX_LINK_MAX_OUT_BUFFERS);

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        UTILS_assert(bufId < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

        chId = pBufList->buffers[bufId]->chNum;
        UTILS_assert(chId < NETWORK_RX_LINK_MAX_CH);

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
 * \param  pObj          [IN] Network rx link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_processData(NetworkRxLink_Obj * pObj)
{
    System_LinkQueInfo *pOutQueInfo;
    System_Buffer *pBuffer;
    UInt32 chId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 numBuf;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstBufferSent==FALSE)
    {
        pObj->isFirstBufferSent = TRUE;

        /*
        * Reset the network rx link statistics when first buffer is ready to be
        * sent to next link.
        */
        Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                            pObj->linkInfo.queInfo[0].numCh, 1U);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    pOutQueInfo = &pObj->createArgs.outQueInfo;

    numBuf = 0;

    for (chId = 0; chId < pOutQueInfo->numCh; chId++)
    {
        status = Utils_queGet(&pObj->emptyOutBufQue[chId], (Ptr *)&pBuffer, 1U,
                              BSP_OSAL_NO_WAIT);

        linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;

        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            /*
            * If for this channel buffer is not available then update stats
            * for dropped buffer and continue for other channels
            */
            linkStatsInfo->linkStats.chStats[chId].inBufDropCount++;
        }
        else
        {

            UTILS_assert(pBuffer != NULL);

            if( (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
                ||
                (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
            {
                status += NetworkRxLink_drvFillData(pObj, chId, pBuffer);
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
            }
            else
            {
                numBuf++;
                /*
                *Putting the buffer onto the Full Queue
                */
                status += Utils_quePut(&pObj->fullOutBufQue, pBuffer, BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                linkStatsInfo->linkStats.chStats[chId].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats[chId].outBufCount[0]++;
            }
        }
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
 * \param  pObj           [IN] Network Rx link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_start(NetworkRxLink_Obj * pObj)
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
 * \param  pObj           [IN] Network Rx link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_stop(NetworkRxLink_Obj * pObj)
{
    BspOsal_clockStop(pObj->timer);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Allocate and Queue Bitstream buffers for a specific channel for netwo
 * rk rx link
 *
 *  \param pObj         [IN] Network Rx link object
 *  \param channelID    [IN] Channel Number for which bitstream buffers need to
 *                          be queued
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */

Int32 NetworkRxLink_allocAndQueueBitstreamBufs(NetworkRxLink_Obj * pObj,
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
    * Network Rx link has a single output queue
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

        if( (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
            ||
            (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
        {
            status += SYSTEM_LINK_STATUS_SOK;
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
 * \brief Allocate and Queue Video frames for a channel for network rx link
 *
 *  \param pObj             [IN] Network Rx link object
 *  \param channelID    [IN] Channel Number for which frames need to be queued
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_allocAndQueueVideoFrames(NetworkRxLink_Obj * pObj,
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
    * Network Rx link has a single output queue
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

                if( (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
                    ||
                (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
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

                if( (pObj->createArgs.dataRxMode ==
                   NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
                   ||
                (pObj->createArgs.dataRxMode ==
                        NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
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

                if( (pObj->createArgs.dataRxMode ==
                   NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
                   ||
                (pObj->createArgs.dataRxMode ==
                        NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
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
 * \brief Allocate and Queue Metadata buffers for a specific channel for network
 * rx link
 *
 *  \param pObj         [IN] Network Rx link object
 *  \param channelID    [IN] Channel Number for which bitstream buffers need to
 *                          be queued
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */

Int32 NetworkRxLink_allocAndQueueMetadataFrames(NetworkRxLink_Obj * pObj,
                                             UInt32 channelID)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId, bufferSize;
    System_Buffer *buffer;
    System_MetaDataBuffer *metaDatabuf;
    void *pBaseAddr;

    bufferSize = NETWORK_RX_MAX_META_FRAME_SIZE;

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
        /*Initialising System_MetaDataBuffer for every buffer on this channel*/
        metaDatabuf = &pObj->metaDataBuf[channelID][bufId];
        metaDatabuf->numMetaDataPlanes = 1U;
        metaDatabuf->bufAddr[0] = pBaseAddr;
        metaDatabuf->metaBufSize[0] = bufferSize;
        metaDatabuf->metaFillLength[0] = bufferSize;

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
        buffer->bufType = SYSTEM_BUFFER_TYPE_METADATA;
        buffer->chNum = channelID;
        buffer->payloadSize = sizeof(System_MetaDataBuffer);
        buffer->payload = metaDatabuf;

        if( (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
            ||
            (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
        {
            status += SYSTEM_LINK_STATUS_SOK;
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
 * \brief Polulates the queue with buffers for network rx link
 *
 *  \param pObj         [IN] Network Rx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_populateQueue(NetworkRxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType;

    /*
    * All buffers are contiguous Initializing them here.
    */
    memset(&pObj->buffers, 0,
                sizeof(System_Buffer)*NETWORK_RX_LINK_MAX_OUT_BUFFERS);
    memset(&pObj->videoFrames, 0,
                sizeof(System_VideoFrameBuffer)*NETWORK_RX_LINK_MAX_OUT_BUFFERS);
    memset(&pObj->bitstreamBuf, 0,
                sizeof(System_BitstreamBuffer)*NETWORK_RX_LINK_MAX_OUT_BUFFERS);

    /*
    * Network Rx link has a single output queue. Hence index 0 is used for queInfo
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
                status += NetworkRxLink_allocAndQueueBitstreamBufs(pObj, chId);
                break;
            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                status += NetworkRxLink_allocAndQueueVideoFrames(pObj, chId);
                break;
            case SYSTEM_BUFFER_TYPE_METADATA:
                status += NetworkRxLink_allocAndQueueMetadataFrames(pObj, chId);
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
 * \brief Network Rx API for link. Link gets created using this function.
 *
 * Sets up link data structure, allocates and queue buffers. Makes link ready
 * for operation.
 *
 * \param  pObj     [IN] Network Rx link global handle
 * \param  pPrm    [IN] Network Rx link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_create(NetworkRxLink_Obj * pObj,
                         const NetworkRxLink_CreateParams * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;

    /*
    * Validating the create params
    * TODO: Extend to validate width, height and pitch params also
    */
    UTILS_assert(pPrm->outQueInfo.numCh <= NETWORK_RX_LINK_MAX_CH);
    UTILS_assert(pPrm->timerPeriodMilliSecs != 0);

    /*
    *Copying Create arguments into Link object from the parametes passed by app
    */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    status += Utils_queCreate(&pObj->fullOutBufQue,
         NETWORK_RX_LINK_MAX_OUT_BUFFERS,
         pObj->pBufferOnFullQ,
         UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Network Rx link has a single queue.
     * Initializing it.
     */
    pObj->linkInfo.numQue = 1;
    pObj->linkInfo.queInfo[0].numCh = pPrm->outQueInfo.numCh;
    for (chId = 0; chId < pPrm->outQueInfo.numCh; chId++)
    {
        memcpy(&pObj->linkInfo.queInfo[0].chInfo[chId],
               &pPrm->outQueInfo.chInfo[chId],
               sizeof(System_LinkChInfo));

        if( pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP )
        {
            status += SYSTEM_LINK_STATUS_SOK;
        }
        else if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
        {
#if !(defined(NSP_TFDTP_INCLUDE))
            Vps_printf(" NETWORK_RX: NETWORK_TFDTP_RX: NSP TFDTP build not enabled !!!\n");
            UTILS_assert(FALSE);
#endif
        }
        else
        {
            status += SYSTEM_LINK_STATUS_EFAIL;
        }
        UTILS_assert(pPrm->channelParams[chId].numBuffers<=
                        NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH);

        status += Utils_queCreate(&pObj->emptyOutBufQue[chId],
             NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH,
             pObj->pBufferOnEmptyQ[chId],
             UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*Populate the queue with buffers*/
    status += NetworkRxLink_populateQueue(pObj);

    /*This flag is set when first buffer is sent to next link.
    * Resetting it at create time.
    */
    pObj->isFirstBufferSent = (Bool)FALSE;

    if ( (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
        ||
         (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )
    {
        NetworkRxLink_drvCreate(pObj);
    }

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "NETWORK_RX");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    /* MISRA.CAST.FUNC_PTR
     * MISRAC_2004 Rule_11.1
     * MISRAC_WAIVER:
     * Valid type-casting from function pointer to function pointer.
     */
    /* Creating timer and setting timer callback function*/
    pObj->timer = BspOsal_clockCreate(
                        (BspOsal_ClockFuncPtr) &NetworkRxLink_timerCallback,
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
 * \brief Delete network rx link
 *
 *
 * \param  pObj         [IN] Network rx link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_Delete(NetworkRxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, size;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType = SYSTEM_BUFFER_TYPE_FORCE32BITS;
    System_VideoDataFormat dataFormat;

    status += Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Network Rx - there is a single queue */
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
            size = NETWORK_RX_MAX_META_FRAME_SIZE;

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

    if( (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
        ||
        (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP) )

    {
        NetworkRxLink_drvDelete(pObj);
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
 *  \param pObj         [IN] Network Rx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkRxLink_getBufInfo(const NetworkRxLink_Obj *pObj,
                        NetworkRxLink_GetBufInfoParams *pBufInfoPrm)
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
 * \brief Pause Network Rx
 *
 *  \param pObj         [IN] Network Rx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkRxLink_pause(NetworkRxLink_Obj *pObj)
{
    pObj->createArgs.pauseLink = TRUE;
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Resume Network Rx
 *
 *  \param pObj         [IN] Network Rx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkRxLink_resume(NetworkRxLink_Obj *pObj)
{
    pObj->createArgs.pauseLink = FALSE;
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Network Rx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkRxLink_printLinkStats(const NetworkRxLink_Obj * pObj)
{
    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
                              "NETWORK_RX",
                              (Bool)TRUE);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print network rx link buffer statistics
 *
 *  \param pObj         [IN] Network Rx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkRxLink_printBufferStatus(NetworkRxLink_Obj * pObj)
{
    System_LinkQueInfo *pOutQueInfo;
    UInt32 chId;

    pOutQueInfo = &pObj->createArgs.outQueInfo;

    Vps_printf(" [%s] Buffer Q Status,\n", "NETWORK RX");

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
 * \param  pObj     [IN] Network Rx link object
 * \param  pTsk     [IN] Network Rx link Task handle
 * \param  pMsg     [IN] Message for the link. Contains command and args.
 * \param  done     [IN] Flag to exit idle state.
 * \param  ackMsg   [IN] Flag to decide whether to send ack message or not
 *                          to caller
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_tskRun(NetworkRxLink_Obj * pObj, Utils_TskHndl * pTsk,
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
                status += NetworkRxLink_processData(pObj);
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
                /* print the network rx link statistics*/
                NetworkRxLink_printLinkStats(pObj);
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                /* print the network rx link output buffer queue status*/
                NetworkRxLink_printBufferStatus(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NETWORK_RX_LINK_CMD_PAUSE:
                NetworkRxLink_pause(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case NETWORK_RX_LINK_CMD_RESUME:
                NetworkRxLink_resume(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            default:

                /* invalid command for this state ACK it, continue RUN loop */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop the link */
    NetworkRxLink_stop(pObj);

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
Void NetworkRxLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl *pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done = (Bool)FALSE;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    NetworkRxLink_Obj *pObj;

    /* IDLE state */

    pObj = (NetworkRxLink_Obj *) pTsk->appData;

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
        status += NetworkRxLink_create(pObj, Utils_msgGetPrm(pMsg));

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
                    status += NetworkRxLink_start(pObj);

                    /* ACK based on create status */
                    Utils_tskAckOrFreeMsg(pMsg, status);

                    /* if start status is error then remain in READY state */
                    if (status == SYSTEM_LINK_STATUS_SOK)
                    {
                        /* start success, entering RUN state */
                        status =
                            NetworkRxLink_tskRun(
                                pObj, pTsk, &pMsg, &done, &ackMsg);
                    }

                    break;
                case SYSTEM_CMD_DELETE:
                    /* exit READY state */
                    done = (Bool)TRUE;
                    ackMsg = (Bool)TRUE;
                    break;
                case NETWORK_RX_LINK_CMD_GET_BUF_INFO:
                    status += NetworkRxLink_getBufInfo(pObj,\
                        (NetworkRxLink_GetBufInfoParams*)Utils_msgGetPrm(pMsg));
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
        NetworkRxLink_Delete(pObj);

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
 * \brief Init function for network rx link. BIOS task for link gets
 * created/registered here.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkObj linkObj;
    UInt32 networkRxId;
    NetworkRxLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for (networkRxId = 0U; networkRxId < NETWORK_RX_LINK_OBJ_MAX; networkRxId++)
    {
        /* register link with system API */

        pObj = &gNetworkRxLink_obj[networkRxId];

        memset(pObj, 0, sizeof(NetworkRxLink_Obj));

        pObj->tskId =
            SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_NETWORK_RX_0) + networkRxId;

        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &NetworkRxLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &NetworkRxLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &NetworkRxLink_getInfo;

        System_registerLink(pObj->tskId, &linkObj);

        snprintf(pObj->name, NUL_STR_SZ, "NETWORK_RX%u   ", networkRxId);

        /* Create link task, task remains in IDLE state
       * NetworkRxLink_tskMain is called when a message command is received
       */
        status += Utils_tskCreate(&pObj->tsk,
                                 NetworkRxLink_tskMain,
                                 NETWORK_RX_LINK_TSK_PRI,
                                 gNetworkRxLink_tskStack[networkRxId],
                                 NETWORK_RX_LINK_TSK_STACK_SIZE,
                                 pObj, pObj->name, UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief De-Init function for network rx link. BIOS task for network rx link
 * gets deleted in here.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 NetworkRxLink_deInit(void)
{
    UInt32 networkRxId;

    for (networkRxId = 0U; networkRxId < NETWORK_RX_LINK_OBJ_MAX; networkRxId++)
    {
        Utils_tskDelete(&gNetworkRxLink_obj[networkRxId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
/* Nothing beyond this point */
