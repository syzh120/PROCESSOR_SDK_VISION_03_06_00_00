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
 *  ======== NameServer.xs ========
 *
 */

var NameServer = null;
var GateSwi    = null;
var Memory     = null;
var List       = null;
var MultiProc  = null;
var Settings   = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    NameServer = this;
    NameServer.common$.namedInstance = false;

    /*
     *  Plug in the Remote Proxy 'NameServerRemoteNull' by default.
     *  Ipc will plug in the real Remote Proxy when its used.
     */
    NameServer.SetupProxy = xdc.useModule('ti.sdo.utils.NameServerRemoteNull');
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    GateSwi    = xdc.useModule("ti.sysbios.gates.GateSwi");
    Hwi        = xdc.useModule("ti.sysbios.hal.Hwi");
    Memory     = xdc.useModule("xdc.runtime.Memory");
    List       = xdc.useModule("ti.sdo.utils.List");
    MultiProc  = xdc.useModule("ti.sdo.utils.MultiProc");
    Settings   = xdc.useModule('ti.sdo.ipc.family.Settings');
}

/*
 * ======== module$static$init ========
 */
function module$static$init(state, mod)
{
    /* This will result is some code reduction if building whole_program. */
    if (MultiProc.numProcessors == 1) {
        NameServer.singleProcessor = true;
    }
    else {
        NameServer.singleProcessor = false;
    }

    if (MultiProc.procAddrMode == MultiProc.ProcAddrMode_Global) {
        /* global address mode: NameServerRemote instance for every processor */
        state.nsRemoteHandle.length = MultiProc.numProcessors;
    }
    else if (MultiProc.procAddrMode == MultiProc.ProcAddrMode_Cluster) {
        /* cluster address mode: need instance only for cluster members */
        state.nsRemoteHandle.length = MultiProc.numProcsInCluster;
    }
    else {
        NameServer.$logError("Unknown MultiProc.procAddrMode", this);
    }

    for (var i = 0; i < state.nsRemoteHandle.length; i++) {
        state.nsRemoteHandle[i] = null;
    }

    /* Gate for all NameServer critical regions */
    state.gate = GateSwi.create();
}

/*
 *  ======== instance$static$init ========
 *  Initialize instance values.
 */
function instance$static$init(obj, name, params)
{
    var index;
    var numModTable = 0;
    var numStatic = params.metaTable.length;

    if (NameServer.metaModTable[name]) {
        numModTable = NameServer.metaModTable[name].length;
        var numStatic = params.metaTable.length + numModTable;
    }

    /* Fill in the object */
    obj.name          = name;
    obj.maxNameLen    = params.maxNameLen;
    obj.numDynamic    = params.maxRuntimeEntries;
    obj.checkExisting = params.checkExisting;
    obj.numStatic     = numStatic;
    obj.refCount      = 1;
    obj.table.length  = numStatic;
    if (params.tableHeap == null) {
        obj.tableHeap     = NameServer.common$.instanceHeap;
    }
    else {
        obj.tableHeap     = params.tableHeap;
    }

    /* Make sure the minumim size is UInt32 */
    var target  = Program.build.target;
    if (params.maxValueLen < target.stdTypes["t_Int32"].size) {
        obj.maxValueLen  = target.stdTypes["t_Int32"].size;
    }
    else {
        obj.maxValueLen  = params.maxValueLen;
    }

    List.construct(obj.nameList);
    List.construct(obj.freeList);

    /* Move the metaTable into the object. */
    for (index = 0; index < params.metaTable.length; index++) {
        /* Make sure the name and value are not too long */
        if (this.metaTable[index].len > obj.maxValueLen) {
            NameServer.$logError("Value length "
                                 + this.metaTable[index].len
                                 + " is larger than maxValueLen value of "
                                 + obj.maxValueLen, this);
        }
        if (this.metaTable[index].name.length > obj.maxNameLen) {
            NameServer.$logError("Name length is of " +
                                 this.metaTable[index].name.length +
                                 " is larger than maxNameLen value of " +
                                 obj.maxNameLen, this);
        }

        obj.table[index].name  = this.metaTable[index].name;
        obj.table[index].len   = this.metaTable[index].len;
        obj.table[index].value = this.metaTable[index].value;
        obj.nameList.putMeta(obj.table[index].elem);
    }

    /* Move the metaModTable into the object. */
    for (var k = 0; k < numModTable; k++) {
        /* Make sure the name and value are no too long */
        if (NameServer.metaModTable[name][k].len > obj.maxValueLen) {
            NameServer.$logError("Value length is of "
                                 + NameServer.metaModTable[name][k].len
                                 + " is larger than maxValueLen value of "
                                 + obj.maxValueLen, this);
        }
        if (NameServer.metaModTable[name][k].name.length > obj.maxNameLen) {
            NameServer.$logError("Name length is of " +
                            + NameServer.metaModTable[name][k].name.length
                            + " is larger than maxNameLen value of "
                            + obj.maxNameLen, this);
        }

        obj.table[index].name  = NameServer.metaModTable[name][k].name;
        obj.table[index].len   = NameServer.metaModTable[name][k].len;
        obj.table[index].value = NameServer.metaModTable[name][k].value;
        obj.nameList.putMeta(obj.table[index].elem);
        index++;
    }

    this.metaTable.$seal();

    /* Handle the creation of the runtime entries */
    if ((obj.numDynamic != 0) && (obj.numDynamic != NameServer.ALLOWGROWTH)) {
        /* Create the table and place it */
        obj.table.length += params.maxRuntimeEntries;

        /*
         *  Create the block that will contain a copy of the names and
         *  place it.
         */
        obj.names.length  = params.maxRuntimeEntries * params.maxNameLen;
        Memory.staticPlace(obj.names,  0, params.tableSection);

        /*
         *  Create the block that will contain a copy of the values and
         *  place it.
         *  If the values are small, simply use the values UArg to store
         *  the UInt32. Thus no need for the block of memory.
         */
        if (params.maxValueLen == target.stdTypes["t_Int32"].size) {
            obj.values.length = 0;
        }
        else {
            obj.values.length = params.maxRuntimeEntries * params.maxValueLen;
            Memory.staticPlace(obj.values, 0, params.tableSection);
        }

        /*
         *  Need to fill in all values, else we get an undefined
         *  The majority of the work in done in the Module_startup.
         */
        for (var j = numStatic; j < obj.table.length; j++) {
            obj.table[j].name  = null;
            obj.table[j].len   = 0;
            obj.table[j].value = 0;
            obj.freeList.putMeta(obj.table[j].elem);
        }
    }
    Memory.staticPlace(obj.table,  0, params.tableSection);
}

