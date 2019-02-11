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
 *  ======== HeapMemMP.c ========
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
#include <ti/sdo/ipc/heaps/_HeapMemMP.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/_GateMP.h>

#include "package/internal/HeapMemMP.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(HeapMemMP_Params_init);
    #pragma FUNC_EXT_CALLED(HeapMemMP_alloc);
    #pragma FUNC_EXT_CALLED(HeapMemMP_close);
    #pragma FUNC_EXT_CALLED(HeapMemMP_create);
    #pragma FUNC_EXT_CALLED(HeapMemMP_delete);
    #pragma FUNC_EXT_CALLED(HeapMemMP_free);
    #pragma FUNC_EXT_CALLED(HeapMemMP_getExtendedStats);
    #pragma FUNC_EXT_CALLED(HeapMemMP_getStats);
    #pragma FUNC_EXT_CALLED(HeapMemMP_open);
    #pragma FUNC_EXT_CALLED(HeapMemMP_openByAddr);
    #pragma FUNC_EXT_CALLED(HeapMemMP_restore);
    #pragma FUNC_EXT_CALLED(HeapMemMP_sharedMemReq);
#endif

/*
 *  ======== HeapMemMP_getSharedParams ========
 */
static Void HeapMemMP_getSharedParams(HeapMemMP_Params *sparams,
        const ti_sdo_ipc_heaps_HeapMemMP_Params *params)
{
    sparams->gate        = (GateMP_Handle)params->gate;
    sparams->name        = params->name;
    sparams->regionId    =  params->regionId;
    sparams->sharedAddr  =  params->sharedAddr;
    sparams->sharedBufSize = params->sharedBufSize;
}

/*
 *  ======== HeapMemMP_getRTSCParams ========
 */
static Void HeapMemMP_getRTSCParams(
        ti_sdo_ipc_heaps_HeapMemMP_Params *params,
        const HeapMemMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapMemMP_Params_init(params);

    params->gate = (ti_sdo_ipc_GateMP_Handle)sparams->gate;
    params->name = sparams->name;
    params->regionId = sparams->regionId;
    params->sharedAddr  =  sparams->sharedAddr;
    params->sharedBufSize = sparams->sharedBufSize;
}

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== HeapMemMP_Params_init ========
 */
Void HeapMemMP_Params_init(HeapMemMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapMemMP_Params params;

    ti_sdo_ipc_heaps_HeapMemMP_Params_init(&params);
    HeapMemMP_getSharedParams(sparams, &params);
}

/*
 *  ======== HeapMemMP_alloc ========
 */
Ptr HeapMemMP_alloc(HeapMemMP_Handle handle, SizeT size, SizeT align)
{
    Error_Block eb;

    Error_init(&eb);

    return (ti_sdo_ipc_heaps_HeapMemMP_alloc(
            (ti_sdo_ipc_heaps_HeapMemMP_Handle)handle, size, align, &eb));
}

/*
 *  ======== HeapMemMP_create ========
 */
HeapMemMP_Handle HeapMemMP_create(const HeapMemMP_Params *sparams)
{
    ti_sdo_ipc_heaps_HeapMemMP_Params params;
    ti_sdo_ipc_heaps_HeapMemMP_Object *obj;
    Error_Block eb;

    Error_init(&eb);

    if (sparams != NULL) {
        HeapMemMP_getRTSCParams(&params, (Ptr)sparams);

        /* call the module create */
        obj = ti_sdo_ipc_heaps_HeapMemMP_create(&params, &eb);
    }
    else {
        obj = ti_sdo_ipc_heaps_HeapMemMP_create(NULL, &eb);
    }

    return ((HeapMemMP_Handle)obj);
}

/*
 *  ======== HeapMemMP_close ========
 */
Int HeapMemMP_close(HeapMemMP_Handle *handlePtr)
{
    HeapMemMP_delete(handlePtr);

    return (HeapMemMP_S_SUCCESS);
}

