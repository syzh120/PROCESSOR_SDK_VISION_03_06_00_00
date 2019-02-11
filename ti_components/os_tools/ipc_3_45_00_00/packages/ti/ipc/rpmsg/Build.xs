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
 *  ======== Build.xs ========
 */

/*
 *  ======== getDefs ========
 */
function getDefs()
{
    var defs = "";
    var Program = xdc.module('xdc.cfg.Program');
    var device = Program.cpu.deviceName;
    var target = Program.build.target

    if (xdc.module('ti.sysbios.BIOS').smpEnabled) {
        defs += " -DSMP"; /* TODO where is this used? */
    }

    if (target.isa == "674") {
        switch (device) {
            case "OMAPL138":
                defs += " -DOMAPL138";
                break;
            default:
                throw new Error("Unsupported device: " + device);
                break;
        }
    }
    else if (target.isa == "66") {
        switch (device) {
            case "Kepler":
            case "TMS320C66AK2E05":
            case "TMS320TCI6630K2L":
            case "TMS320TCI6636":
            case "TMS320TCI6638":
            case "TCI66AK2G02":
                defs += " -DTCI6638 -DRPMSG_NS_2_0";
                break;
            case "Vayu":
            case "DRA7XX":
                defs += " -DVAYU -DDSP -DRPMSG_NS_2_0";
                break;
            default:
                throw new Error("Unsupported device: " + device);
                break;
        }
    }
    else if (target.isa.match(/^v7M(|4)$/)) {
        switch (device) {
            case "OMAP4430":
            case "OMAP5430":
                defs += " -DOMAP5 -DRPMSG_NS_2_0";
                break;
            case "Vayu":
            case "DRA7XX":
                defs += " -DVAYU -DRPMSG_NS_2_0";
                break;
            default:
                throw new Error("Unsupported device: " + device);
                break;
        }
    }
    else if (target.isa == "64T") {
        switch (device) {
            case "OMAP5430":
                defs += " -DOMAP5 -DDSP -DRPMSG_NS_2_0";
                break;
            default:
                throw new Error("Unsupported device: " + device);
                break;
        }
    }

    return (defs);
}
