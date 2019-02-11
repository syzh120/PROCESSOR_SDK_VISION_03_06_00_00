/*
 * Copyright (c) 2008-2013, Texas Instruments Incorporated
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
 *  ======== SysMin.xs ========
 */

var SysMin = this;
var Core = undefined;

/*
 *  ======== module$static$init ========
 */
function module$static$init(obj, params)
{
    var segname = Program.sectMap[".tracebuf"];
    if (segname == undefined) {
        this.$logError(".tracebuf section not found in Program.sectMap", this);
    }

    var segment = Program.cpu.memoryMap[segname];
    if (segment == undefined) {
        this.$logError(".tracebuf section found, but not in " +
                "Program.cpu.memoryMap", this);
    }

    if (params.bufSize > segment.len) {
        this.$logError("bufSize 0x" + Number(params.bufSize).toString(16) +
                       " configured is too large, maximum bufSize allowed is " +
                       "0x" + Number(segment.len).toString(16) + ". Decrement" +
                       " the bufSize appropriately.", this);
    }

    if (params.bufSize - 8 < this.LINEBUFSIZE) {
        this.$logError("Buffer Size need to be larger than line buffer of size"
                       + " = 0x" + Number(this.LINEBUFSIZE).toString(16), this);
    }

    if (Core != undefined) {
        obj.lineBuffers.length = Core.numCores;
    }
    else {
        obj.lineBuffers.length = 1;
    }
    for (var i = 0; i < obj.lineBuffers.length; i++) {
        obj.lineBuffers[i].lineidx = 0;
        for (var j = 0; j < this.LINEBUFSIZE; j++) {
            obj.lineBuffers[i].linebuf[j] = 0;
        }
    }

    obj.outbuf.length = params.bufSize - 8;
    obj.writeidx.length = 0x1;
    obj.readidx.length = 0x1;
    if (params.bufSize != 0) {
        var Memory = xdc.module('xdc.runtime.Memory');
        Memory.staticPlace(obj.outbuf, 0x1000, params.sectionName);
        Memory.staticPlace(obj.writeidx, 0x4, params.sectionName);
        Memory.staticPlace(obj.readidx, 0x4, params.sectionName);
    }

    obj.outidx = 0;
    obj.getTime = false;
    obj.wrapped = false;
}

/*
 *  ======== module$use ========
 */
function module$use(obj, params)
{
    Core = xdc.useModule("ti.sysbios.hal.Core");
}

/*
 *  ======== viewInitModule ========
 *
 */
function viewInitModule(view, mod)
{
    view.outBuf = mod.outbuf;
    view.outBufIndex = mod.outidx;
    view.wrapped = mod.wrapped;
}

/*
 *  ======== viewInitOutputBuffer ========
 *  Displays the contents of SysMin's output buffer in ROV.
 */
function viewInitOutputBuffer(view)
{
    var Program = xdc.useModule('xdc.rov.Program');

    /*
     * Retrieve the module's state.
     * If this throws an exception, just allow it to propogate up.
     */
    var rawView = Program.scanRawView('ti.trace.SysMin');

    /*
     * If the buffer has not wrapped and the index of the next character to
     * write is 0, then the buffer is empty, and we can just return.
     */
    if (!rawView.modState.wrapped && (rawView.modState.outidx == 0)) {
        view.elements = new Array();
        return;
    }

    /* Get the buffer size from the configuration. */
    var bufSize = Program.getModuleConfig('ti.trace.SysMin').bufSize;

    /* Read in the outbuf */
    var outbuf = null;
    try {
        outbuf = Program.fetchArray(rawView.modState.outbuf$fetchDesc,
                                    rawView.modState.outbuf, bufSize);
    }
    /* If there's a problem, just re-throw the exception. */
    catch (e) {
        throw ("Problem reading output buffer: " + e.toString());
    }

    /*
     * We will create a new view element for each string terminated in a
     * newline.
     */
    var elements = new Array();

    /* Leftover characters from each read which did not end in a newline. */
    var leftover = "";

    /* If the output buffer has wrapped... */
    if (rawView.modState.wrapped) {
        /* Read from outidx to the end of the buffer. */
        var leftover = readChars("", outbuf, rawView.modState.outidx,
                                 outbuf.length - 1, elements);
    }

    /* Read from the beginning of the buffer to outidx */
    leftover = readChars(leftover, outbuf, 0, rawView.modState.outidx - 1,
                         elements);

    /*
     * If there are any leftover characters not terminated in a newline,
     * create an element for these and display them.
     */
    if (leftover != "") {
        var elem = Program.newViewStruct('ti.trace.SysMin',
                                         'OutputBuffer');
        elem.entry = leftover;
        elements[elements.length] = elem;
    }

    view.elements = elements;
}

/*
 *  ======== readChars ========
 *  Reads characters from 'buffer' from index 'begin' to 'end' and adds
 *  any newline-terminated strings as elements to the 'elements' array.
 *  If the last character is not a newline, this function returns what it's
 *  read from the "incomplete" string.
 *  The string 'leftover', the leftover incomplete string from the previous
 *  call, is prepended to the first string read.
 */
function readChars(leftover, buffer, begin, end, elements)
{
    /* Start with the previous incomplete string. */
    var str = leftover;

    /* For each of the specified characters... */
    for (var i = begin; i <= end; i++) {

        /* Convert the target values to characters. */
        var ch = String.fromCharCode(buffer[i]);

        /* Add the character to the current string. */
        str += ch;

        /*
         * If a string ends in a newline, create a separate table entry for it.
         */
        if (ch == '\n') {
            /*
             * Create a view structure to display the string, and add
             * it to the table.
             */
            var elem = Program.newViewStruct('ti.trace.SysMin',
                                             'OutputBuffer');
            elem.entry = str;
            elements[elements.length] = elem;

            /* Reset the string */
            str = "";
        }
    }

    /* Return any unfinished string characters. */
    return (str);
}
