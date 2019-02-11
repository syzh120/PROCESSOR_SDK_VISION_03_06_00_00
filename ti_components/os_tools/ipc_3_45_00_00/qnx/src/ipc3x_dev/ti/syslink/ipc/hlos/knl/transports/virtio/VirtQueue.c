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
/** ============================================================================
 *  @file       VirtQueue.c
 *
 *  @brief      Virtio Queue implementation for BIOS
 *
 *  Differences between BIOS version and Linux kernel (include/linux/virtio.h):
 *  - Renamed module from virtio.h to VirtQueue_Object.h to match the API prefixes;
 *  - BIOS (XDC) types and CamelCasing used;
 *  - virtio_device concept removed (i.e, assumes no containing device);
 *  - simplified scatterlist from Linux version;
 *  - VirtQueue_Objects are created statically here, so just added a VirtQueue_Object_init()
 *    fxn to take the place of the Virtio vring_new_virtqueue() API;
 *  - The notify function is implicit in the implementation, and not provided
 *    by the client, as it is in Linux virtio.
 *
 *  All VirtQueue operations can be called in any context.
 *
 *  The virtio header should be included in an application as follows:
 *  @code
 *  #include <ti/ipc/rpmsg/VirtQueue.h>
 *  @endcode
 *
 */

#include <ti/syslink/Std.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>

#include <_ArchIpcInt.h>
#include <ArchIpcInt.h>
#include "VirtQueue.h"

#include <ti/ipc/MultiProc.h>
#include <ti/syslink/ProcMgr.h>

#include <ti/syslink/utils/String.h>

#include "virtio_ring.h"
#include "_rpmsg.h"
#include <ipu_pm.h>
#include <pthread.h>

/* Used for defining the size of the virtqueue registry */
#define NUM_QUEUES                      2

typedef struct VirtQueue_Object {
    /* Id for this VirtQueue_Object */
    UInt16                  id;

    /* The function to call when buffers are consumed (can be NULL) */
    VirtQueue_callback      callback;

    /* Shared state */
    struct vring            vring;

    /* Number of free buffers */
    UInt16                  num_free;

    /* Last available index; updated by VirtQueue_getUsedBuf */
    UInt16                  last_used_idx;

    /* Will eventually be used to kick remote processor */
    UInt16                  procId;

    /* Interrupt Id for kicking remote processor */
    UInt16                  intId;

    /* Local virtual address for vring struct */
    UInt32                  vaddr;

    /* Physical address for vring struct */
    UInt32                  paddr;

    /* Private arg from user */
    void *                  arg;

    /* Mutex to protect vrings from multi-thread access */
    pthread_mutex_t         mutex;
} VirtQueue_Object;

static UInt numQueues = 0;
static struct VirtQueue_Object *queueRegistry[MultiProc_MAXPROCESSORS][NUM_QUEUES];

static UInt32 coreIntId[MultiProc_MAXPROCESSORS];

static inline Void * mapPAtoVA(VirtQueue_Handle vq, UInt pa)
{
    UInt offset = vq->paddr - pa;
    return (Void *)(vq->vaddr - offset);
}

static inline UInt mapVAtoPA(VirtQueue_Handle vq, Void * va)
{
    UInt offset = vq->vaddr - (UInt)va;
    return (UInt)(vq->paddr - offset);
}

/*!
 * ======== VirtQueue_cb ========
 */
Void VirtQueue_cb(Void *buf, VirtQueue_Handle vq)
{
    if (vq/* && vq->cb_enabled*/) {
        /* Call the registered vq callback */
        vq->callback(vq, vq->arg);
    }
}

/*!
 * ======== VirtQueue_kick ========
 */
Void VirtQueue_kick(VirtQueue_Handle vq)
{
    /*
     * We need to expose available array entries before sending an
     * interrupt.
     */
#if _NTO_VERSION >= 660
    asm("   DSB ST");
#else
    asm("   DSB  ");
#endif

    GT_2trace(curTrace, GT_2CLASS,
            "VirtQueue_kick: Sending interrupt to proc %d with payload 0x%x",
            vq->procId, vq->id);

#if defined (IPC_USE_IPU_PM)
    ipu_pm_restore_ctx(vq->procId);
#endif
    ArchIpcInt_sendInterrupt(vq->procId, vq->intId, vq->id);
}

/*!
 * ======== VirtQueue_addUsedBufAddr ========
 */
