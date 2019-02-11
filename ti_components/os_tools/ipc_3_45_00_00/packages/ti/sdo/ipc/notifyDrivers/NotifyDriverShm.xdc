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
 *  ======== NotifyDriverShm.xdc ================
 *
 */

import xdc.runtime.Error;
import ti.sdo.utils.MultiProc;
import ti.sdo.ipc.interfaces.INotifyDriver;
import ti.sdo.ipc.notifyDrivers.IInterrupt;
import ti.sdo.ipc.Notify;

import xdc.rov.ViewInfo;

/*!
 *  ======== NotifyDriverShm ========
 *  A shared memory driver for the Notify Module.
 *
 *  This is a {@link ti.sdo.ipc.Notify} driver that utilizes shared memory
 *  and inter-processor hardware interrupts for notification between cores.
 *  This driver supports caching and currently expects a cache line size of 128
 *  Bytes. Event priorities are supported and correspond to event numbers used
 *  to register the events.
 *
 *  This driver is designed to work with a variety of devices, each with
 *  distinct interrupt mechanisms.  Therefore, this module needs to be plugged
 *  with an appropriate module that implements the {@link IInterrupt} interface
 *  for a given device.
 *
 *  The driver utilizes shared memory in the manner indicated by the following
 *  diagram.
 *
 *  @p(code)
 *
 *  NOTE: Processors '0' and '1' correspond to the processors with lower and
 *        higher MultiProc ids, respectively
 *
 * sharedAddr -> --------------------------- bytes
 *               |  recvInitStatus (0)     | 4  -\
 *               |  sendInitStatus (0)     | 4   |= sizeof(ProcCtrl)
 *               |  eventRegMask (0)       | 4   |
 *               |  eventEnableMask (0)    | 4  -/
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *               |  recvInitStatus (1)     | 4
 *               |  sendInitStatus (1)     | 4
 *               |  eventRegMask (1)       | 4
 *               |  eventEnableMask (1)    | 4
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *               |  eventEntry_0 (0)       | 12 -> sizeof(EventEntry)
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *               |  eventEntry_1 (0)       | 12
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *                       ... ...
 *               |-------------------------|
 *               |  eventEntry_N (0)       | 12
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *               |  eventEntry_0 (1)       | 12
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *               |  eventEntry_1 (1)       | 12
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *                       ... ...
 *               |-------------------------|
 *               |  eventEntry_N (1)       | 12
 *               |  [PADDING] (if needed)  |
 *               |-------------------------|
 *
 *
 *  Legend:
 *  (0), (1) : Memory that belongs to the proc with lower and higher
 *             MultiProc.id, respectively
 *   |----|  : Cache line boundary
 *   N       : Notify_numEvents - 1
 *
 *  @p
 */

@InstanceInitError
@InstanceFinalize

module NotifyDriverShm inherits ti.sdo.ipc.interfaces.INotifyDriver
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String      remoteProcName;
        Bool        cacheEnabled;
    }

    /*! @_nodoc */
    metaonly struct EventDataView {
        UInt        eventId;
        String      procName;
        Bool        enabled;
        Bool        flagged;
        Ptr         payload;
    }

    /*!
     *  ======== rovViewInfo ========
     */
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Basic',
                    {
                        type: ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ],
                ['Events',
                    {
                        type: ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitData',
                        structName: 'EventDataView'
                    }
                ],
            ]
        });


    /*! @_nodoc
     *  IInterrupt proxy that handles interrupts between multiple CPU cores
     */
    proxy InterruptProxy inherits IInterrupt;

    /*!
     *  ======== sharedMemReq ========
     *  Amount of shared memory required for creation of each instance
     *
     *  @param(params)      Pointer to parameters that will be used in the
     *                      create
     *
     *  @a(returns)         Number of MAUs in shared memory needed to create
     *                      the instance.
     */
    SizeT sharedMemReq(const Params *params);

