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
 *  ======== MultiProc.xdc ========
 *
 */

import xdc.rov.ViewInfo;

import xdc.runtime.Assert;

/*!
 *  ======== MultiProc ========
 *  Processor Id Module Manager
 *
 *  Many IPC modules require identifying processors in a
 *  multi-processor environment. The MultiProc module centralizes
 *  processor id management into one module.  Since this configuration
 *  is almost always universally required, most IPC applications
 *  require supplying configuration of this module.
 *
 *  Each processor in the MultiProc module may be uniquely identified by
 *  either a name string or an integer ranging from 0 to MAXPROCESSORS - 1.
 *  Configuration is supplied using the {@link #setConfig} meta function,
 *  the {@link #numProcessors} and {@link #baseIdOfCluster}.
 *
 *  The setConfig function tells the MultiProc module:
 *  @p(blist)
 *      - The specific processor for which the application is being built
 *      - The number of processors in the cluster
 *  @p
 *
 *  A cluster is a set of processors within a system which share some share
 *  shared memory and supports notifications. Typically most systems contain
 *  one cluster.  When there are multiple clusters in the system, the
 *  {@link #numProcessors} and {@link #baseIdOfCluster} configuration
 *  paramaters are required to be set before calling {@link #setConfig}
 *
 *  For examle in a system with 2 C6678 devices [each C6678 contains 8
 *  homogeneuous cores].  For first C6678 device:
 *  @p(code)
 *  var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
 *  MultiProc.baseIdOfCluster = 0;
 *  MultiProc.numProcessors = 16;
 *  MultiProc.setConfig(null, ["CORE0", "CORE1", "CORE2", "CORE3",
 *                             "CORE4", "CORE5", "CORE6", "CORE7"]);
 *  @p
 *
 *  For second C6678 device:
 *  @p(code)
 *  var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
 *  MultiProc.baseIdOfCluster = 8;
 *  MultiProc.numProcessors = 16;
 *  MultiProc.setConfig(null, ["CORE0", "CORE1", "CORE2", "CORE3",
 *                             "CORE4", "CORE5", "CORE6", "CORE7"]);
 *  @p
 *
 *  Using the information supplied using the {@link #setConfig} meta function
 *  and the {@link #baseIdOfCluster} module configuration, the processor IDs
 *  are internally set.  Please refer to the documentation for
 *  {@link #setConfig} and {@link #baseIdOfCluster} for more details.
 *
 *  At runtime, the {@link #getId} call returns the MultiProc id of those
 *  processors within its cluster. At config-time, the {@link #getIdMeta}
 *  call returns the the same value.
 *
 */

