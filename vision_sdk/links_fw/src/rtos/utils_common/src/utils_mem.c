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
 * \file utils_mem.c
 *
 * \brief  This file has the implementataion of Display Control Driver Calls
 *
 *         This file implements the calls to display controller driver.
 *         Calls to driver create, control commands, deletion is done in this
 *         file. Conversion / population of FVID2 parameters based on
 *         parameters of link API structures happen here.|
 *
 * \version 0.0 (Jun 2013) : [PS] First version
 * \version 0.1 (Jul 2013) : [PS] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
*/
#include "utils_mem_priv.h"

void System_memPrintHeapStatus(void);

/**
 *******************************************************************************
 * \brief Macro to enable the memory/Heap debug
 *******************************************************************************
*/

#ifdef ENABLE_HEAP_L2

/**
 *******************************************************************************
 * \brief L2 heap memory
 *******************************************************************************
*/
/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#pragma DATA_ALIGN(gUtils_memHeapL2, 4)
/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * Non-documented pragma directive.
 * KW State: Fixed in Later Release -> Waiver
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#pragma DATA_SECTION(gUtils_memHeapL2, ".bss:heapMemL2")
UInt8 gUtils_memHeapL2[UTILS_MEM_HEAP_L2_SIZE];

#endif

Utils_MemHeapObj gUtils_memHeapObj[UTILS_HEAPID_MAXNUMHEAPS];

/**
 *******************************************************************************
 *
 * \brief One time system init of memory allocator
 *
 *        Should be called by application before using allocate APIs
 *
 * \return SYSTEM_LINK_STATUS_SOK on sucess, else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memInit(void)
{
    extern const IHeap_Handle Memory_defaultHeapInstance;
    Utils_MemHeapStats memStats;
    Utils_HeapId       heapId;

    memset(gUtils_memHeapObj, 0, sizeof(gUtils_memHeapObj));

    snprintf(gUtils_memHeapObj[UTILS_HEAPID_DDR_NON_CACHED_SR0].heapName,
             sizeof(gUtils_memHeapObj[UTILS_HEAPID_DDR_NON_CACHED_SR0].heapName),
             "SR_DDR_NON_CACHED");

    snprintf(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR].heapName,
             sizeof(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR].heapName),
             "SR_DDR_CACHED");

    snprintf(gUtils_memHeapObj[UTILS_HEAPID_OCMC_SR].heapName,
             sizeof(gUtils_memHeapObj[UTILS_HEAPID_OCMC_SR].heapName),
             "SR_OCMC");

    #ifdef ECC_FFI_INCLUDE
    snprintf(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL].heapName,
             sizeof(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL].heapName),
             "SR_DDR_CACHED_SR_ECC_ASIL");
    snprintf(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_ECC_QM].heapName,
             sizeof(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_ECC_QM].heapName),
             "SR_DDR_CACHED_SR_ECC_QM");
    snprintf(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL].heapName,
             sizeof(gUtils_memHeapObj[UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL].heapName),
             "SR_DDR_CACHED_SR_NON_ECC_ASIL");
    #endif
    #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
    Utils_memHeapSetup();
    #endif

    heapId = UTILS_HEAPID_DDR_CACHED_LOCAL;

    snprintf(gUtils_memHeapObj[heapId].heapName,
            sizeof(gUtils_memHeapObj[heapId].heapName),
            "LOCAL_DDR");
    gUtils_memHeapObj[heapId].heapHandle = Memory_defaultHeapInstance;
    gUtils_memHeapObj[heapId].heapAddr   = 0; /* Local heap address cannot be retrived */
    gUtils_memHeapObj[heapId].isClearBufOnAlloc = (Bool)FALSE;

    Utils_memGetHeapStats(heapId, &memStats);

    gUtils_memHeapObj[heapId].heapSize = memStats.heapSize;

#ifdef ENABLE_HEAP_L2
    heapId = UTILS_HEAPID_L2_LOCAL;

    snprintf(gUtils_memHeapObj[heapId].heapName,
             sizeof(gUtils_memHeapObj[heapId].heapName),
             "LOCAL_L2");
    gUtils_memHeapObj[heapId].heapHandle = NULL;
    gUtils_memHeapObj[heapId].heapAddr = (UInt32)gUtils_memHeapL2;
    gUtils_memHeapObj[heapId].heapAllocOffset = 0;
    gUtils_memHeapObj[heapId].isClearBufOnAlloc = (Bool)FALSE;
    gUtils_memHeapObj[heapId].heapSize   = sizeof(gUtils_memHeapL2);
