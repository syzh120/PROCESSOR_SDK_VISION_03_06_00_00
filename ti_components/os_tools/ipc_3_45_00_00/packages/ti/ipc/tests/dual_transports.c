/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 * */
/*
 *  ======== dual_transports.c ========
 *  Multiprocessor MessageQ example, demonstrating TransportRpmsg and
 *  TransportShm coexistence.
 *
 *  Task1 uses MessageQ to pass a message in a ring between DSP CORES.
 *
 *  Task2 responds the the Host MessageQApp or MessageQBench.
 *
 *  A semaphore synchronizes Task1 to wait until Task2 starts it, which
 *  is initiated by a sync message from the host.
 */

#include <xdc/std.h>
#include <string.h>

/*  -----------------------------------XDC.RUNTIME module Headers    */
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Assert.h>

/*  ----------------------------------- IPC module Headers           */
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/HeapBufMP.h>
#include <ti/ipc/MultiProc.h>

/*  ----------------------------------- BIOS6 module Headers         */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/family/c66/Cache.h>

/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>

/* Used by multicoreMsgqFxn: */
#define HEAP_NAME   "myHeapBuf"
#define HEAPID      1
#define NUMLOOPS    10

/* Used by hostMsgqFxn: */
#define SLAVE_MESSAGEQNAME "SLAVE"
#define MessageQ_payload(m) ((void *)((char *)(m) + sizeof(MessageQ_MsgHeader)))

extern volatile cregister UInt DNUM;

typedef struct SyncMsg {
    MessageQ_MsgHeader header;
    UInt32 numLoops;  /* also used for msgId */
    UInt32 print;
} SyncMsg;


/*
 *  ======== hostMsgqFxn ========
 *  Receive and return messages to HOST.
 *
 *  When sync received from host, signal multicoreMesgqFxn to proceed.
 */
Void hostMsgqFxn(UArg arg0, UArg arg1)
{
    MessageQ_Msg msg;
    MessageQ_Handle  messageQ;
    MessageQ_QueueId remoteQueueId;
    Char             localQueueName[64];
    UInt16 procId;
    Int status;
    UInt16 msgId;
    UInt32 start;
    UInt32 end;
    UInt32 numLoops;
    UInt32 print;
    UInt32 msgNum;

    /* Construct a MessageQ name adorned with core name: */
    System_sprintf(localQueueName, "%s_%s", SLAVE_MESSAGEQNAME,
                   MultiProc_getName(MultiProc_self()));

    messageQ = MessageQ_create(localQueueName, NULL);
    if (messageQ == NULL) {
        System_abort("MessageQ_create failed\n" );
    }

    System_printf("hostMsgqFxn: created MessageQ: %s; QueueID: 0x%x\n",
        localQueueName, MessageQ_getQueueId(messageQ));

    while (1) {
        /* handshake with host to get starting parameters */
        System_printf("Awaiting sync message from host...\n");
        MessageQ_get(messageQ, &msg, MessageQ_FOREVER);

        numLoops = ((SyncMsg *)msg)->numLoops;
        print = ((SyncMsg *)msg)->print;

        remoteQueueId = MessageQ_getReplyQueue(msg);
        procId = MessageQ_getProcId(remoteQueueId);

        System_printf("Received msg from (procId:remoteQueueId): 0x%x:0x%x\n"
            "\tpayload: %d bytes; loops: %d %s printing.\n",
            procId, remoteQueueId,
            (MessageQ_getMsgSize(msg) - sizeof(MessageQ_MsgHeader)),
            numLoops, print ? "with" : "without");

        MessageQ_put(remoteQueueId, msg);

        /* ==> If CORE0, Kick multicoreMsgqFxn to start running */
        if (DNUM == 0) {
            Semaphore_post(semStartMultiCoreTest);
        }

        start = Clock_getTicks();
        for (msgId = 1; msgId <= numLoops; msgId++) {
            status = MessageQ_get(messageQ, &msg, MessageQ_FOREVER);
            Assert_isTrue(status == MessageQ_S_SUCCESS, NULL);

            msgNum = ((SyncMsg *)msg)->numLoops;

            if (print) {
                System_printf("Got msg #%d (%d bytes) from procId %d\n",
                    msgNum, MessageQ_getMsgSize(msg), procId);
            }

            Assert_isTrue(msgNum == msgId, NULL);

            if (print) {
                System_printf("Sending msg Id #%d to procId %d\n", msgId,
                              procId);
            }

            status = MessageQ_put(remoteQueueId, msg);
            Assert_isTrue(status == MessageQ_S_SUCCESS, NULL);
        }
        end = Clock_getTicks();

        if (!print) {
            System_printf("%d iterations took %d ticks or %d usecs/msg\n",
                          numLoops,
            end - start, ((end - start) * Clock_tickPeriod) / numLoops);
        }
    }
}

/*
 *  ======== multicoreFxn ========
 *  Allocates a message and ping-pongs the message around the processors.
 *  A local message queue is created and a remote message queue is opened.
 *  Messages are sent to the remote message queue and retrieved from the
 *  local MessageQ.
 */
