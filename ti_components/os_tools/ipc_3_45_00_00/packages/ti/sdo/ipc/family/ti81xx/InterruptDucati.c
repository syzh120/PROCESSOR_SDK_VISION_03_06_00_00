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
 *  Ducati/TI81xx based interupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/sysbios/family/arm/ducati/Core.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/InterruptDucati.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/*
 *  Ducati control register that maintains inter-core interrupt bits.
 *
 *  Using separate VIDEO and VPSS values to do 16-bit reads/writes
 *  because we do not want to overwrite the other cores value.
 */
#define INTERRUPT_VIDEO           (InterruptDucati_ducatiCtrlBaseAddr)
#define INTERRUPT_VPSS            (InterruptDucati_ducatiCtrlBaseAddr + 2)

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

#define MAILBOX_MESSAGE(M) (InterruptDucati_mailboxBaseAddr + 0x040 + (0x4 * M))
#define MAILBOX_STATUS(M)  (InterruptDucati_mailboxBaseAddr + 0x0C0 + (0x4 * M))

/* VIDEO registers */
#define MAILBOX_IRQSTATUS_CLR_VIDEO    (InterruptDucati_mailboxBaseAddr + 0x124)
#define MAILBOX_IRQENABLE_SET_VIDEO    (InterruptDucati_mailboxBaseAddr + 0x128)
#define MAILBOX_IRQENABLE_CLR_VIDEO    (InterruptDucati_mailboxBaseAddr + 0x12C)

/* VPSS registers */
#define MAILBOX_IRQSTATUS_CLR_VPSS     (InterruptDucati_mailboxBaseAddr + 0x134)
#define MAILBOX_IRQENABLE_SET_VPSS     (InterruptDucati_mailboxBaseAddr + 0x138)
#define MAILBOX_IRQENABLE_CLR_VPSS     (InterruptDucati_mailboxBaseAddr + 0x13C)

