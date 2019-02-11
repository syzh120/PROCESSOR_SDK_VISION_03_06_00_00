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
 */

/*
 *  ======== package.xs ========
 */
var Build = null;

/*
 *  ======== package.close ========
 */
function close()
{
    if (xdc.om.$name != 'cfg') {
        return;
    }

    /* Force the Build module to get used if any module
     * in this package is used.
     */
    for (var mod in this.$modules) {
        if (this.$modules[mod].$used == true) {
            Build = xdc.useModule('ti.sdo.ipc.Build');
            break;
        }
    }

    /* if custom build, add package dependencies to participating modules */
    if ((Build != null) && ((Build.libType == Build.LibType_Custom)
            || (Build.libType == Build.LibType_Debug))) {

        for (var m = 0; m < xdc.om.$modules.length; m++) {
            var mod = xdc.om.$modules[m];

            /* exclude modules which have not been used */
            if (!mod.$used) {
                continue;
            }

            /* exclude modules from this package */
            if (this == mod.$package) {
                continue;
            }

            /* determine if module belongs to an ipc package */
            var ipcPkg = false;
            var pn = mod.$package.$name;

            for (var i = 0; i < Build.$private.ipcPkgs.length; i++) {
                if (pn == Build.$private.ipcPkgs[i]) {
                    ipcPkg = true;
                    break;
                }
            }

            /* if not a proxy module, add dependency from this package */
            if (ipcPkg && !mod.$name.match(/Proxy/)) {
                xdc.useModule(mod.$name);
                continue;
            }

            /* special handling for non-target modules */
            for (var p in Build.$private.cFiles) {
                if (pn == p) {
                    xdc.useModule(mod.$name);
                    continue;
                }
            }
        }
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
    var BIOS = xdc.module('ti.sysbios.BIOS');
    var lib;
    var libPath;
    var suffix;

    var Build = xdc.module('ti.sdo.ipc.Build');

    switch (Build.libType) {
        case Build.LibType_Instrumented:
        case Build.LibType_NonInstrumented:
        case Build.LibType_Custom:
        case Build.LibType_Debug:
            if (Build.$used == false) return (null);
            lib = Build.$private.outputDir + Build.$private.libraryName;
            return ("!" + String(java.io.File(lib).getCanonicalPath()));

        case Build.LibType_PkgLib:
            /* lib path defined in Build.buildLibs() */
            libPath = (BIOS.smpEnabled ? "lib/smpipc/debug" : "lib/ipc/debug");

            /* find a compatible suffix */
            if ("findSuffix" in prog.build.target) {
                suffix = prog.build.target.findSuffix(this);
            }
            else {
                suffix = prog.build.target.suffix;
            }
            return (libPath + "/" + this.$name + ".a" + suffix);

        default:
            throw new Error("unknown Build.libType: " + Build.libType);
    }
}

/*
 *  ======== Package.getSects ========
 */
function getSects()
{
    return "ti/sdo/ipc/linkcmd.xdt";
}
