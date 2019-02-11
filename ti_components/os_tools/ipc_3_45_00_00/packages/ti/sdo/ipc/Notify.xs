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
 *  ======== Notify.xs ========
 */

var Notify      = null;
var MultiProc   = null;
var Memory      = null;
var Ipc         = null;
var List        = null;
var Settings    = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    Notify      = this;
    Memory      = xdc.useModule('xdc.runtime.Memory');
    MultiProc   = xdc.useModule('ti.sdo.utils.MultiProc');
    List        = xdc.useModule('ti.sdo.utils.List');
    Settings    = xdc.useModule('ti.sdo.ipc.family.Settings');

    /* Check for valid numEvents */
    if (Notify.numEvents > Notify.MAXEVENTS) {
        Notify.$logFatal("Notify.numEvents may not be set to a value greater" +
                          " than " + Notify.MAXEVENTS, Notify);
    }

    /*
     *  Plug the module gate which will be used for protecting Notify APIs from
     *  each other. Use GateSwi
     */
    if (Notify.common$.gate === undefined) {
        var GateSwi = xdc.useModule('ti.sysbios.gates.GateSwi');
        Notify.common$.gate = GateSwi.create();
    }

    /* Plug the NotifySetup proxy */
    if (Notify.SetupProxy == null) {
        if (MultiProc.numProcessors == 1) {
            /*
             *  On a uniprocessor system (or Notify is disabled). We will never
             *  need to setup remote notify driver instances, so plug in
             *  NotifySetupNull.
             */
            Notify.SetupProxy
                = xdc.useModule('ti.sdo.ipc.notifyDrivers.NotifySetupNull');
        }
        else {
            /*
             *  On a multiprocessor system.  Query the Settings module for the
             *  device-specific NotifySetup delegate.
             */
            try {
                delegateName = Settings.getNotifySetupDelegate();
                Notify.SetupProxy = xdc.useModule(delegateName);
            }
            catch (e) {
                Notify.$logFatal(String(e), Notify);
            }
        }
    }

}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    var handles = Notify.$object.notifyHandles;

    handles.length = MultiProc.numProcsInCluster;

    /* Initialize every handle to null */
    for (var i = 0; i < handles.length; i++) {
        handles[i].length = params.numLines;

        for (var j = 0; j < handles[i].length; j++) {
            handles[i][j] = null;
        }
    }

    mod.localEnableMask = ~0;   /* all enabled by default */
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

    /* view.lineId */
    view.lineId = obj.lineId;

    /* view.disabled */
    view.disabled = obj.nesting;
}

/*
 *  ======== viewInitData ========
 *  Instance data view.
 */
function viewInitData(view, obj)
{
    var Notify  = xdc.useModule('ti.sdo.ipc.Notify');
    var List    = xdc.useModule('ti.sdo.utils.List');
    var modCfg = Program.getModuleConfig('ti.sdo.ipc.Notify');

    /* Display the instance label in the tree */
    view.label = "procId = " + obj.remoteProcId + " lineId = " + obj.lineId;

    /* Fetch the callback array */
    try {
        var callbacks = Program.fetchArray(obj.callbacks$fetchDesc,
                                           obj.callbacks,
                                           modCfg.numEvents);
    }
    catch(e) {
        Program.displayError(view, "eventId", "Problem retrieving callback " +
                             " array from instance state.");
        return;
    }

    /* Fetch the eventList */
    try {
        var eventList = Program.fetchArray(obj.eventList$fetchDesc,
                                           obj.eventList,
                                           modCfg.numEvents);
    }
    catch(e) {
        Program.displayError(view, "eventId", "Problem retrieving eventList " +
                             " from instance state.");
        return;
    }

    /* For each element of the buffer... */
    for (var eventId = 0; eventId < modCfg.numEvents; eventId++) {
        var fnNotifyCbck = callbacks[eventId].fnNotifyCbck;
        if (Number(fnNotifyCbck) == 0) {
            /* Event is unplugged */
            continue;
        }

        var fxnName = Program.lookupFuncName(Number(fnNotifyCbck))[0];
        if (fxnName == "ti_sdo_ipc_Notify_execMany__I") {
            /* Multiple callbacks registered.  View all of them */
            try {
                listView = Program.scanObjectView('ti.sdo.utils.List',
                                                   eventList[eventId],
                                                  'Basic');
                }
            catch (e) {
                Program.displayError(view, "eventId", "Problem scanning ROV " +
                    " for embedded event list object");
                return;
            }
            for each (var listElemPtr in listView.elems) {
                try {
                    var eventListener = Program.fetchStruct(
                            Notify.EventListener$fetchDesc,
                            $addr(listElemPtr));
                }
                catch(e) {
                    Program.displayError(view, "eventId", "Problem " +
                        "retrieving event listener ");
                    return;
                }

                var elem = Program.newViewStruct('ti.sdo.ipc.Notify',
                                                 'EventListeners');
                elem.eventId = eventId;
                elem.fnNotifyCbck = Program.lookupFuncName(
                    Number(eventListener.callback.fnNotifyCbck))[0];
                elem.cbckArg = "0x" +
                    Number(eventListener.callback.cbckArg).toString(16);

                /* Create a new row in the instance data view */
                view.elements.$add(elem);
            }
        }
        else {
            /* Single callback function registered. Just view one. */
            var elem = Program.newViewStruct('ti.sdo.ipc.Notify',
                                             'EventListeners');
            elem.fnNotifyCbck = fxnName;
            elem.eventId = eventId;
            elem.cbckArg = "0x" +
                Number(callbacks[eventId].cbckArg).toString(16);

            /* Create a new row in the instance data view */
            view.elements.$add(elem);
        }
    }
}
