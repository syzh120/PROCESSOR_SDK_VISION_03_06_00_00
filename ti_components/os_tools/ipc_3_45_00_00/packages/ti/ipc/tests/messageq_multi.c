/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *  ======== messageq_multi.c ========
 *
 *  Test for messageq operating in multiple simultaneous threads.
 *
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/heaps/HeapBuf.h>

#include <ti/ipc/MessageQ.h>
#include <ti/ipc/MultiProc.h>

#define SLAVE_MESSAGEQNAME "SLAVE"
#define HOST_MESSAGEQNAME "HOST"
#define NUMTHREADS 25
#define NUMLOOPS 1000

static int numTests = 0;

/*
 *  ======== loopbackFxn========
 *  Receive and return messages.
 *  Run at priority lower than tsk1Fxn above.
 *  Inputs:
 *     - arg0: number of the thread, appended to MessageQ host and slave names.
 */
Void loopbackFxn(UArg arg0, UArg arg1)
{
    MessageQ_Msg     getMsg;
    MessageQ_Handle  messageQ;
    MessageQ_QueueId remoteQueueId;
    Int              status;
    UInt16           msgId = 0;
    Char             localQueueName[64];
    Char             hostQueueName[64];

    System_printf("Thread loopbackFxn: %d\n", arg0);

    System_sprintf(localQueueName, "%s_%d", SLAVE_MESSAGEQNAME, arg0);
    System_sprintf(hostQueueName,  "%s_%d", HOST_MESSAGEQNAME,  arg0);

    /* Create a message queue. */
    messageQ = MessageQ_create(localQueueName, NULL);
    if (messageQ == NULL) {
        System_abort("MessageQ_create failed\n");
    }

    System_printf("loopbackFxn: created MessageQ: %s; QueueID: 0x%x\n",
        localQueueName, MessageQ_getQueueId(messageQ));

    System_printf("Start the main loop: %d\n", arg0);
    while (msgId < NUMLOOPS) {
        /* Get a message */
        status = MessageQ_get(messageQ, &getMsg, MessageQ_FOREVER);
        if (status != MessageQ_S_SUCCESS) {
           System_abort("This should not happen since timeout is forever\n");
        }
        remoteQueueId = MessageQ_getReplyQueue(getMsg);

#ifndef BENCHMARK
        System_printf("%d: Received message #%d from core %d\n",
                arg0, MessageQ_getMsgId(getMsg),
                MessageQ_getProcId(remoteQueueId));
#endif
        /* test id of message received */
        if (MessageQ_getMsgId(getMsg) != msgId) {
            System_abort("The id received is incorrect!\n");
        }

#ifndef BENCHMARK
        /* Send it back */
        System_printf("%d: Sending message Id #%d to core %d\n",
                      arg0, msgId, MessageQ_getProcId(remoteQueueId));
#endif
        status = MessageQ_put(remoteQueueId, getMsg);
        if (status != MessageQ_S_SUCCESS) {
           System_abort("MessageQ_put had a failure/error\n");
        }
        msgId++;
    }

    MessageQ_delete(&messageQ);
    numTests += NUMLOOPS;

    System_printf("Test thread %d complete!\n", arg0);
}

/*
 *  ======== main ========
 */
Int main(Int argc, Char* argv[])
{
    Task_Params params;
    Int i;

    System_printf("%s:main: MultiProc id = %d\n", __FILE__, MultiProc_self());

    /* Create N threads to correspond with host side N thread test app: */
    Task_Params_init(&params);
    params.priority = 3;
    for (i = 0; i < NUMTHREADS; i++) {
        params.arg0 = i;
        Task_create(loopbackFxn, &params, NULL);
    }

    BIOS_start();

    return (0);
 }
