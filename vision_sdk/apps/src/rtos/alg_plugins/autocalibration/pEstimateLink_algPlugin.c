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
//#include "svAlgLink_priv.h"
#include "pEstimateLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/alg_plugins/commonutils/lens_distortion_correction/ldc_config.h>

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
Int32 AlgorithmLink_pEstimate_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_pEstimateCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_pEstimateProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_pEstimateControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_pEstimateStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_pEstimateDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_POSE_ESTIMATE;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for pose estimate alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pEstimateCreate(void * pObj, void * pCreateParams)
{
    void                       * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    //System_Buffer              * pSystemBufferCornerLoc;
    //System_MetaDataBuffer      * pSystemMetaDataBufferCornerLoc;
    System_LinkInfo              prevLinkInfo;
    AlgorithmLink_PEstimateOutputQueId   outputQId;
    AlgorithmLink_PEstimateInputQueId    inputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    //UInt32                       prevLinkQueId;
    UInt32                       metaBufSize;
    //UInt32                       dataFormat;
    System_LinkChInfo          * pOutChInfo;
    //System_LinkChInfo          * pPrevChInfo;
    //UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_PEstimateObj           * pPEstimateObj;
    AlgorithmLink_PEstimateCreateParams  * pPEstimateLinkCreateParams;
    SV_PEstimate_CreationParamsStruct    * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;

    pPEstimateLinkCreateParams =
        (AlgorithmLink_PEstimateCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    if(sizeof(AlgorithmLink_PEstimateObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
    	pPEstimateObj = (AlgorithmLink_PEstimateObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                       sizeof(AlgorithmLink_PEstimateObj), 32);
    }
    else
    {
    	pPEstimateObj = (AlgorithmLink_PEstimateObj *)
                        malloc(sizeof(AlgorithmLink_PEstimateObj));
    }

    UTILS_assert(pPEstimateObj!=NULL);

    pAlgCreateParams = &pPEstimateObj->algCreateParams;

    pOutputQInfo = &pPEstimateObj->outputQInfo[0];
    pInputQInfo  = &pPEstimateObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pPEstimateObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pPEstimateObj->algLinkCreateParams),
           (void*)(pPEstimateLinkCreateParams),
           sizeof(AlgorithmLink_PEstimateCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of pose estimate
     * algorithm link
     */
    numInputQUsed     = ALGLINK_PESTIMATE_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_PESTIMATE_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo[ALGLINK_PESTIMATE_IPQID_FEATURE].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_PESTIMATE_OPQID_CALMAT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_PESTIMATE_OPQID_CALMAT].queInfo.numCh = numChannelsUsed;

    inputQId  = ALGLINK_PESTIMATE_IPQID_FEATURE;

    /* previous link info */
    status = System_linkGetInfo(
                pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkId,
                &prevLinkInfo);

    // may not needed
    /*
    prevLinkQueId =
        pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkQueId;
    pPrevChInfo   =
        &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    prevChInfoFlags    = pPrevChInfo->flags;


    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(NULL);
    }

    pGAlignObj->dataFormat = dataFormat;
    pGAlignObj->inPitch[0] = pPrevChInfo->pitch[0];
    pGAlignObj->inPitch[1] = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pGAlignObj->algLinkCreateParams.maxInputWidth)
       ||
       (pPrevChInfo->height > pGAlignObj->algLinkCreateParams.maxInputHeight)
      )
    {
      UTILS_assert(NULL);
    }
   */


    /*
     * Channel info population for output Q Id - ALGLINK_PESTIMATE_OPQID_CALMAT
     * TBD - To check if anything in channel info is needed for meta data op
     */
    outputQId = ALGLINK_PESTIMATE_OPQID_CALMAT;
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

    UTILS_assert(pPEstimateLinkCreateParams->maxInputHeight <=
    				PESTIMATE_LINK_INPUT_FRAME_HEIGHT);
    UTILS_assert(pPEstimateLinkCreateParams->maxInputWidth <=
    				PESTIMATE_LINK_INPUT_FRAME_WIDTH);
    /*
    UTILS_assert(pGAlignLinkCreateParams->maxOutputHeight <=
                    SV_ALGLINK_OUTPUT_FRAME_HEIGHT);
    UTILS_assert(pGAlignLinkCreateParams->maxOutputWidth <=
                    SV_ALGLINK_OUTPUT_FRAME_WIDTH);
    */

    pAlgCreateParams->SVInCamFrmHeight =
    		pPEstimateLinkCreateParams->maxInputHeight;
    pAlgCreateParams->SVInCamFrmWidth =
    		pPEstimateLinkCreateParams->maxInputWidth;
    /*
    pAlgCreateParams->SVOutDisplayHeight =
        pGAlignLinkCreateParams->maxOutputHeight;
    pAlgCreateParams->SVOutDisplayWidth =
        pGAlignLinkCreateParams->maxOutputWidth;
    */
    pAlgCreateParams->numCameras =
        pPEstimateLinkCreateParams->numViews;

    /*
    pAlgCreateParams->numColorChannels      = 3;
    pAlgCreateParams->DMAblockSizeV         = 40;
    pAlgCreateParams->DMAblockSizeH         = 40;

    pAlgCreateParams->saladbowlFocalLength  = 8000;
    */
    pAlgCreateParams->defaultFocalLength    =
    		pPEstimateObj->algLinkCreateParams.defaultFocalLength;
    /*
    if (pGAlignLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
    {
       pAlgCreateParams->subsampleratio        = 2;
    }
    else
    {
       pAlgCreateParams->subsampleratio        = 4;
    }
    */

    /*
    pAlgCreateParams->outputMode = pGAlignLinkCreateParams->svOutputMode; //2D or 2D
    pAlgCreateParams->enablePixelsPerCm = pGAlignLinkCreateParams->enablePixelsPerCm; //use PixelsPerCm output ? 1-yes, 0-no
    pAlgCreateParams->useDefaultPixelsPerCm = 1; //use default PixelPerCm values ? 1-yes, 0-no

    pAlgCreateParams->GAlignTuningParams.max_num_features = 100;
    pAlgCreateParams->GAlignTuningParams.min_match_score  = -10;
    pAlgCreateParams->GAlignTuningParams.max_BRIEF_score  = 100;
    pAlgCreateParams->GAlignTuningParams.min_distBW_feats = 10;
    //pAlgCreateParams->GAlignTuningParams.downsamp_ratio   = 2;
    pAlgCreateParams->downsamp_ratio        = 2;

    pAlgCreateParams->svCarBoxParams.CarBoxCenter_x =
        (pAlgCreateParams->SVOutDisplayWidth / 2);
    pAlgCreateParams->svCarBoxParams.CarBoxCenter_y =
        (pAlgCreateParams->SVOutDisplayHeight / 2);
    pAlgCreateParams->svCarBoxParams.CarBox_height =
    		pGAlignLinkCreateParams->carBoxHeight;
    pAlgCreateParams->svCarBoxParams.CarBox_width =
    		pGAlignLinkCreateParams->carBoxWidth;
   */

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_PoseEstimateMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_PoseEstimateMemQuery(pAlgCreateParams, &memRequests, 0);
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

    pAlgCreateParams->pLensPrm = pPEstimateLinkCreateParams->pLensPrm;

    algHandle = Alg_PoseEstimateCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pPEstimateObj->algHandle = algHandle;

    /*
     * Creation of output buffers for output Qs
     *  - Connecting metadata buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    outputQId = ALGLINK_PESTIMATE_OPQID_CALMAT;
    channelId = 0;

    for(frameIdx = 0;
        frameIdx < pPEstimateObj->algLinkCreateParams.numOutput;
        frameIdx++)
    {
        pSystemBuffer         =
                             &(pPEstimateObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =
                             &(pPEstimateObj->calibMat[outputQId][frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        metaBufSize = PESTIMATE_LINK_CALMAT_SIZE;

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



    pPEstimateObj->frameDropCounter          = 0;

    pPEstimateObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_PESTIMATE");
    UTILS_assert(NULL != pPEstimateObj->linkStatsInfo);

    pPEstimateObj->numInputChannels = 1;

    pPEstimateObj->isFirstFrameRecv   = FALSE;
    pPEstimateObj->isFirstOPGenerated = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of pose estimate algorithm link
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
Int32 AlgorithmLink_pEstimateProcess(void * pObj)
{

	AlgorithmLink_PEstimateObj * pPEstimateObj;
    void                       * algHandle;
    AlgorithmLink_PEstimateInputQueId    inputQId;
    AlgorithmLink_PEstimateOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    //Int32                        inputStatus;
    UInt32                       bufId;
    //UInt32                       viewId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferCalMat;
    //System_Buffer              * pSysBufferGACornerLoc;
    //System_Buffer              * pSysBufferGASGXLUT;
    //System_Buffer              * pSystemBufferMultiview;
    Bool                         bufDropFlag;
    System_MetaDataBuffer      * pFeaturePtBuffer;
    System_MetaDataBuffer      * pCalMatBuffer;
    //System_MetaDataBuffer        tmpGACornerLocBuffer; /* To avoid KW error */
    //System_MetaDataBuffer      * pGACornerLocBuffer = &tmpGACornerLocBuffer;
    //System_MetaDataBuffer      * pGASGXLUTBuffer;
    //void                       * pGASGXLUTBufAddr;
    UInt32                       pEstimateMode = 0;
    Bool                         algoProcessCallNeeded;

    //System_VideoFrameCompositeBuffer     * pCompositeBuffer;
    AlgorithmLink_PEstimateCreateParams  * pPEstimateLinkCreateParams;
    System_LinkStatistics	   * linkStatsInfo;

    pPEstimateObj = (AlgorithmLink_PEstimateObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pPEstimateObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);


    algHandle               = pPEstimateObj->algHandle;
    pPEstimateLinkCreateParams = (AlgorithmLink_PEstimateCreateParams *)
                                    &pPEstimateObj->algLinkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);



    if(pPEstimateObj->isFirstFrameRecv==FALSE)
    {
    	pPEstimateObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pPEstimateObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_GALIGN_IPQID_MULTIVIEW and process them if output is
     * available
     */
    inputQId = ALGLINK_PESTIMATE_IPQID_FEATURE;

    System_getLinksFullBuffers(
        pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {

    	Vps_printf("========= Get INPUT LINK for pose estimation\n");
    	for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
    	{
            /*
             * At any point in time, Pose Estimate link will hold only one set of feature Pts.
             * So whenever feature Pts are received, the previously received ones
             * will be released and the newly received one will be archived.
             */
    		/*
            if(pPEstimateObj->receivedFeaturePtsFlag == TRUE)
            {
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pPEstimateObj->sysBufferFeaturePts;
                bufDropFlag = FALSE;

                AlgorithmLink_releaseInputBuffer(
                    pObj,
                    inputQId,
                    pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkId,
                    pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                    &inputBufListReturn,
                    &bufDropFlag);

                pPEstimateObj->receivedFeaturePtsFlag = FALSE;
            }
            */

            pPEstimateObj->sysBufferFeaturePts = inputBufList.buffers[bufId];
            pFeaturePtBuffer = (System_MetaDataBuffer *) pPEstimateObj->sysBufferFeaturePts->payload;

            bufDropFlag = TRUE;
            /*TBD: Check for parameter correctness. If in error, return input*/
            /*
            pPEstimateObj->receivedFeaturePtsFlag = TRUE;
			*/

    		/*
    		 * TBD - Currently this link will call algorithm only once for first
    		 * frame. Logic needs to change in future.
    		 */

            /*
             * For frame to be processed:
             *  - Output buffer will be queried
             *  - If output buffer is available, then algorithm will be called
             */

            if(pPEstimateObj->isFirstOPGenerated == FALSE)
            {
            	outputQId = ALGLINK_PESTIMATE_OPQID_CALMAT;
            	channelId = 0;
            	status = AlgorithmLink_getEmptyOutputBuffer(
            												pObj,
            												outputQId,
            												channelId,
            												&pSysBufferCalMat);


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
            		pSysBufferCalMat->srcTimestamp = pPEstimateObj->sysBufferFeaturePts->srcTimestamp;
            		pSysBufferCalMat->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
            		pCalMatBuffer = (System_MetaDataBuffer *)pSysBufferCalMat->payload;


            		switch (pPEstimateObj->algLinkCreateParams.pEstimateParams.pEstimateMode)
            		{
            			default:
            			case ALGLINK_PESTIMATE_MODE_SKIP:
            				pEstimateMode = 0;
            				algoProcessCallNeeded = TRUE;
            				pPEstimateObj->isFirstOPGenerated = TRUE;
            				break;

            			case ALGLINK_PESTIMATE_MODE_ENABLE:
            				pEstimateMode = 1;
            				algoProcessCallNeeded = TRUE;
            				pPEstimateObj->isFirstOPGenerated = TRUE;
    						break;

    				    // to add
    				    /*
            			case ALGLINK_PESTIMATE_MODE_DEFAULT:
       						algoProcessCallNeeded = FALSE;

       						memcpy(pCalMatBuffer->bufAddr[0],
       							   pPEstimateLinkCreateParams->calParams.gaLUTDDRPtr,
       							   pCalMatBuffer->metaBufSize[0]
       						);

       						pPEstimateObj->isFirstOPGenerated = TRUE;
       						break;
       					*/

            		}

            		if(algoProcessCallNeeded == TRUE)
            		{
            			status = Alg_PoseEstimateProcess(algHandle,
            											 pCalMatBuffer->bufAddr[0],
            											 pFeaturePtBuffer->bufAddr[0], // pPEstimateObj->sysBufferFeaturePts->payload,
            											 pEstimateMode);


            			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


            			Cache_wb(pCalMatBuffer->bufAddr[0],
            					pCalMatBuffer->metaBufSize[0],
            					Cache_Type_ALLD,
            					TRUE);

            			Utils_updateLatency(&linkStatsInfo->linkLatency,
            								pSysBufferCalMat->linkLocalTimestamp);
            			Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
            								pSysBufferCalMat->srcTimestamp);

            			/*
            			 * For pEstimateMode of 1, pose estimation algo will generate new calibration matrix
            			 * calibration matrix, Storing these tables in use case provided buffers
            			 *  1. Calibration matrix is copied here
            			 */
            			if(pEstimateMode == 1)
            			{
            				memcpy(pPEstimateLinkCreateParams->pEstimateParams.pEstCalMatDRPtr,
            						pCalMatBuffer->bufAddr[0],
            						pCalMatBuffer->metaBufSize[0]);

            				Cache_wb(pPEstimateLinkCreateParams->pEstimateParams.pEstCalMatDRPtr,
            						pCalMatBuffer->metaBufSize[0],
            						Cache_Type_ALLD,
            						TRUE);
            			}

            			/*
    					pGAlignObj->linkStats.chStats[pSystemBufferMultiview->chNum].inBufProcessCount++;
    					pGAlignObj->linkStats.chStats[pSystemBufferMultiview->chNum].outBufCount[0]++;
            			 */

            			/* ===============================================================*/
            			/* Calibration matrix */
            			/* ===============================================================*/
            			/*
            			 * Putting filled buffer into output full buffer for
            			 * outputQId = ALGLINK_PESTIMATE_OPQID_CALMAT
            			 */
            			outputQId = ALGLINK_PESTIMATE_OPQID_CALMAT;
            			status    = AlgorithmLink_putFullOutputBuffer(pObj,
            														outputQId,
            														pSysBufferCalMat);

            			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            			/*
            			 * Informing next link that a new data has been put for its
            			 * processing
            			 */
            			System_sendLinkCmd(
            						pPEstimateLinkCreateParams->outQueParams[outputQId].nextLink,
    								SYSTEM_CMD_NEW_DATA,
    								NULL);

            			/*
            			 * Releasing (Free'ing) output buffers, since algorithm does not need
            			 * it for any future usage.
            			 */
            			outputBufListReturn.numBuf     = 1;
            			outputBufListReturn.buffers[0] = pSysBufferCalMat;
            			AlgorithmLink_releaseOutputBuffer(pObj,
            											outputQId,
            											&outputBufListReturn);

            			Vps_printf("============== released CalMat in pEstimateLin_AlgPlugnin\n");
            			printf("============== released CalMat in pEstimateLin_AlgPlugnin\n");
            		} else
            		{
    					AlgorithmLink_putEmptyOutputBuffer(pObj,
    					        						  outputQId,
    					        						  pSysBufferCalMat);
            		}


    				bufDropFlag = FALSE;
            	}

            } /* if(pPEstimateObj->isFirstOPGenerated == FALSE) */

            /*
             * Releasing (Free'ing) Input buffers, since algorithm does not need
             * it for any future usage.
             */
            inputQId                      = ALGLINK_PESTIMATE_IPQID_FEATURE;
            inputBufListReturn.numBuf     = 1;
            inputBufListReturn.buffers[0] = pPEstimateObj->sysBufferFeaturePts;
            AlgorithmLink_releaseInputBuffer(
            								pObj,
            								inputQId,
            								pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkId,
            								pPEstimateLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
            								&inputBufListReturn,
            								&bufDropFlag);

    	}

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for pose estimate algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_pEstimateControl(void * pObj, void * pControlParams)
{
	AlgorithmLink_PEstimateObj     * pPEstimteObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pPEstimteObj = (AlgorithmLink_PEstimateObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pPEstimteObj->algHandle;

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
        	AlgorithmLink_pEstimatePrintStatistics(pObj, pPEstimteObj);
            break;

        default:
            status = Alg_PoseEstimateControl(algHandle,
                                            &(pPEstimteObj->controlParams)
                                            );
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for pose estimate algorithm link
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
Int32 AlgorithmLink_pEstimateStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for pose estimate algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pEstimateDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       metaBufSize;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_PEstimateObj         * pPEstimateObj;
    UInt32                               memTabId;
    AlgorithmLink_PEstimateOutputQueId   outputQId;


    pPEstimateObj = (AlgorithmLink_PEstimateObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pPEstimateObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_PoseEstimateDelete(pPEstimateObj->algHandle, &memRequests);

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
    outputQId = ALGLINK_PESTIMATE_OPQID_CALMAT;
    for(frameIdx = 0;
        frameIdx < pPEstimateObj->algLinkCreateParams.numOutput;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pPEstimateObj->calibMat[outputQId][frameIdx]);

        metaBufSize = PESTIMATE_LINK_CALMAT_SIZE;

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                metaBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }


    /*
     * Space for Algorithm specific object gets freed here.
     */
    if(sizeof(AlgorithmLink_PEstimateObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pPEstimateObj,
                               sizeof(AlgorithmLink_PEstimateObj));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        free(pPEstimateObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pGAlignObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pEstimatePrintStatistics(void *pObj,
                       AlgorithmLink_PEstimateObj *pPEstimateObj)
{
	UTILS_assert(NULL != pPEstimateObj->linkStatsInfo);

    Utils_printLinkStatistics(&pPEstimateObj->linkStatsInfo->linkStats, "ALG_PESTIMATE", TRUE);

    Utils_printLatency("ALG_PESTIMATE",
                       &pPEstimateObj->linkStatsInfo->linkLatency,
                       &pPEstimateObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
