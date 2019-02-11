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
 *  ======== Notify.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Error.h>

#include <ti/sdo/ipc/interfaces/INotifyDriver.h>

#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/utils/List.h>

#include <ti/sysbios/hal/Hwi.h>

#include "package/internal/Notify.xdc.h"

#define ISRESERVED(eventId) (((eventId) & 0xFFFF) >= ti_sdo_ipc_Notify_reservedEvents || \
                                (((eventId) >> 16) == Notify_SYSTEMKEY))

/* Bit mask operations */
#define SET_BIT(num,pos)            ((num) |= (1u << (pos)))
#define CLEAR_BIT(num,pos)          ((num) &= ~(1u << (pos)))
#define TEST_BIT(num,pos)           ((num) & (1u << (pos)))

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(Notify_attach);
    #pragma FUNC_EXT_CALLED(Notify_disable);
    #pragma FUNC_EXT_CALLED(Notify_disableEvent);
    #pragma FUNC_EXT_CALLED(Notify_enableEvent);
    #pragma FUNC_EXT_CALLED(Notify_eventAvailable);
    #pragma FUNC_EXT_CALLED(Notify_intLineRegistered);
    #pragma FUNC_EXT_CALLED(Notify_numIntLines);
    #pragma FUNC_EXT_CALLED(Notify_registerEvent);
    #pragma FUNC_EXT_CALLED(Notify_registerEventSingle);
    #pragma FUNC_EXT_CALLED(Notify_restore);
    #pragma FUNC_EXT_CALLED(Notify_sendEvent);
    #pragma FUNC_EXT_CALLED(Notify_sharedMemReq);
    #pragma FUNC_EXT_CALLED(Notify_unregisterEvent);
    #pragma FUNC_EXT_CALLED(Notify_unregisterEventSingle);
#endif

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  A Note about interrupt latency:
 *
 *  Some of the functions below modify the registration of callback functions
 *  (registerEventSingle, unregisterEventSingle, registerEvent, unregisterEvent)
 *  Because the state of event registration is modified in these functions and
 *  the Notify_exec function (run within an ISR context) reads this state, we
 *  have to consider the possibility and outcome of these functions being
 *  interrupted by the Notify_exec function.  In order to ensure the integrity
 *  of the callback registration state during any call to Notify_exec, we
 *  eliminate the possiblity of preemption altogether by adhering to the
 *  following rules:
 *
 *  - If registering a single (or many) callback functions, modify state in the
 *    following order:
 *
 *    1.  Add to the event list (if registerEvent)
 *    2.  Add the callback function (if registerEventSingle for the first time
 *        or if doing a single register)
 *    3.  Finally enable the event in the notify driver, thus opening the gate
 *        for incoming interrupts.
 *
 *    Performing step 3) last during a register is crucial as it ensures that
 *    the remote processor never sends an interrupt that disrupts the operations
 *    performed in/between 1) and 2).
 *
 *  - If unregistering a single (or many) callback functions, perform the
 *    above steps in reverse order.  Doing so ensures that possibility of
 *    getting incoming interrupts is eliminated before local callback
 *    registration state is modified.
 *
 */

/*
 *  ======== Notify_attach ========
 *  Called within Ipc module or directly by the user
 */
Int Notify_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    Int status;

    /* validate remote processor ID */
    if ((remoteProcId >= ti_sdo_utils_MultiProc_numProcessors)
            || (remoteProcId == MultiProc_self())) {

        return (Notify_E_INVALIDARG);
    }

    /* use the NotifySetup proxy to setup drivers */
    status = ti_sdo_ipc_Notify_SetupProxy_attach(remoteProcId, sharedAddr);

    return (status);
}


/*
 *  ======== Notify_disable ========
 */
UInt Notify_disable(UInt16 procId, UInt16 lineId)
{
    UInt key;
    UInt modKey;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    ti_sdo_ipc_Notify_Object *obj;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors &&
            lineId < ti_sdo_ipc_Notify_numLines,
            ti_sdo_ipc_Notify_A_invArgument);

    obj = (ti_sdo_ipc_Notify_Object *)
        Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    /* Nesting value and enable state have to be in sync */
    modKey = Gate_enterModule();

    obj->nesting++;
    if (obj->nesting == 1) {
        /* Disable receiving all events */
        if (procId != MultiProc_self()) {
            INotifyDriver_disable(obj->driverHandle);
        }
    }

    key = obj->nesting;

    Gate_leaveModule(modKey);

    return (key);
}

