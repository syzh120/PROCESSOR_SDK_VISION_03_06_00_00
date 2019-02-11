/*
 *  @file  MemoryOS.c
 *
 *  @brief  Memory interface implementation.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

/* Standard headers */
#include <ti/syslink/Std.h>

/*OSAL and kernel utils */
#include <ti/syslink/utils/MemoryOS.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/List.h>
#include <Bitops.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/IGateProvider.h>

#include <string.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 * Macros
 * =============================================================================
 */
/* Macro to make a correct module magic number with refCount */
#define MEMORYOS_MAKE_MAGICSTAMP(x) ((MEMORYOS_MODULEID << 12u) | (x))


/* =============================================================================
 * Structs & Enums
 * =============================================================================
 */
/*!
 *  @brief  Structure for containing
 */
typedef struct MemoryOS_MapTableInfo {
    List_Elem next;
    /*!< Pointer to next entry */
    UInt32    actualAddress;
    /*!< Actual address */
    UInt32    mappedAddress;
    /*!< Mapped address */
    UInt32    size;
    /*!< Size of the region mapped */
    UInt16    refCount;
    /*!< Reference count of mapped entry. */
    Bool      isCached;
    /*!< Is cached? */
} MemoryOS_MapTableInfo;

/*!
 *  @brief  Structure defining state object of system memory manager.
 */
typedef struct MemoryOS_ModuleObject {
    Atomic      refCount;
    /*!< Reference count */
    List_Object mapTable;
    /*!< Head of map table */
    IGateProvider_Handle gateHandle;
    /*!< Pointer to lock */
} MemoryOS_ModuleObject;

static UInt32 ioremap(UInt32 src, UInt32 size)
{
    void *addr;
    addr = mmap_device_memory(NULL, size, PROT_READ|PROT_WRITE, 0, src);
    return((UInt32)addr);
}

static UInt32 ioremap_nocache(UInt32 src, UInt32 size)
{
    void *addr;
    addr = mmap_device_memory(NULL, size, PROT_READ|PROT_WRITE|PROT_NOCACHE,
            0, src);
    return((UInt32)addr);
}

/* =============================================================================
 * Globals
 * =============================================================================
 */
/*!
 *  @brief  Object containing state of the Memory OS module.
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
MemoryOS_ModuleObject MemoryOS_state;


/* =============================================================================
 * APIS
 * =============================================================================
 */
/*!
 *  @brief      Initialize the memory os module.
 */
Int32
MemoryOS_setup (void)
{
    Int32        status = MEMORYOS_SUCCESS;
    List_Params  listparams;
    Error_Block  eb;

    GT_0trace (curTrace, GT_ENTER, "MemoryOS_setup");

    Error_init(&eb);

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (&MemoryOS_state.refCount,
                            MEMORYOS_MAKE_MAGICSTAMP(0),
                            MEMORYOS_MAKE_MAGICSTAMP(0));

    if (   Atomic_inc_return (&MemoryOS_state.refCount)
        != MEMORYOS_MAKE_MAGICSTAMP(1u)) {
        status = MEMORYOS_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "MemoryOS Module already initialized!");
    }
    else {
        /* Create the Gate handle */
        MemoryOS_state.gateHandle = (IGateProvider_Handle)
                              GateMutex_create ((GateMutex_Params *) NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (MemoryOS_state.gateHandle == NULL) {
            Atomic_set (&MemoryOS_state.refCount, MEMORYOS_MAKE_MAGICSTAMP(0));
            /*! @retval MEMORYOS_E_FAIL Failed to create the local gate */
            status = MEMORYOS_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MemoryOS_alloc",
                                 status,
                                 "Failed to create the local gate");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            List_Params_init (&listparams);
            /* Construct the map table.Not passing gate as MemoryOs module
             *  takes care of protection over list operations
             */
            List_construct (&MemoryOS_state.mapTable, &listparams);
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif

    }

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_setup", status);

    /*! @retval MEMORY_SUCCESS OPeration was successful */
    return status;
}


