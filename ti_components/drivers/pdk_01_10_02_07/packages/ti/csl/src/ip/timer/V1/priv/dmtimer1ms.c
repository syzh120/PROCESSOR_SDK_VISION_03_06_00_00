/*
 *  Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file  dmtimer1ms.c
 *
 *  \brief DM Timer 1MS APIs.
 *
 *   This file contains the device abstraction layer APIs for Timer.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/**
 * \brief   This function will check for write POSTED status
 *
 * \param   reg          Register whose status has to be checked
 *
 *    'reg' can take the following values \n
 *    DMTIMER1MS_WRITE_POST_TCLR - Timer Control register \n
 *    DMTIMER1MS_WRITE_POST_TCRR - Timer Counter register \n
 *    DMTIMER1MS_WRITE_POST_TLDR - Timer Load register \n
 *    DMTIMER1MS_WRITE_POST_TTGR - Timer Trigger register \n
 *    DMTIMER1MS_WRITE_POST_TMAR - Timer Match register \n
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
static inline void TimerWaitForWrite(uint32_t reg, uint32_t baseAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DMTIMER1MSEnable(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Start the timer */
    HW_WR_FIELD32(
        baseAddr + DMTIMER_1MS_TCLR,
        DMTIMER_1MS_TCLR_ST,
        DMTIMER_1MS_TCLR_ST_CNT_START);
}

void DMTIMER1MSDisable(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Stop the timer */
    HW_WR_FIELD32(
        baseAddr + DMTIMER_1MS_TCLR,
        DMTIMER_1MS_TCLR_ST,
        DMTIMER_1MS_TCLR_ST_CNT_STOP);
}

void DMTIMER1MSModeConfigure(uint32_t baseAddr, uint32_t timerMode)
{
    uint32_t regVal;

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Clear the AR and CE field of TCLR */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TCLR,
                  DMTIMER_1MS_TCLR_AR,
                  DMTIMER_1MS_TCLR_AR_ONE_SHOT);

    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TCLR,
                  DMTIMER_1MS_TCLR_CE,
                  DMTIMER_1MS_TCLR_CE_DSB_CMP);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Set the timer mode in TCLR register */
    regVal = HW_RD_REG32(baseAddr + DMTIMER_1MS_TCLR);

    regVal |= (timerMode & (DMTIMER_1MS_TCLR_AR_MASK | DMTIMER_1MS_TCLR_CE_MASK));

    HW_WR_REG32(baseAddr + DMTIMER_1MS_TCLR, regVal);
}

void DMTIMER1MSPreScalerClkEnable(uint32_t baseAddr, uint32_t ptv)
{
    uint32_t regVal;

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Clear the PTV field of TCLR */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TCLR, DMTIMER_1MS_TCLR_PTV, 0U);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Set the PTV field and enable the pre-scaler clock */
    regVal = HW_RD_REG32(baseAddr + DMTIMER_1MS_TCLR);

    regVal |= (ptv & (DMTIMER_1MS_TCLR_PTV_MASK | DMTIMER_1MS_TCLR_PRE_MASK));

    HW_WR_REG32(baseAddr + DMTIMER_1MS_TCLR, regVal);
}

void DMTIMER1MSPreScalerClkDisable(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Disable Pre-scaler clock */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TCLR,
                  DMTIMER_1MS_TCLR_PRE,
                  DMTIMER_1MS_TCLR_PRE_NO_PRESCAL);
}

void DMTIMER1MSCounterSet(uint32_t baseAddr, uint32_t counter)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCRR, baseAddr);

    /* Set the counter value */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TCRR, counter);
}

uint32_t DMTIMER1MSCounterGet(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCRR, baseAddr);

    /* Read the counter value from TCRR */
    return (HW_RD_REG32(baseAddr + DMTIMER_1MS_TCRR));
}

void DMTIMER1MSReloadSet(uint32_t baseAddr, uint32_t reload)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TLDR, baseAddr);

    /* Load the register with the re-load value */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TLDR, reload);
}

uint32_t DMTIMER1MSReloadGet(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TLDR, baseAddr);

    /* Return the contents of TLDR */
    return (HW_RD_REG32(baseAddr + DMTIMER_1MS_TLDR));
}

void DMTIMER1MSGPOConfigure(uint32_t baseAddr, uint32_t gpoCfg)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Clear the GPO_CFG field of TCLR */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TCLR,
                  DMTIMER_1MS_TCLR_GPO_CFG,
                  DMTIMER_1MS_TCLR_GPO_CFG_0);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    /* Write to the gpoCfg field of TCLR */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TCLR,
                  DMTIMER_1MS_TCLR_GPO_CFG,
                  gpoCfg >> DMTIMER_1MS_TCLR_GPO_CFG_SHIFT);
}

