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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
*/
#include "utils_mem_priv.h"
#if !defined (IPC_LIB_INCLUDE)
#include <ti/ipc/SharedRegion.h>
#endif

IHeap_Handle Utils_memGetHeapHandleSR(UInt32 heapId);

UInt8* System_getSr1FrameBufferAddr(void);
UInt32 System_getSr1FrameBufferSize(void);
UInt8* System_getSr1BuffEccAsilAddr(void);
UInt32 System_getSr1BuffEccAsilSize(void);
UInt8* System_getSr1BuffEccQmAddr(void);
UInt32 System_getSr1BuffEccQmSize(void);
UInt8* System_getSr1BuffNonEccAsilAddr(void);
UInt32 System_getSr1BuffNonEccAsilSize(void);

#ifdef UTILS_MEM_HEAP_OCMC_SIZE
#pragma DATA_ALIGN(gUtils_memHeapOCMC, UTILS_MEM_SR_HEAP_MIN_ALIGN)
#pragma DATA_SECTION(gUtils_memHeapOCMC, ".bss:heapMemOCMC")
UInt8 gUtils_memHeapOCMC[UTILS_MEM_HEAP_OCMC_SIZE];
#endif

Int32 Utils_memHeapSetup(void)
{
    if(System_getSr1FrameBufferSize() > 0U)
    {
        Utils_MemHeapObj *pObj;
        HeapMem_Params heapParams;

        pObj = &gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR];

        HeapMem_Params_init(&heapParams);

        heapParams.buf = (UInt8*)SystemUtils_align(
        (UInt32)System_getSr1FrameBufferAddr(), UTILS_MEM_SR_HEAP_MIN_ALIGN);
        heapParams.size = System_getSr1FrameBufferSize() - \
            ((UInt8*)heapParams.buf - System_getSr1FrameBufferAddr());

        HeapMem_construct(&pObj->heapStruct, &heapParams);

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated buffer pointer to int as type of the
         * heapAddr is int.
         */
        pObj->heapAddr   = (UInt32)heapParams.buf;
        pObj->heapSize   = heapParams.size;
        pObj->heapHandle = HeapMem_Handle_upCast(
                            HeapMem_handle(&pObj->heapStruct)
                            );
    }

#ifdef ECC_FFI_INCLUDE
    if(System_getSr1BuffEccAsilSize() > 0U)
    {
        Utils_MemHeapObj *pObj;
        HeapMem_Params heapParams;

        pObj = &gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL];

        HeapMem_Params_init(&heapParams);

        heapParams.buf = (UInt8*)SystemUtils_align(
        (UInt32)System_getSr1BuffEccAsilAddr(), UTILS_MEM_SR_HEAP_MIN_ALIGN);
        heapParams.size = System_getSr1BuffEccAsilSize() - \
            ((UInt8*)heapParams.buf - System_getSr1BuffEccAsilAddr());

        HeapMem_construct(&pObj->heapStruct, &heapParams);

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated buffer pointer to int as type of the
         * heapAddr is int.
         */
        pObj->heapAddr   = (UInt32)heapParams.buf;
        pObj->heapSize   = heapParams.size;
        pObj->heapHandle = HeapMem_Handle_upCast(
                            HeapMem_handle(&pObj->heapStruct)
                            );
    }

    if(System_getSr1BuffEccQmSize() > 0U)
    {
        Utils_MemHeapObj *pObj;
        HeapMem_Params heapParams;

        pObj = &gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_ECC_QM];

        HeapMem_Params_init(&heapParams);

        heapParams.buf = (UInt8*)SystemUtils_align(
        (UInt32)System_getSr1BuffEccQmAddr(), UTILS_MEM_SR_HEAP_MIN_ALIGN);
        heapParams.size = System_getSr1BuffEccQmSize() - \
            ((UInt8*)heapParams.buf - System_getSr1BuffEccQmAddr());

        HeapMem_construct(&pObj->heapStruct, &heapParams);

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated buffer pointer to int as type of the
         * heapAddr is int.
         */
        pObj->heapAddr   = (UInt32)heapParams.buf;
        pObj->heapSize   = heapParams.size;
        pObj->heapHandle = HeapMem_Handle_upCast(
                            HeapMem_handle(&pObj->heapStruct)
                            );
    }

    if(System_getSr1BuffNonEccAsilSize() > 0U)
    {
        Utils_MemHeapObj *pObj;
        HeapMem_Params heapParams;

        pObj = &gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL];

        HeapMem_Params_init(&heapParams);

        heapParams.buf = (UInt8*)SystemUtils_align(
        (UInt32)System_getSr1BuffNonEccAsilAddr(), UTILS_MEM_SR_HEAP_MIN_ALIGN);
        heapParams.size = System_getSr1BuffNonEccAsilSize() -
            ((UInt8*)heapParams.buf - System_getSr1BuffNonEccAsilAddr());

        HeapMem_construct(&pObj->heapStruct, &heapParams);

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated buffer pointer to int as type of the
         * heapAddr is int.
         */
        pObj->heapAddr   = (UInt32)heapParams.buf;
        pObj->heapSize   = heapParams.size;
        pObj->heapHandle = HeapMem_Handle_upCast(
                            HeapMem_handle(&pObj->heapStruct)
                            );
    }
#endif

