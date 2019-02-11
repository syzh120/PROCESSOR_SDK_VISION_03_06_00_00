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
 *  ======== SharedRegion.xs ========
 *
 */

var GateMP       = null;
var HeapMemMP    = null;
var Ipc          = null;
var MultiProc    = null;
var SharedRegion = null;
var Cache        = null;

var staticInited = false;   /* set to true in  module$static$init */
var idArray = [];           /* for storing the id of an entry     */

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    SharedRegion = this;

    SharedRegion.entry.length = 0;
    SharedRegion.entryCount = 0;
    SharedRegion.numOffsetBits = 0;
    SharedRegion.$object.regions.length = 0;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    GateMP    = xdc.useModule("ti.sdo.ipc.GateMP");
    Ipc       = xdc.useModule("ti.sdo.ipc.Ipc");
    HeapMemMP = xdc.useModule("ti.sdo.ipc.heaps.HeapMemMP");
    MultiProc = xdc.useModule("ti.sdo.utils.MultiProc");
    Cache     = xdc.useModule("ti.sysbios.hal.Cache");

    /* in a single processor system, we should never translate */
    if (MultiProc.numProcessors == 1) {
        SharedRegion.translate = false;
    }

    if (SharedRegion.translate == false) {
        SharedRegion.INVALIDSRPTR = 0x0;
    }
}

/*
 *  ======== module$static$init ========
 *  Initialize module values.
 */
function module$static$init(mod, params)
{
    var Memory    = xdc.module('xdc.runtime.Memory');
    var regions   = SharedRegion.$object.regions;

    staticInited = true;

    /* allocate the number of entries in the table and intialize it */
    regions.length   = params.numEntries;

    for (var i = 0; i < params.numEntries; i++) {
        regions[i].entry.base          = $addr(0);
        regions[i].entry.len           = 0;
        regions[i].entry.ownerProcId   = 0;
        regions[i].entry.isValid       = false;
        regions[i].entry.cacheEnable   = true;
        regions[i].entry.cacheLineSize = params.cacheLineSize;
        regions[i].entry.createHeap    = true;
        regions[i].reservedSize        = 0;
        regions[i].heap                = null;
        regions[i].entry.name          = String(null);
    }

    /* set the length of the genSectionInLinkCmd[] */
    SharedRegion.genSectionInLinkCmd.length   = params.numEntries;

    /* default the generate output section to be true for all shared regions */
    for (var i = 0; i < SharedRegion.genSectionInLinkCmd.length; i++) {
        SharedRegion.genSectionInLinkCmd[i] = true;
    }

    SharedRegion.numOffsetBits = getNumOffsetBits();
    SharedRegion.offsetMask = (1 << SharedRegion.numOffsetBits) - 1;

    /*
     *  Add entry to lookup table for all segments added by 'addEntry'. Each
     *  entry's info was temporarily stored into SharedRegion.entry[].
     *  where 'i' is equivalent to the number of entries.
     */
    for (var i = 0; i < SharedRegion.entry.length; i++) {
        var entry = SharedRegion.entry[i];

        /* make sure id is smaller than numEntries */
        if (idArray[i] >= params.numEntries) {
            SharedRegion.$logError("Id: " + idArray[i] + " " +
                "is greater than or equal to numEntries.", SharedRegion);
        }

        if (idArray[i] != SharedRegion.INVALIDREGIONID) {
            regions[idArray[i]].entry.base          = entry.base;
            regions[idArray[i]].entry.len           = entry.len;
            regions[idArray[i]].entry.ownerProcId   = entry.ownerProcId;
            regions[idArray[i]].entry.isValid       = entry.isValid;
            regions[idArray[i]].entry.cacheEnable   = entry.cacheEnable;
            regions[idArray[i]].entry.cacheLineSize = entry.cacheLineSize;
            regions[idArray[i]].entry.createHeap    = entry.createHeap;
            regions[idArray[i]].entry.name          = entry.name;
        }
    }
}

/*
 *  ======== setEntryMeta ========
 *  Adds a memory region to the lookup table.
 *  Function places entries in temporary storage and process this structure
 *  at the end of module$static$init() because the number of entries
 *  cannot be initialize until after user's configuration is executed.
 */
