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
 *  \file vps_cfgipipe.h
 *
 *  \brief
 *
 */

#ifndef VPS_CFG_IPIPE_H_
#define VPS_CFG_IPIPE_H_

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
 *  \brief IPIPE number of the CSC coefficients.
 */
#define VPS_ISS_IPIPE_CSC_NUM_COEFF        (3U)

/**
 *  \brief Ioctl for setting IPIPE parameters
 */
#define VPS_ISS_IPIPE_IOCTL_GET_CONFIG     (VPS_ISS_IOCTL_IPIPE_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for getting IPIPE parameters
 */
#define VPS_ISS_IPIPE_IOCTL_SET_CONFIG     (VPS_ISS_IPIPE_IOCTL_GET_CONFIG + 1U)

/**
 *  \brief For 3D Lut, the ip LUT format is different. It does not
 *         use Red, Green and Blue directly. Instead, ip requires them
 *         to be merged in different way and then they can be used. This
 *         ioctl is used for converting LUT format.
 */
#define VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT (VPS_ISS_IPIPE_IOCTL_GET_CONFIG + 2U)

/**
 *  \brief Max Multiplication coefficients in Edge Enhancer
 */
#define VPS_ISS_IPIPE_YEE_MAX_HPF_COEFF     (9U)

/**
 *  \brief Maximum number of thresholds for NF2
 */
#define VPS_ISS_IPIPE_NF2_MAX_THR           (8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  enum vpsissIpipeModule
 *  \brief IPIPE submodules, this is used for setting or getting configuration
 *         for this module.
 */
typedef enum vpsissIpipeModule
{
    VPS_ISS_IPIPE_MODULE_INPUT = 0x0,
    /**< CFA Input configuration */
    VPS_ISS_IPIPE_MODULE_CFA = 0x1,
    /**< CFA Sub-Module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_WB = 0x2,
    /**< White balance sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_RGB2RGB1 = 0x3,
    /**< RGB2RGB sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_RGB2RGB2 = 0x4,
    /**< RGB2RGB sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_RGB2YUV = 0x5,
    /**< RGB2RGB sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_YUV444_YUV422 = 0x6,
    /**< YUV422 to YUV422 sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_DPC_LUT = 0x7,
    /**< LUT based DPC sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_DPC_OTF = 0x8,
    /**< OnTheFly DPC sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION = 0x9,
    /**< Gamma Correction sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_3D_LUT = 0xa,
    /**< 3D LUT sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER = 0xb,
    /**< 3D LUT sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_GIC = 0xc,
    /**< GIC (Green Imbalance Correction) sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_LSC = 0xd,
    /**< GIC (Green Imbalance Correction) sub-module of the IPIPE */
    VPS_ISS_IPIPE_MODULE_NF1 = 0xe,
    /**< Noise Filter 1 */
    VPS_ISS_IPIPE_MODULE_NF2 = 0xf
    /**< Noise Filter 2 */
} vpsissIpipeModule_t;  /**< vpsissIpipeModule_t */

/**
 *  enum vpsissIpipeSelDataPath
 *  \brief Valid data path within IPIPE
 */
typedef enum vpsissIpipeSelDataPath
{
    VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422 = 0x0,
    /**< input data is in RAW BAYER format and output data format YUV422 */
    VPS_ISS_IPIPE_DATA_PATH_RAW_RAW = 0x1,
    /**< The data are output after the White Balance module. It
     *   enables to bypass a large part of the IPIPE module */
    VPS_ISS_IPIPE_DATA_PATH_RAW_DISABLED = 0x2,
    /**< input data is in RAW BAYER format and output is disabled */
    VPS_ISS_IPIPE_DATA_PATH_YUV422_YUV422 = 0x3
    /**< input data and output data formats are in YUV422 format */
} vpsissIpipeSelDataPath_t; /**< vpsissIpipeSelDataPath_t */

/**
 *  enum vpsissIpipeCfaMode
 *  \brief Valid CFA Modes. Used for selecting algorithm for CFA and
 *         to select Digital anti-aliasing filter
 */
