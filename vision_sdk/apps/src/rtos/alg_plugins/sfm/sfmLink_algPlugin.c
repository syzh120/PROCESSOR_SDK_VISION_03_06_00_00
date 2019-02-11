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
 * \file sfmLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for algorithm plugin
 *         Link
 *
 * \version 0.0 (Feb 2014) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "sfmLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <math.h>

/* uncomment below to disable calling of alg process API - used for debug ONLY */
//#define ALG_DISABLE

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of gAlign algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfm_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_sfmCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_sfmProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_sfmControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_sfmStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_sfmDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SFM;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Alg uses the IVISION standard to interact with the
 *        framework. All process/control calls to the algorithm should adhere
 *        to the IVISION standard. This function initializes input and output
 *        buffers
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmAlgParamsInit (
                                  AlgorithmLink_SfmObj *pObj,
                                  System_LinkChInfo *inChInfo
                                )
{
    UInt32 i;

    pObj->algSfmInBufs.size    = sizeof(pObj->algSfmInBufs);
    pObj->algSfmInBufs.numBufs = 1;
    pObj->algSfmInBufs.bufDesc = pObj->algSfmInBufDesc;

    pObj->algSfmInBufDesc[0]   = &pObj->algSfmInBufDescSofPoints;

    pObj->algSfmOutBufs.size    = sizeof(pObj->algSfmOutBufs);
    pObj->algSfmOutBufs.numBufs = 1;
    pObj->algSfmOutBufs.bufDesc = pObj->algSfmOutBufDesc;

    pObj->algSfmOutBufDesc[0]   = &pObj->algSfmOutBufDescSfmPoints;

    memset(&pObj->algSfmInArgs, 0, sizeof(pObj->algSfmInArgs));
    pObj->algSfmInArgs.iVisionInArgs.size         = sizeof(pObj->algSfmInArgs);
    pObj->algSfmInArgs.iVisionInArgs.subFrameInfo = 0;

    pObj->algSfmCreateParams.visionParams.algParams.size = sizeof(pObj->algSfmCreateParams);
    pObj->algSfmCreateParams.visionParams.cacheWriteBack = NULL;
    pObj->algSfmCreateParams.camExtPrmNormType = SFM_TI_CAM_EXT_PRM_NORM_DEFAULT;
    for(i=0; i<SFM_TI_CAMERA_INTRINSIC_PARAM_SIZE; i++)
    {
        pObj->algSfmCreateParams.camIntPrm[i]
            =
            pObj->algLinkCreateParams.cameraIntrinsicParams[i];
    }
    pObj->algSfmCreateParams.maxNumTracks = pObj->algLinkCreateParams.maxTrackPoints;

    pObj->algSfmInArgs.numTracks         = pObj->algSfmCreateParams.maxNumTracks;
    /* pObj->algSfmInArgs.camExtPrm[x] is set later on a per frame basis */
    pObj->algSfmInArgs.fMatrixCalcMethod = SFM_TI_FMAT_EXT_PRM_NORM_DEFAULT;
    pObj->algSfmInArgs.fMatrixPrunEn     = 1;
    pObj->algSfmInArgs.fMatrixInTh       = 7;
    pObj->algSfmInArgs.maxRansacItr      = 45;
    pObj->algSfmInArgs.maxTriangItr      = 3;
    pObj->algSfmInArgs.curPrev3DPtFlag   = SFM_TI_OUT_CUR_PREV_3D_POINTS_DEFAULT;
    pObj->algSfmInArgs.trackPtQfmt       = 4;
    pObj->algSfmInArgs.pointPruneAngle   = 2.0;
    pObj->algSfmInArgs.reserved0         = 0;
    pObj->algSfmInArgs.reserved1         = 0;

    memset(&pObj->algSfmOutArgs, 0, sizeof(pObj->algSfmOutArgs));
    pObj->algSfmOutArgs.iVisionOutArgs.size         = sizeof(pObj->algSfmOutArgs);

    memset(&pObj->algSfmInBufDescSofPoints, 0, sizeof(pObj->algSfmInBufDescSofPoints));
    pObj->algSfmInBufDescSofPoints.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].buf                 = NULL;
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].width               = pObj->algLinkCreateParams.maxTrackPoints*sizeof(SFM_TI_trackInfo);
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].height              = 1;
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].frameROI.width      = pObj->algSfmInBufDescSofPoints.bufPlanes[0].width;
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].frameROI.height     = 1;
    pObj->algSfmInBufDescSofPoints.bufPlanes[0].planeType           = 0;
    pObj->algSfmInBufDescSofPoints.formatType                       = 0; /* NOT USED */
    pObj->algSfmInBufDescSofPoints.bufferId                         = 0xFF; /* NOT USED */

    memset(&pObj->algSfmOutBufDescSfmPoints, 0, sizeof(pObj->algSfmOutBufDescSfmPoints));
    pObj->algSfmOutBufDescSfmPoints.numPlanes                        = 1;
    /* Will be filled with output pointer later
     */
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].buf                 = NULL;
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].width               = pObj->algLinkCreateParams.maxTrackPoints*sizeof(SFM_TI_output);
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].height              = 1;
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].frameROI.width      = pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].width;
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].frameROI.height     = 1;
    pObj->algSfmOutBufDescSfmPoints.bufPlanes[0].planeType           = 0;
    pObj->algSfmOutBufDescSfmPoints.formatType                       = 0; /* NOT USED */
    pObj->algSfmOutBufDescSfmPoints.bufferId                         = 0xFF; /* NOT USED */

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sfmCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_SfmObj                  * pAlgObj;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_SfmObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_SfmObj),
                        128);
    UTILS_assert(pAlgObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    pInputQInfo       = &pAlgObj->inputQInfo;
    pOutputQInfo      = &pAlgObj->outputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            &pAlgObj->algLinkCreateParams,
            pCreateParams,
            sizeof(pAlgObj->algLinkCreateParams)
           );

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    status = System_linkGetInfo(
                    pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
                    &prevLinkInfo
                    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= 1);
    UTILS_assert(pAlgObj->algLinkCreateParams.maxTrackPoints <= SFM_LINK_MAX_TRACK_POINTS);
    UTILS_assert(pAlgObj->algLinkCreateParams.cameraExtrinsicParamsDataSize <= pAlgObj->algLinkCreateParams.cameraExtrinsicParamsBufSize);
    UTILS_assert(pAlgObj->algLinkCreateParams.cameraExtrinsicParamsBufAddr != NULL);

    prevLinkQId = pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId;
    pAlgObj->inChInfo = prevLinkInfo.queInfo[prevLinkQId].chInfo[0];

    pOutputQInfo->queInfo.numCh = 1;

    pOutChInfo          = &pOutputQInfo->queInfo.chInfo[0];
    pOutChInfo->flags   = 0;
    pOutChInfo->height  = 0;
    pOutChInfo->width   = 0;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(
                                    pObj,
                                    1,
                                    pInputQInfo,
                                    1,
                                    pOutputQInfo
                               );

    AlgorithmLink_sfmAlgParamsInit(pAlgObj, &pAlgObj->inChInfo);

    pAlgObj->algSfmHandle = AlgIvision_create(
                        &SFM_TI_VISION_FXNS,
                        (IALG_Params *)&pAlgObj->algSfmCreateParams
                        );
    UTILS_assert(pAlgObj->algSfmHandle!=NULL);

    if(pAlgObj->algLinkCreateParams.numOutBuffers
        > SFM_LINK_MAX_NUM_OUTPUT)
    {
        pAlgObj->algLinkCreateParams.numOutBuffers
            = SFM_LINK_MAX_NUM_OUTPUT;
    }

    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */

    for (bufId = 0; bufId < pAlgObj->algLinkCreateParams.numOutBuffers; bufId++)
    {
        pSystemBuffer       =   &pAlgObj->buffers[bufId];
        pMetaDataBuffer     =   &pAlgObj->metaDataBuffers[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pMetaDataBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =   0;

        pMetaDataBuffer->numMetaDataPlanes  =  1;
        pMetaDataBuffer->metaBufSize[0]
            =  SFM_LINK_SFM_POINTS_BUF_SIZE;

        pMetaDataBuffer->bufAddr[0]         =  Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pMetaDataBuffer->metaBufSize[0],
                                                    128
                                                    );

        pMetaDataBuffer->metaFillLength[0] = pMetaDataBuffer->metaBufSize[0];

        UTILS_assert(pMetaDataBuffer->bufAddr[0] != NULL);

        pMetaDataBuffer->flags = 0;

        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    pAlgObj->isFirstFrameRecv    = FALSE;

    /* Assign pointer to link stats object */
    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_SFM");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    /* Invalidate extrinic parameter buffer */
    Cache_inv(
              (Ptr)pAlgObj->algLinkCreateParams.cameraExtrinsicParamsBufAddr,
              pAlgObj->algLinkCreateParams.cameraExtrinsicParamsBufSize,
              Cache_Type_ALLD,
              TRUE
            );

    pAlgObj->maxFrameId = pAlgObj->algLinkCreateParams.cameraExtrinsicParamsDataSize
                    /
        sizeof(pAlgObj->algSfmInArgs.camExtPrm);

    return SYSTEM_LINK_STATUS_SOK;
}

