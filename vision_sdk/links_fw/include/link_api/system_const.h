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
 *  \ingroup SYSTEM_LINK_API
 *  \defgroup SYSTEM_CONST_API System constants
 *
 *  \brief This module lists the system wide common constants and enums
 *
 * @{
 *
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file system_const.h
 *
 * \brief System wide constants and enums.
 *
 * \version 0.0 (Jun 2013) : [HS] First version
 * \version 0.1 (Jul 2013) : [HS] Updates as per code review comments
 * \version 0.2 (Mar 2015) : [YM] Added SYSTEM_LINK_STATUS_EUNBLOCK
 *
 *******************************************************************************
 */
#ifndef SYSTEM_CONST_H_
#define SYSTEM_CONST_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 * \brief Buffer alignment required across all links
 *  In case of linux kernel 4.4 the buffer needs to be 4k alligned
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#if defined (A15_TARGET_OS_LINUX)
#if defined (A15_TARGET_OS_QNX)
#define SYSTEM_BUFFER_ALIGNMENT         (32U)
#else
#define SYSTEM_BUFFER_ALIGNMENT         (4096U)
#endif
#else
#define SYSTEM_BUFFER_ALIGNMENT         (32U)
#endif
/**
 *******************************************************************************
 *
 * \brief Maximum number of output queues
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_MAX_OUT_QUE              (6U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of channels per output queue
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_MAX_CH_PER_OUT_QUE       (8U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of planes with buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_MAX_PLANES               (3U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of Meta data planes
 *
 *******************************************************************************
 */
#define SYSTEM_MAX_META_DATA_PLANES     (4U)


/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enum for the returns status of the link API.
 *
 *  Link API returns error codes based on failure scenario or success
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_LINK_STATUS_SOK = 0x0,
    /** \brief LINK API call successful. */

    SYSTEM_LINK_STATUS_EFAIL = -(Int32)1,
    /**< LINK API call returned for general failure. Where failure
     *  code doesnt fall into any of the below category
     */

    SYSTEM_LINK_STATUS_ETIMEOUT = -(Int32)2,
    /**< LINK API call returned with error as timed out. Typically API is
     *  waiting for some condition and returned as condition not happened
     *  in the timeout period. */

    SYSTEM_LINK_STATUS_EALLOC = -(Int32)3,
    /**< LINK API call returned with error as allocation failure. Typically
     *  memory or resource allocation failure. */

    SYSTEM_LINK_STATUS_EAGAIN = -(Int32)4,
    /**< LINK API call returned with error as try again. Momentarily API is
     *  not able to service request because of queue full or any other temporary
     *  reason. */

    SYSTEM_LINK_STATUS_EUNSUPPORTED_CMD = -(Int32)5,
    /**< LINK API call returned with unsupported command. Typically when
     *  command is not supported by control API. */

    SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS = -(Int32)6,
    /**< LINK API call returned with error as no more buffers available.
     *  Typically when no buffers are available. */

    SYSTEM_LINK_STATUS_EINVALID_PARAMS = -(Int32)7,
    /**< LINK API call returned with error as invalid parameters. Typically
     *  when parameters passed are not valid or out of range. */

    SYSTEM_LINK_STATUS_EUNBLOCK = -(Int32)8,
    /**< Status used to force unblock the blocking thread.
      *  used by rpmsg based msgq with host communication */

    SYSTEM_LINK_STATUS_EFILE_NO_FILE = -(Int32)9,
    /**< Status used to force unblock the blocking thread.
      *  File with name already exists  */

    SYSTEM_LINK_STATUS_EFILE_NOT_OPEN = -(Int32)10,
    /**< Status used to force unblock the blocking thread.
      *  File NOT opened  */

    SYSTEM_LINK_STATUS_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}System_LinkApiReturnCodes;

