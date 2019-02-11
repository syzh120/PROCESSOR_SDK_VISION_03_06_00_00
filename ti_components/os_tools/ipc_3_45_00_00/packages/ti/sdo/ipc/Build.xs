/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
var Ipc = null;

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

var ipcPackages = [
    "ti.sdo.ipc",
    "ti.sdo.ipc.family.omap4430",
    "ti.sdo.ipc.family.omap3530",
    "ti.sdo.ipc.family.da830",
    "ti.sdo.ipc.family.dm6446",
    "ti.sdo.ipc.family.ti81xx",
    "ti.sdo.ipc.family.arctic",
    "ti.sdo.ipc.family.c647x",
    "ti.sdo.ipc.family.c6a8149",
    "ti.sdo.ipc.family.tci663x",
    "ti.sdo.ipc.family.tda3xx",
    "ti.sdo.ipc.family.vayu",
    "ti.sdo.ipc.gates",
    "ti.sdo.ipc.heaps",
    "ti.sdo.ipc.notifyDrivers",
    "ti.sdo.ipc.nsremote",
    "ti.sdo.ipc.transports",
    "ti.sdo.utils",
    "ti.ipc.family.tci6614",
    "ti.ipc.family.tci6638",
    "ti.ipc.family.vayu",
    "ti.ipc.namesrv",
    "ti.ipc.remoteproc",
    "ti.ipc.transports"
];

