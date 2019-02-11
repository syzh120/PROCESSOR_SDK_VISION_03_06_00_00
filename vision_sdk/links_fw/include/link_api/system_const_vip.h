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
 *  \brief This module lists the VIP port specific constants and enums
 *
 * @{
 *
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file system_const_vip.h
 *
 * \brief VIP system constants and enums
 *
 * \version 0.0 (Jun 2013) : [HS] First version
 * \version 0.1 (Jul 2013) : [HS] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef SYSTEM_CONST_VIP_H_
#define SYSTEM_CONST_VIP_H_

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
 * \brief Capture instance - VIP1 - Slice1 Port A
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA (0u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP1 - Slice1 Port B
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB (1u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP1 - Slice2 Port A
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA (2u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP1 - Slice1 Port B
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB (3u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP2 - Slice1 Port A
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA (4u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP2 - Slice1 Port B
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTB (5u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP2 - Slice2 Port A
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTA (6u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP2 - Slice2 Port B
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB (7u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP3 - Slice1 Port A
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA (8u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP3 - Slice1 Port B
 *
 * NOT SUPPORTED in any platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTB (9u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP3 - Slice3 Port A
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA (10u)

/**
 *******************************************************************************
 *
 * \brief Capture instance - VIP3 - Slice2 Port A
 *
 * NOT SUPPORTED in any platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTB (11u)


/**
 *******************************************************************************
 *
 * \brief Capture instance - MAX instances
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SYSTEM_CAPTURE_VIP_INST_MAX         (10U)
#define SYSTEM_CAPTURE_DSSWB_INST_MAX       (1U)

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
 * \brief Enum for Vip Sync Type
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
/**
 *  enum System_VipParserSyncType.
 *  \brief Enum for Vip Sync Type.
 */
typedef enum
{
    SYSTEM_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV = 0,
    /**< Embedded sync single 4:2:2 YUV stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_2X_422_YUV = 1,
    /**< Embedded sync 2x multiplexed 4:2:2 YUV stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_4X_422_YUV = 2,
    /**< Embedded sync 4x multiplexed 4:2:2 YUV stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_LINE_YUV = 3,
    /**< Embedded sync line multiplexed 4:2:2 YUV stream. */
    SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV = 4,
    /**< Discrete sync single 4:2:2 YUV stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_SINGLE_RGB_OR_444_YUV = 5,
    /**< Embedded sync single RGB stream or single 444 YUV stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_2X_RGB = 6,
    /**< Embedded sync 2x multiplexed RGB stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_4X_RGB = 7,
    /**< Embedded sync 4x multiplexed RGB stream. */
    SYSTEM_VIP_SYNC_TYPE_EMB_LINE_RGB = 8,
    /**< Embedded sync line multiplexed RGB stream. */
    SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_8B_RGB = 9,
    /**< Discrete sync single 8b RGB stream. */
    SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_24B_RGB = 10,
    /**< Discrete sync single 24b RGB stream. */
    SYSTEM_VIP_SYNC_TYPE_FORCE32BITS = 0x7FFFFFFF
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} System_VipSyncType;

/**
 *  \brief Enum for Control Channel Selection
 *  It describes channels numbers from extract control code and Vertical
 *  Ancillary Data
 */
/**
 *******************************************************************************
 * \brief Enum for Control Channel Selection
 *
 *  From which channel the control code and vertical ancillary data will be
 *  extracted.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
     SYSTEM_VIP_CTRL_CHAN_SEL_7_0 = 0,
     /**< Use data[7:0] to extract control codes and Vertical Ancillary Data */

     SYSTEM_VIP_CTRL_CHAN_SEL_15_8 = 1,
     /**< Use data[15:8] to extract control codes and Vertical Ancillary Data */

     SYSTEM_VIP_CTRL_CHAN_SEL_23_16 = 2,
     /**< Use data[23:16] to extract control codes and Vertical Ancillary Data
      */

     SYSTEM_VIP_CTRL_CHAN_DONT_CARE =  -(Int32)1,
     /**< Value is dont care */
     SYSTEM_VIP_CTRL_CHAN_FORCE32BITS = 0x7FFFFFFF
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */

} System_VipCtrlChanSel;

/**
 *******************************************************************************
 * \brief Enum for line capture style for vertical and discrete sync.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_VIP_LINE_CAPTURE_STYLE_HSYNC = 0,
    /**< Use HSYNC style linecapture */

    SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID = 1,
    /**< Use ACTVID style line capture */

    SYSTEM_VIP_LINE_CAPTURE_STYLE_DONT_CARE =  -(Int32)1,
    /**< Value is dont care */
    SYSTEM_VIP_LINE_CAPTURE_STYLE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_VipLineCaptureStyle;

/**
 *******************************************************************************
 * \brief Enum on how to detect the FID for interlaced capture.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_VIP_FID_DETECT_MODE_PIN = 0,
    /**< Take FID from pin */

    SYSTEM_VIP_FID_DETECT_MODE_VSYNC = 1,
    /**< FID is determined by VSYNC skew */

    SYSTEM_VIP_FID_DETECT_MODE_DONT_CARE =  -(Int32)1,
    /**< Value is dont care */
    SYSTEM_VIP_FID_DETECT_MODE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_VipFidDetectMode;

/**
 *******************************************************************************
 * \brief Polarity of pixel clock.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_VIP_PIX_CLK_EDGE_POL_RISING = 0,
    /**< Rising Edge is active PIXCLK edge */

    SYSTEM_VIP_PIX_CLK_EDGE_POL_FALLING = 1,
    /**< Falling Edge is active PIXCLK edge */

    SYSTEM_VIP_PIX_CLK_EDGE_POL_DONT_CARE =  -(Int32)1,
    /**< Value is dont care */
    SYSTEM_VIP_PIX_CLK_EDGE_POL_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_VipPixClkEdgePol;

/**
 *******************************************************************************
 * \brief Extract ancillary information from which channel
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE = 0,
    /**< Extract 8b Mode Vertical Ancillary Data from Luma Sites */

    SYSTEM_VIP_ANC_CH_SEL_8B_CHROMA_SIDE = 1,
    /**< Extract 8b Mode Vertical Ancillary Data from Chroma Sites */

    SYSTEM_VIP_ANC_CH_SEL_DONT_CARE =  -(Int32)1,
    /**< Value is dont care */
    SYSTEM_VIP_ANC_CH_SEL_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_VipAncChSel8b;

#if 0
/**
 *  \brief In embedded sync for 2x/4x mux mode there are two way to extract
 *  soruce number, one is from least significant nibble of the XV/fvh codeword
 *  and other is least significant nibble of a horizontal blanking pixel value
 */
typedef enum
{
    SYSTEM_VIP_SRC_NUM_POS_LS_NIBBLE_OF_CODEWORD = 0,
    /**< srcnum is in the least significant nibble of the XV/fvh codeword */

    SYSTEM_VIP_SRC_NUM_POS_LS_NIBBLE_OF_HOR_BLNK_PIX,
    /**< srcnum is in the least significant nibble of a horizontal blanking
     * pixelvalue
     */

    SYSTEM_VIP_SRC_NUM_POS_DONT_CARE =  -(Int32)1,
    /**< Value is dont care */
    SYSTEM_VIP_SRC_NUM_POS_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_VipSrcNumPos;
#endif
/**
 *  enum System_VipRepackMode
 *  \brief Different Repacker Modes supported by VIP Port A
 *  For first 6 modes:
 *    Enum names assume C=[23:16], B=[15:8], A=[7:0]
 *    Enum name is of format VPS_VIP_<repacker INPUT>_TO_<repacker OUTPUT>
 *  For VPS_VIP_REPACK_RAW16_TO_RGB565:
 *    OUT[23:16]=IN[15:11]['b000]
 *    OUT[15: 8]=IN[10: 5]['b00]
 *    OUT[ 7: 0]=IN[ 4: 0]['b000]
 *  For VPS_VIP_REPACK_RAW12_SWAP:
 *    OUT[23:12] = IN[11:0], OUT[11:0] = IN[23:12],
 */
typedef enum
{
    SYSTEM_VIP_REPACK_CBA_TO_CBA      = 0,
    SYSTEM_VIP_REPACK_CBA_TO_ABC      = 1,
    SYSTEM_VIP_REPACK_CBA_TO_BCA      = 2,
    SYSTEM_VIP_REPACK_CBA_TO_CAB      = 3,
    SYSTEM_VIP_REPACK_CBA_TO_ACB      = 4,
    SYSTEM_VIP_REPACK_CBA_TO_BAC      = 5,
    SYSTEM_VIP_REPACK_RAW16_TO_RGB565 = 6,
    SYSTEM_VIP_REPACK_RAW12_SWAP      = 7,
    SYSTEM_VIP_REPACK_DONT_CARE       = SYSTEM_VIP_REPACK_CBA_TO_CBA,
    SYSTEM_VIP_REPACK_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} System_VipRepackMode;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
