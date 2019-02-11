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
 * \file    pmlib_sysconfig.c
 *
 * \brief   This file defines the function used for
 *          switching on or switching off modules or putting them in HW
 *          controlled Auto Clock Gated mode.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include "pmhal_prcm.h"
#include "pm_utils.h"
#include "pmlib_sysconfig.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include "pmhal_rm.h"
#include "pmhal_pdm.h"
#include "pmhal_sd.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API is used to disable a given module.
 *
 * \param  modIdx       Unique ID of the module to be disabled.
 * \param  result      Structure to return to user the cause of failure.
 * \param  timeout     Time for which to wait for the module to be disabled.
 *                     PM_TIMEOUT_NOWAIT (0) - The API does not wait.
 *                     PM_TIMEOUT_INFINITE (0xFFFFFFFF) - The API waits
 *                     infinitely.
 *                     Any other value - The API waits to any one of the
 *                     events to happen first : (1) Success of operation
 *                     (2) The timeout is reached.
 *
 * \return errorStatus Status of the API call. Can be any of the following,
 *         PM_SUCCESS  Indicates the operation is success
 *         PM_FAIL     Indicates the module is not disabled (timeout)
 */
static pmErrCode_t PmlibSysConfigDisable(pmhalPrcmModuleId_t        modIdx,
                                         pmlibSysConfigErrReturn_t *result,
                                         uint32_t                   timeout);

/**
 * \brief This API is used to auto clock gate a given module.
 *
 * \param  modIdx       Unique ID of the module to be auto clock gated.
 * \param  result      Structure to return to user the cause of failure.
 * \param  timeout     Time for which to wait for the module to be auto clock
 *                     gated.
 *                     PM_TIMEOUT_NOWAIT (0) - The API does not wait.
 *                     PM_TIMEOUT_INFINITE (0xFFFFFFFF) - The API waits
 *                     infinitely.
 *                     Any other value - The API waits to any one of the
 *                     events to happen first : (1) Success of operation
 *                     (2) The timeout is reached.
 *
 * \return errorStatus Status of the API call. Can be any of the following,
 *         PM_SUCCESS  Indicates the operation is success
 *         PM_FAIL     Indicates failure of API
 */
static pmErrCode_t PmlibSysConfigAutoCg(pmhalPrcmModuleId_t        modIdx,
                                        pmlibSysConfigErrReturn_t *result,
                                        uint32_t                   timeout);

/**
 * \brief This API is used to enable a given module.
 *
 * \param  modIdx       Unique ID of the module to be enabled.
 * \param  result      Structure to return to user the cause of failure.
 * \param  timeout     Time for which to wait for the module to be enabled
 *                     PM_TIMEOUT_NOWAIT (0) - The API does not wait.
 *                     PM_TIMEOUT_INFINITE (0xFFFFFFFF) - The API waits
 *                     infinitely.
 *                     Any other value - The API waits to any one of the
 *                     events to happen first : (1) Success of operation
 *                     (2) The timeout is reached.
 *
 * \return errorStatus Status of the API call. Can be any of the following,
 *         PM_SUCCESS  Indicates the operation is success
 *         PM_FAIL     Indicates the module is not enabled (timeout)
 */
static pmErrCode_t PmlibSysConfigEnable(pmhalPrcmModuleId_t        modIdx,
                                        pmlibSysConfigErrReturn_t *result,
                                        uint32_t                   timeout);

/**
 * \brief This API is used to know the final state of a given module.
 *
 * \param  moduleMode  Module state in terms of sidle state.
 *                     Refer #pmhalPrcmModuleSIdleState_t for details.
 * \param  clockMode   Clock mode in terms of clock activity.
 *                     Refer #pmhalPrcmClockActivityState_t for details.
 * \param  pdMode      Power domain mode in terms of PWRSTST.
 *                     Refer #pmhalPrcmPdState_t for details.
 *
 * \return finalSt     Final state of the module as defined in
 *                     #pmlibSysConfigPowerState_t
 */
static pmlibSysConfigPowerState_t PmlibSysConfigGetFinalState(
    pmhalPrcmModuleSIdleState_t   moduleMode,
    pmhalPrcmClockActivityState_t clockMode,
    pmhalPrcmPdState_t            pdMode);

/**
 * \brief This API is used to assert or deassert any subsystem level reset of
 *        the module given.
 *
 * \param  modIdx      Module id of the interested module.
 *                     Refer #pmhalPrcmModuleId_t for details.
 * \param  resetAssert Value to indicate the module should be asserted (1) or
 *                     deasserted (0).
 * \param  timeout     Time to wait for when the reset is deasserted.
 *
 * \return status      Return value of the PMHAL reset functions.
 */
