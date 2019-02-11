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
 *  \file  pm_types.h
 *
 *  \brief This file contains all the error types that are used for PM Layer.
 *
 */

#ifndef PM_TYPES_H_
#define PM_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Define True Value as 1U */
#ifndef TRUE
#define TRUE  ((uint32_t) 1U)
#endif
/** \brief Define False Value as 0U */
#ifndef FALSE
#define FALSE ((uint32_t) 0U)
#endif

/** \brief Macro defining the flag for infinite timeout */
#define PM_TIMEOUT_INFINITE         (0xFFFFFFFFU)

/** \brief Macro defining the flag for no time out */
#define PM_TIMEOUT_NOWAIT           ((uint32_t) 0x0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Generic Error Codes.
 */
typedef enum
{
    PM_SUCCESS = 0,
    /**< Error Code for SUCCESS. */
    PM_FAIL = -((int32_t)1),
    /**< Error Code for FAIL. */
    PM_BADARGS = -((int32_t)2),
    /**< Error Code for BADARGS. */
    PM_TIMEOUT = -((int32_t)3),
    /**< Error Code for TIMEOUT */
    PM_INPUT_PARAM_BAD_MODULE_ID = -((int32_t)4),
    /**< Error Code for INPUT PARAM BAD MODULE ID */
    PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE = -((int32_t)5),
    /**< Error Code for PM_MM Module does not support a sysconfig register */
    PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE = -((int32_t)6),
    /**< Error Code for PM_MM Module does not support clock control register */
    PM_MM_MODULE_SYSCONFIG_CLKACTIVITY_NOT_PRESENT = -((int32_t)7),
    /**< Error Code for PM_MM Module does not support sysconfig clock activity
    **/
    PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED = -((int32_t)8),
    /**< Error Code for PM_MM Module does not support any standby mode */
    PM_INPUT_PARAM_BAD_MODULE_MODE = -((int32_t)9),
    /**< Error Code for INPUT PARAM BAD MODULE MODE */
    PM_INPUT_MODULE_STANDBY_MODE_INVALID = -((int32_t)10),
    /**< Error Code for INPUT Standby Mode Invalid */
    PM_INPUT_MODULE_IDLE_MODE_INVALID = -((int32_t)11),
    /**< Error Code for INPUT Idle Mode Invalid */
    PM_INPUT_PARAM_BAD_RESET_ID = -((int32_t)12),
    /**< Error Code for INPUT PARAM BAD RESET ID */
    PM_INPUT_PARAM_NONCONFIGURABLE_RESET_DOMAIN_ID = -((int32_t)13),
    /**< Error Code for INPUT PARAM NONCONFIGURABLE RESET DOMAIN ID */
    PM_RM_BAD_RESET_OCCURANCE_TYPE = -((int32_t)14),
    /**< Error Code for PM_RM Bad Reset Occurrence given */
    PM_INPUT_PARAM_BAD_DPLL_ID = -((int32_t)15),
    /**< Error Code for INPUT PARAM BAD DPLL ID */
    PM_CM_DPLL_CLK_SEL_REGISTER_INVALID = -((int32_t)16),
    /**< Error Code for PM_CM Dpll Clock Selection Register Invalid */
    PM_CM_DPLL_CLK_MODE_REGISTER_INVALID = -((int32_t)17),
    /**< Error Code for PM_CM Dpll Clock Mode Register Invalid */
    PM_CM_DPLL_IDLEST_REGISTER_INVALID = -((int32_t)18),
    /**< Error Code for PM_CM Dpll Idle State Register Invalid */
    PM_CM_DPLL_POWER_MODE_NOT_SUPPORTED = -((int32_t)19),
    /**< Error Code for PM_CM DPLL Power mode not supported */
    PM_CM_DPLL_MULTIPLIER_VALUE_OUT_OF_RANGE = -((int32_t)20),
    /**< Error Code for PM_CM DPLL Multiplier value out of range */
    PM_CM_DPLL_DIVIDER_VALUE_OUT_OF_RANGE = -((int32_t)21),
    /**< Error Code for PM_CM DPLL Divider value out of range */
    PM_CM_DPLL_AUTO_IDLE_REGISTER_INVALID = -((int32_t)22),
    /**< Error Code for PM_CM DPLL Auto IDLE register is Invalid */
    PM_CM_DPLL_AUTO_IDLE_PROGRAMMING_NOT_AVAILABLE = -((int32_t)23),
    /**< Error Code for PM_CM DPLL Auto IDLE register programming is not allowed
    **/
    PM_INPUT_PARAM_BAD_CLOCK_ID = -((int32_t)24),
    /**< Error Code for INPUT PARAM BAD CLOCK ID */
    PM_INPUT_PARAM_BAD_CLK_DOMAIN_ID = -((int32_t)25),
    /**< Error Code for INPUT PARAM BAD CLK DOMAIN ID */
    PM_CM_MODULE_CLKSEL_CONFIG_NOT_AVAILABLE = -((int32_t)26),
    /**< Error Code for PM_CM Module clock select configuration not available */
    PM_CM_CLOCK_DOMAIN_CLK_STATE_CTRL_REG_INVALID = -((int32_t)27),
    /**< Error Code for PM_CM Clock Domain Clock State Ctrl Register Invalid */
    PM_INPUT_PARAM_BAD_MUX_ID = -((int32_t)28),
    /**< Error Code for PM_CM Mux Id not valid */
    PM_INPUT_PARAM_BAD_DIV_ID = -((int32_t)29),
    /**< Error Code for PM_CM Divider ID not valid */
    PM_CM_MUX_CLK_SEL_REGISTER_INVALID = -((int32_t)30),
    /**< Error Code for PM_CM Mux Clock Select Register Invalid */
    PM_CM_CLK_DOMAIN_TRANS_MODE_NOT_SUPPORTED = -((int32_t)31),
    /**< Error Code for PM_CM Clock Domain transition mode not supported */
    PM_CM_MUX_PARENT_SELECTION_INVALID = -((int32_t)32),
    /**< Error Code for PM_CM Mux Parent Selection Not valid */
    PM_CM_POST_DIV_REGISTER_INVALID = -((int32_t)33),
    /**< Error Code for PM_CM Post Divider register Invalid */
    PM_INPUT_PARAM_BAD_POST_DIV_ID = -((int32_t)34),
    /**< Error Code for PM_CM Bad Post Divider ID */
    PM_CM_CLKSEL_CTRL_NOT_APPLICABLE = -((int32_t)35),
    /**< Error Code for PM_CM Clock Selection control not applicable */
    PM_CM_DIV_SEL_REGISTER_NOT_APPLICABLE = -((int32_t)36),
    /**< Error Code for PM_CM Clock Divider Select control not applicable */
    PM_INPUT_PARAM_BAD_VOLTAGE_ID = -((int32_t)37),
    /**< Error Code for INPUT PARAM BAD VOLTAGE ID */
    PM_PMIC_VENDOR_ID_INVALID = -((int32_t)38),
    /**< Error Code for PMIC VENDOR ID INVALID */
    PM_PMIC_PRODUCT_ID_INVALID = -((int32_t)39),
    /**< Error Code for PMIC PRODUCT ID INVALID */
    PM_REGULATOR_STATE_INVALID = -((int32_t)40),
    /**< Error Code for REGULATOR STATE INVALID */
    PM_PMIC_COMM_TIMEOUT_ERROR = -((int32_t)41),
    /**< Error Code for PMIC_COMM TIMEOUT ERROR */
    PM_PMIC_COMM_NO_ACK_ERROR = -((int32_t)42),
    /**< Error Code for PMIC_COMM NO ACK ERROR */
    PM_PMIC_COMM_ARB_LOST_ERROR = -((int32_t)43),
    /**< Error Code for PMIC_COMM ARB LOST ERROR */
    PM_PMIC_COMM_ARDY_ERROR = -((int32_t)44),
    /**< Error Code for PMIC_COMM ARDY ERROR */
    PM_VOLTAGE_INVALID = -((int32_t)45),
    /**< Error Code for VOLTAGE INVALID */
    PM_OPP_INVALID = -((int32_t)46),
    /**< Error Code for OPP INVALID */
    PM_INPUT_PARAM_BAD_POWER_DOMAIN_ID = -((int32_t)47),
    /**< Error Code for INPUT PARAM BAD POWER DOMAIN ID */
    PM_PDM_PDSTATE_NOT_SUPPORTED = -((int32_t)48),
    /**< Error Code for PM_PDM Power State not supported */
    PM_PDM_LOGIC_RET_STATE_NOT_SUPPORTED = -((int32_t)49),
    /**< Error Code for PM_PDM Power State not supported */
    PM_PDM_LOW_POWER_REQUEST_NOT_SUPPORTED = -((int32_t)50),
    /**< Error Code for PM_PDM Low Power request not supported */
    PM_PDM_MEM_RET_STATE_NOT_SUPPORTED = -((int32_t)51),
    /**< Error Code for PM_PDM Memory retention state not supported */
    PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID = -((int32_t)52),
    /**< Error Code for PM_PDM Power state Ctrl Register not valid */
    PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID = -((int32_t)53),
    /**< Error Code for PM_PDM Power state status Register not valid */
    PM_INPUT_PARAM_BAD_PHYSICAL_MEMORY_ID = -((int32_t)54),
    /**< Error Code for INPUT PARAM BAD PHYSICAL MEMORY ID */
    PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED = -((int32_t)55),
    /**< Error Code for PMLIB System Config Module Cannot be enabled */
    PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED = -((int32_t)56),
    /**< Error Code for PMLIB System Config Module Cannot be disabled */
    PM_SYS_CONFIG_MODULE_NOT_GETTING_DISABLED = -((int32_t)57),
    /**< Error Code for PMLIB System Config Module not getting disabled */
    PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES = -((int32_t)58),
    /**< Error Code for PMLIB System Config Module has dependencies */
    PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG = -((int32_t)59),
    /**< Error Code for PMLIB System Config Module Cannot be auto clock gated */
    PM_SD_CLOCK_DOMAIN_DEPENDENCY_HARDWIRED = -((int32_t)60),
    /**< Error Code for Static dependency Clock domain dependency hard wired */
    PM_INPUT_PARAM_BAD_CPU_ID = -((int32_t)61),
    /**< Error Code for INPUT PARAM BAD PM IRQ ID */
    PM_INPUT_PARAM_BAD_CLOCKTREE_NODE_ID = -((int32_t)62),
    /**< Error Code for INPUT PARAM CLOCKTREE NODE ID */
    PM_INPUT_PARAM_BAD_CLOCKTREE_EDGE_PROPERTY_ID = -((int32_t)63),
    /**< Error Code for INPUT PARAM CLOCKTREE EDGE PROPERTY ID */
    PM_CLOCTREE_EDGE_NOT_AVAILABLE = -((int32_t)64),
    /**< Error Code for PM_CLOCTREE Edge is not available */
    PM_CLOCKRATE_ROOTCLK_NOT_SUPPORTED = -((int32_t)65),
    /**< Error Code for PM_CLOCKRATE root clock is not supported */
    PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ = -((int32_t)66),
    /**< Error Code for PM_CLOCKRATE same frequency change requested */
    PM_CLOCKRATE_FREQ_NOT_SUPPORTED = -((int32_t)67),
    /**< Error Code for PM_CLOCKRATE frequency not supported */
    PM_VIDEOPLL_HSDIV_NOT_VALID = -((int32_t)68),
    /**< Error Code for PM Video PLL HSDIV is not valid */
    PM_VIDEOPLL_HSDIV_NOT_ENABLED = -((int32_t)69),
    /**< Error Code for PM Video PLL HSDIV is not enabled */
    PM_VIDEOPLL_HSDIV_NOT_SUPPORTED = -((int32_t)70),
    /**< Error Code for PM Video PLL HSDIV is not supported */
    PM_VIDEOPLL_CALC_PARAMS_FAILED = -((int32_t)71),
    /**< Error Code for PM Video calc params failed */
    PM_MIN_ERR_CODE = PM_VIDEOPLL_CALC_PARAMS_FAILED,
    /**< Minimum Number of Return Codes */
    PM_COUNT_ERR_CODE = -(PM_MIN_ERR_CODE) + 1
                        /**< Number of Return Codes */
} pmErrCode_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

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

