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

var symTypes = "\nSymbol types:\n\
  A    absolute symbol\n\
  B    bss segment symbol\n\
  D    data segment symbol\n\
  E    external symbol\n\
  S    section name symbol\n\
  T    text segment symbol\n\
  U    undefined symbol\n\n";

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
function getAttrs(testId)
{
    return {
        description: "All algorithms must implement the IALG interface."
    };
}

// test execution function
function run(testId, algoParams, testSettings, testDetailLevel, cbPrintLog)
{
    cbPrintLog("Running test '" + testId + "'\n");

    cbPrintLog("Extracting names of global BSS data symbols...\n");

    // construct the command line
    var cgtoolsDir = testSettings.cgtoolsDir + "/bin/";

    var cmd = System.getCommandPath(cgtoolsDir + "nm6x");

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -g " + libPath;

    // execute the command line
    var runResult = System.runShellCommand(cmd, cbPrintLog, testDetailLevel);

    // return if command failed
    if (runResult.status != 0) {
        return {
            status:        ITest.TEST_RUNERROR,
            statusDetails: "",
            runResult:     runResult
        };
    }

    // do the work
    var stdout = runResult.stdout;

    var MOD = algoParams.moduleName;
    var VEND = algoParams.vendor;
    var INT  = algoParams.interfaceName;
    var PREFIX = MOD + "_" + VEND + "_";
    var PREFIX1 = PREFIX + "IALG";
    var PREFIX2 = PREFIX + INT ;

    if (testDetailLevel >= 2) {
        cbPrintLog(symTypes);
    }
    cbPrintLog( "Verifying that objects '" + PREFIX1 + "' and '" + PREFIX2 + "' are defined...\n" );

    var prefix1Found = false;
    var prefix2Found = false;
    var stdoutLines = stdout.split( "\n" );
    for (var i = 0; i < stdoutLines.length; i++) {
        if (!stdoutLines[i].match(/ [BD] /)) {
            continue;
        }
        var symName = stdoutLines[i].replace( /^.*\sB\s_?/, "" ); // cut "00...0 B _" (underscore optional)
        if (symName == PREFIX1) {
            prefix1Found = true;
            cbPrintLog( "Data object '" + PREFIX1 + "' found.\n" );
        }
        else if (symName == PREFIX2) {
            prefix2Found = true;
            cbPrintLog( "Data object '" + PREFIX2 + "' found.\n" );
        }
        symName = stdoutLines[i].replace( /^.*\sD\s_?/, "" ); // cut "00...0 D _" (undescore optional)
        if (symName == PREFIX1) {
            prefix1Found = true;
            cbPrintLog( "Data object '" + PREFIX1 + "' found.\n" );
        }
        else if (symName == PREFIX2) {
            prefix2Found = true;
            cbPrintLog( "Data object '" + PREFIX2 + "' found.\n" );
        }

}

    // if failed, describe what's wrong and how to fix it
    if (!prefix1Found || !prefix2Found) {
        if (!prefix1Found) {
            cbPrintLog( "Error: data object '" + PREFIX1 + "' not found.\n" );
        }
        if (!prefix2Found) {
            cbPrintLog( "Error: data object '" + PREFIX2 + "' not found.\n" );
        }
        return {
            status:             ITest.TEST_FAIL,
            statusDetails:      "Test failed. The module does not define data " +
                                ((!prefix1Found && !prefix2Found) ? ("objects '" + PREFIX1 + "' and '" + PREFIX2) :
                                ("object '" + (!prefix1Found ? PREFIX1 : PREFIX2))) + "'."
        };
    }

    // s' all good
    return {
        status: ITest.TEST_PASS,
        statusDetails: "Test passed."
    };
}

