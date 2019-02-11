/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 *  ======== Build.xs ========
 */

var BIOS = null;
var Build = null;

var custom6xOpts = " -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 --mem_model:const=data --mem_model:data=far ";
var customARP32xOpts = " -q --gen_func_subsections ";
var customArmOpts = " -q -ms --opt_for_speed=2 ";
var customGnuArmM3Opts = " ";
var customGnuArmM4Opts = " ";
var customGnuArmM4FOpts = " ";
var customGnuArmA9Opts = " ";
var customGnuArmA8Opts = " ";
var customGnuArmA15Opts = " ";

var ccOptsList = {
    "ti.targets.C64P"                           : custom6xOpts,
    "ti.targets.elf.C64P"                       : custom6xOpts,
    "ti.targets.C64P_big_endian"                : custom6xOpts,
    "ti.targets.elf.C64P_big_endian"            : custom6xOpts,
    "ti.targets.C674"                           : custom6xOpts,
    "ti.targets.elf.C674"                       : custom6xOpts,
    "ti.targets.elf.C67P"                       : custom6xOpts,
    "ti.targets.elf.C64T"                       : custom6xOpts,
    "ti.targets.elf.C66"                        : custom6xOpts,
    "ti.targets.elf.C66_big_endian"             : custom6xOpts,
    "ti.targets.arp32.elf.ARP32"                : customARP32xOpts,
    "ti.targets.arp32.elf.ARP32_far"            : customARP32xOpts,
    "ti.targets.arm.elf.Arm9"                   : customArmOpts,
    "ti.targets.arm.elf.A8F"                    : customArmOpts,
    "ti.targets.arm.elf.A8Fnv"                  : customArmOpts,
    "ti.targets.arm.elf.M3"                     : customArmOpts,
    "ti.targets.arm.elf.M4"                     : customArmOpts,
    "ti.targets.arm.elf.M4F"                    : customArmOpts,
    "gnu.targets.arm.M3"                        : customGnuArmM3Opts,
    "gnu.targets.arm.M4"                        : customGnuArmM4Opts,
    "gnu.targets.arm.M4F"                       : customGnuArmM4FOpts,
    "gnu.targets.arm.A8F"                       : customGnuArmA8Opts,
    "gnu.targets.arm.A9F"                       : customGnuArmA9Opts,
    "gnu.targets.arm.A15F"                      : customGnuArmA15Opts,
};

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    Build = this;

    /*
     * Set default verbose level for custom build flow
     * User can override this in their cfg file.
     */
    var SourceDir = xdc.module("xdc.cfg.SourceDir");
    SourceDir.verbose = 2;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    BIOS = xdc.module("ti.sysbios.BIOS");
    Build = this;

