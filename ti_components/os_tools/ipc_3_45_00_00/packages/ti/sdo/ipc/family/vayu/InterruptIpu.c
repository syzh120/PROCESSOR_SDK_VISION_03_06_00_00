/*
 * Copyright (c) 2013-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== InterruptIpu.c ========
 *  Vayu IPU based interupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/sysbios/family/arm/ducati/Core.h>

#include <ti/sdo/ipc/family/vayu/NotifySetup.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/InterruptIpu.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

/*
 *  Ducati control register that maintains inter-core interrupt bits.
 *
 *  Using separate CORE0 and CORE1 values to do 16-bit reads/writes
 *  because we do not want to overwrite the other cores value.
 */
#define INTERRUPT_CORE0         (InterruptIpu_ducatiCtrlBaseAddr)
#define INTERRUPT_CORE1         (InterruptIpu_ducatiCtrlBaseAddr + 2)

#define PROCID(IDX)               (InterruptIpu_procIdTable[(IDX)])
#define MBX_TABLE_IDX(SRC, DST)   ((PROCID(SRC) * InterruptIpu_NUM_CORES) + \
                                    PROCID(DST))
#define SUBMBX_IDX(IDX)           (InterruptIpu_mailboxTable[(IDX)] & 0xFF)
#define MBX_USER_IDX(IDX)         ((InterruptIpu_mailboxTable[(IDX)] >> 8) \
                                    & 0xFF)
#define MBX_BASEADDR_IDX(IDX)    ((InterruptIpu_mailboxTable[(IDX)] >> 16) \
                                    & 0xFFFF)

#define MAILBOX_REG_VAL(M)        (0x1 << (2 * M))

#define MAILBOX_MESSAGE(IDX)      (InterruptIpu_mailboxBaseAddr[  \
                                    MBX_BASEADDR_IDX(IDX)] + 0x40 +   \
                                    (0x4 * SUBMBX_IDX(IDX)))
#define MAILBOX_STATUS(IDX)       (InterruptIpu_mailboxBaseAddr[  \
                                    MBX_BASEADDR_IDX(IDX)] + 0xC0 +   \
                                    (0x4 * SUBMBX_IDX(IDX)))

#define MAILBOX_IRQSTATUS_CLR(IDX)   (InterruptIpu_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + (0x10 * \
                                        MBX_USER_IDX(IDX)) + 0x104)
#define MAILBOX_IRQENABLE_SET(IDX)   (InterruptIpu_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + (0x10 * \
                                        MBX_USER_IDX(IDX)) + 0x108)
#define MAILBOX_IRQENABLE_CLR(IDX)   (InterruptIpu_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + (0x10 * \
                                        MBX_USER_IDX(IDX)) + 0x10C)
#define MAILBOX_EOI_REG(IDX)         (InterruptIpu_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + 0x140)

#define WUGENIPU        19

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== InterruptIpu_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptIpu_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt16 index;
    Bool useMailbox = TRUE;
    UInt subMbxIdx;

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());

    if (Core_ipuId == 1) {
        if ((remoteProcId == InterruptIpu_ipu1_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu1_1ProcId)) {
            Hwi_enableInterrupt(WUGENIPU);
            useMailbox = FALSE;
        }
    }
    else {
        if ((remoteProcId == InterruptIpu_ipu2_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu2_1ProcId)) {
            Hwi_enableInterrupt(WUGENIPU);
            useMailbox = FALSE;
        }
    }

    /*  If the remote processor communicates via mailboxes, we should enable
     *  the Mailbox IRQ instead of enabling the Hwi because multiple mailboxes
     *  share the same Hwi
     */
    if (useMailbox) {
        subMbxIdx = SUBMBX_IDX(index);
        REG32(MAILBOX_IRQENABLE_SET(index)) = MAILBOX_REG_VAL(subMbxIdx);
    }
}

/*
 *  ======== InterruptIpu_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptIpu_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt16 index;
    Bool useMailbox = TRUE;
    UInt subMbxIdx;

    if (Core_ipuId == 1) {
        if ((remoteProcId == InterruptIpu_ipu1_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu1_1ProcId)) {
            Hwi_disableInterrupt(WUGENIPU);
            useMailbox = FALSE;
        }
    }
    else {
        if ((remoteProcId == InterruptIpu_ipu2_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu2_1ProcId)) {
            Hwi_disableInterrupt(WUGENIPU);
            useMailbox = FALSE;
        }
    }

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());

    /*  If the remote processor communicates via mailboxes, we should disable
     *  the Mailbox IRQ instead of disabling the Hwi because multiple mailboxes
     *  share the same Hwi
     */
    if (useMailbox) {
        subMbxIdx = SUBMBX_IDX(index);
        REG32(MAILBOX_IRQENABLE_CLR(index)) = MAILBOX_REG_VAL(subMbxIdx);
    }
}

