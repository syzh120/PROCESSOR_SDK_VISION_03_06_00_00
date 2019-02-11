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
 *  ======== mmrpc_test.c ========
 */
#include <stdio.h>
#include <stdlib.h>

/* IPC Headers */
#include <ti/ipc/Std.h>

#if defined(IPC_BUILDOS_QNX)
#include <ti/ipc/Ipc.h>
#include <ti/shmemallocator/SharedMemoryAllocatorUsr.h>
#else  /* Linux HLOS */
#include <omap/omap_drm.h>
#include <libdrm/omap_drmif.h>
#include <errno.h>
#include <string.h>
#endif

#include "Mx.h"

#define PROC_ID_DFLT 1

/*
 * These callCompute() functions separated per HLOS due to very different
 * HLOS specific shared memory buffer allocation methods.
 */

#if defined(IPC_BUILDOS_QNX)

static int callCompute_QnX()
{
    Mx_Compute *compute;
    shm_buf shmCompute, shmInBuf, shmOutBuf;
    int status = 0;
    int size;
    int32_t ret;
    uint32_t val;
    int i;

    /* allocate a compute structure in shared memory */
    SHM_alloc(sizeof(Mx_Compute), &shmCompute);
    compute = (Mx_Compute *)(shmCompute.vir_addr);

    if (compute == NULL) {
        /* temporary: memory alloc not implemented on Linux */
        fprintf(stderr, "failed to map omap_bo to user space\n");
        goto leave;
    }

    /* initialize compute structure */
    compute->coef = 0x80400000;
    compute->key = 0xABA0;
    compute->size = 0x1000;
    compute->inBuf = NULL;
    compute->outBuf = NULL;

    /* allocate an input buffer in shared memory */
    size = compute->size * sizeof(uint32_t);
    SHM_alloc(size, &shmInBuf);
    compute->inBuf = (uint32_t *)(shmInBuf.vir_addr);

    if (compute->inBuf == NULL) {
        printf("mmrpc_test: Error: compute->inBuf == NULL\n");
        status = -1;
        goto leave;
    }

    /* fill input buffer with seed value */
    for (i = 0; i < compute->size; i++) {
        compute->inBuf[i] = 0x2010;
    }

    /* allocate an output buffer in shared memory */
    SHM_alloc(size, &shmOutBuf);
    compute->outBuf = (uint32_t *)(shmOutBuf.vir_addr);

    if (compute->outBuf == NULL) {
        printf("mmrpc_test: Error: compute->outBuf == NULL\n");
        status = -1;
        goto leave;
    }

    /* clear output buffer */
    for (i = 0; i < compute->size; i++) {
        compute->outBuf[i] = 0;
    }

    /* print some debug info */
    printf("mmrpc_test: calling Mx_compute(0x%x)\n", (unsigned int)compute);
    printf("mmrpc_test: compute->coef=0x%x\n", compute->coef);
    printf("mmrpc_test: compute->key=0x%x\n", compute->key);
    printf("mmrpc_test: compute->size=0x%x\n", compute->size);
    printf("mmrpc_test: compute->inBuf=0x%x\n", (unsigned int)compute->inBuf);
    printf("mmrpc_test: compute->outBuf=0x%x\n", (unsigned int)compute->outBuf);

    /* process the buffer */
    ret = Mx_compute_QnX(compute);

    if (ret < 0) {
        status = -1;
        printf("mmrpc_test: Error: Mx_Compute() failed\n");
        goto leave;
    }

    printf("mmrpc_test: after Mx_compute(0x%x)\n", (unsigned int)compute);
    printf("mmrpc_test: compute->coef=0x%x\n", compute->coef);
    printf("mmrpc_test: compute->key=0x%x\n", compute->key);
    printf("mmrpc_test: compute->size=0x%x\n", compute->size);
    printf("mmrpc_test: compute->inBuf=0x%x\n", (unsigned int)compute->inBuf);
    printf("mmrpc_test: compute->outBuf=0x%x\n", (unsigned int)compute->outBuf);
    printf("mmrpc_test: compute->inBuf[0]=0x%x\n",
            (unsigned int)compute->inBuf[0]);
    printf("mmrpc_test: compute->outBuf[0]=0x%x\n",
            (unsigned int)compute->outBuf[0]);

    /* check the output buffer */
    for (i = 0; i < compute->size; i++) {
        val = compute->outBuf[i] | compute->coef;
        if (compute->outBuf[i] != val) {
            status = -1;
            printf("mmrpc_test: Error: incorrect outBuf\n");
            break;
        }
    }

leave:
    SHM_release(&shmOutBuf);
    SHM_release(&shmInBuf);
    SHM_release(&shmCompute);

    return (status);
}