Int VirtQueue_addUsedBufAddr(VirtQueue_Handle vq, Void *buf, UInt32 len)
{
    struct vring_used_elem *used = NULL;
    UInt16 head = 0;
    Int status = 0;

    if ((head > vq->vring.num) || (head < 0)) {
        status = -1;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VirtQueue_addUsedBuf",
                             status,
                             "head is invalid!");
    }
    else {
        /*
         * The virtqueue contains a ring of used buffers.  Get a pointer to the
         * next entry in that used ring.
         */
        head = vq->vring.used->idx % vq->vring.num;
        vq->vring.desc[head].addr = mapVAtoPA(vq, buf);
        vq->vring.desc[head].len = len;
        vq->vring.desc[head].flags = 0;
        used = &vq->vring.used->ring[head];
        used->id = head;
        used->len = len;

        vq->vring.used->idx++;
    }

    return status;
}

/*!
 * ======== VirtQueue_addAvailBuf ========
 */
Int VirtQueue_addAvailBuf(VirtQueue_Handle vq, Void *buf, UInt32 len, Int16 head)
{
    UInt16 avail;

    pthread_mutex_lock(&vq->mutex);

    if (vq->num_free == 0) {
        /* There's no more space */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VirtQueue_addAvailBuf",
                             (-1), // TODO: Make this a valid error code
                             "no more space!");

    }
    else {
        vq->num_free--;

        avail = vq->vring.avail->idx % vq->vring.num;
        vq->vring.avail->ring[avail] = head;

        vq->vring.desc[head].addr = mapVAtoPA(vq, buf);
        vq->vring.desc[head].len = len;
        vq->vring.desc[head].flags = 0;

        /*
         * Descriptors and available array need to be set before we expose the
         * new available array entries.
         */
#if _NTO_VERSION >= 660
        asm("   DMB ST");
#else
        asm("   DMB  ");
#endif

        vq->vring.avail->idx++;
    }

    pthread_mutex_unlock(&vq->mutex);

    return (vq->num_free);
}

/*!
 * ======== VirtQueue_getUsedBuf ========
 */
Int16 VirtQueue_getUsedBuf(VirtQueue_Object *vq, Void **buf)
{
    UInt16 head;

    pthread_mutex_lock(&vq->mutex);

    /* There's nothing available? */
    if (vq->last_used_idx == vq->vring.used->idx) {
        /* We need to know about added buffers */
        vq->vring.avail->flags &= ~VRING_AVAIL_F_NO_INTERRUPT;

        pthread_mutex_unlock(&vq->mutex);

        return (-1);
    }

    /* Only get used array entries after they have been exposed. */
    asm("   DMB");

    /* No need to know be kicked about added buffers anymore */
    //vq->vring.avail->flags |= VRING_AVAIL_F_NO_INTERRUPT; // disabling for now, since there seems to be a race condition where an M3->A9 message is not detected because the interrupt isn't sent.

    head = vq->vring.used->ring[vq->last_used_idx % vq->vring.num].id;
    vq->last_used_idx++;
    vq->num_free++;

    pthread_mutex_unlock(&vq->mutex);

    *buf = mapPAtoVA(vq, vq->vring.desc[head].addr);

    return (head);
}

/*!
 * ======== VirtQueue_disableCallback ========
 */
Void VirtQueue_disableCallback(VirtQueue_Handle vq)
{
    //TODO
    GT_0trace(curTrace, GT_3CLASS, "VirtQueue_disableCallback not supported.");
}

/*!
 * ======== VirtQueue_enableCallback ========
 */
Bool VirtQueue_enableCallback(VirtQueue_Handle vq)
{
    GT_0trace(curTrace, GT_3CLASS, "VirtQueue_enableCallback not supported.");

    //TODO
    return (FALSE);
}

/*!
 *  @brief      This function implements the interrupt service routine for the
 *              interrupt received from the remote cores.
 *
 *  @param      refData       object to be handled in ISR
 *
 *  @sa         VirtQueue_cb
 */
