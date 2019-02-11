/*
 * Copyright (c) 2010 - 2012, Texas Instruments Incorporated
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

var UTILS = xdc.loadCapsule("ti/sdo/fc/utils/utils.xs");

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix;
    var libName;
    var profile;
    var isa = prog.build.target.isa;
    var dir = "lib/" + this.profile;

    suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        print(this.$name + ".getLibs(): Can't find suffix for " +
                prog.build.target.name + " target.");
        return ("");
    }

    libName = "ecpy.a";

    if (!this.ECPY.cachedIresMode) {
        print(this.$name + ": WARNING: ECPY.cachedIresMode=false variant is" +
               " deprecated.\n\tDefaulting to the cachedIresMode=true variant");
    }

    libs =  libName + suffix;

    if (!java.io.File(this.packageBase + dir + "/" + libs ).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");

       dir = "lib/release";

    }

    return (dir + "/" + libs);
}

/*
 *  ======== getSects ========
 */
function getSects() {

   return (null);
}

/*
 *  ======== close ========
 */
function close() {

    if (xdc.om.$name != "cfg") {
        return;
    }

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if ((null == this.ECPY.persistentAllocFxn) ||
            (null == this.ECPY.persistentFreeFxn)) {

        if (UTILS.usingPackage("ti.sdo.fc.rman")) {

            RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');
            if (RMAN.useDSKT2 == true) {

                print("Setting to dskt2's functions ");
                this.ECPY.persistentAllocFxn = "DSKT2_allocPersistent";
                this.ECPY.persistentFreeFxn = "DSKT2_freePersistent";

                /* RMAN should already have done this, but... */
                xdc.useModule("ti.sdo.fc.dskt2.DSKT2");
            }
            else {
                print("Setting to rman's functions ");
                this.ECPY.persistentAllocFxn = RMAN.persistentAllocFxn;
                this.ECPY.persistentFreeFxn = RMAN.persistentFreeFxn;
            }
        }
    }

    xdc.loadPackage("ti.xdais");
    xdc.loadPackage("ti.sdo.fc.ires");
    xdc.loadPackage("ti.sdo.fc.utils");
}

function validate() {
}
/*
 *  @(#) ti.sdo.fc.ecpy; 1, 0, 0,10; 8-26-2010 17:48:49; /db/atree/mk/fc-n13x/src/
 */
