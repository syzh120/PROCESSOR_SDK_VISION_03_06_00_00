/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 *  ======== GateMP.xdc ========
 *
 */

package ti.sdo.ipc;

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.IGateProvider;
import xdc.runtime.Log;
import xdc.runtime.Diags;

import ti.sdo.utils.NameServer;
import ti.sdo.ipc.interfaces.IGateMPSupport;

/*!
 *  ======== GateMP ========
 *  Multiple processor gate that provides local and remote context protection.
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/GateMP.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>GateMP = xdc.useModule('ti.sdo.ipc.GateMP');</PRE>
 *
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../../doxygen/html/files.html">Doxygen documentation</A>
 *  for the IPC product.  However, the documentation presented on this page
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 */

@InstanceInitError
@InstanceFinalize

@Template("./GateMP.xdt")
module GateMP
{
    /*!
     *  ======== BasicView ========
     *  @_nodoc
     */
    metaonly struct BasicView {
        String  name;
        String  remoteProtect;
        String  remoteStatus;
        String  localProtect;
        UInt    numOpens;
        Bits32  resourceId;
        UInt    creatorProcId;
        String  objType;
    }

    /*!
     *  ======== ModuleView ========
     *  @_nodoc
     */
    metaonly struct ModuleView {
        UInt    numGatesSystem;
        UInt    numUsedSystem;
        UInt    numGatesCustom1;
        UInt    numUsedCustom1;
        UInt    numGatesCustom2;
        UInt    numUsedCustom2;
    }

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Basic',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ],
                ['Gate Resources',
                    {
                        type: xdc.rov.ViewInfo.MODULE,
                        viewInitFxn: 'viewInitModule',
                        structName: 'ModuleView'
                    }
                ]
            ]
        });

    /*!
     *  ======== Reserved space at the top of SharedRegion0 ========
     */
    struct Reserved {
        Bits32  version;
    };

    /*!
     *  ======== E_gateUnavailable ========
     *  Error raised no gates of the requested type are available
     */
    config Error.Id E_gateUnavailable  = {
        msg: "E_gateUnavailable: No gates of requested type are available"
    };

    /*!
     *  ======== E_localGate ========
     *  Error raised when remote side tried to open local gate
     */
    config Error.Id E_localGate  = {
        msg: "E_localGate: Only creator can open local Gate"
    };

    /*!
     *  Assert raised when calling GateMP_close with the wrong handle
     */
    config Assert.Id A_invalidClose  = {
        msg: "A_invalidClose: Calling GateMP_close with the wrong handle"
    };

    /*!
     *  Assert raised when calling GateMP_delete incorrectly
     */
    config Assert.Id A_invalidDelete  = {
        msg: "A_invalidDelete: Calling GateMP_delete incorrectly"
    };

    /*!
     *  ======== LM_enter ========
     *  Logged on gate enter
     */
    config Log.Event LM_enter = {
        mask: Diags.USER1,
        msg: "LM_enter: Gate (remoteGate = %d, resourceId = %d) entered, returning key = %d"
    };

    /*!
     *  ======== LM_leave ========
     *  Logged on gate leave
     */
    config Log.Event LM_leave = {
        mask: Diags.USER1,
        msg: "LM_leave: Gate (remoteGate = %d, resourceId = %d) left using key = %d"
    };

    /*!
     *  ======== LM_create ========
     *  Logged on gate create
     */
    config Log.Event LM_create = {
        mask: Diags.USER1,
        msg: "LM_create: Gate (remoteGate = %d, resourceId = %d) created"
    };

    /*!
     *  ======== LM_open ========
     *  Logged on gate open
     */
    config Log.Event LM_open = {
        mask: Diags.USER1,
        msg: "LM_open: Remote gate (remoteGate = %d, resourceId = %d) opened"
    };

    /*!
     *  ======== LM_delete ========
     *  Logged on gate deletion
     */
    config Log.Event LM_delete = {
        mask: Diags.USER1,
        msg: "LM_delete: Gate (remoteGate = %d, resourceId = %d) deleted"
    };

    /*!
     *  ======== LM_close ========
     *  Logged on gate close
     */
    config Log.Event LM_close = {
        mask: Diags.USER1,
        msg: "LM_close: Gate (remoteGate = %d, resourceId = %d) closed"
    };

    /*!
     *  A set of local context protection levels
     *
     *  Each member corresponds to a specific local processor gates used for
     *  local protection.
     *
     *  For SYS/BIOS users, the following are the mappings for the constants
     *  @p(blist)
     * -INTERRUPT -> GateAll: disables interrupts
     * -TASKLET   -> GateSwi: disables Swis (software interrupts)
     * -THREAD    -> GateMutexPri: based on Semaphores
     * -PROCESS   -> GateMutexPri: based on Semaphores
     *  @p
     */
    enum LocalProtect {
        LocalProtect_NONE      = 0,
        LocalProtect_INTERRUPT = 1,
        LocalProtect_TASKLET   = 2,
        LocalProtect_THREAD    = 3,
        LocalProtect_PROCESS   = 4
    };

    /*!
     *  Type of remote Gate
     *
     *  Each member corresponds to a specific type of remote gate.
     *  Each enum value corresponds to the following remote protection levels:
     *  @p(blist)
     * -NONE      -> No remote protection (the GateMP instance will exclusively
     *               offer local protection configured in {@link #localProtect})
     * -SYSTEM    -> Use the SYSTEM remote protection level (default for remote
     *               protection
     * -CUSTOM1   -> Use the CUSTOM1 remote protection level
     * -CUSTOM2   -> Use the CUSTOM2 remote protection level
     *  @p
     */
    enum RemoteProtect {
        RemoteProtect_NONE     = 0,
        RemoteProtect_SYSTEM   = 1,
        RemoteProtect_CUSTOM1  = 2,
        RemoteProtect_CUSTOM2  = 3
    };

    /*!
     *  ======== maxRuntimeEntries ========
     *  Maximum runtime entries
     *
     *  Maximum number of GateMP's that can be dynamically created and
     *  added to the NameServer.
     *
     *  To minimize the amount of runtime allocation, this parameter allows
     *  the pre-allocation of memory for the GateMP's NameServer table.
     *  The default is to allow growth (i.e. memory allocation when
     *  creating a new instance).
     */
    metaonly config UInt maxRuntimeEntries = NameServer.ALLOWGROWTH;

    /*!
     *  ======== maxNameLen ========
     *  Maximum length for names
     */
    config UInt maxNameLen = 32;

    /*!
     *  ======== hostSupport ========
     *  Support for host processor
     */
    metaonly config Bool hostSupport = false;

    /*!
     *  ======== tableSection ========
     *  Section name is used to place the names table
     */
    metaonly config String tableSection = null;

    /*!
     *  ======== RemoteSystemProxy ========
     *  System remote gate proxy
     *
     *  By default, GateMP instances use the 'System' proxy for locking between
     *  multiple processors by setting the 'localProtect' setting to .  This
     *  remote gate proxy defaults to a device-specific remote GateMP delegate
     *  and typically should not be modified.
     */
    proxy RemoteSystemProxy inherits IGateMPSupport;

    /*!
     *  ======== remoteCustom1Proxy ========
     *  Custom1 remote gate proxy
     *
     *  GateMP instances may use the 'Custom1' proxy for locking between
     *  multiple processors.  This proxy defaults to
     *  {@link ti.sdo.ipc.gates.GatePeterson}.
     */
    proxy RemoteCustom1Proxy inherits IGateMPSupport;

    /*!
     *  ======== remoteCustom2Proxy ========
     *  Custom2 remote gate proxy
     *
     *  GateMP instances may use the 'Custom2' proxy for locking between
     *  multiple processors.  This proxy defaults to
     *  {@link ti.sdo.ipc.gates.GateMPSupportNull}.
     */
    proxy RemoteCustom2Proxy inherits IGateMPSupport;

    /*!
     *  ======== createLocal ========
     *  @_nodoc
     *  Get a local IGateProvider instance
     *
     *  This function is designed to be used by the IGateMPSupport modules
     *  to get a local Gate easily.
     */
    IGateProvider.Handle createLocal(LocalProtect localProtect);

    /*! @_nodoc
     *  ======== attach ========
     */
    Int attach(UInt16 remoteProcId, Ptr sharedAddr);

    /*! @_nodoc
     *  ======== detach ========
     */
    Int detach(UInt16 remoteProcId);

    /*!
     *  ======== getRegion0ReservedSize ========
     *  @_nodoc
     *  Amount of shared memory to be reserved for GateMP in region 0.
     */
    SizeT getRegion0ReservedSize();

    /*!
     *  ======== setRegion0Reserved ========
     *  @_nodoc
     *  Set and initialize GateMP reserved memory in Region 0.
     */
    Void setRegion0Reserved(Ptr sharedAddr);

    /*!
     *  ======== openRegion0Reserved ========
     *  @_nodoc
     *  Open shared memory reserved for GateMP in region 0.
     */
    Void openRegion0Reserved(Ptr sharedAddr);

    /*!
     *  ======== setDefaultRemote ========
     *  @_nodoc
     *  Set the default Remote Gate. Called by SharedRegion_start().
     */
     Void setDefaultRemote(Handle handle);

    /*! @_nodoc
     *  ======== start ========
     */
    Int start(Ptr sharedAddr);

    /*! @_nodoc
     *  ======== stop ========
     */
    Int stop();

