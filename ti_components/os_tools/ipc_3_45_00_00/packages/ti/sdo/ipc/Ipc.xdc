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
 *  ======== Ipc.xdc ========
 *
 */

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.rov.ViewInfo;
import ti.sdo.utils.MultiProc;

/*!
 *  ======== Ipc ========
 *  IPC Master Manager
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/Ipc.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg):
 *
 *  <PRE>Ipc = xdc.useModule('ti.sdo.ipc.Ipc');</PRE>
 *
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../../doxygen/html/files.html">Doxygen documenation</A>
 *  for the IPC product.  However, the documentation presented on this page
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 *
 *  The most common static configuration that is required of the Ipc module
 *  is the {@link #procSync} configuration that affects the behavior of the
 *  Ipc_start and Ipc_attach runtime APIs.
 *
 *  Additionally, certain subsystems of IPC (such as Notify and MessageQ) can
 *  be disabled to save resources on a per-connection basis by configuring Ipc
 *  using {@link #setEntryMeta}.
 *
 */

@Template ("./Ipc.xdt")
module Ipc
{
    /*!
     *  ======== ModuleView ========
     *  @_nodoc
     */
    metaonly struct ModuleView {
        UInt16  remoteProcId;
        Bool    attached;
        Bool    setupNotify;
        Bool    setupMessageQ;
    };

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Module',
                    {
                        type: xdc.rov.ViewInfo.MODULE_DATA,
                        viewInitFxn: 'viewInitModule',
                        structName: 'ModuleView'
                    }
                ],
            ]
        });

    /*!
     *  Various configuration options for {@link #procSync}
     *
     *  The values in this enum affect the behavior of the Ipc_start and
     *  Ipc_attach runtime APIs.
     *
     *  ProcSync_ALL:  Calling Ipc_start will also internally Ipc_attach to
     *  each remote processor.  The application should never call Ipc_attach.
     *  This type of startup and synchronization should be used if all IPC
     *  processors on a device start up at the same time and connections should
     *  be established between every possible pair of processors.
     *
     *  ProcSync_PAIR (default):  Calling Ipc_start will perform system-wide IPC
     *  initialization required on all processor, but connections to remote
     *  processors will not be established (i.e. Ipc_attach will never be
     *  called).  This configuration should be chosen if synchronization is
     *  required and some/all these conditions are true:
     *  @p(blist)
     *  - It is necessary to control when synchronization with each remote
     *    processor occurs
     *  - Useful work can be done while trying to synchronize with a remote
     *    processor by yielding a thread after each attempt to Ipc_attach
     *    to the processor.
     *  - Connections to all remote processors are unnecessary and connections
     *    should selectively be made to save memory
     *  @p
     *  NOTE: A connection should be made to the owner of region 0 (usually the
     *  processor with id = 0) before any connection to any other remote
     *  processor can be made. For example, if there are three processors
     *  configured with MultiProc, #1 should attach to #0 before it can attach
     *  to #2.
     *
     *  ProcSync_NONE:  This should be selected with caution.  Ipc_start will
     *  work exactly as it does with ProcSync_PAIR.  However, Ipc_attach will
     *  not synchronize with the remote processor.  Callers of Ipc_attach are
     *  bound by the same restrictions imposed by using ProcSync_PAIR.
     *  Additionally, an Ipc_attach to a remote processor whose id is less than
     *  our own has to occur *after* the corresponding remote processor has
     *  called attach to the original processor.  For example, processor #2
     *  can call
     *  @p(code)
     *  Ipc_attach(1);
     *  @p
     *  only after processor #1 has called:
     *  @p(code)
     *  Ipc_attach(2);
     *  @p
     *
     */
    enum ProcSync {
        ProcSync_NONE,          /*! ProcSync_PAIR with no synchronization   */
        ProcSync_PAIR,          /*! Ipc_start does not Ipc_attach           */
        ProcSync_ALL            /*! Ipc_start attach to all remote procs    */
    };

    /*!
     *  Struct used for configuration via {@link #setEntryMeta}
     *
     *  This structure defines the fields that are to be configured
     *  between the executing processor and a remote processor.
     */
    struct Entry {
        UInt16 remoteProcId;    /*! Remote processor id                     */
        Bool   setupNotify;     /*! Whether to setup Notify                 */
        Bool   setupMessageQ;   /*! Whether to setup MessageQ               */
    };

    /*! struct for attach/detach plugs. */
    struct UserFxn {
        Int (*attach)(UArg, UInt16);
        Int (*detach)(UArg, UInt16);
    };

    /*
     *************************************************************************
     *                       Generic IPC Errors/Asserts
     *************************************************************************
     */

    /*!
     *  ======== A_addrNotInSharedRegion ========
     *  Assert raised when an address lies outside all known shared regions
     */
    config Assert.Id A_addrNotInSharedRegion  = {
        msg: "A_addrNotInSharedRegion: Address not in any shared region"
    };

    /*!
     *  ======== A_addrNotCacheAligned ========
     *  Assert raised when an address is not cache-aligned
     */
    config Assert.Id A_addrNotCacheAligned  = {
        msg: "A_addrNotCacheAligned: Address is not cache aligned"
    };

    /*!
     *  ======== A_nullArgument ========
     *  Assert raised when a required argument is null
     */
    config Assert.Id A_nullArgument  = {
        msg: "A_nullArgument: Required argument is null"
    };

    /*!
     *  ======== A_nullPointer ========
     *  Assert raised when a pointer is null
     */
    config Assert.Id A_nullPointer  = {
        msg: "A_nullPointer: Pointer is null"
    };

    /*!
     *  ======== A_invArgument ========
     *  Assert raised when an argument is invalid
     */
    config Assert.Id A_invArgument  = {
        msg: "A_invArgument: Invalid argument supplied"
    };

    /*!
     *  ======== A_invParam ========
     *  Assert raised when a parameter is invalid
     */
    config Assert.Id A_invParam  = {
        msg: "A_invParam: Invalid configuration parameter supplied"
    };

    /*!
     *  ======== A_internal ========
     *  Assert raised when an internal error is encountered
     */
    config Assert.Id A_internal = {
        msg: "A_internal: An internal error has occurred"
    };

    /*!
     *  ======== E_nameFailed ========
     *  Error raised when a name failed to be added to the NameServer
     *
     *  Error raised in a create call when a name fails to be added
     *  to the NameServer table.  This can be because the name already
     *  exists, the table has reached its max length, or out of memory.
     */
    config Error.Id E_nameFailed  = {
        msg: "E_nameFailed: '%s' name failed to be added to NameServer"
    };

    /*!
     *  ======== E_internal ========
     *  Error raised when an internal error occured
     */
    config Error.Id E_internal  = {
        msg: "E_internal: An internal error occurred"
    };

    /*!
     *  ======== E_versionMismatch ========
     *  Error raised when a version mismatch occurs
     *
     *  Error raised in an open call because there is
     *  a version mismatch between the opener and the creator
     */
    config Error.Id E_versionMismatch  = {
        msg: "E_versionMismatch: IPC Module version mismatch: creator: %d, opener: %d"
    };

    /*
     *************************************************************************
     *                       Module-wide Config Parameters
     *************************************************************************
     */

    /*!
     *  ======== sr0MemorySetup ========
     *  Whether Shared Region 0 memory is accessible
     *
     *  Certain devices have a slave MMU that needs to be configured by the
     *  host core before the slave core can access shared region 0.  If
     *  the host core is also running BIOS, it is necessary to set this
     *  configuration to 'true', otherwise {@link #start} will always fail.
     *
     *  This configuration should not be used for devices that don't have
     *  a slave MMU and don't run Linux.
     */
    config Bool sr0MemorySetup;

    /*! @_nodoc
     *  ======== hostProcId ========
     *  Host processor identifier.
     *
     *  Used to specify the host processor's id.  This parameter is only used
     *  in a Syslink system.
     */
    metaonly config UInt16 hostProcId = MultiProc.INVALIDID;

    /*!
     *  ======== procSync ========
     *  Affects how Ipc_start and Ipc_attach behave
     *
     *  Refer to the documentation for the {@link #ProcSync} enum for
     *  information about the various ProcSync options.
     */
    config ProcSync procSync = Ipc.ProcSync_PAIR;

    /*! @_nodoc
     *  ======== generateSlaveDataForHost ========
     *  generates the slave's data into a section for the host.
     */
    config Bool generateSlaveDataForHost;

    /*!@_nodoc
     *  ======== userFxn ========
     *  Attach and Detach hooks.
     */
    config UserFxn userFxn;

    /*
     *************************************************************************
     *                       IPC Functions
     *************************************************************************
     */

     /*!
     *  ======== addUserFxn ========
     *  Add a function that gets called during Ipc_attach/detach.
     *
     *  The user added functions must be non-blocking and must run
     *  to completion. The functions need to check to make sure it
     *  is not called multiple times when more than one thread calls
     *  Ipc_attach() for the same processor.  It is safe to use IPC
     *  APIs in a user function as long as the IPC APIs satisfy these
     *  requirements.
     *
     *  @p(code)
     *      var Ipc = xdc.useModule('ti.sdo.ipc.Ipc');
     *      var fxn = new Ipc.UserFxn;
     *      fxn.attach = '&userAttachFxn';
     *      fxn.detach = '&userDetachFxn';
     *      Ipc.addUserFxn(fxn, arg);
     *  @p
     *
     *  @param(fxn)     The user function to call during attach/detach.
     *  @param(arg)     The argument to the function.
     */
    metaonly Void addUserFxn(UserFxn fxn, UArg arg);

     /*!
     *  ======== getEntry ========
     *  Gets the properties for attaching to a remote processor.
     *
     *  This function must be called before Ipc_attach().  The
     *  parameter entry->remoteProcId field must be set prior to calling
     *  the function.
     *
     *  @param(entry)       Properties between a pair of processors.
     */
    Void getEntry(Entry *entry);

    /*!
     *  ======== setEntryMeta ========
     *  Statically sets the properties for attaching to a remote processor.
     *
     *  This function allows the user to configure whether Notify and/or
     *  MessageQ is setup during Ipc_attach().  If 'setupNotify' is set
     *  to 'false', neither the Notify or NameServerRemoteNotify instances
     *  are created.  If 'setupMessageQ' is set to 'false', the MessageQ
     *  transport instances are not created.  By default, both flags are
     *  set to 'true'.
     *
     *  Note: For any pair of processors, the flags must be the same
     *
     *  @param(entry)       Properties between a pair of processors.
     */
    metaonly Void setEntryMeta(Entry entry);

    /*!
     *  ======== setEntry ========
     *  Sets the properties for attaching to a remote processor.
     *
     *  This function must be called before Ipc_attach().  It allows
     *  the user to configure whether Notify and/or MessageQ is setup
     *  during Ipc_attach().  If 'setupNotify' is set to 'FALSE',
     *  neither the Notify or NameServerRemoteNotify instances are
     *  created.  If 'setupMessageQ' is set to 'FALSE', the MessageQ
     *  transport instances are not created.  By default, both flags are
     *  set to 'TRUE'.
     *
     *  Note: For any pair of processors, the flags must be the same
     *
     *  @param(entry)       Properties between a pair of processors.
     */
    Void setEntry(Entry *entry);

    /*! @_nodoc
     *  This is needed to prevent the Ipc module from being optimized away
     *  during the whole_program[_debug] partial link.
     */
    Void dummy();


