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
 *  @file   MessageQ.c
 *
 *  @brief  MessageQ Linux implementation
 *
 *  This implementation is geared for use in a "client/server" model, whereby
 *  system-wide data is maintained in a "server" component and process-
 *  specific data is handled here.  At the moment, this implementation
 *  connects and communicates with LAD for the server connection.
 */

/* Standard IPC header */
#include <ti/ipc/Std.h>

/* Module level headers */
#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>
#define MessageQ_internal 1     /* must be defined before include file */
#include <ti/ipc/MessageQ.h>
#include <_MessageQ.h>
#include <ti/ipc/interfaces/IHeap.h>
#include <ti/ipc/interfaces/ITransport.h>
#include <ti/ipc/interfaces/IMessageQTransport.h>
#include <ti/ipc/interfaces/INetworkTransport.h>

/* Socket Headers */
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/eventfd.h>
#include <sys/queue.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#include <ladclient.h>
#include <_lad.h>

/* =============================================================================
 * Macros/Constants
 * =============================================================================
 */

/*!
 *  @brief  Name of the reserved NameServer used for MessageQ.
 */
#define MessageQ_NAMESERVER  "MessageQ"

#define MessageQ_MAXTRANSPORTS 8

#define MessageQ_GROWSIZE 32

/* Trace flag settings: */
#define TRACESHIFT    12
#define TRACEMASK     0x1000

/* Define BENCHMARK to quiet key MessageQ APIs: */
//#define BENCHMARK

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */

/* params structure evolution */
typedef struct {
    Void *synchronizer;
} MessageQ_Params_Legacy;

typedef struct {
    Int __version;
    Void *synchronizer;
    MessageQ_QueueIndex queueIndex;
} MessageQ_Params_Version2;

/* structure for MessageQ module state */
typedef struct MessageQ_ModuleObject {
    MessageQ_Handle           *queues;
    Int                       numQueues;
    Int                       refCount;
    NameServer_Handle         nameServer;
    pthread_mutex_t           gate;
    int                       seqNum;
    pthread_mutex_t           seqNumGate;
    IMessageQTransport_Handle transports[MultiProc_MAXPROCESSORS][2];
    ITransport_Handle         transInst[MessageQ_MAXTRANSPORTS];
    MessageQ_PutHookFxn       putHookFxn;
    Ptr                      *heaps;
    Int                       numHeaps;
} MessageQ_ModuleObject;

typedef struct MessageQ_CIRCLEQ_ENTRY {
     CIRCLEQ_ENTRY(MessageQ_CIRCLEQ_ENTRY) elem;
} MessageQ_CIRCLEQ_ENTRY;

/*!
 *  @brief  Structure for the Handle for the MessageQ.
 */
typedef struct MessageQ_Object_tag {
    CIRCLEQ_HEAD(dummy2, MessageQ_CIRCLEQ_ENTRY) msgList;
    pthread_mutex_t              msgListGate;
    MessageQ_Params              params;
    MessageQ_QueueId             queue;
    int                          unblocked;
    void                         *serverHandle;
    sem_t                        synchronizer;
} MessageQ_Object;

/* traces in this file are controlled via _MessageQ_verbose */
Bool _MessageQ_verbose = FALSE;
#define verbose _MessageQ_verbose

/* =============================================================================
 *  Globals
 * =============================================================================
 */
static MessageQ_ModuleObject MessageQ_state =
{
    .refCount   = 0,
    .nameServer = NULL,
#if defined(IPC_BUILDOS_ANDROID) && (PLATFORM_SDK_VERSION < 23)
    .gate       = PTHREAD_RECURSIVE_MUTEX_INITIALIZER,
#else
    .gate       = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP,
#endif
    .seqNumGate = PTHREAD_MUTEX_INITIALIZER,
    .putHookFxn = NULL,
    .heaps      = NULL,
    .numHeaps   = 0
};

/*!
 *  @var    MessageQ_module
 *
 *  @brief  Pointer to the MessageQ module state.
 */
MessageQ_ModuleObject *MessageQ_module = &MessageQ_state;

Void _MessageQ_grow(UInt16 queueIndex);

/* =============================================================================
 * APIS
 * =============================================================================
 */

Bool MessageQ_registerTransport(IMessageQTransport_Handle handle,
                                UInt16 rprocId, UInt priority)
{
    Int status = FALSE;
    UInt16 clusterId;

    if (handle == NULL) {
        fprintf(stderr,
                "MessageQ_registerTransport: invalid handle, must be non-NULL\n"
               );

        return status;
    }

    /* map procId to clusterId */
    clusterId = rprocId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_MAXPROCESSORS) {
        fprintf(stderr,
                "MessageQ_registerTransport: invalid procId %d\n", rprocId);

        return status;
    }

    if (MessageQ_module->transports[clusterId][priority] == NULL) {
        MessageQ_module->transports[clusterId][priority] = handle;

        status = TRUE;
    }

    return status;
}

