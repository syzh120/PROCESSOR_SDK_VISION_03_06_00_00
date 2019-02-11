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
 *  ======== SharedRegion.c ========
 *  Implementation of functions specified in SharedRegion.xdc.
 */

#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Memory.h>

#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/ipc/heaps/_HeapMemMP.h>

#include "package/internal/SharedRegion.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(SharedRegion_clearEntry);
    #pragma FUNC_EXT_CALLED(SharedRegion_getCacheLineSize);
    #pragma FUNC_EXT_CALLED(SharedRegion_getEntry);
    #pragma FUNC_EXT_CALLED(SharedRegion_getEntryPtr);
    #pragma FUNC_EXT_CALLED(SharedRegion_getHeap);
    #pragma FUNC_EXT_CALLED(SharedRegion_getId);
    #pragma FUNC_EXT_CALLED(SharedRegion_getIdByName);
    #pragma FUNC_EXT_CALLED(SharedRegion_getNumRegions);
    #pragma FUNC_EXT_CALLED(SharedRegion_getPtr);
    #pragma FUNC_EXT_CALLED(SharedRegion_getSRPtr);
    #pragma FUNC_EXT_CALLED(SharedRegion_isCacheEnabled);
    #pragma FUNC_EXT_CALLED(SharedRegion_setEntry);
    #pragma FUNC_EXT_CALLED(SharedRegion_translateEnabled);
    #pragma FUNC_EXT_CALLED(SharedRegion_invalidSRPtr);
#endif

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== SharedRegion_clearEntry ========
 *  Clears the region in the table.
 */
Int SharedRegion_clearEntry(UInt16 id)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    HeapMemMP_Handle    heapMemHandle;
    UInt16 myId, ownerProcId;
    Int status = HeapMemMP_S_SUCCESS;
    UInt key;

    /* Need to make sure id is smaller than numEntries */
    Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries), ti_sdo_ipc_SharedRegion_A_idTooLarge);

    /* Need to make sure not trying to clear Region 0 */
    Assert_isTrue(id != 0, ti_sdo_ipc_SharedRegion_A_region0Clear);

    myId = MultiProc_self();

    /* get the region */
    region = &(SharedRegion_module->regions[id]);

    /* store these fields to local variables */
    ownerProcId = region->entry.ownerProcId;
    heapMemHandle  = (HeapMemMP_Handle)region->heap;

    /* needs to be thread safe */
    key = Hwi_disable();

    /* clear region to their defaults */
    region->entry.isValid       = FALSE;
    region->entry.base          = NULL;
    region->entry.len           = 0;
    region->entry.ownerProcId   = 0;
    region->entry.cacheEnable   = TRUE;
    region->entry.cacheLineSize = ti_sdo_ipc_SharedRegion_cacheLineSize;
    region->entry.createHeap    = TRUE;
    region->entry.name          = NULL;
    region->reservedSize        = 0;
    region->heap                = NULL;

    /* leave the gate */
    Hwi_restore(key);

    /* delete or close previous created heap outside the gate */
    if (heapMemHandle != NULL) {
        if (ownerProcId == myId) {
            status = HeapMemMP_delete(&heapMemHandle);
        }
        else if (ownerProcId != MultiProc_INVALIDID) {
            status = HeapMemMP_close(&heapMemHandle);
        }
    }

    if (status == HeapMemMP_S_SUCCESS) {
        status = SharedRegion_S_SUCCESS;
    }
    else {
        status = SharedRegion_E_FAIL;
    }

    return (status);
}

/*
 *  ======== SharedRegion_getCacheLineSize ========
 */
SizeT SharedRegion_getCacheLineSize(UInt16 id)
{
    SizeT cacheLineSize = 0;

    /*
     *  if translate == TRUE or translate == FALSE
     *  and 'id' is not INVALIDREGIONID, then Assert id is valid.
     *  Return the heap associated with the region id.
     *
     *  If those conditions are not met, the id is from
     *  an addres in local memory so return NULL.
     */
    if ((ti_sdo_ipc_SharedRegion_translate) ||
        ((ti_sdo_ipc_SharedRegion_translate == FALSE) &&
        (id != SharedRegion_INVALIDREGIONID))) {
        /* Need to make sure id is smaller than numEntries */
        Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries),
            ti_sdo_ipc_SharedRegion_A_idTooLarge);

        cacheLineSize = SharedRegion_module->regions[id].entry.cacheLineSize;
    }

    return (cacheLineSize);
}

