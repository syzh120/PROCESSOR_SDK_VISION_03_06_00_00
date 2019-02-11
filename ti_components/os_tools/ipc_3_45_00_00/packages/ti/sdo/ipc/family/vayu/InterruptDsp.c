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
 *  ======== InterruptDsp.c ========
 *  Mailbox based interrupt manager
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/family/vayu/NotifySetup.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/InterruptDsp.xdc.h"

/* Register access method. */
#define REG16(A)   (*(volatile UInt16 *) (A))
#define REG32(A)   (*(volatile UInt32 *) (A))

#define PROCID(IDX)               (InterruptDsp_procIdTable[(IDX)])
#define MBX_TABLE_IDX(SRC, DST)   ((PROCID(SRC) * InterruptDsp_NUM_CORES) + \
                                    PROCID(DST))
#define SUBMBX_IDX(IDX)           (InterruptDsp_mailboxTable[(IDX)] & 0xFF)
#define MBX_USER_IDX(IDX)         ((InterruptDsp_mailboxTable[(IDX)] >> 8) & 0xFF)
#define MBX_BASEADDR_IDX(IDX)     ((InterruptDsp_mailboxTable[(IDX)] >> 16) & 0xFFFF)

#define MAILBOX_REG_VAL(M)        (0x1 << (2 * M))

#define MAILBOX_MESSAGE(IDX)      (InterruptDsp_mailboxBaseAddr[  \
                                    MBX_BASEADDR_IDX(IDX)] + 0x40 \
                                    + (0x4 * SUBMBX_IDX(IDX)))
#define MAILBOX_STATUS(IDX)       (InterruptDsp_mailboxBaseAddr[  \
                                    MBX_BASEADDR_IDX(IDX)] + 0xC0 \
                                    + (0x4 * SUBMBX_IDX(IDX)))

#define MAILBOX_IRQSTATUS_CLR_DSP(IDX)   (InterruptDsp_mailboxBaseAddr[ \
                                           MBX_BASEADDR_IDX(IDX)] +     \
                                           (0x10 * MBX_USER_IDX(IDX)) + 0x104)
#define MAILBOX_IRQENABLE_SET_DSP(IDX)   (InterruptDsp_mailboxBaseAddr[ \
                                           MBX_BASEADDR_IDX(IDX)] +     \
                                           (0x10 * MBX_USER_IDX(IDX)) + 0x108)
#define MAILBOX_IRQENABLE_CLR_DSP(IDX)   (InterruptDsp_mailboxBaseAddr[ \
                                           MBX_BASEADDR_IDX(IDX)] +     \
                                           (0x10 * MBX_USER_IDX(IDX)) + 0x10C)
#define MAILBOX_EOI_REG(IDX)             (InterruptDsp_mailboxBaseAddr[ \
                                           MBX_BASEADDR_IDX(IDX)] + 0x140)
#define EVENT_GROUP_SIZE                 32

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== InterruptDsp_intEnable ========
 *  Enable remote processor interrupt
 */
Void InterruptDsp_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt16 index;
    UInt subMbxIdx;

    Assert_isTrue(((remoteProcId < MultiProc_getNumProcsInCluster()) &&
            (remoteProcId != MultiProc_self())), ti_sdo_ipc_Ipc_A_internal);

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());
    subMbxIdx = SUBMBX_IDX(index);
    REG32(MAILBOX_IRQENABLE_SET_DSP(index)) = MAILBOX_REG_VAL(subMbxIdx);
}

/*
 *  ======== InterruptDsp_intDisable ========
 *  Disables remote processor interrupt
 */
Void InterruptDsp_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt16 index;
    UInt subMbxIdx;

    Assert_isTrue(((remoteProcId < MultiProc_getNumProcsInCluster()) &&
            (remoteProcId != MultiProc_self())), ti_sdo_ipc_Ipc_A_internal);

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());
    subMbxIdx = SUBMBX_IDX(index);
    REG32(MAILBOX_IRQENABLE_CLR_DSP(index)) = MAILBOX_REG_VAL(subMbxIdx);
}