/*!
 *  @brief      Finalize the memory os module.
 */
Int32
MemoryOS_destroy (void)
{
    Int32 status     = MEMORYOS_SUCCESS;
    Int32 tmpStatus  = MEMORYOS_SUCCESS;
    List_Elem * info = NULL;

    GT_0trace (curTrace, GT_ENTER, "MemoryOS_destroy");

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval MEMORYOS_E_INVALIDSTATE Module was not initialized */
        status = MEMORYOS_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (   Atomic_dec_return (&MemoryOS_state.refCount)
            == MEMORYOS_MAKE_MAGICSTAMP(0)) {
            /* Free any remaining regions */
            List_traverse (info, (List_Handle) &MemoryOS_state.mapTable) {
                munmap ((unsigned int *)
                         ((MemoryOS_MapTableInfo *) info)->mappedAddress,
                         ((MemoryOS_MapTableInfo *) info)->size);
                List_remove ((List_Handle) &MemoryOS_state.mapTable,
                             info);
                MemoryOS_free (info, sizeof (MemoryOS_MapTableInfo), 0);
            }

            List_destruct (&MemoryOS_state.mapTable);

            /* Delete the gate handle */
            tmpStatus = GateMutex_delete ((GateMutex_Handle *)
                                          &MemoryOS_state.gateHandle);
            if ((status >= 0) && (tmpStatus < 0)) {
                status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MemoryOS_destroy",
                                     status,
                                     "GateMutex_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_destroy", status);

    /*! @retval MEMORY_SUCCESS OPeration was successful */
    return status;
}


/*!
 *  @brief      Allocates the specified number of bytes.
 *
 *  @param      ptr pointer where the size memory is allocated.
 *  @param      size amount of memory to be allocated.
 *  @sa         Memory_calloc
 */
Ptr MemoryOS_alloc (UInt32 size, UInt32 align, UInt32 flags)
{
    Ptr ptr = NULL;

    GT_3trace (curTrace, GT_ENTER, "MemoryOS_alloc", size, align, flags);

    /* check whether the right paramaters are passed or not.*/
    GT_assert (curTrace, (size > 0));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_alloc",
                             MEMORYOS_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        if (flags == MemoryOS_MemTypeFlags_Default) {
            /* Call the kernel API for memory allocation */
            ptr = malloc (size) ;
        }
        else {
            /*! @retval NULL Memory allocation failed */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MemoryOS_alloc",
                                 MEMORYOS_E_MEMORY,
                                 "Memory allocation type is invalid");
        }
#if !defined(IPC_BUILD_OPTIMIZE)
        if (NULL == ptr) {
            /*! @retval NULL Memory allocation failed */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MemoryOS_alloc",
                                 MEMORYOS_E_MEMORY,
                                 "Could not allocate memory");
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_alloc", ptr);

    /*! @retval Pointer Memory allocation successful */
    return ptr;
}


/*!
 *  @brief      Allocates the specified number of bytes and memory is
 *              set to zero.
 *
 *  @param      ptr pointer where the size memory is allocated.
 *  @param      size amount of memory to be allocated.
 *  @sa         Memory_alloc
 */
Ptr
MemoryOS_calloc (UInt32 size, UInt32 align, UInt32 flags)
{
    Ptr ptr = NULL;
    GT_3trace (curTrace, GT_ENTER, "MemoryOS_calloc", size, align, flags);

    ptr = MemoryOS_alloc (size, align, flags);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (NULL == ptr) {
        /*! @retval NULL Memory allocation failed */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_calloc",
                             MEMORYOS_E_MEMORY,
                             "Could not allocate memory");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        memset (ptr, 0, size);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_calloc", ptr);

    /*! @retval Pointer Memory allocation successful */
    return ptr;
}