var cFiles = {
    "ti.ipc.ipcmgr" : {
        cSources: [ "IpcMgr.c" ]
    },
    "ti.ipc.family.vayu" : {
        cSources: [ "VirtQueue.c" ]
    },
    "ti.ipc.rpmsg" : {
        cSources: [ "NameMap.c", "RPMessage.c" ]
    }
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

    /* register onSet hooks */
    var GetSet = xdc.module("xdc.services.getset.GetSet");
    GetSet.onSet(this, "libType", _setLibType);

    /* Construct default customCCOpts value.
     * User can override this in their cfg file.
     */
    Build.customCCOpts = Build.getDefaultCustomCCOpts();

    /* needed by IPackage.close() method */
    Build.$private.ipcPkgs = ipcPackages;
    Build.$private.cFiles = cFiles;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    BIOS = xdc.module("ti.sysbios.BIOS");
    var profile;

    /* inform ti.sdo.utils.Build *not* to contribute libraries */
//  xdc.module("ti.sdo.utils.Build").doBuild = false;

    /* if Build.libType is undefined, use BIOS.libType */
    if (Build.libType == undefined) {
        switch (BIOS.libType) {
            case BIOS.LibType_Instrumented:
                Build.libType = Build.LibType_Instrumented;
                break;
            case BIOS.LibType_NonInstrumented:
                Build.libType = Build.LibType_NonInstrumented;
                break;
            case BIOS.LibType_Custom:
                Build.libType = Build.LibType_Custom;
                break;
            case BIOS.LibType_Debug:
                Build.libType = Build.LibType_Debug;
                break;
        }
    }

    /*  Get the profile associated with the ti.sdo.ipc package. The
     *  profile may be specified per package with a line like this
     *  in your .cfg script:
     *
     *  xdc.loadPackage('ti.sdo.ipc').profile = "release";
     */
    if (this.$package.profile != undefined) {
        profile = this.$package.profile;
    }
    else {
        profile = Program.build.profile;
    }

    /* gracefully handle non-supported whole_program profiles */
    if (profile.match(/whole_program/) &&
            (Build.libType != Build.LibType_Debug)) {

        /* allow build to proceed */
        Build.libType = Build.LibType_Debug;
        /* but warning the user */
        Build.$logWarning(
            "The '" + profile + "' build profile will not be supported " +
            "in future releases of IPC. Use 'release' or 'debug' profiles " +
            "together with the 'Build.libType' configuration parameter to " +
            "specify your preferred library. See the compatibility section " +
            "of your IPC release notes for more information.",
            "Profile Deprecation Warning", Build);
    }

    /* inform getLibs() about location of library */
    switch (Build.libType) {
        case Build.LibType_Instrumented:
            this.$private.libraryName = "/ipc.a" + Program.build.target.suffix;
            this.$private.outputDir = this.$package.packageBase + "lib/" +
                (BIOS.smpEnabled ? "smpipc/instrumented/":"ipc/instrumented/");
            break;

        case Build.LibType_NonInstrumented:
            this.$private.libraryName = "/ipc.a" + Program.build.target.suffix;
            this.$private.outputDir = this.$package.packageBase + "lib/" +
                (BIOS.smpEnabled ? "smpipc/nonInstrumented/" :
                "ipc/nonInstrumented/");
            break;

        case Build.LibType_Debug:
        case Build.LibType_Custom:
            this.$private.libraryName = "/ipc.a" + Program.build.target.suffix;
            var SourceDir = xdc.useModule("xdc.cfg.SourceDir");
            /* if building a pre-built library */
            if (BIOS.buildingAppLib == false) {
                var appName = Program.name.substring(0,
                        Program.name.lastIndexOf('.'));
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
                var src = SourceDir.create("ipc");
                src.libraryName = this.$private.libraryName.substring(1);
                this.$private.outputDir = src.getGenSourceDir();
            }
            else {
                var curPath = java.io.File(".").getCanonicalPath();
                /* If package.bld world AND building an application OR
                 * pre-built lib... */
                if (java.io.File(curPath).getName() != "configPkg") {
                    var appName = Program.name.substring(0,
                            Program.name.lastIndexOf('.'));
                    appName = appName + "_p" + Program.build.target.suffix +
                            ".src";
                    SourceDir.outputDir = "package/cfg/" + appName;
                    SourceDir.toBuildDir = ".";
                    var src = SourceDir.create("ipc");
                    src.libraryName = this.$private.libraryName.substring(1);
                    this.$private.outputDir = src.getGenSourceDir();
                }
                /* Here ONLY if building an application in CCS world */
                else {
                    /* request output source directory for generated files */
                    var appName = Program.name.substring(0,
                            Program.name.lastIndexOf('.'));
                    appName = appName + "_" + Program.name.substr(
                            Program.name.lastIndexOf('.')+1);
                    SourceDir.toBuildDir = "..";
                    var src = SourceDir.create("ipc/");
                    src.libraryName = this.$private.libraryName.substring(1);

                    /*  save this directory in our private state (to be
                     *  read during generation, see Gen.xdt)
                     */
                    this.$private.outputDir = src.getGenSourceDir();
                }
            }
            break;
    }
}

/*
 *  ======== module$validate ========
 *  Some redundant tests are here to catch changes since
 *  module$static$init() and instance$static$init().
 */
function module$validate()
{
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Diags = xdc.module("xdc.runtime.Diags");
    var libType = getEnumString(Build.libType);

    switch (Build.libType) {
        case Build.LibType_Instrumented:
            if (Build.assertsEnabled == false) {
                Build.$logWarning(
                        "Build.assertsEnabled must be set to true when " +
                        "Build.libType == Build." + libType + ". " + "Set " +
                        "Build.libType = Build.LibType_Custom to build a " +
                        "custom library or update your configuration.",
                        Build, "assertsEnabled");
            }
            if (Build.logsEnabled == false) {
                Build.$logWarning(
                        "Build.logsEnabled must be set to true when " +
                        "Build.libType == Build." + libType + ". " + "Set " +
                        "Build.libType = Build.LibType_Custom to build a " +
                        "custom library or update your configuration.",
                        Build, "logsEnabled");
            }
            break;

        case Build.LibType_NonInstrumented:
            if ((Build.assertsEnabled == true) &&
                    Build.$written("assertsEnabled")){
                Build.$logWarning(
                        "Build.assertsEnabled must be set to false when " +
                        "Build.libType == Build." + libType + ". " + "Set " +
                        "Build.libType = Build.LibType_Custom to build a " +
                        "custom library or update your configuration.",
                        Build, "assertsEnabled");
            }
            if ((Build.logsEnabled == true) && Build.$written("logsEnabled")) {
                Build.$logWarning(
                        "Build.logsEnabled must be set to false when " +
                        "Build.libType == Build." + libType + ". " + "Set " +
                        "Build.libType = Build.LibType_Custom to build a " +
                        "custom library or update your configuration.",
                        Build, "logsEnabled");
            }
            break;

        case Build.LibType_Custom:
            if ((Build.assertsEnabled == true)
                && (Defaults.common$.diags_ASSERT == Diags.ALWAYS_OFF)
                && (Defaults.common$.diags_INTERNAL == Diags.ALWAYS_OFF)) {
                Build.$logWarning(
                        "Build.assertsEnabled should be set to 'false' when " +
                        "Defaults.common$.diags_ASSERT == Diags.ALWAYS_OFF.",
                        Build, "assertsEnabled");
            }
            break;
    }
}

