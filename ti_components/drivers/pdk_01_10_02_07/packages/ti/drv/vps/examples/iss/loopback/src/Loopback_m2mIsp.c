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
 *  \file M2mIssWdrScale_main.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <Loopback_main.h>
#include <white_balance.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Application Object containing all the parameters
 */
typedef struct
{
    Fvid2_Handle               drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams             cbPrms;
    /**< Callback params. */

    Vps_M2mIntfCreateParams    createPrms;
    /**< Create Parameters */
    Vps_M2mIntfCreateStatus    createStatusPrms;
    /**< Create Status Parameters */

    vpsissIspParams_t          ispPrms;
    /**< isp parameters */

    vpsissIspOpenParams_t      openPrms;
    /**< Core Open Parameters */
    vpsissIspOpenRetParams_t   retPrms;
    /**< Core Returns Parameters */
    Vps_M2mIntfStats           stats;

    vpsissRszCtrl_t            rszCtrl;
    /**< Resizer Control structure containing pointer to the
     *   resizer configuration */
    vpsissRszCfg_t             rszCfg;
    /**< Resizer configuration */

    vpsissIpipeCtrl_t          ipipeCtrl;
    vpsissIpipeInConfig_t      ipipeInputCfg;
    vpsissIpipeWbConfig_t      wbCfg;
    vpsissIpipeRgb2RgbConfig_t rgb2rgbCfg;

    vpsissIsif2DLscConfig_t    isifLscCfg;
    /**< ISIF LSC Configuration */
    vpsissIsifCtrl_t           isifCtrl;
    /**< ISIF Control structure containing pointer to the
     *   ISIF configuration */

    Fvid2_Frame                frames[2];

    /**< Array of FVID Frames */
    Fvid2_FrameList            inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList            outFrmList;
    /**< Output Frames List */

    Vps_M2mIntfStatsParams     statsPrms;
    /**< Statistics parameters */

    vpsissH3aCtrl_t            h3aCtrl;
    vpsissH3aAewbConfig_t      aewbCfg;
    vpsissH3aAfConfig_t        afCfg;

    Image                      image;
    WBParams                   wbParams;
    aewDataEntry               aewb[500];

    UInt32                     frmCnt;

    /* Test complete semaphore used to sync between test task and main task. */
    Semaphore_Handle           waitForCompl;

    Fvid2_Format               inFmt;
    Fvid2_Format               outFmt;
} LpbkApp_m2mIspObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 LpbkApp_m2mIspOpenDriver(LpbkApp_m2mIspObj *appObj);
static Int32 LpbkApp_m2mIspSetParams(LpbkApp_m2mIspObj *appObj);
static Int32 LpbkApp_m2mIspSetRszConfig(LpbkApp_m2mIspObj *appObj);
static Int32 LpbkApp_m2mIspSetIpipeConfig(LpbkApp_m2mIspObj *appObj);
static Int32 LpbkApp_m2mIspAllocFrames(LpbkApp_m2mIspObj *appObj);
static Int32 LpbkApp_m2mIspCloseDriver(LpbkApp_m2mIspObj *appObj);
static Int32 LpbkApp_m2mIspSetH3aParams(LpbkApp_m2mIspObj *appObj);
static void LpbkApp_m2mIspCreateImageData(LpbkApp_m2mIspObj *appObj);
static void LpbkApp_m2mIspSetAewbGains(LpbkApp_m2mIspObj *appObj);

static Int32 LpbkApp_m2mIspCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved);

extern int WB_estimateIlluminant(Image *imgPtr, float percPix,
                                 Illuminant *Illum);
extern int WB_estimateWbParams(Image *imgPtr, float percPix, WBParams *cP);