/*
 *  ======== HeapMemMP_delete ========
 */
Int HeapMemMP_delete(HeapMemMP_Handle *handlePtr)
{
    ti_sdo_ipc_heaps_HeapMemMP_delete(
            (ti_sdo_ipc_heaps_HeapMemMP_Handle *)handlePtr);

    return (HeapMemMP_S_SUCCESS);
}

/*
 *  ======== HeapMemMP_free ========
 */
Void HeapMemMP_free(HeapMemMP_Handle handle, Ptr addr, SizeT size)
{
    ti_sdo_ipc_heaps_HeapMemMP_free(
            (ti_sdo_ipc_heaps_HeapMemMP_Handle)handle, addr, size);
}

/*
 *  ======== HeapMemMP_getExtendedStats ========
 */
Void HeapMemMP_getExtendedStats(HeapMemMP_Handle handle,
        HeapMemMP_ExtendedStats *stats)
{
    ti_sdo_ipc_heaps_HeapMemMP_Object *obj =
            (ti_sdo_ipc_heaps_HeapMemMP_Object *)handle;

    stats->buf   = obj->buf;
    stats->size  = obj->bufSize;
}

/*
 *  ======== HeapMemMP_getStats ========
 */
Void HeapMemMP_getStats(HeapMemMP_Handle handle, Ptr stats)
{
    ti_sdo_ipc_heaps_HeapMemMP_getStats(
        (ti_sdo_ipc_heaps_HeapMemMP_Handle)handle, (Memory_Stats *)stats);
}

/*
 *  ======== HeapMemMP_open ========
 */
Int HeapMemMP_open(String name, HeapMemMP_Handle *handlePtr)
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
            (NameServer_Handle)HeapMemMP_module->nameServer, name,
            &sharedShmBase, MultiProc_getClusterProcList());

    if (status < 0) {
        /* Name not found. */
        *handlePtr = NULL;
        return (HeapMemMP_E_NOTFOUND);
    }

    sharedAddr = SharedRegion_getPtr(sharedShmBase);

    status = HeapMemMP_openByAddr(sharedAddr, handlePtr);

    return (status);
}

/*
 *  ======== HeapMemMP_openByAddr ========
 */
Int HeapMemMP_openByAddr(Ptr sharedAddr,
                         HeapMemMP_Handle *handlePtr)
{
    ti_sdo_ipc_heaps_HeapMemMP_Params params;
    ti_sdo_ipc_heaps_HeapMemMP_Attrs *attrs;
    Int status;
    Error_Block eb;

    Error_init(&eb);

    ti_sdo_ipc_heaps_HeapMemMP_Params_init(&params);

    /* Tell Instance_init() that we're opening */
    params.openFlag = TRUE;

    params.sharedAddr = sharedAddr;
    attrs = (ti_sdo_ipc_heaps_HeapMemMP_Attrs *)sharedAddr;

    if (SharedRegion_isCacheEnabled(SharedRegion_getId(sharedAddr))) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Attrs),
                Cache_Type_ALL, TRUE);
    }

    if (attrs->status != ti_sdo_ipc_heaps_HeapMemMP_CREATED) {
        *handlePtr = NULL;
        status = HeapMemMP_E_NOTFOUND;
    }
    else {
        *handlePtr = (HeapMemMP_Handle)ti_sdo_ipc_heaps_HeapMemMP_create(
                &params, &eb);
        if (*handlePtr == NULL) {
            status = HeapMemMP_E_FAIL;
        }
        else {
            status = HeapMemMP_S_SUCCESS;
        }
    }

    return (status);
}

/*
 *  ======== HeapMemMP_restore ========
 *  The buffer should have the properly alignment at this
 *  point (either from instance$static$init in HeapMemMP.xs or
 *  from the above HeapMemMP_Instance_init).
 */
