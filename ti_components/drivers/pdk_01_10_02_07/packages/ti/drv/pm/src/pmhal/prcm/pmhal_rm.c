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
 *  \file      pmhal_rm.c
 *
 *  \brief     This file contains the PRCM Reset Manager APIs
 *             implementation.
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
#include "pmhal_rm.h"

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
 * \brief This API verifies if the Global Reset Domain ID is valid or not.
 *
 * \param  glbResetId       Unique ID of the global reset domain to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the reset domain is not enabled (timeout)
 *         PM_BADARGS       Invalid reset domain
 */
static pmErrCode_t PmhalIsGlobalResetDomainIdValid(
    pmhalPrcmGlobalResetGroupId_t glbResetId);

/**
 * \brief This API verifies if the Reset Domain ID is valid or not.
 *
 * \param  rstId            Unique ID of the reset domain to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the reset domain is not enabled (timeout)
 *         PM_BADARGS       Invalid reset domain
 */
static pmErrCode_t PmhalIsResetDomainIdValid(
    pmhalPrcmResetGroupId_t rstId);

/**
 * \brief This API verifies if the Reset Domain ID is valid or not.
 *
 * \param  rstId            Unique ID of the reset domain to be enabled
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the reset domain is not enabled (timeout)
 *         PM_BADARGS       Invalid reset domain
 */
static pmErrCode_t PmhalIsResetDomainRegAvailable(
    pmhalPrcmResetGroupId_t rstId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t PMHALResetAssertGlobal(pmhalPrcmGlobalResetGroupId_t glbResetId)
{
    pmErrCode_t retVal;
    uint32_t    resetTypeMask;
    retVal = PM_SUCCESS;
    /* Software can control only global cold and warm reset among global resets
     * as given in PRM_RSTCTRL.
     */
    if (!((glbResetId == PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST) ||
          (glbResetId == PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST)))
    {
        retVal = PM_BADARGS;
    }
    if (PM_SUCCESS == retVal)
    {
        /* Only the shift is saved for the reset bit */
        resetTypeMask =
            (uint32_t) 1U <<
            pmhalGlobalResetControlElems[glbResetId].rstctrlBitField->regShift;
        HW_WR_FIELD32_RAW(
            pmhalGlobalResetControlElems[glbResetId].rstctrlBitField->regAddr,
            resetTypeMask,
            pmhalGlobalResetControlElems[glbResetId].rstctrlBitField->regShift,
            (uint32_t) 0x1U);
    }
    return (int32_t) retVal;
}

int32_t PMHALResetGetGlobalStatus(pmhalPrcmGlobalResetGroupId_t glbResetId,
                                  uint32_t                     *rGlbStatusMask)
{
    pmErrCode_t retVal;
    uint32_t    glbResetStMask;
    retVal = PM_SUCCESS;
    if (NULL == rGlbStatusMask)
    {
        retVal = PM_BADARGS;
    }
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsGlobalResetDomainIdValid(glbResetId);
    }
    /* Software can read the status of all sources of global chip level resets
     * as given in PRM_RSTST.
     */
    if (PM_SUCCESS == retVal)
    {
        glbResetStMask =
            (uint32_t) 1U <<
            pmhalGlobalResetStatusElems[glbResetId].rstStBitField->regShift;
        *rGlbStatusMask =
            (uint32_t) HW_RD_FIELD32_RAW(
                pmhalGlobalResetStatusElems[glbResetId].rstStBitField->regAddr,
                glbResetStMask,
                pmhalGlobalResetStatusElems[glbResetId].rstStBitField->regShift);
    }
    return (int32_t) retVal;
}

int32_t PMHALResetClearGlobalStatus(pmhalPrcmGlobalResetGroupId_t glbResetId)
{
    pmErrCode_t retVal;
    uint32_t    glbResetStMask;
    retVal = PM_SUCCESS;
    retVal = PmhalIsGlobalResetDomainIdValid(glbResetId);
    if (PM_SUCCESS == retVal)
    {
        /* Software can clear the status of all previously occurred sources of
         * global chip level resets as given in PRM_RSTST.
         */
        glbResetStMask =
            (uint32_t) 1U <<
            pmhalGlobalResetStatusElems[glbResetId].rstStBitField->regShift;
        HW_WR_FIELD32_RAW(
            pmhalGlobalResetStatusElems[glbResetId].rstStBitField->regAddr,
            glbResetStMask,
            pmhalGlobalResetStatusElems[glbResetId].rstStBitField->regShift,
            (uint32_t) 0x1U);
    }
    return (int32_t) retVal;
}

int32_t PMHALResetGetStatus(pmhalPrcmResetGroupId_t resId,
                            uint32_t               *rStatusMask)
{
    pmErrCode_t retVal;
    uint32_t    resetStMask;
    retVal = PM_SUCCESS;
    if (NULL == rStatusMask)
    {
        retVal = PM_BADARGS;
    }
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsResetDomainIdValid(resId);
    }
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsResetDomainRegAvailable(resId);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Get the reset status of the local reset as given in <RD>_RSTST */
        resetStMask =
            (uint32_t) 1U <<
            pmhalResetDomainElems[resId].rstStBitField->regShift;
        *rStatusMask = (uint32_t) HW_RD_FIELD32_RAW(
            pmhalResetDomainElems[resId].rstStBitField->regAddr,
            resetStMask,
            pmhalResetDomainElems[resId].rstStBitField->regShift);
    }
    return (int32_t) retVal;
}

