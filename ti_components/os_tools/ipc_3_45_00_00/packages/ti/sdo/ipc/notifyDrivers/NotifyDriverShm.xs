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
 *  ======== NotifyDriverShm.xs ================
 *
 */

var NotifyDriverShm  = null;
var List             = null;
var MultiProc        = null;
var Notify           = null;
var Ipc              = null;
var Cache            = null;
var Memory           = null;
var SharedRegion     = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    NotifyDriverShm = this;
    List            = xdc.useModule("ti.sdo.utils.List");
    MultiProc       = xdc.useModule("ti.sdo.utils.MultiProc");
    Notify          = xdc.useModule("ti.sdo.ipc.Notify");
    Ipc             = xdc.useModule("ti.sdo.ipc.Ipc");
    SharedRegion    = xdc.useModule("ti.sdo.ipc.SharedRegion");
    Cache           = xdc.useModule("ti.sysbios.hal.Cache");
    Memory          = xdc.useModule("xdc.runtime.Memory");

    if (NotifyDriverShm.InterruptProxy == null) {
        var Settings = xdc.module("ti.sdo.ipc.family.Settings");
        var interruptDelegate = Settings.getDefaultInterruptDelegate();
        NotifyDriverShm.InterruptProxy = xdc.useModule(interruptDelegate);
    }
}

/*
 *************************************************************************
 *                       ROV View functions
 *************************************************************************
 */

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');

    /* view.remoteProcName */
    try {
        view.remoteProcName = MultiProc.getName$view(obj.remoteProcId);
    }
    catch(e) {
        Program.displayError(view, 'remoteProcName',
                             "Problem retrieving proc name: " + e);
    }


    /* view.cacheEnabled */
    view.cacheEnabled = obj.cacheEnabled;
}

/*
 *  ======== getEventData ========
 *  Helper function for use within viewInitData
 */
function getEventData(view, obj, procCtrlPtr, eventChartPtr)
{
    var NotifyDriverShm =
        xdc.useModule('ti.sdo.ipc.notifyDrivers.NotifyDriverShm');
    var modCfg = Program.getModuleConfig('ti.sdo.ipc.Notify');

    if (procCtrlPtr == obj.selfProcCtrl) {
        var procName = "[local]";
    }
    else {
        var procName = "[remote]";
    }

    try {
        var procCtrl = Program.fetchStruct(NotifyDriverShm.ProcCtrl$fetchDesc,
                                           procCtrlPtr, false);
    }
    catch(e) {
        throw (new Error("Error fetching procCtrl struct from shared memory"));
    }

    /* For each possible eventId... */
    for (var eventId = 0; eventId < modCfg.numEvents; eventId++) {
        if (procCtrl.eventRegMask & (1 << eventId)) {
            /* The event is registered */
            var elem = Program.newViewStruct(
                'ti.sdo.ipc.notifyDrivers.NotifyDriverShm',
                'Events');

            elem.eventId = eventId;
            elem.procName = procName;
            elem.enabled = procCtrl.eventEnableMask & (1 << eventId);

            try {
                var eventEntry = Program.fetchStruct(
                    NotifyDriverShm.EventEntry$fetchDesc,
                    $addr(Number(eventChartPtr) + obj.eventEntrySize *
                          eventId), false);

            }
            catch (e) {
                throw (new Error("Error fetching eventEntry from shared memory"));
            }

            elem.flagged = (eventEntry.flag == NotifyDriverShm.UP);
            elem.payload = eventEntry.payload;

            /* Create a new row in the instance data view */
            view.elements.$add(elem);
        }
    }
}


/*
 *  ======== viewInitData ========
 *  Instance data view.
 */
function viewInitData(view, obj)
{
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    try {
        var notifyObj = Program.scanHandleView('ti.sdo.ipc.Notify',
            obj.notifyHandle, 'Basic');
    }
    catch (e) {
        throw (new Error("Error fetching Notify instance view"));
    }

    /* Display the instance label in the tree */
    view.label = "procId = " + obj.remoteProcId + " lineId = " +
        notifyObj.lineId;

    /* Fetch self/other procCtrl's */
    try {
        var procCtrl = Program.fetchStruct(obj.selfProcCtrl$fetchDesc,
                                           obj.selfProcCtrl, false);
    }
    catch(e) {
        throw (new Error("Error fetching procCtrl struct from shared memory"));
    }

    /* Get event data for the local processor */
    getEventData(view, obj, obj.selfProcCtrl, obj.selfEventChart);

    /* Get event data for the remote processor */
    getEventData(view, obj, obj.otherProcCtrl, obj.otherEventChart);

}
