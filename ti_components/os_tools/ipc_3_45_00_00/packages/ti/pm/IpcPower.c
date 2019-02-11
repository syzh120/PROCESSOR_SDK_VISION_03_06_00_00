/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
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
 */
/** ============================================================================
 *  @file       IpcPower.c
 *
 *  @brief      A simple Power Managment which responses to the host commands.
 *
 *  TODO:
 *     - Add suspend/resume notifications
 *  ============================================================================
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Main.h>
#include <xdc/runtime/Registry.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/timers/dmtimer/Timer.h>
#ifndef SMP
#include <ti/sysbios/family/arm/ducati/omap4430/Power.h>
#include <ti/sysbios/family/arm/ducati/Core.h>
#else
#include <ti/sysbios/hal/Core.h>
#include <ti/sysbios/family/arm/ducati/smp/Power.h>
#endif

#include <ti/ipc/MultiProc.h>
#include <ti/pm/IpcPower.h>
#include "_IpcPower.h"

#define MASTERCORE                      (1)
#define NO_MASTERCORE                   (0)
#define CPU_COPY                       (-1)
#define REG32(A)   (*(volatile UInt32 *) (A))

#define SET_DEEPSLEEP (REG32(M3_SCR_REG) | (1 << DEEPSLEEP_BIT))
#define CLR_DEEPSLEEP (REG32(M3_SCR_REG) & (~(1 << DEEPSLEEP_BIT)))

#ifndef SMP
#pragma DATA_SECTION(IpcPower_hibLocks, ".ipcpower_data")
UInt32 IpcPower_hibLocks[2]; /* One lock for each of the IPU cores */
#else
static UInt32 IpcPower_hibLocks; /* Only one lock in SMP mode */
#endif

/* PM transition debug counters */
#ifndef SMP
UInt32 IpcPower_idleCount = 0;
#else
UInt32 IpcPower_idleCount[2] = { 0, 0 };
#endif
UInt32 IpcPower_suspendCount = 0;
UInt32 IpcPower_resumeCount = 0;

/* Clock function pointer to handle custom clock functions */
Void *IpcPower_clockFxn = NULL;

/* Handle to store BIOS Tick Timer */
static Timer_Handle tickTimerHandle = NULL;

static Power_SuspendArgs PowerSuspArgs;
static Swi_Handle suspendResumeSwi;
#ifndef SMP
static Semaphore_Handle IpcPower_semSuspend = NULL;
static Semaphore_Handle IpcPower_semExit = NULL;
static Task_Handle IpcPower_tskSuspend = NULL;
static UInt16 sysm3ProcId;
static UInt16 appm3ProcId;
#endif
static Int32 refWakeLockCnt;

/* List for storing all registered callback functions */
static IpcPower_CallbackElem *IpcPower_callbackList = NULL;

/* Module ref count: */
static Int curInit = 0;

typedef enum IpcPower_SleepMode {
    IpcPower_SLEEP_MODE_DEEPSLEEP,
    IpcPower_SLEEP_MODE_WAKELOCK,
    IpcPower_SLEEP_MODE_WAKEUNLOCK
} IpcPower_SleepMode;

/* Deep sleep state variable for IpcPower module */
static Bool IpcPower_deepSleep = TRUE;

static IpcPower_WugenEvtMask wugenEvtMask;


/*
 *  ======== IpcPower_callUserFxns ========
 */
static Void IpcPower_callUserFxns(IpcPower_Event event)
{
    IpcPower_CallbackElem *node = IpcPower_callbackList;

    /* Call the registered functions matching the event */
    while (node != NULL) {
        if (node->event == event) {
            (*(node->callback))(event, node->data);
        }
        node = node->next;
    }
}

static inline Void IpcPower_sleepMode(IpcPower_SleepMode opt)
{
    IArg hwiKey;

    /* Set/Restore the DeepSleep bit if no timer already in use */
    hwiKey = Hwi_disable();
    switch (opt) {
        case IpcPower_SLEEP_MODE_WAKEUNLOCK:
            if (refWakeLockCnt) {
                refWakeLockCnt--;
            }
            /* Fall through: */
        case IpcPower_SLEEP_MODE_DEEPSLEEP:
            if (!refWakeLockCnt) {
                IpcPower_deepSleep = TRUE;
            }
            break;
        case IpcPower_SLEEP_MODE_WAKELOCK:
            refWakeLockCnt++;
            IpcPower_deepSleep = FALSE;
            break;
    }
    Hwi_restore(hwiKey);
}