/*
 *  ======== Notify_disableEvent ========
 */
Void Notify_disableEvent(UInt16 procId, UInt16 lineId, UInt32 eventId)
{
    UInt32 strippedEventId = (eventId & 0xFFFF);
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    ti_sdo_ipc_Notify_Object *obj;
    UInt sysKey;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors && lineId <
            ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    if (procId != MultiProc_self()) {
        /* disable the remote event */
        INotifyDriver_disableEvent(obj->driverHandle, strippedEventId);
    }
    else {
        /* disable the local event */
        sysKey = Hwi_disable();
        CLEAR_BIT(Notify_module->localEnableMask, strippedEventId);
        Hwi_restore(sysKey);
    }
}

/*
 *  ======== Notify_enableEvent ========
 */
Void Notify_enableEvent(UInt16 procId, UInt16 lineId, UInt32 eventId)
{
    UInt32 strippedEventId = (eventId & 0xFFFF);
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    ti_sdo_ipc_Notify_Object *obj;
    UInt sysKey;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors && lineId <
            ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    if (procId != MultiProc_self()) {
        /* enable the remote event */
        INotifyDriver_enableEvent(obj->driverHandle, strippedEventId);
    }
    else {
        /* enable the local event */
        sysKey = Hwi_disable();
        SET_BIT(Notify_module->localEnableMask, strippedEventId);
        Hwi_restore(sysKey);
    }
}

/*
 *  ======== Notify_eventAvailable ========
 */
Bool Notify_eventAvailable(UInt16 procId, UInt16 lineId, UInt32 eventId)
{
    UInt32 strippedEventId = (eventId & 0xFFFF);
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    Bool available;
    ti_sdo_ipc_Notify_Object *obj;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors && lineId <
            ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];
    if (obj == NULL) {
        /* Driver not registered */
        return (FALSE);
    }

    if (!ISRESERVED(eventId)) {
        /* Event is reserved and the caller isn't using Notify_SYSTEMKEY */
        return (FALSE);
    }

    available = (obj->callbacks[strippedEventId].fnNotifyCbck == NULL);

    return (available);
}

/*
 *  ======== Notify_intLineRegistered ========
 */
Bool Notify_intLineRegistered(UInt16 procId, UInt16 lineId)
{
    Bool registered;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors && lineId <
            ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);

    registered = (Notify_module->notifyHandles[clusterId][lineId] != NULL);

    return (registered);
}

/*
 *  ======== Notify_numIntLines ========
 */
UInt16 Notify_numIntLines(UInt16 procId)
{
    UInt16 numIntLines;

    if (MultiProc_self() == procId) {
        /* There is always a single interrupt line to the loopback instance */
        numIntLines = 1;
    }
    else {
        /* Query the NotifySetup module for the device */
        numIntLines = ti_sdo_ipc_Notify_SetupProxy_numIntLines(procId);
    }

    return (numIntLines);
}

/*
 *  ======== Notify_registerEvent ========
 */
Int Notify_registerEvent(UInt16                 procId,
                         UInt16                 lineId,
                         UInt32                 eventId,
                         Notify_FnNotifyCbck    fnNotifyCbck,
                         UArg                   cbckArg)
{
    UInt32               strippedEventId = (eventId & 0xFFFF);
    UInt16 clusterId =   ti_sdo_utils_MultiProc_getClusterId(procId);
    Int                  status;
    ti_sdo_ipc_Notify_Object        *obj;
    UInt                 modKey;
    List_Handle          eventList;
    ti_sdo_ipc_Notify_EventListener *listener;
    Bool                 listWasEmpty;
    Error_Block          eb;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors &&
            lineId < ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    Error_init(&eb);

    modKey = Gate_enterModule();

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    /* Allocate a new EventListener */
    listener = Memory_alloc(ti_sdo_ipc_Notify_Object_heap(),
            sizeof(ti_sdo_ipc_Notify_EventListener), 0, &eb);
    if (listener == NULL) {
        /* Listener memory allocation failed.  Leave module gate & return */
        Gate_leaveModule(modKey);

        return (Notify_E_MEMORY);
    }

    listener->callback.fnNotifyCbck = (Fxn)fnNotifyCbck;
    listener->callback.cbckArg = cbckArg;

    eventList = List_Object_get(obj->eventList, strippedEventId);

    /*
     *  Store whether the list was empty so we know whether to register the
     *  callback
     */
    listWasEmpty = List_empty(eventList);

    /*
     *  Need to atomically add to the list using the system gate because
     *  Notify_exec might preempt List_remove.  List_put is atomic.
     */
    List_put(eventList, (List_Elem *)listener);

    if (listWasEmpty) {
        /*
         *  Registering this event for the first time.  Need to register the
         *  callback function.
         */
        status = Notify_registerEventSingle(procId, lineId, eventId,
            Notify_execMany, (UArg)obj);

        /* Notify_registerEventSingle should always succeed */
        Assert_isTrue(status == Notify_S_SUCCESS,
                ti_sdo_ipc_Notify_A_internal);
    }

    status = Notify_S_SUCCESS;

    Gate_leaveModule(modKey);

    return (status);
}