Bool MessageQ_registerTransportId(UInt tid, ITransport_Handle inst)
{
    if (inst == NULL) {
        fprintf(stderr, "MessageQ_registerTransportId: invalid NULL handle\n");

        return MessageQ_E_INVALIDARG;
    }

    if (tid >= MessageQ_MAXTRANSPORTS) {
        fprintf(stderr,
                "MessageQ_unregisterNetTransport: invalid transport id %d, "
                "must be < %d\n", tid, MessageQ_MAXTRANSPORTS);

        return MessageQ_E_INVALIDARG;
    }

    if (MessageQ_module->transInst[tid] != NULL) {
        fprintf(stderr,
                "MessageQ_registerTransportId: transport id %d already "
                "registered\n", tid);

        return MessageQ_E_ALREADYEXISTS;
    }

    MessageQ_module->transInst[tid] = inst;

    return MessageQ_S_SUCCESS;
}

Void MessageQ_unregisterTransport(UInt16 rprocId, UInt priority)
{
    UInt16 clusterId;

    /* map procId to clusterId */
    clusterId = rprocId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_MAXPROCESSORS) {
        fprintf(stderr, "MessageQ_unregisterTransport: invalid rprocId %d\n",
                rprocId);

        return;
    }

    MessageQ_module->transports[clusterId][priority] = NULL;
}

Void MessageQ_unregisterTransportId(UInt tid)
{
    if (tid >= MessageQ_MAXTRANSPORTS) {
        fprintf(stderr,
                "MessageQ_unregisterTransportId: invalid transport id %d, "
                "must be < %d\n", tid, MessageQ_MAXTRANSPORTS);

        return;
    }

    MessageQ_module->transInst[tid] = NULL;
}

/*
 * Function to get default configuration for the MessageQ module.
 */
Void MessageQ_getConfig(MessageQ_Config *cfg)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    assert (cfg != NULL);

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "MessageQ_getConfig: can't find connection to daemon for pid %d\n",
           getpid())

        return;
    }

    cmd.cmd = LAD_MESSAGEQ_GETCONFIG;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "MessageQ_getConfig: sending LAD command failed, status=%d\n", status)
        return;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_getConfig: no LAD response, status=%d\n",
                      status)
        return;
    }
    status = rsp.messageQGetConfig.status;

    PRINTVERBOSE2(
      "MessageQ_getConfig: got LAD response for client %d, status=%d\n",
      handle, status)

    memcpy(cfg, &rsp.messageQGetConfig.cfg, sizeof (*cfg));

    return;
}

/*
 *  Function to setup the MessageQ module.
 */
Int MessageQ_setup(const MessageQ_Config *cfg)
{
    Int status = MessageQ_S_SUCCESS;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;
    Int pri;
    Int i;
    Int tid;

    /* this entire function must be serialized */
    pthread_mutex_lock(&MessageQ_module->gate);

    /* ensure only first thread performs startup procedure */
    if (++MessageQ_module->refCount > 1) {
        PRINTVERBOSE1("MessageQ module has been already setup, refCount=%d\n",
                MessageQ_module->refCount)
        status = MessageQ_S_ALREADYSETUP;
        goto exit;
    }

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1("MessageQ_setup: can't find connection to daemon for "
                "pid %d\n", getpid())
        status = MessageQ_E_RESOURCE;
        goto exit;
    }

    cmd.cmd = LAD_MESSAGEQ_SETUP;
    cmd.clientId = handle;
    memcpy(&cmd.args.messageQSetup.cfg, cfg, sizeof(*cfg));

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_setup: sending LAD command failed, "
                "status=%d\n", status)
        status = MessageQ_E_FAIL;
        goto exit;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_setup: no LAD response, status=%d\n", status)
        status = MessageQ_E_FAIL;
        goto exit;
    }
    status = rsp.setup.status;

    PRINTVERBOSE2("MessageQ_setup: LAD response for client %d, status=%d\n",
            handle, status)

    MessageQ_module->seqNum = 0;
    MessageQ_module->nameServer = rsp.setup.nameServerHandle;
    MessageQ_module->numQueues = cfg->maxRuntimeEntries;
    MessageQ_module->queues = calloc(cfg->maxRuntimeEntries,
            sizeof(MessageQ_Handle));
    MessageQ_module->numHeaps = cfg->numHeaps;
    MessageQ_module->heaps = calloc(cfg->numHeaps, sizeof(Ptr));

    for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
        for (pri = 0; pri < 2; pri++) {
            MessageQ_module->transports[i][pri] = NULL;
        }
    }

    for (tid = 0; tid < MessageQ_MAXTRANSPORTS; tid++) {
        MessageQ_module->transInst[tid] = NULL;
    }

exit:
    /* if error, must decrement reference count */
    if (status < 0) {
        MessageQ_module->refCount--;
    }

    pthread_mutex_unlock(&MessageQ_module->gate);

    return (status);
}

/*
 *  MessageQ_destroy - destroy the MessageQ module.
 */
