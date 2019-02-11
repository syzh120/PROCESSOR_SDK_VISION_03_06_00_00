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
 *  \file vpscore_vpeHal.c
 *
 *  \brief VPS VPE Path Core internal file containing HAL related functions.
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

static Int32 vcoreVpeSetHalCfg(const Vcore_VpeInstObj *instObj,
                               Vcore_VpeChObj         *chObj);
static Int32 vcoreVpeSetChrusHalCfg(Vcore_VpeChObj *chObj);
static Int32 vcoreVpeSetDeiHalCfg(const Vcore_VpeInstObj *instObj,
                                  Vcore_VpeChObj         *chObj);
static Int32 vcoreVpeSetScHalCfg(const Vcore_VpeInstObj *instObj,
                                 Vcore_VpeChObj         *chObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  vcoreVpeInitHalParams
 *  \brief Sets the HAL overlay pointers and function pointers.
 */
void vcoreVpeInitHalParams(Vcore_VpeInstObj          *instObj,
                           const Vcore_VpeInitParams *initPrms)
{
    UInt32 ovlyOffset;
    UInt32 halCnt;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != initPrms);

    /* Assign get overlay size function pointer */
    instObj->getCfgOvlySize[VCORE_VPE_CHRUS0_IDX] =
        &VpsHal_chrusGetConfigOvlySize;
    instObj->getCfgOvlySize[VCORE_VPE_CHRUS1_IDX] =
        &VpsHal_chrusGetConfigOvlySize;
    instObj->getCfgOvlySize[VCORE_VPE_CHRUS2_IDX] =
        &VpsHal_chrusGetConfigOvlySize;
    instObj->getCfgOvlySize[VCORE_VPE_DEI_IDX]   = &VpsHal_deiGetConfigOvlySize;
    instObj->getCfgOvlySize[VCORE_VPE_SC_IDX]    = &VpsHal_scGetConfigOvlySize;
    instObj->getCfgOvlySize[VCORE_VPE_VPDMA_IDX] = NULL;

    /* Assign create overlay function pointer */
    instObj->createCfgOvly[VCORE_VPE_CHRUS0_IDX] =
        &VpsHal_chrusCreateConfigOvly;
    instObj->createCfgOvly[VCORE_VPE_CHRUS1_IDX] =
        &VpsHal_chrusCreateConfigOvly;
    instObj->createCfgOvly[VCORE_VPE_CHRUS2_IDX] =
        &VpsHal_chrusCreateConfigOvly;
    instObj->createCfgOvly[VCORE_VPE_DEI_IDX]   = &VpsHal_deiCreateConfigOvly;
    instObj->createCfgOvly[VCORE_VPE_SC_IDX]    = &VpsHal_scCreateConfigOvly;
    instObj->createCfgOvly[VCORE_VPE_VPDMA_IDX] = NULL;

    /* VPDMA HAL can't be NULL */
    GT_assert(VpsVpeCoreTrace,
              NULL != initPrms->halHandle[VCORE_VPE_VPDMA_IDX]);

    /* Initialize HAL variables */
    ovlyOffset = 0U;
    for (halCnt = 0U; halCnt < VCORE_VPE_MAX_HAL; halCnt++)
    {
        /* Get the HAL handle */
        instObj->halHandle[halCnt] = initPrms->halHandle[halCnt];

        instObj->ovlyOffset[halCnt] = ovlyOffset;
        /* Get the overlay size for each of the modules */
        if ((NULL != instObj->halHandle[halCnt]) &&
            (NULL != instObj->getCfgOvlySize[halCnt]))
        {
            instObj->halShadowOvlySize[halCnt] =
                instObj->getCfgOvlySize[halCnt](instObj->halHandle[halCnt]);
            ovlyOffset += instObj->halShadowOvlySize[halCnt];
        }
        else
        {
            instObj->halShadowOvlySize[halCnt] = 0U;
        }
    }

    return;
}

/**
 *  vcoreVpeSetChParams
 *  \brief Sets the channel parameter.
 */
Int32 vcoreVpeSetChParams(const Vcore_VpeInstObj *instObj,
                          Vcore_VpeChObj         *chObj,
                          const Vcore_VpeParams  *corePrms)
{
    Int32  retVal = BSP_SOK;
    UInt32 descOffset;
    UInt32 vpdmaChCnt;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != corePrms);

    /* Copy the params to the local structure */
    BspUtils_memcpy(&chObj->corePrms, corePrms, sizeof (Vcore_VpeParams));

    /* Figure out the DEI state depending up on the DEI parameter */
    retVal = vcoreVpeFigureOutState(instObj, chObj, corePrms);
    if (BSP_SOK == retVal)
    {
        /* Set the configuration for each of the HALs */
        retVal = vcoreVpeSetHalCfg(instObj, chObj);
    }

    if (BSP_SOK == retVal)
    {
        /* Dummy data descriptor is not needed if frame size and buffer
         * bottom-right coordinates match */
        chObj->numExtraDesc = 0U;
        if (((corePrms->startX + corePrms->fmt.width) <
             corePrms->frameWidth) ||
            ((corePrms->startY + corePrms->fmt.height) < corePrms->frameHeight))
        {
            chObj->isDummyNeeded = TRUE;
            chObj->numExtraDesc += instObj->numDescPerWindow;
        }
        else
        {
            chObj->isDummyNeeded = FALSE;
        }

        /* Initialize the register offsets for the frame start registers
         * which are used to form the VPDMA configuration overlay */
        chObj->numFsEvtReg = 0U;
        for (vpdmaChCnt = VCORE_VPE_START_IN_CH;
             vpdmaChCnt < (VCORE_VPE_START_IN_CH + VCORE_VPE_MAX_IN_CH);
             vpdmaChCnt++)
        {
            /* Set the frame start only if the descriptor is required.
             * This way it also makes sure that it programs frame start
             * event for the DEI_M channels correctly */
            if (TRUE == chObj->isDescReq[vpdmaChCnt])
            {
                chObj->fsRegOffset[chObj->numFsEvtReg] =
                    (UInt32 *) VpsHal_vpdmaGetClientRegAdd(
                        instObj->halHandle[VCORE_VPE_VPDMA_IDX],
                        instObj->vpdmaCh[vpdmaChCnt]);
                chObj->numFsEvtReg++;
            }
        }

        /* Get the size of the overlay for DEI registers and the relative
         * virtual offset for the above registers when VPDMA config register
         * overlay is formed */
        chObj->fsCfgOvlySize = VpsHal_vpdmaCalcRegOvlyMemSize(
            chObj->fsRegOffset,
            chObj->numFsEvtReg,
            chObj->fsVirRegOffset);

        /* Set the channel information depending on DEIs requirement. */
        vcoreVpeSetDescInfo(
            instObj,
            chObj,
            &chObj->descInfo,
            instObj->numDescPerWindow);

        /* Figure out the descriptor offset for inbound descriptors */
        descOffset = 0U;
        for (vpdmaChCnt = VCORE_VPE_START_IN_CH;
             vpdmaChCnt < (VCORE_VPE_START_IN_CH + VCORE_VPE_MAX_IN_CH);
             vpdmaChCnt++)
        {
            chObj->descOffset[vpdmaChCnt] = descOffset;
            /* Add the offset only when the programming is required */
            if (TRUE == chObj->isDescReq[vpdmaChCnt])
            {
                descOffset++;
            }
        }

        /* Figure out the descriptor offset for outbound descriptors */
        descOffset = 0U;
        for (vpdmaChCnt = VCORE_VPE_START_OUT_CH;
             vpdmaChCnt < (VCORE_VPE_START_OUT_CH + VCORE_VPE_MAX_OUT_CH);
             vpdmaChCnt++)
        {
            chObj->descOffset[vpdmaChCnt] = descOffset;
            /* Add the offset only when the programming is required */
            if (TRUE == chObj->isDescReq[vpdmaChCnt])
            {
                descOffset++;
            }
        }

        /* Figure out the Y and C buffer index based on data format */
        if (Fvid2_isDataFmtYuv422I(corePrms->fmt.dataFormat))
        {
            /* YUV 422 interleaved format - C buffer is also same as Y */
            chObj->bufIndex[VCORE_VPE_Y_IDX]    = FVID2_YUV_INT_ADDR_IDX;
            chObj->bufIndex[VCORE_VPE_CBCR_IDX] = FVID2_YUV_INT_ADDR_IDX;
        }
        else
        {
            /* YUV 420/422 semi-planar format */
            chObj->bufIndex[VCORE_VPE_Y_IDX]    = FVID2_YUV_SP_Y_ADDR_IDX;
            chObj->bufIndex[VCORE_VPE_CBCR_IDX] =
                FVID2_YUV_SP_CBCR_ADDR_IDX;
        }

        /* Set proper state - parameter is set */
        chObj->state.isParamsSet = (UInt32) TRUE;
    }

    return (retVal);
}

