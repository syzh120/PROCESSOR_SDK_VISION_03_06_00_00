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
 *  \file vpslib_initTda3xx.c
 *
 *  \brief File containing the VPS library init and deinit functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/csl/soc.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#endif
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dssWb.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#endif

#ifdef VPS_CAL_BUILD
#include <ti/drv/vps/src/vpslib/common/irm_resrcMgr.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_capture.h>
#endif /* VPS_CAL_BUILD */

#ifdef VPS_ISS_BUILD
#include <ti/drv/vps/src/vpslib/isscore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_simcop.h>
#endif

#include <ti/drv/vps/src/vpslib/common/vps_common.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS Init object to store HAL handles and other variables.
 */
typedef struct
{
#if defined (VPS_VIP_BUILD)
    VpsHal_Handle vpdmaHandle[VPSHAL_VPDMA_INST_ID_MAX];
    VpsHal_Handle cscHandle[VPSHAL_CSC_INST_ID_MAX];
    VpsHal_Handle scHandle[VPSHAL_SC_INST_ID_MAX];
#endif
#ifdef VPS_VIP_BUILD
    VpsHal_Handle vipTopHandle[VPSHAL_VIP_TOP_MAX_INST];
    VpsHal_Handle vipPortHandle[VPSHAL_VIP_PORT_INST_ID_MAX];

    VpsCore_Inst  vipCoreInstObj[VPSHAL_VIP_TOP_MAX_INST];
#endif
#ifdef VPS_DSS_BUILD
    VpsHal_Handle vidPipeHandle[VPSHAL_DSS_DISPC_VID_INST_ID_MAX];
    VpsHal_Handle ovlHandle[VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX];
    UInt32        dctrlHandle;

    VpsCore_Inst  dssCoreInstObj;
    VpsCore_Inst  dssWbCoreInstObj;
    VpsCore_Inst  dctrlCoreInstObj;
#endif
#if !(defined (VPS_VIP_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    UInt32        dummy;
#endif
} VpsLibInit_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Vps_commonInit(const VpsLib_InitParams *initPrms);
static Int32 Vps_commonDeInit(void);
static Int32 VpsHal_open(void);
static Int32 VpsHal_close(void);
#ifdef VPS_VIP_BUILD
static Int32 Vps_captVipCoreInit(void);
static Int32 Vps_captVipCoreDeInit(void);
#endif
#ifdef VPS_DSS_BUILD
static Int32 Vps_dispCoreInit(const VpsLib_InitParams *initPrms);
static Int32 Vps_dispCoreDeInit(void);
#endif
#ifdef VPS_CAL_BUILD
static Int32 Vps_issCaptCoreInit(void);
static Int32 Vps_issCaptCoreDeInit(void);
#endif
#ifdef VPS_ISS_BUILD
static Int32 Vps_issM2mCoreInit(void);
static Int32 Vps_issM2mCoreDeInit(void);
#endif
#ifdef VPS_SIMCOP_BUILD
static Int32 Vps_issSimcopCoreInit(void);
static Int32 Vps_issSimcopCoreDeInit(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsLibInit_Obj      gVpsLibInitObj;

static VpsLib_PlatformData gVpsPlatDataTda3xx =
{
    NULL,                    /* HAL platform data */

    NULL,

    NULL,

    NULL,

    /*
     * Misc platform data.
     */
    /* Event Manager */
    0U,                      /* numEvtMgr */
    {
        /*  evtMgrInstPrms:instId,          evtMgrInstPrms:irqNumber,
         *  evtMgrInstPrms:intcNum,         evtMgrInstPrms:intcBaseAddr,
         *  evtMgrInstPrms:vpdmaBaseAddr */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {
            VEM_INST_ID_VIP1,CSL_INTC_EVENTID_VIP1INT0,
            CSL_VPS_INTC_NUM,SOC_VIP1_VIP_REGS_BASE,
            SOC_VIP1_VIP_VPDMA_REGS_BASE
        },
  #endif    /*   #if defined (VPS_VIP1_BUILD) */
        /* VIP2, VIP3, VPE are not present for TDA3xx,
         * But VEM max inst is 4 for all pplatforms. */
        {
            0U
        },
        {
            0U
        },
        {
            0U
        },
#endif
#if (defined (VPS_DSS_BUILD) && !defined (VPS_VIP_BUILD))

        {
            /* This is Just To avoid DSS only Build error, Interrupts are
             * handled differently for DSS. Below data is invalid */
            0U
        }

#endif
#if !(defined (VPS_VIP_BUILD)) && \
        !(defined (VPS_DSS_BUILD))
        0U
#endif
    },

    /* Resorce Manager */
    0U,                      /* numResrcMgr */
    {
        /* resrcMgrInstPrms:instId */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {
            VRM_INST_ID_VIP1
        },
  #endif    /*   #if defined (VPS_VIP1_BUILD) */
        /* VIP2, VIP3, VPE are not present for TDA3xx,
         * But VRM max inst is 4 for all pplatforms. */
        {
            VRM_INST_ID_GENERIC
        },
        {
            VRM_INST_ID_GENERIC
        },
        {
            VRM_INST_ID_GENERIC
        },
#endif
#if (defined (VPS_DSS_BUILD) && !defined (VPS_VIP_BUILD))

        {
            /* This is Just To avoid DSS only Build error, Interrupts are
             * handled differently for DSS. Below data is invalid */
            VRM_INST_ID_GENERIC
        }
#endif
#if !(defined (VPS_VIP_BUILD)) && \
        !(defined (VPS_DSS_BUILD))
        0U
#endif
    },
    NULL,   /* calHal */
    0U,     /* numCalEmInst */
    NULL    /* calEmInitPrms */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS Lib init function.
 */
Int32 VpsLib_init(const VpsLib_InitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    VpsLib_InitParams localInitPrms;
    VpsHal_InitParams halInitPrms;

    /* Memset to zero is must as this sets the pointers to NULL */
    BspUtils_memset(&gVpsLibInitObj, 0, sizeof (gVpsLibInitObj));

    /* If NULL is passed use default */
    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        VpsLibInitParams_init(&localInitPrms);
    }

    halInitPrms.isAddrTransReq  = initPrms->isAddrTransReq;
    halInitPrms.virtBaseAddr    = initPrms->virtBaseAddr;
    halInitPrms.physBaseAddr    = initPrms->physBaseAddr;
    halInitPrms.isCacheOpsReq   = initPrms->isCacheOpsReq;
    halInitPrms.isCacheFlushReq = initPrms->isCacheFlushReq;
    retVal += VpsHal_init(&halInitPrms);
    retVal += VpsHal_open();
    retVal += Vps_commonInit(initPrms);
#ifdef VPS_VIP_BUILD
    retVal += Vps_captVipCoreInit();
#endif
#ifdef VPS_DSS_BUILD
    retVal += Vps_dispCoreInit(initPrms);
#endif

#ifdef VPS_CAL_BUILD
    retVal += Vps_issCaptCoreInit();
#endif /* VPS_CAL_BUILD */
#ifdef VPS_ISS_BUILD
    retVal += Vps_issM2mCoreInit();
#endif /* VPS_ISS_BUILD */
#ifdef VPS_SIMCOP_BUILD
    retVal += Vps_issSimcopCoreInit();
#endif /* VPS_SIMCOP_BUILD */

    return (retVal);
}

/**
 *  \brief VPS Lib deinit function.
 */
Int32 VpsLib_deInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

#ifdef VPS_SIMCOP_BUILD
    retVal += Vps_issSimcopCoreDeInit();
#endif /* VPS_SIMCOP_BUILD */
#ifdef VPS_CAL_BUILD
    retVal += Vps_issCaptCoreDeInit();
#endif /* VPS_CAL_BUILD */
#ifdef VPS_ISS_BUILD
    retVal += Vps_issM2mCoreDeInit();
#endif

#ifdef VPS_DSS_BUILD
    retVal += Vps_dispCoreDeInit();
#endif
#ifdef VPS_VIP_BUILD
    retVal += Vps_captVipCoreDeInit();
#endif
    retVal += Vps_commonDeInit();
    retVal += VpsHal_close();
    retVal += VpsHal_deInit();

    return (retVal);
}

