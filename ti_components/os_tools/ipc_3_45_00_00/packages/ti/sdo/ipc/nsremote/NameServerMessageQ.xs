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
 *  ======== NameServerMessageQ.xs ========
 */

var NameServerMessageQ = null;
var NameServer = null;
var Semaphore  = null;
var Swi = null;
var Clock = null;
var Ipc = null;
var SyncSwi = null;
var GateMutex = null;
var MessageQ = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    NameServerMessageQ = this;
    NameServer      = xdc.useModule("ti.sdo.utils.NameServer");
    Semaphore       = xdc.useModule("ti.sysbios.knl.Semaphore");
    Swi             = xdc.useModule("ti.sysbios.knl.Swi");
    Clock           = xdc.useModule("ti.sysbios.knl.Clock");
    Ipc             = xdc.useModule("ti.sdo.ipc.Ipc");
    SyncSwi         = xdc.useModule("ti.sysbios.syncs.SyncSwi");
    GateMutex       = xdc.useModule("ti.sysbios.gates.GateMutex");
    MessageQ        = xdc.useModule("ti.sdo.ipc.MessageQ");
}

/*
 *  ======== module$static$init ========
 *  Initialize module values.
 */
function module$static$init(mod, params)
{
    mod.msgHandle = null;
    mod.msg       = null;

    /* calculate the timeout value */
    if (NameServerMessageQ.timeoutInMicroSecs != ~(0)) {
        NameServerMessageQ.timeout =
            NameServerMessageQ.timeoutInMicroSecs / Clock.tickPeriod;
    }
    else {
        NameServerMessageQ.timeout = NameServerMessageQ.timeoutInMicroSecs;
    }

    /* create Swi with lowest priority */
    var swiParams = new Swi.Params();
    swiParams.priority = 0;
    mod.swiHandle  = Swi.create(NameServerMessageQ.swiFxn, swiParams);

    /* create SyncSwi as the synchronizer */
    var syncSwiParams = new SyncSwi.Params();
    syncSwiParams.swi = mod.swiHandle;
    mod.syncSwiHandle = SyncSwi.create(syncSwiParams);

    /* create the semaphore to wait for a response message */
    mod.semRemoteWait = Semaphore.create(0);

    /* create GateMutex */
    mod.gateMutex = GateMutex.create();
}

function module$validate()
{
    if (MessageQ.numReservedEntries == 0) {
        NameServerMessageQ.$logFatal(
            "NameServerMessageQ is using MessageQ_create2 and requesting " +
            "queueIndex 0. However MessageQ.numReservedEntries is zero. " +
            "MessageQ.numReservedEntries must be increased to at least 1",
            NameServerMessageQ);
    }
}