typedef enum vpsissIpipeCfaMode
{
    VPS_ISS_IPIPE_CFA_MODE_2DIRAC = 0,
    /**< CFA Mode is 2DirAC */
    VPS_ISS_IPIPE_CFA_MODE_2DIRAC_DAA = 1,
    /**< CFA Mode is 2DirAC plus Digital Antialiasing */
    VPS_ISS_IPIPE_CFA_MODE_DAA = 2,
    /**< CFA Mode is Digital Antialiasing */
    VPS_ISS_IPIPE_CFA_MODE_COSITED = 3
    /**< CFA Mode is Co-Sited bayer format, the sampling points of R/Gr/Gb/B
            in each 2x2 block is at the same position. In this mode, the CFA
            interpolator simply copies R, G, and B to all points in
            the 2x2 block. (G is an average of Gb and Gr.)  */
} vpsissIpipeCfaMode_t; /**< vpsissIpipeCfaMode_t */

/**
 *  enum vpsissIpipeDpcOtfModes
 *  \brief On the FLY DPC valid methods
 */
typedef enum vpsissIpipeDpcOtfModes
{
    VPS_ISS_IPIPE_DPC_OTF_METHOD_MIN = 0,
    /**< Adaptive OTF DPC - Min Guard */
    VPS_ISS_IPIPE_DPC_OTF_METHOD_1,
    /**< Adaptive OTF DPC - Method 1, refer spec for details */
    VPS_ISS_IPIPE_DPC_OTF_METHOD_2,
    /**< Adaptive OTF DPC - Method 2, refer spec for details */
    VPS_ISS_IPIPE_DPC_OTF_METHOD_3,
    /**< Adaptive OTF DPC - Method 3, refer spec for details */
    VPS_ISS_IPIPE_DPC_OTF_METHOD_MAX
    /**< Adaptive OTF DPC - Max Guard */
} vpsissIpipeDpcOtfModes_t; /**< vpsissIpipeDpcOtfModes_t */

/**
 *  enum vpsissIpipeGammaTblSize
 *  \brief Valid Gamma Correction Table size
 *         Used only when ROM Table is used
 */
typedef enum vpsissIpipeGammaTblSize
{
    VPS_ISS_IPIPE_GAMMA_TBL_SIZE_64 = 0,
    /**< Gamma Table size is 64 words */
    VPS_ISS_IPIPE_GAMMA_TBL_SIZE_128 = 1,
    /**< Gamma Table size is 128 words */
    VPS_ISS_IPIPE_GAMMA_TBL_SIZE_256 = 2,
    /**< Gamma Table size is 256 words */
    VPS_ISS_IPIPE_GAMMA_TBL_SIZE_512 = 3,
    /**< Gamma Table size is 64 words */
    VPS_ISS_IPIPE_GAMMA_MAX_TBL_SIZE = 4
    /**< Max Table Size, Used only for error checking */
} vpsissIpipeGammaTblSize_t;    /**< vpsissIpipeGammaTblSize_t */

/**
 *  enum vpsissIpipeGammaTbl
 *  \brief Enum for selecting the Gamma Table either ROM or RAM based
 */
typedef enum vpsissIpipeGammaTbl
{
    VPS_ISS_IPIPE_GAMMA_TBL_RAM = 0,
    /**< RAM Based Gamma Table is used */
    VPS_ISS_IPIPE_GAMMA_TBL_ROM = 1
    /**< ROM Based Gamma Table is used */
} vpsissIpipeGammaTbl_t;    /**< vpsissIpipeGammaTbl_t */

/**
 *  enum vpssissIpipeEeMergeMethod
 *  \brief Enum for selecting Edge Enhancer merge method
 */
typedef enum vpssissIpipeEeMergeMethod
{
    VPS_ISS_IPIPE_EE_MERGE_METHOD_SUM = 0,
    /**< The merge method for Edge Enhanced and Sharpener is Max of both */
    VPS_ISS_IPIPE_EE_MERGE_METHOD_MAX = 1
    /**< The merge method for Edge Enhanced and Sharpener is Sum of both */
} vpssissIpipeEeMergeMethod_t;  /**< vpssissIpipeEeMergeMethod_t */

/**
 *  enum vpsissIpipeGicAlgoType
 *  \brief Enum for selecting GIC algorith type, could be either
 *         simple averaging or adaptive
 */
typedef enum vpsissIpipeGicAlgoType
{
    VPS_ISS_IPIPE_GIC_ALG_TYPE_AVERAGE = 0,
    /**< GIC Algorithm is simple Averaging algorithm */
    VPS_ISS_IPIPE_GIC_ALG_TYPE_ADAPT
    /**< GIC Algorithm is Adaptive */
} vpsissIpipeGicAlgoType_t; /**< vpsissIpipeGicAlgoType_t */

/**
 *  enum vpsissIpipeGicThresholdSel
 *  \brief Enum for GIC threshold, could be either from GIC register
 *         itself or from NF2
 */
typedef enum vpsissIpipeGicThresholdSel
{
    VPS_ISS_IPIPE_GIC_THR_SEL_GIC_REG = 0,
    /**< Use GIC register for the threshold */
    VPS_ISS_IPIPE_GIC_THR_SEL_NF2
    /**< Use Threshold from NF2 registes */
} vpsissIpipeGicThresholdSel_t; /**< vpsissIpipeGicThresholdSel_t */

/**
 *  enum vpsissIpipeNf2GreenPixType
 *  \brief Enum defining sampling format for the green pixel
 */
typedef enum vpsissIpipeNf2GreenPixType
{
    VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX = 0,
    /**< Green pixel sampling format is Box, same as Red/Blue */
    VPS_ISS_IPIPE_NF2_GREEN_TYPE_DIAMOND
    /**< Green pixel sampling format is diamond */
} vpsissIpipeNf2GreenPixType_t; /**< vpsissIpipeNf2GreenPixType_t */

/**
 *  struct vpsissIpipeInConfig
 *  \brief IPIPE Input configuration, used to select input frame
 *         window and ipipe internal data path
 */
typedef struct vpsissIpipeInConfig
{
    vpsissIpipeSelDataPath_t dataPath;
    /**< IPIPE Internal data path */
    Fvid2_CropConfig         procWin;
    /**< IPIPE Processing Window size */
} vpsissIpipeInConfig_t;

/**
 *  struct vpsissIpipeNf2Config
 *  \brief Noise Filter Configuration
 */
typedef struct vpsissIpipeNf2Config
{
    uint32_t                     enable;
    /**< Flag to enable/disable NF2 */
    vpsissIpipeNf2GreenPixType_t grPixType;
    /**< Green pixel sampling type */
    uint32_t                     enableLscGain;
    /**< Flag to enable/disable LSC gain to threshold value */
    uint32_t                     useLutSpr;
    /**< Flag to use Lut based SPR, spread factor
     *   TRUE: Use Lut based Spread factor
     *   FALSE: Use Single Spread factor */
    uint32_t                     downShift;
    /**< Down Shift value for look up table reference */
    uint32_t                     spreadVal;
    /**< Spread Value used when useLutSpr is set to false */
    uint32_t                     threshold[VPS_ISS_IPIPE_NF2_MAX_THR];
    /**< Threshold table, used in filtering algorithm */
    uint32_t                     intensity[VPS_ISS_IPIPE_NF2_MAX_THR];
    /**< Intensity table */
    uint32_t                     sprFactor[VPS_ISS_IPIPE_NF2_MAX_THR];
    /**< Spread Factor table */
    uint32_t                     edgeMin;
    /**< Edge Detectio min */
    uint32_t                     edgeMax;
    /**< Edge Detectio max */
} vpsissIpipeNf2Config_t;

/**
 *  struct vpsissIpipeCfgDaaCfg
 *  \brief Digital Anti aliasing configuration. Used along with CFA to reduce
 *         aliasing caused by undersampling.
 */
typedef struct vpsissIpipeCfgDaaCfg
{
    uint32_t hueFraction;
    /**< Mono Hue Fraction */
    uint32_t edgeThreshold;
    /**< Edge of Threshold */
    uint32_t minThreshold;
    /**< Minimum Threshold */
    uint32_t slopeThreshold;
    /**< Slope Threshold */
    uint32_t slopeMin;
    /**< SLP MIN */
    uint32_t slopeSlope;
    /**< SLP Slope */
    uint32_t lpWeight;
    /**< LP Weight */
} vpsissIpipeCfgDaaCfg_t;

/**
 *  struct vpsissIpipeCfaConfig
 *  \brief Structure containing CFA configuration, CFA module is used for
 *         converting Bayer format to RGB format. It also does digital
 *         anti-aliasing to improve the output quality.
 */
