/*
 * Copyright (c) 2015, Texas Instruments Incorporated
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
 *  @file       IpcPowerDsp_dra7xx.c
 *
 *  @brief      Power Managment for DRA7xx DSP.
 *
 *  ============================================================================
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/timers/dmtimer/Timer.h>
#include <ti/sysbios/family/c66/vayu/Power.h>

#include <ti/pm/IpcPower.h>
#include "_IpcPower.h"

#define REG32(A)   (*(volatile UInt32 *) (A))

#define DSP_SYS_SYSCONFIG 0x01D00008
#define IDLE_STBY_MASK    0x0000003C

#define PDCCMD_REG        0x01810000
#define SLEEP_MASK        0x10000
#define AWAKE_MASK        0xFFFEFFFF

static UInt32 IpcPower_hibLock;
static Semaphore_Handle IpcPower_semSuspend = NULL;
static Semaphore_Handle IpcPower_semExit = NULL;
static Task_Handle IpcPower_tskSuspend = NULL;
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

static IpcPower_WugenEvtMask wugenEvtMask;

/* PM transition debug counters */
UInt32 IpcPower_idleCount = 0;
UInt32 IpcPower_suspendCount = 0;
UInt32 IpcPower_resumeCount = 0;

/* Handle to store BIOS Tick Timer */
static Timer_Handle tickTimerHandle = NULL;

/*
 * Assembly function that calls idle using a workaround for a silicon bug that
 * would hang the CPU when prefetch is enabled.
 */
extern Void IpcPower_callIdle();

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
                REG32(PDCCMD_REG) |= SLEEP_MASK;
                REG32(PDCCMD_REG);
            }
            break;
        case IpcPower_SLEEP_MODE_WAKELOCK:
            refWakeLockCnt++;
            REG32(PDCCMD_REG) &= AWAKE_MASK;
            REG32(PDCCMD_REG);
            break;
    }
    Hwi_restore(hwiKey);
}

/*
 *  ======== IpcPower_getWugenEvtMask ========
 */
Void IpcPower_getWugenEvtMask(IpcPower_WugenEvtMask *mask)
{
    mask->mevt0 = wugenEvtMask.mevt0;
    mask->mevt1 = wugenEvtMask.mevt1;
}

/*
 *  ======== IpcPower_setWugenEvtMask ========
 */
Void IpcPower_setWugenEvtMask(IpcPower_WugenEvtMask *mask)
{
    wugenEvtMask.mevt0 = mask->mevt0;
    wugenEvtMask.mevt1 = mask->mevt1;
}

/*
 * On the C66 DSPs, there is no official WUGEN IP per se, but the
 * DSP_SYS_IRQWAKEEN0/1 registers have the same role as WUGEN
 * event mask registers in terms of determining which interrupts
 * cause wakeup event generation.
 */
static inline Void IpcPower_getWugen(IpcPower_WugenEvtMask *mask)
{
    mask->mevt0 = REG32(DSP_SYS_IRQWAKEEN0);
    mask->mevt1 = REG32(DSP_SYS_IRQWAKEEN1);
}

static inline Void IpcPower_setWugen(IpcPower_WugenEvtMask *mask)
{
    REG32(DSP_SYS_IRQWAKEEN0) |= mask->mevt0;
    REG32(DSP_SYS_IRQWAKEEN1) |= mask->mevt1;
}

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

            Power_suspend(Power_Suspend_HIBERNATE);

            /* Call post-resume preparation function */
            IpcPower_postResume();
        }
    }

    /* Signal the task end */
    Semaphore_post(IpcPower_semExit);
}

/*
 *  ======== IpcPower_init ========
 */
