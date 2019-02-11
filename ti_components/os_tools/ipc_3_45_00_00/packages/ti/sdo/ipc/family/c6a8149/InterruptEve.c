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
 *  ======== InterruptEve.c ========
 *  EVE mailbox based interrupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/family/arp32/Hwi.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/InterruptEve.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Assigned eve mailbox users */
#define EVE_TO_HOST     0
#define EVE_TO_DSP      1
#define EVE_TO_VIDEO    2
#define HOST_TO_EVE     3
#define DSP_TO_EVE      4
#define VIDEO_TO_EVE    5

#define MAILBOX_REG_VAL(M)   (0x1 << (2 * M))

#define MAILBOX_MESSAGE(M) (InterruptEve_mailboxEveBaseAddr + 0x040 + (0x4 * M))
#define MAILBOX_STATUS(M)  (InterruptEve_mailboxEveBaseAddr + 0x0C0 + (0x4 * M))

#define MAILBOX_IRQSTATUS_CLR_EVE  (InterruptEve_mailboxEveBaseAddr + 0x104)
#define MAILBOX_IRQENABLE_SET_EVE  (InterruptEve_mailboxEveBaseAddr + 0x108)
#define MAILBOX_IRQENABLE_CLR_EVE  (InterruptEve_mailboxEveBaseAddr + 0x10C)
#define MAILBOX_EOI_REG            (InterruptEve_mailboxEveBaseAddr + 0x140)

#define MAILBOX_EVEINT      29

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== InterruptEve_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptEve_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    if (remoteProcId == InterruptEve_hostProcId) {
        REG32(MAILBOX_IRQENABLE_SET_EVE) = MAILBOX_REG_VAL(HOST_TO_EVE);
    }
    else if ((remoteProcId == InterruptEve_videoProcId) ||
        (remoteProcId == InterruptEve_vpssProcId)) {
        REG32(MAILBOX_IRQENABLE_SET_EVE) = MAILBOX_REG_VAL(VIDEO_TO_EVE);
    }
    else if (remoteProcId == InterruptEve_dspProcId) {
        REG32(MAILBOX_IRQENABLE_SET_EVE) = MAILBOX_REG_VAL(DSP_TO_EVE);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*
 *  ======== InterruptEve_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptEve_intDisable(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    if (remoteProcId == InterruptEve_hostProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_EVE) = MAILBOX_REG_VAL(HOST_TO_EVE);
    }
    else if ((remoteProcId == InterruptEve_videoProcId) ||
        (remoteProcId == InterruptEve_vpssProcId)) {
        REG32(MAILBOX_IRQENABLE_CLR_EVE) = MAILBOX_REG_VAL(VIDEO_TO_EVE);
    }
    else if (remoteProcId == InterruptEve_dspProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_EVE) = MAILBOX_REG_VAL(DSP_TO_EVE);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*
 *  ======== InterruptEve_intRegister ========
 */
Void InterruptEve_intRegister(UInt16 remoteProcId,
                              IInterrupt_IntInfo *intInfo,
                              Fxn func, UArg arg)
{
    UInt        key;
    Int         index;
    Hwi_Params  hwiAttrs;
    Error_Block eb;
    InterruptEve_FxnTable *table;

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_internal);

    /* Assert that our MultiProc id is set correctly */
    Assert_isTrue((InterruptEve_eveProcId == MultiProc_self()),
                   ti_sdo_ipc_Ipc_A_internal);

    /* init error block */
    Error_init(&eb);

    if (remoteProcId == InterruptEve_hostProcId) {
        index = 0;
    }
    else if ((remoteProcId == InterruptEve_videoProcId) ||
        (remoteProcId == InterruptEve_vpssProcId)) {
        index = 1;
    }
    else if (remoteProcId == InterruptEve_dspProcId) {
        index = 2;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }

    /* Disable global interrupts */
    key = Hwi_disable();

    table = &(InterruptEve_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptEve_intClear(remoteProcId, intInfo);

    /* Make sure the interrupt only gets plugged once */
    InterruptEve_module->numPlugged++;
    if (InterruptEve_module->numPlugged == 1) {
        /* Register interrupt to remote processor */
        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.arg = arg;
        hwiAttrs.vectorNum = intInfo->intVectorId;

        Hwi_create(MAILBOX_EVEINT,
                  (Hwi_FuncPtr)InterruptEve_intShmStub,
                   &hwiAttrs,
                   &eb);

        Hwi_enableInterrupt(MAILBOX_EVEINT);
    }

    /* enable the mailbox and Hwi */
    InterruptEve_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== InterruptEve_intUnregister ========
 */
Void InterruptEve_intUnregister(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle  hwiHandle;
    Int         index;
    InterruptEve_FxnTable *table;

    if (remoteProcId == InterruptEve_hostProcId) {
        index = 0;
    }
    else if ((remoteProcId == InterruptEve_videoProcId) ||
        (remoteProcId == InterruptEve_vpssProcId)) {
        index = 1;
    }
    else if (remoteProcId == InterruptEve_dspProcId) {
        index = 2;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }

    /* Disable the mailbox interrupt source */
    InterruptEve_intDisable(remoteProcId, intInfo);

    InterruptEve_module->numPlugged--;
    if (InterruptEve_module->numPlugged == 0) {
        /* Delete the Hwi */
        hwiHandle = Hwi_getHandle(intInfo->intVectorId);
        Hwi_delete(&hwiHandle);
    }

    /* Clear the FxnTable entry for the remote processor */
    table = &(InterruptEve_module->fxnTable[index]);
    table->func = NULL;
    table->arg  = 0;
}


/*
 *  ======== InterruptEve_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptEve_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt key;

    if (remoteProcId == InterruptEve_hostProcId) {
        /* disable interrupts */
        key = Hwi_disable();

        if (REG32(MAILBOX_STATUS(EVE_TO_HOST)) == 0) {
            /* write the mailbox message to host */
            REG32(MAILBOX_MESSAGE(EVE_TO_HOST)) = arg;
        }

        /* restore interrupts */
        Hwi_restore(key);
    }
    else if ((remoteProcId == InterruptEve_videoProcId) ||
        (remoteProcId == InterruptEve_vpssProcId)) {
        /* disable interrupts */
        key = Hwi_disable();

        if (REG32(MAILBOX_STATUS(EVE_TO_VIDEO)) == 0) {
            /* write the mailbox message to video-m3 */
            REG32(MAILBOX_MESSAGE(EVE_TO_VIDEO)) = arg;
        }

        /* restore interrupts */
        Hwi_restore(key);
    }
    else {
        /* disable interrupts */
        key = Hwi_disable();

        if (REG32(MAILBOX_STATUS(EVE_TO_DSP)) == 0) {
            /* write the mailbox message to dsp */
            REG32(MAILBOX_MESSAGE(EVE_TO_DSP)) = arg;
        }

        /* restore interrupts */
        key = Hwi_disable();
    }
}