/*
 *  ======== InterruptDsp_intRegister ========
 */
Void InterruptDsp_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
        Fxn func, UArg arg)
{
    UInt        key;
    Int         index;
    InterruptDsp_FxnTable *table;

    Assert_isTrue(((remoteProcId < MultiProc_getNumProcsInCluster()) &&
            (remoteProcId != MultiProc_self())), ti_sdo_ipc_Ipc_A_internal);

    /* index is the virtual id (invariant) */
    index = PROCID(remoteProcId);

    /* Disable global interrupts */
    key = Hwi_disable();

    /* store callback function by virtual id */
    table = &(InterruptDsp_module->fxnTable[index]);
    table->func = func;
    table->arg  = arg;

    InterruptDsp_intClear(remoteProcId, intInfo);

    /* plug the cpu interrupt with notify setup dispatch isr */
    NotifySetup_plugHwi(remoteProcId, intInfo->intVectorId,
            InterruptDsp_intShmStub);

    /* Enable the mailbox interrupt to the DSP */
    InterruptDsp_intEnable(remoteProcId, intInfo);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== InterruptDsp_intUnregister ========
 */
Void InterruptDsp_intUnregister(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    Int index;
    InterruptDsp_FxnTable *table;

    Assert_isTrue(((remoteProcId < MultiProc_getNumProcsInCluster()) &&
            (remoteProcId != MultiProc_self())), ti_sdo_ipc_Ipc_A_internal);

    index = PROCID(remoteProcId);

    /* disable the mailbox interrupt source */
    InterruptDsp_intDisable(remoteProcId, intInfo);

    /* unplug isr and unprogram the event dispatcher */
    NotifySetup_unplugHwi(remoteProcId, intInfo->intVectorId);

    table = &(InterruptDsp_module->fxnTable[index]);
    table->func = NULL;
    table->arg  = 0;
}

/*
 *  ======== InterruptDsp_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptDsp_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
        UArg arg)
{
    UInt key;
    UInt16 index;

    index = MBX_TABLE_IDX(MultiProc_self(), remoteProcId);

    /*  Before writing to a mailbox, check whether it already contains a
     *  message. If so, wait for the message to be read since we want one
     *  and only one message per interrupt. Disable interrupts between reading
     *  the MSGSTATUS_X register and writing to the mailbox to protect from
     *  another thread doing an intSend at the same time.
     */
    key = Hwi_disable();
    while (REG32(MAILBOX_STATUS(index)) != 0) {
        Hwi_restore(key);
        key = Hwi_disable();
    }
    REG32(MAILBOX_MESSAGE(index)) = arg;
    Hwi_restore(key);
}

/*
 *  ======== InterruptDsp_intPost ========
 */
Void InterruptDsp_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
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
 *  ======== InterruptDsp_intClear ========
 *  Clear interrupt
 */
UInt InterruptDsp_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;
    UInt16 index;

    index = MBX_TABLE_IDX(remoteProcId, MultiProc_self());

    arg = REG32(MAILBOX_MESSAGE(index));
    REG32(MAILBOX_IRQSTATUS_CLR_DSP(index)) = MAILBOX_REG_VAL(SUBMBX_IDX(index));

    /* Write to EOI (End Of Interrupt) register */
    REG32(MAILBOX_EOI_REG(index)) = 0x1;

    return (arg);
}

/*
 *************************************************************************
 *                      Internals functions
 *************************************************************************
 */

/*
 *  ======== InterruptDsp_intShmStub ========
 */
Void InterruptDsp_intShmStub(UInt16 idx)
{
    UInt16 srcVirtId;
    InterruptDsp_FxnTable *table;

    srcVirtId = idx / InterruptDsp_NUM_CORES;
    table = &(InterruptDsp_module->fxnTable[srcVirtId]);
    (table->func)(table->arg);
}
