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
 * \file    pm_utils.c
 *
 * \brief   Power Management Utility Functions
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pm_types.h"
#include "pmhal_prcm.h"
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

void PMUtilsMinDelayUS(uint32_t timeUS)
{
    /* TDA2xx uses max frequency of 750MHz (A15) */
    volatile int32_t cnt = (int32_t) timeUS * 125;

    for (; cnt > 0; --cnt)
    {
        ;
    }
}

void PMUtilsMinDelayMS(uint32_t timeMS)
{
    volatile int32_t cnt;
    /* Convert the delay from Milli Seconds to micro seconds and wait in
     * a dead loop
     */
    for (cnt = (int32_t) timeMS; cnt > 0; --cnt)
    {
        PMUtilsMinDelayUS((uint32_t) 1000U);
    }
}

pmhalPrcmCdId_t PMUtilsGetCdId(pmhalPrcmModuleId_t modId)
{
    pmhalPrcmCdId_t cdId;
    if ((modId < (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)) ||
        (modId > (PMHAL_PRCM_MOD_COUNT - 1U)))
    {
        cdId = PMHAL_PRCM_CD_COUNT;
    }
    else
    {
        uint32_t currModId = (uint32_t) PMUtilsGetModuleId(modId);
        /* Each module contains the information regarding which CD it belongs
         * to. Read this field and return the value of the clock domain ID
         */
        cdId = (pmhalPrcmCdId_t) pmhalModuleElems[currModId].clockDomainId;
    }
    return cdId;
}

pmhalPrcmPdId_t PMUtilsGetPdId(pmhalPrcmCdId_t cdId)
{
    pmhalPrcmPdId_t pdId;
    if ((cdId <= PMHAL_PRCM_CD_LOWER_BOUND) || (cdId >= PMHAL_PRCM_CD_COUNT))
    {
        pdId = PMHAL_PRCM_PD_COUNT;
    }
    else
    {
        /* Each CD contains the information regarding which PD it belongs
         * to. Read this field and return the value of the power domain ID
         */
        pdId = (pmhalPrcmPdId_t) pmhalClockDomainElems[cdId].powerDomainId;
    }
    return pdId;
}

pmhalPrcmVdId_t PMUtilsGetVdId(pmhalPrcmPdId_t pdId)
{
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_UNDEF;
    if (!((pdId <= PMHAL_PRCM_PD_LOWER_BOUND) || (pdId >= PMHAL_PRCM_PD_COUNT)))
    {
        /* Each PD contains the information regarding which VD it belongs
         * to. Read this field and return the value of the voltage domain ID
         */
        const pmhalPowerDomain_t *currPd = &pmhalPowerDomainElems[pdId];
        voltId = (pmhalPrcmVdId_t) currPd->vdId;
    }
    return voltId;
}

uint32_t PMUtilsGetNumModsInCd(pmhalPrcmCdId_t cdId)
{
    uint32_t num;
    if ((cdId <= PMHAL_PRCM_CD_LOWER_BOUND) || (cdId >= PMHAL_PRCM_CD_COUNT))
    {
        num = 0U;
    }
    else
    {
        /* Get the total number of modules in the CD. This is specifically
         * useful when trying to turn off a clock domain by looking at
         * all the modules in the clock domain.
         */
        const pmhalClkDomain_t *currCd = &pmhalClockDomainElems[cdId];
        num = currCd->numModulesInCd;
    }
    return num;
}

pmhalPrcmModuleId_t PMUtilsGetModuleIdinCd(pmhalPrcmCdId_t cdId,
                                           uint32_t        iter)
{
    pmhalPrcmModuleId_t modId;
    if ((cdId <= PMHAL_PRCM_CD_LOWER_BOUND) || (cdId >= PMHAL_PRCM_CD_COUNT))
    {
        modId = PMHAL_PRCM_MOD_UNDEF;
    }
    else
    {
        /* From the given clock domain ID and the iteration number find first
         * if the index is lesser than the number of modules in the clock domain
         * and return the module ID for that particular index.
         */
        const pmhalClkDomain_t *currCd = &pmhalClockDomainElems[cdId];
        modId = PMHAL_PRCM_MOD_UNDEF;
        if (iter < PMUtilsGetNumModsInCd(cdId))
        {
            modId = currCd->pFirstModPtr[iter];
        }
        else
        {
            modId = PMHAL_PRCM_MOD_UNDEF;
        }
    }
    return modId;
}