Void HeapMemMP_restore(HeapMemMP_Handle handle)
{
    ti_sdo_ipc_heaps_HeapMemMP_Object *obj =
            (ti_sdo_ipc_heaps_HeapMemMP_Object *)handle;

    ti_sdo_ipc_heaps_HeapMemMP_Header *begHeader;

    /*
     *  Fill in the top of the memory block
     *  next: pointer will be NULL (end of the list)
     *  size: size of this block
     *  NOTE: no need to Cache_inv because obj->attrs->bufPtr should be const
     */
    begHeader = (ti_sdo_ipc_heaps_HeapMemMP_Header *)obj->buf;
    begHeader->next = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
    begHeader->size = obj->bufSize;

    obj->attrs->head.next = obj->attrs->bufPtr;
    if (obj->cacheEnabled) {
        Cache_wbInv(&(obj->attrs->head),
                sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header), Cache_Type_ALL,
                FALSE);
        Cache_wbInv(begHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                Cache_Type_ALL, TRUE);
    }
}

/*
 *  ======== HeapMemMP_sharedMemReq ========
 */
SizeT HeapMemMP_sharedMemReq(const HeapMemMP_Params *params)
{
    SizeT memReq, minAlign;
    UInt16 regionId;

    /* Ensure that the sharedBufSize param has been set */
    Assert_isTrue(params->sharedBufSize != 0, ti_sdo_ipc_Ipc_A_invParam);

    if (params->sharedAddr == NULL) {
        regionId = params->regionId;
    }
    else {
        regionId = SharedRegion_getId(params->sharedAddr);
    }

    Assert_isTrue(regionId != SharedRegion_INVALIDREGIONID,
            ti_sdo_ipc_Ipc_A_internal);

    minAlign = sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header);
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
    }

    /* Add size of HeapBufMP Attrs */
    memReq = _Ipc_roundup(sizeof(ti_sdo_ipc_heaps_HeapMemMP_Attrs), minAlign);

    /* Add the buffer size */
    memReq += params->sharedBufSize;

    /* Make sure the size is a multiple of minAlign (round down) */
    memReq = (memReq / minAlign) * minAlign;

    return((SizeT)memReq);
}

/*
 *************************************************************************
 *                      Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapMemMP_Instance_init ========
 */
