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
 *  \file vpshal_dssDispcOvly.h
 *
 *  \brief HAL layer for the DSS DISPC Video Pipeline Module.
 *  This file exposes the HAL APIs of the DISPC Overlay .
 *  This HAL is meant to be used by other VPS driver. The application don't
 *  have to access this HAL module.
 *
 */

#ifndef VPSHAL_DSS_DISPC_OVLY_H_
#define VPSHAL_DSS_DISPC_OVLY_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum VpsHal_DispcOvlyInstId
 *  \brief Enum to define the various DISPC OVL instance.
 */
typedef enum
{
    VPSHAL_DSS_DISPC_LCD1 = 0,
    /**< DSS DISPC LCD1 instance. */
    VPSHAL_DSS_DISPC_LCD2,
    /**< DSS DISPC LCD2 instance.. */
    VPSHAL_DSS_DISPC_LCD3,
    /**< DSS DISPC LCD3 instance.. */
    VPSHAL_DSS_DISPC_HDMI,
    /**< DSS DISPC HDMI instance. */
    VPSHAL_DSS_DISPC_WBOVR,
    /**< DSS DISPC WB instance. */
    VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_DispcOvlyInstId;

/**
 *  \brief DISPC OVL maximum number of instances for any given platform - used
 *  for memory allocation.
 */
#define VPSHAL_DSS_DISPC_OVLY_MAX_INST             (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DispcOvlyInstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance. For valid values see
     *#VpsHal_DispcOvlyInstId. */
} VpsHal_DispcOvlyInstParams;

/**
 *  struct VpsHal_DispcOvlyOpenParams
 *  \brief Structure to identify a DISPC OVL HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< DISPC OVL Instance ID. For valid values see #VpsHal_DispcOvlyInstId. */
} VpsHal_DispcOvlyOpenParams;

/**
 *  struct VpsHal_DssDispcLcdAdvSignalParam
 *  \brief Advance Signal Params for the overlays(LCD1,LCD2,LCD3) .
 */
typedef struct
{
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
    UInt32 acBiasGated;
    /**< ACBias gated enabled
     *   0x0: AcBias gated disabled
     *   0x1: AcBias gated enabled. */
    UInt32 vSyncGated;
    /**< VSYNC gated enabled
     *   0x0: VSYNC gated disabled
     *   0x1: VSYNC gated enabled. */
    UInt32 hSyncGated;
    /**< HSYNC gated enabled
     *   0x0: HSYNC gated disabled
     *   0x1: HSYNC gated enabled. */
    UInt32 pixelClockGated;
    /**< Pixel clock gated enabled
     *   0x0: Pixel clock gated disabled
     *   0x1: Pixel clock gated enabled.*/
    UInt32 pixelDataGated;
    /**< Pixel data gated enabled
     *   0x0: Pixel data gated disabled
     *   0x1: Pixel data gated enabled. */
    UInt32 pixelGated;
    /**< Pixel gated enable (only for TFT)
     *   0x0: Pixel clock always toggles (only in TFT mode).
     *   0x1: Pixel clock toggles only when there is valid data to
     *   display (only in TFT mode). */
} VpsHal_DssDispcLcdAdvSignalParam;

/**
 *  struct VpsHal_DssDispcLcdSignalPolarityParam
 *  \brief Polarity of Pixel clock, hsync, vsync and actvideo signals
 *   for the overlays(LCD1,LCD2,LCD3). */
typedef struct
{
    UInt32 dvoActVidPolarity;
    /**< Invert output enable
     *   0x0: Ac-bias is active high (active display mode).
     *   0x1: Ac-bias is active low (active display mode). */
    UInt32 pixelClkPolarity;
    /**< Invert pixel clock
     *   0x0: Data is driven on the LCD data lines on the
     *      rising edge of the pixel clock.
     *   0x1: Data is driven on the LCD data lines on the
     *      falling edge of the pixel clock. */
    UInt32 hsPolarity;
    /**< HSYNC Polarity
     *   0x0: Line clock pin is active high and inactive low.
     *   0x1: Line clock pin is active low and inactive high. */
    UInt32 vsPolarity;
    /**< VSYNC Polarity
     *   0x0: Frame clock pin is active high and inactive low.
     *   0x1: Frame clock pin is active low and inactive high. */
}VpsHal_DssDispcLcdSignalPolarityParam;

