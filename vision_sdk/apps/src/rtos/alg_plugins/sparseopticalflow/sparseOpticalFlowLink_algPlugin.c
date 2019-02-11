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
 * \version 0.1 (Jan 2016):  [Mueller]
 *     Modifications for 3D Perception usecase:
 *     - Copy ErrEst to output buffer's plane 2
 *     - Pull out several algorithm parameters from algplugin to usecase level
 *     - Enable input type VideoFrame or CompositeFrameBuffer
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "sparseOpticalFlowLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

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
Int32 AlgorithmLink_sparseOpticalFlow_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_sparseOpticalFlowCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_sparseOpticalFlowProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_sparseOpticalFlowControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_sparseOpticalFlowStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_sparseOpticalFlowDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_SPARSE_OPTICAL_FLOW;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}
/**
 *******************************************************************************
 *
 * \brief This function allocates memory for the algorithm internal objects
 *
 *
 * \param  numMemRec         [IN] Number of objects
 * \param  memRec            [IN] pointer to the memory records
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
UInt32 AlgorithmLink_sparseOpticalFlowAlgCreate(
                                       AlgorithmLink_SparseOpticalFlowChObj *pObj)
{
    /*
     * Intialize the algorithm instance with the alocated memory
     * and user create parameters
     */
    pObj->algSofHandle = AlgIvision_create(
                            &SOF_TI_VISION_FXNS,
                            (IALG_Params*)&pObj->algSofCreateParams
                            );
    UTILS_assert(pObj->algSofHandle!=NULL);

    pObj->algSofOutBufSizeKeyPoints     =
        pObj->algSofCreateParams.maxNumKeyPoints
        *
        sizeof(UInt16)
        *
        4
        ;

    pObj->algSofOutBufSizeErrEst        =
        pObj->algSofCreateParams.maxNumKeyPoints
        *
        sizeof(UInt16)
        ;

    pObj->algSofOutBufSizeTrackedPoints =
        SOF_ALGLINK_FLOW_TRACK_POINTS_BUF_SIZE
        ;

    pObj->pAlgSofOutBufKeyPoints =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->algSofOutBufSizeKeyPoints,
            128
          );
    UTILS_assert(pObj->pAlgSofOutBufKeyPoints!=NULL);

    pObj->pAlgSofOutBufErrEst =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->algSofOutBufSizeErrEst,
            128
          );
    UTILS_assert(pObj->pAlgSofOutBufErrEst!=NULL);

    pObj->pAlgSofOutBufTrackedPoints =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->algSofOutBufSizeTrackedPoints,
            128
          );
    UTILS_assert(pObj->pAlgSofOutBufTrackedPoints!=NULL);

    pObj->algSofOutBufDescKeyPoints.bufPlanes[0].buf
        = pObj->pAlgSofOutBufKeyPoints;
    pObj->algSofOutBufDescErrEst.bufPlanes[0].buf
        = pObj->pAlgSofOutBufErrEst;
    pObj->algSofOutBufDescTrackedPoints.bufPlanes[0].buf
        = pObj->pAlgSofOutBufTrackedPoints;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function frees memory for the algorithm internal objects
 *
 *
 * \param  numMemRec         [IN] Number of objects
 * \param  memRec            [IN] pointer to the memory records
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
UInt32 AlgorithmLink_sparseOpticalFlowAlgDelete(
                                      AlgorithmLink_SparseOpticalFlowChObj *pObj)
{
    Int32 status;

    status = AlgIvision_delete(pObj->algSofHandle);
    UTILS_assert(status==0);

    status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->pAlgSofOutBufKeyPoints,
            pObj->algSofOutBufSizeKeyPoints
          );
    UTILS_assert(status==0);

    status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->pAlgSofOutBufErrEst,
            pObj->algSofOutBufSizeErrEst
          );
    UTILS_assert(status==0);

    status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->pAlgSofOutBufTrackedPoints,
            pObj->algSofOutBufSizeTrackedPoints
          );
    UTILS_assert(status==0);

    return status;
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
Int32 AlgorithmLink_sparseOpticalFlowAlgParamsInit (
                                  AlgorithmLink_SparseOpticalFlowObj *pLinkObj,
                                  AlgorithmLink_SparseOpticalFlowChObj *pObj,
                                  System_LinkChInfo *inChInfo
                                )
{
    UInt32 i;

    pObj->algSofInBufs.size    = sizeof(pObj->algSofInBufs);
    pObj->algSofInBufs.numBufs = 2;
    pObj->algSofInBufs.bufDesc = pObj->algSofInBufDesc;

    pObj->algSofInBufDesc[0]   = &pObj->algSofInBufDescImage;
    pObj->algSofInBufDesc[1]   = &pObj->algSofInBufDescKeyPoints;

    pObj->algSofOutBufs.size    = sizeof(pObj->algSofOutBufs);
    pObj->algSofOutBufs.numBufs = 3;
    pObj->algSofOutBufs.bufDesc = pObj->algSofOutBufDesc;

    pObj->algSofOutBufDesc[0]   = &pObj->algSofOutBufDescKeyPoints;
    pObj->algSofOutBufDesc[1]   = &pObj->algSofOutBufDescErrEst;
    pObj->algSofOutBufDesc[2]   = &pObj->algSofOutBufDescTrackedPoints;

    memset(&pObj->algSofInArgs, 0, sizeof(pObj->algSofInArgs));
    pObj->algSofInArgs.iVisionInArgs.size         = sizeof(pObj->algSofInArgs);
    pObj->algSofInArgs.iVisionInArgs.subFrameInfo = 0;
    pObj->algSofInArgs.numCorners                 = 0;
    pObj->algSofInArgs.trackErrThr                = pLinkObj->algLinkCreateParams.trackErrThr;
    pObj->algSofInArgs.trackMinFlowQ4             = pLinkObj->algLinkCreateParams.trackMinFlowQ4;
    pObj->algSofInArgs.trackNmsWinSize            = pLinkObj->algLinkCreateParams.trackNmsWinSize;
    pObj->algSofInArgs.reservered0                = 0;
    pObj->algSofInArgs.staticFrame                = 0;

    memset(&pObj->algSofOutArgs, 0, sizeof(pObj->algSofOutArgs));
    pObj->algSofOutArgs.iVisionOutArgs.size         = sizeof(pObj->algSofOutArgs);

    memset(&pObj->algSofInBufDescImage, 0, sizeof(pObj->algSofInBufDescImage));
    pObj->algSofInBufDescImage.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algSofInBufDescImage.bufPlanes[0].buf                 = NULL;
    pObj->algSofInBufDescImage.bufPlanes[0].width               = inChInfo->pitch[0];
    pObj->algSofInBufDescImage.bufPlanes[0].height              = inChInfo->height;
    if(pLinkObj->algLinkCreateParams.enableRoi)
    {
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.topLeft.x  = pLinkObj->algLinkCreateParams.roiStartX;
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.topLeft.y  = pLinkObj->algLinkCreateParams.roiStartY;
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.width      = pLinkObj->algLinkCreateParams.roiWidth;
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.height     = pLinkObj->algLinkCreateParams.roiHeight;
    }
    else
    {
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.topLeft.x  = pLinkObj->algLinkCreateParams.imgFrameStartX;
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.topLeft.y  = pLinkObj->algLinkCreateParams.imgFrameStartY;
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.width      = pLinkObj->algLinkCreateParams.imgFrameWidth;
        pObj->algSofInBufDescImage.bufPlanes[0].frameROI.height     = pLinkObj->algLinkCreateParams.imgFrameHeight;
    }
    pObj->algSofInBufDescImage.formatType                       = 0; /* NOT USED */
    pObj->algSofInBufDescImage.bufferId                         = 0xFF; /* NOT USED */

    memset(&pObj->algSofInBufDescKeyPoints, 0, sizeof(pObj->algSofInBufDescKeyPoints));
    pObj->algSofInBufDescKeyPoints.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algSofInBufDescKeyPoints.bufPlanes[0].buf                 = NULL;

    memset(&pObj->algSofOutBufDescKeyPoints, 0, sizeof(pObj->algSofOutBufDescKeyPoints));
    pObj->algSofOutBufDescKeyPoints.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algSofOutBufDescKeyPoints.bufPlanes[0].buf                 = NULL;

    memset(&pObj->algSofOutBufDescErrEst, 0, sizeof(pObj->algSofOutBufDescErrEst));
    pObj->algSofOutBufDescErrEst.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algSofOutBufDescErrEst.bufPlanes[0].buf                 = NULL;

    memset(&pObj->algSofOutBufDescTrackedPoints, 0, sizeof(pObj->algSofOutBufDescTrackedPoints));
    pObj->algSofOutBufDescTrackedPoints.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algSofOutBufDescTrackedPoints.bufPlanes[0].buf                 = NULL;

    pObj->algSofCreateParams.visionParams.algParams.size = sizeof(pObj->algSofCreateParams);
    pObj->algSofCreateParams.visionParams.cacheWriteBack = NULL;
    pObj->algSofCreateParams.imWidth                     = inChInfo->pitch[0];
    pObj->algSofCreateParams.imHeight                    = inChInfo->height;

    if(pLinkObj->algLinkCreateParams.enableRoi)
    {
        pObj->algSofCreateParams.roiWidth   = pLinkObj->algLinkCreateParams.roiWidth;
        pObj->algSofCreateParams.roiHeight  = pLinkObj->algLinkCreateParams.roiHeight;
        pObj->algSofCreateParams.startX     = pLinkObj->algLinkCreateParams.roiStartX;
        pObj->algSofCreateParams.startY     = pLinkObj->algLinkCreateParams.roiStartY;
    }
    else
    {
        pObj->algSofCreateParams.roiWidth
            = SystemUtils_floor(
                    pLinkObj->algLinkCreateParams.imgFrameWidth - SOF_ALGLINK_PAD_PIXELS*2,
                    SOF_ALGLINK_PAD_PIXELS);
        pObj->algSofCreateParams.roiHeight
            = SystemUtils_floor(
                    pLinkObj->algLinkCreateParams.imgFrameHeight - SOF_ALGLINK_PAD_PIXELS*2,
                    SOF_ALGLINK_PAD_PIXELS);
        pObj->algSofCreateParams.startX = pLinkObj->algLinkCreateParams.imgFrameStartX + SOF_ALGLINK_PAD_PIXELS;
        pObj->algSofCreateParams.startY = pLinkObj->algLinkCreateParams.imgFrameStartY + SOF_ALGLINK_PAD_PIXELS;
    }

    UTILS_assert(pLinkObj->algLinkCreateParams.numLevels < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.numLevels                   = pLinkObj->algLinkCreateParams.numLevels;
    if(pObj->algSofCreateParams.imHeight < 300)
    {
        pObj->algSofCreateParams.numLevels               = 3;
    }

    UTILS_assert(pLinkObj->algLinkCreateParams.keyPointDetectMethod < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.keyPointDetectMethod        = pLinkObj->algLinkCreateParams.keyPointDetectMethod;
    UTILS_assert(pLinkObj->algLinkCreateParams.keyPointDetectInterval < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.keyPointDetectInterval      = pLinkObj->algLinkCreateParams.keyPointDetectInterval;
    pObj->algSofCreateParams.maxNumKeyPoints             = pLinkObj->algLinkCreateParams.maxNumKeyPoints;
    pObj->algSofCreateParams.maxPrevTrackPoints          = pLinkObj->algLinkCreateParams.maxPrevTrackPoints;
    UTILS_assert(pLinkObj->algLinkCreateParams.fast9Threshold < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.fast9Threshold              = pLinkObj->algLinkCreateParams.fast9Threshold;
    UTILS_assert(pLinkObj->algLinkCreateParams.scoreMethod< 0x00000100); /*uint8*/
    pObj->algSofCreateParams.scoreMethod                 = pLinkObj->algLinkCreateParams.scoreMethod;
	UTILS_assert(pLinkObj->algLinkCreateParams.harrisScaling < 0x00010000); /*uint16*/
    pObj->algSofCreateParams.harrisScaling               = pLinkObj->algLinkCreateParams.harrisScaling;
    pObj->algSofCreateParams.nmsThreshold                = pLinkObj->algLinkCreateParams.nmsThreshold;
    UTILS_assert(pLinkObj->algLinkCreateParams.harrisScoreMethod < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.harrisScoreMethod           = pLinkObj->algLinkCreateParams.harrisScoreMethod;
    UTILS_assert(pLinkObj->algLinkCreateParams.harrisWindowSize < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.harrisWindowSize            = pLinkObj->algLinkCreateParams.harrisWindowSize;
    UTILS_assert(pLinkObj->algLinkCreateParams.suppressionMethod < 0x00000100); /*uint8*/
    pObj->algSofCreateParams.suppressionMethod           = pLinkObj->algLinkCreateParams.suppressionMethod;

    UTILS_assert(pLinkObj->algLinkCreateParams.trackOffsetMethod < 0x00010000); /*uint16*/
        pObj->algSofCreateParams.trackOffsetMethod        = pLinkObj->algLinkCreateParams.trackOffsetMethod;

    for(i=0; i<PYRAMID_LK_TRACKER_TI_MAXLEVELS;i++)
    {
        UTILS_assert(pLinkObj->algLinkCreateParams.maxItersLK[i] < 0x00010000); /*uint16*/
        pObj->algSofCreateParams.maxItersLK[i] = pLinkObj->algLinkCreateParams.maxItersLK[i];
        UTILS_assert(pLinkObj->algLinkCreateParams.minErrValue[i] < 0x00010000); /*uint16*/
        pObj->algSofCreateParams.minErrValue[i] = pLinkObj->algLinkCreateParams.minErrValue[i];
        UTILS_assert(pLinkObj->algLinkCreateParams.searchRange[i] < 0x00000100); /*uint8*/
        pObj->algSofCreateParams.searchRange[i] = pLinkObj->algLinkCreateParams.searchRange[i];
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
Int32 AlgorithmLink_sparseOpticalFlowCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId, chId;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_SparseOpticalFlowObj                  * pSOFObj;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_LinkChInfo                                   * pPrevChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;

    pSOFObj = (AlgorithmLink_SparseOpticalFlowObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_SparseOpticalFlowObj),
                        32);
    UTILS_assert(pSOFObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pSOFObj);

    pInputQInfo       = &pSOFObj->inputQInfo;
    pOutputQInfo      = &pSOFObj->outputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            &pSOFObj->algLinkCreateParams,
            pCreateParams,
            sizeof(pSOFObj->algLinkCreateParams)
           );

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    status = System_linkGetInfo(
                    pSOFObj->algLinkCreateParams.inQueParams.prevLinkId,
                    &prevLinkInfo
                    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= 1);
    UTILS_assert(pSOFObj->algLinkCreateParams.maxNumKeyPoints <= SOF_ALGLINK_TRACK_POINTS_MAX);

    prevLinkQId = pSOFObj->algLinkCreateParams.inQueParams.prevLinkQueId;

    if (pSOFObj->algLinkCreateParams.compositeBufferInput == -1)
    {
        UTILS_assert(prevLinkInfo.queInfo[prevLinkQId].numCh
            <
            SPARSEOPTICALFLOW_LINK_MAX_CH
        );
    }

    if(pSOFObj->algLinkCreateParams.numOutBuffers
        > SPARSEOPTICALFLOW_LINK_MAX_NUM_OUTPUT)
    {
        pSOFObj->algLinkCreateParams.numOutBuffers
            = SPARSEOPTICALFLOW_LINK_MAX_NUM_OUTPUT;
    }

    if (pSOFObj->algLinkCreateParams.compositeBufferInput == -1)
    {
        pOutputQInfo->queInfo.numCh = prevLinkInfo.queInfo[prevLinkQId].numCh;
    }
    else
    {
        pOutputQInfo->queInfo.numCh = 1;
    }

    for(chId=0; chId<pOutputQInfo->queInfo.numCh; chId++)
    {
        pOutChInfo          = &pOutputQInfo->queInfo.chInfo[chId];
        pOutChInfo->flags   = 0;
        pOutChInfo->height  = 0;
        pOutChInfo->width   = 0;
    }

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

    for(chId=0; chId<pOutputQInfo->queInfo.numCh; chId++)
    {
        UTILS_assert(chId < SPARSEOPTICALFLOW_LINK_MAX_CH);
        pPrevChInfo = &prevLinkInfo.queInfo[prevLinkQId].chInfo[chId];

        if(System_Link_Ch_Info_Get_Flag_Data_Format(pPrevChInfo->flags)
                != SYSTEM_DF_YUV420SP_UV
        )
        {
            UTILS_assert(NULL);
        }

        AlgorithmLink_sparseOpticalFlowAlgParamsInit(
                        pSOFObj, &pSOFObj->chObj[chId], pPrevChInfo);

        AlgorithmLink_sparseOpticalFlowAlgCreate(
                &pSOFObj->chObj[chId]);

        /*
         * Allocate memory for the output buffers and link metadata buffer with
         * system Buffer
         */

        for (bufId = 0; bufId < pSOFObj->algLinkCreateParams.numOutBuffers; bufId++)
        {
            pSystemBuffer       =   &pSOFObj->chObj[chId].buffers[bufId];
            pMetaDataBuffer     =   &pSOFObj->chObj[chId].metaDataBuffers[bufId];

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
            pSystemBuffer->payload      =   pMetaDataBuffer;
            pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
            pSystemBuffer->chNum        =   chId;

            pMetaDataBuffer->numMetaDataPlanes  =  3;
            pMetaDataBuffer->metaBufSize[0]
                =  pSOFObj->chObj[chId].algSofOutBufSizeTrackedPoints;

            pMetaDataBuffer->bufAddr[0] =  Utils_memAlloc(
                                                UTILS_HEAPID_DDR_CACHED_SR,
                                                pMetaDataBuffer->metaBufSize[0],
                                                ALGORITHMLINK_FRAME_ALIGN
                                                );

            pMetaDataBuffer->metaFillLength[0] = pMetaDataBuffer->metaBufSize[0];

            UTILS_assert(pMetaDataBuffer->bufAddr[0] != NULL);

            pMetaDataBuffer->metaBufSize[1]
                = SPARSEOPTICALFLOW_SFM_META_DATA_MAX_SIZE;

            pMetaDataBuffer->bufAddr[1]  =  Utils_memAlloc(
                                                 UTILS_HEAPID_DDR_CACHED_SR,
                                                 pMetaDataBuffer->metaBufSize[1],
                                                 ALGORITHMLINK_FRAME_ALIGN
                                                 );

            pMetaDataBuffer->metaFillLength[1] = 0;

            UTILS_assert(pMetaDataBuffer->bufAddr[1] != NULL);

            pMetaDataBuffer->metaBufSize[2]
                    =  pSOFObj->chObj[chId].algSofOutBufSizeErrEst;

            pMetaDataBuffer->bufAddr[2] =  Utils_memAlloc(
                         UTILS_HEAPID_DDR_CACHED_SR,
                         pMetaDataBuffer->metaBufSize[2],
                         ALGORITHMLINK_FRAME_ALIGN
                        );

            pMetaDataBuffer->metaFillLength[2] = pMetaDataBuffer->metaBufSize[2];

            UTILS_assert(pMetaDataBuffer->bufAddr[2] != NULL);

            pMetaDataBuffer->flags = 0;

            status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    pSOFObj->isFirstFrameRecv    = FALSE;

    /* Assign pointer to link stats object */
    pSOFObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_SPARSE_OPTICAL_FLOW");
    UTILS_assert(NULL != pSOFObj->linkStatsInfo);

    return SYSTEM_LINK_STATUS_SOK;
}


Int32 AlgorithmLink_sparseOpticalFlowProcess(void * pObj)
{
    UInt32 bufId, chId;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_SparseOpticalFlowObj                  * pSOFObj;
    AlgorithmLink_SparseOpticalFlowChObj                * pChObj;
    System_BufferList                                     inputBufList;
    AlgorithmLink_SparseOpticalFlowCreateParams         * pLinkCreatePrms;
    System_Buffer                                       * pSysOutBuffer;
    System_Buffer                                       * pSysInBuffer;
    System_VideoFrameBuffer                             * pInVideoBuf;
    System_VideoFrameCompositeBuffer                    * pInVideoCompBuf;
    System_MetaDataBuffer                               * pOutMetaBuf;
    System_BufferList                                   bufListReturn;
    System_LinkStatistics *linkStatsInfo;

    pSOFObj = (AlgorithmLink_SparseOpticalFlowObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    Int32 compositeBufferInput = pSOFObj->algLinkCreateParams.compositeBufferInput;

    pLinkCreatePrms = &pSOFObj->algLinkCreateParams;

    linkStatsInfo = pSOFObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if (pSOFObj->isFirstFrameRecv == FALSE)
    {
        pSOFObj->isFirstFrameRecv = TRUE;

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
            if(pSysInBuffer->chNum >= pSOFObj->outputQInfo.queInfo.numCh)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            chId = pSysInBuffer->chNum;

            pChObj = &pSOFObj->chObj[chId];

            linkStatsInfo->linkStats.chStats[chId].inBufRecvCount++;

            status = AlgorithmLink_getEmptyOutputBuffer(
                                                    pObj,
                                                    0,
                                                    chId,
                                                    &pSysOutBuffer
                                                    );
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                linkStatsInfo->linkStats.chStats
                            [chId].inBufDropCount++;
                linkStatsInfo->linkStats.chStats
                            [chId].outBufDropCount[0]++;
            }
            else
            {
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                /*if input is no composite buffer*/
                if (compositeBufferInput<0)
                {
                  pInVideoCompBuf = 0; /*not used*/
                  pInVideoBuf  = (System_VideoFrameBuffer *) pSysInBuffer->payload;

                  if(pLinkCreatePrms->enableRoi)
                  {
                      /* Offset should be calculated with pitch */
                      pChObj->algSofInBufDescImage.bufPlanes[0].buf =
                                 (Void *)((UInt8 *)pInVideoBuf->bufAddr[0] +
                                 (pLinkCreatePrms->imgFrameStartY * pChObj->algSofCreateParams.imWidth + pLinkCreatePrms->imgFrameStartX));
                  }
                  else
                  {
                      pChObj->algSofInBufDescImage.bufPlanes[0].buf = (Void *)(pInVideoBuf->bufAddr[0]);
                  }

                  if(pInVideoBuf->metaBufAddr!=NULL
                     &&
                     pInVideoBuf->metaBufSize!=0
                     &&
                     pInVideoBuf->metaFillLength!=0
                     &&
                     pInVideoBuf->metaFillLength <=
                     pOutMetaBuf->metaBufSize[1]
                     )
                  {
                    memcpy(
                            pOutMetaBuf->bufAddr[1],
                            pInVideoBuf->metaBufAddr,
                            pInVideoBuf->metaFillLength
                            );

                    pOutMetaBuf->metaFillLength[1] = pInVideoBuf->metaFillLength;
                  }
                }
                /*if input is composite buffer*/
                else
                {
                  pInVideoBuf  = 0; /*not used*/
                  pInVideoCompBuf  = (System_VideoFrameCompositeBuffer *) pSysInBuffer->payload;
                  UTILS_assert(pInVideoCompBuf!=NULL);

                  pChObj->algSofInBufDescImage.bufPlanes[0].buf = pInVideoCompBuf->bufAddr[0][compositeBufferInput];

                  if(pInVideoCompBuf->metaBufAddr[compositeBufferInput]!=NULL
                    &&
                    pInVideoCompBuf->metaBufSize!=0
                    &&
                    pInVideoCompBuf->metaFillLength!=0
                    &&
                    pInVideoCompBuf->metaFillLength <=
                    pOutMetaBuf->metaBufSize[1]
                    )
                  {
                     memcpy(
                         pOutMetaBuf->bufAddr[1],
                         pInVideoCompBuf->metaBufAddr[compositeBufferInput],
                         pInVideoCompBuf->metaFillLength
                        );

                     pOutMetaBuf->metaFillLength[1] = pInVideoCompBuf->metaFillLength;
                  }
                }

                status = AlgIvision_process(
                                pChObj->algSofHandle,
                                &pChObj->algSofInBufs,
                                &pChObj->algSofOutBufs,
                                (IVISION_InArgs*)&pChObj->algSofInArgs,
                                (IVISION_OutArgs *)&pChObj->algSofOutArgs
                    );

                UTILS_assert(status==IALG_EOK);

                pChObj->algSofInArgs.numCorners = pChObj->algSofOutArgs.numCorners;

                EDMA_UTILS_memcpy2D(
                       pOutMetaBuf->bufAddr[0],
                       pChObj->pAlgSofOutBufTrackedPoints,
                       sizeof(strackInfo),
                       pChObj->algSofCreateParams.maxNumKeyPoints,
                       sizeof(strackInfo),
                       sizeof(strackInfo)
                       );

                EDMA_UTILS_memcpy2D(
                       pOutMetaBuf->bufAddr[2],
                       pChObj->pAlgSofOutBufErrEst,
                       sizeof(UInt16),
                       pChObj->algSofCreateParams.maxNumKeyPoints,
                       sizeof(UInt16),
                       sizeof(UInt16)
                       );

                pOutMetaBuf->flags = 0;

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                            [chId].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                            [chId].outBufCount[0]++;

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

Int32 AlgorithmLink_sparseOpticalFlowControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_SparseOpticalFlowObj* pSOFObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pSOFObj = (AlgorithmLink_SparseOpticalFlowObj *)
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
            AlgorithmLink_sparseOpticalFlowPrintStatistics(
                                                                pObj,
                                                                pSOFObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_sparseOpticalFlowStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_sparseOpticalFlowDelete(void * pObj)
{

    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId, chId;
    AlgorithmLink_SparseOpticalFlowObj *pSOFObj;
    System_MetaDataBuffer              *pMetaDataBuffer;

    pSOFObj = (AlgorithmLink_SparseOpticalFlowObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pSOFObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(chId=0; chId<pSOFObj->outputQInfo.queInfo.numCh; chId++)
    {
        UTILS_assert(chId < SPARSEOPTICALFLOW_LINK_MAX_CH);
        /*
         * Free allocated memory for alg internal objects
         */
        AlgorithmLink_sparseOpticalFlowAlgDelete(&pSOFObj->chObj[chId]);

        /*
         * Free link buffers
         */
        for (bufId = 0; bufId < pSOFObj->algLinkCreateParams.numOutBuffers; bufId++)
        {
            pMetaDataBuffer     =   &pSOFObj->chObj[chId].metaDataBuffers[bufId];

            status = Utils_memFree(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    pMetaDataBuffer->bufAddr[0],
                                    pMetaDataBuffer->metaBufSize[0]
                                   );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            status = Utils_memFree(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    pMetaDataBuffer->bufAddr[1],
                                    pMetaDataBuffer->metaBufSize[1]
                                   );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            status = Utils_memFree(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    pMetaDataBuffer->bufAddr[2],
                                    pMetaDataBuffer->metaBufSize[2]
                                   );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    Utils_memFree(
                   UTILS_HEAPID_DDR_CACHED_LOCAL,
                   pSOFObj,
                   sizeof(AlgorithmLink_SparseOpticalFlowObj)
                );

    return status;
}

Int32 AlgorithmLink_sparseOpticalFlowPrintStatistics(void *pObj,
                AlgorithmLink_SparseOpticalFlowObj *pSOFObj)
{
    UTILS_assert(NULL != pSOFObj->linkStatsInfo);

    Utils_printLinkStatistics(&pSOFObj->linkStatsInfo->linkStats,
                            "ALG_SPARSE_OPTICAL_FLOW",
                            TRUE);

    Utils_printLatency("ALG_SPARSE_OPTICAL_FLOW",
                       &pSOFObj->linkStatsInfo->linkLatency,
                       &pSOFObj->linkStatsInfo->srcToLinkLatency,
                        TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

