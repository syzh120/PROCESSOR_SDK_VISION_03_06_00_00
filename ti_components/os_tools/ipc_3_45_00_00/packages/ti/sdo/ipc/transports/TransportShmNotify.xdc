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
 *  ======== TransportShmNotify.xdc ========
 */

/*!
 *  ======== TransportShmNotify ========
 *  Transport for MessageQ that acts on shared memory.
 *
 *  TransportShmSingle is a simplified version of {@link TransportShm}.  This
 *  transport uses the Notify module to do all the real work.  The 'put'
 *  function passes the message to the other processor using the 'payload'
 *  parameter to Notify_sendEvent().  The receive side simply casts this
 *  payload parameter to a MessageQ_Msg and enqueues it locally.
 *
 *  CAVEATS:
 *
 *  The sender will spin in Notify_sendEvent until the receive side has
 *  read the previous message.  This is Notify-driver specific.
 *  NotifyDriverShm  will spin before sending a new event if the prior event
 *  hasn't been handled.  Some Notify drivers may support a FIFO or queue
 *  for these events to mitigate this busy-wait affect.
 */
@InstanceFinalize
@InstanceInitError

module TransportShmNotify inherits ti.sdo.ipc.interfaces.IMessageQTransport
{
    /*!
     *  ======== notifyEventId ========
     *  Notify event ID for transport.
     */
    config UInt16 notifyEventId = 2;

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

instance:

internal:

    Void notifyFxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg,
                   UInt32 payload);

    /* Instance State object */
    struct Instance_State {
        UInt16          remoteProcId;  /* dst proc id                   */
        UInt16          priority;      /* priority to register          */
    };
}
