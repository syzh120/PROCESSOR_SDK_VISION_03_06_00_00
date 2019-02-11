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

/**
 *******************************************************************************
 *
 * \ingroup UTILS_API
 * \defgroup UTILS_MEM_API External/Internal Memory allocator API
 *
 * \brief  APIs to allocate system buffer memory from a predefined memory pool
 *
 * @{
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file utils_mem_if.h
 *
 * \brief External/Internal Memory allocator API
 *
 * \version 0.0 First version
 * \version 0.1 Updates as per code review comments
 *
 *******************************************************************************
*/

#ifndef UTILS_MEM_IF_H_
#define UTILS_MEM_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/link_api/systemLink_common_if.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 * \brief Heap ID
 *******************************************************************************
*/
typedef enum
{
    UTILS_HEAPID_DDR_NON_CACHED_SR0 = SYSTEM_HEAPID_DDR_NON_CACHED_SR0,
    /**< Heap ID of heap in DDR
     *   - This is non-cached memory
     *   - This is shared across all CPUs
     *   - Recommended to be used for small information structures, that need to be
     *     shared across CPUs
     */

    UTILS_HEAPID_DDR_CACHED_SR = SYSTEM_HEAPID_DDR_CACHED_SR1,
    /**< Heap ID of heap in DDR
     *   - This is cached memory with ECC disabled and QM access permissions
     *   - This is shared across all CPUs
     *   - Recommended to be used for big buffer allocations, that need to be shared
     *     across CPUs
     */

    UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_QM = SYSTEM_HEAPID_DDR_CACHED_SR1,
    /**< Heap ID of heap in DDR
     *   - This is cached memory with ECC disabled and QM access permissions
     *   - This is shared across all CPUs
     *   - Recommended to be used for big buffer allocations, that need to be shared
     *     across CPUs
     */

    UTILS_HEAPID_OCMC_SR = SYSTEM_HEAPID_OCMC_SR2,
    /**< Heap ID of heap in DDR
     *   - This is cached or non-cached memory depending on CPU MMU setting
     *   - This is shared across all CPUs
     *   - Recommended to be used as fast access temporary memory by algorithms
     */

    UTILS_HEAPID_DDR_CACHED_LOCAL = SYSTEM_HEAPID_RESERVED1,
    /**< Heap ID of heap in DDR
     *   - This is cached memory
     *   - This is only visible to the local CPUs
     *   - Recommended to be used for small information, that is needed by the
     *     local algorithm
     */

    UTILS_HEAPID_L2_LOCAL = SYSTEM_HEAPID_RESERVED2,
    /**< Heap ID of heap in L2 Memory
     *   - This is cached or non-cached memory depending on CPU MMU setting
     *   - This is only visible to the local CPU
     *   - Recommended to be used as fast access temporary memory by algorithms
     */


    UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL = SYSTEM_HEAPID_DDR_CACHED_SR1_ECC_ASIL,
    /**< Heap ID of heap in DDR
     *   - This is cached memory with ECC enabled and ASIL access permissions
     *   - This is shared across all CPUs
     *   - Recommended to be used for big buffer allocations, that need to be shared
     *     across CPUs
     *   - Valid only when ECC_FFI_INCLUDE is defined.
     *     Else will map to UTILS_HEAPID_DDR_CACHED_SR
     */

    UTILS_HEAPID_DDR_CACHED_SR_ECC_QM = SYSTEM_HEAPID_DDR_CACHED_SR1_ECC_QM,
    /**< Heap ID of heap in DDR
     *   - This is cached memory with ECC enabled and QM access permissions
     *   - This is shared across all CPUs
     *   - Recommended to be used for big buffer allocations, that need to be shared
     *     across CPUs
     *   - Valid only when ECC_FFI_INCLUDE is defined.
     *     Else will map to UTILS_HEAPID_DDR_CACHED_SR
     */

    UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL = SYSTEM_HEAPID_DDR_CACHED_SR1_NON_ECC_ASIL,
    /**< Heap ID of heap in DDR
     *   - This is cached memory with ECC disabled and ASIL access permissions
     *   - This is shared across all CPUs
     *   - Recommended to be used for big buffer allocations, that need to be shared
     *     across CPUs
     *   - Valid only when ECC_FFI_INCLUDE is defined.
     *     Else will map to UTILS_HEAPID_DDR_CACHED_SR
     */

    UTILS_HEAPID_MAXNUMHEAPS = SYSTEM_HEAPID_MAXNUMHEAPS
    /**< max Heap ID */

} Utils_HeapId;

/**
 *******************************************************************************
 * \brief Information related to a heap
 *******************************************************************************
*/
typedef struct {

    char   heapName[32];
    /**< Name of heap */

    UInt32 heapId;
    /**< Heap ID */

    UInt32 heapAddr;
    /**< Physical base address of heap */

    UInt32 heapSize;
    /**< Total size of heap in bytes */

    UInt32 freeSize;
    /**< Free space in heap in bytes */

} Utils_MemHeapStats;


/*******************************************************************************
 *  Functions
 *******************************************************************************
*/

Ptr   Utils_memAlloc(Utils_HeapId heapId, UInt32 size, UInt32 align);

Int32 Utils_memFree(Utils_HeapId heapId, Ptr addr, UInt32 size);

Int32 Utils_memClearOnAlloc(Bool enable);

Int32 Utils_memGetHeapStats(Utils_HeapId heapId, Utils_MemHeapStats *pStats);

void *Utils_memPhysToVirt(void *physPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
