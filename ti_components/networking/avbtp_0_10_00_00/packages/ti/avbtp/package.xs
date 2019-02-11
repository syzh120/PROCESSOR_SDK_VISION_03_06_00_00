/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  ======== Package.getLibs ========
 *  This function is called when a program's configuration files are
 *  being generated and it returns the name of a library appropriate
 *  for the program's configuration.
 */

function getLibs(prog)
{
    /* get necessary module references */
    var AVBTP = xdc.module('ti.avbtp.AVBTP');

    /* determine the lib's suffix-based directory name */
    var suffix = prog.build.target.suffix;
    var libSuffix = ".a" + suffix;
    
    /* append "e" to lib name for big endian builds */    
    libSuffix += (prog.build.target.model.endian == "little") ? "" : "e";    

    var libName = this.$name;
    var lib = "";
    
    if (AVBTP.instrumentedBuild)
    {
        libName += "_instr";
    }

    var profile = ((this.profile + "").match(/whole_program/)) ?
        "release" : this.profile;
     
    lib = "lib/" + profile + "/" + libName + libSuffix;

    if (java.io.File(this.packageBase + lib).exists())
    {
        print("Inside AVBTP Package getLibs:");
        print("\twill link with library: " + lib);
        return lib;
    }
    else
    {
        /* could not find any library, return null */
        print("Error: Library not found: " + lib);
        return null;
    }
}

