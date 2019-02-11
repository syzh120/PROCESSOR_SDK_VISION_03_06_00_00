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
 *  \file vps_cfgisif.h
 *
 *  \brief
 *
 */

#ifndef VPS_CFG_ISIF_H_
#define VPS_CFG_ISIF_H_

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
 *  \brief Ioctl for getting isif parameters
 */
#define VPS_ISS_ISIF_IOCTL_GET_CONFIG       (VPS_ISS_IOCTL_ISIF_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for setting isif parameters
 */
#define VPS_ISS_ISIF_IOCTL_SET_CONFIG       (VPS_ISS_ISIF_IOCTL_GET_CONFIG + 1U)

/**
 *  \brief Number of vertical line defects that could be corrected.
 */
#define VPS_ISS_ISIF_VFDC_MAX_PIX_CORR      (0x8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum defining supported sub-modules of ISIF.
 */
typedef enum vpsissIsifModule
{
    VPS_ISS_ISIF_MODULE_WB = 0x0,
    /**< Gain and Offset Sub-Module of the ISIF */
    VPS_ISS_ISIF_MODULE_VDFC = 0x1,
    /**< Vertical Line Defect Pixel correction */
    VPS_ISS_ISIF_MODULE_BLACK_CLAMP = 0x2,
    /**< Black Clamping module, also used for setting up DC offset */
    VPS_ISS_ISIF_MODULE_2D_LSC = 0x3,
    /**< 2D Lens Shading correction module */
    VPS_ISS_ISIF_MODULE_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                                will always be contained in int */
} vpsissIsifModule_t;   /**< vpsissIsifModule_t */

/**
 *  \brief Enum defining three outputs from ISIF. Used in enabling/disabling
 *         gain offset/white balance for the output.
 */
typedef enum vpsissIsifOutput
{
    VPS_ISS_ISIF_OUTPUT_H3A = 0x0,
    /**< H3A Output from ISIF */
    VPS_ISS_ISIF_OUTPUT_IPIPE = 0x1,
    /**< IPIPE Output from ISIF */
    VPS_ISS_ISIF_OUTPUT_MEMORY = 0x2,
    /**< Memory Output from ISIF */
    VPS_ISS_ISIF_MAX_OUTPUT = 0x3,
    /**< should be the last number, used in defining array size */
    VPS_ISS_ISIF_OUTPUT_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                                will always be contained in int */
} vpsissIsifOutput_t;   /**< vpsissIsifOutput_t */

/**
 *  \brief Enum defining down scaling factor for gain and offset
 *   table for 2D LSC.
 */
typedef enum vpsissIsif2DLscDownScaleFactor
{
    VPS_ISS_ISIF_2D_LSC_DS_8 = 0x3,
    /**< Down Scaling factor is 8, ie paxel is 8 pixel tall */
    VPS_ISS_ISIF_2D_LSC_DS_16 = 0x4,
    /**< Down Scaling factor is 16, ie paxel is 16 pixel tall */
    VPS_ISS_ISIF_2D_LSC_DS_32 = 0x5,
    /**< Down Scaling factor is 32, ie paxel is 32 pixel tall */
    VPS_ISS_ISIF_2D_LSC_DS_64 = 0x6,
    /**< Down Scaling factor is 64, ie paxel is 64 pixel tall */
    VPS_ISS_ISIF_2D_LSC_DS_128 = 0x7,
    /**< Down Scaling factor is 128, ie paxel is 128 pixel tall */
    VPS_ISS_ISIF_2D_LSC_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed,
                                            will always be contained in int */
} vpsissIsif2DLscDownScaleFactor_t; /**< vpsissIsif2DLscDownScaleFactor_t */

/**
 *  \brief Enum defining gain format for 2D LSC,
 *  8bit gain can be in various format, based on number of number of bits
 *  for int and fraction portion
 */
typedef enum vpsissIsif2DLscGainFormat
{
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q8 = 0x0,
    /**< All bits are fraction */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q8_1Base = 0x1,
    /**< All bits are fraction with base of 1.0 */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q7 = 0x2,
    /**< In 8bit mode, 7bit fraction */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q7_1BASE = 0x3,
    /**< In 8bit mode, 7bit fraction with base of 1.0 */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q6 = 0x4,
    /**< In 8bit mode, 6bit fraction */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q6_1BASE = 0x5,
    /**< In 8bit mode, 7bit fraction with base of 1.0 */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q5 = 0x6,
    /**< In 8bit mode, 5bit fraction */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q5_1BASE = 0x7,
    /**< In 8bit mode, 5bit fraction with base of 1.0 */
    VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed,
      *  will always be contained in int */
} vpsissIsif2DLscGainFormat_t; /**< vpsissIsif2DLscGainFormat_t */

/**
 *  \brief Enum defining gain format for 2D LSC,
 *  8bit gain can be in various format, based on number of number of bits
 *  for int and fraction portion
 */
