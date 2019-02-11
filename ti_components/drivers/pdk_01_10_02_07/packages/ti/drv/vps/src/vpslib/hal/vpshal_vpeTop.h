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
 *  \file vpshal_vpeTop.h
 *
 *  \brief HAL Header file for VPE-TOP
 *  This file exposes the HAL APIs of the VPE Clock and Reset control
 *  modules, Interrupts and Muxes
 *
 */

#ifndef VPSHAL_VPETOP_H_
#define VPSHAL_VPETOP_H_

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
#define VPSHAL_VPE_TOP_MAX_INST  (VPSHAL_NUM_VPE_INST)

/**
 *  enum VpsHal_VpeTopModule
 *  \brief Enum for selecting different modules within VPE
 *  Used in enabling/disabling/reset/unreset APIs
 */
typedef enum
{
    VPSHAL_VPE_PRIM_DP = 0U,
    /**< Primary Data path */
    VPSHAL_VPE_TOP_VPDMA = 1U,
    /**< VPDMA */
    VPSHAL_VPE_TOP_NUM_MODULES = 2U,
    /**< Total sub-modules in VPE */
    VPSHAL_VPE_TOP_FORCE_INT = 0x7FFFFFFFU
                               /**< This will ensure enum is not packed, will always be contained in int */
} VpsHal_VpeTopModule;

/**
 *  enum VpsHal_VpeTopMux
 *  \brief Enum for selecting different muxes within VPE
 *  Used in setMux APIs.
 */
typedef enum
{
    VPSHAL_VPE_TOP_CSC_SRC = 0U,
    /**< Mux to select Color space converter source */
    VPSHAL_VPE_TOP_RGB_OUT = 1U,
    /**< Mux to select RGB_OUT output type */
    VPSHAL_VPE_TOP_CHRDS0_SRC = 2U,
    /**< Mux to select Chroma down-sample instance 0 source */
    VPSHAL_VPE_TOP_CHRDS0_BYPASS = 3U,
    /**< Mux to control Chroma down-sample instance 0 bypass */
    VPSHAL_VPE_TOP_422SP_EN = 4U,
    /**< Mux to enable 422 semiplanar output */
    VPSHAL_VPE_TOP_NUM_MUXES = 5U,
    /**< Number of Muxes in VPE */
    VPSHAL_VPE_TOP_MUX_FORCE_INT = 0x7FFFFFFFU
                                   /**< This will ensure enum is not packed, will always be contained in int */
} VpsHal_VpeTopMux;

/**
 *  enum VpsHal_VpeTopMuxVal
 *  \brief Enum for selecting mux input/output within VPE
 *  Used in setMux APIs.
 *  Value for each enum is important since it is used directly in HAL
 */
typedef enum
{
    VPSHAL_VPE_TOP_CSC_MUX_SRC_DISABLED = 0,
    /**< For VPSHAL_VPE_TOP_CSC_SRC: Path Disabled */
    VPSHAL_VPE_TOP_CSC_MUX_SRC_DEI_SC = 3,
    /**< For VPSHAL_VPE_TOP_CSC_SRC: Source from DEI+SC path */
    VPSHAL_VPE_TOP_RGB_OUT_YUV = 0,
    /**< For VPSHAL_VPE_TOP_RGB_OUT: Output is YUV */
    VPSHAL_VPE_TOP_RGB_OUT_RGB = 1,
    /**< For VPSHAL_VPE_TOP_RGB_OUT: Output is RGB or YUV444 */
    VPSHAL_VPE_TOP_CHRDS0_MUX_SRC_DISABLED = 0,
    /**< For VPSHAL_VPE_TOP_CHRDS0_SRC: Path Disabled */
    VPSHAL_VPE_TOP_CHRDS0_MUX_SRC_DEI_SC = 5,
    /**< For VPSHAL_VPE_TOP_CHRDS0_SRC:
     *Source from DEI+SC path */
    VPSHAL_VPE_TOP_MUX_SRC_FORCE_INT = 0x7FFFFFFF
                                       /**< This will ensure enum is not packed, will always be contained in int */
} VpsHal_VpeTopMuxVal;

