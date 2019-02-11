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
 *  \file vpscore_dssWb.c
 *
 *  \brief DSS WB core implementation
 *  This file implements the VPS core interface for DSS WB.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stddef.h>
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dssWb.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dctrlIntr.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dssWbPriv.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/include/vps_cfgMem.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

static Int32 VpsCore_dssValidateDssWbParams(
    const VpsCore_DispDssWbParams *pathCfg,
    const VpsCore_DssWbPathObj    *
    pathObj);

static Int32 VpsCore_dssWbPathCopyConfig(VpsCore_DssWbPathObj          *pathObj,
                                         const VpsCore_DispDssWbParams *pathCfg);

static Int32 VpsCore_isWbPipeline(const VpsCore_DssWbPathObj *pathObj);

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
static UInt32 VpsCore_convertWbInNodetoOvlyIndex(UInt32 wbInNode);
#endif

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void vpsCoreDssWbDispcCb(Ptr arg0);
#ifdef __cplusplus
}
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsCore_DssWbObj     gVcoreDssWbObj;

/** \brief Dss Path Objects */
static VpsCore_DssWbPathObj gVcoreDssWbPathObjMemPool[
    VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS];
/** \brief Pool parameters for Dss Path Object pool memory */
static BspUtils_PoolParams  VcoreDssWbPathObjPoolParams;
/**
 *  \brief The flag variable represents whether a given context object is
 *  allocated or not
 */
static UInt32 VcoreDssWbPathObjMemFlag[VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS];

