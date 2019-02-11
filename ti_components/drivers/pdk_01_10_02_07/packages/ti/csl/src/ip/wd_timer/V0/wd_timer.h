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
 *  \defgroup CSL_WD_TIMER WD Timer
 *
 *  @{
 */
/**
 *  \file   wd_timer.h
 *
 *  \brief  Watchdog timer APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 **/

#ifndef WD_TIMER_H_
#define WD_TIMER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_wd_timer.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \name Values that can be passed to WDTIMERPreScalerClkEnable API as ptv.
 *  @{
**/
/* \brief Divide functional clock by 1 */
#define WD_TIMER_PRESCALER_CLK_DIV_1        (uint32_t) (0x00000000U)

/* \brief Divide functional clock by 2 */
#define WD_TIMER_PRESCALER_CLK_DIV_2        (uint32_t) (0x00000004U)

/* \brief Divide functional clock by 4 */
#define WD_TIMER_PRESCALER_CLK_DIV_4        (uint32_t) (0x00000008U)

/* \brief Divide functional clock by 8 */
#define WD_TIMER_PRESCALER_CLK_DIV_8        (uint32_t) (0x0000000CU)

/* \brief Divide functional clock by 16 */
#define WD_TIMER_PRESCALER_CLK_DIV_16       (uint32_t) (0x00000010U)

/* \brief Divide functional clock by 32 */
#define WD_TIMER_PRESCALER_CLK_DIV_32       (uint32_t) (0x00000014U)

/* \brief Divide functional clock by 64 */
#define WD_TIMER_PRESCALER_CLK_DIV_64       (uint32_t) (0x00000018U)

/* \brief Divide functional clock by 128 */
#define WD_TIMER_PRESCALER_CLK_DIV_128      (uint32_t) (0x0000001CU)
/* @} */

/**
 * \brief Values that can be passed to WDTIMERIntRawStatusSet,
 * WDTIMERIntStatusClear APIs as intFlags.
 *  @{
**/
/* \brief Watchdog delay interrupt */
#define WD_TIMER_INT_DELAY              (WD_TIMER_WIRQSTATRAW_EVENT_DLY_MASK)

/* \brief Watchdog overflow interrupt */
#define WD_TIMER_INT_OVERFLOW           (WD_TIMER_WIRQSTATRAW_EVENT_OVF_MASK)

/* \brief Watchdog all interrupts */
#define WD_TIMER_INT_ALL                (WD_TIMER_INT_DELAY | \
                                         WD_TIMER_INT_OVERFLOW)
/* @} */

/**
 * \brief values passed to WDTIMERIntEnable as intFlags.
 *  @{
**/
/* \brief Enable delay interrupt */
#define WD_TIMER_INT_ENABLE_DELAY           (WD_TIMER_WIRQENSET_ENABLE_DLY_MASK)

/* \brief Enable overflow interrupt */
#define WD_TIMER_INT_ENABLE_OVRFLW          (WD_TIMER_WIRQENSET_ENABLE_OVF_MASK)

/* \brief Enable all interrupts */
#define WD_TIMER_INT_ENABLE_ALL             (WD_TIMER_INT_ENABLE_DELAY | \
                                             WD_TIMER_INT_ENABLE_OVRFLW)
/* @} */

/**
 * \brief Values passed to WDTIMERIntDisable as intFlags.
 *  @{
**/
/* \brief Disable delay interrupt */
#define WD_TIMER_INT_DISABLE_DELAY      (WD_TIMER_WIRQENCLR_ENABLE_DLY_MASK)

/* \brief Disable overflow interrupt */
#define WD_TIMER_INT_DISABLE_OVRFLW     (WD_TIMER_WIRQENCLR_ENABLE_OVF_MASK)

/* \brief Disable all interrupts */
#define WD_TIMER_INT_DISABLE_ALL        (WD_TIMER_INT_DISABLE_DELAY | \
                                         WD_TIMER_INT_DISABLE_OVRFLW)
