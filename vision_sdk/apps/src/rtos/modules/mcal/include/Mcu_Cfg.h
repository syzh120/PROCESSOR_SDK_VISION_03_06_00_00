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
 *  \file     Mcu_Cfg.h
 *
 *  \brief    This file contains generated pre compile configuration file
 *            for MCU MCAL driver
 *
 */

/**
 *  \defgroup MCAL_MCU_CFG MCU Configuration
 *
 *  This files defines MCU MCAL configuration structures
 *  @{
 */

#ifndef MCU_CFG_H_
#define MCU_CFG_H_

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

/** \brief MCU Config ID */
#define MCU_CFG_ID                      (MCU_CFG_ID_0)

/* Requirements: SWS_Mcu_00129 */
/**
 *  \name MCU Driver Configuration SW Version Info
 *
 *  Defines for Mcu Driver configuration version
 *  @{
 */
#define MCU_CFG_MAJOR_VERSION           (1U)
#define MCU_CFG_MINOR_VERSION           (9U)
#define MCU_CFG_PATCH_VERSION           (0U)
/* @} */

/**
 *  \name Service enable/diable defines
 *
 *  Pre-compile switches for enabling/disabling MCU MCAL APIs
 *  @{
 */
/** \brief Enable/Disable Development Error Detection */
#define MCU_DEV_ERROR_DETECT            (STD_ON)

/** \brief Enable/Disable Mcu_CheckRamState() API */
#define MCU_GET_RAM_STATE_API           (STD_ON)

/** \brief Enable/Disable Mcu_InitClock() API */
#define MCU_INIT_CLOCK_API              (STD_ON)

/** \brief Enable/Disable Mcu_PerformReset() API */
#define MCU_PERFORM_RESET_API           (STD_OFF)

/** \brief Enable/Disable Mcu_GetVersionInfo() API */
#define MCU_GET_VERSION_INFO_API        (STD_ON)

/** \brief Enable/Disable Mcu_InitRamSection() API */
#define MCU_INIT_RAM_API                (STD_ON)

/** \brief Enable/Disable PLL support */
#define MCU_NO_PLL                      (STD_ON)

/** \brief Enable/Disable Mcu_ClearResetReason() API */
#define MCU_CLEAR_RESET_REASON_API      (STD_ON)

/* @} */

/** \brief Counter ID for counter used to count wait ticks */
#define MCU_OS_COUNTER_ID               ((CounterType) 0x0U)

/**
 *  \brief MCU timeout - used in MCU check Mode.
 *   Each tick is 31.25us (for 32K Counter). Wait for 1s which comes to
 *   below value
 */
#define MCU_TIMEOUT_DURATION            (0x7D00U)

/**
*  \brief MCU Build Variant.
*   Build variants.(i.e Precompile,postbuild or linktime)
*/
#define MCU_PRE_COMPILE_VARIANT         (STD_OFF)

/**
 *  \name MCU DEM Error codes to report
 *
 *  Pre-compile switches for enabling/disabling DEM events
 *  @{
 */
#define DemConf_DemEventParameter_MCU_DEM_NO_EVENT (0xFFFFU)
#define MCU_DEM_NO_EVENT DemConf_DemEventParameter_MCU_DEM_NO_EVENT

#ifndef MCU_E_MODE_FAILURE
/** \brief Hardware failed */
#define MCU_E_MODE_FAILURE          (MCU_DEM_NO_EVENT)
#endif

#ifndef MCU_E_CLOCK_FAILURE
/** \brief Hardware failed */
#define MCU_E_CLOCK_FAILURE          (MCU_DEM_NO_EVENT)
#endif

/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/** \brief MCU Configuration struct declaration */
extern const struct Mcu_ConfigType_s McuModuleConfiguration_0;

/**
 * \brief  Type of McuModes supported
 */
enum
{
    MCU_MODE_NORMAL = 0 /*!< Mcu normal mode. Only supported mode */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef MCU_CFG_H_ */

/* @} */
