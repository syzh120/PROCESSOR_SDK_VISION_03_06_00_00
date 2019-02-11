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
 *  ======== HeapMultiBufMP.c ========
 */


#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>

#include <string.h> /* for memcpy */
#include <stdlib.h> /* for qsort */

#include <ti/sysbios/hal/Cache.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_NameServer.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/heaps/_HeapMultiBufMP.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/_GateMP.h>

#include "package/internal/HeapMultiBufMP.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_Params_init);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_alloc);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_close);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_create);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_delete);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_free);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_getExtendedStats);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_getStats);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_open);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_openByAddr);
    #pragma FUNC_EXT_CALLED(HeapMultiBufMP_sharedMemReq);
#endif

/*
 *  ======== HeapMultiBufMP_getSharedParams ========
 */
static Void HeapMultiBufMP_getSharedParams(HeapMultiBufMP_Params *sparams,
        const ti_sdo_ipc_heaps_HeapMultiBufMP_Params *params)
{
    sparams->gate        = (GateMP_Handle)params->gate;
    sparams->exact       = params->exact;
    sparams->name        = params->name;
    sparams->numBuckets  = params->numBuckets;
    sparams->bucketEntries =
        (HeapMultiBufMP_Bucket *)params->bucketEntries;
    sparams->regionId    =  params->regionId;
    sparams->sharedAddr  =  params->sharedAddr;
}

/*
 *  ======== HeapMultiBufMP_getRTSCParams ========
 */
static Void HeapMultiBufMP_getRTSCParams(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Params *params,
        const HeapMultiBufMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_Params_init(params);

    params->gate = (ti_sdo_ipc_GateMP_Handle)sparams->gate;
    params->exact = sparams->exact;
    params->name = sparams->name;
    params->numBuckets = sparams->numBuckets;
    params->bucketEntries = (ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket *)
        sparams->bucketEntries;
    params->regionId = sparams->regionId;
    params->sharedAddr = sparams->sharedAddr;
}

/*
 *  ======== HeapMultiBufMP_sizeAlignCompare ========
 *  Comparison function for qsort. Compares Buckets first by blockSize, then
 *  by align, in ascending order.
 */
static int HeapMultiBufMP_sizeAlignCompare(const void *a, const void *b)
{
    int diff;
    HeapMultiBufMP_Bucket *bucketA, *bucketB;

    bucketA = (HeapMultiBufMP_Bucket *)a;
    bucketB = (HeapMultiBufMP_Bucket *)b;

    diff = bucketA->blockSize - bucketB->blockSize;

    /* If the blockSizes match, sort them by ascending align */
    if (diff == 0) {
        diff = bucketA->align - bucketB->align;
    }

    return (diff);
}

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== HeapMultiBufMP_Params_init ========
 */
Void HeapMultiBufMP_Params_init(HeapMultiBufMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_Params params;

    ti_sdo_ipc_heaps_HeapMultiBufMP_Params_init(&params);
    HeapMultiBufMP_getSharedParams(sparams, &params);
}

/*
 *  ======== HeapMultiBufMP_alloc ========
 */
Ptr HeapMultiBufMP_alloc(HeapMultiBufMP_Handle handle,
        SizeT size, SizeT align)
{
    Error_Block eb;

    Error_init(&eb);

    return (ti_sdo_ipc_heaps_HeapMultiBufMP_alloc(
        (ti_sdo_ipc_heaps_HeapMultiBufMP_Object *)handle, size, align, &eb));
}

/*
 *  ======== HeapMultiBufMP_close ========
 */
Int HeapMultiBufMP_close(HeapMultiBufMP_Handle *handlePtr)
{
    HeapMultiBufMP_delete(handlePtr);

    return (HeapMultiBufMP_S_SUCCESS);
}

/*
 *  ======== HeapMultiBufMP_create ========
 */
