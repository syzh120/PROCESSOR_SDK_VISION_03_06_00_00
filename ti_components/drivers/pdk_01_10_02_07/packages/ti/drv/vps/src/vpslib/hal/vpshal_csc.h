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
 *  \file vpshal_csc.h
 *
 *  \brief HAL Header file for CSC
 *  This file exposes the HAL APIs for VPS CSC module
 *
 */

#ifndef VPSHAL_CSC_H_
#define VPSHAL_CSC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum VpsHal_CscInst
 *  \brief Keep VPSHAL_VPE1_CSC instances after VIPx instances - required to
 *  control multiple handle support
 */
typedef enum
{
    VPSHAL_VIP1_S0_CSC = 0,
    /**< VIP 1 - Slice 0. */
    VPSHAL_VIP1_S1_CSC,
    /**< VIP 1 - Slice 1. */
    VPSHAL_VIP2_S0_CSC,
    /**< VIP 2 - Slice 0. */
    VPSHAL_VIP2_S1_CSC,
    /**< VIP 2 - Slice 1. */
    VPSHAL_VIP3_S0_CSC,
    /**< VIP 3 - Slice 0. */
    VPSHAL_VIP3_S1_CSC,
    /**< VIP 3 - Slice 1. */
    VPSHAL_VPE1_CSC,
    /**< VPE. */

    /*
     * Below instances are applicable only to TI81xx platforms.
     */
    VPSHAL_CSC_INST_HD1,
    /**< CSC block on the HD1 display path which displays HD mode. */
    VPSHAL_CSC_INST_SD,
    /**< CSC block on SD display path. */
    VPSHAL_CSC_INST_WB2,
    /**< CSC block on the display write back path. */
    VPSHAL_CSC_INST_HD0,
    /**< CSC block on the HD0 display path which displays HD mode. */

    VPSHAL_CSC_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_CscInstId;

/**
 *  \brief CSC maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define VPSHAL_CSC_MAX_INST             (7U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_CscInstParams
 *  \brief Structure containg parameters to initialize CSC HAL instance,
 *  primarily base address.
 */
typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance. For valid values see #VpsHal_CscInstId. */
    UInt32 baseAddr;
    /**< Base address of CSC module for current instance. */
} VpsHal_CscInstParams;

/**
 *  struct VpsHal_CscOpenParams
 *  \brief Structure to identify a CSC HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< CSC Instance ID. For valid values see #VpsHal_CscInstId. */
} VpsHal_CscOpenParams;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_cscInit
 *  \brief CSC HAL init function.
 *
 *  Initializes CSC objects, gets the register overlay offsets for CSC
 *  registers.
 *  This function should be called before calling any of CSC HAL API's.
 *  VPDMA HAL should be initialized prior to calling any of CSC HAL
 *  functions.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #VpsHal_CscInstParams.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
Int32 VpsHal_cscInit(UInt32                      numInst,
                     const VpsHal_CscInstParams *instPrms,
                     Ptr                         arg);

/**
 *  VpsHal_cscDeInit
 *  \brief CSC HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_cscDeInit(Ptr arg);

/**
 *  VpsHal_cscOpen
 *  \brief Returns the handle to the requested CSC instance.
 *
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the CSC HAL
 *  configuration APIs.
 *
 *  VpsHal_cscInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openPrms     VpsHal_CscOpenParams *
 *
 *  \return             success     CSC instance's HAL handle
 *                      failure     NULL
 */
VpsHal_Handle VpsHal_cscOpen(const VpsHal_CscOpenParams *openPrms);

/**
 *  VpsHal_cscClose
 *  \brief Closes specified instance of CSC HAL
 *  VpsHal_cscInit and cscOpen should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_cscOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_cscClose(VpsHal_Handle handle);

/**
 *  VpsHal_cscGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA
 *  register configuration overlay required to program the CSC registers using
 *  VPDMA config descriptors.
 *
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the CSC registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context (multiple
 *  instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay one-time
 *  and submit this to VPDMA everytime when context changes. Thus saving
 *  valuable CPU in programming the VPS registers.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *
 *  \param handle Valid handle returned by VpsHal_cscOpen function.
 *
 *  \return       Returns 0 on success else returns error value.
 */
UInt32 VpsHal_cscGetConfigOvlySize(VpsHal_Handle handle);

/**
 *  VpsHal_cscCreateConfigOvly
 *  \brief Creates the CSC register configuration
 *  overlay using VPDMA helper function.
 *
 *  This function does not initialize the overlay with CSC configuration. It is
 *  the responsibility of the client driver to configure the overlay by calling
 *  VpsHal_cscSetConfig function before submitting the same to VPDMA for
 *  register configuration at runtime.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *
 *  \param handle         Valid handle returned by VpsHal_cscOpen function.
 *
 *  \param configOvlyPtr  Pointer to the overlay memory where the overlay is
 *                        formed. The memory for the overlay should be allocated
 *                        by client driver. This parameter should be non-NULL.
 *
 *  \return               Returns 0 on success else returns error value.
 */
Int32 VpsHal_cscCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr);

/**
 *  VpsHal_cscSetConfig
 *  \brief Sets the CSC configuration to either the
 *  actual CSC registers or to the configuration overlay memory.
 *
 *  This function configures the CSC registers. Depending on the value
 *  of configOvlyPtr parameter, the updating will happen to actual CSC MMR or
 *  to configuration overlay memory.
 *  This function configures all the sub-modules in CSC using other config
 *  function call.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *  CSC registers or configuration overlay memory are programmed
 *  according to the parameters passed.
 *
 *  \param handle          Valid handle returned by VpsHal_cscOpen function.
 *
 *  \param config          Pointer to Vps_CscConfig structure containing the
 *                         register configurations. This parameter should be
 *                         non-NULL.
 *
 *  \param configOvlyPtr   Pointer to the configuration overlay memory.
 *                         If this parameter is NULL, then the configuration is
 *                         written to the actual CSC registers. Otherwise the
 *                         configuration is updated in the memory pointed
 *                         by the same at proper virtual offsets. This parameter
 *                         can be NULL depending on the intended usage.
 *
 *  \return                Returns 0 on success else returns error value.
 */
Int32 VpsHal_cscSetConfig(VpsHal_Handle        handle,
                          const Vps_CscConfig *config,
                          Ptr                  configOvlyPtr);

/**
 *  VpsHal_cscGetConfig
 *  \brief Gets the CSC configuration from the actual CSC registers.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *
 *  \param handle  Valid handle returned by VpsHal_cscOpen function.
 *
 *  \param config  Pointer to Vps_CscConfig structure to be filled with
 *                 register configurations. This parameter should be non-NULL.
 *
 *  \return        Returns 0 on success else returns error value.
 */
Int32 VpsHal_cscGetConfig(VpsHal_Handle handle, Vps_CscConfig *config);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_CSC_H_ */
