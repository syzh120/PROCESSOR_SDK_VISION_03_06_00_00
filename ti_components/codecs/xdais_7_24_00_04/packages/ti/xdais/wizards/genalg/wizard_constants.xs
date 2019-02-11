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
var wizardVersion = "7.21";

var INIT_MESSAGE = "XDM GenAlg Wizard v" + wizardVersion
    + "\nTexas Instruments";

var GUI_HELP_LINK = 'http://processors.wiki.ti.com/index.php/XDM_GenAlg_Wizard_FAQ#Basic_Algorithm_Information';
var FAQ_LINK = 'http://processors.wiki.ti.com/index.php/XDM_GenAlg_Wizard_FAQ';
var TEMPLATES_DIR_LINK = 'http://processors.wiki.ti.com/index.php/XDM_GenAlg_Wizard_FAQ#What_is_the_templates_directory.3F';

var ABOUT_MESSAGE = INIT_MESSAGE;

/* abridged instructions to show at the top of each panel */
var BANNER0 =  "Specify Module, Vendor, Interface and Package Name." +
" Select a Base Interface and Target. Specify a valid Destination" +
" Directory and C6000 TI 'cgtools' Dir." +
" See Help for detailed information about field input. ";

/* if we ever change this list from static, we must
 * make sure the target we are loading inherits xdc.lbld.ITarget */
var targetList = [
    'ti.targets.C64P',
    'ti.targets.elf.C64P',
    'ti.targets.elf.C66',
    'ti.targets.C674',
    'ti.targets.elf.C674',
    'ti.targets.elf.C67P',
    'ti.targets.arm.elf.M3',
    'gnu.targets.arm.GCArmv5T',
    'gnu.targets.arm.GCArmv6',
    'gnu.targets.arm.GCArmv7A'
];

var targetDesc = [
    'C64P COFF',
    'C64P ELF',
    'C66 ELF',   // C66
    'C674 COFF',
    'C674 ELF',
    'C67P ELF',
    'M3 ELF',
    'ARM v5T GCC Linux',
    'ARM v6 GCC Linux',
    'ARM v7A GCC Linux'
];

var targetSuffixes = [
    '64P',
    'e64P',
    'e66',      // C66
    '674',
    'e674',
    'e67P',
    'em3',
    'v5T',
    'v6',
    'v7A'
];

var ccOpts = [
    '-mi10 -mo',
    '',
    '',           // C66
    '-mi10 -mo',
    '',
    '',
    '',
    '',
    '',
    ''
];

var cgTools = [
    'C64P',
    'C64P',
    'C66',   // C66
    'C674',
    'C674',
    'C67P',
    'M3',
    'v5T',
    'v6',
    'v7A'
];

var ENTER_CGTOOLS = '<C6000 TI codegen tools directory>';
var ENTER_M3_CGTOOLS = '<ARM M3 TI codegen tools directory>';
var ENTER_ARM_CGTOOLS = '<ARM GCC Linux codegen tools directory>';
var ENTER_OUTREPO = '<Algorithm package destination repository>';

var CGTOOLS_DESC = 'Your TI C6000 codegen tools directory, e.g.\n' +
'"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c6000"';

var M3_CGTOOLS_DESC = 'Your TI ARM M3 codegen tools directory, e.g.\n' +
'"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470"';

var ARM_CGTOOLS_DESC = 'Your ARM GCC Linux codegen tools directory, e.g.\n' +
'"/home/usr/arm/arm-2007q3"';

var GENALG_MODULE_HOVER = 'The name of the algorithm module';
var GENALG_VENDOR_HOVER = 'The name of the algorithm vendor';
var GENALG_INTERFACE_HOVER = 'The name of the algorithm interface.\nHas the form I<Module>';
var GENALG_XDM_ALG_PKG_HOVER = 'The name of the algorithm package';
var GENALG_TARGET = "The algorithm's build targets";
var OUTPUT_HOVER = 'Destination directory. The generated package will be in:\n'
+'<Destination Directory>/<Package Name with.dots.turned.into.forward.slashes>';

var EXPERT_HOVER = 'When left unchecked, the Interface and Package Name '
+'fields will be read-only\nand will be automatically generated based '
+'on Module and Vendor';

var IRES_HOVER = 'Check to add a generic implementation of the'
+' IRES interface to your algorithm.\n'
+'You will have to modify generated source files to implement'
+' a specific resource manager.';

