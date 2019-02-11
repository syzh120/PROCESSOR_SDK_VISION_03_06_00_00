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
 *  ======== InterruptHost.xs ========
 *
 */

var Hwi             = null;
var MultiProc       = null;
var Ipc             = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    Hwi         = xdc.useModule("ti.sysbios.family.arm.a8.intcps.Hwi");
    MultiProc   = xdc.useModule("ti.sdo.utils.MultiProc");
    Ipc         = xdc.useModule("ti.sdo.ipc.Ipc");

    this.dspProcId      = MultiProc.getIdMeta("DSP");
    this.videoProcId    = MultiProc.getIdMeta("VIDEO-M3");
    this.vpssProcId     = MultiProc.getIdMeta("VPSS-M3");
    this.hostProcId     = MultiProc.getIdMeta("HOST");
}

function module$static$init(mod, params)
{
    /* DSP to HOST */
    mod.fxnTable[0].func  = null;
    mod.fxnTable[0].arg   = 0;

    /* VIDEO-M3 to HOST */
    mod.fxnTable[1].func  = null;
    mod.fxnTable[1].arg   = 0;

    /* VPSS-M3 to HOST */
    mod.fxnTable[2].func  = null;
    mod.fxnTable[2].arg   = 0;

    mod.numPlugged = 0;
}

/*
 *  ======== viewInitInterrupt ========
 */
function viewInitInterrupt(view)
{
    var InterruptHostModStr = "ti.sdo.ipc.family.ti81xx.InterruptHost";
    var Program             = xdc.useModule('xdc.rov.Program');
    var InterruptHost       = xdc.useModule(InterruptHostModStr);
    var MultiProc           = xdc.useModule('ti.sdo.utils.MultiProc');
    var MultiProcCfg        = Program.getModuleConfig('ti.sdo.utils.MultiProc');
    var InterruptHostCfg    = Program.getModuleConfig(InterruptHostModStr);
    var ScalarStructs       = xdc.useModule('xdc.rov.support.ScalarStructs');
    var mod                 = Program.scanRawView(InterruptHostModStr).modState;

    var remoteProcIds = [
        /*
         * [remoteProcId,
         *  fxnTable index,
         *  MBX# (from remote),
         *  MBX# (to remote)]
         */
        [InterruptHostCfg.dspProcId, 0, 0, 3],
        [InterruptHostCfg.videoProcId, 1, 6, 4],
        [InterruptHostCfg.vpssProcId, 2, 8, 5]
    ];

    var MAILBOX_IRQSTATUS_CLR_HOST = (InterruptHostCfg.mailboxBaseAddr + 0x104);
    var MAILBOX_IRQENABLE_SET_HOST = (InterruptHostCfg.mailboxBaseAddr + 0x108);
    var MAILBOX_IRQENABLE_CLR_HOST = (InterruptHostCfg.mailboxBaseAddr + 0x10C);

    function MAILBOX_MESSAGE(M) {
        return (InterruptHostCfg.mailboxBaseAddr + 0x040 + (0x4 * M));
    }

    function MAILBOX_STATUS(M) {
        return (InterruptHostCfg.mailboxBaseAddr + 0x0C0 + (0x4 * M));
    }

    function MAILBOX_REG_VAL(M) {
        return (0x1 << (2 * M));
    }

    for each (procId in remoteProcIds) {
        if (procId[0] != MultiProc.INVALIDID) {
            var entryView = Program.newViewStruct(InterruptHostModStr,
                    'IncomingInterrupts');
            entryView.remoteProcName = MultiProc.getName$view(procId[0]) + " ("
                    + procId[0] + ")";
            entryView.registered = (Number(mod.fxnTable[procId[1]].func) != 0);
            print(entryView.remoteProcName + ": " + mod.fxnTable[procId[1]].func);

            var enabled = Program.fetchStruct(
                    ScalarStructs.S_Bits32$fetchDesc,
                    $addr(MAILBOX_IRQENABLE_SET_HOST), false).elem;
            entryView.enabled = ((enabled & MAILBOX_REG_VAL(procId[2])) != 0);

            var intPending = Program.fetchStruct(
                    ScalarStructs.S_Bits32$fetchDesc,
                    $addr(MAILBOX_STATUS(procId[2])), false).elem;
            entryView.intPending = (intPending != 0);

            entryView.payload = $addr(Program.fetchStruct(
                    ScalarStructs.S_Bits32$fetchDesc,
                    $addr(MAILBOX_MESSAGE(procId[2])), false).elem);

            view.elements.$add(entryView);
        }
    }
}
