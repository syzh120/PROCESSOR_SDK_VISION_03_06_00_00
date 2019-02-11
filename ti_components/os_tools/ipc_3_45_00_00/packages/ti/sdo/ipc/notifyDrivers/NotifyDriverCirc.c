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
 *  ======== NotifyDriverCirc.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Timestamp.h>

#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/hal/Cache.h>

#include <ti/sdo/ipc/interfaces/INotifyDriver.h>

#include "package/internal/NotifyDriverCirc.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/utils/_MultiProc.h>

/* Bit mask operations */
#define SET_BIT(num,pos)            ((num) |= (1u << (pos)))
#define CLEAR_BIT(num,pos)          ((num) &= ~(1u << (pos)))
#define TEST_BIT(num,pos)           ((num) & (1u << (pos)))


/*
 **************************************************************
 *                       Instance functions
 **************************************************************
 */

/*
 *  ======== NotifyDriverCirc_Instance_init ========
 */
Void NotifyDriverCirc_Instance_init(NotifyDriverCirc_Object *obj,
                                  const NotifyDriverCirc_Params *params)
{
    UInt16 regionId;
    UInt16 localIndex, remoteIndex;
    SizeT  regionCacheSize, minAlign;
    SizeT  ctrlSize, circBufSize, totalSelfSize;

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

    /*
     *  Store all interrupt information so it may be used (if neccessary) by
     *  the IInterrupt delegates
     */
    obj->intInfo.remoteIntId = params->remoteIntId;
    obj->intInfo.localIntId  = params->localIntId;
    obj->intInfo.intVectorId = params->intVectorId;

    /* determine which slot to use */
    if (params->remoteProcId > MultiProc_self()) {
        localIndex  = 0;
        remoteIndex = 1;
    }
    else {
        localIndex  = 1;
        remoteIndex = 0;
    }

    /* set the remote processor's id */
    obj->remoteProcId = params->remoteProcId;

    /* counters for capturing spin wait statistics */
    obj->spinCount = 0;
    obj->spinWaitTime = 0;

    /* calculate the circular buffer size one-way */
    circBufSize = _Ipc_roundup(
        sizeof(NotifyDriverCirc_EventEntry) * NotifyDriverCirc_numMsgs,
               minAlign);

    /* calculate the control size one-way */
    ctrlSize = _Ipc_roundup(sizeof(Bits32), minAlign);

    /* calculate the total size one-way */
    totalSelfSize =  circBufSize + (2 * ctrlSize);

    /*
     *  Init put/get buffer and index pointers.
     *  These are all on different cache lines.
     */
    obj->putBuffer = (NotifyDriverCirc_EventEntry *)
        ((UInt32)params->sharedAddr + (localIndex * totalSelfSize));

    obj->putWriteIndex = (Bits32 *)((UInt32)obj->putBuffer + circBufSize);

    obj->putReadIndex = (Bits32 *)((UInt32)obj->putWriteIndex + ctrlSize);

    obj->getBuffer = (NotifyDriverCirc_EventEntry *)
        ((UInt32)params->sharedAddr + (remoteIndex * totalSelfSize));

    obj->getWriteIndex = (Bits32 *)((UInt32)obj->getBuffer + circBufSize);

    obj->getReadIndex = (Bits32 *)((UInt32)obj->getWriteIndex + ctrlSize);

    /*
     *  Calculate the size for cache wb/inv in sendEvent and isr.
     *  This size is the circular buffer + putWriteIndex.
     *  [sizeof(EventEntry) * numMsgs] + [the sizeof(Ptr)]
     *  aligned to a cache line.
     */
    obj->opCacheSize = ((UInt32)obj->putReadIndex - (UInt32)obj->putBuffer);

    /* init the putWrite and putRead Index to 0 */
    obj->putWriteIndex[0] = 0;
    obj->putReadIndex[0] = 0;

    /* cache wb the putWrite/Read Index but no need to inv them */
    if (obj->cacheEnabled) {
        Cache_wb(obj->putWriteIndex,
                 sizeof(Bits32),
                 Cache_Type_ALL, TRUE);

        Cache_wb(obj->putReadIndex,
                 sizeof(Bits32),
                 Cache_Type_ALL, TRUE);

        /* invalidate any stale data of the get buffer and indexes */
        Cache_inv(obj->getBuffer,
                  totalSelfSize,
                  Cache_Type_ALL, TRUE);
    }

    /* Register the incoming interrupt */
    NotifyDriverCirc_InterruptProxy_intRegister(obj->remoteProcId,
        &(obj->intInfo), (Fxn)NotifyDriverCirc_isr, (UArg)obj);
}

