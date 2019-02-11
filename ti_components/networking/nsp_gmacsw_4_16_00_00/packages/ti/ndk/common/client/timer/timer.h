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
 *  \file   timer.h
 *
 *  \brief  Timer API prototypes and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"
#include "hw_timer.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/*
** Values that can be passed to TIMERPreScalerClkEnable as ptv so as to derive
** Pre-Scalar clock from timer clock.
*/
/* Value used to divide timer clock by 2 */
#define TIMER_PRESCALER_CLK_DIV_BY_2      ((0 << TIMER_TCLR_PTV_SHIFT) | \
                                           TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 4 */
#define TIMER_PRESCALER_CLK_DIV_BY_4        ((1 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 8 */
#define TIMER_PRESCALER_CLK_DIV_BY_8        ((2 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 16 */
#define TIMER_PRESCALER_CLK_DIV_BY_16       ((3 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 32 */
#define TIMER_PRESCALER_CLK_DIV_BY_32       ((4 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 64 */
#define TIMER_PRESCALER_CLK_DIV_BY_64       ((5 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 128 */
#define TIMER_PRESCALER_CLK_DIV_BY_128    ((6 << TIMER_TCLR_PTV_SHIFT) | \
                                           TIMER_TCLR_PRE_MASK)

/* Value used to divide timer clock by 256 */
#define TIMER_PRESCALER_CLK_DIV_BY_256    ((7 << TIMER_TCLR_PTV_SHIFT) | \
                                           TIMER_TCLR_PRE_MASK)

/******************************************************************************/
/*
** Values that can be passed to TIMERModeConfigure as timerMode.
*/
/* Value used to enable the timer in one-shot and compare mode */
#define TIMER_ONESHOT_CMP_ENABLE          (TIMER_TCLR_CE_MASK)

/* Value used to enable the timer only in one-shot mode */
#define TIMER_ONESHOT_NOCMP_ENABLE        (0x0000000)

/* Value used to enable the timer in auto-reload and compare mode */
#define TIMER_AUTORLD_CMP_ENABLE          (TIMER_TCLR_AR_MASK | \
                                           TIMER_TCLR_CE_MASK)

/* Value used to enable the timer only in auto-reload mode */
#define TIMER_AUTORLD_NOCMP_ENABLE        (TIMER_TCLR_AR_MASK)

/******************************************************************************/
/*
** Values that can be passed to TIMERGPOConfigure as gpoCfg.
*/
/* Value used to drive 0 on PORGPOCFG pin */
#define TIMER_GPO_CFG_0         (TIMER_TCLR_GPO_CFG_GPO_CFG_0)

/* Value used to drive 1 on PORGPOCFG pin */
#define TIMER_GPO_CFG_1         (TIMER_TCLR_GPO_CFG_GPO_CFG_1 << \
                                 TIMER_TCLR_GPO_CFG_SHIFT)

/******************************************************************************/
/*
** Values that can be passed to TIMERIntStatusClear/TIMERIntRawStatusSet/
** as intFlags. Also these values can be used while checking the status got from
** TIMERIntRawStatusGet/TIMERIntStatusGet.
** Any combination is also followed.
** Example- (TIMER_INT_TCAR_IT_FLAG | TIMER_INT_OVF_IT_FLAG)
*/
/* Value used for capture event of Timer */
#define TIMER_INT_TCAR_IT_FLAG             ( \
        TIMER_IRQSTATUS_RAW_TCAR_IT_FLAG_MASK)

/* Value used for overflow event of Timer */
#define TIMER_INT_OVF_IT_FLAG              ( \
        TIMER_IRQSTATUS_RAW_OVF_IT_FLAG_MASK)

/* Value used for Match event of Timer */
#define TIMER_INT_MAT_IT_FLAG              ( \
        TIMER_IRQSTATUS_RAW_MAT_IT_FLAG_MASK)

/******************************************************************************/
/*
** Values that can be passed to TIMERIntEnable/TIMERIntDisable as intFlags.
** Also these values can be used while checking the status got from
** TIMERIntEnableGet.
** Any combination is also followed.
** Example- (TIMER_INT_TCAR_EN_FLAG | TIMER_INT_OVF_EN_FLAG)
*/
/* Value used for capture event of Timer */
#define TIMER_INT_TCAR_EN_FLAG             ( \
        TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK)

/* Value used for overflow event of Timer */
#define TIMER_INT_OVF_EN_FLAG              ( \
        TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK)

/* Value used for Match event of Timer */
#define TIMER_INT_MAT_EN_FLAG              ( \
        TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK)

/******************************************************************************/
/*
** Values that can be passed to TIMERResetConfigure as rstOption.
*/
/* Value used to enable software reset for Timer */
#define TIMER_SFT_RESET_ENABLE             (TIMER_TSICR_SFT_MASK)

/* Value used to disable software reset for Timer */
#define TIMER_SFT_RESET_DISABLE            (TIMER_TSICR_SFT_SFT_0)

