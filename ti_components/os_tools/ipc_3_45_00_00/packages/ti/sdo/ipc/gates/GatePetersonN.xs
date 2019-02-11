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
 *  ======== GatePetersonN.xs ========
 *
 */

var GatePetersonN = null;
var MultiProc    = null;
var Cache        = null;
var Ipc          = null;
var GateMP       = null;

/*!
 *  ======== module$use ========
 */
function module$use()
{
    GatePetersonN = this;
    MultiProc    = xdc.useModule('ti.sdo.utils.MultiProc');
    Cache        = xdc.useModule('ti.sysbios.hal.Cache');
    Ipc          = xdc.useModule('ti.sdo.ipc.Ipc');
    GateMP       = xdc.useModule('ti.sdo.ipc.GateMP');
}
/* TODO: add function module$static$init() and set MAX_NUM_PROCS from MultiProc
 */

/*!
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, params)
{
    GatePetersonN.$logError("Static instances not supported yet",
            GatePetersonN.common$, GatePetersonN.common$.namedInstance);
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
            rc = false;
            break;
        case IGateProvider.Q_PREEMPTING:
            rc = true;
            break;
        default:
           GatePetersonN.$logWarning("Invalid quality.", this, qual);
           break;
    }

    return (rc);
}

/*
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
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');

    try {
        var view = Program.scanHandleView('ti.sdo.ipc.gates.GatePetersonN',
                                          $addr(handle), 'Basic');
        if (view.gateOwner == "free") {
            return (view.gateOwner);
        }
        return ("Entered by " + view.gateOwner);
    }
    catch(e) {
        throw("ERROR: Couldn't scan GatePetersonN handle view: " + e);
    }
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    var GatePetersonN    = xdc.useModule('ti.sdo.ipc.gates.GatePetersonN');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');

    /* view.objType */
    view.objType = Ipc.getObjTypeStr$view(obj.objType);

    /* view.nested */
    view.nested = obj.nested;
    /*
    try {
        var sstruct_flag0 = Program.fetchStruct(ScalarStructs.S_Bits16$fetchDesc,
                                                obj.flag[0].$addr);
        var sstruct_flag1 = Program.fetchStruct(ScalarStructs.S_Bits16$fetchDesc,
                                                obj.flag[1].$addr);
        var sstruct_turn  = Program.fetchStruct(ScalarStructs.S_Bits16$fetchDesc,
                                                obj.turn.$addr);

        var flag = [sstruct_flag0.elem, sstruct_flag1.elem];
        var turn = sstruct_turn.elem;

        if (flag[1] == 1 && (turn == 1 || flag[0] == 0)) {
            view.gateOwner = "opener";
        }
        else if (flag[0] == 1 && (turn == 0 || flag[1] == 0)) {
            view.gateOwner = "creator";
        }
        else {
            view.gateOwner = "[free]";
        }
    }
    catch(e) {
        view.$status["gateOwner"] =
            "Error: could not fetch turn/flag data from shared memory: " + e;
    }
   */
}
