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
 *  ======== TransportRpmsg.c ========
 */

#include <string.h>

#include <xdc/std.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Main.h>
#include <xdc/runtime/Registry.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>


#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_MessageQ.h>

#include <ti/ipc/rpmsg/virtio_ring.h>
#include <ti/ipc/rpmsg/_VirtQueue.h>
#include <ti/ipc/rpmsg/Rpmsg.h>
#include <ti/ipc/rpmsg/NameMap.h>

#include <ti/ipc/rpmsg/_RPMessage.h>
#include <ti/ipc/rpmsg/RPMessage.h>

#include <ti/ipc/namesrv/_NameServerRemoteRpmsg.h>

#include "_TransportRpmsg.h"
#include "package/internal/TransportRpmsg.xdc.h"

/* Maximum RPMSG payload: */
#define MAX_PAYLOAD (RPMSG_BUF_SIZE - sizeof(Rpmsg_Header))

/* Addresses below this are assumed to be bound to MessageQ objects: */
#define RPMSG_RESERVED_ADDRESSES     (1024)

/* Name of the rpmsg socket on host: */
#define RPMSG_SOCKET_NAME  "rpmsg-proto"

static Void transportCallbackFxn(RPMessage_Handle msgq, UArg arg, Ptr data,
                                      UInt16 dataLen, UInt32 srcAddr);

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== TransportRpmsg_Instance_init ========
 *
 */
#define FXNN "TransportRpmsg_Instance_init"
Int TransportRpmsg_Instance_init(TransportRpmsg_Object *obj,
        UInt16 remoteProcId, const TransportRpmsg_Params *params,
        Error_Block *eb)
{
    Bool        flag = FALSE;
    UInt32      myEndpoint = 0;

    Log_print1(Diags_INFO, FXNN": remoteProc: %d\n", remoteProcId);

    /* This MessageQ Transport over RPMSG only talks to the "HOST" for now: */
    Assert_isTrue(remoteProcId == MultiProc_getId("HOST"), NULL);
    RPMessage_init(remoteProcId);

    /* set object fields */
    obj->priority     = params->priority;
    obj->remoteProcId = remoteProcId;

    /* Announce our "MessageQ" service to the HOST: */
#ifdef RPMSG_NS_2_0
    NameMap_register(RPMSG_SOCKET_NAME, RPMSG_SOCKET_NAME, RPMSG_MESSAGEQ_PORT);
#else
    NameMap_register(RPMSG_SOCKET_NAME, RPMSG_MESSAGEQ_PORT);
#endif

    /* Associate incomming messages with this transport's callback fxn: */
    obj->msgqHandle = RPMessage_create(RPMSG_MESSAGEQ_PORT,
                                          transportCallbackFxn,
                                          (UArg)obj,
                                          &myEndpoint);

    /*
     * TBD: The following should be set via a ns_announcement from Linux side.
     * Setting this now will cause NameServer requests from BIOS side to
     * timeout (benignly), if the app calls MessageQ_open() in a loop.
     * Ideally, a NameMap module needs to allow registration for announcements.
     */
    NameServerRemote_SetNameServerPort(NAME_SERVER_RPMSG_ADDR);

    if (obj->msgqHandle) {
        /* Register the transport with MessageQ */
        flag = ti_sdo_ipc_MessageQ_registerTransport(
            TransportRpmsg_Handle_upCast(obj), remoteProcId, params->priority);
    }

    if (flag == FALSE) {
        return (2);
    }

    return (0);
}
#undef FXNN

/*
 *  ======== TransportRpmsg_Instance_finalize ========
 */
#define FXNN "TransportRpmsg_Instance_finalize"
Void TransportRpmsg_Instance_finalize(TransportRpmsg_Object *obj, Int status)
{
    Log_print0(Diags_ENTRY, "--> "FXNN);

    /* Announce our "MessageQ" service is going away: */
#ifdef RPMSG_NS_2_0
    NameMap_unregister(RPMSG_SOCKET_NAME, RPMSG_SOCKET_NAME,
            RPMSG_MESSAGEQ_PORT);
#else
    NameMap_unregister(RPMSG_SOCKET_NAME, RPMSG_MESSAGEQ_PORT);
#endif

    switch(status) {
        case 0: /* MessageQ_registerTransport succeeded */
            ti_sdo_ipc_MessageQ_unregisterTransport(obj->remoteProcId,
                obj->priority);
            /* fall thru OK */
        case 1: /* NOT USED: Notify_registerEventSingle failed */
        case 2: /* MessageQ_registerTransport failed */
            break;
    }

    RPMessage_finalize();

#undef FXNN
}

/*
 *  ======== TransportRpmsg_put ========
 *
 *  Notes: In keeping with the semantics of IMessageQTransport_put(), we
 *  simply return FALSE if the remote proc has made no buffers available in the
 *  vring.
 *  Otherwise, we could block here, waiting for the remote proc to add a buffer.
 *  This implies that the remote proc must always have buffers available in the
 *  vring in order for this side to send without failing!
 *
 *  Also, this is a copy-transport, to match the Linux side rpmsg.
 */