HeapMultiBufMP_Handle HeapMultiBufMP_create(
        const HeapMultiBufMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_Params params;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj;
    Error_Block eb;

    Error_init(&eb);

    if (sparams != NULL) {
        HeapMultiBufMP_getRTSCParams(&params, (Ptr)sparams);
        /* call the module create */
        obj = ti_sdo_ipc_heaps_HeapMultiBufMP_create(&params, &eb);
    }
    else {
        obj = ti_sdo_ipc_heaps_HeapMultiBufMP_create(NULL, &eb);
    }

    return ((HeapMultiBufMP_Handle)obj);
}

/*
 *  ======== HeapMultiBufMP_delete ========
 */
Int HeapMultiBufMP_delete(HeapMultiBufMP_Handle *handlePtr)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_delete(
        (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle *)handlePtr);

    return (HeapMultiBufMP_S_SUCCESS);
}

/*
 *  ======== HeapMultiBufMP_free ========
 */
Void HeapMultiBufMP_free(HeapMultiBufMP_Handle handle, Ptr addr, SizeT size)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_free(
        (ti_sdo_ipc_heaps_HeapMultiBufMP_Object *)handle, addr, size);
}

/*
 *  ======== HeapMultiBufMP_getExtendedStats ========
 */
Void HeapMultiBufMP_getExtendedStats(HeapMultiBufMP_Handle handle,
        HeapMultiBufMP_ExtendedStats *stats)
{
    IArg key;
    UInt i;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj =
        (ti_sdo_ipc_heaps_HeapMultiBufMP_Object *)handle;

    key = GateMP_enter((GateMP_Handle)obj->gate);

    stats->numBuckets = obj->numBuckets;

    /* Make sure the attrs are not in cache */
    if (obj->cacheEnabled) {
        Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs),
            Cache_Type_ALL, TRUE);
    }

    /*
     *  The maximum number of allocations for this HeapMultiBufMP (for any given
     *  instance of time during its liftime) is computed as follows:
     *
     *  maxAllocatedBlocks = obj->numBlocks - obj->minFreeBlocks
     *
     *  Note that maxAllocatedBlocks is *not* the maximum allocation count, but
     *  rather the maximum allocations seen at any snapshot of time in the
     *  HeapMultiBufMP instance.
     */

    /* if nothing has been alloc'ed yet, return 0 */
    for (i = 0; i < stats->numBuckets; i++) {
        /* Get the blockSize and align for the buffer */
        stats->numBlocks[i] = obj->attrs->buckets[i].numBlocks;
        stats->blockSize[i] = obj->attrs->buckets[i].blockSize;
        stats->align[i]     = obj->attrs->buckets[i].align;

        /* if nothing has been alloc'ed yet, return 0 */
        if ((Int)(obj->attrs->buckets[i].minFreeBlocks) == -1) {
            stats->maxAllocatedBlocks[i] = 0;
        }
        else {
            stats->maxAllocatedBlocks[i] = obj->attrs->buckets[i].numBlocks
                                         - obj->attrs->buckets[i].minFreeBlocks;
        }
        /*
         * current number of alloc'ed blocks is computed using curr # free
         * blocks
         */
        stats->numAllocatedBlocks[i] = obj->attrs->buckets[i].numBlocks
                                     - obj->attrs->buckets[i].numFreeBlocks;
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);
}
/*
 *  ======== HeapMultiBufMP_getStats ========
 */
Void HeapMultiBufMP_getStats(HeapMultiBufMP_Handle handle, Ptr stats)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_getStats(
        (ti_sdo_ipc_heaps_HeapMultiBufMP_Handle)handle,
        (Memory_Stats *)stats);
}
/*
 *  ======== HeapMultiBufMP_open ========
 */
Int HeapMultiBufMP_open(String name,
        HeapMultiBufMP_Handle *handlePtr)
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
            (NameServer_Handle)HeapMultiBufMP_module->nameServer, name,
            &sharedShmBase, MultiProc_getClusterProcList());

    if (status < 0) {
        /* Name not found. */
        *handlePtr = NULL;
        return (HeapMultiBufMP_E_NOTFOUND);
    }

    sharedAddr = SharedRegion_getPtr(sharedShmBase);

    status = HeapMultiBufMP_openByAddr(sharedAddr, handlePtr);

    return (status);
}

/*
 *  ======== HeapMultiBufMP_openByAddr ========
 */
Int HeapMultiBufMP_openByAddr(Ptr sharedAddr,
        HeapMultiBufMP_Handle *handlePtr)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_Params params;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs *attrs;
    Int status;
    Error_Block eb;

    Error_init(&eb);

    ti_sdo_ipc_heaps_HeapMultiBufMP_Params_init(&params);

    /* Tell Instance_init() that we're opening */
    params.openFlag = TRUE;

    params.sharedAddr = sharedAddr;
    attrs = (ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs *)sharedAddr;

    if (SharedRegion_isCacheEnabled(SharedRegion_getId(sharedAddr))) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs),
            Cache_Type_ALL, TRUE);
    }

    if (attrs->status != ti_sdo_ipc_heaps_HeapMultiBufMP_CREATED) {
        *handlePtr = NULL;
        status = HeapMultiBufMP_E_NOTFOUND;
    }
    else {
        *handlePtr = (HeapMultiBufMP_Handle)
            ti_sdo_ipc_heaps_HeapMultiBufMP_create(&params, &eb);
        if (*handlePtr == NULL) {
            status = HeapMultiBufMP_E_FAIL;
        }
        else {
            status = HeapMultiBufMP_S_SUCCESS;
        }
    }

    return (status);
}

/*
 *  ======== HeapMultiBufMP_sharedMemReq ========
 */
SizeT HeapMultiBufMP_sharedMemReq(const HeapMultiBufMP_Params *sparams)
{
    SizeT   memReq, minAlign;
    UInt    i;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket
        bucketEntries[HeapMultiBufMP_MAXBUCKETS];
    UInt    numBuckets;
    UInt16  regionId;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Params params;

    /* Assert that the required params have been set */
    Assert_isTrue(sparams->bucketEntries != NULL, ti_sdo_ipc_Ipc_A_invParam);
    Assert_isTrue(sparams->numBuckets != 0, ti_sdo_ipc_Ipc_A_invParam);

    if (sparams->sharedAddr == NULL) {
        regionId = sparams->regionId;
    }
    else {
        regionId = SharedRegion_getId(sparams->sharedAddr);
    }

    Assert_isTrue(regionId != SharedRegion_INVALIDREGIONID,
            ti_sdo_ipc_Ipc_A_internal);

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
    }

    memReq = _Ipc_roundup(sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs),
        minAlign);

    HeapMultiBufMP_getRTSCParams(&params, (Ptr)sparams);

    /* Optimize the bucketEntries array */
    numBuckets = HeapMultiBufMP_processBuckets(bucketEntries, &params,
        regionId);

    for (i = 0; i < numBuckets; i++) {
        memReq = _Ipc_roundup(memReq, bucketEntries[i].align);

        memReq += bucketEntries[i].blockSize * bucketEntries[i].numBlocks;
    }

    return (memReq);
}

/*
 *************************************************************************
 *                      Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_init ========
 */