typedef struct vpsissIpipeCfaConfig
{
    vpsissIpipeCfaMode_t   cfgMode;
    /**< Selects the CFA Algorithm */

    /* 2DIR Parameters */
    uint32_t               hpfThreshold;
    /**< Low value of the HP threshold */
    uint32_t               hpfSlope;
    /**< HPF Slope */
    uint32_t               mixThreshold;
    /**< Mixed threshold */
    uint32_t               mixSlope;
    /**< Mixed Slope */
    uint32_t               dirThreshold;
    /**< Direction Threshold */
    uint32_t               dirSlope;
    /**< Direction Slope */
    uint32_t               nonDirWeight;
    /**< Non Directional Weight */

    vpsissIpipeCfgDaaCfg_t daaCfg;
    /**< Configuration for Digital Anti Aliasing */
} vpsissIpipeCfaConfig_t;

/**
 *  struct vpsissIpipeWbConfig
 *  \brief IPIPE White Balance Configuration
 */
typedef struct vpsissIpipeWbConfig
{
    uint32_t offset[FVID2_BAYER_COLOR_COMP_MAX];
    /**< Offset before white balance (S12)
     *   Range of the valid values is from -2048 to +2047 */
    uint32_t gain[FVID2_BAYER_COLOR_COMP_MAX];
    /**< White balance gain for each of the color component in U4.9 format
     *   Range of the valid values is from 0 to +15.998 */
} vpsissIpipeWbConfig_t;

/**
 *  struct vpsissIpipeGammaConfig
 *  \brief IPIPE Gamma Correction Configuration
 */
typedef struct vpsissIpipeGammaConfig
{
    vpsissIpipeGammaTbl_t     tbl;
    /**< Select the Table Type, either ROM or RAM Based */
    vpsissIpipeGammaTblSize_t tblSize;
    /**< Select the Table Size */
    uint32_t                  enableRed;
    /**< Flag to enable/disable Gamma Correction for the Red Color Component */
    uint32_t                  enableGreen;
    /**< Flag to enable/disable Gamma Correction for the Green Color Component
    **/
    uint32_t                  enableBlue;
    /**< Flag to enable/disable Gamma Correction for the Blue Color Component */
    uint32_t                 *lutRed;
    /**< Pointer to the Gamma Correction table for the Red Color */
    uint32_t                 *lutGreen;
    /**< Pointer to the Gamma Correction table for the Green Color */
    uint32_t                 *lutBlue;
    /**< Pointer to the Gamma Correction table for the Blue Color */
} vpsissIpipeGammaConfig_t;

/**
 *  struct vpsissIpipe3DLutConfig
 *  \brief IPIPE 3D Lut Configuration
 */
typedef struct vpsissIpipe3DLutConfig
{
    uint32_t  enable;
    /**< Flag to enable/disable 3D Lut */
    uint32_t *b0Addr;
    /**< Lut Bank0 Address */
    uint32_t *b1Addr;
    /**< Lut Bank1 Address */
    uint32_t *b2Addr;
    /**< Lut Bank2 Address */
    uint32_t *b3Addr;
    /**< Lut Bank3 Address */
} vpsissIpipe3DLutConfig_t;

/**
 *  struct vpsissIpipeEeConfig
 *  \brief IPIPE YEE/Edge Enhancer Configuration
 */
typedef struct vpsissIpipeEeConfig
{
    uint32_t                    enable;
    /**< Flag to enable/disable Edge Enhancer */

    vpssissIpipeEeMergeMethod_t method;
    /**< Merge Method */
    uint32_t                    enableHaloReduction;
    /**< Enable/Disable Halo reduction in Edge Sharpener module */

    uint32_t                    hpfDs;
    /**< HPF Down Shift Value
     *   Edge Enhancer Parameter */
    uint32_t                    hpfMulCoeff[VPS_ISS_IPIPE_YEE_MAX_HPF_COEFF];
    /**< HPF Multiplier Coefficients
     *   Edge Enhancer Parameter */
    uint32_t                    hpfThreshold;
    /**< HPF Threshold
     *   Edge Enhancer Parameter */

    uint32_t                    gain;
    /**< Edge Sharpener Gain */
    uint32_t                    hpfThresholdLow;
    /**< Edge Sharpener Low Threshold */
    uint32_t                    hpfThresholdHigh;
    /**< Edge Sharpener High Threshold */
    uint32_t                    gradientGain;
    /**< Edge Sharpener Gradient Gain */
    uint32_t                    gradientOffset;
    /**< Edge Sharpener Gradient Offset */
    uint32_t                   *lutAddr;
    /**< Pointer describing the EE Lut */
} vpsissIpipeEeConfig_t;

