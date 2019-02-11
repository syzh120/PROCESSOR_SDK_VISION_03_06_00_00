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
 * \file tfdtpRxLink_drv.c
 *
 * \brief  This file communicates with driver for TfdtpRx link.
 *
 *         This file calls the driver commands and APIs for the application
 *         commands and APIs. All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (Nov 2016) : [PYJ] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "tfdtpRxLink_priv.h"

#define SYSTEM_DEBUG_TFDTPRX 1

Int32 TfdtpRx_populateQueue(TfdtpRxLink_Obj * pObj,
                                TfdtpRxLink_ChObj * pChObj,
                                UInt32 numBufs);
Int32 TfdtpRx_allocAndQueueVideoFrames(TfdtpRxLink_Obj * pObj,
                                           TfdtpRxLink_ChObj *pChObj,
                                           UInt32 channelID);
Int32 TfdtpRx_deleteVideoFrames(TfdtpRxLink_Obj * pObj, TfdtpRxLink_ChObj *pChObj);

Int32 TfdtpRxLink_drvCallback( tfdtp_rx_buf_handle_t appBuffh, void *cbdata, uint32_t channelNum);

/**
 *******************************************************************************
 *
 * \brief Callback function from driver to application
 *
 * CallBack Function registered in NSP, ITs called on every new
 * frame received at the channel. Frame is further passed to next component
 *
 * \param  pPayload    buf - Buffer with mjpeg data
 * \param  appBuffh     app_rx_buf_handle_t *appBuffh - Handle to rx app buffer
 *
 * \param  pCbData     void *pCbData - callback function data.
 *
 * \param  nChanNum    channelNum - Channel Number of the frame received
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_drvCallback( tfdtp_rx_buf_handle_t appBuffh, void *cbdata, uint32_t channelNum)
{
    TfdtpRxLink_Obj *pObj = (TfdtpRxLink_Obj*)cbdata;
    System_Buffer *pBuffer;
    System_BitstreamBuffer *bitstreamBuf;
    Int32 status;

    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.notifyEventCount++;

    pBuffer = ((System_Buffer *)appBuffh->bufMetaData);
    bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

    if (((appBuffh->error & 1U) == 1U ) || /* Packet drop error */
        ((appBuffh->error & 2U) == 1U )) /* Out of sync packet error  */
    {
        appBuffh->bufState = BUFF_EMPTY;
        appBuffh->error = 0u;
        linkStatsInfo->linkStats.inBufErrorCount++;
        linkStatsInfo->linkStats.chStats[channelNum].outBufDropCount[0]++;
    }

    if(appBuffh->bufState == BUFF_FULL)
    {
        bitstreamBuf->fillLength = appBuffh->dataLength;
        pBuffer->srcTimestamp = Utils_getCurGlobalTimeInUsec();
        pBuffer->frameId = 0;
        pBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
        status = Utils_bufPutFullBuffer(&pObj->bufQue, pBuffer);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        linkStatsInfo->linkStats.newDataCmdCount++;
        linkStatsInfo->linkStats.chStats[channelNum].outBufCount[0]++;

        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                            SYSTEM_CMD_NEW_DATA, NULL);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Create API for link. Link gets created using this function.
 *
 * Creates driver instance, sets up link data structure, allocates and
 * queue frames to driver. Make link and driver ready for operation.
 *
 * \param  pObj     [IN] TFDTP link global handle
 * \param  pPrm     [IN] TFDTP link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_drvCreate(TfdtpRxLink_Obj * pObj,
                            const TfdtpRxLink_CreateParams * pPrm)
{
    Int32 status = 0;
    UInt32 lisIdx = 0;
    TfdtpRxLink_ChObj  *pTfdtpRxChInst;
    TFDTP_RxChOpenPrm_t tfdtpRxChOpenPrms;

#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTPRX: Create in progress !!!\n");
#endif

    /*
    * Validating the create params
    * TODO: Extend to validate width, height and pitch params also
    */
    UTILS_assert(pPrm->outQueInfo.numCh <= TFDTP_SRC_LINK_MAX_CH);

    /*
    *Copying Create arguments into Link object from the parametes passed by app
    */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* Tfdtp Src link has a single queue.
     * Initializing it.
     */
    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    pObj->linkInfo.numQue = TFDTP_RX_LINK_MAX_OUT_QUE;
    pObj->linkInfo.queInfo[0].numCh = pPrm->outQueInfo.numCh;

    for (lisIdx = 0; lisIdx < pPrm->outQueInfo.numCh; lisIdx++)
    {
        memcpy(&pObj->linkInfo.queInfo[0].chInfo[lisIdx],
               &pPrm->outQueInfo.chInfo[lisIdx],
               sizeof(System_LinkChInfo));

        UTILS_assert(pPrm->numBufs <=
                        TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT);

    }

    status = Utils_bufCreate(&pObj->bufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Initialize TFDTP with device IP address */
    pObj->tfdtpHandle = Network_tfdtpOpen();
    UTILS_assert(pObj->tfdtpHandle != NULL);

    memset(&tfdtpRxChOpenPrms, 0, sizeof(tfdtpRxChOpenPrms));
    tfdtpRxChOpenPrms.rcv_cb_fxn  = &TfdtpRxLink_drvCallback;
    for (lisIdx = 0; lisIdx < pPrm->numChannels; lisIdx++)
    {
        pTfdtpRxChInst = &pObj->tfdtpSrcObj[lisIdx];
        pTfdtpRxChInst->chID = lisIdx;

        tfdtp_rx_buf_details_t bufArrayDesc = &(pTfdtpRxChInst->tfdtpBuffDescriptor.tfdtpBufDetails);

        tfdtpRxChOpenPrms.rcv_cb_data = pObj;
        tfdtpRxChOpenPrms.channelId = NETWORK_TFDTP_TX_CHANNEL_NUM;

        pTfdtpRxChInst->rxChannelHandle =
                        TFDTP_openRxChannel( pObj->tfdtpHandle, &tfdtpRxChOpenPrms);
        UTILS_assert(NULL != pTfdtpRxChInst->rxChannelHandle);

        /*Populate the queue with buffers*/
        status = TfdtpRx_populateQueue(pObj,
                                           pTfdtpRxChInst, pPrm->numBufs);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        /* Submit buffers to TFDTP channels */
        status = TFDTP_submitRxBuf(pTfdtpRxChInst->rxChannelHandle, bufArrayDesc);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "TFDTP_RX");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("TFDTPRX:",
                        pObj->memUsed,
                        UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTPRX: Create Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Link callback for putting empty buffers into link input queue
 *
 *
 * \param  pObj           [IN] Tfdtp link global handle
 * \param  pBufList       [IN] List of buffers to be kept back into link queue
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_drvPutEmptyBuffers(TfdtpRxLink_Obj * pObj,
                                     System_BufferList * pBufList)
{
    System_Buffer *pBuffer;
    System_BitstreamBuffer *bitstreamBuf;
    UInt32 chID,idx,buffidx;
    TfdtpRxLink_ChObj  *pTfdtpRxChInst ;
    TfdtpRxLink_tfdtpBuffDesc *bufDesc;

    if (pBufList->numBuf != 0)
    {
        for (idx = 0; idx < pBufList->numBuf; idx++)
        {
            pBuffer   = pBufList->buffers[idx];
            chID = pBuffer->chNum;

            pTfdtpRxChInst = &pObj->tfdtpSrcObj[chID];
            bufDesc  = &(pTfdtpRxChInst->tfdtpBuffDescriptor);

            bitstreamBuf = (System_BitstreamBuffer*)pBuffer->payload;

            for( buffidx = 0 ; buffidx < pObj->createArgs.numBufs;buffidx++)
            {
                if(bufDesc->tfdtpBufDetails.appBufArray[buffidx].bufPtr == bitstreamBuf->bufAddr)
                {
                    bufDesc->tfdtpBufDetails.appBufArray[buffidx].bufState = BUFF_EMPTY;
                    pObj->linkStatsInfo->linkStats.chStats[pTfdtpRxChInst->chID].inBufRecvCount++;
                    pObj->linkStatsInfo->linkStats.chStats[pTfdtpRxChInst->chID].inBufProcessCount++;
                    break;
                }
            }
        }
    }

    pObj->linkStatsInfo->linkStats.putEmptyBufCount++;
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to start the link.
 *
 * This function calls the driver function to start the driver. As a part of
 * this call VIP TFDTP Rx stack is ready to receive frames.
 *
 * \param  pObj           [IN] TFDTP Rx link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_drvStart(TfdtpRxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTP Rx: Start in progress !!!\n");
#endif

    status = TFDTP_start(pObj->tfdtpHandle);

#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTP Rx: Start Done !!!\n");
#endif

    return status;
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
Int32 TfdtpRxLink_drvStop(TfdtpRxLink_Obj * pObj)
{
#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTP Rx: Stop in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTP Rx: Stop Done !!!\n");
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
Int32 TfdtpRx_deleteVideoFrames(TfdtpRxLink_Obj * pObj, TfdtpRxLink_ChObj *pChObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, size;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType;
    System_VideoDataFormat dataFormat;

    /* Tfdtp Src - there is a single queue */
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
            /* Not supported */
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
                        pChObj->videoFrames[0].bufAddr[0],
                        size * pChObj->numBufs);
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
                        pChObj->videoFrames[0].bufAddr[0],
                        size * pChObj->numBufs);
                    break;

                default:
                    status = SYSTEM_LINK_STATUS_EFAIL;
                    break;
            }

        }
        else
        {
            UTILS_assert((bufferType == SYSTEM_BUFFER_TYPE_BITSTREAM) ||
                         (bufferType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME));
        }
    }

    return status;
}

Int32 TfdtpRxLink_drvDelete(TfdtpRxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chNum = 0;
    TfdtpRxLink_ChObj  *pTfdtpRxChInst;

#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTP Rx: Delete in progress !!!\n");
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(chNum = 0 ; chNum < pObj->createArgs.numChannels; chNum++)
    {
        pTfdtpRxChInst = &pObj->tfdtpSrcObj[chNum];
        TFDTP_closeRxChannel(pTfdtpRxChInst->rxChannelHandle);
        TfdtpRx_deleteVideoFrames(pObj, pTfdtpRxChInst);
    }

    /* Close TFDTP */
    Network_tfdtpClose(pObj->tfdtpHandle);

    Utils_bufDelete(&pObj->bufQue);
#ifdef SYSTEM_DEBUG_TFDTPRX
    Vps_printf(" TFDTP Rx: Delete Done !!!\n");
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
Int32 TfdtpRxLink_drvPrintStatus(TfdtpRxLink_Obj * pObj)
{

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "TFDTP Rx", (Bool) TRUE);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Print TFDTP Rx link buffer statistics
 *
 *  \param pObj         [IN] TfdtpRx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_printBufferStatus(TfdtpRxLink_Obj * pObj)
{
    Uint8 str[32];

    snprintf ((char *) str,32U, "TFDTPRX");

    Utils_bufPrintStatus(str, &pObj->bufQue);
    return 0;
}

/**
 ******************************************************************************
 *
 * \brief Polulates the queue with buffers for Tfdtp source link
 *
 *  \param pObj         [IN] Tfdtp Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 TfdtpRx_populateQueue(TfdtpRxLink_Obj * pObj,
                                TfdtpRxLink_ChObj * pChObj,
                                UInt32 numBufs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;
    System_LinkChInfo *pChInfo;
    System_BufferType bufferType;

    /*
    * All buffers are contiguous Initializing them here.
    */
    memset(&pChObj->buffers, 0,
                sizeof(System_Buffer)*TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT);
    memset(&pChObj->videoFrames, 0,
                sizeof(System_VideoFrameBuffer)*TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT);
    memset(&pChObj->bitstreamBuf, 0,
                sizeof(System_BitstreamBuffer)*TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT);

    pChObj->numBufs = numBufs;

    /*
    * Tfdtp Src link has a single output queue. Hence index 0 is used for queInfo
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
                /* Not implemented */
                break;
            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                status = TfdtpRx_allocAndQueueVideoFrames(pObj, pChObj, chId);
                break;
            default:
                UTILS_assert(
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
 * \brief Allocate and Queue Video frames for a channel for Tfdtp source link
 *
 *  \param pObj             [IN] Tfdtp Source link object
 *  \param channelID    [IN] Channel Number for which frames need to be queued
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 TfdtpRx_allocAndQueueVideoFrames(TfdtpRxLink_Obj * pObj,
                                           TfdtpRxLink_ChObj *pChObj,
                                           UInt32 channelID)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 frameId, frameSize, numBufs;
    System_LinkChInfo *pChInfo;
    System_Buffer *buffer;
    System_VideoFrameBuffer *videoFrame;
    System_VideoDataFormat dataFormat;
    void *pBaseAddr;
    tfdtp_rx_buf_details_t bufArrayDesc =
                         &(pChObj->tfdtpBuffDescriptor.tfdtpBufDetails);

    numBufs = pChObj->numBufs;
    bufArrayDesc->bufCount = numBufs;
    bufArrayDesc->channelNum = pChObj->chID;

    /*
    * Tfdtp Src link has a single output queue
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
               frameSize * numBufs,
               VPS_BUFFER_ALIGNMENT);
            UTILS_assert(pBaseAddr != NULL);

            for(frameId = 0;
                frameId < numBufs;
                frameId++)
            {
                videoFrame = &pChObj->videoFrames[frameId];

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Increment is within allocated size of
                 * frameSize * pChObj->numBufs
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
                buffer = &pChObj->buffers[frameId];
                buffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                buffer->chNum = channelID;
                buffer->payloadSize = sizeof(System_VideoFrameBuffer);
                buffer->payload = videoFrame;

                /* Initialize TFDTP buffer descriptor using video frame buffer */
                bufArrayDesc->bufSize = frameSize;
                bufArrayDesc->appBufArray[frameId].bufState = BUFF_EMPTY;
                bufArrayDesc->appBufArray[frameId].bufPtr = videoFrame->bufAddr[0];
                bufArrayDesc->appBufArray[frameId].dataLength = 0;
                bufArrayDesc->appBufArray[frameId].bufMetaData = buffer;
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
               frameSize * numBufs,
               VPS_BUFFER_ALIGNMENT);
            UTILS_assert(pBaseAddr != NULL);

            for(frameId = 0;
                frameId < numBufs;
                frameId++)
            {
                videoFrame = &pChObj->videoFrames[frameId];

                videoFrame->bufAddr[0] = pBaseAddr;
                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Increment is within allocated size of
                 * frameSize * pChObj->numBufs
                 */
                pBaseAddr = (void *)((char*)pBaseAddr + frameSize);

                memcpy(&videoFrame->chInfo, pChInfo,sizeof(System_LinkChInfo));

                /* 0 indicates progressive*/
                videoFrame->flags = System_Video_Frame_Set_Flag_Fid(videoFrame->flags, 0U);

                /*
                * Initialize System Buffer using the Video frame information
                * and associate the System_VideoFrameBuffer as its payload.
                */
                buffer = &pChObj->buffers[frameId];
                buffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                buffer->chNum = channelID;
                buffer->payloadSize = sizeof(System_VideoFrameBuffer);
                buffer->payload = videoFrame;

                /* Initialize TFDTP buffer descriptor using video frame buffer */
                bufArrayDesc->bufSize = frameSize;
                bufArrayDesc->appBufArray[frameId].bufState = BUFF_EMPTY;
                bufArrayDesc->appBufArray[frameId].bufPtr = videoFrame->bufAddr[0];
                bufArrayDesc->appBufArray[frameId].dataLength = 0;
                bufArrayDesc->appBufArray[frameId].bufMetaData = buffer;
            }
            break;

        default:
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
    }

    return status;
}



