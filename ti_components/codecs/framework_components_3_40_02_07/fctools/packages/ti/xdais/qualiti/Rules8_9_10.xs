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

/* list of disallowed external function references from spru352 Appendix B.1 */
var disallowedFxns = [

    // heap management functions not allowed
    "malloc",
    "free",
    "realloc",
    "calloc",

    // I/O functions not allowed
    "printf",
    "open",
    "read",
    "write",
    "fopen",
    "fread",
    "fwrite",

    // misc non-reentrant functions not allowed
    "sprintf",
    "ctime",
    "time",
    "abort_msg",
    "assert",
];

/* list of allowed functions
 * taken from spru352, Appendix B.1, spru187, Table 7.7
 * and customer use cases
 */
var allowedFxns = [
    "absd",
    "absf",
    "addd",
    "addf",
    "atoi",
    "cosh",
    "cmpd",
    "cmpf",
    "cvtdf",
    "cvtfd",
    "divd",
    "divf",
    "divi",
    "divli",
    "divlli",
    "divu",
    "divul",
    "divull",
    "fixdi",
    "fixdli",
    "fixdlli",
    "fixdu",
    "fixdul",
    "fixdull",
    "fixfi",
    "fltlid",
    "fltlif",
    "fixfli",
    "fltllid",
    "fltllif",
    "fixflli",
    "fixfu",
    "fixful",
    "fixfull",
    "fltid",
    "fltif",
    "fltud",
    "fltuf",
    "fltuld",
    "fltulf",
    "fltulld",
    "fltullf",
    "ftoi",
    "itof",
    "labs",
    "llabs",
    "llshl",
    "llshr",
    "llshru",
    "log10",
    "memclr",
    "memcpy",
    "memmove",
    "memset",
    "mpyd",
    "mpyf",
    "mpyll",
    "negf",
    "negll",
    "remi",
    "remli",
    "remlli",
    "remu",
    "remul",
    "remull",
    "strchr",
    "strcpy",
    "strlen",
    "strncpy",
    "subd",
    "subf",
    "aeabi_memclr",
    "aeabi_memclr4",
    "aeabi_memcpy",
    "aeabi_memcpy4",
    "aeabi_memmove",
    "aeabi_memset",
    "aeabi_f2uiz",
    "aeabi_fmul",
    "aeabi_i2f",
    "aeabi_ui2f",
    "aeabi_idivmod",
    "aeabi_uidivmod",
    "aeabi_i2d",
    "_strasgi_64plus",
    "_c6xabi_strasgi_64plus"
];

/* list of allowed symbol prefixes */
var allowedPrefixes = [
    "ECPY_",
    "ACPY3_",
    "MEMUTILS_",
    "_IQN",
    "_TI_DW\.debug_info\."
];

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
        description:
            "(Rule 8) All external definitions must be either API identifiers or API and vendor prefixed.\n\n" +
            "(Rule 9) All undefined references must refer either to the operations specified in Appendix B (a subset of C runtime support library functions and a subset of the DSP/BIOS HWI API functions), or TI's DSPLIB or IMGLIB functions or other XDAIS-compliant modules.\n\n" +
            "(Rule 10) All modules must follow the eXpressDSP naming conventions for those external declarations disclosed to the client." +
            ""
    };
}

