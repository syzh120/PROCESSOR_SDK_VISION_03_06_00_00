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
    if ((this.RMAN.useDSKT2 == false) &&
            ((this.RMAN.persistentAllocFxn == null ) ||
                    (this.RMAN.persistentFreeFxn == null))) {
       throw("\n\n  RMAN Error: Config parameter useDSKT2 set to false and "
            + "valid persistentAllocFxn and persistentFreeFxn not set. "
            + "Please re-configure RMAN to either set useDSKT2 to true"
            + " or set valid persistentAllocFxn and persistentFreeFxn.\n");
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix;
    var libName;

    if ("findSuffix" in prog.build.target) {
        suffix = prog.build.target.findSuffix(this);
        if (suffix == null) {
            print(this.$name + ".getLibs(): Can't find suffix for " +
                  prog.build.target.name + " target.");
            return ("");
        }
    }
    else {
        suffix = prog.build.target.suffix;
    }

    var dir = "lib/" + this.profile;

    // Non-BIOS targets use the 'no yield' library.
    if (prog.build.target.os == undefined) {
        libName = "rman.a";
    }
    else {
        libName = "rmanNoYield.a";
    }

    libName += suffix;

    if (!java.io.File(this.packageBase + dir + "/" + libName).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");

       dir = "lib/release";
    }

    return (dir + "/" + libName);
}


/*
 * ======== close ========
 */
function close() {

    var isa = Program.build.target.isa;

    xdc.loadPackage("ti.xdais");

    xdc.loadPackage("ti.sdo.fc.ires");
    xdc.loadPackage("ti.sdo.fc.utils.osalsupport");

    Program.exportModule('xdc.runtime.Log');
    Program.exportModule('xdc.runtime.Assert');
    Program.exportModule('xdc.runtime.Diags');

    xdc.useModule("ti.sdo.fc.ires.nullresource.NULLRES");

    /* Unconditionally, establish dependency on nullresource */
    xdc.loadPackage("ti.sdo.fc.ires.nullresource");

    if ((isa.match(/i686/)) || (isa.match(/v5T/))) {
        this.RMAN.useDSKT2 = false;
    }

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    if ( (this.RMAN.lockFxn != null) &&
            (this.RMAN.lockFxn != "DSKT2_acquireLock")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"lockFxn\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated"
            + " configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.unlockFxn != null) &&
            (this.RMAN.unlockFxn != "DSKT2_releaseLock")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"unlockFxn\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated"
            + " configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.getContextFxn != null) &&
            (this.RMAN.getContextFxn != "DSKT2_getContext")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"getContext\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off. "
            + "Please use RMAN.useDSKT2 flag instead of deprecated"
            + " configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.setContextFxn != null) &&
            (this.RMAN.setContextFxn != "DSKT2_setContext")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"setContext\" set to something other than DSKT2 functions.\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated "
            + "configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.yieldFxn != null) &&
            (this.RMAN.yieldFxn != "TSK_yield")) {
        print("Warning - RMAN has deprecated configuration parameter "
            + "\"yieldFxn\".\n"
            + "Cooperative Preemption support will be turned off.\n"
            + "Please use RMAN.useDSKT2 flag instead of deprecated "
            + "configuration parameters: lockFxn, unlockFxn, setContextFxn,"
            + "getContextFxn, yieldFxn.\n");
        this.RMAN.useDSKT2 = false;
    }

    if ( (this.RMAN.semCreateFxn != null) || (this.RMAN.semDeleteFxn != null) ||
            (this.RMAN.semPendFxn != null) || (this.RMAN.semPostFxn != null) ) {

        print("Warning - RMAN has deprecated the semaphore related "
            + "configuration parameters \"semCreateFxn\", \"semDeleteFxn\", "
            + " \"semPendFxn\", \"semPostFxn\".\n"
            + "These configurations will be ignored.\n"
            + "Default OS specific sempahore implementation will be plugged  "
            + "in automatically using the OSAL. To change it please configure "
            + "the xdc.runtime.knl.Semaphore or SemaphoreMP modules' "
            + "_proxy_ configuration "
            + "with the specific implementation for your OS.\n");
    }

    if (this.RMAN.useDSKT2 == true) {

        xdc.useModule("ti.sdo.fc.dskt2.DSKT2");

        if (this.RMAN.persistentAllocFxn != null) {
            print("Warning - RMAN.persistentAllocFxn was assigned and " +
                    "RMAN.useDSKT2 was set true.  Previous assignment " +
                    "will be overridden with DSKT2_allocPersistent.\n");
        }
        this.RMAN.persistentAllocFxn = "DSKT2_allocPersistent";

        if (this.RMAN.persistentFreeFxn != null) {
            print("Warning - RMAN.persistentFreeFxn was assigned and " +
                    "RMAN.useDSKT2 was set true.  Previous assignment " +
                    "will be overridden with DSKT2_freePersistent.\n");
        }
        this.RMAN.persistentFreeFxn = "DSKT2_freePersistent";
    }

    if ((Program.build.target.os == "Linux")) {
        /* load package for Multi process build of RMAN */
        xdc.loadPackage('ti.sdo.fc.utils');
        xdc.useModule('ti.sdo.fc.memutils.MEMUTILS');
    }
}