static pmErrCode_t PmlibSysConfigResetConfig(pmhalPrcmModuleId_t modIdx,
                                             uint32_t            resetAssert,
                                             uint32_t            timeout);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMLIBSysConfigSetPowerState(
    const pmlibSysConfigPowerStateParams_t *inputTable,
    uint32_t                                numConfig,
    uint32_t                                timeout,
    pmlibSysConfigErrReturn_t              *resultReturn)
{
    pmErrCode_t status   = PM_SUCCESS;
    uint32_t    modCount = 0U;
    uint32_t    logError = 0U;

    /* Check if the errors can be logged. Done only when a valid pointer
     * is passed to the API for returning the results.
     */
    if (NULL != resultReturn)
    {
        logError = 1U;
    }

    if ((NULL == inputTable) || (0U == numConfig))
    {
        status = PM_BADARGS;
    }
    else
    {
        /* Loop through the number of modules given to the API */
        for (modCount = 0U; modCount < numConfig; modCount++)
        {
            pmhalPrcmModuleId_t        currMod =
                inputTable[modCount].modId;
            pmlibSysConfigPowerState_t desiredPwrSt =
                inputTable[modCount].pwrState;
            /* Check if the input parameters are correct */
            if ((PM_SUCCESS != PMHALModuleIsIdValid(currMod)) ||
                (desiredPwrSt > PMLIB_SYS_CONFIG_MAX))
            {
                if (1U == logError)
                {
                    resultReturn[modCount].moduleId  = currMod;
                    resultReturn[modCount].failCause = PM_BADARGS;
                }
                status = (pmErrCode_t) ((uint32_t) status | (uint32_t) PM_FAIL);
            }
            else
            {
                pmlibSysConfigErrReturn_t *currResult = NULL;
                if (1U == logError)
                {
                    currResult = &resultReturn[modCount];
                }
                /* Based on which power state is requested go to the
                 * corresponding internal function.
                 */
                switch (desiredPwrSt)
                {
                    case PMLIB_SYS_CONFIG_DISABLED:
                        /* Case when the module is to be disabled */
                        status = (pmErrCode_t) ((uint32_t) status |
                                                (uint32_t)
                                                PmlibSysConfigDisable(currMod,
                                                                      currResult,
                                                                      timeout));
                        break;
                    case PMLIB_SYS_CONFIG_AUTO_CG:
                        /* Case when the module automatically goes to low
                         * power when the module is not active.
                         */
                        status = (pmErrCode_t) ((uint32_t) status |
                                                (uint32_t) PmlibSysConfigAutoCg(
                                                    currMod,
                                                    currResult,
                                                    timeout));
                        break;
                    case PMLIB_SYS_CONFIG_ALWAYS_ENABLED:
                        /* Case when the module is in its highest power
                         * configuration.
                         */
                        status = (pmErrCode_t) ((uint32_t) status |
                                                (uint32_t) PmlibSysConfigEnable(
                                                    currMod,
                                                    currResult,
                                                    timeout));
                        break;
                    default:
                        /* Invalid power state */
                        if (1U == logError)
                        {
                            currResult->moduleId  = currMod;
                            currResult->failCause = PM_BADARGS;
                        }
                        status = (pmErrCode_t) ((uint32_t) status |
                                                (uint32_t) PM_FAIL);
                        break;
                }
            }
        }
    }

    return status;
}

pmErrCode_t PMLIBSysConfigPowerStateParams_init(
    pmlibSysConfigPowerStateParams_t *inputTable,
    uint32_t                          numConfig)
{
    pmErrCode_t status   = PM_SUCCESS;
    uint32_t    modCount = 0U;
    if ((NULL == inputTable) || (0U == numConfig))
    {
        status = PM_BADARGS;
    }
    else
    {
        /* Loop through the number of modules given. The Init API would
         * fill in the details of all the modules in a sequence of module IDs
         * and initialize the initial state of the modules to DISABLED. Based
         * on what the software wants to enable the modules corresponding to
         * that can be enabled/auto clock gated.
         */
        for (modCount = 0U; modCount < numConfig; modCount++)
        {
            inputTable[modCount].modId = (pmhalPrcmModuleId_t)
                                         ((uint32_t) PMHAL_PRCM_MOD_LOWER_BOUND
                                          +
                                          modCount + 1U);
            inputTable[modCount].pwrState =
                PMLIB_SYS_CONFIG_DISABLED;
        }
    }
    return status;
}

