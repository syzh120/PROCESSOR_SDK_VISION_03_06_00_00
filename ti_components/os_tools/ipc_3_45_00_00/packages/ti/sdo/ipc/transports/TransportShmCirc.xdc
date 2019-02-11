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
 *  ======== TransportShmCirc.xdc ================
 */

import ti.sdo.utils.MultiProc;
import ti.sdo.ipc.Ipc;
import ti.sysbios.knl.Swi;

import xdc.rov.ViewInfo;

/*!
 *  ======== TransportShmCirc ========
 *  Transport for MessageQ that uses a circular buffer to queue messages
 *
 *  This is a {@link ti.sdo.ipc.MessageQ} transport that utilizes shared
 *  memory for passing messages between multiple processors.
 *
 *  The transport implements a queue using a circular buffer in the manner
 *  indicated by the following diagram.
 *
 *  @p(code)
 *
 *  NOTE: Processors '0' and '1' correspond to the processors with lower and
 *        higher MultiProc ids, respectively
 *
 * sharedAddr -> --------------------------- bytes
 *               |  entry0  (0) [Put]      | 4
 *               |  entry1  (0)            | 4
 *               |  ...                    |
 *               |  entryN  (0)            | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  putWriteIndex (0)      | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  putReadIndex (0)       | 4
 *               |  [align to cache size]  |
 *               |-------------------------|
 *               |  entry0  (1) [Get]      | 4
 *               |  entry1  (1)            | 4
 *               |  ...                    |
 *               |  entryN  (1)            | 4
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
@InstanceInitError

module TransportShmCirc inherits ti.sdo.ipc.interfaces.IMessageQTransport
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String      remoteProcName;
        Bool        cacheEnabled;
    }

    /*! @_nodoc */
    metaonly struct EventDataView {
        UInt        index;
        String      buffer;
        Ptr         addr;
        Ptr         message;
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
     *  @_nodoc
     *  Determines whether the put() call unconditionally does a Cache_wbInv of
     *  the message before sending a notification to the remote core.
     *  The default value of 'true' allows us to skip the additional step of
     *  checking whether cache is enabled for the message.
     *
     *  This should be set to 'false' when it is optimal to perform this
     *  check.  This may be OPTIMAL when sending a message that is allocated
     *  from a shared region whose cacheFlag is 'false' and when the write-back
     *  cache operation is expensive.
     */
    config Bool alwaysWriteBackMsg = true;

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
     *  ======== notifyEventId ========
     *  Notify event ID for transport.
     */
    config UInt16 notifyEventId = 2;

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

    /*! @_nodoc
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

internal:

    /*! The max index set to (numMsgs - 1) */
    config UInt maxIndex;

    /*!
     *  The modulo index value. Set to (numMsgs / 4).
     *  Used in the isr for doing cache_wb of readIndex.
     */
    config UInt modIndex;

    /*!
     *  ======== swiFxn ========
     */
    Void swiFxn(UArg arg);

    /*!
     *  ======== notifyFxn ========
     */
    Void notifyFxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg,
                   UInt32 payload);

    /*! Instance state structure */
    struct Instance_State {
        Ptr              *putBuffer;     /* buffer used to put events        */
        Bits32           *putReadIndex;  /* ptr to readIndex for put buffer  */
        Bits32           *putWriteIndex; /* ptr to writeIndex for put buffer */
        Ptr              *getBuffer;     /* buffer used to get events        */
        Bits32           *getReadIndex;  /* ptr to readIndex for get buffer  */
        Bits32           *getWriteIndex; /* ptr to writeIndex for put buffer */
        SizeT            opCacheSize;    /* optimized cache size for wb/inv  */
        UInt16           regionId;       /* the shared region id             */
        UInt16           remoteProcId;   /* dst proc id                      */
        Bool             cacheEnabled;   /* set by param or SharedRegion     */
        UInt16           priority;       /* priority to register             */
        Swi.Object       swiObj;         /* Each instance has a swi          */
        Ipc.ObjType      objType;        /* Static/Dynamic? open/creator?    */
    }
}
