/**
 *   @file  csl_armGic.h
 *
 *   @brief
 *      This is the main header file for the A15 GIC Module which defines
 *      all the data structures and exported API.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2002-2017, Texas Instruments, Inc.
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

/** @defgroup CSL_ARM_GIC_V0_API ARMGIC_V0
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 * The timer can be configured as a general-purpose 64-bit timer, dual general-purpose 32-bit
 * timers, or a watchdog timer. When configured as a dual 32-bit timers, each half can operate in
 * conjunction (chain mode) or independently (unchained mode) of each other. The timer can be
 * configured in one of three modes using the timer mode (TIMMODE) bits in the timer global control
 * register (TGCR): a 64-bit general-purpose (GP) timer, dual 32-bit timers (Timer Low and Timer
 * High), or a watchdog timer. When configured as dual 32-bit timers, each half can operate
 * dependently (chain mode) or independently (unchained mode) of each other. At reset, the timer is
 * configured as a 64-bit GP timer. The watchdog timer function can be enabled if desired, via the
 * TIMMODE bits in timer global control register (TGCR) and WDEN bit in the watchdog timer
 * control register WDTCR). Once the timer is configured as a watchdog timer, it cannot be reconfigured
 * as a regular timer until a device reset occurs. The timer has one input pin (TINPL) and
 * one output pin (TOUTL). The timer control register (TCR) controls the function of the input and
 * output pin.
 * The timers can be used to: time events, count events, generate pulses, interrupt the CPU, and
 * send synchronization events to the EDMA.
 *
 *  @subsection References
 *    -# Timer User's Guide SPRU818.pdf (December 2005)
 */

#ifndef CSL_ARM_GIC_V0_H
#define CSL_ARM_GIC_V0_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/csl/soc.h>
#include <ti/csl/csl.h>
#include <ti/csl/src/ip/arm_gic/V0/cslr_arm_gic.h>

/*  Maximum number of interrupts supported by GIC */
#define CSL_ARM_GIC_MAX_INTR_NO         ((uint32_t)1024U)

/*  Maximum number of CPU supported by GIC */
#define CSL_ARM_GIC_MAX_CPU_NO          ((uint32_t)8U)

/* Interrupt type - secure mode only */
#define CSL_ARM_GIC_SECURE_INT          ((uint32_t)1U)
#define CSL_ARM_GIC_NON_SECURE_INT      ((uint32_t)2U)
#define CSL_ARM_GIC_SEC_NS_INT          ((uint32_t)3U)

/* Macro to get mask for set-enable and clear-enable register bits */
#define CSL_ARM_GICD_SET_CLR_MASK(intrNum)      (((uint32_t)0x1U) << ((intrNum) % 32U))

#define CSL_ARM_GICD_INT_CONF_MASK(intrNum)     (((uint32_t)0x11U) << ((intrNum) % 16U))
#define CSL_ARM_GICD_INT_CONF_SHIFT(intrNum)    ((intrNum) % 16U)

#define CSL_ARM_GIC_CPU_INTF_MIN_PRI_ALL ((CSL_ARM_GIC_CPU_INTF_MIN_PRI) |       \
                                          ((CSL_ARM_GIC_CPU_INTF_MIN_PRI) << 8) |  \
                                          ((CSL_ARM_GIC_CPU_INTF_MIN_PRI) << 16) | \
                                          ((CSL_ARM_GIC_CPU_INTF_MIN_PRI) << 24))

#define CSL_ARM_GICD_DISABLE_INTR               ((uint32_t)0xFFFFFFFFU)

/*
    Configure the priority mask to lowest value, so that all the priorities
    can be used. Based on the application need this can be modified
    apprioriately.
*/
#define CSL_ARM_GIC_CPU_INTF_MIN_PRI                ((uint32_t)0xffU)

/*  PPI trigger type configurable */
#define CSL_ARM_GIC_PPI_TRIG_WRITABLE               ((uint32_t)0)

/* Follow as configured in target list filter */
#define CSL_ARM_GIC_SGI_TARGET_LIST                 ((uint32_t)0U)

/** Send interrupt only if the target interrupt (security) configuration
    matches with this configuration. */
#define CSL_ARM_GIC_SGI_SATT_SECURE                 ((uint32_t)0U)
#define CSL_ARM_GIC_SGI_SATT_NON_SECURE             ((uint32_t)1U)

/**
@defgroup CSL_ARM_GIC_V0_SYMBOL  ARMGIC_V0 Symbols Defined
@ingroup CSL_ARM_GIC_V0_API
*/
/**
@defgroup CSL_ARM_GIC_V0_DATASTRUCT  ARMGIC_V0 Data Structures
@ingroup CSL_ARM_GIC_V0_API
*/
/**
@defgroup CSL_ARM_GIC_V0_FUNCTION  ARMGIC_V0 Functions
@ingroup CSL_ARM_GIC_V0_API
*/
/**
@defgroup CSL_ARM_GIC_V0_ENUM ARMGIC_V0 Enumerated Data Types
@ingroup CSL_ARM_GIC_V0_API
*/

/**
@addtogroup CSL_ARM_GIC_V0_ENUM
@{
*/

/**
 * General purpose global type def declarations
 */

/**
 *  @brief Enumerates the types different trigger types.
 */
