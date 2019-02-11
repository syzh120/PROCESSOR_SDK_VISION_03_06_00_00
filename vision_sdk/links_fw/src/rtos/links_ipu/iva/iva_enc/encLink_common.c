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
 * \file encLink_common.c Implement the Multichannel Encode Link
 *         - Enc link input/output queue interface
 *         - Create codec instance and allocate the ouput buffers
 *
 * \version 0.0 (April 2014) : [SS] First version
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
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include <src/rtos/links_ipu/iva/codec_utils/hdvicp2_config.h>
#include "encLink_priv.h"
#include "encLink_jpeg_priv.h"
#include "encLink_h264_priv.h"

/*******************************************************************************
 *  \brief Resolution class internal data structure
 *******************************************************************************
 */
typedef struct encLinkResClassChannelInfo {
    UInt32 numActiveResClass;
    struct resInfo_s {
        EncDec_ResolutionClass resClass;
        UInt32 width;
        UInt32 height;
        UInt32 numChInResClass;
        UInt32 chIdx[ENC_LINK_MAX_CH];
    } resInfo[UTILS_ENCDEC_RESOLUTION_CLASS_COUNT];
} encLinkResClassChannelInfo;

/*******************************************************************************
 *  Encode Link Private Functions
 *******************************************************************************
 */
static
EncDec_ResolutionClass enclink_get_resolution_class(UInt32 width,
                                                    UInt32 height);
static
Int enclink_get_resolution_class_info(EncDec_ResolutionClass resClass,
                                      UInt32 * pWidth, UInt32 * pHeight);
static
Int enclink_add_chinfo_to_resclass(EncDec_ResolutionClass resClass,
                                   UInt32 chID,
                                   encLinkResClassChannelInfo * resClassChInfo);
static
Int enclink_compare_resclass_resolution(const void *resInfoA,
                                        const void *resInfoB);
static
Void enclink_merge_resclass_chinfo_entry(struct resInfo_s *entryTo,
                                         struct resInfo_s *entryFrom);
static
Int enclink_merge_resclass_chinfo(encLinkResClassChannelInfo * resClassChInfo,
                                  UInt32 targetResClassCount);
static
Int enclink_populate_outbuf_pool_size_info(EncLink_CreateParams * createArgs,
                                           System_LinkQueInfo * inQueInfo,
                                           EncLink_OutObj * outQueInfo);
static Int32 EncLink_codecCreateReqObj(EncLink_Obj * pObj);
static Int32 EncLink_codecCreateOutObj(EncLink_Obj * pObj);
static Int32 EncLink_codecCreateChObj(EncLink_Obj * pObj, UInt32 chId);
static Int32 EncLink_codecCreateEncObj(EncLink_Obj * pObj, UInt32 chId);
static Void EncLink_codecProcessTskFxn(UArg arg1, UArg arg2);
static Int32 EncLink_codecCreateProcessTsk(EncLink_Obj * pObj, UInt32 tskId);
static Int32 EncLink_codecDeleteProcessTsk(EncLink_Obj * pObj, UInt32 tskId);
static Int32 EncLink_codecQueueFramesToChQue(EncLink_Obj * pObj);
static Int32 EncLink_codecSubmitData(EncLink_Obj * pObj);
static Int32 EncLink_codecGetProcessedData(EncLink_Obj * pObj);
static Int32 EncLink_codecDynamicResolutionChange(EncLink_Obj * pObj,
                                                  EncLink_ReqObj * pReqObj,
                                                  UInt32 chId);
static Int32 EncLink_codecCreateReqObjDummy(EncLink_Obj * pObj);
static Int32 EncLink_codecDeleteReqObjDummy(EncLink_Obj * pObj);
static Int32 EncLink_codecSwitchCodecAlg(EncLink_Obj * pObj, UInt32 chId);


/**
 *******************************************************************************
 *
 * \brief Function to get the proper resolution class for the given resolution
 *
 * \param   width      [IN] frame width
 * \param   height     [IN] frame height
 *
 * \return  resClass (EncDec_ResolutionClass)
 *
 *******************************************************************************
*/
static EncDec_ResolutionClass enclink_get_resolution_class(UInt32 width,
                                                           UInt32 height)
{
    EncDec_ResolutionClass resClass = UTILS_ENCDEC_RESOLUTION_CLASS_16MP;

    UTILS_assert((width <= UTILS_ENCDEC_RESOLUTION_CLASS_16MP_WIDTH)
                 && (height <= UTILS_ENCDEC_RESOLUTION_CLASS_16MP_HEIGHT));

    if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_9MP_WIDTH) ||
        (height > UTILS_ENCDEC_RESOLUTION_CLASS_9MP_HEIGHT))
    {
        resClass = UTILS_ENCDEC_RESOLUTION_CLASS_16MP;
    }
    else
    {
        if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_5MP_WIDTH) ||
            (height > UTILS_ENCDEC_RESOLUTION_CLASS_5MP_HEIGHT))
        {
            resClass = UTILS_ENCDEC_RESOLUTION_CLASS_9MP;
        }
        else
        {
            if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_4MP_WIDTH) ||
                (height > UTILS_ENCDEC_RESOLUTION_CLASS_4MP_HEIGHT))
            {
                resClass = UTILS_ENCDEC_RESOLUTION_CLASS_5MP;
            }
            else
            {
                if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_1080P_WIDTH) ||
                    (height > UTILS_ENCDEC_RESOLUTION_CLASS_1080P_HEIGHT))
                {
                    resClass = UTILS_ENCDEC_RESOLUTION_CLASS_4MP;
                }
                else
                {
                    if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_720P_WIDTH) ||
                        (height > UTILS_ENCDEC_RESOLUTION_CLASS_720P_HEIGHT))
                    {
                        resClass = UTILS_ENCDEC_RESOLUTION_CLASS_1080P;
                    }
                    else
                    {
                        if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_D1_WIDTH) ||
                            (height > UTILS_ENCDEC_RESOLUTION_CLASS_D1_HEIGHT))
                        {
                            resClass = UTILS_ENCDEC_RESOLUTION_CLASS_720P;
                        }
                        else
                        {
                            if ((width > UTILS_ENCDEC_RESOLUTION_CLASS_CIF_WIDTH) ||
                                (height > UTILS_ENCDEC_RESOLUTION_CLASS_CIF_HEIGHT))
                            {
                                resClass = UTILS_ENCDEC_RESOLUTION_CLASS_D1;
                            }
                            else
                            {
                                resClass = UTILS_ENCDEC_RESOLUTION_CLASS_CIF;
                            }
                        }
                    }
                }
            }
        }
    }
    return resClass;
}

/**
 *******************************************************************************
 *
 * \brief This function populates the resolution class info,
 *        such as width, height etc.
 *
 * \param   resClass   [IN]   resolution class
 * \param   width      [OUT]  frame width
 * \param   height     [OUT]  frame height
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int enclink_get_resolution_class_info(EncDec_ResolutionClass resClass,
                                             UInt32 * pWidth, UInt32 * pHeight)
{
    Int status = ENC_LINK_S_SUCCESS;

    switch (resClass)
    {
        case UTILS_ENCDEC_RESOLUTION_CLASS_16MP:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_16MP_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_16MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_9MP:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_9MP_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_9MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_5MP:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_5MP_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_5MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_4MP:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_4MP_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_4MP_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_1080P:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_1080P_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_1080P_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_720P:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_720P_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_720P_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_D1:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_D1_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_D1_HEIGHT;
            break;
        case UTILS_ENCDEC_RESOLUTION_CLASS_CIF:
            *pWidth = UTILS_ENCDEC_RESOLUTION_CLASS_CIF_WIDTH;
            *pHeight = UTILS_ENCDEC_RESOLUTION_CLASS_CIF_HEIGHT;
            break;
        default:
            *pWidth = *pHeight = 0;
            status = UTILS_ENCDEC_E_INT_UNKNOWNRESOLUTIONCLASS;
            Vps_printf(" ENCODE: ERROR: Unknown resoltuion class"
                       " [resClass=%d, status=%d] !!!\n",
                         resClass, status);
            break;
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function populates the number of resolution class and channel ID
 *
 * \param   resClass        [IN]   resolution class
 * \param   chID            [OUT]  chID
 * \param   resClassChInfo  [OUT]  resolution class Info
 *
 * \return  UTILS_ENCDEC_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int enclink_add_chinfo_to_resclass(EncDec_ResolutionClass resClass,
                                          UInt32 chID,
                                   encLinkResClassChannelInfo * resClassChInfo)
{
    Int i;
    Int status = UTILS_ENCDEC_S_SUCCESS;

    UTILS_assert(resClassChInfo->numActiveResClass <=
                 UTILS_ENCDEC_RESOLUTION_CLASS_COUNT);
    for (i = 0; i < resClassChInfo->numActiveResClass; i++)
    {
        if (resClassChInfo->resInfo[i].resClass == resClass)
        {
            UInt32 curChIdx = resClassChInfo->resInfo[i].numChInResClass;

            UTILS_assert(curChIdx < ENC_LINK_MAX_CH);
            resClassChInfo->resInfo[i].chIdx[curChIdx] = chID;
            resClassChInfo->resInfo[i].numChInResClass++;
            break;
        }
    }
    if (i == resClassChInfo->numActiveResClass)
    {
        Int resClassIndex = resClassChInfo->numActiveResClass;

        /* Need to add a entry for this resolution class */
        UTILS_assert(resClassChInfo->numActiveResClass <
                     UTILS_ENCDEC_RESOLUTION_CLASS_COUNT);
        resClassChInfo->resInfo[resClassIndex].resClass = resClass;
        status =
            enclink_get_resolution_class_info(resClass,
                                              &(resClassChInfo->
                                                resInfo[resClassIndex].width),
                                              &(resClassChInfo->
                                                resInfo[resClassIndex].height));
        UTILS_assert((status == ENC_LINK_S_SUCCESS));
        resClassChInfo->resInfo[resClassIndex].numChInResClass = 0;
        resClassChInfo->resInfo[resClassIndex].chIdx[0] = chID;
        resClassChInfo->resInfo[resClassIndex].numChInResClass++;
        resClassChInfo->numActiveResClass++;
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function compare and return diff size of two resolutions
 *
 * \param   resInfoA  [IN]  First resolution
 * \param   resInfoA  [IN]  Second resolution
 *
 * \return  the diff value
 *
 *******************************************************************************
*/
static Int enclink_compare_resclass_resolution(const void *resInfoA,
                                               const void *resInfoB)
{
    const struct resInfo_s *resA = resInfoA;
    const struct resInfo_s *resB = resInfoB;

    return ((resA->width * resA->height) - (resB->width * resB->height));
}

/**
 *******************************************************************************
 *
 * \brief This function merges two resolution class channel info entries
 *
 * \param   entryTo      [IN] First channel info entry
 * \param   entryFrom    [IN] Second channel info entry
 *
 * \return  None
 *
 *******************************************************************************
*/
static Void enclink_merge_resclass_chinfo_entry(struct resInfo_s *entryTo,
                                                struct resInfo_s *entryFrom)
{
    Int i;