//  if (!Build.doBuild) {
//      return;
//  }

    /*
     * Get the profile associated with the ti.sdo.ipc package.
     * The profile can be specified on a per package basis with a line like
     * this in your .cfg script:
     *
     * xdc.loadPackage('ti.sysbios').profile = "release";
     */
    if (this.$package.profile != undefined) {
        profile = this.$package.profile;
    }
    else {
        profile = Program.build.profile;
    }

    /*
     * Gracefully handle non-supported whole_program profiles
     */
    if (profile.match(/whole_program/)
        && (BIOS.libType != BIOS.LibType_Debug)) {
        /* allow build to proceed */
        BIOS.libType = BIOS.LibType_Debug;
        /* but warning the user */
        BIOS.$logWarning("The '" + profile +
            "' build profile will not be supported " +
            "in future releases of SYS/BIOS.  " +
            "Use 'release' or 'debug' profiles together with the " +
            "'BIOS.libType' configuration parameter to specify your " +
            "preferred library.  See the compatibility section of " +
            "your SYS/BIOS release notes for more information.",
            "Profile Deprecation Warning", BIOS);
    }
    /* inform getLibs() about location of library */
    switch (BIOS.libType) {
        case BIOS.LibType_Instrumented:
            this.$private.libraryName = "/utils.a" + Program.build.target.suffix;
            this.$private.outputDir = this.$package.packageBase + "lib/"
                        + (BIOS.smpEnabled ? "smputils/instrumented/" : "utils/instrumented/");
            break;

        case BIOS.LibType_NonInstrumented:
            this.$private.libraryName = "/utils.a" + Program.build.target.suffix;
            this.$private.outputDir = this.$package.packageBase + "lib/"
                        + (BIOS.smpEnabled ? "smputils/nonInstrumented/" : "utils/nonInstrumented/");
            break;

        case BIOS.LibType_Debug:
        case BIOS.LibType_Custom:
            this.$private.libraryName = "/utils.a" + Program.build.target.suffix;
            var SourceDir = xdc.useModule("xdc.cfg.SourceDir");
            /* if building a pre-built library */
            if (BIOS.buildingAppLib == false) {
                var appName = Program.name.substring(0, Program.name.lastIndexOf('.'));
                this.$private.libDir = this.$package.packageBase + Build.libDir;
                if (!java.io.File(this.$private.libDir).exists()) {
                    java.io.File(this.$private.libDir).mkdir();
                }
            }
            /*
             * If building an application in CCS or package.bld world
             * and libDir has been specified
             */
            if ((BIOS.buildingAppLib == true) && (Build.libDir !== null)) {
                SourceDir.outputDir = Build.libDir;
                var src = SourceDir.create("utils");
                src.libraryName = this.$private.libraryName.substring(1);
                this.$private.outputDir = src.getGenSourceDir();
            }
            else {
                var curPath = java.io.File(".").getCanonicalPath();
                /* If package.bld world AND building an application OR pre-built lib */
                if (java.io.File(curPath).getName() != "configPkg") {
                    var appName = Program.name.substring(0, Program.name.lastIndexOf('.'));
                    appName = appName + "_p" + Program.build.target.suffix + ".src";
                    SourceDir.outputDir = "package/cfg/" + appName;
                    SourceDir.toBuildDir = ".";
                    var src = SourceDir.create("utils");
                    src.libraryName = this.$private.libraryName.substring(1);
                    this.$private.outputDir = src.getGenSourceDir();
                }
                /* Here ONLY if building an application in CCS world */
                else {
                    /* request output source directory for generated files */
                    var appName = Program.name.substring(0, Program.name.lastIndexOf('.'));
                    appName = appName + "_" + Program.name.substr(Program.name.lastIndexOf('.')+1);
                    SourceDir.toBuildDir = "..";
                    var src = SourceDir.create("utils/");
                    src.libraryName = this.$private.libraryName.substring(1);

                    /* save this directory in our private state (to be read during
                    * generation, see Gen.xdt)
                    */
                    this.$private.outputDir = src.getGenSourceDir();
                }
            }
            break;
    }
}

/*
 * Add pre-built Instrumented and Non-Intrumented release libs
 */
var utilsSources = "utils/MultiProc.c " +
                   "utils/List.c " +
                   "utils/NameServerRemoteNull.c " +
                   "utils/NameServer.c ";

var utilsPackages = [
    "ti.sdo.utils",
];

var asmListNone = [
];

var cFiles = {
    "ti.sdo.io.DriverTypes" :
        { cSources: [] },
}

