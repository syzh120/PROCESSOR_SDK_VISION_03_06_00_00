/*
 * Copyright (c) 2011-2015, Texas Instruments Incorporated
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
 *  ======== package.xs ========
 *
 */

var powerEnabled = false;

/*
 *  ======== init ========
 */
function init()
{
    if (xdc.om.$name != 'cfg') {
        return;
    }

    if (Program.build.target.name.match(/M3/) &&
        !Program.platformName.match(/ipu/)) {
        Program.sectMap[".ipcpower_data"] = new Program.SectionSpec();
        Program.sectMap[".ipcpower_data"].type = "NOINIT";
        Program.sectMap[".ipcpower_data"].loadAddress = 0x2100;
    }
}

/*
 *  ======== close ========
 */
function close()
{
    if (xdc.om.$name != "cfg") {
        return;
    }

    Program.exportModule('ti.sysbios.knl.Idle');

    xdc.useModule('ti.sysbios.timers.dmtimer.Timer');

    /* Find out if PM is wanted */
    if ((("ti.sysbios.family.c66.vayu.Power" in xdc.om) &&
         (xdc.module('ti.sysbios.family.c66.vayu.Power').$used)) ||
        (("ti.sysbios.family.c64p.tesla.Power" in xdc.om) &&
         (xdc.module('ti.sysbios.family.c64p.tesla.Power').$used)) ||
        (("ti.sysbios.family.arm.ducati.smp.Power" in xdc.om) &&
         (xdc.module('ti.sysbios.family.arm.ducati.smp.Power').$used))) {
        powerEnabled = true;
    }

    /* plug-in the power event hooks for SMP/BIOS */
    if (Program.build.target.isa.match(/v7M4/) &&
        (Program.platformName.match(/IPU/) ||
         Program.platformName.match(/ipu/))) {
        var BIOS = xdc.module('ti.sysbios.BIOS');
        if ((BIOS.smpEnabled) &&
            ("ti.sysbios.family.arm.ducati.smp.Power" in xdc.om)) {
            var Power = xdc.module('ti.sysbios.family.arm.ducati.smp.Power');
            if (Power.$used) {
                Power.preSuspendHooks.$add("&IpcPower_preSuspend");
                Power.postSuspendHooks.$add("&IpcPower_postResume");
            }
        }
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix;
    var file;
    var libAry = [];
    var profile = this.profile;
    var smp = "";
    var device = prog.cpu.deviceName;
    var platform = "";

    suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return "";  /* nothing to contribute */
    }

    if (prog.platformName.match(/ipu/)) {
        smp = "_smp";
    }

    switch (device) {
        case "OMAP5430":
            platform = "_omap5";
            break;

        case "Vayu":
        case "DRA7XX":
            platform = "_vayu";
            break;

        default:
            throw ("Unspported device: " + device);
            return "";  /* nothing to contribute */
    }

    /* Use the 'null' implementation if PM is not needed */
    if (powerEnabled == false) {
        libAry.push("lib/" + profile + "/ti.pm_null.a" + suffix);
    }
    else {
        /* make sure the library exists, else fallback to a built library */
        file = "lib/" + profile + "/ti.pm" + smp + platform + ".a" + suffix;
        if (java.io.File(this.packageBase + file).exists()) {
            libAry.push(file);
        }
        else {
            file = "lib/release/ti.pm" + smp + platform + ".a" + suffix;
            if (java.io.File(this.packageBase + file).exists()) {
                libAry.push(file);
            }
            else {
                /* fallback to a compatible library built by this package */
                for (var p in this.build.libDesc) {
                    if (suffix == this.build.libDesc[p].suffix) {
                        libAry.push(p);
                        break;
                    }
                }
            }
        }
    }

    return libAry.join(";");
}