Void multicoreFxn(UArg arg0, UArg arg1)
{
    MessageQ_Msg     msg;
    MessageQ_Handle  messageQ;
    MessageQ_QueueId remoteQueueId;
    Int              status;
    UInt16           msgId = 0;
    HeapBufMP_Handle              heapHandle;
    HeapBufMP_Params              heapBufParams;
    Char localQueueName[10];
    Char nextQueueName[10];
    UInt16 nextProcId;

    System_printf("multicoreFxn: Entered...\n");

    nextProcId = (MultiProc_self() + 1) % MultiProc_getNumProcessors();
    if (nextProcId == MultiProc_getId("HOST")) {
        nextProcId = 1;  /* Skip the host: Assumes host id is 0. */
    }

    /* Generate queue names based on own proc ID and total number of procs */
    System_sprintf(localQueueName, "%s", MultiProc_getName(MultiProc_self()));
    System_sprintf(nextQueueName, "%s",  MultiProc_getName(nextProcId));

    if (MultiProc_self() == MultiProc_getId("CORE0")) {
        /*
         *  Create the heap that will be used to allocate messages.
         */
        System_printf("multicoreFxn: Creating HeapBufMP...\n");
        HeapBufMP_Params_init(&heapBufParams);
        heapBufParams.regionId       = 0;
        heapBufParams.name           = HEAP_NAME;
        heapBufParams.numBlocks      = 1;
        heapBufParams.blockSize      = sizeof(MessageQ_MsgHeader);
        heapHandle = HeapBufMP_create(&heapBufParams);
        if (heapHandle == NULL) {
            System_abort("HeapBufMP_create failed\n" );
        }
    }
    else {
        System_printf("multicoreFxn: Opening HeapBufMP...\n");
        /* Open the heap created by the other processor. Loop until opened. */
        do {
            status = HeapBufMP_open(HEAP_NAME, &heapHandle);
            /*
             *  Sleep for 1 clock tick to avoid inundating remote processor
             *  with interrupts if open failed
             */
            if (status < 0) {
                Task_sleep(1);
            }
        } while (status < 0);
    }

    /* Register this heap with MessageQ */
    MessageQ_registerHeap((IHeap_Handle)heapHandle, HEAPID);

    /* Create the local message queue */
    messageQ = MessageQ_create(localQueueName, NULL);
    if (messageQ == NULL) {
        System_abort("MessageQ_create failed\n" );
    }

    /* Open the remote message queue. Spin until it is ready. */
    System_printf("multicoreFxn: Opening Remote Queue: %s...\n", nextQueueName);
    do {
        status = MessageQ_open(nextQueueName, &remoteQueueId);
        /*
         *  Sleep for 1 clock tick to avoid inundating remote processor
         *  with interrupts if open failed
         */
        if (status < 0) {
            Task_sleep(1);
        }
    } while (status < 0);

    if (MultiProc_self() == MultiProc_getId("CORE0")) {
        /* Allocate a message to be ping-ponged around the processors */
        msg = MessageQ_alloc(HEAPID, sizeof(MessageQ_MsgHeader));
        if (msg == NULL) {
           System_abort("MessageQ_alloc failed\n" );
        }

        while (1) {

        /* ==> If CORE0, wait for signal from hostMsgqFxn to start loop: */
        if (DNUM == 0) {
            Semaphore_pend(semStartMultiCoreTest, BIOS_WAIT_FOREVER);
        }

        /*
         *  Send the message to the next processor and wait for a message
         *  from the previous processor.
         */
        System_printf("multicoreFxn: Sender: Start the main loop\n");
        for (msgId = 0; msgId < NUMLOOPS; msgId++) {
            /* Increment...the remote side will check this */
            MessageQ_setMsgId(msg, msgId);

            System_printf("Sending message #%d to %s\n", msgId, nextQueueName);

            /* send the message to the next processor */
            status = MessageQ_put(remoteQueueId, msg);
            if (status < 0) {
               System_abort("MessageQ_put had a failure/error\n");
            }

            /* Get a message */
            status = MessageQ_get(messageQ, &msg, MessageQ_FOREVER);
            if (status < 0) {
               System_abort("This should not happen as timeout is forever\n");
            }
        }
        }
    }
    else {

        /*
         *  Wait for a message from the previous processor and
         *  send it to the next processor
         */
        System_printf("multicoreFxn: Receiver: Start the main loop\n");
        while (TRUE) {
            /* Get a message */
            status = MessageQ_get(messageQ, &msg, MessageQ_FOREVER);
            if (status < 0) {
               System_abort("This should not happen since timeout is forever\n");
            }

            /* Get the message id */
            msgId = MessageQ_getMsgId(msg);

            System_printf("Sending a message #%d to %s\n", msgId,
                nextQueueName);

            /* send the message to the remote processor */
            status = MessageQ_put(remoteQueueId, msg);
            if (status < 0) {
               System_abort("MessageQ_put had a failure/error\n");
            }

            /* test done */
            if (msgId >= NUMLOOPS) {
                System_printf("multicore loop test is complete\n");
            }
        }
    }
}

/*
 *  ======== main ========
 *  Creates thread and calls BIOS_start
 */
Int main(Int argc, Char* argv[])
{
    /* Put CCS breakpoint for CORE0 */
#if 0
    if (DNUM == 0) {
       /* Wait until we connect CCS; write 1 to var spin to continue: */
       volatile int spin = 1;
       while(spin);
    }
#endif

    System_printf("main: MultiProc id: %d\n", MultiProc_self());

    Task_create(multicoreFxn, NULL, NULL);
    Task_create(hostMsgqFxn, NULL, NULL);

    BIOS_start();

    return (0);
}