static Int32 LpbkApp_m2mIspSetIsifLscConfig(
    LpbkApp_m2mIspObj *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* \brief Global Application Object */
LpbkApp_m2mIspObj gLpbkAppM2mObj;

static vpsissIpipeWbConfig_t gLpbkAppM2mIspWbDefCfg =
{
    {0U,    0U,    0U,    0U   },
    {0x200, 0x200, 0x200, 0x200}
};
static vpsissIpipeRgb2RgbConfig_t gLpbkAppRgb2rgbDefCfg =
{
    {
        #if 0
        {275,  29,   -48},
        {-125, 306,  75 },
        {-32,  -197, 485}
        #endif
        {256,  0,    0  },
        {0,    256,  0  },
        {0,    0,    256}
    },
    {0U,   0U,   0U }
};

volatile UInt32   gIspApplyWbGains = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  LpbkApp_m2mIspCreate
 *  Application test task.
 */
void LpbkApp_m2mIspCreate(LpbkApp_testCfg *testCfg)
{
    Int32 status = FVID2_SOK;
    Semaphore_Params semPrms;

    /* Create semaphore */
    Semaphore_Params_init(&semPrms);
    gLpbkAppM2mObj.waitForCompl = Semaphore_create(0U, &semPrms, NULL);
    if (NULL == gLpbkAppM2mObj.waitForCompl)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        status = FVID2_EFAIL;
    }

    Fvid2Format_init(&gLpbkAppM2mObj.inFmt);
    Fvid2Format_init(&gLpbkAppM2mObj.outFmt);

    /* Copy input and output parameters */
    gLpbkAppM2mObj.inFmt.width      = testCfg->inWidth;
    gLpbkAppM2mObj.inFmt.height     = testCfg->inHeight;
    gLpbkAppM2mObj.inFmt.dataFormat = testCfg->inDataFormat;
    gLpbkAppM2mObj.inFmt.bpp        = testCfg->inBpp;
    gLpbkAppM2mObj.inFmt.pitch[0U]  = testCfg->inPitch;
    gLpbkAppM2mObj.inFmt.pitch[1U]  = testCfg->inPitch;
    gLpbkAppM2mObj.inFmt.pitch[2U]  = testCfg->inPitch;

    gLpbkAppM2mObj.outFmt.width      = testCfg->outWidth;
    gLpbkAppM2mObj.outFmt.height     = testCfg->outHeight;
    gLpbkAppM2mObj.outFmt.dataFormat = testCfg->outDataFormat;
    gLpbkAppM2mObj.outFmt.bpp        = testCfg->outBpp;
    gLpbkAppM2mObj.outFmt.pitch[0U]  = testCfg->outPitch;
    gLpbkAppM2mObj.outFmt.pitch[1U]  = testCfg->outPitch;
    gLpbkAppM2mObj.outFmt.pitch[2U]  = testCfg->outPitch;
    gLpbkAppM2mObj.frmCnt = 0U;

    status = LpbkApp_m2mIspOpenDriver(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
        return;
    }

    status = LpbkApp_m2mIspSetParams(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: SetParams Failed\r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        return;
    }

    status = LpbkApp_m2mIspSetRszConfig(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: Resizer SetConfig Failed\r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        return;
    }

    status = LpbkApp_m2mIspSetIpipeConfig(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: IPIPE SetConfig Failed\r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        return;
    }

    status = LpbkApp_m2mIspSetH3aParams(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Setting H3A Params \r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mIspSetIsifLscConfig(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MIspApp: ISIF SetLscConfig Failed\r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }
    status = LpbkApp_m2mIspAllocFrames(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error in Allocating Buffers \r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        return;
    }
}

void LpbkApp_m2mIspClose(void)
{
    Int32 status = FVID2_SOK;

    status = LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    Semaphore_delete(&gLpbkAppM2mObj.waitForCompl);

    IDH_freeImage(&gLpbkAppM2mObj.image);
}

void LpbkApp_m2mIspProcessFrame(Fvid2_Frame *inpFrm, Fvid2_Frame *outFrm)
{
    Int32 status = FVID2_SOK;

    Fvid2FrameList_init(&gLpbkAppM2mObj.inFrmList);
    Fvid2FrameList_init(&gLpbkAppM2mObj.outFrmList);

    /* Make input and output frames list */
    gLpbkAppM2mObj.inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] = inpFrm;
    /* Always provide number of frames in the frame list to be max
     * streams of isp */
    gLpbkAppM2mObj.inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

    gLpbkAppM2mObj.outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] = outFrm;
    /* Always provide number of frames in the frame list to be max
     * streams of isp */
    gLpbkAppM2mObj.outFrmList.frames[VPS_ISS_STREAM_ID_AEWB] =
        &gLpbkAppM2mObj.frames[0U];
    gLpbkAppM2mObj.outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

    /* Submit Processing Request to the driver */
    status = Fvid2_processRequest(
        gLpbkAppM2mObj.drvHandle,
        &gLpbkAppM2mObj.inFrmList,
        &gLpbkAppM2mObj.outFrmList);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Submitting request \r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        return;
    }

    /* Wait for test to complete */
    Semaphore_pend(gLpbkAppM2mObj.waitForCompl, BIOS_WAIT_FOREVER);

    /* Submit Processing Request to the driver */
    status = Fvid2_getProcessedRequest(
        gLpbkAppM2mObj.drvHandle,
        &gLpbkAppM2mObj.inFrmList,
        &gLpbkAppM2mObj.outFrmList,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Getting completed Request\r\n");
        LpbkApp_m2mIspCloseDriver(&gLpbkAppM2mObj);
        return;
    }

    /* Run AEWB Algorithm */
    LpbkApp_m2mIspCreateImageData(&gLpbkAppM2mObj);
    WB_estimateWbParams(&gLpbkAppM2mObj.image, 8,
                        &gLpbkAppM2mObj.wbParams);

    #if 0
    if ((gLpbkAppM2mObj.frmCnt % 100) == 0)
    {
        printf("Gains %f %f %f\r\n",
               gLpbkAppM2mObj.wbParams.gainOffset.gainFactors[0],
               gLpbkAppM2mObj.wbParams.gainOffset.gainFactors[1],
               gLpbkAppM2mObj.wbParams.gainOffset.gainFactors[2]);
        printf("Offset %f %f %f\r\n",
               gLpbkAppM2mObj.wbParams.gainOffset.offsets[0],
               gLpbkAppM2mObj.wbParams.gainOffset.offsets[1],
               gLpbkAppM2mObj.wbParams.gainOffset.offsets[2]);
    }
    #endif

    gLpbkAppM2mObj.frmCnt++;

    if ((gIspApplyWbGains == 1) &&
        (gLpbkAppM2mObj.frmCnt % 5 == 0))
    {
        LpbkApp_m2mIspSetAewbGains(&gLpbkAppM2mObj);
    }

    return;
}

