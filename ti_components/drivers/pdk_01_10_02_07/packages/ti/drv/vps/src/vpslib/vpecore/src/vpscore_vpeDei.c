/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file vpscore_vpeDei.c
 *
 *  \brief VPS VPE path core internal file containing functions related to
 *  DEI module logic.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/src/vpslib/vpecore/src/vpscore_vpePriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  vcoreVpeProgramDesc
 *  \brief Programs the inbound data descriptor depending on the parameters set.
 *  This is used in case of non-mosaic mode of operation.
 */
Int32 vcoreVpeProgramDesc(const Vcore_VpeInstObj *instObj,
                          const Vcore_VpeChObj   *chObj,
                          const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, descOffset;
    void  *descPtr;
    VpsHal_VpdmaInDescParams inDescPrm[VCORE_VPE_NUM_DESC_PER_WINDOW];

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);

    /* Set the commom VPDMA parameters between Y and C descriptors */
    for (cnt = 0U; cnt < instObj->numDescPerWindow; cnt++)
    {
        /*
         *  Caution:
         *  Next two statements relies on the fact that VCORE_VPE_FLD0LUMA_IDX
         *  and VCORE_VPE_FLD0CHROMA_IDX are next to each other.
         */
        inDescPrm[cnt].channel =
            instObj->vpdmaCh[VCORE_VPE_FLD0LUMA_IDX + cnt];
        inDescPrm[cnt].nextChannel =
            instObj->vpdmaCh[VCORE_VPE_FLD0LUMA_IDX + cnt];
        inDescPrm[cnt].transWidth = chObj->corePrms.fmt.width;
        inDescPrm[cnt].frameWidth = chObj->corePrms.frameWidth;
        inDescPrm[cnt].startX     = chObj->corePrms.startX;
        inDescPrm[cnt].notify     = (UInt32) FALSE;
        inDescPrm[cnt].priority   = VPS_CFG_M2M_VPDMA_PRIORITY_RD;
        inDescPrm[cnt].memType    =
            (VpsHal_VpdmaMemoryType) chObj->corePrms.memType;
        inDescPrm[cnt].is1DData = (UInt32) FALSE;

        /* In deinterlacing mode or in progressive/interlaced bypass mode,
         * either field or progressive frame is queued in to the driver.
         * Hence program the entire field/frame. */
        inDescPrm[cnt].transHeight = chObj->corePrms.fmt.height;
        inDescPrm[cnt].frameHeight = chObj->corePrms.frameHeight;
        inDescPrm[cnt].startY      = chObj->corePrms.startY;
        inDescPrm[cnt].lineSkip    = VPSHAL_VPDMA_LS_1;

        inDescPrm[cnt].lineStride =
            chObj->corePrms.fmt.pitch[chObj->bufIndex[cnt]];
    }

    /* Set the other VPDMA parameters */
    if (FVID2_DF_YUV422I_YUYV == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_YC422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_YC422;
    }
    else if (FVID2_DF_YUV422I_UYVY == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_CY422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_CY422;
    }
    else if (FVID2_DF_YUV422I_YVYU == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_YCb422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_YCb422;
    }
    else if (FVID2_DF_YUV422I_VYUY == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_CbY422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_CbY422;
    }
    else if (FVID2_DF_YUV422SP_VU == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_Cb422;
    }
    else if (FVID2_DF_YUV422SP_UV == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_C422;
    }
    else if (FVID2_DF_YUV420SP_VU == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y420;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_Cb420;

        /* Chroma height is half of Luma for YUV420 */
        inDescPrm[VCORE_VPE_CBCR_IDX].transHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].frameHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].startY      /= 2U;
    }
    else if (FVID2_DF_YUV420SP_UV == chObj->corePrms.fmt.dataFormat)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y420;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_C420;

        /* Chroma height is half of Luma for YUV420 */
        inDescPrm[VCORE_VPE_CBCR_IDX].transHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].frameHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].startY      /= 2U;
    }
    else /* Invalid Data Format */
    {
        retVal = FVID2_EINVALID_PARAMS;
    }

    if (BSP_SOK == retVal)
    {
        for (cnt = 0U; cnt < instObj->numDescPerWindow; cnt++)
        {
            /* Configure data descriptor */
            /*
             *  Caution:
             *  Next statement relies on the fact that VCORE_VPE_FLD0LUMA_IDX
             *  and VCORE_VPE_FLD0CHROMA_IDX are next to each other.
             */
            descOffset = chObj->descOffset[VCORE_VPE_FLD0LUMA_IDX + cnt];
            descPtr    = descMem->inDataDesc[descOffset];
            GT_assert(VpsVpeCoreTrace, NULL != descPtr);
            retVal = VpsHal_vpdmaCreateInBoundDataDesc(
                descPtr,
                &inDescPrm[cnt]);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "VPDMA Descriptor Creation Failed!!\r\n");
                break;
            }
        }
    }

    return retVal;
}