VpsLib_PlatformData *VpsLib_getPlatformData(void)
{
    VpsLib_PlatformData *platData = NULL;
#ifdef VPS_VIP_BUILD
    UInt32 numVip;
#endif

    platData = &gVpsPlatDataTda3xx;
    platData->numEvtMgr   = 0U;
    platData->numResrcMgr = 0U;
#ifdef VPS_VIP_BUILD
    numVip = 0U;
    #if defined (VPS_VIP1_BUILD)
        numVip++;
    #endif    /* #if defined (VPS_VIP1_BUILD) */

    platData->numEvtMgr   += numVip;
    platData->numResrcMgr += numVip;
#endif

    platData->hal = VpsHal_getPlatformData();
    GT_assert(VpsTrace, (NULL != platData->hal));

    platData->issCommonPrms = NULL;
    platData->calHal        = NULL;
    platData->ispHal        = NULL;
    platData->numCalEmInst  = 0;
    platData->calEmInitPrms = NULL;

#ifdef VPS_CAL_BUILD
    platData->calHal = (const Ptr *) VpsHal_getCalPlatformData();
#endif /* VPS_CAL_BUILD */

#ifdef VPS_ISS_BUILD
    platData->ispHal = (const Ptr *) VpsHal_getIspPlatformData();
#endif

#ifdef VPS_SIMCOP_BUILD
    platData->simcopHal = (const Ptr *) VpsHal_getSimcopPlatformData();
#endif
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * Name 'issCommonPrms, calHal, ispHal & simcopHal'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointers to different layer's meta data are stored as void*.
 */

    return (platData);
}

