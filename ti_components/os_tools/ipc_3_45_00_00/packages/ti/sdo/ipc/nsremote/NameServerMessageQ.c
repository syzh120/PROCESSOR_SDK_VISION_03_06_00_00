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
 *  ======== NameServerMessageQ.c ========
 */

#include <xdc/std.h>
#include <string.h>
#include <stdlib.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/knl/ISync.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/syncs/SyncSwi.h>
#include <ti/sysbios/gates/GateMutex.h>

#include "package/internal/NameServerMessageQ.xdc.h"

#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/_MessageQ.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/utils/_NameServer.h>

/*
 *  Determine name array size:
 *    maxNameLen / ((bits per char) / (bits per byte) * (sizeof(Bits32)))
 */
#define MAXNAMEINCHAR   (NameServerMessageQ_maxNameLen / \
                        (xdc_target__bitsPerChar / 8))
#define NAMEARRAYSIZE   (((MAXNAMEINCHAR - 1) / sizeof(Bits32)) + 1)

#define MESSAGEQ_INDEX 0

/* message sent to remote procId */
typedef struct NameServerMsg {
    MessageQ_MsgHeader header;  /* message header                   */
    Bits32  value;              /* holds value                      */
    Bits32  request;            /* whether its a request/response   */
    Bits32  requestStatus;      /* status of request                */
    Bits32  reserved;           /* reserved field                   */
                                /* name of NameServer instance      */
    Bits32  instanceName[NAMEARRAYSIZE];
                                /* name of NameServer entry         */
    Bits32  name[NAMEARRAYSIZE];
} NameServerMsg;

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */
Void NameServerMessageQ_Instance_init(NameServerMessageQ_Object *obj,
        UInt16 remoteProcId,
        const NameServerMessageQ_Params *params)
{
    /* Assert that remoteProcId is valid */
    Assert_isTrue(remoteProcId != MultiProc_self() &&
                  remoteProcId != MultiProc_INVALIDID,
                  Ipc_A_invParam);

    obj->remoteProcId = remoteProcId;

    /* register the remote driver with NameServer */
    ti_sdo_utils_NameServer_registerRemoteDriver(
            NameServerMessageQ_Handle_upCast(obj), remoteProcId);
}

/*
 *  ======== NameServerMessageQ_Instance_finalize ========
 */
Void NameServerMessageQ_Instance_finalize(NameServerMessageQ_Object *obj)
{
    /* unregister remote driver from NameServer module */
    ti_sdo_utils_NameServer_unregisterRemoteDriver(obj->remoteProcId);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== NameServerMessageQ_Module_startup ========
 */
Int NameServerMessageQ_Module_startup(Int phase)
{
    MessageQ_Params2  messageQParams;

    /* Ensure MessageQ and SyncSwi Module_startup() have completed */
    if ((ti_sdo_ipc_MessageQ_Module_startupDone() == FALSE) ||
        (ti_sysbios_syncs_SyncSwi_Module_startupDone() == FALSE)) {
        return (Startup_NOTDONE);
    }

    /* Create the message queue for NameServer using SyncSwi */
    MessageQ_Params2_init(&messageQParams);
    messageQParams.synchronizer = NameServerMessageQ_module->syncSwiHandle;
    messageQParams.queueIndex = MESSAGEQ_INDEX;
    NameServerMessageQ_module->msgHandle =
        (ti_sdo_ipc_MessageQ_Handle)MessageQ_create2(NULL, &messageQParams);

    /* assert msgHandle is not null */
    Assert_isTrue(NameServerMessageQ_module->msgHandle != NULL,
        Ipc_A_nullPointer);

    /* assert this is the first MessageQ created */
    Assert_isTrue((MessageQ_getQueueId((MessageQ_Handle)
        NameServerMessageQ_module->msgHandle) & 0xffff) == MESSAGEQ_INDEX,
        NameServerMessageQ_A_reservedMsgQueueId);

    return (Startup_DONE);
}

/*
 *  ======== NameServerMessageQ_attach ========
 */
Int NameServerMessageQ_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    NameServerMessageQ_Params params;
    NameServerMessageQ_Handle handle;
    Int status = NameServerMessageQ_E_FAIL;
    Error_Block eb;

    Error_init(&eb);

    /* init params */
    NameServerMessageQ_Params_init(&params);

    /* create driver to remote proc */
    handle = NameServerMessageQ_create(remoteProcId,
                                       &params,
                                       &eb);

    if (handle != NULL) {
        status = NameServerMessageQ_S_SUCCESS;
    }

    return (status);
}

/*
 *  ======== NameServerMessageQ_detach ========
 */
Int NameServerMessageQ_detach(UInt16 remoteProcId)
{
    NameServerMessageQ_Handle handle;
    Int status = NameServerMessageQ_S_SUCCESS;

    /* return handle based upon procId */
    for (handle = NameServerMessageQ_Object_first(); handle != NULL;
        handle = NameServerMessageQ_Object_next(handle)) {
        if (handle->remoteProcId == remoteProcId) {
            break;
        }
    }

    if (handle == NULL) {
        status = NameServerMessageQ_E_FAIL;
    }
    else {
        NameServerMessageQ_delete(&handle);
    }

    return (status);
}

/*
 *  ======== NameServerMessageQ_get ========
 */
