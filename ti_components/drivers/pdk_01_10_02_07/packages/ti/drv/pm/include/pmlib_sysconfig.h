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
 *  \ingroup PM_LIB PM LIB API
 *  \defgroup PMLIB_SYSCONFIG System Configuration
 *
 *  System Configuration APIs are used to put the module to a desired
 *  power state as specified by the power spread sheet. It abstracts
 *  the programming of PRCM registers to enable/disable or auto clock
 *  gate a given module. Many modules can be programmed in one go by providing
 *  the list of modules and their desired power state.
 *
 *  The system configuration does not take care of dependencies between
 *  modules and it is the user’s responsibility to maintain the right
 *  dependency order to switch off a given module vs another.
 *
 * @{
 */

/**
 *  \file  pmlib_sysconfig.h
 *
 *  \brief  This file declares the interface for the system configuration for
 *          switching on or switching off modules or putting them in HW
 *          controlled Auto Clock Gated mode.
 */

#ifndef PMLIB_SYSCONFIG_H_
#define PMLIB_SYSCONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of configurable reset lines for a module. */
#define PMLIB_SYS_CONFIG_MAX_RESET_CONFIG   (3U)

/**
 * \brief   Enumeration for programming the desired power mode for the module.
 */
typedef enum pmlibSysConfigPowerState
{
    PMLIB_SYS_CONFIG_MIN = 0U,
    /**< Minimum system configuration mode for the module */
    PMLIB_SYS_CONFIG_DISABLED = PMLIB_SYS_CONFIG_MIN,
    /**< Module is disabled/ switched off in this mode */
    PMLIB_SYS_CONFIG_AUTO_CG = 1U,
    /**< Module is auto clock gated in this mode. */
    PMLIB_SYS_CONFIG_ALWAYS_ENABLED = 2U,
    /**< Module is always enabled in this mode */
    PMLIB_SYS_CONFIG_MAX = PMLIB_SYS_CONFIG_ALWAYS_ENABLED,
    /**< Maximum system configuration mode for the module */
    PMLIB_SYS_CONFIG_COUNT = PMLIB_SYS_CONFIG_MAX + 1U,
    /**< Count of the system configuration modes for the module */
    PMLIB_SYS_CONFIG_INVALID = 0x7FFFFFFF
                               /**< Invalid system configuration */
} pmlibSysConfigPowerState_t;

/**
 * \brief   Structure to define the system configuration Table for a module.
 */
typedef struct pmlibSysConfigPowerStateParams
{
    pmhalPrcmModuleId_t        modId;
    /**< Module ID of the Module one wants to program */
    pmlibSysConfigPowerState_t pwrState;
    /**< Desired Power State for the module */
} pmlibSysConfigPowerStateParams_t;

/**
 * \brief   Structure to help the user understand if the module configuration
 *          was successful or not. If it is a failure the reason for the
 *          failure is also returned.
 */
typedef struct pmlibSysConfigErrReturn
{
    pmhalPrcmModuleId_t moduleId;
    /**< Module ID of the Module that is returned */
    pmErrCode_t         failCause;
    /**< Code which indicates cause of the failure */
} pmlibSysConfigErrReturn_t;

/**
 * \brief   Structure to help the user get the more detailed power mode in the
 *          PMLIBSysConfigGetPowerState API.
 */
typedef struct pmlibSysConfigDetailedState
{
    pmhalPrcmModuleSIdleState_t   moduleMode;
    /**< Details about the module mode for the given module */
    pmhalPrcmClockActivityState_t clockMode;
    /**< Details about the clock mode for the given module */
    pmhalPrcmPdState_t            pdMode;
    /**< Details about the power mode for the given module */
} pmlibSysConfigDetailedState_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API configures the given module to the desired power state.
 *
 * \param   inputTable      Table of modules and their desired power and
 *                          clock state.
 * \param   numConfig       Number of entries in the system configuration table.
 * \param   timeout         Desired time out for which one should wait for each
 *                          of the modules to reach its desired power state.
 *                        - #PM_TIMEOUT_NOWAIT - The API does not wait.
 *                        - #PM_TIMEOUT_INFINITE  - The API waits infinitely.
 *                        - Any other value - The API waits to any one of the
 *                          events to happen first :
 *                          - (1) Success of operation
 *                          - (2) The timeout is reached.
 * \param   resultReturn    Table which returns success or error codes got
 *                          while programming the power state. Useful for debug
 *                          One must allocate the same number of entries as the
 *                          input table to ensure the API has sufficient space
 *                          to return the error or pass codes. The structure
 *                          returns in the format
 *                          [module, return code (success/fail code)] for all
 *                          the modules given in a one to one mapping.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 - #PM_SUCCESS  If the desired power state was met.
 *                 - #PM_FAIL     If the desired power state was not met. One
 **must
 *                              check the resultReturn to check the cause for
 *                              failure.
 */
pmErrCode_t PMLIBSysConfigSetPowerState(
    const pmlibSysConfigPowerStateParams_t *inputTable,
    uint32_t                                numConfig,
    uint32_t                                timeout,
    pmlibSysConfigErrReturn_t              *resultReturn);

/**
 * \brief   This API initializes the table for the system config.
 *
 * \param   inputTable      Input table to be initialized
 * \param   numConfig       Number of entries in the system configuration table.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 - #PM_SUCCESS  If the initialization is complete.
 *                 - #PM_BADARGS  If the input parameters are not correct.
 */
pmErrCode_t PMLIBSysConfigPowerStateParams_init(
    pmlibSysConfigPowerStateParams_t *inputTable,
    uint32_t                          numConfig);

/**
 * \brief   This API is used to get the power state for a given module.
 *
 * \param   moduleId        Module ID of the module one is interested in. Refer
 *                          #pmhalPrcmModuleId_t for details.
 * \param   currState       Returns the final state of the module. Refer
 *                          #pmlibSysConfigPowerState_t for details.
 * \param   detailedState   This is an optional parameter which can be used to
 *                          return the detailed state of the module broken
 *                          down into module state, clock state and power state.
 *                          If one is not interested in knowing the detailed
 *                          state one can put NULL for this parameter.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 - #PM_SUCCESS  If the status is obtained correctly.
 *                 - #PM_BADARGS  If currState pointer is NULL.
 */
pmErrCode_t PMLIBSysConfigGetPowerState(
    pmhalPrcmModuleId_t            moduleId,
    pmlibSysConfigPowerState_t    *currState,
    pmlibSysConfigDetailedState_t *detailedState);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