/** \brief DSS core function pointer. */
static const VpsCore_Ops    gDssWbCoreOps =
{
    &VpsCore_dssWbGetProperty,   /* Get property */
    &VpsCore_dssWbOpen,          /* Open function */
    &VpsCore_dssWbClose,         /* Close function */
    &VpsCore_dssWbPathSetConfig, /* Set config */
    &VpsCore_dssWbPathGetConfig, /* Get config */
    &VpsCore_dssWbControl,       /* Control */
    &VpsCore_dssWbStart,         /* Start */
    &VpsCore_dssWbStop,          /* Stop */
    &VpsCore_dssWbIsr,           /* Process */
    NULL,                        /* Prog Buffer*/
    NULL,                        /* putFrames */
    NULL,                        /* getFrames */
    &VpsCore_dssWbGetErrorStat,  /* Get error stats */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void vpsCoreDssWbDispcCb(Ptr arg0)
{
    VpsCore_Handle pathHandle;

    GT_assert(VpsDssCoreTrace, (NULL != arg0));
    pathHandle = (VpsCore_Handle) arg0;
    VpsCore_dssWbIsr(pathHandle, (UInt32) 0);

    return;
}

VpsCore_Inst VpsCore_dssWbInit(const VpsCore_DssWbInitParams *initParams)
{
    VpsCore_DssWbObj *pNewObj = &gVcoreDssWbObj;
    UInt32 i;

    /* init path object pool */
    BspUtils_initPool(&VcoreDssWbPathObjPoolParams,
                      (void *) gVcoreDssWbPathObjMemPool,
                      VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS,
                      sizeof (VpsCore_DssWbPathObj),
                      VcoreDssWbPathObjMemFlag,
                      VpsDssCoreTrace);

    pNewObj->dispcIrqNumber = initParams->dispcIrqNumber;
    /* WB pipeline handle*/
    pNewObj->wbHandle[0] = initParams->wbHandle[0];

    pNewObj->dcNodeNum[0] = VPSCORE_DCTRL_NODE_WB;

    for (i = 0; i < VPSHAL_DSS_DISPC_WB_MAX_INST; i++)
    {
        pNewObj->pathObjPool[i] = 0;
    }
    return (VpsCore_Inst) pNewObj;
}

Int32 VpsCore_dssWbDeInit(VpsCore_Inst pDssWbHandle)
{
    return BSP_SOK;
}

/**
 *  VpsCore_dssWbGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dssWbGetCoreOps(void)
{
    return (&gDssWbCoreOps);
}

Int32 VpsCore_dssWbGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property)
{
    Int32 retVal = BSP_EFAIL;

    if (NULL != property)
    {
        property->name = VPSCORE_DISP_DSSWB;
        retVal         = BSP_SOK;
    }

    return (retVal);
}

Int32 VpsCore_dssWbPathGetConfig(VpsCore_Handle pathHandle,
                                 void          *params)
{
    Int32 retVal = BSP_EFAIL;

    return retVal;
}

Int32 VpsCore_dssWbControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs)
{
    Int32 retVal = BSP_EFAIL;
    VpsCore_DssWbPathObj *pathObj;

    GT_assert(VpsDssCoreTrace, (NULL != handle));
    GT_assert(VpsDssCoreTrace, (NULL != appArgs));

    pathObj = (VpsCore_DssWbPathObj *) handle;

    switch (cmd)
    {
        case VCORE_DSS_SET_CSC_COEFF:
            retVal =
                VpsHal_dssSetCscCoeff(pathObj->pipeHandle,
                                      (Vps_DssCscCoeff *) appArgs);
            break;
        default:
            GT_0trace(VpsDssCoreTrace, GT_ERR, "Invalid cmd \r\n");
            break;
    }
    return retVal;
}

Int32 VpsCore_dssWbGetErrorStat(VpsCore_Handle pathHandle,
                                void          *params)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbErrorStatus *retParams;

    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (NULL != params));

    pathObj = (VpsCore_DssWbPathObj *) pathHandle;

    retParams = (VpsCore_DssWbErrorStatus *) params;

    retVal = Vpscore_dctrlGetDssWbErrorCount(pathObj->dcHandle, retParams);

    return retVal;
}

VpsCore_Handle VpsCore_dssWbOpen(VpsCore_Inst            pDssWbHandle,
                                 const VpsCore_OpenPrms *openPrms,
                                 const void             *coreOpenPrms,
                                 void                   *coreReturnPrms)
{
    const VpsCore_DssWbOpenParams *corePrms =
        (const VpsCore_DssWbOpenParams *) coreOpenPrms;

    VpsCore_DssWbPathObj          *pathObj       = NULL;
    VpsCore_DssWbObj              *pDssWbInstObj =
        (VpsCore_DssWbObj *) pDssWbHandle;
    Int32 retVal    = BSP_SOK;
    UInt32 index    = 0;
    UInt32 handleId = 0;
    Vpscore_dctrlClientInfo        clientInfo;

    GT_assert(VpsDssCoreTrace, (coreOpenPrms != NULL));
    GT_assert(VpsDssCoreTrace, (openPrms != NULL));

    if (corePrms->src != VPS_DSS_DISPC_PIPE_WB)
    {
        retVal = BSP_EINVALID_PARAMS;
    }
    else
    {
        /* Currently only one WB pipeline present */
        index = 0;
    }

    /* TODO: make this part as re-interant, protect global variables*/
    if (retVal == BSP_SOK)
    {
        if (NULL == pDssWbInstObj->pathObjPool[index])
        {
            pDssWbInstObj->pathObjPool[index] = (VpsCore_Handle) BspUtils_alloc(
                &VcoreDssWbPathObjPoolParams,
                sizeof (VpsCore_DssWbPathObj),
                VpsDssCoreTrace);
            if (pDssWbInstObj->pathObjPool[index] == NULL)
            {
                GT_0trace(
                    VpsDssCoreTrace, GT_ERR,
                    "Failed to allocate memory for pathobj\r\n");
                retVal = BSP_EALLOC;
            }
            else
            {
                pathObj =
                    (VpsCore_DssWbPathObj *) pDssWbInstObj->pathObjPool[index];
                BspUtils_memset(pathObj, (UInt8) 0U,
                                sizeof (VpsCore_DssWbPathObj));
            }
        }
        else
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Core for this instance is already opened\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (retVal == BSP_SOK)
    {
        pathObj->drvData        = openPrms->drvData;
        pathObj->handleId       = (index + VPS_DSS_DISPC_PIPE_WB);
        pathObj->parent         = (VpsCore_DssWbObj *) pDssWbInstObj;
        pathObj->reqFrmCb       = openPrms->reqFrmCb;
        pathObj->frmDoneCb      = openPrms->frmDoneCb;
        pathObj->pipeHandle     = pDssWbInstObj->wbHandle[index];
        pathObj->dcNode         = pDssWbInstObj->dcNodeNum[index];
        pathObj->isStarted      = FALSE;
        pathObj->regionBasedBit = 0;
        pathObj->pipeDisableSem = BspOsal_semCreate(0, TRUE);
    }

    if (retVal == BSP_SOK)
    {
        clientInfo.cbFxn        = &vpsCoreDssWbDispcCb;
        clientInfo.arg          = pathObj;
        clientInfo.clientMode   = corePrms->wbMode;
        pathObj->dcHandle = Vpscore_dctrlRegisterClient(
            pathObj->dcNode,
            &clientInfo,
            NULL);
        if (pathObj->dcHandle == NULL)
        {
            GT_1trace(
                VpsDssCoreTrace, GT_ERR,
                "Display Controller registration failed for dss \
                  Wb core instance %d \r\n",
                index);
            retVal = BSP_EALLOC;
        }
        else
        {
            /* This is to clear the Error(overflow & Incomplete) count */
            Vpscore_dctrlClrErrorCount(pathObj->dcHandle);
        }
    }

    if (retVal != BSP_SOK)
    {
        /* Free previously allocated memory*/
        if (pathObj != NULL)
        {
            if (pathObj->dcHandle != NULL)
            {
                Vpscore_dctrlUnRegisterClient(pathObj->dcHandle);
            }
            handleId = (pathObj->handleId - VPS_DSS_DISPC_PIPE_WB);
            retVal   = BspUtils_free(&VcoreDssWbPathObjPoolParams,
                                     (const void *) pathObj,
                                     VpsDssCoreTrace);
            pDssWbInstObj->pathObjPool[handleId] = NULL;
        }
        pathObj = NULL;
    }
    return pathObj;
}

