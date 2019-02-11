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
 *  ======== NotifySetup.xs ========
 */
var MultiProc = null;
var Core = null;
var Mmu = null;
var isaChain = "";

/*
 *  ======== isMbxDrv ========
 */
function isMbxDrv(mod, name)
{
    if (mod.connections == undefined) {
        return (false);
    }

    for (var i = 0; i < mod.connections.length; i++) {
        if (mod.connections[i].procName == name) {
            if (mod.connections[i].driver == mod.Driver_MAILBOX) {
                return (true);
            }
            else {
                return (false);
            }
        }
    }

    return (false);
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    /* load modules needed in meta domain and in target domain */
    var TableInit = xdc.useModule("ti.sdo.ipc.family.tda3xx.TableInit");
    MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Error');
    xdc.useModule('xdc.runtime.Startup');

    /* concatinate isa chain into single string for easier matching */
    isaChain = "#" + Program.build.target.getISAChain().join("#") + "#";

    if (isaChain.match(/#64P#/)) {
        xdc.useModule('ti.sysbios.family.c64p.EventCombiner');
        xdc.useModule('ti.sysbios.family.c64p.Hwi');
        xdc.useModule('ti.sysbios.family.shared.vayu.IntXbar');
    }
    else if (isaChain.match(/#arp32#/)) {
        xdc.useModule('ti.sysbios.family.arp32.Hwi');
    }
    else if (isaChain.match(/#v7M#/)) {
        xdc.useModule("ti.sysbios.BIOS");
        Core = xdc.useModule("ti.sysbios.family.arm.ducati.Core");
        xdc.useModule('ti.sysbios.family.arm.m3.Hwi');
        xdc.useModule('ti.sysbios.family.shared.vayu.IntXbar');
    }

    /* initialize procIdTable */
    TableInit.initProcId(this);

    /* initialize mailboxTable */
    TableInit.generateTable(this);

    if (isaChain.match(/#64P#/)) {
        /* initialize mailbox base address table */
        this.mailboxBaseAddr[0] = 0x4208B000;   /* EVE1 Mailbox 0 */
        this.mailboxBaseAddr[1] = 0x4208C000;   /* EVE1 Mailbox 1 */
        this.mailboxBaseAddr[2] = 0x4883A000;   /* System Mailbox 2 */
    }
    else if (isaChain.match(/#arp32#/)) {
        this.mailboxBaseAddr[0] = 0x4008B000;   /* EVE1 Mailbox 0 */
        this.mailboxBaseAddr[1] = 0x4008C000;   /* EVE1 Mailbox 1 */
        this.mailboxBaseAddr[2] = 0x4883A000;   /* System Mailbox 2 */
    }
    else if (isaChain.match(/#v7M#/)) {
        /* initialize mailbox base address table */
        if (this.mailboxBaseAddr[0] == undefined) {
            this.mailboxBaseAddr[0] = 0x6208B000;   /* EVE1 Mailbox 0 */
        }
        if (this.mailboxBaseAddr[1] == undefined) {
            this.mailboxBaseAddr[1] = 0x6208C000;   /* EVE1 Mailbox 1 */
        }
        if (this.mailboxBaseAddr[2] == undefined) {
            this.mailboxBaseAddr[2] = 0x6883A000;   /* System Mailbox 2 */
        }
    }
    else {
        throw("Invalid target: " + Program.build.target.$name);
    }

    /* determine which notify drivers to include */
    this.$private.driverMask = 0;

    /* for unspecfied connections, the default is shared memory */
    if (this.connections.length < (MultiProc.numProcessors - 1)) {
        this.$private.driverMask |= this.Driver_SHAREDMEMORY;
    }

    /* remember which notify drivers have been specified */
    for (var i = 0; i < this.connections.length; i++) {
        if (this.connections[i].driver == this.Driver_SHAREDMEMORY) {
            this.$private.driverMask |= this.Driver_SHAREDMEMORY;
        }
        if (this.connections[i].driver == this.Driver_MAILBOX) {
            this.$private.driverMask |= this.Driver_MAILBOX;
        }
    }

    /*  If Notify module is already used, then load notify drivers into
     *  configuration model. Do *not* useModule the Notify module. Some
     *  applications require this notify driver but do *not* want the
     *  ti.sdo.ipc package to be loaded.
     */
    if (xdc.module('ti.sdo.ipc.Notify').$used) {
        if (this.$private.driverMask & this.Driver_SHAREDMEMORY) {
            xdc.useModule('ti.sdo.ipc.notifyDrivers.NotifyDriverShm');
        }
        if (this.$private.driverMask & this.Driver_MAILBOX) {
            xdc.useModule('ti.sdo.ipc.family.tda3xx.NotifyDriverMbx');
        }
    }
}

/*
 *  ======== module$static$init ========
 *  Initialize the target state object.
 */
function module$static$init(state, mod)
{
    var procId;

    /*  Initialize the state connAry from the config params. Translate
     *  processor names into IDs for better runtime performance.
     */
    state.connAry.length = mod.connections.length;

    for (var i = 0; i < mod.connections.length; i++) {
        procId = MultiProc.getIdMeta(mod.connections[i].procName);
        state.connAry[i].procId = procId;
        state.connAry[i].driver = mod.connections[i].driver;
    }

    if (isaChain.match(/#64P#/)) {
        state.numPlugged.length = 1;
        for (var i = 0; i < state.numPlugged.length; i++) {
            state.numPlugged[i] = 0;
        }

        /* interrupt event IDs used by this processor */
        state.interruptTable[0] = 71; /* DSP1   -> DSP2 */
        state.interruptTable[1] = 71; /* DSP2   -> DSP1 */
        state.interruptTable[2] = 71; /* IPU1   -> DSP1 or DSP2 */
        state.interruptTable[3] = 71; /* IPU1-1 -> DSP1 or DSP2 */
        state.interruptTable[4] = 72; /* EVE1 -  > DSP1 or DSP2 */
    }
    else if (isaChain.match(/#arp32#/)) {
        state.numPlugged.length = this.NUM_EVE_MBX / this.NUM_EVES;
        for (var i = 0; i < state.numPlugged.length; i++) {
            state.numPlugged[i] = 0;
        }

        /* interrupt event IDs used by this processor */
        state.interruptTable[0] = 29; /* DSP1   -> Group0/INTC0 */
        state.interruptTable[1] = 29; /* DSP2   -> Group0/INTC0 */
        state.interruptTable[2] = 29; /* IPU1-0 -> Group0/INTC0 */
        state.interruptTable[3] = 30; /* IPU1-1 -> Group0/INTC0 */
        state.interruptTable[4] = 0;  /* unused */
    }
    else if (isaChain.match(/#v7M#/)) {
        state.numPlugged.length = mod.NUM_EVE_MBX + mod.NUM_SYS_MBX;
        for (var i = 0; i < state.numPlugged.length; i++) {
            state.numPlugged[i] = 0;
        }

        if (Core.id == 0) {
            /* interrupt event IDs used by this processor */
            state.interruptTable[0] = 55; /* DSP1 */
            state.interruptTable[1] = 55; /* DSP2 */
            state.interruptTable[2] = 0;  /* IPU1-0 (unused) */
            var mbxDrv = isMbxDrv(mod, "IPU1-1");
            state.interruptTable[3] = mbxDrv ? 55 : 19; /* IPU1-1 */
            state.interruptTable[4] = 62; /* EVE1 */
        }
        else {
            /* interrupt event IDs used by this processor */
            state.interruptTable[0] = 56; /* DSP1 */
            state.interruptTable[1] = 56; /* DSP2 */
            var mbxDrv = isMbxDrv(mod, "IPU1-0");
            state.interruptTable[2] = mbxDrv ? 56 : 19; /* IPU1-1 */
            state.interruptTable[3] = 0;  /* IPU1-1 (unused) */
            state.interruptTable[4] = 63; /* EVE1 */
        }
    }
    else {
        throw("Invalid target: " + Program.build.target.$name);
    }

    /* initialize the driver table */
    for (var i = 0; i < state.isrDispatchTable.length; i++) {
        state.isrDispatchTable[i] = null;
    }
}
