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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_TIMER Timer
 *
 *  @{
 */
/**
 *  \file   timer.h
 *
 *  \brief  Timer API prototypes and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 **/

#ifndef TIMER_H_
#define TIMER_H_

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
 * \name Values that can be passed to TIMERPreScalerClkEnable as ptv so as to derive
 *        Pre-Scalar clock from timer clock.
 *  @{
**/
/* \brief Value used to divide timer clock by 2 */
#define TIMER_PRESCALER_CLK_DIV_BY_2      ((0 << TIMER_TCLR_PTV_SHIFT) | \
                                           TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 4 */
#define TIMER_PRESCALER_CLK_DIV_BY_4        ((1 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 8 */
#define TIMER_PRESCALER_CLK_DIV_BY_8        ((2 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 16 */
#define TIMER_PRESCALER_CLK_DIV_BY_16       ((3 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 32 */
#define TIMER_PRESCALER_CLK_DIV_BY_32       ((4 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 64 */
#define TIMER_PRESCALER_CLK_DIV_BY_64       ((5 << TIMER_TCLR_PTV_SHIFT) | \
                                             TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 128 */
#define TIMER_PRESCALER_CLK_DIV_BY_128    ((6 << TIMER_TCLR_PTV_SHIFT) | \
                                           TIMER_TCLR_PRE_MASK)

/* \brief Value used to divide timer clock by 256 */
#define TIMER_PRESCALER_CLK_DIV_BY_256    ((7 << TIMER_TCLR_PTV_SHIFT) | \
                                           TIMER_TCLR_PRE_MASK)
/* @} */

/**
 * \name Values that can be passed to TIMERModeConfigure as timerMode.
 *  @{
**/
/* \brief Value used to enable the timer in one-shot and compare mode */
#define TIMER_ONESHOT_CMP_ENABLE          (TIMER_TCLR_CE_MASK)

/* \brief Value used to enable the timer only in one-shot mode */
#define TIMER_ONESHOT_NOCMP_ENABLE        (0x0000000)

/* \brief Value used to enable the timer in auto-reload and compare mode */
#define TIMER_AUTORLD_CMP_ENABLE          (TIMER_TCLR_AR_MASK | \
                                           TIMER_TCLR_CE_MASK)

/* \brief Value used to enable the timer only in auto-reload mode */
#define TIMER_AUTORLD_NOCMP_ENABLE        (TIMER_TCLR_AR_MASK)
/* @} */

/**
 * \name Values that can be passed to TIMERGPOConfigure as gpoCfg.
 *  @{
**/
/* \brief Value used to drive 0 on PORGPOCFG pin */
#define TIMER_GPO_CFG_0         (TIMER_TCLR_GPO_CFG_GPO_CFG_0)

/* \brief Value used to drive 1 on PORGPOCFG pin */
#define TIMER_GPO_CFG_1         (TIMER_TCLR_GPO_CFG_GPO_CFG_1 << \
                                 TIMER_TCLR_GPO_CFG_SHIFT)
/* @} */

/**
 * \name Values that can be passed to TIMERIntStatusClear/TIMERIntRawStatusSet/
 * as intFlags. Also these values can be used while checking the status got from
 * TIMERIntRawStatusGet/TIMERIntStatusGet.
 * Any combination is also followed.
 * Example- (TIMER_INT_TCAR_IT_FLAG | TIMER_INT_OVF_IT_FLAG)
 *  @{
**/
/* \brief Value used for capture event of Timer */
#define TIMER_INT_TCAR_IT_FLAG             ( \
        TIMER_IRQSTATUS_RAW_TCAR_IT_FLAG_MASK)

/* \brief Value used for overflow event of Timer */
#define TIMER_INT_OVF_IT_FLAG              ( \
        TIMER_IRQSTATUS_RAW_OVF_IT_FLAG_MASK)

/* \brief Value used for Match event of Timer */
#define TIMER_INT_MAT_IT_FLAG              ( \
        TIMER_IRQSTATUS_RAW_MAT_IT_FLAG_MASK)
/* @} */