function setEntryMeta(id, entry)
{
    var num = SharedRegion.entryCount;

    SharedRegion.entryCount++;
    idArray.length++;
    SharedRegion.entry.length = SharedRegion.entryCount;

    /* Initialize new table entry for all processors. */
    SharedRegion.entry[num].base          = $addr(0);
    SharedRegion.entry[num].len           = 0;
    SharedRegion.entry[num].ownerProcId   = 0;
    SharedRegion.entry[num].isValid       = false;
    SharedRegion.entry[num].cacheEnable   = true;
    SharedRegion.entry[num].cacheLineSize = SharedRegion.cacheLineSize;
    SharedRegion.entry[num].createHeap    = true;
    SharedRegion.entry[num].name          = String(null);

    /* check to see region does not overlap */
    checkOverlap(entry);

    /* squirrel away entry information to be processed in module$static$init */
    idArray[num]                          = id;
    SharedRegion.entry[num].base          = $addr(entry.base);
    SharedRegion.entry[num].len           = entry.len;

    /* set 'ownerProcId' if defined otherwise no default owner */
    if (entry.ownerProcId != undefined) {
        SharedRegion.entry[num].ownerProcId   = entry.ownerProcId;
    }

    /* set 'name' field if defined otherwise name is null */
    if (entry.name != undefined) {
        SharedRegion.entry[num].name = entry.name;
    }

    /* set 'isValid' field if defined otherwise its false */
    if (entry.isValid != undefined) {
        SharedRegion.entry[num].isValid = entry.isValid;
    }

    /* set the 'cacheEnable' field if defined otherwise is true */
    if (entry.cacheEnable != undefined) {
        SharedRegion.entry[num].cacheEnable = entry.cacheEnable;
    }

    /* set the 'createHeap' field if defined otherwise use default */
    if (entry.createHeap != undefined) {
        SharedRegion.entry[num].createHeap = entry.createHeap;
    }

    /* set the 'cacheLineSize' field if defined otherwise its the default */
    if (entry.cacheLineSize != undefined) {
        /* Error if cacheEnable but cacheLineSize set to 0 */
        if (SharedRegion.entry[num].cacheEnable && (entry.cacheLineSize == 0)) {
            SharedRegion.$logError("cacheEnable is set to true for " +
                "region: " + id + " cacheLineSize it set to 0.", SharedRegion);
        }
        else {
            SharedRegion.entry[num].cacheLineSize = entry.cacheLineSize;
        }
    }

    /*
     *  The cacheLineSize is used for alignment of an address as well as
     *  padding of shared structures therefore it cannot be 0.
     *  This value must be the same across different processors in the system.
     *  Initially it was thought this would be the size of a Ptr (4), but the
     *  max default alignment is the size of a Long or Double (8) on C64P
     *  target therefore the minimum cacheLineSize must be 8.
     */
    if (SharedRegion.entry[num].cacheLineSize == 0) {
        var target  = Program.build.target;
        SharedRegion.entry[num].cacheLineSize = 8;
    }

    if (entry.base % SharedRegion.entry[num].cacheLineSize != 0) {
        /* Error if base address not aligned to cache boundary */
        SharedRegion.$logError("Base Address of 0x" +
            Number(entry.base).toString(16) +
            " is not aligned to cache boundary (" +
            SharedRegion.entry[num].cacheLineSize + ")", SharedRegion);
    }
}

/*
 *  ======== genSectionInCmd ========
 *  Depending on what 'gen' is, it will either generate or not
 *  generate an output section for the given shared region with 'id'.
 */
function genSectionInCmd(id, gen)
{
    /* make sure id is smaller than numEntries */
    if (id >= SharedRegion.numEntries) {
        SharedRegion.$logError("Id: " + id + " " +
            "is greater than or equal to numEntries.", SharedRegion);
    }

    SharedRegion.genSectionInLinkCmd[id] = gen;
}

/*
 *  ======== getPtrMeta ========
 *  Get the pointer given the SRPtr.
 */
function getPtrMeta(srptr)
{
    var returnPtr = 0;
    var offsetBits = getNumOffsetBits();
    var base;
    var entry;
    var foundBase = false;

    if (staticInited && (SharedRegion.translate == false)) {
        returnPtr = srptr;
    }
    else {
        entry = SharedRegion.entry;

        /* unsigned right shift by offsetBits to get id */
        var id = srptr >>> offsetBits;

        /* loop through entry table */
        for (var i = 0; i < entry.length; i++) {
            if ((entry[i].isValid == true) && (idArray[i] == id)) {
                base = entry[i].base;
                foundBase = true;
                break;
            }
        }

        /* a valid entry was found so get the ptr from srptr */
        if (foundBase) {
            returnPtr = (srptr & ((1 << offsetBits) - 1)) + base;
        }
    }

    return (returnPtr);
}

/*
 *  ======== getIdMeta ========
 *  Get the id given the addr
 */
