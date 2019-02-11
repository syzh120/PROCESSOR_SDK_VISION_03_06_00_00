/*
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== InterruptDsp.xs ========
 */
var InterruptDsp = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    /* load modules needed in meta domain and in target domain */
    var TableInit = xdc.useModule("ti.sdo.ipc.family.tda3xx.TableInit");
    InterruptDsp = this;
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Startup');
    xdc.useModule('ti.sysbios.family.c64p.EventCombiner');
    xdc.useModule('ti.sysbios.family.c64p.Hwi');
    xdc.useModule('ti.sysbios.family.shared.vayu.IntXbar');
    xdc.useModule('ti.sdo.ipc.Ipc');
    xdc.useModule('ti.sdo.ipc.family.tda3xx.NotifySetup');
    xdc.useModule('ti.sdo.ipc.notifyDrivers.IInterrupt');
    xdc.useModule('ti.sdo.utils.MultiProc');

    /* Initialize procIdTable */
    TableInit.initProcId(InterruptDsp);

    /* Initialize mailboxTable */
    TableInit.generateTable(InterruptDsp);

    /* Initialize mailbox base address table */
    this.mailboxBaseAddr[0] = 0x4208B000;   /* EVE1 Mailbox 0 */
    this.mailboxBaseAddr[1] = 0x4208C000;   /* EVE1 Mailbox 1 */
    this.mailboxBaseAddr[2] = 0x4883A000;   /* System Mailbox 2 */

    /* In case of a spec change, follow the process shown below:
     * 1. Update the mailboxBaseAddr Table.
     * 2. Update the dspInterruptTable.
     * 3. Update Virtual Index assignment.
     * 4. Update NUMCORES, NUMEVES and EVEMBX2BASEIDX variables
     *    in order to correctly intialize the mailboxTable.
     */
}

function module$static$init(mod, params)
{
    var remoteProcId;
    var idx;

    for (remoteProcId = 0; remoteProcId < InterruptDsp.procIdTable.length;
        remoteProcId++) {
        mod.fxnTable[remoteProcId].func  = null;
        mod.fxnTable[remoteProcId].arg   = 0;
    }
}
