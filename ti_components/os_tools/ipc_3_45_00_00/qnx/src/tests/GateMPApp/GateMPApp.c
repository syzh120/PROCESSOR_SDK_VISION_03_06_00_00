/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
 *  ======== GateMPApp.c ========
 *
 */

/* host header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* package header files */
#include <ti/ipc/Std.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/GateMP.h>

/* local header files */
#include "GateMPApp.h"

#include <ti/shmemallocator/SharedMemoryAllocatorUsr.h>
#include <ti/ipc/tests/GateMPAppCommon.h>

/* module structure */
typedef struct {
    MessageQ_Handle       hostQue;    /* created locally */
    MessageQ_QueueId      slaveQue;   /* opened remotely */
    UInt16                heapId;     /* MessageQ heapId */
    UInt32                msgSize;    /* Size of messages */
    volatile UInt32 *     intPtr;     /* Integer pointer */
    UInt32                physAddr;   /* Physical address of shared memory */
    GateMP_Handle         hostGateMPHandle;  /* handle to host-created gate */
    GateMP_Handle         slaveGateMPHandle; /* handle to slave-created gate */
    shm_buf               buf;        /* shared memory buffer */
} GateMPApp_Module;

/* private data */
static GateMPApp_Module Module;


/*
 *  ======== GateMPApp_create ========
 */

