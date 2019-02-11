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
 * \file laneDetectLink_algPlugin.c
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

#include "laneDetectLink_priv.h"
#include <include/link_api/system_common.h>
#include <include/alglink_api/algorithmLink_imgPyramid.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <math.h>

/* uncomment below to disable calling of alg process API - used for debug ONLY */
//#define ALG_DISABLE

/* Flag to enable or disable the Lane detection algorithm Reset */
#define LD_RESET

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
Int32 AlgorithmLink_laneDetect_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_laneDetectCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_laneDetectProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_laneDetectControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_laneDetectStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_laneDetectDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_LANE_DETECT;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Feature Plane Alg uses the IVISION standard to interact with the
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
Int32 AlgorithmLink_laneDetectAlgParamsInit (
                                  AlgorithmLink_LaneDetectObj *pObj,
                                  System_LinkChInfo *inChInfo
                                )
{
    pObj->algLdInBufs.size    = sizeof(pObj->algLdInBufs);
    pObj->algLdInBufs.numBufs = 1;
    pObj->algLdInBufs.bufDesc = pObj->algLdInBufDesc;

    pObj->algLdInBufDesc[0]   = &pObj->algLdInBufDescImage;

    pObj->algLdOutBufs.size    = sizeof(pObj->algLdOutBufs);
    pObj->algLdOutBufs.numBufs = 1;
    pObj->algLdOutBufs.bufDesc = pObj->algLdOutBufDesc;

    pObj->algLdOutBufDesc[0]   = &pObj->algLdOutBufDescLanePoints;

    memset(&pObj->algLdInArgs, 0, sizeof(pObj->algLdInArgs));
    pObj->algLdInArgs.iVisionInArgs.size         = sizeof(pObj->algLdInArgs);
    pObj->algLdInArgs.iVisionInArgs.subFrameInfo = 0;

    pObj->algLdInArgs.cannyHighThresh        = pObj->algLinkCreateParams.cannyHighThresh;
    pObj->algLdInArgs.cannyLowThresh         = pObj->algLinkCreateParams.cannyLowThresh;
    pObj->algLdInArgs.houghNmsThresh         = pObj->algLinkCreateParams.houghNmsThresh;
    pObj->algLdInArgs.startThetaLeft         = pObj->algLinkCreateParams.startThetaLeft;
    pObj->algLdInArgs.endThetaLeft           = pObj->algLinkCreateParams.endThetaLeft;
    pObj->algLdInArgs.startThetaRight        = pObj->algLinkCreateParams.startThetaRight;
    pObj->algLdInArgs.endThetaRight          = pObj->algLinkCreateParams.endThetaRight;
    pObj->algLdInArgs.thetaStepSize          = pObj->algLinkCreateParams.thetaStepSize;
    pObj->algLdInArgs.numHoughMaximasDet     = pObj->algLinkCreateParams.numHoughMaximasDet;
    pObj->algLdInArgs.numHoughMaximasTrack   = pObj->algLinkCreateParams.numHoughMaximasTrack;
    pObj->algLdInArgs.trackingMethod         = (LD_TI_TRACKMETHOD)pObj->algLinkCreateParams.trackingMethod;
    pObj->algLdInArgs.warningMethod          = (LD_TI_WARNING_INFO)pObj->algLinkCreateParams.warningMethod;
    pObj->algLdInArgs.departThetaLeftMin     = pObj->algLinkCreateParams.departThetaLeftMin;
    pObj->algLdInArgs.departThetaLeftMax     = pObj->algLinkCreateParams.departThetaLeftMax;
    pObj->algLdInArgs.departRhoLeftMin       = pObj->algLinkCreateParams.departRhoLeftMin;
    pObj->algLdInArgs.departRhoLeftMax       = pObj->algLinkCreateParams.departRhoLeftMax;
    pObj->algLdInArgs.departThetaRightMin    = pObj->algLinkCreateParams.departThetaRightMin;
    pObj->algLdInArgs.departThetaRightMax    = pObj->algLinkCreateParams.departThetaRightMax;
    pObj->algLdInArgs.departRhoRightMin      = pObj->algLinkCreateParams.departRhoRightMin;
    pObj->algLdInArgs.departRhoRightMax      = pObj->algLinkCreateParams.departRhoRightMax;

    memset(&pObj->algLdOutArgs, 0, sizeof(pObj->algLdOutArgs));
    pObj->algLdOutArgs.iVisionOutArgs.size         = sizeof(pObj->algLdOutArgs);

    memset(&pObj->algLdInBufDescImage, 0, sizeof(pObj->algLdInBufDescImage));
    pObj->algLdInBufDescImage.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algLdInBufDescImage.bufPlanes[0].buf                 = NULL;
    pObj->algLdInBufDescImage.bufPlanes[0].width               = inChInfo->pitch[0];
    pObj->algLdInBufDescImage.bufPlanes[0].height              = pObj->algLinkCreateParams.imgFrameHeight;
    pObj->algLdInBufDescImage.bufPlanes[0].frameROI.topLeft.x  = pObj->algLinkCreateParams.roiStartX;
    pObj->algLdInBufDescImage.bufPlanes[0].frameROI.topLeft.y  = pObj->algLinkCreateParams.roiStartY;
    pObj->algLdInBufDescImage.bufPlanes[0].frameROI.width      = pObj->algLinkCreateParams.roiWidth;
    pObj->algLdInBufDescImage.bufPlanes[0].frameROI.height     = pObj->algLinkCreateParams.roiHeight;
    pObj->algLdInBufDescImage.bufPlanes[0].planeType           = 0;
    pObj->algLdInBufDescImage.formatType                       = 0; /* NOT USED */
    pObj->algLdInBufDescImage.bufferId                         = 0xFF; /* NOT USED */

    memset(&pObj->algLdOutBufDescLanePoints, 0, sizeof(pObj->algLdOutBufDescLanePoints));
    pObj->algLdOutBufDescLanePoints.numPlanes                        = 1;
    /* Will be filled with output pointer later
     */
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].buf                 = NULL;
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].width               = LD_TI_MAXLANEPOINTS*sizeof(LD_TI_output);
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].height              = 1;
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].frameROI.width      = LD_TI_MAXLANEPOINTS*sizeof(LD_TI_output);
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].frameROI.height     = 1;
    pObj->algLdOutBufDescLanePoints.bufPlanes[0].planeType           = 0;
    pObj->algLdOutBufDescLanePoints.formatType                       = 0; /* NOT USED */
    pObj->algLdOutBufDescLanePoints.bufferId                         = 0xFF; /* NOT USED */

    pObj->algLdCreateParams.visionParams.algParams.size = sizeof(pObj->algLdCreateParams);
    pObj->algLdCreateParams.visionParams.cacheWriteBack = NULL;
    pObj->algLdCreateParams.maxImageWidth              = pObj->algLinkCreateParams.imgFrameWidth;
    pObj->algLdCreateParams.maxImageHeight             = pObj->algLinkCreateParams.imgFrameHeight;
    pObj->algLdCreateParams.maxRho                     = pObj->algLinkCreateParams.maxRho;

    pObj->algLdCreateParams.maxTheta                   = LD_TI_MAXNUMTHETA;
    pObj->algLdCreateParams.edma3RmLldHandle           = NULL;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for feature plane computation alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_laneDetectCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_LaneDetectObj                         * pAlgObj;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;
    AlgorithmLink_LaneDetectCreateParams                * pLinkCreateParams;

    pLinkCreateParams = (AlgorithmLink_LaneDetectCreateParams *) pCreateParams;


    pAlgObj = (AlgorithmLink_LaneDetectObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_LaneDetectObj),
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
            pLinkCreateParams,
            sizeof(AlgorithmLink_LaneDetectCreateParams)
           );

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    if(pAlgObj->algLinkCreateParams.isImgPmdInputType==FALSE)
    {
        status = System_linkGetInfo(
                        pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
                        &prevLinkInfo
                        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        UTILS_assert(prevLinkInfo.numQue >= 1);

        prevLinkQId = pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId;
        pAlgObj->inChInfo = prevLinkInfo.queInfo[prevLinkQId].chInfo[0];
    }
    else
    {
        /* input channel info for image pyramid input is not valid
         * hence fill with known values based on algLinkCreateParams
         */

        pAlgObj->inChInfo.flags = 0;

        pAlgObj->inChInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(
            pAlgObj->inChInfo.flags, SYSTEM_DF_YUV420SP_UV);

        pAlgObj->inChInfo.flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
            pAlgObj->inChInfo.flags, SYSTEM_SF_PROGRESSIVE);

        pAlgObj->inChInfo.flags = System_Link_Ch_Info_Set_Flag_Mem_Type(
            pAlgObj->inChInfo.flags, SYSTEM_MT_NONTILEDMEM);

        pAlgObj->inChInfo.flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
            pAlgObj->inChInfo.flags, SYSTEM_BUFFER_TYPE_METADATA);

        pAlgObj->inChInfo.startX = pAlgObj->algLinkCreateParams.imgFrameStartX;
        pAlgObj->inChInfo.startY = pAlgObj->algLinkCreateParams.imgFrameStartX;
        pAlgObj->inChInfo.width = pAlgObj->algLinkCreateParams.imgFrameWidth;
        pAlgObj->inChInfo.height = pAlgObj->algLinkCreateParams.imgFrameHeight;
        pAlgObj->inChInfo.pitch[0] = pAlgObj->algLinkCreateParams.imgFrameWidth;
        pAlgObj->inChInfo.pitch[1] = pAlgObj->algLinkCreateParams.imgFrameWidth;
    }

    if(System_Link_Ch_Info_Get_Flag_Data_Format(pAlgObj->inChInfo.flags)
            != SYSTEM_DF_YUV420SP_UV
       )
    {
        UTILS_assert(NULL);
    }

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

    AlgorithmLink_laneDetectAlgParamsInit(pAlgObj, &pAlgObj->inChInfo);

    pAlgObj->enableLD = TRUE;

    pAlgObj->algLdHandle = AlgIvision_create(
                        &LD_TI_VISION_FXNS,
                        (IALG_Params *)&pAlgObj->algLdCreateParams
                        );
    UTILS_assert(pAlgObj->algLdHandle!=NULL);

    if(pAlgObj->algLinkCreateParams.numOutBuffers
        > LANEDETECT_LINK_MAX_NUM_OUTPUT)
    {
        pAlgObj->algLinkCreateParams.numOutBuffers
            = LANEDETECT_LINK_MAX_NUM_OUTPUT;
    }

    pAlgObj->tmpBufSize = 4*1024*1024;
    pAlgObj->tmpBuf = Utils_memAlloc(
                                 UTILS_HEAPID_DDR_CACHED_SR,
                                 pAlgObj->tmpBufSize,
                                 128
                                 );
    UTILS_assert(pAlgObj->tmpBuf!=NULL);

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
            =  LANEDETECT_LINK_LANE_POINTS_BUF_SIZE;

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
        AlgorithmLink_getLinkId(pObj), "ALG_LANE_DETECT");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    return SYSTEM_LINK_STATUS_SOK;
}


