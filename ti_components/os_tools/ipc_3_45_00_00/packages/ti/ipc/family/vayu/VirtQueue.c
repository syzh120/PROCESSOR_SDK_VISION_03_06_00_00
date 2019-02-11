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
 *  - Renamed module from virtio.h to VirtQueue_Object.h to match the API
 *    prefixes;
 *  - BIOS (XDC) types and CamelCasing used;
 *  - virtio_device concept removed (i.e, assumes no containing device);
 *  - simplified scatterlist from Linux version;
 *  - VirtQueue_Objects are created statically here, so just added a
 *    VirtQueue_Object_init()
 *    fxn to take the place of the Virtio vring_new_virtqueue() API;
 *  - The notify function is implicit in the implementation, and not provided
 *    by the client, as it is in Linux virtio.
 *
 *  All VirtQueue operations can be called in any context.
 *
 *  The virtio header should be included in an application as follows:
 *  @code
 *  #include <ti/ipc/family/vayu/VirtQueue.h>
 *  @endcode
 *
 */

/* this define must precede inclusion of any xdc header file */
#define Registry_CURDESC ti_ipc_family_vayu__Desc
#define MODULE_NAME "ti.ipc.family.vayu.VirtQueue"

#include <string.h>

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>

#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/gates/GateHwi.h>
#include <ti/sysbios/hal/Cache.h>

#include <ti/ipc/MultiProc.h>
#include <ti/ipc/remoteproc/Resource.h>
#include <ti/ipc/remoteproc/rsc_types.h>
#include <ti/ipc/rpmsg/virtio_ring.h>
#include <ti/ipc/rpmsg/_VirtQueue.h>
#include <ti/pm/IpcPower.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "InterruptProxy.h"
#include "VirtQueue.h"

/*
 *  The following three VIRTIO_* defines must match those in
 *  <Linux_kernel>/include/uapi/linux/virtio_config.h
 */
#define VIRTIO_CONFIG_S_ACKNOWLEDGE     1
#define VIRTIO_CONFIG_S_DRIVER          2
#define VIRTIO_CONFIG_S_DRIVER_OK       4

#define VRING_BUFS_PRIMED  (VIRTIO_CONFIG_S_ACKNOWLEDGE | \
                            VIRTIO_CONFIG_S_DRIVER | VIRTIO_CONFIG_S_DRIVER_OK)

/* Used for defining the size of the virtqueue registry */
#define NUM_QUEUES              2

/*
 * Size of the virtqueues (expressed in number of buffers supported,
 * and must be power of two)
 */
#define VQ_SIZE                 256

/*
 * enum - Predefined Mailbox Messages
 *
 * @RP_MSG_MBOX_READY: informs the slave that we're up and running. will be
 * followed by another mailbox message that carries the HOST's virtual address
 * of the shared buffer. This would allow the HOST's drivers to send virtual
 * addresses of the buffers.
 *
 * @RP_MSG_MBOX_STATE_CHANGE: informs the receiver that there is an inbound
 * message waiting in its own receive-side vring. please note that currently
 * this message is optional: alternatively, one can explicitly send the index
 * of the triggered virtqueue itself. the preferred approach will be decided
 * as we progress and experiment with those design ideas.
 *
 * @RP_MSG_MBOX_CRASH: this message indicates that the BIOS side is unhappy
 *
 * @RP_MBOX_ECHO_REQUEST: this message requests the remote processor to reply
 * with RP_MBOX_ECHO_REPLY
 *
 * @RP_MBOX_ECHO_REPLY: this is a reply that is sent when RP_MBOX_ECHO_REQUEST
 * is received.
 *
 * @RP_MBOX_ABORT_REQUEST:  tells the M3 to crash on demand
 *
 * @RP_MBOX_BOOTINIT_DONE: this message indicates the BIOS side has reached a
 * certain state during the boot process. This message is used to inform the
 * host that the basic BIOS initialization is done, and lets the host use this
 * notification to perform certain actions.
 */
enum {
    RP_MSG_MBOX_READY           = (Int)0xFFFFFF00,
    RP_MSG_MBOX_STATE_CHANGE    = (Int)0xFFFFFF01,
    RP_MSG_MBOX_CRASH           = (Int)0xFFFFFF02,
    RP_MBOX_ECHO_REQUEST        = (Int)0xFFFFFF03,
    RP_MBOX_ECHO_REPLY          = (Int)0xFFFFFF04,
    RP_MBOX_ABORT_REQUEST       = (Int)0xFFFFFF05,
    RP_MSG_FLUSH_CACHE          = (Int)0xFFFFFF06,
    RP_MSG_BOOTINIT_DONE        = (Int)0xFFFFFF07,
    RP_MSG_HIBERNATION          = (Int)0xFFFFFF10,
    RP_MSG_HIBERNATION_FORCE    = (Int)0xFFFFFF11,
    RP_MSG_HIBERNATION_ACK      = (Int)0xFFFFFF12,
    RP_MSG_HIBERNATION_CANCEL   = (Int)0xFFFFFF13
};

