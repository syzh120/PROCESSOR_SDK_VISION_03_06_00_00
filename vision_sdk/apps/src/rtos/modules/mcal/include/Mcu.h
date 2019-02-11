/* ======================================================================
 *   Copyright (C) 2015-2017 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Mcu.h
 *
 *  \brief    This file contains interface header for Mcu Driver
 *
 */

/**
 *  \defgroup MCAL_MCU_API MCU Driver API
 *
 *  The MCU driver provides services for basic microcontroller initialization,
 *  power down functionality, reset  and microcontroller specific functions
 *  required by other MCAL software modules.
 *
 *  @sa MCAL_MCU_CFG
 *  @{
 */

/*
 * Below are the global requirements which are met by this MCU
 * driver which can't be mapped to a particular source ID
 */
/*
 * Requirements : SWS_Mcu_00017, SWS_Mcu_00226
 *                MCAL-200, MCAL-207, MCAL-213,
 *                MCAL-237, MCAL-250, MCAL-225
 */

/*
 * Below are the MCU module environment requirements which can't be mapped
 * to this driver
 */
/*
 * Requirements : SWS_Mcu_00116, SWS_Mcu_00051,
 *                SWS_Mcu_00244, SWS_Mcu_00246, SWS_Mcu_00247
 */
/* Design : MCU_DesignId_001 */
#ifndef MCU_H_
#define MCU_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
/* Requirements: SWS_Mcu_00211 ,SWS_Mcu_00215 */
/* Design : MCU_DesignId_002,MCU_DesignId_004 */
#include "Mcu_Cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name MCU Driver Module SW Version Info
 *
 *  Defines for MCU Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define MCU_SW_MAJOR_VERSION            (1U)
/** \brief Driver Implementation Minor Version */
#define MCU_SW_MINOR_VERSION            (9U)
/** \brief Driver Implementation Patch Version */
#define MCU_SW_PATCH_VERSION            (0U)
/* @} */

/**
 *  \name MCU Driver Module AUTOSAR Version Info
 *
 *  Defines for MCU Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by MCU Driver */
#define MCU_AR_RELEASE_MAJOR_VERSION    (4U)
/** \brief AUTOSAR Minor  version specification implemented by MCU Driver */
#define MCU_AR_RELEASE_MINOR_VERSION    (2U)
/** \brief AUTOSAR Patch version specification implemented by MCU Driver */
#define MCU_AR_RELEASE_REVISION_VERSION (1U)
/* @} */

/**
 *  \name MCU Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define MCU_VENDOR_ID                   ((uint16) 44U)
/** \brief MCU Driver Module ID */
#define MCU_MODULE_ID                   ((uint16) 101U)
/** \brief MCU Driver Instance ID */
#define MCU_INSTANCE_ID                 ((uint8) 0U)
/* @} */

/**
 *  \name MCU Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Mcu_Init() API Service ID */
#define MCU_SID_INIT                    ((uint8) 0x00U)
/** \brief Mcu_InitRamSection() API Service ID */
#define MCU_SID_INIT_RAMSECTION         ((uint8) 0x01U)
/** \brief Mcu_InitClock() API Service ID */
#define MCU_SID_INIT_CLOCK              ((uint8) 0x02U)
/** \brief Mcu_DistributePllClock() API Service ID */
#define MCU_SID_DISTRIBUTE_PLL_CLOCK    ((uint8) 0x03U)
/** \brief Mcu_GetPllStatus() API Service ID */
#define MCU_SID_GET_PLL_STATUS          ((uint8) 0x04U)
/** \brief Mcu_GetResetReason() API Service ID */
#define MCU_SID_GET_RESET_REASON        ((uint8) 0x05U)
/** \brief Mcu_GetResetRawValue() API Service ID */
#define MCU_SID_GET_RESET_RAW_VALUE     ((uint8) 0x06U)
/** \brief Mcu_PerformReset() API Service ID */
#define MCU_SID_PERFORM_RESET           ((uint8) 0x07U)
/** \brief Mcu_SetMode() API Service ID */
#define MCU_SID_SET_MODE                ((uint8) 0x08U)
/** \brief Mcu_GetVersionInfo() API Service ID */
#define MCU_SID_GET_VERSION_INFO        ((uint8) 0x09U)
/** \brief Mcu_GetRamState() API Service ID */
#define MCU_SID_GET_RAM_STATE           ((uint8) 0x0AU)
/* @} */

/* Requirements: SWS_Mcu_00012 */
/**
 *  \name MCU Error Codes
 *
 *  Error Codes returned by MCU Driver
 *  @{
 */
#ifndef MCU_E_PARAM_CONFIG
/** \brief ERROR:Mcu_init config param invalid */
#define MCU_E_PARAM_CONFIG              ((uint8) 0x0AU)
#endif
#ifndef MCU_E_PARAM_CLOCK
/** \brief ERROR:Mcu_InitClock clockid param invalid */
#define MCU_E_PARAM_CLOCK               ((uint8) 0x0BU)
#endif
#ifndef MCU_E_PARAM_MODE
/** \brief ERROR:Mcu_SetMode modeid param invalid */
#define MCU_E_PARAM_MODE                ((uint8) 0x0CU)
#endif
#ifndef MCU_E_PARAM_RAMSECTION
/** \brief ERROR:Mcu_InitRamSection ramSect param invalid */
#define MCU_E_PARAM_RAMSECTION          ((uint8) 0x0DU)
#endif
#ifndef MCU_E_PLL_NOT_LOCKED
/** \brief ERROR:PLL not locked */
#define MCU_E_PLL_NOT_LOCKED            ((uint8) 0x0EU)
#endif
#ifndef MCU_E_UNINIT
/** \brief ERROR:API invoked without performing Mcu_Init */
#define MCU_E_UNINIT                    ((uint8) 0x0FU)
#endif
#ifndef MCU_E_PARAM_POINTER
/** \brief ERROR:NULL_PTR passed to MCU driver APIs */
#define MCU_E_PARAM_POINTER             ((uint8) 0x10U)
#endif
#ifndef MCU_E_RUNTIME_ASSERT
/** \brief ERROR:Runtime assert failure */
#define MCU_E_RUNTIME_ASSERT            ((uint8) 0x11U)
#endif
/* @} */

/**
 *  \name MCU Config Ids
 *
 *  The Config Ids used for different
 *  MCU Configuration builds
 *  @{
 */