#define FXNN "TransportRpmsg_put"
Bool TransportRpmsg_put(TransportRpmsg_Object *obj, Ptr msg)
{
    Int          status;
    UInt         msgSize;
    UInt16       dstAddr;

    /* Send to remote processor: */
    /* Assert msg->msgSize <= vring's max fixed buffer size */
    msgSize = MessageQ_getMsgSize(msg);
    Assert_isTrue(msgSize <= MAX_PAYLOAD, NULL);
    dstAddr  = (((MessageQ_Msg)msg)->dstId & 0x0000FFFF);

    Log_print3(Diags_INFO, FXNN": sending msg from: %d, to: %d, dataLen: %d",
                  (IArg)RPMSG_MESSAGEQ_PORT, (IArg)dstAddr, (IArg)msgSize);
    status = RPMessage_send(obj->remoteProcId, dstAddr, RPMSG_MESSAGEQ_PORT,
                      msg, msgSize);

    /* free the app's message */
    if (((MessageQ_Msg)msg)->heapId != ti_sdo_ipc_MessageQ_STATICMSG) {
       MessageQ_free(msg);
    }

    return (status == RPMessage_S_SUCCESS? TRUE: FALSE);
}
#undef FXNN

/*
 *  ======== TransportRpmsg_control ========
 */
Bool TransportRpmsg_control(TransportRpmsg_Object *obj, UInt cmd,
    UArg cmdArg)
{
    return (FALSE);
}

/*
 *  ======== TransportRpmsg_getStatus ========
 */
Int TransportRpmsg_getStatus(TransportRpmsg_Object *obj)
{
    return (0);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== transportCallbackFxn ========
 *
 */
#define FXNN "transportCallbackFxn"
static Void transportCallbackFxn(RPMessage_Handle msgq, UArg arg, Ptr data,
                                      UInt16 dataLen, UInt32 srcAddr)
{
    UInt32            queueId;
    MessageQ_Msg      msg;
    MessageQ_Msg      buf = NULL;
    UInt              msgSize;
    NameServerRemote_Msg * nsrMsg;  /* Name Server Message */

    Log_print0(Diags_ENTRY, "--> "FXNN);

    Log_print3(Diags_INFO, FXNN": Received data: 0x%x from: %d, dataLen: %d",
                  (IArg)data, (IArg)srcAddr, (IArg)dataLen);
#if 0
/* TBD: This logic needs to be put in a callback from the name service endpt: */
    {
        Int               nsPort = NAME_SERVER_PORT_INVALID;

        /* See if this is an rpmsg ns announcment... : */
        if (rpMsg->dstAddr != RPMSG_MESSAGEQ_PORT) {
            if (rpMsg->dstAddr == RPMSG_NAMESERVICE_PORT) {
                nsMsg = (Rpmsg_NsMsg *)rpMsg->payload;
                Log_print3(Diags_USER1, FXNN": ns announcement "
                  "from %d: %s, flag: %s\n",
                  nsMsg->addr, (IArg)nsMsg->name,
                  (IArg)(nsMsg->flags == RPMSG_NS_CREATE? "create":"destroy"));
                /* ... and if it is from our rpmsg-proto socket, save
                 * the rpmsg src address as the NameServer reply address:
                 */
                if (!strcmp(nsMsg->name, RPMSG_SOCKET_NAME) &&
                    rpMsg->srcAddr == NAME_SERVER_RPMSG_ADDR) {
                    if (nsMsg->flags == RPMSG_NS_CREATE) {
                        nsPort = NAME_SERVER_RPMSG_ADDR;
                    }
                    else if (nsMsg->flags  == RPMSG_NS_DESTROY) {
                        nsPort = NAME_SERVER_PORT_INVALID;
                    }
                    NameServerRemote_SetNameServerPort(nsPort);
                }
            }
            goto skip;
        }
    }
#endif
    if(srcAddr >= RPMSG_RESERVED_ADDRESSES) {
        /*
         * This could either be a NameServer request or a MessageQ.
         * Check the NameServerRemote_Msg reserved field to distinguish.
         */
        nsrMsg = (NameServerRemote_Msg *)data;
        if (nsrMsg->reserved == NAMESERVER_MSG_TOKEN) {
            /* Process the NameServer request/reply message: */
            NameServerRemote_processMessage(nsrMsg);
            goto exit;
        }
    }

    /* Convert Rpmsg payload into a MessageQ_Msg: */
    msg = (MessageQ_Msg)data;

    Log_print4(Diags_INFO, FXNN": \n\tmsg->heapId: %d, "
               "msg->msgSize: %d, msg->dstId: %d, msg->msgId: %d\n",
               msg->heapId, msg->msgSize, msg->dstId, msg->msgId);

    /* Alloc a message from msg->heapId to copy the msg */
    msgSize = MessageQ_getMsgSize(msg);
    buf = MessageQ_alloc(msg->heapId, msgSize);

    /* Make sure buf is not NULL */
    Assert_isTrue(buf != NULL, NULL);

    /* copy the message to the buffer allocated. */
    memcpy((Ptr)buf, (Ptr)msg, msgSize);

    /*
     * If the message received was statically allocated, reset the
     * heapId, so the app can free it.
     */
    if (msg->heapId == ti_sdo_ipc_MessageQ_STATICMSG)  {
        msg->heapId = 0;  /* for a copy transport, heap id is 0. */
    }

    /* get the queue id */
    queueId = MessageQ_getDstQueue(msg);

    /* Pass to desitination queue: */
    MessageQ_put(queueId, buf);

exit:
    Log_print0(Diags_EXIT, "<-- "FXNN);
}

/*
 *  ======== TransportRpmsg_setErrFxn ========
 */
Void TransportRpmsg_setErrFxn(TransportRpmsg_ErrFxn errFxn)
{
    /* Ignore the errFxn */
}
