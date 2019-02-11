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
 *  ======== NotifyDriverMbx.xs ================
 */
var NotifyDriverMbx = null;
var isaChain = "";

/*
 *  ======== module$use ========
 */
function module$use()
{
    /* load modules needed in meta domain and in target domain */
    var TableInit = xdc.useModule("ti.sdo.ipc.family.tda3xx.TableInit");
    var MultiProc = xdc.useModule("ti.sdo.utils.MultiProc");
    NotifyDriverMbx = this;
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Startup');

    /* concatenate isa chain into single string for easier matching */
    isaChain = "#" + Program.build.target.getISAChain().join("#") + "#";

    if (isaChain.match(/#64P#/)) {
        xdc.useModule("ti.sysbios.family.c64p.Hwi");
    }
    else if (isaChain.match(/#arp32#/)) {
        xdc.useModule('ti.sysbios.family.arp32.Hwi');
    }
    else if (isaChain.match(/#v7M#/)) {
        xdc.useModule('ti.sysbios.family.arm.m3.Hwi');
    }

    xdc.useModule("ti.sdo.ipc.Notify");
    xdc.useModule('ti.sdo.ipc.family.tda3xx.NotifySetup');

    /* initialize procIdTable */
    TableInit.initProcId(this);

    /* Initialize mailboxTable */
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
}

/*
 *  ======== module$static$init ========
 *  Initialize the target state object.
 */
function module$static$init(state, mod)
{
    for (var i = 0; i < state.drvHandles.length; i++) {
        state.drvHandles[i] = null;
    }

    if (isaChain.match(/#64P#/)) {
    }
    else if (isaChain.match(/#arp32#/)) {
    }
    else if (isaChain.match(/#v7M#/)) {
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
 *  ======== viewInitBasic ========
 *  Initizalize the 'Basic' ROV view. Called once per instance.
 *
 *  view = instance of 'struct NotifyDriverMbx.BasicView'
 */
function viewInitBasic(view, obj)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');

    /* view.remoteProc */
    try {
        view.remoteProc = MultiProc.getName$view(obj.remoteProcId);
    }
    catch (e) {
        Program.displayError(view, 'remoteProc',
                "Problem retrieving proc name: " + e);
    }
}

/*
 *  ======== viewInitMailbox ========
 *  Initizalize the 'Mailbox' ROV view. Called once per instance.
 *
 *  view = instance of 'struct xdc.rov.Program.InstDataView'
 */
function viewInitMailbox(view, obj)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var ScalarStructs = xdc.useModule('xdc.rov.support.ScalarStructs');
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    var modCfg = Program.getModuleConfig(
            'ti.sdo.ipc.family.tda3xx.NotifyDriverMbx');

    /* view.label (use remote processor name) */
    try {
        view.label = MultiProc.getName$view(obj.remoteProcId);
    }
    catch (e) {
        Program.displayError(view, 'remoteProcId',
                "Problem retrieving proc name: " + e);
    }

    /* create an array to hold the instance data table */
    var dataTable = new Array();
    var mailbox = ["Inbound", "Outbound"];

    for (var i = 0; i < mailbox.length; i++) {

        /* create the view element */
        var elem = Program.newViewStruct(
                'ti.sdo.ipc.family.tda3xx.NotifyDriverMbx', 'Mailbox');

        /* elem.direction (make a descriptive label) */
        if (mailbox[i] == "Inbound") {
            elem.direction = mailbox[i] + " (from " + view.label + ")";
        }
        else if (mailbox[i] == "Outbound") {
            elem.direction = mailbox[i] + " (to " + view.label + ")";
        }
        else {
            throw new Error("invalid mailbox type");
        }

        /* elem.mailboxAddr */
        var selfVirtId = modCfg.procIdTable[MultiProc.self$view()];
        var idx;

        if (mailbox[i] == "Inbound") {
            idx = (obj.remoteVirtId * modCfg.NUM_CORES) + selfVirtId;
        }
        else if (mailbox[i] == "Outbound") {
            idx = (selfVirtId * modCfg.NUM_CORES) + obj.remoteVirtId;
        }
        else {
            throw new Error("invalid mailbox type");
        }

        var baseAddrIdx = (modCfg.mailboxTable[idx] >> 16) & 0xFFFF;
        var mailboxAddr = modCfg.mailboxBaseAddr[baseAddrIdx];
        elem.mailboxAddr = "0x" + Number(mailboxAddr).toString(16);

        /* elem.subMbxId */
        elem.subMbxId = modCfg.mailboxTable[idx] & 0xFF;

        /* elem.msgCount */
        try {
            var MAILBOX_STATUS_IN = Program.fetchStruct(
                    ScalarStructs.S_Bits32$fetchDesc,
                    mailboxAddr + 0xC0 + (0x4 * elem.subMbxId), false);
            elem.msgCount = MAILBOX_STATUS_IN.elem;
        }
        catch (e) {
            Program.displayError(view, 'msgCount',
                    "Problem retrieving messsage count: " + e);
        }

        /* elem.mbxInterrupt */
        elem.mbxInterrupt = (modCfg.mailboxTable[idx] >> 8) & 0xFF;

        /* add the element to the instance data table */
        dataTable.push(elem);
    }

    /* view.elements */
    view.elements = dataTable;
}
