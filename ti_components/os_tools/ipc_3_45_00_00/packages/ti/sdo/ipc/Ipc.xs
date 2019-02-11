/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== Ipc.xs ========
 *
 */

var Ipc                    = null;
var Notify                 = null;
var SharedRegion           = null;
var MessageQ               = null;
var MultiProc              = null;
var NameServer             = null;
var Settings               = null;
var Cache                  = null;
var Hwi                    = null;

var initEntryDone = false;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    Ipc = this;

    Ipc.entry.length = 0;

    Settings = xdc.module("ti.sdo.ipc.family.Settings");

    /* determine if slave data is needed to be generated for host */
    Ipc.generateSlaveDataForHost = Settings.generateSlaveDataForHost();

    /* Set Ipc.sr0MemorySetup based on device defaults */
    var sr0MemorySetup = Settings.getIpcSR0Setup();
    if (sr0MemorySetup) {
        Ipc.sr0MemorySetup = true;
    }
    else {
        Ipc.sr0MemorySetup = false;
    }
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    SharedRegion    = xdc.useModule("ti.sdo.ipc.SharedRegion");
    Cache           = xdc.useModule("ti.sysbios.hal.Cache");
    Hwi             = xdc.useModule("ti.sysbios.hal.Hwi");
    Notify          = xdc.useModule("ti.sdo.ipc.Notify");
    MessageQ        = xdc.useModule("ti.sdo.ipc.MessageQ");
    MultiProc       = xdc.useModule("ti.sdo.utils.MultiProc");
    NameServer      = xdc.useModule("ti.sdo.utils.NameServer");
    Settings        = xdc.useModule("ti.sdo.ipc.family.Settings");

    if (!(NameServer.SetupProxy.$written("delegate$"))) {
        NameServer.SetupProxy =
            xdc.useModule(Settings.getNameServerRemoteDelegate());
    }

    /* get the host processor id */
    Ipc.hostProcId = Settings.getHostProcId();
}

/*
 *  ======== module$static$init ========
 *  Initialize module values.
 */
function module$static$init(state, mod)
{
    var fxn = new Ipc.UserFxn;
    var userFxnSet = false;

    /* set user's default attach/detach funtions */
    if (Ipc.userFxn.attach == undefined) {
        Ipc.userFxn.attach = null;
        fxn.attach = null;
    }
    else {
        fxn.attach = Ipc.userFxn.attach;
        userFxnSet = true;
    }

    if (Ipc.userFxn.detach == undefined) {
        Ipc.userFxn.detach = null;
        fxn.detach = null;
    }
    else {
        fxn.detach = Ipc.userFxn.detach;
        userFxnSet = true;
    }

    if (userFxnSet) {
        Ipc.$logWarning("Ipc.userFxn is deprecated.  The recommended way " +
            "to add an attach/detach function is by using " +
            "Ipc.addUserFxn(fxn, arg).", Ipc);
        addUserFxn(fxn, null);
    }

    /* init Ipc.entry */
    initEntryArray();

    /* initialize the procEntry[] array */
    state.procEntry.length = MultiProc.numProcsInCluster;

    for (var i = 0; i < state.procEntry.length; i++) {
        state.procEntry[i].entry = Ipc.entry[i];
        state.procEntry[i].localConfigList     = null;
        state.procEntry[i].remoteConfigList    = null;
        state.procEntry[i].attached            = 0;
    }

    state.ipcSharedAddr = null;
    state.gateMPSharedAddr = null;
    Ipc.numUserFxns = Ipc.userFxns.length;
}

/*
 *  ======== addUserFxn ========
 */
function addUserFxn(fxn, arg)
{
    Ipc.userFxns.$add({userFxn: fxn, arg: arg});
}

/*
 *  ======== setEntryMeta ========
 *  MultiProc.numProcessors must be set before calling this function
 */
