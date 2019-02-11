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
 *  ======== NotifyDriverShm.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sdo/utils/List.h>

#include <ti/sdo/ipc/interfaces/INotifyDriver.h>

#include "package/internal/NotifyDriverShm.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/utils/_MultiProc.h>

/* Bit mask operations */
#define SET_BIT(num,pos)            ((num) |= (1u << (pos)))
#define CLEAR_BIT(num,pos)          ((num) &= ~(1u << (pos)))
#define TEST_BIT(num,pos)           ((num) & (1u << (pos)))

#define EVENTENTRY(eventChart, entrySize, eventId) \
            ((NotifyDriverShm_EventEntry *) \
             ((UInt32)(eventChart) + ((entrySize) * (eventId))));

/*
 **************************************************************
 *                       Instance functions
 **************************************************************
 */

/*
 *  ======== NotifyDriverShm_Instance_init ========
 */
Int NotifyDriverShm_Instance_init(NotifyDriverShm_Object *obj,
                                  const NotifyDriverShm_Params *params,
                                  Error_Block *eb)
{
    UInt16 regionId;
    SizeT regionCacheSize, minAlign, procCtrlSize;

   /*
    * Check whether remote proc ID has been set and isn't the same as the
    * local proc ID
    */
    Assert_isTrue ((params->remoteProcId != MultiProc_INVALIDID) &&
                   (params->remoteProcId != MultiProc_self()),
                   ti_sdo_ipc_Ipc_A_invParam);

    /*
     *  Determine obj->cacheEnabled using params->cacheEnabled and SharedRegion
     *  cache flag setting, if applicable.
     */
    obj->cacheEnabled = params->cacheEnabled;
    minAlign = params->cacheLineSize;
    if (minAlign == 0) {
        /* Fix alignment of zero */
        minAlign = sizeof(Ptr);
    }
    regionId = SharedRegion_getId(params->sharedAddr);
    if (regionId != SharedRegion_INVALIDREGIONID) {
        /*
         *  Override the user cacheEnabled setting if the region
         *  cacheEnabled is FALSE.
         */
        if (!SharedRegion_isCacheEnabled(regionId)) {
            obj->cacheEnabled = FALSE;
        }

        regionCacheSize = SharedRegion_getCacheLineSize(regionId);

        /*
         *  Override the user cache line size setting if the region
         *  cache line size is smaller.
         */
        if (regionCacheSize < minAlign) {
            minAlign = regionCacheSize;
        }
    }

    /* Check if shared memory base addr is aligned to cache line boundary.*/
    Assert_isTrue ((UInt32)params->sharedAddr % minAlign == 0,
        ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

    obj->remoteProcId           = params->remoteProcId;

    /*
     *  Store all interrupt information so it may be used (if neccessary) by
     *  the IInterrupt delegates
     */
    obj->intInfo.remoteIntId    = params->remoteIntId;
    obj->intInfo.localIntId     = params->localIntId;
    obj->intInfo.intVectorId    = params->intVectorId;

    obj->nesting            = 0;

    if (params->remoteProcId > MultiProc_self()) {
        obj->selfId  = 0;
        obj->otherId = 1;
    }
    else {
        obj->selfId  = 1;
        obj->otherId = 0;
    }

    /* Initialize pointers to shared memory regions */
    procCtrlSize = _Ipc_roundup(sizeof(NotifyDriverShm_ProcCtrl), minAlign);

    /*
     *  Save the eventEntrySize in obj since we will need it at runtime to
     *  index the event charts
     */
    obj->eventEntrySize = _Ipc_roundup(sizeof(NotifyDriverShm_EventEntry),
        minAlign);

    obj->selfProcCtrl = (NotifyDriverShm_ProcCtrl *)
        ((UInt32)params->sharedAddr + (obj->selfId * procCtrlSize));
    obj->otherProcCtrl = (NotifyDriverShm_ProcCtrl *)
        ((UInt32)params->sharedAddr + (obj->otherId * procCtrlSize));
    obj->selfEventChart  = (NotifyDriverShm_EventEntry *)
        ((UInt32)params->sharedAddr
         + (2 * procCtrlSize)
         + (obj->eventEntrySize * ti_sdo_ipc_Notify_numEvents * obj->selfId));
    obj->otherEventChart  = (NotifyDriverShm_EventEntry *)
         ((UInt32)params->sharedAddr
         + (2 * procCtrlSize)
         + (obj->eventEntrySize * ti_sdo_ipc_Notify_numEvents * obj->otherId));

    /* Allocate memory for regChart and init to (UInt32)-1 (unregistered) */
    obj->regChart = Memory_valloc(
            NotifyDriverShm_Object_heap(),
            (sizeof(UInt32) * ti_sdo_ipc_Notify_numEvents),
            0,
            ~0,
            eb);
    if (obj->regChart == NULL) {
        return (1);
    }

    /* Enable all events initially.*/
    obj->selfProcCtrl->eventEnableMask = 0xFFFFFFFF;

    /* Write back our own ProcCtrl */
    if (obj->cacheEnabled) {
        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
            Cache_Type_ALL, TRUE);
    }

    /* Register the incoming interrupt */
    NotifyDriverShm_InterruptProxy_intRegister(obj->remoteProcId,
        &(obj->intInfo), (Fxn)NotifyDriverShm_isr, (UArg)obj);

    return (0);
}

