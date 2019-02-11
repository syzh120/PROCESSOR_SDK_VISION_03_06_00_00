/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file vpsdrv_init.c
 *
 *  \brief File containing the VPS driver init and deinit functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/csl/soc.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_control.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <vpsdrv_control.h>

#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#endif /* VPS_VIP_BUILD */
#include <captdrv/vpsdrv_capture.h>
#include <ti/drv/vps/include/vps_capture.h>
#endif /* VPS_CAPT_BUILD */

#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_vpe.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_vpeWb.h>
#include <vpedrv/vps_mlm.h>
#include <vpedrv/vpsdrv_m2mVpe.h>
#endif /* VPS_VPE_BUILD */

#ifdef VPS_DISP_BUILD
#include <ti/drv/vps/include/vps_display.h>
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dssWb.h>
#endif /* VPS_DSS_BUILD */
#include <dispdrv/vpsdrv_display.h>
#include <dispdrv/vpsdrv_dctrl.h>
#include <ti/drv/vps/include/dss/vps_m2mDss.h>
#include <m2mdrv_dss/vpsdrv_m2mDss.h>
#endif /* VPS_DISP_BUILD */

#ifdef VPS_CAL_BUILD
#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <captdrv/vpsdrv_capture.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_capture.h>
#endif /* VPS_CAL_BUILD */

#ifdef VPS_SIMCOP_BUILD
#include <ti/drv/vps/src/vpslib/isscore/vpscore_simcop.h>
#endif /* VPS_SIMCOP_BUILD */

#ifdef VPS_M2M_BUILD
#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <m2mdrv/vpsdrv_m2mintf.h>
#ifdef VPS_ISS_BUILD
#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_calm2m.h>
#endif /* VPS_ISS_BUILD */
#ifdef VPS_SIMCOP_BUILD
#include <ti/drv/vps/src/vpslib/isscore/vpscore_simcop.h>
#endif /* VPS_SIMCOP_BUILD */
#endif /* VPS_M2M_BUILD */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Platform specific data containing base address information of
 *  various modules.
 */
typedef struct
{
#ifdef VPS_CAPT_BUILD
    VpsDrv_CaptInitParams     captDrvInitPrms[VPS_CFG_CAPT_NUM_INST_OBJS];
    /**< Capture driver init parameters. */
#endif

#ifdef VPS_DISP_BUILD
    VpsDrv_DispInitParams     dispDrvInitPrms[VPS_DISP_INST_MAX];
    /**< Display driver init parameters. */
    VpsMdrv_DssInitParams     m2mDssDrvInitPrms[VPS_M2M_DSS_INST_MAX];
    /**< M2M DSS driver init parameters. */
#endif

#ifdef VPS_CAL_BUILD
    VpsDrv_CaptInitParams     issCaptDrvInitPrms[VPS_ISS_CAPT_INST_MAX_ID];
#endif /* VPS_CAL_BUILD */

#ifdef VPS_M2M_BUILD
    VpsMdrv_M2mIntfInitParams m2mIntfDrvInitPrms[VPS_M2M_INTF_INST_MAX];
#endif

    UInt32                    reserved;
    /**< Needed in case both VIP and DSS are not defined!! */
} VpsDrv_PlatformData;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
void vpsInitTda2xxPlatData(void);
#elif defined (SOC_TDA3XX)
void vpsInitTda3xxPlatData(void);
#elif defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
void vpsInitTi814xPlatData(void);
#elif defined (OMAP5430_BUILD)
void vpsInitOmap5PlatData(void);
#endif

const VpsDrv_PlatformData *VpsDrv_getPlatformData(void);

