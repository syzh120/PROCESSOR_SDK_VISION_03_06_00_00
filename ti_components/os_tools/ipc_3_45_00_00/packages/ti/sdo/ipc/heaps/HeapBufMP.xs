/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *  ======== HeapBufMP.xs ========
 *
 */

var HeapBufMP       = null;
var SharedRegion    = null;
var NameServer      = null;
var ListMP          = null;
var Ipc             = null;
var Cache           = null;
var GateMP          = null;
var Memory          = null;

var instCount = 0;  /* use to determine if processing last instance */

/*
 *  ======== module$use ========
 */
function module$use()
{
    HeapBufMP       = this;
    NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    ListMP          = xdc.useModule("ti.sdo.ipc.ListMP");
    SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');
    Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    GateMP          = xdc.useModule('ti.sdo.ipc.GateMP');
    Cache           = xdc.useModule('ti.sysbios.hal.Cache');
    Memory          = xdc.useModule('xdc.runtime.Memory');
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    mod.nameServer  = null;

    /* initialize the NameServer param to be used now or later */
    HeapBufMP.nameSrvPrms.maxRuntimeEntries = params.maxRuntimeEntries;
    HeapBufMP.nameSrvPrms.tableSection      = params.tableSection;
    HeapBufMP.nameSrvPrms.maxNameLen        = params.maxNameLen;

    /*
     *  Get the current number of created static instances of this module.
     *  Note: if user creates a static instance after this point and
     *        expects to use NameServer, this is a problem.
     */
    var instCount = this.$instances.length;

    /* create NameServer here only if no static instances are created */
    if (instCount == 0) {
        mod.nameServer = NameServer.create("HeapBufMP",
                                            HeapBufMP.nameSrvPrms);
    }
}


/*
 *  ======== viewInitBasic ========
 *  Initialize the 'Basic' HeapBufMP instance view.
 */
function viewInitBasic(view, obj)
{
    var NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    var HeapBufMP       = xdc.useModule('ti.sdo.ipc.heaps.HeapBufMP');
    var Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    var SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');

    view.name       = NameServer.getName$view("HeapBufMP",
                      SharedRegion.getSRPtrMeta$view(obj.attrs));
    view.buf        = $addr(obj.buf);
    view.objType    = Ipc.getObjTypeStr$view(obj.objType);
    view.gate       = obj.gate;
    view.exact      = obj.exact;
    view.align      = obj.align;
    view.blockSize  = obj.blockSize;
    view.numBlocks  = obj.numBlocks;

    var modCfg = Program.getModuleConfig('ti.sdo.ipc.heaps.HeapBufMP');

    try {
        var attrs = Program.fetchStruct(HeapBufMP.Attrs$fetchDesc,
                                        obj.attrs.$addr, false);

        var dataViews = Program.scanInstanceDataView('ti.sdo.ipc.ListMP',
            'Lists');

        /*
         *  Compute 'numFreeBlocks' by counting the number of elements
         *  on the freeList
         */
        for each (var dataView in dataViews) {
            if (dataView.label.match(Number(obj.freeList).toString(16))) {
                var numFreeBlocks = dataView.elements.length;
            }
        }

        view.curAllocated  = obj.numBlocks - numFreeBlocks;

        if (modCfg.trackAllocs) {
            /* Compute only if trackMaxAllocs. Otherwise leave blank */
            if (attrs.minFreeBlocks != 0xFFFFFFFF) {
                var minFreeBlocks = attrs.minFreeBlocks;
            }
            else {
                var minFreeBlocks = obj.numBlocks;

            }
            view.maxAllocated = obj.numBlocks - minFreeBlocks;
        }

        if (view.curAllocated < 0) {
            view.$status["curAllocated"] = "Error: curAllocated" +
                    " < 0! (possibly caused by an invalid free)";
        }
    }
    catch (e) {
        view.$status["curAllocated"] = view.$status["maxAllocated"] =
            "Error:  could not access shared memory to retreive stats: " + e;
    }
}
