/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - www.ti.com
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
 * \file       mcspi.c
 *
 * \brief      This file contains the function definitions for the device
 *             abstraction layer for MCSPI.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include <stdint.h>
/*LDRA_ANALYSIS*/
#include <ti/csl/csl_mcspi.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MCSPI_CLKD_MASK       (0xF)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void McSPIClkConfig(uint32_t baseAddr,
                    uint32_t spiInClk,
                    uint32_t spiOutClk,
                    uint32_t chNum,
                    uint32_t clkMode)
{
    uint32_t fRatio;
    uint32_t spiClk;
    uint32_t clkD;
    /*TI_INSPECTED 105 D: MISRAC_2012_R.2.2
     * "Reason - LDRA tool issue not able to understand HW_WR_FIELD32 macros
     *" */
    uint32_t extClk;

    /* Calculate the value of fRatio. */
    fRatio = spiInClk / spiOutClk;

    /* If fRatio is not a power of 2, set granularity of 1 clock cycle */
    if ((uint32_t) 0U != (fRatio & (fRatio - 1U)))
    {
        /* Set the clock granularity to 1 clock cycle.*/
        HW_WR_FIELD32(
            baseAddr + MCSPI_CHCONF(chNum),
            MCSPI_CH0CONF_CLKG,
            MCSPI_CH0CONF_CLKG_ONECYCLE);

        /* Calculate the ratios clkD and extClk based on fClk */
        extClk = (fRatio - 1U) >> 4U;
        clkD   = (fRatio - 1U) & (uint32_t) MCSPI_CLKD_MASK;

        /* Set the extClk field of MCSPI_CHCTRL register.*/
        HW_WR_FIELD32(
            baseAddr + MCSPI_CHCTRL(chNum),
            MCSPI_CH0CTRL_EXTCLK,
            extClk);
    }
    else
    {
        clkD   = 0U;
        /* Clock granularity of power of 2.*/
        HW_WR_FIELD32(
            baseAddr + MCSPI_CHCONF(chNum),
            MCSPI_CH0CONF_CLKG,
            MCSPI_CH0CONF_CLKG_POWERTWO);

        while (1U != fRatio)
        {
            fRatio /= 2U;
            clkD++;
        }
    }

    /* Configure the clkD field of MCSPI_CHCONF register.*/
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_CLKD,
        clkD);

    /*Clearing the clkMode field of MCSPI_CHCONF register.*/
    spiClk = HW_RD_REG32(baseAddr + MCSPI_CHCONF(chNum));

    spiClk &= ~((uint32_t) MCSPI_CH0CONF_PHA_MASK | (uint32_t) MCSPI_CH3CONF_POL_MASK);

    /* Configure the clkMode of MCSPI_CHCONF register.*/
    spiClk |= (clkMode & (MCSPI_CH0CONF_PHA_MASK | MCSPI_CH3CONF_POL_MASK));

    HW_WR_REG32(baseAddr + MCSPI_CHCONF(chNum), spiClk);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is setting a WordLength
 *  register field in McSPI register" */