#define FXNN "IpcPower_init"
Void IpcPower_init()
{
    extern cregister volatile UInt DNUM;
    Task_Params taskParams;
    Int i;
    UArg arg;
    UInt func;
    Timer_Handle tHandle = NULL;

    if (curInit++) {
        return;
    }

    IpcPower_hibLock = 0;
    refWakeLockCnt = 0;

    for (i = 0; i < Timer_Object_count(); i++) {
        tHandle = Timer_Object_get(NULL, i);
        func = (UInt) Timer_getFunc(tHandle, &arg);
        if (func && ((func == (UInt) ti_sysbios_knl_Clock_doTick__I) ||
                     (func == (UInt) Clock_tick))) {
            tickTimerHandle = tHandle;
            break;
        }
    }
    if (tickTimerHandle == NULL) {
        Log_print0(Diags_INFO, FXNN": Cannot find tickTimer Handle. "
                        "Custom clock timer functions currently not "
                        "supported.\n");
    }

    IpcPower_semSuspend = Semaphore_create(0, NULL, NULL);
    IpcPower_semExit = Semaphore_create(0, NULL, NULL);

    Task_Params_init(&taskParams);
    taskParams.priority = Task_numPriorities - 1; /* Highest priority */
    taskParams.instance->name = "ti.pm.IpcPower_tskSuspend";
    IpcPower_tskSuspend = Task_create(IpcPower_suspendTaskFxn, &taskParams,
        NULL);

    IpcPower_sleepMode(IpcPower_SLEEP_MODE_DEEPSLEEP);

    /* Setup IDLEMODE and STANDBYMODE in DSP_SYS_SYSCONFIG */
    REG32(DSP_SYS_SYSCONFIG) |= IDLE_STBY_MASK;

    /* Setup DSP_SYS_IRQWAKEEN0/1 */
    IpcPower_getWugen(&wugenEvtMask);
    if (DNUM == 0) { /* DSP1 */
        wugenEvtMask.mevt0 |= VAYU_DSP1_WUGEN_INT_MASK0;
        wugenEvtMask.mevt1 |= VAYU_DSP1_WUGEN_INT_MASK1;
    }
    else {
        wugenEvtMask.mevt0 |= VAYU_DSP2_WUGEN_INT_MASK0;
        wugenEvtMask.mevt1 |= VAYU_DSP2_WUGEN_INT_MASK1;
    }
    IpcPower_setWugen(&wugenEvtMask);
}
#undef FXNN

/*
 *  ======== IpcPower_exit ========
 */
Void IpcPower_exit()
{

    --curInit;

    if (curInit == 0) {
        /* Unblock PM suspend task */
        Semaphore_post(IpcPower_semSuspend);

        /* Wait for task completion */
        Semaphore_pend(IpcPower_semExit, BIOS_WAIT_FOREVER);

        /* Delete the suspend task and semaphore */
        Task_delete(&IpcPower_tskSuspend);
        Semaphore_delete(&IpcPower_semSuspend);
        Semaphore_delete(&IpcPower_semExit);
    }
}

/*
 *  ======== IpcPower_suspend ========
 */
Void IpcPower_suspend()
{
    Assert_isTrue((curInit > 0) , NULL);

    Semaphore_post(IpcPower_semSuspend);
}

/*
 *  ======== IpcPower_idle ========
 */
Void IpcPower_idle()
{
    Hwi_disable();
    IpcPower_idleCount++;

    IpcPower_callIdle();
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

    hwiKey = Hwi_disable();

    IpcPower_hibLock++;

    Hwi_restore(hwiKey);

    return (IpcPower_hibLock);
}

/*
 *  ======== IpcPower_hibernateUnlock ========
 */
UInt IpcPower_hibernateUnlock()
{
    IArg hwiKey;

    hwiKey = Hwi_disable();

    if (IpcPower_hibLock > 0) {
        IpcPower_hibLock--;
    }

    Hwi_restore(hwiKey);

    return (IpcPower_hibLock);
}


/*
 *  ======== IpcPower_canHibernate ========
 */
Bool IpcPower_canHibernate()
{
    if (IpcPower_hibLock) {
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
    if (tickTimerHandle != NULL) {
        Timer_restoreRegisters(tickTimerHandle, NULL);
        Timer_start(tickTimerHandle);
    }

    /* Call all user registered resume callback functions */
    IpcPower_callUserFxns(IpcPower_Event_RESUME);
    IpcPower_resumeCount++;
}
