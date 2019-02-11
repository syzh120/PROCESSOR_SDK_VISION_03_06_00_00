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
 *  ======== InterruptDsp.c ========
 *  Mailbox based interrupt manager
 */
#include <xdc/std.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_Ipc.h>

#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/InterruptDsp.xdc.h"

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

#define MAILBOX_REG_VAL(M)   (0x1 << (2 * M))

#define MAILBOX_MESSAGE(M)   (InterruptDsp_mailboxBaseAddr + 0x40 + (0x4 * M))
#define MAILBOX_STATUS(M)    (InterruptDsp_mailboxBaseAddr + 0xC0 + (0x4 * M))

#define MAILBOX_IRQSTATUS_CLR_DSP   (InterruptDsp_mailboxBaseAddr + 0x114)
#define MAILBOX_IRQENABLE_SET_DSP   (InterruptDsp_mailboxBaseAddr + 0x118)
#define MAILBOX_IRQENABLE_CLR_DSP   (InterruptDsp_mailboxBaseAddr + 0x11C)
#define MAILBOX_EOI_REG             (InterruptDsp_mailboxBaseAddr + 0x140)

#define HOSTINT                77
#define M3VIDEOINT             53
#define M3DSSINT               54
#define DSPINT                 56

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
    if (remoteProcId == InterruptDsp_hostProcId) {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = MAILBOX_REG_VAL(HOST_TO_DSP);
    }
    else if (remoteProcId == InterruptDsp_videoProcId) {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = MAILBOX_REG_VAL(VIDEO_TO_DSP);
    }
    else if (remoteProcId == InterruptDsp_vpssProcId) {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = MAILBOX_REG_VAL(VPSS_TO_DSP);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*!
 *  ======== InterruptDsp_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptDsp_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    if (remoteProcId == InterruptDsp_hostProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = MAILBOX_REG_VAL(HOST_TO_DSP);
    }
    else if (remoteProcId == InterruptDsp_videoProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = MAILBOX_REG_VAL(VIDEO_TO_DSP);
    }
    else if (remoteProcId == InterruptDsp_vpssProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = MAILBOX_REG_VAL(VPSS_TO_DSP);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*!
 *  ======== InterruptDsp_intRegister ========
 */
Void InterruptDsp_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                              Fxn func, UArg arg)
{
    UInt        key;
    Int         index;
    InterruptDsp_FxnTable *table;

    Assert_isTrue(intInfo->intVectorId <= 15, ti_sdo_ipc_Ipc_A_internal);

    if (remoteProcId == InterruptDsp_hostProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptDsp_videoProcId) {
        index = 1;
    }
    else if (remoteProcId == InterruptDsp_vpssProcId) {
        index = 2;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
        return;    /* keep Coverity happy */
    }

    /* Disable global interrupts */
    key = Hwi_disable();

    table = &(InterruptDsp_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptDsp_intClear(remoteProcId, intInfo);

    /* Make sure the interrupt only gets plugged once */
    InterruptDsp_module->numPlugged++;
    if (InterruptDsp_module->numPlugged == 1) {
        /* Map the interrupt number to HWI vector */
        Hwi_eventMap(intInfo->intVectorId, DSPINT);

        Hwi_create(intInfo->intVectorId,
                   (Hwi_FuncPtr)InterruptDsp_intShmStub,
                   NULL,
                   NULL);
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
    Int         index;
    InterruptDsp_FxnTable *table;

    if (remoteProcId == InterruptDsp_hostProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptDsp_videoProcId) {
        index = 1;
    }
    else if (remoteProcId == InterruptDsp_vpssProcId) {
        index = 2;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
        return;    /* keep Coverity happy */
    }

    /* Disable the mailbox interrupt source */
    InterruptDsp_intDisable(remoteProcId, intInfo);

    InterruptDsp_module->numPlugged--;
    if (InterruptDsp_module->numPlugged == 0) {
        /* Delete the Hwi */
        hwiHandle = Hwi_getHandle(intInfo->intVectorId);
        Hwi_delete(&hwiHandle);
    }

    table = &(InterruptDsp_module->fxnTable[index]);
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
    if (remoteProcId == InterruptDsp_hostProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_HOST)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_HOST)) = arg;
        }
        Hwi_restore(key);
    }
    else if (remoteProcId == InterruptDsp_videoProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_VIDEO)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_VIDEO)) = arg;
        }
        Hwi_restore(key);
    }
    else { /* VPSS-M3 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_VPSS)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_VPSS)) = arg;
        }
        Hwi_restore(key);
    }
}

/*!
 *  ======== InterruptDsp_intPost ========
 */
Void InterruptDsp_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt key;

    if (srcProcId == InterruptDsp_vpssProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(VPSS_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(VPSS_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
    else if (srcProcId == InterruptDsp_videoProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(VIDEO_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(VIDEO_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
    else {  /* hostProcId */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(HOST_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(HOST_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
}

/*!
 *  ======== InterruptDsp_intClear ========
 *  Clear interrupt
 */
UInt InterruptDsp_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    if (remoteProcId == InterruptDsp_hostProcId) {
        arg = REG32(MAILBOX_MESSAGE(HOST_TO_DSP));
        REG32(MAILBOX_IRQSTATUS_CLR_DSP) = MAILBOX_REG_VAL(HOST_TO_DSP);
    }
    else if (remoteProcId == InterruptDsp_videoProcId) {
        arg = REG32(MAILBOX_MESSAGE(VIDEO_TO_DSP));
        REG32(MAILBOX_IRQSTATUS_CLR_DSP) = MAILBOX_REG_VAL(VIDEO_TO_DSP);
    }
    else { /* VPSS-M3 */
        arg = REG32(MAILBOX_MESSAGE(VPSS_TO_DSP));
        REG32(MAILBOX_IRQSTATUS_CLR_DSP) = MAILBOX_REG_VAL(VPSS_TO_DSP);
    }

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

    /* Process messages from the HOST */
    if ((REG32(MAILBOX_IRQENABLE_SET_DSP) & MAILBOX_REG_VAL(HOST_TO_DSP))
        && REG32(MAILBOX_STATUS(HOST_TO_DSP)) != 0) {
        table = &(InterruptDsp_module->fxnTable[0]);
        (table->func)(table->arg);
    }

    /* Process messages from VIDEO  */
    if ((REG32(MAILBOX_IRQENABLE_SET_DSP) & MAILBOX_REG_VAL(VIDEO_TO_DSP))
        && REG32(MAILBOX_STATUS(VIDEO_TO_DSP)) != 0) {
        table = &(InterruptDsp_module->fxnTable[1]);
        (table->func)(table->arg);
    }

    /* Process messages from VPSS  */
    if ((REG32(MAILBOX_IRQENABLE_SET_DSP) & MAILBOX_REG_VAL(VPSS_TO_DSP))
        && REG32(MAILBOX_STATUS(VPSS_TO_DSP)) != 0) {
        table = &(InterruptDsp_module->fxnTable[2]);
        (table->func)(table->arg);
    }
}