void DMTIMER1MSCompareSet(uint32_t baseAddr, uint32_t compareVal)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TMAR, baseAddr);

    /* Write the compare value to TMAR */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TMAR, compareVal);
}

uint32_t DMTIMER1MSCompareGet(uint32_t baseAddr)
{
    /* Return the TMAR value */
    return (HW_RD_REG32(baseAddr + DMTIMER_1MS_TMAR));
}

uint32_t DMTIMER1MSIntStatusGet(uint32_t baseAddr)
{
    /* Return the status of TISR register */
    return (HW_RD_REG32(baseAddr + DMTIMER_1MS_TISR));
}

void DMTIMER1MSIntStatusClear(uint32_t baseAddr, uint32_t intFlags)
{
    /* Clear the interrupt status from TISR register */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TISR,
                intFlags & (DMTIMER_1MS_TISR_TCAR_IT_FLAG_MASK |
                            DMTIMER_1MS_TISR_OVF_IT_FLAG_MASK |
                            DMTIMER_1MS_TISR_MAT_IT_FLAG_MASK));
}

void DMTIMER1MSIntEnable(uint32_t baseAddr, uint32_t intFlags)
{
	uint32_t regVal;

    regVal  = HW_RD_REG32(baseAddr + DMTIMER_1MS_TIER);
	regVal |= (intFlags & (TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK |
                           TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK |
                           TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK));

    /* Enable the Timer interrupts represented by intFlags */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TIER, regVal);
}

void DMTIMER1MSIntDisable(uint32_t baseAddr, uint32_t intFlags)
{
	uint32_t regVal, mask;
    
	mask = ~(intFlags & (TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK |
                         TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK |
                         TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK));

	/* Disable the Timer interrupts represented by intFlags */
	regVal = HW_RD_REG32(baseAddr + DMTIMER_1MS_TIER) & mask;
	
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TIER, regVal);
}

void DMTIMER1MSWakeEnable(uint32_t baseAddr, uint32_t wakeFlags)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + DMTIMER_1MS_TWER);
    regVal |= wakeFlags & (DMTIMER_1MS_TWER_TCAR_WUP_ENA_MASK |
                           DMTIMER_1MS_TWER_OVF_WUP_ENA_MASK |
                           DMTIMER_1MS_TWER_MAT_WUP_ENA_MASK);
    /* Enable the Timer Wakeup events represented by wakeFlags */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TWER, regVal);
}

void DMTIMER1MSWakeDisable(uint32_t baseAddr, uint32_t wakeFlags)
{
    uint32_t regVal, mask;

    mask = ~(wakeFlags & (DMTIMER_1MS_TWER_TCAR_WUP_ENA_MASK |
                          DMTIMER_1MS_TWER_OVF_WUP_ENA_MASK |
                          DMTIMER_1MS_TWER_MAT_WUP_ENA_MASK));
    regVal = HW_RD_REG32(baseAddr + DMTIMER_1MS_TWER) & mask;
    /* Disable the Timer Wakeup events represented by wakeFlags */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TWER, regVal);
}

void DMTIMER1MSTriggerSet(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TTGR, baseAddr);

    /* Write a value to the register */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TTGR, DMTIMER_1MS_TTGR_TTGR_VALUE_MASK);
}

uint32_t DMTIMER1MSIntEnableGet(uint32_t baseAddr)
{
    /* Return the status of register TIER */
    return (HW_RD_REG32(baseAddr + DMTIMER_1MS_TIER));
}

void DMTIMER1MSResetConfigure(uint32_t baseAddr, uint32_t rstOption)
{
    /* Write the option sent by user to SFT field of TSICR */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TSICR,
                  DMTIMER_1MS_TSICR_SFT,
                  rstOption >> DMTIMER_1MS_TSICR_SFT_SHIFT);
}

void DMTIMER1MSReset(uint32_t baseAddr)
{
    /* Reset the Timer module */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TIOCP_CFG,
                  DMTIMER_1MS_TIOCP_CFG_SOFTRESET,
                  DMTIMER_1MS_TIOCP_CFG_SOFTRESET_RSTMODE);

    while (DMTIMER_1MS_TIOCP_CFG_SOFTRESET_RSTMODE ==
           HW_RD_FIELD32(baseAddr + DMTIMER_1MS_TIOCP_CFG,
                         DMTIMER_1MS_TIOCP_CFG_SOFTRESET))
    {
        /* Do nothing - Busy wait */
    }
}