instance:

    /*!
     *  ======== name ========
     *  Name of the instance
     *
     *  Name needs to be unique. Used only if {@link #useNameServer}
     *  is set to TRUE.
     */
    config String name = null;

    /*! @_nodoc
     *  Set to true by the open() call. No one else should touch this!
     */
    config Bool openFlag = false;

    /*! @_nodoc
     *  Set by the open() call. No one else should touch this!
     */
    config Bits32 resourceId = 0;

    /*!
     *  Shared Region Id
     *
     *  The ID corresponding to the shared region in which this shared instance
     *  is to be placed.
     */
    config UInt16 regionId = 0;

    /*!
     *  ======== sharedAddr ========
     *  Physical address of the shared memory
     *
     *  The creator must supply the shared memory that will be used
     *  for maintaining shared state information.  This parameter is used
     *  only when {@link #Type} is set to {@link #Type_SHARED}
     */
    config Ptr sharedAddr = null;

    /*!
     *  ======== localProtect ========
     */
    config LocalProtect localProtect = LocalProtect_THREAD;

    /*!
     *  ======== localProtect ========
     */
    config RemoteProtect remoteProtect = RemoteProtect_SYSTEM;

    /*!
     *  ======== getSharedAddr ========
     *  @_nodoc
     *  Return the SRPtr that points to a GateMP instance's shared memory
     *
     *  getSharedAddr is typically used internally by other IPC modules to save
     *  the shared address to a GateMP instance in the other modules' shared
     *  state.  This allows the other module's open() call to open the GateMP
     *  instance by address.
     */
    SharedRegion.SRPtr getSharedAddr();

