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
 *  \file vpshal_issisif.h
 *
 *  \brief HAL Header file for ISIF
 *  This file exposes the HAL APIs for ISS ISIF module
 *
 */

#ifndef VPSHAL_ISS_ISIF_H_
#define VPSHAL_ISS_ISIF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/iss/vps_cfgisif.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief ISIF maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_ISIF_MAX_INST               (1U)

/* Control IOCTLs supported by IPIPE */

/**
 *  \brief Ioctl for setting White Balance Configuration
 */
#define ISSHAL_IOCTL_ISIF_SET_WBCFG        (VPS_HAL_ISS_IOCTL_ISIF_BEGIN + \
                                            0U)
/**
 *  \brief Ioctl for Getting Default Configuration, this ioctl fills
 *         up complete isshalisifConfig_t structure and returns.
 */
#define ISSHAL_IOCTL_ISIF_GET_DEFAULTCFG   (VPS_HAL_ISS_IOCTL_ISIF_BEGIN + \
                                            1U)

/**
 *  \brief Ioctl to configure vertical line defect correction sub-module.
 *          No error checks performed. Caller ensure all config is valid.
 *  CAUTION - When number of pixels to be corrected is less than 8,
 *          This function updates the co-ordinate to mark unused entries as
 *          invalid. In short memory for all 8 pixel should be allocated.
 */
#define ISSHAL_IOCTL_ISIF_SET_VFDC_CFG  (ISSHAL_IOCTL_ISIF_GET_DEFAULTCFG + \
                                         1U)

/**
 *  \brief Ioctl for setting Black clamping Configuration
 *         No error checks performed. Caller ensure all config is valid.
 */
#define ISSHAL_IOCTL_ISIF_SET_BLACK_CLAMP_CFG (ISSHAL_IOCTL_ISIF_SET_VFDC_CFG+ \
                                               1U)

/**
 *  \brief Ioctl to configure input frame size.
 *          Primarily used to for re-sizing YUV420 input data type.
 *          Where Luma is processed followed by chroma.
 *
 *  \warning This should be re-enterent, callable from an ISR.
 */
#define ISSHAL_IOCTL_ISIF_SET_IP_FRM_SIZE \
    (ISSHAL_IOCTL_ISIF_SET_BLACK_CLAMP_CFG + 1U)

/**
 *  \brief Ioctl for setting 2d lsc configuration.
 *  Caution: caller should make sure that isif lsc is in correct state,
 *           before enabling/disabling it.
 */
#define ISSHAL_IOCTL_ISIF_SET_2D_LSC_CFG \
    (ISSHAL_IOCTL_ISIF_SET_IP_FRM_SIZE + 1U)

#if (ISSHAL_IOCTL_ISIF_SET_2D_LSC_CFG > VPS_HAL_ISS_IOCTL_ISIF_END)
    #error "Increase VPS_HAL_ISS_IOCTL_ISIF_NUM in vpshal_iss.h file"
#endif

/**
 *  \brief Enum to define the various ISIF instance.
 */
typedef enum isshalisifInstId
{
    ISSHAL_ISIF_INST_0 = 0,
    /**< Isif Instance Id 0. */
    ISSHAL_ISIF_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_ISIF_INST_FORCE_INT = 0x7FFFFFFF
                                 /**< This will ensure enum is not packed, will always be contained in int */
} isshalisifInstId_t;

/**
 *  \brief Enum to select the MSB bit of the ISIF input with which
 *         MSB bit of the input is connected.
 */
typedef enum isshalisifInDataMsbPos
{
    ISSHAL_ISIF_INPUT_MSB_POS_BIT15 = 0x0,
    /**< MSB Bit is Bit 15 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT14 = 0x1,
    /**< MSB Bit is Bit 14 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT13 = 0x2,
    /**< MSB Bit is Bit 13 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT12 = 0x3,
    /**< MSB Bit is Bit 12 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT11 = 0x4,
    /**< MSB Bit is Bit 11 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT10 = 0x5,
    /**< MSB Bit is Bit 10 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT9 = 0x6,
    /**< MSB Bit is Bit 9 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT8 = 0x7,
    /**< MSB Bit is Bit 8 */
    ISSHAL_ISIF_INPUT_MSB_POS_BIT7 = 0x8,
    /**< MSB Bit is Bit 7 */
    ISSHAL_ISIF_INPUT_MSB_POS_FORCE_INT = 0x7FFFFFFF
                                          /**< This will ensure enum is not packed, will always be contained in int */
} isshalisifInDataMsbPos_t;

