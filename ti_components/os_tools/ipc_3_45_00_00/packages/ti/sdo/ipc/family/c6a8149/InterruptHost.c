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
 *  ======== InterruptHost.c ========
 *  Mailbox based interrupt manager
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/family/arm/a8/intcps/Hwi.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_Ipc.h>

#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/InterruptHost.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Assigned mailboxes */
#define DSP_TO_HOST      0
#define DSP_TO_VIDEO     1
#define DSP_TO_VPSS      2
#define HOST_TO_DSP      3
#define HOST_TO_VIDEO    4
#define HOST_TO_VPSS     5
#define VIDEO_TO_HOST    6
#define VIDEO_TO_DSP     7
#define VPSS_TO_HOST     8
#define VPSS_TO_DSP      9

#define MAILBOX_MESSAGE(M)   (InterruptHost_mailboxBaseAddr + 0x040 + (0x4 * M))
#define MAILBOX_STATUS(M)    (InterruptHost_mailboxBaseAddr + 0x0C0 + (0x4 * M))

#define MAILBOX_REG_VAL(M)   (0x1 << (2 * M))

#define MAILBOX_IRQSTATUS_CLR_HOST  (InterruptHost_mailboxBaseAddr + 0x104)
#define MAILBOX_IRQENABLE_SET_HOST  (InterruptHost_mailboxBaseAddr + 0x108)
#define MAILBOX_IRQENABLE_CLR_HOST  (InterruptHost_mailboxBaseAddr + 0x10C)

#define MAILBOX_HOSTINT        77

/* Assigned eve mailbox users */
#define EVE_TO_HOST     0
#define EVE_TO_DSP      1
#define EVE_TO_VIDEO    2
#define HOST_TO_EVE     3
#define DSP_TO_EVE      4
#define VIDEO_TO_EVE    5

#define EVE_MAILBOX_MESSAGE(M)      (InterruptHost_mailboxEveBaseAddr + 0x40 + (0x4 * M))
#define EVE_MAILBOX_STATUS(M)       (InterruptHost_mailboxEveBaseAddr + 0xC0 + (0x4 * M))

#define EVE_MAILBOX_IRQSTATUS_CLR_HOST   (InterruptHost_mailboxEveBaseAddr + 0x114)
#define EVE_MAILBOX_IRQENABLE_SET_HOST   (InterruptHost_mailboxEveBaseAddr + 0x118)
#define EVE_MAILBOX_IRQENABLE_CLR_HOST   (InterruptHost_mailboxEveBaseAddr + 0x11C)
#define EVE_MAILBOX_EOI_REG              (InterruptHost_mailboxEveBaseAddr + 0x140)

