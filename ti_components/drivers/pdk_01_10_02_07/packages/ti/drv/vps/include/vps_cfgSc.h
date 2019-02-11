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
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_SC VPS - Scaler Config API
 *
 *  @{
 */

/**
 *  \file vps_cfgSc.h
 *
 *  \brief VPS - Scaler Config API
 */

#ifndef VPS_CFG_SC_H_
#define VPS_CFG_SC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/vps/include/common/bsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of scaler phases. */
#define VPS_SC_NUM_PHASES               (32U)

/** \brief Number of horizontal scaler taps. */
#define VPS_SC_NUM_HORZ_TAPS            (7U)
/**
 *  \brief Number of horizontal scaler taps aligned because of VPDMA
 *  requirements.
 */
#define VPS_SC_NUM_HORZ_TAPS_ALIGNED    (VPS_SC_NUM_HORZ_TAPS + 1U)
/** \brief Number of scaler horizontal coefficient. */
#define VPS_SC_HORZ_NUM_COEFF           (VPS_SC_NUM_PHASES * \
                                         VPS_SC_NUM_HORZ_TAPS_ALIGNED)

/** \brief Number of vertical scaler taps. */
#define VPS_SC_NUM_VERT_TAPS            (5U)
/**
 *  \brief Number of vertical scaler taps aligned because of VPDMA
 *  requirements.
 */
#define VPS_SC_NUM_VERT_TAPS_ALIGNED    (VPS_SC_NUM_VERT_TAPS + 3U)
/** \brief Number of scaler vertical coefficient. */
#define VPS_SC_VERT_NUM_COEFF           (VPS_SC_NUM_PHASES * \
                                         VPS_SC_NUM_VERT_TAPS_ALIGNED)

/** \brief Number of bilinear scaler taps. */
#define VPS_SC_NUM_BILINEAR_TAPS        (7U)
/**
 *  \brief Number of bilinear scaler taps aligned because of VPDMA
 *  requirements.
 */
#define VPS_SC_NUM_BILINEAR_TAPS_ALIGNED    (VPS_SC_NUM_BILINEAR_TAPS + 1U)
/** \brief Number of scaler bilinear coefficient. */
#define VPS_SC_BILINEAR_NUM_COEFF       (VPS_SC_NUM_PHASES * \
                                         VPS_SC_NUM_BILINEAR_TAPS_ALIGNED)

/** \brief Number of peaking coefficients */
#define VPS_SC_PEAKING_MAX_COEFF        (6U)

/**
 *  enum Vps_ScCoeffSet
 *  \brief This defines the standard coefficient sets available for
 *  different scaling ratios.
 *  IMP: Do not assign numerical values to enum here.
 */