Int32 VpsCore_dssWbClose(VpsCore_Handle pathHandle)
{
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbObj     *pDssWbInstObj;
    UInt32 handleId = 0;

    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj       = (VpsCore_DssWbPathObj *) pathHandle;
    pDssWbInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssWbInstObj));

    BspOsal_semDelete(&(pathObj->pipeDisableSem));
    Vpscore_dctrlUnRegisterClient(pathObj->dcHandle);

    handleId = (pathObj->handleId - VPS_DSS_DISPC_PIPE_WB);
    BspUtils_free(&VcoreDssWbPathObjPoolParams,
                  (const void *) pathObj,
                  VpsDssCoreTrace);
    pDssWbInstObj->pathObjPool[handleId] = NULL;

    return BSP_SOK;
}

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
static UInt32 VpsCore_convertWbInNodetoOvlyIndex(UInt32 wbInNode)
{
    UInt32 ovlyIdx;

    if (wbInNode == VPS_DSS_DISPC_WB_IN_NODE_LCD1)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD1;
    }
    else if (wbInNode == VPS_DSS_DISPC_WB_IN_NODE_LCD2)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD2;
    }
    else if (wbInNode == VPS_DSS_DISPC_WB_IN_NODE_LCD3)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD3;
    }
    else if (wbInNode == VPS_DSS_DISPC_WB_IN_NODE_TV)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_HDMI;
    }
    else
    {
        ovlyIdx = VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX;
    }

    return ovlyIdx;
}
#endif

