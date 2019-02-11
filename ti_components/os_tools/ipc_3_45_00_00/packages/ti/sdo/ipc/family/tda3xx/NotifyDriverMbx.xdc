/*
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com
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
package ti.sdo.ipc.family.tda3xx;

import ti.sdo.utils.MultiProc;
import ti.sdo.ipc.interfaces.INotifyDriver;
import ti.sdo.ipc.Notify;

import ti.sysbios.hal.Hwi;

import xdc.runtime.Assert;
import xdc.rov.ViewInfo;

/*!
 *  ======== NotifyDriverMbx ========
 *  A notify driver based on hardware mailbox.
 *
 *  This notify driver uses hardware mailboxes to transmit notifications
 *  to remote processors. This driver implements the
 *  {@link ti.sdo.ipc.interfaces.INotifyDriver} interface.
 *
 *  Unlike the Notify drivers available in the {@link ti.sdo.ipc.notifyDrivers}
 *  package, this driver is not generic and will only work with the TDA3XX
 *  family of devices.
 *
 *  The driver does not use shared memory. The event IDs and payloads are
 *  transmitted via the hardware mailbox FIFO. The FIFO can hold up to 4
 *  mailbox messages. The number of notification that can be stored in the
 *  FIFO depends on the size of the payloads being sent via Notify_sendEvent.
 *  If the payload is less than 0x7FFFFFF, then a single message will be
 *  sent per notification. Otherwise, two mailbox messages are needed to
 *  send the notification.
 *
 *  The behavior of Notify_sendEvent when the FIFO is full depends on the
 *  value of the 'waitClear' argument to the function. If 'waitClear' is
 *  TRUE, then Notify_sendEvent will spin waiting for enough room in the
 *  FIFO. If 'waitClear' is FALSE, then Notify_sendEvent will return
 *  Notify_E_FAIL.
 *
 *  The Notify_enableEvent and Notify_disableEvent APIs are not supported
 *  by this driver.
 */
@InstanceFinalize
@ModuleStartup

module NotifyDriverMbx inherits ti.sdo.ipc.interfaces.INotifyDriver
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String      remoteProc;
    }

    /*! @_nodoc */
    metaonly struct MailboxView {
        String      direction;
        String      mailboxAddr;
        Int         subMbxId;
        Int         msgCount;
        Int         mbxInterrupt;
    }

    /*!  @_nodoc */
    metaonly struct ModuleView {
        NotifyDriverMbx.Handle  drvHandles[NUM_CORES];
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
                ['Mailbox',
                    {
                        type: ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitMailbox',
                        structName: 'MailboxView'
                    }
                ]
//              ['Module',
//                  {
//                      type: ViewInfo.MODULE,
//                      viewInitFxn: 'viewInitModule',
//                      structName: 'ModuleView'
//                  }
//              ]
            ]
        });

    /*!
     *  Assert raised when trying to use Notify_[enable/disable]Event with
     *  NotifyDriverMbx
     */
    config Assert.Id A_notSupported = {
        msg: "A_notSupported: [enable/disable]Event not supported"
    };

instance:

    /*!
     *  ======== remoteProcId ========
     *  The MultiProc ID corresponding to the remote processor
     *
     *  This is a required parameter, it is not optional.
     */
    config UInt16 remoteProcId = MultiProc.INVALIDID;

    /*!
     *  ======== intVectorId ========
     *  Interrupt vector ID to be used by the driver.
     *
     *  This parameter is only used by C66 targets.
     *  This is a required parameter, it is not optional.
     */
    config UInt intVectorId = ~1u;

internal:
    /* total number of cores on SoC */
    const UInt8 NUM_CORES = 5;

    /* number of cores in eve subsystem */
    const UInt8 NUM_EVES = 1;

    /* number of internal eve mailboxes */
    const UInt8 NUM_EVE_MBX = 2;

    /* number of system mailboxes (used by IPC) */
    const UInt8 NUM_SYS_MBX = 1;

    /*  Mailbox table for storing encoded base address, mailbox user ID,
     *  and sub-mailbox index.
     */
    config UInt32 mailboxTable[NUM_CORES * NUM_CORES];

    /* base address table for the mailbox subsystem */
    /* TODO use the table in NotifySetup module */
    config UInt32 mailboxBaseAddr[NUM_EVE_MBX + NUM_SYS_MBX];

    /* map MultiProc ID to virtual ID, virtId = procIdTable[procId] */
    config UInt32 procIdTable[NUM_CORES];

    /*! define MultiProcID for each core to avoid doing this at runtime */
    config UInt eve1ProcId     = MultiProc.INVALIDID;
    config UInt dsp1ProcId     = MultiProc.INVALIDID;
    config UInt dsp2ProcId     = MultiProc.INVALIDID;
    config UInt ipu1_0ProcId   = MultiProc.INVALIDID;
    config UInt ipu1_1ProcId   = MultiProc.INVALIDID;

    /* plugs the interrupt and executes the callback functions */
    Void isr(UInt16 idx);

    /*! instance state structure */
    struct Instance_State {
        Bits32          evtRegMask;     /* local event register mask        */
        Notify.Handle   notifyHandle;   /* handle to front-end object       */
        UInt16          remoteProcId;   /* remote processor ID              */
        UInt16          remoteVirtId;   /* remote processor virtual ID      */
        Int             cpuIntrNum;     /* cpu interrupt number             */
    }

    struct Module_State {
        /*  Used by the isr to retrieve the driver handle. This table is
         *  indexed by virtual processorID.
         */
        NotifyDriverMbx.Handle drvHandles[NUM_CORES];
    };
}
