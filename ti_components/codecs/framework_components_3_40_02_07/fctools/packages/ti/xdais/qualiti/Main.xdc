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
metaonly module Main inherits xdc.tools.ICmd {

    function createPartControl(parent);
    /*!
     * usage help message
     */
    override config String usage[] = [
        '[-h] [-u file] [-o outDir] [-ol] [-e] [-t toolsIniFile] ',
        '[-d 0|1|2] [-f] [-v|q] [-g] algproject',
        '  -u: run user script',
        '(following options in command-line mode only)',
        '  -o: output HTML reports to outDir',
        '  -l: output HTML reports in the algorithm library dir',
        '       (default is in the algorithm base dir)',
        '  -e: embed time stamp in the report filename',
        '  -t: specify alternative Tools.ini file with toolpaths',
        '  -d: report detail level',
        '  -f: make report diff friendly',
        '  -v: verbose',
        '  -q: quiet',
        '  algproject: a .qti file with algorithm description',
    ];

instance:
    /*!
     * help
     */
    @CommandOption("h")
    config Bool help = false;
    
    /*!
     * User script to run before the main script
     */
    @CommandOption("u")
    config String userIniFile = null;
    
    /*!
     * HTML report output in alg. lib directory and not base directory
     */
    @CommandOption("l")
    config Bool outputInLibDir = false;

    /*!
     * Make report diff friendly
     */
    @CommandOption("f")
    config Bool diffFriendly = false;

    /*!
     * HTML report output in a specified directory
     */
    @CommandOption("o")
    config String outputDir = null;

    /*!
     * Embed time stamp in HTML report filename
     */
    @CommandOption("e")
    config Bool embedTimeStampInReportName = false;

    /*!
     * Test detail level
     */
    @CommandOption("d")
    config Int testDetailLevel = 2;

    /*!
     * Alternative Tools.ini file (full path)
     */
    @CommandOption("t")
    config String toolsIniFile = null;

    /*!
     * Verbose
     */
    @CommandOption("v")
    config Bool verbose = false;

    /*!
     * Quiet
     */
    @CommandOption("q")
    config Bool quiet = false;

    /*!
     * Gui
     */
    @CommandOption("g")
    config Bool gui = false;

}
