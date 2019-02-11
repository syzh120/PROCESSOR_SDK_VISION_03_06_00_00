/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include "timer.h"
#include "hw_types.h"

/*******************************************************************************
 *                       INTERNAL FUNCTION DECLARATIONS
 *******************************************************************************/

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
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
static inline void TimerWaitForWrite (uint32_t reg, uint32_t baseAdd);

/*******************************************************************************
 *                        API FUNCTION DEFINITIONS
 *******************************************************************************/

/**
 * \brief   This API will start the timer.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 * \note    The timer must be configured before it is started/enabled.
 *
 **/
void
TIMEREnable (uint32_t baseAdd)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Start the timer */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_ST, TIMER_TCLR_ST_ST_VALUE_1);
}

/**
 * \brief   This API will stop the timer.
 *
 * \param   baseAdd      Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
void
TIMERDisable (uint32_t baseAdd)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Stop the timer */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_ST, TIMER_TCLR_ST_ST_VALUE_0);
}

/**
 * \brief   This API will configure the timer in combinations of
 *          'One Shot timer' and 'Compare' Mode or 'Auto-reload timer'
 *          and 'Compare' Mode.
 *
 * \param   baseAdd      Base Address of the Timer Module Register.
 * \param   timerMode    Mode for enabling the timer.
 *
 * 'timerMode' can take the following values \n
 *    TIMER_ONESHOT_CMP_ENABLE - One shot and compare mode enabled \n
 *    TIMER_ONESHOT_NOCMP_ENABLE - One shot enabled, compare mode disabled \n
 *    TIMER_AUTORLD_CMP_ENABLE - Auto-reload and compare mode enabled \n
 *    TIMER_AUTORLD_NOCMP_ENABLE - Auto-reload enabled, compare mode
 *                                   disabled \n
 *
 * \return  None.
 *
 **/
void
TIMERModeConfigure (uint32_t baseAdd, uint32_t timerMode)
{
  uint32_t regVal;

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Clear the AR and CE field of TCLR */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_AR, TIMER_TCLR_AR_AR_VALUE_0);

  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_CE, TIMER_TCLR_CE_CE_VALUE_0);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Set the timer mode in TCLR register */
  regVal = HW_RD_REG32 (baseAdd + TIMER_TCLR);

  regVal |= (timerMode & (TIMER_TCLR_AR_MASK | TIMER_TCLR_CE_MASK));

  HW_WR_REG32 (baseAdd + TIMER_TCLR, regVal);
}

/**
 * \brief   This API will configure and enable the pre-scaler clock.
 *
 * \param   baseAdd      Base Address of the Timer Module Register.
 * \param   ptv          Pre-scale clock Timer value.
 *
 * 'ptv' can take the following values \n
 *    TIMER_PRESCALER_CLK_DIV_BY_2 - Timer clock divide by 2 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_4 - Timer clock divide by 4 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_8 - Timer clock divide by 8 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_16 - Timer clock divide by 16 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_32 - Timer clock divide by 32 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_64 - Timer clock divide by 64 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_128 - Timer clock divide by 128 \n
 *    TIMER_PRESCALER_CLK_DIV_BY_256 - Timer clock divide by 256 \n
 *
 * \return  None.
 *
 **/
void
TIMERPreScalerClkEnable (uint32_t baseAdd, uint32_t ptv)
{
  uint32_t regVal;

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Clear the PTV field of TCLR */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR, TIMER_TCLR_PTV, 0U);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Set the PTV field and enable the pre-scaler clock */
  regVal = HW_RD_REG32 (baseAdd + TIMER_TCLR);

  regVal |= (ptv & (TIMER_TCLR_PTV_MASK | TIMER_TCLR_PRE_MASK));

  HW_WR_REG32 (baseAdd + TIMER_TCLR, regVal);
}

/**
 * \brief   This API will disable the pre-scaler clock.
 *
 * \param   baseAdd      Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
void
TIMERPreScalerClkDisable (uint32_t baseAdd)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Disable Pre-scaler clock */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_PRE, TIMER_TCLR_PRE_PRE_VALUE_0);
}

