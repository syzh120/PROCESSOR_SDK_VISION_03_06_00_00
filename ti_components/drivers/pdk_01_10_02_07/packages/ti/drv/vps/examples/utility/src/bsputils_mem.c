/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file bsputils_mem.c
 *
 *  \brief Frame buffer memory allocator API.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#if defined (BARE_METAL)
#include <stdlib.h>
#else
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/knl/Clock.h>
#endif
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>

/* See bsputils_mem.h for function documentation  */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Memory pool handle */
HeapMem_Handle gBspUtils_heapMemFrameHandle = NULL;
#if !defined(BARE_METAL)
HeapMem_Struct gBspUtils_heapMemFrameStruct;
#endif

Bool           gBspUtils_memClearBuf;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 BspUtils_memInit_internal(UInt32 *pMemAddr, UInt32 memSize)
{
#if !defined (BARE_METAL)
    HeapMem_Params heapMemPrm;

    /* create memory pool heap  */
    HeapMem_Params_init(&heapMemPrm);

    heapMemPrm.buf  = pMemAddr;
    heapMemPrm.size = memSize;

    HeapMem_construct(&gBspUtils_heapMemFrameStruct, &heapMemPrm);
    gBspUtils_heapMemFrameHandle = HeapMem_handle(&gBspUtils_heapMemFrameStruct);
    GT_assert(BspAppTrace, gBspUtils_heapMemFrameHandle != NULL);
#endif
    gBspUtils_memClearBuf = (Bool) FALSE;

    return (BSP_SOK);
}

Int32 BspUtils_memDeInit(void)
{
    /* delete memory pool heap  */
#if !defined (BARE_METAL)
    HeapMem_destruct(&gBspUtils_heapMemFrameStruct);
    gBspUtils_heapMemFrameHandle = NULL;
#endif
    return (BSP_SOK);
}

