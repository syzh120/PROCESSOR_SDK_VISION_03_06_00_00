/*
 * Copyright (c) 2011-2015 Texas Instruments Incorporated - http://www.ti.com
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
/** ============================================================================
 *  @file       RPMessage.c
 *
 *  @brief      A simple copy-based MessageQ, to work with Linux virtio_rp_msg.
 *
 *  Notes:
 *  - The logic in the functions for sending (_put()) and receiving _swiFxn()
 *    depend on the role (host or slave) the processor is playing in the
 *    asymmetric virtio I/O.
 *  - The host always adds *available* buffers to send/receive, while the slave
 *    always adds *used* buffers to send/receive.
 *  - The logic is summarized below:
 *
 *    Host:
 *    - Prime vq_host with avail bufs, and kick vq_host so slave can send.
 *    - To send a buffer to the slave processor:
 *          allocate a tx buffer, or get_used_buf(vq_slave);
 *               >> copy data into buf <<
 *          add_avail_buf(vq_slave);
 *          kick(vq_slave);
 *    - To receive buffer from slave processor:
 *          get_used_buf(vq_host);
 *              >> empty data from buf <<
 *          add_avail_buf(vq_host);
 *          kick(vq_host);
 *
 *    Slave:
 *    - To receive buffer from the host:
 *          get_avail_buf(vq_slave);
 *              >> empty data from buf <<
 *          add_used_buf(vq_slave);
 *          kick(vq_slave);
 *    - To send buffer to the host:
 *          get_avail_buf(vq_host);
 *              >> copy data into buf <<
 *          add_used_buf(vq_host);
 *          kick(vq_host);
 *
 *  ============================================================================
 */

/* this define must precede inclusion of any xdc header file */
#define Registry_CURDESC ti_ipc_rpmsg_RPMessage__Desc
#define MODULE_NAME "ti.ipc.rpmsg.RPMessage"

#include <xdc/std.h>
#include <string.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/heaps/HeapBuf.h>
#include <ti/sysbios/gates/GateHwi.h>

#include <ti/sdo/utils/List.h>
#include <ti/ipc/MultiProc.h>

#include <ti/ipc/rpmsg/RPMessage.h>

#include "_VirtQueue.h"

/* TBD: VirtQueue.h needs to somehow get factored out of family directory .*/
#if defined(OMAPL138)
#include <ti/ipc/family/omapl138/VirtQueue.h>
#elif defined(TCI6614)
#include <ti/ipc/family/tci6614/VirtQueue.h>
#elif defined(TCI6638)
#include <ti/ipc/family/tci6638/VirtQueue.h>
#elif defined(OMAP5)
#include <ti/ipc/family/omap54xx/VirtQueue.h>
#elif defined(VAYU)
#include <ti/ipc/family/vayu/VirtQueue.h>
#else
#error unknown processor!
#endif

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */

/* Various arbitrary limits: */
#define MAXMESSAGEQOBJECTS     256

/* The RPMessage Object */
typedef struct RPMessage_Object {
    UInt32           queueId;      /* Unique id (procId | queueIndex)       */
    Semaphore_Handle semHandle;    /* I/O Completion                        */
    RPMessage_callback cb;      /* RPMessage Callback */
    UArg             arg;          /* Callback argument */
    List_Handle      queue;        /* Queue of pending messages             */
    Bool             unblocked;    /* Use with signal to unblock _receive() */
} RPMessage_Object;

/* Module_State */
typedef struct RPMessage_Module {
    /* Instance gate: */
    GateHwi_Handle gateH;
    /* Array of messageQObjects in the system: */
    struct RPMessage_Object  *msgqObjects[MAXMESSAGEQOBJECTS];
    /* Heap from which to allocate free messages for copying: */
    HeapBuf_Handle              heap;
} RPMessage_Module;

/* Message Header: Must match mp_msg_hdr in virtio_rp_msg.h on Linux side. */
typedef struct RPMessage_MsgHeader {
    Bits32 srcAddr;                 /* source endpoint addr               */
    Bits32 dstAddr;                 /* destination endpoint addr          */
    Bits32 reserved;                /* reserved                           */
    Bits16 dataLen;                 /* data length                        */
    Bits16 flags;                   /* bitmask of different flags         */
    UInt8  payload[];               /* Data payload                       */
} RPMessage_MsgHeader;

