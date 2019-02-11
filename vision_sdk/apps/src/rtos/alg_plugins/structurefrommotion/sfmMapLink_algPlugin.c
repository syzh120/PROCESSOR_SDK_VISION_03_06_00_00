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
 * \file sfmMapLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Sfm Map Link
 *
 * \version 0.0 (Jun 2015) : [MM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sfmMapLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include "sfmMainLink_priv.h"

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
Int32 AlgorithmLink_sfmMap_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_sfmMapCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_sfmMapProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_sfmMapControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_sfmMapStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_sfmMapDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SFMMAP;
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
Int32 AlgorithmLink_sfmMapCreate(void * pObj, void * pCreateParams)
{
	AlgorithmLink_SfmMapObj              * pLinkObj;
	AlgorithmLink_SfmMapCreateParams     * pLinkCreateParams;
	SfmMap_CreateParams       		      * pAlgCreateParams;

	Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef VERBOSE_ON
    Vps_printf("SFM_MAP: ++++++++++ Entering Create");
#endif

    //Allocate Memory for AlgObject
    //================================
	/* Space for Algorithm specific object gets allocated here.
	  * Pointer gets recorded in algorithmParams */
	if(sizeof(AlgorithmLink_SfmMapObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
	{
	    pLinkObj = (AlgorithmLink_SfmMapObj *)
	                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
	                                   sizeof(AlgorithmLink_SfmMapObj), 32);
	}
	else
	{
	    pLinkObj = (AlgorithmLink_SfmMapObj *)
	                    malloc(sizeof(AlgorithmLink_SfmMapObj));
	}

	UTILS_assert(pLinkObj!=NULL);

	AlgorithmLink_setAlgorithmParamsObj(pObj, pLinkObj);

    //Set pointers and take copy of create params
    //==================================================
	//Link level create params
	pLinkCreateParams =
	        (AlgorithmLink_SfmMapCreateParams *)pCreateParams;

	memcpy((void*)(&pLinkObj->linkCreateParams),
	       (void*)(pLinkCreateParams),
	        sizeof(AlgorithmLink_SfmMapCreateParams)
	      );
	//Algorithm level create params
	pAlgCreateParams = (SfmMap_CreateParams *)&(pLinkObj->linkCreateParams.algCreateParams);

	//Get input Queue Info
	//======================================
    Int32                       				   numInputQUsed;
	AlgorithmLink_SfmMapInputQueId   	 	 	   inputQId;
    AlgorithmLink_InputQueueInfo         		 * pInputQInfo;
    System_LinkInfo                                prevLinkInfo;

	pInputQInfo  = &pLinkObj->inputQInfo[0];
    numInputQUsed     = ALGLINK_SFMMAP_IPQID_MAXIPQ;

    //3D Points
   	inputQId = ALGLINK_SFMMAP_IPQID_3DPOINTS;
    pInputQInfo[inputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    status = System_linkGetInfo(
                        pLinkCreateParams->inQueParams[inputQId].prevLinkId,
                        &prevLinkInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Poses
   	inputQId = ALGLINK_SFMMAP_IPQID_POSES;
    pInputQInfo[inputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    status = System_linkGetInfo(
                        pLinkCreateParams->inQueParams[inputQId].prevLinkId,
                        &prevLinkInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

	//Set output Queue Info
	//======================================
    Int32                        		   numOutputQUsed;
	AlgorithmLink_SfmMapOutputQueId 	   outputQId;
    AlgorithmLink_OutputQueueInfo         * pOutputQInfo;
    pOutputQInfo = &pLinkObj->outputQInfo[0];
    numOutputQUsed    = ALGLINK_SFMMAP_OPQID_MAXOPQ;

    //Boxes
    outputQId = ALGLINK_SFMMAP_OPQID_BOXES;
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

    Alg_SfmMapMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    Alg_SfmMapMemQuery(pAlgCreateParams, &memRequests, 0);
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
        }
    }

    //Algorithm Creation
    //============================================
    void *algHandle = Alg_SfmMapCreate(pAlgCreateParams, &memRequests);
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

    for (bufferId=0; bufferId < SFMMAP_LINK_MAX_NUM_OUTPUT; bufferId++)
    {
    	//BOXES
    	//===============================================
		outputQId = ALGLINK_SFMMAP_OPQID_BOXES;
		outputBuffer = &(pLinkObj->buffers[outputQId][bufferId]);
		outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][bufferId]);
		outputBuffer_payload->numMetaDataPlanes = 2;
		outputBuffer_payload->flags             = 0;

		outputBuffer->payload     = outputBuffer_payload;
		outputBuffer->payloadSize = sizeof(System_MetaDataBuffer);
		outputBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
		outputBuffer->chNum       = 0;

		//boxes
		metaBufSize = SFMMAP_BOXES_BUFFER_SIZE;
	   	outputBuffer_payload->bufAddr[0] =  Utils_memAlloc(
	                                            UTILS_HEAPID_DDR_CACHED_SR,
	                                            metaBufSize,
	                                            ALGORITHMLINK_FRAME_ALIGN);
	    outputBuffer_payload->metaBufSize[0]    = metaBufSize;
	    outputBuffer_payload->metaFillLength[0] = metaBufSize;
	    UTILS_assert(outputBuffer_payload->bufAddr[0] != NULL);

	    //labelmap
		metaBufSize = SFMMAP_LABELMAP_BUFFER_SIZE;
	   	outputBuffer_payload->bufAddr[1] =  Utils_memAlloc(
	                                            UTILS_HEAPID_DDR_CACHED_SR,
	                                            metaBufSize,
	                                            ALGORITHMLINK_FRAME_ALIGN);
	    outputBuffer_payload->metaBufSize[1]    = metaBufSize;
	    outputBuffer_payload->metaFillLength[1] = metaBufSize;
	    UTILS_assert(outputBuffer_payload->bufAddr[1] != NULL);

	    AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, outputBuffer);
    }


    //Other Initializations
	//========================================
    pLinkObj->frameDropCounter = 0;

    pLinkObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_SFMMAP");
    UTILS_assert(NULL != pLinkObj->linkStatsInfo);

    pLinkObj->isFirstFrameRecv   = FALSE;
    pLinkObj->isFirstOPGenerated = FALSE;
    pLinkObj->receivedFirstPoseFlag = FALSE;

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
Int32 AlgorithmLink_sfmMapProcess(void * pObj)
{
	AlgorithmLink_SfmMapObj              * pLinkObj;
	AlgorithmLink_SfmMapCreateParams     * pLinkCreateParams;
	AlgorithmLink_SfmMapOutputQueId 	 outputQId;
	AlgorithmLink_SfmMapInputQueId      inputQId;
    System_LinkStatistics	   * linkStatsInfo;

	Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 channelId;
    Bool bufDropFlag;

#ifdef VERBOSE_ON
    Vps_printf("SFM_MAP: ++++++++++ Entering Process");
#endif

    pLinkObj = (AlgorithmLink_SfmMapObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pLinkObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    void *algHandle = pLinkObj->algHandle;
    pLinkCreateParams = (AlgorithmLink_SfmMapCreateParams *) &pLinkObj->linkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

	//If first call, reset statistics
	//===============================
	if(pLinkObj->isFirstFrameRecv==FALSE)
    {
        pLinkObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats, 1, 1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    //If input buffer is full, process data
    //=================================================
    System_BufferList      			   inputBufList;
    System_Buffer 					 * outputBuffer; //boxes
    System_MetaDataBuffer 			 * outputBuffer_payload;
    System_Buffer       			 * inputBuffer; //3d points
    System_MetaDataBuffer  			 * inputBuffer_payload;
	UInt32 bufId;

	//check ALGLINK_SFMMAP_IPQID_POSES input
	//------------------------------------------------
    System_BufferList            inputBufListReturn;
	inputQId = ALGLINK_SFMMAP_IPQID_POSES;

	inputBufList.numBuf = 0;
    status = System_getLinksFullBuffers(
        pLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       	for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
       	{
       	    if(pLinkObj->receivedFirstPoseFlag== TRUE)
       	    {
       	        inputBufListReturn.numBuf     = 1;
       	        inputBufListReturn.buffers[0] = pLinkObj->sysBufferPoses;

       	        status = System_putLinksEmptyBuffers( pLinkCreateParams->inQueParams[inputQId].prevLinkId,
       	        									  pLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
       	                                             &inputBufListReturn);

       	        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
       	    }
       	    else
       	    {
       	    	pLinkObj->receivedFirstPoseFlag = TRUE;
       	    }
       	    pLinkObj->sysBufferPoses = inputBufList.buffers[bufId];
       	    pLinkObj->metaBufferPoses =  (System_MetaDataBuffer *)pLinkObj->sysBufferPoses->payload;
       	}
     }



	//check ALGLINK_SFMMAP_IPQID_3DPOINTS input
	//------------------------------------------------
	inputQId = ALGLINK_SFMMAP_IPQID_3DPOINTS;

	inputBufList.numBuf = 0;
    status = System_getLinksFullBuffers(
        pLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf && status==SYSTEM_LINK_STATUS_SOK)
    {
    	//Get pointer to input data
    	for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
    	{
			inputBuffer = inputBufList.buffers[bufId];
			if(inputBuffer == NULL)
			{
				Vps_printf("ERROR: inputBuffer==NULL in SfM Map AlgPlugin Process");
				UTILS_assert(NULL);
			}
			inputBuffer_payload = (System_MetaDataBuffer  *)inputBuffer->payload;

		    if (pLinkObj->receivedFirstPoseFlag== TRUE)
		    {
				//============================================
				//get buffer for ALGLINK_SFMMAP_OPQID_BOXES
				//=============================================
				outputQId =  ALGLINK_SFMMAP_OPQID_BOXES;
				channelId = 0;
				//request empty buffer from framework
				status = AlgorithmLink_getEmptyOutputBuffer(
					  										pObj,
					  										outputQId,
					  										channelId,
					  										&outputBuffer);
				if(status != SYSTEM_LINK_STATUS_SOK)
				{
					linkStatsInfo->linkStats.outBufErrorCount++;
				}
				else
				{
					/*--------------------------------------------------------------
					 *  DONE REQUESTING BUFFERS, START SET UP DATA POINTERS
					 *  ------------------------------------------------------------ */
					outputBuffer->srcTimestamp = inputBuffer->srcTimestamp;
					outputBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
					outputBuffer_payload = (System_MetaDataBuffer *)outputBuffer->payload;

					Cache_inv(inputBuffer_payload->bufAddr[0],
							SFMMAIN_POINTS0_BUFFER_SIZE,
							Cache_Type_ALLD,
							TRUE);

					Cache_inv(inputBuffer_payload->bufAddr[1],
							SFMMAIN_POINTS1_BUFFER_SIZE,
							Cache_Type_ALLD,
							TRUE);

					Cache_inv(pLinkObj->metaBufferPoses->bufAddr[0],
							SFMMAIN_POSES0_BUFFER_SIZE,
							Cache_Type_ALLD,
							TRUE);


					//Algorithm Process Call
					//-----------------------
					status = Alg_SfmMapProcess(
	               				 algHandle,
	               				 inputBuffer_payload->bufAddr[0],
	               			     inputBuffer_payload->bufAddr[1],
	               			     pLinkObj->metaBufferPoses->bufAddr[0],
	               				 outputBuffer_payload->bufAddr[0],
	               				 outputBuffer_payload->bufAddr[1]);

					UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

					Cache_wb(outputBuffer_payload->bufAddr[0],
							 outputBuffer_payload->metaBufSize[0],
							 Cache_Type_ALLD,
							 TRUE);

					Cache_wb(outputBuffer_payload->bufAddr[1],
							 outputBuffer_payload->metaBufSize[1],
							 Cache_Type_ALLD,
							 TRUE);

					Utils_updateLatency(&linkStatsInfo->linkLatency,
	                                outputBuffer->linkLocalTimestamp);
					Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
	                                outputBuffer->srcTimestamp);

					linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
					linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

					//put and release output ALGLINK_SFMMAP_OPQID_BOXES
					//-----------------------------------------------
					outputQId = ALGLINK_SFMMAP_OPQID_BOXES;
					//tell framework that output buffer is filled
					status    = AlgorithmLink_putFullOutputBuffer(pObj,
	                                                          	  outputQId,
	                                                          	  outputBuffer);
					UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

					//tell next link that data is ready
					System_sendLinkCmd(
							pLinkCreateParams->outQueParams[outputQId].nextLink,
							SYSTEM_CMD_NEW_DATA,
							NULL);

					//release output buffer
					// (note: buffer is freed only when next also frees the buffer)
					System_BufferList outputBufListReturn;
					outputBufListReturn.numBuf     = 1;
					outputBufListReturn.buffers[0] = outputBuffer;
					AlgorithmLink_releaseOutputBuffer(pObj,
							  	  	  	  	  	  	 outputQId,
							  	  	  	  	  	  	 &outputBufListReturn);
					bufDropFlag = FALSE;

				} //END if(status == SYSTEM_LINK_STATUS_SOK)
		    }//END if (pLinkObj->receivedFirstPoseFlag== TRUE)

		// ALGLINK_SFMMAP_IPQID_3DPOINTS
		//-----------------------------------------------
	    //release input buffer
        System_BufferList            inputBufListReturn;
        inputQId                      = ALGLINK_SFMMAP_IPQID_3DPOINTS;
        inputBufListReturn.numBuf     = 1;
        inputBufListReturn.buffers[0] = inputBuffer;
        AlgorithmLink_releaseInputBuffer(
        		pObj,
        		inputQId,
        		pLinkCreateParams->inQueParams[inputQId].prevLinkId,
        		pLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        		&inputBufListReturn,
        		&bufDropFlag);

      }	 //END for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
    } //END if(inputBufList.numBuf)

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

Int32 AlgorithmLink_sfmMapControl(void * pObj, void * pControlParams)
{
		AlgorithmLink_SfmMapObj        * pLinkObj;
	    AlgorithmLink_ControlParams    		   * pLinkControlParams;
	    void                           	       * algHandle;
	    Int32 status    = SYSTEM_LINK_STATUS_SOK;

	    pLinkObj = (AlgorithmLink_SfmMapObj *)
	                        AlgorithmLink_getAlgorithmParamsObj(pObj);
	    algHandle  = pLinkObj->algHandle;

	    pLinkControlParams = (AlgorithmLink_ControlParams *)pControlParams;

	    switch(pLinkControlParams->controlCmd)
	    {

	        case SYSTEM_CMD_PRINT_STATISTICS:
	            AlgorithmLink_sfmMapPrintStatistics(pObj, pLinkObj);
	            break;

	        default:
	        	pLinkObj->algControlParams.controlCommand = RESET_MAP;
	            status = Alg_SfmMapControl(algHandle,
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
Int32 AlgorithmLink_sfmMapStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for egoMotion algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmMapDelete(void * pObj)
{
	AlgorithmLink_SfmMapObj *pLinkObj;
	AlgLink_MemRequests memRequests;
	Int32 status = SYSTEM_LINK_STATUS_SOK;

	pLinkObj = (AlgorithmLink_SfmMapObj *)
	                        AlgorithmLink_getAlgorithmParamsObj(pObj);

	Alg_SfmMapDelete(pLinkObj->algHandle, &memRequests);

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
    AlgorithmLink_SfmMapOutputQueId   outputQId;
    Int32 bufferId;

    //ALGLINK_SFMMAP_OPQID_BOXES
    //------------------------------------------------
    outputQId = ALGLINK_SFMMAP_OPQID_BOXES;
	for (bufferId = 0; bufferId < SFMMAP_LINK_MAX_NUM_OUTPUT; bufferId++)
    {
    	outputBuffer_payload = &(pLinkObj->metaDataBuffers[outputQId][bufferId]);

    	status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[0],
    	                                SFMMAP_BOXES_BUFFER_SIZE);
    	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    	status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
    	                                outputBuffer_payload->bufAddr[1],
    	                                SFMMAP_LABELMAP_BUFFER_SIZE);
    	UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

	/*======================================================================
	* Deletion of Algorithm object
	 ======================================================================*/
	if(sizeof(AlgorithmLink_SfmMapObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
	{
	    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
	                           pLinkObj,
	                           sizeof(AlgorithmLink_SfmMapObj));
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
Int32 AlgorithmLink_sfmMapPrintStatistics(void *pObj, void *pLinkObjIn)
{
	AlgorithmLink_SfmMapObj *pLinkObj = (AlgorithmLink_SfmMapObj *)pLinkObjIn;
	Utils_printLinkStatistics(&pLinkObj->linkStatsInfo->linkStats, "ALG_SFMMAP", TRUE);

	Utils_printLatency("ALG_SFMMAP",
	                       &pLinkObj->linkStatsInfo->linkLatency,
	                       &pLinkObj->linkStatsInfo->srcToLinkLatency,
	                        TRUE
	                  );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */

