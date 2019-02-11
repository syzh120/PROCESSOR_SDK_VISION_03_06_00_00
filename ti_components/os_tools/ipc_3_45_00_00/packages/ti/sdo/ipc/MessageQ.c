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
 *  ======== MessageQ.c ========
 *  Implementation of functions specified in MessageQ.xdc.
 */

#include <xdc/std.h>

#include <string.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Startup.h>

#include <xdc/runtime/knl/ISync.h>
#include <xdc/runtime/knl/GateThread.h>

#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/syncs/SyncSem.h>

#include <ti/sdo/ipc/interfaces/ITransport.h>
#include <ti/sdo/ipc/interfaces/IMessageQTransport.h>
#include <ti/sdo/ipc/interfaces/INetworkTransport.h>
#include <ti/sdo/utils/List.h>

/* must be included after the internal header file for now */
#define MessageQ_internal 1     /* must be defined before include file */
#include <ti/sdo/ipc/_MessageQ.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/utils/_NameServer.h>

#include "package/internal/MessageQ.xdc.h"

/* params structure evolution */
typedef struct {
    Void *synchronizer;
} MessageQ_Params_Legacy;

typedef struct {
    Int __version;
    Void *synchronizer;
    MessageQ_QueueIndex queueIndex;
} MessageQ_Params_Version2;

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(MessageQ_Params_init);
    #pragma FUNC_EXT_CALLED(MessageQ_Params2_init);
    #pragma FUNC_EXT_CALLED(MessageQ_alloc);
    #pragma FUNC_EXT_CALLED(MessageQ_close);
    #pragma FUNC_EXT_CALLED(MessageQ_count);
    #pragma FUNC_EXT_CALLED(MessageQ_create);
    #pragma FUNC_EXT_CALLED(MessageQ_create2);
    #pragma FUNC_EXT_CALLED(MessageQ_delete);
    #pragma FUNC_EXT_CALLED(MessageQ_open);
    #pragma FUNC_EXT_CALLED(MessageQ_openQueueId);
    #pragma FUNC_EXT_CALLED(MessageQ_free);
    #pragma FUNC_EXT_CALLED(MessageQ_get);
    #pragma FUNC_EXT_CALLED(MessageQ_getQueueId);
    #pragma FUNC_EXT_CALLED(MessageQ_put);
    #pragma FUNC_EXT_CALLED(MessageQ_registerHeap);
    #pragma FUNC_EXT_CALLED(MessageQ_registerTransportId);
    #pragma FUNC_EXT_CALLED(MessageQ_setFreeHookFxn);
    #pragma FUNC_EXT_CALLED(MessageQ_setPutHookFxn);
    #pragma FUNC_EXT_CALLED(MessageQ_setReplyQueue);
    #pragma FUNC_EXT_CALLED(MessageQ_setMsgTrace);
    #pragma FUNC_EXT_CALLED(MessageQ_staticMsgInit);
    #pragma FUNC_EXT_CALLED(MessageQ_unblock);
    #pragma FUNC_EXT_CALLED(MessageQ_unregisterHeap);
#endif

/*
 *  ======== MessageQ_msgInit ========
 *  This is a helper function to initialize a message.
 */
static Void MessageQ_msgInit(MessageQ_Msg msg)
{
    UInt key;

    msg->replyId = (UInt16)MessageQ_INVALIDMESSAGEQ;
    msg->msgId   = MessageQ_INVALIDMSGID;
    msg->dstId   = (UInt16)MessageQ_INVALIDMESSAGEQ;
    msg->flags   = ti_sdo_ipc_MessageQ_HEADERVERSION |
                   MessageQ_NORMALPRI |
                   (ti_sdo_ipc_MessageQ_TRACEMASK &
                   (ti_sdo_ipc_MessageQ_traceFlag << ti_sdo_ipc_MessageQ_TRACESHIFT));
    msg->srcProc = MultiProc_self();

    key = Hwi_disable();
    msg->seqNum  = MessageQ_module->seqNum++;
    Hwi_restore(key);
}

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

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
            Assert_isTrue(FALSE, NULL);
            break;
    }
}

/*
 *  ======== MessageQ_Params2_init ========
 *  Deprecated
 */
Void MessageQ_Params2_init(MessageQ_Params2 *params)
{
    params->synchronizer = NULL;
    params->queueIndex = MessageQ_ANY;
}

/*
 *  ======== MessageQ_alloc ========
 *  Allocate a message and initialize the needed fields
 *
 *  Note: some of the fields in the header are set via other
 *  APIs or in the MessageQ_put function.
 */
