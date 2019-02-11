/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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

/*
 *  ======== getLibs ========
 */
function getLibs()
{
    var suffix = Program.build.target.findSuffix(this);
    var device = Program.cpu.deviceName;
    var isa = Program.build.target.isa;

    if (null == suffix) {
        return (null);
    }


    var lib = "tiledmemory";
    lib += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }

  return (dir + "/" + lib);
}

/*
 *  ======== getSects ========
 */
function getSects() {
   return (null);
}


function close()
{
    var os = Program.build.target.os;

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }


    // This module uses Semaphores
    if (this.TILEDMEMORY.$used) {

        if (os == "Linux") {
            var Sem = xdc.useModule('xdc.runtime.knl.SemProcess');
            Sem.Proxy = xdc.useModule('ti.sdo.xdcrunime.linux.SemProcessSupport');
        }
        else if (os == undefined) {
            /* assume bios 6 */
            var Sem = xdc.useModule('xdc.runtime.knl.SemThread');
            Sem.Proxy = xdc.useModule('ti.sysbios.xdcruntime.SemThreadSupport');
        }
        else {
            var Sem = xdc.useModule('xdc.runtime.knl.SemThread');
            var SemMP = xdc.useModule('xdc.runtime.knl.SemProcess');
            if ((Sem.Proxy == undefined) && (SemMP.Proxy == undefined)) {
                print(this.$name + "close(): WARNING. SemaphoreMP proxy was "
                        + "not configured and no "
                        + "default was known for the target OS");
            }
        }

        var device = Program.cpu.deviceName;

        if (this.TILEDMEMORY.tiledmemoryBaseAddress == null) {
            if ((device.match("OMAP4430") != null)) {
                this.TILEDMEMORY.tiledmemoryBaseAddress = 0x60000000;
            } else if ((device.match(/TMS320DM8168|TMS320C6A8168|TMS320TI816X/)
                    != null)) {
                this.TILEDMEMORY.tiledmemoryBaseAddress = 0x60000000;
            } else if ((device.match(/TMS320DM8148|TMS320TI814X/) != null)) {
                this.TILEDMEMORY.tiledmemoryBaseAddress = 0x60000000;
            }
            else {
                throw(" TILEDMEMORY error: Unrecognized device " +device +
                        ". Please configure tiledmemoryBaseAddress in the .cfg"+
                        " file.\n");
            }
        }

        /* include ti.sdo.tiler */
        /* var tilerSettings = xdc.useModule('ti.sdo.tiler.Settings'); */

        xdc.useModule("ti.sdo.fc.ires.IRESMAN");
    }
}
