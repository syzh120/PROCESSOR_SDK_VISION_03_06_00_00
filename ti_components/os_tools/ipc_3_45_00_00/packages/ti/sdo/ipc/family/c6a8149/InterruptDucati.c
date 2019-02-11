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
#include <xdc/runtime/Error.h>

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

#define MAILBOX_M3VIDEOINT     53
#define MAILBOX_M3DSSINT       54

/* Assigned eve mailbox users */
#define EVE_TO_HOST     0
#define EVE_TO_DSP      1
#define EVE_TO_VIDEO    2
#define HOST_TO_EVE     3
#define DSP_TO_EVE      4
#define VIDEO_TO_EVE    5

#define EVE_MAILBOX_MESSAGE(M)      (InterruptDucati_mailboxEveBaseAddr + 0x40 + (0x4 * M))
#define EVE_MAILBOX_STATUS(M)       (InterruptDucati_mailboxEveBaseAddr + 0xC0 + (0x4 * M))

#define EVE_MAILBOX_IRQSTATUS_CLR_VIDEO   (InterruptDucati_mailboxEveBaseAddr + 0x134)
#define EVE_MAILBOX_IRQENABLE_SET_VIDEO   (InterruptDucati_mailboxEveBaseAddr + 0x138)
#define EVE_MAILBOX_IRQENABLE_CLR_VIDEO   (InterruptDucati_mailboxEveBaseAddr + 0x13C)
#define EVE_MAILBOX_EOI_REG               (InterruptDucati_mailboxEveBaseAddr + 0x140)

#define EVE_MAILBOX_M3VIDEOINT  38

#define M3INTERCOREINT          19

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
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
        else if (remoteProcId == InterruptDucati_eveProcId) {
            REG32(EVE_MAILBOX_IRQENABLE_SET_VIDEO) =
                MAILBOX_REG_VAL(EVE_TO_VIDEO);
        }
        else {
            Hwi_enableInterrupt(M3INTERCOREINT);
        }
    }
    else {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_eveProcId) {
            REG32(EVE_MAILBOX_IRQENABLE_SET_VIDEO) =
                MAILBOX_REG_VAL(EVE_TO_VIDEO);
        }
        else {
            Hwi_enableInterrupt(M3INTERCOREINT);
        }
    }
}

/*
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
        else if (remoteProcId == InterruptDucati_eveProcId) {
            REG32(EVE_MAILBOX_IRQENABLE_CLR_VIDEO) =
                MAILBOX_REG_VAL(EVE_TO_VIDEO);
        }
        else {
            Hwi_disableInterrupt(M3INTERCOREINT);
        }
    }
    else {
        if (remoteProcId == InterruptDucati_hostProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_eveProcId) {
            REG32(EVE_MAILBOX_IRQENABLE_CLR_VIDEO) =
                MAILBOX_REG_VAL(EVE_TO_VIDEO);
        }
        else {
            Hwi_disableInterrupt(M3INTERCOREINT);
        }
    }
}

/*
 *  ======== InterruptDucati_intRegister ========
 */
