/*
 * Copyright (c) 2014-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  Implementation of functions specified in the IMessageQTransport interface.
 */

/* Socket Headers */
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/eventfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>


/* Socket Protocol Family */
#include <net/rpmsg.h>


/* IPC headers */
#include <ti/ipc/Std.h>
#include <SocketFxns.h>         /* Socket utils: */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/transports/TransportRpmsg.h>
#include <_MessageQ.h>
#include <_lad.h>

#if !defined(EFD_SEMAPHORE)
#  define EFD_SEMAPHORE (1 << 0)
#endif

/* More magic rpmsg port numbers: */
#define MESSAGEQ_RPMSG_PORT       61
#define MESSAGEQ_RPMSG_MAXSIZE   512

#define TransportRpmsg_GROWSIZE 32
#define INVALIDSOCKET (-1)

#define TransportRpmsg_Event_ACK        (1 << 0)
#define TransportRpmsg_Event_PAUSE      (1 << 1)
#define TransportRpmsg_Event_CONTINUE   (1 << 2)
#define TransportRpmsg_Event_SHUTDOWN   (1 << 3)


#define _MAX(a,b) (((a)>(b))?(a):(b))

/* traces in this file are controlled via _TransportMessageQ_verbose */
Bool _TransportMessageQ_verbose = FALSE;
#define verbose _TransportMessageQ_verbose

Int TransportRpmsg_bind(Void *handle, UInt32 queueId);
Int TransportRpmsg_unbind(Void *handle, UInt32 queueId);
Bool TransportRpmsg_put(Void *handle, Ptr msg);

typedef struct TransportRpmsg_Module {
    int             sock[MultiProc_MAXPROCESSORS];
    fd_set          rfds;
    int             maxFd;
    struct {
        int     fd;
        UInt32  qId;
    } inFds[1024];
    int	            nInFds;
    pthread_mutex_t gate;
    int             unblockEvent;    /* unblock the dispatch thread */
    int             waitEvent;       /* block the client thread */
    pthread_t       threadId;        /* ID returned by pthread_create() */
    Bool            threadStarted;

    TransportRpmsg_Handle *inst;    /* array of instances */
} TransportRpmsg_Module;

IMessageQTransport_Fxns TransportRpmsg_fxns = {
    .bind    = TransportRpmsg_bind,
    .unbind  = TransportRpmsg_unbind,
    .put     = TransportRpmsg_put
};

typedef struct TransportRpmsg_Object {
    IMessageQTransport_Object base;
    Int status;
    UInt16 rprocId;
    int numQueues;
    int *qIndexToFd;
} TransportRpmsg_Object;

TransportRpmsg_Module TransportRpmsg_state = {
    .sock = {INVALIDSOCKET},
    .unblockEvent = -1,
    .waitEvent = -1,
    .threadStarted = FALSE,
    .inst = NULL
};
TransportRpmsg_Module *TransportRpmsg_module = &TransportRpmsg_state;

static void *rpmsgThreadFxn(void *arg);
static Int transportGet(int sock, MessageQ_Msg *retMsg);
static Void bindFdToQueueIndex(TransportRpmsg_Object *obj,
                               Int fd,
                               UInt16 qIndex);
static Void unbindQueueIndex(TransportRpmsg_Object *obj, UInt16 qIndex);
static Int queueIndexToFd(TransportRpmsg_Object *obj, UInt16 qIndex);

/* factory functions */
Int TransportRpmsg_Factory_create(Void);
Void TransportRpmsg_Factory_delete(Void);
Int TransportRpmsg_Factory_attach(UInt16 procId);
Int TransportRpmsg_Factory_detach(UInt16 procId);

Ipc_TransportFactoryFxns TransportRpmsg_Factory = {
    .createFxn = TransportRpmsg_Factory_create,
    .deleteFxn = TransportRpmsg_Factory_delete,
    .attachFxn = TransportRpmsg_Factory_attach,
    .detachFxn = TransportRpmsg_Factory_detach
};

/* -------------------------------------------------------------------------- */