static Int32 LpbkApp_m2mIspOpenDriver(LpbkApp_m2mIspObj *appObj)
{
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn   = LpbkApp_m2mIspCallback;
    appObj->cbPrms.appData = appObj;

    VpsM2mIntfCreateParams_init(&appObj->createPrms);
    appObj->createPrms.numCh           = 1U;
    appObj->createPrms.chInQueueLength = 1U;
    appObj->createPrms.maxStatsInst    = 0U;
    appObj->createPrms.frmStats        = NULL;
    appObj->createPrms.pAdditionalArgs = (Ptr) & appObj->openPrms;

    VpsM2mIntfCreateStatus_init(&appObj->createStatusPrms);
    appObj->createStatusPrms.pAdditionalStatus = (Ptr) & appObj->retPrms;

    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = FALSE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = FALSE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = FALSE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = TRUE;
    appObj->openPrms.arg = NULL;

    appObj->drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CAL_ISP,
        &appObj->createPrms,
        &appObj->createStatusPrms,
        &appObj->cbPrms);
    if (NULL == appObj->drvHandle)
    {
        Bsp_printf("ISSM2MApp: Could not open driver for P1\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mIspSetRszConfig(LpbkApp_m2mIspObj *appObj)
{
    Int32 status;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->rszCfg,
                    0x0,
                    sizeof (vpsissRszCfg_t));
    BspUtils_memset(&appObj->rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));

    appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    appObj->rszCtrl.rszCfg = &appObj->rszCfg;

    appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    appObj->rszCtrl.rszCfg = &appObj->rszCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_RSZ_IOCTL_GET_CONFIG,
        &appObj->rszCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: Resizer GetConfig Failed\r\n");

        return -1;
    }

    appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
    appObj->rszCfg.inCfg.procWin.cropStartX = 0u;
    appObj->rszCfg.inCfg.procWin.cropStartY = 0u;
    appObj->rszCfg.inCfg.procWin.cropWidth  = appObj->inFmt.width;
    appObj->rszCfg.inCfg.procWin.cropHeight = appObj->inFmt.height;

    appObj->rszCfg.instCfg[0U].enable = 1U;
    appObj->rszCfg.instCfg[0U].outFmt.dataFormat = appObj->outFmt.dataFormat;
    appObj->rszCfg.instCfg[0U].outFmt.width      = appObj->outFmt.width;
    appObj->rszCfg.instCfg[0U].outFmt.height     = appObj->outFmt.height;
    appObj->rszCfg.instCfg[0U].outFmt.pitch[0U]  = appObj->outFmt.pitch[0U];
    appObj->rszCfg.instCfg[0U].outFmt.pitch[1U]  = appObj->outFmt.pitch[1U];
    appObj->rszCfg.instCfg[0U].outFmt.pitch[2U]  = appObj->outFmt.pitch[2U];

    appObj->rszCfg.instCfg[0u].flipCtrl =
        VPS_ISS_RSZ_STR_MODE_NORMAL;
    appObj->rszCfg.instCfg[0u].startPos.startX = 0u;
    appObj->rszCfg.instCfg[0u].startPos.startY = 0u;
    appObj->rszCfg.instCfg[0u].scaleMode       =
        VPS_ISS_RSZ_SCALE_MODE_NORMAL;
    appObj->rszCfg.instCfg[0u].filtCfg.horzLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0u].filtCfg.vertLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0u].filtCfg.horzChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0u].filtCfg.vertChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;

    appObj->rszCfg.instCfg[0u].intensityCfg.horzLumaIntensity   = 0x595u;
    appObj->rszCfg.instCfg[0u].intensityCfg.horzChromaIntensity = 0x0u;
    appObj->rszCfg.instCfg[0u].intensityCfg.vertLumaIntensity   = 0x3CFu;
    appObj->rszCfg.instCfg[0u].intensityCfg.vertChromaIntensity = 0x0u;

    appObj->rszCfg.instCfg[1U].enable = 0U;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_RSZ_IOCTL_SET_CONFIG,
        &appObj->rszCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: RSZ SetConfig Failed\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mIspSetParams(LpbkApp_m2mIspObj *appObj)
{
    Int32 status;

    /* Set the Params */
    appObj->ispPrms.inFmt    = appObj->inFmt;
    appObj->ispPrms.inFmtN_1 = appObj->inFmt;

    appObj->ispPrms.enableWdrMerge            = FALSE;
    appObj->ispPrms.enableDfs                 = FALSE;
    appObj->ispPrms.glbcePath                 = VPS_ISS_GLBCE_PATH_DISABLED;
    appObj->ispPrms.nsf3Path                  = VPS_ISS_NSF3_PATH_DISABLED;
    appObj->ispPrms.enableDpcPreNsf3          = FALSE;
    appObj->ispPrms.enableCnf                 = FALSE;
    appObj->ispPrms.enableRszInputFromIpipeif = FALSE;

    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] = TRUE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A]       = TRUE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1]    = FALSE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B]       = FALSE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_AF]          = FALSE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB]        = TRUE;

    appObj->ispPrms.useWen = FALSE;
    appObj->ispPrms.hdPol  = FVID2_POL_HIGH;
    appObj->ispPrms.vdPol  = FVID2_POL_HIGH;

    status = Fvid2_control(
        appObj->drvHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &appObj->ispPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: SetParams Failed for P1\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mIspSetIpipeConfig(LpbkApp_m2mIspObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->ipipeInputCfg,
                    0x0,
                    sizeof (vpsissIpipeInConfig_t));
    BspUtils_memset(&appObj->ipipeCtrl, 0x0, sizeof (vpsissIpipeCtrl_t));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
    appObj->ipipeCtrl.inCfg  = &appObj->ipipeInputCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: IPIPE GetConfig Failed\r\n");

        return -1;
    }

    appObj->ipipeInputCfg.dataPath =
        VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422;
    appObj->ipipeInputCfg.procWin.cropStartX = 0U;
    appObj->ipipeInputCfg.procWin.cropStartY = 0U;
    appObj->ipipeInputCfg.procWin.cropWidth  = appObj->inFmt.width;
    appObj->ipipeInputCfg.procWin.cropHeight = appObj->inFmt.height;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: IPIPE GetConfig Failed\r\n");

        return -1;
    }

    BspUtils_memset(&appObj->ipipeCtrl,
                    0x0,
                    sizeof (appObj->ipipeCtrl));
    BspUtils_memset(&appObj->rgb2rgbCfg,
                    0x0,
                    sizeof (appObj->rgb2rgbCfg));

    appObj->ipipeCtrl.module     = VPS_ISS_IPIPE_MODULE_RGB2RGB1;
    appObj->ipipeCtrl.rgb2RgbCfg = &appObj->rgb2rgbCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: IPIPE GetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memcpy(
        &appObj->rgb2rgbCfg,
        &gLpbkAppRgb2rgbDefCfg,
        sizeof (appObj->rgb2rgbCfg));

    appObj->ipipeCtrl.module     = VPS_ISS_IPIPE_MODULE_RGB2RGB1;
    appObj->ipipeCtrl.rgb2RgbCfg = &appObj->rgb2rgbCfg;
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: IPIPE SetConfig Failed\r\n");
        return -1;
    }

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: IPIPE GetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memcpy(
        &appObj->wbCfg,
        &gLpbkAppM2mIspWbDefCfg,
        sizeof (appObj->wbCfg));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: IPIPE SetConfig Failed\r\n");
        return -1;
    }

    return (status);
}

