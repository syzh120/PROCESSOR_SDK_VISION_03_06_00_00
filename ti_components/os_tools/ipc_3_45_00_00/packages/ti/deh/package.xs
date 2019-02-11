/*
 * Copyright (c) 2011-2014, Texas Instruments Incorporated
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

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix;
    var lib;
    var profile = this.profile;
    var smp = "";
    var plat = "";

    suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return "";  /* nothing to contribute */
    }

    var device = Program.cpu.deviceName;
    switch (device) {
	case "OMAP5430": /* OMAP5 */
	    plat = "_omap5";
	    break;

	case "Vayu":
	case "DRA7XX":
	    plat = "_vayu";
	    break;

	default:
	    var deh = xdc.module("ti.deh.Deh");
	    var watchdog = xdc.module("ti.deh.Watchdog");
	    var stackdbg = xdc.module("ti.deh.StackDbg");
	    if (deh.$used || watchdog.$used || stackdbg.$used) {
		    throw new Error("Unsupported device: " + device);
	    }
	    else {
		/* package is merely referenced and not used */
		return "";
	    }

	    break;
    }

    if (Program.build.target.isa.match(/v7M(|4)/)) {
        smp = "_smp";
    }

    var name = "/ti.deh" + plat + smp + ".a" + suffix;
    lib = "lib/" + profile + name;

    /*
     * If the requested profile doesn't exist, we return the 'release' library.
     */
    if (!java.io.File(this.packageBase + lib).exists()) {
        $trace("Unable to locate lib for requested '" + this.profile +
                "' profile.  Using 'release' profile.", 1, ['getLibs']);
        lib = "lib/release/" + name;
    }

    return lib;
}