/*
 *  ======== Notify_registerEventSingle ========
 */
Int Notify_registerEventSingle(UInt16                 procId,
                               UInt16                 lineId,
                               UInt32                 eventId,
                               Notify_FnNotifyCbck    fnNotifyCbck,
                               UArg                   cbckArg)
{
    UInt32        strippedEventId = (eventId & 0xFFFF);
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    UInt          modKey;
    Int           status;
    ti_sdo_ipc_Notify_Object *obj;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors &&
            lineId < ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    modKey = Gate_enterModule();

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    if (obj->callbacks[strippedEventId].fnNotifyCbck) {
        /* A callback is already registered. Fail. */
        status = Notify_E_ALREADYEXISTS;
    }
    else {
        /*
         *  No callback is registered. Register it. There is no need to protect
         *  these modifications because the event isn't registered yet.
         */
        obj->callbacks[strippedEventId].fnNotifyCbck = (Fxn)fnNotifyCbck;
        obj->callbacks[strippedEventId].cbckArg = cbckArg;

        if (procId != MultiProc_self()) {
            /* Tell the remote notify driver that the event is now registered */
            INotifyDriver_registerEvent(obj->driverHandle, strippedEventId);
        }

        status = Notify_S_SUCCESS;
    }

    Gate_leaveModule(modKey);

    return (status);
}

/*
 *  ======== Notify_restore ========
 */
Void Notify_restore(UInt16 procId, UInt16 lineId, UInt key)
{
    UInt modKey;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    ti_sdo_ipc_Notify_Object *obj;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors &&
            lineId < ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);
    Assert_isTrue(key == obj->nesting, ti_sdo_ipc_Notify_A_outOfOrderNesting);

    /* Nesting value and enable state have to be in sync */
    modKey = Gate_enterModule();

    obj->nesting--;
    if (obj->nesting == 0) {
        /* Enable receiving events */
        if (procId != MultiProc_self()) {
            INotifyDriver_enable(obj->driverHandle);
        }
    }

    Gate_leaveModule(modKey);
}

/*
 *  ======== Notify_sendEvent ========
 */
Int Notify_sendEvent(UInt16   procId,
                     UInt16   lineId,
                     UInt32   eventId,
                     UInt32   payload,
                     Bool     waitClear)
{
    UInt32        strippedEventId = (eventId & 0xFFFF);
    UInt16        clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    Int           status;
    ti_sdo_ipc_Notify_Object *obj;
    UInt          sysKey;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors &&
            lineId < ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    if (procId != MultiProc_self()) {
        /* Send a remote event */
        status = INotifyDriver_sendEvent(obj->driverHandle,
                                         strippedEventId,
                                         payload, waitClear);
    }
    else {
        /*
         *  The check agaist non-NULL fnNotifyCbCk must be atomic with
         *  Notify_exec so Notify_exec doesn't encounter a null callback.
         */
        sysKey = Hwi_disable();

        /*
         *  If nesting == 0 (the driver is enabled) and the event is enabled,
         *  send the event
         */
        if (obj->callbacks[strippedEventId].fnNotifyCbck == NULL) {
            /* No callbacks are registered locally for the event. */
            status = Notify_E_EVTNOTREGISTERED;
        }
        else if (obj->nesting != 0) {
            /* Driver is disabled */
            status = Notify_E_FAIL;
        }
        else if (!TEST_BIT (Notify_module->localEnableMask, strippedEventId)){
            /* Event is disabled */
            status = Notify_E_EVTDISABLED;
        }
        else {
            /* Execute the callback function registered to the event */
            ti_sdo_ipc_Notify_exec(obj, strippedEventId, payload);

            status = Notify_S_SUCCESS;
        }

        Hwi_restore(sysKey);
    }

    return (status);
}

