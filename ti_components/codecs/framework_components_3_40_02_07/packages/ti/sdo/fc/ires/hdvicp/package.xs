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

var UTILS = xdc.loadCapsule('ti/sdo/fc/utils/utils.xs');

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
    var suffix = Program.build.target.findSuffix(this);
    var device = Program.cpu.deviceName;
    var isa = Program.build.target.isa;


    if (null == suffix) {
        return (null);
    }

    if ((suffix.match(/64P/)) ||
            (device.match("TMS320DM365") && isa.match(/v5T/))) {
        var lib = "hdvicp.a";
    }
    else if ( isa.match(/x86/) || isa.match(/v7M/) ) {
        var lib = "hdvicp2.a";
    }
    else {
        return (null);
    }

    lib = lib + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }

    return (dir + "/" + lib);
}


/*
 *  ======== close ========
 */
function close()
{
    var os = Program.build.target.os;
    var device = Program.cpu.deviceName;
    var isa = Program.build.target.isa;
    var suffix = Program.build.target.findSuffix(this);

    xdc.useModule('xdc.runtime.Log');
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Diags');

    xdc.useModule("ti.sdo.fc.ires.IRESMAN");
    xdc.loadPackage("ti.xdais");
/*      xdc.useModule('ti.sdo.fc.memutils.MEMUTILS');*/

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if (this.HDVICP2.clearPRCMRegister == undefined) {
        this.HDVICP2.clearPRCMRegister = false;
    }

    /* Check if the yield functions have been defined */
    if ((this.HDVICP2.yieldReleaseFxn == undefined) ||
            (this.HDVICP2.yieldAcquireFxn == undefined) ||
            (this.HDVICP2.getYieldArgsFxn == undefined)) {

        if (UTILS.usingPackage("ti.sdo.fc.rman")) {

            RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');

            if (RMAN.useDSKT2 == true) {
                xdc.useModule("ti.sdo.fc.dskt2.DSKT2");

                /* If using RMAN and useDSKT2 set to true, */
                this.HDVICP2.yieldReleaseFxn = "DSKT2_contextRelease";
                this.HDVICP2.yieldAcquireFxn = "DSKT2_contextAcquire";
                this.HDVICP2.getYieldArgsFxn = "DSKT2_getYieldArgs";
            }
        }
        else if (UTILS.usingPackage("ti.sdo.fc.dskt2")) {
            /* Using DSKT2 */
            this.HDVICP2.yieldReleaseFxn = "DSKT2_contextRelease";
            this.HDVICP2.yieldAcquireFxn = "DSKT2_contextAcquire";
            this.HDVICP2.getYieldArgsFxn = "DSKT2_getYieldArgs";

        }
    }

    /* If the yield functions are undefined still, set them to NULL */
    if ((this.HDVICP2.yieldReleaseFxn == undefined) ||
            (this.HDVICP2.yieldAcquireFxn == undefined) ||
            (this.HDVICP2.getYieldArgsFxn == undefined)) {
        this.HDVICP2.yieldReleaseFxn = "NULL";
        this.HDVICP2.yieldAcquireFxn = "NULL";
        this.HDVICP2.getYieldArgsFxn = "NULL";
    }
    else {
    }

    xdc.loadPackage('ti.sdo.fc.utils.osalsupport');

    if (Program.build.target.os == "Linux") {
        /* Scratch manager and shared memory implementation */
        xdc.loadPackage("ti.sdo.fc.utils");
        xdc.useModule("ti.sdo.linuxutils.vicp.VICP");
    }
    else {
        xdc.useModule("ti.sdo.fc.dskt2.DSKT2");
    }

    if (this.HDVICP2.$used) {

        for (var i = 0; i < this.HDVICP2.MAXRESOURCES ; i++) {
            if (null == this.HDVICP2.memoryBaseAddress[i]) {
                this.HDVICP2.memoryBaseAddress[i] = 0x0;
            }
            if (null == this.HDVICP2.registerBaseAddress[i]) {
                this.HDVICP2.registerBaseAddress[i] = 0x0;
            }
            if (null == this.HDVICP2.resetControlAddress[i]) {
                this.HDVICP2.resetControlAddress[i] = 0x0;
            }
        }

        if ((null == this.HDVICP2.configureFxn) &&
                (null == this.HDVICP2.waitFxn)  &&
                (null == this.HDVICP2.doneFxn)) {

            /*
            print(this.$name + " close(): Configure, wait, done "
                    + "configuration parameters not set to valid "
                    + "functions, default implementations will be "
                    + "used to configure these functions.\n");
            */
            this.HDVICP2.configureFxn =
                    "ti_sdo_fc_ires_hdvicp_HDVICP2_configure";
            this.HDVICP2.waitFxn = "ti_sdo_fc_ires_hdvicp_HDVICP2_wait";
            this.HDVICP2.doneFxn = "ti_sdo_fc_ires_hdvicp_HDVICP2_done";
        }

        if (null == this.HDVICP2.resetFxn) {
            /*
            print(this.$name + " close(): configuration parameter \"resetFxn\" "
                    + "not set to valid "
                    + "function, default implementation will be "
                    + "used to configure this function.\n");
            */
            /* Can pick a function depending on device */
            if (Program.cpu.deviceName == "TMS320TI816X") {
                this.HDVICP2.resetFxn =
                        "ti_sdo_fc_ires_hdvicp_HDVICP2_reset_Netra";
            }
            else if (Program.cpu.deviceName == "OMAP4430") {
                this.HDVICP2.resetFxn =
                        "ti_sdo_fc_ires_hdvicp_HDVICP2_reset_Omap";
            }
            else {
                print(this.$name + " close(): Warning configuration parameter "
                        + " \"resetFxn\" not set to valid function, leaving "
                        + "undefined. Do NOT call this function.");
            }
        }

        if (this.HDVICP2.delegate != undefined) {

            /* Valid function names provided for these functions. Load the
               package that implements these functions */
            xdc.loadPackage(this.delegate);
        }
        else {
            this.HDVICP2.delegate = null;
        }

        if (undefined == this.HDVICP2.configureFxn) {
            this.HDVICP2.configureFxn = null;
        }

        if (undefined == this.HDVICP2.waitFxn) {
            this.HDVICP2.waitFxn = null;
        }

        if (undefined == this.HDVICP2.doneFxn) {
            this.HDVICP2.doneFxn = null;
        }

        if (undefined == this.HDVICP2.resetFxn) {
            this.HDVICP2.resetFxn = null;
        }

        if ((this.HDVICP2.getHDVICP2Fxn == undefined) ||
                (this.HDVICP2.freeHDVICP2Fxn == undefined)) {

            this.HDVICP2.getHDVICP2Fxn = null;
            this.HDVICP2.freeHDVICP2Fxn = null;
        }

        if (this.HDVICP2.timeout == undefined) {
            this.HDVICP2.timeout = this.HDVICP2.FOREVER;
        }
    }

}
