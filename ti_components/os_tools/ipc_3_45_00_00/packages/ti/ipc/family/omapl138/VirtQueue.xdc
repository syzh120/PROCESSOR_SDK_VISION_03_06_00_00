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
 *
 */
/** ============================================================================
 *  @file       VirtQueue.xdc
 *
 *  @brief      Virtio Queue interface for BIOS
 *
 *  Differences between BIOS version and Linux kernel (include/linux/virtio.h):
 *  - Renamed module from virtio.h to VirtQueue.h to match the API prefixes;
 *  - BIOS (XDC) types and CamelCasing used;
 *  - virtio_device concept removed (i.e, assumes no containing device);
 *  - removed scatterlist;
 *  - VirtQueues are created statically here, so just added a VirtQueue_init()
 *    fxn to take the place of the Virtio vring_new_virtqueue() API;
 *  - The notify function is implicit in the implementation, and not provided
 *    by the client, as it is in Linux virtio.
 *  - Broke into APIs to add/get used and avail buffers, as the API is
 *    assymmetric.
 *
 *  Usage:
 *     This IPC only works between one processor designated as the Host (Linux)
 *     and one or more Slave processors (BIOS).
 *
 *     For any Host/Slave pair, there are 2 VirtQueues (aka Vrings);
 *     Only the Host adds new buffers to the avail list of a vring;
 *     Available buffers can be empty or full, depending on direction;
 *     Used buffer means "processed" (emptied or filled);
 *
 *  Host:
 *    - To send buffer to the slave processor:
 *          add_avail_buf(slave_virtqueue);
 *          kick(slave_virtqueue);
 *          get_used_buf(slave_virtqueue);
 *    - To receive buffer from slave processor:
 *          add_avail_buf(host_virtqueue);
 *          kick(host_virtqueue);
 *          get_used_buf(host_virtqueue);
 *
 *  Slave:
 *    - To send buffer to the host:
 *          get_avail_buf(host_virtqueue);
 *          add_used_buf(host_virtqueue);
 *          kick(host_virtqueue);
 *    - To receive buffer from the host:
 *          get_avail_buf(slave_virtqueue);
 *          add_used_buf(slave_virtqueue);
 *          kick(slave_virtqueue);
 *
 *  All VirtQueue operations can be called in any context.
 *
 *  The virtio header should be included in an application as follows:
 *  @code
 *  #include <ti/ipc/rpmsg/VirtQueue.h>
 *  @endcode
 *
 *  ============================================================================
 */

import  ti.sysbios.knl.Swi;
import  ti.sdo.utils.MultiProc;
import  ti.sysbios.gates.GateAll;

/*!
 *  ======== VirtQueue ========
 *
 */

@InstanceInitError
module VirtQueue
{
    // -------- Module Constants --------

    // -------- Module Types --------


    /*!
     *  ======== BasicView ========
     *  @_nodoc
     */
    metaonly struct BasicView {

    };

    /*!
     *  ======== ModuleView ========
     *  @_nodoc
     */
    metaonly struct ModuleView {

    };

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
/*    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Basic',  {type: ViewInfo.INSTANCE, viewInitFxn: 'viewInitBasic',  structName: 'BasicView'}],
                ['Module', {type: ViewInfo.MODULE,   viewInitFxn: 'viewInitModule', structName: 'ModuleView'}]
            ]
         });
*/
    // -------- Module Proxies --------

    // -------- Module Parameters --------

    /*
     * Sizes of the virtqueues (expressed in number of buffers supported,
     * and must be power of two)
     */
    config UInt VQ0_SIZE = 256;
    config UInt VQ1_SIZE = 256;

    /* See VirtQueue.c also for other constants:   */
    config UInt RP_MSG_NUM_BUFS = VQ0_SIZE; /* must be power of two */

    config UInt PAGE_SIZE = 4096;

    /*
     * The alignment to use between consumer and producer parts of vring.
     * Note: this is part of the "wire" protocol. If you change this, you need
     * to update your BIOS image as well
     */
    config UInt RP_MSG_VRING_ALIGN = 4096;

   /*!
    * ======== startup ========
    *
    * Plug interrupts, and if host, initialize vring memory and send
    * startup sequence events to slave.
    */
    Void startup(UInt16 remoteProcId, Bool isHost);

instance:

    /*!
     *  @brief      Initialize at runtime the VirtQueue
     *
     *  Maps to Instance_init function
     *
     *  @param[in]  remoteProcId    Remote processor ID associated with this VirtQueue.
     *
     *  @Returns    Returns a handle to a new initialized VirtQueue.
     */
    @DirectCall
    create(UInt16 remoteProcId);

