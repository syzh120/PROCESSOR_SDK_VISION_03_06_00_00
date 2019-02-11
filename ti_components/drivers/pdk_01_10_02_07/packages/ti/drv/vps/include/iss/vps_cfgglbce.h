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
 *  \file vps_cfgglbce.h
 *
 *  \brief
 *
 */

#ifndef VPS_CFG_GLBCE_H_
#define VPS_CFG_GLBCE_H_

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
 *  \brief Ioctl for getting GLBCE parameters
 */
#define VPS_ISS_GLBCE_IOCTL_GET_CONFIG     (VPS_ISS_IOCTL_GLBCE_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for setting GLBCE parameters
 */
#define VPS_ISS_GLBCE_IOCTL_SET_CONFIG     (VPS_ISS_GLBCE_IOCTL_GET_CONFIG + 1U)

/**
 *  \brief Size of the asymmentry LUT
 */
#define VPS_ISS_GLBCE_ASYMMETRY_LUT_SIZE        (33U)

/**
 *  \brief Size of Perceptual LUT
 */
#define VPS_ISS_GLBCE_PERCEPT_LUT_SIZE          (65U)

/**
 *  \brief Size of WDR LUT
 */
#define VPS_ISS_GLBCE_WDR_LUT_SIZE              (257U)

/**
 *  \brief Value of the second pole, used in generating assymetry lut.
 */
#define VPS_ISS_GLBCE_ASYMMETRY_LUT_SEC_POLE    (255U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Defines the sub-modules with in GLBCE. Used to identify sub-module
 *          of interest.
 */
typedef enum vpsissGlbceModule
{
    VPS_ISS_GLBCE_MODULE_GLBCE = 0x0,
    /**< Configure GLBCE common Settings */
    VPS_ISS_GLBCE_MODULE_FWD_PERCEPT = 0x1,
    /**< Configure Forward Perceptual Settings */
    VPS_ISS_GLBCE_MODULE_REV_PERCEPT = 0x2,
    /**< Configure Forward Perceptual Settings */
    VPS_ISS_GLBCE_MODULE_GET_STATS_INFO = 0x3,
    /**< Command to get the GLBCE Stats Information */
    VPS_ISS_GLBCE_MODULE_WDR = 0x4
} vpsissGlbceModule_t;  /**< vpsissGlbceModule_t */

/**
 *  \brief Defines valid dithering options supported.
 */
typedef enum vpsissGlbceDither
{
    VPS_ISS_GLBCE_NO_DITHER = 0x0,
    /**< No Dithering */
    VPS_ISS_GLBCE_DITHER_ONE_BIT = 0x1,
    /**< One least significant bit of the output is dithered */
    VPS_ISS_GLBCE_DITHER_TWO_BIT = 0x2,
    /**< Two least significant bit of the output are dithered */
    VPS_ISS_GLBCE_DITHER_THREE_BIT = 0x3,
    /**< Three least significant bit of the output are dithered */
    VPS_ISS_GLBCE_DITHER_FOUR_BIT = 0x4
                        /**< Four least significant bit of the output are dithered */
} vpsissGlbceDither_t;  /**< vpsissGlbceDither_t */

/**
 *  \brief Perceptual control structure. Used for both forward & reverse.
 */
typedef struct vpsissGlbcePerceptConfig
{
    uint32_t enable;
    /**< Flag to enable/disable Forward or Reverse Percept */
    uint32_t table[VPS_ISS_GLBCE_PERCEPT_LUT_SIZE];
    /**< Perceptual Table */
} vpsissGlbcePerceptConfig_t;

/**
 *  \brief WDR control structure.
 */
typedef struct vpsissGlbceWdrConfig
{
    uint32_t enable;
    /**< Flag to enable/disable FrontEnd Wdr */
    uint32_t table[VPS_ISS_GLBCE_WDR_LUT_SIZE];
    /**< WDR Table */
} vpsissGlbceWdrConfig_t;

/**
 *  \brief GLBCE Stats memory information
 */
