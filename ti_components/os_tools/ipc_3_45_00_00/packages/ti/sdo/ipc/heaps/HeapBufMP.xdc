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
 *  ======== HeapBufMP.xdc ========
 *
 */

package ti.sdo.ipc.heaps;

import ti.sdo.ipc.ListMP;
import ti.sdo.ipc.SharedRegion;
import ti.sdo.ipc.Ipc;
import ti.sdo.ipc.GateMP;
import ti.sdo.utils.NameServer;

import xdc.rov.ViewInfo;

import xdc.runtime.Error;
import xdc.runtime.Assert;

/*!
 *  ======== HeapBufMP ========
 *  Multi-processor fixed-size buffer heap implementation
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/HeapBufMP.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>HeapBufMP = xdc.useModule('ti.sdo.ipc.heaps.HeapBufMP');</PRE>
 *
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../../../doxygen/html/files.html">Doxygen documenation</A>
 *  for the IPC product.  However, the documentation presented on this page
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 *
 *  It is important to note that allocation tracking is disabled by default in
 *  {@link #trackAllocs}.  Disabling allocation tracking improves alloc/free
 *  performance especially when cache calls are required in shared memory.
 */

@InstanceInitError
@InstanceFinalize

module HeapBufMP inherits xdc.runtime.IHeap
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String      name;
        Ptr         buf;
        String      objType;
        Ptr         gate;
        Bool        exact;
        SizeT       align;
        SizeT       blockSize;
        UInt        numBlocks;
        UInt        curAllocated;
        UInt        maxAllocated;
        Ptr         freeList;
    }

    /*! @_nodoc */
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                [
                    'Basic',
                    {
                        type: ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ]
            ]
        });

    /*!
     *  Assert raised when freeing a block that is not in the buffer's range
     */
    config Assert.Id A_invBlockFreed =
        {msg: "A_invBlockFreed: Invalid block being freed"};

    /*!
     *  Assert raised when freeing a block that isn't aligned properly
     */
    config Assert.Id A_badAlignment =
        {msg: "A_badAlignment: Block being freed is not aligned properly "};

    /*!
     *  Error raised when a requested alloc size is too large
     */
    config Error.Id E_sizeTooLarge =
        {msg: "E_sizeTooLarge: Requested alloc size of %u is greater than %u"};

    /*!
     *  Error raised when a requested alignment is too large
     */
    config Error.Id E_alignTooLarge =
        {msg: "E_alignTooLarge: Requested alignment size of %u is greater than %u"};

    /*!
     *  Error raised when exact matching failed
     */
    config Error.Id E_exactFail =
        {msg: "E_exactFail: Exact allocation failed (requested size = %u and buffer size = %u)"};

    /*!
     *  Error raised when there are no more blocks left in the buffer
     */
    config Error.Id E_noBlocksLeft =
        {msg: "E_noBlocksLeft: No more blocks left in buffer (handle = 0x%x, requested size = %u)"};

    /*!
     *  Maximum runtime entries
     *
     *  Maximum number of HeapBufMP's that can be dynamically created and
     *  added to the NameServer.
     *
     *  To minimize the amount of runtime allocation, this parameter allows
     *  the pre-allocation of memory for the HeapBufMP's NameServer table.
     *  The default is to allow growth (i.e. memory allocation when
     *  creating a new instance).
     */
    metaonly config UInt maxRuntimeEntries = NameServer.ALLOWGROWTH;

    /*!
     *  Maximum length for heap names
     */
    config UInt maxNameLen = 32;

    /*!
     *  Section name is used to place the names table
     *
     *  The default value of NULL implies that no explicit placement is
     *  performed.
     */
    metaonly config String tableSection = null;

    /*!
     *  Track the number of allocated blocks
     *
     *  This will enable/disable the tracking of the current and maximum number
     *  of allocations for a HeapBufMP instance.  This maximum refers to the
     *  "all time" maximum number of allocations for the history of a HeapBufMP
     *  instance.
     *
     *  Tracking allocations might adversely affect performance when allocating
     *  and/or freeing.  This is especially true if cache is enabled for the
     *  shared region.  If this feature is not needed, setting this to false
     *  avoids the performance penalty.
     */
    config Bool trackAllocs = false;