/*
 *  ======== getCCOpts ========
 */
function getCCOpts(target)
{
    var ccOpts = "";

    if (target.$name.match(/^ti\.targets\./)) {
        if (("ti.ipc.rpmsg" in xdc.om) || ("ti.ipc.transports" in xdc.om)) {
            ccOpts += " --gcc";
        }
    }

    return (Build.customCCOpts + ccOpts);
}

/*
 *  ======== getEnumString ========
 *  Return the enum value as a string.
 *
 *  Example usage:
 *  If obj contains an enumeration type property "Enum enumProp"
 *
 *  view.enumString = getEnumString(obj.enumProp);
 */
function getEnumString(enumProperty)
{
    /*  Split the string into tokens in order to get rid of the
     *  huge package path that precedes the enum string name.
     *  Return the last two tokens concatenated with "_".
     */
    var enumStrArray = String(enumProperty).split(".");
    var len = enumStrArray.length;
    return (enumStrArray[len - 1]);
}

/*
 * Add pre-built Instrumented and Non-Intrumented release libs
 */
var ipcSources  =  "ti/sdo/ipc/GateMP.c " +
                   "ti/sdo/ipc/ListMP.c " +
                   "ti/sdo/ipc/SharedRegion.c " +
                   "ti/sdo/ipc/MessageQ.c " +
                   "ti/sdo/ipc/Ipc.c " +
                   "ti/sdo/ipc/Notify.c " +
                   "ti/ipc/namesrv/NameServerRemoteRpmsg.c " +
                   "ti/ipc/remoteproc/Resource.c ";

var gatesSources = "ti/sdo/ipc/gates/GatePeterson.c " +
                   "ti/sdo/ipc/gates/GatePetersonN.c " +
                   "ti/sdo/ipc/gates/GateMPSupportNull.c ";

var heapsSources = "ti/sdo/ipc/heaps/HeapBufMP.c " +
                   "ti/sdo/ipc/heaps/HeapMemMP.c " +
                   "ti/sdo/ipc/heaps/HeapMultiBufMP.c ";

var notifyDriverSources =
                   "ti/sdo/ipc/notifyDrivers/NotifyDriverCirc.c " +
                   "ti/sdo/ipc/notifyDrivers/NotifySetupNull.c " +
                   "ti/sdo/ipc/notifyDrivers/NotifyDriverShm.c ";

var nsremoteSources =
                   "ti/sdo/ipc/nsremote/NameServerRemoteNotify.c " +
                   "ti/sdo/ipc/nsremote/NameServerMessageQ.c ";

var transportsSources =
                   "ti/sdo/ipc/transports/TransportShm.c " +
                   "ti/sdo/ipc/transports/TransportShmCircSetup.c " +
                   "ti/sdo/ipc/transports/TransportShmNotifySetup.c " +
                   "ti/sdo/ipc/transports/TransportShmCirc.c " +
                   "ti/sdo/ipc/transports/TransportShmNotify.c " +
                   "ti/sdo/ipc/transports/TransportShmSetup.c " +
                   "ti/sdo/ipc/transports/TransportNullSetup.c " ;

