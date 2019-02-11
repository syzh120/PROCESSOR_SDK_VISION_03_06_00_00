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
 * \file gAlignLink_algPlugin.c
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
#include "gAlign3DLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/alg_plugins/commonutils/lens_distortion_correction/ldc_config.h>

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
Int32 AlgorithmLink_gAlign3D_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_gAlign3DCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_gAlign3DProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_gAlign3DControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_gAlign3DStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_gAlign3DDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_GALIGNMENT_3D;
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
Int32 AlgorithmLink_gAlign3DCreate(void * pObj, void * pCreateParams)
{
    void                       * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    System_Buffer              * pSystemBufferCornerLoc;
    System_MetaDataBuffer      * pSystemMetaDataBufferCornerLoc;
    System_LinkInfo              prevLinkInfo;
    AlgorithmLink_GAlign3DOutputQueId   outputQId;
    AlgorithmLink_GAlign3DInputQueId    inputQId;
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

    AlgorithmLink_GAlign3DObj              * pGAlignObj;
    AlgorithmLink_GAlign3DCreateParams     * pGAlignLinkCreateParams;
    SV_GAlign3D_CreationParamsStruct       * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;
    UInt32                                 memTabId;

    pGAlignLinkCreateParams =
        (AlgorithmLink_GAlign3DCreateParams *)pCreateParams;

    Vps_printf("================ GAlign3D Create\n");
    printf("======== GAlign3D Create\n");

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    if(sizeof(AlgorithmLink_GAlign3DObj) > SV_ALGLINK_SRMEM_THRESHOLD)
    {
        pGAlignObj = (AlgorithmLink_GAlign3DObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                       sizeof(AlgorithmLink_GAlign3DObj), 32);
    }
    else
    {
        pGAlignObj = (AlgorithmLink_GAlign3DObj *)
                        malloc(sizeof(AlgorithmLink_GAlign3DObj));
    }

    UTILS_assert(pGAlignObj!=NULL);

    pAlgCreateParams = &pGAlignObj->algCreateParams;

    pOutputQInfo = &pGAlignObj->outputQInfo[0];
    pInputQInfo  = &pGAlignObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pGAlignObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pGAlignObj->algLinkCreateParams),
           (void*)(pGAlignLinkCreateParams),
           sizeof(AlgorithmLink_GAlign3DCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of geometric alignment
     * algorithm link
     */
    if (pGAlignObj->algLinkCreateParams.calmatInputBufferConnected == TRUE)
        numInputQUsed     = ALGLINK_GALIGN3D_IPQID_MAXIPQ;
    else
        numInputQUsed     = ALGLINK_GALIGN3D_IPQID_MAXIPQ-1;

    numOutputQUsed    = ALGLINK_GALIGN3D_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo[ALGLINK_GALIGN3D_IPQID_MULTIVIEW].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    if (numInputQUsed>ALGLINK_GALIGN3D_IPQID_CALMAT)
        pInputQInfo[ALGLINK_GALIGN3D_IPQID_CALMAT].qMode =
            ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_GALIGN3D_OPQID_GALUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_GALIGN3D_OPQID_PIXELSPERCM].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_GALIGN3D_OPQID_GASGXLUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_GALIGN3D_OPQID_GALUT].queInfo.numCh = numChannelsUsed;
    pOutputQInfo[ALGLINK_GALIGN3D_OPQID_PIXELSPERCM].queInfo.numCh = numChannelsUsed;
    pOutputQInfo[ALGLINK_GALIGN3D_OPQID_GASGXLUT].queInfo.numCh = numChannelsUsed;

    // input frames
    inputQId  = ALGLINK_GALIGN3D_IPQID_MULTIVIEW;

    status = System_linkGetInfo(
                pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
                &prevLinkInfo);

    prevLinkQueId =
        pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId;
    pPrevChInfo   =
        &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    prevChInfoFlags    = pPrevChInfo->flags;
    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(NULL);
    }

    pGAlignObj->dataFormat = dataFormat;
    pGAlignObj->inPitch[0] = pPrevChInfo->pitch[0];
    pGAlignObj->inPitch[1] = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pGAlignObj->algLinkCreateParams.maxInputWidth)
       ||
       (pPrevChInfo->height > pGAlignObj->algLinkCreateParams.maxInputHeight)
      )
    {
      UTILS_assert(NULL);
    }

    // calibration matrix
    if (numInputQUsed>ALGLINK_GALIGN3D_IPQID_CALMAT)
    {
        inputQId  = ALGLINK_GALIGN3D_IPQID_CALMAT;

        /* previous link info */
        status = System_linkGetInfo(
                pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
                 &prevLinkInfo);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }


    /*
     * Channel info population for output Q Id - ALGLINK_GALIGN3D_OPQID_GALUT
     * TBD - To check if anything in channel info is needed for meta data op
     */
    outputQId = ALGLINK_GALIGN3D_OPQID_GALUT;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;

    outputQId = ALGLINK_GALIGN3D_OPQID_PIXELSPERCM;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;

    outputQId = ALGLINK_GALIGN3D_OPQID_GASGXLUT;
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


       //Creation parameters for Geometric Alignment, to be updated with the correct value,     Buyue 11/22/2013


    UTILS_assert(pGAlignLinkCreateParams->maxInputHeight <=
                    SV_ALGLINK_INPUT_FRAME_HEIGHT);

    if(ALGLINK_GALIGN3D_INPUTRES_2MP == pGAlignLinkCreateParams->inputRes)
    {
        UTILS_assert(pGAlignLinkCreateParams->maxInputWidth <=
                    SV_ALGLINK_INPUT_FRAME_WIDTH_2MP);
    }
    else
    {
        UTILS_assert(pGAlignLinkCreateParams->maxInputWidth <=
                    SV_ALGLINK_INPUT_FRAME_WIDTH);
    }

    UTILS_assert(pGAlignLinkCreateParams->maxOutputHeight <=
                    SV_ALGLINK_OUTPUT_FRAME_HEIGHT);

    if(ALGLINK_GALIGN3D_OUTPUTRES_2MP == pGAlignLinkCreateParams->outputRes)
    {
        UTILS_assert(pGAlignLinkCreateParams->maxOutputWidth <=
                        SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP);
    }
    else
    {
        UTILS_assert(pGAlignLinkCreateParams->maxOutputWidth <=
                        SV_ALGLINK_OUTPUT_FRAME_WIDTH);
    }

    pAlgCreateParams->SVInCamFrmHeight =
        pGAlignLinkCreateParams->maxInputHeight;
    pAlgCreateParams->SVInCamFrmWidth =
        pGAlignLinkCreateParams->maxInputWidth;
    pAlgCreateParams->SVOutDisplayHeight =
        pGAlignLinkCreateParams->maxOutputHeight;
    pAlgCreateParams->SVOutDisplayWidth =
        pGAlignLinkCreateParams->maxOutputWidth;
    pAlgCreateParams->numCameras =
        pGAlignLinkCreateParams->numViews;

       //To be updated by Pavan, these three parameters should be consistent for All three algorithms, therefore should be passed in
    pAlgCreateParams->numColorChannels      = 3;
    pAlgCreateParams->DMAblockSizeV         = 40;
    pAlgCreateParams->DMAblockSizeH         = 40;

    pAlgCreateParams->saladbowlFocalLength  = 8000;
    pAlgCreateParams->defaultFocalLength    =
                            pGAlignObj->algLinkCreateParams.defaultFocalLength;
    if (pGAlignLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
    {
       pAlgCreateParams->subsampleratio        = 2;
    }
    else
    {
       pAlgCreateParams->subsampleratio        = 4;
    }

    pAlgCreateParams->outputMode = pGAlignLinkCreateParams->svOutputMode; //2D or 3D
    pAlgCreateParams->enablePixelsPerCm = pGAlignLinkCreateParams->enablePixelsPerCm; //use PixelsPerCm output ? 1-yes, 0-no
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
            pGAlignLinkCreateParams->carBoxHeight;
    pAlgCreateParams->svCarBoxParams.CarBox_width =
            pGAlignLinkCreateParams->carBoxWidth;

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_GeometricAlignment3DMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = malloc(
                                            memRequests.memTab[memTabId].size);
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_GeometricAlignment3DMemQuery(pAlgCreateParams, &memRequests, 0);
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

    pAlgCreateParams->pLensPrm = pGAlignLinkCreateParams->pLensPrm;
    pAlgCreateParams->pLensPrm2D = pGAlignLinkCreateParams->pLensPrm2D;

    algHandle = Alg_GeometricAlignment3DCreate(pAlgCreateParams, &memRequests);
    UTILS_assert(algHandle != NULL);

    pGAlignObj->algHandle = algHandle;

    /*
     * Creation of output buffers for output Qs
     *  - Connecting metadata buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
     /* ===============================================================*/
     /* GALUT */
     /* ===============================================================*/
    outputQId = ALGLINK_GALIGN3D_OPQID_GALUT;
    channelId = 0;

    for(frameIdx = 0;
        frameIdx < pGAlignObj->algLinkCreateParams
                    .numOutputTables;
        frameIdx++)
    {
        pSystemBuffer         =
                             &(pGAlignObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =
                             &(pGAlignObj->gAlignLUT[outputQId][frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        if(ALGLINK_GALIGN3D_INPUTRES_2MP == pGAlignObj->algLinkCreateParams.inputRes)
        {
            metaBufSize = SV_ALGLINK_GALUT_SIZE_2MP;
        }
        else
        {
            metaBufSize = SV_ALGLINK_GALUT_SIZE;
        }

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


     /* ===============================================================*/
     /* Only for 3D SRV mode: GASGXLUT */
     /* ===============================================================*/
    if (pGAlignLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
    {
        channelId = 0;
        outputQId = ALGLINK_GALIGN3D_OPQID_GASGXLUT;
        for(frameIdx = 0;
            frameIdx < pGAlignObj->algLinkCreateParams
                        .numOutputTables;
            frameIdx++)
        {
            pSystemBuffer         =
                                 &(pGAlignObj->buffers[outputQId][frameIdx]);
            pSystemMetaDataBuffer =
                                 &(pGAlignObj->gAlignLUT[outputQId][frameIdx]);

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
            metaBufSize = (9*SV_ALGLINK_3D_PIXEL_POINTS_WIDTH*
                             SV_ALGLINK_3D_PIXEL_POINTS_HEIGHT*4);

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

     /* ===============================================================*/
    /*ALGLINK_GALIGN3D_OPQID_PIXELSPERCM*/
    /* ===============================================================*/

    if (pGAlignLinkCreateParams->enablePixelsPerCm)
    {
       outputQId = ALGLINK_GALIGN3D_OPQID_PIXELSPERCM;
       channelId = 0;

       for(frameIdx = 0;
       frameIdx < pGAlignObj->algLinkCreateParams.numOutputTables;
                   //.numCornerTables;
       frameIdx++)
       {
           pSystemBufferCornerLoc         =
                                &(pGAlignObj->buffers[outputQId][frameIdx]);
           pSystemMetaDataBufferCornerLoc =
                                &(pGAlignObj->gAlignLUT[outputQId][frameIdx]);

           /*
            * Properties of pSystemBuffer, which do not get altered during
            * run time (frame exchanges) are initialized here
            */
           pSystemBufferCornerLoc->payload     = pSystemMetaDataBufferCornerLoc;
           pSystemBufferCornerLoc->payloadSize = sizeof(System_MetaDataBuffer);
           pSystemBufferCornerLoc->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
           pSystemBufferCornerLoc->chNum       = channelId;

           metaBufSize = SV_ALGLINK_GA_PIXELSPERCM_SIZE;

           pSystemMetaDataBufferCornerLoc->numMetaDataPlanes = 1;
           pSystemMetaDataBufferCornerLoc->bufAddr[0] =  Utils_memAlloc(
                                                   UTILS_HEAPID_DDR_CACHED_SR,
                                                   metaBufSize,
                                                   ALGORITHMLINK_FRAME_ALIGN);
           pSystemMetaDataBufferCornerLoc->metaBufSize[0]    = metaBufSize;
           pSystemMetaDataBufferCornerLoc->metaFillLength[0] = metaBufSize;
           pSystemMetaDataBufferCornerLoc->flags             = 0;

           UTILS_assert(pSystemMetaDataBufferCornerLoc->bufAddr[0] != NULL);

           AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBufferCornerLoc);
       }
    }

    pGAlignObj->frameDropCounter          = 0;

    pGAlignObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_GALIGN");
    UTILS_assert(NULL != pGAlignObj->linkStatsInfo);

    pGAlignObj->numInputChannels = 1;

    pGAlignObj->isFirstFrameRecv   = FALSE;
    pGAlignObj->isFirstOPGenerated = FALSE;
    pGAlignObj->isCalMatReceived   = FALSE;


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
Int32 AlgorithmLink_gAlign3DProcess(void * pObj)
{
    AlgorithmLink_GAlign3DObj * pGAlignObj;
    void                       * algHandle;
    AlgorithmLink_GAlign3DInputQueId    inputQId;
    AlgorithmLink_GAlign3DOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    Int32                        inputStatus;
    UInt32                       bufId;
    UInt32                       viewId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferGALUT;
    System_Buffer              * pSysBufferGACornerLoc;
    System_Buffer              * pSysBufferGASGXLUT;
    System_Buffer              * pSystemBufferMultiview;
    Bool                         bufDropFlag;
    System_MetaDataBuffer      * pCalMatBuffer;
    System_MetaDataBuffer      * pGALUTBuffer;
    System_MetaDataBuffer        tmpGACornerLocBuffer; /* To avoid KW error */
    System_MetaDataBuffer      * pGACornerLocBuffer = &tmpGACornerLocBuffer;
    System_MetaDataBuffer      * pGASGXLUTBuffer;
    void                       * pGASGXLUTBufAddr;
    UInt32                       gAlignMode = 0;
    Bool                         algoProcessCallNeeded;

    Word32                     * pInCalMatPtr;

    System_VideoFrameCompositeBuffer     * pCompositeBuffer;
    AlgorithmLink_GAlign3DCreateParams  * pGAlignLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;
    System_VideoFrameCompositeBuffer     compositeBufferTmp;
    UInt32 offsetY, offsetUV;

    pGAlignObj = (AlgorithmLink_GAlign3DObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pGAlignObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle               = pGAlignObj->algHandle;
    pGAlignLinkCreateParams = (AlgorithmLink_GAlign3DCreateParams *)
                                    &pGAlignObj->algLinkCreateParams;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);


    if(pGAlignObj->isFirstFrameRecv==FALSE)
    {
        pGAlignObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pGAlignObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    if (pGAlignObj->algLinkCreateParams.calmatInputBufferConnected == TRUE &&
            pGAlignObj->isCalMatReceived == FALSE)
    {
        /*
         * Get Input buffers from previous link for
         * Qid = ALGLINK_GALIGN3D_IPQID_CALMAT and store latest copy locally.
         */
        inputQId = ALGLINK_GALIGN3D_IPQID_CALMAT;

        System_getLinksFullBuffers(
            pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
            pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
            &inputBufList);

        if(inputBufList.numBuf)
        {
            for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
            {
                if(pGAlignObj->isCalMatReceived == FALSE)
                {
                    Word32 i, idx;

                    pGAlignObj->sysBufferCalMat = inputBufList.buffers[bufId];
                    pCalMatBuffer = (System_MetaDataBuffer *) pGAlignObj->sysBufferCalMat->payload;
                    pInCalMatPtr = (Word32 *)pCalMatBuffer->bufAddr[0];

                    pGAlignObj->isCalMatReceived = TRUE;

                    Vps_printf("----PERSMAT in GALIGN 3D ----\n");
                    for (i = 0; i < 4; i++)
                    {
                        idx = i * 12 + 1;

                        Vps_printf("%d %d %d %d %d %d %d %d %d %d %d %d \n",
                                pInCalMatPtr[idx], pInCalMatPtr[idx + 1] , pInCalMatPtr[idx + 2], pInCalMatPtr[idx + 3], pInCalMatPtr[idx + 4], pInCalMatPtr[idx + 5],
                                pInCalMatPtr[idx + 6], pInCalMatPtr[idx + 7], pInCalMatPtr[idx + 8], pInCalMatPtr[idx + 9], pInCalMatPtr[idx + 10], pInCalMatPtr[idx + 11]);
                    }
                    Vps_printf("\n");



                    if (pInCalMatPtr[0] == 1)
                    {
                        //pInCalMatPtr++;
                        memcpy(pGAlignLinkCreateParams->calParams.autoPersMatDDRPtr,
                                pInCalMatPtr,
                                pCalMatBuffer->metaBufSize[0]);

                        pInCalMatPtr = (Word32 *)pGAlignLinkCreateParams->calParams.autoPersMatDDRPtr;
                        Vps_printf("----PERSMAT in GALIGN 3D DDR Ptr ----\n");
                        for (i = 0; i < 4; i++)
                        {
                            idx = i * 12 + 1;

                            Vps_printf("%d %d %d %d %d %d %d %d %d %d %d %d \n",
                                    pInCalMatPtr[idx], pInCalMatPtr[idx + 1] , pInCalMatPtr[idx + 2], pInCalMatPtr[idx + 3], pInCalMatPtr[idx + 4], pInCalMatPtr[idx + 5],
                                    pInCalMatPtr[idx + 6], pInCalMatPtr[idx + 7], pInCalMatPtr[idx + 8], pInCalMatPtr[idx + 9], pInCalMatPtr[idx + 10], pInCalMatPtr[idx + 11]);
                        }
                        Vps_printf("\n");

                        Cache_wb(pGAlignLinkCreateParams->calParams.autoPersMatDDRPtr,
                                 pCalMatBuffer->metaBufSize[0],
                                 Cache_Type_ALLD,
                                 TRUE);
                    }
                }
                // release buffer
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pGAlignObj->sysBufferCalMat;
                bufDropFlag = FALSE;

                AlgorithmLink_releaseInputBuffer(
                        pObj,
                        inputQId,
                        pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
                        pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                        &inputBufListReturn,
                        &bufDropFlag);
            }
        }
    }
    else
    {
        pGAlignObj->isCalMatReceived = TRUE;
    }


    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_GALIGN3D_IPQID_MULTIVIEW and process them if output is
     * available
     */
    inputQId = ALGLINK_GALIGN3D_IPQID_MULTIVIEW;

    System_getLinksFullBuffers(
        pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
      for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
      {
        pSystemBufferMultiview = inputBufList.buffers[bufId];
        pCompositeBuffer = (System_VideoFrameCompositeBuffer *)
                                pSystemBufferMultiview->payload;

        bufDropFlag = TRUE;

        /*
         * TBD: Put any other checks for input parameter correctness.
         */
        inputStatus = SYSTEM_LINK_STATUS_SOK;

        if(pSystemBufferMultiview->bufType !=
                SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
        {
            inputStatus = SYSTEM_LINK_STATUS_EFAIL;
            linkStatsInfo->linkStats.inBufErrorCount++;
        }

        /*
         * TBD - Currently this link will call algorithm only once for first
         * frame. Logic needs to change in future.
         */

        /*
         * For frame to be processed:
         *  - Output buffer will be queried
         *  - If output buffer is available, then algorithm will be called
         */

        if(pGAlignObj->isFirstOPGenerated == FALSE &&
           inputStatus == SYSTEM_LINK_STATUS_SOK  && pGAlignObj->isCalMatReceived == TRUE)
        {

          outputQId = ALGLINK_GALIGN3D_OPQID_GALUT;
          channelId = 0;
          status = AlgorithmLink_getEmptyOutputBuffer(
                                            pObj,
                                            outputQId,
                                            channelId,
                                            &pSysBufferGALUT);

          /* ===============================================================*/
          /* Set the second output Q only incase of 3D SRV mode */
          /* ===============================================================*/
          if ((status == SYSTEM_LINK_STATUS_SOK) &&
              (pGAlignObj->algLinkCreateParams.svOutputMode ==
                                               ALGORITHM_LINK_SRV_OUTPUT_3D))
          {
              outputQId = ALGLINK_GALIGN3D_OPQID_GASGXLUT;
              channelId = 0;
              status = AlgorithmLink_getEmptyOutputBuffer(
                                                pObj,
                                                outputQId,
                                                channelId,
                                                &pSysBufferGASGXLUT);

              if(status != SYSTEM_LINK_STATUS_SOK)
              {
                /*
                 * If output buffer is not available,
                 * then free-up the previously allocated output buffer
                 */
                AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                   ALGLINK_GALIGN3D_OPQID_GALUT,
                                                   pSysBufferGALUT);

              }
          }

          /* ===============================================================*/
          /* Set the second output Q2 only incase of Ultrasonic */
          /* ===============================================================*/
          if ((status == SYSTEM_LINK_STATUS_SOK) &&
              pGAlignObj->algLinkCreateParams.enablePixelsPerCm)
          {
            outputQId = ALGLINK_GALIGN3D_OPQID_PIXELSPERCM;
            channelId = 0;
            status = AlgorithmLink_getEmptyOutputBuffer(
                                              pObj,
                                              outputQId,
                                              channelId,
                                              &pSysBufferGACornerLoc);

              if(status != SYSTEM_LINK_STATUS_SOK)
              {
                /*
                 * If output buffer is not available,
                 * then free-up the previously allocated output buffer
                 */
                AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                   ALGLINK_GALIGN3D_OPQID_GALUT,
                                                   pSysBufferGALUT);
                if (pGAlignObj->algLinkCreateParams.svOutputMode ==
                        ALGORITHM_LINK_SRV_OUTPUT_3D)
                    AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                   ALGLINK_GALIGN3D_OPQID_GASGXLUT,
                                                   pSysBufferGASGXLUT);
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
            pSysBufferGALUT->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
            pSysBufferGALUT->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
            pGALUTBuffer = (System_MetaDataBuffer *)pSysBufferGALUT->payload;


          /* ===============================================================*/
          /* Only for 3D SRV mode */
          /* ===============================================================*/
            pGASGXLUTBufAddr = NULL;
            if (pGAlignObj->algLinkCreateParams.svOutputMode ==
                                                ALGORITHM_LINK_SRV_OUTPUT_3D)
            {
                pSysBufferGASGXLUT->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
                pSysBufferGASGXLUT->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                pGASGXLUTBuffer = (System_MetaDataBuffer *)pSysBufferGASGXLUT->payload;
                pGASGXLUTBufAddr = pGASGXLUTBuffer->bufAddr[0];
            }

          /* ===============================================================*/
          /* Only for Ultrasound */
          /* ===============================================================*/
            if (pGAlignObj->algLinkCreateParams.enablePixelsPerCm)
            {
                pSysBufferGACornerLoc->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
                pSysBufferGACornerLoc->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
                pGACornerLocBuffer = (System_MetaDataBuffer *)pSysBufferGACornerLoc->payload;
                UTILS_assert(pGACornerLocBuffer != NULL);
            }


            for(viewId = 0; viewId < SV_ALGLINK_MAX_NUM_VIEWS; viewId++)
            {
             Cache_inv(pCompositeBuffer->bufAddr[0][viewId],
              (pGAlignObj->algLinkCreateParams.maxInputWidth*pGAlignObj->algLinkCreateParams.maxInputHeight),
              Cache_Type_ALLD, TRUE);
             Cache_inv(pCompositeBuffer->bufAddr[1][viewId],
              ((pGAlignObj->algLinkCreateParams.maxInputWidth*pGAlignObj->algLinkCreateParams.maxInputHeight)/2),
              Cache_Type_ALLD, TRUE);
            }

            Vps_printf (" calMode = %d\n",\
                            pGAlignObj->algLinkCreateParams.calParams.calMode);

            switch (pGAlignObj->algLinkCreateParams.calParams.calMode)
            {
                default:
                case ALGLINK_GALIGN3D_CALMODE_DEFAULT:
                    gAlignMode = 0;
                    algoProcessCallNeeded = TRUE;
                    pGAlignObj->isFirstOPGenerated = TRUE;
                    break;

                case ALGLINK_GALIGN3D_CALMODE_USERGALUT:
                    algoProcessCallNeeded = FALSE;

                    Cache_inv(
                            pGAlignLinkCreateParams->calParams.gaLUTDDRPtr,
                            pGALUTBuffer->metaBufSize[0],
                            Cache_Type_ALLD,
                            TRUE);

                    memcpy(pGALUTBuffer->bufAddr[0],
                           pGAlignLinkCreateParams->calParams.gaLUTDDRPtr,
                           pGALUTBuffer->metaBufSize[0]
                          );

                    pGAlignObj->isFirstOPGenerated = TRUE;
                    break;

                case ALGLINK_GALIGN3D_CALMODE_FORCE_DEFAULTPERSMATRIX:
                    gAlignMode = 0;
                    algoProcessCallNeeded = TRUE;
                    if(linkStatsInfo->linkStats.newDataCmdCount >
                        pGAlignObj->algLinkCreateParams.ignoreFirstNFrames)
                    {
                        gAlignMode = 1;
                        pGAlignObj->isFirstOPGenerated = TRUE;
                    }
                    break;

                case ALGLINK_GALIGN3D_CALMODE_FORCE_USERPERSMATRIX:
                    gAlignMode = 0;
                    algoProcessCallNeeded = TRUE;
                    if(linkStatsInfo->linkStats.newDataCmdCount >
                        pGAlignObj->algLinkCreateParams.ignoreFirstNFrames)
                    {
                        gAlignMode = 2;
                        pGAlignObj->isFirstOPGenerated = TRUE;
                    }
                    break;

                case ALGLINK_GALIGN3D_CALMODE_FORCE_USERGASGXLUT:
                    gAlignMode = 0;
                    algoProcessCallNeeded = FALSE;
                    pGAlignObj->isFirstOPGenerated = TRUE;
                    break;
            }

            if(algoProcessCallNeeded == TRUE)
            {
                if (NULL != \
                        pGAlignLinkCreateParams->calParams.autoPersMatDDRPtr)
                {
                    Cache_inv(
                          pGAlignLinkCreateParams->calParams.autoPersMatDDRPtr,
                          256U,
                          Cache_Type_ALLD,
                          TRUE);
                }

                compositeBufferTmp = *pCompositeBuffer;
                if ((compositeBufferTmp.chInfo.startX!=0) || (compositeBufferTmp.chInfo.startY!=0))
                {
                    offsetY  = compositeBufferTmp.chInfo.pitch[0]*compositeBufferTmp.chInfo.startY
                             + compositeBufferTmp.chInfo.startX;
                    offsetUV = compositeBufferTmp.chInfo.pitch[1]*compositeBufferTmp.chInfo.startY/2
                             + compositeBufferTmp.chInfo.startX;
                    compositeBufferTmp.bufAddr[0][0] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][0] + offsetY);
                    compositeBufferTmp.bufAddr[0][1] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][1] + offsetY);
                    compositeBufferTmp.bufAddr[0][2] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][2] + offsetY);
                    compositeBufferTmp.bufAddr[0][3] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][3] + offsetY);
                    compositeBufferTmp.bufAddr[1][0] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][0] + offsetUV);
                    compositeBufferTmp.bufAddr[1][1] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][1] + offsetUV);
                    compositeBufferTmp.bufAddr[1][2] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][2] + offsetUV);
                    compositeBufferTmp.bufAddr[1][3] =
                        (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][3] + offsetUV);
                }
                status = Alg_GeometricAlignment3DProcess(
                             algHandle,
                             &compositeBufferTmp,
                             &pGAlignObj->inPitch[0],
                             pGALUTBuffer->bufAddr[0],
                             pGASGXLUTBufAddr,
                             pGAlignLinkCreateParams->calParams.persMatDDRPtr,
                             pGAlignLinkCreateParams->calParams.autoPersMatDDRPtr,
                             pGACornerLocBuffer->bufAddr[0],
                             gAlignMode);
                             //pGAlignObj->dataFormat);


                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }

            Cache_wb(pGALUTBuffer->bufAddr[0],
                     pGALUTBuffer->metaBufSize[0],
                     Cache_Type_ALLD,
                     TRUE);

            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                pSysBufferGALUT->linkLocalTimestamp);
            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pSysBufferGALUT->srcTimestamp);


          /* ===============================================================*/
          /* Only for 3D SRV mode */
          /* ===============================================================*/
            if (pGAlignObj->algLinkCreateParams.svOutputMode ==
                                                ALGORITHM_LINK_SRV_OUTPUT_3D)
            {
                Cache_wb(pGASGXLUTBuffer->bufAddr[0],
                         pGASGXLUTBuffer->metaBufSize[0],
                         Cache_Type_ALLD,
                         TRUE);

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysBufferGASGXLUT->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysBufferGASGXLUT->srcTimestamp);
            }

          /* ===============================================================*/
          /* Only for Ultrasound */
          /* ===============================================================*/
             if (pGAlignObj->algLinkCreateParams.enablePixelsPerCm)
              {
                  Cache_wb(pGACornerLocBuffer->bufAddr[0],
                           pGACornerLocBuffer->metaBufSize[0],
                           Cache_Type_ALLD,
                           TRUE);

                  Utils_updateLatency(&linkStatsInfo->linkLatency,
                                      pSysBufferGACornerLoc->linkLocalTimestamp);
                  Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                      pSysBufferGACornerLoc->srcTimestamp);
              }
            /*
             * For gAlignMode of 1 and 2, GA algo will generate new tables.
             * Storing these tables in use case provided buffers
             *  1. GALUT table is copied here
             *  2. Perspective matrix will be directly updated by algo into
             *     use case provided buffer. Just doing cache wb here.
             */

            if(gAlignMode == 1 || gAlignMode == 2)
            {
                memcpy(pGAlignLinkCreateParams->calParams.gaLUTDDRPtr,
                       pGALUTBuffer->bufAddr[0],
                       pGALUTBuffer->metaBufSize[0]
                      );

                Cache_wb(pGAlignLinkCreateParams->calParams.gaLUTDDRPtr,
                         pGALUTBuffer->metaBufSize[0],
                         Cache_Type_ALLD,
                         TRUE
                        );

                Cache_wb(pGAlignLinkCreateParams->calParams.persMatDDRPtr,
                         256,
                         Cache_Type_ALLD,
                         TRUE);
            }


            linkStatsInfo->linkStats.chStats
                  [pSystemBufferMultiview->chNum].inBufProcessCount++;
            linkStatsInfo->linkStats.chStats
                  [pSystemBufferMultiview->chNum].outBufCount[0]++;

            /* ===============================================================*/
            /* GALUT */
            /* ===============================================================*/

            /*
             * Putting filled buffer into output full buffer for
             * outputQId = ALGLINK_GALIGN3D_OPQID_GALUT
             */
            outputQId = ALGLINK_GALIGN3D_OPQID_GALUT;
            status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                          outputQId,
                                                          pSysBufferGALUT);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            /*
             * Informing next link that a new data has peen put for its
             * processing
             */
            System_sendLinkCmd(
              pGAlignLinkCreateParams->outQueParams[outputQId].nextLink,
              SYSTEM_CMD_NEW_DATA,
              NULL);

            /*
             * Releasing (Free'ing) output buffers, since algorithm does not need
             * it for any future usage.
             */

            outputBufListReturn.numBuf     = 1;
            outputBufListReturn.buffers[0] = pSysBufferGALUT;
            AlgorithmLink_releaseOutputBuffer(pObj,
                                            outputQId,
                                            &outputBufListReturn);




            /* ===============================================================*/
            /* Only for 3D SRV mode: GASGXLUT */
            /* ===============================================================*/
            /* Set the third output Q only incase of 3D SRV mode
             * Putting filled buffer into output full buffer for
             * outputQId = ALGLINK_GALIGN3D_OPQID_GASGXLUT
             */
            if (pGAlignObj->algLinkCreateParams.svOutputMode ==
                                                ALGORITHM_LINK_SRV_OUTPUT_3D)
            {
                outputQId = ALGLINK_GALIGN3D_OPQID_GASGXLUT;
                status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                              outputQId,
                                                              pSysBufferGASGXLUT);

                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(
                  pGAlignLinkCreateParams->outQueParams[outputQId].nextLink,
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
            }

            /* ===============================================================*/
                    /* ALGLINK_GALIGN3D_OPQID_PIXELSPERCM */
                    /* ===============================================================*/
                    /* Set the second output Q only incase of Ultrasound
                     * Putting filled buffer into output full buffer for
                     * outputQId = ALGLINK_GALIGN3D_OPQID_PIXELSPERCM
                     */
                    if (pGAlignObj->algLinkCreateParams.enablePixelsPerCm)
                    {
                        outputQId = ALGLINK_GALIGN3D_OPQID_PIXELSPERCM;
                        if ((pGAlignObj->isFirstOPGenerated == TRUE) && (gAlignMode == 1 || gAlignMode == 2) )
                        {
                            status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                                          outputQId,
                                                                          pSysBufferGACornerLoc);
                            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                            /*
                             * Informing next link that a new data has peen put for its
                             * processing
                            */
                            System_sendLinkCmd(
                            pGAlignLinkCreateParams->outQueParams[outputQId].nextLink,
                            SYSTEM_CMD_NEW_DATA,
                             NULL);

                            /*
                             * Releasing (Free'ing) output buffers, since algorithm does not need
                             * it for any future usage.
                            */

                            outputBufListReturn.numBuf     = 1;
                            outputBufListReturn.buffers[0] = pSysBufferGACornerLoc;
                            AlgorithmLink_releaseOutputBuffer(pObj,
                                                              outputQId,
                                                              &outputBufListReturn);
                        }
                        else
                        {
                            AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                               outputQId,
                                                               pSysBufferGACornerLoc);
                        }

                    }

            bufDropFlag = FALSE;
          }

        } /* if(pGAlignObj->isFirstOPGenerated == FALSE) */

        /*
         * Releasing (Free'ing) Input buffers, since algorithm does not need
         * it for any future usage.
         */
        inputQId                      = ALGLINK_GALIGN3D_IPQID_MULTIVIEW;
        inputBufListReturn.numBuf     = 1;
        inputBufListReturn.buffers[0] = pSystemBufferMultiview;
        AlgorithmLink_releaseInputBuffer(
            pObj,
            inputQId,
            pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkId,
            pGAlignLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
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

Int32 AlgorithmLink_gAlign3DControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_GAlign3DObj        * pGAlignObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pGAlignObj = (AlgorithmLink_GAlign3DObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle  = pGAlignObj->algHandle;

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
            AlgorithmLink_gAlign3DPrintStatistics(pObj, pGAlignObj);
            break;

        default:
            status = Alg_GeometricAlignment3DControl(algHandle,
                                                  &(pGAlignObj->controlParams)
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
Int32 AlgorithmLink_gAlign3DStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for gAlign algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_gAlign3DDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       metaBufSize;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_GAlign3DObj         * pGAlignObj;
    UInt32                            memTabId;
    AlgorithmLink_GAlign3DOutputQueId   outputQId;

    pGAlignObj = (AlgorithmLink_GAlign3DObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pGAlignObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_GeometricAlignment3DDelete(pGAlignObj->algHandle, &memRequests);

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

    /*
     * Deletion of output buffers for output Qs
     */
    /* ===============================================================*/
    /* GALUT */
    /* ===============================================================*/
    outputQId = ALGLINK_GALIGN3D_OPQID_GALUT;
    for(frameIdx = 0;
        frameIdx < pGAlignObj->algLinkCreateParams
                    .numOutputTables;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pGAlignObj->gAlignLUT[outputQId][frameIdx]);

        if(ALGLINK_GALIGN3D_INPUTRES_2MP == pGAlignObj->algLinkCreateParams.inputRes)
        {
            metaBufSize = SV_ALGLINK_GALUT_SIZE_2MP;
        }
        else
        {
            metaBufSize = SV_ALGLINK_GALUT_SIZE;
        }

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                metaBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /* ===============================================================*/
    /* Only for 3D SRV mode: GASGXLUT */
    /* ===============================================================*/
    if (pGAlignObj->algLinkCreateParams.svOutputMode ==
                                        ALGORITHM_LINK_SRV_OUTPUT_3D)
    {
        outputQId = ALGLINK_GALIGN3D_OPQID_GASGXLUT;
        for(frameIdx = 0;
            frameIdx < pGAlignObj->algLinkCreateParams
                        .numOutputTables;
            frameIdx++)
        {
            pSystemMetaDataBuffer =
                                 &(pGAlignObj->gAlignLUT[outputQId][frameIdx]);

            metaBufSize = (9*SV_ALGLINK_3D_PIXEL_POINTS_WIDTH*
                             SV_ALGLINK_3D_PIXEL_POINTS_HEIGHT*4);

            status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemMetaDataBuffer->bufAddr[0],
                                    metaBufSize);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    /* ===============================================================*/
    /* ALGLINK_GALIGN3D_OPQID_PIXELSPERCM*/
    /* ===============================================================*/
    if (pGAlignObj->algLinkCreateParams.enablePixelsPerCm)
    {
        outputQId = ALGLINK_GALIGN3D_OPQID_PIXELSPERCM;
        for(frameIdx = 0;
            frameIdx < pGAlignObj->algLinkCreateParams
                        .numOutputTables;
            frameIdx++)
        {
            pSystemMetaDataBuffer =
                                 &(pGAlignObj->gAlignLUT[outputQId][frameIdx]);

            metaBufSize = SV_ALGLINK_GA_PIXELSPERCM_SIZE;

            status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemMetaDataBuffer->bufAddr[0],
                                    metaBufSize);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    /*
     * Space for Algorithm specific object gets freed here.
     */
    if(sizeof(AlgorithmLink_GAlign3DObj) > SV_ALGLINK_SRMEM_THRESHOLD)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                               pGAlignObj,
                               sizeof(AlgorithmLink_GAlign3DObj));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        free(pGAlignObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pGAlignObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_gAlign3DPrintStatistics(void *pObj,
                       AlgorithmLink_GAlign3DObj *pGAlignObj)
{
    UTILS_assert(NULL != pGAlignObj->linkStatsInfo);

    Utils_printLinkStatistics(&pGAlignObj->linkStatsInfo->linkStats, "ALG_GALIGN3D", TRUE);

    Utils_printLatency("ALG_GALIGN3D",
                       &pGAlignObj->linkStatsInfo->linkLatency,
                       &pGAlignObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
