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
 *  ======== InterruptDucati.c ========
 *  OMAP4430/Ducati Interrupt Manger
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/sysbios/family/arm/ducati/Core.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/InterruptDucati.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

#define HOSTINT                26
#define DSPINT                 55
#define M3INT_MBX              50
#define M3INT                  19

/* Assigned mailboxes */
#define DSP_TO_HOST            0
#define DSP_TO_M3              1
#define M3_TO_DSP              2
#define HOST_TO_DSP            3
#define HOST_TO_M3             4
#define M3_TO_HOST             5

#define MAILBOX_MESSAGE(M)   InterruptDucati_mailboxBaseAddr + 0x040 + (0x4 * M)
#define MAILBOX_STATUS(M)    InterruptDucati_mailboxBaseAddr + 0x0C0 + (0x4 * M)

#define MAILBOX_IRQSTATUS_CLR_M3    InterruptDucati_mailboxBaseAddr + 0x124
#define MAILBOX_IRQENABLE_SET_M3    InterruptDucati_mailboxBaseAddr + 0x128
#define MAILBOX_IRQENABLE_CLR_M3    InterruptDucati_mailboxBaseAddr + 0x12C

/*
 *  Ducati control register that maintains inter-core interrupt bits.
 *
 *  Using separate core0 and core1 values to do 16-bit reads/writes
 *  because we do not want to overwrite the other cores value.
 */
#define INTERRUPT_CORE_0       (InterruptDucati_ducatiCtrlBaseAddr)
#define INTERRUPT_CORE_1       (InterruptDucati_ducatiCtrlBaseAddr + 2)

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== InterruptDucati_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptDucati_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    /*
     *  If the remote processor communicates via mailboxes, we should enable
     *  the Mailbox IRQ instead of enabling the Hwi because multiple mailboxes
     *  share the same Hwi
     */
    if (Core_getId() == 0) {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_SET_M3) = 0x100;
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_SET_M3) = 0x4;
        }
        else {
            Hwi_enableInterrupt(M3INT);
        }
    }
    else {
        Hwi_enableInterrupt(M3INT);
    }
}

/*!
 *  ======== InterruptDucati_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptDucati_intDisable(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    /*
     *  If the remote processor communicates via mailboxes, we should disable
     *  the Mailbox IRQ instead of disabling the Hwi because multiple mailboxes
     *  share the same Hwi
     */
    if (Core_getId() == 0) {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_M3) = 0x100;
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_M3) = 0x4;
        }
        else {
            Hwi_disableInterrupt(M3INT);
        }
    }
    else {
        Hwi_disableInterrupt(M3INT);
    }
}

/*!
 *  ======== InterruptDucati_intRegister ========
 */
Void InterruptDucati_intRegister(UInt16 remoteProcId,
                                 IInterrupt_IntInfo *intInfo,
                                 Fxn func, UArg arg)
{
    Hwi_Params  hwiAttrs;
    UInt        key;
    Int         index;
    InterruptDucati_FxnTable *table;

    /* Ensure that remoteProcId is valid */
    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_internal);

    /* Ensure that our ID is set correctly */
    Assert_isTrue((InterruptDucati_core0ProcId == MultiProc_self()) ||
                  (InterruptDucati_core1ProcId == MultiProc_self()),
                  ti_sdo_ipc_Ipc_A_internal);

    /* Ensure that, if on CORE1, we're only talking to CORE0 */
    Assert_isTrue(Core_getId() == 0 ||
                  remoteProcId == InterruptDucati_core0ProcId,
                  ti_sdo_ipc_Ipc_A_internal);

    if (remoteProcId == InterruptDucati_dspProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptDucati_hostProcId) {
        index = 1;
    }
    else {
        /* Going to the other M3 */
        index = 2;
    }

    /* Disable global interrupts */
    key = Hwi_disable();

    table = &(InterruptDucati_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptDucati_intClear(remoteProcId, intInfo);

    Hwi_Params_init(&hwiAttrs);
    hwiAttrs.maskSetting = Hwi_MaskingOption_LOWER;

    /* Make sure the interrupt only gets plugged once */
    if (remoteProcId == InterruptDucati_core0ProcId ||
        remoteProcId == InterruptDucati_core1ProcId) {
        Hwi_create(M3INT,
                   (Hwi_FuncPtr) InterruptDucati_intShmDucatiStub,
                   &hwiAttrs,
                   NULL);
    }
    else {
        InterruptDucati_module->numPlugged++;
        if (InterruptDucati_module->numPlugged == 1) {
            Hwi_create(M3INT_MBX,
                       (Hwi_FuncPtr) InterruptDucati_intShmMbxStub,
                       &hwiAttrs,
                       NULL);


            /* Interrupt_intEnable won't enable the Hwi */
            Hwi_enableInterrupt(M3INT_MBX);
        }
    }

    /* Enable the mailbox interrupt to the M3 core */
    InterruptDucati_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);

}

/*!
 *  ======== InterruptDucati_intUnregister ========
 */