MessageQ_Msg MessageQ_alloc(UInt16 heapId, UInt32 size)
{
    MessageQ_Msg msg;
    Error_Block eb;

    Assert_isTrue((heapId < MessageQ_module->numHeaps),
                  ti_sdo_ipc_MessageQ_A_heapIdInvalid);

    Assert_isTrue((MessageQ_module->heaps[heapId] != NULL),
                  ti_sdo_ipc_MessageQ_A_heapIdInvalid);

    /* Allocate the message. No alignment requested */
    Error_init(&eb);
    msg = Memory_alloc(MessageQ_module->heaps[heapId], size, 0, &eb);

    if (msg == NULL) {
        return (NULL);
    }

    /* Fill in the fields of the message */
    MessageQ_msgInit(msg);
    msg->msgSize = size;
    msg->heapId  = heapId;

    if (ti_sdo_ipc_MessageQ_traceFlag == TRUE) {
        Log_write3(ti_sdo_ipc_MessageQ_LM_alloc, (UArg)(msg),
            (UArg)(msg->seqNum), (UArg)(msg->srcProc));
    }

    return (msg);
}

/*
 *  ======== MessageQ_count ========
 */
Int MessageQ_count(MessageQ_Handle handle)
{
    Int              count = 0;
    UInt             key;
    List_Elem       *tempMsg = NULL;
    List_Handle      listHandle;
    ti_sdo_ipc_MessageQ_Object *obj = (ti_sdo_ipc_MessageQ_Object *)handle;

    /* lock */
    key = Hwi_disable();

    /* Get the list */
    listHandle = ti_sdo_ipc_MessageQ_Instance_State_highList(obj);

    /* Loop through and count the messages */
    while ((tempMsg = List_next(listHandle, tempMsg)) != NULL) {
        count++;
    }

    listHandle = ti_sdo_ipc_MessageQ_Instance_State_normalList(obj);

    /* Loop through and count the messages */
    while ((tempMsg = List_next(listHandle, tempMsg)) != NULL) {
        count++;
    }

    /* unlock scheduler */
    Hwi_restore(key);

    return (count);
}

/*
 *  ======== MessageQ_close ========
 */
Int MessageQ_close(MessageQ_QueueId *queueId)
{
    *queueId = MessageQ_INVALIDMESSAGEQ;

    return (MessageQ_S_SUCCESS);
}

/*
 *  ======== MessageQ_create ========
 */
MessageQ_Handle MessageQ_create(String name, const MessageQ_Params *pp)
{
    ti_sdo_ipc_MessageQ_Handle handle;
    ti_sdo_ipc_MessageQ_Params ps;
    Error_Block eb;

    Error_init(&eb);

    if (pp != NULL) {
        ti_sdo_ipc_MessageQ_Params_init(&ps);

        /* snoop the params pointer to see if it's a legacy structure */
        if ((pp->__version == 0) || (pp->__version > 100)) {
            ps.synchronizer = ((MessageQ_Params_Legacy *)pp)->synchronizer;
        }

        /* not legacy structure, use params version field */
        else if (pp->__version == MessageQ_Params_VERSION_2) {
            ps.synchronizer = ((MessageQ_Params_Version2 *)pp)->synchronizer;
            ps.queueIndex = ((MessageQ_Params_Version2 *)pp)->queueIndex;
        }
        else {
            Assert_isTrue(FALSE, NULL);
        }

        handle = ti_sdo_ipc_MessageQ_create(name, &ps, &eb);
    }
    else {
        handle = ti_sdo_ipc_MessageQ_create(name, NULL, &eb);
    }

    return ((MessageQ_Handle)handle);
}

/*
 *  ======== MessageQ_create2 ========
 */
MessageQ_Handle MessageQ_create2(String name, const MessageQ_Params2 *params)
{
    ti_sdo_ipc_MessageQ_Handle handle;
    ti_sdo_ipc_MessageQ_Params prms;
    Error_Block eb;

    Error_init(&eb);

    if (params != NULL) {
        ti_sdo_ipc_MessageQ_Params_init(&prms);

        prms.synchronizer = params->synchronizer;
        prms.queueIndex = params->queueIndex;

        handle = ti_sdo_ipc_MessageQ_create(name, &prms, &eb);
    }
    else {
        handle = ti_sdo_ipc_MessageQ_create(name, NULL, &eb);
    }

    return ((MessageQ_Handle)handle);
}

/*
 *  ======== MessageQ_delete ========
 */
Int MessageQ_delete(MessageQ_Handle *handlePtr)
{
    ti_sdo_ipc_MessageQ_Handle *instp;

    instp = (ti_sdo_ipc_MessageQ_Handle *)handlePtr;

    ti_sdo_ipc_MessageQ_delete(instp);

    return (MessageQ_S_SUCCESS);
}

/*
 *  ======== MessageQ_free ========
 */