static Int32 LpbkApp_m2mIspAllocFrames(LpbkApp_m2mIspObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* Allocate the Buffer for the Input Frame */
    status = BspUtils_memFrameAlloc(
        &appObj->ispPrms.inFmt,
        &appObj->frames[0U],
        1U);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
        return (status);
    }

    return (status);
}

static Int32 LpbkApp_m2mIspCloseDriver(LpbkApp_m2mIspObj *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 frmCnt;

    /* Free up the buffer allocated for the input and output frames */
    if (NULL != appObj->frames[0U].addr[0U][0U])
    {
        status = BspUtils_memFrameFree(
            &appObj->ispPrms.inFmt,
            &appObj->frames[0U],
            1U);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Input Frame Free Failed!!!\r\n");
        }
        /* Set the chroma address */
        for (frmCnt = 0U; frmCnt < 1; frmCnt++)
        {
            appObj->frames[frmCnt].addr[0U][0U] = NULL;
            appObj->frames[frmCnt].addr[0U][1U] = NULL;
        }
    }

    if (NULL != appObj->drvHandle)
    {
        Fvid2_delete(appObj->drvHandle, NULL);
        appObj->drvHandle = NULL;
    }

    return 0;
}

static Int32 LpbkApp_m2mIspCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved)
{
    LpbkApp_m2mIspObj *appObj = (LpbkApp_m2mIspObj *) appData;

    if (NULL == handle)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Handle is null in isr !!\r\n");
    }
    if (NULL == appObj)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Object is null in isr !!\r\n");
    }
    else
    {
        /* Mark Frame As completed */
        Semaphore_post(appObj->waitForCompl);
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mIspSetH3aParams(LpbkApp_m2mIspObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->h3aCtrl,
                    0x0,
                    sizeof (vpsissH3aCtrl_t));
    BspUtils_memset(&appObj->aewbCfg, 0x0, sizeof (vpsissH3aAewbConfig_t));
    BspUtils_memset(&appObj->afCfg, 0x0, sizeof (vpsissH3aAfConfig_t));

    appObj->h3aCtrl.module  = VPS_ISS_H3A_MODULE_AEWB;
    appObj->h3aCtrl.aewbCfg = &appObj->aewbCfg;

    /* Get the ISIF Default Configuration */
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_H3A_IOCTL_GET_CONFIG,
        &appObj->h3aCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: H3A GetConfig Failed\r\n");

        return -1;
    }

    appObj->aewbCfg.enableALowComp     = FALSE;
    appObj->aewbCfg.enableMedFilt      = FALSE;
    appObj->aewbCfg.midFiltThreshold   = 0xFFF;
    appObj->aewbCfg.winCfg.pos.startX  = 32u;
    appObj->aewbCfg.winCfg.pos.startY  = 106u;
    appObj->aewbCfg.winCfg.width       = 64u;
    appObj->aewbCfg.winCfg.height      = 8u;
    appObj->aewbCfg.winCfg.horzCount   = 16u;
    appObj->aewbCfg.winCfg.vertCount   = 64u;
    appObj->aewbCfg.winCfg.horzIncr    = 4u;
    appObj->aewbCfg.winCfg.vertIncr    = 4u;
    appObj->aewbCfg.blackLineHeight    = 2u;
    appObj->aewbCfg.blackLineVertStart = 718u;
    appObj->aewbCfg.outMode  = VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY;
    appObj->aewbCfg.sumShift = 0x0;
    appObj->aewbCfg.satLimit = 1023;
    appObj->aewbCfg.mode     = VPS_ISS_H3A_MODE_NORMAL;

    /* Set the ISIF Changed configuration */
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_H3A_IOCTL_SET_CONFIG,
        &appObj->h3aCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: H3A SetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memset(&gLpbkAppM2mObj.image, 0x0, sizeof (gLpbkAppM2mObj.image));
    IDH_createImage(
        &gLpbkAppM2mObj.image,
        appObj->aewbCfg.winCfg.horzCount,
        appObj->aewbCfg.winCfg.vertCount,
        24,
        1);
    return (status);
}

