/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file  timer.c
 *
 *  \brief Timer APIs.
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
 *    TIMER_WRITE_POST_TCLR - Timer Control register \n
 *    TIMER_WRITE_POST_TCRR - Timer Counter register \n
 *    TIMER_WRITE_POST_TLDR - Timer Load register \n
 *    TIMER_WRITE_POST_TTGR - Timer Trigger register \n
 *    TIMER_WRITE_POST_TMAR - Timer Match register \n
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
void TIMEREnable(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Start the timer */
    HW_WR_FIELD32(
        baseAddr + TIMER_TCLR,
        TIMER_TCLR_ST,
        TIMER_TCLR_ST_ST_VALUE_1);
}

void TIMERDisable(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Stop the timer */
    HW_WR_FIELD32(
        baseAddr + TIMER_TCLR,
        TIMER_TCLR_ST,
        TIMER_TCLR_ST_ST_VALUE_0);
}

void TIMERModeConfigure(uint32_t baseAddr, uint32_t timerMode)
{
    uint32_t regVal;

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Clear the AR and CE field of TCLR */
    HW_WR_FIELD32(baseAddr + TIMER_TCLR,
                  TIMER_TCLR_AR,
                  TIMER_TCLR_AR_AR_VALUE_0);

    HW_WR_FIELD32(baseAddr + TIMER_TCLR,
                  TIMER_TCLR_CE,
                  TIMER_TCLR_CE_CE_VALUE_0);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Set the timer mode in TCLR register */
    regVal = HW_RD_REG32(baseAddr + TIMER_TCLR);

    regVal |= (timerMode & (TIMER_TCLR_AR_MASK | TIMER_TCLR_CE_MASK));

    HW_WR_REG32(baseAddr + TIMER_TCLR, regVal);
}

void TIMERPreScalerClkEnable(uint32_t baseAddr, uint32_t ptv)
{
    uint32_t regVal;

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Clear the PTV field of TCLR */
    HW_WR_FIELD32(baseAddr + TIMER_TCLR, TIMER_TCLR_PTV, 0U);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Set the PTV field and enable the pre-scaler clock */
    regVal = HW_RD_REG32(baseAddr + TIMER_TCLR);

    regVal |= (ptv & (TIMER_TCLR_PTV_MASK | TIMER_TCLR_PRE_MASK));

    HW_WR_REG32(baseAddr + TIMER_TCLR, regVal);
}

void TIMERPreScalerClkDisable(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Disable Pre-scaler clock */
    HW_WR_FIELD32(baseAddr + TIMER_TCLR,
                  TIMER_TCLR_PRE,
                  TIMER_TCLR_PRE_PRE_VALUE_0);
}

void TIMERCounterSet(uint32_t baseAddr, uint32_t counter)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCRR, baseAddr);

    /* Set the counter value */
    HW_WR_REG32(baseAddr + TIMER_TCRR, counter);
}

uint32_t TIMERCounterGet(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCRR, baseAddr);

    /* Read the counter value from TCRR */
    return (HW_RD_REG32(baseAddr + TIMER_TCRR));
}

void TIMERReloadSet(uint32_t baseAddr, uint32_t reload)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TLDR, baseAddr);

    /* Load the register with the re-load value */
    HW_WR_REG32(baseAddr + TIMER_TLDR, reload);
}

uint32_t TIMERReloadGet(uint32_t baseAddr)
{
    /* Return the contents of TLDR */
    return (HW_RD_REG32(baseAddr + TIMER_TLDR));
}

void TIMERGPOConfigure(uint32_t baseAddr, uint32_t gpoCfg)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Clear the GPO_CFG field of TCLR */
    HW_WR_FIELD32(baseAddr + TIMER_TCLR,
                  TIMER_TCLR_GPO_CFG,
                  TIMER_TCLR_GPO_CFG_GPO_CFG_0);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    /* Write to the gpoCfg field of TCLR */
    HW_WR_FIELD32(baseAddr + TIMER_TCLR,
                  TIMER_TCLR_GPO_CFG,
                  gpoCfg >> TIMER_TCLR_GPO_CFG_SHIFT);
}

void TIMERCompareSet(uint32_t baseAddr, uint32_t compareVal)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TMAR, baseAddr);

    /* Write the compare value to TMAR */
    HW_WR_REG32(baseAddr + TIMER_TMAR, compareVal);
}

uint32_t TIMERCompareGet(uint32_t baseAddr)
{
    /* Return the TMAR value */
    return (HW_RD_REG32(baseAddr + TIMER_TMAR));
}

