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
 * \file    radarDrawFFTHeatMap.c
 *
 * \brief  This file contains algorithm functions for drawing the radar related
 *         metadata output on the display.
 *
 * \version 0.0 (Oct 2016) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "radarDrawFFTHeatMap_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarDrawFFTHeatMap_fxns =
{
    &AlgorithmFxn_RadarDrawFFTHeatMapCreate,
    &AlgorithmFxn_RadarDrawFFTHeatMapProcess,
    &AlgorithmFxn_RadarDrawFFTHeatMapControl,
    &AlgorithmFxn_RadarDrawFFTHeatMapDelete
};

/**
 *******************************************************************************
 *
 * \brief Implementation of get functions for the algorithm functions
 *
 *        This function will be called to get the pointer to the table of
 *        functions which correspond to this algorithm.
 *
 * \return  AlgRadarProcessFxns_FxnTable pointer.
 *
 *******************************************************************************
 */
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDrawFFTHeatMap_getFunctions(void)
{
    return &gAlgorithmFxn_RadarDrawFFTHeatMap_fxns;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for radar draw
 *
 *  \param createParams Create Parameters corresponding to the algorithm
 *                      function.
 *
 *  \param opParams     These parameters are provided from the algorithm fxn to
 *                      the alg plugin to allow for the alg plugin to know
 *                      alg function specific requirements with respect to
 *                      output buffer size and type.
 *
 *  \return algHandle   This function is expected to allocate memory for the
 *                      algorithm handle. This handle is later used by the alg
 *                      function during process and delete calls.
 *
 *******************************************************************************
 */
void * AlgorithmFxn_RadarDrawFFTHeatMapCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams      * pLinkCreateParams;
    System_LinkChInfo * pOutChInfo;
    Int32 status;
    Utils_DmaChCreateParams dmaParams;
    AlgorithmFxn_RadarDrawFFTHeatMap_Obj * pObjectDrawFFTHeatMapObj;
    UInt32 chId;
    UInt32                    prevLinkQueId;
    System_LinkInfo           prevLinkInfo;

    pObjectDrawFFTHeatMapObj = (AlgorithmFxn_RadarDrawFFTHeatMap_Obj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarDrawFFTHeatMap_Obj), 32);
    UTILS_assert(pObjectDrawFFTHeatMapObj != NULL);

    pLinkCreateParams = (AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *)createParams;
    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pObjectDrawFFTHeatMapObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarDrawFFTHeatMapCreateParams)
           );

    /* Fill the output buffer information */
    for (chId = 0; chId < SYSTEM_MAX_CH_PER_OUT_QUE; chId++)
    {
        pOutChInfo          = &opParams->outputChannelInfo[chId];

        pOutChInfo->height = pLinkCreateParams->outBufHeight;
        pOutChInfo->width  = pLinkCreateParams->outBufWidth;
        pOutChInfo->startX = 0;
        pOutChInfo->startY = 0;
        pOutChInfo->flags  = 0;

        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
                                                pOutChInfo->flags,
                                                SYSTEM_SF_PROGRESSIVE);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(
                                                pOutChInfo->flags,
                                                SYSTEM_MT_NONTILEDMEM);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                                                pOutChInfo->flags,
                                                SYSTEM_DF_BGR16_565);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
                                                pOutChInfo->flags,
                                                SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
        pOutChInfo->pitch[0] = 2 * VpsUtils_align(pOutChInfo->width,
                                              VPS_BUFFER_ALIGNMENT);
        pOutChInfo->pitch[1] = pOutChInfo->pitch[0];
        pOutChInfo->pitch[2] = pOutChInfo->pitch[0];
        /* buffer size for YUV422 data */
        pObjectDrawFFTHeatMapObj->outBufferSize = pOutChInfo->pitch[0] *
                          pOutChInfo->height;
        opParams->outputBufferSize[chId] = pObjectDrawFFTHeatMapObj->outBufferSize;
    }

    opParams->outputBufferType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
    prevLinkQueId = createParams->inQueParams.prevLinkQueId;
    status = System_linkGetInfo(createParams->inQueParams.prevLinkId, &prevLinkInfo);
    opParams->numOutputCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    pObjectDrawFFTHeatMapObj->backgroundBufAddr = (UInt32) Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        pObjectDrawFFTHeatMapObj->outBufferSize,
                                        128);
    pObjectDrawFFTHeatMapObj->prevDrawnBufAddr = (UInt32) Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        pObjectDrawFFTHeatMapObj->outBufferSize,
                                        128);
    /* Draw Create and set up functions */
    status = Draw2D_create(&pObjectDrawFFTHeatMapObj->draw2DHndl);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Dummy address value, that is overridden later */
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.bufAddr[0]  = 0xFFFF;
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.bufAddr[1]  = 0xFFFF;

    pObjectDrawFFTHeatMapObj->draw2DBufInfo.bufWidth    = pOutChInfo->width;
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.bufHeight   = pOutChInfo->height;
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.bufPitch[0] = pOutChInfo->pitch[0];
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.bufPitch[1] = pOutChInfo->pitch[1];
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.transperentColor = DRAW2D_TRANSPARENT_COLOR;
    pObjectDrawFFTHeatMapObj->draw2DBufInfo.transperentColorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;

    status = Draw2D_setBufInfo(pObjectDrawFFTHeatMapObj->draw2DHndl,
                                &pObjectDrawFFTHeatMapObj->draw2DBufInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Draw2D_updateBufAddr(pObjectDrawFFTHeatMapObj->draw2DHndl,
                         &pObjectDrawFFTHeatMapObj->backgroundBufAddr);
    /*
     * Create DMA channel
     */
    Utils_DmaChCreateParams_Init(&dmaParams);

    status = Utils_dmaCreateCh(
                                &pObjectDrawFFTHeatMapObj->copyFramesDmaObj,
                                &dmaParams
                               );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    pObjectDrawFFTHeatMapObj->currProfileId = 0U;

    return (void *) pObjectDrawFFTHeatMapObj;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process function for radar draw
 *
 *  \param  alg_handle      Algorithm Handle which was created during the create
 *                          algorithm function call.
 *  \param  in_buf          Input buffer pointer.
 *  \param  out_buf         Output buffer pointer.
 *
 *  \return status          Status of the success or failure of the process
 *                          operations.
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarDrawFFTHeatMapProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDrawFFTHeatMap_Obj           * pObjectDrawFFTHeatMapObj;
    System_VideoFrameBuffer             * pVidInBuf;
    System_VideoFrameBuffer             * pVidOutBuf;
    System_MetaDataBuffer               * pMetadataBuffer;

    pObjectDrawFFTHeatMapObj = (AlgorithmFxn_RadarDrawFFTHeatMap_Obj *)alg_handle;

    pVidInBuf = (System_VideoFrameBuffer *)in_buf->payload;
    pVidOutBuf = (System_VideoFrameBuffer *)out_buf->payload;
    pMetadataBuffer = (System_MetaDataBuffer *) pVidInBuf->metaBufAddr;


    status = RadarDrawFFTHeatMap_processData(
                   pObjectDrawFFTHeatMapObj,
                   pVidInBuf,
                   pVidOutBuf,
                   (AlgorithmFxn_RadarFftBuffDescriptor *)pMetadataBuffer);
    return status;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Control function for radar draw
 *
 *  \param  alg_handle      Algorithm Handle which was created during the create
 *  \param  controlParams   Control parameters which can change the algorithm
 *                          parameters at run time.
 *
 *  \return status          Status of the success or failure of the control
 *                          operations.
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarDrawFFTHeatMapControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    AlgorithmLink_ControlParams * pAlgLinkControlPrm;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDrawFFTHeatMap_Obj * pObjectDrawFFTHeatMapObj;

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)controlParams;
    if(pAlgLinkControlPrm->size !=
        sizeof(AlgorithmFxn_RadarDrawFFTHeatMapControlParams))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        AlgorithmFxn_RadarDrawFFTHeatMapControlParams * pPrms =
        (AlgorithmFxn_RadarDrawFFTHeatMapControlParams *) controlParams;
        pObjectDrawFFTHeatMapObj = (AlgorithmFxn_RadarDrawFFTHeatMap_Obj *)alg_handle;
        pObjectDrawFFTHeatMapObj->currProfileId = pPrms->profileId;
        pObjectDrawFFTHeatMapObj->algLinkCreateParams.rangeRes[pPrms->profileId] = pPrms->rangeRes;
        pObjectDrawFFTHeatMapObj->algLinkCreateParams.velocityRes[pPrms->profileId] = pPrms->velocityRes;
        pObjectDrawFFTHeatMapObj->firstTime = 0;
    }
    return status;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Delete function for radar draw
 *
 *  \param  alg_handle  Algorithm Handle which was created during the create
 *                      algorithm function call.
 *
 *  \return status      Status of the success or failure of the process
 *                      operations.
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarDrawFFTHeatMapDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDrawFFTHeatMap_Obj                   * pObjectDrawFFTHeatMapObj;

    pObjectDrawFFTHeatMapObj = (AlgorithmFxn_RadarDrawFFTHeatMap_Obj *)alg_handle;

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           (Ptr) pObjectDrawFFTHeatMapObj->backgroundBufAddr,
                           pObjectDrawFFTHeatMapObj->outBufferSize);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           (Ptr) pObjectDrawFFTHeatMapObj->prevDrawnBufAddr,
                           pObjectDrawFFTHeatMapObj->outBufferSize);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_dmaDeleteCh(&pObjectDrawFFTHeatMapObj->copyFramesDmaObj);

    status = Draw2D_delete(pObjectDrawFFTHeatMapObj->draw2DHndl);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                  pObjectDrawFFTHeatMapObj,
                  sizeof(AlgorithmFxn_RadarDrawFFTHeatMap_Obj)
                    );

    return status;
}
