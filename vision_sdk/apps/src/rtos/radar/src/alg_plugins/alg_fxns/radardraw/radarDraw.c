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
 * \file    radarDraw.c
 *
 * \brief  This file contains algorithm functions for drawing the radar related
 *         metadata output on the display.
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "radarDraw_priv.h"

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarDraw_fxns =
{
    &AlgorithmFxn_RadarDrawCreate,
    &AlgorithmFxn_RadarDrawProcess,
    &AlgorithmFxn_RadarDrawControl,
    &AlgorithmFxn_RadarDrawDelete
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
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDraw_getFunctions(void)
{
    return &gAlgorithmFxn_RadarDraw_fxns;
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
void * AlgorithmFxn_RadarDrawCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    Utils_DmaChCreateParams dmaParams;
    AlgorithmFxn_RadarDrawCreateParams      * pLinkCreateParams;
    UInt32 radius;
    UInt32 offset;
    System_LinkChInfo * pOutChInfo;
    AlgorithmFxn_RadarDrawObj * pObjectDrawObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;
    UInt32                    prevLinkQueId;
    System_LinkInfo           prevLinkInfo;

    pObjectDrawObj = (AlgorithmFxn_RadarDrawObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarDrawObj), 32);
    UTILS_assert(pObjectDrawObj != NULL);

    pLinkCreateParams = (AlgorithmFxn_RadarDrawCreateParams *)createParams;
    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pObjectDrawObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarDrawCreateParams)
           );

    /* Fill the output buffer information */
    for (chId = 0; chId < SYSTEM_MAX_CH_PER_OUT_QUE; chId++)
    {
        pOutChInfo          = &opParams->outputChannelInfo[chId];

        pOutChInfo->height = pLinkCreateParams->imgFrameHeight;
        pOutChInfo->width  = pLinkCreateParams->imgFrameWidth;
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
        pObjectDrawObj->pitch = pOutChInfo->pitch[0];

        pObjectDrawObj->outBufferSize_y = pOutChInfo->pitch[0] *
                          pOutChInfo->height;
        opParams->outputBufferSize[chId] = pObjectDrawObj->outBufferSize_y;
    }
    opParams->outputBufferType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
    prevLinkQueId = createParams->inQueParams.prevLinkQueId;
    status = System_linkGetInfo(createParams->inQueParams.prevLinkId, &prevLinkInfo);
    opParams->numOutputCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    /* Prepare background buffer which will be copied over every time a new
     * frame has to be drawn.
     */
    pObjectDrawObj->backgroundBufAddr = (UInt32) Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        pObjectDrawObj->outBufferSize_y,
                                        128);
    pObjectDrawObj->prevDrawnBuffer = (UInt32) Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        pObjectDrawObj->outBufferSize_y,
                                        128);
    pObjectDrawObj->currProfileId = 0;

    /* Draw Create and set up functions */
    status = Draw2D_create(&pObjectDrawObj->draw2DHndl);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Dummy address value, that is overridden later */
    pObjectDrawObj->draw2DBufInfo.bufAddr[0]  = 0xFFFF;
    pObjectDrawObj->draw2DBufInfo.bufAddr[1]  = 0xFFFF;

    pObjectDrawObj->draw2DBufInfo.bufWidth    = pOutChInfo->width;
    pObjectDrawObj->draw2DBufInfo.bufHeight   = pOutChInfo->height;
    pObjectDrawObj->draw2DBufInfo.bufPitch[0] = pOutChInfo->pitch[0];
    pObjectDrawObj->draw2DBufInfo.bufPitch[1] = pOutChInfo->pitch[1];
    pObjectDrawObj->draw2DBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;//SYSTEM_DF_BGRA16_4444;
    pObjectDrawObj->draw2DBufInfo.transperentColor = DRAW2D_TRANSPARENT_COLOR;
    pObjectDrawObj->draw2DBufInfo.transperentColorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;

    status = Draw2D_setBufInfo(pObjectDrawObj->draw2DHndl,
                                &pObjectDrawObj->draw2DBufInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pObjectDrawObj->centerX = pOutChInfo->width/2;
    pObjectDrawObj->centerY = (pOutChInfo->height*9)/10;
    pObjectDrawObj->radius = (pOutChInfo->height*8)/10;
    pObjectDrawObj->angle = 30;
    pObjectDrawObj->scale = pLinkCreateParams->scale;
    /*
     * Create DMA channel
     */
    Utils_DmaChCreateParams_Init(&dmaParams);

    status = Utils_dmaCreateCh(
                                &pObjectDrawObj->copyFramesDmaObj,
                                &dmaParams
                               );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    RadarDraw_sinFillTable();

    /* Save the background to a buffer */
    Draw2D_updateBufAddr(pObjectDrawObj->draw2DHndl,
                         &pObjectDrawObj->backgroundBufAddr);

    RadarDraw_drawLabels(pObjectDrawObj,
                             pObjectDrawObj->centerX,
                             pObjectDrawObj->centerY,
                             pObjectDrawObj->radius,
                             0);

    /* By default, 1 pixel = 1 centermeter with scale = 1. */
    offset = 100;
    for (radius=offset; radius < pObjectDrawObj->radius; radius+=offset)
    {
        RadarDraw_drawPartCircle(pObjectDrawObj,
                pObjectDrawObj->centerX,
                pObjectDrawObj->centerY,
                radius,
                pObjectDrawObj->angle * 2
                );
    }

    RadarDraw_drawPartCircle(pObjectDrawObj,
            pObjectDrawObj->centerX,
            pObjectDrawObj->centerY,
            pObjectDrawObj->radius,
            pObjectDrawObj->angle * 2
            );

    /* draw the sector lines */
    RadarDraw_drawSectorLines(pObjectDrawObj,
            pObjectDrawObj->centerX,
            pObjectDrawObj->centerY,
            pObjectDrawObj->radius,
            pObjectDrawObj->angle * 2
            );

    return (void *) pObjectDrawObj;
}

