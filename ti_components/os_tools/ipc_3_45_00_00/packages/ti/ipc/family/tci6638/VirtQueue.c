/*
 * Copyright (c) 2011-2015 Texas Instruments Incorporated - http://www.ti.com
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

/** ============================================================================
 *  @file       VirtQueue.c
 *
 *  @brief      Virtio Queue implementation for BIOS
 *
 *  Differences between BIOS version and Linux kernel (include/linux/virtio.h):
 *  - Renamed module from virtio.h to VirtQueue.h to match the API prefixes
 *  - XDC Standard Types and CamelCasing used
 *  - virtio_device concept removed (i.e, assumes no containing device)
 *  - simplified scatterlist from Linux version
 *  - VirtQueue objects are created statically, added VirtQueue_Instance_init()
 *    fxn to take the place of the Virtio vring_new_virtqueue() API
 *  - The notify function is implicit in the implementation, and not provided
 *    by the client, as it is in Linux virtio
 *
 *  All VirtQueue operations can be called in any context.
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/SysMin.h>
#include <ti/sysbios/gates/GateAll.h>

#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/family/c66/Cache.h>
#include <ti/sysbios/knl/Swi.h>

#include <ti/ipc/remoteproc/Resource.h>

#include <ti/ipc/MultiProc.h>

#include "package/internal/VirtQueue.xdc.h"

#include <string.h>

#include <ti/ipc/rpmsg/_VirtQueue.h>
#include <ti/ipc/rpmsg/virtio_ring.h>

/* Used for defining the size of the virtqueue registry */
#define NUM_QUEUES 2

#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))
#define RP_MSG_BUFS_SPACE   (VirtQueue_RP_MSG_NUM_BUFS * RPMSG_BUF_SIZE * 2)

/* With 256 buffers, our vring will occupy 3 pages */
#define RP_MSG_RING_SIZE    \
        ((DIV_ROUND_UP(vring_size(VirtQueue_RP_MSG_NUM_BUFS, \
        VirtQueue_RP_MSG_VRING_ALIGN), \
        VirtQueue_PAGE_SIZE)) * VirtQueue_PAGE_SIZE)

/* The total IPC space needed to communicate with a remote processor */
#define RPMSG_IPC_MEM   (RP_MSG_BUFS_SPACE + 2 * RP_MSG_RING_SIZE)

#define ID_SELF_TO_HOST 0
#define ID_HOST_TO_SELF 1

extern volatile cregister UInt DNUM;

static VirtQueue_Object *queueRegistry[NUM_QUEUES] = {NULL};

static inline  Void * mapPAtoVA(UInt pa)
{
    return (Void *)(pa | 0x80000000);
}

static inline UInt mapVAtoPA(Void * va)
{
    return ((UInt)va & 0x000fffffU) | 0xe1000000U;
}

/*
 * ======== VirtQueue_init ========
 */
Void VirtQueue_init()
{
    extern cregister volatile UInt DNUM;
    UInt16 clusterId;
    UInt16 procId;

    /*  VirtQueue_init() must be called before MultiProcSetup_init().
     *  Check the xdc_runtime_Startup_firstFxns__A array in the XDC
     *  generated code. Abort if the procId has already been set; we
     *  must set it!
     */
    if (MultiProc_self() != MultiProc_INVALIDID) {
        System_abort("VirtQueue_init(): MultiProc_self already set!");
        return;
    }

    /* clusterId is needed to support single image loading */
    clusterId = MultiProc_getBaseIdOfCluster();

    /* compute local procId, add one to account for HOST processor */
    procId = clusterId + DNUM + 1;

    /* set the local procId */
    MultiProc_setLocalId(procId);
}

/*
 * ======== VirtQueue_Instance_init ========
 */
