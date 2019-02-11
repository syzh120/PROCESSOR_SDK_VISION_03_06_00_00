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
 *   \ingroup PM_HAL PM HAL API
 *   \defgroup MODULE_MODE Module Configuration
 *
 *   The Module Mode API is a component of Power Management (PM)
 *   software which provides access to the PRCM HAL to enable/disable
 *   the modules and provides APIs to program the module level clock Management.
 *
 * @{
 */

/**
 *  \file  pmhal_mm.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of PRCM module mode.
 *            This also contains some related macros.
 */

#ifndef PMHAL_MM_H_
#define PMHAL_MM_H_

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

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief This API sets the module Standby Mode.
 *
 * \param   moduleId            Unique ID of the module to be enabled
 * \param   stbyMode            Module Mode to be set.
 *                              Refer enum #pmhalPrcmModuleMStbyMode_t for
 *                              values.
 * \param   timeOut             Wait time duration can be set to any uint32 or
 *          - #PM_TIMEOUT_INFINITE Waits till the Api Succeed
 *          - #PM_TIMEOUT_NOWAIT   Doesn't wait for api success.
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *          - #PM_SUCCESS        Indicates the operation is success
 *          - #PM_FAIL           Indicates the module is not enabled (timeout)
 *          - #PM_BADARGS       Invalid module id
 */
int32_t PMHALModuleStandbyModeSet(pmhalPrcmModuleId_t        moduleId,
                                  pmhalPrcmModuleMStbyMode_t stbyMode,
                                  uint32_t                   timeOut);

/**
 * \brief This API gets the module Standby State.
 *
 * \param   moduleId          Unique ID of the module to be enabled
 * \param   standbyState      Standby status of module.
 *                            Refer enum #pmhalPrcmModuleMStbyState_t for
 *                            values.
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *         - #PM_SUCCESS        Indicates the operation is success
 *         - #PM_FAIL           Indicates the module is not enabled (timeout)
 *         - #PM_BADARGS       Invalid module id
 */
int32_t PMHALModuleStandbyStatusGet(pmhalPrcmModuleId_t          moduleId,
                                    pmhalPrcmModuleMStbyState_t *standbyState);

/**
 * \brief This API sets the module sIdleMode State.
 *
 * \param   moduleId            Unique ID of the module to be enabled
 * \param   sIdleMode           IdleState to be set for the module.
 *                              Refer enum #pmhalPrcmModuleSIdleMode_t for
 *                              values.
 * \param   timeOut             Wait time duration can be set to any uint32 or
 *         - #PM_TIMEOUT_INFINITE Waits till the Api Succeed
 *         - #PM_TIMEOUT_NOWAIT   Doesn't wait for api success.
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *         - #PM_SUCCESS        Indicates the operation is success
 *         - #PM_FAIL           Indicates the module is not enabled (timeout)
 *         - #PM_BADARGS       Invalid module id
 */
int32_t PMHALModuleSIdleModeSet(pmhalPrcmModuleId_t        moduleId,
                                pmhalPrcmModuleSIdleMode_t sIdleMode,
                                uint32_t                   timeOut);

/**
 * \brief This API gets the module sIdle State.
 *
 * \param   moduleId          Unique ID of the module to be enabled
 * \param   sIdleState        IdleState of module.
 *                            Refer enum #pmhalPrcmModuleSIdleState_t for values
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *         - #PM_SUCCESS        Indicates the operation is success
 *         - #PM_FAIL           Indicates the module is not enabled (timeout)
 *         - #PM_BADARGS       Invalid module id
 */
int32_t PMHALModuleSIdleStatusGet(pmhalPrcmModuleId_t          moduleId,
                                  pmhalPrcmModuleSIdleState_t *sIdleState);

/**
 * \brief This API sets the module CLOCKACTIVITY State.
 *
 * \param moduleId              Unique ID of the module to be enabled
 * \param sClkActivity          ClkActivity to be set for module.
 *                              Refer enum #pmhalPrcmModuleSClkActivity_t for
 *                              values.
 * \param   timeOut             Wait time duration can be set to any uint32 or
 *         - #PM_TIMEOUT_INFINITE Waits till the Api Succeed
 *         - #PM_TIMEOUT_NOWAIT   Doesn't wait for api success.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *         - #PM_SUCCESS     Indicates the operation is success
 *         - #PM_FAIL        Indicates the module is not enabled (timeout)
 *         - #PM_BADARGS    Invalid module id
 */
int32_t PMHALModuleSClkActivitySet(pmhalPrcmModuleId_t           moduleId,
                                   pmhalPrcmModuleSClkActivity_t sClkActivity,
                                   uint32_t                      timeOut);

/**
 * \brief This API gets the module CLOCKACTIVITY State.
 *
 * \param moduleId         Unique ID of the module to be enabled
 * \param sClkActivity     ClkActivity State of module.
 *                         Refer enum #pmhalPrcmModuleSClkActivity_t for values.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *         - #PM_SUCCESS     Indicates the operation is success
 *         - #PM_FAIL        Indicates the module is not enabled (timeout)
 *         - #PM_BADARGS    Invalid module id
 */
int32_t PMHALModuleSClkActivityGet(pmhalPrcmModuleId_t            moduleId,
                                   pmhalPrcmModuleSClkActivity_t *sClkActivity);
/**
 * \brief This API sets the module Mode.
 *
 * \param moduleId              Unique ID of the module to be enabled
 * \param modMode               Mode to be set for module.
 *                              Refer enum #pmhalPrcmModuleSModuleMode_t for
 *                              values.
 * \param   timeOut             Wait time duration can be set to any uint32 or
 *         - #PM_TIMEOUT_INFINITE Waits till the Api Succeed
 *         - #PM_TIMEOUT_NOWAIT   Doesn't wait for api success.
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *         - #PM_SUCCESS      Indicates the operation is success
 *         - #PM_FAIL         Indicates the module is not enabled (timeout)
 *         - #PM_BADARGS     Invalid module id
 */
int32_t PMHALModuleModeSet(pmhalPrcmModuleId_t          moduleId,
                           pmhalPrcmModuleSModuleMode_t modMode,
                           uint32_t                     timeOut);

/**
 * \brief This API verifies if the Module Id is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *        - #PM_SUCCESS       Indicates the operation is success
 *        - #PM_FAIL          Indicates the module is not enabled (timeout)
 *        - #PM_BADARGS       Invalid module id
 */
pmErrCode_t PMHALModuleIsIdValid(pmhalPrcmModuleId_t moduleId);

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_MM_H_ */

/* @} */


