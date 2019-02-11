/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *  ======== GateMP.xs ========
 *
 */

var GateMP       = null;
var NameServer   = null;
var MultiProc    = null;
var GateAll      = null;
var GateSwi      = null;
var GateMutexPri = null;
var GateNull     = null;
var SharedRegion = null;
var Ipc          = null;
var Settings     = null;

var instCount = 0;  /* use to determine if processing last instance */

/*!
 *  ======== module$use ========
 */
function module$use()
{
    GateMP       = this;
    NameServer   = xdc.useModule("ti.sdo.utils.NameServer");
    MultiProc    = xdc.useModule("ti.sdo.utils.MultiProc");
    SharedRegion = xdc.useModule("ti.sdo.ipc.SharedRegion");
    Settings     = xdc.useModule("ti.sdo.ipc.family.Settings");

    /* For local protection */
    GateMutexPri = xdc.useModule('ti.sysbios.gates.GateMutexPri');
    GateSwi      = xdc.useModule('ti.sysbios.gates.GateSwi');
    GateAll      = xdc.useModule('ti.sysbios.gates.GateAll');
    GateNull     = xdc.useModule('xdc.runtime.GateNull');

    /* Asserts, errors, etc */
    Ipc          = xdc.useModule('ti.sdo.ipc.Ipc');

    if (GateMP.RemoteSystemProxy == null) {
        var gateDel = Settings.getHWGate();
        GateMP.RemoteSystemProxy = xdc.module(gateDel);
    }

    if (GateMP.RemoteCustom1Proxy == null) {
        GateMP.RemoteCustom1Proxy
            = xdc.module('ti.sdo.ipc.gates.GatePeterson');
    }

    if (GateMP.RemoteCustom2Proxy == null) {
        GateMP.RemoteCustom2Proxy
            = xdc.module('ti.sdo.ipc.gates.GateMPSupportNull');
    }
}

