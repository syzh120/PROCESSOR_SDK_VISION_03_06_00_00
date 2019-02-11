/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 *  ======== instrumented.cfg.xs ========
 */

var BIOS = xdc.module('ti.sysbios.BIOS');

BIOS.libType = BIOS.LibType_Custom;
BIOS.buildingAppLib = false;
BIOS.assertsEnabled = true;
BIOS.logsEnabled = true;

var SourceDir = xdc.module("xdc.cfg.SourceDir");
SourceDir.verbose = 1;

/* remove all symbolic debug info */
if (Program.build.target.$name.match(/gnu/)) {
    BIOS.customCCOpts = BIOS.customCCOpts.replace("-g","");
}
else if (!Program.build.target.$name.match(/iar/)) {
    BIOS.customCCOpts = BIOS.customCCOpts.replace("-g","");
    BIOS.customCCOpts = BIOS.customCCOpts.replace("--optimize_with_debug","");
    BIOS.customCCOpts += "--symdebug:none ";
    /* suppress warnings regarding .asmfunc and .endasmfunc */
    BIOS.customCCOpts += "--asm_define\".asmfunc= \" --asm_define\".endasmfunc= \" ";
}

/* suppress un-placed sections warning from m3 Hwi.meta$init() */
if (Program.sectMap[".vecs"] !== undefined) {
    Program.sectMap[".vecs"].type = "DSECT";
}
if (Program.sectMap[".resetVecs"] !== undefined) {
    Program.sectMap[".resetVecs"].type= "DSECT";
}