/*
 *  ======== SharedRegion_getEntry ========
 */
Int SharedRegion_getEntry(UInt16 id, SharedRegion_Entry *entry)
{
    ti_sdo_ipc_SharedRegion_Region *region;

    /* Make sure entry is not NULL */
    Assert_isTrue((entry != NULL), ti_sdo_ipc_Ipc_A_nullArgument);

    /* Need to make sure id is smaller than numEntries */
    Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries), ti_sdo_ipc_SharedRegion_A_idTooLarge);

    region = &(SharedRegion_module->regions[id]);

    entry->base          = region->entry.base;
    entry->len           = region->entry.len;
    entry->ownerProcId   = region->entry.ownerProcId;
    entry->isValid       = region->entry.isValid;
    entry->cacheEnable   = region->entry.cacheEnable;
    entry->cacheLineSize = region->entry.cacheLineSize;
    entry->createHeap    = region->entry.createHeap;
    entry->name          = region->entry.name;

    return (SharedRegion_S_SUCCESS);
}

/*
 *  ======== SharedRegion_getEntryPtr ========
 */
SharedRegion_Entry *SharedRegion_getEntryPtr(UInt16 id)
{
    ti_sdo_ipc_SharedRegion_Region *region;

    region = &(SharedRegion_module->regions[id]);
    return ((SharedRegion_Entry *)(&region->entry));
}

/*
 *  ======== SharedRegion_getId ========
 *  Returns the id of shared region that the pointer resides in.
 *  Returns SharedRegion_INVALIDREGIONID if no region is found.
 */
UInt16 SharedRegion_getId(Ptr addr)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    UInt i;
    UInt key;
    UInt16 regionId = SharedRegion_INVALIDREGIONID;

    /* Try to find the entry that contains the address */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);

        /* needs to be thread safe */
        key = Hwi_disable();

        if ((region->entry.isValid) && (addr >= region->entry.base) &&
            (addr < (Ptr)((UInt32)region->entry.base + region->entry.len))) {
            regionId = i;

            /* leave the gate */
            Hwi_restore(key);
            break;
        }

        /* leave the gate */
        Hwi_restore(key);
    }

    return (regionId);
}

/*
 *  ======== SharedRegion_getIdByName ========
 *  Returns the id of shared region that matches name.
 *  Returns SharedRegion_INVALIDREGIONID if no region is found.
 */
UInt16 SharedRegion_getIdByName(String name)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    UInt16 i;
    UInt key;
    UInt16 regionId = SharedRegion_INVALIDREGIONID;

    /* loop through entries to find matching name */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);

        /* needs to be thread safe */
        key = Hwi_disable();

        if (region->entry.isValid) {
            if (strcmp(region->entry.name, name) == 0) {
                regionId = i;

                /* leave the gate */
                Hwi_restore(key);
                break;
            }
        }

        /* leave the gate */
            Hwi_restore(key);
    }

    return (regionId);
}

/*
 *  ======== SharedRegion_getNumRegions ========
 */
UInt16 SharedRegion_getNumRegions(Void)
{
    return (ti_sdo_ipc_SharedRegion_numEntries);
}

/*
 *  ======== SharedRegion_getPtr ========
 *  This function takes a shared region pointer and returns a pointer.
 */
Ptr SharedRegion_getPtr(SharedRegion_SRPtr srPtr)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    Ptr returnPtr;
    UInt16 regionId;

    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        returnPtr = (Ptr)srPtr;
    }
    else if (srPtr == ti_sdo_ipc_SharedRegion_INVALIDSRPTR) {
        returnPtr = NULL;
    }
    else {
        /* find regionId from srPtr */
        regionId = (UInt32)srPtr >> ti_sdo_ipc_SharedRegion_numOffsetBits;

        /* make sure regionId of SRPtr less than numEntries */
        Assert_isTrue(regionId < ti_sdo_ipc_SharedRegion_numEntries,
            ti_sdo_ipc_SharedRegion_A_idTooLarge);

        region = &(SharedRegion_module->regions[regionId]);

        /* Make sure the region is valid */
        Assert_isTrue(region->entry.isValid == TRUE,
                ti_sdo_ipc_SharedRegion_A_regionInvalid);

        returnPtr = (Ptr)((srPtr & ti_sdo_ipc_SharedRegion_offsetMask) +
                          (UInt32)region->entry.base);
    }

    return (returnPtr);
}

/*
 *  ======== SharedRegion_getSRPtr ========
 *  This function takes a pointer and an id and returns a shared region
 *  pointer.
 */
SharedRegion_SRPtr SharedRegion_getSRPtr(Ptr addr, UInt16 id)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    SharedRegion_SRPtr retPtr;

    /* if translate == false, set SRPtr to addr */
    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        retPtr = (SharedRegion_SRPtr)addr;
    }
    else if (addr == NULL) {
        retPtr = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
    }
    else {
        /* Need to make sure id is smaller than numEntries */
        Assert_isTrue(id < ti_sdo_ipc_SharedRegion_numEntries,
            ti_sdo_ipc_SharedRegion_A_idTooLarge);

        region = &(SharedRegion_module->regions[id]);

        /*
         *  Note: The very last byte on the very last id cannot be mapped
         *        because ti_sdo_ipc_SharedRegion_INVALIDSRPTR which is ~0 denotes an
         *        error. Since pointers should be word aligned, we don't
         *        expect this to be a problem.
         *
         *        ie: numEntries = 4,
         *            id = 3, base = 0x00000000, len = 0x40000000
         *            ==> address 0x3fffffff would be invalid because the
         *                SRPtr for this address is 0xffffffff
         */
        if (((UInt32)addr >= (UInt32)region->entry.base) &&
            ((UInt32)addr < ((UInt32)region->entry.base + region->entry.len))) {
            retPtr = (SharedRegion_SRPtr)((id << ti_sdo_ipc_SharedRegion_numOffsetBits)
                     | ((UInt32)addr - (UInt32)region->entry.base));
        }
        else {
            Assert_isTrue(FALSE, ti_sdo_ipc_SharedRegion_A_addrOutOfRange);
            retPtr = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
        }
    }

    return (retPtr);
}

/*
 *  ======== SharedRegion_isCacheEnabled ========
 */
Bool SharedRegion_isCacheEnabled(UInt16 id)
{
    Bool cacheEnable = FALSE;

    /*
     *  if translate == TRUE or translate == FALSE
     *  and 'id' is not INVALIDREGIONID, then Assert id is valid.
     *  Return the heap associated with the region id.
     *
     *  If those conditions are not met, the id is from
     *  an address in local memory so return NULL.
     */
    if ((ti_sdo_ipc_SharedRegion_translate) ||
        ((ti_sdo_ipc_SharedRegion_translate == FALSE) &&
        (id != SharedRegion_INVALIDREGIONID))) {
        /* Need to make sure id is smaller than numEntries */
        Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries),
            ti_sdo_ipc_SharedRegion_A_idTooLarge);

        cacheEnable = SharedRegion_module->regions[id].entry.cacheEnable;
    }

    return (cacheEnable);
}

/*
 *  ======== SharedRegion_setEntry ========
 *  Sets the region specified in the table.
 */
