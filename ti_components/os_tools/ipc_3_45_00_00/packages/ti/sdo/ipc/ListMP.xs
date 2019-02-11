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
 *  ======== ListMP.xs ========
 *
 */

var Cache        = null;
var Ipc          = null;
var GateMP       = null;
var ListMP       = null;
var SharedRegion = null;
var MultiProc    = null;
var NameServer   = null;
var instCount = 0;      /* use to determine if processing last instance */

/*
 *  ======== module$use ========
 */
function module$use()
{
    ListMP = this;
    Ipc          = xdc.useModule('ti.sdo.ipc.Ipc');
    GateMP       = xdc.useModule('ti.sdo.ipc.GateMP');
    SharedRegion = xdc.useModule("ti.sdo.ipc.SharedRegion");
    MultiProc    = xdc.useModule("ti.sdo.utils.MultiProc");
    NameServer   = xdc.useModule("ti.sdo.utils.NameServer");
    Cache        = xdc.useModule("ti.sysbios.hal.Cache");

    ListMP.common$.fxntab = false;
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    mod.nameServer = null;
    ListMP.nameSrvPrms.maxRuntimeEntries = params.maxRuntimeEntries;
    ListMP.nameSrvPrms.maxNameLen        = params.maxNameLen;
    ListMP.nameSrvPrms.tableSection      = params.tableSection;

    /*
     *  Get the current number of created static instances of this module.
     *  Note: if user creates a static instance after this point and
     *        expects to use NameServer, this is a problem.
     */
    var instCount = this.$instances.length;

    /* create NameServer here only if no static instances are created */
    if (instCount == 0) {
        mod.nameServer = NameServer.create("ListMP", ListMP.nameSrvPrms);
    }
}

/*
 *  ======== viewInitBasic ========
 *  Processes the 'Basic' view for a ListMP instance.
 */
function viewInitBasic(view, obj)
{
    var NameServer = xdc.useModule('ti.sdo.utils.NameServer');
    var Ipc = xdc.useModule('ti.sdo.ipc.Ipc');
    var GateMP = xdc.useModule('ti.sdo.ipc.GateMP');

    /* Determine if the instance was given a name in the nameserver. */
    if (obj.nsKey != 0x0) {
        view.label = NameServer.getNameByKey$view(obj.nsKey);
    }
    /* Otherwise, leave the label empty. */
    else {
        view.label = "";
    }

    /* Get the instance's type (created, opened, etc.) */
    view.type = Ipc.getObjTypeStr$view(obj.objType);

    /* Display the handle to the instance's gate. */
    view.gate = String(obj.gate);
}

/*
 *  ======== viewInitLists ========
 *  Processes the 'Lists' view for a ListMP instance.
 *
 *  The 'Lists' view is a tree-type view (Instance Data) which displays the
 *  elements on the list. For each element, it displays an index and both the
 *  local and shared region address of the element.
 */
function viewInitLists(view, obj)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var SharedRegion = xdc.useModule('ti.sdo.ipc.SharedRegion');
    var ListMP = xdc.useModule('ti.sdo.ipc.ListMP');

    /* Label the list by its address. */
    view.label = String(obj.$addr);

    /* Retrieve the ListMP's Attrs struct. */
    var attrs;
    try {
        attrs = Program.fetchStruct(obj.attrs$fetchDesc, obj.attrs);
    }
    /* If there was a problem fetching the attrs struct, report it. */
    catch (e) {
        /* Create an element view to display the problem. */
        var elemView = Program.newViewStruct('ti.sdo.ipc.ListMP', 'Lists');
        Program.displayError(elemView, 'index',
                             "Problem retrieving the instance's Attrs " +
                             "struct: " + e);
        view.elements.$add(elemView);
        return;
    }

    /* Compute the address of the 'head' element within the attrs struct. */
    var hdrOffset = $om['ti.sdo.ipc.ListMP.Attrs'].$offsetof('head');
    var hdrAddr = Number(obj.attrs) + hdrOffset;

    /* Get the shared region address of the header. */
    try {
        var srHdrAddr = SharedRegion.getSRPtrMeta$view(hdrAddr);
    }
    /* If there was a problem, report it. */
    catch (e) {
        /* Create an element view to display the problem. */
        var elemView = Program.newViewStruct('ti.sdo.ipc.ListMP', 'Lists');
        Program.displayError(elemView, 'index',
                             "Problem retrieving SharedRegion address for " +
                             "the list's head: " + e);
        view.elements.$add(elemView);
        return;
    }

    /*
     * To check for loops, store each address as a key in a map,
     * then with each new address check first if it is already in
     * the map.
     */
    var srAddrs = {};

    /* Start at the head element. */
    var e = attrs.head;

    /* Loop through all of the elements until we're back at the head. */
    while (e.next != srHdrAddr) {

        /* Before fetching the next element, verify we're not in a loop. */
        if (e.next in srAddrs) {
            var lastElem = view.elements[view.elements.length - 1];
            Program.displayError(lastElem, 'addr', "List contains loop. " +
                                 "This element points to SharedRegion " +
                                 "address 0x" + Number(e.next).toString(16));
            break;
        }

        /* Create a view structure to represent the next element. */
        var elemView = Program.newViewStruct('ti.sdo.ipc.ListMP', 'Lists');

        /* Display the shared region address of the next element. */
        elemView.srPtr = "0x" + Number(e.next).toString(16);

        /*
         * Get the local address of the next element using the SharedRegion
         * module.
         */
        try {
            var nextAddr = SharedRegion.getPtrMeta$view(Number(e.next));
        }
        catch (e) {
            Program.displayError(elemView, 'addr', "Problem calculating " +
                                 "local address: " + addressString(e));
        }

        /* Display the local address of the next element. */
        elemView.addr = "0x" + Number(nextAddr).toString(16);

        /* Add the element to the view. */
        view.elements.$add(elemView);

        /*
         * Add the address to a map so we can check for loops.
         * The value 'true' is just a placeholder to make sure the address
         * is in the map.
         */
        srAddrs[e.next] = true;

        /* Fetch the next element (using its local address) */
        e = Program.fetchStruct(ListMP.Elem$fetchDesc, nextAddr);
    }
}
