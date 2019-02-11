/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * */
/*
 * ======== task.c ========
 *
 * Task Management functions using BIOS6
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>

/* XDC/BIOS6 Includes */
#include <xdc/std.h>

#include <xdc/runtime/Error.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>

extern Void ti_ndk_config_global_taskCreateHook(Task_Handle h);
extern Void ti_ndk_config_global_taskExitHook(Task_Handle h);

/* 
 * Low Resource Flag
 * We can only process a low resource condition when
 * we are not in kernel mode, so we use a flag and
 * then process it on a call to llExit()
 */
static uint _TaskFlagLowResource = 0;

/* signal that system resources are low */
void NotifyLowResource(void)
{
    _TaskFlagLowResource = 1;
}

/* 
 * Hook ID
 * The Hook ID is used to set our environment pointer for
 * slot zero. It must be valid!! (Check in SetEnv function)
 */
static int     hookId = 0xffffffff;
static uint    hookOK = 0;

/*
 * This hookInit() function must be hooked into DSP/BIOS for
 * the NDK to work properly.
 */
void NDK_hookInit(int id)
{
    hookId = id;
}

/*
 * This hookCreate() function is needed to init the environment
 * to zero.
 *
 * Call fdOpenSession via Task create hook to allow BSD sockets code to work
 * "as is."  Note that this function will only be run in Task context for
 * dynamically created Tasks.
 */
void NDK_hookCreate(Task_Handle h)
{
    hookOK = 1;

    if( hookId != 0xffffffff ) {
        Task_setHookContext(h, (Int)hookId, 0);

        /* open the file descriptor session automatically (if configured to) */
        ti_ndk_config_global_taskCreateHook(h);
    }
}

/*
 * Call fdCloseSession via Task exit hook to allow BSD sockets code to work
 * "as is."
 *
 * Task exit hook should always run in the context of the Task that is exiting
 * (i.e. Task context).
 */
Void NDK_hookExit(Task_Handle h)
{
    if( hookId != 0xffffffff ) {
        /* close the file descriptor session automatically (if configured to) */
        ti_ndk_config_global_taskExitHook(h);
    }
}

/*-------------------------------------------------------------------- */
/* llEnter / llExit - Kernel Mode gate functions */
/*-------------------------------------------------------------------- */
/* NOTE: There are two versions of the llEnter()/llExit() pairing. */
/* The default version uses task priority to implement exclusion. The */
/* second version uses a semaphore. The priority based version is */
/* faster, but not as safe if care is not taken when setting task */
/* priorities. */

/* NOTE: Whether or not to use a semaphore for exclusion is independent */
/*       of the choice to use a semaphore for scheduling in NETCTRL. */
/*       The concepts are unrelated. */

/* To enable the semaphore version, set the below #define to 1 */
/* Note that when _NDK_EXTERN_CONFIG is defined, this USE_LL_SEMAPHORE */
/* is defined outside the module. */
/*-------------------------------------------------------------------- */
#ifndef _NDK_EXTERN_CONFIG
#define USE_LL_SEMAPHORE 0
#endif

static HANDLE   hSemGate = 0;
static volatile int InKernel = 0;

