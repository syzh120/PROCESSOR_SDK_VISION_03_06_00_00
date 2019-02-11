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
 * ======== package.xs ========
 */
var UTILS = xdc.loadCapsule('ti/sdo/fc/utils/utils.xs');

/*
 * This var has scope of this file.  It's set in close() and used in
 * validate().
 */
var RMAN;

/*
 *  ======== close ========
 */
function close()
{
    Program.exportModule('xdc.runtime.Log');
    Program.exportModule('xdc.runtime.Assert');
    Program.exportModule('xdc.runtime.Diags');
    Program.exportModule('xdc.runtime.Registry');

    /* For gate create/delete functions */
    xdc.loadPackage('ti.sdo.fc.utils.osalsupport');

    /* To get the iresman header */
    xdc.loadPackage("ti.sdo.fc.ires");

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    xdc.loadPackage("ti.sdo.fc.memutils");

    if ((null == this.Settings.persistentAllocFxn) ||
            (null == this.Settings.persistentFreeFxn)) {

        if (UTILS.usingPackage("ti.sdo.fc.rman")) {

            RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');
            if (RMAN.useDSKT2 == true) {

                this.Settings.persistentAllocFxn = "DSKT2_allocPersistent";
                this.Settings.persistentFreeFxn = "DSKT2_freePersistent";

                /* RMAN should already have done this, but... */
                xdc.useModule("ti.sdo.fc.dskt2.DSKT2");
            }
            else {
                this.Settings.persistentAllocFxn = RMAN.persistentAllocFxn;
                this.Settings.persistentFreeFxn = RMAN.persistentFreeFxn;
            }
        }
    }

    var isa = Program.build.target.isa;

    /* os == undefined implies BIOS, which implies 'dsp' */
    var os = Program.build.target.os;
    var dsp = (os == undefined);

    if (dsp) {
        /* Load low-level Resource manager */
        var RM = xdc.useModule('ti.sdo.edma3.rm.RM');

        if (UTILS.usingPackage("ti.sdo.fc.rman")) {
            RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');
            RM.edma3_max_rm_instances = RMAN.maxAlgs + 1;
        }
        else {
            RM.edma3_max_rm_instances = this.Settings.maxAlgs + 1;
        }

        /* If undefined queue/TC settings, give them default values */
        //Arbitrarily set intMemoryQs to 0
        if (this.Settings.intMemoryQ0 == undefined) {
            this.Settings.intMemoryQ0 = 0;
        }
        if (this.Settings.intMemoryQ1 == undefined) {
            this.Settings.intMemoryQ1 = this.Settings.intMemoryQ0;
        }
        if (this.Settings.intMemoryQ2 == undefined) {
            this.Settings.intMemoryQ2 = this.Settings.intMemoryQ0;
        }
        //Arbitrarily set extMemoryQs to 1
        if (this.Settings.extMemoryQ0 == undefined) {
            this.Settings.extMemoryQ0 = 1;
        }
        if (this.Settings.extMemoryQ1 == undefined) {
            this.Settings.extMemoryQ1 = this.Settings.extMemoryQ0;
        }
        if (this.Settings.extMemoryQ2 == undefined) {
            this.Settings.extMemoryQ2 = this.Settings.extMemoryQ0;
        }

        //Arbitrarily set otherQs to 1
        if (this.Settings.otherQ0 == undefined) {
            this.Settings.otherQ0 = 1;
        }
        if (this.Settings.otherQ1 == undefined) {
            this.Settings.otherQ1 = this.Settings.otherQ0;
        }

        if (UTILS.arrayUndef(this.Settings.queueTCMap)) {
            this.Settings.queueTCMap = [0,1,2,3,4,5,6,7];
        }
        else {
            /* Set the values to either configured values of -1 */
            for (i = 0; i < this.Settings.EDMA3_MAXTCS; i++) {
                this.Settings.queueTCMap[i] =
                        ((this.Settings.queueTCMap[i] == undefined) ?  -1 :
                        this.Settings.queueTCMap[i]);
            }
        }

        if (UTILS.arrayUndef(this.Settings.queuePriority)) {
            this.Settings.queuePriority = [0,0,0,0,0,0,0,0];
        }
        else {
            /* Set the values to either configured values of -1 */
            for (i = 0; i < this.Settings.EDMA3_MAXTCS; i++) {
                this.Settings.queuePriority[i] =
                        ((this.Settings.queuePriority[i] == undefined) ?  -1 :
                        this.Settings.queuePriority[i]);
            }
        }
    }
    else {
        if (os == "Linux") {
            xdc.useModule('ti.sdo.fc.memutils.MEMUTILS');

            /* Load linuxutils resource management support */
            xdc.loadPackage('ti.sdo.linuxutils.edma');

            /* Need this for shared memory APIs */
            xdc.loadPackage('ti.sdo.fc.utils');
        }
    }

    var defaultTccs = [10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;
    var defaultPaRams = [20,20,20,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;
    var defaultEdma = [4,4,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;
    var defaultQdma = [1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;

   if (dsp == false) {
        /* Make sure no unncessary configuration has been done for non-dsp
           targets */
        if (this.Settings.region != 1) {
            print("Warning configuration parameter \"region\" being used. "
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (this.Settings.globalInit != false) {
            print("Warning configuration parameter \"globalInit\" being used. "
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (this.Settings.regionConfig != null) {
            print("Warning configuration parameter \"regionConfig\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (this.Settings.globalConfig != null) {
            print("Warning configuration parameter \"globalConfig\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (!UTILS.arrayUndef(this.Settings.maxTccs)) {
            print("Warning configuration parameter \"maxTccs\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (!(UTILS.arrayUndef(this.Settings.maxPaRams))) {
            print("Warning configuration parameter \"maxPaRams\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (!UTILS.arrayUndef(this.Settings.maxEdmaChannels)) {
            print("Warning configuration parameter \"maxEdmaChannels\" being "
                    + "used. This parameter is not applicable for non-DSP "
                    + "targets. Will be ignored by this module.");
        }
        if (!UTILS.arrayUndef(this.Settings.maxQdmaChannels)) {
            print("Warning configuration parameter \"maxQdmaChannels\" being "
                    + "used. This parameter is not applicable for non-DSP "
                    + "targets. Will be ignored by this module.");
        }

        /* Need this for shared memory module */
        xdc.loadPackage('ti.sdo.fc.utils');
    }

    if ((dsp) && (os == undefined)) {
        //Assume BIOS
        xdc.loadPackage("ti.sysbios");
        //Check for NULL configurations
        if ((null == this.Settings.regionConfig) ||
                (null == this.Settings.globalConfig)) {
            /* Call the function to get the right region/global Configuration */
        }
    }

    for (i = 0; i < this.Settings.EDMA3_MAXGROUPS; i++) {
        this.Settings.maxTccs[i] = ((this.Settings.maxTccs[i] == undefined) ?
                0 : this.Settings.maxTccs[i]);
        this.Settings.maxPaRams[i] = ((this.Settings.maxPaRams[i] == undefined)                 ? 0 : this.Settings.maxPaRams[i]);
        this.Settings.maxEdmaChannels[i] = ((this.Settings.maxEdmaChannels[i]
                == undefined) ? 0 : this.Settings.maxEdmaChannels[i]);
        this.Settings.maxQdmaChannels[i] = ((this.Settings.maxQdmaChannels[i]
                == undefined) ? 0 : this.Settings.maxQdmaChannels[i]);
    }
}

/*
 *  ======== validate ========
 */
function validate()
{
    var suffix = Program.build.target.findSuffix(this);
    var dsp = (((suffix == "64P") || (suffix == "674")) ? true : false);
    var os = Program.build.target.os;

    if (dsp) {
        /* Validate config settings here */
        /*
        if (this.Settings.semCreateFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semCreateFxn.");
        }

        if (this.Settings.semDeleteFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semDeleteFxn.");
        }

        if (this.Settings.semPendFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semPendFxn.");
        }

        if (this.Settings.semPostFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semPostFxn.");
        }
        */
    }

    if (this.Settings.persistentAllocFxn == null) {
        throw("\n\n: EDMA3 error : Configure valid persistentAllocFxn.");
    }

    if (this.Settings.persistentFreeFxn == null) {
        throw("\n\n: EDMA3 error : Configure valid persistentFreeFxn.");
    }
}


/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix;
    var libName;
    var profile;
    var isa = prog.build.target.isa;
    var device = prog.cpu.deviceName;

    if ("findSuffix" in prog.build.target) {
        suffix = prog.build.target.findSuffix(this);
        if (suffix == null) {
            print(this.$name + ".getLibs(): Can't find suffix for " +
                  prog.build.target.name + " target.");
            return ("");
        }
       /* For Arm devices, this package is available only for DM355 and DM365 */
        if (prog.cpu.attrs.cpuCore == "v7A") {
            if (!(device.match("DM355") || (device.match("DM365")))) {
                return (null);
            }
        }
    }
    else {
        suffix = Program.build.target.suffix;
    }

    if (this.Settings.createRMObj) {
        var libs = "edma3.a" + suffix;
    }
    else {
        var libs = "edma3_externalRmObj.a" + suffix;
    }
    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libs).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does"
                    + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }

    return (dir + "/" + libs);
}