/**
 *  struct VpsHal_DssDispcLcdOutputParam
 *  \brief Output format , interface width for the overlays(LCD1,LCD2,LCD3). */
typedef struct
{
    UInt32 dvoFormat;
    /**< digital output format. BT656/BT1120/Discrete sync format */
    UInt32 videoIfWidth;
    /**< [IN] Video interface Width. */
} VpsHal_DssDispcLcdOutputParam;

/**
 *  struct VpsHal_DssDispcLcdTimingParam
 *  \brief Timing Params for the LCD overlays(LCD1,LCD2,LCD3) .
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
    UInt32 hFrontPorch;
    /**< Horizontal Front Porch, specifies the number of pixel clock periods
     *   to add to the end of a line transmission before line clock is asserted.
     * */
    UInt32 hBackPorch;
    /**< Horizontal Back Porch, specifies the number of pixel clock periods
     *   to add to the beginning of a line transmission before the first set of
     *   pixels is output to the display. */
    UInt32 hSyncLen;
    /**< Horizontal synchronization pulse width, Encoded Value(from 1 to 256)to
     *   specify the number of pixel clock periods to pulse the line clock
     *   at the end of each line. */
    UInt32 vFrontPorch;
    /**< Vertical front porch encoded value (from 0 to 4095) to
     *   specify the number of line clock periods to add to the end
     *   of each frame. */
    UInt32 vBackPorch;
    /**< Vertical back porch encoded value (from 0 to 4095) to
     *   specify the number of line clock periods to add to the
     *   beginning of a frame. */
    UInt32 vSyncLen;
    /**< Vertical synchronization pulse width In active mode, RW 0x00
     *  encoded value (from 1 to 256) to specify the number of
     *  line clock periods (program to value minus 1) to pulse the
     *  frame clock (VSYNC) pin at the end of each frame after
     *  the end of frame wait (VFP) period elapses. Frame clock
     *  uses as VSYNC signal in active mode. */
} VpsHal_DssDispcLcdTimingParam;

/**
 *  struct VpsHal_DssDispcLcdDivisorParam
 *  \brief Divisor Values for the LCDx overlays(LCD1,LCD2,LCD3) .
 *   DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
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
} VpsHal_DssDispcLcdDivisorParam;

/**
 *  struct VpsHal_DssDispcLcdTimingParam
 *  \brief Timing Params for the LCD overlays(LCD1,LCD2,LCD3) .
 */
typedef struct
{
    UInt32 hFrontPorch;
    /**< Horizontal Front Porch, specifies the number of pixel clock periods
     *   to add to the end of a line transmission before line clock is asserted.
     * */
    UInt32 hBackPorch;
    /**< Horizontal Back Porch, specifies the number of pixel clock periods
     *   to add to the beginning of a line transmission before the first set of
     *   pixels is output to the display. */
    UInt32 hSyncLen;
    /**< Horizontal synchronization pulse width, Encoded Value(from 1 to 256)to
     *   specify the number of pixel clock periods to pulse the line clock
     *   at the end of each line. */
    UInt32 vFrontPorch;
    /**< Vertical front porch encoded value (from 0 to 4095) to
     *   specify the number of line clock periods to add to the end
     *   of each frame. */
    UInt32 vBackPorch;
    /**< Vertical back porch encoded value (from 0 to 4095) to
     *   specify the number of line clock periods to add to the
     *   beginning of a frame. */
    UInt32 vSyncLen;
    /**< Vertical synchronization pulse width In active mode, RW 0x00
     *  encoded value (from 1 to 256) to specify the number of
     *  line clock periods (program to value minus 1) to pulse the
     *  frame clock (VSYNC) pin at the end of each frame after
     *  the end of frame wait (VFP) period elapses. Frame clock
     *  uses as VSYNC signal in active mode. */
} VpsHal_DssDispcLcdBlankTimingParam;

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
} VpsHal_DssDispcMflagConfigParam;

