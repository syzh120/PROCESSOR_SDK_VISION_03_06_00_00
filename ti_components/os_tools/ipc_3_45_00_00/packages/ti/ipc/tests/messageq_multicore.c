/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 *  ======== message_multicore.c ========
 *  Multiprocessor MessageQ example
 *
 *  This is an example program that uses MessageQ to pass a message
 *  from one processor to another.
 *
 *  Each processor creates its own MessageQ first and then will try to open
 *  a remote processor's MessageQ.
 *
 *  See message_multicore.k file for expected output.
 */

#include <xdc/std.h>
#include <string.h>

/*  -----------------------------------XDC.RUNTIME module Headers    */
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>

/*  ----------------------------------- IPC module Headers           */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/HeapBufMP.h>
#include <ti/ipc/MultiProc.h>

/*  ----------------------------------- BIOS6 module Headers         */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/family/c66/Cache.h>

/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>

#define HEAP_NAME   "myHeapBuf"
#define HEAPID      0
#define NUMLOOPS    10

Char localQueueName[10];
Char nextQueueName[10];
UInt16 nextProcId;

/*
 *  ======== tsk0_func ========
 *  Allocates a message and ping-pongs the message around the processors.
 *  A local message queue is created and a remote message queue is opened.
 *  Messages are sent to the remote message queue and retrieved from the
 *  local MessageQ.
 */
Void tsk0_func(UArg arg0, UArg arg1)
{
    MessageQ_Msg     msg;
    MessageQ_Handle  messageQ;
    MessageQ_QueueId remoteQueueId;
    Int              status;
    UInt16           msgId = 0;
    HeapBufMP_Handle              heapHandle;
    HeapBufMP_Params              heapBufParams;

    if (MultiProc_self() == 0) {
        /*
         *  Create the heap that will be used to allocate messages.
         */
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

    if (MultiProc_self() == 0) {
        /* Allocate a message to be ping-ponged around the processors */
        msg = MessageQ_alloc(HEAPID, sizeof(MessageQ_MsgHeader));
        if (msg == NULL) {
           System_abort("MessageQ_alloc failed\n" );
        }

        /*
         *  Send the message to the next processor and wait for a message
         *  from the previous processor.
         */
        System_printf("Start the main loop\n");
        while (msgId < NUMLOOPS) {
            /* Increment...the remote side will check this */
            msgId++;
            MessageQ_setMsgId(msg, msgId);

            System_printf("Sending a message #%d to %s\n", msgId, nextQueueName);

            /* send the message to the remote processor */
            status = MessageQ_put(remoteQueueId, msg);
            if (status < 0) {
               System_abort("MessageQ_put had a failure/error\n");
            }

            /* Get a message */
            status = MessageQ_get(messageQ, &msg, MessageQ_FOREVER);
            if (status < 0) {
               System_abort("This should not happen since timeout is forever\n");
            }
        }
    }
    else {
        /*
         *  Wait for a message from the previous processor and
         *  send it to the next processor
         */
        System_printf("Start the main loop\n");
        while (TRUE) {
            /* Get a message */
            status = MessageQ_get(messageQ, &msg, MessageQ_FOREVER);
            if (status < 0) {
               System_abort("This should not happen since timeout is forever\n");
            }

            System_printf("Sending a message #%d to %s\n", MessageQ_getMsgId(msg),
                nextQueueName);

            /* Get the message id */
            msgId = MessageQ_getMsgId(msg);

            /* send the message to the remote processor */
            status = MessageQ_put(remoteQueueId, msg);
            if (status < 0) {
               System_abort("MessageQ_put had a failure/error\n");
            }

            /* test done */
            if (msgId >= NUMLOOPS) {
                break;
            }
        }
    }

    System_printf("The test is complete\n");
    BIOS_exit(0);
}

#define CACHE_WB_TICK_PERIOD    5

/*
 * ======== VirtQueue_cacheWb ========
 *
 * Used for flushing SysMin trace buffer.
 */
Void traceBuf_cacheWb()
{
    static UInt32 oldticks = 0;
    UInt32 newticks;

    newticks = Clock_getTicks();
    if (newticks - oldticks < (UInt32)CACHE_WB_TICK_PERIOD) {
        /* Don't keep flushing cache */
        return;
    }

    oldticks = newticks;

    Cache_wbAll();

}

/*
 *  ======== main ========
 *  Synchronizes all processors (in Ipc_start) and calls BIOS_start
 */
Int main(Int argc, Char* argv[])
{
    Int status;

    nextProcId = (MultiProc_self() + 1) % MultiProc_getNumProcessors();

    /* Generate queue names based on own proc ID and total number of procs */
    System_sprintf(localQueueName, "%s", MultiProc_getName(MultiProc_self()));
    System_sprintf(nextQueueName, "%s",  MultiProc_getName(nextProcId));

    /*
     *  Ipc_start() calls Ipc_attach() to synchronize all remote processors
     *  because 'Ipc.procSync' is set to 'Ipc.ProcSync_ALL' in *.cfg
     */
    status = Ipc_start();
    if (status < 0) {
        System_abort("Ipc_start failed\n");
    }

    BIOS_start();

    return (0);
}
