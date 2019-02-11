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
 *  @file   Msgq100.c
 *
 *  @brief  Bug validation test: ####
 *
 *  ============================================================================
 */

/* standard headers */
#include <stdio.h>
#include <stdlib.h>

/* ipc headers */
#include <ti/ipc/Std.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/transports/TransportRpmsg.h>

#define HEAPID                  0               /* not actually used */
#define SLAVE_MSGQNAME          "SLAVE"
#define MPU_MESSAGEQNAME        "HOST"
#define Main_MAXQUE             10
#define NUM_LOOPS_DFLT          4

#define Main_USAGE "\
Usage:\n\
    Msgq100 [options] procId ...\n\
\n\
Arguments:\n\
    procId: remote processor id\n\
\n\
Options:\n\
    h   : print this help message\n\
    l   : list the available remote processors\n\
\n\
Examples:\n\
    Msgq100 1\n\
    Msgq100 1 4\n\
    Msgq100 -h\n\
\n"

typedef struct SyncMsg {
    MessageQ_MsgHeader header;
    UInt32 numLoops;
    UInt32 print;
} SyncMsg;

/* private functions */
static int Main_main(Void);

static int Main_procCount = 0;
static UInt16 Main_procAry[Main_MAXQUE];
static MessageQ_QueueId Main_msgQueAry[Main_MAXQUE];


/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    Int32 status = 0;
    int arg, opt;
    int p;
    UInt16 procId;
    UInt16 numProcs;
    String name;

    /* configure the transport factory */
    Ipc_transportConfig(&TransportRpmsg_Factory);

    /* parse the command line options (e.g. -h) */
    for (arg = 1; (arg < argc) && (argv[arg][0] == '-'); arg++) {

        /* convert option into numeric value */
        opt = (int)argv[arg][1];

        switch (opt) {
            case 'h': /* -h */
                printf("%s", Main_USAGE);
                exit(0);
                break;

            case 'l': /* -l */
                printf("Processor List\n");
                status = Ipc_start();
                if (status >= 0) {
                    numProcs = MultiProc_getNumProcessors();
                    for (p = 0; p < numProcs; p++) {
                        name = MultiProc_getName(p);
                        printf("    procId=%d, procName=%s\n", p, name);
                    }
                    Ipc_stop();
                }
                else {
                    printf(
                        "Error: %s, line %d: Ipc_start failed\n",
                        __FILE__, __LINE__);
                    goto leave;
                }
                exit(0);
                break;

            default:
                printf(
                    "Error: %s, line %d: invalid option, %c\n",
                    __FILE__, __LINE__, (Char)opt);
                printf("%s", Main_USAGE);
                status = -1;
                goto leave;
        }
    }

    /* parse the command line arguments */
    while (arg < argc) {

        if (Main_procCount == Main_MAXQUE) {
            printf("Error: too many procIds (max=%d)\n", Main_MAXQUE);
            status = -1;
            goto leave;
        }

        /* remaining arguments is a list of procId's */
        Main_procAry[Main_procCount++] = atoi(argv[arg]);

        arg++;
    }

    /* ipc initialization */
    status = Ipc_start();

    if (status < 0) {
        printf("Error: Ipc_start failed: status = %d\n", status);
        status = -1;
        goto leave;
    }

    /* validate procId list, must do this after Ipc_start() */
    for (p = 0; p < Main_procCount; p++) {
        procId = Main_procAry[p];

        if (procId >= MultiProc_getNumProcessors()) {
            printf("Error: procId must be less than %d\n",
                    MultiProc_getNumProcessors());
            status = -1;
            goto stop;
        }
    }

    /* execute main body of test */
    status = Main_main();

    if (status == 0) {
        printf("Test PASSED\n");
    }

stop:
    /* ipc finalization */
    Ipc_stop();

leave:
    return(status);
}

/*
 *  ======== Main_main ========
 */
