/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
// this section (declarations and module$meta$init) is common for all tests:
var csd = String(xdc.csd()).replace(/\\/g,"/") + '/';
var thisMod;
var thisPkg;
var thisPkgDir;
var ITest;
var System;

function module$meta$init()
{
    thisPkg     = this.$package;
    thisPkgDir  = csd;
    thisMod     = this;
    ITest       = xdc.module( thisPkg.$name + ".ITest" );
    System = xdc.module( thisPkg.$name + ".System" );
}

// reset function resets any state that needs to be reset
function reset()
{
}

// return the attributes of the test, by testId (if there are more than 1 here)
function getAttrs( testId )
{
    return {
        description:       "All algorithms must characterize their worst-case stack space memory requirements (including alignment).",
        isPerformanceTest: true,
    };
}

// test execution function
function run( testId, algoParams, testSettings, testDetailLevel, cbPrintLog )
{
    // only run this for TI compiled libraries
    if ( !(algoParams.compilerParams.isTICompiler) ) {
        cbPrintLog( "Currently, this test cannot be run on non-TI compiled libraries." );
        return {
            status:             ITest.TEST_NOTAPPLY,
            statusDetails:      "Currently, this test cannot be run on non-TI compiled libraries.  "
                                + "The test requires DWARF information that was not detected in this library.  "
                                + "You will need to calculate the worst case stack size using other means and "
                                + "report this in the data sheet.",
        };
    }

    cbPrintLog( "Running test '" + testId + "'\n" );

    cbPrintLog( "Using call_graph on ofd output to find out worst case stack...\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/";
    var cgxmlDir   = testSettings.cgxmlDir + "/";

    // fixme: not checking architecture etc. at all, everything is 6x. other rules too

    var cmd = System.getCommandPath( cgtoolsDir + "bin/ofd6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -xg --xml_indent=0 --obj_display=none,header,optheader,symbols --dwarf_display=none,dinfo  " +
           libPath;
    cmd += " | " + System.getCommandPath( cgxmlDir + "bin/call_graph" ) + " --stack_max";

    // execute the command line
    var runResult = System.runShellCommand( cmd, cbPrintLog, testDetailLevel );

    // return if command failed
    if (runResult.status != 0) {
        return {
            status:        ITest.TEST_RUNERROR,
            statusDetails: "",
            runResult:     runResult,
        }
    }

    // do the work
    var stdout = runResult.stdout;

    cbPrintLog( "Extracting worst case stack from a stdout line that ends with ': wcs = <num>'\n");

    /* sample output:
        Reading from stdin ...
        _FIR_TI_filter : wcs = 24
    */

    var wsc = -1;
    var stdoutLines = stdout.split( "\n" );
    for (var i = 0; i < stdoutLines.length; i++) {
        var line = stdoutLines[i].replace( /.* : wcs =/, "" );
        if (parseInt( line ) > 0) {
            wsc = parseInt( line );
            break;
        }
    }

    var status;
    var statusDetails;

    if (wsc > 0) {
        cbPrintLog( "Calculated worst case stack is " + wsc + " bytes.\n" );
        status = ITest.TEST_PASS;
        statusDetails = "Performance test completed. " + ((wsc > 0) ? ("Calculated Worst Case Stack is " + wsc + " bytes.") : ("Warning: the program was unable to calculate the worst case stack requirement."));
    } else {
        cbPrintLog( "Warning: Unable to extract the 'worst case stack' information.\n" );
        status = ITest.TEST_FAIL;
        statusDetails = "Performance test failed. Unable to extract the 'worst case stack' information.";
    }

    return {
        status: status,
        statusDetails: statusDetails,
    };
}