Void InterruptDucati_intRegister(UInt16 remoteProcId,
                                 IInterrupt_IntInfo *intInfo,
                                 Fxn func, UArg arg)
{
    Hwi_Params  hwiAttrs;
    UInt        key;
    Int         index;
    Error_Block eb;
    InterruptDucati_FxnTable *table;

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_internal);

    /* Assert that our MultiProc id is set correctly */
    Assert_isTrue((InterruptDucati_videoProcId == MultiProc_self()) ||
                  (InterruptDucati_vpssProcId == MultiProc_self()),
                  ti_sdo_ipc_Ipc_A_internal);

    /* init error block */
    Error_init(&eb);

    /*
     *  VPSS-M3 & VIDEO-M3 each have a unique interrupt ID for receiving
     *  interrupts external to the Ducati subsystem.
     *  (M3DSSINT & MAILBOX_M3VIDEOINT).
     *  However, they have a separate interrupt ID for receving interrupt from
     *  each other(M3INTERCOREINT).
     *
     *  Store the interrupt id in the intInfo so it can be used during
     *  intUnregiseter.
     */
    if (remoteProcId == InterruptDucati_dspProcId) {
        index = 0;
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            intInfo->localIntId = MAILBOX_M3VIDEOINT;
        }
        else {
            intInfo->localIntId = MAILBOX_M3DSSINT ;
        }
    }
    else if (remoteProcId == InterruptDucati_hostProcId) {
        index = 1;
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            intInfo->localIntId = MAILBOX_M3VIDEOINT;
        }
        else {
            intInfo->localIntId = MAILBOX_M3DSSINT ;
        }
    }
    else if (remoteProcId == InterruptDucati_eveProcId) {
        index = 3;
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            if (InterruptDucati_enableVpssToEve) {
                /* Core0 communication to EVE is not supported */
                Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
            }
            else {
                intInfo->localIntId = EVE_MAILBOX_M3VIDEOINT;
            }
        }
        else {
            if (InterruptDucati_enableVpssToEve) {
                /*
                 *  Core1 communication to EVE use same mbox
                 *  so only 1 can communicate to EVE.
                 */
                intInfo->localIntId = EVE_MAILBOX_M3VIDEOINT;
            }
            else {
                /* Core1 communication to EVE is not supported */
                Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
            }
        }
    }
    else {
        /* Going to the other M3 */
        index = 2;
        intInfo->localIntId = M3INTERCOREINT;
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
    if (index == 0 || index == 1) {
        InterruptDucati_module->numPlugged++;
        if (InterruptDucati_module->numPlugged == 1) {
            Hwi_create(intInfo->localIntId,
                      (Hwi_FuncPtr)InterruptDucati_intShmMbxStub,
                      &hwiAttrs,
                      &eb);

            /* Interrupt_intEnable won't enable the Hwi */
            Hwi_enableInterrupt(intInfo->localIntId);
        }
    }
    else if (index == 2) {
        Hwi_create(intInfo->localIntId,
                  (Hwi_FuncPtr)InterruptDucati_intShmDucatiStub,
                  &hwiAttrs,
                  &eb);
    }
    else {
        if ((BIOS_smpEnabled) || (Core_getId() == 0) ||
            (InterruptDucati_enableVpssToEve)) {
            Hwi_create(intInfo->localIntId,
                      (Hwi_FuncPtr)InterruptDucati_intShmEveMbxStub,
                      &hwiAttrs,
                      &eb);

            /* Interrupt_intEnable won't enable the Hwi */
            Hwi_enableInterrupt(intInfo->localIntId);
        }
    }

    InterruptDucati_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
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
    else if (remoteProcId == InterruptDucati_eveProcId) {
        index = 3;
        if (!(BIOS_smpEnabled) && (Core_getId() == 1) &&
            !(InterruptDucati_enableVpssToEve)) {
            /* Core1 communication to EVE is not supported */
            return;
        }
    }
    else {
        /* Going to the other M3 */
        index = 2;
    }

    /* Disable the mailbox interrupt source */
    InterruptDucati_intDisable(remoteProcId, intInfo);

    /* Disable the interrupt itself */
    if (index == 0 || index == 1) {
        /* case for DSP or HOST */
        InterruptDucati_module->numPlugged--;
        if (InterruptDucati_module->numPlugged == 0) {
            hwiHandle = Hwi_getHandle(intInfo->localIntId);
            Hwi_delete(&hwiHandle);
        }
    }
    else if (index == 2) {
        /* case for other M3 */
        hwiHandle = Hwi_getHandle(M3INTERCOREINT);
        Hwi_delete(&hwiHandle);
    }
    else {
        /* case for EVE */
        hwiHandle = Hwi_getHandle(intInfo->localIntId);
        Hwi_delete(&hwiHandle);
    }

    /* Clear the FxnTable entry for the remote processor */
    table = &(InterruptDucati_module->fxnTable[index]);
    table->func = NULL;
    table->arg  = 0;
}