/*
 *  ======== NotifyDriverShm_Instance_finalize ========
 */
Void NotifyDriverShm_Instance_finalize(NotifyDriverShm_Object *obj, int status)
{
    if (status == 0) {
        /* Indicate that driver is no longer ready to send/receive events */
        obj->selfProcCtrl->recvInitStatus = 0;
        obj->selfProcCtrl->sendInitStatus = 0;

        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
            Cache_Type_ALL, TRUE);

        /* Unregister interrupt */
        NotifyDriverShm_InterruptProxy_intUnregister(obj->remoteProcId,
            &(obj->intInfo));

        /* Free memory alloc'ed for regChart */
        Memory_free(NotifyDriverShm_Object_heap(), obj->regChart,
            sizeof(UInt32) * ti_sdo_ipc_Notify_numEvents);
    }
}

/*
 *  ======== NotifyDriverShm_registerEvent ========
 */
Void NotifyDriverShm_registerEvent(NotifyDriverShm_Object *obj,
                                   UInt32 eventId)
{
    NotifyDriverShm_EventEntry *eventEntry;
    Int i, j;

    /*
     *  Disable interrupt line to ensure that NotifyDriverShm_isr doesn't
     *  preempt registerEvent and encounter corrupt state
     */
    NotifyDriverShm_disable(obj);

    /*
     *  Add an entry for the registered event into the Event Registration
     *  Chart, in ascending order of event numbers (and decreasing
     *  priorities).
     */
    for (i = 0; i < ti_sdo_ipc_Notify_numEvents; i++) {
        /* Find the correct slot in the registration array.*/
        if (obj->regChart[i] == (UInt32)-1) {
            for (j = i - 1; j >= 0; j--) {
                if (eventId < obj->regChart[j]) {
                    obj->regChart[j + 1] = obj->regChart[j];
                    i = j;
                }
                else {
                    /* End the loop, slot found.*/
                    j = -1;
                }
            }
            obj->regChart[i] = eventId;
            break;
        }
    }

    /*
     *  Clear any pending unserviced event as there are no listeners
     *  for the pending event
     */
    eventEntry = EVENTENTRY(obj->selfEventChart, obj->eventEntrySize, eventId)
    eventEntry->flag = NotifyDriverShm_DOWN;
    if (obj->cacheEnabled) {
        Cache_wbInv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
                    Cache_Type_ALL, TRUE);
    }

    /* Set the 'registered' bit in shared memory and write back */
    SET_BIT(obj->selfProcCtrl->eventRegMask, eventId);
    if (obj->cacheEnabled) {
        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
                    Cache_Type_ALL, TRUE);
    }

    /* Restore the interrupt line */
    NotifyDriverShm_enable(obj);
}

/*
 *  ======== NotifyDriverShm_unregisterEvent ========
 */