#ifdef VPS_CAPT_BUILD
static Int32 Vps_captInit(void);
static Int32 Vps_captDeInit(void);
#endif
#ifdef VPS_VPE_BUILD
static Int32 Vps_vpeInit(void);
static Int32 Vps_vpeDeInit(void);
#endif
#ifdef VPS_DISP_BUILD
static Int32 Vps_dispInit(void);
static Int32 Vps_dispDeInit(void);
#endif
#ifdef VPS_M2M_BUILD
static Int32 Vps_m2mInit(void);
static Int32 Vps_m2mDeInit(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
static VpsDrv_PlatformData gVpsDrvPlatDataTda2xx;
#endif

#if defined (SOC_TDA3XX)
static VpsDrv_PlatformData gVpsDrvPlatDataTda3xx;
#endif

#if defined (OMAP5430_BUILD)
static VpsDrv_PlatformData gVpsDrvPlatDataOmap5x;
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
static VpsDrv_PlatformData gVpsDrvPlatDataTI814x;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS init function.
 */
Int32 Vps_init(const Vps_InitParams *initPrms)
{
    Int32             retVal = BSP_SOK;
    Vps_InitParams    localInitPrms;
    VpsLib_InitParams vpsLibInitPrms;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    vpsInitTda2xxPlatData();
#elif defined (SOC_TDA3XX)
    vpsInitTda3xxPlatData();
#elif defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    vpsInitTi814xPlatData();
#elif defined (OMAP5430_BUILD)
    vpsInitOmap5PlatData();
#else
    GT_0trace(VpsDrvTrace, GT_ERR, "VPS: Unsupported SOC!!\r\n");
#endif

    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        VpsInitParams_init(&localInitPrms);
    }

    vpsLibInitPrms.isAddrTransReq           = initPrms->isAddrTransReq;
    vpsLibInitPrms.virtBaseAddr             = initPrms->virtBaseAddr;
    vpsLibInitPrms.physBaseAddr             = initPrms->physBaseAddr;
    vpsLibInitPrms.isCacheOpsReq            = initPrms->isCacheOpsReq;
    vpsLibInitPrms.isCacheFlushReq          = initPrms->isCacheFlushReq;
    vpsLibInitPrms.irqParams.vipIrqNum[0U]  = initPrms->irqParams.vipIrqNum[0U];
    vpsLibInitPrms.irqParams.vipIrqNum[1U]  = initPrms->irqParams.vipIrqNum[1U];
    vpsLibInitPrms.irqParams.vipIrqNum[2U]  = initPrms->irqParams.vipIrqNum[2U];
    vpsLibInitPrms.irqParams.vpeIrqNum      = initPrms->irqParams.vpeIrqNum;
    vpsLibInitPrms.irqParams.dssIrqNum      = initPrms->irqParams.dssIrqNum;
    vpsLibInitPrms.irqParams.calIrqNum      = initPrms->irqParams.calIrqNum;
    vpsLibInitPrms.irqParams.issIrqNum      = initPrms->irqParams.issIrqNum;
    retVal = VpsLib_init(&vpsLibInitPrms);
    if (BSP_SOK == retVal)
    {
        retVal += VpsDrv_ctrlInit();
#ifdef VPS_CAPT_BUILD
        retVal += Vps_captInit();
#endif
#ifdef VPS_VPE_BUILD
        retVal += Vps_vpeInit();
#endif
#ifdef VPS_DISP_BUILD
        retVal += Vps_dispInit();
#endif
#ifdef VPS_M2M_BUILD
        retVal += Vps_m2mInit();
#endif
    }

    return (retVal);
}

/**
 *  \brief VPS deinit function.
 */
Int32 Vps_deInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

#ifdef VPS_M2M_BUILD
    retVal += Vps_m2mDeInit();
#endif

#ifdef VPS_DISP_BUILD
    retVal += Vps_dispDeInit();
#endif
#ifdef VPS_VPE_BUILD
    retVal += Vps_vpeDeInit();
#endif
#ifdef VPS_CAPT_BUILD
    retVal += Vps_captDeInit();
#endif

    retVal += VpsDrv_ctrlDeInit();
    retVal += VpsLib_deInit(NULL);

    return (retVal);
}