Int MessageQ_destroy(void)
{
    Int status = MessageQ_S_SUCCESS;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;
    int i;

    /* this entire function must be serialized */
    pthread_mutex_lock(&MessageQ_module->gate);

    /* ensure only last thread does the work */
    if (--MessageQ_module->refCount > 0) {
        goto exit;
    }

    /* ensure all registered heaps have been unregistered */
    for (i = 0; i < MessageQ_module->numHeaps; i++) {
        if (MessageQ_module->heaps[i] != NULL) {
            PRINTVERBOSE1("MessageQ_destroy: Warning: found heapId=%d", i);
        }
    }
    free(MessageQ_module->heaps);
    MessageQ_module->heaps = NULL;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1("MessageQ_destroy: can't find connection to daemon "
                "for pid %d\n", getpid())
        status =  MessageQ_E_RESOURCE;
        goto exit;
    }

    cmd.cmd = LAD_MESSAGEQ_DESTROY;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_destroy: sending LAD command failed, "
                "status=%d\n", status)
        status = MessageQ_E_FAIL;
        goto exit;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_destroy: no LAD response, status=%d\n", status)
        status = MessageQ_E_FAIL;
        goto exit;
    }
    status = rsp.status;

    PRINTVERBOSE2("MessageQ_destroy: got LAD response for client %d, "
            "status=%d\n", handle, status)

exit:
    pthread_mutex_unlock(&MessageQ_module->gate);

    return (status);
}

/*
 *  ======== MessageQ_Params_init ========
 *  Legacy implementation.
 */
Void MessageQ_Params_init(MessageQ_Params *params)
{
    ((MessageQ_Params_Legacy *)params)->synchronizer = NULL;
}

/*
 *  ======== MessageQ_Params_init__S ========
 *  New implementation which is version aware.
 */
Void MessageQ_Params_init__S(MessageQ_Params *params, Int version)
{
    MessageQ_Params_Version2 *params2;

    switch (version) {

        case MessageQ_Params_VERSION_2:
            params2 = (MessageQ_Params_Version2 *)params;
            params2->__version = MessageQ_Params_VERSION_2;
            params2->synchronizer = NULL;
            params2->queueIndex = MessageQ_ANY;
            break;

        default:
            assert(FALSE);
            break;
    }
}

/*
 *  ======== MessageQ_create ========
 */
MessageQ_Handle MessageQ_create(String name, const MessageQ_Params *pp)
{
    Int                   status;
    MessageQ_Object      *obj = NULL;
    IMessageQTransport_Handle transport;
    INetworkTransport_Handle netTrans;
    ITransport_Handle     baseTrans;
    UInt16                queueIndex;
    UInt16                clusterId;
    Int                   tid;
    Int                   priority;
    LAD_ClientHandle      handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;
    MessageQ_Params ps;

    MessageQ_Params_init__S(&ps, MessageQ_Params_VERSION);

    /* copy the given params into the current params structure */
    if (pp != NULL) {

        /* snoop the params pointer to see if it's a legacy structure */
        if ((pp->__version == 0) || (pp->__version > 100)) {
            ps.synchronizer = ((MessageQ_Params_Legacy *)pp)->synchronizer;
        }

        /* not legacy structure, use params version field */
        else if (pp->__version == MessageQ_Params_VERSION_2) {
            ps.__version = ((MessageQ_Params_Version2 *)pp)->__version;
            ps.synchronizer = ((MessageQ_Params_Version2 *)pp)->synchronizer;
            ps.queueIndex = ((MessageQ_Params_Version2 *)pp)->queueIndex;
        }
        else {
            assert(FALSE);
        }
    }

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "MessageQ_create: can't find connection to daemon for pid %d\n",
           getpid())

        return NULL;
    }

    cmd.cmd = LAD_MESSAGEQ_CREATE;
    cmd.clientId = handle;

    if (name == NULL) {
        cmd.args.messageQCreate.name[0] = '\0';
    }
    else {
        strncpy(cmd.args.messageQCreate.name, name,
                LAD_MESSAGEQCREATEMAXNAMELEN - 1);
        cmd.args.messageQCreate.name[LAD_MESSAGEQCREATEMAXNAMELEN - 1] = '\0';
    }

    memcpy(&cmd.args.messageQCreate.params, &ps, sizeof(ps));

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "MessageQ_create: sending LAD command failed, status=%d\n", status)
        return NULL;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_create: no LAD response, status=%d\n", status)
        return NULL;
    }
    status = rsp.messageQCreate.status;

    PRINTVERBOSE2(
      "MessageQ_create: got LAD response for client %d, status=%d\n",
      handle, status)

    if (status == -1) {
       PRINTVERBOSE1(
          "MessageQ_create: MessageQ server operation failed, status=%d\n",
          status)
       return NULL;
    }

    /* Create the generic obj */
    obj = (MessageQ_Object *)calloc(1, sizeof (MessageQ_Object));

   /* Populate the params member */
    memcpy(&obj->params, &ps, sizeof(ps));


    obj->queue = rsp.messageQCreate.queueId;
    obj->serverHandle = rsp.messageQCreate.serverHandle;
    pthread_mutex_init(&obj->msgListGate, NULL);
    CIRCLEQ_INIT(&obj->msgList);
    if (sem_init(&obj->synchronizer, 0, 0) < 0) {
        PRINTVERBOSE1(
          "MessageQ_create: failed to create synchronizer (errno %d)\n", errno)

        MessageQ_delete((MessageQ_Handle *)&obj);

        return NULL;
    }

    /* lad returns the queue port # (queueIndex + PORT_OFFSET) */
    queueIndex = MessageQ_getQueueIndex(rsp.messageQCreate.queueId);

    PRINTVERBOSE2("MessageQ_create: creating endpoints for '%s' "
            "queueIndex %d\n", (name == NULL) ? "NULL" : name , queueIndex)

    pthread_mutex_lock(&MessageQ_module->gate);

    for (clusterId = 0; clusterId < MultiProc_MAXPROCESSORS; clusterId++) {
	for (priority = 0; priority < 2; priority++) {
            transport = MessageQ_module->transports[clusterId][priority];
            if (transport) {
                /* need to check return and do something if error */
                IMessageQTransport_bind((Void *)transport, obj->queue);
            }
        }
    }

    for (tid = 1; tid < MessageQ_MAXTRANSPORTS; tid++) {
        baseTrans = MessageQ_module->transInst[tid];

        if (baseTrans != NULL) {
            switch (ITransport_itype(baseTrans)) {
                case INetworkTransport_TypeId:
                    netTrans = INetworkTransport_downCast(baseTrans);
                    INetworkTransport_bind((void *)netTrans, obj->queue);
                    break;

                default:
                    /* error */
                    fprintf(stderr,
                            "MessageQ_create: Error: transport id %d is an "
                            "unsupported transport type.\n", tid);
                    break;
            }
        }
    }

    /* LAD's MessageQ module can grow, we need to grow as well */
    if (queueIndex >= MessageQ_module->numQueues) {
        _MessageQ_grow(queueIndex);
    }

    /*  No need to "allocate" slot since the queueIndex returned by
     *  LAD is guaranteed to be unique.
     */
    MessageQ_module->queues[queueIndex] = (MessageQ_Handle)obj;

    pthread_mutex_unlock(&MessageQ_module->gate);

    /* send announce message to LAD, indicating we are ready to receive msgs */
    cmd.cmd = LAD_MESSAGEQ_ANNOUNCE;
    cmd.clientId = handle;

    if (name == NULL) {
        cmd.args.messageQAnnounce.name[0] = '\0';
    }
    else {
        strncpy(cmd.args.messageQAnnounce.name, name,
                LAD_MESSAGEQCREATEMAXNAMELEN - 1);
        cmd.args.messageQAnnounce.name[LAD_MESSAGEQCREATEMAXNAMELEN - 1] = '\0';
    }

    cmd.args.messageQAnnounce.serverHandle = obj->serverHandle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "MessageQ_create: sending LAD command failed, status=%d\n", status)
        goto exit;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_create: no LAD response, status=%d\n", status)
        goto exit;
    }
    status = rsp.messageQAnnounce.status;

    PRINTVERBOSE2(
      "MessageQ_create: got LAD response for client %d, status=%d\n",
      handle, status)

    if (status == -1) {
       PRINTVERBOSE1(
          "MessageQ_create: MessageQ server operation failed, status=%d\n",
          status)
    }