/**
 *  vcoreVpeSetDescInfo
 *  \brief Sets the descriptor information based on the parameters set.
 */
Int32 vcoreVpeSetDescInfo(const Vcore_VpeInstObj *instObj,
                          const Vcore_VpeChObj   *chObj,
                          Vcore_M2mDescInfo      *descInfo,
                          UInt32                  numFirstRowDesc)
{
    Int32  retVal = BSP_SOK;
    UInt32 halCnt;
    UInt32 vpdmaChCnt, socIdx;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);
    GT_assert(VpsVpeCoreTrace, NULL != descInfo);

    /* Calculate the number of inbound descriptors required */
    descInfo->numInDataDesc =
        numFirstRowDesc +
        (UInt32) (chObj->ctxInfo.numPrevFld * VCORE_VPE_NUM_DESC_PER_FIELD) +
        chObj->ctxInfo.numMvIn;
    /* If the MVSTM loop is needed, it needs two input buffers,
     * so context information indicates two buffers but number
     * of in bound descriptors is one only for MVSTM loop.
     * This should be removed if mvstm itself needs two input
     * descriptors. */
    if (chObj->ctxInfo.numMvstmIn > 0U)
    {
        descInfo->numInDataDesc += (chObj->ctxInfo.numMvstmIn - 1U);
    }

    /* Calculate the number of outbound descriptors required */
    descInfo->numOutDataDesc =
        (chObj->ctxInfo.numCurFldOut * VCORE_VPE_NUM_DESC_PER_FIELD) +
        chObj->ctxInfo.numMvOut +
        chObj->ctxInfo.numMvstmOut;

    /* Calculate the size of shadow overlay memory required by adding
     * the shadow overlay size of each HAL */
    descInfo->shadowOvlySize = 0U;
    for (halCnt = 0U; halCnt < VCORE_VPE_MAX_HAL; halCnt++)
    {
        descInfo->shadowOvlySize += instObj->halShadowOvlySize[halCnt];
    }

    /* Only in M2M mode, FS event will be programmed through overlay */
    descInfo->nonShadowOvlySize = chObj->fsCfgOvlySize;

    /* Get the horizontal, vertical and bilinear (if applicable) coeff
     * overlay sizes if scaler HAL is present.
     */
    if (NULL != instObj->halHandle[VCORE_VPE_SC_IDX])
    {
        VpsHal_scGetCoeffOvlySize(instObj->halHandle[VCORE_VPE_SC_IDX],
                                  &(descInfo->horzCoeffOvlySize),
                                  &(descInfo->vertCoeffOvlySize),
                                  &(descInfo->vertBilinearCoeffOvlySize));
        descInfo->coeffConfigDest = VpsHal_scGetVpdmaConfigDest(
            instObj->halHandle[VCORE_VPE_SC_IDX]);
    }
    else
    {
        descInfo->horzCoeffOvlySize         = 0U;
        descInfo->vertCoeffOvlySize         = 0U;
        descInfo->vertBilinearCoeffOvlySize = 0U;
    }

    /*
     * Assign the channels that needs to be used for SOCH descriptors.
     *
     * H/W Bug:
     * -------
     * If the video input data to the compressor for the next
     * frame starts before the compressor has completed sending out the
     * last frame, it will lock up. When it locks up, the input request
     * for the compressor goes low and stays low. This will cause the
     * current luma and chroma channels to lock up.
     *
     * Workaround:
     * ----------
     * Put a "Sync on Channel compress outputs" at the end of each
     * channel descriptors to send data to DEI. This will ensure that
     * the next field of video to send to DEI won’t start until
     * compress has completed sending the previous field out. Hence
     * using SOCH for all the possible input and output channels.
     *
     * Also when compression is enabled, driver should process the write
     * descriptor written to memory (to know the compressed data size)
     * only after VPDMA completes it. Hence SOCH is required on the
     * write channels to avoid this race condition.
     * Note: When compression is disabled, this may not be needed. But
     * still using it for uniformity.
     *
     * Otherwise SOCH on the main input channels and the output channels
     * is sufficient.
     */
    socIdx = 0U;
    for (vpdmaChCnt = 0U; vpdmaChCnt < VCORE_VPE_MAX_VPDMA_CH; vpdmaChCnt++)
    {
        if (TRUE == chObj->isDescReq[vpdmaChCnt])
        {
            descInfo->socChNum[socIdx] = instObj->vpdmaCh[vpdmaChCnt];
            socIdx++;
        }
    }
    descInfo->numChannels = socIdx;

    return (retVal);
}

/**
 *  vcoreVpeSetFsEvent
 *  \brief Sets the frame start event to the descriptor memory or directly
 *  to the VPDMA CSTAT registers.
 */
