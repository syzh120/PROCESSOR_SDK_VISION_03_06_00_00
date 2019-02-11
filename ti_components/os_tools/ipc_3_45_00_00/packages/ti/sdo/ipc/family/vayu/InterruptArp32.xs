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
 *  ======== InterruptArp32.xs ========
 */
var InterruptArp32 = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    var TableInit = xdc.useModule("ti.sdo.ipc.family.vayu.TableInit");
    var MultiProc = xdc.useModule("ti.sdo.utils.MultiProc");
    InterruptArp32 = this;

    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Error');
    xdc.useModule("ti.sysbios.family.arp32.Hwi");
    xdc.useModule("ti.sdo.ipc.Ipc");
    xdc.useModule('ti.sdo.ipc.family.vayu.NotifySetup');
    xdc.useModule('ti.sdo.ipc.notifyDrivers.IInterrupt');

    /* Initialize procIdTable */
    TableInit.initProcId(InterruptArp32);

    /* Initialize mailboxTable */
    TableInit.generateTable(InterruptArp32);

    /* Initialize mailbox base address table */
    this.mailboxBaseAddr[0]  = 0x4008B000;  /* EVE1 Internal Mailbox 0 */
    this.mailboxBaseAddr[1]  = 0x4008C000;  /* EVE1 Internal Mailbox 1 */
    this.mailboxBaseAddr[2]  = 0x4208D000;  /* EVE1 Internal Mailbox 2 */
    this.mailboxBaseAddr[3]  = 0x4008B000;  /* EVE2 Internal Mailbox 0 */
    this.mailboxBaseAddr[4]  = 0x4008C000;  /* EVE2 Internal Mailbox 1 */
    this.mailboxBaseAddr[5]  = 0x4218D000;  /* EVE2 Internal Mailbox 2 */
    this.mailboxBaseAddr[6]  = 0x4008B000;  /* EVE3 Internal Mailbox 0 */
    this.mailboxBaseAddr[7]  = 0x4008C000;  /* EVE3 Internal Mailbox 1 */
    this.mailboxBaseAddr[8]  = 0x4228D000;  /* EVE3 Internal Mailbox 2 */
    this.mailboxBaseAddr[9]  = 0x4008B000;  /* EVE4 Internal Mailbox 0 */
    this.mailboxBaseAddr[10] = 0x4008C000;  /* EVE4 Internal Mailbox 1 */
    this.mailboxBaseAddr[11] = 0x4238D000;  /* EVE4 Internal Mailbox 2 */
    this.mailboxBaseAddr[12] = 0x48840000;  /* System Mailbox 5 */
    this.mailboxBaseAddr[13] = 0x48842000;  /* System Mailbox 6 */
    this.mailboxBaseAddr[14] = 0x48844000;  /* System Mailbox 7 */
    this.mailboxBaseAddr[15] = 0x48846000;  /* System Mailbox 8 */

    /* each EVE receives its message using the local mailbox address */
    if (MultiProc.id == this.eve1ProcId) {
        this.mailboxBaseAddr[2] = 0x4008D000;
    }
    else if (MultiProc.id == this.eve2ProcId) {
        this.mailboxBaseAddr[5] = 0x4008D000;
    }
    else if (MultiProc.id == this.eve3ProcId) {
        this.mailboxBaseAddr[8] = 0x4008D000;
    }
    else if (MultiProc.id == this.eve4ProcId) {
        this.mailboxBaseAddr[11] = 0x4008D000;
    }

    /* EVE interrupt mapping. See EVE28 functional specs */
    this.eveInterruptTable[0] = 60;  /* EVE1 - Group1/INTC1 */
    this.eveInterruptTable[1] = 60;  /* EVE2 - Group1/INTC1 */
    this.eveInterruptTable[2] = 60;  /* EVE3 - Group1/INTC1 */
    this.eveInterruptTable[3] = 60;  /* EVE4 - Group1/INTC1 */
    this.eveInterruptTable[4] = 29;  /* DSP1 - Group0/INTC0 */
    this.eveInterruptTable[5] = 30;  /* DSP2 - Group0/INTC0 */
    this.eveInterruptTable[6] = 29;  /* IPU1-0 */
    this.eveInterruptTable[7] = 30;  /* IPU2-0 */
    this.eveInterruptTable[8] = 29;  /* HOST */
    this.eveInterruptTable[9] = 30;  /* IPU1-1 */
    this.eveInterruptTable[10] = 30; /* IPU2-1 */

    /*
     * In case of a spec change, follow the process shown below:
     * 1. Update the mailboxBaseAddr Table.
     * 2. Update the eveInterruptTable.
     * 3. Update Virtual Index assignment.
     * 4. Update NUMCORES, NUMEVES and EVEMBX2BASEIDX variables
     *    in order to correctly intialize the mailboxTable.
     */
}

/*
 *  ======== module$static$init ========
 *  Initialize module values.
 */
function module$static$init(state, mod)
{
    var i;

    for (i = 0; i < mod.procIdTable.length; i++) {
        state.fxnTable[i].func  = null;
        state.fxnTable[i].arg   = 0;
    }
}
