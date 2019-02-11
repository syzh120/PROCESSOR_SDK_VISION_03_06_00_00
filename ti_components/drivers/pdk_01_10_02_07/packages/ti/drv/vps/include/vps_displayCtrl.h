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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_DCTRL_API Display Controller API
 *
 *  @{
 */

/**
 *  \file vps_displayCtrl.h
 *
 *  \brief Display Controller Driver
 *  Generic Display Controller Driver Interface file.
 */

#ifndef VPS_DISPLAY_CTRL_H_
#define VPS_DISPLAY_CTRL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>
#include <ti/drv/vps/include/vps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  Macros for display controller instance numbers to be passed as instance ID
 *  at the time of driver create.
 *  Note: These are read only macros. Don't modify the value of these macros.
 */

/**
 *  \name DCTRL Instance ID's
 *
 *  @{
 */

/** \brief Display controller instance 0. */
#define VPS_DCTRL_INST_0                (0U)

/* @} */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_DCTRL
 *  @{
 */

/** \brief Command to set the entire VPS display path configuration in
 *  one shot.
 *
 *  All the VPS modules handled by the Display Controller can be
 *  represented by a graph, where node represents a module like blender,
 *  mux etc. and edge is present between two nodes if they are connected. All
 *  VPS paths can be configured by this IOCTL in one shot. Use macro
 *  defined in this file for input path, muxes
 *  output and blender(overlay) as the node numbers.
 *
 *  This IOCTL takes either name of the pre-defined configuration or
 *  list of edges
 *  connecting nodes and configures display paths.
 *  It first validates these paths and then configures VPS for the display
 *  paths. It configures all the modules present in the path.
 *
 * \par This IOCTL cannot be used for clearing configuration on a path
 *      streaming path.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlConfig
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_SET_CONFIG      (VPS_DCTRL_IOCTL_BASE + 0x01U)

/** \brief Command to clear the VPS display path configuration in
 *  one shot.
 *
 *  This IOCTL takes either name of the pre-defined configuration or
 *  list of edges
 *  connecting nodes and clears the configuration. It also stops vencs.
 *
 *  It does not validates the edge list. It simply disables the edge
 *  connecting nodes. For the vencs, it checks for the validity and then
 *  disables the venc if there are not errors.
 *
 *  Use macro defined in this file for input path, muxes
 *  output and blender(overlay) as the node numbers.
 *
 * \par This IOCTL cannot be used for clearing configuration on a path
 *      streaming path.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlConfig
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_CLEAR_CONFIG    (VPS_DCTRL_IOCTL_BASE + 0x02U)

/** \brief Command to set output in the given Venc.
 *
 *  This IOCTL is used to set the output i.e. dataformat, polarities of all the
 *  signals of the given venc if venc is not on. For the tied vencs, venc has to
 *  be stopped first, then output can can be changed.This IOCTL should be called
 *  before SET_CONFIG_IOCTL.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlOutputInfo
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_VENC_OUTPUT (VPS_DCTRL_IOCTL_BASE + 0x03U)

/** \brief Command to get output in the given Venc.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlOutputInfo
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_GET_VENC_OUTPUT (VPS_DCTRL_IOCTL_BASE + 0x04U)

/** \brief Command to set output in the given Venc.
 *
 *  This IOCTL is used to set the Overlay parameters like transparency color
 *  key,
 *  background color, alphablender, overlay optimization etc.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DssDispcOvlyPanelConfig
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_OVLY_PARAMS (VPS_DCTRL_IOCTL_BASE + 0x05U)

/** \brief Command to set Pipeline related params.
 *
 *  This IOCTL is used to set the pipeline parameters related to display
 *  contoller like Zorder, global alpha and premultiply alpha.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DssDispcOvlyPipeConfig
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS  (VPS_DCTRL_IOCTL_BASE + 0x06U)

/** \brief Command to set Venc(Overlay) pixel clock divisor params.
 *
 *  This IOCTL is used to set the divisor values for the Venc pixel clock.
 *   DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlVencDivisorInfo
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS  (VPS_DCTRL_IOCTL_BASE + 0x07U)

/** \brief Command to enable/disable the SDVENC.
 *
 *  This IOCTL is used to Enable/disable and Init/deinit the SD VENC.
 *  This IOCTL should be called before calling any SD VENC related IOCTL.
 *  In this IOCTL we put the Display Controller in Slave Mode and Disable
 *  the DPI output when SD Is Enabled. When its disabled we put DIPSC
 *  back to master mode and enable the DPI output.
 *  This IOCTL should be called after IOCTL_VPS_DCTRL_SET_CONFIG IOCTL
 *
 * \param   cmdArgs [IN] (UInt32*) value enable/disable the SD-VENC
 *                                1- enable
 *                                0 - disable
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_ENABLE_SDVENC  (VPS_DCTRL_IOCTL_BASE + 0x08U)

/** \brief Command to configure the SDVENC for particular video mode(NTSC/PAL).
 *
 *  This IOCTL is used to configure the SD-VENC for different video modes like
 *  NTSC, PAL variants.
 *
 *  \param   cmdArgs [IN]  pointer of type Vps_DctrlSDVencVideoStandard.
 *                         Standard to which the SDVENC should be configured for
 *                         For valid values see #Fvid2_Standard. Supported only
 *                         NTSC and PAL Format as of now.
 *  \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_SDVENC_MODE  (VPS_DCTRL_IOCTL_BASE + 0x09U)

/** \brief IOCTl to get the count of number of sync losts of all the overlays
 *  and ocp error.
 *
 *  This IOCTL is used to get the count of number of sync losts occured for all
 *  the applicable overlays and number of ocp errors occured.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DctrlErrorSyncLostStats.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_GET_ERROR_STATS   (VPS_DCTRL_IOCTL_BASE + 0x0AU)

/** \brief IOCTl to get the sdvenc default configuration.
 *
 *  This IOCTL is used initialize the object of Vps_DssDispcSdVencAdvConfig
 *  passed in cmdArgs with the default values.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssDispcSdVencAdvConfig.
 *          Vps_DssDispcSdVencAdvConfig->videoStandard should be set
 *          to get proper default values
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SDVENC_GET_DEF_ADV_CONFIG  (VPS_DCTRL_IOCTL_BASE + \
                                                    0x0BU)

/** \brief IOCTl to set the sdvenc configuration.
 *
 *  This IOCTL is used to set the sd venc configuration using the object of
 *  Vps_DssDispcSdVencAdvConfig passed in cmdArgs.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssDispcSdVencAdvConfig.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SDVENC_SET_ADV_CONFIG  (VPS_DCTRL_IOCTL_BASE + 0x0CU)

/** \brief IOCTl to get the venc blanking timing.
 *
 *  This IOCTL is used to get the current venc blanking timing information in
 *  the object of type Vps_DctrlVencBlankTiming passed in cmdArgs. This ioctl
 *  can be called dynamically at runtime after IOCTL_VPS_DCTRL_SET_CONFIG.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DctrlVencBlankTiming.
 *          Vps_DctrlVencBlankTiming->vencId  should be set appropriately.
 *          Use one of the following values for the venc id -
 *          VPS_DCTRL_DSS_VENC_LCD1, VPS_DCTRL_DSS_VENC_LCD2,
 *          VPS_DCTRL_DSS_VENC_LCD3.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_GET_VENC_BLANK_TIMING  (VPS_DCTRL_IOCTL_BASE + 0x0DU)

/** \brief IOCTl to set the venc blanking timing.
 *
 *  This IOCTL is used to set the venc mode information using the object of
 *  Vps_DctrlVencBlankTiming passed in cmdArgs. This ioctl can be called
 *  dynamically at runtime after IOCTL_VPS_DCTRL_SET_CONFIG.
 *  Note: The change in timing will take effect from the next vsync.
 *  This API should be called in the vsync callback to the application in the
 *  ISR context or immediately after that in task/swi context. Calling this
 *  ioctl near the vsync should be avoided as the shadow to work copy could
 *  happens while we are changing the timing parameters and could result in
 *  taking only a part of this configuration for next one frame or delaying the
 *  timing change by next one frame. Subsequent frames will have proper timing.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DctrlVencBlankTiming.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_VENC_BLANK_TIMING  (VPS_DCTRL_IOCTL_BASE + 0x0EU)

/** \brief IOCTl to set coefficients for color phase rotation of overlay.
 *
 *  This IOCTL can be used to set the CPR coefficients.
 *  Note: Default BT601 coefficients are set.
 *        IOCTL_VPS_DCTRL_SET_VENC_OUTPUT ioctl will disable CPR and
 *        enable/disable CSC based dvo Format, this is not changed for backward
 *        compatibility.
 *        This ioctl should be called after IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT
 *        to enable/disable CPR and CSC. also note that both the CRP and CSC
 *        should not be enabled simultaneously.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssVencCprCoeff.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_CPR_COEFF  (VPS_DCTRL_IOCTL_BASE + 0x0FU)

/** \brief IOCTl to get coefficients for color phase rotation of overlay.
 *
 *  This IOCTL can be used to get the CPR coefficients.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssVencCprCoeff.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_GET_CPR_COEFF  (VPS_DCTRL_IOCTL_BASE + 0x10U)

/**
 * \brief IOCTl to flip the data (D0, D1, D2) P and N pad control of HDMI output
 *
 *  This IOCTL is typically not used and is requried only when there is
 *  an issue in the board layout in swapping the pads. This is applicable
 *  only for TDA2xx, TDA2Px and TDA2Ex.
 *
 * \param   cmdArgs [IN]  NULL, not used
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_HDMI_FLIP_DATA_P_N_ORDER    (VPS_DCTRL_IOCTL_BASE + 0x11U)

/**
 * \brief IOCTl to set the mflag paramters
 *
 *  This IOCTL can be used to set the mflag parameters currently configured.
 *
 * \param   cmdArgs [IN] pointer of type Vps_DssDispcMflagConfigParam.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_MFLAG_PARAM    (VPS_DCTRL_IOCTL_BASE + 0x12U)

/**
 * \brief IOCTl to get the mflag paramters
 *
 *  This IOCTL can be used to get the mflag parameters currently configured.
 *
 * \param   cmdArgs [IN] pointer of type Vps_DssDispcMflagConfigParam.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_GET_MFLAG_PARAM    (VPS_DCTRL_IOCTL_BASE + 0x13U)

/* ========================================================================== */
/* ========================================================================== */
/*                      Part-3 Advanced Configuration                         */
/* ========================================================================== */
/* ========================================================================== */

/** \brief Advanced configurations
 *
 *  Marker used to denote the begining of IOCTLs that would be required
 *  for advanced control
 *
 *  \par CAUTION Ensure that basic IOCTL value does not execeed this value
 */
#define VPS_DCTRL_IOCTL_ADV_BASE    (VPS_DCTRL_IOCTL_BASE + 0x100U)

/** \brief Command to program advance Venc Signal parameters
 *
 *  This IOCTL is used to program the advance signal parameters for the VENCS,
 *  parameters include when the Hsync and Vsync should be driver(rising or
 *  falling
 *  edge of the pixel clock), Hsync,Vsync,pixelclock,pixel data signals are
 *  gated, aC bias pin transition , ac bias pin frequency etc.
 *  This is valid only for first three VENCS(DPI1/DPI2/DPI3),
 *  not valid for VPS_DCTRL_DSS_VENC_HDMI.
 *
 * \param   cmdArgs [IN]     Pointer of type Vps_DssDispcLcdAdvSignalConfig.
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_SIGNAL_PARAMS  ( \
        VPS_DCTRL_IOCTL_ADV_BASE +                        \
        0x1U)

/** \brief Command to program advance Venc Display parameters
 *
 *  This IOCTL is used to program the advance Display parameters for the VENCS
 *  like stall mode, number of tft datalines, scanformat, which fid to display
 *  first etc.
 *  This is valid only for first three VENCS(DPI1/DPI2/DPI3),
 *  not valid for VPS_DCTRL_DSS_VENC_HDMI.
 *
 *
 * \param   cmdArgs [IN]     Pointer of type Vps_DssDispcLcdAdvDisplayConfig.
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_DISP_PARAMS  (VPS_DCTRL_IOCTL_ADV_BASE \
                                                       + 0x2U)

/** \brief Command to program advance Venc TDM(Time division multiplexing)
 *  parameters
 *
 *  This IOCTL is used to program all the parameters related to TDM display.
 *  This is valid only for first three VENCS(DPI1/DPI2/DPI3),
 *  not valid for VPS_DCTRL_DSS_VENC_HDMI.
 *
 * \param   cmdArgs [IN]     Pointer of type Vps_DssDispcAdvLcdTdmConfig.
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_TDM_PARAMS  (VPS_DCTRL_IOCTL_ADV_BASE \
                                                      + 0x3U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_DISPLAY_CTRL_H_ */

/* @} */
