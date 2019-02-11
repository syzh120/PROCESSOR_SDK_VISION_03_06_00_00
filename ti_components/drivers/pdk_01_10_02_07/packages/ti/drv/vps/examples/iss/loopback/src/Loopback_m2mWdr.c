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
#include <ipipeif_lut_10640.h>
#include <white_balance.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_REP_CNT            (1u)
float EXPOSURE_RATIO = (127.0);
/* Log 2 of EXPOSURE_RAIO */
float EV_RATIO = (7.0);

/*
 * The range of THRESHOLD_PERCENTAGE is 0-100% specified Q16 format
 * 65535 Maps to 100%
 */
#define THRESHOLD_PERCENTAGE    (65535)

extern int WB_estimateIlluminant(Image *imgPtr, float percPix,
                                 Illuminant *Illum);
extern int WB_estimateWbParams(Image *imgPtr, float percPix, WBParams *cP);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

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

    vpsissIspParams_t        ispPrms;
    /**< isp parameters */

    vpsissIspOpenParams_t    openPrms;
    /**< Core Open Parameters */
    vpsissIspOpenRetParams_t retPrms;
    /**< Core Returns Parameters */
} LpbkApp_m2mWdrPassObj;

/** \brief Application Object containing all the parameters
 */
typedef struct
{
    LpbkApp_m2mWdrPassObj         p1Cfg;
    LpbkApp_m2mWdrPassObj         p2Cfg;
    UInt32                        enableP2;

    vpsissRszCtrl_t               rszCtrl;
    /**< Resizer Control structure containing pointer to the
     *   resizer configuration */
    vpsissRszCfg_t                rszCfg;
    /**< Resizer configuration */

    vpsissIpipeifWdrCfg_t         wdrCfg;
    /**< IPIPEIF WDR Configuration */
    vpsissIpipeifCtrl_t           ipipeifCtrl;
    /**< IPIPE Control structure containing pointer to the
     *   IPIPE configuration */
    vpsissIpipeifSaturaInsts_t    satCfg;
    /**< IPIPEIF WDR Configuration */
    vpsissIpipeifDeCompandInsts_t cmpDecmpCfg;
    /**< IPIPEIF Companding/DeCompanding Configuration */
    vpsissIpipeifLutConfig_t      ipipeifLut;
    vpsissIsifGainOfstConfig_t    isifWbCfg;
    /**< White balance configuration of ISIF */
    vpsissIsif2DLscConfig_t       isifLscCfg;
    /**< ISIF LSC Configuration */
    vpsissIsifVfdcConfig_t        isifVfdcCfg;
    /**< Vertical Line pixel defect correction config */
    vpsissIsifBlackClampConfig_t  isifBlkClampCfg;
    /**< ISIF Optical Black Clamping Configuration, also used for
     *   configuring DC Offset */
    vpsissIsifCtrl_t              isifCtrl;
    /**< ISIF Control structure containing pointer to the
     *   ISIF configuration */
    vpsissIpipeInConfig_t         ipipeInputCfg;
    /**< IPIPE Input Configuration */
    vpsissIpipeCfaConfig_t        cfaCfg;
    /**< IPIPE CFA configuration */
    vpsissIpipeRgb2RgbConfig_t    rgb2rgbCfg;
    /**< IPIPE RGB2RGB configuration */

    vpsissIpipeWbConfig_t         wbCfg;
    /**< IPIPE White Balance Config */
    vpsissIpipeCtrl_t             ipipeCtrl;
    vpsissIpipeGammaConfig_t      gammaCfg;
    vpsissIpipe3DLutConfig_t      lut3d;
    vpsissIpipeEeConfig_t         eeCfg;
    vpsissIpipeGicConfig_t        gicCfg;
    vpsissIpipeLscConfig_t        lscCfg;
    vpsissIpipeNf2Config_t        nf1Cfg;
    vpsissIpipeNf2Config_t        nf2Cfg;
    vpsissIpipeLutFmtCnvt_t       lutFmtCnvt;

    vpsissIpipeDpcOtfConfig_t     dpcOtfCfg;

    vpsissNsf3Config_t            nsf3vCfg;

    UInt32                        enableGlbce;
    UInt32                        enableNsf3;
    UInt32                        enableDpc;
    UInt32                        enableCnf;
    UInt32                        enableIpipeifDpc;

    uint32_t                      enableLsc;
    uint32_t                      enableGic;
    uint32_t                      enableYee;
    uint32_t                      enable3dLut;
    uint32_t                      enableGamma;
    uint32_t                      enableNf1;
    uint32_t                      enableNf2;

    vpsissGlbceConfig_t           glbceCfg;
    vpsissGlbcePerceptConfig_t    perCfg;
    vpsissGlbceCtrl_t             glbceCtrl;

    vpsissCnfConfig_t             cnfCfg;

    Fvid2_Frame                   frames[3U];
    /**< Array of FVID Frames */
    Fvid2_FrameList               inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList               outFrmList;
    /**< Output Frames List */

    vpsissH3aCtrl_t               h3aCtrl;
    vpsissH3aAewbConfig_t         aewbCfg;
    vpsissH3aAfConfig_t           afCfg;

    Semaphore_Handle              waitForCompl;
    /**< Semaphore for waiting for the completion */

    Image                         image;
    WBParams                      wbParams;
    WBParams                      longWbPrms, shortWbPrms;
    aewDataEntry                  aewb[1000];

    UInt32                        frmCnt;

    Fvid2_Format                  inFmt;
    Fvid2_Format                  outFmt;
    float                         expRatio;
    float                         evRatio;
} LpbkApp_m2mWdrObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 LpbkApp_m2mWdrOpenDriver(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrAllocFrames(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrCloseDriver(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrSetParams(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrSetIsifConfig(
    LpbkApp_m2mWdrObj *appObj,
    UInt32             ispass2);
static Int32 LpbkApp_m2mWdrSetIpipeifConfig(LpbkApp_m2mWdrObj *appObj,
                                            uint32_t           isPass2);
static Int32 LpbkApp_m2mWdrSaturConfig(
    LpbkApp_m2mWdrObj *appObj,
    UInt32             isPass2);
static Int32 LpbkApp_m2mWdrSetIpipeConfig(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrSetNsf3vConfig(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrSetGlbceConfig(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrSetCnfConfig(LpbkApp_m2mWdrObj *appObj);
static Int32 LpbkApp_m2mWdrSetRszConfig(
    LpbkApp_m2mWdrObj *appObj,
    UInt32             isPass2);
static Int32 LpbkApp_m2mWdrCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved);
static Int32 LpbkApp_m2mWdrSetH3aParams(LpbkApp_m2mWdrObj *appObj);
static void LpbkApp_m2mWdrCreateImageData(LpbkApp_m2mWdrObj *appObj);
static void LpbkApp_m2mWdrSetAewbGains(LpbkApp_m2mWdrObj *appObj);
static void LpbkApp_m2mWdrSetIpipeifAewbGains(LpbkApp_m2mWdrObj *appObj);

Int32 LpbkApp_m2mWdrIpipeifWdrLutsConfig(LpbkApp_m2mWdrObj *appObj,
                                         uint32_t           isPass2);

static Int32 LpbkApp_m2mWdrSetIsifLscConfig(
    LpbkApp_m2mWdrObj *appObj);

#if 0
static void CalcBlendFact(float T, float V, UInt32 *afe,
                          UInt32 *afm, UInt32 *af);
#endif

static Int32 Power2(Int32 k);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

LpbkApp_m2mWdrObj gLpbkAppM2mWdrObj;
UInt32 gApplyWbGains          = 1;
UInt32 gApplyWbGainsInIpipeif = 1;
UInt32 gApplyWbGainFrmCnt     = 5;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  IntgApp_createM2mWdr
 *  Application test task.
 */
void LpbkApp_m2mWdrCreate(LpbkApp_testCfg *testCfg)
{
    Int32 status = FVID2_SOK;
    Semaphore_Params semPrms;

    /* Create semaphore */
    Semaphore_Params_init(&semPrms);
    gLpbkAppM2mWdrObj.waitForCompl = Semaphore_create(0U, &semPrms, NULL);
    if (NULL == gLpbkAppM2mWdrObj.waitForCompl)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d:Could not Create Semaphore\r\n",
                  __FUNCTION__, __LINE__);
        GT_assert(BspAppTrace, FALSE);
    }
    if (gApplyWbGains)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME
                  " AWB is enabled!!!\r\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME
                  " AWB is disabled`!!!\r\n");
    }

    Fvid2Format_init(&gLpbkAppM2mWdrObj.inFmt);
    Fvid2Format_init(&gLpbkAppM2mWdrObj.outFmt);

    /* Copy input and output parameters */
    gLpbkAppM2mWdrObj.inFmt.width      = testCfg->inWidth;
    gLpbkAppM2mWdrObj.inFmt.height     = testCfg->inHeight;
    gLpbkAppM2mWdrObj.inFmt.dataFormat = testCfg->inDataFormat;
    gLpbkAppM2mWdrObj.inFmt.bpp        = testCfg->inBpp;
    gLpbkAppM2mWdrObj.inFmt.pitch[0U]  = testCfg->inPitch;
    gLpbkAppM2mWdrObj.inFmt.pitch[1U]  = testCfg->inPitch;
    gLpbkAppM2mWdrObj.inFmt.pitch[2U]  = testCfg->inPitch;

    gLpbkAppM2mWdrObj.outFmt.width      = testCfg->outWidth;
    gLpbkAppM2mWdrObj.outFmt.height     = testCfg->outHeight;
    gLpbkAppM2mWdrObj.outFmt.dataFormat = testCfg->outDataFormat;
    gLpbkAppM2mWdrObj.outFmt.bpp        = testCfg->outBpp;
    gLpbkAppM2mWdrObj.outFmt.pitch[0U]  = testCfg->outPitch;
    gLpbkAppM2mWdrObj.outFmt.pitch[1U]  = testCfg->outPitch;
    gLpbkAppM2mWdrObj.outFmt.pitch[2U]  = testCfg->outPitch;

    /* Flag for Enabling Modules */
    gLpbkAppM2mWdrObj.enableP2    = TRUE;
    gLpbkAppM2mWdrObj.enableGlbce = TRUE;
    gLpbkAppM2mWdrObj.enableNsf3  = TRUE;
    gLpbkAppM2mWdrObj.enableDpc   = TRUE;
    gLpbkAppM2mWdrObj.enableCnf   = TRUE;

    gLpbkAppM2mWdrObj.enableLsc   = FALSE;
    gLpbkAppM2mWdrObj.enableGic   = FALSE;
    gLpbkAppM2mWdrObj.enableYee   = FALSE;
    gLpbkAppM2mWdrObj.enable3dLut = FALSE;
    gLpbkAppM2mWdrObj.enableGamma = TRUE;
    gLpbkAppM2mWdrObj.enableNf1   = FALSE;
    gLpbkAppM2mWdrObj.enableNf2   = FALSE;
    gLpbkAppM2mWdrObj.frmCnt      = 0U;

    status = LpbkApp_m2mWdrOpenDriver(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
    }

    status = LpbkApp_m2mWdrSetParams(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Seting Driver Parameters\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableNsf3)
    {
        status = LpbkApp_m2mWdrSetNsf3vConfig(&gLpbkAppM2mWdrObj);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MWdrApp: Nsf3v SetConfig Failed\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            GT_assert(BspAppTrace, FALSE);
            return;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableGlbce)
    {
        status = LpbkApp_m2mWdrSetGlbceConfig(&gLpbkAppM2mWdrObj);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MWdrApp: Glbce SetConfig Failed\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            GT_assert(BspAppTrace, FALSE);
            return;
        }
    }

    gLpbkAppM2mWdrObj.expRatio = EXPOSURE_RATIO;
    gLpbkAppM2mWdrObj.evRatio  = EV_RATIO;
    status = LpbkApp_m2mWdrIpipeifWdrLutsConfig(&gLpbkAppM2mWdrObj, FALSE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed for P1 \r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }
    status = LpbkApp_m2mWdrIpipeifWdrLutsConfig(&gLpbkAppM2mWdrObj, TRUE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed for P2 \r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetIpipeifConfig(&gLpbkAppM2mWdrObj, FALSE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed P1\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetIpipeifConfig(&gLpbkAppM2mWdrObj, TRUE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed P2\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetIsifConfig(&gLpbkAppM2mWdrObj, FALSE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: ISIF SetConfig Failed\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetIsifLscConfig(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: ISIF SetLscConfig Failed\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetIpipeConfig(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetRszConfig(&gLpbkAppM2mWdrObj, FALSE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: Resizer SetConfig Failed\r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrAllocFrames(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error in Allocating Buffers \r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    status = LpbkApp_m2mWdrSetH3aParams(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Setting H3A Params \r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    return;
}

void LpbkApp_m2mWdrApplyWdrParams(float expRatio, float evRatio)
{
    Int32 status;

    gLpbkAppM2mWdrObj.expRatio = EXPOSURE_RATIO;
    gLpbkAppM2mWdrObj.evRatio  = EV_RATIO;
    status = LpbkApp_m2mWdrIpipeifWdrLutsConfig(&gLpbkAppM2mWdrObj, FALSE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed for P1 \r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }
    status = LpbkApp_m2mWdrIpipeifWdrLutsConfig(&gLpbkAppM2mWdrObj, TRUE);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed for P2 \r\n");
        LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
        GT_assert(BspAppTrace, FALSE);
        return;
    }
}

void LpbkApp_m2mWdrClose(void)
{
    Int32 status = FVID2_SOK;

    status = LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
        GT_assert(BspAppTrace, FALSE);
        return;
    }

    Semaphore_delete(&gLpbkAppM2mWdrObj.waitForCompl);

    IDH_freeImage(&gLpbkAppM2mWdrObj.image);
}

void LpbkApp_m2mWdrProcessFrame(Fvid2_Frame *inpFrm, Fvid2_Frame *outFrm)
{
    Int32  status = FVID2_SOK;
    UInt32 repeatCnt;

    for (repeatCnt = 0U; repeatCnt < TEST_REP_CNT; repeatCnt++)
    {
        Fvid2FrameList_init(&gLpbkAppM2mWdrObj.inFrmList);
        Fvid2FrameList_init(&gLpbkAppM2mWdrObj.outFrmList);

        status = LpbkApp_m2mWdrSetIsifConfig(&gLpbkAppM2mWdrObj, FALSE);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MWdrApp: ISIF SetConfig Failed\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            GT_assert(BspAppTrace, FALSE);
            return;
        }

        status = LpbkApp_m2mWdrSetRszConfig(&gLpbkAppM2mWdrObj, FALSE);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MWdrApp: Resizer SetConfig Failed\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            return;
        }

        status = LpbkApp_m2mWdrSaturConfig(&gLpbkAppM2mWdrObj, FALSE);
        if (FVID2_SOK != status)
        {
            Bsp_printf(
                "ISSM2MWdrApp: IPIPEIF Saturation SetConfig Failed\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            return;
        }

        /* Make input and output frames list */
        gLpbkAppM2mWdrObj.inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
            inpFrm;
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        gLpbkAppM2mWdrObj.inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        gLpbkAppM2mWdrObj.outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
            &gLpbkAppM2mWdrObj.frames[0U];
        gLpbkAppM2mWdrObj.outFrmList.frames[VPS_ISS_STREAM_ID_AEWB] =
            &gLpbkAppM2mWdrObj.frames[1U];

        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        gLpbkAppM2mWdrObj.outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        /* Submit Processing Request to the driver */
        status = Fvid2_processRequest(
            gLpbkAppM2mWdrObj.p1Cfg.drvHandle,
            &gLpbkAppM2mWdrObj.inFrmList,
            &gLpbkAppM2mWdrObj.outFrmList);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Submitting request P1\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            return;
        }

        /* Wait for test to complete */
        Semaphore_pend(gLpbkAppM2mWdrObj.waitForCompl, BIOS_WAIT_FOREVER);

        /* Submit Processing Request to the driver */
        status = Fvid2_getProcessedRequest(
            gLpbkAppM2mWdrObj.p1Cfg.drvHandle,
            &gLpbkAppM2mWdrObj.inFrmList,
            &gLpbkAppM2mWdrObj.outFrmList,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Getting completed Request\r\n");
            LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
            return;
        }

        /* Run AEWB Algorithm */
        /*AppCreateImageData(&gLpbkAppM2mWdrObj);
         * WB_estimateWbParams(&gLpbkAppM2mWdrObj.image, 8,
         *                  &gLpbkAppM2mWdrObj.shortWbPrms);*/

        if (TRUE == gLpbkAppM2mWdrObj.enableP2)
        {
            status = LpbkApp_m2mWdrSetIsifConfig(&gLpbkAppM2mWdrObj, TRUE);
            if (FVID2_SOK != status)
            {
                Bsp_printf("ISSM2MWdrApp: ISIF SetConfig Failed\r\n");
                LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
                GT_assert(BspAppTrace, FALSE);
                return;
            }

            status = LpbkApp_m2mWdrSetRszConfig(&gLpbkAppM2mWdrObj, TRUE);
            if (FVID2_SOK != status)
            {
                Bsp_printf("ISSM2MWdrApp: Resizer SetConfig Failed\r\n");
                LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
                return;
            }

            if (TRUE == gLpbkAppM2mWdrObj.enableCnf)
            {
                status = LpbkApp_m2mWdrSetCnfConfig(&gLpbkAppM2mWdrObj);
                if (FVID2_SOK != status)
                {
                    Bsp_printf("ISSM2MWdrApp: CNF SetConfig Failed\r\n");
                    LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
                    return;
                }
            }

            status = LpbkApp_m2mWdrSaturConfig(&gLpbkAppM2mWdrObj, TRUE);
            if (FVID2_SOK != status)
            {
                Bsp_printf(
                    "ISSM2MWdrApp: IPIPEIF Saturation SetConfig Failed\r\n");
                LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
                return;
            }

            /* Make input and output frames list */
            gLpbkAppM2mWdrObj.inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
                inpFrm;
            gLpbkAppM2mWdrObj.inFrmList.frames[VPS_ISS_STREAM_ID_INPUT_N1] =
                &gLpbkAppM2mWdrObj.frames[0U];
            /* Always provide number of frames in the frame list to be max
             * streams of isp */
            gLpbkAppM2mWdrObj.inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

            gLpbkAppM2mWdrObj.outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
                outFrm;

            gLpbkAppM2mWdrObj.outFrmList.frames[VPS_ISS_STREAM_ID_AEWB] =
                &gLpbkAppM2mWdrObj.frames[1U];
            /* Always provide number of frames in the frame list to be max
             * streams of isp */
            gLpbkAppM2mWdrObj.outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

            /* Submit Processing Request to the driver */
            status = Fvid2_processRequest(
                gLpbkAppM2mWdrObj.p2Cfg.drvHandle,
                &gLpbkAppM2mWdrObj.inFrmList,
                &gLpbkAppM2mWdrObj.outFrmList);
            if (FVID2_SOK != status)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          APP_NAME ": Error Submitting request P2\r\n");
                LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
                return;
            }

            /* Wait for test to complete */
            Semaphore_pend(gLpbkAppM2mWdrObj.waitForCompl, BIOS_WAIT_FOREVER);

            /* Submit Processing Request to the driver */
            status = Fvid2_getProcessedRequest(
                gLpbkAppM2mWdrObj.p2Cfg.drvHandle,
                &gLpbkAppM2mWdrObj.inFrmList,
                &gLpbkAppM2mWdrObj.outFrmList,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != status)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          APP_NAME ": Error Getting completed Request\r\n");
                LpbkApp_m2mWdrCloseDriver(&gLpbkAppM2mWdrObj);
                return;
            }

            gLpbkAppM2mWdrObj.frmCnt++;

            /* Run AEWB Algorithm */
            LpbkApp_m2mWdrCreateImageData(&gLpbkAppM2mWdrObj);
            WB_estimateWbParams(&gLpbkAppM2mWdrObj.image, 8,
                                &gLpbkAppM2mWdrObj.longWbPrms);

            if ((gApplyWbGains == 1) &&
                (gLpbkAppM2mWdrObj.frmCnt % gApplyWbGainFrmCnt == 0))
            {
                if (1 == gApplyWbGainsInIpipeif)
                {
                    LpbkApp_m2mWdrSetIpipeifAewbGains(&gLpbkAppM2mWdrObj);
                }
                else
                {
                    LpbkApp_m2mWdrSetAewbGains(&gLpbkAppM2mWdrObj);
                }
            }
        }
    }
}

static Int32 LpbkApp_m2mWdrCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved)
{
    LpbkApp_m2mWdrObj *appObj = (LpbkApp_m2mWdrObj *) appData;

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

static Int32 LpbkApp_m2mWdrAllocFrames(LpbkApp_m2mWdrObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* allocate the buffer for the intermediate output */
    status = BspUtils_memFrameAlloc(
        &appObj->p1Cfg.ispPrms.inFmt,
        &appObj->frames[0U],
        2U);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
        return (status);
    }

    return (status);
}

static Int32 LpbkApp_m2mWdrOpenDriver(LpbkApp_m2mWdrObj *appObj)
{
    Fvid2CbParams_init(&appObj->p1Cfg.cbPrms);
    appObj->p1Cfg.cbPrms.cbFxn   = LpbkApp_m2mWdrCallback;
    appObj->p1Cfg.cbPrms.appData = appObj;

    VpsM2mIntfCreateParams_init(&appObj->p1Cfg.createPrms);
    appObj->p1Cfg.createPrms.numCh           = 1U;
    appObj->p1Cfg.createPrms.chInQueueLength = 1U;
    appObj->p1Cfg.createPrms.maxStatsInst    = 0U;
    appObj->p1Cfg.createPrms.frmStats        = NULL;
    appObj->p1Cfg.createPrms.pAdditionalArgs = (Ptr) & appObj->p1Cfg.openPrms;

    VpsM2mIntfCreateStatus_init(&appObj->p1Cfg.createStatusPrms);
    appObj->p1Cfg.createStatusPrms.pAdditionalStatus =
        (Ptr) & appObj->p1Cfg.retPrms;

    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = FALSE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = FALSE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = TRUE;
    appObj->p1Cfg.openPrms.arg = NULL;

    appObj->p1Cfg.drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CAL_ISP,
        &appObj->p1Cfg.createPrms,
        &appObj->p1Cfg.createStatusPrms,
        &appObj->p1Cfg.cbPrms);
    if (NULL == appObj->p1Cfg.drvHandle)
    {
        Bsp_printf("ISSM2MWdrApp: Could not open driver for P1\r\n");
        return -1;
    }

    if (TRUE == appObj->enableP2)
    {
        Fvid2CbParams_init(&appObj->p2Cfg.cbPrms);
        appObj->p2Cfg.cbPrms.cbFxn   = LpbkApp_m2mWdrCallback;
        appObj->p2Cfg.cbPrms.appData = appObj;

        VpsM2mIntfCreateParams_init(&appObj->p2Cfg.createPrms);
        appObj->p2Cfg.createPrms.numCh           = 1U;
        appObj->p2Cfg.createPrms.chInQueueLength = 1U;
        appObj->p2Cfg.createPrms.maxStatsInst    = 0U;
        appObj->p2Cfg.createPrms.frmStats        = NULL;
        appObj->p2Cfg.createPrms.pAdditionalArgs = (Ptr) &
                                                   appObj->p2Cfg.openPrms;

        VpsM2mIntfCreateStatus_init(&appObj->p2Cfg.createStatusPrms);
        appObj->p2Cfg.createStatusPrms.pAdditionalStatus =
            (Ptr) & appObj->p2Cfg.retPrms;

        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     =
            gLpbkAppM2mWdrObj.enableCnf;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A] = TRUE;
        appObj->p2Cfg.openPrms.arg = NULL;

        appObj->p2Cfg.drvHandle = Fvid2_create(
            FVID2_VPS_COMMON_M2M_INTF_DRV,
            VPS_M2M_ISS_INST_CAL_ISP,
            &appObj->p2Cfg.createPrms,
            &appObj->p2Cfg.createStatusPrms,
            &appObj->p2Cfg.cbPrms);
        if (NULL == appObj->p2Cfg.drvHandle)
        {
            Bsp_printf("ISSM2MWdrApp: Could not open driver for P2\r\n");
            return -1;
        }
    }
    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mWdrCloseDriver(LpbkApp_m2mWdrObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* Free up the buffer allocated for the input and output frames */
    if (NULL != appObj->frames[0U].addr[0U][0U])
    {
        status = BspUtils_memFrameFree(
            &appObj->p1Cfg.ispPrms.inFmt,
            &appObj->frames[0U],
            2U);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Input Frame Free Failed!!!\r\n");
        }
        appObj->frames[0U].addr[0U][0U] = NULL;
        appObj->frames[1U].addr[0U][0U] = NULL;
    }
    if (NULL != appObj->p1Cfg.drvHandle)
    {
        Fvid2_delete(appObj->p1Cfg.drvHandle, NULL);
        appObj->p1Cfg.drvHandle = NULL;
    }
    if (NULL != appObj->p2Cfg.drvHandle)
    {
        Fvid2_delete(appObj->p2Cfg.drvHandle, NULL);
        appObj->p2Cfg.drvHandle = NULL;
    }

    return 0;
}