#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))
#define RP_MSG_NUM_BUFS     (VQ_SIZE) /* must be power of two */
#define RP_MSG_BUF_SIZE     (512)
#define RP_MSG_BUFS_SPACE   (RP_MSG_NUM_BUFS * RP_MSG_BUF_SIZE * 2)

#define PAGE_SIZE           (4096)
/*
 * The alignment to use between consumer and producer parts of vring.
 * Note: this is part of the "wire" protocol. If you change this, you need
 * to update your BIOS image as well
 */
#define RP_MSG_VRING_ALIGN  (4096)

/* With 256 buffers, our vring will occupy 3 pages */
#define RP_MSG_RING_SIZE    ((DIV_ROUND_UP(vring_size(RP_MSG_NUM_BUFS, \
                            RP_MSG_VRING_ALIGN), PAGE_SIZE)) * PAGE_SIZE)

/* The total IPC space needed to communicate with a remote processor */
#define RPMSG_IPC_MEM   (RP_MSG_BUFS_SPACE + 2 * RP_MSG_RING_SIZE)

typedef struct VirtQueue_Object {
    /* Id for this VirtQueue_Object */
    UInt16                  id;

    /* The function to call when buffers are consumed (can be NULL) */
    VirtQueue_callback      callback;

    /* Shared state */
    struct vring            vring;

    /* Number of free buffers */
    UInt16                  num_free;

    /* Last available index; updated by VirtQueue_getAvailBuf */
    UInt16                  last_avail_idx;

    /* Will eventually be used to kick remote processor */
    UInt16                  procId;

    /* Gate to protect from multiple threads */
    GateHwi_Handle       gateH;

    /* Base phys addr - used for quick pa/va translations */
    UInt32               basePa;

    /* Base virt addr - used for quick pa/va translations */
    UInt32               baseVa;
} VirtQueue_Object;

/* module diags mask */
Registry_Desc Registry_CURDESC;

static struct VirtQueue_Object *queueRegistry[NUM_QUEUES] = {NULL};

static UInt16 hostProcId;

#define DSPEVENTID              5
IInterrupt_IntInfo intInfo;

/*!
 * ======== _VirtQueue_init ========
 *
 * This function adds the VirtQueue "module" to the Registry so that
 * DIAGS will work with this non-XDC module.
 * Since VirtQueue_init is not called by XDC-VirtQueue module clients, this
 * function is called in the first VirtQueue fxn called: VirtQueue_create.
 */