/**
 *  struct VpsHal_DssDispcCprCoeff
 *  \brief  Params for CPR Coefficients for RGB to YUV color conversion.
 */
typedef struct
{
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
} VpsHal_DssDispcCprCoeff;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsHal_dssOvlyEnable
 *  \brief Configures the Video/Gfx pipeline params related to overlay.
 *
 *  This function will enable or disable the overlay
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param enable           enable or disable the Overlay
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnable(VpsHal_Handle handle,
                           UInt32        enable);

/**
 *  VpsHal_dssOvlyInit
 *  \brief DISPC OVL HAL init function.
 *
 *  Initializes OVL objects, gets the register overlay offsets for DISPC OVL
 *  registers.
 *  This function should be called before calling any of DISPC OVL HAL API's.
 *
 *  \param numInst          Number of instance objects to be initialized
 *  \param instPrms         Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *                          This parameter should not be NULL.
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyInit(UInt32                            numInst,
                         const VpsHal_DispcOvlyInstParams *instPrms,
                         Ptr                               arg);

/**
 *  VpsHal_dssOvlyDeInit
 *  \brief DSS DISPC OVL HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyDeInit(Ptr arg);

/**
 *  VpsHal_dssDefaultParalleSelect
 *  \brief Default select Mux 13 value.
 *
 *  By default, the input to DPI is TV input, which shows HDMI output on
 *  LCD too. To solve that, initialize the mux to have a default value of
 *  LCD1.
 *
 *  \param                 None
 *
 *  \return                 Returns BSP_SOK on success
 */

Int32 VpsHal_dssDefaultParalleSelect(void);

/**
 *  VpsHal_dssOvlyOpen
 *  \brief Returns the handle to the requested DISPC OVL(Overlay) instance.
 *
 *  This function should be called prior to calling any of the DISPC OVL HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param halId            Requested DISPC OVL instance.
 *
 *  \return                 Returns DISPC OVL instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_dssOvlyOpen(
    const VpsHal_DispcOvlyOpenParams *openPrms);

/**
 *  VpsHal_dssOvlyClose
 *  \brief Closes the DISPC OVL HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyClose(VpsHal_Handle handle);

/**
 *  VpsHal_dssOvlyGetHandle
 *  \brief Returns the overlay HAL handle
 *
 *  \param halId        Requested DISPC OVL instance #VpsHal_DispcOvlyInstId.
 *
 *  \return             Returns DISPC OVL instance handle on success else
 *                      returns NULL.
 */
VpsHal_Handle VpsHal_dssOvlyGetHandle(UInt32 halId);

