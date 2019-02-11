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
 *  \addtogroup BSP_DRV_VPS_COMMON_VIP_PARSER VPS - VIP Parser Config API
 *
 *  @{
 */

/**
 *  \file vps_cfgVipParser.h
 *
 *  \brief VPS - VIP Parser Config API
 */

#ifndef VPS_CFG_VIP_PARSER_H_
#define VPS_CFG_VIP_PARSER_H_

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

/** \brief Use this when a particular value for VIP config is dont care. */
#define VPS_VIP_VALUE_DONT_CARE         (-((Int32) 1))

/**
 *  \brief Enum for Control Channel Selection.
 *
 *  It describes channels numbers from extract control code and Vertical
 *  Ancillary Data.
 */
typedef enum
{
    VPS_VIP_CTRL_CHAN_SEL_7_0 = 0,
    /**< Use data[7:0] to extract control codes. */
    VPS_VIP_CTRL_CHAN_SEL_15_8 = 1,
    /**< Use data[15:8] to extract control codes. */
    VPS_VIP_CTRL_CHAN_SEL_23_16 = 2,
    /**< Use data[23:16] to extract control codes. */
    VPS_VIP_CTRL_CHAN_DONT_CARE = (-((Int32) 1)) /**< Value is dont care. */
} Vps_VipCtrlChanSel;

/**
 *  \brief It gives the imformation in 8b interface mode from where to extract
 *  Vertical Ancillary data.
 */
typedef enum
{
    VPS_VIP_ANC_CH_SEL_8B_LUMA_SIDE = 0,
    /**< Extract 8b Mode Vertical Ancillary Data from Luma Sites. */
    VPS_VIP_ANC_CH_SEL_8B_CHROMA_SIDE = 1,
    /**< Extract 8b Mode Vertical Ancillary Data from Chroma Sites. */
    VPS_VIP_ANC_CH_SEL_DONT_CARE = VPS_VIP_VALUE_DONT_CARE
                                   /**< Value is dont care. */
} Vps_VipAncChSel8b;

/**
 *  \brief It is used only for Discrete Sync.
 */
typedef enum
{
    VPS_VIP_LINE_CAPTURE_STYLE_HSYNC = 0,
    /**< Use HSYNC style line capture. */
    VPS_VIP_LINE_CAPTURE_STYLE_AVID = 1,
    /**< Use AVID style line capture. */
    VPS_VIP_LINE_CAPTURE_STYLE_DONT_CARE = VPS_VIP_VALUE_DONT_CARE
                                           /**< Value is dont care. */
} Vps_VipLineCaptureStyle;

/**
 *  \brief It is only used for Discrete Sync.
 */
typedef enum
{
    VPS_VIP_FID_DETECT_MODE_PIN = 0,
    /**< Take FID from pin. */
    VPS_VIP_FID_DETECT_MODE_VSYNC = 1,
    /**< FID is determined by VSYNC skew. */
    VPS_VIP_FID_DETECT_MODE_DONT_CARE = VPS_VIP_VALUE_DONT_CARE
                                        /**< Value is dont care. */
} Vps_VipFidDetectMode;

/**
 *  \brief In embedded sync for 2x/4x mux mode there are two way to extract
 *  soruce number, one is from least significant nibble of the XV/fvh codeword
 *  and other is least significant nibble of a horizontal blanking pixel value.
 */
typedef enum
{
    VPS_VIP_SRC_NUM_POS_LS_NIBBLE_OF_CODEWORD = 0,
    /**< srcnum is in the least significant nibble of the XV/fvh codeword. */
    VPS_VIP_SRC_NUM_POS_LS_NIBBLE_OF_HOR_BLNK_PIX = 1,
    /**< srcnum is in the least significant nibble of a horizontal blanking
     *   pixelvalue. */
    VPS_VIP_SRC_NUM_POS_DONT_CARE = VPS_VIP_VALUE_DONT_CARE
                                    /**< Value is dont care. */
} Vps_VipSrcNumPos;

/**
 *  enum Vps_VipParserSyncType.
 *  \brief Enum for Vip Sync Type.
 */
typedef enum
{
    VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV = 0,
    /**< Embedded sync single 4:2:2 YUV stream. */
    VPS_VIP_SYNC_TYPE_EMB_2X_422_YUV = 1,
    /**< Embedded sync 2x multiplexed 4:2:2 YUV stream. */
    VPS_VIP_SYNC_TYPE_EMB_4X_422_YUV = 2,
    /**< Embedded sync 4x multiplexed 4:2:2 YUV stream. */
    VPS_VIP_SYNC_TYPE_EMB_LINE_YUV = 3,
    /**< Embedded sync line multiplexed 4:2:2 YUV stream. */
    VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV = 4,
    /**< Discrete sync single 4:2:2 YUV stream. */
    VPS_VIP_SYNC_TYPE_EMB_SINGLE_RGB_OR_444_YUV = 5,
    /**< Embedded sync single RGB stream or single 444 YUV stream. */
    VPS_VIP_SYNC_TYPE_EMB_2X_RGB = 6,
    /**< Embedded sync 2x multiplexed RGB stream. */
    VPS_VIP_SYNC_TYPE_EMB_4X_RGB = 7,
    /**< Embedded sync 4x multiplexed RGB stream. */
    VPS_VIP_SYNC_TYPE_EMB_LINE_RGB = 8,
    /**< Embedded sync line multiplexed RGB stream. */
    VPS_VIP_SYNC_TYPE_DIS_SINGLE_8B_RGB = 9,
    /**< Discrete sync single 8b RGB stream. */
    VPS_VIP_SYNC_TYPE_DIS_SINGLE_24B_RGB = 10
                                           /**< Discrete sync single 24b RGB
                                            * stream. */
} Vps_VipSyncType;

/**
 *  enum Vps_VipRepackMode
 *  \brief Different Repacker Modes supported by VIP Port A
 *  For first 6 modes:
 *    Enum names assume C=[23:16], B=[15:8], A=[7:0]
 *    Enum name is of format VPS_VIP_<repacker INPUT>_TO_<repacker OUTPUT>
 *  For VPS_VIP_REPACK_RAW16_TO_RGB565:
 *    OUT[23:16]=IN[15:11]['b000]
 *    OUT[15: 8]=IN[10: 5]['b00]
 *    OUT[ 7: 0]=IN[ 4: 0]['b000]
 *  For VPS_VIP_REPACK_RAW12_SWAP:
 *    OUT[23:12] = IN[11:0], OUT[11:0] = IN[23:12],
 */
typedef enum
{
    VPS_VIP_REPACK_CBA_TO_CBA      = 0,
    VPS_VIP_REPACK_CBA_TO_ABC      = 1,
    VPS_VIP_REPACK_CBA_TO_BCA      = 2,
    VPS_VIP_REPACK_CBA_TO_CAB      = 3,
    VPS_VIP_REPACK_CBA_TO_ACB      = 4,
    VPS_VIP_REPACK_CBA_TO_BAC      = 5,
    VPS_VIP_REPACK_RAW16_TO_RGB565 = 6,
    VPS_VIP_REPACK_RAW12_SWAP      = 7,
    VPS_VIP_REPACK_DONT_CARE       = VPS_VIP_REPACK_CBA_TO_CBA
} Vps_VipRepackMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_VipPortIntfConfig
 *  \brief Configuration parameter for VIP Instance
 */
typedef struct
{
    UInt32 clipActive;
    /**< FALSE: Do not clip active Data
     *   TRUE : Clip active Data. */
    UInt32 clipBlank;
    /**< FALSE: Do not clip blanking Data
     *   TRUE : Clip blanking Data. */
    UInt32 intfWidth;
    /**< Interface mode. See #Fvid2_VideoIfWidth. */
} Vps_VipPortIntfConfig;

/**
 *  struct Vps_VipPortEmbConfig
 *  \brief Configuration parameters specific to Embedded Sync only
 */
typedef struct
{
    UInt32 errCorrEnable;
    /**< TRUE: Error Correction enable, FALSE: disabled. */
    UInt32 srcNumPos;
    /**< For valid values see #Vps_VipSrcNumPos. */
    UInt32 reserved;
    /**< Previously isMaxChan3Bits - missing from header file
     *   FALSE: Use all 5 bits of the field for 32 total sources,
     *   TRUE : Use only bits 2:0 of this field to support
     *          the TVP5158's 8 sources, with the two upper
     *          most bits reserved. */
} Vps_VipPortEmbConfig;

/**
 *  struct Vps_VipPortDisConfig
 *  \brief Configuration parameters specific to Discrete Sync mode
 */
typedef struct
{
    UInt32 fidSkewPostCnt;
    /**< Post count value when using vsync skew in FID determination. */
    UInt32 fidSkewPreCnt;
    /**< Pre count value when using vsync skew in FID determination. */
    UInt32 lineCaptureStyle;
    /**< For valid values see #Vps_VipLineCaptureStyle. */
    UInt32 fidDetectMode;
    /**< For valid values see #Vps_VipFidDetectMode. */
    UInt32 actvidPol;
    /**< For valid values see #Fvid2_Polarity. */
    UInt32 vsyncPol;
    /**< For valid values see #Fvid2_Polarity. */
    UInt32 hsyncPol;
    /**< For valid values see #Fvid2_Polarity. */
    UInt32 discreteBasicMode;
    /**< FALSE = Normal Discrete Mode, TRUE = Basic Discrete Mode.
     *   TRUE = DE signal need not be active during the VBLANK period. Most of
     *     the encoder provide the discrete signals in this way.
     *   FALSE = DE signal needs to be active during the VBLANK period. */
} Vps_VipPortDisConfig;

/**
 *  struct Vps_VipPortComConfig
 *  \brief Configuration parameters common to Embedded and Discrete sync modes
 */
typedef struct
{
    UInt32 ctrlChanSel;
    /**< For valid values see #Vps_VipCtrlChanSel. */
    UInt32 ancChSel8b;
    /**< For valid values see #Vps_VipAncChSel8b. */
    UInt32 pixClkEdgePol;
    /**< For valid values see #Fvid2_EdgePolarity. */
    UInt32 invertFidPol;
    /**< FALSE: Keep FID as found, TRUE: Invert Value of FID. */
    UInt32 enablePort;
    /**< '0' = Disable Port, '1' = Enable Port.
     *   Keep 0 when doing setCfg, set to 1 using enablePort API. */
    UInt32 clrAsyncFifoRd;
    /**< '0' = Normal, '1' = Clear Async FIFO Read Logic. */
    UInt32 clrAsyncFifoWr;
    /**< '0' = Normal,  '1' = Clear Async FIFO Write Logic. */
    UInt32 expectedNumLines;
    /**< Expected number of lines in the source. */
    UInt32 expectedNumPix;
    /**< Expected number of pixels per line in the source. */
    UInt32 repackerMode;
    /**< Repacker Mode. Use #Vps_VipRepackMode. */
} Vps_VipPortComConfig;

/**
 *  struct Vps_VipPortCropConfig
 *  \brief Structure containing configuration for VIP cropping module.
 */
typedef struct
{
    UInt32           srcNum;
    /**< Cropping module works on only one srcNum. */
    Fvid2_CropConfig cropCfg;
    /**< VIP Port crop configuration. */
} Vps_VipPortCropConfig;

/**
 *  \brief Configuration parameter for a VIP Port
 */
typedef struct
{
    UInt32                syncType;
    /**< Sync Type. See #Vps_VipSyncType. Also indicates which among
     *   embCfg and disCfg contains valid data. */
    UInt32                actCropEnable;
    /**< Is cropping enabled for active video channel. Indicates if actCropCfg
     *   contains valid data. */
    UInt32                ancCropEnable;
    /**< Is cropping enabled for ancillary channel. Indicates if ancCropCfg
     *   contains valid data. */

    Vps_VipPortIntfConfig intfCfg;
    /**< Basic port configuration parameters. */

    Vps_VipPortEmbConfig  embCfg;
    /**< Configuration parameters specific to Embedded Sync mode. */
    Vps_VipPortDisConfig  disCfg;
    /**< Configuration parameters specific to Discrete Sync mode. */

    Vps_VipPortComConfig  comCfg;
    /**< Configuration parameter common to both Embedded/Discrete Sync modes. */

    Vps_VipPortCropConfig actCropCfg;
    /**< Cropping parameters for active video channel. */
    Vps_VipPortCropConfig ancCropCfg;
    /**< Cropping parameters for ancillary channel. */
} Vps_VipPortConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_VipPortIntfConfig structure init function.
 *
 *  \param intfCfg      [IN] Pointer to #Vps_VipPortIntfConfig structure.
 *
 */
static inline void VpsVipPortIntfConfig_init(Vps_VipPortIntfConfig *intfCfg);

/**
 *  \brief Vps_VipPortEmbConfig structure init function.
 *
 *  \param embCfg       [IN] Pointer to #Vps_VipPortEmbConfig structure.
 *
 */
static inline void VpsVipPortEmbConfig_init(Vps_VipPortEmbConfig *embCfg);

/**
 *  \brief Vps_VipPortDisConfig structure init function.
 *
 *  \param disCfg       [IN] Pointer to #Vps_VipPortDisConfig structure.
 *
 */
static inline void VpsVipPortDisConfig_init(Vps_VipPortDisConfig *disCfg);

/**
 *  \brief Vps_VipPortComConfig structure init function.
 *
 *  \param comCfg       [IN] Pointer to #Vps_VipPortComConfig structure.
 *
 */
static inline void VpsVipPortComConfig_init(Vps_VipPortComConfig *comCfg);

/**
 *  \brief Vps_VipPortCropConfig structure init function.
 *
 *  \param cropCfg      [IN] Pointer to #Vps_VipPortCropConfig structure.
 *
 */
static inline void VpsVipPortCropConfig_init(Vps_VipPortCropConfig *cropCfg);

/**
 *  \brief Vps_VipPortConfig structure init function.
 *
 *  \param portCfg      [IN] Pointer to #Vps_VipPortConfig structure.
 *
 */
static inline void VpsVipPortConfig_init(Vps_VipPortConfig *portCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsVipPortIntfConfig_init(Vps_VipPortIntfConfig *intfCfg)
{
    if (NULL != intfCfg)
    {
        intfCfg->clipActive = (UInt32) FALSE;
        intfCfg->clipBlank  = (UInt32) FALSE;
        intfCfg->intfWidth  = FVID2_VIFW_16BIT;
    }

    return;
}

static inline void VpsVipPortEmbConfig_init(Vps_VipPortEmbConfig *embCfg)
{
    if (NULL != embCfg)
    {
        embCfg->errCorrEnable = (UInt32) FALSE;
        embCfg->srcNumPos     = VPS_VIP_SRC_NUM_POS_LS_NIBBLE_OF_CODEWORD;
        embCfg->reserved      = (UInt32) TRUE;
    }

    return;
}

static inline void VpsVipPortDisConfig_init(Vps_VipPortDisConfig *disCfg)
{
    if (NULL != disCfg)
    {
        disCfg->fidSkewPostCnt    = 0U;
        disCfg->fidSkewPreCnt     = 0U;
        disCfg->lineCaptureStyle  = VPS_VIP_LINE_CAPTURE_STYLE_AVID;
        disCfg->fidDetectMode     = VPS_VIP_FID_DETECT_MODE_PIN;
        disCfg->actvidPol         = FVID2_POL_HIGH;
        disCfg->vsyncPol          = FVID2_POL_HIGH;
        disCfg->hsyncPol          = FVID2_POL_HIGH;
        disCfg->discreteBasicMode = (UInt32) TRUE;
    }

    return;
}

static inline void VpsVipPortComConfig_init(Vps_VipPortComConfig *comCfg)
{
    if (NULL != comCfg)
    {
        comCfg->ctrlChanSel      = VPS_VIP_CTRL_CHAN_SEL_7_0;
        comCfg->ancChSel8b       = VPS_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        comCfg->pixClkEdgePol    = FVID2_EDGE_POL_RISING;
        comCfg->invertFidPol     = (UInt32) FALSE;
        comCfg->enablePort       = (UInt32) FALSE;
        comCfg->clrAsyncFifoRd   = (UInt32) FALSE;
        comCfg->clrAsyncFifoWr   = (UInt32) FALSE;
        comCfg->expectedNumLines = 0U;
        comCfg->expectedNumPix   = 0U;
        comCfg->repackerMode     = VPS_VIP_REPACK_CBA_TO_CBA;
    }

    return;
}

static inline void VpsVipPortCropConfig_init(Vps_VipPortCropConfig *cropCfg)
{
    if (NULL != cropCfg)
    {
        cropCfg->srcNum = 0U;
        Fvid2CropConfig_init(&cropCfg->cropCfg);
    }

    return;
}

static inline void VpsVipPortConfig_init(Vps_VipPortConfig *portCfg)
{
    if (NULL != portCfg)
    {
        portCfg->syncType      = VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV;
        portCfg->actCropEnable = (UInt32) FALSE;
        portCfg->ancCropEnable = (UInt32) FALSE;
        VpsVipPortIntfConfig_init(&portCfg->intfCfg);
        VpsVipPortEmbConfig_init(&portCfg->embCfg);
        VpsVipPortDisConfig_init(&portCfg->disCfg);
        VpsVipPortComConfig_init(&portCfg->comCfg);
        VpsVipPortCropConfig_init(&portCfg->actCropCfg);
        VpsVipPortCropConfig_init(&portCfg->ancCropCfg);
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_VIP_PARSER_H_ */

/* @} */
