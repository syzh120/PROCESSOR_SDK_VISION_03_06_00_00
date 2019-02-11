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
    var suffix = null;

    suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        print(this.$name + ".getLibs(): Can't find suffix for " +
              prog.build.target.name + " target.");
        return ("");
    }

    if ((null == suffix) || (this.MEMUTILS.noLib == true)) {
        return (null);
    }

    /* If we're here, we have a valid suffix, and need to return a lib */
    var libs = "memutils";

    /* TODO - is there a better way to do this suffix check? */
    if ((this.MEMUTILS.noOS) || (suffix == "86U") || (suffix == "9t")) { // ||
            // (suffix == "m3")) {
        libs += "_std";
    }

    libs += ".a" +  suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libs ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");

       dir = "lib/release";
    }

    return (dir + "/" + libs);
}


/*
 * ======== close ========
 */
function close()
{

    var isa = Program.build.target.isa;

    Program.exportModule('xdc.runtime.Log');
    Program.exportModule('xdc.runtime.Assert');
    Program.exportModule('xdc.runtime.Diags');

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if (!this.MEMUTILS.noOS) {
        if ((Program.build.target.os == undefined) && (!isa.match(/v5T/))) {
            Program.exportModule("ti.sysbios.hal.Cache");

        }
        else {
            if ((Program.build.target.os == "Linux")  && (isa.match(/v5T/))){
                xdc.loadPackage("ti.sdo.linuxutils.cmem");
            }
        }
    }
}
