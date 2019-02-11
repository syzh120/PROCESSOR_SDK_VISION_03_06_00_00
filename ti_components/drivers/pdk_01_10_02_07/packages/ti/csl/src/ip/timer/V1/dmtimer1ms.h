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
 *  \file   dmtimer1ms.h
 *
 *  \brief  Timer API prototypes and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 **/

#ifndef _DMTIMER1MS_H_
#define _DMTIMER1MS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_timer.h>
#include <ti/csl/hw_types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \name Values that can be passed to DMTIMER1MSPreScalerClkEnable as ptv so as to derive
 *        Pre-Scalar clock from timer clock.
 *  @{
**/
/* \brief Value used to divide timer clock by 2 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_2      ((0 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                           DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 4 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_4        ((1 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                             DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 8 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_8        ((2 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                             DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 16 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_16       ((3 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                             DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 32 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_32       ((4 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                             DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 64 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_64       ((5 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                             DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 128 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_128    ((6 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                           DMTIMER_1MS_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 256 */
#define DMTIMER1MS_PRESCALER_CLK_DIV_BY_256    ((7 << DMTIMER_1MS_TCLR_PTV_SHIFT) | \
                                           DMTIMER_1MS_TCLR_PRE_MASK)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSModeConfigure as timerMode.
 *  @{
**/
/* \brief Value used to enable the timer in one-shot and compare mode */
#define DMTIMER1MS_ONESHOT_CMP_ENABLE          (DMTIMER_1MS_TCLR_CE_MASK)

/* \brief Value used to enable the timer only in one-shot mode */
#define DMTIMER1MS_ONESHOT_NOCMP_ENABLE        (0x0000000)

/* \brief Value used to enable the timer in auto-reload and compare mode */
#define DMTIMER1MS_AUTORLD_CMP_ENABLE          (DMTIMER_1MS_TCLR_AR_MASK | \
                                           DMTIMER_1MS_TCLR_CE_MASK)

/* \brief Value used to enable the timer only in auto-reload mode */
#define DMTIMER1MS_AUTORLD_NOCMP_ENABLE        (DMTIMER_1MS_TCLR_AR_MASK)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSGPOConfigure as gpoCfg.
 *  @{
**/
/* \brief Value used to drive 0 on PORGPOCFG pin */
#define DMTIMER1MS_GPO_CFG_0         (DMTIMER_1MS_TCLR_GPO_CFG_0)

/* \brief Value used to drive 1 on PORGPOCFG pin */
#define DMTIMER1MS_GPO_CFG_1         (DMTIMER_1MS_TCLR_GPO_CFG_1 << \
                                      DMTIMER_1MS_TCLR_GPO_CFG_SHIFT)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSIntStatusClear
 * as intFlags. Also these values can be used while checking the status got from
 * TIMERIntRawStatusGet/TIMERIntStatusGet.
 * Any combination is also followed.
 * Example- (DMTIMER1MS_INT_TCAR_IT_FLAG | DMTIMER1MS_INT_OVF_IT_FLAG)
 *  @{
**/
/* \brief Value used for capture event of Timer */
#define DMTIMER1MS_INT_TCAR_IT_FLAG             ( \
        DMTIMER_1MS_TISR_TCAR_IT_FLAG_MASK)

/* \brief Value used for overflow event of Timer */
#define DMTIMER1MS_INT_OVF_IT_FLAG              ( \
        DMTIMER_1MS_TISR_OVF_IT_FLAG_MASK)

/* \brief Value used for Match event of Timer */
#define DMTIMER1MS_INT_MAT_IT_FLAG              ( \
        DMTIMER_1MS_TISR_MAT_IT_FLAG_MASK)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSIntEnable/DMTIMER1MSIntDisable as intFlags.
 * Also these values can be used while checking the status got from
 * TIMERIntEnableGet.
 * Any combination is also followed.
 * Example- (DMTIMER1MS_INT_TCAR_EN_FLAG | DMTIMER1MS_INT_OVF_EN_FLAG)
 *  @{
**/
/* \brief Value used for capture event of Timer */
#define DMTIMER1MS_INT_TCAR_EN_FLAG             ( \
        DMTIMER_1MS_TIER_TCAR_IT_ENA_MASK)

/* \brief Value used for overflow event of Timer */
#define DMTIMER1MS_INT_OVF_EN_FLAG              ( \
        DMTIMER_1MS_TIER_OVF_IT_ENA_MASK)