exit:
    return (MessageQ_Handle)obj;
}

/*
 *  ======== MessageQ_delete ========
 */
Int MessageQ_delete(MessageQ_Handle *handlePtr)
{
    MessageQ_Object *obj;
    IMessageQTransport_Handle transport;
    INetworkTransport_Handle  netTrans;
    ITransport_Handle         baseTrans;
    Int              status = MessageQ_S_SUCCESS;
    UInt16           queueIndex;
    UInt16                clusterId;
    Int                   tid;
    Int                   priority;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "MessageQ_delete: can't find connection to daemon for pid %d\n",
           getpid())

        return MessageQ_E_FAIL;
    }

    obj = (MessageQ_Object *)(*handlePtr);

    cmd.cmd = LAD_MESSAGEQ_DELETE;
    cmd.clientId = handle;
    cmd.args.messageQDelete.serverHandle = obj->serverHandle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "MessageQ_delete: sending LAD command failed, status=%d\n", status)
        return MessageQ_E_FAIL;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_delete: no LAD response, status=%d\n", status)
        return MessageQ_E_FAIL;
    }
    status = rsp.messageQDelete.status;

    PRINTVERBOSE2(
      "MessageQ_delete: got LAD response for client %d, status=%d\n",
      handle, status)

    pthread_mutex_lock(&MessageQ_module->gate);

    for (clusterId = 0; clusterId < MultiProc_MAXPROCESSORS; clusterId++) {
	for (priority = 0; priority < 2; priority++) {
            transport = MessageQ_module->transports[clusterId][priority];
            if (transport) {
                IMessageQTransport_unbind((Void *)transport, obj->queue);
            }
        }
    }

    for (tid = 1; tid < MessageQ_MAXTRANSPORTS; tid++) {
        baseTrans = MessageQ_module->transInst[tid];

        if (baseTrans != NULL) {
            switch (ITransport_itype(baseTrans)) {
                case INetworkTransport_TypeId:
                    netTrans = INetworkTransport_downCast(baseTrans);
                    INetworkTransport_unbind((void *)netTrans, obj->queue);
                    break;

                default:
                    /* error */
                    fprintf(stderr,
                            "MessageQ_create: Error: transport id %d is an "
                            "unsupported transport type.\n", tid);
                    break;
            }
        }
    }

    /* extract the queue index from the queueId */
    queueIndex = MessageQ_getQueueIndex(obj->queue);
    MessageQ_module->queues[queueIndex] = NULL;

    pthread_mutex_unlock(&MessageQ_module->gate);

    free(obj);
    *handlePtr = NULL;

    return status;
}

