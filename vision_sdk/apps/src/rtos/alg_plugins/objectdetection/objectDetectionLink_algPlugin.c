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
 * \file featurePlaneCompLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for feature Plane computation
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

#include "objectDetectionLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>



#define OD_SOFT_CASCADE_THRESHOLD        (-8192)
#define OD_STRONG_CASCADE_THRESHOLD      (-8192)


/* uncomment below to disable calling of alg process API - used for debug ONLY */
/* #define ALG_DISABLE */


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
Int32 AlgorithmLink_ObjectDetection_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_objectDetectionCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_objectDetectionProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_objectDetectionControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_objectDetectionStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_objectDetectionDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_OBJECTDETECTION;
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
UInt32 AlgorithmLink_objectDetectionInitIOBuffers(
                                  AlgorithmLink_ObjectDetectionObj *pObj
                                )
{
    IVISION_InBufs  *pInBufs    = &pObj->inBufs;
    IVISION_OutBufs *pOutBufs   = &pObj->outBufs;
    UInt32 width;
    UInt32 height;
    TI_OD_CreateParams *pPrms = &pObj->algCreateParams;

    width   = pPrms->maxImageWidth;
    height  = pPrms->maxImageHeight;

    pInBufs->size       = sizeof(IVISION_InBufs);
    pOutBufs->size      = sizeof(IVISION_OutBufs);
    pInBufs->numBufs    = TI_OD_IN_BUFDESC_TOTAL;
    pOutBufs->numBufs   = TI_OD_OUT_BUFDESC_TOTAL;

    pInBufs->bufDesc[0]->numPlanes                          = 1;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pInBufs->bufDesc[0]->bufPlanes[0].width                 = 2*(width /4)*2;
    pInBufs->bufDesc[0]->bufPlanes[0].height                = 2*(height/4)*2*10;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = 2*(width /4)*2;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 2*(height/4)*2*10;
    pInBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;
    pInBufs->bufDesc[0]->bufPlanes[0].buf                   = NULL;

    pOutBufs->bufDesc[0]->numPlanes                          = 1;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pOutBufs->bufDesc[0]->bufPlanes[0].width                 =
        TI_OD_OUT_BUFDESC_LIST_SIZE;
    pOutBufs->bufDesc[0]->bufPlanes[0].height                = 1;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.width        =
        TI_OD_OUT_BUFDESC_LIST_SIZE;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 1;
    pOutBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;
    pOutBufs->bufDesc[0]->bufPlanes[0].buf                   = NULL;

    pOutBufs->bufDesc[1]->numPlanes                          = 1;
    pOutBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pOutBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pOutBufs->bufDesc[1]->bufPlanes[0].width                 =
        TI_OD_OUT_BUFDESC_LIST_SIZE;
    pOutBufs->bufDesc[1]->bufPlanes[0].height                = 1;
    pOutBufs->bufDesc[1]->bufPlanes[0].frameROI.width        =
        TI_OD_OUT_BUFDESC_LIST_SIZE;
    pOutBufs->bufDesc[1]->bufPlanes[0].frameROI.height       = 1;
    pOutBufs->bufDesc[1]->bufPlanes[0].planeType             = 0;
    pOutBufs->bufDesc[1]->bufPlanes[0].buf                   = NULL;

    return SYSTEM_LINK_STATUS_SOK;

}