/**
 * \brief   Set/Write the Counter register with the counter value.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   counter       Count value for the timer.
 *
 * \return  None.
 *
 * \note    Value can be loaded into the counter register when the counter is
 *          stopped or when it is running.
 **/
void
TIMERCounterSet (uint32_t baseAdd, uint32_t counter)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCRR, baseAdd);

  /* Set the counter value */
  HW_WR_REG32 (baseAdd + TIMER_TCRR, counter);
}

/**
 * \brief   Get/Read the counter value from the counter register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the count value present in the Timer Counter
 *          register.
 *
 * \note:   Value can be read from the counter register when the counter is
 *          stopped or when it is running.
 **/
uint32_t
TIMERCounterGet (uint32_t baseAdd)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCRR, baseAdd);

  /* Read the counter value from TCRR */
  return (HW_RD_REG32 (baseAdd + TIMER_TCRR));
}

/**
 * \brief   Set the reload count value in the timer load register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   reload        The reload count value of the timer.
 *
 * \return  None.
 *
 * \note:   It is recommended to not use reload value as 0xFFFFFFFF as it can
 *          lead to undesired results.
 **/
void
TIMERReloadSet (uint32_t baseAdd, uint32_t reload)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TLDR, baseAdd);

  /* Load the register with the re-load value */
  HW_WR_REG32 (baseAdd + TIMER_TLDR, reload);
}

/**
 * \brief   Get the reload count value from the timer load register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the value present in Timer Load Register.
 *
 **/
uint32_t
TIMERReloadGet (uint32_t baseAdd)
{
  /* Return the contents of TLDR */
  return (HW_RD_REG32 (baseAdd + TIMER_TLDR));
}

/**
 * \brief   Configure general purpose output pin.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   gpoCfg        General purpose output.
 *
 * 'gpoCfg' can take the following values \n
 *    TIMER_GPO_CFG_0 - PORGPOCFG drives 0 \n
 *    TIMER_GPO_CFG_1 - PORGPOCFG drives 1 \n
 *
 * \return  None.
 *
 **/
void
TIMERGPOConfigure (uint32_t baseAdd, uint32_t gpoCfg)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Clear the GPO_CFG field of TCLR */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_GPO_CFG, TIMER_TCLR_GPO_CFG_GPO_CFG_0);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  /* Write to the gpoCfg field of TCLR */
  HW_WR_FIELD32 (baseAdd + TIMER_TCLR,
       TIMER_TCLR_GPO_CFG, gpoCfg >> TIMER_TCLR_GPO_CFG_SHIFT);
}

/**
 * \brief   Set the match register with the compare value.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   compareVal    Compare value.
 *
 * \return  None.
 *
 **/
void
TIMERCompareSet (uint32_t baseAdd, uint32_t compareVal)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TMAR, baseAdd);

  /* Write the compare value to TMAR */
  HW_WR_REG32 (baseAdd + TIMER_TMAR, compareVal);
}

/**
 * \brief   Get the match register contents.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the match register contents.
 *
 **/
uint32_t
TIMERCompareGet (uint32_t baseAdd)
{
  /* Return the TMAR value */
  return (HW_RD_REG32 (baseAdd + TIMER_TMAR));
}

/**
 * \brief   Trigger IRQ event by software.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to trigger the events.
 *
 * 'intFlags' can take the following values \n
 *    TIMER_INT_TCAR_IT_FLAG - Trigger IRQ status for capture \n
 *    TIMER_INT_OVF_IT_FLAG - Trigger IRQ status for overflow \n
 *    TIMER_INT_MAT_IT_FLAG - Trigger IRQ status for match \n
 *
 * \return  None.
 *
 **/
void
TIMERIntRawStatusSet (uint32_t baseAdd, uint32_t intFlags)
{
  /* Trigger the events in IRQSTATUS_RAW register */
  HW_WR_REG32 (baseAdd + TIMER_IRQSTATUS_RAW,
          intFlags & (TIMER_IRQSTATUS_RAW_MAT_IT_FLAG_MASK |
            TIMER_IRQSTATUS_RAW_OVF_IT_FLAG_MASK |
            TIMER_IRQSTATUS_RAW_TCAR_IT_FLAG_MASK));
}