Void IpcPower_getWugenEvtMask(IpcPower_WugenEvtMask *mask)
{
    mask->mevt0 = wugenEvtMask.mevt0;
    mask->mevt1 = wugenEvtMask.mevt1;
}

Void IpcPower_setWugenEvtMask(IpcPower_WugenEvtMask *mask)
{
    wugenEvtMask.mevt0 = mask->mevt0;
    wugenEvtMask.mevt1 = mask->mevt1;
}

static inline Void IpcPower_getWugen(IpcPower_WugenEvtMask *mask)
{
    mask->mevt0 = REG32(WUGEN_MEVT0);
    mask->mevt1 = REG32(WUGEN_MEVT1);
}

static inline Void IpcPower_setWugen(IpcPower_WugenEvtMask *mask)
{
    REG32(WUGEN_MEVT0) = mask->mevt0;
    REG32(WUGEN_MEVT1) = mask->mevt1;
}

/*
 *  ======== IpcPower_suspendSwi ========
 */
#define FXNN "IpcPower_suspendSwi"
static Void IpcPower_suspendSwi(UArg arg0, UArg arg1)
{
#ifndef SMP
    if (MultiProc_self() == sysm3ProcId) {
#endif
        Log_print0(Diags_INFO, FXNN":Core0 Hibernation Swi");
#ifndef SMP
        PowerSuspArgs.pmMasterCore = MASTERCORE;
    }
    else if (MultiProc_self() == appm3ProcId) {
        Log_print0(Diags_INFO, FXNN":Core1 Hibernation Swi");
        PowerSuspArgs.pmMasterCore = NO_MASTERCORE;
    }
#endif
    if (refWakeLockCnt) {
        System_printf("Warning: Wake locks in use\n");
    }

    Power_suspend(&PowerSuspArgs);
#ifndef SMP
    IpcPower_sleepMode(IpcPower_SLEEP_MODE_DEEPSLEEP);
    IpcPower_setWugen(&wugenEvtMask);

    Log_print0(Diags_INFO, FXNN":Resume");
#endif
}
#undef FXNN

/* =============================================================================
 *  IpcPower Functions:
 * =============================================================================
 */

#ifndef SMP
/*
 *  ======== IpcPower_suspendTaskFxn ========
 */
Void IpcPower_suspendTaskFxn(UArg arg0, UArg arg1)
{
    while (curInit) {
        /* Wait for suspend notification from host-side */
        Semaphore_pend(IpcPower_semSuspend, BIOS_WAIT_FOREVER);

        if (curInit) {
            /* Call pre-suspend preparation function */
            IpcPower_preSuspend();

            Swi_post(suspendResumeSwi);

            /* Call post-resume preparation function */
            IpcPower_postResume();
        }
    }

    /* Signal the task end */
    Semaphore_post(IpcPower_semExit);
}
#endif

/*
 *  ======== IpcPower_init ========
 */
