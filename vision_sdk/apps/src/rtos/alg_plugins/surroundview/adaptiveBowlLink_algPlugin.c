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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 * \file adaptiveBowlLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for geometric alignment Link
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "svAlgLink_priv.h"
#include "adaptiveBowlLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include <include/link_api/sgx3DsrvLink.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of adaptive bowl algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_adaptiveBowl_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_adaptiveBowlCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_adaptiveBowlProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_adaptiveBowlControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_adaptiveBowlStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_adaptiveBowlDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_ADAPTIVEBOWL;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for geometric alignment alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_adaptiveBowlCreate(void * pObj, void * pCreateParams)
{
    void                       * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    System_LinkInfo              prevLinkInfo;
    AlgorithmLink_AdaptiveBowlOutputQueId   outputQId;
    AlgorithmLink_AdaptiveBowlInputQueId    inputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       metaBufSize;
    UInt32                       dataFormat;
    System_LinkChInfo          * pOutChInfo;
    System_LinkChInfo          * pPrevChInfo;
    UInt32                       prevChInfoFlags;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_AdaptiveBowlObj              * pAdaptiveBowlObj;
    AlgorithmLink_AdaptiveBowlCreateParams     * pAdaptiveBowlLinkCreateParams;
    SV_AdaptiveBowl_CreationParamsStruct       * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;

    pAdaptiveBowlLinkCreateParams =
        (AlgorithmLink_AdaptiveBowlCreateParams *)pCreateParams;

    Vps_printf("================ AdaptiveBowl Create\n");

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    if(sizeof(AlgorithmLink_AdaptiveBowlObj) > SV_ALGLINK_SRMEM_THRESHOLD)
    {
        pAdaptiveBowlObj = (AlgorithmLink_AdaptiveBowlObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                       sizeof(AlgorithmLink_AdaptiveBowlObj), 32);
    }
    else
    {
        pAdaptiveBowlObj = (AlgorithmLink_AdaptiveBowlObj *)
                        malloc(sizeof(AlgorithmLink_AdaptiveBowlObj));
    }

    UTILS_assert(pAdaptiveBowlObj!=NULL);

    pAlgCreateParams = &pAdaptiveBowlObj->algCreateParams;

    pOutputQInfo = &pAdaptiveBowlObj->outputQInfo[0];
    pInputQInfo  = &pAdaptiveBowlObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAdaptiveBowlObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pAdaptiveBowlObj->algLinkCreateParams),
           (void*)(pAdaptiveBowlLinkCreateParams),
           sizeof(AlgorithmLink_AdaptiveBowlCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of geometric alignment
     * algorithm link
     */
    numInputQUsed     = ALGLINK_ADAPTIVEBOWL_IPQID_MAXIPQ;

    numOutputQUsed    = ALGLINK_ADAPTIVEBOWL_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    // Output from ultrasonic link
    pInputQInfo[ALGLINK_ADAPTIVEBOWL_IPQID_MULTISENSOR].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT].queInfo.numCh = numChannelsUsed;

    // input frames
    inputQId  = ALGLINK_ADAPTIVEBOWL_IPQID_MULTISENSOR;

    status = System_linkGetInfo(
                pAdaptiveBowlLinkCreateParams->inQueParams[inputQId].prevLinkId,
                &prevLinkInfo);

    prevLinkQueId =
        pAdaptiveBowlLinkCreateParams->inQueParams[inputQId].prevLinkQueId;
    pPrevChInfo   =
        &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    prevChInfoFlags    = pPrevChInfo->flags;
    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    pAdaptiveBowlObj->dataFormat = dataFormat;
    pAdaptiveBowlObj->inPitch[0] = pPrevChInfo->pitch[0];
    pAdaptiveBowlObj->inPitch[1] = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pAdaptiveBowlObj->algLinkCreateParams.maxInputWidth)
       ||
       (pPrevChInfo->height > pAdaptiveBowlObj->algLinkCreateParams.maxInputHeight)
      )
    {
      UTILS_assert(NULL);
    }

    outputQId = ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT;
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

    if(ALGLINK_ADAPTIVE_OUTPUTRES_2MP == pAdaptiveBowlObj->algLinkCreateParams.outputRes)
    {
        UTILS_assert(pAdaptiveBowlLinkCreateParams->maxOutputWidth <=
                        SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP);
    }
    else
    {
        UTILS_assert(pAdaptiveBowlLinkCreateParams->maxOutputHeight <=
                        SV_ALGLINK_OUTPUT_FRAME_HEIGHT);
        UTILS_assert(pAdaptiveBowlLinkCreateParams->maxOutputWidth <=
                        SV_ALGLINK_OUTPUT_FRAME_WIDTH);
    }

    pAlgCreateParams->SVInCamFrmHeight =
        pAdaptiveBowlLinkCreateParams->maxInputHeight;
    pAlgCreateParams->SVInCamFrmWidth =
        pAdaptiveBowlLinkCreateParams->maxInputWidth;
    pAlgCreateParams->SVOutDisplayHeight =
        pAdaptiveBowlLinkCreateParams->maxOutputHeight;
    pAlgCreateParams->SVOutDisplayWidth =
        pAdaptiveBowlLinkCreateParams->maxOutputWidth;
    pAlgCreateParams->numCameras =
        pAdaptiveBowlLinkCreateParams->numViews;

    pAlgCreateParams->offsetXleft =
        pAdaptiveBowlLinkCreateParams->offsetXleft;
    pAlgCreateParams->offsetXright =
        pAdaptiveBowlLinkCreateParams->offsetXright;
    pAlgCreateParams->offsetYfront =
        pAdaptiveBowlLinkCreateParams->offsetYfront;
    pAlgCreateParams->offsetYback =
        pAdaptiveBowlLinkCreateParams->offsetYback;

       //To be updated by Pavan, these three parameters should be consistent for All three algorithms, therefore should be passed in
    pAlgCreateParams->numColorChannels      = 3;
    pAlgCreateParams->DMAblockSizeV         = 40;
    pAlgCreateParams->DMAblockSizeH         = 40;

    pAlgCreateParams->saladbowlFocalLength  = 8000;
    pAlgCreateParams->defaultFocalLength    =
                            pAdaptiveBowlObj->algLinkCreateParams.defaultFocalLength;
    pAlgCreateParams->subsampleratio        = 4; // Subsample set here

    pAlgCreateParams->outputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
    pAlgCreateParams->useDefaultPixelsPerCm = 1; //use default PixelPerCm values ? 1-yes, 0-no

    pAlgCreateParams->GAlignTuningParams.max_num_features = 100;
    pAlgCreateParams->GAlignTuningParams.min_match_score  = -10;
    pAlgCreateParams->GAlignTuningParams.max_BRIEF_score  = 100;
    pAlgCreateParams->GAlignTuningParams.min_distBW_feats = 10;
    //pAlgCreateParams->GAlignTuningParams.downsamp_ratio   = 2;
    pAlgCreateParams->downsamp_ratio        = 2;

    pAlgCreateParams->svCarBoxParams.CarBoxCenter_x =
        (pAlgCreateParams->SVOutDisplayWidth / 2);
    pAlgCreateParams->svCarBoxParams.CarBoxCenter_y =
        (pAlgCreateParams->SVOutDisplayHeight / 2);
    pAlgCreateParams->svCarBoxParams.CarBox_height =
            pAdaptiveBowlLinkCreateParams->carBoxHeight;
    pAlgCreateParams->svCarBoxParams.CarBox_width =
            pAdaptiveBowlLinkCreateParams->carBoxWidth;

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_AdaptiveBowlMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_AdaptiveBowlMemQuery(pAlgCreateParams, &memRequests, 0);
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {
        if(memRequests.memTab[memTabId].size > SV_ALGLINK_SRMEM_THRESHOLD)
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

    Cache_inv(
            pAlgCreateParams->pLensPrm,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pAlgCreateParams->pLensPrm2D,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    pAlgCreateParams->pLensPrm = pAdaptiveBowlLinkCreateParams->pLensPrm;
    pAlgCreateParams->pLensPrm2D = pAdaptiveBowlLinkCreateParams->pLensPrm2D;

    algHandle = Alg_AdaptiveBowlCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pAdaptiveBowlObj->algHandle = algHandle;

     /* ===============================================================*/
     /* GASGXLUT */
     /* ===============================================================*/
        channelId = 0;
        outputQId = ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT;
        for(frameIdx = 0;
            frameIdx < pAdaptiveBowlObj->algLinkCreateParams
                        .numOutputTables;
            frameIdx++)
        {
            pSystemBuffer         =
                                 &(pAdaptiveBowlObj->buffers[outputQId][frameIdx]);
            pSystemMetaDataBuffer =
                                 &(pAdaptiveBowlObj->AdaptiveBowlLUT[outputQId][frameIdx]);

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSystemBuffer->payload     = pSystemMetaDataBuffer;
            pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
            pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
            pSystemBuffer->chNum       = channelId;

            /*
             * metaBufSize = stride*POINTS_WIDTH*POINTS_HEIGHT*sizeof(float)
             */
            metaBufSize = (9*SV_ALGLINK_3D_PIXEL_POINTS_WIDTH_2MP*
                             SV_ALGLINK_3D_PIXEL_POINTS_HEIGHT_2MP*4);

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

    pAdaptiveBowlObj->frameDropCounter          = 0;

    pAdaptiveBowlObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_AdaptiveBowl");
    UTILS_assert(NULL != pAdaptiveBowlObj->linkStatsInfo);

    pAdaptiveBowlObj->numInputChannels = 1;

    pAdaptiveBowlObj->isFirstFrameRecv     = FALSE;
    pAdaptiveBowlObj->isFirstOPGenerated   = FALSE;

    pAdaptiveBowlObj->newCoordinates       = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of geometric alignment algorithm link
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
Int32 AlgorithmLink_adaptiveBowlProcess(void * pObj)
{
    AlgorithmLink_AdaptiveBowlObj * pAdaptiveBowlObj;
    void                       * algHandle;
    AlgorithmLink_AdaptiveBowlInputQueId    inputQId;
    AlgorithmLink_AdaptiveBowlOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    Int32                        inputStatus;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferGASGXLUT;
    System_Buffer              * pSystemBufferMultisensor;
    System_MetaDataBuffer      * pMultisensorBuffer;
    Bool                         bufDropFlag;
    System_MetaDataBuffer      * pGASGXLUTBuffer;
    void                       * pGASGXLUTBufAddr;
    UInt32                       AdaptiveBowlMode = 0;
    Bool                         algoProcessCallNeeded;
    SV_AdaptiveBowl_CreationParamsStruct       * pAlgCreateParams;
    UltrasonicCapture_MeasurementInfo *ultrasonicInfo;
    Sgx3DsrvLink_UpdateRenderCfgPrms renderCfgPrms;

    AlgorithmLink_AdaptiveBowlCreateParams  * pAdaptiveBowlLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;

    pAdaptiveBowlObj = (AlgorithmLink_AdaptiveBowlObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    pAlgCreateParams = &pAdaptiveBowlObj->algCreateParams;

    linkStatsInfo = pAdaptiveBowlObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle               = pAdaptiveBowlObj->algHandle;
    svAdaptiveBowlStruct *sv = (svAdaptiveBowlStruct*)algHandle;
    pAdaptiveBowlLinkCreateParams = (AlgorithmLink_AdaptiveBowlCreateParams *)
                                    &pAdaptiveBowlObj->algLinkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);


    if(pAdaptiveBowlObj->isFirstFrameRecv==FALSE)
    {
        pAdaptiveBowlObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pAdaptiveBowlObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_ADAPTIVEBOWL_IPQID_MULTISENSOR and process them if output is
     * available
     */
    inputQId = ALGLINK_ADAPTIVEBOWL_IPQID_MULTISENSOR;

    System_getLinksFullBuffers(
        pAdaptiveBowlLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pAdaptiveBowlLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
      for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
      {
        pSystemBufferMultisensor = inputBufList.buffers[bufId];
        UTILS_assert(pSystemBufferMultisensor != NULL);
        pMultisensorBuffer = (System_MetaDataBuffer *)
                             (pSystemBufferMultisensor->payload);

        bufDropFlag = TRUE;

        /*
         * TBD: Put any other checks for input parameter correctness.
         */
        inputStatus = SYSTEM_LINK_STATUS_SOK;

        /*
         * TBD - Currently this link will call algorithm only once for first
         * frame. Logic needs to change in future.
         */

        if (sv->isFirstTime)
        {
            renderCfgPrms.inputChar = '1';
            System_linkControl(
                SYSTEM_LINK_ID_SGX3DSRV_0,
                SYSTEM_COMMON_CMD_UPDATE_RENDER_VIEW,
                &renderCfgPrms,
                sizeof(Sgx3DsrvLink_UpdateRenderCfgPrms),
                TRUE);
        }

        ultrasonicInfo = (UltrasonicCapture_MeasurementInfo*)pMultisensorBuffer->bufAddr[0];

        /* Call to algorithms to determine whether or not to regenerate bowl */
        checkForNewDepthValues(algHandle, ultrasonicInfo);

        /* Comment out for no ultrasonic */
        Cache_inv(pMultisensorBuffer->bufAddr[0],
                  pMultisensorBuffer->metaBufSize[0],
                  Cache_Type_ALLD, TRUE);

        /*
         * For frame to be processed:
         *  - Output buffer will be queried
         *  - If output buffer is available, then algorithm will be called
         */
        if((pAdaptiveBowlObj->isFirstOPGenerated == FALSE || pAdaptiveBowlObj->newCoordinates == TRUE || sv->newDepthValues == TRUE) &&
           inputStatus == SYSTEM_LINK_STATUS_SOK)
        {
          // Clear flag for new coordinates
          pAdaptiveBowlObj->newCoordinates = FALSE;
          sv->newDepthValues = FALSE;

          outputQId = ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT;
          channelId = 0;
          status = AlgorithmLink_getEmptyOutputBuffer(
                                                pObj,
                                                outputQId,
                                                channelId,
                                                &pSysBufferGASGXLUT);

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
          /* ===============================================================*/
          /* Only for 3D SRV mode */
          /* ===============================================================*/
            pGASGXLUTBuffer = (System_MetaDataBuffer *)pSysBufferGASGXLUT->payload;
            pGASGXLUTBufAddr = pGASGXLUTBuffer->bufAddr[0];

            AdaptiveBowlMode = 0;
            algoProcessCallNeeded = TRUE;
            if(linkStatsInfo->linkStats.newDataCmdCount >
               pAdaptiveBowlObj->algLinkCreateParams.ignoreFirstNFrames)
            {
                AdaptiveBowlMode = 3;
                pAdaptiveBowlObj->isFirstOPGenerated = TRUE;
            }

            if(algoProcessCallNeeded == TRUE)
            {
                pSysBufferGASGXLUT->srcTimestamp = pSystemBufferMultisensor->srcTimestamp;
                pSysBufferGASGXLUT->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                // Storing local timestamps in local variables
                uint64_t tempLocalTimestamp = pSysBufferGASGXLUT->linkLocalTimestamp;
                uint64_t tempSrcTimestamp = pSysBufferGASGXLUT->srcTimestamp;

                status = Alg_AdaptiveBowlProcess(
                             algHandle,
                             pMultisensorBuffer->bufAddr[0],
                             &pAdaptiveBowlObj->inPitch[0],
                             pGASGXLUTBufAddr,
                             AdaptiveBowlMode,
                             pAdaptiveBowlLinkCreateParams->calParams.calMatDDRPtr,
                             sv->frontDepthValue,
                             sv->rightDepthValue,
                             sv->backDepthValue,
                             sv->leftDepthValue,
                             pAlgCreateParams->offsetXleft,
                             pAlgCreateParams->offsetXright,
                             pAlgCreateParams->offsetYfront,
                             pAlgCreateParams->offsetYback,
                             sv->isFirstTime,
                             sv->useWideBowl);

                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                sv->isFirstTime = FALSE;

                Cache_wb(pGASGXLUTBuffer->bufAddr[0],
                         pGASGXLUTBuffer->metaBufSize[0],
                         Cache_Type_ALLD,
                         TRUE);

                // Setting local time stamp and src time stamp
                // These get overwritten so correct values are stored in local variables
                pSysBufferGASGXLUT->linkLocalTimestamp = tempLocalTimestamp;
                pSysBufferGASGXLUT->srcTimestamp = tempSrcTimestamp;

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                     pSysBufferGASGXLUT->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                     pSysBufferGASGXLUT->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                     [pSystemBufferMultisensor->chNum].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                     [pSystemBufferMultisensor->chNum].outBufCount[0]++;
            }

            /* ===============================================================*/
            /* Only for 3D SRV mode: GASGXLUT */
            /* ===============================================================*/
            /* Set the third output Q only incase of 3D SRV mode
             * Putting filled buffer into output full buffer for
             * outputQId = ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT
             */
                outputQId = ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT;
                status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                              outputQId,
                                                              pSysBufferGASGXLUT);

                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(
                  pAdaptiveBowlLinkCreateParams->outQueParams[outputQId].nextLink,
                  SYSTEM_CMD_NEW_DATA,
                  NULL);

                /*
                 * Releasing (Free'ing) output buffers, since algorithm does not need
                 * it for any future usage.
                 */

                outputBufListReturn.numBuf     = 1;
                outputBufListReturn.buffers[0] = pSysBufferGASGXLUT;
                AlgorithmLink_releaseOutputBuffer(pObj,
                                                outputQId,
                                                &outputBufListReturn);

            bufDropFlag = FALSE;

        }
        }
        /*
         * Releasing (Free'ing) Input buffers, since algorithm does not need
         * it for any future usage.
         */
        inputQId                      = ALGLINK_ADAPTIVEBOWL_IPQID_MULTISENSOR;
        inputBufListReturn.numBuf     = 1;
        inputBufListReturn.buffers[0] = pSystemBufferMultisensor;
        AlgorithmLink_releaseInputBuffer(
            pObj,
            inputQId,
            pAdaptiveBowlLinkCreateParams->inQueParams[inputQId].prevLinkId,
            pAdaptiveBowlLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
            &inputBufListReturn,
            &bufDropFlag);
      }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for geometric align algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_adaptiveBowlControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_AdaptiveBowlObj        * pAdaptiveBowlObj;
    AlgorithmLink_AdaptiveBowlControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    SV_AdaptiveBowl_CreationParamsStruct       * pAlgCreateParams;

    pAdaptiveBowlObj = (AlgorithmLink_AdaptiveBowlObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pAdaptiveBowlObj->algHandle;

    pAlgCreateParams = &pAdaptiveBowlObj->algCreateParams;

    pAlgLinkControlPrm = (AlgorithmLink_AdaptiveBowlControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */
    switch(pAlgLinkControlPrm->baseClassControl.controlCmd)
    {

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_adaptiveBowlPrintStatistics(pObj, pAdaptiveBowlObj);
            break;
        case ALGORITHM_LINK_CMD_CONFIG:
            pAlgCreateParams->offsetXleft  = pAlgLinkControlPrm->offsetXleft;
            pAlgCreateParams->offsetXright = pAlgLinkControlPrm->offsetXright;
            pAlgCreateParams->offsetYfront = pAlgLinkControlPrm->offsetYfront;
            pAlgCreateParams->offsetYback  = pAlgLinkControlPrm->offsetYback;
            pAdaptiveBowlObj->newCoordinates     = TRUE;
            break;
        default:
            status = Alg_AdaptiveBowlControl(algHandle,
                                                  &(pAdaptiveBowlObj->controlParams)
                                                  );
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for geometric align algorithm link
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
Int32 AlgorithmLink_adaptiveBowlStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for AdaptiveBowl algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_adaptiveBowlDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       metaBufSize;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_AdaptiveBowlObj         * pAdaptiveBowlObj;
    UInt32                            memTabId;
    AlgorithmLink_AdaptiveBowlOutputQueId   outputQId;

    pAdaptiveBowlObj = (AlgorithmLink_AdaptiveBowlObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAdaptiveBowlObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_AdaptiveBowlDelete(pAdaptiveBowlObj->algHandle, &memRequests);

    /*
     * Memory allocations for the requests done by algorithm
     */
    for(memTabId = 0 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        if(memRequests.memTab[memTabId].size > 0)
        {

            if(memRequests.memTab[memTabId].size > SV_ALGLINK_SRMEM_THRESHOLD)
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

    /* ===============================================================*/
    /* GASGXLUT */
    /* ===============================================================*/

        outputQId = ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT;
        for(frameIdx = 0;
            frameIdx < pAdaptiveBowlObj->algLinkCreateParams
                        .numOutputTables;
            frameIdx++)
        {
            pSystemMetaDataBuffer =
                                 &(pAdaptiveBowlObj->AdaptiveBowlLUT[outputQId][frameIdx]);

            metaBufSize = (9*SV_ALGLINK_3D_PIXEL_POINTS_WIDTH_2MP*
                             SV_ALGLINK_3D_PIXEL_POINTS_HEIGHT_2MP*4);

            status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemMetaDataBuffer->bufAddr[0],
                                    metaBufSize);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

    /*
     * Space for Algorithm specific object gets freed here.
     */
    if(sizeof(AlgorithmLink_AdaptiveBowlObj) > SV_ALGLINK_SRMEM_THRESHOLD)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pAdaptiveBowlObj,
                               sizeof(AlgorithmLink_AdaptiveBowlObj));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        free(pAdaptiveBowlObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pAdaptiveBowlObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_adaptiveBowlPrintStatistics(void *pObj,
                       AlgorithmLink_AdaptiveBowlObj *pAdaptiveBowlObj)
{
    UTILS_assert(NULL != pAdaptiveBowlObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAdaptiveBowlObj->linkStatsInfo->linkStats, "ALG_ADAPTIVEBOWL", TRUE);

    Utils_printLatency("ALG_ADAPTIVEBOWL",
                       &pAdaptiveBowlObj->linkStatsInfo->linkLatency,
                       &pAdaptiveBowlObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
