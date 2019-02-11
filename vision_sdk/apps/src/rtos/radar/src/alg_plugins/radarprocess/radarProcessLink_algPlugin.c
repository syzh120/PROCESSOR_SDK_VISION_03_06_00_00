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
 * \file radarProcessLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for radar frame copy Link
 *
 * \version 0.0 (Sept 2016) : [PG] First version copy from frame copy
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "radarProcessLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <include/common/alg_functions.h>
#include <system_cfg.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RadarProcess_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_radarProcessCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_radarProcessProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_radarProcessControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_radarProcessStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_radarProcessDelete;

#ifdef BUILD_M4
    algId = ALGORITHM_LINK_IPU_ALG_RADAR_PROCESS;
#endif

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_RADAR_PROCESS;
#endif

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_RADAR_PROCESS;
#endif

#ifdef BUILD_A15
    algId = ALGORITHM_LINK_A15_ALG_RADAR_PROCESS;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

#ifdef BUILD_ARP32
    #if defined (ALG_FXN_radarfft2)
    {
        Void RadarFftWork_registerFxns();
        RadarFftWork_registerFxns();
    }
    #endif
    #if defined (ALG_FXN_radarpeakdetect)
    {
        Void RadarPkDetectWork_registerFxns();
        RadarPkDetectWork_registerFxns();
    }
    #endif
    #if defined (ALG_FXN_radarbeamform)
    {
        Void RadarBeamFormWork_registerFxns();
        RadarBeamFormWork_registerFxns();
    }
    #endif
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for frame copy algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_radarProcessCreate(void * pObj, void * pCreateParams)
{
    Int32                     frameIdx;
    Int32                     status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer           * pSystemBuffer;
    System_MetaDataBuffer   * pMetaDataBuffer;
    System_VideoFrameBuffer * pSystemVideoFrameBuffer;
    System_LinkInfo           prevLinkInfo;
    Int32                     outputQId;
    Int32                     numInputQUsed;
    Int32                     numOutputQUsed;
    UInt32                    prevLinkQueId;
    System_LinkChInfo       * pOutChInfo;
    AlgorithmLink_RadarProcessObj          * pAlgObj;
    AlgorithmLink_RadarProcessCreateParams * pRadarProcessCreateParams;

    AlgorithmLink_OutputQueueInfo       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo        * pInputQInfo;
    UInt32 i, j;

    pRadarProcessCreateParams =
        (AlgorithmLink_RadarProcessCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pAlgObj = (AlgorithmLink_RadarProcessObj *) Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_LOCAL,
                            sizeof(AlgorithmLink_RadarProcessObj), 32);

    UTILS_assert(pAlgObj!=NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            &pAlgObj->algLinkCreateParams,
            pRadarProcessCreateParams,
            sizeof(AlgorithmLink_RadarProcessCreateParams)
           );
    /* Get the corresponding alg functions */
    pAlgObj->algFxnTbl = AlgRadarProcessFxns_get(
        pAlgObj->algLinkCreateParams.algFxnName);

    UTILS_assert(pAlgObj->algFxnTbl != NULL);

    pAlgObj->createOpParams.inputBufCacheOps  = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_INV;
    pAlgObj->createOpParams.outputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB;

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */
    pAlgObj->algHandle = pAlgObj->algFxnTbl->alg_create(pRadarProcessCreateParams,
                            &pAlgObj->createOpParams);
    UTILS_assert(pAlgObj->algHandle != NULL);

    /*
     * Populating parameters corresponding to Q usage of frame copy
     * algorithm link
     */
    pOutputQInfo = &pAlgObj->outputQInfo;
    pInputQInfo  = &pAlgObj->inputQInfo;
    numInputQUsed     = 1;
    numOutputQUsed    = 1;
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    outputQId                 = 0;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In frame copy example, only pitch changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    prevLinkQueId = pRadarProcessCreateParams->inQueParams.prevLinkQueId;
    status = System_linkGetInfo(pRadarProcessCreateParams->inQueParams.prevLinkId, &prevLinkInfo);
    pAlgObj->numCh = pAlgObj->createOpParams.numOutputCh;
    pOutputQInfo->queInfo.numCh = pAlgObj->numCh;

    /*
     * Channel Info Population
     */
    for (i = 0U; i < pOutputQInfo->queInfo.numCh; i++)
    {
        pOutChInfo      = &(pOutputQInfo->queInfo.chInfo[i]);
        pAlgObj->inputChInfo[i] = prevLinkInfo.queInfo[prevLinkQueId].chInfo[i];
        /*
         * Certain channel info parameters simply get defined by previous link
         * channel info. Hence copying them to output channel info
         */
        memcpy(pOutChInfo, &pAlgObj->createOpParams.outputChannelInfo,
            sizeof (System_LinkChInfo));
    }

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
     * Creation of output buffers for output buffer Q = 0 (Used)
     *  - Connecting meta data frame buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    /* Only a single algorithm processing queue is currently supported */
    outputQId = 0;

    for (i = 0U; i < pOutputQInfo->queInfo.numCh; i++)
    {
        for(frameIdx = 0;
        frameIdx < pAlgObj->algLinkCreateParams.numOutputBuffers;
        frameIdx++)
        {
            Void *pBufAddr = NULL;
            UInt32 bufSize = 0;

            pSystemBuffer = &(pAlgObj->buffers[i][frameIdx]);
            switch (pAlgObj->createOpParams.outputBufferType)
            {
                case SYSTEM_BUFFER_TYPE_METADATA:
                    pMetaDataBuffer = &(pAlgObj->metaDataBuffers[i][frameIdx]);

                    /*
                    * Properties of pSystemBuffer, which do not get altered during
                    * run time (frame exchanges) are initialized here
                    */
                    pSystemBuffer->payload     = pMetaDataBuffer;
                    pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
                    pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
                    pSystemBuffer->chNum       = i;

                    UTILS_assert(pAlgObj->createOpParams.numMetaDataPlanes <= SYSTEM_MAX_META_DATA_PLANES);
                    pMetaDataBuffer->numMetaDataPlanes  =  pAlgObj->createOpParams.numMetaDataPlanes;
                    for (j = 0U; j < pAlgObj->createOpParams.numMetaDataPlanes; j++)
                    {
                        pMetaDataBuffer->metaBufSize[j] =
                            pAlgObj->createOpParams.metaBufSize[i][j];

                        /*
                         * Buffer allocation done for maxHeight, maxWidth and also assuming
                         * worst case num planes = 2, for data Format SYSTEM_DF_YUV422I_YUYV
                         * run time (frame exchanges) are initialized here
                         */
                        pMetaDataBuffer->bufAddr[j] = Utils_memAlloc(
                                                       UTILS_HEAPID_DDR_CACHED_SR,
                                                       pMetaDataBuffer->metaBufSize[j],
                                                       128);

                        pBufAddr = pMetaDataBuffer->bufAddr[j];
                        bufSize = pMetaDataBuffer->metaBufSize[j];

                        UTILS_assert(pMetaDataBuffer->bufAddr[j] != NULL);
                        pMetaDataBuffer->metaFillLength[j] = pMetaDataBuffer->metaBufSize[j];
                    }
                    pMetaDataBuffer->flags = 0;
                    break;

                case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                    pSystemVideoFrameBuffer = &(pAlgObj->videoDataBuffers[i][frameIdx]);
                    /*
                     * Properties of pSystemBuffer, which do not get altered during
                     * run time (frame exchanges) are initialized here
                     */
                    pSystemBuffer->payload     = pSystemVideoFrameBuffer;
                    pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
                    pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
                    pSystemBuffer->chNum       = i;

                    memcpy((void *)&pSystemVideoFrameBuffer->chInfo,
                           (void *)&pAlgObj->createOpParams.outputChannelInfo[i],
                           sizeof(System_LinkChInfo));
                    pSystemVideoFrameBuffer->bufAddr[0] = Utils_memAlloc(
                                               UTILS_HEAPID_DDR_CACHED_SR,
                                               pAlgObj->createOpParams.outputBufferSize[i],
                                               ALGORITHMLINK_FRAME_ALIGN);
                    UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);

                    pBufAddr = pSystemVideoFrameBuffer->bufAddr[0];
                    bufSize = pAlgObj->createOpParams.outputBufferSize[i];

                    if(pAlgObj->createOpParams.metaBufSize[i][0] != 0U)
                    {
                        pSystemVideoFrameBuffer->metaBufSize =
                                pAlgObj->createOpParams.metaBufSize[i][0];
                        pSystemVideoFrameBuffer->metaBufAddr = Utils_memAlloc(
                                               UTILS_HEAPID_DDR_CACHED_SR,
                                               pAlgObj->createOpParams.metaBufSize[i][0],
                                               ALGORITHMLINK_FRAME_ALIGN);
                        UTILS_assert(pSystemVideoFrameBuffer->metaBufAddr != NULL);
                    }
                break;
                default:
                /* Only Metadata and Video frame type currently supported */
                Vps_printf(" ALG_RADAR_PROCESS: Unsupported output buffer type!!\n");
                UTILS_assert(0);
            }
            #if 1
            Vps_printf(" ALG: %s: CH%d BUF%d: 0x%08x ( %d B )",
                pAlgObj->algLinkCreateParams.algFxnName,
                i,
                frameIdx,
                pBufAddr,
                bufSize
                );
            #endif
            AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
        }
    }

    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), pAlgObj->algLinkCreateParams.algFxnName);
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    pAlgObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for frame copy algorithm link
 *
 *        This function executes on the DSP or EVE or A15 processor.
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
Int32 AlgorithmLink_radarProcessProcess(void * pObj)
{
    AlgorithmLink_RadarProcessObj * pAlgObj;
    Int32                           inputQId;
    Int32                           status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                          bufId;
    System_BufferList               inputBufList;
    System_BufferList               inputBufListReturn;
    System_BufferList               outputBufListReturn;
    System_Buffer                 * pSysBufferInput;
    System_Buffer                 * pSysBufferOutput;
    Bool                            bufDropFlag;
    System_LinkStatistics         * linkStatsInfo;
    System_MetaDataBuffer         * pOutMetaBuf;
    System_VideoFrameBuffer       * pOutVideoFrameBuffer;
    UInt8 *pInAddr[SYSTEM_MAX_META_DATA_PLANES];
    UInt32 size[SYSTEM_MAX_META_DATA_PLANES];
    UInt32 numDataPlanes;
    UInt32 chNum;
    UInt32 i;

    pAlgObj = (AlgorithmLink_RadarProcessObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pAlgObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pAlgObj->isFirstFrameRecv==FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, pAlgObj->numCh, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
                               pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput           = inputBufList.buffers[bufId];
            if(pSysBufferInput == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }
            chNum = pSysBufferInput->chNum;
            linkStatsInfo->linkStats.chStats[chNum].inBufRecvCount++;

            /*
             * Getting free (empty) buffers from pool of output buffers
             */
            status = AlgorithmLink_getEmptyOutputBuffer(pObj,
                                                      0,
                                                      chNum,
                                                      &pSysBufferOutput);
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                linkStatsInfo->linkStats.chStats
                            [chNum].inBufDropCount++;
                linkStatsInfo->linkStats.chStats
                            [chNum].outBufDropCount[0]++;
            }
            else
            {
                pSysBufferOutput->srcTimestamp = pSysBufferInput->srcTimestamp;
                pSysBufferOutput->frameId = pSysBufferInput->frameId;
                pSysBufferOutput->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                /* Check what is the input buffer type to decide how to
                 * handle it.
                 */
                if (pSysBufferInput->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
                {
                    System_VideoFrameBuffer *pInVideoBuf;
                    pInVideoBuf  = (System_VideoFrameBuffer *) pSysBufferInput->payload;
                    pInAddr[0] = pInVideoBuf->bufAddr[0];
                    size[0] = pAlgObj->inputChInfo[chNum].pitch[0] *
                          pAlgObj->inputChInfo[chNum].height;
                    numDataPlanes = 1;
                }
                else if (pSysBufferInput->bufType == SYSTEM_BUFFER_TYPE_METADATA)
                {
                    System_MetaDataBuffer *pInMetaBuf;
                    pInMetaBuf = (System_MetaDataBuffer *) pSysBufferInput->payload;
                    numDataPlanes = pInMetaBuf->numMetaDataPlanes;
                    for (i = 0U; i < numDataPlanes; i++)
                    {
                        pInAddr[i] = pInMetaBuf->bufAddr[i];
                        size[i] = pInMetaBuf->metaBufSize[i];
                    }
                }
                else if (pSysBufferInput->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
                {
                    System_VideoFrameCompositeBuffer *pInCompositeVideoBuf;
                    pInCompositeVideoBuf  = (System_VideoFrameCompositeBuffer *) pSysBufferInput->payload;
                    for (i = 0; i < pInCompositeVideoBuf->numFrames; i++)
                    {
                        pInAddr[i] = pInCompositeVideoBuf->bufAddr[0][i];
                        size[i] = pInCompositeVideoBuf->chInfo.pitch[0] *
                                pInCompositeVideoBuf->chInfo.height;

                    }
                    numDataPlanes = pInCompositeVideoBuf->numFrames;
                }
                else
                {
                    /* No other input type is supported */
                    UTILS_assert(0);
                }
                if( pAlgObj->createOpParams.inputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_INV)
                {
                    for (i = 0U; i < numDataPlanes; i++)
                    {
                        Cache_inv (pInAddr[i], size[i], Cache_Type_ALLD, TRUE);
                    }
                }
                status = pAlgObj->algFxnTbl->alg_process(
                            pAlgObj->algHandle,
                            pSysBufferInput,
                            pSysBufferOutput
                        );
                UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
                switch (pAlgObj->createOpParams.outputBufferType)
                {
                    case SYSTEM_BUFFER_TYPE_METADATA:
                        pOutMetaBuf  = (System_MetaDataBuffer *)
                            pSysBufferOutput->payload;
                        numDataPlanes = pOutMetaBuf->numMetaDataPlanes;
                        for (i = 0U; i < numDataPlanes; i++)
                        {
                            if( (pAlgObj->createOpParams.outputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV)
                                == ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV
                                )
                            {
                                Cache_wbInv(
                                  pOutMetaBuf->bufAddr[i],
                                  pAlgObj->createOpParams.metaBufSize[chNum][i],
                                  Cache_Type_ALLD,
                                  TRUE
                                );
                            }
                            else
                            if( pAlgObj->createOpParams.outputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB)
                            {
                                Cache_wb(
                                  pOutMetaBuf->bufAddr[i],
                                  pAlgObj->createOpParams.metaBufSize[chNum][i],
                                  Cache_Type_ALLD,
                                  TRUE
                                );
                            }
                        }
                        break;
                    case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                        pOutVideoFrameBuffer = (System_VideoFrameBuffer *)
                            pSysBufferOutput->payload;
                        if( (pAlgObj->createOpParams.outputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV)
                            == ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV
                            )
                        {
                            Cache_wbInv(
                              pOutVideoFrameBuffer->bufAddr[0],
                              pAlgObj->createOpParams.outputBufferSize[chNum],
                              Cache_Type_ALLD,
                              TRUE
                            );
                        }
                        else
                        if( pAlgObj->createOpParams.outputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB)
                        {
                            Cache_wb(
                              pOutVideoFrameBuffer->bufAddr[0],
                              pAlgObj->createOpParams.outputBufferSize[chNum],
                              Cache_Type_ALLD,
                              TRUE
                            );
                        }

                        if(pAlgObj->createOpParams.metaBufSize[chNum][0] != 0U)
                        {
                            if( (pAlgObj->createOpParams.outputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV)
                                == ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV
                              )
                               {
                                Cache_wbInv(
                                    pOutVideoFrameBuffer->metaBufAddr,
                                    pAlgObj->createOpParams.metaBufSize[chNum][0],
                                    Cache_Type_ALLD,
                                    TRUE
                                );
                            }
                            else
                            if( pAlgObj->createOpParams.outputBufCacheOps & ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB)
                            {
                                Cache_wb(
                                  pOutVideoFrameBuffer->metaBufAddr,
                                  pAlgObj->createOpParams.metaBufSize[chNum][0],
                                  Cache_Type_ALLD,
                                  TRUE
                                );
                            }
                        }
                        break;
                    default:
                        UTILS_assert (0);
                        break;
                }
                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysBufferOutput->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysBufferOutput->srcTimestamp);

                linkStatsInfo->linkStats.chStats[chNum].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats[chNum].outBufCount[0]++;

                /*
                 * Putting filled buffer into output full buffer Q
                 * Note that this does not mean algorithm has freed the output
                 * buffer
                 */
                status = AlgorithmLink_putFullOutputBuffer(pObj,
                                                     0,
                                                     pSysBufferOutput);

                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(pAlgObj->algLinkCreateParams.outQueParams.nextLink,
                             SYSTEM_CMD_NEW_DATA,
                             NULL);

                /*
                 * Releasing (Free'ing) output buffer, since algorithm does
                 * not need it for any future usage.
                 * In case of INPLACE computation, there is no need to free
                 * output buffer, since it will be freed as input buffer.
                 */
                outputBufListReturn.numBuf     = 1;
                outputBufListReturn.buffers[0] = pSysBufferOutput;

                AlgorithmLink_releaseOutputBuffer(pObj, 0,
                    &outputBufListReturn);

                bufDropFlag = FALSE;

            }

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
                                      pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
                                      pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId,
                                      &inputBufListReturn,
                                      &bufDropFlag);
        } /* Input Buffer validity */

    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for frame copy algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_radarProcessControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_RadarProcessObj * pAlgObj;
    AlgorithmLink_RadarProcessControlParams     * pAlgLinkControlPrm;

    Int32  status    = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgorithmLink_RadarProcessObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pAlgLinkControlPrm = (AlgorithmLink_RadarProcessControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics.
     */
    switch(pAlgLinkControlPrm->controlCmd)
    {
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_radarProcessPrintStatistics(pObj, pAlgObj);
            break;
        case ALGORITHM_LINK_RADAR_PROCESS_CONTROL_CMD:
            status = pAlgObj->algFxnTbl->alg_control(
                            pAlgObj->algHandle, pAlgLinkControlPrm);
        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for frame copy algorithm link
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
Int32 AlgorithmLink_radarProcessStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for frame copy algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_radarProcessDelete(void * pObj)
{
    Int32                     frameIdx;
    Int32                     status = SYSTEM_LINK_STATUS_SOK;
    System_MetaDataBuffer   * pMetaDataBuffer;
    System_VideoFrameBuffer * pSystemVideoFrameBuffer;
    UInt32 i, j;

    AlgorithmLink_RadarProcessObj * pAlgObj;

    pAlgObj = (AlgorithmLink_RadarProcessObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = pAlgObj->algFxnTbl->alg_delete(pAlgObj->algHandle);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (i = 0U; i < pAlgObj->numCh; i++)
    {
        for(frameIdx = 0;
            frameIdx < (pAlgObj->algLinkCreateParams.numOutputBuffers);
            frameIdx++)
        {
            switch (pAlgObj->createOpParams.outputBufferType)
            {
                case SYSTEM_BUFFER_TYPE_METADATA:
                    pMetaDataBuffer = &(pAlgObj->metaDataBuffers[i][frameIdx]);

                    /*
                     * Free'ing up of allocated buffers
                     */
                    for (j = 0U; j < pMetaDataBuffer->numMetaDataPlanes; j++)
                    {
                        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                            pMetaDataBuffer->bufAddr[j],
                                            pAlgObj->createOpParams.metaBufSize[i][j]
                                            );
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    }
                    break;
                case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                    pSystemVideoFrameBuffer = &(pAlgObj->videoDataBuffers[i][frameIdx]);
                    /*
                     * Free'ing up of allocated buffers
                     */
                    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                           pSystemVideoFrameBuffer->bufAddr[0],
                                           pAlgObj->createOpParams.outputBufferSize[i]
                                           );

                   if(pSystemVideoFrameBuffer->metaBufAddr)
                   {
                        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                           pSystemVideoFrameBuffer->metaBufAddr,
                                           pAlgObj->createOpParams.metaBufSize[i][0]
                                           );
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    }
                    break;
                default:
                    UTILS_assert(0);
                    break;
            }
        }
    }
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                           pAlgObj, sizeof(AlgorithmLink_RadarProcessObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pAlgObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_radarProcessPrintStatistics(void *pObj,
                       AlgorithmLink_RadarProcessObj *pAlgObj)
{

    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats, pAlgObj->algLinkCreateParams.algFxnName, TRUE);

    Utils_printLatency(pAlgObj->algLinkCreateParams.algFxnName,
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
