/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file IssIntf_simcop.c
 *
 *  \brief Simcop LDC And VTNF M2M application.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <Loopback_main.h>
#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgsimcop.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MESH_TABLE_PITCH         (1984U)

#define OB_WIDTH                 (32U)
#define OB_HEIGHT                (40U)

#define LDC_PIX_PAD              (2U)
#define LDC_PIX_PAD              (2U)
#define LDC_INTERPOLATION_METHOD (VPS_ISS_LDC_LUMA_INTRP_BICUBIC)
/* VPS_ISS_LDC_LUMA_INTRP_BILINEAR */

#define SIMCOP_MODE             (VPS_ISS_SIMCOP_LDC_VTNF)
/*#define SIMCOP_MODE             (VPS_ISS_SIMCOP_VTNF)*/

#define APP_REP_COUNT           (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Application Object containing all the parameters
 */
typedef struct
{
    Fvid2_Handle             drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams           cbPrms;
    /**< Callback params. */

    Vps_M2mIntfCreateParams  createPrms;
    /**< Create Parameters */
    Vps_M2mIntfCreateStatus  createStatusPrms;
    /**< Create Status Parameters */

    Fvid2_Format             meshTableFmt;
    /**< Used for allocating frame for the mesh table */
    vpsissSimcopOpenParams_t simcopCoreOpenParams;
    vpsissSimcopCfgPrms_t    simcopCfgPrms;
    vpsissldcConfig_t        ldcCfg;
    vpsissvtnfConfig_t       vtnfCfg;

    Fvid2_FrameList          inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList          outFrmList;
    /**< Output Frames List */

    Fvid2_Frame              meshTableFrame;
    /**< Frame for storing Mesh Table */

    Semaphore_Handle         waitForCompl;
    /* Semaphore for waiting for completion */
} LpbkApp_m2mSimcopObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 LpbkApp_m2mSimcopOpenDriver(LpbkApp_m2mSimcopObj *pAppObj);
static Int32 LpbkApp_m2mSimcopAllocFrames(LpbkApp_m2mSimcopObj *pAppObj);
static Int32 LpbkApp_m2mSimcopCloseDriver(LpbkApp_m2mSimcopObj *pAppObj);
static Int32 LpbkApp_m2mSimcopSetParams(
    LpbkApp_m2mSimcopObj *pAppObj,
    LpbkApp_testCfg      *testCfg);

static Int32 LpbkApp_m2mSimcopCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

LpbkApp_m2mSimcopObj gLpbkAppSimcopObj;

