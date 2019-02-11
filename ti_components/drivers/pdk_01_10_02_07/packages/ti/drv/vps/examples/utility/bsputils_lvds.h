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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_LVDS_API Application helper APIs for LVDS operations
 *  @{
 */

/**
 *  \file bsputils_lvds.h
 *
 *  \brief Header file to use application level LVDS helper functions.
 */

#ifndef BSPUTILS_LVDS_H_
#define BSPUTILS_LVDS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif  /* #ifdef VPS_VIP_BUILD */
#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#endif  /* #ifdef VPS_VPE_BUILD */
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_display.h>
#endif  /* #ifdef VPS_DSS_BUILD */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  BspUtils_appInitSerDeSer
 *
 *  \brief BSP application utils function to setup MULDES board for LVDS
 *  Support.
 */
Int32 BspUtils_appInitSerDeSer(void);

/**
 *  BspUtils_appDeInitSerDeSer
 *
 *  \brief BSP application utils function to undo stuff done in init.
 *  1. Deletion of semaphore created.
 */
Int32 BspUtils_appDeInitSerDeSer(void);

/**
 *  BspUtils_appConfSerDeSer
 *
 *  \brief BSP application utils function to Configure a particular instance of
 *  De-Serializer and serializer for LVDS Support.
 *
 *  \param devDrvId         [IN]    Device Driver ID.
 *  \param devInstId        [IN]    Instance ID of the Device.
 */
Int32 BspUtils_appConfSerDeSer(UInt32 devDrvId, UInt32 devInstId);

/**
 *  BspUtils_appDeConfSerDeSer
 *
 *  \brief BSP application utils function to De-Configure a particular instance
 *           of De-Serializer and serializer for LVDS Support.
 *
 *  \param devDrvId         [IN]    Device Driver ID.
 *  \param devInstId        [IN]    Instance ID of the Device.
 */
Int32 BspUtils_appDeConfSerDeSer(UInt32 devDrvId, UInt32 devInstId);

/**
 *  BspUtils_appDumpDeSerReg
 *
 *  \brief BSP application utils function to print all the registers of
 *  deserializer.
 *
 *  \param devDrvId         [IN]   Device Driver ID.
 *  \param devInstId        [IN]   Instance ID of the Device.
 */
Int32 BspUtils_appDumpDeSerReg(UInt32 devDrvId, UInt32 devInstId);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_LVDS_H_ */

/* @} */
