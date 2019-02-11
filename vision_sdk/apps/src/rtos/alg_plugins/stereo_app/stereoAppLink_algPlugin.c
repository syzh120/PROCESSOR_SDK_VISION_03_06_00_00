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
 * \file stereoAppLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Stereo App algorithm Link
 *
 * \version 0.1 (Oct 2014) : [VT] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "stereoAppLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>


//#define POINT_3D_SIZE 8 // sizeof(Int16) * 4 elements

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plug-ins of stereoApp algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoApp_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
            AlgorithmLink_StereoAppCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
            AlgorithmLink_StereoAppProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
            AlgorithmLink_StereoAppControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
            AlgorithmLink_StereoAppStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
            AlgorithmLink_StereoAppDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_STEREO_APP;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief  Initialize Sense and Avoid link create params
 *
 *
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return
 *
 *******************************************************************************
 */
Void AlgorithmLink_initAlgCreateParams(StereoApp_CreationParamsStruct *pAlgCreateParams,
        AlgorithmLink_StereoAppCreateParams * pStereoAppLinkCreateParams)
{
    // uniform grid size
    pAlgCreateParams->uniGridSizeX = UNIF_GRID_SIZE_X;
    pAlgCreateParams->uniGridSizeY = UNIF_GRID_SIZE_Y;
    pAlgCreateParams->uniGridSizeZ = UNIF_GRID_SIZE_Z;

    // ROI
    pAlgCreateParams->xRoiSIdx = (UNIF_GRID_SIZE_X / 2) - X_ROI_OFFSET;
    pAlgCreateParams->xRoiEIdx = (UNIF_GRID_SIZE_X / 2) + X_ROI_OFFSET;
    pAlgCreateParams->yRoiSIdx = pAlgCreateParams->xRoiSIdx;
    pAlgCreateParams->yRoiEIdx = pAlgCreateParams->xRoiEIdx;
    pAlgCreateParams->zRoiSIdx = pAlgCreateParams->xRoiSIdx;
    pAlgCreateParams->zRoiEIdx = pAlgCreateParams->xRoiEIdx;

    // safety bubble
    pAlgCreateParams->xSbSIdx = (UNIF_GRID_SIZE_X / 2) - X_SB_OFFSET;
    pAlgCreateParams->xSbEIdx = (UNIF_GRID_SIZE_X / 2) + X_SB_OFFSET;
    pAlgCreateParams->ySbSIdx = pAlgCreateParams->xSbSIdx;
    pAlgCreateParams->ySbEIdx = pAlgCreateParams->xSbEIdx;
    pAlgCreateParams->zSbSIdx = pAlgCreateParams->xSbSIdx;
    pAlgCreateParams->zSbEIdx = pAlgCreateParams->xSbEIdx; 

    pAlgCreateParams->baseline = pStereoAppLinkCreateParams->saParams.baseline;
    pAlgCreateParams->scale_x = pStereoAppLinkCreateParams->saParams.scale_x;
    pAlgCreateParams->scale_y = pStereoAppLinkCreateParams->saParams.scale_y;
    pAlgCreateParams->f = pStereoAppLinkCreateParams->saParams.f;
    pAlgCreateParams->dc_x = pStereoAppLinkCreateParams->saParams.dc_x;
    pAlgCreateParams->dc_y = pStereoAppLinkCreateParams->saParams.dc_y;
    pAlgCreateParams->ofst_x = pStereoAppLinkCreateParams->saParams.ofst_x;
    pAlgCreateParams->ofst_y = pStereoAppLinkCreateParams->saParams.ofst_y;
    memcpy(pAlgCreateParams->calmat, pStereoAppLinkCreateParams->saParams.calmat, sizeof(float)*12);


    /*
     * for sense and avoid algorithm
     */
    pAlgCreateParams->objectDSigma = 50.0;
    pAlgCreateParams->objectDSigmaMin = 50.0;

    // z range (indices) where drone can move
    // if droneMoveSZRange = droneMoveEZRange  =  UNIF_GRID_SIZE_X / 2, drone doesn't move vertically (in z direction)
    pAlgCreateParams->droneMoveSZRange = (UNIF_GRID_SIZE_Z / 2);
    pAlgCreateParams->droneMoveEZRange = (UNIF_GRID_SIZE_Z / 2);

    // waypoint in x, y z
    pAlgCreateParams->wayPoint[0] = 0;
    pAlgCreateParams->wayPoint[1] = 1000;
    pAlgCreateParams->wayPoint[2] = 0;

}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for stereo app alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoAppCreate(void * pObj, void * pCreateParams)
{

    void                       * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgorithmLink_StereoAppOutputQueId   outputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       metaBufSize;

    System_LinkChInfo          * pOutChInfo;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_StereoAppObj          * pStereoAppObj;
    AlgorithmLink_StereoAppCreateParams * pStereoAppLinkCreateParams;
    StereoApp_CreationParamsStruct      * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;

    pStereoAppLinkCreateParams =
        (AlgorithmLink_StereoAppCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    if(sizeof(AlgorithmLink_StereoAppObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
        pStereoAppObj = (AlgorithmLink_StereoAppObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                       sizeof(AlgorithmLink_StereoAppObj), 32);
    }
    else
    {
        pStereoAppObj = (AlgorithmLink_StereoAppObj *)
                        malloc(sizeof(AlgorithmLink_StereoAppObj));
    }

    UTILS_assert(pStereoAppObj!=NULL);

    pAlgCreateParams = &pStereoAppObj->algCreateParams;

    pOutputQInfo = &pStereoAppObj->outputQInfo[0];
    pInputQInfo  = &pStereoAppObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pStereoAppObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pStereoAppObj->algLinkCreateParams),
           (void*)(pStereoAppLinkCreateParams),
           sizeof(AlgorithmLink_StereoAppCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of stereoApp
     * algorithm link
     */
    numInputQUsed     = ALGLINK_STEREOAPP_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_STEREOAPP_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo[ALGLINK_STEREOAPP_IPQID_DISPARITY].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_STEREOAPP_OPQID_PCL].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[ALGLINK_STEREOAPP_OPQID_OGMAP].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[ALGLINK_STEREOAPP_OPQID_MV].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_STEREOAPP_OPQID_PCL].queInfo.numCh = numChannelsUsed;
    pOutputQInfo[ALGLINK_STEREOAPP_OPQID_OGMAP].queInfo.numCh = numChannelsUsed;
    pOutputQInfo[ALGLINK_STEREOAPP_OPQID_MV].queInfo.numCh = numChannelsUsed;


    /*
     * Channel info population for output Q Ids
     */
    outputQId  = ALGLINK_STEREOAPP_OPQID_PCL;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;

    outputQId  = ALGLINK_STEREOAPP_OPQID_OGMAP;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;

    outputQId  = ALGLINK_STEREOAPP_OPQID_MV;
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
    // Creation parameters for sense and avoid detect
    UTILS_assert(pStereoAppLinkCreateParams->maxInputHeight <=
                    STEREOAPP_LINK_INPUT_HEIGHT);
    UTILS_assert(pStereoAppLinkCreateParams->maxInputWidth <=
                    STEREOAPP_LINK_INPUT_WIDTH);


    pAlgCreateParams->inPCLHeight =
            pStereoAppLinkCreateParams->maxInputHeight;
    pAlgCreateParams->inPCLWidth =
            pStereoAppLinkCreateParams->maxInputWidth;


    pAlgCreateParams->numPairs =
            pStereoAppLinkCreateParams->numPairs;
    pAlgCreateParams->bDataStreaming =
            pStereoAppLinkCreateParams->bDataStreaming;
    pAlgCreateParams->bSenseAvoid =
                pStereoAppLinkCreateParams->bSenseAvoid;
    pAlgCreateParams->objectDetectMode =
                pStereoAppLinkCreateParams->objectDetectMode;

    pAlgCreateParams->useDispRoiForPCL =
                pStereoAppLinkCreateParams->dispRoiParams.useDispRoiForPCL;
    pAlgCreateParams->dispRoiStartX =
                    pStereoAppLinkCreateParams->dispRoiParams.dispRoiStartX;
    pAlgCreateParams->dispRoiStartY =
                    pStereoAppLinkCreateParams->dispRoiParams.dispRoiStartY;
    pAlgCreateParams->dispRoiWidth =
                    pStereoAppLinkCreateParams->dispRoiParams.dispRoiWidth;
    pAlgCreateParams->dispRoiHeight =
                    pStereoAppLinkCreateParams->dispRoiParams.dispRoiHeight;


    // initialize remaining Stereo App link create params
    AlgorithmLink_initAlgCreateParams(pAlgCreateParams, pStereoAppLinkCreateParams);

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_StereoAppMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_StereoAppMemQuery(pAlgCreateParams, &memRequests, 0);
#if 0
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
            if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
            {
                memRequests.memTab[memTabId].basePtr = (void *)Utils_memAlloc(
                        UTILS_HEAPID_L2_LOCAL,
                        memRequests.memTab[memTabId].size,
                        memRequests.memTab[memTabId].alignment);
            } else if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD){
                memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        memRequests.memTab[memTabId].size,
                        memRequests.memTab[memTabId].alignment);
            } else {
                memRequests.memTab[memTabId].basePtr = malloc(memRequests.memTab[memTabId].size);
            }
            UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
        }
    }