#define VTNF_BYPASS
#ifdef VTNF_BYPASS
vpsissvtnfConfig_t   gLpbkAppVtnfCfg =
{
    FVID2_DF_YUV420SP_UV,          /* outDataFormat */
    TRUE,                          /* isAdvCfgValid */
    {
        OB_WIDTH,                  /* blockWidth */
        OB_HEIGHT,                 /* blockHeight */
        3,                         /* roundBitCount */
        0,                         /* colorWeight1 */
        0,                         /* colorWeight2 */
        {                          /* lut1[ISSHAL_VTNF_LUT_SIZE] */
            0, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24, 16,
            8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {   /* lut2[ISSHAL_VTNF_LUT_SIZE] */
            0, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24, 16,
            8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        ISSHAL_VTNF_TRG_SRC_HWSEQ, /* triggerSource */
        TRUE                       /* intrEnable */
    }
};
#else
vpsissvtnfConfig_t   gLpbkAppVtnfCfg =
{
    FVID2_DF_YUV420SP_UV,          /* outDataFormat */
    TRUE,                          /* isAdvCfgValid */
    {
        OB_WIDTH,                  /* blockWidth */
        OB_HEIGHT,                 /* blockHeight */
        5,                         /* roundBitCount */
        4,                         /* colorWeight1 */
        4,                         /* colorWeight2 */
        {                          /* lut1[ISSHAL_VTNF_LUT_SIZE] */
            192, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24,
            16,
            8,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {   /* lut2[ISSHAL_VTNF_LUT_SIZE] */
            192, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24,
            16,
            8,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        ISSHAL_VTNF_TRG_SRC_HWSEQ,  /* triggerSource */
        TRUE                        /* intrEnable */
    }
};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  LpbkApp_m2mSimcopCreate
 *  Application test task.
 */
void LpbkApp_m2mSimcopCreate(LpbkApp_testCfg *testCfg)
{
    Int32 status = FVID2_SOK;
    Semaphore_Params semPrms;

    /* Create semaphore */
    Semaphore_Params_init(&semPrms);
    gLpbkAppSimcopObj.waitForCompl = Semaphore_create(0U, &semPrms, NULL);
    if (NULL == gLpbkAppSimcopObj.waitForCompl)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        status = FVID2_EFAIL;
    }

    status = LpbkApp_m2mSimcopOpenDriver(&gLpbkAppSimcopObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
    }

    status = LpbkApp_m2mSimcopSetParams(&gLpbkAppSimcopObj, testCfg);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Seting Driver Parameters\r\n");
        LpbkApp_m2mSimcopCloseDriver(&gLpbkAppSimcopObj);
        return;
    }

    status = LpbkApp_m2mSimcopAllocFrames(&gLpbkAppSimcopObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error in Allocating Buffers \r\n");
        LpbkApp_m2mSimcopCloseDriver(&gLpbkAppSimcopObj);
        return;
    }

    return;
}

void LpbkApp_m2mSimcopClose(void)
{
    Int32 status = FVID2_SOK;

    status = LpbkApp_m2mSimcopCloseDriver(&gLpbkAppSimcopObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
    }

    Semaphore_delete(&gLpbkAppSimcopObj.waitForCompl);
}

void LpbkApp_m2mSimcopProcessFrame(
    Fvid2_Frame *inpFrm,
    Fvid2_Frame *prevFrm,
    Fvid2_Frame *outFrm)
{
    Int32  status = FVID2_SOK;
    UInt32 cnt;

    for (cnt = 0U; cnt < APP_REP_COUNT; cnt++)
    {
        Fvid2FrameList_init(&gLpbkAppSimcopObj.inFrmList);
        Fvid2FrameList_init(&gLpbkAppSimcopObj.outFrmList);

        /* Make input and output frames list */
        gLpbkAppSimcopObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_CUR_FRAME] =
            inpFrm;
        gLpbkAppSimcopObj.outFrmList.frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME] =
            outFrm;
        gLpbkAppSimcopObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_MESH_TABLE] =
            &gLpbkAppSimcopObj.meshTableFrame;
        gLpbkAppSimcopObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME] =
            prevFrm;

        gLpbkAppSimcopObj.inFrmList.numFrames  = VPS_SIMCOP_STREAM_ID_MAX + 1;
        gLpbkAppSimcopObj.outFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;

        /* Submit Processing Request to the driver */
        status = Fvid2_processRequest(
            gLpbkAppSimcopObj.drvHandle,
            &gLpbkAppSimcopObj.inFrmList,
            &gLpbkAppSimcopObj.outFrmList);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Submitting request \r\n");
            LpbkApp_m2mSimcopCloseDriver(&gLpbkAppSimcopObj);
            return;
        }

        /* Wait for test to complete */
        Semaphore_pend(gLpbkAppSimcopObj.waitForCompl, BIOS_WAIT_FOREVER);

        /* Submit Processing Request to the driver */
        status = Fvid2_getProcessedRequest(
            gLpbkAppSimcopObj.drvHandle,
            &gLpbkAppSimcopObj.inFrmList,
            &gLpbkAppSimcopObj.outFrmList,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Getting completed Request\r\n");
            LpbkApp_m2mSimcopCloseDriver(&gLpbkAppSimcopObj);
            return;
        }
    }
}