void VpsInitParams_init(Vps_InitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isAddrTransReq  = (UInt32) FALSE;
        initPrms->virtBaseAddr    = 0U;
        initPrms->physBaseAddr    = 0U;
        initPrms->isCacheOpsReq   = (UInt32) FALSE;
        initPrms->isCacheFlushReq = (UInt32) FALSE;
        BspUtils_memset(&initPrms->irqParams, 0, sizeof (Vps_IrqParams));
    #if defined (VPS_VIP1_BUILD)
        initPrms->irqParams.vipIrqNum[0U] = CSL_INTC_EVENTID_VIP1INT0;
    #endif
    #if defined (VPS_VIP2_BUILD)
        initPrms->irqParams.vipIrqNum[1U] = CSL_INTC_EVENTID_VIP2INT0;
    #endif
    #if defined (VPS_VIP3_BUILD)
        initPrms->irqParams.vipIrqNum[2U] = CSL_INTC_EVENTID_VIP3INT0;
    #endif
    #if defined (VPS_VPE_BUILD)
        initPrms->irqParams.vpeIrqNum    = CSL_INTC_EVENTID_VPEINT0;
    #endif
    #if defined (VPS_DSS_BUILD)
        initPrms->irqParams.dssIrqNum    = CSL_INTC_EVENTID_DSS_DISPC;
    #endif
    #if defined (VPS_CAL_BUILD)
        initPrms->irqParams.calIrqNum    = CSL_CAL_IRQ_NUM;
    #endif
    #if defined (VPS_ISS_BUILD)
        initPrms->irqParams.issIrqNum    = CSL_ISS_IRQ0_NUM;
    #endif
    }
    return;
}

const VpsDrv_PlatformData *VpsDrv_getPlatformData(void)
{
    VpsDrv_PlatformData *platData = NULL;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    platData = &gVpsDrvPlatDataTda2xx;
#elif defined (SOC_TDA3XX)
    platData = &gVpsDrvPlatDataTda3xx;
#elif defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    platData = &gVpsDrvPlatDataTI814x;
#elif defined (OMAP5430_BUILD)
    platData = &gVpsDrvPlatDataOmap5x;
#else
    GT_0trace(VpsDrvTrace, GT_ERR, "VPS: Unsupported SOC!!\r\n");
#endif
    return (platData);
}

#ifdef VPS_CAPT_BUILD
static Int32 Vps_captInit(void)
{
    Int32  retVal  = BSP_SOK;
    UInt32 instCnt = 0, numInst = 0;

#ifdef VPS_VIP_BUILD
    UInt32 numVipPort;
#endif
#ifdef VPS_DSS_BUILD
    UInt32 numWbPipe;
#endif

    UInt32 captInstCnt = 0U;
    const VpsLib_PlatformData *libPlatData;
    const VpsDrv_PlatformData *drvPlatData;
#ifdef VPS_CAL_BUILD
    VpsDrv_CaptInitParams      captDrvInitPrms[VPS_CFG_CAPT_NUM_INST_OBJS +
                                               VPS_ISS_CAPT_INST_MAX_ID];
#else
    VpsDrv_CaptInitParams      captDrvInitPrms[VPS_CFG_CAPT_NUM_INST_OBJS];
#endif /* VPS_CAL_BUILD */

    /* Get Platform data */
    libPlatData = VpsLib_getPlatformData();

#ifdef VPS_VIP_BUILD
    numVipPort = libPlatData->hal->numVipPort;
    numInst   += numVipPort;
    GT_assert(VpsDrvTrace,
              (numVipPort <= VPS_CFG_CAPT_NUM_INST_OBJS));
#endif

#ifdef VPS_DSS_BUILD
    numWbPipe = libPlatData->hal->numWbPipe;
    numInst  += numWbPipe;
    GT_assert(VpsDrvTrace,
              (numWbPipe <= VPS_DISP_INST_MAX));
#endif

#ifdef VPS_CAL_BUILD
    numInst += VPS_ISS_CAPT_INST_MAX_ID;
    GT_assert(VpsDrvTrace,
              (numInst <= (VPS_CFG_CAPT_NUM_INST_OBJS + VPS_ISS_CAPT_INST_MAX_ID)));
#endif /* VPS_CAL_BUILD */

    GT_assert(VpsDrvTrace, (NULL != libPlatData));

    drvPlatData = VpsDrv_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != drvPlatData));

