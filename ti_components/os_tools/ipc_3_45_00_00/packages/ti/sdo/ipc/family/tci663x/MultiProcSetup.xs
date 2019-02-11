/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== MultiProcSetup.xs ========
 */

var MultiProcSetup  = null;
var MultiProc       = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    MultiProcSetup = this;
    MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');

    /*  If not disabled by user and if procId has not been configured,
     *  add run-time function to set it.
     */
    if ((MultiProcSetup.configureProcId)
            && (MultiProc.id == MultiProc.INVALIDID)) {
        var Startup = xdc.useModule('xdc.runtime.Startup');
        Startup.firstFxns.$add(MultiProcSetup.init);
    }

    /* the procMap is for all processors on the local device */
    this.procMap.length = this.segmentSize;

    for (var i = 0; i < this.procMap.length; i++) {
        this.procMap[i] = -1;
    }

    /* make sure the MultiProc.nameList length fits into segmentSize */
    if (MultiProc.nameList.length > this.segmentSize) {
        this.$logError("The MultiProc.nameList length ("
            + MultiProc.nameList.length + ") is larger than "
            + "MultiProcSetup.segmentSize (" + this.segmentSize + ")", this);
    }

    /*  Use the MultiProc.nameList to initialize the procMap array
     *  with the corresponding coreId.
     */
    for (var i = 0; i < MultiProc.nameList.length; i++) {

        /* exclude host processor */
        if (MultiProc.nameList[i] == "HOST") {
            continue;
        }

        /* the numeric part of the name string determines the coreId */
        var name = MultiProc.nameList[i];
        var coreId = Number(name.substring("CORE".length));
        this.procMap[i] = coreId;
    }
}
