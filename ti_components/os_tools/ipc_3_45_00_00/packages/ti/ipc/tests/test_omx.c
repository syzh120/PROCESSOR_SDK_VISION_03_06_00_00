/*
 * Copyright (c) 2011-2015, Texas Instruments Incorporated
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
 *  ======== test_omx.c ========
 *
 *  Example of setting up an "OMX" service with the ServiceMgr, allowing clients
 *  to instantiate OMX instances.
 *
 *  Works with the test_omx.c Linux user space application over the rpmsg_omx\
 *  driver.
 */

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Diags.h>

#include <ti/ipc/MultiProc.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/grcm/RcmTypes.h>
#include <ti/grcm/RcmServer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ti/srvmgr/ServiceMgr.h>
#include <ti/srvmgr/rpmsg_omx.h>
#include <ti/srvmgr/omx_packet.h>

/* Turn on/off printf's */
#define CHATTER 0

/* Legacy function to allow Linux side rpmsg sample tests to work: */
extern void start_ping_tasks();
extern void start_resmgr_task();
extern void start_hwSpinlock_task();

/*
 * OMX packet expected to have its data payload start with a payload of
 * this value. Need to export this properly in a meaningful header file on
 * both HLOS and RTOS sides
 */
typedef enum {
    RPC_OMX_MAP_INFO_NONE       = 0,
    RPC_OMX_MAP_INFO_ONE_BUF    = 1,
    RPC_OMX_MAP_INFO_TWO_BUF    = 2,
    RPC_OMX_MAP_INFO_THREE_BUF  = 3,
    RPC_OMX_MAP_INFO_MAX        = 0x7FFFFFFF
} map_info_type;

/*
 *  ======== fxnDouble used by omx_benchmark test app ========
 */
typedef struct {
    Int a;
} FxnDoubleArgs;

static Int32 fxnDouble(UInt32 size, UInt32 *data);

/* ==========================================================================
 * OMX Fxns, adapted from rpc_omx_skel.c.
 *
 * These defines are to illustrate reuse of RPC_SKEL fxns with ServiceMgr.
 *===========================================================================*/

#define H264_DECODER_NAME   "H264_decoder"

#define OMX_VIDEO_THREAD_PRIORITY    5

typedef Int32  RPC_OMX_ERRORTYPE;
typedef UInt32 OMX_HANDLETYPE;

static RPC_OMX_ERRORTYPE RPC_SKEL_GetHandle(Void *, UInt32 size, UInt32 *data);
static RPC_OMX_ERRORTYPE RPC_SKEL_SetParameter(UInt32 size, UInt32 *data);
static RPC_OMX_ERRORTYPE RPC_SKEL_GetParameter(UInt32 size, UInt32 *data);



/* RcmServer static function table */
static RcmServer_FxnDesc OMXServerFxnAry[] = {
    {"RPC_SKEL_GetHandle"   , NULL}, /* Set at runtime to RPC_SKEL_GetHandle */
    {"RPC_SKEL_SetParameter", RPC_SKEL_SetParameter},
    {"RPC_SKEL_GetParameter", RPC_SKEL_GetParameter},
    {"fxnDouble", fxnDouble },
};

#define OMXServerFxnAryLen (sizeof OMXServerFxnAry / sizeof OMXServerFxnAry[0])

static const RcmServer_FxnDescAry OMXServer_fxnTab = {
    OMXServerFxnAryLen,
    OMXServerFxnAry
};


static RPC_OMX_ERRORTYPE RPC_SKEL_SetParameter(UInt32 size, UInt32 *data)
{
#if CHATTER
    System_printf("RPC_SKEL_SetParameter: Called\n");
#endif

    return(0);
}

static RPC_OMX_ERRORTYPE RPC_SKEL_GetParameter(UInt32 size, UInt32 *data)
{
#if CHATTER
    System_printf("RPC_SKEL_GetParameter: Called\n");
#endif

    return(0);
}

#define CALLBACK_DATA      "OMX_Callback"
#define PAYLOAD_SIZE       sizeof(CALLBACK_DATA)
#define CALLBACK_DATA_SIZE (HDRSIZE + OMXPACKETSIZE + PAYLOAD_SIZE)

