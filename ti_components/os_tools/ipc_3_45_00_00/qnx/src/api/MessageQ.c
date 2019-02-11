/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
/*============================================================================
 *  @file   MessageQ.c
 *
 *  @brief  MessageQ module "client" implementation
 *
 *  This implementation is geared for use in a "client/server" model, whereby
 *  system-wide data is maintained in a "server" component and process-
 *  specific data is handled here.  At the moment, this implementation
 *  connects and communicates with LAD for the server connection.
 *
 *  The MessageQ module supports the structured sending and receiving of
 *  variable length messages. This module can be used for homogeneous or
 *  heterogeneous multi-processor messaging.
 *
 *  MessageQ provides more sophisticated messaging than other modules. It is
 *  typically used for complex situations such as multi-processor messaging.
 *
 *  The following are key features of the MessageQ module:
 *  -Writers and readers can be relocated to another processor with no
 *   runtime code changes.
 *  -Timeouts are allowed when receiving messages.
 *  -Readers can determine the writer and reply back.
 *  -Receiving a message is deterministic when the timeout is zero.
 *  -Messages can reside on any message queue.
 *  -Supports zero-copy transfers.
 *  -Can send and receive from any type of thread.
 *  -Notification mechanism is specified by application.
 *  -Allows QoS (quality of service) on message buffer pools. For example,
 *   using specific buffer pools for specific message queues.
 *
 *  Messages are sent and received via a message queue. A reader is a thread
 *  that gets (reads) messages from a message queue. A writer is a thread that
 *  puts (writes) a message to a message queue. Each message queue has one
 *  reader and can have many writers. A thread may read from or write to multiple
 *  message queues.
 *
 *  Conceptually, the reader thread owns a message queue. The reader thread
 *  creates a message queue. Writer threads  a created message queues to
 *  get access to them.
 *
 *  Message queues are identified by a system-wide unique name. Internally,
 *  MessageQ uses the NameServermodule for managing
 *  these names. The names are used for opening a message queue. Using
 *  names is not required.
 *
 *  Messages must be allocated from the MessageQ module. Once a message is
 *  allocated, it can be sent on any message queue. Once a message is sent, the
 *  writer loses ownership of the message and should not attempt to modify the
 *  message. Once the reader receives the message, it owns the message. It
 *  may either free the message or re-use the message.
 *
 *  Messages in a message queue can be of variable length. The only
 *  requirement is that the first field in the definition of a message must be a
 *  MsgHeader structure. For example:
 *  typedef struct MyMsg {
 *      MessageQ_MsgHeader header;
 *      ...
 *  } MyMsg;
 *
 *  The MessageQ API uses the MessageQ_MsgHeader internally. Your application
 *  should not modify or directly access the fields in the MessageQ_MsgHeader.
 *
 *  All messages sent via the MessageQ module must be allocated from a
 *  Heap implementation. The heap can be used for
 *  other memory allocation not related to MessageQ.
 *
 *  An application can use multiple heaps. The purpose of having multiple
 *  heaps is to allow an application to regulate its message usage. For
 *  example, an application can allocate critical messages from one heap of fast
 *  on-chip memory and non-critical messages from another heap of slower
 *  external memory
 *
 *  MessageQ does support the usage of messages that allocated via the
 *  alloc function. Please refer to the staticMsgInit
 *  function description for more details.
 *
 *  In a multiple processor system, MessageQ communications to other
 *  processors via MessageQTransport instances. There must be one and
 *  only one MessageQTransport instance for each processor where communication
 *  is desired.
 *  So on a four processor system, each processor must have three
 *  MessageQTransport instance.
 *
 *  The user only needs to create the MessageQTransport instances. The instances
 *  are responsible for registering themselves with MessageQ.
 *  This is accomplished via the registerTransport function.
 *
 *  ============================================================================
 */


/* Standard headers */
#include <ti/ipc/Std.h>

/* Linux specific header files, replacing OSAL: */
#include <pthread.h>

