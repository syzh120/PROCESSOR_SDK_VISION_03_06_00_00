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
/*============================================================================
 *  @file   MessageQ.c
 *
 *  @brief  MessageQ module "server" implementation
 *
 *  This implementation is geared for use in a "client/server" model, whereby
 *  system-wide data is maintained here as needed and process-specific data
 *  is handled at the "client" level.  At the moment, LAD is the only "user"
 *  of this implementation.
 */


/* Standard IPC headers */
#include <ti/ipc/Std.h>

/* POSIX thread support */
#include <pthread.h>

/* Socket Headers */
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/eventfd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

/* Socket Protocol Family */
#include <net/rpmsg.h>

/* Module level headers */
#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>
#include <ti/ipc/MessageQ.h>
#include <_MessageQ.h>

#include <_lad.h>

/* =============================================================================
 * Macros/Constants
 * =============================================================================
 */

/*!
 *  @brief  Name of the reserved NameServer used for MessageQ.
 */
#define MessageQ_NAMESERVER  "MessageQ"

/* Number of entries to grow when we run out of queueIndexs */
#define MessageQ_GROWSIZE 32

/* Define BENCHMARK to quiet key MessageQ APIs: */
//#define BENCHMARK

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */

/* structure for MessageQ module state */
typedef struct MessageQ_ModuleObject {
    Int                 refCount;
    /*!< Reference count */
    NameServer_Handle   nameServer;
    /*!< Handle to the local NameServer used for storing GP objects */
    pthread_mutex_t     gate;
    /*!< Handle of gate to be used for local thread safety */
    MessageQ_Config    *cfg;
    /*!< Current config values */
    MessageQ_Params     defaultInstParams;
    /*!< Default instance creation parameters */
    MessageQ_Handle *   queues;
    /*!< Global array of message queues */
    UInt16              numQueues;
    /*!< Initial number of messageQ objects allowed */
    Bool                canFreeQueues;
    /*!< Grow option */
    Bits16              seqNum;
    /*!< sequence number */
} MessageQ_ModuleObject;

/*!
 *  @brief  Structure for the Handle for the MessageQ.
 */
typedef struct MessageQ_Object {
    MessageQ_Params         params;
    /*! Instance specific creation parameters */
    MessageQ_QueueId        queue;
    /* Unique id */
    Ptr                     nsKey;
    /* NameServer key */
    Int                     ownerPid;
    /* Process ID of owner */
} MessageQ_Object;


/* =============================================================================
 *  Globals
 * =============================================================================
 */
extern MessageQ_Config ti_ipc_MessageQ_cfg;