static Int32 LpbkApp_m2mSimcopCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved)
{
    LpbkApp_m2mSimcopObj *pAppObj = (LpbkApp_m2mSimcopObj *) appData;

    if (NULL == handle)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Handle is null in isr !!\r\n");
    }
    if (NULL == pAppObj)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Object is null in isr !!\r\n");
    }
    else
    {
        /* Mark Frame As completed */
        Semaphore_post(pAppObj->waitForCompl);
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mSimcopAllocFrames(LpbkApp_m2mSimcopObj *pAppObj)
{
    Int32 status = FVID2_SOK;

    /* Allocate the Buffer for the Mesh Table */
    status = BspUtils_memFrameAlloc(
        &pAppObj->meshTableFmt,
        &pAppObj->meshTableFrame,
        1U);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Mesh Table Alloc Failed!!!\r\n");
        return (status);
    }

    BspUtils_memset(
        pAppObj->meshTableFrame.addr[0U][0U],
        0x0,
        pAppObj->meshTableFmt.pitch[0U] * pAppObj->meshTableFmt.height);

    return (status);
}

static Int32 LpbkApp_m2mSimcopOpenDriver(LpbkApp_m2mSimcopObj *pAppObj)
{
    Fvid2CbParams_init(&pAppObj->cbPrms);
    pAppObj->cbPrms.cbFxn   = LpbkApp_m2mSimcopCallback;
    pAppObj->cbPrms.appData = pAppObj;

    Fvid2Format_init(&pAppObj->meshTableFmt);
    pAppObj->meshTableFmt.width      = MESH_TABLE_PITCH;
    pAppObj->meshTableFmt.height     = 1080;
    pAppObj->meshTableFmt.pitch[0U]  = MESH_TABLE_PITCH;
    pAppObj->meshTableFmt.bpp        = FVID2_BPP_BITS8;
    pAppObj->meshTableFmt.dataFormat = FVID2_DF_YUV422I_YUYV;

    VpsM2mIntfCreateParams_init(&pAppObj->createPrms);

    pAppObj->createPrms.numCh           = 1U;
    pAppObj->createPrms.chInQueueLength = 1U;
    pAppObj->createPrms.maxStatsInst    = 0U;
    pAppObj->createPrms.frmStats        = NULL;
    pAppObj->createPrms.pAdditionalArgs = (Ptr) & pAppObj->simcopCoreOpenParams;

    VpsM2mIntfCreateStatus_init(&pAppObj->createStatusPrms);

    pAppObj->simcopCoreOpenParams.mode = SIMCOP_MODE;
    pAppObj->simcopCoreOpenParams.arg  = NULL; /* Reserved */

    pAppObj->drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_SIMCOP,
        &pAppObj->createPrms,
        &pAppObj->createStatusPrms,
        &pAppObj->cbPrms);
    if (NULL == pAppObj->drvHandle)
    {
        Bsp_printf("M2mSimcopLdcVtnfApp: Could not open driver for P1\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mSimcopCloseDriver(LpbkApp_m2mSimcopObj *pAppObj)
{
    Int32 status = FVID2_SOK;

    status = BspUtils_memFrameFree(
        &pAppObj->meshTableFmt,
        &pAppObj->meshTableFrame,
        1U);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Mesh Table Frame Free Failed!!!\r\n");
    }

    if (NULL != pAppObj->drvHandle)
    {
        Fvid2_delete(pAppObj->drvHandle, NULL);
        pAppObj->drvHandle = NULL;
    }

    return 0;
}

static Int32 LpbkApp_m2mSimcopSetParams(
    LpbkApp_m2mSimcopObj *pAppObj,
    LpbkApp_testCfg      *testCfg)
{
    Int32 status;
    vpsissldcConfig_t  *pLdcCfg;
    vpsissldcPerspectiveTransformCfg_t *pLdcPTxCfg;
    vpsissldcLutCfg_t  *pLdcLutCfg;

    vpsissvtnfConfig_t *pVtnfCfg;

    /* Set the Params */

    /* SIMCOP Configuration */
    pAppObj->simcopCfgPrms.inpFrmPitch   = testCfg->outPitch;
    pAppObj->simcopCfgPrms.prevFrmPitch  = testCfg->outPitch;
    pAppObj->simcopCfgPrms.outFrmPitch   = testCfg->outPitch;
    pAppObj->simcopCfgPrms.inFrameWidth  = testCfg->outWidth;
    pAppObj->simcopCfgPrms.inFrameHeight = testCfg->outHeight;
    pAppObj->simcopCfgPrms.blkWidth      = OB_WIDTH;
    pAppObj->simcopCfgPrms.blkHeight     = OB_HEIGHT;

    /* LDC Configuration */
    pLdcCfg       = &(pAppObj->simcopCfgPrms.ldcCfg);
    pLdcCfg->mode = VPS_ISS_LDC_MODE_YUV420_LDC;
    pLdcCfg->bayerDataFormat =
        VPS_ISS_LDC_BAYER_DATA_FORMAT_UNPACKED_12BIT;
    pLdcCfg->enableBackMapping         = TRUE;
    pLdcCfg->advCfg.enableCircAddrMode = FALSE;
    pLdcCfg->advCfg.circBuffSize       = 0x0;
    pLdcCfg->advCfg.enableConstOutAddr = TRUE;
    pLdcCfg->lumeIntrType             = LDC_INTERPOLATION_METHOD;
    pLdcCfg->bayerInitColor           = VPS_ISS_LDC_BAYER_INIT_COLOR_R;
    pLdcCfg->inputFrameWidth          = testCfg->outWidth;
    pLdcCfg->inputFrameHeight         = testCfg->outHeight;
    pLdcCfg->advCfg.outputBlockWidth  = OB_WIDTH;
    pLdcCfg->advCfg.outputBlockHeight = OB_HEIGHT;
    pLdcCfg->advCfg.outputFrameWidth  = testCfg->outWidth;
    pLdcCfg->advCfg.outputFrameHeight = testCfg->outHeight;
    pLdcCfg->isAdvCfgValid            = TRUE;
    pLdcCfg->advCfg.outputStartX      = 0x0;
    pLdcCfg->advCfg.outputStartY      = 0x0;
    pLdcCfg->pixelPad = LDC_PIX_PAD;

    pLdcPTxCfg = &(pLdcCfg->perspTrnsformCfg);
    pLdcPTxCfg->enableWarp      = FALSE;
    pLdcPTxCfg->enableExpandFmt = FALSE;
    pLdcPTxCfg->coeffA          = 4096U;
    pLdcPTxCfg->coeffB          = 0U;
    pLdcPTxCfg->coeffC          = 0U;
    pLdcPTxCfg->coeffD          = 0U;
    pLdcPTxCfg->coeffE          = 4096U;
    pLdcPTxCfg->coeffF          = 0U;
    pLdcPTxCfg->coeffG          = 0U;
    pLdcPTxCfg->coeffH          = 0U;

    pLdcLutCfg          = &(pLdcCfg->lutCfg);
    pLdcLutCfg->address =
        (uint32_t) pAppObj->meshTableFrame.addr[0][0];
    pLdcLutCfg->lineOffset      = MESH_TABLE_PITCH;
    pLdcLutCfg->downScaleFactor = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4;

    /* VTNF Configuration */
    pVtnfCfg = &(pAppObj->simcopCfgPrms.vtnfCfg);
    BspUtils_memcpy(pVtnfCfg, &gLpbkAppVtnfCfg, sizeof (vpsissvtnfConfig_t));
    pVtnfCfg->outDataFormat        = testCfg->outDataFormat;
    pVtnfCfg->advCfg.triggerSource = ISSHAL_VTNF_TRG_SRC_HWSEQ;
    pVtnfCfg->advCfg.blockWidth    = OB_WIDTH;
    pVtnfCfg->advCfg.blockHeight   = OB_HEIGHT;
    pVtnfCfg->advCfg.intrEnable    = TRUE;

    status = Fvid2_control(
        pAppObj->drvHandle,
        IOCTL_VPS_SIMCOP_M2M_SET_PARAMS,
        &pAppObj->simcopCfgPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("M2mSimcopLdcVtnfApp: SetParams Failed for P1\r\n");
        return -1;
    }

    return (status);
}