Int MessageQ_free(MessageQ_Msg msg)
{
    IHeap_Handle heap;
    Bits16 msgId;
    Bits16 heapId;

    /* make sure msg is not NULL */
    Assert_isTrue((msg != NULL), ti_sdo_ipc_MessageQ_A_invalidMsg);

    /* Cannot free a message that was initialized via MessageQ_staticMsgInit */
    Assert_isTrue((msg->heapId != ti_sdo_ipc_MessageQ_STATICMSG),
                  ti_sdo_ipc_MessageQ_A_cannotFreeStaticMsg);

    Assert_isTrue((msg->heapId < MessageQ_module->numHeaps),
                  ti_sdo_ipc_MessageQ_A_heapIdInvalid);

    Assert_isTrue((MessageQ_module->heaps[msg->heapId] != NULL),
                  ti_sdo_ipc_MessageQ_A_heapIdInvalid);

    if ((ti_sdo_ipc_MessageQ_traceFlag == TRUE) ||
        (msg->flags & ti_sdo_ipc_MessageQ_TRACEMASK) != 0) {
        Log_write3(ti_sdo_ipc_MessageQ_LM_free, (UArg)(msg),
            (UArg)(msg->seqNum), (UArg)(msg->srcProc));
    }

    heap = MessageQ_module->heaps[msg->heapId];

    if (heap != NULL) {
        msgId = MessageQ_getMsgId(msg);
        heapId = msg->heapId;
        Memory_free(heap, msg, msg->msgSize);
        if (MessageQ_module->freeHookFxn != NULL) {
            MessageQ_module->freeHookFxn(heapId, msgId);
        }
    }
    else {
        return (MessageQ_E_FAIL);
    }

    return (MessageQ_S_SUCCESS);
}

/*
 *  ======== MessageQ_get ========
 */
Int MessageQ_get(MessageQ_Handle handle, MessageQ_Msg *msg, UInt timeout)
{
    Int status;
    List_Handle highList;
    List_Handle normalList;
    ti_sdo_ipc_MessageQ_Object *obj = (ti_sdo_ipc_MessageQ_Object *)handle;

    /* Get the list */
    normalList = ti_sdo_ipc_MessageQ_Instance_State_normalList(obj);
    highList   = ti_sdo_ipc_MessageQ_Instance_State_highList(obj);

    /* Keep looping while there are no elements on either list */
    *msg = (MessageQ_Msg)List_get(highList);
    while (*msg == NULL) {
        *msg = (MessageQ_Msg)List_get(normalList);
        if (*msg == NULL) {
            /*  Block until notified. */
            status = ISync_wait(obj->synchronizer, timeout, NULL);
            if (status == ISync_WaitStatus_TIMEOUT) {
                return (MessageQ_E_TIMEOUT);
            }
            else if (status < 0) {
                return (MessageQ_E_FAIL);
            }

            if (obj->unblocked) {
                /* *(msg) may be NULL */
                return (MessageQ_E_UNBLOCKED);
            }

            *msg = (MessageQ_Msg)List_get(highList);
        }
    }

    if ((ti_sdo_ipc_MessageQ_traceFlag == TRUE) ||
        (((*msg)->flags & ti_sdo_ipc_MessageQ_TRACEMASK) != 0)) {
        Log_write4(ti_sdo_ipc_MessageQ_LM_get, (UArg)(*msg),
            (UArg)((*msg)->seqNum), (UArg)((*msg)->srcProc), (UArg)(obj));
    }

    return (MessageQ_S_SUCCESS);
}

/*
 *  ======== MessageQ_getQueueId ========
 */
MessageQ_QueueId MessageQ_getQueueId(MessageQ_Handle handle)
{
    MessageQ_QueueId queueId;
    ti_sdo_ipc_MessageQ_Object *obj = (ti_sdo_ipc_MessageQ_Object *)handle;

    queueId = (obj->queue);

    return (queueId);
}

/*
 *  ======== MessageQ_open ========
 */