internal:

    /* flag for starting processor synchronization */
    const UInt32 PROCSYNCSTART  = 1;

    /* flag for finishing processor synchronization */
    const UInt32 PROCSYNCFINISH = 2;

    /* flag for detaching */
    const UInt32 PROCSYNCDETACH = 3;

    /* Type of Ipc object. Each value needs to be a power of two. */
    enum ObjType {
        ObjType_CREATESTATIC            = 0x1,
        ObjType_CREATESTATIC_REGION     = 0x2,
        ObjType_CREATEDYNAMIC           = 0x4,  /* Created by sharedAddr      */
        ObjType_CREATEDYNAMIC_REGION    = 0x8,  /* Created by regionId        */
        ObjType_OPENDYNAMIC             = 0x10, /* Opened instance            */
        ObjType_LOCAL                   = 0x20  /* Local-only instance        */
    };

    /*
     *  This structure captures Configuration details of a module/instance
     *  written by a slave to synchornize with a remote slave/HOST
     */
    struct ConfigEntry {
        Bits32 remoteProcId;
        Bits32 localProcId;
        Bits32 tag;
        Bits32 size;
        Bits32 next;
    };

    struct ProcEntry {
        SharedRegion.SRPtr *localConfigList;
        SharedRegion.SRPtr *remoteConfigList;
        UInt   attached;
        Entry  entry;
    };

    /* The structure used for reserving memory in SharedRegion */
    struct Reserved {
        volatile Bits32    startedKey;
        SharedRegion.SRPtr notifySRPtr;
        SharedRegion.SRPtr nsrnSRPtr;
        SharedRegion.SRPtr transportSRPtr;
        SharedRegion.SRPtr configListHead;
    };

    /* The structure used for reserving memory in SharedRegion */
    struct UserFxnAndArg {
        UserFxn userFxn;
        UArg    arg;
    };

    /* Storage for setup of processors */
    metaonly config Entry entry[];

    config UInt numUserFxns = 0;

    /*!
     *  ======== userFxns ========
     *  Attach and Detach hooks.
     */
    config UserFxnAndArg userFxns[] = [];

    /*!
     *  ======== getMasterAddr() ========
     */
    Ptr getMasterAddr(UInt16 remoteProcId, Ptr sharedAddr);

    /*!
     *  ======== getRegion0ReservedSize ========
     *  Returns the amount of memory to be reserved for Ipc in SharedRegion 0.
     *
     *  This is used for synchronizing processors.
     */
    SizeT getRegion0ReservedSize();

    /*!
     *  ======== getSlaveAddr() ========
     */
    Ptr getSlaveAddr(UInt16 remoteProcId, Ptr sharedAddr);

    /*!
     *  ======== procSyncStart ========
     *  Starts the process of synchronizing processors.
     *
     *  Shared memory in region 0 will be used.  The processor which owns
     *  SharedRegion 0 writes its reserve memory address in region 0
     *  to let the other processors know it has started.  It then spins
     *  until the other processors start.  The other processors write their
     *  reserve memory address in region 0 to let the owner processor
     *  know they've started.  The other processors then spin until the
     *  owner processor writes to let them know its finished the process
     *  of synchronization before continuing.
     */
    Int procSyncStart(UInt16 remoteProcId, Ptr sharedAddr);

    /*!
     *  ======== procSyncFinish ========
     *  Finishes the process of synchronizing processors.
     *
     *  Each processor writes its reserve memory address in SharedRegion 0
     *  to let the other processors know its finished the process of
     *  synchronization.
     */
    Int procSyncFinish(UInt16 remoteProcId, Ptr sharedAddr);

    /*!
     *  ======== reservedSizePerProc ========
     *  The amount of memory required to be reserved per processor.
     */
    SizeT reservedSizePerProc();

    /*! Used for populated the 'objType' field in ROV views*/
    metaonly String getObjTypeStr$view(ObjType type);

    /* Module state */
    struct Module_State {
        Ptr       ipcSharedAddr;
        Ptr       gateMPSharedAddr;
        ProcEntry procEntry[];
    };
}
