/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== NotifySetup.xdc ========
 */

package ti.sdo.ipc.family.vayu;

import xdc.runtime.Assert;
import ti.sdo.utils.MultiProc;

/*!
 *  ======== NotifySetup ========
 *  Notify driver setup proxy for Vayu
 *
 *  This module creates and registers the IPC Notify drivers for the Vayu
 *  device family. There are two types of notify drivers available: 1) shared
 *  memory driver, and 2) mailbox driver. Use the {@link #connections}
 *  configuration parameter to select which driver to use for communicating
 *  with each remote processor.
 *
 *  The shared memory notify driver is the default driver. It implements the
 *  full Notify API set. This driver uses memory for passing the notify
 *  payload between processors. The memory is allocated from SharedRegion #0.
 *
 *  The mailbox notify driver uses hardware FIFOs for passing the notify
 *  payload between processors. No shared memory is required. However, this
 *  driver does not implement the full Notify API set. For example, the
 *  `Notify_sendEvent()` API will never return `Notify_E_EVTNOTREGISTERED`
 *  because it does not track this information.
 *
 *  When configuring the notify driver, you specify which driver to use
 *  for communicating to each remote processor. If not configured, the
 *  shared memory driver will be used by default. Both sides of each connection
 *  must use the same driver. This is an easy mistake to make and there is
 *  no way to check this.
 *
 *  This module is primarily used by notify driver authors. It is not expected
 *  that any application would ever use this module in its runtime code.
 *  The typical use of this module is simply to configure which notify driver
 *  to use. See the following example for details.
 *
 *  @a(Configuration Example)
 *
 *  The following is a three processor example: HOST DSP1 EVE1. In this
 *  example, HOST and DSP1 will communicate using the shared memory driver
 *  and DSP1 and EVE1 will communicate using the mailbox driver. This example
 *  explicitly configures the shared memory driver for HOST and DSP1, but
 *  this is strictly not necessary. If left unconfigured, the shared memory
 *  driver would be used as the default. Also, the connection between HOST
 *  and EVE1 is left undefined as we don't expect to use this connection.
 *
 *  Notice that each connection configuration specifies the remote processor
 *  name and the driver type. This is how the local processor declares which
 *  driver it will use when communicating to that remote processor. The
 *  corresponding configuration on the remote processor must be complimentary.
 *
 *  Add the following to your HOST configuration script.
 *
 *  @p(code)
 *  // configure the notify driver
 *  var NotifySetup = xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
 *
 *  NotifySetup.connections.$add(
 *      new NotifySetup.Connection({
 *          driver: NotifySetup.Driver_SHAREDMEMORY,
 *          procName: "DSP1"
 *      })
 *  );
 *  @p
 *  Add the following to your DSP1 configuration script.
 *
 *  @p(code)
 *  // configure the notify driver
 *  var NotifySetup = xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
 *
 *  NotifySetup.connections.$add(
 *      new NotifySetup.Connection({
 *          driver: NotifySetup.Driver_SHAREDMEMORY,
 *          procName: "HOST"
 *      })
 *  );
 *
 *  NotifySetup.connections.$add(
 *      new NotifySetup.Connection({
 *          driver: NotifySetup.Driver_MAILBOX,
 *          procName: "EVE1"
 *      })
 *  );
 *  @p
 *  Add the following to your EVE1 configuration script.
 *
 *  @p(code)
 *  // configure the notify driver
 *  var NotifySetup = xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
 *
 *  NotifySetup.connections.$add(
 *      new NotifySetup.Connection({
 *          driver: NotifySetup.Driver_MAILBOX,
 *          procName: "DSP1"
 *      })
 *  );
 *  @p
 */

@ModuleStartup
@Template("./NotifySetup.xdt")

module NotifySetup inherits ti.sdo.ipc.interfaces.INotifySetup
{
    /*! @_nodoc
     *  ======== DriverIsr ========
     *  Notify driver isr function type definition
     *  param1 = mailbox table index
     */
    typedef Void (*DriverIsr)(UInt16);

