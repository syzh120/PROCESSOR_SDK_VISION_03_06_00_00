/*
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
*/

/**
 *******************************************************************************
 *
 * \file decLink_common.c Implement the Multichannel Decode Link
 *         - Dec link input/output queue interface
 *         - Create codec instance and allocate the ouput buffers
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <stdlib.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include "decLink_priv.h"
#include <src/rtos/links_ipu/iva/codec_utils/hdvicp2_config.h>

/*******************************************************************************
 *  Decode Link Private Functions
 *******************************************************************************
 */
static Int32 DecLink_codecCreateReqObj(DecLink_Obj * pObj);
static Int32 DecLink_codecCreateOutObjCommon(DecLink_Obj * pObj);
static Int32 DecLink_codecMapCh2ResolutionPool(DecLink_Obj * pObj, UInt32 chId);
static Int32 DecLink_codecCreateOutChObj(DecLink_Obj * pObj, UInt32 chId);
static Int32 DecLink_codecCreateChObj(DecLink_Obj * pObj, UInt32 chId);
static Int32 DecLink_codecCreateDecObj(DecLink_Obj * pObj, UInt32 chId);
static Int32 DecLink_codecCreateChannel(DecLink_Obj * pObj, UInt32 chId);
static Int32 DecLink_codecDeleteChannel(DecLink_Obj * pObj, UInt32 chId);
static Void  DecLink_codecProcessTskFxn(UArg arg1, UArg arg2);
static Int32 DecLink_codecCreateProcessTsk(DecLink_Obj * pObj, UInt32 tskId);
static Int32 DecLink_codecDeleteProcessTsk(DecLink_Obj * pObj, UInt32 tskId);
static Int32 DecLink_codecQueueBufsToChQue(DecLink_Obj * pObj);
static Int32 DecLink_codecSubmitData(DecLink_Obj * pObj);
static Int32 DecLink_codecGetProcessedData(DecLink_Obj * pObj);
static Int32 decLink_map_displayDelay2CodecParam(Int32 displayDelay);
static Int32 DecLink_codecFlushNDeleteChannel(DecLink_Obj * pObj, UInt32 chId);
static Int32 DecLink_dupFrame(DecLink_Obj * pObj, System_Buffer * pOrgFrame,
                              System_Buffer ** ppDupFrame);
static Int32 DecLink_codecCreateReqObjDummy(DecLink_Obj * pObj);
static Int32 DecLink_codecDeleteReqObjDummy(DecLink_Obj * pObj);



