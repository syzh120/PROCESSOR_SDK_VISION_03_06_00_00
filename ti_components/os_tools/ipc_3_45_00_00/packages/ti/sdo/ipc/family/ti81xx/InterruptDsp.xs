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
 *  ======== InterruptDsp.xs ========
 */

var Hwi             = null;
var MultiProc       = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    Hwi         = xdc.useModule("ti.sysbios.family.c64p.Hwi");
    MultiProc   = xdc.useModule("ti.sdo.utils.MultiProc");
    Ipc         = xdc.useModule("ti.sdo.ipc.Ipc");

    this.dspProcId      = MultiProc.getIdMeta("DSP");
    this.videoProcId    = MultiProc.getIdMeta("VIDEO-M3");
    this.vpssProcId     = MultiProc.getIdMeta("VPSS-M3");
    this.hostProcId     = MultiProc.getIdMeta("HOST");
}

function module$static$init(mod, params)
{
    /* HOST to DSP */
    mod.fxnTable[0].func  = null;
    mod.fxnTable[0].arg   = 0;

    /* VIDEO-M3 to DSP */
    mod.fxnTable[1].func  = null;
    mod.fxnTable[1].arg   = 0;

    /* VPSS-M3 to DSP */
    mod.fxnTable[2].func  = null;
    mod.fxnTable[2].arg   = 0;

    mod.numPlugged = 0;
}

/*
 *  ======== viewInitInterrupt ========
 */
function viewInitInterrupt(view)
{
    var InterruptDspModStr = "ti.sdo.ipc.family.ti81xx.InterruptDsp";
    var Program             = xdc.useModule('xdc.rov.Program');
    var InterruptDsp       = xdc.useModule(InterruptDspModStr);
    var MultiProc           = xdc.useModule('ti.sdo.utils.MultiProc');
    var MultiProcCfg        = Program.getModuleConfig('ti.sdo.utils.MultiProc');
    var InterruptDspCfg    = Program.getModuleConfig(InterruptDspModStr);
    var ScalarStructs       = xdc.useModule('xdc.rov.support.ScalarStructs');
    var mod                 = Program.scanRawView(InterruptDspModStr).modState;

    var remoteProcIds = [
        /*
         * [remoteProcId,
         *  fxnTable index,
         *  MBX# (from remote),
         *  MBX# (to remote)]
         */
        [InterruptDspCfg.hostProcId, 0, 3, 0],
        [InterruptDspCfg.videoProcId, 1, 7, 1],
        [InterruptDspCfg.vpssProcId, 2, 9, 2]
    ];

    var MAILBOX_IRQSTATUS_CLR_DSP = (InterruptDspCfg.mailboxBaseAddr + 0x114);
    var MAILBOX_IRQENABLE_SET_DSP = (InterruptDspCfg.mailboxBaseAddr + 0x118);
    var MAILBOX_IRQENABLE_CLR_DSP = (InterruptDspCfg.mailboxBaseAddr + 0x11C);

    function MAILBOX_MESSAGE(M) {
        return (InterruptDspCfg.mailboxBaseAddr + 0x040 + (0x4 * M));
    }

    function MAILBOX_STATUS(M) {
        return (InterruptDspCfg.mailboxBaseAddr + 0x0C0 + (0x4 * M));
    }

    function MAILBOX_REG_VAL(M) {
        return (0x1 << (2 * M));
    }

    for each (procId in remoteProcIds) {
        if (procId[0] != MultiProc.INVALIDID) {
            var entryView = Program.newViewStruct(InterruptDspModStr,
                    'IncomingInterrupts');
            entryView.remoteProcName = MultiProc.getName$view(procId[0]) + " ("
                    + procId[0] + ")";
            entryView.registered = (Number(mod.fxnTable[procId[1]].func) != 0);
            print(entryView.remoteProcName + ": " + mod.fxnTable[procId[1]].func);

            var enabled = Program.fetchStruct(
                    ScalarStructs.S_Bits32$fetchDesc,
                    $addr(MAILBOX_IRQENABLE_SET_DSP), false).elem;
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