// test execution function
function run(testId, algoParams, testSettings, testDetailLevel, cbPrintLog)
{
    cbPrintLog("Running test '" + testId + "'\n");
    cbPrintLog("Extracting names of global symbols defined by the " +
            "algorithm...\n");

    var cgtoolsDir = testSettings.cgtoolsDir + "/bin/";

    var cmd = System.getCommandPath( cgtoolsDir + "nm6x" );

    /* always call checkPath when passing a path to a command */
    var libPath =
            System.checkPath(algoParams.baseDir + "/" + algoParams.library);

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

    // define prefix
    var MOD = algoParams.moduleName;
    var VEND = algoParams.vendor;
    var PREFIX = MOD + "_" + VEND + "_";
    var EXT_PREFIX = "<MODULE>_" + VEND + "_";

    if (testDetailLevel >= 2) {
        cbPrintLog(symTypes);
    }
    cbPrintLog( "Verifying that all global symbols are named XXX_" + VEND +
            "_xxx ...\n" +
            "and that no blacklisted external references are made\n");

    /* sample output:
      00000000 T _FIR_TI_exit
      00000000 T _FIR_TI_init
      00000064 T _FIR_TI_filter
      00000000 B _FIR_TI_myTables
      00000000 T _dummy1
      00000000 U _memcpy
      00000000 T _FIR_TI_activate
      00000000 T _FIR_TI_alloc
      00000000 T _FIR_TI_control
      00000000 T _FIR_TI_deactivate
      00000000 T _FIR_TI_free
      00000000 T _FIR_TI_initObj
      00000000 T _FIR_TI_moved
      00000000 T _FIR_TI_numAlloc
      00000000 U _IFIR_PARAMS
      00000000 U _memcpy
      00000000 B _FIR_TI_IALG
      00000000 B _FIR_TI_IFIR
      00000000 U _FIR_TI_activate
      00000000 U _FIR_TI_alloc
      00000000 U _FIR_TI_control
      00000000 U _FIR_TI_deactivate
      00000000 U _FIR_TI_filter
      00000000 U _FIR_TI_free
      00000000 U _FIR_TI_initObj
      00000000 U _FIR_TI_moved
      00000000 U _FIR_TI_numAlloc
    */

    // is this a package? todo: this should be a param passed on by the caller
    var isPackage = false;
    if (java.io.File( algoParams.baseDir + "/package.xdc" ).exists()) {
        isPackage = true;
    }

    // check all function names
    var badList = [];
    var foundDisallowedFxns = [];
    var badExternList = [];

    var stdoutLines = stdout.split( "\n" );
    for (var i = 0; i < stdoutLines.length; i++) {
        if (!stdoutLines[i].match(/ [TBCUD] /)) {
            continue;
        }
        var symType = stdoutLines[i].substr(9, 1);  // "T", "B", "C", "U" or "D"
        var symName = stdoutLines[i].substr(11);     // "_FIR_TI_free"
        if (symName == "") {
            continue;
        }

        if (symName.charAt(0) == "_") {
            symName = symName.substr(1); // eat any leading underscores
        }

        if ((symName == "I" + MOD + "_PARAMS") && (symType != "U")) {
            cbPrintLog("Found symbol '" +
                    "I" + MOD + "_PARAMS', that's okay.\n");
            continue;
        }

        var foundPre = false;
        for each (var j = 0; j < allowedPrefixes.length; j++) {
            var regex = new RegExp( "^" + allowedPrefixes[j]);
            if (symName.match(regex) != null) {
                cbPrintLog("Found symbol '" + symName + "', that's okay.\n");
                foundPre = true;
                break;
            }
        }
        if (foundPre) {
            continue;
        }

        if ((symName.match(/.*__dummy__$/)) && (symType == "B") || (symType == "C")) {
            cbPrintLog("Found bad symbol '...__dummy__' but ignoring it " +
                    "because the algorithm is in an XDC package.\n");
            continue;
        }

        // this is what we're looking for in a good symbol
        var r = new RegExp( "^[A-Z0-9]+_" + VEND + "_" );
        if (symName.match( r ) == null) {
            // maybe not a good name. first check if it's an allowed symbol; if
            // not, either it's defined symbol, in which case it's
            // definitely not a good name, or it's an undefined reference; if
            // the latter we'll save it and check later against the black list
            var goodReference = false;
            if (symType != "U") {
                for (var j = 0; j < allowedFxns.length && symType == "T"; j++) {
                    if (isAllowedFxn(allowedFxns[j], symName)) {
                        goodReference = true;
                        break;
                    }
                }
                if (goodReference == false) {
                    badList[badList.length] = symName + (symType == "T" ? "()" : "");
                    cbPrintLog("Error: here-defined global name '" +
                               badList[badList.length - 1] +
                               "' does not comply.\n");
                }
            }
            else {
                if (isDisallowedFxn(symName)) {
                    foundDisallowedFxns.push(symName);
                }
                else {
                    /*
                     * If it's not on the accepted list, add it to the
                     * badExternList.
                     */
                    for (var j = 0; j < allowedFxns.length; j++) {
                        if (isAllowedFxn(allowedFxns[j], symName)) {
                            goodReference = true;
                            break;
                        }
                    }
                    if (goodReference == false) {
                        badExternList.push(symName);
                    }
                }
            }
        }
    }

    var statusDetails = "";
    var status = ITest.TEST_PASS;

    if (badList.length > 0) {
        if (badList.length == 1) {
            var errStr = "Global " + (badList[0].match(/\(/) ? "function" : "object") +
                         " '" + badList[0] + "' is non-compliant as it does not have the \"" +
                         PREFIX + "\" (i.e. \"module_vendor_\") prefix.\n";

            statusDetails += "Problem: " + errStr + "\n";
            cbPrintLog("Error: " + errStr);
        } else {
            statusDetails += "Problem: Not all global symbols defined by " +
                    "the module have the \"" + PREFIX +
                    "\" prefix (i.e. module_vendor_).\n\n" +
                    "The following is the list of offending symbols:\n";
            for (var i = 0; i < badList.length; i++) {
                statusDetails += badList[i] + "\n";

                cbPrintLog("Error: Global " +
                        (badList[i].match(/\(/) ? "function" : "object") +
                        " '" + badList[i] + "' is non-compliant as it does " +
                        "not have the \"" + PREFIX +
                        "\" (i.e. \"module_vendor_\") prefix.\n");

            }
            statusDetails += "\n";
        }
        status = ITest.TEST_FAIL;
    }

    if (badExternList.length > 0) {
        if (badExternList.length == 1) {
            var errStr = "External " +
                    (badExternList[0].match(/\(/) ? "function" : "object") +
                    " '" + badExternList[0] + "' is non-compliant as it "  +
                    "does not have the \"" + EXT_PREFIX +
                    "\" (i.e. \"module_vendor_\") prefix.\n";

            statusDetails += "Problem: " + errStr + "\n";
            cbPrintLog("Error: " + errStr);
        }
        else {
            statusDetails += "Problem: Not all external symbols declared " +
                    "by the module have the \"" + EXT_PREFIX +
                    "\" prefix (i.e. module_vendor_).\n\n" +
                    "The following is the list of offending symbols:\n";
            for (var i = 0; i < badExternList.length; i++) {
                statusDetails += badExternList[i] + "\n";

                cbPrintLog("Error: External " +
                        (badExternList[i].match(/\(/) ? "function" : "object") +
                        " '" + badExternList[i] + "' is non-compliant as " +
                        "it does not have the \"" + EXT_PREFIX +
                        "\" (i.e. \"module_vendor_\") prefix.\n");
            }
            statusDetails += "\n";
        }
        status = ITest.TEST_FAIL;
    }

    // flag disallowed external references
    for (var j = 0; j < foundDisallowedFxns.length; j++) {
            cbPrintLog("Error: external reference '" + foundDisallowedFxns[j] +
                    "' is not allowed.\n");
            if (j == 0) {
                statusDetails += "Problem: The algorithm makes the " +
                        "following disallowed external references:\n";
            }
            statusDetails += "  - " + foundDisallowedFxns[j] + "\n";
    }

    if (foundDisallowedFxns.length > 0) {
        statusDetails += "\nPlease check that these references are resolved " +
                "via allowed functions in RTS, IMG, DSP, ACPYx libraries.\n\n" +
                "For your reference, the following external references are " +
                "not allowed:\n";
        for (var j = 0; j < disallowedFxns.length; j++) {
            statusDetails += "  - " + disallowedFxns[j] + "\n";
        }
        status = ITest.TEST_FAIL;
    }

    if (status == ITest.TEST_PASS) {
        return {
            status: ITest.TEST_PASS,
            statusDetails: "Test passed."
        };
    }
    else {
        return {
            status: ITest.TEST_FAIL,
            statusDetails: "Test failed. " + statusDetails
        };
    }
}

function isAllowedFxn(allowedName, symName)
{
    return (symName == allowedName || (symName == '_' + allowedName));
}

function isDisallowedFxn(symName)
{
    for (var i = 0; i < disallowedFxns.length; i++) {
        if (symName == disallowedFxns[i] || (symName == '_' + disallowedFxns[i])) {
            return (true);
        }
    }
    return (false);
}
