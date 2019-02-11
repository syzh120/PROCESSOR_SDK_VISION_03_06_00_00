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
/* =============================================================================
 *  @file   MessageQApp.c
 *
 *  @brief  Sample application for MessageQ module between MPU and Remote Proc
 *
 *  ============================================================================
 */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>

/* IPC Headers */
#include <ti/ipc/Std.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/transports/TransportRpmsg.h>

/* App defines:  Must match on remote proc side: */
#define HEAPID              0u
#define SLAVE_MESSAGEQNAME  "SLAVE"
#define MPU_MESSAGEQNAME    "HOST"

#define PROC_ID_DFLT        1     /* Host is zero, remote cores start at 1 */
#define NUM_LOOPS_DFLT   100

typedef struct SyncMsg {
    MessageQ_MsgHeader header;
    UInt32 numLoops;  /* also used for msgId */
    UInt32 print;
} SyncMsg ;

Int MessageQApp_execute(UInt32 numLoops, UInt16 procId)
{
    Int32                    status = 0;
    MessageQ_Msg             msg = NULL;
    MessageQ_Params          msgParams;
    UInt32                   i;
    MessageQ_QueueId         queueId = MessageQ_INVALIDMESSAGEQ;
    MessageQ_Handle          msgqHandle;
    char                     remoteQueueName[64];
    UInt32                   msgId;

    printf("Entered MessageQApp_execute\n");

    /* Create the local Message Queue for receiving. */
    MessageQ_Params_init(&msgParams);
    msgqHandle = MessageQ_create(MPU_MESSAGEQNAME, &msgParams);
    if (msgqHandle == NULL) {
        printf("Error in MessageQ_create\n");
        goto exit;
    }
    else {
        printf("Local MessageQId: 0x%x\n", MessageQ_getQueueId(msgqHandle));
    }

    sprintf(remoteQueueName, "%s_%s", SLAVE_MESSAGEQNAME,
             MultiProc_getName(procId));

    /* Poll until remote side has it's messageQ created before we send: */
    do {
        status = MessageQ_open(remoteQueueName, &queueId);
        sleep (1);
    } while (status == MessageQ_E_NOTFOUND);

    if (status < 0) {
        printf("Error in MessageQ_open [%d]\n", status);
        goto cleanup;
    }
    else {
        printf("Remote queueId  [0x%x]\n", queueId);
    }

    msg = MessageQ_alloc(HEAPID, sizeof(SyncMsg));
    if (msg == NULL) {
        printf("Error in MessageQ_alloc\n");
        MessageQ_close(&queueId);
        goto cleanup;
    }

    /* handshake with remote to set the number of loops */
    MessageQ_setReplyQueue(msgqHandle, msg);
    ((SyncMsg *)msg)->numLoops = numLoops;
    ((SyncMsg *)msg)->print = FALSE;
    MessageQ_put(queueId, msg);
    MessageQ_get(msgqHandle, &msg, MessageQ_FOREVER);

    printf("Exchanging %d messages with remote processor %s...\n",
           numLoops, MultiProc_getName(procId));

    for (i = 1 ; i <= numLoops; i++) {
        ((SyncMsg *)msg)->numLoops = i;

        /* Have the remote proc reply to this message queue */
        MessageQ_setReplyQueue(msgqHandle, msg);

        status = MessageQ_put(queueId, msg);
        if (status < 0) {
            printf("Error in MessageQ_put [%d]\n", status);
            MessageQ_free(msg);
            break;
        }

        status = MessageQ_get(msgqHandle, &msg, MessageQ_FOREVER);

        if (status < 0) {
            printf("Error in MessageQ_get [%d]\n", status);
            break;
        }
        else {
            /* validate the returned message */
            msgId = ((SyncMsg *)msg)->numLoops;
            if ((msg != NULL) && (msgId != i)) {
                printf("Data integrity failure!\n"
                        "    Expected %d\n"
                        "    Received %d\n",
                        i, msgId);
                break;
            }
        }

        if (numLoops <= 200) {
            printf("MessageQ_get #%d Msg = 0x%x\n", i, (UInt)msg);
        }
        else if ((i % 1000) == 0) {
            printf("MessageQ_get #%d Msg = 0x%x\n", i, (UInt)msg);
        }
    }

    printf("Exchanged %d messages with remote processor %s\n",
        (i-1), MultiProc_getName(procId));

    if (status >= 0) {
       printf("Sample application successfully completed!\n");
       MessageQ_free(msg);
    }

    MessageQ_close(&queueId);

cleanup:
    /* Clean-up */
    status = MessageQ_delete(&msgqHandle);
    if (status < 0) {
        printf("Error in MessageQ_delete [%d]\n", status);
    }

exit:
    printf("Leaving MessageQApp_execute\n\n");

    return (status);
}

int main (int argc, char ** argv)
{
    Int status = 0;
    UInt numLoops = NUM_LOOPS_DFLT;
    UInt16 procId = PROC_ID_DFLT;

    /* Parse Args: */
    switch (argc) {
        case 1:
           /* use defaults */
           break;
        case 2:
           numLoops   = atoi(argv[1]);
           break;
        case 3:
           numLoops   = atoi(argv[1]);
           procId     = atoi(argv[2]);
           break;
        default:
           printf("Usage: %s [<numLoops>] [<ProcId>]\n", argv[0]);
           printf("\tDefaults: numLoops: %d; ProcId: %d\n",
                   NUM_LOOPS_DFLT, PROC_ID_DFLT);
           exit(0);
    }

    /* configure the transport factory */
    Ipc_transportConfig(&TransportRpmsg_Factory);

    /* IPC initialization */
    status = Ipc_start();

    if (status < 0) {
        printf("Error: Ipc_start failed, error=%d\n", status);
        goto exit;
    }

    if ((procId == 0) || (procId >= MultiProc_getNumProcessors())) {
        printf("ProcId (%d) must be nonzero and less than %d\n",
                procId, MultiProc_getNumProcessors());
        Ipc_stop();
        exit(0);
    }
    printf("Using numLoops: %d; procId : %d\n", numLoops, procId);

    if (status >= 0) {
        MessageQApp_execute(numLoops, procId);
        Ipc_stop();
    }
    else {
        printf("Ipc_start failed: status = %d\n", status);
    }

exit:
    return (status);
}