/**
 * \name Values that can be passed to TIMERIntEnable/TIMERIntDisable as intFlags.
 * Also these values can be used while checking the status got from
 * TIMERIntEnableGet.
 * Any combination is also followed.
 * Example- (TIMER_INT_TCAR_EN_FLAG | TIMER_INT_OVF_EN_FLAG)
 *  @{
**/
/* \brief Value used for capture event of Timer */
#define TIMER_INT_TCAR_EN_FLAG             ( \
        TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK)

/* \brief Value used for overflow event of Timer */
#define TIMER_INT_OVF_EN_FLAG              ( \
        TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK)

/* \brief Value used for Match event of Timer */
#define TIMER_INT_MAT_EN_FLAG              ( \
        TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK)
/* @} */

/**
 * \name Values that can be passed to TIMERWakeEnable/TIMERWakeDisable as wakeFlags.
 * Any combination is also followed.
 * Example- (TIMER_WAKE_TCAR_FLAG | TIMER_WAKE_OVF_FLAG)
 *  @{
**/
/* \brief Value used for capture event of Timer */
#define TIMER_WAKE_TCAR_FLAG             ( \
        TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK)

/* \brief Value used for overflow event of Timer */
#define TIMER_WAKE_OVF_FLAG              ( \
        TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK)

/* \brief Value used for Match event of Timer */
#define TIMER_WAKE_MAT_FLAG              ( \
        TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK)
/* @} */

/**
 * \name Values that can be passed to TIMERResetConfigure as rstOption.
 *  @{
**/
/* \brief Value used to enable software reset for Timer */
#define TIMER_SFT_RESET_ENABLE             (TIMER_TSICR_SFT_MASK)

/* \brief Value used to disable software reset for Timer */
#define TIMER_SFT_RESET_DISABLE            (TIMER_TSICR_SFT_SFT_0)
/* @} */

/**
 * \name Values that can be used while checking the status received from
 * TIMERIsResetDone.
 *  @{
**/
/* \brief Value used to check whether reset is done */
#define TIMER_IS_RESET_DONE                ( \
        TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_0)

/* \brief Value used to check whether reset is ongoing */
#define TIMER_IS_RESET_ONGOING             ( \
        TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1)
/* @} */

/**
 * \brief Values that can be passed to TIMERPostedModeConfig as postMode.
 *  @{
**/
/* \brief Value used to enable the posted mode of operation */
#define TIMER_POSTED                       (TIMER_TSICR_POSTED_MASK)

/* \brief Value used to disable the posted mode of operation */
#define TIMER_NONPOSTED                    (TIMER_TSICR_POSTED_POSTED_VALUE_0)
/* @} */

/**
 * \name Values that can be passed to TIMERReadModeConfig as postMode.
 *  @{
**/
/* \brief Value used to enable the read mode of operation */
#define TIMER_READ_MODE_POSTED                       (TIMER_TSICR_READ_MODE_READ_MODE_VALUE_0)

/* \brief Value used to disable the read mode of operation */
#define TIMER_READ_MODE_NONPOSTED                    (TIMER_TSICR_READ_MODE_READ_MODE_VALUE_1)
/* @} */

/**
 * \name Values that can be used while checking status received from
 * TIMERWritePostedStatusGet API.
 *  @{
**/
/* \brief Value used to check the write posted condition for TMAR register */
#define TIMER_WRITE_POST_TMAR           ((uint32_t) TIMER_TWPS_W_PEND_TMAR_MASK)

/* \brief Value used to check the write posted condition for TTGR register */
#define TIMER_WRITE_POST_TTGR           ((uint32_t) TIMER_TWPS_W_PEND_TTGR_MASK)

/* \brief Value used to check the write posted condition for TLDR register */
#define TIMER_WRITE_POST_TLDR           ((uint32_t) TIMER_TWPS_W_PEND_TLDR_MASK)

/* \brief Value used to check the write posted condition for TCRR register */
#define TIMER_WRITE_POST_TCRR           ((uint32_t) TIMER_TWPS_W_PEND_TCRR_MASK)

/* \brief Value used to check the write posted condition for TCLR register */
#define TIMER_WRITE_POST_TCLR           ((uint32_t) TIMER_TWPS_W_PEND_TCLR_MASK)
/* @} */