#else

    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if (memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
        {
            memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                    UTILS_HEAPID_L2_LOCAL,
                    memRequests.memTab[memTabId].size,
                    memRequests.memTab[memTabId].alignment);

            UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

        } else
        {
            if(memRequests.memTab[memTabId].size > 0)
            {
                if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD)
                {
                    memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            memRequests.memTab[memTabId].size,
                            memRequests.memTab[memTabId].alignment);
                }
                else
                {
                    memRequests.memTab[memTabId].basePtr =
                            malloc(memRequests.memTab[memTabId].size);
                }

                UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);
            }
        }
    }
#endif

    algHandle = Alg_StereoAppCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);


    pStereoAppObj->algHandle = algHandle;

    /*
     * Creation of output buffers for output Qs
     *  - Connecting metadata buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    // ALGLINK_STEREOAPP_OPQID_PCL
    channelId = 0;
    outputQId = ALGLINK_STEREOAPP_OPQID_PCL;

    for(frameIdx = 0;
        frameIdx < pStereoAppObj->algLinkCreateParams.numOutputBuffers;
        frameIdx++)
    {
        pSystemBuffer         =  &(pStereoAppObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =  &(pStereoAppObj->stereoAppOut[outputQId][frameIdx]); //&(pStereoAppObj->motionVector[frameIdx]);


        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        // buf size
        metaBufSize = pStereoAppLinkCreateParams->maxInputWidth * pStereoAppLinkCreateParams->maxInputHeight *
                pStereoAppLinkCreateParams->numPairs * 8 + PCL_HEADER_SIZE;  // 8 is point size (x, y, z, pel)

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

    // ALGLINK_STEREOAPP_OPQID_OGMAP
    channelId = 0;
    outputQId = ALGLINK_STEREOAPP_OPQID_OGMAP;

    for(frameIdx = 0;
        frameIdx < pStereoAppObj->algLinkCreateParams.numOutputBuffers;
        frameIdx++)
    {
        pSystemBuffer         =  &(pStereoAppObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =  &(pStereoAppObj->stereoAppOut[outputQId][frameIdx]); //&(pStereoAppObj->motionVector[frameIdx]);


        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        // 6 = 2 bytes for x, y, z
        metaBufSize = UNIF_GRID_SIZE_X * UNIF_GRID_SIZE_Y * UNIF_GRID_SIZE_Z + 1 + OGMAP_HEADER_SIZE;

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

    // ALGLINK_STEREOAPP_OPQID_MV
    if (pStereoAppObj->algLinkCreateParams.bSenseAvoid)
    {
        channelId = 0;
        outputQId = ALGLINK_STEREOAPP_OPQID_MV;

        for(frameIdx = 0;
            frameIdx < pStereoAppObj->algLinkCreateParams.numOutputBuffers;
            frameIdx++)
        {
            pSystemBuffer         = &(pStereoAppObj->buffers[outputQId][frameIdx]);
            pSystemMetaDataBuffer = &(pStereoAppObj->stereoAppOut[outputQId][frameIdx]);

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSystemBuffer->payload     = pSystemMetaDataBuffer;
            pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
            pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
            pSystemBuffer->chNum       = channelId;

            metaBufSize = DRONE_MV_SIZE;

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
    }

    pStereoAppObj->frameDropCounter          = 0;

    pStereoAppObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
            AlgorithmLink_getLinkId(pObj), "ALG_SENSEAVOID");
    UTILS_assert(NULL != pStereoAppObj->linkStatsInfo);

    pStereoAppObj->numInputChannels = 1;

    pStereoAppObj->isFirstFrameRecv = FALSE;
    pStereoAppObj->isFirstFrameToProcess = TRUE;


    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of stereo app algorithm link
 *
 *        This function and the algorithm process function execute
 *        on same processor core. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empty this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoAppProcess(void * pObj)
{

    AlgorithmLink_StereoAppObj  * pStereoAppObj;
    void                        * algHandle;
    AlgorithmLink_StereoAppInputQueId    inputQId;
    AlgorithmLink_StereoAppOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;

    System_Buffer              * pSysBufferMV;
    System_Buffer              * pSysBufferOGMap;
    System_Buffer              * pSysBufferPCL;

    System_MetaDataBuffer      * pDisparityBuffer;
    System_MetaDataBuffer      * pMVBuffer;
    System_MetaDataBuffer      * pOGMapBuffer;
    System_MetaDataBuffer      * pPCLBuffer;

    UInt8                      * pPCLDataBuffer;
    UInt8                      * pOGMapDataBuffer;

    Bool                         bufDropFlag;
    //Bool                         algoProcessCallNeeded;

    AlgorithmLink_StereoAppCreateParams  * pStereoAppLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    pStereoAppObj = (AlgorithmLink_StereoAppObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pStereoAppObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                 = pStereoAppObj->algHandle;
    pStereoAppLinkCreateParams = (AlgorithmLink_StereoAppCreateParams *)
                                    &pStereoAppObj->algLinkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);


    if(pStereoAppObj->isFirstFrameRecv==FALSE)
    {
        pStereoAppObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pStereoAppObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_STEREOAPP_IPQID_DISPARITY and process them if output is
     * available
     */
    inputQId = ALGLINK_STEREOAPP_IPQID_DISPARITY;

    System_getLinksFullBuffers(
        pStereoAppLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pStereoAppLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pStereoAppObj->sysBufferDisparity = inputBufList.buffers[bufId];
            pDisparityBuffer = (System_MetaDataBuffer *) pStereoAppObj->sysBufferDisparity->payload;

            bufDropFlag = TRUE;

            /*
             * TBD: Put any other checks for input parameter correctness.
             */


            /*
             * For frame to be processed:
             *  - Output buffer will be queried
             *  - If output buffer is available, then algorithm will be called
             */
            {
                outputQId = ALGLINK_STEREOAPP_OPQID_PCL;
                channelId = 0;
                status = AlgorithmLink_getEmptyOutputBuffer(
                                                    pObj,
                                                    outputQId,
                                                    channelId,
                                                    &pSysBufferPCL);

                if (status == SYSTEM_LINK_STATUS_SOK)
                {
                    outputQId = ALGLINK_STEREOAPP_OPQID_OGMAP;
                    channelId = 0;
                    status = AlgorithmLink_getEmptyOutputBuffer(
                                                        pObj,
                                                        outputQId,
                                                        channelId,
                                                        &pSysBufferOGMap);

                    if (status == SYSTEM_LINK_STATUS_SOK)
                    {
                        if (pStereoAppObj->algLinkCreateParams.bSenseAvoid)
                        {
                            outputQId = ALGLINK_STEREOAPP_OPQID_MV;
                            channelId = 0;
                            status = AlgorithmLink_getEmptyOutputBuffer(
                                                                pObj,
                                                                outputQId,
                                                                channelId,
                                                                &pSysBufferMV);

                            if (status != SYSTEM_LINK_STATUS_SOK)
                            {
                                /*
                                 * If output buffer is not available,
                                 * then free-up the previously allocated output buffer
                                 */
                                AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                               ALGLINK_STEREOAPP_OPQID_PCL,
                                                               pSysBufferPCL);

                                AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                               ALGLINK_STEREOAPP_OPQID_OGMAP,
                                                               pSysBufferOGMap);
                            }
                        }
                    } else
                    {
                        /*
                         * If output buffer is not available,
                         * then free-up the previously allocated output buffer
                         */
                        AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                           ALGLINK_STEREOAPP_OPQID_PCL,
                                                           pSysBufferPCL);
                    }
                }

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

                    pSysBufferPCL->srcTimestamp = pStereoAppObj->sysBufferDisparity->srcTimestamp;
                    pSysBufferPCL->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                    pPCLBuffer = (System_MetaDataBuffer *)pSysBufferPCL->payload;

                    pSysBufferOGMap->srcTimestamp = pStereoAppObj->sysBufferDisparity->srcTimestamp;
                    pSysBufferOGMap->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                    pOGMapBuffer = (System_MetaDataBuffer *)pSysBufferOGMap->payload;

                    if (pStereoAppObj->algLinkCreateParams.bSenseAvoid)
                    {
                        pSysBufferMV->srcTimestamp = pStereoAppObj->sysBufferDisparity->srcTimestamp;
                        pSysBufferMV->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                        pMVBuffer = (System_MetaDataBuffer *)pSysBufferMV->payload;
                    }

                    /*
                     * set header first for PCL and OG Map
                     */
                    pPCLDataBuffer = (UInt8 *)pPCLBuffer->bufAddr[0];
                    pOGMapDataBuffer = (UInt8 *)pOGMapBuffer->bufAddr[0];


                    ((UInt32 *)pPCLDataBuffer)[0] = PLC_START_CODE;
                    ((UInt16 *)((UInt8 *)pPCLDataBuffer + 4))[0] = pStereoAppLinkCreateParams->maxInputWidth;
                    ((UInt16 *)((UInt8 *)pPCLDataBuffer + 4))[1] = pStereoAppLinkCreateParams->maxInputHeight;

                    ((UInt32 *)pOGMapDataBuffer)[0] = OGMAP_START_CODE;
                    ((UInt16 *)((UInt8 *)pOGMapDataBuffer + 4))[0] = UNIF_GRID_SIZE_X;
                    ((UInt16 *)((UInt8 *)pOGMapDataBuffer + 4))[1] = UNIF_GRID_SIZE_Y;
                    ((UInt16 *)((UInt8 *)pOGMapDataBuffer + 4))[2] = UNIF_GRID_SIZE_Z;


                    status = Alg_StereoAppProcess(
                                algHandle,
                                pDisparityBuffer->bufAddr[0],
                                pStereoAppObj->isFirstFrameToProcess,
                                (Int16 *)pMVBuffer->bufAddr[0],
                                (Int16 *)((UInt8 *) pPCLBuffer->bufAddr[0] + PCL_HEADER_SIZE),
                                (UInt8 *)((UInt8 *) pOGMapBuffer->bufAddr[0] + OGMAP_HEADER_SIZE)
                             );

                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    pStereoAppObj->isFirstFrameToProcess = FALSE;


                    Cache_wb(pPCLBuffer->bufAddr[0],
                             pPCLBuffer->metaBufSize[0],
                             Cache_Type_ALLD,
                             TRUE);

                    Cache_wb(pOGMapBuffer->bufAddr[0],
                             pOGMapBuffer->metaBufSize[0],
                             Cache_Type_ALLD,
                             TRUE);

                    if (pStereoAppObj->algLinkCreateParams.bSenseAvoid)
                    {
                        Cache_wb(pMVBuffer->bufAddr[0],
                                pMVBuffer->metaBufSize[0],
                                Cache_Type_ALLD,
                                TRUE);
                    }

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pSysBufferPCL->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pSysBufferPCL->srcTimestamp);


                    // Point cloud
                    /*
                     * Putting filled buffer into output full buffer
                     */
                    outputQId = ALGLINK_STEREOAPP_OPQID_PCL;
                    status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                                  outputQId,
                                                                  pSysBufferPCL);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /*
                     * Informing next link that a new data has been put for its
                     * processing
                     */
                    System_sendLinkCmd(
                          pStereoAppLinkCreateParams->outQueParams[outputQId].nextLink,
                          SYSTEM_CMD_NEW_DATA,
                          NULL);

                    /*
                     * Releasing (Free'ing) output buffers, since algorithm does not need
                     * it for any future usage.
                     */
                    outputBufListReturn.numBuf     = 1;
                    outputBufListReturn.buffers[0] = pSysBufferPCL;
                    status = AlgorithmLink_releaseOutputBuffer(pObj,
                                                      outputQId,
                                                      &outputBufListReturn);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    // OG map
                    outputQId = ALGLINK_STEREOAPP_OPQID_OGMAP;
                    status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                                  outputQId,
                                                                  pSysBufferOGMap);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /*
                     * Informing next link that a new data has been put for its
                     * processing
                     */
                    System_sendLinkCmd(
                          pStereoAppLinkCreateParams->outQueParams[outputQId].nextLink,
                          SYSTEM_CMD_NEW_DATA,
                          NULL);

                    outputBufListReturn.numBuf     = 1;
                    outputBufListReturn.buffers[0] = pSysBufferOGMap;
                    status = AlgorithmLink_releaseOutputBuffer(pObj,
                                                      outputQId,
                                                      &outputBufListReturn);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    // Drone Motion Vector
                    if (pStereoAppObj->algLinkCreateParams.bSenseAvoid)
                    {
                        /*
                         * Putting filled buffer into output full buffer
                         */
                        outputQId = ALGLINK_STEREOAPP_OPQID_MV;
                        status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                                  outputQId,
                                                                  pSysBufferMV);

                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                        /*
                         * Informing next link that a new data has been put for its
                         * processing
                         */
                        System_sendLinkCmd(
                              pStereoAppLinkCreateParams->outQueParams[outputQId].nextLink,
                              SYSTEM_CMD_NEW_DATA,
                              NULL);

                        /*
                         * Releasing (Free'ing) output buffers, since algorithm does not need
                         * it for any future usage.
                         */
                        outputBufListReturn.numBuf     = 1;
                        outputBufListReturn.buffers[0] = pSysBufferMV;
                        AlgorithmLink_releaseOutputBuffer(pObj,
                                                          outputQId,
                                                          &outputBufListReturn);
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    }

                    bufDropFlag = FALSE;
                }
            }

            /*
             * Releasing (Free'ing) Input buffers, since algorithm does not need
             * it for any future usage.
             */
            inputQId                      = ALGLINK_STEREOAPP_IPQID_DISPARITY;
            inputBufListReturn.numBuf     = 1;
            inputBufListReturn.buffers[0] = pStereoAppObj->sysBufferDisparity;
            AlgorithmLink_releaseInputBuffer(
                                            pObj,
                                            inputQId,
                                            pStereoAppLinkCreateParams->inQueParams[inputQId].prevLinkId,
                                            pStereoAppLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                                            &inputBufListReturn,
                                            &bufDropFlag);
        }

    }

    return status;

}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for sense and avoid algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_StereoAppControl(void * pObj, void * pControlParams)
{

    AlgorithmLink_StereoAppObj    * pStereoAppObj;
    AlgorithmLink_ControlParams   * pAlgLinkControlPrm;
    void                          * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pStereoAppObj = (AlgorithmLink_StereoAppObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pStereoAppObj->algHandle;

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
            AlgorithmLink_StereoAppPrintStatistics(pObj, pStereoAppObj);
            break;

        default:
            status = Alg_StereoAppControl(algHandle,
                                                &(pStereoAppObj->controlParams)
                                                );
            break;
    }

    return status;

}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for sense and avoid algorithm link
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
Int32 AlgorithmLink_StereoAppStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for sense and avoid algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoAppDelete(void * pObj)
{

    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_StereoAppObj     * pStereoAppObj;
    UInt32                            memTabId;

    AlgorithmLink_StereoAppOutputQueId   outputQId;

    pStereoAppObj = (AlgorithmLink_StereoAppObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pStereoAppObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_StereoAppDelete(pStereoAppObj->algHandle, &memRequests);

    /*
     * Memory allocations for the requests done by algorithm
     */
#if 0
    for(memTabId = 0; memTabId < memRequests.numMemTabs; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
            if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
            {
                status = Utils_memFree( UTILS_HEAPID_L2_LOCAL,
                                memRequests.memTab[memTabId].basePtr,
                                memRequests.memTab[memTabId].size);
            } else if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD)
            {
                status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                   memRequests.memTab[memTabId].basePtr,
                                   memRequests.memTab[memTabId].size);
            } else if(memTabId == 0)
            {
                status = Utils_memFree(  UTILS_HEAPID_DDR_CACHED_SR,
                                   memRequests.memTab[memTabId].basePtr,
                                   memRequests.memTab[memTabId].size);
            }
            else
            {
                free(memRequests.memTab[memTabId].basePtr);
            }
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }
#else
    for(memTabId = 0 ; memTabId < memRequests.numMemTabs; memTabId++)
    {
        if (memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
        {
            status = Utils_memFree( UTILS_HEAPID_L2_LOCAL,
                    memRequests.memTab[memTabId].basePtr,
                    memRequests.memTab[memTabId].size);
        } else
        {
            if(memRequests.memTab[memTabId].size > 0)
            {
                if(memRequests.memTab[memTabId].size > ALGORITHMLINK_SRMEM_THRESHOLD)
                {
                    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                            memRequests.memTab[memTabId].basePtr,
                            memRequests.memTab[memTabId].size);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                else
                {
                    free(memRequests.memTab[memTabId].basePtr);
                }
            }
        }
    }
#endif

    /*
     * Deletion of output buffers for output Qs
     */
    outputQId = ALGLINK_STEREOAPP_OPQID_PCL;
    for(frameIdx = 0;
        frameIdx < pStereoAppObj->algLinkCreateParams.numOutputBuffers;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pStereoAppObj->stereoAppOut[outputQId][frameIdx]);

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                pSystemMetaDataBuffer->metaBufSize[0] );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    outputQId = ALGLINK_STEREOAPP_OPQID_OGMAP;
    for(frameIdx = 0;
        frameIdx < pStereoAppObj->algLinkCreateParams.numOutputBuffers;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pStereoAppObj->stereoAppOut[outputQId][frameIdx]);


        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                pSystemMetaDataBuffer->metaBufSize[0]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    if (pStereoAppObj->algLinkCreateParams.bSenseAvoid)
    {
        outputQId = ALGLINK_STEREOAPP_OPQID_MV;
        for(frameIdx = 0;
            frameIdx < pStereoAppObj->algLinkCreateParams.numOutputBuffers;
            frameIdx++)
        {
            pSystemMetaDataBuffer =
                    &(pStereoAppObj->stereoAppOut[outputQId][frameIdx]);

            status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemMetaDataBuffer->bufAddr[0],
                                    pSystemMetaDataBuffer->metaBufSize[0] );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    /*
     * Space for Algorithm specific object gets freed here.
     */
    if(sizeof(AlgorithmLink_StereoAppObj) > ALGORITHMLINK_SRMEM_THRESHOLD)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pStereoAppObj,
                               sizeof(AlgorithmLink_StereoAppObj));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        free(pStereoAppObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pACDetectObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoAppPrintStatistics(void *pObj,
                       AlgorithmLink_StereoAppObj *pStereoAppObj)
{

    UTILS_assert(NULL != pStereoAppObj->linkStatsInfo);

    Utils_printLinkStatistics(&pStereoAppObj->linkStatsInfo->linkStats, "ALG_SENSEAVOID", TRUE);

    Utils_printLatency("ALG_SENSEAVOID",
                       &pStereoAppObj->linkStatsInfo->linkLatency,
                       &pStereoAppObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */


