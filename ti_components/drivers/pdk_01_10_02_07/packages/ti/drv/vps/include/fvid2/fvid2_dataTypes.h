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
 *  \file fvid2_dataTypes.h
 *
 *  \brief FVID2 API
 */

/*
 *  \author  BSP, TI
 *
 *  \version 0.1    Splitting fvid2.h into two files. fvid2_dataTypes.h will
 *                  contain only data-types which can be used independent of
 *                  the FVID2 driver layer
 *
 */

#ifndef FVID2_DATATYPES_H_
#define FVID2_DATATYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/tistdtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name FVID2 Error Codes
 *
 *  Error codes returned by FVID2 APIs
 *
 *  @{
 */

/** \brief FVID2 API call successful. */
#define FVID2_SOK                       ((Int32) 0)

/** \brief FVID2 API call returned with error as failed. Used for generic error.
 *  It may be some hardware failure and/or software failure. */
#define FVID2_EFAIL                     (-(Int32) 1)

/** \brief FVID2 API call returned with error as bad arguments.
 *  Typically, NULL pointer passed to the FVID2 API where its not expected. */
#define FVID2_EBADARGS                  (-(Int32) 2)

/** \brief FVID2 API call returned with error as invalid parameters. Typically
 *  when parameters passed are not valid or out of range. */
#define FVID2_EINVALID_PARAMS           (-(Int32) 3)

/** \brief FVID2 API call returned with error as device already in use. Example,
 *  tried to open the driver maximum + 1 times. Display and Capture driver
 *  supports single open only, while M2M driver supports multiple open. */
#define FVID2_EDEVICE_INUSE             (-(Int32) 4)

/** \brief FVID2 API call returned with error as timed out. Typically API is
 *  waiting for some condition and returned as condition not happened
 *  in the timeout period. */
#define FVID2_ETIMEOUT                  (-(Int32) 5)

/** \brief FVID2 API call returned with error as allocation failure. Typically
 *  memory or resource allocation failure. */
#define FVID2_EALLOC                    (-(Int32) 6)

/** \brief FVID2 API call returned with error as out of range. Typically when
 *  API is called with some argument that is out of range for that API like
 *  array index etc. */
#define FVID2_EOUT_OF_RANGE             (-(Int32) 7)

/** \brief FVID2 API call returned with error as try again. Momentarily API is
 *  not able to service request because of queue full or any other temporary
 *  reason. */
#define FVID2_EAGAIN                    (-(Int32) 8)

/** \brief FVID2 API call returned with unsupported command. Typically when
 *  command is not supported by control API. */
#define FVID2_EUNSUPPORTED_CMD          (-(Int32) 9)

/** \brief FVID2 API call returned with error as no more buffers available.
 *  Typically when no buffers are available. */
#define FVID2_ENO_MORE_BUFFERS          (-(Int32) 10)

/** \brief FVID2 API call returned with error as unsupported operation.
 *  Typically when the specific operation is not supported by that API such
 *  as IOCTL not supporting some specific functions. */
#define FVID2_EUNSUPPORTED_OPS          (-(Int32) 11)

/** \brief FVID2 API call returned with error as driver already in use. */
#define FVID2_EDRIVER_INUSE             (-(Int32) 12)

/** \brief FVID2 API call returned with warning for non-recommended parameter
 *  settings sent by application. Application may choose to ignore this. */
#define FVID2_WNON_RECOMMENDED_PARAMS   (-(Int32) 13)

/** \brief FVID2 API call returned with error as no device present for
 * the given command and API. */
#define FVID2_ENO_DEVICE                (-(Int32) 14)

/* @} */

/**
 *  \name FVID2 Max limits -- TODO
 *  @{
 */

/**
 *  \brief This macro determines the maximum number of FVID2 frame pointers
 *  that can be passed per frame list.
 */
#define FVID2_MAX_FRAME_PTR             (64U)

/**
 *  \brief This macro determines the maximum number of planes/address used to
 *  represent a video buffer per field. Currently this is set to 3 to support
 *  the maximum pointers required for YUV planar format - Y, Cb and Cr.
 */
#define FVID2_MAX_PLANES                (3U)

/**
 *  \brief Number of fields - top and bottom. Used for allocating address
 *  pointers for both the fields.
 */
#define FVID2_MAX_FIELDS                (2U)

/* @} */

/** \brief No Timeout. */
#define FVID2_TIMEOUT_NONE              (0U)

/** \brief Timeout wait forever. */
#define FVID2_TIMEOUT_FOREVER           (~((UInt32) 0U))

/**
 *  \name FVID2 Frame Address Index
 *
 *  Fvid2_Frame.addr structure is a 2D array of pointers.
 *  The below indices are used to identify the correct buffer address
 *  corresponding to the field and buffer formats.
 */

/* @{ */

/** \brief Index for top field address in case of interlaced frame mode. */
#define FVID2_FIELD_TOP_ADDR_IDX        (0U)

/** \brief Index for bottom field address in case of interlaced frame mode. */
#define FVID2_FIELD_BOTTOM_ADDR_IDX     (1U)

/** \brief Index for frame address in case of progressive mode. */
#define FVID2_FRAME_ADDR_IDX            (0U)

/** \brief Index for field mode address index. This is used in case of field
 *  mode of operation as in field capture or in deinterlacing mode of
 *  operation. In these cases both the top and bottom field index is one and
 *  the same. */
#define FVID2_FIELD_MODE_ADDR_IDX       (0U)

/** \brief Index for frame address in case of progressive mode. */
#define FVID2_FIELD_NONE_ADDR_IDX       (FVID2_FRAME_ADDR_IDX)

/** \brief Index for YUV444/YUV422 interleaved formats. */
#define FVID2_YUV_INT_ADDR_IDX          (0U)

/** \brief Y Index for YUV444/YUV422/YUV420 planar formats. */
#define FVID2_YUV_PL_Y_ADDR_IDX         (0U)

/** \brief CB Index for YUV444/YUV422/YUV420 planar formats. */
#define FVID2_YUV_PL_CB_ADDR_IDX        (1U)

/** \brief CR Index for YUV444/YUV422/YUV420 planar formats. */
#define FVID2_YUV_PL_CR_ADDR_IDX        (2U)

/** \brief Y Index for YUV semi planar formats. */
#define FVID2_YUV_SP_Y_ADDR_IDX         (0U)

/** \brief CB Index for semi planar formats. */
#define FVID2_YUV_SP_CBCR_ADDR_IDX      (1U)

/** \brief Index for RGB888/RGB565/ARGB32 formats. */
#define FVID2_RGB_ADDR_IDX              (0U)

/** \brief Index for RAW formats. */
#define FVID2_RAW_ADDR_IDX              (0U)

/** \brief Index for generic formats containing only one plane. */
#define FVID2_GENERIC_ADDR_IDX          (0U)

/** \brief No Field. */
#define FVID2_FID_NONE                  (FVID2_FID_FRAME)

/* @} */

/**
 *  \brief Video Data format.
 *   Naming convention followed
 *   FVID2_DF_ARGB32_8888
 *   In 8-bit byte memory
 *   B0       B1       B2        B3       B4       B5       B6      B7
 * ==========================================================================
 * |  A    |  R     | G      |  B     |    A  |    R    |    G   |   B   |
 * ==========================================================================
 *
 *   FVID2_DF_YUV422I_UYVY
 *   B0      B1       B2        B3        B4        B5        B6       B7
 * =========================================================================
 * |  U    |  Y     | V      |  Y       |  U     |  Y      |  V     |   Y   |
 * =========================================================================
 *
 *   FVID2_DF_ARGB16_4444
 *   B0      B1       B2        B3        B4        B5        B6      B7
 * ======================================================================
 * |  AR   |  GB   | AR    |   GB     |   AR   |    GB   |    AR  |   GB |
 * ======================================================================
 *
 */
typedef enum
{
    FVID2_DF_YUV422I_UYVY = 0x0000,
    /**< YUV 422 Interleaved format - UYVY. */
    FVID2_DF_YUV422I_YUYV = 0x0001,
    /**< YUV 422 Interleaved format - YUYV. */
    FVID2_DF_YUV422I_YVYU = 0x0002,
    /**< YUV 422 Interleaved format - YVYU. */
    FVID2_DF_YUV422I_VYUY = 0x0003,
    /**< YUV 422 Interleaved format - VYUY. */
    FVID2_DF_YUV422SP_UV = 0x0004,
    /**< YUV 422 Semi-Planar - Y separate, UV interleaved. */
    FVID2_DF_YUV422SP_VU = 0x0005,
    /**< YUV 422 Semi-Planar - Y separate, VU interleaved. */
    FVID2_DF_YUV422P = 0x0006,
    /**< YUV 422 Planar - Y, U and V separate. */
    FVID2_DF_YUV420SP_UV = 0x0007,
    /**< YUV 420 Semi-Planar - Y separate, UV interleaved. */
    FVID2_DF_YUV420SP_VU = 0x0008,
    /**< YUV 420 Semi-Planar - Y separate, VU interleaved. */
    FVID2_DF_YUV420P = 0x0009,
    /**< YUV 420 Planar - Y, U and V separate. */
    FVID2_DF_YUV444P = 0x000A,
    /**< YUV 444 Planar - Y, U and V separate. */
    FVID2_DF_YUV444I = 0x000B,
    /**< YUV 444 interleaved - YUVYUV... */
    FVID2_DF_RGB16_565 = 0x000C,
    /**< RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B. */
    FVID2_DF_ARGB16_1555 = 0x000D,
    /**< ARGB1555 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha . */
    FVID2_DF_RGBA16_5551 = 0x000E,
    /**< RGBA5551 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha  . */
    FVID2_DF_ARGB16_4444 = 0x000F,
    /**< ARGB4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha . */
    FVID2_DF_RGBA16_4444 = 0x0010,
    /**< RGBA4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha  . */
    FVID2_DF_RGBX16_4444 = 0x0011,
    /**< RGBX4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Unused  . */
    FVID2_DF_ARGB24_6666 = 0x0012,
    /**< ARGB6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha . */
    FVID2_DF_RGBA24_6666 = 0x0013,
    /**< RGBA6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha  . */
    FVID2_DF_RGB24_888 = 0x0014,
    /**< RGB24 24-bit - 8-bits R, 8-bits G, 8-bits B. */
    FVID2_DF_BGRX_4444 = 0x0015,
    /**<RGBx12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused .*/
    FVID2_DF_XBGR_4444 = 0x0016,
    /**<xRGB12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused.*/
    FVID2_DF_ARGB32_8888 = 0x0017,
    /**< ARGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha . */
    FVID2_DF_XRGB32_8888 = 0x0018,
    /**< XRGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit unused . */
    FVID2_DF_RGBA32_8888 = 0x0019,
    /**< RGBA32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha  . */
    FVID2_DF_BGR16_565 = 0x001A,
    /**< BGR565 16-bit -   5-bits B, 6-bits G, 5-bits R. */
    FVID2_DF_ABGR16_1555 = 0x001B,
    /**< ABGR1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha . */
    FVID2_DF_ABGR16_4444 = 0x001C,
    /**< ABGR4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha . */
    FVID2_DF_BGRA16_5551 = 0x001D,
    /**< BGRA5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha  . */
    FVID2_DF_BGRA16_4444 = 0x001E,
    /**< BGRA4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha  . */
    FVID2_DF_AGBR16_1555 = 0x001F,
    /**< ABGR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit Alpha . */
    FVID2_DF_AGBR16_4444 = 0x0020,
    /**< ABGR4444 16-bit - 4-bits G, 4-bits B, 4-bits R, 4-bit Alpha . */
    FVID2_DF_XGBR16_1555 = 0x0021,
    /**< XGBR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit unused . */
    FVID2_DF_BGRX16_5551 = 0x0022,
    /**< BGRX5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused . */
    FVID2_DF_ABGR24_6666 = 0x0023,
    /**< ABGR6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha . */
    FVID2_DF_BGR24_888 = 0x0024,
    /**< BGR888 24-bit - 8-bits B, 8-bits G, 8-bits R. */
    FVID2_DF_XBGR24_8888 = 0x0025,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused */
    FVID2_DF_RGBX24_8888 = 0x0026,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused  */
    FVID2_DF_BGRX24_8888 = 0x0027,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused */
    FVID2_DF_ABGR32_8888 = 0x0028,
    /**< ABGR8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha . */
    FVID2_DF_BGRA24_6666 = 0x0029,
    /**< BGRA6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha  . */
    FVID2_DF_BGRA32_8888 = 0x002A,
    /**< BGRA8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha  . */
    FVID2_DF_BGRX32_8888 = 0x002B,
    /**< BGRX8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused. */
    FVID2_DF_BGRA16_1555 = 0x002C,
    /**< BGRA1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha. */
    FVID2_DF_BGRX16_1555 = 0x002D,
    /**< BGRX1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused. */
    FVID2_DF_BGRA32_1010102 = 0x002E,
    /**< BGRA1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit Alpha.*/
    FVID2_DF_BGRX32_1010102 = 0x002F,
    /**< BGRX1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit unused.*/
    FVID2_DF_RGBA32_1010102 = 0x0030,
    /**< RGBA1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit Alpha.*/
    FVID2_DF_RGBX32_1010102 = 0x0031,
    /**< RGBX1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit unused.*/
    FVID2_DF_BGRA64_16161616 = 0x0032,
    /**< RGBA16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit Alpha.*/
    FVID2_DF_BGRX64_16161616 = 0x0033,
    /**< BGRX16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit unused.*/
    FVID2_DF_ABGR64_16161616 = 0x0034,
    /**< ABGR16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit Alpha.*/
    FVID2_DF_XBGR64_16161616 = 0x0035,
    /**< XBGR16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit unused.*/
    FVID2_DF_BITMAP8 = 0x0036,
    /**< BITMAP 8bpp. */
    FVID2_DF_BITMAP4_LOWER = 0x0037,
    /**< BITMAP 4bpp lower address in CLUT. */
    FVID2_DF_BITMAP4_UPPER = 0x0038,
    /**< BITMAP 4bpp upper address in CLUT. */
    FVID2_DF_BITMAP2_OFFSET0 = 0x0039,
    /**< BITMAP 2bpp offset 0 in CLUT. */
    FVID2_DF_BITMAP2_OFFSET1 = 0x003A,
    /**< BITMAP 2bpp offset 1 in CLUT. */
    FVID2_DF_BITMAP2_OFFSET2 = 0x003B,
    /**< BITMAP 2bpp offset 2 in CLUT. */
    FVID2_DF_BITMAP2_OFFSET3 = 0x003C,
    /**< BITMAP 2bpp offset 3 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET0 = 0x003D,
    /**< BITMAP 1bpp offset 0 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET1 = 0x003E,
    /**< BITMAP 1bpp offset 1 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET2 = 0x003F,
    /**< BITMAP 1bpp offset 2 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET3 = 0x0040,
    /**< BITMAP 1bpp offset 3 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET4 = 0x0041,
    /**< BITMAP 1bpp offset 4 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET5 = 0x0042,
    /**< BITMAP 1bpp offset 5 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET6 = 0x0043,
    /**< BITMAP 1bpp offset 6 in CLUT. */
    FVID2_DF_BITMAP1_OFFSET7 = 0x0044,
    /**< BITMAP 1bpp offset 7 in CLUT. */
    FVID2_DF_BITMAP8_BGRA32 = 0x0045,
    /**< BITMAP 8bpp BGRA32. */
    FVID2_DF_BITMAP4_BGRA32_LOWER = 0x0046,
    /**< BITMAP 4bpp BGRA32 lower address in CLUT. */
    FVID2_DF_BITMAP4_BGRA32_UPPER = 0x0047,
    /**< BITMAP 4bpp BGRA32 upper address in CLUT. */
    FVID2_DF_BITMAP2_BGRA32_OFFSET0 = 0x0048,
    /**< BITMAP 2bpp BGRA32 offset 0 in CLUT. */
    FVID2_DF_BITMAP2_BGRA32_OFFSET1 = 0x0049,
    /**< BITMAP 2bpp BGRA32 offset 1 in CLUT. */
    FVID2_DF_BITMAP2_BGRA32_OFFSET2 = 0x004A,
    /**< BITMAP 2bpp BGRA32 offset 2 in CLUT. */
    FVID2_DF_BITMAP2_BGRA32_OFFSET3 = 0x004B,
    /**< BITMAP 2bpp BGRA32 offset 3 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET0 = 0x004C,
    /**< BITMAP 1bpp BGRA32 offset 0 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET1 = 0x004D,
    /**< BITMAP 1bpp BGRA32 offset 1 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET2 = 0x004E,
    /**< BITMAP 1bpp BGRA32 offset 2 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET3 = 0x004F,
    /**< BITMAP 1bpp BGRA32 offset 3 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET4 = 0x0050,
    /**< BITMAP 1bpp BGRA32 offset 4 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET5 = 0x0051,
    /**< BITMAP 1bpp BGRA32 offset 5 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET6 = 0x0052,
    /**< BITMAP 1bpp BGRA32 offset 6 in CLUT. */
    FVID2_DF_BITMAP1_BGRA32_OFFSET7 = 0x0053,
    /**< BITMAP 1bpp BGRA32 offset 7 in CLUT. */
    FVID2_DF_BAYER_RAW = 0x0054,
    /**< Bayer pattern. */
    FVID2_DF_BAYER_GRBG = 0x0055,
    /* < Raw bayer data color pattern
     * G R G R ...
     * B G B G ...
     */
    FVID2_DF_BAYER_RGGB = 0x0056,
    /* < Raw bayer data color pattern
     * R G G R ...
     * G B G B ...
     */
    FVID2_DF_BAYER_BGGR = 0x0057,
    /* < Raw bayer data color pattern
     * B G B G ...
     * G B G B ...
     */
    FVID2_DF_BAYER_GBRG = 0x0058,
    /* < Raw bayer data color pattern
     * G B G B ...
     * R R R G ...
     */
    FVID2_DF_RAW_VBI = 0x0059,
    /**< Raw VBI data. */
    FVID2_DF_RAW24 = 0x005A,
    /**< 24 bit raw-data. */
    FVID2_DF_RAW16 = 0x005B,
    /**< 16 bit raw-data. */
    FVID2_DF_RAW08 = 0x005C,
    /**< 8 bit raw-data. */
    FVID2_DF_MISC = 0x005D,
    /**< For future purpose. */
    FVID2_DF_BITMAP4 = FVID2_DF_BITMAP4_LOWER,
    /** BITMAP 4bpp. */
    FVID2_DF_BITMAP2 = FVID2_DF_BITMAP2_OFFSET0,
    /** BITMAP 2bpp. */
    FVID2_DF_BITMAP1 = FVID2_DF_BITMAP1_OFFSET0,
    /** BITMAP 1bpp. */
    FVID2_DF_RAW06 = 0x5E,
    /**< 6 bit raw-data. */
    FVID2_DF_RAW07 = 0x5F,
    /**< 7 bit raw-data. */
    FVID2_DF_RAW10 = 0x60,
    /**< 10 bit raw-data. */
    FVID2_DF_RAW12 = 0x61,
    /**< 12 bit raw-data. */
    FVID2_DF_RAW14 = 0x62,
    /**< 14 bit raw-data. */
    FVID2_DF_JPEG1_INTERCHANGE = 0x63,
    /**< JPEG INTERCHANGE data. */
    FVID2_DF_JPEG2_JFIF = 0x64,
    /**< JPEG2 JFIF data. */
    FVID2_DF_JPEG3_EXIF = 0x65,
    /**< JPEG3 EXIF data. */
    FVID2_DF_DPCM_10_8_10_PRED1 = 0x66,
    /**< DPCM 10-8-10 PRED1 data. */
    FVID2_DF_DPCM_10_8_10_PRED2 = 0x67,
    /**< DPCM 10-8-10 PRED2 data. */
    FVID2_DF_DPCM_10_7_10_PRED1 = 0x68,
    /**< DPCM 10-7-10 PRED1 data. */
    FVID2_DF_DPCM_10_7_10_PRED2 = 0x69,
    /**< DPCM 10-7-10 PRED2 data. */
    FVID2_DF_DPCM_10_6_10_PRED1 = 0x6A,
    /**< DPCM 10-6-10 PRED1 data. */
    FVID2_DF_DPCM_10_6_10_PRED2 = 0x6B,
    /**< DPCM 10-6-10 PRED2 data. */
    FVID2_DF_DPCM_12_8_10_PRED1 = 0x6C,
    /**< DPCM 12-8-10 PRED1 data. */
    FVID2_DF_DPCM_12_8_10_PRED2 = 0x6D,
    /**< DPCM 12-8-10 PRED2 data. */
    FVID2_DF_DPCM_12_7_10_PRED1 = 0x6E,
    /**< DPCM 12-7-10 PRED1 data. */
    FVID2_DF_DPCM_12_7_10_PRED2 = 0x6F,
    /**< DPCM 12-7-10 PRED2 data. */
    FVID2_DF_DPCM_12_6_10_PRED1 = 0x70,
    /**< DPCM 12-6-10 PRED1 data. */
    FVID2_DF_DPCM_12_6_10_PRED2 = 0x71,
    /**< DPCM 12-6-10 PRED2 data. */
    FVID2_DF_BGR16_565_A8 = 0x72,
    /**< BGR565 16-bit - 5-bits B, 6-bits G, 5-bits R.
     *Alpha 8 -bits another plane */
    FVID2_DF_RGB16_565_A8 = 0x73,
    /**< RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B.
     *Alpha 8 -bits another plane */
    FVID2_DF_LUMA_ONLY = 0x74,
    /**< Luma only data for YUV data format*/
    FVID2_DF_CHROMA_ONLY = 0x75,
    /**< Chroma only data for YUV data format*/

    FVID2_DF_INVALID = 0x0074
                       /**< Invalid data format. Could be used to initialize
                        *variables. */
} Fvid2_DataFormat;

/**
 *  \brief Scan format.
 */
typedef enum
{
    FVID2_SF_INTERLACED = 0,
    /**< Interlaced mode. */
    FVID2_SF_PROGRESSIVE,
    /**< Progressive mode. */
    FVID2_SF_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_ScanFormat;

/**
 *  \brief Video standards.
 */
typedef enum
{
    FVID2_STD_NTSC = 0U,
    /**< 720x480 30FPS interlaced NTSC standard. */
    FVID2_STD_PAL,
    /**< 720x576 30FPS interlaced PAL standard. */

    FVID2_STD_480I,
    /**< 720x480 30FPS interlaced SD standard. */
    FVID2_STD_576I,
    /**< 720x576 30FPS interlaced SD standard. */

    FVID2_STD_CIF,
    /**< Interlaced, 360x120 per field NTSC, 360x144 per field PAL. */
    FVID2_STD_HALF_D1,
    /**< Interlaced, 360x240 per field NTSC, 360x288 per field PAL. */
    FVID2_STD_D1,
    /**< Interlaced, 720x240 per field NTSC, 720x288 per field PAL. */

    FVID2_STD_480P,
    /**< 720x480 60FPS progressive ED standard. */
    FVID2_STD_576P,
    /**< 720x576 60FPS progressive ED standard. */

    FVID2_STD_720P_60,
    /**< 1280x720 60FPS progressive HD standard. */
    FVID2_STD_720P_50,
    /**< 1280x720 50FPS progressive HD standard. */

    FVID2_STD_1080I_60,
    /**< 1920x1080 30FPS interlaced HD standard. */
    FVID2_STD_1080I_50,
    /**< 1920x1080 50FPS interlaced HD standard. */

    FVID2_STD_1080P_60,
    /**< 1920x1080 60FPS progressive HD standard. */
    FVID2_STD_1080P_50,
    /**< 1920x1080 50FPS progressive HD standard. */

    FVID2_STD_1080P_24,
    /**< 1920x1080 24FPS progressive HD standard. */
    FVID2_STD_1080P_30,
    /**< 1920x1080 30FPS progressive HD standard. */

    /* Vesa standards from here Please add all SMTPE and CEA standard enums
     * above this only. this is to ensure proxy Oses compatibility */
    FVID2_STD_VGA_60,
    /**< 640x480 60FPS VESA standard. */
    FVID2_STD_VGA_72,
    /**< 640x480 72FPS VESA standard. */
    FVID2_STD_VGA_75,
    /**< 640x480 75FPS VESA standard. */
    FVID2_STD_VGA_85,
    /**< 640x480 85FPS VESA standard. */

    FVID2_STD_WVGA_60,
    /**< 800x480 60PFS WVGA */

    FVID2_STD_SVGA_60,
    /**< 800x600 60FPS VESA standard. */
    FVID2_STD_SVGA_72,
    /**< 800x600 72FPS VESA standard. */
    FVID2_STD_SVGA_75,
    /**< 800x600 75FPS VESA standard. */
    FVID2_STD_SVGA_85,
    /**< 800x600 85FPS VESA standard. */

    FVID2_STD_WSVGA_70,
    /**< 1024x600 70FPS standard. */

    FVID2_STD_XGA_60,
    /**< 1024x768 60FPS VESA standard. */
    FVID2_STD_XGA_DSS_TDM_60,
    /**< 1024x768 60FPS VESA standard. Applicable for
     *  DSS in 8-bit TDM mode.*/
    FVID2_STD_XGA_70,
    /**< 1024x768 72FPS VESA standard. */
    FVID2_STD_XGA_75,
    /**< 1024x768 75FPS VESA standard. */
    FVID2_STD_XGA_85,
    /**< 1024x768 85FPS VESA standard. */

    FVID2_STD_1368_768_60,
    /**< 1368x768 60 PFS VESA. */
    FVID2_STD_1366_768_60,
    /**< 1366x768 60 PFS VESA. */
    FVID2_STD_1360_768_60,
    /**< 1360x768 60 PFS VESA. */

    FVID2_STD_WXGA_30,
    /**< 1280x800 30FPS VESA standard. */
    FVID2_STD_WXGA_60,
    /**< 1280x800 60FPS VESA standard. */
    FVID2_STD_WXGA_75,
    /**< 1280x800 75FPS VESA standard. */
    FVID2_STD_WXGA_85,
    /**< 1280x800 85FPS VESA standard. */

    FVID2_STD_1440_900_60,
    /**< 1440x900 60 PFS VESA>*/

    FVID2_STD_SXGA_60,
    /**< 1280x1024 60FPS VESA standard. */
    FVID2_STD_SXGA_75,
    /**< 1280x1024 75FPS VESA standard. */
    FVID2_STD_SXGA_85,
    /**< 1280x1024 85FPS VESA standard. */

    FVID2_STD_WSXGAP_60,
    /**< 1680x1050 60 PFS VESA>*/

    FVID2_STD_SXGAP_60,
    /**< 1400x1050 60FPS VESA standard. */
    FVID2_STD_SXGAP_75,
    /**< 1400x1050 75FPS VESA standard. */

    FVID2_STD_UXGA_60,
    /**< 1600x1200 60FPS VESA standard. */

    /* Multi channel standards from here Please add all VESA standards enums
     * above this only. this is to ensure proxy Oses compatibility */
    FVID2_STD_MUX_2CH_D1,
    /**< Interlaced, 2Ch D1, NTSC or PAL. */
    FVID2_STD_MUX_2CH_HALF_D1,
    /**< Interlaced, 2ch half D1, NTSC or PAL. */
    FVID2_STD_MUX_2CH_CIF,
    /**< Interlaced, 2ch CIF, NTSC or PAL. */
    FVID2_STD_MUX_4CH_D1,
    /**< Interlaced, 4Ch D1, NTSC or PAL. */
    FVID2_STD_MUX_4CH_CIF,
    /**< Interlaced, 4Ch CIF, NTSC or PAL. */
    FVID2_STD_MUX_4CH_HALF_D1,
    /**< Interlaced, 4Ch Half-D1, NTSC or PAL. */
    FVID2_STD_MUX_8CH_CIF,
    /**< Interlaced, 8Ch CIF, NTSC or PAL. */
    FVID2_STD_MUX_8CH_HALF_D1,
    /**< Interlaced, 8Ch Half-D1, NTSC or PAL. */

    FVID2_STD_WXGA_5x3_30,
    /**< WXGA standard (1280x768) with the aspect ratio 5:3 at 30FPS. */
    FVID2_STD_WXGA_5x3_60,
    /**< WXGA resolution (1280x768) with the aspect ratio 5:3 at 60FPS. */
    FVID2_STD_WXGA_5x3_75,
    /**< WXGA resolution (1280x768) with the aspect ratio 5:3 at 75FPS. */

    /* Auto detect and Custom standards Please add all multi channel standard
     * enums above this only. this is to ensure proxy Oses compatibility */
    FVID2_STD_AUTO_DETECT,
    /**< Auto-detect standard. Used in capture mode. */
    FVID2_STD_CUSTOM
    /**< Custom standard used when connecting to external LCD etc...
     *   The video timing is provided by the application.
     *   Used in display mode. */
} Fvid2_Standard;

/**
 *  \brief Field type.
 */
typedef enum
{
    FVID2_FID_TOP = 0,
    /**< Top field. */
    FVID2_FID_BOTTOM,
    /**< Bottom field. */
    FVID2_FID_FRAME,
    /**< Frame mode - Contains both the fields or a progressive frame. */
    FVID2_FID_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_Fid;

/**
 *  \brief Polarity type.
 */
typedef enum
{
    FVID2_POL_LOW = 0,
    /**< Low Polarity. */
    FVID2_POL_HIGH,
    /**< High Polarity. */
    FVID2_POL_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_Polarity;

/**
 *  \brief Polarity type.
 */
typedef enum
{
    FVID2_EDGE_POL_RISING = 0,
    /**< Rising Edge. */
    FVID2_EDGE_POL_FALLING,
    /**< Falling Edge. */
    FVID2_EDGE_POL_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_EdgePolarity;

/**
 *  \brief Enumerations for Field ID polarity.
 */
typedef enum
{
    FVID2_FIDPOL_NORMAL = 0,
    /**< FID = 0, top field */
    FVID2_FIDPOL_INVERT
    /**< FID = 1, bottom field */
} Fvid2_FidPol;

/**
 * \brief Buffer storage format.
 */
typedef enum
{
    FVID2_BUF_FMT_FIELD = 0,
    /**< Buffers are captured/displayed as fields instead of frames */
    FVID2_BUF_FMT_FRAME
    /**< Buffers are captured/displayed as frames instead of frames */
} Fvid2_BufferFormat;

/**
 *  \brief Bits per pixel.
 */
typedef enum
{
    FVID2_BPP_BITS1 = 0,
    /**< 1 Bits per Pixel. */
    FVID2_BPP_BITS2,
    /**< 2 Bits per Pixel. */
    FVID2_BPP_BITS4,
    /**< 4 Bits per Pixel. */
    FVID2_BPP_BITS8,
    /**< 8 Bits per Pixel. */
    FVID2_BPP_BITS12,
    /**< 12 Bits per Pixel, unpacked in 16bit container */
    FVID2_BPP_BITS16,
    /**< 16 Bits per Pixel. */
    FVID2_BPP_BITS24,
    /**< 24 Bits per Pixel. */
    FVID2_BPP_BITS32,
    /**< 32 Bits per Pixel. */
    FVID2_BPP_BITS10,
    /**< 10 Bits per Pixel unpacked in 16bit container */
    FVID2_BPP_BITS7,
    /**< 7 Bits per Pixel unpacked in 8bit container. */
    FVID2_BPP_BITS9,
    /**< 9 Bits per Pixel unpacked in 16bit container. */
    FVID2_BPP_BITS11,
    /**< 11 Bits per Pixel unpacked in 16bit container. */
    FVID2_BPP_BITS13,
    /**< 13 Bits per Pixel unpacked in 16bit container. */
    FVID2_BPP_BITS14,
    /**< 14 Bits per Pixel unpacked in 16bit container. */
    FVID2_BPP_BITS15,
    /**< 15 Bits per Pixel unpacked in 16bit container. */
    FVID2_BPP_BITS20,
    /**< 20 Bits per Pixel unpacked in 24bit container. */
    FVID2_BPP_BITS6,
    /**< 6 Bits per Pixel unpacked in 8bit container. */
    FVID2_BPP_BITS10_PACKED,
    /**< 12 Bits per Pixel packed */
    FVID2_BPP_BITS12_PACKED,
    /**< 12 Bits per Pixel packed */
    FVID2_BPP_BITS14_PACKED,
    /**< 12 Bits per Pixel packed */
    FVID2_BPP_BITS12_PACKED_MIPI,
    /**< 12 Bits per Pixel packed in MIPI output format */
    FVID2_BPP_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_BitsPerPixel;

/**
 *  \brief Digital video interface width.
 */
typedef enum
{
    FVID2_VIFW_8BIT = 0,
    /**< 8-bit interface. */
    FVID2_VIFW_10BIT,
    /**< 10-bit interface. */
    FVID2_VIFW_12BIT,
    /**< 12-bit interface. */
    FVID2_VIFW_14BIT,
    /**< 14-bit interface. */
    FVID2_VIFW_16BIT,
    /**< 16-bit interface. */
    FVID2_VIFW_18BIT,
    /**< 18-bit interface. */
    FVID2_VIFW_20BIT,
    /**< 20-bit interface. */
    FVID2_VIFW_24BIT,
    /**< 24-bit interface. */
    FVID2_VIFW_30BIT,
    /**< 30-bit interface. */
    FVID2_VIFW_1LANES,
    /**< CSI2 specific - 1 data lanes */
    FVID2_VIFW_2LANES,
    /**< CSI2 specific - 2 data lanes */
    FVID2_VIFW_3LANES,
    /**< CSI2 specific - 3 data lanes */
    FVID2_VIFW_4LANES,
    /**< CSI2 / LVDS specific - 4 data lanes */
    FVID2_VIFW_MAX
    /**< Maximum modes */
} Fvid2_VideoIfWidth;

/**
 *  \brief Video interface mode.
 */
typedef enum
{
    FVID2_VIFM_SCH_ES = 0,
    /**< Single Channel non multiplexed mode. */
    FVID2_VIFM_MCH_LINE_MUX_ES,
    /**< Multi-channel line-multiplexed mode. */
    FVID2_VIFM_MCH_PIXEL_MUX_ES,
    /**< Multi-channel pixel muxed. */
    FVID2_VIFM_SCH_DS_HSYNC_VBLK,
    /**< Single Channel non multiplexed discrete sync mode with HSYNC and
     *   VBLK as control signals. */
    FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
    /**< Single Channel non multiplexed discrete sync mode with HSYNC and
     *   VSYNC as control signals. */
    FVID2_VIFM_SCH_DS_AVID_VBLK,
    /**< Single Channel non multiplexed discrete sync mode with AVID and
     *   VBLK as control signals. */
    FVID2_VIFM_SCH_DS_AVID_VSYNC,
    /**< Single Channel non multiplexed discrete sync mode with AVID and
     *   VBLK as control signals. */
    FVID2_VIFM_MCH_LINE_MUX_SPLIT_LINE_ES,
    /**< Multi-channel line-multiplexed mode - split line mode. */
    FVID2_VIFM_SCH_CSI2,
    /**< Single channel capture via CSI2 interface */
    FVID2_VIFM_SCH_LVDS,
    /**< Single channel capture via LVDS interface */
    FVID2_VIFM_SCH_CPI,
    /**< Single channel capture via Parallel interface */
    FVID2_VIFM_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_VideoIfMode;

/**
 *  \brief Video frame rate.
 */
typedef enum
{
    FVID2_FPS_85,
    /**< 85 frames per second. */
    FVID2_FPS_75,
    /**< 75 frames per second. */
    FVID2_FPS_72,
    /**< 72 frames per second. */
    FVID2_FPS_70,
    /**< 70 frames per second. */
    FVID2_FPS_60,
    /**< 60 frames per second. */
    FVID2_FPS_50,
    /**< 50 frames per second. */
    FVID2_FPS_30,
    /**< 30 frames per second. */
    FVID2_FPS_25,
    /**< 25 frames per second. */
    FVID2_FPS_24,
    /**< 24 frames per second. */
    FVID2_FPS_15,
    /**< 15 frames per second. */
    FVID2_FPS_10,
    /**< 10 frames per second. */
    FVID2_FPS_5,
    /**< 5 frames per second. */
    FVID2_FPS_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Fvid2_VideoFrameRate;

/**
 *  \brief Enum for selecting chroma position in chroma up or down sampler
 */
typedef enum
{
    FVID2_CHROMA_POS_COSITED,
    /**< Chroma is cosited */
    FVID2_CHROMA_POS_CENTERED
    /**< Chroma is Centered */
} Fvid2_ChromaPos;

/**
 *  \brief Enum for selecting bayer color components for odd/even pixel
 *         position on odd/even lines, Also used for specifying gain and offset
 *         in White balance config for each color component
 */
typedef enum
{
    FVID2_BAYER_COLOR_COMP_R,
    /**< Red Color Component in Bayer image */
    FVID2_BAYER_COLOR_COMP_GR,
    /**< GreenR Color Component in Bayer image */
    FVID2_BAYER_COLOR_COMP_GB,
    /**< GreenB Color Component in Bayer image */
    FVID2_BAYER_COLOR_COMP_B,
    /**< Blue Color Component in Bayer image */
    FVID2_BAYER_COLOR_COMP_MAX
    /**< This should be the last number,
     *   used in specifying array size */
} Fvid2_BayerColorComp;

/**
 *  \brief Enum for state of the FVID2 frame. Typically used for
 *         marking FVID2_frame as either SUBMITTED, Completed/Done, Erroneous
 *         at the time of flush/abort when driver returns back all the frames
 */
typedef enum
{
    FVID2_FRAME_STATUS_INIT = 0,
    /**< FVID2 Frame is initialized using init function */
    FVID2_FRAME_STATUS_COMPLETED,
    /**< Frame processing is completed and can be used in the application */
    FVID2_FRAME_STATUS_PENDING,
    /**< Frame processing is still pending, used for the frames which
     *   are dequeued before being processed */
    FVID2_FRAME_STATUS_SUBMITTED,
    /**< Frame is just submitted to the driver */
    FVID2_FRAME_STATUS_ERROR,
    /**< Frame has error */
    FVID2_FRAME_STATUS_ABORTED,
    /**< Frame processing is aborted, used for the frames which
     *   are force moved to output queue */
    FVID2_FRAME_STATUS_OVERFLOW,
    /**< The IP processing this frame experienced and overflow of its internal
            buffers. Indicates severe error */
    FVID2_FRAME_STATUS_ECC_CORRECTED,
    /**< There was 1 bit ECC error, which was corrected.
            Provided the hardware and/or protocol used to process this frame
            supports ECC */
    FVID2_FRAME_STATUS_CRC_ERROR,
    /**< CRC errors were detected, the integrity of the data is not guaranteed.
            Provided the hardware and/or protocol used to process this frame
            supports CRC */
    FVID2_FRAME_STATUS_ECC_ERROR,
    /**< There were multiple bit ECC error, which was could not be corrected.
            Provided the hardware and/or protocol used to process this frame
            supports ECC */
    FVID2_FRAME_STATUS_MAX
    /**< This should be the last number, */
} Fvid2_FrameStatus;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief FVID2 video buffer format specification.
 *
 *  Used during Fvid2_create() by some drivers. Used as parameter to
 *  Fvid2_setFormat(), Fvid2_getFormat() by some drivers.
 */
typedef struct
{
    UInt32 chNum;
    /**< Channel Number to which this format belongs to. */

    UInt32 width;
    /**< Width of the video frame or field in pixels. */

    UInt32 height;
    /**< Height of the video frame or field in lines. */

    UInt32 pitch[FVID2_MAX_PLANES];
    /**< Pitch in bytes for each of the sub-buffers. This represents the
     *   difference between two consecutive line addresses in bytes.
     *   This is irrespective of whether the video is interlaced or
     *   progressive and whether the fields are merged or separated for
     *   interlaced video. */

    UInt32 fieldMerged[FVID2_MAX_PLANES];
    /**< This field tells whether both the fields have to be merged,
     *   i.e line interleaved or not.
     *   Used only for interlaced format. The effective pitch is calculated
     *   based on this information along with pitch parameter. If fields are
     *   merged, effective pitch = pitch * 2 else effective pitch = pitch. */

    UInt32 dataFormat;
    /**< Frame data Format. For valid values see #Fvid2_DataFormat. */

    UInt32 scanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    UInt32 bpp;
    /**< Number of bits per pixel. For valid values see #Fvid2_BitsPerPixel. */

    Ptr    reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Fvid2_Format;

/**
 *  \brief Sub-Frame information
 *
 *  This is used in drivers supporting sub-frame level processing,
 *  for application and driver interaction
 */
typedef struct
{
    UInt32 subFrameNum;
    /**< [IN]/[OUT] Current sub-frame number in this frame,
     *   range is from 0 to (number of sub-frames in frame - 1).
     *   Set by application and used by driver in case of M2M mode.
     *   Set by driver and used by application in case of capture mode. */

    UInt32 numInLines;
    /**< [IN] Number of lines available in input frame at the end of this
     *   sub-frame.
     *   Used only in M2M mode. Not used in capture mode. */

    UInt32 numOutLines;
    /**< [OUT] Number of lines generated in output buffer after processing
     *   current sub-frame. Set by driver and used by application. */
} Fvid2_SubFrameInfo;

/**
 *  \brief FVID2 frame buffer structure.
 *
 *  Unless specified otherwise, all fields in this structure are
 *
 *  [IN]  for Fvid2_queue(), Fvid2_processFrames() operation.
 *  [OUT] for Fvid2_dequeue(), Fvid2_getProcessedFrames() operation.
 *
 */
typedef struct
{
    Ptr addr[FVID2_MAX_FIELDS][FVID2_MAX_PLANES];
    /**<
     *   FVID2 buffer pointers for supporting multiple addresses like
     *   Y, U, V etc for a given frame. The interpretation of these pointers
     *   depend on the format configured for the driver.
     *   The first dimension represents the field and the second dimension
     *   represents the color plane.
     *   Not all pointers are valid for a given format.
     *
     *   Representation of YUV422 Planar Buffer:
     *   Field 0 Y -> addr[0][0], Field 1 Y -> addr[1][0]
     *   Field 0 U -> addr[0][1], Field 1 U -> addr[1][1]
     *   Field 0 V -> addr[0][2], Field 1 V -> addr[1][2]
     *   Other pointers are not valid.
     *
     *   Representation of YUV422 Interleaved Buffer:
     *   Field 0 YUV -> addr[0][0], Field 1 YUV -> addr[1][0]
     *   Other pointers are not valid.
     *
     *   Representation of YUV420SP or YUV422SP Buffer:
     *   Field 0 Y  -> addr[0][0], Field 1 Y  -> addr[1][0]
     *   Field 0 UV -> addr[0][1], Field 1 UV -> addr[1][1]
     *   Other pointers are not valid.
     *
     *   Representation of RGB888 Buffer
     *   Field 0 RGB -> addr[0][0], Field 1 RGB -> addr[1][0],
     *   Other pointers are not valid.
     *
     *   For progressive mode data formats
     *   or when fields are processed by driver in frame mode.
     *   addr[1][x] is not used.
     *
     *   Instead of using numerical for accessing the buffers, the application
     *   can use the macros defined for each buffer formats like
     *   FVID2_YUV_INT_ADDR_IDX, FVID2_RGB_ADDR_IDX, FVID2_FID_TOP etc. */

    UInt32 fid;
    /**< Indicates whether this frame belong to top or bottom field.
     *   For valid values see #Fvid2_Fid. */
    UInt32 chNum;
    /**< Channel number to which this FVID2 frame belongs to. */

    UInt32 timeStamp;
    /**< Time stamp returned by the driver, in units of msecs.
     *   Only valid for frames received using Fvid2_dequeue(). */
    UInt64 timeStamp64;
    /**< 64-bit Time stamp returned by the driver.
     *   The value and the unit is driver implementation dependent.
     *   But in general the time stamp stored is in micro-seconds.
     *   Refer to each driver implementation for the meaning and unit of the
     *   time stamp value.
     *   Only valid for frames received using Fvid2_dequeue(). */

    Ptr    appData;
    /**< Additional application parameter per frame. This is not modified by
     *   driver. */

    Ptr    perFrameCfg;
    /**< Per frame configuration parameters like scaling ratio, positioning,
     *   cropping etc...
     *   This should be set to NULL if not used.
     *
     *   This can be used by application to control driver behaviour on a per
     *   frame basis, example changing scaling ratio for scaler driver.
     *
     *   This can be used by application to get per frame status, example
     *   detected frame width, height from capture driver.
     *
     *   This could be set to NULL if not used. In this case, the driver will
     *   use the last supplied configuration.
     *
     *   The exact structure type that is passed is driver specific. */

    Ptr                 blankData;
    /**< Blanking data associated with this video frame.
     *   This could be set to NULL if not used. */

    Ptr                 drvData;
    /**< Used by driver. Application should not modify this. */

    Fvid2_SubFrameInfo *subFrameInfo;
    /**< Used for SubFrame level processing information exchange between
     *   application and driver.
     *   This could be set to NULL if sub-frame level processing  is
     *   not used. */

    UInt32              status;
    /**< Status of the Frame, see #Fvid2_FrameStatus for the valid values
     *   Updated by the driver */

    Ptr                 reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Fvid2_Frame;

/**
 *  \brief FVID2 frame buffer list used to exchange multiple FVID2
 *  frames in a single driver call.
 *
 *  Unless specified otherwise, all fields in this structure are
 *
 *  [IN]  for Fvid2_queue(), Fvid2_processFrames() operation.
 *  [OUT] for Fvid2_dequeue(), Fvid2_getProcessedFrames() operation.
 *
 */
typedef struct
{
    Fvid2_Frame *frames[FVID2_MAX_FRAME_PTR];
    /**< Array of Fvid2_Frame pointers that are to given or received from the
     *   driver. */

    UInt32       numFrames;
    /**< Number of frames that are given or received from the driver
     * i.e number of valid pointers in the array containing Fvid2_Frame
     * pointers. */

    Ptr          perListCfg;
    /**< Per list configuration parameters like scaling ratio, positioning,
     *   cropping etc which are applicable for the frames together.
     *
     *   This could be set to NULL if not used. In this case, the driver will
     *   use the last supplied configuration.
     *
     *   The exact structure type that is passed is driver specific. */

    Ptr          drvData;
    /**< Used by driver. Application should not modify this. */

    Ptr          reserved;
    /**< For future use. Not used currently. Set this to NULL. */

    Ptr          appData;
    /**< Additional application parameter per frame. This is not modified by
     *   driver. */
} Fvid2_FrameList;

/**
 *  \brief FVID2 Mode information structure.
 */
typedef struct
{
    UInt32 standard;
    /**< [IN] Standard for which to get the info.
     *   For valid values see #Fvid2_Standard. */
    UInt32 width;
    /**< Active video frame width in pixels. */
    UInt32 height;
    /**< Active video frame height in lines. */
    UInt32 scanFormat;
    /**< Scan format of standard. For valid values see #Fvid2_ScanFormat. */
    UInt32 pixelClock;
    /**< Pixel clock of standard in KHz. This assumes 8-bit interface for
     *   NTSC/PAL/480I/576I resolutions and 16/24-bit interface for other
     *   resolutions including 480P and 576P. */
    UInt32 fps;
    /**< Frames per second. */
    UInt32 hFrontPorch;
    /**< Horizontal front porch. Same for both fields in case of interlaced
     *   display. */
    UInt32 hBackPorch;
    /**< Horizontal back porch. */
    UInt32 hSyncLen;
    /**< Horizontal sync length. Same for both fields in case of interlaced
     *   display. */
    UInt32 vFrontPorch;
    /**< Vertical front porch for each field or frame. */
    UInt32 vBackPorch;
    /**< Vertical back porch for each field or frame. */
    UInt32 vSyncLen;
    /**< Vertical sync length for each field. */
    UInt32 reserved[4U];
    /**< For future use. Not used currently. */
} Fvid2_ModeInfo;

/**
 *  struct Fvid2_CropConfig
 *  \brief Structure containing crop configuration - used in Scaler and VCOMP.
 */
typedef struct
{
    UInt32 cropStartX;
    /**< Horizontal offset from which picture needs to be cropped. */
    UInt32 cropStartY;
    /**< Vertical offset from which picture needs to be cropped. */
    UInt32 cropWidth;
    /**< Width of the picture to be cropped. */
    UInt32 cropHeight;
    /**< Height of the picture to be cropped. */
} Fvid2_CropConfig;

/**
 *  struct Fvid2_PosConfig
 *  \brief Structure containing position configuration - used in VCOMP and CIG.
 */
typedef struct
{
    UInt32 startX;
    /**< Horizontal offset from which picture needs to be positioned. */
    UInt32 startY;
    /**< Vertical offset from which picture needs to be positioned. */
} Fvid2_PosConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to get the information about various FVID2 modes/standards.
 *
 *  \param modeInfo     [OUT] Pointer to #Fvid2_ModeInfo structure where
 *                            the information is filled.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Fvid2_getModeInfo(Fvid2_ModeInfo *modeInfo);

/**
 *  \brief Function to get the name of the data format in printable string.
 *
 *  \param dataFmt      [IN] Data format to get the name.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns a const pointer to the string. If the data format is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Fvid2_getDataFmtString(UInt32 dataFmt);

/**
 *  \brief Function to get the name of the standard in printable string.
 *
 *  \param standard     [IN] Standard to get the name.
 *                           For valid values see #Fvid2_Standard.
 *
 *  \return Returns a const pointer to the string. If the standard is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Fvid2_getStandardString(UInt32 standard);

/**
 *  \brief Function to check whether a data format is YUV422.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV422, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv422(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is YUV420.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV420, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv420(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is YUV420SP.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV420SP, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv420Sp(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is YUV422SP.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV422SP, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv422Sp(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is semi-planar.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is semi-planar, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtSemiPlanar(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is YUV422 interleaved.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV422 interleaved, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv422I(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is YUV444 .
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV444 , FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv444(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is YUV.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtYuv(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is Bayer with MosaicPattern.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is Bayer, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtBayer(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 16-bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 16-bit, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtRgb16bit(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is RGB .
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB , FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtRgb(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 24-bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 24-bit, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtRgb24bit(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 32-bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 32-bit, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtRgb32bit(UInt32 dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 64 bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 64-bit, FALSE otherwise.
 */
static inline Int32 Fvid2_isDataFmtRgb64bit(UInt32 dataFmt);

/**
 *  \brief Function to get the index of the color for bayer data format.
 *
 *  \param dataFmt      [IN] Bayer Data Format
 *                           For valid values see #Fvid2_DataFormat.
 *  \param color        [IN] Bayer Color Component
 *                           For valid values see #Fvid2_BayerColorComp
 *
 *
 *  \return Returns index of the color component.
 */
static inline UInt32 Fvid2_BayerColorIndex(UInt32 dataFmt, UInt32 color);

/**
 *  \brief Function to check whether a standard is VESA mode or not.
 *
 *  \param standard     [IN] Standard to check.
 *                           For valid values see #Fvid2_Standard.
 *
 *  \return Returns TRUE if standard is VESA, FALSE otherwise.
 */
static inline Int32 Fvid2_isStandardVesa(UInt32 standard);

/**
 *  \brief Fvid2_Format structure init function.
 *
 *  \param fmt          [IN] Pointer to #Fvid2_Format structure.
 *
 */
static inline void Fvid2Format_init(Fvid2_Format *fmt);

/**
 *  \brief Fvid2_SubFrameInfo structure init function.
 *
 *  \param sfInfo       [IN] Pointer to #Fvid2_SubFrameInfo structure.
 *
 */
static inline void Fvid2SubFrameInfo_init(Fvid2_SubFrameInfo *sfInfo);

/**
 *  \brief Fvid2_Frame structure init function.
 *
 *  \param frm          [IN] Pointer to #Fvid2_Frame structure.
 *
 */
static inline void Fvid2Frame_init(Fvid2_Frame *frm);

/**
 *  \brief Fvid2_FrameList structure init function.
 *
 *  \param fList        [IN] Pointer to #Fvid2_FrameList structure.
 *
 */
static inline void Fvid2FrameList_init(Fvid2_FrameList *fList);

/**
 *  \brief Fvid2_ModeInfo structure init function. This defaults to 1080p60.
 *
 *  \param modeInfo     [IN] Pointer to #Fvid2_ModeInfo structure.
 *
 */
static inline void Fvid2ModeInfo_init(Fvid2_ModeInfo *modeInfo);

/**
 *  \brief Fvid2_CropConfig structure init function.
 *
 *  \param cropCfg      [IN] Pointer to #Fvid2_CropConfig structure.
 *
 */
static inline void Fvid2CropConfig_init(Fvid2_CropConfig *cropCfg);

/**
 *  \brief Fvid2_PosConfig structure init function.
 *
 *  \param posCfg       [IN] Pointer to #Fvid2_PosConfig structure.
 *
 */
static inline void Fvid2PosConfig_init(Fvid2_PosConfig *posCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline Int32 Fvid2_isDataFmtYuv422(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV422P:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtYuv420(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
        case FVID2_DF_YUV420P:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtYuv420Sp(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtYuv422Sp(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtSemiPlanar(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtYuv422I(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtYuv444(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV444P:
        case FVID2_DF_YUV444I:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtBayer(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BAYER_GBRG:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RAW:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtYuv(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV422P:
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
        case FVID2_DF_YUV420P:
        case FVID2_DF_YUV444P:
        case FVID2_DF_YUV444I:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtRgb(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_RGB16_565:
        case FVID2_DF_RGBA16_5551:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_RGBX16_4444:
        case FVID2_DF_RGBA24_6666:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_RGBA32_1010102:
        case FVID2_DF_RGBX32_1010102:
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_BGRX16_5551:
        case FVID2_DF_BGR24_888:
        case FVID2_DF_BGRX24_8888:
        case FVID2_DF_BGRA24_6666:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_BGRX32_8888:
        case FVID2_DF_BGRA16_1555:
        case FVID2_DF_BGRX16_1555:
        case FVID2_DF_BGRA32_1010102:
        case FVID2_DF_BGRX32_1010102:
        case FVID2_DF_BGRA64_16161616:
        case FVID2_DF_BGRX64_16161616:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_XBGR64_16161616:
        case FVID2_DF_ABGR16_1555:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_ABGR24_6666:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_ABGR64_16161616:
        case FVID2_DF_ARGB16_1555:
        case FVID2_DF_ARGB16_4444:
        case FVID2_DF_ARGB24_6666:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_XRGB32_8888:
        case FVID2_DF_BITMAP8_BGRA32:
        case FVID2_DF_BITMAP4_BGRA32_LOWER:
        case FVID2_DF_BITMAP4_BGRA32_UPPER:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET0:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET1:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET2:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET3:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET0:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET1:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET2:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET3:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET4:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET5:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET6:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET7:
        case FVID2_DF_BAYER_RAW:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_GBRG:
        case FVID2_DF_BGR16_565_A8:
        case FVID2_DF_RGB16_565_A8:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtRgb16bit(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_AGBR16_4444:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_RGBX16_4444:
        case FVID2_DF_XGBR16_1555:
        case FVID2_DF_AGBR16_1555:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_RGB16_565:
        case FVID2_DF_ARGB16_1555:
        case FVID2_DF_RGBA16_5551:
        case FVID2_DF_ARGB16_4444:
        case FVID2_DF_ABGR16_1555:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_BGRX16_5551:
        case FVID2_DF_BGRA16_1555:
        case FVID2_DF_BGRX16_1555:
        case FVID2_DF_BGR16_565_A8:
        case FVID2_DF_RGB16_565_A8:
            /* BGR16_565_A8 and RGB16_565_A8 data formats have 24 bits per pixel
             * With 8 bits Alpha in different plane.
             * Since this function is used to check pitch, added in RGB16bit */
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtRgb24bit(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_ABGR24_6666:
        case FVID2_DF_BGRA24_6666:
        case FVID2_DF_ARGB24_6666:
        case FVID2_DF_RGBA24_6666:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtRgb32bit(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRX24_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_BGRX32_8888:
        case FVID2_DF_XRGB32_8888:
        case FVID2_DF_RGBA32_1010102:
        case FVID2_DF_RGBX32_1010102:
        case FVID2_DF_BGRA32_1010102:
        case FVID2_DF_BGRX32_1010102:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline Int32 Fvid2_isDataFmtRgb64bit(UInt32 dataFmt)
{
    Int32 retVal = (Int32) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BGRA64_16161616:
        case FVID2_DF_BGRX64_16161616:
        case FVID2_DF_ABGR64_16161616:
        case FVID2_DF_XBGR64_16161616:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline UInt32 Fvid2_BayerColorIndex(UInt32 dataFmt, UInt32 color)
{
    UInt32 bayerColorIndex;

    switch(dataFmt)
    {
        case FVID2_DF_BAYER_RGGB:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                bayerColorIndex = 0U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                bayerColorIndex = 1U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                bayerColorIndex = 2U;
            }
            else
            {
                bayerColorIndex = 3U;
            }
            break;
        case FVID2_DF_BAYER_GRBG:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                bayerColorIndex = 1U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                bayerColorIndex = 0U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                bayerColorIndex = 3U;
            }
            else
            {
                bayerColorIndex = 2U;
            }
            break;
        case FVID2_DF_BAYER_BGGR:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                bayerColorIndex = 3U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                bayerColorIndex = 2U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                bayerColorIndex = 1U;
            }
            else
            {
                bayerColorIndex = 0U;
            }
            break;
        case FVID2_DF_BAYER_GBRG:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                bayerColorIndex = 2U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                bayerColorIndex = 3U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                bayerColorIndex = 0U;
            }
            else
            {
                bayerColorIndex = 1U;
            }
            break;
        default:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                bayerColorIndex = 0U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                bayerColorIndex = 1U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                bayerColorIndex = 2U;
            }
            else
            {
                bayerColorIndex = 3U;
            }
            break;
    }

    return (bayerColorIndex);
}

static inline Int32 Fvid2_isStandardVesa(UInt32 standard)
{
    Int32 retVal = (Int32) FALSE;

    switch(standard)
    {
        case FVID2_STD_VGA_60:
        case FVID2_STD_VGA_72:
        case FVID2_STD_VGA_75:
        case FVID2_STD_VGA_85:
        case FVID2_STD_SVGA_60:
        case FVID2_STD_SVGA_72:
        case FVID2_STD_SVGA_75:
        case FVID2_STD_SVGA_85:
        case FVID2_STD_WSVGA_70:
        case FVID2_STD_XGA_60:
        case FVID2_STD_XGA_DSS_TDM_60:
        case FVID2_STD_XGA_70:
        case FVID2_STD_XGA_75:
        case FVID2_STD_XGA_85:
        case FVID2_STD_WXGA_60:
        case FVID2_STD_WXGA_75:
        case FVID2_STD_WXGA_85:
        case FVID2_STD_SXGA_60:
        case FVID2_STD_SXGA_75:
        case FVID2_STD_SXGA_85:
        case FVID2_STD_SXGAP_60:
        case FVID2_STD_SXGAP_75:
        case FVID2_STD_UXGA_60:
            retVal = (Int32) TRUE;
            break;

        default:
            retVal = (Int32) FALSE;
            break;
    }

    return (retVal);
}

static inline void Fvid2Format_init(Fvid2_Format *fmt)
{
    UInt32 i;

    if(NULL != fmt)
    {
        fmt->chNum  = 0U;
        fmt->width  = 0U;
        fmt->height = 0U;
        for(i = 0U; i < FVID2_MAX_PLANES; i++)
        {
            fmt->pitch[i]       = 0U;
            fmt->fieldMerged[i] = (UInt32) FALSE;
        }
        fmt->dataFormat = FVID2_DF_YUV422I_YUYV;
        fmt->scanFormat = FVID2_SF_PROGRESSIVE;
        fmt->bpp        = FVID2_BPP_BITS16;
        fmt->reserved   = NULL;
    }

    return;
}

static inline void Fvid2SubFrameInfo_init(Fvid2_SubFrameInfo *sfInfo)
{
    if(NULL != sfInfo)
    {
        sfInfo->subFrameNum = 0U;
        sfInfo->numInLines  = 0U;
        sfInfo->numOutLines = 0U;
    }

    return;
}

static inline void Fvid2Frame_init(Fvid2_Frame *frm)
{
    UInt32 i, j;

    if(NULL != frm)
    {
        for(i = 0U; i < FVID2_MAX_FIELDS; i++)
        {
            for(j = 0U; j < FVID2_MAX_PLANES; j++)
            {
                frm->addr[i][j] = NULL;
            }
        }
        frm->fid          = FVID2_FID_FRAME;
        frm->chNum        = 0U;
        frm->timeStamp    = 0U;
        frm->timeStamp64  = 0U;
        frm->appData      = NULL;
        frm->perFrameCfg  = NULL;
        frm->blankData    = NULL;
        frm->drvData      = NULL;
        frm->subFrameInfo = NULL;
        frm->status       = FVID2_FRAME_STATUS_INIT;
        frm->reserved     = NULL;
    }

    return;
}

static inline void Fvid2FrameList_init(Fvid2_FrameList *fList)
{
    UInt32 i;

    if(NULL != fList)
    {
        for(i = 0U; i < FVID2_MAX_FRAME_PTR; i++)
        {
            fList->frames[i] = NULL;
        }
        fList->numFrames  = 0U;
        fList->perListCfg = NULL;
        fList->drvData    = NULL;
        fList->reserved   = NULL;
        fList->appData    = NULL;
    }

    return;
}

static inline void Fvid2ModeInfo_init(Fvid2_ModeInfo *modeInfo)
{
    if(NULL != modeInfo)
    {
        modeInfo->standard     = FVID2_STD_1080P_60;
        modeInfo->width        = 1920U;
        modeInfo->height       = 1080U;
        modeInfo->scanFormat   = FVID2_SF_PROGRESSIVE;
        modeInfo->pixelClock   = 148500U;
        modeInfo->fps          = 60U;
        modeInfo->hFrontPorch  = 88U;
        modeInfo->hBackPorch   = 148U;
        modeInfo->hSyncLen     = 44U;
        modeInfo->vFrontPorch  = 4U;
        modeInfo->vBackPorch   = 36U;
        modeInfo->vSyncLen     = 5U;
        modeInfo->reserved[0U] = 0U;
        modeInfo->reserved[1U] = 0U;
        modeInfo->reserved[2U] = 0U;
        modeInfo->reserved[3U] = 0U;
    }

    return;
}

static inline void Fvid2CropConfig_init(Fvid2_CropConfig *cropCfg)
{
    if(NULL != cropCfg)
    {
        cropCfg->cropStartX = 0U;
        cropCfg->cropStartY = 0U;
        cropCfg->cropWidth  = 0U;
        cropCfg->cropHeight = 0U;
    }

    return;
}

static inline void Fvid2PosConfig_init(Fvid2_PosConfig *posCfg)
{
    if(NULL != posCfg)
    {
        posCfg->startX = 0U;
        posCfg->startY = 0U;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef FVID2_DATATYPES_H_ */

/* @} */