function setEntryMeta(entry)
{
    var MultiProc = xdc.module("ti.sdo.utils.MultiProc");

    if (entry.remoteProcId == undefined) {
        Ipc.$logError("Ipc.setEntryMeta: remoteProcId was not specified.\n",
                      Ipc);
    }

    /* Log an error if the specified remoteProcId is invalid */
    if (entry.remoteProcId > MultiProc.numProcessors) {
        Ipc.$logError("Ipc.setEntryMeta: Invalid remoteProcId was " +
                      "specified.\n", Ipc);
    }

    /* init Ipc.entry */
    initEntryArray();

    if (MultiProc.baseIdOfCluster == MultiProc.INVALIDID) {
        Ipc.$logError("Cannot use Ipc.setEntryMeta when "
                + "MultiProc.baseIdOfCluster is INVALIDID.", Ipc);
    }

    var clusterId = entry.remoteProcId - MultiProc.baseIdOfCluster;

    if (entry.setupNotify != undefined) {
        Ipc.entry[clusterId].setupNotify = entry.setupNotify;
    }

    if (entry.setupMessageQ != undefined) {
        Ipc.entry[clusterId].setupMessageQ = entry.setupMessageQ;
    }
}

/*
 *  ======== initEntryArray ========
 *  This is an internal function. This function is called from
 *  setEntryMeta and module$static$init
 */
function initEntryArray()
{
    var MultiProc = xdc.module("ti.sdo.utils.MultiProc");

    /* init Ipc.entry if its not already initialized */
    if (!(initEntryDone)) {
        Ipc.entry.length = MultiProc.numProcsInCluster;

        for (var i = 0; i < MultiProc.numProcsInCluster; i++) {
            Ipc.entry[i].remoteProcId =
                    (MultiProc.baseIdOfCluster == MultiProc.INVALIDID) ?
                    MultiProc.INVALIDID : MultiProc.baseIdOfCluster + i;
            Ipc.entry[i].setupNotify      = true;
            Ipc.entry[i].setupMessageQ    = true;
        }

        initEntryDone = true;
    }
}

/*
 *  ======== getObjTypeStr$view ========
 */
function getObjTypeStr$view(type)
{
    var typeStr;

    switch(type) {
        case this.ObjType_CREATESTATIC:
            typeStr = "CREATESTATIC";
            break;
        case this.ObjType_CREATESTATIC_REGION:
            typeStr = "CREATESTATIC";
            break;
        case this.ObjType_CREATEDYNAMIC:
            typeStr = "CREATEDYNAMIC";
            break;
        case this.ObjType_CREATEDYNAMIC_REGION:
            typeStr = "CREATEDYNAMIC_REGION";
            break;
        case this.ObjType_OPENDYNAMIC:
            typeStr = "OPENDYNAMIC";
            break;
        case this.ObjType_LOCAL:
            typeStr = "LOCAL";
            break;
        default:
            typeStr = null;
    }

    return (typeStr);
}

/*
 *  ======== viewInitModule ========
 */
function viewInitModule(view)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var Ipc = xdc.useModule('ti.sdo.ipc.Ipc');
    var SharedRegion = xdc.useModule('ti.sdo.ipc.SharedRegion');
    var MultiProc = Program.getModuleConfig('ti.sdo.utils.MultiProc');

    /* Scan the raw view in order to obtain the module state. */
    var rawView;
    try {
        rawView = Program.scanRawView('ti.sdo.ipc.Ipc');
    }
    catch (e) {
        var entryView = Program.newViewStruct('ti.sdo.ipc.Ipc',
                'Module');
        Program.displayError(entryView, 'remoteProcId',
            "Problem retrieving raw view: " + e);
        view.elements.$add(entryView);
        return;
    }

    var mod = rawView.modState;

    /* Retrieve the processor entry table */
    try {
        var entries = Program.fetchArray(Ipc.ProcEntry$fetchDesc,
                                         mod.procEntry,
                                         MultiProc.numProcsInCluster);
    }
    catch (e) {
        var entryView = Program.newViewStruct('ti.sdo.ipc.Ipc',
                'Module');
        Program.displayError(entryView, 'remoteProcId',
            "Caught exception while trying to retrieve entry table: " + e);
        view.elements.$add(entryView);
        return;
    }

    /* Display each of the remote entries */
    for (var i = 0; i < entries.length; i++) {
        if (i != MultiProc.id) {
            var entry = entries[i].entry;

            var entryView = Program.newViewStruct('ti.sdo.ipc.Ipc',
                                                  'Module');

            entryView.remoteProcId = entry.remoteProcId;
            if (entries[i].attached) {
                entryView.attached = true;
            }
            else {
                entryView.attached = false;
            }
            entryView.setupNotify = entry.setupNotify;
            entryView.setupMessageQ = entry.setupMessageQ;

            view.elements.$add(entryView);
        }
    }
}
