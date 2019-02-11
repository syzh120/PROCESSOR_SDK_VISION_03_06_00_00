/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== HeapBufMP.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>

#include <ti/sysbios/hal/Cache.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_NameServer.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/heaps/_HeapBufMP.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/_GateMP.h>
#include <ti/sdo/ipc/_ListMP.h>

#include "package/internal/HeapBufMP.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(HeapBufMP_Params_init);
    #pragma FUNC_EXT_CALLED(HeapBufMP_alloc);
    #pragma FUNC_EXT_CALLED(HeapBufMP_close);
    #pragma FUNC_EXT_CALLED(HeapBufMP_create);
    #pragma FUNC_EXT_CALLED(HeapBufMP_delete);
    #pragma FUNC_EXT_CALLED(HeapBufMP_free);
    #pragma FUNC_EXT_CALLED(HeapBufMP_getExtendedStats);
    #pragma FUNC_EXT_CALLED(HeapBufMP_getStats);
    #pragma FUNC_EXT_CALLED(HeapBufMP_open);
    #pragma FUNC_EXT_CALLED(HeapBufMP_openByAddr);
    #pragma FUNC_EXT_CALLED(HeapBufMP_sharedMemReq);
#endif

/*
 *  ======== HeapBufMP_getSharedParams ========
 */
static Void HeapBufMP_getSharedParams(HeapBufMP_Params *sparams,
    const ti_sdo_ipc_heaps_HeapBufMP_Params *params)
{
    sparams->gate        = (GateMP_Handle)params->gate;
    sparams->name        = params->name;
    sparams->regionId    = params->regionId;
    sparams->sharedAddr  = params->sharedAddr;
    sparams->align       = params->align;
    sparams->numBlocks   = params->numBlocks;
    sparams->blockSize   = params->blockSize;
    sparams->exact       = params->exact;
}

/*
 *  ======== HeapBufMP_getRTSCParams ========
 */
static Void HeapBufMP_getRTSCParams(
    ti_sdo_ipc_heaps_HeapBufMP_Params *params,
    const HeapBufMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapBufMP_Params_init(params);

    params->gate        = (ti_sdo_ipc_GateMP_Handle)sparams->gate;
    params->name        = sparams->name;
    params->regionId    = sparams->regionId;
    params->sharedAddr  = sparams->sharedAddr;
    params->align       = sparams->align;
    params->numBlocks   = sparams->numBlocks;
    params->blockSize   = sparams->blockSize;
    params->exact       = sparams->exact;
}

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== HeapBufMP_Params_init ========
 */
Void HeapBufMP_Params_init(HeapBufMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapBufMP_Params params;

    ti_sdo_ipc_heaps_HeapBufMP_Params_init(&params);
    HeapBufMP_getSharedParams(sparams, &params);
}

/*
 *  ======== HeapBufMP_alloc ========
 */
Ptr HeapBufMP_alloc(HeapBufMP_Handle handle,
                      SizeT size,
                      SizeT align)
{
    Error_Block eb;

    Error_init(&eb);

    return (ti_sdo_ipc_heaps_HeapBufMP_alloc(
            (ti_sdo_ipc_heaps_HeapBufMP_Object *)handle, size, align, &eb));
}

/*
 *  ======== HeapBufMP_close ========
 */
Int HeapBufMP_close(HeapBufMP_Handle *handlePtr)
{
    HeapBufMP_delete(handlePtr);

    return (HeapBufMP_S_SUCCESS);
}

/*
 *  ======== HeapBufMP_create ========
 */
HeapBufMP_Handle HeapBufMP_create(const HeapBufMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapBufMP_Params params;
    ti_sdo_ipc_heaps_HeapBufMP_Object *obj;
    Error_Block eb;

    Error_init(&eb);

    if (sparams != NULL) {
        HeapBufMP_getRTSCParams(&params, (Ptr)sparams);

        /* call the module create */
        obj = ti_sdo_ipc_heaps_HeapBufMP_create(&params, &eb);
    }
    else {
        obj = ti_sdo_ipc_heaps_HeapBufMP_create(NULL, &eb);
    }

    return ((HeapBufMP_Handle)obj);
}

/*
 *  ======== HeapBufMP_delete ========
 */
Int HeapBufMP_delete(HeapBufMP_Handle *handlePtr)
{
    ti_sdo_ipc_heaps_HeapBufMP_delete(
            (ti_sdo_ipc_heaps_HeapBufMP_Handle *)handlePtr);

    return (HeapBufMP_S_SUCCESS);
}

/*
 *  ======== HeapBufMP_free ========
 */
Void HeapBufMP_free(HeapBufMP_Handle handle, Ptr addr, SizeT size)
{
    ti_sdo_ipc_heaps_HeapBufMP_free(
        (ti_sdo_ipc_heaps_HeapBufMP_Object *)handle, addr, size);
}
/*
 *  ======== HeapBufMP_getExtendedStats ========
 */
Void HeapBufMP_getExtendedStats(HeapBufMP_Handle handle,
                                HeapBufMP_ExtendedStats *stats)
{
    IArg key;
    ti_sdo_ipc_heaps_HeapBufMP_Object *obj =
            (ti_sdo_ipc_heaps_HeapBufMP_Object *)handle;

    key = GateMP_enter((GateMP_Handle)obj->gate);

    /* Make sure the attrs are not in cache */
    if (obj->cacheEnabled) {
        Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                Cache_Type_ALL, TRUE);
    }

    /*
     *  The maximum number of allocations for this HeapBufMP (for any given
     *  instance of time during its liftime) is computed as follows:
     *
     *  maxAllocatedBlocks = obj->numBlocks - obj->minFreeBlocks
     *
     *  Note that maxAllocatedBlocks is *not* the maximum allocation count, but
     *  rather the maximum allocations seen at any snapshot of time in the
     *  HeapBufMP instance.
     */

    /* if nothing has been alloc'ed yet, return 0 */
    if ((Int)(obj->attrs->minFreeBlocks) == -1) {
        stats->maxAllocatedBlocks = 0;
    }
    else {
        stats->maxAllocatedBlocks = obj->attrs->numBlocks -
                              obj->attrs->minFreeBlocks;
    }

    /* current # of alloc'ed blocks is computed using curr # of free blocks */
    stats->numAllocatedBlocks = obj->attrs->numBlocks -
            obj->attrs->numFreeBlocks;

    GateMP_leave((GateMP_Handle)obj->gate, key);
}

/*
 *  ======== HeapBufMP_getStats ========
 */
Void HeapBufMP_getStats(HeapBufMP_Handle handle, Ptr stats)
{
    ti_sdo_ipc_heaps_HeapBufMP_getStats(
            (ti_sdo_ipc_heaps_HeapBufMP_Handle)handle,
            (Memory_Stats *)stats);
}
/*
 *  ======== HeapBufMP_open ========
 */