/* @} */

/**
 * \brief Values to read the status of WDTIMERWritePostedStatusGet API.
 *  @{
**/
/* \brief Write pending for register WD_TIMER_WCLR */
#define WD_TIMER_WRITE_PENDING_WCLR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WCLR_MASK)

/* \brief Write pending for register WD_TIMER_WCRR */
#define WD_TIMER_WRITE_PENDING_WCRR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WCRR_MASK)

/* \brief Write pending for register WD_TIMER_WLDR */
#define WD_TIMER_WRITE_PENDING_WLDR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WLDR_MASK)

/* \brief Write pending for register WD_TIMER_WTGR */
#define WD_TIMER_WRITE_PENDING_WTGR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WTGR_MASK)

/* \brief Write pending for register WD_TIMER_WSPR */
#define WD_TIMER_WRITE_PENDING_WSPR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WSPR_MASK)

/* \brief Write pending for register WD_TIMER_WDLY */
#define WD_TIMER_WRITE_PENDING_WDLY \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WDLY_MASK)
/* @} */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Starts/Enables the watchdog timer.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WDTIMEREnable(uint32_t baseAddr);

/**
 * \brief   Stops/Disables the watchdog timer.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WDTIMERDisable(uint32_t baseAddr);

/**
 * \brief   Return the revision id of the SOC used.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  Returns the revision id  of the SOC used.
 *
 **/
uint32_t WDTIMERRevisionIDGet(uint32_t baseAddr);

/**
 * \brief   Reset the watchdog timer module.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WDTIMERReset(uint32_t baseAddr);

/**
 * \brief   This API will configure and enable the pre-scaler clock.
 *
 * \param   baseAddr      Base Address of the Watchdog Timer Module Register.
 * \param   ptv          Pre-scale clock Timer value.
 *
 * 'ptv' can take the following values \n
 *   WD_TIMER_PRESCALER_CLK_DIV_1   - WD_TIMER Functional clock divide by 1 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_2   - WD_TIMER Functional clock divide by 2 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_4   - WD_TIMER Functional clock divide by 4 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_8   - WD_TIMER Functional clock divide by 8 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_16  - WD_TIMER Functional clock divide by 16 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_32  - WD_TIMER Functional clock divide by 32 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_64  - WD_TIMER Functional clock divide by 64 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_128 - WD_TIMER Functional clock divide by 128\n
 *
 * \return  None.
 *
 **/
void WDTIMERPreScalerClkEnable(uint32_t baseAddr, uint32_t ptv);

/**
 * \brief   This API will disable the pre-scaler clock.
 *
 * \param   baseAddr      Base Address of the Watchdog Timer Module Register.
 *
 * \return  None.
 *
 **/
void WDTIMERPreScalerClkDisable(uint32_t baseAddr);

/**
 * \brief   Set/Write the Counter register with the counter value.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   countVal      Count value for the Watchdog Timer.
 *
 * \return  None.
 *
 **/
void WDTIMERCounterSet(uint32_t baseAddr, uint32_t countVal);

/**
 * \brief   Get/Read the counter value from the counter register.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the count value present in the Watchdog Timer
 *            Counter register.
 *
 **/
uint32_t WDTIMERCounterGet(uint32_t baseAddr);

/**
 * \brief   Set the reload count value in the Watchdog timer load register.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   reloadVal     The reload count value of the Watchdog timer.
 *
 * \return  None.
 *
 * \note:   It is recommended to not use reload value as 0xFFFFFFFF.
 *
 **/
void WDTIMERReloadSet(uint32_t baseAddr, uint32_t reloadVal);

/**
 * \brief   Get the reload count value from the Watchdog timer load register.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the value present in Watchdog Timer Load Register.
 *
 **/
uint32_t WDTIMERReloadGet(uint32_t baseAddr);