static Int32 LpbkApp_m2mWdrSetParams(LpbkApp_m2mWdrObj *appObj)
{
    Int32 status;

    BspUtils_memset(&appObj->p1Cfg.ispPrms, 0x0, sizeof (vpsissIspParams_t));
    /* Set the Params */
    appObj->p1Cfg.ispPrms.inFmt    = appObj->inFmt;
    appObj->p1Cfg.ispPrms.inFmtN_1 = appObj->inFmt;

    appObj->p1Cfg.ispPrms.enableWdrMerge = FALSE;
    appObj->p1Cfg.ispPrms.enableDfs      = FALSE;
    appObj->p1Cfg.ispPrms.nsf3Path       = VPS_ISS_NSF3_PATH_ISP;
    appObj->p1Cfg.ispPrms.glbcePath      =
        VPS_ISS_GLBCE_PATH_DISABLED;
    appObj->p1Cfg.ispPrms.enableDpcPreNsf3          = TRUE;
    appObj->p1Cfg.ispPrms.enableCnf                 = FALSE;
    appObj->p1Cfg.ispPrms.enableRszInputFromIpipeif = TRUE;

    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] = TRUE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A]       = TRUE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1]    = FALSE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B]       = FALSE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AF]          = FALSE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB]        = TRUE;

    appObj->p1Cfg.ispPrms.useWen = FALSE;
    appObj->p1Cfg.ispPrms.hdPol  = FVID2_POL_HIGH;
    appObj->p1Cfg.ispPrms.vdPol  = FVID2_POL_HIGH;

    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &appObj->p1Cfg.ispPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: SetParams Failed for P1\r\n");
        return -1;
    }

    if (TRUE == appObj->enableP2)
    {
        BspUtils_memset(&appObj->p2Cfg.ispPrms, 0x0, sizeof (vpsissIspParams_t));
        /* Set the Params for Pass2 */
        appObj->p2Cfg.ispPrms.inFmt    = appObj->inFmt;
        appObj->p2Cfg.ispPrms.inFmtN_1 = appObj->inFmt;

        appObj->p2Cfg.ispPrms.enableWdrMerge = TRUE;
        appObj->p2Cfg.ispPrms.enableDfs      = FALSE;
        appObj->p2Cfg.ispPrms.nsf3Path       = VPS_ISS_NSF3_PATH_ISP;
        appObj->p2Cfg.ispPrms.glbcePath      =
            VPS_ISS_GLBCE_PATH_ISP;
        appObj->p2Cfg.ispPrms.enableDpcPreNsf3 = TRUE;
        appObj->p2Cfg.ispPrms.enableCnf        =
            gLpbkAppM2mWdrObj.enableCnf;
        appObj->p2Cfg.ispPrms.enableRszInputFromIpipeif = FALSE;

        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
            TRUE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A] =
            TRUE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1] =
            TRUE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] =
            FALSE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AF] =
            FALSE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB] =
            TRUE;

        appObj->p2Cfg.ispPrms.useWen = FALSE;
        appObj->p2Cfg.ispPrms.hdPol  = FVID2_POL_HIGH;
        appObj->p2Cfg.ispPrms.vdPol  = FVID2_POL_HIGH;

        status = Fvid2_control(
            appObj->p2Cfg.drvHandle,
            IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
            &appObj->p2Cfg.ispPrms,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: SetParams Failed for P1\r\n");
            return -1;
        }
    }
    return (status);
}