Int32 vcoreVpeSetFsEvent(const Vcore_VpeInstObj *instObj,
                         const Vcore_VpeChObj   *chObj,
                         const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 chCnt, fsEvtCnt;
    Int32  isDataFmtYuv422I, isDataFmtYuv422Sp;
    VpsHal_VpdmaLineMode lineMode[VCORE_VPE_NUM_DESC_PER_FIELD], tempLineMode;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    isDataFmtYuv422I  = Fvid2_isDataFmtYuv422I(chObj->corePrms.fmt.dataFormat);
    isDataFmtYuv422Sp = Fvid2_isDataFmtYuv422Sp(chObj->corePrms.fmt.dataFormat);
    /* Figure out line mode based on data format and scan format */
    if (((Int32) TRUE == isDataFmtYuv422I) ||
        ((Int32) TRUE == isDataFmtYuv422Sp))
    {
        /* YUV422 data to CHR_US and DEI is in deinterlacing mode or
         * in interlaced bypass mode. Progressive bypass not supported.
         * Line mode for luma is reserved, set to 0 */
        lineMode[VCORE_VPE_Y_IDX]    = VPSHAL_VPDMA_LM_0;
        lineMode[VCORE_VPE_CBCR_IDX] = VPSHAL_VPDMA_LM_1;
    }
    else
    {
        /* YUV420 data to CHR_US and DEI is in deinterlacing mode or
         * in interlaced bypass mode. Progressive bypass not supported.
         * Line mode for luma is reserved, set to 0 */
        lineMode[VCORE_VPE_Y_IDX]    = VPSHAL_VPDMA_LM_0;
        lineMode[VCORE_VPE_CBCR_IDX] = VPSHAL_VPDMA_LM_0;
    }

    /* Program the frame start event of Y and CbCr channels in
     * overlay memory if requested for */
    if ((NULL != descMem) && (NULL != descMem->nonShadowOvlyMem))
    {
        /* Create overlay memory for VPDMA frame start event registers */
        retVal = VpsHal_vpdmaCreateRegOverlay(
            chObj->fsRegOffset,
            chObj->numFsEvtReg,
            descMem->nonShadowOvlyMem);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "Create Overlay Failed for VPDMA FS Event Reg!!\r\n");
        }
        else
        {
            fsEvtCnt = 0U;
            for (chCnt = VCORE_VPE_START_IN_CH;
                 chCnt < (VCORE_VPE_START_IN_CH + VCORE_VPE_MAX_IN_CH);
                 chCnt++)
            {
                if ((VCORE_VPE_FLD1LUMA_IDX == chCnt) ||
                    (VCORE_VPE_FLD2LUMA_IDX == chCnt) ||
                    (VCORE_VPE_FLD3LUMA_IDX == chCnt) ||
                    (VCORE_VPE_FLD0LUMA_IDX == chCnt))
                {
                    /* Set line mode for luma channels */
                    tempLineMode = lineMode[VCORE_VPE_Y_IDX];
                }
                else if ((VCORE_VPE_FLD1CHROMA_IDX == chCnt) ||
                         (VCORE_VPE_FLD2CHROMA_IDX == chCnt) ||
                         (VCORE_VPE_FLD3CHROMA_IDX == chCnt) ||
                         (VCORE_VPE_FLD0CHROMA_IDX == chCnt))
                {
                    /* Set line mode for chroma channels */
                    tempLineMode = lineMode[VCORE_VPE_CBCR_IDX];
                }
                else
                {
                    /* Set LM 0 for non-input channels */
                    tempLineMode = VPSHAL_VPDMA_LM_0;
                }

                /* Set the frame start only if the descriptor is required.
                 * This way it also makes sure that it programs frame start
                 * event for the DEI_M channels correctly */
                if (TRUE == chObj->isDescReq[chCnt])
                {
                    /* Program the frame start event */
                    VpsHal_vpdmaSetFrameStartEvent(
                        instObj->halHandle[VCORE_VPE_VPDMA_IDX],
                        instObj->vpdmaCh[chCnt],
                        chObj->fsEvent,
                        tempLineMode,
                        (UInt32) 0U,
                        descMem->nonShadowOvlyMem,
                        chObj->fsVirRegOffset[fsEvtCnt]);

                    fsEvtCnt++;
                }
            }
        }
    }
    else
    {
        /*
         * Program it directly in VPDMA regsiter
         */
        /* Program the frame start event for all inbound channels.
         * This is not required for outbound channels. In fact
         * for outbound channels, frame start should not be programmed
         * as the frame start of outbound channel is used by display
         * controller/DLM!! */
        for (chCnt = VCORE_VPE_START_IN_CH;
             chCnt < (VCORE_VPE_START_IN_CH + VCORE_VPE_MAX_IN_CH);
             chCnt++)
        {
            if ((VCORE_VPE_FLD1LUMA_IDX == chCnt) ||
                (VCORE_VPE_FLD2LUMA_IDX == chCnt) ||
                (VCORE_VPE_FLD3LUMA_IDX == chCnt) ||
                (VCORE_VPE_FLD0LUMA_IDX == chCnt))
            {
                /* Set line mode for luma channels */
                tempLineMode = lineMode[VCORE_VPE_Y_IDX];
            }
            else if ((VCORE_VPE_FLD1CHROMA_IDX == chCnt) ||
                     (VCORE_VPE_FLD2CHROMA_IDX == chCnt) ||
                     (VCORE_VPE_FLD3CHROMA_IDX == chCnt) ||
                     (VCORE_VPE_FLD0CHROMA_IDX == chCnt))
            {
                /* Set line mode for chroma channels */
                tempLineMode = lineMode[VCORE_VPE_CBCR_IDX];
            }
            else
            {
                /* Set LM 0 for non-input channels */
                tempLineMode = VPSHAL_VPDMA_LM_0;
            }

            /* Set the frame start only if the descriptor is required.
             * This way it also makes sure that it programs frame start
             * event for the DEI_M channels correctly */
            if (TRUE == chObj->isDescReq[chCnt])
            {
                VpsHal_vpdmaSetFrameStartEvent(
                    instObj->halHandle[VCORE_VPE_VPDMA_IDX],
                    instObj->vpdmaCh[chCnt],
                    chObj->fsEvent,
                    tempLineMode,
                    (UInt32) 0U,
                    NULL,
                    (UInt32) 0U);
            }
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeProgramReg
 *  \brief Programs all the HAL registers either through direct register writes
 *  or update them in overlay memory.
 */
Int32 vcoreVpeProgramReg(const Vcore_VpeInstObj *instObj,
                         const Vcore_VpeChObj   *chObj,
                         const Vcore_M2mDescMem *descMem)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt, tempIdx;
    void  *cfgOvlyPtr      = NULL;
    UInt32 cfgOvlyPtrValue = 0;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Configure Chrus module */
    if (BSP_SOK == retVal)
    {
        for (cnt = 0U; cnt < VCORE_VPE_MAX_CHR_US; cnt++)
        {
            tempIdx = cnt + VCORE_VPE_CHRUS0_IDX;
            if (NULL != instObj->halHandle[tempIdx])
            {
                cfgOvlyPtr = NULL;
                if (NULL != descMem)
                {
                    cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                                      + instObj->ovlyOffset[tempIdx];
                    cfgOvlyPtr = (void *) cfgOvlyPtrValue;
                }
                retVal = VpsHal_chrusSetConfig(
                    instObj->halHandle[tempIdx],
                    &chObj->chrusHalCfg,
                    cfgOvlyPtr);
                if (BSP_SOK != retVal)
                {
                    GT_1trace(VpsVpeCoreTrace, GT_ERR,
                              "CHRUS(%d) HAL Config Overlay Failed!!\r\n", cnt);
                    break;
                }
            }
        }
    }

    /* Configure deinterlacer module */
    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VPE_DEI_IDX])
        {
            if (NULL != descMem)
            {
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                                  + instObj->ovlyOffset[VCORE_VPE_DEI_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            }
            retVal = VpsHal_deiSetConfig(
                instObj->halHandle[VCORE_VPE_DEI_IDX],
                &chObj->deiHalCfg,
                cfgOvlyPtr);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "DEI HAL Config Overlay Failed!!\r\n");
            }
        }
    }

    /* Configure scaler module */
    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VPE_SC_IDX])
        {
            cfgOvlyPtr = NULL;
            if (NULL != descMem)
            {
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                                  + instObj->ovlyOffset[VCORE_VPE_SC_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            }
            retVal = VpsHal_scSetConfig(
                instObj->halHandle[VCORE_VPE_SC_IDX],
                &chObj->scHalCfg,
                cfgOvlyPtr);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "SCALER HAL Config Overlay Failed!!\r\n");
            }
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeProgramFmdReg
 *  \brief Programs FMD HAL registers either through direct register writes
 *  or update them in overlay memory.
 */
