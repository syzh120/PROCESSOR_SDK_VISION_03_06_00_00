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
 * \ingroup FRAMEWORK_MODULE_API
 * \defgroup DISPLAYCTRL_LINK_API Display Controller Link API
 *
 * \brief  This module has the interface for using Display Control Link
 *
 *         Display Controller Link can be used to configure the
 *         connections between the video / graphic pipes and the Venc paths
 *         and to set up several parameters of the Venc path
 *
 *         A single display controller link instance is enough to configure
 *         all the paths and set up corresponding parameters.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file displayCtrlLink.h
 *
 * \brief Display Controller Link API
 *
 * \version 0.0 (Jun 2013) : [PS] First version
 * \version 0.1 (Jul 2013) : [PS] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef DISPLAYCTRL_LINK_H_
#define DISPLAYCTRL_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */
/**
 *******************************************************************************
 *
 * \brief Default value of maximum number of frames allowed to be queued
 *        in driver
 *
 *        SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define DISPLAYCTRL_LINK_MAX_INPUT_PIPES                 (4U)
/* @} */

/**
 *******************************************************************************
 *
 *  \ingroup LINK_API_CMD
 *  \addtogroup DISPLAYCTRL_LINK_API_CMD Display Controller Link Control Commands
 *
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To configure connections between pipes and enc paths
 *
 *          SUPPORTED in ALL platforms
 *
 *          MUST be set by user
 *
 *   \param DisplayCtrlLink_ConfigParams *pPrm
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DISPLAYCTRL_LINK_CMD_SET_CONFIG                  (0x5000U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To configure parameters of encode path like overlay,
 *          divisor info, output port parameters. This command needs to be sent
 *          once per every encode path.
 *
 *          SUPPORTED in ALL platforms
 *
 *          OPTIONAL if not set default values taken
 *
 *   \param DisplayCtrlLink_OvlyParams *pPrm [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
*/
#define DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS             (0x5001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To configure parameters of video / graphics pipeline
 *          related to overlay.
 *          This command needs to be sent once per every pipeline.
 *
 *          SUPPORTED in ALL platforms
 *
 *          OPTIONAL if not set default values taken
 *
 *   \param DisplayCtrlLink_OvlyPipeParams *pPrm [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
*/
#define DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS    (0x5002U)

/**
 *******************************************************************************
 *
 *  \brief Link CMD: To clear connections between pipes and enc paths
 *
 *         SUPPORTED in ALL platforms
 *
 *         MUST be used by user. Same values sent by user during SET_CONFIG
 *         need to be resent
 *
 *  \param DisplayCtrlLink_ConfigParams *pPrm   [IN]
 *
 *  \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
*/
#define DISPLAYCTRL_LINK_CMD_CLR_CONFIG                  (0x5003U)

/**
 *******************************************************************************
 *
 *  \brief Link CMD: Flips the HDMI P/N order to correct for hardware defects
 *
 *         SUPPORTED in TDA2x
 *
 *         OPTIONAL if not called P/N order not flipped
 *
 *  \param DisplayCtrlLink_ConfigParams *pPrm   [IN]
 *
 *  \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
*/
#define DISPLAYCTRL_LINK_CMD_HDMI_FLIP_DATA_P_N_ORDER      (0x5004U)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for output device.
 *
 *          List of output devices supported. Currently LCD and HDMI are
 *          supported. Default device will be LCD
 *
 *******************************************************************************
*/
typedef enum
{
    DISPLAYCTRL_LINK_USE_LCD  = 0U,
    /**< Choose LCD for Display */

    DISPLAYCTRL_LINK_USE_HDMI = 1U,
    /**< Choose HDMI for Display */
    DISPLAYCTRL_LINK_USE_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} DisplayCtrlLink_OutDevice;

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for TDM mode.
 *
 *          Supported modes for TDM operation of VENCs.
 *          Currently only supported for TDA3xx
 *
 *******************************************************************************
*/
typedef enum
{
    DISPLAYCTRL_LINK_TDM_DISABLE = 0U,
    /**< TDM operation is disabled */

    DISPLAYCTRL_LINK_TDM_24BIT_TO_8BIT = 1U,
    /**< 24bit data is sent on 8bit bus over three clock cycles */
    DISPLAYCTRL_LINK_TDM_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} DisplayCtrlLink_TdmMode;


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure containing output information.
 *
 *          This structure is used to set output in the output node.
 *          This structure is used as an argument to
 *          IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT ioctl.
 *
 *******************************************************************************
*/
typedef struct
{
    System_VideoDataFormat dataFormat;
    /**< Output Data format from Venc. Currently, valid values are
     *    SYSTEM_DF_RGB24_888, SYSTEM_DF_YUV422I_YUYV. */
    System_DctrlDigitalFmt dvoFormat;
    /**< digital output. See #System_DctrlDigitalFmt for the possible Values */
    System_DctrlAnalogFmt aFmt;
    /**< Analog output. See #System_DctrlAnalogFmt for the possible Values */
    System_VideoIfWidth videoIfWidth;
    /**< [IN] Video interface mode. For valid values see #System_VideoIfWidth */
    System_DctrlSignalPolarity fidPolarity;
    /**< Polarity for the field id signal for the digital output only
     *   valid values see #System_DctrlSignalPolarity
     *   TODO - Check if this is possible in DSS. */
    System_DctrlSignalPolarity vsPolarity;
    /**< Polarity for the vertical sync signal for the digital output only
     *   valid values see #System_DctrlSignalPolarity */
    System_DctrlSignalPolarity hsPolarity;
    /**< Polarity for the horizontal sync signal for the digital output only
     *   valid values see #System_DctrlSignalPolarity */
    System_DctrlSignalPolarity actVidPolarity;
    /**< Polarity for the active video signal for the digital output only
     *   valid values see #System_DctrlSignalPolarity */
    System_DctrlSignalPolarity pixelClkPolarity;
    /**< for valid values TODO
     *   0x0: Data is driven on the LCD data lines on the
     *      rising edge of the pixel clock.
     *   0x1: Data is driven on the LCD data lines on the
     *      falling edge of the pixel clock. */
} DisplayCtrlLink_OutputInfo;

/**
 *******************************************************************************
 *
 *  \brief  FVID2 Mode information structure.
 *
 *******************************************************************************
*/
typedef struct
{
    System_Standard     standard;
    /**< [IN] Standard for which to get the info.
     */
    UInt32              width;
    /**< Active video frame width in pixels. */
    UInt32              height;
    /**< Active video frame height in lines. */
    UInt32              scanFormat;
    /**< Scan format of standard. For valid values see #System_VideoScanFormat*/
    UInt32              pixelClock;
    /**< Pixel clock of standard in KHz. This assumes 8-bit interface for
     *   NTSC/PAL/480I/576I resolutions and 16/24-bit interface for other
     *   resolutions including 480P and 576P. */
    UInt32              fps;
    /**< Frames per second. */
    UInt32              hFrontPorch;
    /**< Horizontal front porch. Same for both fields in case of interlaced
     *   display. */
    UInt32              hBackPorch;
    /**< Horizontal back porch. */
    UInt32              hSyncLen;
    /**< Horizontal sync length. Same for both fields in case of interlaced
     *   display. */
    UInt32              vFrontPorch;
    /**< Vertical front porch for each field or frame. */
    UInt32              vBackPorch;
    /**< Vertical back porch for each field or frame. */
    UInt32              vSyncLen;
    /**< Vertical sync length for each field. */
} System_ModeInfo;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing Venc Divisor information for the LCDx
 *          overlays(LCD1,LCD2,LCD3).
 *          DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 divisorLCD;
    /**< Display controller logic clock divisor value (from 1 to 255)
     *   to specify the intermediate pixel clock frequency based
     *   on the LCDx_CLK. The value 0 is invalid. */
    UInt32 divisorPCD;
    /**< Pixel clock divisor value (from 1 to 255) to specify the
     *   frequency of the pixel clock based on the LCDx_CLK.
     *   The values 0 is invalid */
} DisplayCtrlLink_VencDivisorInfo;

