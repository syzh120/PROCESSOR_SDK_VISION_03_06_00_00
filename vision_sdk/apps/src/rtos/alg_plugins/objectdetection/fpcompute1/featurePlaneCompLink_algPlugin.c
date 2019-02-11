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
 * \file featurePlaneCompLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for feature Plane computation
 *         Link
 *
 * \version 0.0 (Feb 2014) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "featurePlaneCompLink_priv.h"


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
Int32 AlgorithmLink_featurePlaneComputation_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_featurePlaneComputeCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_featurePlaneComputeProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_featurePlaneComputeControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_featurePlaneComputeStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_featurePlaneComputeDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_FEATUREPLANECOMPUTE;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for feature plane computation alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_featurePlaneComputeCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    UInt32 outBufferSize, numScales, numSteps;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_FeaturePlaneComputeObj                * pFPlaneObj;
    AlgorithmLink_FeaturePlaneComputationCreateParams   * pLinkCreateParams;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_LinkChInfo                                   * pPrevChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;

    pFPlaneObj = (AlgorithmLink_FeaturePlaneComputeObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_FeaturePlaneComputeObj),
                        32);
    UTILS_assert(pFPlaneObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pFPlaneObj);

    pLinkCreateParams = (AlgorithmLink_FeaturePlaneComputationCreateParams *)
                         pCreateParams;
    pInputQInfo       = &pFPlaneObj->inputQInfo;
    pOutputQInfo      = &pFPlaneObj->outputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pFPlaneObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_FeaturePlaneComputationCreateParams)
           );

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->queInfo.numCh = 1;

    status = System_linkGetInfo(
                                  pLinkCreateParams->inQueParams.prevLinkId,
                                  &prevLinkInfo
                                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= 1);

    prevLinkQId = pLinkCreateParams->inQueParams.prevLinkQueId;

    pFPlaneObj->inChInfo = prevLinkInfo.queInfo[prevLinkQId].chInfo[0];
    pPrevChInfo = &pFPlaneObj->inChInfo;

    if(System_Link_Ch_Info_Get_Flag_Data_Format(pPrevChInfo->flags)
        !=
        SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(0);
    }

    UTILS_assert(
                  (pPrevChInfo->width  >= pLinkCreateParams->imgFrameWidth)
                  ||
                  (pPrevChInfo->height >= pLinkCreateParams->imgFrameHeight)
                );

    pOutChInfo          = &pOutputQInfo->queInfo.chInfo[0];
    pOutChInfo->flags   = 0;
    pOutChInfo->height  = pLinkCreateParams->imgFrameHeight;
    pOutChInfo->width   = pLinkCreateParams->imgFrameWidth;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(
                                pObj,
                                1,
                                pInputQInfo,
                                1,
                                pOutputQInfo
                               );

    numScales = pLinkCreateParams->numScales;
    numSteps  = 6;

    if(pLinkCreateParams->roiEnable==FALSE)
    {
        pLinkCreateParams->roiCenterX =
            pLinkCreateParams->imgFrameWidth/2;

        pLinkCreateParams->roiCenterY =
            pLinkCreateParams->imgFrameHeight/2;

        pLinkCreateParams->roiWidth =
            pLinkCreateParams->imgFrameWidth;

        pLinkCreateParams->roiHeight =
            pLinkCreateParams->imgFrameHeight;
    }

    Alg_filter2dCreate(
        &pFPlaneObj->algFilter2dObj,
        pLinkCreateParams->imgFrameWidth,
        pLinkCreateParams->imgFrameHeight,
        pPrevChInfo->pitch,
        TRUE,
        TRUE,
        TRUE
        );

    Alg_imagePyramidCreate(
        &pFPlaneObj->algImagePyramidObj,
        &pFPlaneObj->algFilter2dObj,
        numScales,
        numSteps,
        pLinkCreateParams->roiCenterX,
        pLinkCreateParams->roiCenterY,
        pLinkCreateParams->roiWidth,
        pLinkCreateParams->roiHeight
        );

    Alg_featureComputeCreate(
        &pFPlaneObj->algFeatureComputeObj,
        &pFPlaneObj->algImagePyramidObj,
        &pFPlaneObj->outBufferSize
        );

    pFPlaneObj->filter2dTime = 0;
    pFPlaneObj->imagePyramidTime = 0;
    pFPlaneObj->featureComputeTime = 0;
    pFPlaneObj->frameCount = 0;

    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */

    outBufferSize   =   pFPlaneObj->outBufferSize;

    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer       =   &pFPlaneObj->buffers[bufId];
        pMetaDataBuffer     =   &pFPlaneObj->featurePlanes[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pMetaDataBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =   0;

        pMetaDataBuffer->numMetaDataPlanes  =   1;
        pMetaDataBuffer->metaBufSize[0]     =   outBufferSize;
        pMetaDataBuffer->metaFillLength[0]  =   outBufferSize;
        pMetaDataBuffer->bufAddr[0]         =   Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    outBufferSize,
                                                    ALGORITHMLINK_FRAME_ALIGN
                                                    );
        UTILS_assert(pMetaDataBuffer->bufAddr[0] != NULL);
        pMetaDataBuffer->flags = 0;

        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }

    pFPlaneObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_FEATURE_PLANE_COMPUTE");
    UTILS_assert(NULL != pFPlaneObj->linkStatsInfo);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmLink_featurePlaneComputeProcess(void * pObj)
{
    UInt32 bufId;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_FeaturePlaneComputeObj                * pFPlaneObj;
    System_BufferList                                     inputBufList;
    AlgorithmLink_FeaturePlaneComputationCreateParams   * pLinkCreateParams;
    System_Buffer                                       * pSysOutBuffer;
    System_Buffer                                       * pSysInBuffer;
    System_VideoFrameBuffer                             * pVideoFrameBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;
    System_BufferList                                   bufListReturn;
    System_LinkStatistics                               * linkStatsInfo;
    UInt8 *inBufAddr[2];
    UInt64 curTime;

    pFPlaneObj = (AlgorithmLink_FeaturePlaneComputeObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pFPlaneObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pLinkCreateParams = &pFPlaneObj->algLinkCreateParams;

    if (pFPlaneObj->isFirstFrameRecv == FALSE)
    {
        pFPlaneObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                        pLinkCreateParams->inQueParams.prevLinkId,
                        pLinkCreateParams->inQueParams.prevLinkQueId,
                        &inputBufList);

    if (inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];
            if(pSysInBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

            status = AlgorithmLink_getEmptyOutputBuffer(
                                                        pObj,
                                                        0,
                                                        0,
                                                        &pSysOutBuffer
                                                        );
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                 linkStatsInfo->linkStats.chStats
                                [0].inBufDropCount++;
                 linkStatsInfo->linkStats.chStats
                                [0].outBufDropCount[0]++;
            }
            else
            {
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                pVideoFrameBuffer = (System_VideoFrameBuffer *)pSysInBuffer->payload;
                pMetaDataBuffer   = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                inBufAddr[0] = pVideoFrameBuffer->bufAddr[0];
                inBufAddr[1] = pVideoFrameBuffer->bufAddr[1];

                inBufAddr[0] += pFPlaneObj->inChInfo.pitch[0]*pLinkCreateParams->imgFrameStartY
                                +
                                pLinkCreateParams->imgFrameStartX;

                inBufAddr[1] += pFPlaneObj->inChInfo.pitch[1]*pLinkCreateParams->imgFrameStartY/2
                                +
                                pLinkCreateParams->imgFrameStartX;

                curTime = Utils_getCurGlobalTimeInUsec();

                Alg_filter2dProcess(
                    &pFPlaneObj->algFilter2dObj,
                    (Void**)inBufAddr,
                    NULL /* NOT USED */
                    );

                curTime = Utils_getCurGlobalTimeInUsec() - curTime;

                pFPlaneObj->filter2dTime += curTime;

                curTime = Utils_getCurGlobalTimeInUsec();

                Alg_imagePyramidProcess(
                    &pFPlaneObj->algImagePyramidObj
                    );

                curTime = Utils_getCurGlobalTimeInUsec() - curTime;

                pFPlaneObj->imagePyramidTime += curTime;

                curTime = Utils_getCurGlobalTimeInUsec();

                Alg_featureComputeProcess(
                    &pFPlaneObj->algFeatureComputeObj,
                    pMetaDataBuffer->bufAddr[0]
                    );

                curTime = Utils_getCurGlobalTimeInUsec() - curTime;

                pFPlaneObj->featureComputeTime += curTime;

                pFPlaneObj->frameCount++;

                #if 0
                if((pFPlaneObj->frameCount > 0) && (pFPlaneObj->frameCount%300==0))
                {
                    Vps_printf(
                        " ALG_FEATURE_PLANE_COMPUTE: filter2d (avg) = %d us\n",
                            pFPlaneObj->filter2dTime/pFPlaneObj->frameCount
                        );
                    Vps_printf(
                        " ALG_FEATURE_PLANE_COMPUTE: imagePyramid (avg) = %d us\n",
                            pFPlaneObj->imagePyramidTime/pFPlaneObj->frameCount
                        );
                    Vps_printf(
                        " ALG_FEATURE_PLANE_COMPUTE: featureCompute (avg) = %d us\n",
                            pFPlaneObj->featureComputeTime/pFPlaneObj->frameCount
                        );

                    pFPlaneObj->filter2dTime = 0;
                    pFPlaneObj->imagePyramidTime = 0;
                    pFPlaneObj->featureComputeTime = 0;
                    pFPlaneObj->frameCount = 0;
                }
                #endif

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                                [0].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                                [0].outBufCount[0]++;

                status = AlgorithmLink_putFullOutputBuffer(
                                                pObj,
                                                0,
                                                pSysOutBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(
                      pLinkCreateParams->outQueParams.nextLink,
                      SYSTEM_CMD_NEW_DATA,
                      NULL);
                /*
                 * Releasing (Free'ing) output buffers, since algorithm
                 * does not need it for any future usage.
                 */
                bufListReturn.numBuf = 1;
                bufListReturn.buffers[0] = pSysOutBuffer;

                AlgorithmLink_releaseOutputBuffer(
                                                  pObj,
                                                  0,
                                                  &bufListReturn
                                                  );
            }
            bufListReturn.numBuf = 1;
            bufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                              pObj,
                              0,
                              pLinkCreateParams->inQueParams.prevLinkId,
                              pLinkCreateParams->inQueParams.prevLinkQueId,
                              &bufListReturn,
                              &bufDropFlag);
        }
    }

    return status;
}

