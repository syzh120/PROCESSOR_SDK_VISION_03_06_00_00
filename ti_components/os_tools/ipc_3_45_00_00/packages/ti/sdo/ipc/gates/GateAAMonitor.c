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
 *  ======== GateAAMonitor.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/family/c64p/Cache.h>
#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include "package/internal/GateAAMonitor.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_SharedRegion.h>

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== GateAAMonitor_Instance_init ========
 */
Int GateAAMonitor_Instance_init(GateAAMonitor_Object *obj,
                                IGateProvider_Handle localGate,
                                const GateAAMonitor_Params *params,
                                Error_Block *eb)
{
    /* Assert that params->sharedAddr is valid */
    Assert_isTrue(
        (UInt32)params->sharedAddr >= GateAAMonitor_SL2_RANGE_BASE &&
        (UInt32)params->sharedAddr <  GateAAMonitor_SL2_RANGE_MAX,
        GateAAMonitor_A_invSharedAddr);

    obj->localGate  = localGate;
    obj->sharedAddr = (Ptr)_Ipc_roundup(params->sharedAddr,
            GateAAMonitor_CACHELINE_SIZE);
    obj->nested = 0;

    if (!params->openFlag) {
        /*
         *  The processor that inits the AAM initializes the value
         *  to zero (e.g. no one is using it). The other processors
         *  must invalidate the memory in case it is in cache.
         */
        *(obj->sharedAddr) = 0;
        Cache_wbInv((Ptr)obj->sharedAddr, GateAAMonitor_CACHELINE_SIZE,
                    Cache_Type_ALL, TRUE);
    }
    else {
        /* Opening. */
        Cache_inv((Ptr)obj->sharedAddr, GateAAMonitor_CACHELINE_SIZE,
                  Cache_Type_ALL, TRUE);
    }

    return (0);
}

/*
 *  ======== GateAAMonitor_enter ========
 */
IArg GateAAMonitor_enter(GateAAMonitor_Object *obj)
{
    IArg key;

    key = IGateProvider_enter(obj->localGate);

    /* If the gate object has already been entered, return the nested value */
    obj->nested++;
    if (obj->nested > 1) {
        return (key);
    }

    /* Enter the monitor */
    GateAAMonitor_getLock((Ptr)obj->sharedAddr);

    return (key);
}

/*
 *  ======== GateAAMonitor_leave ========
 *  The sharedAddr must come from SL2 (shared L2 memory) so we only
 *  have to freeze L1D.
 */
Void GateAAMonitor_leave(GateAAMonitor_Object *obj, IArg key)
{
    Cache_Mode mode;
    UInt hwiKey;

    obj->nested--;

    if (obj->nested == 0) {
        /* disable interrupts before setting Cache to FREEZE */
        hwiKey = Hwi_disable();

        mode = Cache_setMode(Cache_Type_L1D, Cache_Mode_FREEZE);

        /* Leave the critical region by setting address value to zero */
        *(obj->sharedAddr) = 0;

        Cache_setMode(Cache_Type_L1D, mode);

        /* restore interrupts */
        Hwi_restore(hwiKey);
    }

    IGateProvider_leave(obj->localGate, key);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== GateAAMonitor_getReservedMask ========
 */
Bits32 *GateAAMonitor_getReservedMask()
{
    /* This gate doesn't allow reserving resources */
    return (NULL);
}

/*
 *  ======== GatePeterson_sharedMemReq ========
 */
SizeT GateAAMonitor_sharedMemReq(const IGateMPSupport_Params *params)
{
    SizeT memReq;

    memReq = (SizeT)(2 * GateAAMonitor_CACHELINE_SIZE);

    return (memReq);
}

/*
 *  ======== GateAAMonitor_query ========
 */
Bool GateAAMonitor_query(Int qual)
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
