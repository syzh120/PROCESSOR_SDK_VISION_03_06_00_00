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
 *  \ingroup BSP_DRV_VPS_CAPTURE_API
 *  \defgroup BSP_DRV_VPS_CAPTURE_DSSWB_API VPS DSSWB Capture API
 *
 *  This modules define APIs to capture video data using DSSWB in VPS.
 *  @{
 */

/**
 *  \file vps_captureDssWb.h
 *
 *  \brief Video Capture API specific to DSSWB.
 */

#ifndef VPS_CAPTURE_DSSWB_H_
#define VPS_CAPTURE_DSSWB_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of streams supported by the DSS WB driver. */
#define VPS_CAPT_DSSWB_STREAM_ID_MAX    (1U)

/* DSSWB Capture IOCTL's */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS_CAPTURE
 *  \defgroup BSP_DRV_IOCTL_VPS_CAPTURE_DSSWB DSSWB Capture IOCTL's
 *  @{
 */

/**
 *  \brief Set DSSWB parameters.
 *
 *  This IOCTL can be used to set the DSS WB hardware specific parameters.
 *  This IOCTL should be called after creating any DSS WB capture driver
 *  instance and before queueing or starting the capture driver. Starting the
 *  capture driver without calling this IOCTL will result in error.
 *
 *  Once the capture is started this IOCTL can't be invoked and will result in
 *  error.
 *
 *  Once the capture is stopped, application could call this IOCTL to
 *  reconfigure the DSS WB block with a different set of parameters.
 *
 *  \param cmdArgs       [IN]  const Vps_CaptDssWbParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_DSSWB_PARAMS   (VPS_CAPT_DSSWB_IOCTL_BASE + 0x0000U)

/**
 *  \brief Get DSSWB parameters.
 *
 *  This IOCTL can be used to get the DSSWB hardware parameters.
 *  This IOCTL could be called at anytime after creating DSSWB capture
 *  driver instance.
 *
 *  \param cmdArgs       [IN]  Vps_CaptDssWbParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_GET_DSSWB_PARAMS   (VPS_CAPT_DSSWB_IOCTL_BASE + 0x0001U)

/**
 *  \brief Set DSSWB CSC Coefficients IOCTL.
 *
 *  This IOCTL can be used to set the CSC coefficients.
 *  Note: Default BT601 coefficients are set.
 *
 *  \param cmdArgs       [IN] const Vps_DssCscCoeff *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */
#define IOCTL_VPS_CAPT_DSSWB_SET_CSC_COEFF  (VPS_CAPT_DSSWB_IOCTL_BASE + \
                                             0x0002U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Capture output format information
 */
typedef struct
{
    Fvid2_Format outFmt;
    /**<
     *   <b>width</b>:<br>
     *   Output width, in pixels.
     *   This represents the scaler output width to be programmed if scaler
     *   is used.
     *   Otherwise output width is equal to the inCrop source width
     *   of the overlay in case of TDA3XX.In case of TDA2XX it is equal to
     *   Overlay Width if scaler is not used<br>
     *
     *   <b>height</b>:<br>
     *   Output height, in lines.
     *   This represents the scaler output Height to be programmed if scaler
     *   is used.
     *   Otherwise output width is equal to the inCrop source height
     *   of the overlay in case of TDA3XX. In case of TDA2XX it's equal to
     *   Overlay Height if scaler is not used<br>
     *
     *   <b>dataFormat</b>:<br>
     *   Output Data format, valid options for TDA3XX are<br>
     *   FVID2_DF_BGRA16_4444,<br>
     *   FVID2_DF_RGBA16_4444,<br>
     *   FVID2_DF_ABGR16_4444,<br>
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_RGB16_565,<br>
     *   FVID2_DF_BGRA16_1555,<br>
     *   FVID2_DF_RGBA16_1555,<br>
     *   FVID2_DF_RGBA32_8888,<br>
     *   FVID2_DF_BGRA32_8888,<br>
     *   FVID2_DF_ABGR32_8888,<br>
     *   FVID2_DF_ARGB32_8888,<br>
     *   FVID2_DF_BGR24P_888,<br>
     *   FVID2_DF_BGRA64_16161616,<br>
     *   FVID2_DF_ABGR64_16161616,<br>
     *   FVID2_DF_BGRX16_4444,<br>
     *   FVID2_DF_RGBA16_4444,<br>
     *   FVID2_DF_ABGR16_4444,<br>
     *   FVID2_DF_BGRX16_5551,<br>
     *   FVID2_DF_RGBX16_5551,<br>
     *   FVID2_DF_BGRX32_8888,<br>
     *   FVID2_DF_RGBX32_8888,<br>
     *   FVID2_DF_XBGR32_8888,<br>
     *   FVID2_DF_XRGB32_8888,<br>
     *   FVID2_DF_BGRX64_16161616,<br>
     *   FVID2_DF_XBGR64_16161616,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV422I_UYVY.<br>
     *   Output Data format, valid options for TDA2XX are<br>
     *   FVID2_DF_YUV422I_UYVY,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_BGR24_888,<br>
     *   FVID2_DF_XBGR_4444,<br>
     *   FVID2_DF_BGRX_4444,<br>
     *   FVID2_DF_BGRA16_4444,<br>
     *   FVID2_DF_ABGR16_4444,<br>
     *   FVID2_DF_BGRX16_5551,<br>
     *   FVID2_DF_BGRA16_5551,<br>
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_BGRX24_8888,<br>
     *   FVID2_DF_XBGR24_8888,<br>
     *   FVID2_DF_BGRA32_8888,<br>
     *   FVID2_DF_ABGR32_8888,<br>
     *   FVID2_DF_ARGB32_8888.<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines.It should be (BPP * Width)
     *   No other value is supported.
     *   And should be aligned to VPS_BUFFER_ALIGNMENT.<br>
     *
     *   <b>fieldMerged</b>:<br>
     *   Valid only in case of FVID2_BUF_FMT_FRAME buffer format and
     *   interlaced capture mode. <br>
     *   TRUE - Fields are merged. Driver programs difference between each line
     *   as pitch * 2. Application has to provide bottom field address
     *   as top field address + pitch (next line).
     *   FALSE - Fields are separated. Driver programs difference between
     *   each line as pitch * 1 only. Top and bottom field buffers could be
     *   in entirely different buffer location.
     *
     *   <b>chNum, scanFormat, bpp</b>: Not used, set to 0 or default. */
    UInt32                    memType;
    /**< Tiled or non-tiled memory selection for output.
     *   For valid values see #Vps_VpdmaMemoryType.
     *   NON_TILED is not supported for both TDA2XX and TDA3XX . */

    UInt32                    scEnable;
    /**< TRUE: Use scaler before writing video data to memory,
     *   FALSE: Scaler is not used in capture path. */

    UInt32                    cscFullRngEnable;
    /**< TRUE: Use CSC Full Range ,
     *   FALSE: Limited Range CSC is used. */

    UInt32                    cropEnable;
    /**<Set to true if inFmt.width and inCropCfg.cropWidth are not same and
     *  inFmt.height and inCropHeight.cropHeight are not same
     *  Not applicable for tda2xx */

    Vps_DssDispcAdvDmaConfig *advDmaCfg;
    /**< Advanced DMA Configuration structure.
     *     For default values pass NULL */
} Vps_CaptDssWbOutInfo;

/**
 *  \brief DSSWB parameters used in set/get DSSWB params IOCTL.
 */
typedef struct
{
    Fvid2_Format inFmt;
    /**<
     *   <b>width</b>:<br>
     *   Input source width,
     *   video source input width. This represents width of overlay to whcih
     *   WB is connected.<br>
     *
     *   <b>height</b>:<br>
     *   Input source height, MUST be >= actual or expected
     *   video source input height.
     *   This represents height of overlay to whcih WB is connected.<br>
     *   Height should be field height in case source is interlaced<br>
     *   Height should be frame height in case source is progressive<br>
     *
     *   <b>dataFormat</b>:<br>
     *   Input source color data format, valid values are given below<br>
     *   FVID2_DF_BGR24_888.<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   <b>scanFormat</b>:<br>
     *   Input source scan format - interlaced or progressive.
     *   For valid values see #Fvid2_ScanFormat.<br>
     *
     *   <b>chNum, pitch, fieldMerged, bpp</b>: Not used, set to 0 or default.
     * */
    Vps_CaptDssWbOutInfo outStreamInfo[VPS_CAPT_DSSWB_STREAM_ID_MAX];
    /**< Output format for each stream. The number of valid entries should
     *   match the numStream parameter provided at create time. */

    Fvid2_CropConfig     inCropCfg;
    /**< DSS Overlay crop config. Not valid for tda2xx Platforms.
     *   For tda3xx platform for full frame write back,
     *   height and width of crop config should be same as in inFmt */
    UInt32               wbMode;
    /**< M2M Writeback or capture Writeback mode. For valid
     *   values check #Vps_DssDispcWbMode. */
    UInt32               inNode;
    /**< Input pipe/overlay that is connected to writeback Pipeline
     *    For valid values see #Vps_DssDispcWbInNode. */
} Vps_CaptDssWbParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_CaptDssWbOutInfo structure init function.
 *
 *  \param dssWbOutInfo   [IN] Pointer to #Vps_CaptDssWbOutInfo structure.
 *
 */
static inline void VpsCaptDssWbOutInfo_init(Vps_CaptDssWbOutInfo *dssWbOutInfo);

/**
 *  \brief VpsCaptDssWbParams structure init function.
 *
 *  \param dssWbPrms      [IN] Pointer to #Vps_CaptDssWbParams structure.
 *
 */
static inline void VpsCaptDssWbParams_init(Vps_CaptDssWbParams *dssWbPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsCaptDssWbOutInfo_init(Vps_CaptDssWbOutInfo *dssWbOutInfo)
{
    if (NULL != dssWbOutInfo)
    {
        Fvid2Format_init(&dssWbOutInfo->outFmt);
        dssWbOutInfo->memType           = VPS_VPDMA_MT_NONTILEDMEM;
        dssWbOutInfo->scEnable          = (UInt32) FALSE;
        dssWbOutInfo->cscFullRngEnable  = (UInt32) TRUE;
        dssWbOutInfo->cropEnable        = (UInt32) FALSE;
        dssWbOutInfo->advDmaCfg         = NULL;
    }

    return;
}

static inline void VpsCaptDssWbParams_init(Vps_CaptDssWbParams *dssWbPrms)
{
    UInt32 streamId;

    if (NULL != dssWbPrms)
    {
        Fvid2Format_init(&dssWbPrms->inFmt);
        for (streamId = 0U; streamId < VPS_CAPT_DSSWB_STREAM_ID_MAX; streamId++)
        {
            VpsCaptDssWbOutInfo_init(&dssWbPrms->outStreamInfo[streamId]);
        }
        Fvid2CropConfig_init(&dssWbPrms->inCropCfg);

        dssWbPrms->inNode = VPS_DSS_DISPC_WB_IN_NODE_LCD1;
        dssWbPrms->wbMode = VPS_DSS_DISPC_WB_CAPT;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_CAPTURE_DSSWB_H_ */

/* @} */
