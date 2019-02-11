/**
 *  @file   SysLink.h
 *
 *  @brief      This module contains common definitions, types, structures and
 *              functions used by IPC.
 *
 *
 */
/*
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



#ifndef _SysLink_H_
#define _SysLink_H_


#if defined (__cplusplus)
extern "C" {
#endif

/* =============================================================================
 * macros & defines
 * =============================================================================
 */

/* The bulk of this file is wrapped in this doxygen INTERNAL as it's not intended
 * to be used by end users.  Most of this is implementation details that users
 * shouldn't see or bind to.
 */

/** @cond INTERNAL */

/**
 *  @const  IPC_BUFFER_ALIGN
 *
 *  @desc   Macro to align a number.
 *          x: The number to be aligned
 *          y: The value that the number should be aligned to.
 */
#define IPC_BUFFER_ALIGN(x, y) (UInt32)((UInt32)((x + y - 1) / y) * y)


/**
 *  @brief   Maximum number of mem entries for each core for one platform.
 */
#define IPC_MAX_MEMENTRIES  32

/**
 *  @brief   Max name length.
 */
#define IPC_MAX_NAMELENGTH  32

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */

typedef UInt32 Ipc_MapMask;

/**
 *  @brief  Kernel Virtual address on master processor
 */
#define Ipc_MASTERKNLVIRT   (Ipc_MapMask)(1 << 0)

/**
 *  @brief  User Virtual address on master processor
 */
#define Ipc_MASTERUSRVIRT   (Ipc_MapMask)(1 << 1)

/**
 *  @brief  Virtual address on slave processor
 */
#define Ipc_SLAVEVIRT       (Ipc_MapMask)(1 << 2)

/**
 *  @brief  Structure for memEntry.
 */
typedef struct Ipc_MemEntry_tag {
    UInt32 slaveVirtAddr;    /**< Virtual address */
    UInt32 masterPhysAddr;   /**< Physical address */
    UInt32 size;             /**< Size of the entry */
    Ipc_MapMask mapMask; /**< Used for entries for which map is TRUE */
    Bool   map;              /**< Flag indicating whether this region should
                              *   be mapped to the slave MMU.
                              */
    Bool   isCached;         /**< Flag indicating whether the cache is enabled
                              *   for this region
                              */
    Bool   isValid;          /**< Specifies if the memEntry is valid */
} Ipc_MemEntry;

/**
 *  @brief  Structure for memEntry block for one core.
 */
typedef struct Ipc_MemEntry_Block_tag {
    Char             procName[IPC_MAX_NAMELENGTH];
    /*!< Processor name for which entries are being defined*/
    UInt32           numEntries;
    /*!< Max memEntries for one core*/
    Ipc_MemEntry memEntries [IPC_MAX_MEMENTRIES];
    /*!< Entire memory map (p->v) for one code*/
} Ipc_MemEntry_Block;


/**
 *  @brief  Structure for memEntry block for one core.
 */
typedef struct Ipc_MemoryMap_tag {
    UInt16                   numBlocks;
    /*!< Number of memory blocks in the memory map */
    Ipc_MemEntry_Block * memBlocks;
    /*!< Poninter to entire system memory map */
} Ipc_MemoryMap;

#if defined (__cplusplus)
}
#endif


#endif /*_SysLink_H_*/