Void IpcPower_init()
{
    Swi_Params swiParams;
#ifndef SMP
    Task_Params taskParams;
    UInt coreIdx = Core_getId();
#endif
    Int i;
    UArg arg;
    UInt func;
    Timer_Handle tHandle = NULL;

    if (curInit++) {
        return;
    }

#ifndef SMP
    IpcPower_hibLocks[coreIdx] = 0;

    sysm3ProcId = MultiProc_getId("CORE0");
    appm3ProcId = MultiProc_getId("CORE1");
#else
    IpcPower_hibLocks = 0;
#endif
    refWakeLockCnt = 0;

    for (i = 0; i < Timer_Object_count(); i++) {
        tHandle = Timer_Object_get(NULL, i);
        func = (UInt) Timer_getFunc(tHandle, &arg);
        if (func && ((func == (UInt) ti_sysbios_knl_Clock_doTick__I) ||
                     (func == (UInt) Clock_tick) ||
                     (func == (UInt) IpcPower_clockFxn))) {
            tickTimerHandle = tHandle;
            break;
        }
    }
    if (tickTimerHandle == NULL) {
        System_abort("IpcPower_init: Cannot find tickTimer Handle. Custom"
                        " clock timer functions currently not supported.\n");
    }

#ifndef SMP
    IpcPower_semSuspend = Semaphore_create(0, NULL, NULL);
    IpcPower_semExit = Semaphore_create(0, NULL, NULL);

    Task_Params_init(&taskParams);
    taskParams.priority = Task_numPriorities - 1; /* Highest priority */
    taskParams.instance->name = "ti.pm.IpcPower_tskSuspend";
    IpcPower_tskSuspend = Task_create(IpcPower_suspendTaskFxn, &taskParams,
                                                                        NULL);
#endif

    Swi_Params_init(&swiParams);
    swiParams.priority = Swi_numPriorities - 1; /* Max Priority Swi */
    suspendResumeSwi = Swi_create(IpcPower_suspendSwi, &swiParams, NULL);

    /*Power settings for saving/restoring context */
    PowerSuspArgs.rendezvousResume = TRUE;
    PowerSuspArgs.dmaChannel = CPU_COPY;
    PowerSuspArgs.intMask31_0 = 0x0;
#ifndef SMP
    PowerSuspArgs.intMask63_32 = 0x0;
#else
    PowerSuspArgs.intMask63_32 = WUGEN_MAILBOX_BIT << 16;
#endif
    PowerSuspArgs.intMask79_64 = 0x0;
    IpcPower_sleepMode(IpcPower_SLEEP_MODE_DEEPSLEEP);

    IpcPower_getWugen(&wugenEvtMask);
#ifdef OMAP5
    wugenEvtMask.mevt0 |= OMAP_IPU_WUGEN_INT_MASK0;
    wugenEvtMask.mevt1 |= OMAP_IPU_WUGEN_INT_MASK1;
#else
    if (MultiProc_self() == MultiProc_getId("IPU2")) {
        wugenEvtMask.mevt0 |= VAYU_IPU2_WUGEN_INT_MASK0;
        wugenEvtMask.mevt1 |= VAYU_IPU2_WUGEN_INT_MASK1;
    }
    else {
        wugenEvtMask.mevt0 |= VAYU_IPU1_WUGEN_INT_MASK0;
        wugenEvtMask.mevt1 |= VAYU_IPU1_WUGEN_INT_MASK1;
    }
#endif
    IpcPower_setWugen(&wugenEvtMask);
}

/*
 *  ======== IpcPower_exit ========
 */
Void IpcPower_exit()
{
    --curInit;

    if (curInit == 0) {
#ifndef SMP
        /* Unblock PM suspend task */
        Semaphore_post(IpcPower_semSuspend);

        /* Wait for task completion */
        Semaphore_pend(IpcPower_semExit, BIOS_WAIT_FOREVER);

        /* Delete the suspend task and semaphore */
        Task_delete(&IpcPower_tskSuspend);
        Semaphore_delete(&IpcPower_semSuspend);
        Semaphore_delete(&IpcPower_semExit);
#endif
    }
}

/*
 *  ======== IpcPower_suspend ========
 */
Void IpcPower_suspend()
{
    Assert_isTrue((curInit > 0) , NULL);

#ifndef SMP
    Semaphore_post(IpcPower_semSuspend);
#else
    Swi_post(suspendResumeSwi);
#endif
}

/*
 *  ======== IpcPower_idle ========
 */
Void IpcPower_idle()
{
#ifndef SMP
    IpcPower_idleCount++;
#else
    UInt coreId = Core_getId();
    IpcPower_idleCount[coreId]++;
#endif

    REG32(M3_SCR_REG) = IpcPower_deepSleep ? SET_DEEPSLEEP : CLR_DEEPSLEEP;
    asm(" wfi");
}

/*
 *  ======== IpcPower_wakeLock ========
 */
Void IpcPower_wakeLock()
{
    IpcPower_sleepMode(IpcPower_SLEEP_MODE_WAKELOCK);
}

/*
 *  ======== IpcPower_wakeUnlock ========
 */
Void IpcPower_wakeUnlock()
{
    IpcPower_sleepMode(IpcPower_SLEEP_MODE_WAKEUNLOCK);
}

/*
 *  ======== IpcPower_hibernateLock ========
 */
UInt IpcPower_hibernateLock()
{
    IArg hwiKey;
#ifndef SMP
    UInt coreIdx = Core_getId();
#endif

    hwiKey = Hwi_disable();

#ifndef SMP
    IpcPower_hibLocks[coreIdx] += 1;
#else
    IpcPower_hibLocks++;
#endif

    Hwi_restore(hwiKey);

#ifndef SMP
    return (IpcPower_hibLocks[coreIdx]);
#else
    return IpcPower_hibLocks;
#endif
}

/*
 *  ======== IpcPower_hibernateUnlock ========
 */
