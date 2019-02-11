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
 * */

var csd = String(xdc.csd()).replace(/\\/g,"/");
var fileModule = xdc.module('xdc.services.io.File');
var logic;
var wizard_constants;

function setLogic(log)
{
    logic = log;
}

function setWizardConstants(wc)
{
    wizard_constants = wc;
}

/**
 * Logic to save userInput to an XML file
 * @param userInput
 * @return text to be saved to XML file
/*
 *  ======== saveXml ========
 */
function saveXml(algEnv)
{
    algEnv = logic.argsValidation(algEnv);
    try {
        var doc = <xdais_genalg_wizard/>;

        doc.packageName = algEnv.packageName;
        doc.moduleName = algEnv.moduleName;
        doc.vendorName = algEnv.vendorName;
        doc.interfaceName = algEnv.interfaceName;
        doc.templatesDir = algEnv.templatesDir;
        doc.templateName = algEnv.templateName;
        doc.outputRepository = algEnv.output;
        var targets = <targets/>;
        for (var i = 0; i < algEnv.targets.length; i++) {
            var targ = <target/>;
            targ.@target = algEnv.targets[i].target;
            targ.@name = algEnv.targets[i].targname;
            targ.@suffix = algEnv.targets[i].targsuffix;
            targ.@ccOpts = algEnv.targets[i].ccOpts;
            targ.@cgTools = algEnv.targets[i].cgTools;
            targets.appendChild(targ);
        }
        doc.appendChild(targets);
        doc.genCCSProj = algEnv.genCCSProj;
        if (algEnv.cgTools) {
            doc.cgTools = algEnv.cgTools;
        }
        if (algEnv.m3cgTools) {
            doc.m3cgTools = algEnv.m3cgTools;
        }
        if (algEnv.gccCgTools) {
            doc.gccCgTools = algEnv.gccCgTools;
        }
        doc.rulesCheck = algEnv.rulesCheck == true ? 'true' : 'false';
        doc.expertCheck = algEnv.expertCheck == true ? 'true' : 'false';
        doc.ires = algEnv.ires == true ? 'true' : 'false';

        return(doc.toXMLString());
    }
    catch (e) {
        print('exception ' + e.message);
        return ('');
    }
}


/**
 * Writes text to a file
 * @param {String} Output file location
 * @param {String} Text to be written to file
 * @return {Integer} 0 for completion, 1 for error
 */
function textFileWriter( outputFileLocation, fileText ) {
    var file = fileModule.open( outputFileLocation, "w" );
    var completed = file.writeLine( fileText.toString() );
    file.close();
    if (completed==false) {
        return -1;
    }
    return 0;
}

function textFileReader( inputFileLocation ) {
    var text = "";
    var file = fileModule.open(inputFileLocation, "r");
    var line;
    while ((line = file.readLine()) != null) {
          text += line + "\n";
    }
    file.close();
    return text;
}

/**
* Logic to update userInput based on XML file
* @param XML file containing userInput data
* @return updated userInput based on XML file
*/
function loadXml(file, algEnv)
{
    var readXml = textFileReader(file);
    readXml = readXml.replace(/<\?xml version="1\.0"\?>/, '');
    var doc = new XML(readXml);

    algEnv.wizardVersion = String(doc.version);
    algEnv.packageName = String(doc.packageName);
    algEnv.moduleName = String(doc.moduleName);
    algEnv.vendorName = String(doc.vendorName);
    algEnv.interfaceName = String(doc.interfaceName);
    algEnv.templatesDir = String(doc.templatesDir);
    algEnv.templateName = String(doc.templateName);
    algEnv.output = String(doc.outputRepository);
    algEnv.targets = [];
    for (var i = 0; i < doc.targets.target.length(); i++) {
        var data = {};
        var targIndex = null;
        data.target = String(doc.targets.target[i].@target);
        data.targname = String(doc.targets.target[i].@name);;
        data.targsuffix = String(doc.targets.target[i].@suffix);
        if (doc.targets.target[i].@ccOpts.length()) {
            data.ccOpts = String(doc.targets.target[i].@ccOpts);
        }
        else {
            targIndex = logic.getTargetIndex(data.target);
            if (targIndex != -1) {
                data.ccOpts = wizard_constants.ccOpts(targIndex);
            }
        }
        if (doc.targets.target[i].@cgTools.length()) {
            data.cgTools = String(doc.targets.target[i].@cgTools);
        }
        else {
            targIndex = (targIndex == null) ? logic.getTargetIndex(data.target) : targIndex;
            if (targIndex != -1) {
                data.cgTools = wizard_constants.cgTools(targIndex);
            }
        }
        algEnv.targets.push(data);
    }
    algEnv.genCCSProj = (doc.genCCSProj == 'true') ? true : false;
    algEnv.cgTools = String(doc.cgTools);
    if (doc.m3cgTools.length()) {
        algEnv.m3cgTools = String(doc.m3cgTools);
    }
    if (doc.v5TcgTools.length()) {
        algEnv.gccCgTools = String(doc.v5TcgTools);
    }
    if (doc.gccCgTools.length()) {
        algEnv.gccCgTools = String(doc.gccCgTools);
    }
    algEnv.rulesCheck = doc.rulesCheck == 'true' ? true : false;
    algEnv.expertCheck = doc.expertCheck == 'true' ? true : false;
    algEnv.ires = doc.ires == 'true' ? true : false;

    return algEnv;
}

/**
* A relative path in a saved XML file (used in the examples dir) must be
* evaluated
* @param {String} Exact string from XML file
* @return {String} Canonical Path of Input
*/
function relativePathCheck(path)
{
    path = String(path);
    if (path.length) {
        if (!java.io.File(path).isAbsolute()) {
            var canonicalPath = csd + path.substring(1, path.length);
        }
        else {
            var canonicalPath = path;
        }
        canonicalPath = String(java.io.File(canonicalPath).getCanonicalPath());
        return (canonicalPath.replace(/\\/g,"/"));
    }
    return ("");
}

