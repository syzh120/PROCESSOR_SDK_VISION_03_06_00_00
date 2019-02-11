/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *  ======== OmxSrvMgr.c ========
 *
 *  The primary task function that serves the incoming requests on the OMX
 *  Service.
 */

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/ipc/MultiProc.h>

#include <ti/ipc/rpmsg/RPMessage.h>
#include <ti/ipc/rpmsg/NameMap.h>
#include <ti/srvmgr/rpmsg_omx.h>
#include <ti/srvmgr/ServiceMgr.h>

#include "package/internal/OmxSrvMgr.xdc.h"

/* Hard coded to match rpmsg-omx Host side driver */
#define  OMX_MGR_PORT   60

Void OmxSrvMgr_taskFxn(UArg arg0, UArg arg1)
{
    RPMessage_Handle msgq;
    UInt32 local;
    UInt32 remote;
    Char msg[HDRSIZE + sizeof(struct omx_connect_req)];
    struct omx_msg_hdr * hdr = (struct omx_msg_hdr *)msg;
    struct omx_connect_rsp * rsp = (struct omx_connect_rsp *)hdr->data;
    struct omx_connect_req * req = (struct omx_connect_req *)hdr->data;
    struct omx_disc_req * disc_req = (struct omx_disc_req *)hdr->data;
    struct omx_disc_rsp * disc_rsp = (struct omx_disc_rsp *)hdr->data;
    UInt16 dstProc;
    UInt16 len;
    UInt32 newAddr = 0;

#ifdef BIOS_ONLY_TEST
    dstProc = MultiProc_self();
#else
    dstProc = MultiProc_getId("HOST");
#endif

    msgq = RPMessage_create(OMX_MGR_PORT, NULL, NULL, &local);

    System_printf("OmxSrvMgr: started on port: %d\n", OMX_MGR_PORT);

#ifdef SMP
    if (MultiProc_self() == MultiProc_getId("IPU1")) {
        NameMap_register("rpmsg-omx", "rpmsg-omx3", OMX_MGR_PORT);
    }
    else {
        NameMap_register("rpmsg-omx", "rpmsg-omx1", OMX_MGR_PORT);
    }
    System_printf("OmxSrvMgr: Proc#%d sending BOOTINIT_DONE\n",
                        MultiProc_self());
#else
    if (MultiProc_self() == MultiProc_getId("CORE0")) {
        NameMap_register("rpmsg-omx", "rpmsg-omx0", OMX_MGR_PORT);
    }
    if (MultiProc_self() == MultiProc_getId("CORE1")) {
        NameMap_register("rpmsg-omx", "rpmsg-omx1", OMX_MGR_PORT);
    }
    if (MultiProc_self() == MultiProc_getId("DSP") ||
        MultiProc_self() == MultiProc_getId("DSP1")) {
        NameMap_register("rpmsg-omx", "rpmsg-omx2", OMX_MGR_PORT);
    }
    if (MultiProc_self() == MultiProc_getId("DSP2")) {
        NameMap_register("rpmsg-omx", "rpmsg-omx4", OMX_MGR_PORT);
    }
#endif

    while (1) {
       RPMessage_recv(msgq, (Ptr)msg, &len, &remote, RPMessage_FOREVER);
       System_printf("OmxSrvMgr: received msg type: %d from addr: %d\n",
                      hdr->type, remote);
       switch (hdr->type) {
           case OMX_CONN_REQ:
            /* This is a request to create a new service, and return
             * it's connection endpoint.
             */
            System_printf("OmxSrvMgr: CONN_REQ: len: %d, name: %s\n",
                 hdr->len, req->name);

            rsp->status = ServiceMgr_createService(req->name, &newAddr);

            hdr->type = OMX_CONN_RSP;
            rsp->addr = newAddr;
            hdr->len = sizeof(struct omx_connect_rsp);
            len = HDRSIZE + hdr->len;
            break;

           case OMX_DISC_REQ:
            /* Destroy the service instance at given service addr: */
            System_printf("OmxSrvMgr: OMX_DISCONNECT: len %d, addr: %d\n",
                 hdr->len, disc_req->addr);

            disc_rsp->status = ServiceMgr_deleteService(disc_req->addr);

            /* currently, no response expected from rpmsg_omx: */
            continue;
#if 0       /* rpmsg_omx is not listening for this ... yet. */
            hdr->type = OMX_DISC_RSP;
            hdr->len = sizeof(struct omx_disc_rsp);
            len = HDRSIZE + hdr->len;
            break;
#endif

           default:
            System_printf("unexpected msg type: %d\n", hdr->type);
            hdr->type = OMX_NOTSUPP;
            break;
       }

       System_printf("OmxSrvMgr: Replying with msg type: %d to addr: %d "
                      " from: %d\n",
                      hdr->type, remote, local);
       RPMessage_send(dstProc, remote, local, msg, len);
    }
}

Int OmxSrvMgr_Module_startup(Int phase)
{
    Task_Params params;

    if (Task_Module_startupDone()) {
        ServiceMgr_init();

        /* Create our ServiceMgr Thread: */
        Task_Params_init(&params);
        params.instance->name = "OmxSrvMgr";
        params.priority = 1;   /* Lowest priority thread */

        ServiceMgr_registerSrvTask(0, OmxSrvMgr_taskFxn, &params);

        return (Startup_DONE);
    }
    else {
        return (Startup_NOTDONE);
    }
}