#endif

/**
 * \mainpage  PM Drivers
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * Power Management (PM) requires setting the right power
 * and clock configurations which allow any IP to consume optimal power.
 * This helps not only reduce the total power consumed by the device
 * but also manage thermal dissipation of the silicon.
 *
 * <b>
 * Also refer to top level user guide for detailed features,
 * limitations and usage description.
 * </b>
 *
 * The PM driver API can be broadly divided into the following layers
 *
 * - <b> PM Hardware Abstraction Layer (PMHAL) </b> (See \ref PM_HAL) <br>
 *  PMHAL provides low level APIs which allow:
 *      - Programming PRCM registers
 *          - Power Domain Manager (PDM)
 *          - Clock Domain Manager (CM)
 *          - Reset Manager (RM)
 *          - Module Manager (MM)
 *      - Programming Temperature Sensor Registers (Temp)
 *      - Programming Voltage Domain AVS and ABB (VM)
 *      - Programming board specific PMIC
 *
 * - <b> PM Library (PMLIB) </b> (See \ref PM_LIB) <br>
 *  PMLIB provides application interface to
 *     - Configure system level clock frequencies
 *     - Configure the system power states
 *     - Perform dynamic CPU power optimization
 *
 * - <b> PM RTOS API Interface (PMRTOS) </b> (See \ref PM_RTOS) <br>
 *  PMRTOS provides application interface to power management
 *     - The Power manager facilitates the transition of the CPU from
 *       active state to one of the sleep states and vice versa.
 *     - It provides drivers the ability to set and release dependencies
 *       on hardware resources and keeps a reference count on each resource
 *       to know when to enable or disable the peripheral clock to the
 *       resource.
 *     - It provides drivers the ability to register a callback function
 *       upon a specific power event.
 *     - Drivers and apps can set or release constraints to prevent the CPU
 *       from transitioning into a particular sleep state. 
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */


