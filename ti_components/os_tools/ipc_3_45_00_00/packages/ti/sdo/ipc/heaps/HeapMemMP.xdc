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
 *  ======== HeapMemMP.xdc ========
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
 *  ======== HeapMemMP ========
 *  Multi-processor variable size buffer heap implementation.
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/HeapMemMP.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg) if runtime APIs will be used in the application:
 *
 *  <PRE>HeapMemMP = xdc.useModule('ti.sdo.ipc.heaps.HeapMemMP');</PRE>
 *
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../../../doxygen/html/files.html">Doxygen documenation</A>
 *  for the IPC product.  However, the documentation presented on this page
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 */
@InstanceInitError   /* For NameServer_addUInt32                            */
@InstanceFinalize    /* For finalizing shared memory and removing NS entry  */

module HeapMemMP inherits xdc.runtime.IHeap {

    /*! @_nodoc */
    metaonly struct BasicView {
        String          name;
        Ptr             buf;
        Memory.Size     totalSize;
        String          objType;
        Ptr             gate;
    }

    /*! @_nodoc */
    metaonly struct DetailedView {
        String          name;
        Ptr             buf;
        Memory.Size     totalSize;
        String          objType;
        Ptr             gate;
        Ptr             attrs;
        Bool            cacheEnabled;
        Memory.Size     totalFreeSize;
        Memory.Size     largestFreeSize;
    }

    /*! @_nodoc */
    metaonly struct FreeBlockView {
        String          address;
        String          label;
        String          size;
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
                'Detailed',
                {
                    type: ViewInfo.INSTANCE,
                    viewInitFxn: 'viewInitDetailed',
                    structName: 'DetailedView'
                }
            ],
            [
                'FreeList',
                {
                    type: ViewInfo.INSTANCE_DATA,
                    viewInitFxn: 'viewInitData',
                    structName: 'FreeBlockView'
                }
            ]
            ]
        });

    /*!
     *  ======== ExtendedStats ========
     *  Stats structure for the getExtendedStats API.
     *
     *  @field(buf)           Local address of the shared buffer
     *                        This may be different from the original buf
     *                        parameter due to alignment requirements.
     *  @field(size)          Size of the shared buffer.
     *                        This may be different from the original size
     *                        parameter due to alignment requirements.
     */
    struct ExtendedStats {
        Ptr   buf;
        SizeT size;
    }

    /*!
     *  Assert raised when a block of size 0 is requested.
     */
    config Assert.Id A_zeroBlock =
        {msg: "A_zeroBlock: Cannot allocate size 0"};

    /*!
     *  Assert raised when the requested heap size is too small.
     */
    config Assert.Id A_heapSize =
        {msg: "A_heapSize: Requested heap size is too small"};

    /*!
     *  Assert raised when the requested alignment is not a power of 2.
     */
    config Assert.Id A_align =
        {msg: "A_align: Requested align is not a power of 2"};

    /*!
     *  Assert raised when the free detects that an invalid addr or size.
     *
     *  This could arise when multiple frees are done on the same buffer or
     *  if corruption occurred.
     *
     *  This also could occur when an alloc is made with size N and the
     *  free for this buffer specifies size M where M > N. Note: not every
     *  case is detectable.
     *
     *  This assert can also be caused when passing an invalid addr to free
     *  or if the size is causing the end of the buffer to be
     *  out of the expected range.
     */
    config Assert.Id A_invalidFree =
        {msg: "A_invalidFree: Invalid free"};

    /*!
     *  Raised when requested size exceeds largest free block.
     */
    config Error.Id E_memory =
        {msg: "E_memory: Out of memory: handle=0x%x, size=%u"};

    /*!
     *  Maximum runtime entries
     *
     *  Maximum number of HeapMemMP's that can be dynamically created and
     *  added to the NameServer.
     *
     *  To minimize the amount of runtime allocation, this parameter allows
     *  the pre-allocation of memory for the HeapMemMP's NameServer table.
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
     *  Name of this instance.
     *
     *  The name (if not NULL) must be unique among all HeapMemMP
     *  instances in the entire system.  When creating a new
     *  heap, it is necessary to supply an instance name.
     */
    config String name = null;

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

    /*!
     *  Size of {@link #sharedBuf}
     *
     *  This is the size of the buffer to be used in the HeapMemMP instance.
     *  The actual buffer size in the created instance might actually be less
     *  than the value supplied in 'sharedBufSize' because of alignment
     *  constraints.
     *
     *  It is important to note that the total amount of shared memory required
     *  for a HeapMemMP instance will be greater than the size supplied here.
     *  Additional space will be consumed by shared instance attributes and
     *  alignment-related padding.  Use the {@link #sharedMemReq} or the
     *  {@link #sharedMemReqMeta} call to determine the exact amount of shared
     *  memory required for an instance for a given sharedBufSize and cache
     *  settings.
     */
    config SizeT sharedBufSize = 0;

    /*!
     *  ======== getStats ========
     *  @a(HeapMemMP)
     *  getStats() will lock the heap using the HeapMemMP Gate while it retrieves
     *  the HeapMemMP's statistics.
     *
     *  The returned totalSize reflects the usable size of the buffer, not
     *  necessarily the size specified during create.
     */
    @DirectCall
    override Void getStats(xdc.runtime.Memory.Stats *stats);

    @DirectCall
    override Ptr alloc(SizeT size, SizeT align, xdc.runtime.Error.Block *eb);

    @DirectCall
    override Void free(Ptr block, SizeT size);

internal:

    /*! Used in the attrs->status field */
    const UInt32 CREATED    = 0x07041776;

    /*!
     *  This Params object is used for temporary storage of the
     *  module wide parameters that are for setting the NameServer instance.
     */
    metaonly config NameServer.Params nameSrvPrms;

    /*! Initialize shared memory, adjust alignment, allocate memory for buf */
    Void postInit(Object *obj, Error.Block *eb);

    /*!
     * Header maintained at the lower address of every free block. The size of
     * this struct must be a power of 2
     */
    struct Header {
        SharedRegion.SRPtr  next;  /* SRPtr to next header (Header *)    */
        Bits32              size;  /* Size of this segment (Memory.size) */
    };

    /*! Structure of attributes in shared memory */
    struct Attrs {
        Bits32                  status;     /* Version number                */
        SharedRegion.SRPtr      bufPtr;     /* SRPtr to buf                  */
        Header                  head;       /* First free block pointer.     */
                                            /* The size field will be used   */
                                            /* to store original heap size.  */
        SharedRegion.SRPtr      gateMPAddr; /* GateMP SRPtr                  */
    }

    struct Instance_State {
        Attrs               *attrs;         /* Local pointer to attrs        */
        GateMP.Handle       gate;           /* Gate for critical regions     */
        Ipc.ObjType         objType;        /* Static/Dynamic? open/creator? */
        Ptr                 nsKey;          /* Used to remove NS entry       */
        Bool                cacheEnabled;   /* Whether to do cache calls     */
        UInt16              regionId;       /* SharedRegion index            */
        SizeT               allocSize;      /* Shared memory allocated       */
        Char                *buf;           /* Local pointer to buf          */
        SizeT               minAlign;       /* Minimum alignment required    */
        SizeT               bufSize;        /* Size of usable buffer         */
    };

    struct Module_State {
        NameServer.Handle       nameServer;
    };
}
