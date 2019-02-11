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
 *  \file vps_cfgrsz.h
 *
 *  \brief
 *
 */

#ifndef VPS_CFG_RSZ_H_
#define VPS_CFG_RSZ_H_

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
 *  \brief Ioctl for getting Resizer parameters
 */
#define VPS_ISS_RSZ_IOCTL_GET_CONFIG         (VPS_ISS_IOCTL_RSZ_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for setting Resizer parameters
 */
#define VPS_ISS_RSZ_IOCTL_SET_CONFIG         (VPS_ISS_RSZ_IOCTL_GET_CONFIG + 1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Valid sub configurations of RSZ
 */
typedef enum vpsissRszModule
{
    VPS_ISS_RSZ_MODULE_RSZCFG = 0x0,
    /**< Module id for setting the Resizer configuration */
    VPS_ISS_RSZ_MODULE_FLIPCFG = 0x1
                        /**< Module Id for setting flip configuration for
                         *resizer */
} vpsissRszModule_t;    /**< vpsissRszModule_t */

/**
 *  \brief Enum to define Resizer Instance ie resizer outputs.
 *         Caution: values of these enum are used as array index
 */
typedef enum vpsissRszScalerInstId
{
    VPS_ISS_RSZ_SCALER_A = 0x0,
    /**< Rescalar A in the RSZ module */
    VPS_ISS_RSZ_SCALER_B = 0x1,
    /**< Rescalar B in the RSZ module */
    VPS_ISS_RSZ_SCALER_MAX = 0x2
                            /**< Should the last num, used as array size */
} vpsissRszScalerInstId_t;  /**< vpsissRszScalerInstId_t */

/**
 *  \brief Enum for Resizer operating modes
 */
typedef enum vpsissRszOpMode
{
    VPS_ISS_RSZ_OP_MODE_BYPASS = 0x0,
    /**< Resizer bypass mode */
    VPS_ISS_RSZ_OP_MODE_PASSTHRU = 0x1,
    /**< Resizer Pass Thru mode */
    VPS_ISS_RSZ_OP_MODE_RESIZING = 0x2
                        /**< Resizing mode */
} vpsissRszOpMode_t;    /**< vpsissRszOpMode_t */

/**
 *  \brief Enum for Selecting Filter type
 */
typedef enum vpsissRszFilterType
{
    VPS_ISS_RSZ_FILTER_4TAP_CUBIC = 0x0,
    /**< 4 Tap Cubic Convolution algorithm for vertical resizing */
    VPS_ISS_RSZ_FILTER_2TAP_LINEAR = 0x1
                            /**< 2 Tap Linear Interpolation algorithm for
                             *vertical resizing */
} vpsissRszFilterType_t;    /**< vpsissRszFilterType_t */

/**
 *  \brief Enum for Scaling mode, it can be either normal in which
 *         it supports 1/16x to 16x or downscale mode in which allows
 *         scaling factor from 1/4096x to 1x.
 */
typedef enum vpsissRszScaleMode
{
    VPS_ISS_RSZ_SCALE_MODE_NORMAL = 0x0,
    /**< Normal Scaling mode in which up and down scaling is allowed */
    VPS_ISS_RSZ_SCALE_MODE_DOWNSCALE = 0x1
                        /**< Down scaling mode. Not yet supported, please do not
                         *use TODO */
} vpsissRszScaleMode_t; /**< vpsissRszScaleMode_t */

/**
 *  \brief Enum for selecting flip mode
 */
typedef enum vpsissRszFlipCtrl
{
    VPS_ISS_RSZ_STR_MODE_NORMAL = 0x0,
    /**< Normal Storage Mode */
    VPS_ISS_RSZ_STR_MODE_HFLIP = 0x1,
    /**< Output is fliped in horizontal direction */
    VPS_ISS_RSZ_STR_MODE_VFLIP = 0x2,
    /**< Output is fliped in vertical direction */
    VPS_ISS_RSZ_STR_MODE_HFLIP_VFLIP = 0x3
                        /**< Output is fliped in horizontal and vertical
                         *direction */
} vpsissRszFlipCtrl_t;  /**< vpsissRszFlipCtrl_t */

/**
 *  \brief Enum for YUV mode of resizing
 */
typedef enum vpsissRszYuvResizeMode
{
    VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_ONLY = 0x0,
    /**< Luma only mode */
    VPS_ISS_RSZ_YUV_RSZ_MODE_CHROMA_ONLY = 0x1,
    /**< Chroma only mode */
    VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_AND_CHROMA = 0x2
                             /**< Luma and Chroma both mode */
} vpsissRszYuvResizeMode_t;  /**< vpsissRszYuvResizeMode_t */
/**
 *  \brief Control structure used the define the operation mode and
 *          select region of frame to be processed.
 */
typedef struct vpsissRszInputConfig
{
    vpsissRszOpMode_t opMode;
    /**< Resizer Operation Mode, can be bypass, pass through or resizing
     *   resizing mode is supported only for the YUV input format.
     *   For the Raw input, it should be be either bypassed or set to pass
     *      through mode,
     *   For YUV input, it can either enabled or bypassed or set to pass
     *      through mode */
    Fvid2_CropConfig  procWin;
    /**< Window to be processed, RSZ module crops input image to this
     *   size and uses this size for all its processing */

    uint32_t          overrideInCfg;
    /**< Input configuration is set by the driver based in
     *   the SET_PARAMS ioctl,
     *   this flag is used to override input configuration and set the input
     *   configuration provided in this structure
     *   Currently it is only used to change input data format */
    Fvid2_DataFormat  inDataFormat;
    /**< Override input data format to this one */
} vpsissRszInputConfig_t;