instance:

    /*!
     *  ======== sharedAddr ========
     *  Address in shared memory where this instance will be placed
     *
     *  Use {@link #sharedMemReq} to determine the amount of shared memory
     *  required.
     */
    config Ptr sharedAddr = null;

    /*!
     *  ======== cacheEnabled ========
     *  Whether cache operations will be performed
     *
     *  If it is known that no cache operations are needed for this instance
     *  set this flag to FALSE.  If {@link #sharedAddr} lies within a shared
     *  region and the cache enabled setting for the region is FALSE,
     *  then the value specified here will be overriden to FALSE.
     */
    config Bool cacheEnabled = true;

    /*!
     *  ======== cacheLineSize ========
     *  The cache line size of the shared memory
     *
     *  This value should be configured
     */
    config SizeT cacheLineSize = 128;

    /*!
     *  ======== remoteProcId ========
     *  The MultiProc ID corresponding to the remote processor
     *
     *  This parameter must be set for every device.  The
     *  {@link ti.sdo.utils.MultiProc#getId} call can be used to obtain
     *  a MultiProc id given the remote processor's name.
     */
    config UInt16 remoteProcId = MultiProc.INVALIDID;

    /*!
     *  ======== intVectorId ========
     *  Interrupt vector ID to be used by the driver.
     *
     *  This parameter is only used by C64x+ targets
     */
    config UInt intVectorId = ~1u;

    /*!
     *  ======== localIntId ========
     *  Local interrupt ID for interrupt line
     *
     *  For devices that support multiple inter-processor interrupt lines, this
     *  configuration parameter allows selecting a specific line to use for
     *  receiving an interrupt.  The value specified here corresponds to the
     *  incoming interrupt line on the local processor.
     *
     *  If this configuration is not set, a default interrupt id is
     *  typically chosen.
     */
    config UInt localIntId = -1u;

    /*!
     *  ======== remoteIntId ========
     *  Remote interrupt ID for interrupt line
     *
     *  For devices that support multiple inter-processor interrupt lines, this
     *  configuration parameter allows selecting a specific line to use for
     *  receiving an interrupt.  The value specified here corresponds to the
     *  incoming interrupt line on the remote processor.
     *
     *  If this configuration is not set, a default interrupt id is
     *  typically chosen.
     */
    config UInt remoteIntId = -1u;

internal:

    /*! Flag an event up/down in shared memory */
    const UInt16 DOWN = 0;
    const UInt16 UP   = 1;

    /*! Initialization stamp */
    const UInt32 INIT_STAMP = 0xA9C8B7D6;

    /*!
     *  Plugs the interrupt and executes the callback functions according
     *  to event priority
     */
    Void isr(UArg arg);

    /*!
     *  Used to flag a remote event and determine if a local event has been
     *  flagged. This struct is placed in shared memory.
     */
    struct EventEntry {
        volatile Bits32 flag;
        volatile Bits32 payload;
        volatile Bits32 reserved;
        /* Padding if necessary */
    }

    /*!
     *  NotifyDriverShm state for a single processor in shared memory.
     *  Only the processor that owns this memory may write to it.
     *  However, the contents may be read by both processors.
     *
     *  Two of these structs are place at the base of shared memory. Slots
     *  [0] and [1] are respectively assigned to the processors with the
     *  lower and higher MultiProc ids.
     *
     *  Constraints: sizeof(NotifyDriverShm_ProcCtrl) must be a power of two
     *               and must be greater than sizeof(NotifyDriverShm_EventEntry)
     */
    struct ProcCtrl {
        volatile Bits32 recvInitStatus;   /* Whether ready to receive events  */
        volatile Bits32 sendInitStatus;   /* Whether ready to send events     */
        volatile Bits32 eventRegMask;     /* Event Registered mask            */
        volatile Bits32 eventEnableMask;  /* Event Enabled mask               */
    }

    struct Instance_State {
        ProcCtrl         *selfProcCtrl;    /* Control struct for local proc   */
        ProcCtrl         *otherProcCtrl;   /* Control struct for remote proc  */
        EventEntry       *selfEventChart;  /* flags, payload (local)          */
        EventEntry       *otherEventChart; /* flags, payload (remote)         */
        Notify.Handle    notifyHandle;     /* Handle to front-end object      */
        UInt32           regChart[];       /* Locally track registered events */
        UInt             selfId;           /* Which procCtrl to use           */
        UInt             otherId;          /* Which procCtrl to use           */
        IInterrupt.IntInfo intInfo;        /* Intr info passed to Interr mod  */
        UInt16           remoteProcId;     /* Remote MultiProc id             */
        UInt             nesting;          /* For disable/restore nesting     */
        Bool             cacheEnabled;     /* Whether to perform cache calls  */
        SizeT            eventEntrySize;   /* Spacing between event entries   */
    }
}