/**
 *  vcoreVpeProgramPrevFldDesc
 *  \brief Programs the previous field inbound data descriptor depending on the
 *  parameters set.
 */
Int32 vcoreVpeProgramPrevFldDesc(const Vcore_VpeInstObj *instObj,
                                 const Vcore_VpeChObj   *chObj,
                                 const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, fldCnt;
    UInt32 tempIdx;
    UInt32 descOffset;
    UInt32 prevFldDataFmt;
    void  *descPtr;
    VpsHal_VpdmaInDescParams  inDescPrm[VCORE_VPE_NUM_DESC_PER_FIELD];
    VpsHal_VpdmaInDescParams *tempDescPrm;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);

    if ((VPSHAL_VPDMA_CHANNEL_INVALID ==
         instObj->vpdmaCh[VCORE_VPE_WRLUMA_IDX]) ||
        (VPSHAL_VPDMA_CHANNEL_INVALID ==
         instObj->vpdmaCh[VCORE_VPE_WRCHROMA_IDX]))
    {
        /* No write channel available, use the data format of input */
        prevFldDataFmt = chObj->corePrms.fmt.dataFormat;
    }
    else
    {
        /* Use YUV422SP if write descriptor is present */
        prevFldDataFmt = FVID2_DF_YUV422SP_UV;
    }

    /* Set the common VPDMA parameter for previous field inputs -
     * Assume initially compressor/decompressor is disabled for all fields. */
    for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_FIELD; cnt++)
    {
        inDescPrm[cnt].transWidth = chObj->corePrms.fmt.width;
        inDescPrm[cnt].frameWidth = chObj->corePrms.fmt.width;
        inDescPrm[cnt].startX     = 0U;
        inDescPrm[cnt].startY     = 0U;
        inDescPrm[cnt].notify     = (UInt32) FALSE;
        inDescPrm[cnt].priority   = VPS_CFG_M2M_VPDMA_PRIORITY_RD;

        /* No write channel available, use the input tiler mode */
        if ((VPSHAL_VPDMA_CHANNEL_INVALID ==
             instObj->vpdmaCh[VCORE_VPE_WRLUMA_IDX]) ||
            (VPSHAL_VPDMA_CHANNEL_INVALID ==
             instObj->vpdmaCh[VCORE_VPE_WRCHROMA_IDX]))
        {
            inDescPrm[cnt].memType =
                (VpsHal_VpdmaMemoryType) chObj->corePrms.memType;
        }
        else
        {
            inDescPrm[cnt].memType = VPSHAL_VPDMA_MT_NONTILEDMEM;
        }

        inDescPrm[cnt].is1DData = (UInt32) FALSE;
        inDescPrm[cnt].lineSkip = VPSHAL_VPDMA_LS_1;

        /* In the Progressive mode, since entire frame is queued,
         * size of field is half of frame size */
        if (FVID2_SF_PROGRESSIVE == chObj->corePrms.fmt.scanFormat)
        {
            inDescPrm[cnt].transHeight = chObj->corePrms.fmt.height / 2U;
            inDescPrm[cnt].frameHeight = chObj->corePrms.fmt.height / 2U;
        }
        else /* DEI is de-interlacing, so format contains field size */
        {
            inDescPrm[cnt].transHeight = chObj->corePrms.fmt.height;
            inDescPrm[cnt].frameHeight = chObj->corePrms.fmt.height;
        }

        if ((VPSHAL_VPDMA_CHANNEL_INVALID ==
             instObj->vpdmaCh[VCORE_VPE_WRLUMA_IDX]) ||
            (VPSHAL_VPDMA_CHANNEL_INVALID ==
             instObj->vpdmaCh[VCORE_VPE_WRCHROMA_IDX]))
        {
            /* No write channel available, use the line stride of input */
            inDescPrm[cnt].lineStride =
                chObj->corePrms.fmt.pitch[chObj->bufIndex[cnt]];
        }
        else
        {
            /* Since the buffer is in YUV 422 semi-planar format, line stride
             * is same as line size for both Y and C buffer */
            inDescPrm[cnt].lineStride = (UInt16) VpsUtils_align(
                chObj->corePrms.fmt.width,
                (UInt32) VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
        }
    }

    /* Set the other VPDMA parameters */
    if (FVID2_DF_YUV422I_YUYV == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_YC422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_YC422;
    }
    else if (FVID2_DF_YUV422I_UYVY == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_CY422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_CY422;
    }
    else if (FVID2_DF_YUV422I_YVYU == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_YCb422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_YCb422;
    }
    else if (FVID2_DF_YUV422I_VYUY == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_CbY422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_CbY422;
    }
    else if (FVID2_DF_YUV422SP_VU == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_Cb422;
    }
    else if (FVID2_DF_YUV422SP_UV == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y422;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_C422;
    }
    else if (FVID2_DF_YUV420SP_VU == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y420;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_Cb420;

        /* Chroma height is half of Luma for YUV420 */
        inDescPrm[VCORE_VPE_CBCR_IDX].transHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].frameHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].startY      /= 2U;
    }
    else if (FVID2_DF_YUV420SP_UV == prevFldDataFmt)
    {
        inDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y420;
        inDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_C420;

        /* Chroma height is half of Luma for YUV420 */
        inDescPrm[VCORE_VPE_CBCR_IDX].transHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].frameHeight /= 2U;
        inDescPrm[VCORE_VPE_CBCR_IDX].startY      /= 2U;
    }
    else /* Invalid Data Format */
    {
        retVal = FVID2_EINVALID_PARAMS;
    }

    if (BSP_SOK == retVal)
    {
        /* Program the descriptor */
        for (fldCnt = 0U; fldCnt < VCORE_VPE_MAX_PREV_FLD; fldCnt++)
        {
            /*
             *  Caution:
             *  This relies on the fact that the previous fields are in order
             *  starting from VCORE_VPE_FLD1LUMA_IDX.
             */
            tempIdx = (UInt32) VCORE_VPE_FLD1LUMA_IDX +
                      (fldCnt * VCORE_VPE_NUM_DESC_PER_FIELD);
            for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_FIELD; cnt++)
            {
                if (TRUE == chObj->isDescReq[tempIdx + cnt])
                {
                    tempDescPrm = &inDescPrm[cnt];

                    /*
                     *  Caution:
                     *  Next statements relies on the fact that luma index
                     *  and chroma index are next to each other.
                     */
                    tempDescPrm->channel     = instObj->vpdmaCh[tempIdx + cnt];
                    tempDescPrm->nextChannel = instObj->vpdmaCh[tempIdx + cnt];

                    descOffset = chObj->descOffset[tempIdx + cnt];
                    descPtr    = descMem->inDataDesc[descOffset];
                    GT_assert(VpsVpeCoreTrace, NULL != descPtr);
                    retVal = VpsHal_vpdmaCreateInBoundDataDesc(
                        descPtr,
                        tempDescPrm);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(VpsVpeCoreTrace, GT_ERR,
                                  "VPDMA Descriptor Creation Failed!!\r\n");
                        break;
                    }
                }
            }
        }
    }

    return retVal;
}