var utilsSources = "ti/sdo/utils/MultiProc.c " +
                   "ti/sdo/utils/List.c " +
                   "ti/sdo/utils/NameServerRemoteNull.c " +
                   "ti/sdo/utils/NameServer.c ";

var commonSources = ipcSources +
                    gatesSources +
                    heapsSources +
                    notifyDriverSources +
                    nsremoteSources +
                    transportsSources;

var C64PSources  = "ti/sdo/ipc/gates/GateAAMonitor.c " +
                   "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/gates/GateHWSem.c " +
                   "ti/sdo/ipc/family/dm6446/NotifySetup.c " +
                   "ti/sdo/ipc/family/dm6446/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/dm6446/InterruptDsp.c " +
                   "ti/sdo/ipc/family/omap3530/NotifySetup.c " +
                   "ti/sdo/ipc/family/omap3530/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/omap3530/InterruptDsp.c ";

var C66Sources   = "ti/sdo/ipc/gates/GateHWSem.c " +
                   "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/tci663x/Interrupt.c " +
                   "ti/sdo/ipc/family/tci663x/MultiProcSetup.c " +
                   "ti/sdo/ipc/family/tci663x/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/tci663x/NotifySetup.c " +
                   "ti/sdo/ipc/family/vayu/InterruptDsp.c " +
                   "ti/sdo/ipc/family/vayu/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/vayu/NotifySetup.c " +
                   "ti/sdo/ipc/family/tda3xx/InterruptDsp.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifySetup.c " +
                   "ti/ipc/family/tci6614/Interrupt.c " +
                   "ti/ipc/family/tci6614/VirtQueue.c " +
                   "ti/ipc/family/tci6614/NotifySetup.c " +
                   "ti/ipc/family/tci6638/VirtQueue.c " +
                   "ti/ipc/family/vayu/VirtQueue.c ";

var C674Sources  = "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/da830/NotifySetup.c " +
                   "ti/sdo/ipc/family/da830/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/da830/InterruptDsp.c " +
                   "ti/sdo/ipc/family/arctic/NotifySetup.c " +
                   "ti/sdo/ipc/family/arctic/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/arctic/InterruptDsp.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifySetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/InterruptDsp.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifySetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/InterruptDsp.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyDriverMbx.c ";

var C647xSources = "ti/sdo/ipc/family/c647x/Interrupt.c " +
                   "ti/sdo/ipc/family/c647x/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/c647x/MultiProcSetup.c " +
                   "ti/sdo/ipc/family/c647x/NotifySetup.c ";

var C64TSources  = "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/omap4430/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/omap4430/NotifySetup.c " +
                   "ti/sdo/ipc/family/omap4430/InterruptDsp.c ";

var M3Sources    = "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/omap4430/NotifySetup.c " +
                   "ti/sdo/ipc/family/omap4430/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/omap4430/InterruptDucati.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifySetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/InterruptDucati.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifySetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/InterruptDucati.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/vayu/InterruptIpu.c " +
                   "ti/sdo/ipc/family/vayu/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/vayu/NotifySetup.c " +
                   "ti/sdo/ipc/family/tda3xx/InterruptIpu.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifySetup.c " +
                   "ti/ipc/family/vayu/VirtQueue.c ";

var M4Sources    = "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/vayu/InterruptIpu.c " +
                   "ti/sdo/ipc/family/vayu/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/vayu/NotifySetup.c " +
                   "ti/sdo/ipc/family/tda3xx/InterruptIpu.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifySetup.c " +
                   "ti/ipc/family/vayu/VirtQueue.c ";

var Arm9Sources  = "ti/sdo/ipc/family/dm6446/NotifySetup.c " +
                   "ti/sdo/ipc/family/dm6446/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/dm6446/InterruptArm.c " +
                   "ti/sdo/ipc/family/da830/NotifySetup.c " +
                   "ti/sdo/ipc/family/da830/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/da830/InterruptArm.c ";

