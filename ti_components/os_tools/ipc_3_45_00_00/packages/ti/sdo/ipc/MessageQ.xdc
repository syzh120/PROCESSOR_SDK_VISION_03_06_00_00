/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== MessageQ.xdc ========
 *
 */

package ti.sdo.ipc;

import xdc.runtime.IHeap;
import xdc.runtime.Assert;
import xdc.runtime.Error;
import xdc.runtime.Diags;
import xdc.runtime.Log;
import xdc.runtime.IGateProvider;
import xdc.runtime.knl.ISync;

import ti.sysbios.syncs.SyncSem;

import ti.sdo.ipc.interfaces.ITransport;
import ti.sdo.ipc.interfaces.IMessageQTransport;
import ti.sdo.utils.NameServer;
import ti.sdo.utils.List;

import xdc.rov.ViewInfo;

/*!
 *  ======== MessageQ ========
 *  Message-passing with queuing
 *
 *  The MessageQ module supports the structured sending and receiving of
 *  variable length messages. This module can be used for homogeneous
 *  (DSP to DSP)  or heterogeneous (Arm to DSP) multi-processor messaging.
 *
 *  MessageQ provides more sophisticated messaging than other modules. It is
 *  typically used for complex situations such as multi-processor messaging.
 *
 *  The following are key features of the MessageQ module:
 *  @p(blist)
 *  -Writers and readers can be relocated to another processor with no
 *   runtime code changes.
 *  -Timeouts are allowed when receiving messages.
 *  -Readers can determine the writer and reply back.
 *  -Receiving a message is deterministic when the timeout is zero.
 *  -Messages can reside on any message queue.
 *  -Supports zero-copy transfers.
 *  -Can send and receive from any type of thread.
 *  -Notification mechanism is specified by application.
 *  -Allows QoS (quality of service) on message buffer pools. For example,
 *   using specific buffer pools for specific message queues.
 *  @p
 *
 *  Messages are sent and received by being placed on and removed from a
 *  message queue. A reader is a thread that gets (reads) messages from a
 *  message queue. A writer is a thread that puts (writes) a message to a
 *  message queue. Each message queue has one reader and can have many writers.
 *  A thread may read from or write to multiple message queues.
 *
 *  Conceptually, the reader thread owns a message queue. The reader thread
 *  creates a message queue. The writer threads open a created message queue
 *  to get access to them.
 *
 *  Message queues are identified by a system-wide unique name. Internally,
 *  MessageQ uses the {@link ti.sdo.utils.NameServer} module for managing
 *  these names. The names are used for opening a message queue.
 *
 *  Messages must be allocated from the MessageQ module. Once a message is
 *  allocated, it can be sent to any message queue. Once a message is sent, the
 *  writer loses ownership of the message and should not attempt to modify the
 *  message. Once the reader receives the message, it owns the message. It
 *  may either free the message or re-use the message.
 *
 *  Messages in a message queue can be of variable length. The only
 *  requirement is that the first field in the definition of a message must be a
 *  {@link #MsgHeader} structure. For example:
 *  @p(code)
 *  typedef struct MyMsg {
 *      MessageQ_MsgHeader header;
 *      ...
 *  } MyMsg;
 *  @p
 *
 *  The MessageQ API uses the MessageQ_MsgHeader internally. Your application
 *  should not modify or directly access the fields in the MessageQ_MsgHeader.
 *
 *  All messages sent via the MessageQ module must be allocated from a
 *  {@link xdc.runtime.IHeap} implementation. The heap can also be used for
 *  other memory allocation not related to MessageQ.
 *
 *  An application can use multiple heaps. The purpose of having multiple
 *  heaps is to allow an application to regulate its message usage. For
 *  example, an application can allocate critical messages from one heap of fast
 *  on-chip memory and non-critical messages from another heap of slower
 *  external memory.
 *
 *  The {@link #registerHeap} and {@link #registerHeapMeta} are APIs used to
 *  assign a MessageQ heapId to a heap. When allocating a message, the heapId
 *  is used, not the heap handle. This heapId is actually placed into the
 *  message (part of the {@link #MsgHeader}). Care must be taken when assigning
 *  heapIds. Refer to the {@link #registerHeap} and {@link #registerHeapMeta}
 *  descriptions for more details.
 *
 *  MessageQ also supports the usage of messages that are not allocated via the
 *  {@link #alloc} function. Please refer to the {@link #staticMsgInit}
 *  function description for more details.
 *
 *  MessageQ supports reads/writes of different thread models. This is
 *  accomplished by having the creator of the message queue specify a
 *  {@link xdc.runtime.knl.ISync#Object} via the {@link #synchronizer}
 *  configuration parameter. The {@link xdc.runtime.knl.ISync#signal}
 *  portion of the ISync instance is called whenever the {@link #put}
 *  is called. The {@link xdc.runtime.knl.ISync#wait} portion is
 *  called in the {@link #get} if and only if there are no messages.
 *
 *  Since ISyncs are binary, the reader must drain the message queue of all
 *  messages before waiting for another signal. For example, if the reader
 *  was a SYSBIOS Swi, the {@link xdc.runtime.knl.ISync} instance
 *  could be a SyncSwi. If a {@link #put} was called, the Swi_post() would
 *  be called. The Swi would run and it must call {@link #get} until no
 *  messages are returned.
 *
 *  In a multiple processor system, MessageQ communicates to other
 *  processors via {@link ti.sdo.ipc.interfaces.IMessageQTransport} instances.
 *  MessageQ supports a high priority and a normal priority transport between
 *  any two processors. The IMessageQTransport instances are created via the
 *  {@link #SetupTransportProxy}. The instances are responsible for
 *  registering themselves with MessageQ. This is accomplished via the
 *  {@link #registerTransport} function.
 *
 *  @a(Note)
 *  This modules reflects upon the {@link ti.sdo.utils.MultiProc#procAddrMode}
 *  configuration parameter. Some internal data structure allocations are
 *  optimized for the given processor address mode. For example, when using
 *  {@link ti.sdo.utils.MultiProc#ProcAddrMode_Global}, a message can be
 *  addressed to any processor using only the destination queueId. However,
 *  when using {@link ti.sdo.utils.MultiProc#ProcAddrMode_Cluster}, only
 *  the processors within your cluster can be addressed using only the
 *  destination queueId. For processors outside the cluster, you must also
 *  specify the Transport ID.
 */