/**
 *  vcoreVpeProgramCurOutDesc
 *  \brief Programs the current output data descriptor depending on the
 *  parameters set.
 */
Int32 vcoreVpeProgramCurOutDesc(const Vcore_VpeInstObj *instObj,
                                const Vcore_VpeChObj   *chObj,
                                const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, fldCnt;
    UInt32 tempIdx;
    UInt32 descOffset;
    UInt32 lineStride;
    void  *descPtr;
    VpsHal_VpdmaOutDescParams outDescPrm[VCORE_VPE_NUM_DESC_PER_FIELD];

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);

    /* Set the common VPDMA parameter for current field output -
     * Assume initially compressor/decompressor is disabled for all fields. */
    for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_FIELD; cnt++)
    {
        /* Since the buffer is in YUV 422 semi-planar format, line stride
         * is same as line size for both Y and C buffer */
        lineStride = chObj->corePrms.fmt.width;
        lineStride = VpsUtils_align(lineStride,
                                    (UInt32) VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
        outDescPrm[cnt].lineStride = lineStride;
        outDescPrm[cnt].lineSkip   = VPSHAL_VPDMA_LS_1;
        outDescPrm[cnt].notify     = (UInt32) FALSE;
        outDescPrm[cnt].priority   = VPS_CFG_M2M_VPDMA_PRIORITY_WR;
        outDescPrm[cnt].memType    = VPSHAL_VPDMA_MT_NONTILEDMEM;
        outDescPrm[cnt].maxWidth   =
            VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED;
        outDescPrm[cnt].maxHeight =
            VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED;
    }

    /* Set the other VPDMA parameters */
    outDescPrm[VCORE_VPE_Y_IDX].dataType    = VPSHAL_VPDMA_CHANDT_Y422;
    outDescPrm[VCORE_VPE_CBCR_IDX].dataType = VPSHAL_VPDMA_CHANDT_C422;

    /* Program the descriptor */
    for (fldCnt = 0U; fldCnt < VCORE_VPE_MAX_OUT_FLD; fldCnt++)
    {
        /*
         *  Caution:
         *  This relies on the fact that the fields out are in order
         *  starting from VCORE_VPE_WRLUMA_IDX.
         */
        tempIdx = (UInt32) VCORE_VPE_WRLUMA_IDX +
                  (fldCnt * VCORE_VPE_NUM_DESC_PER_FIELD);
        for (cnt = 0U; cnt < VCORE_VPE_NUM_DESC_PER_FIELD; cnt++)
        {
            /*
             *  Caution:
             *  Next statement relies on the fact that luma index
             *  and chroma index are next to each other.
             */
            if (TRUE == chObj->isDescReq[tempIdx + cnt])
            {
                /*
                 *  Caution:
                 *  Next statement relies on the fact that luma index
                 *  and chroma index are next to each other.
                 */
                outDescPrm[cnt].channel =
                    instObj->vpdmaCh[tempIdx + cnt];
                outDescPrm[cnt].nextChannel =
                    instObj->vpdmaCh[tempIdx + cnt];
                outDescPrm[cnt].is1DData = (UInt32) FALSE;

                descOffset = chObj->descOffset[tempIdx + cnt];
                descPtr    = descMem->outDataDesc[descOffset];
                GT_assert(VpsVpeCoreTrace, NULL != descPtr);
                retVal = VpsHal_vpdmaCreateOutBoundDataDesc(
                    descPtr,
                    &outDescPrm[cnt]);
                if (BSP_SOK != retVal)
                {
                    GT_0trace(VpsVpeCoreTrace, GT_ERR,
                              "VPDMA Descriptor Creation Failed!!\r\n");
                    break;
                }
            }
        }
    }

    return retVal;
}

