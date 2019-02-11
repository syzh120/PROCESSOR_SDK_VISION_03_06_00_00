/*
 * Copyright (c) 2012-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 *  ======== Watchdog.c ========
 *
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Types.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/interfaces/ITimer.h>
#include <ti/sysbios/timers/dmtimer/Timer.h>

#ifdef DSP
#include <ti/sysbios/family/c64p/Hwi.h>
#ifdef OMAP5
#include <ti/sysbios/family/c64p/tesla/Wugen.h>
#endif
#endif

#ifdef IPU
#include <ti/sysbios/family/arm/m3/Hwi.h>
#endif

#ifdef SMP
#include <ti/sysbios/hal/Core.h>
#endif

#include <ti/pm/IpcPower.h>

#include "package/internal/Watchdog.xdc.h"

/* Macro to write to GP timer registers */
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Bit mask for writing into GP timer TGRR reg for posted write mode */
#define WATCHDOG_TIMER_TWPS_W_PEND_TGRR     0x8

/* Bit mask for writing into GP timer TLDR reg for posted write mode */
#define WATCHDOG_TIMER_TWPS_W_PEND_TLDR     0x4

/* Bit mask for writing into GP timer TCRR reg for posted write mode */
#define WATCHDOG_TIMER_TWPS_W_PEND_TCRR     0x2

/* Bit mask for writing into GP timer TCLR reg for posted write mode */
#define WATCHDOG_TIMER_TWPS_W_PEND_TCLR     0x1

/* GP Timers Clock Control register bit mask */
#define WATCHDOG_WDT_CLKCTRL_IDLEST_MASK    (3 << 16)

#if defined(IPU) && defined(OMAP5)
/* OMAP IDCode Register to find the version id, 0x4A002204 */
#define IDCODE_REGISTER                     (0xAA002204)

/*
 *  ======== adjustGptClkCtrlAddr ========
 *  Adjust the GPTimer PRCM Clock Register Addresses on OMAP5 ES2.x
 */
static Void adjustGptClkCtrlAddr()
{
    Int     i;
    Bool    adjust = FALSE;
    UInt32  idCode = REG32(IDCODE_REGISTER);
    UInt32  ramp = (idCode >> 12) & 0xFFFF;
    UInt32  version = (idCode >> 28) & 0xF;

    /* Change the addresses only for OMAP5 ES2.x */
    if (ramp == 0xB942 || ramp == 0xB998) {
        if (version == 1) {
            adjust = TRUE;
        }
    }

    /*
     * OMAP5 ES 2.x has PER GPT PRCM addresses moved up by 0x400
     * w.r.t OMAP4 and OMAP5 ES 1.0
     */
    if (adjust == TRUE) {
        for (i = 0; i < Watchdog_module->wdtCores; i++) {
            Watchdog_module->device[i].clkCtrl =
                    (Ptr)((UInt32)Watchdog_module->device[i].clkCtrl - 0x400);
        }
    }
}
#endif

/*
 *  ======== initTimer ========
 */
static Void initTimer(volatile Watchdog_TimerRegs *timer, Bool boot)
{
    Timer_Handle    tHandle;
    Types_FreqHz    tFreq;

    /* Get timer frequency */
    tHandle = Timer_Object_get(NULL, 0);
    Timer_getFreq(tHandle, &tFreq);

    timer->tisr = ~0;
    timer->tier = 2;
    timer->twer = 2;
    timer->tldr = (0 - (tFreq.lo * Watchdog_TIME_SEC));

    /* Booting can take more time, so set CRR to WDT_BOOT_TIME */
    if (boot) {
        timer->tcrr = (0 - (tFreq.lo * Watchdog_BOOT_TIME_SEC));
    }
    else {
        timer->tcrr = (0 - (tFreq.lo * Watchdog_TIME_SEC));
    }

    timer->tsicr |= 4; /* enable posted write mode */
}