/* instance convertors */
IMessageQTransport_Handle TransportRpmsg_upCast(TransportRpmsg_Handle handle)
{
    TransportRpmsg_Object *obj = (TransportRpmsg_Object *)handle;
    return ((IMessageQTransport_Handle)&obj->base);
}

TransportRpmsg_Handle TransportRpmsg_downCast(IMessageQTransport_Handle base)
{
    return ((TransportRpmsg_Handle)base);
}

/*
 *  ======== TransportRpmsg_create ========
 */
TransportRpmsg_Handle TransportRpmsg_create(TransportRpmsg_Params *params)
{
    Int status = MessageQ_S_SUCCESS;
    TransportRpmsg_Object *obj = NULL;
    int sock;
    int flags;
    UInt16 clusterId;
    int i;


    clusterId = params->rprocId - MultiProc_getBaseIdOfCluster();

    /* create socket for sending messages to remote processor */
    sock = socket(AF_RPMSG, SOCK_SEQPACKET, 0);

    if (sock < 0) {
        status = Ipc_E_FAIL;
        fprintf(stderr,
                "TransportRpmsg_create: socket failed: %d (%s)\n", errno,
                strerror(errno));
        goto done;
    }
    TransportRpmsg_module->sock[clusterId] = sock;
    PRINTVERBOSE1("attach: created send socket: %d\n", sock)

    status = ConnectSocket(sock, params->rprocId, MESSAGEQ_RPMSG_PORT);

    if (status < 0) {
        status = Ipc_E_FAIL;
        fprintf(stderr,
                "TransportRpmsg_create: connect failed: %d (%s) procId: %d\n",
                errno, strerror(errno), params->rprocId);
        close(sock);
        TransportRpmsg_module->sock[clusterId] = INVALIDSOCKET;
        goto done;
    }

    /* make sure socket fd doesn't exist for 'fork() -> exec*()'ed child */
    flags = fcntl(sock, F_GETFD);
    if (flags != -1) {
        fcntl(sock, F_SETFD, flags | FD_CLOEXEC);
    }

    /* create the instance object */
    obj = calloc(1, sizeof(TransportRpmsg_Object));

    if (obj == NULL) {
        status = Ipc_E_MEMORY;
        close(sock);
        TransportRpmsg_module->sock[clusterId] = INVALIDSOCKET;
        goto done;
    }

    /* initialize the instance */
    obj->base.base.interfaceType = IMessageQTransport_TypeId;
    obj->base.fxns = &TransportRpmsg_fxns;
    obj->rprocId = params->rprocId;
    obj->numQueues = TransportRpmsg_GROWSIZE;

    obj->qIndexToFd = calloc(TransportRpmsg_GROWSIZE, sizeof(int));

    if (obj->qIndexToFd == NULL) {
        status = Ipc_E_MEMORY;
        goto done;
    }

    /* must initialize array */
    for (i = 0; i < TransportRpmsg_GROWSIZE; i++) {
        obj->qIndexToFd[i] = -1;
    }

done:
    if (status < 0) {
        TransportRpmsg_delete((TransportRpmsg_Handle *)&obj);
    }

    return (TransportRpmsg_Handle)obj;
}

/*
 *  ======== TransportRpmsg_delete ========
 */
Void TransportRpmsg_delete(TransportRpmsg_Handle *pHandle)
{
    TransportRpmsg_Object *obj = *(TransportRpmsg_Object **)pHandle;
    UInt16 clusterId;
    int sock;

    if (obj == NULL) {
        goto done;
    }

    clusterId = obj->rprocId - MultiProc_getBaseIdOfCluster();

    /* close the socket for the given transport instance */
    sock = TransportRpmsg_module->sock[clusterId];
    if (sock != INVALIDSOCKET) {
        PRINTVERBOSE1("detach: closing socket: %d\n", sock)
        close(sock);
    }
    TransportRpmsg_module->sock[clusterId] = INVALIDSOCKET;

    if ((obj != NULL) && (obj->qIndexToFd != NULL)) {
        free(obj->qIndexToFd);
        obj->qIndexToFd = NULL;
    }

    if (obj != NULL) {
        free(obj);
        obj = NULL;
    }

done:
    *pHandle = NULL;
}