pmErrCode_t PMLIBSysConfigGetPowerState(
    pmhalPrcmModuleId_t            moduleId,
    pmlibSysConfigPowerState_t    *currState,
    pmlibSysConfigDetailedState_t *detailedState)
{
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == currState)
    {
        status = PM_BADARGS;
    }
    else
    {
        pmhalPrcmModuleId_t           currMod = moduleId;
        pmhalPrcmClockActivityState_t clockState =
                               PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_MIN;
        pmhalPrcmCdId_t cdId = (pmhalPrcmCdId_t) PMUtilsGetCdId(currMod);
        pmhalPrcmPdId_t pdId = (pmhalPrcmPdId_t) PMUtilsGetPdId(cdId);
        pmhalPrcmModuleSIdleState_t   sIdleState;
        pmhalPrcmPdState_t pdState;
        /* For the given module first get the module state */
        status = (pmErrCode_t) PMHALModuleSIdleStatusGet(currMod, &sIdleState);

        if (PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE == status)
        {
            /* If a module does not have a valid CLKCTRL register the module
             * state is determined by the clock domain state.
             */
            sIdleState = PMHAL_PRCM_MODULE_SIDLESTATE_DETERMINED_BY_CLK_STATE;
            status     = PM_SUCCESS;
        }
        if (PM_SUCCESS == status)
        {
            /* Log the module state if the detailed state is requested. */
            if (NULL != detailedState)
            {
                detailedState->moduleMode = sIdleState;
            }
            /* Once the module state is determined, find if any clock getting
             * sourced to the module is running. If yes then the clocks are
             * determined to be on.
             */
            status = (pmErrCode_t) ((int32_t) status +
                                    PMHALCMGetModuleAllClockState(currMod,
                                                                  &clockState));
        }
        if (PM_SUCCESS == status)
        {
            if (NULL != detailedState)
            {
                detailedState->clockMode =
                    (pmhalPrcmClockActivityState_t) clockState;
            }
            /* Once the module clock status is determined the module power
             * status can be determined by looking at the PD status.
             */
            status = (pmErrCode_t) ((int32_t) status +
                                    PMHALPdmGetCurrPDStatus(pdId, &pdState));
        }

        if (PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID == status)
        {
            /* This valid for always on power domains which do not have a valid
             * power status register.
             */
            pdState = PMHAL_PRCM_PD_STATE_ON_ACTIVE;
            status  = PM_SUCCESS;
        }

        if (PM_SUCCESS == status)
        {
            if (NULL != detailedState)
            {
                detailedState->pdMode = pdState;
            }
            /* Based on the module, clock and power domain status a decision
             * tree is used to understand what is the final state of the module
             */
            *currState = PmlibSysConfigGetFinalState
                             (sIdleState, clockState, pdState);
        }
    }
    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PmlibSysConfigDisable(pmhalPrcmModuleId_t        modIdx,
                                         pmlibSysConfigErrReturn_t *result,
                                         uint32_t                   timeout)
{
    pmErrCode_t     status = PM_SUCCESS;
    pmhalPrcmCdId_t cdId   = (pmhalPrcmCdId_t) PMUtilsGetCdId(
        modIdx);
    pmhalPrcmPdId_t pdId = (pmhalPrcmPdId_t) PMUtilsGetPdId(
        cdId);
    uint32_t        numModinCd      = PMUtilsGetNumModsInCd(cdId);
    uint32_t        numClockDomInPd = PMUtilsGetNumCdsInPd(pdId);
    uint32_t        i          = 0U;
    uint32_t        j          = 0U;
    uint32_t        disableCd  = 1U;
    uint32_t        disablePd  = 1U;
    uint32_t        checkLater = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    uint32_t        moduleAlreadyDisabled = 0U;

    /* First check if the module is enabled or not. If not enabled then enable
     * the module.
     */
    status = (pmErrCode_t) PMHALModuleSIdleStatusGet(modIdx, &sIdleState);

    if (PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE == status)
    {
        status = PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED;
    }

    if (PM_SUCCESS == status)
    {
        if (PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED != sIdleState)
        {
            /* Enable the module only when the module is in IDLE or stuck in
             * TRANSITION.
             */
            status = PmlibSysConfigEnable(modIdx, result, timeout);
        }
        if (PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED == sIdleState)
        {
            /* If the module is disabled already we do not have to write to the
             * module sysconfig registers. This flag is used to check whether
             * the module sysconfig registers need to be accessed or not later
             * in the logic for powering down the module.
             */
            moduleAlreadyDisabled = 1U;
        }
        /* Unconditionally set the PD state to ON_ACTIVE */
        status = (pmErrCode_t) PMHALPdmSetPDState(pdId,
                                                  PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                                  PM_TIMEOUT_NOWAIT);
        if ((PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID == status) ||
            (PM_PDM_PDSTATE_NOT_SUPPORTED == status))
        {
            /* Given Module power domain cannot be software controlled */
            status = PM_SUCCESS;
        }
    }

    if (PM_FAIL == status)
    {
        /* Module cannot be enabled hence cannot be Disabled gated */
        status = PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED;
    }

    /* Loop through all the modules in the same clock domain as the given module
     * If the all the modules apart from the current module are in Idle or
     * disabled state, then set a flag to later disable the CD.
     */
    for (i = 0U; i < numModinCd; i++)
    {
        pmhalPrcmModuleId_t iterModId = PMUtilsGetModuleIdinCd(cdId, i);
        if (modIdx != iterModId)
        {
            status = (pmErrCode_t) PMHALModuleSIdleStatusGet(iterModId,
                                                             &sIdleState);
            /* If any one module is functional the Clock domain cannot be clock
             * gated.
             */
            if (((pmhalPrcmModuleSIdleState_t)
                 PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == sIdleState) &&
                (PM_SUCCESS == status))
            {
                disableCd = 0U;
                break;
            }
            else if (PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE == status)
            {
                status = PM_SUCCESS;
            }
            else
            {
                ; /* Misra C */
            }
        }
    }
    /* Only if the clock domain can be disabled check if the power domain can
     * be disabled.
     */
    if (1U == disableCd)
    {
        /* Loop through all the clock domains in the power domain */
        for (i = 0U; i < numClockDomInPd; i++)
        {
            pmhalPrcmCdId_t currCd = PMUtilsGetClockDomInPd(pdId, i);
            if (cdId != currCd)
            {
                pmhalPrcmCdClkTrnModes_t cdTrnMode;
                status = (pmErrCode_t) PMHALCMGetCdClockMode(currCd, &cdTrnMode);
                if (PM_SUCCESS == status)
                {
                    /* If the clock domain has been put to SW_WKUP or NO_SLEEP
                     * the software requests the clock domain to be active. In
                     * this case the power domain cannot be disabled.
                     */
                    if ((PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP == cdTrnMode) ||
                        (PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP == cdTrnMode))
                    {
                        disablePd = 0U;
                    }
                    /* If the clock domain is in HW_AUTO, we can find if the
                     * clock domain is inactive by looping through all the
                     * modules in that clock domain and check if the modules
                     * in the clock domain have all their clocks gated. If
                     * gated then the power domain can be switched off else no.
                     */
                    else if (PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO == cdTrnMode)
                    {
                        /* Check if modules have clock enabled */
                        uint32_t numModsInCd = PMUtilsGetNumModsInCd(currCd);
                        for (j = 0U; j < numModsInCd; j++)
                        {
                            pmhalPrcmModuleId_t           modInCd =
                                PMUtilsGetModuleIdinCd(currCd, j);
                            pmhalPrcmClockActivityState_t clockState =
                                PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED;
                            status = (pmErrCode_t)
                                     PMHALCMGetModuleAllClockState(modInCd,
                                                                   &clockState);
                            if ((PM_SUCCESS == status) &&
                                (PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED ==
                                 clockState))
                            {
                                disablePd = 0U;
                                break;
                            }
                        }
                    }
                    else
                    {
                        ; /* For Misra C */
                    }
                    if (0U == disablePd)
                    {
                        break;
                    }
                }
            }
        }
    }
    else
    {
        disablePd = 0U;
    }

    /* Configure standby and idle modes for the modules to Force standby and
     * force idle.
     * Set the right module system configurations - Valid only for modules
     * which have valid sysconfig registers.
     * If the module is already disabled do not access module level registers.
     * If SW accesses the registers in a module which is disabled, it will
     * receive aborts.
     */
    if (0U == moduleAlreadyDisabled)
    {
        if (PM_SUCCESS == status)
        {
            status = (pmErrCode_t) PMHALModuleStandbyModeSet(
                modIdx,
                PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                PM_TIMEOUT_NOWAIT);
            /* Case to take care of sysconfig not available */
            if ((PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE == status) ||
                (PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED == status) ||
                (PM_INPUT_MODULE_STANDBY_MODE_INVALID == status))
            {
                status = PM_SUCCESS;
            }
        }

        if (PM_SUCCESS == status)
        {
            status = (pmErrCode_t) PMHALModuleSIdleModeSet(
                modIdx,
                PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                PM_TIMEOUT_NOWAIT);
            if ((PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE == status) ||
                (PM_INPUT_MODULE_IDLE_MODE_INVALID == status))
            {
                status = PM_SUCCESS;
            }
        }
    }

    /* Should not disable static dependencies if the clock domains are not to
     * be clock gated.
     */
    if ((PM_SUCCESS == status) && (1U == disableCd))
    {
        /* Disable static dependency from the slave CD to all master CDs */
        status = (pmErrCode_t) PMHALStaticDepDisableToAllMaster(cdId, NULL);
        /* If PM_BADARGS is returned the CD is not a slave CD */
        if ((PM_BADARGS == status) ||
            (PM_SD_CLOCK_DOMAIN_DEPENDENCY_HARDWIRED == status))
        {
            status = PM_SUCCESS;
        }
    }

    /* Module disable */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALModuleModeSet(
            modIdx,
            PMHAL_PRCM_MODULE_MODE_DISABLED,
            PM_TIMEOUT_NOWAIT);
        /* Check if the module is really disabled at the end of the function */
        if (PM_SUCCESS == status)
        {
            checkLater = 1U;
        }
        /* If PMHAL_PRCM_MODULE_MODE_DISABLED mode is not supported then
         * disabling the module to be HW managed.
         */
        if (PM_INPUT_PARAM_BAD_MODULE_MODE == status)
        {
            status = (pmErrCode_t) PMHALModuleModeSet(
                modIdx,
                PMHAL_PRCM_MODULE_MODE_AUTO,
                PM_TIMEOUT_NOWAIT);
            /* Check if the module is really disabled at the end of the
             * function
             */
            if (PM_SUCCESS == status)
            {
                checkLater = 1U;
            }
        }
        if ((PM_INPUT_PARAM_BAD_MODULE_MODE == status) ||
            (PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE == status))
        {
            /* Module does not support any module modes */
            status = PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED;
        }
    }

    /* Disable Optional clocks if any */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALCMModuleDisableAllOptClock(modIdx);
        /* Not all clocks of a module are programmable */
        if ((PM_CM_CLKSEL_CTRL_NOT_APPLICABLE == status) ||
            (PM_CM_MODULE_CLKSEL_CONFIG_NOT_AVAILABLE == status))
        {
            status = PM_SUCCESS;
        }
    }
    /* Once the module has been programmed to go to low power state. Configure
     * the reset to have the modules in reset state.
     */
    if (PM_SUCCESS == status)
    {
        /* The function finds the reset for the module and applies it. */
        status = PmlibSysConfigResetConfig(modIdx, (uint32_t) 1U, timeout);
    }

    /* If CD should be disabled then put to SW_SLEEP or HW_AUTO as applicable */
    if ((PM_SUCCESS == status) && (1U == disableCd))
    {
        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            cdId,
            PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
            timeout);
        if (PM_CM_CLK_DOMAIN_TRANS_MODE_NOT_SUPPORTED == status)
        {
            status = (pmErrCode_t) PMHALCMSetCdClockMode(
                cdId,
                PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                timeout);
        }
    }

    /* Some modules with HW_AUTO configuration only go into disabled state
     * when the clock domain goes into HW_AUTO/SW_SLEEP. Do not check for
     * state if the clock domain is not programmed.
     */
    if (1U == checkLater)
    {
        pmhalPrcmModuleMStbyState_t readStandbyState =
            PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL;
        pmhalPrcmModuleSIdleState_t readState =
            PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL;
        if (1U == disableCd)
        {
            uint32_t timeToWait = timeout;
            /* Wait for the module to go to disabled. The PMHAL does not
             * check for HW_AUTO disable status.
             */
            do
            {
                PMHALModuleSIdleStatusGet(modIdx, &readState);
                timeToWait--;
            } while ((readState !=
                      PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE) &&
                     (readState != PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED) &&
                     (timeToWait != 0));
            if (timeToWait == 0U)
            {
                if ((readState !=
                     PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE) &&
                    (readState != PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED))
                {
                    status = PM_SYS_CONFIG_MODULE_NOT_GETTING_DISABLED;
                }
            }
        }
        else
        {
            PMHALModuleSIdleStatusGet(modIdx, &readState);
            if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == readState)
            {
                status = (pmErrCode_t) PMHALModuleStandbyStatusGet(
                    modIdx,
                    &
                    readStandbyState);
                if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_STANDBY == readStandbyState)
                {
                    /* Module is in standby. */
                    status = PM_SUCCESS;
                }
                else if (PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED == status)
                {
                    /* Check only Idle mode for the module */
                    /* This can clock domain or any other module dependencies */
                    status = PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES;
                }
                else
                {
                    /* This can clock domain or any other module dependencies */
                    status = PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES;
                }
            }
        }
    }

    if ((PM_SUCCESS == status) && (1U == disablePd))
    {
        /* Check if module clocks are disabled before cutting power. This
         * is done to ensure the clock domain is really disabled before
         * killing the power to the power domain.
         */
        pmhalPrcmClockActivityState_t clockState =
            PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED;
        status = (pmErrCode_t) PMHALCMGetModuleAllClockState(modIdx,
                                                             &clockState);
        if ((PM_SUCCESS == status) &&
            (PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED == clockState))
        {
            status = (pmErrCode_t) PMHALPdmSetPDState(pdId,
                                                      PMHAL_PRCM_PD_STATE_OFF,
                                                      timeout);
            if (PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID == status)
            {
                /* Given Module power domain cannot be software controlled */
                status = PM_SUCCESS;
            }
            if (PM_PDM_PDSTATE_NOT_SUPPORTED == status)
            {
                status =
                    (pmErrCode_t) PMHALPdmSetPDState(
                        pdId,
                        PMHAL_PRCM_PD_STATE_RETENTION,
                        timeout);
            }
        }
    }

    if (NULL != result)
    {
        /* Save the result of the operation */
        result->moduleId  = modIdx;
        result->failCause = status;
    }

    if (PM_SUCCESS != status)
    {
        /* The system config API always returns PM_FAIL. The real cause of fail
         * is captured in the result structure.
         */
        status = PM_FAIL;
    }

    return status;
}