/**
 *******************************************************************************
 * \brief Enums for data format.
 *
 *  All data formats may not be supported by all links. For supported data
 *  formats please look link header file.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DF_YUV422I_UYVY = 0x0000,
    /**< YUV 422 Interleaved format - UYVY. */
    SYSTEM_DF_YUV422I_YUYV = 1,
    /**< YUV 422 Interleaved format - YUYV. */
    SYSTEM_DF_YUV422I_YVYU = 2,
    /**< YUV 422 Interleaved format - YVYU. */
    SYSTEM_DF_YUV422I_VYUY = 3,
    /**< YUV 422 Interleaved format - VYUY. */
    SYSTEM_DF_YUV422SP_UV = 4,
    /**< YUV 422 Semi-Planar - Y separate, UV interleaved. */
    SYSTEM_DF_YUV422SP_VU = 5,
    /**< YUV 422 Semi-Planar - Y separate, VU interleaved. */
    SYSTEM_DF_YUV422P = 6,
    /**< YUV 422 Planar - Y, U and V separate. */
    SYSTEM_DF_YUV420SP_UV = 7,
    /**< YUV 420 Semi-Planar - Y separate, UV interleaved. */
    SYSTEM_DF_YUV420SP_VU = 8,
    /**< YUV 420 Semi-Planar - Y separate, VU interleaved. */
    SYSTEM_DF_YUV420P = 9,
    /**< YUV 420 Planar - Y, U and V separate. */
    SYSTEM_DF_YUV444P = 10,
    /**< YUV 444 Planar - Y, U and V separate. */
    SYSTEM_DF_YUV444I = 11,
    /**< YUV 444 interleaved - YUVYUV... */
    SYSTEM_DF_RGB16_565 = 12,
    /**< RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B. */
    SYSTEM_DF_ARGB16_1555 = 13,
    /**< ARGB1555 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha (MSB). */
    SYSTEM_DF_RGBA16_5551 = 14,
    /**< RGBA5551 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha (LSB). */
    SYSTEM_DF_ARGB16_4444 = 15,
    /**< ARGB4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha (MSB). */
    SYSTEM_DF_RGBA16_4444 = 16,
    /**< RGBA4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha (LSB). */
    SYSTEM_DF_RGBX16_4444 = 17,
        /**< RGBX4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Unused  . */
    SYSTEM_DF_ARGB24_6666 = 18,
    /**< ARGB6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha (MSB). */
    SYSTEM_DF_RGBA24_6666 = 19,
    /**< RGBA6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha (LSB). */
    SYSTEM_DF_RGB24_888 = 20,
    /**< RGB24 24-bit - 8-bits R, 8-bits G, 8-bits B. */
    SYSTEM_DF_BGRX_4444 = 21,
    /**<RGBx12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused(LSB).*/
    SYSTEM_DF_XBGR_4444 = 22,
    /**<xRGB12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused(MSB).*/
    SYSTEM_DF_ARGB32_8888 = 23,
    /**< ARGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha (MSB). */
    SYSTEM_DF_XRGB32_8888 = 24,
    /**< XRGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit unused . */
    SYSTEM_DF_RGBA32_8888 = 25,
    /**< RGBA32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha (LSB). */
    SYSTEM_DF_BGR16_565 = 26,
    /**< BGR565 16-bit -   5-bits B, 6-bits G, 5-bits R. */
    SYSTEM_DF_ABGR16_1555 = 27,
    /**< ABGR1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha (MSB). */
    SYSTEM_DF_ABGR16_4444 = 28,
    /**< ABGR4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha (MSB). */
    SYSTEM_DF_BGRA16_5551 = 29,
    /**< BGRA5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha (LSB). */
    SYSTEM_DF_BGRA16_4444 = 30,
    /**< BGRA4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha (LSB). */
    SYSTEM_DF_AGBR16_1555 = 31,
    /**< ABGR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit Alpha (MSB). */
    SYSTEM_DF_AGBR16_4444 = 32,
    /**< ABGR4444 16-bit - 4-bits G, 4-bits B, 4-bits R, 4-bit Alpha (MSB). */
    SYSTEM_DF_XGBR16_1555 = 33,
    /**< XGBR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit unused (MSB). */
    SYSTEM_DF_BGRX16_5551 = 34,
    /**< BGRX5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused (MSB). */
    SYSTEM_DF_ABGR24_6666 = 35,
    /**< ABGR6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha (MSB). */
    SYSTEM_DF_BGR24_888 = 36,
    /**< BGR888 24-bit - 8-bits B, 8-bits G, 8-bits R. */
    SYSTEM_DF_XBGR24_8888 = 37,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused(MSB) */
    SYSTEM_DF_RGBX24_8888 = 38,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused(LSB) */
    SYSTEM_DF_BGRX24_8888 = 39,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused(MSB) */
    SYSTEM_DF_ABGR32_8888 = 40,
    /**< ABGR8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha (MSB). */
    SYSTEM_DF_BGRA24_6666 = 41,
    /**< BGRA6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha (LSB). */
    SYSTEM_DF_BGRA32_8888 = 42,
    /**< BGRA8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha  . */
    SYSTEM_DF_BGRX32_8888 = 43,
    /**< BGRX8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused. */
    SYSTEM_DF_BGRA16_1555 = 44,
    /**< BGRA1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha. */
    SYSTEM_DF_BGRX16_1555 = 45,
    /**< BGRX1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused. */
    SYSTEM_DF_BGRA32_1010102 = 46,
    /**< BGRA1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit Alpha.*/
    SYSTEM_DF_BGRX32_1010102 = 47,
    /**< BGRX1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit unused.*/
    SYSTEM_DF_RGBA32_1010102 = 48,
    /**< RGBA1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit Alpha.*/
    SYSTEM_DF_RGBX32_1010102 = 49,
    /**< RGBX1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit unused.*/
    SYSTEM_DF_BGRA64_16161616 = 50,
    /**< RGBA16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit Alpha.*/
    SYSTEM_DF_BGRX64_16161616 = 51,
    /**< BGRX16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit unused.*/
    SYSTEM_DF_ABGR64_16161616 = 52,
    /**< ABGR16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit Alpha.*/
    SYSTEM_DF_XBGR64_16161616 = 53,
    /**< XBGR16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit unused.*/
    SYSTEM_DF_BITMAP8 = 54,
    /**< BITMAP 8bpp. */
    SYSTEM_DF_BITMAP4_LOWER = 55,
    /**< BITMAP 4bpp lower address in CLUT. */
    SYSTEM_DF_BITMAP4_UPPER = 56,
    /**< BITMAP 4bpp upper address in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET0 = 57,
    /**< BITMAP 2bpp offset 0 in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET1 = 58,
    /**< BITMAP 2bpp offset 1 in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET2 = 59,
    /**< BITMAP 2bpp offset 2 in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET3 = 60,
    /**< BITMAP 2bpp offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET0 = 61,
    /**< BITMAP 1bpp offset 0 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET1 = 62,
    /**< BITMAP 1bpp offset 1 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET2 = 63,
    /**< BITMAP 1bpp offset 2 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET3 = 64,
    /**< BITMAP 1bpp offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET4 = 65,
    /**< BITMAP 1bpp offset 4 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET5 = 66,
    /**< BITMAP 1bpp offset 5 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET6 = 67,
    /**< BITMAP 1bpp offset 6 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET7 = 68,
    /**< BITMAP 1bpp offset 7 in CLUT. */
    SYSTEM_DF_BITMAP8_BGRA32 = 69,
    /**< BITMAP 8bpp BGRA32. */
    SYSTEM_DF_BITMAP4_BGRA32_LOWER = 70,
    /**< BITMAP 4bpp BGRA32 lower address in CLUT. */
    SYSTEM_DF_BITMAP4_BGRA32_UPPER = 71,
    /**< BITMAP 4bpp BGRA32 upper address in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET0 = 72,
    /**< BITMAP 2bpp BGRA32 offset 0 in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET1 = 73,
    /**< BITMAP 2bpp BGRA32 offset 1 in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET2 = 74,
    /**< BITMAP 2bpp BGRA32 offset 2 in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET3 = 75,
    /**< BITMAP 2bpp BGRA32 offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET0 = 76,
    /**< BITMAP 1bpp BGRA32 offset 0 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET1 = 77,
    /**< BITMAP 1bpp BGRA32 offset 1 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET2 = 78,
    /**< BITMAP 1bpp BGRA32 offset 2 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET3 = 79,
    /**< BITMAP 1bpp BGRA32 offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET4 = 80,
    /**< BITMAP 1bpp BGRA32 offset 4 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET5 = 81,
    /**< BITMAP 1bpp BGRA32 offset 5 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET6 = 82,
    /**< BITMAP 1bpp BGRA32 offset 6 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET7 = 83,
    /**< BITMAP 1bpp BGRA32 offset 7 in CLUT. */
    SYSTEM_DF_BAYER_RAW = 84,
    /**< Bayer pattern. */
    SYSTEM_DF_BAYER_GRBG = 85,
    /** < Raw bayer data color pattern
     * G R G R ...
     * B G B G ...
     */
    SYSTEM_DF_BAYER_RGGB = 86,
    /** < Raw bayer data color pattern
     * R G G R ...
     * G B G B ...
     */
    SYSTEM_DF_BAYER_BGGR = 87,
    /** < Raw bayer data color pattern
     * B G B G ...
     * G B G B ...
     */
    SYSTEM_DF_BAYER_GBRG = 88,
    /** < Raw bayer data color pattern
     * G B G B ...
     * R R R G ...
     */
    SYSTEM_DF_RAW_VBI = 89,
    /**< Raw VBI data. */
    SYSTEM_DF_RAW24 = 90,
    /**< 24 bit raw-data. */
    SYSTEM_DF_RAW16 = 91,
    /**< 16 bit raw-data. */
    SYSTEM_DF_RAW08 = 92,
    /**< 8 bit raw-data. */
    SYSTEM_DF_MISC = 93,
    /**< For future purpose. */
    SYSTEM_DF_BITMAP4 = SYSTEM_DF_BITMAP4_LOWER,
    /** BITMAP 4bpp. */
    SYSTEM_DF_BITMAP2 = SYSTEM_DF_BITMAP2_OFFSET0,
    /** BITMAP 2bpp. */
    SYSTEM_DF_BITMAP1 = SYSTEM_DF_BITMAP1_OFFSET0,
    /** BITMAP 1bpp. */
    SYSTEM_DF_RAW06 = 94,
    /**< 6 bit raw-data. */
    SYSTEM_DF_RAW07 = 95,
    /**< 7 bit raw-data. */
    SYSTEM_DF_RAW10 = 96,
    /**< 10 bit raw-data. */
    SYSTEM_DF_RAW12 = 97,
    /**< 12 bit raw-data. */
    SYSTEM_DF_RAW14 = 98,
    /**< 14 bit raw-data. */
    SYSTEM_DF_JPEG1_INTERCHANGE = 99,
    /**< JPEG INTERCHANGE data. */
    SYSTEM_DF_JPEG2_JFIF = 100,
    /**< JPEG2 JFIF data. */
    SYSTEM_DF_JPEG3_EXIF = 101,
    /**< JPEG3 EXIF data. */
    SYSTEM_DF_DPCM_10_8_10_PRED1 = 102,
    /**< DPCM 10-8-10 PRED1 data. */
    SYSTEM_DF_DPCM_10_8_10_PRED2 = 103,
    /**< DPCM 10-8-10 PRED2 data. */
    SYSTEM_DF_DPCM_10_7_10_PRED1 = 104,
    /**< DPCM 10-7-10 PRED1 data. */
    SYSTEM_DF_DPCM_10_7_10_PRED2 = 105,
    /**< DPCM 10-7-10 PRED2 data. */
    SYSTEM_DF_DPCM_10_6_10_PRED1 = 106,
    /**< DPCM 10-6-10 PRED1 data. */
    SYSTEM_DF_DPCM_10_6_10_PRED2 = 107,
    /**< DPCM 10-6-10 PRED2 data. */
    SYSTEM_DF_DPCM_12_8_10_PRED1 = 108,
    /**< DPCM 12-8-10 PRED1 data. */
    SYSTEM_DF_DPCM_12_8_10_PRED2 = 109,
    /**< DPCM 12-8-10 PRED2 data. */
    SYSTEM_DF_DPCM_12_7_10_PRED1 = 110,
    /**< DPCM 12-7-10 PRED1 data. */
    SYSTEM_DF_DPCM_12_7_10_PRED2 = 111,
    /**< DPCM 12-7-10 PRED2 data. */
    SYSTEM_DF_DPCM_12_6_10_PRED1 = 112,
    /**< DPCM 12-6-10 PRED1 data. */
    SYSTEM_DF_DPCM_12_6_10_PRED2 = 113,
    /**< DPCM 12-6-10 PRED2 data. */
    SYSTEM_DF_BGR16_565_A8 = 114,
    /**< BGR565 16-bit - 5-bits B, 6-bits G, 5-bits R.
     *Alpha 8 -bits another plane */
    SYSTEM_DF_RGB16_565_A8 = 115,
    /**< RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B.
     *Alpha 8 -bits another plane */
    SYSTEM_DF_INVALID = 116,
    /**< Invalid data format. Could be used to initialize variables. */
    SYSTEM_DF_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
}System_VideoDataFormat;


/**
 *******************************************************************************
 * \brief Buffer formats enums.
 *
 * Is Buffer a field or frame in memory
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_BUF_FMT_FIELD = 0,
    /**< Buffers are captured/displayed as fields instead of frames */
    SYSTEM_BUF_FMT_FRAME = 1,
    /**< Buffers are captured/displayed as frames instead of frames */
    SYSTEM_BUF_FMT_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_BufferFormat;

/**
 *******************************************************************************
 * \brief Bits per pixel for data formats.
 *
 * Bits per pixel for data formats.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_BPP_BITS1 = 0,
    /**< 1 Bits per Pixel. */
    SYSTEM_BPP_BITS2 = 1,
    /**< 2 Bits per Pixel. */
    SYSTEM_BPP_BITS4 = 2,
    /**< 4 Bits per Pixel. */
    SYSTEM_BPP_BITS8 = 3,
    /**< 8 Bits per Pixel. */
    SYSTEM_BPP_BITS12 = 4,
    /**< 12 Bits per Pixel - used for YUV420 format. */
    SYSTEM_BPP_BITS16 = 5,
    /**< 16 Bits per Pixel. */
    SYSTEM_BPP_BITS24 = 6,
    /**< 24 Bits per Pixel. */
    SYSTEM_BPP_BITS32 = 7,
    /**< 32 Bits per Pixel. */
    SYSTEM_BPP_BITS10 = 8,
    /**< 10 Bits per Pixel. */
    SYSTEM_BPP_BITS7 = 9,
    /**< 7 Bits per Pixel. */
    SYSTEM_BPP_BITS9 = 10,
    /**< 9 Bits per Pixel. */
    SYSTEM_BPP_BITS11 = 11,
    /**< 11 Bits per Pixel. */
    SYSTEM_BPP_BITS13 = 12,
    /**< 13 Bits per Pixel. */
    SYSTEM_BPP_BITS14 = 13,
    /**< 14 Bits per Pixel. */
    SYSTEM_BPP_BITS15 = 14,
    /**< 15 Bits per Pixel. */
    SYSTEM_BPP_BITS20 = 15,
    /**< 20 Bits per Pixel. */
    SYSTEM_BPP_BITS6 = 16,
    /**< 6 Bits per Pixel. */
    SYSTEM_BPP_BITS10_PACKED = 17,
    /**< 12 Bits per Pixel packed */
    SYSTEM_BPP_BITS12_PACKED = 18,
    /**< 12 Bits per Pixel packed */
    SYSTEM_BPP_BITS14_PACKED = 19,
    /**< 12 Bits per Pixel packed */
    SYSTEM_BPP_BITS12_PACKED_MIPI = 20,
    /**< 12Bits per pixel stored in MIPI format */

    SYSTEM_BPP_MAX = 21,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_BPP_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_BitsPerPixel;

/**
 *******************************************************************************
 * \brief Enums for frames per second
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_FPS_85 = 0,
    /**< 85 frames per second. */
    SYSTEM_FPS_75 = 1,
    /**< 75 frames per second. */
    SYSTEM_FPS_72 = 2,
    /**< 72 frames per second. */
    SYSTEM_FPS_70 = 3,
    /**< 70 frames per second. */
    SYSTEM_FPS_60 = 4,
    /**< 60 frames per second. */
    SYSTEM_FPS_50 = 5,
    /**< 50 frames per second. */
    SYSTEM_FPS_30 = 6,
    /**< 30 frames per second. */
    SYSTEM_FPS_25 = 7,
    /**< 25 frames per second. */
    SYSTEM_FPS_24 = 8,
    /**< 24 frames per second. */
    SYSTEM_FPS_15 = 9,
    /**< 15 frames per second. */
    SYSTEM_FPS_10 = 10,
    /**< 10 frames per second. */
    SYSTEM_FPS_5 = 11,
    /**< 5 frames per second. */
    SYSTEM_FPS_MAX = 12,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_FPS_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_VideoFrameRate;

/**
 *******************************************************************************
 * \brief Enums for frames status. Used to indicate the status of the frame
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_FRAME_STATUS_COMPLETED = 1,
    /**< Frame processing is completed and can be used further */
    SYSTEM_FRAME_STATUS_ABORTED = 5,
    /**< Frame processing is aborted, used for the frames which are not to be
     *   processed */
    SYSTEM_FRAME_STATUS_OVERFLOW = 6,
    /**< The IP processing this frame experienced and overflow of its internal
            buffers. Indicates severe error */
    SYSTEM_FRAME_STATUS_ECC_CORRECTED = 7,
    /**< There was 1 bit ECC error, which was corrected.
            Provided the hardware and/or protocol used to process this frame
            supports ECC */
    SYSTEM_FRAME_STATUS_CRC_ERROR = 8,
    /**< CRC errors were detected, the integrity of the data is not guaranteed.
            Provided the hardware and/or protocol used to process this frame
            supports CRC */
    SYSTEM_FRAME_STATUS_ECC_ERROR = 9,
    /**< There were multiple bit ECC error, which was could not be corrected.
            Provided the hardware and/or protocol used to process this frame
            supports ECC */
    SYSTEM_FRAME_STATUS_MAX = 10
    /**< This should be the last number, */
} System_VideoFrameStatus;

/**
 *******************************************************************************
 * \brief Enum for Field/Format
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_SF_INTERLACED = 0,
    /**< Interlaced mode. */
    SYSTEM_SF_PROGRESSIVE = 1,
    /**< Progressive mode. */
    SYSTEM_SF_MAX = 2,
    /**< Should be the last value of this enumeration.
         Will be used by driver for validating the input parameters. */
    SYSTEM_SF_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_VideoScanFormat;

/**
 *******************************************************************************
 * \brief Enum for Tiled v/s Non Tiled memory
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_MT_NONTILEDMEM = 0,
    /**< 1D non-tiled memory. */
    SYSTEM_MT_TILEDMEM = 1,
    /**< 2D tiled memory. */
    SYSTEM_MT_MAX = 2,
    /**< Should be the last value of this enumeration.
         Will be used by driver for validating the input parameters. */
    SYSTEM_MT_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_MemoryType;

