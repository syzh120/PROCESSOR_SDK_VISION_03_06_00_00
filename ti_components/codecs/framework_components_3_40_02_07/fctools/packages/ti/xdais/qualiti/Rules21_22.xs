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
        description:       "All algorithms must characterize their static data & program memory requirements",
        isPerformanceTest: true,
    };
}

// test execution function
function run( testId, algoParams, testSettings, testDetailLevel, cbPrintLog )
{
    cbPrintLog( "Running test '" + testId + "'\n" );

    cbPrintLog( "Using sectti on ofd output to find static data & program memory requirements...\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/";
    var cgxmlDir   = testSettings.cgxmlDir + "/";

    var cmd = System.getCommandPath( cgtoolsDir + "bin/ofd6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -x --xml_indent=0 --obj_display=none,sections,header " + libPath;
    cmd += " | " + System.getCommandPath( cgxmlDir + "bin/sectti" );

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

    /*
      sample output:
Reading from stdin
====================================================================
REPORT FOR LIBRARY: qwa_qnx.l64P
====================================================================

************************************************************
REPORT FOR FILE: qwa_qnx_plink.obj
************************************************************
                          Name : Size (dec)  Size (hex)  Type
------------------------------ : ----------  ----------  ----
                .text:algAlloc :         64  0x00000040  CODE
                 .text:algInit :        800  0x00000320  CODE
                 .text:algFree :         64  0x00000040  CODE
                .text:algMoved :         32  0x00000020  CODE
                         .text :     185600  0x0002d500  CODE
                        .const :      14169  0x00003759  DATA
                       .switch :        820  0x00000334  DATA
                        .cinit :         56  0x00000038  DATA
                          .far :         48  0x00000030  UDATA

------------------------------------------------------------
Totals by section type
------------------------------------------------------------
  Uninitialized Data :         48  0x00000030
    Initialized Data :      15045  0x00003ac5
                Code :     186560  0x0002d8c0
    */

    var status = ITest.TEST_PASS;
    var statusDetails = "Performance test completed. CODE, DATA & UDATA sections characterized";

    return {
        status: status,
        statusDetails: statusDetails,
    };
}

