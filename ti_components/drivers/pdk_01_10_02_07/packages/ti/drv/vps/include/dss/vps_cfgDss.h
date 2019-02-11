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
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_DSS VPS - DSS Config API
 *
 *  @{
 */

/**
 *  \file vps_cfgDss.h
 *
 *  \brief VPS - Display sub system Configurations options interface
 */

#ifndef VPS_CFG_DSS_H_
#define VPS_CFG_DSS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum Vps_DssDispcLcdHvAlign
 *  \brief Enumeration for HSYNC VSYNC alignment in LCD timing.
 */
typedef enum
{
    VPS_DSS_DISPC_HVSYNC_NOT_ALIGNED = 0,
    /**< HSYNC and VSYNC are not aligned */
    VPS_DSS_DISPC_HVSYNC_ALIGNED,
    /**< HSYNC and VSYNC assertions are aligned */
    VPS_DSS_DISPC_HVSYNC_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcLcdHvAlign;

/**
 *  enum Vps_DssDispcZorder
 *  \brief Enumeration for Zorder
 */
typedef enum
{
    VPS_DSS_DISPC_ZORDER0 = 0,
    /**< Zorder 0 - lowest priority.
     *   Above background layer and below all layers having higher z-order. */
    VPS_DSS_DISPC_ZORDER1,
    /**< Zorder 1.
     *   Above layer with z-order 0 and below all layers having higher
     *   z-order */
    VPS_DSS_DISPC_ZORDER2,
    /**< Zorder 2.
     *   Above layer with z-order 1 and below all layers having higher
     *   z-order */
    VPS_DSS_DISPC_ZORDER3,
    /**< Zorder 3 - highest priority. Above all layers. */
    VPS_DSS_DISPC_ZORDER_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcZorder;

/**
 *  enum Vps_DssDispcOvlyOptimization
 *  \brief Enumeration for Overlay optization mode
 */
typedef enum
{
    VPS_DSS_DISPC_OVLY_FETCH_ALLDATA = 0,
    /**< Fetch all data , no optimization.
     *   All the data for all the enabled pipelines are fetched
     *   from memory regardless of the overlay/alpha blending
     *   configuration. */
    VPS_DSS_DISPC_OVLY_FETCH_OPTIMIZED,
    /**< Fetch data that is required.
     *   The data not used by the overlay manager because
     *   of overlap between layers with no alpha blending
     *   between them must not be fetched from memory in order
     *   to optimize the bandwidth. */
    VPS_DSS_DISPC_OVLY_FETCH_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcOvlyOptimization;

/**
 *  enum Vps_DssDispcTransColorKeySel
 *  \brief Enumerations for Transparency Color Key Selection.
 */
typedef enum
{
    VPS_DSS_DISPC_TRANS_COLOR_KEY_DEST = 0,
    /**< Destination Transparency color key selected. */
    VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC,
    /**< Source Transparency color key selected. */
    VPS_DSS_DISPC_TRANS_COLOR_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcTransColorKeySel;

/**
 *  enum Vps_DssDispcCscRange
 *  \brief Enumerations for Type of CSC mode in Dispc.
 */
typedef enum
{
    VPS_DSS_DISPC_CSC_LIMITED = 0,
    /**< CSC in limited range */
    VPS_DSS_DISPC_CSC_FULL,
    /**< CSC in Full range */
    VPS_DSS_DISPC_CSC_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcCscRange;

/**
 *  enum Vps_DssDispcWbMode
 *  \brief Enumerations for Type of WB mode in Dispc.
 */
typedef enum
{
    VPS_DSS_DISPC_WB_CAPT = 0,
    /**< Writeback in capture Mode */
    VPS_DSS_DISPC_WB_M2M,
    /**< WriteBack In M2M Mode */
    VPS_DSS_DISPC_WB_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcWbMode;

/**
 *  enum Vps_DssDispcWbInNode
 *  \brief Enumerations for WB connection to Pipeline/Overlay.
 */
typedef enum
{
    VPS_DSS_DISPC_WB_IN_NODE_VID1 = 1,
    /**< VID1 pipeline is connected to Writeback. */
    VPS_DSS_DISPC_WB_IN_NODE_VID2 = 2,
    /**< VID2 pipeline is connected to Writeback. */
    VPS_DSS_DISPC_WB_IN_NODE_VID3 = 3,
    /**< VID3 pipeline is connected to Writeback
     *    Not applicable for tda3xx platform. */
    VPS_DSS_DISPC_WB_IN_NODE_GFX = 4,
    /**< GFX pipeline is connected to Writeback */
    VPS_DSS_DISPC_WB_IN_NODE_LCD1 = 6,
    /**< LCD1 Overlay is connected to Writeback */
    VPS_DSS_DISPC_WB_IN_NODE_LCD2 = 7,
    /**< LCD2 Overlay is connected to Writeback
     *   In case of tda3xx platform, this represents the WB OVLY2 used for
     *   M2M writeback and is not applicable for display or capture writeback */
    VPS_DSS_DISPC_WB_IN_NODE_LCD3 = 8,
    /**< LCD3 Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    VPS_DSS_DISPC_WB_IN_NODE_TV = 9,
    /**< TV Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    VPS_DSS_DISPC_WB_IN_NODE_MAX = 10
                                   /**< Should be the last value of this
                                    * enumeration. Will be used by driver for
                                    * validating the input parameters. */
} Vps_DssDispcWbInNode;

/**
 *  enum Vps_DssDispcScEnable
 *  \brief Enumerations for Type of scaler conf in Dispc.
 */
typedef enum
{
    VPS_DSS_DISPC_SC_NONE = 0,
    /**< Both Vertical and Horizontal Disabled */
    VPS_DSS_DISPC_SC_HORIZONTAL,
    /**< Only Horizontal scaling enabled */
    VPS_DSS_DISPC_SC_VERTICAL,
    /**< Only Vertical scaling enabled */
    VPS_DSS_DISPC_SC_BOTH,
    /**< Both Horizontal and Vertical scaling enabled */
    VPS_DSS_DISPC_SC_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcScEnable;

/**
 *  enum Vps_DssDispcOvly
 *  \brief Enumerations for Overlays in Dispc.
 */
typedef enum
{
    VPS_DSS_DISPC_OVLY_DPI1 = 0,
    /**< DPI1 output. */
    VPS_DSS_DISPC_OVLY_DPI2,
    /**< DPI2 output. */
    VPS_DSS_DISPC_OVLY_DPI3,
    /**< DPI3 output. */
    VPS_DSS_DISPC_OVLY_HDMI,
    /**< HDMI output. */
    VPS_DSS_DISPC_OVLY_WB,
    /**< Write back is considered as overlay here as pipe can be connected
     *   to it. */
    VPS_DSS_DISPC_OVLY_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcOvly;

/**
 *  enum Vps_DssDispcPipes
 *  \brief Enumerations for Pipes in Dispc.
 */
typedef enum
{
    VPS_DSS_DISPC_PIPE_VID1 = 0,
    /**< Video1 Pipeline. */
    VPS_DSS_DISPC_PIPE_VID2,
    /**< Video2 Pipeline. */
    VPS_DSS_DISPC_PIPE_VID3,
    /**< Video3 Pipeline. */
    VPS_DSS_DISPC_PIPE_GFX1,
    /**< GFX1 Pipeline. */
    VPS_DSS_DISPC_PIPE_WB,
    /**< Write back. */
    VPS_DSS_DISPC_PIPE_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DssDispcPipes;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_DssDispcDmaConfig
 *  \brief Advanced DMA related Config parameters .
 */
typedef struct
{
    UInt32 burstSize;
    /**<  Video DMA Burst SiZe
     *    0x0: 2x128bit bursts
     *    0x1: 4x128bit bursts
     *    0x2: 8x128bit bursts
     *    0x3: Reserved. */
    UInt32 burstType;
    /**<  Type of the Burst (INC or BLCK)
     *    0x0 Inc burst type
     *    0x1 2D burst type (Used for Tiler, Currently not supported)*/
    UInt32 bufPreloadType;
    /**< Allows to choose between pre-fixed preload size
     *   and a programmable size.
     *    0 - user programmed Preload value
     *    1 - Preload will be equal to bufHighThreshold Value */
    UInt32 bufLowThreshold;
    /**<  DMA buffer low threshold. Number of 128 bits defining the
     *    threshold value. */
    UInt32 bufHighThreshold;
    /**<  Video DMA buffer high threshold. Number of 128 bits defining the
     *    Threshold value. */
    UInt32 selfRefreshEnable;
    /**<  Enables the self refresh of the video window from its own.
     *    DMA buffer only
     *    FALSE - Disable
     *    TRUE - Enable. */
    UInt32 arbitration;
    /**<  Determines the priority of the video pipeline.
     *    0x0 - Normal Priority
     *    0x1 - High priority. */
    UInt32 pixelInc;
    /**<  Number of bytes to increment between two pixels.
     *    Encoded unsigned value (from 1 to 255) to specify the
     *    number of bytes between two pixels in the video buffer.
     *    The value 0 is invalid. The value 1 means next pixel. The
     *    value 1 + n * bpp means increment of n pixels.
     *    For YUV4:2:0, maximum supported value is 128. */
    UInt32 idleNumber;
    /**<  Number of idles between the requests on L3 Interconnect.
     *    if idleSize is 0 - number of idle cycles = idle Number
     *          range 0 to 15
     *    if idleSize is 1 - number of idle clcles = idle Number * Burst Size.
     *          range 0 to 120 for value of burstSize = 2,
     *          range 0 to 60  for value of burstSize = 1,
     *          range 0 to 30  for value of burstSize = 0.
     *    Applicable only for the writeback pipe. */
    UInt32 idleSize;
    /**<  determines multiplication factor to idleNumber.
     *    refer comment for idleNumber.
     *    Applicable only for the writeback pipe. */
} Vps_DssDispcAdvDmaConfig;

/**
 *  struct Vps_DssDispcVidVC1Config
 *  \brief VC1 configuration of Video Pipeline .
 */
typedef struct
{
    UInt32 enable;
    /**< Enable VC1 Range mapping, should be enabled only for YUV formats. */
    UInt32 rangeY;
    /**< VC1 Range Value for Y Component, valid values 0-7. */
    UInt32 rangeUV;
    /**< VC1 Range Value for UV(CbCr) Component, valid values 0-7. */
} Vps_DssDispcVidVC1Config;

/**
 *  struct Vps_DssDispcPipeCfg
 *  \brief Video pipeline configuration structure.
 */
typedef struct
{
    UInt32 repliEnable;
    /**< Enable or disable the video replication logic. */
    UInt32 scEnable;
    /**< Enable or disable the scaling, enable only if input size and
     *   Output size are different.For valid values check
     *   #Vps_DssDispcScEnable.
     *   There is a limitation with scaling in TDA2xx/TDA2Ex/AM571x/AM572x/
     *   DRA75x platforms, Max horizontal scaling ratio supported is the ratio
     *   of (the dss functional clock) / (pixel clk) for both up and down
     *   scaling.
     *   Ex: For 192Mhz of DSS functional clock and 148.5 MHz of pixel clk with
     *   1080p frame, Max scaling ratio supported is 192/148.5 = 1.29.
     *   So max horizontal down scaling possible is 1920/1.29 = 1485 pixels.
     *   Application should make sure scaling ratio is within allowed limits. */
    UInt32 cscFullRngEnable;
    /**< Full range or Limited Range for CSC module. For valid
     *   values check #Vps_DssDispcCscRange. */
    UInt32 chromaSampling;
    /**< chromaSampling member is deprecated. It is present for SW backward
     *   compatiblity only.
     *   For 420SP input, DSS driver internally set this field to 1 and the
     *   application has to just set the data format to YUV420SP in the
     *   structure : instObj.dssPrms.inFmt.dataFormat
     */
} Vps_DssDispcVidPipeConfig;

/**
 *  struct Vps_DssDispcVidConfig
 *  \brief Video configuration.
 */
typedef struct
{
    Vps_DssDispcVidPipeConfig pipeCfg;
    /**< Video pipeline configuration structure. */
    Vps_DssDispcAdvDmaConfig *advDmaCfg;
    /**< Pointer to Advance DMA configuraion.
     *   if its NULL - Default configuration will be used. */
    Vps_DssDispcVidVC1Config *vc1Cfg;
    /**< VC1 Range Config structure. */
} Vps_DssDispcVidConfig;

/**
 *  struct Vps_DssDispcGfxPipeConfig
 *  \brief Graphics pipeline configuration structure.
 */
typedef struct
{
    UInt32 repliEnable;
    /**< Enable or disable the replication logic in graphics pipeline.
     *   TODO - Check if this needs to be exposed. */
    UInt32 antiFlickerEnable;
    /**< Enable or disable the anti Flicker filter in graphics pipeline.
     *   The anti-flicker filter processes the graphics data in RGB format in
     *   order to remove some of the vertical flicker. It is based on 3-tap FIR
     *   filter with hardcoded coefficients: 0.25, 0.5 and 0.25. */
} Vps_DssDispcGfxPipeConfig;

/**
 *  struct Vps_DssDispcGfxConfig
 *  \brief Graphics configuration.
 */
typedef struct
{
    Vps_DssDispcGfxPipeConfig pipeCfg;
    /**< Graphics pipeline configuration structure. */
    Vps_DssDispcAdvDmaConfig *advDmaCfg;
    /**< Pointer to Advance DMA configuraion.
     *   if its NULL - Default configuration will be used. */
} Vps_DssDispcGfxConfig;

/**
 *  struct Vps_DssDispcWbPipeConfig
 *  \brief Writeback pipeline configuration structure.
 */
typedef struct
{
    UInt32 scEnable;
    /**< Enable or disable the scaling, enable only if input size and
     *   Output size are different. For valid values check
     *   #Vps_DssDispcScEnable. */
    UInt32 cscFullRngEnable;
    /**< Full range or Limited Range for CSC module. For valid
     *   values check #Vps_DssDispcCscRange. */
    UInt32 cropEnable;
    /**< Enable or Disable Crop (Region based writeback)
     *   Not applicable for TDA2XX. */
}Vps_DssDispcWbPipeConfig;

/**
 *  struct Vps_DssDispcWbConfig
 *  \brief Writeback configuration.
 */
typedef struct
{
    Vps_DssDispcWbPipeConfig  pipeCfg;
    /**< Video pipeline configuration structure. */
    Vps_DssDispcAdvDmaConfig *advDmaCfg;
    /**< Pointer to Advance DMA configuraion.
     *   if its NULL - Default configuration will be used. */
} Vps_DssDispcWbConfig;

/**
 *  struct Vps_DssDispcOvlyPanelConfig
 *  \brief Common Overlay panel parameters .
 */
typedef struct
{
    UInt32 vencId;
    /**< VencID of the panel to which this config is to be done. */
    UInt32 colorKeyEnable;
    /**< Enable or Disable the transparence Color Key. */
    UInt32 colorKeySel;
    /**< Transparence Color Key Selection. For valid
     *   values check #Vps_DssDispcTransColorKeySel. */
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
    UInt32 ovlyOptimization;
    /**< Overlay Optimization for the overlay. For valid
     *   values check #Vps_DssDispcOvlyOptimization. */
} Vps_DssDispcOvlyPanelConfig;

/**
 *  struct Vps_DssDispcOvlyPipeConfig
 *  \brief Common Overlay pipe related parameters.
 */
typedef struct
{
    UInt32 pipeLine;
    /**< All below configuration is applied to this pipeline. For valid values
     *   check #Vps_DssDispcPipes. */
    UInt32 zorder;
    /**< Defining the priority of the layer compared to
     *   others when overlaying different pipelines, for valid values
     * #Vps_DssDispcZorder */
    UInt32 zorderEnable;
    /**< Enable or disable the zorder for a pipeline. */
    UInt32 globalAlpha;
    /**< Global alpha value from 0 to 255. 0 corresponds to fully
     *   transparent and 255 to fully opaque.
     *   Transparency will take effect only when zorder > 0 for a pipeline
     */
    UInt32 preMultiplyAlpha;
    /**< This will configures the piepline to process incoming data as
     *   premultiplied alpha or not. */
} Vps_DssDispcOvlyPipeConfig;

/**
 *  struct Vps_DssDispcLcdAdvSignalConfig
 *  \brief Advance Signal Params for the overlays.
 */
typedef struct
{
    UInt32 vencId;
    /**< VencID of the panel to which this config is to be done. */
    UInt32 hVAlign;
    /**< Defines the alignment betwwen HSYNC and VSYNC assertion.
     *   For valid values see #Vps_DssDispcLcdHvAlign */
    UInt32 hVClkControl;
    /**< HSYNC/VSYNC pixel clock control on/off.
     *   0x0: HSYNC and VSYNC are driven on opposite edges of the pixel clock
     *      than pixel data.
     *   0x1: HSYNC and VSYNC are driven according to hVClkRiseFall value. */
    UInt32 hVClkRiseFall;
    /**< Program HSYNC/VSYNC rise or fall
     *   0x0: HSYNC and VSYNC are driven on the falling edge
     *        of the pixel clock (if hVClkControl is set to 1).
     *   0x1: HSYNC and VSYNC are driven on the rising edge of
     *        the pixel clock (if hVClkControl is set to 1). */
    UInt32 acBI;
    /**< AC bias pin transitions per interrupt
     *   Value (from 0 to 15) used to specify the number of AC
     *   bias pin transitions. */
    UInt32 acB;
    /**< AC bias pin frequency RW 0x00
     *   Value (from 0 to 255) used to specify the number of line
     *   clocks to count before transitioning the AC bias pin. This
     *   pin is used to periodically invert the polarity of the power
     *   supply to prevent DC charge buildup within the display. */
} Vps_DssDispcLcdAdvSignalConfig;

/**
 *  struct Vps_DssDispcLcdAdvDisplayConfig
 *  \brief Advance Display Params for the LCD overlays(LCD1,LCD2,LCD3) .
 */
typedef struct
{
    UInt32 vencId;
    /**< VencID of the panel to which this config is to be done. */
    UInt32 stallModeEnable;
    /**< STALL mode for the LCD output.
     *   FALSE: Normal mode selected
     *   TRUE: STALL mode selected. The display controller sends the data
     *   without considering the VSYNC/HSYNC. The LCD output is disabled at
     *   the end of the transfer of the frame. Software must reenable the
     *   LCD output to generate a new frame. STALL mode is currently
     *   not used. */
    UInt32 mono8bit;
    /**< Mono 8-bit mode of the LCD, For valid values TODO */
    UInt32 stnTft;
    /**< LCD Display type of the LCD output, for valid values TODO */
    UInt32 monoColor;
    /**< Monochrome/color selection for the LCD. */
    UInt32 fidFirst;
    /**< Selects the first field to output in case of interlace mode.
     *   In case of progressive mode, the value is not used. For valid values
     *   check TODO. */
    UInt32 buffHandCheck;
    /**< Controls the handscheck between the DMA buffer and
     *   the STALL signal to prevent from underflow. The bit must be set to 0
     *   when the module is not in STALL mode.TODO-Check if we need to expose */
} Vps_DssDispcLcdAdvDisplayConfig;

/**
 *  struct Vps_DssDispcAdvLcdTdmConfig
 *  \brief  Params for the LCD overlays(LCD1,LCD2,LCD3) .
 */
typedef struct
{
    UInt32 vencId;
    /**< VencID of the panel to which this config is to be done. */
    UInt32 tdmEnable;
    /**< Enable the multiple cycle format (TDM mode only used RW 0
     *   for Active matrix mode with the RFBI enable bit off) for
     *   the LCD output,
     *   FALSE: TDM disabled
     *   TRUE: TDM enabled */
    UInt32 noBitsPixel1Cycle1;
    /**< Number of bits from the pixel 1 for cycle 1(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    UInt32 noBitsPixel1Cycle2;
    /**< Number of bits from the pixel 1 for cycle 2(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    UInt32 noBitsPixel1Cycle3;
    /**< Number of bits from the pixel 1 for cycle 3(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    UInt32 bitAlignPixel1Cycle1;
    /**< Alignment of the bits from pixel 1 for cycle1 on the output
     *   interface. */
    UInt32 bitAlignPixel1Cycle2;
    /**< Alignment of the bits from pixel 1 for cycle2 on the output
     *   interface. */
    UInt32 bitAlignPixel1Cycle3;
    /**< Alignment of the bits from pixel 1 for cycle3 on the output
     *   interface. */
    UInt32 noBitsPixel2Cycle1;
    /**< Number of bits from the pixel 2 for cycle 1(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid. */
    UInt32 noBitsPixel2Cycle2;
    /**< Number of bits from the pixel 2 for cycle 2(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid. */
    UInt32 noBitsPixel2Cycle3;
    /**< Number of bits from the pixel 2 for cycle 3(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid. */
    UInt32 bitAlignPixel2Cycle1;
    /**< Alignment of the bits from pixel 2 for cycle 1 on the output
     *   interface. */
    UInt32 bitAlignPixel2Cycle2;
    /**< Alignment of the bits from pixel 2 for cycle 2 on the output
     *   interface. */
    UInt32 bitAlignPixel2Cycle3;
    /**< Alignment of the bits from pixel 2 for cycle 3 on the output
     *   interface. */
    UInt32 tdmUnusedBits;
    /**< State of unused bits (TDM mode only) for the LCD output.
     *   0x0: Low level (0)
     *   0x1: High level (1)
     *   0x2: Unchanged from previous state
     *   0x3: Reserved
     */
    UInt32 tdmCycleFormat;
    /**< Cycle format (TDM mode only) for the LCD output.
     *   0x0: 1 cycle for 1 pixel
     *   0x1: 2 cycles for 1 pixel
     *   0x2: 3 cycles for 1 pixel
     *   0x3: 3 cycles for 2 pixels */
    UInt32 tdmParallelMode;
    /**< Output interface width (TDM mode only) for the LCD output.
     *   0x0: 8-bit parallel output interface selected
     *   0x1: 9-bit parallel output interface selected
     *   0x2: 12-bit parallel output interface selected
     *   0x3: 16-bit parallel output interface selected */
} Vps_DssDispcAdvLcdTdmConfig;

typedef struct
{
    UInt32 videoStandard;
    /**< SD-Venc standard to be configured. */
    UInt32 vencFCtrl;
    /**< Input video source and format configuration. */
    UInt32 vidoutCtrl;
    /**<  Video Encoder output clock configuration. */
    UInt32 syncCtrl;
    /**< Sync control configuration like polarity of hs, vs, fid etc.
     *   SD-Venc in master mode setting etc. */
    UInt32 totalPixels;
    /**< Line length or total number of pixels in a scan line including active
     *   video and blanking. Total number of pixels in a scan line =
     *   totalPixels. */
    UInt32 totalLines;
    /**< The frame length or total number of lines in a frame including active
     *   video and blanking from the source image.Total number of lines in a
     *   frame from the source image = totalLines + 1 */
    UInt32 filterCtrl;
    /**< Chrominance and luminance interpolation filter control */
    UInt32 freqCodeCtrl;
    /**< Frequencie code control */
    UInt32 cPhase;
    /**< Phase of the encoded video color subcarrier (including the color burst)
     *   relative to H-sync. The adjustable step is 360/256 degrees */
    UInt32 gainU;
    /**< Gain control for Cb signal */
    UInt32 gainV;
    /**< Gain control of Cr signal */
    UInt32 gainY;
    /**< Gain control of Y signal */
    UInt32 blackLevel;
    /**< Black level setting */
    UInt32 blankLevel;
    /**< Blank level setting */
    UInt32 xColorCtrl;
    /**< Cross-Colour Control register */
    UInt32 mControl;
    /**< M control register */
    UInt32 bstampWssData;
    /**< amplitude of color burst and wide screen signalling data */
    UInt32 colorSubFreq;
    /**< Color Subcarrier Frequency */
    UInt32 line21;
    /**< LINE 21 Closed Caption data */
    UInt32 lineSel;
    /**< closed caption runin code position */
    UInt32 wcCtrlL21;
    /**< WC control and Line 21 setting */
    UInt32 hvTrigger;
    /**< Horizontal and vertical trigger */
    UInt32 actVidSet;
    /**< Start and end of active video */
    UInt32 fieldSet;
    /**< Active line of field and field length setting */
    UInt32 lalPhaseReset;
    /**< Phase reset and vertical blanking settings */
    UInt32 hsyncIntConf;
    /**< HSYNC internal start stop configuration */
    UInt32 hsyncExtConf;
    /**< HSYNC External start stop configuration */
    UInt32 vSyncIntStr;
    /**< VSYNC internal start configuration */
    UInt32 vSyncIntStrStp;
    /**< VSYNC internal start stop configuration */
    UInt32 vSyncIntStpExtStr;
    /**< VSYNC internal stop external start configuration */
    UInt32 vSyncExtStpExtStr;
    /**< VSYNC external start stop configuration */
    UInt32 vSyncExtStpY;
    /**< VSYNC external stop Y configuration */
    UInt32 aVidStrStpX;
    /**< Active Video start stop X configuration */
    UInt32 aVidStrStpY;
    /**< Active Video start stop Y configuration */
    UInt32 fidIntStrXStrY;
    /**< Field ID internal start Y configuration */
    UInt32 fidIntOffYExtStrX;
    /**< Field ID internal offset Y External start X configuration */
    UInt32 fidExtStrYExtOffY;
    /**< Field ID external start Y External offset X configuration */
    UInt32 tvdetgpIntStrStpX;
    /**< TVDETGP internal start stop X configuration */
    UInt32 tvdetgpIntStrStpY;
    /**< TVDETGP internal start stop Y configuration */
    UInt32 genCtrl;
    /**< TVDETGP enable and SYNC POLARITY and UVPHASE POL */
    UInt32 outputCtrl;
    /**< Video Invert and Composite output enable */
} Vps_DssDispcSdVencAdvConfig;

/**
 *  struct Vps_DssCscCoeff
 *  \brief  Params for CSC Coefficients for YUV to RGB color conversion.
 */
typedef struct
{
    Int16 ry;
    /**< RY Coefficient Encoded signed value */
    Int16 rcr;
    /**< RCr Coefficient Encoded signed value */
    Int16 rcb;
    /**< RCb Coefficient Encoded signed value */
    Int16 gy;
    /**< GY Coefficient Encoded signed value */
    Int16 gcr;
    /**< GCr Coefficient Encoded signed value */
    Int16 gcb;
    /**< GCb Coefficient Encoded signed value */
    Int16 by;
    /**< BY Coefficient Encoded signed value */
    Int16 bcr;
    /**< BCr Coefficient Encoded signed value */
    Int16 bcb;
    /**< BCb Coefficient Encoded signed value */
    Int16 roff;
    /**< R offset Encoded signed value */
    Int16 goff;
    /**< G offset Encoded signed value */
    Int16 boff;
    /**< B offset Encoded signed value */
} Vps_DssCscCoeff;

/**
 *  struct Vps_DssVencCprCoeff
 *  \brief  Params for CPR Coefficients for RGB to YUV color conversion.
 */
typedef struct
{
    UInt32 vencId;
    /**< VencID of the panel to which this config is to be done. */
    UInt32 enableCpr;
    /**< Boolean to enable CPR */
    UInt32 enableCsc;
    /**< Boolean to enable CSC */
    Int16 rr;
    /**< RR Coefficient Encoded signed value */
    Int16 rg;
    /**< RG Coefficient Encoded signed value */
    Int16 rb;
    /**< RB Coefficient Encoded signed value */
    Int16 gr;
    /**< GR Coefficient Encoded signed value */
    Int16 gg;
    /**< GG Coefficient Encoded signed value */
    Int16 gb;
    /**< GB Coefficient Encoded signed value */
    Int16 br;
    /**< BR Coefficient Encoded signed value */
    Int16 bg;
    /**< BG Coefficient Encoded signed value */
    Int16 bb;
    /**< BB Coefficient Encoded signed value */
} Vps_DssVencCprCoeff;

typedef struct
{
    UInt32 inWidth;
    /**< Horizontal Size of picture at input of writeback pipeline .
     *    Should be same as overlay/forward pipe Width in case
     *    of TDA2XX. */
    UInt32 inHeight;
    /**< Verticle Size of picture at input of writeback pipeline
     *    Should be same as overlay/forward pipe Height in case
     *    of TDA2XX. */
    UInt32 outWidth;
    /**< Horizontal Size of picture at output of writeback pipeline
     *     whcih is going to memory */
    UInt32 outHeight;
    /**< Vertical Size of picture at output of writeback pipeline
     *     whcih is going to memory */
    UInt32 inPosX;
    /**< PositionX of picture at input of writeback pipeline(Overlay Window)
     *    Applicable only for TDA3xx platform. */
    UInt32 inPosY;
    /**< PositionY of picture at input of writeback pipeline(Overlay Window)
     *    Applicable only for TDA3xx platform. */
} Vps_DssDispcWbRtParams;

/**
 *  struct Vps_DssDispcRtParams
 *  \brief  Params for runtime change of configuration of fwd pipes per frame.
 *          Supports changing in width/Height, out width/height, position in
 *          Overlay per frame.
 *          Since the RT Param Update happens inside ISR context, we donot print
 *          any errors and If the parameters are not proper RT Params will not
 *          be applied, But the Buffer will still be displayed as per older
 *          configuration.
 */
typedef struct
{
    UInt32 inWidth;
    /**< Horizontal Size in pixels of picture at input of vid/gfx pipeline. */
    UInt32 inHeight;
    /**< Verticle Size in pixels of picture at input of vid/gfx pipeline. */
    UInt32 outWidth;
    /**< Horizontal Size in pixels of picture at Overlay.
     *   should be same as inWidth for Gfx pipe which doesnot have scalar.
     *   Up Scaling greater than 8x is not supported.
     *   outWidth < (8 * inWidth).
     *   Down scaling greater than 4x is not supported.
     *   inWidth < (4 * outWidth).
     */
    UInt32 outHeight;
    /**< Vertical Size in pixels of picture at Overlay.
     *   should be same as inHeight for Gfx pipe which doesnot have scalar.
     *   Up Scaling greater than 8x is not supported.
     *   outHeight < (8 * inHeight).
     *   Down scaling greater than 4x is not supported.
     *   inHeight < (4 * outHeight).
     */
    UInt32 posX;
    /**< PositionX of picture at Overlay.
     *   (posX + outWidth) < Overlay width.
     */
    UInt32 posY;
    /**< PositionY of picture at Overlay.
     *   (posY + outHeight) < Overlay height.
     */
    UInt32 scEnable;
    /**< Make TRUE to enable scalar if in and out width/Height are different.
     *   Not applicable for GFX pipe.
     *   There is a limitation with scaling in TDA2xx/TDA2Ex/AM571x/AM572x/
     *   DRA75x platforms, max scaling ratio supported is the ratio
     *   dss functional clock / pixel clk. Application should make sure scaling
     *   ratio is within allowed limits.
     */
    UInt32 pitch[FVID2_MAX_PLANES];
    /**< pitch in Bytes of the Buffer.
     *   should be retained as original buffer pitch when no change.
     */
} Vps_DssDispcRtParams;

/**
 *  struct Vps_DssDispcMflagConfigParam
 *  \brief  Params for mflag configuration.
 */
typedef struct
{
    UInt32 globalMflagStart;
    /**< used to drive mflag signal when dma buffer is empty at the beginning of
     *   pipeline.
     *   0: mflag signal for each pipe kept 0 till preload is reached.
     *   1: Even at the beginning mflag ctrl is used to driver mflag signal. */
    UInt32 globalMflagCtrl;
    /**< used to control the mflag signal.
     *   0: mflag mechanism is disabled.
     *   1: mflag out of band signal always enabled (force mode for debug).
     *   2: mflag out of band signal is dynamically set and reset based on
            mflag rules. */
    UInt32 gfxMflagHighThreshold;
    /**< high threshold for mflag generation for gfx pipe. */
    UInt32 gfxMflagLowThreshold;
    /**< low threshold for mflag generation for gfx pipe. */
    UInt32 vid1MflagHighThreshold;
    /**< high threshold for mflag generation for vid1 pipe. */
    UInt32 vid1MflagLowThreshold;
    /**< low threshold for mflag generation for vid1 pipe. */
    UInt32 vid2MflagHighThreshold;
    /**< high threshold for mflag generation for vid2 pipe. */
    UInt32 vid2MflagLowThreshold;
    /**< low threshold for mflag generation for vid2 pipe. */
    UInt32 vid3MflagHighThreshold;
    /**< high threshold for mflag generation for vid3 pipe. */
    UInt32 vid3MflagLowThreshold;
    /**< low threshold for mflag generation for vid3 pipe. */
    UInt32 wbMflagHighThreshold;
    /**< high threshold for mflag generation for wb pipe. */
    UInt32 wbMflagLowThreshold;
    /**< low threshold for mflag generation for wb pipe. */
} Vps_DssDispcMflagConfigParam;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_DssDispcAdvLcdTdmConfig structure init function LCD Overlays.
 *
 *  \param  advLcdTdmCfg   [IN] Pointer to #Vps_DssDispcAdvLcdTdmConfig
 *                              structure.
 *
 */
static inline void VpsDssDispcAdvLcdTdmConfig_init(
    Vps_DssDispcAdvLcdTdmConfig *advLcdTdmCfg);

/**
 *  \brief Vps_DssDispcAdvDmaConfig structure init function for vid pipeline.
 *
 *  \param  advDmaCfg   [IN] Pointer to #Vps_DssDispcAdvDmaConfig structure.
 *
 */
static inline void VpsDssDispcAdvDmaConfig_init(
    Vps_DssDispcAdvDmaConfig *advDmaCfg);

/**
 *  \brief Vps_DssDispcAdvDmaConfig structure init function for WB pipeline.
 *
 *  \param  advWbDmaCfg [IN] Pointer to #Vps_DssDispcAdvDmaConfig structure.
 *
 */
static inline void VpsDssDispcAdvWbDmaConfig_init(
    Vps_DssDispcAdvDmaConfig *advWbDmaCfg);

/**
 *  \brief Vps_DssDispcVidVC1Config structure init function.
 *
 *  \param  vc1Cfg      [IN] Pointer to #Vps_DssDispcVidVC1Config structure.
 *
 */
static inline void VpsDssDispcVidVC1Config_init(
    Vps_DssDispcVidVC1Config *vc1Cfg);

/**
 *  \brief Vps_DssDispcVidPipeConfig structure init function.
 *
 *  \param  vidPipeCfg  [IN] Pointer to #Vps_DssDispcVidPipeConfig structure.
 *
 */
static inline void VpsDssDispcVidPipeConfig_init(
    Vps_DssDispcVidPipeConfig *vidPipeCfg);

/**
 *  \brief Vps_DssDispcVidConfig structure init function.
 *
 *  \param  vidCfg      [IN] Pointer to #Vps_DssDispcVidConfig structure.
 *
 */
static inline void VpsDssDispcVidConfig_init(Vps_DssDispcVidConfig *vidCfg);

/**
 *  \brief Vps_DssDispcGfxPipeConfig structure init function.
 *
 *  \param  gfxPipeCfg  [IN] Pointer to #Vps_DssDispcGfxPipeConfig structure.
 *
 */
static inline void VpsDssDispcGfxPipeConfig_init(
    Vps_DssDispcGfxPipeConfig *gfxPipeCfg);

/**
 *  \brief Vps_DssDispcGfxConfig structure init function.
 *
 *  \param  gfxCfg      [IN] Pointer to #Vps_DssDispcGfxConfig structure.
 *
 */
static inline void VpsDssDispcGfxConfig_init(Vps_DssDispcGfxConfig *gfxCfg);

/**
 *  \brief Vps_DssDispcGfxPipeConfig structure init function.
 *
 *  \param  wbPipeCfg  [IN] Pointer to #Vps_DssDispcGfxPipeConfig structure.
 *
 */
static inline void VpsDssDispcWbPipeConfig_init(
    Vps_DssDispcWbPipeConfig *wbPipeCfg);

/**
 *  \brief Vps_DssDispcWbConfig structure init function.
 *
 *  \param  wbCfg      [IN] Pointer to #Vps_DssDispcWbConfig structure.
 *
 */
static inline void VpsDssDispcWbConfig_init(Vps_DssDispcWbConfig *wbCfg);

/**
 *  \brief Vps_DssDispcOvlyPanelConfig structure init function.
 *
 *  \param  ovlyPanelCfg [IN] Pointer to #Vps_DssDispcOvlyPanelConfig structure.
 *
 */
static inline void VpsDssDispcOvlyPanelConfig_init(
    Vps_DssDispcOvlyPanelConfig *ovlyPanelCfg);

/**
 *  \brief Vps_DssDispcOvlyPipeConfig structure init function.
 *
 *  \param  ovlyPipeCfg [IN] Pointer to #Vps_DssDispcOvlyPipeConfig structure.
 *
 */
static inline void VpsDssDispcOvlyPipeConfig_init(
    Vps_DssDispcOvlyPipeConfig *ovlyPipeCfg);

/**
 *  \brief Vps_DssCscCoeff structure init function.
 *
 *  \param  cscCoeff    [IN] Pointer to #Vps_DssCscCoeff structure.
 *
 */
static inline void VpsDssCscCoeff_init(Vps_DssCscCoeff *cscCoeff);

/**
 *  \brief Vps_DssDispcMflagConfigParam structure init function.
 *
 *  \param  mflagParam    [IN] Pointer to #Vps_DssDispcMflagConfigParam structure.
 *
 */
static inline void VpsDssDispcMflagConfigParam_init(
    Vps_DssDispcMflagConfigParam *mflagParam);

/**
 *  \brief Returns TRUE if the writeback input node is from an overlay. Else
 *  returns FALSE indicating that the node is from a pipeline
 *
 *  \param  inNode      [IN] Writeback input node. Refer #Vps_DssDispcWbInNode.
 *
 *  \return TRUE or FALSE accordingly.
 *
 */
static inline UInt32 VpsDss_isWbInNodeFromOvly(UInt32 inNode);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsDssDispcAdvLcdTdmConfig_init(
    Vps_DssDispcAdvLcdTdmConfig *advLcdTdmCfg)
{
    if (advLcdTdmCfg != NULL)
    {
        advLcdTdmCfg->tdmEnable = 0U;
        advLcdTdmCfg->bitAlignPixel1Cycle1 = 0U;
        advLcdTdmCfg->bitAlignPixel1Cycle2 = 0U;
        advLcdTdmCfg->bitAlignPixel1Cycle3 = 0U;
        advLcdTdmCfg->bitAlignPixel2Cycle1 = 0U;
        advLcdTdmCfg->bitAlignPixel2Cycle2 = 0U;
        advLcdTdmCfg->bitAlignPixel2Cycle3 = 0U;
        advLcdTdmCfg->noBitsPixel1Cycle1   = 8U;
        advLcdTdmCfg->noBitsPixel1Cycle2   = 8U;
        advLcdTdmCfg->noBitsPixel1Cycle3   = 8U;
        advLcdTdmCfg->noBitsPixel2Cycle1   = 0U;
        advLcdTdmCfg->noBitsPixel2Cycle2   = 0U;
        advLcdTdmCfg->noBitsPixel2Cycle3   = 0U;
        advLcdTdmCfg->tdmUnusedBits        = 0U;
        advLcdTdmCfg->tdmCycleFormat       = 0x2U;
        advLcdTdmCfg->tdmParallelMode      = 0x0U;
    }
}

static inline void VpsDssDispcAdvDmaConfig_init(
    Vps_DssDispcAdvDmaConfig *advDmaCfg)
{
    if (advDmaCfg != NULL)
    {
        /* TODO - Verify these values */
        advDmaCfg->burstSize        = 0x2U; /* 8 x 128-bit burst */
        advDmaCfg->burstType        = 0U;
        advDmaCfg->bufPreloadType   = 1U;
        advDmaCfg->bufHighThreshold = 0x07FFU;
        advDmaCfg->bufLowThreshold  = 0x07F8U;
#if defined (SOC_TDA3XX)
        advDmaCfg->bufHighThreshold = 0x09FFU;
        advDmaCfg->bufLowThreshold  = 0x09F8U;
#endif
        advDmaCfg->selfRefreshEnable = (UInt32) FALSE;
        advDmaCfg->arbitration       = 0U;
        advDmaCfg->pixelInc          = 1U;
        advDmaCfg->idleNumber        = 0U;
        advDmaCfg->idleSize          = 0U;
    }
}

static inline void VpsDssDispcAdvWbDmaConfig_init(
    Vps_DssDispcAdvDmaConfig *advWbDmaCfg)
{
    if (advWbDmaCfg != NULL)
    {
        /* TODO - Verify these values */
        advWbDmaCfg->burstSize         = 0x0U;
        advWbDmaCfg->burstType         = 0U;
        advWbDmaCfg->bufPreloadType    = 0U;
        advWbDmaCfg->bufHighThreshold  = 0x016U;
        advWbDmaCfg->bufLowThreshold   = 0x08U;
        advWbDmaCfg->selfRefreshEnable = (UInt32) FALSE;
        advWbDmaCfg->arbitration       = 0U;
        advWbDmaCfg->pixelInc          = 1U;
        advWbDmaCfg->idleNumber        = 0U;
        advWbDmaCfg->idleSize          = 0U;
    }
}

static inline void VpsDssDispcVidVC1Config_init(
    Vps_DssDispcVidVC1Config *vc1Cfg)
{
    if (vc1Cfg != NULL)
    {
        vc1Cfg->enable  = (UInt32) FALSE;
        vc1Cfg->rangeY  = 0;
        vc1Cfg->rangeUV = 0;
    }
}

static inline void VpsDssDispcVidPipeConfig_init(
    Vps_DssDispcVidPipeConfig *vidPipeCfg)
{
    if (vidPipeCfg != NULL)
    {
        vidPipeCfg->repliEnable      = (UInt32) FALSE;
        vidPipeCfg->scEnable         = VPS_DSS_DISPC_SC_NONE;
        vidPipeCfg->cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;
        vidPipeCfg->chromaSampling   = 0U;
    }
}

static inline void VpsDssDispcVidConfig_init(Vps_DssDispcVidConfig *vidCfg)
{
    if (vidCfg != NULL)
    {
        VpsDssDispcVidPipeConfig_init(&vidCfg->pipeCfg);
        vidCfg->advDmaCfg = NULL;
        vidCfg->vc1Cfg    = NULL;
    }
}

static inline void VpsDssDispcGfxPipeConfig_init(
    Vps_DssDispcGfxPipeConfig *gfxPipeCfg)
{
    if (gfxPipeCfg != NULL)
    {
        gfxPipeCfg->repliEnable       = (UInt32) FALSE;
        gfxPipeCfg->antiFlickerEnable = (UInt32) FALSE;
    }
}

static inline void VpsDssDispcGfxConfig_init(Vps_DssDispcGfxConfig *gfxCfg)
{
    if (gfxCfg != NULL)
    {
        VpsDssDispcGfxPipeConfig_init(&gfxCfg->pipeCfg);
        gfxCfg->advDmaCfg = NULL;
    }
}

static inline void VpsDssDispcWbPipeConfig_init(
    Vps_DssDispcWbPipeConfig *wbPipeCfg)
{
    if (wbPipeCfg != NULL)
    {
        wbPipeCfg->scEnable         = VPS_DSS_DISPC_SC_NONE;
        wbPipeCfg->cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;
    }
}

static inline void VpsDssDispcWbConfig_init(Vps_DssDispcWbConfig *wbCfg)
{
    if (wbCfg != NULL)
    {
        VpsDssDispcWbPipeConfig_init(&wbCfg->pipeCfg);
        wbCfg->advDmaCfg = NULL;
    }
}

static inline void VpsDssDispcOvlyPanelConfig_init(
    Vps_DssDispcOvlyPanelConfig *ovlyPanelCfg)
{
    if (ovlyPanelCfg != NULL)
    {
        ovlyPanelCfg->colorKeyEnable     = (UInt32) FALSE;
        ovlyPanelCfg->colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
        ovlyPanelCfg->deltaLinesPerPanel = 0U;
        ovlyPanelCfg->transColorKey      = 0x00000000U;
        ovlyPanelCfg->backGroundColor    = 0x00000000U;
        ovlyPanelCfg->alphaBlenderEnable = (UInt32) FALSE;
        ovlyPanelCfg->ovlyOptimization   = VPS_DSS_DISPC_OVLY_FETCH_ALLDATA;
    }
}

static inline void VpsDssDispcOvlyPipeConfig_init(
    Vps_DssDispcOvlyPipeConfig *ovlyPipeCfg)
{
    if (ovlyPipeCfg != NULL)
    {
        ovlyPipeCfg->pipeLine         = VPS_DSS_DISPC_PIPE_VID1;
        ovlyPipeCfg->zorder           = VPS_DSS_DISPC_ZORDER0;
        ovlyPipeCfg->zorderEnable     = (UInt32) FALSE;
        ovlyPipeCfg->globalAlpha      = 0xFFU;
        ovlyPipeCfg->preMultiplyAlpha = (UInt32) FALSE;
    }
}
/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-2105)
 */
static inline void VpsDssCscCoeff_init(Vps_DssCscCoeff *cscCoeff)
{
    if (cscCoeff != NULL)
    {
        /* BT601-5 YUV to RGB */
        cscCoeff->ry    = 298;
        cscCoeff->rcr   = 409;
        cscCoeff->rcb   = 0;
        cscCoeff->gy    = 298;
        cscCoeff->gcr   = -((Int16) 208);
        cscCoeff->gcb   = -((Int16) 100);
        cscCoeff->by    = 298;
        cscCoeff->bcr   = 0;
        cscCoeff->bcb   = 517;
        cscCoeff->roff  = 0;
        cscCoeff->goff  = 0;
        cscCoeff->boff  = 0;
    }
}

static inline void VpsDssDispcMflagConfigParam_init(
    Vps_DssDispcMflagConfigParam *mflagParam)
{
    if(mflagParam != NULL)
    {
        mflagParam->globalMflagStart       = 0U;
        mflagParam->globalMflagCtrl        = 0U;
        mflagParam->gfxMflagHighThreshold  = 0U;
        mflagParam->gfxMflagLowThreshold   = 0U;
        mflagParam->vid1MflagHighThreshold = 0U;
        mflagParam->vid1MflagLowThreshold  = 0U;
        mflagParam->vid2MflagHighThreshold = 0U;
        mflagParam->vid2MflagLowThreshold  = 0U;
        mflagParam->vid3MflagHighThreshold = 0U;
        mflagParam->vid3MflagLowThreshold  = 0U;
        mflagParam->wbMflagHighThreshold   = 0U;
        mflagParam->wbMflagLowThreshold    = 0U;
    }
}

static inline UInt32 VpsDss_isWbInNodeFromOvly(UInt32 inNode)
{
    UInt32 isOvlyInput = (UInt32) FALSE;

    if ((VPS_DSS_DISPC_WB_IN_NODE_LCD1 == inNode) ||
        (VPS_DSS_DISPC_WB_IN_NODE_LCD2 == inNode) ||
        (VPS_DSS_DISPC_WB_IN_NODE_LCD3 == inNode) ||
        (VPS_DSS_DISPC_WB_IN_NODE_TV == inNode))
    {
        isOvlyInput = (UInt32) TRUE;
    }

    return (isOvlyInput);
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_DSS_H_ */

/* @} */
