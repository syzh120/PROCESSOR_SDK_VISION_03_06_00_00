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
 *  \file vps_cfgnsf3.h
 *
 *  \brief
 *
 */

#ifndef VPS_CFG_NSF3_H_
#define VPS_CFG_NSF3_H_

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
 *  \brief Ioctl for getting nsf3 parameters
 */
#define VPS_ISS_NSF3_IOCTL_GET_CONFIG       (VPS_ISS_IOCTL_NSF3_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for getting nsf3 parameters
 */
#define VPS_ISS_NSF3_IOCTL_SET_CONFIG       (VPS_ISS_NSF3_IOCTL_GET_CONFIG + 1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Maximm Color Component
 */
#define VPS_ISS_NSF3_MAX_COLOR                          (4U)

/**
 *  \brief Maximum number of NSF Threshold
 */
#define VPS_ISS_NSF3_MAX_NSF_THRESHOLD                  (4U)

/**
 *  \brief Maximum number of knee points
 */
#define VPS_ISS_NSF3_MAX_KNEE_POINTS                    (3U)

/**
 *  \brief Maximum number of Edge Enhancement level
 */
#define VPS_ISS_NSF3_EE_MAX_LEVEL                       (3U)

/**
 *  \brief Maximum number of Supression level
 */
#define VPS_ISS_NSF3_SUPPRESSION_MAX_LEVEL              (3U)

/**
 *  \brief Maximum number of HA/VA Coefficients
 */
#define VPS_ISS_NSF3_SHADE_GAIN_MAX_COEFF               (2U)

/**
 *  \brief NSF3 maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define VPS_ISS_NSF3_MAX_INST                           (1U)

/**
 *  \brief Enum for defining NSF3 operation mode.
 */
typedef enum vpsissNsf3OpMode
{
    VPS_ISS_NSF3_OP_MODE_BAYER = 0x0,
    /**< Bayer */
    VPS_ISS_NSF3_OP_MODE_BAYER_2x2 = 0x1,
    /**< Bayer interleaved 2x2 */
    VPS_ISS_NSF3_OP_MODE_BAYER_3x3 = 0x2,
    /**< Bayer interleaved 3x3 */
    VPS_ISS_NSF3_OP_MODE_YUV422 = 0x3,
    /**< YUV422 */
    VPS_ISS_NSF3_OP_MODE_YUV420_LUMA = 0x4,
    /**< YUV420 Y plane */
    VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA = 0x5,
    /**< YUV420 UV plane */
    VPS_ISS_NSF3_OP_MODE_YUV422_INTLD = 0x6,
    /**< YUV422 Interleaved */
    VPS_ISS_NSF3_OP_MODE_YUV420_LUMA_INTLD = 0x7,
    /**< YUV420 Y interleaved */
    VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA_INTLD = 0x8,
    /**< YUV420 UV interleaved */
    VPS_ISS_NSF3_MAX_OP_MODE = 0x9
                        /**< Should be the last Enum */
} vpsissNsf3OpMode_t;   /**< vpsissNsf3OpMode_t */

/**
 *  \brief Struct for Noise Threshold Configuration.
 */
typedef struct vpsissNsf3NoiseThrshldConfig
{
    uint32_t horzPos[VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_MAX_NSF_THRESHOLD];
    /**< Segments X Coordinates in U11 Format
         For the segment-0, it is fixed to 0, so cannot be changed */
    uint32_t vertPos[VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_MAX_NSF_THRESHOLD];
    /**< Segments Y Coordinates in U12 format */
    uint32_t slope[VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_MAX_NSF_THRESHOLD];
    /**< Segment Slope in S3.11 format */
    uint32_t scaleFactorTn1;
    /**< Scaling factor to get TN3, noise threshold for level 3 subbands */
    uint32_t scaleFactorTn3;
    /**< Scaling factor to get TN1, noise threshold for level 1 subbands */
    uint32_t kneePoint[VPS_ISS_NSF3_MAX_KNEE_POINTS];
    /**< Knee Points */
} vpsissNsf3NoiseThrshldConfig_t;

