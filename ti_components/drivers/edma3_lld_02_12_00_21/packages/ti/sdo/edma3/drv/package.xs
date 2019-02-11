/*
 * package.xs
 *
 * xdc script file for the EDMA DRV package.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/*
 * ======== package.xs ========
 *
 */

/*
 * ======== getLibs ========
 */
function getLibs(prog)
{
    var bool = 0;

    print ("Inside EDMA3 Drv getLibs");

    /* Prepare variables to form the library path within this package */
    var name = "edma3_lld_drv";
    var lib = "lib/";
    var target;
    var extension;

    /* Boards supported */
    var devices = [
                        'TMS320DA830',
                        'TMS320TCI6608',
                        'TMS320TCI6616',
                        'TMS320TCI6614',
                        'TMS320C6657',
                        'Kepler',
                        'TMS320C6670',
                        'TMS320C6678',
                        'TMS320TCI6614',
                        'TMS320C6657',
                        'TMS320TCI6638',
                        'TMS320TCI6636',
                        'TMS320TCI6630K2L',
                        'TMS320C66AK2E05',
                        'TCI66AK2G02',
                        'TMS320C6748',
                        'OMAPL137',
                        'OMAPL138',
                        'TMS320DM8168',
                        'TMS320C6472',
                        'TMS320CTCI6486',
                        'TMS320DM8148',
                        'TMS320TI814X',
                        'TMS320TI816X',
                        'AM3359',
                        'AM437X',
                        'Vayu',
                        'DRA7XX',
                        'TDA3XX',
                        'DRA72X',
                        'TDA2EX',
                        'AM572X',
                        'AM571X',
                        'TCI6636K2H',
                        'C66AK2E05',
                        'TCI6630K2L'
                    ];

    for (var i = 0; i < devices.length; i++)
        {
        if (java.lang.String(Program.cpu.deviceName).equals(devices[i]))
            {
                /* Choose the selected platform and build the complete name */
                extension = ".a" + Program.build.target.suffix;
                if (java.lang.String(Program.build.target.suffix).contains('674'))
                	target = "674/";
                if (java.lang.String(Program.build.target.suffix).contains('64P'))
                	target = "64p/";
                if (java.lang.String(Program.build.target.suffix).contains('66'))
                	target = "66/";
                if (java.lang.String(Program.build.target.suffix).contains('a8'))
                	target = "a8/";
                if (java.lang.String(Program.build.target.suffix).contains('m3'))
                	target = "m3/";
                if (java.lang.String(Program.build.target.suffix).contains('m4'))
                	target = "m4/";
                if (java.lang.String(Program.build.target.suffix).contains('a15'))
                	target = "a15/";
                if (java.lang.String(Program.build.target.suffix).contains('a8'))
                	target = "a8/";
                if (java.lang.String(Program.build.target.suffix).contains('9'))
                	target = "arm9/";
                if (java.lang.String(Program.build.target.suffix).contains('arp32'))
                	target = "arp32/";
                lib = lib + target;
                bool = 1;
                break;
            }
        }

    if (bool == 0)
        throw new Error('Unexpected value in "platform" parameter')

    switch (this.profile) {
    case 'debug':
        /* enable debug build for debug profile only */
        lib = lib + "debug/" + name + extension;
        break;

    default:
        /* release profile for everything else */
        lib = lib + "release/" + name + extension;
    }

    print("    will link with " + this.$name + ":" + lib);

    /* return the library name */
    return (lib);
}