Int ti_sdo_ipc_heaps_HeapMemMP_Instance_init(
        ti_sdo_ipc_heaps_HeapMemMP_Object *obj,
        const ti_sdo_ipc_heaps_HeapMemMP_Params *params,
        Error_Block *eb)
{
    SharedRegion_SRPtr sharedShmBase;
    Ptr localAddr;
    Int status;

    /* Assert that sharedBufSize is sufficient */
    Assert_isTrue(params->openFlag == TRUE ||
                  params->sharedBufSize != 0,
                  ti_sdo_ipc_Ipc_A_invParam);

    obj->nsKey          = NULL;
    obj->allocSize      = 0;

    if (params->openFlag == TRUE) {
        /* Opening the gate */
        obj->attrs      = (ti_sdo_ipc_heaps_HeapMemMP_Attrs *)
            params->sharedAddr;

        /* No need to Cache_inv- already done in openByAddr() */
        obj->buf            = (Char *)SharedRegion_getPtr(
                                    obj->attrs->bufPtr);
        obj->bufSize        = obj->attrs->head.size;
        obj->objType        = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;
        obj->regionId       = SharedRegion_getId(obj->buf);
        obj->cacheEnabled   = SharedRegion_isCacheEnabled(obj->regionId);

        /* Set minAlign */
        obj->minAlign = sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header);
        if (SharedRegion_getCacheLineSize(obj->regionId) > obj->minAlign) {
            obj->minAlign = SharedRegion_getCacheLineSize(obj->regionId);
        }

        localAddr = SharedRegion_getPtr(obj->attrs->gateMPAddr);

        status = GateMP_openByAddr(localAddr, (GateMP_Handle *)&(obj->gate));
        if (status != GateMP_S_SUCCESS) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return(1);
        }

        return(0);
    }

    /* Creating the heap */
    if (params->gate != NULL) {
        obj->gate       = params->gate;
    }
    else {
        /* If no gate specified, get the default system gate */
        obj->gate       = (ti_sdo_ipc_GateMP_Handle)GateMP_getDefaultRemote();
    }

    obj->bufSize        = params->sharedBufSize;

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

        /* Assert that sharedAddr is cache aligned */
        Assert_isTrue(((UInt32)params->sharedAddr %
                      SharedRegion_getCacheLineSize(obj->regionId) == 0),
                      ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

        obj->objType    = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;

        /* obj->buf will get alignment-adjusted in postInit */
        obj->buf        = (Ptr)((UInt32)params->sharedAddr +
                          sizeof(ti_sdo_ipc_heaps_HeapMemMP_Attrs));
        obj->attrs     = (ti_sdo_ipc_heaps_HeapMemMP_Attrs *)params->sharedAddr;
    }

    obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);

    /* Set minAlign */
    obj->minAlign = sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header);
    if (SharedRegion_getCacheLineSize(obj->regionId) > obj->minAlign) {
        obj->minAlign = SharedRegion_getCacheLineSize(obj->regionId);
    }

    HeapMemMP_postInit(obj, eb);
    if (Error_check(eb)) {
        return(2);
    }

    /* Add entry to NameServer */
    if (params->name != NULL) {
        /* We will store a shared pointer in the NameServer */
        sharedShmBase = SharedRegion_getSRPtr(obj->attrs,
                                              obj->regionId);
        obj->nsKey = NameServer_addUInt32((NameServer_Handle)
                HeapMemMP_module->nameServer, params->name,
                (UInt32)sharedShmBase);

        if (obj->nsKey == NULL) {
            /* NameServer_addUInt32 failed */
            Error_raise(eb, ti_sdo_ipc_Ipc_E_nameFailed, params->name, 0);
            return (3);
        }
    }

    return (0);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMemMP_Instance_finalize ========
 */
