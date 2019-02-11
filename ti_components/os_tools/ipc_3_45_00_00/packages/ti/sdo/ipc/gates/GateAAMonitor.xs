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
 *  ======== GateAAMonitor.xs ========
 *
 */

var GateAAMonitor   = null;
var Cache           = null;
var Ipc             = null;
var GateMP          = null;

/*!
 *  ======== module$use ========
 */
function module$use()
{
    GateAAMonitor   = this;
    Cache           = xdc.useModule('ti.sysbios.hal.Cache');
    Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    GateMP          = xdc.useModule('ti.sdo.ipc.GateMP');
}

/*!
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, params)
{
    GateAAMonitor.$logError("Static instances not supported yet",
            GateAAMonitor.common$, GateAAMonitor.common$.namedInstance);
}

/*!
 *  ======== queryMeta ========
 */
function queryMeta(qual)
{
    var rc = false;
    var IGateProvider = xdc.module('xdc.runtime.IGateProvider');

    switch (qual) {
        case IGateProvider.Q_BLOCKING:
            rc = true;
            break;
        case IGateProvider.Q_PREEMPTING:
            rc = true;
            break;
        default:
           GateAAMonitor.$logWarning("Invalid quality.", this, qual);
           break;
    }

    return (rc);
}

/*!
 *  ======== sharedMemReqMeta ========
 */
function sharedMemReqMeta(params)
{
    GateAAMonitor.$logError("Static instances not supported yet",
            GateAAMonitor.common$, GateAAMonitor.common$.namedInstance);
}

/*!
 *  ======== getNumResources ========
 */
function getNumResources()
{
    return (this.numInstances);
}

/*
 *************************************************************************
 *                       ROV View functions
 *************************************************************************
 */

/*
 *  ======== getRemoteStatus$view ========
 */
function getRemoteStatus$view(handle)
{
    var Program         = xdc.useModule('xdc.rov.Program');

    try {
        var view = Program.scanHandleView('ti.sdo.ipc.gates.GateAAMonitor',
                                          $addr(handle), 'Basic');
        return ("Entered by " + view.enteredBy);
    }
    catch(e) {
        throw("ERROR: Couldn't scan GateAAMonitor handle view: " + e);
    }
}

/*!
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    var GateAAMonitor   = xdc.useModule('ti.sdo.ipc.gates.GateAAMonitor');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');

    /* view.sharedAddr */
    view.sharedAddr = "0x" + Number(obj.sharedAddr).toString(16);

    /* view.nested */
    view.nested = obj.nested;

    /* view.enteredBy */
    try {
        var sstruct_status = Program.fetchStruct(ScalarStructs.S_Bits32$fetchDesc,
                                                 obj.sharedAddr.$addr, false);
        var status = sstruct_status.elem;
        if (status > 0) {
            view.enteredBy = "CORE" + (status - 1);
        }
        else {
            view.enteredBy = "[free]";
        }
    }
    catch(e) {
        view.$status["enteredBy"] =
            "Error: could not fetch status data from shared memory: " + e;
    }
}