Int32 VpsCore_dssWbPathSetConfig(VpsCore_Handle pathHandle,
                                 const void    *params,
                                 void          *retPrms)
{
    VpsCore_DssWbPathObj          *pathObj =
        (VpsCore_DssWbPathObj *) pathHandle;
    Int32 retVal = BSP_SOK;
    const VpsCore_DispDssWbParams *pathCfg =
        (const VpsCore_DispDssWbParams *) params;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (NULL != params));

    /* Validate the DssParams */
    retVal = VpsCore_dssValidateDssWbParams(pathCfg, pathObj);
    if (BSP_SOK == retVal)
    {
        /* Copy the Writeback parameters into the path handle. */
        if ((Int32) TRUE == VpsCore_isWbPipeline(pathObj))
        {
            retVal = VpsCore_dssWbPathCopyConfig(pathObj, pathCfg);
        }
        else
        {
            retVal = BSP_EBADARGS;
        }
    }

    /* pathObj->pipeHandle should be opened in core open only */
    if (BSP_SOK == retVal)
    {
        if ((Int32) TRUE == VpsCore_isWbPipeline(pathObj))
        {
            retVal = VpsHal_dssConfWbPipe(pathObj->pipeHandle,
                                          &pathObj->wbPipeCfg);
        }
        else
        {
            retVal = BSP_EBADARGS;
        }
    }

    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_dssConfAdvDma(pathObj->pipeHandle,
                                      &pathObj->halAdvDmaCfg);
    }

    if (BSP_SOK == retVal)
    {
        if (pathObj->wbPipeCfg.wbMode == VPS_DSS_DISPC_WB_CAPT)
        {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VpsHal_Handle ovlyHalHandle;
            UInt32        ovlyIdx;
            UInt32        wbDelayCnt;
            VpsHal_DssDispcLcdBlankTimingParam lcdBlankTimingParm;
#endif
            VpsCore_dctrlPipeUpdateOverlayNode(pathObj->dcHandle,
                                               pathObj->wbPipeCfg.inNode);
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
            /* For capture writeback mode configure the WBDELAYCNT to (VFP - 1U)
             * value of the connected overlay node when writeback is from LCD.
             * WBDELAYCNT should be configured to 0 for writeback from HDMI
             * overlay.
             * WBDELAYCNT configuration is not applicable for TDA3xx.
             */
            ovlyIdx =
                VpsCore_convertWbInNodetoOvlyIndex(pathObj->wbPipeCfg.inNode);
            if (ovlyIdx != VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
            {
                if (ovlyIdx == VPSHAL_DSS_DISPC_HDMI)
                {
                    wbDelayCnt = 0U;
                }
                else
                {
                    ovlyHalHandle = VpsLib_getDssOvlyHalHandle(ovlyIdx);
                    VpsHal_dssOvlyLcdGetBlankTiming(ovlyHalHandle,
                                                    &lcdBlankTimingParm);
                    wbDelayCnt = lcdBlankTimingParm.vFrontPorch - 1U;
                }
                VpsHal_dssConfWbDelayCnt(pathObj->pipeHandle, wbDelayCnt);
            }
#endif
        }
        else
        {
            /* In m2m Mode WB node acts as Dummy Ovly node */
            VpsCore_dctrlPipeUpdateOverlayNode(pathObj->dcHandle,
                                            VPSCORE_DCTRL_NODE_WB);
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
            /* For m2m writeback mode configure the WBDELAYCNT to 0U. */
            VpsHal_dssConfWbDelayCnt(pathObj->pipeHandle, 0U);
#endif
        }
    }

    return retVal;
}