Int32 vcoreVpeProgramFmdReg(const Vcore_VpeHandleObj *hObj,
                            const Vps_DeiFmdConfig   *fmdCfg,
                            const Vcore_M2mDescMem   *descMem)
{
    Int32  retVal     = BSP_SOK;
    void  *cfgOvlyPtr = NULL;
    Vcore_VpeInstObj *instObj;
    Vcore_VpeChObj   *chObj;
    VpsHal_DeiConfig *deiHalCfg;
    UInt32 cfgOvlyPtrValue;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != fmdCfg);
    chObj = hObj->chObjs[fmdCfg->chNum];
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Configure deinterlacer module */
    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VPE_DEI_IDX])
        {
            if (NULL != descMem)
            {
                cfgOvlyPtr      = NULL;
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                                  + instObj->ovlyOffset[VCORE_VPE_DEI_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            }

            /* Update the FMD config in the channel object. */
            deiHalCfg = &chObj->deiHalCfg;
            deiHalCfg->fmd.filmMode = fmdCfg->filmMode;
            deiHalCfg->fmd.bed      = fmdCfg->bed;
            deiHalCfg->fmd.window   = fmdCfg->window;
            /* The two below are Read-Only registers: fmd.lock, fmd.jamDir */
            deiHalCfg->fmd.windowMinx = fmdCfg->windowMinx;
            deiHalCfg->fmd.windowMiny = fmdCfg->windowMiny;
            deiHalCfg->fmd.windowMaxx = fmdCfg->windowMaxx;
            deiHalCfg->fmd.windowMaxy = fmdCfg->windowMaxy;

            retVal = VpsHal_deiSetFmdConfig(
                instObj->halHandle[VCORE_VPE_DEI_IDX],
                &deiHalCfg->fmd,
                cfgOvlyPtr,
                deiHalCfg->width,
                deiHalCfg->height);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "DEI HAL Config Overlay Failed!!\r\n");
            }
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeProgramFmdUpdateReg
 *  \brief Programs FMD HAL registers either through direct register writes
 *  or update them in overlay memory.
 */
Int32 vcoreVpeProgramFmdUpdateReg(const Vcore_VpeHandleObj     *hObj,
                                  const Vps_DeiFmdUpdateConfig *fmdCfg,
                                  const Vcore_M2mDescMem       *descMem)
{
    Int32  retVal     = BSP_SOK;
    void  *cfgOvlyPtr = NULL;
    Vcore_VpeInstObj         *instObj;
    Vcore_VpeChObj           *chObj;
    VpsHal_DeiFmdUpdateConfig deiHalFmdUpdateCfg;
    UInt32 cfgOvlyPtrValue;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != fmdCfg);
    chObj = hObj->chObjs[fmdCfg->chNum];
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Configure deinterlacer module */
    if (BSP_SOK == retVal)
    {
        if (NULL != instObj->halHandle[VCORE_VPE_DEI_IDX])
        {
            if (NULL != descMem)
            {
                cfgOvlyPtr      = NULL;
                cfgOvlyPtrValue = (UInt32) descMem->shadowOvlyMem
                                  + instObj->ovlyOffset[VCORE_VPE_DEI_IDX];
                cfgOvlyPtr = (void *) cfgOvlyPtrValue;
            }
            /* copy to HAL config for overlay memory write */
            deiHalFmdUpdateCfg.lock   = fmdCfg->lock;
            deiHalFmdUpdateCfg.jamDir = fmdCfg->jamDir;

            /* Update the Hal Cfg for later overlay memory update */
            chObj->deiHalCfg.fmd.lock   = fmdCfg->lock;
            chObj->deiHalCfg.fmd.jamDir = fmdCfg->jamDir;

            retVal = VpsHal_deiUpdateFmdConfig(
                instObj->halHandle[VCORE_VPE_DEI_IDX],
                &deiHalFmdUpdateCfg,
                cfgOvlyPtr);
            if (BSP_SOK != retVal)
            {
                GT_0trace(VpsVpeCoreTrace, GT_ERR,
                          "DEI HAL Config Overlay Failed!!\r\n");
            }
        }
    }

    return (retVal);
}

/**
 *  vcoreVpeGetAdvCfgIoctl
 *  \brief Reads the advance DEI configuration.
 */
Int32 vcoreVpeGetAdvCfgIoctl(const Vcore_VpeHandleObj *hObj,
                             Vps_DeiRdWrAdvCfg        *advCfg)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj     *chObj;
    Vcore_VpeInstObj   *instObj;
    VpsHal_DeiConfig   *deiHalCfg;
    VpsHal_DeiFmdStatus fmdStatus;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != advCfg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != instObj->halHandle[VCORE_VPE_DEI_IDX]);
    chObj = hObj->chObjs[advCfg->chNum];
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Get the advance configuration */
    retVal = VpsHal_deiGetAdvConfig(
        instObj->halHandle[VCORE_VPE_DEI_IDX],
        advCfg);

    /* For all other configuration get them from the channel object. */
    deiHalCfg          = &chObj->deiHalCfg;
    advCfg->bypass     = deiHalCfg->bypass;
    advCfg->width      = deiHalCfg->width;
    advCfg->height     = deiHalCfg->height;
    advCfg->scanFormat = deiHalCfg->scanFormat;
    advCfg->fieldFlush = deiHalCfg->fieldFlush;

    /* Copy MDT configuration */
    advCfg->mdtCfg.spatMaxBypass = deiHalCfg->mdt.spatMaxBypass;
    advCfg->mdtCfg.tempMaxBypass = deiHalCfg->mdt.tempMaxBypass;

    /* Copy EDI configuration */
    advCfg->ediCfg.inpMode             = deiHalCfg->edi.inpMode;
    advCfg->ediCfg.tempInpEnable       = deiHalCfg->edi.tempInpEnable;
    advCfg->ediCfg.tempInpChromaEnable = deiHalCfg->edi.tempInpChromaEnable;

    /* Copy FMD configuration */
    advCfg->fmdCfg.filmMode   = deiHalCfg->fmd.filmMode;
    advCfg->fmdCfg.bed        = deiHalCfg->fmd.bed;
    advCfg->fmdCfg.window     = deiHalCfg->fmd.window;
    advCfg->fmdCfg.lock       = deiHalCfg->fmd.lock;
    advCfg->fmdCfg.jamDir     = deiHalCfg->fmd.jamDir;
    advCfg->fmdCfg.windowMinx = deiHalCfg->fmd.windowMinx;
    advCfg->fmdCfg.windowMiny = deiHalCfg->fmd.windowMiny;
    advCfg->fmdCfg.windowMaxx = deiHalCfg->fmd.windowMaxx;
    advCfg->fmdCfg.windowMaxy = deiHalCfg->fmd.windowMaxy;

    /* Read FMD status */
    retVal += VpsHal_deiGetFmdStatus(
        instObj->halHandle[VCORE_VPE_DEI_IDX],
        &fmdStatus);
    if (BSP_SOK == retVal)
    {
        /* Copy FMD status */
        advCfg->fmdCfg.frameDiff = fmdStatus.frameDiff;
        advCfg->fmdCfg.fldDiff   = fmdStatus.fldDiff;
        advCfg->fmdCfg.reset     = fmdStatus.reset;
        advCfg->fmdCfg.caf       = fmdStatus.caf;
    }

    return (retVal);
}