#ifdef UTILS_MEM_HEAP_OCMC_SIZE
    {
        Utils_MemHeapObj *pObj;
        HeapMem_Params heapParams;

        pObj = &gUtils_memHeapObj[UTILS_HEAPID_OCMC_SR];

        HeapMem_Params_init(&heapParams);

        heapParams.buf = gUtils_memHeapOCMC;
        heapParams.size = sizeof(gUtils_memHeapOCMC);

        #if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD) || defined(TDA2PX_BUILD)
        /* In case of TDA2x/TDA2Px/TDA2Ex HS devices, first 4*kB of OCMC_RAM1 is never
         * available. This constraint will be forced for GP devices for
         * simplicity. As a result, actual memory available in OCMC Heap will be
         * (UTILS_MEM_HEAP_OCMC_SIZE - 4*kB) in case of TDA2x/TDA2Ex
         */
        heapParams.buf = &gUtils_memHeapOCMC[4096U];
        heapParams.size -= 4096U;
        #endif

        HeapMem_construct(&pObj->heapStruct, &heapParams);

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated buffer pointer to int as type of the
         * heapAddr is int.
         */
        pObj->heapAddr   = (UInt32)heapParams.buf;
        pObj->heapSize   = heapParams.size;
        pObj->heapHandle = HeapMem_Handle_upCast(
                            HeapMem_handle(&pObj->heapStruct)
                            );
    }
#endif

#ifdef ENABLE_HEAP_SR0
    {
        Utils_MemHeapObj *pObj;
        SharedRegion_Entry srEntry;

        pObj = &gUtils_memHeapObj[UTILS_HEAPID_DDR_NON_CACHED_SR0];

        SharedRegion_entryInit(&srEntry);
        SharedRegion_getEntry(0, &srEntry);

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated buffer pointer to int as type of the
         * heapAddr is int.
         */
        pObj->heapAddr   = (UInt32)srEntry.base;
        pObj->heapSize   = srEntry.len;
        pObj->heapHandle = SharedRegion_getHeap(0);
    }
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

IHeap_Handle Utils_memGetHeapHandleSR(UInt32 heapId)
{
    IHeap_Handle heapHandle = NULL;
#ifndef ECC_FFI_INCLUDE
    if((UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL == heapId) ||
       (UTILS_HEAPID_DDR_CACHED_SR_ECC_QM == heapId) ||
       (UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL == heapId))
    {
        heapId = UTILS_HEAPID_DDR_CACHED_SR;
    }
#endif

    if((UTILS_HEAPID_DDR_CACHED_SR == heapId) ||
       (UTILS_HEAPID_OCMC_SR == heapId) ||
       (UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL == heapId) ||
       (UTILS_HEAPID_DDR_CACHED_SR_ECC_QM == heapId) ||
       (UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL == heapId) ||
       (UTILS_HEAPID_DDR_NON_CACHED_SR0 == heapId))
    {
        heapHandle = gUtils_memHeapObj[heapId].heapHandle;
    }

    return heapHandle;
}

Int32 Utils_memAllocSR(SystemCommon_AllocBuffer *pPrm)
{
    volatile Ptr addr = NULL;
    UInt32 align, size;
    Error_Block ebObj;
    Error_Block *eb = &ebObj;
    IHeap_Handle heapHandle = NULL;

    Error_init(eb);

    align = SystemUtils_align(pPrm->align, UTILS_MEM_SR_HEAP_MIN_ALIGN);
    size  = SystemUtils_align(pPrm->size, UTILS_MEM_SR_HEAP_MIN_ALIGN);

    heapHandle = Utils_memGetHeapHandleSR(pPrm->heapId);

    if(heapHandle)
    {
            /*
             * Heap is present in this CPU, allocate memory
             */
            addr = Memory_alloc(
                        heapHandle,
                        size,
                        align,
                        eb);
    }

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * MISRAC_WAIVER:
     * Typecasing pointer to Uint as buffer pointer pointer expects
     * in uint format
     * This API is called from memAlloc API, in case, this is failed,
     * Utils_memAlloc, then returns a NULL address
     */
    pPrm->bufferPtr = (UInt32)addr;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * MISRAC_WAIVER:
     * Typecasting here just to make sure that previous write is
     * completed to memory
     */
    /* read back value to ensure previous write, if it is to shared memory gets
     * written completely to memory
     */
    addr = (Ptr)pPrm->bufferPtr;

    if(addr!=NULL)
    {
        /* Invalidate is required here to ensure that we (this core) will
            not update memory, after releasing the memory */
        Cache_inv(addr, size, Cache_Type_ALL, (Bool)TRUE);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_memFreeSR(SystemCommon_FreeBuffer *pPrm)
{
    UInt32 size;
    IHeap_Handle heapHandle = NULL;

    size  = SystemUtils_align(pPrm->size, UTILS_MEM_SR_HEAP_MIN_ALIGN);

    heapHandle = Utils_memGetHeapHandleSR(pPrm->heapId);

    if(heapHandle)
    {
        /*
         * Heap is present in this CPU, free memory
         */
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * MISRAC_WAIVER:
         * Typecasting allocated int to poiner as memory_free expects
         * pointer as an argument.
         * Memory_free checks for the validity of the passed address in
         * the given heap
         */
        Memory_free(
                    heapHandle,
                    (Ptr)pPrm->bufferPtr,
                    size);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_memGetHeapStatsSR(Utils_MemHeapStats *pPrm)
{
    Utils_memGetHeapStats((Utils_HeapId)(pPrm->heapId), pPrm);
    return SYSTEM_LINK_STATUS_SOK;
}