Int32 AlgorithmLink_laneDetectProcess(void * pObj)
{
    UInt32 bufId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_LaneDetectObj * pAlgObj;
    System_BufferList inputBufList;
    AlgorithmLink_LaneDetectCreateParams * pLinkCreatePrms;
    System_Buffer * pSysOutBuffer;
    System_Buffer * pSysInBuffer;
    System_MetaDataBuffer * pOutMetaBuf;
    System_BufferList bufListReturn;
    System_LinkStatistics *linkStatsInfo;
    UInt8 *pInAddr;

    pAlgObj = (AlgorithmLink_LaneDetectObj *)
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
                AlgorithmLink_LaneDetectOutput *pLaneDetectOutput;

                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                pLaneDetectOutput = (AlgorithmLink_LaneDetectOutput*)pOutMetaBuf->bufAddr[0];

                if(pAlgObj->algLinkCreateParams.isImgPmdInputType==FALSE)
                {
                    System_VideoFrameBuffer *pInVideoBuf;

                    pInVideoBuf  = (System_VideoFrameBuffer *) pSysInBuffer->payload;

                    pInAddr = pInVideoBuf->bufAddr[0];
                }
                else
                {
                    System_MetaDataBuffer *pInMetaBuf;
                    AlgorithmLink_ImgPyramidFrameDesc *imgPmdFrameDescList;
                    AlgorithmLink_ImgPyramidFrameDesc *pInImgPmdFrameDesc;

                    pInMetaBuf  =
                        (System_MetaDataBuffer *) pSysInBuffer->payload;

                    Cache_inv(
                        pInMetaBuf->bufAddr[0],
                        pInMetaBuf->metaBufSize[0],
                        Cache_Type_ALLD,
                        TRUE
                        );

                    imgPmdFrameDescList =
                        (AlgorithmLink_ImgPyramidFrameDesc*)
                            pInMetaBuf->bufAddr[0];

                    pInImgPmdFrameDesc =
                        &imgPmdFrameDescList[
                            pAlgObj->algLinkCreateParams.imgPmdScaleIdx];

                    pInAddr = pInImgPmdFrameDesc->bufAddr[0];
                    pAlgObj->inChInfo.pitch[0] = pInImgPmdFrameDesc->pitch[0];
                }

                pAlgObj->algLdInBufDescImage.bufPlanes[0].width =
                    pAlgObj->inChInfo.pitch[0];

                pAlgObj->algLdInBufDescImage.bufPlanes[0].buf =
                    (Void*)( (UInt32)pInAddr
                                +
                            pAlgObj->algLinkCreateParams.imgFrameStartY*
                            pAlgObj->inChInfo.pitch[0]
                                +
                            pAlgObj->algLinkCreateParams.imgFrameStartX
                           )
                            ;

                pAlgObj->algLdOutBufDescLanePoints.bufPlanes[0].buf = (Void*)
                    (&pLaneDetectOutput->laneInfo[0]);

                Cache_inv(
                          pInAddr,
                          pAlgObj->inChInfo.pitch[0]*pAlgObj->inChInfo.height,
                          Cache_Type_ALLD,
                          TRUE
                        );

#ifndef ALG_DISABLE
                /* clear L2MEM, this is required to make sure the scratch memory
                 * for lane detect is set to known state before execution.
                 * When multiple algorithms run on same DSP, this memory
                 * could be filled by other algorithms
                 *
                 * NOTE: This workaround is specific to this algorithm
                 *       and is NOT a general rule to use for DSP programming.
                 */
                memset((void*)0x800000, 0, 24*1024);
#if !defined (LD_RESET)
                if(pAlgObj->enableLD)
                {
                    status = AlgIvision_process(
                                pAlgObj->algLdHandle,
                                &pAlgObj->algLdInBufs,
                                &pAlgObj->algLdOutBufs,
                                (IVISION_InArgs*)&pAlgObj->algLdInArgs,
                                (IVISION_OutArgs *)&pAlgObj->algLdOutArgs);
                }
#else
                status = AlgIvision_process(
                                pAlgObj->algLdHandle,
                                &pAlgObj->algLdInBufs,
                                &pAlgObj->algLdOutBufs,
                                (IVISION_InArgs*)&pAlgObj->algLdInArgs,
                                (IVISION_OutArgs *)&pAlgObj->algLdOutArgs);
#endif
                if(status!=IALG_EOK)
                {
                    Vps_printf(" ALG_LANEDETECT: ERROR: Alg process !!!\n");
                }
#else
                pAlgObj->algLdOutArgs.numLeftLanePoints = 0;
                pAlgObj->algLdOutArgs.numRightLanePoints = 0;
                pAlgObj->algLdOutArgs.infoFlag = 0;
#endif
                pLaneDetectOutput->numLeftLanePoints
                    = pAlgObj->algLdOutArgs.numLeftLanePoints;

                pLaneDetectOutput->numRightLanePoints
                    = pAlgObj->algLdOutArgs.numRightLanePoints;

                pLaneDetectOutput->laneCrossInfo
                    = pAlgObj->algLdOutArgs.infoFlag;

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

Int32 AlgorithmLink_laneDetectControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_LaneDetectObj* pAlgObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_LaneDetectAlgParams          *pLdPrms;

    pAlgObj = (AlgorithmLink_LaneDetectObj *)
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

        case ALGORITHM_LINK_LD_CMD_SET_PARAMS:
            if(pAlgLinkControlPrm->size != sizeof(AlgorithmLink_LaneDetectAlgParams))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pLdPrms = (AlgorithmLink_LaneDetectAlgParams *)
                                    pControlParams;

                if (pLdPrms->changeEnableLD == TRUE)
                {
                    pAlgObj->enableLD = pLdPrms->enableLD;
                }
#if defined(LD_RESET)
                if(pAlgObj->enableLD)
                {
                    pAlgObj->algLdInArgs.resetLDAlg = 0;
                }
                else
                {
                    pAlgObj->algLdInArgs.resetLDAlg = 1;
                }
#endif
                if(pLdPrms->enableAdvConfig)
                {
                    pAlgObj->algLdInArgs.cannyHighThresh       = pLdPrms->cannyHighThresh;
                    pAlgObj->algLdInArgs.cannyLowThresh        = pLdPrms->cannyLowThresh;
                    pAlgObj->algLdInArgs.houghNmsThresh        = pLdPrms->houghNmsThresh;
                    pAlgObj->algLdInArgs.startThetaLeft        = pLdPrms->startThetaLeft;
                    pAlgObj->algLdInArgs.endThetaLeft          = pLdPrms->endThetaLeft;
                    pAlgObj->algLdInArgs.startThetaRight       = pLdPrms->startThetaRight;
                    pAlgObj->algLdInArgs.endThetaRight         = pLdPrms->endThetaRight;
                    pAlgObj->algLdInArgs.thetaStepSize         = pLdPrms->thetaStepSize;
                    pAlgObj->algLdInArgs.numHoughMaximasDet    = pLdPrms->numHoughMaximasDet;
                    pAlgObj->algLdInArgs.numHoughMaximasTrack  = pLdPrms->numHoughMaximasTrack;
                    pAlgObj->algLdInArgs.trackingMethod        = pLdPrms->trackingMethod;
                    pAlgObj->algLdInArgs.warningMethod         = pLdPrms->warningMethod;
                    pAlgObj->algLdInArgs.departThetaLeftMin    = pLdPrms->departThetaLeftMin;
                    pAlgObj->algLdInArgs.departThetaLeftMax    = pLdPrms->departThetaLeftMax;
                    pAlgObj->algLdInArgs.departRhoLeftMin      = pLdPrms->departRhoLeftMin;
                    pAlgObj->algLdInArgs.departRhoLeftMax      = pLdPrms->departRhoLeftMax;
                    pAlgObj->algLdInArgs.departThetaRightMin   = pLdPrms->departThetaRightMin;
                    pAlgObj->algLdInArgs.departThetaRightMax   = pLdPrms->departThetaRightMax;
                    pAlgObj->algLdInArgs.departRhoRightMin     = pLdPrms->departRhoRightMin;
                    pAlgObj->algLdInArgs.departRhoRightMax     = pLdPrms->departRhoRightMax;
                }
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_laneDetectPrintStatistics(
                                                                pObj,
                                                                pAlgObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_laneDetectStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_laneDetectDelete(void * pObj)
{
    Int32 status;
    UInt32 bufId;
    AlgorithmLink_LaneDetectObj *pAlgObj;
    System_MetaDataBuffer              *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_LaneDetectObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status==0);

    /*
     * Free allocated memory for alg internal objects
     */
    status = AlgIvision_delete(pAlgObj->algLdHandle);
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

    status = Utils_memFree(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pAlgObj->tmpBuf,
                            pAlgObj->tmpBufSize
                           );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_memFree(
                       UTILS_HEAPID_DDR_CACHED_LOCAL,
                       pAlgObj,
                       sizeof(AlgorithmLink_LaneDetectObj)
                    );
    return status;

}

Int32 AlgorithmLink_laneDetectPrintStatistics(void *pObj,
                AlgorithmLink_LaneDetectObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
                            "ALG_LANE_DETECT",
                            TRUE);

    Utils_printLatency("ALG_LANE_DETECT",
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