/**
 * \name Values that can be passed to TIMERIdleModeConfigure as idleModeOption.
 *  @{
**/
/* \brief Value used to set Timer in Force-idle mode*/
#define TIMER_FORCE_IDLE            (TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X0)

/* \brief Value used to set Timer in No-idle mode*/
#define TIMER_NO_IDLE               (TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X1)

/* \brief Value used to set Timer in Smart-idle mode*/
#define TIMER_SMART_IDLE            (TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X2)

/* \brief Value used to set Timer in Smart-idle wake-up-capable mode*/
#define TIMER_SMART_IDLE_WAKEUP     (TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X3)
/* @} */

/**
 * \name Values that can be passed to TIMEREmuModeConfigure as emuModeOption.
 *  @{
**/
/* \brief Value used to freeze Timer in emulation mode*/
#define TIMER_FROZEN            (TIMER_TIOCP_CFG_EMUFREE_TIMER_FROZEN)

/* \brief Value used to free run Timer in emulation mode  */
#define TIMER_FREE              (TIMER_TIOCP_CFG_EMUFREE_TIMER_FREE)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief Structure to store the timer context
**/
typedef struct timerContext {
    uint32_t tldr;
    uint32_t tmar;
    uint32_t irqenableset;
    uint32_t tcrr;
    uint32_t tclr;
}TIMERCONTEXT;

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
extern void TIMEREnable(uint32_t baseAddr);

/**
 * \brief   This API will stop the timer.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
extern void TIMERDisable(uint32_t baseAddr);

/**
 * \brief   This API will configure the timer in combinations of
 *          'One Shot timer' and 'Compare' Mode or 'Auto-reload timer'
 *          and 'Compare' Mode.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
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
extern void TIMERModeConfigure(uint32_t baseAddr, uint32_t timerMode);

/**
 * \brief   This API will configure and enable the pre-scaler clock.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
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
extern void TIMERPreScalerClkEnable(uint32_t baseAddr, uint32_t ptv);

/**
 * \brief   This API will disable the pre-scaler clock.
 *
 * \param   baseAddr      Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
extern void TIMERPreScalerClkDisable(uint32_t baseAddr);

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
extern void TIMERCounterSet(uint32_t baseAddr, uint32_t counter);

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
extern uint32_t TIMERCounterGet(uint32_t baseAddr);

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
extern void TIMERReloadSet(uint32_t baseAddr, uint32_t reload);

/**
 * \brief   Get the reload count value from the timer load register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the value present in Timer Load Register.
 *
 **/
extern uint32_t TIMERReloadGet(uint32_t baseAddr);

/**
 * \brief   Configure general purpose output pin.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   gpoCfg        General purpose output.
 *
 * 'gpoCfg' can take the following values \n
 *    TIMER_GPO_CFG_0 - PORGPOCFG drives 0 \n
 *    TIMER_GPO_CFG_1 - PORGPOCFG drives 1 \n
 *
 * \return  None.
 *
 **/
extern void TIMERGPOConfigure(uint32_t baseAddr, uint32_t gpoCfg);

/**
 * \brief   Set the match register with the compare value.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   compareVal    Compare value.
 *
 * \return  None.
 *
 **/
extern void TIMERCompareSet(uint32_t baseAddr, uint32_t compareVal);

/**
 * \brief   Get the match register contents.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the match register contents.
 *
 **/
extern uint32_t TIMERCompareGet(uint32_t baseAddr);

/**
 * \brief   Trigger IRQ event by software.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
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
extern void TIMERIntRawStatusSet(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Read the status of IRQSTATUS_RAW register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the contents of IRQSTATUS_RAW register.
 *
 **/
extern uint32_t TIMERIntRawStatusGet(uint32_t baseAddr);

/**
 * \brief   Read the status of IRQ_STATUS register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of IRQSTATUS register.
 *
 **/
extern uint32_t TIMERIntStatusGet(uint32_t baseAddr);