/*
 *  ======== TransportRpmsg_bind ========
 */
Int TransportRpmsg_bind(Void *handle, UInt32 queueId)
{
    TransportRpmsg_Object *obj = (TransportRpmsg_Object *)handle;
    UInt16 queuePort = queueId & 0x0000ffff;
    int fd;
    int flags;
    int err;
    uint64_t event;
    UInt16 rprocId;
    pthread_t tid;
    Int status = MessageQ_S_SUCCESS;

    tid = pthread_self();
    rprocId = obj->rprocId;

    PRINTVERBOSE3("TransportRpmsg_bind: creating endpoint for rprocId %d "
            "queuePort 0x%x, tid=0x%x\n", rprocId, queuePort, (unsigned int)tid)

    pthread_mutex_lock(&TransportRpmsg_module->gate);

    /*  Check if binding already exists.
     *
     *  There is a race condition between a thread calling MessageQ_create
     *  and another thread calling Ipc_attach. Must make sure we don't bind
     *  the same queue twice.
     */
    if (queueIndexToFd(obj, queueId) != -1) {
        goto done;
    }

    /*  Create the socket to receive messages for this messageQ. */
    fd = socket(AF_RPMSG, SOCK_SEQPACKET, 0);
    if (fd < 0) {
        fprintf(stderr, "TransportRpmsg_bind: socket call failed: %d (%s)\n",
                errno, strerror(errno));
        status = MessageQ_E_OSFAILURE;
        goto done;
    }
    PRINTVERBOSE2("TransportRpmsg_bind: created socket fd %d, tdi=0x%x\n", fd,
            (unsigned int)tid);

    err = SocketBindAddr(fd, rprocId, (UInt32)queuePort);
    if (err < 0) {
        /* don't hard-printf since this is no longer fatal */
        PRINTVERBOSE2("TransportRpmsg_bind: bind failed: %d (%s)\n",
                      errno, strerror(errno));
        close(fd);
        status = MessageQ_E_OSFAILURE;
        goto done;
    }

    /* make sure socket fd doesn't exist for 'fork() -> exec*()'ed child */
    flags = fcntl(fd, F_GETFD);
    if (flags != -1) {
        fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
    }

    /*  pause the dispatch thread */
    PRINTVERBOSE1("TransportRpmsg_bind: sending PAUSE event, tid=0x%x\n",
            (unsigned int)tid);
    event = TransportRpmsg_Event_PAUSE;
    write(TransportRpmsg_module->unblockEvent, &event, sizeof(event));

    /* wait for ACK event */
    read(TransportRpmsg_module->waitEvent, &event, sizeof(event));
    PRINTVERBOSE2("TransportRpmsg_bind: received ACK event (%d), tid=0x%x\n",
            (int)event, (unsigned int)tid);

    /* add to our fat fd array and update select() parameters */
    TransportRpmsg_module->inFds[TransportRpmsg_module->nInFds].fd = fd;
    TransportRpmsg_module->inFds[TransportRpmsg_module->nInFds++].qId = queueId;
    TransportRpmsg_module->maxFd = _MAX(TransportRpmsg_module->maxFd, fd);
    FD_SET(fd, &TransportRpmsg_module->rfds);
    bindFdToQueueIndex(obj, fd, queuePort);

    /* release the dispatch thread */
    PRINTVERBOSE1("TransportRpmsg_bind: sending CONTINUE event, tid=0x%x\n",
            (unsigned int)tid);
    event = TransportRpmsg_Event_CONTINUE;
    write(TransportRpmsg_module->unblockEvent, &event, sizeof(event));

done:
    pthread_mutex_unlock(&TransportRpmsg_module->gate);

    return (status);
}

/*
 *  ======== TransportRpmsg_unbind ========
 */
