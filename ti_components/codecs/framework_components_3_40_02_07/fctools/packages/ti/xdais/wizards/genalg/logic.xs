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

var xmlOps = xdc.loadCapsule("xmlOps.xs");
var shared_gui = xdc.loadCapsule("shared_gui.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var mkpkg = xdc.module("xdc.tools.mkpkg.Main");
var csd = String(xdc.csd()).replace(/\\/g,"/");

function argsValidation(algEnv) {

    var proot = csd + '/..';
    var pn = 'ti.xdais.wizards.genalg';
    for (var i = 0; (i = pn.indexOf('.', i) + 1) > 0; ) {
            proot += '/..';
    }
    proot = String(java.io.File(proot).getCanonicalPath()).replace(/\\/g, '/');

    if ( algEnv.xmlFile != null && algEnv.xmlFile != "null") {
        if ( java.io.File( algEnv.xmlFile ).exists() ) {
            try {
                algEnv = xmlOps.loadXml( algEnv.xmlFile, algEnv );
            }
            catch(e) {
                gprint("Error: " + e, algEnv );
            }
        }
        else {
            gprint("XML File, " + algEnv.xmlFile + ", not found. "
                + "Wizard starting without loading XML File...",
                algEnv);
            algEnv.xmlFile = "null";
        }
    }

    if (!algEnv.moduleName) {
        algEnv.moduleName = 'MYMODULE';
    }

    if (!algEnv.vendorName) {
        algEnv.vendorName = 'MYCOMPANY';
    }

    if (!algEnv.interfaceName) {
        algEnv.interfaceName = 'I' + algEnv.moduleName;
    }

    if (!algEnv.packageName) {
        algEnv.packageName = (algEnv.vendorName + '.' + algEnv.moduleName).toLowerCase();
    }

    if (algEnv.output == null || algEnv.output == 'null') {
        algEnv.output = wizard_constants.ENTER_OUTREPO;
    }
    if (!algEnv.templatesDir) {
        algEnv.templatesDir = proot + '/ti/xdais/dm/templates';
    }
    if (!algEnv.targets) {
        try {
            var tmod = xdc.useModule(wizard_constants.targetList[0]);
            var data = {};
            data.target = wizard_constants.targetList[0];
            data.targname = tmod.name;
            data.targsuffix = tmod.suffix;
            data.ccOpts = wizard_constants.ccOpts[0];
            data.cgTools = wizard_constants.cgTools[0];
            algEnv.targets = [];
            algEnv.targets.push(data);
        }
        catch (e) {
        }
    }

    if (algEnv.genCCSProj != true && algEnv.genCCSProj != false) {
        algEnv.genCCSProj = true;
    }

    if (!algEnv.xdaisInstall) {
        algEnv.xdaisInstall = proot.replace(/\/packages$/, '');
    }
    if (!algEnv.xdcInstall) {
        algEnv.xdcInstall = xdc.getPackageBase('xdc');
        algEnv.xdcInstall = algEnv.xdcInstall.replace(/\\/g, '/');
        algEnv.xdcInstall = algEnv.xdcInstall.replace(/\/+$/, '');
        algEnv.xdcInstall = algEnv.xdcInstall.replace(/\/packages\/xdc$/, '');
        algEnv.xdcVersOK = false;
        for each (var f in java.io.File(algEnv.xdcInstall + '/eclipse/plugins').listFiles()) {
            if (f.isFile()) {
                continue;
            }
            var name = String(f.getName());
            if (name.match(/^org.eclipse.rtsc.xdctools.core_/)) {
                algEnv.xdcVers = name.substr(31);
                if (Number(algEnv.xdcVers.substr(0, 4)) >= 3.16) {
                    algEnv.xdcVersOK = true;
                }
                break;
            }
        }
    }
    if (!algEnv.cgTools) {
        var cgTools = algEnv.xdcInstall + '/../ccsv4/tools/compiler/c6000';
        var validCgTools = validCgToolsDir(cgTools);
        if (!validCgTools && java.io.File(algEnv.xdaisInstall).exists()) {
            cgTools = algEnv.xdaisInstall + '/../ccsv4/tools/compiler/c6000';
            validCgTools = validCgToolsDir(cgTools);
        }
        if (validCgTools) {
            algEnv.cgTools =
                String(java.io.File(cgTools).getCanonicalPath()).replace(/\\/g, '/');
        }
        else {
            algEnv.cgTools = wizard_constants.ENTER_CGTOOLS
        }
    }
    if (!algEnv.m3cgTools) {
        var m3cgTools = algEnv.xdcInstall + '/../ccsv4/tools/compiler/tms470';
        var validm3cgTools = validM3cgToolsDir(m3cgTools);
        if (validm3cgTools) {
            algEnv.m3cgTools =
                String(java.io.File(m3cgTools).getCanonicalPath()).replace(/\\/g, '/');
        }
        else {
            algEnv.m3cgTools = wizard_constants.ENTER_M3_CGTOOLS
        }
    }
    if (!algEnv.gccCgTools) {
        algEnv.gccCgTools = wizard_constants.ENTER_ARM_CGTOOLS
    }
    return algEnv;
}

function gprint(message, algEnv) {
    if (algEnv.gui == true) {
        shared_gui.createMessageBox(message, algEnv);
    }
    else{
        print(message);
    }
}

function createFiles(algEnv) {

    var status = 0;
//    algEnv = argsValidation(algEnv);

    var outputDir = algEnv.output + '/' + algEnv.packageName.replace(/\./g,'/');
    outputDir = outputDir.replace("//", "/");
    outputDir = outputDir.replace(/\\/g,"/");
    if (java.io.File(outputDir).exists()) {
        var list = java.io.File(outputDir).list();
        if (list.length!=0) {
            if (!algEnv.gui ) {
                gprint("\nWarning: " + outputDir + " is not empty--files may be "
                    + "overwritten... Would you like to continue? y/n",
                    algEnv);
                var isr = new java.io.InputStreamReader(
                    java.lang.System["in"] );
                var br = new java.io.BufferedReader( isr );

                try{
                    var output = br.readLine();
                }
                catch(e) {}

                if (output == "n") {
                    gprint("Quitting now...", algEnv);
                    status = 1;
                }
                else if(output != "y") {
                    gprint("Invalid selection. Quitting now...", algEnv);
                    status = 1;
                }
            }
        }
    }

    if (status == 0) {
        /* function mkpkg( template_dir, output, args ) */
        try {
            var algObj = {};
            algObj.packageName = algEnv.packageName;
            algObj.module = algEnv.moduleName.toUpperCase();
            algObj.vendor = algEnv.vendorName.toUpperCase();
            algObj.inface = algEnv.interfaceName.toUpperCase();
            algObj.targets = algEnv.targets;
            algObj.xdaisInstall = algEnv.xdaisInstall;
            algObj.xdcInstall = algEnv.xdcInstall;
            algObj.ires = algEnv.ires;
            algObj.templateName = algEnv.templateName;

            var C6x = false;
            var gcc = false;
            var M3 = false;
            for (var i = 0; i < algObj.targets.length; i++) {
                if (!C6x && (algObj.targets[i].cgTools == 'C64P' || algObj.targets[i].cgTools == 'C674' ||
                    algObj.targets[i].cgTools == 'C66' || algObj.targets[i].cgTools == 'C67P')) {
                    C6x = true;
                }
                else if (!gcc && (algObj.targets[i].cgTools == 'v5T' || algObj.targets[i].cgTools == 'v6' ||
                         algObj.targets[i].cgTools == 'v7A')) {
                    gcc = true;
                }
                else if (!M3 && algObj.targets[i].cgTools == 'M3') {
                    M3 = true;
                }
                if (C6x && gcc && M3) {
                    break;
                }
            }
            if (C6x) {
                algObj.cgTools = algEnv.cgTools;
                if (algObj.cgTools) {
                    algObj.cgTools = algObj.cgTools.replace(/\\/g,'/');
                }
            }
            else {
                algObj.cgTools = null;
            }
            if (gcc) {
                algObj.gccCgTools = algEnv.gccCgTools;
                if (algObj.gccCgTools) {
                    algObj.gccCgTools = algObj.gccCgTools.replace(/\\/g,'/');
                }
            }
            else {
                algObj.gccCgTools = null;
            }
            if (M3) {
                algObj.m3cgTools = algEnv.m3cgTools;
                if (algObj.m3cgTools) {
                    algObj.m3cgTools = algObj.m3cgTools.replace(/\\/g,'/');
                }
            }
            else {
                algObj.m3cgTools = null;
            }
            algObj.xdcVersOK = algEnv.xdcVersOK;

            mkpkg.mkpkg(algEnv.templatesDir + '/' + algEnv.templateName,
                        outputDir, algObj);

            mkpkg.mkpkg("ti/xdais/wizards/genalg/templates/build", outputDir,
                        algObj);

            if (algEnv.genCCSProj) {
                mkpkg.mkpkg("ti/xdais/wizards/genalg/templates/ccsv4", outputDir,
                             algEnv);
            }

            if (algEnv.ires) {
                mkpkg.mkpkg("ti/xdais/wizards/genalg/templates", outputDir,
                            algObj);
            }
        }
        catch (e) {
            gprint("An error while creating package " +
                    algEnv.packageName + ":\n" + e, algEnv);
            status = 1;
        }
    }
    return(status);
}

function validCgToolsDir(dir)
{
    if (!String(dir).length) {
        return (false);
    }
    var valid = true;
    var clFile = dir + '/bin/cl6x';
    var clExeFile = dir + '/bin/cl6x.exe';
    if (!java.io.File(clFile).exists() &&
        !java.io.File(clExeFile).exists()) {
        valid = false;
    }
    return (valid);
}

function validM3cgToolsDir(dir)
{
    if (!String(dir).length) {
        return (false);
    }
    var valid = true;
    var clFile = dir + '/bin/cl470';
    var clExeFile = dir + '/bin/cl470.exe';
    if (!java.io.File(clFile).exists() &&
        !java.io.File(clExeFile).exists()) {
        valid = false;
    }
    return (valid);
}

function validGccCgToolsDir(dir)
{
    if (!String(dir).length) {
        return (false);
    }
    var valid = true;
    if (!java.io.File(dir + '/bin/arm-none-linux-gnueabi-gcc').exists()) {
        valid = false;
    }
    return (valid);
}

function getTargetIndex(target)
{
    for (var i = 0; i < wizard_constants.targetList.length; i++) {
        if (wizard_constants.targetList[i] == target) {
            return (i);
        }
    }
    return (-1);
}
