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
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/tesla/Wugen.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_Ipc.h>

#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/InterruptDsp.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

#define MPUINT                 26
#define DSPINT                 55
#define M3INT_MBX              50

/* Assigned mailboxes */
#define DSP_TO_MPU             0
#define DSP_TO_M3              1
#define M3_TO_DSP              2
#define MPU_TO_DSP             3
#define MPU_TO_M3              4
#define M3_TO_MPU              5

#define MAILBOX_MESSAGE(M) \
    InterruptDsp_mailboxBaseAddr + 0x040 + (0x4 * M)
#define MAILBOX_STATUS(M) \
    InterruptDsp_mailboxBaseAddr + 0x0C0 + (0x4 * M)

#define MAILBOX_IRQSTATUS_CLR_DSP   InterruptDsp_mailboxBaseAddr + 0x114
#define MAILBOX_IRQENABLE_SET_DSP   InterruptDsp_mailboxBaseAddr + 0x118
#define MAILBOX_IRQENABLE_CLR_DSP   InterruptDsp_mailboxBaseAddr + 0x11C

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
        REG32(MAILBOX_IRQENABLE_SET_DSP) = 0x40;
    }
    else if (remoteProcId == InterruptDsp_core0ProcId) {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = 0x10;
    }
    else {
        /* DSP cannot talk to CORE1 */
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
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = 0x40;
    }
    else if (remoteProcId == InterruptDsp_core0ProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = 0x10;
    }
    else {
        /* DSP cannot talk to CORE1 */
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
    Hwi_Params  hwiParams;

    /* Ensure that our ID is set correctly */
    Assert_isTrue(InterruptDsp_dspProcId == MultiProc_self(),
            ti_sdo_ipc_Ipc_A_internal);

    /* Ensure that remoteProcId is valid */
    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_invArgument);

    /* Ensure that proper intVectorId has been supplied */
    Assert_isTrue(intInfo->intVectorId <= 15, ti_sdo_ipc_Ipc_A_internal);

    if (remoteProcId == InterruptDsp_hostProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptDsp_core0ProcId) {
        index = 1;
    }
    else {
        /* DSP cannot talk to CORE1 */
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
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
        Hwi_Params_init(&hwiParams);
        hwiParams.eventId = DSPINT;
        Hwi_create(intInfo->intVectorId,
                   (Hwi_FuncPtr)InterruptDsp_intShmStub,
                   &hwiParams,
                   NULL);

        /* Enable the interrupt */
        Wugen_enableEvent(DSPINT);
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
    else if (remoteProcId == InterruptDsp_core0ProcId) {
        index = 1;
    }
    else {
        /* DSP cannot talk to CORE1 */
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
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
     */
    if (remoteProcId == InterruptDsp_hostProcId) {
        /* Using mailbox 0 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_MPU)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_MPU)) = arg;
        }
        Hwi_restore(key);
    }
    else if (remoteProcId == InterruptDsp_core0ProcId) {
        /* Using mailbox 1 */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_M3)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_M3)) = arg;
        }
        Hwi_restore(key);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }
}

/*!
 *  ======== InterruptDsp_intPost ========
 *  Send interrupt to the remote processor
 */
Void InterruptDsp_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt key;

    if (srcProcId == InterruptDsp_hostProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(MPU_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(MPU_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
    else if (srcProcId == InterruptDsp_core0ProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(M3_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(M3_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
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
        /* Mailbox 3 */
        arg = REG32(MAILBOX_MESSAGE(MPU_TO_DSP));
        REG32(MAILBOX_IRQSTATUS_CLR_DSP) = 0x40;
    }
    else if (remoteProcId == InterruptDsp_core0ProcId) {
        /* Mailbox 2 */
        arg = REG32(MAILBOX_MESSAGE(M3_TO_DSP));
        REG32(MAILBOX_IRQSTATUS_CLR_DSP) = 0x10;
    }
    else {
        Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
    }

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

    /* Process messages from  HOST */
    if ((REG32(MAILBOX_IRQENABLE_SET_DSP) & 0x40) &&
        REG32(MAILBOX_STATUS(MPU_TO_DSP)) != 0) {
        table = &(InterruptDsp_module->fxnTable[0]);
        (table->func)(table->arg);
    }

    /* Process messages from CORE0 */
    if ((REG32(MAILBOX_IRQENABLE_SET_DSP) & 0x10) &&
        REG32(MAILBOX_STATUS(M3_TO_DSP)) != 0) {
        table = &(InterruptDsp_module->fxnTable[1]);
        (table->func)(table->arg);
    }
}
