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
 *  ======== InterruptArp32.c ========
 *  ARP32 mailbox based interrupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/family/arp32/Hwi.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/InterruptArp32.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Assigned mailboxes */
#define DSP_TO_ARP32      0
#define ARP32_TO_DSP      1

#define MAILBOX_REG_VAL(M)   (0x1 << (2 * M))

#define MAILBOX_MESSAGE(M) (InterruptArp32_mailboxBaseAddr + 0x040 + (0x4 * M))
#define MAILBOX_STATUS(M)  (InterruptArp32_mailboxBaseAddr + 0x0C0 + (0x4 * M))

/* ARP32 registers */
#define MBX_INTR_TO_ARP32 0
#define MBX_INTR_TO_DSP 1

#define MAILBOX_IRQSTATUS_CLR(INTR_NUM)  (InterruptArp32_mailboxBaseAddr + 0x104 + ((INTR_NUM) * 0x10))

#define MAILBOX_IRQENABLE_SET(INTR_NUM)  (InterruptArp32_mailboxBaseAddr + 0x108 + ((INTR_NUM) * 0x10))

#define MAILBOX_IRQENABLE_CLR(INTR_NUM)  (InterruptArp32_mailboxBaseAddr + 0x10C + ((INTR_NUM) * 0x10))

#define ARP32INT           29

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== InterruptArp32_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptArp32_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    REG32(MAILBOX_IRQENABLE_SET(MBX_INTR_TO_ARP32)) = MAILBOX_REG_VAL(DSP_TO_ARP32);
    Hwi_enableInterrupt(ARP32INT);
}

/*!
 *  ======== InterruptArp32_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptArp32_intDisable(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    REG32(MAILBOX_IRQENABLE_CLR(MBX_INTR_TO_ARP32)) = MAILBOX_REG_VAL(DSP_TO_ARP32);
    Hwi_disableInterrupt(ARP32INT);
}

/*!
 *  ======== InterruptArp32_intRegister ========
 */
Void InterruptArp32_intRegister(UInt16 remoteProcId,
                                 IInterrupt_IntInfo *intInfo,
                                 Fxn func, UArg arg)
{
    UInt        key;
    Hwi_Params  hwiAttrs;
    Error_Block eb;
    InterruptArp32_FxnTable *table;

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_internal);

    /* Assert that our MultiProc id is set correctly */
    Assert_isTrue((InterruptArp32_arp32ProcId == MultiProc_self()),
                   ti_sdo_ipc_Ipc_A_internal);

    /* init error block */
    Error_init(&eb);

    /* Disable global interrupts */
    key = Hwi_disable();

    table = &(InterruptArp32_module->fxnTable);
    table->func = func;
    table->arg  = arg;

    InterruptArp32_intClear(remoteProcId, intInfo);

    /* Make sure the interrupt only gets plugged once */
    InterruptArp32_module->numPlugged++;
    if (InterruptArp32_module->numPlugged == 1) {
        /* Register interrupt to remote processor */
        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.arg = arg;
        hwiAttrs.vectorNum = intInfo->intVectorId;

        Hwi_create(ARP32INT,
                  (Hwi_FuncPtr)InterruptArp32_intShmStub,
                   &hwiAttrs,
                   &eb);
    }

    /* enable the mailbox and Hwi */
    InterruptArp32_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*!
 *  ======== InterruptArp32_intUnregister ========
 */
Void InterruptArp32_intUnregister(UInt16 remoteProcId,
                                   IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle  hwiHandle;
    InterruptArp32_FxnTable *table;

    /* Disable the mailbox interrupt source */
    InterruptArp32_intDisable(remoteProcId, intInfo);

    InterruptArp32_module->numPlugged--;
    if (InterruptArp32_module->numPlugged == 0) {
        /* Delete the Hwi */
        hwiHandle = Hwi_getHandle(intInfo->intVectorId);
        Hwi_delete(&hwiHandle);
    }

    /* Clear the FxnTable entry for the remote processor */
    table = &(InterruptArp32_module->fxnTable);
    table->func = NULL;
    table->arg  = 0;
}


/*!
 *  ======== InterruptArp32_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptArp32_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;

    /* disable interrupts */
    key = Hwi_disable();

    if (REG32(MAILBOX_STATUS(ARP32_TO_DSP)) == 0) {
        /* write the mailbox message to dsp */
        REG32(MAILBOX_MESSAGE(ARP32_TO_DSP)) = arg;
    }

    /* restore interrupts */
    Hwi_restore(key);
}


/*!
 *  ======== InterruptArp32_intPost ========
 *  Simulate an interrupt from a remote processor
 */
Void InterruptArp32_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;

    /* disable interrupts */
    key = Hwi_disable();

    if (REG32(MAILBOX_STATUS(DSP_TO_ARP32)) == 0) {
        /* write the mailbox message to arp32 */
        REG32(MAILBOX_MESSAGE(DSP_TO_ARP32)) = arg;
    }

    /* restore interrupts */
    Hwi_restore(key);
}


/*!
 *  ======== InterruptArp32_intClear ========
 *  Clear interrupt
 */
UInt InterruptArp32_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    /* DSP to ARP32 */
    arg = REG32(MAILBOX_MESSAGE(DSP_TO_ARP32));

    /* clear the dsp mailbox */
    REG32(MAILBOX_IRQSTATUS_CLR(MBX_INTR_TO_ARP32)) = MAILBOX_REG_VAL(DSP_TO_ARP32);

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*!
 *  ======== InterruptArp32_intShmStub ========
 */
Void InterruptArp32_intShmStub(UArg arg)
{
    InterruptArp32_FxnTable *table;

    if ((REG32(MAILBOX_IRQENABLE_SET(MBX_INTR_TO_ARP32)) &
        MAILBOX_REG_VAL(DSP_TO_ARP32)) &&
        REG32(MAILBOX_STATUS(DSP_TO_ARP32)) != 0) { /* DSP to ARP32 */
        /* call function with arg */
        table = &(InterruptArp32_module->fxnTable);
        (table->func)(table->arg);
    }
}