Int ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_init(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj,
        const ti_sdo_ipc_heaps_HeapMultiBufMP_Params *params, Error_Block *eb)
{
    SharedRegion_SRPtr sharedShmBase;
    Ptr localAddr;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket
        optBucketEntries[HeapMultiBufMP_MAXBUCKETS];
    Int status;

    /* Ensure that bucketEntries has been supplied */
    Assert_isTrue(params->openFlag ||
                  params->bucketEntries != NULL, ti_sdo_ipc_Ipc_A_invParam);


    /* Check numBuckets */
    Assert_isTrue(params->openFlag ||
                  params->numBuckets <= HeapMultiBufMP_MAXBUCKETS,
                  ti_sdo_ipc_Ipc_A_invParam);

    obj->nsKey          = NULL;
    obj->allocSize      = 0;

    if (params->openFlag) {
        /* Opening the heap */
        obj->attrs          = (ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs *)
            params->sharedAddr;
        obj->objType        = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;
        obj->bucketEntries  = NULL; /* Never used in open */

        /* No need to Cache_inv attrs- already done in openByAddr() */
        obj->numBuckets     = obj->attrs->numBuckets;
        obj->exact          = obj->attrs->exact == 1;
        obj->buf            = SharedRegion_getPtr(
                              obj->attrs->buckets[0].baseAddr);
        obj->regionId       = SharedRegion_getId(obj->buf);
        obj->cacheEnabled   = SharedRegion_isCacheEnabled(obj->regionId);

        localAddr = SharedRegion_getPtr(obj->attrs->gateMPAddr);

        status = GateMP_openByAddr(localAddr, (GateMP_Handle *)&(obj->gate));
        if (status != GateMP_S_SUCCESS) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (1);
        }

        /* Done opening */
        return (0);
    }

    /* Creating the heap */
    if (params->gate != NULL) {
        obj->gate       = params->gate;
    }
    else {
        /* If no gate specified, get the default system gate */
        obj->gate       = (ti_sdo_ipc_GateMP_Handle)GateMP_getDefaultRemote();
    }

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

        /* Assert that sharedAddr is cached aligned if region cache aligned */
        Assert_isTrue(((UInt32)params->sharedAddr %
                      SharedRegion_getCacheLineSize(obj->regionId) == 0),
                      ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

        obj->objType    = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;

        /* obj->buf will get alignment-adjusted in postInit */
        obj->buf        = (Ptr)((UInt32)params->sharedAddr +
                                sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs));
        obj->attrs      = (ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs *)
            params->sharedAddr;
    }

    obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
    obj->exact        = params->exact;
    /* Adjust & sort the copied bucket entries by blockSize & align */
    obj->numBuckets = HeapMultiBufMP_processBuckets(optBucketEntries,
        (ti_sdo_ipc_heaps_HeapMultiBufMP_Params *)params, obj->regionId);
    obj->bucketEntries = optBucketEntries;

    HeapMultiBufMP_postInit(obj, eb);
    if (Error_check(eb)) {
        return (1);
    }

    /* Set to NULL since optBucketEntries is on the stack */
    obj->bucketEntries = NULL;

    /* Add entry to NameServer */
    if (params->name != NULL) {
        /* We will store a shared pointer in the NameServer */
        sharedShmBase = SharedRegion_getSRPtr(obj->attrs,
                                              obj->regionId);
        obj->nsKey = NameServer_addUInt32(
                (NameServer_Handle)HeapMultiBufMP_module->nameServer,
                params->name, (UInt32)sharedShmBase);

        if (obj->nsKey == NULL) {
            /* NameServer_addUInt32 failed */
            Error_raise(eb, ti_sdo_ipc_Ipc_E_nameFailed, params->name, 0);
            return (2);
        }
    }

    return (0);
}

/*
 *  ======== HeapMultiBufMP_Instance_finalize ========
 */
