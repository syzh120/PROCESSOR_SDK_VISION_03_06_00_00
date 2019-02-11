/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *  ======== Interrupt.c ========
 *  C647x based interrupt manager.
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_SharedRegion.h>

#include <ti/sdo/ipc/family/c647x/MultiProcSetup.h>

#include "package/internal/Interrupt.xdc.h"


/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== Interrupt_Module_startup ========
 */
Int Interrupt_Module_startup(Int phase)
{
    volatile UInt32 *kick0 = (volatile UInt32 *)Interrupt_KICK0;
    volatile UInt32 *kick1 = (volatile UInt32 *)Interrupt_KICK1;
    SharedRegion_Entry entry;
    UInt16 procId = MultiProc_self();

    /*
     *  Wait for Startup to be done (if MultiProc id not yet set) because a
     *  user fxn should set it
     */
    if (!Startup_Module_startupDone() && procId == MultiProc_INVALIDID) {
        return (Startup_NOTDONE);
    }

    if (!Interrupt_enableKick) {
        /* Do not unlock the kick registers */
        return (Startup_DONE);
    }

    SharedRegion_getEntry(0, &entry);

    /*
     * Only write to the KICK registers if:
     * - This core is the SR0 owner
     * - There is no SR0 and this core has procId '0'
     */
    if ((entry.isValid && procId == entry.ownerProcId) ||
        (!entry.isValid && procId == 0)) {
        if (Interrupt_KICK0 && Interrupt_KICK1){
            /* unlock the KICK mechanism in the Bootcfg MMRs if defined */
            kick0[0] = 0x83e70b13;      /* must be written with this value */
            kick1[0] = 0x95a4f1e0;      /* must be written with this value */
        }
    }

    return (Startup_DONE);
}

/*
 *  ======== Interrupt_intEnable ========
 *  Enable interrupt
 */
Void Interrupt_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_enableInterrupt(intInfo->intVectorId);
}

/*
 *  ======== Interrupt_intDisable ========
 *  Disables interrupts
 */
Void Interrupt_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_disableInterrupt(intInfo->intVectorId);
}

/*
 *  ======== Interrupt_intRegister ========
 *  Register ISR for remote processor interrupt
 */
Void Interrupt_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                           Fxn func, UArg arg)
{
    UInt key, i;
    Hwi_Params hwiAttrs;

    /* Disable global interrupts */
    key = Hwi_disable();

    /* setup the function table using the same Hwi int */
    Interrupt_module->args[remoteProcId] = arg;

    /* Make sure the interrupt only gets plugged once */
    Interrupt_module->numPlugged++;
    if (Interrupt_module->numPlugged == 1) {
        Interrupt_module->func = func;

        /* Clear any pending interrupt */
        for (i = 0; i < ti_sdo_utils_MultiProc_numProcessors; i++) {
            Interrupt_intClear(i, NULL);
        }

        /* Register interrupt to remote processor */
        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.maskSetting = Hwi_MaskingOption_SELF;
        hwiAttrs.arg         = arg;
        hwiAttrs.eventId     = Interrupt_INTERDSPINT;

        Hwi_create(intInfo->intVectorId,
            (Hwi_FuncPtr)Interrupt_intShmStub, &hwiAttrs, NULL);

        Hwi_enableInterrupt(intInfo->intVectorId);
    }

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== Interrupt_intUnregister ========
 */
Void Interrupt_intUnregister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle hwiHandle;

    Interrupt_module->numPlugged--;
    if (Interrupt_module->numPlugged == 0) {
        /* No need to disable interrupt: Hwi_delete takes care of this */
        hwiHandle = Hwi_getHandle(intInfo->intVectorId);
        Hwi_delete(&hwiHandle);

        /* unset the function */
        Interrupt_module->func = NULL;
    }

    /* Unset the function table */
    Interrupt_module->args[remoteProcId] = 0;
}

/*
 *  ======== Interrupt_intSend ========
 *  Send interrupt to the remote processor
 */
Void Interrupt_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                       UArg arg)
{
    UInt32 val;
    extern volatile cregister UInt DNUM;
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;

    /*
     *  bit 0 is set to generate interrupt.
     *  bits 4-7 is set to specify the interrupt generation source.
     *  The convention is that bit 4 (SRCS0) is used for core 0,
     *  bit 5 (SRCS1) for core 1, etc... .
     */
    val = (1 << (DNUM + Interrupt_SRCSx_SHIFT)) | 1;

    ipcgr[MultiProcSetup_procMap[remoteProcId]] =  val;
}

/*
 *  ======== Interrupt_intPost ========
 *  Send interrupt to the remote processor
 */
Void Interrupt_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                       UArg arg)
{
    UInt32 val;
    extern volatile cregister UInt DNUM;
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;

    /*
     *  bit 0 is set to generate interrupt.
     *  bits 4-7 is set to specify the interrupt generation source.
     *  The convention is that bit 4 (SRCS0) is used for core 0,
     *  bit 5 (SRCS1) for core 1, etc... .
     */
    val = (1 << (MultiProcSetup_procMap[srcProcId] + Interrupt_SRCSx_SHIFT)) | 1;

    ipcgr[DNUM] =  val;
}

/*
 *  ======== Interrupt_intClear ========
 *  Acknowledge interrupt by clearing the corresponding source bit.
 *  Does not clear the IFR bit by way of ICR write because that should
 *  only be done during init time.
 */
UInt Interrupt_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    extern volatile cregister UInt DNUM;
    volatile UInt32 *ipcar = (volatile UInt32 *)Interrupt_IPCAR0;

    ipcar[DNUM] =  (1 << (MultiProcSetup_procMap[remoteProcId] +
            Interrupt_SRCSx_SHIFT));

    return (0);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*
 *  ======== Interrupt_intShmStub ========
 */
Void Interrupt_intShmStub(UArg arg)
{
    Int i;
    extern volatile cregister UInt DNUM;
    volatile UInt32 *ipcar = (volatile UInt32 *)Interrupt_IPCAR0;
    UInt32 ipcarVal = ipcar[DNUM];

    for (i = 0; i < ti_sdo_utils_MultiProc_numProcsInCluster; i++) {
        if ((ipcarVal) & (1 << (MultiProcSetup_procMap[i +
            MultiProc_getBaseIdOfCluster()]
            + Interrupt_SRCSx_SHIFT))) {
            Interrupt_module->func(Interrupt_module->args[i +
                MultiProc_getBaseIdOfCluster()]);
        }
    }
}
