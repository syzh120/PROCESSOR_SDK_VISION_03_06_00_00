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
 *  \file vps_cfgldc.h
 *
 *  \brief  Defines the structures / control operations that could be used to
 *              configure / control LDC module
 */

/**
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \defgroup BSP_DRV_VPS_COMMON_CAPTURE_SIMCOP_LDC_ISS LDC Config API
 *
 *  @{
 */

#ifndef VPS_CFG_LDC_H_
#define VPS_CFG_LDC_H_

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
 *  enum vpsissldcMode
 *  \brief Enum to define LDC Mode depending on the dataFormat
 */
typedef enum vpsissldcMode
{
    VPS_ISS_LDC_MODE_YUV422_LDC = 0,
    /**< YCbCr 4:2:2 Lens Distortion Correction */
    VPS_ISS_LDC_MODE_BAYER_CHROMA_ABBERATION = 1,
    /**< Chroma Abberation for bayer format */
    VPS_ISS_LDC_MODE_YUV420_LDC = 2,
    /**< YCbCr 4:2:0 Lens Distortion Correction */
    VPS_ISS_LDC_MODE_FORCE_INT = 0x7FFFFFFF
                    /**< This will ensure enum is not packed, will
                     *      always be contained in int */
} vpsissldcMode_t;  /**< vpsissldcMode_t */

/**
 *  enum vpsissldcBayerDataFormat
 *  \brief Enum to define Bayer DataFormat
 */
typedef enum vpsissldcBayerDataFormat
{
    VPS_ISS_LDC_BAYER_DATA_FORMAT_UNPACKED_12BIT = 0,
    /**< Input/Output data format is 12bit unpacked */
    VPS_ISS_LDC_BAYER_DATA_FORMAT_PACKED_12BIT = 1,
    /**< Input/Output data format is 12bit packed */
    VPS_ISS_LDC_BAYER_DATA_FORMAT_PACKED_8BIT = 2,
    /**< Input/Output data format is 8bit packed */
    VPS_ISS_LDC_BAYER_DATA_FORMAT_ALAW = 3,
    /**< Input/Output data format is ALAW data */
    VPS_ISS_LDC_BAYER_DATA_FORMAT_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed, will
                                 *      always be contained in int */
} vpsissldcBayerDataFormat_t;   /**< vpsissldcBayerDataFormat_t */

/**
 *  enum vpsissldcBayerInitColor
 *  \brief Enum to define first color component for the bayer data
 */
typedef enum vpsissldcBayerInitColor
{
    VPS_ISS_LDC_BAYER_INIT_COLOR_R = 0,
    /**< First color in the bayer data is Red */
    VPS_ISS_LDC_BAYER_INIT_COLOR_GR = 1,
    /**< First color in the bayer data is GreenR */
    VPS_ISS_LDC_BAYER_INIT_COLOR_GB = 2,
    /**< First color in the bayer data is GreenB */
    VPS_ISS_LDC_BAYER_INIT_COLOR_B = 3,
    /**< First color in the bayer data is Blue */
    VPS_ISS_LDC_BAYER_INIT_COLOR_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed, will
                                 *      always be contained in int */
} vpsissldcBayerInitColor_t;    /**< vpsissldcBayerInitColor_t */

/**
 *  enum vpsissldcLumaIntrType
 *  \brief Enum to define Luma interpolation type. For all other components,
 *         i.e. chroma or bayer, bilinear interpolation is used.
 */
typedef enum vpsissldcLumaIntrType
{
    VPS_ISS_LDC_LUMA_INTRP_BICUBIC = 0,
    /**< Bicubic interpolation is used for Luma */
    VPS_ISS_LDC_LUMA_INTRP_BILINEAR = 1,
    /**< Bilinear interpolation is used for Luma */
    VPS_ISS_LDC_LUMA_INTRP_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed, will
                             *      always be contained in int */
} vpsissldcLumaIntrType_t;  /**< vpsissldcLumaIntrType_t */

/**
 *  enum vpsissldcLutDownScFactor
 *  \brief Enum to define down scaling factor for LUT.
 */
typedef enum vpsissldcLutDownScFactor
{
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_1 = 0,
    /**< no downsampling */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_2 = 1,
    /**< Down sampling by 2 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4 = 2,
    /**< Down sampling by 4 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8 = 3,
    /**< Down sampling by 5 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_16 = 4,
    /**< Down sampling by 16 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_32 = 5,
    /**< Down sampling by 32 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_64 = 6,
    /**< Down sampling by 64 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_128 = 7,
    /**< Down sampling by 128 */
    VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed, will
                                 *      always be contained in int */
} vpsissldcLutDownScFactor_t;   /**< vpsissldcLutDownScFactor_t */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct vpsissldcLutCfg
 *  \brief All LUT Parameters.
 */
typedef struct vpsissldcLutCfg
{
    uint32_t                   address;
    /**< Read address for mesh offset table, must be 16 byte aligned */
    uint32_t                   lineOffset;
    /**< LDC Mesh table line offset, must be 16 byte aligned */
    vpsissldcLutDownScFactor_t downScaleFactor;
    /**< Defines the downsampling factors used for the mesh offset tables,
     *   Note that down scaling factor (ISSHAL_LDC_LUT_DOWN_SCALE_FACTOR_1)
     *   is not valid for the RAW capture. */
} vpsissldcLutCfg_t;

/**
 *  struct vpsissldcPerspectiveTransformCfg
 *  \brief Perspective transformation parameters.
 */
typedef struct vpsissldcPerspectiveTransformCfg
{
    uint32_t enableWarp;
    /**< Enable perspective warp transformation,
     *   0: Disables this transformation
     *   1: Enables this transformation
     *   If Disabled, coeffG and coeffH must be set to 0.
     *   For the affine transformation,
     *      set the parameters coeffA, coeffB, coeffC, coeffD, coeffE, coeffF,
     *   To disable affine transformation, set the parameters as below
     *   coeffA = coeffE = 4096, coeffB = coeffC = coeffD = coeffD = 0 */
    uint32_t enableExpandFmt;
    /**< Enables expanded format of affine warp coefficients  A, B, D, E
     *   1: A, B, D, E are treated as S16Q12
     *   0: A, B, D, E are treated as S14Q12 */
    int32_t  coeffA;
    /**< Perspective Transformation Parameter A */
    int32_t  coeffB;
    /**< Perspective Transformation Parameter B */
    int32_t  coeffC;
    /**< Perspective Transformation Parameter C */
    int32_t  coeffD;
    /**< Perspective Transformation Parameter D */
    int32_t  coeffE;
    /**< Perspective Transformation Parameter E */
    int32_t  coeffF;
    /**< Perspective Transformation Parameter F */
    int32_t  coeffG;
    /**< Perspective Transformation Parameter G */
    int32_t  coeffH;
    /**< Perspective Transformation Parameter H */
} vpsissldcPerspectiveTransformCfg_t;

/**
 *  struct vpsissldcAdvConfig_t
 *  \brief Advanced configuration Parameters for LDC.
 */
typedef struct vpsissldcAdvConfig
{
    uint32_t outputBlockWidth;
    /**< Output block width
     *   must be
     *      multiple of 8 in 422 mode
     *      multiple of 16 in 420 mode
     *      multiple of 8 in 12bit unpacked mode
     *      multiple of 32 in 12bit packed mode
     *      multiple of 16 in 8bit packed or ALAW input
     *   depending on the format, must be greater than 8/16/32 */
    uint32_t outputBlockHeight;
    /**< Output block Height
     *   must be even and greater than 0 */
    uint32_t outputFrameWidth;
    /**< Output Frame Width, must be multiple of outBlockWidth
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to input width */
    uint32_t outputFrameHeight;
    /**< Output Frame Height, must be multiple of outBlockHeight
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to input height */
    uint32_t outputStartX;
    /**< Output starting X-coordiinate (must be even)
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to 0 */
    uint32_t outputStartY;
    /**< Output starting Y-coordinate (must be even)
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to 0 */
    uint32_t enableCircAddrMode;
    /**< Flag to enable Circular addressing mode for input data
     *   1: Enables circular addressing mode, need to specify mod parameter
     *   0: Disables circular addressing mode
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to FALSE */
    uint32_t circBuffSize;
    /**< Circular buffer size if circular buffering mode is used.
     *   Specified in terms of number of rows. must be even
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to 0 */

    uint32_t enableConstOutAddr;
    /**< Flag to enable Constant output address mode
     *   Supported in HAL.
     *   Unsupported in driver - will be forced to TRUE */
} vpsissldcAdvConfig_t;
/**
 *  struct vpsissldcCfg
 *  \brief All configuration Parameters for LDC.
 */
