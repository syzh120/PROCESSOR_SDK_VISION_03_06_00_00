/*
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
 *  \file bspdrv_sii9022aPriv.h
 *
 *  \brief SII9022a encoder internal header file.
 */

#ifndef BSP_SII9022A_PRIV_H_
#define BSP_SII9022A_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_videoEncoder.h>
#include <ti/drv/vps/include/devices/bsp_sii9022a.h>
#include <sii9022a/bspdrv_sii9022a.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_SII9022A_OBJ_STATE_UNUSED       (UInt32) (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_SII9022A_OBJ_STATE_IDLE         (UInt32) (1U)
/** \brief Device state - Not initialized. */
#define BSP_SII9022A_NOT_INITED             (UInt32) (0U)
/** \brief Device state - initialized successfully. */
#define BSP_SII9022A_INITED                 (UInt32) (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief SII9022A driver handle object.
 */
typedef struct
{
    UInt32                 state;
    /**< Handle state - used or free. */
    UInt32                 handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle      lock;
    /**< Driver lock. */
    Bsp_VidEncCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_Sii9022aParams     prms;
    /**< SII9022A params */
    Bsp_Sii9022aHdmiChipId hdmiChipId;
    /**< HDMI Chip id. */
    UInt32                 hpd;
    /**< HDMI Hot plug detect. */
    UInt8                  syncCfgReg;
    /**< Sync Configuration Register. */
    UInt8                  syncPolarityReg;
    /**< Sync polarity Register. */
    UInt32                 isRgbOutput;
    /**< Is output RGB. */
    UInt32                 inBusCfg;
    /**< Input bus config. */
} Bsp_Sii9022aHandleObj;

/**
 *  \brief SII9022A Global driver object.
 */
typedef struct
{
    UInt32                deviceState;
    /**< Driver state. */
    BspOsal_SemHandle     lock;
    /**< Global driver lock. */
    Bsp_Sii9022aHandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Sii9022aCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSPDRV_SII9022A_PRIV_H_ */