/**
 * \brief   Read the status of IRQSTATUS_RAW register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the contents of IRQSTATUS_RAW register.
 *
 **/
uint32_t
TIMERIntRawStatusGet (uint32_t baseAdd)
{
  /* Return the status of IRQSTATUS_RAW register */
  return (HW_RD_REG32 (baseAdd + TIMER_IRQSTATUS_RAW));
}

/**
 * \brief   Read the status of IRQ_STATUS register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of IRQSTATUS register.
 *
 **/
uint32_t
TIMERIntStatusGet (uint32_t baseAdd)
{
  /* Return the status of IRQSTATUS register */
  return (HW_RD_REG32 (baseAdd + TIMER_IRQSTATUS));
}

/**
 * \brief   Clear the status of interrupt events.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to clear the events.
 *
 * 'intFlags' can take the following values \n
 *    TIMER_INT_TCAR_IT_FLAG - Clear IRQ status for capture \n
 *    TIMER_INT_OVF_IT_FLAG - Clear IRQ status for overflow \n
 *    TIMER_INT_MAT_IT_FLAG - Clear IRQ status for match \n
 *
 * \return  None.
 *
 **/
void
TIMERIntStatusClear (uint32_t baseAdd, uint32_t intFlags)
{
  /* Clear the interrupt status from IRQSTATUS register */
  HW_WR_REG32 (baseAdd + TIMER_IRQSTATUS,
          intFlags & (TIMER_IRQSTATUS_TCAR_IT_FLAG_MASK |
            TIMER_IRQSTATUS_OVF_IT_FLAG_MASK |
            TIMER_IRQSTATUS_MAT_IT_FLAG_MASK));
}

/**
 * \brief   Enable the Timer interrupts.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to enable the interrupts.
 *
 * 'intFlags' can take the following values \n
 *    TIMER_INT_TCAR_EN_FLAG - IRQ enable for capture \n
 *    TIMER_INT_OVF_EN_FLAG - IRQ enable for overflow \n
 *    TIMER_INT_MAT_EN_FLAG - IRQ enable for match \n
 *
 * \return  None.
 *
 **/
void
TIMERIntEnable (uint32_t baseAdd, uint32_t intFlags)
{
  /* Enable the Timer interrupts represented by intFlags */
  HW_WR_REG32 (baseAdd + TIMER_IRQENABLE_SET,
          intFlags & (TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK |
            TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK |
            TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK));
}

/**
 * \brief   Disable the Timer interrupts.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to disable the interrupts.
 *
 * 'intFlags' can take the following values \n
 *    TIMER_INT_TCAR_EN_FLAG - IRQ disable for capture \n
 *    TIMER_INT_OVF_EN_FLAG - IRQ disable for overflow \n
 *    TIMER_INT_MAT_EN_FLAG - IRQ disable for match \n
 *
 * \return  None.
 *
 **/
void
TIMERIntDisable (uint32_t baseAdd, uint32_t intFlags)
{
  /* Disable the Timer interrupts represented by intFlags */
  HW_WR_REG32 (baseAdd + TIMER_IRQENABLE_CLR,
          intFlags & (TIMER_IRQENABLE_CLR_TCAR_EN_FLAG_MASK |
            TIMER_IRQENABLE_CLR_OVF_EN_FLAG_MASK |
            TIMER_IRQENABLE_CLR_MAT_EN_FLAG_MASK));
}

/**
 * \brief   Enable the Timer Wakeup.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   wakeFlags     Variable used to enable the Wakeup events.
 *
 * 'intFlags' can take the following values
 *    TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK - Wakeup enable for capture
 *    TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK - Wakeup enable for overflow
 *    TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK - Wakeup enable for match
 *
 * \return  None.
 *
 **/
void
TIMERWakeEnable (uint32_t baseAdd, uint32_t wakeFlags)
{
  uint32_t regVal;

  regVal = HW_RD_REG32 (baseAdd + TIMER_IRQWAKEEN);
  regVal |= wakeFlags & (TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK |
          TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK |
          TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK);
  /* Enable the Timer Wakeup events represented by wakeFlags */
  HW_WR_REG32 (baseAdd + TIMER_IRQWAKEEN, regVal);
}