    /*!
     *  ======== Driver ========
     *  Define the available notify drivers
     *
     *  For any given connection to a remote processor, one of the
     *  following notify driver types may be used. Each driver has
     *  different characteristics and system requirements.
     *
     *  @p(html)
     *  <div class="xdocText"><dl>
     *  <dt>Driver_SHAREDMEMORY</dt>
     *      <dd>
     *      This driver uses shared memory for passing the notify payload
     *      between processors. Additional state is also stored in the
     *      shared memory.<br><br>
     *
     *      There is a separate, cache-aligned block of memory for each
     *      event number. This is necessary to maintain cache coherency.
     *      However, this requires a non-trivial amount of memory.<br><br>
     *      </dd>
     *
     *  <dt>Driver_MAILBOX</dt>
     *      <dd>
     *      This driver uses a hardware FIFO (provided by the hardware
     *      mailbox) to pass the notify payload between processors. No
     *      shared memory is required by this driver.<br><br>
     *
     *      This driver does not support the full Notify API set. This
     *      driver has lower delivery latency when compard to the shared
     *      memory driver.<br><br>
     *      </dd>
     *  </dl>
     *  @p
     */
    enum Driver {
        Driver_SHAREDMEMORY = 0x01,     /*! shared memory driver */
        Driver_MAILBOX = 0x02           /*! hardware mailbox driver */
    };

    /*!
     *  ======== Connection ========
     *  Define a notify driver connection
     *
     *  Each IPC connection is defined by two end-points: the local
     *  processor and the remote processor. Each connection supports
     *  only one type of notify driver. In other words, both ends of
     *  the connection must configure the same notify driver type.
     *
     *  However, when a processor has multiple connections (when
     *  communicating with multiple remote processors), each connection
     *  is configured independently. Therefore, different notify drivers
     *  may be used for different connections. Currently, IPC supports
     *  only one connection for each remote processor.
     *
     *  The configuration for a given connection must be coordinated with
     *  the remote processor. Each processor is only able to configure its
     *  local end-point for the connection. It is important that the remote
     *  processor use the same notify driver for the connection.
     *
     *  @field(driver)
     *  The driver to be used for this connection. See the {@link #Driver}
     *  enumeration for details.
     *
     *  @field(procName)
     *  The name of the remote processor for the given connection.
     *  @p
     */
    struct Connection {
        Driver driver;                  /*! notify driver */
        String procName;                /*! remote processor name */
    };

    /*!
     *  ======== connections ========
     *  Configure the notify driver for each given connection
     *
     *  Use this configuration parameter to define which notify driver
     *  is to be used when communicating with remote processors. Create
     *  one entry in this array for each connection. Each entry you create,
     *  defines the local end-point of the connection. The remote processor
     *  must have a complimentary entry in its `connections` array.
     *
     *  Any connection which is undefined, will use the shared memory
     *  notify driver. It is not necessary to define all connections, just
     *  the ones which will not use the default.
     *
     *  To define a local end-point connection, establish a reference to
     *  this module and add a new entry to this array.
     *
     *  The following example show how to setup the mailbox driver for
     *  communicating from DSP1 to EVE1 and EVE2.
     *
     *  Add the following to your DSP1 configuration script.
     *
     *  @p(code)
     *  // configure the notify driver
     *  var NotifySetup = xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
     *
     *  NotifySetup.connections.$add(
     *      new NotifySetup.Connection({
     *          driver: NotifySetup.Driver_MAILBOX,
     *          procName: "EVE1"
     *      })
     *  );
     *
     *  NotifySetup.connections.$add(
     *      new NotifySetup.Connection({
     *          driver: NotifySetup.Driver_MAILBOX,
     *          procName: "EVE2"
     *      })
     *  );
     *  @p
     *
     *  Add the following to your EVE1 configuration script.
     *
     *  @p(code)
     *  // configure the notify driver
     *  var NotifySetup = xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
     *
     *  NotifySetup.connections.$add(
     *      new NotifySetup.Connection({
     *          driver: NotifySetup.Driver_MAILBOX,
     *          procName: "DSP1"
     *      })
     *  );
     *  @p
     *
     *  Add the following to your EVE2 configuration script.
     *
     *  @p(code)
     *  // configure the notify driver
     *  var NotifySetup = xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
     *
     *  NotifySetup.connections.$add(
     *      new NotifySetup.Connection({
     *          driver: NotifySetup.Driver_MAILBOX,
     *          procName: "DSP1"
     *      })
     *  );
     *  @p
     */
    metaonly config Connection connections[length];

    /*! @_nodoc
     *  ======== plugHwi ========
     *  Register an isr for the given interrupt and event.
     *
     *  @param(remoteProcId) The MutiProc Id of the remote processor
     *  which will raise the given interrupt.
     *
     *  @param(cpuIntrNum) The interrupt number which will be raised
     *  by the remote processor.
     *
     *  @param(isr) The ISR which should be invoked to service the
     *  given interrupt.
     */
    Void plugHwi(UInt16 remoteProcId, Int cpuIntrNum, DriverIsr isr);

    /*! @_nodoc
     *  ======== unplugHwi ========
     *  Unregister the isr for the given interrupt.
     */
    Void unplugHwi(UInt16 remoteProcId, Int cpuIntrNum);

    /*! @_nodoc
     *  ======== interruptTable ========
     *  Accessor method to return interrupt id for given virtual proc id
     */
    UInt16 interruptTable(Int srcVirtId);

internal:
    /* interrupt vector id for dsp */
    config UInt dspIntVectId = 4;

    /* interrupt vector id for eve */
    config UInt eveIntVectId_INTC0 = 4;
    config UInt eveIntVectId_INTC1 = 8;

    /* total number of cores on Vayu SoC */
    const UInt8 NUM_CORES = 11;

    /* number of cores in eve subsystem */
    const UInt8 NUM_EVES = 4;

    /* number of internal eve mailboxes */
    const UInt8 NUM_EVE_MBX = 12;

    /* number of system mailboxes (used by IPC) */
    const UInt8 NUM_SYS_MBX = 4;

    /*  Mailbox table for storing encoded base address, mailbox user ID,
     *  and sub-mailbox index.
     */
    config UInt32 mailboxTable[NUM_CORES * NUM_CORES];

    /* base address table for the mailbox subsystem */
    config UInt32 mailboxBaseAddr[NUM_EVE_MBX + NUM_SYS_MBX];

    /* map procId to discrete processor/core */
    config UInt eve1ProcId = MultiProc.INVALIDID;
    config UInt eve2ProcId = MultiProc.INVALIDID;
    config UInt eve3ProcId = MultiProc.INVALIDID;
    config UInt eve4ProcId = MultiProc.INVALIDID;
    config UInt dsp1ProcId = MultiProc.INVALIDID;
    config UInt dsp2ProcId = MultiProc.INVALIDID;
    config UInt ipu1_0ProcId = MultiProc.INVALIDID;  /* also used for ipu1 */
    config UInt ipu1_1ProcId = MultiProc.INVALIDID;
    config UInt ipu2_0ProcId = MultiProc.INVALIDID;  /* also used for ipu2 */
    config UInt ipu2_1ProcId = MultiProc.INVALIDID;
    config UInt hostProcId = MultiProc.INVALIDID;

    /* map MultiProc ID to virtual ID, virtId = procIdTable[procId] */
    config UInt32 procIdTable[NUM_CORES];

    /* runtime driver binding structure */
    struct DrvBind {
        Driver driver;                  /* notify driver */
        UInt16 procId;                  /* remote processor ID */
    };

    /*
     *  ======== A_internal ========
     *  Internal implementation error.
     */
    config Assert.Id A_internal = {
        msg: "A_internal: internal implementation error"
    };

    /*
     *  ======== driverType ========
     */
    Driver driverType(UInt16 remoteProcId);

    /*
     *  ======== Shm_attach ========
     */
    Int Shm_attach(UInt16 remoteProcId, Ptr sharedAddr);

    /*
     *  ======== Shm_sharedMemReq ========
     */
    SizeT Shm_sharedMemReq(UInt16 remoteProcId, Ptr sharedAddr);

    /*
     *  ======== Mbx_attach ========
     */
    Int Mbx_attach(UInt16 remoteProcId, Ptr sharedAddr);

    /*
     *  ======== Mbx_sharedMemReq ========
     */
    SizeT Mbx_sharedMemReq(UInt16 remoteProcId, Ptr sharedAddr);

    /*
     *  ======== dispatchIsr ========
     *  Dispatch interrupt to notify driver instance.
     */
    Void dispatchIsr(UArg arg);

    /*
     *  ======== Module_State ========
     */
    struct Module_State {
        /* interrupt plug counter */
        UInt16 numPlugged[];

        /* connection array */
        DrvBind connAry[length];

        /*  Interrupt event IDs used to communicate with this processor.
         *  This table is indexed by virtual processor ID.
         */
        UInt16 interruptTable[NUM_CORES];

        /*  Notify driver isr dispatch table. This table is indexed
         *  by virtual processor ID.
         */
        DriverIsr isrDispatchTable[NUM_CORES];
    };
}