typedef enum
{
    VPS_SC_DS_SET_ANTI_FLICKER,
    /**< Coefficient for anti-flicker effect */
    VPS_SC_DS_SET_3_16,
    /**< Coefficient for down sampling 0.1875(3/16) <Factor<= 0.25(4/16). */
    VPS_SC_DS_SET_4_16,
    /**< Coefficient for down sampling 0.25(4/16) <Factor<= 0.3125(5/16). */
    VPS_SC_DS_SET_5_16,
    /**< Coefficient for down sampling 0.3125(5/16) <Factor<= 0.375(6/16). */
    VPS_SC_DS_SET_6_16,
    /**< Coefficient for down sampling 0.375(6/16) <Factor<= 0.4375(7/16). */
    VPS_SC_DS_SET_7_16,
    /**< Coefficient for down sampling 0.4375(7/16) <Factor<= 0.5(8/16). */
    VPS_SC_DS_SET_8_16,
    /**< Coefficient for down sampling 0.5(8/16) <Factor<= 0.5625(9/16). */
    VPS_SC_DS_SET_9_16,
    /**< Coefficient for down sampling 0.5625(9/16) <Factor<= 0.625(10/16). */
    VPS_SC_DS_SET_10_16,
    /**< Coefficient for down sampling 0.625(10/16) <Factor<= 0.6875(11/16). */
    VPS_SC_DS_SET_11_16,
    /**< Coefficient for down sampling 0.6875(11/16) <Factor<= 0.75(12/16). */
    VPS_SC_DS_SET_12_16,
    /**< Coefficient for down sampling 0.75(12/16) <Factor<= 0.8125(13/16). */
    VPS_SC_DS_SET_13_16,
    /**< Coefficient for down sampling 0.8125(13/16) <Factor<= 0.875(14/16). */
    VPS_SC_DS_SET_14_16,
    /**< Coefficient for down sampling 0.875(14/16) <Factor<= 0.9375(15/16). */
    VPS_SC_DS_SET_15_16,
    /**< Coefficient for down sampling 0.9375(15/16) < Factor< 1(16/16) */
    VPS_SC_US_SET,
    /**< Coefficient set for the upsampling.  Includes horizontal, vertical
     *   and both chroma and luma up sampling. */
    VPS_SC_SET_1_1,
    /**< Coefficient set for one-to-one scenario, when scaler is not in
     *   bypass. */
    VPS_SC_SET_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_ScCoeffSet;

/**
 *  enum Vps_ScHorzScalerDcmType
 *  \brief This defines the type of horizontal scaler.
 *  In HW, two decimators are cascaded with a polyphase filter for horizontal
 *  scaling. Each decimator can perform 0.5x scaling.
 *  If auto is selected, driver will set appropriate decimator setting.
 */
typedef enum
{
    VPS_SC_HST_DCM_AUTO = 0,
    /**< Automatically selects decimation filter and then polyphase filter if
     *   required. */
    VPS_SC_HST_DCM_2X,
    /**< Selects 2X decimation Filter. Used for downscaling only. Not used when
     *   down scaling ratio > 0.5x. */
    VPS_SC_HST_DCM_4X,
    /**< Selects 4X decimation Filter. Used for down scaling only. Not used
     *   when down scaling ratio > 0.5x. */
    VPS_SC_HST_DCM_NONE,
    /**< Only polyphase filter is active */
    VPS_SC_HST_DCM_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_ScHorzScalerDcmType;

/**
 *  enum Vps_ScVertScalerType
 *  \brief This defines type of vertical scaling. Vertical
 *  scaling two types scalers i.e. running average filter and polyphase filter.
 *  The output of the running average filter is based on weighted average
 *  of pixels in the current and previous rows in vertical direction.
 */
typedef enum
{
    VPS_SC_VST_AUTO = 0,
    /**< Automatically selects appropriate combination of polyphase or RAV
     *   filter and decimation filters for vertical scaling */
    VPS_SC_VST_POLYPHASE,
    /**< Selects polyphase filter.
     *   Recommended for polyphase scaling ratios >= 0.25x
     *   Supported for all scaling ratios */
    VPS_SC_VST_RAV,
    /**< Uses Running Average Filter.
     *   Not supported for scaling ratios > 0.25x
     *   Recommended for scaling ratios < 0.25x. */
    VPS_SC_VST_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_ScVertScalerType;

/**
 *  enum Vps_ScBiLinearIntpType
 *  \brief Enum for specifying Scaler biliear interpolation type.
 */
typedef enum
{
    VPS_SC_BINTP_ORIGINAL = 0,
    /**< Original bilinear interpolation. */
    VPS_SC_BINTP_MODIFIED,
    /**< Modified bilinear interpolation. */
    VPS_SC_BINTP_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_ScBiLinearIntpType;

/**
 *  enum Vps_ScSelfGenFid
 *  \brief Enum for specifying whether Scaler generates FID or not.
 */
typedef enum
{
    VPS_SC_SELF_GEN_FID_DISABLE = 0,
    /**< Disable Self Generation of FID. */
    VPS_SC_SELF_GEN_FID_ENABLE
    /**< Enable Self Generation of FID. */
} Vps_ScSelfGenFid;

/**
 *  enum Vps_ScSetPhaseInfoMode
 *  \brief Enum for specifying whether Scaler phase offsets are used from
 *         application OR calculated locally from config
 *         used for setting following values
 *         PolyPh: row_acc_inc, row_acc_offset,row_acc_offset_b
 *         RAV   : Sc_factor_rav, Row_acc_init_rav, Row_acc_init_rav_b
 */
typedef enum
{
    VPS_SC_SET_PHASE_INFO_DEFAULT = 0,
    /**< Calculate phase info locally and use . */
    VPS_SC_SET_PHASE_INFO_FROM_APP
    /**< use the values passed from calling layer. */
} Vps_ScSetPhaseInfoMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_ScCoeff
 *  \brief Structure is used to provide application defined scaler coefficients.
 *  Scaler provides functions to configure standard coefficients as per the
 *  scaling ratio. If application wants to use its own set of coefficients, it
 *  can point the pointers in the structure to the coefficient array and call
 *  Sc_createUserCoeffOvly function to fill up coefficient memory.
 */
typedef struct
{
    UInt16 hsLuma[VPS_SC_HORZ_NUM_COEFF];
    /**< Array in which horizontal polyphase filter coefficients for Luma
     *   will be stored. */
    UInt16 hsChroma[VPS_SC_HORZ_NUM_COEFF];
    /**< Array in which horizontal polyphase filter coefficients for Chroma
     *   will be stored. */
    UInt16 vsLuma[VPS_SC_VERT_NUM_COEFF];
    /**< Array in which vertical polyphase filter coefficients for Luma
     *   will be stored. */
    UInt16 vsChroma[VPS_SC_VERT_NUM_COEFF];
    /**< Array in which vertical polyphase filter coefficients for Chroma
     *   will be stored. */
    UInt16 vsBilinearLuma[VPS_SC_BILINEAR_NUM_COEFF];
    /**< Array in which bilinear polyphase filter coefficients for Luma
     *   will be stored. */
    UInt16 vsBilinearChroma[VPS_SC_BILINEAR_NUM_COEFF];
    /**< Array in which bilinear polyphase filter coefficients for Chroma
     *   will be stored. */
} Vps_ScCoeff;

/**
 *  struct Vps_ScCoeffParams
 *  \brief Application interface structure for programming the coefficients.
 *  Structure will be used for all drivers involving scalers.
 */
typedef struct
{
    UInt32 scalerId;
    /**< Scaler ID - Used in case multiple scalers are present in a driver. */
    UInt32 hScalingSet;
    /**< Horizontal scaling coefficient set.
     *   For valid values see #Vps_ScCoeffSet. */
    UInt32 vScalingSet;
    /**< Vertical scaling coefficeint set.
     *   For valid values see #Vps_ScCoeffSet. */
} Vps_ScCoeffParams;

/**
 *  struct Vps_ScRtConfig
 *  \brief Struture to configure runtime scaler parameters.
 */
typedef struct
{
    UInt32 scBypass;
    /**< To bypass the scaler .*/
    UInt32 scSetPhInfo;
    /**< Flag to indicate whether to program scaler phase information.
     *   This is used only for subframe based processing to set scaler state for
     *   required phase values by application.
     *   If this flag is TRUE, following values are programmed:
     *         for PolyPh : row_acc_inc, row_acc_offset,row_acc_offset_b
     *         for RAV    : Sc_factor_rav, Row_acc_init_rav, Row_acc_init_rav_b
     *   If this flag is FALSE, below values are ignored. */
    UInt32 rowAccInc;
    /**< Row accumulator increment for vertical polyphase filter. */
    UInt32 rowAccOffset;
    /**< Scaler phase value for vertical polyphase filter case for
     *   top field/progressive input. */
    UInt32 rowAccOffsetB;
    /**< Scaler phase value for vertical polyphase filter case for
     *   bottom field. */
    UInt32 ravScFactor;
    /**< Scaling factor for vertical running average filter. */
    UInt32 ravRowAccInit;
    /**< Scaler phase value for vertical running average filter case for
     *   top field/progressive input. */
    UInt32 ravRowAccInitB;
    /**< Scaler phase value for vertical running average filter case for
     *   bottom field. */
} Vps_ScRtConfig;

/**
 *  struct Vps_ScPeakingConfig
 *  \brief This structure defines the parameters required to configure the
 *  peaking block.
 *
 *  Peaking block increases the amplitude of high frequency luminance
 *  information in horizontal direction to increase the sharpness of a video
 *  image before it is scaled.
 *  This configuration is for the advanced users and for debugging.
 *  Normal applications should not use this structure.
 */
typedef struct
{
    UInt8  hpfCoeff[VPS_SC_PEAKING_MAX_COEFF];
    /**< Array of coefficients for 11 tap high pass filter. */
    UInt8  hpfNormShift;
    /**< HPF value will be right shifted by this value. */
    UInt16 nlClipLimit;
    /**< Non linear clipping limit. */
    UInt16 nlLowThreshold;
    /**< Coring threshold. */
    UInt16 nlHighThreshold;
    /**< High threshold for nonlinear peaking block. */
    UInt16 nlLowSlopeGain;
    /**< Slope of the nonlinear peaking function. */
    UInt16 nlHighSlopeShift;
    /**< Shift of the nonlinear peaking function. */
} Vps_ScPeakingConfig;

/**
 *  struct Vps_ScEdgeDetectConfig
 *  \brief Edge Detection Params.
 *
 *  This block is used to detect edges in image to have edge directed scaling.
 *  This block is available in high quality scaler only.
 *  This configuration is for the advanced users and for debugging.
 *  Normal applications should not use this structure.
 *  confFactor - Defines confidence factor when edge detection is disabled.
 */
typedef struct
{
    UInt16 gradientThreshold;
    /**< Threshold for the gradient for the edge strength test. */
    UInt8  gradientRange;
    /**< Define the soft switch range of the edge strength test. The range is
     *   2^gradient_thr_range. */
    UInt16 minGyThreshold;
    /**< Threshold for the soft switch of the decay for small Gy. */
    UInt8  minGyRange;
    /**< Range for minimum Gy threshold. The range is 2^minGyRange. */
    UInt16 chromaIntpThreshold;
    /**< defines the difference-threshold between chroma pixels. If the
     *   difference is less than this threshold, the interpolation of chroma
     *   should be done along edge direction. Otherwise the interpolation
     *   of chroma should be done vertically. */
    UInt16 evThreshold;
    /**< If abs(edge-vector) > ev_thr then luma output is based on a soft
     *   switch between pixels along the edge and vertical. */
    UInt8  deltaChromaThreshold;
    /**< It defines the range for chroma soft switch based on pixel
     *   differences. */
    UInt8  deltaLumaThreshold;
    /**< It defines the range of luma soft switch based on pixel difference. */
    UInt8  deltaEvThreshold;
    /**< It defines the range for chroma soft switch based on edge vector. */
} Vps_ScEdgeDetectConfig;

typedef struct
{
    UInt32 rowAccInc;
    /**< Scaler phase value increment to be used by vertical polyphase filter */
    UInt32 rowAccOffset;
    /**< Scaler phase value for vertical polyphase filter case, for top field/
     *   progressive input */
    UInt32 rowAccOffsetB;
    /**< Scaler phase value for vertical polyphase filter case, for bottom
     *   field */
} Vps_ScPolyPhaseInfo;

typedef struct
{
    UInt32 ravScFactor;
    /**< Scaler factor used by vertical RAV filter */
    UInt32 ravRowAccInit;
    /**< Scaler phase value for vertical RAV filter case, for top field/
     *   progressive input */
    UInt32 ravRowAccInitB;
    /**< Scaler phase value for vertical RAV filter case, for bottom
     *   field */
} Vps_ScRavPhaseInfo;

/**
 *  struct Vps_ScAdvConfig
 *
 *  \brief This structure define parameters additional to #Vps_ScConfig
 *  to configure scaler modules.
 *  It can be used to set the parameters in the scaler registers as well as
 *  in the VPDMA register overlay.
 *  It also is used to configure runtime changes in the scale ratio.
 *
 *  TODO: Verify HAL function for the validity of following line
 *  For the runtime changes, only size and position parameters will
 *  be configured but still upper layer will have to pass all the parameters
 *  because scaler uses these parameters to calculate ratio specific parameters.
 *
 */
typedef struct
{
    UInt32                  tarWidth;
    /**< Target image Height */
    UInt32                  tarHeight;
    /**< Target image Width */

    UInt32                  srcWidth;
    /**< Source image height. This is the original non-cropped image height */
    UInt32                  srcHeight;
    /**< Source image width. This is the original non-cropped image width */

    UInt32                  cropStartX;
    /**< Vertical Offset of the cropped image. From this vertical offset,
     *   original image will be cropped. If cropping is not required, this
     *   should be set to zero. */
    UInt32                  cropStartY;
    /**< Horizontal Offset of the cropped image. From this horizontal offset,
     *   original image will be cropped. If cropping is not required, this
     *   should be set to zero. */

    UInt32                  cropWidth;
    /**< Cropped image Height. Original image will be cropped to this size. If
     *   cropping is not required, then this should same as the original image
     *   size */
    UInt32                  cropHeight;
    /**< Cropped image Width. Original image will be cropped to this size. If
     *   cropping is not required, then this should same as the original image
     *   size */

    UInt32                  inFrameMode;
    /**< Input Frame Mode i.e. Interlaced/progressive. Use #Fvid2_ScanFormat */
    UInt32                  outFrameMode;
    /**< Output Frame Mode i.e. interlaced or progressive. Input and
     *   output frame mode can be different so that scaler can convert
     *   one format to another. Use #Fvid2_ScanFormat */
    UInt32                  fidPol;
    /**< This is used to specify whether input FID will be inverted before use
     *   or not. Use #Fvid2_FidPol */
    UInt32                  selfGenFid;
    /**< Flag to indicate whether to use self Generate FID feature of the
     *   scaler. Use #Vps_ScSelfGenFid */

    UInt32                  biLinIntpType;
    /**< Variable to specify Bilinear Interpolation Type
     *   For valid values see #Vps_ScBiLinearIntpType */

    UInt32                  hsDcmType;
    /**< Choose which decimators are active
     *   For valid values see #Vps_ScHorzScalerDcmType */
    UInt32                  hPolyBypass;
    /**< Flag to bypass horizontal scaler. When this flag is zero, polyphase
     *   scaler is always used regardless of the width configuration */

    UInt32                  vsType;
    /**< This is used to specify vertical scaling algorithm.
     *   For valid values see #Vps_ScVertScalerType */

    UInt32                  defConfFactor;
    /**< Default Confidence factor when edge detection is disabled. This is
     *  used only for the High Quality scaler where edge detection block is
     *  available. */

    Vps_ScEdgeDetectConfig *edgeDetectCfg;
    /**< Pointer to edege detect parameters for HQ scaler.
     *   If this is NULL peaking configuation will
     *   not be applied.  Else configuration for this will be applied
     *   Values applied will be applicable to all the channels of the driver.
     *   This is not per channel configuration.  Only used by
     *   VpsHal_scSetAdvConfig function
     */

    Vps_ScPeakingConfig    *peakingCfg;
    /**< Pointer to Peaking params. If this is NULL peaking configuation will
     *   not be applied.  Else peaking configuration for this will be applied
     *   Values applied will be applicable to all the channels of the driver.
     *   This is not per channel configuration. Only used by
     *   VpsHal_scSetAdvConfig function
     */

    UInt32                  phInfoMode;
    /**< Flag to indicate whether to program Scaler phase information from
     *  below values Or calculate locally from config.
     *  The variable polyPhaseValues and ravPhaseValues should be
     *  set appropriately in case of
     *  phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP
     *  Use #Vps_ScSetPhaseInfoMode
     */
    Vps_ScPolyPhaseInfo     polyphasePhInfo;
    /**< Scaler phase value for polyphase filter case - used only when
     * phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP
     */
    Vps_ScRavPhaseInfo      ravPhInfo;
    /**< Scaler phase value for RAV filter case - used only when
     * phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP
     */

    Ptr                     arg;
    /**< Currently not used. It should be NULL. */
} Vps_ScAdvConfig;

/**
 *  struct Vps_ScConfig
 *  \brief These are all scaler parameters exposed to the application.
 *
 *  #Vps_ScAdvConfig can be left as NULL by the application
 *  Driver shall derive these from channel properties.
 *  HAL layer shall always require advCfg != NULL
 */
typedef struct
{
    UInt32           bypass;
    /**< Scaler should be bypassed or not. */

    UInt32           nonLinear;
    /**< Flag to indicate whether linear or non-linear scaling is used for
     *   horizontal scaler. Non-linear scaling is available for polyphase
     *   filter only
     *   Example: Scaling from 16/9 aspect ratio to 4/3 aspect ratio.*/

    UInt32           stripSize;
    /**< Size of left and right strip for nonlinear horizontal scaling in terms
     *   of pixel. It must be set to zero for linear horz scaling. */

    UInt32           enableEdgeDetect;
    /**< Enables/Disables Edge detection. Edge detection is only available in
     * high quality scaler.*/

    UInt32           enablePeaking;
    /**< Flag to enable Peaking block in the scaler. All the default
     *   coefficients required for the peaking block are already configured
     *   as part of initialization. These coefficient values are considered
     *   as expert values and taken from the specs. If required, it should
     *   be changed at the compile time in vpshal_scDefaults.h file. */

    Vps_ScAdvConfig *advCfg;
    /**< If this is NULL, driver will update this with pointer to default
     *   parameters.*/
} Vps_ScConfig;

/**
 *  sturct Vps_ScRdWrAdvCfg
 *  \brief Structure to read/write to advance scaler registers.
 */
typedef struct
{
    UInt32       chNum;
    /**< Channel number for which the configuration is to be set/get.
     *   Used only in M2M driver, for display and capture driver set
     *   this to 0. */
    UInt32       scalerId;
    /**< Scaler ID - Used in case multiple scalers are present in a driver. */
    Vps_ScConfig scCfg;
    /**< Scaler configuration to be read/write. All advanced parameters should
     *   be set when using this structure */
} Vps_ScRdWrAdvCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_ScCoeffParams structure init function.
 *
 *  \param scCoeff      [IN] Pointer to #Vps_ScCoeffParams structure.
 *
 */
static inline void VpsScCoeffParams_init(Vps_ScCoeffParams *scCoeff);

/**
 *  \brief Vps_ScConfig structure init function.
 *
 *  \param scCfg        [IN] Pointer to #Vps_ScConfig structure.
 *
 */
static inline void VpsScConfig_init(Vps_ScConfig *scCfg);

/**
 *  \brief Vps_ScRdWrAdvCfg structure init function.
 *
 *  \param advCfg       [IN] Pointer to #Vps_ScRdWrAdvCfg structure.
 *
 */
static inline void VpsScRdWrAdvCfg_init(Vps_ScRdWrAdvCfg *advCfg);

/**
 *  \brief Vps_ScAdvConfig structure init function.
 *
 *  \param advCfg       [IN] Pointer to #Vps_ScAdvConfig structure.
 *
 */
static inline void VpsScAdvConfig_init(Vps_ScAdvConfig *advCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsScCoeffParams_init(Vps_ScCoeffParams *scCoeff)
{
    if (NULL != scCoeff)
    {
        scCoeff->scalerId    = 0U;
        scCoeff->hScalingSet = VPS_SC_US_SET;
        scCoeff->vScalingSet = VPS_SC_US_SET;
    }

    return;
}

static inline void VpsScConfig_init(Vps_ScConfig *scCfg)
{
    if (NULL != scCfg)
    {
        scCfg->bypass           = (UInt32) TRUE;
        scCfg->nonLinear        = (UInt32) FALSE;
        scCfg->stripSize        = 0U;
        scCfg->enableEdgeDetect = (UInt32) FALSE;
        scCfg->enablePeaking    = (UInt32) TRUE;
        scCfg->advCfg           = NULL;
    }

    return;
}

static inline void VpsScRdWrAdvCfg_init(Vps_ScRdWrAdvCfg *advCfg)
{
    if (NULL != advCfg)
    {
        advCfg->chNum    = 0U;
        advCfg->scalerId = 0U;
        VpsScConfig_init(&advCfg->scCfg);
    }

    return;
}

static inline void VpsScAdvConfig_init(Vps_ScAdvConfig *advCfg)
{
    if (NULL != advCfg)
    {
        advCfg->srcWidth      = 0U;
        advCfg->srcHeight     = 0U;
        advCfg->tarWidth      = advCfg->srcWidth;
        advCfg->tarHeight     = advCfg->srcHeight;
        advCfg->cropStartX    = 0U;
        advCfg->cropStartY    = 0U;
        advCfg->cropWidth     = advCfg->srcWidth;
        advCfg->cropHeight    = advCfg->srcHeight;
        advCfg->inFrameMode   = FVID2_SF_PROGRESSIVE;
        advCfg->outFrameMode  = FVID2_SF_PROGRESSIVE;
        advCfg->fidPol        = FVID2_FIDPOL_NORMAL;
        advCfg->selfGenFid    = (UInt32) FALSE;
        advCfg->biLinIntpType = VPS_SC_BINTP_ORIGINAL;
        advCfg->hsDcmType     = VPS_SC_HST_DCM_NONE;
        advCfg->hPolyBypass   = (UInt32) FALSE;
        advCfg->vsType        = VPS_SC_VST_AUTO;
        advCfg->defConfFactor = 0U;
        advCfg->edgeDetectCfg = NULL;
        advCfg->peakingCfg    = NULL;
        advCfg->phInfoMode    = VPS_SC_SET_PHASE_INFO_DEFAULT;
        advCfg->polyphasePhInfo.rowAccInc     = 0U;
        advCfg->polyphasePhInfo.rowAccOffset  = 0U;
        advCfg->polyphasePhInfo.rowAccOffsetB = 0U;
        advCfg->ravPhInfo.ravScFactor         = 0U;
        advCfg->ravPhInfo.ravRowAccInit       = 0U;
        advCfg->ravPhInfo.ravRowAccInitB      = 0U;
        advCfg->arg = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_SC_H_ */

/* @} */