/**
 *  \brief Struct for Edge Enhancement Configuration.
 */
typedef struct vpsissNsf3EdgeEnhnceConfig
{
    uint32_t enable;
    /**< Flag to enable/disable Edge Enhancement */
    uint32_t hhSubbandMax[VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_EE_MAX_LEVEL];
    /**< HH suband ee_max */
    uint32_t lhSubbandMax[VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_EE_MAX_LEVEL];
    /**< LH and HL subband ee_max */
    uint32_t deSaturateThreshold1;
    /**< De Saturation Thresold 1 */
    uint32_t deSaturateThreshold2;
    /**< De Saturation Thresold 2 */
    uint32_t deSaturateSlope1;
    /**< De Saturation Slope 1 */
    uint32_t deSaturateSlope2;
    /**< De Saturation Slope 2 */
} vpsissNsf3EdgeEnhnceConfig_t;

/**
 *  \brief Struct for Shading Gain Configuration.
 */
typedef struct vpsissNsf3ShadeGainConfig
{
    uint32_t        enable;
    /**< Flag to enable/disable Shading Gain */

    Fvid2_PosConfig pos;
    /**< Starting position for the Shading Gain */

    uint32_t        haCoeff[VPS_ISS_NSF3_SHADE_GAIN_MAX_COEFF];
    /**< Shading Gain HA Coefficients */
    uint32_t        vaCoeff[VPS_ISS_NSF3_SHADE_GAIN_MAX_COEFF];
    /**< Shading Gain VA Coefficients */

    uint32_t        s0ShiftCnt;
    /**< shading gain S0 shift count */
    uint32_t        hs1ShiftCnt;
    /**< shading gain HS1 shift count */
    uint32_t        hs2BitCnt;
    /**< shading gain HS2 bit count */
    uint32_t        hscShiftCnt;
    /**< shading gain HCS shift count, Valid values are 1 and 2 */
    uint32_t        vs1BitCnt;
    /**< shading gain VS1 bit count */
    uint32_t        vs2ShiftCnt;
    /**< shading gain VS2 shift count */
    uint32_t        vcsShiftCnt;
    /**< Vshading gain VCS shift count, Valid values are 1 and 2 */

    uint32_t        OfstAdj;
    /**< shading gain offset adjustment */
    uint32_t        adj;
    /**< shading gain gain adjustment */
    uint32_t        maxShadGain;
    /**< Maximum Shading Gain */
} vpsissNsf3ShadeGainConfig_t;

/**
 *  \brief Configuration parameters of NSF3.
 */
typedef struct vpsissNsf3Config
{
    uint32_t                       bypass;
    /**< Bypass all processing, so that output = input, but maintain
         the same latency */

    vpsissNsf3OpMode_t             opMode;
    /**< Mode of Operations, depends on input data type */

    uint32_t                       enableBorderReplicate;
    /**< enables/Disables replication of border lines and pixels so that
         top and bottom 7 lines and left and right 8 pixels are not lost */

    uint32_t                       enableChromaDeSatur;
    /**< Enables/Disables Chroma DeSaturation */

    vpsissNsf3NoiseThrshldConfig_t nsCfg;
    /**< Noise Threshold Configuration */

    uint32_t                       hhSubbandMax
    [VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_SUPPRESSION_MAX_LEVEL];
    /**< HH subband suppression max */
    uint32_t                       lhSubbandMax
    [VPS_ISS_NSF3_MAX_COLOR]
    [VPS_ISS_NSF3_SUPPRESSION_MAX_LEVEL];
    /**< LH and HL subband suppression max */

    vpsissNsf3EdgeEnhnceConfig_t   eeCfg;
    /**< Edge Enhancement Configuration */
    vpsissNsf3ShadeGainConfig_t    sgCfg;
    /**< Shading Gain Configuration */
} vpsissNsf3Config_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_CFG_NSF3_H_ */