Int TransportRpmsg_unbind(Void *handle, UInt32 queueId)
{
    TransportRpmsg_Object *obj = (TransportRpmsg_Object *)handle;
    UInt16 queuePort = queueId & 0x0000ffff;
    uint64_t event;
    Int    status = MessageQ_S_SUCCESS;
    int    maxFd;
    int    fd;
    int    i;
    int    j;

    pthread_mutex_lock(&TransportRpmsg_module->gate);

    /*  pause the dispatch thread */
    event = TransportRpmsg_Event_PAUSE;
    write(TransportRpmsg_module->unblockEvent, &event, sizeof(event));

    /* wait for ACK event */
    read(TransportRpmsg_module->waitEvent, &event, sizeof(event));

    /*  Check if binding already deleted.
     *
     *  There is a race condition between a thread calling MessageQ_delete
     *  and another thread calling Ipc_detach. Must make sure we don't unbind
     *  the same queue twice.
     */
    if ((fd = queueIndexToFd(obj, queuePort)) == -1) {
        goto done;
    }
    PRINTVERBOSE1("TransportRpmsg_unbind: closing socket %d\n", fd)

    /* guarenteed to work because queueIndexToFd above succeeded */
    unbindQueueIndex(obj, queuePort);

    /* remove from input fd array */
    for (i = 0; i < TransportRpmsg_module->nInFds; i++) {
        if (TransportRpmsg_module->inFds[i].fd == fd) {
            TransportRpmsg_module->nInFds--;

            /* shift subsequent elements down */
            for (j = i; j < TransportRpmsg_module->nInFds; j++) {
                TransportRpmsg_module->inFds[j] =
                        TransportRpmsg_module->inFds[j + 1];
            }
            TransportRpmsg_module->inFds[TransportRpmsg_module->nInFds].fd = -1;
            TransportRpmsg_module->inFds[TransportRpmsg_module->nInFds].qId = 0;
            break;
        }
    }

    /* remove fd from the descriptor set, compute new max value */
    FD_CLR(fd, &TransportRpmsg_module->rfds);
    if (fd == TransportRpmsg_module->maxFd) {
        /* find new max fd */
        maxFd = TransportRpmsg_module->unblockEvent;
        for (i = 0; i < TransportRpmsg_module->nInFds; i++) {
            maxFd = _MAX(TransportRpmsg_module->inFds[i].fd, maxFd);
        }
        TransportRpmsg_module->maxFd = maxFd;
    }

    close(fd);

    /* release the dispatch thread */
    event = TransportRpmsg_Event_CONTINUE;
    write(TransportRpmsg_module->unblockEvent, &event, sizeof(event));

done:
    pthread_mutex_unlock(&TransportRpmsg_module->gate);

    return (status);
}

/*
 *  ======== TransportRpmsg_put ========
 */
Bool TransportRpmsg_put(Void *handle, Ptr pmsg)
{
    MessageQ_Msg msg  = (MessageQ_Msg)pmsg;
    Int     status    = TRUE;
    int     sock;
    int     err;
    UInt16  clusterId;

    /*
     * Retrieve the socket for the AF_SYSLINK protocol associated with this
     * transport.
     */
    clusterId = msg->dstProc - MultiProc_getBaseIdOfCluster();
    sock = TransportRpmsg_module->sock[clusterId];
    if (!sock) {
        return FALSE;
    }

    PRINTVERBOSE2("Sending msgId: %d via sock: %d\n", msg->msgId, sock)

    err = send(sock, msg, msg->msgSize, 0);
    if (err < 0) {
        fprintf(stderr, "TransportRpmsg_put: send failed: %d (%s)\n",
                errno, strerror(errno));
        status = FALSE;

        goto exit;
    }

    /*
     * Free the message, as this is a copy transport, we maintain MessageQ
     * semantics.
     */
    MessageQ_free(msg);

exit:
    return status;
}

/*
 *  ======== TransportRpmsg_control ========
 */
Bool TransportRpmsg_control(Void *handle, UInt cmd, UArg cmdArg)
{
    return FALSE;
}

/*
 *  ======== rpmsgThreadFxn ========
 */
