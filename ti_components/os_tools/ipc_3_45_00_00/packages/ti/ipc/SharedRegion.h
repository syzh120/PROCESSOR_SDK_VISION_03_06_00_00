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
/**
 *  @file       ti/ipc/SharedRegion.h
 *
 *  @brief      Shared memory manager and address translator
 *
 *  @note       SharedRegion is currently only available for SYS/BIOS.
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
 *  Note:  The number of entries must be the same on all processors.
 *
 *  Each shared region contains the following:
 *    - @b base - The base address
 *    - @b len - The length
 *    - @b name - The name of the region
 *    - @b isValid - Whether the region is valid
 *    - @b ownerProcId - The id of the processor which owns the region
 *    - @b cacheEnable - Whether the region is cacheable
 *    - @b cacheLineSize - The cache line size
 *    - @b createHeap - Whether a heap is created for the region.
 *
 *  A region is added using the SharedRegion_setEntry() API.
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
 *  After a shared region is valid, SharedRegion APIs can be used to convert
 *  pointers between the local processor's address space and the SharedRegion-
 *  pointer (SRPtr) address space.  These APIs include
 *  SharedRegion_getId(), SharedRegion_getSRPtr() and SharedRegion_getPtr().
 *  An example is shown below:
 *
 *  @code
 *  SharedRegion_SRPtr srptr;
 *  Ptr     addr;
 *  UInt16  id;
 *
 *  // to get the id of the local address if id is not already known.
 *  id = SharedRegion_getId(addr);
 *
 *  // to get the shared region pointer for the local address
 *  srptr = SharedRegion_getSRPtr(addr, id);
 *
 *  // to get the local address from the shared region pointer
 *  addr = SharedRegion_getPtr(srptr);
 *  @endcode
 *
 *  The SharedRegion header should be included in an application as follows:
 *  @code
 *  #include <ti/ipc/SharedRegion.h>
 *  @endcode
 */

#ifndef ti_ipc_SharedRegion__include
#define ti_ipc_SharedRegion__include


#if defined (__cplusplus)
extern "C" {
#endif

/* ============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @brief  The resource is still in use
 */
#define SharedRegion_S_BUSY             2

/*!
 *  @brief  The module has been already setup
 */
#define SharedRegion_S_ALREADYSETUP     1

/*!
 *  @brief  Operation is successful.
 */
#define SharedRegion_S_SUCCESS          0

/*!
 *  @brief  Generic failure.
 */
#define SharedRegion_E_FAIL             -1

/*!
 *  @brief  Argument passed to function is invalid.
 */
#define SharedRegion_E_INVALIDARG       -2

/*!
 *  @brief  Operation resulted in memory failure.
 */
#define SharedRegion_E_MEMORY           -3

/*!
 *  @brief  The specified entity already exists.
 */
#define SharedRegion_E_ALREADYEXISTS    -4

/*!
 *  @brief  Unable to find the specified entity.
 */
#define SharedRegion_E_NOTFOUND         -5

/*!
 *  @brief  Operation timed out.
 */
#define SharedRegion_E_TIMEOUT          -6

/*!
 *  @brief  Module is not initialized.
 */
#define SharedRegion_E_INVALIDSTATE     -7

/*!
 *  @brief  A failure occurred in an OS-specific call
 */
#define SharedRegion_E_OSFAILURE        -8

/*!
 *  @brief  Specified resource is not available
 */
#define SharedRegion_E_RESOURCE         -9

/*!
 *  @brief  Operation was interrupted. Please restart the operation
 */
#define SharedRegion_E_RESTART          -10

/* =============================================================================
 *  Macros
 * =============================================================================
 */

/*!
 *  @brief  Invalid region id
 */
#define SharedRegion_INVALIDREGIONID    (0xFFFF)

/* =============================================================================
 *  Structures & Enums
 * =============================================================================
 */

/*!
 *  @brief  SharedRegion pointer type
 */
typedef Bits32 SharedRegion_SRPtr;

/*!
 *  @brief  Structure defining a region
 */
typedef struct SharedRegion_Entry {
    Ptr base;
    /*!< @brief The base address of the region */

    SizeT len;
    /*!< @brief The length of the region
     *
     *  The length of a region must be the same across all
     *  processors in the system.
     */

    UInt16 ownerProcId;
    /*!< @brief The MultiProc id of the owner of the region
     *
     *  The owner id for a shared region must be the same across
     *  all processors in the system.
     */

    Bool isValid;
    /*!< @brief Whether the region is valid */

    Bool cacheEnable;
    /*!< @brief Whether to perform cache operations for the region
     *
     *  If 'TRUE', a cache invalidate is performed before any read
     *  and a cache write back invalidate is performed after any
     *  write for the shared region.  The cache operations are done
     *  for all caches.  If 'FALSE', no cache operations are performed.
     */

    SizeT cacheLineSize;
    /*!< @brief The cache line size of the region
     *
     *  The cache line size for a region must be the same across
     *  all processors in the system.  It is used for structure
     *  alignment and padding.
     */

    Bool createHeap;
    /*!< @brief Whether a heap is created for the region
     *
     *  If 'TRUE', a HeapMemMP instance is created with the size
     *  spanning the length of the shared region minus any memory
     *  that is reserved in the region.  If 'FALSE', no heap
     *  is created in the shared region.
     */

    String name;
    /*!< @brief The name of the region.
     *
     *  The name must be in persistent memory.  It is used for
     *  displaying in ROV.
     */
} SharedRegion_Entry;


/* =============================================================================
 *  SharedRegion Module-wide Functions
 * =============================================================================
 */

/*!
 *  @brief      Clears the @c regionid entry
 *
 *  SharedRegion_clearEntry() is used to render invalid a shared region that is
 *  currently valid.  If the region has a heap, it will either be closed or
 *  deleted as necessary.  All attributes of region are reset to defaults.
 *
 *  Calling SharedRegion_clearEntry() upon a region that is already invalid
 *  simply resets the region attributes to their defaults.
 *
 *  @note Region #0 is special and can neither be cleared nor set.
 *
 *  @param      regionId  the region id
 *
 *  @return     Status
 *              - #SharedRegion_S_SUCCESS:  Operation was successful
 *              - #SharedRegion_E_FAIL:  Delete or close of heap created
 *                in region failed.
 *
 *  @sa         SharedRegion_setEntry()
 */
Int SharedRegion_clearEntry(UInt16 regionId);

/*!
 *  @brief      Initializes the entry fields
 *
 *  @param      entry  pointer to a SharedRegion entry
 *
 *  @sa         SharedRegion_setEntry()
 */
Void SharedRegion_entryInit(SharedRegion_Entry *entry);

/*!
 *  @brief      Gets the cache line size for the specified region id
 *
 *  @param      regionId  the region id
 *
 *  @return     Cache line size
 *
 *  @sa         SharedRegion_isCacheEnabled()
 */
SizeT SharedRegion_getCacheLineSize(UInt16 regionId);

/*!
 *  @brief      Gets the entry information for the specified region id
 *
 *  @param      regionId  the region id
 *  @param      entry     pointer to return region information
 *
 *  @return     Status
 *              - #SharedRegion_S_SUCCESS:  Operation was successful
 *              - #SharedRegion_E_FAIL:  Operation failed
 *
 *  @sa         SharedRegion_setEntry()
 */
Int SharedRegion_getEntry(UInt16 regionId, SharedRegion_Entry *entry);

/*!
 *  @brief      Return the address of the shared region entry structure
 *
 *  This function is to be used only for module startup configuration.
 *  The returned address gives you direct access to the in-memory entry
 *  structure. Use it to configure the entry just before the module
 *  startup phase begins. It is intended to support single-image loading.
 *
 *  Do not use this function during normal run-time operations; use
 *  SharedRegion_getEntry() instead.
 */
SharedRegion_Entry *SharedRegion_getEntryPtr(UInt16 regionId);

/*!
 *  @brief      Gets the heap associated with the specified region id
 *
 *  The heap handle returned is of type xdc.runtime.IHeap.
 *  This handle type can be used with xdc.runtime.Memory.
 *
 *  The following code shows an example.
 *
 *  @code
 *  #include <xdc/runtime/IHeap.h>
 *  #include <xdc/runtime/Memory.h>
 *  #include <ti/ipc/SharedRegion.h>
 *
 *  IHeap_Handle heap;
 *  UInt16       regionId;
 *  SizeT        size;
 *  SizeT        align;
 *
 *  heap = (IHeap_Handle)SharedRegion_getHeap(regionId);  // get the heap
 *  Memory_alloc(heap, size, align, NULL);  // alloc memory from heap
 *  @endcode
 *
 *  @param      regionId  the region id
 *
 *  @return     Handle of the heap, NULL if the region has no heap
 */
Ptr SharedRegion_getHeap(UInt16 regionId);

/*!
 *  @brief      Gets the region id for the specified address
 *
 *  @param      addr  address
 *
 *  @return     region id
 */
UInt16 SharedRegion_getId(Ptr addr);

/*!
 *  @brief      Gets the id of a region, given its name
 *
 *  @param      name  name of the region
 *
 *  @return     region id
 */
UInt16 SharedRegion_getIdByName(String name);

/*!
 *  @brief      Gets the number of regions
 *
 *  @return     number of regions
 */
UInt16 SharedRegion_getNumRegions(Void);

/*!
 *  @brief      Calculate the local pointer from the shared region pointer
 *
 *  @param      srptr  SharedRegion pointer
 *
 *  @return     local pointer or NULL if shared region pointer is invalid
 *
 *  @sa         SharedRegion_getSRPtr()
 */
Ptr SharedRegion_getPtr(SharedRegion_SRPtr srptr);

/*!
 *  @brief      Calculate the shared region pointer given local address and id
 *
 *  @param      addr      the local address
 *  @param      regionId  region id
 *
 *  @return     SharedRegion pointer
 *
 *  @sa         SharedRegion_getPtr()
 */
SharedRegion_SRPtr SharedRegion_getSRPtr(Ptr addr, UInt16 regionId);

/*!
 *  @brief      whether cache enable was specified
 *
 *  @param      regionId  region id
 *
 *  @return     'TRUE' if cache enable specified, otherwise 'FALSE'
 */
Bool SharedRegion_isCacheEnabled(UInt16 regionId);

/*!
 *  @brief      Sets the entry at the specified region id
 *
 *  SharedRegion_setEntry() is used to set up a shared region that is
 *  currently invalid.  Configuration is performed using the values supplied
 *  in the 'entry' parameter.  If the 'createHeap' flag is TRUE, then a
 *  region heap will be created (if the processor is the region owner)
 *  or opened.
 *
 *  If 'createHeap' is TRUE, SharedRegion_setEntry() must always be called by
 *  a 'client' of the shared region only after the region owner has called
 *  SharedRegion_setEntry().  It is unsafe to poll using SharedRegion_setEntry()
 *  to wait for the corresponding heap to be created by the owner.  An external
 *  synchronization mechanism (i.e. Notify, shared memory, etc) must be used
 *  to ensure the proper sequence of operations.
 *
 *  NOTE: This function should never be called upon a region
 *  that is currently valid.
 *
 *  @param      regionId  region id
 *  @param      entry     pointer to set region information.
 *
 *  @return     Status
 *              - #SharedRegion_S_SUCCESS:  Operation was successful
 *              - #SharedRegion_E_FAIL:  Region already exists or overlaps with
 *                 with another region
 *              - #SharedRegion_E_MEMORY: Unable to create Heap
 */
Int SharedRegion_setEntry(UInt16 regionId, SharedRegion_Entry *entry);

/*!
 *  @brief      Whether address translation is enabled
 *
 *  @return     'TRUE' if translate is enabled otherwise 'FALSE'
 */
Bool SharedRegion_translateEnabled(Void);

/*!
 *  @brief      Returns the SharedRegion_SRPtr value that maps to NULL
 *
 *  @return     Value in SRPtr-space that maps to NULL in Ptr-space
 */
SharedRegion_SRPtr SharedRegion_invalidSRPtr(Void);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_ipc_SharedRegion__include */