#ifdef VPS_VIP_BUILD
    for (instCnt = 0U; instCnt < numVipPort; instCnt++)
    {
        captDrvInitPrms[captInstCnt].drvInstId =
            drvPlatData->captDrvInitPrms[instCnt].drvInstId;
        captDrvInitPrms[captInstCnt].coreInstObj =
            VpsLib_getVipCoreInstObj(
                Vps_captGetVipId(captDrvInitPrms[instCnt].drvInstId));

        GT_assert(VpsDrvTrace,
                  (NULL != captDrvInitPrms[captInstCnt].coreInstObj));

        captDrvInitPrms[captInstCnt].coreOps = VpsCore_vipGetCoreOps();
        captInstCnt++;
    }
#endif

#ifdef VPS_DSS_BUILD
    for (instCnt = 0U; instCnt < numWbPipe; instCnt++)
    {
        captDrvInitPrms[captInstCnt].drvInstId =
            VPS_CAPT_INST_DSS_WB_BASE + instCnt;
        captDrvInitPrms[captInstCnt].coreInstObj =
            VpsLib_getDssWbCoreInstObj();
        GT_assert(VpsDrvTrace,
                  (NULL != captDrvInitPrms[captInstCnt].coreInstObj));

        captDrvInitPrms[captInstCnt].coreOps = VpsCore_dssWbGetCoreOps();
        captInstCnt++;
    }
#endif

#if defined (VPS_CAL_BUILD)
    {
        UInt32 coreInst = 0;
        for (instCnt = 0U; instCnt < VPS_ISS_CAPT_INST_MAX_ID; instCnt++)
        {
            captDrvInitPrms[captInstCnt].drvInstId = VPS_CAPT_INST_ISS_BASE +
                                                     drvPlatData->
                                                     issCaptDrvInitPrms[instCnt
                                                     ].drvInstId;
            /* Get core instance objects for a given instance */
            captDrvInitPrms[captInstCnt].coreInstObj =
                VpsCore_issCaptGetCoreInstObj((vpsissCaptInstId_t) coreInst);

            GT_assert(VpsDrvTrace,
                      (NULL != captDrvInitPrms[captInstCnt].coreInstObj));

            captDrvInitPrms[captInstCnt].coreOps = VpsCore_issCaptGetCoreOps();
            captInstCnt++;
            coreInst++;
        }
    }
#endif /* VPS_CAL_BUILD */

    /* Call Capture init only if required */
    if (captInstCnt > 0U)
    {
        retVal =
            VpsDrv_captInit(captInstCnt, &captDrvInitPrms[0U]);
    }

    return (retVal);
}

static Int32 Vps_captDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal = VpsDrv_captDeInit();

    return (retVal);
}

#endif /* VPS_CAPT_BUILD */

