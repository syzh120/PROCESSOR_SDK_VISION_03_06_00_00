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
var os = java.lang.System.getProperty("os.name") + "";
var isWin = (os.match(/^Windows/i) != null);

// self properties, initialized in below, used throughout
var csd = String(xdc.csd()).replace(/\\/g,"/") + '/';
var thisMod;
var thisPkg;
var thisPkgDir;

function module$meta$init()
{
    thisPkg     = this.$package;
    thisPkgDir  = csd;
    thisMod     = this;
}

function runShellCommand(
    commandStr,      // shell command
    cbPrint,         // log print callback
    detailLevel      // detail level
    )
{

    var stdout = "";
    var stderr = "";
    var stdsys = "";

    if (cbPrint == null) {
        cbPrint = print;
    }

    function printOut( text ) {
        stdout += text;
        if (detailLevel >= 2) {
            cbPrint( "  " + text );
        }
    }
    function printErr( text ) {
        stderr += text;
        cbPrint( "  " + text );
    }
    function printSys( text ) {
        stdsys += text;
        cbPrint( " " + text );
    }


    var shScriptFile;

    // create temporary file
    var shScriptFile = java.io.File.createTempFile("qualiti_runcmd_", ".sh");

    // Delete temp file when program exits.
    shScriptFile.deleteOnExit();

    // Write to temp file
    var out = new java.io.BufferedWriter(new java.io.FileWriter(shScriptFile));
    out.write( "#!/bin/sh\n" );
    out.write( commandStr.replace( /\\/g, "/" ) + "\n" );
    out.close();

    // generate the shell command to run this script
    var cmdArray = [];
    var os = java.lang.System.getProperty("os.name") + "";
    if (os.match(/^Windows/i)) {
        cmdArray[0] = environment['xdc.root'] + "\\bin\\sh.exe";
    } else {
        cmdArray[0] = "sh";
    }
    cmdArray[1] = shScriptFile.getCanonicalPath();

    // create the command array
    var cmdArray_j = java.lang.reflect.Array.newInstance(
        java.lang.String, cmdArray.length);
    for (var i = 0; i < cmdArray.length; i++) {
        cmdArray_j[i] = cmdArray[i];
    }

    // copy the environment array from the current environment
    var env   = java.lang.System.getenv();
    var keys  = env.keySet().toArray();
    var env_j = java.lang.reflect.Array.newInstance(
        java.lang.String, keys.length);
    for (var i=0; i < keys.length; i++) {
        var key = keys[i];
        env_j[i] = key + '=' + env.get(key);
    }

    if (isWin) {
        printSys( "Running command:> " + commandStr.replace( /\//g, "\\" ) + "\n");
    } else {
        printSys( "Running command:> " + commandStr + "\n");
    }
    if (detailLevel >= 2) {
        printSys( "                  (from \"" + cmdArray[1] + "\"\n" );
    }
    if (detailLevel >= 3) {
        printSys( "Environment:> " );
        for (var i = 0; i < env_j.length; i++) {
            printSys( env_j[i] + " " );
        }
        printSys( "\n" );
    }

    // create the process
    var runtime = java.lang.Runtime.getRuntime();
    try {
        var proc = runtime.exec(cmdArray_j, env_j);
    } catch( e ) {
        var msg = "Failed to run command '" + cmdArray[0] + "'; " +
                  "check if path is correct. Details: " + e;
        printSys( msg );
        return {
            status: -1,
            stdout: stdout,
            stderr: stderr,
            stdsys: stdsys,
        };
    }

    // local function to manage out and err streams of the process execing cmd
    function _copy_stream(inStream, cbPrint) {
        var thread = new java.lang.Thread(function() {
            var isr = new java.io.InputStreamReader(inStream);
            var br = new java.io.BufferedReader(isr);
            var line;
            while (line = br.readLine()) {
                line += "";
                cbPrint(line + "\n");
            }
        });
        thread.start();
        return thread;
    }

    // create threads to copy the stdout and stderr streams
    var cpyerr = _copy_stream(proc.getErrorStream(), printErr);
    var cpyout = _copy_stream(proc.getInputStream(), printOut);

    // wait for the process to complete
    var status = proc.waitFor();

    // wait for the streams to complete
    cpyerr.join();
    cpyout.join();

    // return the exit status of the process
        return {
            status: status,
            stdout: stdout,
            stderr: stderr,
            stdsys: stdsys,
        };
}

function getCommandPath( command )
{
    if (isWin) {
        command += ".exe";
        command = command.replace( /\\/g, "/" );
        command = '"' + command + '"';
    }
    return command;
}

function checkPath(path)
{
    if (isWin) {
        path = '"' + path + '"';
    }
    return (path);
}