static MessageQ_ModuleObject MessageQ_state =
{
    .refCount               = 0,
    .nameServer             = NULL,
    .queues                 = NULL,
    .numQueues              = 2u,
    .canFreeQueues          = FALSE,
#if defined(IPC_BUILDOS_ANDROID) && (PLATFORM_SDK_VERSION < 23)
    .gate                   = PTHREAD_RECURSIVE_MUTEX_INITIALIZER,
#else
    .gate                   = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP,
#endif
    .cfg = &ti_ipc_MessageQ_cfg,
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
/* Grow the MessageQ table */
static UInt16 _MessageQ_grow(MessageQ_Object * obj);

/* =============================================================================
 * APIS
 * =============================================================================
 */
/* Function to get default configuration for the MessageQ module.
 *
 */
Void MessageQ_getConfig(MessageQ_Config * cfg)
{
    assert(cfg != NULL);

    memcpy(cfg, MessageQ_module->cfg, sizeof(MessageQ_Config));
}

/* Function to setup the MessageQ module. */
Int MessageQ_setup(const MessageQ_Config * cfg)
{
    Int                    status = MessageQ_S_SUCCESS;
    NameServer_Params      params;

    pthread_mutex_lock(&(MessageQ_module->gate));

    LOG1("MessageQ_setup: entered, refCount=%d\n", MessageQ_module->refCount)

    MessageQ_module->refCount++;
    if (MessageQ_module->refCount > 1) {
        status = MessageQ_S_ALREADYSETUP;
        LOG1("MessageQ module has been already setup, refCount=%d\n",
                MessageQ_module->refCount)
        goto exitSetup;
    }

    /* Initialize the parameters */
    NameServer_Params_init(&params);
    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen  = MessageQ_module->cfg->maxNameLen;

    /* Create the nameserver for modules */
    MessageQ_module->nameServer = NameServer_create(MessageQ_NAMESERVER,
                                                    &params);

    MessageQ_module->seqNum = 0;
    MessageQ_module->numQueues = MessageQ_module->cfg->maxRuntimeEntries;
    MessageQ_module->queues = (MessageQ_Handle *)
        calloc(1, sizeof(MessageQ_Handle) * MessageQ_module->numQueues);
    MessageQ_module->canFreeQueues = TRUE;

exitSetup:
    LOG1("MessageQ_setup: exiting, refCount=%d\n", MessageQ_module->refCount)

    pthread_mutex_unlock(&(MessageQ_module->gate));

    return (status);
}

/*
 * Function to destroy the MessageQ module.
 */
Int MessageQ_destroy(void)
{
    Int    status    = MessageQ_S_SUCCESS;
    UInt32 i;

    pthread_mutex_lock(&(MessageQ_module->gate));

    LOG1("MessageQ_destroy: entered, refCount=%d\n", MessageQ_module->refCount)

    /* Decrease the refCount */
    MessageQ_module->refCount--;
    if (MessageQ_module->refCount > 0) {
        goto exitDestroy;
    }

    /* Delete any Message Queues that have not been deleted so far. */
    for (i = 0; i< MessageQ_module->numQueues; i++) {
        if (MessageQ_module->queues [i] != NULL) {
            MessageQ_delete(&(MessageQ_module->queues [i]));
        }
    }

    if (MessageQ_module->nameServer != NULL) {
        /* Delete the nameserver for modules */
        status = NameServer_delete(&MessageQ_module->nameServer);
    }

    /* Since MessageQ_module->gate was not allocated, no need to delete. */

    if (MessageQ_module->queues != NULL) {
        free(MessageQ_module->queues);
        MessageQ_module->queues = NULL;
    }

    MessageQ_module->numQueues  = 0u;

exitDestroy:
    LOG1("MessageQ_destroy: exiting, refCount=%d\n", MessageQ_module->refCount)

    pthread_mutex_unlock(&(MessageQ_module->gate));

    return (status);
}

/*
 *   Function to create a MessageQ object for receiving.
 */
MessageQ_Handle MessageQ_create(String name, const MessageQ_Params * params)
{
    Int                 status    = MessageQ_S_SUCCESS;
    MessageQ_Object   * obj    = NULL;
    Bool                found  = FALSE;
    UInt16              count  = 0;
    UInt16              queueIndex;
    UInt16              queuePort;
    UInt16              procId;
    int                 i;
    UInt                numReserved;

    LOG1("MessageQ_create: creating '%s'\n", (name == NULL) ? "NULL" : name)

    /* Create the generic obj */
    obj = (MessageQ_Object *)calloc(1, sizeof(MessageQ_Object));

    if (obj == NULL) {
        LOG0("MessageQ_create: Error: no memory\n")
        return (NULL);
    }

    numReserved = MessageQ_module->cfg->numReservedEntries;

    pthread_mutex_lock(&(MessageQ_module->gate));

    /* check if creating a reserved queue */
    if (params->queueIndex != MessageQ_ANY) {
        queueIndex = params->queueIndex;

        if (queueIndex > numReserved) {
            LOG2("MessageQ_create: Error: requested queue index %d is greater "
                    "than reserved maximum %d\n", queueIndex, numReserved - 1)
            free(obj);
            obj = NULL;
        }
        else if (MessageQ_module->queues[queueIndex] != NULL) {
            LOG1("MessageQ_create: Error: requested queue index %d is already "
                    "in use.\n", queueIndex);
            free(obj);
            obj = NULL;
        }

        if (obj == NULL) {
            pthread_mutex_unlock(&(MessageQ_module->gate));
            return (NULL);
        }

        MessageQ_module->queues[queueIndex] = (MessageQ_Handle)obj;
        found = TRUE;
    }
    else {
        count = MessageQ_module->numQueues;

        /* search the dynamic array for any holes */
        for (i = numReserved; i < count ; i++) {
            if (MessageQ_module->queues [i] == NULL) {
                MessageQ_module->queues [i] = (MessageQ_Handle)obj;
                queueIndex = i;
                found = TRUE;
                break;
            }
        }
    }

    if (found == FALSE) {
        /* Growth is always allowed. */
        queueIndex = _MessageQ_grow(obj);
    }

    pthread_mutex_unlock(&(MessageQ_module->gate));

    if (params != NULL) {
       /* Populate the params member */
        memcpy((Ptr)&obj->params, (Ptr)params, sizeof(MessageQ_Params));
    }

    /* create globally unique message queue ID */
    procId = MultiProc_self();
    queuePort = queueIndex + MessageQ_PORTOFFSET;
    obj->queue = (MessageQ_QueueId)(((UInt32)procId << 16) | queuePort);
    obj->ownerPid = 0;

    /* Cleanup if fail */
    if (status < 0) {
        MessageQ_delete((MessageQ_Handle *)&obj);
    }

    LOG2("MessageQ_create: returning obj=%p, qid=0x%x\n", obj, obj->queue)

    return ((MessageQ_Handle)obj);
}

Int MessageQ_announce(String name, MessageQ_Handle * handlePtr)
{
    Int                 status = MessageQ_S_SUCCESS;
    MessageQ_Object   * obj    = (MessageQ_Object *)(*handlePtr);

    LOG1("MessageQ_announce: announcing %p\n", obj);

    if (name != NULL && obj->nsKey == NULL) {
        obj->nsKey = NameServer_addUInt32(MessageQ_module->nameServer, name,
                obj->queue);
    }
    else {
        status = MessageQ_E_FAIL;
    }

    return status;
}

/*
 * Function to delete a MessageQ object for a specific slave processor.
 */
Int MessageQ_delete(MessageQ_Handle * handlePtr)
{
    Int              status = MessageQ_S_SUCCESS;
    MessageQ_Object *obj;
    MessageQ_Handle queue;
    UInt16          queueIndex;

    obj = (MessageQ_Object *)(*handlePtr);

    LOG1("MessageQ_delete: deleting %p\n", obj)

    queueIndex = MessageQ_getQueueIndex(obj->queue);
    queue = MessageQ_module->queues[queueIndex];
    if (queue != obj) {
        LOG1("ERROR: obj != MessageQ_module->queues[%d]\n", queueIndex)
    }

    if (obj->nsKey != NULL) {
        /* Remove from the name server */
        status = NameServer_removeEntry(MessageQ_module->nameServer,
                                         obj->nsKey);
        if (status < 0) {
            /* Override with a MessageQ status code. */
            status = MessageQ_E_FAIL;
        }
        else {
            status = MessageQ_S_SUCCESS;
        }
    }

    pthread_mutex_lock(&(MessageQ_module->gate));

    /* Clear the MessageQ obj from array. */
    MessageQ_module->queues[queueIndex] = NULL;

    /* Release the local lock */
    pthread_mutex_unlock(&(MessageQ_module->gate));

    /* Now free the obj */
    free(obj);
    *handlePtr = NULL;

    LOG1("MessageQ_delete: returning %d\n", status)

    return (status);
}

/* Returns the MessageQ_QueueId associated with the handle. */
MessageQ_QueueId MessageQ_getQueueId(MessageQ_Handle handle)
{
    MessageQ_Object * obj = (MessageQ_Object *)handle;
    UInt32            queueId;

    queueId = (obj->queue);

    return queueId;
}

/*!
 *  @brief   Grow the MessageQ table
 *
 *  @param   obj     Pointer to the MessageQ object.
 *
 *  @sa      _MessageQ_grow
 *
 */
static UInt16 _MessageQ_grow(MessageQ_Object * obj)
{
    UInt16            queueIndex = MessageQ_module->numQueues;
    UInt16            oldSize;
    MessageQ_Handle * queues;
    MessageQ_Handle * oldQueues;

    /* No parameter validation required since this is an internal function. */
    oldSize = (MessageQ_module->numQueues) * sizeof(MessageQ_Handle);

    /* Allocate larger table */
    queues = calloc(MessageQ_module->numQueues + MessageQ_GROWSIZE,
                    sizeof(MessageQ_Handle));

    /* Copy contents into new table */
    memcpy(queues, MessageQ_module->queues, oldSize);

    /* Fill in the new entry */
    queues[queueIndex] = (MessageQ_Handle)obj;

    /* Hook-up new table */
    oldQueues = MessageQ_module->queues;
    MessageQ_module->queues = queues;
    MessageQ_module->numQueues += MessageQ_GROWSIZE;

    /* Delete old table if not statically defined */
    if (MessageQ_module->canFreeQueues == TRUE) {
        free(oldQueues);
    }
    else {
        MessageQ_module->canFreeQueues = TRUE;
    }

    LOG1("_MessageQ_grow: queueIndex: 0x%x\n", queueIndex)

    return (queueIndex);
}

/*
 * This is a helper function to initialize a message.
 */
Void MessageQ_msgInit(MessageQ_Msg msg)
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

NameServer_Handle MessageQ_getNameServerHandle(void)
{
    return MessageQ_module->nameServer;
}

Void MessageQ_setQueueOwner(MessageQ_Handle handle, Int pid)
{
    handle->ownerPid = pid;

    return;
}

Void MessageQ_cleanupOwner(Int pid)
{
    MessageQ_Handle queue;
    Int i;

    for (i = 0; i < MessageQ_module->numQueues; i++) {
        queue = MessageQ_module->queues[i];
        if (queue != NULL && queue->ownerPid == pid) {
            MessageQ_delete(&queue);
        }
    }
}

Void _MessageQ_setNumReservedEntries(UInt n)
{
    MessageQ_module->cfg->numReservedEntries = n;
}
