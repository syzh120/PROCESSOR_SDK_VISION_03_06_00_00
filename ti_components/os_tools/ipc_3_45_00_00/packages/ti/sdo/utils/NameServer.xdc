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
 *  ======== NameServer.xdc ========
 *
 */

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.IHeap;
import ti.sysbios.gates.GateSwi;
import xdc.rov.ViewInfo;

/*!
 *  ======== NameServer ========
 *  Manages and serves names to remote/local processor
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/NameServer.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>NameServer = xdc.useModule('ti.sdo.ipc.NameServer');</PRE>
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
 *  @a(Note)
 *  This modules reflects upon the {@link ti.sdo.utils.MultiProc#procAddrMode}
 *  configuration parameter. Some internal data structure allocations are
 *  optimized for the given processor address mode. For example, when using
 *  MultiProc.ProcAddrMode_Global, resource is allocated for every processor
 *  in the system. When using MultiProc.ProcAddrMode_Cluster, resources are
 *  only allocated for processors in the cluster. A side-effect is that when
 *  using Cluster mode, name queries cannot be addressed to processors
 *  outside of the cluster.
 */

@ModuleStartup
@InstanceInitError /* Initialization may throw errors */
@InstanceFinalize

module NameServer
{
    /*!
     *  ======== BasicView ========
     *  @_nodoc
     */
    metaonly struct BasicView {
        String  name;
        Bool    checkExisting;
        UInt    maxNameLen;
        UInt    maxValueLen;
        UInt    numStatic;
        String  numDynamic;
    }

    /*!
     *  ======== NamesListView ========
     *  @_nodoc
     */
    metaonly struct NamesListView {
        String  name;
        String  value;
        UInt    len;
        Ptr     nsKey;
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
                ['NamesValues',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitData',
                        structName: 'NamesListView'
                    }
                ]
            ]
        });

    /*!
     *  Assert raised when the name or value is too long
     */
    config Assert.Id A_invalidLen  = {
        msg: "A_invalidLen: Invalid length"
    };

    /*!
     *  ======== A_invArgument ========
     *  Assert raised when an argument is invalid
     */
    config Assert.Id A_invArgument  = {
        msg: "A_invArgument: Invalid argument supplied"
    };

    /*!
     *  Error raised if all the entries in the instance Name/Value table
     *  are taken
     */
    config Error.Id E_maxReached  = {
        msg: "E_maxReached: All entries in use. NameServer.maxRuntimeEntries is %d"
    };

    /*!
     *  Error raised when the name already exists in the instance
     *  Name/Value table
     */
    config Error.Id E_entryExists  = {
        msg: "E_entryExists: %s name already in table "
    };

    /*!
     *  Error raised when creation parameters do not match those of an
     *  existing NameServer
     */
    config Error.Id E_paramMismatch  = {
        msg: "E_paramMismatch: parameters do not match existing NameServer %s "
    };

    /*!
     *  Allow dynamic growth of the NameServer instance table
     *
     *  This value can be used to set the {@link #maxRuntimeEntries}.
     *  This flag tells NameServer to allow dynamic growth
     *  of the table.
     */
    const UInt ALLOWGROWTH = (~0);

    /*!
     *  Structure of entry in Name/Value table
     *
     *  This structure is returned from the {@link #getMeta}
     *  API.
     *
     *  @field(name)  Name portion of the name/value pair.
     *  @field(len)   Length of the value field.
     *  @field(value) Value portion of the name/value entry.
     */
    metaonly struct Entry {
        String      name;
        UInt        len;
        UArg        value;
    };

    /*!
     *  ======== SetupProxy ========
     *  NameServer setup proxy
     */
    proxy SetupProxy inherits INameServerRemote;

    /*!
     *  ======== isRegistered ========
     *  Determines if a remote driver is registered for the specified id.
     *
     *  @param(procId)  The remote processor id.
     */
    @DirectCall
    Bool isRegistered(UInt16 procId);

    /*!
     *  ======== registerRemoteDriver ========
     *  Register the NameServer remote handle for the specified processor id.
     *
     *  This function is used by NameServer remote driver to register
     *  themselves with NameServer. Only one remote driver can be registered
     *  with a remote processor. The API returns {@link #Status_FAIL} if there
     *  is already a registered remote driver for the processor id.
     *
     *  @param(handle)  The handle for a NameServer remote driver instance.
     *  @param(procId)  The remote processor id.
     *
     *  @b(returns)     Returns {@link #Status_SUCCESS} if successful or
     *                  {@link #Status_FAIL} if the processor id has already
     *                  been set.
     */
    @DirectCall
    Int registerRemoteDriver(INameServerRemote.Handle handle, UInt16 procId);

    /*!
     *  ======== unregisterRemoteDriver ========
     *  Unregister the NameServer remote handle for the specified processor id.
     *
     *  This function is used by NameServer Remote implementations to unregister
     *  themselves with NameServer.
     *
     *  @param(procId)  The remote processor id to unregister.
     */
    @DirectCall
    Void unregisterRemoteDriver(UInt16 procId);

    /*!
     *  ======== modAddMeta ========
     *  Add a name/value pair into the specified instance's table during
     *  configuration
     *
     *  This function adds any length value into the local table. The function
     *  makes sure the name does not already exist in the local table.
     *
     *  This function should be used by modules when adding into a NameServer
     *  instance. The application configuration file, should
     *  use {@link #addMeta}.
     *
     *  The function does not query remote processors to make sure the
     *  name is unique.
     *
     *  @param(instName)   NameServer instance name
     *  @param(name)       Name portion of the name/value pair
     *  @param(value)      Value portion of the name/value pair
     *  @param(len)        Length of the value buffer
     */
    metaonly Void modAddMeta(String instName, String name, Any value, UInt len);

    /*!
     *  ======== getName$view ========
     *  @_nodoc
     *  Used at ROV time to display reverse-lookup name from 32-bit value and
     *  tableName
     */
    metaonly String getName$view(String tableName, UInt32 value);

    /*!
     *  ======== getNameByKey$view ========
     *  @_nodoc
     *  ROV function for retrieving an entry by its address. Throws an exception
     *  if the name was not found
     */
    metaonly String getNameByKey$view(Ptr addr);