/*
 *  ======== addUInt32Meta ========
 */
function addUInt32Meta(name, value)
{
    var target  = Program.build.target;
    this.addMeta(name, value, target.stdTypes["t_Int32"].size);
}

/*
 *  ======== modAddMeta ========
 */
function modAddMeta(instName, name, value, len)
{
    /* Check to see if NameServer instance already exists */
    if (!NameServer.metaModTable[instName]) {
        NameServer.metaModTable[instName] = new NameServer.EntryMap();
        var instLen = 0;
    }
    else {
        var instLen = NameServer.metaModTable[instName].length;

        /* Make sure the name does not already exist. */
        for (var i = 0; i < instLen; i++) {
            if (name == NameServer.metaModTable[instName][i].name) {
                NameServer.$logError("Cannot add \"" + name +
                                 "\". It already exists.", NameServer);
            }
        }
    }
    NameServer.metaModTable[instName].length++;

    /* Add it into this table */
    NameServer.metaModTable[instName][instLen].name = name;
    NameServer.metaModTable[instName][instLen].len = len;
    NameServer.metaModTable[instName][instLen].value = value;

}

/*
 *  ======== addMeta ========
 */
function addMeta(name, value, len)
{
    if (this.metaTable.$sealed() == true) {
        NameServer.$logError("Cannot add into the NameServer during " +
                             "this phase (" + xdc.om.$$phase + ")" , this);
    }

    NameServer = xdc.module('ti.sdo.utils.NameServer');

    /* Make sure the name does not already exist. */
    for (var i = 0; i < this.metaTable.length; i++) {
        if (name == this.metaTable[i].name) {
            NameServer.$logError("Cannot add \"" + name +
                                 "\". It already exists.", this);
        }
    }

    var entry = new NameServer.Entry();

    entry.name  = name;
    entry.len   = len;
    entry.value = value;

    /* Add it into this table */
    this.metaTable.$add(entry);
}

/*
 *  ======== getMeta ========
 *  Return the entry
 */
function getMeta(name, value)
{
    for (var i = 0; i < this.metaTable.length; i++) {
        if (this.metaTable[i].name == name) {
            return (this.metaTable[i])
        }
    }
}

/*
 *  ======== viewInitBasic ========
 *  Processes the 'Basic' view for a NameServer instance.
 */