static pmErrCode_t PmlibSysConfigAutoCg(pmhalPrcmModuleId_t        modIdx,
                                        pmlibSysConfigErrReturn_t *result,
                                        uint32_t                   timeout)
{
    pmErrCode_t     status = PM_SUCCESS;
    pmhalPrcmCdId_t cdId   = (pmhalPrcmCdId_t) PMUtilsGetCdId(modIdx);
    pmhalPrcmPdId_t pdId   = (pmhalPrcmPdId_t) PMUtilsGetPdId(cdId);
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;

    /* First check if the module is enabled or not. If not enabled then enable
     * the module.
     */
    status = (pmErrCode_t) PMHALModuleSIdleStatusGet(modIdx, &sIdleState);

    if (PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE == status)
    {
        status = PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG;
    }

    if (PM_SUCCESS == status)
    {
        if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL != sIdleState)
        {
            status = PmlibSysConfigEnable(modIdx, result, timeout);
        }
    }

    if (PM_FAIL == status)
    {
        /* Module cannot be enabled hence cannot be auto clock gated */
        status = PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG;
    }

    if (PM_SUCCESS == status)
    {
        /* The time out given is no wait as the hardware would
         * enter auto clock gate only in certain conditions which
         * are determined by the kind of operations the module
         * will do in the future. No need to wait here.
         */
        /* Configure CD to HW_AUTO */
        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            cdId,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);
    }

    /* Not checking for PM_CM_CLOCK_DOMAIN_CLK_STATE_CTRL_REG_INVALID as the
     * user cannot put such a module to auto CG.
     */

    /* If module is the only module in the PD and retention is supported
     * then configure the PD to retention.
     */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALPdmSetPDState(pdId,
                                                  PMHAL_PRCM_PD_STATE_RETENTION,
                                                  PM_TIMEOUT_NOWAIT);

        if (PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID == status)
        {
            /* Power Domain cannot be put to HW AUTO */
            status = PM_SUCCESS;
        }

        if (PM_PDM_PDSTATE_NOT_SUPPORTED == status)
        {
            status = (pmErrCode_t) PMHALPdmSetPDState(
                pdId,
                PMHAL_PRCM_PD_STATE_ON_INACTIVE,
                PM_TIMEOUT_NOWAIT);
        }

        if (PM_PDM_PDSTATE_NOT_SUPPORTED == status)
        {
            /* Power Domain cannot be put to any auto power state but it is
             * still okay since the clock domain has been gated.
             */
            status = PM_SUCCESS;
        }
    }

    /* Configure standby and idle modes for the modules to smart standby and
     * smart idle.
     * Set the right module system configurations - Valid only for modules
     * which have valid sys config registers.
     */

    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALModuleSIdleStatusGet(modIdx, &sIdleState);

        if ((PM_SUCCESS == status) &&
            (sIdleState == PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL))
        {
            status = (pmErrCode_t) PMHALModuleStandbyModeSet(
                modIdx,
                PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY,
                PM_TIMEOUT_NOWAIT);
            /* Case to take care of sysconfig not available */
            if ((PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE == status) ||
                (PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED == status) ||
                (PM_INPUT_MODULE_STANDBY_MODE_INVALID == status))
            {
                status = PM_SUCCESS;
            }
            if (PM_SUCCESS == status)
            {
                status = (pmErrCode_t) PMHALModuleSIdleModeSet(
                    modIdx,
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE,
                    PM_TIMEOUT_NOWAIT);
                if ((PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE == status) ||
                    (PM_INPUT_MODULE_IDLE_MODE_INVALID == status))
                {
                    status = PM_SUCCESS;
                }
            }
        }
    }

    if (PM_SUCCESS == status)
    {
        /* If the module does not support auto clock gate and is stuck in
         * transition when the clock domain is made to go to HW_AUTO. The module
         * is brought back from auto clock gate configuration.
         */
        PMHALModuleSIdleStatusGet(modIdx, &sIdleState);
        if (PMHAL_PRCM_MODULE_SIDLESTATE_INTRANSITION == sIdleState)
        {
            /* Configure CD to SW_WKUP */
            status = (pmErrCode_t) PMHALCMSetCdClockMode(
                cdId,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                PM_TIMEOUT_NOWAIT);
            status = (pmErrCode_t) PMHALPdmSetPDState(
                pdId,
                PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                PM_TIMEOUT_NOWAIT);
            status = PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG;
        }
    }

    if (NULL != result)
    {
        /* Save the result of the operation */
        result->moduleId  = modIdx;
        result->failCause = status;
    }

    if (PM_SUCCESS != status)
    {
        /* The system config API always returns PM_FAIL. The real cause of fail
         * is captured in the result structure.
         */
        status = PM_FAIL;
    }
    return status;
}