static
Bool
VirtQueue_ISR (UInt32 msg, Void * arg)
{
    UInt32 procId = (UInt32)arg;
    ProcMgr_Handle handle = NULL;
    Int status = 0;

    GT_2trace (curTrace, GT_ENTER, "_VirtQueue_ISR", msg, arg);

        /* Interrupt clear is done by ArchIpcInt. */

        switch(msg) {
            case (UInt)RP_MBOX_ECHO_REPLY:
                Osal_printf ("Echo reply from %s",
                             MultiProc_getName(procId));
                break;

            case (UInt)RP_MBOX_CRASH:
                Osal_printf ("Crash notification for %s",
                             MultiProc_getName(procId));
                status = ProcMgr_open(&handle, procId);
                if (status >= 0) {
                    ProcMgr_setState(handle, ProcMgr_State_Error);
                    ProcMgr_close(&handle);
                }
                else {
                    Osal_printf("Failed to open ProcMgr handle");
                }
                break;

            case (UInt)RP_MBOX_BOOTINIT_DONE:
                Osal_printf ("Got BootInit done from %s",
                             MultiProc_getName(procId));
                // TODO: What to do with this message?
                break;

            case (UInt)RP_MBOX_HIBERNATION_ACK:
                Osal_printf ("Got Hibernation ACK from %s",
                             MultiProc_getName(procId));
                break;

            case (UInt)RP_MBOX_HIBERNATION_CANCEL:
                Osal_printf ("Got Hibernation CANCEL from %s",
                             MultiProc_getName(procId));
                break;

            default:
                /*
                 *  If the message isn't one of the above, it's a virtqueue
                 *  message
                 */
                if (msg%2 < NUM_QUEUES) {
                    /* This message is for us! */
                    VirtQueue_cb((void *)msg, queueRegistry[procId][msg%2]);
                }
            break;
        }

    return TRUE;
}

/*!
 * ======== VirtQueue_create ========
 */
VirtQueue_Handle VirtQueue_create (VirtQueue_callback callback, UInt16 procId,
                                   UInt16 id, UInt32 vaddr, UInt32 paddr,
                                   UInt32 num, UInt32 align, Void *arg)
{
    VirtQueue_Object *vq = NULL;

    vq = Memory_alloc(NULL, sizeof(VirtQueue_Object), 0, NULL);
    if (!vq) {
        return (NULL);
    }

    vq->callback = callback;
    vq->id = id;
    numQueues++;
    vq->procId = procId;
    vq->intId = coreIntId[procId];
    vq->arg = arg;

    /* init the vring */
    vring_init(&(vq->vring), num, (void *)vaddr, align);

    vq->num_free = num;
    vq->last_used_idx = 0;
    vq->vaddr = vaddr;
    vq->paddr = paddr;

    vq->vring.avail->idx = 0;
    vq->vring.used->idx = 0;

    /* Initialize the flags */
    vq->vring.avail->flags = 0;
    vq->vring.used->flags = 0;

    /* Store the VirtQueue locally */
    if (queueRegistry[procId][vq->id%2] == NULL)
        queueRegistry[procId][vq->id%2] = vq;
    else {
        Osal_printf ("VirtQueue ID %d already created", id);
        Memory_free(NULL, vq, sizeof(VirtQueue_Object));
        vq = NULL;
    }

    /* Initialize mutex */
    pthread_mutex_init(&vq->mutex, NULL);

    return (vq);
}

/*!
 * ======== VirtQueue_delete ========
*/
Int VirtQueue_delete (VirtQueue_Handle * vq)
{
    VirtQueue_Object * obj = (VirtQueue_Object *)(*vq);
    /* Store the VirtQueue locally */
    queueRegistry[obj->procId][obj->id%2] = NULL;

    /* Destroy mutex */
    pthread_mutex_destroy(&obj->mutex);

    Memory_free(NULL, obj, sizeof(VirtQueue_Object));
    *vq = NULL;
    numQueues--;

    return 0;
}

/*!
 * ======== VirtQueue_startup ========
 */
Void VirtQueue_startup(UInt16 procId, UInt32 intId, UInt32 paddr)
{
    Int32 status = 0;
    UInt32 arg = procId;

    coreIntId[procId] = intId;

    /* Register for interrupts with CORE0, CORE1 messages come through CORE0 */
    status = ArchIpcInt_interruptRegister (procId,
                                           intId,
                                           VirtQueue_ISR, (Ptr)arg);
    if (status >= 0) {
        /* Notify the remote proc that the mbox is ready */
        status = ArchIpcInt_sendInterrupt (procId,
                                           intId,
                                           RP_MBOX_READY);
    }
}

/*!
 * ======== VirtQueue_startup ========
 */
Void VirtQueue_destroy(UInt16 procId)
{
    Int32 status = 0;
    Int i = 0;

    for (i = 0; i < NUM_QUEUES; i++) {
        if (queueRegistry[procId][i]) {
            VirtQueue_delete(&queueRegistry[procId][i]);
            queueRegistry[procId][i] = NULL;
        }
    }

    /* Un-register for interrupts with CORE0 */
    status = ArchIpcInt_interruptUnregister (procId);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VirtQueue_destroy",
                             status,
                             "ArchIpcInt_interruptUnregister failed");
    }
}
