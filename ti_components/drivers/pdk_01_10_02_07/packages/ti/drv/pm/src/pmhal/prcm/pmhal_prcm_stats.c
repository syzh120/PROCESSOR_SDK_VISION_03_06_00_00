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
 * \file    pmhal_prcm_stats.c
 *
 * \brief   This file contains the API definition for the PRCM Status HAL.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pmhal_prcm_stats.h"
#include "hw_pmhal_data.h"
#include "pm_utils.h"

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMHALPrcmStatsGetPdRegData(pmhalPrcmPdId_t pdIdx,
                                   pmhalPDStats_t *pdStatus)
{
    int32_t retVal = PM_SUCCESS;

    if (pdStatus != NULL)
    {
        if (pmhalPowerDomainElems[pdIdx].pwrStateCtrlRegAddr !=
            PMHAL_REG_NOTAPPLICABLE)
        {
            /* Power domain register data is populated in the following fashion:
             * PWRSTCTRL Address : PWRSTCTRL Value
             * PWRSTST Address   : PWRSTST Value.
             */
            pdStatus->pwrStateCtrlRegAddr = pmhalPowerDomainElems[pdIdx].
                                            pwrStateCtrlRegAddr;
            pdStatus->pwrStateCtrlRegVal = HW_RD_REG32(
                pmhalPowerDomainElems
                [pdIdx].
                pwrStateCtrlRegAddr);
            pdStatus->pwrStateStatusRegAddr = pmhalPowerDomainElems[pdIdx].
                                              pwrStateStatusRegAddr;
            pdStatus->pwrStateStatusRegVal = HW_RD_REG32(
                pmhalPowerDomainElems
                [pdIdx].
                pwrStateStatusRegAddr);
        }
        else
        {
            retVal = PM_FAIL;
        }
        /* Additionally for each power domain find the number of clock domains
         * and get the pointer to the clock domain list for that given power
         * domain.
         */
        pdStatus->numClockDomain = pmhalPowerDomainElems[pdIdx].numClockDomain;
        pdStatus->prcmCdList     = pmhalPowerDomainElems[pdIdx].clockDomainId;
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

int32_t PMHALPrcmStatsGetCdRegData(pmhalPrcmCdId_t cdIdx,
                                   pmhalCDStats_t *cdStatus)
{
    int32_t retVal = PM_SUCCESS;

    if (cdStatus != NULL)
    {
        /* Clock domain register data is populated in the following fashion:
         * CLKSTCTRL Address : CLKSTCTRL Value
         * STATICDEP Address : STATICDEP Value
         */
        if (pmhalClockDomainElems[cdIdx].clkStCtrlAddr !=
            PMHAL_REG_NOTAPPLICABLE)
        {
            cdStatus->clkStCtrlAddr = pmhalClockDomainElems[cdIdx].
                                      clkStCtrlAddr;
            cdStatus->clkStCtrlRegVal = HW_RD_REG32(pmhalClockDomainElems
                                                    [cdIdx].clkStCtrlAddr);
        }
        else
        {
            cdStatus->clkStCtrlAddr   = 0X00000000;
            cdStatus->clkStCtrlRegVal = 0U;
        }

        if (pmhalClockDomainElems[cdIdx].staticDepAddr !=
            PMHAL_REG_NOTAPPLICABLE)
        {
            cdStatus->staticDepAddr =
                pmhalClockDomainElems[cdIdx].staticDepAddr;
            cdStatus->staticDepRegVal = HW_RD_REG32(pmhalClockDomainElems
                                                    [cdIdx].staticDepAddr);
        }
        else
        {
            cdStatus->staticDepAddr   = 0X00000000;
            cdStatus->staticDepRegVal = 0U;
        }
        /* Additionally for each clock domain find the number of modules
         * and get the pointer to the module list for that given clock
         * domain.
         */
        cdStatus->numModulesInCd = pmhalClockDomainElems[cdIdx].
                                   numModulesInCd;
        cdStatus->prcmModList = pmhalClockDomainElems[cdIdx].pFirstModPtr;
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

int32_t PMHALPrcmStatsGetModRegData(pmhalPrcmModuleId_t modIdx,
                                    pmhalModuleStats_t *modStatus)
{
    int32_t retVal = PM_SUCCESS;
    pmhalPrcmModuleId_t moduleId;

    if (modStatus != NULL)
    {
        moduleId = PMUtilsGetModuleId(modIdx);
        /* Module register data is populated in the following fashion:
         * CLKCTRL Address : CLKCTRL Value
         */
        if (moduleId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
        {
            if (pmhalModuleElems[moduleId].clkCtrlRegAddr !=
                PMHAL_REG_NOTAPPLICABLE)
            {
                modStatus->clkCtrlRegAddr = pmhalModuleElems[moduleId].
                                            clkCtrlRegAddr;
                modStatus->clkCtrlRegVal = HW_RD_REG32(
                    pmhalModuleElems
                    [moduleId].
                    clkCtrlRegAddr);
            }
            else
            {
                modStatus->clkCtrlRegAddr = 0X00000000;
                modStatus->clkCtrlRegVal  = 0U;
            }
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

