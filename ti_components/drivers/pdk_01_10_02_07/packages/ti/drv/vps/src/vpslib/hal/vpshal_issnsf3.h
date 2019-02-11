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
 *  \file vpshal_issnsf3.h
 *
 *  \brief HAL Header file for NSF3
 *  This file exposes the HAL APIs for ISS NSF3 module
 *
 */

#ifndef VPSHAL_ISS_NSF3_H_
#define VPSHAL_ISS_NSF3_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/iss/vps_cfgnsf3.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 1, Blanking requirement, 32 pixels and 24 lines when cropping is enabled and
 *    48pixels and 14 lines when copying is enabled
 * 2, Supports only 12bpp
 * 3, When DPC is used as pre-NSF3
 *      1, NF-1 function is turned off.
 *      2, turning on/off DPC by setting 0 to enable bit will change
 *         the latency of DPC function. This may result in the change
 *         in blanking period. Therefore, it is recommended to disable
 *         DPC by changing parameters rather than by setting 0/1
 *         to enable bit
 *      3, if DPC works in Pre-NSF3V, IPIPE_CLK_ENABLE bit must be
 *         turned on before MMR of DPC is accessed.
 *      4, whole ISP must be reset for resetting NSF3
 *      5, If the input is YUV422, PCLK must be x1/2 of functional
 *         clock or lower
 *      6, Downstream modules may require to be programmed
 *         differently when it is enabled like IPIPEIF.PPLN/LPFR
 */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Maximm Color Component
 */
#define ISSHAL_NSF3_MAX_COLOR               (VPS_ISS_NSF3_MAX_COLOR)

/**
 *  \brief Maximum number of NSF Threshold
 */
#define ISSHAL_NSF3_MAX_NSF_THRESHOLD       (VPS_ISS_NSF3_MAX_NSF_THRESHOLD)

/**
 *  \brief Maximum number of knee points
 */
#define ISSHAL_NSF3_MAX_KNEE_POINTS         (VPS_ISS_NSF3_MAX_KNEE_POINTS)

/**
 *  \brief Maximum number of Edge Enhancement level
 */
#define ISSHAL_NSF3_EE_MAX_LEVEL            (VPS_ISS_NSF3_EE_MAX_LEVEL)

/**
 *  \brief Maximum number of Supression level
 */
#define ISSHAL_NSF3_SUPPRESSION_MAX_LEVEL   (VPS_ISS_NSF3_SUPPRESSION_MAX_LEVEL)

/**
 *  \brief Maximum number of HA/VA Coefficients
 */
#define ISSHAL_NSF3_SHADE_GAIN_MAX_COEFF    (VPS_ISS_NSF3_SHADE_GAIN_MAX_COEFF)

/**
 *  \brief Ioctl for Getting Default Configuration, this ioctl fills
 *         up complete vpsissNsf3Config_t structure and returns.
 */
#define ISSHAL_IOCTL_NSF3_GET_DEFAULTCFG   (VPS_HAL_ISS_IOCTL_NSF3_BEGIN + \
                                            0U)

#if (ISSHAL_IOCTL_NSF3_GET_DEFAULTCFG > VPS_HAL_ISS_IOCTL_NSF3_END)
    #error "Increase VPS_HAL_ISS_IOCTL_NSF3_END in vpshal_iss.h file"
#endif

/**
 *  \brief NSF3 maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_NSF3_MAX_INST                            (2U)

/**
 *  \brief Enum to define the various NSF3 instance.
 */
typedef enum isshalnsf3InstId
{
    ISSHAL_NSF3_INST_0 = 0,
    /**< Nsf3 Instance Id 0. */
    ISSHAL_NSF3_INST_1,
    /**< Nsf3 Instance Id 1. */
    ISSHAL_NSF3_INST_MAX_ID
    /**< Max - used for error check. */
} isshalnsf3InstId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalnsf3InstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalnsf3InstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalnsf3InstId. */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t moduleId;
} isshalnsf3InstParams_t;

typedef struct isshalnsf3FrameSizeParams
{
    uint32_t width;
    /**< Image width, in pixels.
     *   For Bayer and YUV420_Y, YUV420_UV, this is the same as
     *   number of data points horizontally.
     *   For YUV422, this is half of number of data points horizontally */
    uint32_t height;
    /**< Image height, in lines.
     *   For Bayer, YUV422, and YUV420_Y, this is same as vertical
     *   resolution in pixels.
     *   For YUV420_UV, image height is half of vertical resolution in pixels */
} isshalnsf3FrameSizeParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issnsf3Init
 *  \brief NSF3 init function.
 *
 *  Initializes NSF3 objects.
 *  This function should be called before calling any of NSF3 HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalnsf3InstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issnsf3Init(
    UInt32                        numInst,
    const isshalnsf3InstParams_t *instPrms,
    Ptr                           arg);

/**
 *  VpsHal_issnsf3DeInit
 *  \brief NSF3 HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issnsf3DeInit(Ptr arg);

/**
 *  VpsHal_issnsf3Open
 *  \brief This function should be called prior to calling any of the NSF3 HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issnsf3Open(const isshalOpenParams_t *openPrms,
                                 Ptr                       arg);

/**
 *  VpsHal_issnsf3Close
 *  \brief This functions closes the nsf3 handle and after call to this
 *  function, nsf3 handle is not valid.
 *
 *  \param handle         Requested NSF3 instance
 */
int32_t VpsHal_issnsf3Close(VpsHal_Handle handle,
                            Ptr           arg);

/**
 *  \brief Sets the entire NSF3 configuration to the NSF3 registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issnsf3Config structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issnsf3SetConfig(
    VpsHal_Handle             handle,
    const vpsissNsf3Config_t *cfg,
    Ptr                       arg);

/**
 *  VpsHal_issnsf3GetConfig
 *  \brief Gets the entire NSF3 configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issnsf3Config structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issnsf3GetConfig(
    VpsHal_Handle       handle,
    vpsissNsf3Config_t *config);

/**
 *  VpsHal_issnsf3Control
 *  \brief NSF3 specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issnsf3Control(
    VpsHal_Handle handle,
    UInt32        cmd,
    Ptr           cmdArgs,
    Ptr           arg);

/**
 *  VpsHal_issnsf3Start
 *  \brief NSF3 Api for enabling the module. Used to start the NSF3 block
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
int32_t VpsHal_issnsf3Start(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  VpsHal_issnsf3Stop
 *  \brief NSF3 Api for disabling the module, when it is used in free
 *         running mode.
 *
 *  \param handle           Instance handle
 *  \param arg              Not Used
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issnsf3Stop(
    VpsHal_Handle handle,
    Ptr           arg);

/**
 *  VpsHal_issnsf3Stop
 *  \brief NSF3 Api for setting the clock division.
 *         Output Clock = functional clock * fractClk / 64K
 *
 *  \param handle           Instance handle
 *  \param fractClk         Fractional Clock Value
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issnsf3SetFractClkDiv(VpsHal_Handle handle, uint32_t fractClk);

/**
 *  VpsHal_issnsf3SetFrameSize
 *  \brief NSF3 Api for configuring frame size.
 *
 *  \param handle           Instance handle
 *  \param cfg              frameWidth, frameHeight members of this structure
 *                              are used.
 *  \param arg              Not Used
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issnsf3SetFrameSize(
    VpsHal_Handle                      handle,
    const isshalnsf3FrameSizeParams_t *cfg,
    Ptr                                arg);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_NSF3_H_ */
