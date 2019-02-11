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
 * \file sfmLinearTwoViewLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Sfm LinearTwoView Link
 *
 * \version 0.0 (Jun 2015) : [MM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sfmLinearTwoViewLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include "sfmMainLink_priv.h"

//#include <algorithms/structurefrommotion/algorithmSrc/include/sfmLinearTwoView.h>

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
Int32 AlgorithmLink_sfmLinearTwoView_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_sfmLinearTwoViewCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_sfmLinearTwoViewProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_sfmLinearTwoViewControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_sfmLinearTwoViewStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_sfmLinearTwoViewDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SFMLTV;
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
Int32 AlgorithmLink_sfmLinearTwoViewCreate(void * pObj, void * pCreateParams)
{
	AlgorithmLink_SfmLinearTwoViewObj              * pLinkObj;
	AlgorithmLink_SfmLinearTwoViewCreateParams     * pLinkCreateParams;
	SfmLinearTwoView_CreateParams       		   * pAlgCreateParams;
	Int32                   				       status    = SYSTEM_LINK_STATUS_SOK;

#ifdef VERBOSE_ON
    Vps_printf("SFM_LTV: ++++++++++ Entering Create");
#endif

    //Allocate Memory for AlgObject
    //================================
	/* Space for Algorithm specific object gets allocated here.
	  * Pointer gets recorded in algorithmParams */
	if(sizeof(AlgorithmLink_SfmLinearTwoViewObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
	{
	    pLinkObj = (AlgorithmLink_SfmLinearTwoViewObj *)
	                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
	                                   sizeof(AlgorithmLink_SfmLinearTwoViewObj), 32);
	}
	else
	{
	    pLinkObj = (AlgorithmLink_SfmLinearTwoViewObj *)
	                    malloc(sizeof(AlgorithmLink_SfmLinearTwoViewObj));
	}

	UTILS_assert(pLinkObj!=NULL);

	AlgorithmLink_setAlgorithmParamsObj(pObj, pLinkObj);


    //Set pointers and take copy of create params
    //==================================================
	//Link level create params
	pLinkCreateParams =
	        (AlgorithmLink_SfmLinearTwoViewCreateParams *)pCreateParams;

	memcpy((void*)(&pLinkObj->linkCreateParams),
	       (void*)(pLinkCreateParams),
	        sizeof(AlgorithmLink_SfmLinearTwoViewCreateParams)
	      );
	//Algorithm level create params
	pAlgCreateParams = (SfmLinearTwoView_CreateParams *)&(pLinkObj->linkCreateParams.algCreateParams);


	//Get input Queue Info
	//======================================
    Int32                       				   numInputQUsed;
	AlgorithmLink_SfmLinearTwoViewInputQueId   	 	inputQId;
    AlgorithmLink_InputQueueInfo         		 * pInputQInfo;
    System_LinkInfo                                prevLinkInfo;

	pInputQInfo  = &pLinkObj->inputQInfo[0];
    numInputQUsed     = ALGLINK_SFMLTV_IPQID_MAXIPQ;

    //LTV API
    inputQId = ALGLINK_SFMLTV_IPQID_LTVAPI;
    pInputQInfo[inputQId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    status = System_linkGetInfo(
                  pLinkCreateParams->inQueParams[inputQId].prevLinkId,
                  &prevLinkInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

	//Set output Queue Info
	//======================================
    Int32                        		   numOutputQUsed;
    AlgorithmLink_OutputQueueInfo        		 * pOutputQInfo;
    pOutputQInfo = NULL;
    numOutputQUsed    = ALGLINK_SFMLTV_OPQID_MAXOPQ;

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

    Alg_SfmLinearTwoViewMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    Alg_SfmLinearTwoViewMemQuery(pAlgCreateParams, &memRequests, 0);

    UInt8 *dataPtr;
    UInt32 ii;
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
        	if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD )
        	{
        		if (memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
        		{
        			memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
        								UTILS_HEAPID_L2_LOCAL,
                                        memRequests.memTab[memTabId].size,
                                        memRequests.memTab[memTabId].alignment);
        		}
        		else
        		{
        			memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        memRequests.memTab[memTabId].size,
                                        memRequests.memTab[memTabId].alignment);
        		}
        	}
        	else
        	{
        		memRequests.memTab[memTabId].basePtr =
        				malloc(memRequests.memTab[memTabId].size);
        	}

        	UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

        	dataPtr = (UInt8 *)memRequests.memTab[memTabId].basePtr;
        	for (ii=0;ii<memRequests.memTab[memTabId].size;ii++)
        		*(dataPtr+ii)=0;
        }
    }

    //Algorithm Creation
    //============================================
    void *algHandle = Alg_SfmLinearTwoViewCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pLinkObj->algHandle = algHandle;

    //Other Initializations
	//========================================
    pLinkObj->frameDropCounter = 0;

    pLinkObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_SFMLTV");
    UTILS_assert(NULL != pLinkObj->linkStatsInfo);

    pLinkObj->isFirstFrameRecv   = FALSE;
    pLinkObj->isFirstOPGenerated = FALSE;

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
Int32 AlgorithmLink_sfmLinearTwoViewProcess(void * pObj)
{
	AlgorithmLink_SfmLinearTwoViewObj              * pLinkObj;
	AlgorithmLink_SfmLinearTwoViewCreateParams     * pLinkCreateParams;
	AlgorithmLink_SfmLinearTwoViewInputQueId      inputQId;
    System_LinkStatistics	   * linkStatsInfo;

	Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool bufDropFlag;

#ifdef VERBOSE_ON
    Vps_printf("SFM_LTV: ++++++++++ Entering  Process");
#endif

    pLinkObj = (AlgorithmLink_SfmLinearTwoViewObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pLinkObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    void *algHandle = pLinkObj->algHandle;
    pLinkCreateParams = (AlgorithmLink_SfmLinearTwoViewCreateParams *) &pLinkObj->linkCreateParams;

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
    System_Buffer       			 * inputBuffer; //LTV API
    System_MetaDataBuffer  			 * inputBuffer_payload;
	UInt32 bufId;

	//check ALGLINK_SFMLTV_IPQID_LTVAPI input
	//------------------------------------------------
	inputQId = ALGLINK_SFMLTV_IPQID_LTVAPI;

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
				Vps_printf("ERROR: inputBuffer==NULL in SfM LTV AlgPlugin Process");
				UTILS_assert(NULL);
			}
			inputBuffer_payload = (System_MetaDataBuffer  *)inputBuffer->payload;


			Cache_inv(inputBuffer_payload->bufAddr[0],
					SFMMAIN_LTVAPI_BUFFER_SIZE,
					Cache_Type_ALLD,
					TRUE);

			//Algorithm Process Call
			//-----------------------
			status = Alg_SfmLinearTwoViewProcess(
							algHandle,
							inputBuffer_payload->bufAddr[0]
               		  );

			UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

			linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
			linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

			// ALGLINK_SFMLTV_IPQID_LTVAPI
			//-----------------------------------------------
			//release input buffer
			System_BufferList            inputBufListReturn;
			inputQId                      = ALGLINK_SFMLTV_IPQID_LTVAPI;
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

Int32 AlgorithmLink_sfmLinearTwoViewControl(void * pObj, void * pControlParams)
{
		AlgorithmLink_SfmLinearTwoViewObj        * pLinkObj;
	    AlgorithmLink_ControlParams    		   * pLinkControlParams;
	    void                           	       * algHandle;
	    Int32 status    = SYSTEM_LINK_STATUS_SOK;

	    pLinkObj = (AlgorithmLink_SfmLinearTwoViewObj *)
	                        AlgorithmLink_getAlgorithmParamsObj(pObj);
	    algHandle  = pLinkObj->algHandle;

	    pLinkControlParams = (AlgorithmLink_ControlParams *)pControlParams;

	    switch(pLinkControlParams->controlCmd)
	    {

	        case SYSTEM_CMD_PRINT_STATISTICS:
	            AlgorithmLink_sfmLinearTwoViewPrintStatistics(pObj, pLinkObj);
	            break;

	        default:
	            status = Alg_SfmLinearTwoViewControl(algHandle,
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
Int32 AlgorithmLink_sfmLinearTwoViewStop(void * pObj)
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
Int32 AlgorithmLink_sfmLinearTwoViewDelete(void * pObj)
{
	AlgorithmLink_SfmLinearTwoViewObj *pLinkObj;
	AlgLink_MemRequests memRequests;
	Int32 status = SYSTEM_LINK_STATUS_SOK;

	pLinkObj = (AlgorithmLink_SfmLinearTwoViewObj *)
	                        AlgorithmLink_getAlgorithmParamsObj(pObj);

	Alg_SfmLinearTwoViewDelete(pLinkObj->algHandle, &memRequests);

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
			   if (memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
			   {
				   status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
				   	                      memRequests.memTab[memTabId].basePtr,
				   	                      memRequests.memTab[memTabId].size);
			   }
			   else
			   {
			       status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
			                              memRequests.memTab[memTabId].basePtr,
			           				      memRequests.memTab[memTabId].size);
			    }
	            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
	        }
	        else
	        {
	            free(memRequests.memTab[memTabId].basePtr);
	        }
	   }
	}

	/*======================================================================
	* Deletion of Algorithm object
	 ======================================================================*/
	if(sizeof(AlgorithmLink_SfmLinearTwoViewObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
	{
	    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
	                           pLinkObj,
	                           sizeof(AlgorithmLink_SfmLinearTwoViewObj));
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
Int32 AlgorithmLink_sfmLinearTwoViewPrintStatistics(void *pObj, void *pLinkObjIn)
{
	AlgorithmLink_SfmLinearTwoViewObj *pLinkObj = (AlgorithmLink_SfmLinearTwoViewObj *)pLinkObjIn;
	Utils_printLinkStatistics(&pLinkObj->linkStatsInfo->linkStats, "ALG_SFMLTV", TRUE);

	Utils_printLatency("ALG_SFMLTV",
	                       &pLinkObj->linkStatsInfo->linkLatency,
	                       &pLinkObj->linkStatsInfo->srcToLinkLatency,
	                        TRUE
	                  );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */

