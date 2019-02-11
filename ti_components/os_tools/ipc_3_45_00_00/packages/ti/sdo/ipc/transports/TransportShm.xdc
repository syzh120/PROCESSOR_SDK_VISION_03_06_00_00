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
 *  ======== TransportShm.xdc ========
 */

import xdc.runtime.Error;
import ti.sdo.ipc.Ipc;
import ti.sdo.ipc.GateMP;
import ti.sdo.ipc.ListMP;
import ti.sdo.ipc.SharedRegion;
import ti.sysbios.knl.Swi;

/*!
 *  ======== TransportShm ========
 *  Shared-memory MessageQ transport that uses ListMP to queue messages
 *
 *  Messages sent via TransportShm are temporarily queued in a shared memory
 *  {@link ti.sdo.ipc.ListMP} instance before the messages are moved by the
 *  receiver to the destination queue.
 */
@InstanceFinalize
@InstanceInitError

module TransportShm inherits ti.sdo.ipc.interfaces.IMessageQTransport
{
    /*! @_nodoc
     *  ======== openByAddr ========
     *  Open a created TransportShm instance by address
     *
     *  Just like {@link #open}, openByAddr returns a handle to a created
     *  TransportShm instance.  This function is used to open a
     *  TransportShm using a shared address instead of a name.
     *  While {@link #open} should generally be used to open transport
     *  instances that have been either locally or remotely created, openByAddr
     *  may be used to bypass a NameServer query that would typically be
     *  required of an {@link #open} call.
     *
     *  Opening by address requires that the created instance was created
     *  by supplying a {@link #sharedAddr} parameter rather than a
     *  {@link #regionId} parameter.
     *
     *  A status value of Status_SUCCESS is returned if the instance
     *  is successfully opened.  Status_FAIL indicates that the instance
     *  is not yet ready to be opened.  Status_ERROR indicates that
     *  an error was raised in the error block.
     *
     *  Call {@link #close} when the opened instance is no longer needed.
     *
     *  @param(sharedAddr)  Shared address for the instance
     *  @param(handlePtr)   Pointer to handle to be opened
     *  @param(eb)          Pointer to error block
     *
     *  @a(returns)         TransportShm status
     */
    Int openByAddr(Ptr sharedAddr, Handle *handlePtr, Error.Block *eb);

    /*!
     *  ======== close ========
     *  Close an opened instance
     *
     *  Closing an instance will free local memory consumed by the opened
     *  instance.  Instances that are opened should be closed before the
     *  instance is deleted.
     *
     *  @param(handle)  handle that is returned from an {@link #openByAddr}
     */
    Void close(Handle *handle);

    /*! @_nodoc
     *  ======== sharedMemReq ========
     *  Amount of shared memory required for creation of each instance
     *
     *  Can be used to make sure the {link #sharedAddr} buffer is large
     *  enough before calling create.
     *
     *  The {@link #sharedAddr} needs to be
     *  supplied because the cache alignment settings for the region
     *  may affect the total amount of shared memory required.
     *
     *  @param(params)      Pointer to the parameters that will be used in
     *                      the create.
     *
     *  @a(returns)         Number of MAUs needed to create the instance.
     */
    SizeT sharedMemReq(const Params *params);

    /*!
     *  ======== notifyEventId ========
     *  Notify event ID for transport.
     */
    config UInt16 notifyEventId = 2;

instance:

    /*!
     *  ======== gate ========
     *  GateMP used for critical region management of the shared memory
     */
    config GateMP.Handle gate = null;

    /*! @_nodoc
     *  ======== openFlag ========
     *  Set to 'true' by the open() call. No one else should touch this!
     */
    config Bool openFlag = false;

    /*!
     *  ======== sharedAddr ========
     *  Physical address of the shared memory
     *
     *  The creator must supply the shared memory that is used to maintain
     *  shared state information.
     */
    config Ptr sharedAddr = null;

internal:

    /*!
     *  Constants that all delegate writers need.
     */
    const UInt32 UP = 0xBADC0FFE;

    /*!
     *  ======== swiFxn ========
     *  This function takes the messages from the transport ListMP and
     *  calls MessageQ_put to send them to their destination queue.
     *  This function is posted by the NotifyFxn.
     *
     *  @param(arg)     argument for the function
     */
    Void swiFxn(UArg arg);

    /*!
     *  ======== notifyFxn ========
     *  This is a callback function registered with Notify.  It is called
     *  when a remote processor does a Notify_sendEvent().  It is executed
     *  at ISR level.  It posts the instance Swi object to execute swiFxn.
     *
     *  @param(eventId) Notify event id
     *  @param(arg)     argument for the function
     *  @param(payload) 32-bit payload value.
     */
    Void notifyFxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg,
                   UInt32 payload);

    /* Structure of attributes in shared memory */
    struct Attrs {
        Bits32              flag;
        Bits32              creatorProcId;
        Bits32              notifyEventId;
        Bits16              priority;
        SharedRegion.SRPtr  gateMPAddr;
    };

    /* Instance State object */
    struct Instance_State {
        Attrs           *self;         /* Attrs in shared memory        */
        Attrs           *other;        /* Only flag field is used       */
        ListMP.Handle   localList;     /* ListMP to my processor        */
        ListMP.Handle   remoteList;    /* ListMP to remote processor    */
        Swi.Object      swiObj;        /* Each instance has a swi       */
        UInt32          status;        /* Current status                */
        Ipc.ObjType     objType;       /* Static/Dynamic? open/creator? */
        SizeT           allocSize;     /* Shared memory allocated       */
        Bool            cacheEnabled;  /* Whether to do cache calls     */
        UInt16          regionId;      /* the shared region id          */
        UInt16          remoteProcId;  /* dst proc id                   */
        UInt16          priority;      /* priority to register          */
        GateMP.Handle   gate;          /* Gate for critical regions     */
    };

}