/*
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
    else if (remoteProcId == InterruptDucati_hostProcId) {
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
    else {
        if ((BIOS_smpEnabled) || (Core_getId() == 0) ||
            (InterruptDucati_enableVpssToEve)) {
            /* VIDEO-M3/VPSS-M3 to EVE */
            key = Hwi_disable();
            if (REG32(EVE_MAILBOX_STATUS(VIDEO_TO_EVE)) == 0) {
                REG32(EVE_MAILBOX_MESSAGE(VIDEO_TO_EVE)) = arg;
            }
            Hwi_restore(key);
        }
    }
}


/*
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
    else if (srcProcId == InterruptDucati_hostProcId) {
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
    else {
        if ((BIOS_smpEnabled) || (Core_getId() == 0) ||
            (InterruptDucati_enableVpssToEve)) {
            /* EVE to VIDEO-M3/VPSS-M3 */
            key = Hwi_disable();
            if (REG32(EVE_MAILBOX_STATUS(EVE_TO_VIDEO)) == 0) {
                REG32(EVE_MAILBOX_MESSAGE(EVE_TO_VIDEO)) = arg;
            }
            Hwi_restore(key);
        }
    }
}


/*
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
        else if (remoteProcId == InterruptDucati_dspProcId) {
            /* DSP to VIDEO-M3 */
            arg = REG32(MAILBOX_MESSAGE(DSP_TO_VIDEO));
            REG32(MAILBOX_IRQSTATUS_CLR_VIDEO) = MAILBOX_REG_VAL(DSP_TO_VIDEO);
        }
        else {
            if (InterruptDucati_enableVpssToEve) {
                /* EVE cannot send an interrupt to VIDEO-M3 in this case */
                Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
                arg = 0;    /* keep Coverity happy */
            }
            else {
                /* EVE to VIDEO-M3 */
                arg = REG32(EVE_MAILBOX_MESSAGE(EVE_TO_VIDEO));
                REG32(EVE_MAILBOX_IRQSTATUS_CLR_VIDEO) = MAILBOX_REG_VAL(EVE_TO_VIDEO);
            }
        }
    }
    else { /* M3DSSINT */
        if (remoteProcId == InterruptDucati_hostProcId) {
            /* HOST to VPSS-M3 */
            arg = REG32(MAILBOX_MESSAGE(HOST_TO_VPSS));
            REG32(MAILBOX_IRQSTATUS_CLR_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == InterruptDucati_dspProcId) {
            /* DSP to VPSS-M3 */
            arg = REG32(MAILBOX_MESSAGE(DSP_TO_VPSS));
            REG32(MAILBOX_IRQSTATUS_CLR_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else {
            if (InterruptDucati_enableVpssToEve) {
                /* EVE to VPSS-M3 */
                arg = REG32(EVE_MAILBOX_MESSAGE(EVE_TO_VIDEO));
                REG32(EVE_MAILBOX_IRQSTATUS_CLR_VIDEO) = MAILBOX_REG_VAL(EVE_TO_VIDEO);
            }
            else {
                /* EVE cannot send an interrupt to VPSS-M3 */
                Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
                arg = 0;    /* keep Coverity happy */
            }
        }
    }

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*
 *  ======== InterruptDucati_intShmDucatiStub ========
 */
Void InterruptDucati_intShmDucatiStub(UArg arg)
{
    InterruptDucati_FxnTable *table;

    table = &(InterruptDucati_module->fxnTable[2]);
    (table->func)(table->arg);
}

/*
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

/*
 *  ======== InterruptDucati_intShmEveMbxStub ========
 */
Void InterruptDucati_intShmEveMbxStub(UArg arg)
{
    InterruptDucati_FxnTable *table;

    if ((BIOS_smpEnabled) || (Core_getId() == 0) ||
        (InterruptDucati_enableVpssToEve)) {
        if ((REG32(EVE_MAILBOX_IRQENABLE_SET_VIDEO) &
            MAILBOX_REG_VAL(EVE_TO_VIDEO)) &&
            REG32(EVE_MAILBOX_STATUS(EVE_TO_VIDEO)) != 0) {
             /* EVE to VIDEO-M3/VPSS-M3 */
            table = &(InterruptDucati_module->fxnTable[3]);
            (table->func)(table->arg);
        }
    }
}
