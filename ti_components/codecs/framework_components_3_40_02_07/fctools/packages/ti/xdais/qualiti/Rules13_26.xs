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

// result of the command execution, remembered here for efficiency
var runResult;
var runResultTestId;

// reset function resets any state that needs to be reset
function reset()
{
    runResult = null;
}

// return the attributes of the test, by testId (if there are more than 1 here)
function getAttrs( testId )
{
    switch (testId) {
        case "XDAIS Rule 13+":
            var d =
                "Each of the IALG methods implemented by an algorithm must be independently relocatable.\n\n" +
                "Additional rule: there should be no non-standard linker sections. " +
                "(Standard linker sections are: ";
                for (var j = 0; j < thisMod.standardSections.length; j++) {
                    d += '"' + thisMod.standardSections[j] + '"' + (j < thisMod.standardSections.length - 1 ? ", " : ".");
                    }
                d += ")";
            return {
                description: d,
            };
        case "XDAIS Rule 26":
            return {
                description: "All C6x algorithms must access all static and global data as far data.",
            };
        default:
            throw "Internal error: wrong test id '" + testId + "'";
   }
}

// test execution function
function run( testId, algoParams, testSettings, testDetailLevel, cbPrintLog )
{
    switch (testId) {
        case "XDAIS Rule 13+":
            return runRule13( testId, algoParams, testSettings, testDetailLevel, cbPrintLog );
        case "XDAIS Rule 26":
            return runRule26( testId, algoParams, testSettings, testDetailLevel, cbPrintLog );
        default:
            throw "Internal error: wrong test id '" + testId + "'";
   }
}

