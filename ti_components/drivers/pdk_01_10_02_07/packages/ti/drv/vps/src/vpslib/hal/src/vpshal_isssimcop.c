/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpshal_isssimcop.c
 *
 *  \brief File containing the implementation of SIMCOP functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isssimcop.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Wait cycles required before flagging simcop reset failure. */
#define SIMCOP_RESET_TIMEOUT        (0xFFFFU)
/** \brief Wait cycles required before flagging simcop dma reset failure. */
#define SIMCOP_DMA_RESET_TIMEOUT    (0xFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief Defines a local enum used to demonstrate coding guidelines for
 *         StarterWare
 */
typedef struct isshalsimcopObj
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalsimcopInstId. */
    uint32_t simcopBaseAddress;
    /**< BaseAddress of the SIMCOP module */
    uint32_t simcopDmaBaseAddress;
    /**< BaseAddress of the SIMCOP DMA module */
    uint32_t numIrq;
    /**< Number of IRQ lines supproted by SIMCOP Module */
    uint32_t maxHwSeqSteps;
    /**< Maximum number of hwSeq steps supported */

    uint32_t imgBufMap[ISSHAL_SIMCOP_HWSEQ_MAX_IMG_BUF]
    [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAX_PORT];
    /**< Image Buffer Mapping table */
} isshalsimcopObj_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

int32_t HwSeqSetStepCfg(
    VpsHal_Handle                        handle,
    uint32_t                             stepNum,
    const isshalsimcopHwSeqStepParams_t *stepCfg);

static int32_t SimcopResetDma(VpsHal_Handle handle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines a static global information for the module. */
static isshalsimcopObj_t gSimcopObj[ISSHAL_SIMCOP_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_isssimcopInit(UInt32                          numInst,
                             const isshalsimcopInstParams_t *instPrms,
                             Ptr                             arg)
{
    VpsHal_Handle handle;
    uint32_t      i;
    GT_assert(VpsHalTrace, (NULL != instPrms));
    GT_assert(VpsHalTrace, (ISSHAL_SIMCOP_MAX_INST >= numInst));

    for(i = 0U; i < numInst; i++)
    {
        handle = (VpsHal_Handle) (&gSimcopObj[i]);
        /* Initialize base addresses and other init parameters */
        gSimcopObj[i].simcopBaseAddress    = instPrms->simcopBaseAddress;
        gSimcopObj[i].simcopDmaBaseAddress = instPrms->simcopDmaBaseAddress;
        gSimcopObj[i].numIrq               = instPrms->numIrq;
        gSimcopObj[i].maxHwSeqSteps        = instPrms->maxHwSeqSteps;

        /* Soft Reset the Simcop */
        VpsHal_isssimcopReset(handle);

        /* Enable all modules */
        VpsHal_isssimcopEnableModule(handle, ISSHAL_SIMCOP_MODULE_DMA,
                                     (uint32_t)TRUE);
        VpsHal_isssimcopEnableModule(handle, ISSHAL_SIMCOP_MODULE_LDC,
                                     (uint32_t)TRUE);
        VpsHal_isssimcopEnableModule(handle, ISSHAL_SIMCOP_MODULE_VTNF,
                                     (uint32_t)TRUE);

        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_COPROC_BUS] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_COPR;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_DMA;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_LDC_O;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_VTNF_IO;

        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_COPROC_BUS] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_COPR;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_DMA;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_LDC_O;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_VTNF_IO;

        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_COPROC_BUS] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_COPR;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_DMA;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_LDC_O;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_VTNF_IO;

        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_COPROC_BUS] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_COPR;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_DMA;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_LDC_O;
        gSimcopObj[i].imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H]
        [ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO] =
            SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_VTNF_IO;
    }

    return (FVID2_SOK);
}

