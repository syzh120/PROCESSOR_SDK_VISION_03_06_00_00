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
 *  ======== GateHWSpinlock.xs ========
 *
 */

var GateHWSpinlock = null;
var GateMP      = null;
var Ipc         = null;

var devCfg;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    GateHWSpinlock = this;

    try {
        var Settings = xdc.module("ti.sdo.ipc.family.Settings");
        devCfg = Settings.getGateHWSpinlockSettings();
        GateHWSpinlock.numLocks = devCfg.numLocks;

        GateHWSpinlock.reservedMaskArr.length =
                Math.ceil(GateHWSpinlock.numLocks / 32);
        for (var i = 0; i < GateHWSpinlock.reservedMaskArr.length; i++) {
            GateHWSpinlock.reservedMaskArr[i] = 0;
        }
    }
    catch (e) {
    }
}


/*!
 *  ======== module$use ========
 */
function module$use()
{
    Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');
    MultiProc       = xdc.useModule('ti.sdo.utils.MultiProc');

    if (GateHWSpinlock.baseAddr == null) {
        GateHWSpinlock.baseAddr = devCfg.baseAddr;
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
           GateHWSpinlock.$logWarning("Invalid quality.", this, qual);
           break;
    }

    return (rc);
}

/*
 *  ======== getNumResources ========
 */
function getNumResources()
{
    return (GateHWSpinlock.numLocks);
}

/*
 *  ======== setReserved ========
 */
function setReserved(lockNum)
{
    if (lockNum >= GateHWSpinlock.numLocks) {
        GateHWSpinlock.$logError("Invalid spinlock number: " + lockNum +
                ". There are only " + GateHWSpinlock.numLocks +
                " locks on this device.", GateHWSpinlock);
    }

    GateHWSpinlock.reservedMaskArr[lockNum >> 5] |= (1 << (lockNum % 32));
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
    /* HW Spinlocks don't offer status */
    return("[no status]");
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    GateHWSpinlock = xdc.useModule('ti.sdo.ipc.gates.GateHWSpinlock');

    /* view.lockNum */
    view.lockNum = obj.lockNum;

    /* view.nested */
    view.nested = obj.nested;
}