static pmErrCode_t PmlibSysConfigEnable(pmhalPrcmModuleId_t        modIdx,
                                        pmlibSysConfigErrReturn_t *result,
                                        uint32_t                   timeout)
{
    pmErrCode_t                 status = PM_SUCCESS;
    pmhalPrcmCdId_t             cdId   = (pmhalPrcmCdId_t) PMUtilsGetCdId(
        modIdx);
    pmhalPrcmPdId_t             pdId = (pmhalPrcmPdId_t) PMUtilsGetPdId(
        cdId);
    pmhalPrcmCdClkTrnModes_t    cdState   = PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP;
    pmhalPrcmModuleSIdleState_t readState =
        PMHAL_PRCM_MODULE_SIDLESTATE_INTRANSITION;
    uint32_t timeToWait = timeout;
    uint32_t checkLater = 0U;
    status = (pmErrCode_t) PMHALPdmSetPDState(pdId,
                                              PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                              PM_TIMEOUT_NOWAIT);
    /* To take care of the case where the PD cannot be programmed or does
     * not contain ON_ACTIVE as a valid mode. eg. PD_EMU.
     */
    if ((PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID == status) ||
        (PM_PDM_PDSTATE_NOT_SUPPORTED == status))
    {
        status = PM_SUCCESS;
    }
    else if (PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID == status)
    {
        /* Module does not have a configurable PD. Part of AON domain */
        status = PM_SUCCESS;
    }
    else
    {
        /* Should never hit here to solve misra error */
    }
    if (PM_SUCCESS == status)
    {
        /* Assert the reset to the subsystem to make sure the subsystem starts
         * from a clean state.
         */
        status = PmlibSysConfigResetConfig(modIdx, (uint32_t) 1U, timeout);
    }
    /* Check if CD is enabled. If not enable CD */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALCMGetCdClockMode(cdId, &cdState);
    }

    if ((PM_SUCCESS == status) &&
        (PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP != cdState))
    {
        status = (pmErrCode_t) PMHALCMSetCdClockMode(
            cdId, PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
            PM_TIMEOUT_NOWAIT);
        if (PM_CM_CLOCK_DOMAIN_CLK_STATE_CTRL_REG_INVALID == status)
        {
            /* The clock domain is not configurable */
            status = PM_SUCCESS;
        }
        /* If SW_WKUP is not supported then set the HW_AUTO */
        if (PM_CM_CLK_DOMAIN_TRANS_MODE_NOT_SUPPORTED == status)
        {
            status = (pmErrCode_t) PMHALCMSetCdClockMode(
                cdId,
                PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                PM_TIMEOUT_NOWAIT);
        }
    }

    /* Enable all optional clocks */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALCMModuleEnableAllOptClock(modIdx);
        /* Not all clocks of a module are programmable */
        if ((PM_CM_CLKSEL_CTRL_NOT_APPLICABLE == status) ||
            (PM_CM_MODULE_CLKSEL_CONFIG_NOT_AVAILABLE == status))
        {
            status = PM_SUCCESS;
        }
    }

    /* Enable Module */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALModuleModeSet(
            modIdx,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_NOWAIT);
        if (PM_SUCCESS == status)
        {
            checkLater = 1U;
        }
        /* If PMHAL_PRCM_MODULE_MODE_ENABLED mode is not supported then enabling
         * the module to be HW managed.
         */
        if (PM_INPUT_PARAM_BAD_MODULE_MODE == status)
        {
            status = (pmErrCode_t) PMHALModuleModeSet(
                modIdx,
                PMHAL_PRCM_MODULE_MODE_AUTO,
                PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS == status)
            {
                checkLater = 1U;
            }
        }

        if ((PM_INPUT_PARAM_BAD_MODULE_MODE == status) ||
            (PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE == status))
        {
            /* Module does not support any module modes */
            status = PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED;
        }
    }

    if (PM_SUCCESS == status)
    {
        /* When deassrting the reset only the subsystem reset is lifted when
         * a CPU subsystem is enabled. This is done so that the application
         * can configure the CPU subsystem like MMU/code in subsystem memory
         * before the CPU reset can be lifted and the code runs on the CPU
         * correctly.
         */
        PmlibSysConfigResetConfig(modIdx, (uint32_t) 0U, timeout);
    }
    if (1U == checkLater)
    {
        /* Wait for the module to be enabled */
        do
        {
            PMHALModuleSIdleStatusGet(modIdx, &readState);
            timeToWait--;
        } while ((readState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL) &&
                 (timeToWait != 0U));
        if (timeToWait == 0U)
        {
            if (readState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL)
            {
                status = PM_FAIL;
            }
        }
    }

    /* Set the right module system configurations - Valid only for modules
     * which have valid sysconfig registers.
     */
    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALModuleStandbyModeSet(
            modIdx,
            PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY,
            timeout);
        /* Case to take care of sysconfig not available */
        if ((PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE == status) ||
            (PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED == status) ||
            (PM_INPUT_MODULE_STANDBY_MODE_INVALID == status))
        {
            status = PM_SUCCESS;
        }
    }

    if (PM_SUCCESS == status)
    {
        status = (pmErrCode_t) PMHALModuleSIdleModeSet(
            modIdx,
            PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE,
            timeout);
        if (PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE == status)
        {
            status = PM_SUCCESS;
        }
        else if (PM_INPUT_MODULE_IDLE_MODE_INVALID == status)
        {
            status = (pmErrCode_t) PMHALModuleSIdleModeSet(
                modIdx,
                PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE,
                timeout);
        }
        else
        {
            ; /* Nothing to do here */
        }
    }

    if (NULL != result)
    {
        /* Save the result of the operation */
        result->moduleId  = modIdx;
        result->failCause = status;
    }

    if (PM_SUCCESS != status)
    {
        /* The system config API always returns PM_FAIL. The real cause of fail
         * is captured in the result structure.
         */
        status = PM_FAIL;
    }

    return status;
}

