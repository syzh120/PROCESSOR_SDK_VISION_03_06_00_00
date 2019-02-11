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
 *  ======== TransportShmNotify.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/hal/Cache.h>

#include "package/internal/TransportShmNotify.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_MessageQ.h>

/* Need to use reserved notify events */
#undef TransportShmNotify_notifyEventId
#define TransportShmNotify_notifyEventId \
        ti_sdo_ipc_transports_TransportShmNotify_notifyEventId + \
                    (UInt32)((UInt32)Notify_SYSTEMKEY << 16)

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */


/*
 *  ======== TransportShmNotify_notifyFxn ========
 */
Void TransportShmNotify_notifyFxn(UInt16 procId,
                            UInt16 lineId,
                            UInt32 eventId,
                            UArg arg,
                            UInt32 payload)
{
    UInt32 queueId;
    MessageQ_Msg msg;
    UInt16 regionId;

    msg = SharedRegion_getPtr((SharedRegion_SRPtr)payload);

    /* Read new data into memory instead of old data from cache */
    regionId = SharedRegion_getId(msg);
    if (SharedRegion_isCacheEnabled(regionId)) {
        /* invalidate header before reading header */
        Cache_inv(msg,
                  sizeof(MessageQ_MsgHeader),
                  Cache_Type_ALL,
                  TRUE);
        /* invalidate the rest of the message */
        Cache_inv(((char *)msg) + sizeof(MessageQ_MsgHeader),
                  msg->msgSize - sizeof(MessageQ_MsgHeader),
                  Cache_Type_ALL,
                  TRUE);
    }

    queueId = MessageQ_getDstQueue(msg);

    MessageQ_put(queueId, msg);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== TransportShmNotify_Instance_init ========
 */
Int TransportShmNotify_Instance_init(TransportShmNotify_Object *obj,
        UInt16 procId, const TransportShmNotify_Params *params,
        Error_Block *eb)
{
    Int status;
    Bool flag;

    obj->priority      = params->priority;
    obj->remoteProcId  = procId;

    /* register the event with Notify */
    status = Notify_registerEventSingle(
                 procId,    /* remoteProcId */
                 0,         /* lineId */
                 TransportShmNotify_notifyEventId,
                 (Notify_FnNotifyCbck)TransportShmNotify_notifyFxn, 0);

    if (status < 0) {
        Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
        return (1);
    }

    /* Register the transport with MessageQ */
    flag = ti_sdo_ipc_MessageQ_registerTransport(
            TransportShmNotify_Handle_upCast(obj), procId, params->priority);

    if (flag == FALSE) {
        Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
        return (2);
    }

    return (0);
}

/*
 *  ======== TransportShmNotify_Instance_finalize ========
 */
Void TransportShmNotify_Instance_finalize(TransportShmNotify_Object* obj,
        Int status)
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
                TransportShmNotify_notifyEventId);
            break;
    }
}

/*
 *  ======== TransportShmNotify_put ========
 *  Assuming MessageQ_put is making sure that the arguments are ok
 */
Bool TransportShmNotify_put(TransportShmNotify_Object *obj, Ptr msg)
{
    UInt16 regionId = SharedRegion_INVALIDREGIONID;
    SharedRegion_SRPtr msgSRPtr;
    Int status;

    /*
     *  If translation is disabled and we always have to write back the message
     *  then we can avoid calling SharedRegion_getId()
     */
    if (ti_sdo_ipc_SharedRegion_translate ||
            !TransportShmNotify_alwaysWriteBackMsg ) {
        regionId = SharedRegion_getId(msg);
        if (SharedRegion_isCacheEnabled(regionId)) {
            Cache_wbInv(msg, ((MessageQ_Msg)(msg))->msgSize, Cache_Type_ALL,
                    TRUE);
        }
    }
    else {
        Cache_wbInv(msg, ((MessageQ_Msg)(msg))->msgSize, Cache_Type_ALL, TRUE);
    }

    /*
     *  Get the msg's SRPtr.  OK if (regionId == SharedRegion_INVALIDID &&
     *  SharedRegion_translate == FALSE)
     */
    msgSRPtr = SharedRegion_getSRPtr(msg, regionId);

    /*
     * Notify the remote processor and send msg via payload parameter
     * use waitClear = TRUE to make sure prior message was received
     */
    status = Notify_sendEvent(obj->remoteProcId, 0,
        TransportShmNotify_notifyEventId, (UInt32)msgSRPtr, TRUE);
    if (status < 0) {
        return (FALSE);
    }

    return (TRUE);
}

/*
 *  ======== TransportShmNotify_control ========
 */
Bool TransportShmNotify_control(TransportShmNotify_Object *obj, UInt cmd,
    UArg cmdArg)
{
    return (FALSE);
}

/*
 *  ======== TransportShmNotify_getStatus ========
 */
Int TransportShmNotify_getStatus(TransportShmNotify_Object *obj)
{
    return (0);
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== TransportShmNotify_setErrFxn ========
 */
Void TransportShmNotify_setErrFxn(TransportShmNotify_ErrFxn errFxn)
{
    /* Ignore the errFxn */
}