typedef enum vpsissIsif2DLscOffsetShiftup
{
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_0 = 0,
    /**< No Shifting */
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_1 = 1,
    /**< 1 bit left shift/shift up the offset */
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_2 = 2,
    /**< 2 bit left shift/shift up the offset */
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_3 = 3,
    /**< 3 bit left shift/shift up the offset */
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_4 = 4,
    /**< 4 bit left shift/shift up the offset */
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_5 = 5,
    /**< 5 bit left shift/shift up the offset */
    VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed,
     *   will always be contained in int */
} vpsissIsif2DLscOffsetShiftup_t; /**< vpsissIsif2DLscOffsetShiftup_t */

/**
 *  \brief Structure containing ISIF gain and offset configuration.
 *         Sets these parameters in WB submodule, Also used for selecting
 *         output to which this WB is applied
 */
typedef struct vpsissIsifGainOfstConfig
{
    uint32_t gain[FVID2_BAYER_COLOR_COMP_MAX];
    /**< Gain for each color component,
     *   the format: U12Q9. Range: 0 to 7+511/512*/
    uint32_t offset;
    /**< Offset value adjustment,
     *   Range is 0 to 4095 */
    uint32_t gainEnable[VPS_ISS_ISIF_MAX_OUTPUT];
    /**< Flag to enable gain multiplication for IPIPE, H3A, Memory outputs */
    uint32_t offsetEnable[VPS_ISS_ISIF_MAX_OUTPUT];
    /**< Flag to enable offset adjustment for IPIPE, H3A, Memory outputs */
} vpsissIsifGainOfstConfig_t; /**< vpsissIsifGainOfstConfig_t */

/**
 *  \brief Used to configure the mode of Vertical Line Defect Correction block
 */
typedef enum vpsissIsifVfdcMethod
{
    VPS_ISS_ISIF_VDFC_METHOD_2_NON_SATU_PIX = 0x0,
    /**< Method 2 -
     *      Saturated pixels  - Will passed as received.
     *      NON-Saturated pixels - Corrected by subtracting with defined value.
     *          Seperate value to be subtracted for pixels that are above
     *              defective pixels.
     *          Seperate value to be subtracted for pixels that are below
     *              defective pixels.
     *          All above three values are configureable.
     *          Subtraction of pixels that are above defective pixels can be
     *              disabled. */
    VPS_ISS_ISIF_VDFC_METHOD_2_SATU_PIX = 0x1,
    /**< Method 2 - Same as VPS_ISS_ISIF_VDFC_METHOD_2_NON_SATU_PIX with
     *      horizontal interpolation for saturated pixels.
     *      n-2, n-1, n, n+1, n+2.
     *      saturated pixel value = avg ((n-2) + n+2) / 2 */

    VPS_ISS_ISIF_VDFC_METHOD_1_HAVG = 0x2,
    /**< Method 1 - Defective pixel value is replaced by average of 2 pixels.
     *      n-2, n-1, n, n+1, n+2.
     *      defective pixel value = avg ((n-2) + n+2) / 2 */

    VPS_ISS_ISIF_VDFC_DISABLE = 0xFF,
    /** VFDC is disabled */

    VPS_ISS_ISIF_VDFC_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed,
                                    will always be contained in int */
} vpsissIsifVfdcMethod_t;   /**< vpsissIsifVfdcMethod_t */

/**
 *  \brief VFDC config / control structure. Used to enable / disable and
 *          configure VFDC.
 */
typedef struct vpsissIsifVfdcConfig
{
    vpsissIsifVfdcMethod_t mode;
    /**< Mode of VFDC operation. When mode is != VPS_ISS_ISIF_VDFC_DISABLE
     *      The configuration below would be applied and module is functional
     *      Otherwise module is disabled. */
    uint32_t               shiftUp;
    /**< Controls shifting up (left shift) of defective pixel values before
     *      subtracting with defined levels.
     *      This is not applicable when mode is VPS_ISS_ISIF_VDFC_METHOD_1_HAVG.
     *      Valid values are between 0 - 6. */
    uint32_t               correctAbovePixels;
    /**< A non zero values indicated pixels that are above defective pixels
     *      would also be corrected. Applicable to all modes of operation */
    uint32_t               satVal;
    /**< Specify the number that marks begining values of saturated pixels.
     *      i.e. pixel value >= satVal will be considered treated saturated.
     *      valid values are 0 - 4095*/
    uint32_t               subtractValues[3U][VPS_ISS_ISIF_VFDC_MAX_PIX_CORR];
    /**< Applicable when mode is != VPS_ISS_ISIF_VDFC_METHOD_1_HAVG.
     *      Specify the values that are to be subtracted for defective pixels
     *      subtractValues [0][n] - For defective pixels
     *      subtractValues [1][n] - For pixels that are above defective pixels
     *      subtractValues [2][n] - for pixels that are below defective pixels.
     *      Valid rage 0 - 255 */
    uint32_t               numPixToBeCorrected;
    /**< Configure the number of pixels to be corrected. It should not be > 7 */
    uint32_t               defectivePixCoOr[2U][VPS_ISS_ISIF_VFDC_MAX_PIX_CORR];
    /**< Defined co-ordinates of defective pixels.
     *      A defective pixel location is to be defined as
     *      defectivePixCoOr[0][n] = V co-ordinate
     *      defectivePixCoOr[1][n] = H co-ordinate
     *      Should always start from left to right.
     *      Maximum of 8 defects could be corrected */
} vpsissIsifVfdcConfig_t; /**< vpsissIsifVfdcConfig_t */

