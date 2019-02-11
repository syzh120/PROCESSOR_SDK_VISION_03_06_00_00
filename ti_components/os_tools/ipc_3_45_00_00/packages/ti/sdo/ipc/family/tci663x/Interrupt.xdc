/*
 * Copyright (c) 2014-2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== Interrupt.xdc ========
 */
package ti.sdo.ipc.family.tci663x;

import xdc.rov.ViewInfo;
import xdc.runtime.Assert;
import ti.sysbios.hal.Hwi;

/*!
 *  ======== Interrupt ========
 *  TCI663x based interrupt manager
 */
@ModuleStartup

module Interrupt inherits ti.sdo.ipc.notifyDrivers.IInterrupt
{

    /*! Return value from Interrupt_intClear() when procId != HOST
     *
     *  When acknowledging an interrupt from the host, the IPCGR register
     *  value is returned as the payload. For all other processors,
     *  Interrupt_INVALIDPAYLOAD is returned.
     */
    const UInt INVALIDPAYLOAD = 0xFFFFFFFF;

    /*!
     *  ======== enableKick ========
     *  If set to 'true' IPC will unlock the KICK registers on C66x devices
     *
     *  IPC unlocks the KICK registers on the local core if the local
     *  core is CORE0.
     */
    config Bool enableKick = true;

    /*! cpu interrupt number for IPC */
    config UInt ipcIntr = 5;

    /*! Host processor must be first in MultiProc name list
     *
     *  If the host processor is present in the MultiProc name list,
     *  it must be listed as the first member. The internal implementation
     *  depends on this ordering.
     */
    config Assert.Id A_hostConfig  = {
        msg: "A_hostConfig: HOST must be first in MultiProc name list"
    };

    /*! The cluster base ID has not been set
     *
     *  The cluster base ID must be set either by the configuration script
     *  or during the startup phase by a user defined function. This assert
     *  indicates neither has been done.
     */
    config Assert.Id A_clusterBaseId  = {
        msg: "A_clusterBaseId: cluster base ID has not been set"
    };

    /* @_nodoc */
    metaonly struct InterruptDataStruct {
        UInt    remoteCoreId;
        String  isrFxn;
        String  isrArg;
        Bool    isFlagged;
    }

    /*!
     *  ======== rovViewInfo ========
     */
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Registered Interrupts',
                    {
                        type: ViewInfo.MODULE_DATA,
                        viewInitFxn: 'viewInterruptsData',
                        structName: 'InterruptDataStruct'
                    }
                ]
            ]
        });

internal:

    /* Shift value used for setting/identifying interrupt source */
    const UInt SRCSx_SHIFT = 4;

    /* Ptr to the IPC Generation Registers */
    config Ptr IPCGR0;

    /* Ptr to the IPC Acknowledgment Registers */
    config Ptr IPCAR0;

    /* Ptr to the IPC Host Generation Host Register */
    config Ptr IPCGRH;

    /* Ptr to the IPC Acknowledgement Host Register */
    config Ptr IPCARH;

    /* Ptr to the KICK0 Bootcfg Registers */
    config Ptr KICK0;

    /* Ptr to the KICK1 Bootcfg Registers */
    config Ptr KICK1;

    /* Inter-processor interrupt id (varies per device) */
    config UInt INTERDSPINT;

    /* client table entry */
    struct ClientEntry {
        Fxn    func;            /* client function */
        UArg   arg;             /* client argument */
    };

    /* hardware configuration data */
    struct HwCfg {
        UInt        dnum;           /* DNUM value */
        UInt        srcsx;          /* source bit position */
    };

    /*
     *  ======== isr ========
     *  Stub function plugged as interrupt handler
     */
    Void isr(UArg arg);

    /*
     *  ======== Module_State ========
     *  Define the module state structure
     */
    struct Module_State {
        UInt        numPlugged;     /* # of times interrupt was registered */
        UInt16      baseId;         /* cluster base procId */
        Hwi.Handle  hwi;            /* Hwi object for ipc interrupt */
        ClientEntry clientTab[];    /* index by clusterId */
        HwCfg       hwTab[];        /* index by clusterId */
    };
}