/**
 * \brief   Disable the Timer Wakeup.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   wakeFlags     Variable used to disable the Wakeup events.
 *
 * 'intFlags' can take the following values
 *    TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK - Wakeup disable for capture
 *    TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK - Wakeup disable for overflow
 *    TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK - Wakeup disable for match
 *
 * \return  None.
 *
 **/
void
TIMERWakeDisable (uint32_t baseAdd, uint32_t wakeFlags)
{
  uint32_t regVal, mask;

  mask = ~(wakeFlags & (TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK |
         TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK |
         TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK));
  regVal = HW_RD_REG32 (baseAdd + TIMER_IRQWAKEEN) & mask;
  /* Disable the Timer Wakeup events represented by wakeFlags */
  HW_WR_REG32 (baseAdd + TIMER_IRQWAKEEN, regVal);
}

/**
 * \brief   Set/enable the trigger write access.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 * \note    When we have enabled the timer in Auto-reload mode, the value from
 *          TLDR is reloaded into TCRR when a overflow condition occurs. But if
 *           we want to load the contents from TLDR to TCRR before overflow
 *          occurs then call this API.
 **/
void
TIMERTriggerSet (uint32_t baseAdd)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TTGR, baseAdd);

  /* Write a value to the register */
  HW_WR_REG32 (baseAdd + TIMER_TTGR, TIMER_TTGR_TTGR_VALUE_MASK);
}

/**
 * \brief   Read the status of IRQENABLE_SET register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of IRQENABLE_SET register.
 *
 **/
uint32_t
TIMERIntEnableGet (uint32_t baseAdd)
{
  /* Return the status of register IRQENABLE_SET */
  return (HW_RD_REG32 (baseAdd + TIMER_IRQENABLE_SET));
}

/**
 * \brief   Enable/Disable software reset for Timer module.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   rstOption     Enable/Disable reset option for TIMER.
 *
 * 'rstOption' can take the following values \n
 *    TIMER_SFT_RESET_ENABLE - Software reset is enabled \n
 *    TIMER_SFT_RESET_DISABLE - Software reset is disabled \n
 *
 * \return  None.
 *
 **/
void
TIMERResetConfigure (uint32_t baseAdd, uint32_t rstOption)
{
  /* Write the option sent by user to SFT field of TSICR */
  HW_WR_FIELD32 (baseAdd + TIMER_TSICR,
       TIMER_TSICR_SFT, rstOption >> TIMER_TSICR_SFT_SHIFT);
}

/**
 * \brief   Reset the Timer module.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
void
TIMERReset (uint32_t baseAdd)
{
  /* Reset the Timer module */
  HW_WR_FIELD32 (baseAdd + TIMER_TIOCP_CFG,
       TIMER_TIOCP_CFG_SOFTRESET,
       TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1);

  while (TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1 ==
    HW_RD_FIELD32 (baseAdd + TIMER_TIOCP_CFG, TIMER_TIOCP_CFG_SOFTRESET))
    {
      /* Do nothing - Busy wait */
    }
}

/**
 * \brief   This API stores the context of the TIMER
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   contextPtr    Pointer to the structure where the DM timer context
 *                        need to be saved.
 *
 * \return  None.
 *
 **/
void
TIMERContextSave (uint32_t baseAdd, TIMERCONTEXT * contextPtr)
{
  contextPtr->tldr = HW_RD_REG32 (baseAdd + TIMER_TLDR);
  contextPtr->tmar = HW_RD_REG32 (baseAdd + TIMER_TMAR);
  contextPtr->irqenableset = HW_RD_REG32 (baseAdd + TIMER_IRQENABLE_SET);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCRR, baseAdd);

  contextPtr->tcrr = HW_RD_REG32 (baseAdd + TIMER_TCRR);
  contextPtr->tclr = HW_RD_REG32 (baseAdd + TIMER_TCLR);
}

/**
 * \brief   This API restores the context of the TIMER
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   contextPtr    Pointer to the structure where the DM timer context
 *                        need to be restored from.
 *
 * \return  None.
 *
 **/