/** \brief Config 0 (All configurations ON) */
#define  MCU_CFG_ID_0     (0x01U)
/** \brief Config 1 (All configurations OFF).
 *         MCU_CFG_ID_1 is used only for compile check */
#define  MCU_CFG_ID_1     (0x02U)
/** \brief Config 2 (All configurations ON except DET OFF) */
#define  MCU_CFG_ID_2     (0x04U)
/** \brief Config 3 (Configurator auto generated file) */
#define  MCU_CFG_ID_3     (0x08U)
/* @} */

/**
 *  \name MCU Reset Modes
 *
 *  Reset mode enum which can be used in Mcu_PerformReset()
 *  @{
 */
/** \brief Initiate SW COLD RESET sequence */
#define MCU_PERFORM_RESET_MODE_COLD     ((uint8) 0U)
/** \brief Initiate SW WARM RESET sequence */
#define MCU_PERFORM_RESET_MODE_WARM     ((uint8) 1U)
/* @} */

/**
 *  \name MCU PRCM modules mode ID defines
 *
 *  PRCM modules ids defines are used tp enable specific modules
 *  @{
 */
#define MCU_PRCM_MODULE_ID_FIRST        (0U)
#define MCU_PRCM_MODULE_ID_CPGMAC       (0U)  /*!< ModuleId for EMAC */
#define MCU_PRCM_MODULE_ID_MCSPI1       (1U)  /*!< ModuleId for MCSPI1 */
#define MCU_PRCM_MODULE_ID_MCSPI2       (2U)  /*!< ModuleId for MCSPI2 */
#define MCU_PRCM_MODULE_ID_MCSPI3       (3U)  /*!< ModuleId for MCSPI3 */
#define MCU_PRCM_MODULE_ID_MCSPI4       (4U)  /*!< ModuleId for MCSPI4 */
#define MCU_PRCM_MODULE_ID_GPIO2        (5U)  /*!< ModuleId for GPIO2 */
#define MCU_PRCM_MODULE_ID_GPIO3        (6U)  /*!< ModuleId for GPIO3 */
#define MCU_PRCM_MODULE_ID_GPIO4        (7U)  /*!< ModuleId for GPIO4 */
#define MCU_PRCM_MODULE_ID_DCAN2        (8U)  /*!< ModuleId for DCAN2 */
#define MCU_PRCM_MODULE_ID_QSPI         (9U)  /*!< ModuleId for QSPI */
#define MCU_PRCM_MODULE_ID_DCAN1        (10U) /*!< ModuleId for DCAN1 */
#define MCU_PRCM_MODULE_ID_GPIO1        (11U) /*!< ModuleId for GPIO1 */
#define MCU_PRCM_MODULE_ID_WDTIMER2     (12U) /*!< ModuleId for WDTIMER2 */
#define MCU_PRCM_MODULE_ID_UART1        (13U) /*!< ModuleId for UART1 */
#define MCU_PRCM_MODULE_ID_GPTIMER1     (14U) /*!< ModuleId for GPTIMER1 */
#define MCU_PRCM_MODULE_ID_GPTIMER2     (15U) /*!< ModuleId for GPTIMER2  */
#define MCU_PRCM_MODULE_ID_GPTIMER3     (16U) /*!< ModuleId for GPTIMER3  */
#define MCU_PRCM_MODULE_ID_GPTIMER4     (17U) /*!< ModuleId for GPTIMER4  */
#define MCU_PRCM_MODULE_ID_GPTIMER5     (18U) /*!< ModuleId for GPTIMER5  */
#define MCU_PRCM_MODULE_ID_GPTIMER6     (19U) /*!< ModuleId for GPTIMER6  */
#define MCU_PRCM_MODULE_ID_GPTIMER7     (20U) /*!< ModuleId for GPTIMER7  */
#define MCU_PRCM_MODULE_ID_GPTIMER8     (21U) /*!< ModuleId for GPTIMER8  */
#define MCU_PRCM_MODULE_ID_PWM1         (22U) /*!< ModuleId for ePWM1  */

#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
#define MCU_PRCM_MODULE_ID_GPTIMER9     (23U) /*!< ModuleId for GPTIMER9  */
#define MCU_PRCM_MODULE_ID_GPTIMER10    (24U) /*!< ModuleId for GPTIMER10 */
#define MCU_PRCM_MODULE_ID_GPTIMER11    (25U) /*!< ModuleId for GPTIMER11 */
#define MCU_PRCM_MODULE_ID_GPTIMER13    (26U) /*!< ModuleId for GPTIMER13 */
#define MCU_PRCM_MODULE_ID_GPTIMER14    (27U) /*!< ModuleId for GPTIMER14 */
#define MCU_PRCM_MODULE_ID_GPTIMER15    (28U) /*!< ModuleId for GPTIMER15 */
#define MCU_PRCM_MODULE_ID_GPTIMER16    (29U) /*!< ModuleId for GPTIMER16 */
#define MCU_PRCM_MODULE_ID_GPIO5        (30U) /*!< ModuleId for GPIO5 */
#define MCU_PRCM_MODULE_ID_GPIO6        (31U) /*!< ModuleId for GPIO6 */
#define MCU_PRCM_MODULE_ID_GPIO7        (32U) /*!< ModuleId for GPIO7 */
#define MCU_PRCM_MODULE_ID_GPIO8        (33U) /*!< ModuleId for GPIO8 */
#define MCU_PRCM_MODULE_ID_UART3        (34U) /*!< ModuleId for UART3 */
#define MCU_PRCM_MODULE_ID_UART5        (35U) /*!< ModuleId for UART5 */
#define MCU_PRCM_MODULE_ID_PWM2         (36U) /*!< ModuleId for ePWM2  */
#define MCU_PRCM_MODULE_ID_PWM3         (37U) /*!< ModuleId for ePWM3  */
#if defined (TDA2PX_BUILD)
#define MCU_PRCM_MODULE_ID_MCAN1        (38U) /*!< ModuleId for MCAN (TDA2px) */
#endif /* (TDA2PX_BUILD) */
#endif /* (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD) */

#if defined (TDA3XX_BUILD)
#define MCU_PRCM_MODULE_ID_ADC          (23U) /*!< ModuleId for ADC (TDA3x) */
#define MCU_PRCM_MODULE_ID_MCAN1        (24U) /*!< ModuleId for MCAN (TDA3x) */
#endif

