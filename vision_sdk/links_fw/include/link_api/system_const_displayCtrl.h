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
 *
 * \ingroup SYSTEM_LINK_API
 *
 * \defgroup SYSTEM_CONST_DISPLAYCTRL_API System constants of Display Controller
 *
 * \brief  This module lists the Display Controller specific constants and enums
 *
 * @{
 *
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \file system_const_displayCtrl.h
 *
 * \brief System constants for Display Controller
 *
 * \version 0.0 (Jun 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef SYSTEM_DISPLAY_CTRL_DATA_TYPES_H_
#define SYSTEM_DISPLAY_CTRL_DATA_TYPES_H_

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
 * \brief Macro defining DPI1 Output
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_DPI1_OUTPUT       (10u)

/**
 *******************************************************************************
 * \brief Macro defining DPI2 Output
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_DPI2_OUTPUT       (11u)

/**
 *******************************************************************************
 * \brief Macro defining DPI3 Output
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_DPI3_OUTPUT       (12u)

/**
 *******************************************************************************
 * \brief Macro defining HDMI Output
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_HDMI_OUTPUT       (13u)

/**
 *******************************************************************************
 * \brief Macro defining Write Back Output
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_WB_OUTPUT         (5u)

/**
 *******************************************************************************
 * \brief Macro defining maximum number of edges for allocation
 *******************************************************************************
*/
#define SYSTEM_DCTRL_MAX_EDGES             (50u)

/**
 *******************************************************************************
 * \brief Bitmask for LCD1 VENC
 *
 *        Following macros define bitmasks for the Vencs. Here, bitmasks are
 *        used for identifying Vencs so that tied vencs can be easily specified
 *        and configured. Two vencs, which uses same pixel clock and whose
 *        vsync are synchronized, can be tied together. In DSS Tied Venc
 *        concept is not applicable
 *
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_VENC_LCD1         (0x01u)
/**
 *******************************************************************************
 * \brief Bitmask for LCD2 VENC
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_VENC_LCD2         (0x02u)
/**
 *******************************************************************************
 * \brief Bitmask for LCD3 VENC
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_VENC_LCD3         (0x04u)
/**
 *******************************************************************************
 * \brief Bitmask for HDMI VENC
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_VENC_HDMI         (0x08u)
/**
 *******************************************************************************
 * \brief Bitmask for SDTV (NTSC / PAL)
 *******************************************************************************
*/
#define SYSTEM_DCTRL_DSS_VENC_SDTV         (0x10u)

/**
 *******************************************************************************
 * \brief Maximum number of vencs supported
 *******************************************************************************
*/
#define SYSTEM_DCTRL_MAX_VENC              (5u)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Digital Video Output Formats
 *
 *          BT656 and BT1120 are two different type of embedded
 *          sync formats supported by the SYSTEM module. It supports
 *          Discrete sync format as well
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DCTRL_DVOFMT_BT656_EMBSYNC = 0,
    /**< Output data format is BT656 with embedded sync */
    SYSTEM_DCTRL_DVOFMT_BT1120_EMBSYNC = 1,
    /**< Ouptut data format is BT1120 with embedded sync */
    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC = 2,
    /**< Output data format is for any discrete sync */
    SYSTEM_DCTRL_DVOFMT_MAX = 3,
    /**< This should be the last Enum */
    SYSTEM_DCTRL_DVOFMT_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DctrlDigitalFmt;

/**
 *******************************************************************************
 *
 *  \brief  Analog Video Formats
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DCTRL_A_OUTPUT_COMPOSITE = 0,
    /**< Analog output format composite */
    SYSTEM_DCTRL_A_OUTPUT_SVIDEO = 1,
    /**< Analog output format svideo */
    SYSTEM_DCTRL_A_OUTPUT_COMPONENT = 2,
    /**< Analog output format component */
    SYSTEM_DCTRL_A_OUTPUT_MAX = 3,
    /**< This should be the last Enum */
    SYSTEM_DCTRL_A_OUTPUT_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DctrlAnalogFmt;

/**
 *******************************************************************************
 *
 *  \brief  Signal Polarities
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DCTRL_POLARITY_ACT_LOW = 0U,
    /**< Signal polarity Active low */
    SYSTEM_DCTRL_POLARITY_ACT_HIGH = 1U,
    /**< Signal polarity Active high */
    SYSTEM_DCTRL_POLARITY_MAX = 2U,
    /**< Signal polarity Max value */
    SYSTEM_DCTRL_POLARITY_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
}System_DctrlSignalPolarity;

/**
 *******************************************************************************
 *
 *  \brief Enumeration for HSYNC VSYNC alignment in LCD timing
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_HVSYNC_NOT_ALIGNED = 0,
    /**< HSYNC and VSYNC are not aligned */
    SYSTEM_DSS_DISPC_HVSYNC_ALIGNED = 1,
    /**< HSYNC and VSYNC assertions are aligned */
    SYSTEM_DSS_DISPC_HVSYNC_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_HVSYNC_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcLcdHvAlign;

/**
 *******************************************************************************
 *
 *  \brief Enumeration for Z order
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_ZORDER0 = 0,
    /**< Zorder 0 - lowest priority.
     *   Above background layer and below all layers having higher z-order. */
    SYSTEM_DSS_DISPC_ZORDER1 = 1,
    /**< Zorder 1.
     *   Above layer with z-order 0 and below all layers having higher
     *   z-order */
    SYSTEM_DSS_DISPC_ZORDER2 = 2,
    /**< Zorder 2.
     *   Above layer with z-order 1 and below all layers having higher
     *   z-order */
    SYSTEM_DSS_DISPC_ZORDER3 = 3,
    /**< Zorder 3 - highest priority. Above all layers. */
    SYSTEM_DSS_DISPC_ZORDER_MAX = 4,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_ZORDER_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcZorder;

/**
 *******************************************************************************
 *
 *  \brief Enumeration for Overlay optization mode
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA = 0,
    /**< Fetch all data , no optimization.
     *   All the data for all the enabled pipelines are fetched
     *   from memory regardless of the overlay/alpha blending
     *   configuration. */
    SYSTEM_DSS_DISPC_OVLY_FETCH_OPTIMIZED = 1,
    /**< Fetch data that is required.
     *   The data not used by the overlay manager because
     *   of overlap between layers with no alpha blending
     *   between them must not be fetched from memory in order
     *   to optimize the bandwidth. */
    SYSTEM_DSS_DISPC_OVLY_FETCH_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_OVLY_FETCH_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcOvlyOptimization;

/**
 *******************************************************************************
 *
 *  \brief Enumeration for Transparency Color Key Selection.
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_DEST = 0,
    /**< Destination Transparency color key selected. */
    SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC = 1,
    /**< Source Transparency color key selected. */
    SYSTEM_DSS_DISPC_TRANS_COLOR_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_TRANS_COLOR_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcTransColorKeySel;

/**
 *******************************************************************************
 *
 *  \brief Enumeration for Type of CSC mode in Dispc.
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_CSC_LIMITED = 0,
    /**< CSC in limited range */
    SYSTEM_DSS_DISPC_CSC_FULL = 1,
    /**< CSC in Full range */
    SYSTEM_DSS_DISPC_CSC_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_CSC_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcCscRange;

/**
 *******************************************************************************
 *
 *  \brief Enumeration for Type of scaler conf in Dispc.
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_SC_NONE = 0,
    /**< Both Vertical and Horizontal Disabled */
    SYSTEM_DSS_DISPC_SC_HORIZONTAL = 1,
    /**< Only Horizontal scaling enabled */
    SYSTEM_DSS_DISPC_SC_VERTICAL = 2,
    /**< Only Vertical scaling enabled */
    SYSTEM_DSS_DISPC_SC_BOTH = 3,
    /**< Both Horizontal and Vertical scaling enabled */
    SYSTEM_DSS_DISPC_SC_MAX = 4,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_SC_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcScEnable;

/**
 *******************************************************************************
 *
 *  \brief Enumerations for Overlays in Dispc.
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_OVLY_DPI1 = 0,
    /**< DPI1 output. */
    SYSTEM_DSS_DISPC_OVLY_DPI2 = 1,
    /**< DPI2 output. */
    SYSTEM_DSS_DISPC_OVLY_DPI3 = 2,
    /**< DPI3 output. */
    SYSTEM_DSS_DISPC_OVLY_HDMI = 3,
    /**< HDMI output. */
    SYSTEM_DSS_DISPC_OVLY_WB = 4,
    /**< Write back is considered as overlay here as pipe can be connected
     *   to it. */
    SYSTEM_DSS_DISPC_OVLY_MAX = 5,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_OVLY_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcOvly;

/**
 *******************************************************************************
 *
 *  \brief Enumerations for Pipes in Dispc.
 *
 *******************************************************************************
*/
typedef enum
{
    SYSTEM_DSS_DISPC_PIPE_VID1 = 0,
    /**< Video1 Pipeline. */
    SYSTEM_DSS_DISPC_PIPE_VID2 = 1,
    /**< Video2 Pipeline. */
    SYSTEM_DSS_DISPC_PIPE_VID3 = 2,
    /**< Video3 Pipeline. */
    SYSTEM_DSS_DISPC_PIPE_GFX1 = 3,
    /**< GFX1 Pipeline. */
    SYSTEM_DSS_DISPC_PIPE_WB = 4,
    /**< Write back. */
    SYSTEM_DSS_DISPC_PIPE_MAX = 5,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    SYSTEM_DSS_DISPC_PIPE_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} System_DssDispcPipes;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SYSTEM_DISPLAY_CTRL_DATA_TYPES_H_ */

/* @} */