typedef struct vpsissGlbceStatsInfo
{
    uint32_t addr;
    /**< Address of the stats memory */
    uint32_t size;
    /**< size of the stats memory */
} vpsissGlbceStatsInfo_t;

/**
 *  \brief GLBCE control structure, passed as an argument to
 *         VPS_ISS_GET_IOCTL_GET_CONFIG/VPS_ISS_GET_IOCTL_SET_CONFIG.
 */
typedef struct vpsissGlbceConfig
{
    uint32_t            enable;
    /**< Flag to enable/disable the module */

    uint32_t            irStrength;
    /**< This sets processing Strength. Minimum value is 0, maximum is 255.
     *   When set to 0x00, Video data will not be processed at all and will
     *   go to output unchanged. */

    uint32_t            blackLevel;
    /**< Blank level of the input pixels,
     *   value used here will be used as zero level for all GLBCE processing
     *   Data below Black level will not be processed and stay unchanged */
    uint32_t            whiteLevel;
    /**< Whie level of the input pixels,
     *   value used here will be used as white level for all GLBCE processing
     *   Data above white level will not be processed and stay unchanged*/

    uint32_t            intensityVariance;
    /**< Variance Intensity - Sets the degree of sensitivity in the
     *   luminance domain. Maximum Variance is 0xF, and minimum
     *   Variance is 0x0 */
    uint32_t            spaceVariance;
    /**< Variance Space - Sets the degree of spatial sensitivity of
     *   the algorithm. As this parameter is made smaller,
     *   the algorithm focuses on smaller regions within the image.
     *   Maximum Variance is 0xF, and minimum Variance is 0x0 */

    uint32_t            brightAmplLimit;
    /**< The resultant tone curve cannot be lower than bright
     *   amplification limit line controlled by the this parameter.
     *   Maximum limit is 0xF, when the value is 0x0 there is no limit */
    uint32_t            darkAmplLimit;
    /**< The resultant tone curve cannot be higher than dark
     *   amplification limit line controlled by the this parameter.
     *   Maximum limit is 0xF, when the value is 0x0 there is no limit */

    vpsissGlbceDither_t dither;
    /**< Sets the number of LSB bits to dither */

    uint32_t            maxSlopeLimit;
    /**< Slope Max Limit is used to restrict the slope of the
     *   tone-curve generated by GLBCE */
    uint32_t            minSlopeLimit;
    /**< Slope Min Limit is used to restrict the slope of the
     *   tone-curve generated by GLBCE */

    uint32_t            asymLut[VPS_ISS_GLBCE_ASYMMETRY_LUT_SIZE];
    /**< The Asymmetry Function Lookup Table, The size of each entry is 16bits.
     *   The Asymmetry function is used to balance the GLBCE
     *   effect between the dark and bright regions of the image */
} vpsissGlbceConfig_t;

/**
 *  \brief GLBCE control structure, passed as an argument to
 *         VPS_ISS_GET_IOCTL_GET_CONFIG/VPS_ISS_GET_IOCTL_SET_CONFIG.
 */
typedef struct vpsissGlbceCtrl
{
    vpsissGlbceModule_t         module;
    /**< Id of the module to be configured,
     *   could be either AF or AEWB configuration
     *   Appropriate structure pointer need to be assigned when one of
     *   these modules is selected here */
    vpsissGlbceConfig_t        *glbceCfg;
    /**< Aewb Configuration Structure */
    vpsissGlbcePerceptConfig_t *fwdPrcptCfg;
    /**< Forward Percept Config Configuration Structure */
    vpsissGlbcePerceptConfig_t *revPrcptCfg;
    /**< Forward Percept Config Configuration Structure */
    vpsissGlbceWdrConfig_t     *wdrCfg;
    /**< WDR Configuration structure */
    vpsissGlbceStatsInfo_t     *statsInfo;
    /**< Stats Informaion */
} vpsissGlbceCtrl_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* _VPS_CFG_GLBCE_H_ */

