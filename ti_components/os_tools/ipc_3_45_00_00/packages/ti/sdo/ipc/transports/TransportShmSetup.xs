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
/* ======== TransportShmSetup.xs ========
 *
 */

var TransportShmSetup = null;
var GateMP            = null;
var Ipc               = null;
var Notify            = null;
var SharedRegion      = null;
var TransportShm      = null;
var MultiProc         = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    TransportShmSetup = this;
    GateMP       = xdc.useModule("ti.sdo.ipc.GateMP");
    Ipc          = xdc.useModule("ti.sdo.ipc.Ipc");
    Notify       = xdc.useModule("ti.sdo.ipc.Notify");
    SharedRegion = xdc.useModule("ti.sdo.ipc.SharedRegion");
    TransportShm = xdc.useModule("ti.sdo.ipc.transports.TransportShm");
    MultiProc    = xdc.useModule("ti.sdo.utils.MultiProc");
}

/*
 * ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    /* set the length of handles to the number of processors */
    mod.handles.length = MultiProc.numProcessors;

    /* init the remote processor handles to null */
    for (var i=0; i < mod.handles.length; i++) {
        mod.handles[i] = null;
    }
}
