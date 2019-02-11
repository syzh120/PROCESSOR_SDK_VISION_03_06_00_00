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
 *  ======== SharedRegion.xdc ========
 *
 */

package ti.sdo.ipc;

import xdc.runtime.Error;
import xdc.runtime.IHeap;
import xdc.rov.ViewInfo;

/*!
 *  ======== SharedRegion ========
 *  Shared memory manager and address translator.
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/SharedRegion.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>SharedRegion = xdc.useModule('ti.sdo.ipc.SharedRegion');</PRE>
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
 *  The SharedRegion module is designed to be used in a multi-processor
 *  environment in which memory regions are shared and accessed
 *  across different processors. The module itself does not use any shared
 *  memory, because all module state is stored locally.  SharedRegion
 *  APIs use the system gate for thread protection.
 *
 *  This module creates and stores a local shared memory region table.  The
 *  table contains the processor's view for every shared region in the system.
 *  The table must not contain any overlapping regions.  Each processor's
 *  view of a particular shared memory region is determined by the region id.
 *  In cases where a processor cannot access a certain shared memory region,
 *  that shared memory region should be left invalid for that processor.
 *  Note:  The {@link #numEntries} must be the same on all processors.
 *
 *  Each shared region contains the following:
 *  @p(blist)
 *  -base:          The base address
 *  -len:           The length
 *  -name:          The name of the region
 *  -isValid:       Whether the region is valid
 *  -ownerProcId:   The id of the processor which owns the region
 *  -cacheEnable:   Whether the region is cacheable
 *  -cacheLineSize: The cache line size
 *  -createHeap:    Whether a heap is created for the region.
 *  @p
 *
 *  A region is added statically using the {@link #setEntryMeta} API.
 *  The length of a region must be the same across all processors.
 *  The owner of the region can be specified.  If specified, the owner
 *  manages the shared region.  It creates a HeapMemMP instance which spans
 *  the full size of the region.  The other processors open the same HeapMemMP
 *  instance.
 *
 *  Note: Prior to calling Ipc_start(), If a SharedRegion's 'isValid'
 *  is true and 'createHeap' is true then the owner of the SharedRegion
 *  must be the same as the owner of SharedRegion 0.
 *
 *  An example of a SharedRegion configuration is as follows:
 *
 *  @p(code)
 *
 * var SharedRegion = xdc.useModule('ti.sdo.ipc.SharedRegion');
 * SharedRegion.setEntryMeta(0,
 *     { base: 0x80000000,
 *       len: 0x20000,
 *       ownerProcId: 0,
 *       isValid: true,
 *       cacheLineSize: 64,
 *       name: "DDR2",
 *     });
 *
 *  @p
 *
 *  The shared region table along with a shared region pointer (SRPtr)
 *  is used to do address translation at runtime. The shared region
 *  pointer is a 32-bit portable pointer composed of an id and offset.
 *  The most significant bits of a SRPtr are used for the id.
 *  The id corresponds to the index of the entry in the table.
 *  The offset is the offset from the base of the shared memory region.
 *  The number of entries in the table determines the number of bits to
 *  use for the id.  Increasing the number of entries increases the
 *  range of ids but decreases the range of the offset.
 *
 *  Note:  Region 0 must be visible by all processors.  Region 0 is used for
 *         synchonizing the processors, creating the default GateMP, and
 *         creating Notify and MessageQ transport instances.  The HeapMemMP
 *         created in Region 0 is the length of the region minus memory
 *         reserved for creating these internal instances.
 *
 *  Refer to the doxygen documentation for run-time API documenation.
 *
 */