#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD)
#define MCU_PRCM_MODULE_ID_LAST         (MCU_PRCM_MODULE_ID_PWM3)
#elif defined (TDA2PX_BUILD) || defined (TDA3XX_BUILD)
#define MCU_PRCM_MODULE_ID_LAST         (MCU_PRCM_MODULE_ID_MCAN1)
#endif

#define MCU_PRCM_MODULE_ID_COUNT        (MCU_PRCM_MODULE_ID_LAST + 1U)
#define MCU_PRCM_MODULE_ID_UNDEF        (MCU_PRCM_MODULE_ID_COUNT + 1U)
/* @} */

/**
 *  \name PRCM modules mode  defines
 *
 *  PRCM modules mode  defines are used tp control module enable mode
 *  @{
 */
/** \brief Min value of the enum. Can be used for validation. */
#define MCU_PRCM_MODULE_MODE_MIN        ((uint8) 0x0U)
/** \brief Disabled: Any access to module registers will result in error */
#define MCU_PRCM_MODULE_MODE_DISABLED   (MCU_PRCM_MODULE_MODE_MIN)
/**
 *  \brief Auto: Clocks will be gated automatically when there is no activity
 *  and enabled when there is an activity.
 */
#define MCU_PRCM_MODULE_MODE_AUTO       ((uint8) 0x1U)
/**
 *  \brief Enabled: Functional and interface clocks are available and access to
 *  module registers are permitted.
 */
#define MCU_PRCM_MODULE_MODE_ENABLED    ((uint8) 0x2U)
/** \brief Max value of the enum. Can be used for validation. */
#define MCU_PRCM_MODULE_MODE_MAX        (MCU_PRCM_MODULE_MODE_ENABLED)
/* @} */

/** \brief Define indicating invalid raw reset value */
#define MCU_ERRORRST_MASK           ((Mcu_RawResetType) 0xFFFF0000U)

/* Requirements: SWS_Mcu_00251,SWS_Mcu_00232,SWS_Mcu_00233 */
/**
 *  \brief This type specifies the identification (ID) for a ClockType
 *  status used by Mcu_InitClock()
 */
typedef uint8 Mcu_ClockType;

/* Requirements: SWS_Mcu_00253,SWS_Mcu_00235,SWS_Mcu_00236 */
/**
 *  \brief This type specifies the identification (ID) for a RAW MCU reset
 *  status returned by Mcu_GetResetRawValue()
 */
typedef uint32 Mcu_RawResetType;

/* Requirements : SWS_Mcu_00255,SWS_Mcu_00239,SWS_Mcu_00240 */
/**
 *  \brief This type specifies the identification (ID) for a RAM section used
 *  in Mcu_InitRamSection()
 */
typedef uint8 Mcu_RamSectionType;

/* Requirements : SWS_Mcu_00254,SWS_Mcu_00237,SWS_Mcu_00238 */
/**
 *  \brief This type specifies the identification (ID) for a MCU mode used
 *  in Mcu_SetMode()
 */
