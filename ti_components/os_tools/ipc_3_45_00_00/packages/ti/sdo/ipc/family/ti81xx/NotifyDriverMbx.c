/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#ifdef xdc_target__isaCompatible_v7M
#include <ti/sysbios/family/arm/ducati/Core.h>
#endif

#include <ti/sdo/ipc/interfaces/INotifyDriver.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/NotifyDriverMbx.xdc.h"

/* Bit mask operations */
#define SET_BIT(num,pos)            ((num) |= (1u << (pos)))
#define CLEAR_BIT(num,pos)          ((num) &= ~(1u << (pos)))
#define TEST_BIT(num,pos)           ((num) & (1u << (pos)))

/* Assigned mailboxes */
#define DSP_TO_HOST         0
#define DSP_TO_VIDEO        1
#define DSP_TO_VPSS         2
#define HOST_TO_DSP         3
#define HOST_TO_VIDEO       4
#define HOST_TO_VPSS        5
#define VIDEO_TO_HOST       6
#define VIDEO_TO_DSP        7
#define VPSS_TO_HOST        8
#define VPSS_TO_DSP         9
#define VIDEO_TO_VPSS       10
#define VPSS_TO_VIDEO       11

#define MAILBOX_REG_VAL(M)            (0x1 << (2 * M))

/* Register access method. */
#define REG16(A)                      (*(volatile UInt16 *) (A))
#define REG32(A)                      (*(volatile UInt32 *) (A))

#define MAILBOX_FIFOLENGTH      4

#define MAILBOX_MESSAGE(M) \
        (NotifyDriverMbx_mailboxBaseAddr + 0x40 + (0x4 * M))
#define MAILBOX_FIFOSTATUS(M) \
        (NotifyDriverMbx_mailboxBaseAddr + 0x80 + (0x4 * M))
#define MAILBOX_STATUS(M) \
        (NotifyDriverMbx_mailboxBaseAddr + 0xC0 + (0x4 * M))

/* HOST registers */
#define MAILBOX_IRQSTATUS_CLR_HOST    (NotifyDriverMbx_mailboxBaseAddr + 0x104)
#define MAILBOX_IRQENABLE_SET_HOST    (NotifyDriverMbx_mailboxBaseAddr + 0x108)
#define MAILBOX_IRQENABLE_CLR_HOST    (NotifyDriverMbx_mailboxBaseAddr + 0x10C)

/* DSP registers */
#define MAILBOX_IRQSTATUS_CLR_DSP     (NotifyDriverMbx_mailboxBaseAddr + 0x114)
#define MAILBOX_IRQENABLE_SET_DSP     (NotifyDriverMbx_mailboxBaseAddr + 0x118)
#define MAILBOX_IRQENABLE_CLR_DSP     (NotifyDriverMbx_mailboxBaseAddr + 0x11C)

/* VIDEO registers */
#define MAILBOX_IRQSTATUS_CLR_VIDEO   (NotifyDriverMbx_mailboxBaseAddr + 0x124)
#define MAILBOX_IRQENABLE_SET_VIDEO   (NotifyDriverMbx_mailboxBaseAddr + 0x128)
#define MAILBOX_IRQENABLE_CLR_VIDEO   (NotifyDriverMbx_mailboxBaseAddr + 0x12C)

/* VPSS registers */
#define MAILBOX_IRQSTATUS_CLR_VPSS    (NotifyDriverMbx_mailboxBaseAddr + 0x134)
#define MAILBOX_IRQENABLE_SET_VPSS    (NotifyDriverMbx_mailboxBaseAddr + 0x138)
#define MAILBOX_IRQENABLE_CLR_VPSS    (NotifyDriverMbx_mailboxBaseAddr + 0x13C)

#define MAILBOX_EOI_REG               (NotifyDriverMbx_mailboxBaseAddr + 0x140)

#define MBX(src, dst)                 (src##_TO_##dst)

#define PROCID_HOST                   NotifyDriverMbx_hostProcId
#define PROCID_VPSS                   NotifyDriverMbx_vpssProcId
#define PROCID_VIDEO                  NotifyDriverMbx_videoProcId
#define PROCID_DSP                    NotifyDriverMbx_dspProcId

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverMbx_Module_startup ========
 */