Int SharedRegion_setEntry(UInt16 id, SharedRegion_Entry *entry)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    HeapMemMP_Params    params;
    HeapMemMP_Handle    heapHandle;
    HeapMemMP_Handle    *heapHandlePtr;
    UInt                key;
    Ptr                 sharedAddr;
    Int status = SharedRegion_S_SUCCESS;
    Error_Block eb;

    /* Need to make sure id is smaller than numEntries */
    Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries),
        ti_sdo_ipc_SharedRegion_A_idTooLarge);

    /* Make sure entry is not NULL */
    Assert_isTrue((entry != NULL), ti_sdo_ipc_Ipc_A_nullArgument);

    Error_init(&eb);

    region = &(SharedRegion_module->regions[id]);

    /* make sure region does not overlap existing ones */
    status = SharedRegion_checkOverlap(entry->base, entry->len);

    if (status == SharedRegion_S_SUCCESS) {
        /* region entry should be invalid at this point */
        if (region->entry.isValid) {
            /* Assert that a region already exists */
            Assert_isTrue(FALSE, ti_sdo_ipc_SharedRegion_A_alreadyExists);
            status = SharedRegion_E_ALREADYEXISTS;
            return (status);
        }

        /* Assert if cacheEnabled and cacheLineSize equal 0 */
        if ((entry->cacheEnable) && (entry->cacheLineSize == 0)) {
            /* if cache enabled, cache line size must != 0 */
            Assert_isTrue(FALSE, ti_sdo_ipc_SharedRegion_A_cacheLineSizeIsZero);
        }

        /* needs to be thread safe */
        key = Hwi_disable();

        /* set specified region id to entry values */
        region->entry.base          = entry->base;
        region->entry.len           = entry->len;
        region->entry.ownerProcId   = entry->ownerProcId;
        region->entry.cacheEnable   = entry->cacheEnable;
        region->entry.cacheLineSize = entry->cacheLineSize;
        region->entry.createHeap    = entry->createHeap;
        region->entry.name          = entry->name;
        region->entry.isValid       = entry->isValid;

        /* leave gate */
        Hwi_restore(key);

        if (!region->entry.isValid) {
            /* Region isn't valid yet */
            return (status);
        }

        if (entry->ownerProcId == MultiProc_self()) {
            if ((entry->createHeap) && (region->heap == NULL)) {
                /* get current Ptr (reserve memory with size of 0) */
                sharedAddr = ti_sdo_ipc_SharedRegion_reserveMemory(id, 0);

                HeapMemMP_Params_init(&params);
                params.sharedAddr = sharedAddr;
                params.sharedBufSize = region->entry.len -
                                       region->reservedSize;

                /*
                 *  Calculate size of HeapMemMP_Attrs and adjust sharedBufSize
                 *  Size of HeapMemMP_Attrs = HeapMemMP_sharedMemReq(&params) -
                 *                            params.sharedBufSize
                 */
                params.sharedBufSize -= (HeapMemMP_sharedMemReq(&params)
                                         - params.sharedBufSize);

                heapHandle = HeapMemMP_create(&params);
                if (heapHandle == NULL) {
                    region->entry.isValid = FALSE;
                    return (SharedRegion_E_MEMORY);
                }

                region->heap = (IHeap_Handle)heapHandle;
            }
        }
        else {
            if ((entry->createHeap) && (region->heap == NULL)) {
                /* sharedAddr should match creator's for each region */
                sharedAddr = (Ptr)((UInt32)entry->base +
                    region->reservedSize);

                /* set the pointer to a heap handle */
                heapHandlePtr = (HeapMemMP_Handle *)&(region->heap);

                /* open the heap by address */
                if (HeapMemMP_openByAddr(sharedAddr, heapHandlePtr) !=
                    HeapMemMP_S_SUCCESS) {
                    status = SharedRegion_E_FAIL;
                    region->entry.isValid = FALSE;
                }
            }
        }
    }

    return (status);
}

/*
 *  ======== SharedRegion_checkOverlap ========
 *  Checks to make sure overlap does not exists.
 */
Int SharedRegion_checkOverlap(Ptr base, SizeT len)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    UInt i;
    UInt key;

    /* needs to be thread safe */
    key = Hwi_disable();

    /* check to make sure new region does not overlap existing ones */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);
        if (region->entry.isValid) {
            if (base >= region->entry.base) {
                if (base < (Ptr)((UInt32)region->entry.base +
                    region->entry.len)) {
                    Hwi_restore(key);
                    Assert_isTrue(FALSE, ti_sdo_ipc_SharedRegion_A_overlap);
                    return (SharedRegion_E_FAIL);
                }
            }
            else {
                if ((Ptr)((UInt32)base + len) > region->entry.base) {
                    Hwi_restore(key);
                    Assert_isTrue(FALSE, ti_sdo_ipc_SharedRegion_A_overlap);
                    return (SharedRegion_E_FAIL);
                }
            }
        }
    }

    Hwi_restore(key);

    return (SharedRegion_S_SUCCESS);
}


/*
 *  ======== SharedRegion_entryInit ========
 */
Void SharedRegion_entryInit(SharedRegion_Entry *entry)
{
    /* Make sure entry is not NULL */
    Assert_isTrue((entry != NULL), ti_sdo_ipc_Ipc_A_nullArgument);

    /* init the entry to default values */
    entry->base          = NULL;
    entry->len           = 0;
    entry->ownerProcId   = 0;
    entry->cacheEnable   = TRUE;
    entry->cacheLineSize = ti_sdo_ipc_SharedRegion_cacheLineSize;
    entry->createHeap    = TRUE;
    entry->name          = NULL;
    entry->isValid       = FALSE;
}

/*
 *  ======== SharedRegion_getHeap ========
 */