#else /* Linux */

static int callCompute_Linux()
{
    Mx_Compute *compute = NULL;
    int drmFd = 0;
    struct omap_device *dev = NULL;
    struct omap_bo *compute_bo = NULL;
    struct omap_bo *inBuf_bo = NULL;
    struct omap_bo *outBuf_bo = NULL;
    uint32_t * inBufPtr = NULL;
    uint32_t * outBufPtr = NULL;
    int status = 0;
    int size;
    uint32_t val;
    int i;
    int32_t ret;

    /* On Linux, use omapdrm driver to get a Tiler buffer for shared memory */
    drmFd = drmOpen("omapdrm", NULL);

    if (drmFd < 0) {
        fprintf(stderr, "could not open omapdrm device: %d: %s\n",
                         errno, strerror(errno));
        return 1;
    }

    dev = omap_device_new(drmFd);
    if (!dev) {
        fprintf(stderr, "could not get device from fd\n");
        goto leave;
    }

    /* allocate a compute structure in shared memory and get a pointer */
    compute_bo = omap_bo_new(dev, sizeof(Mx_Compute), OMAP_BO_CACHED);
    if (compute_bo) {
        compute = (Mx_Compute *)omap_bo_map(compute_bo);
    }
    else {
        fprintf(stderr, "failed to allocate omap_bo\n");
    }

    if (compute == NULL) {
        fprintf(stderr, "failed to map omap_bo to user space\n");
        goto leave;
    }

    /* initialize compute structure */
    compute->coef = 0x80400000;
    compute->key = 0xABA0;
    compute->size = 0x1000;
    compute->inBuf = NULL;
    compute->outBuf = NULL;

    /* allocate an input buffer in shared memory */
    size = compute->size * sizeof(uint32_t);
    inBuf_bo = omap_bo_new(dev, size, OMAP_BO_CACHED);
    if (inBuf_bo) {
        inBufPtr = (uint32_t *)omap_bo_map(inBuf_bo);
    }
    else {
        fprintf(stderr, "failed to allocate inBuf_bo\n");
    }

    if (inBufPtr == NULL) {
        printf("mmrpc_test: Error: inBufPtr == NULL\n");
        status = -1;
        goto leave;
    }

    /* fill input buffer with seed value */
    for (i = 0; i < compute->size; i++) {
        inBufPtr[i] = 0x2010;
    }

    /* allocate an output buffer in shared memory */
    outBuf_bo = omap_bo_new(dev, size, OMAP_BO_CACHED);
    if (outBuf_bo) {
        outBufPtr = (uint32_t *)omap_bo_map(outBuf_bo);
    }
    else {
        fprintf(stderr, "failed to allocate outBuf_bo handle\n");
    }

    if (outBufPtr == NULL) {
        printf("mmrpc_test: Error: outBufPtr == NULL\n");
        status = -1;
        goto leave;
    }

    /* clear output buffer */
    for (i = 0; i < compute->size; i++) {
        outBufPtr[i] = 0;
    }

    compute->inBuf = (uint32_t *)inBufPtr;
    compute->outBuf = (uint32_t *)outBufPtr;

    /* print some debug info */
    printf("mmrpc_test: calling Mx_compute(0x%x)\n", (unsigned int)compute);
    printf("mmrpc_test: compute->coef=0x%x\n", compute->coef);
    printf("mmrpc_test: compute->key=0x%x\n", compute->key);
    printf("mmrpc_test: compute->size=0x%x\n", compute->size);
    printf("mmrpc_test: compute->inBuf=0x%x\n", (unsigned int)compute->inBuf);
    printf("mmrpc_test: compute->outBuf=0x%x\n", (unsigned int)compute->outBuf);

    /* process the buffer */
    ret = Mx_compute_Linux(compute, omap_bo_dmabuf(compute_bo),
                                    omap_bo_dmabuf(inBuf_bo),
                                    omap_bo_dmabuf(outBuf_bo));

    if (ret < 0) {
        status = -1;
        printf("mmrpc_test: Error: Mx_Compute() failed\n");
        goto leave;
    }

    printf("mmrpc_test: after Mx_compute(0x%x)\n", (unsigned int)compute);
    printf("mmrpc_test: compute->coef=0x%x\n", compute->coef);
    printf("mmrpc_test: compute->key=0x%x\n", compute->key);
    printf("mmrpc_test: compute->size=0x%x\n", compute->size);
    printf("mmrpc_test: compute->inBuf=0x%x\n", (unsigned int)compute->inBuf);
    printf("mmrpc_test: compute->outBuf=0x%x\n", (unsigned int)compute->outBuf);
    printf("mmrpc_test: compute->inBuf[0]=0x%x\n",
            (unsigned int)compute->inBuf[0]);
    printf("mmrpc_test: compute->outBuf[0]=0x%x\n",
            (unsigned int)compute->outBuf[0]);

    /* check the output buffer */
    for (i = 0; i < compute->size; i++) {
        val = outBufPtr[i] | compute->coef;
        if (outBufPtr[i] != val) {
            status = -1;
            printf("mmrpc_test: Error: incorrect outBuf\n");
            break;
        }
    }

leave:
    if (outBuf_bo) {
        omap_bo_del(outBuf_bo);
    }
    if (inBuf_bo) {
        omap_bo_del(inBuf_bo);
    }
    if (compute_bo) {
        omap_bo_del(compute_bo);
    }
    if (dev) {
        omap_device_del(dev);
    }
    if (drmFd) {
        close(drmFd);
    }

    return (status);
}
#endif


