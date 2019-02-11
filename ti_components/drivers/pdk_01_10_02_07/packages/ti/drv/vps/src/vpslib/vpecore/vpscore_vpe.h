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
 *  \file vpscore_vpe.h
 *
 *  \brief VPS Core header file for VPE input path.
 *  This core is used by both display as well as in M2M drivers.
 *  In display mode, only one handle could be opened per instance, while in
 *  M2M mode each instance could be opened multiple times.
 *
 */

#ifndef VPSCORE_VPE_H_
#define VPSCORE_VPE_H_

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

/** \brief Instance ID for VPE in the primary main path. */
#define VCORE_VPE_INST_PRI              (0U)
/**
 *  \brief Maximum number of instance. Change this macro accordingly when
 *  number of instance is changed.
 */
#define VCORE_VPE_INST_MAX              (1U)

/** \brief Maximum number of handles supported per VPE path instance. */
#define VCORE_VPE_MAX_HANDLES           (16U)

/**
 *  \brief Maximum number of channels supported for all handles.
 *  When the core is configured in display mode, this is always 1.
 *  This is only used in M2M driver mode where software context makes sense.
 */
#define VCORE_VPE_MAX_CHANNELS          (40U)

/**
 *  \brief Maximum number of multiwindow settings that can be set for an
 *  instance. This is used in dynamic mosaic layout change.
 *  Note: When mosaic layout is supported in M2M mode, this should be
 *  changed to at least a minimum of VCORE_VPE_MAX_CHANNELS count, so that
 *  each channel could get one mosaic configuration memory.
 */
#define VCORE_VPE_MAX_MULTIWIN_SETTINGS (16U)

/**
 *  \brief Number of descriptors for VPE previous and current field output.
 *  One for Y buffer and other for CbCr buffer.
 */
#define VCORE_VPE_NUM_DESC_PER_FIELD    (2U)

/** \brief Luma index to the buffer address array in FVID frame structure. */
#define VCORE_VPE_Y_IDX                 (0U)
/** \brief Chroma index to the buffer address array in FVID frame structure. */
#define VCORE_VPE_CBCR_IDX              (1U)

/*
 *  Note:
 *  Below indices are provided in the same order in which the data
 *  descriptors will be programmed for each and every buffer.
 *  In bound and out bound index could be exchanged - only the order of
 *  the index within inbound or outbound should be maintained the same.
 *  Input luma and chroma indices are kept at the last of the inbound
 *  descriptors so that mosaic descriptors could continue after them.
 */
/*
 *  Caution:
 *  Always have VCORE_VPE_FLD1/2LUMA_IDX and VCORE_VPE_FLD1/2CHROMA_IDX value
 *  next to each other as some of the code involving loop depends on this fact.
 *  Also field 2 luma/chroma index should be next to field 1 luma/chroma.
 */
/** \brief VPE VPDMA channel index for previous N-1 field luma. */
#define VCORE_VPE_FLD1LUMA_IDX          (0U)
/** \brief VPE VPDMA channel index for previous N-1 field chroma. */
#define VCORE_VPE_FLD1CHROMA_IDX        (1U)
/** \brief VPE VPDMA channel index for previous N-2 field luma. */
#define VCORE_VPE_FLD2LUMA_IDX          (2U)
/** \brief VPE VPDMA channel index for previous N-2 field chroma. */
#define VCORE_VPE_FLD2CHROMA_IDX        (3U)
/** \brief VPE VPDMA channel index for previous N-3 field luma. */
#define VCORE_VPE_FLD3LUMA_IDX          (4U)
/** \brief VPE VPDMA channel index for previous N-3 field chroma. */
#define VCORE_VPE_FLD3CHROMA_IDX        (5U)

/** \brief VPE VPDMA channel index for MV N-1 input. */
#define VCORE_VPE_MV1_IDX               (6U)
/** \brief VPE VPDMA channel index for MV N-2 input. */
#define VCORE_VPE_MV2_IDX               (7U)
/** \brief VPE VPDMA channel index for MVSTM N-2 input. */
#define VCORE_VPE_MVSTM_IDX             (8U)