/**
 *******************************************************************************
 *
 *  \brief  Common Overlay panel parameters
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 vencId;
    /**< Identifies the VENC on which mode parameters is to be applied.
     *   Use one of SYSTEM_DCTRL_DSS_VENC_LCD1, SYSTEM_DCTRL_DSS_VENC_LCD2,
     *   SYSTEM_DCTRL_DSS_VENC_LCD3, SYSTEM_DCTRL_DSS_VENC_HDMI
     *   macro for this variable. */
    UInt32 colorKeyEnable;
    /**< Enable or Disable the transparence Color Key. */
    System_DssDispcTransColorKeySel colorKeySel;
    /**< Transparence Color Key Selection. For valid
     *   values check #System_DssDispcTransColorKeySel. */
    Int32  deltaLinesPerPanel;
    /**< Delta Size value of the bottom field compared to top field. */
    UInt32 transColorKey;
    /**< Transparence color key value in RGB format.
     *   [0] BITMAP 1 (CLUT), [23,1] set to 0's
     *   [1:0] BITMAP 2 (CLUT), [23,2] set to 0's
     *   [3:0] BITMAP 4 (CLUT), [23,4] set to 0's
     *   [7:0] BITMAP 8 (CLUT), [23,8] set to 0's
     *   [11:0] RGB 12, [23,12] set to 0's
     *   24-----12 11-----8 7------4 3-------0
     *     Zero      R          G        B
     *   [15:0] RGB 16, [23,16] set to 0's
     *   ??????????????????????????????????
     *     Unused      R          G        B
     *   [23:0] RGB 24 - (RW)
     *   23-----16-15------8-7-------0
     *       R          G        B.    */
    UInt32 backGroundColor;
    /**< 24-bit RGB color value to specify the default background color.
     *   31-----24 23-----16 15------8 7-------0
     *     Unused      R          G        B.     */
    UInt32 alphaBlenderEnable;
    /**< Selects the alpha blender overlay manager for the output
     *   instead of the color key alpha blende. TODO - This is depreciated,
     *   Check if we need to have this variable. */
    System_DssDispcOvlyOptimization ovlyOptimization;
    /**< Overlay Optimization for the overlay. For valid
     *   values check #System_DssDispcOvlyOptimization. */
} DisplayCtrlLink_OvlyParams;

