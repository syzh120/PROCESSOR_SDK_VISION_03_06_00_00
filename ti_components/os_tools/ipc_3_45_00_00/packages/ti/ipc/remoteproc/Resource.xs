/*
 * Copyright (c) 2011-2012, Texas Instruments Incorporated
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
 *  ======== IpcMemory.xs ========
 *
 */
var IpcMemory;

/*
 *  ======== module$meta$init ========
 */
function module$use()
{
    IpcMemory = this;

    var memmap = Program.cpu.memoryMap;
    var segment = null;
    var addr = IpcMemory.loadAddr;

    if (IpcMemory.loadSegment != undefined) {
        for (var i=0; i < memmap.length; i++) {
            if (memmap[i].name == IpcMemory.loadSegment) {
                segment = memmap[i];
            }
        }
        if (segment == null) {
            this.$logError("IpcMemory.loadSegment not found", this);
        }
        addr = segment.base;
    }

    /* The .resource_table section should always be at the segment base */
    Program.sectMap[".resource_table"] = new Program.SectionSpec();
    Program.sectMap[".resource_table"].type = "NOINIT";
    Program.sectMap[".resource_table"].loadAddress = addr;
}

function module$static$init(obj, params)
{
    var memmap = Program.cpu.memoryMap;
    var segment = null;
    var addr = IpcMemory.loadAddr;

    if (IpcMemory.loadSegment != undefined) {
        for (var i=0; i < memmap.length; i++) {
            if (memmap[i].name == IpcMemory.loadSegment) {
                segment = memmap[i];
            }
        }
        if (null == segment) {
            this.$logError("IpcMemory.loadSegment not found", this);
        }
//        print("IpcMemory.loadSegment", IpcMemory.loadSegment);
        addr = segment.base;
    }

    /* Assign the addresses for the module state variables */
    obj.pTable = addr;
}