static Int32 LpbkApp_m2mWdrSetIpipeifConfig(LpbkApp_m2mWdrObj *appObj,
                                            uint32_t           isPass2)
{
    Int32        status;
    Fvid2_Handle drvHdl;

    drvHdl = appObj->p1Cfg.drvHandle;
    if (TRUE == isPass2)
    {
        drvHdl = appObj->p2Cfg.drvHandle;
    }

    BspUtils_memset(&appObj->ipipeifLut, 0x0, sizeof (appObj->ipipeifLut));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT;
    appObj->ipipeifCtrl.pLutCfg = &appObj->ipipeifLut;

    appObj->ipipeifLut.vportDecompandLut = vport_lut;
    appObj->ipipeifLut.vportLutSize      = 513u * 4u;
    appObj->ipipeifLut.memifDecompandLut = sd_lut;
    appObj->ipipeifLut.memifLutSize      = 513u * 4u;
    appObj->ipipeifLut.wdrCompandLut     = wdr_lut;
    appObj->ipipeifLut.wdrLutSize        = 513u * 4u;

    /* Set the Companding and Decompanding LUTs in ipipeif */
    status = Fvid2_control(
        drvHdl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Update LUT Config Failed\r\n");
        return -1;
    }

    BspUtils_memset(&appObj->satCfg, 0x0, sizeof (appObj->satCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG;
    appObj->ipipeifCtrl.pSatCfg = &appObj->satCfg;

    appObj->satCfg.vportSatCfg.enable = TRUE;
    appObj->satCfg.vportSatCfg.sat    = 4095u;
    appObj->satCfg.vportSatCfg.dcClmp = 0u;
    appObj->satCfg.vportSatCfg.dsf    = 0u;

    appObj->satCfg.memifSatCfg.enable = FALSE;
    appObj->satCfg.memifSatCfg.sat    = 4095u;
    appObj->satCfg.memifSatCfg.dcClmp = 0u;
    appObj->satCfg.memifSatCfg.dsf    = 0u;

    appObj->satCfg.isifSatCfg.enable = FALSE;
    appObj->satCfg.isifSatCfg.sat    = 4095u;
    appObj->satCfg.isifSatCfg.dcClmp = 0u;
    appObj->satCfg.isifSatCfg.dsf    = 0u;

    /* Set the Saturation Configuration in all three saturation
     * modules of ipipeif */
    status = Fvid2_control(
        drvHdl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Saturation Config Failed\r\n");

        return -1;
    }

    return (FVID2_SOK);
}

Int32 LpbkApp_m2mWdrIpipeifWdrLutsConfig(LpbkApp_m2mWdrObj *appObj,
                                         uint32_t           isPass2)
{
    Int32        status;
    Fvid2_Handle drvHndl;

    drvHndl = appObj->p1Cfg.drvHandle;
    if (TRUE == isPass2)
    {
        drvHndl = appObj->p2Cfg.drvHandle;
    }

    BspUtils_memset(&appObj->cmpDecmpCfg, 0x0, sizeof (appObj->cmpDecmpCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module =
        VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
    appObj->ipipeifCtrl.pCompDecompCfg = &gVportCompDecompCfg;

    appObj->ipipeifCtrl.module =
        VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
    appObj->ipipeifCtrl.pCompDecompCfg = &gVportCompDecompCfg;

    /* Set the Comp/Decomp Configuration in ipipeif */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Comp/Decomp Config Failed\r\n");

        return -1;
    }

    BspUtils_memset(&appObj->wdrCfg, 0x0, sizeof (appObj->wdrCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG;
    appObj->ipipeifCtrl.pWdrCfg = &gWdrCfg;

    /* Set the changed configuration */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set WDR Config Failed\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

#if 0
Int32 LpbkApp_m2mWdrIpipeifWdrLutsConfig(LpbkApp_m2mWdrObj *appObj)
{
    Int32  status;
    UInt32 mergeWidth, bit_width = 12, wtDsf, wdrClip, cfg4Dst, temp, wdrThrThr;
    UInt64 t1;

    if (gLpbkAppM2mWdrObj.inFmt.bpp == FVID2_BPP_BITS12)
    {
        bit_width = 12;
    }

    mergeWidth = appObj->evRatio + bit_width;

    BspUtils_memset(&appObj->cmpDecmpCfg, 0x0, sizeof (appObj->cmpDecmpCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module =
        VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
    appObj->ipipeifCtrl.pCompDecompCfg = &gVportCompDecompCfg;

    if (mergeWidth > 16)
    {
        gVportCompDecompCfg.compandCfg.enable = TRUE;
        wtDsf = mergeWidth - 16U;
        gVportCompDecompCfg.compandCfg.size = mergeWidth - 9U;
        cfg4Dst = 15;

        wdrClip = Power2(mergeWidth);
        wdrClip = wdrClip - 1;
    }
    else
    {
        gVportCompDecompCfg.compandCfg.enable = FALSE;
        wtDsf   = 0U;
        cfg4Dst = mergeWidth - 1u;
        wdrClip = 65535;
    }

    appObj->ipipeifCtrl.module =
        VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
    appObj->ipipeifCtrl.pCompDecompCfg = &gVportCompDecompCfg;

    /* Set the Comp/Decomp Configuration in ipipeif */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Comp/Decomp Config Failed\r\n");

        return -1;
    }

    BspUtils_memset(&appObj->wdrCfg, 0x0, sizeof (appObj->wdrCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG;
    appObj->ipipeifCtrl.pWdrCfg = &gWdrCfg;

    gWdrCfg.dst  = cfg4Dst;
    gWdrCfg.lbit = mergeWidth - bit_width;
    gWdrCfg.sbit = gWdrCfg.lbit;

    gWdrCfg.gshort = 32768;
    gWdrCfg.glong  = gWdrCfg.gshort / gLpbkAppM2mWdrObj.expRatio;
    temp           = Power2(bit_width);

    temp = temp - 1;
    t1   =
        ((UInt64) THRESHOLD_PERCENTAGE * ((UInt64) (temp) * gWdrCfg.glong));
    wdrThrThr = (UInt32) (t1 >> (31 - gWdrCfg.lbit));

    wdrThrThr = wdrThrThr >> wtDsf;

    gWdrCfg.thr = wdrThrThr;

    gWdrCfg.mergeShift = wtDsf;
    gWdrCfg.mergeClip  = wdrClip;

#if 0
    CalcBlendFact(wdrThrThr, 0.51, &gWdrCfg.afe, &gWdrCfg.afm, &gWdrCfg.bf);
#else
    gWdrCfg.afe = 0;
    gWdrCfg.afm = 0;
    gWdrCfg.bf  = 0;
#endif

    /* Set the changed configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set WDR Config Failed\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

#endif

static Int32 LpbkApp_m2mWdrSaturConfig(
    LpbkApp_m2mWdrObj *appObj,
    UInt32             isPass2)
{
    Int32 status = FVID2_SOK, bit_width = 12;

    if (gLpbkAppM2mWdrObj.inFmt.bpp == FVID2_BPP_BITS12)
    {
        bit_width = 12;
    }

    BspUtils_memset(&appObj->satCfg, 0x0, sizeof (appObj->satCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG;
    appObj->ipipeifCtrl.pSatCfg = &appObj->satCfg;

    if (TRUE == isPass2)
    {
        gLongSatCfg.vportSatCfg.sat = (Power2(bit_width) - 1);
        gLongSatCfg.vportSatCfg.dsf = 0;

        BspUtils_memcpy(
            &appObj->satCfg,
            &gShortSatCfg,
            sizeof (vpsissIpipeifSaturaInsts_t));
    }
    else
    {
        gLongSatCfg.vportSatCfg.sat =
            (Power2(bit_width) - 1) * gLpbkAppM2mWdrObj.expRatio;
        gLongSatCfg.vportSatCfg.dsf = appObj->evRatio;

        BspUtils_memcpy(
            &appObj->satCfg,
            &gLongSatCfg,
            sizeof (vpsissIpipeifSaturaInsts_t));
    }

    /* Set the changed configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Saturation Config Failed\r\n");
        return -1;
    }

    return (status);
}

static Int32 LpbkApp_m2mWdrSetIpipeConfig(LpbkApp_m2mWdrObj *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 cnt;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->ipipeInputCfg,
                    0x0,
                    sizeof (vpsissIpipeInConfig_t));
    BspUtils_memset(&appObj->ipipeCtrl, 0x0, sizeof (vpsissIpipeCtrl_t));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
    appObj->ipipeCtrl.inCfg  = &appObj->ipipeInputCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
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
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: IPIPE Input SetConfig Failed\r\n");
        return -1;
    }

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->cfaCfg,
                    0x0,
                    sizeof (vpsissIpipeCfaConfig_t));
    BspUtils_memset(&appObj->ipipeCtrl, 0x0, sizeof (vpsissIpipeCtrl_t));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_CFA;
    appObj->ipipeCtrl.cfaCfg = &appObj->cfaCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: CFA GetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memcpy(&appObj->cfaCfg, &gIssCfaDefCfg, sizeof (gIssCfaDefCfg));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: IPIPE CFA SetConfig Failed\r\n");
        return -1;
    }

    /* Set the Gamma Correct Configuration */
    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->ipipeCtrl,
                    0x0,
                    sizeof (appObj->ipipeCtrl));
    BspUtils_memset(&appObj->rgb2rgbCfg,
                    0x0,
                    sizeof (appObj->rgb2rgbCfg));

    appObj->ipipeCtrl.module     = VPS_ISS_IPIPE_MODULE_RGB2RGB1;
    appObj->ipipeCtrl.rgb2RgbCfg = &appObj->rgb2rgbCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memcpy(
        &appObj->rgb2rgbCfg,
        &gIssRgb2rgbDefCfg,
        sizeof (appObj->rgb2rgbCfg));

    appObj->ipipeCtrl.module     = VPS_ISS_IPIPE_MODULE_RGB2RGB1;
    appObj->ipipeCtrl.rgb2RgbCfg = &appObj->rgb2rgbCfg;
    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");
        return -1;
    }

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memcpy(
        &appObj->wbCfg,
        &gIssWbDefCfg,
        sizeof (appObj->wbCfg));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;
    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");
        return -1;
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableDpc)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->dpcOtfCfg,
                        0x0,
                        sizeof (appObj->dpcOtfCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_DPC_OTF;
        appObj->ipipeCtrl.dpcOtf = &appObj->dpcOtfCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->dpcOtfCfg.enableOtfDpc = FALSE;
        appObj->dpcOtfCfg.method       = VPS_ISS_IPIPE_DPC_OTF_METHOD_1;
        appObj->dpcOtfCfg.dThr         = 0x0u;
        appObj->dpcOtfCfg.grThr        = 0x1u;
        appObj->dpcOtfCfg.gbThr        = 0x0u;
        appObj->dpcOtfCfg.bThr         = 800u;
        appObj->dpcOtfCfg.rCor         = 0x0u;
        appObj->dpcOtfCfg.grCor        = 0x1u;
        appObj->dpcOtfCfg.gbCor        = 0x0u;
        appObj->dpcOtfCfg.bCor         = 1023u;
        appObj->dpcOtfCfg.shiftValue   = 0x2u;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableGamma)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->gammaCfg,
                        0x0,
                        sizeof (appObj->gammaCfg));

        appObj->ipipeCtrl.module   = VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION;
        appObj->ipipeCtrl.gammaCfg = &appObj->gammaCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->lutFmtCnvt.moduleId    = VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION;
        appObj->lutFmtCnvt.gammaLutIn  = gamma_lut;
        appObj->lutFmtCnvt.gammaLutOut = gamma_lut;
        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
            &appObj->lutFmtCnvt,
            NULL);
        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Could not convert 3D Lut format\r\n");

            return -1;
        }

        appObj->gammaCfg.enableRed   = TRUE;
        appObj->gammaCfg.enableGreen = TRUE;
        appObj->gammaCfg.enableBlue  = TRUE;
        appObj->gammaCfg.lutRed      = gamma_lut;
        appObj->gammaCfg.lutGreen    = gamma_lut;
        appObj->gammaCfg.lutBlue     = gamma_lut;
        appObj->gammaCfg.tbl         = VPS_ISS_IPIPE_GAMMA_TBL_RAM;
        appObj->gammaCfg.tblSize     = VPS_ISS_IPIPE_GAMMA_TBL_SIZE_512;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enable3dLut)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->lut3d,
                        0x0,
                        sizeof (appObj->lut3d));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_3D_LUT;
        appObj->ipipeCtrl.colorConvert3DLutCfg = &appObj->lut3d;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        /* Convert Lut to IP expected format */
        appObj->lutFmtCnvt.moduleId    = VPS_ISS_IPIPE_MODULE_3D_LUT;
        appObj->lutFmtCnvt.lut3DRed    = lut3d_red;
        appObj->lutFmtCnvt.lut3DBlue   = lut3d_blue;
        appObj->lutFmtCnvt.lut3DGreen  = lut3d_green;
        appObj->lutFmtCnvt.out3DB0Addr = lutBankAddr[0U];
        appObj->lutFmtCnvt.out3DB1Addr = lutBankAddr[1U];
        appObj->lutFmtCnvt.out3DB2Addr = lutBankAddr[2U];
        appObj->lutFmtCnvt.out3DB3Addr = lutBankAddr[3U];
        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
            &appObj->lutFmtCnvt,
            NULL);
        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Could not convert 3D Lut format\r\n");

            return -1;
        }

        appObj->lut3d.enable = TRUE;
        appObj->lut3d.b0Addr = lutBankAddr[0U];
        appObj->lut3d.b1Addr = lutBankAddr[1U];
        appObj->lut3d.b2Addr = lutBankAddr[2U];
        appObj->lut3d.b3Addr = lutBankAddr[3U];

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableYee)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->eeCfg,
                        0x0,
                        sizeof (appObj->eeCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER;
        appObj->ipipeCtrl.eeCfg  = &appObj->eeCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->lutFmtCnvt.moduleId  = VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER;
        appObj->lutFmtCnvt.yeeLutIn  = yee_table;
        appObj->lutFmtCnvt.yeeLutOut = yee_table;
        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
            &appObj->lutFmtCnvt,
            NULL);
        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Could not convert YEE format\r\n");

            return -1;
        }

        appObj->eeCfg.enable = TRUE;
        appObj->eeCfg.method = VPS_ISS_IPIPE_EE_MERGE_METHOD_SUM;
        appObj->eeCfg.enableHaloReduction = FALSE;
        /* EDGE ENHANCER : TURN OFF THE FILTER */
        appObj->eeCfg.hpfDs           = 0;
        appObj->eeCfg.hpfMulCoeff[0u] = 0;
        appObj->eeCfg.hpfMulCoeff[1u] = 0;
        appObj->eeCfg.hpfMulCoeff[2u] = 0;
        appObj->eeCfg.hpfMulCoeff[3u] = 0;
        appObj->eeCfg.hpfMulCoeff[4u] = 0;
        appObj->eeCfg.hpfMulCoeff[5u] = 0;
        appObj->eeCfg.hpfMulCoeff[6u] = 0;
        appObj->eeCfg.hpfMulCoeff[7u] = 0;
        appObj->eeCfg.hpfMulCoeff[8u] = 0;
        appObj->eeCfg.hpfThreshold    = 0x0u;

        /* EDGE SHARPENER */
        appObj->eeCfg.gain = 128;             /* e_gain range is 1.0 -2.0 : i.e.
                                               *64 - 128 */
        appObj->eeCfg.hpfThresholdLow  = 512; /* change proportionatley
                                               * with e_gain */
        appObj->eeCfg.hpfThresholdHigh = 32;  /* always 32 */
        appObj->eeCfg.gradientGain     = (appObj->eeCfg.gain * 3) / 2;
        appObj->eeCfg.gradientOffset   = 24;  /* always 24 */

        /* Needed for Edge Enhancer */
        appObj->eeCfg.lutAddr = yee_table;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed P1 \r\n");
            return -1;
        }
        else
        {
            status = Fvid2_control(
                appObj->p2Cfg.drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &appObj->ipipeCtrl,
                NULL);
            if (FVID2_SOK != status)
            {
                BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed P2 \r\n");
                return -1;
            }
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableGic)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->gicCfg,
                        0x0,
                        sizeof (appObj->gicCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_GIC;
        appObj->ipipeCtrl.gicCfg = &appObj->gicCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->gicCfg.enable        = TRUE;
        appObj->gicCfg.type          = VPS_ISS_IPIPE_GIC_ALG_TYPE_AVERAGE;
        appObj->gicCfg.enableLscGain = FALSE;

        appObj->gicCfg.thrSel    = VPS_ISS_IPIPE_GIC_THR_SEL_GIC_REG;
        appObj->gicCfg.gain      = 64u;
        appObj->gicCfg.slope     = 64u;
        appObj->gicCfg.threshold = 32u;
        appObj->gicCfg.nfGain    = 0u;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableLsc)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->lscCfg,
                        0x0,
                        sizeof (appObj->lscCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_LSC;
        appObj->ipipeCtrl.lscCfg = &appObj->lscCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->lscCfg.vertOffset   = 0x0U;
        appObj->lscCfg.horzLinCoeff = 0xFFFFF175U;
        appObj->lscCfg.horzQdrCoeff = 2293U;
        appObj->lscCfg.horzLinShift = 13U;
        appObj->lscCfg.horzQdrShift = 10U;
        appObj->lscCfg.vertLinCoeff = 0xFFFFF572U;
        appObj->lscCfg.vertQdrCoeff = 2376U;
        appObj->lscCfg.vertLinShift = 13U;
        appObj->lscCfg.vertQdrShift = 10U;
        appObj->lscCfg.horzOffset   = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_R]    = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_GR]   = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_GB]   = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_B]    = 0x0U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_R]  = 64U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_GR] = 0U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_GB] = 0U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_B]  = 64U;
        appObj->lscCfg.shift = 9U;
        appObj->lscCfg.max   = 511U;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableNf1)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->nf1Cfg,
                        0x0,
                        sizeof (appObj->nf1Cfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_NF1;
        appObj->ipipeCtrl.nf1Cfg = &appObj->nf1Cfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->nf1Cfg.enable        = FALSE;;
        appObj->nf1Cfg.grPixType     = VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX;
        appObj->nf1Cfg.enableLscGain = FALSE;
        appObj->nf1Cfg.useLutSpr     = FALSE;
        appObj->nf1Cfg.downShift     = 2U;
        appObj->nf1Cfg.spreadVal     = 3U;
        appObj->nf1Cfg.threshold[0U] = 11U;
        appObj->nf1Cfg.threshold[1U] = 16U;
        appObj->nf1Cfg.threshold[2U] = 21U;
        appObj->nf1Cfg.threshold[3U] = 27U;
        appObj->nf1Cfg.threshold[4U] = 32U;
        appObj->nf1Cfg.threshold[5U] = 37U;
        appObj->nf1Cfg.threshold[6U] = 42U;
        appObj->nf1Cfg.threshold[7U] = 47U;

        for (cnt = 0U; cnt < VPS_ISS_IPIPE_NF2_MAX_THR; cnt++)
        {
            appObj->nf1Cfg.intensity[cnt] = 31U;
            appObj->nf1Cfg.sprFactor[cnt] = 3U;
        }

        appObj->nf1Cfg.edgeMin = 0x0U;
        appObj->nf1Cfg.edgeMax = 0x0U;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gLpbkAppM2mWdrObj.enableNf2)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->nf2Cfg,
                        0x0,
                        sizeof (appObj->nf2Cfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_NF2;
        appObj->ipipeCtrl.nf2Cfg = &appObj->nf2Cfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->nf2Cfg.enable        = FALSE;;
        appObj->nf2Cfg.grPixType     = VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX;
        appObj->nf2Cfg.enableLscGain = FALSE;
        appObj->nf2Cfg.useLutSpr     = FALSE;
        appObj->nf2Cfg.downShift     = 2U;
        appObj->nf2Cfg.spreadVal     = 3U;
        appObj->nf2Cfg.threshold[0U] = 26U;
        appObj->nf2Cfg.threshold[1U] = 38U;
        appObj->nf2Cfg.threshold[2U] = 50U;
        appObj->nf2Cfg.threshold[3U] = 62U;
        appObj->nf2Cfg.threshold[4U] = 74U;
        appObj->nf2Cfg.threshold[5U] = 86U;
        appObj->nf2Cfg.threshold[6U] = 98U;
        appObj->nf2Cfg.threshold[7U] = 110U;

        for (cnt = 0U; cnt < VPS_ISS_IPIPE_NF2_MAX_THR; cnt++)
        {
            appObj->nf2Cfg.intensity[cnt] = 31U;
            appObj->nf2Cfg.sprFactor[cnt] = 3U;
        }

        appObj->nf2Cfg.edgeMin = 0x0U;
        appObj->nf2Cfg.edgeMax = 0x0U;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }
    return (status);
}

