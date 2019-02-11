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
 * \file clrLink_algPlugin.c
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

#include "clrLink_priv.h"
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
Int32 AlgorithmLink_clr_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_clrCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_clrProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_clrControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_clrStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_clrDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_CLR;
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
Int32 AlgorithmLink_clrAlgParamsInit (
                                  AlgorithmLink_ClrObj *pObj,
                                  System_LinkChInfo *inChInfo
                                )
{
    UInt32 i;

    pObj->algClrInBufs.size    = sizeof(pObj->algClrInBufs);
    pObj->algClrInBufs.numBufs = 1;
    pObj->algClrInBufs.bufDesc = pObj->algClrInBufDesc;

    pObj->algClrInBufDesc[0]   = &pObj->algClrInBufDescImage;

    pObj->algClrOutBufs.size    = sizeof(pObj->algClrOutBufs);
    pObj->algClrOutBufs.numBufs = 1;
    pObj->algClrOutBufs.bufDesc = pObj->algClrOutBufDesc;

    pObj->algClrOutBufDesc[0]   = &pObj->algClrOutBufDescClrOut;

    memset(&pObj->algClrInArgs, 0, sizeof(pObj->algClrInArgs));
    pObj->algClrInArgs.iVisionInArgs.size         = sizeof(pObj->algClrInArgs);
    pObj->algClrInArgs.iVisionInArgs.subFrameInfo = 0;
    pObj->algClrInArgs.lightSelection           = TI_CLR_LSM_CUSTOM;
    pObj->algClrInArgs.lightBrightnessThr[0]    =  90;
    pObj->algClrInArgs.lightBrightnessThr[1]    = 100;
    pObj->algClrInArgs.lightColor[0]            = TI_CLR_PC_RED;
    pObj->algClrInArgs.lightColor[1]            = TI_CLR_PC_GREEN;
    pObj->algClrInArgs.lightThr1[0]             = 152;
    pObj->algClrInArgs.lightThr1[1]             = 113;
    pObj->algClrInArgs.lightThr2[0]             = 128;
    pObj->algClrInArgs.lightThr2[1]             = 143;
    pObj->algClrInArgs.falseFilterThr[0]        = 400;
    pObj->algClrInArgs.falseFilterThr[1]        = 400;
    pObj->algClrInArgs.numColors                = 2;
    pObj->algClrInArgs.numRadius                = 7;

    pObj->algClrInArgs.radius[0]                = 3;
    pObj->algClrInArgs.radius[1]                = 4;
    pObj->algClrInArgs.radius[2]                = 5;
    pObj->algClrInArgs.radius[3]                = 7;
    pObj->algClrInArgs.radius[4]                = 9;
    pObj->algClrInArgs.radius[5]                = 12;
    pObj->algClrInArgs.radius[6]                = 16;

    pObj->algClrInArgs.circleDetectionThr[0]    = 260;
    pObj->algClrInArgs.circleDetectionThr[1]    = 260;
    pObj->algClrInArgs.circleDetectionThr[2]    = 260;
    pObj->algClrInArgs.circleDetectionThr[3]    = 260;
    pObj->algClrInArgs.circleDetectionThr[4]    = 260;
    pObj->algClrInArgs.circleDetectionThr[5]    = 260;
    pObj->algClrInArgs.circleDetectionThr[6]    = 260;

    pObj->algClrInArgs.scalingFactor[0]         = 0;
    pObj->algClrInArgs.scalingFactor[1]         = 0;
    pObj->algClrInArgs.scalingFactor[2]         = 1;
    pObj->algClrInArgs.scalingFactor[3]         = 1;
    pObj->algClrInArgs.scalingFactor[4]         = 1;
    pObj->algClrInArgs.scalingFactor[5]         = 2;
    pObj->algClrInArgs.scalingFactor[6]         = 2;

    pObj->algClrInArgs.morphologyMethod         = 1;
    pObj->algClrInArgs.houghSpaceVotingMethod   = TI_CLR_HSV_GRAD_MAGNITUDE;
    pObj->algClrInArgs.groupingWindowSize       = 5;
    pObj->algClrInArgs.reserved                 = 0;

    memset(&pObj->algClrOutArgs, 0, sizeof(pObj->algClrOutArgs));
    pObj->algClrOutArgs.iVisionOutArgs.size         = sizeof(pObj->algClrOutArgs);

    memset(&pObj->algClrInBufDescImage, 0, sizeof(pObj->algClrInBufDescImage));
    pObj->algClrInBufDescImage.numPlanes                        = 2;
    /* Will be filled with input pointer later
     */
    pObj->algClrInBufDescImage.bufPlanes[0].buf                 = NULL;
    pObj->algClrInBufDescImage.bufPlanes[0].width               = inChInfo->pitch[0];
    pObj->algClrInBufDescImage.bufPlanes[0].height              = pObj->algLinkCreateParams.imgFrameHeight;
    pObj->algClrInBufDescImage.bufPlanes[0].frameROI.topLeft.x  = pObj->algLinkCreateParams.roiStartX;
    pObj->algClrInBufDescImage.bufPlanes[0].frameROI.topLeft.y  = pObj->algLinkCreateParams.roiStartY;
    pObj->algClrInBufDescImage.bufPlanes[0].frameROI.width      = pObj->algLinkCreateParams.roiWidth;
    pObj->algClrInBufDescImage.bufPlanes[0].frameROI.height     = pObj->algLinkCreateParams.roiHeight;
    pObj->algClrInBufDescImage.bufPlanes[0].planeType           = 0; // for Y
    pObj->algClrInBufDescImage.formatType                       = 0; /* NOT USED */
    pObj->algClrInBufDescImage.bufferId                         = 0xFF; /* NOT USED */

    pObj->algClrInBufDescImage.bufPlanes[1].buf                 = NULL;
    pObj->algClrInBufDescImage.bufPlanes[1].width               = inChInfo->pitch[1];
    pObj->algClrInBufDescImage.bufPlanes[1].height              = pObj->algLinkCreateParams.imgFrameHeight/2;
    pObj->algClrInBufDescImage.bufPlanes[1].frameROI.topLeft.x  = pObj->algLinkCreateParams.roiStartX;
    pObj->algClrInBufDescImage.bufPlanes[1].frameROI.topLeft.y  = pObj->algLinkCreateParams.roiStartY/2;
    pObj->algClrInBufDescImage.bufPlanes[1].frameROI.width      = pObj->algLinkCreateParams.roiWidth;
    pObj->algClrInBufDescImage.bufPlanes[1].frameROI.height     = pObj->algLinkCreateParams.roiHeight/2;
    pObj->algClrInBufDescImage.bufPlanes[1].planeType           = 1; // for C
    pObj->algClrInBufDescImage.formatType                       = 0; /* NOT USED */
    pObj->algClrInBufDescImage.bufferId                         = 0xFF; /* NOT USED */

    memset(&pObj->algClrOutBufDescClrOut, 0, sizeof(pObj->algClrOutBufDescClrOut));
    pObj->algClrOutBufDescClrOut.numPlanes                        = 1;
    /* Will be filled with output pointer later
     */
    pObj->algClrOutBufDescClrOut.bufPlanes[0].buf                 = NULL;
    pObj->algClrOutBufDescClrOut.bufPlanes[0].width               = sizeof(TI_CLR_output);
    pObj->algClrOutBufDescClrOut.bufPlanes[0].height              = 1;
    pObj->algClrOutBufDescClrOut.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algClrOutBufDescClrOut.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algClrOutBufDescClrOut.bufPlanes[0].frameROI.width      = sizeof(TI_CLR_output);
    pObj->algClrOutBufDescClrOut.bufPlanes[0].frameROI.height     = 1;
    pObj->algClrOutBufDescClrOut.bufPlanes[0].planeType           = 0;
    pObj->algClrOutBufDescClrOut.formatType                       = 0; /* NOT USED */
    pObj->algClrOutBufDescClrOut.bufferId                         = 0xFF; /* NOT USED */

    pObj->algClrCreateParams.visionParams.algParams.size = sizeof(pObj->algClrCreateParams);
    pObj->algClrCreateParams.visionParams.cacheWriteBack = NULL;
    pObj->algClrCreateParams.maxImageWidth              = pObj->algLinkCreateParams.imgFrameWidth;
    pObj->algClrCreateParams.maxImageHeight             = pObj->algLinkCreateParams.imgFrameHeight;
    pObj->algClrCreateParams.maxNumColors               = TI_CLR_MAX_NUM_COLOR_LIGHTS;
    pObj->algClrCreateParams.maxNumRadius               = 8;
    pObj->algClrCreateParams.minScalingFactor           = TI_CLR_HS_NO_SCALING;
    pObj->algClrCreateParams.trackingMethod             = TI_CLR_TRACKING_KALMAN;

    pObj->algClrCreateParams.maxRadius = 0;
    for (i =0 ; i < pObj->algClrInArgs.numRadius; i++)
    {
        if(pObj->algClrInArgs.radius[i] > pObj->algClrCreateParams.maxRadius)
        {
            pObj->algClrCreateParams.maxRadius = pObj->algClrInArgs.radius[i];
        }
    }

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
Int32 AlgorithmLink_clrCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_ClrObj                  * pAlgObj;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_ClrObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_ClrObj),
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

    prevLinkQId = pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId;
    pAlgObj->inChInfo = prevLinkInfo.queInfo[prevLinkQId].chInfo[0];

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

    AlgorithmLink_clrAlgParamsInit(pAlgObj, &pAlgObj->inChInfo);

    pAlgObj->algClrHandle = AlgIvision_create(
                        &TI_CLR_VISION_FXNS,
                        (IALG_Params *)&pAlgObj->algClrCreateParams
                        );
    UTILS_assert(pAlgObj->algClrHandle!=NULL);

    if(pAlgObj->algLinkCreateParams.numOutBuffers
        > CLR_LINK_MAX_NUM_OUTPUT)
    {
        pAlgObj->algLinkCreateParams.numOutBuffers
            = CLR_LINK_MAX_NUM_OUTPUT;
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
            =  CLR_LINK_OUT_BUF_SIZE;

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
        AlgorithmLink_getLinkId(pObj), "ALG_CLR");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    return SYSTEM_LINK_STATUS_SOK;
}