/**
 *******************************************************************************
 * \brief Enums for standard resolution
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_STD_NTSC = 0,
    /**< 720x480 30FPS interlaced NTSC standard. */
    SYSTEM_STD_PAL = 1,
    /**< 720x576 30FPS interlaced PAL standard. */

    SYSTEM_STD_480I = 2,
    /**< 720x480 30FPS interlaced SD standard. */
    SYSTEM_STD_576I = 3,
    /**< 720x576 30FPS interlaced SD standard. */

    SYSTEM_STD_CIF = 4,
    /**< Interlaced, 360x120 per field NTSC, 360x144 per field PAL. */
    SYSTEM_STD_HALF_D1 = 5,
    /**< Interlaced, 360x240 per field NTSC, 360x288 per field PAL. */
    SYSTEM_STD_D1 = 6,
    /**< Interlaced, 720x240 per field NTSC, 720x288 per field PAL. */

    SYSTEM_STD_480P = 7,
    /**< 720x480 60FPS progressive ED standard. */
    SYSTEM_STD_576P = 8,
    /**< 720x576 60FPS progressive ED standard. */

    SYSTEM_STD_720P_60 = 9,
    /**< 1280x720 60FPS progressive HD standard. */
    SYSTEM_STD_720P_50 = 10,
    /**< 1280x720 50FPS progressive HD standard. */

    SYSTEM_STD_1080I_60 = 11,
    /**< 1920x1080 30FPS interlaced HD standard. */
    SYSTEM_STD_1080I_50 = 12,
    /**< 1920x1080 50FPS interlaced HD standard. */

    SYSTEM_STD_1080P_60 = 13,
    /**< 1920x1080 60FPS progressive HD standard. */
    SYSTEM_STD_1080P_50 = 14,
    /**< 1920x1080 50FPS progressive HD standard. */

    SYSTEM_STD_1080P_24 = 15,
    /**< 1920x1080 24FPS progressive HD standard. */
    SYSTEM_STD_1080P_30 = 16,
    /**< 1920x1080 30FPS progressive HD standard. */

    /* Vesa standards from here Please add all SMTPE and CEA standard enums
     * above this only. this is to ensure proxy Oses compatibility
     */
    SYSTEM_STD_VGA_60 = 17,
    /**< 640x480 60FPS VESA standard. */
    SYSTEM_STD_VGA_72 = 18,
    /**< 640x480 72FPS VESA standard. */
    SYSTEM_STD_VGA_75 = 19,
    /**< 640x480 75FPS VESA standard. */
    SYSTEM_STD_VGA_85 = 20,
    /**< 640x480 85FPS VESA standard. */

    SYSTEM_STD_WVGA_60 = 21,
    /**< 800x480 60PFS WVGA */

    SYSTEM_STD_SVGA_60 = 22,
    /**< 800x600 60FPS VESA standard. */
    SYSTEM_STD_SVGA_72 = 23,
    /**< 800x600 72FPS VESA standard. */
    SYSTEM_STD_SVGA_75 = 24,
    /**< 800x600 75FPS VESA standard. */
    SYSTEM_STD_SVGA_85 = 25,
    /**< 800x600 85FPS VESA standard. */

    SYSTEM_STD_WSVGA_70 = 26,
    /**< 1024x600 70FPS standard. */

    SYSTEM_STD_XGA_60 = 27,
    /**< 1024x768 60FPS VESA standard. */
    SYSTEM_STD_XGA_DSS_TDM_60 = 28,
    /**< 1024x768 60FPS VESA standard. Applicable for
      *  DSS in 8-bit TDM mode.*/
    SYSTEM_STD_XGA_70 = 29,
    /**< 1024x768 72FPS VESA standard. */
    SYSTEM_STD_XGA_75 = 30,
    /**< 1024x768 75FPS VESA standard. */
    SYSTEM_STD_XGA_85 = 31,
    /**< 1024x768 85FPS VESA standard. */

    SYSTEM_STD_1368_768_60 = 32,
    /**< 1368x768 60 PFS VESA. */
    SYSTEM_STD_1366_768_60 = 33,
    /**< 1366x768 60 PFS VESA. */
    SYSTEM_STD_1360_768_60 = 34,
    /**< 1360x768 60 PFS VESA. */

    SYSTEM_STD_WXGA_30 = 35,
    /**< 1280x800 30FPS VESA standard. */
    SYSTEM_STD_WXGA_60 = 36,
    /**< 1280x800 60FPS VESA standard. */
    SYSTEM_STD_WXGA_75 = 37,
    /**< 1280x800 75FPS VESA standard. */
    SYSTEM_STD_WXGA_85 = 38,
    /**< 1280x800 85FPS VESA standard. */

    SYSTEM_STD_1440_900_60 = 39,
    /**< 1440x900 60 PFS VESA>*/

    SYSTEM_STD_SXGA_60 = 40,
    /**< 1280x1024 60FPS VESA standard. */
    SYSTEM_STD_SXGA_75 = 41,
    /**< 1280x1024 75FPS VESA standard. */
    SYSTEM_STD_SXGA_85 = 42,
    /**< 1280x1024 85FPS VESA standard. */

    SYSTEM_STD_WSXGAP_60 = 43,
    /**< 1680x1050 60 PFS VESA>*/

    SYSTEM_STD_SXGAP_60 = 44,
    /**< 1400x1050 60FPS VESA standard. */
    SYSTEM_STD_SXGAP_75 = 45,
    /**< 1400x1050 75FPS VESA standard. */

    SYSTEM_STD_UXGA_60 = 46,
    /**< 1600x1200 60FPS VESA standard. */

    /* Multi channel standards from here Please add all VESA standards enums
     * above this only. this is to ensure proxy Oses compatibility
     */
    SYSTEM_STD_MUX_2CH_D1 = 47,
    /**< Interlaced, 2Ch D1, NTSC or PAL. */
    SYSTEM_STD_MUX_2CH_HALF_D1 = 48,
    /**< Interlaced, 2ch half D1, NTSC or PAL. */
    SYSTEM_STD_MUX_2CH_CIF = 49,
    /**< Interlaced, 2ch CIF, NTSC or PAL. */
    SYSTEM_STD_MUX_4CH_D1 = 50,
    /**< Interlaced, 4Ch D1, NTSC or PAL. */
    SYSTEM_STD_MUX_4CH_CIF = 51,
    /**< Interlaced, 4Ch CIF, NTSC or PAL. */
    SYSTEM_STD_MUX_4CH_HALF_D1 = 52,
    /**< Interlaced, 4Ch Half-D1, NTSC or PAL. */
    SYSTEM_STD_MUX_8CH_CIF = 53,
    /**< Interlaced, 8Ch CIF, NTSC or PAL. */
    SYSTEM_STD_MUX_8CH_HALF_D1 = 54,
    /**< Interlaced, 8Ch Half-D1, NTSC or PAL. */

    SYSTEM_STD_WXGA_5x3_30 = 55,
    /**< WXGA standard (1280x768) with the aspect ratio 5:3 at 30FPS. */
    SYSTEM_STD_WXGA_5x3_60 = 56,
    /**< WXGA resolution (1280x768) with the aspect ratio 5:3 at 60FPS. */
    SYSTEM_STD_WXGA_5x3_75 = 57,
    /**< WXGA resolution (1280x768) with the aspect ratio 5:3 at 75FPS. */

    /* Auto detect and Custom standards Please add all multi channel standard
     * enums above this only. this is to ensure proxy Oses compatibility
     */
    SYSTEM_STD_AUTO_DETECT = 58,
    /**< Auto-detect standard. Used in capture mode. */
    SYSTEM_STD_CUSTOM = 59,
    /**< Custom standard used when connecting to external LCD etc...
     *   The video timing is provided by the application.
     *   Used in display mode. */
    SYSTEM_STD_INVALID = 60,

    SYSTEM_STD_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_Standard;

/**
 *******************************************************************************
 * \brief Enums for how many bits are interfaced with VIP capture
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_VIFW_8BIT = 0,
    /**< 8-bit interface. */
    SYSTEM_VIFW_10BIT = 1,
    /**< 10-bit interface. */
    SYSTEM_VIFW_12BIT = 2,
    /**< 12-bit interface. */
    SYSTEM_VIFW_14BIT = 3,
    /**< 14-bit interface. */
    SYSTEM_VIFW_16BIT = 4,
    /**< 16-bit interface. */
    SYSTEM_VIFW_18BIT = 5,
    /**< 18-bit interface. */
    SYSTEM_VIFW_20BIT = 6,
    /**< 20-bit interface. */
    SYSTEM_VIFW_24BIT = 7,
    /**< 24-bit interface. */
    SYSTEM_VIFW_30BIT = 8,
    /**< 30-bit interface. */
    SYSTEM_VIFW_1LANES = 9,
    /**< CSI2 specific - 1 data lanes */
    SYSTEM_VIFW_2LANES = 10,
    /**< CSI2 specific - 2 data lanes */
    SYSTEM_VIFW_3LANES = 11,
    /**< CSI2 specific - 3 data lanes */
    SYSTEM_VIFW_4LANES = 12,
    /**< CSI2 / LVDS specific - 4 data lanes */
    SYSTEM_VIFW_MAX = 13,
    /**< Maximum modes */
    SYSTEM_VIFW_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_VideoIfWidth;

/**
 *******************************************************************************
 * \brief How sensor/decoder is interfaced with VIP capture port
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_VIFM_SCH_ES = 0,
    /**< Single Channel non multiplexed mode. */
    SYSTEM_VIFM_MCH_LINE_MUX_ES = 1,
    /**< Multi-channel line-multiplexed mode. */
    SYSTEM_VIFM_MCH_PIXEL_MUX_ES = 2,
    /**< Multi-channel pixel muxed. */
    SYSTEM_VIFM_SCH_DS_HSYNC_VBLK = 3,
    /**< Single Channel non multiplexed discrete sync mode with HSYNC and
     *   VBLK as control signals. */
    SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC = 4,
    /**< Single Channel non multiplexed discrete sync mode with HSYNC and
     *   VSYNC as control signals. */
    SYSTEM_VIFM_SCH_DS_AVID_VBLK = 5,
    /**< Single Channel non multiplexed discrete sync mode with AVID and
     *   VBLK as control signals. */
    SYSTEM_VIFM_SCH_DS_AVID_VSYNC = 6,
    /**< Single Channel non multiplexed discrete sync mode with AVID and
     *   VBLK as control signals. */
    SYSTEM_VIFM_MCH_LINE_MUX_SPLIT_LINE_ES = 7,
    /**< Multi-channel line-multiplexed mode - split line mode. */
    SYSTEM_VIFM_SCH_CSI2 = 8,
    /**< Single channel capture via CSI2 interface */
    SYSTEM_VIFM_SCH_LVDS = 9,
    /**< Single channel capture via LVDS interface */
    SYSTEM_VIFM_SCH_CPI = 10,
    /**< Single channel capture via Parallel interface */
    SYSTEM_VIFM_MAX = 11,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_VIFM_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_VideoIfMode;