internal:
    const UInt32 VERSION = 1;
    const UInt32 CREATED = 0x11202009;

    const Int ProxyOrder_SYSTEM  = 0;
    const Int ProxyOrder_CUSTOM1 = 1;
    const Int ProxyOrder_CUSTOM2 = 2;
    const Int ProxyOrder_NUM     = 3;

    /*!
     *  ======== nameSrvPrms ========
     *  This Params object is used for temporary storage of the
     *  module wide parameters that are for setting the NameServer instance.
     */
    metaonly config NameServer.Params nameSrvPrms;

    UInt getFreeResource(UInt8 *inUse, Int num, Error.Block *eb);

    struct LocalGate {
        IGateProvider.Handle    localGate;
        Int                     refCount;
    }

    /* Structure of attributes in shared memory */
    struct Attrs {
        Bits16 mask;
        Bits16 creatorProcId;
        Bits32 arg;
        Bits32 status;                  /* Created stamp                 */
    };

    struct Instance_State {
        RemoteProtect           remoteProtect;
        LocalProtect            localProtect;
        Ptr                     nsKey;
        Int                     numOpens;
        Bool                    cacheEnabled;
        Attrs                   *attrs;
        UInt16                  regionId;
        SizeT                   allocSize;
        Ipc.ObjType             objType;
        Ptr                     proxyAttrs;
        UInt                    resourceId;
        IGateProvider.Handle    gateHandle;
    };

    struct Module_State {
        NameServer.Handle       nameServer;
        Int                     numRemoteSystem;
        Int                     numRemoteCustom1;
        Int                     numRemoteCustom2;
        UInt8                   remoteSystemInUse[];
        UInt8                   remoteCustom1InUse[];
        UInt8                   remoteCustom2InUse[];
        Handle                  remoteSystemGates[];
        Handle                  remoteCustom1Gates[];
        Handle                  remoteCustom2Gates[];
        IGateProvider.Handle    gateAll;
        IGateProvider.Handle    gateSwi;
        IGateProvider.Handle    gateMutexPri;
        IGateProvider.Handle    gateNull;
        Handle                  defaultGate;
        Ptr                     nsKey;
        Bool                    hostSupport;
        Int                     proxyMap[ProxyOrder_NUM];
    };
}