/* Module level headers */
#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/inc/_MultiProc.h>
#define MessageQ_internal 1     /* must be defined before include file */
#include <ti/ipc/MessageQ.h>
#include <_MessageQ.h>
#include <_IpcLog.h>
#include <ti/syslink/inc/MessageQDrvDefs.h>

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/param.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

#include <ti/syslink/inc/usr/Qnx/MessageQDrv.h>

/* TI IPC utils: */
#include <ti/ipc/TiIpcFxns.h>

#include <ti/syslink/inc/ti/ipc/ti_ipc.h>

/* =============================================================================
 * Macros/Constants
 * =============================================================================
 */

/*!
 *  @brief  Name of the reserved NameServer used for MessageQ.
 */
#define MessageQ_NAMESERVER  "MessageQ"

/* More magic rpmsg port numbers: */
#define MESSAGEQ_RPMSG_PORT       61
#define MESSAGEQ_RPMSG_MAXSIZE    512
#define RPMSG_RESERVED_ADDRESSES  (1024)

/* Trace flag settings: */
#define TRACESHIFT    12
#define TRACEMASK     0x1000

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
    Int                 refCount;
    /*!< Reference count */
    NameServer_Handle   nameServer;
    /*!< Handle to the local NameServer used for storing GP objects */
    pthread_mutex_t     gate;
    /*!< Handle of gate to be used for local thread safety */
    int                 ipcFd[MultiProc_MAXPROCESSORS];
    /*!< File Descriptors for sending to each remote processor */
    int                 seqNum;
    /*!< Process-specific sequence number */
    MessageQ_PutHookFxn putHookFxn;
    /*!< hook function for MessageQ_put method */
} MessageQ_ModuleObject;

/*!
 *  @brief  Structure for the Handle for the MessageQ.
 */
typedef struct MessageQ_Object_tag {
    MessageQ_Params         params;
    /*! Instance specific creation parameters */
    MessageQ_QueueId        queue;
    /* Unique id */
    int                     ipcFd;
    /* File Descriptors to receive from a message queue. */
    int                     unblocked;
    /* Is the queue unblocked and how */
    int                     unblockFdW;
    /* Write this fd to unblock the select() call in MessageQ _get() */
    int                     unblockFdR;
     /* File Descriptor to block on to listen to unblockFdW. */
    void                    *serverHandle;
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
    .putHookFxn = NULL
};

/*!
 *  @var    MessageQ_module
 *
 *  @brief  Pointer to the MessageQ module state.
 */
MessageQ_ModuleObject * MessageQ_module = &MessageQ_state;


/* =============================================================================
 * Forward declarations of internal functions
 * =============================================================================
 */

/* This is a helper function to initialize a message. */
static Int transportCreateEndpoint(int * fd, UInt16 queueIndex);
static Int transportCloseEndpoint(int fd);
static Int transportGet(int fd, MessageQ_Msg * retMsg);
static Int transportPut(MessageQ_Msg msg, UInt16 dstId, UInt16 dstProcId);

/* =============================================================================
 * APIS
 * =============================================================================
 */
/* Function to get default configuration for the MessageQ module.
 *
 */