#define EVE_MAILBOX_HOSTINT     107

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== InterruptHost_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptHost_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    if (remoteProcId == InterruptHost_dspProcId) {
        REG32(MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(DSP_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_videoProcId) {
        REG32(MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(VIDEO_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_vpssProcId) {
        REG32(MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(VPSS_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_eveProcId) {
        REG32(EVE_MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(EVE_TO_HOST);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*
 *  ======== InterruptHost_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptHost_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    if (remoteProcId == InterruptHost_dspProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(DSP_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_videoProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(VIDEO_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_vpssProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(VPSS_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_eveProcId) {
        REG32(EVE_MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(EVE_TO_HOST);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*
 *  ======== InterruptHost_intRegister ========
 */
Void InterruptHost_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                              Fxn func, UArg arg)
{
    UInt        key;
    Int         index;
    Error_Block eb;
    InterruptHost_FxnTable *table;

    /* init error block */
    Error_init(&eb);

    if (remoteProcId == InterruptHost_dspProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptHost_videoProcId) {
        index = 1;
    }
    else if (remoteProcId == InterruptHost_vpssProcId) {
        index = 2;
    }
    else if (remoteProcId == InterruptHost_eveProcId) {
        index = 3;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
        return;   /* should never get here, but keep Coverity happy */
    }

    /* Disable global interrupts */
    key = Hwi_disable();

    table = &(InterruptHost_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptHost_intClear(remoteProcId, intInfo);

    if (remoteProcId == InterruptHost_eveProcId) {
        /* Register interrupt for eve mailbox */
        Hwi_create(EVE_MAILBOX_HOSTINT,
                   (Hwi_FuncPtr)InterruptHost_intEveShmStub,
                   NULL,
                   &eb);

        Hwi_enableInterrupt(EVE_MAILBOX_HOSTINT);
    }
    else {
        /* Make sure the interrupt only gets plugged once */
        InterruptHost_module->numPlugged++;

        if (InterruptHost_module->numPlugged == 1) {
            /* Register interrupt for system mailbox */
            Hwi_create(MAILBOX_HOSTINT,
                      (Hwi_FuncPtr)InterruptHost_intShmStub,
                      NULL,
                      &eb);

            Hwi_enableInterrupt(MAILBOX_HOSTINT);
        }
    }

    /* Enable the mailbox interrupt to the HOST core */
    InterruptHost_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== InterruptHost_intUnregister ========
 */
Void InterruptHost_intUnregister(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle  hwiHandle;
    Int         index;
    InterruptHost_FxnTable *table;

    if (remoteProcId == InterruptHost_dspProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptHost_videoProcId) {
        index = 1;
    }
    else if (remoteProcId == InterruptHost_vpssProcId) {
        index = 2;
    }
    else if (remoteProcId == InterruptHost_eveProcId) {
        index = 3;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
        return;   /* should never get here, but keep Coverity happy */
    }

    /* Disable the mailbox interrupt source */
    InterruptHost_intDisable(remoteProcId, intInfo);

    if (remoteProcId == InterruptHost_eveProcId) {
        /* Delete the Hwi for eve internal mailbox */
        hwiHandle = Hwi_getHandle(EVE_MAILBOX_HOSTINT);
        Hwi_delete(&hwiHandle);
    }
    else {
        /* decrement numPlugged */
        InterruptHost_module->numPlugged--;

        if (InterruptHost_module->numPlugged == 0) {
            /* Delete the Hwi */
            hwiHandle = Hwi_getHandle(MAILBOX_HOSTINT);
            Hwi_delete(&hwiHandle);
        }
    }

    table = &(InterruptHost_module->fxnTable[index]);
    table->func = NULL;
    table->arg  = 0;
}

/*
 *  ======== InterruptHost_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptHost_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
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
    if (remoteProcId == InterruptHost_dspProcId) { /* DSP */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(HOST_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(HOST_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
    else if (remoteProcId == InterruptHost_videoProcId) { /* VIDEO-M3 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(HOST_TO_VIDEO)) == 0) {
            REG32(MAILBOX_MESSAGE(HOST_TO_VIDEO)) = arg;
        }
        Hwi_restore(key);
    }
    else if (remoteProcId == InterruptHost_vpssProcId) { /* VPSS-M3 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(HOST_TO_VPSS)) == 0) {
            REG32(MAILBOX_MESSAGE(HOST_TO_VPSS)) = arg;
        }
        Hwi_restore(key);
    }
    else { /* EVE */
        key = Hwi_disable();
        if (REG32(EVE_MAILBOX_STATUS(HOST_TO_EVE)) == 0) {
            REG32(EVE_MAILBOX_MESSAGE(HOST_TO_EVE)) = arg;
        }
        Hwi_restore(key);
    }
}

/*
 *  ======== InterruptHost_intPost ========
 */
Void InterruptHost_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt key;

    if (srcProcId == InterruptHost_vpssProcId) { /* VPSS-M3 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(VPSS_TO_HOST)) == 0) {
            REG32(MAILBOX_MESSAGE(VPSS_TO_HOST)) = arg;
        }
        Hwi_restore(key);
    }
    else if (srcProcId == InterruptHost_videoProcId) { /* VIDEO-M3 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(VIDEO_TO_HOST)) == 0) {
            REG32(MAILBOX_MESSAGE(VIDEO_TO_HOST)) = arg;
        }
        Hwi_restore(key);
    }
    else if (srcProcId == InterruptHost_dspProcId) {  /* DSP */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_HOST)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_HOST)) = arg;
        }
        Hwi_restore(key);
    }
    else { /* EVE */
        key = Hwi_disable();
        if (REG32(EVE_MAILBOX_STATUS(EVE_TO_HOST)) == 0) {
            REG32(EVE_MAILBOX_MESSAGE(EVE_TO_HOST)) = arg;
        }
        Hwi_restore(key);
    }
}

/*
 *  ======== InterruptHost_intClear ========
 *  Clear interrupt
 */
UInt InterruptHost_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    if (remoteProcId == InterruptHost_dspProcId) { /* DSP */
        arg = REG32(MAILBOX_MESSAGE(DSP_TO_HOST));
        REG32(MAILBOX_IRQSTATUS_CLR_HOST) = MAILBOX_REG_VAL(DSP_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_videoProcId) { /* VIDEO-M3 */
        arg = REG32(MAILBOX_MESSAGE(VIDEO_TO_HOST));
        REG32(MAILBOX_IRQSTATUS_CLR_HOST) = MAILBOX_REG_VAL(VIDEO_TO_HOST);
    }
    else if (remoteProcId == InterruptHost_vpssProcId) { /* VPSS-M3 */
        arg = REG32(MAILBOX_MESSAGE(VPSS_TO_HOST));
        REG32(MAILBOX_IRQSTATUS_CLR_HOST) = MAILBOX_REG_VAL(VPSS_TO_HOST);
    }
    else { /* EVE */
        arg = REG32(EVE_MAILBOX_MESSAGE(EVE_TO_HOST));
        REG32(EVE_MAILBOX_IRQSTATUS_CLR_HOST) = MAILBOX_REG_VAL(EVE_TO_HOST);

        /* Write to EOI (End Of Interrupt) register */
        REG32(EVE_MAILBOX_EOI_REG) = 0x1;
    }

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*
 *  ======== InterruptHost_intShmStub ========
 */
Void InterruptHost_intShmStub(UArg arg)
{
    InterruptHost_FxnTable *table;

    /* Process messages from the DSP */
    if ((REG32(MAILBOX_IRQENABLE_SET_HOST) & MAILBOX_REG_VAL(DSP_TO_HOST))
        && REG32(MAILBOX_STATUS(DSP_TO_HOST)) != 0) {
        table = &(InterruptHost_module->fxnTable[0]);
        (table->func)(table->arg);
    }

    /* Process messages from VIDEO  */
    if ((REG32(MAILBOX_IRQENABLE_SET_HOST) & MAILBOX_REG_VAL(VIDEO_TO_HOST))
        && REG32(MAILBOX_STATUS(VIDEO_TO_HOST)) != 0) {
        table = &(InterruptHost_module->fxnTable[1]);
        (table->func)(table->arg);
    }

    /* Process messages from VPSS  */
    if ((REG32(MAILBOX_IRQENABLE_SET_HOST) & MAILBOX_REG_VAL(VPSS_TO_HOST))
        && REG32(MAILBOX_STATUS(VPSS_TO_HOST)) != 0) {
        table = &(InterruptHost_module->fxnTable[2]);
        (table->func)(table->arg);
    }
}

/*
 *  ======== InterruptHost_intEveShmStub ========
 */
Void InterruptHost_intEveShmStub(UArg arg)
{
    InterruptHost_FxnTable *table;

    /* Process messages from the EVE */
    if ((REG32(EVE_MAILBOX_IRQENABLE_SET_HOST) & MAILBOX_REG_VAL(EVE_TO_HOST))
        && REG32(EVE_MAILBOX_STATUS(EVE_TO_HOST)) != 0) {
        table = &(InterruptHost_module->fxnTable[3]);
        (table->func)(table->arg);
    }
}
