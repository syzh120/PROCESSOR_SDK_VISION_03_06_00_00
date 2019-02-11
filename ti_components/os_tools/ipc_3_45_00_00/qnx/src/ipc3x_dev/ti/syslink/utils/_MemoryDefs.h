/**
 *  @file   _MemoryDefs.h
 *
 *  @brief      Definitions for Memory module.
 *
 *              This provides macros and type definitions for the Memory module.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2008-2012, Texas Instruments Incorporated
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



#ifndef _MEMORYDEFS_H_0x73E4
#define _MEMORYDEFS_H_0x73E4

#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @brief   Enumerates the types of translation
 */
typedef enum {
    Memory_XltFlags_Virt2Phys       = 0x00000000,
    /*!< Virtual to physical */
    Memory_XltFlags_Phys2Virt       = 0x00000001,
    /*!< Virtual to physical */
    Memory_XltFlags_EndValue        = 0x00000002
    /*!< End delimiter indicating start of invalid values for this enum */
} Memory_XltFlags;

/*!
 *  @brief   Structure containing information required for mapping a
 *           memory region.
 */
typedef struct MemoryOS_MapInfo_tag {
    UInt32   src;
    /*!< Address to be mapped. */
    UInt32   size;
    /*!< Size of memory region to be mapped. */
    UInt32   dst;
    /*!< Mapped address. */
    Bool     isCached;
    /*!< Whether the mapping is to a cached area or uncached area. */
    Ptr      drvHandle;
    /*!< Handle to the driver that is implementing the mmap call. Ignored for
         Kernel-side version. */
} MemoryOS_MapInfo ;

/*!
 *  @brief   Structure containing information required for unmapping a
 *           memory region.
 */
typedef struct MemoryOS_UnmapInfo_tag {
    UInt32  addr;
    /*!< Address to be unmapped.*/
    UInt32  size;
    /*!< Size of memory region to be unmapped.*/
    Bool    isCached;
    /*!< Whether the mapping is to a cached area or uncached area.  */
} MemoryOS_UnmapInfo;

/*!
 *  @brief   Structure for scatter-gathered list.
 */
typedef struct MemoryOS_SGList {
    UInt32  paddr;
    /*!< Page address.*/
    UInt32  offset;
    /*!< Offset of memory segment in the page.*/
    UInt32  size;
    /*!< Size of memory segment in the page.*/
    Bool    isCached;
    /*!< Whether the mapping is to a cached area or uncached area.  */
} MemoryOS_SGList;

/*!
 *  @brief   Structure containing information required for mapping a
 *           memory region.
 */
#define Memory_MapInfo   MemoryOS_MapInfo

/*!
 *  @brief   Structure containing information required for unmapping a
 *           memory region.
 */
#define Memory_UnmapInfo MemoryOS_UnmapInfo

/*!
 *  @brief   Structure for scatter-gathered list.
 */
#define Memory_SGList       MemoryOS_SGList

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef _MEMORYDEFS_H_0x73E4 */
