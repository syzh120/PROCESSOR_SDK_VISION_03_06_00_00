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
 * \file pAlignLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for photometric alignment Link
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 * \version 0.1 (Oct 2013) : [PS] Some code cleanup and corrected tracing
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "pAlignLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of synthesis algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pAlign_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_pAlignCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_pAlignProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_pAlignControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_pAlignStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_pAlignDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_PALIGNMENT;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for photometric alignment alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pAlignCreate(void * pObj, void * pCreateParams)
{
    void                       * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    System_LinkInfo              prevLinkInfo;
    AlgorithmLink_PAlignOutputQueId   outputQId;
    AlgorithmLink_PAlignInputQueId    inputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       metaBufSize;
    System_LinkChInfo          * pOutChInfo;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_PAlignObj              * pPAlignObj;
    AlgorithmLink_PAlignCreateParams     * pPAlignLinkCreateParams;
    SV_PAlign_CreationParamsStruct       * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;

    pPAlignLinkCreateParams =
        (AlgorithmLink_PAlignCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pPAlignObj = (AlgorithmLink_PAlignObj *)
                                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    sizeof(AlgorithmLink_PAlignObj), 64);
    UTILS_assert(pPAlignObj!=NULL);

    pAlgCreateParams = &pPAlignObj->algCreateParams;

    pOutputQInfo = &pPAlignObj->outputQInfo[0];
    pInputQInfo  = &pPAlignObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pPAlignObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pPAlignObj->algLinkCreateParams),
           (void*)(pPAlignLinkCreateParams),
           sizeof(AlgorithmLink_PAlignCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of photometric alignment
     * algorithm link
     */
    numInputQUsed     = ALGLINK_PALIGN_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_PALIGN_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo[ALGLINK_PALIGN_IPQID_PASTATS].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_PALIGN_OPQID_PALUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_PALIGN_OPQID_PALUT].queInfo.numCh = numChannelsUsed;

    inputQId  = ALGLINK_PALIGN_IPQID_PASTATS;

    status = System_linkGetInfo(
                pPAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
                &prevLinkInfo);

    /*
     * Channel info population for output Q Id - ALGLINK_PALIGN_OPQID_PALUT
     * TBD - To check if anything in channel info is needed for meta data op
     */
    outputQId = ALGLINK_PALIGN_OPQID_PALUT;
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

    pAlgCreateParams->SVInCamFrmHeight =
        pPAlignLinkCreateParams->maxInputHeight;
    pAlgCreateParams->SVInCamFrmWidth =
        pPAlignLinkCreateParams->maxInputWidth;
    pAlgCreateParams->SVOutDisplayHeight =
        pPAlignLinkCreateParams->maxOutputHeight;
    pAlgCreateParams->SVOutDisplayWidth =
        pPAlignLinkCreateParams->maxOutputWidth;
    pAlgCreateParams->numCameras =
        pPAlignLinkCreateParams->numViews;

    pAlgCreateParams->numColorChannels = 3;
    pAlgCreateParams->svCarBoxParams.CarBoxCenter_x =
        (pAlgCreateParams->SVOutDisplayHeight / 2);
    pAlgCreateParams->svCarBoxParams.CarBoxCenter_y =
        (pAlgCreateParams->SVOutDisplayWidth / 2);
    pAlgCreateParams->svCarBoxParams.CarBox_height =
            pPAlignLinkCreateParams->carBoxHeight;
    pAlgCreateParams->svCarBoxParams.CarBox_width =
            pPAlignLinkCreateParams->carBoxWidth;

    pAlgCreateParams->blockSizeV = 40;
    pAlgCreateParams->blockSizeH = 40;

    pAlgCreateParams->PAlignTuningParams.beta = (1<<7);
    pAlgCreateParams->PAlignTuningParams.inTh = 6400; // 65536; //800; 1600;
    pAlgCreateParams->PAlignTuningParams.nAnPts = 5;
    pAlgCreateParams->PAlignTuningParams.nUpGn = 10;
    pAlgCreateParams->PAlignTuningParams.nUpTv = 10;

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_PhotometricAlignmentMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                                     UTILS_HEAPID_DDR_CACHED_SR,
                                     memRequests.memTab[memTabId].size,
                                     memRequests.memTab[memTabId].alignment);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_PhotometricAlignmentMemQuery(pAlgCreateParams, &memRequests, 0);
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
        memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                                         UTILS_HEAPID_DDR_CACHED_SR,
                                         memRequests.memTab[memTabId].size,
                                         memRequests.memTab[memTabId].alignment);
        UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
        }
    }

    algHandle = Alg_PhotometricAlignmentCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pPAlignObj->algHandle = algHandle;

    /*
     * Creation of output buffers for output Q of ALGLINK_PALIGN_OPQID_PALUT
     *  - Connecting metadata buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    outputQId = ALGLINK_PALIGN_OPQID_PALUT;
    channelId = 0;

    for(frameIdx = 0;
        frameIdx < pPAlignObj->algLinkCreateParams
                    .numOutputTables;
        frameIdx++)
    {
        pSystemBuffer         =
                             &(pPAlignObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =
                             &(pPAlignObj->pAlignLUT[frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        metaBufSize = sizeof(PAlignOutStruct);

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

    pPAlignObj->frameDropCounter          = 0;

    pPAlignObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_PALIGN");
    UTILS_assert(NULL != pPAlignObj->linkStatsInfo);

    pPAlignObj->numInputChannels = 1;

    pPAlignObj->isFirstFrameRecv   = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of photometric alignment alg link
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
Int32 AlgorithmLink_pAlignProcess(void * pObj)
{
    AlgorithmLink_PAlignObj    * pPAlignObj;
    void                       * algHandle;
    AlgorithmLink_PAlignInputQueId    inputQId;
    AlgorithmLink_PAlignOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status      = SYSTEM_LINK_STATUS_SOK;
    Int32                        inputStatus = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferPALUT;
    System_Buffer              * pSystemBufferPAStats;
    Bool                         bufDropFlag;
    System_MetaDataBuffer      * pPALUTBuffer;

    System_MetaDataBuffer      * pPAStatsBuffer;
    AlgorithmLink_PAlignCreateParams  * pPAlignLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    pPAlignObj = (AlgorithmLink_PAlignObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pPAlignObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    algHandle               = pPAlignObj->algHandle;
    pPAlignLinkCreateParams = (AlgorithmLink_PAlignCreateParams *)
                                    &pPAlignObj->algLinkCreateParams;

    if(pPAlignObj->isFirstFrameRecv==FALSE)
    {
        pPAlignObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pPAlignObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_PALIGN_IPQID_PASTATS and process them if output is
     * available
     */
    inputQId = ALGLINK_PALIGN_IPQID_PASTATS;

    System_getLinksFullBuffers(
        pPAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pPAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {

      for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
      {
          pSystemBufferPAStats = inputBufList.buffers[bufId];
          pPAStatsBuffer = (System_MetaDataBuffer *)pSystemBufferPAStats->payload;
          bufDropFlag = TRUE;

          /*TBD: Check for parameter correctness. If in error, return input*/
          inputStatus = SYSTEM_LINK_STATUS_SOK;
          if(pSystemBufferPAStats->bufType != SYSTEM_BUFFER_TYPE_METADATA)
          {
            inputStatus = SYSTEM_LINK_STATUS_EFAIL;
            linkStatsInfo->linkStats.inBufErrorCount++;
          }

          if(inputStatus == SYSTEM_LINK_STATUS_SOK)
          {
          /*
           * For frame to be processed:
           *  - Output buffer will be queried
           *  - If output buffer is available, then algorithm will be called
           */

          outputQId = ALGLINK_PALIGN_OPQID_PALUT;
          channelId = 0;
          status = AlgorithmLink_getEmptyOutputBuffer(
                                            pObj,
                                            outputQId,
                                            channelId,
                                            &pSysBufferPALUT);

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
            pSysBufferPALUT->srcTimestamp = pSystemBufferPAStats->srcTimestamp;
            pSysBufferPALUT->frameId = pSystemBufferPAStats->frameId;
            pSysBufferPALUT->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

            pPALUTBuffer = (System_MetaDataBuffer *)pSysBufferPALUT->payload;

            Cache_inv(pPAStatsBuffer->bufAddr[0],
                      pPAStatsBuffer->metaBufSize[0],
                      Cache_Type_ALLD,
                      TRUE);

            /* Enable PAlign for 2D usecases */
            Byte PAlign_Mode;
            if (pPAlignObj->algLinkCreateParams.svOutputMode==ALGORITHM_LINK_SRV_OUTPUT_2D)
            {
                PAlign_Mode = 1;
            }
            else
            {
                PAlign_Mode = 0;
            }
            status = Alg_PhotometricAlignmentProcess(
                             algHandle,
                             pPAStatsBuffer->bufAddr[0],
                             pPALUTBuffer->bufAddr[0],
                             pPAlignLinkCreateParams->dataFormat,
                             PAlign_Mode);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            Cache_wb(pPALUTBuffer->bufAddr[0],
                     pPALUTBuffer->metaBufSize[0],
                     Cache_Type_ALLD,
                     TRUE
                    );

            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                pSysBufferPALUT->linkLocalTimestamp);
            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pSysBufferPALUT->srcTimestamp);

            linkStatsInfo->linkStats.chStats
                  [pSystemBufferPAStats->chNum].inBufProcessCount++;
            linkStatsInfo->linkStats.chStats
                  [pSystemBufferPAStats->chNum].outBufCount[0]++;

            /*
             * Putting filled buffer into output full buffer for
             * outputQId = ALGLINK_PALIGN_OPQID_PALUT
             */
            outputQId = ALGLINK_PALIGN_OPQID_PALUT;
            status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                          outputQId,
                                                          pSysBufferPALUT);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            /*
             * Informing next link that a new data has peen put for its
             * processing
             */
            System_sendLinkCmd(
              pPAlignLinkCreateParams->outQueParams[outputQId].nextLink,
              SYSTEM_CMD_NEW_DATA,
              NULL);

            /*
             * Releasing (Free'ing) output buffers, since algorithm does not need
             * it for any future usage.
             */

            outputQId                      = ALGLINK_PALIGN_OPQID_PALUT;
            outputBufListReturn.numBuf     = 1;
            outputBufListReturn.buffers[0] = pSysBufferPALUT;
            AlgorithmLink_releaseOutputBuffer(pObj,
                                            outputQId,
                                            &outputBufListReturn);


            bufDropFlag = FALSE;
          }

          } /* (inputStatus == SYSTEM_LINK_STATUS_SOK) */

          /*
           * Releasing (Free'ing) Input buffers, since algorithm does not need
           * it for any future usage.
           */
          inputQId                      = ALGLINK_PALIGN_IPQID_PASTATS;
          inputBufListReturn.numBuf     = 1;
          inputBufListReturn.buffers[0] = pSystemBufferPAStats;
          AlgorithmLink_releaseInputBuffer(
            pObj,
            inputQId,
            pPAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
            pPAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
            &inputBufListReturn,
            &bufDropFlag);

      } /* for (bufId = 0; bufId < inputBufList.numBuf; bufId++) */

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for photometric align algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_pAlignControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_PAlignObj        * pPAlignObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pPAlignObj = (AlgorithmLink_PAlignObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pPAlignObj->algHandle;

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
            AlgorithmLink_pAlignPrintStatistics(pObj, pPAlignObj);
            break;

        default:
            status = Alg_PhotometricAlignmentControl(algHandle,
                                                  &(pPAlignObj->controlParams)
                                                  );
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for photometric align algorithm link
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
Int32 AlgorithmLink_pAlignStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for synthesis algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pAlignDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       metaBufSize;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_PAlignObj           * pPAlignObj;
    UInt32                              memTabId;

    pPAlignObj = (AlgorithmLink_PAlignObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pPAlignObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_PhotometricAlignmentDelete(pPAlignObj->algHandle, &memRequests);

    /*
     * Memory allocations for the requests done by algorithm
     */
    for(memTabId = 0 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               memRequests.memTab[memTabId].basePtr,
                               memRequests.memTab[memTabId].size);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    /*
     * Deletion of output buffers for output Q of ALGLINK_PALIGN_OPQID_PALUT
     */
    for(frameIdx = 0;
        frameIdx < pPAlignObj->algLinkCreateParams
                    .numOutputTables;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pPAlignObj->pAlignLUT[frameIdx]);

        metaBufSize = sizeof(PAlignOutStruct);

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                metaBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Space for Algorithm specific object gets freed here.
     */
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           pPAlignObj,
                           sizeof(AlgorithmLink_PAlignObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pPAlignObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_pAlignPrintStatistics(void *pObj,
                       AlgorithmLink_PAlignObj *pPAlignObj)
{
    UTILS_assert(NULL != pPAlignObj->linkStatsInfo);

    Utils_printLinkStatistics(&pPAlignObj->linkStatsInfo->linkStats, "ALG_PHOTOALIGN", TRUE);

    Utils_printLatency("ALG_PHOTOALIGN",
                       &pPAlignObj->linkStatsInfo->linkLatency,
                       &pPAlignObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
