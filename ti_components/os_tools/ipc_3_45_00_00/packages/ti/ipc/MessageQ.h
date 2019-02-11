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

/**
 *  @file       ti/ipc/MessageQ.h
 *
 *  @brief      MessageQ Manager
 *
 *  The MessageQ module supports the structured sending and receiving of
 *  variable length messages. This module can be used for homogeneous
 *  (e.g. DSP to DSP) or heterogeneous (e.g. ARM to DSP) multi-processor
 *  messaging.
 *
 *  MessageQ provides more sophisticated messaging than other modules. It is
 *  typically used for complex situations such as multi-processor messaging.
 *
 *  The following are key features of the MessageQ module:
 *  - Writers and readers can be relocated to another processor with no
 *    runtime code changes.
 *  - Timeouts are allowed when receiving messages.
 *  - Readers can determine the writer and reply back.
 *  - Receiving a message is deterministic when the timeout is zero.
 *  - Messages can reside on any message queue.
 *  - Supports zero-copy transfers.
 *  - Can send and receive from any type of thread.
 *  - Notification mechanism is specified by application.
 *  - Allows QoS (quality of service) on message buffer pools. For example,
 *    using specific buffer pools for specific message queues.
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
 *  MessageQ uses the NameServer module for managing
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
 *  #MessageQ_MsgHeader structure. For example:
 *  @code
 *  typedef struct MyMsg {
 *      MessageQ_MsgHeader header;
 *      ...
 *  } MyMsg;
 *  @endcode
 *
 *  The MessageQ API uses the MessageQ_MsgHeader internally. Your application
 *  should not modify or directly access the fields in the MessageQ_MsgHeader.
 *
 *  All messages sent via the MessageQ module must be allocated from a
 *  heap. The heap can also be used for other memory allocation not related to
 *  MessageQ.
 *
 *  An application can use multiple heaps. The purpose of having multiple
 *  heaps is to allow an application to regulate its message usage. For
 *  example, an application can allocate critical messages from one heap of fast
 *  on-chip memory and non-critical messages from another heap of slower
 *  external memory.
 *
 *  The MessageQ_registerHeap() API is used to
 *  assign a MessageQ heapId to a heap. When allocating a message, the heapId
 *  is used, not the heap handle. This heapId is actually placed into the
 *  message (part of the #MessageQ_MsgHeader). Care must be taken when
 *  assigning heapIds. Refer to the MessageQ_registerHeap() API description for
 *  more details.
 *
 *  MessageQ also supports the usage of messages that are not allocated via the
 *  MessageQ_alloc() function. Please refer to the MessageQ_staticMsgInit()
 *  function description for more details.
 *
 *  MessageQ supports reads/writes of different thread models. This is
 *  accomplished by having the creator of the message queue specify a
 *  synchronizer via the #MessageQ_Params.synchronizer
 *  configuration parameter. The synchronizer is signaled whenever the
 *  MessageQ_put() is called. The synchronizer waits if MessageQ_get() is called
 *  and there are no messages.
 *
 *  Since ISyncs are binary, the reader must drain the message queue of all
 *  messages before waiting for another signal. For example, if the reader
 *  was a SYS/BIOS Swi, the synchronizer instance could be a SyncSwi.
 *  If a MessageQ_put() was called, the Swi_post() would
 *  be called. The Swi would run and it must call MessageQ_get() until no
 *  messages are returned.
 *
 *  The MessageQ header should be included in an application as follows:
 *  @code
 *  #include <ti/ipc/MessageQ.h>
 *  @endcode
 */

#ifndef ti_ipc_MessageQ__include
#define ti_ipc_MessageQ__include

#include <ti/ipc/MultiProc.h>

