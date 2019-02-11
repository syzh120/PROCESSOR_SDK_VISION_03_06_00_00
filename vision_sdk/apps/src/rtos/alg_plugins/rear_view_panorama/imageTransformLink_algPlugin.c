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
#include "imageTransformLink_priv.h"
#include "CommonDefs.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#define ALGLINK_OUTPUT_FRAME_WIDTH  (1920)
#define ALGLINK_OUTPUT_FRAME_HEIGHT (1080)

#define ALGLINK_NUM_OUTPUT_FRAME_MULTIVIEW (3)
#define ALGLINK_NUM_OUTPUT_FRAME_DISPARITY (1)

#define ALGLINK_FRAME_WIDTH  (1920)
#define ALGLINK_FRAME_HEIGHT (480)

static const float InputCalibParams[] = {
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
Int32 AlgorithmLink_ImageTransform_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_ImageTransformCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_ImageTransformProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_ImageTransformControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_ImageTransformStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_ImageTransformDelete;
        
#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_IMAGETRANSFORM;
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
Int32 AlgorithmLink_ImageTransformCreate(void * pObj, void * pCreateParams)
{
	void                       * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       maxHeight;
    UInt32                       maxWidth;
    
    System_Buffer              * pSystemBuffer;
    System_VideoFrameCompositeBuffer    * pSystemVideoFrameCompositeBuffer;  
    System_LinkInfo              prevLinkInfo;
    
    AlgorithmLink_ImageTransformOutputQueId   outputQId;
    AlgorithmLink_ImageTransformInputQueId    inputQId;
    Int32                        frameIdx;
    Int32                        channelId;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       dataFormat;
    System_LinkChInfo            * pOutChInfo;
    System_LinkChInfo            * pPrevChInfo;
    UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;
    UInt32                       bufferSize;
    UInt32                       cnt;
    AlgorithmLink_ImageTransformObj             * pImageTransformObj;
    AlgorithmLink_ImageTransformCreateParams    * pImageTransformLinkCreateParams;
    RVP_ImageTransform_CreationParamsStruct       pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        		* pOutputQInfo;
    AlgorithmLink_InputQueueInfo         		* pInputQInfo;
    UInt32                                		  memTabId;
    
	////////////////////////////////////////////////////////////////////
	// Allows pointer access to create parameters
    pImageTransformLinkCreateParams = (AlgorithmLink_ImageTransformCreateParams *)pCreateParams;

    ////////////////////////////////////////////////////////////////////
    // Allocates object
    pImageTransformObj = (AlgorithmLink_ImageTransformObj *)Utils_memAlloc(	UTILS_HEAPID_DDR_CACHED_SR,
																			sizeof(AlgorithmLink_ImageTransformObj), 64);
																			
	////////////////////////////////////////////////////////////////////
	// Check to see if object is NULL
    UTILS_assert(pImageTransformObj!= NULL);
    UTILS_assert(ALGORITHM_LINK_MAX_VIEWS <= pImageTransformLinkCreateParams->numCameras);
    
	////////////////////////////////////////////////////////////////////
	// Copy algorithm parameters pointers
    pAlgCreateParams = pImageTransformObj->algCreateParams;

    pOutputQInfo = &pImageTransformObj->outputQInfo[0];
    pInputQInfo  = &pImageTransformObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pImageTransformObj);
    
	////////////////////////////////////////////////////////////////////
    // Copy of needed create time parameters for the future. Need?
    memcpy(	(void*)(&pImageTransformObj->algLinkCreateParams),
			(void*)(pImageTransformLinkCreateParams),
			sizeof(AlgorithmLink_ImageTransformCreateParams));
			
    ////////////////////////////////////////////////////////////////////
    // Setup all queues
    numInputQUsed     = ALGLINK_IMAGETRANSFORM_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_IMAGETRANSFORM_OPQID_MAXOPQ;
    channelId         = 0;

    pInputQInfo[ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pInputQInfo[ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED].queInfo.numCh = ALGLINK_NUM_OUTPUT_FRAME_MULTIVIEW;
    
    ////////////////////////////////////////////////////////////////////
    // Setups individual input/output queues
    /** Multiview */
    {
    outputQId = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED;
    inputQId  = ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW;
	channelId = 0;
    status = System_linkGetInfo(	pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkId,
									&prevLinkInfo);
	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	prevLinkQueId = pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkQueId;								

	    pPrevChInfo   = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);
	
	    maxHeight = pImageTransformObj->algLinkCreateParams.maxOutputHeight;
	    maxWidth  = pImageTransformObj->algLinkCreateParams.maxOutputWidth;
	
	    UTILS_assert(maxWidth  <= ALGLINK_OUTPUT_FRAME_WIDTH);
	    UTILS_assert(maxHeight <= ALGLINK_OUTPUT_FRAME_HEIGHT);
	
	    pImageTransformObj->outputPitch[0] = maxWidth; 
	    pImageTransformObj->outputPitch[1] = pImageTransformObj->outputPitch[0];
	    pImageTransformObj->outputPitch[2] = pImageTransformObj->outputPitch[0];
	
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
	
	    pImageTransformObj->inputPitch[0] = pPrevChInfo->pitch[0];
	    pImageTransformObj->inputPitch[1] = pPrevChInfo->pitch[1];
		
		if(	(pPrevChInfo->width > pImageTransformObj->algLinkCreateParams.maxInputWidth) ||
			(pPrevChInfo->height > pImageTransformObj->algLinkCreateParams.maxInputHeight)){
			UTILS_assert(NULL);}
	
	    pOutChInfo->pitch[0] = pImageTransformObj->outputPitch[0];
	    pOutChInfo->pitch[1] = pImageTransformObj->outputPitch[1];
	    pOutChInfo->pitch[2] = pImageTransformObj->outputPitch[2];
	    
	    for(channelId =0 ; channelId < 3; channelId++)
        {
        /*
         * Taking a copy of input channel info in the link object for any future
         * use
         */
        memcpy((void *)&(pImageTransformObj->inputChInfo[channelId]),
            (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
            sizeof(System_LinkChInfo)
            );
        }
	}
    
    /** Disparity */
    {
    inputQId  = ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW;
	channelId = 0;
    status = System_linkGetInfo(	pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkId,
									&prevLinkInfo);
	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    prevLinkQueId = pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkQueId;
    
    pPrevChInfo   = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    maxHeight = pImageTransformObj->algLinkCreateParams.maxOutputHeight;
    maxWidth  = pImageTransformObj->algLinkCreateParams.maxOutputWidth;

    UTILS_assert(maxWidth  <= ALGLINK_OUTPUT_FRAME_WIDTH);
    UTILS_assert(maxHeight <= ALGLINK_OUTPUT_FRAME_HEIGHT);

    pImageTransformObj->outputPitch[0] = maxWidth; 
    pImageTransformObj->outputPitch[1] = pImageTransformObj->outputPitch[0];
    pImageTransformObj->outputPitch[2] = pImageTransformObj->outputPitch[0];

    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV){
		UTILS_assert(NULL);}

    pImageTransformObj->inputPitch[0] = pPrevChInfo->pitch[0];
    pImageTransformObj->inputPitch[1] = pPrevChInfo->pitch[1];
	//pImageTransformObj->inputPitch[2] = pPrevChInfo->pitch[2];
	if(	(pPrevChInfo->width > pImageTransformObj->algLinkCreateParams.maxInputWidth) ||
		(pPrevChInfo->height > pImageTransformObj->algLinkCreateParams.maxInputHeight)){
		UTILS_assert(NULL);}
	}
	for(channelId =0 ; channelId < 1; channelId++)
    {
        /*
         * Taking a copy of input channel info in the link object for any future
         * use
         */
        memcpy((void *)&(pImageTransformObj->inputChInfo[channelId]),
            (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
            sizeof(System_LinkChInfo)
            );
    }
	////////////////////////////////////////////////////////////////////
    // Initializations needed for book keeping of buffer handling
    //  Note that this needs to be called only after setting inputQMode and outputQMode.
    status = AlgorithmLink_queueInfoInit(pObj, numInputQUsed, pInputQInfo, numOutputQUsed, pOutputQInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);                       
	////////////////////////////////////////////////////////////////////
    // Populates create time parameters
    pAlgCreateParams.RVPInCamFrmHeight    = 	pImageTransformLinkCreateParams->maxInputHeight;
    pAlgCreateParams.RVPInCamFrmWidth     =	    pImageTransformLinkCreateParams->maxInputWidth;
    pAlgCreateParams.RVPOutDisplayHeight  =	    pImageTransformLinkCreateParams->maxOutputHeight;
    pAlgCreateParams.RVPOutDisplayWidth   =	    pImageTransformLinkCreateParams->maxOutputWidth;
    pAlgCreateParams.numCameras   		  =  	pImageTransformLinkCreateParams->numCameras;

    for (cnt = 0; cnt < pImageTransformLinkCreateParams->numCameras + 1; cnt++)
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

    pAlgCreateParams.vc_scale_height = VC_SCALE_HEIGHT; //scale in z-direction
    pAlgCreateParams.vc_scale_depth  = VC_SCALE_DEPTH; //scale in y-direction

    pAlgCreateParams.focalLength = FOCAL_LENGTH;

    pAlgCreateParams.vc_wall_distance = VC_WALL_DISTANCE; //distance of wall from virtual camera
    pAlgCreateParams.vc_vf = VC_VF; //virtual camera focal length
    pAlgCreateParams.vc_rotx = VC_ROTX; //rotation of virtual camera about x-axis
    pAlgCreateParams.vc_roty = VC_ROTY;
    pAlgCreateParams.vc_rotz = VC_ROTZ;


    pImageTransformObj->pInputCalibParams  				= (float *)InputCalibParams;
    pImageTransformObj->imageTransformMode		   		= pImageTransformLinkCreateParams->imageTransformMode;
    
	////////////////////////////////////////////////////////////////////
    // First time call is just to get size for algorithm handle
    //  TBD - Currently since memquery function is dependent on alg handle
    //   space, there are two calls - first for alg handle and then for other
    //   requests. In future, once this dependency is removed, there will be
    //   only call of MemQuery
    Alg_ImageTransformMemQuery(&pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = Utils_memAlloc(	UTILS_HEAPID_DDR_CACHED_SR,
															memRequests.memTab[memTabId].size,
															memRequests.memTab[memTabId].alignment);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
 	////////////////////////////////////////////////////////////////////
 	// Memory allocations for the requests done by algorithm
    //  For now treating all requests as persistent and allocating in DDR
    Alg_ImageTransformMemQuery(&pAlgCreateParams, &memRequests, 0); 
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++){
        if(memRequests.memTab[memTabId].size > 0){
			if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2){
				memRequests.memTab[memTabId].basePtr = (void *)Utils_memAlloc(	UTILS_HEAPID_L2_LOCAL,
																				memRequests.memTab[memTabId].size,
																				memRequests.memTab[memTabId].alignment);}
	        else if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD){
	            memRequests.memTab[memTabId].basePtr = Utils_memAlloc(  UTILS_HEAPID_DDR_CACHED_SR,
																		memRequests.memTab[memTabId].size,
																		memRequests.memTab[memTabId].alignment);}
	        else{
	            memRequests.memTab[memTabId].basePtr = malloc(memRequests.memTab[memTabId].size);}
			UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);}}
	
	algHandle = Alg_ImageTransformCreate(&pAlgCreateParams, &memRequests); // Error coming here?
    UTILS_assert(algHandle != NULL);

    pImageTransformObj->algHandle = algHandle;
	////////////////////////////////////////////////////////////////////
    // Creation of output buffers for output queue
    /** ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED */
    {
	outputQId = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED;
	channelId = 0;
	bufferSize = (maxHeight*(pImageTransformObj->outputPitch[0])*(1.5));
	for(frameIdx = 0; frameIdx < pImageTransformObj->algLinkCreateParams.numOutBuffers; frameIdx++)
        {
			/** Connects video frame buffer to system buffer payload */
			pSystemBuffer           = &(pImageTransformObj->buffers[outputQId][frameIdx]);
			pSystemVideoFrameCompositeBuffer = &(pImageTransformObj->videoCompositeFrames[frameIdx]);
			memset(pSystemVideoFrameCompositeBuffer, 0, sizeof(System_VideoFrameCompositeBuffer));
			pSystemBuffer->payload     = pSystemVideoFrameCompositeBuffer;
			pSystemBuffer->payloadSize = sizeof(System_VideoFrameCompositeBuffer);
			pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
			pSystemBuffer->chNum       = 0;
			

                   
			pSystemVideoFrameCompositeBuffer->numFrames = 3;
			/** Buffer allocation done for maxHeight, maxWidth and for 420SP format */
			for(channelId =0 ; channelId < 4; channelId++)
			{
			pSystemVideoFrameCompositeBuffer->bufAddr[0][channelId] = Utils_memAlloc(
                                                   UTILS_HEAPID_DDR_CACHED_SR,
                                                   bufferSize,
                                                   ALGORITHMLINK_FRAME_ALIGN
                                                   );
			if (channelId != 3)
			{
	            pSystemVideoFrameCompositeBuffer->bufAddr[1][channelId] = (void*)(  (UInt32) pSystemVideoFrameCompositeBuffer->bufAddr[0][channelId] + (UInt32)(bufferSize/1.5));
			}
			else
			{
			    pSystemVideoFrameCompositeBuffer->bufAddr[1][channelId] = NULL;
			}

			UTILS_assert(pSystemVideoFrameCompositeBuffer->bufAddr[0][0] != NULL);
			}
			 pSystemVideoFrameCompositeBuffer->flags = 0;
			/** Puts the buffer into an empty queue */
			status = AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

			
						memcpy((void *)&pSystemVideoFrameCompositeBuffer->chInfo,
                   (void *)&pOutputQInfo[outputQId].queInfo.chInfo[channelId],
                   sizeof(System_LinkChInfo));
	}
	}

	////////////////////////////////////////////////////////////////////
    // Creation of local input queue
    /** ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW */
    {
    inputQId = ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW;
    status  = Utils_queCreate(	&(pImageTransformObj->localInputQ[inputQId].queHandle),
								IMAGETRANSFORM_LINK_MAX_LOCALQUEUELENGTH,
								(pImageTransformObj->localInputQ[inputQId].queMem),
								UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(&(pImageTransformObj->localInputQ[inputQId].queHandle) != NULL);
    UTILS_assert(&(pImageTransformObj->localInputQ[inputQId].queMem) != NULL);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

	////////////////////////////////////////////////////////////////////
	// Stat collection
    //pImageTransformObj->frameDropCounter = 0;
    pImageTransformObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst( AlgorithmLink_getLinkId(pObj),"ALG_IMAGETRANSFORM");
    UTILS_assert(NULL != pImageTransformObj->linkStatsInfo);
    
	////////////////////////////////////////////////////////////////////
	// Seems to be for outdated structs but currently they are implemented in the process fucntion         
    pImageTransformObj->isFirstFrameRecv   = FALSE;
    pImageTransformObj->isFirstOPGenerated = FALSE;
    pImageTransformObj->receivedDisparityFlag  = FALSE;

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
Int32 AlgorithmLink_ImageTransformProcess(void * pObj)
{
    AlgorithmLink_ImageTransformObj 		* pImageTransformObj;
    void                       				* algHandle;
    AlgorithmLink_ImageTransformInputQueId    inputQId;
    AlgorithmLink_ImageTransformOutputQueId   outputQId;
    
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    UInt32                       viewId;
    Bool                         bufDropFlag;
  
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    
    System_Buffer              * pSysBufferMultiview_Raw;
    System_Buffer              * pSysBufferMultiview_Transformed;
    
    System_VideoFrameBuffer    			* pDisparityInputBuffer;
    System_VideoFrameCompositeBuffer	* pMultiviewInputCompositeBuffer;
    System_VideoFrameCompositeBuffer	* pMultiviewOutputCompositeBuffer;

	Bool isProcessCallDoneFlag;
	////////////////////////////////////////////////////////////////////
    AlgorithmLink_ImageTransformCreateParams  * pImageTransformLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    pImageTransformObj = (AlgorithmLink_ImageTransformObj *)
                         AlgorithmLink_getAlgorithmParamsObj(pObj);
	UTILS_assert(NULL != pImageTransformObj);
    linkStatsInfo = pImageTransformObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                  = pImageTransformObj->algHandle;
    UTILS_assert(NULL != algHandle);
    pImageTransformLinkCreateParams = (AlgorithmLink_ImageTransformCreateParams *)&pImageTransformObj->algLinkCreateParams;
	UTILS_assert(NULL != pImageTransformLinkCreateParams);


	////////////////////////////////////////////////////////////////////
    // Get Input Buffers from previous link and queue them up locally
    /** ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW */
    {
    inputQId = ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW;
    status = System_getLinksFullBuffers(	pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkId,
								pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
								&inputBufList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            
            pSysBufferMultiview_Raw = inputBufList.buffers[bufId];            
            if (pSysBufferMultiview_Raw != NULL)
            {
                status = Utils_quePut(	&(pImageTransformObj->localInputQ[inputQId].queHandle), 
										pSysBufferMultiview_Raw, 
									BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }

	}
    /** ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW */
    {
    inputQId = ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW;
    status = System_getLinksFullBuffers(	pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkId,
								pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
								&inputBufList);
	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        if(inputBufList.numBuf)
        {
            for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
            {
                /*
                 * At any point in time, Synthesis link will hold only one GA LUT.
                 * So whenever GA LUT is received, the previously received one
                 * will be released and the newly received one will be archived.
                 */
                if(pImageTransformObj->receivedDisparityFlag == TRUE)
                {
                    inputBufListReturn.numBuf     = 1;
                    inputBufListReturn.buffers[0] = pImageTransformObj->sysBufferDisparity;
                    bufDropFlag = FALSE;

                    status = AlgorithmLink_releaseInputBuffer(
                        pObj,
                        inputQId,
                        pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkId,
                        pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                        &inputBufListReturn,
                        &bufDropFlag);
                    pImageTransformObj->receivedDisparityFlag = FALSE;					
					UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
					
                }

                pImageTransformObj->sysBufferDisparity = inputBufList.buffers[bufId];
                pImageTransformObj->receivedDisparityFlag = TRUE;
            }
        }
    }
    
    ////////////////////////////////////////////////////////////////////
    // Restarts stat collection
    if(pImageTransformObj->isFirstFrameRecv==FALSE)
    {
        pImageTransformObj->isFirstFrameRecv = TRUE;
        Utils_resetLinkStatistics(  &linkStatsInfo->linkStats,
                                    1,
                                    1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);
    linkStatsInfo->linkStats.newDataCmdCount++;


	////////////////////////////////////////////////////////////////////
    // Continuous loop to perform the algorithm as buffers are available
    while(1)
    {
		isProcessCallDoneFlag = FALSE;
	    
	    if( ( (Utils_queGetQueuedCount(&(pImageTransformObj->localInputQ[ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW].queHandle))>0) &&
			(pImageTransformObj->receivedDisparityFlag) ))
		{
			/** ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED */
			{
			
			pMultiviewOutputCompositeBuffer = NULL;
			outputQId = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED;
			channelId = 0;
			//Task_sleep(50);
			status = AlgorithmLink_getEmptyOutputBuffer(pObj, outputQId, channelId, &pSysBufferMultiview_Transformed);

			if(status != SYSTEM_LINK_STATUS_SOK){
			  linkStatsInfo->linkStats.outBufErrorCount++;
			  //Vps_printf("No multiview output buffer ImageTransform");
			  break;
			}
			UTILS_assert(pSysBufferMultiview_Transformed != NULL);
			pMultiviewOutputCompositeBuffer = (System_VideoFrameCompositeBuffer *)(pSysBufferMultiview_Transformed->payload);
		    }
			
			
			/** ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW */
			{
			UTILS_assert(&(pImageTransformObj->localInputQ[ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW].queHandle) != NULL);
		    status = Utils_queGet(  &(pImageTransformObj->localInputQ[ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW].queHandle),
									(Ptr *)&pSysBufferMultiview_Raw,
									1,
									BSP_OSAL_NO_WAIT);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			UTILS_assert(pSysBufferMultiview_Raw != NULL);
			pMultiviewInputCompositeBuffer = (System_VideoFrameCompositeBuffer *)(pSysBufferMultiview_Raw->payload);		
			}
			 /** ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW */
			{

			pDisparityInputBuffer = (System_VideoFrameBuffer *)(pImageTransformObj->sysBufferDisparity->payload);		
			}
		 
			///////////////////////////////////////////////////////////////////
			// Invalidates cache to be used for buffers
			for(viewId = 0; viewId < ALGORITHM_LINK_MAX_VIEWS ;viewId++)
			{
				Cache_inv( 	pMultiviewInputCompositeBuffer->bufAddr[0][viewId],
							(pImageTransformLinkCreateParams->maxInputWidth*pImageTransformLinkCreateParams->maxInputHeight), 
							Cache_Type_ALLD, TRUE);
				Cache_inv(	pMultiviewInputCompositeBuffer->bufAddr[1][viewId],
							((pImageTransformLinkCreateParams->maxInputWidth*pImageTransformLinkCreateParams->maxInputHeight)/2), // May need to be changed as I believe the /2 in the buffer is specifcally for the SV case
							Cache_Type_ALLD, TRUE);
			}
			Cache_inv( 	pDisparityInputBuffer->bufAddr[0],
						(pImageTransformLinkCreateParams->maxInputWidth*pImageTransformLinkCreateParams->maxInputHeight), 
						Cache_Type_ALLD, TRUE);
			Cache_inv(	pDisparityInputBuffer->bufAddr[1],
						((pImageTransformLinkCreateParams->maxInputWidth*pImageTransformLinkCreateParams->maxInputHeight)/2), // May need to be changed as I believe the /2 in the buffer is specifcally for the SV case
						Cache_Type_ALLD, TRUE);
	
			/////////////////////////////////////////////////////////////////////
			// Sets up timestamps for outputs in respect to their inputs
			pSysBufferMultiview_Transformed->srcTimestamp 	= pSysBufferMultiview_Raw->srcTimestamp;
			pSysBufferMultiview_Transformed->frameId 			= pSysBufferMultiview_Raw->frameId;
			pSysBufferMultiview_Transformed->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

			//////////////////////////////////////////////////////////////////////
			// Algorithm Process Run
			if (pImageTransformObj->imageTransformMode == 2){
				pImageTransformObj->imageTransformMode = 0;
				status = Alg_ImageTransformProcess(
							   algHandle,
							   pMultiviewInputCompositeBuffer,
							   pMultiviewOutputCompositeBuffer,
							   pDisparityInputBuffer,
							   &pImageTransformObj->inputPitch[0],
							   pImageTransformObj->pInputCalibParams,
							   pImageTransformObj->imageTransformMode);
			}
			else {
			status = Alg_ImageTransformProcess(
							   algHandle,
							   pMultiviewInputCompositeBuffer,
							   pMultiviewOutputCompositeBuffer,
							   pDisparityInputBuffer,
							   &pImageTransformObj->inputPitch[0],
							   pImageTransformObj->pInputCalibParams,
							   pImageTransformObj->imageTransformMode);
			}

			UTILS_assert(pMultiviewOutputCompositeBuffer != NULL);
	
			////////////////////////////////////////////////////////////////////////
			// Writes back any left over data
			/** Multiview Buffer */
			{
			for(viewId = 0; viewId < ALGORITHM_LINK_MAX_VIEWS+1 ;viewId++)
			{
				Cache_wb( 	pMultiviewOutputCompositeBuffer->bufAddr[0][viewId],
							(pImageTransformLinkCreateParams->maxOutputWidth*pImageTransformLinkCreateParams->maxOutputHeight), 
							Cache_Type_ALLD, TRUE);
				Cache_wb(	pMultiviewOutputCompositeBuffer->bufAddr[1][viewId],
							((pImageTransformLinkCreateParams->maxOutputWidth*pImageTransformLinkCreateParams->maxOutputHeight)/2),
							Cache_Type_ALLD, TRUE);
			}

			Utils_updateLatency(	&linkStatsInfo->linkLatency,
								pSysBufferMultiview_Transformed->linkLocalTimestamp);
			Utils_updateLatency(	&linkStatsInfo->srcToLinkLatency,
								pSysBufferMultiview_Transformed->srcTimestamp);

	        }
			isProcessCallDoneFlag = TRUE;
			/////////////////////////////////////////////////////////////////////////
			// Post-processing for buffers and stats
			/** Multiview Stats */
			
			if (pSysBufferMultiview_Raw != NULL){
				linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
				linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;}
			/** Disparity Stats */
			if (pImageTransformObj->sysBufferDisparity != NULL){
				linkStatsInfo->linkStats.chStats[pImageTransformObj->sysBufferDisparity->chNum].inBufProcessCount++;
				linkStatsInfo->linkStats.chStats[pImageTransformObj->sysBufferDisparity->chNum].outBufCount[0]++;}
	      
			////////////////////////////////////////////////////////////////////////
			// Fills full output buffer to be given to next link and informs next link of new data
			/** outputQId = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED */
			{
			outputQId = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED;
			status    = AlgorithmLink_putFullOutputBuffer(pObj, outputQId, pSysBufferMultiview_Transformed);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			
			System_sendLinkCmd(	pImageTransformLinkCreateParams->outQueParams[outputQId].nextLink,
								SYSTEM_CMD_NEW_DATA, NULL);
								
			}
	
			///////////////////////////////////////////////////////////////////////
			// Releases output buffers, free'ing the memory
			/** ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED */
			{
	          outputQId                      = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED;
	          outputBufListReturn.numBuf     = 1;
	          outputBufListReturn.buffers[0] = pSysBufferMultiview_Transformed;
	          status = AlgorithmLink_releaseOutputBuffer( pObj, outputQId, &outputBufListReturn);
			  UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			}
			
			////////////////////////////////////////////////////////////////////////
			// Releases input buffers, free'ing the memory
			bufDropFlag = FALSE;
			/** ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW */
			{
			inputQId                      = ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW;
			inputBufListReturn.numBuf     = 1;
			inputBufListReturn.buffers[0] = pSysBufferMultiview_Raw;
			status = AlgorithmLink_releaseInputBuffer( pObj, inputQId,
											  pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkId,
											  pImageTransformLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
											  &inputBufListReturn,&bufDropFlag);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			}

	        pImageTransformObj->isFirstOPGenerated = TRUE;
	    } /* End of main if statement */

	    if(isProcessCallDoneFlag == FALSE)
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
Int32 AlgorithmLink_ImageTransformDelete(void * pObj)
{
    Int32  status    = SYSTEM_LINK_STATUS_SOK;
    Int32                        frameIdx;
    UInt32 memTabId;

    System_VideoFrameCompositeBuffer    * pSystemVideoFrameCompositeBuffer;
    AlgLink_MemRequests          memRequests;
	AlgorithmLink_ImageTransformInputQueId     inputQId;
    AlgorithmLink_ImageTransformObj           * pImageTransformObj;
    
	
    pImageTransformObj = (AlgorithmLink_ImageTransformObj *)AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pImageTransformObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_ImageTransformDelete(pImageTransformObj->algHandle, &memRequests);

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
			else{
				free(memRequests.memTab[memTabId].basePtr);}
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);}}
	
	////////////////////////////////////////////////////////////////////
	// Deletion of output buffers for output queues
	/** ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED */
	{
	//outputQId = ALGLINK_IMAGETRANSFORM_OPQID_MULTIVIEW_TRANSFORMED;
	
	for(frameIdx =0 ; frameIdx < pImageTransformObj->algLinkCreateParams.numOutBuffers; frameIdx++){
			pSystemVideoFrameCompositeBuffer = &(pImageTransformObj->videoCompositeFrames[frameIdx]);
			
			/** Buffer allocation done for maxHeight, outputPitch and for 420SP format */
			status = Utils_memFree(	UTILS_HEAPID_DDR_CACHED_SR,
									pSystemVideoFrameCompositeBuffer->bufAddr[0][0],
									(ALGLINK_NUM_OUTPUT_FRAME_MULTIVIEW*ALGLINK_FRAME_HEIGHT*(pImageTransformObj->outputPitch[0])*(1.5))); // ALGLINK_OUTPUT_FRAME_HEIGHT
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);}
	}
	
	////////////////////////////////////////////////////////////////////
	// Deletion of local input queues
	/** ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW */
	{
    inputQId = ALGLINK_IMAGETRANSFORM_IPQID_MULTIVIEW_RAW;
    status = Utils_queDelete(&(pImageTransformObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}
	/** ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW */
	{
    inputQId = ALGLINK_IMAGETRANSFORM_IPQID_DISPARITY_RAW;
    status = Utils_queDelete(&(pImageTransformObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}
    
    ////////////////////////////////////////////////////////////////////
    // Space for algorithm specific object gets freed here
    status = Utils_memFree(	UTILS_HEAPID_DDR_CACHED_SR,
							pImageTransformObj,
							sizeof(AlgorithmLink_ImageTransformObj));
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

Int32 AlgorithmLink_ImageTransformControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_ImageTransformObj     * pImageTransformObj;
    AlgorithmLink_ControlParams    		* pAlgLinkControlPrm;
    AlgorithmLink_ImageTransformObj     * algHandle;
    Int32                        		status    = SYSTEM_LINK_STATUS_SOK;

    pImageTransformObj = (AlgorithmLink_ImageTransformObj *)AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pImageTransformObj->algHandle;

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */
    switch(pAlgLinkControlPrm->controlCmd){
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_ImageTransformPrintStatistics(pObj, pImageTransformObj);
            break;

        default:
            status = Alg_ImageTransformControl(	algHandle,&(pImageTransformObj->controlParams));
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
Int32 AlgorithmLink_ImageTransformStop(	void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pImageTransformObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_ImageTransformPrintStatistics(	void *pObj, AlgorithmLink_ImageTransformObj *pImageTransformObj)
{
    UTILS_assert(NULL != pImageTransformObj->linkStatsInfo);

    Utils_printLinkStatistics(&pImageTransformObj->linkStatsInfo->linkStats, "ALG_IMAGETRANSFORM", TRUE);

    Utils_printLatency("ALG_IMAGETRANSFORM",
                       &pImageTransformObj->linkStatsInfo->linkLatency,
                       &pImageTransformObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