/** \brief VPE VPDMA channel index for current field luma. */
#define VCORE_VPE_FLD0LUMA_IDX          (9U)
/*
 *  Caution:
 *  Always have VCORE_VPE_FLD0LUMA_IDX and VCORE_VPE_FLD0CHROMA_IDX value
 *  next to each other as some of the code involving loop depends on this fact.
 */
/** \brief VPE VPDMA channel index for current field chroma. */
#define VCORE_VPE_FLD0CHROMA_IDX        (10U)

/** \brief VPE VPDMA channel index for top field output luma. */
#define VCORE_VPE_WRLUMA_IDX            (11U)
/** \brief VPE VPDMA channel index for top field output chroma. */
#define VCORE_VPE_WRCHROMA_IDX          (12U)
/*
 * Note: Below four indices are used in progressive TNR mode only.
 */
/** \brief VPE VPDMA channel index for top field output luma. */
#define VCORE_VPE_TOP_WRLUMA_IDX        (11U)
/** \brief VPE VPDMA channel index for top field output chroma. */
#define VCORE_VPE_TOP_WRCHROMA_IDX      (12U)
/** \brief VPE VPDMA channel index for Bottom field output luma. */
#define VCORE_VPE_BOT_WRLUMA_IDX        (13U)
/** \brief VPE VPDMA channel index for Bottom field output chroma. */
#define VCORE_VPE_BOT_WRCHROMA_IDX      (14U)

/** \brief VPE VPDMA channel index for MV output. */
#define VCORE_VPE_MVOUT_IDX             (15U)
/** \brief VPE VPDMA channel index for MVSTM output. */
#define VCORE_VPE_MVSTMOUT_IDX          (16U)

/** \brief Maximum number of VPDMA channels requried by VPE. */
#define VCORE_VPE_MAX_VPDMA_CH          (17U)

/** \brief Maximum number of previous field inputs requried by VPE. */
#define VCORE_VPE_MAX_PREV_FLD          (3U)
/** \brief Maximum number of Output field stored by VPE. */
#define VCORE_VPE_MAX_OUT_FLD           (2U)
/** \brief Maximum number of previous MV inputs requried by VPE. */
#define VCORE_VPE_MAX_MV_IN             (2U)
/** \brief Maximum number of previous MVSTM inputs requried by VPE. */
#define VCORE_VPE_MAX_MVSTM_IN          (1U)
/** \brief Number of CHR_US module required by VPE. */
#define VCORE_VPE_MAX_CHR_US            (3U)

/** \brief Maximum number of in bound VPDMA channels. */
#define VCORE_VPE_MAX_IN_CH             (11U)
/** \brief Maximum number of out bound VPDMA channels. */
#define VCORE_VPE_MAX_OUT_CH            (6U)

/** \brief Start of in bound VPDMA channels. */
#define VCORE_VPE_START_IN_CH           (0U)
/** \brief Start of out bound VPDMA channels. */
#define VCORE_VPE_START_OUT_CH          (11U)

/** \brief VPE index for CHR_US0 HAL. */
#define VCORE_VPE_CHRUS0_IDX            (0U)
/** \brief VPE index for CHR_US1 HAL - used when write client is not there. */
#define VCORE_VPE_CHRUS1_IDX            (1U)
/** \brief VPE index for CHR_US2 HAL - used when write client is not there. */
#define VCORE_VPE_CHRUS2_IDX            (2U)
/** \brief VPE index for DEI HAL. */
#define VCORE_VPE_DEI_IDX               (3U)
/** \brief VPE index for SC HAL. */
#define VCORE_VPE_SC_IDX                (4U)
/** \brief VPE index for VPDMA HAL. */
#define VCORE_VPE_VPDMA_IDX             (5U)
/** \brief Maximum number of HAL required by VPE. */
#define VCORE_VPE_MAX_HAL               (6U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vcore_VpeInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32              instId;
    /**< VPE Path Instance. */
    UInt32              maxHandle;
    /**< Maximum number of handles/channels to be supported per instance. */
    VpsHal_VpdmaChannel vpdmaCh[VCORE_VPE_MAX_VPDMA_CH];
    /**< Array to pass the VPDMA channel number required by core. */
    VpsHal_Handle       halHandle[VCORE_VPE_MAX_HAL];
    /**< Array to pass the HAL handles required by core. */
    VpsHal_VpdmaPath    vpdmaPath;
    /**< VPDMA Path name. */
} Vcore_VpeInitParams;