typedef RPMessage_MsgHeader *RPMessage_Msg;

/* Element to hold payload copied onto receiver's queue.                  */
typedef struct Queue_elem {
    List_Elem    elem;              /* Allow list linking.                */
    UInt         len;               /* Length of data                     */
    UInt32       src;               /* Src address/endpt of the msg       */
    Char         data[];            /* payload begins here                */
} Queue_elem;

/* Combine transport related objects into a struct for future migration: */
typedef struct RPMessage_Transport  {
    Swi_Handle       swiHandle;
    VirtQueue_Handle virtQueue_toHost;
    VirtQueue_Handle virtQueue_fromHost;
    Semaphore_Handle semHandle_toHost;
} RPMessage_Transport;

/* generated in RPMessage.xs: module$use() */
extern __FAR__ const HeapBuf_Handle ti_ipc_rpmsg_RPMessage_heap;

/* generated in template file RPMessage.xdt */
extern __FAR__ const UInt ti_ipc_rpmsg_RPMessage_messageBufferSize;

/* module diags mask */
Registry_Desc Registry_CURDESC;

static RPMessage_Module      module;
static RPMessage_Transport   transport;

/* Module ref count: */
static Int curInit = 0;

/*
 *  ======== RPMessage_swiFxn ========
 */
#define FXNN "RPMessage_swiFxn"
static Void RPMessage_swiFxn(UArg arg0, UArg arg1)
{
    Int16             token;
    RPMessage_Msg  msg;
    UInt16            dstProc = MultiProc_self();
    Bool              usedBufAdded = FALSE;
    int len;

    Log_print0(Diags_ENTRY, "--> "FXNN);

    /* Process all available buffers: */
    while ((token = VirtQueue_getAvailBuf(transport.virtQueue_fromHost,
                                         (Void **)&msg, &len)) >= 0) {

        Log_print3(Diags_INFO, FXNN": Received msg from: 0x%x, "
                   "to: 0x%x, dataLen: %d",
                  (IArg)msg->srcAddr, (IArg)msg->dstAddr, (IArg)msg->dataLen);

        /* Pass to destination queue (on this proc), or callback: */
        RPMessage_send(dstProc, msg->dstAddr, msg->srcAddr,
                         (Ptr)msg->payload, msg->dataLen);

        VirtQueue_addUsedBuf(transport.virtQueue_fromHost, token,
                                                            RPMSG_BUF_SIZE);
        usedBufAdded = TRUE;
    }

    if (usedBufAdded)  {
       /* Tell host we've processed the buffers: */
       VirtQueue_kick(transport.virtQueue_fromHost);
    }
    Log_print0(Diags_EXIT, "<-- "FXNN);
}
#undef FXNN


#define FXNN "callback_availBufReady"
static Void callback_availBufReady(VirtQueue_Handle vq)
{

    if (vq == transport.virtQueue_fromHost)  {
       /* Post a SWI to process all incoming messages */
        Log_print0(Diags_INFO, FXNN": virtQueue_fromHost kicked");
        Swi_post(transport.swiHandle);
    }
    else if (vq == transport.virtQueue_toHost) {
       /* Note: We normally post nothing for transport.virtQueue_toHost,
        * unless we were starved for buffers, and we turned on notifications.
        */
        Semaphore_post(transport.semHandle_toHost);
        Log_print0(Diags_INFO, FXNN": virtQueue_toHost kicked");
    }
}
#undef FXNN

/* =============================================================================
 *  RPMessage Functions:
 * =============================================================================
 */

/*
 *  ======== MessasgeQCopy_init ========
 *
 *
 */
