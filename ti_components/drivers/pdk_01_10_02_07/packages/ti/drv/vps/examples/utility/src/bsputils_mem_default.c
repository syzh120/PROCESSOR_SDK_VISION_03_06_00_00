/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>

/** \brief Maximum frame buffer memory pool size */
#if defined (SOC_TDA2XX) || defined (SOC_DRA75x) || defined (SOC_TDA2PX)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (236U * MB)
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (242U * MB)
#endif

#if defined (SOC_TDA3XX)
    #ifdef PLATFORM_ZEBU
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (64U * MB)
    #else
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (240U * MB)
    #endif
#define BSPUTILS_MEM_FRAME_HEAP_SIZE_12x12  (48U * MB)
#endif

#if defined (OMAP5430_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (246U * MB)
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (123U * MB)
#endif

#if defined (TI811X_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (57U * MB)
#endif

#ifdef CUSTOM_MEM_FRAME_HEAP_SIZE
#undef BSPUTILS_MEM_FRAME_HEAP_SIZE
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (CUSTOM_MEM_FRAME_HEAP_SIZE * MB)
#endif

/* Memory pool */
/* Align descriptor memory with that of VPDMA requirement. */
/* Place the frame heap in frame buffer section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPS_BUFFER_ALIGNMENT_RECOMMENDED)
#pragma DATA_SECTION(".bss:frameBuffer");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPS_BUFFER_ALIGNMENT_RECOMMENDED) DATA_SECTION(".bss:frameBuffer")
#else
#pragma DATA_ALIGN(gBspUtils_heapMemFrame, VPS_BUFFER_ALIGNMENT_RECOMMENDED)
#pragma DATA_SECTION(gBspUtils_heapMemFrame,".bss:frameBuffer");
#endif /* #if defined(__GNUC__) && !defined(__ti__) */
#endif  /* #ifdef __cplusplus */
UInt32 gBspUtils_heapMemFrame[(UInt32) BSPUTILS_MEM_FRAME_HEAP_SIZE /
                              (UInt32) sizeof (UInt32)];

Int32 BspUtils_memInit(void)
{
    UInt32 memSize;

    memSize = sizeof (gBspUtils_heapMemFrame);
    /* In case of TDA3xx 12x12 package, only 64MB DDR is present */
#if defined (SOC_TDA3XX)
    if (Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_12x12)
    {
        /* Out of 64MB, 16MB is used for code/data/descriptor */
        memSize = BSPUTILS_MEM_FRAME_HEAP_SIZE_12x12;
    }
#endif

    BspUtils_memInit_internal(gBspUtils_heapMemFrame, memSize);
    return 0;
}