Int32 BspUtils_memFrameGetSize(const Fvid2_Format *pFormat,
                               UInt32             *size,
                               UInt32             *cOffset)
{
    Int32  status = BSP_SOK;
    UInt32 bufferHeight;

    bufferHeight = pFormat->height;
    switch (pFormat->dataFormat)
    {
        case FVID2_DF_RAW08:
        case FVID2_DF_RAW16:
        case FVID2_DF_RAW24:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV444I:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RAW_VBI:
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_AGBR16_4444:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_XGBR16_1555:
        case FVID2_DF_AGBR16_1555:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_BAYER_RAW:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_GBRG:
            /* for single plane data format's */
            *size = pFormat->pitch[0] * bufferHeight;
            break;

        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV420SP_UV:
            /* for Y plane  */
            *size = pFormat->pitch[0] * bufferHeight;

            /* cOffset is at end of Y plane  */
            if (NULL != cOffset)
            {
                *cOffset = *size;
            }
            if (pFormat->dataFormat == FVID2_DF_YUV420SP_UV)
            {
                /* C plane height is 1/2 of Y plane */
                bufferHeight = bufferHeight / 2U;
            }

            /* for C plane  */
            *size += (pFormat->pitch[1] * bufferHeight);
            break;

        default:
            /* illegal data format  */
            status = BSP_EFAIL;
            break;
    }

    /* align size to minimum required frame buffer alignment  */
    *size = VpsUtils_align(*size, (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);

    return (status);
}

Int32 BspUtils_memFrameAlloc(Fvid2_Format *pFormat,
                             Fvid2_Frame  *pFrame,
                             UInt32        numFrames)
{
    Int32  status;
    UInt32 size, cOffset, frameId;
    UInt8 *pBaseAddr;

    /* align height to multiple of 2  */
    pFormat->height = VpsUtils_align(pFormat->height, (UInt32) 2U);

    /* get frame size for given pFormat */
    status = BspUtils_memFrameGetSize(pFormat, &size, &cOffset);
    if (status == BSP_SOK)
    {
        /* allocate the memory for 'numFrames' */

        /* for all 'numFrames' memory is contigously allocated  */
        pBaseAddr = (UInt8 *) BspUtils_memAlloc(
            (size * numFrames),
            (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
        if (pBaseAddr == NULL)
        {
            status = BSP_EALLOC;  /* Error in allocation, exit with error */
        }
    }

    if (status == BSP_SOK)
    {
        /* init memory pointer for 'numFrames'  */
        for (frameId = 0; frameId < numFrames; frameId++)
        {
            /* init Fvid2_Frame to 0's  */
            Fvid2Frame_init(pFrame);

            /* copy chNum to Fvid2_Frame from Fvid2_Format */
            pFrame->chNum      = pFormat->chNum;
            pFrame->addr[0][0] = pBaseAddr;

            switch (pFormat->dataFormat)
            {
                case FVID2_DF_RAW08:
                case FVID2_DF_RAW16:
                case FVID2_DF_RAW24:
                case FVID2_DF_RAW_VBI:
                case FVID2_DF_YUV422I_UYVY:
                case FVID2_DF_YUV422I_VYUY:
                case FVID2_DF_YUV422I_YUYV:
                case FVID2_DF_YUV422I_YVYU:
                case FVID2_DF_YUV444I:
                case FVID2_DF_RGB24_888:
                case FVID2_DF_BGR24_888:
                case FVID2_DF_BGRX_4444:
                case FVID2_DF_XBGR_4444:
                case FVID2_DF_AGBR16_4444:
                case FVID2_DF_RGBA16_4444:
                case FVID2_DF_XGBR16_1555:
                case FVID2_DF_AGBR16_1555:
                case FVID2_DF_BGR16_565:
                case FVID2_DF_XBGR24_8888:
                case FVID2_DF_RGBX24_8888:
                case FVID2_DF_ARGB32_8888:
                case FVID2_DF_ABGR32_8888:
                case FVID2_DF_RGBA32_8888:
                case FVID2_DF_BGRA32_8888:
                case FVID2_DF_BAYER_RAW:
                case FVID2_DF_BAYER_GRBG:
                case FVID2_DF_BAYER_RGGB:
                case FVID2_DF_BAYER_BGGR:
                case FVID2_DF_BAYER_GBRG:
                    break;
                case FVID2_DF_YUV422SP_UV:
                case FVID2_DF_YUV420SP_UV:
                    /* assign pointer for C plane */
                    pFrame->addr[0][1] = (UInt8 *) pFrame->addr[0][0] + cOffset;
                    break;
                default:
                    /* illegal data format  */
                    status = BSP_EFAIL;
                    break;
            }

            /* go to next frame */
            pFrame++;
            /* increment base address */
            pBaseAddr += size;
        }
    }

    GT_assert(BspAppTrace, status == BSP_SOK);

    return (status);
}

Int32 BspUtils_memFrameFree(const Fvid2_Format *pFormat,
                            Fvid2_Frame        *pFrame,
                            UInt32              numFrames)
{
    Int32  status;
    UInt32 size, cOffset;

    /* get frame size for given 'pFormat' */
    status = BspUtils_memFrameGetSize(pFormat, &size, &cOffset);
    if (status == BSP_SOK)
    {
        /* free the frame buffer memory */

        /* for all 'numFrames' memory is allocated contigously during alloc,
         *  so first frame memory pointer points to the complete
         *  memory block for all frames */
        BspUtils_memFree(pFrame->addr[0][0], (size * numFrames));
    }

    return (BSP_SOK);
}

#if defined (BARE_METAL)
/* Align stack memory to integer boundary. */
#if defined (__GNUC__) && !defined (__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:mallocSection")
#else
#pragma DATA_ALIGN(gBspUtils_mallocMem, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gBspUtils_mallocMem, ".bss:mallocSection")
#endif

/* Static memory allocation for bare metal */
#define  BSPUTILS_MALLOC_MEM_SIZE (0x4000000U)

uint8_t  gBspUtils_mallocMem[BSPUTILS_MALLOC_MEM_SIZE];
uint8_t *fw_mem_start_phy = (uint8_t*)&gBspUtils_mallocMem[0];
uint8_t *fw_mem_start = (uint8_t*)gBspUtils_mallocMem;
static uint8_t *fw_mem_end = (uint8_t*)(&gBspUtils_mallocMem[BSPUTILS_MALLOC_MEM_SIZE-1U]);
static uint8_t *fw_mem_alloc_ptr = (uint8_t*)gBspUtils_mallocMem;
/* Macro to align x to y */
#define align(x,y)   ((x + y) & (~y))

Ptr BspUtils_alignedMalloc(uint32_t    size,    uint32_t    alignment)
{
  uint8_t *alloc_ptr;
  Ptr     p_block = (Ptr) NULL;

  alloc_ptr = (uint8_t*)align((uint32_t)fw_mem_alloc_ptr, alignment);

  if ((alloc_ptr + size) < fw_mem_end)    {
    p_block =(void *)alloc_ptr;
    fw_mem_alloc_ptr = alloc_ptr + size;
  }

    return p_block;
}

void BspUtils_alignedFree(Ptr p, uint32_t size )
{
  /* Nothing to be done here */
}
#endif

Ptr BspUtils_memAlloc(UInt32 size, UInt32 align)
{
    Ptr addr;

    /* allocate memory  */
#if defined (BARE_METAL)
    addr = BspUtils_alignedMalloc(size, align);
#else
    addr = HeapMem_alloc(gBspUtils_heapMemFrameHandle, size, align, NULL);
#endif
    if (((Bool) (addr != NULL)) && gBspUtils_memClearBuf)
    {
        BspUtils_memset(addr, 0x80U, size);
        /* Flush and invalidate the CPU write */
        BspOsal_cacheWbInv(addr, size, BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
    }

    return (addr);
}

Int32 BspUtils_memFree(Ptr addr, UInt32 size)
{
    /* free previously allocated memory  */
#if defined (BARE_METAL)
   BspUtils_alignedFree(addr, size);
#else
    HeapMem_free(gBspUtils_heapMemFrameHandle, addr, size);
#endif
    return (BSP_SOK);
}

Int32 BspUtils_memClearOnAlloc(Bool enable)
{
    gBspUtils_memClearBuf = enable;

    return (BSP_SOK);
}

/**
 *  BspUtils_memGetHeapStat
 *  \brief Returns the current status (free size) of the various heaps used.
 *
 *  \param heapStat [OUT]   Status filled by the function.
 *
 */
void BspUtils_memGetHeapStat(BspUtils_MemHeapStatus *heapStat)
{
    /* NULL pointer check */
    GT_assert(BspAppTrace, NULL != heapStat);

    heapStat->freeSysHeapSize  = BspUtils_memGetSystemHeapFreeSpace();
    heapStat->freeBufHeapSize  = BspUtils_memGetBufferHeapFreeSpace();

    return;
}

/**
 *  BspUtils_memCheckHeapStat
 *  \brief Checks the current status of each heap with the value passed.
 *  This returns an error if the values of each of the heap doesn't match.
 *
 *  \param heapStat [IN]    Older status to be compared with the current status.
 *
 *  \return                 Returns 0 if the heap sizes match else return
 *                          BSP_EFAIL.
 */
Int32 BspUtils_memCheckHeapStat(const BspUtils_MemHeapStatus *heapStat)
{
    Int32 retVal = BSP_SOK;
    BspUtils_MemHeapStatus curStat;

    /* NULL pointer check */
    GT_assert(BspAppTrace, NULL != heapStat);

    BspUtils_memGetHeapStat(&curStat);

    if (heapStat->freeSysHeapSize != curStat.freeSysHeapSize)
    {
        GT_1trace(BspAppTrace, GT_CRIT,
                  "Warning: Memory leak (%d bytes) in System Heap!!\r\n",
                  (heapStat->freeSysHeapSize - curStat.freeSysHeapSize));
        retVal = BSP_EFAIL;
    }
    if (heapStat->freeBufHeapSize != curStat.freeBufHeapSize)
    {
        GT_1trace(BspAppTrace, GT_CRIT,
                  "Warning: Memory leak (%d bytes) in Buffer Heap!!\r\n",
                  (heapStat->freeBufHeapSize - curStat.freeBufHeapSize));
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

UInt32 BspUtils_memGetSystemHeapFreeSpace(void)
{
#if   !defined (BARE_METAL)
    Memory_Stats stats;
    extern const IHeap_Handle Memory_defaultHeapInstance;

    Memory_getStats(Memory_defaultHeapInstance, &stats);

    return ((UInt32) (stats.totalFreeSize));
#else
    return ((UInt32) 1U);
#endif
}

UInt32 BspUtils_memGetBufferHeapFreeSpace(void)
{
    UInt32       totalFreeSize = 0U;
#if   !defined (BARE_METAL)
    Memory_Stats stats;

    if (NULL != gBspUtils_heapMemFrameHandle)
    {
        HeapMem_getStats(gBspUtils_heapMemFrameHandle, &stats);
        totalFreeSize = (UInt32) stats.totalFreeSize;
    }
#endif
    return (totalFreeSize);
}