Void ti_sdo_ipc_heaps_HeapMultiBufMP_Instance_finalize(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, Int status)
{
    /* First remove the NameServer entry */
    if (obj->objType & (ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC |
        ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION)) {
        if (obj->nsKey != NULL) {
            NameServer_removeEntry((NameServer_Handle)
                    HeapMultiBufMP_module->nameServer, obj->nsKey);
        }

        if (obj->attrs != NULL) {
            obj->attrs->status = 0;

            if (obj->cacheEnabled) {
                Cache_wbInv(obj->attrs,
                            sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs),
                            Cache_Type_ALL, TRUE);
            }
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
        /* Close the gate. If NULL, then GateMP_openByAddr failed. */
        if (obj->gate != NULL) {
            GateMP_close((GateMP_Handle *)&(obj->gate));
        }
    }
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_alloc ========
 *  Allocate a block.
 */
Ptr ti_sdo_ipc_heaps_HeapMultiBufMP_alloc(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, SizeT size, SizeT align,
        Error_Block *eb)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *block;
    UInt index;
    IArg key;
    Bool alignMatches, sizeMatches;

    /* Read-only field, so no cache/gate concerns */
    for (index = 0; index < obj->numBuckets; index++) {
        sizeMatches = (size <= obj->attrs->buckets[index].blockSize);
        alignMatches = (align <= obj->attrs->buckets[index].align);

        if (sizeMatches && alignMatches) {
            if (obj->exact && size != obj->attrs->buckets[index].blockSize) {
                Error_raise(eb, ti_sdo_ipc_heaps_HeapMultiBufMP_E_exactFail,
                            size, obj->attrs->buckets[index].blockSize);
                return (NULL);
            }
            break;
        }
    }

    if (index == obj->attrs->numBuckets) {
        /* Couldn't find a buffer with suitable size/align */
        Error_raise(eb, ti_sdo_ipc_heaps_HeapMultiBufMP_E_size,
                size, align);

        return (NULL);
    }

    /* At this point, we know the bucket number. Enter the gate */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    if (obj->cacheEnabled) {
        Cache_inv(&(obj->attrs->buckets[index]),
                  sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs),
                  Cache_Type_ALL, TRUE);
    }

    /* Get the first block */
    block = HeapMultiBufMP_getHead(obj, index);

    /* Make sure that a valid pointer was returned. */
    if (block == NULL) {
        /* No more blocks left in the buffer */
        GateMP_leave((GateMP_Handle)obj->gate, key);
        Error_raise(eb, ti_sdo_ipc_heaps_HeapMultiBufMP_E_noBlocksLeft,
                    obj->attrs->buckets[index].blockSize,
                    obj->attrs->buckets[index].align);

        return (NULL);
    }

    obj->attrs->buckets[index].numFreeBlocks--;

    /*
     *  Keep track of the [min] number of free for this HeapMultiBufMP, if user
     *  has set the config variable trackMaxAllocs to true.
     *
     *  The min number of free blocks, 'minFreeBlocks', will be used to compute
     *  the "all time" maximum number of allocated blocks in getExtendedStats()
     */
    if (ti_sdo_ipc_heaps_HeapMultiBufMP_trackMaxAllocs) {
        if (obj->attrs->buckets[index].numFreeBlocks <
                obj->attrs->buckets[index].minFreeBlocks) {
            /* save the new minimum */
            obj->attrs->buckets[index].minFreeBlocks =
            obj->attrs->buckets[index].numFreeBlocks;
        }
    }

    /* Results of getHead and trackMaxAllocs written out to memory */
    if (obj->cacheEnabled) {
        Cache_wbInv(&(obj->attrs->buckets[index]),
            sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs), Cache_Type_ALL,
            TRUE);
    }

    /* Leave the gate */
    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (block);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_free ========
 *  Frees the block to this HeapMultiBufMP.
 */