int32_t PMHALResetClearStatus(pmhalPrcmResetGroupId_t resId)
{
    pmErrCode_t retVal;
    uint32_t    resetStMask;
    retVal = PM_SUCCESS;
    retVal = PmhalIsResetDomainIdValid(resId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsResetDomainRegAvailable(resId);
    }
    /* Clear the reset status of the local reset as recorded in <RD>_RSTST */
    if (PM_SUCCESS == retVal)
    {
        resetStMask =
            (uint32_t) 1U <<
            pmhalResetDomainElems[resId].rstStBitField->regShift;
        HW_WR_FIELD32_RAW(pmhalResetDomainElems[resId].rstStBitField->regAddr,
                          resetStMask,
                          pmhalResetDomainElems[resId].rstStBitField->regShift,
                          (uint32_t) 0x1U);
    }
    return (int32_t) retVal;
}

int32_t PMHALResetAssert(pmhalPrcmResetGroupId_t resId)
{
    pmErrCode_t retVal;
    uint32_t    resetCtrlMask;
    retVal = PM_SUCCESS;
    retVal = PmhalIsResetDomainIdValid(resId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsResetDomainRegAvailable(resId);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Put the local reset domain in reset state by programming the
         * <RD>_RSTCTRL bit to 1.
         */
        resetCtrlMask =
            (uint32_t) 1U <<
            pmhalResetDomainElems[resId].rstCtrlBitField->regShift;
        HW_WR_FIELD32_RAW(
            pmhalResetDomainElems[resId].rstCtrlBitField->regAddr,
            resetCtrlMask,
            pmhalResetDomainElems[resId].rstCtrlBitField->regShift,
            (uint32_t) 0x1U);
    }
    return (int32_t) retVal;
}

int32_t PMHALResetRelease(pmhalPrcmResetGroupId_t resId, uint32_t timeout)
{
    pmErrCode_t retVal;
    uint32_t    resetCtrlMask;
    uint32_t    timeToWait;
    uint32_t    rstStat;
    uint32_t    rstStMask;
    rstStat = 0x0U;
    retVal  = PM_SUCCESS;
    retVal  = PmhalIsResetDomainIdValid(resId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsResetDomainRegAvailable(resId);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Put the local reset domain out of reset state by programming the
         * <RD>_RSTCTRL bit to 0.
         */
        resetCtrlMask =
            (uint32_t) 1U <<
            pmhalResetDomainElems[resId].rstCtrlBitField->regShift;
        HW_WR_FIELD32_RAW(
            pmhalResetDomainElems[resId].rstCtrlBitField->regAddr,
            resetCtrlMask,
            pmhalResetDomainElems[resId].rstCtrlBitField->regShift,
            (uint32_t) 0x0U);
        /* On lifting the reset based on the time out given by the user wait
         * for the reset to complete and the status reflected in the <RD>_RSTST.
         */
        if (timeout == PM_TIMEOUT_NOWAIT)
        {
            /* Will not wait for the release status */
            ;
        }
        else if (timeout == PM_TIMEOUT_INFINITE)
        {
            /* Wait infinitely for the reset to complete */
            do
            {
                rstStMask = (uint32_t) 1U <<
                            pmhalResetDomainElems[resId].rstStBitField->
                            regShift;
                rstStat =
                    (uint32_t) HW_RD_FIELD32_RAW(
                        pmhalResetDomainElems[resId].rstStBitField->regAddr,
                        rstStMask,
                        pmhalResetDomainElems[resId].rstStBitField->regShift);
            } while (0x1U != rstStat);
        }
        else
        {
            /* Wait for the reset to complete till time out occurs */
            timeToWait = timeout;
            do
            {
                rstStMask = (uint32_t) 1U <<
                            pmhalResetDomainElems[resId].rstStBitField->
                            regShift;
                rstStat =
                    (uint32_t) HW_RD_FIELD32_RAW(
                        pmhalResetDomainElems[resId].rstStBitField->regAddr,
                        rstStMask,
                        pmhalResetDomainElems[resId].rstStBitField->regShift);
                timeToWait--;
            } while ((0x1U != rstStat) && (0U != timeToWait));
            /* If the time out expires and the reset has still not completed
             * the function returns failure.
             */
            if (timeToWait == 0U)
            {
                if (0x1U == rstStat)
                {
                    retVal = PM_SUCCESS;
                }
                else
                {
                    retVal = PM_FAIL;
                }
            }
        }
    }
    return (int32_t) retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static pmErrCode_t PmhalIsGlobalResetDomainIdValid(
    pmhalPrcmGlobalResetGroupId_t glbResetId)
{
    pmErrCode_t retVal;
    if ((glbResetId < PMHAL_PRCM_GLB_RG_MIN) ||
        (glbResetId > PMHAL_PRCM_GLB_RG_MAX))
    {
        retVal = PM_INPUT_PARAM_BAD_RESET_ID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsResetDomainIdValid(
    pmhalPrcmResetGroupId_t rstId)
{
    pmErrCode_t retVal;
    if ((rstId <= PMHAL_PRCM_RG_LOWER_BOUND) || (rstId >= PMHAL_PRCM_RG_COUNT))
    {
        retVal = PM_INPUT_PARAM_BAD_RESET_ID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static pmErrCode_t PmhalIsResetDomainRegAvailable(
    pmhalPrcmResetGroupId_t rstId)
{
    pmErrCode_t retVal;
    /* Not all reset domains are software programmable */
    if ((rstId <= PMHAL_PRCM_RG_LOWER_BOUND) ||
        (rstId >= PMHAL_PRCM_RG_PROGRAMMABLE_RST_COUNT))
    {
        retVal = PM_INPUT_PARAM_NONCONFIGURABLE_RESET_DOMAIN_ID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