@ModuleStartup
@InstanceInitError
@InstanceFinalize

module MessageQ
{
    /*!
     *  ======== QueuesView ========
     *  @_nodoc
     */
    metaonly struct QueuesView {
        String  name;
        UInt    queueId;
        Bool    reserved;
    }

    /*!
     *  ======== MessagesView ========
     *  @_nodoc
     */
    metaonly struct MessagesView {
        Int          seqNum;
        Int          msgSize;
        String       priority;
        String       srcProc;
        String       replyProc;
        String       replyId;
        Int          msgId;
        String       heap;
        Bool         traceEnabled;
        Int          version;
    }

    /*!
     *  ======== ModuleView ========
     *  @_nodoc
     */
    metaonly struct ModuleView {
        String               heaps[];
        String               gate;
        UInt16               nextSeqNum;
        String               freeHookFxn[];
    }

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Queues',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitQueues',
                        structName: 'QueuesView'
                    }
                ],
                ['Messages',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitMessages',
                        structName: 'MessagesView'
                    }
                ],
                ['Module',
                    {
                        type: xdc.rov.ViewInfo.MODULE,
                        viewInitFxn: 'viewInitModule',
                        structName: 'ModuleView'
                    }
                ]
            ]
        });

    /*!
     *  ======== LM_setTrace ========
     *  Logged when setting the trace flag on a message
     *
     *  This is logged when tracing on a message is set via
     *  {@link #setMsgTrace}.
     */
    config Log.Event LM_setTrace = {
        mask: Diags.USER1,
        msg: "LM_setTrace: Message 0x%x (seqNum = %d, srcProc = %d) traceFlag = %d"
    };

    /*!
     *  ======== LM_alloc ========
     *  Logged when allocating a message
     *
     *  When the {@link #traceFlag} is true, all message allocations
     *  are logged.
     */
    config Log.Event LM_alloc = {
        mask: Diags.USER1,
        msg: "LM_alloc: Message 0x%x (seqNum = %d, srcProc = %d) was allocated"
    };

    /*!
     *  ======== LM_staticMsgInit ========
     *  Logged when statically initializing a message
     *
     *  When the {@link #traceFlag} is true, all messages that
     *  are statically initialized via {@link #staticMsgInit} are logged.
     */
    config Log.Event LM_staticMsgInit = {
        mask: Diags.USER1,
        msg: "LM_staticMsgInit: Message 0x%x (seqNum = %d, srcProc = %d) was set in MessageQ_staticMsgInit"
    };

    /*!
     *  ======== LM_free ========
     *  Logged when freeing a message
     *
     *  When the {@link #traceFlag} is true, all freeing of messages
     *  are logged. If an individual message's tracing was enabled
     *  via {@link #setMsgTrace}, the MessageQ_free is also logged.
     */
    config Log.Event LM_free = {
        mask: Diags.USER1,
        msg: "LM_free: Message 0x%x (seqNum = %d, srcProc = %d) was freed"
    };

    /*!
     *  ======== LM_putLocal ========
     *  Logged when a message is placed onto a local queue
     *
     *  When the {@link #traceFlag} is true, all putting of messages
     *  are logged. If an individual message's tracing was enabled
     *  via {@link #setMsgTrace}, the MessageQ_put is also logged.
     */
    config Log.Event LM_putLocal = {
        mask: Diags.USER1,
        msg: "LM_putLocal: Message 0x%x (seqNum = %d, srcProc = %d) was placed onto queue 0x%x"
    };

    /*!
     *  ======== LM_putRemote ========
     *  Logged when a message is given to a transport
     *
     *  When the {@link #traceFlag} is true, all putting of messages
     *  to a transport are logged. If an individual message's tracing
     *  was enabled  via {@link #setMsgTrace}, the MessageQ_put is
     *  also logged.
     */
    config Log.Event LM_putRemote = {
        mask: Diags.USER1,
        msg: "LM_putRemote: Message 0x%x (seqNum = %d, srcProc = %d) was given to processor %d transport"
    };

    /*!
     *  ======== LM_rcvByTransport ========
     *  Logged when a transport receives an incoming message
     *
     *  When the {@link #traceFlag} is true, all incoming messages
     *  are logged. If an individual message's tracing
     *  was enabled  via {@link #setMsgTrace}, the receiving of a message is
     *  also logged.
     */
    config Log.Event LM_rcvByTransport = {
        mask: Diags.USER1,
        msg: "LM_rcvByTransport: Message 0x%x (seqNum = %d, srcProc = %d) was received"
    };

    /*!
     *  ======== LM_get ========
     *  Logged when a message is received off the queue
     *
     *  When the {@link #traceFlag} is true, all getting of messages
     *  are logged. If an individual message's tracing
     *  was enabled  via {@link #setMsgTrace}, the MessageQ_get is
     *  also logged.
     */
    config Log.Event LM_get = {
        mask: Diags.USER1,
        msg: "LM_get: Message 0x%x (seqNum = %d, srcProc = %d) was received by queue 0x%x"
    };

    /*!
     *  ======== FreeHookFxn ========
     *  Function prototype for the MessageQ_free callback
     *
     *  @param(Bits16)  heapId of message that was freed
     *  @param(Bits16)  msgId of message that was freed
     */
    typedef Void (*FreeHookFxn)(Bits16, Bits16);

    /*!
     *  ======== PutHookFxn ========
     *  Function prototype for the MessageQ_put callback
     *
     *  @param(Bits32)  queueId of the destination message queue
     *  @param(Ptr)     pointer to a message header structure
     */
    typedef Void (*PutHookFxn)(Bits32, Ptr);

    /*! MessageQ ID */
    typedef UInt32 QueueId;

    /*!
     *  ======== SetupTransportProxy ========
     *  MessageQ transport setup proxy
     */
    proxy SetupTransportProxy inherits ti.sdo.ipc.interfaces.ITransportSetup;

    /*!
     *  Message priority values. These must match the values defined in
     *  ti/ipc/MessageQ.h but are needed here for ROV.
     */
    const UInt NORMALPRI   = 0;
    const UInt HIGHPRI     = 1;
    const UInt RESERVEDPRI = 2;
    const UInt URGENTPRI   = 3;

    /*!
     *  Denotes any queueId is acceptable
     *
     *  This constant is the default for the {@link #queueId} parameter.
     *  This value must match ti/ipc/MessageQ.h but is needed to initialize
     *  queueId.
     */
    const Bits16 ANY = ~(0);

    /*!
     *  Assert raised when calling API with wrong handle
     *
     *  Some APIs can only be called with an opened handle (e.g.
     *  {@link #close}. Some can only be called with a created handle
     *  (e.g. {@link #get}).
     */
    config Assert.Id A_invalidContext  = {
        msg: "A_invalidContext: Cannot call with an open/create handle"
    };

    /*!
     *  Assert raised when attempting to free a static message
     */
    config Assert.Id A_cannotFreeStaticMsg  = {
        msg: "A_cannotFreeStaticMsg: Cannot call MessageQ_free with static msg"
    };

    /*!
     *  Assert raised when an invalid message is supplied
     */
    config Assert.Id A_invalidMsg  = {
        msg: "A_invalidMsg: Invalid message"
    };

    /*!
     *  Assert raised when an invalid queueId is supplied
     */
    config Assert.Id A_invalidQueueId  = {
        msg: "A_invalidQueueId: Invalid queueId is used"
    };

    /*!
     *  Assert raised when using an invalid heapId
     */
    config Assert.Id A_heapIdInvalid  = {
        msg: "A_heapIdInvalid: heapId is invalid"
    };

    /*!
     *  Assert raised when using an invalid procId
     */
    config Assert.Id A_procIdInvalid  = {
        msg: "A_procIdInvalid: procId is invalid"
    };

    /*!
     *  Assert raised for an invalid MessageQ object
     */
    config Assert.Id A_invalidObj  = {
        msg: "A_invalidObj: an invalid obj is used"
    };

    /*!
     *  Assert raised for an invalid parameter
     */
    config Assert.Id A_invalidParam  = {
        msg: "A_invalidParam: an invalid parameter was passed in"
    };

    /*!
     *  Assert raised when attempting to send a message to a core
     *  where a transport has not been registered.
     */
    config Assert.Id A_unregisteredTransport  = {
        msg: "A_unregisteredTransport: transport is not registered"
    };

    /*!
     *  Assert raised when attempting to unblock a remote MessageQ or one that
     *  has been configured with a non-blocking synchronizer
     */
    config Assert.Id A_invalidUnblock  = {
        msg: "A_invalidUnblock: Trying to unblock a remote MessageQ or a queue with non-blocking synchronizer"
    };

    /*!
     *  Error raised if all the message queue objects are taken
     */
    config Error.Id E_maxReached  = {
        msg: "E_maxReached: All objects in use. MessageQ.maxRuntimeEntries is %d"
    };

    /*!
     *  Error raised when heapId has not been registered
     */
    config Error.Id E_unregisterHeapId  = {
        msg: "E_unregisterHeapId: Heap id %d not registered"
    };

    /*!
     *  Error raised in a create call when a name fails to be added
     *  to the NameServer table.  This can be because the name already
     *  exists, the table has reached its max length, or out of memory.
     */
    config Error.Id E_nameFailed  = {
        msg: "E_nameFailed: '%s' name failed to be added to NameServer"
    };

    /*!
     *  Error raised if the requested queueIndex is not available
     */
    config Error.Id E_indexNotAvailable  = {
        msg: "E_indexNotAvailable: queueIndex %d not available"
    };

    /*!
     *  Trace setting
     *
     *  This flag allows the configuration of the default module trace
     *  settings.
     */
    config Bool traceFlag = false;

    /*!
     *  Number of heapIds in the system
     *
     *  This allows MessageQ to pre-allocate the heaps table.
     *  The heaps table is used when registering heaps.
     *
     *  There is no default heap, so unless the system is only using
     *  {@link #staticMsgInit}, the application must register a heap.
     */
    config UInt16 numHeaps = 8;

    /*!
     *  Maximum number of MessageQs that can be dynamically created
     */
    config UInt maxRuntimeEntries = NameServer.ALLOWGROWTH;

    /*!
     *  Number of reserved MessageQ indexes
     *
     *  An application can request the first N message queue indexes be
     *  reserved to be used by MessageQ_create2. MessageQ_create will
     *  not use these slots. The application can use any index less than
     *  the value of numReservedEntries for the queueIndex field in the
     *  MessageQ_Params2 structure.
     *
     *  numReservedEntries must be equal or less than
     *  {@link #maxRuntimeEntries}.
     */
    config UInt numReservedEntries = 0;

    /*!
     *  Gate used to make the name table thread safe
     *
     *  This gate is used when accessing the name table during
     *  a {@link #create}, {@link #delete}, and {@link #open}.
     *
     *  This gate is also used to protect MessageQ when growing
     *  internal tables in the {@link #create}.
     *
     *  The table is in local memory, not shared memory. So a
     *  single processor gate will work.
     *
     *  The default will be {@link xdc.runtime.knl.GateThread}
     *  instance.
     */
    config IGateProvider.Handle nameTableGate = null;

    /*!
     *  Maximum length for Message queue names
     */
    config UInt maxNameLen = 32;

    /*!
     *  Section name is used to place the names table
     */
    metaonly config String tableSection = null;

    /*!
     *  ======== freeHookFxn ========
     *  Free function in MessageQ_free after message was freed back to the heap
     */
    config FreeHookFxn freeHookFxn = null;

    /*!
     *  ======== putHookFxn ========
     *  Put function hook
     */
    config PutHookFxn putHookFxn = null;

    /*!
     *  ======== registerHeapMeta ========
     *  Statically register a heap with MessageQ
     *
     *  Build error if heapId is in use.
     *
     *  @param(heap)        Heap to register
     *  @param(heapId)      heapId associated with the heap
     */
    metaonly Void registerHeapMeta(IHeap.Handle heap, UInt16 heapId);

     /*!
     *  ======== registerTransportMeta ========
     *  Statically register a transport with MessageQ
     *
     *  Build error if remote processor already has a transport
     *  registered.
     *
     *  @param(transport)   transport to register
     *  @param(procId)      procId that transport communicaties with
     *  @param(priority)    priority of transport
     */
     metaonly Void registerTransportMeta(IMessageQTransport.Handle transport,
             UInt16 procId, UInt priority);

    /*!
     *  ======== registerTransport ========
     *  Register a transport with MessageQ
     *
     *  This API is called by the transport when it is created.
     *
     *  @param(transport)   transport to register
     *  @param(procId)      MultiProc id that transport communicates with
     *  @param(priority)    priority of transport
     *
     *  @b(returns)         Whether the register was successful.
     */
    Bool registerTransport(IMessageQTransport.Handle transport, UInt16 procId,
        UInt priority);

    /*!
     *  ======== unregisterTransport ========
     *  Unregister a transport with MessageQ
     *
     *  @param(procId)      unregister transport that communicates with
     *                      this remote processor
     *  @param(priority)    priority of transport
     */
    Void unregisterTransport(UInt16 procId, UInt priority);

