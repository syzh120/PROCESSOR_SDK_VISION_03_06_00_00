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
 *  \file bsputils_tiler.c
 *
 *  \brief This file implements application level tiler utils functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/examples/utility/bsputils_tiler.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPUTILS_TILER_CNT_8BIT_SIZE    (80U * MB)
#define BSPUTILS_TILER_CNT_16BIT_SIZE   (48U * MB)
#define BSPUTILS_TILER_CNT_32BIT_SIZE   (0U * MB)

#define BSPUTILS_TILER_MAX_HEIGHT_8BIT   (BSPUTILS_TILER_CNT_8BIT_SIZE / \
                                          VPSUTILS_TILER_CNT_8BIT_PITCH)
#define BSPUTILS_TILER_MAX_HEIGHT_16BIT  (BSPUTILS_TILER_CNT_16BIT_SIZE / \
                                          VPSUTILS_TILER_CNT_16BIT_PITCH)
#define BSPUTILS_TILER_MAX_HEIGHT_32BIT  (BSPUTILS_TILER_CNT_32BIT_SIZE / \
                                          VPSUTILS_TILER_CNT_32BIT_PITCH)

#define BSPUTILS_TILER_CNT_8BIT_MAX_LINES   (8U * 1024U)
#define BSPUTILS_TILER_CNT_16BIT_MAX_LINES  (4U * 1024U)
#define BSPUTILS_TILER_CNT_32BIT_MAX_LINES  (4U * 1024U)

#define BSPUTILS_TILER_CNT_8BIT_SWAP_MAX_LINES  (16U * 1024U)
#define BSPUTILS_TILER_CNT_16BIT_SWAP_MAX_LINES (16U * 1024U)
#define BSPUTILS_TILER_CNT_32BIT_SWAP_MAX_LINES (8U * 1024U)

#define BSPUTILS_TILER_REG_BASE                       (0x4E000100U)
#define BSPUTILS_TILER_DMM_PAT_VIEW_MAP_BASE          (0x4E000460U)
#define BSPUTILS_TILER_DMM_PAT_VIEW_MAP__0            (0x4E000440U)

#define BSPUTILS_TILER_DMM_PAT_VIEW_MASK              (0x80000000U)
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
/* In TI81xx platforms, this is a 4 bit entry starting from 28th bit. */
#define BSPUTILS_TILER_DMM_PAT_VIEW_MAP_OFFSET_MASK   (0x78000000U)
#define BSPUTILS_TILER_DMM_PAT_VIEW_MAP_OFFSET_SHIFT  (27U)
#else
#define BSPUTILS_TILER_DMM_PAT_VIEW_MAP_OFFSET_MASK   (0x70000000U)
#define BSPUTILS_TILER_DMM_PAT_VIEW_MAP_OFFSET_SHIFT  (28U)
#endif

#define BSPUTILS_TILER_DMM_PAT_TWO_NIBBLE_SHIFT       (8U)

#define BSPUTILS_TILER_PUT_CNT_MODE(tilerAddr, cntMode) \
    (((tilerAddr) | (((cntMode) & 0x3U) << 27)))

#define BSPUTILS_TILER_ORI_MODE_SHIFT   (29U)
#define BSPUTILS_TILER_ORI_MODE_MASK    ((UInt32) 0x07U << \
                                         BSPUTILS_TILER_ORI_MODE_SHIFT)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32 curX[BSPUTILS_TILER_CNT_MAX];
    UInt32 curStartY[BSPUTILS_TILER_CNT_MAX];
    UInt32 curEndY[BSPUTILS_TILER_CNT_MAX];
    UInt32 enableLog;
} BspUtils_TilerObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 BspUtils_tilerGetMaxPitchHeight(UInt32  cntMode,
                                             UInt32 *maxPitch,
                                             UInt32 *maxHeight);

/**
 *  \brief BspUtils_getCntMode  function.
 *
 *  \param tilerAddr     [IN] tilerAddr.
 *
 */