/*
 *  ======== InterruptEve_intPost ========
 *  Simulate an interrupt from a remote processor
 */
Void InterruptEve_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                            UArg arg)
{
    UInt key;

    if (srcProcId == InterruptEve_hostProcId) {
        /* disable interrupts */
        key = Hwi_disable();

        if (REG32(MAILBOX_STATUS(HOST_TO_EVE)) == 0) {
            /* write the mailbox message to arp32 */
            REG32(MAILBOX_MESSAGE(HOST_TO_EVE)) = arg;
        }

        /* restore interrupts */
        Hwi_restore(key);
    }
    else if ((srcProcId == InterruptEve_videoProcId) ||
        (srcProcId == InterruptEve_vpssProcId)) {
        /* disable interrupts */
        key = Hwi_disable();

        if (REG32(MAILBOX_STATUS(VIDEO_TO_EVE)) == 0) {
            /* write the mailbox message to arp32 */
            REG32(MAILBOX_MESSAGE(VIDEO_TO_EVE)) = arg;
        }

        /* restore interrupts */
        Hwi_restore(key);
    }
    else {
        /* disable interrupts */
        key = Hwi_disable();

        if (REG32(MAILBOX_STATUS(DSP_TO_EVE)) == 0) {
            /* write the mailbox message to arp32 */
            REG32(MAILBOX_MESSAGE(DSP_TO_EVE)) = arg;
        }

        /* restore interrupts */
        Hwi_restore(key);
    }
}


/*
 *  ======== InterruptEve_intClear ========
 *  Clear interrupt
 */
UInt InterruptEve_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    if (remoteProcId == InterruptEve_hostProcId) { /* HOST */
        arg = REG32(MAILBOX_MESSAGE(HOST_TO_EVE));
        REG32(MAILBOX_IRQSTATUS_CLR_EVE) = MAILBOX_REG_VAL(HOST_TO_EVE);
    }
    else if ((remoteProcId == InterruptEve_videoProcId) || /* VIDEO-M3 */
        (remoteProcId == InterruptEve_vpssProcId)) {
        arg = REG32(MAILBOX_MESSAGE(VIDEO_TO_EVE));
        REG32(MAILBOX_IRQSTATUS_CLR_EVE) = MAILBOX_REG_VAL(VIDEO_TO_EVE);
    }
    else { /* DSP */
        arg = REG32(MAILBOX_MESSAGE(DSP_TO_EVE));
        REG32(MAILBOX_IRQSTATUS_CLR_EVE) = MAILBOX_REG_VAL(DSP_TO_EVE);
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

/*
 *  ======== InterruptEve_intShmStub ========
 */
Void InterruptEve_intShmStub(UArg arg)
{
    InterruptEve_FxnTable *table;

    /* Process messages from the HOST */
    if ((REG32(MAILBOX_IRQENABLE_SET_EVE) & MAILBOX_REG_VAL(HOST_TO_EVE))
        && REG32(MAILBOX_STATUS(HOST_TO_EVE)) != 0) {
        table = &(InterruptEve_module->fxnTable[0]);
        (table->func)(table->arg);
    }

    /* Process messages from VIDEO OR VPSS */
    if ((REG32(MAILBOX_IRQENABLE_SET_EVE) & MAILBOX_REG_VAL(VIDEO_TO_EVE))
        && REG32(MAILBOX_STATUS(VIDEO_TO_EVE)) != 0) {
        table = &(InterruptEve_module->fxnTable[1]);
        (table->func)(table->arg);
    }

    /* Process messages from DSP  */
    if ((REG32(MAILBOX_IRQENABLE_SET_EVE) & MAILBOX_REG_VAL(DSP_TO_EVE))
        && REG32(MAILBOX_STATUS(DSP_TO_EVE)) != 0) {
        table = &(InterruptEve_module->fxnTable[2]);
        (table->func)(table->arg);
    }
}