typedef struct vpsissldcConfig
{
    vpsissldcMode_t                    mode;
    /**< Mode of the LDC, essentially input data format */
    vpsissldcBayerDataFormat_t         bayerDataFormat;
    /**< Bayer DataFormat,
     *  applicable only when Mode is
     *  ISSHAL_LDC_MODE_BAYER_CHROMA_ABBERATION */
    uint32_t                           enableBackMapping;
    /**< Flag to enable/disable LDC Back Mapping
     *   1: Enables LDC back mapping
     *   0: Disables LDC Back mapping */

    vpsissldcLumaIntrType_t            lumeIntrType;
    /**< Luma Interpolation Type */
    vpsissldcBayerInitColor_t          bayerInitColor;
    /**< First color for the Bayer format */

    uint32_t                           inputFrameWidth;
    /**< width of the input frame */
    uint32_t                           inputFrameHeight;
    /**< height of the input frame */

    vpsissldcPerspectiveTransformCfg_t perspTrnsformCfg;
    /**< Affine transformation parameters */

    vpsissldcLutCfg_t                  lutCfg;
    /**< LDC Lut configuration */

    uint32_t                           pixelPad;
    /**< Pixel pad (must be greater than 1) */

    uint32_t                           isAdvCfgValid;
    /**< Are the advCfg contents valid, if FALSE driver will compute advCfg
     *   internally */

    vpsissldcAdvConfig_t               advCfg;
    /**< LDC advanced configuration - if isAdvCfgValid == FALSE, driver will
     *   compute the advCfg internally */

#if 0
    vpsissldcSmartCodecStatsCfg_t      smartCodecStatsCfg;
    /**< Smart Codec Statistics parameters */
#endif
} vpsissldcConfig_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  vpsissLdcCfg_init
 *  \brief This function should be used to initialize variable of type
 *          #vpsissldcConfig_t.
 *
 *  \param ldcCfg   A pointer of type vpsissldcConfig_t
 *  \return         None
 */
static inline void vpsissLdcCfg_init(vpsissldcConfig_t *ldcCfg);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static inline void vpsissLdcCfg_init(vpsissldcConfig_t *ldcCfg)
{
    if (NULL != ldcCfg)
    {
        ldcCfg->mode = VPS_ISS_LDC_MODE_YUV420_LDC;

        /* NOT USED when mode is VPS_ISS_LDC_MODE_YUV420_LDC */
        ldcCfg->bayerDataFormat = VPS_ISS_LDC_BAYER_DATA_FORMAT_UNPACKED_12BIT;
        /* NOT USED when mode is VPS_ISS_LDC_MODE_YUV420_LDC */
        ldcCfg->bayerInitColor = VPS_ISS_LDC_BAYER_INIT_COLOR_R;

        ldcCfg->enableBackMapping = (uint32_t) TRUE;
        ldcCfg->lumeIntrType      =
            VPS_ISS_LDC_LUMA_INTRP_BICUBIC;
        ldcCfg->inputFrameWidth  = 0; /* NEED NOT be set by USER */
        ldcCfg->inputFrameHeight = 0; /* NEED NOT be set by USER */
        ldcCfg->perspTrnsformCfg.enableWarp      = (uint32_t) FALSE;
        ldcCfg->perspTrnsformCfg.enableExpandFmt = 0;
        ldcCfg->perspTrnsformCfg.coeffA          = 4096U;
        ldcCfg->perspTrnsformCfg.coeffB          = 0;
        ldcCfg->perspTrnsformCfg.coeffC          = 0;
        ldcCfg->perspTrnsformCfg.coeffD          = 0;
        ldcCfg->perspTrnsformCfg.coeffE          = 4096U;
        ldcCfg->perspTrnsformCfg.coeffF          = 0;
        ldcCfg->perspTrnsformCfg.coeffG          = 0;
        ldcCfg->perspTrnsformCfg.coeffH          = 0;
        ldcCfg->lutCfg.address         = 0;
        ldcCfg->lutCfg.lineOffset      = 0;
        ldcCfg->lutCfg.downScaleFactor =
            VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4;
        ldcCfg->pixelPad                 = 2;
        ldcCfg->isAdvCfgValid            = (uint32_t) TRUE;
        ldcCfg->advCfg.outputBlockWidth  = 32;
        ldcCfg->advCfg.outputBlockHeight = 36;
        /* other fields in pPrm->ldcConfig.advCfg , NEED NOT be set by USER */
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* _VPS_CFG_LDC_H_ */

/* @} */
