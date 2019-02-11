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
 *  ======== validate ========
 */
function validate()
{
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var os = Program.build.target.os;
    var isa = Program.build.target.isa;
    var dir = "lib/" + this.profile;
    var suffix  = Program.build.target.findSuffix(this);
    var FC = xdc.module("ti.sdo.fc.global.Settings");

    if (null == suffix) {
        return (null);
    }

    var libs = new Array();

    if (!((isa.match(/v5T/)) || (isa.match(/86/)))) {

        libName = "fcutils";

        libName += ".a" + suffix;

        var dir = "lib/" + this.profile;

        if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
            print(this.$name + ": Requested profile '" + this.profile + "' does "
                    + "not exist.\n\tDefaulting to the 'release' profile");

           dir = "lib/release";
        }

        libs.push(dir + "/" + libName);
    }

    libName = "rmm";

    libName += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");

       dir = "lib/release";
    }

    libs.push(dir + "/" + libName);

    libName = "smgr";

    libName += ".a" + suffix;

    if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");

       dir = "lib/release";

    }
    libs.push(dir + "/" + libName);

/*
    if ((suffix != "64P") && (suffix != "674") && (suffix != "e64P")
        && (suffix != "e674")) {
*/

        var libName = "rmmp";


        libName += ".a" + suffix;

    if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does"
        + " not exist.\n\tDefaulting to the 'release' profile");
        dir = "lib/release";

    }
        libs.push(dir + "/" + libName);

    /* The multiprocess libs required for Arm only (not dsp) */
     if ((isa.match(/v5T/)) || (isa.match(/86/))) {
        libName = "smgrmp";


        libName += ".a" +  suffix;


        if (!java.io.File(this.packageBase + dir + "/" + libName ).exists()) {
            print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");

            dir = "lib/release";

        }
        libs.push(dir + "/" + libName);

        if (os  == "Linux") {

            if (FC.multiProcess) {
                libName = "shmMp";
            }
            else {
                libName = "shmNonMp";
            }


            libName += ".a" +  suffix;


            if (!java.io.File(this.packageBase + dir + "/" + libName).exists()){
                print(this.$name + ": Requested profile '" + this.profile +
                        "' does not exist.\n\tDefaulting to the 'release' "
                        + "profile");

                dir = "lib/release";

            }
            libs.push(dir + "/" + libName);
        }
    }

    return libs.join(";");
}


/*
 * ======== close ========
 */
function close()
{

    if (xdc.om.$name != "cfg") {
        return;
    }

    var isa = Program.build.target.isa;

    Program.exportModule('xdc.runtime.Log');
    Program.exportModule('xdc.runtime.Assert');
    Program.exportModule('xdc.runtime.Diags');

    var FC = xdc.module("ti.sdo.fc.global.Settings");

    xdc.loadPackage("ti.xdais");
    if (this.profile == undefined) {
        this.profile = FC.profile;
    }

    xdc.loadPackage("ti.sdo.fc.memutils");
    xdc.loadPackage("ti.sdo.fc.dskt2");
}