int32_t VpsHal_isssimcopDeInit(VpsHal_Handle handle, Ptr arg)
{
    int32_t status;
    /* Disable all modules */
    /* No s/w book keep required. Next call should be INIT */
    status = VpsHal_isssimcopEnableModule(handle, ISSHAL_SIMCOP_MODULE_VTNF,
                                          (uint32_t) FALSE);
    GT_assert(VpsHalTrace, (FVID2_SOK == status));
    status = VpsHal_isssimcopEnableModule(handle, ISSHAL_SIMCOP_MODULE_LDC,
                                          (uint32_t) FALSE);
    GT_assert(VpsHalTrace, (FVID2_SOK == status));

    status = SimcopResetDma(handle);
    if(FVID2_SOK == status)
    {
        status = VpsHal_isssimcopReset(handle);
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_isssimcopEnableModule(handle, ISSHAL_SIMCOP_MODULE_DMA,
                                              (uint32_t) FALSE);
        GT_assert(VpsHalTrace, (FVID2_SOK == status));
    }
    return (status);
}

VpsHal_Handle VpsHal_isssimcopOpen(
    const isshalsimcopOpenParams_t *instPrms,
    Ptr                             arg)
{
    GT_assert(VpsHalTrace, (NULL != instPrms));
    GT_assert(VpsHalTrace, (ISSHAL_SIMCOP_INST_MAX_ID > instPrms->instId));

    return ((VpsHal_Handle) (&(gSimcopObj[instPrms->instId])));
}

int32_t VpsHal_isssimcopClose(VpsHal_Handle handle)
{
    /* What would you close - I guess this function is completed :) */
    return BSP_SOK;
}

int32_t VpsHal_isssimcopEnableModule(VpsHal_Handle        handle,
                                     isshalsimcopModule_t module,
                                     uint32_t             flag)
{
    int32_t            status = FVID2_SOK;
    uint32_t           regVal, mask;
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    switch(module)
    {
        case ISSHAL_SIMCOP_MODULE_DMA:
            mask = SIMCOP_CLKCTRL_DMA_MASK;
            break;
        case ISSHAL_SIMCOP_MODULE_LDC:
            mask = SIMCOP_CLKCTRL_LDC_MASK;
            break;
        case ISSHAL_SIMCOP_MODULE_VTNF:
            mask = SIMCOP_CLKCTRL_VTNF_MASK;
            break;
        default:
            status = FVID2_EINVALID_PARAMS;
            break;
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_CLKCTRL);

        if((uint32_t)TRUE == flag)
        {
            regVal |= mask;
        }
        else /* Disable the module */
        {
            regVal &= ~mask;
        }

        HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_CLKCTRL, regVal);

        BspOsal_sleep(1U);
    }

    /* Enable internal memories of LDC - no need to disable */
    if((FVID2_SOK == status) && (SIMCOP_CLKCTRL_LDC_MASK == mask))
    {
        HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL,
                    HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL) |
                    ((((UInt32) SIMCOP_CTRL_LDC_INPUT_PRIVATE) <<
                      SIMCOP_CTRL_LDC_INPUT_SHIFT) &
                     SIMCOP_CTRL_LDC_INPUT_MASK));
    }

    return (status);
}

int32_t VpsHal_isssimcopReset(VpsHal_Handle handle)
{
    int32_t            status = FVID2_SOK;
    uint32_t           regVal;
    uint32_t           tempCnt;
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    /* Assert the reset */
    regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_HL_SYSCONFIG);
    regVal = regVal | SIMCOP_HL_SYSCONFIG_SOFTRESET_MASK;
    HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_HL_SYSCONFIG, regVal);

    regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_HL_SYSCONFIG);

    /* Waits until reset is done */
    tempCnt = SIMCOP_RESET_TIMEOUT;
    while((0x0U != tempCnt) &&
          ((regVal & SIMCOP_HL_SYSCONFIG_SOFTRESET_PENDING) !=
           SIMCOP_HL_SYSCONFIG_SOFTRESET_DONE))
    {
        tempCnt--;
        regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_HL_SYSCONFIG);
    }

    if(0x0U == tempCnt)
    {
        GT_assert(VpsHalTrace, FALSE);
        status = FVID2_EFAIL;
    }

    return (status);
}

