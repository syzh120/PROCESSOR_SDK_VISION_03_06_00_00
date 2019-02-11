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
 *  \file vps_cfgh3a.h
 *
 *  \brief
 *
 */

#ifndef VPS_CFG_H3A_H_
#define VPS_CFG_H3A_H_

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
 *  \brief Ioctl for getting H3A parameters
 */
#define VPS_ISS_H3A_IOCTL_GET_CONFIG         (VPS_ISS_IOCTL_H3A_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for setting H3A parameters
 */
#define VPS_ISS_H3A_IOCTL_SET_CONFIG         (VPS_ISS_H3A_IOCTL_GET_CONFIG + 1U)

/**
 *  \brief Maximum IIR coefficients
 */
#define VPS_ISS_H3A_AF_IIR_COEFF_MAX     (11U)

/**
 *  \brief Maximum FIR coefficients
 */
#define VPS_ISS_H3A_AF_FIR_COEFF_MAX     (5U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Defines the sub-modules with in H3A. Used to identify sub-module
 *          of interest.
 */
typedef enum vpsissH3aModule
{
    VPS_ISS_H3A_MODULE_AF = 0x0,
    /**< AutoFocus module */
    VPS_ISS_H3A_MODULE_AEWB = 0x1
    /**< Auto Exposure and Auto White Balance Module */
} vpsissH3aModule_t;    /**< vpsissH3aModule_t */

/**
 *  \brief Valid AF modes
 */
typedef enum vpsissH3aMode
{
    VPS_ISS_H3A_MODE_NORMAL = 0x0,
    /**< Normal AF mode */
    VPS_ISS_H3A_MODE_ADVANCED = 0x1
    /**< Advanced AF Mode */
} vpsissH3aMode_t;  /**< vpsissH3aMode_t */

/**
 *  \brief Different layout for RGB in bayer format
 */
typedef enum vpsissH3aAfRgbPos
{
    VPS_ISS_H3A_AF_RGBPOS_GR_GB = 0x0,
    /**< RGB Position 0 */
    VPS_ISS_H3A_AF_RGBPOS_RG_GB = 0x1,
    /**< RGB Position 1 */
    VPS_ISS_H3A_AF_RGBPOS_GR_BG = 0x2,
    /**< RGB Position 2 */
    VPS_ISS_H3A_AF_RGBPOS_RG_BG = 0x3,
    /**< RGB Position 3 */
    VPS_ISS_H3A_AF_RGBPOS_GG_RB = 0x4,
    /**< RGB Position 4 */
    VPS_ISS_H3A_AF_RGBPOS_RB_GG = 0x5
    /**< RGB Position 5 */
} vpsissH3aAfRgbPos_t;  /**< vpsissH3aAfRgbPos_t */

/**
 *  \brief Valid the AF FV mode
 */
typedef enum vpsissH3aAfFvMode
{
    VPS_ISS_H3A_AF_FV_MODE_SUM = 0x0,
    /**< FV Accumulation mode is sum mode */
    VPS_ISS_H3A_AF_FV_MODE_PEAK = 0x1
    /**< FV Accumulation mode is Peak mode */
} vpsissH3aAfFvMode_t;  /**< vpsissH3aAfFvMode_t */

/**
 *  \brief Valid AF Vf modes
 */
typedef enum vpsissH3aAfVfMode
{
    VPS_ISS_H3A_AF_VF_HORZ_ONLY = 0x0,
    /**< Vertical Focus mode is 4 color horizontal FV Only */
    VPS_ISS_H3A_AF_VF_VERT_HORZ = 0x1
    /**< Vertical Focus mode is 1 color horizontal and 1 color vertical */
} vpsissH3aAfVfMode_t;  /**< vpsissH3aAfVfMode_t */

/**
 *  \brief  Valid output modes
 */
typedef enum vpsissH3aOutputMode
{
    VPS_ISS_H3A_OUTPUT_MODE_SUM_SQR = 0x0,
    /**< Output format is sum of square */
    VPS_ISS_H3A_OUTPUT_MOPE_MIN_MAX = 0x1,
    /**< Output format is Min and Max Value */
    VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY = 0x2
    /**< Output format is sum only */
} vpsissH3aOutputMode_t;    /**< vpsissH3aOutputMode_t */

/**
 *  \brief Structure containing IIR Filter configuration
 */
typedef struct vpsissH3aAfIirFiltConfig
{
    int32_t coeff[VPS_ISS_H3A_AF_IIR_COEFF_MAX];
    /**< IIR filter coefficients */
    uint32_t threshold;
    /**< Threshold of the filter */
} vpsissH3aAfIirFiltConfig_t;

/**
 *  \brief Structure containing FIR Filter configuration
 */
typedef struct vpsissH3aAfFirFilrConfig
{
    int32_t coeff[VPS_ISS_H3A_AF_FIR_COEFF_MAX];
    /**< FIR filter coefficients */
    uint32_t threshold;
    /**< Threshold of the filter */
} vpsissH3aAfFirFilrConfig_t;

