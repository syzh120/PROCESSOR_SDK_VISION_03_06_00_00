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
 * \file    pmlib_cpuidle_c66x.c
 *
 * \brief   This file declares the interface for DSP CPU Idle functionality.
 *          This is a low latency power saving mode which allows fast wakeup
 *          depending on the power mode set.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include "c6x.h"
#include <ti/csl/arch/csl_arch.h>
#include "pm_types.h"
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include "pmhal_sd.h"
#include "pmhal_pdm.h"
#include "pmlib_cpuidle.h"
#include "pm_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< \brief Macro to give the address of the DSP XMC XPFCMD register */
#define DSP_XPFCMD                                         (0x00000300U)

/**< \brief Macro to give the address of the DSP XMC XPFACS register */
#define DSP_XPFACS                                         (0x00000304U)

/**< \brief Macro to give the Shift of the Invalidate Prefetch bit in the
 *          XPFCMD register.
 */
#define DSP_XPFCMD_INV_SHIFT                               (0U)

/**< \brief Macro to give the Mask of the Invalidate Prefetch bit in the
 *          XPFCMD register.
 */
#define DSP_XPFCMD_INV_MASK                                (0x00000001U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief Execute IDLE instruction.
 *
 *        This function is called by CPU Idle API to execute IDLE.
 *
 * \param none
 *
 * \return none
 **/
static void PmlibDoWFI(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMLIBCpuIdle(pmhalPrcmPdState_t pwrst)
{
    pmErrCode_t status = PM_SUCCESS;

    if (pwrst < PMHAL_PRCM_PD_STATUS_COUNT)
    {
        uint32_t regVal = 0U;
        pmhalPrcmModuleMStbyMode_t lastStandbyState =
            PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY;
        /* Read the value of the DSP SYSCONFIG register before modification */
        regVal = HW_RD_REG32(SOC_DSP_SYSTEM_BASE + DSP_SYSCONFIG);
        /* Configure the DSP SYSCONFIG to SMART_STANDBY_WKUP mode */
        HW_WR_FIELD32(SOC_DSP_SYSTEM_BASE + DSP_SYSCONFIG,
                      DSP_SYSCONFIG_STANDBYMODE,
                      DSP_SYSCONFIG_STANDBYMODE_SMART_STANDBY_WKUP);

        /* Perform the DSP Idle sequence */
        PmlibDoWFI();

        /* After coming out of low power state find the original configuration
         * of the standby state and reprogram.
         */
        lastStandbyState = (pmhalPrcmModuleMStbyMode_t) HW_GET_FIELD(
            regVal, DSP_SYSCONFIG_STANDBYMODE);
        HW_WR_FIELD32(SOC_DSP_SYSTEM_BASE + DSP_SYSCONFIG,
                      DSP_SYSCONFIG_STANDBYMODE,
                      lastStandbyState);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

void PMLIBSetCorepacPowerDown(uint32_t enable)
{
    /* By setting the MEGPD bit to 1 in the PDCCMD register, the
     * C66x CorePac global static power-down mode is enabled; when the MEGPD
     * register is set to 1, the C66x CorePac global static power-down mode
     * is activated when the DSP enters the idle state.
     */
    if (1U == enable)
    {
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_PDCCMD, DSP_PDCCMD_MEGPD, 1U);
        while (HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_PDCCMD,
                             DSP_PDCCMD_MEGPD) != 1U)
        {
            ;
        }
    }
    else
    {
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_PDCCMD, DSP_PDCCMD_MEGPD, 0U);
        while (HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_PDCCMD,
                             DSP_PDCCMD_MEGPD) != 0U)
        {
            ;
        }
    }
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
        /* CorePac needs to be powered down to achieve auto clock gate */
        PMLIBSetCorepacPowerDown(1U);
        /* Set CPU to ClockGate mode while execuiting Idle instruction */
        pdState = PMHAL_PRCM_PD_STATE_ON_ACTIVE;
        cdMode  = PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO;
        retVal  = PM_SUCCESS;
    }
    else if (mode == PMLIB_IDLE_CPU_MODE_OFF)
    {
        /* CorePac needs to be powered down to achieve cpu off */
        PMLIBSetCorepacPowerDown(1U);
        /* Set CPU to Off mode. */
        pdState = PMHAL_PRCM_PD_STATE_OFF;
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
            cdId = PMUtilsGetCdId(moduleId);
            if (cdId != PMHAL_PRCM_CD_COUNT)
            {
                pdId = PMUtilsGetPdId(cdId);

                PMHALStaticDepDisableToAllMaster(cdId, 0x00);
                PMHALStaticDepDisableAllSlaveDep(cdId);
                if (pdId != PMHAL_PRCM_PD_COUNT)
                {
                    /* Enable CPU Power/Clock domain to configure to next power state */
                    retVal = (pmErrCode_t) PMHALPdmSetPDState(pdId, pdState,
                                                            PM_TIMEOUT_NOWAIT);
                }
            }
            if ((retVal == PM_SUCCESS) && (cdId != PMHAL_PRCM_CD_COUNT))
            {
                retVal = (pmErrCode_t) PMHALCMSetCdClockMode(cdId, cdMode,
                                                             PM_TIMEOUT_NOWAIT);
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
/* The following sections are placed in the DSP L2 RAM to ensure that when the
 * DSP is going to power down state the DSP XMC does not prefetch any more
 * instructions from the external memories outside the DSP subsystem.
 */
#ifdef __cplusplus
#pragma CODE_SECTION(".pmIdleFunc")
#else
#pragma CODE_SECTION(PmlibDoWFI, ".pmIdleFunc")
#endif
static void PmlibDoWFI(void)
{
    /* The MFENCE instruction stalls the instruction fetch pipeline until
     * the memory system busy flag goes low.
     * Invalidate prefetch buffer contents.
     * INV = 1 invalidates both program and data prefetch buffers.
     * When invalidating the prefetch buffers, XMC blocks all incoming requests
     * until the prefetch buffers are completely idle. XMC waits for all
     * outstanding hits to resolve and all outstanding prefetches to return.
     * Once idle, XMC returns both buffers to their reset state.
     */
    asm (
        "IDLE_STEP:     ; Each fetch packet contains 8 instructions             \n"
        "               ; fetch packet 1                                        \n"
        "               STW         B5, *SP--(8); allocate 8 bytes on stack     \n"
        "               STW         B4, *+SP(4) ; save B4, B5                   \n"
        "               dint                    ; Disable Interrupts GIE = 0    \n\t"
        "               mfence                  ; Stall Prefetch Pipeline       \n\t"
        "               mvk         0x0300,b5   ; Get the XPFCMD address        \n\t"
        "               mvkh        0x8000000,b5                                \n\t"
        "           ||  mvk         1,b4        ; Set INV = 1                   \n\t"
        "               stw         b4,*b5[0]                                   \n\t"
        "               ; fetch packet 2                                        \n"
        "               ldw         *+B5[4],B5  ; Read XPFACS                   \n\t"
        "               ; idle the CPU with a simultaneous interrupt enable     \n\t"
        "               ; (GIE=1)                                               \n\t"
        "               mvc csr, b4                                             \n\t"
        "               or 1, b4, b4            ; set GIE                       \n\t"
        "               mvc b4, csr             ; Parallel Execution of Setting \n\t"
        "           ||  idle                    ; GIE And IDLE instruction      \n\t"
        "               LDW         *+SP(4),  B4; restore B4, B5, SP            \n"
        "               LDW         *++SP(8), B5                                \n"
        "               ; last instr in fetch packet: RETNOP instr from func    \n"
        );
}