int32_t VpsHal_isssimcopSetLdcReadDmaCfg(
    VpsHal_Handle                   handle,
    uint32_t                        tagCnt,
    isshalsimcopLdcMaxBurstLength_t maxBrstLn,
    uint32_t                        enableBurstBreak)
{
    int32_t            status = FVID2_SOK;
    uint32_t           regVal;
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    if((ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_B96 == maxBrstLn) &&
       ((uint32_t)TRUE == enableBurstBreak))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL);

        regVal &= ~SIMCOP_CTRL_LDC_R_BURST_BREAK_MASK;
        if((uint32_t)TRUE == enableBurstBreak)
        {
            regVal |= SIMCOP_CTRL_LDC_R_BURST_BREAK_MASK;
        }

        regVal &= ~SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_MASK;
        regVal |= (((uint32_t) maxBrstLn) <<
                   SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_SHIFT) &
                  SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_MASK;

        regVal &= ~SIMCOP_CTRL_LDC_R_TAG_CNT_MASK;
        regVal |= (tagCnt << SIMCOP_CTRL_LDC_R_TAG_CNT_SHIFT) &
                  SIMCOP_CTRL_LDC_R_TAG_CNT_MASK;

        HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL, regVal);
    }

    return (status);
}

int32_t VpsHal_isssimcopSetIrqMode(VpsHal_Handle         handle,
                                   uint32_t              irqNum,
                                   isshalsimcopIrqMode_t irqMode)
{
    int32_t            status = FVID2_SOK;
    uint32_t           regVal;
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    if(irqNum >= simcopObj->numIrq)
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL);

        regVal &= ~((uint32_t)0x1U << (irqNum + SIMCOP_CTRL_IRQ0_MODE_SHIFT));
        if(ISSHAL_SIMCOP_IRQ_MODE_AND == irqMode)
        {
            regVal |= ((uint32_t)0x1U <<
                       (irqNum + SIMCOP_CTRL_IRQ0_MODE_SHIFT));
        }

        HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL, regVal);
    }

    return (status);
}

int32_t VpsHal_isssimcopSetLdcReadBwCtrl(VpsHal_Handle handle,
                                         uint32_t      bwLimit)
{
    int32_t status = FVID2_SOK;
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    if(bwLimit > SIMCOP_CTRL2_LDCR_BW_CTRL_MASK)
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_CTRL2,
                    (bwLimit << SIMCOP_CTRL2_LDCR_BW_CTRL_SHIFT) &
                    SIMCOP_CTRL2_LDCR_BW_CTRL_MASK);
    }

    return (status);
}

int32_t VpsHal_isssimcopHwSeqSetConfig(
    VpsHal_Handle handle,
    const isshalsimcopHwSeqParams_t *
    hwSeqCfg)
{
    int32_t            status = FVID2_SOK;
    uint32_t           regVal;
    uint32_t           stepCnt;
    uint32_t           stepNum;
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    /* Error checking */
    GT_assert(VpsHalTrace, (NULL != hwSeqCfg));

    if(1U == hwSeqCfg->useHwSeq)
    {
        if((0U == hwSeqCfg->stepCnt) ||
           (0U == hwSeqCfg->numSteps))
        {
            status = FVID2_EINVALID_PARAMS;
        }

        if((hwSeqCfg->startStep >= simcopObj->maxHwSeqSteps) ||
           (hwSeqCfg->numSteps > simcopObj->maxHwSeqSteps))
        {
            status = FVID2_EINVALID_PARAMS;
        }

        for(stepCnt = 0U; stepCnt < hwSeqCfg->numSteps; stepCnt++)
        {
            if(hwSeqCfg->stepParams[stepCnt].nextStep >=
               simcopObj->maxHwSeqSteps)
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_CTRL);

        regVal &= ~((UInt32) SIMCOP_HWSEQ_CTRL_STEP_MASK);
        regVal &= ~SIMCOP_HWSEQ_CTRL_HW_SEQ_STEP_COUNTER_MASK;
        if(1U == hwSeqCfg->useHwSeq)
        {
            regVal |= (hwSeqCfg->stepCnt <<
                       SIMCOP_HWSEQ_CTRL_HW_SEQ_STEP_COUNTER_SHIFT) &
                      SIMCOP_HWSEQ_CTRL_HW_SEQ_STEP_COUNTER_MASK;

            regVal |= (hwSeqCfg->startStep << SIMCOP_HWSEQ_CTRL_STEP_SHIFT) &
                      SIMCOP_HWSEQ_CTRL_STEP_MASK;
        }

        HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_CTRL, regVal);

        stepNum = hwSeqCfg->startStep;
        for(stepCnt = 0U; stepCnt < hwSeqCfg->numSteps; stepCnt++)
        {
            HwSeqSetStepCfg(handle, stepNum, &hwSeqCfg->stepParams[stepCnt]);
            stepNum = hwSeqCfg->stepParams[stepCnt].nextStep;
        }
    }

    return (status);
}

