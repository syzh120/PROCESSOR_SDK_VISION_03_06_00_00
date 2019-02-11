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
 *  ======== Interrupt.xs ========
 */

var isaChain = "";
var deviceSettings = {
    /* all Keystone II devices inherit from TCI6634 */
    'TMS320TCI6634' : {
        IPCGR0:         0x02620240,
        IPCAR0:         0x02620280,
        IPCGRH:         0x02620260,
        IPCARH:         0x026202A0,
        KICK0:          0x02620038,
        KICK1:          0x0262003C,
        INTERDSPINT:    105,
        IPCHOSTINT:     4
    },
    'TCI66AK2G02' : {
        IPCGR0:         0x02620240,
        IPCAR0:         0x02620280,
        IPCGRH:         0x02620260,
        IPCARH:         0x026202A0,
        KICK0:          0x02620038,
        KICK1:          0x0262003C,
        INTERDSPINT:    8,
        IPCHOSTINT:     1
    }

};

var Settings = xdc.loadCapsule('ti/sdo/ipc/family/Settings.xs');
Settings.setDeviceAliases(deviceSettings, Settings.deviceAliases);

var MultiProc;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    /* concatinate isa chain into single string for easier matching */
    isaChain = "#" + Program.build.target.getISAChain().join("#") + "#";

    var settings = deviceSettings[Program.cpu.deviceName];

    this.IPCGR0         = settings.IPCGR0;
    this.IPCAR0         = settings.IPCAR0;
    this.IPCGRH         = settings.IPCGRH;
    this.IPCARH         = settings.IPCARH;
    this.KICK0          = settings.KICK0;
    this.KICK1          = settings.KICK1;
    if (isaChain.match(/#64P#/)) {
        this.INTERDSPINT    = settings.INTERDSPINT;
    }
    else if (isaChain.match(/#v7A#/)) {
        this.INTERDSPINT    = settings.IPCHOSTINT;
    }
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    xdc.useModule("ti.sysbios.hal.Hwi");
    xdc.useModule("ti.sdo.ipc.family.tci663x.MultiProcSetup");

    MultiProc = xdc.useModule("ti.sdo.utils.MultiProc");

    /*  Hack: fix conflict between NotifyDriverCirc and VirtQueue.
     *
     *  If both of these modules are in the configuration, then instruct
     *  the NotifyCircSetup module to exclude the host during the IPC
     *  attach phase.
     */
    var ncsName = this.$package.$name + ".NotifyCircSetup";
    var vqName = "ti.ipc.family.tci6638.VirtQueue";

    var notifySetup = ((ncsName in xdc.om) && xdc.module(ncsName).$used);
    var virtQue = ((vqName in xdc.om) && xdc.module(vqName).$used);

    if (notifySetup && virtQue) {
        xdc.module(ncsName).includeHost = false;
    }
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(state, mod)
{
    state.numPlugged = 0;
    state.baseId = MultiProc.baseIdOfCluster;
    state.hwi = null;

    /* initialize client function table */
    state.clientTab.length = MultiProc.numProcsInCluster;

    for (var i = 0; i < state.clientTab.length; i++) {
        state.clientTab[i].func = null;
        state.clientTab[i].arg = -1;
    }

    /* initialize ipcar source bit mapping */
    state.hwTab.length = MultiProc.numProcsInCluster;

    for (var i = 0; i < state.hwTab.length; i++) {
        var name = MultiProc.nameList[i];

        if (name == "HOST") {
            state.hwTab[i].dnum = MultiProc.INVALIDID;
            /* by convention, host is bit 31 in ipcgr and ipcar registers */
            state.hwTab[i].srcsx = 31;
        }
        else {
            /* the numeric part of the name string determines the coreId */
            var coreId = Number(name.substring("CORE".length));
            state.hwTab[i].dnum = coreId;
            state.hwTab[i].srcsx = coreId + mod.SRCSx_SHIFT;
        }
    }
}

/*
 *************************************************************************
 *                       ROV View functions
 *************************************************************************
 */

/*
 *  ======== viewInterruptsData ========
 *  Module data view
 */
function viewInterruptsData(view)
{
    var Interrupt       = xdc.useModule('ti.sdo.ipc.family.tci663x.Interrupt');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');
    var MultiProc       = xdc.useModule('ti.sdo.utils.MultiProc');

    /* Retrieve the module state. */
    var rawView = Program.scanRawView('ti.sdo.ipc.family.tci663x.Interrupt');
    var mod = rawView.modState;
    /* Retrieve the module configuration. */
    var modCfg = Program.getModuleConfig('ti.sdo.ipc.family.tci663x.Interrupt');
    var MultiProcCfg = Program.getModuleConfig('ti.sdo.utils.MultiProc');

    var clientTab = Program.fetchArray(Interrupt.clientTab$fetchDesc,
            mod.clientTab, MultiProcCfg.numProcessors);

    var localId = MultiProc.self$view();

    if (localId != MultiProc.INVALIDID) {
        var ipcar0 = Program.fetchArray(ScalarStructs.S_Bits32$fetchDesc,
            $addr(modCfg.IPCAR0), MultiProcCfg.numProcessors, false);
    }

    for (var i = 0; i < MultiProcCfg.numProcsInCluster; i++) {
        var entryView =
                Program.newViewStruct('ti.sdo.ipc.family.tci663x.Interrupt',
                'Registered Interrupts');

        entryView.remoteCoreId = MultiProc.baseIdOfCluster + i;

        var fxn = Number(clientTab[i].func);
        if (fxn != 0) {
            entryView.isrFxn = Program.lookupFuncName(fxn)[0];
            entryView.isrArg = "0x" + Number(clientTab[i].arg).toString(16);
        }
        else {
            entryView.isrFxn = "(unplugged)";
            entryView.isrArg = "";
        }

        if (localId != MultiProc.INVALIDID) {
            var enableFlag = ipcar0[localId].elem;

            if (enableFlag & (1 << (i + Interrupt.SRCSx_SHIFT))) {
                entryView.isFlagged = true;
            }
            else {
                entryView.isFlagged = false;
            }
        }

        view.elements.$add(entryView);
    }
}
