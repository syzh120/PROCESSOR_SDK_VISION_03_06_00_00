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
 *  ======== NotifyDriverMbx.xdc ================
 */

import ti.sdo.utils.MultiProc;
import ti.sdo.ipc.interfaces.INotifyDriver;
import ti.sdo.ipc.Notify;

import ti.sysbios.hal.Hwi;

import xdc.runtime.Assert;
import xdc.rov.ViewInfo;

/*!
 *  ======== NotifyDriverMbx ========
 *  A TI81xx hardware mailbox based driver for the Notify Module.
 *
 *  This is a {@link ti.sdo.ipc.Notify} driver that uses hardware mailboxes to
 *  transmit notifications to remote processors.
 *
 *  Unlike the Notify drivers available in the {@link ti.sdo.ipc.notifyDrivers}
 *  package, this driver is not generic and will only work with the TI81xx
 *  family of devices.
 *
 *  The driver uses no shared memory since the event IDs and payloads that
 *  comprise notifications are transmitted via the hardware mailbox FIFO.  The
 *  FIFO can hold up to 4 mailbox messages.  The number of notification that can
 *  be stored in the FIFO depends on the sizes of the payloads being sent via
 *  Notify_sendEvent.  If the payload is less than 0x7FFFFFF, then a single
 *  message will be sent per notification.  Otherwise, if the payload is greater
 *  than or equal to 0x7FFFFFF, two mailbox messages are needed to send the
 *  notification.
 *
 *  The behavior of Notify_sendEvent when the FIFO is full depends on the value
 *  of the 'waitClear' argument to the function.  If 'waitClear' is TRUE, then
 *  Notify_sendEvent will spin waiting for enough room in the FIFO for the
 *  notification before actually sending it.  If 'waitClear' is FALSE, then
 *  Notify_sendEvent will return Notify_E_FAIL if there isn't enough room in the
 *  FIFO to store the notification.
 *
 *  The Notify_[enable/disable]Event APIs are not supported by this driver.
 *
 */
@InstanceFinalize
@ModuleStartup
module NotifyDriverMbx inherits ti.sdo.ipc.interfaces.INotifyDriver
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String      remoteProcName;
        UInt        numIncomingPending;
        UInt        numOutgoingPending;
        String      incomingIntStatus;
        String      outgoingIntStatus;
        String      registeredEvents;
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
            ]
        });

    /*!
     *  Assert raised when trying to use Notify_[enable/disable]Event with
     *  NotifyDriverMbx
     */
    config Assert.Id A_notSupported =
        {msg: "A_notSupported: [enable/disable]Event not supported by NotifyDriverMbx"};


    /*! Base address for the Mailbox subsystem */
    config UInt32 mailboxBaseAddr = 0x480C8000;

    /*!
     *  ======== intVectorId ========
     *  Interrupt vector ID to be used by the driver.
     *
     *  This parameter is only used by the DSP core
     */
    config UInt intVectorId = ~1u;

instance:

    /*!
     *  ======== remoteProcId ========
     *  The MultiProc ID corresponding to the remote processor
     */
    config UInt16 remoteProcId = MultiProc.INVALIDID;

internal:

    config UInt16 dspProcId   = MultiProc.INVALIDID;
    config UInt16 hostProcId  = MultiProc.INVALIDID;
    config UInt16 videoProcId = MultiProc.INVALIDID;
    config UInt16 vpssProcId  = MultiProc.INVALIDID;

    /*!
     *  Plugs the interrupt and executes the callback functions according
     *  to event priority
     */
    Void isr(UArg arg);

    /*! Instance state structure */
    struct Instance_State {
        Bits32           evtRegMask;     /* local event register mask        */
        Notify.Handle    notifyHandle;   /* Handle to front-end object       */
        UInt16           remoteProcId;   /* Remote MultiProc id              */
    }

    struct Module_State {
        NotifyDriverMbx.Handle drvHandles[4];
        Hwi.Object hwi;
    };
}
