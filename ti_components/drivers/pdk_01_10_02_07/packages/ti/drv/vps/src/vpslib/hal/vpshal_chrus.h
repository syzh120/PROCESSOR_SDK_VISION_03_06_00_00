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
 *  \file vpshal_chrus.h
 *
 *  \brief VPS Chroma Up Sampler HAL header file.
 *  This file exposes the HAL APIs of the VPS Chroma Up Sampler.
 *
 */

#ifndef VPSHAL_CHRUS_H_
#define VPSHAL_CHRUS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#include <ti/drv/vps/include/vps_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Defines number of coefficients for each coefficient type
 */
#define VPSHAL_CHRUS_NUM_COEFFS             (4U)

/**
 *  enum VpsHal_ChrusInstId
 *  \brief Enum to define the various CHRUS instance.
 */
typedef enum
{
    VPSHAL_VPE1_CHRUS_PRI0 = 0,
    /**< CHRUS 0 on the Primary path. */
    VPSHAL_CHRUS_AUX,
    /**< CHRUS on the Auxiliary path. */
    VPSHAL_CHRUS_SEC0,
    /**< CHRUS on the Secondary path 0. */
    VPSHAL_CHRUS_SEC1,
    /**< CHRUS on the Secondary path 1. */
    VPSHAL_VPE1_CHRUS_PRI1,
    /**< CHRUS 1 on the Primary path. */
    VPSHAL_VPE1_CHRUS_PRI2,
    /**< CHRUS 2 on the Primary path. */

    VPSHAL_CHRUS_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_ChrusInstId;

/**
 *  \brief CHRUS maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define VPSHAL_CHRUS_MAX_INST       (6U)

/**
 *  \brief Enum for CHRUS Modes. Chroma Upsampler Supports four modes of
 *  operations depending input type and output operation
 */
typedef enum
{
    VPSHAL_CHRUS_CFGMODE_A = 0,
    /**< Indicates the Source is YUV420 and DEI is
     *   de-interlacing. CHR_US does chroma upsampling.
     *   Not used for secondary paths. */
    VPSHAL_CHRUS_CFGMODE_B,
    /**< Indicates the Source is YUV422 and DEI is
     *   de-interlacing. CHR_US is in bypass mode.
     *   Not used for secondary paths. */
    VPSHAL_CHRUS_CFGMODE_C,
    /**< Indicates the Source is YUV420 and DEI is not
     *   de-interlacing. CHR_US does chroma upsampling.
     *   This mode is also used for the secondary paths. */
    VPSHAL_CHRUS_CFGMODE_D
    /**< Indicates the Source is YUV422 and DEI is not
     *   de-interlacing. CHR_US is in bypass mode.
     *   This mode is also used for the secondary paths. */
} VpsHal_ChrusCfgMode;

/**
 *  enum Vps_ChrusCoeffType
 *  \brief Enum for Type Coefficients. The enum defines type of coefficients
 *  needs to be configured in CHR_US. This enum is mainly used as index in the
 *  Chrus_Coeff structure to index first dimension.
 */
typedef enum
{
    VPS_CHRUS_COEFFTYPE_ANCHOR_FID0 = 0,
    /**< Coefficients for Anchor pixel Field 0. */
    VPS_CHRUS_COEFFTYPE_INTERP_FID0,
    /**< Coefficients for interpolated pixel Field 0. */
    VPS_CHRUS_COEFFTYPE_ANCHOR_FID1,
    /**< Coefficients for Anchor pixel Field 1. */
    VPS_CHRUS_COEFFTYPE_INTERP_FID1,
    /**< Coefficients for interpolated pixel Field 1. */
    VPS_CHRUS_NUM_COEFFTYPE
    /**< Count of Coefficients Type. */
} Vps_ChrusCoeffType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_ChrusInstParams
 *  \brief Structure containing instance specific parameters used at the init.
 *
 *  halId      - Instance Identifier
 *  baseAddress - Physical register start address for this instance
 */
typedef struct
{
    UInt32 halId;
    /**< CHRUS Instance */
    UInt32 baseAddr;
    /**< Base address for the current instance */
} VpsHal_ChrusInstParams;

/**
 *  struct VpsHal_ChrusOpenParams
 *  \brief Structure to identify a CHRUS HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< CHRUS Instance ID. For valid values see #VpsHal_ChrusInstId. */
} VpsHal_ChrusOpenParams;

/**
 *  struct VpsHal_ChrusCoeff
 *  \brief Defines structure into which user provided coefficients
 *  can be provided.
 */
