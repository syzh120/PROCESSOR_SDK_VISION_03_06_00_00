/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== InterruptHost.xs ========
 */

/*
 *  ======== module$use ========
 */
function module$use()
{
    xdc.useModule("xdc.runtime.Assert");

    xdc.useModule("ti.sysbios.family.arm.a15.Mmu");
    xdc.useModule("ti.sysbios.family.arm.gic.Hwi");
    xdc.useModule("ti.sysbios.family.shared.vayu.IntXbar");

    xdc.useModule("ti.sdo.ipc.Ipc");
    xdc.useModule("ti.sdo.ipc.family.vayu.InterruptHost");
    xdc.useModule("ti.sdo.ipc.family.vayu.NotifySetup");

    var TableInit = xdc.useModule("ti.sdo.ipc.family.vayu.TableInit");

    /* initialize procIdTable */
    TableInit.initProcId(this);

    /* initialize mailboxTable */
    TableInit.generateTable(this);

    /* Initialize mailbox base address table */
    this.mailboxBaseAddr[0]  = 0x4208B000;  /* EVE1 Internal Mailbox 0 */
    this.mailboxBaseAddr[1]  = 0x4208C000;  /* EVE1 Internal Mailbox 1 */
    this.mailboxBaseAddr[2]  = 0x4208D000;  /* EVE1 Internal Mailbox 2 */
    this.mailboxBaseAddr[3]  = 0x4218B000;  /* EVE2 Internal Mailbox 0 */
    this.mailboxBaseAddr[4]  = 0x4218C000;  /* EVE2 Internal Mailbox 1 */
    this.mailboxBaseAddr[5]  = 0x4218D000;  /* EVE2 Internal Mailbox 2 */
    this.mailboxBaseAddr[6]  = 0x4228B000;  /* EVE3 Internal Mailbox 0 */
    this.mailboxBaseAddr[7]  = 0x4228C000;  /* EVE3 Internal Mailbox 1 */
    this.mailboxBaseAddr[8]  = 0x4228D000;  /* EVE3 Internal Mailbox 2 */
    this.mailboxBaseAddr[9]  = 0x4238B000;  /* EVE4 Internal Mailbox 0 */
    this.mailboxBaseAddr[10] = 0x4238C000;  /* EVE4 Internal Mailbox 1 */
    this.mailboxBaseAddr[11] = 0x4238D000;  /* EVE4 Internal Mailbox 2 */
    this.mailboxBaseAddr[12] = 0x48840000;  /* System Mailbox 5 */
    this.mailboxBaseAddr[13] = 0x48842000;  /* System Mailbox 6 */
    this.mailboxBaseAddr[14] = 0x48844000;  /* System Mailbox 7 */
    this.mailboxBaseAddr[15] = 0x48846000;  /* System Mailbox 8 */
}

/*
 *  ======== module$static$init ========
 *  Initialize the target state object.
 */
function module$static$init(state, mod)
{
    for (var i = 0; i < this.procIdTable.length; i++) {
        state.fxnTable[i].func = null;
        state.fxnTable[i].arg = 0;
    }
}