/* ========================================================================= */
/*                         Structure Declarations                            */
/* ========================================================================= */
/**
 *  struct VpsHal_VpeTopOpenParams
 *  \brief Structure to identify a VPE TOP HAL instance
 */
typedef struct
{
    UInt32 halId;
    /**< Vpe Instance ID: #Vps_VpeInst */
} VpsHal_VpeTopOpenParams;

/**
 *  struct VpsHal_VpeTopInstParams
 *  \brief Structure containg parameters to initialize VPE TOP HAL instance
 *         Primarily baseAddress.
 */
typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance. For valid values see #Vps_VpeInst. */
    UInt32 baseAddr;
    /**< Base address of VPE TOP for current instance. */
} VpsHal_VpeTopInstParams;

/**
 *  struct VpsHal_VpeTopConfig
 *  \brief Configuration parameters for VPE top.
 */
typedef struct
{
    Fvid2_DataFormat dataFmt;
    /**< Output data format of VPE required to program the muxes. */
} VpsHal_VpeTopConfig;

/* ========================================================================== */
/*                        Public Function Declarations                        */
/* ========================================================================== */
/**
 *  VpsHal_vpeTopInit
 *  \brief VPE TOP HAL init function.
 *  This function should be called before calling any of VPE TOP HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param instPrms           Pointer to #VpsHal_VpeTopInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vpeTopInit(UInt32                         numInst,
                        const VpsHal_VpeTopInstParams *instPrms,
                        Ptr                            arg);

/**
 *  VpsHal_vpeTopDeInit
 *  \brief VPE TOP HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vpeTopDeInit(Ptr arg);

/**
 *  VpsHal_vpeTopOpen
 *  \brief Returns the handle to the requested VPE instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the VPE HAL
 *  configuration APIs.
 *
 *  VpsHal_vpeInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openParams        #VpsHal_VpeTopOpenParams
 *
 *  \return              success     VPE instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vpeTopOpen(const VpsHal_VpeTopOpenParams *openParams);

/**
 *  VpsHal_vpeClose
 *  \brief Closes specified instance of VPE Top HAL
 *  VpsHal_vpeInit and vpe_open should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopClose(VpsHal_Handle handle);

/**
 *  VpsHal_vpeTopGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA
 *  register configuration overlay required to program the VPE TOP mux
 *  register using VPDMA config descriptors.
 *
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the vpeTop registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context (multiple
 *  instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay one-time
 *  and submit this to VPDMA everytime when context changes. Thus saving
 *  valuable CPU in programming the VPS registers.
 *  VpsHal_vpeTopInit and VpsHal_vpeTopOpen should be called prior to this.
 *
 *  \param handle Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \return       Returns 0 on success else returns error value.
 */
UInt32 VpsHal_vpeTopGetConfigOvlySize(VpsHal_Handle handle);

/**
 *  VpsHal_vpeTopCreateConfigOvly
 *  \brief Creates the VPE top register configuration
 *  overlay using VPDMA helper function.
 *
 *  This function does not initialize the overlay with VPE Top mux
 *  configuration. It is the responsibility of the client driver to configure
 *  the overlay by calling VpsHal_vpeTopSetConfig function before submitting
 *  the same to VPDMA for register configuration at runtime.
 *  VpsHal_vpeTopInit and VpsHal_vpeTopOpen should be called prior to this.
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \param configOvlyPtr  Pointer to the overlay memory where the overlay is
 *                        formed. The memory for the overlay should be allocated
 *                        by client driver. This parameter should be non-NULL.
 *
 *  \return               Returns 0 on success else returns error value.
 */
