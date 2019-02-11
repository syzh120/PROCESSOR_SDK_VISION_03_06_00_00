/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== TransportShm.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Memory.h>

#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/knl/Swi.h>

#include "package/internal/TransportShm.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_GateMP.h>
#include <ti/sdo/ipc/_ListMP.h>
#include <ti/sdo/ipc/_MessageQ.h>

/* Need to use reserved notify events */
#undef TransportShm_notifyEventId
#define TransportShm_notifyEventId \
        ti_sdo_ipc_transports_TransportShm_notifyEventId + \
                    (UInt32)((UInt32)Notify_SYSTEMKEY << 16)

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */


/*
 *  ======== TransportShm_notifyFxn ========
 */
Void TransportShm_notifyFxn(UInt16 procId,
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
 *  ======== TransportShm_swiFxn ========
 */
Void TransportShm_swiFxn(UArg arg)
{
    UInt32 queueId;
    TransportShm_Object *obj = (TransportShm_Object *)arg;
    MessageQ_Msg msg = NULL;

    /*
     *  While there are messages, get them out and send them to
     *  their final destination.
     */
    msg = (MessageQ_Msg)ListMP_getHead((ListMP_Handle)obj->localList);
    while (msg != NULL) {
        /* Get the destination message queue Id */
        queueId = MessageQ_getDstQueue(msg);

        /* put the message to the destination queue */
        MessageQ_put(queueId, msg);

        /* check to see if there are more messages */
        msg = (MessageQ_Msg)ListMP_getHead((ListMP_Handle)obj->localList);
    }
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== TransportShm_Instance_init ========
 */
Int TransportShm_Instance_init(TransportShm_Object *obj,
        UInt16 procId, const TransportShm_Params *params,
        Error_Block *eb)
{
    Int            localIndex;
    Int            remoteIndex;
    Int            status;
    Bool           flag;
    UInt32         minAlign;
    ListMP_Params  listMPParams[2];
    Swi_Handle     swiHandle;
    Swi_Params     swiParams;
    Ptr            localAddr;

    swiHandle = TransportShm_Instance_State_swiObj(obj);

    /*
     *  Determine who gets the '0' slot in shared memory and who gets
     *  the '1' slot. The '0' slot is given to the lower MultiProc id.
     */
    if (MultiProc_self() < procId) {
        localIndex  = 0;
        remoteIndex = 1;
    }
    else {
        localIndex  = 1;
        remoteIndex = 0;
    }

    if (params->openFlag) {
        /* Open by sharedAddr */
        obj->objType = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;
        obj->self = (TransportShm_Attrs *)params->sharedAddr;
        obj->regionId = SharedRegion_getId(params->sharedAddr);
        obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);

        localAddr = SharedRegion_getPtr(obj->self->gateMPAddr);
        status = GateMP_openByAddr(localAddr, (GateMP_Handle *)&obj->gate);
        if (status < 0) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return(1);
        }
    }
    else {
        /* init the gate for ListMP create below */
        if (params->gate != NULL) {
            obj->gate = params->gate;
        }
        else {
            obj->gate = (ti_sdo_ipc_GateMP_Handle)GateMP_getDefaultRemote();
        }

        /* Creating using sharedAddr */
        obj->regionId = SharedRegion_getId(params->sharedAddr);

        /* Assert that the buffer is in a valid shared region */
        Assert_isTrue(obj->regionId != SharedRegion_INVALIDREGIONID,
                ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

        /* Assert that sharedAddr is cache aligned */
        Assert_isTrue(SharedRegion_getCacheLineSize(obj->regionId) == 0 ||
                ((UInt32)params->sharedAddr %
                SharedRegion_getCacheLineSize(obj->regionId) == 0),
                ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

        /* set object's cacheEnabled, type, self */
        obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
        obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
        obj->self = (TransportShm_Attrs *)params->sharedAddr;
    }

    /* determine the minimum alignment to align to */
    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(obj->regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(obj->regionId);
    }

    /*
     *  Carve up the shared memory.
     *  If cache is enabled, these need to be on separate cache lines.
     *  This is done with minAlign and _Ipc_roundup function.
     */
    obj->other = (TransportShm_Attrs *)((UInt32)(obj->self) +
        (_Ipc_roundup(sizeof(TransportShm_Attrs), minAlign)));

    ListMP_Params_init(&(listMPParams[0]));
    listMPParams[0].gate = (GateMP_Handle)obj->gate;
    listMPParams[0].sharedAddr = (UInt32 *)((UInt32)(obj->other) +
        (_Ipc_roundup(sizeof(TransportShm_Attrs), minAlign)));

    ListMP_Params_init(&listMPParams[1]);
    listMPParams[1].gate = (GateMP_Handle)obj->gate;
    listMPParams[1].sharedAddr = (UInt32 *)((UInt32)(listMPParams[0].sharedAddr)
        + ListMP_sharedMemReq(&listMPParams[0]));

    obj->priority      = params->priority;
    obj->remoteProcId  = procId;

    Swi_Params_init(&swiParams);
    swiParams.arg0 = (UArg)obj;
    Swi_construct(Swi_struct(swiHandle),
                 (Swi_FuncPtr)TransportShm_swiFxn,
                 &swiParams, eb);

    if (params->openFlag == FALSE) {
        obj->localList = (ti_sdo_ipc_ListMP_Handle)
                ListMP_create(&(listMPParams[localIndex]));
        if (obj->localList == NULL) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (2);
        }

        obj->remoteList = (ti_sdo_ipc_ListMP_Handle)
                ListMP_create(&(listMPParams[remoteIndex]));
        if (obj->localList == NULL) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (2);
        }
    }
    else {
        /* Open the local ListMP instance */
        status = ListMP_openByAddr(listMPParams[localIndex].sharedAddr,
                                   (ListMP_Handle *)&(obj->localList));

        if (status < 0) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (2);
        }

        /* Open the remote ListMP instance */
        status = ListMP_openByAddr(listMPParams[remoteIndex].sharedAddr,
                                   (ListMP_Handle *)&(obj->remoteList));

        if (status < 0) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (2);
        }
    }

    /* register the event with Notify */
    status = Notify_registerEventSingle(
                 procId,    /* remoteProcId */
                 0,         /* lineId */
                 TransportShm_notifyEventId,
                 (Notify_FnNotifyCbck)TransportShm_notifyFxn,
                 (UArg)swiHandle);
    if (status < 0) {
        Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
        return (3);
    }

    /* Register the transport with MessageQ */
    flag = ti_sdo_ipc_MessageQ_registerTransport(
            TransportShm_Handle_upCast(obj), procId, params->priority);
    if (flag == FALSE) {
        Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
        return (4);
    }

    if (params->openFlag == FALSE) {
        obj->self->creatorProcId = MultiProc_self();
        obj->self->notifyEventId = TransportShm_notifyEventId;
        obj->self->priority = obj->priority;

        /* Store the GateMP sharedAddr in the Attrs */
        obj->self->gateMPAddr = ti_sdo_ipc_GateMP_getSharedAddr(obj->gate);
        obj->self->flag = TransportShm_UP;

        if (obj->cacheEnabled) {
            Cache_wbInv(obj->self, sizeof(TransportShm_Attrs),
                     Cache_Type_ALL, TRUE);
        }
    }
    else {
        obj->other->flag = TransportShm_UP;
        if (obj->cacheEnabled) {
            Cache_wbInv(&(obj->other->flag), minAlign, Cache_Type_ALL, TRUE);
        }
    }

    obj->status = TransportShm_UP;

    return (0);
}