void McSPIWordLengthSet(uint32_t baseAddr,
                        uint32_t wordLength,
                        uint32_t chNum)
{
    /* Setting the wordlength field. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_WL,
        wordLength >> MCSPI_CH0CONF_WL_SHIFT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is enabling chipSelect
 *  register field in McSPI register" */
void McSPICSEnable(uint32_t baseAddr)
{
    /* CLear PIN34 of MCSPI_MODULCTRL register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_PIN34,
        MCSPI_MODULCTRL_PIN34_4PINMODE);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is disabling chipSelect
 *  register field in McSPI register" */
void McSPICSDisable(uint32_t baseAddr)
{
    /* Set PIN34 of MCSPI_MODULCTRL register.*/
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_PIN34,
        MCSPI_MODULCTRL_PIN34_3PINMODE);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is setting chipSelect
 *  polarity register field in McSPI register" */
void McSPICSPolarityConfig(uint32_t baseAddr,
                           uint32_t spiEnPol,
                           uint32_t chNum)
{
    /* Set the EPOL field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_EPOL,
        spiEnPol >> MCSPI_CH0CONF_EPOL_SHIFT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is setting chipSelect
 *  time control register field in McSPI register" */
void McSPICSTimeControlSet(uint32_t baseAddr,
                           uint32_t csTimeControl,
                           uint32_t chNum)
{
    /* Set the TCS field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_TCS0,
        csTimeControl);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is setting the force bit
 *  register field in McSPI register for McSPI channel configiration" */
void McSPICSAssert(uint32_t baseAddr, uint32_t chNum)
{
    /* Set the FORCE bit of MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_FORCE,
        MCSPI_CH0CONF_FORCE_ASSERT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It clears the force bit
 *  register field in McSPI register for McSPI channel configiration" */
void McSPICSDeAssert(uint32_t baseAddr, uint32_t chNum)
{
    /* Clear the FORCE bit of MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_FORCE,
        MCSPI_CH0CONF_FORCE_DEASSERT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It enables the start bit
 *  register field in McSPI register for McSPI channel configiration" */
 void McSPIStartBitEnable(uint32_t baseAddr, uint32_t chNum)
{
    /* Set the SBE bit of MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_SBE,
        MCSPI_CH0CONF_SBE_ENABLED);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the start bit polarity
 *  register field in McSPI register for McSPI channel configiration" */
void McSPIStartBitPolarityConfig(uint32_t baseAddr,
                                 uint32_t startBitPol,
                                 uint32_t chNum)
{
    /* Set the SBPOL bit of MCSPI_CHCONF register with the user sent value */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_SBPOL,
        startBitPol);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It disables the start bit
 *  register field in McSPI register for McSPI channel configiration" */
void McSPIStartBitDisable(uint32_t baseAddr, uint32_t chNum)
{
    /* Clear the SBE field of MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_SBE,
        MCSPI_CH0CONF_SBE_DISABLED);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It enables the Master Mode
 *  register field in McSPI register" */
void McSPIMasterModeEnable(uint32_t baseAddr)
{
    /* Clear the MS field of MCSPI_MODULCTRL register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_MS,
        MCSPI_MODULCTRL_MS_MASTER);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It enables the Slave Mode
 *  register field in McSPI register" */
void McSPISlaveModeEnable(uint32_t baseAddr)
{
    /* Set the MS field of MCSPI_MODULCTRL register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_MS,
        MCSPI_MODULCTRL_MS_SLAVE);
}

uint32_t McSPIMasterModeConfig(uint32_t baseAddr,
                               uint32_t channelMode,
                               uint32_t trMode,
                               uint32_t pinMode,
                               uint32_t chNum)
{
    uint32_t retVal;
    uint32_t regVal;

    /* Set the MS field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_SINGLE,
        channelMode);

    /* Set the TRM field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_TRM,
        trMode >> MCSPI_CH0CONF_TRM_SHIFT);

    if (((MCSPI_TX_RX_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_3 == pinMode)) ||
        ((MCSPI_TX_ONLY_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_3 == pinMode)) ||
        ((MCSPI_TX_RX_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_7 == pinMode)) ||
        ((MCSPI_TX_ONLY_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_7 == pinMode)))
    {
        retVal = (uint32_t) FALSE;
    }
    else
    {
        /* Clear the IS, DPE0, DPE1 fields of MCSPI_CHCONF register. */
        regVal = HW_RD_REG32(baseAddr + MCSPI_CHCONF(chNum));

        regVal &= ~(MCSPI_CH0CONF_IS_MASK |
                    MCSPI_CH0CONF_DPE1_MASK |
                    MCSPI_CH0CONF_DPE0_MASK);

        /* Set the IS, DPE0, DPE1 fields with the user sent values. */
        regVal |= (pinMode & (MCSPI_CH0CONF_IS_MASK |
                              MCSPI_CH0CONF_DPE1_MASK |
                              MCSPI_CH0CONF_DPE0_MASK));

        HW_WR_REG32(baseAddr + MCSPI_CHCONF(chNum), regVal);

        retVal = (uint32_t) TRUE;
    }

    return retVal;
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It enables the channel
 *  register field in McSPI register" */
 void McSPIChannelEnable(uint32_t baseAddr, uint32_t chNum)
{
    /* Set the EN field of MCSPI_CHCTRL register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCTRL(chNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_ACT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It disables the channel
 *  register field in McSPI register" */
 void McSPIChannelDisable(uint32_t baseAddr, uint32_t chNum)
{
    /* Clear the EN field of MCSPI_CHCTRL register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCTRL(chNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_NACT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the reset register
 *  field in McSPI register" */
void McSPIReset(uint32_t baseAddr)
{
    /* Set the SOFTRESET field of MCSPI_SYSCONFIG register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_SYSCONFIG,
        MCSPI_SYSCONFIG_SOFTRESET,
        MCSPI_SYSCONFIG_SOFTRESET_ON);

    /* Stay in the loop until reset is done. */
    while ((MCSPI_SYSSTATUS_RESETDONE_COMPLETED &
           (HW_RD_REG32(baseAddr + MCSPI_SYSSTATUS))) != 1U)
    {
        /* Do nothing - Busy wait */
    }
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It enables the turbo mode
 *  register field in McSPI register" */
void McSPITurboModeEnable(uint32_t baseAddr, uint32_t chNum)
{
    /* Set the TURBO field on MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_TURBO,
        MCSPI_CH0CONF_TURBO_TURBO);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It disables the turbo mode
 *  register field in McSPI register" */
void McSPITurboModeDisable(uint32_t baseAddr, uint32_t chNum)
{
    /* Clear the TURBO field of MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_TURBO,
        MCSPI_CH0CONF_TURBO_OFF);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the FFEW register
 *  field in McSPI register" */
void McSPITxFIFOConfig(uint32_t baseAddr,
                       uint32_t txFifo,
                       uint32_t chNum)
{
    /* Set the FFEW field with user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_FFEW,
        txFifo >> MCSPI_CH0CONF_FFEW_SHIFT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the FFER register
 *  field in McSPI register" */
void McSPIRxFIFOConfig(uint32_t baseAddr,
                       uint32_t rxFifo,
                       uint32_t chNum)
{
    /* Set the FFER field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_FFER,
        rxFifo >> MCSPI_CH0CONF_FFER_SHIFT);
}

void McSPIFIFOTrigLvlSet(uint32_t baseAddr,
                         uint8_t  afl,
                         uint8_t  ael,
                         uint32_t trMode)
{
    uint32_t regVal;

    if (MCSPI_TX_RX_MODE == trMode)
    {
        /* Clear the AFL and AEL fields of MCSPI_XFERLEVEL register. */
        regVal = HW_RD_REG32(baseAddr + MCSPI_XFERLEVEL);

        regVal &= ~((uint32_t) MCSPI_XFERLEVEL_AFL_MASK | (uint32_t) MCSPI_XFERLEVEL_AEL_MASK);

        regVal |= (((((uint32_t) afl - 1U) << MCSPI_XFERLEVEL_AFL_SHIFT) &
                    MCSPI_XFERLEVEL_AFL_MASK) |
                   (((uint32_t) ael - 1U) & MCSPI_XFERLEVEL_AEL_MASK));

        /* Set the AFL and AEL fields with the user sent value. */
        HW_WR_REG32(baseAddr + MCSPI_XFERLEVEL, regVal);
    }
    else if (MCSPI_TX_ONLY_MODE == trMode)
    {
        /* Set the AEL field with the user sent value. */
        HW_WR_FIELD32(
            baseAddr + MCSPI_XFERLEVEL,
            MCSPI_XFERLEVEL_AEL,
            (uint32_t) ael - 1U);
    }
    else if (MCSPI_RX_ONLY_MODE == trMode)
    {
        /* Set the AFL field with the user sent value. */
        HW_WR_FIELD32(
            baseAddr + MCSPI_XFERLEVEL,
            MCSPI_XFERLEVEL_AFL,
            (uint32_t) afl - 1U);
    }
    else
    {
        /*
         * Do nothing
         */
    }
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the word count
 *  register field in McSPI register" */
void McSPIWordCountSet(uint32_t baseAddr, uint16_t wCnt)
{
    /* Set the WCNT field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_XFERLEVEL,
        MCSPI_XFERLEVEL_WCNT,
        wCnt);
}

void McSPIDMAEnable(uint32_t baseAddr,
                    uint32_t dmaFlags,
                    uint32_t chNum)
{
    /* Enable the DMA events. */
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + MCSPI_CHCONF(chNum));

    regVal |= (dmaFlags & (MCSPI_CH0CONF_DMAR_MASK | MCSPI_CH0CONF_DMAW_MASK));

    HW_WR_REG32(baseAddr + MCSPI_CHCONF(chNum), regVal);
}

void McSPIDMADisable(uint32_t baseAddr,
                     uint32_t dmaFlags,
                     uint32_t chNum)
{
    /* Disable the DMA events. */
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + MCSPI_CHCONF(chNum));

    regVal &= ~(dmaFlags & (MCSPI_CH0CONF_DMAR_MASK | MCSPI_CH0CONF_DMAW_MASK));

    HW_WR_REG32(baseAddr + MCSPI_CHCONF(chNum), regVal);
}

void McSPIIntEnable(uint32_t baseAddr, uint32_t intFlags)
{
    /* Enable the Interrupts. */
    uint32_t intrMask;

    intrMask = HW_RD_REG32(baseAddr + MCSPI_IRQENABLE);

    intrMask |= intFlags;

    HW_WR_REG32(baseAddr + MCSPI_IRQENABLE, intrMask);
}

void McSPIIntDisable(uint32_t baseAddr, uint32_t intFlags)
{
    /* Disable the interrupts. */
    uint32_t intrMask;

    intrMask = HW_RD_REG32(baseAddr + MCSPI_IRQENABLE);

    intrMask &= ~intFlags;

    HW_WR_REG32(baseAddr + MCSPI_IRQENABLE, intrMask);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the Intial delay
 *  register field in McSPI register" */
void McSPIInitDelayConfig(uint32_t baseAddr, uint32_t initDelay)
{
    /* Set the INITDLY field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_INITDLY,
        initDelay >> MCSPI_MODULCTRL_INITDLY_SHIFT);
}

/*TI_INSPECTED 1 D 1: MISRA-C:2012_R.2.7
 * "Reason - Ensured procedure parameter is used" */
void McSPITransmitData(uint32_t baseAddr,
                       uint32_t txData,
                       uint32_t chNum)
{
    /* Load the MCSPI_TX register with the data to be transmitted */
    HW_WR_REG32(baseAddr + MCSPI_CHTX(chNum), txData);
}

uint32_t McSPIReceiveData(uint32_t baseAddr, uint32_t chNum)
{
    /* Return the data present in the MCSPI_RX register. */
    return (HW_RD_REG32(baseAddr + MCSPI_CHRX(chNum)));
}

uint32_t McSPIIntStatusGet(uint32_t baseAddr)
{
    /* Return the interrupt status present in the MCSPI_IRQSTATUS register. */
    return (HW_RD_REG32(baseAddr + MCSPI_IRQSTATUS));
}

void McSPIIntStatusClear(uint32_t baseAddr, uint32_t intFlags)
{
    /* Clear the SSB bit in the MCSPI_SYST register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_SYST,
        MCSPI_SYST_SSB,
        MCSPI_SYST_SSB_OFF);

    /* Clear the interrupt status. */
    HW_WR_REG32(baseAddr + MCSPI_IRQSTATUS, intFlags);
}

uint32_t McSPIChannelStatusGet(uint32_t baseAddr, uint32_t chNum)
{
    /* Return the status from MCSPI_CHSTAT register. */
    return (HW_RD_REG32(baseAddr + MCSPI_CHSTAT(chNum)));
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It sets the MOA register field
 *  in McSPI register" */
void McSPIMultipleWordAccessConfig(uint32_t baseAddr, uint32_t moa)
{
    /* Set the MOA fields with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_MOA,
        moa >> MCSPI_MODULCTRL_MOA_SHIFT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect.It sets the FDAA register field
 *  in McSPI register" */
void McSPIFIFODatManagementConfig(uint32_t baseAddr, uint32_t fdaa)
{
    /* Set the FDAA field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_FDAA,
        fdaa >> MCSPI_MODULCTRL_FDAA_SHIFT);
}

/*TI_INSPECTED 1 D 1: MISRA-C:2012_R.2.7
 * "Reason - Ensured procedure parameter is used" */
void MCSPISysConfigSetup(uint32_t baseAddr,
                         uint32_t clockActivity,
                         uint32_t sidleMode,
                         uint32_t wakeUp,
                         uint32_t autoIdle)
{
    HW_WR_REG32(
        baseAddr + MCSPI_SYSCONFIG,
        (clockActivity | sidleMode | wakeUp | autoIdle) &
        (MCSPI_SYSCONFIG_CLOCKACTIVITY_MASK | MCSPI_SYSCONFIG_SIDLEMODE_MASK |
         MCSPI_SYSCONFIG_ENAWAKEUP_MASK | MCSPI_SYSCONFIG_AUTOIDLE_MASK));
}

uint32_t MCSPIPinDirSet(uint32_t baseAddr,
                        uint32_t trMode,
                        uint32_t pinMode,
                        uint32_t chNum)
{
    uint32_t regVal, retVal;

    /* Set the TRM field with the user sent value. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_TRM,
        trMode >> MCSPI_CH0CONF_TRM_SHIFT);

    if (((MCSPI_TX_RX_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_3 == pinMode)) ||
        ((MCSPI_TX_ONLY_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_3 == pinMode)) ||
        ((MCSPI_TX_RX_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_7 == pinMode)) ||
        ((MCSPI_TX_ONLY_MODE == trMode) &&
         (MCSPI_DATA_LINE_COMM_MODE_7 == pinMode)))
    {
        /* Not Supported */
        retVal = 1U;
    }
    else
    {
        /* Clear the IS, DPE0, DPE1 fields of MCSPI_CHCONF register. */
        regVal = HW_RD_REG32(baseAddr + MCSPI_CHCONF(chNum));

        regVal &= ~(MCSPI_CH0CONF_IS_MASK |
                    MCSPI_CH0CONF_DPE0_MASK |
                    MCSPI_CH0CONF_DPE1_MASK);

        HW_WR_REG32(baseAddr + MCSPI_CHCONF(chNum), regVal);

        /* Set the IS, DPE0, DPE1 fields with the user sent values. */
        regVal = HW_RD_REG32(baseAddr + MCSPI_CHCONF(chNum));

        regVal |= (pinMode & (MCSPI_CH0CONF_IS_MASK |
                              MCSPI_CH0CONF_DPE0_MASK |
                              MCSPI_CH0CONF_DPE1_MASK));

        HW_WR_REG32(baseAddr + MCSPI_CHCONF(chNum), regVal);

        retVal = 0U;
    }
    return retVal;
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect.It enables single channel Mode
 *  register field in McSPI register" */
 void MCSPISingleChModeEnable(uint32_t baseAddr)
{
    /* Set the SINGLE field of MCSPI_MODULCTRL register to enable single channel
       Mode */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_SINGLE,
        MCSPI_MODULCTRL_SINGLE_SINGLE);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect.It enables multi channel Mode
 *  register field in McSPI register" */
void MCSPIMultiChModeEnable(uint32_t baseAddr)
{
    /* Clear the SINGLE field of MCSPI_MODULCTRL register to enable multi
       channel Mode */
    HW_WR_FIELD32(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_SINGLE,
        MCSPI_MODULCTRL_SINGLE_MULTI);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect.It sets the slave chip select
 *  register field in McSPI register" */
void McSPISetSlaveChipSel(uint32_t baseAddr,
                          uint32_t chNum,
                          uint32_t slaveChipSel)
{
    /* Set the SPIENSLV field of MCSPI_CHCONF register. */
    HW_WR_FIELD32(
        baseAddr + MCSPI_CHCONF(chNum),
        MCSPI_CH0CONF_SPIENSLV,
        slaveChipSel);
}

/***************************** END OF FILE ************************************/
