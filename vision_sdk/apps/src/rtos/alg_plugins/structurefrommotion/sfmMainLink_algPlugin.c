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
 * \file sfmMainLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Sfm Main Link
 *
 * \version 0.0 (Jun 2015) : [MM] First version
 * \version 0.0 (Jan 2016) : [MM] Post-CES cleanup
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sfmMainLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/alg_plugins/commonutils/lens_distortion_correction/ldc_config.h>

//intercept SOF data and read data from dumped data file instead
#ifdef SFM_MAIN_USE_DUMPED_DATA_ON
	extern UInt32 dumpedNumFrms;
#endif

//link for multi-camera calibration does not exist yet --> will not process that input buffer

/*delay start of SfmMain*/
#define SFM_MAIN_START_DELAY_FRAMES 0

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmMain_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_sfmMainCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_sfmMainProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_sfmMainControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_sfmMainStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_sfmMainDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SFMMAIN;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmMainCreate(void * pObj, void * pCreateParams)
{
	AlgorithmLink_SfmMainObj              * pLinkObj;
	AlgorithmLink_SfmMainCreateParams     * pLinkCreateParams;
	SfmMain_CreateParams       		      * pAlgCreateParams;

	Int32 status    = SYSTEM_LINK_STATUS_SOK;

#ifdef VERBOSE_ON
    Vps_printf("SFM_MAIN: ++++++++++ Entering Create");
#endif

    //Allocate Memory for AlgObject
    //================================
	/* Space for Algorithm specific object gets allocated here.
	  * Pointer gets recorded in algorithmParams */
	if(sizeof(AlgorithmLink_SfmMainObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
	{
	    pLinkObj = (AlgorithmLink_SfmMainObj *)
	                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
	                                   sizeof(AlgorithmLink_SfmMainObj), 32);
	}
	else
	{
	    pLinkObj = (AlgorithmLink_SfmMainObj *)
	                    malloc(sizeof(AlgorithmLink_SfmMainObj));
	}

	UTILS_assert(pLinkObj!=NULL);

	AlgorithmLink_setAlgorithmParamsObj(pObj, pLinkObj);


    //Set pointers and take copy of create params
    //==================================================
	//Link level create params
	pLinkCreateParams =
	        (AlgorithmLink_SfmMainCreateParams *)pCreateParams;

	memcpy((void*)(&pLinkObj->linkCreateParams),
	       (void*)(pLinkCreateParams),
	        sizeof(AlgorithmLink_SfmMainCreateParams)
	      );
	//Algorithm level create params
	pAlgCreateParams = (SfmMain_CreateParams *)&(pLinkObj->linkCreateParams.algCreateParams);


	//Get input Queue Info
	//======================================
    Int32                       				   numInputQUsed;
	AlgorithmLink_SfmMainInputQueId   	 	 	   inputQId;
    AlgorithmLink_InputQueueInfo         		 * pInputQInfo;
    System_LinkInfo                                prevLinkInfo;

	pInputQInfo  = &pLinkObj->inputQInfo[0];
    numInputQUsed     = ALGLINK_SFMMAIN_IPQID_MAXIPQ;

    //Optical Flow Input
	inputQId = ALGLINK_SFMMAIN_IPQID_SOFTRACKS;
    pInputQInfo[inputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    status = System_linkGetInfo(
                    pLinkCreateParams->inQueParams[inputQId].prevLinkId,
                    &prevLinkInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

	//Set output Queue Info
	//======================================
    Int32                        				   numOutputQUsed;
	AlgorithmLink_SfmMainOutputQueId 	   outputQId;
    AlgorithmLink_OutputQueueInfo        		 * pOutputQInfo;
    pOutputQInfo = &pLinkObj->outputQInfo[0];
    numOutputQUsed    = ALGLINK_SFMMAIN_OPQID_MAXOPQ;

    //Camera Poses
    outputQId = ALGLINK_SFMMAIN_OPQID_POSES;
    pOutputQInfo[outputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[outputQId].queInfo.numCh = 1; //# of channels used
    pOutputQInfo[outputQId].queInfo.chInfo[0].flags = 0;

    //Camera Points
    outputQId = ALGLINK_SFMMAIN_OPQID_POINTS;
    pOutputQInfo[outputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[outputQId].queInfo.numCh = 1; //# of channels used
    pOutputQInfo[outputQId].queInfo.chInfo[0].flags = 0;

    //Camera LTV API
    outputQId = ALGLINK_SFMMAIN_OPQID_LTVAPI;
    pOutputQInfo[outputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[outputQId].queInfo.numCh = 1; //# of channels used
    pOutputQInfo[outputQId].queInfo.chInfo[0].flags = 0;


	//Init Queue Info
	//======================================
    AlgorithmLink_queueInfoInit(pObj,
                                numInputQUsed,
                                pInputQInfo,
                                numOutputQUsed,
                                pOutputQInfo
                                );

    //Algorithm's Memory Requests
    //===========================================
    AlgLink_MemRequests		   memRequests;
    UInt32                     memTabId;

    Alg_SfmMainMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    Alg_SfmMainMemQuery(pAlgCreateParams, &memRequests, 0);

    UInt8 *dataPtr;
    UInt32 ii;
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
        if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD )
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

        dataPtr = (UInt8 *)memRequests.memTab[memTabId].basePtr;
        /*set all requested memory to 0*/
        for (ii=0;ii<memRequests.memTab[memTabId].size;ii++)
        	*(dataPtr+ii)=0;

        }
    }

    Cache_inv(
            pAlgCreateParams->pLensPrm,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    pAlgCreateParams->pLensPrm = pLinkCreateParams->pLensPrm;

    //Algorithm Creation
    //============================================
    void *algHandle = Alg_SfmMainCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pLinkObj->algHandle = algHandle;


    //Initialize Output Buffers
    //============================================
    //- Connecting metadata buffer to system buffer payload
    //- Memory allocation for buffers
    //- Put the buffer into empty queue
    System_Buffer              * outputBuffer;
    System_MetaDataBuffer      * outputBuffer_payload;
    UInt32 metaBufSize;
    Int32 bufferId;

    for (bufferId=0; bufferId < SFMMAIN_LINK_MAX_NUM_OUTPUT; bufferId++)
    {
    	//POSES
    	//===============================================
		outputQId = ALGLINK_SFMMAIN_OPQID_POSES;
		outputBuffer = &(pLinkObj->buffers[outputQId][bufferId]);
		outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][bufferId]);
		outputBuffer_payload->numMetaDataPlanes = 2;
		outputBuffer_payload->flags             = 0;

		outputBuffer->payload     = outputBuffer_payload;
		outputBuffer->payloadSize = sizeof(System_MetaDataBuffer);
		outputBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
		outputBuffer->chNum       = 0;

		//vehicle pose
		metaBufSize = SFMMAIN_POSES0_BUFFER_SIZE;
	   	outputBuffer_payload->bufAddr[0] =  Utils_memAlloc(
	                                            UTILS_HEAPID_DDR_CACHED_SR,
	                                            metaBufSize,
	                                            ALGORITHMLINK_FRAME_ALIGN);
	    outputBuffer_payload->metaBufSize[0]    = metaBufSize;
	    outputBuffer_payload->metaFillLength[0] = metaBufSize;
	    UTILS_assert(outputBuffer_payload->bufAddr[0] != NULL);

		//camera poses
		metaBufSize = SFMMAIN_POSES1_BUFFER_SIZE;
	   	outputBuffer_payload->bufAddr[1] =  Utils_memAlloc(
	                                            UTILS_HEAPID_DDR_CACHED_SR,
	                                            metaBufSize,
	                                            ALGORITHMLINK_FRAME_ALIGN);
	    outputBuffer_payload->metaBufSize[1]    = metaBufSize;
	    outputBuffer_payload->metaFillLength[1] = metaBufSize;
	    UTILS_assert(outputBuffer_payload->bufAddr[1] != NULL);

	    AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, outputBuffer);

    	//POINTS
    	//===============================================
		outputQId = ALGLINK_SFMMAIN_OPQID_POINTS;
		outputBuffer = &(pLinkObj->buffers[outputQId][bufferId]);
		outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][bufferId]);
		outputBuffer_payload->numMetaDataPlanes = 2;
		outputBuffer_payload->flags             = 0;

		outputBuffer->payload     = outputBuffer_payload;
		outputBuffer->payloadSize = sizeof(System_MetaDataBuffer);
		outputBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
		outputBuffer->chNum       = 0;

		//3D points
		metaBufSize = SFMMAIN_POINTS0_BUFFER_SIZE;
	   	outputBuffer_payload->bufAddr[0] =  Utils_memAlloc(
	                                            UTILS_HEAPID_DDR_CACHED_SR,
	                                            metaBufSize,
	                                            ALGORITHMLINK_FRAME_ALIGN);
	    outputBuffer_payload->metaBufSize[0]    = metaBufSize;
	    outputBuffer_payload->metaFillLength[0] = metaBufSize;
	    UTILS_assert(outputBuffer_payload->bufAddr[0] != NULL);

		//confidence values
		metaBufSize = SFMMAIN_POINTS1_BUFFER_SIZE;
	   	outputBuffer_payload->bufAddr[1] =  Utils_memAlloc(
	                                            UTILS_HEAPID_DDR_CACHED_SR,
	                                            metaBufSize,
	                                            ALGORITHMLINK_FRAME_ALIGN);
	    outputBuffer_payload->metaBufSize[1]    = metaBufSize;
	    outputBuffer_payload->metaFillLength[1] = metaBufSize;
	    UTILS_assert(outputBuffer_payload->bufAddr[1] != NULL);

	    AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, outputBuffer);

    }

    //LTV API (ONLY ONE BUFFER!)
    //===============================================
	outputQId = ALGLINK_SFMMAIN_OPQID_LTVAPI;
	outputBuffer = &(pLinkObj->buffers[outputQId][0]);
	outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][0]);
	outputBuffer_payload->numMetaDataPlanes = 1;
	outputBuffer_payload->flags             = 0;

	outputBuffer->payload     = outputBuffer_payload;
	outputBuffer->payloadSize = sizeof(System_MetaDataBuffer);
	outputBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
	outputBuffer->chNum       = 0;

	//LTV API
	metaBufSize = SFMMAIN_LTVAPI_BUFFER_SIZE;
	outputBuffer_payload->bufAddr[0] =  Utils_memAlloc(
	                                         UTILS_HEAPID_DDR_CACHED_SR,
	                                         metaBufSize,
	                                         ALGORITHMLINK_FRAME_ALIGN);
	outputBuffer_payload->metaBufSize[0]    = metaBufSize;
	outputBuffer_payload->metaFillLength[0] = metaBufSize;
	UTILS_assert(outputBuffer_payload->bufAddr[0] != NULL);

	AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, outputBuffer);

    //Other Initializations
	//========================================
    pLinkObj->frameDropCounter = 0;

    pLinkObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_SFMMAIN");
    UTILS_assert(NULL != pLinkObj->linkStatsInfo);

    pLinkObj->isFirstFrameRecv   = FALSE;
    pLinkObj->isFirstOPGenerated = FALSE;
    pLinkObj->algoCallCounter = 0;
    pLinkObj->delayCounter = 0;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin
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
Int32 AlgorithmLink_sfmMainProcess(void * pObj)
{
	AlgorithmLink_SfmMainObj              * pLinkObj;
	AlgorithmLink_SfmMainCreateParams     * pLinkCreateParams;

	AlgorithmLink_SfmMainOutputQueId 	 outputQId;
	AlgorithmLink_SfmMainInputQueId      inputQId;

	Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 channelId;
    Bool bufDropFlag;

    Int32 executeMode = -1;//-1:no process called, 0,1,2: process called on dumped data, 3:process called on SOF input buffers
    Int32 processCallNeeded = 1; //determines is Alg Process is reached and executed
    UInt32 calibDataFlag = 0;

    System_LinkStatistics	   * linkStatsInfo;

#ifdef VERBOSE_ON
    Vps_printf("SFM_MAIN: ++++++++++ Entering Process");
#endif

    pLinkObj = (AlgorithmLink_SfmMainObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pLinkObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    void *algHandle = pLinkObj->algHandle;
    pLinkCreateParams =
    		(AlgorithmLink_SfmMainCreateParams *) &pLinkObj->linkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);


	//If first call, reset statistics
	//===============================
	if(pLinkObj->isFirstFrameRecv==FALSE)
    {
        pLinkObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    //If input buffer is full, process data
    //=================================================
    System_BufferList      			   inputBufList;
    System_Buffer 					 * outputBuffer1; //poses
    System_MetaDataBuffer 			 * outputBuffer1_payload;
    System_Buffer 					 * outputBuffer2; //points
    System_MetaDataBuffer 			 * outputBuffer2_payload;
    System_Buffer 					 * outputBuffer3; //Ltv API
    System_MetaDataBuffer 			 * outputBuffer3_payload;
    Void    						 * outputBuffer3_payload_bufAddr;
    System_Buffer       			 * inputBuffer1; //sof tracks
    System_VideoFrameCompositeBuffer * inputBuffer1_payload;
	UInt32 bufId;

	//check ALGLINK_SFMMAIN_IPQID_SOFTRACKS input
	//------------------------------------------------
	inputQId = ALGLINK_SFMMAIN_IPQID_SOFTRACKS;

	inputBufList.numBuf = 0;
    status = System_getLinksFullBuffers(
        pLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);


    if(inputBufList.numBuf && status == SYSTEM_LINK_STATUS_SOK)
    {
    	//Get pointer to input data
    	for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
    	{
			inputBuffer1 = inputBufList.buffers[bufId];
			if(inputBuffer1 == NULL)
			{
				Vps_printf("ERROR: inputBuffer1==NULL in SfM Main AlgPlugin Process");
				UTILS_assert(NULL);
			}
			inputBuffer1_payload =
					(System_VideoFrameCompositeBuffer  *)inputBuffer1->payload;

			//============================================
			//get buffer for ALGLINK_SFMMAIN_OPQID_POSES
			//=============================================
			outputQId =  ALGLINK_SFMMAIN_OPQID_POSES;
			channelId = 0;
			//request empty buffer from framework
			status = AlgorithmLink_getEmptyOutputBuffer(
						pObj, outputQId, channelId,	&outputBuffer1);

			if(status != SYSTEM_LINK_STATUS_SOK)
			{
				linkStatsInfo->linkStats.outBufErrorCount++;
			}
			else
			{
				//============================================
				//get buffer for ALGLINK_SFMMAIN_OPQID_POINTS
				//=============================================
				outputQId =  ALGLINK_SFMMAIN_OPQID_POINTS;
				channelId = 0;
				//request empty buffer from framework
				status = AlgorithmLink_getEmptyOutputBuffer(
							pObj, outputQId, channelId, &outputBuffer2);

				if(status != SYSTEM_LINK_STATUS_SOK)
				{
					linkStatsInfo->linkStats.outBufErrorCount++;
					AlgorithmLink_putEmptyOutputBuffer(
							pObj, ALGLINK_SFMMAIN_OPQID_POSES, outputBuffer1);
				}
				else
				{
					//============================================
					//get buffer for ALGLINK_SFMMAIN_OPQID_LTVAPI
					//=============================================
					outputQId =  ALGLINK_SFMMAIN_OPQID_LTVAPI;
					channelId = 0;
					//request empty buffer from framework
					status = AlgorithmLink_getEmptyOutputBuffer(
								pObj, outputQId, channelId, &outputBuffer3);

					if(status != SYSTEM_LINK_STATUS_SOK)
					{
						status = SYSTEM_LINK_STATUS_SOK;
						pLinkObj->isLTVBufferAvailable = FALSE;
					}
					else
					{
						pLinkObj->isLTVBufferAvailable = TRUE;
					}
				}

				/*--------------------------------------------------------------
				 *  DONE REQUESTING BUFFERS, START SET UP DATA POINTERS
				 *  ------------------------------------------------------------ */
				if (status == SYSTEM_LINK_STATUS_SOK)
				{
					outputBuffer1->srcTimestamp = inputBuffer1->srcTimestamp;
					outputBuffer1->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
					outputBuffer1_payload = (System_MetaDataBuffer *)outputBuffer1->payload;

					outputBuffer2->srcTimestamp = inputBuffer1->srcTimestamp;
					outputBuffer2->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
					outputBuffer2_payload = (System_MetaDataBuffer *)outputBuffer2->payload;

					if (pLinkObj->isLTVBufferAvailable == TRUE)
					{
						outputBuffer3->srcTimestamp = inputBuffer1->srcTimestamp;
						outputBuffer3->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
						outputBuffer3_payload = (System_MetaDataBuffer *)outputBuffer3->payload;
						outputBuffer3_payload_bufAddr = outputBuffer3_payload->bufAddr[0];
					}
					else
					{
						outputBuffer3_payload_bufAddr = NULL;
					}

					if (pLinkObj->delayCounter<SFM_MAIN_START_DELAY_FRAMES)
					{
						processCallNeeded = 0;
						pLinkObj->delayCounter++;
					}

					if (processCallNeeded)
					{
#ifdef SFM_MAIN_USE_DUMPED_DATA_ON
						  if (pLinkObj->isLTVBufferAvailable)
						  {
							  pLinkObj->algoCallCounter++;
							  if (pLinkObj->algoCallCounter>dumpedNumFrms)
							  {
								  Vps_printf("Reached End of Dumped Data --> Abort");
								  UTILS_assert(0);
							  }
							  //set LTV flag to alternate
							  if (pLinkObj->algoCallCounter==1)
								  pLinkObj->isLTVBufferAvailable = TRUE;
							  else if (pLinkObj->algoCallCounter%2==0)
								  pLinkObj->isLTVBufferAvailable = TRUE;
							  else
								  pLinkObj->isLTVBufferAvailable = FALSE;
						  }
						  else
							  processCallNeeded = 0; //wait until LTVBuffer is available
#else
						  pLinkObj->algoCallCounter++;
#endif
						  /*HANDLE CALIBRATION DATA*/
						  if (pLinkObj->algoCallCounter==1)
						  {
							  calibDataFlag = 1;
						  }
						  else
						  {
							  calibDataFlag = 0;
						  }

						  /*ALGORITHM PROCESS FUNCTION*/
						  status = Alg_SfmMainProcess(
								   algHandle,
								   pLinkObj->linkCreateParams.calmatAddr,
								   (void *)inputBuffer1_payload->bufAddr[0],
								   (UInt16 **)inputBuffer1_payload->bufAddr[2],
								   outputBuffer1_payload->bufAddr[0],
								   outputBuffer1_payload->bufAddr[1],
								   outputBuffer2_payload->bufAddr[0],
								   outputBuffer2_payload->bufAddr[1],
								   outputBuffer3_payload_bufAddr,
								   pLinkObj->isLTVBufferAvailable,
								   calibDataFlag,
								   &executeMode);

#ifdef SFM_MAIN_USE_DUMPED_DATA_ON
						  processCallNeeded = 0;
						  pLinkObj->isLTVBufferAvailable=TRUE;
#endif
					} /*end if (processCallNeeded)*/

					UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

					if (executeMode>-1)
					{
						Cache_wb(outputBuffer1_payload->bufAddr[0],
							   outputBuffer1_payload->metaBufSize[0],
							   Cache_Type_ALLD,
							   TRUE);
						Cache_wb(outputBuffer1_payload->bufAddr[1],
							   outputBuffer1_payload->metaBufSize[1],
							   Cache_Type_ALLD,
							   TRUE);
						Cache_wb(outputBuffer2_payload->bufAddr[0],
							   outputBuffer2_payload->metaBufSize[0],
							   Cache_Type_ALLD,
							   TRUE);
						Cache_wb(outputBuffer2_payload->bufAddr[1],
							   outputBuffer2_payload->metaBufSize[1],
							   Cache_Type_ALLD,
							   TRUE);
					}

					if (executeMode == 2)
					{
						Cache_wb(outputBuffer3_payload->bufAddr[0],
								outputBuffer3_payload->metaBufSize[0],
								Cache_Type_ALLD,
								TRUE);
					}

					Utils_updateLatency(&linkStatsInfo->linkLatency,
						  outputBuffer1->linkLocalTimestamp);
					Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
						  outputBuffer1->srcTimestamp);
					Utils_updateLatency(&linkStatsInfo->linkLatency,
						  outputBuffer2->linkLocalTimestamp);
					Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
						  outputBuffer2->srcTimestamp);

					if(pLinkObj->isLTVBufferAvailable == TRUE)
					{
						Utils_updateLatency(&linkStatsInfo->linkLatency,
							outputBuffer3->linkLocalTimestamp);
						Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
							outputBuffer3->srcTimestamp);
					}

					linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
					linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

					System_BufferList outputBufListReturn;
					//put and release output ALGLINK_SFMMAIN_OPQID_POSES
					//-----------------------------------------------
					outputQId = ALGLINK_SFMMAIN_OPQID_POSES;
					if (executeMode>-1)
					{
						//tell framework that output buffer is filled
						status = AlgorithmLink_putFullOutputBuffer(pObj,
																   outputQId,
																   outputBuffer1);

						UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

						//tell next link that data is ready
						System_sendLinkCmd(
							pLinkCreateParams->outQueParams[outputQId].nextLink,
							SYSTEM_CMD_NEW_DATA,
							NULL);

						//release output buffer
						// (note: buffer is freed only when next also frees the buffer)
						outputBufListReturn.numBuf     = 1;
						outputBufListReturn.buffers[0] = outputBuffer1;
						AlgorithmLink_releaseOutputBuffer(pObj,
														  outputQId,
														  &outputBufListReturn);
						bufDropFlag = FALSE;
					}
					else
					{
						AlgorithmLink_putEmptyOutputBuffer(pObj,
											  outputQId,
											  outputBuffer1);
						bufDropFlag = TRUE;
					}

					//put and release output ALGLINK_SFMMAIN_OPQID_POINTS
					//-----------------------------------------------
					outputQId = ALGLINK_SFMMAIN_OPQID_POINTS;
					if (executeMode>-1)
					{
						//tell framework that output buffer is filled
						status = AlgorithmLink_putFullOutputBuffer(pObj,
																   outputQId,
																   outputBuffer2);
						UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

						  //tell next link that data is ready
						System_sendLinkCmd(
							pLinkCreateParams->outQueParams[outputQId].nextLink,
							SYSTEM_CMD_NEW_DATA,
							NULL);

						//release output buffer
						// (note: buffer is freed only when next also frees the buffer)
						outputBufListReturn.numBuf     = 1;
						outputBufListReturn.buffers[0] = outputBuffer2;
						AlgorithmLink_releaseOutputBuffer(pObj,
														  outputQId,
														  &outputBufListReturn);
						bufDropFlag = FALSE;
					}
					else
					{
						AlgorithmLink_putEmptyOutputBuffer(pObj,
														   outputQId,
														   outputBuffer2);
						bufDropFlag = TRUE;
					}

					if (pLinkObj->isLTVBufferAvailable==TRUE)
					{
						//put and release output  ALGLINK_SFMMAIN_OPQID_LTVAPI
						//-----------------------------------------------
						outputQId = ALGLINK_SFMMAIN_OPQID_LTVAPI;
						if (executeMode==2)
						{
							//tell framework that output buffer is filled
							status = AlgorithmLink_putFullOutputBuffer(pObj,
																	   outputQId,
																	   outputBuffer3);
							UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

							//tell next link that data is ready
							System_sendLinkCmd(
									pLinkCreateParams->outQueParams[outputQId].nextLink,
									SYSTEM_CMD_NEW_DATA,
									NULL);

							//release output buffer
							// (note: buffer is freed only when next also frees the buffer)
							outputBufListReturn.numBuf     = 1;
							outputBufListReturn.buffers[0] = outputBuffer3;
							AlgorithmLink_releaseOutputBuffer(pObj,
															  outputQId,
															  &outputBufListReturn);
							bufDropFlag = FALSE;
						}
						else
						{
							AlgorithmLink_putEmptyOutputBuffer(pObj,
															   outputQId,
															   outputBuffer3);
							bufDropFlag = TRUE;
						}
					}

				} //END if(status == SYSTEM_LINK_STATUS_SOK)
			} //END if(status == SYSTEM_LINK_STATUS_SOK)


			// ALGLINK_SFMMAIN_IPQID_SOFTRACKS
			//-----------------------------------------------
			//release input buffer
			System_BufferList            inputBufListReturn;
			inputQId                      = ALGLINK_SFMMAIN_IPQID_SOFTRACKS;
			inputBufListReturn.numBuf     = 1;
			inputBufListReturn.buffers[0] = inputBuffer1;
			AlgorithmLink_releaseInputBuffer(
					pObj,
					inputQId,
					pLinkCreateParams->inQueParams[inputQId].prevLinkId,
					pLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
					&inputBufListReturn,
					&bufDropFlag);

		}//END for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
    }//END if(inputBufList.numBuf)

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_sfmMainControl(void * pObj, void * pControlParams)
{
	AlgorithmLink_SfmMainObj        * pLinkObj;
	AlgorithmLink_ControlParams    		   * pLinkControlParams;
	void                           	       * algHandle;
	Int32 status    = SYSTEM_LINK_STATUS_SOK;

	pLinkObj = (AlgorithmLink_SfmMainObj *)
	                    AlgorithmLink_getAlgorithmParamsObj(pObj);
	algHandle  = pLinkObj->algHandle;

	pLinkControlParams = (AlgorithmLink_ControlParams *)pControlParams;

	switch(pLinkControlParams->controlCmd)
	{
	    case SYSTEM_CMD_PRINT_STATISTICS:
	        AlgorithmLink_sfmMainPrintStatistics(pObj, pLinkObj);
	        break;

	    default:
	        status = Alg_SfmMainControl(algHandle,
	                                    &(pLinkObj->algControlParams)
	                                    );
	        break;
	}

	return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin
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
Int32 AlgorithmLink_sfmMainStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmMainDelete(void * pObj)
{
	AlgorithmLink_SfmMainObj *pLinkObj;
	AlgLink_MemRequests memRequests;
	Int32 status = SYSTEM_LINK_STATUS_SOK;

	pLinkObj = (AlgorithmLink_SfmMainObj *)
	                        AlgorithmLink_getAlgorithmParamsObj(pObj);

	Alg_SfmMainDelete(pLinkObj->algHandle, &memRequests);

	/*======================================================================
	 * Memory de-allocations for the requests done by algorithm
	 ======================================================================*/
	UInt32 memTabId = 0;
	free(memRequests.memTab[memTabId].basePtr);
	for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
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

	/*======================================================================
	* Deletion of output buffers
	 ======================================================================*/
	System_MetaDataBuffer      				* outputBuffer_payload;
    AlgorithmLink_SfmMainOutputQueId   outputQId;
    Int32 bufferId;

    //ALGLINK_SFMMAIN_OPQID_POSES
    //------------------------------------------------
    outputQId = ALGLINK_SFMMAIN_OPQID_POSES;
	for (bufferId = 0; bufferId < SFMMAIN_LINK_MAX_NUM_OUTPUT; bufferId++)
    {
    	outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][bufferId]);

    	status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[0],
    	                                SFMMAIN_POSES0_BUFFER_SIZE);
    	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    	status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[1],
    	                                SFMMAIN_POSES1_BUFFER_SIZE);
    	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

     //ALGLINK_SFMMAIN_OPQID_POINTS
    //------------------------------------------------
    outputQId = ALGLINK_SFMMAIN_OPQID_POINTS;
	for (bufferId = 0; bufferId < SFMMAIN_LINK_MAX_NUM_OUTPUT; bufferId++)
    {
    	outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][bufferId]);

    	status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[0],
    	                                SFMMAIN_POINTS0_BUFFER_SIZE);
    	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    	status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[1],
    	                                SFMMAIN_POINTS1_BUFFER_SIZE);
    	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    //ALGLINK_SFMMAIN_OPQID_LTVAPI
    //------------------------------------------------
    outputQId = ALGLINK_SFMMAIN_OPQID_LTVAPI;
    outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][0]);

    status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[0],
    	                                SFMMAIN_LTVAPI_BUFFER_SIZE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

	/*======================================================================
	* Deletion of Algorithm object
	 ======================================================================*/
	if(sizeof(AlgorithmLink_SfmMainObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
	{
	    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
	                           pLinkObj,
	                           sizeof(AlgorithmLink_SfmMainObj));
	    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	}
	else
	{
	    free(pLinkObj);
	}

	return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pLinkObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmMainPrintStatistics(void *pObj, void *pLinkObjIn)
{
	AlgorithmLink_SfmMainObj *pLinkObj = (AlgorithmLink_SfmMainObj *)pLinkObjIn;
	Utils_printLinkStatistics(&pLinkObj->linkStatsInfo->linkStats, "ALG_SFMMAIN", TRUE);

	Utils_printLatency("ALG_SFMMAIN",
	                       &pLinkObj->linkStatsInfo->linkLatency,
	                       &pLinkObj->linkStatsInfo->srcToLinkLatency,
	                        TRUE
	                  );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */

