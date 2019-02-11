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
 *  ======== GateHWSem.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Startup.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include "package/internal/GateHWSem.xdc.h"

/*
 *  ======== GateHWSem_Module_startup ========
 *  release the HW semaphore if the core owns it.
 */
Int GateHWSem_Module_startup(Int phase)
{
    Int i;
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSem_baseAddr;
    Bits32 *reservedMaskArr = (Bits32 *)GateHWSem_reservedMaskArr;

    /* releases the HW semaphore if the core owns it otherwise its a nop */
    for (i = 0; i < GateHWSem_numSems; i++) {
        if (reservedMaskArr[i >> 5] & (1 << (i % 32))) {
            /* Don't reset reserved HW semaphores */
            continue;
        }
        baseAddr[i] = 1;
    }

    return (Startup_DONE);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== GateHWSem_Instance_init ========
 */
Void GateHWSem_Instance_init(GateHWSem_Object *obj,
                            IGateProvider_Handle localGate,
                            const GateHWSem_Params *params)
{
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSem_baseAddr;

    /* Assert that params->resourceId is valid */
    Assert_isTrue(params->resourceId < GateHWSem_numSems,
                  GateHWSem_A_invSemNum);

   /* Create the local gate */
    obj->localGate  = localGate;
    obj->semNum     = params->resourceId;
    obj->nested     = 0;

    /* Check for dynamic open */
    if (!params->openFlag) {
        /* Reset the hardware semaphore */
        baseAddr[obj->semNum] = 1;
    }
}

/*
 *  ======== GateHWSem_enter ========
 */
IArg GateHWSem_enter(GateHWSem_Object *obj)
{
    IArg key;
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSem_baseAddr;

    key = IGateProvider_enter(obj->localGate);

    /* If the gate object has already been entered, return the nested value */
    obj->nested++;
    if (obj->nested > 1) {
        return (key);
    }

    /* Enter the hardware lock */
    while (baseAddr[obj->semNum] != 1) {
        obj->nested--; /* Restore state of delegate object */
        IGateProvider_leave(obj->localGate, key);
        key = IGateProvider_enter(obj->localGate);
        obj->nested++; /* Re-nest the gate */
    }

    return (key);
}

/*
 *  ======== GateHWSem_leave ========
 */
Void GateHWSem_leave(GateHWSem_Object *obj, IArg key)
{
    volatile UInt32 *baseAddr = (volatile UInt32 *)GateHWSem_baseAddr;

    obj->nested--;

    if (obj->nested == 0) {
        /* Leave the critical region by setting address value to 1 */
        baseAddr[obj->semNum] = 1;
    }

    IGateProvider_leave(obj->localGate, key);
}

/*
 *  ======== GateHWSem_getResourceId ========
 */
Bits32 GateHWSem_getResourceId(GateHWSem_Object *obj)
{
    return (obj->semNum);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== GateHWSem_getReservedMask ========
 */
Bits32 *GateHWSem_getReservedMask()
{
    return ((Bits32 *)GateHWSem_reservedMaskArr);
}

/*
 *  ======== GateHWSem_query ========
 */
Bool GateHWSem_query(Int qual)
{
    Bool rc;

    switch (qual) {
        case IGateProvider_Q_BLOCKING:
            /* Depends on gate proxy? */
            rc = TRUE;
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

/*
 *  ======== GateHWSem_sharedMemReq ========
 */
SizeT GateHWSem_sharedMemReq(const IGateMPSupport_Params *params)
{
    /* No shared memory needed */
    return (0);
}