function getDefaultCustomCCOpts()
{
    var BIOS = xdc.module('ti.sysbios.BIOS');

    /* start with target.cc.opts */
    var customCCOpts = Program.build.target.cc.opts;

    /* add target unique custom ccOpts */
    if (!(ccOptsList[Program.build.target.$name] === undefined)) {
        customCCOpts += ccOptsList[Program.build.target.$name];
    }

    /* Gnu targets need to pick up ccOpts.prefix and suffix */
    if (Program.build.target.$name.match(/gnu/)) {
        customCCOpts += " -O3 ";
        customCCOpts += " " + Program.build.target.ccOpts.prefix + " ";
        customCCOpts += " " + Program.build.target.ccOpts.suffix + " ";
    }
    else if (Program.build.target.$name.match(/iar/)) {
        customCCOpts += " --mfc ";
    }
    else {
        /* ti targets do program level compile */
        customCCOpts += " --program_level_compile -o3 -g " +
                "--optimize_with_debug ";
    }

    /* undo optimizations if this is a Debug build */
    if (BIOS.libType == BIOS.LibType_Debug) {
        if (Program.build.target.$name.match(/gnu/)) {
            customCCOpts = customCCOpts.replace("-O3","");
            /* add in stack frames for stack back trace */
            customCCOpts += " -mapcs ";
        }
        else {
            customCCOpts = customCCOpts.replace(" -o3","");
            customCCOpts = customCCOpts.replace(" --optimize_with_debug","");
            if (Program.build.target.$name.match(/arm/)) {
                customCCOpts = customCCOpts.replace(" --opt_for_speed=2","");
            }
        }
    }

    return (customCCOpts);
}

/*
 *  ======== getDefs ========
 */
function getDefs()
{
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Diags = xdc.module("xdc.runtime.Diags");
    var BIOS = xdc.module("ti.sysbios.BIOS");

    var defs = "";

    if ((BIOS.assertsEnabled == false) ||
        ((Defaults.common$.diags_ASSERT == Diags.ALWAYS_OFF)
            && (Defaults.common$.diags_INTERNAL == Diags.ALWAYS_OFF))) {
        defs += " -Dxdc_runtime_Assert_DISABLE_ALL";
    }

    if (BIOS.logsEnabled == false) {
        defs += " -Dxdc_runtime_Log_DISABLE_ALL";
    }

    return (defs);
}

/*
 *  ======== getCFiles ========
 */
function getCFiles(target)
{
    var BIOS = xdc.module("ti.sysbios.BIOS");
    var localSources = "utils/UTILS.c ";

    /*
     * logic to trim the C files down to just what the application needs
     * 3/2/11 disabled for now ...
     */
    if (BIOS.buildingAppLib == true) {
        for each (var mod in Program.targetModules()) {
            var mn = mod.$name;
            var pn = mn.substring(0, mn.lastIndexOf("."));
            var packageMatch = false;

            for (var i = 0; i < utilsPackages.length; i++) {
                if (pn == utilsPackages[i]) {
                    packageMatch = true;
                    break;
                }
            }

            if (packageMatch && !mn.match(/Proxy/)) {
                if (cFiles[mn] === undefined) {
                    var prefix = mn.substr(mn.indexOf("sdo")+4);
                    var mod = mn.substr(mn.lastIndexOf(".")+1);
                    prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                    prefix = prefix.replace(/\./g, "/");
                    localSources += prefix + mod + ".c ";
                }
                else {
                    for (i in cFiles[mn].cSources) {
                        var prefix = mn.substr(mn.indexOf("sdo")+8);
                        prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                        prefix = prefix.replace(/\./g, "/");
                        localSources += prefix + cFiles[mn].cSources[i] + " ";
                    }
                }
            }
        }
    }
    else {
        localSources += utilsSources;
    }

    /* remove trailing " " */
    localSources = localSources.substring(0, localSources.length-1);

    return (localSources);
}

/*
 *  ======== getAsmFiles ========
 */
function getAsmFiles(target)
{
    return (asmListNone);
}

/*
 *  ======== getLibs ========
 */
function getLibs(pkg)
{
    var BIOS = xdc.module("ti.sysbios.BIOS");

    switch (BIOS.libType) {
        case BIOS.LibType_Custom:
        case BIOS.LibType_Instrumented:
        case BIOS.LibType_NonInstrumented:
        case BIOS.LibType_Debug:
            return null;

        default:
            throw new Error("BIOS.libType not supported: " + BIOS.libType);
            break;
    }
}

