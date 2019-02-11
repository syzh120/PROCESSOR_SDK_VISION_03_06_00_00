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
    /* TODO: validate the range of all the config params */
    if (this.EDMA3CHANLITE.$used) {
        if (this.EDMA3CHANLITE.numLogicalChans >
                this.EDMA3CHANLITE.MAX_RESOURCES) {
            throw("\nEDMA3CHANLITE: Error: Configured number of logical " +
                    + "channels exceeds maximum allowed by this module\n");
        }

        if (this.EDMA3CHANLITE.numLogicalChans == 0) {
            print("\nEDMA3CHANLITE: Warning, number of logical resources "
                    + "to be used by this module, set to 0. Please "
                    + "double check config param \"numLogicalChans\"\n");
        }

        if (this.EDMA3CHANLITE.baseAddress == undefined) {
            throw("\nEDMA3CHANLITE: Error: Base address of EDMA device "
                    + "not set. Please set config param \"baseAddress\"\n");
        }

        for (i = 0; i < this.EDMA3CHANLITE.numLogicalChans; i++) {
            var numT = this.EDMA3CHANLITE.logicalChans[i].numTccs;
            var numP = this.EDMA3CHANLITE.logicalChans[i].numParams;
            if (this.EDMA3CHANLITE.logicalChans[i].chan == undefined) {
                throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].chan\" undefined\n");
            }
            if (numT == undefined) {
                throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].numTccs\" undefined\n");
            }

            if (numT > this.EDMA3CHANLITE.MAX_TCCS) {
                throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].numTccs\" is bigger than " +
                        "\"MAX_TCCS\" \n");
            }

            if (numP == undefined) {
                throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].numParams\" undefined\n");
            }

            if (numT > this.EDMA3CHANLITE.MAX_PARAMS) {
                throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].numParams\" is bigger than " +
                        "\"MAX_PARAMS\" \n");
            }

            for (j = 0; j < numT; j++) {
                if (this.EDMA3CHANLITE.logicalChans[i].tccArray[j] == undefined)
                {
                    throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].tccArray[" + j + "]\" not initialized " +
                        "correctly\n");
                }
            }

            for (j = 0; j < numP; j++) {
                if (this.EDMA3CHANLITE.logicalChans[i].paramArray[j] ==
                        undefined) {
                    throw("\nEDMA3CHANLITE: Error: config param \"logicalChans["
                        + i + "].paramArray[" + j + "]\" not initialized " +
                        "correctly\n");
                }
            }
        }
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{

    var device = prog.cpu.deviceName;
    var suffix = "";

    if ((!(this.EDMA3CHAN.$used))  && (this.INTERFACE.$used)){
        return (null);
    }

    suffix = prog.build.target.findSuffix(this);

    if (null == suffix) {
        return (null);
    }

    /* For Arm devices, this package is available only for DM355 and DM365 */
    if (prog.cpu.attrs.cpuCore == "v7A") {
        if (!(device.match("DM355") || (device.match("DM365")))) {
            return (null);
        }
    }

    var lib = "edma3Chan";
    lib += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }

    return (dir + "/" + lib);
}


/*
 *  ======== getSects ========
 */
function getSects() {
   return (null);
}


/*
 * ======== close ========
 */
function close() {

    if ((!(this.EDMA3CHAN.$used))  && (this.INTERFACE.$used)) {
        return;
    }

    xdc.useModule("ti.sdo.fc.ires.IRESMAN");

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if (!(Program.cpu.attrs.cpuCore.match(/ARP32/))) {
        print("useModule Settings: " + prog.cpu.attrs.cpuCore);
        xdc.useModule('ti.sdo.fc.edma3.Settings');
    }
}