static Int32 LpbkApp_m2mWdrSetNsf3vConfig(LpbkApp_m2mWdrObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->nsf3vCfg,
                    0x0,
                    sizeof (vpsissNsf3Config_t));

    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_NSF3_IOCTL_GET_CONFIG,
        &appObj->nsf3vCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: NSF3v GetConfig Failed\r\n");

        return -1;
    }

    appObj->nsf3vCfg.bypass = FALSE;
    appObj->nsf3vCfg.enableBorderReplicate = TRUE;

    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_NSF3_IOCTL_SET_CONFIG,
        &appObj->nsf3vCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: NSF3v GetConfig Failed\r\n");

        return -1;
    }

    return (status);
}

static int32_t LpbkApp_m2mWdrSetGlbceConfig(LpbkApp_m2mWdrObj *appObj)
{
    int32_t status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->glbceCfg,
                    0x0,
                    sizeof (vpsissGlbceConfig_t));

    appObj->glbceCtrl.module   = VPS_ISS_GLBCE_MODULE_GLBCE;
    appObj->glbceCtrl.glbceCfg = &appObj->glbceCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    BspUtils_memcpy(&appObj->glbceCfg, &gGlbceCfg, sizeof (vpsissGlbceConfig_t));
    appObj->glbceCfg.enable = TRUE;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->perCfg,
                    0x0,
                    sizeof (vpsissGlbcePerceptConfig_t));

    appObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_FWD_PERCEPT;
    appObj->glbceCtrl.fwdPrcptCfg = &appObj->perCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    BspUtils_memcpy(
        &appObj->perCfg,
        &gGlbceFwbPerCfg,
        sizeof (vpsissGlbcePerceptConfig_t));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->perCfg,
                    0x0,
                    sizeof (vpsissGlbcePerceptConfig_t));

    appObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_REV_PERCEPT;
    appObj->glbceCtrl.revPrcptCfg = &appObj->perCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    BspUtils_memcpy(
        &appObj->perCfg,
        &gGlbceRevPerCfg,
        sizeof (vpsissGlbcePerceptConfig_t));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }
    return (status);
}