    /*!
     *  @brief      Notify other processor of new buffers in the queue.
     *
     *  After one or more add_buf calls, invoke this to kick the other side.
     *
     *  @param[in]  vq        the VirtQueue.
     *
     *  @sa         VirtQueue_addBuf
     */
    @DirectCall
    Void kick();

    /*!
     *  @brief      VirtQueue instance returns slave status
     *
     *  Returns if this VirtQueue instance belongs to a slave
     *
     *  @param[in]  vq        the VirtQueue.
     *
     */
    @DirectCall
    Bool isSlave();

    /*!
     *  @brief      VirtQueue instance returns host status
     *
     *  Returns if this VirtQueue instance belongs to a host
     *
     *  @param[in]  vq        the VirtQueue.
     *
     */
    @DirectCall
    Bool isHost();

    /*!
     *  @brief      VirtQueue instance returns queue ID
     *
     *  Returns VirtQueue instance's queue ID.
     *
     *  @param[in]  vq        the VirtQueue.
     *
     */
    @DirectCall
    UInt16 getId();

    /*!
     *  @brief      VirtQueue instance returns Swi handle
     *
     *  Returns VirtQueue instance Swi handle
     *
     *  @param[in]  vq        the VirtQueue.
     *
     */
    @DirectCall
    Swi.Handle getSwiHandle();

    /*
     *  ========================================================================
     *  Host Only Functions:
     *  ========================================================================
     */

    /*!
     *  @brief      Add available buffer to virtqueue's available buffer list.
     *              Only used by Host.
     *
     *  @param[in]  vq        the VirtQueue.
     *  @param[in]  buf      the buffer to be processed by the slave.
     *
     *  @return     Remaining capacity of queue or a negative error.
     *
     *  @sa         VirtQueue_getUsedBuf
     */
    @DirectCall
    Int addAvailBuf(Void *buf);

    /*!
     *  @brief      Get the next used buffer.
     *              Only used by Host.
     *
     *  @param[in]  vq        the VirtQueue.
     *
     *  @return     Returns NULL or the processed buffer.
     *
     *  @sa         VirtQueue_addAvailBuf
     */
    @DirectCall
    Void *getUsedBuf();

    /*
     *  ========================================================================
     *  Slave Only Functions:
     *  ========================================================================
     */

    /*!
     *  @brief      Get the next available buffer.
     *              Only used by Slave.
     *
     *  @param[in]  vq        the VirtQueue.
     *  @param[out] buf       Pointer to location of available buffer;
     *  @param[out] len       Length of the available buffer message.
     *
     *  @return     Returns a token used to identify the available buffer, to be
     *              passed back into VirtQueue_addUsedBuf();
     *              token is negative if failure to find an available buffer.
     *
     *  @sa         VirtQueue_addUsedBuf
     */
    @DirectCall
    Int16 getAvailBuf(Void **buf, Int *len);

    /*!
     *  @brief      Add used buffer to virtqueue's used buffer list.
     *              Only used by Slave.
     *
     *  @param[in]  vq        the VirtQueue.
     *  @param[in]  token     token of the buffer added to vring used list.
     *  @param[in]  len       length of the message being added.
     *
     *  @return     Remaining capacity of queue or a negative error.
     *
     *  @sa         VirtQueue_getAvailBuf
     */
    @DirectCall
    Int addUsedBuf(Int16 token, Int len);

    // -------- Handle Parameters --------

    config Fxn callback = null;

    config Int vqId = 0;

    // -------- Handle Functions --------

internal:   /* not for client use */

    /*! Statically retrieve procIds to avoid doing this at runtime */
    config UInt hostProcId  = MultiProc.INVALIDID;
    config UInt dspProcId   = MultiProc.INVALIDID;

    /*!
     *  ======== hostIsr ========
     */
    Void hostIsr(UArg msg);

    /*!
     *  ======== slaveIsr ========
     */
    Void slaveIsr(UArg msg);

    /*!
     * ======== Module_State ========
     * @_nodoc
     */
    struct Module_State
    {
        UInt16 hostSlaveSynced;
        UInt16 virtQueueInitialized;
        UInt32 *queueRegistry;
        Ptr    traceBufPtr;
    }

    /*!
     *  ======== Instance_State ========
     *  @_nodoc
     */
    struct Instance_State {
        Bool hostSlaveSynced;
        UInt16 id;
        Fxn callback;
        Void *vringPtr;
        UInt16 num_free;
        UInt16 last_avail_idx;
        UInt16 last_used_idx;
        UInt16 procId;
        GateAll.Handle gateH;
    };
}