/*
 *  ======== InterruptIpu_intRegister ========
 */
Void InterruptIpu_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
        Fxn func, UArg arg)
{
    Hwi_Params  hwiAttrs;
    UInt        key;
    Int         index;
    InterruptIpu_FxnTable *table;

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    /* index is the virtual id (invariant) */
    index = PROCID(remoteProcId);

    intInfo->localIntId = NotifySetup_interruptTable(index);

    /* Disable global interrupts */
    key = Hwi_disable();

    /* store callback function by virtual id */
    table = &(InterruptIpu_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptIpu_intClear(remoteProcId, intInfo);

    Hwi_Params_init(&hwiAttrs);
    hwiAttrs.maskSetting = Hwi_MaskingOption_LOWER;

    if (Core_ipuId == 1) {
        if ((remoteProcId == InterruptIpu_ipu1_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu1_1ProcId)) {

            /* plug the cpu interrupt with local isr */
            Hwi_create(intInfo->localIntId,
                   (Hwi_FuncPtr)InterruptIpu_intShmDucatiStub,
                   &hwiAttrs, NULL);
        }
        else {
            /* plug the cpu interrupt with notify setup dispatch isr */
            NotifySetup_plugHwi(remoteProcId, intInfo->localIntId,
                    InterruptIpu_intShmMbxStub);
        }
    }
    else {
        if ((remoteProcId == InterruptIpu_ipu2_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu2_1ProcId)) {
            Hwi_create(intInfo->localIntId,
                   (Hwi_FuncPtr)InterruptIpu_intShmDucatiStub,
                   &hwiAttrs, NULL);
        }
        else {
            NotifySetup_plugHwi(remoteProcId, intInfo->localIntId,
                    InterruptIpu_intShmMbxStub);
        }
    }

    InterruptIpu_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== InterruptIpu_intUnregister ========
 */
Void InterruptIpu_intUnregister(UInt16 remoteProcId,
        IInterrupt_IntInfo *intInfo)
{
    Int index;
    Hwi_Handle hwiHandle;
    InterruptIpu_FxnTable *table;

    /* Disable the mailbox interrupt source */
    InterruptIpu_intDisable(remoteProcId, intInfo);

    if (Core_ipuId == 1) {
        if ((remoteProcId == InterruptIpu_ipu1_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu1_1ProcId)) {
            hwiHandle = Hwi_getHandle(WUGENIPU);
            Hwi_delete(&hwiHandle);
        }
        else {
            NotifySetup_unplugHwi(remoteProcId, intInfo->localIntId);
        }
    }
    else {
        if ((remoteProcId == InterruptIpu_ipu2_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu2_1ProcId)) {
            hwiHandle = Hwi_getHandle(WUGENIPU);
            Hwi_delete(&hwiHandle);
        }
        else {
            NotifySetup_unplugHwi(remoteProcId, intInfo->localIntId);
        }
    }

    /* index is the virtual id (invariant) */
    index = PROCID(remoteProcId);

    /* Clear the FxnTable entry for the remote processor */
    table = &(InterruptIpu_module->fxnTable[index]);
    table->func = NULL;
    table->arg  = 0;
}


/*
 *  ======== InterruptIpu_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptIpu_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
        UArg arg)
{
    UInt key;
    UInt16 index;

    if (Core_ipuId == 1) {
        if ((remoteProcId == InterruptIpu_ipu1_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu1_1ProcId)) {
            if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
                /* CORE1 to CORE0 */
                REG16(INTERRUPT_CORE0) |= 0x1;
            }
            else {
                /* CORE0 to CORE1 */
                REG16(INTERRUPT_CORE1) |= 0x1;
            }
        }
        else {
            index = MBX_TABLE_IDX(MultiProc_self(), remoteProcId);
            key = Hwi_disable();
            while (REG32(MAILBOX_STATUS(index)) != 0) {
                Hwi_restore(key);
                key = Hwi_disable();
            }
            REG32(MAILBOX_MESSAGE(index)) = arg;
            Hwi_restore(key);
        }
    }
    else {
        if ((remoteProcId == InterruptIpu_ipu2_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu2_1ProcId)) {
            if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
                /* CORE1 to CORE0 */
                REG16(INTERRUPT_CORE0) |= 0x1;
            }
            else {
                /* CORE0 to CORE1 */
                REG16(INTERRUPT_CORE1) |= 0x1;
            }
        }
        else {
            index = MBX_TABLE_IDX(MultiProc_self(), remoteProcId);
            key = Hwi_disable();
            while (REG32(MAILBOX_STATUS(index)) != 0) {
                Hwi_restore(key);
                key = Hwi_disable();
            }
            REG32(MAILBOX_MESSAGE(index)) = arg;
            Hwi_restore(key);
        }
    }
}


