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
 * \file synthesisLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for synthesis Link
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "stitchingLink_priv.h"
#include "CommonDefs.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

// RSVP Function calls
void Utils_rvpTda3xLdcLutInit();
void Utils_rvpTda3xLdcLutDeInit();

#define ALGLINK_OUTPUT_FRAME_WIDTH  (2600)
#define ALGLINK_OUTPUT_FRAME_HEIGHT (1080)
#define ALGLINK_OUTPUT_FRAME_WIDTH2  (1920)
#define ALGLINK_OUTPUT_FRAME_HEIGHT2 (480)
#define ALGLINK_NUM_OUTPUT_FRAME_MULTIVIEW (3)
#define ALGLINK_NUM_OUTPUT_FRAME_DISPARITY (1)

#define ALGLINK_FRAME_WIDTH  (1920)

#define ALGLINK_FRAME_HEIGHT (480)

#define ENABLEINPUT (1)

#define ALGLINK_BLENDLUT_SIZE ((ALGLINK_OUTPUT_FRAME_HEIGHT2) * (ALGLINK_OUTPUT_FRAME_WIDTH2) *  (1.5) + 256) 

static const float InputCalibParams[] = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0};
static const uWord32 TempLUT[] = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0};	

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of image transform algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_Stitching_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_StitchingCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_StitchingProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_StitchingControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_StitchingStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_StitchingDelete;
        
#ifdef BUILD_DSP
    void Utils_rvpTda3xLdcLutInit(void);

    Utils_rvpTda3xLdcLutInit();

    algId = ALGORITHM_LINK_DSP_ALG_STITCHING;