/**
 *  struct vpsissIpipeGicConfig
 *  \brief IPIPE GIC Configuration
 */
typedef struct vpsissIpipeGicConfig
{
    uint32_t                     enable;
    /**< Flag to enable/disable GIC module */

    vpsissIpipeGicAlgoType_t     type;
    /**< Algorithm Type */
    uint32_t                     enableLscGain;
    /**< Enables/Disables LSC Gain to the threshold values */
    vpsissIpipeGicThresholdSel_t thrSel;
    /**< Threshold Selection */

    uint32_t                     gain;
    /**< GIC Gain Value
     *   In Simple Averaging method, input pixel is mixed with
     *      the surrounding pixels with this gain value.
     *   In Adaptive method, this is used as a gain */
    uint32_t                     slope;
    /**< Slope used in calculating four thresholds (used for doing
     *      weighted average of current and surrounding four pixels)
     *      when thrSel is set to VPS_ISS_IPIPE_GIC_THR_SEL_GIC_REG */
    uint32_t                     threshold;
    /**< Threshold used in calculating four thresholds
     *      when thrSel is set to VPS_ISS_IPIPE_GIC_THR_SEL_GIC_REG */
    uint32_t                     nfGain;
    /**< NF Gain, used in calculating the threshold
     *      when thrSel is set to VPS_ISS_IPIPE_GIC_THR_SEL_NF2 */
} vpsissIpipeGicConfig_t;

/**
 *  struct vpsissIpipeLscConfig
 *  \brief IPIPE GIC Configuration
 */
typedef struct vpsissIpipeLscConfig
{
    uint32_t vertOffset;
    /**< Vertical Offset, VOFT value */
    uint32_t vertLinCoeff;
    /**< Vertical Linear Coefficient, VA1 */
    uint32_t vertQdrCoeff;
    /**< Vertical Quadratic Coefficient, VA2 */
    uint32_t vertLinShift;
    /**< Vertical Linear Offset, VS1 */
    uint32_t vertQdrShift;
    /**< Vertical Quadratic Offset, VS2 */

    uint32_t horzOffset;
    /**< Horizontal Offset, HOFT value */
    uint32_t horzLinCoeff;
    /**< Horizontal Linear Coefficient, HA1 */
    uint32_t horzQdrCoeff;
    /**< Horizontal Quadratic Coefficient, HA2 */
    uint32_t horzLinShift;
    /**< Horizontal Linear Offset, HS1 */
    uint32_t horzQdrShift;
    /**< Horizontal Quadratic Offset, HS2 */

    uint32_t gain[FVID2_BAYER_COLOR_COMP_MAX];
    /**< LSC Gain for each color Component */
    uint32_t offset[FVID2_BAYER_COLOR_COMP_MAX];
    /**< LSC Offset for each color Component */

    uint32_t shift;
    /**< Threshold Shift Value */
    uint32_t max;
    /**< Threshold Maximum Value */
} vpsissIpipeLscConfig_t;

/**
 *  struct vpsissIpipeRgb2RgbConfig
 *  \brief RGB to RGB configuration parameters, used for both RGB2RGB
 *         modules in IPIPE
 */
typedef struct vpsissIpipeRgb2RgbConfig
{
    int32_t mulCoeff[VPS_ISS_IPIPE_CSC_NUM_COEFF]
    [VPS_ISS_IPIPE_CSC_NUM_COEFF];
    /**< Multiplication coefficients in the format RR, GR, BR in the first row,
     *   RG, GG, BG in the second row and RB, GB, BB in the third row. */
    int32_t addCoeff[VPS_ISS_IPIPE_CSC_NUM_COEFF];
    /**<  Addition Coefficients for R, G and B */
} vpsissIpipeRgb2RgbConfig_t;

/**
 *  struct vpsissIpipeRgb2YuvConfig
 *  \brief RGB to YUV configuration parameters
 */