void *rpmsgThreadFxn(void *arg)
{
    Int      status = MessageQ_S_SUCCESS;
    Int      tmpStatus;
    int      retval;
    uint64_t event;
    fd_set   rfds;
    int      maxFd;
    int      nfds;
    MessageQ_Msg     retMsg;
    MessageQ_QueueId queueId;
    MessageQ_Handle handle;
    Bool run = TRUE;
    int i;
    int j;
    int fd;


    while (run) {
        maxFd = TransportRpmsg_module->maxFd;
        rfds = TransportRpmsg_module->rfds;
        nfds = TransportRpmsg_module->nInFds;

        PRINTVERBOSE3("rpmsgThreadFxn: maxFd %d rfds[1:0] 0x%08x%08x\n", maxFd,
                (int)rfds.fds_bits[1], (int)rfds.fds_bits[0])

        retval = select(maxFd + 1, &rfds, NULL, NULL, NULL);

        /* if error, try again */
        if (retval < 0) {
            printf("Warning: rpmsgThreadFxn: select failed, trying again\n");
            continue;
        }

        /* dispatch all pending messages, do this first */
        for (i = 0; i < nfds; i++) {
            fd = TransportRpmsg_module->inFds[i].fd;

            if (FD_ISSET(fd, &rfds)) {
                PRINTVERBOSE1("rpmsgThreadFxn: getting from fd %d\n",
                        TransportRpmsg_module->inFds[i].fd);

                /* transport input fd was signalled: get the message */
                tmpStatus = transportGet(fd, &retMsg);
                if (tmpStatus < 0 && tmpStatus != MessageQ_E_SHUTDOWN) {
                    fprintf(stderr,
                            "rpmsgThreadFxn: transportGet failed on fd %d, "
                            "returned %d\n", fd, tmpStatus);
                }
                else if (tmpStatus == MessageQ_E_SHUTDOWN) {
                    fprintf(stderr,
                            "rpmsgThreadFxn: transportGet failed on fd %d, "
                            "returned %d\n", fd, tmpStatus);

                    pthread_mutex_lock(&TransportRpmsg_module->gate);

                    /*
                     * Don't close(fd) at this time since it will get closed
                     * later when MessageQ_delete() is called in response to
                     * this failure.  Just remove fd's bit from the select mask
                     * 'rfds' for now, but don't remove it from inFds[].
                     */
                    FD_CLR(fd, &TransportRpmsg_module->rfds);
                    if (fd == TransportRpmsg_module->maxFd) {
                        /* find new max fd */
                        maxFd = TransportRpmsg_module->unblockEvent;
                        for (j = 0; j < TransportRpmsg_module->nInFds; j++) {
                            maxFd = _MAX(TransportRpmsg_module->inFds[j].fd,
                                         maxFd);
                        }
                        TransportRpmsg_module->maxFd = maxFd;
                    }
                    queueId = TransportRpmsg_module->inFds[i].qId;

                    pthread_mutex_unlock(&TransportRpmsg_module->gate);

                    handle = MessageQ_getLocalHandle(queueId);

                    PRINTVERBOSE2("rpmsgThreadFxn: shutting down MessageQ "
                                  "%p (queueId 0x%x)...\n", handle, queueId)

                    if (handle != NULL) {
                        MessageQ_shutdown(handle);
                    }
                    else {
                        fprintf(stderr,
                                "rpmsgThreadFxn: MessageQ_getLocalHandle(0x%x) "
                                "returned NULL, can't shutdown\n", queueId);
                    }
                }
                else {
                    queueId = MessageQ_getDstQueue(retMsg);
                    PRINTVERBOSE1("rpmsgThreadFxn: got message, "
                            "delivering to queueId 0x%x\n", queueId)
                    MessageQ_put(queueId, retMsg);
                }
            }
        }

        /* check for events */
        if (FD_ISSET(TransportRpmsg_module->unblockEvent, &rfds)) {

            read(TransportRpmsg_module->unblockEvent, &event, sizeof(event));

            do {
                if (event & TransportRpmsg_Event_SHUTDOWN) {
                    PRINTVERBOSE0("rpmsgThreadFxn: event SHUTDOWN\n");
                    run = FALSE;
                    break; /* highest priority, stop processing events */
                }
                if (event & TransportRpmsg_Event_CONTINUE) {
                    PRINTVERBOSE1("rpmsgThreadFxn: event CONTINUE (%d)\n",
                            (int)event);
                    event &= ~TransportRpmsg_Event_CONTINUE;
                }
                if (event & TransportRpmsg_Event_PAUSE) {
                    /*  Our event was signalled by TransportRpmsg_bind()
                     *  or TransportRpmsg_unbind() to tell us that the set
                     *  of file descriptors has changed.
                     */
                    PRINTVERBOSE0("rpmsgThreadFxn: event PAUSE\n");
                    /* send the acknowledgement */
                    event = TransportRpmsg_Event_ACK;
                    write(TransportRpmsg_module->waitEvent, &event,
                            sizeof(event));
                    /* now wait to be released */
                    read(TransportRpmsg_module->unblockEvent, &event,
                            sizeof(event));
                }
            } while (event != 0);
        }
    }

    return (void *)status;
}

