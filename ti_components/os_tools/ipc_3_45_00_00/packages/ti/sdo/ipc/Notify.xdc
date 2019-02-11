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
 *  ======== Notify.xdc ========
 *
 */

package ti.sdo.ipc;

import xdc.runtime.Assert;
import xdc.runtime.Diags;

import xdc.rov.ViewInfo;

import ti.sdo.utils.List;

import ti.sdo.ipc.interfaces.INotifyDriver;

/*!
 *  ======== Notify ========
 *  Notification manager
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/Notify.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>Notify = xdc.useModule('ti.sdo.ipc.Notify');</PRE>
 *
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../../doxygen/html/files.html">Doxygen documenation</A>
 *  for the IPC product.  However, the documentation presented on this page
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 *
 *  The Notify module typically doesn't require much (if any) configuration at
 *  static time. However, it is possible to reduce the amount of shared memory
 *  used by the Notify subsystem by reducing the value of {@link #numEvents}.
 */

@Gated
@ModuleStartup
@InstanceInitError
@InstanceFinalize

module Notify
{
    /*! @_nodoc */
    metaonly struct BasicView {
        UInt        remoteProcId;
        String      remoteProcName;
        UInt        lineId;
        UInt        disabled;
    }

    /*! @_nodoc */
    metaonly struct EventDataView {
        UInt        eventId;
        String      fnNotifyCbck;
        String      cbckArg;
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
                ['EventListeners',
                    {
                        type: ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitData',
                        structName: 'EventDataView'
                    }
                ],
            ]
        });

    /*!
     *  Assert raised when trying to re-register for given line and processor
     */
    config Assert.Id A_alreadyRegistered =
        {msg: "A_alreadyRegistered: Notify instance for the processor/line already registered"};

    /*!
     *  Assert raised when trying to use an unregistered Notify instance
     */
    config Assert.Id A_notRegistered =
        {msg: "A_notRegistered: Notify instance not yet registered for the processor/line"};

    /*!
     *  Assert raised when trying to improperly use a reserved event
     */
    config Assert.Id A_reservedEvent =
        {msg: "A_reservedEvent: Improper use of a reserved event"};

    /*!
     *  Assert raised when {@link #restore} called with improper key
     */
    config Assert.Id A_outOfOrderNesting =
        {msg: "A_outOfOrderNesting: Out of order nesting"};

    /*!
     *  ======== A_invArgument ========
     *  Assert raised when an argument is invalid
     */
    config Assert.Id A_invArgument  = {
        msg: "A_invArgument: Invalid argument supplied"
    };

    /*!
     *  ======== A_internal ========
     *  Assert raised when an internal error is encountered
     */
    config Assert.Id A_internal = {
        msg: "A_internal: An internal error has occurred"
    };

    /*!
     *  ======== SetupProxy ========
     *  Device-specific Notify setup proxy
     */
    proxy SetupProxy inherits ti.sdo.ipc.interfaces.INotifySetup;

    /*! Maximum number of events supported by the Notify module */
    const UInt MAXEVENTS = 32;

    /*!
     *  Number of events supported by Notify
     *
     *  Lowering this value offers the benefit of lower footprint especially in
     *  shared memory.
     */
    config UInt numEvents = 32;

    /*!
     *  ======== sendEventPollCount ========
     *  Poll for specified amount before sendEvent times out
     *
     *  Setting a finite value for sendEventPollCount will cause
     *  Notify_sendEvent to poll for an amount of time
     *  proportional to this value when the 'waitClear' flag is TRUE.
     */
    config UInt32 sendEventPollCount = -1;

    /*! @_nodoc
     *  Maximum number of interrupt lines between a single pair of processors
     *
     *  This config is usually set internally by the NotfiySetup proxy when the
     *  proxy is set up to use more than one line.
     */
    config UInt16 numLines = 1;

    /*!
     *  Number of reserved event numbers
     *
     *  The first reservedEvents event numbers are reserved for
     *  middleware modules. Attempts to use these reserved events
     *  will result in a {@link #A_reservedEvent} assert.
     *
     *  To use the reserved events, the top 16-bits of the eventId must equal
     *  Notify_SYSTEMKEY.
     */
    config UInt16 reservedEvents = 5;

    /*!
     *  @_nodoc
     *  Detach Notify from a remote processor. Should only be called by the Ipc
     *  module during its detach operation.
     */
    Int detach(UInt16 remoteProcId);

instance:

    /*! @_nodoc
     *  Register a created Notify driver with the Notify module
     *
     *  The Notify module stores a copy of the driverHandle in an array
     *  indexed by procId and lineId.  Furture references to the procId
     *  and lineId in Notify APIs will utilize the driver registered using
     *  {@link #create}.
     *
     *  @param(driverHandle)    Notify driver handle
     *  @param(procId)          Remote processor id
     *  @param(lineId)          Line id
     */
    create(INotifyDriver.Handle driverHandle, UInt16 remoteProcId,
           UInt16 lineId);

    /*! @_nodoc
     *  Called internally by the Notify module or notify driver module
     *  to execute the callback registered to a specific event.
     */
    Void exec(UInt32 eventId, UInt32 payload);

internal:

    /*!
     *  Used to execute a list of callback functions when the callbacks are
     *  registered using registerMany.
     */
    Void execMany(UInt16 remoteProcId, UInt16 lineId, UInt32 eventId, UArg arg,
                  UInt32 payload);

    struct EventCallback {
        Fxn             fnNotifyCbck;
        UArg            cbckArg;
    }

    struct EventListener {
        List.Elem       element;          /* List elem         */
        EventCallback   callback;
    }

    struct Instance_State {
        UInt                    nesting;        /* Disable/restore nesting    */
        INotifyDriver.Handle    driverHandle;   /* Driver handle              */
        UInt16                  remoteProcId;   /* Remote MultiProc id        */
        UInt16                  lineId;         /* Interrupt line id          */
        EventCallback           callbacks[];    /* indexed by eventId         */
        List.Object             eventList[];    /* indexed by eventId         */
    };

    struct Module_State {
        Handle        notifyHandles[][]; /* indexed by procId then lineId */

        /*
         * these fields are used for local/loopback events
         */
        Bits32        localEnableMask;  /* default to enabled (-1) */
    }

}