    for (i = 0; i < entryFrom->numChInResClass; i++)
    {
        UInt32 curChIdx = entryTo->numChInResClass;

        UTILS_assert(entryTo->numChInResClass < ENC_LINK_MAX_CH);
        entryTo->chIdx[curChIdx] = entryFrom->chIdx[i];
        entryTo->numChInResClass++;
    }
    entryTo->resClass = entryFrom->resClass;
    entryTo->width = entryFrom->width;
    entryTo->height = entryFrom->height;
}

/**
 *******************************************************************************
 *
 * \brief This function merges two resolution class channel infos
 *
 * \param   resClassChInfo      [IN] resolution class channel info
 * \param   targetResClassCount [IN] target resolution class count
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int enclink_merge_resclass_chinfo(encLinkResClassChannelInfo * resClassChInfo,
                                         UInt32 targetResClassCount)
{
    Bool sortDone = FALSE;

    UTILS_assert(targetResClassCount > 0);
    while (resClassChInfo->numActiveResClass > targetResClassCount)
    {
        Uint32 resolutionToMergeIdx, resolutionFromMergeIdx;

        if (FALSE == sortDone)
        {
            qsort(resClassChInfo->resInfo, resClassChInfo->numActiveResClass,
                  sizeof(struct resInfo_s),
                  enclink_compare_resclass_resolution);
            sortDone = TRUE;
        }
        UTILS_assert(resClassChInfo->numActiveResClass >= 2);
        resolutionToMergeIdx = resClassChInfo->numActiveResClass - 2;
        resolutionFromMergeIdx = resClassChInfo->numActiveResClass - 1;
        UTILS_assert((resClassChInfo->resInfo[resolutionToMergeIdx].width <=
                      resClassChInfo->resInfo[resolutionFromMergeIdx].width)
                     &&
                     (resClassChInfo->resInfo[resolutionToMergeIdx].height <=
                      resClassChInfo->resInfo[resolutionFromMergeIdx].height));
        enclink_merge_resclass_chinfo_entry(&resClassChInfo->
                                            resInfo[resolutionToMergeIdx],
                                            &resClassChInfo->
                                            resInfo[resolutionFromMergeIdx]);
        resClassChInfo->numActiveResClass--;
    }
    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function populates the output pools size details
 *
 * \param   createArgs [IN] EncLink create parameters
 * \param   inQueInfo  [IN] EncLink input queue info
 * \param   outQueInfo [IN] EncLink output queue info
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int enclink_populate_outbuf_pool_size_info(EncLink_CreateParams * createArgs,
                                                  System_LinkQueInfo * inQueInfo,
                                                  EncLink_OutObj * outQueInfo)
{
    Int i, j;
    Int status = ENC_LINK_S_SUCCESS;
    Int mvFlag = 0;
    Int mvWidth = 0;
    Int mvHeight = 0;
    EncDec_ResolutionClass resClass;
    static encLinkResClassChannelInfo resClassChInfo;

     /** <  resClassChInfo is made static to avoid blowing up the stack
      **    as this structure is large. This requires that all access
      **    to this data structure be executed in critical section
      */
    UInt key;
    UInt32 totalNumOutBufs = 0;

    key = Hwi_disable();
    resClassChInfo.numActiveResClass = 0;
    for (i = 0; i < inQueInfo->numCh; i++)
    {
        resClass = enclink_get_resolution_class(inQueInfo->chInfo[i].width,
                                                inQueInfo->chInfo[i].height);
        enclink_add_chinfo_to_resclass(resClass, i, &resClassChInfo);
    }
    if (resClassChInfo.numActiveResClass > UTILS_BUF_MAX_ALLOC_POOLS)
    {
        enclink_merge_resclass_chinfo(&resClassChInfo,
                                      UTILS_BUF_MAX_ALLOC_POOLS);
    }
    outQueInfo->numAllocPools = resClassChInfo.numActiveResClass;
    UTILS_assert(outQueInfo->numAllocPools <= UTILS_BUF_MAX_ALLOC_POOLS);

    for (i = 0; i < outQueInfo->numAllocPools; i++)
    {
        Int32 maxBitRate = 0;
        Int32 maxFrameRate = 0;
        mvFlag = 0;

        outQueInfo->outNumBufs[i] = 0;
        UTILS_assert(i < UTILS_ENCDEC_RESOLUTION_CLASS_COUNT);
        for (j = 0; j < resClassChInfo.resInfo[i].numChInResClass; j++)
        {
            UInt32 chId;
            Int32 chBitRate;
            Int32 chFrameRate;
            EncLink_ChCreateParams *chCreateParams;

            UTILS_assert(resClassChInfo.resInfo[i].chIdx[j] < ENC_LINK_MAX_CH);
            outQueInfo->ch2poolMap[resClassChInfo.resInfo[i].chIdx[j]] = i;
            chId = resClassChInfo.resInfo[i].chIdx[j];
            chCreateParams = &createArgs->chCreateParams[chId];
            if(chCreateParams->enableAnalyticinfo == 1)
            {
                /* Here Assuming now that all channels will be of
                   same scanFormat type */
                 mvFlag = 1;
                 mvWidth = inQueInfo->chInfo[chId].width;
                 mvHeight = inQueInfo->chInfo[chId].height;
            }

            chBitRate = chCreateParams->defaultDynamicParams.targetBitRate;
            if (chBitRate > maxBitRate)
            {
                maxBitRate = chBitRate;
            }
            chFrameRate = chCreateParams->defaultDynamicParams.inputFrameRate;
            if (chFrameRate > maxFrameRate)
            {
                maxFrameRate = chFrameRate;
            }

            UTILS_assert(i < ENC_LINK_MAX_BUF_ALLOC_POOLS);
            outQueInfo->outNumBufs[i] += createArgs->numBufPerCh[i];
        }
        outQueInfo->buf_size[i] =
            UTILS_ENCDEC_GET_BITBUF_SIZE(resClassChInfo.resInfo[i].width,
                                         resClassChInfo.resInfo[i].height,
                                         maxBitRate,
                                         maxFrameRate);
        if(mvFlag)
        {
            outQueInfo->buf_size[i]
                += ENC_LINK_GET_MVBUF_SIZE((UTILS_ENCDEC_GET_PADDED_WIDTH(mvWidth)),
                                           (UTILS_ENCDEC_GET_PADDED_HEIGHT(mvHeight)));
            mvFlag = 0;
        }

        /* align size to minimum required frame buffer alignment */
        outQueInfo->buf_size[i] = VpsUtils_align(outQueInfo->buf_size[i],
                                     IVACODEC_VDMA_BUFFER_ALIGNMENT);
        totalNumOutBufs += outQueInfo->outNumBufs[i];
    }
    UTILS_assert(totalNumOutBufs <= ENC_LINK_MAX_OUT_FRAMES);
    Hwi_restore(key);
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function create the Enclink request Object Queue
 *
 * \param   pObj      [IN] EncLink_Obj EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecCreateReqObj(EncLink_Obj * pObj)
{
    Int32 status;
    UInt32 reqId;

    memset(pObj->reqObj, 0, sizeof(pObj->reqObj));

    status = Utils_queCreate(&pObj->reqQue,
                             ENC_LINK_MAX_REQ,
                             pObj->reqQueMem, UTILS_QUE_FLAG_BLOCK_QUE_GET);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pObj->isReqPend = FALSE;

    for (reqId = 0; reqId < ENC_LINK_MAX_REQ; reqId++)
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
 * \brief This function creates/populates the EncLink utput object
 *
 * \param   pObj      [IN] EncLink_Obj EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecCreateOutObj(EncLink_Obj * pObj)
{
    EncLink_OutObj *pOutObj;
    Int32 status;
    UInt32 chId, bufIdx, outId;
    System_LinkChInfo *pOutChInfo;
    Int i;
    System_BitstreamBuffer *bitstreamBuf;
    System_Buffer *pBuffer;
    Utils_EncDecLinkPvtInfo *pFrameInfo;
    void *pBaseAddr;

    enclink_populate_outbuf_pool_size_info(&pObj->createArgs, &pObj->inQueInfo,
                                           &pObj->outObj);

    pOutObj = &pObj->outObj;
    status = Utils_bufCreateExt(&pOutObj->bufOutQue, TRUE, FALSE,
                                pObj->outObj.numAllocPools);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_queCreate(&pObj->processDoneQue,
                             ENC_LINK_MAX_OUT_FRAMES,
                             pObj->processDoneQueMem,
                             (UTILS_QUE_FLAG_BLOCK_QUE_GET |
                              UTILS_QUE_FLAG_BLOCK_QUE_PUT));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (i = 0; i < pOutObj->numAllocPools; i++)
    {
        for (bufIdx = 0; bufIdx < pOutObj->outNumBufs[i]; bufIdx++)
        {
            pBaseAddr = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                   pOutObj->buf_size[i],
                                   IVACODEC_VDMA_BUFFER_ALIGNMENT);
            UTILS_assert(pBaseAddr != NULL);

            UTILS_assert((bufIdx) < ENC_LINK_MAX_OUT_FRAMES);

            pBuffer = &pOutObj->outBufs[bufIdx];
            bitstreamBuf = &pOutObj->bitstreamBuf[bufIdx];
            pFrameInfo = &pOutObj->linkPvtInfo[bufIdx];
            memset(pBuffer, 0, sizeof(*pBuffer));
            memset(bitstreamBuf, 0, sizeof(*bitstreamBuf));
            memset(pFrameInfo, 0, sizeof(*pFrameInfo));

            bitstreamBuf->bufAddr = (void *)(char*)pBaseAddr;
            bitstreamBuf->bufSize = pOutObj->buf_size[i];
            bitstreamBuf->fillLength= 0;
            bitstreamBuf->flags = System_Bitstream_Buffer_Flag_Set_Is_Keyframe
                                            (bitstreamBuf->flags, 0);

            pBuffer->bufType = SYSTEM_BUFFER_TYPE_BITSTREAM;
            pBuffer->chNum = 0;
            pBuffer->payloadSize = sizeof(System_BitstreamBuffer);
            pBuffer->payload = bitstreamBuf;
            pBuffer->pEncDecLinkPrivate = pFrameInfo;

            pFrameInfo->allocPoolID = i;
            status =
                Utils_bufPutEmptyBufferExt(&pOutObj->bufOutQue,
                                           &pOutObj->outBufs[bufIdx]);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }
    pObj->info.numQue = ENC_LINK_MAX_OUT_QUE;
    for (outId = 0u; outId < ENC_LINK_MAX_OUT_QUE; outId++)
    {
        pObj->info.queInfo[outId].numCh = pObj->inQueInfo.numCh;
    }

    for (chId = 0u; chId < pObj->inQueInfo.numCh; chId++)
    {
        for (outId = 0u; outId < ENC_LINK_MAX_OUT_QUE; outId++)
        {
            pOutChInfo = &pObj->info.queInfo[outId].chInfo[chId];

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pOutChInfo->flags,
                                    SYSTEM_BUFFER_TYPE_BITSTREAM);


            switch (pObj->createArgs.chCreateParams[chId].format)
            {
                case SYSTEM_IVIDEO_MJPEG:
                pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Bitstream_Format(pOutChInfo->flags,
                                    SYSTEM_BITSTREAM_CODING_TYPE_MJPEG);
                    break;
                case SYSTEM_IVIDEO_H264BP:
                case SYSTEM_IVIDEO_H264MP:
                case SYSTEM_IVIDEO_H264HP:
                pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Bitstream_Format(pOutChInfo->flags,
                                    SYSTEM_BITSTREAM_CODING_TYPE_H264);
                    break;
                default:
                    UTILS_assert(0);
                    break;
            }

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pOutChInfo->flags,
                                    SYSTEM_SF_PROGRESSIVE);

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(pOutChInfo->flags,
                                    SYSTEM_MT_NONTILEDMEM);

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(pOutChInfo->flags,0);

            pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pOutChInfo->flags,
                                     SYSTEM_DF_YUV420SP_UV);

            pOutChInfo->width = pObj->inQueInfo.chInfo[chId].width;
            pOutChInfo->height = pObj->inQueInfo.chInfo[chId].height;
        }
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function creates the EncLink channel specific object
 *
 * \param   pObj      [IN] EncLink_Obj EncLink Object
 * \param   chId      [IN] channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecCreateChObj(EncLink_Obj * pObj, UInt32 chId)
{
    EncLink_ChObj *pChObj;
    Int32 status;

    pChObj = &pObj->chObj[chId];

    status = Utils_queCreate(&pChObj->inQue, ENC_LINK_MAX_REQ,
                             pChObj->inFrameMem, UTILS_QUE_FLAG_BLOCK_QUE_GET);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pChObj->synchToBottomField = FALSE;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the codec create time parameters
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1450)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1453)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1455)
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_004)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1452)
 *
 * \param   pObj      [IN] EncLink_Obj EncLink Object
 * \param   chId      [IN] channel ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 enclink_codec_set_ch_alg_create_params(EncLink_Obj * pObj,
                                                    UInt32 chId)
{
    EncLink_ChObj *pChObj;
    System_LinkChInfo *pInChInfo;

    EncLink_ChCreateParams  *pChCreatePrm;
    EncLink_ChDynamicParams *pChDynPrm;

    EncLink_AlgCreateParams     *pChAlgCreatePrm;

    pChObj = &pObj->chObj[chId];
    pInChInfo = &pObj->inQueInfo.chInfo[chId];

    pChCreatePrm    = &pObj->createArgs.chCreateParams[chId];
    pChDynPrm       = &pChCreatePrm->defaultDynamicParams;

    pChAlgCreatePrm = &pChObj->algObj.algCreateParams;

    pChAlgCreatePrm->format     = (System_IVideoFormat) pChCreatePrm->format;
    pChAlgCreatePrm->dataLayout = (IVIDEO_VideoLayout) pChCreatePrm->dataLayout;
    pChAlgCreatePrm->singleBuf  = pChCreatePrm->fieldMergeEncodeEnable;
    pChAlgCreatePrm->maxWidth   = pInChInfo->width;
    pChAlgCreatePrm->maxHeight  = pInChInfo->height;
    pChAlgCreatePrm->maxInterFrameInterval = pChDynPrm->interFrameInterval;

    pChAlgCreatePrm->inputContentType = Utils_encdecMapSYS2XDMContentType(
          System_Link_Ch_Info_Get_Flag_Scan_Format(pInChInfo->flags));

    pChAlgCreatePrm->inputChromaFormat  = Utils_encdecMapSYS2XDMChromaFormat(
          System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags));

    if (pChAlgCreatePrm->format != SYSTEM_IVIDEO_MJPEG)
    {
        UTILS_assert(pChAlgCreatePrm->inputChromaFormat  == XDM_YUV_420SP);
    }

    pChAlgCreatePrm->profile = pChCreatePrm->profile;

    Utils_encdecGetCodecLevel(pChAlgCreatePrm->format,
                              pChAlgCreatePrm->maxWidth,
                              pChAlgCreatePrm->maxHeight,
                              ENC_LINK_DEFAULT_ALGPARAMS_REFFRAMERATEX1000,
                              pChDynPrm->targetBitRate,
                              &(pChAlgCreatePrm->level),
                              TRUE);

    pChAlgCreatePrm->enableAnalyticinfo = pChCreatePrm->enableAnalyticinfo;

    if(pChAlgCreatePrm->enableAnalyticinfo == 1)
    {
        pChAlgCreatePrm->mvDataSize =
                ENC_LINK_GET_MVBUF_SIZE(
                 (UTILS_ENCDEC_GET_PADDED_WIDTH(pInChInfo->width)),
                 (UTILS_ENCDEC_GET_PADDED_HEIGHT(pInChInfo->height)));
    }

    pChAlgCreatePrm->maxBitRate        = pChCreatePrm->maxBitRate;
    pChAlgCreatePrm->encodingPreset    = pChCreatePrm->encodingPreset;
    pChAlgCreatePrm->rateControlPreset = pChCreatePrm->rateControlPreset;
    pChAlgCreatePrm->enableHighSpeed   = pChCreatePrm->enableHighSpeed;
    pChAlgCreatePrm->numTemporalLayer  = pChCreatePrm->numTemporalLayer;
    pChAlgCreatePrm->enableSVCExtensionFlag = pChCreatePrm->enableSVCExtensionFlag;
    pChAlgCreatePrm->enableWaterMarking = pChCreatePrm->enableWaterMarking;

    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the codec run time (dynamic) parameters
 *
 * \param   pObj      [IN] EncLink_Obj EncLink Object
 * \param   chId      [IN] channel ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 enclink_codec_set_ch_alg_default_dynamic_params(EncLink_Obj * pObj,
                                                             UInt32 chId)
{
    EncLink_ChObj *pChObj;
    System_LinkChInfo *pInChInfo;

    EncLink_ChCreateParams  *pChCreatePrm;
    EncLink_ChDynamicParams *pChDynPrm;

    EncLink_AlgCreateParams     *pChAlgCreatePrm;
    EncLink_AlgDynamicParams    *pChAlgDynPrm;

    pChObj = &pObj->chObj[chId];
    pInChInfo       = &pObj->inQueInfo.chInfo[chId];

    pChCreatePrm    = &pObj->createArgs.chCreateParams[chId];
    pChDynPrm       = &pChCreatePrm->defaultDynamicParams;

    pChAlgCreatePrm = &pChObj->algObj.algCreateParams;
    pChAlgDynPrm    = &pChObj->algObj.algDynamicParams;

    pChAlgDynPrm->startX        = ENC_LINK_DEFAULT_ALGPARAMS_STARTX;
    pChAlgDynPrm->startY        = ENC_LINK_DEFAULT_ALGPARAMS_STARTY;
    pChAlgDynPrm->inputWidth    = pInChInfo->width;
    pChAlgDynPrm->inputHeight   = pInChInfo->height;
    pChAlgDynPrm->inputPitch    = pInChInfo->pitch[0];

    pChAlgDynPrm->targetBitRate         = pChDynPrm->targetBitRate;
    pChAlgDynPrm->rcAlg                 = pChDynPrm->rcAlg;

    if(pChAlgCreatePrm->format == SYSTEM_IVIDEO_MJPEG)
    {
        pChAlgDynPrm->targetFrameRate =
                      ENC_LINK_DEFAULT_ALGPARAMS_TARGETFRAMERATEX1000;
        pChAlgDynPrm->refFrameRate    =
                      ENC_LINK_DEFAULT_ALGPARAMS_REFFRAMERATEX1000;
    }else
    if((pChAlgCreatePrm->format == SYSTEM_IVIDEO_H264BP) ||
       (pChAlgCreatePrm->format == SYSTEM_IVIDEO_H264MP) ||
       (pChAlgCreatePrm->format == SYSTEM_IVIDEO_H264HP))
    {
        pChAlgDynPrm->targetFrameRate =
                      ENC_LINK_DEFAULT_ALGPARAMS_TARGETFRAMERATEX1000;
        pChAlgDynPrm->refFrameRate    =
                      ENC_LINK_DEFAULT_ALGPARAMS_REFFRAMERATEX1000;
    }
    else
    {
        UTILS_assert(FALSE); //Format is not supported
    }

    pChAlgDynPrm->intraFrameInterval    = pChDynPrm->intraFrameInterval;
    pChAlgDynPrm->interFrameInterval    = pChDynPrm->interFrameInterval;
    pChAlgDynPrm->qpMinI                = pChDynPrm->qpMin;
    pChAlgDynPrm->qpMaxI                = pChDynPrm->qpMax;
    pChAlgDynPrm->qpInitI               = pChDynPrm->qpInit;
    pChAlgDynPrm->qpMinP                = pChDynPrm->qpMin;
    pChAlgDynPrm->qpMaxP                = pChDynPrm->qpMax;
    pChAlgDynPrm->qpInitP               = pChDynPrm->qpInit;
    pChAlgDynPrm->forceFrame            = FALSE;
    pChAlgDynPrm->vbrDuration           = pChDynPrm->vbrDuration;
    pChAlgDynPrm->vbrSensitivity        = pChDynPrm->vbrSensitivity;
    pChAlgDynPrm->forceFrameStatus      = FALSE;
    pChAlgDynPrm->mvAccuracy            = pChDynPrm->mvAccuracy;

    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function set the static/dynamic codec parameters
 *        and create the codec/Alg handle
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1446)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1448)
 *
 * \param   pObj      [IN] EncLink_Obj EncLink Object
 * \param   chId      [IN] channel ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecCreateEncObj(EncLink_Obj * pObj, UInt32 chId)
{
    Int retVal;
    EncLink_ChObj *pChObj;
    Int scratchGroupID;

    pChObj = &pObj->chObj[chId];
    pChObj->algObj.setConfigBitMask = 0;
    pChObj->switchCodec.switchCodecFlag = FALSE;
    pChObj->nextFid = SYSTEM_FID_TOP;
    pChObj->expectedFid = SYSTEM_FID_TOP;

    pChObj->inputFrameRate =
       pObj->createArgs.chCreateParams[chId].defaultDynamicParams.inputFrameRate;

    scratchGroupID = -1;

    enclink_codec_set_ch_alg_create_params(pObj, chId);
    enclink_codec_set_ch_alg_default_dynamic_params(pObj, chId);


    switch (pChObj->algObj.algCreateParams.format)
    {
        case SYSTEM_IVIDEO_MJPEG:
            retVal = EncLinkJPEG_algCreate(&pChObj->algObj.u.jpegAlgIfObj,
                                           &pChObj->algObj.algCreateParams,
                                           &pChObj->algObj.algDynamicParams,
                                           pObj->linkId, chId, scratchGroupID);
            break;
        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
            retVal = EncLinkH264_algCreate(&pChObj->algObj.u.h264AlgIfObj,
                                           &pChObj->algObj.algCreateParams,
                                           &pChObj->algObj.algDynamicParams,
                                           pObj->linkId, chId, scratchGroupID);
            break;

        default:
            retVal = ENC_LINK_E_UNSUPPORTEDCODEC;
            break;

    }
    UTILS_assert(retVal == ENC_LINK_S_SUCCESS);

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief This function has the logic to handle various dummy request objects
 *        1. Switch Codec types
 *        2.
 *
 * \param   pObj    [IN] EncLink_Obj EncLink Object
 * \param   pReqObj [IN] request object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecHandleDummyReqObj(EncLink_Obj  *pObj,
                                            EncLink_ReqObj *pReqObj)
{
    Int32 status = ENC_LINK_S_SUCCESS;

    switch (pReqObj->type)
    {
        case ENC_LINK_REQ_OBJECT_TYPE_DUMMY_CODEC_SWITCH:
        {
            EncLink_ChObj *pChObj;
            System_LinkChInfo *pInChInfo;

            UTILS_assert(pReqObj->OutBuf != NULL);
            UTILS_assert(pReqObj->OutBuf->chNum < pObj->inQueInfo.numCh);
            pChObj = &pObj->chObj[pReqObj->OutBuf->chNum];
            UTILS_assert (pChObj->switchCodec.switchCodecFlag == TRUE);
            pInChInfo = &pObj->inQueInfo.chInfo[pReqObj->OutBuf->chNum];
            if (pChObj->switchCodec.algCreatePrm.fieldPicEncode)
            {
                if (SYSTEM_SF_PROGRESSIVE ==
                 System_Link_Ch_Info_Get_Flag_Scan_Format(pInChInfo->flags))
                {
                pInChInfo->height /= 2;
                }
                pInChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pInChInfo->flags,
                                                         SYSTEM_SF_INTERLACED);
            }
            else
            {
                if (SYSTEM_SF_INTERLACED ==
                 System_Link_Ch_Info_Get_Flag_Scan_Format(pInChInfo->flags))
                {
                    pInChInfo->height *= 2;
                }
                pInChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pInChInfo->flags,
                                                         SYSTEM_SF_PROGRESSIVE);
            }
            /* Switch codec Alg type if switchCodecFlag is enabled */
            EncLink_codecSwitchCodecAlg(pObj, pReqObj->OutBuf->chNum);
            pChObj->switchCodec.switchCodecFlag = FALSE;
            #ifdef SYSTEM_DEBUG_ENC
            Vps_printf(" ENCODE: CH%d: %s\n", pReqObj->OutBuf->chNum,
                        "Codec Switch: Completed");
            #endif
            break;
        }
        default:
            /* Unsupported reqObjType.*/
            UTILS_assert(0);
            break;
    }
    pReqObj->type = ENC_LINK_REQ_OBJECT_TYPE_REGULAR;
    UTILS_assert(UTILS_ARRAYISVALIDENTRY(pReqObj,pObj->encDummyReqObj.reqObjDummy));
    status = Utils_quePut(&pObj->encDummyReqObj.reqQueDummy, pReqObj,
                          BSP_OSAL_NO_WAIT);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implement the IVA process task
 *        - Call codec specific process function
 *
 * \param   arg1 [IN] pObj EncLink Object
 * \param   arg2 [IN] tskId IVA task ID
 *
 * \return  None
 *
 *******************************************************************************