/*!
 *  @brief      Frees up the specified chunk of memory.
 *
 *  @param      ptr  Pointer to the previously allocated memory area.
 *  @sa         Memory_alloc
 */
Void
MemoryOS_free (Ptr ptr, UInt32 size, UInt32 flags)
{
    GT_3trace (curTrace, GT_ENTER, "MemoryOS_free", ptr, size, flags);

    GT_assert (GT_1CLASS, (ptr != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (NULL == ptr) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_free",
                             MEMORYOS_E_INVALIDARG,
                             "Pointer NULL for free");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        if (flags == MemoryOS_MemTypeFlags_Default) {
            /*! free the memory pointed by ptr */
            free (ptr);
        }
        else {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MemoryOS_free",
                                 MEMORYOS_E_MEMORY,
                                 "Memory free type is invalid");
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "MemoryOS_free");
}


/*!
 *  @brief      Maps a memory area into virtual space.
 *
 *  @param      mapInfo  Pointer to the area which needs to be mapped.
 *  @sa         Memory_unmap
 */
Int
MemoryOS_map (Memory_MapInfo * mapInfo)
{
    Int                     status = MEMORYOS_SUCCESS;
    Bool                    exists = FALSE;
    IArg                    key;
    List_Elem *             listInfo;
    MemoryOS_MapTableInfo * info;

    GT_1trace (curTrace, GT_ENTER, "MemoryOS_map", mapInfo);

    GT_assert (curTrace, (NULL != mapInfo));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval MEMORYOS_E_INVALIDSTATE Module was not initialized */
        status = MEMORYOS_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_map",
                             status,
                             "Module was not initialized!");
    }
    else  if (mapInfo == NULL) {
        /*! @retval MEMORYOS_E_INVALIDARG NULL provided for argument mapInfo. */
        status = MEMORYOS_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_map",
                             status,
                             "NULL provided for argument mapInfo");
    }
    else if (mapInfo->src == (UInt32) NULL) {
        /*! @retval MEMORYOS_E_INVALIDARG NULL provided for argument
                                          mapInfo->src. */
        status = MEMORYOS_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_map",
                             status,
                             "NULL provided for argument mapInfo->src");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter the critical section */
        key = IGateProvider_enter (MemoryOS_state.gateHandle);

        /* First check if the mapping already exists in the map table */
        List_traverse (listInfo, (List_Handle) &MemoryOS_state.mapTable) {
            if (    (   ((MemoryOS_MapTableInfo *) listInfo)->actualAddress
                    == mapInfo->src)
                &&  (   ((MemoryOS_MapTableInfo *) listInfo)->isCached
                     == mapInfo->isCached)
                &&  (   ((MemoryOS_MapTableInfo *) listInfo)->size
                     >= mapInfo->size)) {
                GT_2trace (curTrace,
                           GT_1CLASS,
                           "MemoryOS_map: Entry already exists\n"
                           "    mapInfo->src  [0x%x]\n"
                           "    mapInfo->size [0x%x]",
                           mapInfo->src,
                           mapInfo->size);
                exists = TRUE;
                mapInfo->dst =
                           ((MemoryOS_MapTableInfo *) listInfo)->mappedAddress;
                /* Increase the refcount. */
                ((MemoryOS_MapTableInfo *) listInfo)->refCount++;
                break;
            }
        }

        if (!exists) {
            mapInfo->dst = 0;
            if (mapInfo->isCached == TRUE) {
                mapInfo->dst = (UInt32) ioremap (mapInfo->src, mapInfo->size);
            }
            else {
                mapInfo->dst = (UInt32) ioremap_nocache(mapInfo->src,
                                                            mapInfo->size);
            }

#if !defined(IPC_BUILD_OPTIMIZE)
            if (mapInfo->dst == (UInt32)MAP_FAILED) {
                /*! @retval MEMORYOS_E_MAP Failed to map to host address space. */
                status = MEMORYOS_E_MAP;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MemoryOS_map",
                                     status,
                                     "Failed to map to host address space!");
            }
            else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
                info = MemoryOS_alloc (sizeof (MemoryOS_MapTableInfo), 0, 0);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (info == NULL) {
                    /*! @retval MEMORYOS_E_MEMORY Failed to allocate memory. */
                    status = MEMORYOS_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "MemoryOS_map",
                                         status,
                                         "Failed to allocate memory!");
                }
                else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
                    /* Initialize the list element */
                    List_elemClear ((List_Elem *) info);
                    /* Populate the info */
                    info->actualAddress = mapInfo->src;
                    info->mappedAddress = mapInfo->dst;
                    info->size          = mapInfo->size;
                    info->refCount      = 1;
                    info->isCached      = mapInfo->isCached;
                    /* Put the info into the list */
                    List_putHead ((List_Handle) &MemoryOS_state.mapTable,
                                  (List_Elem *) info);
