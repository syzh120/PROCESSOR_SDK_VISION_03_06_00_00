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
 *  ======== TransportShmCirc.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>

#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Swi.h>

#include <ti/sdo/ipc/interfaces/INotifyDriver.h>

#include "package/internal/TransportShmCirc.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_MessageQ.h>

/* Bit mask operations */
#define SET_BIT(num,pos)            ((num) |= (1u << (pos)))
#define CLEAR_BIT(num,pos)          ((num) &= ~(1u << (pos)))
#define TEST_BIT(num,pos)           ((num) & (1u << (pos)))

/* Need to use reserved notify events */
#undef TransportShmCirc_notifyEventId
#define TransportShmCirc_notifyEventId \
        ti_sdo_ipc_transports_TransportShmCirc_notifyEventId + \
                    (UInt32)((UInt32)Notify_SYSTEMKEY << 16)

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== TransportShmCirc_Instance_init ========
 */
Int TransportShmCirc_Instance_init(TransportShmCirc_Object *obj,
        UInt16 remoteProcId, const TransportShmCirc_Params *params,
        Error_Block *eb)
{
    Int         localIndex;
    Int         remoteIndex;
    UInt32      minAlign;
    Int         status;
    Bool        flag;
    Swi_Handle  swiHandle;
    Swi_Params  swiParams;
    SizeT       ctrlSize, circBufSize, totalSelfSize;

    swiHandle = TransportShmCirc_Instance_State_swiObj(obj);

    /* determine which slot to use */
    if (MultiProc_self() < remoteProcId) {
        localIndex  = 0;
        remoteIndex = 1;
    }
    else {
        localIndex  = 1;
        remoteIndex = 0;
    }

    /* Creating using sharedAddr */
    obj->regionId = SharedRegion_getId(params->sharedAddr);

    /* determine the minimum alignment */
    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(obj->regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(obj->regionId);
    }

    /* Assert that the buffer is in a valid shared region */
    Assert_isTrue(obj->regionId != SharedRegion_INVALIDREGIONID,
        ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

    /* Assert that sharedAddr is cache aligned */
    Assert_isTrue(((UInt32)params->sharedAddr % minAlign == 0),
        ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

    /* set object fields */
    obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
    obj->objType      = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
    obj->priority     = params->priority;
    obj->remoteProcId = remoteProcId;

    /* calculate the circular buffer size one-way */
    circBufSize =
        _Ipc_roundup(sizeof(Bits32) * TransportShmCirc_numMsgs, minAlign);

    /* calculate the control size one-way */
    ctrlSize = _Ipc_roundup(sizeof(Bits32), minAlign);

    /* calculate the total size one-way */
    totalSelfSize =  circBufSize + (2 * ctrlSize);

    /*
     *  Init put/get buffer and index pointers.
     *  These are all on different cache lines.
     */
    obj->putBuffer =
        (Ptr)((UInt32)params->sharedAddr + (localIndex * totalSelfSize));

    obj->putWriteIndex = (Bits32 *)((UInt32)obj->putBuffer + circBufSize);

    obj->putReadIndex = (Bits32 *)((UInt32)obj->putWriteIndex + ctrlSize);

    obj->getBuffer =
        (Ptr)((UInt32)params->sharedAddr + (remoteIndex * totalSelfSize));

    obj->getWriteIndex = (Bits32 *)((UInt32)obj->getBuffer + circBufSize);

    obj->getReadIndex = (Bits32 *)((UInt32)obj->getWriteIndex + ctrlSize);

    /*
     *  Calculate the size for cache inv in isr.
     *  This size is the circular buffer + putWriteIndex.
     *  [sizeof(Ptr) * numMsgs] + [the sizeof(Ptr)]
     *  aligned to a cache line.
     */
    obj->opCacheSize = ((UInt32)obj->putReadIndex - (UInt32)obj->putBuffer);

    /* construct the Swi */
    Swi_Params_init(&swiParams);
    swiParams.arg0 = (UArg)obj;
    Swi_construct(Swi_struct(swiHandle),
                 (Swi_FuncPtr)TransportShmCirc_swiFxn,
                 &swiParams, eb);

    /* register the event with Notify */
    status = Notify_registerEventSingle(
                 remoteProcId,    /* remoteProcId */
                 0,               /* lineId */
                 TransportShmCirc_notifyEventId,
                 (Notify_FnNotifyCbck)TransportShmCirc_notifyFxn,
                 (UArg)swiHandle);

    if (status < 0) {
        Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
        return (1);
    }

    /* Register the transport with MessageQ */
    flag = ti_sdo_ipc_MessageQ_registerTransport(
        TransportShmCirc_Handle_upCast(obj), remoteProcId, params->priority);

    if (flag == FALSE) {
        Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
        return (2);
    }

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
    }

    return (0);
}

/*
 *  ======== TransportShmCirc_Instance_finalize ========
 */
Void TransportShmCirc_Instance_finalize(TransportShmCirc_Object *obj, Int status)
{
    switch(status) {
        case 0: /* MessageQ_registerTransport succeeded */
            ti_sdo_ipc_MessageQ_unregisterTransport(obj->remoteProcId,
                obj->priority);

            /* fall thru OK */
        case 1: /* Notify_registerEventSingle failed */
        case 2: /* MessageQ_registerTransport failed */
            Notify_unregisterEventSingle(
                obj->remoteProcId,
                0,
                TransportShmCirc_notifyEventId);
            break;
    }
}

/*
 *  ======== TransportShmCirc_put ========
 */
Bool TransportShmCirc_put(TransportShmCirc_Object *obj, Ptr msg)
{
    Int status;
    UInt hwiKey;
    SharedRegion_SRPtr msgSRPtr;
    UInt32 *eventEntry;
    UInt32 writeIndex, readIndex;
    Bool loop       = FALSE;
    UInt16 regionId = SharedRegion_INVALIDREGIONID;

    /*
     *  If translation is disabled and we always have to write back the
     *  message then we can avoid calling SharedRegion_getId(). The wait
     *  flag is "FALSE" here because we do other cache calls below.
     */
    if (ti_sdo_ipc_SharedRegion_translate ||
        !TransportShmCirc_alwaysWriteBackMsg ) {
        regionId = SharedRegion_getId(msg);
        if (SharedRegion_isCacheEnabled(regionId)) {
            Cache_wbInv(msg, ((MessageQ_Msg)(msg))->msgSize, Cache_Type_ALL,
                        FALSE);
        }
    }
    else {
        Cache_wbInv(msg, ((MessageQ_Msg)(msg))->msgSize, Cache_Type_ALL, FALSE);
    }

    /*
     *  Get the msg's SRPtr.  OK if (regionId == SharedRegion_INVALIDID &&
     *  SharedRegion_translate == FALSE)
     */
    msgSRPtr = SharedRegion_getSRPtr(msg, regionId);

    /*
     *  Retrieve the get Index. No need to cache inv the
     *  readIndex until the writeIndex wraps. Only need to invalidate
     *  once every N times [N = number of messages].
     */
    readIndex = obj->putReadIndex[0];

    do {
        /* disable interrupts */
        hwiKey = Hwi_disable();

        /* retrieve the put index */
        writeIndex = obj->putWriteIndex[0];

        /* if slot available 'break' out of loop */
        if (((writeIndex + 1) & TransportShmCirc_maxIndex) != readIndex) {
            break;
        }

        /* restore interrupts */
        Hwi_restore(hwiKey);

        /* check to make sure code has looped */
        if (loop) {
            /* if no slot available */
            return (FALSE);
        }

        /* cache invalidate the putReadIndex */
        if (obj->cacheEnabled) {
            Cache_inv(obj->putReadIndex,
                      sizeof(Bits32),
                      Cache_Type_ALL,
                      TRUE);
        }

        /* re-read the putReadIndex */
        readIndex = obj->putReadIndex[0];

        /* convey that the code has looped around */
        loop = TRUE;
    } while (1);

    /* interrupts are disabled at this point */

    /* calculate the next available entry */
    eventEntry = (UInt32 *)(
        (UInt32)obj->putBuffer + (writeIndex * sizeof(Ptr)));

    /* Set the eventId field and payload for the entry */
    eventEntry[0] = msgSRPtr;

    /*
     *  Writeback the event entry. No need to invalidate since
     *  only one processor ever writes here. No need to wait for
     *  cache operation since another cache operation is done below.
     */
    if (obj->cacheEnabled) {
        Cache_wb(eventEntry,
                 sizeof(Ptr),
                 Cache_Type_ALL,
                 FALSE);
    }

    /* update the putWriteIndex */
    obj->putWriteIndex[0] = (writeIndex + 1) & TransportShmCirc_maxIndex;

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

    /* Notify the remote processor */
    status = Notify_sendEvent(
                 obj->remoteProcId,
                 0,
                 TransportShmCirc_notifyEventId,
                 0,
                 FALSE);

    if (status < 0) {
        return (FALSE);
    }

    return (TRUE);
}

/*
 *  ======== TransportShmCirc_control ========
 */
Bool TransportShmCirc_control(TransportShmCirc_Object *obj, UInt cmd,
    UArg cmdArg)
{
    return (FALSE);
}

/*
 *  ======== TransportShmCirc_getStatus ========
 */
Int TransportShmCirc_getStatus(TransportShmCirc_Object *obj)
{
    return (0);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== TransportShm_notifyFxn ========
 */
Void TransportShmCirc_notifyFxn(UInt16 procId,
                                UInt16 lineId,
                                UInt32 eventId,
                                UArg arg,
                                UInt32 payload)
{
    Swi_Handle swiHandle;

    /* Swi_Handle was passed as arg in register */
    swiHandle = (Swi_Handle)arg;

    /* post the Swi */
    Swi_post(swiHandle);
}

/*
 *  ======== TransportShmCirc_swiFxn ========
 */
Void TransportShmCirc_swiFxn(UArg arg)
{
    TransportShmCirc_Object *obj;
    UInt32 *eventEntry;
    UInt32 queueId;
    MessageQ_Msg msg;
    UInt32 writeIndex, readIndex;

    obj = (TransportShmCirc_Object *)arg;

    /* Make sure the TransportShmCirc_Object is not NULL */
    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_internal);

    /*
     *  Invalidate both getBuffer and getWriteIndex from cache.
     */
    if (obj->cacheEnabled) {
        Cache_inv(obj->getBuffer,
                  obj->opCacheSize,
                  Cache_Type_ALL,
                  TRUE);
    }

    /* get the writeIndex and readIndex */
    writeIndex = obj->getWriteIndex[0];
    readIndex = obj->getReadIndex[0];

    /* get the next entry to be processed */
    eventEntry = (UInt32 *)&(obj->getBuffer[readIndex]);

    while (writeIndex != readIndex) {
        /* get the msg (convert SRPtr to Ptr) */
        msg = SharedRegion_getPtr((SharedRegion_SRPtr)eventEntry[0]);

        /* get the queue id */
        queueId = MessageQ_getDstQueue(msg);

        /* put message on local queue */
        MessageQ_put(queueId, msg);

        /* update the local readIndex. */
        readIndex = ((readIndex + 1) & TransportShmCirc_maxIndex);

        /* set the getReadIndex */
        obj->getReadIndex[0] = readIndex;

        /*
         *  Write back the getReadIndex once every N / 4 messages.
         *  No need to invalidate since only one processor ever
         *  writes this . No need to wait for operation to complete
         *  since remote core updates its readIndex at least once
         *  every N messages and the remote core will not use a slot
         *  until it sees that the event has been processed with this
         *  cache wb. Chances are small that the remote core needs
         *  to spin due to this since we are doing a wb N / 4.
         */
        if ((obj->cacheEnabled) &&
            ((readIndex % TransportShmCirc_modIndex) == 0)) {
            Cache_wb(obj->getReadIndex,
                     sizeof(Bits32),
                     Cache_Type_ALL,
                     FALSE);
        }

        /* get the next entry */
        eventEntry = (UInt32 *)&(obj->getBuffer[readIndex]);
    }
}

/*
 *  ======== TransportShmCirc_sharedMemReq ========
 */
SizeT TransportShmCirc_sharedMemReq(const TransportShmCirc_Params *params)
{
    UInt16 regionId;
    SizeT minAlign, memReq;

    /* Ensure that params is non-NULL */
    Assert_isTrue(params != NULL, ti_sdo_ipc_Ipc_A_internal);

    regionId = SharedRegion_getId(params->sharedAddr);

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
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
     *      128b + 128b + 128b + 128b+ 128b + 128b = 768b
     *
     *  Note: CLS means Cache Line Size
     */
    memReq = 2 * (
        (_Ipc_roundup(sizeof(Ptr) * TransportShmCirc_numMsgs, minAlign)) +
        ( 2 * _Ipc_roundup(sizeof(Bits32), minAlign)));

    return (memReq);
}

/*
 *  ======== TransportShmCirc_setErrFxn ========
 */
Void TransportShmCirc_setErrFxn(TransportShmCirc_ErrFxn errFxn)
{
    /* Ignore the errFxn */
}