/*
 *  ======== Watchdog_init ========
 */
Void Watchdog_init( Void (*timerFxn)(Void) )
{
    Hwi_Params                   hwiParams;
    UInt                         key;
    Timer_Handle                 tHandle;
    Types_FreqHz                 tFreq;
    volatile Watchdog_TimerRegs  *timer;
    Int                          i;
    static __FAR__ Bool          first = TRUE;

    if (Watchdog_disableWatchdog == TRUE) {
        System_printf("Watchdog.disableWatchdog set to true. " \
                      "Set to false in config file to enable Watchdog.\n");
    }
    else {
        tHandle = Timer_Object_get(NULL, 0);
        Timer_getFreq(tHandle, &tFreq);  /* get timer frequency */

#if defined(IPU) && defined(OMAP5)
        if (first) {
            adjustGptClkCtrlAddr();
        }
#endif
        for (i = 0; i < Watchdog_module->wdtCores; i++) {  /* loop for SMP cores */
            timer = (volatile Watchdog_TimerRegs *) Watchdog_module->device[i].baseAddr;

            /* Check if timer is enabled by host-side */
            if ((REG32(Watchdog_module->device[i].clkCtrl) &
                WATCHDOG_WDT_CLKCTRL_IDLEST_MASK) ==
                                        WATCHDOG_WDT_CLKCTRL_IDLEST_MASK) {
                System_printf("Watchdog disabled: TimerBase = 0x%x ClkCtrl = 0x%x\n",
                                        timer, Watchdog_module->device[i].clkCtrl);
                continue;  /* for next core */
            }

            if (Watchdog_module->status[i] != Watchdog_Mode_ENABLED) {
                if (Watchdog_module->device[i].intNum == -1) {
                    System_printf("Watchdog timer @TimerBase = 0x%x does not have"
                                  " a valid intNum setting (it is -1). This"
                                  " timer's intNum must be set in the .cfg file\n",
                                  timer);
                    continue;
                }
#if defined(DSP)
                if (Watchdog_module->device[i].eventId == -1) {
                    System_printf("Watchdog timer @TimerBase = 0x%x does not have"
                                  " a valid eventId setting (it is -1).  This"
                                  " timer's eventId must be set in the .cfg file\n",
                                  timer);
                    continue;
                }
#endif

                /* Enable interrupt in BIOS */
                Hwi_Params_init(&hwiParams);
                hwiParams.priority = 1;
                hwiParams.eventId = Watchdog_module->device[i].eventId;
                hwiParams.maskSetting = Hwi_MaskingOption_LOWER;
                hwiParams.arg = 1;     /* Exception_handler(abortFlag) */
                key = Hwi_disable();
                Hwi_create(Watchdog_module->device[i].intNum,
                           (Hwi_FuncPtr)timerFxn, &hwiParams, NULL);

                /* Configure the timer */
                initTimer(timer, TRUE);

                Hwi_enableInterrupt(Watchdog_module->device[i].intNum);
#if defined(DSP) && defined(OMAP5)
                Wugen_enableEvent(Watchdog_module->device[i].eventId);
#endif
                Hwi_restore(key);

                /* Enable timer */
                while (timer->twps & WATCHDOG_TIMER_TWPS_W_PEND_TCLR);
                timer->tclr |= 1;
                Watchdog_module->status[i] = Watchdog_Mode_ENABLED;

#ifdef SMP
                System_printf("Watchdog enabled: TimerBase = 0x%x SMP-Core = %d "
                                            "Freq = %d\n", timer, i, tFreq.lo);
#else
                System_printf("Watchdog enabled: TimerBase = 0x%x Freq = %d\n",
                                                            timer, tFreq.lo);
#endif
            }
        }

#if defined(OMAP5) || defined(IPU)
        if (first) {
            /* Register callback function */
            if (!IpcPower_registerCallback(IpcPower_Event_RESUME, Watchdog_restore,
                                        NULL)) {
                System_printf("Watchdog_restore registered as a resume callback\n");
            }
        }
#endif
    }

    if (first) {
        first = FALSE;
    }

    return;
}

