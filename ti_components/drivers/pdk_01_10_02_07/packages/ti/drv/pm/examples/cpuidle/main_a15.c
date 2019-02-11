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
 *  \file main_a15host.c
 *
 *  \brief A15 CPU Idle Example Application
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
#include <ti/csl/csl_wd_timer.h>
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
#define MPU_IRQ_40                      (40)

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

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t gCntValue = 10;
static volatile uint32_t gXbarInst = 35;
int32_t gTestStatus = STW_SOK;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void CpuIdleTest(void)
{
    pmErrCode_t status;
    uint32_t    i;

    /*Set PRCM for Timer4 */
    /*This is done in SBL, adding here to make the app standalone */
    TimerPRCMConfigure();
    TimerRun();

    /* Set MPU_PD to Retention */
    PMHALPdmSetPDState(PMHAL_PRCM_PD_MPU, PMHAL_PRCM_PD_STATE_RETENTION,
                       PM_TIMEOUT_NOWAIT);
    PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_MPU,
                          PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                          PM_TIMEOUT_NOWAIT);

    PMLIBCpu1ForcedOff();

    for (i = 0; i < 10; i++)
    {
        AppUtils_printf("\r\nEnter Idle");

        status = PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
        {
            /* For Profiling */
            int32_t timeCnt = 0;
            int32_t cycles  = 0;
            timeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
            cycles = timeCnt - (int32_t) TIMER_RLD_COUNT;
            AppUtils_printf("\r\nTime Taken to Wakeup:%d",cycles);
        }

        if (status == PM_SUCCESS)
        {
            AppUtils_printf("\r\nEnter Targeted Power State successfully");
        }
        else
        {
            AppUtils_printf("\r\nEnter Targeted Power State failed");
            gTestStatus = STW_EFAIL;
            break;
        }
        AppUtils_printf("\r\nExit Idle");
    }
    TimerStop();
    AppUtils_printf("\r\nTest Completed!!");
}

int main(void)
{
    AppUtils_defaultInit();
    AppUtils_printf("\r\nPM CPUIdle Test Application");

    /*stop the wdtimer*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

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
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Enable the Timer4 wakeup event */
    TIMERWakeEnable(SOC_TIMER4_BASE, TIMER_WAKE_OVF_FLAG);

    /* Set the Timer4 to Smart-idle mode */
    TIMERIdleModeConfigure(SOC_TIMER4_BASE, TIMER_SMART_IDLE);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);
}

static void TimerStop(void)
{
    /* Stop the Timer */
    TIMERDisable(SOC_TIMER4_BASE);

    /* Disable the Timer4 wakeup event */
    TIMERWakeDisable(SOC_TIMER4_BASE, TIMER_WAKE_OVF_FLAG);

    /* Unregister Timer4 interrupts */
    TimerIntcDeInit();
}

/*
** Do the necessary Timer configurations on to INTC.
*/
static void TimerIntcInit(void)
{
    /* Configure the Xbar with interrupt source */
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,gXbarInst,CSL_XBAR_TIMER4_IRQ);

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(MPU_IRQ_40, TimerIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(MPU_IRQ_40, 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(MPU_IRQ_40);
}

/*
** Disable the interrupt configurations on INTC.
*/
static void TimerIntcDeInit(void)
{
    /* Restore the initial state of gCntValue */
    gCntValue = 10;

    /* Disable the timer interrupt */
    Intc_SystemDisable(MPU_IRQ_40);

    /* Unregister the interrupt */
    Intc_IntUnregister(MPU_IRQ_40);
}

/*
** Setup the timer for one-shot and compare mode.
*/
static void TimerSetUp(void)
{
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, TIMER_FREE);

    /* Load the counter with the initial count value */
    TIMERCounterSet(SOC_TIMER4_BASE, TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    TIMERReloadSet(SOC_TIMER4_BASE, TIMER_RLD_COUNT);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE, TIMER_AUTORLD_NOCMP_ENABLE);
}

/*
** Timer interrupt service routine. This will send a character to serial
** console.
*/
static void TimerIsr(void *handle)
{
    /* Disable the Timer interrupts */
    TIMERIntDisable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Clear the status of the interrupt flags */
    TIMERIntStatusClear(SOC_TIMER4_BASE, TIMER_INT_OVF_IT_FLAG);

    /* Enable the Timer interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);
}

/*
** Timer4 PRCM configuration. This will explicitly enable the Timer4 module.
*/
static void TimerPRCMConfigure(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL, 0x2);

    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_TIMER4_CLKCTRL) & (0x00030000)) != 0x0) ;
}