typedef struct vpsissIpipeRgb2YuvConfig
{
    uint32_t brightness;
    /**< While doing RGB2YUV conversion, brightness can be adjusted
     *   using this parameter. The range of the brightness is 0 to 255 */

    uint32_t contrast;
    /**< While doing RGB2YUV conversion, contrast can be adjusted
     *   using this parameter. The range of the contrast is 0 to 255,
     *   which is 0/16 to 255/16, ie 0 to 15.93 */

    uint32_t mulCoeff[VPS_ISS_IPIPE_CSC_NUM_COEFF]
    [VPS_ISS_IPIPE_CSC_NUM_COEFF];
    /**< Multiplication coefficients in the format Ry, Gy, By in the first row,
     *   RCb, GCb, BCb in the second row and RCr, GCr, BCr in the third row. */
    uint32_t addCoeff[VPS_ISS_IPIPE_CSC_NUM_COEFF];
    /**<  Addition Coefficients */
} vpsissIpipeRgb2YuvConfig_t;

/**
 *  struct vpsissIpipeYuvPhsConfig
 *  \brief YUV444 to YUV422 configuration
 */
typedef struct vpsissIpipeYuvPhsConfig
{
    uint32_t        enableLpf;
    /**< Flag to enable Low Pass filter */
    Fvid2_ChromaPos chromaPos;
    /**< Position of the output chroma */
} vpsissIpipeYuvPhsConfig_t;

/**
 *  struct vpsissIpipeDpcOtfConfig
 *  \brief Configure on the fly DPC
 */
typedef struct vpsissIpipeDpcOtfConfig
{
    uint32_t                 enableOtfDpc;
    /**< TRUE enables on the FLY (OTF) DPC module, Ensure to choose on the valid
     *      method for OTF DPC */
    vpsissIpipeDpcOtfModes_t method;
    /**< Choose the method for adaptive on the fly DPC */

    /* Detection thresholds */
    uint32_t                 dThr;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_D_THR_R - Method 2
     *  IPIPE_DPC_OTF_3_D_THR   - Method 3
     *  Not used for Method 1 */
    uint32_t                 grThr;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_D_THR_GR- Method 2
     *  IPIPE_DPC_OTF_3_D_SPL   - Method 3
     *  Not used for Method 1 */
    uint32_t                 gbThr;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_D_THR_GB- Method 2
     *  IPIPE_DPC_OTF_3_D_MIN   - Method 3
     *  Not used for Method 1 */
    uint32_t                 bThr;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_D_THR_B- Method 2
     *  IPIPE_DPC_OTF_3_D_MAX  - Method 3
     *  Not used for Method 1 */

    /* Correction thresholds */
    uint32_t                 rCor;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_C_THR_R     - Method 2
     *  IPIPE_DPC_OTF_3_C_THR       - Method 3
     *  Not used for method 1 */
    uint32_t                 grCor;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_C_THR_GR    - Method 2
     *  IPIPE_DPC_OTF_3_C_SLP       - Method 3
     *  Not used for method 1 */
    uint32_t                 gbCor;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_C_THR_GB    - Method 2
     *  IPIPE_DPC_OTF_3_C_MIN       - Method 3
     *  Not used for method 1 */
    uint32_t                 bCor;
    /**< Value for register
     *  IPIPE_DPC_OTF_2_C_THR_B     - Method 2
     *  IPIPE_DPC_OTF_3_C_MAX       - Method 3
     *  Not used for method 1 */

    uint32_t                 shiftValue;
    /**< Value for register IPIPE_DPC_OTF_3_SHF, applicable only for Method 3 */
} vpsissIpipeDpcOtfConfig_t;

/**
 *  struct vpsissIpipeDpcLutConfig
 *  \brief Configure Look Up Table based DPC
 */
typedef struct vpsissIpipeDpcLutConfig
{
    uint32_t enableLutDpc;
    /**< TRUE enables Look Up Table (LUT) DPC module. */
    uint32_t lutMode;
    /**< TRUE specifies the LUT specified is for the whole frame,
     *      Otherwise upto 1024 valid entries in LUT */
    uint32_t blackOrWhite;
    /**< TRUE configures to replace with white dot, replaced with black dot
     *      otherwise. Applicable only when method 0 is choosen.
     *      The LUT entry chooses the method to be employed */
    uint32_t lutAddr;
    /**< Address of the LUT to be used */
    uint32_t lutSize;
    /**< Size of LUT */
} vpsissIpipeDpcLutConfig_t;

/**
 *  struct vpsissIpipeCtrl
 *  \brief Control structure used to configure different sub-modules of IPIPE
 */