Int32 VpsCore_dssWbStart(VpsCore_Handle pathHandle)
{
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbObj     *pDssInstObj;
    Int32 retVal = BSP_SOK;
    VpsCore_Frame       **programedFrame;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssWbPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));

    /* Reset all the frame pointers to NULL */
    pathObj->curFrame  = NULL;
    pathObj->progFrame = NULL;

    programedFrame = &(pathObj->progFrame);

    /* stream ID and Channel Id is Zero Here */
    *programedFrame = pathObj->reqFrmCb(pathObj->drvData, 0, 0);

    /* Driver should always give the buffers when requested */
    GT_assert(VpsDssCoreTrace, (*programedFrame != NULL));

    /*TODO - Error handling when frame is null*/
    retVal += VpsHal_dssVidPipeSetBufAddr(
        pathObj->pipeHandle,
        0,
        (UInt32) (*programedFrame)->addr[0][0],
        (UInt32) (*programedFrame)->addr[0][1]);

    if (pathObj->outScanFormat == FVID2_SF_INTERLACED)
    {
        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            (UInt32) 1U,
            (UInt32) (*programedFrame)->addr[1][0],
            (UInt32) (*programedFrame)->addr[1][1]);
    }

#if defined (SOC_TDA3XX)
        /* For tda3xx clear region based bit
        * If region based to be enabled its already done in set config
        * Update the region based bit status maintained in path object. */
        if (pathObj->wbPipeCfg.cropEnable == TRUE)
        {
            pathObj->regionBasedBit = 1;
        }
#endif
    if (retVal == BSP_SOK)
    {
        retVal = VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) TRUE);
    }

    if (retVal == BSP_SOK)
    {
        retVal = Vpscore_dctrlStartClient(pathObj->dcHandle);
    }

    if (retVal == BSP_SOK)
    {
        pathObj->isStarted = TRUE;
        pathObj->pipeDisableStatus = VPSCORE_DSSWB_PIPE_RUNNING;
    }
    else
    {
        /* TODO - Check if you need this */
        Vpscore_dctrlStopClient(pathObj->dcHandle);
        VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) FALSE);
    }

    return retVal;
}

Int32 VpsCore_dssWbStop(VpsCore_Handle pathHandle)
{
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbObj     *pDssInstObj;
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssWbPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));
    if (pathObj->wbPipeCfg.cropEnable == TRUE)
    {
        pathObj->pipeDisableStatus = VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_3;
    }
    else
    {
        retVal = VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) FALSE);
        pathObj->pipeDisableStatus = VPSCORE_DSSWB_PIPE_DISABLE_INITIATED;
    }
    /* Wait required only for WB capture */
    if (pathObj->wbPipeCfg.wbMode == VPS_DSS_DISPC_WB_CAPT)
    {
        BspOsal_semWait(pathObj->pipeDisableSem, BSP_OSAL_WAIT_FOREVER);
    }
    if (retVal == BSP_SOK)
    {
        pathObj->isStarted = FALSE;

        /* Reset all the frame pointers to NULL */
        pathObj->curFrame  = NULL;
        pathObj->progFrame = NULL;

        retVal = Vpscore_dctrlStopClient(pathObj->dcHandle);
    }
    return retVal;
}

/* Sequence that is followed in the ISR.
 * 1. Give back the current frame to driver if its not NULL.
 * 2. Move programmed Frame to current frame.
 * 3. Get next Frame from the driver, program this into programmed frame.
 * 4. Update the registers with address of program frame.
 * 5. Set Go bit of the corresponding Overlay Manager.
 */
