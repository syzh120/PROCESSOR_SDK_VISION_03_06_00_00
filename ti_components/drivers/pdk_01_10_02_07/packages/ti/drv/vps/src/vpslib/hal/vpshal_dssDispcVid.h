/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file vpshal_dssDispcVid.h
 *
 *  \brief HAL layer for the DSS DISPC Video Pipeline Module.
 *  This file exposes the HAL APIs of the DISPC Video Pipeline .
 *  This HAL is meant to be used by other VPS driver. The application don't
 *  have to access this HAL module.
 *
 */

#ifndef VPSHAL_DISPC_VID_H_
#define VPSHAL_DISPC_VID_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum VpsHal_DispcVidInst
 *  \brief Enum to define the various DISPC VID instance.
 */
typedef enum
{
    VPSHAL_DSS_DISPC_VID1 = 0,
    /**< DSS DISPC VID1 instance. */
    VPSHAL_DSS_DISPC_VID2,
    /**< DSS DISPC VID2 instance.. */
    VPSHAL_DSS_DISPC_VID3,
    /**< DSS DISPC VID3 instance.. */
    VPSHAL_DSS_DISPC_GFX,
    /**< DSS DISPC GFX instance.. */
    VPSHAL_DSS_DISPC_WB1,
    /**< DSS DISPC Write Back instance.. */
    VPSHAL_DSS_DISPC_VID_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_DispcVidInstId;

/**
 *  \brief DISPC VID + GFX + WB maximum number of instances for any given
 *         platform - used for memory allocation.
 */

#define VPSHAL_DSS_DISPC_VID_MAX_INST             (4U)
#define VPSHAL_DSS_DISPC_WB_MAX_INST              (1U)

#define VPSHAL_DSS_DISPC_PIPE_MAX_INST           (VPSHAL_DSS_DISPC_VID_MAX_INST \
                                                  +                             \
                                                  VPSHAL_DSS_DISPC_WB_MAX_INST)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DispcVidInstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance. For valid values see
     *#VpsHal_DispcVidInstId. */
} VpsHal_DispcVidInstParams;

/**
 *  struct VpsHal_DispcVidOpenParams
 *  \brief Structure to identify a DISPC VID HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< DISPC VID Instance ID. For valid values see #VpsHal_DispcVidInstId. */
} VpsHal_DispcVidOpenParams;

/**
 *  struct VpsHal_DssDispcPipeCfg
 *  \brief Video pipeline HAL configuration structure.
 */
typedef struct
{
    Fvid2_Format inFmt;
    /**< Input FVID frame format. */
    UInt32       outWidth;
    /**< Horizontal Size of picture at output of video pipeline . */
    UInt32       outHeight;
    /**< Verticle Size of picture at output of video pipeline . */
    UInt32       posY;
    /**< Y position of the Video Window . */
    UInt32       posX;
    /**< X position of the Video Window . */
    UInt32       repliEnable;
    /**< Enable or disable the video replication logic . */
    UInt32       scEnable;
    /**< Enable or disable the scaling, enable only if input size and
     *   Output size are different. For valid values check
     *   #Vps_DssDispcScEnable. */
    UInt32       cscFullRngEnable;
    /**< Full range or Limited Range for CSC module. For valid
     *   values check #Vps_DssDispcCscRange
     *   0x0:Limited Range
     *   0x1:Full Range. */
    UInt32       chromaSampling;
    /**< 0x0 - Missing Chrominance samples are calculated by averaging adjacent
     *   samples. - only when rotation is disabled and input is YUV422
     *   0x1 - Missing Chrominance samples are calculated by Filtering adjacent
     *   samples. */
    UInt32       clutdata[256];
    /** Clut table for the bitmap formats **/
    UInt32       nibblemode;
    /** Nibble mode for bitmap formats **/
} VpsHal_DssDispcVidPipeCfg;

/**
 *  struct VpsHal_DssDispcGfxPipeCfg
 *  \brief Graphics pipeline HAL configuration structure.
 */