Int NameServerMessageQ_get(NameServerMessageQ_Object *obj,
                           String instanceName,
                           String name,
                           Ptr value,
                           UInt32 *valueLen,
                           ISync_Handle syncHandle,
                           Error_Block *eb)
{
    Int status;
    IArg key;
    MessageQ_QueueId queueId;
    NameServerMsg    *msg;
    Semaphore_Handle semRemoteWait = NameServerMessageQ_module->semRemoteWait;
    GateMutex_Handle gateMutex = NameServerMessageQ_module->gateMutex;

    /* enter gate - prevent multiple threads from entering */
    key = GateMutex_enter(gateMutex);

    /* alloc a message from specified heap */
    msg = (NameServerMsg *)MessageQ_alloc(NameServerMessageQ_heapId,
                                          sizeof(NameServerMsg));

    /* make sure message is not NULL */
    if (msg == NULL) {
        Error_raise(eb, NameServerMessageQ_E_outOfMemory,
                    NameServerMessageQ_heapId, 0);
        return (NameServer_E_OSFAILURE);
    }

    /* make sure this is a request message */
    msg->request = NameServerMessageQ_REQUEST;
    msg->requestStatus = 0;

    /* assert length is smaller than max (must have room for null character) */
    Assert_isTrue(strlen(instanceName) < MAXNAMEINCHAR,
            NameServerMessageQ_A_nameIsTooLong);

    /* copy the name of instance into putMsg */
    strncpy((Char *)msg->instanceName, instanceName, MAXNAMEINCHAR - 1);
    ((Char *)msg->instanceName) [MAXNAMEINCHAR - 1] = '0';

    /* assert length is smaller than max (must have room for null character) */
    Assert_isTrue(strlen(name) < MAXNAMEINCHAR,
            NameServerMessageQ_A_nameIsTooLong);

    /* copy the name of nameserver entry into putMsg */
    strncpy((Char *)msg->name, name, MAXNAMEINCHAR - 1);
    ((Char *)msg->name) [MAXNAMEINCHAR - 1] = '0';

    /* determine the queueId based upon the processor */
    queueId = MessageQ_openQueueId(MESSAGEQ_INDEX, obj->remoteProcId);

    /* set the reply procId */
    MessageQ_setReplyQueue(
        (MessageQ_Handle)NameServerMessageQ_module->msgHandle,
        (MessageQ_Msg)msg);

    /* send message to remote processor. */
    status = MessageQ_put(queueId, (MessageQ_Msg)msg);

    /* make sure message sent successfully */
    if (status < 0) {
        /* free the message */
        MessageQ_free((MessageQ_Msg)msg);

        return (NameServer_E_FAIL);
    }

    /* pend here until we get a response back from remote processor */
    status = Semaphore_pend(semRemoteWait, NameServerMessageQ_timeout);

    if (status == FALSE) {
        /* return timeout failure */
        return (NameServer_E_OSFAILURE);
    }

    /* get the message */
    msg = NameServerMessageQ_module->msg;

    if (msg->requestStatus) {
        /* name is found */

        /* set length to amount of data that was copied */
        *valueLen = sizeof(Bits32);

        /* set the contents of value */
        memcpy(value, &(msg->value), sizeof(Bits32));

        /* set the status to success */
        status = NameServer_S_SUCCESS;
    }
    else {
        /* name is not found */

        /* set status to not found */
        status = NameServer_E_NOTFOUND;
    }

    /* free the message */
    MessageQ_free((MessageQ_Msg)msg);

    /* leave the gate */
    GateMutex_leave(gateMutex, key);

    /* return success status */
    return (status);
}

/*
 *  ======== NameServerMessageQ_sharedMemReq ========
 */
SizeT NameServerMessageQ_sharedMemReq(Ptr sharedAddr)
{
    return (0);
}

/*
 *  ======== NameServerMessageQ_swiFxn ========
 */
Void NameServerMessageQ_swiFxn(UArg arg0, UArg arg1)
{
    NameServerMsg     *msg;
    NameServer_Handle handle;
    MessageQ_QueueId  queueId;
    Int               status = NameServer_E_FAIL;
    Semaphore_Handle  semRemoteWait = NameServerMessageQ_module->semRemoteWait;

    /* drain all messages in the messageQ */
    while (1) {
        /* get a message, this never waits */
        status = MessageQ_get(
                    (MessageQ_Handle)NameServerMessageQ_module->msgHandle,
                    (MessageQ_Msg *)&msg, 0);

        /* if no message then return */
        if (status != MessageQ_S_SUCCESS) {
            break;
        }

        if (msg->request == NameServerMessageQ_REQUEST) {
            /* reset value of status */
            status = NameServer_E_FAIL;

            /*
             *  Message is a request. Lookup name in NameServer table.
             *  Send a response message back to source processor.
             */
            handle = NameServer_getHandle((String)msg->instanceName);

            if (handle != NULL) {
                /* Search for the NameServer entry */
                status = NameServer_getLocalUInt32(handle,
                         (String)msg->name, &msg->value);
            }

            /* set the request status */
            if (status < 0) {
                msg->requestStatus = 0;
            }
            else {
                msg->requestStatus = 1;
            }

            /* specify message as a response */
            msg->request = NameServerMessageQ_RESPONSE;

            /* get the remote processor from the msg header */
            queueId = (UInt32)(msg->header.replyProc) << 16;

            /* send response message to remote processor */
            MessageQ_put(queueId, (MessageQ_Msg)msg);
        }
        else {
            /*
             *  This is a response message. At any given time, there is
             *  only one of these outstanding because of semMultiBlock.
             *  This allows us to safely set the Module state's msg pointer
             *  and post semaphore.
             */
            NameServerMessageQ_module->msg = msg;
            Semaphore_post(semRemoteWait);
        }

    }
}