/**
 * \brief   Set/enable the trigger write access.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   trigVal       Value to be written to the WTGR register.
 *
 * \return  None.
 *
 * \note    This API should be called if the Watchdog timer WD_TIMER_WCRR
 *          register has to be loaded with the WD_TIMER_WLDR register before
 *          overflow occurs. If this API has to be called more than once in an
 *          application then ensure each time this API is called, pass a
 *          different value to the parameter 'trigVal' to ensure proper working.
 *
 **/
void WDTIMERTriggerSet(uint32_t baseAddr, uint32_t trigVal);

/**
 * \brief   Load the delay register of Watchdog timer with the delay value.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   delayVal      Delay value.
 *
 * \return  None.
 *
 **/
void WDTIMERDelaySet(uint32_t baseAddr, uint32_t delayVal);

/**
 * \brief   Return the delay register value of Watchdog timer.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the delay register(WD_TIMER_WDLY) value of Watchdog
 *          timer.
 *
 **/
uint32_t WDTIMERDelayGet(uint32_t baseAddr);

/**
 * \brief   Set IRQ status by software.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to trigger the events.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_DELAY - Set the status for delay interrupt \n
 *    WD_TIMER_INT_OVERFLOW - Set the status for overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntRawStatusSet(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Return the Raw IRQ status.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the status of the WD_TIMER_WIRQSTATRAW register.
 *
 **/
uint32_t WDTIMERIntRawStatusGet(uint32_t baseAddr);

/**
 * \brief   Read the status of WD_TIMER_WIRQSTAT register.
 *
 * \param   baseAddr       Base Address of the DMTimer Module Register.
 *
 * \return  This API returns the status of WD_TIMER_WIRQSTAT register.
 *
 **/
uint32_t WDTIMERIntStatusGet(uint32_t baseAddr);

/**
 * \brief   Clear IRQ status.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to clear the events.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_DELAY - Clear the status for delay interrupt \n
 *    WD_TIMER_INT_OVERFLOW - Clear the status for overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntStatusClear(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Enable Watchdog timer interrupts.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to enable interrupts.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_ENABLE_DELAY - Enable the delay interrupt \n
 *    WD_TIMER_INT_ENABLE_OVRFLW - Enable the overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntEnable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Used to check whether interrupts of Watchdog timer are enabled
 *          or disabled.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the status of WD_TIMER_WIRQENSET register.
 *
 **/
uint32_t WDTIMERIntEnableStatusGet(uint32_t baseAddr);

/**
 * \brief   Disable Watchdog timer interrupts.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to enable interrupts.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_DISABLE_DELAY - Disable the delay interrupt \n
 *    WD_TIMER_INT_DISABLE_OVRFLW - Disable the overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntDisable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief   Read the status of WD_TIMER_WWPS register.
 *
 * \param   baseAddr       Base Address of the Watchdog Timer Module Register.
 * \param   flags         Status of the particular field to be returned.
 *
 * 'flags' can take the following values \n
 *    WD_TIMER_WRITE_PENDING_WCLR - Write pending for register WD_TIMER_WCLR \n
 *    WD_TIMER_WRITE_PENDING_WCRR - Write pending for register WD_TIMER_WCRR \n
 *    WD_TIMER_WRITE_PENDING_WLDR - Write pending for register WD_TIMER_WLDR \n
 *    WD_TIMER_WRITE_PENDING_WTGR - Write pending for register WD_TIMER_WTGR \n
 *    WD_TIMER_WRITE_PENDING_WSPR - Write pending for register WD_TIMER_WSPR \n
 *    WD_TIMER_WRITE_PENDING_WDLY - Write pending for register WD_TIMER_WDLY \n
 *
 * \return  Returns the status of Write posted status(WD_TIMER_WWPS) register.
 *
 **/
uint32_t WDTIMERWritePostedStatusGet(uint32_t baseAddr, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif
 /** @} */
/********************************* End of file ******************************/
