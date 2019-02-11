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
 *  ======== MmServiceMgr.c ========
 */

#include <string.h>

#include <xdc/std.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>

#include <ti/grcm/RcmServer.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/mm/MmType.h>
#include <ti/srvmgr/ServiceMgr.h>
#include <ti/srvmgr/omaprpc/OmapRpc.h>

#include "MmServiceMgr.h"

typedef struct {
    RcmServer_Params    rcmParams;
    Int                 aryLen;
    OmapRpc_FuncSignature *sigAry;
} MmServiceMgr_Client;

static Int MmServiceMgr_ref = 0;

/* temporary: needs to be removed */
extern Int32 OmapRpc_GetSvrMgrHandle(Void *srvc, Int32 num, Int32 *params);

/*
 *  ======== MmServiceMgr_init ========
 */
Int MmServiceMgr_init(Void)
{
    if (MmServiceMgr_ref++ != 0) {
        return(MmServiceMgr_S_SUCCESS); /* module already initialized */
    }

    RcmServer_init();
/*  ServiceMgr_init(); */

    return(MmServiceMgr_S_SUCCESS);
}

/*
 *  ======== MmServiceMgr_exit ========
 */
Void MmServiceMgr_exit(Void)
{
    if (--MmServiceMgr_ref != 0) {
        return; /* module still in use */
    }

    RcmServer_exit();
}

/*
 *  ======== MmServiceMgr_register ========
 */
Int MmServiceMgr_register(const String name, RcmServer_Params *rcmParams,
        MmType_FxnSigTab *fxnSigTab, MmServiceMgr_DelFxn delFxn)
{
    Int status = MmServiceMgr_S_SUCCESS;
    OmapRpc_Handle handle;

    handle = OmapRpc_createChannel(name, MultiProc_getId("HOST"),
            RPMessage_ASSIGN_ANY, rcmParams, fxnSigTab, delFxn);

    if (handle == NULL) {
        status = MmServiceMgr_E_FAIL;
    }

    return(status);
}

/*
 *  ======== MmServiceMgr_getId ========
 */
UInt32 MmServiceMgr_getId()
{
    /* The id has been stashed onto the task environment */
    return ((UInt32)Task_getEnv(Task_self()));
}