/*
 *  ======== MessageQ_open ========
 *  Acquire a queueId for use in sending messages to the queue
 */
Int MessageQ_open(String name, MessageQ_QueueId *queueId)
{
    Int status = MessageQ_S_SUCCESS;

    status = NameServer_getUInt32(MessageQ_module->nameServer,
                                  name, queueId, NULL);

    if (status == NameServer_E_NOTFOUND) {
        /* Set return queue ID to invalid */
        *queueId = MessageQ_INVALIDMESSAGEQ;
        status = MessageQ_E_NOTFOUND;
    }
    else if (status >= 0) {
        /* Override with a MessageQ status code */
        status = MessageQ_S_SUCCESS;
    }
    else {
        /* Set return queue ID to invalid */
        *queueId = MessageQ_INVALIDMESSAGEQ;

        /* Override with a MessageQ status code */
        if (status == NameServer_E_TIMEOUT) {
            status = MessageQ_E_TIMEOUT;
        }
        else {
            status = MessageQ_E_FAIL;
        }
    }

    return status;
}

/*
 *  ======== MessageQ_openQueueId ========
 */
MessageQ_QueueId MessageQ_openQueueId(UInt16 queueIndex, UInt16 procId)
{
    MessageQ_QueueIndex queuePort;
    MessageQ_QueueId queueId;

    /* queue port is embedded in the queueId */
    queuePort = queueIndex + MessageQ_PORTOFFSET;
    queueId = ((MessageQ_QueueId)(procId) << 16) | queuePort;

    return (queueId);
}

/*
 *  ======== MessageQ_close ========
 *  Closes previously opened instance of MessageQ
 */
Int MessageQ_close(MessageQ_QueueId *queueId)
{
    Int32 status = MessageQ_S_SUCCESS;

    /* Nothing more to be done for closing the MessageQ. */
    *queueId = MessageQ_INVALIDMESSAGEQ;

    return status;
}

/*
 *  ======== MessageQ_put ========
 *  Deliver the given message, either locally or to the transport
 *
 *  If the destination is a local queue, deliver the message. Otherwise,
 *  pass the message to a transport for delivery. The transport handles
 *  the sending of the message using the appropriate interface (socket,
 *  device ioctl, etc.).
 */
Int MessageQ_put(MessageQ_QueueId queueId, MessageQ_Msg msg)
{
    Int status = MessageQ_S_SUCCESS;
    MessageQ_Object *obj;
    UInt16 dstProcId;
    UInt16 queueIndex;
    UInt16 queuePort;
    ITransport_Handle baseTrans;
    IMessageQTransport_Handle msgTrans;
    INetworkTransport_Handle netTrans;
    Int priority;
    UInt tid;
    UInt16 clusterId;
    Bool delivered;

    /* extract destination address from the given queueId */
    dstProcId  = (UInt16)(queueId >> 16);
    queuePort = (MessageQ_QueueIndex)(queueId & 0x0000ffff);

    /* write the destination address into the message header */
    msg->dstId = queuePort;
    msg->dstProc= dstProcId;

    /* invoke the hook function after addressing the message */
    if (MessageQ_module->putHookFxn != NULL) {
        MessageQ_module->putHookFxn(queueId, msg);
    }

    /*  For an outbound message: If message destination is on this
     *  processor, then check if the destination queue is in this
     *  process (thread-to-thread messaging).
     *
     *  For an inbound message: Check if destination queue is in this
     *  process (process-to-process messaging).
     */
    if (dstProcId == MultiProc_self()) {
        queueIndex = queuePort - MessageQ_PORTOFFSET;

        if (queueIndex < MessageQ_module->numQueues) {
            obj = (MessageQ_Object *)MessageQ_module->queues[queueIndex];

            if (obj != NULL) {
                /* deliver message to queue */
                pthread_mutex_lock(&obj->msgListGate);
                CIRCLEQ_INSERT_TAIL(&obj->msgList,
                        (MessageQ_CIRCLEQ_ENTRY *)msg, elem);
                pthread_mutex_unlock(&obj->msgListGate);
                sem_post(&obj->synchronizer);
                goto done;
            }
        }
        /* If we get here, then we have failed to deliver a local message. */
        status = MessageQ_E_FAIL;
        goto done;
    }

    /*  Getting here implies the message is outbound. Must give it to
     *  either the primary or secondary transport for delivery. Start
     *  by extracting the transport ID from the message header.
     */
    tid = MessageQ_getTransportId(msg);

    if (tid >= MessageQ_MAXTRANSPORTS) {
        fprintf(stderr,
                "MessageQ_put: Error: transport id %d too big, must be < %d\n",
                tid, MessageQ_MAXTRANSPORTS);
        status = MessageQ_E_FAIL;
        goto done;
    }

    /* if transportId is set, use secondary transport for message delivery */
    if (tid != 0) {
        baseTrans = MessageQ_module->transInst[tid];

        if (baseTrans == NULL) {
            fprintf(stderr, "MessageQ_put: Error: transport is null\n");
            status = MessageQ_E_FAIL;
            goto done;
        }

        /* downcast instance pointer to transport interface */
        switch (ITransport_itype(baseTrans)) {
            case INetworkTransport_TypeId:
                netTrans = INetworkTransport_downCast(baseTrans);
                delivered = INetworkTransport_put(netTrans, (Ptr)msg);
                status = (delivered ? MessageQ_S_SUCCESS :
                          (errno == ESHUTDOWN ? MessageQ_E_SHUTDOWN :
                           MessageQ_E_FAIL));
                break;

            default:
                /* error */
                fprintf(stderr, "MessageQ_put: Error: transport id %d is an "
                        "unsupported transport type\n", tid);
                status = MessageQ_E_FAIL;
                break;
        }
    }
    else {
        /* use primary transport for delivery */
        priority = MessageQ_getMsgPri(msg);
        clusterId = dstProcId - MultiProc_getBaseIdOfCluster();

        /* primary transport can only be used for intra-cluster delivery */
        if (clusterId > MultiProc_getNumProcsInCluster()) {
            fprintf(stderr,
                    "MessageQ_put: Error: destination procId=%d is not "
                    "in cluster. Must specify a transportId.\n", dstProcId);
            status =  MessageQ_E_FAIL;
            goto done;
        }

        msgTrans = MessageQ_module->transports[clusterId][priority];
        if (msgTrans) {
            delivered = IMessageQTransport_put(msgTrans, (Ptr)msg);
        }
        else {
            delivered = MessageQ_E_FAIL;
        }
        status = (delivered ? MessageQ_S_SUCCESS :
                  (errno == ESHUTDOWN ? MessageQ_E_SHUTDOWN : MessageQ_E_FAIL));
    }

done:
    return (status);
}

