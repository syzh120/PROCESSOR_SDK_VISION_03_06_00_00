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
 * \file    pmhal_sd.c
 *
 * \brief   This file contains the API definition for the Static Dependency HAL.
 *          The SD HAL enables the following operations:
 *          - Enables setting the static dependency from one clock domain to the
 *            other.
 *          - Reading the static dependency register value for a given clock
 *            domain.
 *          - Enables clearing the static dependency from one clock domain to
 *            the other.
 *          - Enables clearing all the software controllable static dependencies
 *            from a master.
 *          - Enables clearing the static dependency of a slave clock domain
 *            from all master clock domains.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pmhal_sd.h"
#include "hw_pmhal_data.h"

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

int32_t PMHALStaticDepEnable(pmhalPrcmCdId_t srcDom, pmhalPrcmCdId_t destDom)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    regFieldMask = 0U;
    uint32_t    regFieldShift;
    uint32_t    regVal;

    if ((PMHAL_REG_NOTAPPLICABLE !=
         pmhalClockDomainElems[srcDom].staticDepAddr)
        && (PMHAL_SHIFT_NOTAPPLICABLE !=
            pmhalClockDomainElems[destDom].staticDepCdShift))
    {
        /* Sets the static dependency such that clock domain B (Dest) must be
         * active when clock domain A (Source) is active so that the module in
         * clock domain B (Dest) is accessible by the module in clock domain A
         * (Source).
         */
        regFieldMask = (uint32_t) ((uint32_t) 1U <<
                                   pmhalClockDomainElems[destDom].
                                   staticDepCdShift);
        regFieldShift =
            (uint32_t) pmhalClockDomainElems[destDom].staticDepCdShift;

        HW_WR_FIELD32_RAW(pmhalClockDomainElems[srcDom].staticDepAddr,
                          regFieldMask,
                          regFieldShift,
                          (uint32_t) 1U);
    }
    else
    {
        status = PM_BADARGS;
    }

    if (PM_SUCCESS == status)
    {
        regVal = HW_RD_REG32(pmhalClockDomainElems[srcDom].staticDepAddr);
        if ((uint32_t) 0U == (regVal & regFieldMask))
        {
            status = PM_FAIL;
        }
    }

    return status;
}

int32_t PMHALStaticDepDisable(pmhalPrcmCdId_t srcDom, pmhalPrcmCdId_t destDom)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    regFieldMask = 0U;
    uint32_t    regFieldShift;
    uint32_t    regVal;

    if ((PMHAL_REG_NOTAPPLICABLE !=
         pmhalClockDomainElems[srcDom].staticDepAddr)
        && (PMHAL_SHIFT_NOTAPPLICABLE !=
            pmhalClockDomainElems[destDom].staticDepCdShift))
    {
        /* Clears the static dependency such that clock domain B (Dest) need
         * not be active when clock domain A (Source) is active.
         */
        regFieldMask = (uint32_t) ((uint32_t) 1U <<
                                   pmhalClockDomainElems[destDom].
                                   staticDepCdShift);
        regFieldShift = pmhalClockDomainElems[destDom].staticDepCdShift;

        HW_WR_FIELD32_RAW(pmhalClockDomainElems[srcDom].staticDepAddr,
                          regFieldMask,
                          regFieldShift,
                          (uint32_t) 0U);
    }
    else
    {
        status = PM_BADARGS;
    }

    if (PM_SUCCESS == status)
    {
        regVal = HW_RD_REG32(pmhalClockDomainElems[srcDom].staticDepAddr);
        if ((uint32_t) 0U != (regVal & regFieldMask))
        {
            status = PM_FAIL;
        }
    }

    return status;
}

int32_t PMHALStaticDepRead(pmhalPrcmCdId_t clockDom, uint32_t *regVal)
{
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == regVal)
    {
        status = PM_BADARGS;
    }
    else
    {
        if (PMHAL_REG_NOTAPPLICABLE !=
            pmhalClockDomainElems[clockDom].staticDepAddr)
        {
            /* Returns the 32 bit static dependency field for a given clock
             * domain as given in STATICDEP register
             */
            *regVal = HW_RD_REG32(
                pmhalClockDomainElems[clockDom].staticDepAddr);
        }
        else
        {
            status = PM_BADARGS;
        }
    }

    return status;
}

int32_t PMHALStaticDepDisableAllSlaveDep(pmhalPrcmCdId_t masterClockDom)
{
    pmErrCode_t status = PM_SUCCESS;

    if (PMHAL_REG_NOTAPPLICABLE !=
        pmhalClockDomainElems[masterClockDom].staticDepAddr)
    {
        /* Clears the STATICDEP register for a given clock domain */
        HW_WR_REG32(pmhalClockDomainElems[masterClockDom].staticDepAddr, 0U);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALStaticDepDisableToAllMaster(pmhalPrcmCdId_t  slaveClockDom,
                                         pmhalPrcmCdId_t *failMasterDom)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    masterCD;
    uint32_t    regFieldMask;
    uint32_t    regFieldShift;
    uint32_t    regVal;

    if (PMHAL_SHIFT_NOTAPPLICABLE !=
        pmhalClockDomainElems[slaveClockDom].staticDepCdShift)
    {
        regFieldMask = (uint32_t) ((uint32_t) 1U <<
                                   pmhalClockDomainElems[slaveClockDom].
                                   staticDepCdShift);
        regFieldShift = pmhalClockDomainElems[slaveClockDom].staticDepCdShift;

        /* Go through each master clock domain for which we have a valid
         * static dependency address and then clear the bit which corresponds
         * to the slave clock domain.
         * If the dependency does not exist it is OK to write 0 to the reserved
         * space as well.
         */
        for (masterCD = (uint32_t) (PMHAL_PRCM_CD_LOWER_BOUND + 1);
             masterCD < (uint32_t) PMHAL_PRCM_CD_COUNT;
             masterCD++)
        {
            if (PMHAL_REG_NOTAPPLICABLE !=
                pmhalClockDomainElems[masterCD].staticDepAddr)
            {
                HW_WR_FIELD32_RAW(pmhalClockDomainElems[masterCD].staticDepAddr,
                                  regFieldMask,
                                  regFieldShift,
                                  (uint32_t) 0U);
                /* No need to read the return value here as the PM_BADARGS would
                 * be sent only when the masterCD does not have valid static
                 * dependency register, which is already checked in the above if
                 * condition.
                 */
                PMHALStaticDepRead((pmhalPrcmCdId_t) masterCD, &regVal);
                regVal = (regVal & regFieldMask);
                if (0U != regVal)
                {
                    status = PM_SD_CLOCK_DOMAIN_DEPENDENCY_HARDWIRED;
                    if (NULL != failMasterDom)
                    {
                        *failMasterDom = (pmhalPrcmCdId_t) masterCD;
                    }
                    break;
                }
            }
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

