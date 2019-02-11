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
 *  ======== gatempapp.c ========
 *
 */

/* this define must precede inclusion of any xdc header file */
#define Registry_CURDESC Test__Desc
#define MODULE_NAME "Server"

/* xdctools header files */
#include <xdc/std.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Registry.h>

/* package header files */
#include <ti/ipc/Ipc.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/GateMP.h>
#include <ti/ipc/remoteproc/Resource.h>

/* sytem header files */
#include <stdlib.h>

/* local header files */
#include "gatempapp_rsc_table_vayu_dsp.h"
#include "GateMPAppCommon.h"

/* module structure */
typedef struct {
    UInt16              hostProcId;         /* host processor id */
    MessageQ_Handle     slaveQue;           /* created locally */
    GateMP_Handle       hostGateMPHandle;   /* host created gate */
    GateMP_Handle       slaveGateMPHandle;  /* slave created gate */
} Server_Module;

/* private data */
Registry_Desc               Registry_CURDESC;
static Server_Module        Module;

/* private functions */
static Void smain(UArg arg0, UArg arg1);


/*
 *  ======== Server_init ========
 */
Void Server_init(Void)
{
    Registry_Result result;

    /* register with xdc.runtime to get a diags mask */
    result = Registry_addModule(&Registry_CURDESC, MODULE_NAME);
    Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

    /* initialize module object state */
    Module.hostProcId = MultiProc_getId("HOST");
    Module.slaveQue = NULL;
    Module.hostGateMPHandle = NULL;
    Module.slaveGateMPHandle = NULL;
}


/*
 *  ======== Server_create ========
 */
Int Server_create()
{
    Int                 status = 0;
    MessageQ_Params     msgqParams;
    GateMP_Params       gateParams;

    /* enable some log events */
    Diags_setMask(MODULE_NAME"+EXF");

    /* create GateMP */
    GateMP_Params_init(&gateParams);

    gateParams.name             = GATEMP_SLAVE_NAME;
    gateParams.localProtect     = GateMP_LocalProtect_PROCESS;
    gateParams.remoteProtect    = GateMP_RemoteProtect_SYSTEM;

    Module.slaveGateMPHandle = GateMP_create (&gateParams);

    if (Module.slaveGateMPHandle == NULL) {
        status = GATEMPAPP_E_FAILURE;
        Log_print0(Diags_INFO, "Server_create: Failed to create GateMP");
        goto leave;
    }

    /* create local message queue (inbound messages) */
    MessageQ_Params_init(&msgqParams);
    Module.slaveQue = MessageQ_create(GateMPApp_SlaveMsgQueName, &msgqParams);

    if (Module.slaveQue == NULL) {
        status = -1;
        Log_print0(Diags_INFO, "Server_create: Failed to create MessageQ");
        GateMP_delete(&Module.slaveGateMPHandle);
        goto leave;
    }

    Log_print0(Diags_INFO,"Server_create: Slave is ready");

leave:
    Log_print1(Diags_EXIT, "<-- Server_create: %d", (IArg)status);
    return (status);
}




/*
 *  ======== Server_exec ========
 */