/**
 * \brief   Clear the status of interrupt events.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
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
extern void TIMERIntStatusClear(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Enable the Timer interrupts.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
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
extern void TIMERIntEnable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Disable the Timer interrupts.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
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
extern void TIMERIntDisable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Enable the Timer Wakeup.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
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
extern void TIMERWakeEnable(uint32_t baseAddr, uint32_t wakeFlags);

/**
 * \brief   Disable the Timer Wakeup.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
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
extern void TIMERWakeDisable(uint32_t baseAddr, uint32_t wakeFlags);

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
extern void TIMERTriggerSet(uint32_t baseAddr);

/**
 * \brief   Read the status of IRQENABLE_SET register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of IRQENABLE_SET register.
 *
 **/
extern uint32_t TIMERIntEnableGet(uint32_t baseAddr);

/**
 * \brief   Enable/Disable software reset for Timer module.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   rstOption     Enable/Disable reset option for TIMER.
 *
 * 'rstOption' can take the following values \n
 *    TIMER_SFT_RESET_ENABLE - Software reset is enabled \n
 *    TIMER_SFT_RESET_DISABLE - Software reset is disabled \n
 *
 * \return  None.
 *
 **/
extern void TIMERResetConfigure(uint32_t baseAddr, uint32_t rstOption);

/**
 * \brief   Reset the Timer module.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  None.
 *
 **/
extern void TIMERReset(uint32_t baseAddr);

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
extern void TIMERContextSave(uint32_t baseAddr, TIMERCONTEXT *contextPtr);

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
extern void TIMERContextRestore(uint32_t            baseAddr,
                                const TIMERCONTEXT *contextPtr);

/**
 * \brief   Configure the posted mode of TIMER.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   postMode      Posted mode configuration.
 *
 * 'postMode' can take the following values \n
 *    TIMER_NONPOSTED - Posted mode not used \n
 *    TIMER_POSTED - Posted mode used \n
 *
 * \return  None.
 *
 **/
extern void TIMERPostedModeConfig(uint32_t baseAddr, uint32_t postMode);

/**
 * \brief   Read the status of Write Posted Status register.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 *
 * \return  This API returns the status of TWPS register.
 *
 **/
extern uint32_t TIMERWritePostedStatusGet(uint32_t baseAddr);

/**
 * \brief   Configure the timer idle mode.
 *
 * \param   baseAddr         Base Address of the Timer Module Register.
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
extern void TIMERIdleModeConfigure(uint32_t baseAddr, uint32_t idleModeOption);

/**
 * \brief   Configure the timer status in emulation mode.
 *
 * \param   baseAddr         Base Address of the Timer Module Register.
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
extern void TIMEREmuModeConfigure(uint32_t baseAddr, uint32_t emuModeOption);

/**
 * \brief   Configure the read mode of TIMER.
 *
 * \param   baseAddr       Base Address of the Timer Module Register.
 * \param   readMode      read mode configuration.
 *
 * 'readMode' can take the following values \n
 *    TIMER_READ_MODE_POSTED - Read mode Posted and Module configured in Non Posted mode \n
 *    TIMER_READ_MODE_NONPOSTED - Read mode non Posted and Module configured in Non Posted mode \n
 *
 * \return  None.
 *
 **/
extern void TIMERReadModeConfig(uint32_t baseAddr, uint32_t readMode);

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
extern void TIMERTPIRSet(uint32_t baseAddr, uint32_t tpirVal);

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
extern void TIMERTNIRSet(uint32_t baseAddr, uint32_t tnirVal);

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
extern void TIMERTCVRSet(uint32_t baseAddr, uint32_t val);

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
extern void TIMERTOCRSet(uint32_t baseAddr, uint32_t val);

/**
 * \brief   Read the number of masked overflow interrupts.
 *
 * \param   baseAddr     Base Address of the 1ms Timer Module Register.
 *
 * \return  Over flow wrapping value.
 *
 **/
extern uint32_t TIMERTOWRGet(uint32_t baseAddr);

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
extern void TIMERTOWRSet(uint32_t baseAddr, uint32_t val);

#ifdef __cplusplus
}
#endif
#endif
 /** @} */
/********************************* End of file ******************************/