/******************************************************************************/
/*
** Values that can be used while checking the status received from
** TIMERIsResetDone.
*/
/* Value used to check whether reset is done */
#define TIMER_IS_RESET_DONE                ( \
        TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_0)

/* Value used to check whether reset is ongoing */
#define TIMER_IS_RESET_ONGOING             ( \
        TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1)

/******************************************************************************/
/*
** Values that can be passed to TIMERPostedModeConfig as postMode.
*/
/* Value used to enable the posted mode of operation */
#define TIMER_POSTED                       (TIMER_TSICR_POSTED_MASK)

/* Value used to disable the posted mode of operation */
#define TIMER_NONPOSTED                    (TIMER_TSICR_POSTED_POSTED_VALUE_0)

/******************************************************************************/
/*
** Values that can be used while checking status received from
** TIMERWritePostedStatusGet API.
*/
/* Value used to check the write posted condition for TMAR register */
#define TIMER_WRITE_POST_TMAR           ((uint32_t) TIMER_TWPS_W_PEND_TMAR_MASK)

/* Value used to check the write posted condition for TTGR register */
#define TIMER_WRITE_POST_TTGR           ((uint32_t) TIMER_TWPS_W_PEND_TTGR_MASK)

/* Value used to check the write posted condition for TLDR register */
#define TIMER_WRITE_POST_TLDR           ((uint32_t) TIMER_TWPS_W_PEND_TLDR_MASK)

/* Value used to check the write posted condition for TCRR register */
#define TIMER_WRITE_POST_TCRR           ((uint32_t) TIMER_TWPS_W_PEND_TCRR_MASK)

/* Value used to check the write posted condition for TCLR register */
#define TIMER_WRITE_POST_TCLR           ((uint32_t) TIMER_TWPS_W_PEND_TCLR_MASK)

/******************************************************************************/
/*
** Values that can be passed to TIMEREmuModeConfigure as emuModeOption.
*/
/* Value used to freeze Timer in emulation mode*/
#define TIMER_FROZEN            (TIMER_TIOCP_CFG_EMUFREE_TIMER_FROZEN)

/* Value used to free run Timer in emulation mode  */
#define TIMER_FREE              (TIMER_TIOCP_CFG_EMUFREE_TIMER_FREE)

/******************************************************************************/
/*
** Structure to store the timer context
*/
  typedef struct timerContext
  {
    uint32_t tldr;
    uint32_t tmar;
    uint32_t irqenableset;
    uint32_t tcrr;
    uint32_t tclr;
  } TIMERCONTEXT;

/*
** Prototype of the APIs
*/
  extern void TIMEREnable (uint32_t baseAdd);
  extern void TIMERDisable (uint32_t baseAdd);
  extern void TIMERModeConfigure (uint32_t baseAdd, uint32_t timerMode);
  extern void TIMERPreScalerClkEnable (uint32_t baseAdd, uint32_t ptv);
  extern void TIMERPreScalerClkDisable (uint32_t baseAdd);
  extern void TIMERCounterSet (uint32_t baseAdd, uint32_t counter);
  extern uint32_t TIMERCounterGet (uint32_t baseAdd);
  extern void TIMERReloadSet (uint32_t baseAdd, uint32_t reload);
  extern uint32_t TIMERReloadGet (uint32_t baseAdd);
  extern void TIMERGPOConfigure (uint32_t baseAdd, uint32_t gpoCfg);
  extern void TIMERCompareSet (uint32_t baseAdd, uint32_t compareVal);
  extern uint32_t TIMERCompareGet (uint32_t baseAdd);
  extern void TIMEREmulationModeConfigure (uint32_t baseAdd,
                  uint32_t emuMode);
  extern void TIMERIntRawStatusSet (uint32_t baseAdd, uint32_t intFlags);
  extern uint32_t TIMERIntRawStatusGet (uint32_t baseAdd);
  extern uint32_t TIMERIntStatusGet (uint32_t baseAdd);
  extern void TIMERIntStatusClear (uint32_t baseAdd, uint32_t intFlags);
  extern void TIMERIntEnable (uint32_t baseAdd, uint32_t intFlags);
  extern void TIMERIntDisable (uint32_t baseAdd, uint32_t intFlags);
  extern void TIMERTriggerSet (uint32_t baseAdd);
  extern uint32_t TIMERIntEnableGet (uint32_t baseAdd);
  extern void TIMERResetConfigure (uint32_t baseAdd, uint32_t rstOption);
  extern void TIMERReset (uint32_t baseAdd);
  extern void TIMERContextSave (uint32_t baseAdd, TIMERCONTEXT * contextPtr);
  extern void TIMERContextRestore (uint32_t baseAdd,
               const TIMERCONTEXT * contextPtr);
  extern void TIMERPostedModeConfig (uint32_t baseAdd, uint32_t postMode);
  extern uint32_t TIMERWritePostedStatusGet (uint32_t baseAdd);
  extern void TIMEREmuModeConfigure (uint32_t baseAdd,
                 uint32_t emuModeOption);

#ifdef __cplusplus
}
#endif

#endif