function viewInitBasic(view, obj)
{
    var NameServer = xdc.useModule('ti.sdo.utils.NameServer');
    var Program = xdc.useModule('xdc.rov.Program');

    view.name = Program.fetchString(obj.name);
    view.checkExisting = obj.checkExisting;
    view.maxNameLen    = obj.maxNameLen;
    view.maxValueLen   = obj.maxValueLen;
    view.numStatic     = obj.numStatic;
    if (obj.numDynamic == 0xffffffff) {
        view.numDynamic = "ALLOWGROWTH";
    }
    else {
        view.numDynamic = "0x" + Number(obj.numDynamic).toString(16);
    }
}

/*
 *  ======== viewInitData ========
 *  Processes the 'NamesValues' view for a NameServer instance.
 */
function viewInitData(view, obj)
{
    /* Retrieve the instance name. */
    view.label = Program.fetchString(obj.name);
    view.elements = getNameList(obj);
    return(view);
}

/*
 *  ======== getNameList ========
 */
function getNameList(obj)
{
    var NameServer      = xdc.useModule('ti.sdo.utils.NameServer');
    var List            = xdc.useModule('ti.sdo.utils.List');
    var Program         = xdc.useModule('xdc.rov.Program');

    var nameList = new Array();

    /* List Object is the head */
    var head = obj.nameList.elem;

    /* Get the first entry on the List */
    try {
        // elem is the current element
        var elem = Program.fetchStruct(List.Elem$fetchDesc, head.next);
    }
    catch (error) {
        view.$status["freeList"] = "Error fetching List Elem struct: " + error.toString(); // TODO freeList -> ?
        throw (error);
    }

    /*
     * Maintain a map of the entries by their address to
     * support 'getEntryByKey'.
     */
    var data = Program.getPrivateData('ti.sdo.utils.NameServer');
    if (data.entryMap == undefined) {
        data.entryMap = {};
    }

    /* While the entry is not the head */
    while (Number(elem.$addr) != Number(head.$addr)) {
        /* Fetch the next block */
        try {
            var nameEntry = Program.fetchStruct(NameServer.TableEntry$fetchDesc,
                elem.$addr);
        }
        catch (elem) {
            print("Error: Caught exception from fetchStruct: " +
                elem.toString());
            throw (elem);
        }

        /* Add this block to the list */
        var entry = Program.newViewStruct('ti.sdo.utils.NameServer',
            'NamesValues');
        entry.name = Program.fetchString(nameEntry.name);

        var int32len = Program.build.target.stdTypes["t_Int32"].size;
        if (obj.maxValueLen > int32len) {
            entry.value = "[large value]";
        }
        else {
            entry.value = "0x" + Number(nameEntry.value).toString(16);
        }
        entry.len = nameEntry.len;
        entry.nsKey = nameEntry.elem.$addr;

        /* Add the entry to the view. */
        nameList[nameList.length] = entry;

        /* Add the view to the map. */
        data.entryMap[Number(elem.$addr)] = entry;

        elem = Program.fetchStruct(List.Elem$fetchDesc, elem.next);
    }

    return (nameList);
}

/*
 *  ======== getNameByKey$view ========
 *  In ROV, returns a NameServer name given its key.
 *  Throws an exception if there is no entry at the given address.
 */
function getNameByKey$view(addr)
{
    var Program = xdc.useModule('xdc.rov.Program');

    /*
     *  Scan the instance view to retrieve all of the entries.
     *  This function may throw an exception, let it propogate to the caller.
     */
    Program.scanInstanceDataView('ti.sdo.utils.NameServer', 'NamesValues');

    /* Retrieve the private data. */
    var data = Program.getPrivateData('ti.sdo.utils.NameServer');

    /* Get the entry from the map. */
    var entry = data.entryMap[Number(addr)];

    /* Throw an exception if there's no entry at this address. */
    if (entry == undefined) {
        throw (new Error("There is no NameServer entry at the address: 0x" +
                         Number(addr).toString(16)));
    }

    var name = entry.name;

    return (name);
}

/*
 *  ======== getName$view ========
 *  Only used for ROV. Returns a name in a supplied 'tableName' corresponding
 *  to 'value'.
 */
function getName$view(tableName, value)
{
    var name = null;

    try {
        var NamesValuesView = Program.scanInstanceDataView(
            'ti.sdo.utils.NameServer',
            'NamesValues');

        for (var i in NamesValuesView) {
            if (NamesValuesView[i].label == tableName) {
                elements = NamesValuesView[i].elements;
                for (var j in elements) {
                    if (elements[j].value == "0x" + value.toString(16)) {
                        /* elem found */
                        name = elements[j].name;
                    }
                }
            }
        }
    }
    catch(e) {
        var msg = "error when scaning NameServer instance data view: " + e;
        throw(msg);
    }

    return (name);
}
