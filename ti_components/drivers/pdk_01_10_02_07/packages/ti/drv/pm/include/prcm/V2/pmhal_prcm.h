/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 *  \addtogroup MISC Infrastructure and Domain List
 *
 * @{
 */

/**
 *  \file      V2/pmhal_prcm.h
 *
 *  \brief     This file contains enumeration declarations for different
 *             elements of PRCM like clock, module, power domain, etc.
 *             which uniquely identifies each element of PRCM.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *             If manual changes are required the implications of the
 *             change in this and other auto generated files has to be
 *             completely understood.
 */

#ifndef PMHAL_PRCM_H_
#define PMHAL_PRCM_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm_modinc.h>
#include <ti/drv/pm/include/pm_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/** \brief PMHAL_PRCM_AUTO_DPLL_MODE_DISABLE: Macro defining the value for dpll
 *          auto mode disabled  */
#define PMHAL_PRCM_AUTO_DPLL_MODE_DISABLE   (0U)

/** \brief PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM: Macro defining the number
 *          of CPU resets that a CPU subsystem can have.
 */
#define PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM (2U)

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 *  \brief Enum defining Idle Mode of a module- values are
 *         mapped from register description
 */
typedef enum pmhalPrcmModuleMStbyMode
{
    PMHAL_PRCM_MODULE_MSTANDBYMODE_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY =
        PMHAL_PRCM_MODULE_MSTANDBYMODE_MIN,
    /**< Forced StandBy Mode */
    PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY = 0x1U,
    /**< No StandBy Mode */
    PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY = 0x2U,
    /**< Smart StandBy Mode */
    PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY_WAKEUP_CAPABLE = 0x3U,
    /**< Smart Standby WakeUp Mode */
    PMHAL_PRCM_MODULE_MSTANDBYMODE_MAX =
        PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY_WAKEUP_CAPABLE,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID = 0xFF
                                             /**< Invalid value of the enum. Can
                                              * be used for validation. */
} pmhalPrcmModuleMStbyMode_t;

/**
 *  \brief Enum defining different modes of a module.
 */
typedef enum pmhalPrcmModuleSModuleMode
{
    PMHAL_PRCM_MODULE_MODE_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_MODE_DISABLED = PMHAL_PRCM_MODULE_MODE_MIN,
    /**< Disabled: Any access to module registers will result in error */
    PMHAL_PRCM_MODULE_MODE_AUTO = 0x1U,
    /**< Auto: Clocks will be gated automatically when there is no activity and
     *   enabled when there is an activity. */
    PMHAL_PRCM_MODULE_MODE_ENABLED = 0x2U,
    /**< Enabled: Functional and interface clocks are available and access to
     *   module registers are permitted. */
    PMHAL_PRCM_MODULE_MODE_MAX = PMHAL_PRCM_MODULE_MODE_ENABLED
                                 /**< Max value of the enum. Can be used for
                                  *   validation. */
} pmhalPrcmModuleSModuleMode_t;

/**
 *  \brief Enum defining Idle Mode of a module- values are
 *         mapped from register description
 */
typedef enum pmhalPrcmModuleSIdleMode
{
    PMHAL_PRCM_MODULE_SIDLEMODE_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE = PMHAL_PRCM_MODULE_SIDLEMODE_MIN,
    /**< PM HAL Prcm Module SIdleMode set to Force Idle mode */
    PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE = 0x1U,
    /**< PM HAL Prcm Module SIdleMode set to No Idle mode */
    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE = 0x2U,
    /**< PM HAL Prcm Module SIdleMode set to Smart Idle mode*/
    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE = 0x3U,
    /**< PM HAL Prcm Module SIdleMode set to Smart Idle wakeup mode */
    PMHAL_PRCM_MODULE_SIDLEMODE_MAX =
        PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_SIDLEMODE_INVALID = 0xFF
                                          /**< Enum for invalid . Can be used
                                           * for validation. */
} pmhalPrcmModuleSIdleMode_t;

/**
 *  \brief Enum defining idle states of the module. These values can be used to
 *         check the state of the module after configuring the module mode
 *         property.
 */
typedef enum pmhalPrcmModuleSIdleState
{
    PMHAL_PRCM_MODULE_IDLEST_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL = PMHAL_PRCM_MODULE_IDLEST_MIN,
    /**< Module is functional and can be accessed */
    PMHAL_PRCM_MODULE_SIDLESTATE_INTRANSITION = 0x1U,
    /**< Module is performing transition: wakeup, or sleep,or sleep abortion */
    PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE = 0x2U,
    /**< Module is in Idle mode (only interface part). It is functional if it
     *   uses separate functional clock  */
    PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED = 0x3U,
    /**< Module is in Idle mode (both functional and Interface) */
    PMHAL_PRCM_MODULE_IDLEST_MAX = PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED,
    /**< Max value of the enum. Can be used for
     * validation. */
    PMHAL_PRCM_MODULE_SIDLESTATE_DETERMINED_BY_CLK_STATE =
        PMHAL_PRCM_MODULE_IDLEST_MAX + 1U,
    /**< Used when there is no CLKCTRL register. The module state is
     * determined
     *   by the clock state. Used in PMLIBSysConfig. */
    PMHAL_PRCM_MODULE_SIDLESTATE_UNDEFINED = 0x7FFFFFFFU
                                             /** Undefined Sidle State */
} pmhalPrcmModuleSIdleState_t;

/**
 *  \brief Enum defining standby states of the module (Master only). These
 *         values can be used to check the state of the module after
 *         configuring the module mode property.
 */
typedef enum pmhalPrcmModuleMStbyState
{
    PMHAL_PRCM_CLKCTRL_STBYST_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL = PMHAL_PRCM_CLKCTRL_STBYST_MIN,
    /**< When master module wants to initiate a transaction on the device
     *   interconnect and it requests specific (functional and interface)
     *   clocks for that purpose. The PRCM module ensures that the required
     *   clocks are active and the module is said to be functional after this
     *   transition completes. */
    PMHAL_PRCM_MODULE_MSTANDBYSTATE_STANDBY = 0x1U,
    /**< When the master module no longer requires the clocks, it informs the
     *   PRCM module, which can then gate the clocks to the module. */
    PMHAL_PRCM_CLKCTRL_STBYST_MAX = PMHAL_PRCM_MODULE_MSTANDBYSTATE_STANDBY
                                    /**< Max value of the enum. Can be used for
                                     *   validation. */
} pmhalPrcmModuleMStbyState_t;

/**
 *  \brief Enum defining content of Clock Activity Settings
 *         for Idle Ack Clock Gating Conditions
 */
typedef enum pmhalPrcmModuleSClockActivity
{
    PMHAL_PRCM_MODULE_SCLOCKACTIVITY_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_SCLOCKACTIVITY_GATE_FUNC_INT =
        PMHAL_PRCM_MODULE_SCLOCKACTIVITY_MIN,
    /**< Enum for sClkActivity Function Init */
    PMHAL_PRCM_MODULE_SCLOCKACTIVITY_FUNC_NOINT = 0x1U,
    /**< Enum for sClkActivity Function no Init */
    PMHAL_PRCM_MODULE_SCLOCKACTIVITY_NOFUNC_INT = 0x2U,
    /**< Enum for sClkActivity No Function Init */
    PMHAL_PRCM_MODULE_SCLOCKACTIVITY_NOFUNC_NOINT = 0x3U,
    /**< Enum for sClkActivity No Function No Init */
    PMHAL_PRCM_MODULE_SCLOCKACTIVITY_MAX =
        PMHAL_PRCM_MODULE_SCLOCKACTIVITY_NOFUNC_NOINT
        /**< Max value of the enum. Can be used for
         *   validation. */
} pmhalPrcmModuleSClkActivity_t;

/**
 * \brief Index for System Clock Frequency values.
 */
typedef enum pmhalPrcmSysClkVal
{
    PMHAL_PRCM_SYSCLK_UNINITIALIZED = 0U,
    /**< System clock frequency uninitialized value */
    PMHAL_PRCM_SYSCLK_MIN = PMHAL_PRCM_SYSCLK_UNINITIALIZED,
    /**< Min system clock frequency index */
    PMHAL_PRCM_SYSCLK_12_MHZ = 1U,
    /**< System clock frequency 12 MHz index */
    PMHAL_PRCM_SYSCLK_20_MHZ = 2U,
    /**< System clock frequency 20 MHz index */
    PMHAL_PRCM_SYSCLK_16_8_MHZ = 3U,
    /**< System clock frequency 16.8 MHz index */
    PMHAL_PRCM_SYSCLK_19_2_MHZ = 4U,
    /**< System clock frequency 19.2 MHz index */
    PMHAL_PRCM_SYSCLK_26_MHZ = 5U,
    /**< System clock frequency 26 MHz index */
    PMHAL_PRCM_SYSCLK_27_MHZ = 6U,
    /**< System clock frequency 27 MHz index */
    PMHAL_PRCM_SYSCLK_38_4_MHZ = 7U,
    /**< System clock frequency 38.4 MHz index */
    PMHAL_PRCM_SYSCLK_MAX = PMHAL_PRCM_SYSCLK_38_4_MHZ,
    /**< Max system clock frequency index */
    PMHAL_PRCM_SYSCLK_COUNT = PMHAL_PRCM_SYSCLK_MAX + 1U,
    /**< System clock frequency index count */
    PMHAL_PRCM_SYSCLK_UNDEF = 0x7FFFFFFFU
                              /**< Undefined system clock frequency index */
} pmhalPrcmSysClkVal_t;

/**
 *  \brief Enum defining content of clock status
 */
typedef enum pmhalPrcmClockActivityState
{
    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED =
        PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_MIN,
    /**< Enum for Gated Module CLK Activity. */
    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED = 0x1U,
    /**< Enum for Gated Module CLK Activity. */
    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_MAX =
        PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED
        /**< Min value of the enum. Can be
         *   used for validation. */
} pmhalPrcmClockActivityState_t;

/**
 *  \brief Enum defining clock domain control values. These values can be used
 *         to control the clock domain while initializing the system, entering
 *         sleep state and waking up from sleep state.
 */
typedef enum pmhalPrcmCdClkTrnModes
{
    PMHAL_PRCM_CD_CLKTRNMODES_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP = PMHAL_PRCM_CD_CLKTRNMODES_MIN,
    /**< No sleep in the clock domain */
    PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP = 1U,
    /**< Start a software forced sleep transition on the clock domain. */
    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP = 2U,
    /**< Start a software forced wake-up transition on the clock domain. */
    PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO = 3U,
    /**< If there is no activity in the clock domain HW automatically puts it
     *   into sleep mode. On detecting any activity it wakes up. */
    PMHAL_PRCM_CD_CLKTRNMODES_MAX = PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO
                                    /**< Max value of the enum. Can be used for
                                     *   validation. */
} pmhalPrcmCdClkTrnModes_t;

/**
 *  \brief Enum defining power domain status values. These values can be used
 *         to control the clock domain while initializing the system, entering
 *         sleep state and waking up from sleep state.
 */
typedef enum pmhalPrcmPdState
{
    PMHAL_PRCM_PD_STATUS_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_STATE_OFF = PMHAL_PRCM_PD_STATUS_MIN,
    /**< Power to the domain is off. */
    PMHAL_PRCM_PD_STATE_RETENTION = 1U,
    /**< Power to the domain is in retention mode and it will not be functional
     *   but the memory will be retained. */
    PMHAL_PRCM_PD_STATE_ON_INACTIVE = 2U,
    /**< Power to the domain is ON INACTIVE. */
    PMHAL_PRCM_PD_STATE_ON_ACTIVE = 3U,
    /**< Power to the domain is ON. */
    PMHAL_PRCM_PD_STATUS_MAX = PMHAL_PRCM_PD_STATE_ON_ACTIVE,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_STATUS_COUNT = PMHAL_PRCM_PD_STATUS_MAX + 1U
                                 /**< Count value of the enum. Can be used for
                                  *   validation. */
} pmhalPrcmPdState_t;

/**
 * \brief Enumeration of Static Dependency.
 */
typedef enum pmhalStaticDepBitShift
{
    PMHAL_SD_SHIFT_RESERVED_31 = 31U,
    /**< Static Dependency 31U register bit shift */
    PMHAL_SD_SHIFT_CRC_STATDEP = 30U,
    /**< Static Dependency CRC register bit shift */
    PMHAL_SD_SHIFT_ISS_STATDEP = 28U,
    /**< Static Dependency ISS register bit shift */
    PMHAL_SD_SHIFT_L4PER3_STATDEP = 27U,
    /**< Static Dependency L4PER3 register bit shift */
    PMHAL_SD_SHIFT_L4PER2_STATDEP = 26U,
    /**< Static Dependency L4PER2 register bit shift */
    PMHAL_SD_SHIFT_GMAC_STATDEP = 25U,
    /**< Static Dependency GMAC register bit shift */
    PMHAL_SD_SHIFT_IPU_STATDEP = 24U,
    /**< Static Dependency IPU register bit shift */
    PMHAL_SD_SHIFT_IPU1_STATDEP = 23U,
    /**< Static Dependency IPU1 register bit shift */
    PMHAL_SD_SHIFT_EVE1_STATDEP = 19U,
    /**< Static Dependency EVE1 register bit shift */
    PMHAL_SD_SHIFT_DSP2_STATDEP = 18U,
    /**< Static Dependency DSP2 register bit shift */
    PMHAL_SD_SHIFT_CUSTEFUSE_STATDEP = 17U,
    /**< Static Dependency CUSTEFUSE register bit shift */
    PMHAL_SD_SHIFT_COREAON_STATDEP = 16U,
    /**< Static Dependency COREAON register bit shift */
    PMHAL_SD_SHIFT_WKUPAON_STATDEP = 15U,
    /**< Static Dependency WKUPAON register bit shift */
    PMHAL_SD_SHIFT_L4PER_STATDEP = 13U,
    /**< Static Dependency L4PER register bit shift */
    PMHAL_SD_SHIFT_L4CFG_STATDEP = 12U,
    /**< Static Dependency L4CFG register bit shift */
    PMHAL_SD_SHIFT_SDMA_STATDEP = 11U,
    /**< Static Dependency SDMA register bit shift */
    PMHAL_SD_SHIFT_CAM_STATDEP = 9U,
    /**< Static Dependency CAM register bit shift */
    PMHAL_SD_SHIFT_DSS_STATDEP = 8U,
    /**< Static Dependency DSS register bit shift */
    PMHAL_SD_SHIFT_L3INIT_STATDEP = 7U,
    /**< Static Dependency L3INIT register bit shift */
    PMHAL_SD_SHIFT_RESERVED_6 = 6U,
    /**< Static Dependency RESERVED_6 register bit shift */
    PMHAL_SD_SHIFT_L3MAIN1_STATDEP = 5U,
    /**< Static Dependency L3MAIN1 register bit shift */
    PMHAL_SD_SHIFT_EMIF_STATDEP = 4U,
    /**< Static Dependency EMIF register bit shift */
    PMHAL_SD_SHIFT_RESERVED_3 = 3U,
    /**< Static Dependency RESERVED_3 register bit shift */
    PMHAL_SD_SHIFT_DSP1_STATDEP = 1U,
    /**< Static Dependency DSP1 register bit shift */
    PMHAL_SD_SHIFT_IPU2_STATDEP = 0U
                                  /**< Static Dependency IPU2 register bit shift
                                  **/
}pmhalStaticDepBitShift_t;

/**
 *  \brief Enumeration for different different post dividers.
 */
typedef enum pmhalPrcmDpllPostDivId
{
    PMHAL_PRCM_DPLL_POST_DIV_INVALID = 0x7FFFFFFFU,
    /**< Invalid value. */
    PMHAL_PRCM_DPLL_POST_DIV_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_POST_DIV_M2 = PMHAL_PRCM_DPLL_POST_DIV_MIN,
    /**< M2 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_M2X2 = 1U,
    /**< M2X2 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_M4 = 2U,
    /**< M4 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_M3 = 3U,
    /**< M3 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_M5 = 4U,
    /**< M5 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_M6 = 5U,
    /**< M6 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H11 = 6U,
    /**< H11 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H12 = 7U,
    /**< H12 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H13 = 8U,
    /**< H13 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H14 = 9U,
    /**< H14 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H21 = 10U,
    /**< H21 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H22 = 11U,
    /**< H22 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H23 = 12U,
    /**< H23 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_H24 = 13U,
    /**< H24 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_VCO_LDO_DIV = 14U,
    /**< VCO_LDO_DIV post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_VCO_LDO = 15U,
    /**< VCO_LDO post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO = 16U,
    /**< DCO_LDO post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_M7 = 17U,
    /**< M7 post divider. */
    PMHAL_PRCM_DPLL_POST_DIV_MAX = PMHAL_PRCM_DPLL_POST_DIV_M7,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_POST_DIV_COUNT = PMHAL_PRCM_DPLL_POST_DIV_MAX + 1U
                                     /**< Count value of the enum. Can be used
                                      * for
                                      *   validation. */
} pmhalPrcmDpllPostDivId_t;

/**
 *  \brief Enum defining CLKINPULOW input selection.
 *         These parameters define the clock input to CLKINPULOW signal in
 *         bypass mode.
 */
typedef enum pmhalPrcmDpllClkInputLowSel
{
    PMHAL_PRCM_DPLL_CLKINPULOW_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_CLKINPULOW_CORE_CLKOUTM6 = PMHAL_PRCM_DPLL_CLKINPULOW_MIN,
    /**< Select CORE_CLKOUTM6 as the input for CLKINPULOW. */
    PMHAL_PRCM_DPLL_CLKINPULOW_PER_CLKOUTM2 = 1U,
    /**< Select PER_CLKOUTM2 as the input for CLKINPULOW. */
    PMHAL_PRCM_DPLL_CLKINPULOW_MAX = 1U,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_CLKINPULOW_COUNT = PMHAL_PRCM_DPLL_CLKINPULOW_MAX + 1U
                                       /**< Count value of the enum. Can be used
                                        * for validation. */
} pmhalPrcmDpllClkInputLowSel_t;

/**
 *  \brief Enum defining bypass input clock selection for the PLL.
 *         The bypass clock can either be CLKINP (Master Osc) or CLKINPULOW
 *         (above enum value).
 */
typedef enum pmhalPrcmDpllBypassClkSel
{
    PMHAL_PRCM_DPLL_BYP_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_BYP_CLKINP = PMHAL_PRCM_DPLL_BYP_MIN,
    /**< Select CLKINP (Master Oscillator) as the bypass mode clock. */
    PMHAL_PRCM_DPLL_BYP_CLKINPULOW = 1U,
    /**< Select CLKINPULOW as the bypass mode clock. Refer
     *   prcmDpllClkInputLowSel_t for possible inputs for CLKINPULOW. */
    PMHAL_PRCM_DPLL_BYP_MAX = PMHAL_PRCM_DPLL_BYP_CLKINPULOW,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_BYP_COUNT = PMHAL_PRCM_DPLL_BYP_MAX + 1U
                                /**< Count value of the enum. Can be used for
                                 *   validation. */
} pmhalPrcmDpllBypassClkSel_t;

/**
 *  \brief Enum defining input clocks for the PLL.
 */
typedef enum pmhalPrcmDpllClkInput
{
    PMHAL_PRCM_DPLL_INP_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_INP_CLKINP = PMHAL_PRCM_DPLL_INP_MIN,
    /**< Select CLKINP (Master Oscillator) as the bypass mode clock. */
    PMHAL_PRCM_DPLL_INP_CLKINPULOW = 1U,
    /**< Select CLKINPULOW as the bypass mode clock. Refer
     *   prcmDpllClkInputLowSel_t for possible inputs for CLKINPULOW. */
    PMHAL_PRCM_DPLL_INP_CLKINPHIF = 2U,
    /**< Implicit Select CLKINPHIF as the bypass mode clock for M3 output. Refer
     *   prcmDpllClkInputLowSel_t for possible inputs for CLKINPULOW. */
    PMHAL_PRCM_DPLL_INP_DCO = 3U,
    /**< Implicit Select DCO as the bypass mode clock for M3 output */
    PMHAL_PRCM_DPLL_INP_MAX = PMHAL_PRCM_DPLL_INP_DCO,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_INP_COUNT = PMHAL_PRCM_DPLL_INP_MAX + 1U
                                /**< Count value of the enum. Can be used for
                                 *   validation. */
} pmhalPrcmDpllClkInput_t;
/**
 *  \brief Enum defining different power modes for the PLL.
 */
typedef enum pmhalPrcmDpllPowerMode
{
    PMHAL_PRCM_DPLL_POWER_MODE_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_POWER_MODE_MN_BYP_MODE = PMHAL_PRCM_DPLL_POWER_MODE_MIN,
    /**< MN Bypass mode, the value of multiplier and divider of DPLL are set to
     *   Zero. */
    PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE = 1U,
    /**< Low Power Bypass mode, the value of multiplier and divider of
     *  DPLL are retained. */
    PMHAL_PRCM_DPLL_POWER_MODE_FR_STP_MODE = 2U,
    /**< Fast relock stop mode. */
    PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE = 5U,
    /**< Low Power Bypass mode, the value of multiplier and divider of DPLL are
     *   retained. */
    PMHAL_PRCM_DPLL_POWER_MODE_FR_BYP_MODE = 6U,
    /**< Fast relock Bypass mode. */
    PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE = 7U,
    /**< DPLL Lock mode. */
    PMHAL_PRCM_DPLL_POWER_MODE_MAX = PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_POWER_MODE_COUNT = PMHAL_PRCM_DPLL_POWER_MODE_MAX + 1U,
    /**< Count value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_POWER_MODE_UNDEF = 0x7FFFFFFFU
                                       /**< Mode Not Defined */
} pmhalPrcmDpllPowerMode_t;

/**
 *  \brief Enum defining different ramp levels for the PLL.
 */
typedef enum pmhalPrcmDpllRampLevel
{
    PMHAL_PRCM_DPLL_RAMP_LEVEL_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_RAMP_LEVEL_DISABLE = PMHAL_PRCM_DPLL_RAMP_LEVEL_MIN,
    /**< Ramp level is disabled. */
    PMHAL_PRCM_DPLL_RAMP_LEVEL_ALGO1 = 1U,
    /**< Ramp level to use algorithm1.
     *    CLKOUT   => Bypass clk -> Fout/8 -> Fout/4 -> Fout/2 -> Fout
     *    CLKOUTX2 => Bypass clk -> Foutx2/8 -> Foutx2/4 -> Foutx2/2 -> Foutx2
     */
    PMHAL_PRCM_DPLL_RAMP_LEVEL_ALGO2 = 2U,
    /**< Ramp level to use algorithm2.
     *   CLKOUT   => Bypass clk -> Fout/4 -> Fout/2 -> Fout/1.5 -> Fout
     *   CLKOUTX2 => Bypass clk -> Foutx2/4 -> Foutx2/2 -> Foutx2/1.5 -> Foutx2
     */
    PMHAL_PRCM_DPLL_RAMP_LEVEL_MAX = PMHAL_PRCM_DPLL_RAMP_LEVEL_ALGO2,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_RAMP_LEVEL_COUNT = PMHAL_PRCM_DPLL_RAMP_LEVEL_MAX + 1U
                                       /**< Count value of the enum. Can be used
                                        * for validation. */
} pmhalPrcmDpllRampLevel_t;

/**
 *  \brief Enum defining different ramp rates for the PLL. These rates .
 *         indicates the time spent in each ramp step.
 */
typedef enum pmhalPrcmDpllRampRate
{
    PMHAL_PRCM_DPLL_RAMP_RATE_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX2 = PMHAL_PRCM_DPLL_RAMP_RATE_MIN,
    /**< 2 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX4 = 1U,
    /**< 4 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX8 = 2U,
    /**< 8 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX16 = 3U,
    /**< 16 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX32 = 4U,
    /**< 32 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX64 = 5U,
    /**< 64 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX128 = 6U,
    /**< 128 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX512 = 7U,
    /**< 512 REFCLKs per each ramp step. */
    PMHAL_PRCM_DPLL_RAMP_RATE_MAX = PMHAL_PRCM_DPLL_RAMP_RATE_REFCLKX512,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_RAMP_RATE_COUNT = PMHAL_PRCM_DPLL_RAMP_RATE_MAX + 1U
                                      /**< Count value of the enum. Can be used
                                       * for validation. */
} pmhalPrcmDpllRampRate_t;

/**
 *  \brief Enum defining lock statuses of DPLL.
 */
typedef enum pmhalPrcmDpllLockStatus
{
    PMHAL_PRCM_DPLL_IDLEST_ST_CLK_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_IDLEST_ST_CLK_UNLOCKED = PMHAL_PRCM_DPLL_IDLEST_ST_CLK_MIN,
    /**< DPLL is in bypass mode. */
    PMHAL_PRCM_DPLL_IDLEST_ST_CLK_LOCKED = 1U,
    /**< DPLL is in lock mode. */
    PMHAL_PRCM_DPLL_IDLEST_ST_CLK_MAX = PMHAL_PRCM_DPLL_IDLEST_ST_CLK_LOCKED,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_DPLL_IDLEST_ST_CLK_COUNT =
        PMHAL_PRCM_DPLL_IDLEST_ST_CLK_MAX + 1U
        /**< Count value of the enum. Can be used
         *   for validation. */
} pmhalPrcmDpllLockStatus_t;

/**
 *  \brief Enum defining different types of root clock.
 */
typedef enum pmhalPrcmRootClkType
{
    PMHAL_PRCM_ROOT_CLK_FREQ_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_ROOT_CLK_FREQ_FIXED = PMHAL_PRCM_DPLL_IDLEST_ST_CLK_MIN,
    /**< Frequency of the root clock is fixed in the SoC. */
    PMHAL_PRCM_ROOT_CLK_FREQ_STATIC_CONFIG = 1U,
    /**< Frequency of the root clock is not fixed in the SoC, but fixed during
     *   board design or system initialization. */
    PMHAL_PRCM_ROOT_CLK_FREQ_MAX = PMHAL_PRCM_ROOT_CLK_FREQ_STATIC_CONFIG,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_ROOT_CLK_FREQ_COUNT = PMHAL_PRCM_ROOT_CLK_FREQ_MAX + 1U
                                     /**< Count value of the enum. Can be used
                                      * for validation. */
} pmhalPrcmRootClkType_t;

/**
 *  \brief Enum defining Logic Retention Power States of Logic Area
 */
typedef enum pmhalPrcmPdLogicRetState
{
    PMHAL_PRCM_PD_RET_STATUS_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_RET_STATUS_OSWR = PMHAL_PRCM_PD_RET_STATUS_MIN,
    /**< One of the Logic Retention States */
    PMHAL_PRCM_PD_RET_STATUS_CSWR = 1U,
    /**< One of the Logic Retention States */
    PMHAL_PRCM_PD_RET_STATUS_MAX = PMHAL_PRCM_PD_RET_STATUS_CSWR,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_RET_STATUS_COUNT = PMHAL_PRCM_PD_RET_STATUS_MAX + 1U
                                     /**< Count value of the enum. Can be used
                                      * for validation. */
} pmhalPrcmPdLogicRetState_t;

/**
 *  \brief Enum defining Low Power Request type of the power domain.
 */
typedef enum pmhalPrcmPdLowPwrStateChangeType
{
    PMHAL_PRCM_PD_LOW_PWR_REQUEST_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST = PMHAL_PRCM_PD_LOW_PWR_REQUEST_MIN,
    /**< One of the Low Power State Change Request Values */
    PMHAL_PRCM_PD_LOW_PWR_REQUEST = 1U,
    /**< One of the Low Power State Change Request Values */
    PMHAL_PRCM_PD_LOW_PWR_REQUEST_MAX = PMHAL_PRCM_PD_LOW_PWR_REQUEST,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_LOW_PWR_REQUEST_COUNT = PMHAL_PRCM_PD_LOW_PWR_REQUEST_MAX +
                                          1U
                                          /**< Count value of the enum. Can be
                                           * used for validation. */
} pmhalPrcmPdLowPwrStateChangeType_t;

/**
 * \brief Physical memory data retention states
 */
typedef enum pmhalPhyBankRetStates
{
    PMHAL_BANK_RET_OFF = 0U,
    /**< One of the Physical Memory Bank States */
    PMHAL_BANK_RET_MIN = PMHAL_BANK_RET_OFF,
    /**< Lower bound (inclusive) */
    PMHAL_BANK_RET_ON = 1U,
    /**< One of the Physical Memory Bank States */
    PMHAL_BANK_RET_MAX = PMHAL_BANK_RET_ON,
    /**< Enum Upper bound */
    PMHAL_BANK_RET_COUNT = PMHAL_BANK_RET_MAX + 1U,
    /**< Enum Count */
    PMHAL_BANK_RET_UNDEF = 0xFF
                           /**< Undefined value */
} pmhalPhyBankRetStates_t;

/**
 *  \brief Enum defining PD in Transitions or not
 */
typedef enum pmhalPrcmPdTransitionState
{
    PMHAL_PRCM_PD_TRANSIT_STATUS_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_TRANSIT_STATUS_NOTRANS = PMHAL_PRCM_PD_TRANSIT_STATUS_MIN,
    /**< No on-going transition on power domain */
    PMHAL_PRCM_PD_TRANSIT_STATUS_INTRANS = 1U,
    /**< Power domain transition is in progress. */
    PMHAL_PRCM_PD_TRANSIT_STATUS_MAX = PMHAL_PRCM_PD_TRANSIT_STATUS_INTRANS,
    /**< Max value of the enum. Can be used for validation. */
    PMHAL_PRCM_PD_TRANSIT_STATUS_COUNT = PMHAL_PRCM_PD_TRANSIT_STATUS_MAX + 1U
                                         /**< Count value of the enum. Can be
                                          * used for validation. */
} pmhalPrcmPdTransitionState_t;

/**
 *  \brief Enum defining Context Status
 */
typedef enum pmhalPrcmContextStateId
{
    PMHAL_PRCM_CONTEXT_STATUS_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_CONTEXT_STATUS_MAINTAINED = PMHAL_PRCM_CONTEXT_STATUS_MIN,
    /**< PM HAL Prcm status maintained */
    PMHAL_PRCM_CONTEXT_STATUS_LOST = 1U,
    /**< PM HAL Prcm status Lost */
    PMHAL_PRCM_CONTEXT_STATUS_MAX = PMHAL_PRCM_CONTEXT_STATUS_LOST,
    /**< PM HAL Prcm Status Max */
    PMHAL_PRCM_CONTEXT_STATUS_COUNT = PMHAL_PRCM_CONTEXT_STATUS_MAX + 1U
                                      /**< Count value of the enum. Can be used
                                       * for validation. */
} pmhalPrcmContextStateId_t;

/**
 * \brief Voltage Domains
 */
typedef enum pmhalPrcmVdId
{
    PMHAL_PRCM_VD_LOWER_BOUND = (-(int32_t)1),
    /**< Lower Bound Exclusive */
    PMHAL_PRCM_VD_MIN = 0,
    /**< Minimum Voltage Domain */
    PMHAL_PRCM_VD_CORE = PMHAL_PRCM_VD_MIN,
    /**< VD_CORE Voltage Domain */
    PMHAL_PRCM_VD_DSPEVE = 1,
    /**< VD_DSPEVE Voltage Domain */
    PMHAL_PRCM_VD_MAX = PMHAL_PRCM_VD_DSPEVE,
    /**< Enum Upper bound */
    PMHAL_PRCM_VD_COUNT = PMHAL_PRCM_VD_MAX + 1,
    /**< Enum Count */
    PMHAL_PRCM_VD_UNDEF = 0x7FFFFFFF
                          /**< Undefined value */
} pmhalPrcmVdId_t;

/**
 * \brief The Abstract PMIC Voltage Regulator IDs used by the PMIC Interface.
 *        These abstract regulator IDs represent the regulators connected to
 *        the voltage rail of the respective voltage domains. The mapping
 *        of these abstract regulator IDs to the actual PMIC regulators are
 *        done in the respective HW PMIC module.
 */
typedef enum pmhalPrcmPmicRegulatorId
{
    PMHAL_PRCM_PMIC_REGULATOR_INVALID = (-(int32_t)1),
    /**< Invalid PMIC Regulator */
    PMHAL_PRCM_PMIC_REGULATOR_MIN = 0,
    /**< Minimum Abstracted PMIC Regulator */
    PMHAL_PRCM_PMIC_REGULATOR_CORE = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for CORE */
    PMHAL_PRCM_PMIC_REGULATOR_DSPEVE = 1,
    /**< Abstracted PMIC Regulator ID for DSPEVE */
    PMHAL_PRCM_PMIC_REGULATOR_1V8PHY = 2,
    /**< Abstracted PMIC Regulator ID for 1V8PHY */
    PMHAL_PRCM_PMIC_REGULATOR_DDR_DV = 3,
    /**< Abstracted PMIC Regulator ID for DDR Voltage */
    PMHAL_PRCM_PMIC_REGULATOR_1V8PLL = 4,
    /**< Abstracted PMIC Regulator ID for 1V8PLL */
    PMHAL_PRCM_PMIC_REGULATOR_MAX = PMHAL_PRCM_PMIC_REGULATOR_1V8PLL,
    /**< Maximum Abstracted PMIC Regulator */
    PMHAL_PRCM_PMIC_REGULATOR_COUNT = (PMHAL_PRCM_PMIC_REGULATOR_MAX + 1)
                                      /**< Count for the PMIC regulators */
} pmhalPrcmPmicRegulatorId_t;

/**
 * \brief SRAM LDO Retention states enumeration
 */
typedef enum pmhalPrcmSramLdoRetState
{
    PMHAL_PRCM_SRAM_LDO_RET_STATE_MIN = 0U,
    /**< Minimum SRAM LDO Retention request state */
    PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET = PMHAL_PRCM_SRAM_LDO_RET_STATE_MIN,
    /**< SRAM LDO is not allowed to go to Retention */
    PMHAL_PRCM_SRAM_LDO_RET_STATE_RET = 1U,
    /**< SRAM LDO go to RET mode when all memory of voltage domain are
     *   OFF or RET */
    PMHAL_PRCM_SRAM_LDO_RET_STATE_MAX = PMHAL_PRCM_SRAM_LDO_RET_STATE_RET,
    /**< Maximum SRAM LDO Retention request state */
    PMHAL_PRCM_SRAM_LDO_RET_STATE_INVALID = 0xFFU
                                            /**< Invalid SRAM LDO Retention
                                             * Status */
}pmhalPrcmSramLdoRetState_t;

/**
 * \brief SRAM LDO Transition state enumeration.
 */
typedef enum pmhalPrcmSramLdoTransState
{
    PMHAL_PRCM_SRAM_LDO_TRANS_STATE_MIN = 0U,
    /**< Minimum SRAM LDO Transition state */
    PMHAL_PRCM_SRAM_LDO_TRANS_STATE_STABLE =
        PMHAL_PRCM_SRAM_LDO_TRANS_STATE_MIN,
    /**< SRAM LDO state machine is stable */
    PMHAL_PRCM_SRAM_LDO_TRANS_STATE_IN_TRANSITION = 1U,
    /**< SRAM LDO state machine is in transition */
    PMHAL_PRCM_SRAM_LDO_TRANS_STATE_MAX =
        PMHAL_PRCM_SRAM_LDO_TRANS_STATE_IN_TRANSITION,
    /**< Maximum SRAM LDO Transition state */
    PMHAL_PRCM_SRAM_LDO_TRANS_STATE_INVALID = 0xFFU
                                              /**< Invalid SRAM LDO Transition
                                               * Status */
}pmhalPrcmSramLdoTransState_t;

/**
 * \brief SRAM LDO status.
 */
typedef enum pmhalPrcmSramLdoStatus
{
    PMHAL_PRCM_SRAM_LDO_STATUS_MIN = 0U,
    /**< Minimum SRAM LDO Status */
    PMHAL_PRCM_SRAM_LDO_STATUS_ACTIVE = PMHAL_PRCM_SRAM_LDO_STATUS_MIN,
    /**< SRAMLDO is in ACTIVE mode */
    PMHAL_PRCM_SRAM_LDO_STATUS_RETENTION = 1U,
    /**< SRAMLDO is in RETENTION mode. */
    PMHAL_PRCM_SRAM_LDO_STATUS_MAX = PMHAL_PRCM_SRAM_LDO_STATUS_RETENTION,
    /**< Maximum SRAM LDO Status */
    PMHAL_PRCM_SRAM_LDO_STATUS_INVALID = 0xFFU
                                         /**< Invalid SRAM LDO Status */
}pmhalPrcmSramLdoStatus_t;

/**
 * \brief SRAM LDO Setup Register bit field enumeration.
 */
typedef enum pmhalPrcmSramSetupBitFields
{
    PMHAL_PRCM_SLDO_SETUP_BIT_SHIFT_MIN = 0U,
    /**< Minimum shift supported for SRAM LDO Setup register */
    PMHAL_PRCM_SLDO_SETUP_BIT_ENABLE_RTA = PMHAL_PRCM_SLDO_SETUP_BIT_SHIFT_MIN,
    /**< Bit shift for field which is a control for HD memory RTA feature. */
    PMHAL_PRCM_SLDO_SETUP_BIT_ABBOFF_ACT = 1U,
    /**< Bit shift for field which determines whether SRAMNWA is supplied by
     *   VDDS or RW 0x0 VDDAR during active mode. */
    PMHAL_PRCM_SLDO_SETUP_BIT_ABBOFF_SLEEP = 2U,
    /**< Bit shift for field which determines whether SRAMNWA is supplied by
     *   VDDS or RW 0x0 VDDAR during deep-sleep. */
    PMHAL_PRCM_SLDO_SETUP_BIT_ENFUNC1 = 3U,
    /**< Bit shift for field which controls Short Circuit protection */
    PMHAL_PRCM_SLDO_SETUP_BIT_ENFUNC2 = 4U,
    /**< Bit shift for field which determines External Capacitor usage */
    PMHAL_PRCM_SLDO_SETUP_BIT_ENFUNC3 = 5U,
    /**< Bit shift for field which determines if sub-regulation is enabled */
    PMHAL_PRCM_SLDO_SETUP_BIT_ENFUNC4 = 6U,
    /**< Bit shift for field which determines if external clock is supplied to
     *   SRAM LDO */
    PMHAL_PRCM_SLDO_SETUP_BIT_ENFUNC5 = 7U,
    /**< Bit shift for field which determines if active to retention is a one
     *   step or two step transfer */
    PMHAL_PRCM_SLDO_SETUP_BIT_AIPOFF = 8U,
    /**< Bit shift for field which determines if AIPOFF is overridden or not */
    PMHAL_PRCM_SLDO_SETUP_BIT_SHIFT_COUNT = 9U,
    /**< Maximum shift supported for SRAM LDO Setup register */
    PMHAL_PRCM_SLDO_SETUP_BIT_SHIFT_INVALID = 0xFFU
                                              /**< Invalid shift for SRAM LDO
                                               * Setup register */
}pmhalPrcmSramSetupBitFields_t;

/**
 * \brief Power Domains
 */
typedef enum pmhalPrcmPdId
{
    PMHAL_PRCM_PD_LOWER_BOUND = (-(int32_t)1),
    /**< Lower bound */
    PMHAL_PRCM_PD_CAM,
    /**< CAM Power Domain */
    PMHAL_PRCM_PD_CORE,
    /**< CORE Power Domain */
    PMHAL_PRCM_PD_COREAON,
    /**< COREAON Power Domain */
    PMHAL_PRCM_PD_CUSTEFUSE,
    /**< CUSTEFUSE Power Domain */
    PMHAL_PRCM_PD_DSP1,
    /**< DSP1 Power Domain */
    PMHAL_PRCM_PD_DSP2,
    /**< DSP2 Power Domain */
    PMHAL_PRCM_PD_DSS,
    /**< DSS Power Domain */
    PMHAL_PRCM_PD_EMU,
    /**< EMU Power Domain */
    PMHAL_PRCM_PD_EVE1,
    /**< EVE1 Power Domain */
    PMHAL_PRCM_PD_IPU,
    /**< IPU Power Domain */
    PMHAL_PRCM_PD_L3INIT,
    /**< L3INIT Power Domain */
    PMHAL_PRCM_PD_L4PER,
    /**< L4PER Power Domain */
    PMHAL_PRCM_PD_ISS,
    /**< ISS Power Domain */
    PMHAL_PRCM_PD_MMAON,
    /**< MMAON Power Domain */
    PMHAL_PRCM_PD_WKUPAON,
    /**< WKUPAON Power Domain */
    PMHAL_PRCM_PD_COUNT
    /**< Enum Count */
} pmhalPrcmPdId_t;

/**
 * \brief Clock Domains
 */
typedef enum pmhalPrcmCdId
{
    PMHAL_PRCM_CD_LOWER_BOUND = (-(int32_t)1),
    /**< Lower bound */
    PMHAL_PRCM_CD_CAM,
    /**< CAM Clock Domain */
    PMHAL_PRCM_CD_CRC,
    /**< CRC Clock Domain */
    PMHAL_PRCM_CD_EMIF,
    /**< EMIF Clock Domain */
    PMHAL_PRCM_CD_L3INSTR,
    /**< L3INSTR Clock Domain */
    PMHAL_PRCM_CD_L3MAIN1,
    /**< L3MAIN1 Clock Domain */
    PMHAL_PRCM_CD_L4CFG,
    /**< L4CFG Clock Domain */
    PMHAL_PRCM_CD_COREAON,
    /**< COREAON Clock Domain */
    PMHAL_PRCM_CD_CUSTEFUSE,
    /**< CUSTEFUSE Clock Domain */
    PMHAL_PRCM_CD_DSP1,
    /**< DSP1 Clock Domain */
    PMHAL_PRCM_CD_DSP2,
    /**< DSP2 Clock Domain */
    PMHAL_PRCM_CD_DSS,
    /**< DSS Clock Domain */
    PMHAL_PRCM_CD_EMU,
    /**< EMU Clock Domain */
    PMHAL_PRCM_CD_EVE1,
    /**< EVE1 Clock Domain */
    PMHAL_PRCM_CD_IPU1,
    /**< IPU1 Clock Domain */
    PMHAL_PRCM_CD_IPU,
    /**< IPU Clock Domain */
    PMHAL_PRCM_CD_GMAC,
    /**< GMAC Clock Domain */
    PMHAL_PRCM_CD_L3INIT,
    /**< L3INIT Clock Domain */
    PMHAL_PRCM_CD_L4PER2,
    /**< L4PER2 Clock Domain */
    PMHAL_PRCM_CD_L4PER3,
    /**< L4PER3 Clock Domain */
    PMHAL_PRCM_CD_L4PER1,
    /**< L4PER Clock Domain */
    PMHAL_PRCM_CD_MMAON,
    /**< MMAON Clock Domain */
    PMHAL_PRCM_CD_ISS,
    /**< ISS Clock Domain */
    PMHAL_PRCM_CD_WKUPAON,
    /**< WKUPAON Clock Domain */
    PMHAL_PRCM_CD_COUNT
    /**< Enum Count */
} pmhalPrcmCdId_t;

/**
 * \brief Clocks
 */
typedef enum pmhalPrcmClockId
{
    PMHAL_PRCM_CLK_CRC_L3_GICLK = 0U,
    /**< PM HAL Prcm ATL L3 GICLK Clock */
    PMHAL_PRCM_CLK_MIN = PMHAL_PRCM_CLK_CRC_L3_GICLK,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_CLK_ABE_GICLK = 1U,
    /**< PM HAL Prcm ABE GICLK Clock */
    PMHAL_PRCM_CLK_CLKOUTMUX1_CLK = 2U,
    /**< PM HAL Prcm CLKOUTMUX1 CLK Clock */
    PMHAL_PRCM_CLK_CLKOUTMUX2_CLK = 3U,
    /**< PM HAL Prcm CLKOUTMUX2 CLK Clock */
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK = 4U,
    /**< PM HAL Prcm SR CORE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK = 5U,
    /**< PM HAL Prcm SR DSPEVE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK = 6U,
    /**< PM HAL Prcm CUSTEFUSE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_DSP1_GFCLK = 7U,
    /**< PM HAL Prcm DSP1 GFCLK Clock */
    PMHAL_PRCM_CLK_DSP2_GFCLK = 8U,
    /**< PM HAL Prcm DSP2 GFCLK Clock */
    PMHAL_PRCM_CLK_DSS_L3_GICLK = 9U,
    /**< PM HAL Prcm DSS L3 GICLK Clock */
    PMHAL_PRCM_CLK_HDMI_CEC_GFCLK = 10U,
    /**< PM HAL Prcm HDMI CEC GFCLK Clock */
    PMHAL_PRCM_CLK_HDMI_PHY_GFCLK = 11U,
    /**< PM HAL Prcm HDMI PHY GFCLK Clock */
    PMHAL_PRCM_CLK_DSS_GFCLK = 12U,
    /**< PM HAL Prcm DSS GFCLK Clock */
    PMHAL_PRCM_CLK_HDMI_DPLL_CLK = 13U,
    /**< PM HAL Prcm HDMI DPLL CLK Clock */
    PMHAL_PRCM_CLK_DSS_L4_GICLK = 14U,
    /**< PM HAL Prcm DSS L4 GICLK Clock */
    PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK = 15U,
    /**< PM HAL Prcm VIDEO1 DPLL CLK Clock */
    PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK = 16U,
    /**< PM HAL Prcm VIDEO2 DPLL CLK Clock */
    PMHAL_PRCM_CLK_SDVENC_GFCLK = 17U,
    /**< PM HAL Prcm SDVENC GFCLK Clock */
    PMHAL_PRCM_CLK_EMIF_DLL_GCLK = 18U,
    /**< PM HAL Prcm EMIF DLL GCLK Clock */
    PMHAL_PRCM_CLK_EMIF_L3_GICLK = 19U,
    /**< PM HAL Prcm EMIF L3 GICLK Clock */
    PMHAL_PRCM_CLK_EMIF_PHY_GCLK = 20U,
    /**< PM HAL Prcm EMIF PHY GCLK Clock */
    PMHAL_PRCM_CLK_EVE1_GFCLK = 21U,
    /**< PM HAL Prcm EVE1 GFCLK Clock */
    PMHAL_PRCM_CLK_GMAC_RFT_CLK = 22U,
    /**< PM HAL Prcm GMAC RFT CLK Clock */
    PMHAL_PRCM_CLK_GMAC_MAIN_CLK = 23U,
    /**< PM HAL Prcm GMAC MAIN CLK Clock */
    PMHAL_PRCM_CLK_GMII_250MHZ_CLK = 24U,
    /**< PM HAL Prcm GMII 250MHZ CLK Clock */
    PMHAL_PRCM_CLK_RMII_50MHZ_CLK = 25U,
    /**< PM HAL Prcm RMII 50MHZ CLK Clock */
    PMHAL_PRCM_CLK_RGMII_5MHZ_CLK = 26U,
    /**< PM HAL Prcm RGMII 5MHZ CLK Clock */
    PMHAL_PRCM_CLK_MCASP1_AHCLKR = 27U,
    /**< PM HAL Prcm MCASP1 AHCLKR Clock */
    PMHAL_PRCM_CLK_MCASP1_AHCLKX = 28U,
    /**< PM HAL Prcm MCASP1 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK = 29U,
    /**< PM HAL Prcm MCASP1 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER5_GFCLK = 30U,
    /**< PM HAL Prcm TIMER5 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER6_GFCLK = 31U,
    /**< PM HAL Prcm TIMER6 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER7_GFCLK = 32U,
    /**< PM HAL Prcm TIMER7 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER8_GFCLK = 33U,
    /**< PM HAL Prcm TIMER8 GFCLK Clock */
    PMHAL_PRCM_CLK_IPU1_GFCLK = 34U,
    /**< PM HAL Prcm IPU1 GFCLK Clock */
    PMHAL_PRCM_CLK_L3INIT_L3_GICLK = 35U,
    /**< PM HAL Prcm L3INIT L3 GICLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK = 36U,
    /**< PM HAL Prcm L3INSTR TS GCLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK = 37U,
    /**< PM HAL Prcm L3INSTR DLL AGING GCLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_L3_GICLK = 38U,
    /**< PM HAL Prcm L3INSTR L3 GICLK Clock */
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK = 39U,
    /**< PM HAL Prcm L3MAIN1 L3 GICLK Clock */
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK = 40U,
    /**< PM HAL Prcm L3MAIN1 L4 GICLK Clock */
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK = 41U,
    /**< PM HAL Prcm L4CFG L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK = 42U,
    /**< PM HAL Prcm L4CFG L4 GICLK Clock */
    PMHAL_PRCM_CLK_L4PER_L3_GICLK = 43U,
    /**< PM HAL Prcm L4PER L3 GICLK Clock */
    PMHAL_PRCM_CLK_PER_96M_GFCLK = 44U,
    /**< PM HAL Prcm PER 96M GFCLK Clock */
    PMHAL_PRCM_CLK_L4PER_L4_GICLK = 45U,
    /**< PM HAL Prcm L4PER L4 GICLK Clock */
    PMHAL_PRCM_CLK_TIMER2_GFCLK = 46U,
    /**< PM HAL Prcm TIMER2 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER3_GFCLK = 47U,
    /**< PM HAL Prcm TIMER3 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER4_GFCLK = 48U,
    /**< PM HAL Prcm TIMER4 GFCLK Clock */
    PMHAL_PRCM_CLK_PER_48M_GFCLK = 49U,
    /**< PM HAL Prcm PER 48M GFCLK Clock */
    PMHAL_PRCM_CLK_UART1_GFCLK = 50U,
    /**< PM HAL Prcm UART1 GFCLK Clock */
    PMHAL_PRCM_CLK_UART2_GFCLK = 51U,
    /**< PM HAL Prcm UART2 GFCLK Clock */
    PMHAL_PRCM_CLK_UART3_GFCLK = 52U,
    /**< PM HAL Prcm UART3 GFCLK Clock */
    PMHAL_PRCM_CLK_GPIO_GFCLK = 53U,
    /**< PM HAL Prcm GPIO GFCLK Clock */
    PMHAL_PRCM_CLK_L4PER_32K_GFCLK = 54U,
    /**< PM HAL Prcm L4PER 32K GFCLK Clock */
    PMHAL_PRCM_CLK_MMC4_GFCLK = 55U,
    /**< PM HAL Prcm MMC4 GFCLK Clock */
    PMHAL_PRCM_CLK_DCAN2_SYS_CLK = 56U,
    /**< PM HAL Prcm DCAN2 SYS CLK Clock */
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK = 57U,
    /**< PM HAL Prcm L4PER2 L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4PER2_L4_GICLK = 58U,
    /**< PM HAL Prcm L4PER2 L4 GICLK Clock */
    PMHAL_PRCM_CLK_QSPI_GFCLK = 59U,
    /**< PM HAL Prcm QSPI GFCLK Clock */
    PMHAL_PRCM_CLK_L4PER3_L3_GICLK = 60U,
    /**< PM HAL Prcm L4PER3 L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4PER3_L4_GICLK = 61U,
    /**< PM HAL Prcm L4PER3 L4 GICLK Clock */
    PMHAL_PRCM_CLK_VIP1_GCLK = 62U,
    /**< PM HAL Prcm VIP1 GCLK Clock */
    PMHAL_PRCM_CLK_ISS_GCLK = 63U,
    /**< PM HAL Prcm ISS GCLK Clock */
    PMHAL_PRCM_CLK_EMU_SYS_CLK = 64U,
    /**< PM HAL Prcm EMU SYS CLK Clock */
    PMHAL_PRCM_CLK_ADC_GFCLK = 65U,
    /**< PM HAL Prcm ADC GFCLK Clock */
    PMHAL_PRCM_CLK_ADC_L3_GICLK = 66U,
    /**< PM HAL Prcm ADC L3 GICLK Clock */
    PMHAL_PRCM_CLK_FUNC_32K_CLK = 67U,
    /**< PM HAL Prcm FUNC 32K CLK Clock */
    PMHAL_PRCM_CLK_WKUPAON_GICLK = 68U,
    /**< PM HAL Prcm WKUPAON GICLK Clock */
    PMHAL_PRCM_CLK_DCAN1_SYS_CLK = 69U,
    /**< PM HAL Prcm DCAN1 SYS CLK Clock */
    PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK = 70U,
    /**< PM HAL Prcm WKUPAON SYS GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER1_GFCLK = 71U,
    /**< PM HAL Prcm TIMER1 GFCLK Clock */
    PMHAL_PRCM_CLK_VID_PIX_CLK = 72U,
    /**< PM HAL Prcm VID_PIX_CLK Clock */
    PMHAL_PRCM_CLK_TESOC_EXT_CLK = 73U,
    /**< PM HAL Prcm TESOC_EXT_CLK Clock */
    PMHAL_PRCM_CLK_DEBUG_ATB_CLK = 74U,
    /**< PM HAL Prcm DEBUG_ATB_CLK Clock */
    PMHAL_PRCM_CLK_DEBUG_TREXCPT_CLK = 75U,
    /**< PM HAL Prcm DEBUG_TREXCPT_CLK Clock */
    PMHAL_PRCM_CLK_DEBUG_STMEXPT_CLK = 76U,
    /**< PM HAL Prcm DEBUG_STMEXPT_CLK Clock */
    PMHAL_PRCM_CLK_RTI1_CLK = 77U,
    /**< PM HAL Prcm RTI1_CLK Clock */
    PMHAL_PRCM_CLK_RTI2_CLK = 78U,
    /**< PM HAL Prcm RTI2_CLK Clock */
    PMHAL_PRCM_CLK_RTI3_CLK = 79U,
    /**< PM HAL Prcm RTI3_CLK Clock */
    PMHAL_PRCM_CLK_RTI4_CLK = 80U,
    /**< PM HAL Prcm RTI4_CLK Clock */
    PMHAL_PRCM_CLK_RTI5_CLK = 81U,
    /**< PM HAL Prcm RTI5_CLK Clock */
    PMHAL_PRCM_CLK_IPU_L3_GICLK = 82U,
    /**< PM HAL Prcm IPU L3 GICLK */
    PMHAL_PRCM_CLK_IPU_L4_GICLK = 83U,
    /**< PM HAL Prcm IPU L4 GICLK */
    PMHAL_PRCM_CLK_L3INSTR_L4_GICLK = 84U,
    /**< PM HAL Prcm L3INSTR L4 GICLK */
    PMHAL_PRCM_CLK_COREAON_L4_GICLK = 85U,
    /**< PM HAL Prcm Coreaon L4 GICLK */
    PMHAL_PRCM_CLK_CUSTEFUSE_L4_GICLK = 86U,
    /**< PM HAL Prcm Custefuse L4 GICLK */
    PMHAL_PRCM_CLK_L3INIT_L4_GICLK = 87U,
    /**< PM HAL Prcm L3init L4 GICLK */
    PMHAL_PRCM_CLK_MCAN_CLK = 88U,
    /**< PM HAL Prcm MCAN Clock : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MCASP2_AHCLKR = 89U,
    /**< PM HAL Prcm McASP2 AHCLKR : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MCASP2_AHCLKX = 90U,
    /**< PM HAL Prcm McASP2 AHCLKX : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK = 91U,
    /**< PM HAL Prcm McASP2 AUX_GFCLK : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MCASP3_AHCLKR = 92U,
    /**< PM HAL Prcm McASP3 AHCLKR : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MCASP3_AHCLKX = 93U,
    /**< PM HAL Prcm McASP3 AHCLKX : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK = 94U,
    /**< PM HAL Prcm McASP3 AUX_GFCLK : Kindly note this clock is present only
     *   in TDA3xx SR2.0 */
    PMHAL_PRCM_CLK_MAX = PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
    /**< Enum Upper bound */
    PMHAL_PRCM_CLK_COUNT = PMHAL_PRCM_CLK_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_CLK_GENERIC = 96U,
    /**< Generic Clock ID for user to return module functional clock.
     *  Refer PMLIB_CLK_RATE functions for more details.*/
    PMHAL_PRCM_CLK_UNDEF = 0x7FFFFFFFU
                           /**< Undefined value */
} pmhalPrcmClockId_t;

/**
 * \brief Reset Groups
 */
typedef enum pmhalPrcmResetGroupId
{
    PMHAL_PRCM_RG_LOWER_BOUND = (-(int32_t)1),
    /**< Lower bound placeholder */
    PMHAL_PRCM_RG_DSP1_RET_RST,
    /**< Reset Group DSP1 RET RST */
    PMHAL_PRCM_RG_DSP1_RST,
    /**< Reset Group DSP1 RST */
    PMHAL_PRCM_RG_DSP1_SYS_RST,
    /**< Reset Group DSP1 SYS RST */
    PMHAL_PRCM_RG_DSP2_RET_RST,
    /**< Reset Group DSP2 RET RST */
    PMHAL_PRCM_RG_DSP2_RST,
    /**< Reset Group DSP2 RST */
    PMHAL_PRCM_RG_DSP2_SYS_RST,
    /**< Reset Group DSP2 SYS RST */
    PMHAL_PRCM_RG_EVE1_CPU_RST,
    /**< Reset Group EVE1 CPU RST */
    PMHAL_PRCM_RG_EVE1_RST,
    /**< Reset Group EVE1 RST */
    PMHAL_PRCM_RG_IPU1_CPU0_RST,
    /**< Reset Group IPU1 CPU0 RST */
    PMHAL_PRCM_RG_IPU1_CPU1_RST,
    /**< Reset Group IPU1 CPU1 RST */
    PMHAL_PRCM_RG_IPU1_RET_RST,
    /**< Reset Group IPU1 RET RST */
    PMHAL_PRCM_RG_IPU1_RST,
    /**< Reset Group IPU1 RST */
    PMHAL_PRCM_RG_PROGRAMMABLE_RST_COUNT,
    /**< Enum upper bound count for programmable RST Domains for PRCM */
    PMHAL_PRCM_RG_CAM_RST,
    /**< Reset Group CAM RST */
    PMHAL_PRCM_RG_CM_CORE_AON_PWRON_RST,
    /**< Reset Group CM CORE AON PWRON RST */
    PMHAL_PRCM_RG_CM_CORE_AON_RST,
    /**< Reset Group CM CORE AON RST */
    PMHAL_PRCM_RG_CM_CORE_PWRON_RET_RST,
    /**< Reset Group CM CORE PWRON RET RST */
    PMHAL_PRCM_RG_CM_CORE_RET_RST,
    /**< Reset Group CM CORE RET RST */
    PMHAL_PRCM_RG_COREAON_PWRON_RST,
    /**< Reset Group COREAON PWRON RST */
    PMHAL_PRCM_RG_COREAON_RST,
    /**< Reset Group COREAON RST */
    PMHAL_PRCM_RG_CORE_PWRON_RET_RST,
    /**< Reset Group CORE PWRON RET RST */
    PMHAL_PRCM_RG_CORE_PWRON_RST,
    /**< Reset Group CORE PWRON RST */
    PMHAL_PRCM_RG_CORE_RET_RST,
    /**< Reset Group CORE RET RST */
    PMHAL_PRCM_RG_CORE_RST,
    /**< Reset Group CORE RST */
    PMHAL_PRCM_RG_CUSTEFUSE_RST,
    /**< Reset Group CUSTEFUSE RST */
    PMHAL_PRCM_RG_DLL_RST,
    /**< Reset Group DLL RST */
    PMHAL_PRCM_RG_DMA_RET_RST,
    /**< Reset Group DMA RET RST */
    PMHAL_PRCM_RG_DPLL_IVA_PWRON_RST,
    /**< Reset Group DPLL IVA PWRON RST */
    PMHAL_PRCM_RG_DSP1_PWRON_RST,
    /**< Reset Group DSP1 PWRON RST */
    PMHAL_PRCM_RG_DSP2_PWRON_RST,
    /**< Reset Group DSP2 PWRON RST */
    PMHAL_PRCM_RG_DSS_RET_RST,
    /**< Reset Group DSS RET RST */
    PMHAL_PRCM_RG_DSS_RST,
    /**< Reset Group DSS RST */
    PMHAL_PRCM_RG_EMU_EARLY_PWRON_RST,
    /**< Reset Group EMU EARLY PWRON RST */
    PMHAL_PRCM_RG_EMU_PWRON_RST,
    /**< Reset Group EMU PWRON RST */
    PMHAL_PRCM_RG_EMU_RST,
    /**< Reset Group EMU RST */
    PMHAL_PRCM_RG_EVE1_PWRON_RST,
    /**< Reset Group EVE1 PWRON RST */
    PMHAL_PRCM_RG_IPU1_PWRON_RST,
    /**< Reset Group IPU1 PWRON RST */
    PMHAL_PRCM_RG_IPU2_PWRON_RST,
    /**< Reset Group IPU2 PWRON RST */
    PMHAL_PRCM_RG_IPU_RET_RST,
    /**< Reset Group IPU RET RST */
    PMHAL_PRCM_RG_IPU_RST,
    /**< Reset Group IPU RST */
    PMHAL_PRCM_RG_L3INIT_PWRON_RST,
    /**< Reset Group L3INIT PWRON RST */
    PMHAL_PRCM_RG_L3INIT_RET_RST,
    /**< Reset Group L3INIT RET RST */
    PMHAL_PRCM_RG_L3INIT_RST,
    /**< Reset Group L3INIT RST */
    PMHAL_PRCM_RG_L4PER_PWRON_RET_RST,
    /**< Reset Group L4PER PWRON RET RST */
    PMHAL_PRCM_RG_L4PER_RET_RST,
    /**< Reset Group L4PER RET RST */
    PMHAL_PRCM_RG_L4PER_RST,
    /**< Reset Group L4PER RST */
    PMHAL_PRCM_RG_PRUSS1_RST,
    /**< Reset Group PRUSS1 RST */
    PMHAL_PRCM_RG_VPE_RST,
    /**< Reset Group VPE RST */
    PMHAL_PRCM_RG_WKUPAON_PWRON_RST,
    /**< Reset Group WKUPAON PWRON RST */
    PMHAL_PRCM_RG_WKUPAON_RST,
    /**< Reset Group WKUPAON RST */
    PMHAL_PRCM_RG_WKUPAON_SYS_PWRON_RST,
    /**< Reset Group WKUPAON SYS PWRON RST */
    PMHAL_PRCM_RG_PRM_PWRON_RST,
    /**< Reset Group PRM PWRON RST */
    PMHAL_PRCM_RG_PRM_RST,
    /**< Reset Group PRM RST */
    PMHAL_PRCM_RG_LPRM_PWRON_RST,
    /**< Reset Group LPRM PWRON RST */
    PMHAL_PRCM_RG_LPRM_RST,
    /**< Reset Group LPRM RST */
    PMHAL_PRCM_RG_COUNT
    /**< Enum Count */
} pmhalPrcmResetGroupId_t;

/**
 * \brief Reset List
 */
typedef enum pmhalPrcmGlobalResetGroupId
{
    PMHAL_PRCM_GLB_RG_LOWER_BOUND = (-(int32_t)1),
    /**< Lower bound (exclusive) */
    PMHAL_PRCM_GLB_RG_MIN = 0,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST = PMHAL_PRCM_GLB_RG_MIN,
    /**< Global Reset Group GLOBAL COLD RST */
    PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST = 1,
    /**< Global Reset Group GLOBAL  WARM SW RST */
    PMHAL_PRCM_GLB_RG_EXTERNAL_WARM_RST = 2,
    /**< Global Reset Group EXTERNAL WARM RST */
    PMHAL_PRCM_GLB_RG_ICEPICK_RST = 3,
    /**< Global Reset Group ICEPICK RST */
    PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST = 4,
    /**< Global Reset Group TSHUT_CORE RST */
    PMHAL_PRCM_GLB_RG_MAX = PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST,
    /**< Enum Upper bound */
    PMHAL_PRCM_GLB_RG_COUNT = PMHAL_PRCM_GLB_RG_MAX + 1,
    /**< Enum Count */
    PMHAL_PRCM_GLB_RG_UNDEF = 0x7FFFFFFF
                              /**< Undefined value */
} pmhalPrcmGlobalResetGroupId_t;

/**
 * \brief Reset List
 */
typedef enum pmhalPrcmResetId
{
    PMHAL_PRCM_RST_MIN = 0U,
    /**< Enum Lower bound */
    PMHAL_PRCM_RST_MAX = PMHAL_PRCM_RST_MIN,
    /**< Enum Upper bound */
    PMHAL_PRCM_RST_COUNT = PMHAL_PRCM_RST_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_RST_UNDEF = 0x7FFFFFFFU
                           /**< Undefined value */
} pmhalPrcmResetId_t;

/**
 * \brief Specification of Memory ON State
 */
typedef enum pmhalPrcmMemOnState
{
    MEM_ON_MIN = 0U,
    /**< Lower bound (inclusive) */
    MEM_ON_ALWAYS_ON = MEM_ON_MIN,
    /**<  Memory ON State ALWAYS ON */
    MEM_ON_SOFTWARE_CONTROL = 1U,
    /**<  Memory ON State SOFTWARE CONTROL */
    MEM_ON_MAX = MEM_ON_SOFTWARE_CONTROL,
    /**< Enum Upper bound */
    MEM_ON_COUNT = MEM_ON_MAX + 1U,
    /**< Enum Count */
    MEM_ON_UNDEF = 0x7FFFFFFFU
                   /**< Undefined value */
} pmhalPrcmMemOnState_t;

/**
 * \brief Specification of Memory Retention State
 */
typedef enum pmhalPrcmMemRetState
{
    MEM_RET_MIN = 0U,
    /**< Memory Retention State ALWAYS RETENTION */
    MEM_RET_ALWAYS_RETENTION = MEM_RET_MIN,
    /**< Lower bound (inclusive) */
    MEM_RET_SOFTWARE_CONTROL = 1U,
    /**< Memory Retention State SOFTWARE CONTROL */
    MEM_RET_ALWAYS_OFF = 2U,
    /**< Memory Retention State ALWAYS OFF */
    MEM_RET_MAX = MEM_RET_ALWAYS_OFF,
    /**< Enum Upper bound */
    MEM_RET_COUNT = MEM_RET_MAX + 1U,
    /**< Enum Count */
    MEM_RET_UNDEF = 0x7FFFFFFFU
                    /**< Undefined value */
} pmhalPrcmMemRetState_t;

/**
 * \brief Type of DPLL
 */
typedef enum pmhalPrcmDpllType
{
    PMHAL_PRCM_DPLL_TYPE_MIN = 0U,
    /**< DPLL Type of APLLPCIE */
    PMHAL_PRCM_DPLL_TYPE_APLLPCIE = PMHAL_PRCM_DPLL_TYPE_MIN,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_DPLL_TYPE_ADPLLM = 1U,
    /**< DPLL Type of ADPLLM */
    PMHAL_PRCM_DPLL_TYPE_ADPPLM = 2U,
    /**< DPLL Type of ADPPLM */
    PMHAL_PRCM_DPLL_TYPE_ADPLLLJM = 3U,
    /**< DPLL Type of ADPLLLJM */
    PMHAL_PRCM_DPLL_TYPE_MAX = PMHAL_PRCM_DPLL_TYPE_ADPLLLJM,
    /**< Enum Upper bound */
    PMHAL_PRCM_DPLL_TYPE_COUNT = PMHAL_PRCM_DPLL_TYPE_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_DPLL_TYPE_UNDEF = 0x7FFFFFFFU
                                 /**< Undefined value */
} pmhalPrcmDpllType_t;

/**
 * \brief PRCM Logic Retention Type
 */
typedef enum pmhalPrcmRetentionType
{
    PMHAL_PRCM_RT_MIN = 0U,
    /**< PM HAL Prcm Retention NO RETENTION */
    PMHAL_PRCM_RT_NO_RETENTION = PMHAL_PRCM_RT_MIN,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_RT_FULL_RETENTION = 1U,
    /**< PM HAL Prcm Retention FULL RETENTION */
    PMHAL_PRCM_RT_PARTIAL_RETENTION = 2U,
    /**< PM HAL Prcm Retention PARTIAL RETENTION */
    PMHAL_PRCM_RT_MAX = PMHAL_PRCM_RT_PARTIAL_RETENTION,
    /**< Enum Upper bound */
    PMHAL_PRCM_RT_COUNT = PMHAL_PRCM_RT_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_RT_UNDEF = 0x7FFFFFFFU
                          /**< Undefined value */
} pmhalPrcmRetentionType_t;

/**
 * \brief Physical Memory Bank
 */
typedef enum pmhalPrcmPhyMemBankId
{
    PMHAL_PRCM_PHY_BANK_VIP = 0U,
    /**< PM HAL Prcm Physical Memory Bank of VIP */
    PMHAL_PRCM_PHY_BANK_MIN = PMHAL_PRCM_PHY_BANK_VIP,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_PHY_BANK_CORE_OTHER_BANK = 1U,
    /**< PM HAL Prcm Physical Memory Bank of CORE_OTHER_BANK */
    PMHAL_PRCM_PHY_BANK_OCP_NRET_BANK = 2U,
    /**< PM HAL Prcm Physical Memory Bank of OCP_NRET_BANK */
    PMHAL_PRCM_PHY_BANK_CORE_OCMRAM = 3U,
    /**< PM HAL Prcm Physical Memory Bank of CORE_OCMRAM */
    PMHAL_PRCM_PHY_BANK_IPU_L2RAM = 4U,
    /**< PM HAL Prcm Physical Memory Bank of IPU_L2RAM */
    PMHAL_PRCM_PHY_BANK_IPU_UNICACHE = 5U,
    /**< PM HAL Prcm Physical Memory Bank of IPU_UNICACHE */
    PMHAL_PRCM_PHY_BANK_DSP1_EDMA = 6U,
    /**< PM HAL Prcm Physical Memory Bank of DSP1_EDMA */
    PMHAL_PRCM_PHY_BANK_DSP1_L1 = 7U,
    /**< PM HAL Prcm Physical Memory Bank of DSP1_L1 */
    PMHAL_PRCM_PHY_BANK_DSP1_L2 = 8U,
    /**< PM HAL Prcm Physical Memory Bank of DSP1_L2 */
    PMHAL_PRCM_PHY_BANK_DSP2_EDMA = 9U,
    /**< PM HAL Prcm Physical Memory Bank of DSP2_EDMA */
    PMHAL_PRCM_PHY_BANK_DSP2_L1 = 10U,
    /**< PM HAL Prcm Physical Memory Bank of DSP2_L1 */
    PMHAL_PRCM_PHY_BANK_DSP2_L2 = 11U,
    /**< PM HAL Prcm Physical Memory Bank of DSP2_L2 */
    PMHAL_PRCM_PHY_BANK_DSS_MEM = 12U,
    /**< PM HAL Prcm Physical Memory Bank of DSS_MEM */
    PMHAL_PRCM_PHY_BANK_EMU_BANK = 13U,
    /**< PM HAL Prcm Physical Memory Bank of EMU_BANK */
    PMHAL_PRCM_PHY_BANK_EVE1_BANK = 14U,
    /**< PM HAL Prcm Physical Memory Bank of EVE1_BANK */
    PMHAL_PRCM_PHY_BANK_AESSMEM = 15U,
    /**< PM HAL Prcm Physical Memory Bank of AESSMEM */
    PMHAL_PRCM_PHY_BANK_PERIPHMEM = 16U,
    /**< PM HAL Prcm Physical Memory Bank of PERIPHMEM */
    PMHAL_PRCM_PHY_BANK_L3INIT_BANK1 = 17U,
    /**< PM HAL Prcm Physical Memory Bank of L3INIT_BANK1 */
    PMHAL_PRCM_PHY_BANK_L3INIT_BANK2 = 18U,
    /**< PM HAL Prcm Physical Memory Bank of L3INIT_BANK2 */
    PMHAL_PRCM_PHY_BANK_GMAC_BANK = 19U,
    /**< PM HAL Prcm Physical Memory Bank of GMAC_BANK */
    PMHAL_PRCM_PHY_BANK_RETAINED_BANK = 20U,
    /**< PM HAL Prcm Physical Memory Bank of RETAINED_BANK */
    PMHAL_PRCM_PHY_BANK_NONRETAINED_BANK = 21U,
    /**< PM HAL Prcm Physical Memory Bank of NONRETAINED_BANK */
    PMHAL_PRCM_PHY_BANK_ISS_BANK = 22U,
    /**< PM HAL Prcm Physical Memory Bank of VPE_BANK */
    PMHAL_PRCM_PHY_BANK_WKUP_BANK = 23U,
    /**< PM HAL Prcm Physical Memory Bank of WKUP_BANK */
    PMHAL_PRCM_PHY_BANK_MAX = PMHAL_PRCM_PHY_BANK_WKUP_BANK,
    /**< Enum Upper bound */
    PMHAL_PRCM_PHY_BANK_COUNT = PMHAL_PRCM_PHY_BANK_MAX + 1U
                                /**< Enum Count */
} pmhalPrcmPhyMemBankId_t;

/**
 *  \brief Enum defining modules with SysConfig
 */
typedef enum pmhalPrcmSysConfigModuleId
{
    PMHAL_PRCM_SYSCFG_LOWER_BOUND = (-(int32_t)1),
    /**< Lower bound Place Holder(inclusive) */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    PMHAL_PRCM_SYSCFG_DSP1,
    /**< PM HAL Prcm SysConfig for DSP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    PMHAL_PRCM_SYSCFG_DSP2,
    /**< PRCM SysConfig for DSP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    PMHAL_PRCM_SYSCFG_DSS,
    /**< PRCM SysConfig for DSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILD_C66X
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    PMHAL_PRCM_SYSCFG_EVE1,
    /**< PRCM SysConfig for EVE1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    PMHAL_PRCM_SYSCFG_GPMC,
    /**< PRCM SysConfig for GPMC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILD_C66X
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    PMHAL_PRCM_SYSCFG_MMU_EDMA,
    /**< PRCM SysConfig for MMU_EDMA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_PRCM_SYSCFG_OCMC_RAM1,
    /**< PRCM SysConfig for OCMC_RAM1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    PMHAL_PRCM_SYSCFG_TESOC,
    /**< PRCM SysConfig for OCMC_RAM2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_PRCM_SYSCFG_SPINLOCK,
    /**< PRCM SysConfig for SPINLOCK */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_PRCM_SYSCFG_MAILBOX1,
    /**< PRCM SysConfig for MAILBOX1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_PRCM_SYSCFG_MAILBOX2,
    /**< PRCM SysConfig for MAILBOX2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_PRCM_SYSCFG_I2C1,
    /**< PRCM SysConfig for I2C1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_PRCM_SYSCFG_I2C2,
    /**< PRCM SysConfig for I2C2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    PMHAL_PRCM_SYSCFG_MCSPI1,
    /**< PRCM SysConfig for MCSPI1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    PMHAL_PRCM_SYSCFG_MCSPI2,
    /**< PRCM SysConfig for MCSPI2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    PMHAL_PRCM_SYSCFG_MCSPI3,
    /**< PRCM SysConfig for MCSPI3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    PMHAL_PRCM_SYSCFG_MCSPI4,
    /**< PRCM SysConfig for MCSPI4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    PMHAL_PRCM_SYSCFG_UART1,
    /**< PRCM SysConfig for UART1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    PMHAL_PRCM_SYSCFG_UART2,
    /**< PRCM SysConfig for UART2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    PMHAL_PRCM_SYSCFG_UART3,
    /**< PRCM SysConfig for UART3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    PMHAL_PRCM_SYSCFG_GPIO1,
    /**< PRCM SysConfig for GPIO1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    PMHAL_PRCM_SYSCFG_GPIO2,
    /**< PRCM SysConfig for GPIO2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    PMHAL_PRCM_SYSCFG_GPIO3,
    /**< PRCM SysConfig for GPIO3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    PMHAL_PRCM_SYSCFG_GPIO4,
    /**< PRCM SysConfig for GPIO4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_PRCM_SYSCFG_QSPI,
    /**< PRCM SysConfig for QSPI */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    PMHAL_PRCM_SYSCFG_VIP1,
    /**< PRCM SysConfig for VIP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    PMHAL_PRCM_SYSCFG_ISS,
    /**< PRCM SysConfig for ISS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    PMHAL_PRCM_SYSCFG_COUNTER_32K,
    /**< PRCM SysConfig for COUNTER_32K */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_PRCM_SYSCFG_ELM,
    /**< PRCM SysConfig for ELM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    PMHAL_PRCM_SYSCFG_ESM,
    /**< PRCM SysConfig for HDQ1W */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_PRCM_SYSCFG_PWMSS1,
    /**< PRCM SysConfig for PWMSS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_PRCM_SYSCFG_MMC4,
    /**< PRCM SysConfig for MMC4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    PMHAL_PRCM_SYSCFG_MCASP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifndef __TI_ARM_V7M4__
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    PMHAL_PRCM_SYSCFG_TPTC1,
    /**< PRCM SysConfig for TPTC1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    PMHAL_PRCM_SYSCFG_TPTC2,
    /**< PRCM SysConfig for TPTC2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#endif /* __TI_ARM_V7M4__ */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    PMHAL_PRCM_SYSCFG_MCASP2,
    /**< PRCM SysConfig for MCASP2: Kindly note this is applicable for
     *   TDA3xx SR2.0 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    PMHAL_PRCM_SYSCFG_MCASP3,
    /**< PRCM SysConfig for MCASP3: Kindly note this is applicable for
     *   TDA3xx SR2.0 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_PRCM_SYSCFG_CPGMAC,
    /**< PRCM SysConfig for CPGMACSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
    PMHAL_PRCM_SYSCFG_COUNT,
    /**< Enum Upper bound placeholder and Enum Count */
    PMHAL_PRCM_SYSCFG_NOTAPPLICABLE
    /**< Enum not applicable */
} pmhalPrcmSysConfigModuleId_t;

/**
 * \brief control module configured postdividers
 */
typedef enum pmhalCtrlMdlPostDivIdx
{
    PMHAL_CTRL_POSTDIV_DPLL_EVE_VID_DSP_M2 = 0U,
    /**< Enum Control module index of DPLL EVE VID DSP M2  */
    PMHAL_CTRL_POSTDIV_MIN = PMHAL_CTRL_POSTDIV_DPLL_EVE_VID_DSP_M2,
    /**< Lower bound (inclusive) */
    PMHAL_CTRL_POSTDIV_DPLL_PER_H14 = 1U,
    /**< Enum Control module index of DPLL PER H14  */
    PMHAL_CTRL_POSTDIV_DPLL_CORE_H11 = 2U,
    /**< Enum Control module index of DPLL CORE H11 */
    PMHAL_CTRL_POSTDIV_DPLL_CORE_H13 = 3U,
    /**< Enum Control module index of DPLL CORE H13 */
    PMHAL_CTRL_POSTDIV_DPLL_CORE_H21 = 4U,
    /**< Enum Control module index of DPLL CORE H21 */
    PMHAL_CTRL_POSTDIV_DPLL_DSP_GMAC_H14 = 5U,
    /**< Enum Control module index of DPLL CORE H21 */
    PMHAL_CTRL_POSTDIV_MAX = PMHAL_CTRL_POSTDIV_DPLL_DSP_GMAC_H14,
    /**< Enum Upper bound */
    PMHAL_CTRL_POSTDIV_COUNT = PMHAL_CTRL_POSTDIV_MAX + 1U,
    /**< Enum Count */
    PMHAL_CTRL_POSTDIV_NOTAPPLICABLE = 0xFFU
                                       /**< Undefined value */
} pmhalCtrlMdlPostDivIdx_t;

/**
 * \brief Clock Tree nodes - RootClk, Div, Mux, Pll
 */
typedef enum pmhalPrcmNodeId
{
    PMHAL_PRCM_ROOT_CLK_MIN = 0U,
    /**< PM HAL Prcm Root Clock for SYS CLKIN1 */
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1 = PMHAL_PRCM_ROOT_CLK_MIN,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_NODE_MIN = PMHAL_PRCM_ROOT_CLK_MIN,
    /**< Lower bound for Node */
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2 = 1U,
    /**< PM HAL Prcm Root Clock for SYS CLKIN2 */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0 = 2U,
    /**< PM HAL Prcm Root Clock for REF CLKIN0 */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1 = 3U,
    /**< PM HAL Prcm Root Clock for REF CLKIN1 */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2 = 4U,
    /**< PM HAL Prcm Root Clock for REF CLKIN2. Kindly note this clock
     *   is valid only for TDA3xx SR2.0 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0 = 5U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN0. Kindly note this clock
     *   is valid only for TDA3xx SR2.0 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1 = 6U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN1. Kindly note this clock
     *   is valid only for TDA3xx SR2.0 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2 = 7U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN2. Kindly note this clock
     *   is valid only for TDA3xx SR2.0 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3 = 8U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN3. Kindly note this clock
     *   is valid only for TDA3xx SR2.0 */
    PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC = 9U,
    /**< PM HAL Prcm Root Clock for SECURE_32K_CLK_SRC */
    PMHAL_PRCM_ROOT_CLK_BOARD_MAX = PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC,
    /**< PM HAL Prcm Root Clock maximum for Board configuration */
    PMHAL_PRCM_ROOT_CLK_MAX = PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC,
    /**< Enum Upper bound */
    PMHAL_PRCM_ROOT_CLK_COUNT = PMHAL_PRCM_ROOT_CLK_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_MUX_IPU1_GFCLK_MUX = 10U,
    /**< PM HAL Prcm Mux Element IPU1 GFCLK MUX */
    PMHAL_PRCM_MUX_MIN = PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_MUX_ADC_MUX = 11U,
    /**< PM HAL Prcm Mux Element ADC MUX */
    PMHAL_PRCM_MUX_EVE_GCLK_MUX = 12U,
    /**< PM HAL Prcm Mux Element EVE GCLK MUX */
    PMHAL_PRCM_MUX_QSPI_GFCLK_MUX = 13U,
    /**< PM HAL Prcm Mux Element QSPI GFCLK MUX */
    PMHAL_PRCM_MUX_VIP1_GCLK_MUX = 14U,
    /**< PM HAL Prcm Mux Element VIP1 GCLK MUX */
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX = 15U,
    /**< PM HAL Prcm Mux Element CLKOUTMUX0 CLK MUX */
    PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX = 16U,
    /**< PM HAL Prcm Mux Element CLKOUTMUX1 CLK MUX */
    PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX = 17U,
    /**< PM HAL Prcm Mux Element CLKOUTMUX2 CLK MUX */
    PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX = 18U,
    /**< PM HAL Prcm Mux Element GMAC RFT CLK MUX */
    PMHAL_PRCM_MUX_MMC4_GFCLK_MUX = 19U,
    /**< PM HAL Prcm Mux Element MMC4 GFCLK MUX */
    PMHAL_PRCM_MUX_RMII_50M_CLK_MUX = 20U,
    /**< PM HAL Prcm Mux Element RMII REF CLK MUX */
    PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX = 21U,
    /**< PM HAL Prcm Mux Element MCASP1 AUX GFCLK MUX */
    /**< PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX tied to SYSCLK1 */
    PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX = 22U,
    /**< PM HAL Prcm Mux Element MCASP1 AHCLKR MUX */
    PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX = 23U,
    /**< PM HAL Prcm Mux Element MCASP1 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX = 24U,
    /**< PM HAL Prcm Mux Element MCASP2 AUX GFCLK MUX. Kindly note this
     *   Mux is present only in TDA3xx SR2.0 */
    PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX = 25U,
    /**< PM HAL Prcm Mux Element MCASP2 AHCLKR MUX. Kindly note this
     *   Mux is present only in TDA3xx SR2.0 */
    PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX = 26U,
    /**< PM HAL Prcm Mux Element MCASP2 AHCLKX MUX Kindly note this
     *   Mux is present only in TDA3xx SR2.0 */
    PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX = 27U,
    /**< PM HAL Prcm Mux Element MCASP3 AUX GFCLK MUX. Kindly note this
     *   Mux is present only in TDA3xx SR2.0 */
    PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX = 28U,
    /**< PM HAL Prcm Mux Element MCASP3 AHCLKR MUX. Kindly note this
     *   Mux is present only in TDA3xx SR2.0 */
    PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX = 29U,
    /**< PM HAL Prcm Mux Element MCASP3 AHCLKX MUX Kindly note this
     *   Mux is present only in TDA3xx SR2.0 */
    PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX = 30U,
    /**< PM HAL Prcm Mux Element TIMER5 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX = 31U,
    /**< PM HAL Prcm Mux Element TIMER6 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX = 32U,
    /**< PM HAL Prcm Mux Element TIMER7 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX = 33U,
    /**< PM HAL Prcm Mux Element TIMER8 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX = 34U,
    /**< PM HAL Prcm Mux Element TIMER1 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX = 35U,
    /**< PM HAL Prcm Mux Element TIMER2 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX = 36U,
    /**< PM HAL Prcm Mux Element TIMER3 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX = 37U,
    /**< PM HAL Prcm Mux Element TIMER4 GFCLK MUX */
    PMHAL_PRCM_MUX_UART1_GFCLK_MUX = 38U,
    /**< PM HAL Prcm Mux Element UART1 GFCLK MUX */
    PMHAL_PRCM_MUX_UART2_GFCLK_MUX = 39U,
    /**< PM HAL Prcm Mux Element UART2 GFCLK MUX */
    PMHAL_PRCM_MUX_UART3_GFCLK_MUX = 40U,
    /**< PM HAL Prcm Mux Element UART3 GFCLK MUX */
    PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX = 41U,
    /**< PM HAL Prcm Mux Element DCAN1 SYS CLK MUX */
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX = 42U,
    /**< PM HAL Prcm Mux Element WKUPAON ICLK MUX */
    PMHAL_PRCM_MUX_EVE_CLK_MUX = 43U,
    /**< PM HAL Prcm Mux Element EVE CLK MUX */
    PMHAL_PRCM_MUX_DSP_GFCLK_MUX = 44U,
    /**< PM HAL Prcm Mux Element DSP GFCLK MUX */
    PMHAL_PRCM_MUX_RTI1_CLK_MUX = 45U,
    /**< PM HAL Prcm Mux Element RTI1 CLK MUX */
    PMHAL_PRCM_MUX_RTI2_CLK_MUX = 46U,
    /**< PM HAL Prcm Mux Element RTI2 CLK MUX */
    PMHAL_PRCM_MUX_RTI3_CLK_MUX = 47U,
    /**< PM HAL Prcm Mux Element RTI3 CLK MUX */
    PMHAL_PRCM_MUX_RTI4_CLK_MUX = 48U,
    /**< PM HAL Prcm Mux Element RTI4 CLK MUX */
    PMHAL_PRCM_MUX_RTI5_CLK_MUX = 49U,
    /**< PM HAL Prcm Mux Element RTI5 CLK MUX */
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX = 50U,
    /**< PM HAL Prcm Mux Element FUNC 32K CLK MUX */
    /**< DIV_FUNC_32K_CLK is the Valid selection for MUX_FUNC_32K_CLK_MUX */
    PMHAL_PRCM_MUX_DPLL_CORE_CLK = 51U,
    /**< PM HAL Prcm Mux Element DPLL CORE CLK MUX */
    PMHAL_PRCM_MUX_MAX = PMHAL_PRCM_MUX_DPLL_CORE_CLK,
    /**< Enum Upper bound */
    PMHAL_PRCM_MUX_COUNT = PMHAL_PRCM_MUX_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_DIV_ABE_24M_FCLK = 52U,
    /**< PM HAL Prcm Div Element ABE 24M FCLK */
    PMHAL_PRCM_DIV_MIN = PMHAL_PRCM_DIV_ABE_24M_FCLK,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_DIV_ABE_LP_CLK = 53U,
    /**< PM HAL Prcm Mux Element ABE LP CLK */
    PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK = 54U,
    /**< PM HAL Prcm Div Element DSP DPLL HS CLK */
    PMHAL_PRCM_DIV_FUNC_24M_CLK = 55U,
    /**< PM HAL Prcm Div Element FUNC 24M CLK */
    PMHAL_PRCM_DIV_L3_ICLK = 56U,
    /**< PM HAL Prcm Div Element L3 ICLK */
    PMHAL_PRCM_DIV_L4_ROOT_CLK = 57U,
    /**< PM HAL Prcm Div Element L4 ROOT CLK */
    PMHAL_PRCM_DIV_PER_DPLL_HS_CLK = 58U,
    /**< PM HAL Prcm Div Element PER DPLL HS CLK */
    PMHAL_PRCM_DIV_ABE_CLK = 59U,
    /**< PM HAL Prcm Div Element ABE CLK */
    PMHAL_PRCM_DIV_ABE_GICLK = 60U,
    /**< PM HAL Prcm Div Element ABE GICLK */
    PMHAL_PRCM_DIV_AESS_FCLK = 61U,
    /**< PM HAL Prcm Div Element ABE CLK */
    PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX = 62U,
    /**< PM HAL Prcm Div Element FUNC 128M CLK MUX */
    PMHAL_PRCM_DIV_QSPI_GFCLK = 63U,
    /**< PM HAL Prcm Div Element QSPI GFCLK */
    PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK = 64U,
    /**< PM HAL Prcm Div Element CORE DPLL OUT DCLK */
    PMHAL_PRCM_DIV_DSP_GCLK = 65U,
    /**< PM HAL Prcm Div Element DSP GCLK */
    PMHAL_PRCM_DIV_EMIF_PHY_DCLK = 66U,
    /**< PM HAL Prcm Div Element EMIF PHY DCLK */
    PMHAL_PRCM_DIV_EMU_DCLK = 67U,
    /**< PM HAL Prcm Div Element EMU DCLK */
    PMHAL_PRCM_DIV_EVE_DCLK = 68U,
    /**< PM HAL Prcm Div Element EVE DCLK */
    PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK = 69U,
    /**< PM HAL Prcm Div Element FUNC 96M AON DCLK */
    PMHAL_PRCM_DIV_GMAC_250M_DCLK = 70U,
    /**< PM HAL Prcm Div Element GMAC 250M DCLK */
    PMHAL_PRCM_DIV_GPU_DCLK = 71U,
    /**< PM HAL Prcm Div Element GPU DCLK */
    /**< Input to the PMHAL_PRCM_DIV_GPU_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_HDMI_DCLK = 72U,
    /**< PM HAL Prcm Div Element HDMI DCLK*/
    /**< Input to the PMHAL_PRCM_DIV_HDMI_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_IVA_DCLK = 73U,
    /**< PM HAL Prcm Div Element IVA DCLK */
    /**< Input to the PMHAL_PRCM_DIV_IVA_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_L3INIT_480M_DCLK = 74U,
    /**< PM HAL Prcm Div Element L3INIT 480M DCLK */
    /**< Input to the PMHAL_PRCM_DIV_L3INIT_480M_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_MPU_DCLK = 75U,
    /**< PM HAL Prcm Div Element MPU DCLK */
    /**< Input to the PMHAL_PRCM_DIV_MPU_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_PCIE2_DCLK = 76U,
    /**< PM HAL Prcm Div Element PCIE2 DCLK */
    /**< Input to the PMHAL_PRCM_DIV_PCIE2_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_PCIE_DCLK = 77U,
    /**< PM HAL Prcm Div Element PCIE DCLK */
    /**< Input to the PMHAL_PRCM_DIV_PCIE_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_PER_ABE_X1_DCLK = 78U,
    /**< PM HAL Prcm Div Element PER ABE X1 DCLK */
    /**< Input to the PMHAL_PRCM_DIV_PER_ABE_X1_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_SATA_DCLK = 79U,
    /**< PM HAL Prcm Div Element SATA DCLK */
    /**< Input to the PMHAL_PRCM_DIV_SATA_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_SECURE_32K_DCLK = 80U,
    /**< PM HAL Prcm Div Element SECURE_32K */
    PMHAL_PRCM_DIV_SYS_CLK1_DCLK = 81U,
    /**< PM HAL Prcm Div Element SYS CLK1 DCLK */
    PMHAL_PRCM_DIV_SYS_CLK2_DCLK = 82U,
    /**< PM HAL Prcm Div Element SYS CLK2 DCLK */
    PMHAL_PRCM_DIV_USB_OTG_DCLK = 83U,
    /**< PM HAL Prcm Div Element USB OTG DCLK */
    /**< Input to the PMHAL_PRCM_DIV_USB_OTG_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_VIDEO1_DCLK = 84U,
    /**< PM HAL Prcm Div Element VIDEO1 DCLK */
    /**< Input to the PMHAL_PRCM_DIV_VIDEO1_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_VIDEO2_DCLK = 85U,
    /**< PM HAL Prcm Div Element VIDEO2 DCLK */
    /**< Input to the PMHAL_PRCM_DIV_VIDEO2_DCLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_FUNC_48M_FCLK = 86U,
    /**< PM HAL Prcm Div Element FUNC 48M FCLK */
    PMHAL_PRCM_DIV_FUNC_96M_FCLK = 87U,
    /**< PM HAL Prcm Div Element FUNC 96M FCLK */
    PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK = 88U,
    /**< PM HAL Prcm Div Element GMAC GMII REF CLK */
    PMHAL_PRCM_DIV_MMC4_GFCLK = 89U,
    /**< PM HAL Prcm Div Element MMC4 GFCLK */
    PMHAL_PRCM_DIV_RGMII_5M_CLK = 90U,
    /**< PM HAL Prcm Div Element RGMII 5M REF CLK */
    PMHAL_PRCM_DIV_HDMI_CLK2 = 91U,
    /**< PM HAL Prcm Div Element HDMI CLK2 */
    /**< Input to the PMHAL_PRCM_DIV_HDMI_CLK2 is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2 = 92U,
    /**< PM HAL Prcm Div Element PER ABE X1 GFCLK2 */
    /**< Input to the PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2 is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_VIDEO1_CLK2 = 93U,
    /**< PM HAL Prcm Div Element VIDEO1 CLK2 */
    /**< Input to the PMHAL_PRCM_DIV_VIDEO1_CLK2 is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_VIDEO2_CLK2 = 94U,
    /**< PM HAL Prcm Div Element VIDEO2 CLK2 */
    /**< Input to the PMHAL_PRCM_DIV_VIDEO2_CLK2 is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_MLBP_CLK = 95U,
    /**< PM HAL Prcm Div Element MLBP CLK */
    /**< Input to the PMHAL_PRCM_DIV_MLBP_CLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_MLB_CLK = 96U,
    /**< PM HAL Prcm Div Element MLB CLK */
    /**< Input to the PMHAL_PRCM_DIV_MLB_CLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_HDMI_CLK = 97U,
    /**< PM HAL Prcm Div Element HDMI CLK */
    /**< Input to the PMHAL_PRCM_DIV_HDMI_CLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_VIDEO1_CLK = 98U,
    /**< PM HAL Prcm Div Element VIDEO1 CLK */
    /**< Input to the PMHAL_PRCM_DIV_VIDEO1_CLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_VIDEO2_CLK = 99U,
    /**< PM HAL Prcm Div Element VIDEO2 CLK */
    /**< Input to the PMHAL_PRCM_DIV_VIDEO2_CLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK = 100U,
    /**< PM HAL Prcm Div Element CUSTEFUSE SYS GFCLK */
    PMHAL_PRCM_DIV_ABE_SYS_CLK = 101U,
    /**< PM HAL Prcm Div Element ABE SYS CLK */
    /**< Input to the PMHAL_PRCM_DIV_ABE_SYS_CLK is tied to SYSCLK1 */
    PMHAL_PRCM_DIV_L3INSTR_TS_GCLK = 102U,
    /**< PM HAL Prcm Div Element L3INSTR TS GCLK */
    PMHAL_PRCM_DIV_TIMER_SYS_CLK = 103U,
    /**< PM HAL Prcm Div Element TIMER SYS CLK */
    PMHAL_PRCM_DIV_TESOC_EXT_CLK = 104U,
    /**< PM HAL Prcm Div Element TESOC EXT CLK */
    PMHAL_PRCM_DIV_VID_PIX_CLK = 105U,
    /**< PM HAL Prcm Div Element VID PIX CLK */
    PMHAL_PRCM_DIV_SYS_CLK1 = 106U,
    /**< PM HAL Prcm Div Element SYS CLK1 */
    PMHAL_PRCM_DIV_SYS_CLK2 = 107U,
    /**< PM HAL Prcm Div Element SYS CLK2 */
    PMHAL_PRCM_DIV_IPU1_GCLK = 108U,
    /**< PM HAL Prcm Div Element IPU1 GCLK */
    PMHAL_PRCM_DIV_FUNC_32K_CLK = 109U,
    /**< PM HAL Prcm Div Element FUNC 32K CLK */
    PMHAL_PRCM_DIV_MAX = PMHAL_PRCM_DIV_FUNC_32K_CLK,
    /**< Enum Upper bound */
    PMHAL_PRCM_DIV_COUNT = PMHAL_PRCM_DIV_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_DPLL_CORE = 110U,
    /**< PM HAL Prcm Dpll Element APLL PCIE */
    PMHAL_PRCM_DPLL_MIN = PMHAL_PRCM_DPLL_CORE,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_DPLL_DDR = 111U,
    /**< PM HAL Prcm Dpll Element DDR */
    PMHAL_PRCM_DPLL_DSP_GMAC = 112U,
    /**< PM HAL Prcm Dpll Element GMAC */
    PMHAL_PRCM_DPLL_PER = 113U,
    /**< PM HAL Prcm Dpll Element PER */
    PMHAL_PRCM_DPLL_EVE_VID_DSP = 114U,
    /**< PM HAL Prcm Dpll Element DSP */
    PMHAL_PRCM_DPLL_MAX = PMHAL_PRCM_DPLL_EVE_VID_DSP,
    /**< Enum Upper bound */
    PMHAL_PRCM_DPLL_COUNT = PMHAL_PRCM_DPLL_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_VIDEOPLL_MIN = PMHAL_PRCM_DPLL_EVE_VID_DSP,
    /**< Enum MIN bound for VIDEOPLL*/
    PMHAL_PRCM_VIDEOPLL_MAX = PMHAL_PRCM_DPLL_EVE_VID_DSP,
    /**< Upper bound for VIDEOPLL */
    PMHAL_PRCM_VIDEOPLL_COUNT = PMHAL_PRCM_VIDEOPLL_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_NODE_MAX = PMHAL_PRCM_DPLL_MAX,
    /**< Upper bound for Node */
    PMHAL_PRCM_NODE_COUNT = PMHAL_PRCM_DPLL_COUNT,
    /**< Enum Count for Node */
    PMHAL_PRCM_ROOT_CLK_UNDEF = 0x7FFFFFFFU,
    /**< Undefined value */
    PMHAL_PRCM_MUX_UNDEF = 0x7FFFFFFFU,
    /**< Undefined value */
    PMHAL_PRCM_DIV_UNDEF = 0x7FFFFFFFU,
    /**< Undefined value */
    PMHAL_PRCM_DPLL_UNDEF = 0x7FFFFFFFU,
    /**< Undefined value */
    PMHAL_PRCM_NODE_UNDEF = 0x7FFFFFFFU,
    /**< Undefined value */
    PMHAL_PRCM_VIDEOPLL_UNDEF = 0x7FFFFFFFU
                                /**< Undefined value */
} pmhalPrcmNodeId_t;

/**
 * \brief Modules (Clk Tree leaf nodes)
 */
typedef enum pmhalPrcmModuleId
{
    PMHAL_PRCM_MOD_LOWER_BOUND = PMHAL_PRCM_NODE_MAX,
    /**< Enum Lower bound placeholder */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
    PMHAL_PRCM_MOD_CRC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    PMHAL_PRCM_MOD_SMARTREFLEX_CORE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    PMHAL_PRCM_MOD_DSP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    PMHAL_PRCM_MOD_DSP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    PMHAL_PRCM_MOD_DSS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    PMHAL_PRCM_MOD_DLL,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    PMHAL_PRCM_MOD_EMIF1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    PMHAL_PRCM_MOD_EVE1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_PRCM_MOD_CPGMAC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    PMHAL_PRCM_MOD_MCASP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    PMHAL_PRCM_MOD_TIMER5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    PMHAL_PRCM_MOD_TIMER6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    PMHAL_PRCM_MOD_TIMER7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    PMHAL_PRCM_MOD_TIMER8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    PMHAL_PRCM_MOD_IPU1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    PMHAL_PRCM_MOD_IEEE1500_2_OCP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
    PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
    PMHAL_PRCM_MOD_DLL_AGING,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
    PMHAL_PRCM_MOD_L3_INSTR,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    PMHAL_PRCM_MOD_L3_MAIN_2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    PMHAL_PRCM_MOD_OCP_WP_NOC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    PMHAL_PRCM_MOD_GPMC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    PMHAL_PRCM_MOD_L3_MAIN_1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    PMHAL_PRCM_MOD_MMU_EDMA,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_PRCM_MOD_OCMC_RAM1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    PMHAL_PRCM_MOD_TESOC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
    PMHAL_PRCM_MOD_TPCC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    PMHAL_PRCM_MOD_TPTC1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    PMHAL_PRCM_MOD_TPTC2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    PMHAL_PRCM_MOD_L4_CFG,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_PRCM_MOD_SPINLOCK,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_PRCM_MOD_MAILBOX1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_PRCM_MOD_MAILBOX2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_PRCM_MOD_I2C1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_PRCM_MOD_I2C2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    PMHAL_PRCM_MOD_L4_PER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
    PMHAL_PRCM_MOD_DCC6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
    PMHAL_PRCM_MOD_DCC7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    PMHAL_PRCM_MOD_TIMER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    PMHAL_PRCM_MOD_TIMER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    PMHAL_PRCM_MOD_TIMER4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
    PMHAL_PRCM_MOD_DCC5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_PRCM_MOD_ELM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    PMHAL_PRCM_MOD_ESM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    PMHAL_PRCM_MOD_MCSPI1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    PMHAL_PRCM_MOD_MCSPI2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    PMHAL_PRCM_MOD_MCSPI3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    PMHAL_PRCM_MOD_MCSPI4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    PMHAL_PRCM_MOD_UART1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    PMHAL_PRCM_MOD_UART2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    PMHAL_PRCM_MOD_UART3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    PMHAL_PRCM_MOD_GPIO2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    PMHAL_PRCM_MOD_GPIO3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    PMHAL_PRCM_MOD_GPIO4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_PRCM_MOD_MMC4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    PMHAL_PRCM_MOD_DCAN2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    PMHAL_PRCM_MOD_L4_PER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    PMHAL_PRCM_MOD_ADC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_PRCM_MOD_PWMSS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_PRCM_MOD_QSPI,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    PMHAL_PRCM_MOD_L4_PER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
    PMHAL_PRCM_MOD_DCC1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
    PMHAL_PRCM_MOD_DCC2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
    PMHAL_PRCM_MOD_DCC3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
    PMHAL_PRCM_MOD_DCC4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    PMHAL_PRCM_MOD_VIP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    PMHAL_PRCM_MOD_ISS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    PMHAL_PRCM_MOD_DEBUG_LOGIC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    PMHAL_PRCM_MOD_COUNTER_32K,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
    PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    PMHAL_PRCM_MOD_DCAN1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    PMHAL_PRCM_MOD_GPIO1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    PMHAL_PRCM_MOD_L4_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
    PMHAL_PRCM_MOD_RTI1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
    PMHAL_PRCM_MOD_RTI2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
    PMHAL_PRCM_MOD_RTI3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
    PMHAL_PRCM_MOD_RTI4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
    PMHAL_PRCM_MOD_RTI5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    PMHAL_PRCM_MOD_TIMER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
    PMHAL_PRCM_MOD_CAMERARX,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    PMHAL_PRCM_MOD_MCAN,
    /* Kindly note this module is present only in TDA3xx SR2.0 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    PMHAL_PRCM_MOD_ATL,
    /* Kindly note this module is present only in TDA3xx SR2.0 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    PMHAL_PRCM_MOD_MCASP2,
    /* Kindly note this module is present only in TDA3xx SR2.0 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    PMHAL_PRCM_MOD_MCASP3,
    /* Kindly note this module is present only in TDA3xx SR2.0 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
    PMHAL_PRCM_MOD_COUNT,
    /**< Enum Upper bound placeholder */
    PMHAL_PRCM_MOD_UNDEF
    /**< Undefined value */
} pmhalPrcmModuleId_t;

/**
 *  \brief Enum defining the CPUs available in the SoC.
 */
typedef enum pmhalPrcmSocCpuId
{
    PMHAL_PRCM_SOC_CPU_ID_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_SOC_CPU_ID_MPU = PMHAL_PRCM_SOC_CPU_ID_MIN,
    /**< MPU CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_IPU1 = 0x1U,
    /**< IPU1 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_IPU2 = 0x2U,
    /**< IPU2 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_DSP1 = 0x3U,
    /**< DSP1 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_DSP2 = 0x4U,
    /**< DSP2 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_EVE1 = 0x5U,
    /**< EVE1 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_EVE2 = 0x6U,
    /**< EVE2 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_EVE3 = 0x7U,
    /**< EVE3 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_EVE4 = 0x8U,
    /**< EVE4 CPU Id Enumeration */
    PMHAL_PRCM_SOC_CPU_ID_MAX = PMHAL_PRCM_SOC_CPU_ID_EVE4
                                /**< Max value of the enum.
                                 * Can be used for validation. */
} pmhalPrcmSocCpuId_t;

/**
 *  \brief  Enum defining the interrupts supported by the PRM. The enumeration
 *          values correspond to their bit shifts. The bit shifts for MPU are
 *          slightly different than the other CPUs. This is taken care of in the
 *          API definition.
 */
typedef enum pmhalPrcmPrmIntId
{
    PMHAL_PRCM_PRM_INT_MIN = 0x0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_PRCM_PRM_INT_DPLL_CORE_RECAL = PMHAL_PRCM_PRM_INT_MIN,
    /**< DPLL_CORE_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_MPU_RECAL = 0x1U,
    /**< DPLL_MPU_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_IVA_RECAL = 0x2U,
    /**< DPLL_IVA_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_PER_RECAL = 0x3U,
    /**< DPLL_PER_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_ABE_RECAL = 0x4U,
    /**< DPLL_ABE_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_GMAC_RECAL = 0x5U,
    /**< DPLL_GMAC_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_GPU_RECAL = 0x6U,
    /**< DPLL_GPU_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_DDR_RECAL = 0x7U,
    /**< DPLL_DDR_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_TRANSITION = 0x8U,
    /**< TRANSITION Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_IO = 0x9U,
    /**< IO Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_FORCEWKUP = 0xAU,
    /**< FORCEWKUP Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_DSP_RECAL = 0xBU,
    /**< DPLL_DSP_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_DPLL_EVE_RECAL = 0xCU,
    /**< DPLL_EVE_RECAL Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_ABB_GPU_DONE = 0x1CU,
    /**< ABB_GPU_DONE Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_ABB_DSPEVE_DONE = 0x1DU,
    /**< ABB_DSPEVE_DONE Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_ABB_IVA_DONE = 0x1EU,
    /**< ABB_IVA_DONE Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_ABB_MPU_DONE = 0x1FU,
    /**< ABB_MPU_DONE Interrupt Enumeration */
    PMHAL_PRCM_PRM_INT_MAX = PMHAL_PRCM_PRM_INT_ABB_MPU_DONE
                             /**< Max Interrupt Number */
} pmhalPrcmPrmIntId_t;

/**
 * \brief Operating Performance Points
 */
typedef enum pmhalPrcmVmOppId
{
    PMHAL_VM_OPP_MIN = 0,
    /**< MIN Operating Point */
    PMHAL_VM_OPP_LOW = 0,
    /**< Low OPP_LOW Operating Point */
    PMHAL_VM_OPP_NOM = 1,
    /**< Nominal OPP_NOM Operating Point */
    PMHAL_VM_OPP_OD = 2,
    /**< Over Drive OPP_OD Operating Point */
    PMHAL_VM_OPP_HIGH = 3,
    /**< High OPP_HIGH Operating Point */
    PMHAL_VM_OPP_MAX = 4,
    /**< Maximum Operating Point */
    PMHAL_VM_OPP_UNDEF = (-(int32_t)1)
                         /**< Invalid Operating Point */
} pmhalVmOppId_t;

/**
 * \brief Enumeration of all the Modules that are associated with OPP.
 *        These are the processing units and Interconnect
 */
typedef enum pmhalPrcmCpuId
{
    PMHAL_PRCM_CPU_ID_MIN = 0,
    /**< Minimum CPU Index */
    PMHAL_PRCM_CPU_ID_IPU = PMHAL_PRCM_CPU_ID_MIN,
    /**< CPU Index for IPU */
    PMHAL_PRCM_CPU_ID_DSP = 1,
    /**< CPU Index for DSP */
    PMHAL_PRCM_CPU_ID_EVE = 2,
    /**< CPU Index for EVE */
    PMHAL_PRCM_CPU_ID_MAX = PMHAL_PRCM_CPU_ID_EVE,
    /**< Maximum CPU Index */
    PMHAL_PRCM_CPU_ID_COUNT = PMHAL_PRCM_CPU_ID_MAX + 1,
    /**< CPU Index Count */
    PMHAL_PRCM_CPU_ID_UNDEF = (-(int32_t)1)
                              /**< Undefined CPU Index */
} pmhalPrcmCpuId_t;

/**
 *  \brief Structure defining pll post divider value with post divider ID.
 *         User will use this struct to pass information to the prcm API's.
 *         The division values are 1-N (direct value written to register),
 *         so mapping to bit-field config value is not needed.
 */
typedef struct pmhalPrcmPllPostDivValue
{
    pmhalPrcmDpllPostDivId_t postDivId;
    /**< Unique Id of the post divider. */
    uint32_t                 configValue;
    /**< Division value. */
} pmhalPrcmPllPostDivValue_t;

/**
 * \brief This shall be used by the APIs to take configuration input from the
 *        user. This struct will not be modelled to represent a PLL.
 */
typedef struct pmhalPrcmDpllConfig
{
    uint16_t                    multiplier;
    /**< Multiplier value for DPLL configuration. */
    uint16_t                    divider;
    /**< Divider value for DPLL configuration. */
    uint32_t                    dutyCycleCorrector;
    /**< DutyCycleCorrector enable or disable */
    pmhalPrcmPllPostDivValue_t *postDivConfList;
    /**< List of post divider configuration values. */
    uint32_t                    maxPostDivElems;
    /**< Maximum postdivider elements. */
    uint32_t                    fracMultiplier;
    /**< Fractional Multipler for DPLL Configuration */
} pmhalPrcmDpllConfig_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_PRCM_H_ */

/* @} */


