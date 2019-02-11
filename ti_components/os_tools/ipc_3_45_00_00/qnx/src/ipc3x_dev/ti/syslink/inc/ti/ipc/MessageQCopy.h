/*
 * Copyright (c) 2010, Texas Instruments Incorporated
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
 * */

/** ============================================================================
 *  @file       MessageQCopy.h
 *
 *  @brief      MessageQCopy Manager
 *
 *  The MessageQCopy module supports the structured sending and receiving of
 *  variable length messages. This module can be used for homogeneous
 *  (DSP to DSP)  or heterogeneous (Arm to DSP) multi-processor messaging.
 *
 *  MessageQCopy provides more sophisticated messaging than other modules. It is
 *  typically used for complex situations such as multi-processor messaging.
 *
 *  The following are key features of the MessageQCopy module:
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
 *  #::MessageQ_MsgHeader structure. For example:
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
 *  The #MessageQ_registerHeap API is used to
 *  assign a MessageQ heapId to a heap. When allocating a message, the heapId
 *  is used, not the heap handle. This heapId is actually placed into the
 *  message (part of the #::MessageQ_MsgHeader). Care must be taken when
 *  assigning heapIds. Refer to the #MessageQ_registerHeap API description for
 *  more details.
 *
 *  MessageQ also supports the usage of messages that are not allocated via the
 *  #MessageQ_alloc function. Please refer to the #MessageQ_staticMsgInit
 *  function description for more details.
 *
 *  MessageQ supports reads/writes of different thread models. This is
 *  accomplished by having the creator of the message queue specify a
 *  synchronizer via the #MessageQ_Params::synchronizer
 *  configuration parameter. The synchronizer is signalled whenever the
 *  #MessageQ_put is called. The synchronizer waits if #MessageQ_get is called
 *  and there are no messages.
 *
 *  Since ISyncs are binary, the reader must drain the message queue of all
 *  messages before waiting for another signal. For example, if the reader
 *  was a SYSBIOS Swi, the synchronizer instance could be a SyncSwi.
 *  If a #MessageQ_put was called, the Swi_post() would
 *  be called. The Swi would run and it must call #MessageQ_get until no
 *  messages are returned.
 *
 *  @version        0.00.01
 *
 *  ============================================================================
 */

#ifndef ti_ipc_MessageQCopy__include
#define ti_ipc_MessageQCopy__include

#include <ti/ipc/MultiProc.h>