/**
 *  \brief Control structure used choose different filter
 */
typedef struct vpsissRszFiltConfig
{
    vpsissRszFilterType_t horzLumaFilter;
    /**< Type of filter for luma on horizontal direction */
    vpsissRszFilterType_t horzChromaFilter;
    /**< Type of filter for chroma on horizontal direction */
    vpsissRszFilterType_t vertLumaFilter;
    /**< Type of filter for luma on vertical direction */
    vpsissRszFilterType_t vertChromaFilter;
    /**< Type of filter for chroma on vertical direction */
} vpsissRszFiltConfig_t;

/**
 *  \brief Control structure used set different intensity
 */
typedef struct vpsissRszIntsConfig
{
    uint32_t horzLumaIntensity;
    /**< Horizontal Scalar Luma Intensity */
    uint32_t horzChromaIntensity;
    /**< Horizontal Scalar Chroma Intensity */
    uint32_t vertLumaIntensity;
    /**< Vertical Scalar Luma Intensity */
    uint32_t vertChromaIntensity;
    /**< Vertical Scalar Chroma Intensity */
} vpsissRszIntsConfig_t;

/**
 *  \brief Resizer instance configuration, there are two resizer instances
 *         RSA and RSB, both can be independently resize the input and provide
 *         independent output. This structure contains instance
 *         specific configuration like output dataformat,
 *         horizonta/vertical scaling factor etc.
 */
typedef struct vpsissRszInstConfig
{
    uint32_t                 enable;
    /**< Flag to indicate whether this instanc of the resizer is
     *   enabled or not
     *   TRUE, Instance is enabled and its configuration will be applied
     *   FALSE, instance is not enabled, configuration will not be applied */
    Fvid2_Format             outFmt;
    /**< Output Format from this Resizer instance,
     *   Only width/height and dataFormat variables are used,
     *   Resizer supports only below dataFormats
     *      FVID2_DF_BAYER_RAW,
     *      FVID2_DF_YUV422I_YUYV
     *      FVID2_DF_YUV420SP_UV,
     *      FVID2_DF_RGB16_565,
     *      FVID2_DF_ARGB32_8888
     */
    vpsissRszFlipCtrl_t      flipCtrl;
    /**< Used to flip the output in horizontal and/or vertical direction */

    Fvid2_PosConfig          startPos;
    /**< Starting position of the Input image, this is in addition to the
     *   start position specified in the crop size */

    vpsissRszScaleMode_t     scaleMode;
    /**< Rescaled Mode, could be either Normal or Downscale mode */

    vpsissRszFiltConfig_t    filtCfg;
    /**< Structure containing Filter configuration for luma and chroma on
     *   horizontal and vertical side */

    vpsissRszIntsConfig_t    intensityCfg;
    /**< Structure containing intensity configuration for luma and chroma on
     *   horizontal and vertical side */

    uint32_t                 alpha;
    /**< Alpha Value used for the ARGB output Format,
     *   only lsb 8bits are valid */

    vpsissRszYuvResizeMode_t yuvRszMode;
    /**< Resizer mode for the YUV data,
     *   Used only when overrideInCfg flag of #vpsissRszInputConfig_t is set.
     *   Used to select luma only, chroma only or both luma and
     *   chroma output. */

    uint32_t                 overrideScaleFactor;
    /**< Flag to use user provided scaling factor instead of
         calculating them */
    uint32_t                 hRatio;
    /**< Horizontal Scaling ration, used only when overrideScaleFactor = TRUE */
    uint32_t                 vRatio;
    /**< Vertical Scaling ration, used only when overrideScaleFactor = TRUE */
} vpsissRszInstConfig_t;

/**
 *  \brief Resizer control structure, passed as an argument to
 *         VPS_ISS_IPIPE_IOCTL_CTRL.
 */
typedef struct vpsissRszCfg
{
    vpsissRszInputConfig_t inCfg;
    /**< Resizer input configuration,
     *   Used to set input processing window and resizer operational mode,
     *   horizontal and vertical scaling factor is calculated based on
     *   the output of the crop window
     *   Whenever, there is a change in cropCfg, scaling factor and other
     *   parameters are recalculated and set again. */
    vpsissRszInstConfig_t  instCfg[VPS_ISS_RSZ_SCALER_MAX];
    /**< Pointer to Instance Configuration */
} vpsissRszCfg_t;

/**
 *  \brief Control structure used configure resizer
 */
typedef struct vpsissRszCtrl
{
    vpsissRszModule_t module;
    /**< Id of the module to be configured,
     *   could be either Input, ResizerA or ResizerB
     *   Appropriate structure pointer need to be assigned when one of
     *   these modules is selected here */
    vpsissRszCfg_t   *rszCfg;
    /**< Pointer to resizer config */
} vpsissRszCtrl_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_CFG_RSZ_H_ */