/**
 *  vcoreVpeProgramMvDesc
 *  \brief Programs the MV in and out descriptors depending on the parameters
 *  set.
 */
Int32 vcoreVpeProgramMvDesc(const Vcore_VpeInstObj *instObj,
                            const Vcore_VpeChObj   *chObj,
                            const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 mvCnt;
    UInt32 tempIdx;
    UInt32 descOffset;
    UInt32 lineStride;
    void  *descPtr;
    VpsHal_VpdmaInDescParams  inDescPrm;
    VpsHal_VpdmaOutDescParams outDescPrm;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);

    /* Set the common VPDMA parameter for MV inputs */
    inDescPrm.transWidth  = chObj->corePrms.fmt.width;
    inDescPrm.frameWidth  = chObj->corePrms.fmt.width;
    inDescPrm.transHeight = chObj->corePrms.fmt.height;
    inDescPrm.frameHeight = chObj->corePrms.fmt.height;
    /* 4-bits per pixel. So linesize in bytes is half the linesize in pixels */
    lineStride = chObj->corePrms.fmt.width / (UInt32) 2U;
    lineStride = VpsUtils_align(lineStride,
                                (UInt32) VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
    inDescPrm.lineStride = lineStride;
    inDescPrm.lineSkip   = VPSHAL_VPDMA_LS_1;
    inDescPrm.startX     = 0U;
    inDescPrm.startY     = 0U;
    inDescPrm.notify     = (UInt32) FALSE;
    inDescPrm.priority   = VPS_CFG_M2M_VPDMA_PRIORITY_RD;
    inDescPrm.memType    = VPSHAL_VPDMA_MT_NONTILEDMEM;
    inDescPrm.dataType   = VPSHAL_VPDMA_CHANDT_MV;
    inDescPrm.is1DData   = (UInt32) FALSE;

    /* Program the descriptor */
    for (mvCnt = 0U; mvCnt < VCORE_VPE_MAX_MV_IN; mvCnt++)
    {
        /*
         *  Caution:
         *  This relies on the fact that the MVs are in order
         *  starting from VCORE_VPE_MV1_IDX.
         */
        tempIdx = VCORE_VPE_MV1_IDX + mvCnt;
        if (TRUE == chObj->isDescReq[tempIdx])
        {
            inDescPrm.channel     = instObj->vpdmaCh[tempIdx];
            inDescPrm.nextChannel = instObj->vpdmaCh[tempIdx];

            /* Configure MV data descriptor */
            descOffset = chObj->descOffset[tempIdx];
            descPtr    = descMem->inDataDesc[descOffset];
            GT_assert(VpsVpeCoreTrace, NULL != descPtr);
            retVal = VpsHal_vpdmaCreateInBoundDataDesc(descPtr, &inDescPrm);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "VPDMA Descriptor Creation Failed!!\r\n");
                break;
            }
        }
    }

    if ((BSP_SOK == retVal) &&
        (TRUE == chObj->isDescReq[VCORE_VPE_MVOUT_IDX]))
    {
        /* Program the MV out descriptor */
        outDescPrm.channel     = instObj->vpdmaCh[VCORE_VPE_MVOUT_IDX];
        outDescPrm.nextChannel = instObj->vpdmaCh[VCORE_VPE_MVOUT_IDX];
        outDescPrm.dataType    = VPSHAL_VPDMA_CHANDT_MV;
        /* 4-bits per pixel. So linesize in bytes is half the linesize in
         * pixels */
        lineStride = chObj->corePrms.fmt.width / (UInt32) 2U;
        lineStride = VpsUtils_align(lineStride,
                                    (UInt32) VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
        outDescPrm.lineStride = lineStride;
        outDescPrm.lineSkip   = VPSHAL_VPDMA_LS_1;
        outDescPrm.notify     = (UInt32) FALSE;
        outDescPrm.priority   = VPS_CFG_M2M_VPDMA_PRIORITY_WR;
        outDescPrm.memType    = VPSHAL_VPDMA_MT_NONTILEDMEM;
        outDescPrm.maxWidth   = VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED;
        outDescPrm.maxHeight  = VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED;
        outDescPrm.is1DData   = (UInt32) FALSE;

        /* Configure MV out data descriptor */
        descOffset = chObj->descOffset[VCORE_VPE_MVOUT_IDX];
        descPtr    = descMem->outDataDesc[descOffset];
        GT_assert(VpsVpeCoreTrace, NULL != descPtr);
        retVal = VpsHal_vpdmaCreateOutBoundDataDesc(descPtr, &outDescPrm);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "VPDMA Descriptor Creation Failed!!\r\n");
        }
    }

    return retVal;
}

