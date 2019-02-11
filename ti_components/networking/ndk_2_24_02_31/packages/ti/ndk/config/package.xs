/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 */

/*
 *  ======== init ========
 */
function init()
{
    // Only process during "cfg" phase
    if (xdc.om.$name != "cfg") {
        return;
    }

    // use the modules required by the NDK OSAL
    if (Program.build.target.name == "C64P"            ||
        Program.build.target.name == "C64P_big_endian" ||
        Program.build.target.name == "C674"            ||
        Program.build.target.name == "C66"             ||
        Program.build.target.name == "C66_big_endian") {

        var Ecm       = xdc.useModule('ti.sysbios.family.c64p.EventCombiner');
    }
    var Hwi       = xdc.useModule('ti.sysbios.hal.Hwi');
    var Error     = xdc.useModule('xdc.runtime.Error');
    var Clock     = xdc.useModule('ti.sysbios.knl.Clock');
    var Semaphore = xdc.useModule('ti.sysbios.knl.Semaphore');
    var Cache     = xdc.useModule('ti.sysbios.hal.Cache');
    var Ndk       = xdc.useModule('ti.ndk.rov.Ndk');
}

/*
 *  ======== close ========
 *  Close this package; optionally (re)set other config parameters in the model.
 *
 *  The close() fxn is called after the user's script is processed, and can be
 *  used to update the current state of the configuration (changes to the
 *  configuration are allowed here).
 */
function close()
{
    // Only process during "cfg" phase
    if (xdc.om.$name != "cfg") {
        return;
    }

    /* get necessary module references */
    var Http       = xdc.module('ti.ndk.config.Http');
    var Global     = xdc.module('ti.ndk.config.Global');

    /*
     *  Validate memory manager page size for HTTP (fix for SDOCM00100419).
     *
     *  The HTTP server will call mmAlloc(sizeof(HTTP_MSG)) at run time.  If
     *  using the Http module, ensure that the memory manager is configured
     *  to have at least the minimum page size to hold that struct
     *  (sizeof(HTTP_MSG) = 1676 bytes. Use mulitple of 32 -> 1696 bytes)
     */
    if (Http.$used && Global.memRawPageSize < 1696) {
        var errMsg = "Error: Invalid memory page size " +
                "(Global.memRawPageSize): " + Global.memRawPageSize +
                ".  Size must be 1,696 bytes (or greater) when using the Http" +
                " module.";
        throw (errMsg);
    }

    var System = xdc.useModule('xdc.runtime.System');

    var Task = xdc.useModule('ti.sysbios.knl.Task');

    /*
     *  Create the NDK stack Task thread
     *
     *  If the config parameter 'stackThreadUser' is set, then this will create
     *  a Task that runs a user defined stack thread.  Otherwise, the Task will
     *  run the ti_ndk_config_Global_stackThread() function and the below
     *  comments apply for that scenario.
     *
     *  The NDK heart beat (Clock instance for llTimerTick()) is now created
     *  at run time within the context of the stack thread
     *  (ti_ndk_config_Global_stackThread).  This thread is now generated
     *  independently of the value of Global.enableCodeGeneration, in order to
     *  support users who want the Global module's auto library linking feature,
     *  but do not want the full blown generated stack thread code.
     *  (fix for SDOCM00086022)
     *
     *  In this case, the stack thread will only contain the Clock creation code
     *  for the heart beat.  In the case of Global.enableCodeGeneration == true
     *  then the stack thread will contain the configuration code that results
     *  from the parameters set by the modules in the ti.ndk.config package, in
     *  addition to the Clock creation code.
     *
     */
    var ndkTaskParams = new Task.Params();
    ndkTaskParams.priority = Global.ndkThreadPri;
    ndkTaskParams.stackSize = Global.ndkThreadStackSize;
    ndkTaskParams.affinity = 0;

    /* If the user configured a stack thread function, create the Task w/ it */
    if (Global.stackThreadUser != null) {
        ndkTaskParams.instance.name = "User's NDK Stack Thread";
        Task.create(Global.stackThreadUser + "", ndkTaskParams);
    }
    else {
        /* Else specify ti_ndk_config_Global_stackThread  as the function */
        ndkTaskParams.instance.name = "NDK Stack Thread";
        Task.create('&ti_ndk_config_Global_stackThread', ndkTaskParams);
    }

    // The NDK needs to know when Tasks are created
    var hooks = new Task.HookSet();
    hooks.registerFxn = '&NDK_hookInit';
    hooks.createFxn = '&NDK_hookCreate';
    hooks.exitFxn = '&NDK_hookExit';
    Task.addHookSet(hooks);

    /*
     *  The Clock module is needed when creating the NDK heartbeat at runtime.
     */
    var Clock = xdc.useModule('ti.sysbios.knl.Clock');

    /*
     * Load the Emac module corresponding to the device selected.  If device is
     * set to "NONE" then do nothing.
     */
    var Emac = xdc.module('ti.ndk.config.Emac');
    if (Emac.device == Emac.EVMOMAPL138) {
        /* load EVMOMAPL138 Emac module */
        try {
            xdc.useModule('ti.drv.omapl138.Emac');
        }
        catch (e) {
            throw ("Error: could not find EVMOMAPL138 Ethernet driver.");
        }
    }
    else if (Emac.device == Emac.TMDXDOCKH52C1) {
        /* load TMDXDOCKH52C1 Emac module */
        try {
            xdc.useModule('ti.drivers.EMAC');
        }
        catch (e) {
            throw ("Error: could not find TMDXDOCKH52C1 Ethernet driver.");
        }
    }
    else if (Emac.device == Emac.DK_LM3S9D96) {
        /* load DK_LM3S9D96 Emac module */
        try {
            xdc.useModule('ti.drivers.EMAC');
        }
        catch (e) {
            throw ("Error: could not find DK_LM3S9D96 Ethernet driver.");
        }
    }
    else if (Emac.device == Emac.NONE) {
        /* do nothing */
    }
    else {
        throw("Error: invalid setting for Emac.device: " + Emac.device);
    }

    /* Explicitly bring in other pkgs this pkg manages (e.g. getLibs()) */
    xdc.loadPackage('ti.ndk');
    xdc.loadPackage('ti.ndk.hal.timer_bios');
    xdc.loadPackage('ti.ndk.os');
    xdc.loadPackage('ti.ndk.hal.userled_stub');
    xdc.loadPackage('ti.ndk.hal.eth_stub');
    xdc.loadPackage('ti.ndk.tools.cgi');
    xdc.loadPackage('ti.ndk.tools.hdlc');
    xdc.loadPackage('ti.ndk.stack');
    xdc.loadPackage('ti.ndk.tools.console');
    xdc.loadPackage('ti.ndk.netctrl');
    xdc.loadPackage('ti.ndk.nettools');
    xdc.loadPackage('ti.ndk.hal.ser_stub');
    xdc.loadPackage('ti.ndk.tools.servers');
}

/*
 *  ======== getLibs ========
 */
function getLibs()
{
    // get necessary module references
    var Global     = xdc.module('ti.ndk.config.Global');
    var Telnet     = xdc.module('ti.ndk.config.Telnet');
    var Http       = xdc.module('ti.ndk.config.Http');
    var Nat        = xdc.module('ti.ndk.config.Nat');
    var DhcpServer = xdc.module('ti.ndk.config.DhcpServer');
    var Dns        = xdc.module('ti.ndk.config.Dns');
    var Ppp        = xdc.module('ti.ndk.config.Ppp');
    var Pppoe      = xdc.module('ti.ndk.config.Pppoe');

    var endianString = (Program.build.target.model.endian == "little") ? "" : "e";
    var semLibString = (Global.useSemLibs) ? "_sem" : "";
    var prefix       = this.packageBase + "../lib/";
    var libsList     = "";
    var stackName    = "";
    var netctrlLib   = "";
    var consoleMin   = "";
    var serverMin    = "";
    var stackLibType = Global.stackLibType;

    /*
     *  This function chooses which library to link in based on the user's
     *  config.  Because we cannot perform a useModule at this stage (because
     *  it may be necessary to enable Nat in order to avoid link time errors)
     *  we must use boolean variables that we have control over to determine
     *  the correct NDK lib to link, instead of the $used attribute.
     */
    var natUsed   = (Nat.$used) ? true : false;
    var pppUsed   = (Ppp.$used) ? true : false;
    var pppoeUsed = (Pppoe.$used) ? true : false;

    // determine the lib's suffix-based directory name
    var suffix = Program.build.target.suffix;

    /*
     * Define set of "constant" libs (i.e. not affected by 'stackLibType' or
     * modules used)
     */
    var libSuffix = ".a" + suffix;
    var libs = [
        "hal/timer_bios/lib/hal_timer_bios" + libSuffix,
        "os/lib/os" + semLibString + libSuffix,
        "hal/userled_stub/lib/hal_userled_stub" + libSuffix,
        "hal/eth_stub/lib/hal_eth_stub" + libSuffix,
        "tools/cgi/lib/cgi" + libSuffix,
        "tools/hdlc/lib/hdlc"  + libSuffix
    ];

    // determine which NETCTRL features are needed based on modules used
    if (DhcpServer.$used || Dns.$used || Nat.$used) {
        // if user wants DHCP/DNS/Nat servers, must bring in "full" lib
        netctrlLib = "netctrl_full";

        /*
         * Protect against potential linker errors if user has set configuration
         * for a "non-NAT" stack library.
         *
         * The 'netctrl_full' library contains references to NAT APIs.  If the
         * user has chosen a stackLibType that does not contain NAT, this must
         * be overridden here, otherwise there will be a linker error:
         *
         *     undefined     first referenced
         *     symbol           in file
         *     >> Compilation failure
         *     ---------     ----------------
         *     _NatSetConfig nettool.lib<natsrv.o674>
         */
        if ((Global.stackLibType == Global.PPP_PPPOE) ||
                (Global.stackLibType == Global.NONE)) {
           // change lib type to have NAT
           stackLibType = Global.NAT_PPP_PPPOE;
           natUsed   = true;
           pppUsed   = true;
           pppoeUsed = true;
        }
        else if (Global.stackLibType == Global.PPP) {
           // change lib type to have NAT
           stackLibType = Global.NAT_PPP;
           natUsed   = true;
           pppUsed   = true;
        }
        else if (Global.stackLibType == Global.MIN) {
           // change lib type to have NAT
           stackLibType = Global.NAT;
           natUsed   = true;
        }
        else {
           /*
            * stackLibType == {NAT, NAT_PPP, NAT_PPP_PPPOE}
            *
            * Flag Nat as used, even if Nat.xdc is not used.  This is needed
            * because netctrl_full lib has a reference to NATOpen(), which in
            * turn has a reference to NatSetConfig(), which is defined in the
            * NAT flavors of the stack library.
            *
            * Without the below, a non-NAT flavor of stack lib will
            * be chosen and this will cause link time errors for undefined
            * symbol "NatSetConfig".
            */
           natUsed   = true;
        }
    }
    else if (Telnet.$used || Http.$used || !(Global.enableCodeGeneration)) {
        /*
         * If user wants Telnet or Http, but not DHCP/DNS/NAT servers, then use
         * "standard" lib.
         *
         * Also must choose standard netctrl lib for legacy applications (in
         * which code generation is disabled)
         */
        netctrlLib = "netctrl";
    }
    else {
        /*
         * If user does not want Telnet/Http/DHCP/DNS/NAT servers, then use
         * "min" lib (this lib is used for both DHCP client and static IP cases)
         */
        netctrlLib = "netctrl_min";
    }

    /*
     * Only link libs without PPPoE references if user is not using PPPoE (_min
     * versions do not have PPPoE references)
     */
    if (!(pppoeUsed)) {
        consoleMin = "_min";
        serverMin  = "_min";
    }

    if (Global.IPv6) {
        // bring in the appropriate IPv6 libs
        libs = libs.concat([
                "tools/console/lib/console" + consoleMin + libSuffix,
                "netctrl/lib/" + netctrlLib + libSuffix,
                "nettools/lib/nettool" + libSuffix,
                "hal/ser_stub/lib/hal_ser_stub" + libSuffix,
                "tools/servers/lib/servers" + serverMin + libSuffix
        ]);

        // Base lib name; 'stk6' for IPv6.
        stackName = "stk6";
    }
    else {
        // else user wants pure IPv4 libs
        libs = libs.concat([
                "tools/console/lib/console" + consoleMin + "_ipv4" + libSuffix,
                "netctrl/lib/" + netctrlLib + "_ipv4" + libSuffix,
                "nettools/lib/nettool_ipv4" + libSuffix,
                "hal/ser_stub/lib/hal_ser_stub" + libSuffix,
                "tools/servers/lib/servers" + serverMin + "_ipv4" + libSuffix
        ]);

        // Base lib name; 'stk' is for IPv4
        stackName = "stk";
    }

    if (Global.enableCodeGeneration) {
        // Determine which flavor of stack library based on user's configuration
        if (!(natUsed) && !(pppUsed) && !(pppoeUsed)) {
            stackLibType = Global.MIN;
        }
        else if ((natUsed) && !(pppUsed) && !(pppoeUsed)) {
            stackLibType = Global.NAT;
        }
        else if ((natUsed) && (pppUsed) && !(pppoeUsed)) {
            stackLibType = Global.NAT_PPP;
        }
        else if ((natUsed) && (pppUsed) && (pppoeUsed) ||
                (natUsed) && !(pppUsed) && (pppoeUsed)) {
            stackLibType = Global.NAT_PPP_PPPOE;
        }
        else if (!(natUsed) && (pppUsed) && !(pppoeUsed)) {
            stackLibType = Global.PPP;
        }
        else if ((!(natUsed) && (pppUsed) && (pppoeUsed)) ||
                (!(natUsed) && !(pppUsed) && (pppoeUsed)) ) {
            /*
             *  NOTE: there is no library that exists for the 2nd case of this if
             *  statement - selecting PPPoE but not PPP - but this case must be
             *  handled nonetheless because it is possible for the user to make
             *  such a selection.
             */
            stackLibType = Global.PPP_PPPOE;
        }
        else {
           // should not hit this
           Global.$logWarning("Could not determine proper library based on user " +
                   " configuration, setting to default of Global.MIN", Global);
        }
    }

    var protocol;
    switch (stackLibType) {
        case Global.NONE:
            // Default behavior - return PPP PPPOE library.
            stackName = (Global.IPv6) ? "stk6_ppp_pppoe" : "stk_ppp_pppoe";
        break;

        // for other cases, user has chosen one of the "stk_*" libs
        case Global.NAT:
           stackName = stackName + "_nat";
        break;

        case Global.NAT_PPP:
            stackName = stackName + "_nat_ppp";
        break;

        case Global.NAT_PPP_PPPOE:
            stackName = stackName + "_nat_ppp_pppoe";
        break;

        case Global.PPP:
            stackName = stackName + "_ppp";
        break;

        case Global.PPP_PPPOE:
            stackName = stackName + "_ppp_pppoe";
        break;

        case Global.MIN:
            stackName = stackName;
        break;


        default:
            print("Error: illegal value for configuration parameter" +
                    " \'Global.stackLibType\':" + stackLibType +
                    ".  Please change your configuration script to set" +
                    " \'Global.stackLibType\' to a valid value.");
            return null;

    }

    // add the stack library version determined above into our lib list
    var stackLib = "stack/lib/" + stackName + libSuffix;
    libs[libs.length] = stackLib;

    /*
     *  Check if this stack library actually exists.  If not, inform user that
     *  it must be built manually
     */
    var stackLibFile = java.io.File(this.packageBase + "../" + stackLib);

    if (!stackLibFile.exists()) {
        print("Error: library \"" + stackLibFile.getPath() + "\" does not " +
                "exist.  Please follow the steps to build this NDK library " +
                "at http://processors.wiki.ti.com/index.php/" +
                "Rebuilding_The_NDK_Core_Using_Gmake");

        return null;
    }

    // careful: some versions of XDC don't like trailing ; in list of libs
    for (i in libs) {
        var absLib = "../" + libs[i];
        if (libsList != "") {
            libsList += ";" + absLib;
        }
        else {
            libsList = absLib;
        }
    }

    return libsList;
}
