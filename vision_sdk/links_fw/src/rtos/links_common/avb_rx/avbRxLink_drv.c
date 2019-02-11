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
 * \file avbRxLink_drv.c
 *
 * \brief  This file communicates with driver for AvbRx link.
 *
 *         This file calls the driver commands and APIs for the application
 *         commands and APIs. All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (Nov 2013) : [KRB] First version
 * \version 0.1 (Feb 2014) : [CM]  AVB Link up .
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "avbRxLink_priv.h"

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
Int32 AvbRxLink_drvCallback(uint8_t *buf, uint32_t nPayloadSize,
                          avbtp_sd_info_t *rsdinfo,
                          void *cbdata, uint32_t channelNum, uint32_t buffIndex)
{
    AvbRxLink_Obj *pObj = (AvbRxLink_Obj*)cbdata;
    System_Buffer *pBuffer;
    System_BitstreamBuffer *bitstreamBuf;
    UInt32 status;

    AvbRxLink_ChObj  *pAvbRxChInst = &pObj->avbSrcObj[channelNum];
    app_buff_details_t bufD = &(pAvbRxChInst->avbBuffDescriptor.avbBufDetails);
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.notifyEventCount++;

    pBuffer = ((System_Buffer *)bufD->buffMetaData + buffIndex);
    bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

    if ( ((bufD->error & 1U) == 1U ) || /* Packet drop error */
         ((bufD->error & 2U) == 1U ) ) /* Out of sync packet error  */
    {
        *(bufD->buffState + buffIndex) = BUFF_EMPTY;
            bufD->error = 0u;
            linkStatsInfo->linkStats.inBufErrorCount++;
            linkStatsInfo->linkStats.chStats[channelNum].outBufDropCount[0]++;
        return SYSTEM_LINK_STATUS_SOK;
    }

    if(bufD->buffState[buffIndex] == BUFF_FULL)
    {
        bitstreamBuf->fillLength = nPayloadSize;
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
 * \brief
 *
 *  \param pObj         [IN] AvbRx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AvbRxLink_drvAllocFrames(AvbRxLink_ChObj* pAvbRxChInst, UInt32 numBufs)
{
    System_Buffer *pBuffer;
    System_BitstreamBuffer *bitstreamBuf;
    Int32 nFrame;
    void *pBaseAddr;

    app_buff_details_t bufArrayDesc = &(pAvbRxChInst->avbBuffDescriptor.avbBufDetails);

    pBaseAddr = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                               (pAvbRxChInst->bufferSize * numBufs), 0);
    UTILS_assert(pBaseAddr != NULL);

    bufArrayDesc->arrBuffPtr = &pAvbRxChInst->avbBuffDescriptor.avbBufPtr[0];
    bufArrayDesc->buffCount = numBufs;
    bufArrayDesc->buffSize = pAvbRxChInst->bufferSize;
    bufArrayDesc->channelNum = pAvbRxChInst->chID;
    bufArrayDesc->buffState = &pAvbRxChInst->avbBuffDescriptor.avbBufState[0];
    bufArrayDesc->dataLength = &pAvbRxChInst->avbBuffDescriptor.avbBufValidLen[0];

    for (nFrame = 0; nFrame < numBufs; nFrame++)
    {
        bitstreamBuf = &pAvbRxChInst->bitstreamBuf[nFrame];
        bitstreamBuf->bufAddr = (void *)((char*)pBaseAddr +
                                         (nFrame * pAvbRxChInst->bufferSize));
        bitstreamBuf->bufSize= pAvbRxChInst->bufferSize;
        bitstreamBuf->fillLength= 0;
        bitstreamBuf->flags = System_Bitstream_Buffer_Flag_Set_Is_Keyframe
                                        (bitstreamBuf->flags, 1);
        pBuffer = &pAvbRxChInst->buffers[nFrame];
        pBuffer->bufType = SYSTEM_BUFFER_TYPE_BITSTREAM;
        pBuffer->chNum = pAvbRxChInst->chID;
        pBuffer->payloadSize = sizeof(System_BitstreamBuffer);
        pBuffer->payload = bitstreamBuf;


        bufArrayDesc->arrBuffPtr[nFrame] = bitstreamBuf->bufAddr;
        bufArrayDesc->buffState[nFrame] = BUFF_EMPTY;
        bufArrayDesc->dataLength[nFrame] = 0;
    }

    bufArrayDesc->writePtr = bufArrayDesc->arrBuffPtr[0];

    bufArrayDesc->buffIndex = 0u;
    bufArrayDesc->buffMetaData = &pAvbRxChInst->buffers[0];
    bufArrayDesc->configBits = BUFF_NOTIFY_MJPEG_RST;

    return 0;
}

Void AvbRxLink_drvSetChannelInfo(AvbRxLink_Obj *pObj,UInt32 chNum)
{
    System_LinkChInfo *pQueChInfo;

    pQueChInfo = &pObj->info.queInfo[0].chInfo[chNum];

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pQueChInfo->flags,
                                            SYSTEM_BUFFER_TYPE_BITSTREAM);

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Bitstream_Format(pQueChInfo->flags,
                                    SYSTEM_BITSTREAM_CODING_TYPE_MJPEG);

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pQueChInfo->flags,
                                                SYSTEM_SF_PROGRESSIVE);

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(pQueChInfo->flags,
                                           SYSTEM_MT_NONTILEDMEM);

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(pQueChInfo->flags,0);

    pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pQueChInfo->flags,
                                                SYSTEM_DF_YUV420SP_UV);

    pQueChInfo->startX      = 0;
    pQueChInfo->startY      = 0;
    pQueChInfo->pitch[0]    = pObj->createArgs.width;
    pQueChInfo->pitch[1]    = pObj->createArgs.width;
    pQueChInfo->pitch[2]    = pObj->createArgs.width;

    pQueChInfo->width = pObj->createArgs.width;
    pQueChInfo->height = pObj->createArgs.height;


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
Int32 AvbRxLink_drvCreate(AvbRxLink_Obj * pObj,
                          const AvbRxLink_CreateParams * pPrm)
{
    Int32 status = 0;
    UInt32 lisIdx = 0;
    AvbRxLink_ChObj  *pAvbRxChInst;
    UInt32 queId = 0;

#ifdef SYSTEM_DEBUG_AVBRX
    Vps_printf(" AVBRX: Create in progress !!!\n");
#endif

    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    pObj->info.numQue = AVB_RX_LINK_MAX_OUT_QUE;

    status = Utils_bufCreate(&pObj->bufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    pObj->info.queInfo[queId].numCh = pPrm->numCameras;

    pObj->avbHandle = avbtp_open();
    UTILS_assert(pObj->avbHandle != NULL);

    for (lisIdx = 0; lisIdx < pPrm->numCameras; lisIdx++)
    {
        pAvbRxChInst = &pObj->avbSrcObj[lisIdx];
        pAvbRxChInst->chID = lisIdx;
        pAvbRxChInst->bufferSize = pPrm->buffSize;

        memcpy(pAvbRxChInst->streamId,
                pPrm->streamId[lisIdx],
                AVB_RX_LINK_STREAM_ID_LENGTH);

        memcpy(pAvbRxChInst->talkerMacAddr,
                pPrm->srcMacId[lisIdx],
                AVB_RX_LINK_STREAM_ID_LENGTH);

        app_buff_details_t bufArrayDesc = &(pAvbRxChInst->avbBuffDescriptor.avbBufDetails);

        pAvbRxChInst->listenerHandle = avbtp_listener_open(
                pObj->avbHandle,
                pAvbRxChInst->talkerMacAddr,
                &AvbRxLink_drvCallback,
                pObj,
                NULL,
                NULL,
                pAvbRxChInst->streamId);
        AvbRxLink_drvSetChannelInfo(pObj,lisIdx);
        status = AvbRxLink_drvAllocFrames(pAvbRxChInst,pPrm->numBufs);

        avbtp_submit_buffer(pAvbRxChInst->listenerHandle, bufArrayDesc);
    }

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "AVB_RX");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("AVBRX:",
                        pObj->memUsed,
                        UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_AVBRX
    Vps_printf(" AVBRX: Create Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Link callback for putting empty buffers into link input queue
 *
 *
 * \param  pObj           [IN] Avb link global handle
 * \param  pBufList       [IN] List of buffers to be kept back into link queue
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbRxLink_drvPutEmptyBuffers(AvbRxLink_Obj * pObj,
                                     System_BufferList * pBufList)
{
    System_Buffer *pBuffer;
    System_BitstreamBuffer *bitstreamBuf;
    UInt32 chID,idx,buffidx;
    AvbRxLink_ChObj  *pAvbRxChInst ;
    AvbRxLink_avbBuffDesc *bufDesc;

    if (pBufList->numBuf != 0)
    {
        for (idx = 0; idx < pBufList->numBuf; idx++)
        {
            pBuffer   = pBufList->buffers[idx];
            chID = pBuffer->chNum;

            pAvbRxChInst = &pObj->avbSrcObj[chID];
            bufDesc  = &(pAvbRxChInst->avbBuffDescriptor);

            bitstreamBuf = (System_BitstreamBuffer*)pBuffer->payload;

            for( buffidx = 0 ; buffidx < pObj->createArgs.numBufs;buffidx++)
            {
                if(bufDesc->avbBufPtr[buffidx] == bitstreamBuf->bufAddr)
                {
                    *(bufDesc->avbBufDetails.buffState + buffidx) = BUFF_EMPTY;
                    pObj->linkStatsInfo->linkStats.chStats[pAvbRxChInst->chID].inBufRecvCount++;
                    pObj->linkStatsInfo->linkStats.chStats[pAvbRxChInst->chID].inBufProcessCount++;
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
 * this call VIP AVBTP stack is ready to receive frames.
 *
 * \param  pObj           [IN] AVBTP link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbRxLink_drvStart(AvbRxLink_Obj * pObj)
{

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP RX: Start in progress !!!\n");
#endif

    avbtp_start(pObj->avbHandle);

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP RX: Start Done !!!\n");
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
Int32 AvbRxLink_drvStop(AvbRxLink_Obj * pObj)
{
#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP RX: Stop in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP RX: Stop Done !!!\n");
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
Int32 AvbRxLink_drvDelete(AvbRxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chNum = 0;
    AvbRxLink_ChObj  *pAvbRxChInst;
    System_BitstreamBuffer *bitstreamBuf;

#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP Rx: Delete in progress !!!\n");
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(chNum = 0 ; chNum < pObj->createArgs.numCameras; chNum++)
    {
        pAvbRxChInst = &pObj->avbSrcObj[chNum];
        bitstreamBuf = &pAvbRxChInst->bitstreamBuf[0];
        avbtp_listener_close(pAvbRxChInst->listenerHandle);

        Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                      bitstreamBuf->bufAddr,
                        pObj->createArgs.numBufs * pAvbRxChInst->bufferSize);

    }
    avbtp_close(pObj->avbHandle);
    Utils_bufDelete(&pObj->bufQue);
#ifdef SYSTEM_DEBUG_AVBTP
    Vps_printf(" AVBTP RX: Delete Done !!!\n");
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
Int32 AvbRxLink_drvPrintStatus(const AvbRxLink_Obj * pObj)
{

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "AVBTP RX", (Bool)TRUE);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Print AVB Rx link buffer statistics
 *
 *  \param pObj         [IN] AvbRx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AvbRxLink_printBufferStatus(AvbRxLink_Obj * pObj)
{
    Uint8 str[32];

    sprintf ((char *) str, "AVBRX");
    Utils_bufPrintStatus(str, &pObj->bufQue);
    return 0;
}