Void NotifyDriverShm_unregisterEvent(NotifyDriverShm_Object *obj,
                                     UInt32 eventId)
{
    NotifyDriverShm_EventEntry *eventEntry;
    Int i, j;

    /*
     *  Disable interrupt line to ensure that NotifyDriverShm_isr doesn't
     *  preempt registerEvent and encounter corrupt state
     */
    NotifyDriverShm_disable(obj);

    /*
     *  First unset the registered bit in shared memory so no notifications
     *  arrive after this point
     */
    CLEAR_BIT(obj->selfProcCtrl->eventRegMask, eventId);
    if (obj->cacheEnabled) {
        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
                    Cache_Type_ALL, TRUE);
    }

    /*
     *  Clear any pending unserviced event as there are no listeners
     *  for the pending event.  This should be done only after the event
     *  is unregistered from shared memory so the other processor doesn't
     *  successfully send an event our way immediately after unflagging this
     *  event.
     */
    eventEntry = EVENTENTRY(obj->selfEventChart, obj->eventEntrySize, eventId);
    eventEntry->flag = NotifyDriverShm_DOWN;

    /* Write back both the flag and the reg mask */
    if (obj->cacheEnabled) {
        Cache_wbInv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
                    Cache_Type_ALL, TRUE);
    }

    /*
     *  Re-arrange eventIds in the Event Registration Chart so there is
     *  no gap caused by the removal of this eventId
     *
     *  There is no need to make this atomic since Notify_exec cannot preempt:
     *  the event has already been disabled in shared memory (see above)
     */
    for (i = 0; i < ti_sdo_ipc_Notify_numEvents; i++) {
        if (eventId == obj->regChart[i]) {
            obj->regChart[i] = (UInt32)-1;
            for (j = i + 1; (j != ti_sdo_ipc_Notify_numEvents) &&
                    (obj->regChart[j] != (UInt32)-1); j++) {
                obj->regChart[j - 1] = obj->regChart[j];
                obj->regChart[j] = (UInt32)-1;
            }
            break;
        }
    }

    /* Restore the interrupt line */
    NotifyDriverShm_enable(obj);
}

/*
 *  ======== NotifyDriverShm_sendEvent ========
 */
Int NotifyDriverShm_sendEvent(NotifyDriverShm_Object *obj,
                              UInt32                 eventId,
                              UInt32                 payload,
                              Bool                   waitClear)
{
    NotifyDriverShm_EventEntry *eventEntry;
    UInt32 i;
    UInt sysKey;

    eventEntry = EVENTENTRY(obj->otherEventChart, obj->eventEntrySize, eventId);

    /* Check whether driver on other processor is initialized */
    if (obj->cacheEnabled) {
        Cache_inv(obj->otherProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
                  Cache_Type_ALL, TRUE);
    }

    if (obj->otherProcCtrl->recvInitStatus != NotifyDriverShm_INIT_STAMP) {
        /*
         * This may be used for polling till the other driver is ready, so
         * do not assert or error
         */
        return (Notify_E_NOTINITIALIZED);
    }

    /* Check to see if the remote event is enabled */
    if (!TEST_BIT(obj->otherProcCtrl->eventEnableMask, eventId)) {
        return (Notify_E_EVTDISABLED);
    }

    /* Check to see if the remote event is registered */
    if (!TEST_BIT(obj->otherProcCtrl->eventRegMask, eventId)) {
        return (Notify_E_EVTNOTREGISTERED);
    }


    if (waitClear) {
        i = 0;

        if (obj->cacheEnabled) {
            Cache_inv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
                Cache_Type_ALL, TRUE);
        }

        /*
         *  The system gate is needed to ensure that checking eventEntry->flag
         *  is atomic with the eventEntry modifications (flag/payload).
         */
        sysKey = Hwi_disable();

        /* Wait for completion of previous event from other side. */
        while ((eventEntry->flag != NotifyDriverShm_DOWN)) {
            /*
             * Leave critical section protection. Create a window
             * of opportunity for other interrupts to be handled.
             */
            Hwi_restore(sysKey);
            i++;
            if ((i != (UInt32)-1) &&
                (i == ti_sdo_ipc_Notify_sendEventPollCount)) {
                return (Notify_E_TIMEOUT);
            }

            if (obj->cacheEnabled) {
                Cache_inv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
                    Cache_Type_ALL, TRUE);
            }

            /* Re-enter the system gate */
            sysKey = Hwi_disable();
        }
    }
    else {
        /*
         *  The system gate is needed to ensure that checking eventEntry->flag
         *  is atomic with the eventEntry modifications (flag/payload).
         */
        sysKey = Hwi_disable();
    }

    /* Set the event bit field and payload.*/
    eventEntry->payload = payload;
    eventEntry->flag    = NotifyDriverShm_UP;
    if (obj->cacheEnabled) {
        Cache_wbInv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
            Cache_Type_ALL, TRUE);
    }

    /* Send an interrupt to the Remote Processor */
    NotifyDriverShm_InterruptProxy_intSend(obj->remoteProcId, &(obj->intInfo),
                                           eventId);

    /* must not restore interrupts before sending the interrupt */
    Hwi_restore(sysKey);

    return (Notify_S_SUCCESS);
}