void TIMERIntRawStatusSet(uint32_t baseAddr, uint32_t intFlags)
{
    /* Trigger the events in IRQSTATUS_RAW register */
    HW_WR_REG32(baseAddr + TIMER_IRQSTATUS_RAW,
                intFlags & (
                    TIMER_IRQSTATUS_RAW_MAT_IT_FLAG_MASK |
                    TIMER_IRQSTATUS_RAW_OVF_IT_FLAG_MASK |
                    TIMER_IRQSTATUS_RAW_TCAR_IT_FLAG_MASK));
}

uint32_t TIMERIntRawStatusGet(uint32_t baseAddr)
{
    /* Return the status of IRQSTATUS_RAW register */
    return (HW_RD_REG32(baseAddr + TIMER_IRQSTATUS_RAW));
}

uint32_t TIMERIntStatusGet(uint32_t baseAddr)
{
    /* Return the status of IRQSTATUS register */
    return (HW_RD_REG32(baseAddr + TIMER_IRQSTATUS));
}

void TIMERIntStatusClear(uint32_t baseAddr, uint32_t intFlags)
{
    /* Clear the interrupt status from IRQSTATUS register */
    HW_WR_REG32(baseAddr + TIMER_IRQSTATUS,
                intFlags & (TIMER_IRQSTATUS_TCAR_IT_FLAG_MASK |
                            TIMER_IRQSTATUS_OVF_IT_FLAG_MASK |
                            TIMER_IRQSTATUS_MAT_IT_FLAG_MASK));
}

void TIMERIntEnable(uint32_t baseAddr, uint32_t intFlags)
{
    /* Enable the Timer interrupts represented by intFlags */
    HW_WR_REG32(baseAddr + TIMER_IRQENABLE_SET,
                intFlags & (TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK |
                            TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK |
                            TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK));
}

void TIMERIntDisable(uint32_t baseAddr, uint32_t intFlags)
{
    /* Disable the Timer interrupts represented by intFlags */
    HW_WR_REG32(baseAddr + TIMER_IRQENABLE_CLR,
                intFlags & (TIMER_IRQENABLE_CLR_TCAR_EN_FLAG_MASK |
                            TIMER_IRQENABLE_CLR_OVF_EN_FLAG_MASK |
                            TIMER_IRQENABLE_CLR_MAT_EN_FLAG_MASK));
}

void TIMERWakeEnable(uint32_t baseAddr, uint32_t wakeFlags)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + TIMER_IRQWAKEEN);
    regVal |= wakeFlags & (TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK |
                           TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK |
                           TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK);
    /* Enable the Timer Wakeup events represented by wakeFlags */
    HW_WR_REG32(baseAddr + TIMER_IRQWAKEEN, regVal);
}

void TIMERWakeDisable(uint32_t baseAddr, uint32_t wakeFlags)
{
    uint32_t regVal, mask;

    mask = ~(wakeFlags & (TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK |
                          TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK |
                          TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK));
    regVal = HW_RD_REG32(baseAddr + TIMER_IRQWAKEEN) & mask;
    /* Disable the Timer Wakeup events represented by wakeFlags */
    HW_WR_REG32(baseAddr + TIMER_IRQWAKEEN, regVal);
}

void TIMERTriggerSet(uint32_t baseAddr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TTGR, baseAddr);

    /* Write a value to the register */
    HW_WR_REG32(baseAddr + TIMER_TTGR, TIMER_TTGR_TTGR_VALUE_MASK);
}

uint32_t TIMERIntEnableGet(uint32_t baseAddr)
{
    /* Return the status of register IRQENABLE_SET */
    return (HW_RD_REG32(baseAddr + TIMER_IRQENABLE_SET));
}

void TIMERResetConfigure(uint32_t baseAddr, uint32_t rstOption)
{
    /* Write the option sent by user to SFT field of TSICR */
    HW_WR_FIELD32(baseAddr + TIMER_TSICR,
                  TIMER_TSICR_SFT,
                  rstOption >> TIMER_TSICR_SFT_SHIFT);
}

void TIMERReset(uint32_t baseAddr)
{
    /* Reset the Timer module */
    HW_WR_FIELD32(baseAddr + TIMER_TIOCP_CFG,
                  TIMER_TIOCP_CFG_SOFTRESET,
                  TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1);

    while (TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1 ==
           HW_RD_FIELD32(baseAddr + TIMER_TIOCP_CFG,
                         TIMER_TIOCP_CFG_SOFTRESET))
    {
        /* Do nothing - Busy wait */
    }
}

void TIMERContextSave(uint32_t baseAddr, TIMERCONTEXT *contextPtr)
{
    contextPtr->tldr         = HW_RD_REG32(baseAddr + TIMER_TLDR);
    contextPtr->tmar         = HW_RD_REG32(baseAddr + TIMER_TMAR);
    contextPtr->irqenableset = HW_RD_REG32(baseAddr + TIMER_IRQENABLE_SET);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCRR, baseAddr);

    contextPtr->tcrr = HW_RD_REG32(baseAddr + TIMER_TCRR);
    contextPtr->tclr = HW_RD_REG32(baseAddr + TIMER_TCLR);
}

