/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file main_m4.c
 *
 *  \brief M4 CPU Idle Example Application
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/cslr_cache.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/pmlib_boardconfig.h>
#include <ti/drv/pm/include/pmlib_cpuidle.h>
#include <ti/drv/pm/include/prcm/hw_pmhal_data_names.h>
#include <ti/drv/pm/include/prcm/pmhal_pdm.h>
#include <ti/drv/pm/include/prcm/pmhal_cm.h>
#include <ti/drv/pm/include/prcm/pmhal_mm.h>
#include <ti/drv/pm/include/prcm/pmhal_rm.h>
#include "app_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TIMER_INITIAL_COUNT             (0xFFF00000U)
#define TIMER_RLD_COUNT                 (0xFFF00000U)
#define IPU_IRQ_54                      (uint16_t) (54)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TimerPRCMConfigure(void);
static void TimerIntcInit(void);
static void TimerIntcDeInit(void);
static void TimerSetUp(void);
static void TimerIsr(void *handle);
static void TimerRun(void);
static void TimerStop(void);
static void CpuIdleTest(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t gXbarInst = 35U;
int32_t gTestStatus = STW_SOK;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void CpuIdleTest(void)
{
    uint32_t           i;
    int32_t            retVal    = PM_SUCCESS;
    pmhalPrcmPdState_t lastState = PMHAL_PRCM_PD_STATE_ON_ACTIVE;

    /*Set PRCM for Timer4 */
    /*This is done in SBL, adding here to make the app standalone */

    TimerPRCMConfigure();
    TimerRun();

    /* Enable UNICACHE for IPU*/
    /* If using gels form vision sdk please enable default conf in
     *  DRA7xx_multicore_reset    */

    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE + IPU_UNICACHE_CONFIG,
                  IPU_UNICACHE_CONFIG_BYPASS,
                  IPU_UNICACHE_CONFIG_BYPASS_NORMAL);

    /* Set IPU_PD to On Active
     * Lets not put IPU  to PD retention as ipu being the master core in
     * VisionSDK  */

    retVal = (int32_t) PMHALPdmSetPDState(PMHAL_PRCM_PD_IPU,
                                          PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                          PM_TIMEOUT_NOWAIT);

    retVal += (int32_t) PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU,
                                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                              PM_TIMEOUT_NOWAIT);

    retVal += (int32_t) PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU1,
                                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                              PM_TIMEOUT_NOWAIT);
#if defined (SOC_TDA3XX)
    /*
     * This is required as the force override bit CTRL_CORE_SEC_IPU_WAKEUP
     * does not set the right values for the PRCM registers and when the
     * override is lifted then cores are left in a bad power and reset state.
     */
    PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST, PM_TIMEOUT_NOWAIT);
    PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST, PM_TIMEOUT_NOWAIT);
    retVal += (int32_t) PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                           PMHAL_PRCM_MODULE_MODE_AUTO,
                                           PM_TIMEOUT_NOWAIT);
#endif

    retVal += (int32_t) PMHALPdmSetLastPDStatus(PMHAL_PRCM_PD_IPU,
                                                PMHAL_PRCM_PD_STATE_ON_ACTIVE);

    PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);

    if (PM_SUCCESS != retVal)
    {
        AppUtils_printf(" \r\n Clock settings failed ");
        gTestStatus = STW_EFAIL;
    }

    for (i = 0U; i < 10U; i++)
    {
        AppUtils_printf("\r\nEnter Idle");
        retVal = (int32_t) PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
        AppUtils_printf("\r\nExit Idle");
        retVal = (int32_t) PMHALPdmGetLastPDStatus(PMHAL_PRCM_PD_IPU,
                                                   &lastState);

        if (PMHAL_PRCM_PD_STATE_ON_ACTIVE == lastState)
        {
            AppUtils_printf("\r\nEnter Targeted Power State successfully\r\n");
        }
        else
        {
            AppUtils_printf("\r\nEnter Targeted Power State failed");
            gTestStatus = STW_EFAIL;
            break;
        }
    }
    TimerStop();
    AppUtils_printf("\r\nTest Completed!!");
}

int main(void)
{
    AppUtils_defaultInit();
    AppUtils_printf("\r\nPM CPUIdle Test Application");

    /* Function to Test CPU Idle */
    CpuIdleTest();

    if (gTestStatus == STW_SOK)
    {
        AppUtils_printf("\r\nPM CPUIdle Test Pass");
    }
    else
    {
        AppUtils_printf("\r\nPM CPUIdle Test Fail");
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void TimerRun(void)
{
    /* Register Timer4 interrupts on to INTC */
    TimerIntcInit();

    /* Perform the necessary configurations for Timer4 */
    TimerSetUp();

    /* Enable the Timer4 interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, (uint32_t) TIMER_INT_OVF_EN_FLAG);

    /* Enable the Timer4 wakeup event */
    TIMERWakeEnable(SOC_TIMER4_BASE, (uint32_t) TIMER_WAKE_OVF_FLAG);

    /* Set the Timer4 to Smart-idle mode */
    TIMERIdleModeConfigure(SOC_TIMER4_BASE, (uint32_t) TIMER_SMART_IDLE);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);
}

static void TimerStop(void)
{
    /* Stop the Timer */
    TIMERDisable(SOC_TIMER4_BASE);

    /* Disable the Timer4 wakeup event */
    TIMERWakeDisable(SOC_TIMER4_BASE, (uint32_t) TIMER_WAKE_OVF_FLAG);

    /* Unregister Timer4 interrupts */
    TimerIntcDeInit();
}

/*
** Do the necessary Timer configurations on to INTC.
*/
static void TimerIntcInit(void)
{
    /* Configure the Xbar with interrupt source */
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,gXbarInst,CSL_XBAR_TIMER4_IRQ);

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(IPU_IRQ_54, (IntrFuncPtr) TimerIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(IPU_IRQ_54, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(IPU_IRQ_54);
}

/*
** Disable the interrupt configurations on INTC.
*/
static void TimerIntcDeInit(void)
{
    /* Disable the timer interrupt */
    Intc_SystemDisable(IPU_IRQ_54);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_IRQ_54);
}

/*
** Setup the timer for one-shot and compare mode.
*/
static void TimerSetUp(void)
{
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, (uint32_t) TIMER_FREE);

    /* Load the counter with the initial count value */
    TIMERCounterSet(SOC_TIMER4_BASE, TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    TIMERReloadSet(SOC_TIMER4_BASE, TIMER_RLD_COUNT);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE, (uint32_t) TIMER_AUTORLD_NOCMP_ENABLE);
}

/*
** Timer interrupt service routine. This will send a character to serial
** console.
*/
static void TimerIsr(void *handle)
{
    /* Disable the Timer interrupts */
    TIMERIntDisable(SOC_TIMER4_BASE, (uint32_t) TIMER_INT_OVF_EN_FLAG);

    /* Clear the status of the interrupt flags */
    TIMERIntStatusClear(SOC_TIMER4_BASE, (uint32_t) TIMER_INT_OVF_IT_FLAG);

    /* Enable the Timer interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, (uint32_t) TIMER_INT_OVF_EN_FLAG);
}

/*
** Timer4 PRCM configuration. This will explicitly enable the Timer4 module.
*/
static void TimerPRCMConfigure(void)
{
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER4,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
}

