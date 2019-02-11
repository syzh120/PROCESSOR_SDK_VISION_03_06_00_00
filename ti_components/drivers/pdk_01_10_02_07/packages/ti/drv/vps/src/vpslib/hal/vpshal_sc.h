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
 *  \file vpshal_sc.h
 *
 *  \brief HAL Header file for SC
 *  This file exposes the HAL APIs for VPS SC module
 *
 */
#ifndef VPSHAL_SC_H_
#define VPSHAL_SC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/include/vps_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum VpsHal_ScInstId
 *  \brief Keep VPSHAL_VPE1_SC instances after VIPx instances - required to
 *  control multiple handle support.
 */
typedef enum
{
    VPSHAL_VIP1_S0_SC = 0,
    /**< VIP 1 - Slice 0. */
    VPSHAL_VIP1_S1_SC,
    /**< VIP 1 - Slice 1. */
    VPSHAL_VIP2_S0_SC,
    /**< VIP 2 - Slice 0. */
    VPSHAL_VIP2_S1_SC,
    /**< VIP 2 - Slice 1. */
    VPSHAL_VIP3_S0_SC,
    /**< VIP 3 - Slice 0. */
    VPSHAL_VIP3_S1_SC,
    /**< VIP 3 - Slice 1. */
    VPSHAL_VPE1_SC,
    /**< VPE. */

    /*
     * Below instances are applicable only to TI81xx platforms.
     */
    VPSHAL_SC_INST_2,
    /**< Scaler on the auxiliary path. */
    VPSHAL_SC_INST_5,
    /**< Scaler on the write back path. */

    VPSHAL_SC_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_ScInstId;

/**
 *  \brief SC maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define VPSHAL_SC_MAX_INST              (7U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_ScInstParams
 *  \brief Structure containg parameters to initialize SC HAL instance
 *         Primarily baseAddress.
 */
typedef struct
{
    UInt32                 halId;
    /**< Hal ID for current instance. For valid values see #VpsHal_ScInstId. */
    UInt32                 baseAddr;
    /**< Base address for the current SC instance. */
    VpsHal_VpdmaConfigDest coeffConfigDest;
    /**< VPDMA configuration register destination for the Scaler instance. */
    UInt32                 isHqScaler;
    /**< Type of scaler - high quality or normal quality. */
} VpsHal_ScInstParams;

/**
 *  struct VpsHal_ScOpenParams
 *  \brief Structure to identify a SC HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< SC Instance ID: #VpsHal_ScInstId */
} VpsHal_ScOpenParams;

/**
 * VpsHal_ScFactorConfig
 * \brief This structure contains configuration information related to
 * horizontal and vertical scaling factor for the scaler HAL. This structure
 * contains the horizontal and vertical scaling configuration that is dependent
 * on the scaling factor.
 */
typedef struct
{
    UInt32 hsDcmType;
    /**< This indicates the horizontal scaling algortihm used.
     *   For valid values see #Vps_ScHorzScalerDcmType. */
    UInt32 hScalingSet;
    /**< Coefficient set to be used for the horizontal scaling.
     *   For valid values see #Vps_ScCoeffSet. */
    UInt32 vsType;
    /**< This indicates the horizontal scaling algortihm.
     *   For valid values see #Vps_ScVertScalerType. */
    UInt32 vScalingSet;
    /**< Coefficient set to be used for the vertical scaling.
     *   For valid values see #Vps_ScCoeffSet. */
    UInt32 hPolyBypass;
    /**< Whether horizontal polyphase filtering should be bypassed.
     *    this is applicable only if cfg_auto_hs =1 in SC_0 register,
     *    In current Driver cfg_auto_hs is always zero, so this variable
     *    is dont care. */
} VpsHal_ScFactorConfig;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_scInit
 *  \brief SC HAL init function.
 *
 *  Initializes SC objects, gets the register overlay offsets for SC
 *  registers.
 *  This function should be called before calling any of SC HAL API's.
 *  VPDMA HAL should be initialized prior to calling any of SC HAL
 *  functions.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #VpsHal_ScInstParams.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