Int Server_exec()
{
    Int                 status;
    GateMPApp_Msg *           msg;
    MessageQ_QueueId    queId;
    UInt32              physAddr;
    volatile UInt32 *   intPtr              = 0;
    Int                 num                 = 0;
    Int                 prevNum             = 0;
    UInt                i                   = 0;
    IArg                gateKey             = 0;

    Log_print0(Diags_ENTRY | Diags_INFO, "--> Server_exec:");

    /* wait for inbound message */
    status = MessageQ_get(Module.slaveQue, (MessageQ_Msg *)&msg,
        MessageQ_FOREVER);

    if (status < 0) {
        goto leave;
    }

    if (msg->cmd != GATEMPAPP_CMD_SPTR_ADDR) {
        status = GATEMPAPP_E_UNEXPECTEDMSG;
        goto leave;
    }

    /* Get physical address of shared memory */
    physAddr = msg->payload;

    /* translate the physical address to slave virtual addr */
    if (Resource_physToVirt(physAddr, (UInt32 *)&intPtr)) {
        Log_error1("Server_exec: Failed to translate phys addr %p to virt addr", physAddr);
        goto leave;
    }

    /* send message back */
    queId = MessageQ_getReplyQueue(msg); /* type-cast not needed */
    msg->cmd = GATEMPAPP_CMD_SPTR_ADDR_ACK;
    MessageQ_put(queId, (MessageQ_Msg)msg);

    Log_print0(Diags_INFO,"Server_exec: Modifying shared variable "
            "value");

    /* open host-created GateMP */
    do {
        status = GateMP_open(GATEMP_HOST_NAME, &Module.hostGateMPHandle);
    } while (status == GateMP_E_NOTFOUND);

    if (status < 0) {
        Log_error0("Server_exec: Failed to open host-created GateMP");
        status = GATEMPAPP_E_FAILURE;
        goto leave;
    }

    Log_print0(Diags_INFO,"Server_exec: Opened GateMP successfully");

    Log_print0(Diags_INFO,"Server_exec: Using host-created gate");
    for (i = 0;i < LOOP_ITR; i++) {

        /* modify the shared variable as long as no one else is currently
         * accessing it
         */

        /* enter GateMP */
        gateKey = GateMP_enter(Module.hostGateMPHandle);

        /* read shared variable value */
        prevNum = *intPtr;

        /* randomly modify the shared variable */
        if ( rand() % 2) {
            *intPtr -= 1;
        }
        else {
            *intPtr += 1;
        }

        /* read shared variable value again */
        num = *intPtr;

        if ((prevNum != num + 1) && (prevNum != num - 1)) {
            Log_print0(Diags_INFO, "Server_exec: unexpected variable value." \
                "Test failed.");
            Log_print2(Diags_INFO, "Server_exec: Previous shared variable "
                "value %d, current value=%d", prevNum, num);

            status = GATEMPAPP_E_FAILURE;
            goto leave;
        }

        /* leave Gate */
        GateMP_leave(Module.hostGateMPHandle, gateKey);
    }

    /* wait for sync message before we switch gates */
    status = MessageQ_get(Module.slaveQue, (MessageQ_Msg *)&msg,
        MessageQ_FOREVER);
    if (status < 0) {
        goto leave;
    }

    if (msg->cmd != GATEMPAPP_CMD_SYNC) {
        status = GATEMPAPP_E_UNEXPECTEDMSG;
        goto leave;
    }

    queId = MessageQ_getReplyQueue(msg);
    MessageQ_put(queId, (MessageQ_Msg)msg);

    Log_print0(Diags_INFO,"Server_exec: Using slave-created gate");

    for (i = 0;i < LOOP_ITR; i++) {

        /* modify the shared variable as long as no one else is currently
         * accessing it
         */

        /* enter GateMP */
        gateKey = GateMP_enter(Module.slaveGateMPHandle);

        /* read shared variable value */
        prevNum = *intPtr;

        /* randomly modify the shared variable */
        if ( rand() % 2) {
            *intPtr -= 1;
        }
        else {
            *intPtr += 1;
        }

        /* read shared variable value again */
        num = *intPtr;

        if ((prevNum != num - 1) && (prevNum != num + 1)) {
            Log_print0(Diags_INFO, "Server_exec: unexpected variable value." \
                "Test failed.");
            Log_print2(Diags_INFO, "Server_exec: Previous "
                "value=%d, current value=%d", prevNum, num);

            status = GATEMPAPP_E_FAILURE;
            goto leave;
        }

        /* leave Gate */
        GateMP_leave(Module.slaveGateMPHandle, gateKey);
    }

leave:
    /* close host GateMP */
    if (Module.hostGateMPHandle) {
        GateMP_close(&Module.hostGateMPHandle);
    }
    Log_print0(Diags_ENTRY, "Server_exec: host GateMP closed");

    Log_print1(Diags_EXIT, "<-- Server_exec: %d", (IArg)status);
    return(status);
}

