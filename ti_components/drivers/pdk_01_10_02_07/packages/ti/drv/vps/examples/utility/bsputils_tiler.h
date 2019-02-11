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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_TILER_API Tiler allocator API
 *  @{
 */

/**
 *  \file bsputils_tiler.h
 *
 *  \brief Tiler allocator API
 */

#ifndef BSPUTILS_TILER_H_
#define BSPUTILS_TILER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Tiler CPU virtual address */
#define BSPUTILS_TILER_CPU_VIRT_ADDR    (0x60000000U)

/** \brief Tiler physical memory size */
#define BSPUTILS_TILER_PHYS_MEM_SIZE    (128U * MB)

/** \brief Indicates 8-bit tiled */
#define BSPUTILS_TILER_CNT_8BIT         (0U)
/** \brief Indicates 16-bit tiled */
#define BSPUTILS_TILER_CNT_16BIT        (1U)
/** \brief Indicates 32-bit tiled */
#define BSPUTILS_TILER_CNT_32BIT        (2U)
/** \brief Indicates number of tiled types (8-bit/16-bit/32-bit)  */
#define BSPUTILS_TILER_CNT_MAX          (3U)

/** \brief Indicates direction -- copy to DDR */
#define BSPUTILS_TILER_COPY_TO_DDR      (0U)
/** \brief Indicates direction -- copy from DDR */
#define BSPUTILS_TILER_COPY_FROM_DDR    (1U)

/** \brief Indicates normal orientation */
#define BSPUTILS_TILER_ORI_NONE         (0x00U)
/** \brief Indicates horizontal-flipped orientation */
#define BSPUTILS_TILER_ORI_X_FLIP       (0x01U)
/** \brief Indicates vertical-flipped orientation */
#define BSPUTILS_TILER_ORI_Y_FLIP       (0x02U)
/** \brief Indicates horizontal and vertical flipped orientation */
#define BSPUTILS_TILER_ORI_XY_SWAP      (0x04U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initialize the tiler
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tilerInit(void);

/**
 *  \brief De-initialize the tiler
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tilerDeInit(void);

/**
 *  \brief Enable/disable debug log for tiler APIs
 *
 *  \param enable       [IN] Indicates whether the debug log is to be enabled
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tilerDebugLogEnable(UInt32 enable);

/**
 *  \brief Alloc from tiler space.
 *
 *  Value can be passed directly to VPDMA
 *
 *  \param cntMode      [IN] container mode
 *  \param width        [IN] width in BYTES
 *  \param height       [IN] height in lines
 *
 *  \return Tiler address
 */
UInt32 BspUtils_tilerAlloc(UInt32 cntMode, UInt32 width, UInt32 height);

/**
 *  \brief Free all previously allocated tiler frames
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tilerFreeAll(void);

/**
 *  \brief Convert tilerAddr to CPU addr
 *
 *  \param tilerAddr    [IN] address got via BspUtils_tilerAlloc
 *
 *  \return CPU virtual address
 */
UInt32 BspUtils_tilerAddr2CpuAddr(UInt32 tilerAddr);

/**
 *  \brief Allocate a frame in tiler space
 *
 *  Use FVID2_Format to allocate a frame.
 *  Fill FVID2_Frame fields like channelNum based on Fvid2_Format
 *
 *  \param  pFormat     [IN] Data format information
 *  \param  pFrame      [OUT] Initialzed Fvid2_Frame structure
 *  \param  numFrames   [IN] Number of frames to allocate
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_tilerFrameAlloc(Fvid2_Format *pFormat,
                               Fvid2_Frame  *pFrame,
                               UInt16        numFrames);

/**
 *  \brief Copy between tiler Address space and non-tiler DDR address
 *
 *  This API internally converts tilerAddr to cpuAddr
 *
 *  \param dir          [IN] BSPUTILS_TILER_COPY_TO_DDR or
 *                           BSPUTILS_TILER_COPY_FROM_DDR
 *  \param tilerAddr    [IN] tiler address returned during BspUtils_tilerAlloc()
 *                           or BspUtils_tilerGetAddr()
 *  \param dataWidth    [IN] data width in bytes
 *  \param dataHeight   [IN] data height in lines
 *  \param ddrAddr      [IN] Non tiled DDR address
 *  \param ddrPitch     [IN] Pitch to be used for data in non-tiled space
 *                           in bytes
 *
 *  \return FVID2_SOK on sucess, else failure
 */
Int32 BspUtils_tilerCopy(UInt32       dir,
                         UInt32       tilerAddr,
                         UInt32       dataWidth,
                         UInt32       dataHeight,
                         const UInt8 *ddrAddr,
                         UInt32       ddrPitch);

/**
 *  \brief Get tiler Address
 *
 *  \param cntMode      [IN] container mode
 *  \param startX       [IN] X-coordinate in BYTES
 *  \param startY       [IN] Y-coordinate in LINES
 *
 *  \return tiler address
 */
UInt32 BspUtils_tilerGetAddr(UInt32 cntMode, UInt32 startX, UInt32 startY);

/**
 *  \brief Get tiler address after applying the orientation.
 *
 *  \param tilerAddr    [IN] 0 degree tiler address returned during
 *                           BspUtils_tilerAlloc().
 *  \param cntMode      [IN] Container mode.
 *  \param oriFlag      [IN] Orientation flag representing S, Y', X' bits
 *  \param width        [IN] 0 degree buffer width.
 *  \param height       [IN] 0 degree buffer height.
 *
 *  \return Tiler address after applying the necessary orientation.
 */
UInt32 BspUtils_tilerGetOriAddr(UInt32 tilerAddr,
                                UInt32 cntMode,
                                UInt32 oriFlag,
                                UInt32 width,
                                UInt32 height);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_TILER_H_ */

/* @} */