#if defined (__cplusplus)
extern "C" {
#endif

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @brief  The resource is still in use
 */
#define MessageQ_S_BUSY                  (2)

/*!
 *  @brief  The module has been already setup
 */
#define MessageQ_S_ALREADYSETUP          (1)

/*!
 *  @brief  Operation is successful.
 */
#define MessageQ_S_SUCCESS               (0)

/*!
 *  @brief  Operation is not successful.
 */
#define MessageQ_E_FAIL                 (-1)

/*!
 *  @brief  There is an invalid argument.
 */
#define MessageQ_E_INVALIDARG           (-2)

/*!
 *  @brief  Operation resulted in memory failure.
 */
#define MessageQ_E_MEMORY               (-3)

/*!
 *  @brief  The specified entity already exists.
 */
#define MessageQ_E_ALREADYEXISTS        (-4)

/*!
 *  @brief  Unable to find the specified entity.
 */
#define MessageQ_E_NOTFOUND             (-5)

/*!
 *  @brief  Operation timed out.
 */
#define MessageQ_E_TIMEOUT              (-6)

/*!
 *  @brief  Module is not initialized.
 */
#define MessageQ_E_INVALIDSTATE         (-7)

/*!
 *  @brief  A failure occurred in an OS-specific call
 */
#define MessageQ_E_OSFAILURE            (-8)

/*!
 *  @brief  Specified resource is not available
 */
#define MessageQ_E_RESOURCE             (-9)

/*!
 *  @brief  Operation was interrupted. Please restart the operation
 */
#define MessageQ_E_RESTART              (-10)

/*!
 *  @brief  An invalid message was encountered
 */
#define MessageQ_E_INVALIDMSG           (-11)

/*!
 *  @brief  Not the owner
 */
#define MessageQ_E_NOTOWNER             (-12)

/*!
 *  @brief  Operation resulted in error
 */
#define MessageQ_E_REMOTEACTIVE         (-13)

/*!
 *  @brief  An invalid heap id was encountered
 */
#define MessageQ_E_INVALIDHEAPID        (-14)

/*!
 *  @brief  An invalid MultiProc id was encountered
 */
#define MessageQ_E_INVALIDPROCID        (-15)

/*!
 *  @brief  The max has been reached.
 */
#define MessageQ_E_MAXREACHED           (-16)

/*!
 *  @brief  Attempting to use an unregistered heap id.
 */
#define MessageQ_E_UNREGISTEREDHEAPID   (-17)

/*!
 *  @brief  Trying to free a statically initialized message
 */
#define MessageQ_E_CANNOTFREESTATICMSG  (-18)

/*!
 *  @brief  MessageQ was unblocked
 */
#define MessageQ_E_UNBLOCKED            (-19)

/*!
 *  @brief  MessageQ was shutdown
 */
#define MessageQ_E_SHUTDOWN             (-20)

/* =============================================================================
 *  Macros
 * =============================================================================
 */

/*!
 *  @brief      Used as the timeout value to specify wait forever
 */
#define MessageQ_FOREVER                (~(0))

/*!
 *  @brief      Invalid message id
 */
#define MessageQ_INVALIDMSGID           (0xffff)

/*!
 *  @brief      Invalid message queue
 */
#define MessageQ_INVALIDMESSAGEQ        (0xffff)

/*!
 *  @brief      Mask to extract priority setting
 */
#define MessageQ_PRIORITYMASK           (0x3)

/** @cond INTERNAL */
/*!
 *  @brief      Offset to avoid collision with reserved ports
 *
 *  A queue's port number is computed by adding this offset to the
 *  queue index. Use the port number to address the message or when
 *  binding a socket. Computing a port number with this offset avoids
 *  collisions with reserved port numbers which are typically in the
 *  same range as the queue indexes.
 */
#define MessageQ_PORTOFFSET             (0x80)
/** @endcond INTERNAL */

/*!
 *  @brief      Extract the destination queue ID from a message.
 *
 *  This function is typically used be a transport.
 *
 *  The destination address is written into the message header when
 *  calling MessageQ_put(). Therefore, you can only use this function
 *  to extract the destination queue ID after MessageQ_put() has been
 *  called on the given message. However, ownership rules dictate that
 *  you cannot dereference a message after calling MessageQ_put() (because
 *  you have transfered ownership to the transport).
 *
 *  After receiving a message by calling MessageQ_get(), you may safely
 *  use this function. Although there is little benefit from doing so.
 *
 *  When the message is given to the transport, the destination address
 *  has been written into the message header. In addition, the transport
 *  now has ownership of the message. So, it is appropriate for the transport
 *  to use this macro.
 *
 *  @param[in]  msg     Message of type #MessageQ_Msg
 *
 *  @retval  queueId    Destination message queue ID of type #MessageQ_QueueId
 */
#define MessageQ_getDstQueue(msg) \
        (((MessageQ_Msg)(msg))->dstId == \
        (MessageQ_QueueIndex)MessageQ_INVALIDMESSAGEQ) ? \
        (MessageQ_QueueId)MessageQ_INVALIDMESSAGEQ : \
        (((MessageQ_QueueId)((MessageQ_Msg)(msg))->dstProc << 16u) \
        | (((MessageQ_Msg)(msg))->dstId))


/*!
 *  @brief   Retrieves the message ID of a message.
 *
 *  This function retrieves the message ID from the message. The
 *  MessageQ_setMsgId() function is used to insert the message ID.
 *
 *  The message id is part of the #MessageQ_MsgHeader header and is in every
 *  MessageQ message. All message ids are initialized to #MessageQ_INVALIDMSGID
 *  in the MessageQ_alloc() and MessageQ_staticMsgInit() calls.
 *
 *  @param[in]  msg     Message of type #MessageQ_Msg
 *
 *  @retval     msgId   16-bit message ID from the message
 */
#define MessageQ_getMsgId(msg) (((MessageQ_Msg) (msg))->msgId)

/*!
 *  @brief   Returns the size of the specified message. This function is helpful
 *           when re-using a message.
 *
 *  @param[in]  msg     Message of type #MessageQ_Msg
 *
 *  @retval     size    Size of the message
 */
#define MessageQ_getMsgSize(msg) (((MessageQ_Msg) (msg))->msgSize)

/*!
 *  @brief   Gets the message priority of a message
 *
 *  @param[in]  msg     Message of type #MessageQ_Msg
 *
 *  @retval priority    Priority of the message
 */
#define MessageQ_getMsgPri(msg)        \
                 ((((MessageQ_Msg) (msg))->flags & MessageQ_PRIORITYMASK))

/*!
 *  @brief      Returns the MultiProc processor id on which the queue resides
 *
 *  Message queues reside on the processor that created them. This function
 *  allows the caller to determined on which processor the queue resides.
 *
 *  @param[in]  queueId      Unique #MessageQ_QueueId that identifies the queue
 *
 *  @retval     procId       The MultiProc id on which the queue resides
 */
#define MessageQ_getProcId(queueId)     \
                 ((UInt16)((queueId) >> 16))

/*!
 *  @brief   Extract the queue index from the given queue ID
 *
 *  When creating and opening queues, the queue index is embedded
 *  into the queue ID using an implementation dependent format. This
 *  function extracts the queue index from the queue ID.
 *
 *  For example, in the MessageQ_put() hook function, you might extract
 *  the queue index in order to set the transport ID.
 *
 *      @code
 *      Void msgqPutHook(MessageQ_QueueId queueId, MessageQ_Msg msg)
 *      {
 *          MessageQ_QueueIndex queueIndex;
 *          UInt tid;
 *
 *          queueIndex = MessageQ_getQueueIndex(queueId);
 *          ...
 *          MessageQ_setTransportId(msg, tid);
 *      }
 *      @endcode
 *
 *  This function performs no error checking. Using an invalid queue ID
 *  will result in undefined behavior.
 *
 *  @param[in]  queueId         Message queue ID of type #MessageQ_QueueId
 *
 *  @retval     queueIndex      The queue index of type #MessageQ_QueueIndex
 */
#define MessageQ_getQueueIndex(queueId) \
        (((MessageQ_QueueIndex)((MessageQ_QueueId)0xFFFF & (queueId))) \
        - MessageQ_PORTOFFSET)

/*!
 *  @brief   Retrieves the message queue ID from a message.
 *
 *  This function along with the MessageQ_setReplyQueue() function can  be used
 *  instead of the open function. The sender of a message can embed a messageQ
 *  into the message with the MessageQ_setReplyQueue() function. The receiver of
 *  the message can extract the message queue ID with this function.
 *
 *  This method is particularly useful in a client/server relationship where
 *  the server does not want to know who the clients are. The clients can embed
 *  their message queue into the message to the server and the server extracts
 *  it and uses it to reply.
 *
 *  @param[in]  msg     Message of type #MessageQ_Msg
 *
 *  @retval  queueId    Message queue ID of type #MessageQ_QueueId
 */
#define MessageQ_getReplyQueue(msg)           \
                (MessageQ_QueueId)((((MessageQ_Msg) (msg))->replyProc << 16u) \
                | ((MessageQ_Msg)(msg))->replyId)

/*!
 *  @brief   Return the transport Id for the given message
 *
 *  Extract the transport Id from the message header.
 *
 *  @param[in]   msg      message of type #MessageQ_Msg
 *  @retval      tid      transport Id
 */
#define MessageQ_getTransportId(msg) \
        ((((MessageQ_Msg)(msg))->flags & (0x7 << 2)) >> 2)

/*!
 *  @brief   Sets the message id in a message.
 *
 *  This function sets the message ID in the message. The MessageQ_getMsgId()
 *  function is used to retrieve the message ID.  The message id is part of the
 *  #MessageQ_MsgHeader header and is in every MessageQ message. All message ids
 *  are initialized to #MessageQ_INVALIDMSGID in the MessageQ_alloc() and
 *  MessageQ_staticMsgInit() calls.
 *
 *  @param[in]   msg    Message of type #MessageQ_Msg
 *  @param[in]   id     16-bit value
 */
#define MessageQ_setMsgId(msg, id) ((MessageQ_Msg) (msg))->msgId = (id)

/*!
 *  @brief   Sets the message priority of a message
 *
 *  @param[in]   msg      Message of type #MessageQ_Msg
 *  @param[in]   priority Priority of message to be set.
 */
#define MessageQ_setMsgPri(msg, priority) \
        ((MessageQ_Msg)(msg))->flags = \
        (((MessageQ_Msg)(msg))->flags & ~(MessageQ_PRIORITYMASK)) \
        | ((priority) & MessageQ_PRIORITYMASK)

/*!
 *  @brief   Set the transport Id for the given message
 *
 *  Set the transport Id in the flags field of the message header. When
 *  set to a non-zero value, the message will be given to the specified
 *  transport for delivery. The transport must be registered with MessageQ
 *  with the given Id.
 *
 *  There is no error checking on the transport Id.
 *
 *  @param[in]   msg      message of type #MessageQ_Msg
 *  @param[in]   tid      transport ID (1-7)
 */
#define MessageQ_setTransportId(msg, tid) \
        ((MessageQ_Msg)(msg))->flags = \
        ((((MessageQ_Msg)(msg))->flags & ~(0x7 << 2)) | ((tid) << 2))

/* =============================================================================
 *  Structures & Enums
 * =============================================================================
 */

/*!
 *  @brief  A 32-bit value that uniquely identifies a message queue
 */
typedef UInt32 MessageQ_QueueId;

/*!
 *  @brief  Local queue index
 */
typedef UInt16 MessageQ_QueueIndex;

/*!
 *  @brief  MessageQ_Handle type
 */
typedef struct MessageQ_Object *MessageQ_Handle;

/*!
 *  @brief  Structure defining parameters for MessageQ_create().
 */
typedef struct {
/** @cond INTERNAL */
    Int __version;
    /*  Used internally for tracking implementation evolution.
     *  For internal use only.
     */
/** @endcond INTERNAL */

    Void *synchronizer;
    /*!< Synchronizer instance used to signal IO completion
     *
     *  The synchronizer is used in MessageQ_put() and MessageQ_get().
     *  The synchronizer signal is called as part of MessageQ_put().
     *  The synchronizer waits in MessageQ_get() if there are no messages
     *  present.
     */

     MessageQ_QueueIndex queueIndex;
     /*!< Value used to specify the index in the MessageQ array
      *
      *  This parameter allows an application to specify a queueIndex to
      *  be used for a message queue. To use this functionality, the
      *  MessageQ.numReservedEntries static configuration parameter must be
      *  set to one more than the highest requested queueIndex. The
      *  MessageQ.numReservedEntries parameter reserves that number of
      *  message queue slots starting at 0 and proceeding to
      *  (MessageQ.numReservedEntries - 1).
      *
      *  The default is MessageQ_ANY, which means it is not taken from the
      *  reserved slots.
      */

} MessageQ_Params;

/** @cond INTERNAL */
/*  Date: 02 Dec 2014
 *
 *  Initial implementation of params structure which contains
 *  a version field. This allows for binary compatibility as
 *  the params structure is modified in the future.
 */
#define MessageQ_Params_VERSION_2       2
/** @endcond INTERNAL */

/** @cond INTERNAL */
/*!
 *  @brief      Defines the current params structure version
 */
#define MessageQ_Params_VERSION         MessageQ_Params_VERSION_2
/** @endcond INTERNAL */

/*!
 *  @brief  Structure defining parameters for MessageQ_create2().
 *
 *  MessageQ_Params2 is a superset of MessageQ_Params. It is used
 *  with MessageQ_create2().
 *
 *  @deprecated This type has been deprecated. It will be removed
 *  in a future release. Please use MessageQ_Params instead.
 */
typedef struct {
    Void *synchronizer;
    /*!< Synchronizer instance used to signal IO completion
     *
     *  The synchronizer is used in MessageQ_put() and MessageQ_get().
     *  The synchronizer signal is called as part of MessageQ_put().
     *  The synchronizer waits in MessageQ_get() if there are no messages
     *  present.
     */

     MessageQ_QueueIndex queueIndex;
     /*!< Value used to specify the index in the MessageQ array
      *
      *  This parameter allows an application to specify a queueIndex to
      *  be used for a message queue. To use this functionality, the
      *  MessageQ.numReservedEntries static configuration parameter must be
      *  set to one more than the highest requested queueIndex. The
      *  MessageQ.numReservedEntries parameter reserves that number of
      *  message queue slots starting at 0 and proceeding to
      *  (MessageQ.numReservedEntries - 1).
      *
      *  The default is MessageQ_ANY, which means it is not taken from the
      *  reserved slots.
      */

} MessageQ_Params2;

/*!
 *  @brief      Required first field in every message
 */
typedef struct {
    Bits32       reserved0;         /*!< reserved for List.elem->next       */
    Bits32       reserved1;         /*!< reserved for List.elem->prev       */
    Bits32       msgSize;           /*!< message size                       */
    Bits16       flags;             /*!< bitmask of different flags         */
    Bits16       msgId;             /*!< message id                         */
    Bits16       dstId;             /*!< destination queue id               */
    Bits16       dstProc;           /*!< destination processor id           */
    Bits16       replyId;           /*!< reply id                           */
    Bits16       replyProc;         /*!< reply processor                    */
    Bits16       srcProc;           /*!< source processor                   */
    Bits16       heapId;            /*!< heap id                            */
    Bits16       seqNum;            /*!< sequence number                    */
    Bits16       reserved;          /*!< reserved                           */
} MessageQ_MsgHeader;

/*!
 *  @brief  Typedef for ease of use
 */
typedef MessageQ_MsgHeader *MessageQ_Msg;

/*!
 *  @brief      Message priority
 */
typedef enum {
    MessageQ_NORMALPRI      = 0,    /*!< Normal Priority                  */
    MessageQ_HIGHPRI        = 1,    /*!< High Priority                    */
    MessageQ_RESERVEDPRI    = 2,    /*!< Reserved Priority                */
    MessageQ_URGENTPRI      = 3     /*!< Urgent Priority                  */
} MessageQ_Priority;

/*!
 *  @brief      Denotes any queueId is acceptable.
 *
 *  This constant is the default for the queueId in the MessageQ_Params
 *  structure.
 */
#define MessageQ_ANY (Bits16)~(0)

/*!
 *  @brief      Free hook prototype
 *
 *  @param[in]  heapId      heapId of message that was freed
 *  @param[in]  msgId       msgId of message that was freed
 */
typedef Void (*MessageQ_FreeHookFxn)(Bits16 heapId, Bits16 msgId);

/*!
 *  @brief      Put hook function definition
 *
 *  This function is invoked near the beginning of the MessageQ_put()
 *  function. It allows client code to augment the addressing of the
 *  given message before it is delivered.
 *
 *  @param[in]  queueId     destination message queue
 *  @param[in]  msg         message to be sent
 */
typedef Void (*MessageQ_PutHookFxn)(MessageQ_QueueId queueId, MessageQ_Msg msg);

#ifdef STD_H
#include <ti/ipc/interfaces/ITransport.h>
#include <ti/ipc/interfaces/IMessageQTransport.h>
#else
#include <ti/sdo/ipc/interfaces/ITransport.h>
#include <ti/sdo/ipc/interfaces/IMessageQTransport.h>
#endif

Bool MessageQ_registerTransport(IMessageQTransport_Handle handle,
                                UInt16 rprocId, UInt priority);
Void MessageQ_unregisterTransport(UInt16 rprocId, UInt priority);


/* =============================================================================
 *  MessageQ Module-wide Functions
 * =============================================================================
 */

/** @cond INTERNAL */
/* Returns the local handle associated with queueId. */
MessageQ_Handle MessageQ_getLocalHandle(MessageQ_QueueId queueId);
/** @endcond INTERNAL */


/** @cond INTERNAL */
Void MessageQ_Params_init__S(MessageQ_Params *params, Int version);
/** @endcond INTERNAL */

/*!
 *  @brief      Initialize MessageQ_Params
 *
 *  Initialized the given structure to its default values.
 *
 *  @param[in]  params      Parameters required to create a MessageQ
 */
#ifndef MessageQ_internal
static inline Void MessageQ_Params_init(MessageQ_Params *params)
{
    if (params != NULL) {
        MessageQ_Params_init__S(params, MessageQ_Params_VERSION);
    }
}
#endif

/*!
 *  @brief      Initialize MessageQ_Params2
 *
 *  Initialized the given structure to its default values.
 *
 *  @deprecated This function has been deprecated. It will be removed
 *  in a future release. Please use MessageQ_Params_init() instead.
 *
 *  @param[in]  params      Parameters required to create a MessageQ
 */
Void MessageQ_Params2_init(MessageQ_Params2 *params);

/*!
 *  @brief      Create a MessageQ instance
 *
 *  The name supplied here does not have to be in persistent memory.  The
 *  maximum length of the string supplied here, including the '\\0' terminator,
 *  is '32' by default.
 *
 *  There are no verifications to ensure that the name supplied in
 *  MessageQ_create() is unique across all processors. Caution must be exercised
 *  to ensure that each processor uses a unique name.
 *
 *  @param[in]  name        Name of the queue
 *  @param[in]  params      Initialized MessageQ parameters
 *
 *  @return     MessageQ Handle
 */
MessageQ_Handle MessageQ_create(String name, const MessageQ_Params *params);

/*!
 *  @brief      Create a MessageQ instance using the type MessageQ_Params2
 *
 *  The name supplied here does not have to be in persistent memory.  The
 *  maximum length of the string supplied here, including the '\\0' terminator,
 *  is '32' by default.
 *
 *  There are no verifications to ensure that the name supplied in
 *  MessageQ_create2() is unique across all processors. Caution must
 *  be exercised to ensure that each processor uses a unique name.
 *
 *  @deprecated This function has been deprecated. It will be removed
 *  in a future release. Please use MessageQ_create() instead.
 *
 *  @param[in]  name        Name of the queue
 *  @param[in]  params      Initialized MessageQ_Params2
 *
 *  @return     MessageQ Handle
 */
MessageQ_Handle MessageQ_create2(String name, const MessageQ_Params2 *params);

/*!
 *  @brief      Delete a created MessageQ instance
 *
 *  This function deletes a created message queue instance. If the
 *  message queue is non-empty, any messages remaining in the queue
 *  will not be freed and will be lost.
 *
 *  @param[in,out]  handlePtr   Pointer to handle to delete.
 *
 *  @return     MessageQ status:
 *              - #MessageQ_E_FAIL: delete failed
 *              - #MessageQ_S_SUCCESS: delete successful
 */
Int MessageQ_delete(MessageQ_Handle *handlePtr);

/*!
 *  @brief      Open a message queue
 *
 *  MessageQ_open() is used to retrieve the queue id for a queue that has been
 *  created either locally or remotely.  Note that the queueId is simply a
 *  32 bit value that uniquely identifies a queue.  Therefore, it is also
 *  possible to put a message on a queue whose queueId has been retrieved using
 *  any other method.
 *
 *  @param[in]  name        Name of queue to open
 *  @param[out] queueId     QueueId that can be used in MessageQ_put()
 *
 *  @return     MessageQ status:
 *              - #MessageQ_E_NOTFOUND: open failed (name not found on any
 *                processor)
 *              - #MessageQ_S_SUCCESS: open successful
 */
Int MessageQ_open(String name, MessageQ_QueueId *queueId);

/*!
 *  @brief      Open a MessageQ given the queue index and processor ID
 *
 *  This function can be used instead of MessageQ_open() if the queue
 *  was created with a reserved queue index. In the example below, the
 *  serverFxn function must be running on the processor with PROCID 2.
 *
 *      @code
 *      #define SERVER_QUEIDX   1
 *      #define SERVER_PROCID   2
 *
 *      serverFxn()
 *      {
 *          MessageQ_Params params;
 *
 *          MessageQ_Params_init(&params);
 *          params.queueIndex = SERVER_QUEIDX;
 *          messageQ = MessageQ_create(NULL, &params);
 *          ...
 *      }
 *
 *      clientFxn()
 *      {
 *          MessageQ_QueueId serverQueue;
 *          serverQueue = MessageQ_openQueueId(SERVER_QUEIDX, SERVER_PROCID);
 *      }
 *      @endcode
 *
 *  It is up to the application to guarantee that the queue which is being
 *  opened has already been created. MessageQ_openQueueId() does not validate
 *  that the queue has been created (unlike the MessageQ_open() function).
 *
 *  @param[in] queueIndex   QueueIndex specified in MessageQ_Params when
 *                          the message queue was created.
 *  @param[in] procId       Multiproc_Id of where the created queue resides.
 *
 *  @return     The MessageQ_QueueId associated with the queueIndex
 *              and remoteProcId
 */
MessageQ_QueueId MessageQ_openQueueId(UInt16 queueIndex, UInt16 procId);

/*!
 *  @brief      Close the opened handle
 *
 *  Only close a queueId that was returned from MessageQ_open().
 *
 *  @param[in]  queueId     Pointer to queueId to close
 *
 *  @return     MessageQ status:
 *              - #MessageQ_E_FAIL: close failed
 *              - #MessageQ_S_SUCCESS: close successful
 */
Int MessageQ_close(MessageQ_QueueId *queueId);

/*!
 *  @brief      Allocates a message from the heap
 *
 *  This function allocates a message from the heap associated with the heapId.
 *  The first field of the message must be a #MessageQ_MsgHeader structure.
 *  For example:
 *      @code
 *      typedef struct MyMsg {
 *         MessageQ_MsgHeader header;
 *         ...
 *      } MyMsg;
 *      @endcode
 *
 *  @param[in]  heapId      heapId
 *  @param[in]  size        size of requested message (including the
 *                          #MessageQ_MsgHeader).
 *
 *  @pre        @c size must be at least large enough to hold a
 *              MessageQ_MsgHeader
 *
 *  @return    Allocated message or NULL if no memory.
 */
MessageQ_Msg MessageQ_alloc(UInt16 heapId, UInt32 size);

/*!
 *  @brief      Frees a message back to the heap
 *
 *  Frees the message back to the heap that was used to allocate it.
 *
 *  @param[in]  msg         Message to free.
 *
 *  @return     MessageQ status:
 *              - #MessageQ_E_FAIL: failed to free message
 *              - #MessageQ_S_SUCCESS: successfully freed the message
 */
Int MessageQ_free(MessageQ_Msg msg);

/*!
 *  @brief      Register a heap with MessageQ
 *
 *  This function registers a heap with MessageQ. The user selects a unique
 *  heapId associated with this heap. When a message is allocated via
 *  MessageQ_alloc(), the heapId is specified. Internally, MessageQ
 *  uses the heapId to access the heap.
 *
 *  Care must be taken when assigning heapIds. Internally MessageQ stores
 *  the heapId into the message. When the message is freed
 *  (via MessageQ_free()), the heapId is used to determine which heap to use.
 *  On systems with shared memory the heapIds must match on corresponding
 *  processors. For example, assume there is a heap called myHeap which
 *  acts on shared memory and processors 0 and 1 both use this heap.
 *  When you register the heap with MessageQ, the same heapId must be used
 *  on both processor 0 and 1.
 *
 *  If a heap is already registered for the specified heapId, no action is
 *  taken and #MessageQ_E_ALREADYEXISTS is returned.
 *
 *  @param[in]  heap        Heap to register
 *  @param[in]  heapId      heapId associated with the heap
 *
 *  @return     MessageQ status:
 *              - #MessageQ_S_SUCCESS: heap successfully registered
 *              - #MessageQ_E_ALREADYEXISTS: heap already exists with heapId
 */
Int MessageQ_registerHeap(Ptr heap, UInt16 heapId);

/*!
 *  @brief      Register a transport instance for the given ID
 *
 *  Additional transport instances can be registered with the MessageQ
 *  module. This allows for message delivery over selected transports.
 *
 *  To arrange for a message to be delivered using a registered transport,
 *  the corresponding transport ID must be set in the message header by
 *  calling MessageQ_setTransportId().
 *
 *  @param[in]  tid         Transport ID, must be 1-7 inclusive
 *  @param[in]  inst        Transport instance handle
 *
 *  @return     Status result
 *              - TRUE: transport handle successfully registered
 *              - FALSE: failure, most likely transport ID already in use
 *
 *  @sa         MessageQ_setTransportId()
 *  @sa         MessageQ_unregisterTransportId()
 */
Bool MessageQ_registerTransportId(UInt tid, ITransport_Handle inst);

/*!
 *  @brief      Unregister a heap with MessageQ
 *
 *  This function unregisters the heap associated with the heapId.
 *  Care must be taken to ensure that there are no outstanding messages
 *  allocated from this heap. If there are outstanding messages, an attempt
 *  to free the message will result in non-deterministic results.
 *
 *  @param[in]  heapId      Heap to unregister
 *
 *  @return     MessageQ status:
 *              - #MessageQ_S_SUCCESS: heap successfully unregistered
 */
Int MessageQ_unregisterHeap(UInt16 heapId);

/*!
 *  @brief      Unregister the transport instance for the given ID
 *
 *  Remove the registered transport instance for the give transport ID.
 *
 *  @param[in]  tid         Transport ID, must be 1-7 inclusive
 *
 *  @sa         MessageQ_registerTransportId()
 */
Void MessageQ_unregisterTransportId(UInt tid);

/*!
 *  @brief      Sets the message tracing flag on a given message
 *
 *  This function enables message tracing for a message.  Tracing is offered
 *  in the form of Log messages that are output during operations on the
 *  message (i.e. MessageQ_free(), MessageQ_put(), etc).
 *
 *  @param      msg         Message
 *  @param      traceFlag   Message trace flag (TRUE = tracing enabled)
 */
Void MessageQ_setMsgTrace(MessageQ_Msg msg, Bool traceFlag);

/*!
 *  @brief      Initializes a message not obtained from MessageQ_alloc()
 *
 *  There are several fields in the #MessageQ_MsgHeader that
 *  are initialized by the MessageQ_alloc() function. MessageQ_staticMsgInit()
 *  can be used to initialize these fields for messages that are
 *  not allocated from MessageQ.
 *
 *  There is one strict constraint with using messages not allocated
 *  from MessageQ. The message cannot be freed via MessageQ_free().
 *  This includes
 *      - The application calling MessageQ_free() on the same processor
 *      - The application calling MessageQ_free() on a different processor
 *      - The application cannot send the message to another processor
 *        where the transport might call MessageQ_free() on the message.
 *        For example, copy based transport call MessageQ_free() after sending
 *        the message.
 *  If a staticMsgInit'd msg is passed to MessageQ_free() an assert will occur
 *
 *  @param      msg     Message to initialize
 *  @param[in]  size    Size of the message in MAUs
 *
 *  @pre    @c size must be at least large enough to hold a #MessageQ_MsgHeader
 */
Void MessageQ_staticMsgInit(MessageQ_Msg msg, UInt32 size);

/*!
 *  @brief      Sets MessageQ's free hook function.
 *
 *  This API allows a user to specify a hook function which is called within
 *  MessageQ_free(). The hook is called after a message is freed back to the
 *  associated heap. The two parameters to the hook function are the heapId
 *  and the msgId of the freed message.
 *
 *  The function is called within MessageQ_free(), so care must be taken to
 *  minimize any performance or calling context impact.
 *
 *  MessageQ_setFreeHookFxn() is not thread safe. It should only
 *  be called when no MessageQ_free()'s are happening.
 *
 *  To disable the hook function, call MessageQ_setFreeHookFxn() with NULL.
 *
 *  @param[in]  freeHookFxn  function to be called within MessageQ_free()
 */
Void MessageQ_setFreeHookFxn(MessageQ_FreeHookFxn freeHookFxn);

/*!
 *  @brief      Set the function hook for the MessageQ_put() method
 *
 *  Register a hook function which is called from the beginning of the
 *  MessageQ_put() function. Only one hook may be registered at a time.
 *  Subsequent calls to register a put function will overwrite the
 *  previously registered function.
 *
 *  To disable the hook function, call MessageQ_setPutHookFxn() with NULL.
 *
 *  @param[in]  putHookFxn  function to be called within MessageQ_put()
 */
Void MessageQ_setPutHookFxn(MessageQ_PutHookFxn putHookFxn);

/* =============================================================================
 *  MessageQ Per-instance Functions
 * =============================================================================
 */

/*!
 *  @brief      Gets a message from the message queue
 *
 *  This function returns a status. It also returns a message in msg.
 *  If no message is available, it blocks on the synchronizer object
 *  until the synchronizer is signaled or a timeout occurs.
 *  The synchronizer is signaled, when Message_put is called on the MessageQ
 *  handle. If a timeout occurs, the msg is set to NULL and the status is
 *  #MessageQ_E_TIMEOUT. If a timeout of zero is specified, the function
 *  returns immediately and if no message is available, the msg
 *  is set to NULL and the status is #MessageQ_E_TIMEOUT. The
 *  #MessageQ_E_UNBLOCKED status is return, if MessageQ_unblock is called
 *  on the MessageQ handle. The #MessageQ_E_SHUTDOWN status is returned if
 *  MessageQ_shutdown is called on the MessageQ handle. If a message is
 *  successfully retrieved, the msg is set to the message and a
 *  #MessageQ_S_SUCCESS status is returned.
 *
 *  @param[in]  handle      MessageQ handle
 *  @param[out] msg         Pointer to the message
 *  @param[in]  timeout     Maximum duration to wait for a message in
 *                          microseconds.
 *
 *  @return     MessageQ status:
 *              - #MessageQ_S_SUCCESS: Message successfully returned
 *              - #MessageQ_E_TIMEOUT: MessageQ_get() timed out
 *              - #MessageQ_E_UNBLOCKED: MessageQ_get() was unblocked
 *              - #MessageQ_E_FAIL:    A general failure has occurred
 *
 *  @sa         MessageQ_put()
 *  @sa         MessageQ_unblock()
 *  @sa         MessageQ_shutdown()
 */
Int MessageQ_get(MessageQ_Handle handle, MessageQ_Msg *msg, UInt timeout);

/*!
 *  @brief      Place a message onto a message queue
 *
 *  This call places the message onto the specified message queue. The
 *  message queue could be local or remote. The MessageQ module manages
 *  the delivery.
 *
 *  In the case where the queue is remote, MessageQ does not guarantee that
 *  the message is actually delivered before the MessageQ_put() call returns
 *
 *  The queue id must have been returned from one of the following functions:
 *  - MessageQ_open()
 *  - MessageQ_getReplyQueue()
 *  - MessageQ_getDstQueue()
 *
 *  After the message is placed onto the final destination, the queue's
 *  #MessageQ_Params.synchronizer signal function is called.
 *
 *  The application loses ownership of the message once MessageQ_put() is called.
 *
 *  @param[in]  queueId     Destination MessageQ
 *  @param[in]  msg         Message to be sent.
 *
 *  @return     Status of the call.
 *              - #MessageQ_S_SUCCESS denotes success.
 *              - #MessageQ_E_FAIL denotes failure. The put was not successful.
 *                 The caller still owns the message.
 */
Int MessageQ_put(MessageQ_QueueId queueId, MessageQ_Msg msg);

/*!
 *  @brief      Returns the number of messages in a message queue
 *
 *  This function returns the number of messages in a message queue.
 *
 *  @param[in]  handle      MessageQ handle
 *
 *  @return     Number of messages in the message queue.
 */
Int MessageQ_count(MessageQ_Handle handle);

/*!
 *  @brief      Returns the QueueId associated with the handle
 *
 *  Since the MessageQ_put() function takes a QueueId, the creator
 *  of a message queue cannot send a message to itself without
 *  retrieving the QueueId. This function extracts the QueueId
 *  from the object.
 *
 *  @param[in]  handle      MessageQ handle
 *
 *  @return     QueueId associated to the object
 */
UInt32 MessageQ_getQueueId(MessageQ_Handle handle);

/*!
 *  @brief      Embeds a source message queue into a message
 *
 *  This function along with MessageQ_getReplyQueue()
 *  can be used instead of MessageQ_open(). The sender
 *  of a message can embed a messageQ into the message with this
 *  function. The receiver of the message can extract the message queue
 *  id with the MessageQ_getReplyQueue() function.
 *
 *  This method is particularly useful in a client/server relationship
 *  where the server does not want to know who the clients are. The
 *  clients can embed their message queue into the message to the server
 *  and the server extracts it and uses it to reply.
 *
 *  @param      handle      MessageQ handle
 *  @param      msg         Message to embed queue into
 */
Void MessageQ_setReplyQueue(MessageQ_Handle handle, MessageQ_Msg msg);

/*!
 *  @brief      Unblocks a MessageQ
 *
 *  Unblocks a reader thread that is blocked on a MessageQ_get().  The
 *  MessageQ_get() call will return with status #MessageQ_E_UNBLOCKED indicating
 *  that it returned due to a MessageQ_unblock() rather than a timeout or a
 *  received message.  This call should only be used during a shutdown sequence
 *  in order to ensure that there is no blocked reader on a queue before
 *  deleting the queue.  A queue may not be used after it has been unblocked.
 *
 *  MessageQ_unblock() works by raising a flag in the queue indicating that it
 *  is unblocked and then signaling the synchronizer that is configured with
 *  the target queue.  If MessageQ_unblock() is called upon a queue that has
 *  no blocked listeners, then any subsequent MessageQ_get will not block and
 *  will immediately return #MessageQ_E_UNBLOCKED regardless of whether there
 *  is a message on the queue.
 *
 *  Restrictions:
 *  -  A queue may not be used after it has been unblocked.
 *  -  MessageQ_unblock() may only be called on a local queue.
 *  -  May only be used with a queue configured with a blocking synchronizer.
 *
 *  @param[in]  handle      MessageQ handle
 *
 *  @sa         MessageQ_get
 *  @sa         MessageQ_shutdown()
 */
Void MessageQ_unblock(MessageQ_Handle handle);

/*!
 *  @brief      Shuts down a MessageQ
 *
 *  Similar to MessageQ_unblock(), MessageQ_shutdown() unblocks a reader thread
 *  that is blocked on a MessageQ_get(), but causes a different return code
 *  to be returned from MessageQ_get().  The MessageQ_get() call will return
 *  with status #MessageQ_E_SHUTDOWN indicating that it returned due to a
 *  MessageQ_shutdown() rather than MessageQ_unblock(), a timeout or a
 *  received message.  This call is intended to be used by MessageQ transports
 *  when the transport detects that the transport framework corresponding to
 *  the MessageQ has become unusable.  This call should only be used during a
 *  shutdown sequence in order to ensure that there is no blocked reader on a
 *  queue before deleting the queue.  A queue may not be used after it has been
 *  shut down.
 *
 *  MessageQ_shutdown() works by raising a flag in the queue indicating that it
 *  is shut down and then signaling the synchronizer that is configured with
 *  the target queue.  If MessageQ_shutdown() is called upon a queue that has
 *  no blocked listeners, then any subsequent MessageQ_get will not block and
 *  will immediately return #MessageQ_E_SHUTDOWN regardless of whether there
 *  is a message on the queue.
 *
 *  Restrictions:
 *  -  A queue may not be used after it has been shut down.
 *  -  MessageQ_shutdown() may only be called on a local queue.
 *  -  May only be used with a queue configured with a blocking synchronizer.
 *
 *  @param[in]  handle      MessageQ handle
 *
 *  @sa         MessageQ_get
 *  @sa         MessageQ_unblock
 */
Void MessageQ_shutdown(MessageQ_Handle handle);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
#endif /* ti_ipc_MessageQ__include */