static Int32 LpbkApp_m2mWdrSetCnfConfig(LpbkApp_m2mWdrObj *appObj)
{
    Int32 status = FVID2_SOK;
    vpsissNsf3Config_t *nsf3Cfg;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->cnfCfg,
                    0x0,
                    sizeof (vpsissCnfConfig_t));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_CNF_IOCTL_GET_CONFIG,
        &appObj->cnfCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: CNF GetConfig Failed\r\n");

        return -1;
    }

    nsf3Cfg = &appObj->cnfCfg.nsf3Cfg;
    appObj->cnfCfg.enable    = TRUE;
    appObj->cnfCfg.enableCds = FALSE;
    BspUtils_memcpy(
        nsf3Cfg,
        &gIssHalNsf3DefCfg_Cnf,
        sizeof (vpsissNsf3Config_t));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_CNF_IOCTL_SET_CONFIG,
        &appObj->cnfCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: CNF GetConfig Failed\r\n");

        return -1;
    }

    return (status);
}

static Int32 LpbkApp_m2mWdrSetRszConfig(
    LpbkApp_m2mWdrObj *appObj,
    UInt32             isPass2)
{
    Int32 status;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->rszCfg,
                    0x0,
                    sizeof (vpsissRszCfg_t));
    BspUtils_memset(&appObj->rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));

    if (FALSE == isPass2)
    {
        appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
        appObj->rszCtrl.rszCfg = &appObj->rszCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_GET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Resizer GetConfig Failed\r\n");

            return -1;
        }

        appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_BYPASS;
        appObj->rszCfg.inCfg.procWin.cropStartX = 0u;
        appObj->rszCfg.inCfg.procWin.cropStartY = 0u;
        appObj->rszCfg.inCfg.procWin.cropWidth  = appObj->inFmt.width;
        appObj->rszCfg.inCfg.procWin.cropHeight = appObj->inFmt.height;

        appObj->rszCfg.instCfg[0U].enable = 1U;
        appObj->rszCfg.instCfg[0U].outFmt = appObj->inFmt;

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
            appObj->p1Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_SET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: RSZ SetConfig Failed\r\n");
            return -1;
        }
    }
    else
    {
        appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
        appObj->rszCtrl.rszCfg = &appObj->rszCfg;

        status = Fvid2_control(
            appObj->p2Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_GET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Resizer GetConfig Failed\r\n");

            return -1;
        }

        appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
        appObj->rszCfg.inCfg.procWin.cropStartX = 0u;
        appObj->rszCfg.inCfg.procWin.cropStartY = 0u;
        appObj->rszCfg.inCfg.procWin.cropWidth  = appObj->inFmt.width;
        appObj->rszCfg.inCfg.procWin.cropHeight = appObj->inFmt.height;

        appObj->rszCfg.instCfg[0U].outFmt = appObj->outFmt;

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

        appObj->rszCfg.instCfg[0u].intensityCfg.horzLumaIntensity   = 21u;
        appObj->rszCfg.instCfg[0u].intensityCfg.horzChromaIntensity = 22u;
        appObj->rszCfg.instCfg[0u].intensityCfg.vertLumaIntensity   = 14u;
        appObj->rszCfg.instCfg[0u].intensityCfg.vertChromaIntensity = 15u;

        status = Fvid2_control(
            appObj->p2Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_SET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: RSZ SetConfig Failed\r\n");
            return -1;
        }
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mWdrSetIsifLscConfig(
    LpbkApp_m2mWdrObj *appObj)
{
    Int32 status;
    vpsissIsif2DLscConfig_t *lscCfg;

    BspUtils_memset(&appObj->isifCtrl, 0x0, sizeof (vpsissIsifCtrl_t));
    BspUtils_memset(&appObj->isifLscCfg, 0x0, sizeof (vpsissIsif2DLscConfig_t));

    appObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_2D_LSC;
    appObj->isifCtrl.lscCfg = &appObj->isifLscCfg;

    lscCfg = &appObj->isifLscCfg;

    /* Get the ISIF Default Configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_ISIF_IOCTL_GET_CONFIG,
        &appObj->isifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: ISIF GetLscConfig Failed\r\n");

        return -1;
    }

    lscCfg->enable = FALSE;

    lscCfg->activeReg.cropStartX = 0;
    lscCfg->activeReg.cropStartY = 0;
    lscCfg->activeReg.cropWidth  = 640;
    lscCfg->activeReg.cropHeight = 480;
    lscCfg->startPos.startX      = 0;
    lscCfg->startPos.startY      = 0;

    lscCfg->horzDownScale = VPS_ISS_ISIF_2D_LSC_DS_128;
    lscCfg->vertDownScale = VPS_ISS_ISIF_2D_LSC_DS_128;
    lscCfg->gainFormat    = VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q8;

    lscCfg->gainTableAddr    = 0x80000000;
    lscCfg->offsetTableAddr  = 0x80000000;
    lscCfg->gainTablePitch   = 368;
    lscCfg->offsetTablePitch = 368;

    lscCfg->enableOffset      = 1;
    lscCfg->offsetScaleFactor = 0x80;
    lscCfg->offsetShiftup     = VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_1;

    /* Set the ISIF Changed configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_ISIF_IOCTL_SET_CONFIG,
        &appObj->isifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: ISIF SetConfig Failed\r\n");
        return -1;
    }

    return (status);
}

static Int32 LpbkApp_m2mWdrSetIsifConfig(
    LpbkApp_m2mWdrObj *appObj,
    UInt32             ispass2)
{
    Int32  status;
    UInt32 outCnt;
    UInt32 colorCnt, enableGainOffset;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->isifWbCfg,
                    0x0,
                    sizeof (vpsissIsifGainOfstConfig_t));
    BspUtils_memset(&appObj->isifCtrl, 0x0, sizeof (vpsissIsifCtrl_t));

    appObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_WB;
    appObj->isifCtrl.wbCfg  = &appObj->isifWbCfg;

    /* Get the ISIF Default Configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_ISIF_IOCTL_GET_CONFIG,
        &appObj->isifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: ISIF GetConfig Failed\r\n");

        return -1;
    }

    if (TRUE == ispass2)
    {
        enableGainOffset = FALSE;
    }
    else
    {
        enableGainOffset = TRUE;
    }

    enableGainOffset = TRUE;

    /* Enable Gains and Offsets for all three outputs */
    for (outCnt = 0u; outCnt < VPS_ISS_ISIF_MAX_OUTPUT; outCnt++)
    {
        appObj->isifWbCfg.gainEnable[outCnt]   = enableGainOffset;
        appObj->isifWbCfg.offsetEnable[outCnt] = enableGainOffset;
    }

    /* Setting gains to unit */
    for (colorCnt = 0u; colorCnt < FVID2_BAYER_COLOR_COMP_MAX; colorCnt++)
    {
        appObj->isifWbCfg.gain[colorCnt] = 512;
    }

    /* Setting Offset to 0 */
    appObj->isifWbCfg.offset = 0x0u;

    /* Set the ISIF Changed configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_ISIF_IOCTL_SET_CONFIG,
        &appObj->isifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: ISIF SetConfig Failed\r\n");
        return -1;
    }

    /* TODO: Remove this hard coding once support for blank clamping is
     *       added in isif */
    if (TRUE == ispass2)
    {
        appObj->isifBlkClampCfg.dcOffset = 0x1F81U;
    }
    else
    {
        if (appObj->evRatio < 128)
            appObj->isifBlkClampCfg.dcOffset = (128 / appObj->expRatio) * (-1);
        else
            appObj->isifBlkClampCfg.dcOffset = 0;
    }

    /* apply DC Offset at ISIF */
    appObj->isifCtrl.module      = VPS_ISS_ISIF_MODULE_BLACK_CLAMP;
    appObj->isifCtrl.blkClampCfg = &appObj->isifBlkClampCfg;
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_ISIF_IOCTL_SET_CONFIG,
        &appObj->isifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: ISIF Set Black Clamp Config Failed\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 LpbkApp_m2mWdrSetH3aParams(LpbkApp_m2mWdrObj *appObj)
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
        appObj->p2Cfg.drvHandle,
        VPS_ISS_H3A_IOCTL_GET_CONFIG,
        &appObj->h3aCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: H3A GetConfig Failed\r\n");

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
        appObj->p2Cfg.drvHandle,
        VPS_ISS_H3A_IOCTL_SET_CONFIG,
        &appObj->h3aCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: H3A SetConfig Failed\r\n");
        return -1;
    }

    BspUtils_memset(&gLpbkAppM2mWdrObj.image, 0x0,
                    sizeof (gLpbkAppM2mWdrObj.image));
    IDH_createImage(
        &gLpbkAppM2mWdrObj.image,
        appObj->aewbCfg.winCfg.horzCount,
        appObj->aewbCfg.winCfg.vertCount,
        24,
        1);
    return (status);
}

