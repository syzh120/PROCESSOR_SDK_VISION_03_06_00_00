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
 *  ======== NotifyDriverMbx.xs ================
 */

var NotifyDriverMbx = null;
var MultiProc       = null;
var Notify          = null;
var Hwi             = null;
var Core            = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    NotifyDriverMbx = this;
    MultiProc       = xdc.useModule("ti.sdo.utils.MultiProc");
    Notify          = xdc.useModule("ti.sdo.ipc.Notify");
    Hwi             = xdc.useModule("ti.sysbios.hal.Hwi");

    if (Program.build.target.$name.match(/M3/)) {
        Core = xdc.useModule("ti.sysbios.family.arm.ducati.Core");
    }

    this.dspProcId      = MultiProc.getIdMeta("DSP");
    this.videoProcId    = MultiProc.getIdMeta("VIDEO-M3");
    this.vpssProcId     = MultiProc.getIdMeta("VPSS-M3");
    this.hostProcId     = MultiProc.getIdMeta("HOST");
}


/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    for (var i = 0; i < mod.drvHandles.length; i++) {
        mod.drvHandles[i] = null;
    }

    if (Program.build.target.$name.match(/M3/)) {
        if (Core.id == 0) {
            Hwi.construct(mod.hwi, 53, NotifyDriverMbx.isr);
        }
        else {
            Hwi.construct(mod.hwi, 54, NotifyDriverMbx.isr);
        }
    }
    else if (Program.build.target.$name.match(/674/)) {
        var hwiParams = new Hwi.Params();
        hwiParams.eventId = 56;
        /*
         *  NotifyDriverMbx.intVectorId is typically set by the module that
         *  creates the Notify driver (i.e. the Notify setup module)
         */
        Hwi.construct(mod.hwi, this.intVectorId, NotifyDriverMbx.isr,
                hwiParams);
    }
    else if (Program.build.target.$name.match(/A8/)) {
        Hwi.construct(mod.hwi, 77, NotifyDriverMbx.isr);
    }
    else {
        throw("Invalid target: " + Program.build.target.$name);
    }
}

/*
 *************************************************************************
 *                       ROV View functions
 *************************************************************************
 */

/*
 *  Assigned mailboxes.  Structure is:
 *  var mailBoxMap = {
 *      "SRC_PROC_0" : {
 *          "DST_PROC_1" :  M(SRC_PROC_0_to_DST_PROC_1)
 *          "DST_PROC_2",   M(SRC_PROC_0_to_DST_PROC_2)
 *              :
 *      },
 *          :
 *  }
 */
var mailboxMap = {
    "DSP" : {
        "HOST" :        0,
        "VIDEO-M3" :    1,
        "VPSS-M3" :     2,
    },
    "HOST" : {
        "DSP" :         3,
        "VIDEO-M3" :    4,
        "VPSS-M3" :     5,
    },
    "VIDEO-M3" : {
        "HOST" :        6,
        "DSP" :         7,
        "VPSS-M3" :     10,
    },
    "VPSS-M3" : {
        "HOST" :        8,
        "DSP" :         9,
        "VIDEO-M3" :    11,
    },
}

/* Used to access core-specific mailbox registers */
var coreIds = {
    "HOST" :            0,
    "DSP" :             1,
    "VIDEO-M3" :        2,
    "VPSS-M3" :         3,
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var Program         = xdc.useModule('xdc.rov.Program');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');
    var MultiProc       = xdc.useModule('ti.sdo.utils.MultiProc');
    var modCfg =
        Program.getModuleConfig('ti.sdo.ipc.family.ti81xx.NotifyDriverMbx');
    var NotifyModCfg    = Program.getModuleConfig('ti.sdo.ipc.Notify');

    /* view.remoteProcName */
    try {
        view.remoteProcName = MultiProc.getName$view(obj.remoteProcId);
    }
    catch(e) {
        Program.displayError(view, 'remoteProcName',
                             "Problem retrieving proc name: " + e);
    }

    /* view.registeredEvents */
    var registeredEvents = [];
    for (i = 0; i < NotifyModCfg.numEvents; i++) {
        print("Checking event #" + i);
        if (obj.evtRegMask & (1 << i)) {
            print("registered!");
            registeredEvents.push(i.toString());
        }
    }
    view.registeredEvents = registeredEvents.join(", ");

    /* view.numPending */
    var localName = MultiProc.getName$view(MultiProc.self$view());
    var remoteName = view.remoteProcName;

    var M_in = mailboxMap[remoteName][localName];
    var M_out = mailboxMap[localName][remoteName];

    try {
        var MAILBOX_STATUS_IN = Program.fetchStruct(
                ScalarStructs.S_Bits32$fetchDesc,
                modCfg.mailboxBaseAddr + 0xC0 + (0x4 * M_in), false);
        var MAILBOX_STATUS_OUT = Program.fetchStruct(
                ScalarStructs.S_Bits32$fetchDesc,
                modCfg.mailboxBaseAddr + 0xC0 + (0x4 * M_out), false);
        view.numIncomingPending = MAILBOX_STATUS_IN.elem;
        view.numOutgoingPending = MAILBOX_STATUS_OUT.elem;
    }
    catch(e) {
        throw(e);
    }

    /* view.intStatus */
    try {
        var MAILBOX_IRQENABLE_CLR_LOCAL = Program.fetchStruct(
                ScalarStructs.S_Bits32$fetchDesc,
                modCfg.mailboxBaseAddr + 0x10C + (0x10 * coreIds[localName]),
                false);
        if (MAILBOX_IRQENABLE_CLR_LOCAL.elem & (1 << 2 * M_in)) {
            view.incomingIntStatus = "Enabled";
        }
        else {
            view.incomingIntStatus = "Disabled";
        }

        var MAILBOX_IRQENABLE_CLR_REMOTE = Program.fetchStruct(
                ScalarStructs.S_Bits32$fetchDesc,
                modCfg.mailboxBaseAddr + 0x10C + (0x10 * coreIds[remoteName]),
                false);
        if (MAILBOX_IRQENABLE_CLR_REMOTE.elem & (1 << 2 * M_out)) {
            view.outgoingStatus = "Enabled";
        }
        else {
            view.outgoingStatus = "Disabled";
        }
    }
    catch(e) {
        throw(e);
    }
}