void DMTIMER1MSContextSave(uint32_t baseAddr, DMTIMER1MSCONTEXT *contextPtr)
{
    contextPtr->tldr         = HW_RD_REG32(baseAddr + DMTIMER_1MS_TLDR);
    contextPtr->tmar         = HW_RD_REG32(baseAddr + DMTIMER_1MS_TMAR);
    contextPtr->irqenableset = HW_RD_REG32(baseAddr + DMTIMER_1MS_TIER);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCRR, baseAddr);

    contextPtr->tcrr = HW_RD_REG32(baseAddr + DMTIMER_1MS_TCRR);
    contextPtr->tclr = HW_RD_REG32(baseAddr + DMTIMER_1MS_TCLR);
}

void DMTIMER1MSContextRestore(uint32_t baseAddr, const DMTIMER1MSCONTEXT *contextPtr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TLDR, baseAddr);

    HW_WR_REG32(baseAddr + DMTIMER_1MS_TLDR, contextPtr->tldr);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TMAR, baseAddr);

    HW_WR_REG32(baseAddr + DMTIMER_1MS_TMAR, contextPtr->tmar);
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TIER, contextPtr->irqenableset);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCRR, baseAddr);

    HW_WR_REG32(baseAddr + DMTIMER_1MS_TCRR, contextPtr->tcrr);

    /* Wait for previous write to complete */
    TimerWaitForWrite(DMTIMER1MS_WRITE_POST_TCLR, baseAddr);

    HW_WR_REG32(baseAddr + DMTIMER_1MS_TCLR, contextPtr->tclr);
}

void DMTIMER1MSPostedModeConfig(uint32_t baseAddr, uint32_t postMode)
{
    /* Write to the POSTED field of TSICR */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TSICR,
                  DMTIMER_1MS_TSICR_POSTED,
                  postMode >> DMTIMER_1MS_TSICR_POSTED_SHIFT);
}

uint32_t DMTIMER1MSWritePostedStatusGet(uint32_t baseAddr)
{
    /* Return the status of TWPS register */
    return (HW_RD_REG32(baseAddr + DMTIMER_1MS_TWPS));
}

void DMTIMER1MSIdleModeConfigure(uint32_t baseAddr, uint32_t idleModeOption)
{
    /* Write to the EMUFREE field of TIOCP_CFG */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TIOCP_CFG,
                  DMTIMER_1MS_TIOCP_CFG_IDLEMODE,
                  idleModeOption);
}

void DMTIMER1MSEmuModeConfigure(uint32_t baseAddr, uint32_t emuModeOption)
{
    /* Write to the EMUFREE field of TIOCP_CFG */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TIOCP_CFG,
                  DMTIMER_1MS_TIOCP_CFG_EMUFREE,
                  emuModeOption);
}

void DMTIMER1MSTPIRSet(uint32_t baseAddr, uint32_t tpirVal)
{
    /* Loading the Positive increment Value in TPIR register */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TPIR, tpirVal);

}

void DMTIMER1MSTNIRSet(uint32_t baseAddr, uint32_t tnirVal)
{
    /* Loading the Negative increment Value in TNIR register */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TNIR, tnirVal);
}

void DMTIMER1MSTCVRSet(uint32_t baseAddr, uint32_t val)
{
    /*
    ** Loading the value to decide the next TCRR value will be sub period or
    ** the over period value.
    */
    HW_WR_REG32(baseAddr + DMTIMER_1MS_TCVR, val);
}

void DMTIMER1MSTOCRSet(uint32_t baseAddr, uint32_t val)
{
    /* Loading the value to mask the tick interrupt for 'val' no of ticks */
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TOCR,
                  DMTIMER_1MS_TOCR_OVF_COUNTER_VALUE,
                  val);
}

uint32_t DMTIMER1MSTOWRGet(uint32_t baseAddr)
{
    /* Gets the number of masked overflow interrupts. */
    return (HW_RD_FIELD32(baseAddr + DMTIMER_1MS_TOWR,
            DMTIMER_1MS_TOWR_OVF_WRAPPING_VALUE));
}

void DMTIMER1MSTOWRSet(uint32_t baseAddr, uint32_t val)
{
    /* Setting the overflow count mask value in TOWR register*/
    HW_WR_FIELD32(baseAddr + DMTIMER_1MS_TOWR,
                  DMTIMER_1MS_TOWR_OVF_WRAPPING_VALUE,
                  val);
}

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */
static inline void TimerWaitForWrite(uint32_t reg, uint32_t baseAddr)
{
    if (0U != HW_RD_FIELD32(baseAddr + DMTIMER_1MS_TSICR, DMTIMER_1MS_TSICR_POSTED))
    {
        while ((uint32_t) 0U != (reg & DMTIMER1MSWritePostedStatusGet(baseAddr)))
        {
            /* Do nothing - Busy wait */
        }
    }
}
/********************************* End of file ******************************/
