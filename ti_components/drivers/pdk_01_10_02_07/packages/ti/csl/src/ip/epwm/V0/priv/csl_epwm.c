/*
 *  Copyright (C) 2017 Texas Instruments Incorporated.
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
 *
 */

/**
 *  \file   csl_epwm.c
 *
 *  \brief  This file contains the CSL layer APIs for EPWM.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_epwm.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief Enable clocks to epwm sub-module inside the pwm sub system. */
#define PWMSS_CLK_CFG_EPWM_CLK_ENABLE   (0x1U)

/** \brief Disable clocks to epwm sub-module inside the pwm sub system. */
#define PWMSS_CLK_CFG_EPWM_CLK_STOP     (0x1U)

/** \brief Time base clock high speed clock divider value 14. */
#define EPWM_TBCTL_HSPCLKDIV_14         (0x000EU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CSL_epwmTbTimebaseClkCfg(uint32_t baseAddr,
                              uint32_t tbClk,
                              uint32_t moduleClk)
{
    uint32_t clkDiv = (moduleClk / tbClk);
    uint32_t hspClkDiv = 0U;
    uint32_t lspClkDiv = 0U;
    uint32_t lspClkDivSetting = 0U;
    uint32_t regVal = 0U;

    if (clkDiv > EPWM_TBCTL_HSPCLKDIV_14)
    {
        /* High speed Time-base clock pre scale value */
        hspClkDiv = PWMSS_EPWM_TBCTL_HSPCLKDIV_DIV_14;
        /* Time-base clock pre scale value */
        lspClkDiv = clkDiv/EPWM_TBCTL_HSPCLKDIV_14;

        while(lspClkDiv > 1U)
        {
           lspClkDiv = lspClkDiv >> 1U;
           lspClkDivSetting++;
        }
    }
    else
    {
        /* High speed Time-base clock pre scale value */
        hspClkDiv = clkDiv / 2U;
        /* divide by 1 */
        lspClkDivSetting = PWMSS_EPWM_TBCTL_HSPCLKDIV_DIV_1;
    }

    regVal = HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_TBCTL_CLKDIV, lspClkDivSetting);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_TBCTL_HSPCLKDIV, hspClkDiv);
    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        (uint16_t)regVal);
}


void CSL_epwmTbPwmFreqCfg(uint32_t baseAddr,
                          uint32_t tbClk,
                          uint32_t pwmFreq,
                          uint32_t counterDir,
                          uint32_t enableShadowWrite)
{
    uint32_t tbPeriodCount = tbClk / pwmFreq;
    uint32_t regVal = 0U;

    regVal = HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_TBCTL_PRDLD, enableShadowWrite);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_TBCTL_CTRMODE, counterDir);
    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        (uint16_t)regVal);

    if (CSL_EPWM_TB_COUNTER_DIR_UP_DOWN == counterDir)
    {
        regVal = tbPeriodCount / ((uint32_t) 2U);
    }
    else
    {
        regVal = tbPeriodCount - ((uint32_t) 1U);
    }
    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBPRD),
        (uint16_t)regVal);
}


void CSL_epwmTbSyncEnable(uint32_t baseAddr,
                          uint32_t tbPhsValue,
                          uint32_t counterDir)
{
    /* counter direction configuration. */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        PWMSS_EPWM_TBCTL_PHSDIR, (uint16_t)counterDir);

    /* phase value configuration */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBPHS),
        PWMSS_EPWM_TBPHS, (uint16_t)tbPhsValue);

    /* Enable sync: Load time base counter with phase register value. */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        PWMSS_EPWM_TBCTL_PHSEN, (uint16_t)PWMSS_EPWM_TBCTL_PHSEN_LOAD);
}


void CSL_epwmTbSyncDisable(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        PWMSS_EPWM_TBCTL_PHSEN, (uint16_t)PWMSS_EPWM_TBCTL_PHSEN_DO_NOT_LOAD);
}


void CSL_epwmTbSetSyncOutMode(uint32_t baseAddr, uint32_t syncOutMode)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        PWMSS_EPWM_TBCTL_SYNCOSEL, (uint16_t)syncOutMode);
}


void CSL_epwmTbTriggerSwSync(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        PWMSS_EPWM_TBCTL_SWFSYNC,
        (uint16_t)PWMSS_EPWM_TBCTL_SWFSYNC_FORCE_SYNC);
}


void CSL_epwmTbWriteTbCount(uint32_t baseAddr, uint32_t tbCount)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCNT),
        PWMSS_EPWM_TBCNT, (uint16_t)tbCount);
}


