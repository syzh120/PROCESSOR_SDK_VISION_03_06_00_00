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
 *  ======== MultiProc.xs ========
 *
 */
var MultiProc = null;
var BaseIdOfCluster = null;
var NumProcessors = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    MultiProc = this;

    if (((BaseIdOfCluster != MultiProc.baseIdOfCluster) &&
        (BaseIdOfCluster != null)) ||
        ((NumProcessors != MultiProc.numProcessors) &&
        (NumProcessors != null))) {
        MultiProc.$logError("MultiProc.numProcessors and " +
                            "MultiProc.baseIdOfCluster must be " +
                            "set before MultiProc.setConfig()", this);
    }

    /* Make sure the name list is not too long... */
    if (MultiProc.nameList.length > MultiProc.numProcsInCluster) {
        MultiProc.$logError("The name list is too long. numProcessors = " +
                            MultiProc.numProcsInCluster, this);
    }
    else if (MultiProc.nameList.length < MultiProc.numProcsInCluster) {
        /* If too short, fill in with nulls */
        var len = MultiProc.nameList.length;
        MultiProc.nameList.length = MultiProc.numProcsInCluster;
        for (var i = len; i < MultiProc.numProcsInCluster; i++) {
            MultiProc.nameList[i] = null;
        }
    }

    /*
     *  Make sure the id is ok (e.g. not equal to or greater than numProcessors)
     *  If it is INVALID (e.g. set at runtime) do not do the check.
     */
    if ((MultiProc.id != MultiProc.INVALIDID) &&
        (MultiProc.id >= MultiProc.numProcessors)) {

        MultiProc.$logError("The processor id (" + MultiProc.id +
            ") is larger than numProcessors (" + MultiProc.numProcessors +
            ")", this);
    }
}

/*
 *  ======== setConfig ========
 */
function setConfig(name, nameList)
{
    var Settings = xdc.module('ti.sdo.ipc.family.Settings');
    MultiProc = this;

    MultiProc.nameList          = nameList;
    MultiProc.id                = MultiProc.INVALIDID;

    /* set/check numProcsInCluster */
    if (!(MultiProc.$written("numProcsInCluster"))) {
        /*
         *  If numProcsInCluster is not set, then set it to the
         *  length of the nameList.
         */
        MultiProc.numProcsInCluster = nameList.length;
    }

    /* set/check numProcessors */
    if (!(MultiProc.$written("baseIdOfCluster"))) {
        if (!(MultiProc.$written("numProcessors"))) {
            /*
             *  If baseIdOfCluster is not set and numProcessors is not set
             *  then set numProcessors to numProcsInCluster
             */
            MultiProc.numProcessors = MultiProc.numProcsInCluster;
        }
    }
    else {
        if (!(MultiProc.$written("numProcessors"))) {
            /*
             *  If baseIdOfCluster is set and numProcessors is not set
             *  then throw error because numProcessors needs to be set
             */
            MultiProc.$logError("MultiProc.numProcessors needs to be set" +
                " before calling MultiProc.setConfig()", this);
        }
    }

    /* BaseIdOfCluster and NumProcessors must not change after this point */
    NumProcessors = MultiProc.numProcessors;
    BaseIdOfCluster = MultiProc.baseIdOfCluster;

    if (nameList.length == 0) {
        /* Empty name array supplied */
        MultiProc.$logError("'nameList' cannot be empty", this);
    }
    else {
        /* Check for duplicate names in nameList */
        var temp = [];
        for each (procName in nameList) {
            if (temp[procName] != null) {
                MultiProc.$logError("nameList has a duplicate name: " +
                        procName, this);
            }
            temp[procName] = 1;
        }
    }

    /*
     *  Check for valid nameList names.  I.e. if building on DM6446, the only
     *  possible names in nameList are "HOST" and "DSP".
     */
    if (MultiProc.numProcsInCluster > 1) {
        for each (var tempName in MultiProc.nameList) {
            if (tempName != null && !Settings.procInDevice(tempName)) {
                MultiProc.$logError("The MultiProc name (" + tempName +
                    ") does not match any of the following possible names on the"
                    + " device (" + Program.cpu.deviceName + "): " +
                    Settings.getDeviceProcNames().join(", "),
                    this);
            }
        }
    }

    /* If name is not null, set the id here otherwise set it at runtime */
    if (name != null) {
        /* Set MultiProc.id from the name */
        var id = this.getIdMeta(name);

        if (id == MultiProc.INVALIDID) {
            /* convert XDC array into js array for easy printing */
            var nameListArray = new Array();

            for (var k in MultiProc.nameList) {
                nameListArray.push(MultiProc.nameList[k]);
            }

            MultiProc.$logError("The processor name (" + name +
                ") is not contained within the following configured names: '" +
                nameListArray.join(", ") + "'", this);
        }

        /* only get here if id is valid */
        MultiProc.id = id + MultiProc.baseIdOfCluster;
    }
    else if (MultiProc.numProcsInCluster == 1) {
        /* There is only 1 processor so set id to the base of cluster */
        MultiProc.id = MultiProc.baseIdOfCluster;
    }
}