#if USE_LL_SEMAPHORE
/*-------------------------------------------------------------------- */
/* llEnter() */
/* Enter the IP stack */
/*-------------------------------------------------------------------- */
void llEnter()
{
    Error_Block eb;

    /* If we don't have our semaphore yet, allocate one with "1" entry */
    if( !hSemGate )
    {
        if( !(hSemGate = Semaphore_create( 1, 0, &eb )) )
        {
            DbgPrintf(DBG_ERROR,"llEnter (sem): Could not create llEnter() semaphore");
            return;
        }
    }

    /* Wait on entering the stack. */
    Semaphore_pend( hSemGate, (UINT32) ti_sysbios_BIOS_WAIT_FOREVER );

    /* If case something goes wrong with the semaphore, track */
    /* problems entering the stack */
    if( InKernel )
        DbgPrintf(DBG_ERROR,"llEnter (sem): Illegal call to llEnter()");

    InKernel=1;
}
/*-------------------------------------------------------------------- */
/* llExit() */
/* Release the IP stack */
/*-------------------------------------------------------------------- */
void llExit()
{
    /* Handle the low resource condition */
    if( _TaskFlagLowResource )
    {
        ExecLowResource();
        _TaskFlagLowResource = 0;
    }

    /* The "InKernel" flag traps calls to llExit() before calling */
    /* llEnter(). */
    if( !InKernel )
    {
        DbgPrintf(DBG_ERROR,"llExit (sem): Illegal call to llExit()");
        return;
    }
    InKernel=0;

    /* Signal that we've exited the stack. */
    Semaphore_post( hSemGate );
}
#else
static int OldPriority = 0;
/*-------------------------------------------------------------------- */
/* llEnter() */
/* Enter the IP stack */
/*-------------------------------------------------------------------- */
void llEnter()
{
    int tmpOldPriority;
    Error_Block eb;

    /* If we don't have our semaphore yet, allocate one with "0" entry */
    if( !hSemGate )
    {
        if( !(hSemGate = Semaphore_create( 0, 0, &eb )) )
        {
            DbgPrintf(DBG_ERROR,
                    "llEnter: Could not create llEnter() semaphore");
            return;
        }
    }

    /* Since this task is running (assume for now it has a priority LESS */
    /* THAN the kernel level - we know that nothing is running at the */
    /* kernel level. */

    /* We try to use priority to block other calls from coming into */
    /* llEnter(). However, if we are re-entered, we'll fall back to */
    /* using the semaphore */

    /* Set this task's priority at kernel level */
    tmpOldPriority = TaskSetPri( TaskSelf(), OS_TASKPRIKERN );

    /* Verify this call was legal */
    if( tmpOldPriority >= OS_TASKPRIKERN )
    {
        if( InKernel )
        {
            DbgPrintf(DBG_ERROR,
                    "llEnter: Illegal reentrant call to llEnter()");
        }
        else
        {
            DbgPrintf(DBG_ERROR,"llEnter: Illegal priority call to llEnter()");
        }
        return;
    }

    /* Verify there has been no "reentrance". */
    /* If there was, use the semaphore. */
    if( ++InKernel > 1 )
    {
        /* Wait on entering the stack. */
        Semaphore_pend( hSemGate, (UINT32) ti_sysbios_BIOS_WAIT_FOREVER );
    }

    /* Store the priority of the task that owns kernel mode */
    OldPriority = tmpOldPriority;
}
/*-------------------------------------------------------------------- */
/* llExit() */
/* Release the IP stack */
/*-------------------------------------------------------------------- */
void llExit()
{
    /* Handle the low resource condition */
    if( _TaskFlagLowResource )
    {
        ExecLowResource();
        _TaskFlagLowResource = 0;
    }

    /* Verify we were at kernel level */
    if( !InKernel )
    {
        DbgPrintf(DBG_ERROR,"llExit: Illegal call to llExit()");
        return;
    }

    /* If a task is waiting at llEnter(), signal it */
    if( --InKernel > 0 )
    {
        /* Signal that we've exited the stack. */
        Semaphore_post( hSemGate );
    }

    /* Restore this task's priority */
    TaskSetPri( TaskSelf(), OldPriority );
}
#endif

/*-------------------------------------------------------------------- */
/* TaskInit() - Called from NETCTRL init */
/*-------------------------------------------------------------------- */
void _TaskInit()
{
}

/*-------------------------------------------------------------------- */
/* TaskShutdow() - Called from NETCTRL shutdown */
/*-------------------------------------------------------------------- */
void _TaskShutdown()
{    
}

/*-------------------------------------------------------------------- */
/* TaskBlock() */
/* Block a task */
/*-------------------------------------------------------------------- */
void TaskBlock(HANDLE h)
{
    Task_setPri((Task_Handle)h, -1);
}

