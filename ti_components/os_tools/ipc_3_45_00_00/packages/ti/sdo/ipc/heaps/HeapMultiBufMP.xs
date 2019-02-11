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
 *  ======== HeapMultiBufMP.xs ========
 *
 */

var HeapMultiBufMP  = null;
var SharedRegion    = null;
var NameServer      = null;
var Ipc             = null;
var Cache           = null;
var GateMP          = null;

var instCount = 0;  /* use to determine if processing last instance */

/*
 *  ======== module$use ========
 */
function module$use()
{
    HeapMultiBufMP  = this;
    Memory          = xdc.useModule('xdc.runtime.Memory');
    NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');
    Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    GateMP          = xdc.useModule('ti.sdo.ipc.GateMP');
    Cache           = xdc.useModule('ti.sysbios.hal.Cache');
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    mod.nameServer  = null;

    /* Setup nameserver */
    /* initialize the NameServer param to be used now or later */
    HeapMultiBufMP.nameSrvPrms.maxRuntimeEntries
            = params.maxRuntimeEntries;
    HeapMultiBufMP.nameSrvPrms.tableSection = params.tableSection;
    HeapMultiBufMP.nameSrvPrms.maxNameLen   = params.maxNameLen;

    /*
     *  Get the current number of created static instances of this module.
     *  Note: if user creates a static instance after this point and
     *        expects to use NameServer, this is a problem.
     */
    var instCount = this.$instances.length;

    /* create NameServer here only if no static instances are created */
    if (instCount == 0) {
        mod.nameServer = NameServer.create("HeapMultiBufMP",
                                            HeapMultiBufMP.nameSrvPrms);
    }
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    var HeapMultiBufMP  = xdc.useModule('ti.sdo.ipc.heaps.HeapMultiBufMP');
    var Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');
    var SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');

    /* view.name */
    view.name = NameServer.getName$view("HeapMultiBufMP",
        SharedRegion.getSRPtrMeta$view(obj.attrs));

    /* view.objType */
    view.objType = Ipc.getObjTypeStr$view(obj.objType);

    /* view.gate */
    view.gate = obj.gate;

    try {
        var attrs = Program.fetchStruct(HeapMultiBufMP.Attrs$fetchDesc,
                                        obj.attrs.$addr);
        var totalSize = 0;
        for (var i = 0; i < attrs.numBuckets; i++) {
            totalSize += attrs.buckets[i].blockSize *
                         attrs.buckets[i].numBlocks;
        }

        /* view.totalSize */
        view.totalSize = "0x" + Number(totalSize).toString(16);

        /* view.exact */
        view.exact = attrs.exact == 1 ? true : false;

        /* view.buf */
        view.buf = $addr(obj.buf);
    }
    catch (e) {
        throw("Error: could not access shared memory: " + e);
    }

}

/*
 *  ======== viewInitData ========
 */
function viewInitData(view, obj)
{
    var HeapMultiBufMP = xdc.useModule('ti.sdo.ipc.heaps.HeapMultiBufMP');
    var SharedRegion   = xdc.useModule('ti.sdo.ipc.SharedRegion');
    var NameServer     = xdc.useModule('ti.sdo.utils.NameServer');

    /* Display the instance label in the tree */
    view.label = NameServer.getName$view("HeapMultiBufMP",
        SharedRegion.getSRPtrMeta$view(obj.attrs.$addr));
    if (view.label == null) {
        view.label = "0x" + Number(obj.attrs.$addr).toString(16);
    }

    /* Fetch attrs struct */
    try {
        var attrs = Program.fetchStruct(HeapMultiBufMP.Attrs$fetchDesc,
                                        obj.attrs.$addr);

        for (i = 0; i < Number(attrs.numBuckets); i++) {
            var elem = Program.newViewStruct('ti.sdo.ipc.heaps.HeapMultiBufMP',
                                             'Buffer Information');
            elem.baseAddr       = "0x" + Number(SharedRegion.getPtrMeta$view(
                attrs.buckets[i].baseAddr)).toString(16);
            elem.blockSize      = attrs.buckets[i].blockSize;
            elem.align          = attrs.buckets[i].align;
            elem.numBlocks      = attrs.buckets[i].numBlocks;
            elem.numFreeBlocks  = attrs.buckets[i].numFreeBlocks;

            elem.minFreeBlocks  = attrs.buckets[i].minFreeBlocks == 0xffffffff
                                  ? -1 : attrs.buckets[i].minFreeBlocks;

            /* Add the element to the list. */
            view.elements.$add(elem);
        }
    }
    catch (e) {
        throw("Error: could not access shared memory: " + e);
    }
}