/*
 *  ======== getDeviceProcNames ========
 */
function getDeviceProcNames()
{
    var Settings = xdc.module('ti.sdo.ipc.family.Settings');

    return (Settings.getDeviceProcNames());
}

/*
 *  ======== getIdMeta ========
 */
function getIdMeta(name)
{
    MultiProc = this;

    var id = MultiProc.INVALIDID;

    if (name != null) {
        for (var i in MultiProc.nameList) {
            if (MultiProc.nameList[i] == name) {
                id = Number(i);
            }
        }
    }
    else {
        /* Get our 'own' MultiProc id */
        id = MultiProc.id;
    }

    return (id);
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(state, mod)
{
    state.id = mod.id;
    state.baseIdOfCluster = mod.baseIdOfCluster;

    /* now that we know how big the cluster is, set the size of the array */
    state.clusterProcList.length = mod.numProcsInCluster;

    /* initialize the array if we know the actual procIds */
    for (var i = 0; i < state.clusterProcList.length; i++) {
        state.clusterProcList[i] =
                (mod.baseIdOfCluster != MultiProc.INVALIDID) ?
                mod.baseIdOfCluster + i : MultiProc.INVALIDID;
    }
}

/*
 *  ======== getName$view ========
 *  ROV helper function that returns a processor name given its id
 */
function getName$view(id)
{
    var name;

    /*
     * Scan in the MultiProc view so we have the mapping from processor id
     * to processor name.
     */
    try {
        var multiProcView = Program.scanModuleView('ti.sdo.utils.MultiProc',
                                                   'Module');
    }
    catch (e) {
        /*
         * If there was a problem scanning the MultiProc view, throw an error
         */
        throw("Error scanning MultiProc module view: " + String(e));
    }

    /* Check whether id is valid; throw an error if not */
    if (id > multiProcView.numProcessors) {
        throw("Invalid MultiProc id: " + id);
    }

    /* Since nameList is ordered by id, we can directly index the array */
    name = multiProcView.nameList[id];

    return (name);
}

/*
 *  ======== self$view ========
 *  ROV helper function that returns the local MultiProc id
 */
function self$view()
{
    /* Retrieve the module state. */
    var rawView = Program.scanRawView('ti.sdo.utils.MultiProc');
    var mod = rawView.modState;

    return (mod.id);
}

/*
 *  ======== viewInitModule ========
 *  Display the module properties in ROV
 */
function viewInitModule(view, mod)
{
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    var Program = xdc.useModule('xdc.rov.Program');
    var multiprocModConfig =  Program.getModuleConfig(MultiProc.$name);

    view.id            = mod.id;
    view.numProcessors = multiprocModConfig.numProcsInCluster;

    /* Drop-down of the names */
    view.nameList.length = multiprocModConfig.nameList.length
    for (var i =0; i < multiprocModConfig.nameList.length; i++) {
        if (multiprocModConfig.nameList[i] != null)  {
            view.nameList[i] = multiprocModConfig.nameList[i];
        }
        else {
            view.nameList[i] = "[unnamed]";
        }
    }
}