Void AlgorithmLink_sfmSetCamExtPrm(AlgorithmLink_SfmObj * pAlgObj, UInt32 frameId)
{
    UInt32 offset;
    UInt32 copySize;

    copySize = sizeof(pAlgObj->algSfmInArgs.camExtPrm);
    offset = copySize*frameId;

    if( (offset+copySize) <=
        pAlgObj->algLinkCreateParams.cameraExtrinsicParamsDataSize)
    {
        memcpy(pAlgObj->algSfmInArgs.camExtPrm,
                (void*)(pAlgObj->algLinkCreateParams.cameraExtrinsicParamsBufAddr+offset),
               copySize
                );
    }
}

Int32 AlgorithmLink_sfmProcess(void * pObj)
{
    UInt32 bufId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_SfmObj                  * pAlgObj;
    System_BufferList                       inputBufList;
    AlgorithmLink_SfmCreateParams         * pLinkCreatePrms;
    System_Buffer                         * pSysOutBuffer;
    System_Buffer                         * pSysInBuffer;
    System_MetaDataBuffer                 * pInMetaBuf;
    System_MetaDataBuffer                 * pOutMetaBuf;
    System_BufferList                     bufListReturn;
    System_LinkStatistics *linkStatsInfo;

    pAlgObj = (AlgorithmLink_SfmObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);


    pLinkCreatePrms = &pAlgObj->algLinkCreateParams;

    linkStatsInfo = pAlgObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if (pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                        pLinkCreatePrms->inQueParams.prevLinkId,
                        pLinkCreatePrms->inQueParams.prevLinkQueId,
                        &inputBufList);


    if (inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];
            if(pSysInBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

            if( pSysInBuffer->frameId < pAlgObj->maxFrameId)
            {
                /* valid frame ID */
                status = AlgorithmLink_getEmptyOutputBuffer(
                                                        pObj,
                                                        0,
                                                        0,
                                                        &pSysOutBuffer
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
                    AlgorithmLink_SfmOutput *pSfmOutput;

                    pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                    pSysOutBuffer->frameId = pSysInBuffer->frameId;
                    pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                    pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                    pInMetaBuf  = (System_MetaDataBuffer *) pSysInBuffer->payload;

                    pSfmOutput = (AlgorithmLink_SfmOutput*)pOutMetaBuf->bufAddr[0];

                    pAlgObj->algSfmInBufDescSofPoints.bufPlanes[0].buf =
                        (Void*)pInMetaBuf->bufAddr[0];
                                ;

                    pAlgObj->algSfmOutBufDescSfmPoints.bufPlanes[0].buf = (Void*)
                        (&pSfmOutput->sfmOut[0]);

                    AlgorithmLink_sfmSetCamExtPrm(pAlgObj, pSysInBuffer->frameId);

                    Cache_inv(
                              pInMetaBuf->bufAddr[0],
                              pInMetaBuf->metaBufSize[0],
                              Cache_Type_ALLD,
                              TRUE
                            );

                    #ifndef ALG_DISABLE

                        #if 0
                        Vps_printf(" ALG_SFM: Running .... !!!\n"
                            );
                        #endif

                        status = AlgIvision_process(
                                        pAlgObj->algSfmHandle,
                                        &pAlgObj->algSfmInBufs,
                                        &pAlgObj->algSfmOutBufs,
                                        (IVISION_InArgs*)&pAlgObj->algSfmInArgs,
                                        (IVISION_OutArgs *)&pAlgObj->algSfmOutArgs
                            );

                        #if 0
                        Vps_printf(" ALG_SFM: %d points [%d %d %d]!!!\n",
                            pAlgObj->algSfmOutArgs.outNumPoints,
                            pAlgObj->algSfmOutArgs.sfmStats.numIterFMat,
                            pAlgObj->algSfmOutArgs.sfmStats.numInlierFmat,
                            pAlgObj->algSfmOutArgs.sfmStats.numCur3DPnts
                            );
                        #endif

                        #if 1
                        if(status!=IALG_EOK)
                        {
                            Vps_printf(" ALG_SFM: ERROR: Alg process !!!\n");
                        }
                        #endif
                    #else
                        pAlgObj->algSfmOutArgs.outNumPoints = 0;
                    #endif

                    pSfmOutput->outNumPoints
                        = pAlgObj->algSfmOutArgs.outNumPoints;

                    /* copy camera extrinsic parameters to
                        output buffer, since these could be used by
                        FCW
                     */
                    memcpy(
                        pSfmOutput->camExtPrm,
                        pAlgObj->algSfmInArgs.camExtPrm,
                        sizeof(pSfmOutput->camExtPrm)
                        );

                    Cache_wb(
                              pOutMetaBuf->bufAddr[0],
                              pOutMetaBuf->metaBufSize[0],
                              Cache_Type_ALLD,
                              TRUE
                            );

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pSysOutBuffer->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pSysOutBuffer->srcTimestamp);

                    linkStatsInfo->linkStats.chStats
                                [0].inBufProcessCount++;
                    linkStatsInfo->linkStats.chStats
                                [0].outBufCount[0]++;

                    status = AlgorithmLink_putFullOutputBuffer(
                                                pObj,
                                                0,
                                                pSysOutBuffer);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    System_sendLinkCmd(
                            pLinkCreatePrms->outQueParams.nextLink,
                            SYSTEM_CMD_NEW_DATA,
                            NULL);

                    bufListReturn.numBuf = 1;
                    bufListReturn.buffers[0] = pSysOutBuffer;
                    status = AlgorithmLink_releaseOutputBuffer(
                                                       pObj,
                                                       0,
                                                       &bufListReturn
                                                      );
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
            }
            else
            {
                /* invalid frame ID, drop frame */
                linkStatsInfo->linkStats.chStats
                            [0].inBufDropCount++;
                linkStatsInfo->linkStats.chStats
                            [0].outBufDropCount[0]++;
            }
            bufListReturn.numBuf = 1;
            bufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                          pObj,
                          0,
                          pLinkCreatePrms->inQueParams.prevLinkId,
                          pLinkCreatePrms->inQueParams.prevLinkQueId,
                          &bufListReturn,
                          &bufDropFlag);
        }
    }
    return status;
}