#define HOSTINT                77
#define M3VIDEOINT             53
#define M3DSSINT               54
#define DSPINT                 56
#define M3INT                  19

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
    if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VIDEO) = MAILBOX_REG_VAL(HOST_TO_VIDEO);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VIDEO) = MAILBOX_REG_VAL(DSP_TO_VIDEO);
        }
        else {
            Hwi_enableInterrupt(M3INT);
        }
    }
    else {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else {
            Hwi_enableInterrupt(M3INT);
        }
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
    if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VIDEO) = MAILBOX_REG_VAL(HOST_TO_VIDEO);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VIDEO) = MAILBOX_REG_VAL(DSP_TO_VIDEO);
        }
        else {
            Hwi_disableInterrupt(M3INT);
        }
    }
    else {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else {
            Hwi_disableInterrupt(M3INT);
        }
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

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_internal);

    /* Assert that our MultiProc id is set correctly */
    Assert_isTrue((InterruptDucati_videoProcId == MultiProc_self()) ||
                  (InterruptDucati_vpssProcId == MultiProc_self()),
                  ti_sdo_ipc_Ipc_A_internal);

    /*
     *  VPSS-M3 & VIDEO-M3 each have a unique interrupt ID for receiving
     *  interrupts external to the Ducati subsystem.  (M3DSSINT & M3VIDEOINT).
     *  However, they have a separate interrupt ID for receving interrupt from
     *  each other(M3INT).
     *
     *  Store the interrupt id in the intInfo so it can be used during
     *  intUnregiseter.
     */
    if (remoteProcId == InterruptDucati_dspProcId) {
        index = 0;
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            intInfo->localIntId = M3VIDEOINT;
        }
        else {
            intInfo->localIntId = M3DSSINT;
        }
    }
    else if (remoteProcId == InterruptDucati_hostProcId) {
        index = 1;
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            intInfo->localIntId = M3VIDEOINT;
        }
        else {
            intInfo->localIntId = M3DSSINT;
        }
    }
    else {
        /* Going to the other M3 */
        index = 2;
        intInfo->localIntId = M3INT;
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
    if (remoteProcId == InterruptDucati_videoProcId ||
        remoteProcId == InterruptDucati_vpssProcId) {
        Hwi_create(intInfo->localIntId,
                   (Hwi_FuncPtr)InterruptDucati_intShmDucatiStub,
                   &hwiAttrs,
                   NULL);
    }
    else {
        InterruptDucati_module->numPlugged++;
        if (InterruptDucati_module->numPlugged == 1) {
            Hwi_create(intInfo->localIntId,
                       (Hwi_FuncPtr)InterruptDucati_intShmMbxStub,
                       &hwiAttrs,
                       NULL);

            /* Interrupt_intEnable won't enable the Hwi */
            Hwi_enableInterrupt(intInfo->localIntId);
        }
    }

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
    Int         index;
    InterruptDucati_FxnTable *table;
    Hwi_Handle  hwiHandle;

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

    /* Disable the interrupt itself */
    if (remoteProcId == InterruptDucati_videoProcId ||
        remoteProcId == InterruptDucati_vpssProcId) {
        hwiHandle = Hwi_getHandle(M3INT);
        Hwi_delete(&hwiHandle);
    }
    else {
        InterruptDucati_module->numPlugged--;
        if (InterruptDucati_module->numPlugged == 0) {
            hwiHandle = Hwi_getHandle(intInfo->localIntId);
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
Void InterruptDucati_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;

    if (remoteProcId == InterruptDucati_videoProcId ||
        remoteProcId == InterruptDucati_vpssProcId) {
        if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
            /* VPSS-M3 to VIDEO-M3 */
            REG16(INTERRUPT_VIDEO) |= 0x1;
        }
        else {
            /* VIDEO-M3 to VPSS-M3 */
            REG16(INTERRUPT_VPSS) |= 0x1;
        }
    }
    else if (remoteProcId == InterruptDucati_dspProcId) {
        if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
            /* VPSS-M3 to DSP */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(VPSS_TO_DSP)) == 0) {
                REG32(MAILBOX_MESSAGE(VPSS_TO_DSP)) = arg;
            }
            Hwi_restore(key);
        }
        else {
            /* VIDEO-M3 to DSP */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(VIDEO_TO_DSP)) == 0) {
                REG32(MAILBOX_MESSAGE(VIDEO_TO_DSP)) = arg;
            }
            Hwi_restore(key);
        }
    }
    else { /* HOSTINT */
        if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
            /* VPSS-M3 to HOST */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(VPSS_TO_HOST)) == 0) {
                REG32(MAILBOX_MESSAGE(VPSS_TO_HOST)) = arg;
            }
            Hwi_restore(key);
        }
        else {
            /* VIDEO-M3 to HOST */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(VIDEO_TO_HOST)) == 0) {
                REG32(MAILBOX_MESSAGE(VIDEO_TO_HOST)) = arg;
            }
            Hwi_restore(key);
        }
    }
}


/*!
 *  ======== InterruptDucati_intPost ========
 *  Simulate an interrupt from a remote processor
 */
Void InterruptDucati_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;

    if (srcProcId == InterruptDucati_videoProcId ||
        srcProcId == InterruptDucati_vpssProcId) {
        if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
            /* VIDEO-M3 to VPSS-M3 */
            REG16(INTERRUPT_VPSS) |= 0x1;
        }
        else {
            /* VPSS-M3 to VIDEO-M3 */
            REG16(INTERRUPT_VIDEO) |= 0x1;
        }
    }
    else if (srcProcId == InterruptDucati_dspProcId) {
        if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
            /* DSP to VPSS-M3 */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(DSP_TO_VPSS)) == 0) {
                REG32(MAILBOX_MESSAGE(DSP_TO_VPSS)) = arg;
            }
            Hwi_restore(key);
        }
        else {
            /* DSP to VIDEO-M3 */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(DSP_TO_VIDEO)) == 0) {
                REG32(MAILBOX_MESSAGE(DSP_TO_VIDEO)) = arg;
            }
            Hwi_restore(key);
        }
    }
    else { /* HOSTINT */
        if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
            /* HOST to VPSS-M3 */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(HOST_TO_VPSS)) == 0) {
                REG32(MAILBOX_MESSAGE(HOST_TO_VPSS)) = arg;
            }
            Hwi_restore(key);
        }
        else {
            /* HOST to VIDEO-M3 */
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(HOST_TO_VIDEO)) == 0) {
                REG32(MAILBOX_MESSAGE(HOST_TO_VIDEO)) = arg;
            }
            Hwi_restore(key);
        }
    }
}


