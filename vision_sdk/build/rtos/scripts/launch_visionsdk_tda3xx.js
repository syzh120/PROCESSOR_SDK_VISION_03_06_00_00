//
//File Name: launch_visionsdk.js
//Description:
//   Add entries in CCS menu to do common activities
//
//Usage:
//From Command Window without CCS
//  1. Open a command window
//  2. cd <ccs_install_dir>\csv5\ccs_base\scripting\bin
//  3. dss.bat <location_of_script>\launch_visionsdk_tda3xx.js
//
//From CCS Scripting console
//  1. loadJSFile "C:\\ti\\launch_visionsdk_tda3xx.js"
//     <Ignore the error observed on the CCS scripting console
//     "Wrapped java.io.IOException: The handle is invalid (<location_of_script>\
//     launch_visionsdk.js#93)">
//
//Note:
//  1. Search for "edit this" to look at changes that need to be edited
//     for your usage.
//

// Import the DSS packages into our namespace to save on typing
importPackage(Packages.com.ti.debug.engine.scripting)
importPackage(Packages.com.ti.ccstudio.scripting.environment)
importPackage(Packages.java.lang)
importPackage(java.io);
importPackage(java.lang);

//Path to CCXML file
//<edit this>
configFilePath = "C:\\Users\\a0393700\\ti\\CCSTargetConfigurations\\tda3xx_xds200.ccxml";
//<edit this>
disableGels=0

function updateScriptVars(printEnable)
{
 //<edit this> <start>
    //Path to vision-sdk binaries
    baseDir = "x:\\vsdk_latest\\vision_sdk\\binaries\\apps\\tda3xx_evm_bios_all\\vision_sdk\\bin\\tda3xx-evm\\"
    releaseMode = 1;
    ipu1Smp = 0;
    IPU_0_en = 1;
    IPU_1_en = 1;
    DSP_0_en = 1;
    DSP_1_en = 1;
    EVE_0_en = 1;
    testsuite = 0;
    runAfterLoad = 1;
 //<edit this> <end>

    if(releaseMode)
    {
        IPU_0_exe = "vision_sdk_ipu1_0_release.xem4"
        if(ipu1Smp)
        {
            IPU_1_exe = "vision_sdk_ipu1_0_release.xem4"
        }
        else
        {
            IPU_1_exe = "vision_sdk_ipu1_1_release.xem4"
        }
        DSP_0_exe = "vision_sdk_c66xdsp_1_release.xe66"
        DSP_1_exe = "vision_sdk_c66xdsp_2_release.xe66"
        EVE_0_exe = "vision_sdk_arp32_1_release.xearp32F"
    }
    else
    {
        IPU_0_exe = "vision_sdk_ipu1_0_debug.xem4"
        if(ipu1Smp)
        {
            IPU_1_exe = "vision_sdk_ipu1_0_debug.xem4"
        }
        else
        {
            IPU_1_exe = "vision_sdk_ipu1_1_debug.xem4"
        }
        DSP_0_exe = "vision_sdk_c66xdsp_1_debug.xe66"
        DSP_1_exe = "vision_sdk_c66xdsp_2_debug.xe66"
        EVE_0_exe = "vision_sdk_arp32_1_debug.xearp32F"
    }

	if (testsuite == 1)
	{
	   if(releaseMode == 1)
	   {
	       IPU_0_exe = "vision_sdk_ipu1_0_release_testsuite.xem4";
	   }
	   else
	   {
           IPU_0_exe = "vision_sdk_ipu1_0_debug_testsuite.xem4";
	   }
	}

    //Open a debug session
    dsIPU_0 = debugServer.openSession( ".*Cortex_M4_IPU1_C0" );
    dsIPU_1 = debugServer.openSession( ".*Cortex_M4_IPU1_C1" );
    dsDSP_0 = debugServer.openSession( ".*C66xx_DSP1" );
    dsDSP_1 = debugServer.openSession( ".*C66xx_DSP2" );
    dsEVE_0 = debugServer.openSession( ".*ARP32_EVE_1" );

    if(printEnable == "1")
    {
        print("\nCores Enabled:");
        if(IPU_0_en) print("IPU1_0 is enabled!");
        if(IPU_1_en) print("IPU1_1 is enabled!");
        if(DSP_0_en) print("DSP_0 is enabled!");
        if(DSP_1_en) print("DSP_1 is enabled!");
        if(EVE_0_en) print("EVE_0 is enabled!");
    }
}

function printVars()
{
    updateScriptVars("1");
}

function connectTargets()
{
    updateScriptVars("0");

    // Connect targets
    print("Connecting to IPU1_0!");
    dsIPU_0.target.connect();
    if(!disableGels)
    {
        script.setScriptTimeout(2000);
        print("Executing Gels");
        try
        {
            dsIPU_0.expression.evaluate("DSP1SSClkEnable_API()");
        }
        catch(e)
        {
            print("Some error in GEL execution for DSP_0");
        }
        try
        {
            dsIPU_0.expression.evaluate("DSP2SSClkEnable_API()");
        }
        catch(e)
        {
            print("Some error in GEL execution for DSP_1");
        }
        try
        {
            dsIPU_0.expression.evaluate("EVESSClkEnable_API()");
        }
        catch(e)
        {
            print("Some error in GEL execution for EVE");
        }
        script.setScriptTimeout(-1);
    }

    print("Connecting to IPU1_1!");
    dsIPU_1.target.connect();

    print("Connecting to DSP_0!");
    dsDSP_0.target.connect();
    print("Connecting to DSP_1!");
    dsDSP_1.target.connect();
    print("Connecting to EVE_0!");
    dsEVE_0.target.connect();
}

function disconnectTargets()
{
    updateScriptVars("0");

    // Connect targets
    dsIPU_0.target.disconnect();
    dsIPU_1.target.disconnect();
    dsDSP_0.target.disconnect();
    dsDSP_1.target.disconnect();
    dsEVE_0.target.disconnect();
}

function loadTargets_IPU_0() { updateScriptVars("0"); dsIPU_0.target.connect(); if(IPU_0_en) dsIPU_0.memory.loadProgram( baseDir + IPU_0_exe ); }
function loadTargets_IPU_1() { updateScriptVars("0"); dsIPU_1.target.connect(); if(IPU_1_en) dsIPU_1.memory.loadProgram( baseDir + IPU_1_exe ); }
function loadTargets_DSP_0() { updateScriptVars("0"); dsDSP_0.target.connect(); if(DSP_0_en) dsDSP_0.memory.loadProgram( baseDir + DSP_0_exe ); }
function loadTargets_DSP_1() { updateScriptVars("0"); dsDSP_1.target.connect(); if(DSP_1_en) dsDSP_1.memory.loadProgram( baseDir + DSP_1_exe ); }
function loadTargets_EVE_0() { updateScriptVars("0"); dsEVE_0.target.connect(); if(EVE_0_en) dsEVE_0.memory.loadProgram( baseDir + EVE_0_exe ); }


function loadTargets()
{
    updateScriptVars("0");

    // Load the program
	try
	{
        print("Loading IPU_0_exe!");
        loadTargets_IPU_0();
        print("Loading IPU_1_exe!");
        loadTargets_IPU_1();
        print("Loading DSP_0_exe!");
        loadTargets_DSP_0();
        print("Loading DSP_1_exe!");
        loadTargets_DSP_1();
        print("Loading EVE_0_exe!");
        loadTargets_EVE_0();
    }
    catch (e)
    {
        print("Problems while loading!");
    }
}

function loadSymbols_IPU_0() { updateScriptVars("0"); dsIPU_0.target.connect(); if(IPU_0_en) dsIPU_0.symbol.load( baseDir + IPU_0_exe ); }
function loadSymbols_IPU_1() { updateScriptVars("0"); dsIPU_1.target.connect(); if(IPU_1_en) dsIPU_1.symbol.load( baseDir + IPU_1_exe ); }
function loadSymbols_DSP_0() { updateScriptVars("0"); dsDSP_0.target.connect(); if(DSP_0_en) dsDSP_0.symbol.load( baseDir + DSP_0_exe ); }
function loadSymbols_DSP_1() { updateScriptVars("0"); dsDSP_1.target.connect(); if(DSP_1_en) dsDSP_1.symbol.load( baseDir + DSP_1_exe ); }
function loadSymbols_EVE_0() { updateScriptVars("0"); dsEVE_0.target.connect(); if(EVE_0_en) dsEVE_0.symbol.load( baseDir + EVE_0_exe ); }

function loadSymbolsTargets()
{
    updateScriptVars("0");

    // Load the program
    loadSymbols_IPU_0();
    loadSymbols_IPU_1();
    loadSymbols_DSP_0();
    loadSymbols_DSP_1();
    loadSymbols_EVE_0();
}

function resetTargets()
{
    updateScriptVars("0");

    // Run the program
    if(dsIPU_0.target.isConnected()) dsIPU_0.target.reset();
    if(dsIPU_1.target.isConnected()) dsIPU_1.target.reset();
    if(dsDSP_0.target.isConnected()) dsDSP_0.target.reset();
    if(dsDSP_1.target.isConnected()) dsDSP_1.target.reset();
    if(dsEVE_0.target.isConnected()) dsEVE_0.target.reset();
}

function restartTargets()
{
    updateScriptVars("0");

    // Run the program
    if(IPU_0_en) dsIPU_0.target.restart();
    if(IPU_1_en) dsIPU_1.target.restart();
    if(DSP_0_en) dsDSP_0.target.restart();
    if(DSP_1_en) dsDSP_1.target.restart();
    if(EVE_0_en) dsEVE_0.target.restart();
}

function runTargets()
{
    updateScriptVars("0");

    // Run the program
    if(IPU_0_en) dsIPU_0.target.runAsynch();
    if(IPU_1_en) dsIPU_1.target.runAsynch();
    if(DSP_0_en) dsDSP_0.target.runAsynch();
    if(DSP_1_en) dsDSP_1.target.runAsynch();
    if(EVE_0_en) dsEVE_0.target.runAsynch();
}

function haltTargets()
{
    updateScriptVars("0");
    script.setScriptTimeout(5000);

	try
	{
        // Run the program
        if(dsIPU_0.target.isConnected()) dsIPU_0.target.halt();
        if(dsIPU_1.target.isConnected()) dsIPU_1.target.halt();
        if(dsDSP_0.target.isConnected()) dsDSP_0.target.halt();
        if(dsDSP_1.target.isConnected()) dsDSP_1.target.halt();
        if(dsEVE_0.target.isConnected()) dsEVE_0.target.halt();
    }
    catch (e)
    {
        print("Problems while halting!");
    }
    script.setScriptTimeout(-1);
}

function doEverything()
{
    printVars();
    haltTargets();
    connectTargets();
    resetTargets();
    loadTargets();
    if(runAfterLoad == 1)
    {
        runTargets();
    }
}

var ds;
var debugServer;
var script;

// Check to see if running from within CCSv4 Scripting Console
var withinCCS = (ds !== undefined);

// Create scripting environment and get debug server if running standalone
if (!withinCCS)
{
    // Import the DSS packages into our namespace to save on typing
    importPackage(Packages.com.ti.debug.engine.scripting);
    importPackage(Packages.com.ti.ccstudio.scripting.environment);
    importPackage(Packages.java.lang);

    // Create our scripting environment object - which is the main entry point into any script and
    // the factory for creating other Scriptable ervers and Sessions
    script = ScriptingEnvironment.instance();

    // Get the Debug Server and start a Debug Session
    debugServer = script.getServer("DebugServer.1");
}
else // otherwise leverage existing scripting environment and debug server
{
    debugServer = ds;
    script = env;
}

debugServer.setConfig(configFilePath);

if (!withinCCS)
{
    doEverything();
    System.out.println("Press Any key to stop...");
    var reader = new BufferedReader( new InputStreamReader(System['in']) );
    reader.readLine();

    System.out.println("End of application. Exiting");

    dsIPU_0.terminate();
    dsIPU_1.terminate();
    dsDSP_0.terminate();
    dsDSP_1.terminate();
    dsEVE_0.terminate();

    debugServer.stop();
}

if (withinCCS)
{
    dsIPU_0 = debugServer.openSession( ".*Cortex_M4_IPU1_C0" );
    print("Look for new menu under Scripts for IPU1_0!");
    if(disableGels) dsIPU_0.expression.evaluate("GEL_UnloadAllGels()");

    hotmenu.remove("VSDK/Do everything");
    hotmenu.remove("VSDK/Connect targets");
    hotmenu.remove("VSDK/Disconnect targets");
    hotmenu.remove("VSDK/Reset targets");
    hotmenu.remove("VSDK/Restart targets");
    hotmenu.remove("VSDK/Load targets");
    hotmenu.remove("VSDK/Run targets");
    hotmenu.remove("VSDK/Halt targets");

    hotmenu.remove("VSDK/Load symbols/All");
    hotmenu.remove("VSDK/Load symbols/A15_0");
    hotmenu.remove("VSDK/Load symbols/IPU1_0");
    hotmenu.remove("VSDK/Load symbols/IPU1_1");
    hotmenu.remove("VSDK/Load symbols/DSP_0");
    hotmenu.remove("VSDK/Load symbols/DSP_1");
    hotmenu.remove("VSDK/Load symbols/EVE_0");
    hotmenu.remove("VSDK/Load symbols/EVE_1");
    hotmenu.remove("VSDK/Load symbols/EVE_2");
    hotmenu.remove("VSDK/Load symbols/EVE_3");

    hotmenu.remove("VSDK/Load targets/All");
    hotmenu.remove("VSDK/Load targets/A15_0");
    hotmenu.remove("VSDK/Load targets/IPU1_0");
    hotmenu.remove("VSDK/Load targets/IPU1_1");
    hotmenu.remove("VSDK/Load targets/DSP_0");
    hotmenu.remove("VSDK/Load targets/DSP_1");
    hotmenu.remove("VSDK/Load targets/EVE_0");
    hotmenu.remove("VSDK/Load targets/EVE_1");
    hotmenu.remove("VSDK/Load targets/EVE_2");
    hotmenu.remove("VSDK/Load targets/EVE_3");

    hotmenu.remove("VSDK/Print script variables");

    hotmenu.addJSFunction("VSDK/Do everything", "doEverything()");
    hotmenu.addJSFunction("VSDK/Connect targets", "connectTargets()");
    hotmenu.addJSFunction("VSDK/Disconnect targets", "disconnectTargets()");
    hotmenu.addJSFunction("VSDK/Reset targets", "resetTargets()");
    hotmenu.addJSFunction("VSDK/Restart targets", "restartTargets()");
    hotmenu.addJSFunction("VSDK/Load targets", "loadTargets()");
    hotmenu.addJSFunction("VSDK/Run targets", "runTargets()");
    hotmenu.addJSFunction("VSDK/Halt targets", "haltTargets()");

    hotmenu.addJSFunction("VSDK/Load symbols/All",   "loadSymbolsTargets()");
    hotmenu.addJSFunction("VSDK/Load symbols/IPU_0", "loadSymbols_IPU_0()");
    hotmenu.addJSFunction("VSDK/Load symbols/IPU_1", "loadSymbols_IPU_1()");
    hotmenu.addJSFunction("VSDK/Load symbols/DSP_0", "loadSymbols_DSP_0()");
    hotmenu.addJSFunction("VSDK/Load symbols/DSP_1", "loadSymbols_DSP_1()");
    hotmenu.addJSFunction("VSDK/Load symbols/EVE_0", "loadSymbols_EVE_0()");

    hotmenu.addJSFunction("VSDK/Load targets/All",   "loadTargets()");
    hotmenu.addJSFunction("VSDK/Load targets/IPU_0", "loadTargets_IPU_0()");
    hotmenu.addJSFunction("VSDK/Load targets/IPU_1", "loadTargets_IPU_1()");
    hotmenu.addJSFunction("VSDK/Load targets/DSP_0", "loadTargets_DSP_0()");
    hotmenu.addJSFunction("VSDK/Load targets/DSP_1", "loadTargets_DSP_1()");
    hotmenu.addJSFunction("VSDK/Load targets/EVE_0", "loadTargets_EVE_0()");

    hotmenu.addJSFunction("VSDK/Print script variables", "printVars()");
}