#ifdef VPS_VIP_BUILD
VpsCore_Inst VpsLib_getVipCoreInstObj(UInt32 vipInstId)
{
    VpsCore_Inst    instObj = NULL;
    VpsLibInit_Obj *pObj    = &gVpsLibInitObj;

    if (vipInstId < VPSHAL_VIP_TOP_MAX_INST)
    {
        instObj = pObj->vipCoreInstObj[vipInstId];
    }

    return (instObj);
}

#endif

#ifdef VPS_DSS_BUILD
VpsCore_Inst VpsLib_getDssCoreInstObj(void)
{
    VpsCore_Inst    instObj = NULL;
    VpsLibInit_Obj *pObj    = &gVpsLibInitObj;

    instObj = pObj->dssCoreInstObj;

    return (instObj);
}

VpsCore_Inst VpsLib_getDssWbCoreInstObj(void)
{
    VpsCore_Inst    instObj = NULL;
    VpsLibInit_Obj *pObj    = &gVpsLibInitObj;

    instObj = pObj->dssWbCoreInstObj;

    return (instObj);
}

VpsCore_Inst VpsLib_getDctrlCoreInstObj(void)
{
    VpsCore_Inst    instObj = NULL;
    VpsLibInit_Obj *pObj    = &gVpsLibInitObj;

    instObj = pObj->dctrlCoreInstObj;

    return (instObj);
}

VpsHal_Handle VpsLib_getDssOvlyHalHandle(UInt32 ovlyInstId)
{
    VpsHal_Handle   halHandle = NULL;
    VpsLibInit_Obj *pObj      = &gVpsLibInitObj;

    if (ovlyInstId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        halHandle = pObj->ovlHandle[ovlyInstId];
    }

    return (halHandle);
}

#endif

#if defined (VPS_VIP_BUILD)
VpsHal_Handle VpsLib_getVpdmaHalHandle(UInt32 vpdmaInstId)
{
    VpsHal_Handle   halHandle = NULL;
    VpsLibInit_Obj *pObj      = &gVpsLibInitObj;

    if (vpdmaInstId < VPSHAL_VPDMA_INST_ID_MAX)
    {
        halHandle = pObj->vpdmaHandle[vpdmaInstId];
    }

    return (halHandle);
}

#endif