// test for Rule 13
function runRule13( testId, algoParams, testSettings, testDetailLevel, cbPrintLog )
{
    // only run this for TI compiled libraries
    if ( !(algoParams.compilerParams.isTICompiler) ) {
        cbPrintLog( "Currently, this test cannot be run on non-TI compiled libraries.\n");
        return {
            status:             ITest.TEST_NOTAPPLY,
            statusDetails:      "Currently, this test cannot be run on non-TI compiled libraries.  "
                                + "This rule is not relevant for ARM libraries since sections should "
                                + "be placed properly.\n",
        };
    }
    cbPrintLog( "Running test '" + testId + "'\n" );

    cbPrintLog( "Extracting names of all sections in which all algorithms' symbols are...\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/";
    var cgxmlDir   = testSettings.cgxmlDir + "/";

    var cmd = System.getCommandPath( cgtoolsDir + "bin/ofd6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -x --xml_indent=0 --obj_display=none,sections,header " + libPath;
    cmd += " | " + System.getCommandPath( cgxmlDir + "bin/sectti" ) + " --csv";

    // execute the command line if it's the first time
    if (runResult == null) {
        runResult = System.runShellCommand( cmd, cbPrintLog, testDetailLevel );
        runResultTestId = testId;
    } else {
        cbPrintLog( "[Using output generated by the command from test '" + runResultTestId + '"]:\n' );
        // pretend you're running this
        cbPrintLog( runResult.stdsys );
        cbPrintLog( runResult.stderr );
        if (testDetailLevel >= 2) {
            cbPrintLog( runResult.stdout );
        }
        cbPrintLog( "[end of reused output]\n\n" );
    }

    // return if command had failed
    if (runResult.status != 0) {
        return {
            status:        ITest.TEST_RUNERROR,
            statusDetails: "",
            runResult:     runResult,
        }
    }

    // do the work
    var stdout = runResult.stdout;

    cbPrintLog( "Verifying that IALG functions are in separate sections,\n" +
                "i.e. that there exist sections that match regexp /\\.text:.*[aA]lloc.*/,\n" +
                "and also that there are no non-standard sections.\n" );

    /* sample output:
      Reading from stdin
      Library,Filename,Section,Type,Size
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti.o64,.text:init,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti.o64,.text:exit,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.text,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.bss,UDATA,4
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.cinit,DATA,24
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.tables,UDATA,16
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.text:filter,CODE,224
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algNumAlloc,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algMoved,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algInit,CODE,96
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algAlloc,CODE,96
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algFree,CODE,96
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algDeactivate,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algControl,CODE,64
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algActivate,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_vt.o64,.cinit,DATA,48
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_vt.o64,.far,UDATA,40
    */

    var badList = "";
    var badCount = 0;
    var textAlgSectionsFound = false;  // change this to "true" if you want to ignore actual Rule 13, i.e. searching for .text:algInit etc. sections
    var stdoutLines = stdout.split( "\n" );
    for (var i = 0; i < stdoutLines.length; i++) {
        var lineArray = stdoutLines[i].split(",");
        // ignore the non-data lines. Todo: could use --no_header so there won't be any Size line
        if (lineArray.length != 5 || lineArray[4] == "Size") {
            continue;
        }
        var section = lineArray[2];
        // check if there is at least one .text:something[iI]nitSomething function
        if ( section.match( /^\.text:.*[aA]lloc.*/ ) != null) {
            textAlgSectionsFound = true;
        }
        if (section.match( ":" ) != null) {
            section = section.split( ":" )[0];
        }
        var isStandardSection = false;
        for (var j = 0; j < thisMod.standardSections.length; j++) {
            if (section == thisMod.standardSections[j]) {
                isStandardSection = true;
                break;
            }
        }
        if (!isStandardSection) {
            badList += (badList == "" ? "" : ", ") + '"' + section + '" (file "' + lineArray[1] + '")';
            badCount++;
            cbPrintLog( "Error: symbols in file '" + lineArray[1] + "' are placed in a non-stndard section '" + section + "'.\n" );
        }
    }

    var statusDetails = "";

    if (!textAlgSectionsFound) {
        cbPrintLog( "Error: did not find .text:algAlloc et al functions (or .text:MOD_VEND_algAlloc)\n" );
        statusDetails += "Test failed. There must be a separate section for each IALG function, e.g. .text:algInit. " +
                        "Use the #pragma CODE_SECTION for each of your IALG fxns " +
                        "or build with functions in subsections (-mo on c6x) to fix this problem.";
    }
    if (badCount > 0) {
        statusDetails += (((statusDetails == "") ? "Test failed. T" : "\n\nAlso, t") + "here ") +
                         (((badCount > 1) ? ("are non-standard linker sections: " + badList + "\n\n") : ("is a non-standard linker section: " + badList + ".\n\n"))) +
                         "Non-standard linker-sections are dangerous because the linker can place them " +
                         "in the wrong type of memory. To fix this problem, rename your non-standard section " +
                         "to be a subection of a standard section, for example instead of non-standard " +
                         "\".myTable\" use \".const:myTable\".\n\n" +
                         "This is the list of standard linker sections: ";
        for (var j = 0; j < thisMod.standardSections.length; j++) {
            statusDetails += '"' + thisMod.standardSections[j] + '"' + (j < thisMod.standardSections.length - 1 ? ", " : ".");
        }
    }

    if (statusDetails != "") {
        return {
            status:             ITest.TEST_FAIL,
            statusDetails:      statusDetails,
        };
    }

    return {
        status: ITest.TEST_PASS,
        statusDetails: "Test passed.",
    };
}



// test for Rule 26
function runRule26( testId, algoParams, testSettings, testDetailLevel, cbPrintLog )
{
    // only run this for c64x architecture
    if ( !(algoParams.compilerParams.isC6x) ) {
        cbPrintLog( "This test does not apply since this is not a C6x architecture.\n" );
        return {
            status:             ITest.TEST_NOTAPPLY,
            statusDetails:      "This test does not apply since this is not a C6x architecture.\n",
        };
    }


    cbPrintLog( "Running test '" + testId + "'\n" );

    cbPrintLog( "Extracting names of all used sections to see if there is a '.bss' in there.\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/";
    var cgxmlDir   = testSettings.cgxmlDir + "/";

    var cmd = System.getCommandPath( cgtoolsDir + "bin/ofd6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -x --xml_indent=0 --obj_display=none,sections,header " + libPath;
    cmd += " | " + System.getCommandPath( cgxmlDir + "bin/sectti" ) + " --csv";

    // execute the command line if it's the first time
    if (runResult == null) {
        runResult = System.runShellCommand( cmd, cbPrintLog, testDetailLevel );
        runResultTestId = testId;
    } else {
        cbPrintLog( "[Using output generated by the command from test '" + runResultTestId + '"]:\n' );
        // pretend you're running this
        cbPrintLog( runResult.stdsys );
        cbPrintLog( runResult.stderr );
        if (testDetailLevel >= 2) {
            cbPrintLog( runResult.stdout );
        }
        cbPrintLog( "[end of reused output]\n\n" );
    }

    // return if command had failed
    if (runResult.status != 0) {
        return {
            status:        ITest.TEST_RUNERROR,
            statusDetails: "",
            runResult:     runResult,
        }
    }

    // do the work
    var stdout = runResult.stdout;

    cbPrintLog( "Verifying that there are no '.bss' sections in the output\n" );

    /* sample output:
      Reading from stdin
      Library,Filename,Section,Type,Size
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti.o64,.text:init,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti.o64,.text:exit,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.text,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.bss,UDATA,4
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.cinit,DATA,24
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.tables,UDATA,16
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_filter.o64,.text:filter,CODE,224
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algNumAlloc,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algMoved,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algInit,CODE,96
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algAlloc,CODE,96
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algFree,CODE,96
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algDeactivate,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algControl,CODE,64
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_ialg.o64,.text:algActivate,CODE,32
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_vt.o64,.cinit,DATA,48
      C:/work/qti/alan_algos/download/sample_bad_alg/fir_ti/./lib/fir_ti.l64P,fir_ti_vt.o64,.far,UDATA,40
    */

    var bssCount = 0;
    var bssFiles  = "";
    var stdoutLines = stdout.split( "\n" );
    for (var i = 0; i < stdoutLines.length; i++) {
        var lineArray = stdoutLines[i].split(",");
        if (lineArray.length != 5 || lineArray[4] == "Size") {
            continue;
        }
        var section = lineArray[2];
        if (section == ".bss" || section.match( /^\.bss:/ )) {
            bssCount++;;
            cbPrintLog( "Error: found a '.bss' section in object file '" +lineArray[1] + "' (" + lineArray[3] + "," + lineArray[4] + ").\n" );
            bssFiles += (bssFiles == "" ? "" : ", ") + "'" + lineArray[1] + "'";
        }
    }

    if (bssCount > 0) {
        return {
            status:             ITest.TEST_FAIL,
            statusDetails:      "Test failed. Found a '.bss' section in object file" + (bssCount > 1 ? "s" : "") + " " + bssFiles + ". " +
                                "It is a nightmare for ROMing and also has some total-application-size limits since .bss must be < 32Kb.\n\n" +
                                "Fix this problem by finding the offending data and making it far or const, or " +
                                "rebuild the library with --mem_model:data=far."
        };
    }

    return {
        status: ITest.TEST_PASS,
        statusDetails: "Test passed.",
    };
}

