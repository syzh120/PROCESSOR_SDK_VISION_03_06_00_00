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
 * \file autoRemapLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for automatic rectification
 *         algorithm Link
 *
 * \version 0.1 (Oct 2016) :First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "autoRemapLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include <include/link_api/grpxSrcLink.h>

//#define CAPTURE_DELAY 2


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of auto chart detect algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemap_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_AutoRemapCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_AutoRemapProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_AutoRemapControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_AutoRemapStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_AutoRemapDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_AUTOREMAP;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for automatic rectification alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemapCreate(void * pObj, void * pCreateParams)
{
    void                       * algHandle;
    //Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    //System_Buffer              * pSystemBuffer;
    //System_MetaDataBuffer      * pSystemMetaDataBuffer;

    System_LinkInfo              prevLinkInfo;
    //AlgorithmLink_AutoRemapOutputQueId   outputQId;
    //AlgorithmLink_AutoRemapInputQueId    inputQId;
    Int32                        channelId;
    //Int32                        numChannelsUsed;
    //Int32                        numInputQUsed;
    //Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    //UInt32                       metaBufSize;
    UInt32                       dataFormat;
    System_LinkChInfo          * pOutChInfo;
    System_LinkChInfo          * pPrevChInfo;
    UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_AutoRemapObj           * pAutoRemapObj;
    AlgorithmLink_AutoRemapCreateParams  * pAutoRemapLinkCreateParams;
    AutoRemap_CreationParamsStruct       * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;


    pAutoRemapLinkCreateParams =
        (AlgorithmLink_AutoRemapCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    if(sizeof(AlgorithmLink_AutoRemapObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
    	pAutoRemapObj = (AlgorithmLink_AutoRemapObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                       sizeof(AlgorithmLink_AutoRemapObj), 32);
    }
    else
    {
    	pAutoRemapObj = (AlgorithmLink_AutoRemapObj *)
                        malloc(sizeof(AlgorithmLink_AutoRemapObj));
    }

    UTILS_assert(pAutoRemapObj!=NULL);

    pAlgCreateParams = &pAutoRemapObj->algCreateParams;

    pOutputQInfo = &pAutoRemapObj->outputQInfo;
    pInputQInfo  = &pAutoRemapObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAutoRemapObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pAutoRemapObj->algLinkCreateParams),
           (void*)(pAutoRemapLinkCreateParams),
           sizeof(AlgorithmLink_AutoRemapCreateParams)
          );

    /* Init control params */
    pAutoRemapObj->controlParams.autoRemapMode = -1;

    /*
     * Populating parameters corresponding to Q usage of automatic corner detection
     * algorithm link
     */
    //numInputQUsed     = ALGLINK_AUTOREMAP_IPQID_MAXIPQ;
    //numOutputQUsed    = ALGLINK_AUTOREMAP_OPQID_MAXOPQ;
    //numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

#if 0
    pOutputQInfo[ALGLINK_AUTOREMAP_OPQID_FEATURE].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_AUTOREMAP_OPQID_FEATURE].queInfo.numCh = numChannelsUsed;
