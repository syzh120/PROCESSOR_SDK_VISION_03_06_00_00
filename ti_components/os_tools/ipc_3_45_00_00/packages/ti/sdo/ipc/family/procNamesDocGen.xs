/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 */
/*
 *  ======== delegateDocGen.xs ========
 *
 */

outFileName = "doc-files/procNames.html";

var blacklist = [
    'TMS320CTCI6497',
    'TMS320CTCI6498',
    'TMS320DM8168',
    'TMS320DM8148',
    'TMS320CDM740',
    'Arctic',
    'Sonata',
    'T16v200',
];

/*
 *  ======== getFamilyIndex ========
 *  Returns a list of families corresponding to each target
 */
function getProcNames()
{
    var settings = xdc.loadCapsule("Settings.xs");

    return (settings.procNames);
}

/*
 * ======== getHTML ========
 */
function getHTML(procNames)
{
    var html = "";

    html += getFileContents("doc-files/procNamesHead.inc");

    procNamesArr = [];
    for (var deviceName in procNames) {
        procNamesArr.push(deviceName);
    }
    procNamesArr.sort();
    for (var i = 0; i < procNamesArr.length; i++) {
        deviceName = procNamesArr[i];
        if (blacklist.indexOf(deviceName) != -1) {
            /* Device is blacklisted. Skip it */
            continue;
        }
        html += "<TR><TD>" + deviceName + "</TD><TD>";
        for each (var procName in procNames[deviceName]) {
            html += procName + " ";
        }
        html += "</TD></TR>\n";
    }

    html += "</TABLE>\n";

    var d = new Date();
    html += "<DIV class=\"xdocDate\">generated on "
               + d.toUTCString() + "</DIV>\n";

    html += "</BODY></HTML>\n";

    return (html);
}

/*
 *  ======== writeFile ========
 *  Given a string and a filename, writeFile() writes the string to a new file
 *  located at 'out'
 */
function writeFile(filename, out)
{
    try {
        var outputFile = java.io.File(filename);
        if (outputFile.exists()) {
            outputFile["delete"]();
        }
        var fos = java.io.FileWriter(outputFile);
        fos.write(out);
        fos.close();
    }
    catch (e) {
        throw("Error writing file '" + filename + "'");
    }
}

/*
 *  ======== getFileContents ========
 *  Returns a string containing the contents of file at 'filename'
 */
function getFileContents(filename)
{
    try {
        var input = "";
        var inputFile = java.io.File(filename);
        var fos = java.io.FileReader(inputFile);
        var reader = new java.io.BufferedReader(fos);
        var line;
        while ((line = reader.readLine()) != null)
            input += line + '\n';
        reader.close();

        return (input);
    }
    catch (e) {
        throw("Error reading file '" + filename + "'");
    }
}

/* Execution starts here */
var procNames = getProcNames();
writeFile(outFileName, getHTML(procNames));
