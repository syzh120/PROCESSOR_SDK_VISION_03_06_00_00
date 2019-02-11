/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpshal_issldc.h
 *
 *  \brief HAL Header file for LDC
 *      This file defines the HAL APIs for ISS LDC module
 *
 */

#ifndef VPSHAL_ISS_LDC_H_
#define VPSHAL_ISS_LDC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief LDC maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_LDC_MAX_INST             (1U)

/**
 *  enum isshalldcInstId
 *  \brief Enum to define the various VTNF instance.
 */
typedef enum isshalldcInstId
{
    ISSHAL_LDC_INST_0 = 0,
    /**< LDC Instance Id 0. */
    ISSHAL_LDC_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_LDC_INST_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed, will
                                 *always be contained in int */
} isshalldcInstId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

#if 0
/**
 *  struct isshalldcSmartCodecStatsCfg
 *  \brief All configuration Parameters for LDC.
 */
typedef struct isshalldcSmartCodecStatsCfg
{
    uint32_t enable;
    /**< Enables Smart Codec Statistics */

    uint32_t sliceSize;
    /**< The number of output lines computed by LDC before the computed
     *   macroblock row statistics are transferred to system memory.
     *   This must be a multiple of 16.
     *   The maximum possible value is  8176. */
    uint32_t numRegions;
    /**< The number of regions in both directions for the region
     *   based statistics.
     *   The possible values are,
     *      0: 1x1
     *      1: 2x2
     *      2: 3x3
     *      3: 4x4 */
    uint32_t accShift;
    /**< The output divider for sum of pixels in a region and
     *   sum of squares of pixels in a region.
     *   This parameter right shifts the final accumulator prior to writing
     *   the output statistics. */
} isshalldcSmartCodecStatsCfg_t;
#endif

/**
 *  struct isshalldcInstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalldcInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalldcInstId. */
    uint32_t baseAddress;
    /**< Register base address */
} isshalldcInstParams_t;

/**
 *  struct isshalvldcOpenParams
 *  \brief Structure to identify a LDC HAL instance.
 */
typedef struct isshalldcOpenParams
{
    uint32_t instId;
    /**< Instance ID. For valid values see #isshalldcInstId. */
} isshalldcOpenParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issldcInit
 *  \brief LDC init function.
 *
 *  Initializes LDC objects.
 *  This function should be called before calling any of LDC HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalldcInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issldcInit(UInt32                       numInst,
                          const isshalldcInstParams_t *instPrms,
                          Ptr                          arg);

/**
 *  VpsHal_issldcDeInit
 *  \brief LDC HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issldcDeInit(Ptr arg);

/**
 *  VpsHal_issldcOpen
 *  \brief This function should be called prior to calling any of the LDC HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issldcOpen(const isshalldcOpenParams_t *openPrms);

/**
 *  VpsHal_issldcClose
 *  \brief This functions closes the ldc handle and after call to this
 *  function, ldc handle is not valid.
 *
 *  \param handle         Requested VTNF instance
 */
int32_t VpsHal_issldcClose(VpsHal_Handle handle);

/**
 *  \brief Sets the entire LDC configuration to the LDC registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issldcConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetConfig(VpsHal_Handle            handle,
                               const vpsissldcConfig_t *cfg,
                               Ptr                      arg);

/**
 *  VpsHal_issldcGetConfig
 *  \brief Gets the entire LDC configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issldcConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcGetConfig(VpsHal_Handle handle, vpsissldcConfig_t *cfg);

/**
 *  VpsHal_issldcControl
 *  \brief LDC specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg);

/**
 *  VpsHal_issldcSetInFrameAddress
 *  \brief LDC Api for setting input address.
 *
 *  \param handle           Instance handle
 *  \param mode             LDC Mode, provides data Format
 *  \param addrLuma         Input Luma address, must be 16byte aligned
 *  \param addrChroma       Input Chroma address, must be 16byte aligned
 *  \param lineOffset       Line Offset/pitch for input buffers
 *                          must be even and 16byte aligned
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetInFrameAddress(VpsHal_Handle   handle,
                                       vpsissldcMode_t mode,
                                       uint32_t        addrLuma,
                                       uint32_t        addrChroma,
                                       uint32_t        lineOffset);

/**
 *  VpsHal_issldcSetOutFrameAddress
 *  \brief LDC Api for setting output address.
 *
 *  \param handle           Instance handle
 *  \param mode             LDC Mode, provides data Format
 *  \param addrLuma         Output Luma address, must be 16byte aligned
 *  \param addrChroma       Output Chroma address, must be 16byte aligned
 *  \param lineOffset       Line Offset/pitch for input buffers
 *                          must be even and 16byte aligned
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetOutFrameAddress(VpsHal_Handle   handle,
                                        vpsissldcMode_t mode,
                                        uint32_t        addrLuma,
                                        uint32_t        addrChroma,
                                        uint32_t        lineOffset);
/**
 *  VpsHal_issldcStart
 *  \brief LDC Api for enabling LDC module.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  VpsHal_issldcStop
 *  \brief LDC Api for disabling LDC module.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcStop(VpsHal_Handle handle);

/**
 *  VpsHal_issldcSetLutConfig
 *  \brief API for setting LUT configuration.
 *
 *  \param handle           Instance handle
 *  \param lutCfg           Pointer to LUT configuration structure
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetLutConfig(VpsHal_Handle            handle,
                                  const vpsissldcLutCfg_t *lutCfg);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_LDC_H_ */
