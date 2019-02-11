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
 *  \ingroup BSP_DRV_VPS_DISPLAY_API
 *  \defgroup BSP_DRV_VPS_DISPLAY_DSS_API VPS DSS Display API
 *
 *  This modules define APIs to display video data using DSS in VPS.
 *  @{
 */

/**
 *  \file vps_displayDss.h
 *
 *  \brief Video Display API specific to DSS.
 */

#ifndef VPS_DISPLAY_DSS_H_
#define VPS_DISPLAY_DSS_H_

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

/*
 *  Macros for different driver instance numbers to be passed as instance ID
 *  at the time of driver create.
 *  Note: These are read only macros. Don't modify the value of these macros.
 */

/**
 *  \name DSS Display Instance ID's
 *
 *  @{
 */

/** \brief Video Pipeline 1 display driver instance number. */
#define VPS_DISP_INST_DSS_VID1          (0U)

/** \brief Video Pipeline 2 display driver instance number. */
#define VPS_DISP_INST_DSS_VID2          (1U)

/** \brief Video Pipeline 3 display driver instance number.
 *         This instance is not available for Tda3xx platform. */
#define VPS_DISP_INST_DSS_VID3          (2U)

/** \brief Graphics Pipeline 1 display driver instance number. */
#define VPS_DISP_INST_DSS_GFX1          (3U)

/* @} */

/* DSS Display IOCTL's */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS_DISPLAY
 *  \defgroup BSP_DRV_IOCTL_VPS_DISPLAY_DSS DSS Display IOCTL's
 *  @{
 */

/**
 *  \brief Set DSS display params IOCTL.
 *
 *  This IOCTL can be used to set the Dss display params.
 *  Note: See respective counter comments for details.
 *
 *  \param cmdArgs       [IN] const Vps_DispDssParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */
#define IOCTL_VPS_DISP_SET_DSS_PARAMS   (VPS_DISP_DSS_IOCTL_BASE + 0x0001U)

/**
 *  \brief Get DSS display params IOCTL.
 *
 *  This IOCTL can be used to get the Dss display params.
 *  Note: See respective counter comments for details.
 *
 *  \param cmdArgs       [IN/OUT]  Vps_DispDssParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */
#define IOCTL_VPS_DISP_GET_DSS_PARAMS   (VPS_DISP_DSS_IOCTL_BASE + 0x0002U)

/**
 *  \brief Set DSS CSC Coefficients IOCTL.
 *
 *  This IOCTL can be used to set the CSC coefficients.
 *  Note: Default BT601 coefficients are set.
 *
 *  \param cmdArgs       [IN] const Vps_DssCscCoeff *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */

#define IOCTL_VPS_DISP_SET_CSC_COEFF    (VPS_DISP_DSS_IOCTL_BASE + 0x0003U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief DSS parameters used in set/get DSS params.
 */
typedef struct
{
    Fvid2_Format           inFmt;
    /**< Input FVID frame format. */
    UInt32                 tarWidth;
    /**< Horizontal Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                 tarHeight;
    /**< Verticle Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                 posX;
    /**< X position of the frame in the output Video Window . */
    UInt32                 posY;
    /**< Y position of the frame in the output Video Window . */
    UInt32                 memType;
    /**< Memory type. For valid values see #Vps_VpdmaMemoryType.
     *   Note: Tiler Memory is not supported as of now, user should set this
     *   to VPS_VPDMA_MT_NONTILEDMEM. */
    Vps_DssDispcVidConfig *vidCfg;
    /**< Video Configuration structure, applicable only for Video pipeline
     *   instances, if NULL default configuration will be used */
    Vps_DssDispcGfxConfig *gfxCfg;
    /**< Graphics Configuration structure, applicable only for Graphics pipeline
     *   instances, if NULL default configuration will be used */
} Vps_DispDssParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_DispDssParams structure init function.
 *
 *  \param dssPrms      [IN] Pointer to #Vps_DispDssParams structure.
 *
 */
static inline void VpsDispDssParams_init(Vps_DispDssParams *dssPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsDispDssParams_init(Vps_DispDssParams *dssPrms)
{
    UInt32 i;

    if (NULL != dssPrms)
    {
        Fvid2Format_init(&dssPrms->inFmt);
        dssPrms->inFmt.width  = 1920U;
        dssPrms->inFmt.height = 1080U;
        for (i = 0U; i < FVID2_MAX_PLANES; i++)
        {
            dssPrms->inFmt.pitch[i] = dssPrms->inFmt.width * 2U;
        }

        dssPrms->tarWidth  = dssPrms->inFmt.width;
        dssPrms->tarHeight = dssPrms->inFmt.height;
        dssPrms->posX      = 0U;
        dssPrms->posY      = 0U;
        dssPrms->memType   = VPS_VPDMA_MT_NONTILEDMEM;
        dssPrms->vidCfg    = NULL;
        dssPrms->gfxCfg    = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_DISPLAY_DSS_H_ */

/* @} */