/*-------------------------------------------------------------------- */
/* TaskCreate() */
/* Create a task */
/*-------------------------------------------------------------------- */
/* ARGSUSED */
HANDLE TaskCreate( void(*pFun)(), char *Name, int Priority, uint StackSize,
                   UINT32 Arg1, UINT32 Arg2, UINT32 Arg3 )
{
    Task_Params params;
    Task_Handle htsk;

    Task_Params_init(&params);
    params.instance->name = Name;
    params.priority = Priority;
    params.stackSize = StackSize;
    params.arg0 = Arg1;
    params.arg1 = Arg2;
    params.affinity = 0;

    htsk = Task_create((Task_FuncPtr)pFun, &params, NULL);

    return ((HANDLE)htsk);
}

/*-------------------------------------------------------------------- */
/* TaskDestroy() */
/* Destroy a task */
/*-------------------------------------------------------------------- */
void TaskDestroy( HANDLE h )
{
    if (h == TaskSelf()) {
        TaskExit();
    }
    else {
        Task_delete((Task_Handle *)&h);
    }
}

/*-------------------------------------------------------------------- */
/* TaskSetEnv */
/* Sets the task's Environment pointer */
/*-------------------------------------------------------------------- */
void TaskSetEnv( HANDLE h, int Slot, HANDLE hEnv )
{
    if( Slot )
        return;
    if( hookId == 0xffffffff )
    {
        DbgPrintf(DBG_ERROR,"TaskSetEnv: FATAL: NDK_hookInit() must be set in BIOS Task module config (hookId == 0xffffffff)");
        return;
    }
    if( !hookOK )
    {
        DbgPrintf(DBG_ERROR,"TaskSetEnv: FATAL: NDK_hookCreate() must be set in BIOS Task module config (!hookOK)");
        return;
    }

    Task_setHookContext((Task_Handle)h, (Int)hookId, (Ptr)hEnv);
}

/*-------------------------------------------------------------------- */
/* TaskGetEnv */
/* Gets the task's Environment pointer */
/*-------------------------------------------------------------------- */
HANDLE TaskGetEnv( HANDLE h, int Slot )
{
    if( Slot )
        return (0);
    if( hookId == 0xffffffff )
    {
        DbgPrintf(DBG_ERROR,"TaskGetEnv: FATAL: NDK_hookInit() must be set in DSP/BIOS Task module config (hookId == 0xffffffff)");
        return (0);
    }
    if( !hookOK )
    {
        DbgPrintf(DBG_ERROR,"TaskGetEnv: FATAL: NDK_hookCreate() must be set in DSP/BIOS Task module config (!hookOK)");
        return (0);
    }
    return ((HANDLE)Task_getHookContext((Task_Handle)h, (Int)hookId));
}

/*-------------------------------------------------------------------- */
/* TaskExit() */
/* Exits and destroys a task */
/*-------------------------------------------------------------------- */
void TaskExit()
{    
    Task_exit();
}

/*-------------------------------------------------------------------- */
/* TaskGetPri() */
/* Get a task's priority */
/*-------------------------------------------------------------------- */
int TaskGetPri(HANDLE h)
{
    return ((int)Task_getPri((Task_Handle)h));
}

/*-------------------------------------------------------------------- */
/* TaskSetPri() */
/* Set a task's priority */
/*-------------------------------------------------------------------- */
int TaskSetPri(HANDLE h, int priority)
{
    return (Task_setPri((Task_Handle)h, (Int)priority));
}

/*-------------------------------------------------------------------- */
/* TaskSelf() */
/* Return handle of task itself  */
/*-------------------------------------------------------------------- */
HANDLE TaskSelf()
{
    return ((HANDLE)Task_self());
}

/*-------------------------------------------------------------------- */
/* TaskSleep() */
/* Put a task into sleep  */
/*-------------------------------------------------------------------- */
void TaskSleep(UINT32 delay)
{
     Task_sleep((UInt)delay);
}

/*-------------------------------------------------------------------- */
/* TaskYield() */
/* Yield task  */
/*-------------------------------------------------------------------- */
void TaskYield()
{
     Task_yield();
}
