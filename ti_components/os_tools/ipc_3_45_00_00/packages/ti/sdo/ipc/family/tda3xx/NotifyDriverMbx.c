/*
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== NotifyDriverMbx.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Startup.h>

#if defined(xdc_target__isaCompatible_64P)

#include <ti/sysbios/family/c64p/Hwi.h>

#elif defined(xdc_target__isaCompatible_arp32)

#include <ti/sysbios/family/arp32/Hwi.h>

#elif defined(xdc_target__isaCompatible_v7M)

#include <ti/sysbios/family/arm/m3/Hwi.h>

#else
#error Invalid target
#endif

#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/family/tda3xx/NotifySetup.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/NotifyDriverMbx.xdc.h"

/* Bit mask operations */
#define SET_BIT(num,pos)            ((num) |= (1u << (pos)))
#define CLEAR_BIT(num,pos)          ((num) &= ~(1u << (pos)))
#define TEST_BIT(num,pos)           ((num) & (1u << (pos)))

/* register access methods */
#define REG16(A)        (*(volatile UInt16 *)(A))
#define REG32(A)        (*(volatile UInt32 *)(A))

#define MAILBOX_FIFOLENGTH 4
#define PROCID(idx) (NotifyDriverMbx_procIdTable[(idx)])

#define MBX_BASEADDR_IDX(idx) \
        ((NotifyDriverMbx_mailboxTable[(idx)] >> 16) & 0xFFFF)

#define MAILBOX_ADDR(idx) \
        (NotifyDriverMbx_mailboxBaseAddr[MBX_BASEADDR_IDX(idx)])

#define MBX_TABLE_IDX(src, dst) \
        ((PROCID(src) * NotifyDriverMbx_NUM_CORES) + PROCID(dst))

#define SUBMBX_IDX(idx) (NotifyDriverMbx_mailboxTable[(idx)] & 0xFF)

#define MBX_USER_IDX(idx) ((NotifyDriverMbx_mailboxTable[(idx)] >> 8) & 0xFF)

#define MAILBOX_REG_VAL(m) (0x1 << (2 * m))

#define MAILBOX_MESSAGE(idx) \
        (MAILBOX_ADDR(idx) + 0x40 + (0x4 * SUBMBX_IDX(idx)))

#define MAILBOX_STATUS(idx) \
        (MAILBOX_ADDR(idx) + 0xC0 + (0x4 * SUBMBX_IDX(idx)))

#define MAILBOX_IRQSTATUS_CLR(idx) \
        (MAILBOX_ADDR(idx) + 0x104 + (0x10 * MBX_USER_IDX(idx)))

#define MAILBOX_IRQENABLE_SET(idx) \
        (MAILBOX_ADDR(idx) + 0x108 + (0x10 * MBX_USER_IDX(idx)))

#define MAILBOX_IRQENABLE_CLR(idx) \
        (MAILBOX_ADDR(idx) + 0x10C + (0x10 * MBX_USER_IDX(idx)))

#define MAILBOX_EOI_REG(idx) (MAILBOX_ADDR(idx) + 0x140)

#define EVENT_GROUP_SIZE 32

/* empty the mailbox for the given index, clear its interrupt */
#define MAILBOX_INIT(idx)                                                   \
    while (REG32(MAILBOX_STATUS(idx)) != 0) {                               \
        REG32(MAILBOX_MESSAGE(idx));                                        \
    }                                                                       \
    REG32(MAILBOX_IRQSTATUS_CLR(idx)) = MAILBOX_REG_VAL(SUBMBX_IDX(idx));   \
    REG32(MAILBOX_EOI_REG(idx)) = MBX_USER_IDX(idx);

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverMbx_Module_startup ========
 */
Int NotifyDriverMbx_Module_startup(Int phase)
{
#if defined(xdc_target__isaCompatible_64P)

    /* nothing to do on this processor */
    return (Startup_DONE);

#elif defined(xdc_target__isaCompatible_arp32)

    /* nothing to do on this processor */
    return (Startup_DONE);

#elif defined(xdc_target__isaCompatible_v7M)

    /* nothing to do on this processor */
    return (Startup_DONE);

#else
#error Invalid target
#endif
}

/*
 **************************************************************
 *                       Instance functions
 **************************************************************
 */

/*
 *  ======== NotifyDriverMbx_Instance_init ========
 */