#ifdef VPS_M2M_BUILD
static Int32 Vps_m2mInit(void)
{
    Int32  retVal  = BSP_SOK;
    UInt32 instCnt = 0U;
    VpsMdrv_M2mIntfInitParams m2mDrvInitPrms[VPS_M2M_INTF_INST_MAX];

#ifdef VPS_ISS_BUILD
    m2mDrvInitPrms[instCnt].drvInstId          = VPS_M2M_ISS_INST_CAL_ISP;
    m2mDrvInitPrms[instCnt].isMultiChSupported = FALSE;
    m2mDrvInitPrms[instCnt].numCores           = 1U;
    m2mDrvInitPrms[instCnt].coreInstId[0U]     =
        VpsCore_issM2mGetCoreInstObj(VPSCORE_ISS_M2M_ISP_INST_0);
    m2mDrvInitPrms[instCnt].coreOps[0U] = VpsCore_issM2mGetCoreOps();
    instCnt++;
#endif

#ifdef VPS_SIMCOP_BUILD
    m2mDrvInitPrms[instCnt].drvInstId          = VPS_M2M_ISS_INST_SIMCOP;
    m2mDrvInitPrms[instCnt].isMultiChSupported = FALSE;
    m2mDrvInitPrms[instCnt].numCores           = 1U;
    m2mDrvInitPrms[instCnt].coreInstId[0U]     =
        (VpsCore_Inst *) VPSCORE_ISS_SIMCOP_INST_0;
    m2mDrvInitPrms[instCnt].coreOps[0U] = VpsCore_simcopGetCoreOps();

    instCnt++;
#endif

#ifdef VPS_ISS_CALM2M_BUILD
    m2mDrvInitPrms[instCnt].drvInstId          = VPS_M2M_ISS_INST_CALM2M;
    m2mDrvInitPrms[instCnt].isMultiChSupported = FALSE;
    m2mDrvInitPrms[instCnt].numCores           = 1U;
    m2mDrvInitPrms[instCnt].coreInstId[0U]     =
        (VpsCore_Inst *) VPSCORE_ISS_CALM2M_INST_0;
    m2mDrvInitPrms[instCnt].coreOps[0U] = VpsCore_calm2mGetCoreOps();

    instCnt++;
#endif

    if (0 < instCnt)
    {
        retVal = VpsMdrv_intfInit(instCnt, &m2mDrvInitPrms[0U]);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

static Int32 Vps_m2mDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal = VpsMdrv_intfDeInit();

    return (retVal);
}

#endif /* VPS_M2M_BUILD */

#ifdef VPS_VPE_BUILD
static Int32 Vps_vpeInit(void)
{
    Int32                 retVal = BSP_SOK;
    VpsHal_Handle         vpdmaHandle;
    Mlm_InitParams        mlmInitPrms;
    VpsMdrv_VpeInitParams vpeDrvInitPrms;
    UInt32                numInst;

    /* MLM Init */
    vpdmaHandle = VpsLib_getVpdmaHalHandle(VPSHAL_VPE1_VPDMA);
    if (NULL == vpdmaHandle)
    {
        vpdmaHandle = VpsLib_getVpdmaHalHandle(VPSHAL_VPDMA_GENERIC);
        GT_assert(VpsDrvTrace, (NULL != vpdmaHandle));
        mlmInitPrms.vpdmaHandle = vpdmaHandle;
        mlmInitPrms.vemInstId   = VEM_INST_ID_GENERIC;
        mlmInitPrms.vrmInstId   = VRM_INST_ID_GENERIC;
    }
    else
    {
        mlmInitPrms.vpdmaHandle = vpdmaHandle;
        mlmInitPrms.vemInstId   = VEM_INST_ID_VPE1;
        mlmInitPrms.vrmInstId   = VRM_INST_ID_VPE1;
    }
    retVal = Mlm_init(&mlmInitPrms);
    if (retVal != BSP_SOK)
    {
        GT_0trace(VpsDrvTrace, GT_ERR, "VPS: MLM init failed\r\n");
    }

    /* M2M VPE driver Init */
    if (BSP_SOK == retVal)
    {
        vpeDrvInitPrms.drvInstId = VPS_M2M_INST_VPE1;
        vpeDrvInitPrms.coreInstId[VPSMDRV_VPE_VPE_CORE_IDX] =
            VCORE_VPE_INST_PRI;
        vpeDrvInitPrms.coreInstId[VPSMDRV_VPE_VWB_CORE_IDX] =
            VCORE_VWB_INST_WB0;
        vpeDrvInitPrms.coreOps[VPSMDRV_VPE_VPE_CORE_IDX] =
            Vcore_vpeGetCoreOps();
        vpeDrvInitPrms.coreOps[VPSMDRV_VPE_VWB_CORE_IDX] =
            Vcore_vwbGetCoreOps();
        numInst = 1U;
        retVal  = VpsMdrv_vpeInit(numInst, &vpeDrvInitPrms);
        if (retVal != BSP_SOK)
        {
            GT_0trace(VpsDrvTrace, GT_ERR, "VPS: M2M VPE init failed\r\n");
        }
    }

    return (retVal);
}

static Int32 Vps_vpeDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal += VpsMdrv_vpeDeInit();
    retVal += Mlm_deInit();

    return (retVal);
}

