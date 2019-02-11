/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef UTILS_MEM_PRIV_H_
#define UTILS_MEM_PRIV_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_mem_cfg.h>
#include <include/link_api/system.h>
#include <include/link_api/system_common.h>

/* #define UTILS_MEM_DEBUG */

/*
 * SR heaps are defined on IPU1-0,
 * When DSP/EVE/A15/IPU1-1/IPU2 asks for memory, this memory is allocated by IPU1-0
 * Since heap maintains a data structure in memory, we need to make sure this data
 * structure is not corrupted by unaligned cache operations on DSP/A15/IPU1-0
 *
 * Hence a minimum alignment which is >= max cache line lenght across all CPUs is
 * required.
 *
 * This define is used to specific this minimum alignment
 */
#define UTILS_MEM_SR_HEAP_MIN_ALIGN     (512U)


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

typedef struct {

    HeapMem_Struct heapStruct;
    /**< Object to hold heap information */

    IHeap_Handle heapHandle;
    /**< Heap handle */

    Bool         isClearBufOnAlloc;
    /**< Flag to contorl clear the allocated memory with 0x80 pattern */

    char   heapName[32];
    /**< Name of heap */

    UInt32 heapAddr;
    /**< Physical base address of heap */

    UInt32 heapSize;
    /**< Total size of heap in bytes */

    UInt32 heapAllocOffset;
    /**< Heap alloc offset, only valid for L2 heap */

} Utils_MemHeapObj;


extern Utils_MemHeapObj gUtils_memHeapObj[UTILS_HEAPID_MAXNUMHEAPS];

/*******************************************************************************
 *  Functions
 *******************************************************************************
*/

Int32 Utils_memHeapSetup(void);

#endif

/* @} */
