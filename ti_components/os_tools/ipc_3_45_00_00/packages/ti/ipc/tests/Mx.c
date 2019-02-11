/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 *  ======== Mx.c ========
 */
#include <stdio.h>
#include <ti/ipc/Std.h>

#include <ti/ipc/mm/MmRpc.h>
#include <ti/ipc/MultiProc.h>

#if defined(IPC_BUILDOS_QNX)
#include <ti/shmemallocator/SharedMemoryAllocatorUsr.h>
#endif

#include "Mx.h"

/* hande used for remote communication */
static MmRpc_Handle Mx_rpcIpu = NULL;

/* static function indicies */
#define Mx_Fxn_triple   (0x80000000 | 1)
#define Mx_Fxn_add      (0x80000000 | 2)
#define Mx_Fxn_compute  (0x80000000 | 5)

#define Mx_OFFSET(base, member) ((uint_t)(member) - (uint_t)(base))

#define SERVICE_NAME    "rpc_example"

/*
 *  ======== Mx_initialize ========
 */
int Mx_initialize(UInt16 procId)
{
    int status;
    MmRpc_Params args;
    Char mmServerName[20];

    /* create remote server instance */
    MmRpc_Params_init(&args);

    /* Construct an MmRpc server name adorned with core name: */
    sprintf(mmServerName, "%s_%d", SERVICE_NAME, procId);

    status = MmRpc_create(mmServerName, &args, &Mx_rpcIpu);

    if (status < 0) {
        printf("mmrpc_test: Error: MmRpc_create of %s failed\n", mmServerName);
        status = -1;
    }
    else {
        status = 0;
    }

    return(status);
}

/*
 *  ======== Mx_finalize ========
 */
void Mx_finalize(void)
{
    /* delete remote server instance */
    if (Mx_rpcIpu != NULL) {
        MmRpc_delete(&Mx_rpcIpu);
    }
}

/*
 *  ======== Mx_triple ========
 */
int32_t Mx_triple(uint32_t a)
{
    MmRpc_FxnCtx *fxnCtx;
    int32_t fxnRet;
    char send_buf[512] = {0};
    int status;

    /* marshall function arguments into the send buffer */
    fxnCtx = (MmRpc_FxnCtx *)send_buf;

    fxnCtx->fxn_id = Mx_Fxn_triple;
    fxnCtx->num_params = 1;
    fxnCtx->params[0].type = MmRpc_ParamType_Scalar;
    fxnCtx->params[0].param.scalar.size = sizeof(int);
    fxnCtx->params[0].param.scalar.data = a;
    fxnCtx->num_xlts = 0;
    fxnCtx->xltAry = NULL;

    /* invoke the remote function call */
    status = MmRpc_call(Mx_rpcIpu, fxnCtx, &fxnRet);

    if (status < 0) {
        printf("mmrpc_test: Error: MmRpc_call failed\n");
        fxnRet = -1;
    }

    return(fxnRet);
}

/*
 *  ======== Mx_add ========
 */
int32_t Mx_add(int32_t a, int32_t b)
{
    MmRpc_FxnCtx *fxnCtx;
    int32_t fxnRet;
    char send_buf[512] = {0};
    int status;

    /* marshall function arguments into the send buffer */
    fxnCtx = (MmRpc_FxnCtx *)send_buf;

    fxnCtx->fxn_id = Mx_Fxn_add;
    fxnCtx->num_params = 2;
    fxnCtx->params[0].type = MmRpc_ParamType_Scalar;
    fxnCtx->params[0].param.scalar.size = sizeof(int);
    fxnCtx->params[0].param.scalar.data = a;
    fxnCtx->params[1].type = MmRpc_ParamType_Scalar;
    fxnCtx->params[1].param.scalar.size = sizeof(int);
    fxnCtx->params[1].param.scalar.data = b;
    fxnCtx->num_xlts = 0;

    /* invoke the remote function call */
    status = MmRpc_call(Mx_rpcIpu, fxnCtx, &fxnRet);

    if (status < 0) {
        printf("mmrpc_test: Error: MmRpc_call failed\n");
        fxnRet = -1;
    }

    return(fxnRet);
}

