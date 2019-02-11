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
 *  Consists of List of Domains and enum for the same,
 *  They can be divided as
 *      -   Power Domains
 *      -   Clock Domains
 *      -   Voltage Domains
 *      -   Reset Domains
 *
 *      Also provides API Infrastructure for the following:
 * @{
 */

/**
 *  \file      V0/pmhal_prcm.h
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
                                           *for validation. */
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
    /**< Static Dependency RESERVED_31 register bit shift */
    PMHAL_SD_SHIFT_ATL_STATDEP = 30U,
    /**< Static Dependency ATL register bit shift */
    PMHAL_SD_SHIFT_PCIE_STATDEP = 29U,
    /**< Static Dependency PCIE register bit shift */
    PMHAL_SD_SHIFT_VPE_STATDEP = 28U,
    /**< Static Dependency VPE register bit shift */
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
    PMHAL_SD_SHIFT_EVE4_STATDEP = 22U,
    /**< Static Dependency EVE4 register bit shift */
    PMHAL_SD_SHIFT_EVE3_STATDEP = 21U,
    /**< Static Dependency EVE3 register bit shift */
    PMHAL_SD_SHIFT_EVE2_STATDEP = 20U,
    /**< Static Dependency EVE2 register bit shift */
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
    PMHAL_SD_SHIFT_L4SEC_STATDEP = 14U,
    /**< Static Dependency L4SEC register bit shift */
    PMHAL_SD_SHIFT_L4PER_STATDEP = 13U,
    /**< Static Dependency L4PER register bit shift */
    PMHAL_SD_SHIFT_L4CFG_STATDEP = 12U,
    /**< Static Dependency L4CFG register bit shift */
    PMHAL_SD_SHIFT_SDMA_STATDEP = 11U,
    /**< Static Dependency SDMA register bit shift */
    PMHAL_SD_SHIFT_GPU_STATDEP = 10U,
    /**< Static Dependency GPU register bit shift */
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
    PMHAL_SD_SHIFT_IVA_STATDEP = 2U,
    /**< Static Dependency IVA register bit shift */
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
    PMHAL_PRCM_VD_MPU = PMHAL_PRCM_VD_MIN,
    /**< VD_MPU Voltage Domain */
    PMHAL_PRCM_VD_CORE = 1,
    /**< VD_MPU Voltage Domain */
    PMHAL_PRCM_VD_IVAHD = 2,
    /**< VD_MPU Voltage Domain */
    PMHAL_PRCM_VD_DSPEVE = 3,
    /**< VD_MPU Voltage Domain */
    PMHAL_PRCM_VD_GPU = 4,
    /**< VD_MPU Voltage Domain */
    PMHAL_PRCM_VD_RTC = 5,
    /**< VD_RTC Voltage Domain */
    PMHAL_PRCM_VD_MAX = PMHAL_PRCM_VD_RTC,
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
    PMHAL_PRCM_PMIC_REGULATOR_MPU = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for MPU */
    PMHAL_PRCM_PMIC_REGULATOR_CORE = 1,
    /**< Abstracted PMIC Regulator ID for CORE */
    PMHAL_PRCM_PMIC_REGULATOR_IVA = 2,
    /**< Abstracted PMIC Regulator ID for IVA */
    PMHAL_PRCM_PMIC_REGULATOR_DSPEVE = 3,
    /**< Abstracted PMIC Regulator ID for DSPEVE */
    PMHAL_PRCM_PMIC_REGULATOR_GPU = 4,
    /**< Abstracted PMIC Regulator ID for GPU */
    PMHAL_PRCM_PMIC_REGULATOR_MMC13V3 = 5,
    /**< Abstracted PMIC Regulator ID for MMC13V3 */
    PMHAL_PRCM_PMIC_REGULATOR_SHV5 = 6,
    /**< Abstracted PMIC Regulator ID for SHV5 */
    PMHAL_PRCM_PMIC_REGULATOR_1V8PHY = 7,
    /**< Abstracted PMIC Regulator ID for 1V8PHY */
    PMHAL_PRCM_PMIC_REGULATOR_1V8PLL = 8,
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
    PMHAL_PRCM_PD_EVE2,
    /**< EVE2 Power Domain */
    PMHAL_PRCM_PD_EVE3,
    /**< EVE3 Power Domain */
    PMHAL_PRCM_PD_EVE4,
    /**< EVE4 Power Domain */
    PMHAL_PRCM_PD_GPU,
    /**< GPU Power Domain */
    PMHAL_PRCM_PD_IPU,
    /**< IPU Power Domain */
    PMHAL_PRCM_PD_IVA,
    /**< IVA Power Domain */
    PMHAL_PRCM_PD_L3INIT,
    /**< L3INIT Power Domain */
    PMHAL_PRCM_PD_L4PER,
    /**< L4PER Power Domain */
    PMHAL_PRCM_PD_MMAON,
    /**< MMAON Power Domain */
    PMHAL_PRCM_PD_MPU,
    /**< MPU Power Domain */
    PMHAL_PRCM_PD_MPUAON,
    /**< MPUAON Power Domain */
    PMHAL_PRCM_PD_RTC,
    /**< RTC Power Domain */
    PMHAL_PRCM_PD_VPE,
    /**< VPE Power Domain */
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
    PMHAL_PRCM_CD_ATL,
    /**< ATL Clock Domain */
    PMHAL_PRCM_CD_DMA,
    /**< DMA Clock Domain */
    PMHAL_PRCM_CD_EMIF,
    /**< EMIF Clock Domain */
    PMHAL_PRCM_CD_IPU2,
    /**< IPU2 Clock Domain */
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
    PMHAL_PRCM_CD_EVE2,
    /**< EVE2 Clock Domain */
    PMHAL_PRCM_CD_EVE3,
    /**< EVE3 Clock Domain */
    PMHAL_PRCM_CD_EVE4,
    /**< EVE4 Clock Domain */
    PMHAL_PRCM_CD_GPU,
    /**< GPU Clock Domain */
    PMHAL_PRCM_CD_IPU1,
    /**< IPU1 Clock Domain */
    PMHAL_PRCM_CD_IPU,
    /**< IPU Clock Domain */
    PMHAL_PRCM_CD_IVA,
    /**< IVA Clock Domain */
    PMHAL_PRCM_CD_GMAC,
    /**< GMAC Clock Domain */
    PMHAL_PRCM_CD_L3INIT,
    /**< L3INIT Clock Domain */
    PMHAL_PRCM_CD_PCIE,
    /**< PCIE Clock Domain */
    PMHAL_PRCM_CD_L4PER2,
    /**< L4PER2 Clock Domain */
    PMHAL_PRCM_CD_L4PER3,
    /**< L4PER3 Clock Domain */
    PMHAL_PRCM_CD_L4PER,
    /**< L4PER Clock Domain */
    PMHAL_PRCM_CD_L4SEC,
    /**< L4SEC Clock Domain */
    PMHAL_PRCM_CD_MMAON,
    /**< MMAON Clock Domain */
    PMHAL_PRCM_CD_MPU,
    /**< MPU Clock Domain */
    PMHAL_PRCM_CD_MPUAON,
    /**< MPUAON Clock Domain */
    PMHAL_PRCM_CD_RTC,
    /**< RTC Clock Domain */
    PMHAL_PRCM_CD_VPE,
    /**< VPE Clock Domain */
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
    PMHAL_PRCM_CLK_ATL_L3_GICLK = 0U,
    /**< PM HAL Prcm ATL L3 GICLK Clock */
    PMHAL_PRCM_CLK_MIN = PMHAL_PRCM_CLK_ATL_L3_GICLK,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_CLK_ATL_L4_GICLK = 1U,
    /**< PM HAL Prcm ATL L4 GICLK Clock */
    PMHAL_PRCM_CLK_ATL_GFCLK = 2U,
    /**< PM HAL Prcm ATL GFCLK Clock */
    PMHAL_PRCM_CLK_ABE_GICLK = 3U,
    /**< PM HAL Prcm ABE GICLK Clock */
    PMHAL_PRCM_CLK_CLKOUTMUX1_CLK = 4U,
    /**< PM HAL Prcm CLKOUTMUX1 CLK Clock */
    PMHAL_PRCM_CLK_CLKOUTMUX2_CLK = 5U,
    /**< PM HAL Prcm CLKOUTMUX2 CLK Clock */
    PMHAL_PRCM_CLK_L3INIT_60M_FCLK = 6U,
    /**< PM HAL Prcm L3INIT 60M FCLK Clock */
    PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK = 7U,
    /**< PM HAL Prcm COREAON IO SRCOMP GFCLK Clock */
    PMHAL_PRCM_CLK_COREAON_L4_GICLK = 8U,
    /**< PM HAL Prcm COREAON L4 GICLK Clock */
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK = 9U,
    /**< PM HAL Prcm SR CORE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK = 10U,
    /**< PM HAL Prcm SR DSPEVE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK = 11U,
    /**< PM HAL Prcm SR GPU SYS GFCLK Clock */
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK = 12U,
    /**< PM HAL Prcm SR IVAHD SYS GFCLK Clock */
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK = 13U,
    /**< PM HAL Prcm SR MPU SYS GFCLK Clock */
    PMHAL_PRCM_CLK_COREAON_32K_GFCLK = 14U,
    /**< PM HAL Prcm COREAON 32K GFCLK Clock */
    PMHAL_PRCM_CLK_CUSTEFUSE_L4_GICLK = 15U,
    /**< PM HAL Prcm CUSTEFUSE L4 GICLK Clock */
    PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK = 16U,
    /**< PM HAL Prcm CUSTEFUSE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_DMA_L3_GICLK = 17U,
    /**< PM HAL Prcm DMA L3 GICLK Clock */
    PMHAL_PRCM_CLK_DMA_L4_GICLK = 18U,
    /**< PM HAL Prcm DMA L4 GICLK Clock */
    PMHAL_PRCM_CLK_DSP1_GFCLK = 19U,
    /**< PM HAL Prcm DSP1 GFCLK Clock */
    PMHAL_PRCM_CLK_DSP2_GFCLK = 20U,
    /**< PM HAL Prcm DSP2 GFCLK Clock */
    PMHAL_PRCM_CLK_BB2D_GFCLK = 21U,
    /**< PM HAL Prcm BB2D GFCLK Clock */
    PMHAL_PRCM_CLK_DSS_L3_GICLK = 22U,
    /**< PM HAL Prcm DSS L3 GICLK Clock */
    PMHAL_PRCM_CLK_HDMI_CEC_GFCLK = 23U,
    /**< PM HAL Prcm HDMI CEC GFCLK Clock */
    PMHAL_PRCM_CLK_HDMI_PHY_GFCLK = 24U,
    /**< PM HAL Prcm HDMI PHY GFCLK Clock */
    PMHAL_PRCM_CLK_DSS_GFCLK = 25U,
    /**< PM HAL Prcm DSS GFCLK Clock */
    PMHAL_PRCM_CLK_HDMI_DPLL_CLK = 26U,
    /**< PM HAL Prcm HDMI DPLL CLK Clock */
    PMHAL_PRCM_CLK_DSS_L4_GICLK = 27U,
    /**< PM HAL Prcm DSS L4 GICLK Clock */
    PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK = 28U,
    /**< PM HAL Prcm VIDEO1 DPLL CLK Clock */
    PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK = 29U,
    /**< PM HAL Prcm VIDEO2 DPLL CLK Clock */
    PMHAL_PRCM_CLK_SDVENC_GFCLK = 30U,
    /**< PM HAL Prcm SDVENC GFCLK Clock */
    PMHAL_PRCM_CLK_EMIF_DLL_GCLK = 31U,
    /**< PM HAL Prcm EMIF DLL GCLK Clock */
    PMHAL_PRCM_CLK_EMIF_L3_GICLK = 32U,
    /**< PM HAL Prcm EMIF L3 GICLK Clock */
    PMHAL_PRCM_CLK_EMIF_PHY_GCLK = 33U,
    /**< PM HAL Prcm EMIF PHY GCLK Clock */
    PMHAL_PRCM_CLK_EMIF_L4_GICLK = 34U,
    /**< PM HAL Prcm EMIF L4 GICLK Clock */
    PMHAL_PRCM_CLK_EVE1_GFCLK = 35U,
    /**< PM HAL Prcm EVE1 GFCLK Clock */
    PMHAL_PRCM_CLK_EVE2_GFCLK = 36U,
    /**< PM HAL Prcm EVE2 GFCLK Clock */
    PMHAL_PRCM_CLK_EVE3_GFCLK = 37U,
    /**< PM HAL Prcm EVE3 GFCLK Clock */
    PMHAL_PRCM_CLK_EVE4_GFCLK = 38U,
    /**< PM HAL Prcm EVE4 GFCLK Clock */
    PMHAL_PRCM_CLK_GMAC_RFT_CLK = 39U,
    /**< PM HAL Prcm GMAC RFT CLK Clock */
    PMHAL_PRCM_CLK_GMAC_MAIN_CLK = 40U,
    /**< PM HAL Prcm GMAC MAIN CLK Clock */
    PMHAL_PRCM_CLK_GMII_250MHZ_CLK = 41U,
    /**< PM HAL Prcm GMII 250MHZ CLK Clock */
    PMHAL_PRCM_CLK_RMII_50MHZ_CLK = 42U,
    /**< PM HAL Prcm RMII 50MHZ CLK Clock */
    PMHAL_PRCM_CLK_RGMII_5MHZ_CLK = 43U,
    /**< PM HAL Prcm RGMII 5MHZ CLK Clock */
    PMHAL_PRCM_CLK_GPU_CORE_GCLK = 44U,
    /**< PM HAL Prcm GPU CORE GCLK Clock */
    PMHAL_PRCM_CLK_GPU_HYD_GCLK = 45U,
    /**< PM HAL Prcm GPU HYD GCLK Clock */
    PMHAL_PRCM_CLK_GPU_L3_GICLK = 46U,
    /**< PM HAL Prcm GPU L3 GICLK Clock */
    PMHAL_PRCM_CLK_IPU_L3_GICLK = 47U,
    /**< PM HAL Prcm IPU L3 GICLK Clock */
    PMHAL_PRCM_CLK_IPU_96M_GFCLK = 48U,
    /**< PM HAL Prcm IPU 96M GFCLK Clock */
    PMHAL_PRCM_CLK_IPU_L4_GICLK = 49U,
    /**< PM HAL Prcm IPU L4 GICLK Clock */
    PMHAL_PRCM_CLK_MCASP1_AHCLKR = 50U,
    /**< PM HAL Prcm MCASP1 AHCLKR Clock */
    PMHAL_PRCM_CLK_MCASP1_AHCLKX = 51U,
    /**< PM HAL Prcm MCASP1 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK = 52U,
    /**< PM HAL Prcm MCASP1 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER5_GFCLK = 53U,
    /**< PM HAL Prcm TIMER5 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER6_GFCLK = 54U,
    /**< PM HAL Prcm TIMER6 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER7_GFCLK = 55U,
    /**< PM HAL Prcm TIMER7 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER8_GFCLK = 56U,
    /**< PM HAL Prcm TIMER8 GFCLK Clock */
    PMHAL_PRCM_CLK_UART6_GFCLK = 57U,
    /**< PM HAL Prcm UART6 GFCLK Clock */
    PMHAL_PRCM_CLK_IPU1_GFCLK = 58U,
    /**< PM HAL Prcm IPU1 GFCLK Clock */
    PMHAL_PRCM_CLK_IPU2_GFCLK = 59U,
    /**< PM HAL Prcm IPU2 GFCLK Clock */
    PMHAL_PRCM_CLK_IVA_GCLK = 60U,
    /**< PM HAL Prcm IVA GCLK Clock */
    PMHAL_PRCM_CLK_L3INIT_L3_GICLK = 61U,
    /**< PM HAL Prcm L3INIT L3 GICLK Clock */
    PMHAL_PRCM_CLK_L3INIT_L4_GICLK = 62U,
    /**< PM HAL Prcm L3INIT L4 GICLK Clock */
    PMHAL_PRCM_CLK_MMC1_GFCLK = 63U,
    /**< PM HAL Prcm MMC1 GFCLK Clock */
    PMHAL_PRCM_CLK_L3INIT_32K_GFCLK = 64U,
    /**< PM HAL Prcm L3INIT 32K GFCLK Clock */
    PMHAL_PRCM_CLK_MMC2_GFCLK = 65U,
    /**< PM HAL Prcm MMC2 GFCLK Clock */
    PMHAL_PRCM_CLK_MLB_SHB_L3_GICLK = 66U,
    /**< PM HAL Prcm MLB SHB L3 GICLK Clock */
    PMHAL_PRCM_CLK_MLB_SPB_L4_GICLK = 67U,
    /**< PM HAL Prcm MLB SPB L4 GICLK Clock */
    PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK = 68U,
    /**< PM HAL Prcm MLB SYS L3 GFCLK Clock */
    PMHAL_PRCM_CLK_L3INIT_48M_GFCLK = 69U,
    /**< PM HAL Prcm L3INIT 48M GFCLK Clock */
    PMHAL_PRCM_CLK_SATA_REF_GFCLK = 70U,
    /**< PM HAL Prcm SATA REF GFCLK Clock */
    PMHAL_PRCM_CLK_USB_LFPS_TX_GFCLK = 71U,
    /**< PM HAL Prcm USB LFPS TX GFCLK Clock */
    PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK = 72U,
    /**< PM HAL Prcm USB OTG SS REF CLK Clock */
    PMHAL_PRCM_CLK_L3INIT_960M_GFCLK = 73U,
    /**< PM HAL Prcm L3INIT 960M GFCLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK = 74U,
    /**< PM HAL Prcm L3INSTR TS GCLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK = 75U,
    /**< PM HAL Prcm L3INSTR DLL AGING GCLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_L3_GICLK = 76U,
    /**< PM HAL Prcm L3INSTR L3 GICLK Clock */
    PMHAL_PRCM_CLK_L3INSTR_L4_GICLK = 77U,
    /**< PM HAL Prcm L3INSTR L4 GICLK Clock */
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK = 78U,
    /**< PM HAL Prcm L3MAIN1 L3 GICLK Clock */
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK = 79U,
    /**< PM HAL Prcm L3MAIN1 L4 GICLK Clock */
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK = 80U,
    /**< PM HAL Prcm L4CFG L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK = 81U,
    /**< PM HAL Prcm L4CFG L4 GICLK Clock */
    PMHAL_PRCM_CLK_L4PER_L3_GICLK = 82U,
    /**< PM HAL Prcm L4PER L3 GICLK Clock */
    PMHAL_PRCM_CLK_PER_96M_GFCLK = 83U,
    /**< PM HAL Prcm PER 96M GFCLK Clock */
    PMHAL_PRCM_CLK_L4PER_L4_GICLK = 84U,
    /**< PM HAL Prcm L4PER L4 GICLK Clock */
    PMHAL_PRCM_CLK_TIMER10_GFCLK = 85U,
    /**< PM HAL Prcm TIMER10 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER11_GFCLK = 86U,
    /**< PM HAL Prcm TIMER11 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER2_GFCLK = 87U,
    /**< PM HAL Prcm TIMER2 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER3_GFCLK = 88U,
    /**< PM HAL Prcm TIMER3 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER4_GFCLK = 89U,
    /**< PM HAL Prcm TIMER4 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER9_GFCLK = 90U,
    /**< PM HAL Prcm TIMER9 GFCLK Clock */
    PMHAL_PRCM_CLK_PER_12M_GFCLK = 91U,
    /**< PM HAL Prcm PER 12M GFCLK Clock */
    PMHAL_PRCM_CLK_PER_48M_GFCLK = 92U,
    /**< PM HAL Prcm PER 48M GFCLK Clock */
    PMHAL_PRCM_CLK_UART1_GFCLK = 93U,
    /**< PM HAL Prcm UART1 GFCLK Clock */
    PMHAL_PRCM_CLK_UART2_GFCLK = 94U,
    /**< PM HAL Prcm UART2 GFCLK Clock */
    PMHAL_PRCM_CLK_UART3_GFCLK = 95U,
    /**< PM HAL Prcm UART3 GFCLK Clock */
    PMHAL_PRCM_CLK_UART4_GFCLK = 96U,
    /**< PM HAL Prcm UART4 GFCLK Clock */
    PMHAL_PRCM_CLK_UART5_GFCLK = 97U,
    /**< PM HAL Prcm UART5 GFCLK Clock */
    PMHAL_PRCM_CLK_GPIO_GFCLK = 98U,
    /**< PM HAL Prcm GPIO GFCLK Clock */
    PMHAL_PRCM_CLK_L4PER_32K_GFCLK = 99U,
    /**< PM HAL Prcm L4PER 32K GFCLK Clock */
    PMHAL_PRCM_CLK_MMC3_GFCLK = 100U,
    /**< PM HAL Prcm MMC3 GFCLK Clock */
    PMHAL_PRCM_CLK_MMC4_GFCLK = 101U,
    /**< PM HAL Prcm MMC4 GFCLK Clock */
    PMHAL_PRCM_CLK_DCAN2_SYS_CLK = 102U,
    /**< PM HAL Prcm DCAN2 SYS CLK Clock */
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK = 103U,
    /**< PM HAL Prcm L4PER2 L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4PER2_L4_GICLK = 104U,
    /**< PM HAL Prcm L4PER2 L4 GICLK Clock */
    PMHAL_PRCM_CLK_UART7_GFCLK = 105U,
    /**< PM HAL Prcm UART7 GFCLK Clock */
    PMHAL_PRCM_CLK_UART8_GFCLK = 106U,
    /**< PM HAL Prcm UART8 GFCLK Clock */
    PMHAL_PRCM_CLK_UART9_GFCLK = 107U,
    /**< PM HAL Prcm UART9 GFCLK Clock */
    PMHAL_PRCM_CLK_ICSS_IEP_CLK = 108U,
    /**< PM HAL Prcm ICSS IEP CLK Clock */
    PMHAL_PRCM_CLK_ICSS_CLK = 109U,
    /**< PM HAL Prcm ICSS CLK Clock */
    PMHAL_PRCM_CLK_PER_192M_GFCLK = 110U,
    /**< PM HAL Prcm PER 192M GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP2_AHCLKX = 111U,
    /**< PM HAL Prcm MCASP2 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP2_AHCLKR = 112U,
    /**< PM HAL Prcm MCASP2 AHCLKR Clock */
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK = 113U,
    /**< PM HAL Prcm MCASP2 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP3_AHCLKX = 114U,
    /**< PM HAL Prcm MCASP3 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK = 115U,
    /**< PM HAL Prcm MCASP3 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP4_AHCLKX = 116U,
    /**< PM HAL Prcm MCASP4 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK = 117U,
    /**< PM HAL Prcm MCASP4 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP5_AHCLKX = 118U,
    /**< PM HAL Prcm MCASP5 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK = 119U,
    /**< PM HAL Prcm MCASP5 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP6_AHCLKX = 120U,
    /**< PM HAL Prcm MCASP6 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK = 121U,
    /**< PM HAL Prcm MCASP6 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP7_AHCLKX = 122U,
    /**< PM HAL Prcm MCASP7 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK = 123U,
    /**< PM HAL Prcm MCASP7 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_MCASP8_AHCLKX = 124U,
    /**< PM HAL Prcm MCASP8 AHCLKX Clock */
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK = 125U,
    /**< PM HAL Prcm MCASP8 AUX GFCLK Clock */
    PMHAL_PRCM_CLK_QSPI_GFCLK = 126U,
    /**< PM HAL Prcm QSPI GFCLK Clock */
    PMHAL_PRCM_CLK_L4PER3_L3_GICLK = 127U,
    /**< PM HAL Prcm L4PER3 L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4PER3_L4_GICLK = 128U,
    /**< PM HAL Prcm L4PER3 L4 GICLK Clock */
    PMHAL_PRCM_CLK_TIMER13_GFCLK = 129U,
    /**< PM HAL Prcm TIMER13 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER14_GFCLK = 130U,
    /**< PM HAL Prcm TIMER14 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER15_GFCLK = 131U,
    /**< PM HAL Prcm TIMER15 GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER16_GFCLK = 132U,
    /**< PM HAL Prcm TIMER16 GFCLK Clock */
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK = 133U,
    /**< PM HAL Prcm L4SEC L3 GICLK Clock */
    PMHAL_PRCM_CLK_L4SEC_L4_GICLK = 134U,
    /**< PM HAL Prcm L4SEC L4 GICLK Clock */
    PMHAL_PRCM_CLK_MPU_GCLK = 135U,
    /**< PM HAL Prcm MPU GCLK Clock */
    PMHAL_PRCM_CLK_PCIE_32K_GFCLK = 136U,
    /**< PM HAL Prcm PCIE 32K GFCLK Clock */
    PMHAL_PRCM_CLK_PCIE_L3_GICLK = 137U,
    /**< PM HAL Prcm PCIE L3 GICLK Clock */
    PMHAL_PRCM_CLK_PCIE_PHY_GCLK = 138U,
    /**< PM HAL Prcm PCIE PHY GCLK Clock */
    PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK = 139U,
    /**< PM HAL Prcm PCIE PHY DIV GCLK Clock */
    PMHAL_PRCM_CLK_PCIE_REF_GFCLK = 140U,
    /**< PM HAL Prcm PCIE REF GFCLK Clock */
    PMHAL_PRCM_CLK_PCIE_SYS_GFCLK = 141U,
    /**< PM HAL Prcm PCIE SYS GFCLK Clock */
    PMHAL_PRCM_CLK_RTC_L4_GICLK = 142U,
    /**< PM HAL Prcm RTC L4 GICLK Clock */
    PMHAL_PRCM_CLK_RTC_AUX_CLK = 143U,
    /**< PM HAL Prcm RTC AUX CLK Clock */
    PMHAL_PRCM_CLK_LVDSRX_96M_GFCLK = 144U,
    /**< PM HAL Prcm LVDSRX 96M GFCLK Clock */
    PMHAL_PRCM_CLK_LVDSRX_L4_GICLK = 145U,
    /**< PM HAL Prcm LVDSRX L4 GICLK Clock */
    PMHAL_PRCM_CLK_VIP1_GCLK = 146U,
    /**< PM HAL Prcm VIP1 GCLK Clock */
    PMHAL_PRCM_CLK_VIP2_GCLK = 147U,
    /**< PM HAL Prcm VIP2 GCLK Clock */
    PMHAL_PRCM_CLK_VIP3_GCLK = 148U,
    /**< PM HAL Prcm VIP3 GCLK Clock */
    PMHAL_PRCM_CLK_VPE_GCLK = 149U,
    /**< PM HAL Prcm VPE GCLK Clock */
    PMHAL_PRCM_CLK_EMU_SYS_CLK = 150U,
    /**< PM HAL Prcm EMU SYS CLK Clock */
    PMHAL_PRCM_CLK_ADC_GFCLK = 151U,
    /**< PM HAL Prcm ADC GFCLK Clock */
    PMHAL_PRCM_CLK_ADC_L3_GICLK = 152U,
    /**< PM HAL Prcm ADC L3 GICLK Clock */
    PMHAL_PRCM_CLK_FUNC_32K_CLK = 153U,
    /**< PM HAL Prcm FUNC 32K CLK Clock */
    PMHAL_PRCM_CLK_WKUPAON_GICLK = 154U,
    /**< PM HAL Prcm WKUPAON GICLK Clock */
    PMHAL_PRCM_CLK_DCAN1_SYS_CLK = 155U,
    /**< PM HAL Prcm DCAN1 SYS CLK Clock */
    PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK = 156U,
    /**< PM HAL Prcm WKUPAON SYS GFCLK Clock */
    PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK = 157U,
    /**< PM HAL Prcm WKUPAON IO SRCOMP GFCLK Clock */
    PMHAL_PRCM_CLK_TIMER1_GFCLK = 158U,
    /**< PM HAL Prcm TIMER1 GFCLK Clock */
    PMHAL_PRCM_CLK_SECURE_32K_CLK = 159U,
    /**< PM HAL Prcm SECURE 32K CLK Clock */
    PMHAL_PRCM_CLK_UART10_GFCLK = 160U,
    /**< PM HAL Prcm UART10 GFCLK Clock */
    PMHAL_PRCM_CLK_RTC_32K_GFCLK = 161U,
    /**< PM HAL Prcm RTC 32K GFCLK Clock */
    PMHAL_PRCM_CLK_MAX = PMHAL_PRCM_CLK_RTC_32K_GFCLK,
    /**< Enum Upper bound */
    PMHAL_PRCM_CLK_COUNT = PMHAL_PRCM_CLK_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_CLK_GENERIC = 163U,
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
    PMHAL_PRCM_RG_EVE2_CPU_RST,
    /**< Reset Group EVE2 CPU RST */
    PMHAL_PRCM_RG_EVE2_RST,
    /**< Reset Group EVE2 RST */
    PMHAL_PRCM_RG_EVE3_CPU_RST,
    /**< Reset Group EVE3 CPU RST */
    PMHAL_PRCM_RG_EVE3_RST,
    /**< Reset Group EVE3 RST */
    PMHAL_PRCM_RG_EVE4_CPU_RST,
    /**< Reset Group EVE4 CPU RST */
    PMHAL_PRCM_RG_EVE4_RST,
    /**< Reset Group EVE4 RST */
    PMHAL_PRCM_RG_IPU1_CPU0_RST,
    /**< Reset Group IPU1 CPU0 RST */
    PMHAL_PRCM_RG_IPU1_CPU1_RST,
    /**< Reset Group IPU1 CPU1 RST */
    PMHAL_PRCM_RG_IPU1_RET_RST,
    /**< Reset Group IPU1 RET RST */
    PMHAL_PRCM_RG_IPU1_RST,
    /**< Reset Group IPU1 RST */
    PMHAL_PRCM_RG_IPU2_CPU0_RST,
    /**< Reset Group IPU2 CPU0 RST */
    PMHAL_PRCM_RG_IPU2_CPU1_RST,
    /**< Reset Group IPU2 CPU1 RST */
    PMHAL_PRCM_RG_IPU2_RET_RST,
    /**< Reset Group IPU2 RET RST */
    PMHAL_PRCM_RG_IPU2_RST,
    /**< Reset Group IPU2 RST */
#if defined (__ARM_ARCH_7A__)
    PMHAL_PRCM_RG_LPRM_MPU_C0_RST,
    /**< MPU LPRM'S Reset Group MPU C0 RST */
    PMHAL_PRCM_RG_LPRM_MPU_C1_RST,
    /**< MPU LPRM'S Reset Group MPU C1 RST */
#endif
    PMHAL_PRCM_RG_IVA_RST,
    /**< Reset Group IVA RST */
    PMHAL_PRCM_RG_IVA_SEQ1_RST,
    /**< Reset Group IVA SEQ1 RST */
    PMHAL_PRCM_RG_IVA_SEQ2_RST,
    /**< Reset Group IVA SEQ2 RST */
    PMHAL_PRCM_RG_PCIE1_RST,
    /**< Reset Group PCIE1 RST */
    PMHAL_PRCM_RG_PCIE2_RST,
    /**< Reset Group PCIE2 RST */
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
    PMHAL_PRCM_RG_DPLL_DSP_PWRON_RST,
    /**< Reset Group DPLL DSP PWRON RST */
    PMHAL_PRCM_RG_DPLL_EVE_PWRON_RST,
    /**< Reset Group DPLL EVE PWRON RST */
    PMHAL_PRCM_RG_DPLL_IVA_PWRON_RST,
    /**< Reset Group DPLL IVA PWRON RST */
    PMHAL_PRCM_RG_DPLL_L3INIT_PWRON_RET_RST,
    /**< Reset Group DPLL L3INIT PWRON RET RST */
    PMHAL_PRCM_RG_DPLL_MPU_PWRON_RST,
    /**< Reset Group DPLL MPU PWRON RST */
    PMHAL_PRCM_RG_DSP1_PWRON_RST,
    /**< Reset Group DSP1 PWRON RST */
    PMHAL_PRCM_RG_DSP2_PWRON_RST,
    /**< Reset Group DSP2 PWRON RST */
    PMHAL_PRCM_RG_DSS_RET_RST,
    /**< Reset Group DSS RET RST */
    PMHAL_PRCM_RG_DSS_RST,
    /**< Reset Group DSS RST */
    PMHAL_PRCM_RG_EMIF_DDR_PHY_PWRON_RST,
    /**< Reset Group EMIF DDR PHY PWRON RST */
    PMHAL_PRCM_RG_EMU_EARLY_PWRON_RST,
    /**< Reset Group EMU EARLY PWRON RST */
    PMHAL_PRCM_RG_EMU_PWRON_RST,
    /**< Reset Group EMU PWRON RST */
    PMHAL_PRCM_RG_EMU_RST,
    /**< Reset Group EMU RST */
    PMHAL_PRCM_RG_EVE1_PWRON_RST,
    /**< Reset Group EVE1 PWRON RST */
    PMHAL_PRCM_RG_EVE2_PWRON_RST,
    /**< Reset Group EVE2 PWRON RST */
    PMHAL_PRCM_RG_EVE3_PWRON_RST,
    /**< Reset Group EVE3 PWRON RST */
    PMHAL_PRCM_RG_EVE4_PWRON_RST,
    /**< Reset Group EVE4 PWRON RST */
    PMHAL_PRCM_RG_IPU1_PWRON_RST,
    /**< Reset Group IPU1 PWRON RST */
    PMHAL_PRCM_RG_IPU2_PWRON_RST,
    /**< Reset Group IPU2 PWRON RST */
    PMHAL_PRCM_RG_IPU_RET_RST,
    /**< Reset Group IPU RET RST */
    PMHAL_PRCM_RG_IPU_RST,
    /**< Reset Group IPU RST */
    PMHAL_PRCM_RG_IVA_PWRON_RST,
    /**< Reset Group IVA PWRON RST */
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
    PMHAL_PRCM_RG_MMAON_RST,
    /**< Reset Group MMAON RST */
    PMHAL_PRCM_RG_MPUAON_RST,
    /**< Reset Group MPUAON RST */
    PMHAL_PRCM_RG_MPU_L2RSTDISABLE,
    /**< Reset Group MPU L2RSTDISABLE */
    PMHAL_PRCM_RG_MPU_MA_PWRON_RET_RST,
    /**< Reset Group MPU MA PWRON RET RST */
    PMHAL_PRCM_RG_MPU_MA_RET_RST,
    /**< Reset Group MPU MA RET RST */
    PMHAL_PRCM_RG_MPU_MA_RST,
    /**< Reset Group MPU MA RST */
    PMHAL_PRCM_RG_MPU_PWRON_RST,
    /**< Reset Group MPU PWRON RST */
    PMHAL_PRCM_RG_MPU_RST,
    /**< Reset Group MPU RST */
    PMHAL_PRCM_RG_PRUSS1_RST,
    /**< Reset Group PRUSS1 RST */
    PMHAL_PRCM_RG_PRUSS2_RST,
    /**< Reset Group PRUSS2 RST */
    PMHAL_PRCM_RG_RTC_RST,
    /**< Reset Group RTC RST */
    PMHAL_PRCM_RG_VDD_CORE_ISO_RST,
    /**< Reset Group VDD CORE ISO RST */
    PMHAL_PRCM_RG_VDD_MM_ISO_RST,
    /**< Reset Group VDD MM ISO RST */
    PMHAL_PRCM_RG_VDD_MPU_ISO_RST,
    /**< Reset Group VDD MPU ISO RST */
    PMHAL_PRCM_RG_VDD_WKUP_ISO_RST,
    /**< Reset Group VDD WKUP ISO RST */
    PMHAL_PRCM_RG_VPE_RST,
    /**< Reset Group VPE RST */
    PMHAL_PRCM_RG_WKUPAON_PWRON_RST,
    /**< Reset Group WKUPAON PWRON RST */
    PMHAL_PRCM_RG_WKUPAON_RST,
    /**< Reset Group WKUPAON RST */
    PMHAL_PRCM_RG_WKUPAON_SYS_PWRON_RST,
    /**< Reset Group WKUPAON SYS PWRON RST */
    PMHAL_PRCM_RG_MPUON_RST,
    /**< Reset Group MPUON RST */
    PMHAL_PRCM_RG_PRM_PWRON_RST,
    /**< Reset Group PRM PWRON RST */
    PMHAL_PRCM_RG_PRM_RST,
    /**< Reset Group PRM RST */
    PMHAL_PRCM_RG_LPRM_PWRON_RST,
    /**< Reset Group LPRM PWRON RST */
    PMHAL_PRCM_RG_LPRM_RST,
    /**< Reset Group LPRM RST */
    PMHAL_PRCM_RG_LPRM_MPU_C0_PWRON_RST,
    /**< MPU LPRM'S Reset Group MPU C0 RST */
    PMHAL_PRCM_RG_LPRM_MPU_C1_PWRON_RST,
    /**< MPU LPRM'S Reset Group MPU C1 RST */
    PMHAL_PRCM_RG_GPU_RST,
    /**< Reset Group GPU RST */
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
    /**< Global Reset Group GLOBAL WARM SW RST */
    PMHAL_PRCM_GLB_RG_MPU_WDT_RST = 2,
    /**< Global Reset Group MPU WDT RST */
    PMHAL_PRCM_GLB_RG_EXTERNAL_WARM_RST = 3,
    /**< Global Reset Group EXTERNAL WARM RST */
    PMHAL_PRCM_GLB_RG_ICEPICK_RST = 4,
    /**< Global Reset Group ICEPICK RST */
    PMHAL_PRCM_GLB_RG_TSHUT_MPU_RST = 5,
    /**< Global Reset Group TSHUT MPU RST */
    PMHAL_PRCM_GLB_RG_TSHUT_MM_RST = 6,
    /**< Global Reset Group TSHUT MM RST */
    PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST = 7,
    /**< Global Reset Group TSHUT_CORE RST */
    PMHAL_PRCM_GLB_RG_TSHUT_DSPEVE_RST = 8,
    /**< Global Reset Group TSHUT DSPEVE RST */
    PMHAL_PRCM_GLB_RG_TSHUT_IVA_RST = 9,
    /**< Global Reset Group TSHUT IVA RST */
    PMHAL_PRCM_GLB_RG_MAX = PMHAL_PRCM_GLB_RG_TSHUT_IVA_RST,
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
 * \brief Physical Memories
 */
typedef enum pmhalPrcmPhyMemId
{
    PMHAL_PRCM_PHY_MEM_MIN = 0U,
    /**< PM HAL Prcm Physical Memory of ATL */
    PMHAL_PRCM_PHY_MEM_ATL = PMHAL_PRCM_PHY_MEM_MIN,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_PHY_MEM_DMA = 1U,
    /**< PM HAL Prcm Physical Memory of DMA */
    PMHAL_PRCM_PHY_MEM_DSP_DSP_DMA = 2U,
    /**< PM HAL Prcm Physical Memory of DSP DSP DMA */
    PMHAL_PRCM_PHY_MEM_DSP_L1 = 3U,
    /**< PM HAL Prcm Physical Memory of DSP L1 */
    PMHAL_PRCM_PHY_MEM_DSP_L2 = 4U,
    /**< PM HAL Prcm Physical Memory of DSP L2 */
    PMHAL_PRCM_PHY_MEM_BB2D = 5U,
    /**< PM HAL Prcm Physical Memory of BB2D */
    PMHAL_PRCM_PHY_MEM_DSSMEM = 6U,
    /**< PM HAL Prcm Physical Memory of DSSMEM */
    PMHAL_PRCM_PHY_MEM_DMM_MEMBANK1 = 7U,
    /**< PM HAL Prcm Physical Memory of DMM MEMBANK1 */
    PMHAL_PRCM_PHY_MEM_DMM_MEMBANK2 = 8U,
    /**< PM HAL Prcm Physical Memory of DMM MEMBANK2 */
    PMHAL_PRCM_PHY_MEM_EVE_BANK = 9U,
    /**< PM HAL Prcm Physical Memory of EVE BANK */
    PMHAL_PRCM_PHY_MEM_CPGMACSS_R_RAM_TX_DB = 10U,
    /**< PM HAL Prcm Physical Memory of CPGMACSS R RAM TX DB */
    PMHAL_PRCM_PHY_MEM_GPU = 11U,
    /**< PM HAL Prcm Physical Memory of GPU */
    PMHAL_PRCM_PHY_MEM_UART = 12U,
    /**< PM HAL Prcm Physical Memory of UART */
    PMHAL_PRCM_PHY_MEM_IPU_L2RAM = 13U,
    /**< PM HAL Prcm Physical Memory of IPU L2RAM */
    PMHAL_PRCM_PHY_MEM_IPU_UNICACHE_MEM = 14U,
    /**< PM HAL Prcm Physical Memory of IPU UNICACHE MEM */
    PMHAL_PRCM_PHY_MEM_HWA = 15U,
    /**< PM HAL Prcm Physical Memory of HWA */
    PMHAL_PRCM_PHY_MEM_TCM_1 = 16U,
    /**< PM HAL Prcm Physical Memory of TCM 1 */
    PMHAL_PRCM_PHY_MEM_TCM_2 = 17U,
    /**< PM HAL Prcm Physical Memory of TCM 2 */
    PMHAL_PRCM_PHY_MEM_SL2MEM = 18U,
    /**< PM HAL Prcm Physical Memory of SL2MEM */
    PMHAL_PRCM_PHY_MEM_MMC_RAM = 19U,
    /**< PM HAL Prcm Physical Memory of MMC RAM */
    PMHAL_PRCM_PHY_MEM_MLB = 20U,
    /**< PM HAL Prcm Physical Memory of MLB */
    PMHAL_PRCM_PHY_MEM_SATA_BANK = 21U,
    /**< PM HAL Prcm Physical Memory of SATA BANK */
    PMHAL_PRCM_PHY_MEM_USB = 22U,
    /**< PM HAL Prcm Physical Memory of USB */
    PMHAL_PRCM_PHY_MEM_OCPWP_BANK = 23U,
    /**< PM HAL Prcm Physical Memory of OCPWP BANK */
    PMHAL_PRCM_PHY_MEM_OCMC_RAM_BANK1 = 24U,
    /**< PM HAL Prcm Physical Memory of OCMC RAM BANK1 */
    PMHAL_PRCM_PHY_MEM_OCMC_ROM_MEM = 25U,
    /**< PM HAL Prcm Physical Memory of OCMC ROM MEM */
    PMHAL_PRCM_PHY_MEM_VCP_MEM = 26U,
    /**< PM HAL Prcm Physical Memory of VCP MEM */
    PMHAL_PRCM_PHY_MEM_TPCC = 27U,
    /**< PM HAL Prcm Physical Memory of TPCC */
    PMHAL_PRCM_PHY_MEM_TPTC = 28U,
    /**< PM HAL Prcm Physical Memory of TPTC */
    PMHAL_PRCM_PHY_MEM_DCAN = 29U,
    /**< PM HAL Prcm Physical Memory of DCAN */
    PMHAL_PRCM_PHY_MEM_IMEM3 = 30U,
    /**< PM HAL Prcm Physical Memory of IMEM3 */
    PMHAL_PRCM_PHY_MEM_DMA_CRYPTO = 31U,
    /**< PM HAL Prcm Physical Memory of DMA CRYPTO */
    PMHAL_PRCM_PHY_MEM_PKA_MEM = 32U,
    /**< PM HAL Prcm Physical Memory of PKA MEM */
    PMHAL_PRCM_PHY_MEM_MPU_L2 = 33U,
    /**< PM HAL Prcm Physical Memory of MPU L2 */
    PMHAL_PRCM_PHY_MEM_MPU_RAM = 34U,
    /**< PM HAL Prcm Physical Memory of MPU RAM */
    PMHAL_PRCM_PHY_MEM_PCIE = 35U,
    /**< PM HAL Prcm Physical Memory of PCIE */
    PMHAL_PRCM_PHY_MEM_VIP = 36U,
    /**< PM HAL Prcm Physical Memory of VIP */
    PMHAL_PRCM_PHY_MEM_VPE = 37U,
    /**< PM HAL Prcm Physical Memory of VPE */
    PMHAL_PRCM_PHY_MEM_DEBUGSS = 38U,
    /**< PM HAL Prcm Physical Memory of DEBUGSS */
    PMHAL_PRCM_PHY_MEM_SAR_BANK = 39U,
    /**< PM HAL Prcm Physical Memory of SAR BANK */
    PMHAL_PRCM_PHY_MEM_MAX = PMHAL_PRCM_PHY_MEM_SAR_BANK,
    /**< Enum Upper bound */
    PMHAL_PRCM_PHY_MEM_COUNT = PMHAL_PRCM_PHY_MEM_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_PHY_MEM_UNDEF = 0x7FFFFFFFU
                               /**< Undefined value */
} pmhalPrcmPhyMemId_t;

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
    PMHAL_PRCM_PHY_BANK_EVE2_BANK = 15U,
    /**< PM HAL Prcm Physical Memory Bank of EVE2_BANK */
    PMHAL_PRCM_PHY_BANK_EVE3_BANK = 16U,
    /**< PM HAL Prcm Physical Memory Bank of EVE3_BANK */
    PMHAL_PRCM_PHY_BANK_EVE4_BANK = 17U,
    /**< PM HAL Prcm Physical Memory Bank of EVE4_BANK */
    PMHAL_PRCM_PHY_BANK_GPU_MEM = 18U,
    /**< PM HAL Prcm Physical Memory Bank of GPU_MEM */
    PMHAL_PRCM_PHY_BANK_AESSMEM = 19U,
    /**< PM HAL Prcm Physical Memory Bank of AESSMEM */
    PMHAL_PRCM_PHY_BANK_PERIPHMEM = 20U,
    /**< PM HAL Prcm Physical Memory Bank of PERIPHMEM */
    PMHAL_PRCM_PHY_BANK_HWA_MEM = 21U,
    /**< PM HAL Prcm Physical Memory Bank of HWA_MEM */
    PMHAL_PRCM_PHY_BANK_TCM_1_MEM = 22U,
    /**< PM HAL Prcm Physical Memory Bank of TCM_1_MEM */
    PMHAL_PRCM_PHY_BANK_TCM_2_MEM = 23U,
    /**< PM HAL Prcm Physical Memory Bank of TCM_2_MEM */
    PMHAL_PRCM_PHY_BANK_SL2_MEM = 24U,
    /**< PM HAL Prcm Physical Memory Bank of SL2_MEM */
    PMHAL_PRCM_PHY_BANK_L3INIT_BANK1 = 25U,
    /**< PM HAL Prcm Physical Memory Bank of L3INIT_BANK1 */
    PMHAL_PRCM_PHY_BANK_L3INIT_BANK2 = 26U,
    /**< PM HAL Prcm Physical Memory Bank of L3INIT_BANK2 */
    PMHAL_PRCM_PHY_BANK_GMAC_BANK = 27U,
    /**< PM HAL Prcm Physical Memory Bank of GMAC_BANK */
    PMHAL_PRCM_PHY_BANK_RETAINED_BANK = 28U,
    /**< PM HAL Prcm Physical Memory Bank of RETAINED_BANK */
    PMHAL_PRCM_PHY_BANK_NONRETAINED_BANK = 29U,
    /**< PM HAL Prcm Physical Memory Bank of NONRETAINED_BANK */
    PMHAL_PRCM_PHY_BANK_MPU_L2 = 30U,
    /**< PM HAL Prcm Physical Memory Bank of MPU_L2 */
    PMHAL_PRCM_PHY_BANK_MPU_RAM = 31U,
    /**< PM HAL Prcm Physical Memory Bank of MPU_RAM */
    PMHAL_PRCM_PHY_BANK_VPE_BANK = 32U,
    /**< PM HAL Prcm Physical Memory Bank of VPE_BANK */
    PMHAL_PRCM_PHY_BANK_WKUP_BANK = 33U,
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
#if !defined (__TI_ARM_V7M4__)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    PMHAL_PRCM_SYSCFG_EVE1,
    /**< PRCM SysConfig for EVE1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE2
    PMHAL_PRCM_SYSCFG_EVE2,
    /**< PRCM SysConfig for EVE2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE3
    PMHAL_PRCM_SYSCFG_EVE3,
    /**< PRCM SysConfig for EVE3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE4
    PMHAL_PRCM_SYSCFG_EVE4,
    /**< PRCM SysConfig for EVE4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE4 */
#endif /* __TI_ARM_V7M4__ */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
    PMHAL_PRCM_SYSCFG_I2C5,
    /**< PRCM SysConfig for I2C5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    PMHAL_PRCM_SYSCFG_GPMC,
    /**< PRCM SysConfig for GPMC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    PMHAL_PRCM_SYSCFG_MMU_EDMA,
    /**< PRCM SysConfig for MMU_EDMA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
    PMHAL_PRCM_SYSCFG_MMU_PCIESS,
    /**< PRCM SysConfig for MMU_PCIESS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_PRCM_SYSCFG_OCMC_RAM1,
    /**< PRCM SysConfig for OCMC_RAM1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
    PMHAL_PRCM_SYSCFG_OCMC_RAM2,
    /**< PRCM SysConfig for OCMC_RAM2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
    PMHAL_PRCM_SYSCFG_OCMC_RAM3,
    /**< PRCM SysConfig for OCMC_RAM3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_PRCM_SYSCFG_SPINLOCK,
    /**< PRCM SysConfig for SPINLOCK */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_PRCM_SYSCFG_MAILBOX1,
    /**< PRCM SysConfig for MAILBOX1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
    PMHAL_PRCM_SYSCFG_MAILBOX10,
    /**< PRCM SysConfig for MAILBOX10 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
    PMHAL_PRCM_SYSCFG_MAILBOX11,
    /**< PRCM SysConfig for MAILBOX11 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
    PMHAL_PRCM_SYSCFG_MAILBOX12,
    /**< PRCM SysConfig for MAILBOX12 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
    PMHAL_PRCM_SYSCFG_MAILBOX13,
    /**< PRCM SysConfig for MAILBOX13 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_PRCM_SYSCFG_MAILBOX2,
    /**< PRCM SysConfig for MAILBOX2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
    PMHAL_PRCM_SYSCFG_MAILBOX3,
    /**< PRCM SysConfig for MAILBOX3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
    PMHAL_PRCM_SYSCFG_MAILBOX4,
    /**< PRCM SysConfig for MAILBOX4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
    PMHAL_PRCM_SYSCFG_MAILBOX5,
    /**< PRCM SysConfig for MAILBOX5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
    PMHAL_PRCM_SYSCFG_MAILBOX6,
    /**< PRCM SysConfig for MAILBOX6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
    PMHAL_PRCM_SYSCFG_MAILBOX7,
    /**< PRCM SysConfig for MAILBOX7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
    PMHAL_PRCM_SYSCFG_MAILBOX8,
    /**< PRCM SysConfig for MAILBOX8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
    PMHAL_PRCM_SYSCFG_MAILBOX9,
    /**< PRCM SysConfig for MAILBOX9 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_PRCM_SYSCFG_I2C1,
    /**< PRCM SysConfig for I2C1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_PRCM_SYSCFG_I2C2,
    /**< PRCM SysConfig for I2C2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
    PMHAL_PRCM_SYSCFG_I2C3,
    /**< PRCM SysConfig for I2C3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
    PMHAL_PRCM_SYSCFG_I2C4,
    /**< PRCM SysConfig for I2C4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
    PMHAL_PRCM_SYSCFG_UART4,
    /**< PRCM SysConfig for UART4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
    PMHAL_PRCM_SYSCFG_UART5,
    /**< PRCM SysConfig for UART5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
    PMHAL_PRCM_SYSCFG_GPIO5,
    /**< PRCM SysConfig for GPIO5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
    PMHAL_PRCM_SYSCFG_GPIO6,
    /**< PRCM SysConfig for GPIO6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
    PMHAL_PRCM_SYSCFG_GPIO7,
    /**< PRCM SysConfig for GPIO7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
    PMHAL_PRCM_SYSCFG_GPIO8,
    /**< PRCM SysConfig for GPIO8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
    PMHAL_PRCM_SYSCFG_UART7,
    /**< PRCM SysConfig for UART7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
    PMHAL_PRCM_SYSCFG_UART8,
    /**< PRCM SysConfig for UART8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
    PMHAL_PRCM_SYSCFG_UART9,
    /**< PRCM SysConfig for UART9 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_PRCM_SYSCFG_QSPI,
    /**< PRCM SysConfig for QSPI */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    PMHAL_PRCM_SYSCFG_VIP1,
    /**< PRCM SysConfig for VIP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP2
    PMHAL_PRCM_SYSCFG_VIP2,
    /**< PRCM SysConfig for VIP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP3
    PMHAL_PRCM_SYSCFG_VIP3,
    /**< PRCM SysConfig for VIP3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
    PMHAL_PRCM_SYSCFG_VPE,
    /**< PRCM SysConfig for VPE */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    PMHAL_PRCM_SYSCFG_COUNTER_32K,
    /**< PRCM SysConfig for COUNTER_32K */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    PMHAL_PRCM_SYSCFG_MCASP1,
    /**< PRCM SysConfig for MCASP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    PMHAL_PRCM_SYSCFG_MCASP2,
    /**< PRCM SysConfig for MCASP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    PMHAL_PRCM_SYSCFG_MCASP3,
    /**< PRCM SysConfig for MCASP3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
    PMHAL_PRCM_SYSCFG_MCASP4,
    /**< PRCM SysConfig for MCASP4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
    PMHAL_PRCM_SYSCFG_MCASP5,
    /**< PRCM SysConfig for MCASP5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
    PMHAL_PRCM_SYSCFG_MCASP6,
    /**< PRCM SysConfig for MCASP6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
    PMHAL_PRCM_SYSCFG_MCASP7,
    /**< PRCM SysConfig for MCASP7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
    PMHAL_PRCM_SYSCFG_MCASP8,
    /**< PRCM SysConfig for MCASP8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    PMHAL_PRCM_SYSCFG_PCIESS1,
    /**< PRCM SysConfig for PCIESS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    PMHAL_PRCM_SYSCFG_PCIESS2,
    /**< PRCM SysConfig for PCIESS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
    PMHAL_PRCM_SYSCFG_IVA,
    /**< PRCM SysConfig for IVA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
    PMHAL_PRCM_SYSCFG_OCP2SCP1,
    /**< PRCM SysConfig for OCP2SCP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
    PMHAL_PRCM_SYSCFG_OCP2SCP2,
    /**< PRCM SysConfig for OCP2SCP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
    PMHAL_PRCM_SYSCFG_OCP2SCP3,
    /**< PRCM SysConfig for OCP2SCP3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
    PMHAL_PRCM_SYSCFG_GPU,
    /**< PRCM SysConfig for GPU */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMM
    PMHAL_PRCM_SYSCFG_DMM,
    /**< PRCM SysConfig for DMM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_PRCM_SYSCFG_ELM,
    /**< PRCM SysConfig for ELM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
    PMHAL_PRCM_SYSCFG_DMA_SYSTEM,
    /**< PRCM SysConfig for DMA_SYSTEM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
    PMHAL_PRCM_SYSCFG_RTCSS,
    /**< PRCM SysConfig for RTCSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
    PMHAL_PRCM_SYSCFG_HDQ1W,
    /**< PRCM SysConfig for HDQ1W */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    PMHAL_PRCM_SYSCFG_USB_OTG_SS1,
    /**< PRCM SysConfig for USB_OTG_SS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
    PMHAL_PRCM_SYSCFG_USB_OTG_SS2,
    /**< PRCM SysConfig for USB_OTG_SS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
    PMHAL_PRCM_SYSCFG_USB_OTG_SS3,
    /**< PRCM SysConfig for USB_OTG_SS3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
    PMHAL_PRCM_SYSCFG_USB_OTG_SS4,
    /**< PRCM SysConfig for USB_OTG_SS4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
    PMHAL_PRCM_SYSCFG_SATA,
    /**< PRCM SysConfig for SATA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
    PMHAL_PRCM_SYSCFG_KBD,
    /**< PRCM SysConfig for KBD */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_PRCM_SYSCFG_PWMSS1,
    /**< PRCM SysConfig for PWMSS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
    PMHAL_PRCM_SYSCFG_PWMSS2,
    /**< PRCM SysConfig for PWMSS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
    PMHAL_PRCM_SYSCFG_PWMSS3,
    /**< PRCM SysConfig for PWMSS3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP1
    PMHAL_PRCM_SYSCFG_VCP1,
    /**< PRCM SysConfig for VCP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP2
    PMHAL_PRCM_SYSCFG_VCP2,
    /**< PRCM SysConfig for VCP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
    PMHAL_PRCM_SYSCFG_MMC1,
    /**< PRCM SysConfig for MMC1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
    PMHAL_PRCM_SYSCFG_MMC2,
    /**< PRCM SysConfig for MMC2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
    PMHAL_PRCM_SYSCFG_MMC3,
    /**< PRCM SysConfig for MMC3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_PRCM_SYSCFG_MMC4,
    /**< PRCM SysConfig for MMC4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_PRCM_SYSCFG_CPGMAC,
    /**< PRCM SysConfig for CPGMACSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
    PMHAL_PRCM_SYSCFG_MLB_SS,
    /**< PRCM SysConfig for CPGMACSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
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
    PMHAL_CTRL_POSTDIV_MIN = 0U,
    /**< Lower bound (inclusive) */
    PMHAL_CTRL_POSTDIV_MAX = PMHAL_CTRL_POSTDIV_MIN,
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
    /**< PM HAL Prcm Root Clock for PCIESREF ACS */
    PMHAL_PRCM_ROOT_CLK_PCIESREF_ACS = PMHAL_PRCM_ROOT_CLK_MIN,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_NODE_MIN = PMHAL_PRCM_ROOT_CLK_MIN,
    /**< Lower bound for Node */
    PMHAL_PRCM_ROOT_CLK_RMII = 1U,
    /**< PM HAL Prcm Root Clock for RMII */
    PMHAL_PRCM_ROOT_CLK_SYS_32K = 2U,
    /**< PM HAL Prcm Root Clock for SYS 32K */
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1 = 3U,
    /**< PM HAL Prcm Root Clock for SYS CLKIN1 */
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2 = 4U,
    /**< PM HAL Prcm Root Clock for SYS CLKIN2 */
    PMHAL_PRCM_ROOT_CLK_BOARD_MAX = PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    /**< PM HAL Prcm Root Clock maximum for Board configuration */
    PMHAL_PRCM_ROOT_CLK_EMU_CLKIN = 5U,
    /**< PM HAL Prcm Root Clock for EMU CLKIN */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0 = 6U,
    /**< PM HAL Prcm Root Clock for REF CLKIN0 */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1 = 7U,
    /**< PM HAL Prcm Root Clock for REF CLKIN1 */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2 = 8U,
    /**< PM HAL Prcm Root Clock for REF CLKIN2 */
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3 = 9U,
    /**< PM HAL Prcm Root Clock for REF CLKIN3 */
    PMHAL_PRCM_ROOT_CLK_SATA_CLKIN = 10U,
    /**< PM HAL Prcm Root Clock for SATA CLKIN */
    PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN = 11U,
    /**< PM HAL Prcm Root Clock for SDVENC CLKIN */
    PMHAL_PRCM_ROOT_CLK_USB_OTG_CLKIN = 12U,
    /**< PM HAL Prcm Root Clock for USB OTG CLKIN */
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3 = 13U,
    /**< PM HAL Prcm Root Clock for ATLCLKIN3 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0 = 14U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN0 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1 = 15U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN1 */
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2 = 16U,
    /**< PM HAL Prcm Root Clock for ATL CLKIN2 */
    PMHAL_PRCM_ROOT_CLK_MLBP_CLKIN = 17U,
    /**< PM HAL Prcm Root Clock for MLBP CLKIN */
    PMHAL_PRCM_ROOT_CLK_MLB_CLKIN = 18U,
    /**< PM HAL Prcm Root Clock for MLB CLKIN */
    PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC = 19U,
    /**< PM HAL Prcm Root Clock for SECURE 32K CLK SRC */
    PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN = 20U,
    /**< PM HAL Prcm Root Clock for VIDEO1 CLKIN */
    PMHAL_PRCM_ROOT_CLK_VIDEO1_M2_CLKIN = 21U,
    /**< PM HAL Prcm Root Clock for VIDEO1 M2 CLKIN */
    PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN = 22U,
    /**< PM HAL Prcm Root Clock for VIDEO2 CLKIN */
    PMHAL_PRCM_ROOT_CLK_VIDEO2_M2_CLKIN = 23U,
    /**< PM HAL Prcm Root Clock for VIDEO2 M2 CLKIN */
    PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN = 24U,
    /**< PM HAL Prcm Root Clock for HDMI CLKIN */
    PMHAL_PRCM_ROOT_CLK_MAX = PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN,
    /**< Enum Upper bound */
    PMHAL_PRCM_ROOT_CLK_COUNT = PMHAL_PRCM_ROOT_CLK_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX = 25U,
    /**< PM HAL Prcm Mux Element ATL DPLL CLK MUX */
    PMHAL_PRCM_MUX_MIN = PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_MUX_ATL_GFCLK_MUX = 26U,
    /**< PM HAL Prcm Mux Element ATL GFCLK MUX */
    PMHAL_PRCM_MUX_IPU1_GFCLK_MUX = 27U,
    /**< PM HAL Prcm Mux Element IPU1 GFCLK MUX */
    PMHAL_PRCM_MUX_ADC_GFCLK_MUX = 28U,
    /**< PM HAL Prcm Mux Element ADC GFCLK MUX */
    PMHAL_PRCM_MUX_EVE_GCLK_MUX = 29U,
    /**< PM HAL Prcm Mux Element EVE GCLK MUX */
    PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX = 30U,
    /**< PM HAL Prcm Mux Element GPU CORE GCLK MUX */
    PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX = 31U,
    /**< PM HAL Prcm Mux Element GPU HYD GCLK MUX */
    PMHAL_PRCM_MUX_QSPI_GFCLK_MUX = 32U,
    /**< PM HAL Prcm Mux Element QSPI GFCLK MUX */
    PMHAL_PRCM_MUX_VIP1_GCLK_MUX = 33U,
    /**< PM HAL Prcm Mux Element VIP1 GCLK MUX */
    PMHAL_PRCM_MUX_VIP2_GCLK_MUX = 34U,
    /**< PM HAL Prcm Mux Element VIP2 GCLK MUX */
    PMHAL_PRCM_MUX_VIP3_GCLK_MUX = 35U,
    /**< PM HAL Prcm Mux Element VIP3 GCLK MUX */
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX = 36U,
    /**< PM HAL Prcm Mux Element CLKOUTMUX0 CLK MUX */
    PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX = 37U,
    /**< PM HAL Prcm Mux Element CLKOUTMUX1 CLK MUX */
    PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX = 38U,
    /**< PM HAL Prcm Mux Element CLKOUTMUX2 CLK MUX */
    PMHAL_PRCM_MUX_MMC1_FCLK_MUX = 39U,
    /**< PM HAL Prcm Mux Element MMC1 FCLK MUX */
    PMHAL_PRCM_MUX_MMC2_FCLK_MUX = 40U,
    /**< PM HAL Prcm Mux Element MMC2 FCLK MUX */
    PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX = 41U,
    /**< PM HAL Prcm Mux Element GMAC RFT CLK MUX */
    PMHAL_PRCM_MUX_MMC3_GFCLK_MUX = 42U,
    /**< PM HAL Prcm Mux Element MMC3 GFCLK MUX */
    PMHAL_PRCM_MUX_MMC4_GFCLK_MUX = 43U,
    /**< PM HAL Prcm Mux Element MMC4 GFCLK MUX */
    PMHAL_PRCM_MUX_RMII_REF_CLK_MUX = 44U,
    /**< PM HAL Prcm Mux Element RMII REF CLK MUX */
    PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX = 45U,
    /**< PM HAL Prcm Mux Element MCASP1 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX = 46U,
    /**< PM HAL Prcm Mux Element MCASP2 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX = 47U,
    /**< PM HAL Prcm Mux Element MCASP3 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX = 48U,
    /**< PM HAL Prcm Mux Element MCASP4 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX = 49U,
    /**< PM HAL Prcm Mux Element MCASP5 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX = 50U,
    /**< PM HAL Prcm Mux Element MCASP6 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX = 51U,
    /**< PM HAL Prcm Mux Element MCASP7 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX = 52U,
    /**< PM HAL Prcm Mux Element MCASP8 AUX GFCLK MUX */
    PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX = 53U,
    /**< PM HAL Prcm Mux Element MCASP1 AHCLKR MUX */
    PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX = 54U,
    /**< PM HAL Prcm Mux Element MCASP1 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX = 55U,
    /**< PM HAL Prcm Mux Element MCASP2 AHCLKR MUX */
    PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX = 56U,
    /**< PM HAL Prcm Mux Element MCASP2 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX = 57U,
    /**< PM HAL Prcm Mux Element MCASP3 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX = 58U,
    /**< PM HAL Prcm Mux Element MCASP4 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX = 59U,
    /**< PM HAL Prcm Mux Element MCASP5 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX = 60U,
    /**< PM HAL Prcm Mux Element MCASP6 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX = 61U,
    /**< PM HAL Prcm Mux Element MCASP7 AHCLKX MUX */
    PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX = 62U,
    /**< PM HAL Prcm Mux Element MCASP8 AHCLK MUX */
    PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX = 63U,
    /**< PM HAL Prcm Mux Element TIMER5 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX = 64U,
    /**< PM HAL Prcm Mux Element TIMER6 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX = 65U,
    /**< PM HAL Prcm Mux Element TIMER7 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX = 66U,
    /**< PM HAL Prcm Mux Element TIMER8 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX = 67U,
    /**< PM HAL Prcm Mux Element TIMER1 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX = 68U,
    /**< PM HAL Prcm Mux Element TIMER2 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX = 69U,
    /**< PM HAL Prcm Mux Element TIMER3 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX = 70U,
    /**< PM HAL Prcm Mux Element TIMER4 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX = 71U,
    /**< PM HAL Prcm Mux Element TIMER10 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX = 72U,
    /**< PM HAL Prcm Mux Element TIMER11 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX = 73U,
    /**< PM HAL Prcm Mux Element TIMER9 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX = 74U,
    /**< PM HAL Prcm Mux Element TIMER13 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX = 75U,
    /**< PM HAL Prcm Mux Element TIMER14 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX = 76U,
    /**< PM HAL Prcm Mux Element TIMER15 GFCLK MUX */
    PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX = 77U,
    /**< PM HAL Prcm Mux Element TIMER16 GFCLK MUX */
    PMHAL_PRCM_MUX_UART10_GFCLK_MUX = 78U,
    /**< PM HAL Prcm Mux Element UART10 GFCLK MUX */
    PMHAL_PRCM_MUX_UART1_GFCLK_MUX = 79U,
    /**< PM HAL Prcm Mux Element UART1 GFCLK MUX */
    PMHAL_PRCM_MUX_UART2_GFCLK_MUX = 80U,
    /**< PM HAL Prcm Mux Element UART2 GFCLK MUX */
    PMHAL_PRCM_MUX_UART3_GFCLK_MUX = 81U,
    /**< PM HAL Prcm Mux Element UART3 GFCLK MUX */
    PMHAL_PRCM_MUX_UART4_GFCLK_MUX = 82U,
    /**< PM HAL Prcm Mux Element UART4 GFCLK MUX */
    PMHAL_PRCM_MUX_UART5_GFCLK_MUX = 83U,
    /**< PM HAL Prcm Mux Element UART5 GFCLK MUX */
    PMHAL_PRCM_MUX_UART6_GFCLK_MUX = 84U,
    /**< PM HAL Prcm Mux Element UART6 GFCLK MUX */
    PMHAL_PRCM_MUX_UART7_GFCLK_MUX = 85U,
    /**< PM HAL Prcm Mux Element UART7 GFCLK MUX */
    PMHAL_PRCM_MUX_UART8_GFCLK_MUX = 86U,
    /**< PM HAL Prcm Mux Element UART8 GFCLK MUX */
    PMHAL_PRCM_MUX_UART9_GFCLK_MUX = 87U,
    /**< PM HAL Prcm Mux Element UART9 GFCLK MUX */
    PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX = 88U,
    /**< PM HAL Prcm Mux Element ABE DPLL BYPAS CLK MUX */
    PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX = 89U,
    /**< PM HAL Prcm Mux Element ABE DPLL REF CLK MUX */
    PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX = 90U,
    /**< PM HAL Prcm Mux Element ABE DPLL SYS CLK MUX */
    PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX = 91U,
    /**< PM HAL Prcm Mux Element DCAN1 SYS CLK MUX */
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX = 92U,
    /**< PM HAL Prcm Mux Element WKUPAON ICLK MUX */
    PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX = 93U,
    /**< PM HAL Prcm Mux Element HDMI DPLL CLK MUX */
    PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX = 94U,
    /**< PM HAL Prcm Mux Element VIDEO1 DPLL CLK MUX */
    PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX = 95U,
    /**< PM HAL Prcm Mux Element VIDEO2 DPLL CLK MUX */
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX = 96U,
    /**< PM HAL Prcm Mux Element FUNC 32K CLK MUX */
    PMHAL_PRCM_MUX_VPE_GCLK_MUX = 97U,
    /**< PM HAL Prcm Mux Element for VPE Mux selection */
    PMHAL_PRCM_MUX_MAX = PMHAL_PRCM_MUX_VPE_GCLK_MUX,
    /**< Enum Upper bound */
    PMHAL_PRCM_MUX_COUNT = PMHAL_PRCM_MUX_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_DIV_ABE_24M_FCLK = 98U,
    /**< PM HAL Prcm Div Element ABE 24M FCLK */
    PMHAL_PRCM_DIV_MIN = PMHAL_PRCM_DIV_ABE_24M_FCLK,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_DIV_ABE_LP_CLK = 99U,
    /**< PM HAL Prcm Div Element ABE LP CLK */
    PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK = 100U,
    /**< PM HAL Prcm Div Element DSP DPLL HS CLK */
    PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK = 101U,
    /**< PM HAL Prcm Div Element EVE DPLL HS CLK */
    PMHAL_PRCM_DIV_FUNC_24M_CLK = 102U,
    /**< PM HAL Prcm Div Element FUNC 24M CLK */
    PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK = 103U,
    /**< PM HAL Prcm Div Element IVA DPLL HS CLK */
    PMHAL_PRCM_DIV_L3_ICLK = 104U,
    /**< PM HAL Prcm Div Element L3 ICLK */
    PMHAL_PRCM_DIV_L4_ROOT_CLK = 105U,
    /**< PM HAL Prcm Div Element L4 ROOT CLK */
    PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK = 106U,
    /**< PM HAL Prcm Div Element MPU DPLL HS CLK */
    PMHAL_PRCM_DIV_PER_DPLL_HS_CLK = 107U,
    /**< PM HAL Prcm Div Element PER DPLL HS CLK */
    PMHAL_PRCM_DIV_USB_DPLL_HS_CLK = 108U,
    /**< PM HAL Prcm Div Element USB DPLL HS CLK */
    PMHAL_PRCM_DIV_ABE_CLK = 109U,
    /**< PM HAL Prcm Div Element ABE CLK */
    PMHAL_PRCM_DIV_ABE_GICLK = 110U,
    /**< PM HAL Prcm Div Element ABE GICLK */
    PMHAL_PRCM_DIV_AESS_FCLK = 111U,
    /**< PM HAL Prcm Div Element AESS FCLK */
    PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX = 112U,
    /**< PM HAL Prcm Div Element FUNC 128M CLK MUX */
    PMHAL_PRCM_DIV_QSPI_GFCLK = 113U,
    /**< PM HAL Prcm Div Element QSPI GFCLK */
    PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK = 114U,
    /**< PM HAL Prcm Div Element CORE DPLL OUT DCLK */
    PMHAL_PRCM_DIV_DSP_GCLK = 115U,
    /**< PM HAL Prcm Div Element DSP GCLK */
    PMHAL_PRCM_DIV_EMIF_PHY_DCLK = 116U,
    /**< PM HAL Prcm Div Element EMIF PHY DCLK */
    PMHAL_PRCM_DIV_EMU_DCLK = 117U,
    /**< PM HAL Prcm Div Element EMU DCLK */
    PMHAL_PRCM_DIV_EVE_DCLK = 118U,
    /**< PM HAL Prcm Div Element EVE DCLK */
    PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK = 119U,
    /**< PM HAL Prcm Div Element FUNC 96M AON DCLK */
    PMHAL_PRCM_DIV_GMAC_250M_DCLK = 120U,
    /**< PM HAL Prcm Div Element GMAC 250M DCLK */
    PMHAL_PRCM_DIV_GPU_DCLK = 121U,
    /**< PM HAL Prcm Div Element GPU DCLK */
    PMHAL_PRCM_DIV_HDMI_DCLK = 122U,
    /**< PM HAL Prcm Div Element HDMI DCLK */
    PMHAL_PRCM_DIV_IVA_DCLK = 123U,
    /**< PM HAL Prcm Div Element IVA DCLK */
    PMHAL_PRCM_DIV_L3INIT_480M_DCLK = 124U,
    /**< PM HAL Prcm Div Element L3INIT 480M DCLK */
    PMHAL_PRCM_DIV_MPU_DCLK = 125U,
    /**< PM HAL Prcm Div Element MPU DCLK */
    PMHAL_PRCM_DIV_PCIE2_DCLK = 126U,
    /**< PM HAL Prcm Div Element PCIE2 DCLK */
    PMHAL_PRCM_DIV_PCIE_DCLK = 127U,
    /**< PM HAL Prcm Div Element PCIE DCLK */
    PMHAL_PRCM_DIV_PER_ABE_X1_DCLK = 128U,
    /**< PM HAL Prcm Div Element PER ABE X1 DCLK */
    PMHAL_PRCM_DIV_SATA_DCLK = 129U,
    /**< PM HAL Prcm Div Element SATA DCLK */
    PMHAL_PRCM_DIV_SECURE_32K_DCLK = 130U,
    /**< PM HAL Prcm Div Element SECURE 32K DCLK */
    PMHAL_PRCM_DIV_SYS_CLK1_DCLK = 131U,
    /**< PM HAL Prcm Div Element SYS CLK1 DCLK */
    PMHAL_PRCM_DIV_SYS_CLK2_DCLK = 132U,
    /**< PM HAL Prcm Div Element SYS CLK2 DCLK */
    PMHAL_PRCM_DIV_USB_OTG_DCLK = 133U,
    /**< PM HAL Prcm Div Element USB OTG DCLK */
    PMHAL_PRCM_DIV_VIDEO1_DCLK = 134U,
    /**< PM HAL Prcm Div Element VIDEO1 DCLK */
    PMHAL_PRCM_DIV_VIDEO2_DCLK = 135U,
    /**< PM HAL Prcm Div Element VIDEO2 DCLK */
    PMHAL_PRCM_DIV_FUNC_12M_FCLK = 136U,
    /**< PM HAL Prcm Div Element FUNC 12M FCLK */
    PMHAL_PRCM_DIV_FUNC_48M_FCLK = 137U,
    /**< PM HAL Prcm Div Element FUNC 48M FCLK */
    PMHAL_PRCM_DIV_FUNC_96M_FCLK = 138U,
    /**< PM HAL Prcm Div Element FUNC 96M FCLK */
    PMHAL_PRCM_DIV_MMC1_FCLK = 139U,
    /**< PM HAL Prcm Div Element MMC1 FCLK */
    PMHAL_PRCM_DIV_MMC2_FCLK = 140U,
    /**< PM HAL Prcm Div Element MMC2 FCLK */
    PMHAL_PRCM_DIV_L3INIT_60M_FCLK = 141U,
    /**< PM HAL Prcm Div Element L3INIT 60M FCLK */
    PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK = 142U,
    /**< PM HAL Prcm Div Element GMAC GMII REF CLK */
    PMHAL_PRCM_DIV_GMII_M_CLK = 143U,
    /**< PM HAL Prcm Div Element GMII M CLK */
    PMHAL_PRCM_DIV_MMC3_GFCLK = 144U,
    /**< PM HAL Prcm Div Element MMC3 GFCLK */
    PMHAL_PRCM_DIV_MMC4_GFCLK = 145U,
    /**< PM HAL Prcm Div Element MMC4 GFCLK */
    PMHAL_PRCM_DIV_RGMII_5M_REF_CLK = 146U,
    /**< PM HAL Prcm Div Element RGMII 5M REF CLK */
    PMHAL_PRCM_DIV_HDMI_CLK2 = 147U,
    /**< PM HAL Prcm Div Element HDMI CLK2 */
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2 = 148U,
    /**< PM HAL Prcm Div Element PER ABE X1 GFCLK2 */
    PMHAL_PRCM_DIV_VIDEO1_CLK2 = 149U,
    /**< PM HAL Prcm Div Element VIDEO1 CLK2 */
    PMHAL_PRCM_DIV_VIDEO2_CLK2 = 150U,
    /**< PM HAL Prcm Div Element VIDEO2 CLK2 */
    PMHAL_PRCM_DIV_MLBP_CLK = 151U,
    /**< PM HAL Prcm Div Element MLBP CLK */
    PMHAL_PRCM_DIV_MLB_CLK = 152U,
    /**< PM HAL Prcm Div Element MLB CLK */
    PMHAL_PRCM_DIV_HDMI_CLK = 153U,
    /**< PM HAL Prcm Div Element HDMI CLK */
    PMHAL_PRCM_DIV_VIDEO1_CLK = 154U,
    /**< PM HAL Prcm Div Element VIDEO1 CLK */
    PMHAL_PRCM_DIV_VIDEO2_CLK = 155U,
    /**< PM HAL Prcm Div Element VIDEO2 CLK */
    PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK = 156U,
    /**< PM HAL Prcm Div Element CUSTEFUSE SYS GFCLK */
    PMHAL_PRCM_DIV_ABE_SYS_CLK = 157U,
    /**< PM HAL Prcm Div Element ABE SYS CLK */
    PMHAL_PRCM_DIV_L3INSTR_TS_GCLK = 158U,
    /**< PM HAL Prcm Div Element L3INSTR TS GCLK */
    PMHAL_PRCM_DIV_TIMER_SYS_CLK = 159U,
    /**< PM HAL Prcm Div Element TIMER SYS CLK */
    PMHAL_PRCM_DIV_IPU1_GCLK = 160U,
    /**< PM HAL Prcm Div Element IPU1 GCLK */
    PMHAL_PRCM_DIV_IPU2_GCLK = 161U,
    /**< PM HAL Prcm Div Element IPU2 GCLK */
    PMHAL_PRCM_DIV_FUNC_32K_CLK = 162U,
    /**< PM HAL Prcm Div Element FUNC 32K CLK */
    PMHAL_PRCM_DIV_VPE_GCLK = 163U,
    /**< PM HAL Prcm Div Element VPE GCLK */
    PMHAL_PRCM_DIV_MAX = PMHAL_PRCM_DIV_VPE_GCLK,
    /**< Enum Upper bound */
    PMHAL_PRCM_DIV_COUNT = PMHAL_PRCM_DIV_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_DPLL_APLL_PCIE = 164U,
    /**< PM HAL Prcm Dpll Element APLL PCIE */
    PMHAL_PRCM_DPLL_MIN = PMHAL_PRCM_DPLL_APLL_PCIE,
    /**< Lower bound (inclusive) */
    PMHAL_PRCM_DPLL_ABE = 165U,
    /**< PM HAL Prcm Dpll Element ABE */
    PMHAL_PRCM_DPLL_CORE = 166U,
    /**< PM HAL Prcm Dpll Element CORE */
    PMHAL_PRCM_DPLL_DDR = 167U,
    /**< PM HAL Prcm Dpll Element DDR */
    PMHAL_PRCM_DPLL_GMAC = 168U,
    /**< PM HAL Prcm Dpll Element GMAC */
    PMHAL_PRCM_DPLL_GPU = 169U,
    /**< PM HAL Prcm Dpll Element GPU */
    PMHAL_PRCM_DPLL_IVA = 170U,
    /**< PM HAL Prcm Dpll Element IVA */
    PMHAL_PRCM_DPLL_PCIE_REF = 171U,
    /**< PM HAL Prcm Dpll Element PCIE REF */
    PMHAL_PRCM_DPLL_PER = 172U,
    /**< PM HAL Prcm Dpll Element PER */
    PMHAL_PRCM_DPLL_USB = 173U,
    /**< PM HAL Prcm Dpll Element USB */
    PMHAL_PRCM_DPLL_DSP = 174U,
    /**< PM HAL Prcm Dpll Element DSP */
    PMHAL_PRCM_DPLL_EVE = 175U,
    /**< PM HAL Prcm Dpll Element EVE */
    PMHAL_PRCM_DPLL_MPU = 176U,
    /**< PM HAL Prcm Dpll Element MPU */
    PMHAL_PRCM_DPLL_MAX = PMHAL_PRCM_DPLL_MPU,
    /**< Enum Upper bound */
    PMHAL_PRCM_DPLL_COUNT = PMHAL_PRCM_DPLL_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_VIDEOPLL_VIDEO1 = 177U,
    /**< PM HAL Prcm Videopll Element VIDEO1 */
    PMHAL_PRCM_VIDEOPLL_MIN = PMHAL_PRCM_VIDEOPLL_VIDEO1,
    /**< Lower bound for Video Dpll */
    PMHAL_PRCM_VIDEOPLL_VIDEO2 = 178U,
    /**< PM HAL Prcm Videopll Element VIDEO2 */
    PMHAL_PRCM_VIDEOPLL_HDMI = 179U,
    /**< PM HAL Prcm Videopll Element HDMI */
    PMHAL_PRCM_VIDEOPLL_MAX = PMHAL_PRCM_VIDEOPLL_HDMI,
    /** Enum Upper bound */
    PMHAL_PRCM_VIDEOPLL_COUNT = PMHAL_PRCM_VIDEOPLL_MAX + 1U,
    /**< Enum Count */
    PMHAL_PRCM_NODE_MAX = PMHAL_PRCM_VIDEOPLL_MAX,
    /**< Upper bound for Node */
    PMHAL_PRCM_NODE_COUNT = PMHAL_PRCM_VIDEOPLL_COUNT,
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    PMHAL_PRCM_MOD_ATL,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4
    PMHAL_PRCM_MOD_DUMMY_MODULE4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1
    PMHAL_PRCM_MOD_DUMMY_MODULE1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2
    PMHAL_PRCM_MOD_DUMMY_MODULE2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3
    PMHAL_PRCM_MOD_DUMMY_MODULE3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE
    PMHAL_PRCM_MOD_IO_SRCOMP_CORE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    PMHAL_PRCM_MOD_SMARTREFLEX_CORE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
    PMHAL_PRCM_MOD_SMARTREFLEX_GPU,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
    PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
    PMHAL_PRCM_MOD_SMARTREFLEX_MPU,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
    PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
    PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
    PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
    PMHAL_PRCM_MOD_DMA_SYSTEM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    PMHAL_PRCM_MOD_DSP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    PMHAL_PRCM_MOD_DSP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
    PMHAL_PRCM_MOD_BB2D,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    PMHAL_PRCM_MOD_DSS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
    PMHAL_PRCM_MOD_SDVENC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    PMHAL_PRCM_MOD_DLL,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMM
    PMHAL_PRCM_MOD_DMM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    PMHAL_PRCM_MOD_EMIF1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
    PMHAL_PRCM_MOD_EMIF2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
    PMHAL_PRCM_MOD_EMIF_OCP_FW,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    PMHAL_PRCM_MOD_EVE1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE2
    PMHAL_PRCM_MOD_EVE2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE3
    PMHAL_PRCM_MOD_EVE3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE4
    PMHAL_PRCM_MOD_EVE4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_PRCM_MOD_CPGMAC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
    PMHAL_PRCM_MOD_GPU,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
    PMHAL_PRCM_MOD_I2C5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
    PMHAL_PRCM_MOD_UART6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    PMHAL_PRCM_MOD_IPU1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU2
    PMHAL_PRCM_MOD_IPU2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
    PMHAL_PRCM_MOD_IVA,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
    PMHAL_PRCM_MOD_SL2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    PMHAL_PRCM_MOD_IEEE1500_2_OCP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
    PMHAL_PRCM_MOD_MMC1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
    PMHAL_PRCM_MOD_MMC2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
    PMHAL_PRCM_MOD_MLB_SS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
    PMHAL_PRCM_MOD_SATA,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
    PMHAL_PRCM_MOD_OCP2SCP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
    PMHAL_PRCM_MOD_OCP2SCP3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    PMHAL_PRCM_MOD_USB_OTG_SS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
    PMHAL_PRCM_MOD_USB_OTG_SS2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
    PMHAL_PRCM_MOD_USB_OTG_SS3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
    PMHAL_PRCM_MOD_USB_OTG_SS4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
    PMHAL_PRCM_MOD_MMU_PCIESS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_PRCM_MOD_OCMC_RAM1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
    PMHAL_PRCM_MOD_OCMC_RAM2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
    PMHAL_PRCM_MOD_OCMC_RAM3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM
    PMHAL_PRCM_MOD_OCMC_ROM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2
    PMHAL_PRCM_MOD_SPARE_IVA2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP1
    PMHAL_PRCM_MOD_VCP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP2
    PMHAL_PRCM_MOD_VCP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME
    PMHAL_PRCM_MOD_SPARE_CME,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI
    PMHAL_PRCM_MOD_SPARE_HDMI,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM
    PMHAL_PRCM_MOD_SPARE_ICM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2
    PMHAL_PRCM_MOD_SPARE_SATA2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4
    PMHAL_PRCM_MOD_SPARE_UNKNOWN4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5
    PMHAL_PRCM_MOD_SPARE_UNKNOWN5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6
    PMHAL_PRCM_MOD_SPARE_UNKNOWN6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
    PMHAL_PRCM_MOD_SPARE_VIDEOPLL1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
    PMHAL_PRCM_MOD_SPARE_VIDEOPLL2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
    PMHAL_PRCM_MOD_SPARE_VIDEOPLL3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
    PMHAL_PRCM_MOD_OCP2SCP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
    PMHAL_PRCM_MOD_SAR_ROM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
    PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
    PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
    PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_PRCM_MOD_SPINLOCK,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
    PMHAL_PRCM_MOD_IO_DELAY_BLOCK,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_PRCM_MOD_MAILBOX1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
    PMHAL_PRCM_MOD_MAILBOX10,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
    PMHAL_PRCM_MOD_MAILBOX11,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
    PMHAL_PRCM_MOD_MAILBOX12,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
    PMHAL_PRCM_MOD_MAILBOX13,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_PRCM_MOD_MAILBOX2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
    PMHAL_PRCM_MOD_MAILBOX3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
    PMHAL_PRCM_MOD_MAILBOX4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
    PMHAL_PRCM_MOD_MAILBOX5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
    PMHAL_PRCM_MOD_MAILBOX6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
    PMHAL_PRCM_MOD_MAILBOX7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
    PMHAL_PRCM_MOD_MAILBOX8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
    PMHAL_PRCM_MOD_MAILBOX9,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_PRCM_MOD_I2C1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_PRCM_MOD_I2C2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
    PMHAL_PRCM_MOD_I2C3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
    PMHAL_PRCM_MOD_I2C4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    PMHAL_PRCM_MOD_L4_PER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
    PMHAL_PRCM_MOD_TIMER10,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
    PMHAL_PRCM_MOD_TIMER11,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    PMHAL_PRCM_MOD_TIMER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    PMHAL_PRCM_MOD_TIMER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    PMHAL_PRCM_MOD_TIMER4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
    PMHAL_PRCM_MOD_TIMER9,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_PRCM_MOD_ELM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
    PMHAL_PRCM_MOD_HDQ1W,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
    PMHAL_PRCM_MOD_UART4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
    PMHAL_PRCM_MOD_UART5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    PMHAL_PRCM_MOD_GPIO2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    PMHAL_PRCM_MOD_GPIO3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    PMHAL_PRCM_MOD_GPIO4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
    PMHAL_PRCM_MOD_GPIO5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
    PMHAL_PRCM_MOD_GPIO6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
    PMHAL_PRCM_MOD_GPIO7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
    PMHAL_PRCM_MOD_GPIO8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
    PMHAL_PRCM_MOD_MMC3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_PRCM_MOD_MMC4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    PMHAL_PRCM_MOD_DCAN2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    PMHAL_PRCM_MOD_L4_PER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
    PMHAL_PRCM_MOD_UART7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
    PMHAL_PRCM_MOD_UART8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
    PMHAL_PRCM_MOD_UART9,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    PMHAL_PRCM_MOD_PRUSS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    PMHAL_PRCM_MOD_PRUSS2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    PMHAL_PRCM_MOD_MCASP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    PMHAL_PRCM_MOD_MCASP3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
    PMHAL_PRCM_MOD_MCASP4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
    PMHAL_PRCM_MOD_MCASP5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
    PMHAL_PRCM_MOD_MCASP6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
    PMHAL_PRCM_MOD_MCASP7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
    PMHAL_PRCM_MOD_MCASP8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_PRCM_MOD_PWMSS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
    PMHAL_PRCM_MOD_PWMSS2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
    PMHAL_PRCM_MOD_PWMSS3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_PRCM_MOD_QSPI,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    PMHAL_PRCM_MOD_L4_PER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
    PMHAL_PRCM_MOD_TIMER13,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
    PMHAL_PRCM_MOD_TIMER14,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
    PMHAL_PRCM_MOD_TIMER15,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
    PMHAL_PRCM_MOD_TIMER16,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES1
    PMHAL_PRCM_MOD_AES1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES2
    PMHAL_PRCM_MOD_AES2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
    PMHAL_PRCM_MOD_DES3DES,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
    PMHAL_PRCM_MOD_DMA_CRYPTO,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
    PMHAL_PRCM_MOD_FPKA,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
    PMHAL_PRCM_MOD_RNG,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51
    PMHAL_PRCM_MOD_SHA2MD51,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52
    PMHAL_PRCM_MOD_SHA2MD52,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
    PMHAL_PRCM_MOD_MPU,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
    PMHAL_PRCM_MOD_MPU_MPU_DBG,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    PMHAL_PRCM_MOD_PCIESS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    PMHAL_PRCM_MOD_PCIESS2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
    PMHAL_PRCM_MOD_RTCSS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    PMHAL_PRCM_MOD_VIP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP2
    PMHAL_PRCM_MOD_VIP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP3
    PMHAL_PRCM_MOD_VIP3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
    PMHAL_PRCM_MOD_VPE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    PMHAL_PRCM_MOD_DEBUG_LOGIC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
    PMHAL_PRCM_MOD_MPU_EMU_DBG,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    PMHAL_PRCM_MOD_ADC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
    PMHAL_PRCM_MOD_IO_SRCOMP_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
    PMHAL_PRCM_MOD_KBD,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    PMHAL_PRCM_MOD_L4_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM
    PMHAL_PRCM_MOD_SAR_RAM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1
    PMHAL_PRCM_MOD_SPARE_SAFETY1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2
    PMHAL_PRCM_MOD_SPARE_SAFETY2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3
    PMHAL_PRCM_MOD_SPARE_SAFETY3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4
    PMHAL_PRCM_MOD_SPARE_SAFETY4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2
    PMHAL_PRCM_MOD_SPARE_UNKNOWN2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3
    PMHAL_PRCM_MOD_SPARE_UNKNOWN3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    PMHAL_PRCM_MOD_TIMER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
    PMHAL_PRCM_MOD_TIMER12,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
    PMHAL_PRCM_MOD_UART10,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
    PMHAL_PRCM_MOD_WD_TIMER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
    PMHAL_PRCM_MOD_WD_TIMER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */
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

/**
 *  \brief Enum for the MUX's parent id Used in Display Subsystem
 *  Caution: Do not change the enum values.
 */
typedef enum pmhalVideopllMuxSelectId
{
    PMHAL_PRCM_VIDEOPLL_MUX_MIN = 0U,
    /**< PMHAL PRCM VIDEOPLL MUX for MIN */
    PMHAL_PRCM_VIDEOPLL_MUX_HDMI = PMHAL_PRCM_VIDEOPLL_MUX_MIN,
    /**< PMHAL PRCM VIDEOPLL MUX for HDMI */
    PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1 = 1U,
    /**< PMHAL PRCM VIDEOPLL MUX for VIDEO1*/
    PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2 = 2U,
    /**< PMHAL PRCM VIDEOPLL MUX for VIDEO2*/
    PMHAL_PRCM_VIDEOPLL_MUX_ABE = 3U,
    /**< PMHAL PRCM VIDEOPLL MUX for ABE*/
    PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1_HSDIVIDER_CLKOUT3 = 4U,
    /**< PMHAL PRCM VIDEOPLL MUX for VIDEO1_HSDIVIDER_CLKOUT3*/
    PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM = 5U,
    /**< PMHAL PRCM VIDEOPLL MUX for DPLL_PRCM*/
    PMHAL_PRCM_VIDEOPLL_MUX_DPLL_HDMI_CLK1 = 6U,
    /**< PMHAL PRCM VIDEOPLL MUX for DPLL_HDMI_CLK1*/
    PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1 = 7U,
    /**< PMHAL PRCM VIDEOPLL MUX for DPLL_DSI1_A_CLK1*/
    PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1 = 8U,
    /**< PMHAL PRCM VIDEOPLL MUX for DPLL_DSI1_B_CLK1*/
    PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1 = 9U,
    /**< PMHAL PRCM VIDEOPLL MUX for DPLL_DSI1_C_CLK1*/
    PMHAL_PRCM_VIDEOPLL_MUX_MAX = PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1 + 1U,
    /**< PMHAL PRCM VIDEOPLL MUX for MAX*/
    PMHAL_PRCM_VIDEOPLL_MUX_INVALID = 0x7FFFFFFF
                                      /**< PMHAL PRCM VIDEOPLL MUX for invalid
                                      **/
}pmhalPrcmVideopllMuxSelectId_t;

/**
 *  \brief Enum for the MUX's Used in Display Subsystem
 *  Caution: Do not change the enum values.
 */
typedef enum
{
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MIN = 0U,
    /**< Min Mux Value */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MIN,
    /**< MUX to select clksrc for dpll_dsi1_a_clk1 signal. */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B = 1U,
    /**< MUX to select clksrc for dpll_dsi1_b_clk1 signal.  */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C = 2U,
    /**< MUX to select clksrc for dpll_dsi1_c_clk1 signal. */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH = 3U,
    /**< MUX to select clksrc for LCD1_CLK signal. */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH = 4U,
    /**< MUX to select clksrc for LCD2_CLK signal. */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH = 5U,
    /**< MUX to select clksrc for LCD3_CLK signal. */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH = 6U,
    /**< MUX to select clksrc for F_CLK signal. */
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX =
        PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH + 1U
        /**< This should be last Enum. */
} pmhalPrcmVideopllDssClkSrcMuxId_t;

/**
 * \brief Enumeration of all the Modules that are associated with OPP.
 *        These are the processing units and Interconnect
 */
typedef enum pmhalPrcmCpuId
{
    PMHAL_PRCM_CPU_ID_MIN = 0,
    /**< Minimum CPU Index */
    PMHAL_PRCM_CPU_ID_MPU = PMHAL_PRCM_CPU_ID_MIN,
    /**< CPU Index for MPU */
    PMHAL_PRCM_CPU_ID_IPU = 1,
    /**< CPU Index for IPU */
    PMHAL_PRCM_CPU_ID_IVAHD = 2,
    /**< CPU Index for IVA */
    PMHAL_PRCM_CPU_ID_DSP = 3,
    /**< CPU Index for DSP */
    PMHAL_PRCM_CPU_ID_EVE = 4,
    /**< CPU Index for EVE */
    PMHAL_PRCM_CPU_ID_GPU = 5,
    /**< CPU Index for GPU */
    PMHAL_PRCM_CPU_ID_MAX = PMHAL_PRCM_CPU_ID_GPU,
    /**< Maximum CPU Index */
    PMHAL_PRCM_CPU_ID_COUNT = PMHAL_PRCM_CPU_ID_MAX + 1,
    /**< CPU Index Count */
    PMHAL_PRCM_CPU_ID_UNDEF = (-(int32_t)1)
                              /**< Undefined CPU Index */
} pmhalPrcmCpuId_t;

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