Ptr SharedRegion_getHeap(UInt16 id)
{
    IHeap_Handle heap = NULL;

    /*
     *  if translate == TRUE or translate == FALSE
     *  and 'id' is not INVALIDREGIONID, then Assert id is valid.
     *  Return the heap associated with the region id.
     *
     *  If those conditions are not met, the id is from
     *  an addres in local memory so return NULL.
     */
    if ((ti_sdo_ipc_SharedRegion_translate) ||
        ((ti_sdo_ipc_SharedRegion_translate == FALSE) &&
        (id != SharedRegion_INVALIDREGIONID))) {

        /* assert id is valid */
        Assert_isTrue(id < ti_sdo_ipc_SharedRegion_numEntries,
            ti_sdo_ipc_SharedRegion_A_idTooLarge);

        heap = SharedRegion_module->regions[id].heap;
    }

    return (heap);
}

/*
 *  ======== SharedRegion_translateEnabled ========
 */
Bool SharedRegion_translateEnabled(Void)
{
    return (ti_sdo_ipc_SharedRegion_translate);
}

/*
 *  ======== SharedRegion_invalidSRPtr ========
 */
SharedRegion_SRPtr SharedRegion_invalidSRPtr(Void)
{
    return (ti_sdo_ipc_SharedRegion_INVALIDSRPTR);
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_SharedRegion_attach ========
 */
Int ti_sdo_ipc_SharedRegion_attach(UInt16 remoteProcId)
{
    Int i;
    Ptr sharedAddr;
    ti_sdo_ipc_SharedRegion_Region *region;
    HeapMemMP_Handle    *heapHandlePtr;
    Int status = SharedRegion_S_SUCCESS;

    /*
     *  Loop through the regions and open the heap if not owner
     */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);
        if ((region->entry.isValid) &&
            (region->entry.ownerProcId != MultiProc_self()) &&
            (region->entry.ownerProcId != MultiProc_INVALIDID) &&
            (region->entry.createHeap) &&
            (region->heap == NULL)) {
            /* sharedAddr should match creator's for each region */
            sharedAddr = (Ptr)((UInt32)region->entry.base +
                region->reservedSize);

            /* get the heap handle from SharedRegion Module state */
            heapHandlePtr = (HeapMemMP_Handle *)&(region->heap);

            /* heap should already be created so open by address */
            status = HeapMemMP_openByAddr(sharedAddr, heapHandlePtr);
        }
    }

    return(status);
}

/*
 *  ======== ti_sdo_ipc_SharedRegion_detach ========
 */
Int ti_sdo_ipc_SharedRegion_detach(UInt16 remoteProcId)
{
    Int i;
    ti_sdo_ipc_SharedRegion_Region *region;
    HeapMemMP_Handle    *heapHandlePtr;
    Int status = SharedRegion_S_SUCCESS;

    /*
     *  Loop through the regions and close the heap only when
     *  detaching from owner of heap.
     */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);
        if ((region->entry.isValid) &&
            (region->entry.ownerProcId == remoteProcId) &&
            (region->heap != NULL)) {
            /* get the heap handle from SharedRegion Module state */
            heapHandlePtr = (HeapMemMP_Handle *)&(region->heap);

            /* heap should already be created so open by address */
            status = HeapMemMP_close(heapHandlePtr);
        }
    }

    return(status);
}

/*
 *  ======== ti_sdo_ipc_SharedRegion_clearReservedMemory ========
 *  Clears the reserve memory for each region in the table.
 */
Void ti_sdo_ipc_SharedRegion_clearReservedMemory()
{
    Int i;
    ti_sdo_ipc_SharedRegion_Region *region;

    /*
     *  Loop through shared regions. If an owner of a region is specified,
     *  the owner zeros out the reserved memory in each region.
     */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);
        if ((region->entry.isValid) &&
            (region->entry.ownerProcId == MultiProc_self())) {
            /* clear reserved memory */
            memset(region->entry.base, 0, region->reservedSize);

            /* writeback invalidate the cache if enabled in region */
            if (region->entry.cacheEnable) {
                Cache_wbInv(region->entry.base, region->reservedSize,
                         Cache_Type_ALL, TRUE);
            }
        }
    }
}

/*
 *  ======== ti_sdo_ipc_SharedRegion_reserveMemory ========
 */