/**
 *******************************************************************************
 * \brief Capture mode of buffer. How buffers will be looping around between
 *        driver and application.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_CAPT_BCM_FRM_DROP = 0,
    /**< In this mode the driver will stop capturing data when there are
     *   no more buffers at the input queue.
     *   The driver will not hold any buffer with it and the last buffer
     *   will be returned to the application through dequeue call.
     *   For this mode, the driver makes use of the VPDMA drop data feature. */
    SYSTEM_CAPT_BCM_LAST_FRM_REPEAT = 1,
    /**< In this mode the driver will keep capturing the data to the last
     *   queued buffer when there are no more buffers at the input queue.
     *   The driver will hold the last buffer with it till the application
     *   queues any new buffer or the capture is stopped. */
    SYSTEM_CAPT_BCM_CIRCULAR_FRM_REPEAT = 2,
    /**< In this mode the driver will keep reusing all the sets of buffer
     *   with it in a circular fashion.
     *   Application cannot get back any buffer from the driver when streaming
     *   is on and dequeue call will result in error. */
    SYSTEM_CAPT_BCM_MAX = 3,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_CAPT_BCM_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_CaptBufferCaptMode;

/**
 *******************************************************************************
 * \brief Enum for buffer Field ID
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_FID_TOP = 0,
    /**< Top field. */
    SYSTEM_FID_BOTTOM = 1,
    /**< Bottom field. */
    SYSTEM_FID_FRAME = 2,
    /**< Frame mode - Contains both the fields or a progressive frame. */
    SYSTEM_FID_MAX = 3,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_FID_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_Fid;

/**
 *******************************************************************************
 * \brief Enum for signal polarity
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_POL_LOW = 0,
    /**< Low Polarity. */
    SYSTEM_POL_HIGH = 1,
    /**< High Polarity. */
    SYSTEM_POL_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
     SYSTEM_POL_FORCE32BITS = 0x7FFFFFFF
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} System_Polarity;

/**
 *******************************************************************************
 * \brief  Enum for sampling edge for signal.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_EDGE_POL_RISING = 0,
    /**< Rising Edge. */
    SYSTEM_EDGE_POL_FALLING = 1,
    /**< Falling Edge. */
    SYSTEM_EDGE_POL_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
     SYSTEM_EDGE_POL_FORCE32BITS = 0x7FFFFFFF
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} System_EdgePolarity;

/**
 *******************************************************************************
 *  \brief This defines the standard coefficient sets available for
 *  different scaling ratios.
 *
 *  IMP: Do not assign numerical values to enum here.
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_SC_DS_SET_ANTI_FLICKER = 0,
    /**< Coefficient for anti-flicker effect */
    SYSTEM_SC_DS_SET_3_16 = 1,
    /**< Coefficient for down sampling 0.1875(3/16) <Factor<= 0.25(4/16). */
    SYSTEM_SC_DS_SET_4_16 = 2,
    /**< Coefficient for down sampling 0.25(4/16) <Factor<= 0.3125(5/16). */
    SYSTEM_SC_DS_SET_5_16 = 3,
    /**< Coefficient for down sampling 0.3125(5/16) <Factor<= 0.375(6/16). */
    SYSTEM_SC_DS_SET_6_16 = 4,
    /**< Coefficient for down sampling 0.375(6/16) <Factor<= 0.4375(7/16). */
    SYSTEM_SC_DS_SET_7_16 = 5,
    /**< Coefficient for down sampling 0.4375(7/16) <Factor<= 0.5(8/16). */
    SYSTEM_SC_DS_SET_8_16 = 6,
    /**< Coefficient for down sampling 0.5(8/16) <Factor<= 0.5625(9/16). */
    SYSTEM_SC_DS_SET_9_16 = 7,
    /**< Coefficient for down sampling 0.5625(9/16) <Factor<= 0.625(10/16). */
    SYSTEM_SC_DS_SET_10_16 = 8,
    /**< Coefficient for down sampling 0.625(10/16) <Factor<= 0.6875(11/16). */
    SYSTEM_SC_DS_SET_11_16 = 9,
    /**< Coefficient for down sampling 0.6875(11/16) <Factor<= 0.75(12/16). */
    SYSTEM_SC_DS_SET_12_16 = 10,
    /**< Coefficient for down sampling 0.75(12/16) <Factor<= 0.8125(13/16). */
    SYSTEM_SC_DS_SET_13_16 = 11,
    /**< Coefficient for down sampling 0.8125(13/16) <Factor<= 0.875(14/16). */
    SYSTEM_SC_DS_SET_14_16 = 12,
    /**< Coefficient for down sampling 0.875(14/16) <Factor<= 0.9375(15/16). */
    SYSTEM_SC_DS_SET_15_16 = 13,
    /**< Coefficient for down sampling 0.9375(15/16) < Factor< 1(16/16) */
    SYSTEM_SC_US_SET = 14,
    /**< Coefficient set for the upsampling.  Includes horizontal, vertical
     *   and both chroma and luma up sampling. */
    SYSTEM_SC_SET_1_1 = 15,
    /**< Coefficient set for one-to-one scenario, when scaler is not in
     *   bypass. */
    SYSTEM_SC_SET_MAX = 16,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
     SYSTEM_SC_SET_FORCE32BITS = 0x7FFFFFFF
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} System_ScCoeffSet;


/**
 *******************************************************************************
 * \brief Type of System buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum  {

    SYSTEM_BUFFER_TYPE_VIDEO_FRAME = 0,
    /**< Video frame buffer */

    SYSTEM_BUFFER_TYPE_BITSTREAM = 1,
    /**< Bitstream buffer */

    SYSTEM_BUFFER_TYPE_METADATA = 2,
    /**< Metadata buffer */

    SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER = 3,
    /**< Group of 'synced' video frames buffer across N channels */

    SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME = 4,
    /**< Pixmap Video frame buffer */

    SYSTEM_BUFFER_TYPE_FORCE32BITS = 0x7FFFFFFF
    /**< to force enum as 32-bit size */

} System_BufferType;

/**
 *******************************************************************************
 * \brief Type of bitstream
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum {

    SYSTEM_BITSTREAM_CODING_TYPE_MJPEG = 0,
    /**< MJPEG coding */

    SYSTEM_BITSTREAM_CODING_TYPE_H264 = 1,
    /**< H264 coding */

    SYSTEM_BITSTREAM_CODING_TYPE_FORCE32BITS = 0x7FFFFFFF
    /**< to force enum as 32-bit size */

} System_BitstreamCodingType;

