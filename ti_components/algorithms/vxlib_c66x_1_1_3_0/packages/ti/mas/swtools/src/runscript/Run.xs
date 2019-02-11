/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== Run.xs ========
 */ 

/* Don't load ti.dss when building the tree, it won't be on the path */
if (xdc.om.$name === undefined) {
    xdc.loadPackage("ti.dss");
}

/*  
 *  ======== settings.xs ======== 
 *  Configuration file that specifies paths, such as the default search path,
 *  the package root, and the results directory.
 */
var script;
var logFile = [];

/*
 *  ======== runTestList ========
 *  This function executes the provided list of tests and compares the test
 *  ouput to the provided golden output to determine if the platform has passed
 *  or failed the tests.
 */
function runTest(fileName, numCores,refFile)
{
    var result="pass";
	Main.logPrint("Running " + fileName + " on " + numCores + " cores.");

    /* Reset all the cores before running the test */
    Main.resetCpus();

    var testSessions = loadTest(fileName, numCores);

    Main.logPrint("Running all cores Asynchronously " + Main.settings.timeout);
	for each (var session in testSessions) {
        session.target.runAsynch();
    }    
    Main.logPrint("Waiting for apps to halt ");
    
    for (var i in testSessions) {
        var session = testSessions[i];
        if (!session.target.isHalted()) {
            try {
                Main.logPrint("Waiting for CORE" + i + " to halt");
                session.target.waitForHalt();
            }
            catch (e) {
                print("Session " + session.getName() + " timed out after " + 
                        Main.settings.timeout + "ms.");
			    result="fail"; 
                break;
            }
        }
    }
    for (var i in testSessions) {
        /* Close the log file */
        session.endCIOLogging();
    }
    /* Done- no errors occurred */
    result=printOutput(numCores,result,refFile);

	return result;
}

/* =============================== *
 *        HELPER FUNCTIONS         *
 * =============================== */

/*
 *  ======== loadTest ========
 *  Loads a test onto a device
 */
function loadTest(fileName, numCores) 
{
    var Main = xdc.useModule('runscript.Main');

    var testSessions = [];

    /* For every application in the test */
    for (var i = 0; i < numCores ;i++) {
        var session = Main.getSession(i);
		session.options.setBoolean("AutoRunToLabelOnRestart", false);

        testSessions.push(session);
        /* Write the output to a temporary log file. */
        logFile[i] = Main.settings.tempLogDir + "output_" + i + ".txt";
		//logFile[i] = fileName + "output_" + i + ".txt";
        
        try {
            session.beginCIOLogging(logFile[i]);
        }
        catch(e) {
            /* 
             * If log directory cannot be written to, no point even performing
             * regressions
             */
             
            print(e);
            var logDir = Main.settings.tempLogDir; 
            print("ERROR: Log directory '" + logDir 
                + "' doesn't exist or cannot be written to. Terminating" + e);
            Main.terminateSessions();
            java.lang.System.exit(0);   
        }

        /* 
         *  Load the .out file.  If argsToMain has been specified, load the 
         *  program with arguments
         */
       
         if (!getFile(fileName).exists()) {
            throw(".out file (" + fileName + " ) not found");
         }
        
         try {
		  
            session.memory.loadProgram(fileName); 
			
         }
         catch(e) {
            /* Re-throw the error */
            throw("Load " + fileName + "on core " + i + " failed because of error: " + e);
         }
       
    }

    return (testSessions);
}

/*
 *  ======== printOutput ========
 */
function printOutput(numCores,result,refFile)
{
    var Main = xdc.useModule('runscript.Main');
    
    for (var i = 0; i < numCores; i++) {
        /* Check whether log file exists (if script is working, it should) */
        var outputFile = getFile(logFile[i]);
        if (!outputFile.exists()) {
            throw("Log file (" + logFile[i] + ")not found");
        }
		/* Compare the output with the reference output */
		try {
            var fis1 = new java.io.FileInputStream(outputFile);
            var file1 = new java.io.BufferedReader(new java.io.InputStreamReader(fis1));        
        }
        catch (e) {
            //TODO
            print(e);
			result="fail";
            continue;
        }
		
		if(refFile != "")
		{
		  print("Comparing the output with expected result file \("+refFile+"\)....");
		  if(compareResults(file1,refFile) > 0)
		  {
		    result="fail";
			print("FAIL: Output doesn't match with expected result ....");
		  }
		  else
		    print("PASS: Output completely matched with expected result ....");
		}
        
        outLine = file1.readLine();
        if (outLine != null && outLine.indexOf("A_invalidProcessor") != -1) {
            continue;
        }
        else {
            print("[CORE" + i + "]");
            if (outLine != null) {
                print("    " + outLine);
				if(outLine.toString().match("ERROR") || outLine.toString().toUpperCase().match("FAIL") )
				{
				 result="fail";
				}
            }
            
            while ((outLine = file1.readLine()) != null) {
                print("    " + outLine);
				if(outLine.toString().match("ERROR") || outLine.toString().toUpperCase().match("FAIL"))
				{
				 result="fail";
				}
            }
        }
    }
	return result;
}

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
 *  ======== loadProgram ========
 *  Load a program (app if MP, test if SP) optionally with arguments
 *  onto the specified session.
 */
function loadProgram(session, path, args) 
{    
    if (!getFile(path).exists()) {
        throw(".out file not found");
    }
     
    try {
        if (args != null && args.length != 0) {
            session.memory.loadProgram(path, args); 
        }
        else {
            session.memory.loadProgram(path); 
        }
    }
    catch (e) {
        print(e);
        throw("Unknown error loading .out");
    }
}

/*
 *  ========
 */
function compareResults(file1,file2)
{
var fileModule = xdc.module('xdc.services.io.File');
var compareFile1;
/*try{
   compareFile1 = fileModule.open(file1, "r");
 } catch (ex)
 {
   print(file1 + " cannot be read");
 }*/
 
var compareFile2;
try{
   compareFile2 = fileModule.open(file2, "r");
 } catch (ex)
 {
   print(file2 + " cannot be written to. Please check Writing Permissions.");
 }
 
 var readLine1;
 var readLine2;
 var match=0;
 var total=0;
 var nomatch=0;
 while((readLine2=compareFile2.readLine()) != null)
 {
   readLine1=file1.readLine();
   total+=1;
   if(readLine1 != readLine2)
   {
      print("Expected: "+ readLine2);
	  print("Actual: "+ readLine1);
	  
      nomatch+=1;
   } 
   else
   {
      match+=1;
   }
 }
 return nomatch;
}

/*
 *  @(#) regression.mp; 1,0,0,24; 11-19-2010 17:08:21; /db/vtree/library/trees/regresstest/regresstest.git/src/ regresstest-a45
 */