typedef uint8 Mcu_ModeType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \addtogroup MCAL_MCU_CFG MCU Configuration
 *  @{
 */

/* Requirements: SWS_Mcu_00252,SWS_Mcu_00234 */
/**
 *  \brief  This is the type of the reset enumerator containing the subset of
 *  reset types. <br>
 *  It is not required that all reset types are supported by hardware
 *
 */
typedef enum
{
    /* Requirements: SWS_Mcu_00134 */
    MCU_POWER_ON_RESET = 0,         /*!< Power On reset */
    MCU_WARM_SW_RESET,              /*!< Software intiated warm reset */
    MCU_WATCHDOG_RESET,             /*!< Watchdog reset */
    MCU_WARM_EXTERNAL_RESET,        /*!< Watchdog reset */
    MCU_ICEPICK_RESET,              /*!< Debug reset */
    MCU_TEMP_SHUTDOWN_CORE_RESET,   /*!< Temperature shutdown from core */
    MCU_TEMP_SHUTDOWN_DSPEVE_RESET, /*!< Temperature shutdown from dsp/eve */
    MCU_TEMP_SHUTDOWN_MPU_RESET,    /*!< Temperature shutdown from mpu
                                     * (applicable only for TDA2x) */
    MCU_TEMP_SHUTDOWN_MM_RESET,     /*!< Temperature shutdown from mm
                                     *  (applicable only for TDA2x) */
    MCU_TEMP_SHUTDOWN_IVA_RESET,    /*!< Temperature shutdown from iva
                                     * (applicable only for TDA2x) */
    MCU_RESET_UNDEFINED             /*!< Undefined reset */
} Mcu_ResetType;

/* Requirements: SWS_Mcu_00250,SWS_Mcu_00231 */
/**
 *  \enum Mcu_PllStatusType
 *  \brief  This is a status value returned by the function Mcu_GetPllStatus()
 *  of the MCU module.
 */
typedef enum
{
    MCU_PLL_LOCKED = 0,
    MCU_PLL_UNLOCKED,
    MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

/* Requirements : SWS_Mcu_00256 */
/**
 *  \enum Mcu_RamStateType
 *  \brief  Enumeration of ranstate queried by Mcu_GetRamState()
 */
typedef enum
{
    MCU_RAMSTATE_INVALID,
    MCU_RAMSTATE_VALID
} Mcu_RamStateType;

/* Enumerated list of interrupt sources into the IRQ_XBAR */
/**
 *  \enum Mcu_IrqXbarIntrSourceType
 *  \brief Enumeration that contains all possible interrupt source IDs as
 *  inputs to each irq crossbar instance on TDA2x/TDA3x
 *
 */
typedef enum
{
    MCU_IRQXBAR_INTR_SRC_GPIO1_IRQ_1,
    MCU_IRQXBAR_INTR_SRC_GPIO2_IRQ_1,
    MCU_IRQXBAR_INTR_SRC_GPIO3_IRQ_1,
    MCU_IRQXBAR_INTR_SRC_GPIO4_IRQ_1,
#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
    MCU_IRQXBAR_INTR_SRC_GPIO5_IRQ_1,
    MCU_IRQXBAR_INTR_SRC_GPIO6_IRQ_1,
    MCU_IRQXBAR_INTR_SRC_GPIO7_IRQ_1,
#endif
    MCU_IRQXBAR_INTR_SRC_MCSPI4_IRQ,
    MCU_IRQXBAR_INTR_SRC_MCSPI1_IRQ,
    MCU_IRQXBAR_INTR_SRC_MCSPI2_IRQ,
    MCU_IRQXBAR_INTR_SRC_MCSPI3_IRQ,
#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
    MCU_IRQXBAR_INTR_SRC_GPIO8_IRQ_1,
#endif
    MCU_IRQXBAR_INTR_SRC_GPIO1_IRQ_2,
    MCU_IRQXBAR_INTR_SRC_GPIO2_IRQ_2,
    MCU_IRQXBAR_INTR_SRC_GPIO3_IRQ_2,
    MCU_IRQXBAR_INTR_SRC_GPIO4_IRQ_2,
#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
    MCU_IRQXBAR_INTR_SRC_GPIO5_IRQ_2,
    MCU_IRQXBAR_INTR_SRC_GPIO6_IRQ_2,
#endif
    MCU_IRQXBAR_INTR_SRC_DCAN1_IRQ_INT0,
    MCU_IRQXBAR_INTR_SRC_DCAN1_IRQ_INT1,
    MCU_IRQXBAR_INTR_SRC_DCAN1_IRQ_PARITY,
    MCU_IRQXBAR_INTR_SRC_DCAN2_IRQ_INT0,
    MCU_IRQXBAR_INTR_SRC_DCAN2_IRQ_INT1,
    MCU_IRQXBAR_INTR_SRC_DCAN2_IRQ_PARITY,
    MCU_IRQXBAR_INTR_SRC_GMAC_SW_IRQ_RX_THRESH_PULSE,
    MCU_IRQXBAR_INTR_SRC_GMAC_SW_IRQ_RX_PULSE,
    MCU_IRQXBAR_INTR_SRC_GMAC_SW_IRQ_TX_PULSE,
    MCU_IRQXBAR_INTR_SRC_GMAC_SW_IRQ_MISC_PULSE,
    MCU_IRQXBAR_INTR_SRC_QSPI_IRQ,
#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
    MCU_IRQXBAR_INTR_SRC_GPIO7_IRQ_2,
    MCU_IRQXBAR_INTR_SRC_GPIO8_IRQ_2,
#endif
#if defined (TDA3XX_BUILD) || defined (TDA2PX_BUILD)
    MCU_IRQXBAR_INTR_SRC_MCAN_INT0,
    MCU_IRQXBAR_INTR_SRC_MCAN_INT_ECC,
#endif
#if defined (TDA3XX_BUILD)
    MCU_IRQXBAR_INTR_SRC_ADC1_IRQ,
    MCU_IRQXBAR_INTR_SRC_MBX_2_USER_3,
#endif
    MCU_IRQXBAR_INTR_SRC_GPTIMER1_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER2_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER3_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER4_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER5_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER6_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER7_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER8_IRQ,
    MCU_IRQXBAR_INTR_SRC_PWMSS1_IRQ,
#if defined (TDA2XX_BUILD) || defined (TDA2EX_BUILD) || defined (TDA2PX_BUILD)
    MCU_IRQXBAR_INTR_SRC_GPTIMER9_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER10_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER11_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER12_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER13_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER14_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER15_IRQ,
    MCU_IRQXBAR_INTR_SRC_GPTIMER16_IRQ,
    MCU_IRQXBAR_INTR_SRC_PWMSS2_IRQ,
    MCU_IRQXBAR_INTR_SRC_PWMSS3_IRQ,
#if defined (BUILD_A15)
    MCU_IRQXBAR_INTR_SRC_MBX_5_USER_2,
    MCU_IRQXBAR_INTR_SRC_UART3_IRQ,
    MCU_IRQXBAR_INTR_SRC_UART5_IRQ,
#else
    MCU_IRQXBAR_INTR_SRC_MBX_7_USER_3,
    MCU_IRQXBAR_INTR_SRC_MBX_5_USER_3,
    MCU_IRQXBAR_INTR_SRC_MBX_2_USER_2,
    MCU_IRQXBAR_INTR_SRC_UART3_IRQ,
    MCU_IRQXBAR_INTR_SRC_UART5_IRQ,
#endif

#endif
} Mcu_IrqXbarIntrSourceType;

/* Enumerated list of interrupt sources into the IRQ_XBAR */
/**
 *  \enum Mcu_IrqXbarInstType
 *  \brief Enumeration that contains the MCU IRQ XBAR instance number
 */
typedef enum
{
#if (defined (BUILD_M4))
    MCU_IRQXBAR_INST_IPU_IRQ_23,
    MCU_IRQXBAR_INST_IPU_IRQ_24,
    MCU_IRQXBAR_INST_IPU_IRQ_25,
    MCU_IRQXBAR_INST_IPU_IRQ_26,
    MCU_IRQXBAR_INST_IPU_IRQ_27,
    MCU_IRQXBAR_INST_IPU_IRQ_28,
    MCU_IRQXBAR_INST_IPU_IRQ_29,
    MCU_IRQXBAR_INST_IPU_IRQ_30,
    MCU_IRQXBAR_INST_IPU_IRQ_31,
    MCU_IRQXBAR_INST_IPU_IRQ_32,
    MCU_IRQXBAR_INST_IPU_IRQ_33,
    MCU_IRQXBAR_INST_IPU_IRQ_34,
    MCU_IRQXBAR_INST_IPU_IRQ_35,
    MCU_IRQXBAR_INST_IPU_IRQ_36,
    MCU_IRQXBAR_INST_IPU_IRQ_37,
    MCU_IRQXBAR_INST_IPU_IRQ_38,
    MCU_IRQXBAR_INST_IPU_IRQ_39,
    MCU_IRQXBAR_INST_IPU_IRQ_40,
    MCU_IRQXBAR_INST_IPU_IRQ_41,
    MCU_IRQXBAR_INST_IPU_IRQ_42,
    MCU_IRQXBAR_INST_IPU_IRQ_43,
    MCU_IRQXBAR_INST_IPU_IRQ_44,
    MCU_IRQXBAR_INST_IPU_IRQ_45,
    MCU_IRQXBAR_INST_IPU_IRQ_46,
    MCU_IRQXBAR_INST_IPU_IRQ_47,
    MCU_IRQXBAR_INST_IPU_IRQ_48,
    MCU_IRQXBAR_INST_IPU_IRQ_49,
    MCU_IRQXBAR_INST_IPU_IRQ_50,
    MCU_IRQXBAR_INST_IPU_IRQ_51,
    MCU_IRQXBAR_INST_IPU_IRQ_52,
    MCU_IRQXBAR_INST_IPU_IRQ_53,
    MCU_IRQXBAR_INST_IPU_IRQ_54,
    MCU_IRQXBAR_INST_IPU_IRQ_55,
    MCU_IRQXBAR_INST_IPU_IRQ_56,
    MCU_IRQXBAR_INST_IPU_IRQ_57,
    MCU_IRQXBAR_INST_IPU_IRQ_58,
    MCU_IRQXBAR_INST_IPU_IRQ_59,
    MCU_IRQXBAR_INST_IPU_IRQ_60,
    MCU_IRQXBAR_INST_IPU_IRQ_61,
    MCU_IRQXBAR_INST_IPU_IRQ_62,
    MCU_IRQXBAR_INST_IPU_IRQ_63,
    MCU_IRQXBAR_INST_IPU_IRQ_64,
    MCU_IRQXBAR_INST_IPU_IRQ_65,
    MCU_IRQXBAR_INST_IPU_IRQ_66,
    MCU_IRQXBAR_INST_IPU_IRQ_67,
    MCU_IRQXBAR_INST_IPU_IRQ_68,
    MCU_IRQXBAR_INST_IPU_IRQ_69,
    MCU_IRQXBAR_INST_IPU_IRQ_70,
    MCU_IRQXBAR_INST_IPU_IRQ_71,
    MCU_IRQXBAR_INST_IPU_IRQ_72,
    MCU_IRQXBAR_INST_IPU_IRQ_73,
    MCU_IRQXBAR_INST_IPU_IRQ_74,
    MCU_IRQXBAR_INST_IPU_IRQ_75,
    MCU_IRQXBAR_INST_IPU_IRQ_76,
    MCU_IRQXBAR_INST_IPU_IRQ_77,
    MCU_IRQXBAR_INST_IPU_IRQ_78,
    MCU_IRQXBAR_INST_IPU_IRQ_79
#elif (defined (BUILD_A15))
    MCU_IRQXBAR_INST_MPU_IRQ_4,
    MCU_IRQXBAR_INST_MPU_IRQ_7,
    MCU_IRQXBAR_INST_MPU_IRQ_8,
    MCU_IRQXBAR_INST_MPU_IRQ_9,
    MCU_IRQXBAR_INST_MPU_IRQ_10,
    MCU_IRQXBAR_INST_MPU_IRQ_11,
    MCU_IRQXBAR_INST_MPU_IRQ_12,
    MCU_IRQXBAR_INST_MPU_IRQ_13,
    MCU_IRQXBAR_INST_MPU_IRQ_14,
    MCU_IRQXBAR_INST_MPU_IRQ_15,
    MCU_IRQXBAR_INST_MPU_IRQ_16,
    MCU_IRQXBAR_INST_MPU_IRQ_17,
    MCU_IRQXBAR_INST_MPU_IRQ_18,
    MCU_IRQXBAR_INST_MPU_IRQ_19,
    MCU_IRQXBAR_INST_MPU_IRQ_20,
    MCU_IRQXBAR_INST_MPU_IRQ_21,
    MCU_IRQXBAR_INST_MPU_IRQ_22,
    MCU_IRQXBAR_INST_MPU_IRQ_23,
    MCU_IRQXBAR_INST_MPU_IRQ_24,
    MCU_IRQXBAR_INST_MPU_IRQ_25,
    MCU_IRQXBAR_INST_MPU_IRQ_26,
    MCU_IRQXBAR_INST_MPU_IRQ_27,
    MCU_IRQXBAR_INST_MPU_IRQ_28,
    MCU_IRQXBAR_INST_MPU_IRQ_29,
    MCU_IRQXBAR_INST_MPU_IRQ_30,
    MCU_IRQXBAR_INST_MPU_IRQ_31,
    MCU_IRQXBAR_INST_MPU_IRQ_32,
    MCU_IRQXBAR_INST_MPU_IRQ_33,
    MCU_IRQXBAR_INST_MPU_IRQ_34,
    MCU_IRQXBAR_INST_MPU_IRQ_35,
    MCU_IRQXBAR_INST_MPU_IRQ_36,
    MCU_IRQXBAR_INST_MPU_IRQ_37,
    MCU_IRQXBAR_INST_MPU_IRQ_38,
    MCU_IRQXBAR_INST_MPU_IRQ_39,
    MCU_IRQXBAR_INST_MPU_IRQ_40,
    MCU_IRQXBAR_INST_MPU_IRQ_41,
    MCU_IRQXBAR_INST_MPU_IRQ_42,
    MCU_IRQXBAR_INST_MPU_IRQ_43,
    MCU_IRQXBAR_INST_MPU_IRQ_44,
    MCU_IRQXBAR_INST_MPU_IRQ_45,
    MCU_IRQXBAR_INST_MPU_IRQ_46,
    MCU_IRQXBAR_INST_MPU_IRQ_47,
    MCU_IRQXBAR_INST_MPU_IRQ_48,
    MCU_IRQXBAR_INST_MPU_IRQ_49,
    MCU_IRQXBAR_INST_MPU_IRQ_50,
    MCU_IRQXBAR_INST_MPU_IRQ_51,
    MCU_IRQXBAR_INST_MPU_IRQ_52,
    MCU_IRQXBAR_INST_MPU_IRQ_53,
    MCU_IRQXBAR_INST_MPU_IRQ_54,
    MCU_IRQXBAR_INST_MPU_IRQ_55,
    MCU_IRQXBAR_INST_MPU_IRQ_56,
    MCU_IRQXBAR_INST_MPU_IRQ_57,
    MCU_IRQXBAR_INST_MPU_IRQ_58,
    MCU_IRQXBAR_INST_MPU_IRQ_59,
    MCU_IRQXBAR_INST_MPU_IRQ_60,
    MCU_IRQXBAR_INST_MPU_IRQ_61,
    MCU_IRQXBAR_INST_MPU_IRQ_62,
    MCU_IRQXBAR_INST_MPU_IRQ_63,
    MCU_IRQXBAR_INST_MPU_IRQ_64,
    MCU_IRQXBAR_INST_MPU_IRQ_65,
    MCU_IRQXBAR_INST_MPU_IRQ_66,
    MCU_IRQXBAR_INST_MPU_IRQ_67,
    MCU_IRQXBAR_INST_MPU_IRQ_68,
    MCU_IRQXBAR_INST_MPU_IRQ_69,
    MCU_IRQXBAR_INST_MPU_IRQ_70,
    MCU_IRQXBAR_INST_MPU_IRQ_71,
    MCU_IRQXBAR_INST_MPU_IRQ_72,
    MCU_IRQXBAR_INST_MPU_IRQ_73,
    MCU_IRQXBAR_INST_MPU_IRQ_74,
    MCU_IRQXBAR_INST_MPU_IRQ_75,
    MCU_IRQXBAR_INST_MPU_IRQ_76,
    MCU_IRQXBAR_INST_MPU_IRQ_77,
    MCU_IRQXBAR_INST_MPU_IRQ_78,
    MCU_IRQXBAR_INST_MPU_IRQ_79,
    MCU_IRQXBAR_INST_MPU_IRQ_80,
    MCU_IRQXBAR_INST_MPU_IRQ_81,
    MCU_IRQXBAR_INST_MPU_IRQ_82,
    MCU_IRQXBAR_INST_MPU_IRQ_83,
    MCU_IRQXBAR_INST_MPU_IRQ_84,
    MCU_IRQXBAR_INST_MPU_IRQ_85,
    MCU_IRQXBAR_INST_MPU_IRQ_86,
    MCU_IRQXBAR_INST_MPU_IRQ_87,
    MCU_IRQXBAR_INST_MPU_IRQ_88,
    MCU_IRQXBAR_INST_MPU_IRQ_89,
    MCU_IRQXBAR_INST_MPU_IRQ_90,
    MCU_IRQXBAR_INST_MPU_IRQ_91,
    MCU_IRQXBAR_INST_MPU_IRQ_92,
    MCU_IRQXBAR_INST_MPU_IRQ_93,
    MCU_IRQXBAR_INST_MPU_IRQ_94,
    MCU_IRQXBAR_INST_MPU_IRQ_95,
    MCU_IRQXBAR_INST_MPU_IRQ_96,
    MCU_IRQXBAR_INST_MPU_IRQ_97,
    MCU_IRQXBAR_INST_MPU_IRQ_98,
    MCU_IRQXBAR_INST_MPU_IRQ_99,
    MCU_IRQXBAR_INST_MPU_IRQ_100,
    MCU_IRQXBAR_INST_MPU_IRQ_101,
    MCU_IRQXBAR_INST_MPU_IRQ_102,
    MCU_IRQXBAR_INST_MPU_IRQ_103,
    MCU_IRQXBAR_INST_MPU_IRQ_104,
    MCU_IRQXBAR_INST_MPU_IRQ_105,
    MCU_IRQXBAR_INST_MPU_IRQ_106,
    MCU_IRQXBAR_INST_MPU_IRQ_107,
    MCU_IRQXBAR_INST_MPU_IRQ_108,
    MCU_IRQXBAR_INST_MPU_IRQ_109,
    MCU_IRQXBAR_INST_MPU_IRQ_110,
    MCU_IRQXBAR_INST_MPU_IRQ_111,
    MCU_IRQXBAR_INST_MPU_IRQ_112,
    MCU_IRQXBAR_INST_MPU_IRQ_113,
    MCU_IRQXBAR_INST_MPU_IRQ_114,
    MCU_IRQXBAR_INST_MPU_IRQ_115,
    MCU_IRQXBAR_INST_MPU_IRQ_116,
    MCU_IRQXBAR_INST_MPU_IRQ_117,
    MCU_IRQXBAR_INST_MPU_IRQ_118,
    MCU_IRQXBAR_INST_MPU_IRQ_119,
    MCU_IRQXBAR_INST_MPU_IRQ_120,
    MCU_IRQXBAR_INST_MPU_IRQ_121,
    MCU_IRQXBAR_INST_MPU_IRQ_122,
    MCU_IRQXBAR_INST_MPU_IRQ_123,
    MCU_IRQXBAR_INST_MPU_IRQ_124,
    MCU_IRQXBAR_INST_MPU_IRQ_125,
    MCU_IRQXBAR_INST_MPU_IRQ_126,
    MCU_IRQXBAR_INST_MPU_IRQ_127,
    MCU_IRQXBAR_INST_MPU_IRQ_128,
    MCU_IRQXBAR_INST_MPU_IRQ_129,
    MCU_IRQXBAR_INST_MPU_IRQ_130,
    MCU_IRQXBAR_INST_MPU_IRQ_133,
    MCU_IRQXBAR_INST_MPU_IRQ_134,
    MCU_IRQXBAR_INST_MPU_IRQ_135,
    MCU_IRQXBAR_INST_MPU_IRQ_136,
    MCU_IRQXBAR_INST_MPU_IRQ_137,
    MCU_IRQXBAR_INST_MPU_IRQ_138,
    MCU_IRQXBAR_INST_MPU_IRQ_141,
    MCU_IRQXBAR_INST_MPU_IRQ_142,
    MCU_IRQXBAR_INST_MPU_IRQ_143,
    MCU_IRQXBAR_INST_MPU_IRQ_144,
    MCU_IRQXBAR_INST_MPU_IRQ_145,
    MCU_IRQXBAR_INST_MPU_IRQ_146,
    MCU_IRQXBAR_INST_MPU_IRQ_147,
    MCU_IRQXBAR_INST_MPU_IRQ_148,
    MCU_IRQXBAR_INST_MPU_IRQ_149,
    MCU_IRQXBAR_INST_MPU_IRQ_150,
    MCU_IRQXBAR_INST_MPU_IRQ_151,
    MCU_IRQXBAR_INST_MPU_IRQ_152,
    MCU_IRQXBAR_INST_MPU_IRQ_153,
    MCU_IRQXBAR_INST_MPU_IRQ_154,
    MCU_IRQXBAR_INST_MPU_IRQ_155,
    MCU_IRQXBAR_INST_MPU_IRQ_156,
    MCU_IRQXBAR_INST_MPU_IRQ_157,
    MCU_IRQXBAR_INST_MPU_IRQ_158,
    MCU_IRQXBAR_INST_MPU_IRQ_159
#endif
} Mcu_IrqXbarInstType;

/**
 *  \enum Mcu_ClkModuleIdType
 *  \brief Clock source config modules id enum
 *
 *  Clock source config ids defines are used to set clock source for specific
 *  modules
 */
typedef enum
{
    /** \brief QSPI1 module. */
    MCU_CLKSRC_MODULE_ID_QSPI1 = 0,
    MCU_CLKSRC_MODULE_ID_RTI1,
    MCU_CLKSRC_MODULE_ID_RTI2,
    MCU_CLKSRC_MODULE_ID_RTI3,
    MCU_CLKSRC_MODULE_ID_RTI4,
    MCU_CLKSRC_MODULE_ID_RTI5,
} Mcu_ClkModuleIdType;

/**
 * \brief  This is the type of the clock source in clock tree that is selectable
 *         for QSPI peripheral
 */
typedef enum
{
    MCU_CLKSRC_QSPI_PER_QSPI_CLK = 0,   /*!< PER_QSPI_CLK from DPLL_PER */
    MCU_CLKSRC_QSPI_FUNC_128M_CLK,      /*!< 128MHz derived from DPLL_PER */
} Mcu_ClkSourceType;

/**
 * \brief  This is the type of the clock source in clock tree that is selectable
 *         for QSPI peripheral
 */
enum
{
    MCU_CLKSRC_RTI_SYSCLK1 = 0,   /*!< sysclk1/4 as RTI functional clock */
    MCU_CLKSRC_RTI_SYSCLK2,       /*!< sysclk2/4 as RTI functional clock */
    MCU_CLKSRC_RTI_32KHZ,         /*!< 32Khz as RTI functional clock */
};

/**
 *  \brief  This is the divider for the clock source in clock tree that is
 *  selectable for different MCU_CLKSRC_MODULE_ID
 */
typedef enum
{
    MCU_CLKDIV_DIV_1 = 0,   /*!< Functional clock = (Input clksrc / 1) */
    MCU_CLKDIV_DIV_2,       /*!< Functional clock = (Input clksrc / 2) */
    MCU_CLKDIV_DIV_4        /*!< Functional clock = (Input clksrc / 4) */
} Mcu_ClkDivType;

/**
 *  \brief Structure for PRCM configuration
 */
typedef struct
{
    uint8 Mcu_PrcmModuleId;
    /**< Moudle Id to enable/disable */
    uint8 Mcu_PrcmModuleMode;
    /**< Moudle mode to set @sa MCAL_MCU_API:PRCM modules mode defines */
} Mcu_PrcmConfigType;

/**
 *  \brief Structure for IRQ Crossbar configuration
 */
typedef struct
{
    Mcu_IrqXbarIntrSourceType Mcu_IrqXbarIntrSource;
    /**< Interrupt Source @sa MCAL_MCU_API:Mcu_IrqXbarIntrSourceType */
    uint32 Mcu_IrqXbarInst;
    /**< Interrupt Crossbar instance to map @sa MCAL_MCU_API:Mcu_IrqXbarInst */
} Mcu_IrqXbarConfigType;

/* Requirements: SWS_Mcu_00030 */
/**
 *  \brief Structure for data pre-setting to be initialized
 */
typedef struct
{
    P2VAR(uint8, AUTOMATIC, MCU_RAM_COPY) Mcu_RamSectionBaseAddress;
    /**< RAM section base address, Destination */
    uint8  Mcu_RamDefaultValue;
    /**< RAM Default Value */
    uint32 Mcu_RamSectionBytes;
    /**< Section Size */
} Mcu_RamSectionConfigType;

/* Requirements: SWS_Mcu_00031 */
/**
 *  \brief Structure for module clock setting
 */
typedef struct
{
    Mcu_ClkModuleIdType Mcu_ClockModuleId;
    /**< ModuleId for which clock setting to be applied */
    uint32   Mcu_ClockSourceId;
    /**< Clock source Id for the module */
    Mcu_ClkDivType      Mcu_ClockDivId;
    /**< Clock divider id for the module @sa MCAL_MCU_API:Mcu_ClkDivType */
    boolean             Mcu_InitCfg;
    /**< Apply this configuration at Mcu_init time*/
} Mcu_ClockConfigType;

/* Requirements: SWS_Mcu_00249,SWS_Mcu_00131 */
/**
 *  \brief MCU CONFIG ROOT structure
 */
typedef struct Mcu_ConfigType_s
{
    uint8                    Mcu_ResetMode;
    /**< Reset mode to be used @sa  MCAL_MCU_API:ResetModes */
    /* Requirements: SWS_Mcu_00030 */
    const Mcu_RamSectionConfigType *Mcu_ConfigRamSection;
    /**< Configration of Ram Sections */
    uint8                    Mcu_NumberOfRamSectors;
    /**< Number of entries in Mcu_ConfigRamSection */
    const Mcu_PrcmConfigType *Mcu_PrcmConfig;
    /**< Configration of PRCM modules */
    uint8                    Mcu_NumberOfPrcmModules;
    /**< Number of entries in Mcu_PrcmConfig */
    const Mcu_IrqXbarConfigType    *Mcu_IrqXbarConfig;
    /**< Configuration of IrqXbar */
    uint8                    Mcu_NumberOfIrqSources;
    /**< Number of entries in Mcu_IrqXbarConfig */
    /* Requirements: SWS_Mcu_00031 */
    const Mcu_ClockConfigType *   Mcu_ClockConfig;
    /**< Configuration of Module functional clock source */
    uint8                    Mcu_NumberOfClockConfig;
    /**< Number of entries in Mcu_PrcmConfig */
} Mcu_ConfigType;
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  This service initializes the MCU driver
 *
 *  \verbatim
 *  Service name      : Mcu_Init
 *  Syntax            : void Mcu_Init(const Mcu_ConfigType* CfgPtr)
 *  Service ID[hex]   : 0x0
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CfgPtr - Pointer to MCU driver configuration set.
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : This service initializes the MCU driver
 *  \endverbatim
 */
FUNC(void, MCU_CODE) Mcu_Init(
    P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_PBCFG) CfgPtr);

#if (STD_ON == MCU_INIT_RAM_API)
/**
 *  \brief This service initializes the RAM section wise
 *
 *  \verbatim
 *  Service name      : Mcu_InitRamSection
 *  Syntax            : Std_ReturnType Mcu_InitRamSection(
 *                                  Mcu_RamSectionType RamSection )
 *  Service ID[hex]   : 0x01
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : RamSection - Selects RAM memory section provided
 *                      in configuration set
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                    - E_OK: command has been accepted
 *                    - E_NOT_OK: command has not been accepted e.g. due to
 *                      parameter error
 *  Description       : This service initializes the RAM section wise
 *  \endverbatim
 */
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitRamSection(
    Mcu_RamSectionType RamSection);
#endif /* MCU_INIT_RAM_API */

#if (STD_ON == MCU_INIT_CLOCK_API)
/**
 *  \brief This service initializes the PLL and other MCU specific clock options
 *
 *  \verbatim
 *  Service name      : Mcu_InitClock
 *  Syntax            : Std_ReturnType Mcu_InitClock(
 *                           Mcu_ClockType ClockSetting )
 *  Service ID[hex]   : 0x02
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : ClockSetting - Clock setting
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                    - E_OK: Command has been accepted
 *                    - E_NOT_OK: Command has not been accepted
 *  Description       : This service initializes the PLL and other MCU specific
 *                      clock options
 * \endverbatim
 */
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitClock(Mcu_ClockType ClockSetting);
#endif /* MCU_INIT_CLOCK_API */

#if (STD_ON == MCU_PERFORM_RESET_API)
/**
 *  \brief The service performs a microcontroller reset
 *
 *  \verbatim
 *  Service name      : Mcu_PerformReset
 *  Syntax            : void Mcu_PerformReset( void )
 *  Service ID[hex]   : 0x07
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : The service performs a microcontroller reset
 *  \endverbatim
 */
FUNC(void, MCU_CODE) Mcu_PerformReset(void);
#endif  /* MCU_PERFORM_RESET_API */

/* Requirements: SWS_Mcu_00230 */
/**
 *  \brief This service provides the lock status of the PLL.
 *
 *  \verbatim
 *  Service name      : Mcu_GetPllStatus
 *  Syntax            : Mcu_PllStatusType Mcu_GetPllStatus( void )
 *  Service ID[hex]   : 0x04
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Mcu_PllStatusType - PLL Status
 *  Description       : This service provides the lock status of the PLL.
 *  \endverbatim
 */
FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus(void);

/**
 *  \brief The service reads the reset type from the hardware, if supported
 *
 *  \verbatim
 *  Service name      : Mcu_GetResetReason
 *  Syntax            : Mcu_ResetType Mcu_GetResetReason( void )
 *  Service ID[hex]   : 0x05
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Mcu_ResetType
 *  Description       : The service reads the reset type from the hardware, if
 *                      supported
 *  \endverbatim
 */
FUNC(Mcu_ResetType, MCU_CODE) Mcu_GetResetReason(void);

/**
 *  \brief The service reads the reset type from the hardware register, if
 *  supported
 *
 *  \verbatim
 *  Service name      : Mcu_GetResetRawValue
 *  Syntax            : Mcu_RawResetType Mcu_GetResetRawValue( void )
 *  Service ID[hex]   : 0x06
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : nONE
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Mcu_RawResetType - Reset raw value
 *  Description       : The service reads the reset type from the hardware
 *                      register, if supported
 *  \endverbatim
 */
FUNC(Mcu_RawResetType, MCU_CODE) Mcu_GetResetRawValue(void);

#if (STD_ON == MCU_CLEAR_RESET_REASON_API)
/**
 *  \brief Clear the Mcu Reset reason by clearing the reset reason register
 *
 *  \verbatim
 *  Service name      : Mcu_ClearResetReason
 *  Syntax            : void Mcu_ClearResetReason(void)
 *  Service ID[hex]   : N/A
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Clear the Mcu Reset reason by clearing the reset reason
 *                      register
 *  \endverbatim
 */
FUNC(void, MCU_CODE) Mcu_ClearResetReason(void);
#endif  /* MCU_CLEAR_RESET_REASON_API */

#if (STD_ON == MCU_GET_RAM_STATE_API)
/**
 *  \brief This service provides the actual status of the microcontroller Ram.
 *  (if supported)
 *
 *  \verbatim
 *  Service name      : Mcu_GetRamState
 *  Syntax            : Mcu_RamStateType Mcu_GetRamState(void)
 *  Service ID[hex]   : 0x0a
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Mcu_RamStateType - Status of the Ram Content
 *  Description       : This service provides the actual status of the
 *                      microcontroller Ram. (if supported)
 *  \endverbatim
 */
FUNC(Mcu_RamStateType, MCU_CODE) Mcu_GetRamState(void);
#endif  /* MCU_GET_RAM_STATE_API */

#if (STD_ON == MCU_GET_VERSION_INFO_API)
/**
 *  \brief This service returns the version information of this module
 *
 *  \verbatim
 *  Service name      : Mcu_GetVersionInfo
 *  Syntax            : void Mcu_GetVersionInfo(Std_VersionInfoType*
 *                              versioninfo)
 *  Service ID[hex]   : 0x09
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : versioninfo - Pointer to where to store the
 *                      version information of this module.
 *  Return value      : None
 *  Description       : This service returns the version information of this
 *                      module
 *  \endverbatim
 */
FUNC(void, MCU_CODE) Mcu_GetVersionInfo(
    P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA) versioninfo);
