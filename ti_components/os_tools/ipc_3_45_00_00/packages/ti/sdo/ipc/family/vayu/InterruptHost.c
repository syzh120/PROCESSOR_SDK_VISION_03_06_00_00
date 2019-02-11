/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  Ducati/A8 based interupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/family/shared/vayu/IntXbar.h>
#include <ti/sysbios/family/arm/gic/Hwi.h>

#include <ti/sdo/ipc/family/vayu/NotifySetup.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/InterruptHost.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

#define PROCID(IDX)               (InterruptHost_procIdTable[(IDX)])
#define MBX_TABLE_IDX(SRC, DST)   ((PROCID(SRC) * InterruptHost_NUM_CORES) + \
                                    PROCID(DST))
#define SUBMBX_IDX(IDX)           (InterruptHost_mailboxTable[(IDX)] & 0xFF)
#define MBX_USER_IDX(IDX)         ((InterruptHost_mailboxTable[(IDX)] >> 8) \
                                    & 0xFF)
#define MBX_BASEADDR_IDX(IDX)     ((InterruptHost_mailboxTable[(IDX)] >> 16) \
                                    & 0xFFFF)

#define MAILBOX_REG_VAL(M)        (0x1 << (2 * M))

#define MAILBOX_MESSAGE(IDX)      (InterruptHost_mailboxBaseAddr[  \
                                    MBX_BASEADDR_IDX(IDX)] + 0x40 +   \
                                    (0x4 * SUBMBX_IDX(IDX)))
#define MAILBOX_STATUS(IDX)       (InterruptHost_mailboxBaseAddr[  \
                                    MBX_BASEADDR_IDX(IDX)] + 0xC0 +   \
                                    (0x4 * SUBMBX_IDX(IDX)))

#define MAILBOX_IRQSTATUS_CLR(IDX)   (InterruptHost_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + (0x10 * \
                                        MBX_USER_IDX(IDX)) + 0x104)
#define MAILBOX_IRQENABLE_SET(IDX)   (InterruptHost_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + (0x10 * \
                                        MBX_USER_IDX(IDX)) + 0x108)
#define MAILBOX_IRQENABLE_CLR(IDX)   (InterruptHost_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + (0x10 * \
                                        MBX_USER_IDX(IDX)) + 0x10C)
#define MAILBOX_EOI_REG(IDX)         (InterruptHost_mailboxBaseAddr[  \
                                        MBX_BASEADDR_IDX(IDX)] + 0x140)

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
    UInt16 index;
    UInt subMbxIdx;

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());

    /*  If the remote processor communicates via mailboxes, we should enable
     *  the Mailbox IRQ instead of enabling the Hwi because multiple mailboxes
     *  share the same Hwi
     */
    subMbxIdx = SUBMBX_IDX(index);
    REG32(MAILBOX_IRQENABLE_SET(index)) = MAILBOX_REG_VAL(subMbxIdx);
}

/*
 *  ======== InterruptHost_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptHost_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt16 index;
    UInt subMbxIdx;

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());

    /*  If the remote processor communicates via mailboxes, we should disable
     *  the Mailbox IRQ instead of disabling the Hwi because multiple mailboxes
     *  share the same Hwi
     */
    subMbxIdx = SUBMBX_IDX(index);
    REG32(MAILBOX_IRQENABLE_CLR(index)) = MAILBOX_REG_VAL(subMbxIdx);
}

/*
 *  ======== InterruptHost_intRegister ========
 */
Void InterruptHost_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
        Fxn func, UArg arg)
{
    UInt        key;
    Int         index;
    InterruptHost_FxnTable *table;

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_Ipc_A_internal);

    /* Assert that our MultiProc id is set correctly */
    Assert_isTrue((InterruptHost_hostProcId == MultiProc_self()),
            ti_sdo_ipc_Ipc_A_internal);

    /* index is the virtual id (invariant) */
    index = PROCID(remoteProcId);

    intInfo->localIntId = NotifySetup_interruptTable(index);

    /* Disable global interrupts */
    key = Hwi_disable();

    /* store callback function by virtual id */
    table = &(InterruptHost_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptHost_intClear(remoteProcId, intInfo);

    /* plug the cpu interrupt with notify setup dispatch isr */
    NotifySetup_plugHwi(remoteProcId, intInfo->localIntId,
            InterruptHost_intShmStub);

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
    Int index;
    InterruptHost_FxnTable *table;

    /* Disable the mailbox interrupt source */
    InterruptHost_intDisable(remoteProcId, intInfo);

    NotifySetup_unplugHwi(remoteProcId, intInfo->localIntId);

    /* index is the virtual id (invariant) */
    index = PROCID(remoteProcId);

    /* Clear the FxnTable entry for the remote processor */
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
    UInt16 index;

    index = MBX_TABLE_IDX(MultiProc_self(), remoteProcId);
    key = Hwi_disable();
    if (REG32(MAILBOX_STATUS(index)) == 0) {
        REG32(MAILBOX_MESSAGE(index)) = arg;
    }
    Hwi_restore(key);
}

/*
 *  ======== InterruptHost_intPost ========
 *  Simulate an interrupt from a remote processor
 */
Void InterruptHost_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                             UArg arg)
{
    UInt key;
    UInt16 index;

    index = MBX_TABLE_IDX(srcProcId, MultiProc_self());
    key = Hwi_disable();
    if (REG32(MAILBOX_STATUS(index)) == 0) {
        REG32(MAILBOX_MESSAGE(index)) = arg;
    }
    Hwi_restore(key);
}

/*
 *  ======== InterruptHost_intClear ========
 *  Clear interrupt
 */
UInt InterruptHost_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;
    UInt16 index;

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());
    arg = REG32(MAILBOX_MESSAGE(index));
    REG32(MAILBOX_IRQSTATUS_CLR(index)) = MAILBOX_REG_VAL(SUBMBX_IDX(index));

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*
 *  ======== InterruptHost_intShmMbxStub ========
 */
Void InterruptHost_intShmStub(UInt16 idx)
{
    UInt16 srcVirtId;
    InterruptHost_FxnTable *table;

    srcVirtId = idx / InterruptHost_NUM_CORES;
    table = &(InterruptHost_module->fxnTable[srcVirtId]);
    (table->func)(table->arg);
}