void TIMERContextRestore(uint32_t baseAddr, const TIMERCONTEXT *contextPtr)
{
    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TLDR, baseAddr);

    HW_WR_REG32(baseAddr + TIMER_TLDR, contextPtr->tldr);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TMAR, baseAddr);

    HW_WR_REG32(baseAddr + TIMER_TMAR, contextPtr->tmar);
    HW_WR_REG32(baseAddr + TIMER_IRQENABLE_SET, contextPtr->irqenableset);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCRR, baseAddr);

    HW_WR_REG32(baseAddr + TIMER_TCRR, contextPtr->tcrr);

    /* Wait for previous write to complete */
    TimerWaitForWrite(TIMER_WRITE_POST_TCLR, baseAddr);

    HW_WR_REG32(baseAddr + TIMER_TCLR, contextPtr->tclr);
}

void TIMERPostedModeConfig(uint32_t baseAddr, uint32_t postMode)
{
    /* Write to the POSTED field of TSICR */
    HW_WR_FIELD32(baseAddr + TIMER_TSICR,
                  TIMER_TSICR_POSTED,
                  postMode >> TIMER_TSICR_POSTED_SHIFT);
}

void TIMERReadModeConfig(uint32_t baseAddr, uint32_t readMode)
{
    /* Write to the POSTED field of TSICR */
    HW_WR_FIELD32(baseAddr + TIMER_TSICR,
                  TIMER_TSICR_READ_MODE,
                  readMode >> TIMER_TSICR_READ_MODE_SHIFT);
}

uint32_t TIMERWritePostedStatusGet(uint32_t baseAddr)
{
    /* Return the status of TWPS register */
    return (HW_RD_REG32(baseAddr + TIMER_TWPS));
}

void TIMERIdleModeConfigure(uint32_t baseAddr, uint32_t idleModeOption)
{
    /* Write to the EMUFREE field of TIOCP_CFG */
    HW_WR_FIELD32(baseAddr + TIMER_TIOCP_CFG,
                  TIMER_TIOCP_CFG_IDLEMODE,
                  idleModeOption);
}

void TIMEREmuModeConfigure(uint32_t baseAddr, uint32_t emuModeOption)
{
    /* Write to the EMUFREE field of TIOCP_CFG */
    HW_WR_FIELD32(baseAddr + TIMER_TIOCP_CFG,
                  TIMER_TIOCP_CFG_EMUFREE,
                  emuModeOption);
}

void TIMERTPIRSet(uint32_t baseAddr, uint32_t tpirVal)
{
    /* Loading the Positive increment Value in TPIR register */
    HW_WR_REG32(baseAddr + CSL_DMTIMER1MS_TPIR, tpirVal);

}

void TIMERTNIRSet(uint32_t baseAddr, uint32_t tnirVal)
{
    /* Loading the Negative increment Value in TNIR register */
    HW_WR_REG32(baseAddr + CSL_DMTIMER1MS_TNIR, tnirVal);
}

void TIMERTCVRSet(uint32_t baseAddr, uint32_t val)
{
    /*
    ** Loading the value to decide the next TCRR value will be sub period or
    ** the over period value.
    */
    HW_WR_REG32(baseAddr + CSL_DMTIMER1MS_TCVR, val);
}

void TIMERTOCRSet(uint32_t baseAddr, uint32_t val)
{
    /* Loading the value to mask the tick interrupt for 'val' no of ticks */
    HW_WR_FIELD32(baseAddr + CSL_DMTIMER1MS_TOCR,
                  CSL_DMTIMER1MS_TOCR_OVF_COUNTER_VALUE,
                  val);
}

uint32_t TIMERTOWRGet(uint32_t baseAddr)
{
    /* Gets the number of masked overflow interrupts. */
    return (HW_RD_FIELD32(baseAddr + CSL_DMTIMER1MS_TOWR,
            CSL_DMTIMER1MS_TOWR_OVF_WRAPPING_VALUE));
}

void TIMERTOWRSet(uint32_t baseAddr, uint32_t val)
{
    /* Setting the overflow count mask value in TOWR register*/
    HW_WR_FIELD32(baseAddr + CSL_DMTIMER1MS_TOWR,
                  CSL_DMTIMER1MS_TOWR_OVF_WRAPPING_VALUE,
                  val);
}

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */
static inline void TimerWaitForWrite(uint32_t reg, uint32_t baseAddr)
{
    if (0U != HW_RD_FIELD32(baseAddr + TIMER_TSICR, TIMER_TSICR_POSTED))
    {
        while ((uint32_t) 0U != (reg & TIMERWritePostedStatusGet(baseAddr)))
        {
            /* Do nothing - Busy wait */
        }
    }
}
/********************************* End of file ******************************/