Void AlgorithmLink_objectDetectionSetIOArgs(
                AlgorithmLink_ObjectDetectionObj *pObj
                )
{
    pObj->inArgs.iVisionInArgs.size = sizeof(IVISION_InArgs);

    pObj->inArgs.detectionMode = 0;
    pObj->inArgs.roiPreset = 0;
    pObj->inArgs.refreshInterval = 0;
    pObj->inArgs.reserved0 = 0;
    pObj->inArgs.reserved1 = 0;
    pObj->inArgs.reserved2 = 0;
    pObj->inArgs.reserved3 = 0;

    /*
     * PD - set config values
     */
    pObj->inArgs.pdConfig.enablePD              = pObj->algLinkCreateParams.enablePD;
    pObj->inArgs.pdConfig.detectorTypePD        = 0;
    pObj->inArgs.pdConfig.trackingMethodPD      = 1;
    pObj->inArgs.pdConfig.useExtWeightsPD       = 0;
    pObj->inArgs.pdConfig.softCascadeThPD       = -1;
    pObj->inArgs.pdConfig.strongCascadeThPD     = -1;

    /*
     * TSR - set config values
     */
    pObj->inArgs.tsrConfig.enableTSR            = pObj->algLinkCreateParams.enableTSR;
    pObj->inArgs.tsrConfig.detectorTypeTSR      = 0;
    pObj->inArgs.tsrConfig.trackingMethodTSR    = 2;
    pObj->inArgs.tsrConfig.recognitionMethodTSR = 0;
    pObj->inArgs.tsrConfig.useExtWeightsTSR     = 0;
    pObj->inArgs.tsrConfig.softCascadeThTSR     = -2;
    pObj->inArgs.tsrConfig.strongCascadeThTSR   = -2;

    /*
     * VD - set config values
     */
    pObj->inArgs.vdConfig.enableVD              = pObj->algLinkCreateParams.enableVD;
    pObj->inArgs.vdConfig.detectorTypeVD        = 0;
    pObj->inArgs.vdConfig.trackingMethodVD      = 1;
    pObj->inArgs.vdConfig.useExtWeightsVD       = 0;
    pObj->inArgs.vdConfig.softCascadeThVD       = -1;
    pObj->inArgs.vdConfig.strongCascadeThVD     = -1;

    pObj->outArgs.iVisionOutArgs.size   = sizeof(IVISION_OutArgs);
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
Int32 AlgorithmLink_objectDetectionCreate(void * pObj,void * pCreateParams)
{
    UInt32 numInputQUsed;
    UInt32 numOutputQUsed;
    UInt32 numChannelsUsed;
    UInt32 channelId;
    UInt32 status;
    UInt32 bufId;
    AlgorithmLink_ObjectDetectionObj                   * pObjectDetectObj;
    TI_OD_CreateParams                                 * pAlgCreateParams;
    AlgorithmLink_ObjectDetectionCreateParams          * pLinkCreateParams;
    AlgorithmLink_OutputQueueInfo                           * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                            * pInputQInfo;
    System_LinkInfo                                           prevLinkInfo;
    System_LinkChInfo                                       * pOutChInfo;
    System_Buffer                                           * pSystemBuffer;
    System_MetaDataBuffer                                   * pMetaDataBuffer;


    pObjectDetectObj = (AlgorithmLink_ObjectDetectionObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_ObjectDetectionObj), 32);
    UTILS_assert(pObjectDetectObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pObjectDetectObj);

    pAlgCreateParams  = &pObjectDetectObj->algCreateParams;
    pLinkCreateParams = (AlgorithmLink_ObjectDetectionCreateParams *)
                         pCreateParams;
    pInputQInfo       = &pObjectDetectObj->inputQInfo;
    pOutputQInfo      = &pObjectDetectObj->outputQInfo;
    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pObjectDetectObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_ObjectDetectionCreateParams)
           );
    /*
     * Populating parameters corresponding to Q usage of geometric alignment
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = 1;
    numChannelsUsed             = 1;
    channelId                   = 0;

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->queInfo.numCh = numChannelsUsed;

    status = System_linkGetInfo(
                                  pLinkCreateParams->inQueParams.prevLinkId,
                                  &prevLinkInfo
                                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= numInputQUsed);

    channelId           = 0;
    pOutChInfo          = &pOutputQInfo->queInfo.chInfo[channelId];
    pOutChInfo->flags   = 0;

    pOutChInfo->width   = pLinkCreateParams->imgFrameWidth;
    pOutChInfo->height  = pLinkCreateParams->imgFrameHeight;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(
                                    pObj,
                                    numInputQUsed,
                                    pInputQInfo,
                                    numOutputQUsed,
                                    pOutputQInfo
                               );

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */


    pAlgCreateParams->visionParams.algParams.size = sizeof(IVISION_Params);

    pAlgCreateParams->edma3RmLldHandle  = NULL;
    pAlgCreateParams->maxImageWidth     = pOutChInfo->width;
    pAlgCreateParams->maxImageHeight    = pOutChInfo->height;
    pAlgCreateParams->maxScales         = TI_OD_MAX_TOTAL_SCALES;

    pObjectDetectObj->handle = AlgIvision_create(
                                &TI_OD_VISION_FXNS,
                                (IALG_Params*)pAlgCreateParams
                                );
    UTILS_assert(pObjectDetectObj->handle!=NULL);

    pObjectDetectObj->inBufs.bufDesc  = pObjectDetectObj->inBufDescList;
    pObjectDetectObj->outBufs.bufDesc = pObjectDetectObj->outBufDescList;

    pObjectDetectObj->inBufDescList[TI_OD_IN_BUFDESC_FEATURE_PLANES]  = &pObjectDetectObj->inBufDesc;
    pObjectDetectObj->outBufDescList[TI_OD_OUT_BUFDESC_OBJECT_LIST]       = &pObjectDetectObj->outBufDesc[0];
    pObjectDetectObj->outBufDescList[TI_OD_OUT_BUFDESC_DETECTION_LIST]       = &pObjectDetectObj->outBufDesc[1];

    /*
     * Initialize input output buffers
     */
    AlgorithmLink_objectDetectionInitIOBuffers(pObjectDetectObj);


    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */

    pObjectDetectObj->outBufferSize = sizeof(AlgorithmLink_ObjectDetectionOutput);

    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer       =   &pObjectDetectObj->buffers[bufId];
        pMetaDataBuffer     =   &pObjectDetectObj->odOutput[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pMetaDataBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =   0;

        pMetaDataBuffer->numMetaDataPlanes  =   1;
        pMetaDataBuffer->metaBufSize[0]     =   pObjectDetectObj->outBufferSize;
        pMetaDataBuffer->metaFillLength[0]  =   pObjectDetectObj->outBufferSize;
        pMetaDataBuffer->bufAddr[0]         =   Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pObjectDetectObj->outBufferSize,
                                                    ALGORITHMLINK_FRAME_ALIGN
                                                    );
        UTILS_assert(pMetaDataBuffer->bufAddr[0] != NULL);
        pMetaDataBuffer->flags = 0;

        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }

    pObjectDetectObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_OBJECT_DETECT");
    UTILS_assert(NULL != pObjectDetectObj->linkStatsInfo);

    pObjectDetectObj->isFirstFrameRecv    = FALSE;

    AlgorithmLink_objectDetectionSetIOArgs(pObjectDetectObj);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmLink_objectDetectionProcess(void * pObj)
{
    UInt32 bufId;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_ObjectDetectionObj          * pObjectDetectObj;
    System_BufferList                         inputBufList;
    AlgorithmLink_ObjectDetectionCreateParams * pLinkCreateParams;
    System_Buffer                             * pSysOutBuffer;
    System_Buffer                             * pSysInBuffer;
    System_MetaDataBuffer                     * pMetaDataInBuffer;
    System_MetaDataBuffer                     * pMetaDataOutBuffer;
    IVISION_InBufs                            * pInBufs;
    IVISION_OutBufs                           * pOutBufs;
    System_BufferList                         outputBufListReturn;
    System_BufferList                         inputBufListReturn;
    System_LinkStatistics                     * linkStatsInfo;
    AlgorithmLink_ObjectDetectionOutput       *pOdOutput;


    pObjectDetectObj = (AlgorithmLink_ObjectDetectionObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pObjectDetectObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pLinkCreateParams = &pObjectDetectObj->algLinkCreateParams;

    pInBufs  = &pObjectDetectObj->inBufs;
    pOutBufs = &pObjectDetectObj->outBufs;

    if (pObjectDetectObj->isFirstFrameRecv == FALSE)
    {
        pObjectDetectObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                        pLinkCreateParams->inQueParams.prevLinkId,
                        pLinkCreateParams->inQueParams.prevLinkQueId,
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

            if(pObjectDetectObj->algLinkCreateParams.enablePD==FALSE
                &&
               pObjectDetectObj->algLinkCreateParams.enableTSR==FALSE
                &&
               pObjectDetectObj->algLinkCreateParams.enableVD==FALSE
               )
            {
                 linkStatsInfo->linkStats.chStats
                                [0].inBufDropCount++;
            }
            else
            {
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

                    /*
                     * Get meta data frame buffer out of the system Buffer for both
                     * input and output buffers.
                     * Associate the input/output buffer pointers with inBufs
                     * and outBufs
                     * Record the bufferId with the address of the System Buffer
                     */
                    pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                    pSysOutBuffer->frameId = pSysInBuffer->frameId;
                    pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                    pMetaDataInBuffer    = (System_MetaDataBuffer *)pSysInBuffer->payload;
                    pMetaDataOutBuffer   = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                    pOdOutput = (AlgorithmLink_ObjectDetectionOutput*)pMetaDataOutBuffer->bufAddr[0];

                    pInBufs->bufDesc[0]->bufPlanes[0].buf = pMetaDataInBuffer->bufAddr[0];

                    pOutBufs->bufDesc[0]->bufPlanes[0].buf = &pOdOutput->objectList;
                    pOutBufs->bufDesc[1]->bufPlanes[0].buf = &pOdOutput->detectionList;

                    pInBufs->bufDesc[0]->bufferId   = (UInt32)pSysInBuffer;

                    pObjectDetectObj->inArgs.pdConfig.enablePD
                        = pObjectDetectObj->algLinkCreateParams.enablePD;
                    pObjectDetectObj->inArgs.tsrConfig.enableTSR
                        = pObjectDetectObj->algLinkCreateParams.enableTSR;
                    pObjectDetectObj->inArgs.vdConfig.enableVD
                        = pObjectDetectObj->algLinkCreateParams.enableVD;

                    Cache_inv(pMetaDataInBuffer->bufAddr[0],
                              pMetaDataInBuffer->metaBufSize[0],
                              Cache_Type_ALLD,
                              TRUE
                             );

                    #ifdef ALG_DISABLE
                    /* disable algorithm processing, used for debug
                     * set output as if no object are detected
                     */
                    status = IALG_EOK;
                    pOdOutput->objectList.numObjects = 0;
                    pOdOutput->detectionList.numObjects = 0;
                    #else
                    {
                        TI_OD_InArgs  * pInArgs;
                        TI_OD_OutArgs * pOutArgs;

                        pInArgs  = &pObjectDetectObj->inArgs;
                        pOutArgs = &pObjectDetectObj->outArgs;

                        #if 0
                        Vps_printf(" ALG_OBJECT_DETECT: PD = %d, TSR = %d, VD = %d !!!\n",
                            pObjectDetectObj->inArgs.pdConfig.enablePD,
                            pObjectDetectObj->inArgs.tsrConfig.enableTSR,
                            pObjectDetectObj->inArgs.vdConfig.enableVD
                            );
                        #endif

                        status = AlgIvision_process(
                                                 (IVISION_Handle)pObjectDetectObj->handle,
                                                 pInBufs,
                                                 pOutBufs,
                                                 (IVISION_InArgs *)pInArgs,
                                                 (IVISION_OutArgs *)pOutArgs
                                                );

                        #if 0
                        {
                            TI_OD_outputList *pObjectDataOutput;
                            TI_OD_objectDescriptor *pObjectDataDesc;

                            int i;

                            pObjectDataOutput = &pOdOutput->objectList;

                            Vps_printf(" ALG_OBJECT_DETECT: Objects = %d !!!\n",
                                pObjectDataOutput->numObjects
                                );
                            for (i = 0; i < pObjectDataOutput->numObjects; i++)
                            {
                                pObjectDataDesc = &pObjectDataOutput->objDesc[i];

                                Vps_printf(" ALG_OBJECT_DETECT: #%d: Tag=%d, Type=%d, SubType=%d, Score=%f, Scale=%f, (%d, %d : %d x %d)\n",
                                    i,
                                    pObjectDataDesc->objTag,
                                    pObjectDataDesc->objType,
                                    pObjectDataDesc->objSubType,
                                    pObjectDataDesc->objScore,
                                    pObjectDataDesc->objScale,
                                    pObjectDataDesc->xPos,
                                    pObjectDataDesc->yPos,
                                    pObjectDataDesc->objWidth,
                                    pObjectDataDesc->objHeight
                                    );
                            }
                        }
                        #endif
                    }
                    #endif

                   Cache_wb(pMetaDataOutBuffer->bufAddr[0],
                           pMetaDataOutBuffer->metaBufSize[0],
                           Cache_Type_ALLD,
                           TRUE
                            );

                   if (status != IALG_EOK)
                   {
                        UTILS_assert(NULL);
                   }
                   else
                   {
                       Utils_updateLatency(&linkStatsInfo->linkLatency,
                                            pSysOutBuffer->linkLocalTimestamp);
                       Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                            pSysOutBuffer->srcTimestamp);

                       linkStatsInfo->linkStats.chStats
                                        [0].inBufProcessCount++;
                       linkStatsInfo->linkStats.chStats
                                        [0].outBufCount[0]++;

                       /*
                        * <TODO For Now not handling locking of output buffers
                        *  case >
                        */
                       status = AlgorithmLink_putFullOutputBuffer(
                                                        pObj,
                                                        0,
                                                        pSysOutBuffer);
                       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                       /*
                        * Informing next link that a new data has peen put for its
                        * processing
                        */
                       System_sendLinkCmd(
                              pLinkCreateParams->outQueParams.nextLink,
                              SYSTEM_CMD_NEW_DATA,
                              NULL);
                       /*
                        * Releasing (Free'ing) output buffers, since algorithm
                        * does not need it for any future usage.
                        */
                       outputBufListReturn.numBuf = 1;
                       outputBufListReturn.buffers[0] = pSysOutBuffer;

                       AlgorithmLink_releaseOutputBuffer(
                                                          pObj,
                                                          0,
                                                          &outputBufListReturn
                                                          );

                   }
                }
            }
            inputBufListReturn.numBuf = 1;
            inputBufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                              pObj,
                              0,
                              pLinkCreateParams->inQueParams.prevLinkId,
                              pLinkCreateParams->inQueParams.prevLinkQueId,
                              &inputBufListReturn,
                              &bufDropFlag);
        }
    }
    return status;
}