int32_t VpsHal_isssimcopHwSeqStart(VpsHal_Handle handle)
{
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_CTRL,
                HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_CTRL) |
                SIMCOP_HWSEQ_CTRL_HW_SEQ_START_MASK);

    return (FVID2_SOK);
}

int32_t VpsHal_isssimcopHwSeqStop(VpsHal_Handle handle)
{
    isshalsimcopObj_t *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_CTRL,
                HW_RD_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_CTRL) |
                SIMCOP_HWSEQ_CTRL_HW_SEQ_STOP_MASK);

    return (FVID2_SOK);
}

/**
 *  VpsHal_isssimcopDmaSetChannelConfig
 *  \brief Configure DMA parameters for specified SIMCOP instance and
 *         specified channel
 *
 *  \param handle      Valid SIMCOP HAL handle returned by
 *                     VpsHal_isssimcopOpen
 *  \param cfg         DMA channel configuration #isshalsimcopDmaChannelParams_t
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsHal_isssimcopDmaSetChannelConfig(
    VpsHal_Handle                         handle,
    const isshalsimcopDmaChannelParams_t *cfg)
{
    isshalsimcopObj_t *simcopObj;
    uint32_t           ch, regVal;

    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));
    simcopObj = (isshalsimcopObj_t *) handle;
    ch        = cfg->channelNum;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for  setting memory
     * mapped register
     */
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_SMEM_ADDR(ch),
                ((uint32_t)cfg->sysmemAddr +
                 (cfg->initX * (cfg->blkWidth << 4U)) +
                 (cfg->initY * cfg->blkHeight * cfg->sysmemStride)));

    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_SMEM_OFST(ch),
                (cfg->sysmemStride & ISS_SIMCOP_DMA_CHAN_SMEM_OFST_MASK));

    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_BUF_OFST(ch),
                (cfg->simcopmemStride & ISS_SIMCOP_DMA_CHAN_BUF_OFST_MASK));

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for  setting memory
     * mapped register
     */
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_BUF_ADDR(ch), cfg->simcopmemAddr);

    regVal  = 0;
    regVal |= ((cfg->blkWidth << ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_XNUM_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_XNUM_MASK);
    regVal |= ((cfg->blkHeight << ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_YNUM_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_YNUM_MASK);
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE(ch), regVal);

    regVal  = 0;
    regVal |= ((cfg->numHorzBlks << ISS_SIMCOP_DMA_CHAN_FRAME_XCNT_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_FRAME_XCNT_MASK);
    regVal |= ((cfg->numVertBlks << ISS_SIMCOP_DMA_CHAN_FRAME_YCNT_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_FRAME_YCNT_MASK);
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_FRAME(ch), regVal);

    regVal  = 0;
    regVal |= ((cfg->horzStep << ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_XSTEP_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_XSTEP_MASK);
    regVal |= ((cfg->vertStep << ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_YSTEP_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_YSTEP_MASK);
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_BLOCK_STEP(ch), regVal);

    regVal  = 0;
    regVal |= ((cfg->hwStopChCtrl << ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_MASK);
    regVal |= ((cfg->hwStartChCtrl << ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_MASK);
    regVal |= ((cfg->nextChannel << ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_MASK);
    regVal |= ((cfg->direction << ISS_SIMCOP_DMA_CHAN_CTRL_DIR_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_CTRL_DIR_MASK);
    regVal |= (((uint32_t)TRUE << ISS_SIMCOP_DMA_CHAN_CTRL_ENABLE_SHIFT) &
               ISS_SIMCOP_DMA_CHAN_CTRL_ENABLE_MASK);
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress +
                ISS_SIMCOP_DMA_CHAN_CTRL(ch), regVal);

    return BSP_SOK;
}

int32_t VpsHal_isssimcopCfgDma(uint32_t                           instId,
                               const vpsisssimcopDmaCtrlParams_t *pInstDmaCfg)
{
    volatile uint32_t regVal;
    register uint32_t dmaBaseAddr;

    int32_t           status = BSP_EBADARGS;
    if((ISSHAL_SIMCOP_MAX_INST > instId) && (NULL != pInstDmaCfg))
    {
        dmaBaseAddr = gSimcopObj[instId].simcopDmaBaseAddress;

        regVal  = HW_RD_REG32(dmaBaseAddr + ISS_SIMCOP_DMA_CTRL);
        regVal &= ~(ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_MASK |
                    ISS_SIMCOP_DMA_CTRL_POSTED_WRITES_MASK |
                    ISS_SIMCOP_DMA_CTRL_TAG_CNT_MASK |
                    ISS_SIMCOP_DMA_CTRL_BW_LIMITER_MASK);

        regVal |= ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_MASK &
                  pInstDmaCfg->maxBurstSize;

        regVal |= ISS_SIMCOP_DMA_CTRL_POSTED_WRITES_MASK &
                  (pInstDmaCfg->enablePostedWrite <<
                   ISS_SIMCOP_DMA_CTRL_POSTED_WRITES_SHIFT);

        regVal |= ISS_SIMCOP_DMA_CTRL_TAG_CNT_MASK &
                  (pInstDmaCfg->tagCnt <<
                   ISS_SIMCOP_DMA_CTRL_TAG_CNT_SHIFT);

        regVal |= ISS_SIMCOP_DMA_CTRL_BW_LIMITER_MASK &
                  (pInstDmaCfg->bwLimit <<
                   ISS_SIMCOP_DMA_CTRL_BW_LIMITER_SHIFT);
        HW_WR_REG32(dmaBaseAddr + ISS_SIMCOP_DMA_CTRL, regVal);

        status = BSP_SOK;
    }

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

int32_t HwSeqSetStepCfg(VpsHal_Handle                        handle,
                        uint32_t                             stepNum,
                        const isshalsimcopHwSeqStepParams_t *stepCfg)
{
    uint32_t regVal;
    isshalsimcopHwSeqImgBufMap_t imgbufMap;
    isshalsimcopObj_t           *simcopObj;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    GT_assert(VpsHalTrace, (NULL != stepCfg));

    regVal = HW_RD_REG32(simcopObj->simcopBaseAddress +
                         SIMCOP_HWSEQ_STEP_CTRL(stepNum));

    regVal &= ~SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_MASK;
    regVal |= (((uint32_t) stepCfg->dmaOfst) <<
               SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_SHIFT) &
              SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_MASK;

    regVal &= ~((UInt32) SIMCOP_HWSEQ_STEP_CTRL_NEXT_MASK);
    regVal |= (((uint32_t) stepCfg->nextStep) <<
               SIMCOP_HWSEQ_STEP_CTRL_NEXT_SHIFT) &
              SIMCOP_HWSEQ_STEP_CTRL_NEXT_MASK;

    regVal &= ~((UInt32) SIMCOP_HWSEQ_STEP_CTRL_VTNF_SYNC_MASK);
    if(1U == stepCfg->enableVtnfSync)
    {
        regVal |= SIMCOP_HWSEQ_STEP_CTRL_VTNF_SYNC_MASK;
    }

    regVal &= ~((UInt32) SIMCOP_HWSEQ_STEP_CTRL_LDC_SYNC_MASK);
    if(1U == stepCfg->enableLdcSync)
    {
        regVal |= SIMCOP_HWSEQ_STEP_CTRL_LDC_SYNC_MASK;
    }

    regVal &= ~((UInt32) SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_MASK);
    regVal |= (((uint32_t) stepCfg->dmaSync) <<
               SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_SHIFT) &
              SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_MASK;

    HW_WR_REG32(simcopObj->simcopBaseAddress + SIMCOP_HWSEQ_STEP_CTRL(stepNum),
                regVal);

    regVal = HW_RD_REG32(simcopObj->simcopBaseAddress +
                         SIMCOP_HWSEQ_STEP_SWITCH(stepNum));

    regVal   &= ~SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_MASK;
    imgbufMap = stepCfg->imgMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E];
    regVal   |= simcopObj->imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_E][imgbufMap];

    regVal   &= ~SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_MASK;
    imgbufMap = stepCfg->imgMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F];
    regVal   |= simcopObj->imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_F][imgbufMap];

    regVal   &= ~SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_MASK;
    imgbufMap = stepCfg->imgMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G];
    regVal   |= simcopObj->imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_G][imgbufMap];

    regVal   &= ~SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_MASK;
    imgbufMap = stepCfg->imgMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H];
    regVal   |= simcopObj->imgBufMap[ISSHAL_SIMCOP_HWSEQ_IMG_BUF_H][imgbufMap];

    HW_WR_REG32(simcopObj->simcopBaseAddress +
                SIMCOP_HWSEQ_STEP_SWITCH(stepNum),
                regVal);

    regVal = HW_RD_REG32(simcopObj->simcopBaseAddress +
                         SIMCOP_HWSEQ_STEP_CTRL2(stepNum));

    regVal &= ~((UInt32) SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_MASK);
    regVal |= (((uint32_t) stepCfg->vtnfImBufMap) <<
               SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_SHIFT) &
              SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_MASK;

    regVal &= ~((UInt32) SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_MASK);
    regVal |= (((uint32_t) stepCfg->ldcImBufMap) <<
               SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_SHIFT) &
              SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_MASK;

    HW_WR_REG32(simcopObj->simcopBaseAddress +
                SIMCOP_HWSEQ_STEP_CTRL2(stepNum),
                regVal);

    return (FVID2_SOK);
}