/*
 *  ======== Watchdog_idleBegin ========
 */
Void Watchdog_idleBegin(Void)
{
    Int core = 0;

#ifdef SMP
    core = Core_getId();

    if (core != 0) {
        Watchdog_stop(core);
    }
    else
#endif
    {
        Watchdog_kick(core);
    }
}

/*
 *  ======== Watchdog_swiPrehook ========
 */
Void Watchdog_swiPrehook(Swi_Handle swi)
{
    Int core = 0;

#ifdef SMP
    core = Core_getId();

    if (core != 0) {
        Watchdog_start(core);
    }
    else
#endif
    {
        Watchdog_kick(core);
    }
}

/*
 *  ======== Watchdog_taskSwitch ========
 *  Refresh/restart watchdog timer whenever task switch scheduling happens
 */
Void Watchdog_taskSwitch(Task_Handle p, Task_Handle n)
{
    Int core = 0;

#ifdef SMP
    core = Core_getId();

    if (core != 0) {
        Watchdog_start(core);
    }
    else
#endif
    {
        Watchdog_kick(core);
    }
}

/*
 *  ======== Watchdog_isException ========
 */
Bool Watchdog_isException(UInt excNum)
{
    Int i;
    Bool found = FALSE;

    for (i = 0; i < Watchdog_module->wdtCores; i++) {
        if (excNum == Watchdog_module->device[i].intNum) {
            found = TRUE;
            break;
        }
    }

    return found;
}

/*
 *  ======== Watchdog_stop ========
 */
Void Watchdog_stop(Int core)
{
    volatile Watchdog_TimerRegs *timer = Watchdog_module->device[core].baseAddr;

    if ((Watchdog_module->status[core] == Watchdog_Mode_ENABLED) && timer) {
        while (timer->twps & WATCHDOG_TIMER_TWPS_W_PEND_TCLR);
        timer->tclr &= ~1;
    }
}

/*
 *  ======== Watchdog_start ========
 */
Void Watchdog_start(Int core)
{
    volatile Watchdog_TimerRegs *timer = Watchdog_module->device[core].baseAddr;

    if ((Watchdog_module->status[core] == Watchdog_Mode_ENABLED) && timer) {
        while (timer->twps & WATCHDOG_TIMER_TWPS_W_PEND_TCLR);
        timer->tclr |= 1;

        while (timer->twps & WATCHDOG_TIMER_TWPS_W_PEND_TGRR);
        timer->ttgr = 0;
    }
}

/*
 *  ======== Watchdog_kick ========
 *  Refresh/restart the watchdog timer
 */
Void Watchdog_kick(Int core)
{
    volatile Watchdog_TimerRegs *timer = Watchdog_module->device[core].baseAddr;

    if ((Watchdog_module->status[core] == Watchdog_Mode_ENABLED) && timer) {
        while (timer->twps & WATCHDOG_TIMER_TWPS_W_PEND_TGRR);
        timer->ttgr = 0;
    }
}

/*
 *  ======== Watchdog_restore ========
 *  Refresh/restart the watchdog timer
 */
Void Watchdog_restore(Int event, Ptr data)
{
    Int                          i;
    volatile Watchdog_TimerRegs  *timer;

    for (i = 0; i < Watchdog_module->wdtCores; i++) {  /* loop for SMP cores */
        timer = (volatile Watchdog_TimerRegs *) Watchdog_module->device[i].baseAddr;

        if (Watchdog_module->status[i] == Watchdog_Mode_ENABLED) {
            /* Configure the timer */
            initTimer(timer, FALSE);

            /* Enable timer */
            while (timer->twps & WATCHDOG_TIMER_TWPS_W_PEND_TCLR);
            timer->tclr |= 1;
        }
    }
}