var A8FSources   = "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifySetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/InterruptHost.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifySetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/InterruptHost.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/omap3530/NotifySetup.c " +
                   "ti/sdo/ipc/family/omap3530/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/omap3530/InterruptHost.c ";

var A8gSources  =  "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifySetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/InterruptHost.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/ti81xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifySetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/InterruptHost.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyMbxSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/omap3530/NotifySetup.c " +
                   "ti/sdo/ipc/family/omap3530/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/omap3530/InterruptHost.c ";

var A15gSources  = "ti/sdo/ipc/family/vayu/InterruptHost.c " +
                   "ti/sdo/ipc/family/vayu/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/vayu/NotifySetup.c " +
                   "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/gates/GateHWSem.c " +
                   "ti/sdo/ipc/family/tci663x/Interrupt.c " +
                   "ti/sdo/ipc/family/tci663x/MultiProcSetup.c " +
                   "ti/sdo/ipc/family/tci663x/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/tci663x/NotifySetup.c ";

var ARP32Sources = "ti/sdo/ipc/gates/GateHWSpinlock.c " +
                   "ti/sdo/ipc/family/arctic/NotifySetup.c " +
                   "ti/sdo/ipc/family/arctic/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/arctic/InterruptArp32.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifySetup.c " +
                   "ti/sdo/ipc/family/c6a8149/NotifyCircSetup.c " +
                   "ti/sdo/ipc/family/c6a8149/InterruptEve.c " +
                   "ti/sdo/ipc/family/vayu/InterruptArp32.c " +
                   "ti/sdo/ipc/family/vayu/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/vayu/NotifySetup.c " +
                   "ti/sdo/ipc/family/tda3xx/InterruptArp32.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifyDriverMbx.c " +
                   "ti/sdo/ipc/family/tda3xx/NotifySetup.c ";

var cList = {
    "ti.targets.C64P"                   : commonSources + C647xSources +
                                                C64PSources,
    "ti.targets.C64P_big_endian"        : commonSources + C647xSources +
                                                C64PSources,
    "ti.targets.C674"                   : commonSources + C674Sources,

    "ti.targets.elf.C64P"               : commonSources + C647xSources +
                                                C64PSources,
    "ti.targets.elf.C64P_big_endian"    : commonSources + C647xSources +
                                                C64PSources,
    "ti.targets.elf.C674"               : commonSources + C674Sources,
    "ti.targets.elf.C64T"               : commonSources + C64TSources,
    "ti.targets.elf.C66"                : commonSources + C647xSources +
                                                C66Sources,
    "ti.targets.elf.C66_big_endian"     : commonSources + C647xSources +
                                                C66Sources,

    "ti.targets.arp32.elf.ARP32"        : commonSources + ARP32Sources,
    "ti.targets.arp32.elf.ARP32_far"    : commonSources + ARP32Sources,

    "ti.targets.arm.elf.Arm9"           : commonSources + Arm9Sources,
    "ti.targets.arm.elf.A8F"            : commonSources + A8FSources,
    "ti.targets.arm.elf.A8Fnv"          : commonSources + A8FSources,
    "ti.targets.arm.elf.M3"             : commonSources + M3Sources,
    "ti.targets.arm.elf.M4"             : commonSources + M4Sources,
    "ti.targets.arm.elf.M4F"            : commonSources + M4Sources,

    "gnu.targets.arm.A15F"              : commonSources + A15gSources,
    "gnu.targets.arm.A8F"               : commonSources + A8gSources,
    "gnu.targets.arm.M3"                : commonSources + M3Sources,
    "gnu.targets.arm.M4"                : commonSources + M4Sources,
    "gnu.targets.arm.M4F"               : commonSources + M4Sources,
};

var asmListNone = [
];

var asmList64P = [
    "ti/sdo/ipc/gates/GateAAMonitor_asm.s64P",
];