Int32 VpsHal_scInit(UInt32                     numInst,
                    const VpsHal_ScInstParams *instPrms,
                    Ptr                        arg);

/**
 *  VpsHal_scDeInit
 *  \brief SC HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_scDeInit(Ptr arg);

/**
 *  VpsHal_scOpen
 *  \brief Returns the handle to the requested SC instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the SC HAL
 *  configuration APIs.
 *
 *  VpsHal_scInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param instId        VpsHal_ScOpenParams
 *
 *  \return              success     SC instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_scOpen(const VpsHal_ScOpenParams *instId);

/**
 *  VpsHal_scClose
 *  \brief Closes specified instance of SC HAL
 *  VpsHal_scInit and scOpen should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_scOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_scClose(VpsHal_Handle handle);

/**
 *  VpsHal_scSetConfig
 *  \brief This function is used to set the scaler parameters in appropriate
 *  scaler register or in the virtual registers created in the register
 *  overlay whose address is passed as the last argument. If last
 *  argument is null, it will set the parameters in registers otherwise
 *  it will set the parameters in the VPDMA register overlay.
 *
 *  \param handle           Scaler Handle
 *  \param config           pointers to structure containing scaler parameters
 *                          While calling this function ensure
 *                          config->advCfg->vsType != VPS_SC_VST_AUTO
 *                          config->advCfg->hsDcmType != VPS_SC_HST_DCM_AUTO
 *                          Use #VpsHal_scGetScFactorConfig to set this
 *                          variables appropriately
 *  \param ovlyPtr          Pointer to memory containing VPDMA register
 *                          overlay for scaler. It can be set to memory
 *                          pointer to program register in overlay or set
 *                          to null to program directly in hardware register
 *
 *  \return                 0 on success, -1 on error
 */
Int32 VpsHal_scSetConfig(VpsHal_Handle       handle,
                         const Vps_ScConfig *config,
                         Ptr                 ovlyPtr);

/**
 *  VpsHal_scGetScFactorConfig
 *
 *  \param handle          Scaler Handle
 *  \param config          Pointer to structure containing scaler parameters.
 *  \param scFactorCfg     Pointer to structure scaling factors and scaling
 *                         types. This is the output of this function.
 *
 *  \brief This function is used to get the information that
 *  identifies the scaling factor for the provided configuration.
 *  It also sets the register related to vsType changes.
 */
Int32 VpsHal_scGetScFactorConfig(VpsHal_Handle          handle,
                                 const Vps_ScConfig    *config,
                                 VpsHal_ScFactorConfig *scFactorCfg);

/**
 *  void VpsHal_scSetNonRTParams
 *  \brief Function is used to set registers which are NOT allowed to be changed
 *  at run-time. These include peaking/ED config, some thresholds, lin/non-lin
 *  scaling type, etc.
 *
 *  \param handle           Scaler Handle
 *  \param config           Pointer to structure containing scaler parameters.
 *                          While calling this function ensure
 *                          config->vsType != VPS_SC_VST_AUTO
 *                          config->hsDcmType != VPS_SC_HST_DCM_AUTO
 *  \param ovlyPtr          VPDMA register overlay pointer
 *
 *  \return                 None
 */
void VpsHal_scSetNonRTParams(VpsHal_Handle       handle,
                             const Vps_ScConfig *config,
                             Ptr                 ovlyPtr);

/**
 *  void VpsHal_scSetRTParams
 *  \brief Function is used to set registers which are allowed to be changed at
 *  run-time. These are the scaling ratio, dimensions and position specific
 *  parameters in the VPDMA register overlay. This function will only change
 *  scaling ratio specific parameters. It will not change scaling algorithm
 *  or parameters configurable in CFG_SC0 register.
 *
 *  \param handle           Scaler Handle
 *  \param config           Pointer to structure containing scaler parameters.
 *                          While calling this function ensure
 *                          config->vsType != VPS_SC_VST_AUTO
 *                          config->hsDcmType != VPS_SC_HST_DCM_AUTO
 *  \param ovlyPtr          VPDMA register overlay pointer
 *
 *  \return                 None
 */