Int VirtQueue_Instance_init(VirtQueue_Object *vq, UInt16 remoteProcId,
                             const VirtQueue_Params *params, Error_Block *eb)
{
    void *vringAddr = NULL;
#if !defined(xdc_runtime_Assert_DISABLE_ALL) \
        || !defined(xdc_runtime_Log_DISABLE_ALL)
    UInt32 marValue;
#endif

    VirtQueue_module->traceBufPtr = Resource_getTraceBufPtr();

    /* create the thread protection gate */
    vq->gateH = GateAll_create(NULL, eb);
    if (Error_check(eb)) {
        Log_error0("VirtQueue_create: could not create gate object");
        Error_raise(NULL, Error_E_generic, 0, 0);
        return(0);
    }

    vq->vringPtr = Memory_calloc(NULL, sizeof(struct vring), 0, eb);
    Assert_isTrue((vq->vringPtr != NULL), NULL);

    vq->callback = params->callback;
    vq->id = params->vqId;
    vq->procId = remoteProcId;
    vq->last_avail_idx = 0;
    vq->last_used_idx = 0;
    vq->num_free = VirtQueue_RP_MSG_NUM_BUFS;
    vq->swiHandle = params->swiHandle;

    switch (vq->id) {
        case ID_SELF_TO_HOST:
        case ID_HOST_TO_SELF:
            vringAddr = (struct vring *)Resource_getVringDA(vq->id);
            Assert_isTrue(vringAddr != NULL, NULL);
#ifdef PER_CORE_VRING_PATCH
            /* Add per core offset: must match on host side: */
            vringAddr = (struct vring *)((UInt32)vringAddr +
                                         (DNUM * VirtQueue_VRING_OFFSET));
#endif
            /* Also, assert that the vring address is non-cached: */
#if !defined(xdc_runtime_Assert_DISABLE_ALL) \
        || !defined(xdc_runtime_Log_DISABLE_ALL)
            marValue = Cache_getMar((Ptr)vringAddr);
#endif
            Log_print1(Diags_USER1, "Vring cache is %s",
                 (IArg)(marValue & 0x1 ? "enabled" : "disabled"));
            Assert_isTrue(!(marValue & 0x1), NULL);
            break ;

         default:
            Log_error1("VirtQueue_create: invalid vq->id: %d", vq->id);
            GateAll_delete(&vq->gateH);
            Memory_free(NULL, vq->vringPtr, sizeof(struct vring));
            Error_raise(NULL, Error_E_generic, 0, 0);
            return(0);
    }

    Log_print3(Diags_USER1, "vring: %d 0x%x (0x%x)", vq->id, (IArg)vringAddr,
            RP_MSG_RING_SIZE);

    vring_init(vq->vringPtr, VirtQueue_RP_MSG_NUM_BUFS, vringAddr,
            VirtQueue_RP_MSG_VRING_ALIGN);

    queueRegistry[vq->id] = vq;
    return(0);
}

/*
 * ======== VirtQueue_kick ========
 */
Void VirtQueue_kick(VirtQueue_Handle vq)
{
    struct vring *vring = vq->vringPtr;

    /* For now, simply interrupt remote processor */
    if (vring->avail->flags & VRING_AVAIL_F_NO_INTERRUPT) {
        Log_print0(Diags_USER1, "VirtQueue_kick: no kick because of "
                "VRING_AVAIL_F_NO_INTERRUPT");
        return;
    }

    Log_print2(Diags_USER1, "VirtQueue_kick: Sending interrupt to proc %d "
            "with payload 0x%x", (IArg)vq->procId, (IArg)vq->id);

    VirtQueue_InterruptProxy_intSend(vq->procId, NULL, 0);
}

/*
 * ======== VirtQueue_addUsedBuf ========
 */
Int VirtQueue_addUsedBuf(VirtQueue_Handle vq, Int16 head, Int len)
{
    struct vring_used_elem *used;
    struct vring *vring = vq->vringPtr;
    IArg key;

    key = GateAll_enter(vq->gateH);
    if ((head > vring->num) || (head < 0)) {
        Error_raise(NULL, Error_E_generic, 0, 0);
    }
    else {
        /*
         * The virtqueue contains a ring of used buffers.  Get a pointer to the
         * next entry in that used ring.
         */
        used = &vring->used->ring[vring->used->idx % vring->num];
        used->id = head;
        used->len = len;

        vring->used->idx++;
    }
    GateAll_leave(vq->gateH, key);

    return (0);
}

/*
 * ======== VirtQueue_addAvailBuf ========
 */
Int VirtQueue_addAvailBuf(VirtQueue_Object *vq, Void *buf)
{
    UInt16 avail;
    struct vring *vring = vq->vringPtr;
    IArg key;

    key = GateAll_enter(vq->gateH);
    if (vq->num_free == 0) {
        /* There's no more space */
        Error_raise(NULL, Error_E_generic, 0, 0);
    }
    else {
        vq->num_free--;

        avail =  vring->avail->idx++ % vring->num;

        vring->desc[avail].addr = mapVAtoPA(buf);
        vring->desc[avail].len = RPMSG_BUF_SIZE;
    }
    GateAll_leave(vq->gateH, key);

    return (vq->num_free);
}

/*
 * ======== VirtQueue_getUsedBuf ========
 */
