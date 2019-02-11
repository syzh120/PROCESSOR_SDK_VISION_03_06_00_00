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
 *  \file vpshal_dei.h
 *
 *  \brief HAL layer for the VPS Deinterlacer.
 *  This file exposes the HAL APIs of the VPS Deinterlacer.
 *  This HAL is meant to be used by other VPS driver. The application don't
 *  have to access this HAL module.
 *
 */

#ifndef VPSHAL_DEI_H_
#define VPSHAL_DEI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum VpsHal_DeiInst
 *  \brief Enum to define the various DEI instance.
 */
typedef enum
{
    VPSHAL_VPE1_DEI = 0,
    /**< VPE DEI instance. */
    VPSHAL_DEI_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_DeiInstId;

/**
 *  \brief DEI maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define VPSHAL_DEI_MAX_INST             (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DeiInstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance. For valid values see #VpsHal_DeiInstId. */
    UInt32 baseAddr;
    /**< Base address for the current instance. */
} VpsHal_DeiInstParams;

/**
 *  struct VpsHal_DeiOpenParams
 *  \brief Structure to identify a DEI HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< DEI Instance ID. For valid values see #VpsHal_DeiInstId. */
} VpsHal_DeiOpenParams;

/**
 *  struct VpsHal_DeiMdtConfig
 *  \brief Configuration parameters of MDT sub-module.
 */
typedef struct
{
    UInt32 spatMaxBypass;
    /**< Bypass spatial maximum filtering. */
    UInt32 tempMaxBypass;
    /**< Bypass temporal maximum filtering. */
} VpsHal_DeiMdtConfig;

/**
 *  struct VpsHal_DeiEdiConfig
 *  \brief Configuration parameters of EDI sub-module.
 */
typedef struct
{
    UInt32 inpMode;
    /**< Interpolation mode. For valid values see #Vps_DeiEdiMode. */
    UInt32 tempInpEnable;
    /**< 3D processing (temporal interpolation). */
    UInt32 tempInpChromaEnable;
    /**< 3D processing for chroma. */
} VpsHal_DeiEdiConfig;

/**
 *  struct VpsHal_DeiFmdConfig
 *  \brief Configuration parameters of FMD sub-module.
 */
typedef struct
{
    UInt32 filmMode;
    /**< Film Mode. */
    UInt32 bed;
    /**< Bad Edit Detection. */
    UInt32 window;
    /**< FMD operation window. */
    UInt32 lock;
    /**< Lock Deinterlacer to film mode. */
    UInt32 jamDir;
    /**< Field jamming direction. For valid values see #Vps_DeiFmdJamDir. */
    UInt16 windowMinx;
    /**< Left boundary of FMD window. */
    UInt16 windowMiny;
    /**< Top boundary of FMD window. */
    UInt16 windowMaxx;
    /**< Right boundary of FMD window. */
    UInt16 windowMaxy;
    /**< Bottom boundary of FMD window. */
} VpsHal_DeiFmdConfig;

/**
 *  struct VpsHal_DeiConfig
 *  \brief Configuration parameters of this module along with parameters
 *  of all other sub-modules.
 */
typedef struct
{
    UInt16              width;
    /**< Picture width at output. */
    UInt16              height;
    /**< Picture height. It should be field size for the interlaced
     *   input and frame size for the progressive input. */
    UInt32              scanFormat;
    /**< Interlaced or Progressive video.
     *   For valid values see #Fvid2_ScanFormat. */
    UInt32              bypass;
    /**< Bypassing Deinterlacer. */
    UInt32              fieldFlush;
    /**< Flush internal pipe for current output. */
    VpsHal_DeiMdtConfig mdt;
    /**< MDT configuration structure. */
    VpsHal_DeiEdiConfig edi;
    /**< EDI configuration structure. */
    VpsHal_DeiFmdConfig fmd;
    /**< FMD configuration structure. */
} VpsHal_DeiConfig;