#endif

    //inputQId  = ALGLINK_AUTOREMAP_IPQID_MULTIVIEW;

    /* previous link info */
    status = System_linkGetInfo(
                pAutoRemapLinkCreateParams->inQueParams.prevLinkId,
                &prevLinkInfo);

    prevLinkQueId =
        pAutoRemapLinkCreateParams->inQueParams.prevLinkQueId;
    pPrevChInfo   =
        &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    prevChInfoFlags    = pPrevChInfo->flags;
    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV)
    {
        UTILS_assert(NULL);
    }

    pAutoRemapObj->dataFormat = dataFormat;
    pAutoRemapObj->inPitch[0] = pPrevChInfo->pitch[0];
    pAutoRemapObj->inPitch[1] = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pAutoRemapObj->algLinkCreateParams.maxInputWidth)
       ||
       (pPrevChInfo->height > pAutoRemapObj->algLinkCreateParams.maxInputHeight)
      )
    {
      UTILS_assert(NULL);
    }


    /*
     * Channel info population for output Q Id - ALGLINK_AutoRemap_OPQID_FEATURE
     * TBD - To check if anything in channel info is needed for meta data op
     */
    //outputQId = ALGLINK_AutoRemap_OPQID_FEATURE;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo->queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;


    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                1, //numInputQUsed,
                                pInputQInfo,
                                0, //numOutputQUsed,
                                pOutputQInfo
                                );
    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */

    UTILS_assert(pAutoRemapLinkCreateParams->inFrameHeight <=
            AUTOREMAP_LINK_INPUT_FRAME_HEIGHT);
    UTILS_assert(pAutoRemapLinkCreateParams->inFrameWidth <=
            AUTOREMAP_LINK_INPUT_FRAME_WIDTH);
    
    pAlgCreateParams->inFrameHeight =
            pAutoRemapLinkCreateParams->inFrameHeight;
    pAlgCreateParams->inFrameWidth =
            pAutoRemapLinkCreateParams->inFrameWidth;
    pAlgCreateParams->cropOffsetX =
            pAutoRemapLinkCreateParams->cropOffsetX;
    pAlgCreateParams->cropOffsetY =
            pAutoRemapLinkCreateParams->cropOffsetY;
    
    pAlgCreateParams->numCameras =
            pAutoRemapLinkCreateParams->numCameras;

    pAlgCreateParams->autoRemapForTDA2x = pAutoRemapLinkCreateParams->autoRemapForTDA2x;
    pAlgCreateParams->fishEyeRect = pAutoRemapLinkCreateParams->fishEyeRect;
    pAlgCreateParams->lutWidth = pAutoRemapLinkCreateParams->lutWidth;
    pAlgCreateParams->lutHeight = pAutoRemapLinkCreateParams->lutHeight;

    pAlgCreateParams->useRansac = pAutoRemapLinkCreateParams->useRansac;
    pAlgCreateParams->numRansacIters = pAutoRemapLinkCreateParams->numRansacIters;
    pAlgCreateParams->numRansacData = pAutoRemapLinkCreateParams->numRansacData;

    pAlgCreateParams->roiRegion = pAutoRemapLinkCreateParams->roiRegion;

    pAlgCreateParams->sfWidth = pAutoRemapLinkCreateParams->sfWidth;
    pAlgCreateParams->sfHeight = pAutoRemapLinkCreateParams->sfHeight;

    pAlgCreateParams->remapBlockWidth = pAutoRemapLinkCreateParams->blockWidthBB;
    pAlgCreateParams->remapBlockHeight = pAutoRemapLinkCreateParams->blockHeightBB;

    pAlgCreateParams->isSrcMapFloat       = pAutoRemapLinkCreateParams->isSrcMapFloat;
    pAlgCreateParams->srcFormat           = pAutoRemapLinkCreateParams->srcFormat;
    pAlgCreateParams->mapQshift           = pAutoRemapLinkCreateParams->mapQshift ;
    pAlgCreateParams->interpolationLuma   = pAutoRemapLinkCreateParams->interpolationLuma;
    pAlgCreateParams->interpolationChroma = pAutoRemapLinkCreateParams->interpolationChroma;
    pAlgCreateParams->rightShift          = pAutoRemapLinkCreateParams->rightShift;
    pAlgCreateParams->sat_high            = pAutoRemapLinkCreateParams->sat_high ;
    pAlgCreateParams->sat_high_set        = pAutoRemapLinkCreateParams->sat_high_set;
    pAlgCreateParams->sat_low             = pAutoRemapLinkCreateParams->sat_low;
    pAlgCreateParams->sat_low_set         = pAutoRemapLinkCreateParams->sat_low_set;
    pAlgCreateParams->enableMerge         = pAutoRemapLinkCreateParams->enableMerge;
    pAlgCreateParams->dstFormat           = pAutoRemapLinkCreateParams->dstFormat ;
    pAlgCreateParams->pairIdx             = pAutoRemapLinkCreateParams->pairIdx;

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_AutoRemapMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_AutoRemapMemQuery(pAlgCreateParams, &memRequests, 0);
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
        if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD)
        {
            memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        memRequests.memTab[memTabId].size,
                                        memRequests.memTab[memTabId].alignment);
        }
        else
        {
            memRequests.memTab[memTabId].basePtr =
                malloc(memRequests.memTab[memTabId].size);
        }

        UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
        }
    }

    algHandle = Alg_AutoRemapCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pAutoRemapObj->algHandle = algHandle;


    pAutoRemapObj->frameDropCounter          = 0;

    pAutoRemapObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
            AlgorithmLink_getLinkId(pObj), "ALG_AUTOREMAP");
    UTILS_assert(NULL != pAutoRemapObj->linkStatsInfo);

    pAutoRemapObj->numInputChannels = 1;

    pAutoRemapObj->isFirstFrameRecv   = FALSE;


    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of auto chart detect algorithm link
 *
 *        This function and the algorithm process function execute
 *        on same processor core. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemapProcess(void * pObj)
{

    AlgorithmLink_AutoRemapObj  * pAutoRemapObj;
    void                       * algHandle;
    //AlgorithmLink_AutoRemapInputQueId    inputQId;
    //AlgorithmLink_AutoRemapOutputQueId   outputQId;
    //UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    Int32                        inputStatus;
    UInt32                       bufId;
    UInt32                       viewId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    //System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferFeaturePt;
    //System_Buffer              * pSysBufferGACornerLoc;
    System_Buffer              * pSystemBufferMultiview;
    Bool                         bufDropFlag;
    //System_MetaDataBuffer      * pFeaturePtBuffer;

    UInt32                       autoRemapMode = FEATURE_COLLECT;
    Bool                         firstFrame = 0;
    Bool                         algoProcessCallNeeded;
    Int32                        outLUTSize;

    System_VideoFrameCompositeBuffer    * pCompositeBuffer;
    AlgorithmLink_AutoRemapCreateParams  * pAutoRemapLinkCreateParams;
    System_LinkStatistics	   * linkStatsInfo;

    GrpxSrcLink_StereoCalibPrm grpxSrcStereoCalibPrm;


    pAutoRemapObj = (AlgorithmLink_AutoRemapObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pAutoRemapObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                 = pAutoRemapObj->algHandle;
    pAutoRemapLinkCreateParams = (AlgorithmLink_AutoRemapCreateParams *)
                                    &pAutoRemapObj->algLinkCreateParams;


    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);


    // To overlay detected feature points
    grpxSrcStereoCalibPrm.featurePointBuf =
            (Int16 *)(pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf +
                      pAutoRemapLinkCreateParams->featureBufPrms.featureHeaderSize);

    grpxSrcStereoCalibPrm.featurePointBufSize =
            pAutoRemapLinkCreateParams->featureBufPrms.featureBufSize -
            pAutoRemapLinkCreateParams->featureBufPrms.featureHeaderSize;


    if(pAutoRemapObj->isFirstFrameRecv==FALSE)
    {
        pAutoRemapObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pAutoRemapObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Get Input buffers from previous link
     * and process them if output is available
     */
    System_getLinksFullBuffers(
        pAutoRemapLinkCreateParams->inQueParams.prevLinkId,
        pAutoRemapLinkCreateParams->inQueParams.prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSystemBufferMultiview = inputBufList.buffers[bufId];
            pCompositeBuffer = (System_VideoFrameCompositeBuffer *)
                                       pSystemBufferMultiview->payload;

            bufDropFlag = TRUE;

            /*
             * TBD: Put any other checks for input parameter correctness.
             */
            inputStatus = SYSTEM_LINK_STATUS_SOK;

            if(pSystemBufferMultiview->bufType !=
                    SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
            {
                inputStatus = SYSTEM_LINK_STATUS_EFAIL;
                linkStatsInfo->linkStats.inBufErrorCount++;
            }

            /*
             * For frame to be processed:
             *  - Output buffer will be queried
             *  - If output buffer is available, then algorithm will be called
             */

            if(inputStatus == SYSTEM_LINK_STATUS_SOK)
            {

#if 0
                outputQId = ALGLINK_AutoRemap_OPQID_FEATURE;
                channelId = 0;
                status = AlgorithmLink_getEmptyOutputBuffer(
                                                    pObj,
                                                    outputQId,
                                                    channelId,
                                                    &pSysBufferFeaturePt);
#endif

#if 0

                if(status != SYSTEM_LINK_STATUS_SOK)
                {
                    /*
                     * If output buffer is not available, then input buffer
                     * is just returned back
                     */
                    linkStatsInfo->linkStats.outBufErrorCount++;
                }
                else
#endif
                {
#if 0
                    pSysBufferFeaturePt->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
                    pSysBufferFeaturePt->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                    pFeaturePtBuffer = (System_MetaDataBuffer *)pSysBufferFeaturePt->payload;
#endif

                    for(viewId = 0; viewId < pAutoRemapLinkCreateParams->numCameras; viewId++)
                    {
                        /*
                        Cache_inv(pCompositeBuffer->bufAddr[0][viewId],
                                (AUTOREMAP_LINK_INPUT_FRAME_WIDTH*AUTOREMAP_LINK_INPUT_FRAME_HEIGHT),
                                Cache_Type_ALLD, TRUE);
                        Cache_inv(pCompositeBuffer->bufAddr[1][viewId],
                                ((AUTOREMAP_LINK_INPUT_FRAME_WIDTH*AUTOREMAP_LINK_INPUT_FRAME_HEIGHT)/2),
                                Cache_Type_ALLD, TRUE);
                        */
                        Cache_inv(pCompositeBuffer->bufAddr[0][viewId],
                                (pAutoRemapLinkCreateParams->inFrameWidth*pAutoRemapLinkCreateParams->inFrameHeight),
                                Cache_Type_ALLD, TRUE);
                        Cache_inv(pCompositeBuffer->bufAddr[1][viewId],
                                (pAutoRemapLinkCreateParams->inFrameWidth*pAutoRemapLinkCreateParams->inFrameHeight/2),
                                Cache_Type_ALLD, TRUE);

                    }

                    switch (pAutoRemapObj->controlParams.autoRemapMode)
                    {
                        default:
                        case -1:
                            algoProcessCallNeeded = FALSE;
                            break;

                        case 1:
                            firstFrame = 1;
                            autoRemapMode = FEATURE_COLLECT;
                            algoProcessCallNeeded = TRUE;

                            break;

                        case 2:
                            firstFrame = 0;
                            autoRemapMode = FEATURE_COLLECT;
                            algoProcessCallNeeded = TRUE;

                            break;

                        case 3:
                            autoRemapMode = PERSMAT_CAL;
                            algoProcessCallNeeded = TRUE;
                            break;
                    }

                    if(algoProcessCallNeeded == TRUE)
                    {
                        Vps_printf("1. autoRemapMode:%d\n", pAutoRemapObj->controlParams.autoRemapMode);
                        status = Alg_AutoRemapProcess(algHandle,
                                                      pCompositeBuffer,
                                                      firstFrame,
                                                      pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf,
                                                      pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf +
                                                      pAutoRemapLinkCreateParams->featureBufPrms.featureHeaderSize,
                                                      pAutoRemapLinkCreateParams->calibLUTBufPrms.pCalibLUTBuf +
                                                      pAutoRemapLinkCreateParams->calibLUTBufPrms.calibLUTHeaderSize,
                                                      &outLUTSize,
                                                      autoRemapMode,
                                                      pAutoRemapLinkCreateParams->autoRemapForTDA2x);

                        pAutoRemapObj->controlParams.autoRemapMode = -1;
                        ((Int16 *)pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf)[0] = (Int16)(-1);

                        Vps_printf("2. autoRemapMode:%d\n", pAutoRemapObj->controlParams.autoRemapMode);

                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


                        if (autoRemapMode == FEATURE_COLLECT)
                        {

                            Cache_wb(pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf,
                                    pAutoRemapLinkCreateParams->featureBufPrms.featureBufSize,
                                    Cache_Type_ALLD,
                                    TRUE);

                            /*** overlay detected feature points ***/
                            grpxSrcStereoCalibPrm.startIdx = ((Int16 *)pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf)[1];
                            grpxSrcStereoCalibPrm.endIdx = ((Int16 *)pAutoRemapLinkCreateParams->featureBufPrms.pFeatureBuf)[2];

                            System_linkControl(
                                    IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                                    GRPX_SRC_LINK_CMD_STEREO_CALIB_PARAM,
                                    &grpxSrcStereoCalibPrm,
                                    sizeof(GrpxSrcLink_StereoCalibPrm),
                                    TRUE);
                        }

                        if (autoRemapMode == PERSMAT_CAL)
                        {
                            UInt32* pCalibLUTBuf = (UInt32 *)pAutoRemapLinkCreateParams->calibLUTBufPrms.pCalibLUTBuf;

                            if (pAutoRemapLinkCreateParams->autoRemapForTDA2x)
                            {
                                Vps_printf("Write_QSPI\n");

                                *pCalibLUTBuf =  pAutoRemapLinkCreateParams->calibLUTBufPrms.calibLUTTagID;
                                pCalibLUTBuf ++;

                                *pCalibLUTBuf = outLUTSize + pAutoRemapLinkCreateParams->calibLUTBufPrms.calibLUTHeaderSize;
                                pCalibLUTBuf ++;

                                *pCalibLUTBuf = pAutoRemapLinkCreateParams->calibLUTBufPrms.calibLUTQSPIOffset;
                                pCalibLUTBuf ++;

                                *pCalibLUTBuf = 0U;
                            }

                            Cache_wb(pAutoRemapLinkCreateParams->calibLUTBufPrms.pCalibLUTBuf,
                                    pAutoRemapLinkCreateParams->calibLUTBufPrms.calibLUTBufSize,
                                    Cache_Type_ALLD,
                                    TRUE);

                            //pAutoRemapLinkCreateParams->calibLUTBufPrms.isValid = TRUE;
                        }



                        Utils_updateLatency(&linkStatsInfo->linkLatency,
                                            pSysBufferFeaturePt->linkLocalTimestamp);
                        Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                            pSysBufferFeaturePt->srcTimestamp);


                        linkStatsInfo->linkStats.chStats
                            [pSystemBufferMultiview->chNum].inBufProcessCount++;
                        linkStatsInfo->linkStats.chStats
                            [pSystemBufferMultiview->chNum].outBufCount[0]++;

                    }

                    bufDropFlag = FALSE;
                }

            } /* if(pACDetectObj->isFirstOPGenerated == FALSE) */

            /*
             * Releasing (Free'ing) Input buffers, since algorithm does not need
             * it for any future usage.
             */
            inputBufListReturn.numBuf     = 1;
            inputBufListReturn.buffers[0] = pSystemBufferMultiview;
            AlgorithmLink_releaseInputBuffer(
                                            pObj,
                                            0, //inputQId,
                                            pAutoRemapLinkCreateParams->inQueParams.prevLinkId,
                                            pAutoRemapLinkCreateParams->inQueParams.prevLinkQueId,
                                            &inputBufListReturn,
                                            &bufDropFlag);
        }

    }

    return status;

}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for auto rectification algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_AutoRemapControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_AutoRemapObj      * pAutoRemapObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32  status    = SYSTEM_LINK_STATUS_SOK;
    Int8   autoRemapMode = -1;

    pAutoRemapObj = (AlgorithmLink_AutoRemapObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pAutoRemapObj->algHandle;

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */

    Vps_printf("AUTO REMAP CONTROL....\n");
    switch(pAlgLinkControlPrm->controlCmd)
    {

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_AutoRemapPrintStatistics(pObj, pAutoRemapObj);
            break;

        case AUTO_REMAP_LINK_CMD_FEATURE_COLLECT_NEW:
            autoRemapMode = 1;
            Vps_printf("==========AUTO_REMAP_LINK_CMD_FEATURE_COLLECT_NEW\n ");
            status = Alg_AutoRemapControl(algHandle,
                                          &(pAutoRemapObj->controlParams),
                                          autoRemapMode);
            break;

        case AUTO_REMAP_LINK_CMD_FEATURE_COLLECT:
            autoRemapMode = 2;
            Vps_printf("==========AUTO_REMAP_LINK_CMD_FEATURE_COLLECT\n ");
            status = Alg_AutoRemapControl(algHandle,
                                          &(pAutoRemapObj->controlParams),
                                          autoRemapMode);
            break;

        case AUTO_REMAP_LINK_CMD_PERSMAT_CAL:
            autoRemapMode = 3;
            Vps_printf("==========AUTO_REMAP_LINK_CMD_PERSMAT_CAL\n ");
            status = Alg_AutoRemapControl(algHandle,
                                          &(pAutoRemapObj->controlParams),
                                          autoRemapMode);
            break;

        default:
            status = Alg_AutoRemapControl(algHandle,
                                          &(pAutoRemapObj->controlParams),
                                          autoRemapMode);
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for auto chart detect algorithm link
 *
 *        For this algorithm there is no locking of frames and hence no
 *        flushing of frames. Also there are no any other functionality to be
 *        done at the end of execution of this algorithm. Hence this function
 *        is an empty function for this algorithm.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemapStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for auto chart detect algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemapDelete(void * pObj)
{
    //Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    //UInt32                       metaBufSize;
    //System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_AutoRemapObj       * pAutoRemapObj;
    UInt32                            memTabId;
    //AlgorithmLink_AutoRemapOutputQueId outputQId;

    pAutoRemapObj = (AlgorithmLink_AutoRemapObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAutoRemapObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_AutoRemapDelete(pAutoRemapObj->algHandle, &memRequests);

    /*
     * Memory allocations for the requests done by algorithm
     */
    for(memTabId = 0 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {

            if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD)
            {
                status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                    memRequests.memTab[memTabId].basePtr,
                                    memRequests.memTab[memTabId].size);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            else
            {
                free(memRequests.memTab[memTabId].basePtr);
            }
        }
    }

#if 0
    /*
     * Deletion of output buffers for output Qs
     */
    outputQId = ALGLINK_AutoRemap_OPQID_FEATURE;
    for(frameIdx = 0;
        frameIdx < pAutoRemapObj->algLinkCreateParams.numOutput;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pAutoRemapObj->featurePoints[outputQId][frameIdx]);

        metaBufSize = AutoRemap_LINK_FEATUREPOINT_SIZE;

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                metaBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
#endif

    /*
     * Space for Algorithm specific object gets freed here.
     */
    if(sizeof(AlgorithmLink_AutoRemapObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pAutoRemapObj,
                               sizeof(AlgorithmLink_AutoRemapObj));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        free(pAutoRemapObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pAutoRemapObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemapPrintStatistics(void *pObj,
                       AlgorithmLink_AutoRemapObj *pAutoRemapObj)
{
    UTILS_assert(NULL != pAutoRemapObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAutoRemapObj->linkStatsInfo->linkStats, "ALG_AutoRemap", TRUE);

    Utils_printLatency("ALG_AUTOREMAP",
                       &pAutoRemapObj->linkStatsInfo->linkLatency,
                       &pAutoRemapObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */


