/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== Main.xs ========
 *  This is the entry point for the regression scripts; the code in this file
 *  manages the entire regression test procedure. This file is the entry point
 *  because the code sits outside any functions, so it gets executed 
 *  automatically.
 *
 *  This file implements a command line interface for the scripts. See
 *  regression\doc\UsersGuide.doc for a detailed description of the 
 *  arguments.
 *
 *
 */
 
//var testFile;
//var numCores = 0;


/*
 *  ======== getFile ========
 *  java.io.File interperets the backslashes in paths as escape chars.
 *  This helper function fixes that.
 */
function getFile(filename)
{
    return(java.io.File(java.io.File(filename).getCanonicalPath()));
}


/* 
 * ======== run ========
 * Entry point for the scripts.
 */
function run(args)
{
    var Main = xdc.useModule('runscript.Main');
    var Run = xdc.useModule('runscript.Run');
   
    /* Parse any command line arguments */
    parseArgs(args);

    /* Setup the Run module based on 'settings' */
    Run.tempLogDir = Main.settings.tempLogDir;
    
    var xmlApps = null;
    if (Main.fileName.indexOf('xml') != -1) {
        /* Read in the XML file */
        try {
            var batchXMLObj = xdc.loadXML(getFile(Main.fileName));
        }
        catch(e) {
            print("Error reading XML File: \"" + Main.fileName + "\"");
            print(e);
            java.lang.System.exit(0);
        }
        
        xmlApps = batchXMLObj.testList;
    }
    
    
    script = new Packages.com.ti.ccstudio.scripting.environment.ScriptingEnvironment.instance();
    /* Turn off all console output from DSS */
    script.traceSetConsoleLevel(Packages.com.ti.ccstudio.scripting.environment.TraceLevel.OFF);

    script.setScriptTimeout(Main.settings.timeout * 3);
    
    var total=0;
        var pass=0;
        var fail=0; 
        var result;
        var failedList = new Array();
        for (var i=0; i < Main.iter; i++)
        {
 
    
    if (xmlApps == null) {
       var server = script.getServer("DebugServer.1");
       server.setConfig(Main.ccxmlConfigFile);
       if(Main.gelFile != "")
       {
         Main.loadGel(server);
       }
       Main.connectCpus(server);
    
       result= Run.runTest(Main.fileName, Main.numCores, "");
       total+=1;
        if(result == "fail")
        {
           fail+=1;
        }
        else
        {
            pass+=1;
        }
        print("Total Test: " + total+"   Passed: "+pass+"   Failed: "+fail)
    }
    else {
	   for each (var test in xmlApps) 
	   {
	   print("Executing test suite " +String(test.@name));
	   Main.addCpu("ti.platform.simxxx", String(test.@cpu), false);
       var server = script.getServer("DebugServer.1");
       server.setConfig(String(test.@ccxmlConfigFile));
	   Main.gelFile=String(test.@gel);
       if(Main.gelFile != "")
       {
         Main.loadGel(server);
       }
       Main.connectCpus(server);
       xmltestApps=test.apps.app
		for each (var app in xmltestApps) {
            /* Run regressions on the test list. */
            var fileName = app.@exec.toString();
            
            print("======== Iteration=\>"+i+" " + fileName + " ========");    
            if (app.@num.toString() == "") {
                var numCores = Main.numCores;
            }
            else {
                var numCores = Number(app.@num);
            }
            result=Run.runTest(fileName, numCores, String(app.@ref));
            total+=1;
            if(result == "fail")
            {
               fail+=1;
               failedList.push(fileName);
            }
            else
            {
              pass+=1;
            }
            print("Total Test: " + total+"   Passed: "+pass+"   Failed: "+fail)
            
          }
		  Main.terminateSessions();
        }
		 
	  }

    }

        /* Output results */
        print("===============================================");
        print("=============Final Test Result================");
        print("===============================================");
        print("Total Test: " + total+"   Passed: "+pass+"   Failed: "+fail)
		if(fail > 0)
		{
          print("Failed Tests list: "+failedList);
		}
		else
		{
          print("All Tests Passed");
          print("Verified");		  
		}
    
   

    java.lang.System.exit(0);
} 

/*
 *  ======== parseArgs ========
 */
function parseArgs(args)
{
    var Main = xdc.useModule('runscript.Main');

    
    /*  
     * The first argument should always be the absolute path to settings.xs.
     * settings.xs is a configuration file that specifies paths, such as the 
     * default search path, the package root, and the results directory.
     */
    Main.settings = xdc.loadCapsule(args[0]);
    
    for (var i = 1; i < args.length; i++) {
        if (args[i] == "-n") {
            Main.numCores = Number(args[i + 1]);
            i++;
        }
        else if (args[i] == "-i") {
            Main.iter = Number(args[i + 1]);
            i++;
        }
        else if (args[i] == "-v") {
            Main.enableTracing = true;
        }
        else {
            Main.fileName = args[i];
        }
    }
    
    if (Main.numCores === undefined) {
        Main.numCores = Main.cpus.length;
    }
    
    Main.logPrint("parseArgs: numCores = " + Main.numCores + ", fileName = " + Main.fileName  +", iterations = " + Main.iter);

}

