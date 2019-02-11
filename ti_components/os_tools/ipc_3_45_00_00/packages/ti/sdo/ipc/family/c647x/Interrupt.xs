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
 *  ======== Interrupt.xs ========
 */

var deviceSettings = {
    'TMS320C6472' : {
        IPCGR0:         0x02A80540,
        IPCAR0:         0x02A80580,
        KICK0:          0,
        KICK1:          0,
        INTERDSPINT:    84,
    },
    'TMS320C6474' : {
        IPCGR0:         0x02880900,
        IPCAR0:         0x02880940,
        KICK0:          0,
        KICK1:          0,
        INTERDSPINT:    76,
    },
    'TMS320C6670' : {
        IPCGR0:         0x02620240,
        IPCAR0:         0x02620280,
        KICK0:          0x02620038,
        KICK1:          0x0262003C,
        INTERDSPINT:    90,
    },
    'TMS320C6678' : {
        IPCGR0:         0x02620240,
        IPCAR0:         0x02620280,
        KICK0:          0x02620038,
        KICK1:          0x0262003C,
        INTERDSPINT:    91,
    },
    'Kepler' : {
        IPCGR0:         0x02620240,
        IPCAR0:         0x02620280,
        KICK0:          0x02620038,
        KICK1:          0x0262003C,
        INTERDSPINT:    90,
    },
}
var Settings = xdc.loadCapsule('ti/sdo/ipc/family/Settings.xs');
Settings.setDeviceAliases(deviceSettings, Settings.deviceAliases);

var Hwi;
var Interrupt;
var Ipc;
var MultiProc;
var SharedRegion;
var MultiProcSetup;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    var settings = deviceSettings[Program.cpu.deviceName];

    this.IPCGR0         = settings.IPCGR0;
    this.IPCAR0         = settings.IPCAR0;
    this.KICK0          = settings.KICK0;
    this.KICK1          = settings.KICK1;
    this.INTERDSPINT    = settings.INTERDSPINT;
}


/*
 *  ======== module$use ========
 */
function module$use()
{
    Interrupt       = this;
    Hwi             = xdc.useModule("ti.sysbios.family.c64p.Hwi");
    Ipc             = xdc.useModule("ti.sdo.ipc.Ipc");
    MultiProc       = xdc.useModule("ti.sdo.utils.MultiProc");
    SharedRegion    = xdc.useModule("ti.sdo.ipc.SharedRegion");
    MultiProcSetup  = xdc.useModule("ti.sdo.ipc.family.c647x.MultiProcSetup");
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    var args = Interrupt.$object.args;
    var MultiProc = xdc.module('ti.sdo.utils.MultiProc');

    /* The function table length should be the number of processors */
    args.length = MultiProc.numProcessors;
    for (var i = 0; i < args.length; i++) {
        args[i] = 0;
    }

    mod.func = null;
    mod.numPlugged = 0;
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
    var Interrupt       = xdc.useModule('ti.sdo.ipc.family.c647x.Interrupt');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');
    var MultiProc       = xdc.useModule('ti.sdo.utils.MultiProc');

    /* Retrieve the module state. */
    var rawView = Program.scanRawView('ti.sdo.ipc.family.c647x.Interrupt');
    var mod = rawView.modState;
    /* Retrieve the module configuration. */
    var modCfg = Program.getModuleConfig('ti.sdo.ipc.family.c647x.Interrupt');
    var MultiProcCfg = Program.getModuleConfig('ti.sdo.utils.MultiProc');

    var args = Program.fetchArray(Interrupt.args$fetchDesc,
                                  mod.args,
                                  MultiProcCfg.numProcessors);

    var localId = MultiProc.self$view();

    if (localId != MultiProc.INVALIDID) {
        var ipcar0 = Program.fetchArray(ScalarStructs.S_Bits32$fetchDesc,
            $addr(modCfg.IPCAR0), MultiProcCfg.numProcessors, false);
    }

    for (var i = 0; i < MultiProcCfg.numProcessors; i++) {
        var entryView =
                Program.newViewStruct('ti.sdo.ipc.family.c647x.Interrupt',
                'Registered Interrupts');
        entryView.remoteCoreId = i;
        if (Number(mod.func) != 0) {
            entryView.isrFxn =
                    Program.lookupFuncName(Number(mod.func))[0];
            entryView.isrArg = "0x" + Number(args[i]).toString(16);
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