Int32 VpsCore_dssWbIsr(VpsCore_Handle pathHandle, UInt32 chId)
{
    VpsCore_DssWbPathObj  *pathObj = (VpsCore_DssWbPathObj *) pathHandle;
    Int32 retVal = BSP_SOK;
    UInt32 cookie;
    Vps_DssDispcWbRtParams *rtParams = NULL;
    if (pathObj->isStarted == TRUE)
    {
        cookie = BspOsal_disableInterrupt();
        if (pathObj->wbPipeCfg.wbMode == VPS_DSS_DISPC_WB_CAPT)
        {
            if (pathObj->curFrame != NULL)
            {
                pathObj->frmDoneCb(pathObj->drvData, pathObj->curFrame);
            }
            pathObj->curFrame = pathObj->progFrame;

            pathObj->progFrame = pathObj->reqFrmCb(pathObj->drvData, 0, 0);
            /* Driver should always give the buffers when requested */
            /* Driver should give both the fields in single call for Interlaced
             * display */
            GT_assert(VpsDssCoreTrace, (pathObj->progFrame != NULL));

            if (pathObj->progFrame->rtParams != NULL)
            {
                rtParams = (Vps_DssDispcWbRtParams *) pathObj->progFrame->rtParams;

                pathObj->wbPipeCfg.inHeight      = rtParams->inHeight;
                pathObj->wbPipeCfg.inWidth       = rtParams->inWidth;
                pathObj->wbPipeCfg.outFmt.width  = rtParams->outWidth;
                pathObj->wbPipeCfg.outFmt.height = rtParams->outHeight;
                pathObj->wbPipeCfg.inPosX        = rtParams->inPosX;
                pathObj->wbPipeCfg.inPosY        = rtParams->inPosY;

                retVal += VpsHal_dssConfWbPipe(pathObj->pipeHandle,
                                               &pathObj->wbPipeCfg);
            }
            /*TODO - Error handling when frame is null*/
            retVal += VpsHal_dssVidPipeSetBufAddr(
                pathObj->pipeHandle,
                0,
                (UInt32) pathObj->progFrame->addr[0][0],
                (UInt32) pathObj->progFrame->addr[0][1]);

            if (pathObj->outScanFormat == FVID2_SF_INTERLACED)
            {
                retVal += VpsHal_dssVidPipeSetBufAddr(
                    pathObj->pipeHandle,
                    (UInt32) 1U,
                    (UInt32) pathObj->progFrame->addr[1][0],
                    (UInt32) pathObj->progFrame->addr[1][1]);
            }

            /* In case of Tda3xx GOLCD bit will be cleared at WBsync Event and not
             * at Vsync event in capture WB mode. Since the WB is cleared at wbsync
             * the updated configuration for Forward Pipeline (video/gfx) will not
             * be updated in next vsync which comes after current wbsync event.
             * To avoid such scenarios GOLCD will be set in WBSYNC event
             * callback as well. */
            if (retVal == BSP_SOK)
            {
                retVal = Vpscore_dctrlReadyToSetGoBit(pathObj->dcHandle);
            }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
            /* In case of TDA2XX there is WBGO bit which should be set for
             * shadow to work copy for WB registers.*/
            if (retVal == BSP_SOK)
            {
                retVal = VpsHal_dssWbSetGoBit(pathObj->pipeHandle);
            }
#endif
        }
        else
        {
            /* M2M mode - programmed frame is the current frame and no
             * further processing is required */
            if (pathObj->progFrame != NULL)
            {
                pathObj->frmDoneCb(pathObj->drvData, pathObj->progFrame);
            }
        }
        BspOsal_restoreInterrupt(cookie);
    }

    return retVal;
}