/* \brief Value used for Match event of Timer */
#define DMTIMER1MS_INT_MAT_EN_FLAG              ( \
        DMTIMER_1MS_TIER_MAT_IT_ENA_MASK)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSWakeEnable/DMTIMER1MSWakeDisable as wakeFlags.
 * Any combination is also followed.
 * Example- (DMTIMER1MS_WAKE_TCAR_FLAG | DMTIMER1MS_WAKE_OVF_FLAG)
 *  @{
**/
/* \brief Value used for capture event of Timer */
#define DMTIMER1MS_WAKE_TCAR_FLAG             ( \
        DMTIMER_1MS_TWER_TCAR_WUP_ENA_MASK)

/* \brief Value used for overflow event of Timer */
#define DMTIMER1MS_WAKE_OVF_FLAG              ( \
        DMTIMER_1MS_TWER_OVF_WUP_ENA_MASK)

/* \brief Value used for Match event of Timer */
#define DMTIMER1MS_WAKE_MAT_FLAG              ( \
        DMTIMER_1MS_TWER_MAT_WUP_ENA_MASK)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSResetConfigure as rstOption.
 *  @{
**/
/* \brief Value used to enable software reset for Timer */
#define DMTIMER1MS_SFT_RESET_ENABLE             (DMTIMER_1MS_TSICR_SFT_MASK)

/* \brief Value used to disable software reset for Timer */
#define DMTIMER1MS_SFT_RESET_DISABLE            (DMTIMER_1MS_TSICR_SFT_0)
/* @} */

/**
 * \brief Values that can be passed to TIMERPostedModeConfig as postMode.
 *  @{
**/
/* \brief Value used to enable the posted mode of operation */
#define DMTIMER1MS_POSTED                       (DMTIMER_1MS_TSICR_POSTED_MASK)

/* \brief Value used to disable the posted mode of operation */
#define DMTIMER1MS_NONPOSTED                    (DMTIMER_1MS_TSICR_POSTED_0)
/* @} */

/**
 * \name Values that can be used while checking status received from
 * DMTIMER1MSWritePostedStatusGet API.
 *  @{
**/
/* \brief Value used to check the write posted condition for TMAR register */
#define DMTIMER1MS_WRITE_POST_TMAR           ((uint32_t) DMTIMER_1MS_TWPS_W_PEND_TMAR_MASK)

/* \brief Value used to check the write posted condition for TTGR register */
#define DMTIMER1MS_WRITE_POST_TTGR           ((uint32_t) DMTIMER_1MS_TWPS_W_PEND_TTGR_MASK)

/* \brief Value used to check the write posted condition for TLDR register */
#define DMTIMER1MS_WRITE_POST_TLDR           ((uint32_t) DMTIMER_1MS_TWPS_W_PEND_TLDR_MASK)

/* \brief Value used to check the write posted condition for TCRR register */
#define DMTIMER1MS_WRITE_POST_TCRR           ((uint32_t) DMTIMER_1MS_TWPS_W_PEND_TCRR_MASK)

/* \brief Value used to check the write posted condition for TCLR register */
#define DMTIMER1MS_WRITE_POST_TCLR           ((uint32_t) DMTIMER_1MS_TWPS_W_PEND_TCLR_MASK)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSIdleModeConfigure as idleModeOption.
 *  @{
**/
/* \brief Value used to set Timer in Force-idle mode*/
#define DMTIMER1MS_FORCE_IDLE            (DMTIMER_1MS_TIOCP_CFG_IDLEMODE_FIDLE)

/* \brief Value used to set Timer in No-idle mode*/
#define DMTIMER1MS_NO_IDLE               (DMTIMER_1MS_TIOCP_CFG_IDLEMODE_NIDLE)

/* \brief Value used to set Timer in Smart-idle mode*/
#define DMTIMER1MS_SMART_IDLE            (DMTIMER_1MS_TIOCP_CFG_IDLEMODE_SIDLE)

/* \brief Value used to set Timer in Smart-idle wake-up-capable mode*/
#define DMTIMER1MS_SMART_IDLE_WAKEUP     (DMTIMER_1MS_TIOCP_CFG_IDLEMODE_RES)
/* @} */

/**
 * \name Values that can be passed to DMTIMER1MSEmuModeConfigure as emuModeOption.
 *  @{
**/
/* \brief Value used to freeze Timer in emulation mode*/
#define DMTIMER1MS_FROZEN            (DMTIMER_1MS_TIOCP_CFG_EMUFREE_TIMER_FROZEN)

/* \brief Value used to free run Timer in emulation mode  */
#define DMTIMER1MS_FREE              (DMTIMER_1MS_TIOCP_CFG_EMUFREE_TIMER_FREE)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief Structure to store the timer context
**/
typedef struct dmtimer1msContext {
    uint32_t tldr;
    uint32_t tmar;
    uint32_t irqenableset;
    uint32_t tcrr;
    uint32_t tclr;
}DMTIMER1MSCONTEXT;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API will start the timer.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 * \note    The timer must be configured before it is started/enabled.
 *
 **/
extern void DMTIMER1MSEnable(uint32_t baseAddr);

/**
 * \brief   This API will stop the timer.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSDisable(uint32_t baseAddr);

/**
 * \brief   This API will configure the timer in combinations of
 *          'One Shot timer' and 'Compare' Mode or 'Auto-reload timer'
 *          and 'Compare' Mode.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
 * \param   timerMode    Mode for enabling the timer.
 *
 * 'timerMode' can take the following values \n
 *    DMTIMER1MS_ONESHOT_CMP_ENABLE - One shot and compare mode enabled \n
 *    DMTIMER1MS_ONESHOT_NOCMP_ENABLE - One shot enabled, compare mode disabled \n
 *    DMTIMER1MS_AUTORLD_CMP_ENABLE - Auto-reload and compare mode enabled \n
 *    DMTIMER1MS_AUTORLD_NOCMP_ENABLE - Auto-reload enabled, compare mode
 *                                   disabled \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSModeConfigure(uint32_t baseAddr, uint32_t timerMode);

/**
 * \brief   This API will configure and enable the pre-scaler clock.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
 * \param   ptv          Pre-scale clock Timer value.
 *
 * 'ptv' can take the following values \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_2 - Timer clock divide by 2 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_4 - Timer clock divide by 4 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_8 - Timer clock divide by 8 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_16 - Timer clock divide by 16 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_32 - Timer clock divide by 32 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_64 - Timer clock divide by 64 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_128 - Timer clock divide by 128 \n
 *    DMTIMER1MS_PRESCALER_CLK_DIV_BY_256 - Timer clock divide by 256 \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSPreScalerClkEnable(uint32_t baseAddr, uint32_t ptv);

/**
 * \brief   This API will disable the pre-scaler clock.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSPreScalerClkDisable(uint32_t baseAddr);

/**
 * \brief   Set/Write the Counter register with the counter value.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   counter       Count value for the timer.
 *
 * \return  None.
 *
 * \note    Value can be loaded into the counter register when the counter is
 *          stopped or when it is running.
 **/
extern void DMTIMER1MSCounterSet(uint32_t baseAddr, uint32_t counter);

/**
 * \brief   Get/Read the counter value from the counter register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the count value present in the Timer Counter
 *          register.
 *
 * \note:   Value can be read from the counter register when the counter is
 *          stopped or when it is running.
 **/
extern uint32_t DMTIMER1MSCounterGet(uint32_t baseAddr);

/**
 * \brief   Set the reload count value in the timer load register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   reload        The reload count value of the timer.
 *
 * \return  None.
 *
 * \note:   It is recommended to not use reload value as 0xFFFFFFFF as it can
 *          lead to undesired results.
 **/
extern void DMTIMER1MSReloadSet(uint32_t baseAddr, uint32_t reload);

/**
 * \brief   Get the reload count value from the timer load register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the value present in Timer Load Register.
 *
 **/
extern uint32_t DMTIMER1MSReloadGet(uint32_t baseAddr);

/**
 * \brief   Configure general purpose output pin.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   gpoCfg        General purpose output.
 *
 * 'gpoCfg' can take the following values \n
 *    DMTIMER1MS_GPO_CFG_0 - PORGPOCFG drives 0 \n
 *    DMTIMER1MS_GPO_CFG_1 - PORGPOCFG drives 1 \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSGPOConfigure(uint32_t baseAddr, uint32_t gpoCfg);

/**
 * \brief   Set the match register with the compare value.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   compareVal    Compare value.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSCompareSet(uint32_t baseAddr, uint32_t compareVal);

/**
 * \brief   Get the match register contents.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the match register contents.
 *
 **/
extern uint32_t DMTIMER1MSCompareGet(uint32_t baseAddr);

/**
 * \brief   Read the status of IRQ_STATUS register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of IRQSTATUS register.
 *
 **/
extern uint32_t DMTIMER1MSIntStatusGet(uint32_t baseAddr);

/**
 * \brief   Clear the status of interrupt events.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to clear the events.
 *
 * 'intFlags' can take the following values \n
 *    DMTIMER1MS_INT_TCAR_IT_FLAG - Clear IRQ status for capture \n
 *    DMTIMER1MS_INT_OVF_IT_FLAG - Clear IRQ status for overflow \n
 *    DMTIMER1MS_INT_MAT_IT_FLAG - Clear IRQ status for match \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSIntStatusClear(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Enable the Timer interrupts.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to enable the interrupts.
 *
 * 'intFlags' can take the following values \n
 *    DMTIMER1MS_INT_TCAR_EN_FLAG - IRQ enable for capture \n
 *    DMTIMER1MS_INT_OVF_EN_FLAG - IRQ enable for overflow \n
 *    DMTIMER1MS_INT_MAT_EN_FLAG - IRQ enable for match \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSIntEnable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Disable the Timer interrupts.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   intFlags      Variable used to disable the interrupts.
 *
 * 'intFlags' can take the following values \n
 *    DMTIMER1MS_INT_TCAR_EN_FLAG - IRQ disable for capture \n
 *    DMTIMER1MS_INT_OVF_EN_FLAG - IRQ disable for overflow \n
 *    DMTIMER1MS_INT_MAT_EN_FLAG - IRQ disable for match \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSIntDisable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Enable the Timer Wakeup.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   wakeFlags     Variable used to enable the Wakeup events.
 *
 * 'intFlags' can take the following values
 *    DMTIMER_1MS_TWER_TCAR_WUP_ENA_MASK - Wakeup enable for capture
 *    DMTIMER_1MS_TWER_OVF_WUP_ENA_MASK - Wakeup enable for overflow
 *    DMTIMER_1MS_TWER_MAT_WUP_ENA_MASK - Wakeup enable for match
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSWakeEnable(uint32_t baseAddr, uint32_t wakeFlags);

/**
 * \brief   Disable the Timer Wakeup.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   wakeFlags     Variable used to disable the Wakeup events.
 *
 * 'intFlags' can take the following values
 *    DMTIMER_1MS_TWER_TCAR_WUP_ENA_MASK - Wakeup disable for capture
 *    DMTIMER_1MS_TWER_OVF_WUP_ENA_MASK - Wakeup disable for overflow
 *    DMTIMER_1MS_TWER_MAT_WUP_ENA_MASK - Wakeup disable for match
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSWakeDisable(uint32_t baseAddr, uint32_t wakeFlags);

/**
 * \brief   Set/enable the trigger write access.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 * \note    When we have enabled the timer in Auto-reload mode, the value from
 *          TLDR is reloaded into TCRR when a overflow condition occurs. But if
 *           we want to load the contents from TLDR to TCRR before overflow
 *          occurs then call this API.
 **/
extern void DMTIMER1MSTriggerSet(uint32_t baseAddr);

/**
 * \brief   Read the status of IRQENABLE_SET register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of IRQENABLE_SET register.
 *
 **/
extern uint32_t DMTIMER1MSIntEnableGet(uint32_t baseAddr);

/**
 * \brief   Enable/Disable software reset for Timer module.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   rstOption     Enable/Disable reset option for TIMER.
 *
 * 'rstOption' can take the following values \n
 *    DMTIMER1MS_SFT_RESET_ENABLE - Software reset is enabled \n
 *    DMTIMER1MS_SFT_RESET_DISABLE - Software reset is disabled \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSResetConfigure(uint32_t baseAddr, uint32_t rstOption);

/**
 * \brief   Reset the Timer module.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSReset(uint32_t baseAddr);

/**
 * \brief   This API stores the context of the TIMER
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   contextPtr    Pointer to the structure where the DM timer context
 *                        need to be saved.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSContextSave(uint32_t baseAddr, DMTIMER1MSCONTEXT *contextPtr);

/**
 * \brief   This API restores the context of the TIMER
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   contextPtr    Pointer to the structure where the DM timer context
 *                        need to be restored from.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSContextRestore(uint32_t            baseAddr,
                                const DMTIMER1MSCONTEXT *contextPtr);

/**
 * \brief   Configure the posted mode of TIMER.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   postMode      Posted mode configuration.
 *
 * 'postMode' can take the following values \n
 *    DMTIMER1MS_NONPOSTED - Posted mode not used \n
 *    DMTIMER1MS_POSTED - Posted mode used \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSPostedModeConfig(uint32_t baseAddr, uint32_t postMode);

/**
 * \brief   Read the status of Write Posted Status register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of TWPS register.
 *
 **/
extern uint32_t DMTIMER1MSWritePostedStatusGet(uint32_t baseAddr);

/**
 * \brief   Configure the timer idle mode.
 *
 * \param   baseAddr         Base Address of the Timer Module Register.
 *
 * \param   idleModeOption   Idle mode configuration.
 *
 * 'idleModeOption' can take the following values
 *    DMTIMER1MS_FORCE_IDLE - Timer is in Force-idle Mode
 *    DMTIMER1MS_NO_IDLE - Timer is in No-idle Mode
 *    DMTIMER1MS_SMART_IDLE - Timer is in Smart-idle mode
 *    DMTIMER1MS_SMART_IDLE_WAKEUP - Timer is in Smart-idle wake-up-capable mode
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSIdleModeConfigure(uint32_t baseAddr, uint32_t idleModeOption);

/**
 * \brief   Configure the timer status in emulation mode.
 *
 * \param   baseAddr         Base Address of the Timer Module Register.
 *
 * \param   emuModeOption   Emulation mode configuration.
 *
 * 'emuModeOption' can take the following values \n
 *    DMTIMER1MS_FROZEN - Timer is frozen in emuMode \n
 *    DMTIMER1MS_FREE - Timer is free in emuMode \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSEmuModeConfigure(uint32_t baseAddr, uint32_t emuModeOption);

/**
 * \brief   Configure the read mode of TIMER.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   readMode      read mode configuration.
 *
 * 'readMode' can take the following values \n
 *    DMTIMER1MS_READ_MODE_POSTED - Read mode Posted and Module configured in Non Posted mode \n
 *    DMTIMER1MS_READ_MODE_NONPOSTED - Read mode non Posted and Module configured in Non Posted mode \n
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSReadModeConfig(uint32_t baseAddr, uint32_t readMode);

/**
 * \brief   Configure the positive increment value which is added TCVR to
 *          determine whether next value is subperiod or overperiod value.
 *
 * \param   baseAddr        Base Address of the 1ms Timer Module Register.
 *
 * \param   tpirVal         The Positive increment value.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSTPIRSet(uint32_t baseAddr, uint32_t tpirVal);

/**
 * \brief   Configure the negative increment value which is added TCVR to
 *          determine whether next value is subperiod or overperiod value.
 *
 * \param   baseAddr         Base Address of the 1ms Timer Module Register.
 *
 * \param   tnirVal          The negative increment value
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSTNIRSet(uint32_t baseAddr, uint32_t tnirVal);

/**
 * \brief   Configure the TCVR counter value.
 *
 * \param   baseAddr         Base Address of 1ms the Timer Module Register.
 *
 * \param   val             The TCVR value.
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSTCVRSet(uint32_t baseAddr, uint32_t val);

/**
 * \brief   Configure the number of ticks for which the tick interrupt has to be
 *          masked
 *
 * \param   baseAddr        Base Address of the 1ms Timer Module Register.
 *
 * \param   val             Value representing the number of ticks to be masked
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSTOCRSet(uint32_t baseAddr, uint32_t val);

/**
 * \brief   Read the number of masked overflow interrupts.
 *
 * \param   baseAddr     Base Address of the 1ms Timer Module Register.
 *
 * \return  Over flow wrapping value.
 *
 **/
extern uint32_t DMTIMER1MSTOWRGet(uint32_t baseAddr);

/**
 * \brief   Configure the overflow count mask value in TOWR register.
 *
 * \param   baseAddr     Base Address of the 1ms Timer Module Register.
 *
 * \param   val          Value representing the number of ticks to be masked
 *
 * \return  None.
 *
 **/
extern void DMTIMER1MSTOWRSet(uint32_t baseAddr, uint32_t val);

#ifdef __cplusplus
}
#endif
#endif
/********************************* End of file ******************************/