/*
 *  MessageQ_get - gets a message for a message queue and blocks if
 *  the queue is empty.
 *
 *  If a message is present, it returns it.  Otherwise it blocks
 *  waiting for a message to arrive.
 *  When a message is returned, it is owned by the caller.
 */
Int MessageQ_get(MessageQ_Handle handle, MessageQ_Msg *msg, UInt timeout)
{
    MessageQ_Object * obj = (MessageQ_Object *)handle;
    Int     status = MessageQ_S_SUCCESS;
    struct timespec ts;
    struct timeval tv;

#if 0
/*
 * Optimization here to get a message without going in to the sem
 * operation, but the sem count will not be maintained properly.
 */
    pthread_mutex_lock(&obj->msgListGate);

    if (obj->msgList.cqh_first != &obj->msgList) {
        *msg = (MessageQ_Msg)obj->msglist.cqh_first;
        CIRCLEQ_REMOVE(&obj->msgList, *msg, reserved0);

        pthread_mutex_unlock(&obj->msgListGate);
    }
    else {
        pthread_mutex_unlock(&obj->msgListGate);
    }
#endif

    if (timeout == MessageQ_FOREVER) {
        sem_wait(&obj->synchronizer);
    }
    else {
        /* add timeout (microseconds) to current time of day */
        gettimeofday(&tv, NULL);
        tv.tv_sec += timeout / 1000000;
        tv.tv_usec += timeout % 1000000;

        if (tv.tv_usec >= 1000000) {
              tv.tv_sec++;
              tv.tv_usec -= 1000000;
        }

        /* set absolute timeout value */
        ts.tv_sec = tv.tv_sec;
        ts.tv_nsec = tv.tv_usec * 1000; /* convert to nanoseconds */

        if (sem_timedwait(&obj->synchronizer, &ts) < 0) {
            if (errno == ETIMEDOUT) {
                PRINTVERBOSE0("MessageQ_get: operation timed out\n")
                return (MessageQ_E_TIMEOUT);
            }
            else {
                PRINTVERBOSE0("MessageQ_get: sem_timedwait error\n")
                return (MessageQ_E_FAIL);
            }
        }
    }

    if (obj->unblocked) {
        return obj->unblocked;
    }

    pthread_mutex_lock(&obj->msgListGate);

    *msg = (MessageQ_Msg)obj->msgList.cqh_first;
    CIRCLEQ_REMOVE(&obj->msgList, (MessageQ_CIRCLEQ_ENTRY *)*msg, elem);

    pthread_mutex_unlock(&obj->msgListGate);

    return status;
}

/*
 * Return a count of the number of messages in the queue
 *
 * TBD: Implement as a socket ioctl, using getsockopt().  Return -1 for now.
 */
Int MessageQ_count(MessageQ_Handle handle)
{
    Int               count = -1;
#if 0
    MessageQ_Object * obj   = (MessageQ_Object *) handle;
    socklen_t         optlen;

    /*
     * TBD: Need to find a way to implement (if anyone uses it!), and
     * push down into transport..
     */

    /*
     * 2nd arg to getsockopt should be transport independent, but using
     *  SSKPROTO_SHMFIFO for now:
     */
    getsockopt(obj->fd, SSKPROTO_SHMFIFO, SSKGETOPT_GETMSGQCOUNT,
                 &count, &optlen);
#endif

    return count;
}

/*
 *  Initializes a message not obtained from MessageQ_alloc.
 */
Void MessageQ_staticMsgInit(MessageQ_Msg msg, UInt32 size)
{
    /* Fill in the fields of the message */
    MessageQ_msgInit(msg);
    msg->heapId = MessageQ_STATICMSG;
    msg->msgSize = size;
}

/*
 *  Allocate a message and initialize the needed fields (note some
 *  of the fields in the header are set via other APIs or in the
 *  MessageQ_put function,
 */
