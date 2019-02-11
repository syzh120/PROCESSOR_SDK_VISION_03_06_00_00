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
 *  ======== NotifyDriverCirc.xdc ================
 */

import ti.sdo.utils.MultiProc;
import ti.sdo.ipc.interfaces.INotifyDriver;
import ti.sdo.ipc.notifyDrivers.IInterrupt;
import ti.sdo.ipc.Notify;

import xdc.rov.ViewInfo;

import xdc.runtime.Assert;

/*!
 *  ======== NotifyDriverCirc ========
 *  A shared memory driver using circular buffer for the Notify Module.
 *
 *  This is a {@link ti.sdo.ipc.Notify} driver that utilizes shared memory
 *  and inter-processor hardware interrupts for notification between cores.
 *  This driver supports caching.
 *
 *  This driver is designed to work with a variety of devices, each with
 *  distinct interrupt mechanisms.  Therefore, this module needs to be plugged
 *  with an appropriate module that implements the {@link IInterrupt} interface
 *  for a given device.
 *
 *  The Notify_[enable/disable]Event APIs are not supported by this driver.
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
 *               |  eventEntry0  (0)       | 8
 *               |  eventEntry1  (0)       | 8
 *               |  ...                    |
 *               |  eventEntry15 (0)       | 8
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  eventEntry16 (0)       | 8
 *               |  eventEntry17 (0)       | 8
 *               |  ...                    |
 *               |  eventEntry31 (0)       | 8
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  putWriteIndex (0)      | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  putReadIndex (0)       | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  eventEntry0  (1)       | 8
 *               |  eventEntry1  (1)       | 8
 *               |  ...                    |
 *               |  eventEntry15 (1)       | 8
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  eventEntry16 (1)       | 8
 *               |  eventEntry17 (1)       | 8
 *               |  ...                    |
 *               |  eventEntry31 (1)       | 8
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  getWriteIndex (1)      | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  getReadIndex (1)       | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *
 *
 *  Legend:
 *  (0), (1) : Memory that belongs to the proc with lower and higher
 *             MultiProc.id, respectively
 *   |----|  : Cache line boundary
 *
 *  @p
 */

@InstanceFinalize

module NotifyDriverCirc inherits ti.sdo.ipc.interfaces.INotifyDriver
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String      remoteProcName;
        Bool        cacheEnabled;
        UInt        bufSize;
        UInt        spinCount;
        UInt        maxSpinWait;
    }

    /*! @_nodoc */
    metaonly struct EventDataView {
        UInt        index;
        String      buffer;
        Ptr         addr;
        UInt        eventId;
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

    /*!
     *  Assert raised when trying to use Notify_[enable/disable]Event with
     *  NotifyDriverCirc
     */
    config Assert.Id A_notSupported =
        {msg: "A_notSupported: [enable/disable]Event not supported by NotifyDriverCirc"};


    /*! @_nodoc
     *  IInterrupt proxy that handles interrupts between multiple CPU cores
     */
    proxy InterruptProxy inherits IInterrupt;

    /*!
     *  ======== enableStats ========
     *  Enable statistics for sending an event
     *
     *  If this parameter is to 'TRUE' and 'waitClear' is also set to
     *  TRUE when calling (@link #sendEvent(), then the module keeps
     *  track of the number of times the processor spins waiting for
     *  an empty slot and the max amount of time it waits.
     */
    config Bool enableStats = false;

    /*!
     *  ======== numMsgs ========
     *  The number of messages or slots in the circular buffer
     *
     *  This is use to determine the size of the put and get buffers.
     *  Each eventEntry is two 32bits wide, therefore the total size
     *  of each circular buffer is [numMsgs * sizeof(eventEntry)].
     *  The total size of each buffer must be a multiple of the
     *  the cache line size. For example, if the cacheLineSize = 128
     *  then numMsgs could be 16, 32, etc...
     */
    config UInt numMsgs = 32;

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
     *  MultiProc_getId call can be used to obtain
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

    /*! The max index set to (numMsgs - 1) */
    config UInt maxIndex;

    /*!
     *  The modulo index value. Set to (numMsgs / 4).
     *  Used in the isr for doing cache_wb of readIndex.
     */
    config UInt modIndex;

    /*!
     *  Plugs the interrupt and executes the callback functions according
     *  to event priority
     */
    Void isr(UArg arg);

    /*!
     *  Structure for each event. This struct is placed in shared memory.
     */
    struct EventEntry {
        volatile Bits32 eventid;
        volatile Bits32 payload;
    }

    /*! Instance state structure */
    struct Instance_State {
        EventEntry       *putBuffer;     /* buffer used to put events        */
        Bits32           *putReadIndex;  /* ptr to readIndex for put buffer  */
        Bits32           *putWriteIndex; /* ptr to writeIndex for put buffer */
        EventEntry       *getBuffer;     /* buffer used to get events        */
        Bits32           *getReadIndex;  /* ptr to readIndex for get buffer  */
        Bits32           *getWriteIndex; /* ptr to writeIndex for put buffer */
        Bits32           evtRegMask;     /* local event register mask        */
        SizeT            opCacheSize;    /* optimized cache size for wb/inv  */
        UInt32           spinCount;      /* number of times sender waits     */
        UInt32           spinWaitTime;   /* largest wait time for sender     */
        Notify.Handle    notifyHandle;   /* Handle to front-end object       */
        IInterrupt.IntInfo intInfo;      /* Intr info passed to Interr mod   */
        UInt16           remoteProcId;   /* Remote MultiProc id              */
        Bool             cacheEnabled;   /* set by param or SharedRegion     */
    }
}