#endif

    Utils_memClearOnAlloc((Bool)TRUE);

    /* INVARIANT_CONDITION.UNREACH
    * MISRAC_2004_Rule_13.7
    * MISRAC_WAIVER:
    * Code is currently unreachable.
    * This is kept to ensure future updates by the called function.
    */
    if((System_isFastBootEnabled() == (Bool)TRUE) ||
       (System_isSrvFastBootEnabled() == (Bool)TRUE) ||
      (System_isHLOSFastBootEnabled() == (Bool)TRUE))
    {
        Utils_memClearOnAlloc((Bool)FALSE);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief One time system de-init of memory allocator
 *
 *        Should be called by application at system de-init
 *
 * \return SYSTEM_LINK_STATUS_SOK on sucess, else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memDeInit(void)
{
    memset(gUtils_memHeapObj, 0, sizeof(gUtils_memHeapObj));

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Allocate memory from Frame buffer memory pool
 *
 * \param heapId   [IN] Heap ID
 * \param size     [IN] size in bytes
 * \param align    [IN] alignment in bytes
 *
 * \return NULL or error, else memory pointer
 *
 *******************************************************************************
*/
Ptr Utils_memAlloc(Utils_HeapId heapId, UInt32 size, UInt32 align)
{
    Ptr addr;
    UInt32 heapIdInt, tempAddr;
    Error_Block ebObj;
    Error_Block *eb = &ebObj;
    IHeap_Handle heapHandle;

    if(heapId >= UTILS_HEAPID_MAXNUMHEAPS)
    {
        addr = NULL;
    }
    else
    {
        Error_init(eb);

        heapIdInt = (UInt32)heapId;

        #ifdef UTILS_MEM_DEBUG
        {
            Utils_MemHeapStats stats;

            Utils_memGetHeapStats(heapId, &stats);

            Vps_printf(" UTILS: MEM: Alloc'ing from heap %s. (required size = %d B,"
                   "free space = %d B)\n",
                   gUtils_memHeapObj[heapIdInt].heapName,
                   size,
                   stats.freeSize
                  );
        }
        #endif

        if(UTILS_HEAPID_L2_LOCAL == heapId)
        {
            UInt32 offset;
            UInt32 oldIntState;

            oldIntState = Hwi_disable();

            offset = SystemUtils_align(
                        gUtils_memHeapObj[heapIdInt].heapAllocOffset,
                        align);

            if( (offset + size) > gUtils_memHeapObj[heapIdInt].heapSize)
            {
                addr = NULL;
            }
            else
            {
                tempAddr = gUtils_memHeapObj[heapIdInt].heapAddr + offset;

                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004 Rule_11.3
                 * MISRAC_WAIVER:
                 * Allocated address is typecasted to pointer,
                 * There is an error check to make sure that address is not
                 * going beyond L2 memory size.
                 * also address is returned from this function, so caller will
                 * check returned value againts null.
                 */
                addr = (Ptr)tempAddr;

                gUtils_memHeapObj[heapIdInt].heapAllocOffset
                    = offset + size;
            }

            Hwi_restore(oldIntState);
        }
        else if(UTILS_HEAPID_DDR_CACHED_LOCAL == heapId)
        {
            heapHandle = gUtils_memHeapObj[heapIdInt].heapHandle;
            /*
             * Heap is present in this CPU, allocate memory
             */
            addr = Memory_alloc(heapHandle,
                               size,
                               align,
                               eb);
        }
        /* INVARIANT_CONDITION.UNREACH
        * MISRAC_2004_Rule_13.7
        * MISRAC_WAIVER:
        * Code is currently unreachable.
        * This is kept to ensure future updates by the called function.
        */
        else if((UTILS_HEAPID_DDR_CACHED_SR == heapId) ||
                (UTILS_HEAPID_OCMC_SR == heapId) ||
                (UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL == heapId) ||
                (UTILS_HEAPID_DDR_CACHED_SR_ECC_QM == heapId) ||
                (UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL == heapId) ||
                (UTILS_HEAPID_DDR_NON_CACHED_SR0 == heapId))
        {
            /*
             * Allocate from heap created on IPU1-0
             */
            SystemCommon_AllocBuffer bufAlloc;
            Int32 status = SYSTEM_LINK_STATUS_SOK;

            bufAlloc.bufferPtr = 0U;
            bufAlloc.heapId = heapIdInt;
            bufAlloc.size = size;
            bufAlloc.align = align;

            #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
            /*
             * Alloc locally
             */
            status = Utils_memAllocSR(&bufAlloc);
            #else
            /*
             * Alloc by sending command to IPU1-0 core
             */
            status = System_linkControl(
                        (UInt32)SYSTEM_LINK_ID_IPU1_0,
                        SYSTEM_COMMON_CMD_ALLOC_BUFFER,
                        &bufAlloc,
                        sizeof(bufAlloc),
                        (Bool)TRUE
                        );
            #endif

            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                addr = NULL;
            }
            else
            {
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004 Rule_11.3
                 * MISRAC_WAIVER:
                 * Allocated address is typecasted to pointer,
                 * ALLOC_BUFFER command is implemented using BIOS heap, which
                 * makes sure that the memory space is allocated from
                 * reserved space or it returns error,
                 * also address is returned from this function, so caller will
                 * check returned value againts null.
                 */
                addr = (Ptr)bufAlloc.bufferPtr;
            }
        }
        else
        {
            UTILS_assert((Bool)FALSE);
        }

        #ifdef UTILS_MEM_DEBUG
        Vps_printf(" UTILS: MEM: ALLOC, addr = 0x%08x, size = %d bytes, heap = %s \n",
                addr,
                size,
                gUtils_memHeapObj[heapIdInt].heapName
               );
        #endif

        if (gUtils_memHeapObj[heapIdInt].isClearBufOnAlloc)
        {
            if (NULL != addr)
            {
                if (!Error_check(eb))
                {
                    memset(addr, 0x0, size);

                    if((UTILS_HEAPID_DDR_CACHED_SR == heapId) ||
                       (UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL == heapId) ||
                       (UTILS_HEAPID_DDR_CACHED_SR_ECC_QM == heapId) ||
                       (UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL == heapId))
                    {
                        BspOsal_cacheWb(addr,
                            size,
                            BSP_OSAL_CT_ALL,
                            BSP_OSAL_WAIT_FOREVER);
                    }
                }
            }
        }
    }

    return addr;
}

/**
 *******************************************************************************
 *
 * \brief Free previously allocate Frame buffer memory pointer
 *
 * \param heapId   [IN] Heap ID;
 * \param addr     [IN] memory pointer to free
 * \param size     [IN] size of memory pointed to by the memory pointer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memFree(Utils_HeapId heapId, Ptr addr, UInt32 size)
{
    IHeap_Handle heapHandle;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(heapId >= UTILS_HEAPID_MAXNUMHEAPS)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {

#ifdef UTILS_MEM_DEBUG
    Vps_printf(" UTILS: MEM: FRAME FREE, addr = 0x%08x, size = %d bytes,"
           " heap = %s\n",
           addr,
           size,
           gUtils_memHeapObj[heapId].heapName);
#endif

        if(UTILS_HEAPID_L2_LOCAL == heapId)
        {
            UInt32 oldIntState;

            oldIntState = Hwi_disable();

            gUtils_memHeapObj[heapId].heapAllocOffset = 0;

            Hwi_restore(oldIntState);
        }
        else if(UTILS_HEAPID_DDR_CACHED_LOCAL == heapId)
        {
            heapHandle = gUtils_memHeapObj[heapId].heapHandle;
            /*
             * free previously allocated memory
             */
            Memory_free(heapHandle,
                        addr,
                        size);
        }
        /* INVARIANT_CONDITION.UNREACH
        * MISRAC_2004_Rule_13.7
        * MISRAC_WAIVER:
        * Code is currently unreachable.
        * This is kept to ensure future updates by the called function.
        */
        else if ((UTILS_HEAPID_DDR_CACHED_SR == heapId) ||
                 (UTILS_HEAPID_OCMC_SR == heapId) ||
                 (UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL == heapId) ||
                 (UTILS_HEAPID_DDR_CACHED_SR_ECC_QM == heapId) ||
                 (UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL == heapId) ||
                 (UTILS_HEAPID_DDR_NON_CACHED_SR0 == heapId))
        {
            /*
             * Free from heap created on IPU1-0
             */
            SystemCommon_FreeBuffer bufFree;

            /* Invalidate is required here to ensure that we (this core) will
                not update memory, after releasing the memory */
            Cache_inv(addr, size, Cache_Type_ALL, (Bool)TRUE);

            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004 Rule_11.3
             * MISRAC_WAIVER:
             * Pointer is typecasted to int,
             * This command is implemented using Bios Heap api Memory_free,
             * which checks for the validity of the pointer and size.
             */
            bufFree.bufferPtr = (UInt32)addr;
            bufFree.heapId = heapId;
            bufFree.size = size;

            #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
            Utils_memFreeSR(&bufFree);
            #else
            status = System_linkControl(
                        (UInt32)SYSTEM_LINK_ID_IPU1_0,
                        SYSTEM_COMMON_CMD_FREE_BUFFER,
                        &bufFree,
                        sizeof(bufFree),
                        (Bool)TRUE
                        );
            #endif
        }
        else
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Control if allocated buffer needs to be cleared to 0
 *
 *        By default allocated buffer will not be cleared to 0
 *
 * \param   enable [IN] TRUE: clear allocated buffer, FALSE: do not clear
 *                      allocated buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memClearOnAlloc(Bool enable)
{
    UInt32 i;

    for (i=0; i<UTILS_HEAPID_MAXNUMHEAPS; i++)
    {
        gUtils_memHeapObj[i].isClearBufOnAlloc = enable;
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Returns the heap information to the user
 *
 * \param   heapId  [IN] Heap ID;
 * \param   pStats  [OUT] Heap information
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Utils_memGetHeapStats(Utils_HeapId heapId, Utils_MemHeapStats *pStats)
{
    IHeap_Handle heapHandle;
    Memory_Stats stats;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    memset(pStats, 0, sizeof(Utils_MemHeapStats));
    pStats->heapId = heapId;

    if(heapId >= UTILS_HEAPID_MAXNUMHEAPS)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        strcpy(pStats->heapName, gUtils_memHeapObj[heapId].heapName);
        pStats->heapAddr = gUtils_memHeapObj[heapId].heapAddr;

        if(heapId==UTILS_HEAPID_L2_LOCAL)
        {
            UInt32 oldIntState;

            oldIntState = Hwi_disable();

            pStats->heapSize = gUtils_memHeapObj[heapId].heapSize;
            pStats->freeSize =
                gUtils_memHeapObj[heapId].heapSize -
                gUtils_memHeapObj[heapId].heapAllocOffset;

            Hwi_restore(oldIntState);
        }
        else if(UTILS_HEAPID_DDR_CACHED_LOCAL == heapId)
        {
            heapHandle = gUtils_memHeapObj[heapId].heapHandle;
            if(NULL != heapHandle)
            {
                Memory_getStats(heapHandle, &stats);
                pStats->heapSize = stats.totalSize;
                pStats->freeSize = stats.totalFreeSize;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
        }
        /* INVARIANT_CONDITION.UNREACH
        * MISRAC_2004_Rule_13.7
        * MISRAC_WAIVER:
        * Code is currently unreachable.
        * This is kept to ensure future updates by the called function.
        */
        else if((UTILS_HEAPID_DDR_CACHED_SR == heapId) ||
                (UTILS_HEAPID_OCMC_SR == heapId) ||
                (UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL == heapId) ||
                (UTILS_HEAPID_DDR_CACHED_SR_ECC_QM == heapId) ||
                (UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL == heapId) ||
                (UTILS_HEAPID_DDR_NON_CACHED_SR0 == heapId))
        {
            #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
            heapHandle = gUtils_memHeapObj[heapId].heapHandle;
            if(NULL != heapHandle)
            {
                Memory_getStats(heapHandle, &stats);
                pStats->heapSize = stats.totalSize;
                pStats->freeSize = stats.totalFreeSize;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            #else
            System_linkControl(
                        (UInt32)SYSTEM_LINK_ID_IPU1_0,
                        SYSTEM_COMMON_CMD_GET_HEAP_STATS,
                        pStats,
                        sizeof(*pStats),
                        (Bool)TRUE
                        );
            #endif
        }
        else
        {
            UTILS_assert((Bool)FALSE);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Get buffer size based on data format
 *
 * CbCr buffer height is required for semiplanar data formats.
 * For semiplanar data formats CbCr buffer height will be
 * either equal to Y buffer height or half of Y buffer height
 * based on YUV422 or YUv420 data format. This function
 * calculates that internally. But in case cbCrBufferHeight needs to be
 * different than cbCrBufferHeight parameter can be used. For all normal
 * cases where function needs to internally calculate this, caller should
 * pass cbCrBufferHeight = 0. Currently cbCrBufferHeight takes effect for
 * only semiplanar data
 *
 * \param     pFormat          [IN] data format information
 * \param     *size            [IN] buffer size
 * \param     *cOffset         [IN] C plane offset for YUV420SP data
 * \param     cbCrBufferHeight [IN] Height of CbCr plane for YUV420SP data
 *                                  incase
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memFrameGetSize(const FVID2_Format * pFormat,
                            UInt32 * size,
                            UInt32 * cOffset,
                            UInt32 cbCrBufferHeight)
{
    UInt32 bufferHeight;
    Int32 status = 0;

    bufferHeight = pFormat->height;

    switch (pFormat->dataFormat)
    {
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV444I:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_BGR24_888:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_RAW_VBI:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_BAYER_RAW:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_GBRG:
        case FVID2_DF_RAW16:
            /*
             * for single plane data format's
             */
            *size = pFormat->pitch[0U] * bufferHeight;
            break;

        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV420SP_UV:

            /*
             * for Y plane
             */
            *size = pFormat->pitch[0U] * bufferHeight;

            /*
             * cOffset is at end of Y plane
             */
            *cOffset = *size;

            if (pFormat->dataFormat == FVID2_DF_YUV420SP_UV)
            {
                if (0U == cbCrBufferHeight)
                {
                    bufferHeight = bufferHeight / 2U;
                }
                else
                {
                    bufferHeight = cbCrBufferHeight;
                }
            }

            *size += (pFormat->pitch[1U] * bufferHeight);
            break;

        default:
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
    }

    /*
     * align size to minimum required frame buffer alignment
     */
    *size = VpsUtils_align(*size, VPS_BUFFER_ALIGNMENT);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Allocate a frame
 *
 * Use FVID2_Format to allocate a frame.
 * Fill FVID2_Frame fields like channelNum based on FVID2_Format
 *
 * CbCr buffer height is required for semiplanar data formats.
 * For semiplanar data formats CbCr buffer height will be
 * either equal to Y buffer height or half of Y buffer height
 * based on YUV422 or YUv420 data format. This function
 * calculates that internally. But in case cbCrBufferHeight needs to be
 * different than cbCrBufferHeight parameter can be used. For all normal
 * cases where function needs to internally calculate this, caller should
 * pass cbCrBufferHeight = 0. Currently cbCrBufferHeight takes effect for
 * only semiplanar data
 *
 * \param      pFormat          [IN]  Data format information
 * \param      frame            [OUT] Initialzed FVID2_Frame structure
 * \param      numFrames        [IN]  Number of frames to allocate
 * \param      cbCrBufferHeight [IN]  Height of CbCr plane for YUV420SP data
 *                                     incase
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memFrameAlloc(FVID2_Format * pFormat,
                          FVID2_Frame frame[],
                          UInt16 numFrames,
                          UInt32 cbCrBufferHeight)
{
    UInt32 size, cOffset, frameId;
    Int32 status;
    UInt8 *pBaseAddr;

    pFormat->height = VpsUtils_align(pFormat->height, 2U);

    status = Utils_memFrameGetSize(pFormat, &size, &cOffset, cbCrBufferHeight);

    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        /*
         * allocate the memory for 'numFrames'
         * init memory pointer for 'numFrames'
         */
        for (frameId = 0U; frameId < numFrames; frameId++)
        {
            pBaseAddr = Utils_memAlloc(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                size,
                                SYSTEM_BUFFER_ALIGNMENT
                            );
            if (pBaseAddr == NULL)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
            }

            memset(&frame[frameId], 0, sizeof(FVID2_Frame));

            /*
             * copy channelNum to FVID2_Frame from FVID2_Format
             */
            frame[frameId].chNum = pFormat->chNum;
            frame[frameId].addr[0U][0U] = pBaseAddr;

            switch (pFormat->dataFormat)
            {
                case FVID2_DF_RAW_VBI:
                case FVID2_DF_YUV422I_UYVY:
                case FVID2_DF_YUV422I_VYUY:
                case FVID2_DF_YUV422I_YUYV:
                case FVID2_DF_YUV422I_YVYU:
                case FVID2_DF_YUV444I:
                case FVID2_DF_RGB24_888:
                case FVID2_DF_BGR24_888:
                case FVID2_DF_RGB16_565:
                case FVID2_DF_BGR16_565:
                case FVID2_DF_ARGB32_8888:
                case FVID2_DF_RGBA32_8888:
                case FVID2_DF_ABGR32_8888:
                case FVID2_DF_BGRA32_8888:
                case FVID2_DF_BGRA16_4444:
                case FVID2_DF_BAYER_RAW:
                case FVID2_DF_BAYER_GRBG:
                case FVID2_DF_BAYER_RGGB:
                case FVID2_DF_BAYER_BGGR:
                case FVID2_DF_BAYER_GBRG:
                case FVID2_DF_RAW16:
                    break;
                case FVID2_DF_YUV422SP_UV:
                case FVID2_DF_YUV420SP_UV:
                    /* MISRA.PTR.ARITH
                     * MISRAC_2004 Rule_17.1 & MISRAC_2004 Rule_17.4
                     * MISRAC_WAIVER:
                     * Frame start address is added with chroma offset to
                     * get the chroma buffer offset
                     * Complete frame buffer is allocated using memAlloc API,
                     * which makes sure that complete frame buffer is allcated.
                     */
                    /* assign pointer for C plane */
                    frame[frameId].addr[0U][1U] = (UInt8 *) frame[frameId].addr[0][0] + cOffset;
                    break;
                default:
                    /* illegal data format */
                    status = SYSTEM_LINK_STATUS_EFAIL;
                    break;
            }

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 & MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer to frame is incremented to get next frame location
             * size is same for all frame buffers and all frame buffers
             * are located using single memAlloc api, sure that complete
             * memory is allcated, so baseAddress will never be point to null
             * or out of allocated space.
             */
        }
    }

    if (status != 0)
    {

        Vps_printf(" UTILS: MEM: Memory allocation failed due to "
                   " insufficient free memory, "
                   "requested - %d \n",
                   size * numFrames);
        System_memPrintHeapStatus();
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Free's previously allocate FVID2_Frame's
 *
 * CbCr buffer height is required for semiplanar data formats.
 * For semiplanar data formats CbCr buffer height will be
 * either equal to Y buffer height or half of Y buffer height
 * based on YUV422 or YUv420 data format. This function
 * calculates that internally. But in case cbCrBufferHeight needs to be
 * different than cbCrBufferHeight parameter can be used. For all normal
 * cases where function needs to internally calculate this, caller should
 * pass cbCrBufferHeight = 0. Currently cbCrBufferHeight takes effect for
 * only semiplanar data
 *
 * \param      pFormat          [IN]  Data format information
 * \param      frame            [OUT] Initialzed FVID2_Frame structure
 * \param      numFrames        [IN]  Number of frames to free
 * \param      cbCrBufferHeight [IN]  Height of CbCr plane for YUV420SP data
 *                                     incase
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success else SYSTEM_LINK_STATUS_EFAIL
 *
 *******************************************************************************
*/
Int32 Utils_memFrameFree(const FVID2_Format * pFormat,
                         FVID2_Frame frame[],
                         UInt16 numFrames,
                         UInt32 cbCrBufferHeight)
{
    UInt32 size, cOffset, frameId;
    Int32 status;
    /*
     * get frame size for given 'pFormat'
     */
    status = Utils_memFrameGetSize(pFormat, &size, &cOffset, cbCrBufferHeight);

    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        /*
         * free the frame buffer memory
         */
        for(frameId = 0; frameId < numFrames; frameId++)
        {
            Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                      frame[frameId].addr[0U][0U], size);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/*
 * \brief For Bios implementation, virtual and physical pointers are same
 */
void *Utils_memPhysToVirt(void *physPtr)
{
    return physPtr;
}