/**
 *******************************************************************************
 * \brief Video type for encoder / decoder links
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum {
    SYSTEM_IVIDEO_MPEG1 = 1,
    /**< Video format is Mpeg1 stream */
    SYSTEM_IVIDEO_MPEG2SP = 2,
    /**< Video format is Mpeg2/H.262 stream, Simple Profile */
    SYSTEM_IVIDEO_MPEG2MP = 3,
    /**< Video format is Mpeg2/H.262 stream, Main Profile */
    SYSTEM_IVIDEO_MPEG2HP = 4,
    /**< Video format is Mpeg2/H.262 stream, High Profile */
    SYSTEM_IVIDEO_MPEG4SP = 5,
    /**< Video format is Mpeg4 stream, Simple Profile */
    SYSTEM_IVIDEO_MPEG4ASP = 6,
    /**< Video format is Mpeg4 stream, Advanced Simple Profile */
    SYSTEM_IVIDEO_H264BP = 7,
    /**< Video format is H.264 stream, Base Profile */
    SYSTEM_IVIDEO_H264MP = 8,
    /**< Video format is H.264 stream, Main Profile */
    SYSTEM_IVIDEO_H264HP = 9,
    /**< Video format is H.264 stream, High Profile */
    SYSTEM_IVIDEO_VC1SP = 10,
     /**< Video format is VC1/WMV9 stream, Simple Profile */
    SYSTEM_IVIDEO_VC1MP = 11,
    /**< Video format is VC1/WMV9 stream, Main Profile */
    SYSTEM_IVIDEO_VC1AP = 12,
    /**< Video format is VC1 stream, Advanced Profile */
    SYSTEM_IVIDEO_H264RCDO = 13,
    /**< Video format is H.264 stream, Fast profile/RCDO */
    SYSTEM_IVIDEO_RV8 = 14,
    /**< Video format is Real Video 8 stream */
    SYSTEM_IVIDEO_RV9 = 15,
    /**< Video format is Real Video 9 stream */
    SYSTEM_IVIDEO_RV10 = SYSTEM_IVIDEO_RV9,
    /**< Video format is Real Video 10 stream, same as RV9 */
    SYSTEM_IVIDEO_ON2VP6 = 16,
    /**< Video format is ON2, VP6.x */
    SYSTEM_IVIDEO_ON2VP7 = 17,
    /**< Video format is ON2, VP7.x */
    SYSTEM_IVIDEO_AVS10 = 18,
    /**< Video format is AVS 1.0 */
    SYSTEM_IVIDEO_SORENSONSPARK = 19,
    /**< Video format is SorensonSpark V0/V1 */
    SYSTEM_IVIDEO_H263_PROFILE0 = 20,
    /**< Video format is H263 Base line profile */
    SYSTEM_IVIDEO_H263_PROFILE3 = 21,
    /**< Video format is H263 and Annex IJKT */
    SYSTEM_IVIDEO_H264SVC = 22,
    /**< Video format is SVC */
    SYSTEM_IVIDEO_MULTIVIEW = 23,
    /**< Video format is Multiview coding */
    SYSTEM_IVIDEO_MJPEG = 24,
    /**< Video format is motion JPEG */
    SYSTEM_IVIDEO_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_IVideoFormat;

/**
 *******************************************************************************
 * \brief Video frame types for encoder / decoder links
 *
 *        For the various @c IVIDEO_xy_FRAME values, this frame type is
 *        interlaced where both top and bottom fields are
 *        provided in a single frame.  The first field is an "x"
 *        frame, the second field is "y" field.
 *
 *******************************************************************************
*/

