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
 *  \file vpshal_issh3a.h
 *
 *  \brief HAL Header file for H3A
 *  This file exposes the HAL APIs for ISS H3A module
 *
 */

#ifndef VPSHAL_ISS_H3A_H_
#define VPSHAL_ISS_H3A_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/iss/vps_cfgh3a.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief H3A maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_H3A_MAX_INST                     (1U)

/* Control IOCTLs supported by H3A */

/**
 *  \brief Ioctl for setting Auto Focus Configuration
 */
#define ISSHAL_IOCTL_H3A_SET_AFCFG        (VPS_HAL_ISS_IOCTL_H3A_BEGIN + \
                                           0U)
/**
 *  \brief Ioctl for setting AE/Awb Configuration
 */
#define ISSHAL_IOCTL_H3A_SET_AEWBCFG      (VPS_HAL_ISS_IOCTL_H3A_BEGIN + \
                                           1U)

/**
 *  \brief Ioctl for Getting Default Configuration, this ioctl fills
 *         up complete isshalh3aConfig_t structure and returns.
 */
#define ISSHAL_IOCTL_H3A_GET_DEFAULTCFG   (VPS_HAL_ISS_IOCTL_H3A_BEGIN + \
                                           2U)

#if (ISSHAL_IOCTL_H3A_GET_DEFAULTCFG > VPS_HAL_ISS_IOCTL_H3A_END)
    #error "Increase VPS_HAL_ISS_IOCTL_H3A_END in vpshal_iss.h file"
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum to define the various H3A instance.
 */
typedef enum isshalh3aInstId
{
    ISSHAL_H3A_INST_0 = 0,
    /**< H3a Instance Id 0. */
    ISSHAL_H3A_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_H3A_INST_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed, will always be contained in int */
} isshalh3aInstId_t;

/**
 *  \brief Configuration parameters of H3A.
 */
typedef struct isshalh3aConfig
{
    Fvid2_PosConfig       pos;
    /**< Start position for H3A module */

    vpsissH3aAfConfig_t   afCfg;
    /**< AutoFocus Configuration */

    vpsissH3aAewbConfig_t aewbCfg;
    /**< AE/AWB Configuration */
} isshalh3aConfig_t;

/**
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalh3aInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalh3aInstId. */
    uint32_t baseAddress;
    /**< Register base address */
} isshalh3aInstParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issh3aInit
 *  \brief H3A init function.
 *
 *  Initializes H3A objects.
 *  This function should be called before calling any of H3A HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalh3aInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issh3aInit(
    uint32_t                     numInst,
    const isshalh3aInstParams_t *instPrms,
    Ptr                          arg);

/**
 *  VpsHal_issh3aDeInit
 *  \brief H3A HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issh3aDeInit(Ptr arg);

/**
 *  VpsHal_issh3aOpen
 *  \brief This function should be called prior to calling any of the H3A HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters containing instance to be opened
 */
VpsHal_Handle VpsHal_issh3aOpen(const isshalOpenParams_t *openPrms,
                                Ptr                       arg);

/**
 *  VpsHal_issh3aClose
 *  \brief This functions closes the h3a handle and after call to this
 *  function, h3a handle is not valid.
 *
 *  \param handle         Requested H3A instance
 */
int32_t VpsHal_issh3aClose(VpsHal_Handle handle,
                           Ptr           arg);

/**
 *  \brief Sets the entire H3A configuration to the H3A registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issh3aConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issh3aSetConfig(
    VpsHal_Handle            handle,
    const isshalh3aConfig_t *cfg,
    Ptr                      arg);

/**
 *  VpsHal_issh3aGetConfig
 *  \brief Gets the entire H3A configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issh3aConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issh3aGetConfig(
    VpsHal_Handle      handle,
    isshalh3aConfig_t *config);

int32_t VpsHal_issh3aSetAfConfig(
    VpsHal_Handle              handle,
    const vpsissH3aAfConfig_t *cfg,
    Ptr                        arg);
int32_t VpsHal_issh3aSetAewbConfig(
    VpsHal_Handle                handle,
    const vpsissH3aAewbConfig_t *cfg,
    Ptr                          arg);
int32_t VpsHal_issh3aSetAfAddress(
    VpsHal_Handle handle,
    Ptr           address,
    Ptr           arg);
int32_t VpsHal_issh3aSetAewbAddress(
    VpsHal_Handle handle,
    Ptr           address,
    Ptr           arg);
/**
 *  VpsHal_issh3aControl
 *  \brief H3A specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issh3aControl(
    VpsHal_Handle handle,
    uint32_t      cmd,
    Ptr           cmdArgs,
    Ptr           arg);

/**
 *  VpsHal_issh3aStart
 *  \brief H3A Api for enabling the module. Used to start the H3A block
 *         in either free running or in One-Shot mode. In one-short mode,
 *         it will be disabled at the end of frame processing. In free running
 *         mode, it should be disabled by calling stop API.
 *
 *  \param handle           Instance handle
 *  \param procMode         Processing Mode either one shot or free running
 *  \param arg              Not Used
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issh3aAfStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

int32_t VpsHal_issh3aAewbStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  VpsHal_issh3aStop
 *  \brief H3A Api for disabling the module, when it is used in free
 *         running mode.
 *
 *  \param handle           Instance handle
 *  \param arg              Not Used
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issh3aAfStop(
    VpsHal_Handle handle,
    Ptr           arg);
int32_t VpsHal_issh3aAewbStop(
    VpsHal_Handle handle,
    Ptr           arg);

int32_t VpsHal_issh3aGetDefaultConfig(
    VpsHal_Handle      handle,
    isshalh3aConfig_t *cfg);

/**
 *  VpsHal_issh3aIsAfBusy
 *  \brief API to check if AF module is busy or not.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns TRUE if it is busy, or FALSE
 */
uint32_t VpsHal_issh3aIsAfBusy(VpsHal_Handle handle);
/**
 *  VpsHal_issh3aIsAewbBusy
 *  \brief API to check if AEWB module is busy or not.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns TRUE if it is busy, or FALSE
 */
uint32_t VpsHal_issh3aIsAewbBusy(VpsHal_Handle handle);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_H3A_H_ */