#endif  /* MCU_GET_VERSION_INFO_API */

/**
 *  \brief This service always returns E_OK. The Mcu mode is not programmed by
 *          Mcu module.
 *
 *  \verbatim
 *  Service name      : Mcu_SetMode
 *  Syntax            : void Mcu_SetMode(Mcu_ModeType McuMode)
 *  Service ID[hex]   : 0x08
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : McuMode
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType - E_OK: Always
 *  Description       : This service activates the MCU power modes
 *                      The current implementation dosen't activate power modes.
 *  \endverbatim
 */
void Mcu_SetMode(Mcu_ModeType McuMode);

#if (STD_OFF == MCU_NO_PLL)
/**
 *  \brief This service always returns E_OK. The PLL's are not programmed by
 *          Mcu module.
 *
 *  \verbatim
 *  Service name      : Mcu_DistributePllClock
 *  Syntax            : Std_ReturnType Mcu_DistributePllClock(void)
 *  Service ID[hex]   : 0x03
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType - E_OK: Always
 *  Description       : This service activates the PLL clock to the MCU clock
 *                      distribution. The current implementation dosen't
 *                      activate clock.
 *  \endverbatim
 */
FUNC(Std_ReturnType, MCU_CODE) Mcu_DistributePllClock(void);
#endif /* STD_OFF == MCU_NO_PLL */

/**
 *  \brief This service is only used for UT testing and not for app use
 *
 *  \verbatim
 *  Service name      : Mcu_DeInit
 *  Syntax            : void Mcu_DeInit(void)
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non-Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : This service sets the internal MCU initDone flag to
 *                      FALSE so that Mcu_Init can be invoked again.
 *                      This is required for negative UT test cases
 *  \endverbatim
 */
FUNC(void, MCU_CODE) Mcu_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef MCU_H_ */

/* @} */
