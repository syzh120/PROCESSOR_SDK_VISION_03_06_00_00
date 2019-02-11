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
 *  \file     pmhal_mm.c
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of PRCM module mode.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "stdlib.h"
#include <ti/csl/hw_types.h>
#include "pmhal_prcm.h"
#include "hw_pmhal_data.h"
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_mm.h"

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
 * \brief This API verifies if the Module is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 * \param modMode           Module mode which is to be set
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsModuleModeValid(
    pmhalPrcmModuleId_t          moduleId,
    pmhalPrcmModuleSModuleMode_t modMode);

/**
 * \brief This API verifies if the Module StandbyMode is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsStandbyModeValid(pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API verifies if the Module SysConfig is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsModuleSysConfigValid(
    pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API verifies if the Module ClkCtrlOffset is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsModuleClkCtrlOffsetValid(
    pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API verifies if the Module ClkActivity is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 * \param idx               Module mode index
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsModuleClkActivityValid(
    pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API gets the standby state of the given module.
 *
 * \param   modId           Unique ID of the module ( GET_MOD_ID is taken care)
 * \param   standbyState    IdleState of module.
 *                          Refer enum #pmhalPrcmModuleMStbyState_t for values
 *
 * \retval None
 */
static void PmhalModuleStandbyStatusGetInternal(
    pmhalPrcmModuleId_t modId,
    pmhalPrcmModuleMStbyState_t *
    standbyState);

/**
 * \brief This API gets the sIdle state of the given module.
 *
 * \param   modId           Unique ID of the module ( GET_MOD_ID is taken care)
 * \param   sIdleState      IdleState of module.
 *                          Refer enum #pmhalPrcmModuleSIdleState_t for values
 *
 * \retval None
 */
static void PmhalModuleSIdleStatusGetInternal(
    pmhalPrcmModuleId_t modId,
    pmhalPrcmModuleSIdleState_t *
    sIdleState);

