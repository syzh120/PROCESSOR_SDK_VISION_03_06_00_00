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
 *  \file vpshal_vipTop.h
 *
 *  \brief HAL Header file for VIP-TOP
 *  This file exposes the HAL APIs of the VIP Clock and Reset control
 *  modules, Interrupts and Muxes
 *
 */

#ifndef VPSHAL_VIPTOP_H_
#define VPSHAL_VIPTOP_H_

/* TODO: Interrupt related API pending */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define VPSHAL_VIP_TOP_MAX_INST  (VPSHAL_NUM_VIP_INST)

/**
 *  enum VpsHal_VipTopModule
 *  \brief Enum for selecting different modules within VIP
 *  Used in enabling/disabling/reset/unreset APIs
 */
typedef enum
{
    VPSHAL_VIP_TOP_S0_DP,
    /**< Slice 0 Data path */

    VPSHAL_VIP_TOP_S1_DP,
    /**< Slice 1 Data path */

    VPSHAL_VIP_TOP_VPDMA,
    /**< VPDMA */

    VPSHAL_VIP_TOP_S0_PARSER,
    /**< Slice 0 Parser */

    VPSHAL_VIP_TOP_S0_CHRDS0,
    /**< Slice 0 Chroma down-sample instance 0 */

    VPSHAL_VIP_TOP_S0_CHRDS1,
    /**< Slice 0 Chroma down-sample instance 1 */

    VPSHAL_VIP_TOP_S0_CSC,
    /**< Slice 0 Color space converter */

    VPSHAL_VIP_TOP_S0_SC,
    /**< Slice 0 Scaler */

    VPSHAL_VIP_TOP_S1_PARSER,
    /**< Slice 1 Parser */

    VPSHAL_VIP_TOP_S1_CHRDS0,
    /**< Slice 1 Chroma down-sample instance 0 */

    VPSHAL_VIP_TOP_S1_CHRDS1,
    /**< Slice 1 Chroma down-sample instance 1 */

    VPSHAL_VIP_TOP_S1_CSC,
    /**< Slice 1 Color space converter */

    VPSHAL_VIP_TOP_S1_SC,
    /**< Slice 1 Scaler */

    VPSHAL_VIP_TOP_NUM_MODULES
    /**< Total sub-modules in VIP */
} VpsHal_VipTopModule;

/**
 *  enum VpsHal_VipTopMux
 *  \brief Enum for selecting different muxes within VIP
 *  Used in setMux APIs.
 *  Value for each enum is important since it is used directly in HAL
 */
typedef enum
{
    VPSHAL_VIP_TOP_CSC_SRC = 1,
    /**< Mux to select Color space converter source */

    VPSHAL_VIP_TOP_SC_SRC = 2,
    /**< Mux to select Scaler source */

    VPSHAL_VIP_TOP_RGB_SRC = 3,
    /**< Mux to select RGB source */

    VPSHAL_VIP_TOP_RGB_OUT_LO = 4,
    /**< Mux to select RGB LO output type */

    VPSHAL_VIP_TOP_RGB_OUT_HI = 5,
    /**< Mux to select RGB HI output type */

    VPSHAL_VIP_TOP_CHRDS0_SRC = 6,
    /**< Mux to select Chroma down-sample instance 0 source */

    VPSHAL_VIP_TOP_CHRDS1_SRC = 7,
    /**< Mux to select Chroma down-sample instance 1 source */

    VPSHAL_VIP_TOP_MULTI_CH = 8,
    /**< Mux to select Multi-channel or 24bit output mode */

    VPSHAL_VIP_TOP_CHRDS0_BYPASS = 9,
    /**< Mux to control Chroma down-sample instance 0 bypass */

    VPSHAL_VIP_TOP_CHRDS1_BYPASS = 10,
    /**< Mux to control Chroma down-sample instance 1 bypass */

    VPSHAL_VIP_TOP_TESTPORT_A = 11,
    /**< Mux to enable test-port for PORT A */

    VPSHAL_VIP_TOP_TESTPORT_B = 12,
    /**< Mux to enable test-port for PORT B */

    VPSHAL_VIP_TOP_RGB_OUT = 13,
    /**< Mux to enable VPSHAL_VIP_TOP_RGB_OUT_HI and VPSHAL_VIP_TOP_RGB_SRC
     * in same function
     */

    VPSHAL_VIP_TOP_UV_UP = 14,
    /**< Mux to enable VPSHAL_VIP_TOP_RGB_OUT_HI, VPSHAL_VIP_TOP_CHRDS1_BYPASS
     * and VPSHAL_VIP_TOP_CHRDS0_BYPASS in same function
     */

    VPSHAL_VIP_TOP_UV_LO = 15,
    /**< Mux to enable VPSHAL_VIP_TOP_RGB_OUT_LO and VPSHAL_VIP_TOP_MULTI_CH
     * in same function
     */
    VPSHAL_VIP_TOP_NUM_MUXES = 16
                               /**< Number of Muxes in one VIP Slice */
} VpsHal_VipTopMux;

/**
 *  enum VpsHal_VipTopMuxVal
 *  \brief Enum for selecting mux input/output within VIP
 *  Used in setMux APIs.
 *  Value for each enum is important since it is used directly in HAL
 */
typedef enum
{
    VPSHAL_VIP_TOP_CSC_MUX_SRC_DISABLED = 0,
    /**< For VPSHAL_VIP_TOP_CSC_SRC: Path Disabled */

    VPSHAL_VIP_TOP_CSC_MUX_SRC_VIP_PORTA_422 = 1,
    /**< For VPSHAL_VIP_TOP_CSC_SRC: Source from VIP_PORT A (422/16b) port */

    VPSHAL_VIP_TOP_CSC_MUX_SRC_VIP_PORTB_422 = 2,
    /**< For VPSHAL_VIP_TOP_CSC_SRC: Source from VIP_PORT B port */

    VPSHAL_VIP_TOP_CSC_MUX_SRC_SEC = 3,
    /**< For VPSHAL_VIP_TOP_CSC_SRC: Source from Secondary (422/16b) */

    VPSHAL_VIP_TOP_CSC_MUX_SRC_VIP_PORTA_24B = 4,
    /**< For VPSHAL_VIP_TOP_CSC_SRC: Source from VIP_PORT A (RGB/24b) port */

    VPSHAL_VIP_TOP_CSC_MUX_SRC_COMP = 5,
    /**< For VPSHAL_VIP_TOP_CSC_SRC: Source from Compositor (RGB) */

    VPSHAL_VIP_TOP_SC_MUX_SRC_DISABLED = 0,
    /**< For VPSHAL_VIP_TOP_SC_SRC: Path Disabled */

    VPSHAL_VIP_TOP_SC_MUX_SRC_CSC = 1,
    /**< For VPSHAL_VIP_TOP_SC_SRC: Source from Color Space Converter (CSC) */

    VPSHAL_VIP_TOP_SC_MUX_SRC_VIP_PORTA = 2,
    /**< For VPSHAL_VIP_TOP_SC_SRC: Source from VIP_PORT A port */

    VPSHAL_VIP_TOP_SC_MUX_SRC_VIP_PORTB = 3,
    /**< For VPSHAL_VIP_TOP_SC_SRC: Source from VIP_PORT B port */

    VPSHAL_VIP_TOP_SC_MUX_SRC_VIP_SEC = 4,
    /**< For VPSHAL_VIP_TOP_SC_SRC: Source from Secondary (422) */

    VPSHAL_VIP_TOP_RGB_MUX_SRC_COMP = 0,
    /**< For VPSHAL_VIP_TOP_RGB_SRC: Source from Compositor RGB input */

    VPSHAL_VIP_TOP_RGB_MUX_SRC_CSC = 1,
    /**< For VPSHAL_VIP_TOP_RGB_SRC: Source from CSC */

    VPSHAL_VIP_TOP_RGB_OUT_YUV = 0,
    /**< For VPSHAL_VIP_TOP_RGB_OUT_LO and VPSHAL_VIP_TOP_RGB_OUT_HI
     * Output is YUV
     */

    VPSHAL_VIP_TOP_RGB_OUT_RGB = 1,
    /**< For VPSHAL_VIP_TOP_RGB_OUT_LO and VPSHAL_VIP_TOP_RGB_OUT_HI
     * Output is RGB
     */

    VPSHAL_VIP_TOP_CHRDS_MUX_SRC_DISABLED = 0,
    /**< For VPSHAL_VIP_TOP_CHRDS0_SRC and VPSHAL_VIP_TOP_CHRDS1_SRC:
     * Path Disabled
     */

    VPSHAL_VIP_TOP_CHRDS_MUX_SRC_SC = 1,
    /**< For VPSHAL_VIP_TOP_CHRDS0_SRC and VPSHAL_VIP_TOP_CHRDS1_SRC:
     * Source from Scaler (SC_M)
     */

    VPSHAL_VIP_TOP_CHRDS_MUX_SRC_CSC = 2,
    /**< For VPSHAL_VIP_TOP_CHRDS0_SRC and VPSHAL_VIP_TOP_CHRDS1_SRC:
     * Source from Color Space Converter (CSC)
     */

    VPSHAL_VIP_TOP_CHRDS_MUX_SRC_VIP_PORTA = 3,
    /**< For VPSHAL_VIP_TOP_CHRDS0_SRC and VPSHAL_VIP_TOP_CHRDS1_SRC:
     * Source from VIP_PORT A port
     */

    VPSHAL_VIP_TOP_CHRDS_MUX_SRC_VIP_PORTB = 4,
    /**< For VPSHAL_VIP_TOP_CHRDS0_SRC and VPSHAL_VIP_TOP_CHRDS1_SRC:
     * Source from VIP_PORT B port
     */

    VPSHAL_VIP_TOP_CHRDS_MUX_SRC_SEC = 5,
    /**< For VPSHAL_VIP_TOP_CHRDS0_SRC and VPSHAL_VIP_TOP_CHRDS1_SRC:
     * Source from Secondary (422)
     */

    VPSHAL_VIP_TOP_MULT_CHANNEL_SELECT_SINGLE_CH = 0,
    /**< For VPSHAL_VIP_TOP_MULTI_CH: Single channel 16b mode */

    VPSHAL_VIP_TOP_MULT_CHANNEL_SELECT_MULTI_CHANNEL_OR_RGB = 1,
    /**< For VPSHAL_VIP_TOP_MULTI_CH:
     * multi chan 16b or single chan 24b RGB mode
     */

    VPSHAL_VIP_TOP_CHRDS_BYPASS_ON = 1,
    /**< For VPSHAL_VIP_TOP_CHRDS0_BYPASS and VPSHAL_VIP_TOP_CHRDS1_BYPASS:
     * Bypass Chroma down sampler
     */

    VPSHAL_VIP_TOP_CHRDS_BYPASS_OFF = 0,
    /**< For VPSHAL_VIP_TOP_CHRDS0_BYPASS and VPSHAL_VIP_TOP_CHRDS1_BYPASS:
     * Enable Chroma down sampler
     */

    VPSHAL_VIP_TOP_CHRDS_TESTPORT_ON = 1,
    /**< For VPSHAL_VIP_TOP_TESTPORT_A and VPSHAL_VIP_TOP_TESTPORT_B:
     * Enable test-port
     */

    VPSHAL_VIP_TOP_CHRDS_TESTPORT_OFF = 0
                                        /**< For VPSHAL_VIP_TOP_TESTPORT_A
                                         * and VPSHAL_VIP_TOP_TESTPORT_B:
                                         * Disable test-port
                                         */
} VpsHal_VipTopMuxVal;