#endif

#ifdef VPS_DISP_BUILD
static Int32 Vps_dispInit(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    const VpsLib_PlatformData *libPlatData;
    const VpsDrv_PlatformData *drvPlatData;
    VpsDrv_DispInitParams      dispDrvInitPrms[VPS_DISP_INST_MAX];
    VpsDrv_DctrlInitParams     dctrlDrvInitPrms;
#ifdef VPS_DSS_BUILD
    VpsMdrv_DssInitParams      m2mDssDrvInitPrms[VPS_M2M_DSS_INST_MAX];
#endif

    /* Get Platform data */
    libPlatData = VpsLib_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != libPlatData));
    drvPlatData = VpsDrv_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != drvPlatData));

    dctrlDrvInitPrms.coreInstObj = VpsLib_getDctrlCoreInstObj();
    dctrlDrvInitPrms.coreOps     = VpsCore_dctrlGetCoreOps();

    VpsDrv_dctrlInit(&dctrlDrvInitPrms);

#ifdef VPS_DSS_BUILD
    GT_assert(VpsDrvTrace,
              ((libPlatData->hal->numVidPipe) <= VPS_DISP_INST_MAX));
    for (instCnt = 0U; instCnt < libPlatData->hal->numVidPipe; instCnt++)
    {
        dispDrvInitPrms[instCnt].drvInstId =
            drvPlatData->dispDrvInitPrms[instCnt].drvInstId;
        dispDrvInitPrms[instCnt].coreInstObj = VpsLib_getDssCoreInstObj();
        GT_assert(VpsDrvTrace, (NULL != dispDrvInitPrms[instCnt].coreInstObj));
        dispDrvInitPrms[instCnt].coreOps = VpsCore_dssGetCoreOps();
    }
#endif

    /* Call display init only if required */
    if (libPlatData->hal->numVidPipe > 0U)
    {
        retVal = VpsDrv_dispInit(libPlatData->hal->numVidPipe,
                                 &dispDrvInitPrms[0U]);
    }

#ifdef VPS_DSS_BUILD
    if (BSP_SOK == retVal)
    {
        m2mDssDrvInitPrms[0U].drvInstId         =
            drvPlatData->m2mDssDrvInitPrms[0U].drvInstId;
        m2mDssDrvInitPrms[0U].inCoreInstObj     = VpsLib_getDssCoreInstObj();
        m2mDssDrvInitPrms[0U].inCoreOps         = VpsCore_dssGetCoreOps();
        m2mDssDrvInitPrms[0U].outCoreInstObj    = VpsLib_getDssWbCoreInstObj();
        m2mDssDrvInitPrms[0U].outCoreOps        = VpsCore_dssWbGetCoreOps();
        retVal = VpsMdrv_dssInit(VPS_M2M_DSS_INST_MAX, &m2mDssDrvInitPrms[0U]);
    }
#endif

    return (retVal);
}

static Int32 Vps_dispDeInit(void)
{
    Int32 retVal = BSP_SOK;
    const VpsLib_PlatformData *platData;

    /* Get Platform data */
    platData = VpsLib_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != platData));