typedef struct
{
    Fvid2_Format inFmt;
    /**< Input FVID frame format. */
    UInt32       posY;
    /**< Y position of the Gfx Window . */
    UInt32       posX;
    /**< X position of the Gfx Window . */
    UInt32       repliEnable;
    /**< Enable or disable the replication logic in graphics pipeline . */
    UInt32       antiFlickerEnable;
    /**< Enable or disable the anti Flicker filter in graphics pipeline.
     *   The anti-flicker filter processes the graphics data in RGB format in
     *   order to remove some of the vertical flicker. It is based on 3-tap FIR
     *   filter with hardcoded coefficients: 0.25, 0.5 and 0.25. */
    UInt32       clutdata[256];
    /** Clut table for the bitmap formats **/
    UInt32       nibblemode;
    /** Nibble mode for bitmap formats **/
} VpsHal_DssDispcGfxPipeCfg;

/**
 *  struct VpsHal_DssDispcWbPipeCfg
 *  \brief Write Back pipeline HAL configuration structure.
 */
typedef struct
{
    Fvid2_Format outFmt;
    /**< Input FVID frame format. */
    UInt32       inSourceWidth;
    /**< Horizontal Size of Overlay connected to writeback pipe . */
    UInt32       inSourceHeight;
    /**< Vertical Size of Overlay connected to writeback pipe . */
    UInt32       inWidth;
    /**< Horizontal Size of picture at input of writeback pipeline . */
    UInt32       inHeight;
    /**< Verticle Size of picture at input of writeback pipeline . */
    UInt32       inPosX;
    /**< PositionX of picture at input of writeback pipeline(Overlay Window)
     *    Applicable only for TDA3xx platform. */
    UInt32       inPosY;
    /**< PositionY of picture at input of writeback pipeline(Overlay Window)
     *    Applicable only for TDA3xx platform. */
    UInt32       inDataFormat;
    /**< Input Frame data Format. For valid values see #Fvid2_DataFormat. */
    UInt32       inNode;
    /**< Input pipe/overlay that is connected to writeback Pipeline
     *    For valid values see #Vps_DssDispcWbInNode. */
    UInt32       cropEnable;
    /**< Enable or disable the region based writeback . */
    UInt32       scEnable;
    /**< Enable or disable the scaling, enable only if input size and
     *   Output size are different. For valid values check
     *   #Vps_DssDispcScEnable. */
    UInt32       cscFullRngEnable;
    /**< Full range or Limited Range for CSC module. For valid
     *   values check #Vps_DssDispcCscRange
     *   0x0:Limited Range
     *   0x1:Full Range. */
    UInt32       wbMode;
    /**< M2M Writeback or capture Writeback mode. For valid
     *   values check #Vps_DssDispcWbMode. */
} VpsHal_DssDispcWbPipeCfg;

/**
 *  struct Vps_DssDispcDmaConfig
 *  \brief Advanced DMA related Config parameters .
 */
typedef struct
{
    UInt32 burstSize;
    /**<  Video DMA Burst SiZe
     *    0x0: 2x128bit bursts
     *    0x1: 4x128bit bursts
     *    0x2: 8x128bit bursts
     *    0x3: Reserved. */
    UInt32 burstType;
    /**<  Type of the Burst (INC or BLCK)
     *    0x0 Inc burst type
     *    0x1 2D burst type (Used for Tiler, Currently not supported)*/
    UInt32 bufPreloadType;
    /**< Allows to choose between pre-fixed preload size
     *   and a programmable size. */
    UInt32 bufLowThreshold;
    /**<  DMA buffer low threshold. Number of 128 bits defining the
     *    threshold value. */
    UInt32 bufHighThreshold;
    /**<  Video DMA buffer high threshold. Number of 128 bits defining the
     *    Threshold value. */
    UInt32 selfRefreshEnable;
    /**<  Enables the self refresh of the video window from its own.
     *    DMA buffer only
     *    FALSE - Disable
     *    TRUE - Enable. */
    UInt32 arbitration;
    /**<  Determines the priority of the video pipeline.
     *    0x0 - Normal Priority
     *    0x1 - High priority. */
    UInt32 rowInc;
    /**<  Number of bytes to increment at the end of the row
     *    Encoded signed value (from 2311 to 231) to specify the
     *    number of bytes to increment at the end of the row in the
     *    video buffer. The value 0 is invalid. The value 1 means
     *    next pixel. The value 1 + n * bpp means increment of n
     *    pixels. The value 1 (n + 1)* bpp means decrement of n
     *    pixels. */
    UInt32 pixelInc;
    /**<  Number of bytes to increment between two pixels.
     *    Encoded unsigned value (from 1 to 255) to specify the
     *    number of bytes between two pixels in the video buffer.
     *    The value 0 is invalid. The value 1 means next pixel. The
     *    value 1 + n * bpp means increment of n pixels.
     *    For YUV4:2:0, maximum supported value is 128. */
    UInt32 idleNumber;
    /**<  Number of idles between the requests on L3 Interconnect.
     *    if idleSize is 0 - number of idle cycles = idle Number
     *          range 0 to 15
     *    if idleSize is 1 - number of idle clcles = idle Number * Burst Size.
     *          range 0 to 120 for value of burstSize = 2,
     *          range 0 to 60  for value of burstSize = 1,
     *          range 0 to 30  for value of burstSize = 0.
     *    Applicable only for the writeback pipe. */
    UInt32 idleSize;
    /**<  determines multiplication factor to idleNumber.
     *    refer comment for idleNumber.
     *    Applicable only for the writeback pipe. */
} VpsHal_DssDispcAdvDmaConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief VpsHal_dssGfxPipeCfgInit structure init function.
 *
 *  \param  gfxPipeCfg  [IN] Pointer to #VpsHal_DssDispcGfxPipeCfg structure.
 *
 */
static inline void VpsHal_dssGfxPipeCfgInit(
    VpsHal_DssDispcGfxPipeCfg *gfxPipeCfg);

/**
 *  \brief VpsHal_dssVidPipeCfgInit structure init function.
 *
 *  \param  vidPipeCfg  [IN] Pointer to #VpsHal_DssDispcVidPipeCfg structure.
 *
 */
static inline void VpsHal_dssVidPipeCfgInit(
    VpsHal_DssDispcVidPipeCfg *vidPipeCfg);

/**
 *  \brief VpsHal_dssWbPipeCfgInit structure init function.
 *
 *  \param  wbPipeCfg  [IN] Pointer to #VpsHal_DssDispcWbPipeCfg structure.
 *
 */
static inline void VpsHal_dssWbPipeCfgInit(
    VpsHal_DssDispcWbPipeCfg *wbPipeCfg);

/**
 *  \brief VpsHal_dssAdvDmaConfigInit structure init function.
 *
 *  \param  advDmaCfg   [IN] Pointer to #VpsHal_DssDispcAdvDmaConfig structure.
 *
 */
static inline void VpsHal_dssAdvDmaConfigInit(
    VpsHal_DssDispcAdvDmaConfig *halAdvDmaCfg);

/**
 *  \brief VpsHal_dssWbAdvDmaConfigInit structure init function.
 *
 *  \param  advDmaCfg   [IN] Pointer to #VpsHal_DssDispcAdvDmaConfig structure.
 *
 */
static inline void VpsHal_dssWbAdvDmaConfigInit(
    VpsHal_DssDispcAdvDmaConfig *halAdvDmaCfg);
/**
 *  VpsHal_dssVidInit
 *  \brief DISPC VID HAL init function.
 *
 *  Initializes VID objects, gets the register overlay offsets for DISPC VID
 *  registers.
 *  This function should be called before calling any of DISPC VID HAL API's.
 *
 *  \param numInst          Number of instance objects to be initialized
 *  \param instPrms         Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *                          This parameter should not be NULL.
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */

Int32 VpsHal_dssVidInit(UInt32                           numInst,
                        const VpsHal_DispcVidInstParams *instPrms,
                        Ptr                              arg);

/**
 *  VpsHal_dssVidDeInit
 *  \brief DSS DISPC VID HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidDeInit(Ptr arg);

/**
 *  VpsHal_dssVidOpen
 *  \brief Returns the handle to the requested DISPC VID instance.
 *
 *  This function should be called prior to calling any of the DISPC VID HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param halId            Requested DISPC VID instance.
 *
 *  \return                 Returns DISPC VID instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_dssVidOpen(const VpsHal_DispcVidOpenParams *openPrms);

/**
 *  VpsHal_dssVidClose
 *  \brief Closes the DISPC VID HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_dssVidOpen
 *                          function
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidClose(VpsHal_Handle handle);

/**
 *  VpsHal_dssConfGfxPipe
 *  \brief DISPC GFX Pipeline Conf function.
 *
 *  Initializes GFX objects, gets the Pointers to pipeline config
 *  structure .Configures all the components present in the graphics pipeline
 *  like input Format, output resolution, out position.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Graphics pipeline hal object
 *  \param gfxConf          Pointer to the DispcGfxConf structure.
 *                                    This parameter should not be NULL..
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfGfxPipe(VpsHal_Handle                    handle,
                            const VpsHal_DssDispcGfxPipeCfg *gfxConf);

/**
 *  VpsHal_dssConfVidPipe
 *  \brief DISPC VID Pipeline Conf function.
 *
 *  Initializes VID objects, gets the Pointers to pipeline config and vc1 config
 *  structures .Configures all the components present in the video pipeline
 *  like input Format, output resolution, out position, VC1 config.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Video pipeline hal object
 *  \param vidConf          Pointer to the DispcVidConf structure.
 *                          This parameter should not be NULL.
 *  \param vc1Cfg            Pointer to the Vps_DssDispcVidVC1Config structure.
 *                          This parameter can be NULL, VC1 module will not be.
 *                          Enabled.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfVidPipe(VpsHal_Handle                    handle,
                            const VpsHal_DssDispcVidPipeCfg *vidConf,
                            const Vps_DssDispcVidVC1Config  *vc1Cfg);
/**
 *  VpsHal_dssPipeOvlyConfig
 *  \brief DISPC VID Pipeline overlay config function.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Video pipeline hal object
 *  \param pipeCfg          Pointer to the overlay config structure.
 *                          This parameter should not be NULL.
 *  \param channelOut       channelOut register field
 *  \param channelOut2      channelOut2 register field

 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssPipeOvlyConfig(VpsHal_Handle                     handle,
                               const Vps_DssDispcOvlyPipeConfig *pipeCfg,
                               UInt32                            channelOut,
                               UInt32                            channelOut2);
/**
 *  VpsHal_dssConfWbPipe
 *  \brief DISPC Write Back Pipeline Conf function.
 *
 *  Initializes WB objects, gets the Pointers to Writeback pipeline config.
 *  Configures all the components present in the Writeback pipeline
 *  like input and out Format and resolution, out position, VC1 config.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Writeback pipeline hal object
 *  \param wbConf          Pointer to the DispcwbConf structure.
 *                                  This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfWbPipe(VpsHal_Handle                   handle,
                           const VpsHal_DssDispcWbPipeCfg *wbConf);

/**
 *  VpsHal_dssConfAdvDma
 *  \brief DISPC Advance DMA Config Function.
 *
 *  This function will configure all the advance DMA parameters,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Video pipeline hal object
 *  \param advDmaCfg        Pointer to advance DMA configuration structure.
 *                          This parameter should not be NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfAdvDma(VpsHal_Handle                      handle,
                           const VpsHal_DssDispcAdvDmaConfig *advDmaCfg);

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)

/**
 *  VpsHal_dssWbSetGoBit
 *  \brief Sets the WBGo bit for WB pipeline
 *   Applicable only for WB pipeline
 *
 *  This function will program the buffer address for a pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Handle to the Video pipeline hal object
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */

Int32 VpsHal_dssWbSetGoBit(VpsHal_Handle handle);

#endif

/**
 *  VpsHal_dssVidPipeSetBufAddr
 *  \brief Sets the buffer address for a particular pipeline
 *
 *  This function will program the buffer address for a pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Handle to the Video pipeline hal object
 *  \param field            Top or bottom field.0-top field, 1-bottom field
 *                          For progressive buffers always use 0.
 *  \param baseAddRGBY      Base address of RGB or Y plane depending on format.
 *  \param baseAddCbCr      Valid only for YUV420-NV12 format.
 *
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidPipeSetBufAddr(VpsHal_Handle handle,
                                  UInt32        field,
                                  UInt32        baseAddRGBY,
                                  UInt32        baseAddCbCr);

/**
 *  VpsHal_dssVidPipeEnable
 *  \brief Enables/Disables the Video pipeline
 *
 *  This function will Enable a particular video pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Handle to the Video pipeline hal object
 *  \param enable           enable or disable the pipeline.1-enable,0-disable.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidPipeEnable(VpsHal_Handle handle,
                              UInt32        enable);

Int32 VpsHal_dssWbPipeSetRegionBased(VpsHal_Handle handle,
                                     UInt32        enable);

Int32 VpsHal_dssSetCscCoeff(VpsHal_Handle          handle,
                            const Vps_DssCscCoeff *coeff);

Int32 VpsHal_dssEnablePipeIntr(UInt32       pipeHalId,
                               UInt32       enable);
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
Int32 VpsHal_dssConfWbDelayCnt(VpsHal_Handle          handle,
                               UInt32                 wbDelayCnt);
#endif
/* ========================================================================== */
/*                      Static Function Declarations                          */
/* ========================================================================== */
/**
 *  \brief VpsHal_dssIsWbPipe function.
 *
 *  Function to check whether the current instance is Writeback pipeline or not.
 *
 *  \param  halId   [IN] Hal ID for current instance. For valid values see
 *                       #VpsHal_DispcVidInstId #
 *
 */
static inline Int32 VpsHal_dssIsWbPipe(UInt32 halId);
/**
 *  \brief VpsHal_dssIsVidPipe function.
 *
 *  Function to check whether the current instance is video pipeline or not.
 *
 *  \param  halId   [IN] Hal ID for current instance. For valid values see
 *                       #VpsHal_DispcVidInstId #
 *
 */
static inline Int32 VpsHal_dssIsVidPipe(UInt32 halId);
/**
 *  \brief VpsHal_dssIsGfxPipe function.
 *
 *  Function to check whether the current instance is GRPX pipeline or not.
 *
 *  \param  halId   [IN] Hal ID for current instance. For valid values see
 *                       #VpsHal_DispcVidInstId #
 *
 */