static Int32 Vps_commonInit(const VpsLib_InitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    VpsLib_PlatformData *platData;

    /* Get Platform data */
    platData = VpsLib_getPlatformData();
    GT_assert(VpsTrace, (NULL != platData));

#if defined (VPS_VIP_BUILD)
    if (BSP_SOK == retVal)
    {
        /* Resource Manager Init */
        retVal = Vrm_init(
            platData->numResrcMgr,
            &platData->resrcMgrInstPrms[0U]);
        if (retVal != BSP_SOK)
        {
            GT_0trace(VpsTrace, GT_ERR, "VPS: Resource Manager init failed\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        UInt32 i;
        /* Update the interrupt numbers from init params. */
        for (i= 0U; i< VEM_MAX_INST; i++)
        {
            switch (platData->evtMgrInstPrms[i].instId)
            {
                case VEM_INST_ID_VIP1:
                    platData->evtMgrInstPrms[i].irqNumber = initPrms->irqParams.vipIrqNum[0U];
                    break;
                case VEM_INST_ID_VPE1:
                    platData->evtMgrInstPrms[i].irqNumber = initPrms->irqParams.vpeIrqNum;
                    break;
                default:
                    break;
            }
        }
        /* Event Manager Init */
        retVal = Vem_init(platData->numEvtMgr, &platData->evtMgrInstPrms[0U]);
        if (retVal != BSP_SOK)
        {
            GT_0trace(VpsTrace, GT_ERR, "VPS: Event Manager init failed\r\n");
        }
    }
#endif

#ifdef VPS_ISS_ISP_DEF
    if (BSP_SOK == retVal)
    {
        VpsHal_initCommonPlatformData(initPrms->irqParams.issIrqNum);
        platData->issCommonPrms = (const Ptr *) VpsHal_getCommonPlatformData();
        retVal = VpsLib_issCommonInit(platData);
        if (retVal != BSP_SOK)
        {
            GT_0trace(VpsTrace, GT_ERR, "VPS: ISS Common Init Failed\r\n");
        }
    }
#endif

    return (retVal);
}

static Int32 Vps_commonDeInit(void)
{
    Int32 retVal = BSP_SOK;

#ifdef VPS_ISS_ISP_DEF
    retVal = VpsLib_issCommonDeInit(NULL);
#endif

#if defined (VPS_VIP_BUILD)
    retVal += Vem_deInit();
    if (retVal != BSP_SOK)
    {
        GT_0trace(VpsTrace, GT_ERR, "VPS: Event Manager deinit failed\r\n");
    }

    retVal += Vrm_deInit();
    if (retVal != BSP_SOK)
    {
        GT_0trace(VpsTrace, GT_ERR, "VPS: Resource Manager deinit failed\r\n");
    }
#endif

    return (retVal);
}

static Int32 VpsHal_open(void)
{
    Int32  retVal = BSP_SOK;
    const VpsLib_PlatformData *platData;
#if defined (VPS_VIP_BUILD) || \
    defined (VPS_DSS_BUILD)
    UInt32 halCnt, halId;
    VpsLibInit_Obj            *pObj = &gVpsLibInitObj;
#endif
#if defined (VPS_VIP_BUILD)
    VpsHal_VpdmaOpenParams     vpdmaOpenPrms;
    VpsHal_CscOpenParams       cscOpenPrms;
    VpsHal_ScOpenParams        scOpenPrms;
#endif
#ifdef VPS_VIP_BUILD
    VpsHal_VipTopOpenParams    vipTopOpenPrms;
    VpsHal_VipPortOpenParams   vipPortOpenPrms;
#endif
#ifdef VPS_DSS_BUILD
    VpsHal_DispcVidOpenParams  vidPipeOpenPrms;
    VpsHal_DispcOvlyOpenParams ovlyOpenPrms;
#endif

    /* Get Platform data */
    platData = VpsLib_getPlatformData();
    GT_assert(VpsTrace, (NULL != platData));

#if defined (VPS_VIP_BUILD)
    if ((BSP_SOK == retVal) && (platData->hal->numVpdma > 0))
    {
        /* Open VPDMA HALs */
        for (halCnt = 0U; halCnt < platData->hal->numVpdma; halCnt++)
        {
            halId = platData->hal->vpdmaInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_VPDMA_INST_ID_MAX));
            vpdmaOpenPrms.halId = halId;
            vpdmaOpenPrms.ver   = VPSHAL_VPDMA_VER_DEFAULT;
            if (VpsLib_platformIsTI814xFamilyBuild())
            {
                vpdmaOpenPrms.ver = VPSHAL_VPDMA_VER_288;
            }
            pObj->vpdmaHandle[halId] = VpsHal_vpdmaOpen(&vpdmaOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->vpdmaHandle[halId]));
        }
    }

    if ((BSP_SOK == retVal) && (platData->hal->numCsc > 0))
    {
        /* Open CSC HALs */
        for (halCnt = 0U; halCnt < platData->hal->numCsc; halCnt++)
        {
            halId = platData->hal->cscInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_CSC_INST_ID_MAX));
            cscOpenPrms.halId      = halId;
            pObj->cscHandle[halId] = VpsHal_cscOpen(&cscOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->cscHandle[halId]));
        }
    }

    if ((BSP_SOK == retVal) && (platData->hal->numSc > 0))
    {
        /* Open SC HALs */
        for (halCnt = 0U; halCnt < platData->hal->numSc; halCnt++)
        {
            halId = platData->hal->scInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_SC_INST_ID_MAX));
            scOpenPrms.halId      = halId;
            pObj->scHandle[halId] = VpsHal_scOpen(&scOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->scHandle[halId]));
        }
    }
#endif

#ifdef VPS_VIP_BUILD
    if ((BSP_SOK == retVal) && (platData->hal->numVipTop > 0))
    {
        /* Open VIP Top HALs */
        for (halCnt = 0U; halCnt < platData->hal->numVipTop; halCnt++)
        {
            halId = platData->hal->vipTopInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_VIP_TOP_MAX_INST));
            vipTopOpenPrms.halId      = halId;
            pObj->vipTopHandle[halId] = VpsHal_vipTopOpen(&vipTopOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->vipTopHandle[halId]));
        }
    }

    if ((BSP_SOK == retVal) && (platData->hal->numVipPort > 0))
    {
        /* Open VIP Port HALs */
        for (halCnt = 0U; halCnt < platData->hal->numVipPort; halCnt++)
        {
            halId = platData->hal->vipPortInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_VIP_PORT_INST_ID_MAX));
            vipPortOpenPrms.halId      = halId;
            pObj->vipPortHandle[halId] = VpsHal_vipPortOpen(&vipPortOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->vipPortHandle[halId]));
        }
    }
#endif

#ifdef VPS_DSS_BUILD
    if ((BSP_SOK == retVal) && (platData->hal->numVidPipe > 0))
    {
        /* Open VIDEO Pipeline HALs */
        for (halCnt = 0U; halCnt < platData->hal->numVidPipe; halCnt++)
        {
            halId = platData->hal->vidPipeInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_DSS_DISPC_VID_MAX_INST));
            vidPipeOpenPrms.halId      = halId;
            pObj->vidPipeHandle[halId] = VpsHal_dssVidOpen(
                &vidPipeOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->vidPipeHandle[halId]));
        }
    }

    if ((BSP_SOK == retVal) && (platData->hal->numWbPipe > 0))
    {
        /* Open WB Pipeline HALs */
        for (halCnt = 0U; halCnt < platData->hal->numWbPipe; halCnt++)
        {
            halId = platData->hal->wbPipeInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_DSS_DISPC_PIPE_MAX_INST));
            vidPipeOpenPrms.halId      = halId;
            pObj->vidPipeHandle[halId] = VpsHal_dssVidOpen(
                &vidPipeOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->vidPipeHandle[halId]));
        }
    }

    if ((BSP_SOK == retVal) && (platData->hal->numOvlyMgr > 0))
    {
        /* Open Overlay HALs */
        for (halCnt = 0U; halCnt < platData->hal->numOvlyMgr; halCnt++)
        {
            halId = platData->hal->ovlyMgrInstPrms[halCnt].halId;
            GT_assert(VpsTrace, (halId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX));
            ovlyOpenPrms.halId     = halId;
            pObj->ovlHandle[halId] = VpsHal_dssOvlyOpen(&ovlyOpenPrms);
            GT_assert(VpsTrace, (NULL != pObj->ovlHandle[halId]));
        }
    }