/**
 *  struct VpsHal_DeiFmdStatus
 *  \brief FMD status information to be used by FMD ISR.
 */
typedef struct
{
    UInt32 frameDiff;
    /**< Frame diff between 2 top/bottom field. */
    UInt32 fldDiff;
    /**< Field diff between 2 neighboring field. */
    UInt32 caf;
    /**< Detected combing artifacts. */
    UInt32 reset;
    /**< Reset status. */
} VpsHal_DeiFmdStatus;

/**
 *  struct VpsHal_DeiFmdUpdateConfig
 *  \brief FMD configuration to be updated by FMD ISR.
 */
typedef struct
{
    UInt32 lock;
    /**< Film lock indicator. */
    UInt32 jamDir;
    /**< Field jamming direction. For valid values see #Vps_DeiFmdJamDir. */
} VpsHal_DeiFmdUpdateConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsHal_deiInit
 *  \brief DEI HAL init function.
 *
 *  Initializes DEI objects, gets the register overlay offsets for DEI
 *  registers.
 *  This function should be called before calling any of DEI HAL API's.
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
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiInit(UInt32                      numInst,
                     const VpsHal_DeiInstParams *instPrms,
                     Ptr                         arg);

/**
 *  VpsHal_deiDeInit
 *  \brief DEI HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiDeInit(Ptr arg);

/**
 *  VpsHal_deiOpen
 *  \brief Returns the handle to the requested DEI instance.
 *
 *  This function should be called prior to calling any of the DEI HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms         VpsHal_DeiOpenParams *
 *
 *  \return                 Returns DEI instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_deiOpen(const VpsHal_DeiOpenParams *openPrms);

/**
 *  VpsHal_deiClose
 *  \brief Closes the DEI HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_deiOpen function
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiClose(VpsHal_Handle handle);

/**
 *  VpsHal_deiGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA register configuration
 *  overlay required to program the DEI registers using VPDMA config
 *  descriptors.
 *
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the DEI registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context
 *  (multiple instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay
 *  one-time and submit this to VPDMA everytime when context changes.
 *  Thus saving valuable CPU in programming the VPS registers.
 *
 *  \param handle           Instance handle
 *  \return                 Returns the size of config overlay memory
 */
UInt32 VpsHal_deiGetConfigOvlySize(VpsHal_Handle handle);