Int MessageQ_open(String name, MessageQ_QueueId *queueId)
{
    Int         status;
    Error_Block eb;

    Assert_isTrue(name != NULL, ti_sdo_ipc_MessageQ_A_invalidParam);
    Assert_isTrue(queueId != NULL, ti_sdo_ipc_MessageQ_A_invalidParam);

    Error_init(&eb);

    /* Search NameServer */
    status = NameServer_getUInt32(
            (NameServer_Handle)MessageQ_module->nameServer, name, queueId,
            NULL);

    if (status >= 0) {
        return (MessageQ_S_SUCCESS);    /* name found */
    }
    else {
        return (MessageQ_E_NOTFOUND);   /* name not found */
    }
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
 *  ======== MessageQ_put ========
 */
Int MessageQ_put(MessageQ_QueueId queueId, MessageQ_Msg msg)
{
    IMessageQTransport_Handle transport;
    MessageQ_QueueIndex dstProcId = (MessageQ_QueueIndex)(queueId >> 16);
    List_Handle       listHandle;
    Int               status;
    UInt              priority;
#ifndef xdc_runtime_Log_DISABLE_ALL
    UInt16            flags;
    UInt16            seqNum;
    UInt16            srcProc;
#endif
    ti_sdo_ipc_MessageQ_Object   *obj;
    Int tid;
    ITransport_Handle baseTrans;
    INetworkTransport_Handle netTrans;
    MessageQ_QueueIndex queueIndex;
    UInt16 index;

    Assert_isTrue((msg != NULL), ti_sdo_ipc_MessageQ_A_invalidMsg);

    msg->dstId   = (UInt16)(queueId);
    msg->dstProc = (UInt16)(queueId >> 16);

    /* invoke put hook function after addressing the message */
    if (MessageQ_module->putHookFxn != NULL) {
        MessageQ_module->putHookFxn(queueId, (Ptr)msg);
    }

    /* extract the transport ID from the message header */
    tid = MessageQ_getTransportId(msg);

    /* if recipient is local, use direct message delivery */
    if (dstProcId == MultiProc_self()) {
        /* assert queue index is valid */
        queueIndex = MessageQ_getQueueIndex(queueId);
        Assert_isTrue(queueIndex < MessageQ_module->numQueues,
                      ti_sdo_ipc_MessageQ_A_invalidQueueId);

        /* It is a local MessageQ */
        obj = MessageQ_module->queues[queueIndex];

        /* Assert object is not NULL */
        Assert_isTrue(obj != NULL, ti_sdo_ipc_MessageQ_A_invalidObj);

        if ((msg->flags & MessageQ_PRIORITYMASK) == MessageQ_URGENTPRI) {
            listHandle = ti_sdo_ipc_MessageQ_Instance_State_highList(obj);
            List_putHead(listHandle, (List_Elem *)msg);
        }
        else {
            if ((msg->flags & MessageQ_PRIORITYMASK) == MessageQ_NORMALPRI) {
                listHandle = ti_sdo_ipc_MessageQ_Instance_State_normalList(obj);
            }
            else {
                listHandle = ti_sdo_ipc_MessageQ_Instance_State_highList(obj);
            }
            /* put on the queue */
            List_put(listHandle, (List_Elem *)msg);
        }

        ISync_signal(obj->synchronizer);

        status = MessageQ_S_SUCCESS;

        if ((ti_sdo_ipc_MessageQ_traceFlag) ||
            (msg->flags & ti_sdo_ipc_MessageQ_TRACEMASK) != 0) {
            Log_write4(ti_sdo_ipc_MessageQ_LM_putLocal, (UArg)(msg),
                       (UArg)(msg->seqNum), (UArg)(msg->srcProc), (UArg)(obj));
        }
    }

    /* if transport ID is zero, use primary transport array */
    else if (tid == 0) {
        /* assert that dstProcId is valid */
        Assert_isTrue(dstProcId < ti_sdo_utils_MultiProc_numProcessors,
                      ti_sdo_ipc_MessageQ_A_procIdInvalid);

        /* Put the high and urgent messages to the high priority transport */
        priority = (UInt)((msg->flags) &
            ti_sdo_ipc_MessageQ_TRANSPORTPRIORITYMASK);

        switch (ti_sdo_utils_MultiProc_procAddrMode) {
            case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
                index = dstProcId;
                break;

            case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
                index = dstProcId - MultiProc_getBaseIdOfCluster();
                break;

            default:
                Assert_isTrue(FALSE, NULL);
                break;
        }

        if (index >= MessageQ_module->transports.length) {
            /* raise error */
            status = MessageQ_E_FAIL;
            goto leave;
        }

        /* Call the transport associated with this message queue */
        transport = MessageQ_module->transports.elem[index][priority];

        if (transport == NULL) {
            /* Try the other transport */
            priority = !priority;
            transport = MessageQ_module->transports.elem[index][priority];
        }

        /* assert transport is not null */
        Assert_isTrue(transport != NULL,
            ti_sdo_ipc_MessageQ_A_unregisteredTransport);

#ifndef xdc_runtime_Log_DISABLE_ALL
        /* use local vars so msg does not get cached after put */
        flags = msg->flags;

        if ((ti_sdo_ipc_MessageQ_traceFlag) ||
            (flags & ti_sdo_ipc_MessageQ_TRACEMASK) != 0) {
            /* use local vars so msg does not get cached after put */
            seqNum  = msg->seqNum;
            srcProc = msg->srcProc;
        }
#endif

        /* put msg to remote processor using transport */
        if (IMessageQTransport_put(transport, msg)) {
            status = MessageQ_S_SUCCESS;

#ifndef xdc_runtime_Log_DISABLE_ALL
            /* if trace enabled */
            if ((ti_sdo_ipc_MessageQ_traceFlag) ||
                (flags & ti_sdo_ipc_MessageQ_TRACEMASK) != 0) {
                Log_write4(ti_sdo_ipc_MessageQ_LM_putRemote, (UArg)(msg),
                          (UArg)(seqNum), (UArg)(srcProc),
                          (UArg)(dstProcId));
            }
#endif
        }
        else {
            status = MessageQ_E_FAIL;
        }
    }

    /* use a registered transport to deliver the message */
    else {
        baseTrans = MessageQ_module->regTrans[tid].transport;

        if (baseTrans == NULL) {
            /* raise error */
            status = MessageQ_E_FAIL;
            goto leave;
        }

        switch (MessageQ_module->regTrans[tid].type) {

            case ti_sdo_ipc_MessageQ_TransportType_INetworkTransport:
                netTrans = INetworkTransport_Handle_downCast(baseTrans);

                if (INetworkTransport_put(netTrans, msg)) {
                    status = MessageQ_S_SUCCESS;
                }
                else {
                    status = MessageQ_E_FAIL;
                }
            break;
        }
    }

leave:
    return (status);
}

/*
 *  ======== MessageQ_registerHeap ========
 *  Register a heap
 */
Int MessageQ_registerHeap(Ptr heap, UInt16 heapId)
{
    Int status;
    UInt key;
    IHeap_Handle iheap = (IHeap_Handle)heap;

    /* Make sure the heapId is valid */
    Assert_isTrue((heapId < MessageQ_module->numHeaps),
                  ti_sdo_ipc_MessageQ_A_heapIdInvalid);

    /* lock scheduler */
    key = Hwi_disable();

    /* Make sure the id is not already in use */
    if (MessageQ_module->heaps[heapId] == NULL) {
        MessageQ_module->heaps[heapId] = iheap;
        status = MessageQ_S_SUCCESS;
    }
    else {
        status = MessageQ_E_ALREADYEXISTS;
    }

    /* unlock scheduler */
    Hwi_restore(key);

    return (status);
}

/*
 *  ======== MessageQ_setFreeHookFxn ========
 */
Void MessageQ_setFreeHookFxn(MessageQ_FreeHookFxn freeHookFxn)
{
    MessageQ_module->freeHookFxn = freeHookFxn;
}

/*
 *  ======== MessageQ_setPutHookFxn ========
 */
Void MessageQ_setPutHookFxn(MessageQ_PutHookFxn putHookFxn)
{
    MessageQ_module->putHookFxn = (ti_sdo_ipc_MessageQ_PutHookFxn)putHookFxn;
}

/*
 *  ======== MessageQ_setMsgTrace ========
 */
Void MessageQ_setMsgTrace(MessageQ_Msg msg, Bool traceFlag)
{
    msg->flags = (msg->flags & ~ti_sdo_ipc_MessageQ_TRACEMASK) |
                 (traceFlag << ti_sdo_ipc_MessageQ_TRACESHIFT);
    Log_write4(ti_sdo_ipc_MessageQ_LM_setTrace, (UArg)(msg), (UArg)(msg->seqNum),
               (UArg)(msg->srcProc), (UArg)(traceFlag));
}

/*
 *  ======== MessageQ_setReplyQueue ========
 *  Embed the source message queue into a message.
 */
Void MessageQ_setReplyQueue(MessageQ_Handle handle, MessageQ_Msg msg)
{
    ti_sdo_ipc_MessageQ_Object *obj = (ti_sdo_ipc_MessageQ_Object *)handle;

    msg->replyId   = (UInt16)(obj->queue);
    msg->replyProc = (UInt16)(obj->queue >> 16);
}

/*
 *  ======== MessageQ_staticMsgInit ========
 */
Void MessageQ_staticMsgInit(MessageQ_Msg msg, UInt32 size)
{
    Assert_isTrue((msg != NULL), ti_sdo_ipc_MessageQ_A_invalidMsg);

    MessageQ_msgInit(msg);

    msg->heapId  = ti_sdo_ipc_MessageQ_STATICMSG;
    msg->msgSize = size;

    if (ti_sdo_ipc_MessageQ_traceFlag == TRUE) {
        Log_write3(ti_sdo_ipc_MessageQ_LM_staticMsgInit, (UArg)(msg),
                (UArg)(msg->seqNum), (UArg)(msg->srcProc));
    }
}

/*
 *  ======== MessageQ_unblock ========
 */
Void MessageQ_unblock(MessageQ_Handle handle)
{
    ti_sdo_ipc_MessageQ_Object *obj = (ti_sdo_ipc_MessageQ_Object *)handle;

    /* Assert that the queue is using a blocking synchronizer */
    Assert_isTrue(ISync_query((obj->synchronizer), ISync_Q_BLOCKING) == TRUE,
        ti_sdo_ipc_MessageQ_A_invalidUnblock);

    /* Set instance to 'unblocked' state */
    obj->unblocked = TRUE;

    /* Signal the synchronizer */
    ISync_signal(obj->synchronizer);
}

/*
 *  ======== MessageQ_unregisterHeap ========
 *  Unregister a heap
 */
Int MessageQ_unregisterHeap(UInt16 heapId)
{
    UInt key;

    Assert_isTrue((heapId < MessageQ_module->numHeaps),
                  ti_sdo_ipc_MessageQ_A_heapIdInvalid);

    /* lock scheduler */
    key = Hwi_disable();

    MessageQ_module->heaps[heapId] = NULL;

    /* unlock scheduler */
    Hwi_restore(key);

    return (MessageQ_S_SUCCESS);
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_MessageQ_Module_startup ========
 */
Int ti_sdo_ipc_MessageQ_Module_startup(Int phase)
{
    Int i;

    /* Ensure NameServer Module_startup() has completed */
    if (ti_sdo_utils_NameServer_Module_startupDone() == FALSE) {
        return (Startup_NOTDONE);
    }

    if (GateThread_Module_startupDone() == FALSE) {
        return (Startup_NOTDONE);
    }

    if (MessageQ_module->gate == NULL) {
        MessageQ_module->gate =
            GateThread_Handle_upCast(GateThread_create(NULL, NULL));
    }

    /* Loop through all the static objects and set the id */
    for (i = 0; i < ti_sdo_ipc_MessageQ_Object_count(); i++) {
        MessageQ_module->queues[i] = (ti_sdo_ipc_MessageQ_Object *)
                ti_sdo_ipc_MessageQ_Object_get(NULL, i);
    }

    /* Null out the dynamic ones */
    for (i = ti_sdo_ipc_MessageQ_Object_count(); i < MessageQ_module->numQueues;
            i++) {
        MessageQ_module->queues[i] = NULL;
    }

    return (Startup_DONE);
}

/*
 *  ======== ti_sdo_ipc_MessageQ_registerTransport ========
 */
Bool ti_sdo_ipc_MessageQ_registerTransport(IMessageQTransport_Handle handle,
    UInt16 procId, UInt priority)
{
    Bool flag = FALSE;
    UInt key;
    UInt16 index;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_MessageQ_A_procIdInvalid);

    switch (ti_sdo_utils_MultiProc_procAddrMode) {
        case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
            index = procId;
            break;

        case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
            index = procId - MultiProc_getBaseIdOfCluster();
            break;

        default:
            Assert_isTrue(FALSE, NULL);
            break;
    }

    Assert_isTrue(index < MessageQ_module->transports.length,
            ti_sdo_ipc_MessageQ_A_procIdInvalid);

    /* lock scheduler */
    key = Hwi_disable();

    /* make sure the id is not already in use */
    if (MessageQ_module->transports.elem[index][priority] == NULL) {
        MessageQ_module->transports.elem[index][priority] = handle;
        flag = TRUE;
    }

    /* unlock scheduler */
    Hwi_restore(key);

    return (flag);
}

/*
 *  ======== ti_sdo_ipc_MessageQ_unregisterTransport ========
 */
Void ti_sdo_ipc_MessageQ_unregisterTransport(UInt16 procId, UInt priority)
{
    UInt key;
    UInt16 index;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_ipc_MessageQ_A_procIdInvalid);

    switch (ti_sdo_utils_MultiProc_procAddrMode) {
        case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
            index = procId;
            break;

        case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
            index = procId - MultiProc_getBaseIdOfCluster();
            break;

        default:
            Assert_isTrue(FALSE, NULL);
            break;
    }

    Assert_isTrue(index < MessageQ_module->transports.length,
            ti_sdo_ipc_MessageQ_A_procIdInvalid);

    /* lock scheduler */
    key = Hwi_disable();

    MessageQ_module->transports.elem[index][priority] = NULL;

    /* unlock scheduler */
    Hwi_restore(key);
}

