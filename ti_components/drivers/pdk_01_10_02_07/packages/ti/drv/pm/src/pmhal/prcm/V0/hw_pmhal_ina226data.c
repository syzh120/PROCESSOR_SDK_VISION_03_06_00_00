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
 * \file hw_pmhal_ina226data.c
 *
 * \brief   Board INA226 specific data to measure power from the target.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "hw_pmhal_common_ina226data.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const pmhalIna226RegulatorData_t gPmhalIna226RegData
[PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    {0x41, 1U },
    /** PMHAL_PRCM_PMIC_REGULATOR_MPU */
    {0x48, 2U },
    /** PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {0x49, 2U },
    /** PMHAL_PRCM_PMIC_REGULATOR_IVA */
    {0x40, 1U },
    /** PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {0x44, 2U },
    /** PMHAL_PRCM_PMIC_REGULATOR_GPU */
    {0x45, 10U},
    /** PMHAL_PRCM_PMIC_REGULATOR_MMC13V3 */
    {0x47, 1U },
    /** PMHAL_PRCM_PMIC_REGULATOR_SHV5 */
    {0x4B, 10U},
    /** PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {0x43, 10U}
    /** PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint8_t PmhalIna226GetI2cAddress(pmhalPrcmPmicRegulatorId_t voltDomId)
{
    /* No need to check for limits in this function as this check is done
     * earlier.
     */
    uint8_t i2cAddr = gPmhalIna226RegData[voltDomId].i2cAddress;
    return i2cAddr;
}

uint32_t PmhalIna226GetShuntRes(pmhalPrcmPmicRegulatorId_t voltDomId)
{
    /* No need to check for limits in this function as this check is done
     * earlier.
     */
    uint32_t shuntRes = gPmhalIna226RegData[voltDomId].shuntResistance;
    return shuntRes;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