static inline UInt32 BspUtils_getCntMode(UInt32 tilerAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#ifdef __cplusplus
#pragma DATA_ALIGN(32*KB)
#pragma DATA_SECTION(".bss:tilerBuffer");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32*KB) DATA_SECTION(".bss:tilerBuffer")
#else
#pragma DATA_ALIGN(gBspUtils_tilerPhysMem, 32*KB)
#pragma DATA_SECTION(gBspUtils_tilerPhysMem,".bss:tilerBuffer");
#endif
#endif  /* #ifdef __cplusplus */
UInt8             gBspUtils_tilerPhysMem[BSPUTILS_TILER_PHYS_MEM_SIZE];

BspUtils_TilerObj gBspUtils_tilerObj;
static Bool       gBspTilerInitDone = FALSE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static inline UInt32 BspUtils_getCntMode(UInt32 tilerAddr)
{
    UInt32 cntMode;
    cntMode = (((tilerAddr) >> 27) & 0x3U);
    return cntMode;
}

Int32 BspUtils_tilerInit(void)
{
    volatile UInt32 *pReg =
        (volatile UInt32 *) BSPUTILS_TILER_DMM_PAT_VIEW_MAP_BASE;
    volatile UInt32 *mReg =
        (volatile UInt32 *) BSPUTILS_TILER_DMM_PAT_VIEW_MAP__0;
    UInt32           offsetVal;

    /* Check alignment - should be aligned to 256MB and in TI81xx should be
     * aligned to 128MB. */
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    if ((UInt32) gBspUtils_tilerPhysMem & 0x7FFFFFFU)
    {
        GT_0trace(
            BspAppTrace, GT_ERR,
            "Error: Tiler base address should be aligned to 128MB!!\r\n");
    }
#else
    if ((UInt32) gBspUtils_tilerPhysMem & 0xFFFFFFFU)
    {
        GT_0trace(
            BspAppTrace, GT_ERR,
            "Error: Tiler base address should be aligned to 256MB!!\r\n");
    }
#endif

    /* Only one bit will be set in this register so masking with 0x80000000 */
    *pReg = (UInt32) gBspUtils_tilerPhysMem & BSPUTILS_TILER_DMM_PAT_VIEW_MASK;

    /* Extract the offset value from the tiler address,
     * Offset value is same for 8bit tile and 16 bit tiler
     * Store this offset vale in MAP__0 register          */
    offsetVal = (((UInt32) gBspUtils_tilerPhysMem
                  & BSPUTILS_TILER_DMM_PAT_VIEW_MAP_OFFSET_MASK) >>
                 BSPUTILS_TILER_DMM_PAT_VIEW_MAP_OFFSET_SHIFT);
    *mReg |=
        ((offsetVal << BSPUTILS_TILER_DMM_PAT_TWO_NIBBLE_SHIFT) | offsetVal);

    gBspTilerInitDone = (Bool) TRUE;
    BspUtils_tilerFreeAll();
    BspUtils_tilerDebugLogEnable(FALSE);

    return (0);
}

Int32 BspUtils_tilerDeInit(void)
{
    gBspTilerInitDone = (Bool) FALSE;
    return (0);
}

Int32 BspUtils_tilerDebugLogEnable(UInt32 enable)
{
    gBspUtils_tilerObj.enableLog = enable;

    return (0);
}

UInt32 BspUtils_tilerAddr2CpuAddr(UInt32 tilerAddr)
{
    UInt32 cpuAddr, cntMode;

    cntMode = BspUtils_getCntMode(tilerAddr);

    cpuAddr = BSPUTILS_TILER_CPU_VIRT_ADDR +
              (BSPUTILS_TILER_PHYS_MEM_SIZE * cntMode);
    cpuAddr += (tilerAddr & 0x07FFFFFFU);

    if (gBspUtils_tilerObj.enableLog)
    {
        Bsp_printf(" [TILER] Tiler Addr = 0x%08x, CPU Addr = 0x%08x\r\n",
                   tilerAddr, cpuAddr);
    }

    return (cpuAddr);
}

static Int32 BspUtils_tilerGetMaxPitchHeight(UInt32  cntMode,
                                             UInt32 *maxPitch,
                                             UInt32 *maxHeight)
{
    Int32 retVal = 0;
    *maxPitch  = 0;
    *maxHeight = 0;

    switch (cntMode)
    {
        case BSPUTILS_TILER_CNT_8BIT:
            *maxPitch  = VPSUTILS_TILER_CNT_8BIT_PITCH;
            *maxHeight = BSPUTILS_TILER_MAX_HEIGHT_8BIT;
            break;
        case BSPUTILS_TILER_CNT_16BIT:
            *maxPitch  = VPSUTILS_TILER_CNT_16BIT_PITCH;
            *maxHeight = BSPUTILS_TILER_MAX_HEIGHT_16BIT;
            break;
        case BSPUTILS_TILER_CNT_32BIT:
            *maxPitch  = VPSUTILS_TILER_CNT_32BIT_PITCH;
            *maxHeight = BSPUTILS_TILER_MAX_HEIGHT_32BIT;
            break;
        default:
            retVal = -1;
            break;
    }

    return (retVal);
}

UInt32 BspUtils_tilerGetAddr(UInt32 cntMode, UInt32 startX, UInt32 startY)
{
    UInt32 tilerAddr, maxPitch, maxHeight, offset;

    BspUtils_tilerGetMaxPitchHeight(cntMode, &maxPitch, &maxHeight);

    offset = 0;
    if (cntMode == BSPUTILS_TILER_CNT_16BIT)
    {
        offset = BSPUTILS_TILER_CNT_8BIT_SIZE;
    }
    if (cntMode == BSPUTILS_TILER_CNT_32BIT)
    {
        offset = BSPUTILS_TILER_CNT_8BIT_SIZE + BSPUTILS_TILER_CNT_16BIT_SIZE;
    }

    tilerAddr = offset + ((startY * maxPitch) + startX);
    tilerAddr = BSPUTILS_TILER_PUT_CNT_MODE(tilerAddr, cntMode);

    if (gBspUtils_tilerObj.enableLog)
    {
        Bsp_printf(" [TILER] Tiler Addr = 0x%08x, mode = %d, x,y = %d,%d\r\n",
                   tilerAddr, cntMode, startX, startY);
    }

    return (tilerAddr);
}

UInt32 BspUtils_tilerGetOriAddr(UInt32 tilerAddr,
                                UInt32 cntMode,
                                UInt32 oriFlag,
                                UInt32 width,
                                UInt32 height)
{
    Uint32 elemSize;
    UInt32 oriAddr, tempOriFlag;
    UInt32 hOffset, vOffset;
    UInt32 hStride, vStride;
    UInt32 hElemOffset, vElemOffset;

    /* Get the base address without orientation and container modes */
    oriAddr  = tilerAddr;
    oriAddr &= ~((UInt32) 0x1FU << 27U);
    oriFlag &= (BSPUTILS_TILER_ORI_X_FLIP |
                BSPUTILS_TILER_ORI_Y_FLIP |
                BSPUTILS_TILER_ORI_XY_SWAP);

    /* Calculate the 0 degree (normal view) horizontal and vertical element
     * offsets */
    if (BSPUTILS_TILER_CNT_8BIT == cntMode)
    {
        elemSize     = 1U;
        hElemOffset  = oriAddr & (VPSUTILS_TILER_CNT_8BIT_PITCH - 1U);
        hElemOffset /= elemSize;
        vElemOffset  = (oriAddr / VPSUTILS_TILER_CNT_8BIT_PITCH);
    }
    else if (BSPUTILS_TILER_CNT_16BIT == cntMode)
    {
        elemSize     = 2U;
        hElemOffset  = oriAddr & (VPSUTILS_TILER_CNT_16BIT_PITCH - 1U);
        hElemOffset /= elemSize;
        vElemOffset  = (oriAddr / VPSUTILS_TILER_CNT_16BIT_PITCH);
    }
    else
    {
        elemSize     = 4U;
        hElemOffset  = oriAddr & (VPSUTILS_TILER_CNT_32BIT_PITCH - 1U);
        hElemOffset /= elemSize;
        vElemOffset  = (oriAddr / VPSUTILS_TILER_CNT_32BIT_PITCH);
    }

    /* Figure out horizontal stride and max lines as per container mode and
     * orientation flag - vStride below is the max number of lines. */
    if (oriFlag & BSPUTILS_TILER_ORI_XY_SWAP)
    {
        if (BSPUTILS_TILER_CNT_8BIT == cntMode)
        {
            hStride = VPSUTILS_TILER_CNT_8BIT_SWAP_PITCH;
            vStride = BSPUTILS_TILER_CNT_8BIT_SWAP_MAX_LINES;
        }
        else if (BSPUTILS_TILER_CNT_16BIT == cntMode)
        {
            hStride = VPSUTILS_TILER_CNT_16BIT_SWAP_PITCH;
            vStride = BSPUTILS_TILER_CNT_16BIT_SWAP_MAX_LINES;
        }
        else
        {
            hStride = VPSUTILS_TILER_CNT_32BIT_SWAP_PITCH;
            vStride = BSPUTILS_TILER_CNT_32BIT_SWAP_MAX_LINES;
        }
    }
    else
    {
        if (BSPUTILS_TILER_CNT_8BIT == cntMode)
        {
            hStride = VPSUTILS_TILER_CNT_8BIT_PITCH;
            vStride = BSPUTILS_TILER_CNT_8BIT_MAX_LINES;
        }
        else if (BSPUTILS_TILER_CNT_16BIT == cntMode)
        {
            hStride = VPSUTILS_TILER_CNT_16BIT_PITCH;
            vStride = BSPUTILS_TILER_CNT_16BIT_MAX_LINES;
        }
        else
        {
            hStride = VPSUTILS_TILER_CNT_32BIT_PITCH;
            vStride = BSPUTILS_TILER_CNT_32BIT_MAX_LINES;
        }
    }

    /* Store the orientation flag without swap flag */
    tempOriFlag = (oriFlag & (~((UInt32) BSPUTILS_TILER_ORI_XY_SWAP)));
    if (oriFlag & BSPUTILS_TILER_ORI_XY_SWAP)
    {
        /*
         * Since X and Y axes are swapped, vertical and horizontal names in
         * below calculations represents with respect to swapped axis.
         * That is vertical mean horizontal in normal view and horizontal means
         * vertical in normal view.
         */

        /* Horizontal line offset from start of line */
        hOffset = vElemOffset;
        /* Vertical offset in terms of lines */
        vOffset = hElemOffset;

        /* Calculate X' address */
        if (BSPUTILS_TILER_ORI_X_FLIP == tempOriFlag)
        {
            oriAddr  = (vStride - (vOffset + width)) * hStride;
            oriAddr += (hOffset * elemSize);
        }
        /* Calculate Y' address */
        else if (BSPUTILS_TILER_ORI_Y_FLIP == tempOriFlag)
        {
            oriAddr  = vOffset * hStride;
            oriAddr += (hStride - ((hOffset * elemSize) + height));
        }
        /* Calculate X' and Y' address */
        else if (tempOriFlag ==
                 (BSPUTILS_TILER_ORI_X_FLIP | BSPUTILS_TILER_ORI_Y_FLIP))
        {
            oriAddr  = (vStride - (vOffset + width)) * hStride;
            oriAddr += (hStride - ((hOffset * elemSize) + height));
        }
        /* Calculate normal view address */
        else
        {
            oriAddr = (vOffset * hStride) + (hOffset * elemSize);
        }
    }
    else
    {
        /* Horizontal line offset from start of line */
        hOffset = hElemOffset;
        /* Vertical offset in terms of lines */
        vOffset = vElemOffset;

        /* Calculate X' address */
        if (BSPUTILS_TILER_ORI_X_FLIP == tempOriFlag)
        {
            oriAddr  = vOffset * hStride;
            oriAddr += (hStride - ((hOffset * elemSize) + width));
        }
        /* Calculate Y' address */
        else if  (BSPUTILS_TILER_ORI_Y_FLIP == tempOriFlag)
        {
            oriAddr  = (vStride - (vOffset + height)) * hStride;
            oriAddr += (hOffset * elemSize);
        }
        /* Calculate X' and Y' address */
        else if (tempOriFlag ==
                 (BSPUTILS_TILER_ORI_X_FLIP | BSPUTILS_TILER_ORI_Y_FLIP))
        {
            oriAddr  = (vStride - (vOffset + height)) * hStride;
            oriAddr += (hStride - ((hOffset * elemSize) + width));
        }
        /* Calculate normal view address */
        else
        {
            oriAddr = (vOffset * hStride) + (hOffset * elemSize);
        }
    }

    /* Set the orientation modes */
    oriAddr &= ~BSPUTILS_TILER_ORI_MODE_MASK;
    oriAddr |= (oriFlag << BSPUTILS_TILER_ORI_MODE_SHIFT);

    /* Set the container mode */
    oriAddr = BSPUTILS_TILER_PUT_CNT_MODE(oriAddr, cntMode);

    return (oriAddr);
}

Int32 BspUtils_tilerFreeAll(void)
{
    UInt32 cntMode;

    GT_assert(GT_DEFAULT_MASK, (((Bool) TRUE) == gBspTilerInitDone));

    for (cntMode = 0; cntMode < BSPUTILS_TILER_CNT_MAX; cntMode++)
    {
        gBspUtils_tilerObj.curX[cntMode] = (UInt32) VPS_BUFFER_ALIGNMENT *
                                           2U;
        gBspUtils_tilerObj.curStartY[cntMode] = 0;
        gBspUtils_tilerObj.curEndY[cntMode]   = 0;
    }

    return (0);
}

UInt32 BspUtils_tilerAlloc(UInt32 cntMode, UInt32 width, UInt32 height)
{
    UInt32 tilerAddr = 0, curX, curStartY, curEndY, maxWidth, maxHeight;

    GT_assert(GT_DEFAULT_MASK, (((Bool) TRUE) == gBspTilerInitDone));

    width  = VpsUtils_align(width, (UInt32) VPS_BUFFER_ALIGNMENT * 2U);
    height = VpsUtils_align(height, (UInt32) 2U);

    curX      = gBspUtils_tilerObj.curX[cntMode];
    curStartY = gBspUtils_tilerObj.curStartY[cntMode];
    curEndY   = gBspUtils_tilerObj.curEndY[cntMode];

    BspUtils_tilerGetMaxPitchHeight(cntMode, &maxWidth, &maxHeight);

    if ((curX + width) > maxWidth)
    {
        curX      = 0;
        curStartY = curEndY;
    }

    if ((curStartY + height) <= maxHeight)
    {
        if ((curStartY + height) > curEndY)
        {
            curEndY = curStartY + height;
        }

        tilerAddr = BspUtils_tilerGetAddr(cntMode, curX, curStartY);

        curX += width;

        gBspUtils_tilerObj.curX[cntMode]      = curX;
        gBspUtils_tilerObj.curStartY[cntMode] = curStartY;
        gBspUtils_tilerObj.curEndY[cntMode]   = curEndY;
    }

    return (tilerAddr);
}

Int32 BspUtils_tilerFrameAlloc(Fvid2_Format *pFormat,
                               Fvid2_Frame  *pFrame,
                               UInt16        numFrames)
{
    UInt32 frameId;

    GT_assert(GT_DEFAULT_MASK, (((Bool) TRUE) == gBspTilerInitDone));

    /* align height to multiple of 2  */
    pFormat->height = VpsUtils_align(pFormat->height, (UInt32) 2U);

    for (frameId = 0; frameId < numFrames; frameId++)
    {
        /* init Fvid2_Frame to 0's  */
        BspUtils_memset(pFrame, 0, sizeof (*pFrame));

        /* copy chNum to Fvid2_Frame from Fvid2_Format */
        pFrame->chNum = pFormat->chNum;

        switch (pFormat->dataFormat)
        {
            case FVID2_DF_YUV422SP_UV:
                /* Y plane  */
                pFrame->addr[0][0] = (Ptr) BspUtils_tilerAlloc(
                    (UInt32) BSPUTILS_TILER_CNT_8BIT,
                    pFormat->width,
                    pFormat->height);

                /* C plane  */
                pFrame->addr[0][1] = (Ptr) BspUtils_tilerAlloc(
                    (UInt32) BSPUTILS_TILER_CNT_16BIT,
                    pFormat->width,
                    pFormat->height);
                break;

            case FVID2_DF_YUV420SP_UV:
                /* Y plane  */
                pFrame->addr[0][0] = (Ptr) BspUtils_tilerAlloc(
                    (UInt32) BSPUTILS_TILER_CNT_8BIT,
                    pFormat->width,
                    pFormat->height);
                /* C plane  */
                pFrame->addr[0][1] = (Ptr) BspUtils_tilerAlloc(
                    (UInt32) BSPUTILS_TILER_CNT_16BIT,
                    pFormat->width,
                    pFormat->height / (UInt32) 2U);
                break;

            default:
                GT_assert(GT_DEFAULT_MASK, 0);
                break;
        }

        pFrame++;
    }

    return (0);
}

Int32 BspUtils_tilerCopy(UInt32       dir,
                         UInt32       tilerAddr,
                         UInt32       dataWidth,
                         UInt32       dataHeight,
                         const UInt8 *ddrAddr,
                         UInt32       ddrPitch)
{
    UInt32 cntMode;
    UInt32 tilerCpuAddr, tilerPitch, tilerHeight;
    UInt32 inc;
    UInt32 dstAddrBase, dstAddr, dstPitch;
    UInt32 srcAddrBase, srcAddr, srcPitch;
    UInt32 h, w;

    GT_assert(GT_DEFAULT_MASK, (((Bool) TRUE) == gBspTilerInitDone));

    cntMode      = BspUtils_getCntMode(tilerAddr);
    tilerCpuAddr = BspUtils_tilerAddr2CpuAddr(tilerAddr);

    BspUtils_tilerGetMaxPitchHeight(cntMode, &tilerPitch, &tilerHeight);

    inc = (UInt32) 1U << cntMode;

    if (dir == BSPUTILS_TILER_COPY_TO_DDR)
    {
        dstAddrBase = (UInt32) ddrAddr;
        dstPitch    = ddrPitch;
        srcAddrBase = tilerCpuAddr;
        srcPitch    = tilerPitch;
    }
    else
    {
        srcAddrBase = (UInt32) ddrAddr;
        srcPitch    = ddrPitch;
        dstAddrBase = tilerCpuAddr;
        dstPitch    = tilerPitch;
    }

    for (h = 0; h < dataHeight; h++)
    {
        dstAddr = dstAddrBase;
        srcAddr = srcAddrBase;

        switch (cntMode)
        {
            case BSPUTILS_TILER_CNT_8BIT:
                for (w = 0; w < dataWidth; w += inc)
                {
                    *(volatile UInt8 *) dstAddr = *(volatile UInt8 *) srcAddr;
                    dstAddr += inc;
                    srcAddr += inc;
                }
                break;

            case BSPUTILS_TILER_CNT_16BIT:
                for (w = 0; w < dataWidth; w += inc)
                {
                    *(volatile UInt16 *) dstAddr = *(volatile UInt16 *) srcAddr;
                    dstAddr += inc;
                    srcAddr += inc;
                }
                break;

            case BSPUTILS_TILER_CNT_32BIT:
                for (w = 0; w < dataWidth; w += inc)
                {
                    *(volatile UInt32 *) dstAddr = *(volatile UInt32 *) srcAddr;
                    dstAddr += inc;
                    srcAddr += inc;
                }
                break;

            default:
                GT_assert(GT_DEFAULT_MASK, 0);
                break;
        }

        dstAddrBase += dstPitch;
        srcAddrBase += srcPitch;
    }

    return (0);
}

