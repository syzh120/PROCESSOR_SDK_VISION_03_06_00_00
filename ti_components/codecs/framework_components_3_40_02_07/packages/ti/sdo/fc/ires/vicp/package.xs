/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *
 */
/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{

    var device = prog.cpu.deviceName;
    var isa = prog.build.target.isa;

    var suffix = Program.build.target.findSuffix(this);

    if (null == suffix) {
        return (null);
    }

    var lib = "vicp";
    lib += ".a" + suffix;

    if (suffix == "64P") {

        var dir = "lib/" + this.profile;

        if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

            print(this.$name + ": Requested profile '" + this.profile + "' does"
                    + " not exist.\n\tDefaulting to the 'release' profile");

            dir = "release";
        }

    }
    else  {
        /* For Arm devices, this package is available only for DM355 and DM365*/
        if (prog.cpu.attrs.cpuCore == "v7A") {
            if (!(device.match("DM355") || (device.match("DM365")))) {
                return (null);
            }
        }

        var dir = "lib/" + this.profile;

        if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

            print(this.$name + ": Requested profile '" + this.profile + "' does"
                    + " not exist.\n\tDefaulting to the 'release' profile");

            dir = "lib/release";
        }
    }

    return (dir + "/" + lib);
}


/*
 * ======== close ========
 */
function close() {
    var isa = prog.build.target.isa;

    xdc.useModule('xdc.runtime.Log');
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Diags');
    xdc.useModule("ti.sdo.fc.ires.IRESMAN");

    xdc.loadPackage("ti.xdais");

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    xdc.loadPackage("ti.sdo.fc.utils.osalsupport");

    if (Program.build.target.os == "Linux") {

        /* Scratch manager and shared memory implementation */
        xdc.loadPackage("ti.sdo.fc.utils");
        xdc.loadPackage("ti.sdo.linuxutils.vicp");
        xdc.useModule('ti.sdo.fc.memutils.MEMUTILS');
    }
}