#endif

    return (retVal);
}

static Int32 VpsHal_close(void)
{
    Int32           retVal = BSP_SOK;
#if defined (VPS_VIP_BUILD) || \
    defined (VPS_DSS_BUILD)
    UInt32          halCnt;
    VpsLibInit_Obj *pObj = &gVpsLibInitObj;
#endif

#ifdef VPS_VIP_BUILD
    /* Close VIP Port HALs */
    for (halCnt = 0U; halCnt < VPSHAL_VIP_PORT_INST_ID_MAX; halCnt++)
    {
        if (pObj->vipPortHandle[halCnt] != NULL)
        {
            retVal = VpsHal_vipPortClose(pObj->vipPortHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->vipPortHandle[halCnt] = NULL;
        }
    }

    /* Close VIP Top HALs */
    for (halCnt = 0U; halCnt < VPSHAL_VIP_TOP_MAX_INST; halCnt++)
    {
        if (pObj->vipTopHandle[halCnt] != NULL)
        {
            retVal = VpsHal_vipTopClose(pObj->vipTopHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->vipTopHandle[halCnt] = NULL;
        }
    }
#endif

#if defined (VPS_VIP_BUILD)
    /* Close SC HALs */
    for (halCnt = 0U; halCnt < VPSHAL_SC_INST_ID_MAX; halCnt++)
    {
        if (pObj->scHandle[halCnt] != NULL)
        {
            retVal = VpsHal_scClose(pObj->scHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->scHandle[halCnt] = NULL;
        }
    }

    /* Close CSC HALs */
    for (halCnt = 0U; halCnt < VPSHAL_CSC_INST_ID_MAX; halCnt++)
    {
        if (pObj->cscHandle[halCnt] != NULL)
        {
            retVal = VpsHal_cscClose(pObj->cscHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->cscHandle[halCnt] = NULL;
        }
    }

    /* Close VPDMA HALs */
    for (halCnt = 0U; halCnt < VPSHAL_VPDMA_INST_ID_MAX; halCnt++)
    {
        if (pObj->vpdmaHandle[halCnt] != NULL)
        {
            retVal = VpsHal_vpdmaClose(pObj->vpdmaHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->vpdmaHandle[halCnt] = NULL;
        }
    }
#endif

#ifdef VPS_DSS_BUILD
    /* Close VIDEO Pipeline HALs */
    for (halCnt = 0U; halCnt < VPSHAL_DSS_DISPC_VID_INST_ID_MAX; halCnt++)
    {
        if (pObj->vidPipeHandle[halCnt] != NULL)
        {
            retVal = VpsHal_dssVidClose(pObj->vidPipeHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->vidPipeHandle[halCnt] = NULL;
        }
    }

    /* Close overlay HALs */
    for (halCnt = 0U; halCnt < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX; halCnt++)
    {
        if (pObj->ovlHandle[halCnt] != NULL)
        {
            retVal = VpsHal_dssOvlyClose(pObj->ovlHandle[halCnt]);
            GT_assert(VpsTrace, (BSP_SOK == retVal));
            pObj->ovlHandle[halCnt] = NULL;
        }
    }

#endif

    return (retVal);
}

#ifdef VPS_VIP_BUILD
static Int32 Vps_captVipCoreInit(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 coreCnt;
    VpsLibInit_Obj            *pObj = &gVpsLibInitObj;
    VpsLib_PlatformData *platData;
    VpsCore_VipInitParams      vipCoreInitPrms;

    /* Get Platform data */
    platData = VpsLib_getPlatformData();
    GT_assert(VpsTrace, (NULL != platData));

    /* Open VIP Core */
    GT_assert(VpsTrace, (0U != platData->hal->numVipTop));
    GT_assert(VpsTrace, (platData->hal->numVipTop <= VPSHAL_VIP_TOP_MAX_INST));
    for (coreCnt = 0U; coreCnt < VPSHAL_VIP_TOP_MAX_INST; coreCnt++)
    {
        if (pObj->vipTopHandle[VPSHAL_VIP1 + coreCnt] != NULL)
        {
            vipCoreInitPrms.vipTopHandle =
                pObj->vipTopHandle[VPSHAL_VIP1 + coreCnt];
            if (VpsLib_platformIsTI814xFamilyBuild())
            {
                GT_assert(VpsTrace,
                          (NULL != pObj->vpdmaHandle[VPSHAL_VPDMA_GENERIC]));
                vipCoreInitPrms.vpdmaHandle =
                    pObj->vpdmaHandle[VPSHAL_VPDMA_GENERIC];
                vipCoreInitPrms.vemInstId = VEM_INST_ID_GENERIC;
                vipCoreInitPrms.vrmInstId = VRM_INST_ID_GENERIC;
            }
            else
            {
                vipCoreInitPrms.vpdmaHandle =
                    pObj->vpdmaHandle[VPSHAL_VIP1_VPDMA + coreCnt];
                vipCoreInitPrms.vemInstId =
                    (Vem_InstId) (VEM_INST_ID_VIP1 + coreCnt);
                vipCoreInitPrms.vrmInstId =
                    (Vrm_InstId) (VRM_INST_ID_VIP1 + coreCnt);
            }
            vipCoreInitPrms.s0PortAHandle =
                pObj->vipPortHandle[VPSHAL_VIP1_S0_PORTA + (4U * coreCnt)];
            vipCoreInitPrms.s0PortBHandle =
                pObj->vipPortHandle[VPSHAL_VIP1_S0_PORTB + (4U * coreCnt)];
            vipCoreInitPrms.s1PortAHandle =
                pObj->vipPortHandle[VPSHAL_VIP1_S1_PORTA + (4U * coreCnt)];
            vipCoreInitPrms.s1PortBHandle =
                pObj->vipPortHandle[VPSHAL_VIP1_S1_PORTB + (4U * coreCnt)];
            vipCoreInitPrms.sc0Handle =
                pObj->scHandle[VPSHAL_VIP1_S0_SC + (2U * coreCnt)];
            vipCoreInitPrms.sc1Handle =
                pObj->scHandle[VPSHAL_VIP1_S1_SC + (2U * coreCnt)];
            vipCoreInitPrms.csc0Handle =
                pObj->cscHandle[VPSHAL_VIP1_S0_CSC + (2U * coreCnt)];
            vipCoreInitPrms.csc1Handle =
                pObj->cscHandle[VPSHAL_VIP1_S1_CSC + (2U * coreCnt)];
            pObj->vipCoreInstObj[coreCnt] = VpsCore_vipInit(&vipCoreInitPrms);
            GT_assert(VpsTrace, (NULL != pObj->vipCoreInstObj[coreCnt]));
        }
    }

    return (retVal);
}

static Int32 Vps_captVipCoreDeInit(void)
{
    Int32           retVal = BSP_SOK;
    UInt32          coreCnt;
    VpsLibInit_Obj *pObj = &gVpsLibInitObj;

    for (coreCnt = 0U; coreCnt < VPSHAL_VIP_TOP_MAX_INST; coreCnt++)
    {
        if (NULL != pObj->vipCoreInstObj[coreCnt])
        {
            retVal += VpsCore_vipDeInit(pObj->vipCoreInstObj[coreCnt]);
            pObj->vipCoreInstObj[coreCnt] = NULL;
        }
    }

    return (retVal);
}

#endif

#ifdef VPS_DSS_BUILD
static Int32 Vps_dispCoreInit(const VpsLib_InitParams *initPrms)
{
    Int32  retVal = BSP_SOK;
    VpsLib_PlatformData *platData;
    VpsCore_DssInitParams dssCoreInitPrms;
    VpsCore_DssWbInitParams dssWbCoreInitPrms = {0};
    VpsCore_DctrlInitParams dctrlCoreInitPrms;
    VpsLibInit_Obj            *pObj = &gVpsLibInitObj;
    UInt32 halId, cnt;

    /* Get Platform data */
    platData = VpsLib_getPlatformData();
    GT_assert(VpsTrace, (NULL != platData));

    /* TODO - Check if this sequence is preoper or not, find a way to avoid
     *             hard codings of array index*/

    /* Init DSS Core */
    GT_assert(VpsTrace, ((platData->hal->numVidPipe) <= \
                         VPSHAL_DSS_DISPC_VID_MAX_INST));
    GT_assert(VpsTrace, ((platData->hal->numWbPipe) <= \
                         VPSHAL_DSS_DISPC_WB_MAX_INST));
    GT_assert(VpsTrace, ((platData->hal->numOvlyMgr) <= \
                         VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX));

    dssCoreInitPrms.dispcIrqNumber = 0U;
    dssCoreInitPrms.dispcIrqNumber = initPrms->irqParams.dssIrqNum;
    for (cnt = 0U; cnt < platData->hal->numVidPipe; cnt++)
    {
        halId = platData->hal->vidPipeInstPrms[cnt].halId;
        dssCoreInitPrms.vidHandle[halId] = pObj->vidPipeHandle[halId];
    }
    for (cnt = 0U; cnt < platData->hal->numOvlyMgr; cnt++)
    {
        halId = platData->hal->ovlyMgrInstPrms[cnt].halId;
        dssCoreInitPrms.ovlHandle[halId] = pObj->ovlHandle[halId];
    }

    pObj->dssCoreInstObj = VpsCore_dssInit(&dssCoreInitPrms);
    GT_assert(VpsTrace, (NULL != pObj->dssCoreInstObj));

    dssWbCoreInitPrms.dispcIrqNumber = 0U;
    dssWbCoreInitPrms.dispcIrqNumber = initPrms->irqParams.dssIrqNum;
    for (cnt = 0U; cnt < platData->hal->numWbPipe; cnt++)
    {
        halId = platData->hal->wbPipeInstPrms[cnt].halId;
        dssWbCoreInitPrms.wbHandle[cnt] = pObj->vidPipeHandle[halId];
    }

    pObj->dssWbCoreInstObj = VpsCore_dssWbInit(&dssWbCoreInitPrms);
    GT_assert(VpsTrace, (NULL != pObj->dssWbCoreInstObj));

    dctrlCoreInitPrms.dispcIrqNumber = 0U;
    dctrlCoreInitPrms.dispcIrqNumber = initPrms->irqParams.dssIrqNum;
    dctrlCoreInitPrms.dctrlId        = 0;

    for (halId = 0U; halId < platData->hal->numOvlyMgr; halId++)
    {
        dctrlCoreInitPrms.ovlHandle[halId] = pObj->ovlHandle[halId];
    }

    pObj->dctrlCoreInstObj = VpsCore_dctrlInit(&dctrlCoreInitPrms);
    GT_assert(VpsTrace, (NULL != pObj->dssCoreInstObj));
    return (retVal);
}

static Int32 Vps_dispCoreDeInit(void)
{
    Int32           retVal = BSP_SOK;
    VpsLibInit_Obj *pObj   = &gVpsLibInitObj;

    if (NULL != pObj->dssCoreInstObj)
    {
        retVal += VpsCore_dssDeInit(pObj->dssCoreInstObj);
        pObj->dssCoreInstObj = NULL;
    }
    if (NULL != pObj->dssWbCoreInstObj)
    {
        retVal += VpsCore_dssWbDeInit(pObj->dssWbCoreInstObj);
        pObj->dssWbCoreInstObj = NULL;
    }
    if (NULL != pObj->dctrlCoreInstObj)
    {
        retVal += VpsCore_dctrlDeInit(pObj->dctrlCoreInstObj);
        pObj->dctrlCoreInstObj = NULL;
    }

    return (retVal);
}

#endif

Bool VpsLib_platformIsTda2xxFamilyBuild(void)
{
    return (FALSE);
}

Bool VpsLib_platformIsTI814xFamilyBuild(void)
{
    return (FALSE);
}

Bool VpsLib_platformIsOmap5FamilyBuild(void)
{
    return (FALSE);
}

Bool VpsLib_platformIsTda3xxFamilyBuild(void)
{
    return (TRUE);
}

#if defined VPS_ISS_ISP_DEF
int32_t VpsLib_issCommonInit(const VpsLib_PlatformData *platData)
{
    int32_t status;

    GT_assert(VpsTrace, (NULL != platData));
    GT_assert(VpsTrace, (NULL != platData->issCommonPrms));

    status = Vps_iemInit((const issemInitParams_t *) platData->issCommonPrms);

    return (status);
}

int32_t VpsLib_issCommonDeInit(Ptr arg)
{
    int32_t status;

    status = Vps_iemDeInit();

    return (status);
}

#endif

#ifdef VPS_CAL_BUILD
static Int32 Vps_issCaptCoreInit(void)
{
    int32_t  status;
    uint32_t instCnt = 0U;
    VpsLib_PlatformData *platData;
    vcoreissCaptInitParams_t   coreInitParams[VPS_ISS_CAPT_INST_MAX_ID];

    platData = VpsLib_getPlatformData();
    if (NULL != platData)
    {
        GT_assert(VpsTrace, (NULL != platData->calHal));

        coreInitParams[instCnt].instId          = VPS_ISS_CAPT_CAL_A_ID;
        coreInitParams[instCnt].halPlatformData = platData;
        coreInitParams[instCnt].subModules      = SUB_MODULE_CAL_A;
        coreInitParams[instCnt].irqNum          = IEM_INST_ID_IRQ0;

        instCnt++;
        GT_assert(VpsTrace, instCnt < VPS_ISS_CAPT_INST_MAX_ID);

#if defined (VPS_ISS_BUILD)
        /* CPI & OTF can only be supported in TDA3XX */
        if (NULL != platData->ispHal)
        {
            coreInitParams[instCnt].instId =
                VPS_ISS_CAPT_CAL_A_OTF0_ID;
            coreInitParams[instCnt].halPlatformData = platData;
            coreInitParams[instCnt].subModules      =
                SUB_MODULE_CAL_A | SUB_MODULE_ISP;
            coreInitParams[instCnt].irqNum = IEM_INST_ID_IRQ0;
            instCnt++;
            GT_assert(VpsTrace, instCnt < VPS_ISS_CAPT_INST_MAX_ID);
        }

        coreInitParams[instCnt].instId          = VPS_ISS_CAPT_CAL_A_CPI;
        coreInitParams[instCnt].halPlatformData = platData;
        coreInitParams[instCnt].subModules      = SUB_MODULE_CAL_A;
        coreInitParams[instCnt].irqNum          = IEM_INST_ID_IRQ0;
        instCnt++;
        GT_assert(VpsTrace, instCnt <= VPS_ISS_CAPT_INST_MAX_ID);
#endif

        /** TODO - The number of core & IP block could be different.
         *      Right now, we have 1 capture block with multiple modes
         *      Each mode represented as a different instance of capture
         *      core.
         *      Require to pass number of IP and number of core instances
         *      desired.
         *      Right now passing the core instances only */
        GT_assert(VpsTrace, instCnt <= VPS_ISS_CAPT_INST_MAX_ID);
        status = VpsCore_issCaptInit(instCnt,
                                     &coreInitParams[0], NULL);
    }
    else
    {
        status = FVID2_EFAIL;
        GT_assert(VpsTrace, FALSE);
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'status = FVID2_EFAIL;'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
    }
    return status;
}

static Int32 Vps_issCaptCoreDeInit(void)
{
    return (VpsCore_issCaptDeInit(NULL));
}

#endif /* VPS_CAL_BUILD */

#ifdef VPS_ISS_BUILD
static Int32 Vps_issM2mCoreInit(void)
{
    int32_t status;
    VpsLib_PlatformData *platData;
    vcoreIspInitParams_t       ispInitPrms;

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'if (NULL != platData)' used in the condition
 * always yields the same result.
 * Name if (NULL != platData)
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
    platData = VpsLib_getPlatformData();
    if (NULL != platData)
    {
        if (NULL != platData->ispHal)
        {
            ispInitPrms.instId          = VPSCORE_ISS_M2M_ISP_INST_0;
            ispInitPrms.halPlatformData = (Ptr) platData;
            ispInitPrms.irqNum          = IEM_INST_ID_IRQ0;
            ispInitPrms.calInstId       = 1U;
            ispInitPrms.calIrmId        = IRM_MODULE_CAL_B;
            ispInitPrms.subModules      = SUB_MODULE_ISP | SUB_MODULE_CAL_B;
            ispInitPrms.arg = NULL;

            status = VpsCore_issM2mInit(
                VPSCORE_ISS_M2M_MAX_INST,
                &ispInitPrms,
                NULL);
            if (FVID2_SOK != status)
            {
                Bsp_printf(
                    "ISSM2MWdrApp: VpsCore_issM2mInit: ISP Core Init Failed\r\n");
                status = FVID2_EFAIL;
            }
        }
        else
        {
            status = FVID2_EFAIL;
            GT_assert(VpsTrace, FALSE);
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'status = FVID2_EFAIL;'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
        }
    }
    else
    {
        status = FVID2_EFAIL;
        GT_assert(VpsTrace, FALSE);
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'status = FVID2_EFAIL;'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
    }
    return status;
}

static Int32 Vps_issM2mCoreDeInit(void)
{
    return (VpsCore_issM2mDeInit(NULL));
}

#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
static Int32 Vps_issSimcopCoreInit(void)
{
    int32_t status;
    VpsLib_PlatformData *platData;
    vcoreSimcopInitParams_t    simcopInitPrms;

    platData = VpsLib_getPlatformData();
    if (NULL != platData)
    {
        if (NULL != platData->simcopHal)
        {
            simcopInitPrms.isSimcopDmaCfgValid = (uint32_t) FALSE;
            simcopInitPrms.halPlatformData     =
                (Ptr) VpsHal_getSimcopPlatformData();
            simcopInitPrms.instId     = VPSCORE_ISS_SIMCOP_INST_0;
            simcopInitPrms.irqNum     = IEM_INST_ID_IRQ0;
            simcopInitPrms.eventGroup = IEM_EG_SIMCOP0;
            simcopInitPrms.eventNum   = IEM_SIMCOP_EVENT_HWSEQ_DONE;
            simcopInitPrms.arg        = NULL;

            status = (int32_t) VpsCore_simcopInit(
                VPSCORE_ISS_SIMCOP_INST_MAX,
                &simcopInitPrms,
                NULL);
        }
        else
        {
            status = FVID2_EFAIL;
            GT_assert(VpsTrace, FALSE);
        }
    }
    else
    {
        status = FVID2_EFAIL;
        GT_assert(VpsTrace, FALSE);
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'status = FVID2_EFAIL;'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
    }
    return status;
}

static Int32 Vps_issSimcopCoreDeInit(void)
{
    return (VpsCore_simcopDeInit(VPSCORE_ISS_SIMCOP_INST_MAX));
}

#endif /* VPS_SIMCOP_BUILD */