static Int32 VpsCore_dssWbPathCopyConfig(VpsCore_DssWbPathObj          *pathObj,
                                         const VpsCore_DispDssWbParams *pathCfg)
{
    Int32 retVal = BSP_SOK;

    VpsHal_dssWbAdvDmaConfigInit(&pathObj->halAdvDmaCfg);

    VpsHal_dssWbPipeCfgInit(&pathObj->wbPipeCfg);

    pathObj->wbPipeCfg.inHeight     = pathCfg->inHeight;
    pathObj->wbPipeCfg.inWidth      = pathCfg->inWidth;
    pathObj->wbPipeCfg.inPosX       = pathCfg->inPosX;
    pathObj->wbPipeCfg.inPosY       = pathCfg->inPosY;
    pathObj->outScanFormat          = pathCfg->outFmt.scanFormat;
    pathObj->wbPipeCfg.inDataFormat = pathCfg->indataFormat;
    pathObj->wbPipeCfg.inNode       = pathCfg->inNode;
    pathObj->wbPipeCfg.wbMode       = pathCfg->wbMode;

    pathObj->wbPipeCfg.inSourceHeight= pathCfg->sourceHeight;
    pathObj->wbPipeCfg.inSourceWidth = pathCfg->sourceWidth;

    /* Only Field merge of plane 1 is considered here, as DSS WB doesn't
     * support different options for different planes */
    pathObj->isFieldMergeBuff = pathCfg->outFmt.fieldMerged[0];
    pathObj->currentFieldVal  = FVID2_FID_BOTTOM;
    pathObj->fieldsCaptured   = VPSCORE_DSSWB_CAPTURE_NOT_STARTED;

    BspUtils_memcpy(
        &pathObj->wbPipeCfg.outFmt,
        &pathCfg->outFmt,
        sizeof (Fvid2_Format));

    /* In case of Interlaced output, in Height and out Height should be devided
     * by 2 to make it field height. PosY should be divided by to 2 to make it
     * relative position in field. */
    if (pathObj->outScanFormat == FVID2_SF_INTERLACED)
    {
        pathObj->wbPipeCfg.inHeight      /= 2U;
        pathObj->wbPipeCfg.outFmt.height /= 2U;
        pathObj->wbPipeCfg.inPosY        /= 2U;
    }

    if (retVal == BSP_SOK)
    {
        if ((Int32) TRUE == Fvid2_isDataFmtYuv422I(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 2U)) + 1U;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtSemiPlanar(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width)) + 1U;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb16bit(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 2U)) + 1U;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb24bit(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 3U)) + 1U;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb32bit(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 4U)) + 1U;
        }
        else
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Un supported data format \r\n");
            retVal = BSP_EINVALID_PARAMS;
        }

#if defined (SOC_TDA3XX)
        if (pathObj->halAdvDmaCfg.rowInc != 1)
        {
            GT_0trace(VpsDssCoreTrace, GT_ERR,
                      "Bigger Pitch is not supported for Tda3xx platform \r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
#endif

        /* For interlaced buffers we need to skip one line */
        if ((pathObj->outScanFormat == FVID2_SF_INTERLACED) &&
            (pathObj->isFieldMergeBuff == TRUE))
        {
            pathObj->halAdvDmaCfg.rowInc += pathObj->wbPipeCfg.outFmt.pitch[0];
        }

        pathObj->wbPipeCfg.cscFullRngEnable =
            pathCfg->wbCfg.pipeCfg.cscFullRngEnable;
        pathObj->wbPipeCfg.scEnable =
            pathCfg->wbCfg.pipeCfg.scEnable;
        pathObj->wbPipeCfg.cropEnable = pathCfg->wbCfg.pipeCfg.cropEnable;

        if (pathCfg->wbCfg.advDmaCfg != NULL)
        {
            pathObj->halAdvDmaCfg.burstSize =
                pathCfg->wbCfg.advDmaCfg->burstSize;
            pathObj->halAdvDmaCfg.burstType =
                pathCfg->wbCfg.advDmaCfg->burstType;
            pathObj->halAdvDmaCfg.bufPreloadType =
                pathCfg->wbCfg.advDmaCfg->bufPreloadType;
            pathObj->halAdvDmaCfg.bufHighThreshold =
                pathCfg->wbCfg.advDmaCfg->bufHighThreshold;
            pathObj->halAdvDmaCfg.bufLowThreshold =
                pathCfg->wbCfg.advDmaCfg->bufLowThreshold;
            pathObj->halAdvDmaCfg.selfRefreshEnable =
                pathCfg->wbCfg.advDmaCfg->selfRefreshEnable;
            pathObj->halAdvDmaCfg.arbitration =
                pathCfg->wbCfg.advDmaCfg->arbitration;
            pathObj->halAdvDmaCfg.pixelInc =
                pathCfg->wbCfg.advDmaCfg->pixelInc;
            pathObj->halAdvDmaCfg.idleSize =
                pathCfg->wbCfg.advDmaCfg->idleSize;
            pathObj->halAdvDmaCfg.idleNumber =
                pathCfg->wbCfg.advDmaCfg->idleNumber;
        }
    }
    return retVal;
}