/**
 *  \brief Paxel configuration control structure
 */
typedef struct vpsissH3aPaxelConfig
{
    Fvid2_PosConfig pos;
    /**< Paxel/Window start Position
         For AF,
            Start horizontal position must be iirFiltStartPos + 2 and must be even
            Start vertical position must be greater than 8 if vertical mode is enabled,
            range is 0-4095
         For AEWB,
            Start horizontal position must be in 0-4095
            Start vertical position must be 0-4095 */
    uint32_t        width;
    /**< Width of the paxel,
         minimum width required is 8 pixels */
    uint32_t        height;
    /**< Height of the paxel
         The height could be from 2 to 256 */
    uint32_t        horzCount;
    /**< Horizontal paxel count,
         Valid value is from 2 to 36 */
    uint32_t        vertCount;
    /**< Vertical Paxel count,
         Maximum value supported is 128 */
    uint32_t        horzIncr;
    /**< Horizontal increment,
         The Range is from 2 to 32 */
    uint32_t        vertIncr;
    /**< Vertical increment,
         The range is from 2 to 32 */
} vpsissH3aPaxelConfig_t;

/**
 * \brief Structure for ISP H3A AF engine parameters.
 */
typedef struct vpsissH3aAfConfig
{
    uint32_t                   enableALowCompr;
    /**< Flag to enable A Low Compression */

    uint32_t                   enableMedFilt;
    /**< Flag to enable/disable Medial Filter,
            to reduce Temperature Induced Noise */
    uint32_t                   midFiltThreshold;
    /**< Median Filter Threshold */

    vpsissH3aAfRgbPos_t        rgbPos;
    /**< RGB layout in bayer format */

    vpsissH3aPaxelConfig_t     paxelCfg;
    /**< Paxel configuration */

    vpsissH3aAfFvMode_t        fvMode;
    /**< Defines type of accumulation for FV to be done */

    vpsissH3aAfVfMode_t        vfMode;
    /**< Vertical Focus Mode */

    vpsissH3aAfIirFiltConfig_t iirCfg1;
    /**< IIR parameters */
    vpsissH3aAfIirFiltConfig_t iirCfg2;
    /**< IIR parameters */
    vpsissH3aAfFirFilrConfig_t firCfg1;
    /**< FiR Filter configuration */
    vpsissH3aAfFirFilrConfig_t firCfg2;
    /**< FiR Filter configuration */

    uint32_t                   iirFiltStartPos;
    /**< IIR filter start position */

    vpsissH3aMode_t            mode;
    /**< AF Mode */
} vpsissH3aAfConfig_t;

/**
 * \brief Structure for ISP H3A AEWB engine parameters.
 */
typedef struct vpsissH3aAewbConfig
{
    uint32_t               enableALowComp;
    /**< Flag to enable A Low Compression */

    uint32_t               enableMedFilt;
    /**< Flag to enable/disable Medial Filter, to reduce
         Temperature Induced Noise */
    uint32_t               midFiltThreshold;
    /**< Median Filter Threshold */

    vpsissH3aPaxelConfig_t winCfg;
    /**< Paxel configuration */

    UInt32                 blackLineVertStart;
    /**< Vertical Window Start Position for single black line of windows.
         Sets the first line for the single black line of windows */
    UInt32                 blackLineHeight;
    /**< Window Height for the single black line of windows.
         This specifies the window height in an even number of pixels */

    vpsissH3aOutputMode_t  outMode;
    /**< Output Mode */

    uint32_t               sumShift;
    /**< AE/AWB engine shift value for the accumulation of pixel values
         This bit field sets the right shift value which is applied on
         the result of the pixel accumulation before it is stored in
         the packet. The accumulation takes place on 26 bits
         which is enough for 10-bit data and a maximum widow
         size of 512 x 512 which results into the accumulation of
         256 x 256 pixels of the same color. The shift value must
         be set such that the result fits on 16 bits. */

    uint32_t               satLimit;
    /**< Saturation Limit, This is the value that all sub sampled pixels in the
         AE/AWB engine are compared to. If the data is greater or
         equal to this data then the block is considered saturated. */

    vpsissH3aMode_t        mode;
    /**< AEWB Mode */
} vpsissH3aAewbConfig_t;

/**
 *  \brief H3A control structure, passed as an argument to
 *         VPS_ISS_GET_IOCTL_GET_CONFIG/VPS_ISS_GET_IOCTL_SET_CONFIG.
 */
typedef struct vpsissH3aCtrl
{
    vpsissH3aModule_t      module;
    /**< Id of the module to be configured,
         could be either AF or AEWB configuration
         Appropriate structure pointer need to be assigned when one of
         these modules is selected here */
    vpsissH3aAewbConfig_t *aewbCfg;
    /**< Aewb Configuration Structure */
    vpsissH3aAfConfig_t   *afCfg;
    /**< AF Configuration Structure */
} vpsissH3aCtrl_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_CFG_H3A_H_ */