void
TIMERContextRestore (uint32_t baseAdd, const TIMERCONTEXT * contextPtr)
{
  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TLDR, baseAdd);

  HW_WR_REG32 (baseAdd + TIMER_TLDR, contextPtr->tldr);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TMAR, baseAdd);

  HW_WR_REG32 (baseAdd + TIMER_TMAR, contextPtr->tmar);
  HW_WR_REG32 (baseAdd + TIMER_IRQENABLE_SET, contextPtr->irqenableset);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCRR, baseAdd);

  HW_WR_REG32 (baseAdd + TIMER_TCRR, contextPtr->tcrr);

  /* Wait for previous write to complete */
  TimerWaitForWrite (TIMER_WRITE_POST_TCLR, baseAdd);

  HW_WR_REG32 (baseAdd + TIMER_TCLR, contextPtr->tclr);
}

/**
 * \brief   Configure the posted mode of TIMER.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 * \param   postMode      Posted mode configuration.
 *
 * 'postMode' can take the following values \n
 *    TIMER_NONPOSTED - Posted mode not used \n
 *    TIMER_POSTED - Posted mode used \n
 *
 * \return  None.
 *
 **/
void
TIMERPostedModeConfig (uint32_t baseAdd, uint32_t postMode)
{
  /* Write to the POSTED field of TSICR */
  HW_WR_FIELD32 (baseAdd + TIMER_TSICR,
       TIMER_TSICR_POSTED, postMode >> TIMER_TSICR_POSTED_SHIFT);
}

/**
 * \brief   Read the status of Write Posted Status register.
 *
 * \param   baseAdd       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of TWPS register.
 *
 **/
uint32_t
TIMERWritePostedStatusGet (uint32_t baseAdd)
{
  /* Return the status of TWPS register */
  return (HW_RD_REG32 (baseAdd + TIMER_TWPS));
}

/**
 * \brief   Configure the timer idle mode.
 *
 * \param   baseAdd         Base Address of the Timer Module Register.
 *
 * \param   idleModeOption   Idle mode configuration.
 *
 * 'idleModeOption' can take the following values
 *    TIMER_FORCE_IDLE - Timer is in Force-idle Mode
 *    TIMER_NO_IDLE - Timer is in No-idle Mode
 *    TIMER_SMART_IDLE - Timer is in Smart-idle mode
 *    TIMER_SMART_IDLE_WAKEUP - Timer is in Smart-idle wake-up-capable mode
 *
 * \return  None.
 *
 **/
void
TIMERIdleModeConfigure (uint32_t baseAdd, uint32_t idleModeOption)
{
  /* Write to the EMUFREE field of TIOCP_CFG */
  HW_WR_FIELD32 (baseAdd + TIMER_TIOCP_CFG,
       TIMER_TIOCP_CFG_IDLEMODE, idleModeOption);
}

/**
 * \brief   Configure the timer status in emulation mode.
 *
 * \param   baseAdd         Base Address of the Timer Module Register.
 *
 * \param   emuModeOption   Emulation mode configuration.
 *
 * 'emuModeOption' can take the following values \n
 *    TIMER_FROZEN - Timer is frozen in emuMode \n
 *    TIMER_FREE - Timer is free in emuMode \n
 *
 * \return  None.
 *
 **/
void
TIMEREmuModeConfigure (uint32_t baseAdd, uint32_t emuModeOption)
{
  /* Write to the EMUFREE field of TIOCP_CFG */
  HW_WR_FIELD32 (baseAdd + TIMER_TIOCP_CFG,
       TIMER_TIOCP_CFG_EMUFREE, emuModeOption);
}

/*******************************************************************************
 *                       INTERNAL FUNCTION DEFINITIONS
 *******************************************************************************/

static inline void
TimerWaitForWrite (uint32_t reg, uint32_t baseAdd)
{
  if (0U != HW_RD_FIELD32 (baseAdd + TIMER_TSICR, TIMER_TSICR_POSTED))
    {
      while ((uint32_t) 0U != (reg & TIMERWritePostedStatusGet (baseAdd)))
   {
     /* Do nothing - Busy wait */
   }
    }
}