static pmlibSysConfigPowerState_t PmlibSysConfigGetFinalState(
    pmhalPrcmModuleSIdleState_t   moduleMode,
    pmhalPrcmClockActivityState_t clockMode,
    pmhalPrcmPdState_t            pdMode)
{
    pmlibSysConfigPowerState_t finalSt = PMLIB_SYS_CONFIG_INVALID;
    /* CASE 1: If the power state is off and the clock state is anything
     *         but off the final state is invalid.
     */
    if (pdMode == PMHAL_PRCM_PD_STATE_OFF)
    {
        if (clockMode == PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED)
        {
            finalSt = PMLIB_SYS_CONFIG_DISABLED;
        }
    }
    /* CASE 2: If the power state is in retention/on-inactive and the clock
     *         state is anything but off then the final state is invalid. If
     *         the clock is off based on whether the sidle status is idle or
     *         disabled the module is auto clock gated or disabled.
     */
    else if ((pdMode == PMHAL_PRCM_PD_STATE_RETENTION) ||
             (pdMode == PMHAL_PRCM_PD_STATE_ON_INACTIVE))
    {
        if (clockMode == PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED)
        {
            if ((moduleMode == PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE) ||
                (moduleMode ==
                 PMHAL_PRCM_MODULE_SIDLESTATE_DETERMINED_BY_CLK_STATE))
            {
                finalSt = PMLIB_SYS_CONFIG_AUTO_CG;
            }
            else if (moduleMode == PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED)
            {
                finalSt = PMLIB_SYS_CONFIG_DISABLED;
            }
            else
            {
                finalSt = PMLIB_SYS_CONFIG_INVALID;
            }
        }
    }
    /* CASE 3: If the module is ON and the module state is idle/disabled the
     *         final state is enabled/disabled. If the module is functional it
     *         is always enabled.
     */
    else
    {
        if (moduleMode == PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE)
        {
            finalSt = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
        }
        else if (moduleMode == PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED)
        {
            finalSt = PMLIB_SYS_CONFIG_DISABLED;
        }
        else if (moduleMode == PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL)
        {
            if (clockMode == PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED)
            {
                finalSt = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
            }
        }
        else if (moduleMode ==
                 PMHAL_PRCM_MODULE_SIDLESTATE_DETERMINED_BY_CLK_STATE)
        {
            if (clockMode == PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED)
            {
                finalSt = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
            }
            else
            {
                finalSt = PMLIB_SYS_CONFIG_DISABLED;
            }
        }
        else
        {
            finalSt = PMLIB_SYS_CONFIG_INVALID;
        }
    }
    return finalSt;
}

