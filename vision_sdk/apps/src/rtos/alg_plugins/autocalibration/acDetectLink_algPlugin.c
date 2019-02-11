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
 * \file gAlignLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for geometric alignment Link
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "acDetectLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/alg_plugins/commonutils/lens_distortion_correction/ldc_config.h>

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
Int32 AlgorithmLink_acDetect_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_acDetectCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_acDetectProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_acDetectControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_acDetectStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_acDetectDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_AUTO_CHART_DETECT;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for automatic chart detect alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_acDetectCreate(void * pObj, void * pCreateParams)
{
    void                       * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    //System_Buffer              * pSystemBufferCornerLoc;
    //System_MetaDataBuffer      * pSystemMetaDataBufferCornerLoc;
    System_LinkInfo              prevLinkInfo;
    AlgorithmLink_ACDetectOutputQueId   outputQId;
    AlgorithmLink_ACDetectInputQueId    inputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       metaBufSize;
    UInt32                       dataFormat;
    System_LinkChInfo          * pOutChInfo;
    System_LinkChInfo          * pPrevChInfo;
    UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_ACDetectObj            * pACDetectObj;
    AlgorithmLink_ACDetectCreateParams   * pACDetectLinkCreateParams;
    SV_ACDetect_CreationParamsStruct     * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;

    pACDetectLinkCreateParams =
        (AlgorithmLink_ACDetectCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    if(sizeof(AlgorithmLink_ACDetectObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
    	pACDetectObj = (AlgorithmLink_ACDetectObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                       sizeof(AlgorithmLink_ACDetectObj), 32);
    }
    else
    {
    	pACDetectObj = (AlgorithmLink_ACDetectObj *)
                        malloc(sizeof(AlgorithmLink_ACDetectObj));
    }

    UTILS_assert(pACDetectObj!=NULL);

    pAlgCreateParams = &pACDetectObj->algCreateParams;

    pOutputQInfo = &pACDetectObj->outputQInfo[0];
    pInputQInfo  = &pACDetectObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pACDetectObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pACDetectObj->algLinkCreateParams),
           (void*)(pACDetectLinkCreateParams),
           sizeof(AlgorithmLink_ACDetectCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of automatic corner detection
     * algorithm link
     */
    numInputQUsed     = ALGLINK_ACDETECT_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_ACDETECT_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo[ALGLINK_ACDETECT_IPQID_MULTIVIEW].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_ACDETECT_OPQID_FEATURE].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_ACDETECT_OPQID_FEATURE].queInfo.numCh = numChannelsUsed;

    inputQId  = ALGLINK_ACDETECT_IPQID_MULTIVIEW;

    /* previous link info */
    status = System_linkGetInfo(
                pACDetectLinkCreateParams->inQueParams[inputQId].prevLinkId,
                &prevLinkInfo);

    prevLinkQueId =
        pACDetectLinkCreateParams->inQueParams[inputQId].prevLinkQueId;
    pPrevChInfo   =
        &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    prevChInfoFlags    = pPrevChInfo->flags;
    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(NULL);
    }

    pACDetectObj->dataFormat = dataFormat;
    pACDetectObj->inPitch[0] = pPrevChInfo->pitch[0];
    pACDetectObj->inPitch[1] = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pACDetectObj->algLinkCreateParams.maxInputWidth)
       ||
       (pPrevChInfo->height > pACDetectObj->algLinkCreateParams.maxInputHeight)
      )
    {
      UTILS_assert(NULL);
    }

    /*
     * Channel info population for output Q Id - ALGLINK_ACDETECT_OPQID_FEATURE
     * TBD - To check if anything in channel info is needed for meta data op
     */
    outputQId = ALGLINK_ACDETECT_OPQID_FEATURE;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;


    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                numInputQUsed,
                                pInputQInfo,
                                numOutputQUsed,
                                pOutputQInfo
                                );
    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */


   //Creation parameters for Automatic corner detect

    UTILS_assert(pACDetectLinkCreateParams->maxInputHeight <=
    				ACDETECT_LINK_INPUT_FRAME_HEIGHT);
    UTILS_assert(pACDetectLinkCreateParams->maxInputWidth <=
    				ACDETECT_LINK_INPUT_FRAME_WIDTH);
    /*
    UTILS_assert(pACDetectLinkCreateParams->maxOutputHeight <=
                    SV_ALGLINK_OUTPUT_FRAME_HEIGHT);
    UTILS_assert(pACDetectLinkCreateParams->maxOutputWidth <=
                    SV_ALGLINK_OUTPUT_FRAME_WIDTH);
    */

    pAlgCreateParams->SVInCamFrmHeight =
    	pACDetectLinkCreateParams->maxInputHeight;
    pAlgCreateParams->SVInCamFrmWidth =
    	pACDetectLinkCreateParams->maxInputWidth;
    /*
    pAlgCreateParams->SVOutDisplayHeight =
    	pACDetectLinkCreateParams->maxOutputHeight;
    pAlgCreateParams->SVOutDisplayWidth =
    	pACDetectLinkCreateParams->maxOutputWidth;
    */
    pAlgCreateParams->numCameras =
    	pACDetectLinkCreateParams->numViews;

    //To be updated by Pavan, these three parameters should be consistent for All three algorithms, therefore should be passed in
    pAlgCreateParams->numColorChannels      = 3;
    pAlgCreateParams->DMAblockSizeV         = 40;
    pAlgCreateParams->DMAblockSizeH         = 40;

    pAlgCreateParams->saladbowlFocalLength  = 8000;
    pAlgCreateParams->defaultFocalLength    =
    		pACDetectObj->algLinkCreateParams.defaultFocalLength;

    if (pACDetectLinkCreateParams->is2mp == TRUE)
    {
        pAlgCreateParams->SVROIWidth = 1920;
        pAlgCreateParams->SVROIHeight = 1080;
        pAlgCreateParams->binarizeOffset = 80;
        pAlgCreateParams->borderOffset = 80;
        pAlgCreateParams->smallestCenter = 10;
        pAlgCreateParams->largestCenter = 50;
        pAlgCreateParams->maxWinWidth = 400;
        pAlgCreateParams->maxWinHeight = 400;
        pAlgCreateParams->maxBandLen = 400;
        pAlgCreateParams->minBandLen = 4;
        pAlgCreateParams->minSampleInCluster = 16;
        pAlgCreateParams->firstROITop = 300;
        pAlgCreateParams->firstROIBottom = 1050;
        pAlgCreateParams->firstROILeft = 50;
        pAlgCreateParams->firstROIRight = 900;
        pAlgCreateParams->secondROITop = 300;
        pAlgCreateParams->secondROIBottom = 1050;
        pAlgCreateParams->secondROILeft = 950;
        pAlgCreateParams->secondROIRight = 1870;
    }
    else
    {
        pAlgCreateParams->SVROIWidth = 1280;
        pAlgCreateParams->SVROIHeight = 720;
        pAlgCreateParams->binarizeOffset = 75;
        pAlgCreateParams->borderOffset = 50;
        pAlgCreateParams->smallestCenter = 2;
        pAlgCreateParams->largestCenter = 50;
        pAlgCreateParams->maxWinWidth = 180;
        pAlgCreateParams->maxWinHeight = 180;
        pAlgCreateParams->maxBandLen = 160;
        pAlgCreateParams->minBandLen = 2;
        pAlgCreateParams->minSampleInCluster = 4;
        pAlgCreateParams->firstROITop = 150;
        pAlgCreateParams->firstROIBottom = 670;
        pAlgCreateParams->firstROILeft = 100;
        pAlgCreateParams->firstROIRight = 600;
        pAlgCreateParams->secondROITop = 150;
        pAlgCreateParams->secondROIBottom = 670;
        pAlgCreateParams->secondROILeft = 700;
        pAlgCreateParams->secondROIRight = 1200;
    }

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_AutoChartDetectMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_AutoChartDetectMemQuery(pAlgCreateParams, &memRequests, 0);
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

    Cache_inv(
            pAlgCreateParams->pLensPrm,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    pAlgCreateParams->pLensPrm = pACDetectLinkCreateParams->pLensPrm;

    algHandle = Alg_AutoChartDetectCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pACDetectObj->algHandle = algHandle;

    /*
     * Creation of output buffers for output Qs
     *  - Connecting metadata buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    outputQId = ALGLINK_ACDETECT_OPQID_FEATURE;
    channelId = 0;

    for(frameIdx = 0;
        frameIdx < pACDetectObj->algLinkCreateParams.numOutput;
        frameIdx++)
    {
        pSystemBuffer         =
                             &(pACDetectObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =
                             &(pACDetectObj->featurePoints[outputQId][frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        metaBufSize = ACDETECT_LINK_FEATUREPOINT_SIZE;

        pSystemMetaDataBuffer->numMetaDataPlanes = 1;
        pSystemMetaDataBuffer->bufAddr[0] =  Utils_memAlloc(
                                                UTILS_HEAPID_DDR_CACHED_SR,
                                                metaBufSize,
                                                ALGORITHMLINK_FRAME_ALIGN);
        pSystemMetaDataBuffer->metaBufSize[0]    = metaBufSize;
        pSystemMetaDataBuffer->metaFillLength[0] = metaBufSize;
        pSystemMetaDataBuffer->flags             = 0;

        UTILS_assert(pSystemMetaDataBuffer->bufAddr[0] != NULL);

        AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
    }



    pACDetectObj->frameDropCounter          = 0;

    pACDetectObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
    		AlgorithmLink_getLinkId(pObj), "ALG_ACDETECT");
    UTILS_assert(NULL != pACDetectObj->linkStatsInfo);

    pACDetectObj->numInputChannels = 1;

    pACDetectObj->isFirstFrameRecv   = FALSE;
    pACDetectObj->isFirstOPGenerated = FALSE;

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
Int32 AlgorithmLink_acDetectProcess(void * pObj)
{

    AlgorithmLink_ACDetectObj  * pACDetectObj;
    void                       * algHandle;
    AlgorithmLink_ACDetectInputQueId    inputQId;
    AlgorithmLink_ACDetectOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    Int32                        inputStatus;
    UInt32                       bufId;
    UInt32                       viewId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferFeaturePt;
    //System_Buffer              * pSysBufferGACornerLoc;
    System_Buffer              * pSystemBufferMultiview;
    Bool                         bufDropFlag;
    System_MetaDataBuffer      * pFeaturePtBuffer;
    //System_MetaDataBuffer        tmpGACornerLocBuffer; /* To avoid KW error */
    //System_MetaDataBuffer      * pGACornerLocBuffer = &tmpGACornerLocBuffer;
    //System_MetaDataBuffer      * pGASGXLUTBuffer;
    //void                       * pGASGXLUTBufAddr;
    UInt32                       acDetectMode = 0;
    Bool                         algoProcessCallNeeded;

    System_VideoFrameCompositeBuffer    * pCompositeBuffer;
    AlgorithmLink_ACDetectCreateParams  * pACDetectLinkCreateParams;
    System_LinkStatistics	   * linkStatsInfo;

    pACDetectObj = (AlgorithmLink_ACDetectObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pACDetectObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                 = pACDetectObj->algHandle;
    pACDetectLinkCreateParams = (AlgorithmLink_ACDetectCreateParams *)
                                    &pACDetectObj->algLinkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);



    if(pACDetectObj->isFirstFrameRecv==FALSE)
    {
    	pACDetectObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pACDetectObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_ACDETECT_IPQID_MULTIVIEW and process them if output is
     * available
     */
    inputQId = ALGLINK_ACDETECT_IPQID_MULTIVIEW;

    System_getLinksFullBuffers(
        pACDetectLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pACDetectLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
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
    		 * TBD - Currently this link will call algorithm only once for first
    		 * frame. Logic needs to change in future.
    		 */

    		/*
    		 * For frame to be processed:
    		 *  - Output buffer will be queried
    		 *  - If output buffer is available, then algorithm will be called
    		 */

    		if(pACDetectObj->isFirstOPGenerated == FALSE &&
    				inputStatus == SYSTEM_LINK_STATUS_SOK)
    		{

    			outputQId = ALGLINK_ACDETECT_OPQID_FEATURE;
    			channelId = 0;
    			status = AlgorithmLink_getEmptyOutputBuffer(
    												pObj,
    												outputQId,
    												channelId,
    												&pSysBufferFeaturePt);


    			if(status != SYSTEM_LINK_STATUS_SOK)
    			{
    				/*
    				 * If output buffer is not available, then input buffer
    				 * is just returned back
    				 */
    				linkStatsInfo->linkStats.outBufErrorCount++;
    			}
    			else
    			{
    				pSysBufferFeaturePt->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
    				pSysBufferFeaturePt->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
    				pFeaturePtBuffer = (System_MetaDataBuffer *)pSysBufferFeaturePt->payload;

    				for(viewId = 0; viewId < ACDETECT_LINK_MAX_NUM_VIEWS; viewId++)
    				{
    					Cache_inv(pCompositeBuffer->bufAddr[0][viewId],
    							(ACDETECT_LINK_INPUT_FRAME_WIDTH*ACDETECT_LINK_INPUT_FRAME_HEIGHT),
    							Cache_Type_ALLD, TRUE);
    					Cache_inv(pCompositeBuffer->bufAddr[1][viewId],
    							((ACDETECT_LINK_INPUT_FRAME_WIDTH*ACDETECT_LINK_INPUT_FRAME_HEIGHT)/2),
    							Cache_Type_ALLD, TRUE);
    				}

    				switch (pACDetectObj->algLinkCreateParams.acDetectParams.acDetectMode)
    				{
    					default:
    					case ALGLINK_ACDETECT_MODE_SKIP:
    						acDetectMode = 0;
    						algoProcessCallNeeded = TRUE;
    						pACDetectObj->isFirstOPGenerated = TRUE;
    						break;

    					case ALGLINK_ACDETECT_MODE_ENABLE:
    						acDetectMode = 0;
    						algoProcessCallNeeded = FALSE;
    						if(linkStatsInfo->linkStats.newDataCmdCount >
    							pACDetectObj->algLinkCreateParams.ignoreFirstNFrames)
    						{
    							acDetectMode = 1;
    							algoProcessCallNeeded = TRUE;
    							pACDetectObj->isFirstOPGenerated = TRUE;
    						}
    						break;

    					// to add
    					/*
       					case ALGLINK_ACDETECT_MODE_DEFAULT:
       						algoProcessCallNeeded = FALSE;


       						memcpy(pGALUTBuffer->bufAddr[0],
       							   pGAlignLinkCreateParams->calParams.gaLUTDDRPtr,
       							   pGALUTBuffer->metaBufSize[0]
       						);

       						pACDetectObj->isFirstOPGenerated = TRUE;
       						break;
       					*/

    				}

    				if(algoProcessCallNeeded == TRUE)
    				{
    					status = Alg_AutoChartDetectProcess(
                             algHandle,
                             pCompositeBuffer,
                             &pACDetectObj->inPitch[0],
                             pFeaturePtBuffer->bufAddr[0],
                             acDetectMode);


    					//UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


    					Cache_wb(pFeaturePtBuffer->bufAddr[0],
    							pFeaturePtBuffer->metaBufSize[0],
    							Cache_Type_ALLD,
    							TRUE);

    					Utils_updateLatency(&linkStatsInfo->linkLatency,
    										pSysBufferFeaturePt->linkLocalTimestamp);
    					Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
    										pSysBufferFeaturePt->srcTimestamp);


    				if (status == SYSTEM_LINK_STATUS_SOK)
    				{
    					/*
    					 * For acDetectMode of 1, auto chart detect algorithm will generate
    					 * new feature points, storing them in use case provided buffers
    					 *  1. Feature points are copied here
    					 */
    					if(acDetectMode == 1)
    					{
    						memcpy(pACDetectLinkCreateParams->acDetectParams.featurePtDDRPtr,
    								pFeaturePtBuffer->bufAddr[0],
    								pFeaturePtBuffer->metaBufSize[0]);

    						Cache_wb(pACDetectLinkCreateParams->acDetectParams.featurePtDDRPtr,
    								pFeaturePtBuffer->metaBufSize[0],
    								Cache_Type_ALLD,
    								TRUE);
    					}


    					linkStatsInfo->linkStats.chStats
    						[pSystemBufferMultiview->chNum].inBufProcessCount++;
    					linkStatsInfo->linkStats.chStats
    						[pSystemBufferMultiview->chNum].outBufCount[0]++;


    					/* ==============================================================*/
    					/* Feature points */
    					/* ===============================================================*/
    					/*
    					 * Putting filled buffer into output full buffer for
    					 * outputQId = ALGLINK_ACDETECT_OPQID_FEATURE
    					 */
    					outputQId = ALGLINK_ACDETECT_OPQID_FEATURE;
    					status    = AlgorithmLink_putFullOutputBuffer(pObj,
    																 outputQId,
    																 pSysBufferFeaturePt);

    					UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    					/*
    					 * Informing next link that a new data has been put for its
    					 * processing
    					 */
    					System_sendLinkCmd(
    							pACDetectLinkCreateParams->outQueParams[outputQId].nextLink,
    							SYSTEM_CMD_NEW_DATA,
    							NULL);

    					/*
    					 * Releasing (Free'ing) output buffers, since algorithm does not need
    					 * it for any future usage.
    					 */

    					outputBufListReturn.numBuf     = 1;
    					outputBufListReturn.buffers[0] = pSysBufferFeaturePt;
    					AlgorithmLink_releaseOutputBuffer(pObj,
    													  outputQId,
    													  &outputBufListReturn);
    				}
    				else
    				{
						Vps_printf("======================");
						Vps_printf("!!!!AUTOCALIB FAIL!!!!");
						Vps_printf("======================");
						Vps_printf("Autocalib Error: Pattern not detected --> abort");
						AlgorithmLink_putEmptyOutputBuffer(pObj,
						    					        outputQId,
						    					        pSysBufferFeaturePt);
    				}
    			}
    			else
    			{
					AlgorithmLink_putEmptyOutputBuffer(pObj,
						    					        outputQId,
						    					        pSysBufferFeaturePt);
    				bufDropFlag = FALSE;
    			}
    		}

    		} /* if(pACDetectObj->isFirstOPGenerated == FALSE) */

    		/*
    		 * Releasing (Free'ing) Input buffers, since algorithm does not need
    		 * it for any future usage.
    		 */
    		inputQId                      = ALGLINK_ACDETECT_IPQID_MULTIVIEW;
    		inputBufListReturn.numBuf     = 1;
    		inputBufListReturn.buffers[0] = pSystemBufferMultiview;
    		AlgorithmLink_releaseInputBuffer(
    										pObj,
    										inputQId,
    										pACDetectLinkCreateParams->inQueParams[inputQId].prevLinkId,
    										pACDetectLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
    										&inputBufListReturn,
    										&bufDropFlag);
        }

    }

    return status;

}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for auto chart detect algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_acDetectControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_ACDetectObj      * pACDetectObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pACDetectObj = (AlgorithmLink_ACDetectObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pACDetectObj->algHandle;

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
        	AlgorithmLink_acDetectPrintStatistics(pObj, pACDetectObj);
            break;

        default:
            status = Alg_AutoChartDectectControl(algHandle,
                                                &(pACDetectObj->controlParams)
                                                );
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
Int32 AlgorithmLink_acDetectStop(void * pObj)
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
Int32 AlgorithmLink_acDetectDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       metaBufSize;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_ACDetectObj       * pACDetectObj;
    UInt32                            memTabId;
    AlgorithmLink_ACDetectOutputQueId outputQId;

    pACDetectObj = (AlgorithmLink_ACDetectObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pACDetectObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_AutoChartDetectDelete(pACDetectObj->algHandle, &memRequests);

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

    /*
     * Deletion of output buffers for output Qs
     */
    outputQId = ALGLINK_ACDETECT_OPQID_FEATURE;
    for(frameIdx = 0;
    	frameIdx < pACDetectObj->algLinkCreateParams.numOutput;
    	frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pACDetectObj->featurePoints[outputQId][frameIdx]);

        metaBufSize = ACDETECT_LINK_FEATUREPOINT_SIZE;

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                metaBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }


    /*
     * Space for Algorithm specific object gets freed here.
     */
    if(sizeof(AlgorithmLink_ACDetectObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pACDetectObj,
                               sizeof(AlgorithmLink_ACDetectObj));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        free(pACDetectObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pACDetectObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_acDetectPrintStatistics(void *pObj,
                       AlgorithmLink_ACDetectObj *pACDetectObj)
{
    UTILS_assert(NULL != pACDetectObj->linkStatsInfo);

    Utils_printLinkStatistics(&pACDetectObj->linkStatsInfo->linkStats, "ALG_ACDETECT", TRUE);

    Utils_printLatency("ALG_ACDETECT",
                       &pACDetectObj->linkStatsInfo->linkLatency,
                       &pACDetectObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
