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
 *  \file vpshal_issipipe.h
 *
 *  \brief HAL Header file for IPIPE
 *  This file exposes the HAL APIs for ISS IPIPE module
 *
 */

#ifndef VPSHAL_ISS_IPIPE_H_
#define VPSHAL_ISS_IPIPE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/iss/vps_cfgipipe.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Notes
 *  1, Since IPIPE_INT_LAST_PIX can be used for transferring DPC
 *     initialization data and / or gamma data, we need one register to
 *     let the design know how many accesses need to be performed before
 *     clearing the DMA request. The ISP5_CTRL.DMA3_CFG register needs
 *     to be configured to reflect the type of transfer corresponding
 *     to the DMA request
 *  3, How does bits in the register IPIPE_GCK_PIX work? Does it disable
 *     the clock for the given module so that we cannot even access
 *     the register of that module? Do we have to disable the modules
 *     in GCK_PIX to disable the IPIPE completely from ISS?
 *  4, Do we need to write to EDOF register?
 *  5, DAA configuration is required to be only when CFA mode has DAA enabled
 *     correct?
 */

/**
 *  \brief IPIPE maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_IPIPE_MAX_INST               (1U)

/**
 *  \brief IPIPE number of the CSC coefficients.
 */
#define ISSHAL_IPIPE_CSC_NUM_COEFF          (VPS_ISS_IPIPE_CSC_NUM_COEFF)

/* Control IOCTLs supported by IPIPE */

/**
 *  \brief Ioctl for setting White Balance Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_WBCFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             0U)

/**
 *  \brief Ioctl for setting CFA Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_CFACFG       (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             1U)

/**
 *  \brief Ioctl for setting RGB2RGB1 Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_RGB2RGB1CFG  (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             2U)

/**
 *  \brief Ioctl for setting RGB2RGB2 Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_RGB2RGB2CFG  (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             3U)

/**
 *  \brief Ioctl for setting RGB2YUV Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_RGB2YUVCFG   (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             4U)

/**
 *  \brief Ioctl for setting DPC LUT Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_DPCLUTCFG    (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             5U)

/**
 *  \brief Ioctl for setting DPC OTF Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_DPCOTFCFG    (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             6U)

/**
 *  \brief Ioctl for setting DPC OTF Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_YUVCFG       (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             7U)

/**
 *  \brief Ioctl for setting Gamma Correction Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_GAMMACFG     (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                             8U)

/**
 *  \brief Ioctl for setting 3D LUT Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_3D_LUTCFG    (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                             9U)

/**
 *  \brief Ioctl for setting YEE Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_EECFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                             0xaU)

/**
 *  \brief Ioctl for setting GIC Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_GICCFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                              0xbU)

/**
 *  \brief Ioctl for setting GIC Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_LSCCFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                              0xcU)

/**
 *  \brief Ioctl for setting NF1 Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_NF1CFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                              0xdU)

/**
 *  \brief Ioctl for setting NF2 Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_NF2CFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                              0xeU)

/**
 *  \brief Ioctl for setting IPIPE Source Configuration
 */
#define ISSHAL_IOCTL_IPIPE_SET_SRCCFG        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                              0xfU)

/**
 *  \brief ioctl for updating luts
 */
#define ISSHAL_IOCTL_IPIPE_UPDATE_LUT        (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN  + \
                                              0x10U)
/**
 *  \brief Ioctl for Getting Default Configuration, this ioctl fills
 *         up complete isshalh3aConfig_t structure and returns.
 */
#define ISSHAL_IOCTL_IPIPE_GET_DEFAULTCFG   (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             0x11U)
/**
 *  \brief Ioctl used to update to enable / disable Edge Enhancer sub-block of
 *          of ISR.
 */
#define ISSHAL_IOCTL_IPIPE_EE_ENABLE_DISABLE (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                              0x12U)

#if (ISSHAL_IOCTL_IPIPE_EE_ENABLE_DISABLE > VPS_HAL_ISS_IOCTL_IPIPE_END)
    #error "Increase VPS_HAL_ISS_IOCTL_IPIPE_NUM in vpshal_iss.h file"
#endif

/**
 *  \brief Enum for selecting IPIPE sub module id
 */
