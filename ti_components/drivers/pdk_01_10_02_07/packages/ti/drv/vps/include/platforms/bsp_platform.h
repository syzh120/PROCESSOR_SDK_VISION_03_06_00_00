/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \defgroup BSP_DRV_PLATFORM_API Platform Specific API
 *  @{
 */

/**
 *  \file bsp_platform.h
 *
 *  \brief Interface file to the platform specific functions abstraction APIs.
 *
 */

#ifndef BSP_PLATFORM_H_
#define BSP_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Defines SOC specific IO PAD Register configuration  */

/** \brief Defines Default IO PAD Register configuration except mux mode field -
 *    Disables weak Pull Up/Down, Pull Up is selected, Receive mode is enabled,
 *    Slow slew is selected
 */
#define BSP_PLATFORM_IOPAD_CFG_DEFAULT                  ((UInt32)0xFF)
/** \brief Defines IO PAD Register configuration for PULLUDENABLE field  -
 *   Enables weak Pull Up/Down
 */
#define BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE      ((UInt32) 0x00U)
/** \brief Defines IO PAD Register configuration for PULLUDENABLE field  -
 *   Disables weak Pull Up/Down
 */
#define BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE     ((UInt32) 0x01U)
/** \brief Defines IO PAD Register configuration for PULLTYPESELECT field  -
 *   Pull Down is selected
 */
#define BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN      ((UInt32) 0x00U)
/** \brief Defines IO PAD Register configuration for PULLTYPESELECT field  -
 *   Pull Up is selected
 */
#define BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP        ((UInt32) 0x02U)
/** \brief Defines IO PAD Register configuration for INPUTENABLE field  -
 *   Receive mode is disabled
 */
#define BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT          ((UInt32) 0x00U)
/** \brief Defines IO PAD Register configuration for INPUTENABLE field  -
 *   Receive mode is enabled
 */
#define BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI           ((UInt32) 0x04U)

/**
 *  \brief Platform ID.
 */
typedef enum
{
    BSP_PLATFORM_ID_UNKNOWN = 0x0001U,
    /**< Unknown platform. */
    BSP_PLATFORM_ID_EVM = 0x0002U,
    /**< EVMs. */
    BSP_PLATFORM_ID_SIM = 0x0004U,
    /**< Simulator. */
    BSP_PLATFORM_ID_ZEBU = 0x0008U,
    /**< Zebu presilicon platform. */
    BSP_PLATFORM_ID_VIRTIO = 0x0010U,
    /**< Virtio presilicon platform. */
    BSP_PLATFORM_ID_MAX = 0xFFFFU
                          /**< Max Platform ID. */
} Bsp_PlatformId;

/**
 *  \brief SOC ID.
 */
typedef enum
{
    BSP_PLATFORM_SOC_ID_UNKNOWN = 0x0001U,
    /**< Unknown SOC. */
    BSP_PLATFORM_SOC_ID_TDA2XX = 0x0002U,
    /**< TDA2XX SOC. */
    BSP_PLATFORM_SOC_ID_TI814X = 0x0004U,
    /**< TI814x SOC. */
    BSP_PLATFORM_SOC_ID_TI8149 = 0x0008U,
    /**< TI8149 SOC. */
    BSP_PLATFORM_SOC_ID_TI811X = 0x0010U,
    /**< TI811x SOC. */
    BSP_PLATFORM_SOC_ID_OMAP5X = 0x0020U,
    /**< OMAP5430 SOC. */
    BSP_PLATFORM_SOC_ID_TDA3XX = 0x0040U,
    /**< TDA3XX SOC. */
    BSP_PLATFORM_SOC_ID_DRA75X = 0x0080U,
    /**< DRA75x SOC. */
    BSP_PLATFORM_SOC_ID_TDA2EX = 0x0100U,
    /**< TDA2EX SOC. */
    BSP_PLATFORM_SOC_ID_AM572X = 0x0200U,
    /**< AM572X SOC */
    BSP_PLATFORM_SOC_ID_AM571X = 0x0400U,
    /**< AM571X SOC */
    BSP_PLATFORM_SOC_ID_TDA2PX = 0x0800U,
    /**< TDA2PX SOC. */
    BSP_PLATFORM_SOC_ID_AM574X = 0x1000U,
    /**< AM574X SOC */
    BSP_PLATFORM_SOC_ID_MAX = 0xFFFFU
                              /**< Max SOC ID. */
} Bsp_PlatformSocId;

/**
 *  \brief Core ID.
 */
typedef enum
{
    BSP_PLATFORM_CORE_ID_UNKNOWN = 0x0001U,
    /**< Unknown Core. */
    BSP_PLATFORM_CORE_ID_A15 = 0x0002U,
    /**< A15 Core. */
    BSP_PLATFORM_CORE_ID_M4 = 0x0004U,
    /**< M4 Core. */
    BSP_PLATFORM_CORE_ID_DSP = 0x0008U,
    /**< DSP Core. */
    BSP_PLATFORM_CORE_ID_A8 = 0x0010U,
    /**< A8 Core - Applicable only to TI81xx family. */
    BSP_PLATFORM_CORE_ID_M3 = 0x0020U,
    /**< M3 Core - Applicable only to TI81xx family. */
    BSP_PLATFORM_CORE_ID_MAX = 0xFFFFU
                               /**< Max CORE ID. */
} Bsp_PlatformCoreId;

/**
 *  \brief CPU revision ID.
 */
typedef enum
{
    BSP_PLATFORM_CPU_REV_UNKNOWN,
    /**< Unknown/unsupported CPU revision. */
    BSP_PLATFORM_CPU_REV_1_0,
    /**< CPU revision 1.0. */
    BSP_PLATFORM_CPU_REV_1_1,
    /**< CPU revision 1.1. */
    BSP_PLATFORM_CPU_REV_2_0,
    /**< CPU revision 2.0. */
    BSP_PLATFORM_CPU_REV_2_1,
    /**< CPU revision 2.1. */
    BSP_PLATFORM_CPU_REV_3_0,
    /**< CPU revision 3.0. */
    BSP_PLATFORM_CPU_REV_MAX
    /**< Max CPU revision. */
} Bsp_PlatformCpuRev;

/**
 *  \brief Package Type.
 */
typedef enum
{
    BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN,
    /**< Unknown/unsupported CPU revision. */
    BSP_PLATFORM_PACKAGE_TYPE_15x15,
    /**< 15x15 package. */
    BSP_PLATFORM_PACKAGE_TYPE_12x12,
    /**< 12x12 package. */
    BSP_PLATFORM_PACKAGE_TYPE_17x17,
    /**< 17x17 package. */
    BSP_PLATFORM_PACKAGE_TYPE_23x23,
    /**< 23x23 package. */
    BSP_PLATFORM_PACKAGE_TYPE_MAX
    /**< Max package type. */
} Bsp_PlatformPackageType;

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
/**
 *  \brief Enum for the output clock modules
 *  Caution: Do not change the enum values.
 */
typedef enum
{
    BSP_SYSTEM_VPLL_OUTPUT_VENC_RF = 0,
    /**< Pixel clock frequency for the RF,
     *   Note: SD Pixel frequency will RF Clock Freq/4.
     *   This is Video0 PLL for TI813X. */
    BSP_SYSTEM_VPLL_OUTPUT_VENC_D,
    /**< VencD output clock.
     *   This is Video1 PLL for TI813X. */
    BSP_SYSTEM_VPLL_OUTPUT_VENC_A,
    /**< VencA output clock. For the TI814X, this is for DVO1.
     *   This is HDMI PLL for TI813X. */
    BSP_SYSTEM_VPLL_OUTPUT_HDMI,
    /**< HDMI output clock, this is used for HDMI display TI814X only. */
    BSP_SYSTEM_VPLL_OUTPUT_MAX_VENC
    /**< This should be last Enum. */
} Bsp_VPllOutputClk;
#endif

/**
 *  \brief Enum for the Pll's
 *  Caution: Do not change the enum values.
 */
typedef enum
{
    BSP_PLATFORM_PLL_VIDEO1 = 0,
    /**< Video1 PLL.
     *   Available only in Tda2xx */
    BSP_PLATFORM_PLL_VIDEO2,
    /**< VIDEO2 PLL.
     *   Available only in Tda2xx */
    BSP_PLATFORM_PLL_HDMI,
    /**< HDMI PLL.
     *   Available only in Tda2xx */
    BSP_PLATFORM_PLL_EVE_VID_DSP,
    /**< EVE_VID_DSP PLL.
     *   Available only in Tda3xx */
    BSP_PLATFORM_PLL_MAX
    /**< This should be last Enum. */
} Bsp_PlatformPll;

/**
 *  \brief Enum for the Venc's
 *  Caution: Do not change the enum values.
 *           This is the same values as pmlibVideoPllVenc_t
 */
typedef enum
{
    BSP_PLATFORM_VENC_LCD1 = 0U,
    /**< LCD1 Venc. */
    BSP_PLATFORM_VENC_LCD2,
    /**< LCD2 Venc. */
    BSP_PLATFORM_VENC_LCD3,
    /**< LCD3 Venc */
    BSP_PLATFORM_VENC_HDMI,
    /**< HDMI PLL. */
    BSP_PLATFORM_VENC_MAX
    /**< This should be last Enum. */
} Bsp_PlatformVenc;

/**
 *  \brief Enum for the Venc's Clock Source
 *  Caution: Do not change the enum values.
 *           This is the same values as pmlibVideoPllClkSrc_t
 */
typedef enum
{
    BSP_PLATFORM_CLKSRC_PRCM_PER_PLL = 0,
    /**<  PER PLL*/
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT1,
    /**< Video1 PLL clkout1. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT2,
    /**< Video1 PLL clkout2. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3,
    /**< Video1 PLL clkout3. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT4,
    /**< Video1 PLL clkout4. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO2_CLKOUT1,
    /**< Video2 PLL clkout1. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO2_CLKOUT2,
    /**< Video2 PLL clkout2. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO2_CLKOUT3,
    /**< Video2 PLL clkout3. */
    BSP_PLATFORM_CLKSRC_DPLL_VIDEO2_CLKOUT4,
    /**< Video2 PLL clkout4. */
    BSP_PLATFORM_CLKSRC_DPLL_HDMI,
    /**< HDMI PLL. */
    BSP_PLATFORM_CLKSRC_DPLL_ABE_GICLK,
    /**< ABE PLL. */
    BSP_PLATFORM_CLKSRC_DSS_GFCLK,
    /**< Functional Clock of DISPC. */
    BSP_PLATFORM_CLKSRC_DPLL_EVE_VID_DSP,
    /**< Common PLL for VID,EVE,DSP. Available only on Tda3xx platform . */
    BSP_PLATFORM_CLKSRC_MAX
    /**< This should be last Enum. */
} Bsp_PlatformClkSrc;

/**
 *  \brief Enum for the Memory mapped Region- MMR
 */
typedef enum
{
    BSP_PLATFORM_MMR_REG_1 = 0,
    /**<  MMR Region 1*/
    BSP_PLATFORM_MMR_REG_2,
    /**<  MMR Region 2*/
    BSP_PLATFORM_MMR_REG_3,
    /**<  MMR Region 3*/
    BSP_PLATFORM_MMR_REG_4,
    /**<  MMR Region 4*/
    BSP_PLATFORM_MMR_REG_5
    /**<  MMR Region 5*/
} Bsp_PlatformMmrRegion;

/**
 *  \brief Enum for the Max and Min M and N
 *  Caution: Do not change the enum values.
 */
typedef enum
{
    BSP_PLATFORM_VIDEO_PLL_CALC_MIN_MN  = 0U,
    /**< Flag to indicate to the API to calculate the min M and min N */
    BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN = 1U
    /**< Flag to indicate to the API to calculate the max M and max N */
}Bsp_PlatformVideoPllMNSelection;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Platform initialization parameters.
 */
typedef struct
{
    UInt32 isPinMuxSettingReq;
    /**< Pinumx setting is requried or not. Sometimes pin mux setting
     *   is required to be done from host processor. */
    UInt32 isIrqXBarSettingReq;
    /**< IRQ Cross-bar setting is requried or not. If this is enabled, then
     *   following configuration will be done. If the application wish to
     *   change to a different crossbar setup for VIP, DSS and VPE, this falg
     *   should be set to FALSE and change the corresponding IRQ number in
     *   include/tda2xx/soc_defines.h or include/tda3xx/soc_defines.h and
     *   recompile.
     *
     *      DISPC_IRQ -> IPU1_23
     *      HDMI_IRQ  -> IPU1_26
     *      VIP1_IRQ1 -> IPU1_27
     *      VIP2_IRQ1 -> IPU1_28
     *      VIP3_IRQ1 -> IPU1_29
     *      VPE1_IRQ1 -> IPU1_30
     *      I2C1_IRQ -> IPU1_41
     *      I2C2_IRQ  -> IPU1_42
     */
    UInt32 isDmaXBarSettingReq;
    /**< DMA Cross-bar setting is requried or not. If this is enabled, then
     *   following configuration will be done. If the application wish to
     *   change to a different DMA Crossbar setup for McASP3, this falg
     *   should be set to FALSE and change the corresponding DREQ number
     *   and recompile.
     *
     *      McASP3_DREQ_RX -> DMA_EDMA_DREQ_6_IRQ_6
     *      McASP3_DREQ_TX -> DMA_EDMA_DREQ_10_IRQ_10
     */
    UInt32 isAllMcSPIInitReq;
    /**< isAllMcSPIInitReq is requried or not. If this is enabled, then
     *   all 4 McSPI will be powered ON and corresponding DMACrossBar will be
     *   set. If the application wish to enable isAllMcSPIInitReq for McSPI,
     *   this flag should be set to TRUE and recompile. Default value is FALSE.
     */
    UInt32 isAllMcASPInitReq;
    /**< If this is TRUE, then all the required McASP will be powered ON
     *   If the application wish to disable McASP module power ON,
     *   this flag should be set to FALSE and recompile. Default value is TRUE.
     */
} Bsp_PlatformInitParams;

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
/**
 *  \brief System VPLL Clock
 */
typedef struct
{
    UInt32 outputVenc;
    /**< Select output venc for which Pixel clk source needs to be selected.
     *   See #Bsp_VPllOutputClk  for all possible values. */
    UInt32 outputClk;
    /**< Pixel clock frequency for vencs. Expected to specify in KHz. */
} Bsp_SystemVPllClk;
#endif

/**
 *  \brief Platform Venc clock source
 */
typedef struct
{
    UInt32 outputVenc;
    /**< Select output venc for which video pll is configured.
     *   See #Bsp_PlatformVenc  for all possible values. */
    UInt32 vencClkSrc;
    /**< Video PLL which will be source of pixel clock for the Venc.
     *  See #Bsp_PlatformClkSrc for all possible values. */
} Bsp_PlatformVencSrc;

/**
 *  \brief Set Pixel Clock Freq of the Video PLL's
 */
typedef struct
{
    UInt32 videoPll;
    /**< Video PLL, whcih needs to be programmed.
     *  See #Bsp_PlatformPll for all possible values. */
    UInt32 pixelClk;
    /**< Frequency of pixelClk outpur of PLL. Expected to specify in KHz.*/
    UInt32 chooseMaxorMinMN;
    /**< Decides whether the value of M and N programmed to the PLL is
     *   maximum or minimum. Program BSP_PLATFORM_VIDEO_PLL_CALC_MIN_MN for
     *   minimum and BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN for maximum.
     */
} Bsp_PlatformSetPllFreq;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Init the underlying platform.
 *
 *  \param initPrms     [IN] Platform Initialization parameters. If
 *                           NULL is passed, pin mux setting will be done by
 *                           default.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_platformInit(const Bsp_PlatformInitParams *initPrms);

/**
 *  \brief De-init the underlying platform.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_platformDeInit(Ptr args);

/**
 *  \brief Returns the platform ID.
 *
 *  \return Platform ID on success.
 */
Bsp_PlatformId Bsp_platformGetId(void);

/**
 *  \brief Returns the SOC ID.
 *
 *  \return SOC ID on success.
 */
Bsp_PlatformSocId Bsp_platformGetSocId(void);

/**
 *  \brief Returns the Core ID.
 *
 *  \return Core ID on success.
 */
Bsp_PlatformCoreId Bsp_platformGetCoreId(void);

/**
 *  \brief Returns the CPU revision.
 *
 *  \return CPU revision information on success.
 */
Bsp_PlatformCpuRev Bsp_platformGetCpuRev(void);

/**
 *  \brief Returns the package type.
 *
 *  \return Package Type on success.
 */
Bsp_PlatformPackageType Bsp_platformGetPackageType(void);

/**
 *  \brief Returns the FT revision.
 *
 *  \return FT revision Number on success.
 */
UInt32 Bsp_platformGetFtRev(void);

/**
 *  \brief Selects video port input file and pixel clock for simulator.
 *
 *  \param vipInstId    [IN] VIP instance ID
 *  \param fileId       [IN] File ID
 *  \param pixelClk     [IN] Pixel clock
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Bsp_platformSimVideoInputSelect(UInt32 vipInstId,
                                      UInt32 fileId,
                                      UInt32 pixelClk);

/**
 *  \brief Check if the SOC is Tda2xx derivatives.
 *
 *  \return TRUE if the SOC is Tda2xx derivatives else returns FALSE.
 */
static inline Bool Bsp_platformIsTda2xxFamilyBuild(void);

/**
 *  \brief Check if the SOC is Tda3xx derivatives.
 *
 *  \return TRUE if the SOC is Tda3xx derivatives else returns FALSE.
 */
static inline Bool Bsp_platformIsTda3xxFamilyBuild(void);

/**
 *  \brief Check if the SOC is TI814x derivatives.
 *
 *  \return TRUE if the SOC is TI814x derivatives else returns FALSE.
 */
static inline Bool Bsp_platformIsTI814xFamilyBuild(void);

/**
 *  \brief Check if the SOC is Omap5x derivatives.
 *
 *  \return TRUE if the SOC is Omap5x derivatives else returns FALSE.
 */
static inline Bool Bsp_platformIsOmap5xFamilyBuild(void);

/**
 *  \brief Function to get the name of the platform in printable string.
 *
 *  \return Returns a const pointer to the string. If the platform is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_platformGetString(void);

/**
 *  \brief Function to get the name of the SOC in printable string.
 *
 *  \return Returns a const pointer to the string. If the SOC is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_platformGetSocString(void);

/**
 *  \brief Function to get the name of the Core in printable string.
 *
 *  \return Returns a const pointer to the string. If the Core is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_platformGetCoreString(void);

/**
 *  \brief Function to get the name of the CPU revision in printable string.
 *
 *  \return Returns a const pointer to the string. If the CPU revision is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_platformGetCpuRevString(void);

/**
 *  \brief Function to get the name of the package type in printable string.
 *
 *  \return Returns a const pointer to the string. If the package type is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_platformGetPackageTypeString(void);

/**
 *  \brief Funtion to print all the platform information like CPU revision,
 *  CPU type...
 *
 */
void Bsp_platformPrintInfo(void);

/**
 *  \brief Bsp_PlatformInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Bsp_PlatformInitParams structure.
 *
 */
static inline void BspPlatformInitParams_init(Bsp_PlatformInitParams *initPrms);

/**
 *  \brief Selecte the Clock source for the Venc.
 *
 *  \param vencPrms     [IN] Pointer to #Bsp_PlatformVencSrc structure.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Bsp_platformSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms);

/**
 *  \brief Selects the Clock source for the DISPC Functional Clock.
 *
 *  \param fClkSrc      [IN]  source of Functional clock, valid values
 *  #Bsp_PlatformClkSrc.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Bsp_platformSetDispcFuncClkSrc(UInt32 fClkSrc);

/**
 *  \brief Configures the Pixel clock frequency.
 *
 *  \param pllFreq      [IN] Pointer to #Bsp_PlatformSetPllFreq structure.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Bsp_platformSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq);

/**
 *  \brief Enables/Disables the HDMI PLL
 *
 *  \param enable      [IN] TRUE/FALSE
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Bsp_platformEnableHdmiPll(UInt32 enable);

/**
 *  \brief Sets the DSS LCD clock to desired polarity
 *
 *  \param vencId   ID of the LCD to be configured
 *                  Refer #Bsp_PlatformVenc for valid values. Only to be
 *                  run for LCD
 *  \param polarity The polarity value to be set
 *                  Refer #Fvid2_Polarity for valid set of values
 *
 *  \return BSP_SOK on success, else appropriate BSP error code on failure.
 */
Int32 Bsp_platformSetLcdClkPolarity(UInt32 vencId, UInt32 polarity);

/**
 *  \brief Sets the DSS LCD HSYNC/VSYNC edge polarity (rising/falling) with
 *  respect to pixel clock
 *
 *  \param vencId       ID of the LCD to be configured
 *                      Refer #Bsp_PlatformVenc for valid values. Only to be
 *                      run for LCD
 *  \param ctrlEnable   TRUE - HSYNC and VSYNC are driven according to
 *                      edgePolarity
 *                      FALSE - HSYNC and VSYNC are driven on opposite edges
 *                      of pixel clock than pixel data
 *  \param edgePolarity HSYNC and VSYNC to be driven on rising or falling edge
 *                      of pixel clock if ctrlEnable is TRUE
 *                      Refer #Fvid2_EdgePolarity for valid set of values
 *
 *  \return BSP_SOK on success, else appropriate BSP error code on failure.
 */
Int32 Bsp_platformSetLcdSyncPolarity(UInt32 vencId,
                                     UInt32 ctrlEnable,
                                     UInt32 edgePolarity);

/**
 *  \brief Enable/disable VIP clock inversion at control module.
 *         Note: Applicable only for TDA2XX and TDA2EX
 *
 *  \param instId       VIP port ID to be configured
 *  \param invEnable    TRUE - Enable clock inversion
 *                      FALSE - Disable clock inversion
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_platformSetVipClkInversion(UInt32 instId, UInt32 invEnable);

/**
 *  \brief Configures IO pins needed for module.
 *
 *  \param mode_index   Mux mode to be cofigured
 *  \param offset       offset of the IO pin
 *  \param pupd_info    IO pin configuration settings such as To enable Pull
 *                      Up/Down, PullType Select, Receivemode is enabled / not,
 *                      Slew control etc.,
 *
 *  \return             BSP_SOK
 */
Int32 Bsp_platformSetPinmuxRegs(UInt32 mode_index,
                                UInt32 offset,
                                UInt32 pupd_info);

/**
 *  \brief This API will lock the five memory regions of CTRL_MODULE_CORE
 *         memory mapped space
 *
 *  \param region   Memory Mapped region
 *                  Refer #Bsp_PlatformMmrRegion for valid set of values
 *
 *  \return             BSP_SOK
 */
Int32 Bsp_platformLockRegion(Bsp_PlatformMmrRegion region);

/**
 *  \brief This API will unlock the five memory regions of CTRL_MODULE_CORE
 *         memory mapped space
 *
 *  \param region   Memory Mapped region
 *                  Refer #Bsp_PlatformMmrRegion for valid set of values
 *
 *  \return             BSP_SOK
 */
Int32 Bsp_platformUnLockRegion(Bsp_PlatformMmrRegion region);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline Bool Bsp_platformIsTda2xxFamilyBuild(void)
{
    Bsp_PlatformSocId socId;
    Bool retStatus = FALSE;

    socId = Bsp_platformGetSocId();
    if((BSP_PLATFORM_SOC_ID_TDA2XX == socId) ||
       (BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
       (BSP_PLATFORM_SOC_ID_DRA75X == socId) ||
       (BSP_PLATFORM_SOC_ID_TDA2EX == socId))
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline Bool Bsp_platformIsTda3xxFamilyBuild(void)
{
    Bsp_PlatformSocId socId;
    Bool retStatus = FALSE;

    socId = Bsp_platformGetSocId();
    if(BSP_PLATFORM_SOC_ID_TDA3XX == socId)
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline Bool Bsp_platformIsOmap5xFamilyBuild(void)
{
    Bsp_PlatformSocId socId;
    Bool retStatus = FALSE;

    socId = Bsp_platformGetSocId();
    if(BSP_PLATFORM_SOC_ID_OMAP5X == socId)
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline Bool Bsp_platformIsTI814xFamilyBuild(void)
{
    Bsp_PlatformSocId socId;
    Bool retStatus = FALSE;

    socId = Bsp_platformGetSocId();
    if((BSP_PLATFORM_SOC_ID_TI814X == socId) ||
       (BSP_PLATFORM_SOC_ID_TI8149 == socId) ||
       (BSP_PLATFORM_SOC_ID_TI811X == socId))
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline void BspPlatformInitParams_init(Bsp_PlatformInitParams *initPrms)
{
    if(NULL != initPrms)
    {
        initPrms->isPinMuxSettingReq  = (UInt32) TRUE;
        initPrms->isIrqXBarSettingReq = (UInt32) TRUE;
        initPrms->isDmaXBarSettingReq = (UInt32) TRUE;
        initPrms->isAllMcSPIInitReq   = (UInt32) FALSE;
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        initPrms->isAllMcASPInitReq   = (UInt32) FALSE;
#else
        initPrms->isAllMcASPInitReq   = (UInt32) TRUE;
#endif
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_PLATFORM_H_ */

/* @} */