static int32_t SimcopResetDma(VpsHal_Handle handle)
{
    isshalsimcopObj_t *simcopObj;
    uint32_t           regVal, timeOut;
    int32_t status = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != handle));
    simcopObj = (isshalsimcopObj_t *) handle;

    regVal = HW_RD_REG32(
        simcopObj->simcopDmaBaseAddress + ISS_SIMCOP_DMA_SYSCONFIG);
    regVal |= ISS_SIMCOP_DMA_SYSCONFIG_RESET_MASK;
    HW_WR_REG32(simcopObj->simcopDmaBaseAddress + ISS_SIMCOP_DMA_SYSCONFIG,
                regVal);

    /* Wait for reset to complete */
    timeOut = SIMCOP_DMA_RESET_TIMEOUT;
    while( ((uint32_t)0x0U != timeOut) &&
           (ISS_SIMCOP_DMA_SYSCONFIG_RESET_MASK ==
            (regVal & ISS_SIMCOP_DMA_SYSCONFIG_RESET_MASK)))
    {
        regVal = HW_RD_REG32(
            simcopObj->simcopBaseAddress + ISS_SIMCOP_DMA_SYSCONFIG);
        timeOut--;
    }

    if((uint32_t)0x0U != timeOut)
    {
        status = FVID2_SOK;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    return (status);
}