var asmList = {
    "ti.targets.C64P"                   : asmList64P,
    "ti.targets.C64P_big_endian"        : asmList64P,
    "ti.targets.C674"                   : asmList64P,

    "ti.targets.elf.C64P"               : asmList64P,
    "ti.targets.elf.C64P_big_endian"    : asmList64P,
    "ti.targets.elf.C674"               : asmList64P,

    "ti.targets.elf.C64T"               : asmListNone,
    "ti.targets.elf.C66"                : asmListNone,
    "ti.targets.elf.C66_big_endian"     : asmListNone,

    "ti.targets.arp32.elf.ARP32"        : asmListNone,
    "ti.targets.arp32.elf.ARP32_far"    : asmListNone,

    "ti.targets.arm.elf.Arm9"           : asmListNone,
    "ti.targets.arm.elf.A8F"            : asmListNone,
    "ti.targets.arm.elf.A8Fnv"          : asmListNone,
    "ti.targets.arm.elf.M3"             : asmListNone,
    "ti.targets.arm.elf.M4"             : asmListNone,
    "ti.targets.arm.elf.M4F"            : asmListNone,

    "gnu.targets.arm.M3"                : asmListNone,
    "gnu.targets.arm.M4"                : asmListNone,
    "gnu.targets.arm.M4F"               : asmListNone,
    "gnu.targets.arm.A8F"               : asmListNone,
    "gnu.targets.arm.A9F"               : asmListNone,
    "gnu.targets.arm.A15F"              : asmListNone,
};