Int HeapBufMP_open(String name,
                   HeapBufMP_Handle *handlePtr)
{
    SharedRegion_SRPtr sharedShmBase;
    Int status;
    Ptr sharedAddr;
    Error_Block eb;

    Error_init(&eb);

    /* Assert that a pointer has been supplied */
    Assert_isTrue(handlePtr != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    /* Assert that a name has been supplied */
    Assert_isTrue(name != NULL, ti_sdo_ipc_Ipc_A_invParam);

    /* Open by name */
    status = NameServer_getUInt32(
            (NameServer_Handle)HeapBufMP_module->nameServer, name,
            &sharedShmBase, MultiProc_getClusterProcList());

    if (status < 0) {
        /* Name not found. */
        *handlePtr = NULL;
        return (HeapBufMP_E_NOTFOUND);
    }

    sharedAddr = SharedRegion_getPtr(sharedShmBase);

    status = HeapBufMP_openByAddr(sharedAddr, handlePtr);

    return (status);
}

/*
 *  ======== HeapBufMP_openByAddr ========
 */
Int HeapBufMP_openByAddr(Ptr sharedAddr,
                         HeapBufMP_Handle *handlePtr)
{
    ti_sdo_ipc_heaps_HeapBufMP_Params params;
    ti_sdo_ipc_heaps_HeapBufMP_Attrs *attrs;
    Int status;
    Error_Block eb;

    Error_init(&eb);

    ti_sdo_ipc_heaps_HeapBufMP_Params_init(&params);

    /* Tell Instance_init() that we're opening */
    params.openFlag = TRUE;

    params.sharedAddr = sharedAddr;
    attrs = (ti_sdo_ipc_heaps_HeapBufMP_Attrs *)sharedAddr;

    if (SharedRegion_isCacheEnabled(SharedRegion_getId(sharedAddr))) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                Cache_Type_ALL, TRUE);
    }

    if (attrs->status != ti_sdo_ipc_heaps_HeapBufMP_CREATED) {
        *handlePtr = NULL;
        status = HeapBufMP_E_NOTFOUND;
    }
    else {
        *handlePtr = (HeapBufMP_Handle)
            ti_sdo_ipc_heaps_HeapBufMP_create(&params, &eb);
        if (*handlePtr == NULL) {
            status = HeapBufMP_E_FAIL;
        }
        else {
            status = HeapBufMP_S_SUCCESS;
        }
    }

    return (status);
}

/*
 *  ======== HeapBufMP_sharedMemReq ========
 */
SizeT HeapBufMP_sharedMemReq(const HeapBufMP_Params *params)
{
    SizeT memReq, minAlign, bufAlign, blockSize;
    ListMP_Params listMPParams;
    UInt16 regionId;

    /* Assert that the required params have been set */
    Assert_isTrue(params->blockSize != 0, ti_sdo_ipc_Ipc_A_invParam);
    Assert_isTrue(params->numBlocks != 0, ti_sdo_ipc_Ipc_A_invParam);

    if (params->sharedAddr == NULL) {
        regionId = params->regionId;
    }
    else {
        regionId = SharedRegion_getId(params->sharedAddr);
    }

    Assert_isTrue(regionId != SharedRegion_INVALIDREGIONID,
            ti_sdo_ipc_Ipc_A_internal);

    /* Determine the actual buffer alignment */
    bufAlign = params->align;

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
    }

    if (bufAlign < minAlign) {
        bufAlign = minAlign;
    }

    /* Determine the actual block size */
    blockSize = _Ipc_roundup(params->blockSize, bufAlign);

    /* Add size of HeapBufMP Attrs */
    memReq = _Ipc_roundup(sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs), minAlign);

    /*
     *  Add size of ListMP Attrs.  No need to init params since it's not used
     *  to create.
     */
    ListMP_Params_init(&listMPParams);
    listMPParams.regionId = regionId;
    memReq += ListMP_sharedMemReq(&listMPParams);

    /* Round by the buffer alignment */
    memReq = _Ipc_roundup(memReq, bufAlign);

    /*
     *  Add the buffer size. No need to subsequently round because the product
     *  should be a multiple of cacheLineSize if cache alignment is enabled
     */
    memReq += blockSize * params->numBlocks;

    return(memReq);
}

/*
 *************************************************************************
 *                      Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_Instance_init ========
 */
Int ti_sdo_ipc_heaps_HeapBufMP_Instance_init(
        ti_sdo_ipc_heaps_HeapBufMP_Object *obj,
        const ti_sdo_ipc_heaps_HeapBufMP_Params *params,
        Error_Block *eb)
{
    SharedRegion_SRPtr sharedShmBase;
    Ptr localAddr;
    SizeT minAlign;
    Int status;

    Assert_isTrue(params->openFlag ||
                  params->blockSize != 0, ti_sdo_ipc_Ipc_A_invParam);

    obj->nsKey          = NULL;
    obj->allocSize      = 0;

    if (params->openFlag) {
        /* Opening the gate */
        obj->attrs          =
                (ti_sdo_ipc_heaps_HeapBufMP_Attrs *)params->sharedAddr;

        /* No need to Cache_inv attrs- already done in openByAddr() */
        obj->align          = obj->attrs->align;
        obj->numBlocks      = obj->attrs->numBlocks;
        obj->blockSize      = obj->attrs->blockSize;
        obj->exact          = obj->attrs->exact;
        obj->buf            = SharedRegion_getPtr(obj->attrs->bufPtr);
        obj->regionId       = SharedRegion_getId(obj->buf);

        minAlign = Memory_getMaxDefaultTypeAlign();
        if (SharedRegion_getCacheLineSize(obj->regionId) > minAlign) {
            minAlign = SharedRegion_getCacheLineSize(obj->regionId);
        }

        obj->cacheEnabled   = SharedRegion_isCacheEnabled(obj->regionId);
        obj->objType        = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;

        localAddr = SharedRegion_getPtr(obj->attrs->gateMPAddr);
        status = GateMP_openByAddr(localAddr, (GateMP_Handle *)&(obj->gate));
        if (status != GateMP_S_SUCCESS) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (1);
        }

        /* Open the ListMP */
        localAddr = (Ptr)_Ipc_roundup(
            (UInt32)obj->attrs + sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
            minAlign);
        status = ListMP_openByAddr(localAddr,
            (ListMP_Handle *)&(obj->freeList));

        if (status != ListMP_S_SUCCESS) {
            /* obj->freeList set to NULL */
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (2);
        }

        /* Done opening */
        return (0);
    }

    /* Creating the gate */
    if (params->gate != NULL) {
        obj->gate       = params->gate;
    }
    else {
        /* If no gate specified, get the default system gate */
        obj->gate       = (ti_sdo_ipc_GateMP_Handle)GateMP_getDefaultRemote();
    }

    obj->exact          = params->exact;
    obj->align          = params->align;
    obj->numBlocks      = params->numBlocks;

    if (params->sharedAddr == NULL) {
        /* Creating using a shared region ID */
        obj->objType    = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION;
        obj->attrs      = NULL; /* Will be alloc'ed in postInit */
        obj->regionId   = params->regionId;
    }
    else {
        /* Creating using sharedAddr */
        obj->regionId   = SharedRegion_getId(params->sharedAddr);

        /* Assert that the buffer is in a valid shared region */
        Assert_isTrue(obj->regionId != SharedRegion_INVALIDREGIONID,
                      ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

        /* Assert that sharedAddr is cached aligned if region requires align. */
        Assert_isTrue(((UInt32)params->sharedAddr %
                      SharedRegion_getCacheLineSize(obj->regionId) == 0),
                      ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

        obj->objType    = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
        obj->attrs      = (ti_sdo_ipc_heaps_HeapBufMP_Attrs *)
                params->sharedAddr;
    }

    obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);

    /* Fix the alignment (alignment may be needed even if cache is disabled) */
    obj->align = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(obj->regionId) > obj->align) {
        obj->align = SharedRegion_getCacheLineSize(obj->regionId);
    }

    /* Round the blockSize up by the adjusted alignment */
    obj->blockSize = _Ipc_roundup(params->blockSize, obj->align);

    HeapBufMP_postInit(obj, eb);
    if (Error_check(eb)) {
        return(2);
    }

    /* Add entry to NameServer */
    if (params->name != NULL) {
        /* We will store a shared pointer in the NameServer */
        sharedShmBase = SharedRegion_getSRPtr(obj->attrs,
                                              obj->regionId);
        obj->nsKey = NameServer_addUInt32((NameServer_Handle)
                HeapBufMP_module->nameServer, params->name,
                (UInt32)sharedShmBase);

        if (obj->nsKey == NULL) {
            /* NameServer_addUInt32 failed */
            Error_raise(eb, ti_sdo_ipc_Ipc_E_nameFailed, params->name, 0);
            return (3);
        }
    }

    return(0);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_Instance_finalize ========
 */