/*
 *  ======== TransportShm_Instance_finalize ========
 */
Void TransportShm_Instance_finalize(TransportShm_Object* obj, Int status)
{
    Swi_Handle     swiHandle;

    if (obj->objType == ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC) {
        /* clear the self flag */
        obj->self->flag = 0;

        if (obj->cacheEnabled) {
            Cache_wbInv(&(obj->self->flag),
                SharedRegion_getCacheLineSize(obj->regionId), Cache_Type_ALL,
                    TRUE);
        }

        if (obj->localList != NULL) {
            ListMP_delete((ListMP_Handle *)&(obj->localList));
        }

        if (obj->remoteList != NULL) {
            ListMP_delete((ListMP_Handle *)&(obj->remoteList));
        }
    }
    else {
        /* other flag was set by remote proc */
        obj->other->flag = 0;

        if (obj->cacheEnabled) {
            Cache_wbInv(&(obj->other->flag),
                SharedRegion_getCacheLineSize(obj->regionId), Cache_Type_ALL,
                    TRUE);
        }

        if (obj->gate != NULL) {
            GateMP_close((GateMP_Handle *)&(obj->gate));
        }

        if (obj->localList != NULL) {
            ListMP_close((ListMP_Handle *)&(obj->localList));
        }

        if (obj->remoteList != NULL) {
            ListMP_close((ListMP_Handle *)&(obj->remoteList));
        }
    }

    switch(status) {
        case 0:
            /* MessageQ_registerTransport succeeded */
            ti_sdo_ipc_MessageQ_unregisterTransport(obj->remoteProcId, obj->priority);
            /* OK to fall through */
        case 1: /* GateMP open failed */
        case 2: /* ListMP create/open failed */
        case 3: /* Notify_registerEventSingle failed */
        case 4: /* MessageQ_registerTransport failed */
            Notify_unregisterEventSingle(
                obj->remoteProcId,
                0,
                TransportShm_notifyEventId);
            break;
    }

    /* Destruct the swi */
    swiHandle = TransportShm_Instance_State_swiObj(obj);
    if (swiHandle != NULL) {
        Swi_destruct(Swi_struct(swiHandle));
    }
}

