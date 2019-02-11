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
#include "seamDetectionLink_priv.h"
#include "CommonDefs.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#define ALGLINK_OUTPUT_FRAME_WIDTH  (1920)
#define ALGLINK_OUTPUT_FRAME_HEIGHT (1080)

#define ALGLINK_OUTPUT_FRAME_WIDTH2  (1920)
#define ALGLINK_OUTPUT_FRAME_HEIGHT2 (480)

#define ALGLINK_NUM_OUTPUT_FRAME_MULTIVIEW (3)
#define ALGLINK_NUM_OUTPUT_FRAME_DISPARITY (1)

#define ALGLINK_FRAME_WIDTH  (1280)
#define ALGLINK_FRAME_HEIGHT (720)

#define ENABLEINPUT (0)

#define ALGLINK_BLENDLUT_SIZE ((ALGLINK_OUTPUT_FRAME_HEIGHT2) * (ALGLINK_OUTPUT_FRAME_WIDTH2) + 256)

static const float InputCalibParams[] = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0};
static const uWord32 TempLUT[] = {
	9, 8, 7,
	6, 5, 4,
	3, 2, 1};

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
Int32 AlgorithmLink_SeamDetection_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_SeamDetectionCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_SeamDetectionProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_SeamDetectionControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_SeamDetectionStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_SeamDetectionDelete;
        
