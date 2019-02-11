/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
/*
 *  ======== GateHWSpinlock.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/GateHWSpinlock.xdc.h"

/*
 *  ======== GateHWSpinlock_Module_startup ========
 *  release the HW spinlock if the core owns it.
 */
Int GateHWSpinlock_Module_startup(Int phase)
{
    Int i;
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSpinlock_baseAddr;
    SharedRegion_Entry entry;
    Bits32 *reservedMaskArr = (Bits32 *)GateHWSpinlock_reservedMaskArr;

    /* Wait for Startup to be done because a user fxn may set MultiProc id */
    if (!Startup_Module_startupDone()) {
        return (Startup_NOTDONE);
    }

    /* Don't initialize the spinlocks if not the owner of region 0 */
    SharedRegion_getEntry(0, &entry);
    if (MultiProc_self() != entry.ownerProcId || !(entry.isValid)) {
        return (Startup_DONE);
    }

    /*
     *  See OMAP4 TRM section 21.4.1.2.1
     *  Spinlocks Clearing After a System Bug Recovery
     */

    for (i = 0; i < GateHWSpinlock_numLocks; i++) {
        if (reservedMaskArr[i >> 5] & (1 << (i % 32))) {
            /* Don't reset reserved spinlocks */
            continue;
        }
        baseAddr[i] = 0;
    }

    return (Startup_DONE);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== GateHWSpinlock_Instance_init ========
 */
Void GateHWSpinlock_Instance_init(GateHWSpinlock_Object *obj,
                            IGateProvider_Handle localGate,
                            const GateHWSpinlock_Params *params)
{
    /* Assert that params->resourceId is valid */
    Assert_isTrue(params->resourceId < GateHWSpinlock_numLocks,
                  GateHWSpinlock_A_invSpinLockNum);

    obj->localGate      = localGate;
    obj->lockNum        = params->resourceId;
    obj->nested         = 0;

    /* Check for dynamic open */
    if (params->openFlag) {
        Log_write1(GateHWSpinlock_LM_open, (UArg)obj->lockNum);
    }
    else {
        Log_write1(GateHWSpinlock_LM_create, (UArg)obj->lockNum);
    }
}

/*
 *  ======== GateHWSpinlock_enter ========
 */
IArg GateHWSpinlock_enter(GateHWSpinlock_Object *obj)
{
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSpinlock_baseAddr;
    IArg key;

    key = IGateProvider_enter(obj->localGate);

    /* If the gate object has already been entered, return the nested value */
    obj->nested++;
    if (obj->nested > 1) {
        return (key);
    }

    /* Enter the spinlock */
    while (1) {
        if (baseAddr[obj->lockNum] == 0) {
            break;
        }

        obj->nested--; /* Restore state of delegate object */
        IGateProvider_leave(obj->localGate, key);
        key = IGateProvider_enter(obj->localGate);
        obj->nested++; /* Re-nest the gate */
    }

    Log_write2(GateHWSpinlock_LM_enter,(UArg)obj->lockNum, key);

    return (key);
}

/*
 *  ======== GateHWSpinlock_leave ========
 */
Void GateHWSpinlock_leave(GateHWSpinlock_Object *obj, IArg key)
{
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSpinlock_baseAddr;

    obj->nested--;

    /* Leave the spinlock if the leave() is not nested */
    if (obj->nested == 0) {
        baseAddr[obj->lockNum] = 0;
    }

    IGateProvider_leave(obj->localGate, key);

    Log_write2(GateHWSpinlock_LM_leave, (UArg)obj->lockNum, key);
}

/*
 *  ======== GateHWSpinlock_getResourceId ========
 */
Bits32 GateHWSpinlock_getResourceId(GateHWSpinlock_Object *obj)
{
    return (obj->lockNum);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== GateHWSpinlock_getReservedMask ========
 */
Bits32 *GateHWSpinlock_getReservedMask()
{
    return ((Bits32 *)GateHWSpinlock_reservedMaskArr);
}

/*
 *  ======== GateHWSpinlock_sharedMemReq ========
 */
SizeT GateHWSpinlock_sharedMemReq(const IGateMPSupport_Params *params)
{
    return (0);
}

/*
 *  ======== GateHWSpinlock_query ========
 */
Bool GateHWSpinlock_query(Int qual)
{
    Bool rc;

    switch (qual) {
        case IGateProvider_Q_BLOCKING:
            /* Depends on gate proxy? */
            rc = FALSE;
            break;

        case IGateProvider_Q_PREEMPTING:
            /* Depends on gate proxy? */
            rc = TRUE;
            break;
        default:
            rc = FALSE;
            break;
    }
    return (rc);
}