/**
 *  VpsHal_dssOvlySetGoBit
 *  \brief GO command for the Overlay output. It is used to
 *   synchronized the pipelines (graphics and/or video ones)
 *   associated with the overlay output..
 *
 *  This function will Set the Go Bit of the overlay
 *
 *  \param ovlId           Valid Overlay Id
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetGoBit(UInt32 ovlyId);

/**
 *  VpsHal_dssOvlyGetGoBit
 *  \brief Returns the Value of the GoBit.
 *
 *  This function will Return the status of the Go bit.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param bitVal           Pointer to a variable, varialbe is set to 0 if the
 *                          previous applied configuration by the software is
 *                          accepted by hardware.sets to 1 if Its not accepted.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetGoBit(VpsHal_Handle handle, UInt32 *bitVal);

/**
 *  VpsHal_dssOvlyPipeConfig
 *  \brief Configures the Video/Gfx pipeline params related to overlay.
 *
 *  This function will configure the pipeline parameters like to which overlay
 *  the pipeline should be connected to, z-order of displays, globalalpha and
 *  premultiply alpha
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param pipeCfg          Pointer to the Overlay Pipe config structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyPipeConfig(VpsHal_Handle                     handle,
                               const Vps_DssDispcOvlyPipeConfig *pipeCfg);

/**
 *  VpsHal_dssOvlyPanelConf
 *  \brief Configures the overlay.
 *
 *  This function will configure the pipeline parameters like to which overlay
 *  the pipeline should be connected to, z-order of displays, globalalpha and
 *  premultiply alpha
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param pipeConf         Pointer to the Overlay Pipe config structure.
 *                          This parameter should not be NULL.
 *  \param pipe             This specifies to which pipe this configuration
 *                           should be applied to
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyPanelConf(
    VpsHal_Handle handle,
    const Vps_DssDispcOvlyPanelConfig *
    panelConfig);

/**
 *  VpsHal_dssOvlyLcdAdvDispConfig
 *  \brief Configures the Advance LCD Overlay Display Params.
 *
 *  This function will configures Advance LCD Overlays Display parameters, like
 *  Stall Mode, number of data lines, fid sequence.
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTdmConfig     Pointer to the LCD Overlay Advance Display Param
 *                          structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdAdvDispConfig(
    VpsHal_Handle                          handle,
    const Vps_DssDispcLcdAdvDisplayConfig *lcdAdvDisplay);

/**
 *  VpsHal_dssOvlyLcdTdmConfig
 *  \brief Configures the LCD TDM(Time division multiplexing) Params.
 *
 *  This function will configures LCD Overlay's TDM parameters, like Number of
 *  bits per each cycle, bit alignment for all pixels.
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTdmConfig     Pointer to the LCD Overlay TDM Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdTdmConfig(
    VpsHal_Handle handle,
    const Vps_DssDispcAdvLcdTdmConfig *
    lcdTdmConfig);

/**
 *  VpsHal_dssOvlyLcdConfLineNum
 *  \brief Set the LineNumber at which the interrupt should be generated
 *
 *  This function will configures set the Line number in the overlay
 *  when the display reaches this line it will generate the Interrupt.
 *
 *  \param handle        Valid handle returned by VpsHal_dssOvlyOpen
 *                       function
 *  \param lineNum       Line Number that should be programmed in the register .
 *
 *  \return              Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdConfLineNum(
    VpsHal_Handle handle,
    UInt32        lineNum);

/**
 *  VpsHal_dssOvlyLcdSetTiming
 *  \brief Configures the LCD Timing Params.
 *
 *  This function will configures LCD Overlay Timing Parameters, like front
 *  porch, back porch , divider values
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTimingParm    Pointer to the LCD Timing Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSetTiming(
    VpsHal_Handle handle,
    VpsHal_DssDispcLcdTimingParam *
    lcdTimingParm);

/**
 *  VpsHal_dssOvlyLcdGetBlankTiming
 *  \brief returns the LCD Blank Timing Params.
 *
 *  This function will return the currently configured LCD Overlay Blank Timing
 *  Parameters, like front porch, back porch, sync values.
 *  \param handle               Valid handle returned by VpsHal_dssOvlyOpen
 *                              function
 *  \param lcdBlankTimingParm   Pointer to the LCD Blanking Timing Param
 *                              structure. This parameter should not be NULL.
 *  \return                     Returns BSP_SOK on success else returns error
 *                              value
 */
Int32 VpsHal_dssOvlyLcdGetBlankTiming(
    VpsHal_Handle handle,
    VpsHal_DssDispcLcdBlankTimingParam *
    lcdBlankTimingParm);

/**
 *  VpsHal_dssOvlyLcdSetBlankTiming
 *  \brief Configures the LCD Blank Timing Params.
 *
 *  This function will configures LCD Overlay Blank Timing Parameters
 *  like front porch, back porch, sync values.
 *  \param handle               Valid handle returned by VpsHal_dssOvlyOpen
 *                              function
 *  \param lcdBlankTimingParm   Pointer to the LCD Blanking Timing Param
 *                              structure. This parameter should not be NULL.
 *  \return                     Returns BSP_SOK on success else returns error
 *                              value
 */
