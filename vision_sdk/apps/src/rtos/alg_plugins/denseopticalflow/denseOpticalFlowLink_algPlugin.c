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
 * \file denseOpticalFlowLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for dense optical flow Link
 *
 * \version 0.0 (Nov 2013) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "denseOpticalFlowLink_priv.h"
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
Int32 AlgorithmLink_DenseOptFlow_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_denseOptFlowCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_denseOptFlowProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_denseOptFlowControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_denseOptFlowStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_denseOptFlowDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_DENSE_OPTICAL_FLOW;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for dense optical flow alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_denseOptFlowCreate(void * pObj, void * pCreateParams)
{
    Int32                        bufId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    System_LinkInfo              prevLinkInfo;
    System_LinkChInfo          * pInChInfo;


    AlgorithmLink_DenseOptFlowObj            * pDenseOptFlowObj;
    AlgorithmLink_DenseOptFlowCreateParams   * pDenseOptFlowLinkCreateParams;
    Alg_LKParams                             * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo            * pOutputQInfo;
    AlgorithmLink_InputQueueInfo             * pInputQInfo;

    pDenseOptFlowLinkCreateParams =
        (AlgorithmLink_DenseOptFlowCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pDenseOptFlowObj = (AlgorithmLink_DenseOptFlowObj *)
                 Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                                sizeof(AlgorithmLink_DenseOptFlowObj), 32);

    UTILS_assert(pDenseOptFlowObj != NULL);

    pAlgCreateParams = &pDenseOptFlowObj->algCreateParams;

    pOutputQInfo = &pDenseOptFlowObj->outputQInfo;
    pInputQInfo  = &pDenseOptFlowObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pDenseOptFlowObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pDenseOptFlowObj->algLinkCreateParams),
           (void*)(pDenseOptFlowLinkCreateParams),
           sizeof(AlgorithmLink_DenseOptFlowCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of dense optical flow
     * algorithm link
     */
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;


    status = System_linkGetInfo(
                          pDenseOptFlowLinkCreateParams->inQueParams.prevLinkId,
                          &prevLinkInfo);

    pInChInfo = &prevLinkInfo.queInfo
                   [pDenseOptFlowLinkCreateParams->inQueParams.prevLinkQueId]
                    .chInfo[0];

    UTILS_assert(pInChInfo->height <= DENSE_OPTFLOW_LINK_MAX_HEIGHT);
    UTILS_assert(pInChInfo->width  <= DENSE_OPTFLOW_LINK_MAX_WIDTH);

    pDenseOptFlowObj->isFirstFrameRecv = FALSE;

    pAlgCreateParams->enableSmoothing   =
                                 pDenseOptFlowLinkCreateParams->enableSmoothing;
    pAlgCreateParams->maxVectorSizeX    =
                                 pDenseOptFlowLinkCreateParams->maxVectorSizeX;
    pAlgCreateParams->maxVectorSizeY    =
                                 pDenseOptFlowLinkCreateParams->maxVectorSizeY;
    pAlgCreateParams->numPyr            =
                 (Alg_LKnumPyr)pDenseOptFlowLinkCreateParams->numPyramids;


    pAlgCreateParams->smoothingKernSize =
                 (Alg_LKsmoothSize)pDenseOptFlowLinkCreateParams->smoothingSize;

    if(pDenseOptFlowObj->algLinkCreateParams.roiEnable==FALSE)
    {
        pAlgCreateParams->xRoiStart         = 0;
        pAlgCreateParams->yRoiStart         = 0;

        pAlgCreateParams->roiHeight         =
            pDenseOptFlowObj->algLinkCreateParams.roiParams.height;
        pAlgCreateParams->roiWidth          =
            pDenseOptFlowObj->algLinkCreateParams.roiParams.width;
        pDenseOptFlowObj->scratchSize =
                          pAlgCreateParams->roiWidth *
                          pAlgCreateParams->roiHeight * 3;
    }
    else
    {
        pAlgCreateParams->xRoiStart         =
            pDenseOptFlowObj->algLinkCreateParams.roiParams.startX;
        pAlgCreateParams->yRoiStart         =
            pDenseOptFlowObj->algLinkCreateParams.roiParams.startY;

        pAlgCreateParams->roiHeight         =
            pDenseOptFlowObj->algLinkCreateParams.roiParams.height;
        pAlgCreateParams->roiWidth          =
            pDenseOptFlowObj->algLinkCreateParams.roiParams.width;

        pDenseOptFlowObj->algLinkCreateParams.processPeriodicity = 1;
        pDenseOptFlowObj->algLinkCreateParams.processStartFrame = 0;

        UTILS_assert(pAlgCreateParams->xRoiStart+pAlgCreateParams->roiWidth
                        <=
                     pInChInfo->width);
        UTILS_assert(pAlgCreateParams->yRoiStart+pAlgCreateParams->roiHeight
                        <=
                     pInChInfo->height);
        pDenseOptFlowObj->scratchSize =
                     pDenseOptFlowObj->algLinkCreateParams.roiParams.width *
                     pDenseOptFlowObj->algLinkCreateParams.roiParams.height * 3;
    }

    /* Allocate scratch memory required for the DOF alg */
    pDenseOptFlowObj->scratch =
                      Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                     pDenseOptFlowObj->scratchSize, 32);

    UTILS_assert(pDenseOptFlowObj->scratch != NULL);

    pAlgCreateParams->scratch = pDenseOptFlowObj->scratch;
    pAlgCreateParams->edmaAlgAutoIncrementContext1 =
                      Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
                                     EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE, 32);
    pAlgCreateParams->edmaAlgAutoIncrementContext2 =
                      Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
                                     EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE, 32);
    pAlgCreateParams->edmaAlgAutoIncrementContext3 =
                      Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
                                     EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE, 32);


    pAlgCreateParams->imWidth =
        pAlgCreateParams->roiWidth;

    pAlgCreateParams->imHeight =
        pAlgCreateParams->roiHeight;

    pAlgCreateParams->imPitch  = pInChInfo->pitch[0];

    status = Alg_LKPyrm_create(pAlgCreateParams, &pDenseOptFlowObj->algMemRequests);
    UTILS_assert(status == 0);

    /* pitch should be equal to width */
    pDenseOptFlowObj->outBufPitch = pAlgCreateParams->roiWidth;

    pDenseOptFlowObj->outBufSize =
           pAlgCreateParams->roiHeight * pDenseOptFlowObj->outBufPitch;

    if(pDenseOptFlowObj->algLinkCreateParams.numOutBuf
        > DENSE_OPTFLOW_LINK_MAX_NUM_OUTPUT
        )
    {
        pDenseOptFlowObj->algLinkCreateParams.numOutBuf =
            DENSE_OPTFLOW_LINK_MAX_NUM_OUTPUT;
    }

    pOutputQInfo->queInfo.numCh = 1;
    pOutputQInfo->queInfo.chInfo[0].flags    = pInChInfo->flags;
    pOutputQInfo->queInfo.chInfo[0].pitch[0] = pDenseOptFlowObj->outBufPitch;
    pOutputQInfo->queInfo.chInfo[0].pitch[1] = pDenseOptFlowObj->outBufPitch;
    pOutputQInfo->queInfo.chInfo[0].startX   = 0;
    pOutputQInfo->queInfo.chInfo[0].startY   = 0;
    pOutputQInfo->queInfo.chInfo[0].width    = pInChInfo->width;
    pOutputQInfo->queInfo.chInfo[0].height   = pInChInfo->height;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                1,
                                pInputQInfo,
                                1,
                                pOutputQInfo
                                );

    for(bufId = 0; bufId < pDenseOptFlowObj->algLinkCreateParams.numOutBuf; bufId++)
    {
        pSystemBuffer = &pDenseOptFlowObj->buffers[bufId];
        pSystemMetaDataBuffer = &pDenseOptFlowObj->optFlowTbl[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */

        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum       = 0;

        pSystemMetaDataBuffer->numMetaDataPlanes = 2;
        pSystemMetaDataBuffer->metaBufSize[0] = pDenseOptFlowObj->outBufSize;
        pSystemMetaDataBuffer->metaFillLength[0] = pDenseOptFlowObj->outBufSize;
        pSystemMetaDataBuffer->bufAddr[0] = Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pDenseOptFlowObj->outBufSize,
                                                    ALGORITHMLINK_FRAME_ALIGN
                                                    );
        UTILS_assert(pSystemMetaDataBuffer->bufAddr[0] != NULL);
        pSystemMetaDataBuffer->metaBufSize[1] = pDenseOptFlowObj->outBufSize;
        pSystemMetaDataBuffer->metaFillLength[1] = pDenseOptFlowObj->outBufSize;
        pSystemMetaDataBuffer->bufAddr[1] = Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pDenseOptFlowObj->outBufSize,
                                                    ALGORITHMLINK_FRAME_ALIGN
                                                    );

        UTILS_assert(pSystemMetaDataBuffer->bufAddr[1] != NULL);

        pSystemMetaDataBuffer->flags = 0;

        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }


    pDenseOptFlowObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
         AlgorithmLink_getLinkId(pObj), "ALG_DENSE_OPTICAL_FLOW");
    UTILS_assert(NULL != pDenseOptFlowObj->linkStatsInfo);

    /*
     * Initilaizing frame skip parmaters needed for the process call
     */
    pDenseOptFlowObj->pPrevious = NULL;
    pDenseOptFlowObj->pCurrent  = NULL;
    pDenseOptFlowObj->frameCount = 0;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of dense optical flow alg link
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
Int32 AlgorithmLink_denseOptFlowProcess(void * pObj)
{
    AlgorithmLink_DenseOptFlowObj *pDenseOptFlowObj;
    AlgorithmLink_DenseOptFlowCreateParams *pDenseOptFlowCreateParams;
    System_BufferList inputBufList;
    System_VideoFrameBuffer *currentFrame, *previousFrame;
    System_Buffer *pSysBuf;
    System_BufferList            outputBufListReturn;
    System_BufferList            inputBufListReturn;
    System_MetaDataBuffer *pMetaBuf;
    Alg_LKParams          *pAlgCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId = 0, skipBuf, inBufOffset;
    Bool bufDropFlag;

    pDenseOptFlowObj = (AlgorithmLink_DenseOptFlowObj *)
                              AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pDenseOptFlowObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    pDenseOptFlowCreateParams = &pDenseOptFlowObj->algLinkCreateParams;

    if (pDenseOptFlowObj->isFirstFrameRecv == FALSE)
    {
        pDenseOptFlowObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);
                                  ;
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                 pDenseOptFlowCreateParams->inQueParams.prevLinkId,
                 pDenseOptFlowCreateParams->inQueParams.prevLinkQueId,
                 &inputBufList);

    if (inputBufList.numBuf)
    {
        for(bufId=0; bufId<inputBufList.numBuf; bufId++)
        {
            if(inputBufList.buffers[bufId]==NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

            if(pDenseOptFlowObj->pPrevious == NULL)
            {
                pDenseOptFlowObj->pPrevious = inputBufList.buffers[bufId];
            }
            else
            if(pDenseOptFlowObj->pCurrent == NULL)
            {
                pDenseOptFlowObj->pCurrent = inputBufList.buffers[bufId];
            }
            else
            {
                pDenseOptFlowObj->pPrevious =
                    pDenseOptFlowObj->pCurrent;

                pDenseOptFlowObj->pCurrent =
                    inputBufList.buffers[bufId];
            }

            if (pDenseOptFlowObj->pPrevious && pDenseOptFlowObj->pCurrent)
            {
                skipBuf = TRUE;

                if(pDenseOptFlowObj->frameCount
                    ==
                  pDenseOptFlowCreateParams->processStartFrame)
                {
                    skipBuf = FALSE;
                }

                pDenseOptFlowObj->frameCount
                    =
                    (pDenseOptFlowObj->frameCount+1)
                    %
                    pDenseOptFlowCreateParams->processPeriodicity;

                if(skipBuf)
                {
                     linkStatsInfo->linkStats.chStats
                                    [0].inBufUserDropCount++;
                }
                if(!skipBuf && pDenseOptFlowCreateParams->algEnable)
                {
                    currentFrame =
                        (System_VideoFrameBuffer *)
                            pDenseOptFlowObj->pCurrent->payload;

                    previousFrame =
                        (System_VideoFrameBuffer *)
                            pDenseOptFlowObj->pPrevious->payload;

                    status = AlgorithmLink_getEmptyOutputBuffer(
                                                            pObj,
                                                            0,
                                                            0,
                                                            &pSysBuf
                                                            );
                    if(status != SYSTEM_LINK_STATUS_SOK)
                    {
                         linkStatsInfo->linkStats.chStats
                                        [0].inBufDropCount++;
                         linkStatsInfo->linkStats.chStats
                                        [0].outBufDropCount[0]++;

                    }
                    else
                    {
                        pSysBuf->srcTimestamp = pDenseOptFlowObj->pCurrent->srcTimestamp;
                        pSysBuf->frameId = pDenseOptFlowObj->pCurrent->frameId;

                        pSysBuf->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                        pMetaBuf = (System_MetaDataBuffer *) pSysBuf->payload;

                        pAlgCreateParams = &pDenseOptFlowObj->algCreateParams;

                        inBufOffset = 0;

                        if(pDenseOptFlowCreateParams->roiEnable)
                        {
                            inBufOffset = pAlgCreateParams->yRoiStart
                                         *pAlgCreateParams->imPitch
                                         +
                                          pAlgCreateParams->xRoiStart;

                        }
                        status = Alg_LKPyrm_process(
                                 (UInt8*)previousFrame->bufAddr[0] + inBufOffset,
                                 (UInt8*)currentFrame->bufAddr[0] + inBufOffset,
                                       pAlgCreateParams,
                                       pMetaBuf->bufAddr[0],
                                       pMetaBuf->bufAddr[1]);

                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                        Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pSysBuf->linkLocalTimestamp);
                        Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pSysBuf->srcTimestamp);

                         linkStatsInfo->linkStats.chStats
                                    [0].inBufProcessCount++;
                         linkStatsInfo->linkStats.chStats
                                    [0].outBufCount[0]++;

                        status = AlgorithmLink_putFullOutputBuffer(pObj,
                                                               0,
                                                               pSysBuf);
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                       /*
                        * Informing next link that a new data has peen put for its
                        * processing
                        */

                        System_sendLinkCmd(
                          pDenseOptFlowCreateParams->outQueParams.nextLink,
                          SYSTEM_CMD_NEW_DATA,
                          NULL);


                       /*
                        * Releasing (Free'ing) output buffers, since algorithm
                        * does not need it for any future usage.
                        */
                        outputBufListReturn.numBuf = 1;
                        outputBufListReturn.buffers[0] = pSysBuf;

                        AlgorithmLink_releaseOutputBuffer(
                                                      pObj,
                                                      0,
                                                      &outputBufListReturn
                                                      );
                    }
                }

                /*
                 * Releasing (Free'ing) Input buffers, since algorithm does
                 * not need it for any future usage.
                 */
                inputBufListReturn.numBuf = 1;
                inputBufListReturn.buffers[0] = pDenseOptFlowObj->pPrevious;
                bufDropFlag = FALSE;
                AlgorithmLink_releaseInputBuffer(
                          pObj,
                          0,
                          pDenseOptFlowCreateParams->inQueParams.prevLinkId,
                          pDenseOptFlowCreateParams->inQueParams.prevLinkQueId,
                          &inputBufListReturn,
                          &bufDropFlag);
            }
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for vector to image algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_denseOptFlowControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_DenseOptFlowObj   * pDenseOptFlowObj;
    AlgorithmLink_ControlParams     * pAlgLinkControlPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pDenseOptFlowObj = (AlgorithmLink_DenseOptFlowObj *)
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
            AlgorithmLink_denseOptFlowPrintStatistics(pObj, pDenseOptFlowObj);
            break;

        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for dense optical flow algorithm
 *
 *        For this algorithm there is no locking of frames and hence no
 *        flushing of frames. Also there are no any other functionality to be
 *        one at the end of execution of this algorithm. Hence this function
 *        is an empty function for this algorithm.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_denseOptFlowStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for dense optical flow algorithm
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_denseOptFlowDelete(void * pObj)
{
    UInt32 bufId;
    AlgorithmLink_DenseOptFlowObj *pDenseOptFlowObj;
    System_MetaDataBuffer *pMetaBuf;
    UInt32 status = SYSTEM_LINK_STATUS_SOK;

    pDenseOptFlowObj = (AlgorithmLink_DenseOptFlowObj *)
                          AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pDenseOptFlowObj->linkStatsInfo);
    UTILS_assert(status == 0);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                  pDenseOptFlowObj->algCreateParams.edmaAlgAutoIncrementContext1,
                  EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                  pDenseOptFlowObj->algCreateParams.edmaAlgAutoIncrementContext2,
                  EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                  pDenseOptFlowObj->algCreateParams.edmaAlgAutoIncrementContext3,
                  EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           pDenseOptFlowObj->scratch,
                           pDenseOptFlowObj->scratchSize);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Alg_LKPyrm_delete(&pDenseOptFlowObj->algCreateParams, &pDenseOptFlowObj->algMemRequests);
    UTILS_assert(status == 0);


    /*
     * All allocations done at create time have to be de-allocated
     */

    for (bufId = 0; bufId < pDenseOptFlowObj->algLinkCreateParams.numOutBuf; bufId++)
    {
        pMetaBuf = pDenseOptFlowObj->buffers[bufId].payload;
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pMetaBuf->bufAddr[0], pDenseOptFlowObj->outBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pMetaBuf->bufAddr[1],pDenseOptFlowObj->outBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Space for Algorithm specific object gets freed here.
     */
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                           pDenseOptFlowObj,
                           sizeof(AlgorithmLink_DenseOptFlowObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pDenseOptFlowObj        [IN] optical flow Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_denseOptFlowPrintStatistics(void *pObj,
                       AlgorithmLink_DenseOptFlowObj *pDenseOptFlowObj)
{
    UTILS_assert(NULL != pDenseOptFlowObj->linkStatsInfo);

    Utils_printLinkStatistics(&pDenseOptFlowObj->linkStatsInfo->linkStats,
                            "ALG_DENSE_OPT_FLOW",
                            TRUE);

    Utils_printLatency("ALG_DENSE_OPT_FLOW",
                       &pDenseOptFlowObj->linkStatsInfo->linkLatency,
                       &pDenseOptFlowObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