/* The INIT macro empties the mailbox that corresponds to 'src'-to-'dst' */
#define INIT(src, dst)                                                  \
    while (REG32(MAILBOX_STATUS(MBX(src, dst)))) {                      \
        REG32(MAILBOX_MESSAGE(MBX(src, dst)));                          \
    }                                                                   \
    REG32(MAILBOX_IRQSTATUS_CLR_##dst)                                  \
            = MAILBOX_REG_VAL(MBX(src, dst));

Int NotifyDriverMbx_Module_startup(Int phase)
{
#if defined(xdc_target__isaCompatible_64)

    INIT(HOST, DSP)
    INIT(VIDEO, DSP)
    INIT(VPSS, DSP)
    REG32(MAILBOX_EOI_REG) = 0x1;

#elif defined(xdc_target__isaCompatible_v7M)
    if (!(BIOS_smpEnabled) && (Core_getId())) {
        INIT(DSP, VPSS)
        INIT(HOST, VPSS)
        INIT(VIDEO, VPSS)
    }
    else {
        INIT(DSP, VIDEO)
        INIT(HOST, VIDEO)
        INIT(VPSS, VIDEO)
    }

#else
    INIT(DSP, HOST)
    INIT(VIDEO, HOST)
    INIT(VPSS, HOST)

#endif

    return (Startup_DONE);
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

    /*
     * Check whether remote proc ID has been set and isn't the same as the
     * local proc ID
     */
    Assert_isTrue ((params->remoteProcId != MultiProc_INVALIDID) &&
                   (params->remoteProcId != MultiProc_self()),
                   ti_sdo_ipc_Notify_A_internal);

    if (params->remoteProcId >= MultiProc_getNumProcessors() ||
        params->remoteProcId == MultiProc_INVALIDID) {
        return;    /* keep Coverity happy */
    }

    obj->remoteProcId = params->remoteProcId;
    obj->evtRegMask = 0;
    obj->notifyHandle = NULL;

    /* Disable global interrupts */
    key = Hwi_disable();

    /* Store the driver handle so it can be retreived in the isr */
    NotifyDriverMbx_module->drvHandles[obj->remoteProcId] = obj;

    /* Enable the mailbox interrupt from the remote core */
    NotifyDriverMbx_enable(obj);

    /* Restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== NotifyDriverMbx_Instance_finalize ========
 */
Void NotifyDriverMbx_Instance_finalize(NotifyDriverMbx_Object *obj)
{
    /* Disable the mailbox interrupt source */
    NotifyDriverMbx_disable(obj);

    NotifyDriverMbx_module->drvHandles[obj->remoteProcId] = NULL;
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
#define PUT_NOTIFICATION(m)                                                 \
        key = Hwi_disable();                                                \
        while(MAILBOX_FIFOLENGTH - REG32(MAILBOX_STATUS(m)) < numMsgs) {    \
            Hwi_restore(key);                                               \
            if (!waitClear) {                                               \
                return (Notify_E_FAIL);                                     \
            }                                                               \
            key = Hwi_disable();                                            \
        };                                                                  \
        REG32(MAILBOX_MESSAGE(m)) = eventId + smallPayload;                 \
        if (smallPayload == 0xFFFFFFE0) {                                   \
            REG32(MAILBOX_MESSAGE(m)) = payload;                            \
        }                                                                   \
        Hwi_restore(key);

Int NotifyDriverMbx_sendEvent(NotifyDriverMbx_Object *obj,
                              UInt32                 eventId,
                              UInt32                 payload,
                              Bool                   waitClear)
{
    UInt16 remoteProcId = obj->remoteProcId;
    UInt key, numMsgs;
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

#if defined(xdc_target__isaCompatible_64)
    if (remoteProcId == NotifyDriverMbx_hostProcId) {
        PUT_NOTIFICATION(DSP_TO_HOST)
    }
    else if (remoteProcId == NotifyDriverMbx_videoProcId) {
        PUT_NOTIFICATION(DSP_TO_VIDEO)
    }
    else {
        PUT_NOTIFICATION(DSP_TO_VPSS)
    }
#elif defined(xdc_target__isaCompatible_v7M)
    if (!(BIOS_smpEnabled) && (Core_getId())) {
        if (remoteProcId == NotifyDriverMbx_dspProcId) {
            PUT_NOTIFICATION(VPSS_TO_DSP)
        }
        else if (remoteProcId == NotifyDriverMbx_hostProcId) {
            PUT_NOTIFICATION(VPSS_TO_HOST)
        }
        else {
            PUT_NOTIFICATION(VPSS_TO_VIDEO)
        }
    }
    else {
        if (remoteProcId == NotifyDriverMbx_dspProcId) {
            PUT_NOTIFICATION(VIDEO_TO_DSP)
        }
        else if (remoteProcId == NotifyDriverMbx_hostProcId) {
            PUT_NOTIFICATION(VIDEO_TO_HOST)
        }
        else {
            PUT_NOTIFICATION(VIDEO_TO_VPSS)
        }
    }
#else
    if (remoteProcId == NotifyDriverMbx_dspProcId) {
        PUT_NOTIFICATION(HOST_TO_DSP)
    }
    else if (remoteProcId == NotifyDriverMbx_videoProcId) {
        PUT_NOTIFICATION(HOST_TO_VIDEO)
    }
    else {
        PUT_NOTIFICATION(HOST_TO_VPSS)
    }
#endif

    return (Notify_S_SUCCESS);
}

/*
 *  ======== NotifyDriverMbx_disable ========
 */
Void NotifyDriverMbx_disable(NotifyDriverMbx_Object *obj)
{
    UInt16 remoteProcId = obj->remoteProcId;

#if defined(xdc_target__isaCompatible_64)
    if (remoteProcId == NotifyDriverMbx_hostProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = MAILBOX_REG_VAL(HOST_TO_DSP);
    }
    else if (remoteProcId == NotifyDriverMbx_videoProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = MAILBOX_REG_VAL(VIDEO_TO_DSP);
    }
    else {
        REG32(MAILBOX_IRQENABLE_CLR_DSP) = MAILBOX_REG_VAL(VPSS_TO_DSP);
    }
#elif defined(xdc_target__isaCompatible_v7M)
    if (!(BIOS_smpEnabled) && (Core_getId())) {
        if (remoteProcId == NotifyDriverMbx_hostProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == NotifyDriverMbx_dspProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else {
            REG32(MAILBOX_IRQENABLE_CLR_VPSS) = MAILBOX_REG_VAL(VIDEO_TO_VPSS);
        }
    }
    else {
        if (remoteProcId == NotifyDriverMbx_hostProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VIDEO) = MAILBOX_REG_VAL(HOST_TO_VIDEO);
        }
        else if (remoteProcId == NotifyDriverMbx_dspProcId) {
            REG32(MAILBOX_IRQENABLE_CLR_VIDEO) = MAILBOX_REG_VAL(DSP_TO_VIDEO);
        }
        else {
            REG32(MAILBOX_IRQENABLE_CLR_VIDEO) = MAILBOX_REG_VAL(VPSS_TO_VIDEO);
        }
    }
#else
    if (remoteProcId == NotifyDriverMbx_dspProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(DSP_TO_HOST);
    }
    else if (remoteProcId == NotifyDriverMbx_videoProcId) {
        REG32(MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(VIDEO_TO_HOST);
    }
    else {
        REG32(MAILBOX_IRQENABLE_CLR_HOST) = MAILBOX_REG_VAL(VPSS_TO_HOST);
    }
#endif
}

/*
 *  ======== NotifyDriverMbx_enable ========
 */
Void NotifyDriverMbx_enable(NotifyDriverMbx_Object *obj)
{
    UInt16 remoteProcId = obj->remoteProcId;

#if defined(xdc_target__isaCompatible_64)
    if (remoteProcId == NotifyDriverMbx_hostProcId) {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = MAILBOX_REG_VAL(HOST_TO_DSP);
    }
    else if (remoteProcId == NotifyDriverMbx_videoProcId) {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = MAILBOX_REG_VAL(VIDEO_TO_DSP);
    }
    else {
        REG32(MAILBOX_IRQENABLE_SET_DSP) = MAILBOX_REG_VAL(VPSS_TO_DSP);
    }
#elif defined(xdc_target__isaCompatible_v7M)
    if (!(BIOS_smpEnabled) && (Core_getId())) {
        if (remoteProcId == NotifyDriverMbx_hostProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(HOST_TO_VPSS);
        }
        else if (remoteProcId == NotifyDriverMbx_dspProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(DSP_TO_VPSS);
        }
        else {
            REG32(MAILBOX_IRQENABLE_SET_VPSS) = MAILBOX_REG_VAL(VIDEO_TO_VPSS);
        }
    }
    else {
        if (remoteProcId == NotifyDriverMbx_hostProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VIDEO) = MAILBOX_REG_VAL(HOST_TO_VIDEO);
        }
        else if (remoteProcId == NotifyDriverMbx_dspProcId) {
            REG32(MAILBOX_IRQENABLE_SET_VIDEO) = MAILBOX_REG_VAL(DSP_TO_VIDEO);
        }
        else {
            REG32(MAILBOX_IRQENABLE_SET_VIDEO) = MAILBOX_REG_VAL(VPSS_TO_VIDEO);
        }
    }
#else
    if (remoteProcId == NotifyDriverMbx_dspProcId) {
        REG32(MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(DSP_TO_HOST);
    }
    else if (remoteProcId == NotifyDriverMbx_videoProcId) {
        REG32(MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(VIDEO_TO_HOST);
    }
    else {
        REG32(MAILBOX_IRQENABLE_SET_HOST) = MAILBOX_REG_VAL(VPSS_TO_HOST);
    }
#endif
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

/*
 *  Get a message from the mailbox.  The bottom 5 bits of the message
 *  contains the eventId.  The top 27 bits of the message contains either
 *  1) The payload if the payload is less than 0x7FFFFFF
 *  2) 0x7FFFFFF otherwise
 *  If the top 27 bits of the first message is 0x7FFFFFF, then the payload
 *  is in the next mailbox message.
 */
#define GET_NOTIFICATION(dst, src)                                          \
    if (REG32(MAILBOX_STATUS(MBX(src, dst)))) {                             \
        numProcessed++;                                                     \
        msg = REG32(MAILBOX_MESSAGE(MBX(src, dst)));                        \
        eventId = (UInt16)(msg & 0x1F);                                     \
        payload = msg >> 5;                                                 \
        if (payload == 0x7FFFFFF) {                                         \
            while(REG32(MAILBOX_STATUS(MBX(src, dst))) == 0);               \
            payload = REG32(MAILBOX_MESSAGE(MBX(src, dst)));                \
        }                                                                   \
        REG32(MAILBOX_IRQSTATUS_CLR_##dst) =                                \
                MAILBOX_REG_VAL(MBX(src, dst));                             \
        obj = NotifyDriverMbx_module->drvHandles[PROCID_##src];             \
        Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_internal);           \
        if (TEST_BIT(obj->evtRegMask, eventId)) {                           \
            ti_sdo_ipc_Notify_exec(obj->notifyHandle,                       \
                                   eventId,                                 \
                                   payload);                                \
        }                                                                   \
    }

Void NotifyDriverMbx_isr(UArg arg)
{
    NotifyDriverMbx_Object *obj;
    UInt32 msg, payload;
    UInt16 eventId;
    Int numProcessed;

#if defined(xdc_target__isaCompatible_64)
    do {
        numProcessed = 0;
        GET_NOTIFICATION(DSP, HOST)
        GET_NOTIFICATION(DSP, VPSS)
        GET_NOTIFICATION(DSP, VIDEO)
    }
    while (numProcessed != 0);

    /* Write to EOI (End Of Interrupt) register */
    REG32(MAILBOX_EOI_REG) = 0x1;

#elif defined(xdc_target__isaCompatible_v7M)
    do {
        numProcessed = 0;
        if (!(BIOS_smpEnabled) && (Core_getId())) {
            GET_NOTIFICATION(VPSS, HOST)
            GET_NOTIFICATION(VPSS, DSP)
            GET_NOTIFICATION(VPSS, VIDEO)
        }
        else {
            GET_NOTIFICATION(VIDEO, HOST)
            GET_NOTIFICATION(VIDEO, DSP)
            GET_NOTIFICATION(VIDEO, VPSS)
        }
    }
    while (numProcessed != 0);

#else
    do {
        numProcessed = 0;
        GET_NOTIFICATION(HOST, DSP)
        GET_NOTIFICATION(HOST, VPSS)
        GET_NOTIFICATION(HOST, VIDEO)
    }
    while (numProcessed != 0);

#endif
}

/*
 *  ======== NotifyDriverMbx_setNotifyHandle ========
 */
Void NotifyDriverMbx_setNotifyHandle(NotifyDriverMbx_Object *obj,
                                     Ptr notifyHandle)
{
    /* Internally used, so no Assert needed */
    obj->notifyHandle = (ti_sdo_ipc_Notify_Handle)notifyHandle;
}
