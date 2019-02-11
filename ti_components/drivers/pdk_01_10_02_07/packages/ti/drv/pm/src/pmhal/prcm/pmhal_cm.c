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
 *  \file      pmhal_cm.c
 *
 *  \brief     This file contains the prototypes of the APIs present in the
 *             device abstraction layer file of PRCM module mode.
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
#include "pmhal_cm.h"
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Set Register value.
 */
#define SET_REG (0x1U)

/**
 * \brief Reset Register value.
 */
#define RESET_REG (0x0U)

/**
 * \brief unit bit mask value.
 */
#define UNIT_BIT_MASK (0x00000001U)

/**
 * \brief Dpll lock value.
 */
#define LOCKDPLL (0x07U)

/**
 * \brief Dpll unlock value.
 */
#define UNLOCKDPLL (0x05U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API verifies if the Module Id is valid or not.
 *
 * \param moduleId          Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsModuleIdValid(pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API verifies if the Module clockSelect config is valid or not.
 *
 * \param  moduleId          Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmhalIsModuleClockSelConfigValid(
    pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API verifies if the Clock Id is valid or not.
 *
 * \param  cdId             Unique ID of the module to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid Clock Domain id
 */
static pmErrCode_t PmhalIsClockDomainIdValid(pmhalPrcmCdId_t cdId);

/**
 * \brief This API verifies if the clock status control Reg address
 *        is valid or not.
 *
 * \param  pmhalPrcmCdId_t  Unique ID of the clock domain
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid Clock Domain id
 */
static pmErrCode_t PmhalIsClkStCtrlOffsetValid(pmhalPrcmCdId_t cdId);

/**
 * \brief This API verifies if the Multiplexer Id is valid or not.
 *
 * \param  muxId            Unique ID of the multiplexer
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid multiplexer id
 */
static pmErrCode_t PmhalIsMuxIdValid(pmhalPrcmNodeId_t muxId);

/**
 * \brief This API verifies if multiplexer clock select is valid or not.
 *
 * \param  muxId            Unique ID of the multiplexer
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid multiplexer id
 */
static pmErrCode_t PmhalIsMuxClkSelValid(pmhalPrcmNodeId_t muxId);

/**
 * \brief This API verifies if the Divider Id is valid or not.
 *
 * \param divId             Unique ID of the divider.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid divider id
 */
static pmErrCode_t PmhalIsDivIdValid(pmhalPrcmNodeId_t divId);

/**
 * \brief This API verifies if the Divider value selection is Applicable
 *
 * \param divId             Unique ID of the divider.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS                               Indicates the Divider is
 *                                                  programmable.
 *         PM_CM_DIV_SEL_REGISTER_NOT_APPLICABLE    Indicates that Divider can't
 *                                                  be programmed
 */
static pmErrCode_t PmhalIsDivCtrlValid(pmhalPrcmNodeId_t divId);

/**
 * \brief This API verifies if the Dpll Id is valid or not.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalIsDpllIdValid(pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API verifies if the pllClkModeRegAddr is valid or not.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalIspllClkModeRegAddrValid(
    pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API verifies if the pllAutoIdleRegAddr is valid or not.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalIspllAutoIdleRegAddrValid(
    pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API verifies if the dpllClkSel is valid or not.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalIsDpllClkSelValid(pmhalPrcmNodeId_t dpllId);
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
/**
 * \brief This API verifies if the fracMDivRegAddr is valid or not.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalIsDpllFracMValid(pmhalPrcmNodeId_t dpllId);
#endif
/**
 * \brief This API verifies if the pllIdleStatusRegAddr is valid or not.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalIspllIdleStatusRegAddrValid(
    pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API verifies if the Clock mode is supported or not.
 *
 * \param clockdomainId     Unique ID of the clockDomain.
 * \param mode              pmhalPrcmCdClkTrnModes_t which is to be set.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid clock mode id
 */
static pmErrCode_t PmhalIsCdClkTrnModeSupported
    (pmhalPrcmCdId_t clockdomainId, pmhalPrcmCdClkTrnModes_t mode);

/**
 * \brief This API verifies if the Power mode is supported or not.
 *
 * \param dpllId            Unique ID of the dpll.
 * \param mode              pmhalPrcmDpllPowerMode_t which is to be set.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll power id
 */
static pmErrCode_t PmhalIsDpllPowerModeSupported(
    pmhalPrcmNodeId_t dpllId,
    pmhalPrcmDpllPowerMode_t
    dpllMode);

/**
 * \brief This API sets multiplier value to the given multiplier element.
 *
 * \param id                Unique ID of the dpll.
 * \param mulValue          multiplier value which is to be set.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll power id
 */
static pmErrCode_t PmhalCmDpllMultiplierSetInternal(pmhalPrcmNodeId_t id,
                                                    uint32_t          mulValue);
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
/**
 * \brief This API sets fractional multiplier value to the given multiplier
 *        element.
 *
 * \param id                Unique ID of the dpll.
 * \param fracValue         multiplier value which is to be set.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll power id
 */
static pmErrCode_t PmhalCmDpllFracMultSetInternal(pmhalPrcmNodeId_t id,
                                                  uint32_t          fracValue);
#endif
/**
 * \brief This API Locks the dpll.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval None
 */
static void PmhalCmDpllLockInternal(pmhalPrcmNodeId_t id);

/**
 * \brief This API UnLocks the dpll.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval None
 */
static void PmhalCmDpllUnLockInternal(pmhalPrcmNodeId_t id);

/**
 * \brief This API sets the Duty Cycle Corrector for given dpll.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval None
 */
static void PmhalCmDpllSetDutyCycleCorrectorInternal(pmhalPrcmNodeId_t id);

/**
 * \brief This API sets divider value to the given divider element.
 *
 * \param id                Unique ID of the dpll.
 * \param dividerValue      divider value which is to be set.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll power id
 */
static pmErrCode_t PmhalCmDpllDividerSetInternal(pmhalPrcmNodeId_t id,
                                                 uint32_t          dividerValue);

/**
 * \brief This API gets the dpll operating mode.
 *
 * \param dpllId            Unique ID of the dpll.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid dpll id
 */
static pmErrCode_t PmhalCmDpllGetOperatingModeInternal(
    pmhalPrcmNodeId_t dpllId,
    pmhalPrcmDpllPowerMode_t
                     *dpllMode);

/**
 * \brief This API gets the Clock mode .
 *
 * \param cdId       Unique ID of the clockDomain.
 * \param cdTrnMode  pmhalPrcmCdClkTrnModes_t which is set.
 *
 * \retval None
 */
static void PmhalCmGetCdClockModeInternal(pmhalPrcmCdId_t           cdId,
                                          pmhalPrcmCdClkTrnModes_t *cdTrnMode);

/**
 * \brief This API gets the Module Clock mode .
 *
 * \param modId      Unique ID of the Module.
 * \param cdId       Unique ID of the clockDomain.
 * \param clkIdx     Index of the clock in the clock sel config structure of the
 *                   module.
 * \param clkState   pmhalPrcmClockActivityState_t which is set.
 *
 * \retval None
 */
static void PmhalCmGetModuleClockStatusInternal
    (pmhalPrcmModuleId_t           modId,
    pmhalPrcmCdId_t                cdId,
    uint32_t                       clkIdx,
    pmhalPrcmClockActivityState_t *clkState);

/**
 * \brief This API checks whether the bypass clock select is valid or not
 *
 *
 * \param   dpllBypClkSel     bypassClk selection
 *                            Refer enum #pmhalPrcmDpllBypassClkSel_t for
 *                            values
 *
 * \retval  errorStatus  Status of API call. Can be any of the following,
 *          PM_SUCCESS   Indicates the operation is success
 *          PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *          PM_BADARGS   Invalid clock domain id
 */
static pmErrCode_t PmhalIsDpllBypClkSelValid(pmhalPrcmDpllBypassClkSel_t
                                             dpllBypClkSel);

/**
 * \brief This API checks whether the HIF clock select is valid or not
 *
 *
 * \param   dpllHifClkSel     bypassClk selection
 *                            Refer enum #pmhalPrcmDpllClkInput_t for values
 *
 * \retval  errorStatus  Status of API call. Can be any of the following,
 *          PM_SUCCESS   Indicates the operation is success
 *          PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *          PM_BADARGS   Invalid clock domain id
 */
static pmErrCode_t PmhalIsDpllHifClkSelValid(pmhalPrcmDpllClkInput_t
                                             dpllHifClkSel);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMHALCMDpllConfigure(pmhalPrcmNodeId_t            dpllId,
                             const pmhalPrcmDpllConfig_t *pDpllData,
                             uint32_t                     timeOut)
{
    int32_t           retVal;
    uint32_t          mulValue;
    uint32_t          fracMulValue;
    uint32_t          dividerValue;
    uint32_t          timeToWait;
    pmhalPrcmNodeId_t id;
    uint32_t          dpllLockStatus;

    if (NULL == pDpllData)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        timeToWait = timeOut;
        retVal     = PmhalIsDpllIdValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PmhalIspllAutoIdleRegAddrValid(dpllId);

            if (PM_SUCCESS == retVal)
            {
                /* Only PMHAL_PRCM_AUTO_DPLL_MODE_DISABLE is supported to
                 * ensure we do not hit the Silicon Errata i810 - DPLL
                 * Controller Sticks When Leaf Clock Requests Are Removed.
                 */
                HW_WR_FIELD32(pmhalDpllElems[id].pllAutoIdleRegAddr,
                              PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE,
                              PMHAL_PRCM_AUTO_DPLL_MODE_DISABLE);
            }
            if (PM_SUCCESS == retVal)
            {
                /* First read the M and N values of the given DPLL. If the
                 * multiplier and divider values are the same then only go
                 * ahead and unlock the DPLL to reprogram the M and N values
                 * This is done to ensure that if the DPLL HSDIV values are only
                 * to be updated then the M and N values can be kept constant
                 * and locking time can be saved.
                 */
                mulValue     = PMHALCMDpllGetMultiplier(dpllId);
                fracMulValue = PMHALCMDpllGetFracMultiplier(dpllId);
                dividerValue = PMHALCMDpllGetDivider(dpllId);

                if ((mulValue != pDpllData->multiplier) ||
                    (fracMulValue != pDpllData->fracMultiplier) ||
                    (dividerValue != pDpllData->divider))
                {
                    /* First unlock the DPLL when the M and N values are to be
                     * reprogrammed.
                     */
                    PmhalCmDpllUnLockInternal(id);
                    /* Reprogram the M value when the M value is different */
                    if (mulValue != pDpllData->multiplier)
                    {
                        retVal = PmhalCmDpllMultiplierSetInternal(
                            id,
                            pDpllData->multiplier);
                    }
                    /* Reprogram the frac M value when the M value is
                     * different
                     */
                    if (fracMulValue != pDpllData->fracMultiplier)
                    {
                        #if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
                        retVal = PmhalCmDpllFracMultSetInternal(
                            id,
                            pDpllData->fracMultiplier);
                        #else
                        retVal = (int32_t) PM_SUCCESS;
                        #endif
                    }
                    /* Reprogram the N value when the N value is different */
                    if (PM_SUCCESS == retVal)
                    {
                        if (dividerValue != pDpllData->divider)
                        {
                            retVal = PmhalCmDpllDividerSetInternal(
                                id,
                                pDpllData->
                                divider);
                        }
                    }
                    if (PM_SUCCESS == retVal)
                    {
                        /* Configure the HSDIV values after the M and N values
                         * are programmed.
                         */
                        retVal = PMHALCMDpllSetPostDiv(
                            dpllId,
                            pDpllData->
                            postDivConfList,
                            pDpllData->
                            maxPostDivElems);
                    }
                    /* The DCC set is required especially when a frequency
                     * higher than 1.4 GHz is required. (applies only to
                     * DPLL_MPU).
                     */
                    if (TRUE == pDpllData->dutyCycleCorrector)
                    {
                        PmhalCmDpllSetDutyCycleCorrectorInternal(id);
                    }
                }
                else
                {
                    /* If the M and N values are the same go ahead and program
                     * the HSDIV values.
                     */
                    retVal = PMHALCMDpllSetPostDiv(dpllId,
                                                   pDpllData->postDivConfList,
                                                   pDpllData->maxPostDivElems);
                }
                /* Check the lock status of the DPLL. If the DPLL is unlocked
                 * in the case of coming out of warm reset where the M and N
                 * values are the same but the DPLL is unlocked. Based on the
                 * timeout value either wait for ever or wait for the designated
                 * timeout for the DPLL to lock.
                 */
                dpllLockStatus = PMHALCMDpllLockStatus(dpllId);
                if (0U == dpllLockStatus)
                {
                    PmhalCmDpllLockInternal(id);

                    if (PM_TIMEOUT_NOWAIT != timeOut)
                    {
                        if (PM_TIMEOUT_INFINITE != timeOut)
                        {
                            do
                            {
                                dpllLockStatus =
                                    PMHALCMDpllLockStatus(dpllId);
                                timeToWait--;
                            } while ((0U == dpllLockStatus) &&
                                     (timeToWait != 0U));
                            if (timeToWait == 0U)
                            {
                                if (0U == dpllLockStatus)
                                {
                                    retVal = PM_FAIL;
                                }
                            }
                        }
                        else
                        {
                            do
                            {
                                dpllLockStatus =
                                    PMHALCMDpllLockStatus(dpllId);
                            } while (0U == dpllLockStatus);
                        }
                    }
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllDividerSet(pmhalPrcmNodeId_t dpllId, uint32_t dividerValue)
{
    pmErrCode_t       retVal;
    pmhalPrcmNodeId_t id;

    retVal = PmhalIsDivIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* Program the N value of the DPLL */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PmhalCmDpllDividerSetInternal(id, dividerValue);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllMultiplierSet(pmhalPrcmNodeId_t dpllId, uint32_t mulValue)
{
    pmErrCode_t       retVal;
    pmhalPrcmNodeId_t id;
    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Program the M value of the DPLL */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PmhalCmDpllMultiplierSetInternal(id, mulValue);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetFracMultiplier(pmhalPrcmNodeId_t dpllId,
                                     uint32_t          fracValue)
{
    pmErrCode_t       retVal = PM_SUCCESS;
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
    pmhalPrcmNodeId_t id;
    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Program the M value of the DPLL */
        retVal = PmhalIsDpllFracMValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PmhalCmDpllFracMultSetInternal(id, fracValue);
        }
    }
#endif
    return (int32_t) retVal;
}

uint32_t PMHALCMDpllGetDivider(pmhalPrcmNodeId_t dpllId)
{
    uint32_t retVal = 0U, id;
    if (PM_SUCCESS == PmhalIsDpllIdValid(dpllId))
    {
        /* Get the N value for a given DPLL */
        id = PMUtilsGetDpllId(dpllId);
        if (PM_SUCCESS == PmhalIsDpllClkSelValid(dpllId))
        {
            retVal = HW_RD_FIELD32_RAW(
                (uint32_t) pmhalDpllElems[id].pllClkSelRegAddr,
                (uint32_t) pmhalDpllElems[id].pllDivElemMask,
                (uint32_t) PMHAL_DPLL_DIV_SHIFT);
        }
    }
    return retVal;
}

uint32_t PMHALCMDpllGetMultiplier(pmhalPrcmNodeId_t dpllId)
{
    uint32_t retVal = 0U, id;
    if (PM_SUCCESS == PmhalIsDpllIdValid(dpllId))
    {
        /* Get the M value for a given DPLL */
        id = PMUtilsGetDpllId(dpllId);
        if (PM_SUCCESS == PmhalIsDpllClkSelValid(dpllId))
        {
            retVal = HW_RD_FIELD32_RAW(
                (uint32_t) pmhalDpllElems[id].pllClkSelRegAddr,
                (uint32_t) pmhalDpllElems[id].pllMulElemMask,
                (uint32_t) PMHAL_CLKSEL_MULT_SHIFT);
        }
    }
    return retVal;
}

uint32_t PMHALCMDpllGetFracMultiplier(pmhalPrcmNodeId_t dpllId)
{
    uint32_t retVal = 0U;
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
    uint32_t id;
    if (PM_SUCCESS == PmhalIsDpllIdValid(dpllId))
    {
        /* Get the M value for a given DPLL */
        id = PMUtilsGetDpllId(dpllId);
        if (PM_SUCCESS == PmhalIsDpllFracMValid(dpllId))
        {
            retVal = HW_RD_FIELD32_RAW(
                (uint32_t) pmhalDpllElems[id].fracMDivRegAddr,
                (uint32_t) PMHAL_FRACM_MASK,
                (uint32_t) PMHAL_FRACM_SHIFT);
        }
    }
#endif
    return retVal;
}

int32_t PMHALCMDpllSetOperationMode(pmhalPrcmNodeId_t        dpllId,
                                    pmhalPrcmDpllPowerMode_t dpllMode,
                                    uint32_t                 timeOut)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;
    uint32_t    timeToWait = timeOut;
    pmhalPrcmDpllPowerMode_t readDpllMode;

    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        /* Program the DPLL power mode (DPLL_EN) based on
         * pmhalPrcmDpllPowerMode_t input given. This is specifically used to
         * put the DPLL is Bypass, low power stop or locked state.
         */
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PmhalIsDpllPowerModeSupported(dpllId, dpllMode);
            if (PM_SUCCESS == retVal)
            {
                HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                              PMHAL_CLKMODE_DPLL_EN, dpllMode);
                /* Once the DPLL mode is programmed the status can be checked
                 * based on the time out value.
                 */
                if (PM_TIMEOUT_NOWAIT != timeOut)
                {
                    if (PM_TIMEOUT_INFINITE != timeOut)
                    {
                        do
                        {
                            PmhalCmDpllGetOperatingModeInternal(dpllId,
                                                                &readDpllMode);
                            timeToWait--;
                        } while ((readDpllMode != dpllMode) &&
                                 (timeToWait != 0U));
                        /* If the time out is 0 and the DPLL mode is still not
                         * set correctly the API returns fail.
                         */
                        if (timeToWait == 0U)
                        {
                            if (readDpllMode != dpllMode)
                            {
                                retVal = PM_FAIL;
                            }
                        }
                    }
                    else
                    {
                        /* Wait infinitely for the DPLL mode to be set. */
                        do
                        {
                            PmhalCmDpllGetOperatingModeInternal(dpllId,
                                                                &readDpllMode);
                        } while (readDpllMode != dpllMode);
                    }
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetOperatingMode(pmhalPrcmNodeId_t         dpllId,
                                    pmhalPrcmDpllPowerMode_t *dpllMode)
{
    pmErrCode_t retVal;

    if (NULL == dpllMode)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Get the DPLL operating mode. For instance whether in bypass/locked
         * or low power stop etc.
         */
        retVal = PmhalCmDpllGetOperatingModeInternal(dpllId, dpllMode);
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllLock(pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t       retVal;
    pmhalPrcmNodeId_t id;

    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Check if the DPLL has a valid register to lock the DPLL and then
         * lock the DPLL by programming DPLL_EN to 0x7.
         */
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            PmhalCmDpllLockInternal(id);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllUnLock(pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t       retVal = PM_SUCCESS;
    pmhalPrcmNodeId_t id;
    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Check if the DPLL has a valid register to unlock the DPLL and then
         * unlock the DPLL by programming DPLL_EN to 0x5.
         */
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            PmhalCmDpllUnLockInternal(id);
            retVal = PM_SUCCESS;
        }
    }
    return (int32_t) retVal;
}

uint32_t PMHALCMDpllLockStatus(pmhalPrcmNodeId_t dpllId)
{
    uint32_t retVal;
    uint32_t id;

    retVal = PmhalIspllIdleStatusRegAddrValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* Read the ST_DPLL_CLK field to check if the DPLL is locked or
         * unlocked.
         */
        id     = PMUtilsGetDpllId(dpllId);
        retVal = HW_RD_FIELD32(pmhalDpllElems[id].pllIdleStatusRegAddr,
                               PMHAL_IDLEST_DPLL_ST_CLK);
    }
    return retVal;
}

int32_t PMHALCMDpllSetRampLevel(pmhalPrcmNodeId_t        dpllId,
                                pmhalPrcmDpllRampLevel_t rampLevel)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* The DPLL provides an output clock frequency ramping
         * feature when switching from bypass clock to normal clock
         * during lock and re-lock. Based on the value of rampLevel this ramping
         * feature can be enabled and the algorithm of ramping can be chosen.
         */
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            if (rampLevel <= PMHAL_PRCM_DPLL_RAMP_LEVEL_MAX)
            {
                HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                              PMHAL_DPLL_RAMP_LEVEL, rampLevel);
            }
            else
            {
                retVal = PM_BADARGS;
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetRampRate(pmhalPrcmNodeId_t       dpllId,
                               pmhalPrcmDpllRampRate_t rampRate)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* For the DPLL ramping configuration the time in terms of DPLL REFCLKs
         * spent at each stage of the clock ramping process can be configured
         * using the rampRate value.
         */
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            if (rampRate <= PMHAL_PRCM_DPLL_RAMP_RATE_MAX)
            {
                HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                              PMHAL_DPLL_RAMP_RATE, rampRate);
            }
            else
            {
                retVal = PM_BADARGS;
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetDriftGuard(pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* The Drift Guard bit allows to enable or disable the automatic
         * recalibration feature of the DPLL. The DPLL will automatically
         * start a recalibration process upon assertion of the DPLL's RECAL
         * flag if this bit is set.
         */
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                          PMHAL_DPLL_DRIFTGUARD_EN, SET_REG);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetDutyCycleCorrector(pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t       retVal = PM_SUCCESS;
    pmhalPrcmNodeId_t id;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* The DCC set is required especially the frequency is higher than
         * 1.4 GHz. (applies to DPLL_MPU)
         */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            PmhalCmDpllSetDutyCycleCorrectorInternal(id);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetDutyCycleCorrector(pmhalPrcmNodeId_t dpllId,
                                         uint8_t          *status)
{
    pmErrCode_t       retVal = PM_SUCCESS;
    pmhalPrcmNodeId_t id;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsDpllClkSelValid(dpllId);
        /* Read the current value of the DCC_EN bit of the CM_CLKSEL register
         * for the DPLL.
         */
        if (PM_SUCCESS == retVal)
        {
            id      = PMUtilsGetDpllId(dpllId);
            *status = (uint8_t) HW_RD_FIELD32(
                pmhalDpllElems[id].pllClkSelRegAddr,
                PMHAL_CLKSEL_DPLL_DCC_EN);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetDpllType(pmhalPrcmNodeId_t    dpllId,
                               pmhalPrcmDpllType_t *type)
{
    pmErrCode_t       retVal = PM_SUCCESS;
    pmhalPrcmNodeId_t id;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* There are different types of DPLLs on the device. Based on their
         * type the programming model for the DPLL is different.
         */
        id    = PMUtilsGetDpllId(dpllId);
        *type = (pmhalPrcmDpllType_t) pmhalDpllElems[id].dpllType;
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetLowPowerMode(pmhalPrcmNodeId_t dpllId, uint32_t timeOut)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;
    uint32_t    timeToWait = timeOut;
    pmhalPrcmDpllPowerMode_t readDpllMode;

    retVal = PmhalIsDpllIdValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        /* The type A DPLLs can be switched to low-power operation mode
         * (also called LPMODE) to optimize DPLL power consumption when the
         * input and output clock frequencies are low.
         */
        retVal = PmhalIspllClkModeRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                          PMHAL_DPLL_LPMODE_EN, SET_REG);

            /* Once set to low power mode wait for the DPLL_STATUS to show the
             * the DPLL is in low power bypass.
             */
            if (PM_TIMEOUT_NOWAIT != timeOut)
            {
                if (PM_TIMEOUT_INFINITE != timeOut)
                {
                    do
                    {
                        PmhalCmDpllGetOperatingModeInternal(dpllId,
                                                            &readDpllMode);
                        timeToWait--;
                    } while ((readDpllMode !=
                              PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE)
                             && (timeToWait != 0U));
                    if (timeToWait == 0U)
                    {
                        if (readDpllMode !=
                            PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE)
                        {
                            retVal = PM_FAIL;
                        }
                    }
                }
                else
                {
                    do
                    {
                        PmhalCmDpllGetOperatingModeInternal(dpllId,
                                                            &readDpllMode);
                    } while (readDpllMode !=
                             PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE);
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetAutoPowerMode(pmhalPrcmNodeId_t        dpllId,
                                    pmhalPrcmDpllPowerMode_t dpllMode)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;
    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIspllAutoIdleRegAddrValid(dpllId);

        if (PM_SUCCESS == retVal)
        {
            /* Only PMHAL_PRCM_AUTO_DPLL_MODE_DISABLE is supported to ensure we
             * do not hit the Silicon Errata i810 - DPLL Controller Sticks When
             * Leaf Clock Requests Are Removed.
             */
            if (PMHAL_PRCM_AUTO_DPLL_MODE_DISABLE == dpllMode)
            {
                id = PMUtilsGetDpllId(dpllId);
                HW_WR_FIELD32(pmhalDpllElems[id].pllAutoIdleRegAddr,
                              PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE, dpllMode);
            }
            else
            {
                retVal = PM_CM_DPLL_POWER_MODE_NOT_SUPPORTED;
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetAutoPowerMode(pmhalPrcmNodeId_t         dpllId,
                                    pmhalPrcmDpllPowerMode_t *dpllMode)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;
    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Read the current AUTO power mode for the DPLL */
        retVal = PmhalIspllAutoIdleRegAddrValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id        = PMUtilsGetDpllId(dpllId);
            *dpllMode = (pmhalPrcmDpllPowerMode_t) HW_RD_FIELD32(
                pmhalDpllElems[id].pllAutoIdleRegAddr,
                PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE);
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetBypassClkSelect(pmhalPrcmNodeId_t        dpllId,
                                      pmhalPrcmDpllClkInput_t *bypassClkSel)
{
    pmErrCode_t retVal;
    uint32_t    id;
    uint8_t     clkSelRegVal;

    if (NULL == bypassClkSel)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Read the control of the BYPASS clock of the PLL and the
         * associated HSDIVIDER. In DPLL Bypass mode, 0 - CLKINP is selected as
         * the BYPASS clock for CLKOUT/CLKOUTX2 1 - CLKINPULOW is selected as
         * the BYPASS clock for CLKOUT/CLKOUTX2.
         */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id           = PMUtilsGetDpllId(dpllId);
            clkSelRegVal = (uint8_t) HW_RD_FIELD32(
                pmhalDpllElems[id].pllClkSelRegAddr,
                PMHAL_CLKSEL_DPLL_BYP_CLKSEL);
            if (0 == clkSelRegVal)
            {
                *bypassClkSel = PMHAL_PRCM_DPLL_INP_CLKINP;
            }
            else
            {
                *bypassClkSel = PMHAL_PRCM_DPLL_INP_CLKINPULOW;
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetBypassClkSelect(pmhalPrcmNodeId_t           dpllId,
                                      pmhalPrcmDpllBypassClkSel_t bypassClkSel)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;

    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Configure the control of the BYPASS clock of the PLL and the
         * associated HSDIVIDER. In DPLL Locked mode, 0 - No impact 1 - No
         * impact. In DPLL Bypass mode, 0 - CLKINP is selected as
         * the BYPASS clock for CLKOUT/CLKOUTX2 1 - CLKINPULOW is selected as
         * the BYPASS clock for CLKOUT/CLKOUTX2.
         */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PmhalIsDpllBypClkSelValid(bypassClkSel);
            if (PM_SUCCESS == retVal)
            {
                HW_WR_FIELD32(pmhalDpllElems[id].pllClkSelRegAddr,
                              PMHAL_CLKSEL_DPLL_BYP_CLKSEL, bypassClkSel);
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetClkOutHIFSelect(pmhalPrcmNodeId_t        dpllId,
                                      pmhalPrcmDpllClkInput_t *bypassClkSel)
{
    pmErrCode_t retVal;
    uint32_t    id;
    uint8_t     clkSelRegVal;

    if (NULL == bypassClkSel)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Read the source of the DPLL CLKOUTHIF clock.
         * 0x0: CLKOUTHIF is generated from the DPLL oscillator (DCO)
         * 0x1: CLKOUTHIF is generated from CLKINPHIF
         */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id           = PMUtilsGetDpllId(dpllId);
            clkSelRegVal = (uint8_t) HW_RD_FIELD32(
                pmhalDpllElems[id].pllClkSelRegAddr,
                PMHAL_CLKSEL_DPLL_HIF_CLKSEL);
            if (0 == clkSelRegVal)
            {
                *bypassClkSel = PMHAL_PRCM_DPLL_INP_DCO;
            }
            else
            {
                *bypassClkSel = PMHAL_PRCM_DPLL_INP_CLKINPHIF;
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetClkOutHIFSelect(pmhalPrcmNodeId_t       dpllId,
                                      pmhalPrcmDpllClkInput_t bypassClkSel)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    id;
    uint32_t    clksel;

    retVal = PmhalIsDpllIdValid(dpllId);

    if (PM_SUCCESS == retVal)
    {
        /* Configure the source of the DPLL CLKOUTHIF clock.
         * 0x0: CLKOUTHIF is generated from the DPLL oscillator (DCO)
         * 0x1: CLKOUTHIF is generated from CLKINPHIF
         */
        retVal = PmhalIsDpllClkSelValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id = PMUtilsGetDpllId(dpllId);
            /* Not all PLLs have a valid value for the the clock HIF select */
            retVal = PmhalIsDpllHifClkSelValid(bypassClkSel);
            if (PM_SUCCESS == retVal)
            {
                clksel = (uint32_t) bypassClkSel & 1U;
                HW_WR_FIELD32(pmhalDpllElems[id].pllClkSelRegAddr,
                              PMHAL_CLKSEL_DPLL_HIF_CLKSEL,
                              clksel);
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetPostDiv(
    pmhalPrcmNodeId_t                 dpllId,
    const pmhalPrcmPllPostDivValue_t *divConfig,
    uint32_t                          maxPostDividerElems)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    divElemIdx;
    uint32_t    divConfElemIdx;
    uint32_t    id;
    pmhalCtrlMdlPostDivIdx_t ctrlModDivIndex;
    uint32_t    mask;

    if ((NULL == divConfig) || (0U == maxPostDividerElems))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsDpllIdValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PM_FAIL;
            id     = PMUtilsGetDpllId(dpllId);
            /* For the number of post dividers the user wants to program loop
             * through each of the post dividers.
             */
            for (divConfElemIdx = 0U;
                 divConfElemIdx < maxPostDividerElems;
                 divConfElemIdx++)
            {
                /* Loop through all the post dividers supported by the DPLL */
                for (divElemIdx = 0U;
                     divElemIdx < pmhalDpllElems[id].postDividersMax;
                     divElemIdx++)
                {
                    pmhalDpllPostDiv_t *postDiv = &pmhalDpllElems[id].
                                                  postDividers[divElemIdx];
                    /* Find the post divider which matches the user desired
                     * post divider
                     */
                    if (postDiv->postDivId
                        == divConfig[divConfElemIdx].postDivId)
                    {
                        /* In TDA3xx some post dividers are instantiated in
                         * control module. For these post dividers the
                         * programming sequence is different from PRCM post
                         * dividers.
                         */
                        if (postDiv->ctrlModDivIdx ==
                            PMHAL_CTRL_POSTDIV_NOTAPPLICABLE)
                        {
                            /* Check if the post divider has a valid register for
                            * programming.
                            */
                            if (PMHAL_INVALID_REGADDR != postDiv->postDivBitField
                                ->regAddr)
                            {
                                if (postDiv->postDivBitField->regMask !=
                                    PMHAL_MASK_NOTAPPLICABLE)
                                {
                                    retVal = PM_SUCCESS;
                                    /* Fix for Errata i826 : HSDIVIDER1 CLKOUT4
                                     * could glitch during on-the-fly divider
                                     * change to/from divide-by-2.5
                                     */
                                    if ((PMHAL_PRCM_DPLL_POST_DIV_H14 ==
                                         postDiv->postDivId) ||
                                        (PMHAL_PRCM_DPLL_POST_DIV_H24 ==
                                         postDiv->postDivId))
                                    {
                                        uint32_t currDivider;
                                        currDivider = HW_RD_FIELD32_RAW(
                                            (uint32_t) postDiv->
                                            postDivBitField->regAddr,
                                            (uint32_t) postDiv->
                                            postDivBitField->regMask,
                                            (uint32_t) postDiv->
                                            postDivBitField->regShift);
                                        /* Covering two conditions here:
                                         * 1.) Current value is odd and the new
                                         *     value is div by 2.5.
                                         * 2.) Current value is div by 2.5 and
                                         *     the new value is odd.
                                         */
                                        if (((divConfig[divConfElemIdx].
                                              configValue == 63U) &&
                                             ((currDivider % 0x2U) == 0x1U)) ||
                                            ((currDivider == 63U) &&
                                             ((divConfig[divConfElemIdx].
                                               configValue % 0x2U) == 0x1U)))
                                        {
                                            /* Program post divider to any even
                                             * value. Chosen as 0x4 in this
                                             * case.
                                             */
                                            HW_WR_FIELD32_RAW(
                                                (uint32_t) postDiv->
                                                postDivBitField->regAddr,
                                                (uint32_t) postDiv->
                                                postDivBitField->regMask,
                                                (uint32_t) postDiv->
                                                postDivBitField->regShift,
                                                (uint32_t) 0x4U);
                                        }
                                    }
                                    /* For any other post divider directly go
                                     * and program the value to be configured.
                                     * The IP internally does a -1 to this value
                                     * and divides the clock by config value.
                                     * i.e. if the configValue is 10 then the
                                     * clock would run at frequency
                                     * DCOCLK/10.
                                     */
                                    HW_WR_FIELD32_RAW(
                                        (uint32_t) postDiv->postDivBitField->
                                        regAddr,
                                        (uint32_t) postDiv->postDivBitField->
                                        regMask,
                                        (uint32_t) postDiv->postDivBitField->
                                        regShift,
                                        (uint32_t) divConfig[divConfElemIdx].
                                        configValue);
                                }
                                else
                                {
                                    retVal = PM_FAIL;
                                }
                            }
                            else
                            {
                                /* If the post divider register value is invalid
                                * it can so happen to directly take the clock
                                * from the DCO LDO clock with out a divider. In
                                * this case there is nothing to program.
                                */
                                if (divConfig[divConfElemIdx].postDivId
                                    == PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO)
                                {
                                    retVal = PM_SUCCESS;
                                }
                                else
                                {
                                    retVal = PM_CM_POST_DIV_REGISTER_INVALID;
                                }
                            }
                        }
                        else
                        {
                            uint32_t dividerValue = 0U;

                            /* Do this sequence for tda3xx only if there
                             * is controlModuleReg for the given divider. */
                            ctrlModDivIndex = postDiv->ctrlModDivIdx;

                            if (ctrlModDivIndex < PMHAL_CTRL_POSTDIV_COUNT)
                            {
                                const pmhalDpllCtrlMdlHsDiv_t *ctrlpostDiv
                                    =
                                        &pmhalCtrlModuleDpllDividerElems
                                        [ctrlModDivIndex];
                                /* Control module registers need an
                                 * adjustment value to be subtracted for
                                 * the HS dividers to properly divide the
                                 * DPLL outputs to have the right
                                 * frequency values. The IP internally does
                                 * not do the subtraction like the PRCM
                                 * post dividers.
                                 */
                                dividerValue = divConfig[divConfElemIdx].
                                               configValue -
                                               (uint32_t)
                                               ctrlpostDiv->valueAdjust;

                                /* Set the postDividers reg */
                                HW_WR_FIELD32_RAW(
                                    (uint32_t)
                                    ctrlpostDiv->hsDivValBitField->regAddr,
                                    (uint32_t)
                                    ctrlpostDiv->hsDivValBitField->regMask,
                                    (uint32_t)
                                    ctrlpostDiv->hsDivValBitField->regShift,
                                    (uint32_t) dividerValue);
                                /* Select the mux value */
                                HW_WR_FIELD32_RAW(
                                    (uint32_t) ctrlpostDiv->
                                    hsDivMuxSelBitField->regAddr,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivMuxSelBitField->regMask,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivMuxSelBitField->regShift,
                                    (uint32_t) ctrlpostDiv->muxSelectValue);

                                mask =
                                    (uint32_t) ((uint32_t) UNIT_BIT_MASK <<
                                                ctrlpostDiv->
                                                hsDivTEnableBitField->
                                                regShift);

                                /* Select the Toggle sequence 010 */
                                HW_WR_FIELD32_RAW(
                                    (uint32_t) ctrlpostDiv->
                                    hsDivTEnableBitField->regAddr,
                                    (uint32_t) mask,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivTEnableBitField->regShift,
                                    (uint32_t) 0U);

                                HW_WR_FIELD32_RAW(
                                    (uint32_t) ctrlpostDiv->
                                    hsDivTEnableBitField->regAddr,
                                    (uint32_t) mask,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivTEnableBitField->regShift,
                                    (uint32_t) 1U);

                                HW_WR_FIELD32_RAW(
                                    (uint32_t) ctrlpostDiv->
                                    hsDivTEnableBitField->regAddr,
                                    (uint32_t) mask,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivTEnableBitField->regShift,
                                    (uint32_t) 0U);
                                /* Re Select the mux value */
                                HW_WR_FIELD32_RAW(
                                    (uint32_t) ctrlpostDiv->
                                    hsDivMuxSelBitField->regAddr,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivMuxSelBitField->regMask,
                                    (uint32_t) ctrlpostDiv->
                                    hsDivMuxSelBitField->regShift,
                                    (uint32_t) 0U);
                                if (PMHAL_REG_NOTAPPLICABLE !=
                                    ctrlpostDiv->hsDivValEnableBitField->
                                    regAddr)
                                {
                                    /* Enable the HSDIV post div clock */
                                    HW_WR_FIELD32_RAW(
                                        (uint32_t) ctrlpostDiv->
                                        hsDivValEnableBitField->regAddr,
                                        (uint32_t) ctrlpostDiv->
                                        hsDivValEnableBitField->regMask,
                                        (uint32_t) ctrlpostDiv->
                                        hsDivValEnableBitField->regShift,
                                        (uint32_t) 1U);
                                }
                                retVal = PM_SUCCESS;
                            }
                            else
                            {
                                retVal = PM_CM_POST_DIV_REGISTER_INVALID;
                            }
                        }
                        /* Once the post divider is found break out of the
                         * loop.
                         */
                        break;
                    } /* if (postDiv->postDivId
                       * == divConfig[divConfElemIdx].postDivId) */
                }
                /* Check if the post divider is not found for this particular
                 * DPLL.
                 */
                if (divElemIdx == pmhalDpllElems[id].postDividersMax)
                {
                    retVal = PM_INPUT_PARAM_BAD_POST_DIV_ID;
                    break;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetPostDiv(pmhalPrcmNodeId_t           dpllId,
                              pmhalPrcmPllPostDivValue_t *divConfig,
                              uint32_t                    maxPostDividerElems)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    divElemIdx;
    uint32_t    divConfElemIdx;
    uint32_t    id;
    uint32_t    ctrlModDivIndex;

    if (NULL == divConfig)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsDpllIdValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PM_INPUT_PARAM_BAD_POST_DIV_ID;
            id     = PMUtilsGetDpllId(dpllId);
            /* For the number of post dividers the user wants to read loop
             * through each of the post dividers.
             */
            for (divConfElemIdx = 0U;
                 divConfElemIdx < maxPostDividerElems;
                 divConfElemIdx++)
            {
                /* Loop through all the post dividers supported by the DPLL */
                for (divElemIdx = 0U;
                     divElemIdx < pmhalDpllElems[id].postDividersMax;
                     divElemIdx++)
                {
                    if (pmhalDpllElems[id].postDividers[divElemIdx].postDivId
                        == divConfig[divConfElemIdx].postDivId)
                    {
                        /* Check if the DPLL Post divider has a valid value for
                         * the register address and shift and mask for reading
                         * the post divider value.
                         */
                        if (PMHAL_INVALID_REGADDR != pmhalDpllElems[id].
                            postDividers[divElemIdx].postDivBitField->regAddr)
                        {
                            if (pmhalDpllElems[id].postDividers[divElemIdx].
                                ctrlModDivIdx ==
                                PMHAL_CTRL_POSTDIV_NOTAPPLICABLE)
                            {
                                retVal = PM_SUCCESS;
                                if (pmhalDpllElems[id].postDividers[
                                        divElemIdx].postDivBitField->regMask !=
                                    PMHAL_MASK_NOTAPPLICABLE)
                                {
                                    divConfig[divConfElemIdx].
                                    configValue = HW_RD_FIELD32_RAW(
                                        (uint32_t) pmhalDpllElems[id].
                                        postDividers[
                                            divElemIdx].postDivBitField->
                                        regAddr,
                                        (uint32_t) pmhalDpllElems[id].
                                        postDividers[
                                            divElemIdx].postDivBitField->
                                        regMask,
                                        (uint32_t) pmhalDpllElems[id].
                                        postDividers[
                                            divElemIdx].postDivBitField->
                                        regShift);
                                }
                                else
                                {
                                    divConfig[divConfElemIdx].configValue = 1;
                                    /* Should enter only for dcoldo clk where
                                     *  divider is not present*/
                                }
                            }
                            else
                            {
                                uint32_t dividerValue = 0U;
                                /* Do this sequence for tda3xx only if there
                                 * is controlModuleReg for the given divider. */
                                ctrlModDivIndex = pmhalDpllElems[id].
                                                  postDividers[divElemIdx].
                                                  ctrlModDivIdx;
                                if (ctrlModDivIndex < PMHAL_CTRL_POSTDIV_COUNT)
                                {
                                    /* Read the postDividers reg */
                                    dividerValue = HW_RD_FIELD32_RAW(
                                        (uint32_t)
                                        pmhalCtrlModuleDpllDividerElems[
                                            ctrlModDivIndex].hsDivValBitField->
                                        regAddr,
                                        (uint32_t)
                                        pmhalCtrlModuleDpllDividerElems[
                                            ctrlModDivIndex].hsDivValBitField->
                                        regMask,
                                        (uint32_t)
                                        pmhalCtrlModuleDpllDividerElems[
                                            ctrlModDivIndex].hsDivValBitField->
                                        regShift);

                                    /* Control module registers need an
                                     * adjustment value to be subtracted for
                                     * the HS dividers to properly divide the
                                     * DPLL outputs to have the right
                                     * frequency values.
                                     */
                                    divConfig[divConfElemIdx].configValue =
                                        dividerValue +
                                        (uint32_t)
                                        pmhalCtrlModuleDpllDividerElems[
                                            ctrlModDivIndex].valueAdjust;

                                    retVal = PM_SUCCESS;
                                }
                                else
                                {
                                    retVal = PM_CM_POST_DIV_REGISTER_INVALID;
                                }
                            }
                        }
                        else
                        {
                            if (divConfig[divConfElemIdx].postDivId
                                == PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO)
                            {
                                retVal = PM_SUCCESS;
                                divConfig[divConfElemIdx].configValue = 1;
                                /* Should enter only for dcoldo clk where
                                 *  divider is not present*/
                            }
                            else
                            {
                                retVal = PM_CM_POST_DIV_REGISTER_INVALID;
                            }
                        }
                        /* Once the post divider is found break out of the
                         * loop.
                         */
                        break;
                    } /* if (pmhalDpllElems[id].postDividers[divElemIdx].
                       * postDivId == divConfig[divConfElemIdx].postDivId)
                       */
                }
                /* Check if the post divider is not found for this particular
                 * DPLL.
                 */
                if (divElemIdx == pmhalDpllElems[id].postDividersMax)
                {
                    retVal = PM_INPUT_PARAM_BAD_POST_DIV_ID;
                    divConfig[divConfElemIdx].configValue = 0xFFFFFFFFU;
                    /* Return immediately in an error situation */
                    break;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetPostDivClkStatus(
    pmhalPrcmNodeId_t              dpllId,
    pmhalPrcmDpllPostDivId_t       pPostDivId,
    pmhalPrcmClockActivityState_t *status)
{
    pmErrCode_t retVal;
    uint32_t    divElem;
    uint32_t    id;

    if (status == NULL)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsDpllIdValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            id     = PMUtilsGetDpllId(dpllId);
            retVal = PM_INPUT_PARAM_BAD_POST_DIV_ID;
            /* Loop through all the post dividers for a given DPLL */
            for (divElem = 0U;
                 divElem < pmhalDpllElems[id].postDividersMax;
                 divElem++)
            {
                /* Find the Post divider ID the user is looking for */
                if (pmhalDpllElems[id].postDividers[divElem].postDivId ==
                    pPostDivId)
                {
                    retVal = PM_SUCCESS;
                    break;
                }
            }
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_INVALID_REGADDR !=
                    pmhalDpllElems[id].postDividers[divElem].postDivBitField->
                    regAddr)
                {
                    /* For DPLLs which have a clock out X2 the bit position to
                     * check for the clock status is different than other post
                     * dividers.
                     */
                    if (pmhalDpllElems[id].postDividers[divElem].postDivId ==
                        PMHAL_PRCM_DPLL_POST_DIV_M2X2)
                    {
                        *status = (pmhalPrcmClockActivityState_t) HW_RD_FIELD32
                                  (
                            pmhalDpllElems[id].postDividers[divElem].
                            postDivBitField->regAddr,
                            PMHAL_DIV_DPLL_CLKX2ST);
                    }
                    else
                    {
                        *status = (pmhalPrcmClockActivityState_t) HW_RD_FIELD32
                                  (
                            pmhalDpllElems[id].postDividers[divElem].
                            postDivBitField->regAddr,
                            PMHAL_DIV_DPLL_CLKST);
                    }
                }
                else
                {
                    retVal = PM_CM_POST_DIV_REGISTER_INVALID;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetAllPostDivStatus(pmhalPrcmNodeId_t           dpllId,
                                       pmhalPrcmPllPostDivValue_t *divConfig)
{
    int32_t  retVal;
    uint32_t divElem;
    uint32_t id;
    id = PMUtilsGetDpllId(dpllId);
    if (NULL == divConfig)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsDpllIdValid(dpllId);
        if (PM_SUCCESS == retVal)
        {
            /* Populate the structure for all the post dividers that
             * belong to the given DPLL.
             */
            for (divElem = 0U;
                 divElem < pmhalDpllElems[id].postDividersMax;
                 divElem++)
            {
                divConfig[divElem].postDivId =
                    pmhalDpllElems[id].postDividers[divElem].postDivId;
                divConfig[divElem].configValue = 1U;
            }
            /* Get the value of all post dividers */
            retVal = PMHALCMDpllGetPostDiv(dpllId,
                                           divConfig,
                                           pmhalDpllElems[id].postDividersMax);

            if (retVal == PM_SUCCESS)
            {
                retVal = pmhalDpllElems[id].postDividersMax;
            }
        }
    }
    return retVal;
}

int32_t PMHALCMGetModuleClockStatus(pmhalPrcmModuleId_t            moduleId,
                                    pmhalPrcmClockId_t             clkId,
                                    pmhalPrcmClockActivityState_t *clkState)
{
    pmErrCode_t         retVal = PM_SUCCESS;
    pmhalPrcmCdId_t     cdId;
    pmhalPrcmModuleId_t modId;
    uint32_t clkIdx;

    if (NULL == clkState)
    {
        retVal = PM_BADARGS;
    }
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleIdValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PmhalIsModuleClockSelConfigValid(moduleId);
            if (PM_SUCCESS == retVal)
            {
                modId  = PMUtilsGetModuleId(moduleId);
                retVal = PM_INPUT_PARAM_BAD_CLOCK_ID;
                /* Loop through all the clocks going to a given module and
                 * find if that particular clock is gated or running by looking
                 * at the CLKSTCTRL register at the clock domain level.
                 */
                if (modId <
                    (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                {
                    for (clkIdx = 0U; clkIdx < pmhalModuleElems[modId].maxClock;
                         clkIdx++)
                    {
                        if (clkId ==
                            pmhalModuleElems[modId].clkSelCfg[clkIdx].clockId)
                        {
                            cdId = (pmhalPrcmCdId_t) pmhalModuleElems[modId].
                                   clockDomainId;
                            retVal = PmhalIsClkStCtrlOffsetValid(cdId);
                            if (PM_SUCCESS == retVal)
                            {
                                PmhalCmGetModuleClockStatusInternal(
                                    modId, cdId, clkIdx, clkState);
                                retVal = PM_SUCCESS;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMGetModuleAllClockState(pmhalPrcmModuleId_t            moduleId,
                                      pmhalPrcmClockActivityState_t *clockState)
{
    int32_t             status = (int32_t) PM_SUCCESS;
    pmhalPrcmCdId_t     cdId;
    pmhalPrcmModuleId_t modId;
    uint32_t            idx;

    if (NULL == clockState)
    {
        status = (int32_t) PM_BADARGS;
    }
    if (PM_SUCCESS == status)
    {
        status = (int32_t) PmhalIsModuleIdValid(moduleId);
        if (PM_SUCCESS == status)
        {
            status = (int32_t) PmhalIsModuleClockSelConfigValid(moduleId);
            if (PM_SUCCESS == status)
            {
                modId = PMUtilsGetModuleId(moduleId);
                if (modId <
                    (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                {
                    cdId = (pmhalPrcmCdId_t) pmhalModuleElems[modId].
                           clockDomainId;
                    status = (int32_t) PmhalIsClockDomainIdValid(cdId);
                    /* Loop through the clock status for all the clocks going
                     * to a given module and then 'OR' them to see if any one
                     * of the clocks are enabled. If any one is enabled the
                     * module is said to have the clocks on. This is used
                     * to know if a module is clock gated or not.
                     */
                    if (PM_SUCCESS == status)
                    {
                        status = PmhalIsClkStCtrlOffsetValid(cdId);
                        if (PM_SUCCESS == status)
                        {
                            /* Start with an initial value of clocks being gated
                             */
                            *clockState =
                                PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED;
                            for (idx = 0U;
                                 idx < pmhalModuleElems[modId].maxClock;
                                 idx++)
                            {
                                pmhalPrcmClockActivityState_t clkState =
                                    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED;
                                PmhalCmGetModuleClockStatusInternal(
                                    modId, cdId, idx,
                                    (pmhalPrcmClockActivityState_t *) &clkState);
                                *clockState = (pmhalPrcmClockActivityState_t)
                                              ((uint32_t) (*clockState) |
                                               (uint32_t) clkState);
                            }
                        }
                    }
                }
            }
        }
    }
    return status;
}

int32_t PMHALCMModuleClockEnable(pmhalPrcmModuleId_t moduleId,
                                 pmhalPrcmClockId_t  clkId,
                                 uint32_t            timeOut)
{
    pmErrCode_t                   retVal;
    uint32_t                      idx;
    pmhalPrcmModuleId_t           modId;
    uint32_t                      mask;
    uint32_t                      timeToWait = timeOut;
    pmhalPrcmCdId_t               clkDomainIdx;
    pmhalPrcmClockActivityState_t clkState;

    retVal = PmhalIsModuleIdValid(moduleId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleClockSelConfigValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            modId  = PMUtilsGetModuleId(moduleId);
            retVal = PM_INPUT_PARAM_BAD_CLOCK_ID;
            if (modId <
                (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
            {
                /* Loop through all the clocks which belong to a given module
                 * and find the clock for which the clock has to be enabled.
                 */
                for (idx = 0U; idx < pmhalModuleElems[modId].maxClock; idx++)
                {
                    if (clkId == pmhalModuleElems[modId].clkSelCfg[idx].clockId)
                    {
                        /* Check if the clock can be configured to be enabled */
                        if (PMHAL_CLKSELCTRL_NOTAPPLICABLE !=
                            pmhalModuleElems[modId].clkSelCfg[idx].
                            clockSelControlShift)
                        {
                            /* Find which clock domain does the module belong to
                             * and program the corresponding CLKCTRL register
                             * bit field to 1.
                             */
                            clkDomainIdx =
                                (pmhalPrcmCdId_t) pmhalModuleElems[modId].
                                clockDomainId;
                            retVal = PmhalIsClockDomainIdValid(clkDomainIdx);
                            if (PM_SUCCESS == retVal)
                            {
                                retVal = PmhalIsClkStCtrlOffsetValid(
                                    clkDomainIdx);
                                if (PM_SUCCESS == retVal)
                                {
                                    mask = (uint32_t)
                                           ((uint32_t) UNIT_BIT_MASK <<
                                            pmhalModuleElems[modId].
                                            clkSelCfg[idx].
                                            clockSelControlShift);
                                    HW_WR_FIELD32_RAW(
                                        (uint32_t) pmhalModuleElems[modId].
                                        clkCtrlRegAddr,
                                        (uint32_t) mask,
                                        (uint32_t) pmhalModuleElems[modId].
                                        clkSelCfg[idx].clockSelControlShift,
                                        (uint32_t) SET_REG);
                                    /* Once configured based on the time out
                                     * read the status of the clock to ensure
                                     * the clock is running as desired.
                                     */
                                    if (PM_TIMEOUT_NOWAIT != timeOut)
                                    {
                                        if (PM_TIMEOUT_INFINITE != timeOut)
                                        {
                                            do
                                            {
                                                PmhalCmGetModuleClockStatusInternal
                                                    (modId,
                                                    clkDomainIdx,
                                                    idx,
                                                    &clkState);
                                                timeToWait--;
                                            } while
                                            ((clkState !=
                                              PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED)
                                             && ((timeToWait != 0U)));
                                            if (timeToWait == 0U)
                                            {
                                                if (clkState !=
                                                    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED)
                                                {
                                                    retVal = PM_FAIL;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            do
                                            {
                                                PmhalCmGetModuleClockStatusInternal
                                                    (modId,
                                                    clkDomainIdx,
                                                    idx,
                                                    &clkState);
                                            } while
                                            (clkState !=
                                             PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED);
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            retVal = PM_CM_CLKSEL_CTRL_NOT_APPLICABLE;
                        }
                        break;
                    }
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMModuleClockDisable(pmhalPrcmModuleId_t moduleId,
                                  pmhalPrcmClockId_t  clkId,
                                  uint32_t            timeOut)
{
    pmErrCode_t                   retVal;
    uint32_t                      idx;
    pmhalPrcmModuleId_t           modId;
    uint32_t                      mask;
    uint32_t                      timeToWait = timeOut;
    pmhalPrcmCdId_t               clkDomainIdx;
    pmhalPrcmClockActivityState_t clkState;

    retVal = PmhalIsModuleIdValid(moduleId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleClockSelConfigValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            modId = PMUtilsGetModuleId(moduleId);
            if (modId <
                (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
            {
                /* Loop through all the clocks which belong to a given module
                 * and find the clock for which the clock has to be disabled.
                 */
                retVal = PM_INPUT_PARAM_BAD_CLOCK_ID;
                for (idx = 0U; idx < pmhalModuleElems[modId].maxClock; idx++)
                {
                    if (clkId == pmhalModuleElems[modId].clkSelCfg[idx].clockId)
                    {
                        /* Check if the clock can be configured to be
                         * disabled
                         */
                        if (PMHAL_CLKSELCTRL_NOTAPPLICABLE !=
                            pmhalModuleElems[modId].clkSelCfg[idx].
                            clockSelControlShift)
                        {
                            /* Find which clock domain does the module belong to
                             * and program the corresponding CLKCTRL register
                             * bit field to 1.
                             */
                            clkDomainIdx =
                                (pmhalPrcmCdId_t) pmhalModuleElems[modId].
                                clockDomainId;
                            retVal = PmhalIsClockDomainIdValid(clkDomainIdx);
                            if (PM_SUCCESS == retVal)
                            {
                                retVal = PmhalIsClkStCtrlOffsetValid(
                                    clkDomainIdx);
                                if (PM_SUCCESS == retVal)
                                {
                                    mask = (uint32_t)
                                           ((uint32_t) UNIT_BIT_MASK <<
                                            pmhalModuleElems[modId].
                                            clkSelCfg[idx].
                                            clockSelControlShift);
                                    HW_WR_FIELD32_RAW(
                                        (uint32_t) pmhalModuleElems[modId].
                                        clkCtrlRegAddr,
                                        (uint32_t) mask,
                                        (uint32_t) pmhalModuleElems[modId].
                                        clkSelCfg[idx].clockSelControlShift,
                                        (uint32_t) RESET_REG);
                                    /* Once configured based on the time out
                                     * read the status of the clock to ensure
                                     * the clock is gated as desired.
                                     */
                                    if (PM_TIMEOUT_NOWAIT != timeOut)
                                    {
                                        if (PM_TIMEOUT_INFINITE != timeOut)
                                        {
                                            do
                                            {
                                                PmhalCmGetModuleClockStatusInternal
                                                    (modId,
                                                    clkDomainIdx,
                                                    idx,
                                                    &clkState);
                                                timeToWait--;
                                            } while
                                            ((clkState !=
                                              PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED)
                                             && ((timeToWait != 0U)));
                                            if (timeToWait == 0U)
                                            {
                                                if (clkState !=
                                                    PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED)
                                                {
                                                    retVal = PM_FAIL;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            do
                                            {
                                                PmhalCmGetModuleClockStatusInternal
                                                    (modId,
                                                    clkDomainIdx,
                                                    idx,
                                                    &clkState);
                                            } while
                                            (clkState !=
                                             PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED);
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            retVal = PM_CM_CLKSEL_CTRL_NOT_APPLICABLE;
                        }
                        break;
                    }
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMModuleEnableAllOptClock(pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t     retVal;
    uint32_t        idx;
    uint32_t        modId;
    pmhalPrcmCdId_t clkDomainIdx;
    uint32_t        mask;
    uint8_t         flag = (uint8_t) 0U;

    retVal = PmhalIsModuleIdValid(moduleId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleClockSelConfigValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            modId        = PMUtilsGetModuleId(moduleId);
            clkDomainIdx =
                (pmhalPrcmCdId_t) pmhalModuleElems[modId].clockDomainId;
            retVal = PmhalIsClockDomainIdValid(clkDomainIdx);
            if (PM_SUCCESS == retVal)
            {
                retVal = PmhalIsClkStCtrlOffsetValid(clkDomainIdx);
            }
            if (PM_SUCCESS == retVal)
            {
                /* Loop through all the optional clocks of the module and
                 * enable all of them based on their corresponding bit shift
                 * in the CLKCTRL register for that module.
                 */
                for (idx = 0U; idx < pmhalModuleElems[modId].maxClock; idx++)
                {
                    if (PMHAL_CLKSELCTRL_NOTAPPLICABLE !=
                        pmhalModuleElems[modId].clkSelCfg[idx].
                        clockSelControlShift)
                    {
                        mask = (uint32_t) ((uint32_t) UNIT_BIT_MASK <<
                                           pmhalModuleElems[modId].clkSelCfg[
                                               idx].
                                           clockSelControlShift);
                        HW_WR_FIELD32_RAW(
                            (uint32_t) pmhalModuleElems[modId].clkCtrlRegAddr,
                            (uint32_t) mask,
                            (uint32_t) pmhalModuleElems[modId].clkSelCfg[idx].
                            clockSelControlShift,
                            (uint32_t) SET_REG);
                        flag = (uint8_t) 1U;
                    }
                }
                /* If none of the clocks were programmed */
                if ((uint8_t) 0U == flag)
                {
                    retVal = PM_CM_CLKSEL_CTRL_NOT_APPLICABLE;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMModuleDisableAllOptClock(pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t     retVal;
    uint32_t        idx;
    uint32_t        modId;
    pmhalPrcmCdId_t clkDomainIdx;
    uint32_t        mask;
    uint8_t         flag = (uint8_t) 0U;

    retVal = PmhalIsModuleIdValid(moduleId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsModuleClockSelConfigValid(moduleId);
        if (PM_SUCCESS == retVal)
        {
            modId        = PMUtilsGetModuleId(moduleId);
            clkDomainIdx =
                (pmhalPrcmCdId_t) pmhalModuleElems[modId].clockDomainId;
            retVal = PmhalIsClockDomainIdValid(clkDomainIdx);
            if (PM_SUCCESS == retVal)
            {
                retVal = PmhalIsClkStCtrlOffsetValid(clkDomainIdx);
            }
            if (PM_SUCCESS == retVal)
            {
                /* Loop through all the optional clocks of the module and
                 * disable all of them based on their corresponding bit shift
                 * in the CLKCTRL register for that module.
                 */
                for (idx = 0U; idx < pmhalModuleElems[modId].maxClock; idx++)
                {
                    if (PMHAL_CLKSELCTRL_NOTAPPLICABLE !=
                        pmhalModuleElems[modId].clkSelCfg[idx].
                        clockSelControlShift)
                    {
                        mask = (uint32_t) ((uint32_t) UNIT_BIT_MASK <<
                                           pmhalModuleElems[modId].clkSelCfg[
                                               idx].
                                           clockSelControlShift);
                        HW_WR_FIELD32_RAW(
                            (uint32_t) pmhalModuleElems[modId].clkCtrlRegAddr,
                            (uint32_t) mask,
                            (uint32_t) pmhalModuleElems[modId].clkSelCfg[idx].
                            clockSelControlShift,
                            (uint32_t) RESET_REG);
                        flag = (uint8_t) 1U;
                    }
                }
                /* If none of the clocks were disabled */
                if ((uint8_t) 0U == flag)
                {
                    retVal = PM_CM_CLKSEL_CTRL_NOT_APPLICABLE;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMSetCdClockMode(pmhalPrcmCdId_t          clockdomainId,
                              pmhalPrcmCdClkTrnModes_t mode,
                              uint32_t                 timeOut)
{
    pmErrCode_t retVal     = PM_SUCCESS;
    uint32_t    timeToWait = timeOut;
    pmhalPrcmCdClkTrnModes_t readMode;

    retVal = PmhalIsClockDomainIdValid(clockdomainId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsClkStCtrlOffsetValid(clockdomainId);
        if (PM_SUCCESS == retVal)
        {
            /* Program a given clock domain to any of the valid states to which
             * the clock domain can be programmed to. The CLKSTCTRL:CLKTRCTRL
             * bit field is programmed based on the input.
             */
            retVal = PmhalIsCdClkTrnModeSupported(clockdomainId, mode);
            if (PM_SUCCESS == retVal)
            {
                HW_WR_FIELD32(
                    pmhalClockDomainElems[clockdomainId].clkStCtrlAddr,
                    PMHAL_CLKSTCTRL_CLKTRCTRL,
                    mode);
                /* Based on the time out the code waits for the clock domain
                 * CLKTRCTRL to get the right value.
                 */
                if (PM_TIMEOUT_NOWAIT != timeOut)
                {
                    if (PM_TIMEOUT_INFINITE != timeOut)
                    {
                        do
                        {
                            PmhalCmGetCdClockModeInternal(clockdomainId,
                                                          &readMode);
                            timeToWait--;
                        } while ((readMode != mode) && (timeToWait != 0U));
                        if ((timeToWait == 0U) && (readMode != mode))
                        {
                            retVal = PM_FAIL;
                        }
                    }
                    else
                    {
                        do
                        {
                            PmhalCmGetCdClockModeInternal(clockdomainId,
                                                          &readMode);
                        } while (readMode != mode);
                    }
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMGetCdClockMode(pmhalPrcmCdId_t           cdId,
                              pmhalPrcmCdClkTrnModes_t *cdTrnMode)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL == cdTrnMode)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Read the status of the clock domain CLKSTCTRL:CLKTRCTRL register
         * bit field.
         */
        retVal = PmhalIsClockDomainIdValid(cdId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PmhalIsClkStCtrlOffsetValid(cdId);

            if (PM_SUCCESS == retVal)
            {
                PmhalCmGetCdClockModeInternal(cdId, cdTrnMode);
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMMuxParentSelect(pmhalPrcmNodeId_t muxId,
                               pmhalPrcmNodeId_t pParentNodeId)
{
    pmErrCode_t               retVal;
    uint32_t                  muxParentIdx;
    pmhalPrcmNodeId_t         id;
    const pmhalMultiplexer_t *currMux;

    retVal = PmhalIsMuxIdValid(muxId);
    if (PM_SUCCESS == retVal)
    {
        id     = PMUtilsGetMuxId(muxId);
        retVal = PmhalIsMuxClkSelValid(id);
        if (PM_SUCCESS == retVal)
        {
            /* Loop through all the possible parents of a given multiplexer
             * to find which parent the user wants to configure. If found the
             * API goes and programs the mux selection to the required value
             * to select the desired parent for a given multiplexer.
             */
            currMux = &pmhalMultiplexerElems[id];
            retVal  = PM_CM_MUX_PARENT_SELECTION_INVALID;
            for (muxParentIdx = 0U;
                 muxParentIdx < currMux->pSupportedEnumMax;
                 muxParentIdx++)
            {
                if (currMux->pSupportedEnum[muxParentIdx].
                    nodeName == pParentNodeId)
                {
                    HW_WR_FIELD32_RAW(
                        (uint32_t) currMux->muxSelBitField->
                        regAddr,
                        (uint32_t) currMux->muxSelBitField->
                        regMask,
                        (uint32_t) currMux->muxSelBitField->
                        regShift,
                        (uint32_t) currMux->
                        pSupportedEnum[muxParentIdx].nodeEnumVaule);

                    retVal = PM_SUCCESS;
                    break;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMMuxParentGet(pmhalPrcmNodeId_t  muxId,
                            pmhalPrcmNodeId_t *pParentNodeId)
{
    pmErrCode_t       retVal;
    uint32_t          muxParentEnumValue;
    uint32_t          muxParentIdx;
    pmhalPrcmNodeId_t id;

    retVal = PmhalIsMuxIdValid(muxId);
    if (PM_SUCCESS == retVal)
    {
        id     = PMUtilsGetMuxId(muxId);
        retVal = PmhalIsMuxClkSelValid(id);
        if (PM_SUCCESS == retVal)
        {
            /* Read the value of the register which selects the input for the
             * given multiplexer. Then the software loops through all the valid
             * multiplexer values to find which parent node's clock is
             * propagated by the multiplexer.
             */
            muxParentEnumValue =
                HW_RD_FIELD32_RAW(
                    (uint32_t) pmhalMultiplexerElems[id].muxSelBitField->
                    regAddr,
                    (uint32_t) pmhalMultiplexerElems[id].muxSelBitField->
                    regMask,
                    (uint32_t) pmhalMultiplexerElems[id].muxSelBitField->
                    regShift);
            for (muxParentIdx = 0U;
                 muxParentIdx < pmhalMultiplexerElems[id].pSupportedEnumMax;
                 muxParentIdx++)
            {
                if (pmhalMultiplexerElems[id].pSupportedEnum[muxParentIdx].
                    nodeEnumVaule == muxParentEnumValue)
                {
                    *pParentNodeId = pmhalMultiplexerElems[id].
                                     pSupportedEnum[muxParentIdx].nodeName;
                    break;
                }
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllSetClockDivider(pmhalPrcmNodeId_t dividerId,
                                   uint32_t          dividerValue)
{
    pmErrCode_t                retVal;
    uint32_t                   idx;
    pmhalPrcmNodeId_t          divId;
    const pmhalClockDivider_t *currDiv;

    retVal = PmhalIsDivIdValid(dividerId);
    if (PM_SUCCESS == retVal)
    {
        retVal  = PM_INPUT_PARAM_BAD_DIV_ID;
        divId   = PMUtilsGetDivId(dividerId);
        currDiv = &pmhalDividerElems[divId];
        /* The divider value given by the user is the actual division value
         * which the clock frequency would be divided by. The API loops through
         * the valid division values supported by the divider and finds the
         * appropriate register configuration to program to get the desired
         * division value.
         */
        for (idx = 0U;
             idx < currDiv->pSupportedDivisionMax;
             idx++)
        {
            if (dividerValue ==
                currDiv->pSupportedDivision[idx].divValue)
            {
                HW_WR_FIELD32_RAW(
                    (uint32_t) currDiv->pDivCtrlBitField->
                    regAddr,
                    (uint32_t) currDiv->pDivCtrlBitField->regMask,
                    (uint32_t) currDiv->pDivCtrlBitField->regShift,
                    (uint32_t) currDiv->pSupportedDivision[idx].divEnum);
                retVal = PM_SUCCESS;
                break;
            }
        }
    }
    return (int32_t) retVal;
}

int32_t PMHALCMDpllGetClockDivider(pmhalPrcmNodeId_t dividerId,
                                   uint32_t         *dividerValue)
{
    pmErrCode_t       retVal;
    pmhalPrcmNodeId_t divId;
    uint32_t          idx;
    uint32_t          divEnum;
    retVal = PmhalIsDivIdValid(dividerId);
    if (PM_SUCCESS == retVal)
    {
        divId  = PMUtilsGetDivId(dividerId);
        retVal = PmhalIsDivCtrlValid(divId);
        if (PM_SUCCESS == retVal)
        {
            /* The function reads the register value corresponding to a given
             * division value. The function then loops through the list of
             * valid division values to find the actual divider value by which
             * the clock would be divided.
             */
            divEnum = HW_RD_FIELD32_RAW(
                (uint32_t) pmhalDividerElems[divId].pDivCtrlBitField->
                regAddr,
                (uint32_t) pmhalDividerElems[divId].pDivCtrlBitField->regMask,
                (uint32_t) pmhalDividerElems[divId].pDivCtrlBitField->regShift);
            for (idx = 0U;
                 idx < pmhalDividerElems[divId].pSupportedDivisionMax;
                 idx++)
            {
                if (divEnum ==
                    pmhalDividerElems[divId].pSupportedDivision[idx].divEnum)
                {
                    *dividerValue =
                        pmhalDividerElems[divId].pSupportedDivision[idx].
                        divValue;
                    retVal = PM_SUCCESS;
                    break;
                }
            }
        }
        if (PM_CM_DIV_SEL_REGISTER_NOT_APPLICABLE == retVal)
        {
            *dividerValue = pmhalDividerElems[divId].pSupportedDivision[0U].
                            divValue;
            retVal = PM_SUCCESS;
        }
    }
    return retVal;
}

uint32_t PMHALCMGetSysClockFreq(void)
{
    uint32_t sysClk;
    uint32_t retVal;

    sysClk = (uint32_t) PMHALCMGetSysClockFreqEnum();
    /* Return the system clock frequency read by the ROM from the sysboot pins
     * and written to the PRCM register */
    retVal = gPmhalSysClkFreqkHz[sysClk];
    return retVal;
}

pmhalPrcmSysClkVal_t PMHALCMGetSysClockFreqEnum(void)
{
    pmhalPrcmSysClkVal_t sysClk;
    /* Return the PRCM register contents updated by the ROM from the sysboot
     * pins and written to the PRCM register
     */
    sysClk = (pmhalPrcmSysClkVal_t)
             HW_RD_FIELD32(SOC_CKGEN_PRM_BASE + CM_CLKSEL_SYS,
                           CM_CLKSEL_SYS_SYS_CLKSEL);

    return sysClk;
}

int32_t PMHALCMDpllCoreSwitchSource(pmhalPrcmNodeId_t            sourceId,
                                    const pmhalPrcmDpllConfig_t *pDpllData,
                                    uint32_t                     timeOut)
{
    int32_t           retVal = (int32_t) PM_SUCCESS;
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t          dpllLockStatus;
    pmhalPrcmNodeId_t id;

    if ((NULL == pDpllData) ||
        ((sourceId != PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1) &&
         (sourceId != PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2)))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Ensure DPLL_CORE is in BYPASS mode */
        retVal = PMHALCMDpllSetOperationMode(
            PMHAL_PRCM_DPLL_CORE,
            PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE,
            timeOut);

        /* Set CM_CLKSEL_DPLL_CORE[23] DPLL_BYP_CLKSEL to 1 to select
         * the BYP_CLK_M2 input of DPLL
         */
        retVal += PMHALCMDpllSetBypassClkSelect(PMHAL_PRCM_DPLL_CORE,
                                                PMHAL_PRCM_DPLL_BYP_CLKINPULOW);

        /* Switch the SYS_CLK mux to select SYS_CLK2. */
        retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_DPLL_CORE_CLK,
                                         sourceId);
        id = PMUtilsGetDpllId(PMHAL_PRCM_DPLL_CORE);
        /* Program new DPLL parameters to match SYS_CLK2 clock speed */
        retVal += PmhalCmDpllMultiplierSetInternal(
            id,
            pDpllData->multiplier);
        retVal += PmhalCmDpllDividerSetInternal(
            id,
            pDpllData->divider);
        retVal += PmhalCmDpllFracMultSetInternal(
            id,
            pDpllData->fracMultiplier);
        /* Configure the HSDIV values after the M and N values are
         * programmed. */
        retVal += PMHALCMDpllSetPostDiv(PMHAL_PRCM_DPLL_CORE,
                                        pDpllData->postDivConfList,
                                        pDpllData->maxPostDivElems);

        /* Switch DPLL_CORE input back to REF_CLK. */
        retVal += PMHALCMDpllSetBypassClkSelect(PMHAL_PRCM_DPLL_CORE,
                                                PMHAL_PRCM_DPLL_BYP_CLKINP);

        /* Initiate the DPLL lock */
        /* Check the lock status of the DPLL. If the DPLL is unlocked
         * in the case of coming out of warm reset where the M and N
         * values are the same but the DPLL is unlocked. Based on the
         * timeout value either wait for ever or wait for the designated
         * timeout for the DPLL to lock.
         */
        dpllLockStatus = PMHALCMDpllLockStatus(PMHAL_PRCM_DPLL_CORE);
        if (0U == dpllLockStatus)
        {
            PmhalCmDpllLockInternal(id);

            if (PM_TIMEOUT_NOWAIT != timeOut)
            {
                if (PM_TIMEOUT_INFINITE != timeOut)
                {
                    do
                    {
                        dpllLockStatus =
                            PMHALCMDpllLockStatus(PMHAL_PRCM_DPLL_CORE);
                        timeOut--;
                    } while ((0U == dpllLockStatus) &&
                             (timeOut != 0U));
                    if (timeOut == 0U)
                    {
                        if (0U == dpllLockStatus)
                        {
                            retVal = PM_FAIL;
                        }
                    }
                }
                else
                {
                    do
                    {
                        dpllLockStatus =
                            PMHALCMDpllLockStatus(PMHAL_PRCM_DPLL_CORE);
                    } while (0U == dpllLockStatus);
                }
            }
        }
    }
#endif
    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static pmErrCode_t PmhalIspllAutoIdleRegAddrValid(
    pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t retVal;
    uint32_t    id;

    id = PMUtilsGetDpllId(dpllId);
    if (PMHAL_INVALID_REGADDR ==
        pmhalDpllElems[id].pllAutoIdleRegAddr)
    {
        retVal = PM_CM_DPLL_AUTO_IDLE_REGISTER_INVALID;
    }
    else if (PMHAL_REG_NOTAPPLICABLE ==
             pmhalDpllElems[id].pllAutoIdleRegAddr)
    {
        retVal = PM_CM_DPLL_AUTO_IDLE_PROGRAMMING_NOT_AVAILABLE;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsModuleIdValid(pmhalPrcmModuleId_t moduleId)
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

static pmErrCode_t PmhalIsModuleClockSelConfigValid(
    pmhalPrcmModuleId_t moduleId)
{
    pmErrCode_t         retVal;
    pmhalPrcmModuleId_t modId;

    modId = PMUtilsGetModuleId(moduleId);
    if (modId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        if (NULL == pmhalModuleElems[modId].clkSelCfg)
        {
            retVal = PM_CM_MODULE_CLKSEL_CONFIG_NOT_AVAILABLE;
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

static pmErrCode_t PmhalIsClockDomainIdValid(pmhalPrcmCdId_t cdId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if ((cdId <= PMHAL_PRCM_CD_LOWER_BOUND) || (cdId >= PMHAL_PRCM_CD_COUNT))
    {
        retVal = PM_INPUT_PARAM_BAD_CLK_DOMAIN_ID;
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

static pmErrCode_t PmhalIsClkStCtrlOffsetValid(pmhalPrcmCdId_t cdId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if (PMHAL_INVALID_REGADDR == pmhalClockDomainElems[cdId].clkStCtrlAddr)
    {
        retVal = PM_CM_CLOCK_DOMAIN_CLK_STATE_CTRL_REG_INVALID;
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

static pmErrCode_t PmhalIsMuxIdValid(pmhalPrcmNodeId_t muxId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if ((muxId < PMHAL_PRCM_MUX_MIN) || (muxId > PMHAL_PRCM_MUX_MAX))
    {
        retVal = PM_INPUT_PARAM_BAD_MUX_ID;
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

static pmErrCode_t PmhalIsDivIdValid(pmhalPrcmNodeId_t divId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if ((divId < PMHAL_PRCM_DIV_MIN) || (divId > PMHAL_PRCM_DIV_MAX))
    {
        retVal = PM_INPUT_PARAM_BAD_DIV_ID;
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

static pmErrCode_t PmhalIsDivCtrlValid(pmhalPrcmNodeId_t divId)
{
    pmErrCode_t retVal;
    if (PMHAL_REG_NOTAPPLICABLE ==
        pmhalDividerElems[divId].pDivCtrlBitField->regAddr)
    {
        retVal = PM_CM_DIV_SEL_REGISTER_NOT_APPLICABLE;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsMuxClkSelValid(pmhalPrcmNodeId_t muxId)
{
    pmErrCode_t retVal;
    if (PMHAL_INVALID_REGADDR ==
        pmhalMultiplexerElems[muxId].muxSelBitField->regAddr)
    {
        retVal = PM_CM_MUX_CLK_SEL_REGISTER_INVALID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsDpllClkSelValid(pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t retVal;
    uint32_t    id;

    id = PMUtilsGetDpllId(dpllId);
    if (PMHAL_INVALID_REGADDR == pmhalDpllElems[id].pllClkSelRegAddr)
    {
        retVal = PM_CM_DPLL_CLK_SEL_REGISTER_INVALID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
static pmErrCode_t PmhalIsDpllFracMValid(pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t retVal;
    uint32_t    id;

    id = PMUtilsGetDpllId(dpllId);
    if (PMHAL_REG_NOTAPPLICABLE == pmhalDpllElems[id].fracMDivRegAddr)
    {
        retVal = PM_CM_DPLL_CLK_SEL_REGISTER_INVALID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

#endif
static pmErrCode_t PmhalIspllClkModeRegAddrValid(
    pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t retVal;
    uint32_t    id;

    id = PMUtilsGetDpllId(dpllId);
    if (PMHAL_INVALID_REGADDR == pmhalDpllElems[id].pllClkModeRegAddr)
    {
        retVal = PM_CM_DPLL_CLK_MODE_REGISTER_INVALID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIspllIdleStatusRegAddrValid(
    pmhalPrcmNodeId_t dpllId)
{
    pmErrCode_t retVal;
    uint32_t    id;
    id = PMUtilsGetDpllId(dpllId);
    if (PMHAL_INVALID_REGADDR == pmhalDpllElems[id].pllClkModeRegAddr)
    {
        retVal = PM_CM_DPLL_IDLEST_REGISTER_INVALID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsDpllIdValid(pmhalPrcmNodeId_t dpllId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if ((dpllId < PMHAL_PRCM_DPLL_MIN) || (dpllId > PMHAL_PRCM_DPLL_MAX))
    {
        retVal = PM_INPUT_PARAM_BAD_DPLL_ID;
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

static pmErrCode_t PmhalIsCdClkTrnModeSupported
    (pmhalPrcmCdId_t clockdomainId, pmhalPrcmCdClkTrnModes_t mode)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if (1U ==
        ((pmhalClockDomainElems[clockdomainId].clkDomainCapability >> mode)
         & 1U))
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_CM_CLK_DOMAIN_TRANS_MODE_NOT_SUPPORTED;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static pmErrCode_t PmhalIsDpllPowerModeSupported(
    pmhalPrcmNodeId_t dpllId,
    pmhalPrcmDpllPowerMode_t
    dpllMode)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    uint32_t    id;

    id = PMUtilsGetDpllId(dpllId);
    if (1U == ((pmhalDpllElems[id].pllModesSupportedModes >> dpllMode) & 1U))
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_CM_DPLL_POWER_MODE_NOT_SUPPORTED;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static void PmhalCmDpllLockInternal(pmhalPrcmNodeId_t id)
{
    HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                  PMHAL_CLKMODE_DPLL_EN, LOCKDPLL);
}

static void PmhalCmDpllUnLockInternal(pmhalPrcmNodeId_t id)
{
    HW_WR_FIELD32(pmhalDpllElems[id].pllClkModeRegAddr,
                  PMHAL_CLKMODE_DPLL_EN, UNLOCKDPLL);
}

static void PmhalCmDpllSetDutyCycleCorrectorInternal(pmhalPrcmNodeId_t id)
{
    HW_WR_FIELD32(pmhalDpllElems[id].pllClkSelRegAddr,
                  PMHAL_CLKSEL_DPLL_DCC_EN, SET_REG);
}

static pmErrCode_t PmhalCmDpllMultiplierSetInternal(pmhalPrcmNodeId_t id,
                                                    uint32_t          mulValue)
{
    pmErrCode_t retVal = PM_SUCCESS;
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    if (mulValue > (uint32_t)
        ((uint32_t) pmhalDpllElems[id].pllMulElemMask >>
         (uint32_t) PMHAL_CLKSEL_MULT_SHIFT))
    {
        retVal = PM_CM_DPLL_MULTIPLIER_VALUE_OUT_OF_RANGE;
    }
#endif
    if (PM_SUCCESS == retVal)
    {
        HW_WR_FIELD32_RAW((uint32_t) pmhalDpllElems[id].pllClkSelRegAddr,
                          (uint32_t) pmhalDpllElems[id].pllMulElemMask,
                          (uint32_t) PMHAL_CLKSEL_MULT_SHIFT,
                          (uint32_t) mulValue);
        retVal = PM_SUCCESS;
    }

    return retVal;
}

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX)
static pmErrCode_t PmhalCmDpllFracMultSetInternal(pmhalPrcmNodeId_t id,
                                                  uint32_t          fracValue)
{
    pmErrCode_t retVal = PM_SUCCESS;
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    if (fracValue > (uint32_t)
        ((uint32_t) PMHAL_FRACM_MASK >>
         (uint32_t) PMHAL_FRACM_SHIFT))
    {
        retVal = PM_CM_DPLL_MULTIPLIER_VALUE_OUT_OF_RANGE;
    }
#endif
    if (PM_SUCCESS == retVal)
    {
        HW_WR_FIELD32_RAW((uint32_t) pmhalDpllElems[id].fracMDivRegAddr,
                          (uint32_t) PMHAL_FRACM_MASK,
                          (uint32_t) PMHAL_FRACM_SHIFT,
                          (uint32_t) fracValue);
        retVal = PM_SUCCESS;
    }
    return retVal;
}

#endif

static pmErrCode_t PmhalCmDpllDividerSetInternal(pmhalPrcmNodeId_t id,
                                                 uint32_t          dividerValue)
{
    pmErrCode_t retVal = PM_SUCCESS;
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    if (dividerValue >
        (uint32_t) ((uint32_t) pmhalDpllElems[id].pllDivElemMask >>
                    (uint32_t) PMHAL_DPLL_DIV_SHIFT))
    {
        retVal = PM_CM_DPLL_DIVIDER_VALUE_OUT_OF_RANGE;
    }
#endif
    if (PM_SUCCESS == retVal)
    {
        HW_WR_FIELD32_RAW((uint32_t) pmhalDpllElems[id].pllClkSelRegAddr,
                          (uint32_t) pmhalDpllElems[id].pllDivElemMask,
                          (uint32_t) PMHAL_DPLL_DIV_SHIFT,
                          (uint32_t) dividerValue);
    }
    return retVal;
}

static pmErrCode_t PmhalCmDpllGetOperatingModeInternal(
    pmhalPrcmNodeId_t         dpllId,
    pmhalPrcmDpllPowerMode_t *dpllMode)
{
    pmErrCode_t retVal;
    uint32_t    id;

    retVal = PmhalIspllIdleStatusRegAddrValid(dpllId);
    if (PM_SUCCESS == retVal)
    {
        id        = PMUtilsGetDpllId(dpllId);
        *dpllMode = (pmhalPrcmDpllPowerMode_t) HW_RD_FIELD32(
            pmhalDpllElems[id].pllIdleStatusRegAddr,
            CM_IDLEST_DPLL_ST_DPLL_MODE);
    }
    return retVal;
}

static void PmhalCmGetCdClockModeInternal(pmhalPrcmCdId_t           cdId,
                                          pmhalPrcmCdClkTrnModes_t *cdTrnMode)
{
    *cdTrnMode = (pmhalPrcmCdClkTrnModes_t) HW_RD_FIELD32(
        pmhalClockDomainElems[cdId].clkStCtrlAddr,
        PMHAL_CLKSTCTRL_CLKTRCTRL);
}

static void PmhalCmGetModuleClockStatusInternal(
    pmhalPrcmModuleId_t            modId,
    pmhalPrcmCdId_t                cdId,
    uint32_t                       clkIdx,
    pmhalPrcmClockActivityState_t *clkState)
{
    uint32_t mask;
    mask = (uint32_t) ((uint32_t) UNIT_BIT_MASK << pmhalModuleElems[modId].
                       clkSelCfg[clkIdx].clockStatusShift);
    *clkState = (pmhalPrcmClockActivityState_t) HW_RD_FIELD32_RAW(
        (uint32_t) pmhalClockDomainElems[cdId].clkStCtrlAddr,
        (uint32_t) mask,
        (uint32_t) pmhalModuleElems[modId].clkSelCfg[clkIdx].clockStatusShift);
}

static pmErrCode_t PmhalIsDpllBypClkSelValid(pmhalPrcmDpllBypassClkSel_t
                                             dpllBypClkSel)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;

    if (dpllBypClkSel <= PMHAL_PRCM_DPLL_BYP_MAX)
    {
        retVal = PM_SUCCESS;
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

static pmErrCode_t PmhalIsDpllHifClkSelValid(pmhalPrcmDpllClkInput_t
                                             dpllHifClkSel)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;

    if ((dpllHifClkSel >= PMHAL_PRCM_DPLL_INP_CLKINPHIF) &&
        (dpllHifClkSel <= PMHAL_PRCM_DPLL_INP_MAX))
    {
        retVal = PM_SUCCESS;
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