#if !defined(IPC_BUILD_OPTIMIZE)
                }
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        }

        /* Leave the crtical section */
        IGateProvider_leave (MemoryOS_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_map", status);

    /*! @retval MEMORYOS_SUCESS Operation completed successfully. */
    return status;
}


/*!
 *  @brief      UnMaps a memory area into virtual space.
 *
 *  @param      unmapInfo poiinter to the area which needs to be unmapped.
 *  @sa         Memory_map
 */
Int
MemoryOS_unmap (Memory_UnmapInfo * unmapInfo)
{
    Int         status = MEMORYOS_SUCCESS;
    Bool        found  = FALSE;
    IArg        key;
    List_Elem * info;

    GT_1trace (curTrace, GT_ENTER, "MemoryOS_unmap", unmapInfo);

    GT_assert (curTrace, (NULL != unmapInfo));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval MEMORYOS_E_INVALIDSTATE Module was not initialized */
        status = MEMORYOS_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_unmap",
                             status,
                             "Module was not initialized!");
    }
    else if (unmapInfo == NULL) {
        /*! @retval MEMORYOS_E_INVALIDARG NULL provided for argument
                                          unmapInfo. */
        status = MEMORYOS_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_unmap",
                             status,
                             "NULL provided for argument unmapInfo");
    }
    else if (unmapInfo->addr == (UInt32) NULL) {
        /*! @retval MEMORYOS_E_INVALIDARG NULL provided for argument
                                          unmapInfo->addr. */
        status = MEMORYOS_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_unmap",
                             status,
                             "NULL provided for argument unmapInfo->addr");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        key = IGateProvider_enter (MemoryOS_state.gateHandle);

        /* Find the node in the map table */
        List_traverse (info, (List_Handle) &MemoryOS_state.mapTable) {
            GT_2trace (curTrace,
                       GT_1CLASS,
                       "MemoryOS_unmap:\n"
                       "    info->mappedAddress  [0x%x]\n"
                       "    unmapInfo->addr      [0x%x]",
                       ((MemoryOS_MapTableInfo *) info)->mappedAddress,
                       unmapInfo->addr);
            if (    (   ((MemoryOS_MapTableInfo *) info)->mappedAddress
                     == unmapInfo->addr)
                &&  (   ((MemoryOS_MapTableInfo *) info)->isCached
                     == unmapInfo->isCached)) {
                /* Decrease the refcount. */
                ((MemoryOS_MapTableInfo *) info)->refCount--;
                found = TRUE;
                break;
            }
        }

#if !defined(IPC_BUILD_OPTIMIZE)
        if (!found) {
            status = MEMORYOS_E_UNMAP;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MemoryOS_unmap",
                                 status,
                                 "Could not find specified entry to unmap!");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
            /* Unmap if refCount is 0. */
            if (((MemoryOS_MapTableInfo *) info)->refCount == 0) {
                List_remove ((List_Handle) &MemoryOS_state.mapTable,
                             (List_Elem *) info);
                MemoryOS_free (info, sizeof (MemoryOS_MapTableInfo), 0);
                munmap ((unsigned int *) unmapInfo->addr, unmapInfo->size);
            }
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

        IGateProvider_leave (MemoryOS_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_unmap", status);

    /*! @retval MEMORYOS_SUCESS Operation completed successfully. */
    return status;
}


