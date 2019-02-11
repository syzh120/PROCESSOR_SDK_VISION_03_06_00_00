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
 *  ======== TransportShm.xs ========
 *
 */

var TransportShm = null;
var Ipc          = null;
var GateMP       = null;
var ListMP       = null;
var MessageQ     = null;
var Notify       = null;
var SharedRegion = null;
var MultiProc    = null;
var Cache        = null;
var Swi          = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    TransportShm = this;
    Ipc          = xdc.useModule("ti.sdo.ipc.Ipc");
    GateMP       = xdc.useModule("ti.sdo.ipc.GateMP");
    ListMP       = xdc.useModule("ti.sdo.ipc.ListMP");
    MessageQ     = xdc.useModule("ti.sdo.ipc.MessageQ");
    Notify       = xdc.useModule("ti.sdo.ipc.Notify");
    SharedRegion = xdc.useModule("ti.sdo.ipc.SharedRegion");
    MultiProc    = xdc.useModule("ti.sdo.utils.MultiProc");
    Cache        = xdc.useModule("ti.sysbios.hal.Cache");
    Swi          = xdc.useModule("ti.sysbios.knl.Swi");
}

/*
 *  ======== module$validate ========
 */
function module$validate()
{
    if (Notify.numEvents <= TransportShm.notifyEventId) {
        TransportShm.$logFatal("TransportShm.notifyEventId (" +
                TransportShm.notifyEventId +
                ") is too big: Notify.numEvents = " + Notify.numEvents,
                TransportShm);
    }
}