Int32 AlgorithmLink_sfmControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_SfmObj* pAlgObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgorithmLink_SfmObj *)
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
            AlgorithmLink_sfmPrintStatistics(
                                                                pObj,
                                                                pAlgObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_sfmStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_sfmDelete(void * pObj)
{
    Int32 status;
    UInt32 bufId;
    AlgorithmLink_SfmObj *pAlgObj;
    System_MetaDataBuffer              *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_SfmObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status==0);

    /*
     * Free allocated memory for alg internal objects
     */
    status = AlgIvision_delete(pAlgObj->algSfmHandle);
    UTILS_assert(status==0);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pAlgObj->algLinkCreateParams.numOutBuffers; bufId++)
    {
        pMetaDataBuffer     =   &pAlgObj->metaDataBuffers[bufId];

        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pMetaDataBuffer->bufAddr[0],
                                pMetaDataBuffer->metaBufSize[0]
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    Utils_memFree(
                       UTILS_HEAPID_DDR_CACHED_LOCAL,
                       pAlgObj,
                       sizeof(AlgorithmLink_SfmObj)
                    );
    return status;

}

Int32 AlgorithmLink_sfmPrintStatistics(void *pObj,
                AlgorithmLink_SfmObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
                            "ALG_SFM",
                            TRUE);

    Utils_printLatency("ALG_SFM",
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

int TI_DSP_ProfileModule(void* prfInfo, unsigned int moduleId, unsigned int start, unsigned int acc)
{
    return 0;
}

unsigned int TI_DSP_ProfileInit(void* prfInfo)
{
    return 0;
}