Void ti_sdo_ipc_heaps_HeapBufMP_Instance_finalize(
        ti_sdo_ipc_heaps_HeapBufMP_Object *obj, Int status)
{
    if (obj->objType & (ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC |
                        ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION)) {
        /* Heap is being deleted */
        /* Remove entry from NameServer */
        if (obj->nsKey != NULL) {
            NameServer_removeEntry((NameServer_Handle)
                    HeapBufMP_module->nameServer, obj->nsKey);
        }

        if (obj->attrs != NULL) {
            /* Set status to 'not created' */
            obj->attrs->status = 0;
            if (obj->cacheEnabled) {
                Cache_wbInv(obj->attrs,
                            sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                            Cache_Type_ALL, TRUE);
            }
        }

        /* Delete the freeList. If NULL, then ListMP_create failed. */
        if (obj->freeList != NULL) {
            ListMP_delete((ListMP_Handle *)&(obj->freeList));
        }

        /*
         *  Free the shared memory back to the region heap. If NULL, then the
         *  Memory_alloc failed.
         */
        if (obj->objType == ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION &&
            obj->attrs != NULL) {
            Memory_free(SharedRegion_getHeap(obj->regionId), obj->attrs,
                    obj->allocSize);
        }
    }
    else {
        /* Heap is being closed */
        /* Close the freeList. If NULL, then ListMP_openByAddr failed. */
        if (obj->freeList != NULL) {
            ListMP_close((ListMP_Handle *)&(obj->freeList));
        }

        /* Close the gate. If NULL, then GateMP_openByAddr failed. */
        if (obj->gate != NULL) {
            GateMP_close((GateMP_Handle *)&(obj->gate));
        }
    }
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_alloc ========
 *  Allocate a block.
 */
Ptr ti_sdo_ipc_heaps_HeapBufMP_alloc(ti_sdo_ipc_heaps_HeapBufMP_Object *obj,
        SizeT size, SizeT align, Error_Block *eb)
{
    Char *block;
    IArg key;

    /* Check for valid blockSize */
    if (size > obj->blockSize) {
        Error_raise(eb, ti_sdo_ipc_heaps_HeapBufMP_E_sizeTooLarge, (IArg)size,
                (IArg)obj->blockSize);
        return (NULL);
    }

    /* Check for exact matching */
    if (obj->exact && size != obj->blockSize) {
        Error_raise(eb, ti_sdo_ipc_heaps_HeapBufMP_E_exactFail, (IArg)size,
                (IArg)obj->blockSize);
        return (NULL);
    }

    /* Check for valid alignment */
    if (align > obj->align) {
        Error_raise(eb, ti_sdo_ipc_heaps_HeapBufMP_E_alignTooLarge, (IArg)align,
                (IArg)obj->align);
        return (NULL);
    }

    /* Enter the gate */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    /* Get the first block */
    block = ListMP_getHead((ListMP_Handle)obj->freeList);

    /* Make sure that a valid pointer was returned. */
    if (block == NULL) {
        GateMP_leave((GateMP_Handle)obj->gate, key);
        Error_raise(eb, ti_sdo_ipc_heaps_HeapBufMP_E_noBlocksLeft, (IArg)obj,
                (IArg)size);

        return (NULL);
    }

    /*
     *  Keep track of the min number of free for this HeapBufMP, if user
     *  has set the config variable trackMaxAllocs to true. Also, keep track
     *  of the number of free blocks.
     *
     *  The min number of free blocks, 'minFreeBlocks', will be used to compute
     *  the "all time" maximum number of allocated blocks in getExtendedStats().
     */
    if (ti_sdo_ipc_heaps_HeapBufMP_trackAllocs) {
        /* Make sure the attrs are not in cache */
        if (obj->cacheEnabled) {
            Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                    Cache_Type_ALL, TRUE);
        }

        obj->attrs->numFreeBlocks--;

        if (obj->attrs->numFreeBlocks < (Int32)obj->attrs->minFreeBlocks) {
            /* save the new minimum */
            obj->attrs->minFreeBlocks = obj->attrs->numFreeBlocks;
        }

        /* Make sure the attrs are written out to memory */
        if (obj->cacheEnabled) {
            Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                    Cache_Type_ALL, TRUE);
        }
    }

    /* Leave the gate */
    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (block);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_free ========
 *  Frees the block to this HeapBufMP. 'size' not check for optimization
 */