#if defined (__cplusplus)
extern "C" {
#endif

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    MessageQCopy_S_BUSY
 *  @brief  The resource is still in use
 */
#define MessageQCopy_S_BUSY                  2

/*!
 *  @def    MessageQCopy_S_ALREADYSETUP
 *  @brief  The module has been already setup
 */
#define MessageQCopy_S_ALREADYSETUP          1

/*!
 *  @def    MessageQCopy_S_SUCCESS
 *  @brief  Operation is successful.
 */
#define MessageQCopy_S_SUCCESS               0

/*!
 *  @def    MessageQCopy_E_FAIL
 *  @brief  Operation is not successful.
 */
#define MessageQCopy_E_FAIL                 -1

/*!
 *  @def    MessageQCopy_E_INVALIDARG
 *  @brief  There is an invalid argument.
 */
#define MessageQCopy_E_INVALIDARG           -2

/*!
 *  @def    MessageQCopy_E_MEMORY
 *  @brief  Operation resulted in memory failure.
 */
#define MessageQCopy_E_MEMORY               -3

/*!
 *  @def    MessageQCopy_E_ALREADYEXISTS
 *  @brief  The specified entity already exists.
 */
#define MessageQCopy_E_ALREADYEXISTS        -4

/*!
 *  @def    MessageQCopy_E_NOTFOUND
 *  @brief  Unable to find the specified entity.
 */
#define MessageQCopy_E_NOTFOUND             -5

/*!
 *  @def    MessageQCopy_E_TIMEOUT
 *  @brief  Operation timed out.
 */
#define MessageQCopy_E_TIMEOUT              -6

/*!
 *  @def    MessageQCopy_E_INVALIDSTATE
 *  @brief  Module is not initialized.
 */
#define MessageQCopy_E_INVALIDSTATE         -7

/*!
 *  @def    MessageQCopy_E_OSFAILURE
 *  @brief  A failure occurred in an OS-specific call
 */
#define MessageQCopy_E_OSFAILURE            -8

/*!
 *  @def    MessageQCopy_E_RESOURCE
 *  @brief  Specified resource is not available
 */
#define MessageQCopy_E_RESOURCE             -9

/*!
 *  @def    MessageQCopy_E_RESTART
 *  @brief  Operation was interrupted. Please restart the operation
 */
#define MessageQCopy_E_RESTART              -10

/*!
 *  @def    MessageQCopy_E_INVALIDMSG
 *  @brief  An invalid message was encountered
 */
#define MessageQCopy_E_INVALIDMSG           -11

/*!
 *  @def    MessageQCopy_E_NOTOWNER
 *  @brief  Not the owner
 */
#define MessageQCopy_E_NOTOWNER             -12

/*!
 *  @def    MessageQCopy_E_REMOTEACTIVE
 *  @brief  Operation resulted in error
 */
#define MessageQCopy_E_REMOTEACTIVE         -13

/*!
 *  @def    MessageQCopy_E_INVALIDHEAPID
 *  @brief  An invalid heap id was encountered
 */
#define MessageQCopy_E_INVALIDHEAPID        -14

/*!
 *  @def    MessageQCopy_E_INVALIDPROCID
 *  @brief  An invalid MultiProc id was encountered
 */
#define MessageQCopy_E_INVALIDPROCID        -15

/*!
 *  @def    MessageQCopy_E_MAXREACHED
 *  @brief  The max has been reached.
 */
#define MessageQCopy_E_MAXREACHED           -16

/*!
 *  @def    MessageQCopy_E_UNBLOCKED
 *  @brief  MessageQCopy was unblocked
 */
#define MessageQCopy_E_UNBLOCKED            -20

/* =============================================================================
 *  Macros
 * =============================================================================
 */

/*!
 *  @brief      Used as the timeout value to specify wait forever
 */
#define MessageQCopy_FOREVER                ~(0)

/*!
 *  @brief      Invalid message id
 */
#define MessageQCopy_INVALIDMSGID           0xffff

/*!
 *  @brief      Invalid message queue
 */
#define MessageQCopy_INVALIDMESSAGEQ        0xffff

/*!
 *  @brief      Mask to extract priority setting
 */
#define MessageQCopy_PRIORITYMASK           0x3

/* =============================================================================
 *  Structures & Enums
 * =============================================================================
 */

/*!
 *  @brief  MessageQ_Handle type
 */
typedef struct MessageQCopy_Object_tag *MessageQCopy_Handle;


/* =============================================================================
 *  MessageQCopy Module-wide Functions
 * =============================================================================
 */

/*!
 *  @brief      Create a MessageQCopy instance
 *
 *  @param[in]  reserved   The requested address for the MessageQ
 *  @param[in]  name       Name of the queue
 *  @param[in]  cb         Callback for notifications of messages
 *  @param[in]  priv       Private data to be passed to cb
 *  @param[out] endpoint   Address of created MessageQ
 *
 *  @return     MessageQ Handle
 */
MessageQCopy_Handle MessageQCopy_create (UInt32 reserved,
                                         String name,
                                         Void (*cb)(MessageQCopy_Handle,
                                                    Void *, Int, Void *, UInt32,
                                                    UInt16),
                                         Void *priv,
                                         UInt32 * endpoint);

/*!
 *  @brief      Delete a created MessageQ instance
 *
 *  @param[in,out]  handlePtr   Pointer to handle to delete.
 */
Int MessageQCopy_delete (MessageQCopy_Handle * handlePtr);

/*!
 *  @brief      Register for notification of remote MessageQCopy handles
 *
 *  MessageQCopy_registerNotify is used to register for notification of creation
 *  of remote MessageQCopy handles that have the same name as the local
 *  MessageQCopy instance passed to MessageQCopy_regiserNoify.  When a remote
 *  MessageQCopy instance with the same name is created, the registered
 *  callback is called.  The parameters passed to the callback are the remote
 *  MessageQCopy handle, the remote proc ID, and the remote endpoint address.
 *
 *  @param[in]  handle      The MessageQCopy_Handle instance
 *  @param[in]  cb          The callback to be called when a remote
 *                          MessageQCopy_Handle with the same name is created.
 *
 *  @return     MessageQ status:
 *              - #MessageQCopy_E_INVALIDSTATE: invalid state
 *              - #MessageQCopy_E_INVALIDARG: invalid argument passed
 *              - #MessageQCopy_S_SUCCESS: success
 */
Int MessageQCopy_registerNotify (MessageQCopy_Handle handle,
                                 void(* cb)(MessageQCopy_Handle,
                                            UInt16, UInt32, Char *, Bool));

/* =============================================================================
 *  MessageQCopy Per-instance Functions
 * =============================================================================
 */

/*!
 *  @brief      Place a message onto a message queue endpoint
 *
 *  This call places the message onto the specified message queue endpoint. The
 *  message queue could be local or remote. The MessageQCopy module manages
 *  the delivery.
 *
 *  In the case where the queue is remote, MessageQCopy does not guarantee that
 *  the message is actually delivered before the MessageQCopy_send() call
 *  returns.
 *
 *  After the message is placed onto the final destination, the queue's
 *  #MessageQCopy_Params::synchronizer signal function is called.
 *
 *  The application loses ownership of the message once send() is called.
 *
 *  @param[in]  dstProc     Destination procid to send the message
 *  @param[in]  srcProc     Source procid that is sending the message
 *  @param[in]  dstEndpt    Destination endpoint on destination procid
 *  @param[in]  srcEndpt    Source endpoint that is sending the message
 *  @param[in]  data        Message to be sent.
 *  @param[in]  len         Length of the data to be sent.
 *  @param[in]  wait        Wait until message is available if there are none
 *
 *  @return     Status of the call.
 *              - #MessageQCopy_S_SUCCESS denotes success.
 *              - #MessageQCopy_E_FAIL denotes failure. The send was not
 *                 successful. The caller still owns the message.
 */
Int MessageQCopy_send (UInt16 dstProc, UInt16 srcProc, UInt32 dstEndpt,
                       UInt32 srcEndpt, Ptr data, UInt16 len, Bool wait);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
#endif /* ti_ipc_MessageQCopy__include */

/*
 */

/*
 *  @(#) ti.ipc; 1, 0, 0, 0,111; 6-25-2010 18:56:21; /db/vtree/library/trees/ipc/ipc-e16x/src/
 */