Int32 VpsHal_vpeTopCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopSetConfig
 *  \brief Sets the VPE top configuration to either the
 *  actual mux registers or to the configuration overlay memory.
 *
 *  This function configures the VPE top registers. Depending on the value
 *  of configOvlyPtr parameter, the updating will happen to actual MMR or
 *  to configuration overlay memory.
 *  VpsHal_vpeTopInit and VpsHal_vpeTopOpen should be called prior to this.
 *  VPE top mux registers or configuration overlay memory are programmed
 *  according to the parameters passed.
 *
 *  \param handle          Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \param config          Pointer to Vps_vpeTopConfig structure containing the
 *                         register configurations. This parameter should be
 *                         non-NULL.
 *
 *  \param configOvlyPtr   Pointer to the configuration overlay memory.
 *                         If this parameter is NULL, then the configuration is
 *                         written to the actual registers. Otherwise the
 *                         configuration is updated in the memory pointed
 *                         by the same at proper virtual offsets. This parameter
 *                         can be NULL depending on the intended usage.
 *
 *  \return                Returns 0 on success else returns error value.
 */
Int32 VpsHal_vpeTopSetConfig(VpsHal_Handle              handle,
                             const VpsHal_VpeTopConfig *config,
                             Ptr                        configOvlyPtr);

/**
 *  VpsHal_vpeTopEnableAllModules
 *  \brief Enable/Disable all sub modules within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param enable         1: Enable all modules.
 *                        0: Disable all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopEnableAllModules(VpsHal_Handle handle,
                                    UInt32 enable, Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopResetAllModules
 *  \brief Reset/Unreset all sub modules within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param enable         1: Reset all modules.
 *                        0: Release reset for all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopResetAllModules(VpsHal_Handle handle,
                                   UInt32 enable, Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopEnableModule
 *  \brief Enable/Disable specified module within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param module         Module to reset/unreset.
 *  \param enable         1: Enable module
 *                        0: Disable module
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopEnableModule(VpsHal_Handle handle,
                                UInt32 module, UInt32 enable,
                                Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopResetModule
 *  \brief Reset/Unreset specified module within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param module         Module to reset/unreset. #VpsHal_VpeTopModule
 *  \param enable         1: Reset module
 *                        0: Release module reset
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopResetModule(VpsHal_Handle handle,
                               UInt32 module, UInt32 enable,
                               Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopDisableAllMux
 *  \brief Disable all muxes within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopDisableAllMux(VpsHal_Handle handle, Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopSetMux
 *  \brief Set specified mux within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param mux            VPE Mux to control #VpsHal_VpeTopMux
 *  \param muxVal         Mux value to set #VpsHal_VpeTopMuxVal
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopSetMux(VpsHal_Handle handle,
                          UInt32 mux, UInt32 muxVal, Ptr configOvlyPtr);

/**
 *  VpsHal_vpeTopEnableVpdmaListCompleteInterrupt
 *  \brief Enable/Disable interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopEnableVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable);

/**
 *  VpsHal_vpeTopClearVpdmaListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopClearVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum);

/**
 *  VpsHal_vpeTopEnableVpdmaListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopEnableVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable);

/**
 *  VpsHal_vpeTopClearVpdmaListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopClearVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum);

/**
 *  VpsHal_vpeTopGetInstInfo
 *  \brief Get VPE Handle from VPE Instance ID.
 *  Caller should ensure VPE TOP HAL init is complete.
 *
 *  \param vpeTopId         Valid vpeTopId of type #Vps_VpeInst
 *
 *  \return                 Valid VPE TOP Instance handle.
 *
 */
VpsHal_Handle VpsHal_vpeTopGetInstInfo(UInt32 vpeTopId);

/**
 *  VpsHal_vpeTopGetInstInfo
 *  \brief Get VPE Handle from VPE Instance ID.
 *  Caller should ensure VPE TOP HAL init is complete.
 *
 *  \param vpeTopId         Valid vpeTopId of type #Vps_VpeInst
 *
 *  \return                 Valid VPE TOP Instance handle.
 *
 */
UInt32 VpsHal_vpeTopGetBaseAddress(VpsHal_Handle handle);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSHAL_VPETOP_H_ */
