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
 * \file    pmlib_cpuidle_a15host.c
 *
 * \brief   This file declares the interface for MPU CPU Idle functionality.
 *          This is a low latency power saving mode which allows fast wakeup
 *          depending on the power mode set.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include "pmhal_pdm.h"
#include "pmhal_mpu_lprm.h"
#include "pmlib_cpuidle.h"
#include "pmlib_cpuidle_utils_a15host.h"
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

/**
 * \brief  Disable SMP Bit on MPU CPU 0
 *         This asm code is to disable SMP bit on MPU CPU 0
 *
 * \param  none
 *
 * \return none
 */
static void PmLibDisableSMPBitMPUCPU0(void);

/**
 * \brief  signal EVT to boot MPU CPU 1
 *         This asm code is to signal EVT to boot MPU CPU 1
 *
 * \param  none
 *
 * \return none
 */
static void PmLibSignalEVTToBootMPUCPU1(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMLIBCpuIdle(pmhalPrcmPdState_t pwrst)
{
    uint32_t           coreId;
    pmhalPrcmPdState_t preState;
    pmErrCode_t        status = PM_SUCCESS;

    if (pwrst < PMHAL_PRCM_PD_STATUS_COUNT)
    {
        /* CPU0 = 0 & CPU1 = 1 */
        coreId = CSL_a15ReadCoreId() & 0x1U;

        /*
         * Note: It is a system/application decision whether to use Mercury (HG)
         * retention. Mercury retention is disabled by default.
         * For TDA2xx, the SBL will set HG (mercury retention) and enable HG
         * fast wakeup. The CPUIdle function will not change this system
         * setting.
         *
         * MPU CPU0/1
         * - Ensure CM_CPU0/1_CLKSTCTRL.CLKTRCTRL is set to HW_AUTO
         * - Set PM_CPU0/1_PWRSTCTRL.POWERSTATE to desired low power state
         * - Execute DSB instruction
         * - Execute WFI instruction
         *
         * MPU_PRCM power state after WFI:
         * - If MPU_CPU1 is also in WFI then MPU_PRCM power state is CSWRET
         * - Otherwise, MPU_PRCM power state is ON.
         *   - In this state the A15 internal clock is off providing the power
         *     saving.
         *
         * Note: If TDA2xx exposes only MPU_CPU0, then the MPU_CPU1 will be in
         * Forced off state; the SBL is expected to put CPU0 in forced off
         * state.
         * In this case, calling CPUIdle for CPU0 should result in the MPU_PRCM
         * state of CSWRET providing better power saving.
         */
        PMHALMpuLprmSetPowerMode(coreId, pwrst);
        PMHALMpuLprmSetClockMode(coreId, PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO);
        PMHALMpuLprmSetLastPowerState(coreId, PMHAL_PRCM_PD_STATE_ON_ACTIVE);

        PmlibDoWFI();

        PMHALMpuLprmSetPowerMode(coreId, PMHAL_PRCM_PD_STATE_ON_ACTIVE);
        PMHALMpuLprmGetLastPowerState(coreId, &preState);
        if (preState != pwrst)
        {
            /* Did Not hit the targeted power state. */
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

void PMLIBCpu1ForcedOff(void)
{
    uint32_t cpuId;
    /*
     * Disable all WUGEN Events on CPU1
     */
    MPU_WUGEN_1_DisableAll();

    /*
     * Configure CPU1 Power State to FORCE_OFF
     */
    cpuId = 1U;
    PMHALMpuLprmSetForceOff(cpuId);
    PMHALMpuLprmSetPowerMode(cpuId, PMHAL_PRCM_PD_STATE_OFF);
    PMHALMpuLprmSetClockMode(cpuId, PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO);

    PmLibDisableSMPBitMPUCPU0();

    /*
     * Configure CPU1 boot address and boot status
     */
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_AUX_CORE_BOOT_1, PmlibCpu1Boot);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_AUX_CORE_BOOT_0, 0xFF);

    PmLibSignalEVTToBootMPUCPU1();
}

pmErrCode_t PMLIBCpuModePrepare(pmhalPrcmModuleId_t moduleId,
                                pmlibCpuIdleMode_t  mode)
{
    pmErrCode_t                retVal;
    pmhalPrcmPdState_t         pdState;
    pmhalPrcmCdClkTrnModes_t   cdMode;
    pmhalPrcmPdId_t            pdId;
    pmhalPrcmCdId_t            cdId;
    pmhalPrcmCpuId_t           cpuId;
    pmhalMpuLprmHgRampParams_t hgRampParam = {1, 0};

    if (mode == PMLIB_IDLE_CPU_MODE_IDLE)
    {
        /* Set CPU to IDLE mode while execuiting Idle instruction */
        pdState = PMHAL_PRCM_PD_STATE_ON_ACTIVE;
        cdMode  = PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP;
        retVal  = PM_SUCCESS;
    }
    else if (mode == PMLIB_IDLE_CPU_MODE_AUTOCG)
    {
        /* Set CPU to ClockGate mode while execuiting Idle instruction */
        pdState = PMHAL_PRCM_PD_STATE_RETENTION;
        cdMode  = PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO;
        retVal  = PM_SUCCESS;
    }
    else if (mode == PMLIB_IDLE_CPU_MODE_OFF)
    {
        /* Set CPU to Off mode while execuiting Idle instruction
         * In case of MPU doesn't support CPU_MODE_OFF mode.
         */
        pdState = PMHAL_PRCM_PD_STATE_RETENTION;
        cdMode  = PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO;
        retVal  = PM_SUCCESS;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (retVal == PM_SUCCESS)
    {
        /* Get the CPU id for the given module id */
        cpuId = PMUtilsGetCpuId(moduleId);

        /* Verify that module id belongs to CPU clock domain */
        if (cpuId != PMHAL_PRCM_CPU_ID_UNDEF)
        {
            cdId = PMUtilsGetCdId((pmhalPrcmModuleId_t) moduleId);
            pdId = PMUtilsGetPdId(cdId);

            /* Enable Hg/FastRamp-up in Retention */
            PMHALMpuLprmSetHgRampParams(&hgRampParam);
            PMHALMpuLprmSetMercuryRetention();

            /* Enable CPU Power/Clock domain to configure to next power state */

            retVal = (pmErrCode_t) PMHALPdmSetPDState(pdId, pdState,
                                                      PM_TIMEOUT_NOWAIT);
            if (retVal == PM_SUCCESS)
            {
                retVal = (pmErrCode_t) PMHALCMSetCdClockMode
                             (cdId, cdMode, PM_TIMEOUT_NOWAIT);
            }
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
static void PmLibDisableSMPBitMPUCPU0(void)
{
    /*
     * Disable SMP bit on CPU0
     */
    asm (" mrc   p15, 0, r0, c1, c0, 1");
    asm (" bic   r0, r0, #(1 << 6)");
    asm (" mcr   p15, 0, r0, c1, c0, 1");

    /*
     * Execute an ISB instruction to ensure that all of the
     * CP15 register changes have been committed.
     */
    asm (" isb");
}

static void PmLibSignalEVTToBootMPUCPU1(void)
{
    /*
     * Signal EVT to boot CPU1
     */
    asm (" DSB");
    asm (" SEV");
}

/* None */