Int32 AlgorithmLink_featurePlaneComputeControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_FeaturePlaneComputeObj* pFPlaneObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;
    AlgorithmLink_FeaturePlaneComputationSetROIParams *pROIPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pFPlaneObj = (AlgorithmLink_FeaturePlaneComputeObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */

    switch(pAlgLinkControlPrm->controlCmd)
    {
        case ALGORITHM_LINK_FEATURE_PLANE_COMPUTE_CMD_SET_ROI:

            if(pAlgLinkControlPrm->size != sizeof(*pROIPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pROIPrm = (AlgorithmLink_FeaturePlaneComputationSetROIParams *)
                                    pControlParams;

                pFPlaneObj->algLinkCreateParams.imgFrameStartX
                    = pROIPrm->imgFrameStartX;

                pFPlaneObj->algLinkCreateParams.imgFrameStartY
                    = pROIPrm->imgFrameStartY;

                pFPlaneObj->algLinkCreateParams.imgFrameWidth
                    = pROIPrm->imgFrameWidth;

                pFPlaneObj->algLinkCreateParams.imgFrameHeight
                    = pROIPrm->imgFrameHeight;
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_featurePlaneComputePrintStatistics(
                                                                pObj,
                                                                pFPlaneObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_featurePlaneComputeStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_featurePlaneComputeDelete(void * pObj)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId;
    AlgorithmLink_FeaturePlaneComputeObj                * pFPlaneObj;
    AlgorithmLink_FeaturePlaneComputationCreateParams   * pLinkCreateParams;
    System_MetaDataBuffer                               * pMetaDataBuffer;

    pFPlaneObj = (AlgorithmLink_FeaturePlaneComputeObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pFPlaneObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pFPlaneObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_filter2dDelete(&pFPlaneObj->algFilter2dObj);
    Alg_imagePyramidDelete(&pFPlaneObj->algImagePyramidObj);
    Alg_featureComputeDelete(&pFPlaneObj->algFeatureComputeObj);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pMetaDataBuffer     =   &pFPlaneObj->featurePlanes[bufId];


        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pMetaDataBuffer->bufAddr[0],
                                pMetaDataBuffer->metaBufSize[0]
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    Utils_memFree(
                       UTILS_HEAPID_DDR_CACHED_LOCAL,
                       pFPlaneObj,
                       sizeof(AlgorithmLink_FeaturePlaneComputeObj)
                    );
    return status;
}

Int32 AlgorithmLink_featurePlaneComputePrintStatistics(void *pObj,
                AlgorithmLink_FeaturePlaneComputeObj *pFeaturePlaneComputeObj)
{
    UTILS_assert(NULL != pFeaturePlaneComputeObj->linkStatsInfo);

    Utils_printLinkStatistics(&pFeaturePlaneComputeObj->linkStatsInfo->linkStats,
                            "ALG_FEATURE_PLANE_COMPUTE",
                            TRUE);

    Utils_printLatency("ALG_FEATURE_PLANE_COMPUTE",
                       &pFeaturePlaneComputeObj->linkStatsInfo->linkLatency,
                       &pFeaturePlaneComputeObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