/*!
 *  @brief      Copies the data between memory areas.
 *
 *  @param      dst  destination address.
 *  @param      src  source address.
 *  @param      len  length of byte to be copied.
 */
Ptr
MemoryOS_copy (Ptr dst, Ptr src, UInt32 len)
{
//    Int32 ret;

    GT_3trace (curTrace, GT_ENTER, "Memory_copy", dst, src, len);

    GT_assert (curTrace, ((NULL != dst) && (NULL != src)));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_copy",
                             MEMORYOS_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if ((dst == NULL) || (src == NULL)) {
        /*! @retval NULL Invalid argument */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_copy",
                             MEMORYOS_E_INVALIDARG,
                             "Invalid argument");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

            dst = memcpy (dst, src, len);

#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_copy", dst);

    /*! @retval Pointer Success: Pointer to updated destination buffer */
    return dst;
}


/*!
 *  @brief      Set the specific value in the said memory area.
 *
 *  @param      buf  operating buffer.
 *  @param      value the value to be stored in each byte.
 *  @param      len  length of bytes to be set.
 */
Ptr
MemoryOS_set (Ptr buf, Int value, UInt32 len)
{
    GT_3trace (curTrace, GT_ENTER, "MemoryOS_set", buf, value, len);

    GT_assert (curTrace, (NULL != buf) && (len > 0));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_set",
                             MEMORYOS_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (buf == NULL) {
        /*! @retval NULL Invalid argument */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_set",
                             MEMORYOS_E_INVALIDARG,
                             "Invalid argument");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        buf = memset (buf, value, len);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_set", buf);

    /*! @retval Pointer Success: Pointer to updated destination buffer */
    return buf;
}


/*!
 *  @brief      Function to translate an address.
 *
 *  @param      srcAddr  source address.
 *  @param      flags    Tranlation flags.
 */
Ptr
MemoryOS_translate (Ptr srcAddr, Memory_XltFlags flags)
{
    Ptr                     buf    = NULL;
    MemoryOS_MapTableInfo * tinfo  = NULL;
    List_Elem *             info   = NULL;
    IArg                    key;
    UInt32                  frmAddr;
    UInt32                  toAddr;

    GT_2trace (curTrace, GT_ENTER, "MemoryOS_translate", srcAddr, flags);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MemoryOS_state.refCount),
                                  MEMORYOS_MAKE_MAGICSTAMP(0),
                                  MEMORYOS_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_translate",
                             MEMORYOS_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        key = IGateProvider_enter (MemoryOS_state.gateHandle);

        /* Traverse to the node in the map table */
        List_traverse (info, (List_Handle) &MemoryOS_state.mapTable) {
            tinfo = (MemoryOS_MapTableInfo *) info;
            frmAddr = (flags == Memory_XltFlags_Virt2Phys) ?
                                    tinfo->mappedAddress : tinfo->actualAddress;
            toAddr = (flags == Memory_XltFlags_Virt2Phys) ?
                                    tinfo->actualAddress : tinfo->mappedAddress;
            if (   (((UInt32) srcAddr) >= frmAddr)
                && (((UInt32) srcAddr) < (frmAddr + tinfo->size))) {
                buf = (Ptr) (toAddr + ((UInt32)srcAddr - frmAddr));
                break;
            }
        }

        IGateProvider_leave (MemoryOS_state.gateHandle, key);

#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_translate", buf);

    /*! @retval Pointer Success: Pointer to updated destination buffer */
    return buf;
}


#if defined (__cplusplus)
}
#endif /* defined (_cplusplus)*/