#ifdef VPS_DSS_BUILD
    retVal += VpsMdrv_dssDeInit();
#endif

    /* Call display deinit only if required */
    if (platData->hal->numVidPipe > 0U)
    {
        retVal += VpsDrv_dispDeInit();
    }

    VpsDrv_dctrlDeInit();

    return (retVal);
}

#endif

/* ========================================================================== */
/*                              Local Functions                               */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
void vpsInitTda2xxPlatData(void)
{
#if (defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD) || defined (VPS_CAL_BUILD))
    UInt32 idx = 0;
#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#if defined (VPS_VIP1_BUILD)
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif  /* #if defined (VPS_VIP1_BUILD) */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
#if defined (VPS_VIP2_BUILD)
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;
#endif  /* #if defined (VPS_VIP2_BUILD) */
#if defined (VPS_VIP3_BUILD)
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* #if defined (VPS_VIP3_BUILD) */
#endif /* #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) */
#endif /* VPS_VIP_BUILD */

#ifdef VPS_DSS_BUILD

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_INST_DSS_WB1;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
    idx++;
#endif /* VPS_DSS_BUILD */

#ifdef VPS_CAL_BUILD
    idx = 0U;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_ID;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    /* Right now, we support only 1 instance of the driver. These are
        required when we support 2nd Phy? */
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_ID;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_ID;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.issCaptDrvInitPrms[idx].coreOps     = NULL;

    GT_assert(VpsDrvTrace, (VPS_ISS_CAPT_INST_MAX_ID >= idx));
#endif /* VPS_CAL_BUILD */

#endif /* VPS_CAPT_BUILD */

#ifdef VPS_DSS_BUILD
    /* Display driver */
    idx = 0;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID1;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID2;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID3;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_GFX1;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));

    /* DSS M2M driver */
    gVpsDrvPlatDataTda2xx.m2mDssDrvInitPrms[0U].drvInstId       =
        VPS_M2M_DSS_INST_WB1;
    gVpsDrvPlatDataTda2xx.m2mDssDrvInitPrms[0U].inCoreInstObj   = NULL;
    gVpsDrvPlatDataTda2xx.m2mDssDrvInitPrms[0U].inCoreOps       = NULL;
    gVpsDrvPlatDataTda2xx.m2mDssDrvInitPrms[0U].outCoreInstObj  = NULL;
    gVpsDrvPlatDataTda2xx.m2mDssDrvInitPrms[0U].outCoreOps      = NULL;

#endif /* VPS_DSS_BUILD */
#endif /* defined(VPS_VIP_BUILD) ||... */
#if defined(VPS_CAL_BUILD) && defined (SOC_TDA2EX) || defined (SOC_AM571x)

#endif
}

#endif

#if defined (SOC_TDA3XX)
void vpsInitTda3xxPlatData(void)
{
#if (defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD) || \
    defined (VPS_ISS_BUILD) || defined (VPS_CAL_BUILD))
    UInt32 idx = 0;
#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#if defined (VPS_VIP1_BUILD)
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* #if defined (VPS_VIP1_BUILD) */
#endif /* VPS_VIP_BUILD */

#ifdef VPS_DSS_BUILD
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_INST_DSS_WB1;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* VPS_DSS_BUILD */
#endif /* VPS_CAPT_BUILD */

#ifdef VPS_DSS_BUILD
    /* Display driver */
    idx = 0;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID1;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID2;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_GFX1;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));

    /* DSS M2M driver */
    gVpsDrvPlatDataTda3xx.m2mDssDrvInitPrms[0U].drvInstId       =
        VPS_M2M_DSS_INST_WB1;
    gVpsDrvPlatDataTda3xx.m2mDssDrvInitPrms[0U].inCoreInstObj   = NULL;
    gVpsDrvPlatDataTda3xx.m2mDssDrvInitPrms[0U].inCoreOps       = NULL;
    gVpsDrvPlatDataTda3xx.m2mDssDrvInitPrms[0U].outCoreInstObj  = NULL;
    gVpsDrvPlatDataTda3xx.m2mDssDrvInitPrms[0U].outCoreOps      = NULL;