/*
 *  ======== TransportShm_put ========
 *  Assuming MessageQ_put is making sure that the arguments are ok
 */
Bool TransportShm_put(TransportShm_Object *obj, Ptr msg)
{
    Int32 status;
    Bool retval = TRUE;
    IArg key;
    UInt16 id = SharedRegion_getId(msg);

    /* This transport only deals with messages allocated from SR's */
    Assert_isTrue(id != SharedRegion_INVALIDREGIONID,
            ti_sdo_ipc_SharedRegion_A_regionInvalid);

    /* writeback invalidate the message */
    if (SharedRegion_isCacheEnabled(id)) {
        Cache_wbInv(msg, ((MessageQ_Msg)(msg))->msgSize, Cache_Type_ALL,
            TRUE);
    }

    /* make sure ListMP_put and sendEvent are done before remote executes */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    /* Put the message on the remoteList */
    ListMP_putTail((ListMP_Handle)obj->remoteList, (ListMP_Elem *)msg);

    /* Notify the remote processor */
    status = Notify_sendEvent(obj->remoteProcId, 0, TransportShm_notifyEventId,
        0, FALSE);

    /* check the status of the sendEvent */
    if (status < 0) {
        /* remove the message from the List and return 'FALSE' */
        ListMP_remove((ListMP_Handle)obj->remoteList, (ListMP_Elem *)msg);
        retval = FALSE;
    }

    /* leave the gate */
    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (retval);
}

/*
 *  ======== TransportShm_control ========
 */
Bool TransportShm_control(TransportShm_Object *obj, UInt cmd, UArg cmdArg)
{
    return (FALSE);
}

/*
 *  ======== TransportShm_getStatus ========
 */
Int TransportShm_getStatus(TransportShm_Object *obj)
{
    return (obj->status);
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== TransportShm_close ========
 */
Void TransportShm_close(TransportShm_Handle *handle)
{
    TransportShm_delete(handle);
}

/*
 *  ======== TransportShm_openByAddr ========
 */
Int TransportShm_openByAddr(Ptr sharedAddr,
                      TransportShm_Handle *handlePtr,
                      Error_Block *eb)
{
    TransportShm_Params params;
    TransportShm_Attrs *attrs;
    Int status;
    UInt16 id;

    if (sharedAddr == NULL) {
        return (MessageQ_E_FAIL);
    }

    TransportShm_Params_init(&params);

    /* Tell Instance_init() that we're opening */
    params.openFlag = TRUE;

    attrs = (TransportShm_Attrs *)sharedAddr;
    id = SharedRegion_getId(sharedAddr);

    /* Assert that the region is valid */
    Assert_isTrue(id != SharedRegion_INVALIDREGIONID,
            ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

    /* invalidate the attrs before using it */
    if (SharedRegion_isCacheEnabled(id)) {
        Cache_inv(attrs, sizeof(TransportShm_Attrs), Cache_Type_ALL, TRUE);
    }

    /* set params field */
    params.sharedAddr    = sharedAddr;
    params.priority      = attrs->priority;

    if (attrs->flag != TransportShm_UP) {
        /* make sure transport is up */
        *handlePtr = NULL;
        status = MessageQ_E_NOTFOUND;
    }
    else {
        /* Create the object */
        *handlePtr = TransportShm_create(attrs->creatorProcId, &params, eb);
        if (*handlePtr == NULL) {
            status = MessageQ_E_FAIL;
        }
        else {
            status = MessageQ_S_SUCCESS;
        }
    }

    return (status);
}

/*
 *  ======== TransportShm_sharedMemReq ========
 */
SizeT TransportShm_sharedMemReq(const TransportShm_Params *params)
{
    SizeT memReq, minAlign;
    UInt16 regionId;
    ListMP_Params listMPParams;

    regionId = SharedRegion_getId(params->sharedAddr);

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
    }

    /* for the Attrs structure */
    memReq = _Ipc_roundup(sizeof(TransportShm_Attrs), minAlign);

    /* for the second Attrs structure */
    memReq += _Ipc_roundup(sizeof(TransportShm_Attrs), minAlign);

    ListMP_Params_init(&listMPParams);
    listMPParams.regionId = regionId;

    /* for localListMP */
    memReq += ListMP_sharedMemReq(&listMPParams);

    /* for remoteListMP */
    memReq += ListMP_sharedMemReq(&listMPParams);

    return(memReq);
}

/*
 *  ======== TransportShm_setErrFxn ========
 */
Void TransportShm_setErrFxn(TransportShm_ErrFxn errFxn)
{
    /* Ignore errFxn */
}
