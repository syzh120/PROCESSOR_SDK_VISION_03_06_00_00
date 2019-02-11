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
 *  \ingroup PM_HAL PM HAL API
 *  \defgroup RESET_MANAGER Reset Configuration
 *
 *  The Reset Manager (RM) is a component of Power Management (PM) software
 *  which helps in putting a particular reset domain or the whole system in
 *  reset and bringing the same out of reset by checking if reset has occurred.
 *
 *  The RM is an independent module which is used for monitoring resets
 *  occurring in the System and for issuing Resets to various Reset
 *  domains which are part of the system.
 *
 *  -   The RM API would not retain any state which would record which
 *      reset domain that it is configuring.
 *  -   Only few of the reset domains are software programmable and rest are
 *      hardware controlled.
 *
 * @{
 */

/**
 *  \file      pmhal_rm.h
 *
 *  \brief     This file contains the PRCM Reset Manager Interface
 *             APIs
 */

#ifndef PMHAL_RM_H_
#define PMHAL_RM_H_

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
 * \brief This API issues the Global Reset.
 *
 * \param   glbResetId        Unique ID for a Global Reset Domain
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *          - #PM_SUCCESS     Indicates the operation is success
 *          - #PM_FAIL        Indicates the ResetDomain is not enabled (timeout)
 *          - #PM_BADARGS     Invalid ResetDomain id
 */
int32_t PMHALResetAssertGlobal(pmhalPrcmGlobalResetGroupId_t glbResetId);

/**
 * \brief This API is used to get the Reset status of a Global Reset Source.
 *
 * \param   glbResetId        Unique ID for a Global Reset Domain
 * \param   rGlbStatusMask    Status of whether the reset was asserted or not
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *         - #PM_SUCCESS      Indicates the operation is success
 *         - #PM_FAIL         Indicates the ResetDomain is not enabled (timeout)
 *         - #PM_BADARGS       Invalid ResetDomain id
 */
int32_t PMHALResetGetGlobalStatus(pmhalPrcmGlobalResetGroupId_t glbResetId,
                                  uint32_t                     *rGlbStatusMask);

/**
 * \brief This API clears the Reset Status of a Global Reset Source.
 *
 * \param   glbResetId        Unique ID for a Global Reset Domain
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *          - #PM_SUCCESS     Indicates the operation is success
 *          - #PM_FAIL        Indicates the ResetDomain is not enabled (timeout)
 *          - #PM_BADARGS     Invalid ResetDomain id
 */
int32_t PMHALResetClearGlobalStatus(pmhalPrcmGlobalResetGroupId_t glbResetId);

/**
 * \brief This API gets the Reset Status of a reset domain.
 *
 * \param   resId             Unique ID for a Reset Domain
 * \param   rStatusMask       Status of whether the reset was asserted or not
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *          - #PM_SUCCESS     Indicates the operation is success
 *          - #PM_FAIL        Indicates the ResetDomain is not enabled (timeout)
 *          - #PM_BADARGS     Invalid ResetDomain id
 */
int32_t PMHALResetGetStatus(pmhalPrcmResetGroupId_t resId,
                            uint32_t               *rStatusMask);

/**
 * \brief This API clears the Reset Status of a reset domain.
 *
 * \param   resId             Unique ID for a Reset Domain
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *          - #PM_SUCCESS     Indicates the operation is success
 *          - #PM_FAIL        Indicates the ResetDomain is not enabled (timeout)
 *          - #PM_BADARGS     Invalid ResetDomain id
 */
int32_t PMHALResetClearStatus(pmhalPrcmResetGroupId_t resId);

/**
 * \brief This API asserts reset for the given reset domain.
 *
 * \param   resId             Unique ID for a Reset Domain
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *          - #PM_SUCCESS     Indicates the operation is success
 *          - #PM_FAIL        Indicates the ResetDomain is not enabled (timeout)
 *          - #PM_BADARGS     Invalid ResetDomain id
 */
int32_t PMHALResetAssert(pmhalPrcmResetGroupId_t resId);

/**
 * \brief This API releases reset for the given reset domain.
 *
 * \param   resId             Unique ID for a Reset Domain
 * \param   timeout           Required timeout for which the API should wait for
 *                            the reset to be released.
 *                            \n #PM_TIMEOUT_NOWAIT    - The API does not wait.
 *                            \n #PM_TIMEOUT_INFINITE  - The API waits
 *                            till the reset domain is released. If it does not
 *                            happen the API waits infinitely for the
 *                            reset domain comes out of reset.
 *                            \n Any other value - The API waits to any one of
 *                            the events to happen first :
 *                            \n    (1)(Success)Reset domain released
 *                            from reset.
 *                            \n    (2)(Failure) The timeout is reached but
 *                             reset domain is still in reset.
 *
 * \return  errorStatus       Status of API call. Can be any of the following,
 *         - #PM_SUCCESS      Indicates the operation is success
 *         - #PM_FAIL         Indicates the ResetDomain is not enabled (timeout)
 *         - #PM_BADARGS      Invalid ResetDomain id
 */
int32_t PMHALResetRelease(pmhalPrcmResetGroupId_t resId, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_RM_H_ */

/* @} */