uint16_t CSL_epwmTbReadTbCount(uint32_t baseAddr)
{
    return (HW_RD_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCNT),
        PWMSS_EPWM_TBCNT));
}


uint16_t CSL_epwmTbGetStatus(uint32_t baseAddr, uint32_t tbStatusMask)
{
    return ((HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBSTS)) &
        ((uint16_t)tbStatusMask));
}


void CSL_epwmTbStatusClear(uint32_t baseAddr, uint32_t tbStatusClrMask)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBSTS);
    regVal |= ((tbStatusClrMask) & (PWMSS_EPWM_TBSTS_CTRMAX_MASK |
        PWMSS_EPWM_TBSTS_SYNCI_MASK));

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBSTS),
        (uint16_t)regVal);
}


void CSL_epwmTbSetEmulationMode(uint32_t baseAddr, uint32_t mode)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBCTL),
        PWMSS_EPWM_TBCTL_FREE_SOFT, (uint16_t)mode);
}


uint32_t CSL_epwmCounterComparatorCfg(uint32_t baseAddr,
                                      uint32_t cmpType,
                                      uint32_t cmpVal,
                                      uint32_t enableShadowWrite,
                                      uint32_t shadowToActiveLoadTrigger,
                                      uint32_t overwriteShadow)
{
    uint32_t status = FALSE;
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_CMPCTL);

    if (CSL_EPWM_CC_CMP_A == cmpType)
    {
        if ((TRUE == overwriteShadow) ||
            (PWMSS_EPWM_CMPCTL_SHDWAFULL_FIFO_NOT_FULL ==
                HW_GET_FIELD(regVal, PWMSS_EPWM_CMPCTL_SHDWAFULL)))
        {
            HW_SET_FIELD32(regVal,
                PWMSS_EPWM_CMPCTL_SHDWAMODE, enableShadowWrite);
            HW_SET_FIELD32(regVal, PWMSS_EPWM_CMPCTL_LOADAMODE,
                shadowToActiveLoadTrigger);
            HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_CMPCTL),
                (uint16_t)regVal);

            HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_CMPA),
                PWMSS_EPWM_CMPA, (uint16_t)cmpVal);

            status = TRUE;
        }
    }
    else if (CSL_EPWM_CC_CMP_B == cmpType)
    {
        if ((TRUE == overwriteShadow) ||
            (PWMSS_EPWM_CMPCTL_SHDWBFULL_FIFO_NOT_FULL ==
                HW_GET_FIELD(regVal, PWMSS_EPWM_CMPCTL_SHDWBFULL)))
        {
            HW_SET_FIELD32(regVal,
                PWMSS_EPWM_CMPCTL_SHDWBMODE, enableShadowWrite);
            HW_SET_FIELD32(regVal, PWMSS_EPWM_CMPCTL_LOADBMODE,
                shadowToActiveLoadTrigger);
            HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_CMPCTL),
                (uint16_t)regVal);

            HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_CMPB),
                PWMSS_EPWM_CMPB, (uint16_t)cmpVal);

            status = TRUE;
        }
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    return status;
}


void CSL_epwmAqActionOnOutputCfg(uint32_t baseAddr,
                                 uint32_t pwmOutputCh,
                                 const CSL_EpwmAqActionCfg_t *pCfg)
{
    uint32_t regVal = 0U;

    if (CSL_EPWM_OUTPUT_CH_A == pwmOutputCh)
    {
        regVal =
            HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQCTLA);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLA_CBD, pCfg->cmpBDownAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLA_CBU, pCfg->cmpBUpAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLA_CAD, pCfg->cmpADownAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLA_CAU, pCfg->cmpAUpAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLA_PRD, pCfg->prdAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLA_ZRO, pCfg->zeroAction);
        HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQCTLA),
            (uint16_t)regVal);
    }
    else if (CSL_EPWM_OUTPUT_CH_B == pwmOutputCh)
    {
        regVal =
            HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQCTLB);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLB_CBD, pCfg->cmpBDownAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLB_CBU, pCfg->cmpBUpAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLB_CAD, pCfg->cmpADownAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLB_CAU, pCfg->cmpAUpAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLB_PRD, pCfg->prdAction);
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQCTLB_ZRO, pCfg->zeroAction);
        HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQCTLB),
            (uint16_t)regVal);
    }
    else
    {
        /* This error does not happen because of check done already */
    }
}