module MultiProc
{
    metaonly struct ModuleView {
        UInt16       id;                /* Own ID                           */
        UInt16       numProcessors;     /* # of processors                  */
        String       nameList[];        /* Proc names ordered by procId     */
    }

    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
            [
                'Module',
                {
                    type: ViewInfo.MODULE,
                    viewInitFxn: 'viewInitModule',
                    structName: 'ModuleView'
                }
            ],
            ]
        });

    /*!
     *  Assert raised when an invalid processor id is used
     */
    config Assert.Id A_invalidMultiProcId  = {
        msg: "A_invalidMultiProcId: Invalid MultiProc id"
    };

    /*!
     *  Assert raised when a NULL processor name is encountered
     */
    config Assert.Id A_invalidProcName  = {
        msg: "A_invalidProcName: NULL MultiProc name encountered"
    };

    /*!
     *  Invalid processor id constant
     *
     *  This constant denotes that the processor id is not valid.
     */
    const UInt16 INVALIDID = 0xFFFF;

    /*! @_nodoc
     *  ======== nameList ========
     *  Unique name for the each processor used in a multi-processor app
     *
     *  This array should never be set or read directly by the MultiProc user.
     *  The nameList is used to store names configuration supplied via the
     *  {@link #setConfig} static function.
     *
     *  At runtime, the {@link #getName} function may be used to retrieve
     *  the name of any processor given it's MultiProc id.
     */
    config String nameList[];

    /*! @_nodoc
     *  ======== id ========
     *  Unique software id number for the processor
     *
     *  This value should never be set or read directly by the MultiProc user.
     *  Instead, the {@link #getId}, {@link #getIdMeta}, and
     *  {@link #setLocalId} calls should be used to respectively retrieve any
     *  processors' MultiProc ids or set the local processor's MultiProc id.
     */
    metaonly config UInt16 id = 0;

    /*! @_nodoc
     *  ======== numProcsInCluster ========
     *  Number of processors in a cluster
     *
     *  This parameter should never be set: numProcsInCluster is
     *  internally set by the {@link #setConfig} meta function.
     *  setConfig statically sets the value of this configuration to the
     *  length of the supplied nameList array.
     */
    config UInt16 numProcsInCluster = 1;

    /*!
     *  ======== baseIdOfCluster ========
     *  The base processor ID of the cluster.
     *
     *  The ID of each processor in a cluster is computed by adding
     *  its position in the name list of {@link #setConfig} to the
     *  base ID of the cluster. When more than one cluster exists in
     *  the system, this parameter must be set before calling
     *  {@link #setConfig}.
     */
    metaonly config UInt16 baseIdOfCluster = 0;

    /*!
     *  ======== numProcessors ========
     *  Number of processors in the system
     *
     *  This configuration should only be set when there is more than one
     *  cluster in the system.  It must be set before calling
     *  {@link #setConfig}. If the system contains only one cluster,
     *  it is internally set by the {@link #setConfig} meta function to the
     *  length of the supplied nameList array.
     *  After {@link #setConfig} has been  called, it is possible to
     *  retrive the maximum # of processors by reading this module config
     *  either at run-time or at config time.
     */
    config UInt16 numProcessors = 1;

    /*!
     *  ======== ProcAddrMode ========
     *  Enumerate the Processor Addressing Modes
     *
     *  This enumeration defines the various processor addressing modes
     *  which might impact the behavior and resource allocations of modules
     *  that communicate with other processors in the system (i.e. IPC).
     *
     *  It is a way for the system integrator to control the internal
     *  behavior and resource allocations of various module to suit the
     *  needs of the program. However, it is at the discretion of each
     *  module on how to respond to these processor addressing modes.
     *
     *  For example, the NameServer module reflects on this mode when
     *  constructing its internal data structures. For the 'Global' mode,
     *  it will allocate a resource for every processor in the system.
     *  When using 'Cluster' mode, resources are only allocated for
     *  processors in the cluster. A side-effect is that when using
     *  Cluster mode, name queries cannot be addressed to processors
     *  outside of the cluster.
     *
     *  Specify the addressing mode by setting the
     *  {@link #procAddrMode MultiProc.procAddrMode} configuration
     *  parameter.
     *
     *  @field(ProcAddrMode_Global) Every processor in the system must
     *  be directly addressable. Usually, this requires a resource
     *  allocation for each processor. This might require a dedicated
     *  hardware resource and/or a memory allocation on behalf of every
     *  processor in the sytem. For large systems, this might result in
     *  significant memory requirements. Use with caution.
     *
     *  @field(ProcAddrMode_Cluster) Direct addressing is required
     *  only for the processors in your cluster. Processors outside of
     *  the cluster may share resources. This mode limits the per processor
     *  resource allocations to just the processors within your cluster.
     *  This address mode is typically used for large processor systems.
     *
     *  @see #procAddrMode
     */
    enum ProcAddrMode {
        ProcAddrMode_Global,
        ProcAddrMode_Cluster
    };

    /*!
     *  ======== procAddrMode ========
     *  Define which processor addressing mode is in operation
     *
     *  This configuration parameter is reflected upon by various system
     *  components whose implementation is impacted by the processor
     *  addressing mode currently in effect. It allows modules to optimize
     *  their behavior and resource allocations for any given processor
     *  address mode.
     *
     *  The MultiProc module has no specific behavior associated with
     *  this configuration parameter. It is simply a convenient location
     *  for such a configuration parameter as most processor aware
     *  modules already depend on MultiProc.
     *
     *  @see #ProcAddrMode
     */
    config ProcAddrMode procAddrMode = MultiProc.ProcAddrMode_Global;

    /*! @_nodoc
     *  ======== getClusterId ========
     */
    UInt16 getClusterId(UInt16 procId);

    /*!
     *  ======== getIdMeta ========
     *  Meta version of {@link #getId}
     *
     *  Statically returns the internally set ID based on configuration
     *  supplied via {@link #setConfig}.
     *
     *  @param(name)        MultiProc procName
     */
    metaonly UInt16 getIdMeta(String name);

    /*!
     *  ======== getDeviceProcNames ========
     *  Returns an array of all possible processor names on the build device
     *
     *  @(return)           Array of valid MultiProc processor names
     */
    metaonly Any getDeviceProcNames();

    /*!
     *  ======== setConfig ========
     *  Configure the MultiProc module
     *
     *  Configuration of the MultiProc module is primarily accomplished using
     *  the setConfig API at config time.  The setConfig API allows the
     *  MultiProc module to identify:
     *  @p(blist)
     *      - Which is the local processor
     *      - Which processors are being used
     *      - Which processors can synchronize
     *  @p
     *  The second of these two pieces of information is supplied via the
     *  nameList argument.  The nameList is a non-empty set of distinct
     *  processors valid for the particular device.  For a list of valid
     *  processor names for a given device, please refer to the :
     *  {@link ./../ipc/family/doc-files/procNames.html Table of
     *   Valid Names for Each Device}.
     *
     *  The local processor is identified by using a single name from
     *  nameList.  A MultiProc id is internally set to the index of
     *  'name' in the supplied 'nameList'.  I.e. in the example:
     *
     *  @p(code)
     *  MultiProc.setConfig("DSP", ["HOST", "DSP", "OTHERCORE"]);
     *  @p
     *
     *  The processors, "HOST", "DSP" and "OTHERCORE" get assigned MultiProc
     *  IDs 0, 1, and 2, respectively.  The local processor, "DSP" is assigned
     *  an ID of '1'.
     *
     *  If the local processor is not known at static time, it is possible to
     *  supply a null name. MultiProc will set the local id to
     *  {@link #INVALIDID} until it is set at runtime using
     *  MultiProc_setLocalId.
     *
     *  @param(name)        MultiProc name for the local processor
     *  @param(nameList)    Array of all processors used by the application
     */
    metaonly Void setConfig(String name, String nameList[]);

    /*! @_nodoc
     *  ======== getName$view ========
     *  ROV-time version of {@link #getName}
     */
    metaonly String getName$view(UInt id);

    /*! @_nodoc
     *  ======== self$view ========
     *  ROV-time version of {@link #self}
     */
    metaonly UInt self$view();

    /*! @_nodoc
     *  This is needed to prevent the MultiProc module from being optimized away
     *  during the whole_program[_debug] partial link.
     */
    Void dummy();

internal:

    /*  Store these elements in the module state (instead of config) to
     *  support boot-time assignment (for single image reuse).
     */
    struct Module_State {
        UInt16 id;
        UInt16 baseIdOfCluster;
        UInt16 clusterProcList[];       /* list of procIds in cluster */
    };
}
