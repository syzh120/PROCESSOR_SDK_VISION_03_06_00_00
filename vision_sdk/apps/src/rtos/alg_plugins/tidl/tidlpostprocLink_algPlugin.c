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
 * \file tidlpostprocLink_algPlugin.c
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
#include "tidlpostprocLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Implementation of function to create()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlpostprocCreate(void *pObj,void *pCreateParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, chId, bufIdx;
    AlgorithmLink_tidlpostprocObj *pAlgObj;
    AlgorithmLink_tidlpostprocCreateParams *pLinkCreatePrms;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_Buffer *pSystemBuffer;
    System_VideoFrameBuffer *pVidDataBuffer;
    Utils_DmaChCreateParams dmaParams;
    System_LinkInfo prevLinkInfo;
    UInt32 prevLinkQId;

    pAlgObj = (AlgorithmLink_tidlpostprocObj*)Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                        sizeof(AlgorithmLink_tidlpostprocObj),
                                        128);
    UTILS_assert(NULL != pAlgObj);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    /* Save the create parameters */
    memcpy(
        &pAlgObj->algLinkCreateParams,
        pCreateParams,
        sizeof(AlgorithmLink_tidlpostprocCreateParams));

    pLinkCreatePrms = &pAlgObj->algLinkCreateParams;

    for (queId = 0;queId < pLinkCreatePrms->numInputQueues;queId++)
    {
        /* Get the channel info from previous link */
        status = System_linkGetInfo(
                        pLinkCreatePrms->inQueParams[queId].prevLinkId,
                        &prevLinkInfo);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        prevLinkQId = pLinkCreatePrms->inQueParams[queId].prevLinkQueId;

        for(chId = 0;chId < prevLinkInfo.queInfo[prevLinkQId].numCh;chId++)
        {
            memcpy(
                &pAlgObj->inChInfo[queId][chId],
                &prevLinkInfo.queInfo[prevLinkQId].chInfo[chId],
                sizeof(System_LinkChInfo));
        }
    }

    /* Only RGB888 and RGB565 formats supported */
    switch(pLinkCreatePrms->outDataFormat)
    {
        default:
        case SYSTEM_DF_RGB24_888:
        case SYSTEM_DF_BGR24_888:
            pAlgObj->outBytesPerPixel = 3;
            break;
        case SYSTEM_DF_RGB16_565:
        case SYSTEM_DF_BGR16_565:
            pAlgObj->outBytesPerPixel = 2;
            break;
        case SYSTEM_DF_YUV420SP_UV:
        case SYSTEM_DF_YUV420SP_VU:
            pAlgObj->outBytesPerPixel = 1;
            break;
    }

    pOutputQInfo = &pAlgObj->outputQInfo;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    /* The following out queue info will be used by the next link */
    pOutputQInfo->queInfo.numCh = 1;
    pOutputQInfo->queInfo.chInfo[0].flags = \
                    System_Link_Ch_Info_Set_Flag_Data_Format(
                            pOutputQInfo->queInfo.chInfo[0].flags,
                            pLinkCreatePrms->outDataFormat);
    pOutputQInfo->queInfo.chInfo[0].flags = \
                    System_Link_Ch_Info_Set_Flag_Buf_Type(
                            pOutputQInfo->queInfo.chInfo[0].flags,
                            SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
    pOutputQInfo->queInfo.chInfo[0].flags = \
                    System_Link_Ch_Info_Set_Flag_Scan_Format(
                            pOutputQInfo->queInfo.chInfo[0].flags,
                            SYSTEM_SF_PROGRESSIVE);
    pOutputQInfo->queInfo.chInfo[0].pitch[0] = \
                    (pLinkCreatePrms->outWidth * pAlgObj->outBytesPerPixel);
    pOutputQInfo->queInfo.chInfo[0].pitch[1] = \
                    pOutputQInfo->queInfo.chInfo[0].pitch[0];
    pOutputQInfo->queInfo.chInfo[0].pitch[2] = \
                    pOutputQInfo->queInfo.chInfo[0].pitch[0];
    pOutputQInfo->queInfo.chInfo[0].startX = 0;
    pOutputQInfo->queInfo.chInfo[0].startY = 0;
    pOutputQInfo->queInfo.chInfo[0].width = pLinkCreatePrms->outWidth;
    pOutputQInfo->queInfo.chInfo[0].height = pLinkCreatePrms->outHeight;

    pAlgObj->inWidth = (pLinkCreatePrms->outWidth + (2 * pLinkCreatePrms->inPad));
    pAlgObj->inHeight = (pLinkCreatePrms->outHeight + (2 * pLinkCreatePrms->inPad));

    AlgorithmLink_queueInfoInit(
                        pObj,
                        0,
                        NULL,
                        1,
                        pOutputQInfo);

    for(bufIdx = 0;bufIdx < TIDLPOSTPROC_LINK_NUM_BUF_QUEUE;bufIdx++)
    {
        pSystemBuffer = &pAlgObj->buffers[bufIdx];
        pVidDataBuffer = &pAlgObj->vidDataBuffers[bufIdx];

        pSystemBuffer->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->payload = pVidDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
        pSystemBuffer->chNum = 0;

        pVidDataBuffer->metaBufSize = \
            (pOutputQInfo->queInfo.chInfo[0].pitch[0] * pLinkCreatePrms->outHeight);

        if((SYSTEM_DF_YUV420SP_UV == pLinkCreatePrms->outDataFormat) ||
           (SYSTEM_DF_YUV420SP_VU == pLinkCreatePrms->outDataFormat))
        {
            pVidDataBuffer->metaBufSize += \
                (pOutputQInfo->queInfo.chInfo[0].pitch[1] * pLinkCreatePrms->outHeight/2);
        }

        pVidDataBuffer->bufAddr[0] = Utils_memAlloc(
                                            UTILS_HEAPID_DDR_CACHED_SR,
                                            pVidDataBuffer->metaBufSize,
                                            128);
        UTILS_assert(NULL != pVidDataBuffer->bufAddr[0]);

        /* UV plane address */
        pVidDataBuffer->bufAddr[1] = \
            pVidDataBuffer->bufAddr[0] + \
                (pOutputQInfo->queInfo.chInfo[0].pitch[0] * pLinkCreatePrms->outHeight);

        /* Put empty buffer to empty queue */
        status = AlgorithmLink_putEmptyOutputBuffer(
                                        pObj,
                                        0,          /* outputQId */
                                        pSystemBuffer);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
                                            AlgorithmLink_getLinkId(pObj),
                                            "ALG_TIDLPOSTPROC");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    pAlgObj->isFirstFrameRecv = FALSE;

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
Int32 AlgorithmLink_tidlpostprocDelete(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufIdx;
    System_VideoFrameBuffer *pVidDataBuffer;
    AlgorithmLink_tidlpostprocObj *pAlgObj = \
            (AlgorithmLink_tidlpostprocObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);

    for(bufIdx = 0;bufIdx < TIDLPOSTPROC_LINK_NUM_BUF_QUEUE;bufIdx++)
    {
        pVidDataBuffer = &pAlgObj->vidDataBuffers[bufIdx];

        status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pVidDataBuffer->bufAddr[0],
                        pVidDataBuffer->metaBufSize);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete DMA obj */
    Utils_dmaDeleteCh(&pAlgObj->dumpFramesDmaObj);

    status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                    pAlgObj,
                    sizeof(AlgorithmLink_tidlpostprocObj));
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
Int32 AlgorithmLink_tidlpostprocProcess(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 ht, wd, bufIdx, queId;
    System_BufferList inputBufList;
    System_BufferList bufListReturn;
    System_Buffer *pInSysBuf, *pOutSysBuf;
    System_VideoFrameBuffer *pOutVidBuf;
    System_MetaDataBuffer *pInMetaBuf;
    System_VideoFrameCompositeBuffer *pCompBuf;
    UInt8 inData, *inAddr, *outAddr888, *paletteAddr;
    UInt16 *outAddr565;
    Utils_DmaCopyFill2D dmaPrm;
    AlgorithmLink_tidlpostprocObj *pAlgObj = \
            (AlgorithmLink_tidlpostprocObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    AlgorithmLink_tidlpostprocCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;
    System_LinkStatistics *linkStatsInfo = pAlgObj->linkStatsInfo;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo = &pAlgObj->outputQInfo;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;
        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    for (queId = 0;queId < pLinkCreatePrms->numInputQueues;queId++)
    {
        System_getLinksFullBuffers(
                    pLinkCreatePrms->inQueParams[queId].prevLinkId,
                    pLinkCreatePrms->inQueParams[queId].prevLinkQueId,
                    &inputBufList);

        if(inputBufList.numBuf > 0)
        {
            for (bufIdx = 0;bufIdx < inputBufList.numBuf;bufIdx++)
            {
                linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

                status = AlgorithmLink_getEmptyOutputBuffer(
                                                pObj,
                                                0,      /* outputQId */
                                                0,      /* channelId */
                                                &pOutSysBuf);
                if(SYSTEM_LINK_STATUS_SOK == status)
                {
                    /* Input buffer */
                    pInSysBuf = inputBufList.buffers[bufIdx];
                    if(SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pInSysBuf->bufType)
                    {
                        pCompBuf = (System_VideoFrameCompositeBuffer*)pInSysBuf->payload;
                        inAddr = (UInt8*)pCompBuf->bufAddr[0][1];   /* second channel */
                    }
                    else if(SYSTEM_BUFFER_TYPE_METADATA == pInSysBuf->bufType)
                    {
                        pInMetaBuf = (System_MetaDataBuffer*)pInSysBuf->payload;
                        inAddr = (UInt8*)pInMetaBuf->bufAddr[0];
                    }

                    pOutVidBuf = (System_VideoFrameBuffer*)pOutSysBuf->payload;
                    pOutSysBuf->srcTimestamp = pInSysBuf->srcTimestamp;
                    pOutSysBuf->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                    if(TIDLPOSTPROC_MODE_CLUT == pLinkCreatePrms->mode)
                    {
                        if((SYSTEM_DF_YUV420SP_UV == pLinkCreatePrms->outDataFormat) ||
                           (SYSTEM_DF_YUV420SP_VU == pLinkCreatePrms->outDataFormat))
                        {
                            /* UV address */
                            outAddr565 = (UInt16*)pOutVidBuf->bufAddr[0];

                            Cache_inv(
                                pLinkCreatePrms->colPalette565,
                                (TIDLPOSTPROC_MAX_NUM_PALETTE * sizeof(UInt16)),
                                Cache_Type_ALL,
                                TRUE);
                        }
                        else if((SYSTEM_DF_RGB16_565 == pLinkCreatePrms->outDataFormat) ||
                                (SYSTEM_DF_BGR16_565 == pLinkCreatePrms->outDataFormat))
                        {
                            outAddr565 = (UInt16*)pOutVidBuf->bufAddr[0];

                            Cache_inv(
                                pLinkCreatePrms->colPalette565,
                                (TIDLPOSTPROC_MAX_NUM_PALETTE * sizeof(UInt16)),
                                Cache_Type_ALL,
                                TRUE);
                        }
                        else
                        {
                            outAddr888 = (UInt8*)pOutVidBuf->bufAddr[0];

                            Cache_inv(
                                pLinkCreatePrms->colPalette888,
                                (TIDLPOSTPROC_MAX_NUM_PALETTE * 3),
                                Cache_Type_ALL,
                                TRUE);
                        }

                        Cache_inv(
                            inAddr,
                            (pAlgObj->inWidth * pAlgObj->inHeight),
                            Cache_Type_ALL,
                            TRUE);

                        /* Skip input padding */
                        inAddr += \
                            (pAlgObj->inWidth * pLinkCreatePrms->inPad) + \
                                pLinkCreatePrms->inPad;

                        /* Color Table look up */
                        if((SYSTEM_DF_YUV420SP_UV == pLinkCreatePrms->outDataFormat) ||
                           (SYSTEM_DF_YUV420SP_VU == pLinkCreatePrms->outDataFormat))
                        {
                            /* For YUV format we only dump the UV plane */
                            for (ht = 0;ht < (pLinkCreatePrms->outHeight/2);ht++)
                            {
                                for (wd = 0;wd < pLinkCreatePrms->outWidth;wd += 2)
                                {
                                    inData = *((UInt8*)inAddr + wd);
                                    *((UInt16*)outAddr565++) = pLinkCreatePrms->colPalette565[inData];
                                }

                                inAddr += (2 * pAlgObj->inWidth);
                            }
                        }
                        else
                        {
                            for (ht = 0;ht < pLinkCreatePrms->outHeight;ht++)
                            {
                                for (wd = 0;wd < pLinkCreatePrms->outWidth;wd++)
                                {
                                    inData = *((UInt8*)inAddr + wd);

                                    if((SYSTEM_DF_RGB16_565 == pLinkCreatePrms->outDataFormat) ||
                                       (SYSTEM_DF_BGR16_565 == pLinkCreatePrms->outDataFormat))
                                    {
                                        *((UInt16*)outAddr565++) = pLinkCreatePrms->colPalette565[inData];
                                    }
                                    else
                                    {
                                        *((UInt8*)outAddr888++) = pLinkCreatePrms->colPalette888[inData][0];
                                        *((UInt8*)outAddr888++) = pLinkCreatePrms->colPalette888[inData][1];
                                        *((UInt8*)outAddr888++) = pLinkCreatePrms->colPalette888[inData][2];
                                    }
                                }

                                inAddr += pAlgObj->inWidth;
                            }
                        }

                        Cache_wb(
                            pOutVidBuf->bufAddr[0],
                            (pOutputQInfo->queInfo.chInfo[0].pitch[0] * pLinkCreatePrms->outHeight),
                            Cache_Type_ALL,
                            TRUE);

                    }
                    else
                    {
                        /* copy the Y plane */
                        /* Format used is RAW08 to copy only the Y plane */
                        dmaPrm.dataFormat = SYSTEM_DF_RAW08;
                        dmaPrm.destAddr[0] = (Ptr)(pOutVidBuf->bufAddr[0]);
                        dmaPrm.destAddr[1] = NULL;
                        dmaPrm.destPitch[0] = pOutputQInfo->queInfo.chInfo[0].pitch[0];
                        dmaPrm.destPitch[1] = 0;
                        dmaPrm.destStartX = 0;
                        dmaPrm.destStartY = 0;
                        dmaPrm.width = pLinkCreatePrms->outWidth;
                        dmaPrm.height = pLinkCreatePrms->outHeight;
                        dmaPrm.srcAddr[0] = (Ptr)(pCompBuf->bufAddr[0][0]);
                        dmaPrm.srcAddr[1] = NULL;
                        dmaPrm.srcPitch[0] = pAlgObj->inChInfo[queId][0].pitch[0];
                        dmaPrm.srcPitch[1] = 0;
                        dmaPrm.srcStartX = pAlgObj->inChInfo[queId][0].startX;
                        dmaPrm.srcStartY = pAlgObj->inChInfo[queId][0].startY;

                        status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
                        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                        /* copy the UV plane */
                        /* Format used is RAW08 to copy only the Y plane */
                        dmaPrm.dataFormat = SYSTEM_DF_RAW08;
                        dmaPrm.destAddr[0] = (Ptr)(pOutVidBuf->bufAddr[1]);
                        dmaPrm.destAddr[1] = NULL;
                        dmaPrm.destPitch[0] = pOutputQInfo->queInfo.chInfo[0].pitch[1];
                        dmaPrm.destPitch[1] = 0;
                        dmaPrm.destStartX = 0;
                        dmaPrm.destStartY = 0;
                        dmaPrm.width = pLinkCreatePrms->outWidth;
                        dmaPrm.height = pLinkCreatePrms->outHeight/2;
                        dmaPrm.srcAddr[0] = (Ptr)(pCompBuf->bufAddr[0][1]);
                        dmaPrm.srcAddr[1] = NULL;
                        dmaPrm.srcPitch[0] = pAlgObj->inChInfo[queId][1].pitch[0];
                        dmaPrm.srcPitch[1] = 0;
                        dmaPrm.srcStartX = pAlgObj->inChInfo[queId][1].startX;
                        dmaPrm.srcStartY = pAlgObj->inChInfo[queId][1].startY;

                        status = Utils_dmaCopy2D(&pAlgObj->dumpFramesDmaObj, &dmaPrm, 1U);
                        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
                    }

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
                                                        0,          /* outputQId */
                                                        pOutSysBuf);
                    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                    /* Notify the next link */
                    System_sendLinkCmd(
                                pLinkCreatePrms->outQueParams.nextLink,
                                SYSTEM_CMD_NEW_DATA,
                                NULL);

                    bufListReturn.numBuf = 1;
                    bufListReturn.buffers[0] = pOutSysBuf;
                    status = AlgorithmLink_releaseOutputBuffer(
                                                       pObj,
                                                       0,           /* outputQId */
                                                       &bufListReturn);
                    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
                }
                else
                {
                    linkStatsInfo->linkStats.chStats[0].inBufDropCount++;
                    linkStatsInfo->linkStats.chStats[0].outBufDropCount[0]++;
                }
            }

            System_putLinksEmptyBuffers(
                            pLinkCreatePrms->inQueParams[queId].prevLinkId,
                            pLinkCreatePrms->inQueParams[queId].prevLinkQueId,
                            &inputBufList);
        }
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
Int32 AlgorithmLink_tidlpostprocPrintStatistics(void *pObj,AlgorithmLink_tidlpostprocObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(
                    &pAlgObj->linkStatsInfo->linkStats,
                    "ALG_TIDLPOSTPROC",
                    TRUE);

    Utils_printLatency(
                    "ALG_TIDLPOSTPROC",
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
Int32 AlgorithmLink_tidlpostprocControl(void *pObj,void *pControlParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_tidlpostprocObj *pAlgObj;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;

    pAlgObj = (AlgorithmLink_tidlpostprocObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
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
            AlgorithmLink_tidlpostprocPrintStatistics(pObj, pAlgObj);
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
Int32 AlgorithmLink_tidlpostprocStop(void *pObj)
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
Int32 AlgorithmLink_tidlpostproc_initPlugin(Void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate = AlgorithmLink_tidlpostprocCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = AlgorithmLink_tidlpostprocProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = AlgorithmLink_tidlpostprocControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop = AlgorithmLink_tidlpostprocStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete = AlgorithmLink_tidlpostprocDelete;

    algId = ALGORITHM_LINK_A15_ALG_TIDLPOSTPROC;
    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}