uint32_t PMUtilsGetNumCdsInPd(pmhalPrcmPdId_t pdId)
{
    uint32_t num;
    if ((pdId <= PMHAL_PRCM_PD_LOWER_BOUND) || (pdId >= PMHAL_PRCM_PD_COUNT))
    {
        num = 0U;
    }
    else
    {
        /* Get the total number of clock domains in the PD. This is specifically
         * useful when trying to turn off a power domain by looking at
         * all the clock domains in the power domain.
         */
        const pmhalPowerDomain_t *currPd = &pmhalPowerDomainElems[pdId];
        num = currPd->numClockDomain;
    }
    return num;
}

pmhalPrcmCdId_t PMUtilsGetClockDomInPd(pmhalPrcmPdId_t pdId,
                                       uint32_t        iter)
{
    pmhalPrcmCdId_t cdId = PMHAL_PRCM_CD_COUNT;
    if (!((pdId <= PMHAL_PRCM_PD_LOWER_BOUND) || (pdId >= PMHAL_PRCM_PD_COUNT)))
    {
        /* From the given power domain ID and the iteration number find first
         * if the index is lesser than the number of CDs in the power domain
         * and return the clock domain ID for that particular index.
         * By default the cdId = PMHAL_PRCM_CD_COUNT which is an invalid count
         * which is returned when the index in not its bounds.
         */
        const pmhalPowerDomain_t *currPd = &pmhalPowerDomainElems[pdId];
        if (iter < PMUtilsGetNumCdsInPd(pdId))
        {
            cdId = currPd->clockDomainId[iter];
        }
    }
    return cdId;
}

pmErrCode_t PMUtilsIsResetIdValid(pmhalPrcmResetGroupId_t rstId,
                                  pmhalPrcmPdId_t         pdId)
{
    const pmhalPowerDomain_t *currPd;
    uint32_t i         = 0U;
    pmErrCode_t status = PM_INPUT_PARAM_BAD_RESET_ID;
    if (!((pdId <= PMHAL_PRCM_PD_LOWER_BOUND) || (pdId >= PMHAL_PRCM_PD_COUNT)))
    {
        /* For the given power domain loop through the reset IDs contained in
         * power domain and check if the given reset ID belongs to that power
         * domain.
         */
        currPd = &pmhalPowerDomainElems[pdId];
        for (i = 0U; i < currPd->numResetDomain; i++)
        {
            if (rstId == currPd->resetId[i])
            {
                status = PM_SUCCESS;
                break;
            }
        }
    }
    return status;
}

pmhalPrcmModuleId_t PMUtilsGetModuleId(pmhalPrcmModuleId_t x)
{
    pmhalPrcmModuleId_t y = PMHAL_PRCM_MOD_UNDEF;
    /* The module ID falls in the node ID list. In order to index the module
     * element array the index is converted to a value between 0 and the number
     * of modules to index into the module elements array.
     */
    if (x < PMHAL_PRCM_MOD_COUNT)
    {
        y = ((pmhalPrcmModuleId_t) ((x) - (PMHAL_PRCM_MOD_LOWER_BOUND
                                           + 1U)));
    }
    return y;
}

pmhalPrcmNodeId_t PMUtilsGetDpllId(pmhalPrcmNodeId_t x)
{
    /* The DPLL ID falls in the node ID list. In order to index the DPLL
     * element array the index is converted to a value between 0 and the number
     * of DPLLs to index into the DPLL elements array.
     */
    return ((pmhalPrcmNodeId_t) ((x) - PMHAL_PRCM_DPLL_MIN));
}