int Main_main(Void)
{
    int                 status = 0;
    MessageQ_Msg        msg = NULL;
    MessageQ_Params     msgParams;
    int                 p, j;
    UInt16              procId;
    MessageQ_Handle     hostQ;
    char                queueName[64];
    String              procName;

    printf("Entered Main_main\n");

    /* create local message queue for receiving messages */
    MessageQ_Params_init(&msgParams);

    hostQ = MessageQ_create(MPU_MESSAGEQNAME, &msgParams);

    if (hostQ == NULL) {
        printf("Error: MessageQ_create() failed\n");
        goto leave;
    }
    printf("HOST MessageQId: 0x%x\n", MessageQ_getQueueId(hostQ));

    /* open remote message queues */
    for (p = 0; p < Main_procCount; p++) {

        /* compute remote queue name */
        procId = Main_procAry[p];
        procName = MultiProc_getName(procId);
        sprintf(queueName, "%s_%s", SLAVE_MSGQNAME, procName);

        /* open the remote message queue, loop until queue is available */
        do {
            status = MessageQ_open(queueName, &Main_msgQueAry[p]);

            if (status == MessageQ_E_NOTFOUND) {
                sleep(1);
            }
        } while (status == MessageQ_E_NOTFOUND);

        if (status < 0) {
            printf("Error: MessageQ_open(\"%s\") failed, status=%d\n",
                    queueName, status);
            status = -1;
            goto cleanup;
        }
        printf("Remote queueId[%d]=0x%x\n", p, Main_msgQueAry[p]);
    }

    /* allocate handshake message */
    msg = MessageQ_alloc(HEAPID, sizeof(SyncMsg));

    if (msg == NULL) {
        printf("Error: MessageQ_alloc() failed\n");
        status = -1;
        goto cleanup;
    }

    /* handshake with each remote processor to set the number of loops */
    for (p = 0; p < Main_procCount; p++) {
        MessageQ_setReplyQueue(hostQ, msg);
        ((SyncMsg *)msg)->numLoops = NUM_LOOPS_DFLT;
        ((SyncMsg *)msg)->print = TRUE;
        MessageQ_put(Main_msgQueAry[p], msg);
        MessageQ_get(hostQ, &msg, MessageQ_FOREVER);

        procId = Main_procAry[p];
        procName = MultiProc_getName(procId);
        printf("Exchanging %d messages with remote processor %s...\n",
               NUM_LOOPS_DFLT, procName);
    }

    /* free handshake message */
    MessageQ_free(msg);

    /* allocate and send all messages */
    for (p = 0; p < Main_procCount; p++) {
        for (j = 1; j <= NUM_LOOPS_DFLT; j++) {

            /* allocate message */
            msg = MessageQ_alloc(HEAPID, sizeof(SyncMsg));

            if (msg == NULL) {
                printf("Error: MessageQ_alloc() failed\n");
                status = -1;
                goto cleanup;
            }

            /* fill in message */
            MessageQ_setReplyQueue(hostQ, msg);
            ((SyncMsg *)msg)->numLoops = j;

            /* send the messages */
            status = MessageQ_put(Main_msgQueAry[p], msg);

            if (status < 0) {
                printf("Error: MessageQ_put() failed, procId=%d, status=%d\n",
                        Main_procAry[p], status);
                status = -1;
                goto cleanup;
            }
        }
    }

    /* delay here to allow for return message deliver */
    printf("Waiting...");
    sleep(3);
    printf("done.\n");

    /* receive and free all messages */
    for (p = 0; p < Main_procCount; p++) {
        for (j = 1; j <= NUM_LOOPS_DFLT; j++) {

            /* receive message, timeout 2 sec */
            status = MessageQ_get(hostQ, &msg, 2000);

            if (status == MessageQ_E_TIMEOUT) {
                printf("Error: detected dropped message\n");
                status = -1;
                goto cleanup;
            }
            else if (status < 0) {
                printf("Error: MessageQ_get() failed, status=%d\n", status);
                status = -1;
                goto cleanup;
            }
        }

        procId = Main_procAry[p];
        printf("ProcId %d, received %d messages\n", procId, NUM_LOOPS_DFLT);
    }

   /* getting here implies success */
   printf("All messages received\n");

cleanup:
    /* close remote message queues */
    for (p = 0; p < Main_procCount; p++) {
        MessageQ_close(&Main_msgQueAry[p]);
    }

    /* delete local message queue */
    MessageQ_delete(&hostQ);

leave:
    printf("Leaving Main_main(), status=%d\n", status);

    return(status);
}