void VpsHal_scSetRTParams(VpsHal_Handle       handle,
                          const Vps_ScConfig *config,
                          Ptr                 ovlyPtr);

/**
 *  VpsHal_scGetVpdmaConfigDest
 *  \brief Returns the VPDMA configuration destination to program coefficients
 *  for this scaler instance.
 *
 *  \param handle           Scaler Handle
 *
 *  \return                 VPDMA configuration destination
 */
VpsHal_VpdmaConfigDest VpsHal_scGetVpdmaConfigDest(VpsHal_Handle handle);

/**
 *  void VpsHal_scGetRegOvlySize
 *  \brief Function to get the VPDMA register overlay size required to
 *  store scaler registers. This overlay is mainly used for stoing
 *  register for the runtime configuration as well as for the memory
 *  to memory driver where configuration changes for each channel.
 *
 *  \param handle           Scaler Handle
 *
 *  \return                 Register Overlay size
 */
UInt32 VpsHal_scGetConfigOvlySize(VpsHal_Handle handle);

/**
 *  void VpsHal_scCreateConfigOvly
 *  \brief This function is used to create the complete VPDMA register overlay
 *  for scaler registers. It just create the overlay but does not
 *  initialize the virtual registers with the configuration.
 *  Configuration can be done by calling Sc_setParams function.
 *
 *  \param handle           Scaler Handle
 *  \param configOvlyPtr    Pointer to memory where VPDMA overlay will be
 *                          stored
 *
 *  \return                 0 on success, -1 on error
 */
Int32 VpsHal_scCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr);

/**
 *  void VpsHal_scGetCoeffOvlySize
 *  \brief This function is used to get the memory size required to
 *  store coefficients. It returns size in terms of bytes. Upper
 *  layer can allocate the memory and pass this memory with the
 *  coefficients to fill the the memory with coefficients.
 *
 *  \param handle            Scaler Handle
 *  \param horzCoeffOvlySize Location to return size of horizontal scaling
 *                           coefficients
 *  \param vertCoeffOvlySize Location to return size of vertical scaling
 *                           coefficients
 *  \param vertBilinearCoeffOvlySize Location to return size of vertical
 *                                   bilinear scaling coefficients. If not HQ
 *                                   scaler, value returned shall be 0.
 *
 *  \return                 None
 */
void VpsHal_scGetCoeffOvlySize(VpsHal_Handle handle,
                               UInt32       *horzCoeffOvlySize,
                               UInt32       *vertCoeffOvlySize,
                               UInt32       *vertBilinearCoeffOvlySize);

/**
 *  VpsHal_scSetUserCoeff
 *
 *  \brief  If the application has its own set of coefficients and does not
 *          want to use driver provided coefficient, this function is used. It
 *          copies the user provided coefficients locally so that they can be
 *          used instead of the defaults during scaling.
 *          Coefficient Memory must be allocated by using size provided
 *          by scaler.
 *  \param  handle          Scaler Handle
 *  \param  coeff           Structure containing all user-provided scaler
 *                          coefficients.
 *
 *  \return 0               on Success
 *          -1              on Error
 */
Int32 VpsHal_scSetUserCoeff(VpsHal_Handle      handle,
                            const Vps_ScCoeff *coeff);

/**
 *  VpsHal_scGetCoeffOvlyMemPtr
 *  \brief Function is used to get the coefficient overlay memory pointers
 *  with the standard coefficients provided by the IP team or if with the
 *  user provided memeory pointer in case user has given the coeff.
 *  The coefficients are selected based on the scaling ratio.
 */
Int32 VpsHal_scGetCoeffOvlyMemPtr(
    VpsHal_Handle                handle,
    const VpsHal_ScFactorConfig *config,
    Ptr                         *horzCoeffMemPtr,
    Ptr                         *vertCoeffMemPtr,
    Ptr                         *
    vertBilinearCoeffMemPtr);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_SC_H_ */