Void ti_sdo_ipc_heaps_HeapBufMP_free(ti_sdo_ipc_heaps_HeapBufMP_Object *obj,
        Ptr block, SizeT size)
{
    IArg key;

    Assert_isTrue(((UInt32)block >= (UInt32)obj->buf) &&
        ((UInt32)block < ((UInt32)obj->buf + obj->blockSize * obj->numBlocks)),
        ti_sdo_ipc_heaps_HeapBufMP_A_invBlockFreed);

    /* Assert that 'addr' is block-aligned */
    Assert_isTrue((UInt32)block % obj->align == 0,
            ti_sdo_ipc_heaps_HeapBufMP_A_badAlignment);

    /*
     *  Invalidate entire block make sure stale cache data isn't
     *  evicted later
     */
    if (obj->cacheEnabled) {
        Cache_inv(block, obj->attrs->blockSize, Cache_Type_ALL, FALSE);
    }

    /* Enter the gate */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    ListMP_putTail((ListMP_Handle)obj->freeList, block);

    if (ti_sdo_ipc_heaps_HeapBufMP_trackAllocs) {
        /* Make sure the attrs are not in cache */
        if (obj->cacheEnabled) {
            Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                Cache_Type_ALL, FALSE);
        }

        obj->attrs->numFreeBlocks++;

        /* Make sure the attrs are written out to memory */
        if (obj->cacheEnabled) {
            Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                Cache_Type_ALL, TRUE);
        }
    }

    /* Leave the gate */
    GateMP_leave((GateMP_Handle)obj->gate, key);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_getStats ========
 */
Void ti_sdo_ipc_heaps_HeapBufMP_getStats(ti_sdo_ipc_heaps_HeapBufMP_Object *obj,
        Memory_Stats *stats)
{
    IArg key;
    SizeT blockSize;

    /* This is read-only, so do not need cache management */
    blockSize = obj->attrs->blockSize;

    /* Total size is constant */
    stats->totalSize = blockSize * obj->attrs->numBlocks;

    if (ti_sdo_ipc_heaps_HeapBufMP_trackAllocs) {
        /*
         * Protect this section so that numFreeBlocks doesn't change
         * between totalFreeSize and largestFreeSize
         */
        key = GateMP_enter((GateMP_Handle)obj->gate);
        /* Tracking enabled. Make sure the attrs are not in cache */
        if (obj->cacheEnabled) {
            Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                    Cache_Type_ALL, TRUE);
        }

        stats->totalFreeSize     = blockSize * obj->attrs->numFreeBlocks;
        stats->largestFreeSize   = (obj->attrs->numFreeBlocks > 0) ?
                                    blockSize : 0;

        GateMP_leave((GateMP_Handle)obj->gate, key);
    }
    else {
        /* Tracking disabled */
        stats->totalFreeSize    = 0;
        stats->largestFreeSize  = 0;
    }
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_isBlocking ========
 */
