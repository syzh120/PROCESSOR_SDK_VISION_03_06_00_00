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
 *  ======== GateHWSem.xs ========
 *
 */

var GateHWSem   = null;
var GateMP      = null;
var Ipc         = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    GateHWSem = this

    try {
        var Settings = xdc.module("ti.sdo.ipc.family.Settings");
        var devCfg = Settings.getGateHWSemSettings();
        GateHWSem.baseAddr      = devCfg.baseAddr;
        GateHWSem.queryAddr     = devCfg.queryAddr;
        GateHWSem.numSems       = devCfg.numSems;

        GateHWSem.reservedMaskArr.length =
                Math.ceil(GateHWSem.numSems / 32);
        for (var i = 0; i < GateHWSem.reservedMaskArr.length; i++) {
            GateHWSem.reservedMaskArr[i] = 0;
        }
    }
    catch(e) {
    }
}

/*
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
           GateHWSem.$logWarning("Invalid quality.", this, qual);
           break;
    }

    return (rc);
}

/*
 *  ======== getNumResources ========
 */
function getNumResources()
{
    return (GateHWSem.numSems);
}

/*
 *  ======== setReserved ========
 */
function setReserved(semNum)
{
    var GateHWSem = this;

    if (semNum >= GateHWSem.numSems) {
        GateHWSem.$logError("Invalid semaphore number: " + GateHWSem.numSems +
                ". There are only " + GateHWSem.numSems + " on this device.",
                this);
    }

    GateHWSem.reservedMaskArr[semNum >> 5] |= (1 << (semNum % 32));
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
        var view = Program.scanHandleView('ti.sdo.ipc.gates.GateHWSem',
                                          $addr(handle), 'Basic');
        return ("Entered by " + view.enteredBy);
    }
    catch(e) {
        throw("ERROR: Couldn't scan GateHWSem handle view: " + e);
    }

    return (status);
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var GateHWSem       = xdc.useModule('ti.sdo.ipc.gates.GateHWSem');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');

    /* view.semNum */
    view.semNum = obj.semNum;

    /* view.nested */
    view.nested = obj.nested;

    /* view.enteredBy */
    try {
        var modCfg = Program.getModuleConfig('ti.sdo.ipc.gates.GateHWSem');
        var semQueryAddr = $addr(Number(modCfg.queryAddr) + obj.semNum * 4);

        var sstruct_status = Program.fetchStruct(
                                ScalarStructs.S_Bits32$fetchDesc,
                                semQueryAddr, false);
        var status = sstruct_status.elem;
        if (status & 0x1) {
            view.enteredBy = "[free]";
        }
        else {
            var coreId = (status & 0x0000ff00) >> 8;
            view.enteredBy = "CORE" + coreId;
        }
    }
    catch(e) {
        view.$status["enteredBy"] =
            "Error: could not fetch query data: " + e;
    }
}