/**
 *  vcoreVpeSetAdvCfgIoctl
 *  \brief Writes the advance DEI configuration.
 */
Int32 vcoreVpeSetAdvCfgIoctl(const Vcore_VpeHandleObj *hObj,
                             const Vps_DeiRdWrAdvCfg  *advCfg)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj   *chObj;
    Vcore_VpeInstObj *instObj;
    VpsHal_DeiConfig *deiHalCfg;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != advCfg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != instObj->halHandle[VCORE_VPE_DEI_IDX]);
    chObj = hObj->chObjs[advCfg->chNum];
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Set the advance configuration */
    retVal = VpsHal_deiSetAdvConfig(
        instObj->halHandle[VCORE_VPE_DEI_IDX],
        advCfg,
        NULL);

    /* For all other configuration set them to the channel object. */
    deiHalCfg             = &chObj->deiHalCfg;
    deiHalCfg->bypass     = advCfg->bypass;
    deiHalCfg->width      = advCfg->width;
    deiHalCfg->height     = advCfg->height;
    deiHalCfg->scanFormat = advCfg->scanFormat;
    deiHalCfg->fieldFlush = advCfg->fieldFlush;

    /* Copy MDT configuration */
    deiHalCfg->mdt.spatMaxBypass = advCfg->mdtCfg.spatMaxBypass;
    deiHalCfg->mdt.tempMaxBypass = advCfg->mdtCfg.tempMaxBypass;

    /* Copy EDI configuration */
    deiHalCfg->edi.inpMode             = advCfg->ediCfg.inpMode;
    deiHalCfg->edi.tempInpEnable       = advCfg->ediCfg.tempInpEnable;
    deiHalCfg->edi.tempInpChromaEnable = advCfg->ediCfg.tempInpChromaEnable;

    /* Copy FMD configuration */
    deiHalCfg->fmd.filmMode   = advCfg->fmdCfg.filmMode;
    deiHalCfg->fmd.bed        = advCfg->fmdCfg.bed;
    deiHalCfg->fmd.window     = advCfg->fmdCfg.window;
    deiHalCfg->fmd.lock       = advCfg->fmdCfg.lock;
    deiHalCfg->fmd.jamDir     = advCfg->fmdCfg.jamDir;
    deiHalCfg->fmd.windowMinx = advCfg->fmdCfg.windowMinx;
    deiHalCfg->fmd.windowMiny = advCfg->fmdCfg.windowMiny;
    deiHalCfg->fmd.windowMaxx = advCfg->fmdCfg.windowMaxx;
    deiHalCfg->fmd.windowMaxy = advCfg->fmdCfg.windowMaxy;

    return (retVal);
}

/**
 *  vcoreVpeScGetAdvCfgIoctl
 *  \brief Reads the advance scaler configuration.
 */
Int32 vcoreVpeScGetAdvCfgIoctl(Vcore_VpeHandleObj   *hObj,
                               Vcore_M2mScCfgParams *scCfgPrms)
{
/* TODO */
#if 0
    Int32                  retVal     = BSP_EFAIL;
    void                  *cfgOvlyPtr = NULL;
    Vcore_VpeInstObj      *instObj;
    VpsHal_ScConfig        scHalCfg;
    Vps_ScPeakingConfig    peakingCfg;
    Vps_ScEdgeDetectConfig edgeDetectCfg;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != scCfgPrms);
    GT_assert(VpsVpeCoreTrace, NULL != scCfgPrms->scAdvCfg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    if (NULL != instObj->halHandle[VCORE_VPE_SC_IDX])
    {
        cfgOvlyPtr = NULL;
        if (NULL != scCfgPrms->descMem)
        {
            cfgOvlyPtr = (void *) ((UInt32) scCfgPrms->descMem->shadowOvlyMem
                                   + instObj->ovlyOffset[VCORE_VPE_SC_IDX]);
        }

        /* Get the scaler configuration from HAL */
        scHalCfg.peakingCfg    = &peakingCfg;
        scHalCfg.edgeDetectCfg = &edgeDetectCfg;
        retVal = VpsHal_scGetConfig(
            instObj->halHandle[VCORE_VPE_SC_IDX],
            &scHalCfg,
            cfgOvlyPtr);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "SCALER HAL Get Config Overlay Failed!!\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Copy the configuration */
        scCfgPrms->scAdvCfg->tarWidth         = scHalCfg.tarWidth;
        scCfgPrms->scAdvCfg->tarHeight        = scHalCfg.tarHeight;
        scCfgPrms->scAdvCfg->srcWidth         = scHalCfg.srcWidth;
        scCfgPrms->scAdvCfg->srcHeight        = scHalCfg.srcHeight;
        scCfgPrms->scAdvCfg->cropStartX       = scHalCfg.cropStartX;
        scCfgPrms->scAdvCfg->cropStartY       = scHalCfg.cropStartY;
        scCfgPrms->scAdvCfg->cropWidth        = scHalCfg.cropWidth;
        scCfgPrms->scAdvCfg->cropHeight       = scHalCfg.cropHeight;
        scCfgPrms->scAdvCfg->inFrameMode      = scHalCfg.inFrameMode;
        scCfgPrms->scAdvCfg->outFrameMode     = scHalCfg.outFrameMode;
        scCfgPrms->scAdvCfg->hsType           = scHalCfg.hsType;
        scCfgPrms->scAdvCfg->nonLinear        = scHalCfg.nonLinear;
        scCfgPrms->scAdvCfg->stripSize        = scHalCfg.stripSize;
        scCfgPrms->scAdvCfg->vsType           = scHalCfg.vsType;
        scCfgPrms->scAdvCfg->fidPol           = scHalCfg.fidPol;
        scCfgPrms->scAdvCfg->selfGenFid       = scHalCfg.selfGenFid;
        scCfgPrms->scAdvCfg->defConfFactor    = scHalCfg.defConfFactor;
        scCfgPrms->scAdvCfg->biLinIntpType    = scHalCfg.biLinIntpType;
        scCfgPrms->scAdvCfg->enableEdgeDetect = scHalCfg.enableEdgeDetect;
        scCfgPrms->scAdvCfg->hPolyBypass      = scHalCfg.hPolyBypass;
        scCfgPrms->scAdvCfg->enablePeaking    = scHalCfg.enablePeaking;
        scCfgPrms->scAdvCfg->bypass           = scHalCfg.bypass;
        scCfgPrms->scAdvCfg->rowAccInc        = scHalCfg.rowAccInc;
        scCfgPrms->scAdvCfg->rowAccOffset     = scHalCfg.rowAccOffset;
        scCfgPrms->scAdvCfg->rowAccOffsetB    = scHalCfg.rowAccOffsetB;
        scCfgPrms->scAdvCfg->ravScFactor      = scHalCfg.ravScFactor;
        scCfgPrms->scAdvCfg->ravRowAccInit    = scHalCfg.ravRowAccInit;
        scCfgPrms->scAdvCfg->ravRowAccInitB   = scHalCfg.ravRowAccInitB;
        if (NULL != scCfgPrms->scAdvCfg->peakingCfg)
        {
            BspUtils_memcpy(
                scCfgPrms->scAdvCfg->peakingCfg,
                scHalCfg.peakingCfg,
                sizeof (Vps_ScPeakingConfig));
        }
        if (NULL != scCfgPrms->scAdvCfg->edgeDetectCfg)
        {
            BspUtils_memcpy(
                scCfgPrms->scAdvCfg->edgeDetectCfg,
                scHalCfg.edgeDetectCfg,
                sizeof (Vps_ScEdgeDetectConfig));
        }
    }

    return (retVal);
#endif
    return (BSP_SOK);
}

