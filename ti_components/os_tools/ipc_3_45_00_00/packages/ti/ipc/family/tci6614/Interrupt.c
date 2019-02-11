/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/ipc/MultiProc.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "Interrupt.h"

#include "package/internal/Interrupt.xdc.h"

extern volatile cregister UInt DNUM;

Fxn userFxn = NULL;
Void Interrupt_isr(UArg arg);

/* Shift to source bit id for CORES 0-3 */
#define MAP_TO_BITPOS(intId) \
     ((intId) == (Interrupt_SRCS_BITPOS_CORE0) ? ((intId) + (DNUM)) : (intId))

/*
 * Map remoteProcId to CORE ID [0-3]
 * NOTE: This assumes that HOST is at MultiProcId == 0, and CORE0 at 1i
 */
#define MAP_RPROCID_TO_COREID(rProcId)     ((rProcId)-1)

#define MAP_RPROCID_TO_SRCC(rProcId, intId) \
         ((intId) == (Interrupt_SRCS_BITPOS_CORE0) ?  \
         ((intId) + ((rProcId)-1)) : (intId))
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
    UInt16 procId = MultiProc_self();

    /*
     * If this assert fails, the MultiProc config has changed to break
     * an assumption in Linux rpmsg driver, that HOST is listed first in
     * MultiProc ID configuration.
     */
    Assert_isTrue(0 == MultiProc_getId("HOST"), NULL);

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

    /*
     * Only write to the KICK registers if:
     * - This core is the SR0 owner
     * - There is no SR0 and this core has procId '1' (IPC 3.x: this case).
     */
    /* TODO: What if CORE0 is not started, but the others are? */
    if (DNUM == 0) {
        if (Interrupt_KICK0 && Interrupt_KICK1){
            /* unlock the KICK mechanism in the Bootcfg MMRs if defined */
            kick0[0] = 0x83e70b13;      /* must be written with this value */
            kick1[0] = 0x95a4f1e0;      /* must be written with this value */
        }
    }

    return (Startup_DONE);
}

/*!
 *  ======== Interrupt_intEnable ========
 *  Enable interrupt
 */
Void Interrupt_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_enableInterrupt(intInfo->intVectorId);
}

/*!
 *  ======== Interrupt_intDisable ========
 *  Disables interrupts
 */
Void Interrupt_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_disableInterrupt(intInfo->intVectorId);
}

Void Interrupt_intClearAll()
{
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;
    volatile UInt32 *ipcar = (volatile UInt32 *)Interrupt_IPCAR0;
    UInt val = ipcgr[DNUM]; /* Interrupt source bits */

    ipcar[DNUM] = val;
}


/*
 *  ======== Interrupt_intRegister ========
 *  Register ISR for remote processor interrupt
 */
Void Interrupt_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                           Fxn func, UArg arg)
{
    Hwi_Params hwiAttrs;
    Interrupt_FxnTable *table;

    UInt pos;
    Assert_isTrue(intInfo != NULL, NULL);

    pos = MAP_RPROCID_TO_SRCC(remoteProcId, intInfo->localIntId);

    Log_print2(Diags_USER1, "Interrupt_intRegister: pos: %d, func: 0x%x\n",
              (IArg)pos, (IArg)func);

    /* setup the function table with client function and arg to call: */
    table = &(Interrupt_module->fxnTable[pos]);
    table->func = func;
    table->arg  = arg;

    /* Make sure the interrupt only gets plugged once */
    Interrupt_module->numPlugged++;
    if (Interrupt_module->numPlugged == 1) {
        /* Clear all pending interrupts */
        Interrupt_intClearAll();

        /* Register interrupt to remote processor */
        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.maskSetting = Hwi_MaskingOption_SELF;
        hwiAttrs.arg         = arg;
        hwiAttrs.eventId     = Interrupt_INTERDSPINT;

        Hwi_create(intInfo->intVectorId,
            (Hwi_FuncPtr)Interrupt_isr, &hwiAttrs, NULL);

        Hwi_enableInterrupt(intInfo->intVectorId);
    }
}

Void Interrupt_intUnregister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle hwiHandle;
    Interrupt_FxnTable *table;
    UInt pos;

    Assert_isTrue(intInfo != NULL, NULL);

    Interrupt_module->numPlugged--;
    if (Interrupt_module->numPlugged == 0) {
        /* No need to disable interrupt: Hwi_delete takes care of this */
        hwiHandle = Hwi_getHandle(intInfo->intVectorId);
        Hwi_delete(&hwiHandle);
    }

    /* Unset the function table */
    pos = MAP_RPROCID_TO_SRCC(remoteProcId, intInfo->localIntId);

    table = &(Interrupt_module->fxnTable[pos]);
    table->func = NULL;
    table->arg  = 0;
}