/* ========================================================================= */
/*                         Structure Declarations                            */
/* ========================================================================= */
/**
 *  struct VpsHal_VipTopOpenParams
 *  \brief Structure to identify a VIP TOP HAL instance
 */
typedef struct
{
    UInt32 halId;
    /**< Vip Instance ID: #Vps_VipInst */
} VpsHal_VipTopOpenParams;

/**
 *  struct VpsHal_VipTopInstParams
 *  \brief Structure containg parameters to initialize VIP TOP HAL instance
 *         Primarily baseAddress.
 */
typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance. For valid values see #Vps_VipInst. */
    UInt32 baseAddr;
    /**< Base address of VIP TOP for current instance. */
} VpsHal_VipTopInstParams;

/* ========================================================================== */
/*                        Public Function Declarations                        */
/* ========================================================================== */
/**
 *  VpsHal_vipTopInit
 *  \brief VIP TOP HAL init function.
 *  This function should be called before calling any of VIP TOP HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param instPrms           Pointer to #VpsHal_VipSliceParserInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vipTopInit(UInt32                         numInst,
                        const VpsHal_VipTopInstParams *instPrms,
                        Ptr                            arg);

/**
 *  VpsHal_vipTopDeInit
 *  \brief VIP TOP HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vipTopDeInit(Ptr arg);

/**
 *  VpsHal_vipTopOpen
 *  \brief Returns the handle to the requested Vip instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the VIP HAL
 *  configuration APIs.
 *
 *  VpsHal_vipInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openParams        #VpsHal_VipTopOpenParams
 *
 *  \return              success     VIP instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vipTopOpen(const VpsHal_VipTopOpenParams *openParams);

/**
 *  VpsHal_vipClose
 *  \brief Closes specified instance of Vip Top HAL
 *  VpsHal_vipInit and Vip_open should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_vipTopOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopClose(VpsHal_Handle handle);

/**
 *  VpsHal_vipTopEnableAllModules
 *  \brief Enable/Disable all sub modules within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param enable         1: Enable all modules.
 *                        0: Disable all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopEnableAllModules(VpsHal_Handle handle,
                                    UInt32 enable, Ptr configOvlyPtr);

/**
 *  VpsHal_vipTopResetAllModules
 *  \brief Reset/Unreset all sub modules within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param enable         1: Reset all modules.
 *                        0: Release reset for all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopResetAllModules(VpsHal_Handle handle,
                                   UInt32 enable, Ptr configOvlyPtr);

/**
 *  VpsHal_vipTopEnableModule
 *  \brief Enable/Disable specified module within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param module         Module to reset/unreset.
 *  \param enable         1: Enable module
 *                        0: Disable module
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopEnableModule(VpsHal_Handle handle,
                                UInt32 module, UInt32 enable,
                                Ptr configOvlyPtr);

/**
 *  VpsHal_vipTopResetModule
 *  \brief Reset/Unreset specified module within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param module         Module to reset/unreset. #VpsHal_VipTopModule
 *  \param enable         1: Reset module
 *                        0: Release module reset
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopResetModule(VpsHal_Handle handle,
                               UInt32 module, UInt32 enable,
                               Ptr configOvlyPtr);

/**
 *  VpsHal_vipTopDisableAllMux
 *  \brief Disable all muxes within given VIP slice
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param slice          VIP Slice to control #Vps_VipSliceInst
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopDisableAllMux(VpsHal_Handle handle,
                                 UInt32 slice, Ptr configOvlyPtr);

/**
 *  VpsHal_vipTopSetMux
 *  \brief Set specified mux within given VIP slice
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param slice          VIP Slice to control #Vps_VipSliceInst
 *  \param mux            VIP Mux to control #VpsHal_VipTopMux
 *  \param muxVal         Mux value to set #VpsHal_VipTopMuxVal
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopSetMux(VpsHal_Handle handle,
                          UInt32 slice, UInt32 mux, UInt32 muxVal,
                          Ptr configOvlyPtr);

/**
 *  VpsHal_vipTopEnableVpdmaListCompleteInterrupt
 *  \brief Enable/Disable interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopEnableVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable);

/**
 *  VpsHal_vipTopClearVpdmaListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopClearVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum);

/**
 *  VpsHal_vipTopEnableVpdmaListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopEnableVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable);

/**
 *  VpsHal_vipTopClearVpdmaListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopClearVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum);

/**
 *  VpsHal_vipTopGetInstInfo
 *  \brief Get VIP Handle from VIP Instance ID.
 *  Caller should ensure VIP TOP HAL init is complete.
 *
 *  \param vipTopId         Valid vipTopId of type #Vps_VipInst
 *
 *  \return                 Valid VIP TOP Instance handle.
 *
 */
VpsHal_Handle VpsHal_vipTopGetInstInfo(UInt32 vipTopId);

/**
 *  VpsHal_vipTopGetInstInfo
 *  \brief Get VIP Handle from VIP Instance ID.
 *  Caller should ensure VIP TOP HAL init is complete.
 *
 *  \param vipTopId         Valid vipTopId of type #Vps_VipInst
 *
 *  \return                 Valid VIP TOP Instance handle.
 *
 */
UInt32 VpsHal_vipTopGetBaseAddress(VpsHal_Handle handle);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSHAL_VIPTOP_H_ */