static void LpbkApp_m2mWdrCreateImageData(LpbkApp_m2mWdrObj *appObj)
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

    curAewbAddr = (Char *) gLpbkAppM2mWdrObj.frames[1u].addr[0u][0u];
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

static void LpbkApp_m2mWdrSetAewbGains(LpbkApp_m2mWdrObj *appObj)
{
    Int32 status = FVID2_SOK;

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &appObj->wbCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");
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
        appObj->p2Cfg.drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");
    }
}

static void LpbkApp_m2mWdrSetIpipeifAewbGains(LpbkApp_m2mWdrObj *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 idx, cnt;

    BspUtils_memset(&appObj->wdrCfg, 0x0, sizeof (appObj->wdrCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG;
    appObj->ipipeifCtrl.pWdrCfg = &gWdrCfg;

    for (cnt = 0U; cnt < FVID2_BAYER_COLOR_COMP_MAX; cnt++)
    {
        idx = Fvid2_BayerColorIndex(
            gLpbkAppM2mWdrObj.inFmt.dataFormat,
            cnt);

        /* Algorithm returns only three gains, R G and B.
         * For Gr and Gb, need to use same index */
        if (idx >= 2)
        {
            idx--;
        }

        gWdrCfg.lwb[cnt] =
            (appObj->longWbPrms.gainOffset.gainFactors[idx] * 512U);
        gWdrCfg.swb[cnt] =
            (appObj->longWbPrms.gainOffset.gainFactors[idx] * 512U);
    }

    /* Set the changed configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set WDR Config Failed\r\n");
        return;
    }
}

#if 0
static void CalcBlendFact(float T, float V, UInt32 *afe, UInt32 *afm,
                          UInt32 *af)
{
    float a, b;
    int   K, temp, temp1;

    *afm = -26420;
    *afe = 24;
    *af  = 460;

    a    = (2 - 4 * V) / (T * T);
    b    = (4 * V - 1) / T;
    K    = 0;
    temp = abs(a * (Power2(K)));
    while (temp < 1)
    {
        K    = K + 1;
        temp = abs(a * (Power2(K)));
    }

    K     = K - 1;
    temp1 = Power2(K);
    a     = a * temp1;
    temp1 = Power2(15);
    a     = a * temp1;

    if ((UInt32) a & 0x80000000)
    {
        *afm = (UInt32) (a * (-1));
    }
    else
    {
        *afm = (int) (a);
    }
    *afe = (int) (K);
    *af  = (int) (b * (Power2(5)) * (Power2(15)));
}

#endif

static Int32 Power2(Int32 k)
{
    UInt32 i;
    Int32  t = 1;
    for (i = 0; i < k; i++)
        t *= 2;

    return (t);
}