/**
 *  vcoreVpeScSetAdvCfgIoctl
 *  \brief Writes the advance scaler configuration.
 */
Int32 vcoreVpeScSetAdvCfgIoctl(Vcore_VpeHandleObj         *hObj,
                               const Vcore_M2mScCfgParams *scCfgPrms)
{
/* TODO */
#if 0
    Int32             retVal     = BSP_EFAIL;
    void             *cfgOvlyPtr = NULL;
    Vcore_VpeInstObj *instObj;
    VpsHal_ScConfig   scHalCfg;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != scCfgPrms);
    GT_assert(VpsVpeCoreTrace, NULL != scCfgPrms->scAdvCfg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    if (NULL != instObj->halHandle[VCORE_VPE_SC_IDX])
    {
        /* Copy the configuration */
        scHalCfg.tarWidth    = scCfgPrms->scAdvCfg->tarWidth;
        scHalCfg.tarHeight   = scCfgPrms->scAdvCfg->tarHeight;
        scHalCfg.srcWidth    = scCfgPrms->scAdvCfg->srcWidth;
        scHalCfg.srcHeight   = scCfgPrms->scAdvCfg->srcHeight;
        scHalCfg.cropStartX  = scCfgPrms->scAdvCfg->cropStartX;
        scHalCfg.cropStartY  = scCfgPrms->scAdvCfg->cropStartY;
        scHalCfg.cropWidth   = scCfgPrms->scAdvCfg->cropWidth;
        scHalCfg.cropHeight  = scCfgPrms->scAdvCfg->cropHeight;
        scHalCfg.inFrameMode =
            (Vps_ScanFormat) scCfgPrms->scAdvCfg->inFrameMode;
        scHalCfg.outFrameMode =
            (Vps_ScanFormat) scCfgPrms->scAdvCfg->outFrameMode;
        scHalCfg.hsType     = scCfgPrms->scAdvCfg->hsType;
        scHalCfg.nonLinear  = scCfgPrms->scAdvCfg->nonLinear;
        scHalCfg.stripSize  = scCfgPrms->scAdvCfg->stripSize;
        scHalCfg.vsType     = scCfgPrms->scAdvCfg->vsType;
        scHalCfg.fidPol     = (Fvid2_FidPol) scCfgPrms->scAdvCfg->fidPol;
        scHalCfg.selfGenFid =
            (Vps_ScSelfGenFid) scCfgPrms->scAdvCfg->selfGenFid;
        scHalCfg.defConfFactor    = scCfgPrms->scAdvCfg->defConfFactor;
        scHalCfg.biLinIntpType    = scCfgPrms->scAdvCfg->biLinIntpType;
        scHalCfg.enableEdgeDetect = scCfgPrms->scAdvCfg->enableEdgeDetect;
        scHalCfg.hPolyBypass      = scCfgPrms->scAdvCfg->hPolyBypass;
        scHalCfg.enablePeaking    = scCfgPrms->scAdvCfg->enablePeaking;
        scHalCfg.bypass           = scCfgPrms->scAdvCfg->bypass;
        scHalCfg.phInfoMode       = VPS_SC_SET_PHASE_INFO_FROM_APP;
        scHalCfg.rowAccInc        = scCfgPrms->scAdvCfg->rowAccInc;
        scHalCfg.rowAccOffset     = scCfgPrms->scAdvCfg->rowAccOffset;
        scHalCfg.rowAccOffsetB    = scCfgPrms->scAdvCfg->rowAccOffsetB;
        scHalCfg.ravScFactor      = scCfgPrms->scAdvCfg->ravScFactor;
        scHalCfg.ravRowAccInit    = scCfgPrms->scAdvCfg->ravRowAccInit;
        scHalCfg.ravRowAccInitB   = scCfgPrms->scAdvCfg->ravRowAccInitB;
        scHalCfg.peakingCfg       = scCfgPrms->scAdvCfg->peakingCfg;
        scHalCfg.edgeDetectCfg    = scCfgPrms->scAdvCfg->edgeDetectCfg;

        cfgOvlyPtr = NULL;
        if (NULL != scCfgPrms->descMem)
        {
            cfgOvlyPtr = (void *) ((UInt32) scCfgPrms->descMem->shadowOvlyMem
                                   + instObj->ovlyOffset[VCORE_VPE_SC_IDX]);
        }

        /* Set the scaler configuration to HAL */
        retVal = VpsHal_scSetAdvConfig(
            instObj->halHandle[VCORE_VPE_SC_IDX],
            &scHalCfg,
            cfgOvlyPtr);
        if (BSP_SOK != retVal)
        {
            GT_0trace(VpsVpeCoreTrace, GT_ERR,
                      "SCALER HAL Set Config Overlay Failed!!\r\n");
        }
    }

    return (retVal);
#endif
    return (BSP_SOK);
}

/**
 *  vcoreVpeGetFmdStatIoctl
 *  \brief Reads the DEI FMD film mode status register configuration.
 */