/*
 *  ======== NotifyDriverShm_disable ========
 */
Void NotifyDriverShm_disable(NotifyDriverShm_Object *obj)
{
    /* Disable the incoming interrupt line */
    NotifyDriverShm_InterruptProxy_intDisable(obj->remoteProcId,
                                              &(obj->intInfo));
}

/*
 *  ======== NotifyDriverShm_enable ========
 */
Void NotifyDriverShm_enable(NotifyDriverShm_Object *obj)
{
    /* Enable the incoming interrupt line */
    NotifyDriverShm_InterruptProxy_intEnable(obj->remoteProcId,
                                             &(obj->intInfo));
}

/*
 *  ======== NotifyDriverShm_disableEvent ========
 */
Void NotifyDriverShm_disableEvent(NotifyDriverShm_Object *obj, UInt32 eventId)
{
    UInt sysKey;
    NotifyDriverShm_EventEntry *eventEntry;

    Assert_isTrue(eventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Ipc_A_invArgument);

    /*
     *  Atomically unset the corresponding bit in the processor's
     *  eventEnableMask
     */
    sysKey = Hwi_disable();
    CLEAR_BIT(obj->selfProcCtrl->eventEnableMask, eventId);
    Hwi_restore(sysKey);
    if (obj->cacheEnabled) {
        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
            Cache_Type_ALL, TRUE);
    }

    eventEntry = EVENTENTRY(obj->selfEventChart, obj->eventEntrySize,
            eventId);
    if (obj->cacheEnabled) {
        Cache_inv(eventEntry,
                  sizeof(NotifyDriverShm_EventEntry),
                  Cache_Type_ALL, TRUE);
    }

    /*
     *  Disable incoming Notify interrupts.  This is done to ensure that the
     *  eventEntry->flag is read atomically with any write back to shared
     *  memory
     */
    NotifyDriverShm_disable(obj);

    /*
     *  Is the local NotifyDriverShm_disableEvent happening between the
     *  following two NotifyDriverShm_sendEvent operations on the remote
     *  processor?
     *  1. Writing NotifyDriverShm_UP to shared memory
     *  2. Sending the interrupt across
     *  If so, we should handle this event so the other core isn't left spinning
     *  until the event is re-enabled and the next NotifyDriverShm_isr executes
     *  This race condition is very rare but we need to account for it:
     */
    if (eventEntry->flag == NotifyDriverShm_UP) {
        /*
         *  Acknowledge the event. No need to store the payload. The other side
         *  will not send this event again even though flag is down, because the
         *  event is now disabled. So the payload within the eventChart will not
         *  get overwritten.
         */
        eventEntry->flag = NotifyDriverShm_DOWN;

        /* Write back acknowledgement */
        if (obj->cacheEnabled) {
            Cache_wbInv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
                Cache_Type_ALL, TRUE);
        }

        /*
         *  Execute the callback function. This will execute in a Task
         *  or Swi context (not Hwi!)
         */
        ti_sdo_ipc_Notify_exec(obj->notifyHandle, eventId, eventEntry->payload);
    }

    /* Re-enable incoming Notify interrupts */
    NotifyDriverShm_enable(obj);
}

/*
 *  ======== NotifyDriverShm_enableEvent ========
 */
Void NotifyDriverShm_enableEvent(NotifyDriverShm_Object *obj, UInt32 eventId)
{
    UInt sysKey;

    Assert_isTrue(eventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Ipc_A_invArgument);

    /*
     * Atomically set the corresponding bit in the processor's
     * eventEnableMask
     */
    sysKey = Hwi_disable();
    SET_BIT(obj->selfProcCtrl->eventEnableMask, eventId);
    Hwi_restore(sysKey);

    if (obj->cacheEnabled) {
        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
            Cache_Type_ALL, TRUE);
    }
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverShm_sharedMemReq ========
 */