MessageQ_Msg MessageQ_alloc(UInt16 heapId, UInt32 size)
{
    IHeap_Handle heap;
    MessageQ_Msg msg;

    if (heapId > (MessageQ_module->numHeaps - 1)) {
        PRINTVERBOSE1("MessageQ_alloc: Error: heapId (%d) too large", heapId);
        return (NULL);
    }
    else if (MessageQ_module->heaps[heapId] == NULL) {
        PRINTVERBOSE1("MessageQ_alloc: Error: heapId (%d) not registered",
                heapId);
        return (NULL);
    }
    else {
        heap = (IHeap_Handle)MessageQ_module->heaps[heapId];
    }

    msg = IHeap_alloc(heap, size);

    if (msg == NULL) {
        return (NULL);
    }

    MessageQ_msgInit(msg);
    msg->msgSize = size;
    msg->heapId = heapId;

    return (msg);
}

/*
 *  Frees the message back to the heap that was used to allocate it.
 */
Int MessageQ_free(MessageQ_Msg msg)
{
    UInt32 status = MessageQ_S_SUCCESS;
    IHeap_Handle heap;

    /* ensure this was not allocated by user */
    if (msg->heapId == MessageQ_STATICMSG) {
        status = MessageQ_E_CANNOTFREESTATICMSG;
    }
    else if (msg->heapId > (MessageQ_module->numHeaps - 1)) {
        status = MessageQ_E_INVALIDARG;
    }
    else if (MessageQ_module->heaps[msg->heapId] == NULL) {
        status = MessageQ_E_NOTFOUND;
    }
    else {
        heap = (IHeap_Handle)MessageQ_module->heaps[msg->heapId];
        IHeap_free(heap, (void *)msg);
    }

    return (status);
}

/*
 *  ======== MessageQ_registerHeap ========
 */
Int MessageQ_registerHeap(Ptr heap, UInt16 heapId)
{
    Int status = MessageQ_S_SUCCESS;

    pthread_mutex_lock(&MessageQ_module->gate);

    if (heapId > (MessageQ_module->numHeaps - 1)) {
        status = MessageQ_E_INVALIDARG;
    }
    else if (MessageQ_module->heaps[heapId] != NULL) {
        status = MessageQ_E_ALREADYEXISTS;
    }
    else {
        MessageQ_module->heaps[heapId] = heap;
    }

    pthread_mutex_unlock(&MessageQ_module->gate);

    return (status);
}

/*
 *  ======== MessageQ_unregisterHeap ========
 */
Int MessageQ_unregisterHeap(UInt16 heapId)
{
    Int status = MessageQ_S_SUCCESS;

    pthread_mutex_lock(&MessageQ_module->gate);

    if (heapId > (MessageQ_module->numHeaps - 1)) {
        status = MessageQ_E_INVALIDARG;
    }
    else if (MessageQ_module->heaps[heapId] == NULL) {
        status = MessageQ_E_NOTFOUND;
    }
    else {
        MessageQ_module->heaps[heapId] = NULL;
    }

    pthread_mutex_unlock(&MessageQ_module->gate);

    return (status);
}

/* Unblocks a MessageQ */
Void MessageQ_unblock(MessageQ_Handle handle)
{
    MessageQ_Object *obj = (MessageQ_Object *)handle;

    obj->unblocked = MessageQ_E_UNBLOCKED;
    sem_post(&obj->synchronizer);
}

/* Unblocks a MessageQ that's been shutdown due to transport failure */
Void MessageQ_shutdown(MessageQ_Handle handle)
{
    MessageQ_Object *obj = (MessageQ_Object *)handle;

    obj->unblocked = MessageQ_E_SHUTDOWN;
    sem_post(&obj->synchronizer);
}

/* Embeds a source message queue into a message */
Void MessageQ_setReplyQueue(MessageQ_Handle handle, MessageQ_Msg msg)
{
    MessageQ_Object *obj = (MessageQ_Object *)handle;

    msg->replyId = (UInt16)(obj->queue);
    msg->replyProc = (UInt16)(obj->queue >> 16);
}

/* Returns the QueueId associated with the handle. */
MessageQ_QueueId MessageQ_getQueueId(MessageQ_Handle handle)
{
    MessageQ_Object *obj = (MessageQ_Object *) handle;
    UInt32 queueId;

    queueId = (obj->queue);

    return queueId;
}

/* Returns the local handle associated with queueId. */
MessageQ_Handle MessageQ_getLocalHandle(MessageQ_QueueId queueId)
{
    MessageQ_Object *obj;
    MessageQ_QueueIndex queueIndex;
    UInt16 procId;

    procId = MessageQ_getProcId(queueId);
    if (procId != MultiProc_self()) {
        return NULL;
    }

    queueIndex = MessageQ_getQueueIndex(queueId);
    obj = (MessageQ_Object *)MessageQ_module->queues[queueIndex];

    return (MessageQ_Handle)obj;
}

/* Sets the tracing of a message */
Void MessageQ_setMsgTrace(MessageQ_Msg msg, Bool traceFlag)
{
    msg->flags = (msg->flags & ~TRACEMASK) |   (traceFlag << TRACESHIFT);
}