typedef struct vpsissIpipeCtrl
{
    vpsissIpipeModule_t         module;
    /**< Id of the module to be configured */
    vpsissIpipeInConfig_t      *inCfg;
    /**< Input Configuration */
    vpsissIpipeYuvPhsConfig_t  *yuvPhsCfg;
    /**< Pointer to YUV Phase Configuration,
     *   should not be null when module is set to
     *   VPS_ISS_IPIPE_MODULE_YUV422_YUV422 */
    vpsissIpipeRgb2RgbConfig_t *rgb2RgbCfg;
    /**< Pointer to RGB2RGB configuration
     *   should not be null when module is set to either
     *   VPS_ISS_IPIPE_MODULE_RGB2RGB1 or VPS_ISS_IPIPE_MODULE_RGB2RGB2 */
    vpsissIpipeRgb2YuvConfig_t *rgb2YuvCfg;
    /**< Pointer to RGB2YUV configuration
     *   should not be null when module is set to either
     *   VPS_ISS_IPIPE_MODULE_RGB2YUV */
    vpsissIpipeWbConfig_t      *wbCfg;
    /**< Pointer to White Balance Configuration
     *   should not be null when module is set to either
     *   VPS_ISS_IPIPE_MODULE_WB */
    vpsissIpipeCfaConfig_t     *cfaCfg;
    /**< Pointer to Color Filter Array Configuration
     *   should not be null when module is set to either
     *   VPS_ISS_IPIPE_MODULE_CFA */
    vpsissIpipeDpcOtfConfig_t  *dpcOtf;
    /**< Configure on the fly DPC */
    vpsissIpipeDpcLutConfig_t  *dpcLut;
    /**< Configure LUT based DPC */
    vpsissIpipeGammaConfig_t   *gammaCfg;
    /**< Gamma Correction Config */
    vpsissIpipe3DLutConfig_t   *colorConvert3DLutCfg;
    /**< Color Conversion 3D Lut Configuration */
    vpsissIpipeEeConfig_t      *eeCfg;
    /**< YEE/Edge Enhancer Configuration */
    vpsissIpipeGicConfig_t     *gicCfg;
    /**< GIC Configuration */
    vpsissIpipeLscConfig_t     *lscCfg;
    /**< Lens Shading Configuration */
    vpsissIpipeNf2Config_t     *nf1Cfg;
    /**< Noise Filter 1 Configuration */
    vpsissIpipeNf2Config_t     *nf2Cfg;
    /**< Noise Filter 2 Configuration */
} vpsissIpipeCtrl_t;

/**
 *  struct vpsissIpipeLutFmtCnvt
 *  \brief Structure for converting LUT format from user format to
 *         ip required format
 *         Pointer to this structure is passed as an argument to ioctl
 *         #VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT
 */
typedef struct vpsissIpipeLutFmtCnvt
{
    vpsissIpipeModule_t moduleId;
    /**< Module for which Lut requires to be converted
     *   Currently on 3D LUT module id is supported */
    uint32_t           *lut3DRed;
    /**< 3D Lut for the Red Color */
    uint32_t           *lut3DGreen;
    /**< 3D Lut for the Green Color */
    uint32_t           *lut3DBlue;
    /**< 3D Lut for the Blue Color */
    /**< Each Lut size is 768 and each Lut entry is 10bit */
    uint32_t           *out3DB0Addr;
    /**< Pointer to the Array 0 address */
    uint32_t           *out3DB1Addr;
    /**< Pointer to the Array 1 address */
    uint32_t           *out3DB2Addr;
    /**< Pointer to the Array 2 address */
    uint32_t           *out3DB3Addr;
    /**< Pointer to the Array 3 address */

    /* Map YEE Lut from CMODEL to IP Model, Typically LUT will be in CMODEL
        format, require to convert it to IP format. */
    uint32_t           *yeeLutIn;
    /**< The CMODEL Lut */
    uint32_t           *yeeLutOut;
    /**< IP LUT */

    /* Map YEE Lut from CMODEL to IP Model, Typically LUT will be in CMODEL
        format, require to convert it to IP format. */
    uint32_t           *gammaLutIn;
    /**< The CMODEL Lut */
    uint32_t           *gammaLutOut;
    /**< IP Lut */

} vpsissIpipeLutFmtCnvt_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_CFG_IPIPE_H_ */

