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
 *  ======== List.xs ========
 */

var List = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    List = this;

    /* to minimize object size */
    List.common$.namedInstance = false;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    Hwi = xdc.useModule("ti.sysbios.hal.Hwi");
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, params)
{
    obj.elem.next = obj.elem.prev = obj.elem;

    /* Add all the elem that we placed on the metaList */
    for (var i = 0; i < params.metaList.length; i++) {
         this.putMeta(params.metaList[i]);
    }
}

/*
 *  ======== elemClearMeta ========
 */
function elemClearMeta(elem)
{
    elem.next = elem.prev = elem;
}

/*
 *  ======== putMeta ========
 */
function putMeta(elem)
{
    var obj = this.$object;

    /* If the static$init has not been called, add to metaList*/
    if (obj.elem.prev === undefined) {
        this.metaList.$add(elem);
    }
    else {
       /* Add directly into the object */
       elem.next = obj.elem;
       elem.prev = obj.elem.prev;
       obj.elem.prev.next = elem;
       obj.elem.prev = elem;
    }
}

/*
 *  ======== module$validate ========
 */
function module$validate()
{
    if (List.common$.namedInstance == true) {
        List.$logError("The List module does not support namedInstances.",
        List.common$, List.common$.namedInstance);
    }
}

/*
 *  ======== viewInitInstance ========
 */
function viewInitInstance(view, obj)
{
    var List = xdc.useModule('ti.sdo.utils.List');
    var Program = xdc.useModule('xdc.rov.Program');

    view.label = Program.getShortName(obj.$label);

    /*
     * To check for loops, store each address as a key in a map,
     * then with each new address check first if it is already in
     * the map.
     */
    var addrs = {};

    var e = obj.elem;
    while (Number(e.next) != Number(obj.$addr)) {

        /* Before fetching the next element, verify we're not in a loop. */
        if (e.next in addrs) {
            view.$status["elems"] = "List contains loop. Element " + e.$addr + " points to element " + e.next;
            break;
        }

        /* Fetch the next element and add it to the array of elements. */
        e = Program.fetchStruct(List.Elem$fetchDesc, e.next);
        view.elems.$add(e.$addr);

        /*
         * Add the address to a map so we can check for loops.
         * The value 'true' is just a placeholder to make sure the address
         * is in the map.
         */
        addrs[e.$addr] = true;
    }
}
