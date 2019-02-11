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
    var TableInit = xdc.useModule("ti.sdo.ipc.family.vayu.TableInit");
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
    else if (isaChain.match(/#v7A#/)) {
        Mmu = xdc.useModule("ti.sysbios.family.arm.a15.Mmu");
        xdc.useModule('ti.sysbios.family.arm.gic.Hwi');
        xdc.useModule('ti.sysbios.family.shared.vayu.IntXbar');
    }

    /* initialize procIdTable */
    TableInit.initProcId(this);

    /* initialize mailboxTable */
    TableInit.generateTable(this);

    if (isaChain.match(/#64P#|#v7A#/)) {
        /* initialize mailbox base address table */
        this.mailboxBaseAddr[0]  = 0x4208B000;  /* EVE1 Internal Mailbox 0 */
        this.mailboxBaseAddr[1]  = 0x4208C000;  /* EVE1 Internal Mailbox 1 */
        this.mailboxBaseAddr[2]  = 0x4208D000;  /* EVE1 Internal Mailbox 2 */
        this.mailboxBaseAddr[3]  = 0x4218B000;  /* EVE2 Internal Mailbox 0 */
        this.mailboxBaseAddr[4]  = 0x4218C000;  /* EVE2 Internal Mailbox 1 */
        this.mailboxBaseAddr[5]  = 0x4218D000;  /* EVE2 Internal Mailbox 2 */
        this.mailboxBaseAddr[6]  = 0x4228B000;  /* EVE3 Internal Mailbox 0 */
        this.mailboxBaseAddr[7]  = 0x4228C000;  /* EVE3 Internal Mailbox 1 */
        this.mailboxBaseAddr[8]  = 0x4228D000;  /* EVE3 Internal Mailbox 2 */
        this.mailboxBaseAddr[9]  = 0x4238B000;  /* EVE4 Internal Mailbox 0 */
        this.mailboxBaseAddr[10] = 0x4238C000;  /* EVE4 Internal Mailbox 1 */
        this.mailboxBaseAddr[11] = 0x4238D000;  /* EVE4 Internal Mailbox 2 */
        this.mailboxBaseAddr[12] = 0x48840000;  /* System Mailbox 5 */
        this.mailboxBaseAddr[13] = 0x48842000;  /* System Mailbox 6 */
        this.mailboxBaseAddr[14] = 0x48844000;  /* System Mailbox 7 */
        this.mailboxBaseAddr[15] = 0x48846000;  /* System Mailbox 8 */
    }
    else if (isaChain.match(/#arp32#/)) {
        this.mailboxBaseAddr[0]  = 0x4008B000;  /* EVE1 Internal Mailbox 0 */
        this.mailboxBaseAddr[1]  = 0x4008C000;  /* EVE1 Internal Mailbox 1 */
        this.mailboxBaseAddr[2]  = 0x4208D000;  /* EVE1 Internal Mailbox 2 */
        this.mailboxBaseAddr[3]  = 0x4008B000;  /* EVE2 Internal Mailbox 0 */
        this.mailboxBaseAddr[4]  = 0x4008C000;  /* EVE2 Internal Mailbox 1 */
        this.mailboxBaseAddr[5]  = 0x4218D000;  /* EVE2 Internal Mailbox 2 */
        this.mailboxBaseAddr[6]  = 0x4008B000;  /* EVE3 Internal Mailbox 0 */
        this.mailboxBaseAddr[7]  = 0x4008C000;  /* EVE3 Internal Mailbox 1 */
        this.mailboxBaseAddr[8]  = 0x4228D000;  /* EVE3 Internal Mailbox 2 */
        this.mailboxBaseAddr[9]  = 0x4008B000;  /* EVE4 Internal Mailbox 0 */
        this.mailboxBaseAddr[10] = 0x4008C000;  /* EVE4 Internal Mailbox 1 */
        this.mailboxBaseAddr[11] = 0x4238D000;  /* EVE4 Internal Mailbox 2 */
        this.mailboxBaseAddr[12] = 0x48840000;  /* System Mailbox 5 */
        this.mailboxBaseAddr[13] = 0x48842000;  /* System Mailbox 6 */
        this.mailboxBaseAddr[14] = 0x48844000;  /* System Mailbox 7 */
        this.mailboxBaseAddr[15] = 0x48846000;  /* System Mailbox 8 */

        /* each EVE receives its message using the local mailbox address */
        if (MultiProc.id == this.eve1ProcId) {
            this.mailboxBaseAddr[2] = 0x4008D000;
        }
        else if (MultiProc.id == this.eve2ProcId) {
            this.mailboxBaseAddr[5] = 0x4008D000;
        }
        else if (MultiProc.id == this.eve3ProcId) {
            this.mailboxBaseAddr[8] = 0x4008D000;
        }
        else if (MultiProc.id == this.eve4ProcId) {
            this.mailboxBaseAddr[11] = 0x4008D000;
        }
    }
    else if (isaChain.match(/#v7M#/)) {
        /* initialize mailbox base address table */
        if (this.mailboxBaseAddr[0] == undefined) {
            this.mailboxBaseAddr[0]  = 0x6208B000;  /* EVE1 MBOX0 */
        }
        if (this.mailboxBaseAddr[1] == undefined) {
            this.mailboxBaseAddr[1]  = 0x6208C000;  /* EVE1 MBOX1 */
        }
        if (this.mailboxBaseAddr[2] == undefined) {
            this.mailboxBaseAddr[2]  = 0;           /* EVE1 MBOX2 */
        } else {
            this.$logWarning("NotifySetup.mailboxBaseAddr[2] is EVE1 MBOX2, "
                    + "which is not used for IPU communication and should "
                    + "not be configured.", this);
        }
        if (this.mailboxBaseAddr[3] == undefined) {
            this.mailboxBaseAddr[3]  = 0x6218B000;  /* EVE2 MBOX0 */
        }
        if (this.mailboxBaseAddr[4] == undefined) {
            this.mailboxBaseAddr[4]  = 0x6218C000;  /* EVE2 MBOX1 */
        }
        if (this.mailboxBaseAddr[5] == undefined) {
            this.mailboxBaseAddr[5]  = 0;           /* EVE2 MBOX2 */
        } else {
            this.$logWarning("NotifySetup.mailboxBaseAddr[5] is EVE2 MBOX2, "
                    + "which is not used for IPU communication and should "
                    + "not be configured.", this);
        }

        if (this.mailboxBaseAddr[6] == undefined) {
            this.mailboxBaseAddr[6]  = 0x6228B000;  /* EVE3 MBOX0 */
        }
        if (this.mailboxBaseAddr[7] == undefined) {
            this.mailboxBaseAddr[7]  = 0x6228C000;  /* EVE3 MBOX1 */
        }
        if (this.mailboxBaseAddr[8] == undefined) {
            this.mailboxBaseAddr[8]  = 0;           /* EVE3 MBOX2 */
        } else {
            this.$logWarning("NotifySetup.mailboxBaseAddr[8] is EVE3 MBOX2, "
                    + "which is not used for IPU communication and should "
                    + "not be configured.", this);
        }

        if (this.mailboxBaseAddr[9] == undefined) {
            this.mailboxBaseAddr[9]  = 0x6238B000;  /* EVE4 MBOX0 */
        }
        if (this.mailboxBaseAddr[10] == undefined) {
            this.mailboxBaseAddr[10]  = 0x6238C000; /* EVE4 MBOX1 */
        }
        if (this.mailboxBaseAddr[11] == undefined) {
            this.mailboxBaseAddr[11]  = 0;          /* EVE4 MBOX2 */
        } else {
            this.$logWarning("NotifySetup.mailboxBaseAddr[11] is EVE4 MBOX2, "
                    + "which is not used for IPU communication and should "
                    + "not be configured.", this);
        }

        if (this.mailboxBaseAddr[12] == undefined) {
            this.mailboxBaseAddr[12] = 0x68840000;  /* System Mailbox 5 */
        }
        if (this.mailboxBaseAddr[13] == undefined) {
            this.mailboxBaseAddr[13] = 0x68842000;  /* System Mailbox 6 */
        }
        if (this.mailboxBaseAddr[14] == undefined) {
            this.mailboxBaseAddr[14] = 0x68844000;  /* System Mailbox 7 */
        }
        if (this.mailboxBaseAddr[15] == undefined) {
            this.mailboxBaseAddr[15] = 0x68846000;  /* System Mailbox 8 */
        }
    }
    else {
        throw("Invalid target: " + Program.build.target.$name);
    }

    if (isaChain.match(/#v7A#/)) {
        /*  Add mailbox addresses to the Mmu table.
         *  Force mailbox addresses to be NON cacheable.
         */
        var peripheralAttrs = {
            type : Mmu.DescriptorType_BLOCK,  // BLOCK descriptor
            accPerm    : 0,                   // read/write at PL1
            noExecute  : true,                // not executable
            attrIndx   : 1                    // MAIR0 Byte1 describes mem attr
        };

        /* configure the corresponding MMU page descriptor */
        Mmu.setSecondLevelDescMeta(0x42000000, 0x42000000, peripheralAttrs);
        Mmu.setSecondLevelDescMeta(0x42200000, 0x42200000, peripheralAttrs);
        Mmu.setSecondLevelDescMeta(0x48800000, 0x48800000, peripheralAttrs);
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
            xdc.useModule('ti.sdo.ipc.family.vayu.NotifyDriverMbx');
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
        state.interruptTable[0] = 55; /* EVE1 -> DSP1 or DSP2 */
        state.interruptTable[1] = 56; /* EVE2 -> DSP1 or DSP2 */
        state.interruptTable[2] = 58; /* EVE3 -> DSP1 or DSP2 */
        state.interruptTable[3] = 59; /* EVE4 -> DSP1 or DSP2 */
        state.interruptTable[4] = 60; /* DSP1 -> DSP2 */
        state.interruptTable[5] = 60; /* DSP2 -> DSP1 */
        state.interruptTable[8] = 57; /* HOST -> DSP1 or DSP2 */

        /* these are not known at config time, set at runtime */
        state.interruptTable[6] = 0; /* IPU1 -> DSP1 or DSP2 */
        state.interruptTable[7] = 0; /* IPU2 -> DSP1 or DSP2 */
        state.interruptTable[9] = 0; /* IPU1-1 -> DSP1 or DSP2 */
        state.interruptTable[10] = 0; /* IPU2-1 -> DSP1 or DSP2 */
    }
    else if (isaChain.match(/#arp32#/)) {
        state.numPlugged.length = this.NUM_EVE_MBX / this.NUM_EVES;
        for (var i = 0; i < state.numPlugged.length; i++) {
            state.numPlugged[i] = 0;
        }

        /* interrupt event IDs used by this processor */
        state.interruptTable[0] = 60; /* EVE1 - Group1/INTC1 */
        state.interruptTable[1] = 60; /* EVE2 - Group1/INTC1 */
        state.interruptTable[2] = 60; /* EVE3 - Group1/INTC1 */
        state.interruptTable[3] = 60; /* EVE4 - Group1/INTC1 */
        state.interruptTable[4] = 29; /* DSP1 - Group0/INTC0 */
        state.interruptTable[5] = 30; /* DSP2 - Group0/INTC0 */
        state.interruptTable[6] = 29; /* IPU1-0 */
        state.interruptTable[7] = 30; /* IPU2-0 */
        state.interruptTable[8] = 29; /* HOST */
        state.interruptTable[9] = 30; /* IPU1-1 */
        state.interruptTable[10] = 30; /* IPU2-1 */
    }
    else if (isaChain.match(/#v7M#/)) {
        state.numPlugged.length = mod.NUM_EVE_MBX + mod.NUM_SYS_MBX;
        for (var i = 0; i < state.numPlugged.length; i++) {
            state.numPlugged[i] = 0;
        }

        if (Core.id == 0) {
            /* interrupt event IDs used by this processor */
            state.interruptTable[0] = 64; /* EVE1 */
            state.interruptTable[1] = 65; /* EVE2 */
            state.interruptTable[2] = 67; /* EVE3 */
            state.interruptTable[3] = 68; /* EVE4 */

            if (Core.ipuId == 1) { /* IPU1-0 */
                state.interruptTable[4] = 66;  /* DSP1 */
                state.interruptTable[5] = 69;  /* DSP2 */
                state.interruptTable[6] = 0;   /* IPU1-0 */
                state.interruptTable[7] = 69;  /* Ipu2-0 */
                state.interruptTable[8] = 66;  /* HOST */
                var mbxDrv = isMbxDrv(mod, "IPU1-1");
                state.interruptTable[9] = mbxDrv ? 69 : 19;  /* IPU1-1 */
                state.interruptTable[10] = 70; /* Ipu2-1 */
            }
            else { /* IPU2-0 */
                state.interruptTable[4] = 69;  /* DSP1 */
                state.interruptTable[5] = 66;  /* DSP2 */
                state.interruptTable[6] = 69;  /* IPU1-0 */
                state.interruptTable[7] = 0;   /* Ipu2-0 */
                state.interruptTable[8] = 66;  /* HOST */
                state.interruptTable[9] = 70;  /* IPU1-1 */
                state.interruptTable[10] = 19; /* Ipu2-1 */
            }
        }
        else {
            /* interrupt event IDs used by this processor */
            state.interruptTable[0] = 71; /* EVE1 */
            state.interruptTable[1] = 72; /* EVE2 */
            state.interruptTable[2] = 74; /* EVE3 */
            state.interruptTable[3] = 75; /* EVE4 */

            if (Core.ipuId == 1) { /* IPU1-1 */
                state.interruptTable[4] = 73;  /* DSP1 */
                state.interruptTable[5] = 76;  /* DSP2 */
                var mbxDrv = isMbxDrv(mod, "IPU1-0");
                state.interruptTable[6] = mbxDrv ? 76 : 19;  /* IPU1-0 */
                state.interruptTable[7] = 76;  /* Ipu2-0 */
                state.interruptTable[8] = 73;  /* HOST */
                state.interruptTable[9] = 0;   /* IPU1-1 */
                state.interruptTable[10] = 0;  /* Ipu2-1 */
            }
            else { /* IPU2-1 */
                state.interruptTable[4] = 76;  /* DSP1 */
                state.interruptTable[5] = 73;  /* DSP2 */
                state.interruptTable[6] = 76;  /* IPU1-0 */
                state.interruptTable[7] = 19;  /* Ipu2-0 */
                state.interruptTable[8] = 73;  /* HOST */
                state.interruptTable[9] = 0;   /* IPU1-1 */
                state.interruptTable[10] = 0;  /* Ipu2-1 */
            }
        }
    }
    else if (isaChain.match(/#v7A#/)) {
        state.numPlugged.length = mod.NUM_EVE_MBX + mod.NUM_SYS_MBX;
        for (var i = 0; i < state.numPlugged.length; i++) {
            state.numPlugged[i] = 0;
        }

        /* obtained by looking at MPU IRQ + 32 */
        state.interruptTable[0] = 134 + 32;   /* EVE1 */
        state.interruptTable[1] = 135 + 32;   /* EVE2 */
        state.interruptTable[2] = 137 + 32;   /* EVE3 */
        state.interruptTable[3] = 138 + 32;   /* EVE4 */
        state.interruptTable[4] = 136 + 32;   /* DSP1 */
        state.interruptTable[5] = 141 + 32;   /* DSP2 */
        state.interruptTable[6] = 136 + 32;   /* IPU1-0 */
        state.interruptTable[7] = 141 + 32;   /* IPU2-0 */
        state.interruptTable[8] = 0;          /* HOST */
        state.interruptTable[9] = 136 + 32;   /* IPU1-1 */
        state.interruptTable[10] = 141 + 32;  /* IPU2-1 */
    }
    else {
        throw("Invalid target: " + Program.build.target.$name);
    }

    /* initialize the driver table */
    for (var i = 0; i < state.isrDispatchTable.length; i++) {
        state.isrDispatchTable[i] = null;
    }
}