function getDefaultCustomCCOpts()
{

    /* start with target.cc.opts */
    var customCCOpts = Program.build.target.cc.opts;

    /* add target unique custom ccOpts */
    if (!(ccOptsList[Program.build.target.$name] === undefined)) {
        customCCOpts += ccOptsList[Program.build.target.$name];
    }

    /* gnu targets need to pick up ccOpts.prefix and suffix */
    if (Program.build.target.$name.match(/gnu/)) {
        customCCOpts += " -O3 ";
        customCCOpts += " " + Program.build.target.ccOpts.prefix + " ";
        customCCOpts += " " + Program.build.target.ccOpts.suffix + " ";
    }
    else if (Program.build.target.$name.match(/iar/)) {
        throw new Error("IAR not supported by IPC");
    }
    else {
        /* ti targets do program level compile */
        customCCOpts += " --program_level_compile -o3 -g " +
                "--optimize_with_debug ";
    }

    /* undo optimizations if this is a debug build */
    if (Build.libType == Build.LibType_Debug) {
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
    var MessageQ = xdc.module("ti.sdo.ipc.MessageQ");

    var defs = "";

    if ((Build.assertsEnabled == false) ||
        ((Defaults.common$.diags_ASSERT == Diags.ALWAYS_OFF)
            && (Defaults.common$.diags_INTERNAL == Diags.ALWAYS_OFF))) {
        defs += " -Dxdc_runtime_Assert_DISABLE_ALL";
    }

    if (Build.logsEnabled == false) {
        defs += " -Dxdc_runtime_Log_DISABLE_ALL";
    }

    defs += " -Dti_sdo_ipc_MessageQ_traceFlag__D=" +
            (MessageQ.traceFlag ? "TRUE" : "FALSE");

    if ("ti.ipc.ipcmgr.IpcMgr" in xdc.om) {
        defs += xdc.module("ti.ipc.ipcmgr.IpcMgr").getDefs();
    }

    if ("ti.ipc.rpmsg" in xdc.om) {
        defs += xdc.module('ti.ipc.rpmsg.Build').getDefs();
    }

    var InterruptDucati =
            xdc.module("ti.sdo.ipc.family.ti81xx.InterruptDucati");

    /* If we truely know which platform we're building against,
     * add these application specific -D's
     */
    if (BIOS.buildingAppLib == true) {
        defs += " -Dti_sdo_ipc_family_ti81xx_InterruptDucati_videoProcId__D="
                + InterruptDucati.videoProcId;
        defs += " -Dti_sdo_ipc_family_ti81xx_InterruptDucati_hostProcId__D="
                + InterruptDucati.hostProcId;
        defs += " -Dti_sdo_ipc_family_ti81xx_InterruptDucati_vpssProcId__D="
                + InterruptDucati.vpssProcId;
        defs += " -Dti_sdo_ipc_family_ti81xx_InterruptDucati_dspProcId__D="
                + InterruptDucati.dspProcId;
        defs +=
            " -Dti_sdo_ipc_family_ti81xx_InterruptDucati_ducatiCtrlBaseAddr__D="
            + InterruptDucati.ducatiCtrlBaseAddr;
        defs +=
            " -Dti_sdo_ipc_family_ti81xx_InterruptDucati_mailboxBaseAddr__D="
            + InterruptDucati.mailboxBaseAddr;
    }

    return (defs);
}

/*
 *  ======== getCFiles ========
 */
function getCFiles(target)
{
    var localSources = "";

    if (BIOS.buildingAppLib == true) {
        var targetModules = Program.targetModules();

        for (var m = 0; m < targetModules.length; m++) {
            var mod = targetModules[m];
            var mn = mod.$name;
            var pn = mod.$package.$name;

            /* determine if this is an ipc package */
            var packageMatch = false;

            for (var i = 0; i < ipcPackages.length; i++) {
                if (pn == ipcPackages[i]) {
                    packageMatch = true;
                    break;
                }
            }

            if (packageMatch && !mn.match(/Proxy/)) {
                localSources += mn.replace(/\./g, "/") + ".c" + " ";
            }
        }

        /* special handling for non-target modules */
        for (var p in cFiles) {
            if (p in xdc.om) {
                for (var f in cFiles[p].cSources) {
                    localSources += p.replace(/\./g, "/")
                            + "/" + cFiles[p].cSources[f] + " ";
                }
            }
        }
    }
    else {
        localSources += cList[target];
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
    return (asmList[target]);
}

/*
 *  ======== getLibs ========
 *  This function called by all IPC packages except ti.sdo.ipc package.
 */
function getLibs(pkg)
{
    var libPath = "";
    var name = "";
    var suffix;

    switch (Build.libType) {
        case Build.LibType_Custom:
        case Build.LibType_Instrumented:
        case Build.LibType_NonInstrumented:
        case Build.LibType_Debug:
            return null;

        case Build.LibType_PkgLib:
            throw new Error("internal error: Build.getLibs() called with " +
                    "incorret context (libType == PkgLib)");
            break;

        default:
            throw new Error("Build.libType not supported: " + Build.libType);
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
                var libPath = "lib/smpipc/debug/";
                ccopts += " -Dti_sysbios_BIOS_smpEnabled__D=TRUE";
                asmopts += " -Dti_sysbios_BIOS_smpEnabled__D=TRUE";
            }
            else {
                var libPath = "lib/ipc/debug/";
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

/*
 *  ======== _setLibType ========
 *  The "real-time" setter setLibType function
 *  This function is called whenever libType changes.
 */
function _setLibType(field, val)
{
    var Build = this;

    if (val == Build.LibType_Instrumented) {
        Build.assertsEnabled = true;
        Build.logsEnabled = true;
    }
    else if (val == Build.LibType_NonInstrumented) {
        Build.assertsEnabled = false;
        Build.logsEnabled = false;
    }
    else if (val == Build.LibType_Custom) {
        Build.assertsEnabled = true;
        Build.logsEnabled = true;
    }
    else if (val == Build.LibType_Debug) {
        Build.assertsEnabled = true;
        Build.logsEnabled = true;
    }
    else if (val == Build.LibType_PkgLib) {
        Build.assertsEnabled = true;
        Build.logsEnabled = true;
    }
    else {
        print(Build.$name + ": unknown libType setting: " + val);
    }

    /* re-construct default Build.customCCOpts */
    Build.customCCOpts = Build.getDefaultCustomCCOpts();
}