Int32 AlgorithmFxn_RadarDrawCopyBackGround(
                                        AlgorithmFxn_RadarDrawObj *pObj,
                                        System_Buffer *pOutBuffer
                                                      )
{
    System_VideoFrameBuffer *pVidFrame = (System_VideoFrameBuffer *)pOutBuffer->payload;
    Utils_DmaCopyFill2D dmaPrm;
    Int32 status;

    dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
    dmaPrm.destAddr[0]  = (Ptr) pVidFrame->bufAddr[0];
    dmaPrm.destAddr[1]  = NULL;
    dmaPrm.destPitch[0] = pObj->pitch;
    dmaPrm.destPitch[1] = 0;
    dmaPrm.destStartX   = 0;
    dmaPrm.destStartY   = 0;
    dmaPrm.width        = pObj->algLinkCreateParams.imgFrameWidth;
    dmaPrm.height       = pObj->algLinkCreateParams.imgFrameHeight;
    dmaPrm.srcAddr[0]   = (Ptr) pObj->backgroundBufAddr;
    dmaPrm.srcAddr[1]   = NULL;
    dmaPrm.srcPitch[0]  = pObj->pitch;
    dmaPrm.srcPitch[1]  = 0;
    dmaPrm.srcStartX    = 0;
    dmaPrm.srcStartY    = 0;

    status = Utils_dmaCopy2D(&pObj->copyFramesDmaObj,
                             &dmaPrm,
                             1);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Void AlgorithmFxn_RadarDrawSetMetaDataBuf(AlgorithmFxn_RadarDrawObj *pObj,
    System_MetaDataBuffer *pMetadataBuffer)
{
    UInt32 chId, i;
    AlgorithmFxn_RadarDrawAlgId algId;
    Void *metaDataAddr;

    for(i=0; i<pObj->algLinkCreateParams.numDrawAlg; i++)
    {
        algId = pObj->algLinkCreateParams.drawAlgId[i];

        chId = i;

        metaDataAddr = NULL;

        if(chId<pMetadataBuffer->numMetaDataPlanes)
        {
            metaDataAddr = pMetadataBuffer->bufAddr[chId];
        }

        if(algId==ALG_FXN_RADAR_DRAW_ALG_DETECT)
        {
            pObj->detectedObjs =
                    (AlgorithmFxn_RadarBeamFormBuffDescriptor*)metaDataAddr;
        }
    }
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
Int32 AlgorithmFxn_RadarDrawProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDrawObj           * pObjectDrawObj;
    System_VideoFrameBuffer             * pVideoBuffer;
    System_MetaDataBuffer               * pMetadataBuffer;
    Utils_DmaCopyFill2D dmaPrm;

    pObjectDrawObj = (AlgorithmFxn_RadarDrawObj *)alg_handle;

    /*
     * The input buffer is a composite buffer consisting of two
     * channels. Channel 0 consists of video frame buffer while
     * channel1 consists of meta data.
     */
    pMetadataBuffer = (System_MetaDataBuffer *) in_buf->payload;

    pVideoBuffer    = (System_VideoFrameBuffer *)out_buf->payload;

    AlgorithmFxn_RadarDrawSetMetaDataBuf(pObjectDrawObj, pMetadataBuffer);

    if (pObjectDrawObj->currProfileId == pObjectDrawObj->detectedObjs->profileId)
    {
        status = AlgorithmFxn_RadarDrawCopyBackGround(pObjectDrawObj, out_buf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pObjectDrawObj->drawBufAddr[0] = (UInt32)pVideoBuffer->bufAddr[0];

        Draw2D_updateBufAddr(pObjectDrawObj->draw2DHndl, pObjectDrawObj->drawBufAddr);
        if( pObjectDrawObj->algLinkCreateParams.drawOption & ALG_FXN_RADAR_DRAW_DETECT_OUTPUT )
        {
            RadarDraw_drawRadarObjects(pObjectDrawObj);
        }
        Cache_wbInv(pVideoBuffer->bufAddr[0U],
                    pObjectDrawObj->outBufferSize_y,
                    Cache_Type_ALLD,
                    TRUE
                   );
        dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
        dmaPrm.destAddr[0]  = (Ptr) pObjectDrawObj->prevDrawnBuffer;
        dmaPrm.destAddr[1]  = NULL;
        dmaPrm.destPitch[0] = pObjectDrawObj->pitch;

        dmaPrm.destPitch[1] = 0;
        dmaPrm.destStartX   = 0;
        dmaPrm.destStartY   = 0;
        dmaPrm.width        = pObjectDrawObj->algLinkCreateParams.imgFrameWidth;
        dmaPrm.height       = pObjectDrawObj->algLinkCreateParams.imgFrameHeight;
        dmaPrm.srcAddr[0]   = (Ptr)  pVideoBuffer->bufAddr[0U];
        dmaPrm.srcAddr[1]   = NULL;
        dmaPrm.srcPitch[0]  = pObjectDrawObj->pitch;
        dmaPrm.srcPitch[1]  = 0;
        dmaPrm.srcStartX    = 0;
        dmaPrm.srcStartY    = 0;

        status = Utils_dmaCopy2D(&pObjectDrawObj->copyFramesDmaObj,
                                 &dmaPrm,
                                 1);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
        dmaPrm.destAddr[0]  = (Ptr)  pVideoBuffer->bufAddr[0U];
        dmaPrm.destAddr[1]  = NULL;
        dmaPrm.destPitch[0] = pObjectDrawObj->pitch;

        dmaPrm.destPitch[1] = 0;
        dmaPrm.destStartX   = 0;
        dmaPrm.destStartY   = 0;
        dmaPrm.width        = pObjectDrawObj->algLinkCreateParams.imgFrameWidth;
        dmaPrm.height       = pObjectDrawObj->algLinkCreateParams.imgFrameHeight;
        dmaPrm.srcAddr[0]   = (Ptr) pObjectDrawObj->prevDrawnBuffer;
        dmaPrm.srcAddr[1]   = NULL;
        dmaPrm.srcPitch[0]  = pObjectDrawObj->pitch;
        dmaPrm.srcPitch[1]  = 0;
        dmaPrm.srcStartX    = 0;
        dmaPrm.srcStartY    = 0;

        status = Utils_dmaCopy2D(&pObjectDrawObj->copyFramesDmaObj,
                                 &dmaPrm,
                                 1);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }


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
Int32 AlgorithmFxn_RadarDrawControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    AlgorithmLink_ControlParams * pAlgLinkControlPrm;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDrawObj * pDrawObj;

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)controlParams;
    if(pAlgLinkControlPrm->size !=
        sizeof(AlgorithmFxn_RadarDrawControlParams))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        AlgorithmFxn_RadarDrawControlParams* pPrms =
        (AlgorithmFxn_RadarDrawControlParams*) controlParams;
        pDrawObj = (AlgorithmFxn_RadarDrawObj*)alg_handle;
        pDrawObj->currProfileId = pPrms->profileId;
        pDrawObj->algLinkCreateParams.rangeRes[pDrawObj->currProfileId] = pPrms->rangeRes;
        pDrawObj->algLinkCreateParams.velocityRes[pDrawObj->currProfileId] = pPrms->velocityRes;
        pDrawObj->algLinkCreateParams.azimAngleRes[pDrawObj->currProfileId] = pPrms->azimAngleRes;
        pDrawObj->algLinkCreateParams.elevAngleRes[pDrawObj->currProfileId] = pPrms->elevAngleRes;
        Vps_printf(" RADAR_DRAW_OBJS: Changing Profile Id to %d.\n\r", pPrms->profileId);
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
Int32 AlgorithmFxn_RadarDrawDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDrawObj                   * pObjectDrawObj;

    pObjectDrawObj = (AlgorithmFxn_RadarDrawObj *)alg_handle;

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           (Ptr) pObjectDrawObj->backgroundBufAddr,
                           pObjectDrawObj->outBufferSize_y);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           (Ptr) pObjectDrawObj->prevDrawnBuffer,
                           pObjectDrawObj->outBufferSize_y);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_dmaDeleteCh(&pObjectDrawObj->copyFramesDmaObj);

    status = Draw2D_delete(pObjectDrawObj->draw2DHndl);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                  pObjectDrawObj,
                  sizeof(AlgorithmFxn_RadarDrawObj)
                    );

    return status;
}
