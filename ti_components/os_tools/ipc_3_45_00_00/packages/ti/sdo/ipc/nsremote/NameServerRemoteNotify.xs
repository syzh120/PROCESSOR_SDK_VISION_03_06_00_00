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
 *  ======== NameServerRemoteNotify.xs ========
 */

var NameServerRemoteNotify;
var NameServer;
var MultiProc;
var Notify;
var Ipc;
var GateMP;
var SharedRegion;
var Semaphore;
var Swi;
var Clock = null;
var Cache;

/*
 *  ======== module$use ========
 */
function module$use()
{
    NameServerRemoteNotify = this;
    NameServer      = xdc.useModule("ti.sdo.utils.NameServer");
    MultiProc       = xdc.useModule("ti.sdo.utils.MultiProc");
    Notify          = xdc.useModule("ti.sdo.ipc.Notify");
    Ipc             = xdc.useModule("ti.sdo.ipc.Ipc");
    GateMP          = xdc.useModule("ti.sdo.ipc.GateMP");
    SharedRegion    = xdc.useModule("ti.sdo.ipc.SharedRegion");
    Semaphore       = xdc.useModule("ti.sysbios.knl.Semaphore");
    Swi             = xdc.useModule("ti.sysbios.knl.Swi");
    Clock           = xdc.useModule("ti.sysbios.knl.Clock");
    Cache           = xdc.useModule("ti.sysbios.hal.Cache");
}

/*
 *  ======== module$static$init ========
 *  Initialize module values.
 */
function module$static$init(mod, params)
{
    /* calculate the timeout value */
    if (NameServerRemoteNotify.timeoutInMicroSecs != ~(0)) {
        NameServerRemoteNotify.timeout =
            NameServerRemoteNotify.timeoutInMicroSecs / Clock.tickPeriod;
    }
    else {
        NameServerRemoteNotify.timeout =
            NameServerRemoteNotify.timeoutInMicroSecs;
    }
}

/*
 *  ======== module$validate ========
 */
function module$validate()
{
    if (Notify.numEvents <= NameServerRemoteNotify.notifyEventId) {
        NameServerRemoteNotify.$logFatal(
                "NameServerRemoteNotify.notifyEventId (" +
                NameServerRemoteNotify.notifyEventId +
                ") is too big: Notify.numEvents = " + Notify.numEvents,
                NameServerRemoteNotify);
    }
}

/*
 *************************************************************************
 *                       ROV View functions
 *************************************************************************
 */

/*
 *  ======== fetchString ========
 *  Returns a string contained in one of the Bits32 array fields in 'msg'
 */
function fetchString(msg, field)
{
    var NSRN = xdc.useModule('ti.sdo.ipc.nsremote.NameServerRemoteNotify');

    var ptrToString = $addr(Number(msg) + NSRN.Message.$offsetof(field));

    return (Program.fetchString(ptrToString));
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    var NSRN = xdc.useModule('ti.sdo.ipc.nsremote.NameServerRemoteNotify');

    /* view.remoteProcId */
    view.remoteProcId = obj.remoteProcId;

    /* view.remoteProcName */
    try {
        view.remoteProcName = MultiProc.getName$view(obj.remoteProcId);
    }
    catch(e) {
        Program.displayError(view, 'remoteProcName',
                "Problem retrieving proc name: " + e);
    }

    if (MultiProc.self$view() > obj.remoteProcId) {
        var localId = 1;
        var remoteId = 0;
    }
    else {
        var localId = 0;
        var remoteId = 1;
    }

    /*
     *  process local message state
     */
    try {
        var localMsg = Program.fetchStruct(NSRN.Message$fetchDesc,
                $addr(obj.msg[localId]));
    }
    catch(e) {
        Program.displayError(view, "localRequestStatus",
                "Problem retrieving local request status");
        return;
    }

    view.localValue = "";

    if (obj.localState == NSRN.IDLE) {
        view.localRequestStatus = "Idle";
        view.localInstanceName = "";
        view.localName = "";
    }
    else {
        view.localInstanceName = fetchString(obj.msg[localId], "instanceName");
        view.localName = fetchString(obj.msg[localId], "name");
    }

    if (obj.localState == NSRN.SEND_REQUEST) {
        view.localRequestStatus = "Sending a request";
    }

    if (obj.localState == NSRN.RECEIVE_RESPONSE) {
        view.localRequestStatus = "Receiving a response";

        if (localMsg.requestStatus == 1) {
            view.localRequestStatus += " (found)";

            if (localMsg.valueLen <= 4) {
                view.localValue = "0x"+Number(localMsg.value).toString(16);
            }
            else {
                view.localValue = "Value at 0x" +
                    Number(Number(obj.msg[localId]) +
                    NSRN.Message.$offsetof("valueBuf")).toString(16);
            }
        }
        else {
            view.localRequestStatus += " (not found)";
        }
    }

    /*
     *  process remote message state
     */
    try {
        var remoteMsg = Program.fetchStruct(NSRN.Message$fetchDesc,
                $addr(obj.msg[remoteId]));
    }
    catch(e) {
        Program.displayError(view, "localRequestStatus",
                "Problem retrieving remote request status");
        return;
    }

    view.remoteValue = "";

    if (obj.remoteState == NSRN.IDLE) {
        view.remoteRequestStatus = "Idle";
        view.remoteInstanceName = "";
        view.remoteName = "";
    }
    else {
        view.remoteInstanceName = fetchString(obj.msg[remoteId],"instanceName");
        view.remoteName = fetchString(obj.msg[remoteId], "name");
    }

    if (obj.remoteState == NSRN.RECEIVE_REQUEST) {
        view.remoteRequestStatus = "Receiving a request";
    }

    if (obj.remoteState == NSRN.SEND_RESPONSE) {
        view.remoteRequestStatus = "Sending a response";

        if (remoteMsg.requestStatus == 1) {
            view.remoteRequestStatus += " (found)";

            if (remoteMsg.valueLen <= 4) {
                view.remoteValue = "0x"+Number(remoteMsg.value).toString(16);
            }
            else {
                view.remoteValue = "Value at 0x" +
                    Number(Number(obj.msg[remoteId]) +
                    NSRN.Message.$offsetof("valueBuf")).toString(16);
            }
        }
        else {
            view.remoteRequestStatus += " (not found)";
        }
    }
}