/**
 *  vcoreVpeProgramMvstmDesc
 *  \brief Programs the MV in and out descriptors depending on the parameters
 *  set.
 */
Int32 vcoreVpeProgramMvstmDesc(const Vcore_VpeInstObj *instObj,
                               const Vcore_VpeChObj   *chObj,
                               const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 mvstmCnt;
    UInt32 tempIdx;
    UInt32 descOffset;
    UInt32 lineStride;
    void  *descPtr;
    VpsHal_VpdmaInDescParams  inDescPrm;
    VpsHal_VpdmaOutDescParams outDescPrm;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);

    /* Set the common VPDMA parameter for MVSTM inputs */
    inDescPrm.transWidth  = chObj->corePrms.fmt.width;
    inDescPrm.frameWidth  = chObj->corePrms.fmt.width;
    inDescPrm.transHeight = chObj->corePrms.fmt.height;
    inDescPrm.frameHeight = chObj->corePrms.fmt.height;
    /* 4-bits per pixel. So linesize in bytes is half the linesize in pixels */
    lineStride = chObj->corePrms.fmt.width / (UInt32) 2U;
    lineStride = VpsUtils_align(lineStride,
                                (UInt32) VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
    inDescPrm.lineStride = lineStride;
    inDescPrm.lineSkip   = VPSHAL_VPDMA_LS_1;
    inDescPrm.startX     = 0U;
    inDescPrm.startY     = 0U;
    inDescPrm.notify     = (UInt32) FALSE;
    inDescPrm.priority   = VPS_CFG_M2M_VPDMA_PRIORITY_RD;
    inDescPrm.memType    = VPSHAL_VPDMA_MT_NONTILEDMEM;
    inDescPrm.dataType   = VPSHAL_VPDMA_CHANDT_MV;
    inDescPrm.is1DData   = (UInt32) FALSE;

    for (mvstmCnt = 0; mvstmCnt < VCORE_VPE_MAX_MVSTM_IN; mvstmCnt++)
    {
        /*
         *  Caution:
         *  This relies on the fact that the MVSTMs are in order
         *  starting from VCORE_VPE_MVSTM_IDX.
         */
        tempIdx = VCORE_VPE_MVSTM_IDX + mvstmCnt;
        if (TRUE == chObj->isDescReq[tempIdx])
        {
            inDescPrm.channel     = instObj->vpdmaCh[tempIdx];
            inDescPrm.nextChannel = instObj->vpdmaCh[tempIdx];

            /* Configure MVSTM data descriptor */
            descOffset = chObj->descOffset[tempIdx];
            descPtr    = descMem->inDataDesc[descOffset];
            GT_assert(VpsVpeCoreTrace, NULL != descPtr);
            retVal = VpsHal_vpdmaCreateInBoundDataDesc(descPtr, &inDescPrm);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "VPDMA Descriptor Creation Failed!!\r\n");
                break;
            }
        }
    }

    if ((BSP_SOK == retVal) &&
        (TRUE == chObj->isDescReq[VCORE_VPE_MVSTMOUT_IDX]))
    {
        /* Program the MVSTM out descriptor */
        outDescPrm.channel     = instObj->vpdmaCh[VCORE_VPE_MVSTMOUT_IDX];
        outDescPrm.nextChannel = instObj->vpdmaCh[VCORE_VPE_MVSTMOUT_IDX];
        outDescPrm.dataType    = VPSHAL_VPDMA_CHANDT_MV;
        /* 4-bits per pixel. So linesize in bytes is half the linesize in
         * pixels */
        lineStride = chObj->corePrms.fmt.width / (UInt32) 2U;
        lineStride = VpsUtils_align(lineStride,
                                    (UInt32) VPSHAL_VPDMA_LINE_STRIDE_ALIGN);
        outDescPrm.lineStride = lineStride;
        outDescPrm.lineSkip   = VPSHAL_VPDMA_LS_1;
        outDescPrm.notify     = (UInt32) FALSE;
        outDescPrm.priority   = VPS_CFG_M2M_VPDMA_PRIORITY_WR;
        outDescPrm.memType    = VPSHAL_VPDMA_MT_NONTILEDMEM;
        outDescPrm.maxWidth   = VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED;
        outDescPrm.maxHeight  = VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED;
        outDescPrm.is1DData   = (UInt32) FALSE;

        /* Configure MVSTM out data descriptor */
        descOffset = chObj->descOffset[VCORE_VPE_MVSTMOUT_IDX];
        descPtr    = descMem->outDataDesc[descOffset];
        GT_assert(VpsVpeCoreTrace, NULL != descPtr);
        retVal = VpsHal_vpdmaCreateOutBoundDataDesc(descPtr, &outDescPrm);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "VPDMA Descriptor Creation Failed!!\r\n");
        }
    }

    return retVal;
}