Void MessageQ_getConfig (MessageQ_Config * cfg)
{
    Int status;
    MessageQDrv_CmdArgs cmdArgs;

    assert (cfg != NULL);

    cmdArgs.args.getConfig.config = cfg;
    status = MessageQDrv_ioctl (CMD_MESSAGEQ_GETCONFIG, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("MessageQ_getConfig: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return;
}

/* Function to setup the MessageQ module. */
Int MessageQ_setup (const MessageQ_Config * cfg)
{
    Int status;
    MessageQDrv_CmdArgs cmdArgs;

    Int i;

    cmdArgs.args.setup.config = (MessageQ_Config *) cfg;
    status = MessageQDrv_ioctl(CMD_MESSAGEQ_SETUP, &cmdArgs);
    if (status < 0) {
        PRINTVERBOSE1("MessageQ_setup: API (through IOCTL) failed, \
            status=%d\n", status)
        return status;
    }

    MessageQ_module->nameServer = cmdArgs.args.setup.nameServerHandle;
    MessageQ_module->seqNum = 0;

    /* Create a default local gate. */
    pthread_mutex_init (&(MessageQ_module->gate), NULL);

    /* Clear ipcFd array. */
    for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
       MessageQ_module->ipcFd[i]      = -1;
    }

    return status;
}

/*
 * Function to destroy the MessageQ module.
 */
Int MessageQ_destroy (void)
{
    Int status;
    MessageQDrv_CmdArgs    cmdArgs;

    pthread_mutex_destroy(&(MessageQ_module->gate));

    status = MessageQDrv_ioctl (CMD_MESSAGEQ_DESTROY, &cmdArgs);
    if (status < 0) {
        PRINTVERBOSE1("MessageQ_destroy: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return status;
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
 *   Function to create a MessageQ object for receiving.
 *
 *   Create a file descriptor and bind the source address
 *   (local ProcId/MessageQ ID) in
 *   order to get messages dispatched to this messageQ.
 */
MessageQ_Handle MessageQ_create (String name, const MessageQ_Params * pp)
{
    Int                   status    = MessageQ_S_SUCCESS;
    MessageQ_Object *     obj    = NULL;
    UInt16                queuePort = 0u;
    MessageQDrv_CmdArgs   cmdArgs;
    int                   fildes[2];
    MessageQ_Params       ps;

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

    cmdArgs.args.create.params = &ps;
    cmdArgs.args.create.name = name;

    if (name != NULL) {
        cmdArgs.args.create.nameLen = (strlen (name) + 1);
    }
    else {
        cmdArgs.args.create.nameLen = 0;
    }

    /* Create the generic obj */
    obj = (MessageQ_Object *)calloc(1, sizeof (MessageQ_Object));
    if (obj == NULL) {
        PRINTVERBOSE0("MessageQ_create: memory allocation failed\n")
        return NULL;
    }

    status = MessageQDrv_ioctl (CMD_MESSAGEQ_CREATE, &cmdArgs);
    if (status < 0) {
        PRINTVERBOSE1("MessageQ_create: API (through IOCTL) failed, \
            status=%d\n", status)
        goto cleanup;
    }

    /* Populate the params member */
    memcpy(&obj->params, &ps, sizeof(ps));

    obj->queue = cmdArgs.args.create.queueId;
    obj->serverHandle = cmdArgs.args.create.handle;

    /* Get the queue port # (queueIndex + PORT_OFFSET) */
    queuePort = obj->queue & 0x0000FFFF;

    PRINTVERBOSE2("MessageQ_create: creating endpoint for: %s"
        "queuePort %d\n", (name == NULL) ? "NULL" : name , queuePort)
    status = transportCreateEndpoint(&obj->ipcFd, queuePort);
    if (status < 0) {
       goto cleanup;
    }

    /*
     * Now, to support MessageQ_unblock() functionality, create an event object.
     * Writing to this event will unblock the select() call in MessageQ_get().
     */
    if (pipe(fildes) == -1) {
        printf ("MessageQ_create: pipe creation failed: %d, %s\n",
                   errno, strerror(errno));
        status = MessageQ_E_FAIL;
        obj->unblockFdW = obj->unblockFdR = -1;
    }
    else {
        obj->unblockFdW = fildes[1];
        obj->unblockFdR = fildes[0];
    }

cleanup:
    /* Cleanup if fail: */
    if (status < 0) {
        MessageQ_delete((MessageQ_Handle *)&obj);
    }

    return ((MessageQ_Handle) obj);
}

/*
 * Function to delete a MessageQ object for a specific slave processor.
 *
 * Deletes the file descriptors associated with this MessageQ object.
 */
Int MessageQ_delete (MessageQ_Handle * handlePtr)
{
    Int               status    = MessageQ_S_SUCCESS;
    MessageQ_Object * obj       = NULL;
    MessageQDrv_CmdArgs cmdArgs;

    assert(handlePtr != NULL);
    obj = (MessageQ_Object *) (*handlePtr);
    assert(obj != NULL);

    if (obj->serverHandle != NULL) {
        cmdArgs.args.deleteMessageQ.handle = obj->serverHandle;
        status = MessageQDrv_ioctl (CMD_MESSAGEQ_DELETE, &cmdArgs);
        if (status < 0) {
            PRINTVERBOSE1("MessageQ_delete: API (through IOCTL) failed, \
                status=%d\n", status)
        }
    }

    /* Close the fds used for MessageQ_unblock(): */
    if (obj->unblockFdW >= 0) {
        close(obj->unblockFdW);
    }
    if (obj->unblockFdR >= 0) {
        close(obj->unblockFdR);
    }

    /* Close the communication endpoint: */
    if (obj->ipcFd >= 0) {
        transportCloseEndpoint(obj->ipcFd);
    }

    /* Now free the obj */
    free (obj);
    *handlePtr = NULL;

    return (status);
}

/*
 *  Opens an instance of MessageQ for sending.
 *
 *  We need not create a tiipc file descriptor here; the file descriptors for
 *  all remote processors were created during MessageQ_attach(), and will be
 *  retrieved during MessageQ_put().
 */
Int MessageQ_open (String name, MessageQ_QueueId * queueId)
{
    Int status = MessageQ_S_SUCCESS;

    status = NameServer_getUInt32 (MessageQ_module->nameServer,
                                     name, queueId, NULL);

    if (status == NameServer_E_NOTFOUND) {
        /* Set return queue ID to invalid. */
        *queueId = MessageQ_INVALIDMESSAGEQ;
        status = MessageQ_E_NOTFOUND;
    }
    else if (status >= 0) {
        /* Override with a MessageQ status code. */
        status = MessageQ_S_SUCCESS;
    }
    else {
        /* Set return queue ID to invalid. */
        *queueId = MessageQ_INVALIDMESSAGEQ;
        /* Override with a MessageQ status code. */
        if (status == NameServer_E_TIMEOUT) {
            status = MessageQ_E_TIMEOUT;
        }
        else {
            status = MessageQ_E_FAIL;
        }
    }

    return (status);
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

/* Closes previously opened instance of MessageQ module. */
Int MessageQ_close (MessageQ_QueueId * queueId)
{
    Int32 status = MessageQ_S_SUCCESS;

    /* Nothing more to be done for closing the MessageQ. */
    *queueId = MessageQ_INVALIDMESSAGEQ;

    return (status);
}

/*
 * Place a message onto a message queue.
 *
 * Calls TransportShm_put(), which handles the sending of the message using the
 * appropriate kernel interface (socket, device ioctl) call for the remote
 * procId encoded in the queueId argument.
 *
 */
Int MessageQ_put (MessageQ_QueueId queueId, MessageQ_Msg msg)
{
    Int      status;
    UInt16   dstProcId  = (UInt16)(queueId >> 16);
    UInt16   queuePort = queueId & 0x0000ffff;

    /* use the queue port # for destination address */
    msg->dstId     = queuePort;
    msg->dstProc   = dstProcId;

    /* invoke put hook function after addressing the message */
    if (MessageQ_module->putHookFxn != NULL) {
        MessageQ_module->putHookFxn(queueId, msg);
    }

    status = transportPut(msg, queuePort, dstProcId);

    return (status);
}

/*
 * Gets a message for a message queue and blocks if the queue is empty.
 * If a message is present, it returns it.  Otherwise it blocks
 * waiting for a message to arrive.
 * When a message is returned, it is owned by the caller.
 *
 * We block using select() on the receiving tiipc file descriptor, then
 * get the waiting message via a read.
 * We use the file descriptors stored in the messageQ object via a previous
 * call to MessageQ_create().
 *
 * Note: We currently do not support messages to be sent between threads on the
 * lcoal processor.
 *
 */
Int MessageQ_get (MessageQ_Handle handle, MessageQ_Msg * msg ,UInt timeout)
{
    Int     status = MessageQ_S_SUCCESS;
    Int     tmpStatus;
    MessageQ_Object * obj = (MessageQ_Object *) handle;
    int     retval;
    int     nfds;
    fd_set  rfds;
    struct  timeval tv;
    void    *timevalPtr;
    int     maxfd = 0;

    /* Wait (with timeout) and retreive message */
    FD_ZERO(&rfds);
    FD_SET(obj->ipcFd, &rfds);
    maxfd = obj->ipcFd;

    /* Wait also on the event fd, which may be written by MessageQ_unblock(): */
    FD_SET(obj->unblockFdR, &rfds);

    if (timeout == MessageQ_FOREVER) {
        timevalPtr = NULL;
    }
    else {
        /* Timeout given in msec: convert:  */
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        timevalPtr = &tv;
    }
    /* Add one to last fd created: */
    nfds = ((maxfd > obj->unblockFdR) ? maxfd : obj->unblockFdR) + 1;

    *msg = NULL;

    retval = select(nfds, &rfds, NULL, NULL, timevalPtr);
    if (retval > 0)  {
        if (FD_ISSET(obj->unblockFdR, &rfds))  {
            /*
             * Our event was signalled by MessageQ_unblock().
             *
             * This is typically done during a shutdown sequence, where
             * the intention of the client would be to ignore (i.e. not fetch)
             * any pending messages in the transport's queue.
             * Thus, we shall not check for nor return any messages.
             */
            return (obj->unblocked);
        }
        else {
            if (FD_ISSET(obj->ipcFd, &rfds)) {
                /* Our transport's fd was signalled: Get the message: */
                tmpStatus = transportGet(obj->ipcFd, msg);
                if (tmpStatus < 0) {
                    printf ("MessageQ_get: transportGet failed.\n");
                    if (tmpStatus == MessageQ_E_SHUTDOWN) {
                        status = tmpStatus;
                        MessageQ_shutdown(handle);
                    }
                    else {
                        status = MessageQ_E_FAIL;
                    }
                }
            }
        }
    }
    else if (retval == 0) {
        status = MessageQ_E_TIMEOUT;
    }
    else {
        status = MessageQ_E_FAIL;
    }

    return (status);
}

/*
 * Return a count of the number of messages in the queue
 *
 * TBD: To be implemented. Return -1 for now.
 */
Int MessageQ_count (MessageQ_Handle handle)
{
    Int               count = -1;
    return (count);
}

/* Initializes a message not obtained from MessageQ_alloc. */
Void MessageQ_staticMsgInit (MessageQ_Msg msg, UInt32 size)
{
    /* Fill in the fields of the message */
    MessageQ_msgInit (msg);
    msg->heapId  = MessageQ_STATICMSG;
    msg->msgSize = size;
}

/*
 * Allocate a message and initialize the needed fields (note some
 * of the fields in the header are set via other APIs or in the
 * MessageQ_put function,
 */
MessageQ_Msg MessageQ_alloc (UInt16 heapId, UInt32 size)
{
    MessageQ_Msg msg       = NULL;

    /*
     * heapId not used for local alloc (as this is over a copy transport), but
     * we need to send to other side as heapId is used in BIOS transport:
     */
    msg = (MessageQ_Msg)calloc (1, size);
    MessageQ_msgInit (msg);
    msg->msgSize = size;
    msg->heapId  = heapId;

    return msg;
}

/* Frees the message back to the heap that was used to allocate it. */
Int MessageQ_free (MessageQ_Msg msg)
{
    UInt32         status = MessageQ_S_SUCCESS;

    /* Check to ensure this was not allocated by user: */
    if (msg->heapId == MessageQ_STATICMSG)  {
        status =  MessageQ_E_CANNOTFREESTATICMSG;
    }
    else {
        free (msg);
    }

    return status;
}

/* Register a heap with MessageQ. */
Int MessageQ_registerHeap (Ptr heap, UInt16 heapId)
{
    Int  status = MessageQ_S_SUCCESS;

    /* Do nothing, as this uses a copy transport: */

    return status;
}

/* Unregister a heap with MessageQ. */
Int MessageQ_unregisterHeap (UInt16 heapId)
{
    Int  status = MessageQ_S_SUCCESS;

    /* Do nothing, as this uses a copy transport: */

    return status;
}

/* Unblocks a MessageQ */
Void MessageQ_unblock (MessageQ_Handle handle)
{
    MessageQ_Object * obj   = (MessageQ_Object *) handle;
    char         buf = 'n';

    obj->unblocked = MessageQ_E_UNBLOCKED;

    /* Write to pipe to awaken any threads blocked on this messageQ: */
    write(obj->unblockFdW, &buf, 1);
}

/* Unblocks a MessageQ that's been shutdown due to transport failure */
Void MessageQ_shutdown(MessageQ_Handle handle)
{
    MessageQ_Object *obj = (MessageQ_Object *)handle;
    char         buf = 'n';

    obj->unblocked = MessageQ_E_SHUTDOWN;

    /* Write to pipe to awaken any threads blocked on this messageQ: */
    write(obj->unblockFdW, &buf, 1);
}

/* Embeds a source message queue into a message. */
Void MessageQ_setReplyQueue (MessageQ_Handle handle, MessageQ_Msg msg)
{
    MessageQ_Object * obj   = (MessageQ_Object *) handle;

    msg->replyId   = (UInt16)(obj->queue);
    msg->replyProc = (UInt16)(obj->queue >> 16);
}

/* Returns the QueueId associated with the handle. */
MessageQ_QueueId MessageQ_getQueueId (MessageQ_Handle handle)
{
    MessageQ_Object * obj = (MessageQ_Object *) handle;
    UInt32            queueId;

    queueId = (obj->queue);

    return queueId;
}

/* Sets the tracing of a message */
Void MessageQ_setMsgTrace (MessageQ_Msg msg, Bool traceFlag)
{
    msg->flags = (msg->flags & ~TRACEMASK) |   (traceFlag << TRACESHIFT);
}

/*
 *  Returns the amount of shared memory used by one transport instance.
 *
 *  The MessageQ module itself does not use any shared memory but the
 *  underlying transport may use some shared memory.
 */
SizeT MessageQ_sharedMemReq (Ptr sharedAddr)
{
    SizeT memReq = 0u;

    /* Do nothing, as this is a copy transport. */

    return (memReq);
}

/*
 *  Opens a file descriptor for this remote proc.
 *
 *  Only opens it if one does not already exist for this procId.
 *
 *  Note: remoteProcId may be MultiProc_Self() for loopback case.
 */
Int MessageQ_attach (UInt16 remoteProcId, Ptr sharedAddr)
{
    Int     status = MessageQ_S_SUCCESS;
    int     ipcFd;
    int     err;

    PRINTVERBOSE1("MessageQ_attach: remoteProcId: %d\n", remoteProcId)

    if (remoteProcId >= MultiProc_MAXPROCESSORS) {
        status = MessageQ_E_INVALIDPROCID;
        goto exit;
    }

    pthread_mutex_lock (&(MessageQ_module->gate));

    /* Only open a fd if one doesn't exist: */
    if (MessageQ_module->ipcFd[remoteProcId] == -1)  {
        /* Create a fd for sending messages to the remote proc: */
        ipcFd = open("/dev/tiipc", O_RDWR);
        if (ipcFd < 0) {
            status = MessageQ_E_FAIL;
            printf ("MessageQ_attach: open of tiipc device failed: %d, %s\n",
                       errno, strerror(errno));
        }
        else  {
            PRINTVERBOSE1("MessageQ_attach: opened tiipc fd for sending: %d\n",
                ipcFd)
            MessageQ_module->ipcFd[remoteProcId] = ipcFd;
            /*
             * Connect to the remote endpoint and bind any reserved address as
             * local endpoint
             */
            TiIpcFxns_connect(ipcFd, remoteProcId, MESSAGEQ_RPMSG_PORT);
            /* Bind to any port # above 1024 (MessageQCopy_MAXRESERVEDEPT) */
            err = TiIpcFxns_bindAddr(ipcFd, TIIPC_ADDRANY);
            if (err < 0) {
                status = MessageQ_E_FAIL;
                printf ("MessageQ_attach: bind failed: %d, %s\n",
                    errno, strerror(errno));
            }
        }
    }
    else {
        status = MessageQ_E_ALREADYEXISTS;
    }

    pthread_mutex_unlock (&(MessageQ_module->gate));

exit:
    return (status);
}

/*
 *  Close the fd for this remote proc.
 *
 */
Int MessageQ_detach (UInt16 remoteProcId)
{
    Int status = MessageQ_S_SUCCESS;
    int ipcFd;

    if (remoteProcId >= MultiProc_MAXPROCESSORS) {
        status = MessageQ_E_INVALIDPROCID;
        goto exit;
    }

    pthread_mutex_lock (&(MessageQ_module->gate));

    ipcFd = MessageQ_module->ipcFd[remoteProcId];
    if (close (ipcFd)) {
        status = MessageQ_E_OSFAILURE;
        printf("MessageQ_detach: close failed: %d, %s\n",
                       errno, strerror(errno));
    }
    else {
        PRINTVERBOSE1("MessageQ_detach: closed fd: %d\n", ipcFd)
        MessageQ_module->ipcFd[remoteProcId] = -1;
    }

    pthread_mutex_unlock (&(MessageQ_module->gate));

exit:
    return (status);
}

/*
 * This is a helper function to initialize a message.
 */
Void MessageQ_msgInit (MessageQ_Msg msg)
{
    msg->reserved0 = 0;  /* We set this to distinguish from NameServerMsg */
    msg->replyId   = (UInt16)MessageQ_INVALIDMESSAGEQ;
    msg->msgId     = MessageQ_INVALIDMSGID;
    msg->dstId     = (UInt16)MessageQ_INVALIDMESSAGEQ;
    msg->flags     = MessageQ_HEADERVERSION | MessageQ_NORMALPRI;
    msg->srcProc   = MultiProc_self();

    pthread_mutex_lock(&(MessageQ_module->gate));
    msg->seqNum  = MessageQ_module->seqNum++;
    pthread_mutex_unlock(&(MessageQ_module->gate));
}

/*
 * =============================================================================
 * Transport: Fxns kept here until need for a transport layer is realized.
 * =============================================================================
 */
/*
 * ======== transportCreateEndpoint ========
 *
 * Create a communication endpoint to receive messages.
 */
static Int transportCreateEndpoint(int * fd, UInt16 queuePort)
{
    Int          status    = MessageQ_S_SUCCESS;
    int          err;

    /* Create a fd to the ti-ipc to receive messages for this messageQ */
    *fd= open("/dev/tiipc", O_RDWR);
    if (*fd < 0) {
        status = MessageQ_E_FAIL;
        printf ("transportCreateEndpoint: Couldn't open tiipc device: %d, %s\n",
                  errno, strerror(errno));

        goto exit;
    }

    PRINTVERBOSE1("transportCreateEndpoint: opened fd: %d\n", *fd)

    /* Bind to this port # in the transport */
    err = TiIpcFxns_bindAddr(*fd, (UInt32)queuePort);
    if (err < 0) {
        status = MessageQ_E_FAIL;
        printf("transportCreateEndpoint: bind failed: %d, %s\n",
                  errno, strerror(errno));

        close(*fd);
        goto exit;
    }

exit:
    return (status);
}

/*
 * ======== transportCloseEndpoint ========
 *
 *  Close the communication endpoint.
 */
static Int transportCloseEndpoint(int fd)
{
    Int status = MessageQ_S_SUCCESS;

    PRINTVERBOSE1("transportCloseEndpoint: closing fd: %d\n", fd)

    /* Stop communication to this endpoint */
    close(fd);

    return (status);
}

/*
 * ======== transportGet ========
 *  Retrieve a message waiting in the queue.
*/
static Int transportGet(int fd, MessageQ_Msg * retMsg)
{
    Int           status    = MessageQ_S_SUCCESS;
    MessageQ_Msg  msg;
    int           ret;
    int           byteCount;
    tiipc_remote_params remote;

    /*
     * We have no way of peeking to see what message size we'll get, so we
     * allocate a message of max size to receive contents from tiipc
     * (currently, a copy transport)
     */
    msg = MessageQ_alloc (0, MESSAGEQ_RPMSG_MAXSIZE);
    if (!msg)  {
        status = MessageQ_E_MEMORY;
        goto exit;
    }

    /* Get message */
    byteCount = read(fd, msg, MESSAGEQ_RPMSG_MAXSIZE);
    if (byteCount < 0) {
        status = (errno == ESHUTDOWN ? MessageQ_E_SHUTDOWN : MessageQ_E_FAIL);
        printf("read failed: %s (%d)\n", strerror(errno), errno);
        goto exit;
    }
    else {
         /* Update the allocated message size (even though this may waste space
          * when the actual message is smaller than the maximum rpmsg size,
          * the message will be freed soon anyway, and it avoids an extra copy).
          */
         msg->msgSize = byteCount;

         /*
          * If the message received was statically allocated, reset the
          * heapId, so the app can free it.
          */
         if (msg->heapId == MessageQ_STATICMSG)  {
             msg->heapId = 0;  /* for a copy transport, heap id is 0. */
         }
    }

    PRINTVERBOSE1("transportGet: read from fd: %d\n", fd)
    ret = ioctl(fd, TIIPC_IOCGETREMOTE, &remote);
    if (ret == -1) {
        printf("ioctl failed: %s (%d)\n", strerror(errno), errno);
        status = MessageQ_E_FAIL;
        goto exit;
    }
    PRINTVERBOSE3("\tReceived a msg: byteCount: %d, rpmsg addr: %d, rpmsg \
        proc: %d\n", byteCount, remote.remote_addr, remote.remote_proc)
    PRINTVERBOSE2("\tMessage Id: %d, Message size: %d\n", msg->msgId,
        msg->msgSize)

    *retMsg = msg;

exit:
    return (status);
}

/*
 * ======== transportPut ========
 *
 * Write to tiipc file descriptor associated with
 * with this destination procID.
 */
static Int transportPut(MessageQ_Msg msg, UInt16 dstId, UInt16 dstProcId)
{
    Int     status    = MessageQ_S_SUCCESS;
    int     ipcFd;
    int     err;

    /*
     * Retrieve the tiipc file descriptor associated with this
     * transport for the destination processor.
     */
    ipcFd = MessageQ_module->ipcFd[dstProcId];

    PRINTVERBOSE2("Sending msgId: %d via fd: %d\n", msg->msgId, ipcFd)

    /* send response message to remote processor */
    err = write(ipcFd, msg, msg->msgSize);
    if (err < 0) {
        status = (errno == ESHUTDOWN ? MessageQ_E_SHUTDOWN : MessageQ_E_FAIL);
        printf ("transportPut: write failed: %d, %s\n",
                  errno, strerror(errno));
        goto exit;
    }

    /*
     * Free the message, as this is a copy transport, we maintain MessageQ
     * semantics.
     */
    MessageQ_free (msg);

exit:
    return (status);
}