UInt IpcPower_hibernateUnlock()
{
    IArg hwiKey;
#ifndef SMP
    UInt coreIdx = Core_getId();
#endif

    hwiKey = Hwi_disable();

#ifndef SMP
    if (IpcPower_hibLocks[coreIdx] > 0) {
        IpcPower_hibLocks[coreIdx] -= 1;
    }
#else
    if (IpcPower_hibLocks > 0) {
        IpcPower_hibLocks--;
    }
#endif

    Hwi_restore(hwiKey);

#ifndef SMP
    return (IpcPower_hibLocks[coreIdx]);
#else
    return (IpcPower_hibLocks);
#endif
}

/*
 *  ======== IpcPower_canHibernate ========
 */
Bool IpcPower_canHibernate()
{
#ifndef SMP
    if (IpcPower_hibLocks[0] || IpcPower_hibLocks[1]) {
#else
    if (IpcPower_hibLocks) {
#endif
        return (FALSE);
    }

    return (TRUE);
}

/*
 *  ======== IpcPower_registerCallback ========
 */
#define FXNN "IpcPower_registerCallback"
Int IpcPower_registerCallback(Int event, IpcPower_CallbackFuncPtr cbck,
                              Ptr data)
{
    IArg hwiKey;
    IpcPower_CallbackElem **list, *node;
    BIOS_ThreadType context = BIOS_getThreadType();

    if ((context != BIOS_ThreadType_Task) &&
        (context != BIOS_ThreadType_Main)) {
        Log_print0(Diags_ERROR, FXNN":Invalid context\n");
        return (IpcPower_E_FAIL);
    }

    list = &IpcPower_callbackList;

    /* Allocate and update new element */
    node = Memory_alloc(NULL, sizeof(IpcPower_CallbackElem), 0, NULL);
    if (node == NULL) {
        Log_print0(Diags_ERROR, FXNN":out of memory\n");
        return (IpcPower_E_MEMORY);
    }

    node->next     = NULL;
    node->event    = (IpcPower_Event) event;
    node->callback = cbck;
    node->data     = data;

    hwiKey = Hwi_disable();  /* begin: critical section */
    while (*list != NULL) {
        list = &(*list)->next;
    }
    *list = node;
    Hwi_restore(hwiKey);  /* end: critical section */

    return (IpcPower_S_SUCCESS);
}
#undef FXNN

/*
 *  ======== IpcPower_unregisterCallback ========
 */
#define FXNN "IpcPower_unregisterCallback"
Int IpcPower_unregisterCallback(Int event, IpcPower_CallbackFuncPtr cbck)
{
    IArg hwiKey;
    IpcPower_CallbackElem **list, *node;
    Int status = IpcPower_E_FAIL;
    BIOS_ThreadType context = BIOS_getThreadType();

    if ((context != BIOS_ThreadType_Task) &&
        (context != BIOS_ThreadType_Main)) {
        Log_print0(Diags_ERROR, FXNN":Invalid context\n");
        return (status);
    }


    list = &IpcPower_callbackList;
    node  = NULL;

    hwiKey = Hwi_disable();  /* begin: critical section */
    while (*list != NULL) {
        if ( ((*list)->callback == cbck) &&
             ((*list)->event == event) ) {
            node   = *list;
            *list  = (*list)->next;
            status = IpcPower_S_SUCCESS;
            break;
        }
        list = &(*list)->next;
    }
    Hwi_restore(hwiKey);  /* end: critical section */

    if (status == IpcPower_S_SUCCESS) {
        if (node != NULL) {
            Memory_free(NULL, node, sizeof(IpcPower_CallbackElem));
        }
        else {
            Log_print0(Diags_ERROR, FXNN":Invalid pointer\n");
        }
    }

    return (status);
}
#undef FXNN

/*
 *  ======== IpcPower_preSuspend ========
 */
Void IpcPower_preSuspend(Void)
{
    IpcPower_suspendCount++;

    /* Call all user registered suspend callback functions */
    IpcPower_callUserFxns(IpcPower_Event_SUSPEND);
}

/*
 *  ======== IpcPower_postResume ========
 */
Void IpcPower_postResume(Void)
{
    /* Restore timer registers */
    Timer_restoreRegisters(tickTimerHandle, NULL);
    Timer_start(tickTimerHandle);

    /* Call all user registered resume callback functions */
    IpcPower_callUserFxns(IpcPower_Event_RESUME);

    IpcPower_resumeCount++;
}