#define FXNN "RPMessage_init"
Void RPMessage_init(UInt16 remoteProcId)
{
    GateHwi_Params gatePrms;
    Semaphore_Params semParams;
    int     i;
    Registry_Result result;
    Bool    isHost;
    VirtQueue_Params vqParams;

    if (curInit++) {
        Log_print1(Diags_ENTRY, "--> "FXNN": (remoteProcId=%d)",
                    (IArg)remoteProcId);
        goto exit;  /* module already initialized */
    }

    /* register with xdc.runtime to get a diags mask */
    result = Registry_addModule(&Registry_CURDESC, MODULE_NAME);
    Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

    /* Log should be after the Registry_CURDESC is initialized */
    Log_print1(Diags_ENTRY, "--> "FXNN": (remoteProcId=%d)",
                (IArg)remoteProcId);

    /* Gate to protect module object and lists: */
    GateHwi_Params_init(&gatePrms);
    module.gateH = GateHwi_create(&gatePrms, NULL);

    /* Initialize Module State: */
    for (i = 0; i < MAXMESSAGEQOBJECTS; i++) {
       module.msgqObjects[i] = NULL;
    }

    /* store handle to heap created at config time */
    module.heap = ti_ipc_rpmsg_RPMessage_heap;

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;
    transport.semHandle_toHost = Semaphore_create(0, &semParams, NULL);

    isHost = (MultiProc_self() == MultiProc_getId("HOST"));

    /* Initialize Transport related objects: */

    VirtQueue_Params_init(&vqParams);
    if (isHost)  {
      /* We don't handle this case currently! Host would need to prime vq. */
      Assert_isTrue(FALSE, NULL);
    }
    else {
#if defined(OMAP5) || defined(VAYU)
      vqParams.callback = callback_availBufReady;
#else
      vqParams.callback = (xdc_Fxn)callback_availBufReady;
#endif
    }

    /*
     * Create a pair VirtQueues (one for sending, one for receiving).
     * Note: First one gets an even, second gets odd vq ID.
     */
    vqParams.vqId = ID_SELF_TO_HOST;
    transport.virtQueue_toHost   = (Ptr)VirtQueue_create(remoteProcId,
                                                    &vqParams, NULL);
    vqParams.vqId = ID_HOST_TO_SELF;
    transport.virtQueue_fromHost = (Ptr)VirtQueue_create(remoteProcId,
                                                    &vqParams, NULL);

    /* Plug Vring Interrupts, and wait for host ready to recv kick: */
    VirtQueue_startup(remoteProcId, isHost);

    /* construct the Swi to process incoming messages: */
    transport.swiHandle = Swi_create(RPMessage_swiFxn, NULL, NULL);

exit:
    Log_print0(Diags_EXIT, "<-- "FXNN);
}
#undef FXNN

/*
 *  ======== MessasgeQCopy_finalize ========
 */
#define FXNN "RPMessage_finalize"
Void RPMessage_finalize()
{
    Log_print0(Diags_ENTRY, "--> "FXNN);

    if (!curInit || --curInit) {
         goto exit; /* module still in use, or uninitialized */
    }

    /* Tear down Module */
    Swi_delete(&(transport.swiHandle));

    GateHwi_delete(&module.gateH);

exit:
    Log_print0(Diags_EXIT, "<-- "FXNN);
}
#undef FXNN

/*
 *  ======== RPMessage_create ========
 */
#define FXNN "RPMessage_create"
RPMessage_Handle RPMessage_create(UInt32 reserved,
                                        RPMessage_callback cb,
                                        UArg arg,
                                        UInt32 * endpoint)
{
    RPMessage_Object    *obj = NULL;
    Bool                   found = FALSE;
    Int                    i;
    UInt16                 queueIndex = 0;
    IArg key;

    Log_print4(Diags_ENTRY, "--> "FXNN": "
                "(reserved=%d, cb=0x%x, arg=0x%x, endpoint=0x%x)",
                (IArg)reserved, (IArg)cb, (IArg)arg, (IArg)endpoint);

    Assert_isTrue((curInit > 0) , NULL);

    key = GateHwi_enter(module.gateH);

    if (reserved == RPMessage_ASSIGN_ANY)  {
       /* Search the array for a free slot above reserved: */
       for (i = RPMessage_MAX_RESERVED_ENDPOINT + 1;
           (i < MAXMESSAGEQOBJECTS) && (found == FALSE) ; i++) {
           if (module.msgqObjects[i] == NULL) {
            queueIndex = i;
            found = TRUE;
            break;
           }
       }
    }
    else if ((queueIndex = reserved) <= RPMessage_MAX_RESERVED_ENDPOINT) {
       if (module.msgqObjects[queueIndex] == NULL) {
           found = TRUE;
       }
    }

    if (found)  {
       obj = Memory_alloc(NULL, sizeof(RPMessage_Object), 0, NULL);
       if (obj != NULL) {
           if (cb) {
               /* Store callback and it's arg instead of semaphore: */
               obj->cb = cb;
               obj->arg= arg;
           }
           else {
               obj->cb = NULL;

               /* Allocate a semaphore to signal when messages received: */
               obj->semHandle = Semaphore_create(0, NULL, NULL);

               /* Create our queue of to be received messages: */
               obj->queue = List_create(NULL, NULL);
           }

           /* Store our endpoint, and object: */
           obj->queueId = queueIndex;
           module.msgqObjects[queueIndex] = obj;

           /* See RPMessage_unblock() */
           obj->unblocked = FALSE;

           *endpoint    = queueIndex;
           Log_print1(Diags_LIFECYCLE, FXNN": endPt created: %d",
                        (IArg)queueIndex);
       }
    }

    GateHwi_leave(module.gateH, key);

    Log_print1(Diags_EXIT, "<-- "FXNN": 0x%x", (IArg)obj);
    return (obj);
}
#undef FXNN

