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
 *  ======== HeapMemMP.xs ========
 *
 */

var HeapMemMP       = null;
var SharedRegion    = null;
var NameServer      = null;
var Ipc             = null;
var Cache           = null;
var GateMP          = null;

var instCount = 0;  /* use to determine if processing last instance */

/*
 *  ======== module$use ========
 *  Initialize module values.
 */
function module$use(mod, params)
{
    HeapMemMP       = this;
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

    /* initialize the NameServer param to be used now or later */
    HeapMemMP.nameSrvPrms.maxRuntimeEntries = params.maxRuntimeEntries;
    HeapMemMP.nameSrvPrms.tableSection      = params.tableSection;
    HeapMemMP.nameSrvPrms.maxNameLen        = params.maxNameLen;

    /*
     *  Get the current number of created static instances of this module.
     *  Note: if user creates a static instance after this point and
     *        expects to use NameServer, this is a problem.
     */
    var instCount = this.$instances.length;

    /* create NameServer here only if no static instances are created */
    if (instCount == 0) {
        mod.nameServer = NameServer.create("HeapMemMP",
                                            HeapMemMP.nameSrvPrms);
    }
}

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    var SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');
    var Ipc             = xdc.useModule('ti.sdo.ipc.Ipc');

    view.name = NameServer.getName$view("HeapMemMP",
        SharedRegion.getSRPtrMeta$view(obj.attrs));

    view.buf = $addr(obj.buf);
    view.totalSize = "0x" + obj.bufSize.toString(16);

    view.objType = Ipc.getObjTypeStr$view(obj.objType);
    if (view.objType == null) {
        Program.displayError(view, "objType",
            "Corrupted state: The value of 'objType' is not " +
            "one of known types");
    }

    view.gate = obj.gate;
}

/*
 *  ======== viewInitDetailed ========
 *  Initialize the 'Detailed' HeapMemMP instance view.
 */
function viewInitDetailed(view, obj)
{
    var HeapMemMP       = xdc.useModule('ti.sdo.ipc.heaps.HeapMemMP');
    var SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');

    // first get the Basic view:
    viewInitBasic(view, obj);

    /* view.attrs */
    view.attrs = "0x" + Number(obj.attrs.$addr).toString(16);

    /* view.cacheEnabled */
    view.cacheEnabled = obj.cacheEnabled;

    /* view.totalFreeSize */

    var totalFreeSize = 0;
    var largestFreeSize = 0;

    /* get the free list head; it should always exist even if list is empty */
    var currElem;
    var attrs;

    try {
        attrs = Program.fetchStruct(HeapMemMP.Attrs$fetchDesc,
                                    obj.attrs.$addr, false);

        currElem = Program.fetchStruct(HeapMemMP.Header$fetchDesc,
                                       attrs.head.$addr, false);
    }
    catch (e) {
        view.$status["totalFreeSize"] =
                "Error: could not access head element of free list: " + e;

        throw (e);
    }

    /*
     * Traverse free list and add up all of the sizes.  This loop condition
     * ensures that we don't try to access a null element (i.e. it avoids trav-
     * ersing past the header on an empty list and it ends once the end of a non
     * empty list is reached).
     */
    while (currElem.next != SharedRegion.getSRPtrMeta$view(0)) {
        // Fetch the next free block (next linked list element)
        try {
            var currElem = Program.fetchStruct(
                    HeapMemMP.Header$fetchDesc,
                    SharedRegion.getPtrMeta$view(currElem.next),
                    false);
        }
        catch (e) {
            view.$status["totalFreeSize"] = "Error: could not access" +
                    " next element linked list: " + e;
            throw (e);
        }

        // add up the total free space
        totalFreeSize += currElem.size;

        // check for a new max free size
        if (currElem.size > largestFreeSize) {
            largestFreeSize = currElem.size;
        }
    }

    view.totalFreeSize = "0x" + Number(totalFreeSize).toString(16);
    view.largestFreeSize = "0x" + Number(largestFreeSize).toString(16);

    if (totalFreeSize > obj.bufSize) {
        view.$status["totalFreeSize"] = "Error: totalFreeSize (" +
                view.totalFreeSize + ") > totalSize (" + view.totalSize +
                ")!";
    }

    if (totalFreeSize < 0) {
        view.$status["totalFreeSize"] = "Error: totalFreeSize (" +
                view.totalFreeSize + ") is negative!";
    }

    if (largestFreeSize > obj.bufSize) {
        view.$status["largestFreeSize"] = "Error: largestFreeSize (" +
                view.largestFreeSize + ") > totalSize (" + view.totalSize +
                ")!";
    }

    if (largestFreeSize < 0) {
        view.$status["largestFreeSize"] = "Error: largestFreeSize (" +
                view.largestFreeSize + ") is negative!";
    }
}

/*
 *  ======== viewInitData ========
 */
function viewInitData(view, obj)
{
    var NameServer = xdc.useModule('ti.sdo.utils.NameServer');

    view.label = Program.getShortName(obj.$label);
    if (view.label == "") {
        // split the label to rid of the long full package name that precedes
        // format will be: "HeapMemMP@0x12345678"
        var splitStr = String(obj.$label).split(".");

        view.label = splitStr[splitStr.length - 1];
    }
    view.label += "-freeList";

    if (obj.attrs != 0) {
        view.elements = getFreeList(obj);
    }

    return(view);
}

/*
 *  ======== getFreeList ========
 */
function getFreeList(obj)
{
    var HeapMemMP       = xdc.useModule('ti.sdo.ipc.heaps.HeapMemMP');
    var SharedRegion    = xdc.useModule('ti.sdo.ipc.SharedRegion');

    try {
        var attrs = Program.fetchStruct(HeapMemMP.Attrs$fetchDesc,
                                        obj.attrs.$addr, false);
        var header = Program.fetchStruct(HeapMemMP.Header$fetchDesc,
                                         attrs.head.$addr, false);
    }
    catch (e) {
        print("Error: Caught exception from fetchStruct: " +
            e.toString());
        throw (e);
    }


    var freeList = new Array();

    /* For each block on the free list... */
    while (true) {
        /* Break if this is the last block */
        if (header.next == SharedRegion.getSRPtrMeta$view(0)) {
            break;
        }

        /* Fetch the next block */
        try {
            var header = Program.fetchStruct(
                    HeapMemMP.Header$fetchDesc,
                    SharedRegion.getPtrMeta$view(header.next),
                    false);
        }
        catch (e) {
            print("Error: Caught exception from fetchStruct: " +
                e.toString());
            throw (e);
        }

        /* Add this block to the list */
        var memBlock = Program.newViewStruct('ti.sdo.ipc.heaps.HeapMemMP',
                                             'FreeList');
        memBlock.size = "0x" + Number(header.size).toString(16);
        memBlock.address = "0x" + Number(header.$addr).toString(16);

        freeList[freeList.length] = memBlock;
    }

    return (freeList);
}