Int32 vcoreVpeGetFmdStatIoctl(const Vcore_VpeHandleObj *hObj,
                              Vps_DeiFmdStatusReg      *statusReg)
{
    Int32 retVal = BSP_SOK;
    Vcore_VpeChObj *chObj;
    Vcore_VpeInstObj *instObj;
    VpsHal_DeiFmdStatus fmdStatus;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != statusReg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != instObj->halHandle[VCORE_VPE_DEI_IDX]);
    chObj = hObj->chObjs[statusReg->chNum];
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    /* Get the configuration from the HAL */
    retVal = VpsHal_deiGetFmdStatus(
        instObj->halHandle[VCORE_VPE_DEI_IDX],
        &fmdStatus);
    if (BSP_SOK == retVal)
    {
        /* Copy FMD status */
        statusReg->frameDiff = fmdStatus.frameDiff;
        statusReg->fldDiff   = fmdStatus.fldDiff;
        statusReg->reset     = fmdStatus.reset;
        statusReg->caf       = fmdStatus.caf;
        statusReg->fldMode   = 1U; /* only 4-field MDT is used in DEI_M */
    }

    return (retVal);
}

/**
 *  vcoreVpeSetHalCfg
 *  \brief Sets the configuration in the HAL structures.
 */
static Int32 vcoreVpeSetHalCfg(const Vcore_VpeInstObj *instObj,
                               Vcore_VpeChObj         *chObj)
{
    Int32 retVal;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    retVal  = vcoreVpeSetChrusHalCfg(chObj);
    retVal += vcoreVpeSetDeiHalCfg(instObj, chObj);
    retVal += vcoreVpeSetScHalCfg(instObj, chObj);

    return (retVal);
}

/**
 *  vcoreVpeSetChrusHalCfg
 *  \brief Sets the Chroma Upsampler HAL configuration based on params set.
 */
static Int32 vcoreVpeSetChrusHalCfg(Vcore_VpeChObj *chObj)
{
    Int32 retVal = BSP_SOK;
    VpsHal_ChrusConfig *chrusHalCfg;
    Int32 isDataFmtYuv422I, isDataFmtYuv422Sp;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    chrusHalCfg        = &chObj->chrusHalCfg;
    chrusHalCfg->coeff = NULL;
    if (FVID2_SF_INTERLACED == chObj->corePrms.fmt.scanFormat)
    {
        chrusHalCfg->mode = FVID2_SF_INTERLACED;
    }
    else
    {
        chrusHalCfg->mode = FVID2_SF_PROGRESSIVE;
    }

    /* Figure out line mode based on data format and deinterlacing mode */
    isDataFmtYuv422I  = Fvid2_isDataFmtYuv422I(chObj->corePrms.fmt.dataFormat);
    isDataFmtYuv422Sp = Fvid2_isDataFmtYuv422Sp(chObj->corePrms.fmt.dataFormat);
    if (((Int32) TRUE == isDataFmtYuv422I) ||
        ((Int32) TRUE == isDataFmtYuv422Sp))
    {
        /* YUV422 data to CHR_US and DEI is in deinterlacing mode or
         * in interlaced bypass mode. Progressive bypass not supported. */
        chrusHalCfg->cfgMode = VPSHAL_CHRUS_CFGMODE_B;
    }
    else
    {
        /* YUV420 data to CHR_US and DEI is in deinterlacing mode or
         * in interlaced bypass mode. Progressive bypass not supported. */
        chrusHalCfg->cfgMode = VPSHAL_CHRUS_CFGMODE_A;
    }

    return (retVal);
}

/**
 *  vcoreVpeSetDeiHalCfg
 *  \brief Sets the DEI HAL configuration based on params set.
 */
static Int32 vcoreVpeSetDeiHalCfg(const Vcore_VpeInstObj *instObj,
                                  Vcore_VpeChObj         *chObj)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DeiConfig *deiHalCfg;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    deiHalCfg        = &chObj->deiHalCfg;
    deiHalCfg->width = (UInt16) chObj->corePrms.frameWidth;

    /* When in interlaced bypass display mode, input size is in
     * terms of frame size but DEI needs field size, so dividing
     * input size by 2. */
    deiHalCfg->height = (UInt16) chObj->corePrms.frameHeight;

    if (FVID2_SF_INTERLACED == chObj->corePrms.fmt.scanFormat)
    {
        deiHalCfg->scanFormat = FVID2_SF_INTERLACED;
    }
    else
    {
        deiHalCfg->scanFormat = FVID2_SF_PROGRESSIVE;
    }
    deiHalCfg->bypass     = chObj->corePrms.deiCfg.bypass;
    deiHalCfg->fieldFlush = (UInt32) TRUE;

    /* Configure default values for MDT params */
    deiHalCfg->mdt.spatMaxBypass = chObj->corePrms.deiCfg.spatMaxBypass;
    deiHalCfg->mdt.tempMaxBypass = chObj->corePrms.deiCfg.tempMaxBypass;

    /* Configure default values for EDI params */
    deiHalCfg->edi.inpMode             = chObj->corePrms.deiCfg.inpMode;
    deiHalCfg->edi.tempInpEnable       = chObj->corePrms.deiCfg.tempInpEnable;
    deiHalCfg->edi.tempInpChromaEnable =
        chObj->corePrms.deiCfg.tempInpChromaEnable;

    /* Configure default values for FMD params */
    deiHalCfg->fmd.filmMode   = (UInt32) FALSE;
    deiHalCfg->fmd.bed        = (UInt32) TRUE;
    deiHalCfg->fmd.window     = (UInt32) FALSE;
    deiHalCfg->fmd.lock       = (UInt32) FALSE;
    deiHalCfg->fmd.jamDir     = VPS_DEI_FMDJAMDIR_PREV_FLD;
    deiHalCfg->fmd.windowMinx = 0U;
    deiHalCfg->fmd.windowMiny = 0U;
    deiHalCfg->fmd.windowMaxx = (UInt16) (chObj->corePrms.frameWidth - 1U);
    /* Since deiHalCfg->height is already calculated depending on
     * the scanFormat, using this height here for fmd window configuration */
    deiHalCfg->fmd.windowMaxy = (UInt16) (deiHalCfg->height - 1U);

    return (retVal);
}

/**
 *  vcoreVpeSetScHalCfg
 *  \brief Sets the Scaler HAL configuration based on params set.
 */
