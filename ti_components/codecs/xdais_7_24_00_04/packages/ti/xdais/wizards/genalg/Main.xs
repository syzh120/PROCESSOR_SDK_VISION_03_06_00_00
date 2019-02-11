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
algEnv = {};
var logic = xdc.loadCapsule("logic.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var gui;

/*
 *  ======== run ========
 */
function run(cmdr, args)
{
    var inst = this.$private
    inst.self = this;

    for (p in inst.self) inst[p] = inst.self[p];

    inst.cmdr = cmdr;
    inst.args = args;

    /* for each module in this package ... */
    for each (var mod in this.$package.$modules) {
        var cap = mod.$capsule;
        if (cap && "createPartControl" in cap) {
            gui = cap;
            break;
        }
    }

    if (!gui) {
        print("\nCannot start XDM GenAlg Wizard. Please " +
              "make sure the package ti.xdais.wizards.genalg " +
              "is completely built.");
        return;
    }

    algEnv.wizardVersion = wizard_constants.wizardVersion;

    /* store the cmd line params in our data structure
        all arguments are optional unless otherwise noted */
    algEnv.xmlFile = inst.xmlFile;
    algEnv.gui = inst.gui ? inst.gui : !algEnv.xmlFile;
    algEnv.shellLocation;

    algEnv.argvArgs = [];
    for each (var a in inst.args) {
        algEnv.argvArgs.push(a);
    }

    /* replace since user can enter backward slashes on command line */
    algEnv.xmlFile = (algEnv.xmlFile + "").replace(/\\/g,"/");

    try {
        if (cmdr.tid) {
            algEnv.tid = cmdr.tid;
            algEnv.guiId = cmdr.tid + 1;
        }
        else {
            algEnv.tid = algEnv.guiId = 0;
        }
    }
    catch (e) {
        algEnv.tid = algEnv.guiId = 0;
    }

    if (algEnv.tid != algEnv.guiId) {
        algEnv = logic.argsValidation(algEnv);
        gui.setAlgEnv(algEnv);

        /* create an instance of IWorkbenchPart and send it */
        /* back to the tools server to call gui.createPartControl */
        var wbp = new Packages.org.eclipse.ui.IWorkbenchPart(gui);
        cmdr.socket.giveToClient(wbp);

        /* wait for gui to close */
        var val = cmdr.socket.takeFromClient();
    }
    else {
        if (algEnv.gui) {
            algEnv = logic.argsValidation(algEnv);
            if (inst.cgTools) {
                algEnv.cgTools = inst.cgTools;
            }
            if (inst.gccCgTools) {
                algEnv.gccCgTools = inst.gccCgTools;
            }
            if (inst.m3cgTools) {
                algEnv.m3cgTools = inst.m3cgTools;
            }
            if (inst.destDir) {
                algEnv.output = inst.destDir;
            }
            gui.setAlgEnv(algEnv);
            algEnv = gui.main(algEnv);
        }
        else if (algEnv.xmlFile == "null") {
            print("\nCommand Line Version requires XML File! "
                + "See xs ti.xdais.wizards.genalg --help for more information.");
            algEnv.gui = true;
            algEnv = logic.argsValidation(algEnv);
            if (inst.cgTools) {
                algEnv.cgTools = inst.cgTools;
            }
            if (inst.gccCgTools) {
                algEnv.gccCgTools = inst.gccCgTools;
            }
            if (inst.m3cgTools) {
                algEnv.m3cgTools = inst.m3cgTools;
            }
            if (inst.destDir) {
                algEnv.output = inst.destDir;
            }
            algEnv = gui.main(algEnv);
        }
        else {
            print("\nStarting Command Line XDM GenAlg Wizard...");
            algEnv = logic.argsValidation(algEnv);
            if (inst.cgTools) {
                algEnv.cgTools = inst.cgTools;
            }
            if (inst.gccCgTools) {
                algEnv.gccCgTools = inst.gccCgTools;
            }
            if (inst.m3cgTools) {
                algEnv.m3cgTools = inst.m3cgTools;
            }
            if (inst.destDir) {
                algEnv.output = inst.destDir;
            }
        }
    }
    if (!algEnv.error && logic.createFiles(algEnv) == 0) {
        var output = algEnv.output + '/' + algEnv.packageName.replace(/\./g,'/');

        logic.gprint( "\nPackage creation successful...\n"
            + "Files output to " + output, algEnv);
    }
    else {
        logic.gprint("\nPackage creation unsuccessful.", algEnv);
    }
}
