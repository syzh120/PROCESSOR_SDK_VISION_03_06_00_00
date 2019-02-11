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
 * \file avbTxLink_drv.c
 *
 * \brief  This file communicates with driver for AvbTx link.
 *
 *         This file calls the driver commands and APIs for the application
 *         commands and APIs. All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (March 2017) : [PYJ] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "avbTxLink_priv.h"

/*******************************************************************************
 *  Internal function
 *******************************************************************************
 */
static Int32 AvbTxLink_findEmptyBuffer(AvbTxLink_avbTalkerObj *pAvbTxTalkerInst);
void AvbTxLink_drvCallback(avbtp_tx_buffer *buff,
                           void *cbdata,
                           uint32_t talkerIdx);
/**
 *******************************************************************************
 *
 * \brief Find empty AVB Tx buffer Descriptor
 *
 *******************************************************************************
 */
static Int32 AvbTxLink_findEmptyBuffer(AvbTxLink_avbTalkerObj *pAvbTxTalkerInst)
{
    uint32_t numBufsToCheck = AVB_TX_LINK_MAX_NUM_BUFS_PER_TALKER;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    while (pAvbTxTalkerInst->avbTxbuffDesc[pAvbTxTalkerInst->freeBufIdx].bufState != BUFF_EMPTY)
    {
        pAvbTxTalkerInst->freeBufIdx++;
        if (pAvbTxTalkerInst->freeBufIdx >= AVB_TX_LINK_MAX_NUM_BUFS_PER_TALKER)
        {
            pAvbTxTalkerInst->freeBufIdx = 0;
        }

        numBufsToCheck--;
        if (0U == numBufsToCheck)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function from driver to application
 *
 * CallBack Function registered in NSP, ITs called on every new
 * frame received at the listner. Frame is further passed to next component
 *
 * \param  pPayload    buf - Buffer with mjpeg data
 *
 * \param  PayloadSize  nPayloadSize - Size of payload data
 *
 * \param  rsdinfo     avbtp_sd_info_t *pStreaminfo - stream data information
 *
 * \param  pCbData     void *pCbData - callback function data.
 *
 * \param  nChanNum    channelNum - Channel Number of the frame received
 *
 * \param  nBuffIndex  nBuffIndex - State of Buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
void AvbTxLink_drvCallback(avbtp_tx_buffer *buff,
                          void *cbdata,
                          uint32_t talkerIdx)
{
    Int32 status;
    AvbTxLink_Obj *pObj = (AvbTxLink_Obj*)cbdata;
    System_LinkStatistics *linkStatsInfo;
    avbtp_tx_buff_desc *pTxBufDesc;


    UTILS_assert(NULL != buff);

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.notifyEventCount++;

    if (NULL != buff->buffMetaData)
    {
        pTxBufDesc = (avbtp_tx_buff_desc *)buff->buffMetaData;
        pTxBufDesc->bufState = BUFF_EMPTY;

        /* Put System_Buffer in System buffer queue
         * These will be released when
         * DISPLAY_LINK_CMD_RELEASE_FRAMES is called
         *
         * We need a queue here since we cannot free these buffers
         * from ISR context
         */
        status = Utils_quePut(&pObj->systemBufferQueue[pTxBufDesc->inQueId],
                            (Ptr)pTxBufDesc->pSysBuffer,
                            (UInt32)BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


        Utils_tskSendCmd(&pObj->tsk, AVB_TX_LINK_CMD_RELEASE_FRAMES, NULL);

    }
    else
    {
        Vps_printf(" AVBTX: Application should set buffer pointer !!!\n");
        UTILS_assert(FALSE);
    }

}

/**
 *******************************************************************************
 *
 * This function releases System_Buffer's queued from ISR context to the
 * previous link
 *
 *******************************************************************************
 */
Int32 AvbTxLink_drvReleaseData(AvbTxLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId = 0;
    System_BufferList bufList;
    System_Buffer *pBuffer;
    System_LinkInQueParams *pInQueParams;


    for (queId = 0; queId < pObj->createArgs.numInQue; queId++)
    {
        bufList.numBuf = 0;

        pInQueParams = &pObj->createArgs.inQueParams[queId];
        do
        {
            /*  MISRA.CAST.PTR
            *  MISRAC_2004_Rule_11.4:Cast between a pointer to object type and
            *                        a different pointer to object type
            *  State: FIXED IN LATER RELEASE -> Waiver -> Case by case
            *  Pointers to different layer's handles are stored as void*.
            */
            status = Utils_queGet(&pObj->systemBufferQueue[queId],
                        (Ptr*)&pBuffer,
                        1U,
                        BSP_OSAL_NO_WAIT);


            if((status==SYSTEM_LINK_STATUS_SOK) && (pBuffer != NULL))
            {

                bufList.buffers[bufList.numBuf] = pBuffer;

                bufList.numBuf++;
            }
        } while(status==SYSTEM_LINK_STATUS_SOK);

        /* release buffers to previous link */
        if (bufList.numBuf)
        {
            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                        pInQueParams->prevLinkQueId,
                                        &bufList);
        }
    }

    return status;
}

/**
 *******************************************************************************
 * \brief Null Link just receives incoming buffers and returns back to the
 *   sending link. This function does the same
 *
 * \param  pObj     [IN]  Null link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AvbTxLink_drvProcessFrames(AvbTxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList, freeBufList;
    UInt32 queId, bufId, chNum;
    System_Buffer *pBuffer;
    System_BitstreamBuffer *bitstreamBuf;
    System_VideoFrameBuffer *videoFrame;
    System_VideoDataFormat dataFormat;
    System_LinkChInfo *pChInfo;
    System_LinkStatistics *linkStatsInfo;
    linkStatsInfo = pObj->linkStatsInfo;


    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    for (queId = 0; queId < pObj->createArgs.numInQue; queId++)
    {
        freeBufList.numBuf = 0;

        pInQueParams = &pObj->createArgs.inQueParams[queId];

        System_getLinksFullBuffers(pInQueParams->prevLinkId,
                                pInQueParams->prevLinkQueId, &bufList);
        if (bufList.numBuf)
        {
            pObj->recvCount += bufList.numBuf;

            for (bufId = 0; bufId < bufList.numBuf; bufId++)
            {
                pBuffer = bufList.buffers[bufId];

                if( pBuffer != NULL )
                {
                    chNum = pBuffer->chNum;

                    /* reset stats counter if this is first frame that is recived */
                    if(FALSE == pObj->isFirstFrameRecv)
                    {
                        pObj->isFirstFrameRecv = (Bool)TRUE;

                        Utils_resetLinkStatistics(
                                &linkStatsInfo->linkStats,
                                pObj->inQueInfo[queId].numCh,
                                0);

                        Utils_resetLatency(&linkStatsInfo->linkLatency);
                        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
                    }

                    if ( (queId < AVB_TX_LINK_MAX_IN_QUE)
                            &&
                    (chNum < SYSTEM_MAX_CH_PER_OUT_QUE)
                            &&
                    (chNum < AVB_TX_LINK_MAX_TALKERS_DEFAULT)
                            &&
                    (queId < pObj->createArgs.numInQue)
                            &&
                    (chNum < pObj->inQueInfo[queId].numCh))
                    {
                        UInt8 *dataAddr = NULL;
                        UInt32 dataSize = 0U;

                        linkStatsInfo->linkStats.chStats[chNum].inBufRecvCount++;
                        pChInfo = &pObj->inQueInfo[queId].chInfo[chNum];

                        switch(pBuffer->bufType)
                        {
                            case SYSTEM_BUFFER_TYPE_BITSTREAM:
                                bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;
                                dataAddr = bitstreamBuf->bufAddr;
                                dataSize = bitstreamBuf->fillLength;
                                break;
                            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                                videoFrame = (System_VideoFrameBuffer*)pBuffer->payload;
                                dataFormat = (System_VideoDataFormat)
                                    System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

                                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                                {
                                    Vps_printf(" AVBTX: Only SYSTEM_DF_YUV422P is supported !!!\n");
                                    UTILS_assert(FALSE);
                                }
                                else
                                {
                                    dataAddr = videoFrame->bufAddr[0U];
                                    dataSize = pChInfo->pitch[0U] * pChInfo->height;

                                }
                                break;
                            default:
                            status = SYSTEM_LINK_STATUS_EFAIL;
                            break;
                        }

                        if(status != SYSTEM_LINK_STATUS_SOK)
                        {
                            Vps_printf(" AVBTX: Buffer type not supported !!!\n");
                            UTILS_assert(FALSE);
                        }
                        else
                        {
                            linkStatsInfo->linkStats.chStats[chNum].
                                    inBufProcessCount++;

                            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                                    pBuffer->linkLocalTimestamp);
                            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                                    pBuffer->srcTimestamp);

                            if (SYSTEM_LINK_STATUS_EFAIL ==
                                        AvbTxLink_findEmptyBuffer(&pObj->avbTxTalkerInst[queId][chNum]) )
                            {
                                Vps_printf(" AVBTX: No free buffer descriptor to transmit, modify AVB_TX_LINK_MAX_NUM_BUFS_PER_TALKER as per previous link !!!\n");
                                UTILS_assert(FALSE);
                            }
                            else
                            {
                                avbtp_tx_buffer *avbTxbuffArray[1U];
                                AvbTxLink_avbTalkerObj *pTalkerObj = &pObj->avbTxTalkerInst[queId][chNum];
                                avbtp_tx_buffer *pAvbTxbuf = &pTalkerObj->avbTxbuffDesc[pTalkerObj->freeBufIdx].buffer;

                                pTalkerObj->avbTxbuffDesc[pTalkerObj->freeBufIdx].bufState = BUFF_PARTIAL;
                                pTalkerObj->avbTxbuffDesc[pTalkerObj->freeBufIdx].pSysBuffer = pBuffer;

                                pAvbTxbuf->avth = pObj->avbTxTalkerInst[queId][chNum].avbTalkerHandle;
                                pAvbTxbuf->needsFlushing = false;
                                pAvbTxbuf->pData = dataAddr;
                                pAvbTxbuf->size = dataSize;
                                pAvbTxbuf->buffMetaData = &pTalkerObj->avbTxbuffDesc[pTalkerObj->freeBufIdx];

                                avbTxbuffArray[0] = pAvbTxbuf;

                                avbtp_talker_enqueue(pObj->avbHandle, avbTxbuffArray,  1U);

#ifdef SYSTEM_DEBUG_AVBTX_RT
                                Vps_printf(" AVBTX: Enqued new buffer !!!\n");
#endif
                            }
                        }

                    }
                    else
                    {
                        /* If this is not the correct channel put buffer in buffer
                        * list to be released
                        */
                        Vps_printf(" AVBTX: Buffer from invalid channel !! ");

                        freeBufList.buffers[freeBufList.numBuf]
                            = pBuffer;

                        freeBufList.numBuf++;

                        linkStatsInfo->linkStats.chStats[chNum].inBufDropCount++;
                    }
                }
                else
                {
                    Vps_printf(" AVBTX: Null Buffer Pointer !! ");
                    status = SYSTEM_LINK_STATUS_EFAIL;
                }

            }

            if (0U != freeBufList.numBuf)
            {
                System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &freeBufList);
            }

        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Create API for link. Link gets created using this function.
 *
 * Creates driver instance, sets up link data structure, allocates and
 * queue frames to driver. Make link and driver ready for operation.
 *
 * \param  pObj     [IN] AVB link global handle
 * \param  pPrm     [IN] AVB link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbTxLink_drvCreate(AvbTxLink_Obj * pObj,
                          const AvbTxLink_CreateParams * pPrm)
{
    Int32 status = 0;
    UInt32 numTalkers = 0, desc = 0;
    UInt16 inQue = 0, chId = 0;
    System_LinkInfo inTskInfo;
    System_LinkQueInfo *pInQueInfo;

    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    UTILS_assert(pObj->createArgs.numInQue <= AVB_TX_LINK_MAX_IN_QUE);

    pObj->recvCount= 0;


    Vps_printf(" AVBTX: Create in progress !!!\n");


    pObj->avbHandle = avbtp_open();
    UTILS_assert(pObj->avbHandle != NULL);

    for (inQue = 0; inQue < pPrm->numInQue; inQue++)
    {
        status =
            System_linkGetInfo(pPrm->inQueParams[inQue].prevLinkId,
                               &inTskInfo);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        UTILS_assert(pPrm->inQueParams[inQue].prevLinkQueId <
                     inTskInfo.numQue);

        pObj->inQueInfo[inQue]
            =
                inTskInfo.queInfo
            [pPrm->inQueParams[inQue].prevLinkQueId];

        pInQueInfo = &pObj->inQueInfo[inQue];

        UTILS_assert(pInQueInfo->numCh <= SYSTEM_MAX_CH_PER_OUT_QUE);

        for (chId = 0; chId < pInQueInfo->numCh; chId++)
        {

            if (numTalkers > AVB_TX_LINK_MAX_TALKERS_DEFAULT)
            {
                Vps_printf(" AVBTP Tx: No. of talkers opened exceeded max. allowed!!!\n");
                UTILS_assert(FALSE);
            }

            pObj->avbTxTalkerInst[inQue][chId].freeBufIdx = 0U;

            pObj->avbTxTalkerInst[inQue][chId].avbTalkerHandle = avbtp_talker_open(pObj->avbHandle,
                                    &pObj->createArgs.dstMacId[chId][0U],
                                    AvbTxLink_drvCallback,
                                    pObj,
                                    pObj->createArgs.avbTpSubType[chId],
                                    pObj->createArgs.cvFormatSubType[chId]
                                    );
            if (pObj->avbTxTalkerInst[inQue][chId].avbTalkerHandle == NULL)
            {
                Vps_printf(" AVBTP Tx: avbTalkerInit failed !!!\n");
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }

            /*
             * Initialize queId for all buffer descriptors, this is used in frame
             * send callback
             */
            for (desc = 0; desc < AVB_TX_LINK_MAX_NUM_BUFS_PER_TALKER; desc++)
            {
                pObj->avbTxTalkerInst[inQue][chId].avbTxbuffDesc[desc].inQueId = inQue;
            }


            numTalkers++;
        }

        status = Utils_queCreate(&pObj->systemBufferQueue[inQue],
                                AVB_TX_LINK_MAX_FRAMES_PER_HANDLE,
                                pObj->systemBufferQueueMem,
                                UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "AVB_TX");
    UTILS_assert(NULL != pObj->linkStatsInfo);
    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("AVBTX:",
                        pObj->memUsed,
                        UTILS_ARRAYSIZE(pObj->memUsed));

    Vps_printf(" AVBTX: Create Done !!!\n");

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to start the link.
 *
 * This function calls the driver function to start the driver. As a part of
 * this call VIP AVBTP stack is ready to receive frames.
 *
 * \param  pObj           [IN] AVBTP link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbTxLink_drvStart(AvbTxLink_Obj * pObj)
{

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Tx: Start in progress !!!\n");
#endif

    avbtp_start(pObj->avbHandle);

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Tx: Start Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to stop driver and link.
 *
 * VIP capture hardware stops receiving frames after this call.
 *
 * \param  pObj         [IN] Capture link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbTxLink_drvStop(AvbTxLink_Obj * pObj)
{
#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Tx: Stop in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Tx: Stop Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Delete capture link and driver handle.
 *
 *
 * \param  pObj         [IN] Capture link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbTxLink_drvDelete(AvbTxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId = 0, chId = 0;
    AvbTxLink_avbTalkerObj  *pAvbTxTalkerInst;
    System_LinkQueInfo *pInQueInfo;

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Tx: Delete in progress !!!\n");
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(queId = 0 ; queId < pObj->createArgs.numInQue; queId++)
    {
        pInQueInfo = &pObj->inQueInfo[queId];
        for (chId = 0; chId < pInQueInfo->numCh; chId++)
        {
            pAvbTxTalkerInst = &pObj->avbTxTalkerInst[queId][chId];
            avbtp_talker_close(pAvbTxTalkerInst->avbTalkerHandle);
        }

        status = Utils_queDelete(&pObj->systemBufferQueue[queId]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }


    avbtp_close(pObj->avbHandle);

    Utils_bufDelete(&pObj->bufQue);
#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Tx: Delete Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbTxLink_drvPrintStatus(const AvbTxLink_Obj * pObj)
{

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "AVB Tx", (Bool)TRUE);

    return 0;
}


/* Nothing beyond this point */
