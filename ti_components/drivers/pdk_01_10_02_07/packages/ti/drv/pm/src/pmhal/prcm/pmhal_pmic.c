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
 * \file    pmhal_pmic.c
 *
 * \brief   Power Management IC API implementation.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pm_types.h"
#include "pmhal_pmic.h"
#include "pmhal_vm.h"
#include "hw_pmhal_vmdata.h"

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

/*
 * Pointer to the PMIC Operations. This should be populated with pointers to
 * the PMIC functions specific to the PMIC used on the board.
 */
static const pmhalPmicOperations_t *gPmhalPmicOperations = NULL;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMHALPmicRegister(const pmhalPmicOperations_t *pmicOps)
{
    pmErrCode_t retVal = PM_FAIL;

    /*
     * If pmicOps or isPresent function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * isPresent() function.
     */
    if ((pmicOps != NULL) && (pmicOps->isPresent != NULL))
    {
        retVal = pmicOps->isPresent();

        if (retVal == PM_SUCCESS)
        {
            gPmhalPmicOperations = pmicOps;
        }
    }

    return retVal;
}

const char *PMHALPmicGetRevision(void)
{
    const char *revision = "INVALID";

    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->getRevision != NULL))
    {
        revision = gPmhalPmicOperations->getRevision();
    }

    return revision;
}

pmErrCode_t PMHALPmicGetVendorId(uint32_t *vendorId)
{
    pmErrCode_t retVal = PM_FAIL;

    /*
     * If pmicOps or getVendorId() function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * getVendorId() function.
     */
    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->getVendorId != NULL) &&
        (vendorId != NULL))
    {
        retVal = gPmhalPmicOperations->getVendorId(vendorId);
    }

    return retVal;
}

pmErrCode_t PMHALPmicGetProductId(uint32_t *productId)
{
    pmErrCode_t retVal = PM_FAIL;

    /*
     * If pmicOps or getProductId() function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * getProductId() function.
     */
    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->getProductId != NULL) &&
        (productId != NULL))
    {
        retVal = gPmhalPmicOperations->getProductId(productId);
    }

    return retVal;
}

pmErrCode_t PMHALPmicGetRegulatorVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                         uint32_t                  *voltage)
{
    pmErrCode_t retVal = PM_FAIL;

    /*
     * If pmicOps or regulatorGetVoltage function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * regulatorGetVoltage() function.
     */
    if ((gPmhalPmicOperations == NULL) ||
        (gPmhalPmicOperations->regulatorGetVoltage == NULL))
    {
        retVal = PM_FAIL;
    }
    else if ((voltage == NULL) || (regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
             (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = gPmhalPmicOperations->regulatorGetVoltage(regId, voltage);
    }

    return retVal;
}

pmErrCode_t PMHALPmicSetRegulatorVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                         uint32_t                   voltage,
                                         uint32_t                   timeout,
                                         uint32_t                   checkRange)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (checkRange == TRUE)
    {
        /*
         * Ensure the voltage is with-in the prescribed range for the SOC
         * so we don't damage the device.
         */
        if ((voltage < PMHAL_VM_MIN_SOC_VOLTAGE) ||
            (voltage > PMHAL_VM_MAX_SOC_VOLTAGE))
        {
            retVal = PM_VOLTAGE_INVALID;
        }
    }

    /*
     * If pmicOps or regulatorSetVoltage function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * regulatorSetVoltage() function.
     */
    if (retVal == PM_SUCCESS)
    {
        if ((gPmhalPmicOperations != NULL) &&
            (gPmhalPmicOperations->regulatorSetVoltage != NULL))
        {
            retVal = gPmhalPmicOperations->regulatorSetVoltage(regId, voltage,
                                                               timeout);
        }
    }

    return retVal;
}

uint32_t PMHALPmicIsRegulatorEnabled(pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t present = FALSE;

    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->isRegulatorEnabled != NULL))
    {
        present = gPmhalPmicOperations->isRegulatorEnabled(regId);
    }

    return present;
}

pmErrCode_t PMHALPmicEnableRegulator(pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t retVal = PM_FAIL;

    /*
     * If pmicOps or regulatorEnable function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * regulatorEnable() function.
     */
    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->regulatorEnable != NULL))
    {
        retVal = gPmhalPmicOperations->regulatorEnable(regId);
    }

    return retVal;
}

pmErrCode_t PMHALPmicDisableRegulator(pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t retVal = PM_FAIL;

    /*
     * If pmicOps or regulatorDisable function pointer are NULL
     * return PM_FAIL. Otherwise return the retVal from the
     * regulatorDisable() function.
     */
    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->regulatorDisable != NULL))
    {
        retVal = gPmhalPmicOperations->regulatorDisable(regId);
    }

    return retVal;
}

uint32_t PMHALPmicGetConvRegulatorVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                          uint32_t                   avsVolt)
{
    uint32_t convVolt = 0;

    /*
     * If pmicOps or regulatorDisable function pointer are NULL
     * return 0 for convVolt. Otherwise return the retVal from the
     * regulatorGetConvVoltage() function.
     */
    if ((gPmhalPmicOperations != NULL) &&
        (gPmhalPmicOperations->regulatorGetConvVoltage != NULL))
    {
        convVolt = gPmhalPmicOperations->regulatorGetConvVoltage(regId, avsVolt);
    }

    return convVolt;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