Void *VirtQueue_getUsedBuf(VirtQueue_Object *vq)
{
    UInt16 head;
    Void *buf;
    struct vring *vring = vq->vringPtr;
    IArg key;

    key = GateAll_enter(vq->gateH);
    /* There's nothing available? */
    if (vq->last_used_idx == vring->used->idx) {
        buf = NULL;
    }
    else {
        head = vring->used->ring[vq->last_used_idx % vring->num].id;
        vq->last_used_idx++;
        vq->num_free++;

        buf = mapPAtoVA(vring->desc[head].addr);
    }
    GateAll_leave(vq->gateH, key);

    return (buf);
}

/*
 * ======== VirtQueue_getAvailBuf ========
 */
Int16 VirtQueue_getAvailBuf(VirtQueue_Handle vq, Void **buf, Int *len)
{
    Int16 head;
    struct vring *vring = vq->vringPtr;
    IArg key;

    key = GateAll_enter(vq->gateH);
    Log_print6(Diags_USER1, "getAvailBuf vq: 0x%x %d %d %d 0x%x 0x%x",
        (IArg)vq, (IArg)vq->last_avail_idx, (IArg)vring->avail->idx,
        (IArg)vring->num, (IArg)&vring->avail, (IArg)vring->avail);

    /*  Clear flag here to avoid race condition with remote processor.
     *  This is a negative flag, clearing it means that we want to
     *  receive an interrupt when a buffer has been added to the pool.
     */
    vring->used->flags &= ~VRING_USED_F_NO_NOTIFY;

    /* There's nothing available? */
    if (vq->last_avail_idx == vring->avail->idx) {
        head = (-1);
    }
    else {
        /* No need to be kicked about added buffers anymore */
        vring->used->flags |= VRING_USED_F_NO_NOTIFY;

        /*
         * Grab the next descriptor number they're advertising, and increment
         * the index we've seen.
         */
        head = vring->avail->ring[vq->last_avail_idx++ % vring->num];

        *buf = mapPAtoVA(vring->desc[head].addr);
        *len = vring->desc[head].len;
    }
    GateAll_leave(vq->gateH, key);

    return (head);
}

/*
 * ======== VirtQueue_isr ========
 * Note 'msg' is ignored: it is only used where there is a mailbox payload.
 */
static Void VirtQueue_isr(UArg msg)
{
    VirtQueue_Object *vq;

    Log_print1(Diags_USER1, "VirtQueue_isr received msg = 0x%x", msg);

    vq = queueRegistry[0];
    if (vq) {
        vq->callback(vq);
    }
    vq = queueRegistry[1];
    if (vq) {
        vq->callback(vq);
    }
}

/*
 * ======== VirtQueue_startup ========
 */
Void VirtQueue_startup(UInt16 procId, Bool isHost)
{

    /* Wait for first kick from host, which happens to coincide with the
     * priming of host's receive buffers, indicating host is ready to send.
     * Since interrupt is cleared, we throw away this first kick, which is
     * OK since we don't process this in the ISR anyway.
     */
    Log_print0(Diags_USER1, "VirtQueue_startup: Polling for host int...");
    while (!VirtQueue_InterruptProxy_intClear(procId, NULL));

    VirtQueue_InterruptProxy_intRegister(procId, NULL, (Fxn)VirtQueue_isr, 0);
    Log_print0(Diags_USER1, "Passed VirtQueue_startup");
}

/* By convention, Host VirtQueues host are the even number in the pair */
Bool VirtQueue_isSlave(VirtQueue_Handle vq)
{
  return (vq->id & 0x1);
}

Bool VirtQueue_isHost(VirtQueue_Handle vq)
{
  return (~(vq->id & 0x1));
}

UInt16 VirtQueue_getId(VirtQueue_Handle vq)
{
  return (vq->id);
}

Swi_Handle VirtQueue_getSwiHandle(VirtQueue_Handle vq)
{
  return (vq->swiHandle);
}

#define CACHE_WB_TICK_PERIOD    5

/*
 * ======== VirtQueue_cacheWb ========
 *
 * Used for flushing SysMin trace buffer.
 */
Void VirtQueue_cacheWb()
{
    static UInt32 oldticks = 0;
    UInt32 newticks;

    newticks = Clock_getTicks();
    if (newticks - oldticks < (UInt32)CACHE_WB_TICK_PERIOD) {
        /* Don't keep flushing cache */
        return;
    }

    oldticks = newticks;

    /* Flush the cache of the SysMin buffer only: */
    Assert_isTrue((VirtQueue_module->traceBufPtr != NULL), NULL);
    Cache_wb(VirtQueue_module->traceBufPtr, SysMin_bufSize, Cache_Type_ALL,
             FALSE);
}
