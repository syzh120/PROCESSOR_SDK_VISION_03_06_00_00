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
 *  ======== HeapMultiBufMP.xdc ========
 *
 *
 */

package ti.sdo.ipc.heaps;

import ti.sdo.ipc.SharedRegion;
import ti.sdo.ipc.Ipc;
import ti.sdo.ipc.GateMP;
import ti.sdo.utils.NameServer;

import xdc.rov.ViewInfo;    /* Display local/shared state + FreeBlockView */

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.Memory;
import xdc.runtime.Startup;

/*!
 *  ======== HeapMultiBufMP ========
 *  Multi-processor fixed-size buffer heap implementation
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/HeapMultiBufMP.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>HeapMultiBufMP = xdc.useModule('ti.sdo.ipc.heaps.HeapMultiBufMP');
 *  </PRE>
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
 *  It is important to note that max allocation tracking is disabled by default
 *  in {@link #trackMaxAllocs}.  Disabling allocation tracking improves alloc/
 *  free performance especially when cache calls are required in shared memory.
 */
@InstanceInitError
@InstanceFinalize

module HeapMultiBufMP inherits xdc.runtime.IHeap
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String          name;
        Ptr             buf;
        Memory.Size     totalSize;
        String          objType;
        Ptr             gate;
        Bool            exact;
    }

    /*! @_nodoc */
    metaonly struct BucketsView {
        Ptr             baseAddr;
        UInt            blockSize;
        UInt            align;
        UInt            numBlocks;
        UInt            numFreeBlocks;
        UInt            minFreeBlocks;
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
            ],
            [
                'Buffer Information',
                {
                    type: ViewInfo.INSTANCE_DATA,
                    viewInitFxn: 'viewInitData',
                    structName: 'BucketsView'
                }
            ],
            ]
        });

    /*!
     *  Structure for bucket configuration
     *
     *  An array of buckets is a required parameter to create any
     *  HeapMultiBufMP instance.  The fields of each bucket correspond
     *  to the attributes of each buffer in the HeapMultiBufMP.  The actual
     *  block sizes and alignments may be adjusted per the process described
     *  at {@link #bucketEntries}.
     *
     *  @field(blockSize)       Size of each block (in MADUs)
     *  @field(numBlocks)       Number of blocks
     *  @field(align)           Alignment of each block (in MADUs)
     */
    struct Bucket {
        SizeT       blockSize;
        UInt        numBlocks;
        SizeT       align;
    }

    /*!
     *  ======== ExtendedStats ========
     *  Stats structure for the getExtendedStats API.
     *
     *  @field(numBuckets)         Number of buckets
     *  @field(numBlocks)          Number of blocks in each buffer
     *  @field(blockSize)          Block size of each buffer
     *  @field(align)              Alignment of each buffer
     *  @field(maxAllocatedBlocks) The maximum number of blocks allocated from
     *                             this heap at any single point in time during
     *                             the lifetime of this HeapMultiBufMP instance
     *
     *  @field(numAllocatedBlocks) The total number of blocks currently
     *                             allocated in this HeapMultiBufMP instance
     */
    struct ExtendedStats {
        UInt numBuckets;
        UInt numBlocks          [8];
        UInt blockSize          [8];
        UInt align              [8];
        UInt maxAllocatedBlocks [8];
        UInt numAllocatedBlocks [8];
    }

    /*!
     *  Assert raised when the align parameter is not a power of 2.
     */
    config Assert.Id A_invalidAlign =
        {msg: "align parameter must be a power of 2"};

    /*!
     *  Assert raised when an invalid buffer size was passed to free()
     */
    config Assert.Id A_sizeNotFound =
        {msg: "an invalid buffer size was passed to free"};

    /*!
     *  Assert raised when an invalid block address was passed to free()
     */
    config Assert.Id A_addrNotFound =
        {msg: "an invalid buffer address was passed to free"};

    /*!
     *  Error raised when exact matching failed
     */
    config Error.Id E_exactFail =
        {msg: "E_exactFail: Exact allocation failed (requested size = %u and buffer size = %u)"};

    /*!
     *  Error raised when requested size exceeds all blockSizes.
     */
    config Error.Id E_size =
        {msg: "E_size: requested size/alignment is too big (requested size = %u and requested align = %u)"};

    /*!
     *  Error raised when there are no blocks left in the buffer corresponding to the requested size/alignment
     */
    config Error.Id E_noBlocksLeft =
        {msg: "E_noBlocksLeft: No more blocks left in buffer (buffer size = %u and buffer align = %u)"};

    /*!
     *  Maximum runtime entries
     *
     *  Maximum number of HeapMultiBufMP's that can be dynamically created and
     *  added to the NameServer.
     *
     *  To minimize the amount of runtime allocation, this parameter allows
     *  the pre-allocation of memory for the HeapMultiBufMP's NameServer table.
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
     *  Track the maximum number of allocated blocks
     *
     *  This will enable/disable the tracking of the maximum number of
     *  allocations for a HeapMultiBufMP instance.  This maximum refers to the
     *  "all time" maximum number of allocations for the history of a
     *  HeapMultiBufMP instance, not the current number of allocations.
     *
     *  Tracking the maximum might adversely affect performance when allocating
     *  and/or freeing. If this feature is not needed, setting this to false
     *  avoids the performance penalty.
     */
    config Bool trackMaxAllocs = false;