/**
 *  vcoreVpeFigureOutState
 *  \brief Figures out the DEI state machine parameters like previous field
 *  buffers, number of MVSTM buffers, MV buffers etc... based on DEI params
 *  provided at the time of set params.
 */
Int32 vcoreVpeFigureOutState(const Vcore_VpeInstObj *instObj,
                             Vcore_VpeChObj         *chObj,
                             const Vcore_VpeParams  *corePrms)
{
    Int32  retVal = BSP_SOK;
    UInt32 chCnt;
    Vcore_M2mDeiCtxInfo *ctxInfo;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != corePrms);
    ctxInfo = &chObj->ctxInfo;

    /* Initialize all first */
    for (chCnt = 0U; chCnt < VCORE_VPE_MAX_VPDMA_CH; chCnt++)
    {
        /* Indicates descriptors are not needed */
        chObj->isDescReq[chCnt] = (UInt32) FALSE;
        /* Indicates all of them are dummy */
        chObj->isDescDummy[chCnt] = (UInt32) TRUE;
    }
    ctxInfo->isTnrMode = (UInt32) FALSE;

    if (TRUE == corePrms->deiCfg.bypass)
    {
        /* Bypass mode - no previous, MV and output required */
        ctxInfo->isDeinterlacing = (UInt32) FALSE;
        ctxInfo->numPrevFld      = 0U;
        ctxInfo->numMvIn         = 0U;
        ctxInfo->numMvOut        = 0U;
        ctxInfo->numMvstmIn      = 0U;
        ctxInfo->numMvstmOut     = 0U;
        ctxInfo->numCurFldOut    = 0U;

        /* Set flag to indicate whether a descriptor is required or not */
        chObj->isDescReq[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) TRUE;
        chObj->isDescReq[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) TRUE;

        /* Set flag to indicate whether the required descriptor is
         * dummy or not. Use buffer memset to zero for dummy read
         * descriptors and set the drop data for dummy write descriptor. */
        chObj->isDescDummy[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) FALSE;
        chObj->isDescDummy[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) FALSE;
    }
    else
    {
        ctxInfo->isDeinterlacing = (UInt32) TRUE;
        if (VPS_DEI_EDIMODE_LINE_AVG == corePrms->deiCfg.inpMode)
        {
            ctxInfo->numPrevFld  = 2U;
            ctxInfo->numMvIn     = 1U;
            ctxInfo->numMvOut    = 1U;
            ctxInfo->numMvstmIn  = 0U;
            ctxInfo->numMvstmOut = 0U;
            if ((VPSHAL_VPDMA_CHANNEL_INVALID ==
                 instObj->vpdmaCh[VCORE_VPE_WRLUMA_IDX]) ||
                (VPSHAL_VPDMA_CHANNEL_INVALID ==
                 instObj->vpdmaCh[VCORE_VPE_WRCHROMA_IDX]))
            {
                /* No write channel available */
                ctxInfo->numCurFldOut = 0U;
            }
            else
            {
                ctxInfo->numCurFldOut = 1U;
                chObj->isDescReq[VCORE_VPE_WRLUMA_IDX]     = (UInt32) TRUE;
                chObj->isDescReq[VCORE_VPE_WRCHROMA_IDX]   = (UInt32) TRUE;
                chObj->isDescDummy[VCORE_VPE_WRLUMA_IDX]   = (UInt32) TRUE;
                chObj->isDescDummy[VCORE_VPE_WRCHROMA_IDX] = (UInt32) TRUE;
            }

            /* Set flag to indicate whether a descriptor is required or not */
            chObj->isDescReq[VCORE_VPE_FLD1LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD1CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD2LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD2CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_MV1_IDX]        = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_MVOUT_IDX]      = (UInt32) TRUE;

            /* Set flag to indicate whether the required descriptor is
             * dummy or not. Use buffer memset to zero for dummy read
             * descriptors and set the drop data for dummy write descriptor. */
            chObj->isDescDummy[VCORE_VPE_FLD1LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescDummy[VCORE_VPE_FLD1CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescDummy[VCORE_VPE_FLD2LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescDummy[VCORE_VPE_FLD2CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescDummy[VCORE_VPE_MV1_IDX]        = (UInt32) TRUE;
            chObj->isDescDummy[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_MVOUT_IDX]      = (UInt32) TRUE;
        }
        else if (VPS_DEI_EDIMODE_FLD_AVG == corePrms->deiCfg.inpMode)
        {
            ctxInfo->numPrevFld  = 2U;
            ctxInfo->numMvIn     = 1U;
            ctxInfo->numMvOut    = 1U;
            ctxInfo->numMvstmIn  = 0U;
            ctxInfo->numMvstmOut = 0U;
            if ((VPSHAL_VPDMA_CHANNEL_INVALID ==
                 instObj->vpdmaCh[VCORE_VPE_WRLUMA_IDX]) ||
                (VPSHAL_VPDMA_CHANNEL_INVALID ==
                 instObj->vpdmaCh[VCORE_VPE_WRCHROMA_IDX]))
            {
                /* No write channel available */
                ctxInfo->numCurFldOut = 0U;
            }
            else
            {
                ctxInfo->numCurFldOut = 1U;
                chObj->isDescReq[VCORE_VPE_WRLUMA_IDX]     = (UInt32) TRUE;
                chObj->isDescReq[VCORE_VPE_WRCHROMA_IDX]   = (UInt32) TRUE;
                chObj->isDescDummy[VCORE_VPE_WRLUMA_IDX]   = (UInt32) FALSE;
                chObj->isDescDummy[VCORE_VPE_WRCHROMA_IDX] = (UInt32) FALSE;
            }

            /* Set flag to indicate whether a descriptor is required or not */
            chObj->isDescReq[VCORE_VPE_FLD1LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD1CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD2LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD2CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_MV1_IDX]        = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_MVOUT_IDX]      = (UInt32) TRUE;

            /* Set flag to indicate whether the required descriptor is
             * dummy or not. Use buffer memset to zero for dummy read
             * descriptors and set the drop data for dummy write descriptor. */
            chObj->isDescDummy[VCORE_VPE_FLD1LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD1CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD2LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD2CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_MV1_IDX]        = (UInt32) TRUE;
            chObj->isDescDummy[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_MVOUT_IDX]      = (UInt32) TRUE;
        }
        else
        {
            ctxInfo->numPrevFld  = 2U;
            ctxInfo->numMvIn     = 1U;
            ctxInfo->numMvOut    = 1U;
            ctxInfo->numMvstmIn  = 0U;
            ctxInfo->numMvstmOut = 0U;
            if ((VPSHAL_VPDMA_CHANNEL_INVALID ==
                 instObj->vpdmaCh[VCORE_VPE_WRLUMA_IDX]) ||
                (VPSHAL_VPDMA_CHANNEL_INVALID ==
                 instObj->vpdmaCh[VCORE_VPE_WRCHROMA_IDX]))
            {
                /* No write channel available */
                ctxInfo->numCurFldOut = 0U;
            }
            else
            {
                ctxInfo->numCurFldOut = 1U;
                chObj->isDescReq[VCORE_VPE_WRLUMA_IDX]     = (UInt32) TRUE;
                chObj->isDescReq[VCORE_VPE_WRCHROMA_IDX]   = (UInt32) TRUE;
                chObj->isDescDummy[VCORE_VPE_WRLUMA_IDX]   = (UInt32) FALSE;
                chObj->isDescDummy[VCORE_VPE_WRCHROMA_IDX] = (UInt32) FALSE;
            }

            /* Set flag to indicate whether a descriptor is required or not */
            chObj->isDescReq[VCORE_VPE_FLD1LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD1CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD2LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD2CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_MV1_IDX]        = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) TRUE;
            chObj->isDescReq[VCORE_VPE_MVOUT_IDX]      = (UInt32) TRUE;

            /* Set flag to indicate whether the required descriptor is
             * dummy or not. Use buffer memset to zero for dummy read
             * descriptors and set the drop data for dummy write descriptor. */
            chObj->isDescDummy[VCORE_VPE_FLD1LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD1CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD2LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD2CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_MV1_IDX]        = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD0LUMA_IDX]   = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_FLD0CHROMA_IDX] = (UInt32) FALSE;
            chObj->isDescDummy[VCORE_VPE_MVOUT_IDX]      = (UInt32) FALSE;
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeUpdateMode
 *  \brief Update the DEI mode based on the previous state. This is used
 *  for the reset sequence.
 */
Int32 vcoreVpeUpdateMode(Vcore_VpeInstObj       *instObj,
                         const Vcore_VpeChObj   *chObj,
                         const Vcore_M2mDescMem *descMem,
                         UInt32                  prevFldState)
{
    Int32  retVal     = BSP_SOK;
    void  *cfgOvlyPtr = NULL;
    VpsHal_DeiEdiConfig ediCfg;
    UInt32 cfgOvlyPtrValue;

    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != instObj->halHandle[VCORE_VPE_DEI_IDX]);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descMem);
    GT_assert(VpsVpeCoreTrace, NULL != descMem->shadowOvlyMem);

    /* No need to enter the "change mode state" in line average mode!! */
    if (VPS_DEI_EDIMODE_LINE_AVG != chObj->corePrms.deiCfg.inpMode)
    {
        /* Use Line Average Mode for the first few frames */
        if (0U == prevFldState)
        {
            ediCfg.inpMode             = VPS_DEI_EDIMODE_LINE_AVG;
            ediCfg.tempInpEnable       = chObj->corePrms.deiCfg.tempInpEnable;
            ediCfg.tempInpChromaEnable =
                chObj->corePrms.deiCfg.tempInpChromaEnable;

            /* Set only the EDI mode */
            cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                              + instObj->ovlyOffset[VCORE_VPE_DEI_IDX];
            cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            retVal     = VpsHal_deiSetEdiConfig(
                instObj->halHandle[VCORE_VPE_DEI_IDX],
                &ediCfg,
                cfgOvlyPtr);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "DEI HAL Set EDI Config Overlay Failed!!\r\n");
            }
        }
        else
        {
            /* Switch to the required mode when all the previous fields are
             * available */
            if (prevFldState == chObj->ctxInfo.numPrevFld)
            {
                ediCfg.inpMode       = chObj->corePrms.deiCfg.inpMode;
                ediCfg.tempInpEnable =
                    chObj->corePrms.deiCfg.tempInpEnable;
                ediCfg.tempInpChromaEnable =
                    chObj->corePrms.deiCfg.tempInpChromaEnable;

                /* Set only the EDI mode */
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                                  + instObj->ovlyOffset[VCORE_VPE_DEI_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
                retVal     = VpsHal_deiSetEdiConfig(
                    instObj->halHandle[VCORE_VPE_DEI_IDX],
                    &ediCfg,
                    cfgOvlyPtr);
                if (BSP_SOK != retVal)
                {
                    GT_0trace(VpsVpeCoreTrace, GT_ERR,
                              "DEI HAL Set EDI Config Overlay Failed!!\r\n");
                }
            }
        }
    }

    return (retVal);
}