Void ti_sdo_ipc_heaps_HeapMultiBufMP_free(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, Ptr block, SizeT size)
{
    Int  index;
    IArg key;
    SharedRegion_SRPtr blockSRPtr;

    /* Check for invalid arguments */
    Assert_isTrue(size != 0, ti_sdo_ipc_Ipc_A_nullArgument);

    /*
     *  invaliate the block here so that stale data isn't evicted from cache
     *  at some later point
     */
    if (obj->cacheEnabled) {
        Cache_inv(block, size, Cache_Type_ALL, FALSE);
    }

    /* First search by block */
    blockSRPtr = SharedRegion_getSRPtr(block, obj->regionId);

    Assert_isTrue(blockSRPtr >= obj->attrs->buckets[0].baseAddr &&
                  blockSRPtr <
                  (obj->attrs->buckets[obj->attrs->numBuckets - 1].baseAddr +
                   obj->attrs->buckets[obj->attrs->numBuckets - 1].numBlocks *
                   obj->attrs->buckets[obj->attrs->numBuckets - 1].blockSize),
                   ti_sdo_ipc_heaps_HeapMultiBufMP_A_addrNotFound);

    for (index = obj->numBuckets - 1; index >= 0; index--) {
        /* We can compare SRPtrs because they are both in the same region */
        if (obj->attrs->buckets[index].baseAddr <= blockSRPtr) {
            break;
        }
    }

    /* Assert if the size does not match the found bucket */
    Assert_isTrue((size <= obj->attrs->buckets[index].blockSize) &&
                  (obj->attrs->exact == 0) ||
                  (size == obj->attrs->buckets[index].blockSize) &&
                  (obj->attrs->exact == 1),
                    ti_sdo_ipc_heaps_HeapMultiBufMP_A_sizeNotFound);

    /* Enter the gate */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    if (obj->cacheEnabled) {
        Cache_inv(block, obj->attrs->buckets[index].blockSize, Cache_Type_ALL,
                  FALSE);
        Cache_inv(&(obj->attrs->buckets[index]),
                  sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs),
                  Cache_Type_ALL, TRUE);
    }

    HeapMultiBufMP_putTail(obj, index, block);

    /*
     *  Only need to write back the HeapMultiBufMP_Elem (top) part of the the
     *  block being freed.  The rest of the block must also be invalidated
     *  to ensure that stale data isn't evicted from cache at some later point
     */
    if (obj->cacheEnabled) {
        Cache_wb(block, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Elem),
                 Cache_Type_ALL, FALSE);
    }

    obj->attrs->buckets[index].numFreeBlocks++;
    if (obj->cacheEnabled) {
        Cache_wbInv(&(obj->attrs->buckets[index]),
                 sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_BucketAttrs),
                 Cache_Type_ALL, TRUE);
    }

    /* Leave the gate */
    GateMP_leave((GateMP_Handle)obj->gate, key);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_getHead ========
 */
ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *ti_sdo_ipc_heaps_HeapMultiBufMP_getHead(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, Int index)
{
    ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *block;
    SharedRegion_SRPtr sharedBlock;

    /* obj->attrs->buckets[index] should have already been invalidated */
    if (obj->attrs->buckets[index].head !=
            ti_sdo_ipc_SharedRegion_INVALIDSRPTR) {
        sharedBlock = obj->attrs->buckets[index].head;
        block = SharedRegion_getPtr(sharedBlock);

        if (obj->cacheEnabled) {
            /*
             *  Only need to invalidate the elem, not the entire block.
             */
            Cache_inv(block, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Elem),
                      Cache_Type_ALL, FALSE);
        }
        obj->attrs->buckets[index].head = block->next;
        if (obj->attrs->buckets[index].head ==
                ti_sdo_ipc_SharedRegion_INVALIDSRPTR) {
            /* We've removed the last block from the bucket */
            obj->attrs->buckets[index].tail =
                ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
        }

        /*
         *  No need to write back here since obj->attrs->buckets[index]
         *  written back in HeapMultiBufMP_alloc
         */
    }
    else {
        block = NULL;
    }

    return (block);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_getStats ========
 */
Void ti_sdo_ipc_heaps_HeapMultiBufMP_getStats(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, Memory_Stats *stats)
{
    IArg key;
    SizeT totalSize = 0;
    SizeT totalFreeSize = 0;
    SizeT largestFreeSize = 0;
    UInt i;

    if (obj->cacheEnabled) {
        Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs),
            Cache_Type_ALL, TRUE);
    }

    /*
     * Protect this section so that numFreeBlocks doesn't change between
     * totalFreeSize and largestFreeSize
     */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    for (i = 0; i < obj->attrs->numBuckets; i++) {
        /* Check largest free block. */
        if (obj->attrs->buckets[i].blockSize > largestFreeSize
            && obj->attrs->buckets[i].numFreeBlocks > 0) {
            largestFreeSize = obj->attrs->buckets[i].blockSize;
        }
        totalSize += obj->attrs->buckets[i].blockSize *
                     obj->attrs->buckets[i].numBlocks;
        totalFreeSize += obj->attrs->buckets[i].blockSize *
                         obj->attrs->buckets[i].numFreeBlocks;
    }

    stats->totalSize = totalSize;
    stats->totalFreeSize = totalFreeSize;
    stats->largestFreeSize = largestFreeSize;

    GateMP_leave((GateMP_Handle)obj->gate, key);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking ========
 */