static void LpbkApp_m2mIspCreateImageData(LpbkApp_m2mIspObj *appObj)
{
    UInt16 i, j, numWin, idx1, idx2;
    Char  *curAewbAddr;
    H3aAewbOutSumModeOverlay *pAewbWinData;
    UInt32 shift = 2;

    UInt32 aew_win_vt_cnt = appObj->aewbCfg.winCfg.vertCount;
    UInt32 aew_win_hz_cnt = appObj->aewbCfg.winCfg.horzCount;
    UInt32 rIndex         = 3u;
    UInt32 grIndex        = 2u;
    UInt32 gbIndex        = 1u;
    UInt32 bIndex         = 0u;
    UInt32 pixCtWin;

    pixCtWin = (appObj->aewbCfg.winCfg.height /
                appObj->aewbCfg.winCfg.vertIncr) *
               (appObj->aewbCfg.winCfg.width /
                appObj->aewbCfg.winCfg.horzIncr);

    curAewbAddr = (Char *) gLpbkAppM2mObj.frames[0u].addr[0u][0u];
    numWin      = 0;

    for (i = 0; i < aew_win_vt_cnt; i++)
    {
        for (j = 0; j < aew_win_hz_cnt; j++)
        {
            pAewbWinData = (H3aAewbOutSumModeOverlay *) curAewbAddr;

            idx1 = numWin / 8;
            idx2 = numWin % 8;

            appObj->aewb[idx1].window_data[idx2][0] =
                pAewbWinData->subSampleAcc[0];
            appObj->aewb[idx1].window_data[idx2][1] =
                pAewbWinData->subSampleAcc[1];
            appObj->aewb[idx1].window_data[idx2][2] =
                pAewbWinData->subSampleAcc[2];
            appObj->aewb[idx1].window_data[idx2][3] =
                pAewbWinData->subSampleAcc[3];

            curAewbAddr += sizeof (H3aAewbOutSumModeOverlay);

            numWin++;

            curAewbAddr += sizeof (H3aAewbOutUnsatBlkCntOverlay);
        }
    }

    for (i = 0; i < (aew_win_hz_cnt * aew_win_vt_cnt) / 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            appObj->image.rdata[i * 8 + j] =
                (appObj->aewb[i].window_data[j][rIndex] / pixCtWin) >> shift;
            appObj->image.bdata[i * 8 + j] =
                (appObj->aewb[i].window_data[j][bIndex] / pixCtWin) >> shift;
            appObj->image.gdata[i * 8 + j] =
                ((appObj->aewb[i].window_data[j][grIndex]
                  + appObj->aewb[i].window_data[j][gbIndex] + 1) /
                 pixCtWin) >> (1 + shift);
        }
    }
}