/*
 *  ======== Server_delete ========
 */
Int Server_delete()
{
    Int         status;
    GateMPApp_Msg *           msg;
    MessageQ_QueueId    queId;

    Log_print0(Diags_ENTRY, "--> Server_delete:");

    /* wait for inbound message */
    status = MessageQ_get(Module.slaveQue, (MessageQ_Msg *)&msg,
        MessageQ_FOREVER);

    if (status < 0) {
        goto leave;
    }
    Log_print0(Diags_ENTRY, "--> Server_delete: got msg");
    if (msg->cmd != GATEMPAPP_CMD_SHUTDOWN) {
        status = GATEMPAPP_E_UNEXPECTEDMSG;
        goto leave;
    }

    /* send message back to say that GateMP has been cleaned up */
    queId = MessageQ_getReplyQueue(msg); /* type-cast not needed */
    msg->cmd = GATEMPAPP_CMD_SHUTDOWN_ACK;
    MessageQ_put(queId, (MessageQ_Msg)msg);

    /* delete the video message queue */
    status = MessageQ_delete(&Module.slaveQue);
    if (status < 0) {
        Log_print0(Diags_ENTRY, "Server_delete: MessageQ_delete failed");
        goto leave;
    }

    Log_print0(Diags_ENTRY, "Server_delete: MessageQ deleted");

    /* delete slave GateMP */
    status = GateMP_delete(&Module.slaveGateMPHandle);
    if (status < 0) {
        Log_print0(Diags_ENTRY, "Server_delete: GateMP_delete failed");
        goto leave;
    }

    Log_print0(Diags_ENTRY, "Server_delete: slave GateMP deleted");

leave:
    if (status < 0) {
        Log_error1("Server_delete: error=0x%x", (IArg)status);
    }

    /* disable log events */
    Log_print1(Diags_EXIT, "<-- Server_delete: %d", (IArg)status);
    Diags_setMask(MODULE_NAME"-EXF");

    return(status);
}

/*
 *  ======== Server_exit ========
 */

Void Server_exit(Void)
{
    /*
     * Note that there isn't a Registry_removeModule() yet:
     *     https://bugs.eclipse.org/bugs/show_bug.cgi?id=315448
     *
     * ... but this is where we'd call it.
     */
}


/*
 *  ======== main ========
 */
Int main(Int argc, Char* argv[])
{
    Error_Block     eb;
    Task_Params     taskParams;

    Log_print0(Diags_ENTRY, "--> main:");

    /* must initialize the error block before using it */
    Error_init(&eb);

    /* create main thread (interrupts not enabled in main on BIOS) */
    Task_Params_init(&taskParams);
    taskParams.instance->name = "smain";
    taskParams.stackSize = 0x1000;
    Task_create(smain, &taskParams, &eb);

    if (Error_check(&eb)) {
        System_abort("main: failed to create application startup thread");
    }

    /* start scheduler, this never returns */
    BIOS_start();

    /* should never get here */
    Log_print0(Diags_EXIT, "<-- main:");
    return (0);
}


/*
 *  ======== smain ========
 */
Void smain(UArg arg0, UArg arg1)
{
    Int                 status = 0;

    Log_print0(Diags_ENTRY | Diags_INFO, "--> smain:");

    /* initialize modules */
    Server_init();

    /* turn on Diags_INFO trace */
    Diags_setMask("Server+F");

    /* server setup phase */
    status = Server_create();

    if (status < 0) {
        goto leave;
    }

    /* server execute phase */
    status = Server_exec();

    if (status < 0) {
        goto leave;
    }

    /* server shutdown phase */
    status = Server_delete();

    if (status < 0) {
        goto leave;
    }

    /* finalize modules */
    Server_exit();

leave:
    Log_print1(Diags_EXIT, "<-- smain: %d", (IArg)status);
    return;
}
