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
 * \file opencvCannyLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for OpenCVCanny Link
 *
 * \version 0.0 (March 2016) : [SN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "openvxLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of OpenCV Canny algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_OpenVx_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_openVxCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_openVxProcess ;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_openVxControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_openVxStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_openVxDelete;

    algId = ALGORITHM_LINK_IPU_ALG_OPENVX;

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for OpenCV Canny algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_openVxCreate(void * pObj, void * pCreateParams)
{
    Int32                        status = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo              prevLinkInfo;
    Int32                        chId, cnt;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;

    AlgorithmLink_OpenVxObj          * pOpenVxObj;
    AlgorithmLink_OpenVxCreateParams * pCreatePrms;
    AlgorithmLink_OutputQueueInfo       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo        * pInputQInfo;

    pCreatePrms =
        (AlgorithmLink_OpenVxCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pOpenVxObj = (AlgorithmLink_OpenVxObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                                       sizeof(AlgorithmLink_OpenVxObj), 32);

    UTILS_assert(pOpenVxObj != NULL);
    UTILS_assert(pCreatePrms->numOutputFrames <= OPENVX_LINK_MAX_FRAMES);

    pOutputQInfo = &pOpenVxObj->outputQInfo;
    pInputQInfo  = &pOpenVxObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pOpenVxObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(&pOpenVxObj->createPrms, pCreatePrms,
        sizeof(AlgorithmLink_OpenVxCreateParams));

    memcpy((void*)(&pOpenVxObj->outQueParams),
           (void*)(&pCreatePrms->outQueParams),
           sizeof(System_LinkOutQueParams));
    memcpy((void*)(&pOpenVxObj->inQueParams),
           (void*)(&pCreatePrms->inQueParams),
           sizeof(System_LinkInQueParams));

    /*
     * Populating parameters corresponding to Q usage of OpenCV Canny
     * algorithm link
     */
    numInputQUsed     = 1;
    numOutputQUsed    = 1;
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_INPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_INPLACE;
    pOutputQInfo->inputQId = 0;
    pOutputQInfo->queInfo.numCh = 1u;

    /*
     * If any output buffer Q gets used in INPLACE manner, then
     * outputQInfo.inQueParams and
     * outputQInfo.inputQId need to be populated appropriately.
     */

    pOutputQInfo->inputQId = 0;

    memcpy((void*)(&pOutputQInfo->inQueParams),
           (void*)(&pCreatePrms->inQueParams),
            sizeof(pOutputQInfo->inQueParams)
        );

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[chId]
     */
    status = System_linkGetInfo(pCreatePrms->inQueParams.prevLinkId,
                                &prevLinkInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    prevLinkQueId = pCreatePrms->inQueParams.prevLinkQueId;

    UTILS_assert(1U == prevLinkInfo.queInfo[prevLinkQueId].numCh);

    for(chId =0 ; chId < prevLinkInfo.queInfo[prevLinkQueId].numCh; chId++)
    {
        if (SYSTEM_DF_YUV420SP_UV != System_Link_Ch_Info_Get_Flag_Data_Format(
            prevLinkInfo.queInfo[prevLinkQueId].chInfo[chId].flags))
        {
            UTILS_assert(FALSE);
        }

        memcpy((void *)&(pOutputQInfo->queInfo.chInfo[chId]),
             (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[chId]),
             sizeof(System_LinkChInfo));

        /*
         * Taking a copy of input channel info in the link object for any future
         * use
         */
        memcpy((void *)&(pOpenVxObj->inChInfo),
               (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[chId]),
               sizeof(System_LinkChInfo));
    }

    /*
     * If any output buffer Q gets used in INPLACE manner, then
     * pOutputQInfo->inQueParams and
     * pOutputQInfo->inputQId need to be populated appropriately.
     */

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

    status = openvxCreate(pOpenVxObj);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = Utils_queCreate(&pOpenVxObj->graphQue,
                              OPENVX_LINK_MAX_FRAMES,
                              pOpenVxObj->graphQueMem,
                              UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (cnt = 0U; cnt < pCreatePrms->numOutputFrames; cnt ++)
    {
        status = Utils_quePut(
                &pOpenVxObj->graphQue,
                (Ptr)&pOpenVxObj->graph[cnt],
                (UInt32)BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    pOpenVxObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
                                            AlgorithmLink_getLinkId(pObj),
                                            "ALG_OPENVX");
    UTILS_assert(NULL != pOpenVxObj->linkStatsInfo);
    pOpenVxObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for OpenCV Canny algorithm link
 *
 *        This function executes on the DSP or EVE or IPU or A15 processor.
 *        Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_openVxProcess (void * pObj)
{
    AlgorithmLink_OpenVxObj * pOpenVxObj;
    Int32                        inputQId;
    UInt32                       chId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSysBufferInput;
    System_VideoFrameBuffer    * pSysVideoFrameBufferInput;
    Bool                         bufDropFlag;
    System_LinkStatistics      * linkStatsInfo;
    AlgorithmLink_GraphObj     * pGraphObj;

    pOpenVxObj = (AlgorithmLink_OpenVxObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pOpenVxObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pOpenVxObj->inQueParams.prevLinkId,
                               pOpenVxObj->inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pOpenVxObj->isFirstFrameRecv==FALSE)
        {
            pOpenVxObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    1u,
                    1u);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {

            pSysBufferInput           = inputBufList.buffers[bufId];
            pSysVideoFrameBufferInput = pSysBufferInput->payload;

            chId = pSysBufferInput->chNum;

            /*
             * Error checks can be done on the input buffer and only later,
             * it can be picked for processing
             */
            if((pSysBufferInput->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME) ||
               (chId >= 1u))
            {
                bufDropFlag = TRUE;
                linkStatsInfo->linkStats.inBufErrorCount++;
            }
            else
            {
                linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;

                /*
                 * Getting free graph object
                 */
                status = Utils_queGet(&pOpenVxObj->graphQue,
                                    (Ptr *) & pGraphObj,
                                    (UInt32)1U,
                                    (UInt32)BSP_OSAL_NO_WAIT);

                /*
                 * Get into algorithm processing only if an output
                 * frame is available.
                 * Else input buffer will be returned back to sender
                 * and its a case of frame drop.
                 */
                if(status == SYSTEM_LINK_STATUS_SOK)
                {
                    pSysBufferInput->linkLocalTimestamp =
                        Utils_getCurGlobalTimeInUsec();

                    openvxProcess(pOpenVxObj, pGraphObj,
                                  pSysVideoFrameBufferInput);

                    drawCorners(pOpenVxObj, pGraphObj,
                                pSysVideoFrameBufferInput);

                    Cache_wb(pSysVideoFrameBufferInput->bufAddr[0],
                        pOpenVxObj->inChInfo.pitch[0]*
                            pOpenVxObj->inChInfo.height,
                        Cache_Type_ALLD,
                        TRUE);

                    Cache_wb(pSysVideoFrameBufferInput->bufAddr[1],
                        pOpenVxObj->inChInfo.pitch[1]*
                            pOpenVxObj->inChInfo.height/2,
                        Cache_Type_ALLD,
                        TRUE);

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pSysBufferInput->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pSysBufferInput->srcTimestamp);

                    linkStatsInfo->linkStats.chStats
                              [pSysBufferInput->chNum].inBufProcessCount++;
                    linkStatsInfo->linkStats.chStats
                              [pSysBufferInput->chNum].outBufCount[0]++;

                    status = Utils_quePut(
                            &pOpenVxObj->graphQue,
                            (Ptr)pGraphObj,
                            (UInt32)BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /*
                     * Putting filled buffer into output full buffer Q
                     */
                    status = AlgorithmLink_putFullOutputBuffer(
                        pObj,
                        0,
                        pSysBufferInput);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /*
                     * Informing next link that a new data has peen
                     * put for its processing
                     */
                    System_sendLinkCmd(pOpenVxObj->outQueParams.nextLink,
                                       SYSTEM_CMD_NEW_DATA,
                                       NULL);

                    bufDropFlag = FALSE;
                }
                else
                {
                    bufDropFlag = TRUE;

                    linkStatsInfo->linkStats.outBufErrorCount++;
                    linkStatsInfo->linkStats.chStats
                        [pSysBufferInput->chNum].inBufDropCount++;
                    linkStatsInfo->linkStats.chStats
                        [pSysBufferInput->chNum].outBufDropCount[0]++;
                } /* Output Buffer availability */

            } /* Input Buffer validity */

            /*
             * Releasing (Free'ing) input buffer, since algorithm does not need
             * it for any future usage.
             */
            inputQId                      = 0;
            inputBufListReturn.numBuf     = 1;
            inputBufListReturn.buffers[0] = pSysBufferInput;
            AlgorithmLink_releaseInputBuffer(
                                        pObj,
                                        inputQId,
                                        pOpenVxObj->inQueParams.prevLinkId,
                                        pOpenVxObj->inQueParams.prevLinkQueId,
                                        &inputBufListReturn,
                                        &bufDropFlag);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for OpenCV Canny algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_openVxControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_OpenVxObj     *pOpenVxObj;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;
    Int32                        status = SYSTEM_LINK_STATUS_SOK;

    pOpenVxObj = (AlgorithmLink_OpenVxObj *)
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

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_openVxPrintStatistics(pObj, pOpenVxObj);
            break;

        default:
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for OpenCV Canny algorithm link
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
Int32 AlgorithmLink_openVxStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for OpenCV Canny algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_openVxDelete(void * pObj)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_OpenVxObj     *pOpenVxObj;

    pOpenVxObj = (AlgorithmLink_OpenVxObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pOpenVxObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    openvxDelete(pOpenVxObj);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                           pOpenVxObj, sizeof(AlgorithmLink_OpenVxObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_queDelete(&pOpenVxObj->graphQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pOpenVxObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_openVxPrintStatistics(void *pObj,
                       AlgorithmLink_OpenVxObj *pOpenVxObj)
{

    UTILS_assert(NULL != pOpenVxObj->linkStatsInfo);

    Utils_printLinkStatistics(&pOpenVxObj->linkStatsInfo->linkStats, "ALG_OPENVX", TRUE);

    Utils_printLatency("ALG_OPENVX",
                       &pOpenVxObj->linkStatsInfo->linkLatency,
                       &pOpenVxObj->linkStatsInfo->srcToLinkLatency,
                        TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