#endif



    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for image transform algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StitchingCreate(void * pObj, void * pCreateParams)
{
	void                       * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32 frameIdx;
    System_Buffer              * pSystemBuffer;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer; 
    System_LinkInfo              prevLinkInfo;
    
    AlgorithmLink_StitchingOutputQueId   outputQId;
    AlgorithmLink_StitchingInputQueId    inputQId;	
    
    Int32                        channelId;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       dataFormat;
    System_LinkChInfo            * pOutChInfo;
    System_LinkChInfo            * pPrevChInfo;
    UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;
	UInt32 maxHeight,maxWidth;
	UInt32                       cnt;
    AlgorithmLink_StitchingObj             * pStitchingObj;
    AlgorithmLink_StitchingCreateParams    * pStitchingLinkCreateParams;
    RVP_Stitching_CreationParamsStruct     pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        		* pOutputQInfo;
    AlgorithmLink_InputQueueInfo         		* pInputQInfo;
    UInt32                                		  memTabId;

    UInt32 bufferSize;
	////////////////////////////////////////////////////////////////////
	// Allows pointer access to create parameters
    pStitchingLinkCreateParams = (AlgorithmLink_StitchingCreateParams *)pCreateParams;

    ////////////////////////////////////////////////////////////////////
    // Allocates object
    pStitchingObj = (AlgorithmLink_StitchingObj *)Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
																 sizeof(AlgorithmLink_StitchingObj), 64);
																			
	////////////////////////////////////////////////////////////////////
	// Check to see if object is NULL
    UTILS_assert(pStitchingObj!= NULL);
    UTILS_assert(ALGORITHM_LINK_MAX_VIEWS <= pStitchingLinkCreateParams->numCameras);
    
	////////////////////////////////////////////////////////////////////
	// Copy algorithm parameters pointers
    pAlgCreateParams = pStitchingObj->algCreateParams;

    pOutputQInfo = &pStitchingObj->outputQInfo[0];
    pInputQInfo  = &pStitchingObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pStitchingObj);
    
	////////////////////////////////////////////////////////////////////
    // Copy of needed create time parameters for the future. Need?
    memcpy(	(void*)(&pStitchingObj->algLinkCreateParams),
			(void*)(pStitchingLinkCreateParams),
			sizeof(AlgorithmLink_StitchingCreateParams));
			
    ////////////////////////////////////////////////////////////////////
    // Setup all queues
    numInputQUsed     = ALGLINK_STITCHING_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_STITCHING_OPQID_MAXOPQ;
    channelId         = 0;

    pInputQInfo[ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
	pInputQInfo[ALGLINK_STITCHING_IPQID_BLENDLUT].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED].queInfo.numCh = 1;
    ////////////////////////////////////////////////////////////////////
    // Setups individual input/output queues
    /** Multiview */ // There may be useless components in this
    {
    inputQId  = ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW;
	channelId = 0;
    status = System_linkGetInfo(	pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkId,
									&prevLinkInfo);
	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	prevLinkQueId = pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkQueId;								

	    pPrevChInfo   = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);
	
	    prevChInfoFlags    = pPrevChInfo->flags;
		
	    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);
	
	    if(dataFormat != SYSTEM_DF_YUV420SP_UV){
			UTILS_assert(NULL);}
	
	    pStitchingObj->inputPitch[0] = pPrevChInfo->pitch[0];
	    pStitchingObj->inputPitch[1] = pPrevChInfo->pitch[1];

		 if(	(pPrevChInfo->width > pStitchingObj->algLinkCreateParams.maxInputWidth) ||
			(pPrevChInfo->height > pStitchingObj->algLinkCreateParams.maxInputHeight)){
			UTILS_assert(NULL);}
	}
	 /** Disparity */
    {
    outputQId = ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED;
	channelId = 0;
    
    pPrevChInfo   = &(prevLinkInfo.queInfo[0].chInfo[channelId]);

    maxHeight = pStitchingObj->algLinkCreateParams.maxOutputHeight;
    maxWidth  = pStitchingObj->algLinkCreateParams.maxOutputWidth;

    UTILS_assert(maxWidth  <= ALGLINK_OUTPUT_FRAME_WIDTH);
    UTILS_assert(maxHeight <= ALGLINK_OUTPUT_FRAME_HEIGHT);

    pStitchingObj->outputPitch[0] = maxWidth; 
    pStitchingObj->outputPitch[1] = pStitchingObj->outputPitch[0];
    pStitchingObj->outputPitch[2] = pStitchingObj->outputPitch[0];

    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->startX = 0;
    pOutChInfo->startY = 0;
    pOutChInfo->width  = maxWidth;
    pOutChInfo->height = maxHeight;
    prevChInfoFlags    = pPrevChInfo->flags;
    pOutChInfo->flags  = prevChInfoFlags;

    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV){
		UTILS_assert(NULL);}

    pOutChInfo->pitch[0] = pStitchingObj->outputPitch[0];
    pOutChInfo->pitch[1] = pStitchingObj->outputPitch[1];
    pOutChInfo->pitch[2] = pStitchingObj->outputPitch[2];
    }
	////////////////////////////////////////////////////////////////////
    // Initializations needed for book keeping of buffer handling
    //  Note that this needs to be called only after setting inputQMode and outputQMode.
    status = AlgorithmLink_queueInfoInit(pObj, numInputQUsed, pInputQInfo, numOutputQUsed, pOutputQInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);                       
	////////////////////////////////////////////////////////////////////
    // Populates create time parameters
    pAlgCreateParams.RVPInCamFrmHeight    = 	pStitchingLinkCreateParams->maxInputHeight;
    pAlgCreateParams.RVPInCamFrmWidth     =	pStitchingLinkCreateParams->maxInputWidth;
    pAlgCreateParams.RVPOutDisplayHeight  =	pStitchingLinkCreateParams->maxOutputHeight;
    pAlgCreateParams.RVPOutDisplayWidth   =	pStitchingLinkCreateParams->maxOutputWidth;
    pAlgCreateParams.numCameras   		   =	pStitchingLinkCreateParams->numCameras;

    pAlgCreateParams.overlapBounds[0] = OVERLAP1_TOP1;
    pAlgCreateParams.overlapBounds[1] = OVERLAP1_TOP2;
    pAlgCreateParams.overlapBounds[2] = OVERLAP1_BOTTOM1;
    pAlgCreateParams.overlapBounds[3] = OVERLAP1_BOTTOM2;
    pAlgCreateParams.overlapBounds[4] = OVERLAP2_TOP1;
    pAlgCreateParams.overlapBounds[5] = OVERLAP2_TOP2;
    pAlgCreateParams.overlapBounds[6] = OVERLAP2_BOTTOM1;
    pAlgCreateParams.overlapBounds[7] = OVERLAP2_BOTTOM2;

    for (cnt = 0; cnt < pStitchingLinkCreateParams->numCameras + 1; cnt++)
        	{
        		pAlgCreateParams.Trans_RVP_width[cnt] = pAlgCreateParams.RVPOutDisplayWidth/2;
        		pAlgCreateParams.Trans_RVP_height[cnt] = pAlgCreateParams.RVPOutDisplayHeight;
        	}

    // Swapped channels 0 and 2 for mirror image RSVP output (10 Jan 2017 VAV)

	pAlgCreateParams.start_x_in_op[2] = 0;
	pAlgCreateParams.start_x_in_op[1] = pAlgCreateParams.RVPOutDisplayWidth / 4;
	pAlgCreateParams.start_x_in_op[0] = pAlgCreateParams.RVPOutDisplayWidth / 2;
	pAlgCreateParams.start_x_in_op[3] = pAlgCreateParams.RVPOutDisplayWidth / 4;
	pAlgCreateParams.start_x_in_op[4] = pAlgCreateParams.RVPOutDisplayWidth / 4;

    pStitchingObj->pInputCalibParams       = (float *)InputCalibParams;
    pStitchingObj->stitchingMode           = pStitchingLinkCreateParams->stitchingMode;
    
	////////////////////////////////////////////////////////////////////
    // First time call is just to get size for algorithm handle
    //  TBD - Currently since memquery function is dependent on alg handle
    //   space, there are two calls - first for alg handle and then for other
    //   requests. In future, once this dependency is removed, there will be
    //   only call of MemQuery
    Alg_StitchingMemQuery(&pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = Utils_memAlloc(	UTILS_HEAPID_DDR_CACHED_SR,
															memRequests.memTab[memTabId].size,
															memRequests.memTab[memTabId].alignment);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
 	////////////////////////////////////////////////////////////////////
 	// Memory allocations for the requests done by algorithm
    //  For now treating all requests as persistent and allocating in DDR
    Alg_StitchingMemQuery(&pAlgCreateParams, &memRequests, 0);
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++){
        if(memRequests.memTab[memTabId].size > 0){
			if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2){
				memRequests.memTab[memTabId].basePtr = (void *)Utils_memAlloc(	UTILS_HEAPID_L2_LOCAL,
																				memRequests.memTab[memTabId].size,
																				memRequests.memTab[memTabId].alignment);
																				}
	        else if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD){
	            memRequests.memTab[memTabId].basePtr = Utils_memAlloc(  UTILS_HEAPID_DDR_CACHED_SR,
																		memRequests.memTab[memTabId].size,
																		memRequests.memTab[memTabId].alignment);
																		}
	        else{
	            memRequests.memTab[memTabId].basePtr = malloc(memRequests.memTab[memTabId].size);}
			UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);}}
	
	algHandle = Alg_StitchingCreate(&pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pStitchingObj->algHandle = algHandle;
    
	////////////////////////////////////////////////////////////////////
    // Creation of output buffers for output queue
	/** ALGLINK_STITCHING_OPQID_BLENDLUT */
	{
	outputQId = ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED;
	channelId = 0;
	bufferSize = (maxHeight*(pStitchingObj->outputPitch[0]));
	for(frameIdx = 0; frameIdx < pStitchingObj->algLinkCreateParams.numOutBuffers; frameIdx++){
		/** Connects video frame buffer to system buffer payload */
		pSystemBuffer           = &(pStitchingObj->buffers[outputQId][frameIdx]);
		pSystemVideoFrameBuffer = &(pStitchingObj->videoFrames[frameIdx]);

		pSystemBuffer->payload     = pSystemVideoFrameBuffer;
		pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
		pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
		pSystemBuffer->chNum       = channelId;

		memcpy((void *)&pSystemVideoFrameBuffer->chInfo,
			   (void *)&pOutputQInfo[outputQId].queInfo.chInfo[channelId],
			   sizeof(System_LinkChInfo));

		/** Buffer allocation done for maxHeight, maxWidth and for 420SP format */
		pSystemVideoFrameBuffer->bufAddr[0] = Utils_memAlloc(	UTILS_HEAPID_DDR_CACHED_SR,
																(bufferSize*1.5),
																ALGORITHMLINK_FRAME_ALIGN);
														
		UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);
		/**	Sets up memory allocation for luma and chroma buffers (Assuming 420 SP format) */
		pSystemVideoFrameBuffer->bufAddr[1] = (void*)(	(UInt32) pSystemVideoFrameBuffer->bufAddr[0] + (UInt32)(bufferSize));
		
        UTILS_assert(pSystemVideoFrameBuffer->bufAddr[1] != NULL);
		/** Puts the buffer into an empty queue */
		status = AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
		UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);}
    }    
	////////////////////////////////////////////////////////////////////
    // Creation of local input queue
    /** ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW */
    {
    inputQId = ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW;
    status  = Utils_queCreate(	&(pStitchingObj->localInputQ[inputQId].queHandle),
								STITCHING_LINK_MAX_LOCALQUEUELENGTH,
								(pStitchingObj->localInputQ[inputQId].queMem),
								UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(&(pStitchingObj->localInputQ[inputQId].queHandle) != NULL);
    UTILS_assert(&(pStitchingObj->localInputQ[inputQId].queMem) != NULL);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}

	////////////////////////////////////////////////////////////////////
	// Stat collection
    //pStitchingObj->frameDropCounter = 0;
    pStitchingObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst( AlgorithmLink_getLinkId(pObj),"ALG_STITCHING");
    UTILS_assert(NULL != pStitchingObj->linkStatsInfo);
    
	////////////////////////////////////////////////////////////////////
	// Seems to be for outdated structs but currently they are implemented in the process fucntion         
    pStitchingObj->isFirstFrameRecv   = FALSE;
    pStitchingObj->isFirstOPGenerated = FALSE;
    pStitchingObj->receivedLUTFlag    = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for image transform algorithm link
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
Int32 AlgorithmLink_StitchingProcess(void * pObj)
{
    AlgorithmLink_StitchingObj 		* pStitchingObj;
    void                       				* algHandle;
    AlgorithmLink_StitchingInputQueId    inputQId;
    AlgorithmLink_StitchingOutputQueId   outputQId;
    
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    UInt32                       viewId;
    Bool                         bufDropFlag;
            
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;

    System_Buffer              * pSysBufferMultiview_Raw;
    System_Buffer              * pSysBufferDisparity_Transformed;
    
    System_MetaDataBuffer      			* seamDetectionInputBuffer;

    System_VideoFrameBuffer    			* pOutputBuffer;
    System_VideoFrameCompositeBuffer	* pMultiviewInputCompositeBuffer;

	void                       * inBlendLUTPtr;
    Word16                    * inSeam1;
    Word16                    * inSeam2;
	Bool isProcessCallDoneFlag;
	////////////////////////////////////////////////////////////////////
    AlgorithmLink_StitchingCreateParams  * pStitchingLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    pStitchingObj = (AlgorithmLink_StitchingObj *)
                         AlgorithmLink_getAlgorithmParamsObj(pObj);
	UTILS_assert(NULL != pStitchingObj);
    linkStatsInfo = pStitchingObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                  = pStitchingObj->algHandle;
    UTILS_assert(NULL != algHandle);
    pStitchingLinkCreateParams = (AlgorithmLink_StitchingCreateParams *)&pStitchingObj->algLinkCreateParams;
	UTILS_assert(NULL != pStitchingLinkCreateParams);
	////////////////////////////////////////////////////////////////////
    // Restarts stat collection
    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);
    if(pStitchingObj->isFirstFrameRecv==FALSE){
        pStitchingObj->isFirstFrameRecv = TRUE;
        Utils_resetLinkStatistics(	&linkStatsInfo->linkStats,
									1,
									1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);}

    linkStatsInfo->linkStats.newDataCmdCount++;

	////////////////////////////////////////////////////////////////////
    // Get Input Buffers from previous link and queue them up locally
     /** ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW */
    {
    inputQId = ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW;
    status = System_getLinksFullBuffers(	pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkId,
								pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
								&inputBufList);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    if(inputBufList.numBuf){
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++){
           
            pSysBufferMultiview_Raw = inputBufList.buffers[bufId];
			
            /** Check for parameter correctness. If in error, return input */
            if (pSysBufferMultiview_Raw != NULL)
            {
                status = Utils_quePut(	&(pStitchingObj->localInputQ[inputQId].queHandle), 
										pSysBufferMultiview_Raw, 
									BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
         }
    }
	}
	/** ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW */
	if (ENABLEINPUT == 1)   
    {
        inputQId = ALGLINK_STITCHING_IPQID_BLENDLUT;
        status = System_getLinksFullBuffers(pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkId,
								pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
								&inputBufList);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        if(inputBufList.numBuf){
            for (bufId = 0; bufId < inputBufList.numBuf; bufId++){

                if(pStitchingObj->receivedLUTFlag == TRUE)
                {
                    inputBufListReturn.numBuf     = 1;
                    inputBufListReturn.buffers[0] = pStitchingObj->sysBufferLUT;
                    bufDropFlag = FALSE;

                    status = AlgorithmLink_releaseInputBuffer(
                        pObj,
                        inputQId,
                        pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkId,
                        pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                        &inputBufListReturn,
                        &bufDropFlag);
                    pStitchingObj->receivedLUTFlag = FALSE;
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                }

                pStitchingObj->sysBufferLUT = inputBufList.buffers[bufId];
                pStitchingObj->receivedLUTFlag = TRUE;
            }
		}
	}
    ////////////////////////////////////////////////////////////////////
    // Continuous loop to perform the algorithm as buffers are available
    while(1)
    {
		isProcessCallDoneFlag = FALSE;
	    if( (Utils_queGetQueuedCount(&(pStitchingObj->localInputQ[ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW].queHandle))>0) &&
		  ( (pStitchingObj->receivedLUTFlag && (ENABLEINPUT == 1)) ||
		  (ENABLEINPUT != 1)))
		{
			/** ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED */
			{
			pOutputBuffer = NULL;
			outputQId = ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED;
			channelId = 0;
			status = AlgorithmLink_getEmptyOutputBuffer(pObj, outputQId, channelId, &pSysBufferDisparity_Transformed);
			if(status != SYSTEM_LINK_STATUS_SOK){
			  linkStatsInfo->linkStats.outBufErrorCount++;

				//Vps_printf("No disparity output buffer Stitching");
			  break;}
			UTILS_assert(pSysBufferDisparity_Transformed != NULL);
			pOutputBuffer = (System_VideoFrameBuffer*)pSysBufferDisparity_Transformed->payload;
		    }
			/** ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW */
			{
			    UTILS_assert(&(pStitchingObj->localInputQ[ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW].queHandle) != NULL);
		        status = Utils_queGet(  &(pStitchingObj->localInputQ[ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW].queHandle),
									(Ptr *)&pSysBufferMultiview_Raw,
									1,
									BSP_OSAL_NO_WAIT);
			    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			    UTILS_assert(pSysBufferMultiview_Raw != NULL);
			    pMultiviewInputCompositeBuffer = (System_VideoFrameCompositeBuffer *)(pSysBufferMultiview_Raw->payload);
			}

			/** ALGLINK_STITCHING_IPQID_BLENDLUT */
	       if (ENABLEINPUT == 1)
	       {
		        inBlendLUTPtr = NULL;
			    UTILS_assert(pStitchingObj->sysBufferLUT != NULL);
			    seamDetectionInputBuffer = (System_MetaDataBuffer *)(pStitchingObj->sysBufferLUT->payload);
			    inBlendLUTPtr            = seamDetectionInputBuffer->bufAddr[0];
			    inSeam1                  = seamDetectionInputBuffer->bufAddr[1];
                inSeam2                  = seamDetectionInputBuffer->bufAddr[2];
			}
			else
			{
				inBlendLUTPtr = (uWord32*)TempLUT;
			}
			///////////////////////////////////////////////////////////////////
			// Invalidates cache to be used for buffers
			for(viewId = 0; viewId < ALGORITHM_LINK_MAX_VIEWS+1 ;viewId++) {
				Cache_inv( 	pMultiviewInputCompositeBuffer->bufAddr[0][viewId],
							(pStitchingLinkCreateParams->maxInputWidth*pStitchingLinkCreateParams->maxInputHeight), 
							Cache_Type_ALLD, TRUE);
				Cache_inv(	pMultiviewInputCompositeBuffer->bufAddr[1][viewId],
							(pStitchingLinkCreateParams->maxInputWidth*pStitchingLinkCreateParams->maxInputHeight)/2,
							Cache_Type_ALLD, TRUE);
			}
			/////////////////////////////////////////////////////////////////////
			// Sets up timestamps for outputs in respect to their inputs
			pSysBufferDisparity_Transformed->srcTimestamp 	= pSysBufferMultiview_Raw->srcTimestamp;
			pSysBufferDisparity_Transformed->frameId 			= pSysBufferMultiview_Raw->frameId;
			pSysBufferDisparity_Transformed->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

			//////////////////////////////////////////////////////////////////////
			// Algorithm Process Run

            status = Alg_StitchingProcess(algHandle,
                                          pMultiviewInputCompositeBuffer,
                                          pOutputBuffer,
                                          &pStitchingObj->outputPitch[0],
                                          inBlendLUTPtr,
                                          inSeam1,
                                          inSeam2,
                                          pStitchingObj->stitchingMode);
	
			////////////////////////////////////////////////////////////////////////
			// Writes back any left over data
			/** Disparity Buffer */ 
	        {
			Cache_wb(	pOutputBuffer->bufAddr[0],
						(pStitchingObj->algLinkCreateParams.maxOutputWidth*pStitchingObj->algLinkCreateParams.maxOutputHeight), // Check this value
						Cache_Type_ALLD, TRUE);
			Cache_wb(	pOutputBuffer->bufAddr[1],
						(pStitchingObj->algLinkCreateParams.maxOutputWidth*pStitchingObj->algLinkCreateParams.maxOutputHeight)/2,
						Cache_Type_ALLD, TRUE);
			
			Utils_updateLatency(	&linkStatsInfo->linkLatency,
									pSysBufferDisparity_Transformed->linkLocalTimestamp);
			Utils_updateLatency(	&linkStatsInfo->srcToLinkLatency,
									pSysBufferDisparity_Transformed->srcTimestamp);
			}
			isProcessCallDoneFlag = TRUE;
			/////////////////////////////////////////////////////////////////////////
			// Post-processing for buffers and stats
			/** Multiview Stats */
			
			if (pSysBufferMultiview_Raw != NULL){
				linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
				linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;}
			/** Disparity Stats */
			if((ENABLEINPUT == 1))
			{
			    if (pStitchingObj->sysBufferLUT != NULL) {
				    linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
				    linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;
			    }
			}
	      
			////////////////////////////////////////////////////////////////////////
			// Fills full output buffer to be given to next link and informs next link of new data
			/** outputQId = ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED */
			{
			outputQId = ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED;
			status    = AlgorithmLink_putFullOutputBuffer(pObj, outputQId, pSysBufferDisparity_Transformed);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			
			System_sendLinkCmd(	pStitchingLinkCreateParams->outQueParams[outputQId].nextLink,
								SYSTEM_CMD_NEW_DATA, NULL);
			}
	
			///////////////////////////////////////////////////////////////////////
			// Releases output buffers, free'ing the memory
			/** ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED */
			{
	          outputQId                      = ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED;
	          outputBufListReturn.numBuf     = 1;
	          outputBufListReturn.buffers[0] = pSysBufferDisparity_Transformed;
	          status = AlgorithmLink_releaseOutputBuffer( pObj, outputQId, &outputBufListReturn);
			  UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			}
			////////////////////////////////////////////////////////////////////////
			// Releases input buffers, free'ing the memory
			bufDropFlag = FALSE;
			/** ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW */
			{
			    inputQId                      = ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW;
			    inputBufListReturn.numBuf     = 1;
			    inputBufListReturn.buffers[0] = pSysBufferMultiview_Raw;
			    status = AlgorithmLink_releaseInputBuffer( pObj, inputQId,
											  pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkId,
											  pStitchingLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
											  &inputBufListReturn,&bufDropFlag);
			    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			}
	        pStitchingObj->isFirstOPGenerated = TRUE;
	    } /* End of main if statement */

	    if(isProcessCallDoneFlag == FALSE)
			break;
	    else
	    	break;

	
    } /* End of main while loop */
    
   
    
    return status;
}

 
/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for image transform algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StitchingDelete(void * pObj)
{
    Int32  status    = SYSTEM_LINK_STATUS_SOK;
    UInt32 memTabId;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;
    UInt32 frameIdx;
    AlgLink_MemRequests          memRequests;
	AlgorithmLink_StitchingInputQueId     inputQId;
    AlgorithmLink_StitchingObj            *pStitchingObj;
	
    pStitchingObj = (AlgorithmLink_StitchingObj *)AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pStitchingObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_StitchingDelete(pStitchingObj->algHandle, &memRequests);

    ////////////////////////////////////////////////////////////////////
    // Memory allocations for the requests done by algorithm
    for(memTabId = 0 ; memTabId < memRequests.numMemTabs ; memTabId++){
        if(memRequests.memTab[memTabId].size > 0){
			if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2){
				status = Utils_memFree(	UTILS_HEAPID_L2_LOCAL,
								memRequests.memTab[memTabId].basePtr,
								memRequests.memTab[memTabId].size);}
			else if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD){
				status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                   memRequests.memTab[memTabId].basePtr,
                                   memRequests.memTab[memTabId].size);}
			else if(memTabId == 0){
				status = Utils_memFree(  UTILS_HEAPID_DDR_CACHED_SR,
                                   memRequests.memTab[memTabId].basePtr,
                                   memRequests.memTab[memTabId].size);}
			else{
				free(memRequests.memTab[memTabId].basePtr);}
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);}}
	
	////////////////////////////////////////////////////////////////////
	// Deletion of output buffers for output queues
	{
	for(frameIdx =0 ; frameIdx < pStitchingObj->algLinkCreateParams.numOutBuffers; frameIdx++){
		pSystemVideoFrameBuffer = &(pStitchingObj->videoFrames[frameIdx]);

		/** Buffer allocation done for maxHeight, outputPitch and for 420SP format */
		status = Utils_memFree(	UTILS_HEAPID_DDR_CACHED_SR,
								pSystemVideoFrameBuffer->bufAddr[0],
								(ALGLINK_FRAME_HEIGHT*(pStitchingObj->outputPitch[0])*(1.5)));
		UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);}
	}
	////////////////////////////////////////////////////////////////////
	// Deletion of local input queues
	/** ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW */
	{
    inputQId = ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW;
    status = Utils_queDelete(&(pStitchingObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}
    ////////////////////////////////////////////////////////////////////
    // Space for algorithm specific object gets freed here
    status = Utils_memFree(	UTILS_HEAPID_DDR_CACHED_SR,
							pStitchingObj,
							sizeof(AlgorithmLink_StitchingObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for image transform algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_StitchingControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_StitchingObj     * pStitchingObj;
    AlgorithmLink_ControlParams    		* pAlgLinkControlPrm;
    AlgorithmLink_StitchingObj     * algHandle;
    Int32                        		status    = SYSTEM_LINK_STATUS_SOK;

    pStitchingObj = (AlgorithmLink_StitchingObj *)AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pStitchingObj->algHandle;

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */
    switch(pAlgLinkControlPrm->controlCmd){
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_StitchingPrintStatistics(pObj, pStitchingObj);
            break;

        default:
            status = Alg_StitchingControl(	algHandle,&(pStitchingObj->controlParams));
            break;}
    return status;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for image transform algorithm link
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
Int32 AlgorithmLink_StitchingStop(	void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pStitchingObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StitchingPrintStatistics(	void *pObj, AlgorithmLink_StitchingObj *pStitchingObj)
{
    UTILS_assert(NULL != pStitchingObj->linkStatsInfo);

    Utils_printLinkStatistics(&pStitchingObj->linkStatsInfo->linkStats, "ALG_STITCHING", TRUE);

    Utils_printLatency("ALG_STITCHING",
                       &pStitchingObj->linkStatsInfo->linkLatency,
                       &pStitchingObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
