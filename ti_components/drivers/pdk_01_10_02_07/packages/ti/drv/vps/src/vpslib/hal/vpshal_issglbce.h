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
 *  \file vpshal_issglbce.h
 *
 *  \brief HAL Header file for GLBCE
 *  This file exposes the HAL APIs for ISS GLBCE module
 *
 */

#ifndef VPSHAL_ISS_GLBCE_H_
#define VPSHAL_ISS_GLBCE_H_

/**
 * Notes:
 * 1, GLBCE does not really do anything with the stall signal, it just forwards
 *    stall from CAL output to CAL input. Upstream module should stop
 *    sending data. Stall signal is tied high??
 * 2, Requires start up sequence after powering it on. Should be taken care
 *    in the upper layer, HAL does not take care
 * 3, There are 8 sets of 16bit x 256 entry table, mapped to MMR
 * 4, Receives pixel clock from vport/switch and functional clock from isp
 * 5, Requires 2 line memory (2 x 32bit x 1408(W/2)) and a cache memory
 *    (8 sets of 16bit x 1024)
 * 6, Minimum input size is 480x240
 * 7, Requires initialization state of 554 clock cycles, while in this stage,
 *    filter flag is on and there should not be any input frame
 * 8, LUTs must not be changed during active frame, must be changed in
 *    blanking interval. In most cases, LUT_F1 is changed from frame to frame,
 *    other LUTs are not expected to be updated dynamically
 * 9, where is the cache memory of GLBCE is mapped?
 * 10, Generates the statistics into the cache memory, these statistics
 *     should be read in the DDR and used for the next frame and current frame
 * 11, Supports frame division processing mode (sliced mode), statistics
 *     are generated for the first slice and used for subsequent slices
 * 12, What is I_Variant and S_Variant. Depending on this parameter,
 *     blanking requirement of the GLBCE is changing.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#include <ti/drv/vps/include/iss/vps_cfgglbce.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief GLBCE maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_GLBCE_MAX_INST                     (1u)

/* Control IOCTLs supported by GLBCE */

/**
 *  \brief Ioctl for setting Glbce Configuration
 */
#define ISSHAL_IOCTL_GLBCE_SET_GLBCECFG     (VPS_HAL_ISS_IOCTL_GLBCE_BEGIN  + \
                                             0u)
/**
 *  \brief Ioctl for setting Forward Percept Configuration
 */
#define ISSHAL_IOCTL_GLBCE_SET_FWDPRCPT_CFG (ISSHAL_IOCTL_GLBCE_SET_GLBCECFG + \
                                             1u)

/**
 *  \brief Ioctl for setting Reverse Percept Configuration
 */
#define ISSHAL_IOCTL_GLBCE_SET_REVPRCPT_CFG \
    (ISSHAL_IOCTL_GLBCE_SET_FWDPRCPT_CFG  + \
     1u)

/**
 *  \brief Ioctl for setting Reverse Percept Configuration
 */
#define ISSHAL_IOCTL_GLBCE_SET_WDRCFG (ISSHAL_IOCTL_GLBCE_SET_REVPRCPT_CFG  + \
                                       1u)

/**
 *  \brief Ioctl for Getting Default Configuration, this ioctl fills
 *         up complete isshalglbceConfig_t structure and returns.
 */
#define ISSHAL_IOCTL_GLBCE_GET_DEFAULTCFG   (ISSHAL_IOCTL_GLBCE_SET_WDRCFG  + \
                                             1u)

/**
 *  \brief Ioctl for configure the frame width / height
 */
#define ISSHAL_IOCTL_GLBCE_SET_FRAME_CFG   (ISSHAL_IOCTL_GLBCE_GET_DEFAULTCFG \
                                            + 1u)

/**
 *  \brief Ioctl for Stats Info
 */
#define ISSHAL_IOCTL_GLBCE_GET_STATS_INFO  (ISSHAL_IOCTL_GLBCE_SET_FRAME_CFG \
                                            + 1u)