/*!
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    /* Might be changed below */
    mod.nameServer = null;
    for (var i = 0; i < GateMP.ProxyOrder_NUM; i++) {
        mod.proxyMap[i] = i;
    }

    /* See if any of the proxies are the same */
    if (GateMP.RemoteCustom1Proxy.delegate$.$name ==
        GateMP.RemoteSystemProxy.delegate$.$name) {
        mod.proxyMap[GateMP.ProxyOrder_CUSTOM1] =
            mod.proxyMap[GateMP.ProxyOrder_SYSTEM];
    }

    if (GateMP.RemoteCustom2Proxy.delegate$.$name ==
        GateMP.RemoteSystemProxy.delegate$.$name) {
        mod.proxyMap[GateMP.ProxyOrder_CUSTOM2] =
            mod.proxyMap[GateMP.ProxyOrder_SYSTEM];
    }
    else if (GateMP.RemoteCustom2Proxy.delegate$.$name ==
             GateMP.RemoteCustom1Proxy.delegate$.$name) {
        mod.proxyMap[GateMP.ProxyOrder_CUSTOM2] =
            mod.proxyMap[GateMP.ProxyOrder_CUSTOM1];
    }

    /* Setup nameserver */
    /* initialize the NameServer param to be used now or later */
    GateMP.nameSrvPrms.maxRuntimeEntries = params.maxRuntimeEntries;
    GateMP.nameSrvPrms.tableSection      = params.tableSection;
    GateMP.nameSrvPrms.maxNameLen        = params.maxNameLen;

    var Program = xdc.module('xdc.cfg.Program');
    var target  = Program.build.target;

    if (params.hostSupport) {
        /*
         *  Need 6 words for info entry, which is larger than other entries
         */
        GateMP.nameSrvPrms.maxValueLen = 6 * target.stdTypes["t_Int32"].size;
        if (params.maxNameLen < 32) {
            GateMP.nameSrvPrms.maxNameLen = 32; /* min 32 chars for def gate */
        }
	mod.hostSupport = true;
    }
    else {
        /*
         *  Need 2 words:
         *    1 word for the SharedRegion Ptr.
         *    1 word for the proc id of creator and if remote is allowed.
         */
        GateMP.nameSrvPrms.maxValueLen = 2 * target.stdTypes["t_Int32"].size;
	mod.hostSupport = false;
    }

    /*
     *  Get the current number of created static instances of this module.
     *  Note: if user creates a static instance after this point and
     *        expects to use NameServer, this is a problem.
     */
    var instCount = this.$instances.length;

    /* create NameServer here only if no static instances are created */
    if (instCount == 0) {
        mod.nameServer = NameServer.create("GateMP",
                                           GateMP.nameSrvPrms);
    }

    /* Create the GateAll, GateSwi, and GateNull singletons */
    mod.gateAll  = GateAll.create();
    mod.gateSwi  = GateSwi.create();
    mod.gateMutexPri = GateMutexPri.create();
    mod.gateNull = GateNull.create();

    mod.numRemoteSystem  = GateMP.RemoteSystemProxy.delegate$.getNumResources();
    mod.numRemoteCustom1 = GateMP.RemoteCustom1Proxy.delegate$.getNumResources();
    mod.numRemoteCustom2 = GateMP.RemoteCustom2Proxy.delegate$.getNumResources();
    mod.remoteSystemGates.length  = mod.numRemoteSystem;

    /*
     *  If the proxies are not unique, plug these pointers in GateMP_start
     *  accordingly.
     */
    if (mod.proxyMap[GateMP.ProxyOrder_CUSTOM1] == GateMP.ProxyOrder_CUSTOM1) {
        mod.remoteCustom1Gates.length = mod.numRemoteCustom1;
    }
    else {
        mod.remoteCustom1Gates.length = 0;
    }

    if (mod.proxyMap[GateMP.ProxyOrder_CUSTOM2] == GateMP.ProxyOrder_CUSTOM2) {
        mod.remoteCustom2Gates.length = mod.numRemoteCustom2;
    }
    else {
        mod.remoteCustom2Gates.length = 0;
    }

    mod.defaultGate = null;
    mod.nsKey = 0;
    mod.remoteSystemGates[0] = mod.defaultGate;

    /* Initialize the rest of the proxy gate arrays */
    for (var i = 1; i < mod.remoteSystemGates.length; i++) {
        mod.remoteSystemGates[i] = null;
    }

    for (var i = 0; i < mod.remoteCustom1Gates.length; i++) {
        mod.remoteCustom1Gates[i] = null;
    }

    for (var i = 0; i < mod.remoteCustom2Gates.length; i++) {
        mod.remoteCustom2Gates[i] = null;
    }
}

/*
 *  ======== queryMeta ========
 */