Int32 VpsHal_dssOvlyLcdSetBlankTiming(
    VpsHal_Handle handle,
    const VpsHal_DssDispcLcdBlankTimingParam *
    lcdBlankTimingParm);

/**
 *  VpsHal_dssOvlyLcdSetClkDivisors
 *  \brief Configures the LCD Divisor Params.
 *
 *  This function will configures LCD and PCD divisor values for
 *  the overlays. Resultant pixel clock is as per formula
 *  DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdDivisorParm    Pointer to the LCD Divisor Param structure,
 *                             VpsHal_DssDispcLcdDivisorParam.This parameter
 *  should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSetClkDivisors(
    VpsHal_Handle handle,
    const VpsHal_DssDispcLcdDivisorParam *
    lcdDivisorParm);

/**
 *  VpsHal_dssOvlyLcdAdvSignalConf
 *  \brief Configures the LCD Overlay signal Params.
 *
 *  This function will configure Advance Signal parameters like polarity of
 *  Pixel clock, Hsync, Vsync data sampling at raising edge or falling edge
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdAdvSignalConf(
    VpsHal_Handle                         handle,
    const Vps_DssDispcLcdAdvSignalConfig *lcdSignalParm);

/**
 *  VpsHal_dssOvlyLcdSignalPolarityConf
 *  \brief Configures the Polarity of LCD Overlay signals(hsync,vsync,pclk,DE).
 *
 *  This function will configure Signal parameters like polarity of
 *  Pixel clock, Hsync, Vsync and active video.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSignalPolarityConf(
    VpsHal_Handle handle,
    VpsHal_DssDispcLcdSignalPolarityParam *
    lcdSignalPolParm);

/**
 *  VpsHal_dssOvlyLcdOutputConf
 *  \brief Configures the data format and interface width of LCD Overlay,
 *
 *  This function will configure Output parameters of LCD overlay.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdOutputConf(
    VpsHal_Handle handle,
    const VpsHal_DssDispcLcdOutputParam *
    lcdOutParm);

/**
 *  VpsHal_dssOvlyGetLineNum
 *  \brief Get the lineNumber of the overlay.
 *
 *  This function will give the current line number going on for an overlay
 *
 *  \param ovlId           Valid Ovlerlay ID
 *
 *  \param lineNum         pointer to linenumber variable
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetLineNum(UInt32  ovlyId,
                               UInt32 *lineNum);

/**
 *  VpsHal_dssOvlyGetIRQStat
 *  \brief This function will give the details of the interrupt signals
 *  that are currently being set.
 *
 *  This function will give the details of the interrupt being set
 *
 *  \param                void
 *
 *  \return               Returns List of interrupts being set on success else
 *                          zero.
 */
UInt64 VpsHal_dssOvlyGetIrqStat(void);

/**
 *  VpsHal_dssOvlyClearIrq
 *  \brief This function will clear the Interrupts.
 *
 *  This function will clear the list of interrupts
 *
 *  \param                void
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyClearIrq(UInt64 irqStatus);

/**
 *  VpsHal_dssOvlyEnableIntr
 *  \brief This function will Enable the Vync Interrupt of a particular Overlay
 *
 *  This function will Enable the interrupts related to particular overlay
 *
 *  \param                ovlHalId - Overlay HAL ID
 *
 *  \param                enable - enable or disable the interrupt
 *                          (1 to enable and 0 to disable)
 *
 *  \return               Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnableIntr(UInt32 ovlHalId, UInt32 enable);

/**
 *  VpsHal_dssOvlyBypassTvGamma
 *  \brief Enable or bypass Tv Gamma Table
 *
 *  This function will enable/bypass TV gamma table
 *
 *  \param enable          0 - bypass, 1- enable
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnableTvGamma(UInt32 enable);

/**
 *  VpsHal_dssOvlySetDispcMode
 *  \brief Configures the DISPC Mode
 *
 *  This function will configure the DISPC into master/slave mode.Applicable
 *  only for Tda3xx platform.
 *
 *  \param enable          1 - master, 0 - slave
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetDispcMode(UInt32 dispcMode);

/**
 *  VpsHal_dssOvlyDpiEnable
 *  \brief Enables/Disables the DPI output
 *
 *  This function will enable or disables the DPI output.Applicable
 *  only for Tda3xx platform.
 *
 *  \param enable          TRUE - enable, FALSE - disable
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyDpiEnable(UInt32 dpiEnable);

/**
 *  Vpshal_dssOvlySetTvRes
 *  \brief sets the resolution of the TV overlay
 *
 *  This function will set the resolution of the TV overlay
 *
 * \return Returns BSP_SOK on success else returns error value
 *
 */
