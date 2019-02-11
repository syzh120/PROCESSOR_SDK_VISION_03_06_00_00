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
function getAttrs(testId)
{
    return {
        description: "All C6x algorithms must be supplied in little-endian format.",
    };
}

// test execution function
function run(testId, algoParams, testSettings, testDetailLevel, cbPrintLog)
{
    if ( !(algoParams.compilerParams.isC6x) ) {
        cbPrintLog( "This test does not apply since this is not a C6x architecture.\n" );
        return {
            status:             ITest.TEST_NOTAPPLY,
            statusDetails:      "This test does not apply since this is not a C6x architecture.\n",
        };
    }

    cbPrintLog("Running test '" + testId + "'\n");

    cbPrintLog("Using ofd output to parse for endianness attribute...\n");

    var cgtoolsDir = testSettings.cgtoolsDir + "/";

    // fixme: not checking architecture etc. at all, everything is 6x. other rules too

     var cmd = System.getCommandPath( cgtoolsDir + "bin/ofd6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -x --xml_indent=0 --obj_display=none,header " + libPath
    if (algoParams.compilerParams.libFormat == "ELF") {
        var exp = new RegExp('.*ELFDATA2LSB.*');
        var searchStr = '<ei_data>';
    }
    else {  // assume this is COFF
        var exp = new RegExp('.*little.*');
        var searchStr = '<endian>';
    }

    // execute the command line
    var runResult = System.runShellCommand(cmd, cbPrintLog, testDetailLevel);

    // return if command failed
    if (runResult.status != 0) {
        return {
            status:        ITest.TEST_RUNERROR,
            statusDetails: "Little-endian format may not be possible on some non-C6x architectures.",
            runResult:     runResult,
        }
    }

    /* sample output for COFF:
<endian>little</endian>
       sample output for ELF:
<ei_data>>ELFDATA2LSB</ei_data>
    */

    var found = false;
    var stdoutLines = runResult.stdout.split('\n');
    for (var i = 0; i < stdoutLines.length; i++) {
        if (stdoutLines[i].match(searchStr)) {
            if (stdoutLines[i].match(exp)) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        // s' all good
        return {
            status: ITest.TEST_PASS,
            statusDetails: "Test passed.",
        }
    } else {
        return {
            status:             ITest.TEST_FAIL,
            statusDetails:      "Test failed. This library is not supplied in little-endian format.",
        }
    }

}

