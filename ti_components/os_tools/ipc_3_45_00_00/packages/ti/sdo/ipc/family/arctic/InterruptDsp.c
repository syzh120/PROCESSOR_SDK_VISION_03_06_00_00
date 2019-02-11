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
 *  ======== InterruptDsp.c ========
 *  Mailbox based interrupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/InterruptDsp.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Assigned mailboxes */
#define DSP_TO_ARP32      0
#define ARP32_TO_DSP      1

#define MAILBOX_REG_VAL(M)   (0x1 << (2 * M))

#define MAILBOX_MESSAGE(M)   (InterruptDsp_mailboxBaseAddr + 0x40 + (0x4 * M))
#define MAILBOX_STATUS(M)    (InterruptDsp_mailboxBaseAddr + 0xC0 + (0x4 * M))

#define MBX_INTR_TO_ARP32 0
#define MBX_INTR_TO_DSP 1

#define MAILBOX_IRQSTATUS_CLR(INTR_NUM)  (InterruptDsp_mailboxBaseAddr + 0x104 + ((INTR_NUM) * 0x10))

#define MAILBOX_IRQENABLE_SET(INTR_NUM)  (InterruptDsp_mailboxBaseAddr + 0x108 + ((INTR_NUM) * 0x10))

#define MAILBOX_IRQENABLE_CLR(INTR_NUM)  (InterruptDsp_mailboxBaseAddr + 0x10C + ((INTR_NUM) * 0x10))

#define MAILBOX_EOI_REG             (InterruptDsp_mailboxBaseAddr + 0x140)

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== InterruptDsp_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptDsp_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    REG32(MAILBOX_IRQENABLE_SET(MBX_INTR_TO_DSP)) = MAILBOX_REG_VAL(ARP32_TO_DSP);
}

/*!
 *  ======== InterruptDsp_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptDsp_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    REG32(MAILBOX_IRQENABLE_CLR(MBX_INTR_TO_DSP)) = MAILBOX_REG_VAL(ARP32_TO_DSP);
}

/*!
 *  ======== InterruptDsp_intRegister ========
 */
Void InterruptDsp_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                              Fxn func, UArg arg)
{
    UInt        key;
    Hwi_Params  hwiAttrs;
    Error_Block eb;
    InterruptDsp_FxnTable *table;

    Assert_isTrue(intInfo->intVectorId <= 15, ti_sdo_ipc_Ipc_A_internal);

    /* init error block */
    Error_init(&eb);

    /* Disable global interrupts */
    key = Hwi_disable();

    table = &(InterruptDsp_module->fxnTable);
    table->func = func;
    table->arg  = arg;

    InterruptDsp_intClear(remoteProcId, intInfo);

    /* Make sure the interrupt only gets plugged once */
    InterruptDsp_module->numPlugged++;
    if (InterruptDsp_module->numPlugged == 1) {
        /* Register interrupt to remote processor */
        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.arg = arg;
        hwiAttrs.eventId = 90;

        Hwi_create(intInfo->intVectorId,
                   (Hwi_FuncPtr)InterruptDsp_intShmStub,
                   &hwiAttrs,
                   &eb);

        /* enable the interrupt vector */
        Hwi_enableInterrupt(intInfo->intVectorId);
    }

    /* Enable the mailbox interrupt to the DSP */
    InterruptDsp_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*!
 *  ======== InterruptDsp_intUnregister ========
 */
Void InterruptDsp_intUnregister(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle  hwiHandle;
    InterruptDsp_FxnTable *table;

    /* Disable the mailbox interrupt source */
    InterruptDsp_intDisable(remoteProcId, intInfo);

    InterruptDsp_module->numPlugged--;
    if (InterruptDsp_module->numPlugged == 0) {
        /* Delete the Hwi */
        hwiHandle = Hwi_getHandle(intInfo->intVectorId);
        Hwi_delete(&hwiHandle);
    }

    /* Clear the FxnTable entry for the remote processor */
    table = &(InterruptDsp_module->fxnTable);
    table->func = NULL;
    table->arg  = 0;
}

/*!
 *  ======== InterruptDsp_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptDsp_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt key;

    /*
     *  Before writing to a mailbox, check whehter it already contains a message
     *  If so, then don't write to the mailbox since we want one and only one
     *  message per interrupt.  Disable interrupts between reading
     *  the MSGSTATUS_X register and writing to the mailbox to protect from
     *  another thread doing an intSend at the same time
     *
     *  Note regarding possible race condition between local 'intSend' and
     *  remote 'intClear':
     *  It is possible that we we read the MAILBOX_MSGSTATUS_X register during
     *  the remote side's intClear.  Therefore, we might choose _not_ to send
     *  write to the mailbox even though the mailbox is about to be cleared a
     *  few cycles later. In this case, the interrupt will be lost.
     *  This is OK, however. intClear should always be called by the Notify
     *  driver _before_ shared memory is read, so the event will be picked up
     *  anyway by the previous interrupt that caused intClear to be called.
     */
    key = Hwi_disable();

    if (REG32(MAILBOX_STATUS(DSP_TO_ARP32)) == 0) {
        /* write the mailbox message to arp32 */
        REG32(MAILBOX_MESSAGE(DSP_TO_ARP32)) = arg;
    }

    /* restore interrupts */
    Hwi_restore(key);
}

/*!
 *  ======== InterruptDsp_intPost ========
 */
Void InterruptDsp_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
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
 *  ======== InterruptDsp_intClear ========
 *  Clear interrupt
 */
UInt InterruptDsp_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    arg = REG32(MAILBOX_MESSAGE(ARP32_TO_DSP));

    /* clear the dsp mailbox */
    REG32(MAILBOX_IRQSTATUS_CLR(MBX_INTR_TO_DSP)) = MAILBOX_REG_VAL(ARP32_TO_DSP);

    /* Write to EOI (End Of Interrupt) register */
    REG32(MAILBOX_EOI_REG) = 0x1;

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*!
 *  ======== InterruptDsp_intShmStub ========
 */
Void InterruptDsp_intShmStub(UArg arg)
{
    InterruptDsp_FxnTable *table;

    if (((REG32(MAILBOX_IRQENABLE_SET(MBX_INTR_TO_DSP)) &
        MAILBOX_REG_VAL(ARP32_TO_DSP)) &&
        REG32(MAILBOX_STATUS(ARP32_TO_DSP))) != 0) {
        /* call function with arg */
        table = &(InterruptDsp_module->fxnTable);
        (table->func)(table->arg);
    }
}