/* 
 * ======== addCpu ========
 */
function addCpu(buildName, ccsName, alwaysConnect)
{
    var cpu = new this.RegressionCpu();
    
    if (buildName == null) {
        throw("Main.addCpu: buildName cannot be NULL");
    }
    if (ccsName == null) {
        throw("Main.addCpu: ccsName cannot be NULL");
    }    
    
    cpu.buildName = buildName;
    cpu.ccsName = ccsName;
    cpu.session = null;
    cpu.alwaysConnect = alwaysConnect;
    
    this.cpus.$add(cpu);
}

/* 
 * ======== setPlatformTarget ========
 */
function setPlatformTarget(platform, target)
{
    var map = new this.PlatformTargetMap();
    
    if (platform == null) {
        throw("Main.setPlatformTarget: platform cannot be NULL");
    }
    if (target == null) {
        throw("Main.setPlatformTarget: target cannot be NULL");
    }    
    
    map.platform = platform;
    map.target = target;
    
    this.platformTargetMap.$add(map);
}

/* 
 * ======== getPlatformTarget ========
 */
function getPlatformTarget(platform)
{
    for each(var map in this.platformTargetMap) {
        if (map.platform == platform) {
            return (map.target);
        }
    }
    
    return (null);
}

/*
 *  ======== containsCpu ========
 */
function containsCpu(buildCpuName) 
{
    for (var i in this.cpus) {
        var myCpu = this.cpus[i];
        if (myCpu.buildName == buildCpuName) {
            return (true);
        }
    }
    return (false);
}

/*
 *  ======== getSession ========
 */
function getSession(coreNum) 
{
    if (this.cpus.length > coreNum) {
        return (this.cpus[coreNum].session);
    }
    print("ERROR: Cpu " + ccsCpuName + " does not exist");
    Main.terminateSessions();
    java.lang.System.exit(0);
}


/*
 *  ======== connectCpus ========
 */
function loadGel(debugServer) 
{
   
        try {
            myCpu = this.cpus[0];
            Main.logPrint("Trying to load gel to " + myCpu.ccsName);
            myCpu.session = debugServer.openSession(this.CCSPlatform, myCpu.ccsName);
            myCpu.session.expression.evaluate('GEL_LoadGel("' + Main.gelFile + '")');
           
        }
        catch (e) {
            print("ERROR: Couldn't load gel file "+Main.gelFile + " to "+ myCpu.ccsName);
            print(e);
            java.lang.System.exit(0);
        }
    
    
    
}

/*
 *  ======== connectCpus ========
 */
function connectCpus(debugServer) 
{
    for (var i = 0; i < this.numCores; i++) {
        try {
            myCpu = this.cpus[i];
            Main.logPrint("Trying to connect to " + myCpu.ccsName);
            myCpu.session = debugServer.openSession(this.CCSPlatform, myCpu.ccsName);
            myCpu.session.target.connect();
        }
        catch (e) {
            print("ERROR: Couldn't open session on " + myCpu.ccsName);
            print(e);
            java.lang.System.exit(0);
        }
    }
    
    print("Connected to cores #0-" + (this.numCores - 1));
}

/*
 *  ======== resetCpus ========
 */
function resetCpus() 
{
    /* Reset each cpu. */
    for (var i = 0; i < this.numCores; i++) {
        myCpu = this.cpus[i];
        try {
            myCpu.session.target.halt();
            myCpu.session.target.reset();
        }
        catch (e) {
            print("ERROR: Problem reseting " + myCpu.ccsName);
            print(e);
            // java.lang.System.exit(0);
        }
    }
}

/*
 *  ======== terminateSessions ========
 */
function terminateSessions() 
{
    for (var i = 0; i < this.numCores; i++) {
	     print("Terminating session....");
         try {
           myCpu = this.cpus[i];
           myCpu.session.terminate();
            print("Terminated session: " + myCpu.ccsName);
        }
        catch (e) {
            print("ERROR: Problem terminating " + myCpu.ccsName);
            print(e);
            java.lang.System.exit(0);
        }
    }
	this.cpus=[];
}

/*
 *  ======== logPrint ========
 *  Print debugging messages...
 */
function logPrint(str)
{
    var Main = xdc.useModule('runscript.Main');
    
    if (Main.enableTracing) {
        var curdate = new Date()
        dstring = curdate.toGMTString()

        print(dstring + ": " + str);
    }
}