/*
 *  ======== main ========
 */
int main(int argc, char **argv)
{
    int status;
    int32_t ret;
    UInt16 procId = PROC_ID_DFLT;

    printf("mmrpc_test: --> main\n");

    /* Parse Args: */
    switch (argc) {
        case 1:
           /* use defaults */
           break;
        case 2:
           procId   = atoi(argv[1]);
           break;
        default:
           printf("Usage: %s [<ProcId>]\n", argv[0]);
           printf("\tDefaults: ProcId: %d\n", PROC_ID_DFLT);
           exit(0);
    }

#if defined(IPC_BUILDOS_QNX)
    /* Need to start IPC for MultiProc */
    status = Ipc_start();
    if (status < 0) {
        printf("Ipc_start failed: status = %d\n", status);
        return (0);
    }
#endif

    /* initialize Mx module (setup rpc connection) */
    status = Mx_initialize(procId);

    if (status < 0) {
        goto leave;
    }

    /* invoke Mx functions */
    ret = Mx_triple(11);
    printf("mmrpc_test: Mx_triple(11), ret=%d\n", ret);

    if (ret < 0) {
        status = -1;
        goto leave;
    }

    ret = Mx_triple(111);
    printf("mmrpc_test: Mx_triple(111), ret=%d\n", ret);

    if (ret < 0) {
        status = -1;
        goto leave;
    }

    ret = Mx_add(44, 66);
    printf("mmrpc_test: Mx_add(44, 66), ret=%d\n", ret);

    if (ret < 0) {
        status = -1;
        goto leave;
    }

#if defined(IPC_BUILDOS_QNX)
    ret = callCompute_QnX();
#else
    ret = callCompute_Linux();
#endif
    if (ret < 0) {
        status = -1;
    }

leave:

    /* finalize Mx module (destroy rpc connection) */
    Mx_finalize();

#if defined(IPC_BUILDOS_QNX)
    Ipc_stop();
#endif

    if (status < 0) {
        printf("mmrpc_test: FAILED\n");
    }
    else {
        printf("mmrpc_test: PASSED\n");
    }
    return(0);
}