#if (ISSHAL_IOCTL_GLBCE_GET_STATS_INFO > VPS_HAL_ISS_IOCTL_GLBCE_END)
    #error "Increase VPS_HAL_ISS_IOCTL_GLBCE_END in vpshal_iss.h file"
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum to define the various GLBCE instance.
 */
typedef enum isshalglbceInstId
{
    ISSHAL_GLBCE_INST_0 = 0,
    /**< Glbce Instance Id 0. */
    ISSHAL_GLBCE_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_GLBCE_INST_FORCE_INT = 0x7FFFFFFF
                                  /**< This will ensure enum is not packed, will always be contained in int */
} isshalglbceInstId_t;

/**
 *  \brief Configuration parameters of GLBCE.
 */
typedef struct isshalglbceConfig
{
    uint32_t                   width;
    /**< Width of the input frame size */
    uint32_t                   height;
    /**< Height of the input frame size */

    vpsissGlbceConfig_t        glbceCfg;
    /**< GLBCE Tone mapping configuration */

    vpsissGlbcePerceptConfig_t fwdPrcptCfg;
    /**< Forward Percept Config Configuration Structure */
    vpsissGlbcePerceptConfig_t revPrcptCfg;
    /**< Forward Percept Config Configuration Structure */
    vpsissGlbceWdrConfig_t     wdrCfg;
    /**< WDR Configuration structure */
} isshalglbceConfig_t;

/**
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalglbceInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalglbceInstId. */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t glbceStatMemAddress;
    /**< GLBCE Statistics memory based address */
    uint32_t glbceStatMemSize;
    /**< GLBCE Statistics memory size */
} isshalglbceInstParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issglbceInit
 *  \brief GLBCE init function.
 *
 *  Initializes GLBCE objects.
 *  This function should be called before calling any of GLBCE HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalglbceInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issglbceInit(
    uint32_t                       numInst,
    const isshalglbceInstParams_t *instPrms,
    Ptr                            arg);

/**
 *  VpsHal_issglbceDeInit
 *  \brief GLBCE HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issglbceDeInit(Ptr arg);

/**
 *  VpsHal_issglbceOpen
 *  \brief This function should be called prior to calling any of the GLBCE HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters containing instance to be opened
 */
VpsHal_Handle VpsHal_issglbceOpen(const isshalOpenParams_t *openPrms,
                                  Ptr                       arg);

/**
 *  VpsHal_issglbceClose
 *  \brief This functions closes the glbce handle and after call to this
 *  function, glbce handle is not valid.
 *
 *  \param handle         Requested GLBCE instance
 */
int32_t VpsHal_issglbceClose(VpsHal_Handle handle,
                             Ptr           arg);

/**
 *  \brief Sets the entire GLBCE configuration to the GLBCE registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issglbceConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issglbceSetConfig(
    VpsHal_Handle              handle,
    const isshalglbceConfig_t *cfg,
    Ptr                        arg);

/**
 *  VpsHal_issglbceGetConfig
 *  \brief Gets the entire GLBCE configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issglbceConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issglbceGetConfig(
    VpsHal_Handle        handle,
    isshalglbceConfig_t *config);

/**
 *  VpsHal_issglbceControl
 *  \brief GLBCE specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issglbceControl(
    VpsHal_Handle handle,
    uint32_t      cmd,
    Ptr           cmdArgs,
    Ptr           arg);

/**
 *  VpsHal_issglbceStart
 *  \brief GLBCE Api for enabling the module. Used to start the GLBCE block
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
int32_t VpsHal_issglbceStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  VpsHal_issglbceStop
 *  \brief GLBCE Api for disabling the module, when it is used in free
 *         running mode.
 *
 *  \param handle           Instance handle
 *  \param arg              Not Used
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issglbceStop(
    VpsHal_Handle handle,
    Ptr           arg);

int32_t VpsHal_issglbceGetDefaultConfig(
    VpsHal_Handle        handle,
    isshalglbceConfig_t *cfg);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_GLBCE_H_ */