/*
 *  ======== Mx_compute ========
 */
#if defined(IPC_BUILDOS_QNX)
int32_t Mx_compute_QnX(Mx_Compute *compute)
#else
int32_t Mx_compute_Linux(Mx_Compute *compute, int fd, int fdIn, int fdOut)
#endif
{
    MmRpc_FxnCtx *fxnCtx;
    MmRpc_Xlt xltAry[2];
    int32_t fxnRet;
    char send_buf[512] = {0};
    int status;
    MmRpc_BufDesc desc[1];
    int num = 0;

    /* make the output buffer persistent */
#if defined(IPC_BUILDOS_QNX)
    desc[0].ptr.addr = (size_t)compute->outBuf;
    desc[0].ptr.size = compute->size * sizeof(uint32_t);
    num = 1;

    status = MmRpc_use(Mx_rpcIpu, MmRpc_BufType_Ptr, num, desc);
#else
    desc[0].handle = fdOut;
    num = 1;

    status = MmRpc_use(Mx_rpcIpu, MmRpc_BufType_Handle, num, desc);
#endif

    if (status < 0) {
        printf("mmrpc_test: Error: MmRpc_use failed\n");
        num = 0;
        fxnRet = -1;
        goto leave;
    }

    /* marshall function arguments into the send buffer */
    fxnCtx = (MmRpc_FxnCtx *)send_buf;

    fxnCtx->fxn_id = Mx_Fxn_compute;
    fxnCtx->num_params = 1;
    fxnCtx->params[0].type = MmRpc_ParamType_Ptr;
    fxnCtx->params[0].param.ptr.size = sizeof(Mx_Compute);
    fxnCtx->params[0].param.ptr.addr = (size_t)compute;
#if defined(IPC_BUILDOS_QNX)
    fxnCtx->params[0].param.ptr.handle = NULL;
#else
    fxnCtx->params[0].param.ptr.handle = fd;
#endif

    fxnCtx->num_xlts = 2;
    fxnCtx->xltAry = xltAry;

    fxnCtx->xltAry[0].index = 0;
    fxnCtx->xltAry[0].offset = MmRpc_OFFSET(compute, &compute->inBuf);
    fxnCtx->xltAry[0].base = (size_t)compute->inBuf;
#if defined(IPC_BUILDOS_QNX)
    fxnCtx->xltAry[0].handle = NULL;
#else
    fxnCtx->xltAry[0].handle = fdIn;
#endif

    fxnCtx->xltAry[1].index = 0;
    fxnCtx->xltAry[1].offset = MmRpc_OFFSET(compute, &compute->outBuf);
    fxnCtx->xltAry[1].base = (size_t)compute->outBuf;
#if defined(IPC_BUILDOS_QNX)
    fxnCtx->xltAry[1].handle = NULL;
#else
    fxnCtx->xltAry[1].handle = fdOut;
#endif

    /* invoke the remote function call */
    status = MmRpc_call(Mx_rpcIpu, fxnCtx, &fxnRet);

    if (status < 0) {
        printf("mmrpc_test: Error: MmRpc_call failed\n");
        fxnRet = -1;
        goto leave;
    }

leave:
    /* release the output buffer */
    if (num > 0) {
#if defined(IPC_BUILDOS_QNX)
        status = MmRpc_release(Mx_rpcIpu, MmRpc_BufType_Ptr, num, desc);
#else
        status = MmRpc_release(Mx_rpcIpu, MmRpc_BufType_Handle, num, desc);
#endif

        if (status < 0) {
            printf("mmrpc_test: Error: MmRpc_release failed\n");
            fxnRet = -1;
        }
    }

    return(fxnRet);
}
