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
 *  \addtogroup BSP_DRV_VPS_COMMON_DATATYPES
 *
 *  @{
 */

/**
 *  \file vps_dataTypes.h
 *
 *  \brief VPS - Common API datatypes
 */

#ifndef VPS_DATATYPES_H_
#define VPS_DATATYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

/* ========================================================================== */
/* Include HW specific config constants, structures                           */
/* ========================================================================== */

#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
#include <ti/drv/vps/include/vps_cfgSc.h>
#include <ti/drv/vps/include/vps_cfgCsc.h>
#endif
#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/include/vpe/vps_cfgDei.h>
#endif
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vip/vps_cfgVipParser.h>
#endif
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#endif
#ifdef VPS_SIMCOP_BUILD
#include <ti/drv/vps/include/iss/vps_cfgsimcop.h>
#include <ti/drv/vps/include/iss/vps_cfgldc.h>
#include <ti/drv/vps/include/iss/vps_cfgvtnf.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief VPS video buffer alignment. All application buffer address and
 *  line pitch should be aligned to this byte boundary.
 */
#define VPS_BUFFER_ALIGNMENT            (16U)

/**
 *  \brief Recommended VPS video buffer alignment for better DDR efficiency.
 *
 *  All application buffer address and line pitch could be aligned to this
 *  byte boundary to achieve better DDR efficiency because accesses split
 *  across 32 byte boundary would require 2 DDR burst accesses with burst
 *  chopping.
 */
#define VPS_BUFFER_ALIGNMENT_RECOMMENDED    (32U)

/** \brief Capture maximum MAX_SIZE registers in VPDMA. */
#define VPS_VPDMA_NUM_MAXSIZE_REG       (3U)

/** \brief 8-bit Tiler container pitch in bytes. */
#define VPSUTILS_TILER_CNT_8BIT_PITCH   (16U * 1024U)

/** \brief 16-bit Tiler container pitch in bytes. */
#define VPSUTILS_TILER_CNT_16BIT_PITCH  (32U * 1024U)

/** \brief 32-bit Tiler container pitch in bytes. */
#define VPSUTILS_TILER_CNT_32BIT_PITCH  (32U * 1024U)

/** \brief 8-bit Tiler container pitch in bytes when X/Y axis is swapped. */
#define VPSUTILS_TILER_CNT_8BIT_SWAP_PITCH  (8U * 1024U)

/** \brief 16-bit Tiler container pitch in bytes when X/Y axis is swapped. */
#define VPSUTILS_TILER_CNT_16BIT_SWAP_PITCH (8U * 1024U)

/** \brief 32-bit Tiler container pitch in bytes when X/Y axis is swapped. */
#define VPSUTILS_TILER_CNT_32BIT_SWAP_PITCH (16U * 1024U)

/**
 *  enum Vps_VpdmaMemoryType
 *  \brief Enum for buffer memory type.
 */
typedef enum
{
    VPS_VPDMA_MT_NONTILEDMEM = 0,
    /**< 1D non-tiled memory. */
    VPS_VPDMA_MT_TILEDMEM,
    /**< 2D tiled memory. */
    VPS_VPDMA_MT_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_VpdmaMemoryType;

/**
 *  enum Vps_MemRotationType
 *  \brief This enum is used to define the memory data rotation and mirroring
 *  type. The rotation and mirroring is only valid if the memory type is tiler
 *  container mode. For non-tiler and tiler page mode, rotation and mirroring
 *  is not valid
 */
typedef enum
{
    VPS_MEM_0_ROTATION = 0,
    /**< no rotation and mirroring. */
    VPS_MEM_180_ROTATION_MIRRORING,
    /**< 180 degree rotation with mirroring. */
    VPS_MEM_0_ROTATION_MIRRORING,
    /**< 0 degree rotation with mirroring. */
    VPS_MEM_180_ROTATION,
    /**< 180 degree rotation. */
    VPS_MEM_270_ROTATION_MIRRORING,
    /**< 270 degree rotation with mirroring. */
    VPS_MEM_270_ROTATION,
    /**< 270 degree rotation. */
    VPS_MEM_90_ROTATION,
    /**< 90 degree rotation. */
    VPS_MEM_90_ROTATION_MIRRORING,
    /**< 90 degree rotation with mirroring. */
    VPS_MEM_ROTATION_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_MemRotationType;

/**
 *  enum Vps_RngMapVal
 *  \brief Enumerations for Range Mapping Values.
 */
typedef enum
{
    VPS_RNG_MAP_VAL_0 = 0,
    /**< Range Mapping Value 0 */
    VPS_RNG_MAP_VAL_1,
    /**< Range Mapping Value 2 */
    VPS_RNG_MAP_VAL_2,
    /**< Range Mapping Value 2 */
    VPS_RNG_MAP_VAL_3,
    /**< Range Mapping Value 3 */
    VPS_RNG_MAP_VAL_4,
    /**< Range Mapping Value 4 */
    VPS_RNG_MAP_VAL_5,
    /**< Range Mapping Value 5 */
    VPS_RNG_MAP_VAL_6,
    /**< Range Mapping Value 6 */
    VPS_RNG_MAP_VAL_7
    /**< Range Mapping Value 7 */
} Vps_RngMapVal;

/**
 *  \brief Output data max width.
 *
 *  This enum can be used to limit the width of the output data that is
 *  captured in to the user buffer.
 *
 *  Any additional pixels coming from the source are discarded.
 */
typedef enum
{
    VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED = 0,
    /**< Do not limit the output width, captured whatever is coming from
     *   the source. */
    VPS_VPDMA_MAX_OUT_WIDTH_REG1 = 1,
    /**< Maximum width per line as mentioned in
     *   Max Size Register 1 */
    VPS_VPDMA_MAX_OUT_WIDTH_REG2 = 2,
    /**< Maximum width per line as mentioned in
     *   Max Size Register 2 */
    VPS_VPDMA_MAX_OUT_WIDTH_REG3 = 3,
    /**< Maximum width per line as mentioned in
     *   Max Size Register 3 */
    VPS_VPDMA_MAX_OUT_WIDTH_352_PIXELS = 4,
    /**< Limit height to 352 pixels. */
    VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS = 5,
    /**< Limit height to 768 pixels. */
    VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS = 6,
    /**< Limit height to 1280 pixels. */
    VPS_VPDMA_MAX_OUT_WIDTH_1920_PIXELS = 7
                                          /**< Limit height to 1920 pixels. */
} Vps_VpdmaMaxOutWidth;

/**
 *  \brief Output data max height.
 *
 *  This enum can be used to limit the height of the output data that is
 *  captured in to the user buffer.
 *
 *  By default HW will capture whatever active data comes from the external
 *  video source. The width typically remains fixed from the external source.
 *  However,  in some cases external video sources may generate spurious
 *  frames of active data which have random height. This can cause user
 *  buffers to overflow if the height of such a frame is more that the
 *  allocated buffer height.
 *
 *  To avoid such buffer overflow, users should limit the maximum output
 *  data height.
 *  This a HW feature and limits that can be set are a few fixed values
 *  as shown below.
 *
 *  Any additional lines coming from the source are discarded.
 */
typedef enum
{
    VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED = 0,
    /**< Do not limit the output width, captured whatever is coming from
     *   the source. */
    VPS_VPDMA_MAX_OUT_HEIGHT_REG1 = 1,
    /**< Maximum height per line as mentioned in
     *   Max Size Register 1 */
    VPS_VPDMA_MAX_OUT_HEIGHT_REG2 = 2,
    /**< Maximum height per line as mentioned in
     *   Max Size Register 2 */
    VPS_VPDMA_MAX_OUT_HEIGHT_REG3 = 3,
    /**< Maximum height per line as mentioned in
     *   Max Size Register 3 */
    VPS_VPDMA_MAX_OUT_HEIGHT_288_LINES = 4,
    /**< Limit height to 288 lines. */
    VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES = 5,
    /**< Limit height to 576 lines. */
    VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES = 6,
    /**< Limit height to 720 lines. */
    VPS_VPDMA_MAX_OUT_HEIGHT_1080_LINES = 7
                                          /**< Limit height to 1080 lines. */
} Vps_VpdmaMaxOutHeight;

/**
 *  enum Vps_VpdmaClientIntrMode
 *  \brief This provide different modes of sub-frame client interrupts
 */
typedef enum
{
    VPS_INTR_END_OF_NTH_LINE,
    /**< Interrupt will be generated at the end of Nth Line.
     *   Only one client interrupt per frame. */
    VPS_INTR_END_OF_EVERY_NTH_LINE
    /**< Interrupt will be generated at the end of every Nth Line.
     *   Number of client interrupts per frame =
     *      floor(Number of lines/N)
     *                 ;When (Number of lines) == Non Integer multiple of N
     *      (Number of lines/N) - 1
     *                 ;When (Number of lines) == Integer multiple of N */
} Vps_VpdmaClientIntrMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * struct Vps_FrameParams
 * \brief Structure for setting the frame parameters like frame height, width,
 * pitch and memory type.
 */
typedef struct
{
    UInt32 width;
    /**< Width of frame in pixels. */
    UInt32 height;
    /**< Height of frame in lines. */
    UInt32 pitch[FVID2_MAX_PLANES];
    /**< Pitch for each planes in bytes. Only required planes needs to be
     *   populated. */
    UInt32 memType;
    /**< VPDMA memory type - Tiled buffer or normal non-tiled buffer.
     *   For valid values see #Vps_VpdmaMemoryType. */
    UInt32 dataFormat;
    /**< Frame data Format. For valid values see #Fvid2_DataFormat. */
} Vps_FrameParams;

/**
 *  struct Vps_WinFormat
 *  \brief Structure for setting the mosaic or region based graphic
 *  window for each of the window.
 */
typedef struct
{
    UInt32 winStartX;
    /**< Horizontal offset in pixel (with respect to frame dimension)
     *   from which window starts. */
    UInt32 winStartY;
    /**< Vertical offset in line (with respect to frame dimension)
     *   from which window starts. */
    UInt32 winWidth;
    /**< Width of window in pixels. */
    UInt32 winHeight;
    /**< Number of lines in a window. For interlaced mode, this should
     *   be set to the frame size and not the field size. */
    UInt32 pitch[FVID2_MAX_PLANES];
    /**< Pitch in bytes for each of the sub-window buffers. This represents the
     *   difference between two consecutive line address.
     *   This is irrespective of whether the video is interlaced or
     *   progressive and whether the fields are merged or separated for
     *   interlaced video. */
    UInt32 dataFormat;
    /**< Data format for each window. For valid values see #Fvid2_DataFormat.
     *   Caution: Check the respective driver user/API guide for the
     *   data formats supported. Some driver may not support
     *   separate data formats for each window of the frame. */
    UInt32 bpp;
    /**< Bits per pixels for each window.
     *   For valid values see #Fvid2_BitsPerPixel. */
    UInt32 priority;
    /**< In case of overlapping windows (as in PIP), priority could be used
     *   to choose the window to be displayed in the overlapped region.
     *   0 is highest priority, 1 is next and so on...
     *   Note that keeping same priority for all windows specifies that there
     *   are no overlapping windows. */
} Vps_WinFormat;

/**
 *  struct Vps_MultiWinParams
 *  \brief Structure for setting multiple window (mosaic/region based graphics)
 *  parameters.
 */
typedef struct
{
    UInt32               chNum;
    /**< Channel number to which this this config belongs to.
     *   This is used in case of multiple buffers queuing/deqeuing using a
     *   single call.
     *   If only one channel is supported, then this should be set to 0. */
    UInt32               numWin;
    /**< Specifies the number windows that would require to be
     *   displayed/processed, winFmt should point to a array that has at least
     *   numWin of entries. */
    const Vps_WinFormat *winFmt;
    /**< Pointer to an array of multiple window format containing the format
     *   for each of the mosaic or region based graphics window.
     *   The format array should be filled from left to right and from top to
     *   bottom for all the windows.
     *   The size of the array should be equal to total number of windows
     *   and the memory should be allocated by the application. */
} Vps_MultiWinParams;

/**
 *  struct Vps_LayoutId
 *  \brief Structure for returning the layout ID in create/select/delete
 *  multiple window (mosaic/region based graphics) layout IOCTLs.
 */
typedef struct
{
    UInt32 layoutId;
    /**< Layout ID as assigned by driver. This should be used as a reference
     *   by the application to select/delete the required layout.
     *   Note: Each driver could have different layout ID for a particular
     *   layout. */
} Vps_LayoutId;

/**
 *  struct Vps_RngMapRdtCfg
 *  \brief Structure used to disable or enable the range mapping and range
 *         reduction feature and also it defines the range mapping values for
 *         Y and UV component
 */
typedef struct
{
    UInt32 rngRdtEnable;
    /**< [IN] Defines whether to enable or disable the range
     *   reduction feature. */
    UInt32 rngMapEnable;
    /**< [IN] Defines whether to enable or disable the range
     *   mapping feature. */
    UInt32 rngMapValY;
    /**< [IN] Defines the range mapping value for Y component
     *        For valid values see #Vps_RngMapVal. */
    UInt32 rngMapValUV;
    /**< [IN] Defines the range mapping value for UV component
     *        For valid values see #Vps_RngMapVal. */
} Vps_RngMapRdtCfg;

/**
 *  \brief Capture Max Size information.
 *
 *         The Max Frame Logic has 8 possible settings for both
 *         width and height. The settings are 4 fixed constrained values
 *         which are for typical video standards, 3 programmable values
 *         and an unconstrained setting. The 3 programmable values are set
 *         in the max_size1, max_size2, max_size3 registers.
 *         The descriptor then selects one of the values to constrain the
 *         transmitted frame.
 */
typedef struct
{
    UInt32 instId;
    /**<
     *   instId:
     *   Instance Id determines VIP1, VIP2, VIP3 or VPE
     *   is in use. */
    UInt32 maxOutWidth[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxWidth:
     *   Maximum Width of the frame/field that shall be transmitted to the
     *   external buffer. If the captured width received exceeds this then
     *   only maxWidth number of pixels per line is transmitted to the
     *   external buffer. */
    UInt32 maxOutHeight[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxHeight:
     *   Maximum Height of the frame/field  that shall be transmitted to the
     *   external buffer. If the captured height received exceeds this then
     *   only maxHeight number of lines is transmitted to the external buffer.
     */
} Vps_VpdmaMaxSizeParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_FrameParams structure init function.
 *
 *  \param frmPrms      [IN] Pointer to #Vps_FrameParams structure.
 *
 */
static inline void VpsFrameParams_init(Vps_FrameParams *frmPrms);

/**
 *  \brief Vps_WinFormat structure init function.
 *
 *  \param winFmt       [IN] Pointer to #Vps_WinFormat structure.
 *
 */
static inline void VpsWinFormat_init(Vps_WinFormat *winFmt);

/**
 *  \brief Vps_MultiWinParams structure init function.
 *
 *  \param multiWinPrms [IN] Pointer to #Vps_MultiWinParams structure.
 *
 */
static inline void VpsMultiWinParams_init(Vps_MultiWinParams *multiWinPrms);

/**
 *  \brief Vps_LayoutId structure init function.
 *
 *  \param layoutId     [IN] Pointer to #Vps_LayoutId structure.
 *
 */
static inline void VpsLayoutId_init(Vps_LayoutId *layoutId);

/**
 *  \brief Vps_RngMapRdtCfg structure init function.
 *
 *  \param rngMapCfg    [IN] Pointer to #Vps_RngMapRdtCfg structure.
 *
 */
static inline void VpsRngMapRdtCfg_init(Vps_RngMapRdtCfg *rngMapCfg);

/**
 *  \brief Vps_VpdmaMaxSizeParams structure init function.
 *
 *  \param maxPrms      [IN] Pointer to #Vps_VpdmaMaxSizeParams structure.
 *
 */
static inline void VpsVpdmaMaxSizeParams_init(Vps_VpdmaMaxSizeParams *maxPrms);

/**
 *  \brief Floor a integer value.
 *
 *  \param val          [IN] Integer to floor.
 *  \param align        [IN] Alignement.
 *
 *  \return Returns the floored integer.
 */
static inline UInt32 VpsUtils_floor(UInt32 val, UInt32 align);

/**
 *  \brief Align a integer value.
 *
 *  \param val          [IN] Integer to align.
 *  \param align        [IN] Alignement.
 *
 *  \return Returns the aligned integer.
 */
static inline UInt32 VpsUtils_align(UInt32 val, UInt32 align);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsFrameParams_init(Vps_FrameParams *frmPrms)
{
    UInt32 i;

    if (NULL != frmPrms)
    {
        frmPrms->width  = 0U;
        frmPrms->height = 0U;
        for (i = 0; i < FVID2_MAX_PLANES; i++)
        {
            frmPrms->pitch[i] = 0U;
        }
        frmPrms->memType    = VPS_VPDMA_MT_NONTILEDMEM;
        frmPrms->dataFormat = FVID2_DF_YUV422I_YUYV;
    }

    return;
}

static inline void VpsWinFormat_init(Vps_WinFormat *winFmt)
{
    UInt32 i;

    if (NULL != winFmt)
    {
        winFmt->winStartX = 0U;
        winFmt->winStartY = 0U;
        winFmt->winWidth  = 0U;
        winFmt->winHeight = 0U;
        for (i = 0; i < FVID2_MAX_PLANES; i++)
        {
            winFmt->pitch[i] = 0U;
        }
        winFmt->dataFormat = FVID2_DF_YUV422I_YUYV;
        winFmt->bpp        = FVID2_BPP_BITS16;
        winFmt->priority   = 0U;
    }

    return;
}

static inline void VpsMultiWinParams_init(Vps_MultiWinParams *multiWinPrms)
{
    if (NULL != multiWinPrms)
    {
        multiWinPrms->chNum  = 0U;
        multiWinPrms->numWin = 0U;
        multiWinPrms->winFmt = NULL;
    }

    return;
}

static inline void VpsLayoutId_init(Vps_LayoutId *layoutId)
{
    if (NULL != layoutId)
    {
        layoutId->layoutId = 0U;
    }

    return;
}

static inline void VpsRngMapRdtCfg_init(Vps_RngMapRdtCfg *rngMapCfg)
{
    if (NULL != rngMapCfg)
    {
        rngMapCfg->rngRdtEnable = (UInt32) FALSE;
        rngMapCfg->rngMapEnable = (UInt32) FALSE;
        rngMapCfg->rngMapValY   = 0U;
        rngMapCfg->rngMapValUV  = 0U;
    }

    return;
}

static inline void VpsVpdmaMaxSizeParams_init(Vps_VpdmaMaxSizeParams *maxPrms)
{
    UInt32 i;

    if (NULL != maxPrms)
    {
        maxPrms->instId = 0U;
        for (i = 0; i < VPS_VPDMA_NUM_MAXSIZE_REG; i++)
        {
            maxPrms->maxOutWidth[i]  = 0U;
            maxPrms->maxOutHeight[i] = 0U;
        }
    }

    return;
}

static inline UInt32 VpsUtils_floor(UInt32 val, UInt32 align)
{
    return ((UInt32) ((val / align) * align));
}

static inline UInt32 VpsUtils_align(UInt32 val, UInt32 align)
{
    return (VpsUtils_floor((UInt32) (val + (align - 1U)), align));
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_DATATYPES_H_ */

/* @} */