/*
 *  ======== getProfiles ========
 *  Determines which profiles to build for.
 *
 *  Any argument in XDCARGS which does not contain platform= is treated
 *  as a profile. This way multiple build profiles can be specified by
 *  separating them with a space.
 */
function getProfiles(xdcArgs)
{
    /*
     * cmdlProf[1] gets matched to "whole_program,debug" if
     * ["abc", "profile=whole_program,debug"] is passed in as xdcArgs
     */
    var cmdlProf = (" " + xdcArgs.join(" ") + " ").match(/ profile=([^ ]+) /);

    if (cmdlProf == null) {
        /* No profile=XYZ found */
        return [];
    }

    /* Split "whole_program,debug" into ["whole_program", "debug"] */
    var profiles = cmdlProf[1].split(',');

    return profiles;
}

/*
 *  ======== buildLibs ========
 *  This function generates the makefile goals for the libraries
 *  produced by a package.
 */
function buildLibs(objList, relList, filter, xdcArgs)
{
    var Build = xdc.useModule('xdc.bld.BuildEnvironment');

    for (var i = 0; i < Build.targets.length; i++) {
        var targ = Build.targets[i];

        /* skip target if not supported */
        if (!supportsTarget(targ, filter)) {
            continue;
        }

        var profiles = getProfiles(xdcArgs);

        /* If no profiles were assigned, use only the default one. */
        if (profiles.length == 0) {
            profiles[0] = "debug";
        }

        for (var j = 0; j < profiles.length; j++) {
            var ccopts = "";
            var asmopts = "";

            if (profiles[j] == "smp") {
                var libPath = "lib/smputils/debug/";
                ccopts += " -Dti_sysbios_BIOS_smpEnabled__D=TRUE";
                asmopts += " -Dti_sysbios_BIOS_smpEnabled__D=TRUE";
            }
            else {
                var libPath = "lib/utils/debug/";
                /* build all package libs using Hwi macros */
                ccopts += " -Dti_sysbios_Build_useHwiMacros";
                ccopts += " -Dti_sysbios_BIOS_smpEnabled__D=FALSE";
                asmopts += " -Dti_sysbios_BIOS_smpEnabled__D=FALSE";
            }

            /* confirm that this target supports this profile */
            if (targ.profiles[profiles[j]] !== undefined) {
                var profile = profiles[j];
                var lib = Pkg.addLibrary(libPath + Pkg.name,
                                targ, {
                                profile: profile,
                                copts: ccopts,
                                aopts: asmopts,
                                releases: relList
                                });
                lib.addObjects(objList);
            }
        }
    }
}

/*
 *  ======== supportsTarget ========
 *  Returns true if target is in the filter object. If filter
 *  is null or empty, that's taken to mean all targets are supported.
 */
function supportsTarget(target, filter)
{
    var list, field;

    if (filter == null) {
        return true;
    }

    /*
     * For backwards compatibility, we support filter as an array of
     * target names.  The preferred approach is to specify filter as
     * an object with 'field' and 'list' elements.
     *
     * Old form:
     *     var trgFilter = [ "Arm9", "Arm9t", "Arm9t_big_endian" ]
     *
     * New (preferred) form:
     *
     *     var trgFilter = {
     *         field: "isa",
     *         list: [ "v5T", "v7R" ]
     *     };
     *
     */
    if (filter instanceof Array) {
        list = filter;
        field = "name";
    }
    else {
        list = filter.list;
        field = filter.field;
    }

    if (list == null || field == null) {
        throw("invalid filter parameter, must specify list and field!");
    }

    if (field == "noIsa") {
        if (String(','+list.toString()+',').match(','+target["isa"]+',')) {
            return (false);
        }
        return (true);
    }

    /*
     * add ',' at front and and tail of list and field strings to allow
     * use of simple match API.  For example, the string is updated to:
     * ',v5T,v7R,' to allow match of ',v5t,'.
     */
    if (String(','+list.toString()+',').match(','+target[field]+',')) {
        return (true);
    }

    return (false);
}