Ptr ti_sdo_ipc_SharedRegion_reserveMemory(UInt16 id, SizeT size)
{
    ti_sdo_ipc_SharedRegion_Region *region;
    UInt32 minAlign;
    SizeT curSize, newSize;
    Ptr   retPtr;

    /* Need to make sure id is smaller than numEntries */
    Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries),
        ti_sdo_ipc_SharedRegion_A_idTooLarge);

    /* assert that region at specified id is valid */
    Assert_isTrue(SharedRegion_module->regions[id].entry.isValid == TRUE,
                  ti_sdo_ipc_SharedRegion_A_regionInvalid);

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(id) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(id);
    }

    region = &(SharedRegion_module->regions[id]);

    /* Set the current size to the reservedSize */
    curSize = region->reservedSize;

    /* No need to round here since curSize is already aligned */
    retPtr = (Ptr)((UInt32)region->entry.base + curSize);

    /*  Round the new size to the min alignment since */
    newSize = _Ipc_roundup(size, minAlign);

    /* Need to make sure (curSize + newSize) is smaller than region len */
    Assert_isTrue((region->entry.len >= (curSize + newSize)),
                   ti_sdo_ipc_SharedRegion_A_reserveTooMuch);

    /* Add the new size to current size */
    region->reservedSize = curSize + newSize;

    return (retPtr);
}

/*
 *  ======== ti_sdo_ipc_SharedRegion_resetInternalFields ========
 */
Void ti_sdo_ipc_SharedRegion_resetInternalFields(UInt16 id)
{
    ti_sdo_ipc_SharedRegion_Region *region;

    /* Need to make sure id is smaller than numEntries */
    Assert_isTrue((id < ti_sdo_ipc_SharedRegion_numEntries),
        ti_sdo_ipc_SharedRegion_A_idTooLarge);

    region = &(SharedRegion_module->regions[id]);

    region->reservedSize = 0;
}

/*
 *  ======== ti_sdo_ipc_SharedRegion_start ========
 */
Int ti_sdo_ipc_SharedRegion_start(Void)
{
    Int i;
    ti_sdo_ipc_SharedRegion_Region *region;
    HeapMemMP_Params    params;
    HeapMemMP_Handle    heapHandle;
    Ptr                 sharedAddr;
    Int status = SharedRegion_S_SUCCESS;

    /* assert that region 0 is valid */
    Assert_isTrue((ti_sdo_ipc_SharedRegion_numEntries > 0) &&
        (SharedRegion_module->regions[0].entry.isValid),
        ti_sdo_ipc_SharedRegion_A_region0Invalid);

    /*
     *  Loop through shared regions. If an owner of a region is specified
     *  and createHeap has been specified for the SharedRegion, then
     *  the owner creates a HeapMemMP and the other processors open it.
     */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);
        if ((region->entry.isValid) &&
            (region->entry.ownerProcId == MultiProc_self()) &&
            (region->entry.createHeap) &&
            (region->heap == NULL)) {
            /* get the next free address in each region */
            sharedAddr = (Ptr)((UInt32)region->entry.base +
                region->reservedSize);

            /*  Create the HeapMemMP in the region. */
            HeapMemMP_Params_init(&params);
            params.sharedAddr = sharedAddr;
            params.sharedBufSize = region->entry.len - region->reservedSize;

            /* Adjust to account for the size of HeapMemMP_Attrs */
            params.sharedBufSize -= (HeapMemMP_sharedMemReq(&params)
                                    - params.sharedBufSize);
            heapHandle = HeapMemMP_create(&params);

            if (heapHandle == NULL) {
                status = SharedRegion_E_FAIL;
            }
            else {
                /* put heap handle into SharedRegion Module state */
                region->heap = (IHeap_Handle)heapHandle;
            }
        }
    }

    return (status);
}

/*
 *  ======== ti_sdo_ipc_SharedRegion_stop ========
 */
Int ti_sdo_ipc_SharedRegion_stop(Void)
{
    Int i;
    ti_sdo_ipc_SharedRegion_Region *region;
    HeapMemMP_Handle    *heapHandlePtr;
    Int status = SharedRegion_S_SUCCESS;

    /*
     *  Loop through shared regions. If owner then delete the heap,
     *  otherwise the heap should have been closed in detach().
     */
    for (i = 0; i < ti_sdo_ipc_SharedRegion_numEntries; i++) {
        region = &(SharedRegion_module->regions[i]);
        if ((region->entry.isValid) &&
            (region->entry.ownerProcId == MultiProc_self()) &&
            (region->heap != NULL)) {
            /* get the heap handle from SharedRegion Module state */
            heapHandlePtr = (HeapMemMP_Handle *)&(region->heap);

            /* delete the HeapMemMP */
            status = HeapMemMP_delete(heapHandlePtr);
        }
    }

    return (status);
}