/**
 *******************************************************************************
 *
 * \brief This function create the Declink request Object Queue
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateReqObj(DecLink_Obj * pObj)
{
    Int32 status;
    UInt32 reqId;

    memset(pObj->reqObj, 0, sizeof(pObj->reqObj));

    status = Utils_queCreate(&pObj->reqQue,
                             (DEC_LINK_MAX_REQ),
                             pObj->reqQueMem, UTILS_QUE_FLAG_BLOCK_QUE_GET);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pObj->isReqPend = FALSE;

    for (reqId = 0; reqId < DEC_LINK_MAX_REQ; reqId++)
    {
        status =
            Utils_quePut(&pObj->reqQue, &pObj->reqObj[reqId], BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function create the Declink Dup Object
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateDupObj(DecLink_Obj * pObj)
{
    Int32 status;
    Int i;

    memset(&pObj->dupObj, 0, sizeof(pObj->dupObj));
    status = Utils_queCreate(&pObj->dupObj.dupQue,
                             UTILS_ARRAYSIZE(pObj->dupObj.dupQueMem),
                             pObj->dupObj.dupQueMem,
                             UTILS_QUE_FLAG_BLOCK_QUE_GET);
    UTILS_assertError(!UTILS_ISERROR(status),
                      status,
                      DEC_LINK_E_DUPOBJ_CREATE_FAILED, pObj->linkId, -1);
    if (!UTILS_ISERROR(status))
    {
        for (i = 0; i < DEC_LINK_MAX_DUP_FRAMES; i++)
        {
            pObj->dupObj.linkPvtInfo[i].pDupOrgFrame = NULL;
            pObj->dupObj.linkPvtInfo[i].dupRefCount = 0;

            pObj->dupObj.dupFrameMem[i].pEncDecLinkPrivate =
                                  &(pObj->dupObj.linkPvtInfo[i]);
            status = Utils_quePut(&pObj->dupObj.dupQue,
                                  &pObj->dupObj.dupFrameMem[i], BSP_OSAL_NO_WAIT);
            UTILS_assert(!UTILS_ISERROR(status));
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the Declink Dup Object
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecDeleteDupObj(DecLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#if 0
    UTILS_assertError((Utils_queIsFull(&pObj->dupObj.dupQue) == TRUE),
                      status,
                      DEC_LINK_E_DUPOBJ_DELETE_FAILED, pObj->linkId, -1);
#endif
    status = Utils_queDelete(&pObj->dupObj.dupQue);
    UTILS_assertError(!UTILS_ISERROR(status),
                      status,
                      DEC_LINK_E_DUPOBJ_DELETE_FAILED, pObj->linkId, -1);
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function creates the non channel specific portion of t
 *        he Declink Out object
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateOutObjCommon(DecLink_Obj * pObj)
{
    Int32 status;
    Int32 outId, chId, frameId;
    DecLink_OutObj *pOutObj;
    Utils_EncDecLinkPvtInfo *pFrameInfo;
    System_Buffer   *buffers;
    System_VideoFrameBuffer *videoFrames;
    UInt32 flags;

    pObj->outObj.totalNumOutBufs = 0;
    pObj->info.numQue = DEC_LINK_MAX_OUT_QUE;

    for (outId = 0u; outId < DEC_LINK_MAX_OUT_QUE; outId++)
    {
        pObj->info.queInfo[outId].numCh = pObj->inQueInfo.numCh;
    }

    status = Utils_queCreate(&pObj->processDoneQue,
                             DEC_LINK_MAX_OUT_FRAMES,
                             pObj->processDoneQueMem,
                             (UTILS_QUE_FLAG_BLOCK_QUE_GET |
                              UTILS_QUE_FLAG_BLOCK_QUE_PUT));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pOutObj = &pObj->outObj;
    status = Utils_bufCreateExt(&pOutObj->bufOutQue, TRUE, FALSE,
                                pObj->inQueInfo.numCh);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        status = Utils_queCreate(&pOutObj->outChObj[chId].outFrameQue,
                                 DEC_LINK_MAX_NUM_OUT_BUF_PER_CH*2,
                                 pOutObj->outChObj[chId].outFrameQueMem,
                                 UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        for (frameId = 0; frameId < DEC_LINK_MAX_NUM_OUT_BUF_PER_CH*2; frameId++)
        {

            buffers = &pOutObj->outChObj[chId].outFramesPool[frameId];
            videoFrames = &pOutObj->outChObj[chId].videoFrames[frameId];
            pFrameInfo = &pOutObj->outChObj[chId].linkPvtInfo[frameId];

            memset(buffers, 0, sizeof(*buffers));
            memset(videoFrames, 0, sizeof(*videoFrames));
            memset(pFrameInfo, 0, sizeof(*pFrameInfo));

            buffers->bufType      = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
            buffers->chNum        = chId;
            buffers->payloadSize  = sizeof(System_VideoFrameBuffer);
            buffers->payload      = videoFrames;
            buffers->pEncDecLinkPrivate = pFrameInfo;

            pFrameInfo->allocPoolID = chId;
            pFrameInfo->invalidFrame = FALSE;

            flags = videoFrames->chInfo.flags;
            flags = System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(flags, 0);

            status = Utils_quePut(&pOutObj->outChObj[chId].outFrameQue,
                &pOutObj->outChObj[chId].outFramesPool[frameId], BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function populates the resolution parameters of each
 *        ouput channel of the Declink. Declink output buffer allocation
 *        logic uses a definte number of resolution class pools
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecPopulateOutFrmFormat(DecLink_Obj *pObj, UInt32 chId)
{
    DecLink_OutObj *pOutObj;
    Int32 status = DEC_LINK_S_SUCCESS;
    FVID2_Format *pFormat;

    pOutObj = &pObj->outObj;
    pOutObj->outChObj[chId].outNumFrames =
                            pObj->createArgs.chCreateParams[chId].numBufPerCh;
    UTILS_assert(
       pOutObj->outChObj[chId].outNumFrames <= DEC_LINK_MAX_OUT_FRAMES);
    UTILS_assert(
       pOutObj->outChObj[chId].outNumFrames <= DEC_LINK_MAX_NUM_OUT_BUF_PER_CH);

    pFormat = &pOutObj->outChObj[chId].outFormat;

    pFormat->chNum = 0;
    pFormat->dataFormat = SYSTEM_DF_YUV420SP_UV;
    pFormat->fieldMerged[0] = FALSE;
    pFormat->fieldMerged[1] = FALSE;
    pFormat->fieldMerged[2] = FALSE;

    switch (pOutObj->outChObj[chId].reslutionClass)
    {
        /* Modify this with formula to calculate the single buffer
         * size, if possible */
        case UTILS_ENCDEC_RESOLUTION_CLASS_CIF:       // CIF
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_CIF_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_CIF_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_D1:        // D1
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_D1_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_D1_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_720P:      // 720p
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_720P_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_720P_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_1080P:     // 1080p
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_1080P_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_1080P_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_4MP:      // 4MP
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_4MP_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_4MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_5MP:     // 5MP
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_5MP_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_5MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_9MP:      // 9MP
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_9MP_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_9MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_16MP:     // 16MP
            pFormat->width = UTILS_ENCDEC_RESOLUTION_CLASS_16MP_WIDTH;
            pFormat->height = UTILS_ENCDEC_RESOLUTION_CLASS_16MP_HEIGHT;
            break;
        default:
            Vps_printf (" DECLINK: Unknown reslutionClass");
            UTILS_assert(1);
            break;
    }

    /* Do not apply padding for MJPEG, MJPEG can work even without padding.
     * The SRV Algo expect pitch == width and for AVB SRV usecase to work
     * padding is avoided while MJPEG decoding.
     */
    if (pObj->createArgs.chCreateParams[chId].format != SYSTEM_IVIDEO_MJPEG)
    {
        pFormat->width  = UTILS_ENCDEC_GET_PADDED_WIDTH (pFormat->width);
        pFormat->height = UTILS_ENCDEC_GET_PADDED_HEIGHT (pFormat->height);
    }

    pFormat->pitch[0] = VpsUtils_align(pFormat->width, VPS_BUFFER_ALIGNMENT);
    pFormat->pitch[1] = pFormat->pitch[0];
    pFormat->pitch[2] = 0;

    pFormat->scanFormat = SYSTEM_SF_PROGRESSIVE;
    pFormat->bpp = SYSTEM_BPP_BITS16;
    pFormat->reserved = NULL;

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function creates the DecLink channel specific
 *        portion of the output object
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateOutChObj(DecLink_Obj * pObj, UInt32 chId)
{
    DecLink_OutObj *pOutObj;
    Int32 status = DEC_LINK_S_SUCCESS;
    Int32 queStatus = DEC_LINK_S_SUCCESS;
    UInt32 frameId, outId, planes;
    FVID2_Format *pFormat;
    System_Buffer  *frame;
    System_LinkChInfo *pOutChInfo;
    FVID2_Frame  fvid2Frame;
    System_VideoFrameBuffer *videoFrames;
    Utils_EncDecLinkPvtInfo *pFrameInfo[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH];

    /* init pFrameInfo[] to NULL */
    for(frameId=0; frameId<DEC_LINK_MAX_NUM_OUT_BUF_PER_CH; frameId++)
        pFrameInfo[frameId] = NULL;

    pOutObj = &pObj->outObj;
    pFormat = &pOutObj->outChObj[chId].outFormat;

    DecLink_codecPopulateOutFrmFormat(pObj, chId);

    if (pObj->createArgs.chCreateParams[chId].algCreateStatus ==
        DEC_LINK_ALG_CREATE_STATUS_CREATE)
    {
        pObj->outObj.totalNumOutBufs += pOutObj->outChObj[chId].outNumFrames;
        UTILS_assert(pObj->outObj.totalNumOutBufs <= DEC_LINK_MAX_OUT_FRAMES);

        for (frameId = 0;
             frameId < pOutObj->outChObj[chId].outNumFrames; frameId++)
        {
            status = Utils_queGet(&pOutObj->outChObj[chId].outFrameQue,
                                  (Ptr *)&frame,1,BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            pOutObj->outChObj[chId].outFrames[frameId] = frame;
            pFrameInfo[frameId] =
                pOutObj->outChObj[chId].outFrames[frameId]->pEncDecLinkPrivate;
        }

        for (frameId = 0;
             frameId < pOutObj->outChObj[chId].outNumFrames; frameId++)
        {
            {
                status = Utils_memFrameAlloc(&pOutObj->outChObj[chId].outFormat,
                               &fvid2Frame,
                               1,
                               0);
                //UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
            videoFrames = &pOutObj->outChObj[chId].videoFrames[frameId];
            for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
            {
                videoFrames->bufAddr[planes] = fvid2Frame.addr[0][planes];
            }

            videoFrames->metaBufSize = 0;
            videoFrames->metaBufAddr = NULL;
            videoFrames->metaFillLength = 0;

            if(pObj->createArgs.chCreateParams[chId].format
                == SYSTEM_IVIDEO_MJPEG
                &&
               pObj->createArgs.chCreateParams[chId].extractJpegAppMarker
            )
            {
                videoFrames->metaBufSize = JPEG_APP_MARKER_SIZE_MAX;
                videoFrames->metaBufAddr =
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    videoFrames->metaBufSize,
                                    SYSTEM_BUFFER_ALIGNMENT
                                );
                UTILS_assert(videoFrames->metaBufAddr!=NULL);
            }

            /* Take a copy of the original frame. Will be used at free time */
            pOutObj->outChObj[chId].allocFrames[frameId] =
                            *pOutObj->outChObj[chId].outFrames[frameId];
        }

        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            pObj->outObj.totalNumOutBufs -=
                 (pOutObj->outChObj[chId].outNumFrames - frameId);
            pOutObj->outChObj[chId].outNumFrames = frameId;
            Vps_printf(" DECLINK: ERROR!!! During Channel Open, "
                "Only %d output buffers are getting allocated due to "
                "insufficient memory, might affect CH%d performance \n",
                frameId, chId);
        }

        for (frameId = 0;
             frameId < pOutObj->outChObj[chId].outNumFrames; frameId++)
        {
            pOutObj->outChObj[chId].outFrames[frameId]->pEncDecLinkPrivate =
                     pFrameInfo[frameId];
            queStatus = Utils_bufPutEmptyBufferExt(&pOutObj->bufOutQue,
                              pOutObj->outChObj[chId].outFrames[frameId]);
            UTILS_assert(queStatus == SYSTEM_LINK_STATUS_SOK);
        }

        pObj->chObj[chId].algCreateStatusLocal =
                         DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE;
        pObj->createArgs.chCreateParams[chId].algCreateStatus =
                         DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE;
    }

    for (outId = 0u; outId < DEC_LINK_MAX_OUT_QUE; outId++)
    {
        pFormat = &pObj->outObj.outChObj[chId].outFormat;
        pOutChInfo = &pObj->info.queInfo[outId].chInfo[chId];

        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pOutChInfo->flags,
                                                 pFormat->scanFormat);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(pOutChInfo->flags,
                                              VPS_VPDMA_MT_NONTILEDMEM);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pOutChInfo->flags,
                                                 pFormat->dataFormat);

        if (pObj->createArgs.chCreateParams[chId].format == SYSTEM_IVIDEO_MJPEG)
        {
            pOutChInfo->startX = 0;
            pOutChInfo->startY = 0;
        }
        else
        {
            pOutChInfo->startX = UTILS_ENCDEC_PADX;
            pOutChInfo->startY = UTILS_ENCDEC_PADY;
        }
        pOutChInfo->width = pObj->inQueInfo.chInfo[chId].width;
        pOutChInfo->height = pObj->inQueInfo.chInfo[chId].height;
        pOutChInfo->pitch[0] = pFormat->pitch[0];
        pOutChInfo->pitch[1] = pFormat->pitch[1];
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function creates the DecLink channel specific object
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateChObj(DecLink_Obj * pObj, UInt32 chId)
{
    DecLink_ChObj *pChObj;
    Int32 status;

    pChObj = &pObj->chObj[chId];

    status = Utils_queCreate(&pChObj->inQue, DEC_LINK_MAX_REQ,
                             pChObj->inBitBufMem,
                             (UTILS_QUE_FLAG_BLOCK_QUE_GET |
                              UTILS_QUE_FLAG_BLOCK_QUE_PUT));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pChObj->allocPoolID = chId;

    pChObj->algCreateStatusLocal = DEC_LINK_ALG_CREATE_STATUS_DONOT_CREATE;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the codec create time parameters
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoDecoder_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1335)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1340)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1337)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1334)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1336)
 *          DES_ID: DOX_DES_TAG(DES_VideoDecoder_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1338)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1342)
 *          DES_ID: DOX_DES_TAG(DES_VideoDecoder_003)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1261)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1341)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 declink_codec_set_ch_alg_create_params(DecLink_Obj * pObj,
                                                    UInt32 chId)
{
    DecLink_ChObj *pChObj;

    pChObj = &pObj->chObj[chId];
    pChObj->algObj.algCreateParams.format =
        (System_IVideoFormat) pObj->createArgs.chCreateParams[chId].format;
    pChObj->algObj.algCreateParams.presetProfile =
        pObj->createArgs.chCreateParams[chId].profile;
    pChObj->algObj.algCreateParams.processCallLevel =
        pObj->createArgs.chCreateParams[chId].processCallLevel;
    pChObj->algObj.algCreateParams.fieldMergeDecodeEnable =
        pObj->createArgs.chCreateParams[chId].fieldMergeDecodeEnable;
    pChObj->algObj.algCreateParams.maxWidth =
        pObj->createArgs.chCreateParams[chId].targetMaxWidth;
    pChObj->algObj.algCreateParams.maxHeight =
        pObj->createArgs.chCreateParams[chId].targetMaxHeight;
    pChObj->algObj.algCreateParams.maxFrameRate =
        pObj->createArgs.chCreateParams[chId].defaultDynamicParams.
        targetFrameRate;
    pChObj->algObj.algCreateParams.maxBitRate =
        pObj->createArgs.chCreateParams[chId].defaultDynamicParams.
        targetBitRate;

    pChObj->algObj.algCreateParams.displayDelay =
        decLink_map_displayDelay2CodecParam(
            pObj->createArgs.chCreateParams[chId].displayDelay);

    Utils_encdecGetCodecLevel(pChObj->algObj.algCreateParams.format,
                              pChObj->algObj.algCreateParams.maxWidth,
                              pChObj->algObj.algCreateParams.maxHeight,
                              pObj->createArgs.chCreateParams[chId].
                              defaultDynamicParams.targetFrameRate,
                              pObj->createArgs.chCreateParams[chId].
                              defaultDynamicParams.targetBitRate,
                              &(pChObj->algObj.algCreateParams.presetLevel),
                              FALSE);

    pChObj->algObj.algCreateParams.dpbBufSizeInFrames =
        pObj->createArgs.chCreateParams[chId].dpbBufSizeInFrames;
    pChObj->algObj.algCreateParams.decodeFrameType =
        pObj->createArgs.chCreateParams[chId].decodeFrameType;

    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the codec run time (dynamic) parameters
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 declink_codec_set_ch_alg_default_dynamic_params(DecLink_Obj * pObj,
                                                             UInt32 chId)
{
    DecLink_ChObj *pChObj;

    pChObj = &pObj->chObj[chId];
    pChObj->algObj.algDynamicParams.decodeHeader =
        DEC_LINK_DEFAULT_ALGPARAMS_DECODEHEADER;
#if 0
    pChObj->algObj.algDynamicParams.displayWidth =
        DEC_LINK_DEFAULT_ALGPARAMS_DISPLAYWIDTH;
#endif
    pChObj->algObj.algDynamicParams.displayWidth =
        pObj->outObj.outChObj[chId].outFormat.pitch[0];
    pChObj->algObj.algDynamicParams.frameSkipMode =
        DEC_LINK_DEFAULT_ALGPARAMS_FRAMESKIPMODE;
    pChObj->algObj.algDynamicParams.newFrameFlag =
        DEC_LINK_DEFAULT_ALGPARAMS_NEWFRAMEFLAG;

    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function set the static/dynamic codec parameters
 *        and create the codec/Alg handle
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoDecoder_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1335)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1333)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateDecObj(DecLink_Obj * pObj, UInt32 chId)
{
    Int retVal;
    DecLink_ChObj *pChObj;
    Int scratchGroupID;

    pChObj = &pObj->chObj[chId];
    scratchGroupID = -1;

    DecLink_codecPopulateOutFrmFormat(pObj, chId);
    declink_codec_set_ch_alg_create_params(pObj, chId);
    declink_codec_set_ch_alg_default_dynamic_params(pObj, chId);

    pChObj->algObj.prevOutFrame = NULL;
    switch (pChObj->algObj.algCreateParams.format)
    {
        case SYSTEM_IVIDEO_MJPEG:
            retVal =
                DecLinkJPEG_algCreate(&pChObj->algObj.u.jpegAlgIfObj,
                                      &pChObj->algObj.algCreateParams,
                                      &pChObj->algObj.algDynamicParams,
                                      pObj->linkId, chId, scratchGroupID,
                                      &pObj->outObj.outChObj[chId].outFormat,
                                      pObj->outObj.outChObj[chId].outNumFrames,
                                      &pChObj->algObj.resDesc[0]);
            break;

        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
            retVal =
                DecLinkH264_algCreate(&pChObj->algObj.u.h264AlgIfObj,
                                      &pChObj->algObj.algCreateParams,
                                      &pChObj->algObj.algDynamicParams,
                                      pObj->linkId, chId, scratchGroupID,
                                      &pObj->outObj.outChObj[chId].outFormat,
                                      pObj->outObj.outChObj[chId].outNumFrames,
                                      &pChObj->algObj.resDesc[0]);
            break;

        default:
            retVal = DEC_LINK_E_UNSUPPORTEDCODEC;
            UTILS_assert(retVal == DEC_LINK_S_SUCCESS);
            break;
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief This function create/open a channel
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoDencoder_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1334)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1336)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateChannel(DecLink_Obj * pObj, UInt32 chId)
{
    DecLink_ChObj *pChObj;
    Int32 status = DEC_LINK_S_SUCCESS;

    UTILS_assert(chId <= pObj->inQueInfo.numCh);
    pChObj = &pObj->chObj[chId];
    pObj->outObj.outChObj[chId].reslutionClass =
        (EncDec_ResolutionClass) (UTILS_ENCDEC_RESOLUTION_CLASS_LAST + 1);
    pObj->outObj.outChObj[chId].outNumFrames = 0;
    pChObj->isFirstIDRFrameFound = FALSE;

    status = DecLink_codecMapCh2ResolutionPool(pObj, chId);
    UTILS_assert(status == DEC_LINK_S_SUCCESS);
    /* Set numBufPerCh to the default value if not set properly */
    if(pObj->createArgs.chCreateParams[chId].numBufPerCh <= 0)
    {
        pObj->createArgs.chCreateParams[chId].numBufPerCh =
                         DEC_LINK_MAX_OUT_FRAMES_PER_CH;
    }

    if (DEC_LINK_MAX_NUM_OUT_BUF_PER_CH <
        pObj->createArgs.chCreateParams[chId].numBufPerCh)
    {
       Vps_printf(" DECLINK: WARNING: User is asking for %d"
          " buffers per CH. But max allowed is %d. \n"
          " Over riding user requested with max allowed \n\n",
            pObj->createArgs.chCreateParams[chId].numBufPerCh,
            DEC_LINK_MAX_NUM_OUT_BUF_PER_CH);
        pObj->createArgs.chCreateParams[chId].numBufPerCh =
              DEC_LINK_MAX_NUM_OUT_BUF_PER_CH;
    }

    if (pObj->createArgs.chCreateParams[chId].algCreateStatus ==
        DEC_LINK_ALG_CREATE_STATUS_CREATE)
    {
        status = DecLink_codecCreateDecObj(pObj, chId);
        if (status != DEC_LINK_S_SUCCESS)
        {
            pObj->createArgs.chCreateParams[chId].algCreateStatus =
                             DEC_LINK_ALG_CREATE_STATUS_DELETE;
        }
    }
    else
    {
        #ifdef SYSTEM_DEBUG_DEC
        Vps_printf(" DECODE: CodecInst & OutPut bufs NOT created for CH%d\n",
            chId            );
        #endif
    }

    if (status == DEC_LINK_S_SUCCESS)
    {
        status = DecLink_codecCreateOutChObj(pObj, chId);
        //UTILS_assert(status == DEC_LINK_S_SUCCESS);

        #ifdef SYSTEM_DEBUG_DEC
        Vps_printf(" DECODE: Creating CH%d of %d x %d [%d] [%d],"
                   "target bitrate = %d Kbps ... \n",
            chId,
            pObj->inQueInfo.chInfo[chId].width,
            pObj->inQueInfo.chInfo[chId].height,
            System_Link_Ch_Info_Get_Flag_Scan_Format(
                    pObj->inQueInfo.chInfo[chId].flags),
            System_Link_Ch_Info_Get_Flag_Mem_Type(
                    pObj->inQueInfo.chInfo[chId].flags),
            pObj->createArgs.chCreateParams[chId].defaultDynamicParams.
                                                  targetBitRate/1000
            );
        #endif
    }
    pChObj->IFrameOnlyDecode = FALSE;
    pChObj->processReqestCount = 0;
    pChObj->getProcessDoneCount = 0;
    pChObj->skipFrame = FALSE;
    pChObj->disableChn = FALSE;
    pChObj->skipFrameDue2AccumuInNextLink = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function initilize the ouput buffer paramters by coping
 *        these values from input buffer
 *
 * \param   pObj      [IN] DecLink_Obj Declink Object
 * \param   chId      [IN] channel ID
 * \param   pFrame    [OUT] output buffer pointer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 declink_codec_init_outframe(DecLink_Obj * pObj,
                                         UInt32 chId, System_Buffer * pFrame)
{
    Utils_EncDecLinkPvtInfo *pFrameInfo;
    System_VideoFrameBuffer *videoFrame;

    pFrameInfo = (Utils_EncDecLinkPvtInfo *) pFrame->pEncDecLinkPrivate;
    UTILS_assert((pFrameInfo != NULL)
                 &&
                 UTILS_ARRAYISVALIDENTRY(pFrameInfo,
                       pObj->outObj.outChObj[chId].linkPvtInfo));
    pFrameInfo->dupRefCount = 1;
    pFrameInfo->pDupOrgFrame = NULL;

    /* By Default, the output data type is 420 SP, update the rtparam,
       other link will use this when rtChInfoUpdate is set */
    videoFrame = pFrame->payload;
    UTILS_assert(videoFrame != NULL);
    UTILS_assert(&videoFrame->chInfo != NULL);
    videoFrame->chInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                                            videoFrame->chInfo.flags,
                                            SYSTEM_DF_YUV420SP_UV);

    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function identifing the output buffers which are reday
 *        to sendout to display. Also dup the frame if required
 *
 * \param   pObj          [IN] DecLink_Obj Declink Object
 * \param   outFrame      [IN] output buffer pointer
 * \param   freeFrameList [OUT] free buffer list
 * \param   displayFrame  [OUT] display ready buffer pointer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecGetDisplayFrame(DecLink_Obj * pObj,
                                          System_Buffer * outFrame,
                                          System_BufferList * freeFrameList,
                                          System_Buffer ** displayFrame)
{
    Int i, j, status = DEC_LINK_S_SUCCESS;
    Bool doDup = TRUE;
    UInt32 chId;

    if (outFrame != NULL)
    {
        *displayFrame = NULL;
        chId = outFrame->chNum;
        UTILS_assert(UTILS_ARRAYISVALIDENTRY(outFrame,
                           pObj->outObj.outChObj[chId].outFramesPool));

        for (i = 0; i < freeFrameList->numBuf; i++)
        {
            if (freeFrameList->buffers[i] == outFrame)
            {
                /* This frame is going to be used as display frame. Remove
                 * it from the freeFrameList */
                for (j = (i + 1); j < freeFrameList->numBuf; j++)
                {
                    freeFrameList->buffers[j - 1] = freeFrameList->buffers[j];
                }
                freeFrameList->numBuf -= 1;
                doDup = FALSE;
                break;
            }
        }
    }
    else
    {
        doDup = FALSE;
    }
    if (FALSE == doDup)
    {
        *displayFrame = outFrame;
    }
    else
    {
        status = DecLink_dupFrame(pObj, outFrame, displayFrame);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function free-up the input frames which are processed
 *        Also send-out the filled output buffers to next link
 *
 * \param   pObj          [IN] DecLink_Obj Declink Object
 * \param   freeFrameList [OUT] free buffer list
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecFreeProcessedFrames(DecLink_Obj * pObj,
                                       System_BufferList * freeFrameList)
{
    Int i, status = DEC_LINK_S_SUCCESS;
    System_Buffer *freeFrame;
    System_Buffer *origFrame;
    Utils_EncDecLinkPvtInfo *freeFrameInfo;
    UInt cookie;
    Bool bufFreeDone = FALSE;

    cookie = Hwi_disable();

    for (i = 0; i < freeFrameList->numBuf; i++)
    {
        freeFrame = freeFrameList->buffers[i];
        UTILS_assert(freeFrame != NULL);
        freeFrameInfo = (Utils_EncDecLinkPvtInfo*) freeFrame->pEncDecLinkPrivate;
        UTILS_assert(freeFrameInfo != NULL);
        if (freeFrameInfo->pDupOrgFrame)
        {
            UTILS_assert(UTILS_ARRAYISVALIDENTRY(freeFrame,
                                                 pObj->dupObj.dupFrameMem));
            origFrame = freeFrameInfo->pDupOrgFrame;
            status = Utils_quePut(&pObj->dupObj.dupQue,
                                  freeFrame, BSP_OSAL_NO_WAIT);
            UTILS_assert(!UTILS_ISERROR(status));
            freeFrame = origFrame;
            freeFrameInfo = origFrame->pEncDecLinkPrivate;
        }
        UTILS_assert((freeFrameInfo->pDupOrgFrame == NULL)
                     && (freeFrameInfo->dupRefCount > 0));
        freeFrameInfo->dupRefCount--;
        if (freeFrameInfo->dupRefCount == 0)
        {
            if (freeFrameInfo->invalidFrame == TRUE)
            {
                freeFrameInfo->invalidFrame = FALSE;
                status = Utils_quePut(
                  &pObj->outObj.outChObj[freeFrameInfo->allocPoolID].outFrameQue,
                  freeFrame, BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            else
            {
                status = Utils_bufPutEmptyBufferExt(&pObj->outObj.bufOutQue,
                                                    freeFrame);
                UTILS_assert(!UTILS_ISERROR(status));
                bufFreeDone = TRUE;
            }
        }
    }

    Hwi_restore(cookie);
    if ((TRUE == pObj->newDataProcessOnFrameFree)
      &&
      (bufFreeDone))
    {
        status = System_sendLinkCmd(pObj->linkId,
                                    SYSTEM_CMD_NEW_DATA, NULL);

        if (UTILS_ISERROR(status))
        {
            Vps_printf(" DECLINK:[%s:%d]:"
                       "System_sendLinkCmd SYSTEM_CMD_NEW_DATA failed"
                       "errCode = %d", __FILE__, __LINE__, status);
        }
        else
        {
          pObj->newDataProcessOnFrameFree = FALSE;
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function has the logic to handle various dummy request objects
 *        1. flush & delete channel if its of type CHDELETE (channel delete)
 *        2. flush only if its of type FLUSHFRAME
 *
 * \param   pObj    [IN] DecLink_Obj Declink Object
 * \param   pReqObj [IN] request object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecHandleDummyReqObj(DecLink_Obj  *pObj,
                                            DecLink_ReqObj *pReqObj)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    System_BitstreamBuffer *bitBuf;

    switch (pReqObj->type)
    {
        case DEC_LINK_REQ_OBJECT_TYPE_DUMMY_CHDELETE:
        {
            Vps_printf(" DEC : Delete CH%d Got the Dummy Object queued !!!\n",
                        pReqObj->InBuf->chNum);
            DecLink_codecFlushNDeleteChannel(pObj, pReqObj->InBuf->chNum);
            break;
        }
        case DEC_LINK_REQ_OBJECT_TYPE_DUMMY_FLUSHFRAME:
        {
            UTILS_assert(pReqObj->InBuf != NULL);
            bitBuf = (System_BitstreamBuffer*) pReqObj->InBuf->payload;
            UTILS_assert(bitBuf != NULL);
            UTILS_assert(TRUE ==
                  System_Bitstream_Buffer_Flag_Get_Is_Flushbuf(bitBuf->flags));
            #ifdef SYSTEM_DEBUG_DEC
            Vps_printf(" DECODE: CH%d: %s\n", pReqObj->InBuf->chNum,
                        "Flush Frame Received in ProcessQue");
            #endif
            break;
        }
        default:
            /* Unsupported reqObjType.*/
            UTILS_assert(0);
            break;
    }

    if (DEC_LINK_REQ_OBJECT_TYPE_DUMMY_FLUSHFRAME != pReqObj->type)
    {
        pReqObj->type = DEC_LINK_REQ_OBJECT_TYPE_REGULAR;
        UTILS_assert(UTILS_ARRAYISVALIDENTRY(
                     pReqObj,pObj->decDummyReqObj.reqObjDummy));
        status = Utils_quePut(&pObj->decDummyReqObj.reqQueDummy, pReqObj,
                              BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        Int i;

        pReqObj->type = DEC_LINK_REQ_OBJECT_TYPE_REGULAR;
        DecLink_codecFreeProcessedFrames(pObj,&pReqObj->OutFrameList);
        for (i = 0; i < pReqObj->OutFrameList.numBuf; i++)
        {
            pReqObj->OutFrameList.buffers[i] = NULL;
        }
        pReqObj->OutFrameList.numBuf = 0;
        status = Utils_quePut(&pObj->processDoneQue, pReqObj,
                              BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implement the IVA process task
 *        - Call codec specific process function
 *
 * \param   arg1 [IN] pObj Declink Object
 * \param   arg2 [IN] tskId IVA task ID
 *
 * \return  None
 *
 *******************************************************************************
*/
static Void DecLink_codecProcessTskFxn(UArg arg1, UArg arg2)
{
    Int32 status, chId, j;
    DecLink_Obj *pObj;
    DecLink_ChObj *pChObj;
    DecLink_ReqObj *pReqObj;
    System_BufferList freeFrameList;
    UInt32 tskId;

    pObj = (DecLink_Obj *) arg1;
    tskId = 0; /* assuming Tsk ID is always 0 */

    while (pObj->state != UTILS_ENCDEC_STATE_STOP)
    {
        status = DEC_LINK_S_SUCCESS;

        pReqObj = NULL;

        status = Utils_queGet(&pObj->decProcessTsk[tskId].processQue,
                              (Ptr *) & pReqObj, 1, BSP_OSAL_WAIT_FOREVER);

        if (!UTILS_ISERROR(status))
        {
            if (pReqObj->type != DEC_LINK_REQ_OBJECT_TYPE_REGULAR)
            {
                DecLink_codecHandleDummyReqObj(pObj, pReqObj);
                continue;
            }
            UTILS_assert(pReqObj->type == DEC_LINK_REQ_OBJECT_TYPE_REGULAR);
        }
        freeFrameList.numBuf = 0;
        if (pReqObj != NULL)
        {
            chId = pReqObj->InBuf->chNum;
            pChObj = &pObj->chObj[chId];

            switch (pChObj->algObj.algCreateParams.format)
            {
                case SYSTEM_IVIDEO_MJPEG:
                   status =
                      Declink_jpegDecodeFrame(pObj,
                                              pReqObj,
                                              &freeFrameList);
                   if (UTILS_ISERROR(status))
                   {
                       Vps_printf(" DECLINK:ERROR in "
                             "Declink_jpegDecodeFrame.Status[%d]", status);
                   }
                break;

                case SYSTEM_IVIDEO_H264BP:
                case SYSTEM_IVIDEO_H264MP:
                case SYSTEM_IVIDEO_H264HP:
                   status =
                      Declink_h264DecodeFrame(pObj,
                                              pReqObj,
                                              &freeFrameList);
                   if (UTILS_ISERROR(status))
                   {
                       Vps_printf(" DECLINK:ERROR in "
                             "Declink_h264DecodeFrame.Status[%d]", status);
                   }
                break;

                default:
                    UTILS_assert(FALSE);
                    break;
            }
        }
        if (pReqObj != NULL)
        {
            for (j = 0; j < pReqObj->OutFrameList.numBuf; j++)
            {
                System_Buffer *displayFrame;

                DecLink_codecGetDisplayFrame(pObj,
                                         pReqObj->OutFrameList.buffers[j],
                                         &freeFrameList, &displayFrame);
                pReqObj->OutFrameList.buffers[j] = displayFrame;

            }
            status = Utils_quePut(&pObj->processDoneQue, pReqObj,
                                  BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

        DecLink_codecFreeProcessedFrames(pObj, &freeFrameList);

        status = System_sendLinkCmd(pObj->linkId,
                                    DEC_LINK_CMD_GET_PROCESSED_DATA, NULL);

        if (UTILS_ISERROR(status))
        {
            #ifdef SYSTEM_DEBUG_CMD_ERROR
            Vps_printf(" DECLINK:[%s:%d]:"
                       "System_sendLinkCmd DEC_LINK_CMD_GET_PROCESSED_DATA failed"
                       "errCode = %d", __FILE__, __LINE__, status);
            #endif
        }

    }

    return;
}

/**
 *******************************************************************************
 * \brief IVA process task Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gDecProcessTskStack, 32)
#pragma DATA_SECTION(gDecProcessTskStack, ".bss:taskStackSection:dec_process")
UInt8 gDecProcessTskStack[NUM_HDVICP_RESOURCES][DEC_LINK_PROCESS_TSK_SIZE];

/**
 *******************************************************************************
 *
 * \brief This function create the IVA process task
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   tskId [IN] IVA task ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateProcessTsk(DecLink_Obj * pObj, UInt32 tskId)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    Error_Block ebObj;
    Error_Block *eb = &ebObj;

    Error_init(eb);

    snprintf(pObj->decProcessTsk[tskId].name,
             (sizeof(pObj->decProcessTsk[tskId].name) - 1),
             "DEC_PROCESS_TSK_%d ", tskId);
    pObj->decProcessTsk[tskId].
          name[(sizeof(pObj->decProcessTsk[tskId].name) - 1)] = 0;

    if (DEC_LINK_S_SUCCESS == status)
    {
        pObj->decProcessTsk[tskId].tsk =
              BspOsal_taskCreate(
                    (BspOsal_TaskFuncPtr)DecLink_codecProcessTskFxn,
                    "DecLink_codecProcessTsk",
                    DEC_LINK_TSK_PRI+1,
                    &gDecProcessTskStack[tskId][0],
                    DEC_LINK_PROCESS_TSK_SIZE,
                    pObj,
                    UTILS_TSK_AFFINITY_CORE0
                    );
        UTILS_assert(pObj->decProcessTsk[tskId].tsk!=NULL);
        Utils_prfLoadRegister(pObj->decProcessTsk[tskId].tsk,
                              pObj->decProcessTsk[tskId].name);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the IVA process task
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   tskId [IN] IVA task ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecDeleteProcessTsk(DecLink_Obj * pObj, UInt32 tskId)
{
    Int32 status = DEC_LINK_S_SUCCESS;

    Utils_prfLoadUnRegister(pObj->decProcessTsk[tskId].tsk);

    Utils_queUnBlock(&pObj->decProcessTsk[tskId].processQue);
    Utils_queUnBlock(&pObj->processDoneQue);

    BspOsal_taskDelete(&pObj->decProcessTsk[tskId].tsk);

    pObj->decProcessTsk[tskId].tsk = NULL;
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function maps each channels to appropriate resolution pools
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   chId  [IN] Channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecMapCh2ResolutionPool(DecLink_Obj * pObj, UInt32 chId)
{
    Int32 status = DEC_LINK_E_FAIL;
    DecLink_OutObj *pOutObj;

    pOutObj = &pObj->outObj;

    if ((pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_CIF_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_CIF_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_CIF;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_D1_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_D1_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_D1;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_720P_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_720P_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_720P;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_1080P_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_1080P_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_1080P;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_4MP_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_4MP_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_4MP;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_5MP_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_5MP_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_5MP;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_9MP_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_9MP_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_9MP;
        status = DEC_LINK_S_SUCCESS;
    }
    if ((status != DEC_LINK_S_SUCCESS) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxWidth <=
         UTILS_ENCDEC_RESOLUTION_CLASS_16MP_WIDTH) &&
        (pObj->createArgs.chCreateParams[chId].targetMaxHeight <=
         UTILS_ENCDEC_RESOLUTION_CLASS_16MP_HEIGHT))
    {
        pOutObj->outChObj[chId].reslutionClass = UTILS_ENCDEC_RESOLUTION_CLASS_16MP;
        status = DEC_LINK_S_SUCCESS;
    }
    UTILS_assert(status == DEC_LINK_S_SUCCESS);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function initilize all the codec stats parameters
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static void DecLink_codecCreateInitStats(DecLink_Obj * pObj)
{
    Int32 chId;
    DecLink_ChObj *pChObj;

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        pChObj->processReqestCount = 0;
        pChObj->getProcessDoneCount = 0;
        pChObj->numBufsInCodec       = 0;

        pChObj->disableChn = FALSE;
        pChObj->skipFrame = FALSE;
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief This function initilize the T-play related parameters
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  None
 *
 *******************************************************************************
*/
static void DecLink_initTPlayConfig(DecLink_Obj * pObj)
{
    Int32 chId;
    DecLink_ChObj *pChObj;

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        pChObj->trickPlayObj.skipFrame = FALSE;
        pChObj->trickPlayObj.frameSkipCtx.outputFrameRate = 30;
        pChObj->trickPlayObj.frameSkipCtx.inputFrameRate  = 30;
        pChObj->trickPlayObj.frameSkipCtx.inCnt = 0;
        pChObj->trickPlayObj.frameSkipCtx.outCnt = 0;
        pChObj->trickPlayObj.frameSkipCtx.multipleCnt = 0;
        pChObj->trickPlayObj.frameSkipCtx.firstTime = TRUE;

    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief This is the DecLink top level create function
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   pPrm  [IN] DecLink_CreateParams decLink create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecCreate(DecLink_Obj * pObj, DecLink_CreateParams * pPrm)
{
    Int32 status;
    Int32 chId, tskId;

    #ifdef SYSTEM_DEBUG_DEC
    Vps_printf(" DECODE: Create in progress ... !!!\n" );
    #endif

    #ifdef SYSTEM_DEBUG_MEMALLOC
    Vps_printf (" Before DEC Create:\n");
    System_memPrintHeapStatus();
    #endif

    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    status = System_linkGetInfo(pPrm->inQueParams.prevLinkId, &pObj->inTskInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    memcpy(&pObj->inQueInfo,
           &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
           sizeof(pObj->inQueInfo));
    UTILS_assert(pObj->inQueInfo.numCh <= DEC_LINK_MAX_CH);

    DecLink_initTPlayConfig(pObj);
    DecLink_codecCreateInitStats(pObj);

    DecLink_codecCreateOutObjCommon(pObj);
    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        DecLink_codecCreateChObj(pObj, chId);
        status = DecLink_codecCreateChannel(pObj, chId);
        UTILS_assert(status == DEC_LINK_S_SUCCESS);
    }
    DecLink_codecCreateReqObj(pObj);
    pObj->state = UTILS_ENCDEC_STATE_START;

    DecLink_codecCreateReqObjDummy(pObj);

    #ifdef SYSTEM_DEBUG_DEC
    Vps_printf(" DECODE: All CH Create ... DONE !!!\n" );
    #endif

    for (tskId = 0; tskId < NUM_HDVICP_RESOURCES; tskId++)
    {
        status = Utils_queCreate(&pObj->decProcessTsk[tskId].processQue,
                                 DEC_LINK_MAX_OUT_FRAMES,
                                 pObj->decProcessTsk[tskId].processQueMem,
                                 (UTILS_QUE_FLAG_BLOCK_QUE_GET |
                                  UTILS_QUE_FLAG_BLOCK_QUE_PUT));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        DecLink_codecCreateProcessTsk(pObj, tskId);
    }

    DecLink_codecCreateDupObj(pObj);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, "DECODE");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    DecLink_resetStatistics(pObj);
    pObj->isFirstFrameRecv = FALSE;

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("DECLINK",
                       pObj->memUsed,
                       UTILS_ARRAYSIZE(pObj->memUsed));
    #ifdef SYSTEM_DEBUG_DEC
    Vps_printf(" DECODE: Create ... DONE !!!\n" );
    #endif

    #ifdef SYSTEM_DEBUG_MEMALLOC
    Vps_printf (" After DEC Create:\n");
    System_memPrintHeapStatus();
    #endif
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function gets the input bistream buffers and put the same
 *        into appropriate channel specific intermediate queue
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecQueueBufsToChQue(DecLink_Obj * pObj)
{
    UInt32 bufId, freeBufNum;
    System_Buffer *pBuf;
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList;
    DecLink_ChObj *pChObj;
    Int32 status;
    System_BitstreamBuffer *bitBuf;
    Bool keyFrame, flushFrame;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pInQueParams = &pObj->createArgs.inQueParams;

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &bufList);

    if (bufList.numBuf)
    {
        freeBufNum = 0;
        linkStatsInfo->linkStats.getFullBufCount += bufList.numBuf;

        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {
            pBuf = bufList.buffers[bufId];

            if (pBuf->chNum >= pObj->inQueInfo.numCh)
            {
                bufList.buffers[freeBufNum] = pBuf;
                freeBufNum++;
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }
            linkStatsInfo->linkStats.chStats[pBuf->chNum].inBufRecvCount++;

            bitBuf = pBuf->payload;

            pChObj = &pObj->chObj[pBuf->chNum];

            keyFrame =
                 System_Bitstream_Buffer_Flag_Get_Is_Keyframe(bitBuf->flags);

            flushFrame =
                 System_Bitstream_Buffer_Flag_Get_Is_Flushbuf(bitBuf->flags);

            // pBuf->fid = pChObj->nextFid;
            if(pChObj->disableChn && pChObj->skipFrame == FALSE)
            {
                pChObj->skipFrame = TRUE;
            }
            else if((pChObj->disableChn == FALSE) && pChObj->skipFrame)
            {
                if(TRUE == keyFrame)
                {
                    pChObj->skipFrame = FALSE;
                }
            }

            if (((   ((pChObj->IFrameOnlyDecode) && (!keyFrame))
                || pChObj->skipFrame
                || (pChObj->algCreateStatusLocal !=
                      DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE)))
               &&
               (!flushFrame))
            {
                bufList.buffers[freeBufNum] = pBuf;
                freeBufNum++;
                linkStatsInfo->linkStats.chStats[pBuf->chNum].inBufDropCount++;
            }
            else
            {
                if ((pChObj->algCreateStatusLocal !=
                       DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE)
                    &&
                    (TRUE == flushFrame))
                {
                    DecLink_ReqObj *pReqObj = NULL;
                    UInt32 tskId;

                    UTILS_assert(Utils_queIsEmpty(&pChObj->inQue) == TRUE);
                    status =
                        Utils_queGet(&pObj->reqQue, (Ptr *) & pReqObj, 1,
                                     BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == 0);
                    pReqObj->type = DEC_LINK_REQ_OBJECT_TYPE_DUMMY_FLUSHFRAME;
                    pReqObj->InBuf = pBuf;
                    pReqObj->OutFrameList.numBuf = 0;
                    pReqObj->OutFrameList.buffers[0] = NULL;

                    tskId = 0;

                    #ifdef SYSTEM_DEBUG_DEC
                    Vps_printf( " DECODE: CH%d: %s\n", pBuf->chNum,
                                "Queing flush Frame to processQ");
                    #endif
                    status =
                    Utils_quePut(&pObj->decProcessTsk[tskId].processQue,
                                 pReqObj, BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                else
                {
                    status = Utils_quePut(&pChObj->inQue, pBuf, BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
            }
        }

        if (freeBufNum)
        {
            bufList.numBuf = freeBufNum;
            linkStatsInfo->linkStats.putEmptyBufCount += bufList.numBuf;
            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                        pInQueParams->prevLinkQueId, &bufList);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function gets the input bistream buffers from inQueue
 *        and an empty output frame from Output buffer pool
 *        Populate a request object with above info
 *        Place the request object into process Queue
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecSubmitData(DecLink_Obj * pObj)
{
    DecLink_ReqObj *pReqObj;
    DecLink_ChObj *pChObj;
    UInt32 chCount,chIdIndex;
    System_Buffer *pInBuf;
    System_Buffer *pOutFrame = NULL; /* init to NULL */
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 tskId, i;
    static UInt32 startChID = 0;
    System_BitstreamBuffer *bitBuf;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    chIdIndex    = startChID;
    for (chCount = 0; chCount < pObj->inQueInfo.numCh; chCount++,chIdIndex++)
    {
      if (chIdIndex >= pObj->inQueInfo.numCh)
          chIdIndex = 0;
      pChObj = &pObj->chObj[chIdIndex];
      if (Utils_queIsEmpty(&pObj->outObj.bufOutQue.
                           emptyQue[pChObj->allocPoolID]))
      {
          pObj->newDataProcessOnFrameFree = TRUE;
      }

      status =
          Utils_queGet(&pObj->reqQue, (Ptr *) & pReqObj, 1,
                       BSP_OSAL_NO_WAIT);

      if (UTILS_ISERROR(status)) {
          break;
      }
      pReqObj->type = DEC_LINK_REQ_OBJECT_TYPE_REGULAR;

      tskId = 0;

      if ((pChObj->algObj.algCreateParams.fieldMergeDecodeEnable) &&
          (pChObj->algObj.algCreateParams.processCallLevel ==
                          IH264VDEC_FIELDLEVELPROCESSCALL))
      {
         /* pReqObj->OutFrameList.numBuf should be set to 2 if     */
         /* fieldMergeDecodeEnable is enabled. In this case same      */
         /* input buffer will have both field data and hence decoder  */
         /* should be called twice in a loop to process both fields   */
         /* and each call should go with a seperate output buffer     */
          pReqObj->OutFrameList.numBuf = 2;
      }
      else
      {
          pReqObj->OutFrameList.numBuf = 1;
      }
      if ((status == SYSTEM_LINK_STATUS_SOK) &&
          (Utils_queGetQueuedCount(&pChObj->inQue)) &&
          (Utils_queGetQueuedCount(&pObj->outObj.bufOutQue.emptyQue[pChObj->
                 allocPoolID]) >= pReqObj->OutFrameList.numBuf) &&
          !(Utils_queIsFull(&pObj->decProcessTsk[tskId].processQue)))
      {
          pOutFrame = NULL; /* init to NULL */
          for (i=0; i<pReqObj->OutFrameList.numBuf; i++)
          {
              pOutFrame = NULL;
              status =
                  Utils_bufGetEmptyBufferExt(&pObj->outObj.bufOutQue,
                                             &pOutFrame,
                                             chIdIndex,
                                             BSP_OSAL_NO_WAIT);
              if (pOutFrame)
              {
                  declink_codec_init_outframe(pObj, chIdIndex, pOutFrame);
                  pReqObj->OutFrameList.buffers[i] = pOutFrame;
                  linkStatsInfo->linkStats.chStats[chIdIndex].outBufCount[0]++;
              }
              else
              {
                  break;
              }
          }
          if ((status == SYSTEM_LINK_STATUS_SOK) && (pOutFrame))
          {
              Utils_queGet(&pChObj->inQue, (Ptr *) & pInBuf, 1, BSP_OSAL_NO_WAIT);
              UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
              bitBuf = pInBuf->payload;
              if (System_Bitstream_Buffer_Flag_Get_Is_Flushbuf(bitBuf->flags))
              {
                  pReqObj->type = DEC_LINK_REQ_OBJECT_TYPE_DUMMY_FLUSHFRAME;
                  #ifdef SYSTEM_DEBUG_DEC
                  Vps_printf( " DECODE: CH%d: %s\n", pInBuf->chNum,
                              "Queing flush Frame to processQ");
                  #endif
              }
              pReqObj->InBuf = pInBuf;

              for (i=0; i<pReqObj->OutFrameList.numBuf; i++)
              {
                  pReqObj->OutFrameList.buffers[i]->chNum = pInBuf->chNum;
                  pReqObj->OutFrameList.buffers[i]->srcTimestamp=
                             pInBuf->srcTimestamp;
                  pReqObj->OutFrameList.buffers[i]->frameId=
                             pInBuf->frameId;
                  pReqObj->OutFrameList.buffers[i]->linkLocalTimestamp =
                             Utils_getCurGlobalTimeInUsec();
              }
              linkStatsInfo->linkStats.chStats[pInBuf->chNum].inBufProcessCount++;
              status =
                  Utils_quePut(&pObj->decProcessTsk[tskId].processQue,
                               pReqObj, BSP_OSAL_NO_WAIT);
              UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
              pChObj->processReqestCount++;
          }
          else
          {
              status = Utils_quePut(&pObj->reqQue, pReqObj, BSP_OSAL_NO_WAIT);
              startChID = chIdIndex;
              UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
              status = SYSTEM_LINK_STATUS_EFAIL;
              continue;
          }
      }
      else
      {
          status = Utils_quePut(&pObj->reqQue, pReqObj, BSP_OSAL_NO_WAIT);
          UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
          startChID = chIdIndex;
          status = SYSTEM_LINK_STATUS_EFAIL;
          if (Utils_queIsEmpty(&pObj->outObj.bufOutQue.
                               emptyQue[pChObj->allocPoolID]))
          {
              pObj->newDataProcessOnFrameFree = TRUE;
          }
      }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This is the Top level process data call initiate by NEW_DATA
 *        command from previous link
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecProcessData(DecLink_Obj * pObj)
{
    Int32 status;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    if(pObj->isFirstFrameRecv==FALSE)
    {
        pObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
                &linkStatsInfo->linkStats,
                pObj->inQueInfo.numCh,
                DEC_LINK_MAX_OUT_QUE);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);
    linkStatsInfo->linkStats.newDataCmdCount++;



    pObj->newDataProcessOnFrameFree = FALSE;
    DecLink_codecQueueBufsToChQue(pObj);

    do
    {
        status = DecLink_codecSubmitData(pObj);
    } while (status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function has the logic to skip frames after decode
 *        if the link after Declink hold more frames than the
 *        threshold value set by application
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   chId  [IN] Channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecCheckFrameSkipDue2AccumuInNextLink (DecLink_Obj * pObj,
                                                       UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    DecLink_ChObj *pChObj;

    pChObj = &pObj->chObj[chId];
    pChObj->skipFrameDue2AccumuInNextLink = FALSE;

    if ((TRUE ==
       pObj->createArgs.chCreateParams[chId].enableFrameSkipDue2AccumuInNextLink)
        &&
       (DEC_LINK_FRAMESKIP_DUE2ACCUM_THRESHOLD <
        pObj->createArgs.chCreateParams[chId].numBufPerCh))
    {
        if (DEC_LINK_FRAMESKIP_DUE2ACCUM_THRESHOLD >=
            Utils_queGetQueuedCount(&pObj->outObj.bufOutQue.emptyQue[chId]))
        {
            pChObj->skipFrameDue2AccumuInNextLink = TRUE;
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function has the logic to
 *        - Recollect the request after decode
 *        - Free-up the input frames
 *        - Send-out the filled output frames to next link
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecGetProcessedData(DecLink_Obj * pObj)
{
    System_BufferList inBufList;
    System_BufferList outFrameList;
    System_BufferList outFrameSkipList;
    UInt32 chId, sendCmd;
    System_LinkInQueParams *pInQueParams;
    DecLink_ChObj *pChObj;
    DecLink_ReqObj *pReqObj;
    Int32 status, j;
    System_BitstreamBuffer *bitBuf;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    sendCmd = FALSE;
    inBufList.numBuf = 0;
    outFrameList.numBuf = 0;
    outFrameSkipList.numBuf = 0;

    while(!Utils_queIsEmpty(&pObj->processDoneQue)
          &&
          (inBufList.numBuf < (SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST - 1))
          &&
          (outFrameList.numBuf < (SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST - 1)))
    {
        status = Utils_queGet(&pObj->processDoneQue, (Ptr *) & pReqObj, 1,
                              BSP_OSAL_NO_WAIT);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }

        UTILS_assert(pReqObj->InBuf != NULL);
        chId = pReqObj->InBuf->chNum;
        pChObj = &pObj->chObj[chId];

        pChObj->getProcessDoneCount++;

        bitBuf = (System_BitstreamBuffer*) pReqObj->InBuf->payload;
        UTILS_assert(bitBuf != NULL);

        if (System_Bitstream_Buffer_Flag_Get_Is_Flushbuf(bitBuf->flags))
        {
            #ifdef SYSTEM_DEBUG_DEC
            Vps_printf( " DECODE: CH%d: %s\n", pReqObj->InBuf->chNum,
                        "Freeing flush Frame");
            #endif
        }
        inBufList.buffers[inBufList.numBuf] = pReqObj->InBuf;
        inBufList.numBuf++;

        for (j = 0; j < pReqObj->OutFrameList.numBuf; j++)
        {
            if (pReqObj->OutFrameList.buffers[j])
            {
                UTILS_assert(pReqObj->InBuf->chNum ==
                             pReqObj->OutFrameList.buffers[j]->chNum);
                UTILS_assert(pChObj->allocPoolID < UTILS_BUF_MAX_ALLOC_POOLS);

                pChObj->trickPlayObj.skipFrame =
                    Utils_doSkipBuf(&(pChObj->trickPlayObj.frameSkipCtx));

                DecLink_codecCheckFrameSkipDue2AccumuInNextLink (
                    pObj, pReqObj->InBuf->chNum);

                if ((pChObj->trickPlayObj.skipFrame == TRUE) ||
                    (pChObj->skipFrameDue2AccumuInNextLink == TRUE))
                {
                    /* Skip the output frame */
                    outFrameSkipList.buffers[outFrameSkipList.numBuf] =
                                        pReqObj->OutFrameList.buffers[j];
                    outFrameSkipList.numBuf++;
                    linkStatsInfo->linkStats.chStats[
                          pReqObj->InBuf->chNum].outBufDropCount[0]++;
                    linkStatsInfo->linkStats.chStats[
                          pReqObj->InBuf->chNum].outBufUserDropCount[0]++;
                }
                else
                {
                    outFrameList.buffers[outFrameList.numBuf] =
                                        pReqObj->OutFrameList.buffers[j];

                    if(pObj->createArgs.callback)
                    {
                        status = pObj->createArgs.callback(
                            pObj->createArgs.appObj,
                            outFrameList.buffers[outFrameList.numBuf]
                            );
                    }
                    outFrameList.numBuf++;
                }
            }
        }
        status = Utils_quePut(&pObj->reqQue, pReqObj, BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    if (outFrameList.numBuf)
    {
        for (j=0; j<outFrameList.numBuf; j++)
        {
            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                outFrameList.buffers[j]->linkLocalTimestamp);
            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                outFrameList.buffers[j]->srcTimestamp);
        }

        status = Utils_bufPutFullExt(&pObj->outObj.bufOutQue,
                                     &outFrameList);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        sendCmd = TRUE;
    }

    if (outFrameSkipList.numBuf)
    {
        status = DecLink_codecFreeProcessedFrames(pObj, &outFrameSkipList);
        UTILS_assert(status == DEC_LINK_S_SUCCESS);
    }

    if (inBufList.numBuf)
    {
        /* Free input frames */
        linkStatsInfo->linkStats.putEmptyBufCount += inBufList.numBuf;
        pInQueParams = &pObj->createArgs.inQueParams;
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &inBufList);
    }

    /* Send-out the output bitbuffer */
    if (sendCmd == TRUE)
    {
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA, NULL);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Top level function to process the frames after decode call complete
 *        - Recollect the request after decode
 *        - Free-up the input frames
 *        - Send-out the filled output frames to next link
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecGetProcessedDataMsgHandler(DecLink_Obj * pObj)
{
    Int32 status;

    pObj->linkStatsInfo->linkStats.releaseDataCmdCount++;

    status = DecLink_codecGetProcessedData(pObj);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return DEC_LINK_S_SUCCESS;

}

/**
 *******************************************************************************
 *
 * \brief Function to free-up all the input bitstream buffers which are
 *        present in the output Full Queue of the previous Link
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecFreeInQueuedBufs(DecLink_Obj * pObj)
{
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    pInQueParams = &pObj->createArgs.inQueParams;
    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &bufList);
    if (bufList.numBuf)
    {
        pObj->linkStatsInfo->linkStats.getFullBufCount += bufList.numBuf;
        pObj->linkStatsInfo->linkStats.putEmptyBufCount += bufList.numBuf;
        /* Free input frames */
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &bufList);
    }
    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief Function to stop the DecLink and free-up all the input bitstream
 *        buffers which are present inside the DecLink pending for process
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecStop(DecLink_Obj * pObj)
{
    Int32 rtnValue = SYSTEM_LINK_STATUS_SOK;
    UInt32 tskId;

       #ifdef SYSTEM_DEBUG_DEC
       Vps_printf(" DECODE: Stop in progress !!!\n" );
       #endif

    for (tskId = 0; tskId < NUM_HDVICP_RESOURCES; tskId++)
    {
        Utils_queUnBlock(&pObj->decProcessTsk[tskId].processQue);
    }
#if 0
    while (!Utils_queIsFull(&pObj->reqQue))
    {
        Utils_tskWaitCmd(&pObj->tsk, NULL, DEC_LINK_CMD_GET_PROCESSED_DATA);
        DecLink_codecGetProcessedDataMsgHandler(pObj);
    }
#endif
    DecLink_codecFreeInQueuedBufs(pObj);

       #ifdef SYSTEM_DEBUG_DEC
       Vps_printf(" DECODE: Stop Done !!!\n" );
       #endif

    return (rtnValue);
}

/**
 *******************************************************************************
 *
 * \brief This Function delete the Dclink intermediate Channel Object/Queue
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   chId  [IN] Declink channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecDeleteChObj(DecLink_Obj * pObj, UInt32 chId)
{
    DecLink_ChObj *pChObj;
    Int32 status;

    pChObj = &pObj->chObj[chId];

    status = Utils_queDelete(&pChObj->inQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This Function delete the codec instance
 *        Also free-up/de-allocate the output buffers/memory
 *
 * \param   pObj  [IN] Declink Object Dec link object
 * \param   chId  [IN] Declink channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecDeleteChannel(DecLink_Obj * pObj, UInt32 chId)
{
    Int retVal = DEC_LINK_S_SUCCESS;
    DecLink_ChObj *pChObj;
    DecLink_OutObj *pOutObj;
    UInt32 frameId;
    Int32 status;
    FVID2_Frame  fvid2Frame;

    UTILS_assert(chId <= pObj->inQueInfo.numCh);
    if (pObj->createArgs.chCreateParams[chId].algCreateStatus ==
                         DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE)
    {
        pChObj = &pObj->chObj[chId];
        pOutObj = &pObj->outObj;

        switch (pChObj->algObj.algCreateParams.format)
        {
            case SYSTEM_IVIDEO_MJPEG:
                DecLinkJPEG_algDelete(&pChObj->algObj.u.jpegAlgIfObj);
                break;

            case SYSTEM_IVIDEO_H264BP:
            case SYSTEM_IVIDEO_H264MP:
            case SYSTEM_IVIDEO_H264HP:
                DecLinkH264_algDelete(&pChObj->algObj.u.h264AlgIfObj);
                break;

            default:
                retVal = DEC_LINK_E_UNSUPPORTEDCODEC;
                break;
        }
        UTILS_assert(retVal == DEC_LINK_S_SUCCESS);

        for (frameId = 0;
             frameId < pOutObj->outChObj[chId].outNumFrames; frameId++)
        {
            {
                status = Utils_bufInitFrame(&fvid2Frame,
                               &pOutObj->outChObj[chId].allocFrames[frameId]);
                status = Utils_memFrameFree(&pOutObj->outChObj[chId].outFormat,
                               &fvid2Frame,
                               1,
                               0);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                if(pOutObj->outChObj[chId].videoFrames[frameId].metaBufAddr
                    != NULL
                    )
                {
                    status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pOutObj->outChObj[chId].videoFrames[frameId].metaBufAddr,
                        pOutObj->outChObj[chId].videoFrames[frameId].metaBufSize
                        );

                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
            }

        }
        pObj->createArgs.chCreateParams[chId].algCreateStatus =
                         DEC_LINK_ALG_CREATE_STATUS_DELETE;
        pChObj->algCreateStatusLocal = DEC_LINK_ALG_CREATE_STATUS_DELETE;

        pObj->outObj.totalNumOutBufs -= pOutObj->outChObj[chId].outNumFrames;

    }
    else
    {
        #ifdef SYSTEM_DEBUG_DEC
        Vps_printf(
            " DECODE: CodecInst and OutFrm bufs were NOT created for CH%d\n",
            chId            );
        #endif
    }

    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This Function delete the DecLink instance
 *        Also delete the IVA process task and process queues
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecDelete(DecLink_Obj * pObj)
{
    Int32 status;
    UInt32 outId, chId, tskId;
    DecLink_OutObj *pOutObj;

    #ifdef SYSTEM_DEBUG_DEC
    Vps_printf(" DECODE: Delete in progress !!!\n"  );
    #endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status==0);

    pObj->state = UTILS_ENCDEC_STATE_STOP;
    for (tskId = 0; tskId < NUM_HDVICP_RESOURCES; tskId++)
    {
        DecLink_codecDeleteProcessTsk(pObj, tskId);
        Utils_queDelete(&pObj->decProcessTsk[tskId].processQue);
    }

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        DecLink_codecDeleteChObj(pObj, chId);
        DecLink_codecDeleteChannel(pObj, chId);
    }

    Utils_queDelete(&pObj->processDoneQue);
    DecLink_codecDeleteDupObj(pObj);

    for (outId = 0; outId < DEC_LINK_MAX_OUT_QUE; outId++)
    {
        pOutObj = &pObj->outObj;

        Utils_bufDeleteExt(&pOutObj->bufOutQue);
    }

    Utils_queDelete(&pObj->reqQue);

    DecLink_codecDeleteReqObjDummy(pObj);

    #ifdef SYSTEM_DEBUG_DEC
    Vps_printf(" DECODE: Delete Done !!!\n" );
    #endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to reset the Statistics
 *
 * \param   pObj  [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_resetStatistics(DecLink_Obj * pObj)
{
    UInt32 chId;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        memset (&pObj->linkStatsInfo->linkStats.chStats[chId],
                 0,
                 sizeof(Utils_LinkChStatistics));
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to print the DecLink Statistics
 *
 * \param   pObj            [IN] Declink Object Dec link object
 * \param   resetAfterPrint [IN] flag to reset stats after print
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_printStatistics (DecLink_Obj * pObj, Bool resetAfterPrint)
{
    UInt32 chId;
    DecLink_ChObj *pChObj;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "DECODE", TRUE);

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        Vps_printf( " Num frames inside the codec for chId: %d = %d \n",
                      chId, pChObj->numBufsInCodec);
        Vps_printf( " Num process reqest count for chId: %d = %d \n",
                      chId, pChObj->processReqestCount);
        Vps_printf( " Num process complete count for chId: %d = %d \n",
                      chId, pChObj->getProcessDoneCount);
    }

    Utils_printLatency("DECODE",
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    if(resetAfterPrint)
    {
        DecLink_resetStatistics(pObj);
    }

   return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to dup the output frame if it required to be held by
 *        decoder as a refernce frame
 *
 * \param   pObj       [IN] Declink Object Dec link object
 * \param   pOrgFrame  [IN] Original decoded buffer pointer
 * \param   ppDupFrame [OUT] Pointer to Duppped buffer address
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_dupFrame(DecLink_Obj * pObj, System_Buffer * pOrgFrame,
                              System_Buffer ** ppDupFrame)
{
    Int status = DEC_LINK_S_SUCCESS;
    System_Buffer *pFrame;
    Utils_EncDecLinkPvtInfo *pFrameInfo, *pOrgFrameInfo;

    status =
        Utils_queGet(&pObj->dupObj.dupQue, (Ptr *) & pFrame, 1, BSP_OSAL_NO_WAIT);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pFrame != NULL);
    pFrameInfo = (Utils_EncDecLinkPvtInfo *) pFrame->pEncDecLinkPrivate;
    UTILS_assert(pFrameInfo != NULL);
    while (((Utils_EncDecLinkPvtInfo *)
             pOrgFrame->pEncDecLinkPrivate)->pDupOrgFrame != NULL)
    {
        pOrgFrame =
        ((Utils_EncDecLinkPvtInfo *) pOrgFrame->pEncDecLinkPrivate)->pDupOrgFrame;
    }
    pOrgFrameInfo = pOrgFrame->pEncDecLinkPrivate;
    memcpy(pFrame, pOrgFrame, sizeof(*pOrgFrame));
    pOrgFrameInfo = pOrgFrame->pEncDecLinkPrivate;
    memcpy(pFrameInfo, pOrgFrameInfo, sizeof(*pOrgFrameInfo));

    pFrame->pEncDecLinkPrivate = pFrameInfo;
    pFrameInfo->pDupOrgFrame = pOrgFrame;
    UTILS_assert(pOrgFrameInfo->dupRefCount <= DEC_LINK_MAX_DUP_PER_FRAME);
    pOrgFrameInfo->dupRefCount++;
    *ppDupFrame = pFrame;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to Disable a decodeLink channel
 *
 * \param   pObj    [IN] Declink Object Dec link object
 * \param   params  [IN] DecLink_ChannelInfo channel info (chID)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecDisableChannel(DecLink_Obj * pObj,
                              DecLink_ChannelInfo* params)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    DecLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->disableChn = TRUE;
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to Enable a decodeLink channel
 *
 * \param   pObj    [IN] Declink Object Dec link object
 * \param   params  [IN] DecLink_ChannelInfo channel info (chID)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecEnableChannel(DecLink_Obj * pObj,
                              DecLink_ChannelInfo* params)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    DecLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->disableChn = FALSE;
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to Set T-play related configuration/per channel
 *
 * \param   pObj    [IN] Declink Object Dec link object
 * \param   params  [IN] DecLink_TPlayConfig T-play channel info details
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_setTPlayConfig(DecLink_Obj * pObj,
                             DecLink_TPlayConfig* params)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    DecLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->trickPlayObj.frameSkipCtx.inputFrameRate = params->inputFps;
    pChObj->trickPlayObj.frameSkipCtx.outputFrameRate = params->targetFps;
    pChObj->trickPlayObj.frameSkipCtx.firstTime = TRUE;

    Vps_printf("\r\n DecLink_setTPlayConfig : Ch :%d"
         "InputputFrameRate :%d, trickPlay outputFrameRate: %d ",
         params->chId,
         pChObj->trickPlayObj.frameSkipCtx.inputFrameRate,
         pChObj->trickPlayObj.frameSkipCtx.outputFrameRate);

    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This Function prints Declink Buffer status
 *
 * \param   pObj [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_printBufferStatus (DecLink_Obj * pObj)
{
    Uint8 str[256];

    sprintf ((char *)str, " DECODE OUT ");
    Utils_bufExtPrintStatus(str, &pObj->outObj.bufOutQue);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This Function get/collect the Declink Buffer status
 *
 * \param   pObj     [IN] Declink Object Dec link object
 * \param   bufStats [OUT] DecLink_BufferStats Dec link buffer status object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_getBufferStatus (DecLink_Obj * pObj,DecLink_BufferStats *bufStats)
{
    Int i;
    UInt32 chId;

    /* First queue all input frames to channel specific queu */
    DecLink_codecQueueBufsToChQue(pObj);
    for (i = 0; i < bufStats->numCh; i++)
    {
        chId = bufStats->chId[i];
        if (chId < UTILS_ARRAYSIZE(pObj->chObj))
        {
            bufStats->stats[chId].numInBufQueCount =
                      Utils_queGetQueuedCount(&pObj->chObj[chId].inQue);
            bufStats->stats[chId].numOutBufQueCount =
             pObj->outObj.outChObj[chId].outNumFrames -
             Utils_queGetQueuedCount(&pObj->outObj.bufOutQue.emptyQue[chId]);
        }
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This Function maps the display delay to codec specific parameter
 *
 * \param   displayDelay  [IN] Declink display delay
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 decLink_map_displayDelay2CodecParam(Int32 displayDelay)
{
    Int32 VdecMaxDisplayDelay;

    if ((displayDelay >= IVIDDEC3_DISPLAY_DELAY_AUTO)
        &&
        (displayDelay <= IVIDDEC3_DISPLAY_DELAY_16))
    {
        VdecMaxDisplayDelay =  displayDelay;
    }
    else
    {
       Vps_printf(" DECLINK: Invalid param passed for MaxDisplayDelay param [%d] "
                  "Forcing to default value [%d]\n",
                  displayDelay,
                  IVIDDEC3_DECODE_ORDER);
       VdecMaxDisplayDelay =  IVIDDEC3_DECODE_ORDER;
    }

    return VdecMaxDisplayDelay;
}

/**
 *******************************************************************************
 *
 * \brief This is the top level Function to create/open a new channel
 *
 * \param   pObj   [IN] Declink Object Dec link object
 * \param   params [OUT] DecLink_CreateChannelInfo channel create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecCreateChannelHandler(DecLink_Obj * pObj,
                                        DecLink_CreateChannelInfo* params)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    DecLink_ChObj *pChObj;
    UInt32 chId;
    UInt key;

    chId = params->chId;
    UTILS_assert(chId <= pObj->inQueInfo.numCh);
    pChObj = &pObj->chObj[chId];
    UTILS_assert(params->createPrm.algCreateStatus ==
                         DEC_LINK_ALG_CREATE_STATUS_CREATE);

    if (pObj->createArgs.chCreateParams[chId].algCreateStatus ==
                         DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE)
    {
        Vps_printf(" DECLINK: ERROR!!! During Channel Open, "
                   "CH%d is alreday in open state (opened earlier): "
                   "close first and try open the channel again \n ", chId);
        return (status);
    }

    key = Hwi_disable();
    pChObj->algCreateStatusLocal = DEC_LINK_ALG_CREATE_STATUS_CREATE;
    memcpy (&pObj->inQueInfo.chInfo[chId], &params->chInfo,
                                           sizeof (System_LinkChInfo));
    memcpy(&pObj->createArgs.chCreateParams[chId], &params->createPrm,
                                           sizeof(DecLink_ChCreateParams));

    UTILS_assert(Utils_queGetQueuedCount(
                 &pObj->outObj.bufOutQue.emptyQue[chId]) == 0);
    status = Utils_queReset(&pObj->outObj.bufOutQue.emptyQue[chId]);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Hwi_restore(key);

    status = DecLink_codecCreateChannel(pObj, chId);
    if (status == DEC_LINK_S_SUCCESS)
    {
        key = Hwi_disable();
        pChObj->algCreateStatusLocal = DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE;
        Hwi_restore(key);
        #ifdef SYSTEM_DEBUG_DEC
        Vps_printf(" DECODE: CH%d: Decoder Create CH done!!!\n", chId );
        #endif
    }
    else
    {
        DecLink_ChannelInfo params;
        params.chId = chId;
        DecLink_codecDeleteChannelHandler(pObj, &params);
        Vps_printf(" DECLINK: ERROR!!! During Channel Open, "
                   "Need more memory to open new CH%d; "
                   "Delete a few other channels and try again \n ", chId);
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This is the top level Function to delete/close
 *        an alreday created/opened channel
 *
 * \param   pObj   [IN] Declink Object Dec link object
 * \param   params [OUT] DecLink_ChannelInfo channel identifier parameter
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DecLink_codecDeleteChannelHandler(DecLink_Obj * pObj,
                                        DecLink_ChannelInfo* params)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    UInt32 chId, tskId, frameId;
    DecLink_ChObj *pChObj;
    Utils_EncDecLinkPvtInfo *pFrameInfo;
    DecLink_ReqObj *pReqObj;
    System_Buffer *pInBuf;
    System_BufferList inBufList;
    System_LinkInQueParams *pInQueParams;
    UInt key;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    chId = params->chId;
    UTILS_assert(chId <= pObj->inQueInfo.numCh);
    pChObj = &pObj->chObj[chId];
    tskId = 0;

    key = Hwi_disable();
    pChObj->algCreateStatusLocal = DEC_LINK_ALG_CREATE_STATUS_DELETE;
    for (frameId = 0;
         frameId < pObj->outObj.outChObj[chId].outNumFrames; frameId++)
    {
        pFrameInfo = (Utils_EncDecLinkPvtInfo *)
              pObj->outObj.outChObj[chId].outFrames[frameId]->pEncDecLinkPrivate;
        UTILS_assert(pFrameInfo != NULL);
        pFrameInfo->invalidFrame = TRUE;
    }
    Hwi_restore(key);

    inBufList.numBuf = 0;
    while (Utils_queGetQueuedCount(&pChObj->inQue))
    {
        Utils_queGet(&pChObj->inQue, (Ptr *) & pInBuf, 1, BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        inBufList.buffers[inBufList.numBuf] = pInBuf;
        inBufList.numBuf++;
        if (inBufList.numBuf > SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST/2)
        {
            /* Free input frames */
            linkStatsInfo->linkStats.putEmptyBufCount += inBufList.numBuf;
            pInQueParams = &pObj->createArgs.inQueParams;
            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                        pInQueParams->prevLinkQueId, &inBufList);
            inBufList.numBuf = 0;
        }
    }

    if (inBufList.numBuf)
    {
        /* Free input frames */
        linkStatsInfo->linkStats.putEmptyBufCount += inBufList.numBuf;
        pInQueParams = &pObj->createArgs.inQueParams;
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &inBufList);
        inBufList.numBuf = 0;
    }

    status = Utils_queGet(&pObj->decDummyReqObj.reqQueDummy, (Ptr *) & pReqObj, 1,
                          BSP_OSAL_NO_WAIT);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(UTILS_ARRAYISVALIDENTRY(pReqObj,pObj->decDummyReqObj.reqObjDummy));
    pChObj->dummyBitBuf.chNum = chId;
    pReqObj->InBuf = &pChObj->dummyBitBuf;
    pReqObj->type = DEC_LINK_REQ_OBJECT_TYPE_DUMMY_CHDELETE;
    status = Utils_quePut(&pObj->decProcessTsk[tskId].processQue,
                           pReqObj, BSP_OSAL_NO_WAIT);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Vps_printf(" DEC : Delete CH%d, Dummy Object queued !!!\n", chId);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This Function Flush and delete the channel,
 *        This gets called internally from DecLink_codecDeleteChannelHandler()
 *
 * \param   pObj   [IN] Declink Object Dec link object
 * \param   chId   [IN] DecLink channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecFlushNDeleteChannel(DecLink_Obj * pObj, UInt32 chId)
{
    Int32 status = DEC_LINK_S_SUCCESS;
    DecLink_ChObj *pChObj;
    Utils_EncDecLinkPvtInfo *pFrameInfo;
    System_Buffer  *frame;
    System_BufferList freeFrameList;

    freeFrameList.numBuf = 0;
    if (pObj->createArgs.chCreateParams[chId].algCreateStatus ==
                         DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE)
    {
        pChObj = &pObj->chObj[chId];

        switch (pChObj->algObj.algCreateParams.format)
        {
            case SYSTEM_IVIDEO_MJPEG:
                break;

            case SYSTEM_IVIDEO_H264BP:
            case SYSTEM_IVIDEO_H264MP:
            case SYSTEM_IVIDEO_H264HP:
                DecLinkH264_codecFlush(pChObj,
                                       &pChObj->algObj.u.h264AlgIfObj.inArgs,
                                       &pChObj->algObj.u.h264AlgIfObj.outArgs,
                                       &pChObj->algObj.u.h264AlgIfObj.inBufs,
                                       &pChObj->algObj.u.h264AlgIfObj.outBufs,
                                       pChObj->algObj.u.h264AlgIfObj.algHandle,
                                       &freeFrameList, TRUE);
                break;

            default:
                status = DEC_LINK_E_UNSUPPORTEDCODEC;
                break;
        }
        UTILS_assert(status == DEC_LINK_S_SUCCESS);
    }

    if (freeFrameList.numBuf)
    {
        DecLink_codecFreeProcessedFrames(pObj, &freeFrameList);
    }

    DecLink_codecDeleteChannel(pObj, chId);

    while (Utils_queGetQueuedCount(&pObj->outObj.bufOutQue.emptyQue[chId]))
    {
        status = Utils_queGet(&pObj->outObj.bufOutQue.emptyQue[chId],
                             (Ptr *)&frame,1,BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        pFrameInfo = (Utils_EncDecLinkPvtInfo *) frame->pEncDecLinkPrivate;
        UTILS_assert(pFrameInfo != NULL);
        UTILS_assert(pFrameInfo->invalidFrame == TRUE);
        pFrameInfo->invalidFrame = FALSE;
        status = Utils_quePut(&pObj->outObj.outChObj[chId].outFrameQue,
                              frame, BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    status = System_sendLinkCmd(pObj->linkId, DEC_LINK_CMD_LATE_ACK, NULL);

    if (UTILS_ISERROR(status))
    {
        Vps_printf(" DECLINK:[%s:%d]:"
                   "System_sendLinkCmd DEC_LINK_CMD_LATE_ACK failed"
                   "errCode = %d", __FILE__, __LINE__, status);
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This Function create the Dummy request object used while,
 *        - Delete channel,
 *        - Flush frame process
 *
 * \param   pObj   [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecCreateReqObjDummy(DecLink_Obj * pObj)
{
    Int32 status;
    UInt32 reqId;
    struct decDummyReqObj_s *dummyReq = &pObj->decDummyReqObj;

    memset(dummyReq->reqObjDummy, 0, sizeof(dummyReq->reqObjDummy));

    UTILS_COMPILETIME_ASSERT(UTILS_ARRAYSIZE(dummyReq->reqQueMemDummy) ==
                             UTILS_ARRAYSIZE(dummyReq->reqObjDummy));
    status = Utils_queCreate(&dummyReq->reqQueDummy,
                             UTILS_ARRAYSIZE(dummyReq->reqQueMemDummy),
                             dummyReq->reqQueMemDummy,
                             UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (reqId = 0; reqId < UTILS_ARRAYSIZE(dummyReq->reqObjDummy); reqId++)
    {
        status =
            Utils_quePut(&dummyReq->reqQueDummy,
                         &dummyReq->reqObjDummy[reqId], BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This Function delete the Dummy request object used while,
 *        - Delete channel,
 *        - Flush frame process
 *
 * \param   pObj   [IN] Declink Object Dec link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 DecLink_codecDeleteReqObjDummy(DecLink_Obj * pObj)
{
    struct decDummyReqObj_s *dummyReq = &pObj->decDummyReqObj;
    Int32 status;

    status = Utils_queDelete(&dummyReq->reqQueDummy);

    UTILS_assert(status == 0);

    return DEC_LINK_S_SUCCESS;
}

/* Nothing beyond this point */