/*
 * ======== transportGet ========
 *  Retrieve a message waiting in the socket's queue.
 */
static Int transportGet(int sock, MessageQ_Msg *retMsg)
{
    Int           status    = MessageQ_S_SUCCESS;
    MessageQ_Msg  msg;
    struct sockaddr_rpmsg fromAddr;  /* [Socket address of sender] */
    unsigned int  len;
    int           byteCount;

    /*
     * We have no way of peeking to see what message size we'll get, so we
     * allocate a message of max size to receive contents from the rpmsg socket
     * (currently, a copy transport)
     */
    msg = MessageQ_alloc(0, MESSAGEQ_RPMSG_MAXSIZE);
    if (!msg) {
        status = MessageQ_E_MEMORY;
        goto exit;
    }

    memset(&fromAddr, 0, sizeof (fromAddr));
    len = sizeof (fromAddr);

    byteCount = recvfrom(sock, msg, MESSAGEQ_RPMSG_MAXSIZE, 0,
                         (struct sockaddr *)&fromAddr, &len);
    if (len != sizeof (fromAddr)) {
        fprintf(stderr, "recvfrom: got bad addr len (%d)\n", len);
        status = MessageQ_E_FAIL;
        goto freeMsg;
    }
    if (byteCount < 0) {
        fprintf(stderr, "recvfrom failed: %s (%d)\n", strerror(errno), errno);
        if (errno == ENOLINK) {
            status = MessageQ_E_SHUTDOWN;
        }
        else {
            status = MessageQ_E_FAIL;
        }
        goto freeMsg;
    }
    else {
         /*
          * Update the allocated message size (even though this may waste
          * space when the actual message is smaller than the maximum rpmsg
          * size, the message will be freed soon anyway, and it avoids an
          * extra copy).
          */
         msg->msgSize = byteCount;

         /* set the heapId in the message header to match allocation above */
         msg->heapId = 0;
    }

    PRINTVERBOSE1("transportGet: recvfrom socket: fd: %d\n", sock)
    PRINTVERBOSE3("\tReceived a msg: byteCount: %d, rpmsg addr: %d, rpmsg "
            "proc: %d\n", byteCount, fromAddr.addr, fromAddr.vproc_id)
    PRINTVERBOSE2("\tMessage Id: %d, Message size: %d\n", msg->msgId,
            msg->msgSize)

    *retMsg = msg;

    goto exit;

freeMsg:
    MessageQ_free(msg);

exit:
    return status;
}

/*
 *  ======== bindFdToQueueIndex ========
 *
 *  Precondition: caller must be inside the module gate
 */
Void bindFdToQueueIndex(TransportRpmsg_Object *obj, Int fd, UInt16 queuePort)
{
    Int *queues;
    Int *oldQueues;
    UInt oldSize;
    UInt newCount;
    UInt queueIndex;
    int i;

    /* subtract port offset from queue index */
    queueIndex = queuePort - MessageQ_PORTOFFSET;

    if (queueIndex >= obj->numQueues) {
        newCount = queueIndex + TransportRpmsg_GROWSIZE;
        PRINTVERBOSE1("TransportRpmsg_bind: growing numQueues to %d\n",
                newCount);

        /* allocate larger table */
        oldSize = obj->numQueues * sizeof(int);
        queues = calloc(newCount, sizeof(int));

        /* copy contents from old table int new table */
        memcpy(queues, obj->qIndexToFd, oldSize);

        /* initialize remaining entries of new (larger) table */
        for (i = obj->numQueues; i < newCount; i++) {
            queues[i] = -1;
        }

        /* swap in new table, delete old table */
        oldQueues = obj->qIndexToFd;
        obj->qIndexToFd = queues;
        obj->numQueues = newCount;
        free(oldQueues);
    }

    /* add new entry */
    obj->qIndexToFd[queueIndex] = fd;
}