typedef enum isshalipipeModuleId
{
    ISSHAL_IPIPE_MODULE_NONE           = 0x0,
    ISSHAL_IPIPE_MODULE_SRC_CFG        = 0x1,
    ISSHAL_IPIPE_MODULE_DPC_LUT        = 0x2,
    ISSHAL_IPIPE_MODULE_DPC_OTF        = 0x4,
    ISSHAL_IPIPE_MODULE_NOISE_FILTER_1 = 0x8,
    ISSHAL_IPIPE_MODULE_NOISE_FILTER_2 = 0x10,
    ISSHAL_IPIPE_MODULE_GIC            = 0x20,
    ISSHAL_IPIPE_MODULE_WB             = 0x40,
    ISSHAL_IPIPE_MODULE_CFA            = 0x80,
    ISSHAL_IPIPE_MODULE_RGB_RGB_1      = 0x100,
    ISSHAL_IPIPE_MODULE_GAMMA          = 0x200,
    ISSHAL_IPIPE_MODULE_RGB_RGB_2      = 0x400,
    ISSHAL_IPIPE_MODULE_3D_LUT         = 0x800,
    ISSHAL_IPIPE_MODULE_RGB_TO_YUV     = 0x1000,
    ISSHAL_IPIPE_MODULE_LSC            = 0x2000,
    ISSHAL_IPIPE_MODULE_GBCE           = 0x4000,
    ISSHAL_IPIPE_MODULE_YEE            = 0x8000,
    ISSHAL_IPIPE_MODULE_CAR            = 0x10000,
    ISSHAL_IPIPE_MODULE_CGS            = 0x20000,
    ISSHAL_IPIPE_MODULE_BSC            = 0x40000,
    ISSHAL_IPIPE_MODULE_HST            = 0x80000,
    ISSHAL_IPIPE_MODULE_BOXCAR         = 0x100000,
    ISSHAL_IPIPE_MODULE_YUV444_YUV422  = 0x200000,
    ISSHAL_IPIPE_MODULE_FORCE_INT      = 0x7FFFFFFF
                                         /**< This will ensure enum is not packed, will always be contained in int */
} isshalipipeModuleId_t;

/**
 *  \brief Enum for selecting IPIPE datapath
 */
typedef enum isshalipipeSelDataPath
{
    ISSHAL_IPIPE_DATA_PATH_RAW_YUV422 = 0x0,
    /**< input data is in RAW BAYER format and output data format YUV422 */
    ISSHAL_IPIPE_DATA_PATH_RAW_RAW = 0x1,
    /**< The data are output after the White Balance module. It
     *   enables to bypass a large part of the IPIPE module */
    ISSHAL_IPIPE_DATA_PATH_RAW_DISABLED = 0x2,
    /**< input data is in RAW BAYER format and output is disabled */
    ISSHAL_IPIPE_DATA_PATH_YUV422_YUV422 = 0x3,
    /**< input data and output data
     *formats are in YUV422 format */
    ISSHAL_IPIPE_DATA_PATH_FORCE_INT = 0x7FFFFFFF
                                       /**< This will ensure enum is not packed, will always be contained in int */
} isshalipipeSelDataPath_t;

/**
 *  \brief Enum to define the various IPIPE instance.
 */
typedef enum isshalipipeInstId
{
    ISSHAL_IPIPE_INST_0 = 0,
    /**< Ipipe Instance Id 0. */
    ISSHAL_IPIPE_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_IPIPE_INST_FORCE_INT = 0x7FFFFFFF
                                  /**< This will ensure enum is not packed, will always be contained in int */
} isshalipipeInstId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalipipeSrcConfig
{
    Fvid2_DataFormat         inputDataFormat;
    /**< Input Data Format from IPIPEIF,
     *   Valid input formats are
     *      FVID2_DF_BAYER_GRBG,
     *      FVID2_DF_BAYER_RGGB,
     *      FVID2_DF_BAYER_BGGR,
     *      FVID2_DF_BAYER_GBRG,
     *      FVID2_DF_YUV422I_YUYV */
    vpsissIpipeSelDataPath_t dataPath;
    /**< Selects the input and output data format and depending on
     *   that the path in the IPIPE for the input data */

    Fvid2_ChromaPos          chromaPos;
    /**< Chroma  sumpling postion in YUV422 to 444
     *   Used only when input and output format are YUV422 */

    Fvid2_CropConfig         procWin;
    /**< Window to be processed, IPIPE module crops input image to this
     *   size and uses this size for all its processing,
     *   CropStartX is in terms of number of clocks */
    uint32_t                 wrtEnable;
    /**< Enables the use of the wrt signal from the IPIPEIF */
} isshalipipeSrcConfig_t;

/**
 *  \brief convert VPS structure to hal structure
 */
typedef vpsissIpipeWbConfig_t isshalipipeWbConfig_t;

typedef vpsissIpipeCfaConfig_t isshalipipeCfaConfig_t;

typedef vpsissIpipeRgb2RgbConfig_t isshalipipeRgb2RgbConfig_t;

typedef vpsissIpipeRgb2YuvConfig_t isshalipipeRgb2YuvConfig_t;

typedef vpsissIpipeYuvPhsConfig_t isshalipipeYuvPhsConfig_t;

