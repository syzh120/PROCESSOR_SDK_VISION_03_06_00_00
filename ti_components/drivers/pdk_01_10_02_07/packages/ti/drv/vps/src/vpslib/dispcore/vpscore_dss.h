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
 *  \file vpscore_dss.h
 *
 *  \brief VPS display DSS core interface.
 *  This file defines the interface for the DSS display core.
 *
 */

#ifndef VPSCORE_DSS_H_
#define VPSCORE_DSS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/common/vps_evtMgr.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief IOCTL base address for the common IOCTLs listed below. */
#define VCORE_DSS_COMMON_IOCTL_BASE     (0x00000000U)
/** \brief IOCTL base address for the custom IOCTLs of each cores. */
#define VCORE_DSS_CUSTOM_IOCTL_BASE     (0x00000100U)

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
#define VCORE_DSS_SET_CSC_COEFF  (VCORE_DSS_COMMON_IOCTL_BASE + 0x01U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32        dispcIrqNumber;
    /**< DISPC IRQ number at CPU level INTC. */
    VpsHal_Handle vidHandle[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    VpsHal_Handle ovlHandle[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
} VpsCore_DssInitParams;

typedef struct
{
    UInt32 standard;
    /**< VENC Standard like NTSC, 1080p etc to which the display driver
     *   path is connected. For valid values see #FVID2_Standard. */
    UInt32 dispWidth;
    /**< Width of the display at the VENC in pixels to which the
     *   display driver path is connected. */
    UInt32 dispHeight;
    /**< Height of the display at the VENC in linesto which the
     *   display driver path is connected. */
    UInt32 vencId;
    /**< Venc ID to which this display instance is connected. */
} VpsCore_DssOpenRetParams;

/**
 *  \brief DSS parameters used in set/get DSS params.
 */
typedef struct
{
    Fvid2_Format            inFmt;
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
    Vps_DssDispcOvlyPipeConfig *ovlyPipeCfg;
    /**< Overlay config. Applicable only for M2M mode as DCTRL doesn't
     *   program these parameters */
    UInt32                      channelOut;
    /**< channelOut parameter. Applicable only for M2M mode as DCTRL doesn't
     *   program these parameters */
    UInt32                      channelOut2;
    /**< channelOut parameter. Applicable only for M2M mode as DCTRL doesn't
     *   program these parameters */
} VpsCore_DispDssParams;

typedef struct
{
    UInt32 src;
    /**< #Vps_DssDispcPipes */
    UInt32 isM2mMode;
    /**< TRUE - M2M mode - no DCTRL register done else display mode */
} VpsCore_DssOpenParams;

typedef struct
{
    UInt32 vidBufferUnderflow;
    /**<VID pipeline Buffer underflow count. */
}VpsCore_DssVidErrorStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsCore_dssInit
 *  \brief Initialize DSS Instance.
 *
 *  \param initParams       Valid handle returned by #TODO function.
 *
 *  \return                 success: Valid #VpsCore_Inst
 *                          failure: NULL
 */
VpsCore_Inst VpsCore_dssInit(const VpsCore_DssInitParams *initParams);

/**
 *  VpsCore_dssDeInit
 *  \brief Free DSS instance.
 *
 *  \param pDssHandle     Valid #VpsCore_Inst.
 *
 *  \return               success: Valid #VpsCore_Inst
 *                        failure: NULL
 */
Int32 VpsCore_dssDeInit(VpsCore_Inst pDssHandle);

/**
 *  VpsCore_dssGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dssGetCoreOps(void);

#ifdef __cplusplus
}
#endif

#endif /*VPSCORE_DSS_H_*/