typedef enum {
    SYSTEM_IVIDEO_NA_FRAME = -(Int32)1,
    /**< Frame type not available. */
    SYSTEM_IVIDEO_I_FRAME = 0,
    /**< Intra coded frame. */
    SYSTEM_IVIDEO_P_FRAME = 1,
    /**< Forward inter coded frame. */
    SYSTEM_IVIDEO_B_FRAME = 2,
    /**< Bi-directional inter coded frame. */
    SYSTEM_IVIDEO_IDR_FRAME = 3,
    /**< Intra coded frame that can be used for
     *   refreshing video content.
     */
    SYSTEM_IVIDEO_II_FRAME = 4,
    /**< Interlaced Frame, both fields are I frames
      */
    SYSTEM_IVIDEO_IP_FRAME = 5,
    /**< Interlaced Frame, first field is an I frame,
      *   second field is a P frame.
      */
    SYSTEM_IVIDEO_IB_FRAME = 6,
    /**< Interlaced Frame, first field is an I frame,
      *   second field is a B frame.
      */
    SYSTEM_IVIDEO_PI_FRAME = 7,
    /**< Interlaced Frame, first field is a P frame,
      *   second field is a I frame.
      */
    SYSTEM_IVIDEO_PP_FRAME = 8,
    /**< Interlaced Frame, both fields are P frames.
      */
    SYSTEM_IVIDEO_PB_FRAME = 9,
    /**< Interlaced Frame, first field is a P frame,
      *   second field is a B frame.
      */
    SYSTEM_IVIDEO_BI_FRAME = 10,
    /**< Interlaced Frame, first field is a B frame,
      *   second field is an I frame.
      */
    SYSTEM_IVIDEO_BP_FRAME = 11,
    /**< Interlaced Frame, first field is a B frame,
      *   second field is a P frame.
      */
    SYSTEM_IVIDEO_BB_FRAME = 12,
    /**< Interlaced Frame, both fields are B frames.
     */
    SYSTEM_IVIDEO_MBAFF_I_FRAME = 13,
    /**< Intra coded MBAFF frame.
     */
    SYSTEM_IVIDEO_MBAFF_P_FRAME = 14,
    /**< Forward inter coded MBAFF frame.
     */
    SYSTEM_IVIDEO_MBAFF_B_FRAME = 15,
    /**< Bi-directional inter coded MBAFF frame.
     */
    SYSTEM_IVIDEO_MBAFF_IDR_FRAME = 16,
    /**< Intra coded MBAFF frame that can be used
      *   for refreshing video content.
      */
    /** Default setting. */
    SYSTEM_IVIDEO_FRAMETYPE_DEFAULT = SYSTEM_IVIDEO_I_FRAME,

    SYSTEM_IVIDEO_FRAMETYPE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_IVideoFrameType;

/**
 *******************************************************************************
 * \brief Video content types for encoder / decoder links
 *******************************************************************************
*/

typedef enum {
    SYSTEM_IVIDEO_CONTENTTYPE_NA = -(Int32)1,
    /**< Frame type is not available. */
    SYSTEM_IVIDEO_PROGRESSIVE = 0,
    /**< Progressive frame. */
    SYSTEM_IVIDEO_PROGRESSIVE_FRAME = SYSTEM_IVIDEO_PROGRESSIVE,
    /**< Progressive Frame. */
    SYSTEM_IVIDEO_INTERLACED = 1,
    /**< Interlaced frame. */
    SYSTEM_IVIDEO_INTERLACED_FRAME = SYSTEM_IVIDEO_INTERLACED,
    /**< Interlaced frame. */
    SYSTEM_IVIDEO_INTERLACED_TOPFIELD = 2,
    /**< Interlaced picture, top field. */
    SYSTEM_IVIDEO_INTERLACED_BOTTOMFIELD = 3,
    /**< Interlaced picture, bottom field. */
    /**Default setting. */
    SYSTEM_IVIDEO_CONTENTTYPE_DEFAULT = SYSTEM_IVIDEO_PROGRESSIVE,
    SYSTEM_IVIDEO_CONTENTTYPE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_IVideoContentType;

/**
 *******************************************************************************
 * \brief Encoding Preset for the enclink
 *******************************************************************************
*/

typedef enum {
    SYSTEM_XDM_DEFAULT = 0,
    /**< Default setting of encoder.
     *   See codec specific documentation for its encoding behaviour.
     */
    SYSTEM_XDM_HIGH_QUALITY = 1,
    /**< High quality encoding. */
    SYSTEM_XDM_HIGH_SPEED = 2,
    /**< High speed encoding. */
    SYSTEM_XDM_USER_DEFINED = 3,
    /**< User defined configuration, using advanced parameters.*/
    SYSTEM_XDM_HIGH_SPEED_MED_QUALITY = 4,
     /**< High speed, medium quality encoding */
    SYSTEM_XDM_MED_SPEED_MED_QUALITY = 5,
    /**< Medium speed, medium quality encoding*/
    SYSTEM_XDM_MED_SPEED_HIGH_QUALITY = 6,
    /**< Medium speed, high quality encoding */
    SYSTEM_XDM_ENCODING_PRESET_MAX  = 7,
    SYSTEM_XDM_PRESET_DEFAULT = SYSTEM_XDM_MED_SPEED_MED_QUALITY
    /**< Default setting of encoder.
     *   See codec specific documentation for its encoding behaviour.
     */
} System_XDMEncodingPreset;

/**
 *******************************************************************************
 * \brief Rate control preset for the encoder
 *******************************************************************************
*/

typedef enum {
    SYSTEM_IVIDEO_LOW_DELAY = 1,
    /**< CBR rate control for video conferencing. */
    SYSTEM_IVIDEO_STORAGE = 2,
    /**< VBR rate control for local storage (DVD) recording */
    SYSTEM_IVIDEO_TWOPASS = 3,
    /**< Two pass rate control for non real time applications. */
    SYSTEM_IVIDEO_NONE = 4,
    /**< No configurable video rate control mechanism. */
    SYSTEM_IVIDEO_USER_DEFINED = 5,
    /**< User defined configuration using extended parameters. */
    SYSTEM_IVIDEO_RATECONTROLPRESET_DEFAULT = SYSTEM_IVIDEO_LOW_DELAY
    /** Default setting. */
} System_IVideoRateControlPreset;

/**
 *******************************************************************************
 * \brief Motion Vector accuracy for the encoder link
 *******************************************************************************
*/

typedef enum {
    SYSTEM_IVIDENC2_MOTIONVECTOR_PIXEL = 0,
    /**< Motion vectors accuracy is only integer pel. */
    SYSTEM_IVIDENC2_MOTIONVECTOR_HALFPEL = 1,
    /**< Motion vectors accuracy is half pel. */
    SYSTEM_IVIDENC2_MOTIONVECTOR_QUARTERPEL = 2,
    /**< Motion vectors accuracy is quarter pel. */
    SYSTEM_IVIDENC2_MOTIONVECTOR_EIGHTHPEL = 3,
    /**< Motion vectors accuracy is one-eighth pel. */
    SYSTEM_IVIDENC2_MOTIONVECTOR_MAX = 4
    /**< Motion vectors accuracy is not defined */
} System_IVidenc2MotionVectorAccuracy;


/**
 *******************************************************************************
 *  \brief CSI2 Data types.
 *******************************************************************************
 */
typedef enum
{
    SYSTEM_CSI2_YUV420_8B = 0x18,
    /**< YUV 4:2:0 with 8bit for each Y/U/V */
    SYSTEM_CSI2_YUV420_10B = 0x19,
    /**< YUV 4:2:0 with 10bit for each Y/U/V */
    SYSTEM_CSI2_YUV420_8B_LEGACY = 0x1A,
    /**< YUV 4:2:0 with 8bit for each Y/U/V */
    SYSTEM_CSI2_YUV420_8B_CHROMA_SHIFT = 0x1C,
    /**< YUV 4:2:0 with 8bit for each Y/U/V with
     *   with phase shifted chroma */
    SYSTEM_CSI2_YUV420_10B_CHROMA_SHIFT = 0x1D,
    /**< YUV 4:2:0 with 10bit for each Y/U/V with
     *   with phase shifted chroma */
    SYSTEM_CSI2_YUV422_8B = 0x1E,
    /**< YUV 4:2:2 with 8bit for each Y/U/V */
    SYSTEM_CSI2_YUV422_10B = 0x1F,
    /**< YUV 4:2:2 with 10bit for each Y/U/V */
    SYSTEM_CSI2_RGB444 = 0x20,
    /**< RGB888 - 4-bits B, 4-bits G, 4-bits R */
    SYSTEM_CSI2_RGB555 = 0x21,
    /**< RGB888 - 5-bits B, 5-bits G, 5-bits R */
    SYSTEM_CSI2_RGB565 = 0x22,
    /**< RGB888 - 5-bits B, 6-bits G, 5-bits R */
    SYSTEM_CSI2_RGB666 = 0x23,
    /**< RGB888 - 6-bits B, 6-bits G, 6-bits R */
    SYSTEM_CSI2_RGB888 = 0x24,
    /**< RGB888 - 8-bits B, 8-bits G, 8-bits R */
    SYSTEM_CSI2_RAW6 = 0x28,
    /**< 6 bit raw-data. */
    SYSTEM_CSI2_RAW7 = 0x29,
    /**< 7 bit raw-data. */
    SYSTEM_CSI2_RAW8 = 0x2A,
    /**< 8 bit raw-data. */
    SYSTEM_CSI2_RAW10 = 0x2B,
    /**< 10 bit raw-data. */
    SYSTEM_CSI2_RAW12 = 0x2C,
    /**< 12 bit raw-data. */
    SYSTEM_CSI2_RAW14 = 0x2D,
    /**< 14 bit raw-data. */
    SYSTEM_CSI2_ANY = 0x01,
    /**< Allow any data type for capture */
    SYSTEM_CSI2_DISABLE_CONTEXT = 0x00,
    /**< Disable context */
    SYSTEM_CSI2_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} System_Csi2DataFormat;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