static pmErrCode_t PmlibSysConfigResetConfig(pmhalPrcmModuleId_t modIdx,
                                             uint32_t            resetAssert,
                                             uint32_t            timeout)
{
    pmhalPrcmCdId_t         cdId = (pmhalPrcmCdId_t) PMUtilsGetCdId(modIdx);
    pmhalPrcmPdId_t         pdId = (pmhalPrcmPdId_t) PMUtilsGetPdId(cdId);
    pmhalPrcmResetGroupId_t cpuResetId[PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM];
    uint32_t numResetsReturned = 0U;
    uint32_t count     = 0U;
    pmErrCode_t status = PM_SUCCESS;
    pmhalPrcmResetGroupId_t resetId = PMHAL_PRCM_RG_COUNT;
    /* Find the reset domain ID for the module */
    resetId = PMHALPdmGetModuleResetId(pdId, modIdx);

    resetAssert = resetAssert & 0x1U;

    if (0U == resetAssert)
    {
        /* Put the module out of reset. Note here only the subsystem reset is
         * lifted to ensure that if the module is a CPU subsystem the subsystem
         * can be initialized (like MMU, copying code to subsystem L1/L2
         * memories before the CPU reset can be lifted.
         */
        status = (pmErrCode_t) PMHALResetRelease(resetId, timeout);
        if (PM_INPUT_PARAM_BAD_RESET_ID == status)
        {
            /* The module may not support any resets hence this is a valid
             * scenario.
             */
            status = PM_SUCCESS;
        }
    }
    else
    {
        /* CPU subsystems always have a subsystem reset along with
         * local CPU resets. Find if the module has any CPU resets
         * associated with it. "numResetsReturned" will be 0 if the
         * subsystem has no resets.
         */
        PMHALPdmGetCpuResetId(pdId, modIdx, cpuResetId, &numResetsReturned);
        for (count = 0U; count < numResetsReturned; count++)
        {
            /* The CPU resets are never invalid here as if they are invalid
             * the value of "numResetsReturned" would reflect appropriately
             */
            status = (pmErrCode_t) PMHALResetAssert(cpuResetId[count]);
        }
        /* Put the module in reset. Note here both the subsystem and the CPU
         * resets are asserted to ensure that the module starts from a clean
         * state.
         */
        status = (pmErrCode_t) PMHALResetAssert(resetId);
        if (PM_INPUT_PARAM_BAD_RESET_ID == status)
        {
            /* The module may not support any resets hence this is a valid
             * scenario.
             */
            status = PM_SUCCESS;
        }
    }
    return status;
}

