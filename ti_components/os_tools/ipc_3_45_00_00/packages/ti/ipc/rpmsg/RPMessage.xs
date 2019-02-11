/*
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== RPMessage.xs ========
 */

/*
 *  ======== module$use ========
 *  Use other modules required by this module
 */
function module$use()
{
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Diags');
    xdc.useModule('xdc.runtime.Log');
    xdc.useModule('xdc.runtime.Memory');
    xdc.useModule('xdc.runtime.Registry');
    xdc.useModule('xdc.runtime.System');

    xdc.useModule('ti.sysbios.BIOS');
    xdc.useModule('ti.sysbios.gates.GateHwi');
    xdc.useModule('ti.sysbios.knl.Semaphore');
    xdc.useModule('ti.sysbios.knl.Swi');

    xdc.useModule('ti.sdo.utils.List');
    xdc.useModule('ti.sdo.utils.MultiProc');

    var Program = xdc.useModule('xdc.cfg.Program');
    var device = Program.cpu.deviceName;

    switch (device) {
        case "OMAP5430": /* OMAP5 */
            xdc.loadPackage('ti.ipc.family.omap54xx');
            break;

        case "OMAPL138":
            xdc.useModule('ti.ipc.family.omapl138.VirtQueue');
            break;

        case "TMS320TCI6614":
            xdc.useModule('ti.ipc.family.tci6614.VirtQueue');
            break;

        case "Kepler":
        case "TMS320C66AK2E05":
        case "TMS320C66AK2H12":
        case "TMS320TCI6630K2L":
        case "TMS320TCI6636":
        case "TMS320TCI6638":
        case "TCI66AK2G02":
            xdc.useModule('ti.ipc.family.tci6638.VirtQueue');
            break;

        case "Vayu": /* Vayu */
        case "DRA7XX": /* Vayu */
            xdc.useModule('ti.ipc.family.vayu.VirtQueue');
            break;

        default:
            throw new Error("Unspported device: " + device);
            break;
    }

    /* create message pool */
    var HeapBuf = xdc.useModule('ti.sysbios.heaps.HeapBuf');
    var params = new HeapBuf.Params();

    params.blockSize = this.messageBufferSize;
    params.numBlocks = this.numMessageBuffers;
    params.bufSize = this.messageBufferSize * this.numMessageBuffers;
    params.align = 8;

    var pkg = this.$package.$name.replace(/\./g, "_");
    Program.global[pkg+"_RPMessage_heap"] = HeapBuf.create(params);
}