/* Adjust output co-ordinates based on ROI */
Void AlgorithmLink_clrAdjustOutputCoords(AlgorithmLink_ClrObj *pObj, TI_CLR_output *pClrOutput)
{
    UInt32 i, numObjs;
    TI_CLR_objectDescriptor *pObjDesc;

    numObjs = pClrOutput->numObjects;

    if (numObjs > 0 && numObjs <= TI_CLR_MAX_DETECTIONS_PER_FRAME)
    {
        for (i = 0; i < numObjs; i++)
        {
            pObjDesc = &pClrOutput->objDesc[i];

            pObjDesc->xPos += pObj->algLinkCreateParams.roiStartX;
            pObjDesc->yPos += pObj->algLinkCreateParams.roiStartY;
        }
    }
}

Int32 AlgorithmLink_clrProcess(void * pObj)
{
    UInt32 bufId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_ClrObj                  * pAlgObj;
    System_BufferList                                     inputBufList;
    AlgorithmLink_ClrCreateParams         * pLinkCreatePrms;
    System_Buffer                                       * pSysOutBuffer;
    System_Buffer                                       * pSysInBuffer;
    System_VideoFrameBuffer                             * pInVideoBuf;
    System_MetaDataBuffer                               * pOutMetaBuf;
    System_BufferList                                   bufListReturn;
    System_LinkStatistics *linkStatsInfo;

    pAlgObj = (AlgorithmLink_ClrObj *)
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
                TI_CLR_output *pClrOutput;

                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                pInVideoBuf  = (System_VideoFrameBuffer *) pSysInBuffer->payload;

                pClrOutput = (TI_CLR_output*)pOutMetaBuf->bufAddr[0];

                pAlgObj->algClrInBufDescImage.bufPlanes[0].buf =
                    (Void*)( (UInt32)pInVideoBuf->bufAddr[0]
                                +
                            pAlgObj->algLinkCreateParams.imgFrameStartY*
                            pAlgObj->inChInfo.pitch[0]
                                +
                            pAlgObj->algLinkCreateParams.imgFrameStartX
                           )
                            ;

                pAlgObj->algClrInBufDescImage.bufPlanes[1].buf =
                    (Void*)( (UInt32)pInVideoBuf->bufAddr[1]
                                +
                            pAlgObj->algLinkCreateParams.imgFrameStartY/2*
                            pAlgObj->inChInfo.pitch[1]
                                +
                            pAlgObj->algLinkCreateParams.imgFrameStartX
                           )
                            ;

                pAlgObj->algClrOutBufDescClrOut.bufPlanes[0].buf = (Void*)
                    (pClrOutput);

                Cache_inv(
                          pInVideoBuf->bufAddr[0],
                          pAlgObj->inChInfo.pitch[0]*pAlgObj->inChInfo.height,
                          Cache_Type_ALLD,
                          TRUE
                        );
                Cache_inv(
                          pInVideoBuf->bufAddr[1],
                          pAlgObj->inChInfo.pitch[1]*pAlgObj->inChInfo.height/2,
                          Cache_Type_ALLD,
                          TRUE
                        );
                #ifndef ALG_DISABLE

                #if 0
                Vps_printf(" ALG_CLR: Running .... !!!\n"
                    );
                #endif

                status = AlgIvision_process(
                                pAlgObj->algClrHandle,
                                &pAlgObj->algClrInBufs,
                                &pAlgObj->algClrOutBufs,
                                (IVISION_InArgs*)&pAlgObj->algClrInArgs,
                                (IVISION_OutArgs *)&pAlgObj->algClrOutArgs
                    );

                #if 0
                Vps_printf(" ALG_CLR: Done (%d objects) !!!\n", pClrOutput->numObjects);
                #endif

                #if 1
                if(status!=IALG_EOK)
                {
                    Vps_printf(" ALG_CLR: ERROR: Alg process !!!\n");
                }
                #endif
                #else
                pClrOutput->numObjects = 0;
                #endif

                AlgorithmLink_clrAdjustOutputCoords(pAlgObj, pClrOutput);

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

Int32 AlgorithmLink_clrControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_ClrObj                * pAlgObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;
    AlgorithmLink_ClrAlgParams          * pClrPrms;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgorithmLink_ClrObj *)
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
        case ALGORITHM_LINK_CLR_CMD_SET_PARAMS:
            if(pAlgLinkControlPrm->size != sizeof(AlgorithmLink_ClrAlgParams))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pClrPrms = (AlgorithmLink_ClrAlgParams *)
                                    pControlParams;

                pAlgObj->algClrInArgs.lightBrightnessThr[0]  = pClrPrms->lightBrightnessThr[0];
                pAlgObj->algClrInArgs.lightBrightnessThr[1]  = pClrPrms->lightBrightnessThr[1];
                pAlgObj->algClrInArgs.lightColor[0]          = pClrPrms->lightColor[0];
                pAlgObj->algClrInArgs.lightColor[1]          = pClrPrms->lightColor[1];
                pAlgObj->algClrInArgs.lightThr1[0]           = pClrPrms->lightThr1[0];
                pAlgObj->algClrInArgs.lightThr1[1]           = pClrPrms->lightThr1[1];
                pAlgObj->algClrInArgs.lightThr2[0]           = pClrPrms->lightThr2[0];
                pAlgObj->algClrInArgs.lightThr2[1]           = pClrPrms->lightThr2[1];
                pAlgObj->algClrInArgs.falseFilterThr[0]      = pClrPrms->falseFilterThr[0];
                pAlgObj->algClrInArgs.falseFilterThr[1]      = pClrPrms->falseFilterThr[1];
                pAlgObj->algClrInArgs.numRadius              = pClrPrms->numRadius;

                pAlgObj->algClrInArgs.radius[0]              = pClrPrms->radius[0];
                pAlgObj->algClrInArgs.radius[1]              = pClrPrms->radius[1];
                pAlgObj->algClrInArgs.radius[2]              = pClrPrms->radius[2];
                pAlgObj->algClrInArgs.radius[3]              = pClrPrms->radius[3];
                pAlgObj->algClrInArgs.radius[4]              = pClrPrms->radius[4];
                pAlgObj->algClrInArgs.radius[5]              = pClrPrms->radius[5];
                pAlgObj->algClrInArgs.radius[6]              = pClrPrms->radius[6];

                pAlgObj->algClrInArgs.circleDetectionThr[0]  = pClrPrms->circleDetectionThr[0];
                pAlgObj->algClrInArgs.circleDetectionThr[1]  = pClrPrms->circleDetectionThr[1];
                pAlgObj->algClrInArgs.circleDetectionThr[2]  = pClrPrms->circleDetectionThr[2];
                pAlgObj->algClrInArgs.circleDetectionThr[3]  = pClrPrms->circleDetectionThr[3];
                pAlgObj->algClrInArgs.circleDetectionThr[4]  = pClrPrms->circleDetectionThr[4];
                pAlgObj->algClrInArgs.circleDetectionThr[5]  = pClrPrms->circleDetectionThr[5];
                pAlgObj->algClrInArgs.circleDetectionThr[6]  = pClrPrms->circleDetectionThr[6];

                pAlgObj->algClrInArgs.scalingFactor[0]       = pClrPrms->scalingFactor[0];
                pAlgObj->algClrInArgs.scalingFactor[1]       = pClrPrms->scalingFactor[1];
                pAlgObj->algClrInArgs.scalingFactor[2]       = pClrPrms->scalingFactor[2];
                pAlgObj->algClrInArgs.scalingFactor[3]       = pClrPrms->scalingFactor[3];
                pAlgObj->algClrInArgs.scalingFactor[4]       = pClrPrms->scalingFactor[4];
                pAlgObj->algClrInArgs.scalingFactor[5]       = pClrPrms->scalingFactor[5];
                pAlgObj->algClrInArgs.scalingFactor[6]       = pClrPrms->scalingFactor[6];

                pAlgObj->algClrInArgs.morphologyMethod       = pClrPrms->morphologyMethod;
                pAlgObj->algClrInArgs.groupingWindowSize     = pClrPrms->groupingWindowSize;

                pAlgObj->algClrInBufDescImage.bufPlanes[0].frameROI.topLeft.x =
                    pAlgObj->algLinkCreateParams.roiStartX = pClrPrms->roiStartX;
                pAlgObj->algClrInBufDescImage.bufPlanes[0].frameROI.topLeft.y =
                    pAlgObj->algLinkCreateParams.roiStartY = pClrPrms->roiStartY;
                pAlgObj->algClrInBufDescImage.bufPlanes[0].frameROI.width     =
                    pAlgObj->algLinkCreateParams.roiWidth  = pClrPrms->roiWidth;
                pAlgObj->algClrInBufDescImage.bufPlanes[0].frameROI.height    =
                    pAlgObj->algLinkCreateParams.roiHeight = pClrPrms->roiHeight;


                pAlgObj->algClrInBufDescImage.bufPlanes[1].frameROI.topLeft.x =
                    pClrPrms->roiStartX;
                pAlgObj->algClrInBufDescImage.bufPlanes[1].frameROI.topLeft.y =
                    pClrPrms->roiStartY / 2U;
                pAlgObj->algClrInBufDescImage.bufPlanes[1].frameROI.width     =
                    pClrPrms->roiWidth;
                pAlgObj->algClrInBufDescImage.bufPlanes[1].frameROI.height    =
                    pClrPrms->roiHeight / 2U;
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_clrPrintStatistics(
                                                                pObj,
                                                                pAlgObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_clrStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_clrDelete(void * pObj)
{
    Int32 status;
    UInt32 bufId;
    AlgorithmLink_ClrObj *pAlgObj;
    System_MetaDataBuffer              *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_ClrObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status==0);

    /*
     * Free allocated memory for alg internal objects
     */
    status = AlgIvision_delete(pAlgObj->algClrHandle);
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
                       sizeof(AlgorithmLink_ClrObj)
                    );
    return status;

}

Int32 AlgorithmLink_clrPrintStatistics(void *pObj,
                AlgorithmLink_ClrObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
                            "ALG_CLR",
                            TRUE);

    Utils_printLatency("ALG_CLR",
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