#endif /* VPS_DSS_BUILD */

#ifdef VPS_CAL_BUILD

    /* Generic capture driver should be included in the build, else we cannot
     *  support ISS based capture */
#ifndef VPS_CAPT_BUILD
    #error "ReBuild after including build option -DVPS_CAPT_BUILD"
#endif /* VPS_CAPT_BUILD */

    idx = 0;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_ID;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_CPI;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_OTF0_ID;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_ISS_CAPT_INST_MAX_ID > idx));

#endif /* VPS_CAL_BUILD */
#endif /* (defined(VPS_VIP_BUILD) ||... */

#ifdef VPS_M2M_BUILD

    BspUtils_memset(&gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms, 0U,
                    sizeof (gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms));
    idx = 0U;

#ifdef VPS_ISS_BUILD
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].drvInstId =
        VPS_M2M_ISS_INST_CAL_ISP;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].isMultiChSupported = FALSE;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].numCores           = 1U;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].coreInstId[0U]     =
        VpsCore_issM2mGetCoreInstObj(VPSCORE_ISS_M2M_ISP_INST_0);
    idx++;
#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].drvInstId =
        VPS_M2M_ISS_INST_SIMCOP;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].isMultiChSupported = FALSE;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].numCores           = 1U;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].coreInstId[0U]     =
        (VpsCore_Inst *) VPSCORE_ISS_SIMCOP_INST_0;
    idx++;
#endif /* VPS_SIMCOP_BUILD */

#endif /* VPS_M2M_BUILD */
}

#endif

#if defined (OMAP5430_BUILD)
void vpsInitOmap5PlatData(void)
{
#ifdef VPS_DSS_BUILD
    UInt32 idx = 0;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID1;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID2;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID3;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_GFX1;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));

    /* DSS M2M driver */
    gVpsDrvPlatDataOmap5x.m2mDssDrvInitPrms[0U].drvInstId       =
        VPS_M2M_DSS_INST_WB1;
    gVpsDrvPlatDataOmap5x.m2mDssDrvInitPrms[0U].inCoreInstObj   = NULL;
    gVpsDrvPlatDataOmap5x.m2mDssDrvInitPrms[0U].inCoreOps       = NULL;
    gVpsDrvPlatDataOmap5x.m2mDssDrvInitPrms[0U].outCoreInstObj  = NULL;
    gVpsDrvPlatDataOmap5x.m2mDssDrvInitPrms[0U].outCoreOps      = NULL;

#endif /* VPS_DSS_BUILD */
}

#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
void vpsInitTi814xPlatData(void)
{
#if (defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD))
    UInt32 idx = 0;
#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#if defined (VPS_VIP1_BUILD)
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* #if defined (VPS_VIP1_BUILD) */
#endif /* VPS_VIP_BUILD */
#endif /* VPS_CAPT_BUILD */

#ifdef VPS_DSS_BUILD
    idx = 0;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));

    /* DSS M2M driver */
    gVpsDrvPlatDataTI814x.m2mDssDrvInitPrms[0U].drvInstId       = 0U;
    gVpsDrvPlatDataTI814x.m2mDssDrvInitPrms[0U].inCoreInstObj   = NULL;
    gVpsDrvPlatDataTI814x.m2mDssDrvInitPrms[0U].inCoreOps       = NULL;
    gVpsDrvPlatDataTI814x.m2mDssDrvInitPrms[0U].outCoreInstObj  = NULL;
    gVpsDrvPlatDataTI814x.m2mDssDrvInitPrms[0U].outCoreOps      = NULL;

#endif /* VPS_DSS_BUILD */
#endif /* (defined(VPS_VIP_BUILD) || defined(VPS_DSS_BUILD)) */
}

#endif