static Void _VirtQueue_init()
{
    static int initialized = 0;

    if (!initialized) {
        Registry_Result result;

        /* register with xdc.runtime to get a diags mask */
        result = Registry_addModule(&Registry_CURDESC, MODULE_NAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        initialized = 1;
    }
}

static inline Void * _VirtQueue_getVA(VirtQueue_Handle vq, UInt32 pa)
{
    return (Void *)(pa - vq->basePa + vq->baseVa);
}

/*!
 * ======== VirtQueue_kick ========
 */
Void VirtQueue_kick(VirtQueue_Handle vq)
{
    /* For now, simply interrupt remote processor */
    if (vq->vring.avail->flags & VRING_AVAIL_F_NO_INTERRUPT) {
        Log_print0(Diags_USER1,
                "VirtQueue_kick: no kick because of VRING_AVAIL_F_NO_INTERRUPT\n");
        return;
    }

    Log_print2(Diags_USER1,
            "VirtQueue_kick: Sending interrupt to proc %d with payload 0x%x\n",
            (IArg)vq->procId, (IArg)vq->id);
    InterruptProxy_intSend(vq->procId, NULL, vq->id);
}

/*!
 * ======== VirtQueue_addUsedBuf ========
 */
Int VirtQueue_addUsedBuf(VirtQueue_Handle vq, Int16 head, Int len)
{
    struct vring_used_elem *used;
    IArg key;

    key = GateHwi_enter(vq->gateH);
    if ((head > vq->vring.num) || (head < 0)) {
        GateHwi_leave(vq->gateH, key);
        Error_raise(NULL, Error_E_generic, 0, 0);
    }

    /*
    * The virtqueue contains a ring of used buffers.  Get a pointer to the
    * next entry in that used ring.
    */
    used = &vq->vring.used->ring[vq->vring.used->idx % vq->vring.num];
    used->id = head;
    used->len = len;

    vq->vring.used->idx++;
    GateHwi_leave(vq->gateH, key);

    return (0);
}

/*!
 * ======== VirtQueue_getAvailBuf ========
 */
Int16 VirtQueue_getAvailBuf(VirtQueue_Handle vq, Void **buf, Int *len)
{
    Int16 head;
    IArg key;

    key = GateHwi_enter(vq->gateH);
    Log_print6(Diags_USER1, "getAvailBuf vq: 0x%x %d %d %d 0x%x 0x%x\n",
        (IArg)vq, vq->last_avail_idx, vq->vring.avail->idx, vq->vring.num,
        (IArg)&vq->vring.avail, (IArg)vq->vring.avail);

    /*  Clear flag here to avoid race condition with remote processor.
     *  This is a negative flag, clearing it means that we want to
     *  receive an interrupt when a buffer has been added to the pool.
     */
    vq->vring.used->flags &= ~VRING_USED_F_NO_NOTIFY;

    /* There's nothing available? */
    if (vq->last_avail_idx == vq->vring.avail->idx) {
        head = (-1);
    }
    else {
        /* No need to be kicked about added buffers anymore */
        vq->vring.used->flags |= VRING_USED_F_NO_NOTIFY;

        /*
         * Grab the next descriptor number they're advertising, and increment
         * the index we've seen.
         */
        head = vq->vring.avail->ring[vq->last_avail_idx++ % vq->vring.num];

        *buf = _VirtQueue_getVA(vq, vq->vring.desc[head].addr);
        *len = vq->vring.desc[head].len;
    }
    GateHwi_leave(vq->gateH, key);

    return (head);
}

/*!
 * ======== VirtQueue_disableCallback ========
 */
Void VirtQueue_disableCallback(VirtQueue_Object *vq)
{
    /* TODO */
    Log_print0(Diags_USER1, "VirtQueue_disableCallback called.");
}

/*!
 * ======== VirtQueue_enableCallback ========
 */
Bool VirtQueue_enableCallback(VirtQueue_Object *vq)
{
    Log_print0(Diags_USER1, "VirtQueue_enableCallback called.");

    /* TODO */
    return (FALSE);
}

/*!
 * ======== VirtQueue_isr ========
 * Note 'arg' is ignored: it is the Hwi argument, not the mailbox argument.
 */
Void VirtQueue_isr(UArg msg)
{
    VirtQueue_Object *vq;

    msg = InterruptProxy_intClear(hostProcId, &intInfo);

    Log_print1(Diags_USER1, "VirtQueue_isr received msg = 0x%x\n", msg);

    switch(msg) {
        case (UInt)RP_MSG_MBOX_READY:
            return;

        case (UInt)RP_MBOX_ECHO_REQUEST:
            InterruptProxy_intSend(hostProcId, NULL, (UInt)(RP_MBOX_ECHO_REPLY));
            return;

        case (UInt)RP_MBOX_ABORT_REQUEST:
            {
                /* Suppress Coverity Error: FORWARD_NULL: */
                /* coverity[assign_zero] */
                Fxn f = (Fxn)0x0;
                Log_print0(Diags_USER1, "Crash on demand ...\n");
                /* coverity[var_deref_op] */
                f();
            }
            return;

        case (UInt)RP_MSG_FLUSH_CACHE:
            Cache_wbAll();
            return;

        case (UInt)RP_MSG_HIBERNATION:
            if (IpcPower_canHibernate() == FALSE) {
                InterruptProxy_intSend(hostProcId, NULL,
                        (UInt)RP_MSG_HIBERNATION_CANCEL);
                return;
            }

            /* Fall through */
        case (UInt)RP_MSG_HIBERNATION_FORCE:
            /* Ack request */
            InterruptProxy_intSend(hostProcId, NULL,
                    (UInt)RP_MSG_HIBERNATION_ACK);
            IpcPower_suspend();
            return;

        default:
            /*
             *  If the message isn't one of the above, it's either part of the
             *  2-message synchronization sequence or it a virtqueue message
             */
            break;
    }

    /* Don't let unknown messages to pass as a virtqueue index */
    if (msg >= NUM_QUEUES) {
        /* Adding print here deliberately, we should never see this */
        System_printf("VirtQueue_isr: Invalid mailbox message 0x%x "
                "received\n", msg);
        return;
    }

    vq = queueRegistry[msg];
    if (vq) {
        vq->callback(vq);
    }
}


/*!
 * ======== VirtQueue_create ========
 */
VirtQueue_Handle VirtQueue_create(UInt16 remoteProcId, VirtQueue_Params *params,
                                  Error_Block *eb)
{
    VirtQueue_Object *vq;
    Void *vringAddr;
    Int result;

    /* Perform initialization we can't do in Instance_init (being non-XDC): */
    _VirtQueue_init();

    vq = Memory_alloc(NULL, sizeof(VirtQueue_Object), 0, eb);
    if (NULL == vq) {
        return (NULL);
    }

    /* Create the thread protection gate */
    vq->gateH = GateHwi_create(NULL, eb);
    if (Error_check(eb)) {
        Log_error0("VirtQueue_create: could not create gate object");
        Memory_free(NULL, vq, sizeof(VirtQueue_Object));
        return (NULL);
    }

    vq->callback = params->callback;
    vq->id = params->vqId;
    vq->procId = remoteProcId;
    vq->last_avail_idx = 0;

    switch (vq->id) {
        /* IPC transport vrings */
        case ID_SELF_TO_HOST:
        case ID_HOST_TO_SELF:
            vq->basePa = (UInt32)Resource_getVringDA(vq->id);
            Assert_isTrue(vq->basePa != 0, NULL);

            result = Resource_physToVirt(vq->basePa, &(vq->baseVa));
            Assert_isTrue(result == Resource_S_SUCCESS, (Assert_Id)NULL);

            vringAddr = (Void *)vq->baseVa;
            break;
        default:
            GateHwi_delete(&vq->gateH);
            Memory_free(NULL, vq, sizeof(VirtQueue_Object));
            return (NULL);
    }

    Log_print3(Diags_USER1,
            "vring: %d 0x%x (0x%x)\n", vq->id, (IArg)vringAddr,
            RP_MSG_RING_SIZE);

    /* See coverity related comment in vring_init() */
    /* coverity[overrun-call] */
    vring_init(&(vq->vring), RP_MSG_NUM_BUFS, vringAddr, RP_MSG_VRING_ALIGN);

    /*
     *  Don't trigger a mailbox message every time MPU makes another buffer
     *  available
     */
    if (vq->procId == hostProcId) {
        vq->vring.used->flags &= ~VRING_USED_F_NO_NOTIFY;
    }

    queueRegistry[vq->id] = vq;

    return (vq);
}

/*!
 * ======== VirtQueue_startup ========
 */
Void VirtQueue_startup()
{
    hostProcId = MultiProc_getId("HOST");

/*  Note that "64P" matches 64P, 674, 66 and others.  We prefer 66 on vayu,
 *  but technically vayu DSPs support any of these.
 */
#if defined(xdc_target__isaCompatible_64P)
    intInfo.intVectorId = DSPEVENTID;
#endif

    /* Initilize the IpcPower module */
    IpcPower_init();

    /*
     * Wait for HLOS (Virtio device) to indicate that priming of host's receive
     * buffers is complete, indicating that host is ready to send.
     *
     * Though this is a Linux Virtio configuration status, it must be
     * implemented by each non-Linux HLOS as well.
     */
    Log_print1(Diags_USER1, "VirtQueue_startup: VDEV status: 0x%x\n",
              Resource_getVdevStatus(VIRTIO_ID_RPMSG));
    Log_print0(Diags_USER1, "VirtQueue_startup: Polling VDEV status...\n");
    while (Resource_getVdevStatus(VIRTIO_ID_RPMSG) != VRING_BUFS_PRIMED);
    Log_print1(Diags_USER1, "VirtQueue_startup: VDEV status: 0x%x\n",
              Resource_getVdevStatus(VIRTIO_ID_RPMSG));

    InterruptProxy_intRegister(hostProcId, &intInfo, (Fxn)VirtQueue_isr,
            (UArg)NULL);
    Log_print0(Diags_USER1, "Passed VirtQueue_startup\n");
}

/*!
 * ======== VirtQueue_postCrashToMailbox ========
 */
Void VirtQueue_postCrashToMailbox(Void)
{
    InterruptProxy_intSend(0, NULL, (UInt)RP_MSG_MBOX_CRASH);
}

#define CACHE_WB_TICK_PERIOD    5

/*!
 * ======== ti_ipc_family_vayu_VirtQueue_cacheWb ========
 *
 * Used for flushing SysMin trace buffer.
 */
Void ti_ipc_family_vayu_VirtQueue_cacheWb()
{
    static UInt32 oldticks = 0;
    UInt32 newticks;

    newticks = Clock_getTicks();
    if (newticks - oldticks < (UInt32)CACHE_WB_TICK_PERIOD) {
        /* Don't keep flushing cache */
        return;
    }

    oldticks = newticks;

    /* Flush the cache */
    Cache_wbAll();
}