static void LpbkApp_m2mIspSetAewbGains(LpbkApp_m2mIspObj *appObj)
{
    Int32 status = FVID2_SOK;

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: IPIPE GetConfig Failed\r\n");
    }

    appObj->wbCfg.gain[FVID2_BAYER_COLOR_COMP_R] =
        (appObj->wbParams.gainOffset.gainFactors[0] * 512);
    appObj->wbCfg.gain[FVID2_BAYER_COLOR_COMP_GR] =
        (appObj->wbParams.gainOffset.gainFactors[1] * 512);
    appObj->wbCfg.gain[FVID2_BAYER_COLOR_COMP_GB] =
        (appObj->wbParams.gainOffset.gainFactors[1] * 512);
    appObj->wbCfg.gain[FVID2_BAYER_COLOR_COMP_B] =
        (appObj->wbParams.gainOffset.gainFactors[2] * 512);

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: IPIPE SetConfig Failed\r\n");
    }
}

static Int32 LpbkApp_m2mIspSetIsifLscConfig(
    LpbkApp_m2mIspObj *appObj)
{
    Int32 status;
    vpsissIsif2DLscConfig_t *lscCfg;

    BspUtils_memset(&appObj->isifCtrl, 0x0, sizeof (vpsissIsifCtrl_t));
    BspUtils_memset(&appObj->isifLscCfg, 0x0, sizeof (vpsissIsif2DLscConfig_t));

    lscCfg = &appObj->isifLscCfg;

    appObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_2D_LSC;
    appObj->isifCtrl.lscCfg = &appObj->isifLscCfg;
    /* Get the ISIF Default Configuration */
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_ISIF_IOCTL_GET_CONFIG,
        &appObj->isifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: ISIF GetLscConfig Failed\r\n");

        return -1;
    }

    lscCfg->enable = FALSE;

    lscCfg->activeReg.cropStartX = 100;
    lscCfg->activeReg.cropStartY = 100;
    lscCfg->activeReg.cropWidth  = 640;
    lscCfg->activeReg.cropHeight = 480;
    lscCfg->startPos.startX      = 10;
    lscCfg->startPos.startY      = 10;

    lscCfg->horzDownScale = VPS_ISS_ISIF_2D_LSC_DS_128;
    lscCfg->vertDownScale = VPS_ISS_ISIF_2D_LSC_DS_128;
    lscCfg->gainFormat    = VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q5;

    lscCfg->gainTableAddr    = 0x80000000;
    lscCfg->offsetTableAddr  = 0x80000000;
    lscCfg->gainTablePitch   = 368;
    lscCfg->offsetTablePitch = 368;

    lscCfg->enableOffset      = 1;
    lscCfg->offsetScaleFactor = 0x80;
    lscCfg->offsetShiftup     = VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_1;

    appObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_2D_LSC;
    appObj->isifCtrl.lscCfg = &appObj->isifLscCfg;

    /* Set the ISIF Changed configuration */
    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_ISIF_IOCTL_SET_CONFIG,
        &appObj->isifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MIspApp: ISIF SetConfig Failed\r\n");
        return -1;
    }

    return 0;
}