#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SEAMDETECTION;
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
Int32 AlgorithmLink_SeamDetectionCreate(void * pObj, void * pCreateParams)
{
	void                       * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       maxHeight;
    UInt32 frameIdx;
    System_Buffer              * pSystemBuffer;
    System_LinkInfo              prevLinkInfo;
    
    AlgorithmLink_SeamDetectionOutputQueId   outputQId;
    AlgorithmLink_SeamDetectionInputQueId    inputQId;	
    
    Int32                        channelId;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       dataFormat;
    System_LinkChInfo            * pOutChInfo;
    System_LinkChInfo            * pPrevChInfo;
    UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_SeamDetectionObj             * pSeamDetectionObj;
    AlgorithmLink_SeamDetectionCreateParams    * pSeamDetectionLinkCreateParams;
    RVP_SeamDetection_CreationParamsStruct     pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        		* pOutputQInfo;
    AlgorithmLink_InputQueueInfo         		* pInputQInfo;
    UInt32                                		  memTabId;
    
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    UInt32                       metaBufSize, seamBufSize;
    UInt32                       cnt;

	////////////////////////////////////////////////////////////////////
	// Allows pointer access to create parameters
    pSeamDetectionLinkCreateParams = (AlgorithmLink_SeamDetectionCreateParams *)pCreateParams;

    ////////////////////////////////////////////////////////////////////
    // Allocates object
    pSeamDetectionObj = (AlgorithmLink_SeamDetectionObj *)Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, sizeof(AlgorithmLink_SeamDetectionObj), 64);
																			
	////////////////////////////////////////////////////////////////////
	// Check to see if object is NULL
    UTILS_assert(pSeamDetectionObj!= NULL);
    UTILS_assert(ALGORITHM_LINK_MAX_VIEWS <= pSeamDetectionLinkCreateParams->numCameras);
    
	////////////////////////////////////////////////////////////////////
	// Copy algorithm parameters pointers
    pAlgCreateParams = pSeamDetectionObj->algCreateParams;

    pOutputQInfo = &pSeamDetectionObj->outputQInfo[0];
    pInputQInfo  = &pSeamDetectionObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pSeamDetectionObj);
    
	////////////////////////////////////////////////////////////////////
    // Copy of needed create time parameters for the future. Need?
    memcpy(	(void*)(&pSeamDetectionObj->algLinkCreateParams),
			(void*)(pSeamDetectionLinkCreateParams),
			sizeof(AlgorithmLink_SeamDetectionCreateParams));
			
    ////////////////////////////////////////////////////////////////////
    // Setup all queues
    numInputQUsed     = ALGLINK_SEAMDETECTION_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_SEAMDETECTION_OPQID_MAXOPQ;
    channelId         = 0;

    pInputQInfo[ALGLINK_SEAMDETECTION_IPQID_MULTIVIEW_RAW].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    //pInputQInfo[ALGLINK_SEAMDETECTION_IPQID_DISPARITY_RAW].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
	pInputQInfo[ALGLINK_SEAMDETECTION_IPQID_BLENDLUT].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_SEAMDETECTION_OPQID_BLENDLUT].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_SEAMDETECTION_OPQID_BLENDLUT].queInfo.numCh = 1;
    ////////////////////////////////////////////////////////////////////
    // Setups individual input/output queues
     /** Multiview */ // There may be useless components in this
    {
    inputQId  = ALGLINK_SEAMDETECTION_IPQID_MULTIVIEW_RAW;
	channelId = 0;
    status = System_linkGetInfo(	pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkId,
									&prevLinkInfo);
	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	prevLinkQueId = pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkQueId;								

	    pPrevChInfo   = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);
	
	    prevChInfoFlags    = pPrevChInfo->flags;
		
	    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);
	
	    if(dataFormat != SYSTEM_DF_YUV420SP_UV){
			UTILS_assert(NULL);}
	
	    pSeamDetectionObj->inputPitch[0] = pPrevChInfo->pitch[0];
	    pSeamDetectionObj->inputPitch[1] = pPrevChInfo->pitch[1];

		 if((pPrevChInfo->width > pSeamDetectionObj->algLinkCreateParams.maxInputWidth) ||
			(pPrevChInfo->height > pSeamDetectionObj->algLinkCreateParams.maxInputHeight)){
			UTILS_assert(NULL);}
	}
	/** BlendLUT  */
	{
	outputQId = ALGLINK_SEAMDETECTION_OPQID_BLENDLUT;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;
	}
	////////////////////////////////////////////////////////////////////
    // Initializations needed for book keeping of buffer handling
    //  Note that this needs to be called only after setting inputQMode and outputQMode.
    status = AlgorithmLink_queueInfoInit(pObj, numInputQUsed, pInputQInfo, numOutputQUsed, pOutputQInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);                       
	////////////////////////////////////////////////////////////////////
    // Populates create time parameters
    pAlgCreateParams.RVPInCamFrmHeight    = 	pSeamDetectionLinkCreateParams->maxInputHeight;
    pAlgCreateParams.RVPInCamFrmWidth     =	pSeamDetectionLinkCreateParams->maxInputWidth;
    pAlgCreateParams.RVPOutDisplayHeight  =	pSeamDetectionLinkCreateParams->maxOutputHeight;
    pAlgCreateParams.RVPOutDisplayWidth   =	pSeamDetectionLinkCreateParams->maxOutputWidth;
    pAlgCreateParams.numCameras   		   =	pSeamDetectionLinkCreateParams->numCameras;
    pAlgCreateParams.seamdetectionMode    =    SEAMDETECTIONMODE;
    /* Added from PC code */

    pAlgCreateParams.overlapBounds[0] = OVERLAP1_TOP1;
    pAlgCreateParams.overlapBounds[1] = OVERLAP1_TOP2;
    pAlgCreateParams.overlapBounds[2] = OVERLAP1_BOTTOM1;
    pAlgCreateParams.overlapBounds[3] = OVERLAP1_BOTTOM2;
    pAlgCreateParams.overlapBounds[4] = OVERLAP2_TOP1;
    pAlgCreateParams.overlapBounds[5] = OVERLAP2_TOP2;
    pAlgCreateParams.overlapBounds[6] = OVERLAP2_BOTTOM1;
    pAlgCreateParams.overlapBounds[7] = OVERLAP2_BOTTOM2;

    pAlgCreateParams.seamdetectionMode = SEAMDETECTIONMODE;
    pAlgCreateParams.wallDispDelta = WALLDISP_DELTA;
    pAlgCreateParams.maxDisparity = MAXDISPARITY;

    pAlgCreateParams.searchspacestep = SEARCHSPACEWIDTH;
    pAlgCreateParams.searchspacewidth = SEARCHSPACESTEP;

    pAlgCreateParams.temporalWeight = TEMPORALWEIGHT; //for temporal smoothing method 1; weighted cost function

    pAlgCreateParams.temporalSmoothing_minPix = TEMPORALSMOOTHING_MINPIX; //for temporal smoothing method 2
    pAlgCreateParams.temporalSmoothing_maxPix = TEMPORALSMOOTHING_MAXPIX; //limit displacement from previous seam

    pAlgCreateParams.Stitch_blendlength = DEFAULT_BLENDING_LENGTH;

    pAlgCreateParams.focalLength = FOCAL_LENGTH;

    pAlgCreateParams.vc_scale_height = VC_SCALE_HEIGHT; //scale in z-direction
    pAlgCreateParams.vc_scale_depth  = VC_SCALE_DEPTH; //scale in y-direction

    pAlgCreateParams.vc_wall_distance = VC_WALL_DISTANCE; //distance of wall from virtual camera
    pAlgCreateParams.vc_vf = VC_VF; //virtual camera focal length
    pAlgCreateParams.vc_rotx = VC_ROTX; //rotation of virtual camera about x-axis
    pAlgCreateParams.vc_roty = VC_ROTY;
    pAlgCreateParams.vc_rotz = VC_ROTZ;

    for (cnt = 0; cnt < pSeamDetectionLinkCreateParams->numCameras + 1; cnt++)
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

    // Eventually make this a pointer
    pAlgCreateParams.calmatBuffer[0] = -0.908077239990234;    //right mirror, R_cg
    pAlgCreateParams.calmatBuffer[1] = 0.0700302124023438;
    pAlgCreateParams.calmatBuffer[2] = 0.412905693054199;
    pAlgCreateParams.calmatBuffer[3] = -0.414768218994141;
    pAlgCreateParams.calmatBuffer[4] = -0.0138778686523438;
    pAlgCreateParams.calmatBuffer[5] = -0.909821510314941;
    pAlgCreateParams.calmatBuffer[6] = -0.0579843521118164;
    pAlgCreateParams.calmatBuffer[7] = -0.997447967529297;
    pAlgCreateParams.calmatBuffer[8] = 0.0416479110717773;
    pAlgCreateParams.calmatBuffer[9] = 639.625284194946;             //right mirror, t_cg
    pAlgCreateParams.calmatBuffer[10] = 92.1442842483521;
    pAlgCreateParams.calmatBuffer[11] = 413.566615104675;

    pAlgCreateParams.calmatBuffer[12] = -0.999813079833984;   //right stereo, R_cg
    pAlgCreateParams.calmatBuffer[13] = 0.00150299072265625;
    pAlgCreateParams.calmatBuffer[14] = 0.0192985534667969;
    pAlgCreateParams.calmatBuffer[15] = -0.0191764831542969;
    pAlgCreateParams.calmatBuffer[16] = 0.0589046478271484;
    pAlgCreateParams.calmatBuffer[17] = -0.998079299926758;
    pAlgCreateParams.calmatBuffer[18] = -0.00263690948486328;
    pAlgCreateParams.calmatBuffer[19] = -0.998262405395508;
    pAlgCreateParams.calmatBuffer[20] = -0.0588645935058594;
    pAlgCreateParams.calmatBuffer[21] = 314.304061889648;            //right stereo, t_cg
    pAlgCreateParams.calmatBuffer[22] = 82.4557867050171;
    pAlgCreateParams.calmatBuffer[23] = 347.910552024841;

    pAlgCreateParams.calmatBuffer[24] = -0.999636650085449;   //left stereo, R_cg
    pAlgCreateParams.calmatBuffer[25] = 0.0104665756225586;
    pAlgCreateParams.calmatBuffer[26] = 0.0248212814331055;
    pAlgCreateParams.calmatBuffer[27] = -0.0242528915405273;
    pAlgCreateParams.calmatBuffer[28] = 0.0512742996215820;
    pAlgCreateParams.calmatBuffer[29] = -0.998390197753906;
    pAlgCreateParams.calmatBuffer[30] = -0.0117225646972656;
    pAlgCreateParams.calmatBuffer[31] = -0.998629570007324;
    pAlgCreateParams.calmatBuffer[32] = -0.0510025024414063;
    pAlgCreateParams.calmatBuffer[33] = 326.004869461060;            //left stereo, t_cg
    pAlgCreateParams.calmatBuffer[34] = 81.2984409332275;
    pAlgCreateParams.calmatBuffer[35] = 344.517091751099;

    pAlgCreateParams.calmatBuffer[36] = -0.911864280700684;   //left mirror, R_cg
    pAlgCreateParams.calmatBuffer[37] = 0.0272388458251953;
    pAlgCreateParams.calmatBuffer[38] = -0.409585952758789;
    pAlgCreateParams.calmatBuffer[39] = 0.409553527832031;
    pAlgCreateParams.calmatBuffer[40] = -0.00702857971191406;
    pAlgCreateParams.calmatBuffer[41] = -0.912259101867676;
    pAlgCreateParams.calmatBuffer[42] = -0.0277271270751953;
    pAlgCreateParams.calmatBuffer[43] = -0.999604225158691;
    pAlgCreateParams.calmatBuffer[44] = -0.00474739074707031;
    pAlgCreateParams.calmatBuffer[45] = -61.0447759628296;    //left mirror, t_cg
    pAlgCreateParams.calmatBuffer[46] = 111.708771705627;
    pAlgCreateParams.calmatBuffer[47] = 678.089122772217;

    pSeamDetectionObj->pInputCalibParams  				= (float *)InputCalibParams;
    pSeamDetectionObj->seamDetectionMode		   		= pSeamDetectionLinkCreateParams->seamDetectionMode;
    
	////////////////////////////////////////////////////////////////////
    // First time call is just to get size for algorithm handle
    //  TBD - Currently since memquery function is dependent on alg handle
    //   space, there are two calls - first for alg handle and then for other
    //   requests. In future, once this dependency is removed, there will be
    //   only call of MemQuery
    Alg_SeamDetectionMemQuery(&pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = Utils_memAlloc(	UTILS_HEAPID_DDR_CACHED_SR,
															memRequests.memTab[memTabId].size,
															memRequests.memTab[memTabId].alignment);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
 	////////////////////////////////////////////////////////////////////
 	// Memory allocations for the requests done by algorithm
    //  For now treating all requests as persistent and allocating in DDR
    Alg_SeamDetectionMemQuery(&pAlgCreateParams, &memRequests, 0); 
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
	
	algHandle = Alg_SeamDetectionCreate(&pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pSeamDetectionObj->algHandle = algHandle;
    
	////////////////////////////////////////////////////////////////////
    // Creation of output buffers for output queue
	/** ALGLINK_SEAMDETECTION_OPQID_BLENDLUT */
	{ 
    outputQId = ALGLINK_SEAMDETECTION_OPQID_BLENDLUT;
    channelId = 0;

	metaBufSize = ALGLINK_BLENDLUT_SIZE;
	maxHeight = pSeamDetectionLinkCreateParams->maxOutputHeight;
	seamBufSize = maxHeight * sizeof(Word16);

	for(frameIdx = 0; frameIdx < pSeamDetectionObj->algLinkCreateParams.numOutBuffers; frameIdx++){
		/** Connects video frame buffer to system buffer payload */
		pSystemBuffer         = &(pSeamDetectionObj->buffers[outputQId][frameIdx]);
		pSystemMetaDataBuffer = &(pSeamDetectionObj->blendLUT[frameIdx]);

		pSystemBuffer->payload     = pSystemMetaDataBuffer;
		pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
		pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
		pSystemBuffer->chNum       = channelId;

		/** Buffer allocation done for buffer size and number of planes */
		pSystemMetaDataBuffer->numMetaDataPlanes = 3;
		pSystemMetaDataBuffer->bufAddr[0] =  Utils_memAlloc( UTILS_HEAPID_DDR_CACHED_SR,
															 metaBufSize,
															 ALGORITHMLINK_FRAME_ALIGN);
		pSystemMetaDataBuffer->bufAddr[1] = Utils_memAlloc( UTILS_HEAPID_DDR_CACHED_SR,
                                                             seamBufSize,
                                                             ALGORITHMLINK_FRAME_ALIGN);
        pSystemMetaDataBuffer->bufAddr[2] = Utils_memAlloc( UTILS_HEAPID_DDR_CACHED_SR,
                                                             seamBufSize,
                                                             ALGORITHMLINK_FRAME_ALIGN);
		        													 
		pSystemMetaDataBuffer->metaBufSize[0]    = metaBufSize;
		pSystemMetaDataBuffer->metaBufSize[1]    = seamBufSize;
        pSystemMetaDataBuffer->metaBufSize[2]    = seamBufSize;

		pSystemMetaDataBuffer->metaFillLength[0] = metaBufSize;
        pSystemMetaDataBuffer->metaFillLength[1] = seamBufSize;
        pSystemMetaDataBuffer->metaFillLength[2] = seamBufSize;

		pSystemMetaDataBuffer->flags             = 0;
		UTILS_assert(pSystemMetaDataBuffer->bufAddr[0] != NULL);
		
		/** Puts the buffer into an empty queue */
		AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer); }
	
	}
    if (ENABLEINPUT == 1)
    {
    inputQId = ALGLINK_SEAMDETECTION_IPQID_BLENDLUT;
    status  = Utils_queCreate(&(pSeamDetectionObj->localInputQ[inputQId].queHandle),
                               SEAMDETECTION_LINK_MAX_LOCALQUEUELENGTH,
                               (pSeamDetectionObj->localInputQ[inputQId].queMem),
                               UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(&(pSeamDetectionObj->localInputQ[inputQId].queHandle) != NULL);
    UTILS_assert(&(pSeamDetectionObj->localInputQ[inputQId].queMem) != NULL);                            
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}

	////////////////////////////////////////////////////////////////////
	// Stat collection
    //pSeamDetectionObj->frameDropCounter = 0;
    pSeamDetectionObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst( AlgorithmLink_getLinkId(pObj),"ALG_SEAMDETECTION");
    UTILS_assert(NULL != pSeamDetectionObj->linkStatsInfo);
    
	////////////////////////////////////////////////////////////////////
	// Seems to be for outdated structs but currently they are implemented in the process fucntion         
    pSeamDetectionObj->isFirstFrameRecv   = FALSE;
    pSeamDetectionObj->isFirstOPGenerated = FALSE;
    pSeamDetectionObj->receivedMultiviewFlag  = FALSE;

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
Int32 AlgorithmLink_SeamDetectionProcess(void * pObj)
{
    AlgorithmLink_SeamDetectionObj 		* pSeamDetectionObj;
    void                       				* algHandle;
    AlgorithmLink_SeamDetectionInputQueId    inputQId;
    AlgorithmLink_SeamDetectionOutputQueId   outputQId;
    
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    UInt32                       viewId;
    Bool                         bufDropFlag;
            
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferBlendLUT_Prev;
    
    System_MetaDataBuffer      			* pBlendLUTPrevBuffer;
    System_VideoFrameCompositeBuffer	* pMultiviewInputCompositeBuffer;

    System_Buffer              * pSysBufferBlendLUT;
    void                       * outBlendLUTPtr;
    Word16                    * outSeam1;
    Word16                    * outSeam2;

    System_MetaDataBuffer				* pBlendLUTBuffer;


	void                       * inBlendLUTPtr;
	Bool isProcessCallDoneFlag;
	////////////////////////////////////////////////////////////////////
    AlgorithmLink_SeamDetectionCreateParams  * pSeamDetectionLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    pSeamDetectionObj = (AlgorithmLink_SeamDetectionObj *)
                         AlgorithmLink_getAlgorithmParamsObj(pObj);
	UTILS_assert(NULL != pSeamDetectionObj);
    linkStatsInfo = pSeamDetectionObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                  = pSeamDetectionObj->algHandle;
    UTILS_assert(NULL != algHandle);
    pSeamDetectionLinkCreateParams = (AlgorithmLink_SeamDetectionCreateParams *)&pSeamDetectionObj->algLinkCreateParams;
	UTILS_assert(NULL != pSeamDetectionLinkCreateParams);

	////////////////////////////////////////////////////////////////////
    // Get Input Buffers from previous link and queue them up locally
    /** ALGLINK_SEAMDETECTION_IPQID_MULTIVIEW_RAW */
    {
    inputQId = ALGLINK_SEAMDETECTION_IPQID_MULTIVIEW_RAW;
    status = System_getLinksFullBuffers(	pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkId,
								pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
								&inputBufList);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++){
           
            if(pSeamDetectionObj->receivedMultiviewFlag == TRUE)
            {
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pSeamDetectionObj->sysBufferMultiview;
                bufDropFlag = FALSE;

                status = AlgorithmLink_releaseInputBuffer(
                    pObj,
                    inputQId,
                    pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkId,
                    pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                    &inputBufListReturn,
                    &bufDropFlag);
                pSeamDetectionObj->receivedMultiviewFlag = FALSE;
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            }

            pSeamDetectionObj->sysBufferMultiview = inputBufList.buffers[bufId];
            /*TBD: Check for parameter correctness. If in error, return input*/
            pSeamDetectionObj->receivedMultiviewFlag = TRUE;
        }
    }

	}

    if (ENABLEINPUT == 1)   
    {
    inputQId = ALGLINK_SEAMDETECTION_IPQID_BLENDLUT;
    status = System_getLinksFullBuffers(	pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkId,
								pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
								&inputBufList);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {           
            pSysBufferBlendLUT_Prev = inputBufList.buffers[bufId];
            //pMultiviewInputCompositeBuffer = (System_VideoFrameCompositeBuffer *)(pSysBufferMultiview_Raw->payload);		
			
            /** Check for parameter correctness. If in error, return input */
            
            
            
            if (pSysBufferBlendLUT_Prev != NULL)
            {
                status = Utils_quePut(	&(pSeamDetectionObj->localInputQ[inputQId].queHandle), 
										pSysBufferBlendLUT_Prev, 
									BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
          }
    }

	}

    ////////////////////////////////////////////////////////////////////
    // Restarts stat collection
    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);
    if(pSeamDetectionObj->isFirstFrameRecv==FALSE){
        pSeamDetectionObj->isFirstFrameRecv = TRUE;
        Utils_resetLinkStatistics(  &linkStatsInfo->linkStats,
                                    1,//ALGLINK_NUM_OUTPUT_FRAME_MULTIVIEW,
                                    1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);}

    linkStatsInfo->linkStats.newDataCmdCount++;

    ////////////////////////////////////////////////////////////////////
    // Continuous loop to perform the algorithm as buffers are available
    while(1)
    {
		isProcessCallDoneFlag = FALSE;
	    ////////////////////////////////////////////////////////////////////
	    // Checks if all the inputs are available before running the main if statement 
	    //  This may need to be changed in the future as I am pretty sure this limits framerates

		if( (pSeamDetectionObj->receivedMultiviewFlag) &&
		( ( (Utils_queGetQueuedCount(&(pSeamDetectionObj->localInputQ[ALGLINK_SEAMDETECTION_IPQID_BLENDLUT].queHandle))>0) && (ENABLEINPUT == 1)) ||
		ENABLEINPUT != 1 ) )
		{
			/** ALGLINK_SEAMDETECTION_OPQID_MULTIVIEW_TRANSFORMED */
			{
			pSysBufferBlendLUT = NULL;
			outputQId = ALGLINK_SEAMDETECTION_OPQID_BLENDLUT;
			channelId = 0;
			status = AlgorithmLink_getEmptyOutputBuffer(pObj, outputQId, channelId, &pSysBufferBlendLUT);

			if(status != SYSTEM_LINK_STATUS_SOK){
			  linkStatsInfo->linkStats.outBufErrorCount++;
			  //Vps_printf("No output buffer SD");
			  break;}
			UTILS_assert(pSysBufferBlendLUT != NULL);

			pBlendLUTBuffer = (System_MetaDataBuffer *)pSysBufferBlendLUT->payload;
			outBlendLUTPtr = pBlendLUTBuffer->bufAddr[0];
			outSeam1       = pBlendLUTBuffer->bufAddr[1];
			outSeam2       = pBlendLUTBuffer->bufAddr[2];

			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			UTILS_assert(pSeamDetectionObj->sysBufferMultiview != NULL);
			pMultiviewInputCompositeBuffer = (System_VideoFrameCompositeBuffer *)(pSeamDetectionObj->sysBufferMultiview->payload);
			}
			/** ALGLINK_SEAMDETECTION_IPQID_BLENDLUT */
			if (ENABLEINPUT == 1 && (pSeamDetectionObj->isFirstOPGenerated == FALSE))
	        {
		    inBlendLUTPtr = NULL;
		    UTILS_assert(&(pSeamDetectionObj->localInputQ[ALGLINK_SEAMDETECTION_IPQID_BLENDLUT].queHandle) != NULL);
			status = Utils_queGet(  &(pSeamDetectionObj->localInputQ[ALGLINK_SEAMDETECTION_IPQID_BLENDLUT].queHandle),
								    (Ptr *)&pSysBufferBlendLUT_Prev,
								    1,
								    BSP_OSAL_NO_WAIT);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			UTILS_assert(pSysBufferBlendLUT_Prev != NULL);					    
			pBlendLUTPrevBuffer = (System_MetaDataBuffer *)(pSysBufferBlendLUT_Prev->payload);
			inBlendLUTPtr = pBlendLUTPrevBuffer->bufAddr[0];
			}
			else
			{
				inBlendLUTPtr = (uWord32*)TempLUT;
			}
			///////////////////////////////////////////////////////////////////
			// Invalidates cache to be used for buffers
			for(viewId = 0; viewId < ALGORITHM_LINK_MAX_VIEWS+1 ;viewId++){
				Cache_inv( 	pMultiviewInputCompositeBuffer->bufAddr[0][viewId],
							(pSeamDetectionLinkCreateParams->maxInputWidth*pSeamDetectionLinkCreateParams->maxInputHeight), 
							Cache_Type_ALLD, TRUE);
				Cache_inv(	pMultiviewInputCompositeBuffer->bufAddr[1][viewId],
							((pSeamDetectionLinkCreateParams->maxInputWidth*pSeamDetectionLinkCreateParams->maxInputHeight)/2),
							Cache_Type_ALLD, TRUE);}
	
			/////////////////////////////////////////////////////////////////////
			// Sets up timestamps for outputs in respect to their inputs
			pSysBufferBlendLUT->srcTimestamp = pSeamDetectionObj->sysBufferMultiview->srcTimestamp;
            pSysBufferBlendLUT->frameId = pSeamDetectionObj->sysBufferMultiview->frameId;
            pSysBufferBlendLUT->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
            
			//pVideoOutFrame->numFrames = pVideoInFrame->numFrames;
			//////////////////////////////////////////////////////////////////////
			// Algorithm Process Run
			status = Alg_SeamDetectionProcess(algHandle,
								 pMultiviewInputCompositeBuffer,
								 inBlendLUTPtr,
								 outBlendLUTPtr,
								 outSeam1,
								 outSeam2,
								 pSeamDetectionObj->pInputCalibParams,
								 pSeamDetectionObj->seamDetectionMode);

			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			UTILS_assert(outBlendLUTPtr != NULL);
	
			////////////////////////////////////////////////////////////////////////
			// Writes back any left over data
			Cache_wb(pBlendLUTBuffer->bufAddr[0],
                     pBlendLUTBuffer->metaBufSize[0],
                     Cache_Type_ALLD, TRUE);

            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                pSysBufferBlendLUT->linkLocalTimestamp);
            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pSysBufferBlendLUT->srcTimestamp);				
			
			isProcessCallDoneFlag = TRUE;
			/////////////////////////////////////////////////////////////////////////
			// Post-processing for buffers and stats
			/** Multiview Stats */
			
			if (pSeamDetectionObj->sysBufferMultiview != NULL){
				linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
				linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;}
			/** Disparity Stats */

			if((ENABLEINPUT == 1)&& (pSeamDetectionObj->isFirstOPGenerated == FALSE))
			{
			    if (pSysBufferBlendLUT_Prev != NULL){
				    linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
				    linkStatsInfo->linkStats.chStats[0].outBufCount[0]++; }
			}
			////////////////////////////////////////////////////////////////////////
			// Fills full output buffer to be given to next link and informs next link of new data
			/** outputQId = ALGLINK_SEAMDETECTION_OPQID_BLENDLUT */
			{
            outputQId = ALGLINK_SEAMDETECTION_OPQID_BLENDLUT;
            status    = AlgorithmLink_putFullOutputBuffer(pObj,outputQId,pSysBufferBlendLUT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            
            System_sendLinkCmd(	pSeamDetectionLinkCreateParams->outQueParams[outputQId].nextLink,
								SYSTEM_CMD_NEW_DATA, NULL);
			}
	
			///////////////////////////////////////////////////////////////////////
			// Releases output buffers, free'ing the memory
			/** ALGLINK_SEAMDETECTION_OPQID_BLENDLUT */
			{
			outputQId = ALGLINK_SEAMDETECTION_OPQID_BLENDLUT;
			outputBufListReturn.numBuf     = 1;
            outputBufListReturn.buffers[0] = pSysBufferBlendLUT;
            status = AlgorithmLink_releaseOutputBuffer(pObj, outputQId, &outputBufListReturn);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
			}	
			////////////////////////////////////////////////////////////////////////
			// Releases input buffers, free'ing the memory
			bufDropFlag = FALSE;
			if((ENABLEINPUT == 1) && (pSeamDetectionObj->isFirstOPGenerated == FALSE))
			{
			inputQId                      = ALGLINK_SEAMDETECTION_IPQID_BLENDLUT;
			inputBufListReturn.numBuf     = 1;
			inputBufListReturn.buffers[0] = pSysBufferBlendLUT_Prev;
			status = AlgorithmLink_releaseInputBuffer( pObj, inputQId,
											  pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkId,
											  pSeamDetectionLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
											  &inputBufListReturn,&bufDropFlag);
			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
				
			}
	        pSeamDetectionObj->isFirstOPGenerated = TRUE;
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
Int32 AlgorithmLink_SeamDetectionDelete(void * pObj)
{
    Int32  status    = SYSTEM_LINK_STATUS_SOK;
    UInt32 maxHeight;
    UInt32 memTabId;
    UInt32 frameIdx;
    AlgLink_MemRequests          memRequests;
	AlgorithmLink_SeamDetectionInputQueId     inputQId;
    AlgorithmLink_SeamDetectionObj           * pSeamDetectionObj;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    UInt32                       metaBufSize, seamBufSize;
	
    pSeamDetectionObj = (AlgorithmLink_SeamDetectionObj *)AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pSeamDetectionObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_SeamDetectionDelete(pSeamDetectionObj->algHandle, &memRequests);

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
	metaBufSize = ALGLINK_BLENDLUT_SIZE;
    maxHeight = ALGLINK_OUTPUT_FRAME_HEIGHT2; //pSeamDetectionLinkCreateParams->maxOutputHeight; // Lucas--eventually change this to create params
    seamBufSize = maxHeight * sizeof(Word16);
	for(frameIdx =0 ; frameIdx < pSeamDetectionObj->algLinkCreateParams.numOutBuffers; frameIdx++){
			//pSystemBuffer           = &(pSeamDetectionObj->buffers[outputQId][frameIdx]);
		pSystemMetaDataBuffer = &(pSeamDetectionObj->blendLUT[frameIdx]);

		/** Buffer allocation done for maxHeight, outputPitch and for 420SP format */
		status = Utils_memFree(	UTILS_HEAPID_DDR_CACHED_SR,
								pSystemMetaDataBuffer->bufAddr[0],
								metaBufSize); // ALGLINK_OUTPUT_FRAME_HEIGHT
        /** Buffer allocation done for maxHeight, outputPitch and for 420SP format */
        status = Utils_memFree( UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[1],
                                seamBufSize); // ALGLINK_OUTPUT_FRAME_HEIGHT
        /** Buffer allocation done for maxHeight, outputPitch and for 420SP format */
        status = Utils_memFree( UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[2],
                                seamBufSize); // ALGLINK_OUTPUT_FRAME_HEIGHT
		UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);}
	}
    /** ALGLINK_SEAMDETECTION_IPQID_BLENDLUT */
	{
    inputQId = ALGLINK_SEAMDETECTION_IPQID_BLENDLUT;
    status = Utils_queDelete(&(pSeamDetectionObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}
    ////////////////////////////////////////////////////////////////////
    // Space for algorithm specific object gets freed here
    status = Utils_memFree(	UTILS_HEAPID_DDR_CACHED_SR,
							pSeamDetectionObj,
							sizeof(AlgorithmLink_SeamDetectionObj));
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

Int32 AlgorithmLink_SeamDetectionControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_SeamDetectionObj     * pSeamDetectionObj;
    AlgorithmLink_ControlParams    		* pAlgLinkControlPrm;
    AlgorithmLink_SeamDetectionObj     * algHandle;
    Int32                        		status    = SYSTEM_LINK_STATUS_SOK;

    pSeamDetectionObj = (AlgorithmLink_SeamDetectionObj *)AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pSeamDetectionObj->algHandle;

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */
    switch(pAlgLinkControlPrm->controlCmd){
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_SeamDetectionPrintStatistics(pObj, pSeamDetectionObj);
            break;

        default:
            status = Alg_SeamDetectionControl(	algHandle,&(pSeamDetectionObj->controlParams));
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
Int32 AlgorithmLink_SeamDetectionStop(	void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pSeamDetectionObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SeamDetectionPrintStatistics(	void *pObj, AlgorithmLink_SeamDetectionObj *pSeamDetectionObj)
{
    UTILS_assert(NULL != pSeamDetectionObj->linkStatsInfo);

    Utils_printLinkStatistics(&pSeamDetectionObj->linkStatsInfo->linkStats, "ALG_SEAMDETECTION", TRUE);

    Utils_printLatency("ALG_SEAMDETECTION",
                       &pSeamDetectionObj->linkStatsInfo->linkLatency,
                       &pSeamDetectionObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