Bool ti_sdo_ipc_heaps_HeapBufMP_isBlocking(
        ti_sdo_ipc_heaps_HeapBufMP_Object *obj)
{
    Bool flag = FALSE;

    // TODO figure out how to determine whether the gate is blocking...
    return (flag);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *                          Shared memory Layout:
 *
 *          sharedAddr   -> ---------------------------
 *                         |  HeapBufMP_Attrs        |
 *                         |  (minAlign PADDING)     |
 *                         |-------------------------|
 *                         |  ListMP shared instance |
 *                         |  (bufAlign PADDING)     |
 *                         |-------------------------|
 *                         |  HeapBufMP BUFFER       |
 *                         |-------------------------|
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapBufMP_postInit ========
 *  Slice and dice the buffer up into the correct size blocks and
 *  add to the freelist.
 */
Void ti_sdo_ipc_heaps_HeapBufMP_postInit(ti_sdo_ipc_heaps_HeapBufMP_Object *obj,
        Error_Block *eb)
{
    UInt i;
    Char *buf;
    SizeT minAlign;
    HeapBufMP_Params heapParams;
    ListMP_Params listMPParams;
    IHeap_Handle regionHeap;

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(obj->regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(obj->regionId);
    }

    if (obj->attrs == NULL) {
        HeapBufMP_Params_init(&heapParams);
        heapParams.regionId     = obj->regionId;
        heapParams.numBlocks    = obj->numBlocks;
        heapParams.align        = obj->align;
        heapParams.blockSize    = obj->blockSize;
        obj->allocSize  =  HeapBufMP_sharedMemReq(&heapParams);

        regionHeap = SharedRegion_getHeap(obj->regionId);
        Assert_isTrue(regionHeap != NULL, ti_sdo_ipc_SharedRegion_A_noHeap);
        obj->attrs = Memory_alloc(regionHeap, obj->allocSize, minAlign, eb);
        if (obj->attrs == NULL) {
            return;
        }
    }

    /* Store the GateMP sharedAddr in the HeapBuf Attrs */
    obj->attrs->gateMPAddr = ti_sdo_ipc_GateMP_getSharedAddr(obj->gate);

    /* Create the freeList */
    ListMP_Params_init(&listMPParams);
    listMPParams.sharedAddr = (Ptr)_Ipc_roundup((UInt32)obj->attrs +
            sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs), minAlign);
    listMPParams.gate       = (GateMP_Handle)obj->gate;
    obj->freeList   = (ti_sdo_ipc_ListMP_Handle)ListMP_create(&listMPParams);
    if (obj->freeList == NULL) {
        return;
    }

    obj->buf        = (Ptr)((SizeT)listMPParams.sharedAddr +
                            ListMP_sharedMemReq(&listMPParams));

    obj->attrs->numFreeBlocks = obj->numBlocks;
    obj->attrs->minFreeBlocks = (UInt)-1;
    obj->attrs->blockSize     = obj->blockSize;
    obj->attrs->align         = obj->align;
    obj->attrs->numBlocks     = obj->numBlocks;
    obj->attrs->exact         = obj->exact ? 1 : 0;

    /* Adjust obj->buf and put a SRPtr in attrs */
    buf = obj->buf = (Ptr)_Ipc_roundup(obj->buf, obj->align);
    obj->attrs->bufPtr = SharedRegion_getSRPtr(obj->buf, obj->regionId);

    /*
     * Split the buffer into blocks that are length "blockSize" and
     * add into the freeList Queue.
     */
    for (i = 0; i < obj->numBlocks; i++) {
        /* Add the block to the freeList */
        ListMP_putTail((ListMP_Handle)obj->freeList, (ListMP_Elem *)buf);

        buf += obj->blockSize;
    }

    /* Last thing, set the status */
    obj->attrs->status = ti_sdo_ipc_heaps_HeapBufMP_CREATED;

    if (obj->cacheEnabled) {
        Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapBufMP_Attrs),
                Cache_Type_ALL, TRUE);
    }
}