instance:

    /*!
     *  Maximum number of name/value pairs that can be dynamically created.
     *
     *  This parameter allows NameServer to pre-allocate memory.
     *  When NameServer_add or NameServer_addUInt32 is called, no memory
     *  allocation occurs.
     *
     *  If the number of pairs is not known at configuration time, set this
     *  value to {@link #ALLOWGROWTH}. This instructs NameServer to grow the
     *  table as needed. NameServer will allocate memory from the
     *  {@link #tableHeap} when a name/value pair is added.
     *
     *  The default is {@link #ALLOWGROWTH}.
     */
    config UInt maxRuntimeEntries = ALLOWGROWTH;

    /*!
     *  Name/value table is allocated from this heap.
     *
     *  The instance table and related buffers are allocated out of this heap
     *  during the dynamic create. This heap is also used to allocate new
     *  name/value pairs when {@link #ALLOWGROWTH} for
     *  {@link #maxRuntimeEntries}
     *
     *  The default is to use the same heap that instances are allocated
     *  from which can be configured via the
     *  NameServer.common$.instanceHeap configuration parameter.
     */
    config IHeap.Handle tableHeap = null;

    /*!
     *  Name/value table is placed into this section on static creates.
     *
     *  The instance table and related buffers are placed into this section
     *  during the static create.
     *
     *  The default is no explicit section placement.
     */
    metaonly config String tableSection = null;

    /*!
     *  Check if a name already exists in the name/value table.
     *
     *  When a name/value pair is added during runtime, if this boolean is true,
     *  the table is searched to see if the name already exists. If it does,
     *  the name is not added and the {@link #E_entryExists} error is raised.
     *
     *  If this flag is false, the table will not be checked to see if the name
     *  already exists. It will simply be added. This mode has better
     *  performance at the expense of potentially having non-unique names in the
     *  table.
     *
     *  This flag is used for runtime adds only. Adding non-unique names during
     *  configuration results in a build error.
     */
    config Bool checkExisting = true;

    /*!
     *  Length, in MAUs, of the value field in the table.
     *
     *  Any value less than sizeof(UInt32) will be rounded up to sizeof(UInt32).
     */
    config UInt maxValueLen = 0;

    /*!
     *  Length, in MAUs, of the name field in the table.
     *
     *  The maximum length of the name portion of the name/value
     *  pair. The length includes the null terminator ('\0').
     */
    config UInt maxNameLen = 16;

    /*!
     *  ======== metaTable ========
     *  @_nodoc
     *  Table to hold the statically added name/value pairs until
     *  they ready to be added to the object.
     */
    metaonly config Entry metaTable[];

   /*!
     *  ======== create ========
     *  @_nodoc (Refer to doxygen for ti/ipc/NameServer.h)
     *  Create a NameServer instance
     *
     *  This function creates a NameServer instance. The name is
     *  used for remote processor queries and diagnostic tools. For
     *  single processor system (e.g. no remote queries), the name
     *  can be NULL.
     *
     *  @param(name)    Name of the instance
     */
    create(String name);

    /*!
     *  ======== addUInt32Meta ========
     *  Add a name/value pair into the instance's table during configuration
     *
     *  This function adds a UInt32 value into the local table. The function
     *  makes sure the name does not already exist in the local table.
     *
     *  The function does not query remote processors to make sure the
     *  name is unique.
     *
     *  @param(name)   Name portion of the name/value pair
     *  @param(value)  Value portion of the name/value pair
     */
    metaonly Void addUInt32Meta(String name, any value);

    /*!
     *  ======== addMeta ========
     *  Add a name/value pair into the instance's table during configuration
     *
     *  This function adds any length value into the local table. The function
     *  makes sure the name does not already exist in the local table.
     *
     *  This function should be used by within the application configuration
     *  file. XDC modules should use {@link #modAddMeta}.
     *
     *  The function does not query remote processors to make sure the
     *  name is unique.
     *
     *  @param(name)   Name portion of the name/value pair
     *  @param(value)  Value portion of the name/value pair
     *  @param(len)    Length of the value buffer
     */
    metaonly Void addMeta(String name, Any value, UInt len);

    /*!
     *  ======== getMeta ========
     *  Retrieves the name/value entry
     *
     *  If the name is found, the entry is returned. The caller can parse the
     *  entry as needed. If the name is not found, null is returned.
     *
     *  The search only occurs on the local table.
     *
     *  @param(name)     Name in question
     *
     *  @b(returns)      Name/value entry
     */
    metaonly Entry getMeta(String name);

    /*!
     *  ======== getKey ========
     *  @_nodoc
     *  Returns a pointer to the TableEntry containing the argument 'val'.
     *  This should only be used internally by Ipc modules during their
     *  initialization process.
     *
     *  This function can only be used when maxValueLen = sizeof(UInt32)
     */
    @DirectCall
    Ptr getKey(UInt32 val);