Bool ti_sdo_ipc_heaps_HeapMultiBufMP_isBlocking(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj)
{
    Bool flag = FALSE;

    // TODO figure out how to determine whether the gate is blocking...
    return (flag);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_putTail ========
 */
Void ti_sdo_ipc_heaps_HeapMultiBufMP_putTail(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, Int index,
        ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *block)
{
    SharedRegion_SRPtr sharedBlock;
    ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *temp;

    sharedBlock = SharedRegion_getSRPtr(block, obj->regionId);

    /* obj->attrs->buckets[index] should have already been invalidated */
    if (obj->attrs->buckets[index].tail == ti_sdo_ipc_SharedRegion_INVALIDSRPTR) {
        obj->attrs->buckets[index].head = sharedBlock;
    }
    else {
        temp = (ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *)
                SharedRegion_getPtr(obj->attrs->buckets[index].tail);
        temp->next = sharedBlock;

        /*
         *  No need to wait here because cache operation after putTail() will
         *  wait
         */
        Cache_wbInv(temp, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Elem),
                 Cache_Type_ALL, FALSE);
    }
    obj->attrs->buckets[index].tail = sharedBlock;
    block->next = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;

    /*
     *  No need to write back here since obj->attrs->buckets[index]
     *  and 'block' written back in HeapMultiBufMP_alloc
     */
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_postInit ========
 *  Slice and dice the buffer up into the correct size blocks and
 *  add to the freelist.
 */
Void ti_sdo_ipc_heaps_HeapMultiBufMP_postInit(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Object *obj, Error_Block *eb)
{
    UInt i;
    UInt j;
    Char *buf;
    SizeT minAlign;
    HeapMultiBufMP_Params sparams;
    IHeap_Handle regionHeap;

    if (obj->attrs == NULL) {
        /* Need to allocate from the heap */
        HeapMultiBufMP_Params_init(&sparams);
        sparams.regionId      = obj->regionId;
        sparams.bucketEntries = (HeapMultiBufMP_Bucket *)obj->bucketEntries;
        sparams.numBuckets    = obj->numBuckets;
        obj->allocSize =  HeapMultiBufMP_sharedMemReq(&sparams);

        minAlign = Memory_getMaxDefaultTypeAlign();
        if (minAlign < SharedRegion_getCacheLineSize(obj->regionId)) {
            minAlign = SharedRegion_getCacheLineSize(obj->regionId);
        }

        regionHeap = SharedRegion_getHeap(obj->regionId);
        Assert_isTrue(regionHeap != NULL, ti_sdo_ipc_SharedRegion_A_noHeap);
        obj->attrs = Memory_alloc(regionHeap, obj->allocSize, minAlign, eb);
        if (obj->attrs == NULL) {
            return;
        }

        obj->buf = (Ptr)((UInt32)obj->attrs +
            sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs));
    }

    obj->attrs->numBuckets  = obj->numBuckets;
    obj->attrs->exact       = obj->exact ? 1 : 0;
    obj->attrs->gateMPAddr  = ti_sdo_ipc_GateMP_getSharedAddr(obj->gate);

    for (i = 0; i < obj->numBuckets; i++) {
        obj->attrs->buckets[i].head = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
        obj->attrs->buckets[i].tail = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
        obj->attrs->buckets[i].minFreeBlocks = (UInt)-1;
        obj->attrs->buckets[i].blockSize     = obj->bucketEntries[i].blockSize;
        obj->attrs->buckets[i].numBlocks     = obj->bucketEntries[i].numBlocks;
        obj->attrs->buckets[i].numFreeBlocks = obj->bucketEntries[i].numBlocks;
        obj->attrs->buckets[i].align         = obj->bucketEntries[i].align;
    }

    /* obj->buf should point to base of first buffer */
    obj->buf = buf = (Ptr)_Ipc_roundup(obj->buf, obj->attrs->buckets[0].align);
    for (i = 0; i < obj->numBuckets; i++) {

        /* Make sure buffer is buffer-aligned (not just min-Align'ed) */
        buf = (Ptr)_Ipc_roundup(buf, obj->attrs->buckets[i].align);

        /* Put a shared pointer to the buf in attrs */
        obj->attrs->buckets[i].baseAddr =
                SharedRegion_getSRPtr(buf, obj->regionId);

        /*
         * Split the buffer into blocks that are length "blockSize" and
         * add into the freeList Queue.
         */
        for (j = 0; j < obj->attrs->buckets[i].numBlocks; j++) {
            /* Put the free block on the end of the linked list */
            HeapMultiBufMP_putTail(obj, i,
                (ti_sdo_ipc_heaps_HeapMultiBufMP_Elem *)buf);

            buf += obj->attrs->buckets[i].blockSize;
        }
    }

    /* At the end of the loop, buf points to the end of shared memory */
    if (obj->cacheEnabled) {
        /*
         *  Write back the entire buffer. Don't cache-wait since the
         *  Cache_wbInv below will.
         */
        Cache_wbInv(obj->buf, buf - obj->buf, Cache_Type_ALL, FALSE);
    }

    /* Last thing, set the status */
    obj->attrs->status = ti_sdo_ipc_heaps_HeapMultiBufMP_CREATED;
    if (obj->cacheEnabled) {
        Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapMultiBufMP_Attrs),
            Cache_Type_ALL, TRUE);
    }
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets ========
 *  1) Adjust the blockSize and alignments for each buffer
 *      - Alignment adjusted for cacheLineSize, cacheAlign
 *      - blockSize adjusted for alignment
 *  2) Sort buckets by blockSize and then by alignment
 *  3) Merge buckets with same blockSize and same alignment
 */
