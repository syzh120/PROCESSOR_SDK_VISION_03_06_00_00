/* --COPYRIGHT--,BSD
 * Copyright (c) $(CPYYEAR), Texas Instruments Incorporated
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
 * --/COPYRIGHT--*/
/* 
 *  ======== settings.xs ========
 *  This is essentially a configuration file which defines some paths used
 *  by the scripts. These paths are unique per test framework; in other
 *  words, these only need to be set once per team (BIOS testing, FC testing,
 *  BIOS examples, etc.).
 *
 *! Revision History
 *! ================
 *! 23-Feb-2009     skp     tempLogDir changed to c:\temp
 *! 08-May-2009     skp     testPkgNames removed
 *! 30-Sep-2008     jb      updated for dss regressions.
 *! 14-Dec-2006     cmcc    Added testPkgNames and anyPkg flag.
 *! 13-Dec-2006     cmcc    Added comments and revision history.
 *
 */
 
/*
 *  ======== timeout ========
 */
var timeout = 20000;

/* 
 *  ======== searchPath ========
 *  The *default* path to begin searching for package.bld.xml files. The search
 *  looks for directories named "tests" and then grabs the
 *     /tests/package/package.bld.xml
 *  file. Therefore, all test packages need to be named "tests" for the scripts
 *  to find them, and the search should begin at least one level above any 
 *  'tests' packages.
 *
 *  You can also specify a different searchPath on the command line.
 */
var searchPath = "../../ti";

/*
 *  ======== testAllPkgs ========
 *  If this flag is set, then the scripts will ignore the testPkgNames array
 *  and include any packages found under searchPath as test packages. 
 */
var testAllPkgs = false; 
 
/* 
 *  ======== pkgRoot ========
 *  The scripts need to know the package root so that package names (such as
 *  ti.sysbios.knl.tests) can be turned into paths 
 *  (avala\src\ti\sysbios\knl\tests).
 */
var pkgRoot = "../../";

/* 
 *  ======== resultsDir ========
 *  The directory to place the xml results files in. 
 */
var resultsDir = "../../results_mp/";

/*
 *  ======== tempLogDir ========
 *  Directory to place the temporary log files in. The scripts will delete
 *  these log files as it goes, but errors that terminate the scripts
 *  may cause a log file to stick around.
 *  Include a backslash at the end of the path (e.g., "C:\\").
 */
var tempLogDir = "c:/temp/";

/*
 *  ======== enableFailOutput ========
 *  Enable or disable the saving of output from a failed test. Disable this
 *  in order to run the scripts on a read-only tree. 
 */
var enableFailOutput = true;

/* 
 *  ======== addImportsXML ========
 *  BIOS-only; set to false for non-BIOS testing. 
 *
 *  The top of the avala tree contains a file named imports.xml which lists
 *  all of the packages that were imported to build the tree. This lets us 
 *  know what version of xdc, tools, etc. was used to build the tree. 
 */
var addImportsXML = true;

/*
 *  ======== separators ========
 *  Symbols to take as separators when comparing golden outputs with variable
 *  tokens such as %d.
 */
var separators = " :,.;'\"|/\\`{}[]%";

/*
 *  ======== enableTracing ========
 *  Enable or disable script logging
 */
var enableTracing = false;