/*
 *  ======== unbindQueueIndex ========
 *
 *  Precondition: caller must be inside the module gate
 */
Void unbindQueueIndex(TransportRpmsg_Object *obj, UInt16 queuePort)
{
    UInt queueIndex;

    /* subtract port offset from queue index */
    queueIndex = queuePort - MessageQ_PORTOFFSET;

    /* clear table entry */
    obj->qIndexToFd[queueIndex] = -1;
}

/*
 *  ======== queueIndexToFd ========
 *
 *  Precondition: caller must be inside the module gate
 */
Int queueIndexToFd(TransportRpmsg_Object *obj, UInt16 queuePort)
{
    UInt queueIndex;

    /* subtract port offset from queue index */
    queueIndex = queuePort - MessageQ_PORTOFFSET;

    /* return file descriptor */
    return (obj->qIndexToFd[queueIndex]);
}

/*
 *  ======== TransportRpmsg_Factory_create ========
 *  Create the transport instances
 *
 *  Attach to all remote processors. For now, must attach to
 *  at least one to tolerate MessageQ_E_RESOURCE failures.
 *
 *  This function implements the IPC Factory interface, so it
 *  returns Ipc status codes.
 */
Int TransportRpmsg_Factory_create(Void)
{
    Int status = Ipc_S_SUCCESS;
    Int i;
    UInt16 clusterSize;
    TransportRpmsg_Handle *inst;
    int flags;


    /* needed to enumerate processors in cluster */
    clusterSize = MultiProc_getNumProcsInCluster();

    /* allocate the instance array */
    inst = calloc(clusterSize, sizeof(TransportRpmsg_Handle));

    if (inst == NULL) {
        fprintf(stderr,
                "Error: TransportRpmsg_Factory_create failed, no memory\n");
        status = Ipc_E_MEMORY;
        goto done;
    }

    for (i = 0; i < clusterSize; i++) {
        inst[i] = NULL;
    }

    TransportRpmsg_module->inst = inst;

    /* counter event object for passing commands to dispatch thread */
    TransportRpmsg_module->unblockEvent = eventfd(0, 0);

    if (TransportRpmsg_module->unblockEvent == -1) {
        fprintf(stderr, "create: unblock event failed: %d (%s)\n",
                errno, strerror(errno));
        status = Ipc_E_FAIL;
        goto done;
    }

    PRINTVERBOSE1("create: created unblock event %d\n",
            TransportRpmsg_module->unblockEvent)

    /* semaphore event object for acknowledging client thread */
    TransportRpmsg_module->waitEvent = eventfd(0, EFD_SEMAPHORE);

    if (TransportRpmsg_module->waitEvent == -1) {
        fprintf(stderr,
                "create: wait event failed: %d (%s)\n", errno, strerror(errno));
        status = Ipc_E_FAIL;
        goto done;
    }

    PRINTVERBOSE1("create: created wait event %d\n",
            TransportRpmsg_module->waitEvent)

    /* make sure eventfds don't exist for 'fork() -> exec*()'ed child */
    flags = fcntl(TransportRpmsg_module->waitEvent, F_GETFD);
    if (flags != -1) {
        fcntl(TransportRpmsg_module->waitEvent, F_SETFD, flags | FD_CLOEXEC);
    }
    flags = fcntl(TransportRpmsg_module->unblockEvent, F_GETFD);
    if (flags != -1) {
        fcntl(TransportRpmsg_module->unblockEvent, F_SETFD, flags | FD_CLOEXEC);
    }

    FD_ZERO(&TransportRpmsg_module->rfds);
    FD_SET(TransportRpmsg_module->unblockEvent,
            &TransportRpmsg_module->rfds);
    TransportRpmsg_module->maxFd = TransportRpmsg_module->unblockEvent;
    TransportRpmsg_module->nInFds = 0;

    pthread_mutex_init(&TransportRpmsg_module->gate, NULL);

    status = pthread_create(&TransportRpmsg_module->threadId, NULL,
            &rpmsgThreadFxn, NULL);

    if (status < 0) {
        status = Ipc_E_FAIL;
        fprintf(stderr, "create: failed to spawn thread\n");
        goto done;
    }
    TransportRpmsg_module->threadStarted = TRUE;

done:
    if (status < 0) {
        TransportRpmsg_Factory_delete();
    }

    return (status);
}

