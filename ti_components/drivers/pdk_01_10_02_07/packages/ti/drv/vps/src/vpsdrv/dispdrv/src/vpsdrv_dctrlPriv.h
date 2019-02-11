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
 *  \file vpsdrv_displayPriv.h
 *
 *  \brief Display driver private header file.
 *
 */

#ifndef VPSDRV_DCTRL_PRIV_H_
#define VPSDRV_DCTRL_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <dispdrv/vpsdrv_display.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DctrlInstObj_t VpsDrv_DctrlInstObj;

/**
 *  struct VpsDrv_DispStates
 *  \brief Different states of the driver.
 */
typedef struct
{
    UInt32 isInit;
    /**< Flag to indicate intialization is done or not for an instance. */
    UInt32 isOpened;
    /**< Flag to indicate whether a instance is opened or not. */
    UInt32 isStarted;
    /**< Flag to indicate whether the display has started or not. */
} VpsDrv_DctrlStates;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Fvid2_DrvOps         fvidDrvOps;
    /**< FVID2 driver ops. */
    UInt32               isRegistered;
    /**< FVID2 registeration complete flag. */
    VpsDrv_DctrlInstObj *instObj;
    /**< Display instance objects pointer. */
} VpsDrv_DctrlCommonObj;

/**
 *  \brief Per instance information.
 */
struct VpsDrv_DctrlInstObj_t
{
    UInt32               drvInstId;
    /**< Instance ID. */
    VpsCore_Inst         coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops   *coreOps;
    /**< Core function pointers. */

    VpsCore_Property     coreProperty;
    /**< Core properties. */

    Vps_DispCreateParams createPrms;
    /**< Create parameters. */

    Vps_DispStatus       stat;
    /**< Instance statistics object. */

    VpsDrv_DctrlStates   state;
    /**< Instance state. */

    BspOsal_SemHandle    lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSDRV_DCTRL_PRIV_H_ */