internal:

    /* Used to eliminate code when doing whole-program */
    config Bool singleProcessor = true;

    metaonly typedef Entry EntryMap[];

    /*! Structure of entry in Name/Value table */
    struct TableEntry {
        List.Elem   elem;
        String      name;
        UInt        len;
        UArg        value;
    };

    /*!
     *  ======== metaModTable ========
     *  Table to hold the static added name/value pairs until
     *  they ready to be added to the object.
     */
    metaonly config EntryMap metaModTable[string];

    /*
     *  ======== postInit ========
     *  Finish initializing static and dynamic NameServer instances
     */
    Int postInit(Object *obj);

    /*
     *  ======== findLocal ========
     *  Searches to the local instance table.
     *
     *  This is an internal function because it returns an internal structure.
     */
    TableEntry *findLocal(Object *obj, String name);

    /*
     *  ======== removeLocal ========
     *  removes an entry from the local instance table.
     */
    Void removeLocal(Object *obj, TableEntry *entry);

    /*
     *  ======== editLocal ========
     *  replaces the value of an entry from the local instance table.
     */
    Void editLocal(Object *obj, TableEntry *entry, Ptr newValue);

    /* instance object */
    struct Instance_State {
        String       name;           /* Name of the instance           */
        List.Object  freeList;       /* Empty entries list             */
        List.Object  nameList;       /* Filled entries list            */
        UInt         maxNameLen;     /* Max name length                */
        UInt         maxValueLen;    /* Max value length               */
        UInt         numStatic;      /* Total static entries in table  */
        UInt         numDynamic;     /* Total dynamic entries in table */
        TableEntry   table[];        /* Table                          */
        Char         names[];        /* Buffer for names               */
        UInt8        values[];       /* Buffer for values              */
        IHeap.Handle tableHeap;      /* Heap used to alloc table       */
        Bool         checkExisting;  /* check ig name already exists   */
        UInt32       refCount;       /* reference count to this instance */
    };

    struct Module_State {
        INameServerRemote.Handle nsRemoteHandle[length];
        GateSwi.Handle gate;
    };
}
