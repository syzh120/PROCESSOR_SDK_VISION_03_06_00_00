/*
 *  @file   MemoryOS.c
 *
 *  @brief      Linux user Memory interface implementation.
 *
 *              This abstracts the Memory management interface in the user-side.
 *              Allocation, Freeing-up, copy are supported for the user memory
 *              management.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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

/* Linux OS-specific headers */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* OSAL and kernel utils */
#include <ti/syslink/utils/MemoryOS.h>
#include <ti/syslink/utils/Trace.h>
#include <Bitops.h>


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
 *  @brief  Structure defining state object of system memory manager.
 */
typedef struct MemoryOS_ModuleObject {
    Atomic      refCount;
    /*!< Reference count */
} MemoryOS_ModuleObject;


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
MemoryOS_ModuleObject MemoryOS_state ;


/* =============================================================================
 * APIs
 * =============================================================================
 */
/*!
 *  @brief Initialize the memory os module.
 */
Int32
MemoryOS_setup (void)
{
    Int32  status = MEMORYOS_SUCCESS;
    /* TBD UInt32 key; */

    GT_0trace (curTrace, GT_ENTER, "MemoryOS_setup");

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
    Int32 status    = MEMORYOS_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "MemoryOS_destroy");

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
Ptr
MemoryOS_alloc (UInt32 size, UInt32 align, UInt32 flags)
{
    Ptr ptr = NULL;

    GT_3trace (curTrace, GT_ENTER, "MemoryOS_alloc", size, align, flags);

    /* check whether the right paramaters are passed or not.*/
    GT_assert (curTrace, (size > 0));

    /* Call the Linux API for memory allocation */
    ptr = (Ptr) malloc (size);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (NULL == ptr) {
        /*! @retval NULL Memory allocation failed */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MemoryOS_alloc",
                             MEMORYOS_E_MEMORY,
                             "Could not allocate memory");
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
        ptr = memset (ptr, 0, size);
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
    GT_2trace (curTrace, GT_ENTER, "MemoryOS_free", ptr, flags);

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
        /* Free the memory pointed by ptr */
        free (ptr);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "MemoryOS_free");
}


/*!
 *  @brief      Maps a memory area into virtual space.
 *
 *  @param      mapInfo  Pointer to the area which needs to be mapped.
 *
 *  @sa         Memory_unmap
 */
Int
MemoryOS_map (Memory_MapInfo * mapInfo)
{
    Int                     status = MEMORYOS_E_FAIL;

    GT_1trace (curTrace, GT_ENTER, "MemoryOS_map", mapInfo);

    GT_0trace (curTrace, GT_4CLASS, "MemoryOS_map not supported!");

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_map", status);

    /*! @retval MEMORYOS_SUCESS Operation completed successfully. */
    return status;
}


/*!
 *  @brief      UnMaps a memory area into virtual space.
 *
 *  @param      unmapInfo poiinter to the area which needs to be unmapped.
 *
 *  @sa         Memory_map
 */
Int
MemoryOS_unmap (Memory_UnmapInfo * unmapInfo)
{
    Int         status   = MEMORYOS_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "MemoryOS_unmap", unmapInfo);

    GT_0trace (curTrace, GT_4CLASS, "MemoryOS_unmap not supported!");

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
    GT_3trace (curTrace, GT_ENTER, "Memory_copy", dst, src, len);

    GT_assert (curTrace, ((NULL != dst) && (NULL != src)));

#if !defined(IPC_BUILD_OPTIMIZE)
    if ((dst == NULL) || (src == NULL)) {
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
    if (buf == NULL) {
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

    GT_2trace (curTrace, GT_ENTER, "MemoryOS_translate", srcAddr, flags);

    GT_0trace (curTrace, GT_4CLASS, "MemoryOS_translate not supported!");

    GT_1trace (curTrace, GT_LEAVE, "MemoryOS_translate", buf);

    /*! @retval Pointer Success: Pointer to updated destination buffer */
    return buf;
}


#if defined (__cplusplus)
}
#endif /* defined (_cplusplus)*/