Int32 Vpshal_dssOvlySetTvRes(UInt32 height, UInt32 width);

/**
 *  VpsHal_dssOvlySetLoadMode
 *  \brief Selects the Load mode for graphics pipeline
 *
 *  This function will select the load mode for graphics pipeline
 *
 *  \param loadMode    0 - Palette/Gamma Table and data are loaded every frame
 *                     1 -  Palette/Gamma Table to be loaded
 *                     2 -  Frame data only loaded every frame
 *                     3 -  Palette/Gamma Table and frame data loaded on first
 *                                 frame then switch to 0x2 (Hardware)
 *
 *  \return     Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetLoadMode(UInt32 loadMode);

/**
 *  VpsHal_dssOvlySetParallelMux
 *  \brief Sets the Parallel Mux for DPI1 output
 *
 *  This function will Set Parallel Mux for DPI1 Output
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetParallelMux(UInt32 ovlyId);

/**
 *  VpsHal_dssOvlySetSize
 *  \brief Sets the overlay size parameters.
 *
 *  \param ovlId        Valid Overlay Id
 *  \param ovlyWidth    Overlay width
 *  \param ovlyHeight   Overlay height
 *
 *  \return             Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetSize(UInt32 ovlyId, UInt32 ovlyWidth, UInt32 ovlyHeight);

/**
 *  VpsHal_dssOvlySetCprCoeff
 *  \brief Configures the coefficients for color phase rotation of overlay.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param coeff            pointer to cpr coefficients
 *                          This parameter should not be NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetCprCoeff(VpsHal_Handle handle,
                                const VpsHal_DssDispcCprCoeff *coeff);

/**
 *  VpsHal_dssOvlyGetCprCoeff
 *  \brief Configures the coefficients for color phase rotation of overlay.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param coeff            pointer to get cpr coefficients
 *                          This parameter should not be NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetCprCoeff(VpsHal_Handle handle,
                                VpsHal_DssDispcCprCoeff *coeff);

/**
 *  VpsHal_dssOvlySetMflagConfig
 *  \brief Configures the mflag parameters.
 *
 *  \param mflagCfg         pointer to mflag configuration parameter.
 *                          This parameter should not be NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
void VpsHal_dssOvlySetMflagConfig(const VpsHal_DssDispcMflagConfigParam *mflagCfg);

/**
 *  VpsHal_dssOvlyGetMflagConfig
 *  \brief returns the mflag parameters.
 *
 *  \param mflagCfg         pointer to mflag configuration parameter.
 *                          This parameter should not be NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
void VpsHal_dssOvlyGetMflagConfig(VpsHal_DssDispcMflagConfigParam *mflagCfg);
#if defined (SOC_TDA3XX)

/**
 *  VpsHal_dssOvlyUpdatePanelSizeSdVenc
 *  \brief Update the panel size increase PPL by 2. This is required for
 *         sd venc display for tda3xx.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyUpdatePanelSizeSdVenc(VpsHal_Handle handle);
#endif
#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_DSS_DISPC_OVLY_H_ */