/*
 *  ======== InterruptIpu_intPost ========
 *  Simulate an interrupt from a remote processor
 */
Void InterruptIpu_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;
    UInt16 index;

    if (Core_ipuId == 1) {
        if ((srcProcId == InterruptIpu_ipu1_0ProcId) ||
            (srcProcId == InterruptIpu_ipu1_1ProcId)) {
            if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
                /* CORE0 to CORE1 */
                REG16(INTERRUPT_CORE1) |= 0x1;
            }
            else {
                /* CORE1 to CORE0 */
                REG16(INTERRUPT_CORE0) |= 0x1;
            }
        }
        else {
            index = MBX_TABLE_IDX(srcProcId, MultiProc_self());
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(index)) == 0) {
                REG32(MAILBOX_MESSAGE(index)) = arg;
            }
            Hwi_restore(key);
        }
    }
    else {
        if ((srcProcId == InterruptIpu_ipu2_0ProcId) ||
            (srcProcId == InterruptIpu_ipu2_1ProcId)) {
            if (!(BIOS_smpEnabled) && (Core_getId() == 1)) {
                /* CORE0 to CORE1 */
                REG16(INTERRUPT_CORE1) |= 0x1;
            }
            else {
                /* CORE1 to CORE0 */
                REG16(INTERRUPT_CORE0) |= 0x1;
            }
        }
        else {
            index = MBX_TABLE_IDX(srcProcId, MultiProc_self());
            key = Hwi_disable();
            if (REG32(MAILBOX_STATUS(index)) == 0) {
                REG32(MAILBOX_MESSAGE(index)) = arg;
            }
            Hwi_restore(key);
        }
    }
}

/*
 *  ======== InterruptIpu_intClear ========
 *  Clear interrupt
 */
UInt InterruptIpu_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;
    UInt16 index;

    if (Core_ipuId == 1) {
        if ((remoteProcId == InterruptIpu_ipu1_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu1_1ProcId)) {
            arg = REG32(InterruptIpu_ducatiCtrlBaseAddr);

            /* Look at BIOS's ducati Core id */
            if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
                if ((REG16(INTERRUPT_CORE0) & 0x1) == 0x1) {
                    /* CORE1 to CORE0 */
                    REG16(INTERRUPT_CORE0) &= ~(0x1);
                }
            }
            else {
                if ((REG16(INTERRUPT_CORE1) & 0x1) == 0x1) {
                    /* CORE0 to CORE1 */
                    REG16(INTERRUPT_CORE1) &= ~(0x1);
                }
            }
        }
        else {
            index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());
            arg = REG32(MAILBOX_MESSAGE(index));
            REG32(MAILBOX_IRQSTATUS_CLR(index)) =
                MAILBOX_REG_VAL(SUBMBX_IDX(index));
        }
    }
    else {
        if ((remoteProcId == InterruptIpu_ipu2_0ProcId) ||
            (remoteProcId == InterruptIpu_ipu2_1ProcId)) {
            arg = REG32(InterruptIpu_ducatiCtrlBaseAddr);

            /* Look at BIOS's ducati Core id */
            if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
                if ((REG16(INTERRUPT_CORE0) & 0x1) == 0x1) {
                    /* CORE1 to CORE0 */
                    REG16(INTERRUPT_CORE0) &= ~(0x1);
                }
            }
            else {
                if ((REG16(INTERRUPT_CORE1) & 0x1) == 0x1) {
                    /* CORE0 to CORE1 */
                    REG16(INTERRUPT_CORE1) &= ~(0x1);
                }
            }
        }
        else {
            index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());
            arg = REG32(MAILBOX_MESSAGE(index));
            REG32(MAILBOX_IRQSTATUS_CLR(index)) =
                MAILBOX_REG_VAL(SUBMBX_IDX(index));
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
 *  ======== InterruptIpu_intShmDucatiStub ========
 */
Void InterruptIpu_intShmDucatiStub(UArg arg)
{
    UInt16 index;
    InterruptIpu_FxnTable *table;

    if (Core_ipuId == 1) {
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            index = 9;
        }
        else {
            index = 6;
        }
    }
    else {
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            index = 10;
        }
        else {
            index = 7;
        }
    }

    table = &(InterruptIpu_module->fxnTable[index]);
    (table->func)(table->arg);
}


/*
 *  ======== InterruptIpu_intShmMbxStub ========
 */
Void InterruptIpu_intShmMbxStub(UInt16 idx)
{
    UInt16 srcVirtId;
    InterruptIpu_FxnTable *table;

    srcVirtId = idx / InterruptIpu_NUM_CORES;
    table = &(InterruptIpu_module->fxnTable[srcVirtId]);
    (table->func)(table->arg);
}