Void InterruptDucati_intUnregister(UInt16 remoteProcId,
                                   IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle hwiHandle;
    Int index;
    InterruptDucati_FxnTable *table;

    if (remoteProcId == InterruptDucati_dspProcId) {
        index = 0;
    }
    else if (remoteProcId == InterruptDucati_hostProcId) {
        index = 1;
    }
    else {
        /* Going to the other M3 */
        index = 2;
    }

    /* Disable the mailbox interrupt source */
    InterruptDucati_intDisable(remoteProcId, intInfo);

    /* Delete/disable the Hwi */
    if (remoteProcId == InterruptDucati_core0ProcId ||
        remoteProcId == InterruptDucati_core1ProcId) {
        hwiHandle = Hwi_getHandle(M3INT);
        Hwi_delete(&hwiHandle);
    }
    else {
        InterruptDucati_module->numPlugged--;
        if (InterruptDucati_module->numPlugged == 0) {
            hwiHandle = Hwi_getHandle(M3INT_MBX);
            Hwi_delete(&hwiHandle);
        }
    }

    /* Clear the FxnTable entry for the remote processor */
    table = &(InterruptDucati_module->fxnTable[index]);
    table->func = NULL;
    table->arg  = 0;
}

/*!
 *  ======== InterruptDucati_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptDucati_intSend(UInt16 remoteProcId,
                             IInterrupt_IntInfo *intInfo,
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
    if (remoteProcId == InterruptDucati_core0ProcId ||
        remoteProcId == InterruptDucati_core1ProcId) {
        if (Core_getId() == 1) {
            REG16(INTERRUPT_CORE_0) |= 0x1;
        }
        else {
            REG16(INTERRUPT_CORE_1) |= 0x1;
        }
    }
    else if (remoteProcId == InterruptDucati_dspProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(M3_TO_DSP)) == 0) {
            REG32(MAILBOX_MESSAGE(M3_TO_DSP)) = arg;
        }
        Hwi_restore(key);
    }
    else { /* HOSTINT */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(M3_TO_HOST)) == 0) {
            REG32(MAILBOX_MESSAGE(M3_TO_HOST)) = arg;
        }
        Hwi_restore(key);
    }
}

/*!
 *  ======== InterruptDucati_intPost ========
 *  Simulate interrupt from remote processor
 */
Void InterruptDucati_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;

    if (srcProcId == InterruptDucati_core0ProcId ||
        srcProcId == InterruptDucati_core1ProcId) {
        if (Core_getId() == 1) {
            REG16(INTERRUPT_CORE_1) |= 0x1;
        }
        else {
            REG16(INTERRUPT_CORE_0) |= 0x1;
        }
    }
    else if (srcProcId == InterruptDucati_dspProcId) {
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(DSP_TO_M3)) == 0) {
            REG32(MAILBOX_MESSAGE(DSP_TO_M3)) = arg;
        }
        Hwi_restore(key);
    }
    else { /* HOSTINT */
        key = Hwi_disable();
        if (REG32(MAILBOX_STATUS(HOST_TO_M3)) == 0) {
            REG32(MAILBOX_MESSAGE(HOST_TO_M3)) = arg;
        }
        Hwi_restore(key);
    }
}

/*!
 *  ======== InterruptDucati_intClear ========
 *  Clear interrupt
 */
UInt InterruptDucati_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    if (remoteProcId == InterruptDucati_core0ProcId ||
        remoteProcId == InterruptDucati_core1ProcId) {
        arg = REG32(InterruptDucati_ducatiCtrlBaseAddr);

        /* Look at BIOS's ducati Core id */
        if (Core_getId() == 0) {
            if ((REG16(INTERRUPT_CORE_0) & 0x1) == 0x1) {
                REG16(INTERRUPT_CORE_0) &= ~(0x1);
            }
        }
        else {
            if ((REG16(INTERRUPT_CORE_1) & 0x1) == 0x1) {
                REG16(INTERRUPT_CORE_1) &= ~(0x1);
            }
        }
    }
    else {
        if (remoteProcId == InterruptDucati_hostProcId) {
            arg = REG32(MAILBOX_MESSAGE(HOST_TO_M3));
            REG32(MAILBOX_IRQSTATUS_CLR_M3) = 0x100; /* Mbx 4 */
        }
        else {
            arg = REG32(MAILBOX_MESSAGE(DSP_TO_M3));
            REG32(MAILBOX_IRQSTATUS_CLR_M3) = 0x4; /* Mbx 1 */
        }
    }

    return (arg);
}

/*
 *************************************************************************
 *                      Internal functions
 *************************************************************************
 */

/*!
 *  ======== InterruptDucati_intShmStub ========
 */
Void InterruptDucati_intShmDucatiStub(UArg arg)
{
    InterruptDucati_FxnTable *table;

    table = &(InterruptDucati_module->fxnTable[2]);
    (table->func)(table->arg);
}

/*!
 *  ======== InterruptDucati_intShmMbxStub ========
 */
Void InterruptDucati_intShmMbxStub(UArg arg)
{
    InterruptDucati_FxnTable *table;

    /* Process messages from the DSP  */
    if ((REG32(MAILBOX_IRQENABLE_SET_M3) & 0x4) &&
        REG32(MAILBOX_STATUS(DSP_TO_M3)) != 0) {
        table = &(InterruptDucati_module->fxnTable[0]);
        (table->func)(table->arg);
    }

    /* Process messages from the HOST  */
    if ((REG32(MAILBOX_IRQENABLE_SET_M3) & 0x100) &&
        REG32(MAILBOX_STATUS(HOST_TO_M3)) != 0) {
        table = &(InterruptDucati_module->fxnTable[1]);
        (table->func)(table->arg);
    }
}