void CSL_epwmAqSwTriggerOneTimeAction(uint32_t baseAddr,
                                      uint32_t pwmOutputCh,
                                      uint32_t swTrigAction)
{
    uint32_t regVal = 0U;

    if (CSL_EPWM_OUTPUT_CH_A == pwmOutputCh)
    {
        regVal =
            HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQSFRC);

        /* Configure the software triggered one-time action for A channel */
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQSFRC_ACTSFA, swTrigAction);
        /* Initiate single software forced event on A channel output */
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_AQSFRC_OTSFA, PWMSS_EPWM_AQSFRC_OTSFA_SW_EVENT);

        HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQSFRC),
            (uint16_t)regVal);
    }
    else if (CSL_EPWM_OUTPUT_CH_B == pwmOutputCh)
    {
        regVal =
            HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQSFRC);

        /* Configure the software triggered one-time action for B channel */
        HW_SET_FIELD32(regVal, PWMSS_EPWM_AQSFRC_ACTSFB, swTrigAction);
        /* Initiate single software forced event on B channel output */
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_AQSFRC_OTSFB, PWMSS_EPWM_AQSFRC_OTSFB_SW_EVENT);

        HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQSFRC),
            (uint16_t)regVal);
    }
    else
    {
        /* This error does not happen because of check done already */
    }
}


void CSL_epwmAqSwTriggerContAction(uint32_t baseAddr,
                                   uint32_t pwmOutputCh,
                                   uint32_t swTrigAction,
                                   uint32_t activeRegReloadMode)
{
    /* Program AQCSFRC Active Register Reload From Shadow Options */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQSFRC),
        PWMSS_EPWM_AQSFRC_RLDCSF, (uint16_t)activeRegReloadMode);

    if (CSL_EPWM_OUTPUT_CH_A == pwmOutputCh)
    {
        /* Continuous software forced output on A */
        HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQCSFRC),
            PWMSS_EPWM_AQCSFRC_CSFA, (uint16_t)swTrigAction);
    }
    else if (CSL_EPWM_OUTPUT_CH_B == pwmOutputCh)
    {
        /* Continuous software forced output on B */
        HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_AQCSFRC),
            PWMSS_EPWM_AQCSFRC_CSFB, (uint16_t)swTrigAction);
    }
    else
    {
        /* This error does not happen because of check done already */
    }
}


void CSL_epwmDeadbandCfg(uint32_t baseAddr, const CSL_EpwmDeadbandCfg_t *pCfg)
{
    uint32_t regVal = 0U;

    /* Configure the input source for dead-band */
    regVal = HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_DBCTL);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_DBCTL_IN_MODE, pCfg->inputMode);

    /* Configure the output mode */
    HW_SET_FIELD32(regVal, PWMSS_EPWM_DBCTL_OUT_MODE, pCfg->outputMode);

    /* Configure the polarity selection */
    HW_SET_FIELD32(regVal, PWMSS_EPWM_DBCTL_POLSEL, pCfg->polaritySelect);
    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_DBCTL),
        (uint16_t)regVal);

    /* Configure rising edge delay */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_DBRED),
        PWMSS_EPWM_DBRED_DEL, (uint16_t)pCfg->risingEdgeDelay);

    /* Configure falling edge delay */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_DBFED),
        PWMSS_EPWM_DBFED_DEL, (uint16_t)pCfg->fallingEdgeDelay);
}


void CSL_epwmDeadbandBypass(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_DBCTL),
        PWMSS_EPWM_DBCTL_OUT_MODE,
        (uint16_t)PWMSS_EPWM_DBCTL_OUT_MODE_DISABLED);
}


void CSL_epwmChopperCfg(uint32_t baseAddr, const CSL_EpwmChopperCfg_t *pCfg)
{
    uint32_t freqDivider = pCfg->clkFrequency;
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_PCCTL);

    /* Configure chopping clock duty cycle */
    HW_SET_FIELD32(regVal, PWMSS_EPWM_PCCTL_CHPDUTY, pCfg->dutyCycle);

    /* Configure chopping clock frequency */
    if (freqDivider > CSL_EPWM_CHP_CLK_FREQ_DIV_BY_8)
    {
       freqDivider =  CSL_EPWM_CHP_CLK_FREQ_DIV_BY_8;
    }
    HW_SET_FIELD32(regVal, PWMSS_EPWM_PCCTL_CHPFREQ, freqDivider);

    /* Configure pulse width of first pulse */
    HW_SET_FIELD32(regVal, PWMSS_EPWM_PCCTL_OSHTWTH, pCfg->oneShotPulseWidth);

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_PCCTL), regVal);
}


