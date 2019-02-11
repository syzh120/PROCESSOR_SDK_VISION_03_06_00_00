/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 * */
/*
 *  ======== package.xs ========
 *
 */

/*
 *  ======== init ========
 */
function init()
{
    if (xdc.om.$name != 'cfg') {
        return;
    }

    xdc.loadPackage("ti.deh");
}

/*
 *  ======== close ========
 */
function close()
{
    /*  Hack: Include RPMessage in the configuration model.
     *
     *  The real fix is to have the user config script pull in the
     *  IpcMgr module and to set the tansportCombo config param.
     *  Then the IpcMgr would bring in RPMessage if needed.
     */
     xdc.useModule('ti.ipc.rpmsg.RPMessage');

    /*  To maintain compatibility, "use" the IpcMgr module whenever this
     *  package has been loaded. Issue a warning to inform the user that
     *  the application config script should be loading the module, not
     *  the package.
     */
    if (!xdc.module('ti.ipc.ipcmgr.IpcMgr').$used) {
        var IpcMgr = xdc.useModule('ti.ipc.ipcmgr.IpcMgr');

        IpcMgr.$logWarning("Package ti.ipc.ipcmgr loaded but module IpcMgr "
            + "was not used. To eliminate this warning, replace \""
            + "xdc.loadPackage('ti.ipc.ipcmgr')\" with \"xdc.useModule("
            + "'ti.ipc.ipcmgr.IpcMgr')\" in your application config script",
            IpcMgr);
    }
}

/*
 *  ======== Package.getLibs ========
 *  This function is called when a program's configuration files are
 *  being generated and it returns the name of a library appropriate
 *  for the program's configuration.
 */
function getLibs(prog)
{

    /* if custom build flow, do not contribute package library */
    if ("ti.sdo.ipc.Build" in xdc.om) {
        var Build = xdc.om["ti.sdo.ipc.Build"];

        if ((Build.libType == Build.LibType_Custom)
                || (Build.libType == Build.LibType_Debug)) {
            return ("");
        }
    }

    var lib;
    var suffix = prog.build.target.findSuffix(this);

    if (suffix == null) {
        /* no matching lib found in this package, return "" */
        $trace("Unable to locate a compatible library, returning none.",
                1, ['getLibs']);
        return ("");
    }

    /* the location of the libraries are in lib/<profile>/* */
    if (xdc.module("ti.deh.Deh").$used) {
        /* Deh is used */
        lib = "lib/" + this.profile + "/ti.ipc.ipcmgr_deh.a" + suffix;
    }
    else {
        /* Deh is not used */
        lib = "lib/" + this.profile + "/ti.ipc.ipcmgr.a" + suffix;
    }

    /*
     * If the requested profile doesn't exist, we return the 'release' library.
     */
    if (!java.io.File(this.packageBase + lib).exists()) {
        $trace("Unable to locate lib for requested '" + this.profile +
                "' profile.  Using 'release' profile.", 1, ['getLibs']);
        lib = "lib/release/ti.ipc.ipcmgr.a" + suffix;
    }

    return (lib);
}