Int32 AlgorithmLink_objectDetectionControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_ObjectDetectionObj* pObjectDetectObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;
    AlgorithmLink_ObjectDetectEnableAlgParams *pEnableAlg;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pObjectDetectObj = (AlgorithmLink_ObjectDetectionObj *)
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
        case ALGORITHM_LINK_OBJECT_DETECT_CMD_ENABLE_ALG:

            if(pAlgLinkControlPrm->size != sizeof(*pEnableAlg))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pEnableAlg = (AlgorithmLink_ObjectDetectEnableAlgParams *)
                                    pControlParams;

                pObjectDetectObj->algLinkCreateParams.enablePD
                    = pEnableAlg->enablePD;

                pObjectDetectObj->algLinkCreateParams.enableTSR
                    = pEnableAlg->enableTSR;

                pObjectDetectObj->algLinkCreateParams.enableVD
                    = pEnableAlg->enableVD;

                if(pEnableAlg->enableAdvConfig)
                {
                    pObjectDetectObj->inArgs.pdConfig.detectorTypePD
                        = pEnableAlg->detectorTypePD;
                    pObjectDetectObj->inArgs.pdConfig.trackingMethodPD
                        = pEnableAlg->trackingMethodPD;
                    pObjectDetectObj->inArgs.pdConfig.softCascadeThPD
                        = pEnableAlg->softCascadeThPD;
                    pObjectDetectObj->inArgs.pdConfig.strongCascadeThPD
                        = pEnableAlg->strongCascadeThPD;

                    pObjectDetectObj->inArgs.tsrConfig.detectorTypeTSR
                        = pEnableAlg->detectorTypeTSR;
                    pObjectDetectObj->inArgs.tsrConfig.trackingMethodTSR
                        = pEnableAlg->trackingMethodTSR;
                    pObjectDetectObj->inArgs.tsrConfig.recognitionMethodTSR
                        = pEnableAlg->recognitionMethodTSR;
                    pObjectDetectObj->inArgs.tsrConfig.softCascadeThTSR
                        = pEnableAlg->softCascadeThTSR;
                    pObjectDetectObj->inArgs.tsrConfig.strongCascadeThTSR
                        = pEnableAlg->strongCascadeThTSR;

                    pObjectDetectObj->inArgs.vdConfig.detectorTypeVD
                        = pEnableAlg->detectorTypeVD;
                    pObjectDetectObj->inArgs.vdConfig.trackingMethodVD
                        = pEnableAlg->trackingMethodVD;
                    pObjectDetectObj->inArgs.vdConfig.softCascadeThVD
                        = pEnableAlg->softCascadeThVD;
                    pObjectDetectObj->inArgs.vdConfig.strongCascadeThVD
                        = pEnableAlg->strongCascadeThVD;
                }
            }
            break;
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_objectDetectionPrintStatistics(
                                                             pObj,
                                                             pObjectDetectObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_objectDetectionStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_objectDetectionDelete(void * pObj)
{
    UInt32 status;
    UInt32 bufId;
    AlgorithmLink_ObjectDetectionObj                   * pObjectDetectObj;
    AlgorithmLink_ObjectDetectionCreateParams          * pLinkCreateParams;
    System_MetaDataBuffer                                   * pMetaDataBuffer;

    pObjectDetectObj = (AlgorithmLink_ObjectDetectionObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pObjectDetectObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pObjectDetectObj->linkStatsInfo);
    UTILS_assert(status==0);

    status = AlgIvision_delete(pObjectDetectObj->handle);
    UTILS_assert(status==0);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pMetaDataBuffer     =   &pObjectDetectObj->odOutput[bufId];


        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pMetaDataBuffer->bufAddr[0],
                                pMetaDataBuffer->metaBufSize[0]
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

   Utils_memFree(
                   UTILS_HEAPID_DDR_CACHED_LOCAL,
                   pObjectDetectObj,
                   sizeof(AlgorithmLink_ObjectDetectionObj)
                );

    return status;
}

Int32 AlgorithmLink_objectDetectionPrintStatistics(void *pObj,
                AlgorithmLink_ObjectDetectionObj *pObjectDetectionObj)
{
    UTILS_assert(NULL != pObjectDetectionObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObjectDetectionObj->linkStatsInfo->linkStats,
                            "ALG_OBJECT_DETECT",
                            TRUE);

    Utils_printLatency("ALG_OBJECT_DETECT",
                       &pObjectDetectionObj->linkStatsInfo->linkLatency,
                       &pObjectDetectionObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/*
int _TSC_read()
{
    return 0;
}
*/