Int GateMPApp_create()
{
    Int                 status    =0;
    MessageQ_Params     msgqParams;
    GateMP_Params       gateParams;

    printf("--> GateMPApp_create:\n");

    /* setting default values */
    Module.hostQue = NULL;
    Module.slaveQue = MessageQ_INVALIDMESSAGEQ;
    Module.heapId = GateMPApp_MsgHeapId;
    Module.intPtr = NULL;
    Module.physAddr = 0;
    Module.hostGateMPHandle = NULL;
    Module.slaveGateMPHandle = NULL;
    Module.msgSize = sizeof(GateMPApp_Msg);

    /* create local message queue (inbound messages) */
    MessageQ_Params_init(&msgqParams);

    Module.hostQue = MessageQ_create(GateMPApp_HostMsgQueName, &msgqParams);

    if (Module.hostQue == NULL) {
        printf("GateMPApp_create: Failed creating MessageQ\n");
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* open the remote message queue */
    do {
        status = MessageQ_open(GateMPApp_SlaveMsgQueName, &Module.slaveQue);
        sleep(1);
    } while (status == MessageQ_E_NOTFOUND);

    if (status < 0) {
        printf("GateMPApp_create: Failed opening MessageQ\n");
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* allocate space from shared memory for an integer */
    status = SHM_alloc_aligned(sizeof(UInt32), sizeof(UInt32), &Module.buf);
    if (status < 0) {
        printf("GateMPApp_create: Could not allocate shared memory\n");
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }
    Module.intPtr = (UInt32 *)Module.buf.vir_addr;
    Module.physAddr = (UInt32)Module.buf.phy_addr;

    if ((Module.intPtr == NULL) || (Module.physAddr == NULL)) {
        printf("GateMPApp_create: Failed to get buffer address\n");
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* create GateMP */
    GateMP_Params_init(&gateParams);

    gateParams.name             = GATEMP_HOST_NAME;
    gateParams.localProtect     = GateMP_LocalProtect_PROCESS;
    gateParams.remoteProtect    = GateMP_RemoteProtect_SYSTEM;

    Module.hostGateMPHandle = GateMP_create (&gateParams);

    if (Module.hostGateMPHandle == NULL) {
        status = GATEMPAPP_E_FAILURE;
        printf("GateMPApp_create: Failed to create GateMP\n");
        goto leave;
    }
    printf("GateMPApp_create: Host is ready\n");

leave:
    printf("<-- GateMPApp_create:\n");
    return(status);
}


/*
 *  ======== GateMPApp_delete ========
 */
Int GateMPApp_delete(Void)
{
    Int         status;
    GateMPApp_Msg *   msg;

    printf("--> GateMPApp_delete:\n");

    /* allocate message */
    msg = (GateMPApp_Msg *)MessageQ_alloc(Module.heapId, Module.msgSize);

    if (msg == NULL) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* set the return address in the message header */
    MessageQ_setReplyQueue(Module.hostQue, (MessageQ_Msg)msg);

    /* sending shutdown command */
    msg->cmd = GATEMPAPP_CMD_SHUTDOWN;
    MessageQ_put(Module.slaveQue, (MessageQ_Msg)msg);

    /* wait for acknowledgement message */
    status = MessageQ_get(Module.hostQue, (MessageQ_Msg *)&msg,
            MessageQ_FOREVER);

    if (status < 0) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    if (msg->cmd != GATEMPAPP_CMD_SHUTDOWN_ACK) {
        status = GATEMPAPP_E_UNEXPECTEDMSG;
        goto leave;
    }

    /* free the message */
    MessageQ_free((MessageQ_Msg)msg);

    /* delete GateMP */
    GateMP_delete(&Module.hostGateMPHandle);

    /* free shared memory buffer */
    status = SHM_release(&Module.buf);
    if(status < 0) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* close remote resources */
    status = MessageQ_close(&Module.slaveQue);

    if (status < 0) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* delete the host message queue */
    status = MessageQ_delete(&Module.hostQue);

    if (status < 0) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

leave:
    printf("<-- GateMPApp_delete:\n");
    return(status);
}


/*
 *  ======== GateMPApp_exec ========
 */
Int GateMPApp_exec(Void)
{
    Int         status;
    Int         i;
    GateMPApp_Msg *   msg;
    IArg        gateKey         = 0;
    UInt32      num;
    UInt32      prevNum;

    printf("--> GateMPApp_exec:\n");

    /* set shared variable initial value */
    *Module.intPtr = 500;

    /* allocate message */
    msg = (GateMPApp_Msg *)MessageQ_alloc(Module.heapId, Module.msgSize);
    if (msg == NULL) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* set the return address in the message header */
    MessageQ_setReplyQueue(Module.hostQue, (MessageQ_Msg)msg);

    /* fill in message payload */
    msg->cmd = GATEMPAPP_CMD_SPTR_ADDR;
    msg->payload = Module.physAddr;

    /* send message */
    MessageQ_put(Module.slaveQue, (MessageQ_Msg)msg);

    /* wait for return message */
    status = MessageQ_get(Module.hostQue, (MessageQ_Msg *)&msg,
        MessageQ_FOREVER);
    if (status < 0) {
        goto leave;
    }

    if (msg->cmd != GATEMPAPP_CMD_SPTR_ADDR_ACK)
    {
        status = GATEMPAPP_E_UNEXPECTEDMSG;
        goto leave;
    }

    /* free the message */
    MessageQ_free((MessageQ_Msg)msg);

    /* open slave-created GateMP */
    do {
        status = GateMP_open(GATEMP_SLAVE_NAME, &Module.slaveGateMPHandle);
    } while (status == GateMP_E_NOTFOUND);

    if (status < 0) {
        printf("GateMPApp_exec: Failed to open slave-created GateMP");
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    printf("GateMPApp_exec: Using host-created gate\n");
    for (i = 0; i < LOOP_ITR; i++) {
        /* read the shared variable as long as no one is currently modifying
         * it
         */

        /* enter GateMP */
        gateKey = GateMP_enter(Module.hostGateMPHandle);

        /* read shared variable value */
        prevNum = *Module.intPtr;

        /* randomly modify the shared variable */
        if (rand() % 2) {
            *Module.intPtr -= 1;
        }
        else {
            *Module.intPtr += 1;
        }

        /* read shared variable value again*/
        num = *Module.intPtr;

        if ((prevNum != num + 1) && (prevNum != num - 1)) {
            printf("GateMPApp_exec: unexpected variable value." \
                "Test failed.\n");
            printf("GateMPApp_exec: Previous value: %d, " \
                "current value=%d\n", prevNum, num);

            status = GATEMPAPP_E_FAILURE;
            goto leave;
        }

        /* exit GateMP */
        GateMP_leave(Module.hostGateMPHandle, gateKey);
    }

    /* allocate message */
    msg = (GateMPApp_Msg *)MessageQ_alloc(Module.heapId, Module.msgSize);
    if (msg == NULL) {
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    /* set the return address in the message header */
    MessageQ_setReplyQueue(Module.hostQue, (MessageQ_Msg)msg);

    /* fill in message payload */
    msg->cmd = GATEMPAPP_CMD_SYNC;

    /* send sync message */
    MessageQ_put(Module.slaveQue, (MessageQ_Msg)msg);

    /* wait for return sync message before we switch gates */
    status = MessageQ_get(Module.hostQue, (MessageQ_Msg *)&msg,
        MessageQ_FOREVER);
    if (status < 0) {
        goto leave;
    }

    if (msg->cmd != GATEMPAPP_CMD_SYNC)
    {
        status = GATEMPAPP_E_UNEXPECTEDMSG;
        goto leave;
    }

    /* free the message */
    MessageQ_free((MessageQ_Msg)msg);

    printf("GateMPApp_exec: Using slave-created gate\n");
    for (i = 0; i < LOOP_ITR; i++) {
        /* read the shared variable as long as no one is currently modifying
         * it
         */

        /* enter GateMP */
        gateKey = GateMP_enter(Module.slaveGateMPHandle);

        /* read shared variable value */
        prevNum = *Module.intPtr;

        /* randomly modify the shared variable */
        if (rand() % 2) {
            *Module.intPtr -= 1;
        }
        else {
            *Module.intPtr += 1;
        }

        /* read shared variable value again */
        num = *Module.intPtr;

        if ((prevNum != num + 1) && (prevNum != num - 1)) {
            printf("GateMPApp_exec: unexpected variable value." \
                "Test failed.\n");
            printf("GateMPApp_exec: Previous value: %d, " \
                "current value=%d\n", prevNum, num);

            status = GATEMPAPP_E_FAILURE;
            goto leave;
        }

        /* exit GateMP */
        GateMP_leave(Module.slaveGateMPHandle, gateKey);
    }

leave:
    if (Module.slaveGateMPHandle) {
        GateMP_close(&Module.slaveGateMPHandle);
    }

    printf("<-- GateMPApp_exec: %d\n", status);
    return(status);
}