typedef struct
{
    UInt16 coeff[VPS_CHRUS_NUM_COEFFTYPE][VPSHAL_CHRUS_NUM_COEFFS];
    /**< 2D Array of coefficients. There are 4 coefficients for each type. */
} VpsHal_ChrusCoeff;

/**
 *  struct VpsHal_ChrusConfig
 *  \brief Configuration parameters for CHRUS.
 */
typedef struct
{
    VpsHal_ChrusCfgMode cfgMode;
    /**< CHR_US Mode. It selects the mode of operation in CHR_US depending on
     *   the input image format and output de-interlacing */
    Fvid2_ScanFormat    mode;
    /**< Frame Mode. This is used to select the one of the pre-calculated set
     *   of coefficients. This is used only if the coeff pointer is null */
    VpsHal_ChrusCoeff  *coeff;
    /**< Pointer to the user provided set of coefficients. It should be
     *   null in order to use pre-calculated coefficients */
} VpsHal_ChrusConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsHal_chrusInit
 *  \brief Initializes CHRUS objects, gets the register overlay offsets for
 *  CHRUS registers.
 *  This function should be called before calling any of CHRUS HAL API's.
 *
 *  \param numInst          Number of Noise Filter Instances and number of
 *                          array elements in the second argument
 *  \param instPrms         Instance Specific Parameters
 *  \param arg              Not used currently. Meant for future purpose.
 */
Int32 VpsHal_chrusInit(UInt32                        numInst,
                       const VpsHal_ChrusInstParams *instPrms,
                       Ptr                           arg);

/**
 *  VpsHal_chrusDeInit
 *  \brief Currently this function does not do anything.
 *
 *  \param arg       Not used currently. Meant for future purpose.
 */
Int32 VpsHal_chrusDeInit(Ptr arg);

/**
 *  VpsHal_chrusOpen
 *  \brief This function should be called prior to calling any of the CHRUS HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param chrusInst       Requested CHRUS instance
 */
VpsHal_Handle VpsHal_chrusOpen(const VpsHal_ChrusOpenParams *openPrms);

/**
 *  VpsHal_chrusClose
 *  \brief This functions closes the chrus handle and after call to this
 *  function, chrus handle is not valid. It also decrements the reference
 *  counter.
 *
 *  \param handle         Requested CHRUS instance
 */
Int32 VpsHal_chrusClose(VpsHal_Handle handle);

/**
 *  VpsHal_chrusGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA register configuration
 *  overlay required to program the CHRUS registers using VPDMA config
 *  descriptors.
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the CHRUS registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context
 *  (multiple instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay
 *  one-time and submit this to VPDMA everytime when context changes.
 *  Thus saving valuable CPU in programming the VPS registers.
 *
 *  \param handle         Instance handle
 *  \return               Returns the size of config overlay memory
 */
UInt32 VpsHal_chrusGetConfigOvlySize(VpsHal_Handle handle);

/**
 *  VpsHal_chrusCreateConfigOvly
 *  \brief Creates the CHRUS register configuration overlay using VPDMA
 *  helper function.
 *
 *  This function does not initialize the overlay with CHRUS configuration.
 *  It is the responsibility of the client driver to configure the overlay
 *  by calling HalChrus_setConfig function before submitting the same
 *  to VPDMA for register configuration at runtime.
 *
 *  \param handle           Instance handle
 *  \param configOvlyPtr    Pointer to the overlay memory where the
 *                          overlay is formed. The memory for the overlay
 *                          should be allocated by client driver.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_chrusCreateConfigOvly(VpsHal_Handle handle,
                                   Ptr           configOvlyPtr);

/**
 *  \brief Sets the entire CHRUS configuration to either the actual CHRUS
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire CHRUS registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual CHRUS MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in CHRUS using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_chrusConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          CHRUS registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_chrusSetConfig(VpsHal_Handle             handle,
                            const VpsHal_ChrusConfig *config,
                            Ptr                       configOvlyPtr);

/**
 *  VpsHal_chrusGetConfig
 *  \brief Gets the entire CHRUS configuration from the actual CHRUS registers.
 *
 *  This function gets the entire CHRUS configuration. This function
 *  gets the configuration of all the sub-modules in CHRUS using other
 *  get configuration function calls.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_chrusConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_chrusGetConfig(VpsHal_Handle handle, VpsHal_ChrusConfig *config);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSHAL_CHRUS_H_ */