*/
static Void EncLink_codecProcessTskFxn(UArg arg1, UArg arg2)
{
    Int32 status, chId;
    EncLink_Obj *pObj;
    EncLink_ReqObj *pReqObj;
    EncLink_ChObj *pChObj;
    UInt32 tskId;

    pObj = (EncLink_Obj *) arg1;
    tskId = 0; /* assume tskId is 0 */

    while (pObj->state != UTILS_ENCDEC_STATE_STOP)
    {
        status = ENC_LINK_S_SUCCESS;

        pReqObj = NULL;

        status = Utils_queGet(&pObj->encProcessTsk[tskId].processQue,
                              (Ptr *) & pReqObj, 1, BSP_OSAL_WAIT_FOREVER);

        if (!UTILS_ISERROR(status))
        {

          if (ENC_LINK_REQ_OBJECT_TYPE_REGULAR != pReqObj->type)
          {
              EncLink_codecHandleDummyReqObj(pObj,pReqObj);
              continue;
          }
          UTILS_assert(pReqObj->type == ENC_LINK_REQ_OBJECT_TYPE_REGULAR);
        }

        if (pReqObj != NULL)
        {
            chId = pReqObj->OutBuf->chNum;
            pChObj = &pObj->chObj[chId];

            EncLink_codecDynamicResolutionChange (pObj, pReqObj, chId);

            switch (pChObj->algObj.algCreateParams.format)
            {
                case SYSTEM_IVIDEO_MJPEG:
                    status = EncLinkJPEG_algSetConfig(&pChObj->algObj);
                    status = EncLinkJPEG_algGetConfig(&pChObj->algObj);
                    UTILS_assert(ENC_LINK_REQ_OBJECT_TYPE_REGULAR == pReqObj->type);

                    status = Enclink_jpegEncodeFrame(pChObj, pReqObj);
                    if (UTILS_ISERROR(status))
                    {
                        Vps_printf(" ENCODE: ERROR in "
                                   "Enclink_JPEGEncodeFrame.Status[%d]", status);
                    }
                    break;

                case SYSTEM_IVIDEO_H264BP:
                case SYSTEM_IVIDEO_H264MP:
                case SYSTEM_IVIDEO_H264HP:
                    UTILS_assert(ENC_LINK_REQ_OBJECT_TYPE_REGULAR == pReqObj->type);

                    status = Enclink_H264EncodeFrame(pChObj, pReqObj);
                    if (UTILS_ISERROR(status))
                    {
                        Vps_printf(" ENCODE: ERROR in "
                                   "Enclink_h264EncodeFrame.Status[%d]", status);
                    }
                    break;

                default:
                    UTILS_assert(FALSE);
            }
        }

        if (pReqObj != NULL)
        {
            /*Return the processed ReqObjects to the Enc Link via the ProcessDone
              Queue*/
            pReqObj->OutBuf->frameId =
                     pReqObj->InFrameList.buffers[0]->frameId;

            status = Utils_quePut(&pObj->processDoneQue, pReqObj,
                                  BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

        status = System_sendLinkCmd(pObj->linkId,
                                    ENC_LINK_CMD_GET_PROCESSED_DATA, NULL);

        if (UTILS_ISERROR(status))
        {
            #ifdef SYSTEM_DEBUG_ENC
            Vps_printf(" ENCODE: [%s:%d]:"
                       "System_sendLinkCmd ENC_LINK_CMD_GET_PROCESSED_DATA failed"
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
#pragma DATA_ALIGN(gEncProcessTskStack, 32)
#pragma DATA_SECTION(gEncProcessTskStack, ".bss:taskStackSection:enc_process")
UInt8 gEncProcessTskStack[NUM_HDVICP_RESOURCES][ENC_LINK_PROCESS_TSK_STACK_SIZE];

/**
 *******************************************************************************
 *
 * \brief This function create the IVA process task
 *
 * \param   pObj  [IN] EncLink Object
 * \param   tskId [IN] IVA task ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecCreateProcessTsk(EncLink_Obj * pObj, UInt32 tskId)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    Error_Block ebObj;
    Error_Block *eb = &ebObj;

    Error_init(eb);

    snprintf(pObj->encProcessTsk[tskId].name,
             (sizeof(pObj->encProcessTsk[tskId].name) - 1),
             "ENC_PROCESS_TSK_%d ", tskId);
    pObj->encProcessTsk[tskId].
          name[(sizeof(pObj->encProcessTsk[tskId].name) - 1)] = 0;

    pObj->encProcessTsk[tskId].tsk =
              BspOsal_taskCreate(
                (BspOsal_TaskFuncPtr)EncLink_codecProcessTskFxn,
                "EncLink_codecProcessTsk",
                ENC_LINK_TSK_PRI+1,
                &gEncProcessTskStack[tskId][0],
                ENC_LINK_PROCESS_TSK_STACK_SIZE,
                pObj,
                UTILS_TSK_AFFINITY_CORE0
                );
    UTILS_assert(pObj->encProcessTsk[tskId].tsk!=NULL);
    Utils_prfLoadRegister(pObj->encProcessTsk[tskId].tsk,
                          pObj->encProcessTsk[tskId].name);
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the IVA process task
 *
 * \param   pObj  [IN] EncLink Object
 * \param   tskId [IN] IVA task ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecDeleteProcessTsk(EncLink_Obj * pObj, UInt32 tskId)
{
    Int32 status = ENC_LINK_S_SUCCESS;

    Utils_queUnBlock(&pObj->encProcessTsk[tskId].processQue);
    Utils_queUnBlock(&pObj->processDoneQue);
    Utils_prfLoadUnRegister(pObj->encProcessTsk[tskId].tsk);
    BspOsal_taskDelete(&pObj->encProcessTsk[tskId].tsk);
    pObj->encProcessTsk[tskId].tsk = NULL;
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function initilize all the codec stats parameters
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  None
 *
 *******************************************************************************
*/
static void EncLink_codecCreateInitStats(EncLink_Obj * pObj)
{
    Int32 chId;
    EncLink_ChObj *pChObj;

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        pChObj->processReqestCount = 0;
        pChObj->getProcessDoneCount = 0;
        pChObj->disableChn = FALSE;
        pChObj->curFrameNum = 0;
        pChObj->inputFrameRate = 30;
        pChObj->algObj.setConfigBitMask = 0;
        pChObj->algObj.getConfigFlag = FALSE;
        pChObj->forceAvoidSkipFrame = FALSE;
        pChObj->forceDumpFrame = FALSE;
        pChObj->frameStatus.firstTime = TRUE;
        pChObj->frameStatus.inCnt = 0;
        pChObj->frameStatus.outCnt = 0;
        pChObj->frameStatus.multipleCnt = 0;
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief This is the EncLink top level create function
 *
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1447)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1449)
 *
 * \param   pObj  [IN] EncLink Object
 * \param   pPrm  [IN] EncLink_CreateParams EncLink create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecCreate(EncLink_Obj * pObj, EncLink_CreateParams * pPrm)
{
    Int32 status;
    Int32 chId, tskId, i;
    EncLink_ChObj *pChObj;

    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: Create in progress ... !!!\n");
    #endif

    #ifdef SYSTEM_DEBUG_MEMALLOC
    Vps_printf(" ENCODE: Before ENC Create:\n");
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
    UTILS_assert(pObj->inQueInfo.numCh <= ENC_LINK_MAX_CH);

    for (i=0; i<ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        UTILS_assert(i < UTILS_BUF_MAX_ALLOC_POOLS);
        if(pObj->createArgs.numBufPerCh[i] == 0)
            pObj->createArgs.numBufPerCh[i] = ENC_LINK_MAX_OUT_FRAMES_PER_CH;

        if(pObj->createArgs.numBufPerCh[i] > ENC_LINK_MAX_OUT_FRAMES_PER_CH)
        {
            Vps_printf(" ENCODE: WARNING: "
                " User is asking for %d buffers per CH. But max allowed is %d.\n"
                " Over riding user requested with max allowed \n",
                pObj->createArgs.numBufPerCh[i], ENC_LINK_MAX_OUT_FRAMES_PER_CH
                );

            pObj->createArgs.numBufPerCh[i] = ENC_LINK_MAX_OUT_FRAMES_PER_CH;
        }
    }

    EncLink_codecCreateInitStats(pObj);
    EncLink_codecCreateOutObj(pObj);
    EncLink_codecCreateReqObj(pObj);
    EncLink_codecCreateReqObjDummy(pObj);
    pObj->state = UTILS_ENCDEC_STATE_START;

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        if(pObj->createArgs.chCreateParams[chId].overrideInputScanFormat)
        {
            Vps_printf(" ENCODE: CH%d Updaing PicEncode Mode %d\n",
                       chId, pObj->createArgs.chCreateParams[chId].fieldPicEncode);

            if (pObj->createArgs.chCreateParams[chId].fieldPicEncode)
            {
                pObj->inQueInfo.chInfo[chId].flags =
                        System_Link_Ch_Info_Set_Flag_Scan_Format(
                            pObj->inQueInfo.chInfo[chId].flags,
                            SYSTEM_SF_INTERLACED);
            }
            else
            {
                pObj->inQueInfo.chInfo[chId].flags =
                    System_Link_Ch_Info_Set_Flag_Scan_Format(
                            pObj->inQueInfo.chInfo[chId].flags,
                            SYSTEM_SF_PROGRESSIVE);
            }
        }
        #ifdef SYSTEM_DEBUG_ENC
        Vps_printf(" ENCODE: Creating CH%d of %d x %d, "
                   " pitch = (%d, %d) [%d] [%d], bitrate = %d Kbps ... \n",
                chId,
                pObj->inQueInfo.chInfo[chId].width,
                pObj->inQueInfo.chInfo[chId].height,
                pObj->inQueInfo.chInfo[chId].pitch[0],
                pObj->inQueInfo.chInfo[chId].pitch[1],
                System_Link_Ch_Info_Get_Flag_Scan_Format(
                                       pObj->inQueInfo.chInfo[chId].flags),
                System_Link_Ch_Info_Get_Flag_Mem_Type(
                                       pObj->inQueInfo.chInfo[chId].flags),
                pObj->createArgs.chCreateParams[chId].defaultDynamicParams.targetBitRate/1000
            );
        #endif

        pChObj->nextFid = SYSTEM_FID_TOP;
        pChObj->processReqestCount = 0;
        pChObj->getProcessDoneCount = 0;
        EncLink_codecCreateChObj(pObj, chId);
        EncLink_codecCreateEncObj(pObj, chId);
    }

    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: All CH Create ... DONE !!!\n" );
    #endif

    for (tskId = 0; tskId < NUM_HDVICP_RESOURCES; tskId++)
    {
        status = Utils_queCreate(&pObj->encProcessTsk[tskId].processQue,
                                 UTILS_ARRAYSIZE(pObj->encProcessTsk[tskId].processQueMem),
                                 pObj->encProcessTsk[tskId].processQueMem,
                                 (UTILS_QUE_FLAG_BLOCK_QUE_GET |
                                  UTILS_QUE_FLAG_BLOCK_QUE_PUT));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        EncLink_codecCreateProcessTsk(pObj, tskId);
    }

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, "ENCODE");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = FALSE;

    EncLink_resetStatistics(pObj);
    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("ENCLINK",
                       pObj->memUsed,
                       UTILS_ARRAYSIZE(pObj->memUsed));

    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: Create ... DONE !!!\n" );
    #endif

    #ifdef SYSTEM_DEBUG_MEMALLOC
    Vps_printf(" ENCODE: After ENC Create:\n");
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
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecQueueFramesToChQue(EncLink_Obj * pObj)
{
    UInt32 frameId, freeFrameNum;
    System_Buffer *pFrame;
    System_VideoFrameBuffer *vidFrm;
    System_LinkInQueParams *pInQueParams;
    System_BufferList frameList;
    EncLink_ChObj *pChObj;
    Int32 status;
    Bool skipFrame;
    UInt32 fid;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pInQueParams = &pObj->createArgs.inQueParams;

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &frameList);

    if (frameList.numBuf)
    {
        freeFrameNum = 0;
        linkStatsInfo->linkStats.getFullBufCount += frameList.numBuf;

        for (frameId = 0; frameId < frameList.numBuf; frameId++)
        {
            pFrame = frameList.buffers[frameId];
            vidFrm = pFrame->payload;

            pChObj = &pObj->chObj[pFrame->chNum];

            if (SYSTEM_SF_PROGRESSIVE ==
               System_Link_Ch_Info_Get_Flag_Scan_Format(
                      pObj->inQueInfo.chInfo[pFrame->chNum].flags))
            {
                pChObj->nextFid = 0;
            }
            skipFrame = FALSE;
            if(pChObj->forceDumpFrame == FALSE)
            {
                skipFrame = EncLink_doSkipFrame(pChObj, pFrame->chNum);

                if (pChObj->forceAvoidSkipFrame == TRUE)
                    skipFrame = FALSE;
            }
            else
            {
                pChObj->forceDumpFrame = FALSE;
            }

            pChObj->curFrameNum++;
            fid = System_Video_Frame_Get_Flag_Fid(vidFrm->flags);
            if ((pChObj->synchToBottomField) && (fid != SYSTEM_FID_BOTTOM))
            {
                skipFrame = TRUE;
            }
            if ((pChObj->synchToBottomField) && (fid == SYSTEM_FID_BOTTOM))
            {
                skipFrame = FALSE;
                pChObj->nextFid = SYSTEM_FID_TOP;
                pChObj->synchToBottomField = FALSE;
                #ifdef SYSTEM_DEBUG_ENC
                Vps_printf(" ENCODE: CH%d: %s\n", pFrame->chNum,
                            "INTERLACED SWITCH synch to bottom field done");
                #endif
            }
            /* frame skipped due to user setting */
            //if(skipFrame || pChObj->disableChn)
                //pChObj->inFrameUserSkipCount++;

            /* frame skipped due to framework */
            //if(pChObj->nextFid != fid && fid != SYSTEM_FID_FRAME)
                //pChObj->inFrameRejectCount++;

            if (((pChObj->nextFid == fid) ||
                (fid == SYSTEM_FID_FRAME)) &&
                (pChObj->disableChn != TRUE) && (skipFrame == FALSE))
            {
                // frame is of the expected FID use it, else drop it
                status = Utils_quePut(&pChObj->inQue, pFrame, BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                pChObj->nextFid ^= 1;    // toggle to next required FID
                linkStatsInfo->linkStats.chStats[pFrame->chNum].inBufRecvCount++;
            }
            else
            {
                // frame is not of expected FID, so release frame
                frameList.buffers[freeFrameNum] = pFrame;
                freeFrameNum++;
                if (pChObj->nextFid == fid)
                {
                    pChObj->nextFid ^= 1;  // toggle to next
                }
                linkStatsInfo->linkStats.chStats[pFrame->chNum].inBufDropCount++;
            }
        }

        if (freeFrameNum)
        {
            frameList.numBuf = freeFrameNum;
            linkStatsInfo->linkStats.putEmptyBufCount += frameList.numBuf;
            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                        pInQueParams->prevLinkQueId, &frameList);
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
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecSubmitData(EncLink_Obj * pObj)
{
    EncLink_ReqObj *pReqObj;
    EncLink_ChObj *pChObj;
    UInt32 chId;
    System_Buffer *pInFrame;
    System_Buffer *pOutBuf;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 freeFrameNum, tskId, i;
    System_BufferList frameList;
    System_LinkInQueParams *pInQueParams;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    freeFrameNum = 0;
    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
      pChObj = &pObj->chObj[chId];
      status =
          Utils_queGet(&pObj->reqQue, (Ptr *) & pReqObj, 1,
                       BSP_OSAL_NO_WAIT);
      if (UTILS_ISERROR(status)) {
          break;
      }

      tskId = 0;
      pReqObj->type = ENC_LINK_REQ_OBJECT_TYPE_REGULAR;
      if ((pChObj->algObj.algCreateParams.singleBuf) &&
          (pChObj->algObj.algCreateParams.dataLayout ==
                                          VENC_FIELD_SEPARATED))
      {
          pReqObj->InFrameList.numBuf = 2;
      }
      else
      {
          pReqObj->InFrameList.numBuf = 1;
      }
      if ((status == SYSTEM_LINK_STATUS_SOK) &&
          (Utils_queGetQueuedCount(&pChObj->inQue) >=
           pReqObj->InFrameList.numBuf) &&
          (!Utils_queIsFull(&pObj->encProcessTsk[tskId].processQue)))
      {
          pOutBuf = NULL;
          UTILS_assert(chId < ENC_LINK_MAX_CH);
          status = Utils_bufGetEmptyBufferExt(&pObj->outObj.bufOutQue,
                                              &pOutBuf,
                                              pObj->outObj.ch2poolMap[chId],
                                              BSP_OSAL_NO_WAIT);
          if ((status == SYSTEM_LINK_STATUS_SOK) && (pOutBuf))
          {
              pInFrame = NULL;
              linkStatsInfo->linkStats.chStats[chId].outBufCount[0]++;
              for (i=0; i<pReqObj->InFrameList.numBuf; i++)
              {
                  status = Utils_queGet(&pChObj->inQue, (Ptr *) & pInFrame, 1,
                                        BSP_OSAL_NO_WAIT);
                  UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                  UTILS_assert(pInFrame!=NULL);
                  pReqObj->InFrameList.buffers[i] = pInFrame;
              }

              UTILS_assert(pInFrame!=NULL);

              pOutBuf->chNum = pInFrame->chNum;
              pOutBuf->srcTimestamp = pInFrame->srcTimestamp;
              pOutBuf->frameId = pInFrame->frameId;
              pOutBuf->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
              pReqObj->OutBuf = pOutBuf;
              pChObj->forceAvoidSkipFrame = FALSE;

              linkStatsInfo->linkStats.chStats[pInFrame->chNum].inBufProcessCount++;
              status =
                  Utils_quePut(&pObj->encProcessTsk[tskId].processQue,
                               pReqObj, BSP_OSAL_NO_WAIT);
              UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
              pChObj->processReqestCount++;
          }
          else
          {
              /* Free the input frame if output buffer is not available */
              for (i=0; i<pReqObj->InFrameList.numBuf; i++)
              {
                  status = Utils_queGet(&pChObj->inQue, (Ptr *) & pInFrame, 1,
                                        BSP_OSAL_NO_WAIT);
                  UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                  UTILS_assert(pInFrame!=NULL);
                  UTILS_assert(freeFrameNum < UTILS_ARRAYSIZE(frameList.buffers));
                  frameList.buffers[freeFrameNum] = pInFrame;
                  freeFrameNum++;
                  pChObj->forceAvoidSkipFrame = TRUE;
              }

              status = Utils_quePut(&pObj->reqQue, pReqObj, BSP_OSAL_NO_WAIT);
              UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
              status = SYSTEM_LINK_STATUS_EFAIL;
              continue;
          }
      }
      else
      {
          /* Free the input frame if processQue is full */
          if (Utils_queGetQueuedCount(&pChObj->inQue) >=
              pReqObj->InFrameList.numBuf)
          {
              for (i=0; i<pReqObj->InFrameList.numBuf; i++)
              {
                  status = Utils_queGet(&pChObj->inQue, (Ptr *) & pInFrame, 1,
                                        BSP_OSAL_NO_WAIT);
                  UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                  UTILS_assert(pInFrame!=NULL);
                  UTILS_assert(freeFrameNum < UTILS_ARRAYSIZE(frameList.buffers));
                  frameList.buffers[freeFrameNum] = pInFrame;
                  freeFrameNum++;
                  pChObj->forceAvoidSkipFrame = TRUE;
              }
          }

          status = Utils_quePut(&pObj->reqQue, pReqObj, BSP_OSAL_NO_WAIT);
          UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
          status = SYSTEM_LINK_STATUS_EFAIL;
      }
    }

    if (freeFrameNum)
    {
        /* Free input frames */
        linkStatsInfo->linkStats.putEmptyBufCount += freeFrameNum;
        pInQueParams = &pObj->createArgs.inQueParams;
        frameList.numBuf = freeFrameNum;
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &frameList);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This is the Top level process data call initiate by NEW_DATA
 *        command from previous link
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecProcessData(EncLink_Obj * pObj)
{
    Int32 status;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    if(pObj->isFirstFrameRecv==FALSE)
    {
        pObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
                &pObj->linkStatsInfo->linkStats,
                pObj->inQueInfo.numCh,
                ENC_LINK_MAX_OUT_QUE);

        Utils_resetLatency(&pObj->linkStatsInfo->linkLatency);
        Utils_resetLatency(&pObj->linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.newDataCmdCount++;

    EncLink_codecQueueFramesToChQue(pObj);

    do
    {
        status = EncLink_codecSubmitData(pObj);
    } while (status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function has the logic to
 *        - Recollect the request object after decode
 *        - Free-up the input frames
 *        - Send-out the filled output frames to next link
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecGetProcessedData(EncLink_Obj * pObj)
{
    System_BufferList inFrameList;
    UInt32 chId, i, j;
    System_BufferList outBitBufList;
    System_LinkInQueParams *pInQueParams;
    EncLink_ChObj *pChObj;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    EncLink_ReqObj *pReqObj;
    Bool sendNotify = FALSE;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    outBitBufList.numBuf = 0;
    inFrameList.numBuf = 0;

    while (!Utils_queIsEmpty(&pObj->processDoneQue)
           &&
           (inFrameList.numBuf < (SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST - 1))
           &&
           (outBitBufList.numBuf < (SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST - 1)))
    {
        status = Utils_queGet(&pObj->processDoneQue, (Ptr *) & pReqObj, 1,
                              BSP_OSAL_NO_WAIT);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
        chId = pReqObj->OutBuf->chNum;
        pChObj = &pObj->chObj[chId];

        pChObj->getProcessDoneCount++;
        for (i = 0; i < pReqObj->InFrameList.numBuf; i++)
        {
            if (chId != pReqObj->InFrameList.buffers[i]->chNum)
            {
                Vps_printf(" ENCODE: Error !!! ChId %d,  Req chNum - %d.....\n",
                             chId, pReqObj->InFrameList.buffers[i]->chNum);
            }
            UTILS_assert(chId == pReqObj->InFrameList.buffers[i]->chNum);

            inFrameList.buffers[inFrameList.numBuf] =
                                           pReqObj->InFrameList.buffers[i];
            inFrameList.numBuf++;
        }

        outBitBufList.buffers[outBitBufList.numBuf] = pReqObj->OutBuf;
        outBitBufList.numBuf++;

        status = Utils_quePut(&pObj->reqQue, pReqObj, BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    if (outBitBufList.numBuf)
    {
        for (j=0; j<outBitBufList.numBuf; j++)
        {
            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                outBitBufList.buffers[j]->linkLocalTimestamp);
            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                outBitBufList.buffers[j]->srcTimestamp);
        }

        status = Utils_bufPutFullExt(&pObj->outObj.bufOutQue,
                                      &outBitBufList);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        sendNotify = TRUE;
    }

    if (inFrameList.numBuf)
    {
        /* Free input frames */
        linkStatsInfo->linkStats.putEmptyBufCount += inFrameList.numBuf;
        pInQueParams = &pObj->createArgs.inQueParams;
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId,
                                    &inFrameList);
    }


    if (sendNotify)
    {
        /* Send-out the output bitbuffer */
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA, NULL);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Top level function to process the frames after decode call complete
 *        - Recollect the request object after decode
 *        - Free-up the input frames
 *        - Send-out the filled output frames to next link
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecGetProcessedDataMsgHandler(EncLink_Obj * pObj)
{
    Int32 status;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.releaseDataCmdCount++;

    status = EncLink_codecGetProcessedData(pObj);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief Function to free-up all the input bitstream buffers which are
 *        present in the output Full Queue of the previous Link
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecFreeInQueuedBufs(EncLink_Obj * pObj)
{
    System_LinkInQueParams *pInQueParams;
    System_BufferList frameList;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    pInQueParams = &pObj->createArgs.inQueParams;
    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId, &frameList);
    if (frameList.numBuf)
    {
        pObj->linkStatsInfo->linkStats.getFullBufCount += frameList.numBuf;
        pObj->linkStatsInfo->linkStats.putEmptyBufCount += frameList.numBuf;
        /* Free input frames */
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &frameList);
    }
    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief Function to stop the EncLink and free-up all the input bitstream
 *        buffers which are present inside the EncLink pending for process
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecStop(EncLink_Obj * pObj)
{
    Int32 rtnValue = SYSTEM_LINK_STATUS_SOK;
    UInt32 tskId;

    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: Link ID %d: %s\n", pObj->linkId,
               " Stop in progress !!!");
    #endif
    for (tskId = 0; tskId < NUM_HDVICP_RESOURCES; tskId++)
    {
        Utils_queUnBlock(&pObj->encProcessTsk[tskId].processQue);
    }
#if 0
    while (Utils_queGetQueuedCount(&pObj->reqQue) != ENC_LINK_MAX_REQ)
    {
        Utils_tskWaitCmd(&pObj->tsk, NULL, ENC_LINK_CMD_GET_PROCESSED_DATA);
        EncLink_codecGetProcessedDataMsgHandler(pObj);
    }
#endif
    EncLink_codecFreeInQueuedBufs(pObj);
    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: Link ID %d: %s\n", pObj->linkId,
               " Stop done !!!");
    #endif

    return (rtnValue);
}

/**
 *******************************************************************************
 *
 * \brief Function to get the input frame rate of a specific channel
 *
 * \param   pChObj  [IN] EncLink channel object
 *
 * \return  input frame rate
 *
 *******************************************************************************
*/
Int32 EncLink_getFrameRate(EncLink_ChObj *pChObj)
{
    return pChObj->inputFrameRate;
}

/**
 *******************************************************************************
 *
 * \brief This Function delete the EncLink instance
 *        Also delete the IVA process task and process queues
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecDelete(EncLink_Obj * pObj)
{
    UInt32 outId, chId, tskId, frameId;
    EncLink_ChObj *pChObj;
    EncLink_OutObj *pOutObj;
    Int i;
    System_BitstreamBuffer *bitstreamBuf;
    Int32 status;

    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: Link ID %d: %s\n", pObj->linkId,
               " Delete in progress !!!");
    #endif
    pObj->state = UTILS_ENCDEC_STATE_STOP;

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status==0);

    for (tskId = 0; tskId < NUM_HDVICP_RESOURCES; tskId++)
    {
        EncLink_codecDeleteProcessTsk(pObj, tskId);
        Utils_queDelete(&pObj->encProcessTsk[tskId].processQue);
    }

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        switch (pChObj->algObj.algCreateParams.format)
        {
            case SYSTEM_IVIDEO_MJPEG:
                EncLinkJPEG_algDelete(&pChObj->algObj.u.jpegAlgIfObj);
                break;

            case SYSTEM_IVIDEO_H264BP:
            case SYSTEM_IVIDEO_H264MP:
            case SYSTEM_IVIDEO_H264HP:
                EncLinkH264_algDelete(&pChObj->algObj.u.h264AlgIfObj);
                break;

            default:
                UTILS_assert(FALSE);
        }

        Utils_queDelete(&pChObj->inQue);

        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf(" ENCODE: CH%d: "
                    "FrameNum : %8d, "
                    "FPS: %8d (Required FPS: %8d)\n",
                    chId,
                    pChObj->curFrameNum,
                    EncLink_getFrameRate(pChObj)
                 );
        #endif
    }

    Utils_queDelete(&pObj->processDoneQue);

    for (outId = 0; outId < ENC_LINK_MAX_OUT_QUE; outId++)
    {
        pOutObj = &pObj->outObj;

        Utils_bufDeleteExt(&pOutObj->bufOutQue);
        for (i = 0; i < pOutObj->numAllocPools; i++)
        {
            for(frameId = 0 ; frameId < pOutObj->outNumBufs[i]; frameId++)
            {
                bitstreamBuf = pOutObj->outBufs[frameId].payload;
                UTILS_assert(bitstreamBuf->bufSize == pOutObj->buf_size[i]);
                Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                            bitstreamBuf->bufAddr,
                            bitstreamBuf->bufSize);
            }
        }
    }

    Utils_queDelete(&pObj->reqQue);
    EncLink_codecDeleteReqObjDummy(pObj);

    #ifdef SYSTEM_DEBUG_ENC
    Vps_printf(" ENCODE: Link ID %d: %s\n", pObj->linkId,
               " Delete done !!!");
    #endif
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to reset the Statistics
 *
 * \param   pObj  [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_resetStatistics(EncLink_Obj * pObj)
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
 * \brief Function to print the EncLink Statistics
 *
 * \param   pObj            [IN] EncLink Object
 * \param   resetAfterPrint [IN] flag to reset stats after print
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_printStatistics (EncLink_Obj * pObj, Bool resetAfterPrint)
{
    UInt32 chId;
    EncLink_ChObj *pChObj;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "ENCODE", TRUE);

    for (chId = 0; chId < pObj->inQueInfo.numCh; chId++)
    {
        pChObj = &pObj->chObj[chId];

        Vps_printf(" ENCODE: Num process reqest count for chId: %d = %d \n",
                     chId, pChObj->processReqestCount);
        Vps_printf(" ENCODE: Num process complete count for chId: %d = %d \n",
                     chId, pChObj->getProcessDoneCount);
    }

    Utils_printLatency("ENCODE",
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                        TRUE);

    if(resetAfterPrint)
    {
        EncLink_resetStatistics(pObj);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to get the current encoder link dynamic parameters
 *
 * \param   pObj   [IN] EncLink_Obj Object Enc link object
 * \param   params [IN] EncLink_GetDynParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecGetDynParams(EncLink_Obj * pObj,
                                EncLink_GetDynParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    /* EncLink_AlgDynamicParams algDynamicParams;*/
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];

    pChObj->algObj.getConfigFlag = TRUE;

    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic bit rate parameters
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChBitRateParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetBitrate(EncLink_Obj * pObj,
                              EncLink_ChBitRateParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];

    /**Do a bitrate allowed range check**/
    switch (pChObj->algObj.algCreateParams.format)
    {
        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
        case SYSTEM_IVIDEO_MJPEG:
            if((params->targetBitRate < ENC_LINK_MIN_ALGPARAMS_TARGETBITRATE))
            {
                Vps_printf(" ENCODE: Warning! Out of Bounds bitrate param set requested,"
                           " Minimum allowed value is 16*1024, try again");
                status = ENC_LINK_E_INVALIDARG;
                Hwi_restore(key);
                return (status);
            }
            break;

            default:
                UTILS_assert(FALSE);
    }

    pChObj->algObj.algDynamicParams.targetBitRate = params->targetBitRate;
    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_BITRATE);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link channel FPS parameters
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChFpsParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetFps(EncLink_Obj * pObj, EncLink_ChFpsParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];

    pChObj->frameStatus.firstTime = TRUE;

    pChObj->algObj.algDynamicParams.targetFrameRate = params->targetFps;

    if(params->targetBitRate != 0)
    {
        /**Do a bitrate allowed range check**/
        switch (pChObj->algObj.algCreateParams.format)
        {
            case SYSTEM_IVIDEO_H264BP:
            case SYSTEM_IVIDEO_H264MP:
            case SYSTEM_IVIDEO_H264HP:
            case SYSTEM_IVIDEO_MJPEG:
                if((params->targetBitRate < ENC_LINK_MIN_ALGPARAMS_TARGETBITRATE))
                {
                    Vps_printf(" ENCODE: Warning! Out of Bounds bitrate param set requested,"
                               " Minimum allowed value is 16*1024, try again");
                    status = ENC_LINK_E_INVALIDARG;
                    Hwi_restore(key);
                    return (status);
                }
                break;

                default:
                    UTILS_assert(FALSE);
        }

        pChObj->algObj.algDynamicParams.targetBitRate = params->targetBitRate;
        pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_BITRATE);
    }

    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_FPS);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link channel input FPS parameters
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChInputFpsParam object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecInputSetFps(EncLink_Obj * pObj,
                               EncLink_ChInputFpsParam * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];

    pChObj->inputFrameRate = params->inputFps;
    pChObj->frameStatus.firstTime = TRUE;

    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link channel intra frame interval
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChIntraFrIntParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetIntraIRate(EncLink_Obj * pObj,
                                 EncLink_ChIntraFrIntParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->algObj.algDynamicParams.intraFrameInterval = params->intraFrameInterval;
    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_INTRAI);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel force IDR
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChannelInfo (chID)
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetForceIDR(EncLink_Obj * pObj,
                               EncLink_ChannelInfo * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_FORCEI);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel rate control Alg
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChRcAlgParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetrcAlg(EncLink_Obj * pObj, EncLink_ChRcAlgParams* params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->algObj.algDynamicParams.rcAlg = params->rcAlg;

    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_RCALGO);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel I-Frame QP parameters
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChQPParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetqpParamI(EncLink_Obj * pObj,
                               EncLink_ChQPParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    /**Do a qp allowed range check**/
    switch (pChObj->algObj.algCreateParams.format)
    {
        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
            if(/*(params->qpMin < ENC_LINK_MIN_ALGPARAMS_H264_QPMIN) ||*/
               (params->qpMin > ENC_LINK_MAX_ALGPARAMS_H264_QPMIN) ||
               /*(params->qpMax < ENC_LINK_MIN_ALGPARAMS_H264_QPMAX) ||*/
               (params->qpMax > ENC_LINK_MAX_ALGPARAMS_H264_QPMAX) ||
               (params->qpInit < ENC_LINK_MIN_ALGPARAMS_H264_QPI) ||
               (params->qpInit > ENC_LINK_MAX_ALGPARAMS_H264_QPI)
              )
            {
                Vps_printf(" ENCODE: Warning! Out of Bounds QP param "
                           " set requested, try again");
                status = ENC_LINK_E_INVALIDARG;
                Hwi_restore(key);
                return (status);
            }
            break;

        case SYSTEM_IVIDEO_MJPEG:
            if((params->qpInit < ENC_LINK_MIN_ALGPARAMS_MJPEG_QF) ||
               (params->qpInit > ENC_LINK_MAX_ALGPARAMS_MJPEG_QF)
              )
            {
                Vps_printf(" ENCODE: Warning! Out of Bounds Quality factor "
                           " param set requested, try again");
                status = ENC_LINK_E_INVALIDARG;
                Hwi_restore(key);
                return (status);
            }
            break;

        default:
                UTILS_assert(FALSE);
    }

    pChObj->algObj.algDynamicParams.qpMinI = params->qpMin;
    pChObj->algObj.algDynamicParams.qpMaxI = params->qpMax;
    pChObj->algObj.algDynamicParams.qpInitI = params->qpInit;
    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_QPI);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel P-Frame QP parameters
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChQPParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetqpParamP(EncLink_Obj * pObj,
                               EncLink_ChQPParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    /**Do a qp allowed range check**/
    switch (pChObj->algObj.algCreateParams.format)
    {
        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
            if(/*(params->qpMin < ENC_LINK_MIN_ALGPARAMS_H264_QPMIN) ||*/
               (params->qpMin > ENC_LINK_MAX_ALGPARAMS_H264_QPMIN) ||
               /*(params->qpMax < ENC_LINK_MIN_ALGPARAMS_H264_QPMAX) ||*/
               (params->qpMax > ENC_LINK_MAX_ALGPARAMS_H264_QPMAX) ||
               (params->qpInit < ENC_LINK_MIN_ALGPARAMS_H264_QPP) ||
               (params->qpInit > ENC_LINK_MAX_ALGPARAMS_H264_QPP)
              )
            {
                Vps_printf("Warning! Out of Bounds QP param set requested, try again");
                status = ENC_LINK_E_INVALIDARG;
                Hwi_restore(key);
                return (status);
            }
            break;

        case SYSTEM_IVIDEO_MJPEG:
                Vps_printf(" ENCODE: Warning! this param setting "
                           " not supported for MJPEG");
            break;

        default:
                UTILS_assert(FALSE);
    }
    pChObj->algObj.algDynamicParams.qpMinP = params->qpMin;
    pChObj->algObj.algDynamicParams.qpMaxP = params->qpMax;
    pChObj->algObj.algDynamicParams.qpInitP = params->qpInit;
    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_QPP);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel force
 *        Dup frame parameters, used in the snapshot option
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChannelInfo (chId)
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecForceDumpFrame(EncLink_Obj * pObj,
                                  EncLink_ChannelInfo * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->forceDumpFrame = TRUE;
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel codec switch params
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChSwitchCodecTypeParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSwitchCodec(EncLink_Obj * pObj,
                               EncLink_ChSwitchCodecTypeParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt32 tskId;
    UInt key;

    key = Hwi_disable();
    if (params->chId < pObj->inQueInfo.numCh)
    {
        pChObj = &pObj->chObj[params->chId];
        memcpy(&pChObj->switchCodec, params, sizeof(*params));
        if (pChObj->switchCodec.algCreatePrm.fieldPicEncode)
        {
            pChObj->synchToBottomField = TRUE;
        }
        else
        {
            pChObj->synchToBottomField = FALSE;
        }
    }
    else
    {
        status = ENC_LINK_E_INVALIDARG;
    }
    Hwi_restore(key);

    tskId = 0;
    if (status == ENC_LINK_S_SUCCESS)
    {
        EncLink_ReqObj *pReqObjCodecSwitch;

        status =
        Utils_queGet(&pObj->encDummyReqObj.reqQueDummy,
                     (Ptr *) & pReqObjCodecSwitch, 1,
                     BSP_OSAL_NO_WAIT);
        UTILS_assert(status == 0);

        UTILS_assert(UTILS_ARRAYISVALIDENTRY(
                     pReqObjCodecSwitch,pObj->encDummyReqObj.reqObjDummy));

        pObj->chObj[params->chId].dummyBitBuf.chNum = params->chId;

        pReqObjCodecSwitch->type = ENC_LINK_REQ_OBJECT_TYPE_DUMMY_CODEC_SWITCH;
        pReqObjCodecSwitch->OutBuf = &pObj->chObj[params->chId].dummyBitBuf;
        #ifdef SYSTEM_DEBUG_ENC
        Vps_printf(" ENCODE: CH%d: %s\n", params->chId,
                   " Queueing codec switch dummy reqObj into ReqQ");
        #endif
        status = Utils_quePut(&pObj->encProcessTsk[tskId].processQue,
                              pReqObjCodecSwitch, BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel CVBR duration params
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChCVBRDurationParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetVBRDuration(EncLink_Obj * pObj,
                                  EncLink_ChCVBRDurationParams *params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->algObj.algDynamicParams.vbrDuration = params->vbrDuration;

    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_VBRD);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic Ch CVBR Sensitivity params
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChCVBRSensitivityParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetVBRSensitivity(EncLink_Obj * pObj,
                                     EncLink_ChCVBRSensitivityParams *params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    pChObj->algObj.algDynamicParams.vbrSensitivity = params->vbrSensitivity;

    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_VBRS);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to set the encoder link dynamic channel ROI parameters
 *
 * \param   pObj   [IN] EncLink_Obj Enc link object
 * \param   params [IN] EncLink_ChROIParams object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecSetROIPrms(EncLink_Obj * pObj, EncLink_ChROIParams * params)
{
    Int32 status = ENC_LINK_S_SUCCESS;

    EncLink_ChObj *pChObj;

    UInt key;

    key = Hwi_disable();
    pChObj = &pObj->chObj[params->chId];
    int i = 0;

    if(params->numOfRegion > 4)
    {
        Vps_printf(" ENCODE: Warning!!!"
                   " Maximum only 4 ROIs are allowed, defaulting to 4");
        params->numOfRegion = ENC_LINK_CURRENT_MAX_ROI;
    }

    pChObj->algObj.algDynamicParams.roiParams.roiNumOfRegion = params->numOfRegion;

    for (i = 0; i < params->numOfRegion; i++)
    {
        pChObj->algObj.algDynamicParams.roiParams.roiStartX[i] = params->startX[i];
        pChObj->algObj.algDynamicParams.roiParams.roiStartY[i] = params->startY[i];
        pChObj->algObj.algDynamicParams.roiParams.roiWidth[i] = params->width[i];
        pChObj->algObj.algDynamicParams.roiParams.roiHeight[i] = params->height[i];
        pChObj->algObj.algDynamicParams.roiParams.roiType[i] = params->type[i];
       /*
        *  roiPriority: Valid values include all integers between -8 and 8,
        *  inclusive. A higher value means that more importance will be
        *  given to the ROI compared to other regions. This parameter holds
        *  the mask color information if ROI is of type privacy mask.
        **/

        pChObj->algObj.algDynamicParams.roiParams.roiPriority[i] =
                       params->roiPriority[i];

        /*Checks for out of bounds entered values*/
        if((pChObj->algObj.algDynamicParams.roiParams.roiStartX[i]
            + pChObj->algObj.algDynamicParams.roiParams.roiWidth[i])
            > pObj->inQueInfo.chInfo[params->chId].width)
        {
            pChObj->algObj.algDynamicParams.roiParams.roiWidth[i] =
                pObj->inQueInfo.chInfo[params->chId].width
                - pChObj->algObj.algDynamicParams.roiParams.roiStartX[i];
        }
        if((pChObj->algObj.algDynamicParams.roiParams.roiStartY[i]
            + pChObj->algObj.algDynamicParams.roiParams.roiHeight[i])
            > pObj->inQueInfo.chInfo[params->chId].height)
        {
            pChObj->algObj.algDynamicParams.roiParams.roiHeight[i] =
               pObj->inQueInfo.chInfo[params->chId].height
               - pChObj->algObj.algDynamicParams.roiParams.roiStartY[i];
        }

        if((pChObj->algObj.algDynamicParams.roiParams.roiStartX[i] < 0) ||
           (pChObj->algObj.algDynamicParams.roiParams.roiStartY[i] < 0) ||
           ((pChObj->algObj.algDynamicParams.roiParams.roiStartX[i]
            + pChObj->algObj.algDynamicParams.roiParams.roiWidth[i]) < 0) ||
            ((pChObj->algObj.algDynamicParams.roiParams.roiStartY[i]
            + pChObj->algObj.algDynamicParams.roiParams.roiHeight[i]) < 0))
        {
            Vps_printf(" ENCODE: Warning!!"
                       " Out of Bounds ROI parameters. ROI Privacy mask Disabled");
            pChObj->algObj.algDynamicParams.roiParams.roiNumOfRegion = 0;
        }

        if((pChObj->algObj.algDynamicParams.roiParams.roiStartX[i]
           >= pObj->inQueInfo.chInfo[params->chId].width) ||
           (pChObj->algObj.algDynamicParams.roiParams.roiStartY[i]
           >= pObj->inQueInfo.chInfo[params->chId].height)||
           (pChObj->algObj.algDynamicParams.roiParams.roiWidth[i]
           > pObj->inQueInfo.chInfo[params->chId].width)||
           (pChObj->algObj.algDynamicParams.roiParams.roiHeight[i]
           > pObj->inQueInfo.chInfo[params->chId].height))
        {
            Vps_printf(" ENCODE: Warning!!"
                    " Out of Bounds ROI parameters. ROI Privacy mask Disabled");
            pChObj->algObj.algDynamicParams.roiParams.roiNumOfRegion = 0;
        }
    }

    pChObj->algObj.setConfigBitMask |= (1 << ENC_LINK_SETCONFIG_BITMASK_ROI);
    Hwi_restore(key);

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to Disable a encode Link channel
 *
 * \param   pObj    [IN] EncLink Object
 * \param   params  [IN] EncLink_ChannelInfo channel info (chID)
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecDisableChannel(EncLink_Obj * pObj,
                              EncLink_ChannelInfo* params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
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
 * \brief Function to Enable a encode Link channel
 *
 * \param   pObj    [IN] EncLink Object
 * \param   params  [IN] EncLink_ChannelInfo channel info (chID)
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
Int32 EncLink_codecEnableChannel(EncLink_Obj * pObj,
                              EncLink_ChannelInfo* params)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj *pChObj;
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
 * \brief Function to check and update frame skip logic of a channel
 *
 * \param   pChObj  [IN] EncLink channel specific Object
 * \param   chId    [IN] channel ID
 *
 * \return  skip status (TRUE/FALSE)
 *
 *******************************************************************************
*/
Bool  EncLink_doSkipFrame(EncLink_ChObj *pChObj, Int32 chId)
{
    /* If the target framerate has changed,
       First time case needs to be visited? */
    if(pChObj->frameStatus.firstTime)
    {
        pChObj->frameStatus.outCnt = 0;
        pChObj->frameStatus.inCnt = 0;

        pChObj->frameStatus.multipleCnt = pChObj->inputFrameRate *
            (pChObj->algObj.algDynamicParams.targetFrameRate/1000);

        pChObj->frameStatus.firstTime = FALSE;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf(" ENCODE: Channel:%d inputframerate:%d targetfps:%d",
                     chId, pChObj->inputFrameRate,
                     (pChObj->algObj.algDynamicParams.targetFrameRate/1000));
        #endif
    }

    if (pChObj->frameStatus.inCnt > pChObj->frameStatus.outCnt)
    {
                pChObj->frameStatus.outCnt +=
                    (pChObj->algObj.algDynamicParams.targetFrameRate/1000);
                /* skip this frame, return true */
                return TRUE;
    }

    /* out will also be multiple */
    if (pChObj->frameStatus.inCnt == pChObj->frameStatus.multipleCnt)
    {
        /* reset to avoid overflow */
        pChObj->frameStatus.inCnt = pChObj->frameStatus.outCnt = 0;
    }

    pChObj->frameStatus.inCnt += pChObj->inputFrameRate;
    pChObj->frameStatus.outCnt +=
            (pChObj->algObj.algDynamicParams.targetFrameRate/1000);

    if(pChObj->algObj.algDynamicParams.targetFrameRate == 0)
        return TRUE;

    /* display this frame, hence return false */
    return FALSE;
}

/**
 *******************************************************************************
 *
 * \brief Function to check and apply dynamic resolution change
 *        ASSEMPTION!!!
 *        EncLink_codecDynamicResolutionChnage() Assumes only one input frame
 *        or two fileds (in case of feild merge mode) present in each reqObj
 *
 * \param   pObj    [IN] EncLink Object
 * \param   chId    [IN] channel ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecDynamicResolutionChange(EncLink_Obj * pObj,
                                 EncLink_ReqObj * reqObj, UInt32 chId)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    EncLink_ChObj * pChObj;
    EncLink_AlgDynamicParams *chDynamicParams;
    EncLink_ChannelInfo IdrParams;
    Bool rtParamUpdatePerFrame;
    System_LinkChInfo *pFrameInfo;
    System_VideoFrameBuffer *videoFrame;
    UInt32 flags;

    pChObj = &pObj->chObj[chId];
    rtParamUpdatePerFrame = FALSE;
    UTILS_assert (chId == reqObj->OutBuf->chNum);

    videoFrame = reqObj->InFrameList.buffers[0]->payload;
    UTILS_assert(videoFrame != NULL);
    flags = videoFrame->chInfo.flags;
    pFrameInfo = &videoFrame->chInfo;
    UTILS_assert(pFrameInfo != NULL);

    if ((pFrameInfo != NULL) &&
        (System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update(flags) == TRUE))
    {
        chDynamicParams = &pChObj->algObj.algDynamicParams;
        if (pFrameInfo->height != chDynamicParams->inputHeight)
        {
            chDynamicParams->inputHeight = pFrameInfo->height;
            rtParamUpdatePerFrame = TRUE;
        }
        if (pFrameInfo->width != chDynamicParams->inputWidth)
        {
            chDynamicParams->inputWidth = pFrameInfo->width;
            rtParamUpdatePerFrame = TRUE;
        }
        if (pFrameInfo->pitch[0] != chDynamicParams->inputPitch)
        {
            chDynamicParams->inputPitch = pFrameInfo->pitch[0];
            rtParamUpdatePerFrame = TRUE;
        }

        if (rtParamUpdatePerFrame == TRUE)
        {
            switch (pChObj->algObj.algCreateParams.format)
            {
                case SYSTEM_IVIDEO_MJPEG:
                    status = EncLinkJPEG_algDynamicParamUpdate(
                                         &pChObj->algObj.u.jpegAlgIfObj,
                                         &pChObj->algObj.algCreateParams,
                                         &pChObj->algObj.algDynamicParams);
                    if (UTILS_ISERROR(status))
                    {
                        Vps_printf(" ENCODE: ERROR in "
                        "EncLinkJPEG_algDynamicParamUpdate.Status[%d]", status);
                    }

                    /** Note: The below call to SetForceIDR has been called
                              just to make a control call to the JPEG encoder,
                              so that Dynamic resolution takes effect **/

                    IdrParams.chId = chId;
                    EncLink_codecSetForceIDR(pObj, &IdrParams);
                    break;

                case SYSTEM_IVIDEO_H264BP:
                case SYSTEM_IVIDEO_H264MP:
                case SYSTEM_IVIDEO_H264HP:
                    status = EncLinkH264_algDynamicParamUpdate(
                                         &pChObj->algObj.u.h264AlgIfObj,
                                         &pChObj->algObj.algCreateParams,
                                         &pChObj->algObj.algDynamicParams);
                    if (UTILS_ISERROR(status))
                    {
                        Vps_printf(" ENCODE: ERROR in "
                        "EncLinkH264_algDynamicParamUpdate.Status[%d]", status);
                    }

                    /** Note: The below call to SetForceIDR has been called
                              just to make a control call to the H264 encoder,
                              so that Dynamic resolution takes effect **/

                    IdrParams.chId = chId;
                    EncLink_codecSetForceIDR(pObj, &IdrParams);
                    break;


                default:
                    UTILS_assert(FALSE);
            }
        }
        flags = System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(flags, 0);
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This Function prints EncLink Buffer status
 *
 * \param   pObj [IN] EncLink Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EncLink_printBufferStatus (EncLink_Obj * pObj)
{
    Uint8 str[256];

    sprintf ((char *)str, " ENCODE Out ");
    Utils_bufExtPrintStatus(str, &pObj->outObj.bufOutQue);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This Function create the encode link dummy object
 *
 * \param   pObj [IN] EncLink Object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecCreateReqObjDummy(EncLink_Obj * pObj)
{
    Int32 status;
    UInt32 reqId;
    struct encDummyReqObj_s *dummyReq = &pObj->encDummyReqObj;

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

    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This Function delete the encode link dummy object
 *
 * \param   pObj [IN] EncLink Object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecDeleteReqObjDummy(EncLink_Obj * pObj)
{
    struct encDummyReqObj_s *dummyReq = &pObj->encDummyReqObj;
    Int32 status;

    status = Utils_queDelete(&dummyReq->reqQueDummy);

    UTILS_assert(status == 0);

    return ENC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This Function initiates the codec (Alg) switch functionality
 *
 * \param   pObj [IN] EncLink Object
 * \param   chId [IN] channel ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 EncLink_codecSwitchCodecAlg(EncLink_Obj * pObj, UInt32 chId)
{
    Int32 status;
    EncLink_ChObj *pChObj;

    pChObj = &pObj->chObj[chId];
    switch (pChObj->algObj.algCreateParams.format)
    {
        case SYSTEM_IVIDEO_MJPEG:
            EncLinkJPEG_algDelete(&pChObj->algObj.u.jpegAlgIfObj);
            break;

        case SYSTEM_IVIDEO_H264BP:
        case SYSTEM_IVIDEO_H264MP:
        case SYSTEM_IVIDEO_H264HP:
            EncLinkH264_algDelete(&pChObj->algObj.u.h264AlgIfObj);
            break;

        default:
            UTILS_assert(FALSE);
    }

    memcpy(&pObj->createArgs.chCreateParams[chId],
           &pChObj->switchCodec.algCreatePrm, sizeof(EncLink_ChCreateParams));
    status = EncLink_codecCreateEncObj(pObj, chId);

    if (!UTILS_ISERROR(status))
    {
        status = System_sendLinkCmd(pObj->linkId, ENC_LINK_CMD_LATE_ACK, NULL);
    }

    if (UTILS_ISERROR(status))
    {
        Vps_printf(" ENCODE: [%s:%d]:"
                   "System_sendLinkCmd ENC_LINK_CMD_LATE_ACK failed"
                   "errCode = %d", __FILE__, __LINE__, status);
    }

    return status;
}

/* Nothing beyond this point */


