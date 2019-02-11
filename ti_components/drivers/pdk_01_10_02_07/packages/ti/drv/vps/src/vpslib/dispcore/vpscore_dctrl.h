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
 *  \file vpscore_dctrl.h
 *
 *  \brief VPS display DSS core interface.
 *  This file defines the interface for the DSS display core.
 *
 */

#ifndef VPSCORE_DCTRL_H_
#define VPSCORE_DCTRL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/common/vps_evtMgr.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPSCORE_DCTRL
 *  @{
 */

#define VPSCORE_DCTRL_IOCTL_BASE    (0x0U)

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
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPSCORE_DCTRL_SET_CONFIG      (VPSCORE_DCTRL_IOCTL_BASE + 0x01U)

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
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPSCORE_DCTRL_CLEAR_CONFIG    (VPSCORE_DCTRL_IOCTL_BASE + 0x02U)

/** \brief Command to set output in the given Venc.
 *
 *  This IOCTL is used to set the output i.e. dataformat, polarities of all the
 *  signals of the given venc if venc is not on. For the tied vencs, venc has to
 *  be stopped first, then output can can be changed.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlOutputInfo
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT (VPSCORE_DCTRL_IOCTL_BASE + 0x03U)

/** \brief Command to get output in the given Venc.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlOutputInfo
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPSCORE_DCTRL_GET_VENC_OUTPUT (VPSCORE_DCTRL_IOCTL_BASE + 0x04U)

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
#define IOCTL_VPSCORE_DCTRL_SET_OVLY_PARAMS (VPSCORE_DCTRL_IOCTL_BASE + 0x05U)

/** \brief Command to set Pipeline related params.
 *
 *  This IOCTL is used to set the pipeline parameters related to display
 *  contoller like Zorder, global alpha and premultiply alpha.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DssDispcOvlyPipeConfig
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_SET_PIPELINE_PARAMS  (VPSCORE_DCTRL_IOCTL_BASE + \
                                                  0x06U)

/** \brief Command to set Venc(Overlay) pixel clock divisor params.
 *
 *  This IOCTL is used to set the divisor values for the Venc pixel clock.
 *   DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlVencDivisorInfo
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_SET_VENC_PCLK_DIVISORS  (VPSCORE_DCTRL_IOCTL_BASE + \
                                                     0x07U)

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
#define IOCTL_VPSCORE_DCTRL_SET_ADV_VENC_TDM_PARAMS  (VPSCORE_DCTRL_IOCTL_BASE \
                                                      +                        \
                                                      0x08U)

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
 #define IOCTL_VPSCORE_DCTRL_SET_ADV_VENC_DISP_PARAMS  ( \
        VPSCORE_DCTRL_IOCTL_BASE +                       \
        0x09U)

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
  #define IOCTL_VPSCORE_DCTRL_SET_ADV_VENC_SIGNAL_PARAMS  ( \
        VPSCORE_DCTRL_IOCTL_BASE +                          \
        0x0AU)

/** \brief Command to enable/disable the SDVENC.
 *
 *  This IOCTL is used to Enable/disable and Init/deinit the SD VENC.
 *  This IOCTL should be called before calling any SD VENC related IOCTL
 *
 * \param   cmdArgs [IN]  UInt32 *.
 *                        1- enable
 *                        0 - disable
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_ENABLE_SDVENC  (VPSCORE_DCTRL_IOCTL_BASE + 0x0BU)

/** \brief Command to configure the SDVENC for particular video mode(NTSC/PAL).
 *
 *  This IOCTL is used to configure the SD-VENC for different video modes
 *  like NTSC, PAL variants.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DctrlSDVencVideoStandard.
 *                        Standard to whcih the SDVENC should be configured for.
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_SET_SDVENC_MODE  (VPSCORE_DCTRL_IOCTL_BASE + 0x0CU)

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
#define IOCTL_VPSCORE_DCTRL_GET_ERROR_STATS       (VPSCORE_DCTRL_IOCTL_BASE + \
                                                   0x0DU)

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
#define IOCTL_VPSCORE_DCTRL_GET_DEF_SDVENC_ADV_CONFIG  ( \
        VPSCORE_DCTRL_IOCTL_BASE + 0x0EU)

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
#define IOCTL_VPSCORE_DCTRL_SET_SDVENC_ADV_CONFIG  (VPSCORE_DCTRL_IOCTL_BASE + \
                                                    0x0FU)

/** \brief IOCTl to get the venc blanking timing.
 *
 *  This IOCTL is used to get the current venc blanking timing information in
 *  the object of type Vps_DctrlVencBlankTiming passed in cmdArgs. This ioctl
 *  can be called dynamically at runtime after IOCTL_VPSCORE_DCTRL_SET_CONFIG.
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
#define IOCTL_VPSCORE_DCTRL_GET_VENC_BLANK_TIMING  (VPSCORE_DCTRL_IOCTL_BASE + \
                                                  0x10U)

/** \brief IOCTl to set the venc blanking timing.
 *
 *  This IOCTL is used to set the venc mode information using the object of
 *  Vps_DctrlVencBlankTiming passed in cmdArgs. This ioctl can be called
 *  dynamically at runtime after IOCTL_VPSCORE_DCTRL_SET_CONFIG.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DctrlVencBlankTiming.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_SET_VENC_BLANK_TIMING  (VPSCORE_DCTRL_IOCTL_BASE + \
                                                  0x11U)

/** \brief IOCTl to set coefficients for color phase rotation of overlay.
 *
 *  This IOCTL can be used to set the CPR coefficients.
 *  Note: Default BT601 coefficients are set.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssVencCprCoeff.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_SET_CPR_COEFF  (VPSCORE_DCTRL_IOCTL_BASE + 0x12U)

/** \brief IOCTl to get coefficients for color phase rotation of overlay.
 *
 *  This IOCTL can be used to get the CPR coefficients.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssVencCprCoeff.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPSCORE_DCTRL_GET_CPR_COEFF  (VPSCORE_DCTRL_IOCTL_BASE + 0x13U)

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
#define IOCTL_VPSCORE_DCTRL_HDMI_FLIP_DATA_P_N_ORDER                           \
                                    (VPSCORE_DCTRL_IOCTL_BASE + 0x14U)
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
#define IOCTL_VPSCORE_DCTRL_SET_MFLAG_PARAM   (VPSCORE_DCTRL_IOCTL_BASE + 0x15U)

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
#define IOCTL_VPSCORE_DCTRL_GET_MFLAG_PARAM   (VPSCORE_DCTRL_IOCTL_BASE + 0x16U)

/* @} */

typedef enum
{
    GRAPH_DCTRL_DSS_INVALID,

    /* Overlay */
    GRAPH_DCTRL_DSS_VID1,
    GRAPH_DCTRL_DSS_VID2,
    GRAPH_DCTRL_DSS_VID3,
    GRAPH_DCTRL_DSS_GFX,
    GRAPH_DCTRL_DSS_WB,
    /* blender */
    GRAPH_DCTRL_DSS_LCD1_BLENDER,
    GRAPH_DCTRL_DSS_LCD2_BLENDER,
    GRAPH_DCTRL_DSS_LCD3_BLENDER,
    GRAPH_DCTRL_DSS_HDMI_BLENDER,
    /* output */
    GRAPH_DCTRL_DSS_DPI1_OUTPUT,
    GRAPH_DCTRL_DSS_DPI2_OUTPUT,
    GRAPH_DCTRL_DSS_DPI3_OUTPUT,
    GRAPH_DCTRL_DSS_HDMI_OUTPUT,

    GRAPH_DCTRL_DSS_NUM_NODES
} VpsCore_DctrlGraphNodes;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32        dispcIrqNumber;
    /**< DISPC IRQ number at CPU level INTC. */
    UInt32        dctrlId;

    VpsHal_Handle ovlHandle[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
} VpsCore_DctrlInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsCore_dctrlInit
 *  \brief Initialize DSS Instance.
 *
 *  \param initParams       Valid handle returned by #TODO function.
 *
 *  \return                 success: Valid #VpsCore_Inst
 *                          failure: NULL
 */
VpsCore_Inst VpsCore_dctrlInit(const VpsCore_DctrlInitParams *initParams);

/**
 *  VpsCore_dctrlDeInit
 *  \brief Free Dctrl instance.
 *
 *  \param pDssHandle     Valid #VpsCore_Inst.
 *
 *  \return               success: Valid #VpsCore_Inst
 *                        failure: NULL
 */
Int32 VpsCore_dctrlDeInit(VpsCore_Inst pDctrlHandle);

/**
 *  VpsCore_dctrlGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dctrlGetCoreOps(void);

#ifdef __cplusplus
}
#endif

#endif /*VPSCORE_DSS_H_*/