/*
 *  ======== NotifyDriverCirc_Instance_finalize ========
 */
Void NotifyDriverCirc_Instance_finalize(NotifyDriverCirc_Object *obj)
{
    SizeT  sizeToInv;

    /* Unregister interrupt */
    NotifyDriverCirc_InterruptProxy_intUnregister(obj->remoteProcId,
        &(obj->intInfo));

    /* cache inv the shared memory that is used for instance */
    if (obj->cacheEnabled) {
        if (obj->remoteProcId > MultiProc_self()) {
            /* calculate the size of the buffer and indexes for one side */
            sizeToInv = ((UInt32)obj->getBuffer - (UInt32)obj->putBuffer);

            /* invalidate the shared memory for this instance */
            Cache_inv(obj->putBuffer,
                     (sizeToInv * 2),
                      Cache_Type_ALL, TRUE);
        }
        else {
            /* calculate the size of the buffer and indexes for one side */
            sizeToInv = ((UInt32)obj->putBuffer - (UInt32)obj->getBuffer);

            /* invalidate the shared memory for this instance */
            Cache_inv(obj->getBuffer,
                     (sizeToInv * 2),
                      Cache_Type_ALL, TRUE);
        }
    }
}

/*
 *  ======== NotifyDriverCirc_registerEvent ========
 */
