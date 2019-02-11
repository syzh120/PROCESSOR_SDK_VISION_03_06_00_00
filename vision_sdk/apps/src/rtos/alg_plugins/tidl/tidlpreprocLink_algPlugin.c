/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 * \file tidlpreprocLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for algorithm plugin
 *         Link
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "tidlpreprocLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
/* YUV2RGB Conversion Matrices */
/* [3x3 'Y2R matrix'] + [3 'Offset'] + [1 'Y subtract'] */
Int16 gYuv2RgbMat[TIDLPREPROC_LINK_NUM_Y2R_MAT][13] =
{
    {0x0400,0x0000,0x0629,0x0400,0x00BB,0x01D5,0x0400,0x0742,0x0000,0x0CEC,0x0148,0x0C60,0x0000},  /* Limited Range */
    {0x04A8,0x0000,0x0662,0x04A8,0x0191,0x0340,0x04A8,0x0812,0x0000,0x0200,0x0200,0x0200,0x0010},  /* BT 624 */
    {0x04A8,0x0000,0x072C,0x04A8,0x00DA,0x0222,0x04A8,0x0873,0x0000,0x0200,0x0200,0x0200,0x0010},  /* BT 709 */
};
/**
 *******************************************************************************
 *
 * \brief Implementation of function to create()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreprocCreate(void *pObj,void *pCreateParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, bufIdx, index;
    AlgorithmLink_tidlpreprocObj *pAlgObj;
    AlgorithmLink_tidlpreprocCreateParams *pLinkCreatePrms;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_Buffer *pSystemBuffer;
    System_VideoFrameBuffer *pVidDataBuffer;
    System_LinkInfo prevLinkInfo;
    UInt32 prevLinkQId;
    Utils_DmaChCreateParams dmaParams;

    pAlgObj = (AlgorithmLink_tidlpreprocObj*)Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                        sizeof(AlgorithmLink_tidlpreprocObj),
                                        128);
    UTILS_assert(NULL != pAlgObj);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    /* Save the create parameters */
    memcpy(
        &pAlgObj->algLinkCreateParams,
        pCreateParams,
        sizeof(AlgorithmLink_tidlpreprocCreateParams));

    pLinkCreatePrms = &pAlgObj->algLinkCreateParams;

    /* Get the channel info from previous link */
    status = System_linkGetInfo(
                    pLinkCreatePrms->inQueParams.prevLinkId,
                    &prevLinkInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    prevLinkQId = pLinkCreatePrms->inQueParams.prevLinkQueId;
    memcpy(
        &pAlgObj->inChInfo,
        &prevLinkInfo.queInfo[prevLinkQId].chInfo[0],
        sizeof(System_LinkChInfo));

    switch(pLinkCreatePrms->procMode)
    {
        default:
        case TIDLPREPROC_LINK_PROCMODE_Y2R:
            /* The input is YUV420SP and pitch value is got from previous link */
            break;

        case TIDLPREPROC_LINK_PROCMODE_RGBPAD:
            /* The input is RGB planar hence the pitch should be same as width */
            pAlgObj->inChInfo.pitch[0] = pAlgObj->inChInfo.width;
            pAlgObj->inChInfo.pitch[1] = pAlgObj->inChInfo.width;
            pAlgObj->inChInfo.pitch[2] = pAlgObj->inChInfo.width;
            break;
    }

    pOutputQInfo = &pAlgObj->outputQInfo[0];
    for(queId = 0;queId < pLinkCreatePrms->numOutputQueues;queId++)
    {
        pOutputQInfo[queId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
        pOutputQInfo[queId].queInfo.numCh = 1;
        pOutputQInfo[queId].queInfo.chInfo[0].flags = \
                        System_Link_Ch_Info_Set_Flag_Data_Format(
                                pOutputQInfo[queId].queInfo.chInfo[0].flags,
                                SYSTEM_DF_BGR24_888);
        pOutputQInfo[queId].queInfo.chInfo[0].flags = \
                        System_Link_Ch_Info_Set_Flag_Buf_Type(
                                pOutputQInfo[queId].queInfo.chInfo[0].flags,
                                SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
        pOutputQInfo[queId].queInfo.chInfo[0].flags = \
                        System_Link_Ch_Info_Set_Flag_Scan_Format(
                                pOutputQInfo[queId].queInfo.chInfo[0].flags,
                                SYSTEM_SF_PROGRESSIVE);

        pOutputQInfo[queId].queInfo.chInfo[0].width = \
                    (pAlgObj->inChInfo.width + (2 * pLinkCreatePrms->outPad));
        pOutputQInfo[queId].queInfo.chInfo[0].height = \
                    (pAlgObj->inChInfo.height + (2 * pLinkCreatePrms->outPad));
        pOutputQInfo[queId].queInfo.chInfo[0].pitch[0] = \
                    pOutputQInfo[queId].queInfo.chInfo[0].width;
        pOutputQInfo[queId].queInfo.chInfo[0].pitch[1] = \
                    pOutputQInfo[queId].queInfo.chInfo[0].width;
        pOutputQInfo[queId].queInfo.chInfo[0].pitch[2] = \
                    pOutputQInfo[queId].queInfo.chInfo[0].width;
        pOutputQInfo[queId].queInfo.chInfo[0].startX = 0;
        pOutputQInfo[queId].queInfo.chInfo[0].startY = 0;
    }

    AlgorithmLink_queueInfoInit(
                        pObj,
                        0,
                        NULL,
                        pLinkCreatePrms->numOutputQueues,
                        pOutputQInfo);

    for(queId = 0;queId < pLinkCreatePrms->numOutputQueues;queId++)
    {
        for(bufIdx = 0;bufIdx < TIDLPREPROC_LINK_NUM_BUF_QUEUE;bufIdx++)
        {
            index = (queId * TIDLPREPROC_LINK_NUM_BUF_QUEUE) + bufIdx;
            pSystemBuffer = &pAlgObj->buffers[index];
            pVidDataBuffer = &pAlgObj->vidDataBuffers[index];

            pSystemBuffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
            pSystemBuffer->payload = pVidDataBuffer;
            pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
            pSystemBuffer->chNum = 0;

            pVidDataBuffer->metaBufSize = \
                (pOutputQInfo[queId].queInfo.chInfo[0].pitch[0] * 3U) * \
                    pOutputQInfo[queId].queInfo.chInfo[0].height;
            pVidDataBuffer->bufAddr[0] = Utils_memAlloc(
                                                UTILS_HEAPID_DDR_CACHED_SR,
                                                pVidDataBuffer->metaBufSize,
                                                128);
            UTILS_assert(NULL != pVidDataBuffer->bufAddr[0]);

            /* For planar RGB output format */
            pVidDataBuffer->bufAddr[1] = \
                (Void*)((UInt32)pVidDataBuffer->bufAddr[0] + \
                    (pOutputQInfo[queId].queInfo.chInfo[0].pitch[0] * \
                            pOutputQInfo[queId].queInfo.chInfo[0].height));
            pVidDataBuffer->bufAddr[2] = \
                (Void*)((UInt32)pVidDataBuffer->bufAddr[1] + \
                    (pOutputQInfo[queId].queInfo.chInfo[0].pitch[1] * \
                            pOutputQInfo[queId].queInfo.chInfo[0].height));

            /* Put empty buffer to empty queue */
            status = AlgorithmLink_putEmptyOutputBuffer(
                                            pObj,
                                            queId,          /* outputQId */
                                            pSystemBuffer);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }
    }

    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
                                            AlgorithmLink_getLinkId(pObj),
                                            "ALG_TIDLPREPROC");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    pAlgObj->isFirstFrameRecv = FALSE;
    pAlgObj->curQueId = 0;

    /* Y2R conversion matrix to use:
            TIDLPREPROC_Y2R_MAT_LIMITED_RANGE,
            TIDLPREPROC_Y2R_MAT_BT_624,
            TIDLPREPROC_Y2R_MAT_BT_709
    */
    pAlgObj->y2rMatIdx = TIDLPREPROC_Y2R_MAT_BT_624;

    /* Initialize DMA parameters and create object for Frame Dumping */
    Utils_DmaChCreateParams_Init(&dmaParams);
    status = Utils_dmaCreateCh(&pAlgObj->dumpFramesDmaObj, &dmaParams);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to delete()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreprocDelete(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, bufIdx, index;
    System_VideoFrameBuffer *pVidDataBuffer;
    AlgorithmLink_tidlpreprocObj *pAlgObj = \
            (AlgorithmLink_tidlpreprocObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    AlgorithmLink_tidlpreprocCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;

    for(queId = 0;queId < pLinkCreatePrms->numOutputQueues;queId++)
    {
        for(bufIdx = 0;bufIdx < TIDLPREPROC_LINK_NUM_BUF_QUEUE;bufIdx++)
        {
            index = (queId * TIDLPREPROC_LINK_NUM_BUF_QUEUE) + bufIdx;
            pVidDataBuffer = &pAlgObj->vidDataBuffers[index];

            status = Utils_memFree(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pVidDataBuffer->bufAddr[0],
                            pVidDataBuffer->metaBufSize);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }
    }

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete DMA obj */
    Utils_dmaDeleteCh(&pAlgObj->dumpFramesDmaObj);

    status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                    pAlgObj,
                    sizeof(AlgorithmLink_tidlpreprocObj));
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to process()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreprocProcess(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 ht, wd, bufIdx, uvIdx, uvRowIdx;
    System_BufferList inputBufList;
    System_BufferList bufListReturn;
    System_Buffer *pInSysBuf, *pOutSysBuf;
    System_VideoFrameBuffer *pInVidBuf, *pOutVidBuf;
    UInt8 *inAddrY, *inAddrUV;
    UInt8 *outAddrR, *outAddrG, *outAddrB;
    Int32 Y, U, V;
    Int32 R, G, B;
    TIDLPREPROC_Y2R_MAT y2rIdx;
    AlgorithmLink_tidlpreprocObj *pAlgObj = \
            (AlgorithmLink_tidlpreprocObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    AlgorithmLink_tidlpreprocCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;
    System_LinkStatistics *linkStatsInfo = pAlgObj->linkStatsInfo;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo = &pAlgObj->outputQInfo[0];
    Utils_DmaCopyFill2D dmaPrm;
    UInt8 *srcAddr;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;
        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                pLinkCreatePrms->inQueParams.prevLinkId,
                pLinkCreatePrms->inQueParams.prevLinkQueId,
                &inputBufList);

    if(inputBufList.numBuf > 0)
    {
        for (bufIdx = 0;bufIdx < inputBufList.numBuf;bufIdx++)
        {
            linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

            /*  Get the empty buffer from the current queue which should get
                the full buffer */
            status = AlgorithmLink_getEmptyOutputBuffer(
                                            pObj,
                                            pAlgObj->curQueId,  /* outputQId */
                                            0,                  /* channelId */
                                            &pOutSysBuf);
            if(SYSTEM_LINK_STATUS_SOK == status)
            {
                pInSysBuf = inputBufList.buffers[bufIdx];
                pInVidBuf = (System_VideoFrameBuffer*)pInSysBuf->payload;

                pOutVidBuf = (System_VideoFrameBuffer*)pOutSysBuf->payload;
                outAddrB = (UInt8*)pOutVidBuf->bufAddr[0];
                outAddrG = (UInt8*)pOutVidBuf->bufAddr[1];
                outAddrR = (UInt8*)pOutVidBuf->bufAddr[2];

                /* Provide the padding */
                outAddrB += \
                    (pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[0] * pLinkCreatePrms->outPad) +
                        pLinkCreatePrms->outPad;
                outAddrG += \
                    (pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[1] * pLinkCreatePrms->outPad) +
                        pLinkCreatePrms->outPad;
                outAddrR += \
                    (pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[2] * pLinkCreatePrms->outPad) +
                        pLinkCreatePrms->outPad;

                switch(pLinkCreatePrms->procMode)
                {
                    default:
                    case TIDLPREPROC_LINK_PROCMODE_Y2R:

                        inAddrY = (UInt8*)pInVidBuf->bufAddr[0];
                        inAddrUV = (UInt8*)pInVidBuf->bufAddr[1];

                        Cache_inv(
                            pInVidBuf->bufAddr[0],
                            (pAlgObj->inChInfo.pitch[0] * pAlgObj->inChInfo.height),
                            Cache_Type_ALL,
                            TRUE);

                        Cache_inv(
                            pInVidBuf->bufAddr[1],
                            (pAlgObj->inChInfo.pitch[1] * (pAlgObj->inChInfo.height >> 1)),
                            Cache_Type_ALL,
                            TRUE);

                        inAddrY += \
                            ((pAlgObj->inChInfo.startY * pAlgObj->inChInfo.pitch[0]) + pAlgObj->inChInfo.startX);
                        inAddrUV += \
                            (((pAlgObj->inChInfo.startY >> 1) * pAlgObj->inChInfo.pitch[1]) + pAlgObj->inChInfo.startX);

                        y2rIdx = pAlgObj->y2rMatIdx;

                        for (ht = 0;ht < pAlgObj->inChInfo.height;ht++)
                        {
                            uvIdx = ((ht >> 1) * pAlgObj->inChInfo.pitch[1]);

                            for (wd = 0;wd < pAlgObj->inChInfo.width;wd++)
                            {
                                uvRowIdx = ((wd >> 1) << 1);

                                /* NV12 format has U first then V */
                                U = *((UInt8*)inAddrUV + uvIdx + uvRowIdx);
                                V = *((UInt8*)inAddrUV + uvIdx + uvRowIdx + 1);
                                Y = *((UInt8*)inAddrY++);

                                Y = \
                                    ((Y - gYuv2RgbMat[y2rIdx][12]) * \
                                                        gYuv2RgbMat[y2rIdx][0]);

                                R = \
                                    (Y + (gYuv2RgbMat[y2rIdx][2] * (V - 128)) + \
                                                        gYuv2RgbMat[y2rIdx][9]) >> 10;
                                if(R < 0) R = 0;
                                if(R > 0xFF) R = 0xFF;

                                G = \
                                    (Y - (gYuv2RgbMat[y2rIdx][4] * (U - 128)) - \
                                        (gYuv2RgbMat[y2rIdx][5] * (V - 128)) + \
                                                gYuv2RgbMat[y2rIdx][10]) >> 10;
                                if(G < 0) G = 0;
                                if(G > 0xFF) G = 0xFF;

                                B = \
                                    (Y + (gYuv2RgbMat[y2rIdx][7] * (U - 128)) + \
                                                    gYuv2RgbMat[y2rIdx][11]) >> 10;
                                if(B < 0) B = 0;
                                if(B > 0xFF) B = 0xFF;

                                *((UInt8*)outAddrR + wd) = R;
                                *((UInt8*)outAddrG + wd) = G;
                                *((UInt8*)outAddrB + wd) = B;
                            }

                            inAddrY += (pAlgObj->inChInfo.pitch[0] - pAlgObj->inChInfo.width);

                            /* Provide the line padding */
                            outAddrR += pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[0];
                            outAddrG += pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[1];
                            outAddrB += pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[2];
                        }

                        break;

                    case TIDLPREPROC_LINK_PROCMODE_RGBPAD:

                        /* PAD B plane */
                        srcAddr = (UInt8*)pInVidBuf->bufAddr[0];
                        dmaPrm.dataFormat = SYSTEM_DF_RAW08;
                        dmaPrm.destAddr[0] = (Ptr)(outAddrB);
                        dmaPrm.destAddr[1] = NULL;
                        dmaPrm.destPitch[0] = pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[0];
                        dmaPrm.destPitch[1] = 0;
                        dmaPrm.destStartX = 0;
                        dmaPrm.destStartY = 0;
                        dmaPrm.width = pAlgObj->inChInfo.width;
                        dmaPrm.height = pAlgObj->inChInfo.height;
                        dmaPrm.srcAddr[0] = (Ptr)(srcAddr);
                        dmaPrm.srcAddr[1] = NULL;
                        dmaPrm.srcPitch[0] = pAlgObj->inChInfo.pitch[0];
                        dmaPrm.srcPitch[1] = 0;
                        dmaPrm.srcStartX = 0;
                        dmaPrm.srcStartY = 0;

                        status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
                        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                        /* PAD G plane */
                        srcAddr += (pAlgObj->inChInfo.pitch[0] * pAlgObj->inChInfo.height);
                        dmaPrm.dataFormat = SYSTEM_DF_RAW08;
                        dmaPrm.destAddr[0] = (Ptr)(outAddrG);
                        dmaPrm.destAddr[1] = NULL;
                        dmaPrm.destPitch[0] = pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[1];
                        dmaPrm.destPitch[1] = 0;
                        dmaPrm.destStartX = 0;
                        dmaPrm.destStartY = 0;
                        dmaPrm.width = pAlgObj->inChInfo.width;
                        dmaPrm.height = pAlgObj->inChInfo.height;
                        dmaPrm.srcAddr[0] = (Ptr)(srcAddr);
                        dmaPrm.srcAddr[1] = NULL;
                        dmaPrm.srcPitch[0] = pAlgObj->inChInfo.pitch[0];
                        dmaPrm.srcPitch[1] = 0;
                        dmaPrm.srcStartX = 0;
                        dmaPrm.srcStartY = 0;

                        status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
                        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                        /* PAD R plane */
                        srcAddr += (pAlgObj->inChInfo.pitch[0] * pAlgObj->inChInfo.height);
                        dmaPrm.dataFormat = SYSTEM_DF_RAW08;
                        dmaPrm.destAddr[0] = (Ptr)(outAddrR);
                        dmaPrm.destAddr[1] = NULL;
                        dmaPrm.destPitch[0] = pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[2];
                        dmaPrm.destPitch[1] = 0;
                        dmaPrm.destStartX = 0;
                        dmaPrm.destStartY = 0;
                        dmaPrm.width = pAlgObj->inChInfo.width;
                        dmaPrm.height = pAlgObj->inChInfo.height;
                        dmaPrm.srcAddr[0] = (Ptr)(srcAddr);
                        dmaPrm.srcAddr[1] = NULL;
                        dmaPrm.srcPitch[0] = pAlgObj->inChInfo.pitch[0];
                        dmaPrm.srcPitch[1] = 0;
                        dmaPrm.srcStartX = 0;
                        dmaPrm.srcStartY = 0;

                        status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
                        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                        break;
                }

                pOutSysBuf->frameId = pInSysBuf->frameId;
                pOutSysBuf->srcTimestamp = pInSysBuf->srcTimestamp;
                pOutSysBuf->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                Cache_wb(
                    pOutVidBuf->bufAddr[0],
                    (pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[0] * pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].height),
                    Cache_Type_ALL,
                    TRUE);

                Cache_wb(
                    pOutVidBuf->bufAddr[1],
                    (pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[1] * pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].height),
                    Cache_Type_ALL,
                    TRUE);

                Cache_wb(
                    pOutVidBuf->bufAddr[2],
                    (pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].pitch[2] * pOutputQInfo[pAlgObj->curQueId].queInfo.chInfo[0].height),
                    Cache_Type_ALL,
                    TRUE);

                Utils_updateLatency(
                            &linkStatsInfo->linkLatency,
                            pOutSysBuf->linkLocalTimestamp);
                Utils_updateLatency(
                            &linkStatsInfo->srcToLinkLatency,
                            pOutSysBuf->srcTimestamp);

                linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

                status = AlgorithmLink_putFullOutputBuffer(
                                                    pObj,
                                                    pAlgObj->curQueId,  /* outputQId */
                                                    pOutSysBuf);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                /* Notify the next link */
                System_sendLinkCmd(
                    pLinkCreatePrms->outQueParams[pAlgObj->curQueId].nextLink,
                    SYSTEM_CMD_NEW_DATA,
                    NULL);

                bufListReturn.numBuf = 1;
                bufListReturn.buffers[0] = pOutSysBuf;
                status = AlgorithmLink_releaseOutputBuffer(
                                                   pObj,
                                                   pAlgObj->curQueId,   /* outputQId */
                                                   &bufListReturn);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
            }
            else
            {
                linkStatsInfo->linkStats.chStats[0].inBufDropCount++;
                linkStatsInfo->linkStats.chStats[0].outBufDropCount[0]++;
            }

            pAlgObj->curQueId = \
                    (pAlgObj->curQueId + 1) % pLinkCreatePrms->numOutputQueues;
        }

        System_putLinksEmptyBuffers(
                        pLinkCreatePrms->inQueParams.prevLinkId,
                        pLinkCreatePrms->inQueParams.prevLinkQueId,
                        &inputBufList);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to print statistics()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreprocPrintStatistics(void *pObj,AlgorithmLink_tidlpreprocObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(
                    &pAlgObj->linkStatsInfo->linkStats,
                    "ALG_YUV2RGB",
                    TRUE);

    Utils_printLatency(
                    "ALG_YUV2RGB",
                    &pAlgObj->linkStatsInfo->linkLatency,
                    &pAlgObj->linkStatsInfo->srcToLinkLatency,
                    TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to control()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreprocControl(void *pObj,void *pControlParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_tidlpreprocObj *pAlgObj;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;

    pAlgObj = (AlgorithmLink_tidlpreprocObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */

    switch(pAlgLinkControlPrm->controlCmd)
    {
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_tidlpreprocPrintStatistics(pObj, pAlgObj);
            break;

        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to stop()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreprocStop(void *pObj)
{
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of gAlign algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreproc_initPlugin(Void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate = AlgorithmLink_tidlpreprocCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = AlgorithmLink_tidlpreprocProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = AlgorithmLink_tidlpreprocControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop = AlgorithmLink_tidlpreprocStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete = AlgorithmLink_tidlpreprocDelete;

    algId = ALGORITHM_LINK_A15_ALG_TIDLPREPROC;
    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of gAlign algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpreproc_initPluginIpu(Void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate = AlgorithmLink_tidlpreprocCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = AlgorithmLink_tidlpreprocProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = AlgorithmLink_tidlpreprocControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop = AlgorithmLink_tidlpreprocStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete = AlgorithmLink_tidlpreprocDelete;

    algId = ALGORITHM_LINK_IPU_ALG_TIDLPREPROC;
    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

