/*
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  @file   Fault.c
 *
 *  @brief  Sample application for fault recovery between MPU and Remote Proc
 *
 *  ============================================================================
 */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* IPC Headers */
#include <ti/ipc/Std.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>

/* App defines:  Must match on remote proc side: */
#define HEAPID              0u
#define SLAVE_MESSAGEQNAME  "SLAVE"
#define MPU_MESSAGEQNAME    "HOST"

#define PROC_ID_DFLT        1     /* Host is zero, remote cores start at 1 */
#define NUM_LOOPS_DFLT      100

typedef struct SyncMsg {
    MessageQ_MsgHeader header;
    UInt32 numLoops;  /* also used for msgId */
    UInt32 print;
    Int32 faultId;
} SyncMsg ;

Int MessageQApp_execute(UInt32 numLoops, UInt16 procId, UInt32 faultId)
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
        ((SyncMsg *)msg)->faultId = faultId;

        /* Have the remote proc reply to this message queue */
        MessageQ_setReplyQueue(msgqHandle, msg);

        if (faultId != 0) {
            printf("About to send fault command, hit ENTER to continue...\n");
            getchar();
        }

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

        if (faultId == 1) {
            printf("About to attempt sending data, hit ENTER to continue...\n");
            getchar();
            /* Reset fault id for next round */
            faultId = 0;
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
    if (MessageQ_delete(&msgqHandle) < 0) {
        printf("Error in MessageQ_delete [%d]\n", status);
    }

exit:
    printf("Leaving MessageQApp_execute\n\n");

    return (status);
}

int main (int argc, char ** argv)
{
    Int32 status = 0;
    int opt;
    UInt32 numLoops = NUM_LOOPS_DFLT;
    UInt16 procId = PROC_ID_DFLT;
    UInt32 faultId = 0;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
          case 'f':
            /*
             * Argument for -f corresponds to remote-side "fault" commands.
             * Negative commands cause remote fault before remote MessageQ_put.
             * Positive commands cause remote fault after remote MessageQ_put.
             */
            faultId = atoi(optarg);
            printf("fault %d will be sent in 1st msg\n", faultId);
            break;

          default:
            fprintf(stderr, "Unknown arg '%s'\n", optarg);
            return 1;
        }
    }

    /* Parse Args: */
    switch (argc - optind + 1) {
        case 1:
           /* use defaults */
           break;
        case 2:
           numLoops   = atoi(argv[optind]);
           break;
        case 3:
           numLoops   = atoi(argv[optind]);
           procId     = atoi(argv[optind + 1]);
           break;
        default:
           printf("Usage: %s [<numLoops>] [<ProcId>]\n", argv[0]);
           printf("\tDefaults: numLoops: %d; ProcId: %d\n",
                   NUM_LOOPS_DFLT, PROC_ID_DFLT);
           exit(0);
    }

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

    if (MessageQApp_execute(numLoops, procId, faultId) < 0) {
        int nAttachAttempts = 1;

        printf("MessageQApp_execute failed, attempting stop/start)...\n");
        Ipc_stop();
        while (Ipc_start() != Ipc_S_SUCCESS) {
            nAttachAttempts++;
            if ((nAttachAttempts % 1000) == 0) {
                printf("Ipc_start() failed\n");
            }
        }
        printf("Ipc_start() succeeded (after %d tries)\n", nAttachAttempts);

        /* call without fault this time */
        MessageQApp_execute(numLoops, procId, 0);
    }

    Ipc_stop();

exit:
    return (status);
}