module SharedRegion
{
    /*!
     *  ======== RegionView ========
     *  @_nodoc
     */
    metaonly struct RegionView {
        UInt16       id;
        String       base;
        String       end;
        String       len;
        UInt16       ownerProcId;
        Bool         cacheEnable;
        Bool         isValid;
        UInt16       cacheLineSize;
        SizeT        reservedSize;
        Ptr          heap;
        String       name;
    };

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Regions',
                    {
                        type: xdc.rov.ViewInfo.MODULE_DATA,
                        viewInitFxn: 'viewInitRegions',
                        structName: 'RegionView'
                    }
                ]
            ]
        });

    /*!
     *  Definition of shared region pointer type
     */
    typedef Bits32 SRPtr;

    /*!
     *  Assert raised when the id is larger than numEntries.
     */
    config xdc.runtime.Assert.Id A_idTooLarge =
        {msg: "A_idTooLarge: id cannot be larger than numEntries"};

    /*!
     *  Assert raised when an address is out of the range of the region id.
     */
    config xdc.runtime.Assert.Id A_addrOutOfRange =
        {msg: "A_addrOutOfRange: Address is out of region id's range"};

    /*!
     *  Assert raised when attempting to clear region 0
     */
    config xdc.runtime.Assert.Id A_region0Clear =
        {msg: "A_region0Clear: Region 0 cannot be cleared"};

    /*!
     *  Assert raised when region zero is invalid
     */
    config xdc.runtime.Assert.Id A_region0Invalid =
        {msg: "A_region0Invalid: Region zero is invalid"};

    /*!
     *  Assert raised when region is invalid
     */
    config xdc.runtime.Assert.Id A_regionInvalid =
        {msg: "A_regionInvalid: Region is invalid"};

    /*!
     *  Assert raised when the trying to reserve too much memory.
     */
    config xdc.runtime.Assert.Id A_reserveTooMuch =
        {msg: "A_reserveTooMuch: Trying to reserve too much memory"};

    /*!
     *  Assert raised when cache enabled but cache line size = 0.
     */
    config xdc.runtime.Assert.Id A_cacheLineSizeIsZero =
        {msg: "A_cacheLineSizeIsZero: cache line size cannot be zero"};

    /*!
     *  Assert raised when a new entry overlaps an existing one.
     */
    config xdc.runtime.Assert.Id A_overlap  =
        {msg: "A_overlap: Shared region overlaps"};

    /*!
     *  Assert raised when a valid table entry already exists.
     */
    config xdc.runtime.Assert.Id A_alreadyExists =
        {msg: "A_alreadyExists: Trying to overwrite an existing valid entry"};

    /*!
     *  Assert raised when trying to use a heap for a region that has no heap
     */
    config xdc.runtime.Assert.Id A_noHeap =
        {msg: "A_noHeap: Region has no heap"};

    /*!
     *  ======== Entry ========
     *  Structure for specifying a region.
     *
     *  Each region entry should not overlap with any other entry.  The
     *  length of a region should be the same across all processors.
     *
     *  During static configuration, the 'isValid' field can be set to 'false'
     *  to signify a partially completed entry.  This should only be done
     *  if the base address of the entry is not known during static
     *  configuration.  The entry can be completed and the
     *  'isValid' field can be set to true at runtime.
     *
     *  @field(base)          The base address.
     *  @field(len)           The length.
     *  @field(ownerProcId)   MultiProc id of processor that manages region.
     *  @field(isValid)       Whether the region is valid or not.
     *  @field(cacheEnable)   Whether the region is cacheable.
     *  @field(cacheLineSize) The cache line size for the region.
     *  @field(createHeap)    Whether a heap is created for the region.
     *  @field(name)          The name associated with the region.
     */
    struct Entry {
        Ptr    base;
        SizeT  len;
        UInt16 ownerProcId;
        Bool   isValid;
        Bool   cacheEnable;
        SizeT  cacheLineSize;
        Bool   createHeap;
        String name;
    };

    /*! Specifies the invalid id */
    const UInt16 INVALIDREGIONID = 0xFFFF;

    /*! Specifies the default owner proc id */
    const UInt16 DEFAULTOWNERID = ~0;

    /*!
     *  Worst-case cache line size
     *
     *  This is the default system cache line size for all modules.
     *  When a module puts structures in shared memory, this value is
     *  used to make sure items are aligned on a cache line boundary.
     *  If no cacheLineSize is specified for a region, it will use this
     *  value.
     */
    config SizeT cacheLineSize = 128;

    /*!
     *  The number of shared region table entries.
     *
     *  This value is used for calculating the number of bits for the offset.
     *  Note: This value must be the same across all processors in the system.
     *        Increasing this parameter will increase the footprint and
     *        the time for translating a pointer to a SRPtr.
     */
    config UInt16 numEntries = 4;

    /*!
     *  Determines whether address translation is required.
     *
     *  This configuration parameter should be set to 'false' if and only if all
     *  shared memory regions have the same base address for all processors.
     *  If 'false', it results in a fast {@link #getPtr} and {@link #getSRPtr},
     *  because a SRPtr is equivalent to a Ptr and no translation is done.
     */
    config Bool translate = true;

    /*! @_nodoc
     *  Value that corresponds to NULL in SRPtr address space.
     */
    config SRPtr INVALIDSRPTR = 0xFFFFFFFF;

    /*! @_nodoc
     *  ======== attach ========
     *  Opens a heap, for non-owner processors, for each SharedRegion.
     *
     *  Function is called in Ipc_attach().
     */
    Int attach(UInt16 remoteProcId);

    /*! @_nodoc
     *  ======== clearReservedMemory ========
     *  Clears the reserve memory for each region in the table.
     */
    Void clearReservedMemory();

    /*! @_nodoc
     *  ======== detach ========
     *  Close the heap, for non-owner processors when detaching from the owner.
     *
     *  Function is called in Ipc_detach().
     */
    Int detach(UInt16 remoteProcId);

    /*!
     *  ======== genSectionInCmd ========
     *  Enable/Disable generation of output section in linker cmd file
     *
     *  This function can be called for each shared region to not generate
     *  an output section in the linker command file.  By default all shared
     *  region entries generate an output section in the linker command file.
     *
     *  @param(id)          Region id.
     *  @param(gen)         TRUE - generate, FALSE - don't generate
     */
    metaonly Void genSectionInCmd(UInt16 id, Bool gen);

    /*!
     *  ======== getCacheLineSizeMeta ========
     *  Meta version of Ipc_getCacheLineSize
     */
    metaonly SizeT getCacheLineSizeMeta(UInt16 id);

    /*! @_nodoc
     *  ======== getIdMeta ========
     *  Returns the region id for a given local address
     *
     *  @param(addr)    Address to retrieve the shared region pointer.
     *
     *  @b(returns)     region id
     */
    metaonly UInt16 getIdMeta(Ptr addr);

    /*! @_nodoc
     *  ======== getPtrMeta ========
     *  Meta version of {@link #getPtr}
     */
    metaonly Ptr getPtrMeta(SRPtr srptr);

    /*! @_nodoc
     *  ======== getPtrMeta$view ========
     *  ROV-time version of getPtrMeta
     *
     *  @param(srptr)   Shared region pointer.
     *
     *  @b(returns)     Pointer associated with shared region pointer.
     */
    metaonly Ptr getPtrMeta$view(SRPtr srptr);

    /*! @_nodoc
     *  ======== getSRPtrMeta ========
     *  Meta version of {@link #getSRPtr}
     */
    metaonly SRPtr getSRPtrMeta(Ptr addr);

    /*! @_nodoc
     *  ======== getSRPtrMeta$view ========
     *  ROV-time version of getSRPtrMeta
     *
     *  @param(addr)    Address to retrieve the shared region pointer.
     *
     *  @b(returns)     Shared region pointer.
     */
    metaonly SRPtr getSRPtrMeta$view(Ptr addr);

    /*! @_nodoc
     *  ======== isCacheEnabledMeta ========
     *  Meta version of {@link #isCacheEnabled}
     */
    metaonly Bool isCacheEnabledMeta(UInt16 id);

    /*! @_nodoc
     *  ======== reserveMemory ========
     *  Reserves the specified amount of memory from the specified region id.
     *
     *  Must be called before Ipc_start().  The amount of memory reserved
     *  must be the same on all cores.
     *  The return pointer is the starting address that was reserved.
     *
     *  @param(id)      Region id.
     *  @param(size)    Amount of memory to reserve.
     *
     *  @b(returns)     Starting address of memory reserved.
     */
    Ptr reserveMemory(UInt16 id, SizeT size);

    /*! @_nodoc
     *  ======== resetInternalFields ========
     *  Reset the internal fields of a region.
     *
     *  This function is called in Ipc_stop() to reset the reservedSize
     *  and heap handle.  It should not be called by the user.
     *
     *  @param(id)      Region id.
     */
    Void resetInternalFields(UInt16 id);

    /*!
     *  ======== setEntryMeta ========
     *  Sets the entry at the specified region id in the shared region table.
     *
     *  The required parameters are base and len. All the other fields will
     *  get their default if not specified.
     *
     *  @param(id)          Region id.
     *  @param(entry)       Entry fields about the region.
     */
    metaonly Void setEntryMeta(UInt16 id, Entry entry);

    /*! @_nodoc
     *  ======== start ========
     *  Creates a heap by owner of region for each SharedRegion.
     *
     *  Function is called by Ipc_start().  Requires that SharedRegion 0
     *  be valid before calling start().
     */
    Int start();

    /*! @_nodoc
     *  ======== stop ========
     *  Undo what was done by start.
     *
     *  This function is called by Ipc_stop().  It deletes any heap that
     *  was created in start for the owner of any SharedRegion.  For
     *  non-owners, it doesn't do anything.
     */
    Int stop();


internal:

    const UInt32 CREATED = 0x08111963;

    /* Information stored on a per region basis */
    struct Region {
        Entry        entry;
        SizeT        reservedSize;
        IHeap.Handle heap;
    };

    /* temporary storage of shared regions */
    metaonly config Entry entry[];

    /* generate linker section for shared regions */
    metaonly config Bool genSectionInLinkCmd[];

    /* internal to keep track of the number of entries added */
    metaonly config UInt entryCount;

    /* number of bits for the offset for a SRPtr. This value is calculated */
    config UInt32 numOffsetBits;

    /* offset bitmask using for generating a SRPtr */
    config UInt32 offsetMask;

    /*
     *  ======== checkOverlap ========
     *  Determines if there is an overlap with an existing entry
     *
     *  @param(base)    Base address of the region
     *  @param(len)     Size of the region
     *
     *  @b(returns)     Status if successful or not.
     */
    Int checkOverlap(Ptr base, SizeT len);

    /*
     *  ======== Module State structure ========
     *  The regions array contains information for each shared region entry.
     *  The size of the table will be determined by the number of entries.
     */
    struct Module_State {
        Region      regions[];
    };
}