/*
 *  ======== MessageQ_registerTransportId ========
 */
Bool MessageQ_registerTransportId(UInt tid, ITransport_Handle inst)
{
    ti_sdo_ipc_MessageQ_TransportType type;

    /* validate transport ID */
    if ((tid < 1) || (tid > 7)) {
        /* raise error */
        return (FALSE);
    }

    /* don't overwrite an existing transport */
    if (MessageQ_module->regTrans[tid].transport != NULL) {
        /* raise error */
        return (FALSE);
    }

    /* determine the transport type */
    if (INetworkTransport_Handle_downCast(inst) != NULL) {
        type = ti_sdo_ipc_MessageQ_TransportType_INetworkTransport;
    }
    else {
        /* raise error */
        return (FALSE);
    }

    /* register the transport instance */
    MessageQ_module->regTrans[tid].transport = inst;
    MessageQ_module->regTrans[tid].type = type;
    return (TRUE);
}

/*
 *  ======== MessageQ_unregisterTransportId ========
 */
Void MessageQ_unregisterTransportId(UInt tid)
{
    /* forget the registered transport instance */
    MessageQ_module->regTrans[tid].transport = NULL;
    MessageQ_module->regTrans[tid].type =
            ti_sdo_ipc_MessageQ_TransportType_Invalid;

    return;
}