typedef enum
{
    /**< High Level */
    CSL_ARM_GIC_TRIG_TYPE_HIGH_LEVEL,

    /**< Low Level */
    CSL_ARM_GIC_TRIG_TYPE_LOW_LEVEL,

    /**< Rising edge */
    CSL_ARM_GIC_TRIG_TYPE_RISING_EDGE,

    /**< Falling edge */
    CSL_ARM_GIC_TRIG_TYPE_FALLING_EDGE,

    /**< Both edge */
    CSL_ARM_GIC_TRIG_TYPE_BOTH_EDGE
} CSL_armGicTrigType_t;

/**
 *  @brief Binary point value for priority grouping.
 */
typedef enum
{
    /**
     * @brief   Loads the GP Timer Period Register Low
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL0 = 0U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL1 = 1U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL2 = 2U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL3 = 3U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL4 = 4U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL5 = 5U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL6 = 6U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_BPVAL7 = 7U
} CSL_ArmGicBinPointVal_t;



/** Interrupt support cases. */
typedef enum
{
    CSL_ARM_GIC_INTR_NOT_SUPP            = 0U,
    CSL_ARM_GIC_INTR_SUPP                = 1U,
    CSL_ARM_GIC_INTR_SUPP_ENABLED_ALWAYS = 2U
} CSL_ArmGicIntrSupport_t;

/**
 *  @brief Binary point value for priority grouping.
 */
typedef enum
{
    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_PRIOR_LEVEL_256 = 0x0U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_PRIOR_LEVEL_128 = 0x1U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_PRIOR_LEVEL_64 = 0x2U,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_ARM_GIC_PRIOR_LEVEL_32 = 0x3U,

    /**
     * @brief   Loads the GP Timer Period Register Low
     * @param   Uint32 *
     */
    CSL_ARM_GIC_PRIOR_LEVEL_16 = 0x4U,
} CSL_ArmGicPriorLevel_t;

/**
@}
*/

/** @addtogroup CSL_ARM_GIC_V0_DATASTRUCT
 @{ */

/**
 *  @brief Structure defining parameters to configure an interrupt.
 */
typedef struct
{
    /**< Trigger type */
    CSL_armGicTrigType_t triggerType;

    /** Priority of the interrupt. In some processors not all values of
         priorities are supported.
    */
    Uint32   priority;

    /**< Interrupt handler */
    void (*pFnIntrHandler)(void* pUserParam);

    /**< Parameter to be passed to the handler function */
    void *pUserParam;

    /**< Which CPU to interrupt- in a multi proc system */
    Uint32 targetCpu;
} CSL_ArmGicIntrParams_t;

/**
 * @brief GIC Distributor interface Structure.
 */
typedef struct
{
    /** Pointer to distributor sub-module base address. */
    void *distBasePtr;

    /** GIC distributor initialization status. */
    Uint32 initStatus;

    /** Maximum number of interrupts supported. */
    Uint32 maxValidIntr;

    /** Number of CPU interfaces implemented in GIC. */
    Uint32 noCpuIntf;

    /** Number of priority levels implemented. */
    Uint32 noPriorityStep;

    /** NS binary point for NS priority group configuration. */
    CSL_ArmGicBinPointVal_t nonSecureBinaryPoint;

    /** Number of CPU interfaces implemented in GIC. */
    Uint32 intrSupportMask[CSL_ARM_GIC_MAX_INTR_NO / 32U];
} CSL_ArmGicDistIntrf;

/**
 * @brief GIC CPU interface Structure.
 */
typedef struct
{
    /** Pointer to CPU Interface sub-module base address. */
    void *cpuIntfBasePtr;

    /** CPU interfaces ID in GIC. */
    Uint32 cpuId;

    /** GIC CPU interface initialization status. */
    Uint32 initStatus;

    /** User configurable parameters. */
    CSL_ArmGicDistIntrf *gicDist;

    /**
     * Array of function pointers to hold call back functions for Interrupt
     * handlers. This list will be used for calling the call back functions
     * of interrupts.
     */
    void (*pDefaultIntrHandlers)(void* pUserParam);

    /**
     * Array to hold the user parameters passed during interrupt
     * registration. The same will be passed to the corresponding interrupt
     * handlers.
     */
    void *pDefaultUserParameter;

#if !defined (SOC_AM574x) && !defined (SOC_AM572x) && !defined (SOC_TDA2XX) && !defined (SOC_TDA2PX) && !defined (SOC_DRA75x) && !defined (SOC_AM571x) && !defined (SOC_TDA2EX) && !defined (SOC_DRA72x)
    /**
     * Array of function pointers to hold call back functions for Interrupt
     * handlers. This list will be used for calling the call back functions
     * of interrupts.
     */
    void (*pIntrHandlers[CSL_ARM_GIC_MAX_INTR_NO])(void* pUserParam);

    /**
     * Array to hold the user parameters passed during interrupt
     * registration. The same will be passed to the corresponding interrupt
     * handlers.
     */
    void *pUserParameter[CSL_ARM_GIC_MAX_INTR_NO];
#endif
    /**
    * Interrupt ack register to read from Alias area or
    * non alias register for getting Interrupt ID from IAR register
    */
    uintptr_t         iarRegAddress;

    /**
    * End of Interrupt Register address to read from Alias or
    * non alias EOI register
    */
    uintptr_t         eoiRegAddress;

} CSL_ArmGicCpuIntrf;

/**
@}
*/

/**
@addtogroup CSL_ARM_GIC_V0_SYMBOL
@{
*/

/** @brief Default hardware setup parameters */

/**
@}
*/

/** @addtogroup CSL_ARM_GIC_V0_FUNCTION
 @{ */

/*******************************************************************************
 * Timer global function declarations
 ******************************************************************************/

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif  /* CSL_ARM_GIC_V0_H */