/*
 *  ======== TransportRpmsg_Factory_delete ========
 *  Finalize the transport instances
 */
Void TransportRpmsg_Factory_delete(Void)
{
    uint64_t event;


    /* shutdown the message dispatch thread */
    if (TransportRpmsg_module->threadStarted) {
        event = TransportRpmsg_Event_SHUTDOWN;
        write(TransportRpmsg_module->unblockEvent, &event, sizeof(event));

        /* wait for dispatch thread to exit */
        pthread_join(TransportRpmsg_module->threadId, NULL);
    }

    /* destroy the mutex object */
    pthread_mutex_destroy(&TransportRpmsg_module->gate);

    /* close the client wait event */
    if (TransportRpmsg_module->waitEvent != -1) {
        close(TransportRpmsg_module->waitEvent);
        TransportRpmsg_module->waitEvent = -1;
    }

    /* close the dispatch thread unblock event */
    if (TransportRpmsg_module->unblockEvent != -1) {
        close(TransportRpmsg_module->unblockEvent);
        TransportRpmsg_module->unblockEvent = -1;
    }

    /* free the instance handle array */
    if (TransportRpmsg_module->inst != NULL) {
        free(TransportRpmsg_module->inst);
        TransportRpmsg_module->inst = NULL;
    }

    return;
}

/*
 *  ======== TransportRpmsg_Factory_attach ========
 */
Int TransportRpmsg_Factory_attach(UInt16 procId)
{
    Int status = Ipc_S_SUCCESS;
    UInt16 clusterId;
    TransportRpmsg_Params params;
    TransportRpmsg_Handle transport;
    IMessageQTransport_Handle iMsgQTrans;

    /* cannot attach to yourself */
    if (MultiProc_self() == procId) {
        status = Ipc_E_INVALIDARG;
        goto done;
    }

    /* processor must be a member of the cluster */
    clusterId = procId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_getNumProcsInCluster()) {
        status = Ipc_E_INVALIDARG;
        goto done;
    }

    /* create transport instance for given processor */
    params.rprocId = procId;
    transport = TransportRpmsg_create(&params);

    if (transport == NULL) {
        status = Ipc_E_FAIL;
        goto done;
    }

    /* register transport instance with MessageQ */
    iMsgQTrans = TransportRpmsg_upCast(transport);
    TransportRpmsg_module->inst[clusterId] = transport;
    MessageQ_registerTransport(iMsgQTrans, procId, 0);

done:
    return (status);
}

/*
 *  ======== TransportRpmsg_Factory_detach ========
 */
Int TransportRpmsg_Factory_detach(UInt16 procId)
{
    Int status = Ipc_S_SUCCESS;
    UInt16 clusterId;

    /* cannot detach from yourself */
    if (MultiProc_self() == procId) {
        status = Ipc_E_INVALIDARG;
        goto done;
    }

    /* processor must be a member of the cluster */
    clusterId = procId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_getNumProcsInCluster()) {
        status = Ipc_E_INVALIDARG;
        goto done;
    }

    /* must be attached in order to detach */
    if (TransportRpmsg_module->inst[clusterId] == NULL) {
        status = Ipc_E_INVALIDSTATE;
        goto done;
    }

    /* unregister from MessageQ, delete the transport instance */
    MessageQ_unregisterTransport(procId, 0);
    TransportRpmsg_delete(&(TransportRpmsg_module->inst[clusterId]));

done:
    return (status);
}