/*
 *  ======== RPMessage_delete ========
 */
#define FXNN "RPMessage_delete"
Int RPMessage_delete(RPMessage_Handle *handlePtr)
{
    Int                    status = RPMessage_S_SUCCESS;
    RPMessage_Object    *obj;
    Queue_elem             *payload;
    IArg                   key;

    Log_print1(Diags_ENTRY, "--> "FXNN": (handlePtr=0x%x)", (IArg)handlePtr);

    Assert_isTrue((curInit > 0) , NULL);

    if (handlePtr && (obj = (RPMessage_Object *)(*handlePtr)))  {

       if (obj->cb) {
           obj->cb = NULL;
           obj->arg= NULL;
       }
       else {
           Semaphore_delete(&(obj->semHandle));

           /* Free/discard all queued message buffers: */
           while ((payload = (Queue_elem *)List_get(obj->queue)) != NULL) {
               HeapBuf_free(module.heap, (Ptr)payload,
                       ti_ipc_rpmsg_RPMessage_messageBufferSize);
           }

           List_delete(&(obj->queue));
       }

       /* Null out our slot: */
       key = GateHwi_enter(module.gateH);
       module.msgqObjects[obj->queueId] = NULL;
       GateHwi_leave(module.gateH, key);

       Log_print1(Diags_LIFECYCLE, FXNN": endPt deleted: %d",
                        (IArg)obj->queueId);

       /* Now free the obj */
       Memory_free(NULL, obj, sizeof(RPMessage_Object));

       *handlePtr = NULL;
    }

    Log_print1(Diags_EXIT, "<-- "FXNN": %d", (IArg)status);
    return(status);
}
#undef FXNN

/*
 *  ======== RPMessage_recv ========
 */
#define FXNN "RPMessage_recv"
Int RPMessage_recv(RPMessage_Handle handle, Ptr data, UInt16 *len,
                      UInt32 *rplyEndpt, UInt timeout)
{
    Int                 status = RPMessage_S_SUCCESS;
    RPMessage_Object *obj = (RPMessage_Object *)handle;
    Bool                semStatus;
    Queue_elem          *payload;

    Log_print5(Diags_ENTRY, "--> "FXNN": (handle=0x%x, data=0x%x, len=0x%x,"
               "rplyEndpt=0x%x, timeout=%d)", (IArg)handle, (IArg)data,
               (IArg)len, (IArg)rplyEndpt, (IArg)timeout);

    Assert_isTrue((curInit > 0) , NULL);
    /* A callback was set: client should not be calling this fxn! */
    Assert_isTrue((!obj->cb), NULL);

    /* Check vring for pending messages before we block: */
    Swi_post(transport.swiHandle);

    /*  Block until notified. */
    semStatus = Semaphore_pend(obj->semHandle, timeout);

    if (semStatus == FALSE)  {
       status = RPMessage_E_TIMEOUT;
       Log_print0(Diags_STATUS, FXNN": Sem pend timeout!");
    }
    else if (obj->unblocked) {
       status = RPMessage_E_UNBLOCKED;
    }
    else  {
       payload = (Queue_elem *)List_get(obj->queue);
       Assert_isTrue((payload), NULL);
    }

    if (status == RPMessage_S_SUCCESS)  {
       /* Now, copy payload to client and free our internal msg */
       memcpy(data, payload->data, payload->len);
       *len = payload->len;
       *rplyEndpt = payload->src;

       HeapBuf_free(module.heap, (Ptr)payload,
                    (payload->len + sizeof(Queue_elem)));
    }

    Log_print1(Diags_EXIT, "<-- "FXNN": %d", (IArg)status);
    return (status);
}
#undef FXNN