UInt ti_sdo_ipc_heaps_HeapMultiBufMP_processBuckets(
        ti_sdo_ipc_heaps_HeapMultiBufMP_Bucket *optBucketEntries,
        ti_sdo_ipc_heaps_HeapMultiBufMP_Params *params,
        UInt16 regionId)
{
    UInt i, j;
    Int optNumBuckets;

    /* Copy the supplied buckets to a modifiable area */
    memcpy(optBucketEntries,
           params->bucketEntries,
           sizeof(HeapMultiBufMP_Bucket) * params->numBuckets);

    /* Combine if blockSizes (and alignments) are equal and shrink the array */
    for (i = 0; i < params->numBuckets; i++) {
        /* Ensure that align is a power of two */
        Assert_isTrue((optBucketEntries[i].align &
                      (optBucketEntries[i].align - 1)) == 0,
                      ti_sdo_ipc_heaps_HeapMultiBufMP_A_invalidAlign);

        /* First fix the alignment */
        if (optBucketEntries[i].align <
            SharedRegion_getCacheLineSize(regionId)) {
            optBucketEntries[i].align = SharedRegion_getCacheLineSize(regionId);
        }
        else if (optBucketEntries[i].align <
                 Memory_getMaxDefaultTypeAlign()) {
            /* Cache is disabled, use the default alignment */
            optBucketEntries[i].align = Memory_getMaxDefaultTypeAlign();
        }

        /* Fix the blockSize if blockSize isn't a multiple of alignment */
        optBucketEntries[i].blockSize =
            (optBucketEntries[i].blockSize + (optBucketEntries[i].align - 1))
             & ~(optBucketEntries[i].align - 1);
    }

    /* Sort optBucketEntries by blockSize and then alignment */
    qsort(optBucketEntries, params->numBuckets, sizeof(HeapMultiBufMP_Bucket),
          HeapMultiBufMP_sizeAlignCompare);

    optNumBuckets = 0;

    /* Combine if blockSizes (and alignments) are equal and shrink the array */
    for (i = 0; i < params->numBuckets; i++) {
        if (optBucketEntries[i].numBlocks != 0) {
            memcpy(&(optBucketEntries[optNumBuckets]), &(optBucketEntries[i]),
                   sizeof(HeapMultiBufMP_Bucket));
            for (j = i + 1 ; j < params->numBuckets; j++) {
                if (optBucketEntries[optNumBuckets].blockSize ==
                        optBucketEntries[j].blockSize &&
                    optBucketEntries[optNumBuckets].align ==
                        optBucketEntries[j].align) {
                    /* Combine the buckets */
                    optBucketEntries[optNumBuckets].numBlocks +=
                                  optBucketEntries[j].numBlocks;
                    optBucketEntries[j].numBlocks = 0;
                }
            }
            optNumBuckets++ ;
        }
    }

    return (optNumBuckets);
}
