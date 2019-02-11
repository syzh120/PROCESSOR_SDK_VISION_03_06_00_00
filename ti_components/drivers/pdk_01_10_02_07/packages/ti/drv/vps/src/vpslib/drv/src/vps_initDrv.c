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
 *  \file vps_initDrv.c
 *
 *  \brief File containing the VPS capture driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vip/vps_vipDrv.h>
#endif

#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/dss/vps_dssDrv.h>
#include <ti/drv/vps/include/dss/vps_dctrlDrv.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#ifdef VPS_DSS_BUILD
extern UInt32 gDssDrvInit;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef VPS_VIP_BUILD
extern const VpsDrv_VipPlatformData *VpsDrv_getVipPlatformData(void);
#endif

#ifdef VPS_DSS_BUILD
extern const VpsDrv_DssPlatformData *VpsDrv_getDssPlatformData(void);
#endif

#ifdef VPS_VIP_BUILD
extern Int32 VpsDrv_captInit(UInt32                       numInst,
                             const VpsDrv_CaptInitParams *initPrms);
extern Int32 VpsDrv_captDeInit(void);
#endif

#ifdef VPS_DSS_BUILD
extern Int32 VpsDrv_dssInit(UInt32                       numInst,
                            const VpsDrv_DispInitParams *initPrms);
extern Int32 VpsDrv_dssDeInit(void);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Vps_init
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param none
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_init(Ptr args)
{
#ifdef VPS_VIP_BUILD
    VpsDrv_CaptInitParams         captDrvInitPrms[VPS_CAPT_VIP_INST_MAX];
    const VpsDrv_VipPlatformData *drvVipPlatData;
#endif

#ifdef VPS_DSS_BUILD
    VpsDrv_DispInitParams         dssDrvInitPrms[VPS_DISP_INST_MAX];
    VpsDrv_DctrlInitParams        dctrlDrvInitPrms;
    const VpsDrv_DssPlatformData *drvDssPlatData;
#endif

#if defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD)
    UInt32 instCnt;
#endif

    Int32 retVal;

#if defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD)
    const VpsLib_PlatformData    *libPlatData;
#endif

    retVal = VpsLib_init(NULL);

#ifdef VPS_DSS_BUILD
    gDssDrvInit = 1U;
    dctrlDrvInitPrms.coreInstObj = VpsLib_getDctrlCoreInstObj();
    dctrlDrvInitPrms.coreOps     = VpsCore_dctrlGetCoreOps();
    VpsDrv_dctrlInit(&dctrlDrvInitPrms);
#endif

    if (BSP_SOK == retVal)
    {
#if defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD)
        /* Get Platform data */
        libPlatData = VpsLib_getPlatformData();
#endif

#ifdef VPS_VIP_BUILD

        drvVipPlatData = VpsDrv_getVipPlatformData();

        for (instCnt = 0U; instCnt < libPlatData->hal->numVipPort; instCnt++)
        {
            captDrvInitPrms[instCnt].drvInstId =
                drvVipPlatData->captDrvInitPrms[instCnt].drvInstId;
            captDrvInitPrms[instCnt].coreInstObj =
                VpsLib_getVipCoreInstObj(
                    Vps_captGetVipId(captDrvInitPrms[instCnt].drvInstId));

            captDrvInitPrms[instCnt].coreOps = VpsCore_vipGetCoreOps();
        }

        retVal =
            VpsDrv_captInit(libPlatData->hal->numVipPort, &captDrvInitPrms[0U]);

#endif

#ifdef VPS_DSS_BUILD

        drvDssPlatData = VpsDrv_getDssPlatformData();
        for (instCnt = 0U; instCnt < libPlatData->hal->numVidPipe; instCnt++)
        {
            dssDrvInitPrms[instCnt].drvInstId =
                drvDssPlatData->DispDrvInitPrms[instCnt].drvInstId;
            dssDrvInitPrms[instCnt].coreInstObj = VpsLib_getDssCoreInstObj();
            dssDrvInitPrms[instCnt].coreOps     = VpsCore_dssGetCoreOps();
        }

        /* Call display init only if required */
        if (libPlatData->hal->numVidPipe > 0U)
        {
            retVal = VpsDrv_dssInit(libPlatData->hal->numVidPipe,
                                    &dssDrvInitPrms[0U]);
        }
#endif
    }

    return retVal;
}

/**
 *  Vps_deInit
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param none
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */

Int32 Vps_deInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

#ifdef VPS_VIP_BUILD
    retVal = VpsDrv_captDeInit();
#endif

#ifdef VPS_DSS_BUILD
    retVal     += VpsDrv_dssDeInit();
    retVal     += VpsDrv_dctrlDeInit();
    gDssDrvInit = 0;
#endif
    retVal += VpsLib_deInit(NULL);

    return retVal;
}

