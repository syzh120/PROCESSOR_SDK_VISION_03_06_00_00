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
 *  \ingroup BSP_DRV_VPS_M2M_API
 *  \defgroup BSP_DRV_VPS_M2M_VPE_API M2M VPE API
 *
 *  This modules define APIs for memory to memory operation using VPE in VPS.
 *  @{
 */

/**
 *  \file vps_m2mVpe.h
 *
 *  \brief Interface specific to VPE memory to memory driver.
 */

#ifndef VPS_M2MVPE_H_
#define VPS_M2MVPE_H_

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

/*
 *  VPE M2M driver.
 */
/* None */

/**
 *  \brief Scaler IDs in memory write back
 *
 *  Expected to be used to get/set scaler parameters
 *  It addresses SC1.
 */
#define VPS_M2M_VPE_SCALER_ID_SC0       (0U)

/*
 *  Macros used to identify different drivers, expected to be passed as the
 *  instance ID, during driver creation.
 *
 *  Note: These are read only macros. Don't modify the value of these macros.
 */
/** \brief VPE 1 memory driver instance number. */
#define VPS_M2M_INST_VPE1               (0U)

/**
 *  \brief Maximum number of M2M VPE driver instance.
 *  Note: This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_VPE_INST_MAX            (1U)

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_M2M_VPE
 *  @{
 */

/**
 *  \brief Set VPE parameters.
 *
 *  This IOCTL can be used to set the VPE hardware specific parameters.
 *  This IOCTL should be called after creating VPE M2M driver instance
 *  and before queueing or starting the M2M driver. Starting the M2M
 *  driver without calling this IOCTL will result in error.
 *
 *  Once the operation is started this IOCTL can't be invoked and will result in
 *  error.
 *
 *  Once the M2M driver is stopped, application could call this IOCTL to
 *  reconfigure the VPE block with a different set of parameters.
 *
 *  \param cmdArgs       [IN]  const Vps_M2mVpeParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_M2M_SET_VPE_PARAMS    (VPS_M2M_VPE_IOCTL_BASE + 0x0000U)

/**
 *  \brief Get VPE parameters.
 *
 *  This IOCTL can be used to get the VPE hardware parameters.
 *  This IOCTL could be called at anytime after creating VPE M2M
 *  driver instance.
 *
 *  \param cmdArgs       [IN]  Vps_M2mVpeParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_M2M_GET_VPE_PARAMS    (VPS_M2M_VPE_IOCTL_BASE + 0x0001U)

/**
 *  \brief M2M VPE IOCTL to replace the internal state of the previous
 *  field buffers.
 *
 *  This IOCTL could be used by the application to control the previous fields
 *  used to deinterlace the next request. This will be useful if the application
 *  wants to operate with lower FPS and still wants to perform proper
 *  deinterlacing operation.
 *
 *  The driver will return the FVID2 frames held by the driver in the same
 *  input structure.
 *
 *  When using this IOCTL the application should ensure that there is no
 *  input request pending with the driver. Otherwise the driver will return
 *  error.
 *
 *  \param cmdArgs       [IN/OUT]   Vps_M2mVpeOverridePrevFldBuf *
 *  \param cmdStatusArgs [OUT]      NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_VPE_OVERRIDE_PREV_FLD_BUF (VPS_M2M_VPE_IOCTL_BASE + 0x0002U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPE parameters used in set/get VPE params IOCTL.
 */
typedef struct
{
    UInt32       chNum;
    /**< Channel number to which to apply or get the parameter.
     *   This should br 0 to (numCh - 1), which is passed during create
     *   time. */
    Fvid2_Format inFmt;
    /**<
     *   Frame format for the input frame to the VPE. Details as below
     *
     *   <b>chNum</b>:<br>
     *   Set to the channel number - same as 'chNum' of this structure.<br>
     *
     *   <b>width</b>:<br>
     *   Input width, in pixels.<br>
     *
     *   <b>height</b>:<br>
     *   Input height, in lines.<br>
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines.
     *   Pitch can be specified separately for every plane.
     *   And should be aligned to VPS_BUFFER_ALIGNMENT.<br>
     *
     *   <b>fieldMerged</b>:<br>
     *   Not used - Set to FALSE.<br>
     *
     *   <b>dataFormat</b>:<br>
     *   Input Data format, valid options are<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422SP_UV,<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   <b>scanFormat</b>:<br>
     *   In case of interlaced input set this to FVID2_SF_INTERLACED.<br>
     *   In case of progressive input set this to FVID2_SF_PROGRESSIVE.<br>
     *
     *   <b>bpp</b>: Not used, set to 0 or default. */
    Fvid2_Format outFmt;
    /**<
     *   Frame format for the output frame to the VPE. Details as below
     *
     *   <b>chNum</b>:<br>
     *   Set to the channel number - same as 'chNum' of this structure.<br>
     *
     *   <b>width</b>:<br>
     *   Output width, in pixels.<br>
     *
     *   <b>height</b>:<br>
     *   Output height, in lines.<br>
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines.
     *   Pitch can be specified separately for every plane.
     *   And should be aligned to VPS_BUFFER_ALIGNMENT.<br>
     *
     *   <b>fieldMerged</b>:<br>
     *   Not used - Set to FALSE.<br>
     *
     *   <b>dataFormat</b>:<br>
     *   Output Data format, valid options are<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422SP_UV,<br>
     *   FVID2_DF_RGB24_888,<br>
     *   FVID2_DF_YUV444I,<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   <b>scanFormat</b>:<br>
     *   For both deinterlacing and progressive bypass mode, set this
     *   to FVID2_SF_PROGRESSIVE.<br>
     *
     *   <b>bpp</b>: Not used, set to 0 or default. */

    UInt32             inMemType;
    /**< VPDMA Memory type for the VPE input frame.
     *   For valid values see #Vps_VpdmaMemoryType. */
    UInt32             outMemType;
    /**< VPDMA Memory type for the VPE writeback output frame.
     *   For valid values see #Vps_VpdmaMemoryType. */

    Vps_DeiConfig      deiCfg;
    /**< Pointer to the deinterlacer configuration used for
     *   VPE drivers. */

    Vps_ScConfig       scCfg;
    /**< Pointer to the scaler parameters like crop and scaler type for the
     *   scaler in VPE path. */
    Fvid2_CropConfig   scCropCfg;
    /**< Pointer to the cropping configuration for the VPE scaler. */
    Vps_SubFrameParams subFramePrms;
    /**< SubFrame mode parameters. */
} Vps_M2mVpeParams;

/**
 *  struct Vps_M2mVpeRtParams
 *  \brief Run time configuration structure for the VPE memory to memory
 *  driver. This needs to be passed along with process list to
 *  update any supported run time parameters.
 */
typedef struct
{
    Vps_FrameParams *inFrmPrms;
    /**< Frame params for VPE input frame.
     *   Pass NULL if compressor is enabled or no change is required.
     *
     *   When in deinterlacing mode or in progressive TNR mode, the application
     *   has to allocate bigger context buffer memory depending on the
     *   max input resolution it might change. Driver has no way of
     *   validating the actual allocated size and hence this might lead to
     *   buffer over flow in case max size is not allocated.
     *   Also at the time of input resolution change 2-3 frames after this
     *   will be invalid because of invalid context buffer content. And
     *   hence application should ignore these frames.
     *   Refer #Vps_DeiCtxInfo structure documentation on how to calculate
     *   the context buffer sizes for a given width and height.
     *
     *   This runtime parameter can't be used when compressor is enabled.
     *
     *   Note: When the application changes the input frame parameters and
     *   if the DEI scaler crop configuration is not provided, the
     *   driver changes the scaler crop configuration as per the new input
     *   resolution i.e. cropWidth/cropHeight will be the new input
     *   width/height and cropStartX/cropStartY will be 0. */
    Vps_FrameParams  *outFrmPrms;
    /**< Frame params for VPE writeback output frame.
     *   Pass NULL if no change is required or this output is not used
     *   by an instance. */
    Fvid2_CropConfig *scCropCfg;
    /**< Scaler crop configuration for VPE scaler.
     *   Pass NULL if no change is required or this scaler is not used
     *   by an instance. */
    Vps_ScRtConfig   *scRtCfg;
    /**< Scaler runtime configuration for VPE scaler.
     *   Pass NULL if no change is required or this scaler is not used
     *   by an instance. */
    Vps_DeiRtConfig  *deiRtCfg;
    /**< DEI runtime configuration.
     *   Pass NULL if no change is required. */
} Vps_M2mVpeRtParams;

/**
 *  struct Vps_M2mVpeOverridePrevFldBuf
 *  \brief Structure used to override the previous field context buffers.
 */
typedef struct
{
    Fvid2_FrameList *fldBufFrameList[VPS_DEI_MAX_CTX_FLD_BUF];
    /**< [IN] FVID2 frame list containing the previous field buffers for the
     *   requried channels.
     *
     *   chNum in Fvid2_Frame will be used to update the corresponding
     *   channel field buffers in driver objects.
     *
     *   numFrames in all the Fvid2_FrameList should be same and less than
     *   numCh created during Fvid2_create.
     *
     *   N-1 field buffer is at index 0, N-2 at index 1 and so on. */
    UInt32 numFldBufLists;
    /**< [IN] Number of previous field buffer frame lists. In case of
     *   TI814x/TI807 this should be set to 2 as the DEI IP in these
     *   platforms takes in only N-1 and N-2 inputs. */
} Vps_M2mVpeOverridePrevFldBuf;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_M2mVpeParams structure init function.
 *
 *  \param vpePrms      [IN] Pointer to #Vps_M2mVpeParams structure.
 *
 */
static inline void VpsM2mVpeParams_init(Vps_M2mVpeParams *vpePrms);

/**
 *  \brief Vps_M2mVpeRtParams structure init function.
 *
 *  \param rtPrms       [IN] Pointer to #Vps_M2mVpeRtParams structure.
 *
 */
static inline void VpsM2mVpeRtParams_init(Vps_M2mVpeRtParams *rtPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsM2mVpeParams_init(Vps_M2mVpeParams *vpePrms)
{
    if (NULL != vpePrms)
    {
        /* Default to D1 YUV422I -> D1 YUV422I with DEI and SC bypassed */
        vpePrms->chNum      = 0U;
        vpePrms->inMemType  = VPS_VPDMA_MT_NONTILEDMEM;
        vpePrms->outMemType = VPS_VPDMA_MT_NONTILEDMEM;

        Fvid2Format_init(&vpePrms->inFmt);
        vpePrms->inFmt.width  = 720U;
        vpePrms->inFmt.height = 480U;
        vpePrms->inFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
            (vpePrms->inFmt.width * 2U);
        vpePrms->inFmt.dataFormat = FVID2_DF_YUV422I_YUYV;

        Fvid2Format_init(&vpePrms->outFmt);
        vpePrms->outFmt.width  = 720U;
        vpePrms->outFmt.height = 480U;
        vpePrms->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
            (vpePrms->outFmt.width * 2U);
        vpePrms->outFmt.dataFormat = FVID2_DF_YUV422I_YUYV;

        VpsDeiConfig_init(&vpePrms->deiCfg);
        VpsScConfig_init(&vpePrms->scCfg);

        Fvid2CropConfig_init(&vpePrms->scCropCfg);
        vpePrms->scCropCfg.cropWidth  = vpePrms->inFmt.width;
        vpePrms->scCropCfg.cropHeight = vpePrms->inFmt.height;

        VpsSubFrameParams_init(&vpePrms->subFramePrms);
    }

    return;
}

static inline void VpsM2mVpeRtParams_init(Vps_M2mVpeRtParams *rtPrms)
{
    if (NULL != rtPrms)
    {
        rtPrms->inFrmPrms  = NULL;
        rtPrms->outFrmPrms = NULL;
        rtPrms->scCropCfg  = NULL;
        rtPrms->scRtCfg    = NULL;
        rtPrms->deiRtCfg   = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_M2MVPE_H_ */

/*  @}  */