/*
 *  ======== Notify_sharedMemReq ========
 */
SizeT Notify_sharedMemReq(UInt16 procId, Ptr sharedAddr)
{
    SizeT memReq;

    if (procId == MultiProc_self()) {
        return (0);
    }

    /* Determine device-specific shared memory requirements */
    memReq = ti_sdo_ipc_Notify_SetupProxy_sharedMemReq(procId, sharedAddr);

    return (memReq);
}

/*
 *  ======== Notify_unregisterEventSingle ========
 */
Int Notify_unregisterEventSingle(UInt16 procId, UInt16 lineId, UInt32 eventId)
{
    UInt32  strippedEventId = (eventId & 0xFFFF);
    UInt16  clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    Int     status;
    ti_sdo_ipc_Notify_Object *obj;
    UInt    modKey;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors &&
            lineId < ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    modKey = Gate_enterModule();

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    if (obj->callbacks[strippedEventId].fnNotifyCbck) {
        if (procId != MultiProc_self()) {
            /*
             *  First, Tell the remote notify driver that the event is now
             *  unregistered
             */
            INotifyDriver_unregisterEvent(obj->driverHandle,
                                          strippedEventId);
        }

        /*
         *  No need to protect these modifications with the system gate because
         *  we shouldn't get preempted by Notify_exec after INotifyDriver_
         *  unregisterEvent.
         */
        obj->callbacks[strippedEventId].fnNotifyCbck = NULL;
        obj->callbacks[strippedEventId].cbckArg = 0;

        status = Notify_S_SUCCESS;
    }
    else {
        /* No callback is registered. Fail. */
        status = Notify_E_FAIL;
    }

    Gate_leaveModule(modKey);

    return (status);
}

/*
 *  ======== Notify_unregisterEvent ========
 */