Void NotifyDriverCirc_registerEvent(NotifyDriverCirc_Object *obj,
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
 *  ======== NotifyDriverCirc_unregisterEvent ========
 */
Void NotifyDriverCirc_unregisterEvent(NotifyDriverCirc_Object *obj,
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
 *  ======== NotifyDriverCirc_sendEvent ========
 */
Int NotifyDriverCirc_sendEvent(NotifyDriverCirc_Object *obj,
                              UInt32                 eventId,
                              UInt32                 payload,
                              Bool                   waitClear)
{
    Bool loop = FALSE;
    Bool spinWait = FALSE;
    UInt hwiKey;
    UInt32 startWaitTime, spinWaitTime;
    UInt32 writeIndex, readIndex;
    NotifyDriverCirc_EventEntry *eventEntry;

    /*
     *  Retrieve the get Index. No need to cache inv the
     *  readIndex until out writeIndex wraps. Only need to invalidate
     *  once every N times [N = number of slots in buffer].
     */
    readIndex = obj->putReadIndex[0];

    do {
        /* disable interrupts */
        hwiKey = Hwi_disable();

        /* retrieve the put index */
        writeIndex = obj->putWriteIndex[0];

        /* if slot available 'break' out of loop */
        if (((writeIndex + 1) & NotifyDriverCirc_maxIndex) != readIndex) {
            break;
        }

        /* restore interrupts */
        Hwi_restore(hwiKey);

        /* check to make sure code has looped */
        if (loop && !waitClear) {
            /* if no slot available and waitClear is 'FALSE' */
            return (Notify_E_FAIL);
        }

        /* start timestamp for spin wait statistics */
        if (NotifyDriverCirc_enableStats) {
            if (loop && !spinWait) {
                startWaitTime = Timestamp_get32();
                spinWait = TRUE;
            }
        }

        /* cache invalidate the putReadIndex */
        if (obj->cacheEnabled) {
            Cache_inv(obj->putReadIndex,
                      sizeof(Bits32),
                      Cache_Type_ALL,
                      TRUE);
        }

        /* re-read the get count */
        readIndex = obj->putReadIndex[0];

        /* convey that the code has looped around */
        loop = TRUE;
    } while (1);

    /* interrupts are disabled at this point */

    /* increment spinCount and determine the spin wait time */
    if (NotifyDriverCirc_enableStats) {
        if (spinWait) {
            obj->spinCount++;
            spinWaitTime = Timestamp_get32() - startWaitTime;
            if (spinWaitTime > obj->spinWaitTime) {
                obj->spinWaitTime = spinWaitTime;
            }
        }
    }

    /* calculate the next available entry */
    eventEntry = (NotifyDriverCirc_EventEntry *)((UInt32)obj->putBuffer +
                 (writeIndex * sizeof(NotifyDriverCirc_EventEntry)));

    /* Set the eventId field and payload for the entry */
    eventEntry->eventid = eventId;
    eventEntry->payload = payload;

    /*
     *  Writeback the event entry. No need to invalidate since
     *  only one processor ever writes here. No need to wait for
     *  cache operation since another cache operation is done below.
     */
    if (obj->cacheEnabled) {
        Cache_wb(eventEntry,
                 sizeof(NotifyDriverCirc_EventEntry),
                 Cache_Type_ALL,
                 FALSE);
    }

    /* update the putWriteIndex */
    obj->putWriteIndex[0] = (writeIndex + 1) & NotifyDriverCirc_maxIndex;

    /* restore interrupts */
    Hwi_restore(hwiKey);

    /*
     *  Writeback the putWriteIndex.
     *  No need to invalidate since only one processor
     *  ever writes here.
     */
    if (obj->cacheEnabled) {
        Cache_wb(obj->putWriteIndex,
                 sizeof(Bits32),
                 Cache_Type_ALL,
                 TRUE);
    }

    /* Send an interrupt to the Remote Processor */
    NotifyDriverCirc_InterruptProxy_intSend(obj->remoteProcId, &(obj->intInfo),
                                            eventId);

    return (Notify_S_SUCCESS);
}

/*
 *  ======== NotifyDriverCirc_disable ========
 */
Void NotifyDriverCirc_disable(NotifyDriverCirc_Object *obj)
{
    /* Disable the incoming interrupt line */
    NotifyDriverCirc_InterruptProxy_intDisable(obj->remoteProcId,
                                              &(obj->intInfo));
}

/*
 *  ======== NotifyDriverCirc_enable ========
 */
Void NotifyDriverCirc_enable(NotifyDriverCirc_Object *obj)
{
    /* NotifyDriverCirc_enableEvent not supported by this driver */
    Assert_isTrue(FALSE, NotifyDriverCirc_A_notSupported);
}

/*
 *  ======== NotifyDriverCirc_disableEvent ========
 */
Void NotifyDriverCirc_disableEvent(NotifyDriverCirc_Object *obj, UInt32 eventId)
{
    /* NotifyDriverCirc_disableEvent not supported by this driver */
    Assert_isTrue(FALSE, NotifyDriverCirc_A_notSupported);
}

/*
 *  ======== NotifyDriverCirc_enableEvent ========
 */
Void NotifyDriverCirc_enableEvent(NotifyDriverCirc_Object *obj, UInt32 eventId)
{
    /* Enable the incoming interrupt line */
    NotifyDriverCirc_InterruptProxy_intEnable(obj->remoteProcId,
                                             &(obj->intInfo));
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverCirc_sharedMemReq ========
 */
SizeT NotifyDriverCirc_sharedMemReq(const NotifyDriverCirc_Params *params)
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

    /*
     *  Amount of shared memory:
     *  1 putBuffer with numMsgs (rounded to CLS) +
     *  1 putWriteIndex ptr (rounded to CLS) +
     *  1 putReadIndex put (rounded to CLS) +
     *  1 getBuffer with numMsgs (rounded to CLS) +
     *  1 getWriteIndex ptr (rounded to CLS) +
     *  1 getReadIndex put (rounded to CLS) +
     *
     *  For CLS of 128b it is:
     *      256b + 128b + 128b + 256b+ 128b + 128b = 1KB
     *
     *  Note: CLS means Cache Line Size
     */
    memReq = 2 *
        ((_Ipc_roundup(sizeof(NotifyDriverCirc_EventEntry) *
                       NotifyDriverCirc_numMsgs, minAlign))
        + ( 2 * _Ipc_roundup(sizeof(Bits32), minAlign)));

    return (memReq);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== NotifyDriverCirc_isr ========
 */
Void NotifyDriverCirc_isr(UArg arg)
{
    NotifyDriverCirc_EventEntry *eventEntry;
    NotifyDriverCirc_Object     *obj;
    UInt32 writeIndex, readIndex;

    obj = (NotifyDriverCirc_Object *)arg;

    /* Make sure the NotifyDriverCirc_Object is not NULL */
    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_internal);

    /*
     *  Invalidate both getBuffer getWriteIndex from cache.
     *  Do the Cache_wait() below.
     */
    if (obj->cacheEnabled) {
        Cache_inv(obj->getBuffer,
                  obj->opCacheSize,
                  Cache_Type_ALL,
                  FALSE);
        /* Reading new data instead of pulling old data from cache */
        Cache_inv(obj->getWriteIndex,
                  sizeof(obj->getWriteIndex),
                  Cache_Type_ALL,
                  FALSE);
    }

    /* Clear the remote interrupt */
    NotifyDriverCirc_InterruptProxy_intClear(obj->remoteProcId,
                                            &(obj->intInfo));

    /* wait here to make sure inv is completely done */
    if (obj->cacheEnabled) {
        Cache_wait();
    }

    /* get the writeIndex and readIndex */
    writeIndex = obj->getWriteIndex[0];
    readIndex = obj->getReadIndex[0];

    /* get the event */
    eventEntry = &(obj->getBuffer[readIndex]);

    /* if writeIndex != readIndex then there is an event to process */
    while (writeIndex != readIndex) {
        /*
         *  Check to make sure event is registered. If the event
         *  is not registered, the event is not processed and is lost.
         */
        if (TEST_BIT(obj->evtRegMask, eventEntry->eventid)) {
            /* Execute the callback function */
            ti_sdo_ipc_Notify_exec(obj->notifyHandle,
                                   eventEntry->eventid,
                                   eventEntry->payload);
        }

        /* update the readIndex. */
        readIndex = ((readIndex + 1) & NotifyDriverCirc_maxIndex);

        /* set the getReadIndex */
        obj->getReadIndex[0] = readIndex;

        /*
         *  Write back the getReadIndex once every N / 4 messages.
         *  No need to invalidate since only one processor ever
         *  writes this. No need to wait for operation to complete
         *  since remote core updates its readIndex at least once
         *  every N messages and the remote core will not use a slot
         *  until it sees that the event has been processed with this
         *  cache wb.
         */
        if ((obj->cacheEnabled) &&
            ((readIndex % NotifyDriverCirc_modIndex) == 0)) {
            Cache_wb(obj->getReadIndex,
                     sizeof(Bits32),
                     Cache_Type_ALL,
                     FALSE);
        }

        /* get the next event */
        eventEntry = &(obj->getBuffer[readIndex]);
    }
}

/*
 *  ======== NotifyDriverCirc_setNotifyHandle ========
 */
Void NotifyDriverCirc_setNotifyHandle(NotifyDriverCirc_Object *obj,
                                     Ptr notifyHandle)
{
    /* Internally used, so no Assert needed */
    obj->notifyHandle = (ti_sdo_ipc_Notify_Handle)notifyHandle;
}