/**
 *  VpsHal_deiCreateConfigOvly
 *  \brief Creates the DEI register configuration overlay using VPDMA
 *  helper function.
 *
 *  This function does not initialize the overlay with DEI configuration.
 *  It is the responsibility of the client driver to configure the overlay
 *  by calling VpsHal_deiSetConfig function before submitting the same
 *  to VPDMA for register configuration at runtime.
 *
 *  \param handle           Instance handle
 *  \param configOvlyPtr    Pointer to the overlay memory where the
 *                          overlay is formed. The memory for the overlay
 *                          should be allocated by client driver.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr);

/**
 *  VpsHal_deiSetConfig
 *  \brief Sets the entire DEI configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiSetConfig(VpsHal_Handle           handle,
                          const VpsHal_DeiConfig *config,
                          Ptr                     configOvlyPtr);

/**
 *  VpsHal_deiSetMdtConfig
 *  \brief Sets the entire DEI MDT configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI MDT registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiMdtConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiSetMdtConfig(VpsHal_Handle              handle,
                             const VpsHal_DeiMdtConfig *config,
                             Ptr                        configOvlyPtr);

/**
 *  VpsHal_deiSetEdiConfig
 *  \brief Sets the entire DEI EDI configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI EDI registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiEdiConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiSetEdiConfig(VpsHal_Handle              handle,
                             const VpsHal_DeiEdiConfig *config,
                             Ptr                        configOvlyPtr);

/**
 *  VpsHal_deiSetFmdConfig
 *  \brief Sets the entire DEI FMD configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI FMD registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiFmdConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *  \param width            Picture width at output.
 *  \param height           Picture height at output.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiSetFmdConfig(VpsHal_Handle              handle,
                             const VpsHal_DeiFmdConfig *config,
                             Ptr                        configOvlyPtr,
                             UInt32                     width,
                             UInt32                     height);

/**
 *  VpsHal_deiGetConfig
 *  \brief Gets the entire DEI configuration from the actual DEI registers.
 *
 *  This function gets the entire DEI configuration. This function
 *  gets the configuration of all the sub-modules in DEI using other
 *  get configuration function calls.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiGetConfig(VpsHal_Handle handle, VpsHal_DeiConfig *config);

/**
 *  VpsHal_deiGetMdtConfig
 *  \brief Gets DEI MDT configuration from the actual DEI registers.
 *
 *  This function gets the DEI configuration specific to MDT module.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiMdtConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiGetMdtConfig(VpsHal_Handle        handle,
                             VpsHal_DeiMdtConfig *config);

/**
 *  VpsHal_deiGetEdiConfig
 *  \brief Gets DEI EDI configuration from the actual DEI registers.
 *
 *  This function gets the DEI configuration specific to EDI module.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiEdiConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiGetEdiConfig(VpsHal_Handle        handle,
                             VpsHal_DeiEdiConfig *config);

/**
 *  VpsHal_deiGetFmdConfig
 *  \brief Gets DEI FMD configuration from the actual DEI registers.
 *
 *  This function gets the DEI configuration specific to FMD module.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiFmdConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiGetFmdConfig(VpsHal_Handle        handle,
                             VpsHal_DeiFmdConfig *config);

/**
 *  VpsHal_deiGetFmdStatus
 *  \brief Returns DEI FMD status information that is needed by the FMD
 *  software (ISR context) at each frame ready interrupt.
 *
 *  \param handle           Instance h andle
 *  \param status           Pointer to VpsHal_DeiFmdStatus structure
 *                          containing the register status.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiGetFmdStatus(VpsHal_Handle        handle,
                             VpsHal_DeiFmdStatus *status);

/**
 *  VpsHal_deiUpdateFmdConfig
 *  \brief Updates DEI FMD configuration that needs to be updated by the
 *  FMD software (ISR context) at each frame ready interrupt.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiFmdUpdateConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEIH registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *                          Currently writing to overlay memory is not supported
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_deiUpdateFmdConfig(VpsHal_Handle                    handle,
                                const VpsHal_DeiFmdUpdateConfig *config,
                                Ptr                              configOvlyPtr);

/**
 *  VpsHal_deiSetAdvConfig
 *  \brief This function is used to set the advanced DEI parameters.
 *  This function should be called by core supporting advanced read
 *  and write ioctl. It does not set all the parameters.
 *
 *  \param handle           Instance handle
 *  \param advCfg           Pointers to structure containing DEI advance
 *                          parameters
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEIH registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *                          Currently writing to overlay memory is not supported
 *
 *  \return                 Returns 0 on success else returns error value.
 */
Int32 VpsHal_deiSetAdvConfig(VpsHal_Handle            handle,
                             const Vps_DeiRdWrAdvCfg *advCfg,
                             Ptr                      configOvlyPtr);

/**
 *  VpsHal_deiGetAdvConfig
 *  \brief This function is used to get the advanced DEI parameters.
 *  This function should be called by core supporting advanced read
 *  and write ioctl. It does not read all the parameters.
 *
 *  \param handle           Instance handle
 *  \param advCfg           Pointers to structure containing DEI advance
 *                          parameters
 *
 *  \return                 Returns 0 on success else returns error value.
 */
Int32 VpsHal_deiGetAdvConfig(VpsHal_Handle      handle,
                             Vps_DeiRdWrAdvCfg *advCfg);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_DEI_H_ */