Void ti_sdo_ipc_heaps_HeapMemMP_Instance_finalize(
        ti_sdo_ipc_heaps_HeapMemMP_Object *obj, Int status)
{
    if (obj->objType & (ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC |
                        ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION)) {
        /* Remove entry from NameServer */
        if (obj->nsKey != NULL) {
            NameServer_removeEntry((NameServer_Handle)
                    HeapMemMP_module->nameServer, obj->nsKey);
        }

        if (obj->attrs != NULL) {
            /* Set status to 'not created' */
            obj->attrs->status = 0;
            if (obj->cacheEnabled) {
                Cache_wbInv(obj->attrs,
                            sizeof(ti_sdo_ipc_heaps_HeapMemMP_Attrs),
                            Cache_Type_ALL, TRUE);
            }
        }

        /*
         *  Free the shared memory back to the region heap. If NULL, then the
         *  Memory_alloc failed.
         */
        if (obj->objType == ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION
            && obj->attrs != NULL) {
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
 * NOTE:
 * Embedded within the code for HeapMemMP_alloc and HeapMemMP_free are comments
 * that can be used to match a shared memory reference with its required
 * cache call.  This is done because the code for alloc and free is complex.
 * These two-character comments indicate
 * 1) The type of cache operation that is being performed {A, B}
 *    A = Cache_inv
 *    B = Cache_wbInv
 * 2) A numerical id of the specific cache call that is performed.
 *    1, 2, 3
 *    For example, the comment 'A2' indicates that the corresponding cache call
 *    is a Cache_inv operation identified by the number '2'
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapMemMP_alloc ========
 *  HeapMemMP is implemented such that all of the memory and blocks it works
 *  with have an alignment that is a multiple of the minimum alignment and have
 *  a size which is a multiple of the minAlign. Maintaining this requirement
 *  throughout the implementation ensures that there are never any odd
 *  alignments or odd block sizes to deal with.
 *
 *  Specifically:
 *  The buffer managed by HeapMemMP:
 *    1. Is aligned on a multiple of obj->minAlign
 *    2. Has an adjusted size that is a multiple of obj->minAlign
 *  All blocks on the freelist:
 *    1. Are aligned on a multiple of obj->minAlign
 *    2. Have a size that is a multiple of obj->minAlign
 *  All allocated blocks:
 *    1. Are aligned on a multiple of obj->minAlign
 *    2. Have a size that is a multiple of obj->minAlign
 *
 */
Ptr ti_sdo_ipc_heaps_HeapMemMP_alloc(ti_sdo_ipc_heaps_HeapMemMP_Object *obj,
    SizeT reqSize, SizeT reqAlign, Error_Block *eb)
{
    IArg key;
    ti_sdo_ipc_heaps_HeapMemMP_Header *prevHeader, *newHeader, *curHeader;
    Char *allocAddr;
    Memory_Size curSize, adjSize;
    SizeT remainSize; /* free memory after allocated memory */
    SizeT adjAlign, offset;

    /* Assert that requested align is a power of 2 */
    Assert_isTrue((reqAlign & (reqAlign - 1)) == 0,
        ti_sdo_ipc_heaps_HeapMemMP_A_align);

    /* Assert that requested block size is non-zero */
    Assert_isTrue(reqSize != 0, ti_sdo_ipc_heaps_HeapMemMP_A_zeroBlock);

    adjSize = (Memory_Size)reqSize;

    /* Make size requested a multiple of obj->minAlign */
    if ((offset = (adjSize & (obj->minAlign - 1))) != 0) {
        adjSize = adjSize + (obj->minAlign - offset);
    }

    /*
     *  Make sure the alignment is at least as large as obj->minAlign
     *  Note: adjAlign must be a power of 2 (by function constraint) and
     *  obj->minAlign is also a power of 2,
     */
    adjAlign = reqAlign;
    if (adjAlign & (obj->minAlign - 1)) {
        /* adjAlign is less than obj->minAlign */
        adjAlign = obj->minAlign;
    }

    /* No need to Cache_inv Attrs- 'head' should be constant */
    prevHeader = &(obj->attrs->head);

    key = GateMP_enter((GateMP_Handle)obj->gate);

    /*
     *  The block will be allocated from curHeader. Maintain a pointer to
     *  prevHeader so prevHeader->next can be updated after the alloc.
     */
    if (obj->cacheEnabled) {
        Cache_inv(prevHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                  Cache_Type_ALL, TRUE); /* A1 */
    }
    curHeader = (ti_sdo_ipc_heaps_HeapMemMP_Header *)
        SharedRegion_getPtr(prevHeader->next); /* A1 */

    /* Loop over the free list. */
    while (curHeader != NULL) {
        /* Invalidate curHeader */
        if (obj->cacheEnabled) {
            Cache_inv(curHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                      Cache_Type_ALL, TRUE); /* A2 */
        }
        curSize = curHeader->size;

        /*
         *  Determine the offset from the beginning to make sure
         *  the alignment request is honored.
         */
        offset = (Memory_Size)curHeader & (adjAlign - 1);
        if (offset) {
            offset = adjAlign - offset;
        }

        /* Internal Assert that offset is a multiple of obj->minAlign */
        Assert_isTrue(((offset & (obj->minAlign - 1)) == 0),
                ti_sdo_ipc_Ipc_A_internal);

        /* big enough? */
        if (curSize >= (adjSize + offset)) {

            /* Set the pointer that will be returned. Alloc from front */
            allocAddr = (Char *)((Memory_Size)curHeader + offset);

            /*
             *  Determine the remaining memory after the allocated block.
             *  Note: this cannot be negative because of above comparison.
             */
            remainSize = curSize - adjSize - offset;

            /* Internal Assert that remainSize is a multiple of obj->minAlign */
            Assert_isTrue(((remainSize & (obj->minAlign - 1)) == 0),
                           ti_sdo_ipc_Ipc_A_internal);

            /*
             *  If there is memory at the beginning (due to alignment
             *  requirements), maintain it in the list.
             *
             *  offset and remainSize must be multiples of
             *  sizeof(HeapMemMP_Header). Therefore the address of the newHeader
             *  below must be a multiple of the sizeof(HeapMemMP_Header), thus
             *  maintaining the requirement.
             */
            if (offset) {

                /* Adjust the curHeader size accordingly */
                curHeader->size = offset; /* B2 */
                /* Cache wb at end of this if block */

                /*
                 *  If there is remaining memory, add into the free list.
                 *  Note: no need to coalesce and we have HeapMemMP locked so
                 *        it is safe.
                 */
                if (remainSize) {
                    newHeader = (ti_sdo_ipc_heaps_HeapMemMP_Header *)
                        ((Memory_Size)allocAddr + adjSize);

                    /* curHeader has been inv at top of 'while' loop */
                    newHeader->next = curHeader->next;  /* B1 */
                    newHeader->size = remainSize;       /* B1 */
                    if (obj->cacheEnabled) {
                        /* Writing back curHeader will cache-wait */
                        Cache_wbInv(newHeader,
                                sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                                Cache_Type_ALL, FALSE); /* B1 */
                    }

                    curHeader->next = SharedRegion_getSRPtr(newHeader,
                                                            obj->regionId);
                }
                /* Write back (and invalidate) newHeader and curHeader */
                if (obj->cacheEnabled) {
                    /* B2 */
                    Cache_wbInv(curHeader,
                            sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                            Cache_Type_ALL, TRUE);
                }
            }
            else {
                /*
                 *  If there is any remaining, link it in,
                 *  else point to the next free block.
                 *  Note: no need to coalesce and we have HeapMemMP locked so
                 *        it is safe.
                 */
                if (remainSize) {
                    newHeader = (ti_sdo_ipc_heaps_HeapMemMP_Header *)
                        ((Memory_Size)allocAddr + adjSize);

                    newHeader->next  = curHeader->next; /* A2, B3  */
                    newHeader->size  = remainSize;      /* B3      */

                    if (obj->cacheEnabled) {
                        /* Writing back prevHeader will cache-wait */
                        Cache_wbInv(newHeader,
                                sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                                Cache_Type_ALL, FALSE); /* B3 */
                    }

                    /* B4 */
                    prevHeader->next = SharedRegion_getSRPtr(newHeader,
                                                             obj->regionId);
                }
                else {
                    /* curHeader has been inv at top of 'while' loop */
                    prevHeader->next = curHeader->next; /* A2, B4 */
                }

                if (obj->cacheEnabled) {
                    /* B4 */
                    Cache_wbInv(prevHeader,
                            sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                            Cache_Type_ALL, TRUE);
                }
            }

            GateMP_leave((GateMP_Handle)obj->gate, key);

            /* Success, return the allocated memory */
            return ((Ptr)allocAddr);
        }
        else {
            prevHeader = curHeader;
            curHeader = SharedRegion_getPtr(curHeader->next);
        }
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    Error_raise(eb, ti_sdo_ipc_heaps_HeapMemMP_E_memory, (IArg)obj,
            (IArg)reqSize);

    return (NULL);
}

/*
 *  ======== ti_sdo_ipc_heaps_HeapMemMP_free ========
 */
Void ti_sdo_ipc_heaps_HeapMemMP_free(ti_sdo_ipc_heaps_HeapMemMP_Object *obj,
        Ptr addr, SizeT size)
{
    IArg key;
    ti_sdo_ipc_heaps_HeapMemMP_Header *curHeader, *newHeader, *nextHeader;
    SizeT offset;

    /* Assert that 'addr' is cache aligned  */
    Assert_isTrue(((UInt32)addr % obj->minAlign == 0),
            ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

    /* Restore size to actual allocated size */
    offset = size & (obj->minAlign - 1);
    if (offset != 0) {
        size += obj->minAlign - offset;
    }

    newHeader = (ti_sdo_ipc_heaps_HeapMemMP_Header *)addr;

    /*
     *  Invalidate entire buffer being freed to ensure that stale cache
     *  data in block isn't evicted later
     */
    if (obj->cacheEnabled) {
        Cache_inv(newHeader, size, Cache_Type_ALL, FALSE);
    }

    /*
     * obj->attrs never changes, doesn't need Gate protection
     * and Cache invalidate
     */
    curHeader = &(obj->attrs->head);

    key = GateMP_enter((GateMP_Handle)obj->gate);

    if (obj->cacheEnabled) {
        /* A1 */
        Cache_inv(curHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                Cache_Type_ALL, TRUE);
    }

    nextHeader = SharedRegion_getPtr(curHeader->next);

    /* Make sure the entire buffer is in the range of the heap. */
    Assert_isTrue((((SizeT)newHeader >= (SizeT)obj->buf) &&
                   ((SizeT)newHeader + size <=
                    (SizeT)obj->buf + obj->bufSize)),
                   ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree);

    /* Go down freelist and find right place for buf */
    while (nextHeader != NULL && nextHeader < newHeader) {
        if (obj->cacheEnabled) {
            Cache_inv(nextHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                      Cache_Type_ALL, FALSE); /* A2 */
        }

        /* Make sure the addr is not in this free block */
        Assert_isTrue((SizeT)newHeader >= (SizeT)nextHeader + nextHeader->size,
                       ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree); /* A2 */
        curHeader = nextHeader;
        /* A2 */
        nextHeader = SharedRegion_getPtr(nextHeader->next);
    }

    /* B2 */
    newHeader->next = SharedRegion_getSRPtr(nextHeader, obj->regionId);
    newHeader->size = size;

    /* B1, A1 */
    curHeader->next = SharedRegion_getSRPtr(newHeader, obj->regionId);

    /* Join contiguous free blocks */
    if (nextHeader != NULL) {
        /*
         *  Verify the free size is not overlapping. Not all cases are
         *  detectable, but it is worth a shot. Note: only do this
         *  assert if nextHeader is non-NULL.
         */
        Assert_isTrue(((SizeT)newHeader + size) <= (SizeT)nextHeader,
                      ti_sdo_ipc_heaps_HeapMemMP_A_invalidFree);

        /* Join with upper block */
        if (((Memory_Size)newHeader + size) == (Memory_Size)nextHeader) {
            if (obj->cacheEnabled) {
                Cache_inv(nextHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                          Cache_Type_ALL, TRUE);
            }
            newHeader->next = nextHeader->next; /* A2, B2 */
            newHeader->size += nextHeader->size; /* A2, B2 */
            size += obj->minAlign;

            /* Don't Cache_wbInv, this will be done later */
        }
    }

    /*
     *  Join with lower block. Make sure to check to see if not the
     *  first block. No need to invalidate attrs since head shouldn't change.
     */
    if ((curHeader != &obj->attrs->head) &&
        ((Memory_Size)curHeader + curHeader->size == (Memory_Size)newHeader)) {
        /*
         * Don't Cache_inv newHeader since newHeader has data that
         * hasn't been written back yet (B2)
         */
        curHeader->next = newHeader->next; /* B1, B2 */
        curHeader->size += newHeader->size; /* B1, B2 */
    }

    if (obj->cacheEnabled) {
        Cache_wbInv(curHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
             Cache_Type_ALL, FALSE); /* B1 */
        /*
         *  writeback invalidate the new header
         */
        Cache_wbInv(newHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
             Cache_Type_ALL, TRUE);  /* B2 */
       /*
        *  Invalidate entire buffer being freed to ensure that stale cache
        *  data in block isn't evicted later
        */
        Cache_inv(newHeader, size, Cache_Type_ALL, TRUE);  /* B2 */
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);
}

/*
 *  ======== HeapMemMP_isBlocking ========
 */
Bool ti_sdo_ipc_heaps_HeapMemMP_isBlocking(
        ti_sdo_ipc_heaps_HeapMemMP_Object *obj)
{
    Bool flag = FALSE;

    // TODO figure out how to determine whether the gate is blocking...
    return (flag);
}

/*
 *  ======== HeapMemMP_getStats ========
 */
Void ti_sdo_ipc_heaps_HeapMemMP_getStats(ti_sdo_ipc_heaps_HeapMemMP_Object *obj,
        Memory_Stats *stats)
{
    IArg key;
    ti_sdo_ipc_heaps_HeapMemMP_Header *curHeader;

    stats->totalSize         = obj->bufSize;
    stats->totalFreeSize     = 0;  /* determined later */
    stats->largestFreeSize   = 0;  /* determined later */

    key = GateMP_enter((GateMP_Handle)obj->gate);

    if (obj->cacheEnabled) {
        Cache_inv(&(obj->attrs->head),
                sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header), Cache_Type_ALL,
                TRUE);
    }

    curHeader = SharedRegion_getPtr(obj->attrs->head.next);

    while (curHeader != NULL) {
        /* Invalidate curHeader */
        if (obj->cacheEnabled) {
            Cache_inv(curHeader, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Header),
                      Cache_Type_ALL, TRUE);
        }
        stats->totalFreeSize += curHeader->size;
        if (stats->largestFreeSize < curHeader->size) {
            stats->largestFreeSize = curHeader->size;
        }
        curHeader = SharedRegion_getPtr(curHeader->next);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_heaps_HeapMemMP_postInit ========
 */
Void ti_sdo_ipc_heaps_HeapMemMP_postInit(ti_sdo_ipc_heaps_HeapMemMP_Object *obj,
        Error_Block *eb)
{
    HeapMemMP_Params params;
    IHeap_Handle regionHeap;

    if (obj->attrs == NULL) {
        /* Need to allocate from the heap */
        HeapMemMP_Params_init(&params);
        params.regionId = obj->regionId;
        params.sharedBufSize = obj->bufSize;
        obj->allocSize = HeapMemMP_sharedMemReq(&params);

        regionHeap = SharedRegion_getHeap(obj->regionId);
        Assert_isTrue(regionHeap != NULL, ti_sdo_ipc_SharedRegion_A_noHeap);
        obj->attrs = Memory_alloc(regionHeap,
                                  obj->allocSize,
                                  obj->minAlign, eb);
        if (obj->attrs == NULL) {
            return;
        }

        obj->buf = (Ptr)((UInt32)obj->attrs +
                sizeof(ti_sdo_ipc_heaps_HeapMemMP_Attrs));
    }

    /* Round obj->buf up by obj->minAlign */
    obj->buf = (Ptr)_Ipc_roundup(obj->buf, obj->minAlign);

    /* Verify the buffer is large enough */
    Assert_isTrue((obj->bufSize >=
            SharedRegion_getCacheLineSize(obj->regionId)),
            ti_sdo_ipc_heaps_HeapMemMP_A_heapSize);

    /* Make sure the size is a multiple of obj->minAlign */
    obj->bufSize = (obj->bufSize / obj->minAlign) * obj->minAlign;

    obj->attrs->gateMPAddr = ti_sdo_ipc_GateMP_getSharedAddr(obj->gate);
    obj->attrs->bufPtr = SharedRegion_getSRPtr(obj->buf, obj->regionId);

    /* Store computed obj->bufSize in shared mem */
    obj->attrs->head.size = obj->bufSize;

    /* Place the initial header */
    HeapMemMP_restore((HeapMemMP_Handle)obj);

    /* Last thing, set the status */
    obj->attrs->status = ti_sdo_ipc_heaps_HeapMemMP_CREATED;

    if (obj->cacheEnabled) {
        Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_heaps_HeapMemMP_Attrs),
                Cache_Type_ALL, TRUE);
    }

}