instance:

    /*!
     *  GateMP used for critical region management of the shared memory
     *
     *  Using the default value of NULL will result in use of the GateMP
     *  system gate for context protection.
     */
    config GateMP.Handle gate = null;

    /*! @_nodoc
     *   by the open() call. No one else should touch this!
     */
    config Bool openFlag = false;

    /*!
     *  Use exact matching
     *
     *  Setting this flag will allow allocation only if the requested size
     *  is equal to (rather than less than or equal to) a buffer's block size.
     */
    config Bool exact = false;

    /*!
     *  Name of this instance.
     *
     *  The name (if not NULL) must be unique among all HeapMultiBufMP
     *  instances in the entire system.  When creating a new
     *  heap, it is necessary to supply an instance name.
     */
    config String name = null;

    /*!
     *  Number of buckets in {@link #bucketEntries}
     *
     *  This parameter is required to create any instance.
     */
    config Int numBuckets = 0;

    /*!
     *  Bucket Entries
     *
     *  The bucket entries are an array of {@link #Bucket}s whose values
     *  correspond to the desired alignment, block size and length for each
     *  buffer.  It is important to note that the alignments and sizes for each
     *  buffer may be adjusted due to cache and alignment related constraints.
     *  Buffer sizes are rounded up by their corresponding alignments.  Buffer
     *  alignments themselves will assume the value of region cache alignment
     *  size when the cache size is greater than the requested buffer alignment.
     *
     *  For example, specifying a bucket with {blockSize: 192, align: 256} will
     *  result in a buffer of blockSize = 256 and alignment = 256.  If cache
     *  alignment is required, then a bucket of {blockSize: 96, align: 64} will
     *  result in a buffer of blockSize = 128 and alignment = 128 (assuming
     *  cacheSize = 128).
     */
    config Bucket bucketEntries[];

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
    const UInt32 CREATED = 0x05101920;

    /*!
     *  This Params object is used for temporary storage of the
     *  module wide parameters that are for setting the NameServer instance.
     */
    metaonly config NameServer.Params nameSrvPrms;

    /*! slice and dice the buffer */
    Void postInit(Object *obj, Error.Block *eb);

    /*!
     * Takes in modifiable array of bucket entries, performs an in-place sort
     * of the bucket entries, combines the entries as necessary, and returns
     * the new number of buckets in the combined entries
     */
    UInt processBuckets(Bucket *bucketEntries, Params *params,
                        UInt16 regionId);

    /*!
     * Add the block to the tail; index specifies the buffer number
     *
     * Precondition: inv obj->attrs->bucket[index]
     * Postcondition: wb obj->attrs->bucket[index] and wb the block
     */
    Void putTail(Object *obj, Int index, Elem *block);

    /*!
     * Removes a block from the head and returns it; index specifies
     * the buffer number. The block is invalidated before returned
     *
     * Precondition: inv obj->attrs->bucket[index]
     * Postcondition: wb obj->attrs->bucket[index]
     */
    Elem *getHead(Object *obj, Int index);

    /*! Needed for freelist */
    @Opaque struct Elem {
        /* must be volatile for whole_program */
        volatile SharedRegion.SRPtr next;
    };

    /*! Shared memory state for a single buffer. */
    struct BucketAttrs {
        SharedRegion.SRPtr  head;
        SharedRegion.SRPtr  tail;
        SharedRegion.SRPtr  baseAddr;
        Bits32              numFreeBlocks;
        Bits32              minFreeBlocks;
        Bits32              blockSize;
        Bits32              align;
        Bits32              numBlocks;
    }

    /*! Shared memory state for a HeapMultiBufMP instance */
    struct Attrs {
        Bits32              status;         /* Created stamp                 */
        SharedRegion.SRPtr  gateMPAddr;     /* GateMP SRPtr                  */
        Bits32              numBuckets;     /* Number of buffers             */
        BucketAttrs         buckets[8]; /* Buffer attributes        */
        Bits16              exact;          /* 1 = exact matching, 0 = no    */
    }

    struct Instance_State {
        Attrs               *attrs;         /* Shared state                  */
        GateMP.Handle       gate;           /* Gate for critical regions     */
        Ipc.ObjType         objType;        /* See enum ObjType              */
        Ptr                 nsKey;          /* Used to remove NS entry       */
        Bool                cacheEnabled;   /* Whether to do cache calls     */
        UInt16              regionId;       /* SharedRegion index            */
        SizeT               allocSize;      /* Shared memory allocated       */
        Char                *buf;           /* Local pointer to buf          */
        Bucket              bucketEntries[];/* Optimized bucketEntries       */
                                            /* NULL for dynamic instance     */
        UInt                numBuckets;     /* # of optimized entries        */
        Bool                exact;          /* Exact match flag              */
    };

    struct Module_State {
        NameServer.Handle   nameServer;
    };
}