Void NotifyDriverMbx_Instance_init(NotifyDriverMbx_Object *obj,
        const NotifyDriverMbx_Params *params)
{
    UInt        key;
    UInt16      selfVirtId;
    UInt16      index;

    obj->evtRegMask = 0;
    obj->notifyHandle = NULL;
    obj->remoteProcId = params->remoteProcId;
    obj->remoteVirtId = PROCID(params->remoteProcId);
    obj->cpuIntrNum = params->intVectorId;

    /* disable global interrupts */
    key = Hwi_disable();

    /* clear inbound mailbox of all old messages */
    selfVirtId = PROCID(MultiProc_self());
    index = (obj->remoteVirtId * NotifyDriverMbx_NUM_CORES) + selfVirtId;
    MAILBOX_INIT(index);

    /* must use processor virtual ID to store driver handle in table */
    NotifyDriverMbx_module->drvHandles[obj->remoteVirtId] = obj;

    /* plug the cpu interrupt */
    NotifySetup_plugHwi(params->remoteProcId, params->intVectorId,
            NotifyDriverMbx_isr);

    /* enable the mailbox interrupt from the remote core */
    NotifyDriverMbx_enable(obj);

    /* restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== NotifyDriverMbx_Instance_finalize ========
 */
Void NotifyDriverMbx_Instance_finalize(NotifyDriverMbx_Object *obj)
{

    /* disable the mailbox interrupt source */
    NotifyDriverMbx_disable(obj);

    /* unplug isr and unprogram the event dispatcher */
    NotifySetup_unplugHwi(obj->remoteProcId, obj->cpuIntrNum);

    /* must use processor virtual ID to remove driver handle from table */
    NotifyDriverMbx_module->drvHandles[obj->remoteVirtId] = NULL;
}

/*
 *  ======== NotifyDriverMbx_registerEvent ========
 */
Void NotifyDriverMbx_registerEvent(NotifyDriverMbx_Object *obj,
                                   UInt32 eventId)
{
    UInt hwiKey;

    /*
     *  Disable interrupt line to ensure that isr doesn't
     *  preempt registerEvent and encounter corrupt state
     */
    hwiKey = Hwi_disable();

    /* Set the 'registered' bit */
    SET_BIT(obj->evtRegMask, eventId);

    /* Restore the interrupt line */
    Hwi_restore(hwiKey);
}

/*
 *  ======== NotifyDriverMbx_unregisterEvent ========
 */
Void NotifyDriverMbx_unregisterEvent(NotifyDriverMbx_Object *obj,
                                     UInt32 eventId)
{
    UInt hwiKey;

    /*
     *  Disable interrupt line to ensure that isr doesn't
     *  preempt registerEvent and encounter corrupt state
     */
    hwiKey = Hwi_disable();

    /* Clear the registered bit */
    CLEAR_BIT(obj->evtRegMask, eventId);

    /* Restore the interrupt line */
    Hwi_restore(hwiKey);
}

/*
 *  ======== NotifyDriverMbx_sendEvent ========
 */
/*
 *  PUT_NOTIFICATION will spin waiting for enough room in the mailbox FIFO
 *  to store the number of messages needed for the notification ('numMsgs').
 *  If spinning is necesssary (i.e. if waitClear is TRUE and there isn't enough
 *  room in the FIFO) then PUT_NOTIFICATION will allow pre-emption while
 *  spinning.
 *
 *  PUT_NOTIFICATION needs to prevent another local thread from writing to the
 *  same mailbox after the current thread has
 *  1) determined that there is enough room to write the notification and
 *  2) written the first of two messages to the mailbox.
 *  This is needed to respectively prevent
 *  1) both threads from incorrectly assuming there is enough space in the FIFO
 *     for their own notifications
 *  2) the interrupting thread from writing a notification between two
 *     two messages that need to be successivly written by the preempted thread.
 *  Therefore, the check for enough FIFO room and one/both mailbox write(s)
 *  should all occur atomically (i.e. with interrupts disabled)
 */
#define PUT_NOTIFICATION(idx)                                               \
        key = Hwi_disable();                                                \
        while(MAILBOX_FIFOLENGTH - REG32(MAILBOX_STATUS(idx)) < numMsgs) {  \
            Hwi_restore(key);                                               \
            if (!waitClear) {                                               \
                return (Notify_E_FAIL);                                     \
            }                                                               \
            key = Hwi_disable();                                            \
        };                                                                  \
        REG32(MAILBOX_MESSAGE(idx)) = eventId + smallPayload;               \
        if (smallPayload == 0xFFFFFFE0) {                                   \
            REG32(MAILBOX_MESSAGE(idx)) = payload;                          \
        }                                                                   \
        Hwi_restore(key);

Int NotifyDriverMbx_sendEvent(NotifyDriverMbx_Object *obj, UInt32 eventId,
        UInt32 payload, Bool waitClear)
{
    UInt16 selfVirtId = PROCID(MultiProc_self());
    UInt16 index;
    UInt key;
    UInt numMsgs;
    UInt32 smallPayload;

    /* Decide if the payload is small enough to fit in the first mbx msg */
    if (payload < 0x7FFFFFF) {
        smallPayload = (payload << 5);
        numMsgs = 1;
    }
    else {
        smallPayload = 0xFFFFFFE0;
        numMsgs = 2;
    }

    index = (selfVirtId * NotifyDriverMbx_NUM_CORES) + obj->remoteVirtId;
    PUT_NOTIFICATION(index);

    return (Notify_S_SUCCESS);
}

/*
 *  ======== NotifyDriverMbx_disable ========
 */
Void NotifyDriverMbx_disable(NotifyDriverMbx_Object *obj)
{
    UInt16 selfVirtId = PROCID(MultiProc_self());
    UInt16 index;

    index = (obj->remoteVirtId * NotifyDriverMbx_NUM_CORES) + selfVirtId;
    REG32(MAILBOX_IRQENABLE_CLR(index)) = MAILBOX_REG_VAL(SUBMBX_IDX(index));
}

/*
 *  ======== NotifyDriverMbx_enable ========
 */
Void NotifyDriverMbx_enable(NotifyDriverMbx_Object *obj)
{
    UInt16 selfVirtId = PROCID(MultiProc_self());
    UInt16 index;

    index = (obj->remoteVirtId * NotifyDriverMbx_NUM_CORES) + selfVirtId;
    REG32(MAILBOX_IRQENABLE_SET(index)) = MAILBOX_REG_VAL(SUBMBX_IDX(index));
}

/*
 *  ======== NotifyDriverMbx_disableEvent ========
 */
Void NotifyDriverMbx_disableEvent(NotifyDriverMbx_Object *obj, UInt32 eventId)
{
    /* NotifyDriverMbx_disableEvent not supported by this driver */
    Assert_isTrue(FALSE, NotifyDriverMbx_A_notSupported);
}

/*
 *  ======== NotifyDriverMbx_enableEvent ========
 */
Void NotifyDriverMbx_enableEvent(NotifyDriverMbx_Object *obj, UInt32 eventId)
{
    /* NotifyDriverMbx_enableEvent not supported by this driver */
    Assert_isTrue(FALSE, NotifyDriverMbx_A_notSupported);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverMbx_isr ========
 */

/*  Read a message from the mailbox. The low 5 bits of the message
 *  contains the eventId. The high 27 bits of the message contains
 *  either:
 *      1) The payload if the payload is less than 0x7FFFFFF
 *      2) 0x7FFFFFF otherwise
 *  If the high 27 bits of the first message is 0x7FFFFFF, then the
 *  payload is in the next mailbox message.
 *
 *  idx = mailbox table index
 */
#define MESSAGE_DELIVERY(idx)                                               \
    msg = REG32(MAILBOX_MESSAGE(idx));                                      \
    eventId = (UInt16)(msg & 0x1F);                                         \
    payload = msg >> 5;                                                     \
    if (payload == 0x7FFFFFF) {                                             \
        while(REG32(MAILBOX_STATUS(idx)) == 0);                             \
        payload = REG32(MAILBOX_MESSAGE(idx));                              \
    }                                                                       \
    REG32(MAILBOX_IRQSTATUS_CLR(idx)) = MAILBOX_REG_VAL(SUBMBX_IDX(idx));   \
    obj = NotifyDriverMbx_module->drvHandles[srcVirtId];                    \
    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_internal);               \
    if (TEST_BIT(obj->evtRegMask, eventId)) {                               \
        ti_sdo_ipc_Notify_exec(obj->notifyHandle, eventId, payload);        \
    }                                                                       \
    REG32(MAILBOX_EOI_REG(idx)) = MBX_USER_IDX(idx);

Void NotifyDriverMbx_isr(UInt16 idx)
{
    NotifyDriverMbx_Object *obj;
    UInt32 msg, payload;
    UInt16 eventId;
    UInt16 srcVirtId;

    srcVirtId = idx / NotifyDriverMbx_NUM_CORES;
    MESSAGE_DELIVERY(idx)
}

/*
 *  ======== NotifyDriverMbx_setNotifyHandle ========
 */
Void NotifyDriverMbx_setNotifyHandle(NotifyDriverMbx_Object *obj,
        Ptr notifyHandle)
{
    /* internally used, so no assert needed */
    obj->notifyHandle = (ti_sdo_ipc_Notify_Handle)notifyHandle;
}