instance:

    /*!
     *  ISync handle used to signal IO completion
     *
     *  The ISync instance is used in the {@link #get} and {@link #put}.
     *  The {@link xdc.runtime.knl.ISync#signal} is called as part
     *  of the {@link #put} call.  The {@link xdc.runtime.knl.ISync#wait} is
     *  called in the {@link #get} if there are no messages present.
     */
    config ISync.Handle synchronizer = null;

    /*!
     *  Requested MessageQ_QueueIndex
     *
     *  This parameter allows an application to specify the queueIndex to
     *  be used for a message queue. To use this functionality, the
     *  MessageQ.numReservedEntries static configuration parameter must be
     *  set to a specific value.
     *
     *  The default is {@link #ANY}. This means do that you are not asking for
     *  an explicit index. MessageQ will find the first available one which is
     *  equal or greater than MessageQ.numReservedEntries.
     */
    config UInt16 queueIndex = ANY;

    /*! @_nodoc
     *  ======== create ========
     *  Create a message queue
     *
     *  @param(name)         Name of the message queue.
     */
    create(String name);

internal:
    /*
     *  The following describes the usage of the flag field
     *  ---------------------------------
     *  |V V V|T|  reserved   |t t t|P P|
     *  ---------------------------------
     *   F E D C B A 9 8 7 6 5 4 3 2 1 0
     *
     *  [15:13] V = version
     *  [12]    T = trace flag
     *  [11:5]  reserved
     *  [4:2]   t = transport Id, zero = default
     *  [1:0]   P = priority
     */

    /*! Mask to extract version setting */
    const UInt VERSIONMASK = 0xE000;

    /*! Version setting */
    const UInt HEADERVERSION = 0x2000;

    /*! Mask to extract Trace setting */
    const UInt TRACEMASK = 0x1000;

    /*! Shift for Trace setting */
    const UInt TRACESHIFT = 12;

    /*!
     *  Mask to extract priority setting.
     *  This is needed here for ROV but must match
     *  the value defined in ti/ipc/MessageQ.h
     */
    const UInt PRIORITYMASK = 0x3;

    /*! Mask to extract priority setting */
    const UInt TRANSPORTPRIORITYMASK = 0x1;

     /*! return code for Instance_init */
    const Int PROXY_FAILURE = 1;

    /*
     *  Used to denote a message that was initialized
     *  with the MessageQ_staticMsgInit function.
     */
    const UInt16 STATICMSG = 0xFFFF;

    /*! Required first field in every message */
    @Opaque struct MsgHeader {
        Bits32       reserved0;         /* reserved for List.elem->next */
        Bits32       reserved1;         /* reserved for List.elem->prev */
        Bits32       msgSize;           /* message size                 */
        Bits16       flags;             /* bitmask of different flags   */
        Bits16       msgId;             /* message id                   */
        Bits16       dstId;             /* destination queue id         */
        Bits16       dstProc;           /* destination processor id     */
        Bits16       replyId;           /* reply queue id               */
        Bits16       replyProc;         /* reply processor id           */
        Bits16       srcProc;           /* proc who initialized the msg */
        Bits16       heapId;            /* heap id                      */
        Bits16       seqNum;            /* sequence number              */
        Bits16       reserved;          /* reserved                     */
    };

    struct HeapEntry {
        IHeap.Handle  heap;
        UInt16        heapId;
    };

    struct TransportEntry {
        IMessageQTransport.Handle  transport;
        UInt16             procId;
    };

    enum TransportType {
        TransportType_IMessageQTransport,
        TransportType_INetworkTransport,
        TransportType_Invalid
    };

    struct RegisteredTransport {
        ITransport.Handle transport;
        TransportType type;
    };

    /*!
     *  ======== nameSrvPrms ========
     *  This Params object is used for temporary storage of the
     *  module wide parameters that are for setting the NameServer instance.
     */
    metaonly config NameServer.Params nameSrvPrms;

    /*!
     *  Statically registered heaps
     *
     *  This configuration parameter allows the static registeration
     *  of heaps. The index of the array corresponds to the heapId.
     */
    metaonly config HeapEntry staticHeaps[];

    /*!
     *  Statically registered transports
     *
     *  This configuration parameter allows the static registeration
     *  of transports. The index of the array corresponds to the procId.
     */
    metaonly config TransportEntry staticTransports[];

    /*!
     *  Allows for the number of dynamically created message queues to grow.
     */
    UInt16 grow(Object *obj, Error.Block *eb);

    struct Instance_State {
        QueueId         queue;        /* Unique id                     */
        ISync.Handle    synchronizer; /* completion synchronizer       */
        List.Object     normalList;   /* Embedded List objects         */
        List.Object     highList;     /* Embedded List objects         */
        Ptr             nsKey;        /* unique NameServer key         */
        SyncSem.Handle  syncSemHandle;/* for use in finalize           */
        Bool            unblocked;    /* Whether MessageQ is unblocked */
    };

    struct Module_State {
        IMessageQTransport.Handle transports[length][2];
        Handle               queues[];
        IHeap.Handle         heaps[];
        IGateProvider.Handle gate;
        UInt16               numQueues;
        UInt16               numHeaps;
        NameServer.Handle    nameServer;
        FreeHookFxn          freeHookFxn;
        PutHookFxn           putHookFxn;
        Bool                 canFreeQueues;
        UInt16               seqNum;
        RegisteredTransport  regTrans[8];
    };
}
