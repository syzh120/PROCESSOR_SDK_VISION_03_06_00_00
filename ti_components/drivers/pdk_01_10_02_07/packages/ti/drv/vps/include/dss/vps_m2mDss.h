/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_M2M_DSS_API DSS M2M Interface API
 *
 *  This modules define APIs to DSS memory to memory driver in VPS.
 *
 *  DSS M2M Interface driver supports the following FVID2 APIs
 *  (see also \ref BSP_DRV_FVID2_API)
 *
 * - <b> Creating the driver </b> - Fvid2_create()
 *   <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>drvId</td>
 *      <td>\ref FVID2_VPS_DSS_M2M_DRV</td>
 *    </tr>
 *    <tr>
 *      <td>instanceId</td>
 *      <td>
 *          Driver specific instance id
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createArgs</td>
 *      <td>
 *      Vps_M2mDssCreateParams *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createStatusArgs</td>
 *      <td>
 *      Vps_M2mDssCreateStatus *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>cbParams</td>
 *      <td>
 *      Fvid2_CbParams *
 *
 *      When Fvid2_CbParams.cbFxn is set, Fvid2_CbParams.cbFxn
 *      gets called for every request completion.
 *
 *      </td>
 *    </tr>
 *  </table>
 *  \ref Fvid2_Handle returned by Fvid2_create() is used in subsequent FVID2
 *  APIs
 *
 * - <b> Deleting the driver </b> - Fvid2_delete()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>handle</td>
 *      <td>M2M driver handle</td>
 *    </tr>
 *    <tr>
 *      <td>deleteArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 *  - <b> Controlling the driver </b> - Fvid2_control() <br>
 *  See \ref BSP_DRV_IOCTL_VPS_DSS_M2M for the list of IOCTLs
 *  supported by the driver.
 *
 *  M2M driver application flow is as follows
 *
 *  - <b> Init all required modules by calling respective module init
 *    functions </b>
 *  - <b> Create driver using Fvid2_create() </b>
 *  - <b> Set driver specific parameters using Fvid2_control() </b> <br>
 *  - <b> Provide frames for processing using Fvid2_processRequest() </b>
 *  - <b> Dequeue processed frame using Fvid2_getProcessedRequest() </b>
 *  - <b> Delete M2M driver using Fvid2_delete() </b>
 *  - <b> De-Init modules by calling respective module de-init functions </b>
 *
 *  @{
 */

/**
 *  \file vps_m2mDss.h
 *
 *  \brief FVID2 Interface for the DSS M2M driver.
 */

#ifndef VPS_M2M_DSS_H_
#define VPS_M2M_DSS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/common/bsp_cfgMem.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  Macros used to identify different drivers, expected to be passed as the
 *  instance ID, during driver creation.
 *  Each writback path results in one instance of the driver.
 *
 *  Note: These are read only macros. Don't modify the value of these macros.
 */
/** \brief DSS WB0 memory driver instance number. */
#define VPS_M2M_DSS_INST_WB1                (0U)

/**
 *  \brief Maximum number of M2M DSS driver instance.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_DSS_INST_MAX                (1U)

/**
 *  \name M2M interface max limits or defaults.
 *
 *  @{
 */

/**
 *  \brief Maximum number of handles supported by M2M driver per
 *  driver instance.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_DSS_MAX_HANDLE_PER_INST     (1U)

/** \brief Default max number of M2M operation request that can be
 *        queued per handle. */
#define VPS_M2M_DSS_DEF_QUEUE_LEN           (BSP_CFG_M2M_DSS_QUEUE_LEN_HANDLE)

/* @} */

/* M2M IOCTL's */

/**
 *  \brief M2M Generic Interface IOCTL base.
 *  VPS_M2M_IOCTL_BASE + 0x100U to 0x300U already used by other M2M drivers
 */
#define VPS_M2M_DSS_IOCTL_BASE              (VPS_M2M_IOCTL_BASE + 0x0400U)

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_DSS_M2M
 *  @{
 */

/**
 *  \brief Set DSS M2M parameters.
 *
 *  This IOCTL can be used to set the DSS hardware specific parameters.
 *  This IOCTL should be called after creating DSS M2M driver instance
 *  and before queueing or starting the M2M driver. Starting the M2M
 *  driver without calling this IOCTL will result in error.
 *
 *  Once the operation is started this IOCTL can't be invoked and will result in
 *  error.
 *
 *  Once the M2M driver is stopped, application could call this IOCTL to
 *  reconfigure the DSS block with a different set of parameters.
 *
 *  \param cmdArgs       [IN]  const Vps_M2mDssParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_M2M_DSS_SET_PARAMS        (VPS_M2M_DSS_IOCTL_BASE + 0x0000U)

/**
 *  \brief Set M2M DSSWB CSC Coefficients IOCTL.
 *
 *  This IOCTL can be used to set the CSC coefficients.
 *  Note: Default BT601 coefficients are set.
 *
 *  \param cmdArgs       [IN] const Vps_M2mDssCscCoeffParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */
#define IOCTL_VPS_M2M_DSS_SET_CSC_COEFF     (VPS_M2M_DSS_IOCTL_BASE + 0x0001U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_M2mDssCreateParams
 *  \brief M2M create parameter structure to be passed to the
 *  driver at the time of mem to mem driver create call.
 */
typedef struct
{
    /*
     * Resource allocation parameters.
     */
    UInt32                      wbInNode;
    /**< Input pipe/overlay that is connected to writeback pipeline.
     *   See notes of numInPipeLines below.
     *   For valid values see #Vps_DssDispcWbInNode. */
    UInt32                      numInPipeLines;
    /**< Number of input pipelines connected to the overlay.
     *
     *   This parameter should be set to 1 or above.
     *   When a video or grpx pipeline is directly connected to the WB path,
     *   this should be set to 1 and the wbInNode should point to that
     *   particular input pipeline.
     *   When blending of more than one pipeline is required, this should be set
     *   to the number of video/grpx pipelines connected to the overlay. In
     *   this case the wbInNode should be set to the corresponding overlay.
     */
    UInt32                      inPipeLines[VPS_DSS_DISPC_PIPE_MAX];
    /**< List of input pipelines connected to the overlay or to the WB directly.
     *
     *   For valid values see #Vps_DssDispcPipes.
     *   Note: WB nodes out of #Vps_DssDispcPipes should not be used
     */

    /*
     * Other driver parameters
     */
    UInt32                      inQueueLength;
    /**< [IN] Maximum number of request/frame per channel that can be submitted
     *   for M2M operation without having to dequeue the requests. */
    void                       *reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Vps_M2mDssCreateParams;

/**
 *  sturct Vps_M2mDssCreateStatus
 *  \brief Create status for the M2M create call. This should be
 *  passed to the create function as a create status argument while creating
 *  the driver.
 */
typedef struct
{
    Int32                       retVal;
    /**< Return value of create call. */
    UInt32                      maxHandles;
    /**< Maximum number of handles supported by driver per instance. */
    void                       *reserved;
    /**< Driver specific additional create status params.
     *   Not used set to NULL */
} Vps_M2mDssCreateStatus;

/**
 *  \brief DSS M2M input pipe parameters.
 */
typedef struct
{
    UInt32                      inPipeId;
    /**< Input pipeline ID to which this parameter applies.
     *
     *   For valid values see #Vps_DssDispcPipes.
     *   Note: WB nodes out of #Vps_DssDispcPipes should not be used
     */
    Fvid2_Format                inFmt;
    /**< Input FVID frame format.
     *
     *   <b>width</b>:<br>
     *   Input width, in pixels.
     *   This represents the input width in memory.
     *
     *   <b>height</b>:<br>
     *   Input  height, in lines.
     *   This represents the input height in memory.
     *
     *   <b>dataFormat</b>:<br>
     *   Input Data format, valid options for TDA3XX are<br>
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_RGB16_565,<br>
     *   FVID2_DF_BGR24_888,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV422I_UYVY.<br>
     *
     *   Input Data format, valid options for TDA2XX/TDA2EX are<br>
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_BGR24_888,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422I_UYVY,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines.
     *   And should be aligned to VPS_BUFFER_ALIGNMENT.<br>
     *
     *   <b>fieldMerged, chNum, scanFormat, bpp</b>: Not used, set to 0
     *   or default. */
    UInt32                      tarWidth;
    /**< Horizontal Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                      tarHeight;
    /**< Verticle Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                      posX;
    /**< X position of the frame in the output window when overlay
     *   is used. */
    UInt32                      posY;
    /**< Y position of the frame in the output window when overlay
     *   is used. */
    UInt32                      memType;
    /**< Memory type. For valid values see #Vps_VpdmaMemoryType.
     *   Note: Tiler Memory is not supported as of now, user should set this
     *   to VPS_VPDMA_MT_NONTILEDMEM. */
    Vps_DssDispcVidConfig       vidCfg;
    /**< Video Configuration structure, applicable only for Video pipeline
     *   instances. Leave it to default values for graphics pipeline */
    Vps_DssDispcGfxConfig       gfxCfg;
    /**< Graphics Configuration structure, applicable only for Graphics pipeline
     *   instances. Leave it to default values for video pipeline */
    Vps_DssDispcOvlyPipeConfig  ovlyPipeCfg;
    /**< Overlay configuration per pipe, applicable only when WB is through
     *   overlay. */
} Vps_M2mDssInPipeParams;

/**
 *  \brief DSS M2M output parameters.
 */
typedef struct
{
    Fvid2_Format                outFmt;
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
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_RGB16_565,<br>
     *   FVID2_DF_BGR24_888,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV422I_UYVY.<br>
     *
     *   Output Data format, valid options for TDA2XX/TDA2EX are<br>
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_BGR24_888,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422I_UYVY,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines.It should be (BPP * Width)
     *   No other value is supported.
     *   And should be aligned to VPS_BUFFER_ALIGNMENT.<br>
     *
     *   <b>fieldMerged, chNum, scanFormat, bpp</b>: Not used, set to 0
     *   or default. */
    UInt32                      memType;
    /**< Tiled or non-tiled memory selection for output.
     *   For valid values see #Vps_VpdmaMemoryType.
     *   NON_TILED is not supported for both TDA2XX and TDA3XX . */
    UInt32                      scEnable;
    /**< TRUE: Use scaler before writing video data to memory,
     *   FALSE: Scaler is not used in capture path. */
    UInt32                      cscFullRngEnable;
    /**< TRUE: Use CSC full range,
     *   FALSE: Limited range CSC is used. */
    UInt32                      cropEnable;
    /**< Set to TRUE if inFmt.width and inCropCfg.cropWidth are not same and/or
     *   inFmt.height and inCropCfg.cropHeight are not same
     *   Note: This is not applicable for TDA2xx/TDA2Ex. Set to FALSE. */
    Fvid2_CropConfig            cropCfg;
    /**< DSS WB input crop config. Not valid for TDA2XX/TDA2Ex platforms.
     *   For TDA3XX platform for full frame write back,
     *   height and width of crop config should be same as in inFmt */
    Vps_DssDispcAdvDmaConfig   *advDmaCfg;
    /**< Advanced DMA Configuration structure. For default values pass NULL */
} Vps_M2mDssOutPipeParams;

/**
 *  \brief DSS M2M parameters used in set DSS M2M params IOCTL.
 */
typedef struct
{
    UInt32                      ovlyWidth;
    /**< Width of overlay when WB is captured from an overlay. Otherwise
     *   this is not applicable and can be set to zero.
     */
    UInt32                      ovlyHeight;
    /**< Height of overlay when WB is captured from an overlay. Otherwise
     *   this is not applicable and can be set to zero.
     */
    Vps_DssDispcOvlyPanelConfig ovlyCfg;
    /**< Overlay configuration applicable only when WB is captured from
     *   an overlay. Otherwise set this to default values. */
    Vps_M2mDssInPipeParams      inPipePrms[VPS_DSS_DISPC_PIPE_MAX];
    /**< Input pipe parameters. User should set this as per the number of
     *   input pipes configured at create time. */
    Vps_M2mDssOutPipeParams     outPipePrms;
    /**< WB output parameters. */
} Vps_M2mDssParams;

/**
 *  \brief DSS M2M CSC coeff parameters used in set CSC COEFF IOCTL.
 */
typedef struct
{
    UInt32                      inPipeId;
    /**< Input pipeline ID to which this parameter applies.
     *
     *   For valid values see #Vps_DssDispcPipes.
     *   Note: WB nodes out of #Vps_DssDispcPipes should not be used
     */
    Vps_DssCscCoeff             cscCoeff;
    /**< Params for CSC Coefficients for YUV to RGB color conversion */
} Vps_M2mDssCscCoeffParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_M2mDssCreateParams structure init function.
 *
 *  \param createPrms   [IN] Pointer to #Vps_M2mDssCreateParams structure.
 *
 */
static inline void VpsM2mDssCreateParams_init(
    Vps_M2mDssCreateParams *createPrms);

/**
 *  \brief Vps_M2mDssCreateStatus structure init function.
 *
 *  \param createStatus [IN] Pointer to #Vps_M2mDssCreateStatus structure.
 *
 */
static inline void VpsM2mDssCreateStatus_init(
    Vps_M2mDssCreateStatus *createStatus);

/**
 *  \brief Vps_M2mDssInPipeParams structure init function.
 *
 *  \param inPipePrms   [IN] Pointer to #Vps_M2mDssInPipeParams structure.
 *
 */
static inline void VpsM2mDssInPipeParams_init(
    Vps_M2mDssInPipeParams *inPipePrms);

/**
 *  \brief Vps_M2mDssOutPipeParams structure init function.
 *
 *  \param outPipePrms  [IN] Pointer to #Vps_M2mDssOutPipeParams structure.
 *
 */
static inline void VpsM2mDssOutPipeParams_init(
    Vps_M2mDssOutPipeParams *outPipePrms);

/**
 *  \brief Vps_M2mDssParams structure init function.
 *
 *  \param dssPrms      [IN] Pointer to #Vps_M2mDssParams structure.
 *
 */
static inline void VpsM2mDssParams_init(Vps_M2mDssParams *dssPrms);

/**
 *  \brief Vps_M2mDssCscCoeffParams structure init function.
 *
 *  \param coeffPrms    [IN] Pointer to #Vps_M2mDssCscCoeffParams structure.
 *
 */
static inline void VpsM2mDssCscCoeffParams_init(
    Vps_M2mDssCscCoeffParams *coeffPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsM2mDssCreateParams_init(
    Vps_M2mDssCreateParams *createPrms)
{
    UInt32 i;

    if (NULL != createPrms)
    {
        createPrms->wbInNode            = VPS_DSS_DISPC_WB_IN_NODE_VID1;
        createPrms->numInPipeLines      = 1U;
        for (i = 0U; i < VPS_DSS_DISPC_PIPE_MAX; i++)
        {
            createPrms->inPipeLines[i]  = 0U;   /* Reset to zero first */
        }
        /* Override with VID1 pipe as default */
        createPrms->inPipeLines[0U]     = VPS_DSS_DISPC_PIPE_VID1;
        createPrms->inQueueLength       = VPS_M2M_DSS_DEF_QUEUE_LEN;
        createPrms->reserved            = NULL;
    }

    return;
}

static inline void VpsM2mDssCreateStatus_init(
    Vps_M2mDssCreateStatus *createStatus)
{
    if (NULL != createStatus)
    {
        createStatus->retVal        = FVID2_SOK;
        createStatus->maxHandles    = 0U;
        createStatus->reserved      = NULL;
    }
}

static inline void VpsM2mDssInPipeParams_init(
    Vps_M2mDssInPipeParams *inPipePrms)
{
    if (NULL != inPipePrms)
    {
        Fvid2Format_init(&inPipePrms->inFmt);
        inPipePrms->inPipeId    = VPS_DSS_DISPC_PIPE_VID1;
        inPipePrms->tarWidth    = 720U;
        inPipePrms->tarHeight   = 480U;
        inPipePrms->posX        = 0U;
        inPipePrms->posY        = 0U;
        inPipePrms->memType     = VPS_VPDMA_MT_NONTILEDMEM;
        VpsDssDispcVidConfig_init(&inPipePrms->vidCfg);
        VpsDssDispcGfxConfig_init(&inPipePrms->gfxCfg);
        VpsDssDispcOvlyPipeConfig_init(&inPipePrms->ovlyPipeCfg);
    }
}

static inline void VpsM2mDssOutPipeParams_init(
    Vps_M2mDssOutPipeParams *outPipePrms)
{
    if (NULL != outPipePrms)
    {
        Fvid2Format_init(&outPipePrms->outFmt);
        Fvid2CropConfig_init(&outPipePrms->cropCfg);
        outPipePrms->memType            = VPS_VPDMA_MT_NONTILEDMEM;
        outPipePrms->scEnable           = (UInt32) FALSE;
        outPipePrms->cscFullRngEnable   = (UInt32) TRUE;
        outPipePrms->cropEnable         = (UInt32) FALSE;
        outPipePrms->advDmaCfg          = NULL;
    }
}

static inline void VpsM2mDssParams_init(Vps_M2mDssParams *dssPrms)
{
    UInt32 i;

    if (NULL != dssPrms)
    {
        dssPrms->ovlyWidth  = 720U;
        dssPrms->ovlyHeight = 480U;
        VpsDssDispcOvlyPanelConfig_init(&dssPrms->ovlyCfg);
        for (i = 0U; i < VPS_DSS_DISPC_PIPE_MAX; i++)
        {
            VpsM2mDssInPipeParams_init(&dssPrms->inPipePrms[i]);
        }
        VpsM2mDssOutPipeParams_init(&dssPrms->outPipePrms);
    }
}

static inline void VpsM2mDssCscCoeffParams_init(
    Vps_M2mDssCscCoeffParams *coeffPrms)
{
    if (NULL != coeffPrms)
    {
        coeffPrms->inPipeId = VPS_DSS_DISPC_PIPE_VID1;
        VpsDssCscCoeff_init(&coeffPrms->cscCoeff);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_M2M_DSS_H_ */

/*  @}  */