static inline Int32 VpsHal_dssIsGfxPipe(UInt32 halId);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline Int32 VpsHal_dssIsVidPipe(UInt32 halId)
{
    Int32 retVal = (Int32) FALSE;

    if ((halId == VPSHAL_DSS_DISPC_VID1) ||
        (halId == VPSHAL_DSS_DISPC_VID2) ||
        (halId == VPSHAL_DSS_DISPC_VID3))
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static inline Int32 VpsHal_dssIsGfxPipe(UInt32 halId)
{
    Int32 retVal = (Int32) FALSE;

    if (halId == VPSHAL_DSS_DISPC_GFX)
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static inline Int32 VpsHal_dssIsWbPipe(UInt32 halId)
{
    Int32 retVal = (Int32) FALSE;

    if (halId == VPSHAL_DSS_DISPC_WB1)
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static inline void VpsHal_dssGfxPipeCfgInit(
    VpsHal_DssDispcGfxPipeCfg *gfxPipeCfg)
{
    if (gfxPipeCfg != NULL)
    {
        gfxPipeCfg->repliEnable       = (UInt32) FALSE;
        gfxPipeCfg->antiFlickerEnable = (UInt32) FALSE;
    }
}

static inline void VpsHal_dssVidPipeCfgInit(
    VpsHal_DssDispcVidPipeCfg *vidPipeCfg)
{
    if (vidPipeCfg != NULL)
    {
        vidPipeCfg->repliEnable      = (UInt32) FALSE;
        vidPipeCfg->scEnable         = VPS_DSS_DISPC_SC_NONE;
        vidPipeCfg->cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;
        vidPipeCfg->chromaSampling   = 0U;
    }
}

static inline void VpsHal_dssWbPipeCfgInit(
    VpsHal_DssDispcWbPipeCfg *wbPipeCfg)
{
    if (wbPipeCfg != NULL)
    {
        wbPipeCfg->scEnable         = VPS_DSS_DISPC_SC_NONE;
        wbPipeCfg->cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;
        wbPipeCfg->wbMode           = VPS_DSS_DISPC_WB_CAPT;
        wbPipeCfg->inNode           = VPS_DSS_DISPC_WB_IN_NODE_LCD1;
        wbPipeCfg->inSourceWidth    = 800;
        wbPipeCfg->inSourceHeight   = 480;
        wbPipeCfg->inWidth          = 800;
        wbPipeCfg->inHeight         = 480;
        wbPipeCfg->inPosX           = 0x0;
        wbPipeCfg->inPosY           = 0x0;
        wbPipeCfg->inDataFormat     = FVID2_DF_BGR24_888;

        Fvid2Format_init(&wbPipeCfg->outFmt);

        wbPipeCfg->outFmt.width      = 800;
        wbPipeCfg->outFmt.height     = 480;
        wbPipeCfg->outFmt.dataFormat = FVID2_DF_BGR24_888;
    }
}

static inline void VpsHal_dssAdvDmaConfigInit(
    VpsHal_DssDispcAdvDmaConfig *halAdvDmaCfg)
{
    if (halAdvDmaCfg != NULL)
    {
        /* TODO - Verify these values */
        halAdvDmaCfg->burstSize         = 0x2U; /* 8 × 128-bit bursts */
        halAdvDmaCfg->burstType         = 0U;
        halAdvDmaCfg->bufPreloadType    = 1U; /* Video Preload Value:
                                               * Hardware prefetches pixels
                                               * up to high threshold value.
                                               */
        halAdvDmaCfg->bufHighThreshold  = 0x07FFU;
        halAdvDmaCfg->bufLowThreshold   = 0x07F8U;
        halAdvDmaCfg->selfRefreshEnable = (UInt32) FALSE;
        halAdvDmaCfg->arbitration       = 0U;
        halAdvDmaCfg->pixelInc          = 1U;
        halAdvDmaCfg->rowInc            = 1U;
        halAdvDmaCfg->idleNumber        = 0U;
        halAdvDmaCfg->idleSize          = 0U;
    }
}

static inline void VpsHal_dssWbAdvDmaConfigInit(
    VpsHal_DssDispcAdvDmaConfig *halAdvDmaCfg)
{
    if (halAdvDmaCfg != NULL)
    {
        /* TODO - Verify these values */
        halAdvDmaCfg->burstSize         = 0x0U;
        halAdvDmaCfg->burstType         = 0U;
        halAdvDmaCfg->bufPreloadType    = 0U;
        halAdvDmaCfg->bufHighThreshold  = 0x016U;
        halAdvDmaCfg->bufLowThreshold   = 0x08U;
        halAdvDmaCfg->selfRefreshEnable = (UInt32) FALSE;
        halAdvDmaCfg->arbitration       = 0U;
        halAdvDmaCfg->pixelInc          = 1U;
        halAdvDmaCfg->rowInc            = 1U;
        halAdvDmaCfg->idleNumber        = 0U;
        halAdvDmaCfg->idleSize          = 0U;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_DISPC_VID_H_ */