void CSL_epwmChopperEnable(uint32_t baseAddr, uint32_t enableChopper)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_PCCTL);

    if (TRUE == enableChopper)
    {
        /* Enable chopper sub-module */
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_PCCTL_CHPEN, PWMSS_EPWM_PCCTL_CHPEN_ENABLE);
    }
    else
    {
        /* Disable chopper sub-module */
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_PCCTL_CHPEN, PWMSS_EPWM_PCCTL_CHPEN_DISABLE);
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_PCCTL),
        (uint16_t)regVal);
}


void CSL_epwmTzTriggerTripAction(uint32_t baseAddr,
                                 uint32_t tripAction,
                                 uint32_t pwmOutputCh)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZCTL);

    if (CSL_EPWM_OUTPUT_CH_A == pwmOutputCh)
    {
        HW_SET_FIELD32(regVal, PWMSS_EPWM_TZCTL_TZA, tripAction);
    }
    else if (CSL_EPWM_OUTPUT_CH_B == pwmOutputCh)
    {
        HW_SET_FIELD32(regVal, PWMSS_EPWM_TZCTL_TZB, tripAction);
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZCTL),
        (uint16_t)regVal);
}


void CSL_epwmTzTripEventEnable(uint32_t baseAddr,
                               uint32_t tzEventType,
                               uint32_t pinNum)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZSEL);

    if (CSL_EPWM_TZ_EVENT_ONE_SHOT == tzEventType)
    {
        HW_SET_FIELD32(
            regVal, PWMSS_EPWM_TZSEL_OSHTN, ((uint32_t)1U << pinNum));
    }
    else if (CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE == tzEventType)
    {
        HW_SET_FIELD32(
            regVal, PWMSS_EPWM_TZSEL_CBCN, ((uint32_t) 1U << pinNum));
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZSEL),
        (uint16_t)regVal);
}


void CSL_epwmTzTripEventDisable(uint32_t baseAddr,
                                uint32_t tzEventType,
                                uint32_t pinNum)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZSEL);

    if (CSL_EPWM_TZ_EVENT_ONE_SHOT == tzEventType)
    {
        regVal &= (~((((uint32_t) 1U << pinNum) << PWMSS_EPWM_TZSEL_OSHTN_SHIFT)
            & (PWMSS_EPWM_TZSEL_OSHTN_MASK)));
    }
    else if (CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE == tzEventType)
    {
        regVal &= (~((((uint32_t) 1U << pinNum) << PWMSS_EPWM_TZSEL_CBCN_SHIFT)
            & (PWMSS_EPWM_TZSEL_CBCN_MASK)));
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZSEL),
        (uint16_t)regVal);
}


void CSL_epwmTzIntrEnable(uint32_t baseAddr, uint32_t tzEventType)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZEINT);

    if (CSL_EPWM_TZ_EVENT_ONE_SHOT == tzEventType)
    {
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_TZEINT_OST, PWMSS_EPWM_TZEINT_OST_ENABLE);
    }
    else if (CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE == tzEventType)
    {
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_TZEINT_CBC, PWMSS_EPWM_TZEINT_CBC_ENABLE);
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZEINT),
        (uint16_t)regVal);
}


void CSL_epwmTzIntrDisable(uint32_t baseAddr, uint32_t tzEventType)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZEINT);

    if (CSL_EPWM_TZ_EVENT_ONE_SHOT == tzEventType)
    {
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_TZEINT_OST, PWMSS_EPWM_TZEINT_OST_DISABLE);
    }
    else if (CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE == tzEventType)
    {
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_TZEINT_CBC, PWMSS_EPWM_TZEINT_CBC_DISABLE);
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZEINT),
        (uint16_t)regVal);
}


uint16_t CSL_epwmTzEventStatus(uint32_t baseAddr, uint32_t eventMask)
{
    return ((HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZFLG)) &
        ((uint16_t)eventMask));
}


void CSL_epwmTzEventStatusClear(uint32_t baseAddr, uint32_t eventMask)
{
    uint32_t regVal = 0U;
    regVal = (eventMask) & (PWMSS_EPWM_TZCLR_OST_MASK |
        PWMSS_EPWM_TZCLR_CBC_MASK | PWMSS_EPWM_TZCLR_INT_MASK);
    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZCLR), regVal);
}


