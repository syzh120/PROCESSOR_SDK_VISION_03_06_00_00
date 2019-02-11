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
 * \file    pmlib_cpuidle_m4.c
 *
 * \brief   This file declares the interface for IPU CPU Idle functionality.
 *          This is a low latency power saving mode which allows fast wakeup
 *          depending on the power mode set.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_mmu.h>
#include "pmhal_prcm.h"
#include "pmlib_cpuidle.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include "pmhal_rm.h"
#include "pmhal_pdm.h"
#include "pm_utils.h"
#include "pmlib_cpuidle_utils_m4.h"

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

pmErrCode_t PMLIBCpuIdle(pmhalPrcmPdState_t pwrst)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (pwrst < PMHAL_PRCM_PD_STATUS_COUNT)
    {
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                      CTRL_CORE_MMR_LOCK_1, CTRL_CORE_MMR_LOCK_1,
                      CTRL_CORE_MMR_LOCK_1_TOUNLOCK);

        /*
         * PRCM Override should be removed to allow the IPU to go to low power
         * state.
         */
        HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_IPU_WAKEUP,
                      CTRL_CORE_SEC_IPU_WAKEUP_WKUP_EN,
                      0x00);
#endif

        /* Set IPU in deep sleep to set CM standby */
        HW_WR_FIELD32(SOC_IPU1_C0_INTC_BASE + IPU_M4_NVIC_SYSTEM_CONTROL,
                      IPU_M4_NVIC_SYSTEM_CONTROL_SLEEPDEEP,
                      0x01);

        HW_WR_FIELD32(SOC_IPU1_MMU_BASE + IPU_MMU_SYSCONFIG,
                      IPU_MMU_SYSCONFIG_IDLEMODE,
                      IPU_MMU_SYSCONFIG_IDLEMODE_SSIDLE);

        HW_WR_FIELD32(SOC_IPU1_MMU_BASE + IPU_MMU_SYSCONFIG,
                      IPU_MMU_SYSCONFIG_AUTOIDLE,
                      IPU_MMU_SYSCONFIG_AUTOIDLE_AUTOCLKGATE);

        /* setStandBy_Core_sysconfig  */
        HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_STANDBY_CORE_SYSCONFIG,
                      IPU_STANDBY_CORE_SYSCONFIG_STANDBYMODE,
                      0x3);

        /* setIdle_Core_sysconfig */
        HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_IDLE_CORE_SYSCONFIG,
                      IPU_IDLE_CORE_SYSCONFIG_IDLEMODE,
                      0x3);

        PmlibDoWFI();
    }
    else
    {
        retVal = PM_BADARGS;
    }

    return retVal;
}

pmErrCode_t PMLIBCpuModePrepare(pmhalPrcmModuleId_t moduleId,
                                pmlibCpuIdleMode_t  mode)
{
    pmErrCode_t              retVal;
    pmhalPrcmPdState_t       pdState;
    pmhalPrcmCdClkTrnModes_t cdMode;
    pmhalPrcmPdId_t          pdId;
    pmhalPrcmCdId_t          cdId;
    pmhalPrcmCpuId_t         cpuId;

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
        pdState = PMHAL_PRCM_PD_STATE_ON_ACTIVE;
        cdMode  = PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO;
        retVal  = PM_SUCCESS;
    }
    else if (mode == PMLIB_IDLE_CPU_MODE_OFF)
    {
        retVal = PM_BADARGS;
        /* Set CPU to Off mode while execuiting Idle instruction
         */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU2
        if (moduleId == PMHAL_PRCM_MOD_IPU2)
        {
            /* IPU2 is a part of PD_CORE which cannot be turned off */
            pdState = PMHAL_PRCM_PD_STATE_ON_ACTIVE;
            retVal = PM_SUCCESS;
        }
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
        if (moduleId == PMHAL_PRCM_MOD_IPU1)
        {
            /* IPU1 is a part of PD_IPU which can be turned off */
            pdState = PMHAL_PRCM_PD_STATE_OFF;
            retVal = PM_SUCCESS;
        }
#endif
        cdMode = PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO;
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
            cdId = PMUtilsGetCdId(moduleId);
            pdId = PMUtilsGetPdId(cdId);
            if ((moduleId == PMHAL_PRCM_MOD_IPU1) &&
                (mode != PMLIB_IDLE_CPU_MODE_OFF))
            {
                PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU,
                                      PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                      PM_TIMEOUT_NOWAIT);
            }

            /* Enable CPU Power/Clock domain to configure to next power state */
            retVal = (pmErrCode_t) PMHALPdmSetPDState(pdId, pdState,
                                                      PM_TIMEOUT_NOWAIT);
            if (retVal == PM_SUCCESS)
            {
                retVal = (pmErrCode_t) PMHALCMSetCdClockMode(cdId, cdMode,
                                                             PM_TIMEOUT_NOWAIT);
            }

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
            if (retVal == PM_SUCCESS)
            {
                /*
                 * This is required as the force override bit
                 * CTRL_CORE_SEC_IPU_WAKEUP
                 * does not set the right values for the PRCM registers and when
                 * the override is lifted then cores are left in a bad power and
                 * reset state.
                 */
                PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                                  PM_TIMEOUT_NOWAIT);
                PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST, PM_TIMEOUT_NOWAIT);
                PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                   PMHAL_PRCM_MODULE_MODE_AUTO,
                                   PM_TIMEOUT_NOWAIT);
            }
#endif
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    return retVal;
}

/* None */