SizeT NotifyDriverShm_sharedMemReq(const NotifyDriverShm_Params *params)
{
    UInt16 regionId;
    SizeT regionCacheSize;
    SizeT minAlign, memReq;

    /* Ensure that params is non-NULL */
    Assert_isTrue(params != NULL, ti_sdo_ipc_Ipc_A_internal);

    /*
     *  Determine obj->cacheEnabled using params->cacheEnabled and SharedRegion
     *  cache flag setting, if applicable.
     */
    minAlign = params->cacheLineSize;
    if (minAlign == 0) {
        /* Fix alignment of zero */
        minAlign = sizeof(Ptr);
    }
    regionId = SharedRegion_getId(params->sharedAddr);
    if (regionId != SharedRegion_INVALIDREGIONID) {
        regionCacheSize = SharedRegion_getCacheLineSize(regionId);
        /* Override minAlign if the region cache line size is smaller */
        if (regionCacheSize < minAlign) {
            minAlign = regionCacheSize;
        }
    }

    /* Determine obj->align which will be used to _Ipc_roundup addresses */
    memReq = ((_Ipc_roundup(sizeof(NotifyDriverShm_ProcCtrl), minAlign)) * 2)
           + ((_Ipc_roundup(sizeof(NotifyDriverShm_EventEntry), minAlign) * 2
              * ti_sdo_ipc_Notify_numEvents));

    return (memReq);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverShm_isr ========
 */
Void NotifyDriverShm_isr(UArg arg)
{
    UInt                            i;
    NotifyDriverShm_EventEntry      *eventEntry;
    NotifyDriverShm_Object          *obj;
    UInt32                          eventId;
    UInt32                          payload;

    obj = (NotifyDriverShm_Object *)arg;

    /* Make sure the NotifyDriverShm_Object is not NULL */
    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_internal);

    /* Clear the remote interrupt */
    NotifyDriverShm_InterruptProxy_intClear(obj->remoteProcId,
                                            &(obj->intInfo));

    /*
     * Iterate till no asserted event is found for one complete loop
     * through all registered events.
     */
    i = 0;
    do {
        eventId = obj->regChart[i];

        /* Check if the entry is a valid registered event. */
        if (eventId != (UInt32)-1) {
            /*
             *  Check whether the event is disabled. If so, avoid the
             *  unnecessary Cache invalidate. NOTE: selfProcCtrl does not have
             *  to be cache-invalidated because:
             *  1) Whenever self is written to by the local processor its memory
             *     is also invalidated
             *  2) 'selfProcCtrl' is never written to by the remote processor
             */
            if (!TEST_BIT(obj->selfProcCtrl->eventEnableMask,
                (UInt32)eventId)) {
                i++;
                continue;
            }

            eventEntry = EVENTENTRY(obj->selfEventChart, obj->eventEntrySize,
                eventId);

            if (obj->cacheEnabled) {
                Cache_inv(eventEntry,
                          sizeof(NotifyDriverShm_EventEntry),
                          Cache_Type_ALL, TRUE);
            }

            /* Check if the event is set */
            if (eventEntry->flag == NotifyDriverShm_UP) {
                /*
                 *  Save the payload since it may be overwritten before
                 *  Notify_exec is called
                 */
                payload = eventEntry->payload;

                /* Acknowledge the event. */
                eventEntry->flag = NotifyDriverShm_DOWN;

                /* Write back acknowledgement */
                if (obj->cacheEnabled) {
                    Cache_wbInv(eventEntry, sizeof(NotifyDriverShm_EventEntry),
                        Cache_Type_ALL, TRUE);
                }

                /* Execute the callback function */
                ti_sdo_ipc_Notify_exec(obj->notifyHandle, eventId, payload);

                /* reinitialize the event check counter. */
                i = 0;
            }
            else {
                /* check for next event. */
                i++;
            }
        }
    }
    while ((eventId != (UInt32)-1) && (i < ti_sdo_ipc_Notify_numEvents));
}

/*
 *  ======== NotifyDriverShm_setNotifyHandle ========
 */
Void NotifyDriverShm_setNotifyHandle(NotifyDriverShm_Object *obj,
                                     Ptr notifyHandle)
{
    /* Internally used, so no Assert needed */
    obj->notifyHandle = (ti_sdo_ipc_Notify_Handle)notifyHandle;

    /* Indicate that the driver is initialized for this processor */
    obj->selfProcCtrl->recvInitStatus = NotifyDriverShm_INIT_STAMP;
    obj->selfProcCtrl->sendInitStatus = NotifyDriverShm_INIT_STAMP;

    /* Write back our own ProcCtrl */
    if (obj->cacheEnabled) {
        Cache_wbInv(obj->selfProcCtrl, sizeof(NotifyDriverShm_ProcCtrl),
            Cache_Type_ALL, TRUE);
    }
}