void CSL_epwmTzTriggerSwEvent(uint32_t baseAddr, uint32_t tzEventType)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZFRC);

    if (CSL_EPWM_TZ_EVENT_ONE_SHOT == tzEventType)
    {
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_TZFRC_OST, PWMSS_EPWM_TZFRC_OST_FORCE_TRIP);
    }
    else if (CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE == tzEventType)
    {
        HW_SET_FIELD32(regVal,
            PWMSS_EPWM_TZFRC_CBC, PWMSS_EPWM_TZFRC_CBC_FORCE_TRIP);
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TZFRC),
        (uint16_t)regVal);
}


void CSL_epwmEtIntrCfg(uint32_t baseAddr, uint32_t intrEvtSrc, uint32_t intrPrd)
{
    /* Configure interrupt source */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETSEL),
        PWMSS_EPWM_ETSEL_INTSEL, (uint16_t)intrEvtSrc);

    /* Configure the interrupt period */
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETPS),
        PWMSS_EPWM_ETPS_INTPRD, (uint16_t)intrPrd);
}

void CSL_epwmEtIntrEnable(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETSEL),
        PWMSS_EPWM_ETSEL_INTEN, (uint16_t)PWMSS_EPWM_ETSEL_INTEN_ENABLE);
}

void CSL_epwmEtIntrDisable(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETSEL),
        PWMSS_EPWM_ETSEL_INTEN, (uint16_t)PWMSS_EPWM_ETSEL_INTEN_DISABLE);
}

uint16_t CSL_epwmEtIntrStatus(uint32_t baseAddr)
{
    return (HW_RD_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETFLG),
        PWMSS_EPWM_ETFLG_INT));
}

void CSL_epwmEtIntrClear(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETCLR),
        PWMSS_EPWM_ETCLR_INT, (uint16_t)PWMSS_EPWM_ETCLR_INT_CLEAR);
}

void CSL_epwmEtIntrTrigger(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETFRC),
        PWMSS_EPWM_ETFRC_INT, (uint16_t)PWMSS_EPWM_ETFRC_INT_GENERATE_INTR);
}

uint16_t CSL_epwmEtGetEventCount(uint32_t baseAddr)
{
    return (HW_RD_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_ETPS),
        PWMSS_EPWM_ETPS_INTCNT));
}


void CSL_epwmHighResolutionCfg(uint32_t baseAddr,
                               uint32_t ctrlMode,
                               uint32_t mepCtrlEdge)
{
    uint32_t regVal =
        HW_RD_REG16((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_HRCTL);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_HRCTL_DELBUSSEL, ctrlMode);
    HW_SET_FIELD32(regVal, PWMSS_EPWM_HRCTL_DELMODE, mepCtrlEdge);
    HW_WR_REG16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_HRCTL),
        (uint16_t)regVal);
}


void CSL_epwmHrLoadTbPhaseHrValue(uint32_t baseAddr, uint32_t tbPhsHighResVal)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_TBPHSHR),
        PWMSS_EPWM_TBPHSHR_TBPHSH, (uint16_t)tbPhsHighResVal);
}


void CSL_epwmHrLoadCmpAHrValue(uint32_t baseAddr,
                               uint32_t compAHighResVal,
                               uint32_t ShadowToActiveLoadTrigger)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_CMPAHR),
        PWMSS_EPWM_CMPAHR, (uint16_t)compAHighResVal);

    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_HRCTL),
        PWMSS_EPWM_HRCTL_PULSESEL, (uint16_t)ShadowToActiveLoadTrigger);
}


void CSL_epwmHighResolutionDisable(uint32_t baseAddr)
{
    HW_WR_FIELD16(((baseAddr + PWMSS_EPWM_OFFSET) + PWMSS_EPWM_HRCTL),
        PWMSS_EPWM_HRCTL_DELMODE, (uint16_t)PWMSS_EPWM_HRCTL_DELMODE_NO_DELAY);
}


void CSL_epwmClockEnable(uint32_t baseAddr)
{
    HW_WR_FIELD32((baseAddr + CSL_PWMSS_CLKCONFIG),
        CSL_PWMSS_CLKCONFIG_EPWMCLK_EN,
        PWMSS_CLK_CFG_EPWM_CLK_ENABLE);
}


void CSL_epwmClockDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32((baseAddr + CSL_PWMSS_CLKCONFIG),
        CSL_PWMSS_CLKCONFIG_EPWMCLKSTOP_REQ,
        PWMSS_CLK_CFG_EPWM_CLK_STOP);
}