static Int32 vcoreVpeSetScHalCfg(const Vcore_VpeInstObj *instObj,
                                 Vcore_VpeChObj         *chObj)
{
    Int32 retVal = BSP_SOK;
    Vps_ScConfig         *scHalCfg;
    Vps_ScAdvConfig      *scHalAdvCfg;
    VpsHal_ScFactorConfig scFactorConfig;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != instObj);
    GT_assert(VpsVpeCoreTrace, NULL != chObj);

    scHalCfg         = &chObj->scHalCfg;
    scHalAdvCfg      = &chObj->scHalAdvCfg;
    scHalCfg->advCfg = scHalAdvCfg;

    scHalCfg->bypass           = chObj->corePrms.scCfg.bypass;
    scHalCfg->nonLinear        = chObj->corePrms.scCfg.nonLinear;
    scHalCfg->stripSize        = chObj->corePrms.scCfg.stripSize;
    scHalCfg->enableEdgeDetect = chObj->corePrms.scCfg.enableEdgeDetect;
    scHalCfg->enablePeaking    = chObj->corePrms.scCfg.enablePeaking;

    if (NULL != chObj->corePrms.scCfg.advCfg)
    {
        BspUtils_memcpy(
            scHalAdvCfg,
            chObj->corePrms.scCfg.advCfg,
            sizeof (Vps_ScAdvConfig));
    }
    else
    {
        /* Fill the SC advance config if user did not provide */
        scHalAdvCfg->tarWidth   = chObj->corePrms.tarWidth;
        scHalAdvCfg->tarHeight  = chObj->corePrms.tarHeight;
        scHalAdvCfg->srcWidth   = chObj->corePrms.frameWidth;
        scHalAdvCfg->cropStartX = chObj->corePrms.cropCfg.cropStartX;
        scHalAdvCfg->cropStartY = chObj->corePrms.cropCfg.cropStartY;
        scHalAdvCfg->cropWidth  = chObj->corePrms.cropCfg.cropWidth;
        scHalAdvCfg->cropHeight = chObj->corePrms.cropCfg.cropHeight;
        if (TRUE == chObj->ctxInfo.isDeinterlacing)
        {
            /* When deinterlacing input to scaler will be twice that of DEI */
            scHalAdvCfg->srcHeight   = chObj->corePrms.frameHeight * 2U;
            scHalAdvCfg->inFrameMode = FVID2_SF_PROGRESSIVE;
        }
        else
        {
            /* When in interlaced bypass display mode, input size is in
             * terms of frame size but DEI needs field size, so dividing
             * input size by 2. */
            scHalAdvCfg->srcHeight = chObj->corePrms.frameHeight;

            if (FVID2_SF_INTERLACED == chObj->corePrms.fmt.scanFormat)
            {
                scHalAdvCfg->inFrameMode = FVID2_SF_INTERLACED;
            }
            else
            {
                scHalAdvCfg->inFrameMode = FVID2_SF_PROGRESSIVE;
            }
        }

        if (FVID2_SF_INTERLACED == chObj->corePrms.secScanFmt)
        {
            scHalAdvCfg->outFrameMode = FVID2_SF_INTERLACED;
        }
        else
        {
            scHalAdvCfg->outFrameMode = FVID2_SF_PROGRESSIVE;
        }
        scHalAdvCfg->fidPol        = FVID2_FIDPOL_NORMAL;
        scHalAdvCfg->selfGenFid    = VPS_SC_SELF_GEN_FID_DISABLE;
        scHalAdvCfg->biLinIntpType = VPS_SC_BINTP_MODIFIED;
        scHalAdvCfg->defConfFactor = 0U;
        scHalAdvCfg->edgeDetectCfg = NULL;
        scHalAdvCfg->peakingCfg    = NULL;
        scHalAdvCfg->phInfoMode    = VPS_SC_SET_PHASE_INFO_DEFAULT;

        /* Init to auto so that the hal calculates proper and gives back */
        scHalAdvCfg->hsDcmType   = VPS_SC_HST_DCM_AUTO;
        scHalAdvCfg->vsType      = VPS_SC_VST_AUTO;
        scHalAdvCfg->hPolyBypass = (UInt32) FALSE;

        /* Update hsType and vsType based on scaling ratio */
        VpsHal_scGetScFactorConfig(
            instObj->halHandle[VCORE_VPE_SC_IDX],
            &chObj->scHalCfg,
            &scFactorConfig);

        scHalAdvCfg->hsDcmType   = scFactorConfig.hsDcmType;
        scHalAdvCfg->hPolyBypass = scFactorConfig.hPolyBypass;
        scHalAdvCfg->vsType      = scFactorConfig.vsType;
    }

    return (retVal);
}

/**
 *  vcoreVpeSetRangMapRedtCfgIoctl
 *  \brief Writes the Range Mapping and Range Reduction configuration.
 */
Int32 vcoreVpeSetRangMapRedtCfgIoctl(Vcore_VpeHandleObj     *hObj,
                                     const Vps_RngMapRdtCfg *rngMapRdtCfg)
{
    Int32 retVal = BSP_EFAIL;
/* TODO */
#if 0
    Vcore_VpeInstObj        *instObj;
    VpsHal_VpsRangeMapConfig rngMapconfig;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != rngMapRdtCfg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    if (instObj->instId == VCORE_VPE_INST_PRI)
    {
        rngMapconfig.src = VPSHAL_VPS_RANGE_CONVERT_SRC_PRI;
    }
    else
    {
        rngMapconfig.src = VPSHAL_VPS_RANGE_CONVERT_SRC_AUX;
    }

    rngMapconfig.isEnabled = rngMapRdtCfg->rngMapEnable;

    if (rngMapRdtCfg->rngMapEnable == TRUE)
    {
        rngMapconfig.lumaValue = (VpsHal_VpsRangeMapValue)
                                 rngMapRdtCfg->rngMapValY;
        rngMapconfig.chromaValue = (VpsHal_VpsRangeMapValue)
                                   rngMapRdtCfg->rngMapValUV;
    }

    retVal = VpsHal_vpsSetRangeMapConfig(&rngMapconfig, NULL);

    retVal += VpsHal_vpsSetRangeReductionConfig(rngMapconfig.src,
                                                rngMapRdtCfg->rngRdtEnable,
                                                NULL);
#endif

    return (retVal);
}

/**
 *  vcoreVpeGetRangMapRedtCfgIoctl
 *  \brief Reads the and Range Reduction configuration.
 */
Int32 vcoreVpeGetRangMapRedtCfgIoctl(Vcore_VpeHandleObj *hObj,
                                     Vps_RngMapRdtCfg   *rngMapRdtCfg)
{
    Int32 retVal = BSP_EFAIL;
/* TODO */
#if 0
    Vcore_VpeInstObj *instObj;
    VpsHal_VpsRangeMapConfig rngMapconfig;

    /* NULL pointer check */
    GT_assert(VpsVpeCoreTrace, NULL != hObj);
    GT_assert(VpsVpeCoreTrace, NULL != rngMapRdtCfg);
    instObj = hObj->instObj;
    GT_assert(VpsVpeCoreTrace, NULL != instObj);

    if (instObj->instId == VCORE_VPE_INST_PRI)
    {
        rngMapconfig.src = VPSHAL_VPS_RANGE_CONVERT_SRC_PRI;
    }
    else
    {
        rngMapconfig.src = VPSHAL_VPS_RANGE_CONVERT_SRC_AUX;
    }

    retVal = VpsHal_vpsGetRangeReductionConfig(rngMapconfig.src,
                                               rngMapRdtCfg);
    retVal += VpsHal_vpsGetRangeMapConfig(rngMapconfig.src,
                                          rngMapRdtCfg);
#endif

    return (retVal);
}