/**
 *  \brief Blank Clamp config / control structure. Used to enable / disable and
 *         configure black Clamping.
 *         Currently only supported for setting up the DC Offset
 */
typedef struct vpsissIsifBlackClampConfig
{
    Int32 dcOffset;
    /**< DC Offset, This value is added to the incoming pixels,
     *   regardless whether black clamping is enabled or not
     *   This value is in S13Q0 format. */
} vpsissIsifBlackClampConfig_t; /**< vpsissIsifBlackClampConfig_t */

/**
 *  \brief 2D Lens Shading Configuration. Used to enable / disable and
 *         configure Lens shading module.
 */
typedef struct vpsissIsif2DLscConfig
{
    uint32_t                         enable;
    /**< Flag to enable/disable LSC */

    Fvid2_CropConfig                 activeReg;
    /**< Used to define the active region for the LSC in the complete
         frame recieved by ISIF */
    Fvid2_PosConfig                  startPos;
    /**< Offset within active region, specified in complete frame
         Must be less than M/N down scaling factor
         Must be even */

    vpsissIsif2DLscDownScaleFactor_t horzDownScale;
    /**< Horizontal Down scaling factor,
         Used to configure downscaling factor of the gain and offset table */
    vpsissIsif2DLscDownScaleFactor_t vertDownScale;
    /**< Vertical Down scaling factor,
         Used to configure downscaling factor of the gain and offset table */
    vpsissIsif2DLscGainFormat_t      gainFormat;
    /**< Format of the gain entry in the table */

    uint32_t                         gainTableAddr;
    /**< Gain Table start Address, must be 4byte aligned */
    uint32_t                         offsetTableAddr;
    /**< Offset Table Start address, must be 4byte aligned */
    uint32_t                         gainTablePitch;
    /**< Line offset/pitch for Gain table, must be multiple of 4/42bit */
    uint32_t                         offsetTablePitch;
    /**< Line offset/pitch for Offset table, must be multiple of 4/42bit */

    uint32_t                         enableOffset;
    /**< TRUE: enables Offset control in LSC,
               offset is applied before gain.
               Used only for 8bit mode
         FALSE: disables offset in LSC */
    uint32_t                         offsetScaleFactor;
    /**< Offset Scaling factor in U8Q7 format,
         Range from 0 to 1+127/128 */
    vpsissIsif2DLscOffsetShiftup_t   offsetShiftup;
    /**< Offset value, before being aplpied, is shifted by this
         amount and scaled up using offsetScaleFactor */
} vpsissIsif2DLscConfig_t; /**< vpsissIsif2DLscConfig_t */

/**
 *  \brief Resizer control structure, passed as an argument to
 *         VPS_ISS_IPIPE_IOCTL_CTRL.
 */
typedef struct vpsissIsifCtrl
{
    vpsissIsifModule_t            module;
    /**< Id of the module to be configured,
     *   could be either Input, ResizerA or ResizerB
     *   Appropriate structure pointer need to be assigned when one of
     *   these modules is selected here */
    vpsissIsifGainOfstConfig_t   *wbCfg;
    /**< Pointer to structure containing Gains and Offsets for
     *   all three outputs from ISIF,
     *   should not be null when module is set to
     *   VPS_ISS_ISIF_MODULE_WB */
    vpsissIsifVfdcConfig_t       *vfdcCfg;
    /**< Pointer to vertical defect pixel correction configuration.
     *      Should not be NULL when module is set to VPS_ISS_ISIF_MODULE_VDFC */
    vpsissIsifBlackClampConfig_t *blkClampCfg;
    /**< Pointer to Black Clamping configuration.
     *      Should not be NULL when module is set to
     *      VPS_ISS_ISIF_MODULE_BLACK_CLAMP */

    vpsissIsif2DLscConfig_t      *lscCfg;
    /**< Pointer to 2D Lens Shading Configuration
     *      Should not be NULL when module is set to
     *      VPS_ISS_ISIF_MODULE_2D_LSC */
} vpsissIsifCtrl_t; /**< vpsissIsifCtrl_t */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_CFG_ISIF_H_ */