Int Notify_unregisterEvent(UInt16                 procId,
                           UInt16                 lineId,
                           UInt32                 eventId,
                           Notify_FnNotifyCbck    fnNotifyCbck,
                           UArg                   cbckArg)
{
    UInt32  strippedEventId = (eventId & 0xFFFF);
    UInt16  clusterId = ti_sdo_utils_MultiProc_getClusterId(procId);
    Int     status;
    UInt    sysKey, modKey;
    ti_sdo_ipc_Notify_Object *obj;
    List_Handle eventList;
    ti_sdo_ipc_Notify_EventListener *listener;
    UInt    count = 0;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors && lineId <
            ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(strippedEventId < ti_sdo_ipc_Notify_numEvents,
            ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(ISRESERVED(eventId), ti_sdo_ipc_Notify_A_reservedEvent);

    modKey = Gate_enterModule();

    obj = (ti_sdo_ipc_Notify_Object *)
            Notify_module->notifyHandles[clusterId][lineId];

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Notify_A_notRegistered);

    eventList = List_Object_get(obj->eventList, strippedEventId);

    if (List_empty(eventList)) {
        return (Notify_E_NOTFOUND);
    }

    /* Get the first listener on the list */
    listener = (ti_sdo_ipc_Notify_EventListener *)List_next(eventList, NULL);

    while (listener != NULL) {
        count++;
        if (listener->callback.fnNotifyCbck == (Fxn)fnNotifyCbck &&
                listener->callback.cbckArg == cbckArg ) {
            break;      /* found a match! */
        }
        listener = (ti_sdo_ipc_Notify_EventListener *)
            List_next(eventList, (List_Elem *)listener);
    }

    if (listener == NULL) {
        /* Event listener not found */
        status = Notify_E_NOTFOUND;
    }
    else {
        if (count == 1 && List_next(eventList, (List_Elem *)listener) == NULL) {
            /*
             *  If only one element counted so far and the List_next returns
             *  NULL, the list will be empty after unregistering.  Therefore,
             *  unregister the callback function.
             */
            status = Notify_unregisterEventSingle(procId, lineId, eventId);
            /* unregisterEvent should always suceed */
            Assert_isTrue(status == Notify_S_SUCCESS,
                    ti_sdo_ipc_Notify_A_internal);

            /*  No need to protect the list removal: the event's unregistered */
            List_remove(eventList, (List_Elem *)listener);
        }
        else {
            /*
             *  Need to atomically remove from the list using the system gate
             *  because Notify_exec might preempt List_remove (the event is
             *  still registered)
             */
            sysKey = Hwi_disable();
            List_remove(eventList, (List_Elem *)listener);
            Hwi_restore(sysKey);
        }

        /* Free the memory alloc'ed for the event listener */
        Memory_free(ti_sdo_ipc_Notify_Object_heap(), listener,
            sizeof(ti_sdo_ipc_Notify_EventListener));

        status = Notify_S_SUCCESS;
    }

    Gate_leaveModule(modKey);

    return (status);
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_Notify_Module_startup ========
 */
Int ti_sdo_ipc_Notify_Module_startup(Int phase)
{
    UInt16 procId = MultiProc_self();

    /*
     *  Wait for Startup to be done (if MultiProc id not yet set) because a
     *  user fxn may set it
     */
    if (!Startup_Module_startupDone() && procId == MultiProc_INVALIDID) {
        return (Startup_NOTDONE);
    }

    /* Ensure that the MultiProc ID has been configured */
    Assert_isTrue(procId != MultiProc_INVALIDID,
            ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    /* Create a local instance */
    ti_sdo_ipc_Notify_create(NULL, procId, 0, NULL, NULL);

    return (Startup_DONE);
}

/*
 *************************************************************************
 *                      Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_Notify_Instance_init ========
 */
Int ti_sdo_ipc_Notify_Instance_init(
        ti_sdo_ipc_Notify_Object *obj,
        INotifyDriver_Handle driverHandle,
        UInt16 remoteProcId, UInt16 lineId,
        const ti_sdo_ipc_Notify_Params *params,
        Error_Block *eb)
{
    UInt        i;
    UInt16      clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    List_Handle eventList;

    Assert_isTrue(remoteProcId < ti_sdo_utils_MultiProc_numProcessors &&
                  lineId < ti_sdo_ipc_Notify_numLines, ti_sdo_ipc_Notify_A_invArgument);
    Assert_isTrue(Notify_module->notifyHandles[clusterId][lineId] == NULL,
                  ti_sdo_ipc_Notify_A_alreadyRegistered);

    obj->remoteProcId = remoteProcId;
    obj->lineId = lineId;
    obj->nesting = 0;

    /* Allocate and initialize (to 0 with calloc()) the callbacks array. */
    obj->callbacks = Memory_calloc(ti_sdo_ipc_Notify_Object_heap(),
            (sizeof(ti_sdo_ipc_Notify_EventCallback) *
            ti_sdo_ipc_Notify_numEvents), 0, eb);
    if (obj->callbacks == NULL) {
        return (2);
    }

    obj->eventList = Memory_alloc(ti_sdo_ipc_Notify_Object_heap(),
        sizeof(List_Struct) * ti_sdo_ipc_Notify_numEvents, 0, eb);
    if (obj->eventList == NULL) {
        return (1);
    }

    for (i = 0; i < ti_sdo_ipc_Notify_numEvents; i++) {
        eventList = List_Object_get(obj->eventList, i);

        /* Pass in NULL for eb since construct should never fail */
        List_construct(List_struct(eventList), NULL);
    }

    /* Used solely for remote driver (NULL if remoteProcId == self) */
    obj->driverHandle = driverHandle;

    if (driverHandle != NULL) {
        /* Send this handle to the INotifyDriver */
        INotifyDriver_setNotifyHandle(driverHandle, obj);
    }

    Notify_module->notifyHandles[clusterId][lineId] = obj;

    return (0);
}

/*
 *  ======== ti_sdo_ipc_Notify_Instance_finalize ========
 */
Void ti_sdo_ipc_Notify_Instance_finalize(ti_sdo_ipc_Notify_Object *obj,
        Int status)
{
    UInt    i;
    UInt16  clusterId = ti_sdo_utils_MultiProc_getClusterId(obj->remoteProcId);

    switch (status) {
        case 0:
            /* Unregister the notify instance from the Notify module */
            Notify_module->notifyHandles[clusterId][obj->lineId] = NULL;

            /* Destruct the event lists */
            for (i = 0; i < ti_sdo_ipc_Notify_numEvents; i++) {
                List_destruct(List_struct(List_Object_get(obj->eventList, i)));
            }

            /* Free memory used for the List.Objects */
            Memory_free(ti_sdo_ipc_Notify_Object_heap(), obj->eventList,
                    sizeof(List_Struct) * ti_sdo_ipc_Notify_numEvents);

            /* OK to fall through */

        case 1:
            /* Free memory used for callbacks array */
            Memory_free(ti_sdo_ipc_Notify_Object_heap(), obj->callbacks,
                    sizeof(ti_sdo_ipc_Notify_EventCallback) *
                    ti_sdo_ipc_Notify_numEvents);
    }
}

/*
 *  ======== ti_sdo_ipc_Notify_detach ========
 *  Called within Ipc module
 */
Int ti_sdo_ipc_Notify_detach(UInt16 remoteProcId)
{
    ti_sdo_ipc_Notify_Object *obj;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    INotifyDriver_Handle driverHandle;
    UInt i;

    for (i = 0; i < ti_sdo_ipc_Notify_numLines; i++) {
        obj = (ti_sdo_ipc_Notify_Object *)
                Notify_module->notifyHandles[clusterId][i];

        /* Ensure that notify is actually registered for the procId + lineId */
        if (obj != NULL) {
            driverHandle = obj->driverHandle;

            /* First, unregister the driver since it was registered last */
            ti_sdo_ipc_Notify_delete(&obj);

            /* Second, delete the driver itself */
            INotifyDriver_delete(&driverHandle);
        }

    }

    /* Notify_detech never fails on RTOS */
    return (Notify_S_SUCCESS);
}


/*
 *  ======== ti_sdo_ipc_Notify_exec ========
 */
Void ti_sdo_ipc_Notify_exec(ti_sdo_ipc_Notify_Object *obj, UInt32 eventId,
        UInt32 payload)
{
    ti_sdo_ipc_Notify_EventCallback *callback;

    callback = &(obj->callbacks[eventId]);

    /* Make sure the callback function is not null */
    Assert_isTrue(callback->fnNotifyCbck != NULL,
            ti_sdo_ipc_Notify_A_internal);

    /* Execute the callback function with its argument and the payload */
    callback->fnNotifyCbck(obj->remoteProcId, obj->lineId, eventId,
        callback->cbckArg, payload);
}


/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_Notify_execMany ========
 */
Void ti_sdo_ipc_Notify_execMany(UInt16 procId, UInt16 lineId, UInt32 eventId,
        UArg arg, UInt32 payload)
{
    ti_sdo_ipc_Notify_Object *obj = (ti_sdo_ipc_Notify_Object *)arg;
    List_Handle eventList;
    ti_sdo_ipc_Notify_EventListener *listener;

    /* Both loopback and the the event itself are enabled */
    eventList = List_Object_get(obj->eventList, eventId);

    /* Use "NULL" to get the first EventListener on the list */
    listener = (ti_sdo_ipc_Notify_EventListener *)List_next(eventList, NULL);
    while (listener != NULL) {
        /* Execute the callback function */
        listener->callback.fnNotifyCbck(procId, lineId,
            eventId, listener->callback.cbckArg, payload);

        listener = (ti_sdo_ipc_Notify_EventListener *)List_next(eventList,
             (List_Elem *)listener);
    }
}

/*
 *                      Added procId/lineId Asserts to [un]registerEvent[Single]
 *! 24-Mar-2010 skp     Fix SDOCM00068331 (sendEvent shouldn't enter mod gate)
 *! 04-Mar-2010 skp     Fix SDOCM00067532 (added Notify_eventAvailable)
 *! 19-Feb-2010 skp     Added FUNC_EXT_CALLED #pragma's
 *! 21-Jan-2010 skp     Fix SDOCM00066064 (misc notify bugs)
 *! 01-Dec-2009 skp     Loopback instance created in Module_startup
 *! 19-Nov-2009 skp     fixed high interrupt latency issues
 */