typedef struct isshalipipeConfig
{
    uint32_t                   moduleId;
    /**< Select the feature to be enabled/configured,
     *   Multiple modules can be configured by ORing bitmasks of the module,
     *   see #isshalipipeModuleId_t for the valid values*/

    isshalipipeSrcConfig_t     srcCfg;
    /** Input Source Config */

    isshalipipeWbConfig_t      wbCfg;
    /**< White Balance Parameter Configuration */

    isshalipipeCfaConfig_t     cfaCfg;
    /**< CFA Parameter Configuration */

    isshalipipeRgb2RgbConfig_t rgb2Rgb1;
    /**< RGB2RGB Blending Module */

    isshalipipeRgb2RgbConfig_t rgb2Rgb2;
    /**< RGB2RGB Blending Module */

    isshalipipeRgb2YuvConfig_t rgb2Yuv;
    /**< RGB2YUV Blending Module */

    isshalipipeYuvPhsConfig_t  yuvPhs;
    /**< Chroma down sampler mode, used for converting YUV444 to YUV422
     *   Valid only for RAW Input and YUV output, ie IPIPE_SRC_FMT.FMT = 0
     *   Note: When the chroma output is cosited, and that downsampling
     *         is enabled in the RESIZER module, need to take care
     *         that the averager disrupts the relative phase for luma
     *         and chroma color components.
     *         The RZA_H_PHS_ADJ and RZB_H_PHS_ADJ registers need to be
     *         used to fix the disruption
     *         Also make sure that the RSZ_YUV_PHS.POS = IPIPE_YUV_PHS.POS
     *   Configured when ISSHAL_IPIPE_MODULE_YUV444_YUV422 module is selected */

    vpsissIpipeDpcOtfConfig_t dpcOtf;
    /**< DPC On The Fly config */
    vpsissIpipeDpcLutConfig_t dpcLut;
    /**< DPC based on LUT */
    vpsissIpipeGammaConfig_t  gammaCfg;
    /**< Gamma Correction Configuration */
    vpsissIpipe3DLutConfig_t  colorConvert3DLutCfg;
    /**< 3D Lut Configuration */
    vpsissIpipeEeConfig_t     eeCfg;
    /**< YEE/Edge Enhancer Configuration */
    vpsissIpipeGicConfig_t    gicCfg;
    /**< GIC Configuration */
    vpsissIpipeLscConfig_t    lscCfg;
    /**< LSC Configuration */
    vpsissIpipeNf2Config_t    nf1Cfg;
    /**< Noise Filter 1 Configuration */
    vpsissIpipeNf2Config_t    nf2Cfg;
    /**< Noise Filter 2 Configuration */
} isshalipipeConfig_t;

/**
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalipipeInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalipipeInstId. */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t gammaLutRedAddr;
    uint32_t gammaLutGreenAddr;
    uint32_t gammaLutBlueAddr;

    uint32_t lut3DBank0Addr;
    uint32_t lut3DBank1Addr;
    uint32_t lut3DBank2Addr;
    uint32_t lut3DBank3Addr;
    uint32_t yeeLutAddr;
    uint32_t yeeLutSize;
} isshalipipeInstParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issipipeInit
 *  \brief IPIPE init function.
 *
 *  Initializes IPIPE objects.
 *  This function should be called before calling any of IPIPE HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalipipeInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issipipeInit(UInt32                         numInst,
                            const isshalipipeInstParams_t *instPrms,
                            Ptr                            arg);

/**
 *  VpsHal_issipipeDeInit
 *  \brief IPIPE HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issipipeDeInit(Ptr arg);

/**
 *  \brief This function should be called prior to calling any of the IPIPE HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issipipeOpen(const isshalOpenParams_t *openPrms,
                                  Ptr                       arg);

/**
 *  VpsHal_issipipeClose
 *  \brief This functions closes the ipipe handle and after call to this
 *  function, ipipe handle is not valid.
 *
 *  \param handle         Requested IPIPE instance
 */
int32_t VpsHal_issipipeClose(VpsHal_Handle handle,
                             Ptr           arg);

/**
 *  \brief Sets the entire IPIPE configuration to the IPIPE registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issipipeConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeSetConfig(VpsHal_Handle              handle,
                                 const isshalipipeConfig_t *cfg,
                                 Ptr                        arg);

/**
 *  VpsHal_issipipeGetConfig
 *  \brief Gets the entire IPIPE configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issipipeConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeGetConfig(VpsHal_Handle        handle,
                                 isshalipipeConfig_t *config);

/**
 *  VpsHal_issipipeControl
 *  \brief IPIPE specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeControl(VpsHal_Handle handle,
                               UInt32        cmd,
                               Ptr           cmdArgs,
                               Ptr           arg);

/**
 *  \brief IPIPE Api for enabling the module. The module starts a processing
 *         from the next rising edge of the VD. If the processing mode
 *         of the IPIPE module is one shot, it will be cleared/stoped
 *         immediately after the processing has started
 *
 *  \param handle           Instance handle
 *  \param procMode         Processing Mode, ie one shot or free running
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/**
 *  \brief IPIPE Api for disablinh the module. Used to stop module when it is
 *         configured in the free running mode
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeStop(VpsHal_Handle handle, Ptr arg);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_IPIPE_H_ */