static RPC_OMX_ERRORTYPE RPC_SKEL_GetHandle(Void *srvc, UInt32 size,
                                           UInt32 *data)
{
    char              cComponentName[128] = {0};
    OMX_HANDLETYPE    hComp;
    Char              cb_data[HDRSIZE + OMXPACKETSIZE + PAYLOAD_SIZE] =  {0};

    /*
     * Note: Currently, rpmsg_omx linux driver expects an omx_msg_hdr in front
     * of the omx_packet data, so we allow space for this:
     */
    struct omx_msg_hdr * hdr = (struct omx_msg_hdr *)cb_data;
    struct omx_packet  * packet = (struct omx_packet *)hdr->data;


    /*
     * Marshalled:[>offset(cParameterName)|>pAppData|>offset(RcmServerName)|>pid|
     * >--cComponentName--|>--CallingCorercmServerName--|
     * <hComp]
     */

    strcpy(cComponentName, (char *)data + sizeof(map_info_type));

#if CHATTER
    System_printf("RPC_SKEL_GetHandle: Component Name received: %s\n",
                  cComponentName);
#endif

    /* Simulate sending an async OMX callback message, passing an omx_packet
     * structure.
     */
    packet->msg_id  = 99;   /* Indicates callback instance, buffer id, etc. */
    packet->fxn_idx = 5;    /* Indicate callback fxn */
    packet->data_size = PAYLOAD_SIZE;
    strcpy((char *)packet->data, CALLBACK_DATA);

#if CHATTER
    System_printf("RPC_SKEL_GetHandle: Sending callback message id: %d, "
                  "fxn_id: %d, data: %s\n",
                  packet->msg_id, packet->fxn_idx, packet->data);
#endif
    ServiceMgr_send(srvc, cb_data, CALLBACK_DATA_SIZE);

    /* Call OMX_Get_Handle() and return handle for future calls. */
    /*eCompReturn = OMX_GetHandle(&hComp, (OMX_STRING)&cComponentName[0], pAppData,&rpcCallBackInfo); */
    hComp = 0x5C0FFEE5;
    data[0] = hComp;

#if CHATTER
    System_printf("RPC_SKEL_GetHandle: returning hComp: 0x%x\n", hComp);
#endif

    return(0);
}

/*
 *  ======== fxnDouble ========
 */
Int32 fxnDouble(UInt32 size, UInt32 *data)
{
    FxnDoubleArgs *args;
    Int a;

#if CHATTER
    System_printf("fxnDouble: Executing fxnDouble \n");
#endif

    args = (FxnDoubleArgs *)((UInt32)data + sizeof(map_info_type));
    a = args->a;

    return a * 2;
}

Int main(Int argc, char* argv[])
{
    RcmServer_Params  rcmServerParams;

    System_printf("%s starting..\n", MultiProc_getName(MultiProc_self()));

    /*
     * Enable use of runtime Diags_setMask per module:
     *
     * Codes: E = ENTRY, X = EXIT, L = LIFECYCLE, F = INFO, S = STATUS
     */
    Diags_setMask("ti.ipc.rpmsg.RPMessage=EXLFS");

    /* Setup the table of services, so clients can create and connect to
     * new service instances:
     */
    ServiceMgr_init();

    /* initialize RcmServer create params */
    RcmServer_Params_init(&rcmServerParams);

    /* The first function, at index 0, is a special create function, which
     * gets passed a Service_Handle argument.
     * We set this at run time as our C compiler is not allowing named union
     * field initialization:
     */
    OMXServer_fxnTab.elem[0].addr.createFxn = RPC_SKEL_GetHandle;

    rcmServerParams.priority    = Thread_Priority_ABOVE_NORMAL;
    rcmServerParams.stackSize   = 0x1000;
    rcmServerParams.fxns.length = OMXServer_fxnTab.length;
    rcmServerParams.fxns.elem   = OMXServer_fxnTab.elem;

    /* Register an OMX service to create and call new OMX components: */
    ServiceMgr_register("OMX", &rcmServerParams);

    /* Some background ping testing tasks, used by rpmsg samples: */
    start_ping_tasks();

#if 0 /* DSP or CORE0 or IPU */
    /* Run a background task to test rpmsg_resmgr service */
    start_resmgr_task();
#endif

#if 0  /* DSP or CORE0 or IPU */
    /* Run a background task to test hwspinlock */
    start_hwSpinlock_task();
#endif

    /* Start the ServiceMgr services */
    ServiceMgr_start(0);

    BIOS_start();

    return (0);
}