/*
 *  Returns the amount of shared memory used by one transport instance.
 *
 *  The MessageQ module itself does not use any shared memory but the
 *  underlying transport may use some shared memory.
 */
SizeT MessageQ_sharedMemReq(Ptr sharedAddr)
{
    SizeT memReq = 0u;

    /* Do nothing, as this is a copy transport. */

    return memReq;
}

/*
 * This is a helper function to initialize a message.
 */
Void MessageQ_msgInit(MessageQ_Msg msg)
{
#if 0
    Int                 status    = MessageQ_S_SUCCESS;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "MessageQ_msgInit: can't find connection to daemon for pid %d\n",
           getpid())

        return;
    }

    cmd.cmd = LAD_MESSAGEQ_MSGINIT;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "MessageQ_msgInit: sending LAD command failed, status=%d\n", status)
        return;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MessageQ_msgInit: no LAD response, status=%d\n", status)
        return;
    }
    status = rsp.msgInit.status;

    PRINTVERBOSE2(
      "MessageQ_msgInit: got LAD response for client %d, status=%d\n",
      handle, status)

    memcpy(msg, &rsp.msgInit.msg, sizeof (*msg));
#else
    msg->reserved0 = 0;  /* We set this to distinguish from NameServerMsg */
    msg->replyId   = (UInt16)MessageQ_INVALIDMESSAGEQ;
    msg->msgId     = MessageQ_INVALIDMSGID;
    msg->dstId     = (UInt16)MessageQ_INVALIDMESSAGEQ;
    msg->flags     = MessageQ_HEADERVERSION | MessageQ_NORMALPRI;
    msg->srcProc   = MultiProc_self();

    pthread_mutex_lock(&MessageQ_module->seqNumGate);
    msg->seqNum  = MessageQ_module->seqNum++;
    pthread_mutex_unlock(&MessageQ_module->seqNumGate);
#endif
}

/*
 *  ======== _MessageQ_grow ========
 *  Increase module's queues array to accommodate queueIndex from LAD
 *
 *  Note: this function takes the queue index value (i.e. without the
 *  port offset).
 */
Void _MessageQ_grow(UInt16 queueIndex)
{
    MessageQ_Handle *queues;
    MessageQ_Handle *oldQueues;
    UInt oldSize;

    pthread_mutex_lock(&MessageQ_module->gate);

    oldSize = MessageQ_module->numQueues * sizeof (MessageQ_Handle);

    queues = calloc(queueIndex + MessageQ_GROWSIZE, sizeof(MessageQ_Handle));
    memcpy(queues, MessageQ_module->queues, oldSize);

    oldQueues = MessageQ_module->queues;
    MessageQ_module->queues = queues;
    MessageQ_module->numQueues = queueIndex + MessageQ_GROWSIZE;

    pthread_mutex_unlock(&MessageQ_module->gate);

    free(oldQueues);

    return;
}

/*
 *  ======== MessageQ_bind ========
 *  Bind all existing message queues to the given processor
 *
 *  Note: This function is a hack to work around the driver.
 *
 *  The Linux rpmsgproto driver requires a socket for each
 *  message queue and remote processor tuple.
 *
 *      socket --> (queue, processor)
 *
 *  Therefore, each time a new remote processor is started, all
 *  existing message queues need to create a socket for the new
 *  processor.
 *
 *  The driver should not have this requirement. One socket per
 *  message queue should be sufficient to uniquely identify the
 *  endpoint to the driver.
 */
Void MessageQ_bind(UInt16 procId)
{
    int q;
    int clusterId;
    int priority;
    MessageQ_Handle handle;
    MessageQ_QueueId queue;
    IMessageQTransport_Handle transport;

    clusterId = procId - MultiProc_getBaseIdOfCluster();
    pthread_mutex_lock(&MessageQ_module->gate);

    for (q = 0; q < MessageQ_module->numQueues; q++) {

        if ((handle = MessageQ_module->queues[q]) == NULL) {
            continue;
        }

        queue = ((MessageQ_Object *)handle)->queue;

        for (priority = 0; priority < 2; priority++) {
            transport = MessageQ_module->transports[clusterId][priority];
            if (transport != NULL) {
                IMessageQTransport_bind((Void *)transport, queue);
            }
        }
    }

    pthread_mutex_unlock(&MessageQ_module->gate);
}

/*
 *  ======== MessageQ_unbind ========
 *  Unbind all existing message queues from the given processor
 *
 *  Hack: see MessageQ_bind.
 */
Void MessageQ_unbind(UInt16 procId)
{
    int q;
    int clusterId;
    int priority;
    MessageQ_Handle handle;
    MessageQ_QueueId queue;
    IMessageQTransport_Handle transport;

    pthread_mutex_lock(&MessageQ_module->gate);

    for (q = 0; q < MessageQ_module->numQueues; q++) {

        if ((handle = MessageQ_module->queues[q]) == NULL) {
            continue;
        }

        queue = ((MessageQ_Object *)handle)->queue;
        clusterId = procId - MultiProc_getBaseIdOfCluster();

        for (priority = 0; priority < 2; priority++) {
            transport = MessageQ_module->transports[clusterId][priority];
            if (transport != NULL) {
                IMessageQTransport_unbind((Void *)transport, queue);
            }
        }
    }

    pthread_mutex_unlock(&MessageQ_module->gate);
}
