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
 *  \addtogroup BSP_DRV_VPS_COMMON_DEI
 *
 *  @{
 */

/**
 *  \file vps_cfgDei.h
 *
 *  \brief VPS - De-interlacer Configurations options interface
 */

#ifndef VPS_CFG_DEI_H_
#define VPS_CFG_DEI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* ========================================================================== */
/* Include HW specific advance config constants, structures                   */
/* ========================================================================== */

#include <ti/drv/vps/include/vpe/vps_advCfgDei.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of field buffers requried by DEI. */
#define VPS_DEI_MAX_CTX_FLD_BUF         (4U)
/** \brief Maximum number of MV buffers requried by DEI. */
#define VPS_DEI_MAX_CTX_MV_BUF          (3U)
/** \brief Maximum number of MVSTM buffers requried by DEI. */
#define VPS_DEI_MAX_CTX_MVSTM_BUF       (3U)

/**
 *  enum Vps_DeiFmdJamDir
 *  \brief Enumerations for field jamming direction, used in
 *         Film Mode Detection (FMD)
 */
typedef enum
{
    VPS_DEI_FMDJAMDIR_PREV_FLD = 0,
    /**< Curr fld jammed with previous fld. */
    VPS_DEI_FMDJAMDIR_NEXT_FLD
    /**< Curr fld jammed with next fld. */
} Vps_DeiFmdJamDir;

/**
 *  enum Vps_DeiEdiMode
 *  \brief Enumerations for DEI Edge Directed Interpolation (EDI) mode.
 */
typedef enum
{
    VPS_DEI_EDIMODE_LINE_AVG = 0,
    /**< Line average. */
    VPS_DEI_EDIMODE_FLD_AVG,
    /**< Field average. */
    VPS_DEI_EDIMODE_LUMA_ONLY,
    /**< EDI for Luma only. */
    VPS_DEI_EDIMODE_LUMA_CHROMA,
    /**< EDI for Luma and Chroma. */
    VPS_DEI_EDIMODE_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} Vps_DeiEdiMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_DeiFmdConfig
 *  \brief DEI FMD configuration.
 */
typedef struct
{
    UInt32 chNum;
    /**< Channel number for which the configuration is to be set/get.
     *   Used only in M2M driver, for display and capture driver set
     *   this to 0. */
    UInt32 filmMode;
    /**< Enable Film mode. */
    UInt32 bed;
    /**< Enable Bad edit detection. */
    UInt32 window;
    /**< Enable FMD operation window. */
    UInt32 lock;
    /**< Lock Deinterlacer to film mode. */
    UInt32 jamDir;
    /**< Field jamming direction. For valid values see #Vps_DeiFmdJamDir. */
    UInt16 windowMinx;
    /**< Left boundary of FMD window */
    UInt16 windowMiny;
    /**< Top boundary of FMD window */
    UInt16 windowMaxx;
    /**< Right boundary of FMD window */
    UInt16 windowMaxy;
    /**< Bottom boundary of FMD window */
    UInt32 cafThr;
    /**< CAF threshold used for leaving film mode:  If the
     *   combing artifacts is greater than this threshold, CAF
     *   is detected and thus the state machine will be forced
     *   to leave the film mode. If the user prefers to be more
     *   conservative in using film mode, decrease this threshold. */
    UInt32 cafLineThr;
    /**< CAF threshold used for the pixels from two lines in one
     *   field. This is the threshold used for combing artifacts
     *   detection. The difference of two consecutive lines from
     *   the same field (so there is one line in between if two
     *   fields are merged into one progressive frame) is compared
     *   with this threshold. Decreasing this threshold leads to
     *   be more conservative in detecting CAF. Both
     *   fmd_caf_field_thr and fmd_caf_line_thr are close the values
     *   that two pixels differed by this value is observable. */
    UInt32 cafFieldThr;
    /**< CAF threshold used for the pixels from two fields.
     *   This is the threshold used for combing artifacts detection.
     *   The difference of two consecutive lines (when merging two
     *   fields into one progressive frame) is used to compare with
     *   this threshold. Increasing this threshold leads to be more
     *   conservative in detecting CAF. */
    UInt32 frameDiff;
    /**< Frame difference (difference between two top or two bottom fields).
     *   Read only parameter. */
    UInt32 fldDiff;
    /**< Field difference (difference between two neighboring fields, one
     *   top and one bottom).
     *   Read only parameter. */
    UInt32 reset;
    /**< When 1, the film mode detection module needs to be reset by
     *   the software. This bit needs to be checked at each occurrence
     *   of the film mode detection interrupt.
     *   Read only parameter. */
    UInt32 caf;
    /**< Detected combing artifacts.
     *   Read only parameter. */
} Vps_DeiFmdConfig;

/**
 *  struct Vps_DeiFmdUpdateConfig
 *  \brief DEI FMD Set Result configuration.
 */
typedef struct
{
    UInt32 chNum;
    /**< Channel number for which the configuration is to be set/get.
     *   Used only in M2M driver, for display and capture driver set
     *   this to 0. */
    UInt32 lock;
    /**< Lock Deinterlacer to film mode. */
    UInt32 jamDir;
    /**< Jamming direction. */
} Vps_DeiFmdUpdateConfig;

/**
 *  struct Vps_DeiFmdStatusReg
 *  \brief DEI FMD status register configuration.
 */
typedef struct
{
    UInt32 chNum;
    /**< Channel number for which the configuration is to be set/get.
     *   Used only in M2M driver, for display and capture driver set
     *   this to 0. */
    UInt32 frameDiff;
    /**< Frame difference (difference between two top or two bottom fields).
     *   Read only parameter. */
    UInt32 fldDiff;
    /**< Field difference (difference between two neighboring fields, one
     *   top and one bottom).
     *   Read only parameter. */
    UInt32 reset;
    /**< When 1, the film mode detection module needs to be reset by
     *   the software. This bit needs to be checked at each occurrence
     *   of the film mode detection interrupt.
     *   Read only parameter. */
    UInt32 caf;
    /**< Detected combing artifacts.
     *   Read only parameter. */
    UInt32 fldMode;
    /**< Field mode used in MDT (not part of FMD register but it
     *   is needed for FMD SW. */
} Vps_DeiFmdStatusReg;

/**
 *  struct Vps_DeiRtConfig
 *  \brief Struture to configure runtime DEI parameters.
 */
typedef struct
{
    UInt32 resetDei;
    /**< Resets the DEI context. */
    UInt32 fldRepeat;
    /**< Field repeat flag. Application should set this flag to TRUE if
     *   it repeats the input field. This is needed to disable
     *   context buffer roatation to generate output as same as previous field
     *   without any field artifacts. */
} Vps_DeiRtConfig;

/**
 *  struct Vps_DeiCtxInfo
 *  \brief DEI context information containing the number of buffers and size of
 *  the buffers needed for deinterlacing operation.
 */
typedef struct
{
    UInt32 chNum;
    /**< Channel number from which to get the DEI context information.
     *   If only one channel is supported, then this should be set to 0. */
    UInt32 numFld;
    /**< Number of field buffers needed for deinterlacing operation.
     *   This is not applicable for platform TI814X. Please refer the
     *   user guide of TI814X, that came with this release. */
    UInt32 numMv;
    /**< Number of MV buffers needed for deinterlacing operation. */
    UInt32 numMvstm;
    /**< Number of MVSTM buffers needed for deinterlacing operation.
     *   This is not applicable for platform TI814X. Please refer the
     *   user guide for TI814X, that came with this release. */
    UInt32 fldBufSize;
    /**< Size of one field buffer in bytes.
     *
     *   In case application wants to allocate the context buffer based on the
     *   maximum input resolution it operates with, then below equation could
     *   be used for calculating the context buffer sizes,
     *
     *   Size = Align(width, 16) * field height * 2
     *   If compressor is enabled, then the size could be half of above value.
     *
     *   This is not applicable for platform TI814X. Please refer the
     *   user guide for TI814X, that came with this release. */
    UInt32 mvBufSize;
    /**< Size of one MV buffer in bytes.
     *
     *   In case application wants to allocate the context buffer based on the
     *   maximum input resolution it operates with, then below equation could
     *   be used for calculating the context buffer sizes,
     *
     *   Size = Align(width/2, 16) * field height */
    UInt32 mvstmBufSize;
    /**< Size of one MVSTM buffer in bytes.
     *
     *   In case application wants to allocate the context buffer based on the
     *   maximum input resolution it operates with, then below equation could
     *   be used for calculating the context buffer sizes,
     *
     *   Size = Align(width/2, 16) * field height
     *
     *   This is not applicable for platform TI814X. Please refer the
     *   user guide for TI814X, that came with this release. */
} Vps_DeiCtxInfo;

/**
 *  struct Vps_DeiCtxBuf
 *  \brief DEI context buffers needed for deinterlacing operation.
 */
typedef struct
{
    UInt32 chNum;
    /**< Channel number to which the DEI context buffers be given.
     *   If only one channel is supported, then this should be set to 0. */
    void  *fldBuf[VPS_DEI_MAX_CTX_FLD_BUF];
    /**< Array of DEI context field buffer pointers.
     *   This is not applicable for platform TI814X. Please refer the
     *   user guide for TI814X, that came with this release. */
    void  *mvBuf[VPS_DEI_MAX_CTX_MV_BUF];
    /**< Array of DEI context MV buffer pointers. */
    void  *mvstmBuf[VPS_DEI_MAX_CTX_MVSTM_BUF];
    /**< Array of DEI context MVSTM buffer pointers.
     *   This is not applicable for platform TI814X. Please refer the
     *   user guide for TI814X, that came with this release. */
} Vps_DeiCtxBuf;

/**
 *  struct Vps_DeiConfig
 *  \brief DEI configuration.
 */
typedef struct
{
    UInt32 bypass;
    /**< DEI should be bypassed or not.
     *   1. For interlaced input and interlaced output from DEI/VIP Scaler,
     *   the DEI could be operated in two modes.
     *      a. DEI in bypass mode and the respective scaler in non-interlacing
     *      mode (interlaced input DEI, interlaced output from Scaler).
     *      In this case,
     *      DEI bypass = TRUE
     *      Scaler bypass = TRUE/FALSE depending up on whether scaling is
     *      required or not.
     *      b. DEI in deinterlacing mode - converts interlaced input to
     *      progressive output to the scaler. Scaler in interlacing mode -
     *      converts the progressive input from DEI to interlaced output.
     *      In this case,
     *      DEI bypass = FALSE
     *      Scaler bypass = FALSE
     *   2. For progressive input and interlaced output, Scaler will be in
     *      interlacing mode.
     *      DEI bypass = TRUE
     *      Scaler bypass = FALSE
     *   3. For progressive input and progressive output,
     *      DEI bypass = TRUE
     *      Scaler bypass = TRUE/FALSE depending up on whether scaling is
     *      required or not.
     *   4. For interlaced input and progressive output,
     *      DEI bypass = FALSE
     *      Scaler bypass = TRUE/FALSE depending up on whether scaling is
     *      required or not.
     */
    UInt32 inpMode;
    /**< Interpolation mode. For valid values see #Vps_DeiEdiMode. */
    UInt32 tempInpEnable;
    /**< 3D processing (temporal interpolation). */
    UInt32 tempInpChromaEnable;
    /**< 3D processing for chroma. */
    UInt32 spatMaxBypass;
    /**< Bypass spatial maximum filtering. */
    UInt32 tempMaxBypass;
    /**< Bypass temporal maximum filtering. */
} Vps_DeiConfig;

/**
 *  struct Vps_DeiRdWrAdvCfg
 *  \brief Structure to read/write to advance DEI registers.
 */
typedef struct
{
    UInt32           chNum;
    /**< Channel number for which the configuration is to be set/get.
     *   Used only in M2M driver, for display and capture driver set
     *   this to 0. */
    UInt32           bypass;
    /**< DEI should be bypassed or not. */
    UInt32           width;
    /**< Width of the frame. */
    UInt32           height;
    /**< Height of the frame. */
    UInt32           scanFormat;
    /**< Scan format. For valid values see #Fvid2_ScanFormat. */
    UInt32           fieldFlush;
    /**< Flush internal pipe for current output. */

    Vps_DeiMdtConfig mdtCfg;
    /**< Motion detection configuration. */
    Vps_DeiEdiConfig ediCfg;
    /**< Edge directed interpolation configuration. */
    Vps_DeiFmdConfig fmdCfg;
    /**< Film mode detection configuration. */
} Vps_DeiRdWrAdvCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_DeiConfig structure init function.
 *
 *  \param deiCfg       [IN] Pointer to #Vps_DeiConfig structure.
 *
 */
static inline void VpsDeiConfig_init(Vps_DeiConfig *deiCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsDeiConfig_init(Vps_DeiConfig *deiCfg)
{
    if (NULL != deiCfg)
    {
        deiCfg->bypass              = (UInt32) TRUE;
        deiCfg->inpMode             = VPS_DEI_EDIMODE_LUMA_CHROMA;
        deiCfg->tempInpEnable       = (UInt32) TRUE;
        deiCfg->tempInpChromaEnable = (UInt32) TRUE;
        deiCfg->spatMaxBypass       = (UInt32) FALSE;
        deiCfg->tempMaxBypass       = (UInt32) FALSE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_DEI_H_ */

/* @} */