static Int32 VpsCore_isWbPipeline(const VpsCore_DssWbPathObj *pathObj)
{
    Int32 retVal = (Int32) FALSE;

    if (pathObj->handleId == VPS_DSS_DISPC_PIPE_WB)
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static Int32 VpsCore_dssValidateDssWbParams(
    const VpsCore_DispDssWbParams *pathCfg,
    const VpsCore_DssWbPathObj    *
    pathObj)
{
    Int32 retVal = BSP_SOK;

    /* Memory type */
    if (pathCfg->memType == VPS_VPDMA_MT_TILEDMEM)
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Tiled memory not supported \r\n");
        retVal = BSP_EINVALID_PARAMS;
    }

    if (((pathCfg->inHeight * 8) <
         (pathCfg->outFmt.height)) ||
        ((pathCfg->inWidth * 8) < (pathCfg->outFmt.width)))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Upscaling of greater than 8x is not supported \r\n");
        retVal = BSP_EINVALID_PARAMS;
    }

    if ((Int32) TRUE == Fvid2_isDataFmtYuv(pathCfg->outFmt.dataFormat))
    {
        if (((pathCfg->inHeight) >
             (pathCfg->outFmt.height * 2)) ||
            ((pathCfg->inWidth) > (pathCfg->outFmt.width * 2)))
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Downscaling of greater than 1/2x is not supported \r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else
    {
        if (((pathCfg->inHeight) >
             (pathCfg->outFmt.height * 4)) ||
            ((pathCfg->inWidth) > (pathCfg->outFmt.width * 4)))
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Downscaling of greater than 1/4x is not supported \r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    if ((pathCfg->inHeight != pathCfg->outFmt.height) ||
        (pathCfg->inWidth != pathCfg->outFmt.width))
    {
        if (pathCfg->wbCfg.pipeCfg.scEnable == FALSE)
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Scaling should be enabled\r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    if ((pathCfg->sourceHeight != pathCfg->inHeight) ||
        (pathCfg->sourceWidth != pathCfg->inWidth))
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Crop not supported for tda2xx platform\r\n");
        retVal = BSP_EINVALID_PARAMS;
#else
        if (pathCfg->wbCfg.pipeCfg.cropEnable == FALSE)
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Crop (Region based writeback) should be enabled\r\n");
            retVal = BSP_EINVALID_PARAMS;
        }
#endif
    }
    if (((pathCfg->inHeight + pathCfg->inPosY) > pathCfg->sourceHeight) ||
        ((pathCfg->inWidth + pathCfg->inPosX) > pathCfg->sourceWidth))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "WB Input width+posx/height+posy > Overlay width /height");
        retVal = BSP_EINVALID_PARAMS;
    }
    if (pathCfg->wbMode == VPS_DSS_DISPC_WB_CAPT)
    {
        if ((pathCfg->inNode == VPS_DSS_DISPC_WB_IN_NODE_VID1) ||
            (pathCfg->inNode == VPS_DSS_DISPC_WB_IN_NODE_VID2) ||
            (pathCfg->inNode == VPS_DSS_DISPC_WB_IN_NODE_VID3) ||
            (pathCfg->inNode == VPS_DSS_DISPC_WB_IN_NODE_GFX))
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Capture WB from VID/GFX pipe not supported");
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    return retVal;
}