/**
 *  \brief Enum for selecting the CFA pattern
 */
typedef enum isshalisifCfaPattern
{
    ISSHAL_ISIF_CFG_PATTERN_MOSAIC = 0x0,
    /**< CFA Pattern is Mosaic as shown below
     *   G R G R G R
     *   B G B G B G */
    ISSHAL_ISIF_CFG_PATTERN_STRIP = 0x1,
    /**< CGA Pattern is Strip as shown below
     *  R G B R G B R G B
     *  R G B R G B R G B*/
    ISSHAL_ISIF_CFG_PATTERN_FORCE_INT = 0x7FFFFFFF
                                        /**< This will ensure enum is not packed, will always be contained in int */
} isshalisifCfaPattern_t;

/**
 *  \brief Enum defining Different sub-modules of the ISIF modules
 *         use for configuring the submodule.
 */
typedef enum isshalisifModuleId
{
    ISSHAL_ISIF_MODULE_NONE = 0x0,
    /**< None of the modules */
    ISSHAL_ISIF_MODULE_SRC_CFG = 0x1,
    /**< ISIF Source/Input Configuration */
    ISSHAL_ISIF_MODULE_OUTPUT_CFG = 0x2,
    /**< ISIF Output Configuration */
    ISSHAL_ISIF_MODULE_GAIN_OFST_CFG = 0x4,
    /**< ISIF Gain Offset/White Balance Configuration */
    ISSHAL_ISIF_MODULE_VFDC_CFG = 0x8,
    /**< ISIF Vertical Line defect pixel correction configuration */
    ISSHAL_ISIF_MODULE_BLACK_CLAMP_CFG = 0x10,
    /**< ISIF Black Clamp Configuration */
    ISSHAL_ISIF_MODULE_2D_LSC_CFG = 0x20,
    /**< ISIF 2D LSC Configuration */
    ISSHAL_ISIF_MODULE_FORCE_INT = 0x7FFFFFFF
                                   /**< This will ensure enum is not packed, will always be contained in int */
} isshalisifModuleId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief structure containing ISIF input configuration. It is
 *         used to select/configure HD/VD polarity, direction,
 *         input dataformat, Input Video Size etc.
 */
typedef struct isshalisifSrcConfig
{
    uint32_t                 isHdVdOut;
    /**< Flag to set hdvd signal output */
    uint32_t                 isFidOut;
    /**< Flag to set the FID signal output */
    uint32_t                 isInDataInvt;
    /**< Flag to set input data to be in inverted ie one's complete */
    Fvid2_Polarity           hdPol;
    /**< HD Signal Polarity */
    Fvid2_Polarity           vdPol;
    /**< VD Signal Polarity */
    Fvid2_DataFormat         inDataFormat;
    /**< Input DataFormat,
     *      FVID2_DF_BAYER_GRBG,
     *      FVID2_DF_BAYER_RGGB,
     *      FVID2_DF_BAYER_BGGR,
     *      FVID2_DF_BAYER_GBRG,
     *      FVID2_DF_YUV422I_YUYV
     *      FVID2_DF_YUV422I_UYVY */
    Fvid2_VideoIfWidth       vidIfWidth;
    /**< Video Interface Size,
     *   for YUV dataformat, only 8 or 16bit interface is valid */
    uint32_t                 hdWidth;
    /**< Size of the HD Pulse */
    uint32_t                 vdWidth;
    /**< Size of the VD Pulse */
    uint32_t                 pixelsPerLine;
    /**< Number of pixel clock periods in one line HD period
     *   Used only when HD/VD signal direction is output */
    uint32_t                 linesPerFrame;
    /**< Number of lines per frame,
     *   Used only when HD/VD signal direction is output */

    isshalisifInDataMsbPos_t msbPos;
    /**< Select MSB position of Input Data */
    isshalisifCfaPattern_t   cfaPattern;
    /**< Select the CFA Pattern */
    uint32_t                 ycInSwap;
    /**< When operating in YUV422, its expected that Y is available on
            MS byte and UV on the LS byte. i.e. data format is
            FVID2_DF_YUV422I_UYVY.
            In cases where the input format is FVID2_DF_YUV422I_YUYV
            set, this flag to TRUE to indicate a swap to be done at ISIF source.
            VALID - only when data inDataFormat is either FVID2_DF_YUV422I_YUYV
            OR FVID2_DF_YUV422I_UYVY.
            */
} isshalisifSrcConfig_t;