/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== MessageQ_Instance_init ========
 */
Int ti_sdo_ipc_MessageQ_Instance_init(ti_sdo_ipc_MessageQ_Object *obj,
        String name, const ti_sdo_ipc_MessageQ_Params *params, Error_Block *eb)
{
    Int              i;
    UInt16           start;
    UInt16           count;
    UInt             key;
    Bool             found = FALSE;
    List_Handle      listHandle;
    SyncSem_Handle   syncSemHandle;
    MessageQ_QueueIndex queueIndex;
    MessageQ_QueueIndex queuePort;
    Int tid;
    Int status;
    ITransport_Handle baseTrans;
    INetworkTransport_Handle netTrans;

    /* lock */
    key = IGateProvider_enter(MessageQ_module->gate);

    if (params->queueIndex != MessageQ_ANY) {
        queueIndex = params->queueIndex;

        if ((queueIndex >= ti_sdo_ipc_MessageQ_numReservedEntries) ||
            (MessageQ_module->queues[queueIndex] != NULL)) {
            IGateProvider_leave(MessageQ_module->gate, key);
            Error_raise(eb, ti_sdo_ipc_MessageQ_E_indexNotAvailable,
                queueIndex, 0);
            return (5);
        }
        MessageQ_module->queues[queueIndex] = obj;
        found = TRUE;
    }
    else {
        start = ti_sdo_ipc_MessageQ_numReservedEntries;
        count = MessageQ_module->numQueues;

        /* Search the dynamic array for any holes */
        for (i = start; (i < count) && (found == FALSE); i++) {
            if (MessageQ_module->queues[i] == NULL) {
                MessageQ_module->queues[i] = obj;
                queueIndex = i;
                found = TRUE;
            }
        }
    }

    /*
     *  If no free slot was found:
     *     - if no growth allowed, raise and error
     *     - if growth is allowed, grow the array
     */
    if (found == FALSE) {
        if (ti_sdo_ipc_MessageQ_maxRuntimeEntries != NameServer_ALLOWGROWTH) {
            /* unlock scheduler */
            IGateProvider_leave(MessageQ_module->gate, key);

            Error_raise(eb, ti_sdo_ipc_MessageQ_E_maxReached,
                ti_sdo_ipc_MessageQ_maxRuntimeEntries, 0);
            return (1);
        }
        else {
            queueIndex = MessageQ_grow(obj, eb);
            if (queueIndex == MessageQ_INVALIDMESSAGEQ) {
                /* unlock scheduler */
                IGateProvider_leave(MessageQ_module->gate, key);
                return (2);
            }
        }
    }

    /* create default sync if not specified */
    if (params->synchronizer == NULL) {
        /* Create a SyncSem as the synchronizer */
        syncSemHandle = SyncSem_create(NULL, eb);

        if (syncSemHandle == NULL) {
            /* unlock scheduler */
            IGateProvider_leave(MessageQ_module->gate, key);
            return (3);
        }

        /* store handle for use in finalize ...  */
        obj->syncSemHandle = syncSemHandle;

        obj->synchronizer = SyncSem_Handle_upCast(syncSemHandle);
    }
    else {
        obj->syncSemHandle = NULL;

        obj->synchronizer = params->synchronizer;
    }

    /* unlock scheduler */
    IGateProvider_leave(MessageQ_module->gate, key);

    /* Fill in the message queue object */
    listHandle = ti_sdo_ipc_MessageQ_Instance_State_normalList(obj);
    List_construct(List_struct(listHandle), NULL);

    listHandle = ti_sdo_ipc_MessageQ_Instance_State_highList(obj);
    List_construct(List_struct(listHandle), NULL);

    /* queue port is embedded in the queueId */
    queuePort = queueIndex + MessageQ_PORTOFFSET;
    obj->queue = ((MessageQ_QueueId)(MultiProc_self()) << 16) | queuePort;

    obj->unblocked = FALSE;

    /* Add into NameServer */
    if (name != NULL) {
        obj->nsKey = NameServer_addUInt32(
                (NameServer_Handle)MessageQ_module->nameServer, name,
                obj->queue);

        if (obj->nsKey == NULL) {
            Error_raise(eb, ti_sdo_ipc_MessageQ_E_nameFailed, name, 0);
            return (4);
        }
    }

    /* notify all registered transports about the new queue */
    for (tid = 1; tid <= 7; tid++) {
        if (MessageQ_module->regTrans[tid].transport == NULL) {
            continue;
        }
        baseTrans = MessageQ_module->regTrans[tid].transport;

        switch (MessageQ_module->regTrans[tid].type) {

            case ti_sdo_ipc_MessageQ_TransportType_INetworkTransport:
                netTrans = INetworkTransport_Handle_downCast(baseTrans);

                if (INetworkTransport_bind(netTrans, obj->queue)) {
                    status = MessageQ_S_SUCCESS;
                }
                else {
                    status = MessageQ_E_FAIL;
                }
            break;
        }

        /* check for failure */
        if (status < 0) {
            /* TODO add error handling */
        }
    }

    return (0);
}