/*!
 *  ======== Interrupt_intSend ========
 *  Send interrupt to the remote processor, identifying this core as source.
 *  If CORE0 BIT POS, we add DNUM to identify this core as the source;
 *  Otherwise, we just use the localIntId as the source bit position.
 */
Void Interrupt_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt32 val;
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;
    volatile UInt32 *ipcgrh = (volatile UInt32 *)Interrupt_IPCGRH;
    UInt pos;

    Assert_isTrue((intInfo != NULL), NULL);
    pos = MAP_TO_BITPOS(intInfo->localIntId);

    /*
     *  bit 0 is set to generate the interrupt.
     *  bits 4-7 are set to specify the interrupt generation source.
     *  The convention is that bit 4 (SRCS0) is used for core 0,
     *  bit 5 (SRCS1) for core 1, etc... .
     */
    val = (1 << pos) | 1;
    Log_print3(Diags_USER1,
        "Interrupt_intSend: setting bit %d in SRCS as 0x%x to for rprocId #%d",
        (IArg)pos, (IArg)val, (IArg)remoteProcId);

    if (remoteProcId == MultiProc_getId("HOST"))
    {
        /* Interrupt is to be generated on the Host processor.  Go through
         * IPCGRH register
         */
        *ipcgrh = val;
    }
    else
    {
        /* Interrupt is to be generated on another DSP. */
        ipcgr[MAP_RPROCID_TO_COREID(remoteProcId)] =  val;
    }
}

/*
 *  ======== Interrupt_intClear ========
 *  Acknowledge interrupt by clearing the corresponding source bit.
 *
 *  intInfo->localIntId encodes the Source bit position to be cleared.
 *  If this corresponds to Core0, adjust using remoteProcId to get true
 *  SRCS bit position for the DSP core.
 *
 *  Otherwise, the localIntId is used directly as the bit position.
 *
 *  Only callers setting remoteProcId == HOST id care about return value.
 */
UInt Interrupt_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;
    volatile UInt32 *ipcar = (volatile UInt32 *)Interrupt_IPCAR0;
    UInt payload = Interrupt_INVALIDPAYLOAD;
    UInt val = ipcgr[DNUM]; /* Interrupt source bits */
    UInt pos;

    Assert_isTrue((intInfo != NULL), NULL);
    pos = MAP_RPROCID_TO_SRCC(remoteProcId, intInfo->localIntId);
    ipcar[DNUM] = (1 << pos);

    Log_print2(Diags_USER1, "Interrupt_intClear: ipcgr: 0x%x, cleared: 0x%x\n",
                            val, (1 << pos));

    if (remoteProcId == MultiProc_getId("HOST")) {
        payload = ((val & (UInt)(1 << Interrupt_SRCS_BITPOS_HOST)) ? val :
                    Interrupt_INVALIDPAYLOAD);
    }

    return (payload);
}

/*
 *  ======== Interrupt_checkAndClear ========
 *  Return 1 if the interrupt was set (if so, we clear it);
 *  Otherwise, returns 0.
 */
UInt Interrupt_checkAndClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;
    volatile UInt32 *ipcar = (volatile UInt32 *)Interrupt_IPCAR0;
    UInt val = ipcgr[DNUM]; /* Interrupt source bits */
    UInt pos;

    Assert_isTrue((intInfo != NULL), NULL);

    pos = MAP_TO_BITPOS(intInfo->localIntId);
    if (val & (1 << pos)) {
        ipcar[DNUM] = (1 << pos);
        return(1);
    }

    return(0);
}

/*
 *  ======== Interrupt_isr ========
 */
Void Interrupt_isr(UArg arg)
{
    Int i;
    Interrupt_FxnTable *table;
    volatile UInt32 *ipcgr = (volatile UInt32 *)Interrupt_IPCGR0;
    volatile UInt32 *ipcar = (volatile UInt32 *)Interrupt_IPCAR0;
    UInt val = ipcgr[DNUM]; /* Interrupt source bits */

    Log_print1(Diags_USER1,
        "Interrupt_isr: Interrupt(s) received: 0x%x", (IArg)val);

    for (i = Interrupt_SRCS_BITPOS_CORE0; i < 32; i++) {
        if (val & (1 << i)) {
            /* Clear the specific interrupt: */
            ipcar[DNUM] = (1 << i);

            /* Call the client function: */
            table = &(Interrupt_module->fxnTable[i]);
            if (table->func != NULL) {
                Log_print1(Diags_USER1,
                    "Interrupt_isr: source id bit: %d", i);
                (table->func)(table->arg);
            }
        }
    }
}
