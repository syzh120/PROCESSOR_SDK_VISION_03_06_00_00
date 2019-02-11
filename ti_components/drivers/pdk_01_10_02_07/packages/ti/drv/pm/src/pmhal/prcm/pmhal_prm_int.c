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
 * \file pmhal_prm_int.c
 *
 *  \brief  This file contains the PRM Interrupt interface declarations.
 *          This file contains declarations of APIs which provide:
 *          - Enabling the particular interrupt line for a particular CPU.
 *          - Disabling the particular interrupt line for a particular CPU.
 *          - Reading the status of a particular interrupt for a particular CPU
 *          - Clearing the status of a particular interrupt for a particular
 *            CPU.
 *          - Waiting for the reception of a given interrupt for a given core.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pmhal_prcm.h"
#include "pmhal_prm_int.h"
#include "hw_pmhal_prmdata.h"

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

int32_t PMHALPrmIntEnableInterrupt(pmhalPrcmSocCpuId_t cpuId,
                                   pmhalPrcmPrmIntId_t intId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    regVal;
    uint32_t    shift;
    /* Enable the desired interrupt for the given CPU. Different CPUs have
     * different address and shifts to enable the interrupt
     */
    status = PmhalPrmIntGetIrqEnAddrShift(cpuId, intId, &addr, &shift);

    if (PM_SUCCESS == status)
    {
        regVal  = HW_RD_REG32(addr);
        regVal |= ((uint32_t) 1U << shift);
        HW_WR_REG32(addr, regVal);
    }
    return (int32_t) status;
}

int32_t PMHALPrmIntDisableInterrupt(pmhalPrcmSocCpuId_t cpuId,
                                    pmhalPrcmPrmIntId_t intId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    regVal;
    uint32_t    shift;
    /* Disable the desired interrupt for the given CPU. Different CPUs have
     * different address and shifts to disable the interrupt
     */
    status = PmhalPrmIntGetIrqEnAddrShift(cpuId, intId, &addr, &shift);

    if (PM_SUCCESS == status)
    {
        regVal  = HW_RD_REG32(addr);
        regVal &= (uint32_t) (~((uint32_t) 1U << shift));
        HW_WR_REG32(addr, regVal);
    }

    return (int32_t) status;
}

int32_t PMHALPrmIntGetEnabledInts(pmhalPrcmSocCpuId_t cpuId,
                                  uint64_t           *interrupts)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;

    if (NULL != interrupts)
    {
        *interrupts = 0U;
        status      = PmhalPrmIntGetIrqEnAddr(cpuId, &addr);
        /* Get a 64 bit value indicating which interrupts from PRCM are enabled
         * Each bit position is used to indicate the interrupt enabled/disabled
         */
        if (PM_SUCCESS == status)
        {
            PmhalPrmIntGetEnabledInts(cpuId, addr, interrupts);
        }
    }
    else
    {
        status = PM_BADARGS;
    }
    return (int32_t) status;
}

int32_t PMHALPrmIntEnableAllInts(pmhalPrcmSocCpuId_t cpuId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    /* Writing 1 to the reserved bits would not cause issues */
    uint32_t    regVal = 0xFFFFFFFFU;

    status = PmhalPrmIntGetIrqEnAddr(cpuId, &addr);

    if (PM_SUCCESS == status)
    {
        PmhalPrmIntConfigRegister(cpuId, addr, regVal);
    }

    return (int32_t) status;
}

int32_t PMHALPrmIntDisableAllInts(pmhalPrcmSocCpuId_t cpuId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    /* Writing 0 to the reserved bits would not cause issues */
    uint32_t    regVal = 0x0U;

    status = PmhalPrmIntGetIrqEnAddr(cpuId, &addr);

    if (PM_SUCCESS == status)
    {
        PmhalPrmIntConfigRegister(cpuId, addr, regVal);
    }

    return (int32_t) status;
}

int32_t PMHALPrmIntGetStatus(pmhalPrcmSocCpuId_t cpuId,
                             pmhalPrcmPrmIntId_t intId, uint32_t *isSet)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    regVal;
    uint32_t    shift;

    if (NULL != isSet)
    {
        /* Get the status of the interrupt if the hardware has raised it. */
        status = PmhalPrmIntGetIrqStAddrShift(cpuId, intId, &addr, &shift);

        if (PM_SUCCESS == status)
        {
            regVal = HW_RD_REG32(addr);
            *isSet = (regVal & (uint32_t) ((uint32_t) 1U << shift)) >> shift;
        }
    }
    else
    {
        status = PM_BADARGS;
    }
    return (int32_t) status;
}

int32_t PMHALPrmIntWaitforInt(pmhalPrcmSocCpuId_t cpuId,
                              pmhalPrcmPrmIntId_t intId, uint32_t timeout)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    regVal;
    uint32_t    shift;
    uint32_t    isSet = 0U;
    uint32_t    timeToWait;

    status = PmhalPrmIntGetIrqStAddrShift(cpuId, intId, &addr, &shift);
    /* Based on the time out read the status of the interrupt and break out
     * of the loop when the interrupt is set from the PRCM hardware. Can be used
     * in polling mode for the PRCM interrupts.
     */
    if (PM_SUCCESS == status)
    {
        regVal = HW_RD_REG32(addr);
        isSet  = (regVal & (uint32_t) ((uint32_t) 1U << shift)) >> shift;

        if (timeout == PM_TIMEOUT_INFINITE)
        {
            while (0U == isSet)
            {
                regVal = HW_RD_REG32(addr);
                isSet  =
                    (regVal & (uint32_t) ((uint32_t) 1U << shift)) >> shift;
            }
        }
        else
        {
            timeToWait = timeout;
            /*
             * Wait till the interrupt is set or time out completes, which
             * ever comes first.
             */
            while ((0U == isSet) && (0U != timeToWait))
            {
                regVal = HW_RD_REG32(addr);
                isSet  =
                    (regVal & (uint32_t) ((uint32_t) 1U << shift)) >> shift;
                timeToWait--;
            }

            /* If timeToWait is 0 then the time out has been reached */
            if ((0U == timeToWait) && (0U == isSet))
            {
                status = PM_FAIL;
            }
            else
            {
                status = PM_SUCCESS;
            }
        }
    }

    return (int32_t) status;
}

int32_t PMHALPrmIntClearStatus(pmhalPrcmSocCpuId_t cpuId,
                               pmhalPrcmPrmIntId_t intId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    regVal;
    uint32_t    shift;

    status = PmhalPrmIntGetIrqStAddrShift(cpuId, intId, &addr, &shift);

    if (PM_SUCCESS == status)
    {
        /*
         * SW is required to clear a set bit by writing a '1'
         * into the bit-position to be cleared.
         */
        regVal = ((uint32_t) 1U << shift);
        HW_WR_REG32(addr, regVal);
    }

    return (int32_t) status;
}

int32_t PMHALPrmIntClearAllStatus(pmhalPrcmSocCpuId_t cpuId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    regVal = 0xFFFFFFFFU;

    status = PmhalPrmIntGetIrqStAddr(cpuId, &addr);

    if (PM_SUCCESS == status)
    {
        /*
         * SW is required to clear a set bit by writing a '1'
         * into the bit-position to be cleared. For clear status of all write
         * 0xFFFFFFFF. There are no issues is writing '1's to reserved fields.
         */
        PmhalPrmIntConfigRegister(cpuId, addr, regVal);
    }
    return (int32_t) status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