/*!
 *  ======== InterruptDucati_intClear ========
 *  Clear interrupt
 */
UInt InterruptDucati_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    if (remoteProcId == InterruptDucati_videoProcId ||
        remoteProcId == InterruptDucati_vpssProcId) {
        arg = REG32(InterruptDucati_ducatiCtrlBaseAddr);

        /* Look at BIOS's ducati Core id */
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            if ((REG16(INTERRUPT_VIDEO) & 0x1) == 0x1) {
                /* VPSS-M3 to VIDEO-M3 */
                REG16(INTERRUPT_VIDEO) &= ~(0x1);
            }
        }
        else {
            if ((REG16(INTERRUPT_VPSS) & 0x1) == 0x1) {
                /* VIDEO-M3 to VPSS-M3 */
                REG16(INTERRUPT_VPSS) &= ~(0x1);
            }
        }
    }
    else if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
        if (remoteProcId == InterruptDucati_hostProcId) {
            /* HOST to VIDEO-M3 */
            arg = REG32(MAILBOX_MESSAGE(HOST_TO_VIDEO));
            REG32(MAILBOX_IRQSTATUS_CLR_VIDEO) = MAILBOX_REG_VAL(HOST_TO_VIDEO);
        }
        else {
            /* DSP to VIDEO-M3 */
            arg = REG32(MAILBOX_MESSAGE(DSP_TO_VIDEO));
            REG32(MAILBOX_IRQSTATUS_CLR_VIDEO) = MAILBOX_REG_VAL(DSP_TO_VIDEO);
        }
    }
    else { /* M3DSSINT */
        if (remoteProcId == InterruptDucati_hostProcId) {
            /* HOST to VPSS-M3 */
            arg = REG32(MAILBOX_MESSAGE(HOST_TO_VPSS));
            REG32(MAILBOX_IRQSTATUS_CLR_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else {
            /* DSP to VPSS-M3 */
            arg = REG32(MAILBOX_MESSAGE(DSP_TO_VPSS));
            REG32(MAILBOX_IRQSTATUS_CLR_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
    }

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*!
 *  ======== InterruptDucati_intShmDucatiStub ========
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

    if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
        if ((REG32(MAILBOX_IRQENABLE_SET_VIDEO) &
                MAILBOX_REG_VAL(DSP_TO_VIDEO)) &&
            REG32(MAILBOX_STATUS(DSP_TO_VIDEO)) != 0) { /* DSP to VIDEO-M3 */
            table = &(InterruptDucati_module->fxnTable[0]);
            (table->func)(table->arg);
        }
        if ((REG32(MAILBOX_IRQENABLE_SET_VIDEO) &
                MAILBOX_REG_VAL(HOST_TO_VIDEO)) &&
            REG32(MAILBOX_STATUS(HOST_TO_VIDEO)) != 0) { /* HOST to VIDEO-M3 */
            table = &(InterruptDucati_module->fxnTable[1]);
            (table->func)(table->arg);
        }
    }
    else {
        if ((REG32(MAILBOX_IRQENABLE_SET_VPSS) &
                MAILBOX_REG_VAL(DSP_TO_VPSS)) &&
             REG32(MAILBOX_STATUS(DSP_TO_VPSS)) != 0) { /* DSP to VPSS-M3 */
            table = &(InterruptDucati_module->fxnTable[0]);
            (table->func)(table->arg);
        }
        if ((REG32(MAILBOX_IRQENABLE_SET_VPSS) &
                MAILBOX_REG_VAL(HOST_TO_VPSS)) &&
            REG32(MAILBOX_STATUS(HOST_TO_VPSS)) != 0) { /* HOST to VPSS-M3 */
            table = &(InterruptDucati_module->fxnTable[1]);
            (table->func)(table->arg);
        }
    }
}