function queryMeta(qual)
{
    var rc = false;

    return (rc);
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var Program         = xdc.useModule('xdc.rov.Program');
    var NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    var SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');
    var Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    var GateMP          = xdc.useModule('ti.sdo.ipc.GateMP');

    /* view.name */
    try {
        if (obj.nsKey != 0x0) {
            view.name = NameServer.getNameByKey$view(obj.nsKey);
        }
    }
    catch(e) {
        Program.displayError(view, "name",
            "Error retrieving name from NameServer: " + e);
    }

    var GateSupportProxy;

    /* view.remoteProtect & view.remoteStatus */
    switch(obj.remoteProtect) {
        case GateMP.RemoteProtect_NONE:
            view.remoteProtect = "NONE";
            GateSupportProxy = null;
            break;
        case GateMP.RemoteProtect_SYSTEM:
            view.remoteProtect = "SYSTEM";
            GateSupportProxy =
                Program.$modules['ti.sdo.ipc.GateMP'].RemoteSystemProxy;
            break;
        case GateMP.RemoteProtect_CUSTOM1:
            view.remoteProtect = "CUSTOM1";
            GateSupportProxy =
                Program.$modules['ti.sdo.ipc.GateMP'].RemoteCustom1Proxy;
            break;
        case GateMP.RemoteProtect_CUSTOM2:
            view.remoteProtect = "CUSTOM2";
            GateSupportProxy =
                Program.$modules['ti.sdo.ipc.GateMP'].RemoteCustom2Proxy;
            break;
        default:
            Program.displayError(view, "remoteProtect",
                "Corrupted state: The value of 'obj->remoteProtect' is not " +
                "one of known types");
    }

    if (GateSupportProxy == null) {
        view.remoteStatus = "[none]";
    }
    else {
        try {
            var GateDelegate = xdc.useModule(GateSupportProxy.$name);
            view.remoteStatus
                = GateDelegate.getRemoteStatus$view(obj.gateHandle);
        }
        catch (e) {
            Program.displayError(view, "remoteStatus",
                "Error obtaining remote gate (resourceId = " +
                obj.resourceId + ") status: " + e);
        }
    }

    /* view.localProtect */
    switch(obj.localProtect) {
        case GateMP.LocalProtect_NONE:
            view.localProtect = "NONE";
            break;
        case GateMP.LocalProtect_INTERRUPT:
            view.localProtect = "INTERRUPT";
            break;
        case GateMP.LocalProtect_TASKLET:
            view.localProtect = "TASKLET";
            break;
        case GateMP.LocalProtect_THREAD:
            view.localProtect = "THREAD";
            break;
        case GateMP.LocalProtect_PROCESS:
            view.localProtect = "PROCESS";
            break;
        default:
            Program.displayError(view, "localProtect",
                "Corrupted state: The value of 'obj->localProtect' is not " +
                "one of known types");
    }

    /* view.numOpens */
    view.numOpens = obj.numOpens;

    /* view.resourceId; Ensure that it isn't equal to ((UInt)-1) */
    if (obj.resourceId != 0xFFFFFFFF) {
        view.resourceId = obj.resourceId;
    }

    /* view.creatorProcId */
    try {
        var attrs = Program.fetchStruct(GateMP.Attrs$fetchDesc,
                                        obj.attrs.$addr, false);

        view.creatorProcId = attrs.creatorProcId;
    }
    catch (e) {
        Program.displayError(view, 'creatorProcId',
            "Error: could not fetch shared memory structure: " + e);
    }

    /* view.objType */
    try {
        view.objType = Ipc.getObjTypeStr$view(obj.objType);
    }
    catch (e) {
        Program.displayError(view, "objType", "Corrupted state: " + e);
    }
}

/*
 *  ======== viewInitModule ========
 */
function viewInitModule(view, mod)
{
    var Program         = xdc.useModule('xdc.rov.Program');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');

    view.numGatesSystem = mod.numRemoteSystem;

    if (mod.defaultGate == 0) {
        /* GateMP not started yet */
        view.numUsedSystem = 0;
        return;
    }

    try {
        var remoteSystemInUse = Program.fetchArray(
            mod.remoteSystemInUse$fetchDesc,
            mod.remoteSystemInUse.$addr,
            mod.numRemoteSystem);
    }
    catch (e) {
        throw("Problem fetching remoteSystemInUse" + e); //TODO
    }

    view.numUsedSystem = 0;
    for each (var isUsed in remoteSystemInUse) {
        if (isUsed) {
            view.numUsedSystem++;
        }
    }

    if (mod.proxyMap[1] == 1) {
        view.numGatesCustom1 = mod.numRemoteCustom1;

        try {
            var remoteCustom1InUse = Program.fetchArray(
                mod.remoteCustom1InUse$fetchDesc,
                mod.remoteCustom1InUse.$addr,
                mod.numRemoteCustom1);
        }
        catch (e) {
            throw("Problem fetching remoteCustom1InUse" + e); //TODO
        }


        view.numUsedCustom1 = 0;
        for each (var isUsed in remoteCustom1InUse) {
            if (isUsed) {
                view.numUsedCustom1++;
            }
        }
    }

    if (mod.proxyMap[2] == 2) {
        view.numGatesCustom2 = mod.numRemoteCustom2;

        try {
            var remoteCustom2InUse = Program.fetchArray(
                mod.remoteCustom2InUse$fetchDesc,
                mod.remoteCustom2InUse.$addr,
                mod.numRemoteCustom2);
        }
        catch (e) {
            throw("Problem fetching remoteCustom2InUse" + e); //TODO
        }


        view.numUsedCustom2 = 0;
        for each (var isUsed in remoteCustom2InUse) {
            if (isUsed) {
                view.numUsedCustom2++;
            }
        }
    }
}