function getIdMeta(addr)
{
    var entry;
    var id = SharedRegion.INVALIDREGIONID;

    if (staticInited && (SharedRegion.translate == false)) {
        id = 0;
    }
    else {
        entry = SharedRegion.entry;
        for (var i = 0; i < entry.length; i++) {
            if ((addr >= entry[i].base) &&
                (addr < (entry[i].base + entry[i].len))) {
                id = idArray[i];
                break;
            }
        }
    }

    return (id);
}

/*
 *  ======== getCacheLineSizeMeta ========
 */
function getCacheLineSizeMeta(id)
{
    /* make sure id is smaller than numEntries */
    if (id >= SharedRegion.numEntries) {
        SharedRegion.$logError("Id: " + id + " " +
            "is greater than or equal to numEntries.", SharedRegion);
    }

    return (cacheLineSize[id]);
}

/*
 *  ======== isCacheEnabledMeta ========
 *  Given the id return the 'cacheEnable' flag.
 *  function cannot be called from user's *.cfg file.
 */
function isCacheEnabledMeta(id)
{
    /* make sure id is smaller than numEntries */
    if (id >= SharedRegion.numEntries) {
        SharedRegion.$logError("Id: " + id + " " +
            "is greater than or equal to numEntries.", SharedRegion);
    }

    return (SharedRegion.entry[id].cacheEnable);
}

/*
 *  ======== checkOverlap ========
 *  Checks to make sure the memory region does not overlap with another region.
 *  This function is only called if MultiProc.id has been set to a valid id.
 */
function checkOverlap(memseg)
{
    var map  = SharedRegion.entry;

    for (var i = 0; i < map.length; i++) {
        if (memseg.base >= map[i].base) {
            if (memseg.base < (map[i].base + map[i].len)) {
                /* base of new region is within another region */
                SharedRegion.$logError("Segment: " + utils.toHex(memseg.base) +
                    " overlaps with: " + map[i].name, SharedRegion);
            }
        }
        else {
            if ((memseg.base + memseg.len) > map[i].base) {
                    /* part of region is within another region */
                SharedRegion.$logError("Segment: " + utils.toHex(memseg.base) +
                    " overlaps with: " + map[i].name, SharedRegion);
            }
        }
    }
}

/*
 *  ======== getNumOffsetBits ========
 *  Return the number of offsetBits bits
 */
function getNumOffsetBits()
{
    var numEntries = SharedRegion.numEntries;
    var indexBits = 0;
    var numOffsetBits;

    if (numEntries == 0) {
        indexBits = 0;
    }
    else if (numEntries == 1) {
        indexBits = 1;
    }
    else {
        numEntries = numEntries - 1;

        /* determine the number of bits for the index */
        while (numEntries) {
            indexBits++;
            numEntries = numEntries >> 1;
        }
    }

    numOffsetBits = 32 - indexBits;

    return (numOffsetBits);
}

/*
 *  ======== reserveNumBytes ========
 */
function reserveNumBytes(numBytes)
{
    SharedRegion.numBytesReserved = numBytes;
}

/*
 *  ======== viewInitRegions ========
 */
function viewInitRegions(view)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var SharedRegion = xdc.useModule('ti.sdo.ipc.SharedRegion');

    /* Scan the raw view in order to obtain the module state. */
    var rawView;
    try {
        rawView = Program.scanRawView('ti.sdo.ipc.SharedRegion');
    }
    catch (e) {
        var entryView = Program.newViewStruct('ti.sdo.ipc.SharedRegion',
                'Regions');
        Program.displayError(entryView, 'base',
            "Problem retrieving raw view: " + e);
        view.elements.$add(entryView);
        return;
    }

    var mod = rawView.modState;

    /* Retrieve the module configuration. */
    var modCfg = Program.getModuleConfig('ti.sdo.ipc.SharedRegion');

    /* Retrieve the table of entries. */
    try {
        var regions = Program.fetchArray(SharedRegion.Region$fetchDesc,
                                         mod.regions,
                                         modCfg.numEntries);
    }
    catch (e) {
        var entryView = Program.newViewStruct('ti.sdo.ipc.SharedRegion',
                'Regions');
        Program.displayError(entryView, 'base',
            "Caught exception while trying to retrieve regions table: " + e);
        view.elements.$add(entryView);
        return;
    }

    /* Display each of the regions. */
    for (var i = 0; i < regions.length; i++) {
        var entry = regions[i].entry;

        var entryView = Program.newViewStruct('ti.sdo.ipc.SharedRegion',
                                              'Regions');

        var base =  Number(entry.base);
        var len =  Number(entry.len);

        entryView.id = i;
        entryView.base = "0x" + Number(base).toString(16);
        entryView.len = "0x" + Number(len).toString(16);
        if (len == 0) {
            entryView.end = "0x" + Number(base + len).toString(16);
        }
        else {
            entryView.end = "0x" + Number(base + len - 1).toString(16);
        }
        entryView.ownerProcId = entry.ownerProcId;
        entryView.isValid = entry.isValid;
        entryView.cacheEnable = entry.cacheEnable;
        entryView.cacheLineSize = entry.cacheLineSize;
        entryView.reservedSize = regions[i].reservedSize;
        entryView.heap = regions[i].heap;
        try {
            entryView.name = Program.fetchString(Number(entry.name));
        }
        catch (e) {
            Program.displayError(entryView, 'name', "Problem retrieving name: " + e);
        }

        view.elements.$add(entryView);
    }
}