/**
 *******************************************************************************
 *
 *  \brief  Common Overlay pipe related parameters
 *
 *******************************************************************************
*/
typedef struct
{
    System_DssDispcPipes pipeLine;
    /**< All below configuration is applied to this pipeline.*/
    System_DssDispcZorder zorder;
    /**< Defining the priority of the layer compared to
     *   others when overlaying different pipelines, for valid values
     * #System_DssDispcZorder */
    UInt32 zorderEnable;
    /**< Enable or disable the zorder for a pipeline. */
    UInt32 globalAlpha;
    /**< Global alpha value from 0 to 255. 0 corresponds to fully
     *   transparent and 255 to fully opaque. */
    UInt32 preMultiplyAlpha;
    /**< This will configures the piepline to process incoming data as
     *   premultiplied alpha or not. */
} DisplayCtrlLink_OvlyPipeParams;

/**
 *******************************************************************************
 *
 *  \brief  Parameters to define connections between pipes and Vencs
 *          and certain parameters of Vencs
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32         vencId;
    /**< Identifies the VENC on which mode parameters is to be applied.
     *   Use one of SYSTEM_DCTRL_DSS_VENC_LCD1, SYSTEM_DCTRL_DSS_VENC_LCD2,
     *   SYSTEM_DCTRL_DSS_VENC_LCD3, SYSTEM_DCTRL_DSS_VENC_HDMI
     *     macro for this variable. */
    System_ModeInfo mInfo;
    /**< Mode Information to be configured in VENC */
    UInt32         mode;
    /**< VENC mode */
    UInt32 isInputPipeConnected[DISPLAYCTRL_LINK_MAX_INPUT_PIPES];
    /**< Identifies which of the input paths (pipes) are connected to the venc.
     *   Element ordering corresponds to following order
     *    Video pipe 1, Video pipe 2, Video pipe 3, Grahpics pipe
     *   Assign TRUE to indicate connected
     *   Assign FALSE to indicate unconnected. */
    UInt32 writeBackEnabledFlag;
    /**< Identifies whether write back is enabled or not after overlay
     *   Assign TRUE to indicate enabled
     *   Assign FALSE to indicate not enabled */
    UInt32 outputPort;
    /**< Identifies port to which this venc output needs to go
     *   Possible values are SYSTEM_DCTRL_DSS_DPI1_OUTPUT,
     *   SYSTEM_DCTRL_DSS_DPI2_OUTPUT, SYSTEM_DCTRL_DSS_DPI3_OUTPUT,
     *   SYSTEM_DCTRL_DSS_HDMI_OUTPUT. A VENC output can go to two ports,
     *   MUST be able to specify that, is SYSTEM_DCTRL_DSS_xxx_OUTPUT
     *   like a bitmask */
    DisplayCtrlLink_OutputInfo vencOutputInfo;
    /**< Parameters of output node */
    DisplayCtrlLink_VencDivisorInfo vencDivisorInfo;
    /**< Venc divisor information */
    UInt32 tdmMode;
    /**< Enable TDM mode operation. Use enum #DisplayCtrlLink_TdmMode */
} DisplayCtrlLink_VencInfo;

/**
 *******************************************************************************
 *
 *  \brief  Parameters to define connections between pipes and Vencs
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32            numVencs;
    /**< Number of valid entries in vencInfo array */
    UInt32            tiedVencs;
    /**< Bitmask of tied vencs. Two vencs, which uses same pixel clock and whose
     *   vsync are synchronized, can be tied together. */
    DisplayCtrlLink_VencInfo vencInfo[SYSTEM_DCTRL_MAX_VENC];
    /**< vencInfo for each Venc used*/
    UInt32 deviceId;
    /**< NOT USED */

} DisplayCtrlLink_ConfigParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Init function for display controller link. BIOS task for display
 *        controller link gets created and registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DisplayCtrlLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-Init function for display controller link. BIOS task for display
 *        controller link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DisplayCtrlLink_deInit(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