/**
 *  \brief Structure indirection to maintain naming convenctions
 */
typedef vpsissIsifGainOfstConfig_t isshalisifGainOfstConfig_t;

/**
 *  \brief Structure indirection to maintain naming convenctions
 */
typedef vpsissIsifVfdcConfig_t isshalisifVfdcConfig_t;

/**
 *  \brief Structure indirection to maintain naming convenctions
 */
typedef vpsissIsifBlackClampConfig_t isshalisifBlackClampConfig_t;

/**
 *  \brief Structure containing Complete ISIF configuration.
 */
typedef struct isshalisifConfig
{
    uint32_t                     moduleId;
    /**< Select the feature to be enabled/configured,
     *   Multiple modules can be configured by ORing bitmasks of the module,
     *   see #isshalisifModuleId_t for the valid values*/

    isshalisifSrcConfig_t        srcCfg;
    /**< Input Source Configuration */

    isshalisifGainOfstConfig_t   wbCfg;
    /**< Gain Offset/WB configuration */

    isshalisifVfdcConfig_t       vfdcCfg;
    /**< Vertical Defect Pixel Correction control config */

    isshalisifBlackClampConfig_t blkClampCfg;
    /**< Black Clamping Configuration */

    vpsissIsif2DLscConfig_t      lscCfg;
    /**< LensShading correction configuration */
} isshalisifConfig_t;

/**
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalisifInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalisifInstId. */
    uint32_t baseAddress;
    /**< Register base address */
} isshalisifInstParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issisifInit
 *  \brief ISIF init function.
 *
 *  Initializes ISIF objects.
 *  This function should be called before calling any of ISIF HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalisifInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issisifInit(UInt32                        numInst,
                           const isshalisifInstParams_t *instPrms,
                           Ptr                           arg);

/**
 *  VpsHal_issisifDeInit
 *  \brief ISIF HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issisifDeInit(Ptr arg);

/**
 *  VpsHal_issisifOpen
 *  \brief This function should be called prior to calling any of the ISIF HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issisifOpen(const isshalOpenParams_t *openPrms,
                                 Ptr                       arg);

/**
 *  VpsHal_issisifClose
 *  \brief This functions closes the isif handle and after call to this
 *  function, isif handle is not valid.
 *
 *  \param handle         Requested ISIF instance
 */
int32_t VpsHal_issisifClose(VpsHal_Handle handle,
                            Ptr           arg);

/**
 *  \brief Sets the entire ISIF configuration to the ISIF registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issisifConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issisifSetConfig(VpsHal_Handle       handle,
                                isshalisifConfig_t *cfg,
                                Ptr                 arg);

/**
 *  VpsHal_issisifGetConfig
 *  \brief Gets the entire ISIF configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issisifConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issisifGetConfig(VpsHal_Handle       handle,
                                isshalisifConfig_t *config);

/**
 *  VpsHal_issisifControl
 *  \brief ISIF specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issisifControl(VpsHal_Handle handle,
                              UInt32        cmd,
                              Ptr           cmdArgs,
                              Ptr           arg);

/**
 *  \brief ISIF Api for enabling the module. The module starts a processing
 *         from the next rising edge of the VD. If the processing mode
 *         of the ISIF module is one shot, it will be cleared/stoped
 *         immediately after the processing has started
 *
 *  \param handle           Instance handle
 *  \param procMode         Processing Mode, ie one shot or free running
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issisifStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  \brief ISIF Api for disablinh the module. Used to stop module when it is
 *         configured in the free running mode
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issisifStop(VpsHal_Handle handle, Ptr arg);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_ISIF_H_ */