/*
 *  ======== getPtrMeta$view ========
 */
function getPtrMeta$view(srptr)
{
    var Program = xdc.useModule('xdc.rov.Program');

    /*
     * Retrieve the SharedRegion module configuration.
     * Store the configuration to the 'SharedRegion' global variable in this
     * file so that we can call the config-time API 'getNumOffsetBits'.
     */
    SharedRegion = Program.getModuleConfig('ti.sdo.ipc.SharedRegion');

    /* Ensure that srptr is a number */
    srptr = Number(srptr);

    /* If there's no translation to be done, just return the pointer. */
    if (SharedRegion.translate == false) {
        return (srptr);
    }

    /* If srptr is SharedRegion.INVALIDSRPTR then return NULL*/
    if (srptr == SharedRegion.INVALIDSRPTR) {
        return (0);
    }

    /*
     * Retrieve the 'Regions' view.
     * This view may throw an exception; let this exception propogate up and
     * be caught by the view calling this API.
     */
    var regionsView = Program.scanModuleDataView('ti.sdo.ipc.SharedRegion',
        'Regions');

    /* Get the regions from the view. */
    var regions = regionsView.elements;


    /* Retrieve the number of offset bits. */
    var numOffsetBits = getNumOffsetBits();

    /* unsigned right shift by offset to get id */
    var id = srptr >>> numOffsetBits;

    /* Verify the computed id is within range. */
    if (id > regions.length) {
        throw (new Error("The region id " + id + " of the SharedRegion " +
                         "pointer 0x" + Number(srptr).toString(16) + " is " +
                         "not a valid id."));
    }

    /* Retrieve the region. */
    var region = regions[id];

    /* Verify the region is valid. */
    if (!region.isValid) {
        throw (new Error("The SharedRegion " + id + " of the SharedRegion " +
                         "pointer 0x" + Number(srptr).toString(16) + " is " +
                         "currently invalid."));
    }

    /* Compute the local address. */
    var ptr = (srptr & ((1 << numOffsetBits) - 1)) + parseInt(region.base);

    return (ptr);
}

/*
 *  ======== getSRPtrMeta$view ========
 */
function getSRPtrMeta$view(addr)
{
    /*
     * Retrieve the SharedRegion module configuration.
     * Store the configuration to the 'SharedRegion' global variable in this
     * file so that we can call the config-time API 'getNumOffsetBits'.
     */
    SharedRegion = Program.getModuleConfig('ti.sdo.ipc.SharedRegion');

    /* Ensure the address is a number */
    addr = Number(addr);

    /* If there's no translation to be done, just return the pointer. */
    if (SharedRegion.translate == false) {
        return (addr);
    }

    /* If addr is NULL, return SharedRegion.INVALIDSRPTR */
    if (addr == 0) {
        return (SharedRegion.INVALIDSRPTR);
    }

    /*
     * Retrieve the 'Regions' view.
     * This view may throw an exception; let this exception propogate up and
     * be caught by the view calling this API.
     */
    var regionsView = Program.scanModuleDataView('ti.sdo.ipc.SharedRegion',
        'Regions');

    /* Get the regions from the view. */
    var regions = regionsView.elements;


    /* Retrieve the number of offset bits. */
    var numOffsetBits = getNumOffsetBits();

    /* Look through each of the regions for this address. */
    for (var i = 0; i < regions.length; i++) {

        /* Compute the beginning and end address of this region. */
        var begin = parseInt(regions[i].base);
        var end = parseInt(regions[i].end);

        /* If the address falls within this region... */
        if ((addr >= begin) && (addr < end)) {
            /* Compute the shared region address and return. */
            return ((i << numOffsetBits) + (addr - begin));
        }
    }

    /* If we didn't find a region containing the address, throw an error. */
    throw("No address range found for: " + Number(addr).toString(16));
}