/*
 *  ======== MessageQ_Instance_finalize ========
 */
Void ti_sdo_ipc_MessageQ_Instance_finalize(
        ti_sdo_ipc_MessageQ_Object* obj, Int status)
{
    UInt key;
    MessageQ_QueueIndex queueIndex;
    List_Handle listHandle;
    Int tid;
    ITransport_Handle baseTrans;
    INetworkTransport_Handle netTrans;

    /* Requested queueId was not available. Nothing was done in the init */
    if (status == 5) {
        return;
    }

    /* notify all registered transports that given queue is being deleted */
    for (tid = 1; tid <= 7; tid++) {
        if (MessageQ_module->regTrans[tid].transport == NULL) {
            continue;
        }
        baseTrans = MessageQ_module->regTrans[tid].transport;

        switch (MessageQ_module->regTrans[tid].type) {

            case ti_sdo_ipc_MessageQ_TransportType_INetworkTransport:
                netTrans = INetworkTransport_Handle_downCast(baseTrans);

                if (INetworkTransport_unbind(netTrans, obj->queue)) {
                    status = MessageQ_S_SUCCESS;
                }
                else {
                    status = MessageQ_E_FAIL;
                }
            break;
        }

        /* check for failure */
        if (status < 0) {
            /* TODO add error handling */
        }
    }

    if (obj->syncSemHandle != NULL) {
        SyncSem_delete(&obj->syncSemHandle);
    }

    listHandle = ti_sdo_ipc_MessageQ_Instance_State_normalList(obj);

    /* Destruct the list */
    List_destruct(List_struct(listHandle));

    listHandle = ti_sdo_ipc_MessageQ_Instance_State_highList(obj);

    /* Destruct the list */
    List_destruct(List_struct(listHandle));

    /* lock */
    key = IGateProvider_enter(MessageQ_module->gate);

    /* Null out entry in the array. */
    queueIndex = MessageQ_getQueueIndex(obj->queue);
    MessageQ_module->queues[queueIndex] = NULL;

    /* unlock scheduler */
    IGateProvider_leave(MessageQ_module->gate, key);

    if (obj->nsKey != NULL) {
        NameServer_removeEntry((NameServer_Handle)MessageQ_module->nameServer,
            obj->nsKey);
    }
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_MessageQ_grow ========
 */
UInt16 ti_sdo_ipc_MessageQ_grow(ti_sdo_ipc_MessageQ_Object *obj,
        Error_Block *eb)
{
    UInt16 oldSize;
    UInt16 queueIndex = MessageQ_module->numQueues;
    ti_sdo_ipc_MessageQ_Handle *queues;
    ti_sdo_ipc_MessageQ_Handle *oldQueues;
    oldSize = (MessageQ_module->numQueues) * sizeof(MessageQ_Handle);


    /* Allocate larger table */
    queues = Memory_alloc(ti_sdo_ipc_MessageQ_Object_heap(),
                          oldSize + sizeof(MessageQ_Handle), 0, eb);

    if (queues == NULL) {
        return (MessageQ_INVALIDMESSAGEQ);
    }

    /* Copy contents into new table */
    memcpy(queues, MessageQ_module->queues, oldSize);

    /* Fill in the new entry */
    queues[queueIndex] = obj;

    /* Hook-up new table */
    oldQueues = MessageQ_module->queues;
    MessageQ_module->queues = queues;
    MessageQ_module->numQueues++;

    /* Delete old table if not statically defined */
    if (MessageQ_module->canFreeQueues == TRUE) {
        Memory_free(ti_sdo_ipc_MessageQ_Object_heap(), oldQueues, oldSize);
    }
    else {
        MessageQ_module->canFreeQueues = TRUE;
    }

    return (queueIndex);
}