/**
 *  struct Vcore_VpeParams
 *  \brief VPE config parameters.
 */
typedef struct
{
    UInt32           frameWidth;
    /**< Frame width. */
    UInt32           frameHeight;
    /**< Frame height. */
    UInt32           startX;
    /**< Horizontal start position in pixels. */
    UInt32           startY;
    /**< Vertical start position in lines. */
    UInt32           secScanFmt;
    /** Secondary scan format. For input cores, this represents the scan format
     *  that needs to be sent out of the core. For output cores, this
     *  represents the input scan format for that core.
     *  For valid values see #Fvid2_ScanFormat. */
    UInt32           memType;
    /**< VPDMA Memory type. For valid values see #Vps_VpdmaMemoryType. */

    Fvid2_Format     fmt;
    /**< FVID frame format. */

    Vps_DeiConfig    deiCfg;
    /**< Deinterlacer parameters. */
    Vps_ScConfig     scCfg;
    /**< Scaler parameters. */
    Fvid2_CropConfig cropCfg;
    /**< Cropping parameters. */
    UInt32           tarWidth;
    /**< Target image Width. */
    UInt32           tarHeight;
    /**< Target image Height. */
} Vcore_VpeParams;

/**
 *  struct Vcore_VpeRtParams
 *  \brief VPE runtime configuration parameters.
 */
typedef struct
{
    Vps_FrameParams  *inFrmPrms;
    /**< Frame params for VPE input frame.
     *   Pass NULL if DEI is active or no change is required. */
    Fvid2_PosConfig  *posCfg;
    /**< Runtime position configuration containing startX and startY.
     *   Pass NULL if no change is required. */
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
} Vcore_VpeRtParams;

/**
 *  struct Vcore_VpeUpdateContext
 *  \brief VPE DEI context buffer information used to update the descriptors.
 */
typedef struct
{
    void  *prevInBuf[VCORE_VPE_MAX_PREV_FLD]
    [VCORE_VPE_NUM_DESC_PER_FIELD];
    /**< Pointer to the previous field input buffers. */
    UInt32 prevInFid[VCORE_VPE_MAX_PREV_FLD];
    /**< Corresponding field ID of the previous field input buffers. */
    void  *curOutBuf[VCORE_VPE_MAX_OUT_FLD]
    [VCORE_VPE_NUM_DESC_PER_FIELD];
    /**< Pointer to the current field output buffers. */

    void  *mvInBuf[VCORE_VPE_MAX_MV_IN];
    /**< Pointer to the MV input buffers. */
    UInt32 mvInFid[VCORE_VPE_MAX_MV_IN];
    /**< Corresponding field ID of the MV input buffers. */
    void  *mvOutBuf;
    /**< Pointer to the MV output buffer. */

    void  *mvstmInBuf[VCORE_VPE_MAX_MVSTM_IN + 1U];
    /**< Pointer to the MVSTM input buffers. */
    UInt32 mvstmInFid[VCORE_VPE_MAX_MVSTM_IN + 1U];
    /**< Corresponding field ID of the MVSTM input buffers. */
    void  *mvstmOutBuf;
    /**< Pointer to the MVSTM output buffer. */

    UInt32 prevFldState;
    /**< Represents the previous field state - used in DEI reset sequence
     *   to build up the DEI context and state. */
} Vcore_VpeUpdateContext;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vcore_vpeInit
 *  \brief VPE core init function.
 *  Initializes VPE core objects, allocates memory etc.
 *  This function should be called before calling any of VPE core API's.
 *
 *  \param numInst      [IN] Number of instance objects to be initialized.
 *  \param initPrms     [IN] Pointer to the init parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInst.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 Vcore_vpeInit(UInt32                     numInst,
                    const Vcore_VpeInitParams *initPrms);

/**
 *  Vcore_vpeDeInit
 *  \brief VPE core exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 Vcore_vpeDeInit(void);

/**
 *  Vcore_vpeGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const Vcore_M2mOps *Vcore_vpeGetCoreOps(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSCORE_VPE_H_ */