/**
 * \brief This API verifies if the Idle Mode is supported by module.
 *
 * \param   sysConfElemId   SysConfig element Id
 * \param   sIdleState      IdleState of module.
 *                          Refer enum #pmhalPrcmModuleSIdleState_t for values
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsSIdleModeSupported(
    pmhalPrcmSysConfigModuleId_t sysConfElemId,
    pmhalPrcmModuleSIdleMode_t   sIdleMode);

/**
 * \brief This API verifies if the standBy mode is supported by module.
 *
 * \param   sysConfElemId   SysConfig element Id
 * \param   stbyMode        StandByState of module.
 *                          Refer enum #pmhalPrcmModuleMStbyMode_t for values
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsStandbyModeSupported(
    pmhalPrcmSysConfigModuleId_t sysConfElemId,
    pmhalPrcmModuleMStbyMode_t   stbyMode);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMHALModuleStandbyModeSet(pmhalPrcmModuleId_t        moduleId,
                                  pmhalPrcmModuleMStbyMode_t stbyMode,
                                  uint32_t                   timeOut)
{
    pmErrCode_t                  retVal;
    pmhalPrcmModuleId_t          modId;
    pmhalPrcmSysConfigModuleId_t sysConfElemId = PMHAL_PRCM_SYSCFG_LOWER_BOUND;
    uint32_t timeToWait = timeOut;
    pmhalPrcmModuleMStbyState_t  readState;
    uint32_t mask;

    retVal = PMHALModuleIsIdValid(moduleId);

    /* First check if the module provided is valid. If valid go ahead and check
     * if the module has a valid sysconfig register to which the standby mode
     * can be programmed.
     */
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleSysConfigValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            /* Check if the standby mode is valid or not */
            retVal = PmhalIsStandbyModeValid(moduleId);
            if (PM_SUCCESS == retVal)
            {
                modId = PMUtilsGetModuleId(moduleId);
                if (modId <
                    (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                {
                    /* Since few modules support sysconfig a separate list of
                     * sysconfig enabled modules is maintained for which each
                     * module has an index which helps read the register
                     * addresses for sysconfig.
                     */
                    sysConfElemId =
                        (pmhalPrcmSysConfigModuleId_t) pmhalModuleElems[modId].
                        pmhalPrcmSysConfigModId;
                }
                if ((sysConfElemId > PMHAL_PRCM_SYSCFG_LOWER_BOUND)
                    && (sysConfElemId < PMHAL_PRCM_SYSCFG_COUNT))
                {
                    /* Check if the standby mode is valid for the given module.
                     * Not all modules support all the standby modes available
                     */
                    retVal = PmhalIsStandbyModeSupported(sysConfElemId,
                                                         stbyMode);
                    if (PM_SUCCESS == retVal)
                    {
                        /* There is an exception of MLB_SS where if the
                         * value programmed to the sysconfig is opposite of
                         * all the other modules.
                         */
                        #ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
                        if (moduleId == PMHAL_PRCM_MOD_MLB_SS)
                        {
                            stbyMode = (pmhalPrcmModuleMStbyMode_t)
                                       ((~(uint32_t) stbyMode) & 0x1U);
                        }
                        #endif
                        mask = (uint32_t) ((uint32_t) 0x3U <<
                                           (uint32_t) pmhalSysConfigElems[
                                               sysConfElemId].
                                           standbymodeShift);
                        HW_WR_FIELD32_RAW(pmhalSysConfigElems[sysConfElemId].
                                          sysConfigRegAddr,
                                          mask,
                                          pmhalSysConfigElems[sysConfElemId].
                                          standbymodeShift,
                                          stbyMode);

                        /* For Smart Standby and Smart Standby wakeup we do not
                         * check for the status as it is hardware controlled
                         */
                        if (stbyMode >=
                            PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY)
                        {
                            timeToWait = PM_TIMEOUT_NOWAIT;
                        }
                        /* Once the standby mode is programmed based on the time
                         * out the function checks if the given module reached
                         * the desired power state.
                         * For NO_STANDBY the expectation is FUNCTIONAL mode.
                         * For FORCED_STANDBY the expectation is STANDBY mode.
                         * For SMART_STANDBY or SMART_STANDBY_WITH_WAKEUP the
                         * function does not wait as the mode can lead to
                         * functional or standby state based on the module
                         * operation.
                         */
                        if (PM_TIMEOUT_NOWAIT != timeToWait)
                        {
                            pmhalPrcmModuleMStbyState_t checkState;
                            if (PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY ==
                                stbyMode)
                            {
                                checkState =
                                    PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL;
                            }
                            else
                            {
                                checkState =
                                    PMHAL_PRCM_MODULE_MSTANDBYSTATE_STANDBY;
                            }

                            if (PM_TIMEOUT_INFINITE != timeOut)
                            {
                                do
                                {
                                    PmhalModuleStandbyStatusGetInternal(
                                        modId, &readState);
                                    timeToWait--;
                                } while ((readState != checkState)
                                         && (timeToWait != 0));
                                if (timeToWait == 0U)
                                {
                                    if (readState != checkState)
                                    {
                                        retVal = PM_FAIL;
                                    }
                                }
                            }
                            else
                            {
                                do
                                {
                                    PmhalModuleStandbyStatusGetInternal(
                                        modId,
                                        &
                                        readState);
                                } while (readState != checkState);
                            }
                        }
                    }
                }
                else
                {
                    retVal = PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE;
                }
            }
        }
    }
    return ((int32_t) retVal);
}

int32_t PMHALModuleStandbyStatusGet(pmhalPrcmModuleId_t          moduleId,
                                    pmhalPrcmModuleMStbyState_t *standbyState)
{
    pmErrCode_t         retVal;
    pmhalPrcmModuleId_t modId;

    if (NULL == standbyState)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsStandbyModeValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PMHALModuleIsIdValid(moduleId);
            if (PM_SUCCESS == retVal)
            {
                retVal = PmhalIsModuleClkCtrlOffsetValid(moduleId);
                /* This function reads the CLKCTRL : STBYST field to
                 * return the status of the module.
                 */
                if (PM_SUCCESS == retVal)
                {
                    modId = PMUtilsGetModuleId(moduleId);
                    if (modId <
                        (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                    {
                        PmhalModuleStandbyStatusGetInternal(modId,
                                                            standbyState);
                    }
                }
            }
        }
    }
    return ((int32_t) retVal);
}