instance:

    /*!
     *  GateMP used for critical region management of the shared memory
     *
     *  Using the default value of NULL will result in use of the GateMP
     *  system gate for context protection.
     */
    config GateMP.Handle gate = null;

    /*! @_nodoc
     *  Set to TRUE by the open() call. No one else should touch this!
     */
    config Bool openFlag = false;

    /*!
     *  Use exact matching
     *
     *  Setting this flag will allow allocation only if the requested size
     *  is equal to (rather than less than or equal to) the buffer's block
     *  size.
     */
    config Bool exact = false;

    /*!
     *  Name of this instance.
     *
     *  The name (if not NULL) must be unique among all HeapBufMP
     *  instances in the entire system.  When creating a new
     *  heap, it is necessary to supply an instance name.
     */
    config String name = null;

    /*!
     *  Alignment (in MAUs) of each block.
     *
     *  The alignment must be a power of 2. If the value 0 is specified,
     *  the value will be changed to meet the minimum structure alignment
     *  requirements (refer to
     *  {@link xdc.runtime.Memory#getMaxDefaultTypeAlign} and
     *  {@link xdc.runtime.Memory#getMaxDefaultTypeAlignMeta} and
     *  the cache alignment size of the region in which the heap will
     *  be placed.  Therefore, the actual alignment may be larger.
     *
     *  The default alignment is 0.
     */
    config SizeT align = 0;

    /*!
     *  Number of fixed-size blocks.
     *
     *  This is a required parameter for all new HeapBufMP instances.
     */
    config UInt numBlocks = 0;

    /*!
     *  Size (in MAUs) of each block.
     *
     *  HeapBufMP will round the blockSize up to the nearest multiple of the
     *  alignment, so the actual blockSize may be larger. When creating a
     *  HeapBufMP dynamically, this needs to be taken into account to determine
     *  the proper buffer size to pass in.
     *
     *  Required parameter.
     *
     *  The default size of the blocks is 0 MAUs.
     */
    config SizeT blockSize = 0;

    /*!
     *  Shared region ID
     *
     *  The index corresponding to the shared region from which shared memory
     *  will be allocated.
     */
    config UInt16 regionId = 0;

    /*! @_nodoc
     *  Physical address of the shared memory
     *
     *  This value can be left as 'null' unless it is required to place the
     *  heap at a specific location in shared memory.  If sharedAddr is null,
     *  then shared memory for a new instance will be allocated from the
     *  heap belonging to the region identified by {@link #regionId}.
     */
    config Ptr sharedAddr = null;

    @DirectCall
    override Ptr alloc(SizeT size, SizeT align, xdc.runtime.Error.Block *eb);

    @DirectCall
    override Void free(Ptr block, SizeT size);

internal:

    /*! Used in the attrs->status field */
    const UInt32 CREATED = 0x05251995;

    /*!
     *  This Params object is used for temporary storage of the
     *  module wide parameters that are for setting the NameServer instance.
     */
    metaonly config NameServer.Params nameSrvPrms;

    /*! slice and dice the buffer */
    Void postInit(Object *obj, Error.Block *eb);

    /*! Structure of attributes in shared memory */
    struct Attrs {
        Bits32              status;
        SharedRegion.SRPtr  gateMPAddr;     /* GateMP SRPtr (shm safe)       */
        SharedRegion.SRPtr  bufPtr;         /* Memory managed by instance    */
        Bits32              numFreeBlocks;  /* Number of free blocks         */
        Bits32              minFreeBlocks;  /* Min number of free blocks     */
        Bits32              blockSize;      /* True size of each block       */
        Bits32              align;          /* Alignment of each block       */
        Bits32              numBlocks;      /* Number of individual blocks.  */
        Bits16              exact;          /* For 'exact' allocation        */
    }

    struct Instance_State {
        Attrs               *attrs;
        GateMP.Handle       gate;           /* Gate for critical regions     */
        Ipc.ObjType         objType;        /* See enum ObjType              */
        Ptr                 nsKey;          /* Used to remove NS entry       */
        Bool                cacheEnabled;   /* Whether to do cache calls     */
        UInt16              regionId;       /* SharedRegion index            */
        SizeT               allocSize;      /* Shared memory allocated       */
        Char                *buf;           /* Local pointer to buf          */
        ListMP.Handle       freeList;       /* List of free buffers          */
        SizeT               blockSize;      /* Adjusted blockSize            */
        SizeT               align;          /* Adjusted alignment            */
        UInt                numBlocks;      /* Number of blocks in buffer    */
        Bool                exact;          /* Exact match flag              */
    };

    struct Module_State {
        NameServer.Handle   nameServer;     /* NameServer for this module    */
    };
}