pmhalPrcmNodeId_t PMUtilsGetMuxId(pmhalPrcmNodeId_t x)
{
    /* The Mux ID falls in the node ID list. In order to index the Mux
     * element array the index is converted to a value between 0 and the number
     * of Muxes to index into the Mux elements array.
     */
    return ((pmhalPrcmNodeId_t) ((x) - PMHAL_PRCM_MUX_MIN));
}

pmhalPrcmNodeId_t PMUtilsGetDivId(pmhalPrcmNodeId_t x)
{
    /* The Div ID falls in the node ID list. In order to index the Divider
     * element array the index is converted to a value between 0 and the number
     * of Dividers to index into the Divider elements array.
     */
    return ((pmhalPrcmNodeId_t) ((x) - PMHAL_PRCM_DIV_MIN));
}

pmhalPrcmNodeId_t PMUtilsGetVidpllId(pmhalPrcmNodeId_t x)
{
    /* The Video PLL ID falls in the node ID list. In order to index the Video
     * PLL element array the index is converted to a value between 0 and the
     * number of Video PLLs to index into the Video PLL elements array.
     */
    return ((pmhalPrcmNodeId_t) ((x) - PMHAL_PRCM_VIDEOPLL_MIN));
}

pmhalPrcmCpuId_t PMUtilsGetCpuId(pmhalPrcmModuleId_t modId)
{
    pmhalPrcmCpuId_t    cpuIdx   = PMHAL_PRCM_CPU_ID_UNDEF;
    pmhalPrcmModuleId_t moduleId = PMUtilsGetModuleId(modId);
    /* For modules which are not CPUs the function returns the CPU_ID_UNDEF
     * enumeration. If the module is a CPU (DSP/IPU/A15/EVE) then the generic
     * ISA/CPU ID is returned. For instance for both DSP1 and DSP2 the value
     * returned is PMHAL_PRCM_CPU_ID_DSP.
     */
    if (moduleId < (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
    {
        cpuIdx = pmhalModuleElems[moduleId].cpuId;
    }
    return cpuIdx;
}

pmhalVmOppId_t PMUtilsGetOppFromClkRate(pmhalPrcmCpuId_t cpuId,
                                        uint32_t         rate)
{
    uint32_t      *oppRates     = pmhalOppModuleMaxRate[cpuId];
    pmhalVmOppId_t oppId        = PMHAL_VM_OPP_UNDEF;
    uint8_t        loopVariable = 0;
    /* Each clock rate for a given CPU is associated with an OPP value such that
     * if the clock rate is lesser than or equal to that particular OPP
     * frequency but is higher than the lower OPP frequency the OPP of that CPU
     * is the one for which this condition is true.
     */
    while ((loopVariable < (uint8_t) PMHAL_VM_OPP_MAX))
    {
        if (oppRates[loopVariable] >= rate)
        {
            oppId = (pmhalVmOppId_t) loopVariable;
            break;
        }
        loopVariable++;
    }
    return oppId;
}

pmhalPrcmVdId_t PMUtilsGetCpuVdId(pmhalPrcmModuleId_t modId)
{
    pmhalPrcmCdId_t cdId;
    pmhalPrcmPdId_t pdId;
    pmhalPrcmVdId_t vdId;
    cdId = PMUtilsGetCdId(modId);
    pdId = PMUtilsGetPdId(cdId);
    vdId = PMUtilsGetVdId(pdId);
    return vdId;
}

pmhalPrcmModuleId_t PMUtilsGetModIdForCpuId(pmhalPrcmCpuId_t cpuId)
{
    pmhalPrcmModuleId_t moduleId = PMHAL_PRCM_MOD_UNDEF;
    /* For a given CPU ID return the corresponding first module ID. For instance
     * if the CPU ID is PMHAL_PRCM_CPU_ID_DSP the API returns
     * PMHAL_PRCM_MOD_DSP1 and not PMHAL_PRCM_MOD_DSP2
     */
    if ((cpuId >= PMHAL_PRCM_CPU_ID_MIN) && (cpuId < PMHAL_PRCM_CPU_ID_COUNT))
    {
        moduleId = pmhalCpuModuleId[cpuId];
    }
    return moduleId;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