int32_t PMHALModuleSIdleModeSet(pmhalPrcmModuleId_t        moduleId,
                                pmhalPrcmModuleSIdleMode_t sIdleMode,
                                uint32_t                   timeOut)
{
    pmErrCode_t                  retVal = PM_SUCCESS;
    pmhalPrcmModuleId_t          modId;
    pmhalPrcmSysConfigModuleId_t sysConfElemId = PMHAL_PRCM_SYSCFG_LOWER_BOUND;
    uint32_t timeToWait = timeOut;
    pmhalPrcmModuleSIdleState_t  readState;
    /* First check if the module provided is valid. If valid go ahead and check
     * if the module has a valid sysconfig register to which the idle mode
     * can be programmed.
     */
    retVal = PMHALModuleIsIdValid(moduleId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleSysConfigValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            modId = PMUtilsGetModuleId(moduleId);
            if (modId <
                (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
            {
                /* Since few modules support sysconfig a separate list of
                 * sysconfig enabled modules is maintained for which each
                 * module has an index which helps read the register
                 * addresses for sysconfig.
                 */
                sysConfElemId =
                    (pmhalPrcmSysConfigModuleId_t) pmhalModuleElems[modId].
                    pmhalPrcmSysConfigModId;
            }

            if ((sysConfElemId > PMHAL_PRCM_SYSCFG_LOWER_BOUND)
                && (sysConfElemId < PMHAL_PRCM_SYSCFG_COUNT))
            {
                /* Check if the idle mode is valid for the given module.
                 * Not all modules support all the idle modes available
                 */
                retVal = PmhalIsSIdleModeSupported(sysConfElemId, sIdleMode);
                if (PM_SUCCESS == retVal)
                {
                    HW_WR_FIELD32_RAW(
                        (uint32_t) pmhalSysConfigElems[sysConfElemId].
                        sysConfigRegAddr,
                        (uint32_t) SYSCONFIG_IDLEMODE_MASK,
                        (uint32_t) pmhalSysConfigElems[sysConfElemId].
                        idleModeShift,
                        (uint32_t) sIdleMode);
                    /* If the SIdle mode is Smart Idle or Smart Idle with wakeup
                     * the hardware controls the idle behaviour.
                     */
                    if (sIdleMode >= PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE)
                    {
                        timeToWait = PM_TIMEOUT_NOWAIT;
                    }
                    /* Once the idle mode is programmed based on the time
                     * out the function checks if the given module reached
                     * the desired power state.
                     * For NO_IDLE the expectation is FUNCTIONAL mode.
                     * For FORCED_IDLE the expectation is IDLE mode.
                     * For SMART_IDLE or SMART_IDLE_WITH_WAKEUP the
                     * function does not wait as the mode can lead to
                     * functional or idle state based on the module
                     * operation.
                     */
                    if (PM_TIMEOUT_NOWAIT != timeToWait)
                    {
                        pmhalPrcmModuleSIdleState_t checkState;

                        if (sIdleMode == PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE)
                        {
                            checkState =
                                PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE;
                        }
                        else
                        {
                            checkState =
                                PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL;
                        }

                        if (PM_TIMEOUT_INFINITE != timeOut)
                        {
                            do
                            {
                                PmhalModuleSIdleStatusGetInternal(modId,
                                                                  &readState);
                                timeToWait--;
                                /* This is a special case when the module state
                                 * becomes disabled when the check is for
                                 * idle. The check is changed to check for
                                 * disabled as the module can also go to the
                                 * disabled state when the module is force idled
                                 */
                                if ((PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED ==
                                     readState) &&
                                    (
                                        PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE
                                        == checkState))
                                {
                                    checkState =
                                        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
                                }
                            } while ((readState != checkState) &&
                                     (timeToWait != 0));
                            /* If after timeout the module has still not gone to
                             * the desired power state then the function returns
                             * fail.
                             */
                            if (timeToWait == 0U)
                            {
                                if (readState != checkState)
                                {
                                    retVal = PM_FAIL;
                                }
                            }
                        }
                        else
                        {
                            do
                            {
                                PmhalModuleSIdleStatusGetInternal(modId,
                                                                  &readState);
                                /* This is a special case when the module state
                                 * becomes disabled when the check is for
                                 * idle. The check is changed to check for
                                 * disabled as the module can also go to the
                                 * disabled state when the module is force idled
                                 */
                                if ((PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED ==
                                     readState) &&
                                    (
                                        PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE
                                        == checkState))
                                {
                                    checkState =
                                        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
                                }
                            } while (readState != checkState);
                        }
                    }
                }
            }
            else
            {
                retVal = PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE;
            }
        }
    }
    return ((int32_t) retVal);
}

int32_t PMHALModuleSIdleStatusGet(pmhalPrcmModuleId_t          moduleId,
                                  pmhalPrcmModuleSIdleState_t *sIdleState)
{
    pmErrCode_t         retVal = PM_SUCCESS;
    pmhalPrcmModuleId_t modId;

    if (NULL == sIdleState)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PMHALModuleIsIdValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PmhalIsModuleClkCtrlOffsetValid(moduleId);
            if (PM_SUCCESS == retVal)
            {
                /* This function reads the CLKCTRL : IDLEST field to
                 * return the status of the module.
                 */
                modId = PMUtilsGetModuleId(moduleId);
                if (modId <
                    (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                {
                    if (PMHAL_MODULEMODE_NOTAPPLICABLE !=
                        pmhalModuleElems[modId].moduleMode)
                    {
                        PmhalModuleSIdleStatusGetInternal(modId, sIdleState);
                    }
                    else
                    {
                        retVal = PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE;
                    }
                }
            }
        }
    }
    return ((int32_t) retVal);
}

int32_t PMHALModuleSClkActivitySet(pmhalPrcmModuleId_t           moduleId,
                                   pmhalPrcmModuleSClkActivity_t sClkActivity,
                                   uint32_t                      timeOut)
{
    pmErrCode_t                   retVal = PM_SUCCESS;
    pmhalPrcmModuleId_t           modId;
    uint32_t timeToWait = timeOut;
    pmhalPrcmSysConfigModuleId_t  sysConfElemId = PMHAL_PRCM_SYSCFG_LOWER_BOUND;
    pmhalPrcmModuleSClkActivity_t readClkActivity;

    retVal = PMHALModuleIsIdValid(moduleId);
    if (PM_SUCCESS == retVal)
    {
        /* Not all modules have a valid CLOCKACTIVITY field in their sysconfig
         * register. Check if the module supports CLOCKACTIVITY.
         */
        retVal = PmhalIsModuleClkActivityValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            modId = PMUtilsGetModuleId(moduleId);
            if (modId <
                (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
            {
                /* Since few modules support sysconfig a separate list of
                 * sysconfig enabled modules is maintained for which each
                 * module has an index which helps read the register
                 * addresses for sysconfig.
                 */
                sysConfElemId =
                    (pmhalPrcmSysConfigModuleId_t) pmhalModuleElems[modId].
                    pmhalPrcmSysConfigModId;
            }

            if ((sysConfElemId > PMHAL_PRCM_SYSCFG_LOWER_BOUND)
                && (sysConfElemId < PMHAL_PRCM_SYSCFG_COUNT))
            {
                HW_WR_FIELD32(
                    pmhalSysConfigElems[sysConfElemId].sysConfigRegAddr,
                    SYSCONFIG_CLOCKACTIVITY,
                    sClkActivity);
                /* Based on the clock activity set check if the right clock
                 * activity is programmed in the device.
                 */
                if (PM_TIMEOUT_NOWAIT != timeOut)
                {
                    if (PM_TIMEOUT_INFINITE != timeOut)
                    {
                        do
                        {
                            readClkActivity =
                                (pmhalPrcmModuleSClkActivity_t) HW_RD_FIELD32(
                                    pmhalSysConfigElems[sysConfElemId].
                                    sysConfigRegAddr,
                                    SYSCONFIG_CLOCKACTIVITY);
                            timeToWait--;
                        } while ((readClkActivity != sClkActivity) &&
                                 (timeToWait != 0U));
                        if (timeToWait == 0U)
                        {
                            if (readClkActivity != sClkActivity)
                            {
                                retVal = PM_FAIL;
                            }
                        }
                    }
                    else
                    {
                        do
                        {
                            readClkActivity =
                                (pmhalPrcmModuleSClkActivity_t) HW_RD_FIELD32(
                                    pmhalSysConfigElems[sysConfElemId].
                                    sysConfigRegAddr,
                                    SYSCONFIG_CLOCKACTIVITY);
                        } while (readClkActivity != sClkActivity);
                    }
                }
            }
            else
            {
                retVal = PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE;
            }
        }
    }
    return ((int32_t) retVal);
}

int32_t PMHALModuleSClkActivityGet(pmhalPrcmModuleId_t            moduleId,
                                   pmhalPrcmModuleSClkActivity_t *sClkActivity)
{
    pmErrCode_t                  retVal = PM_SUCCESS;
    pmhalPrcmModuleId_t          modId;
    pmhalPrcmSysConfigModuleId_t sysConfElemId = PMHAL_PRCM_SYSCFG_LOWER_BOUND;

    if (NULL != sClkActivity)
    {
        retVal = PMHALModuleIsIdValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            /* Not all modules have a valid CLOCKACTIVITY field in their
             * sysconfig register. Check if the module supports CLOCKACTIVITY.
             */
            retVal = PmhalIsModuleClkActivityValid(moduleId);
            if (PM_SUCCESS == retVal)
            {
                modId = PMUtilsGetModuleId(moduleId);
                if (modId <
                    (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                {
                    /* Since few modules support sysconfig a separate list of
                     * sysconfig enabled modules is maintained for which each
                     * module has an index which helps read the register
                     * addresses for sysconfig.
                     */
                    sysConfElemId =
                        (pmhalPrcmSysConfigModuleId_t) pmhalModuleElems[modId].
                        pmhalPrcmSysConfigModId;
                }
                if ((sysConfElemId > PMHAL_PRCM_SYSCFG_LOWER_BOUND) &&
                    (sysConfElemId < PMHAL_PRCM_SYSCFG_COUNT))
                {
                    *sClkActivity =
                        (pmhalPrcmModuleSClkActivity_t) HW_RD_FIELD32(
                            pmhalSysConfigElems[sysConfElemId].sysConfigRegAddr,
                            SYSCONFIG_CLOCKACTIVITY);
                }
                else
                {
                    retVal = PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE;
                }
            }
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return ((int32_t) retVal);
}

int32_t PMHALModuleModeSet(pmhalPrcmModuleId_t          moduleId,
                           pmhalPrcmModuleSModuleMode_t modMode,
                           uint32_t                     timeOut)
{
    pmErrCode_t                 retVal = PM_SUCCESS;
    pmhalPrcmModuleId_t         modId;
    uint32_t timeToWait = timeOut;
    pmhalPrcmModuleSIdleState_t readState;
    pmhalPrcmModuleSIdleState_t checkMode =
        PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL;

    retVal = PMHALModuleIsIdValid(moduleId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleClkCtrlOffsetValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PmhalIsModuleModeValid(moduleId, modMode);
            if (PM_SUCCESS == retVal)
            {
                modId = PMUtilsGetModuleId(moduleId);
                /* Configure the CLKCTRL:MODULEMODE to the desired module mode
                 */
                if (modId <
                    (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                {
                    HW_WR_FIELD32(pmhalModuleElems[modId].clkCtrlRegAddr,
                                  PMHAL_MODULE_MODE,
                                  modMode);
                }
                if (modMode == PMHAL_PRCM_MODULE_MODE_ENABLED)
                {
                    checkMode = PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL;
                    /* Checking for Functional state when the module is
                     * enabled. */
                }
                else if (modMode == PMHAL_PRCM_MODULE_MODE_DISABLED)
                {
                    checkMode = PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
                    /* Checking for disabled state when the module is disabled.
                     */
                }
                else if (modMode == PMHAL_PRCM_MODULE_MODE_AUTO)
                {
                    timeOut = PM_TIMEOUT_NOWAIT;
                    /* When the module mode is auto do not wait for power
                     * transition as the module can go to enabled or disabled
                     * state.
                     */
                }
                else
                {
                    /* Should never enter here */
                    ; /* for Misra-C Checker */
                }
                /* Once the module mode is set the function waits for the
                 * module to reach its desired power state based on the time
                 * out provided.
                 */
                if (PM_TIMEOUT_NOWAIT != timeOut)
                {
                    if (PM_TIMEOUT_INFINITE != timeOut)
                    {
                        do
                        {
                            PmhalModuleSIdleStatusGetInternal(modId,
                                                              &readState);
                            timeToWait--;
                            /* To take care of corner case when the
                             * interface is idled on disabling module Mode.
                             */
                            if ((modMode ==
                                 PMHAL_PRCM_MODULE_MODE_DISABLED) &&
                                (readState ==
                                 PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE))
                            {
                                checkMode =
                                    PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE;
                            }
                        } while ((readState != checkMode) && (timeToWait != 0));
                        if (timeToWait == 0U)
                        {
                            if (readState != checkMode)
                            {
                                retVal = PM_FAIL;
                            }
                        }
                    }
                    else
                    {
                        do
                        {
                            PmhalModuleSIdleStatusGetInternal(modId, &readState);
                            /* To take care of corner case when the interface is
                             * idled on disabling module Mode.
                             */
                            if ((modMode == PMHAL_PRCM_MODULE_MODE_DISABLED) &&
                                (readState ==
                                 PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE))
                            {
                                checkMode =
                                    PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE;
                            }
                        } while (readState != checkMode);
                    }
                }
            }
        }
    }
    return ((int32_t) retVal);
}

pmErrCode_t PMHALModuleIsIdValid(pmhalPrcmModuleId_t moduleId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if ((moduleId < (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)) ||
        (moduleId > (PMHAL_PRCM_MOD_COUNT - 1U)))
    {
        retVal = PM_INPUT_PARAM_BAD_MODULE_ID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static pmErrCode_t PmhalIsModuleSysConfigValid(
    pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t         retVal;
    pmhalPrcmModuleId_t modId;

    modId = PMUtilsGetModuleId(moduleId);
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        if (PMHAL_PRCM_SYSCFG_NOTAPPLICABLE ==
            pmhalModuleElems[modId].pmhalPrcmSysConfigModId)
        {
            retVal = PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE;
        }
        else
        {
            retVal = PM_SUCCESS;
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsModuleClkCtrlOffsetValid(
    pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t         retVal;
    pmhalPrcmModuleId_t modId;

    modId = PMUtilsGetModuleId(moduleId);
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        if (PMHAL_INVALID_REGADDR == pmhalModuleElems[modId].clkCtrlRegAddr)
        {
            retVal = PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE;
        }
        else
        {
            retVal = PM_SUCCESS;
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsModuleClkActivityValid(
    pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t                  retVal;
    pmhalPrcmModuleId_t          modId;
    pmhalPrcmSysConfigModuleId_t sysConfElemId = PMHAL_PRCM_SYSCFG_LOWER_BOUND;

    modId = PMUtilsGetModuleId(moduleId);
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        sysConfElemId =
            (pmhalPrcmSysConfigModuleId_t) pmhalModuleElems[modId].
            pmhalPrcmSysConfigModId;
    }

    if ((sysConfElemId > PMHAL_PRCM_SYSCFG_LOWER_BOUND)
        && (sysConfElemId < PMHAL_PRCM_SYSCFG_COUNT))
    {
        if (FALSE == pmhalSysConfigElems[sysConfElemId].
            isSClockActivityPresent)
        {
            retVal = PM_MM_MODULE_SYSCONFIG_CLKACTIVITY_NOT_PRESENT;
        }
        else
        {
            retVal = PM_SUCCESS;
        }
    }
    else
    {
        retVal = PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE;
    }
    return retVal;
}

static pmErrCode_t PmhalIsStandbyModeValid(pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t         retVal;
    pmhalPrcmModuleId_t modId;

    modId = PMUtilsGetModuleId(moduleId);
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        if (0U != pmhalModuleElems[modId].isStandbySuported)
        {
            retVal = PM_SUCCESS;
        }
        else
        {
            retVal = PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED;
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsModuleModeValid(
    pmhalPrcmModuleId_t          moduleId,
    pmhalPrcmModuleSModuleMode_t modMode)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t         retVal;
    pmhalPrcmModuleId_t modId;

    modId = PMUtilsGetModuleId(moduleId);
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        /* Module modes which are valid for a given module are encoded
         * as a one hot encoding. Based on the given module mode the bit
         * position is checked to see if the module mode is supported.
         */
        if (1U == ((pmhalModuleElems[modId].moduleMode >> modMode) & 1U))
        {
            retVal = PM_SUCCESS;
        }
        else
        {
            retVal = PM_INPUT_PARAM_BAD_MODULE_MODE;
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static void PmhalModuleStandbyStatusGetInternal(
    pmhalPrcmModuleId_t modId,
    pmhalPrcmModuleMStbyState_t *
    standbyState)
{
    *standbyState =
        (pmhalPrcmModuleMStbyState_t) HW_RD_FIELD32(
            pmhalModuleElems[modId].clkCtrlRegAddr,
            PMHAL_CLKCTRL_STBYST);
}

static void PmhalModuleSIdleStatusGetInternal(
    pmhalPrcmModuleId_t modId,
    pmhalPrcmModuleSIdleState_t *
    sIdleState)
{
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        *sIdleState = (pmhalPrcmModuleSIdleState_t) HW_RD_FIELD32(
            pmhalModuleElems[modId].clkCtrlRegAddr,
            PMHAL_CLKCTRL_IDLEST);
    }
    else
    {
        *sIdleState = PMHAL_PRCM_MODULE_SIDLESTATE_UNDEFINED;
    }
}

static pmErrCode_t PmhalIsSIdleModeSupported(
    pmhalPrcmSysConfigModuleId_t sysConfElemId,
    pmhalPrcmModuleSIdleMode_t   sIdleMode)
{
    pmErrCode_t retVal;
    /* SIdle modes which are valid for a given module are encoded
     * as a one hot encoding. Based on the given module mode the bit
     * position is checked to see if the SIdle mode is supported.
     */
    if (1U == ((pmhalSysConfigElems[sysConfElemId].sidleMode >> sIdleMode)
               & 1U))
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_INPUT_MODULE_IDLE_MODE_INVALID;
    }
    return retVal;
}

static pmErrCode_t PmhalIsStandbyModeSupported(
    pmhalPrcmSysConfigModuleId_t sysConfElemId,
    pmhalPrcmModuleMStbyMode_t   stbyMode)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    /* Standby modes which are valid for a given module are encoded
     * as a one hot encoding. Based on the given module mode the bit
     * position is checked to see if the Standby mode is supported.
     */
    if (1U == ((pmhalSysConfigElems[sysConfElemId].standbyMode >> stbyMode)
               & 1U))
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_INPUT_MODULE_STANDBY_MODE_INVALID;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