/*
 *  ======== RPMessage_send ========
 */
#define FXNN "RPMessage_send"
Int RPMessage_send(UInt16 dstProc,
                      UInt32 dstEndpt,
                      UInt32 srcEndpt,
                      Ptr    data,
                      UInt16 len)
{
    Int               status = RPMessage_S_SUCCESS;
    RPMessage_Object   *obj;
    Int16             token = 0;
    RPMessage_Msg  msg;
    Queue_elem        *payload;
    UInt              size;
    IArg              key;
    int length;

    Log_print5(Diags_ENTRY, "--> "FXNN": (dstProc=%d, dstEndpt=%d, "
               "srcEndpt=%d, data=0x%x, len=%d", (IArg)dstProc, (IArg)dstEndpt,
               (IArg)srcEndpt, (IArg)data, (IArg)len);

    Assert_isTrue((curInit > 0) , NULL);

    if (dstProc != MultiProc_self()) {
        /* Send to remote processor: */
        do {
            token = VirtQueue_getAvailBuf(transport.virtQueue_toHost,
                    (Void **)&msg, &length);
        } while (token < 0 && Semaphore_pend(transport.semHandle_toHost,
                                             BIOS_WAIT_FOREVER));
        if (token >= 0) {
            /* Copy the payload and set message header: */
            memcpy(msg->payload, data, len);
            msg->dataLen = len;
            msg->dstAddr = dstEndpt;
            msg->srcAddr = srcEndpt;
            msg->flags = 0;
            msg->reserved = 0;

            VirtQueue_addUsedBuf(transport.virtQueue_toHost, token,
                                                            RPMSG_BUF_SIZE);
            VirtQueue_kick(transport.virtQueue_toHost);
        }
        else {
            status = RPMessage_E_FAIL;
            Log_print0(Diags_STATUS, FXNN": getAvailBuf failed!");
        }
    }
    else {
        /* Put on a Message queue on this processor: */

        /* Protect from RPMessage_delete */
        key = GateHwi_enter(module.gateH);
        obj = module.msgqObjects[dstEndpt];
        GateHwi_leave(module.gateH, key);

        if (obj == NULL) {
            Log_print1(Diags_STATUS, FXNN": no object for endpoint: %d",
                   (IArg)dstEndpt);
            status = RPMessage_E_NOENDPT;
            return status;
        }

        /* If callback registered, call it: */
        if (obj->cb) {
            Log_print2(Diags_INFO, FXNN": calling callback with data len: "
                            "%d, from: %d", len, srcEndpt);
            obj->cb(obj, obj->arg, data, len, srcEndpt);
        }
        else {
            /* else, put on a Message queue on this processor: */
            /* Allocate a buffer to copy the payload: */
            size = len + sizeof(Queue_elem);

            /* HeapBuf_alloc() is non-blocking, so needs protection: */
            key = GateHwi_enter(module.gateH);
            payload = (Queue_elem *)HeapBuf_alloc(module.heap, size, 0, NULL);
            GateHwi_leave(module.gateH, key);

            if (payload != NULL)  {
                memcpy(payload->data, data, len);
                payload->len = len;
                payload->src = srcEndpt;

                /* Put on the endpoint's queue and signal: */
                List_put(obj->queue, (List_Elem *)payload);
                Semaphore_post(obj->semHandle);
            }
            else {
                status = RPMessage_E_MEMORY;
                Log_print0(Diags_STATUS, FXNN": HeapBuf_alloc failed!");
            }
        }
    }

    Log_print1(Diags_EXIT, "<-- "FXNN": %d", (IArg)status);
    return (status);
}
#undef FXNN

/*
 *  ======== RPMessage_unblock ========
 */
#define FXNN "RPMessage_unblock"
Void RPMessage_unblock(RPMessage_Handle handle)
{
    RPMessage_Object *obj = (RPMessage_Object *)handle;

    Log_print1(Diags_ENTRY, "--> "FXNN": (handle=0x%x)", (IArg)handle);

    Assert_isTrue((!obj->cb), NULL);
    /* Set instance to 'unblocked' state, and post */
    obj->unblocked = TRUE;
    Semaphore_post(obj->semHandle);
    Log_print0(Diags_EXIT, "<-- "FXNN);
}
#undef FXNN
