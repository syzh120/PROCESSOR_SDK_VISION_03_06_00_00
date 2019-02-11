/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2017
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
 *  \file IssIntf_display.c
 *
 *  \brief DSS display application.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <Loopback_main.h>
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif

#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_lcdController.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DISPLAY_RUN_TEST_ID     (0U)

/* Flag used to set in test params input width and height so that the detected
 * LCD width and height is used. This is kept same as LCD width/height so
 * that the same code works for Zebu as well */
#define DISP_APP_USE_LCD_WIDTH          (800U)
#define DISP_APP_USE_LCD_HEIGHT         (480U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct LpbkApp_dispObj_t LpbkApp_dispObj;

/**
 *  \brief Display application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    Char            *testDescStr;
    /**< Test description. */

    UInt32           numEnc;
    /**< Number of Video Encoders to run with. */
    UInt32           encDrvId[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder driver ID to open for each handle. */
    UInt32           vencId[VPS_DISP_ENC_INST_MAX];
    /**< Venc ID for each handle. */
    Fvid2_Standard   standard[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder video standard. */

    UInt32           numHandles;
    /**< Number of display handles to run with. */
    UInt32           instId[VPS_DISP_INST_MAX];
    /**< Instance ID to open for each handle. */

    Fvid2_DataFormat inDataFmt[VPS_DISP_INST_MAX];
    /**< YUV or RGB data format. */

    UInt32           inWidth[VPS_DISP_INST_MAX];
    /**< Input buffer resolution width in pixels. */
    UInt32           inHeight[VPS_DISP_INST_MAX];
    /**< Input buffer resolution height in lines. */
    UInt32           posx[VPS_DISP_INST_MAX];
    /**< Input buffer position x. */
    UInt32           posy[VPS_DISP_INST_MAX];
    /**< Input buffer position y. */
    UInt32           inScanFormat[VPS_DISP_INST_MAX];
    /**< In scan format. */
    UInt32           isFieldMerge[VPS_DISP_INST_MAX];
    /**< Field merge or field separated. */
    Int32            runCount;
    /**< Number of frames to display. */
    Bsp_BoardMode    boardMode;
    /**< Board mode param like 24-bit, 8-bit. */
    UInt32           displayPitch;
    /**< Display pitch */
} LpbkApp_dispTestPrms;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32                     instId;
    /**< Instance ID. */
    UInt32                     encDrvId;
    /**< Encoder driver ID. */

    Vps_DispCreateParams       createPrms;
    /**< Create time parameters. */
    Vps_DispCreateStatus       createStatus;
    /**< Create status returned by driver during Fvid2_create(). */

    Vps_DispDssParams          dssPrms;
    /**< DSS driver parameters. */
    Vps_DssDispcVidConfig      vidCfg;
    /**< DSS video configuration. */
    Vps_DssDispcGfxConfig      gfxCfg;
    /**< DSS graphics configuration. */

    Fvid2_Handle               drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams             cbPrms;
    /**< Callback params. */

    Vps_DssDispcOvlyPipeConfig ovlpipeconfig;
    /** <Pipe Config. */

    UInt32                     pitch[FVID2_MAX_PLANES];
    /**< Buffer pitch - used for buffer allocation for this instance. */

    UInt32                     isFieldMerge;
    /**< Field merge or field separated. */

    UInt32                     inWidth;
    /**< Input buffer resolution width in pixels. */

    UInt32                     inHeight;
    /**< Input buffer resolution height in lines. */

    Fvid2_DataFormat           inDataFmt;
    /**< YUV or RGB data format. */

    UInt32                     posx;
    /**< Input buffer position x. */

    UInt32                     posy;
    /**< Input buffer position y. */

    UInt32                     inScanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    Fvid2_Handle               encHandle;
    /**< FVID2 encoder driver handle. */
    /* Bsp_VidEncCreateParams    encCreatePrms; */
    /**< Video encoder create params. */
    /* Bsp_VidEncVideoModeParams encVideoModePrms; */
    /**< Video encoder mode params. */

    LpbkApp_dispObj           *appObj;
    /**< Reference pointer to application common object. */

    Fvid2_FrameList            frmList;
    /**< Frame List used for queueing and dequeuing frames to the driver */
} DispApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct LpbkApp_dispObj_t
{
    DispApp_InstObj             instObj[VPS_DISP_INST_MAX];
    /**< Driver instance objects. */
    LpbkApp_dispTestPrms          testPrms;
    /**< Current test parameters. */

    Fvid2_Handle                dctrlHandle;
    /**< DCTRL handle. */

    Fvid2_Handle                hdmiHandle;
    /**< Off-Chip HDMI handle. */

    Vps_DctrlConfig             dctrlCfg;
    /**< DCTRL path config. */

    Vps_DssDispcOvlyPanelConfig panelCfg;
    /** <Panel Config. */

    Bsp_LcdCtrlCreateParams     lcdCtrlCreatePrms;
    /** <LCD controller Create params. */

    Fvid2_Handle                lcdCtrlhdl;
    /**< LCD controller Driver handle. */
    Bsp_LcdCtrlPanelInfo        lcdPanelInfo;
    /**< LCD panel timing data. */

    UInt32                      maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                      maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32                      callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */

    UInt32                      startTime;
    /**< Application start time in clock ticks. */

    Semaphore_Handle           *semHandle;
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void LpbkApp_dispInit(LpbkApp_dispObj *appObj);
static void LpbkApp_dispDeInit(LpbkApp_dispObj *appObj);
static void LpbkApp_dispCreateDriver(LpbkApp_dispObj *appObj);
static void LpbkApp_dispInitParams(LpbkApp_dispObj *appObj);
static void LpbkApp_dispConfigLcd(LpbkApp_dispObj *appObj);
static void LpbkApp_dispTurnOffLcd(LpbkApp_dispObj *appObj);
static Int32 LpbkApp_dispConfigPllAndClkSrc(
    LpbkApp_dispObj *appObj,
    UInt32 pixelClk);
static Int32 LpbkApp_dispConfigDctrlPipe(LpbkApp_dispObj *appObj);
static Int32 LpbkApp_dispConfigDctrl(LpbkApp_dispObj *appObj);
static Int32 LpbkApp_dispConfigOffChipHdmi(
    LpbkApp_dispObj *appObj,
    UInt32 encInst);
static Int32 LpbkApp_dispDeConfigOffChipHdmi(
    LpbkApp_dispObj *appObj,
    UInt32 encInst);
static Int32 LpbkApp_dispCallback(
    Fvid2_Handle handle,
    Ptr appData,
    Ptr reserved);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const LpbkApp_dispTestPrms gLpbkAppDispTestPrms[] =
{
    {       /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_CUSTOM,
        },
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV420SP_UV,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        0,
        BSP_BOARD_MODE_VIDEO_24BIT     /* boardMode */
    },
    {       /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI->Sil9022a-HDMI)@ (720P)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_720P_60,
        },
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV420SP_UV,
        },
        {
            /* inWidth */
            1280U,
        },
        {
            /* inHeight */
            720U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        0,
        BSP_BOARD_MODE_VIDEO_24BIT         /* boardMode */
    }
};

/* Test application object */
static LpbkApp_dispObj gDispAppObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void LpbkApp_dispCreate(LpbkApp_testCfg *testCfg, Semaphore_Handle *semHandle)
{
    LpbkApp_dispObj *appObj = &gDispAppObj;

    if (TRUE == testCfg->hdmiLcdDisplay)
    {
        BspUtils_memcpy(
            &appObj->testPrms,
            &gLpbkAppDispTestPrms[1U],
            sizeof(appObj->testPrms));
    }
    else
    {
        BspUtils_memcpy(
            &appObj->testPrms,
            &gLpbkAppDispTestPrms[0U],
            sizeof(appObj->testPrms));
    }

    /* Copy display parameters to test Params */
    appObj->testPrms.inDataFmt[0U] = (Fvid2_DataFormat)testCfg->outDataFormat;
    appObj->testPrms.displayPitch = testCfg->outPitch;

    appObj->semHandle = semHandle;

    /* Initialize Display Object */
    LpbkApp_dispInit(appObj);

    /* Create driver */
    LpbkApp_dispCreateDriver(appObj);
}

void LpbkApp_dispPutFrames(
    UInt32       handleId,
    UInt32       numFrames,
    Fvid2_Frame *frames[])
{
    Int32            status = FVID2_SOK;
    UInt32           frmCnt;
    LpbkApp_dispObj     *appObj  = &gDispAppObj;
    DispApp_InstObj *instObj = &appObj->instObj[handleId];

    Fvid2FrameList_init(&instObj->frmList);

    instObj->frmList.numFrames = 1U;
    for(frmCnt = 0U; frmCnt < numFrames; frmCnt++)
    {
        instObj->frmList.frames[0U] = frames[frmCnt];
        frames[frmCnt]->chNum       = 0U;

        status = Fvid2_queue(instObj->drvHandle, &instObj->frmList, 0U);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Queue Failed!!!\r\n");
            GT_assert(BspAppTrace, FALSE);
        }
    }
}

void LpbkApp_dispGetFrames(
    UInt32       handleId,
    UInt32      *numFrames,
    Fvid2_Frame *frames[])
{
    Int32            status = FVID2_SOK;
    UInt32           frmCnt;
    LpbkApp_dispObj     *appObj  = &gDispAppObj;
    DispApp_InstObj *instObj = &appObj->instObj[handleId];

    Fvid2FrameList_init(&instObj->frmList);

    status = Fvid2_dequeue(
        instObj->drvHandle,
        &instObj->frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if(FVID2_SOK == status)
    {
        for(frmCnt = 0U; frmCnt < instObj->frmList.numFrames; frmCnt++)
        {
            frames[frmCnt] = instObj->frmList.frames[frmCnt];
        }
        *numFrames = instObj->frmList.numFrames;
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Dequeue Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }
}

void LpbkApp_dispStart(void)
{
    Int32            status = FVID2_SOK;
    UInt32           instCnt;
    LpbkApp_dispObj     *appObj  = &gDispAppObj;
    DispApp_InstObj *instObj = NULL;

    /* Start driver */
    for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        status = Fvid2_start(instObj->drvHandle, NULL);
        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Start Failed!!!\r\n");
            GT_assert(BspAppTrace, FALSE);
        }
    }
}

void LpbkApp_dispStop(void)
{
    Int32            status = FVID2_SOK;
    UInt32           instCnt;
    LpbkApp_dispObj     *appObj  = &gDispAppObj;
    DispApp_InstObj *instObj = NULL;

    /* Stop driver */
    for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        status  = Fvid2_stop(instObj->drvHandle, NULL);
        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Stop Failed!!!\r\n");
            GT_assert(BspAppTrace, FALSE);
        }
    }
}

void LpbkApp_dispClose(void)
{
    Int32            status;
    UInt32           instCnt, encInst;
    LpbkApp_dispObj     *appObj = &gDispAppObj;
    DispApp_InstObj *instObj;
    Fvid2_FrameList  frmList;
    Vps_DctrlConfig *dctrlCfg;

    dctrlCfg = &appObj->dctrlCfg;

    status = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        NULL);

    /* Turn Off the Video Encoders/LCD controllers if required */
    for(encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        if(appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
        {
            /* Turn off LCD controller only if platform is EVM */
            if(BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                LpbkApp_dispTurnOffLcd(appObj);
            }
        }
        else if(appObj->testPrms.encDrvId[encInst] ==
                FVID2_VID_ENC_SII9022A_DRV)
        {
            /* DeConfigure Video Encoder only if platform is EVM */
            if(BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                status = LpbkApp_dispDeConfigOffChipHdmi(appObj, encInst);
                if(FVID2_SOK != status)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": Error: DeConfiguring off-chip \
                               HDMI failed!!\r\n");
                }
            }
        }
        else
        {
            /* Do nothing */
        }
    }

    for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Dequeue all the request from the driver */
        while(1U)
        {
            status = Fvid2_dequeue(
                instObj->drvHandle,
                &frmList,
                0U,
                FVID2_TIMEOUT_NONE);
            if(FVID2_SOK != status)
            {
                break;
            }
        }

        status = Fvid2_delete(instObj->drvHandle, NULL);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Delete Failed!!!\r\n");
            break;
        }
    }
    if(FVID2_SOK == status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Display delete complete!!\r\n");
    }

    LpbkApp_dispDeInit(appObj);

    return;
}

static void LpbkApp_dispInit(LpbkApp_dispObj *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 defPixelClk;

    /* Create DCTRL handle, used for common driver configuration */
    appObj->dctrlHandle = Fvid2_create(
        FVID2_VPS_DCTRL_DRV,
        VPS_DCTRL_INST_0,
        NULL,                       /* NULL for VPS_DCTRL_INST_0 */
        NULL,                       /* NULL for VPS_DCTRL_INST_0 */
        NULL);                      /* NULL for VPS_DCTRL_INST_0 */
    if(NULL == appObj->dctrlHandle)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Create Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }

    if(FVID2_SOK == status)
    {
        if(BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
        {
            /* Set default video PLL clock */
            defPixelClk = 29232U * 4U;

            /* No Internal Dividers present in DSS in Tda3xx platform,
                so default it to 29232 itself. */
            if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
            {
                defPixelClk = 29232U;
            }

            LpbkApp_dispConfigPllAndClkSrc(appObj, defPixelClk);
        }

        status = Bsp_platformEnableHdmiPll(TRUE);
        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Enabling HDMI PLL Failed!!!\r\n");
            GT_assert(BspAppTrace, FALSE);
        }
    }
    if(FVID2_SOK == status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_dispInit() - DONE !!!\r\n");
    }

    return;
}

static void LpbkApp_dispDeInit(LpbkApp_dispObj *appObj)
{
    Int32 status = FVID2_SOK;

    /* Delete DCTRL handle */
    status = Fvid2_delete(appObj->dctrlHandle, NULL);
    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL handle delete failed!!!\r\n");
    }

    if(FVID2_SOK == status)
    {
        status = Bsp_platformEnableHdmiPll(FALSE);
        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Disabling HDMI PLL Failed!!!\r\n");
        }
    }

    if(FVID2_SOK == status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_dispDeInit() - DONE !!!\r\n");
    }

    return;
}

static void LpbkApp_dispCreateDriver(LpbkApp_dispObj *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 instCnt, encInst;
    DispApp_InstObj      *instObj;
    Bsp_LcdCtrlPanelInfo *lcdPanelInfo;

    LpbkApp_dispInitParams(appObj);


    /* Configure the Video Encoders/LCD controllers if required */
    for(encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        /* For J6 Entry change the default venc from LCD1 to LCD3. */
    #if defined (SOC_TDA2EX)
        if ((Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_17x17) &&
            (appObj->testPrms.vencId[encInst] == VPS_DCTRL_DSS_VENC_LCD1))
        {
            appObj->testPrms.vencId[encInst] = VPS_DCTRL_DSS_VENC_LCD3;
        }
    #endif
        if(appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
        {
            /* Configure LCD only if platform is EVM */
            if(BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                LpbkApp_dispConfigLcd(appObj);
            }
            else
            {
                /* Set some default modes so that test case runs in Zebu */
                lcdPanelInfo = &appObj->lcdPanelInfo;
                Fvid2ModeInfo_init(&lcdPanelInfo->modeInfo);
                lcdPanelInfo->modeInfo.standard    = FVID2_STD_CUSTOM;
                lcdPanelInfo->modeInfo.width       = 1280U;
                lcdPanelInfo->modeInfo.height      = 720U;
                lcdPanelInfo->modeInfo.scanFormat  = FVID2_SF_PROGRESSIVE;
                lcdPanelInfo->modeInfo.pixelClock  = 29232U;
                lcdPanelInfo->modeInfo.fps         = 60U;
                lcdPanelInfo->modeInfo.hBackPorch  = 148U;
                lcdPanelInfo->modeInfo.hSyncLen    = 44U;
                lcdPanelInfo->modeInfo.hFrontPorch = 88U;
                lcdPanelInfo->modeInfo.vBackPorch  = 15U;
                lcdPanelInfo->modeInfo.vSyncLen    = 5U;
                lcdPanelInfo->modeInfo.vFrontPorch = 2U;

                lcdPanelInfo->videoIfWidth    = FVID2_VIFW_24BIT;
                lcdPanelInfo->videoDataFormat = FVID2_DF_RGB24_888;
                lcdPanelInfo->videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                lcdPanelInfo->vsPolarity       = FVID2_POL_HIGH;
                lcdPanelInfo->hsPolarity       = FVID2_POL_HIGH;
                lcdPanelInfo->actVidPolarity   = FVID2_POL_HIGH;
                lcdPanelInfo->fidPolarity      = FVID2_POL_HIGH;
                lcdPanelInfo->pixelClkPolarity = FVID2_POL_HIGH;
            }
        }
        else if(appObj->testPrms.encDrvId[encInst] ==
                FVID2_VID_ENC_SII9022A_DRV)
        {
            /* Configure Video Encoder only if platform is EVM */
            if(BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                status = LpbkApp_dispConfigOffChipHdmi(appObj, encInst);
                if(status != FVID2_SOK)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": COnfiguring Off-Chip HDMI Failed !!!\r\n");
                    status = FVID2_SOK;
                }
            }
        }
    }

    LpbkApp_dispConfigDctrl(appObj);

    for(encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        if((status == FVID2_SOK) &&
           (appObj->testPrms.encDrvId[encInst] ==
                FVID2_VID_ENC_SII9022A_DRV))
        {
            status = Fvid2_start(appObj->hdmiHandle, NULL);
            if(FVID2_SOK != status)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                        APP_NAME ": Error: Off-chip HDMI start failed!!\r\n");
            }
        }
    }

    GT_assert(BspAppTrace, appObj->testPrms.numHandles < VPS_DISP_INST_MAX);
    for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->drvHandle = Fvid2_create(
            FVID2_VPS_DISP_DRV,
            instObj->instId,
            &instObj->createPrms,
            &instObj->createStatus,
            &instObj->cbPrms);
        if((NULL == instObj->drvHandle) ||
           (instObj->createStatus.retVal != FVID2_SOK))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Create Failed!!!\r\n");
            status = instObj->createStatus.retVal;
        }

        if(FVID2_SOK == status)
        {
            /* BspUtils_appPrintDispCreateStatus(&instObj->createStatus); */

            status = Fvid2_control(
                instObj->drvHandle,
                IOCTL_VPS_DISP_SET_DSS_PARAMS,
                &instObj->dssPrms,
                NULL);
            if(status != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": DSS Set Params IOCTL Failed!!!\r\n");
            }
        }

        if(FVID2_SOK != status)
        {
            break;
        }
    }

    if(FVID2_SOK == status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Display create complete!!\r\n");
    }

    return;
}

static Int32 LpbkApp_dispConfigPllAndClkSrc(
    LpbkApp_dispObj *appObj,
    UInt32 pixelClk)
{
    Bsp_PlatformSetPllFreq vPllCfg;
    Bsp_PlatformVencSrc    vencClkCfg;
    Int32 retVal = FVID2_SOK;

    vPllCfg.videoPll = BSP_PLATFORM_PLL_VIDEO1;
    vPllCfg.pixelClk = pixelClk;
    vPllCfg.chooseMaxorMinMN = (UInt32) BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN;

    if(TRUE == Bsp_platformIsTda3xxFamilyBuild())
    {
        vPllCfg.videoPll = BSP_PLATFORM_PLL_EVE_VID_DSP;
    }

    retVal = Bsp_platformSetPllFreq(&vPllCfg);
    if(retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Configuring Pll Failed!!!\r\n");
    }

    if(FVID2_SOK == retVal)
    {
        if (appObj->testPrms.vencId[0U] == VPS_DCTRL_DSS_VENC_LCD3)
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD3;
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3;
        }
        else
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD1;
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT1;
        }

        if(TRUE == Bsp_platformIsTda3xxFamilyBuild())
        {
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_EVE_VID_DSP;
        }

        retVal = Bsp_platformSetVencClkSrc(&vencClkCfg);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Setting Venc clock source Failed!!!\r\n");
        }
    }

    return retVal;
}

static Int32 LpbkApp_dispConfigDctrl(LpbkApp_dispObj *appObj)
{
    Int32                        status = FVID2_SOK;
    Vps_DctrlConfig             *dctrlCfg;
    Vps_DssDispcOvlyPanelConfig *panelCfg;
    Fvid2_ModeInfo              *mInfo;
    Vps_DctrlVencDivisorInfo     vencDivisors;
    Vps_DctrlOutputInfo vencInfo;
    UInt32                       pixelClk, instCnt;
    DispApp_InstObj             *instObj;
    Vps_DssDispcAdvLcdTdmConfig  advTdmPrms;

    dctrlCfg           = &appObj->dctrlCfg;
    VpsDctrlConfig_init(dctrlCfg);
    dctrlCfg->useCase  = VPS_DCTRL_USERSETTINGS;
    dctrlCfg->numEdges = 0U;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
    if(appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
    {
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_OUTPUT;
        dctrlCfg->numEdges++;

        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_HDMI;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[0U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.standard[0U];
    }
#endif

    if(appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1)
    {
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;
#endif

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_DPI1_OUTPUT;
        dctrlCfg->numEdges++;

        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD1;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[1U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.standard[0U];
    }

    if(appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)
    {
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;
#endif

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_DPI3_OUTPUT;
        dctrlCfg->numEdges++;

        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD3;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[1U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.standard[0U];
    }

    dctrlCfg->vencInfo.numVencs = 1U;

    mInfo = &dctrlCfg->vencInfo.modeInfo[0U].mInfo;
    if(FVID2_STD_CUSTOM == appObj->testPrms.standard[0U])
    {
        if((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
           (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
           (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
        {
            /* Configure custom timings */
            BspUtils_memcpy(
                mInfo, &appObj->lcdPanelInfo.modeInfo, sizeof(Fvid2_ModeInfo));
        }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        if(appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
        {
            /* Configure custom timings for 720P */
            Fvid2ModeInfo_init(mInfo);
            mInfo->standard = FVID2_STD_CUSTOM;

            mInfo->width      = 1920;
            mInfo->height     = 1080;
            mInfo->scanFormat = appObj->testPrms.inScanFormat[0];

            mInfo->pixelClock  = 74250;
            mInfo->fps         = 60U;
            mInfo->hBackPorch  = 148U;
            mInfo->hSyncLen    = 44U;
            mInfo->hFrontPorch = 88U;
            mInfo->vBackPorch  = 15U;
            mInfo->vSyncLen    = 5U;
            mInfo->vFrontPorch = 2U;
        }
#endif
    }
    else
    {
        /* We are extracting the Pixel Clock frequency which will be used to
           configure the PLL */
        Fvid2_getModeInfo(mInfo);
    }
    dctrlCfg->vencInfo.tiedVencs = 0U;

    panelCfg = &appObj->panelCfg;

    panelCfg->alphaBlenderEnable = 0;
    panelCfg->backGroundColor    = 0x00;
    panelCfg->colorKeyEnable     = 1;
    /* Source transparency color key selected */
    panelCfg->colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    panelCfg->deltaLinesPerPanel = 0;
    panelCfg->transColorKey      = 0x00;

    vencDivisors.vencId     = appObj->testPrms.vencId[0];
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;

    vencInfo.actVidPolarity   = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.dvoFormat        = VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    vencInfo.hsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.vsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.dataFormat       = FVID2_DF_RGB24_888;
    vencInfo.videoIfWidth     = FVID2_VIFW_24BIT;

    if((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
       (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
       (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
    {
        panelCfg->vencId = appObj->testPrms.vencId[0];
        vencInfo.vencId  = appObj->testPrms.vencId[0];

        /* Setting hync and vsync pol to be negative as LCD panel expects
         * it to be */

        if((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
           (appObj->testPrms.encDrvId[0] == FVID2_LCD_CTRL_DRV))
        {
            /*
             * Due to HW bug, polarity cannot be set by
             * vencInfo.pixelClkPolarity So need to change the register
             * SMA_SW_1 which mirrors some fields of the control register.
             * Only to be called for LCD, not for HDMI.
             */
            if(FVID2_POL_LOW == appObj->lcdPanelInfo.pixelClkPolarity)
            {
                Bsp_platformSetLcdClkPolarity(
                    BSP_PLATFORM_VENC_LCD1, FVID2_POL_LOW);
            }
            vencInfo.hsPolarity   = appObj->lcdPanelInfo.hsPolarity;
            vencInfo.vsPolarity   = appObj->lcdPanelInfo.vsPolarity;
            vencInfo.dataFormat   = appObj->lcdPanelInfo.videoDataFormat;
            vencInfo.videoIfWidth = appObj->lcdPanelInfo.videoIfWidth;

            /* Set display width/height equal to that of LCD width/height */
            for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
            {
                instObj = &appObj->instObj[instCnt];

                if(DISP_APP_USE_LCD_WIDTH == appObj->testPrms.inWidth[instCnt])
                {
                    appObj->testPrms.inWidth[instCnt] =
                        appObj->lcdPanelInfo.modeInfo.width;
                    instObj->inWidth = appObj->lcdPanelInfo.modeInfo.width;
                    instObj->dssPrms.inFmt.width = instObj->inWidth;
                    instObj->dssPrms.tarWidth    = instObj->inWidth;
                }

                if(DISP_APP_USE_LCD_HEIGHT ==
                   appObj->testPrms.inHeight[instCnt])
                {
                    appObj->testPrms.inHeight[instCnt] =
                        appObj->lcdPanelInfo.modeInfo.height;
                    instObj->inHeight = appObj->lcdPanelInfo.modeInfo.height;
                    instObj->dssPrms.inFmt.height = instObj->inHeight;
                    instObj->dssPrms.tarHeight    = instObj->inHeight;
                }
            }
        }
    }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
    if(appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
    {
        panelCfg->vencId = VPS_DCTRL_DSS_VENC_HDMI;

        vencInfo.hsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencInfo.vsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencInfo.vencId     = VPS_DCTRL_DSS_VENC_HDMI;
    }
#endif

    /* This IOCTL should be called before SET_CONFIG_IOCTL */
    status = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_VENC_OUTPUT,
        &vencInfo,
        NULL);
    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Venc Output IOCTL Failed!!!\r\n");
    }

    if(appObj->testPrms.boardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
    {
        VpsDssDispcAdvLcdTdmConfig_init(&advTdmPrms);
        advTdmPrms.tdmEnable = 1;
        advTdmPrms.vencId    = appObj->testPrms.vencId[0];

        status = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_TDM_PARAMS,
            &advTdmPrms,
            NULL);
        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Set ADV TDM Pramas Failed!!!\r\n");
        }
    }

    status = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_CONFIG,
        dctrlCfg,
        NULL);
    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
    }

    status = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_OVLY_PARAMS,
        panelCfg,
        NULL);
    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set OVLY Params IOCTL Failed!!!\r\n");
    }

    /* Setting LCD and PCD values */
    if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
        * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed to output
        * 29.232 * 4 MHz and set PCD as 4. */
        if(29232U == appObj->lcdPanelInfo.modeInfo.pixelClock)
        {
            vencDivisors.divisorPCD = 4U;
        }

        status = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS,
            &vencDivisors,
            NULL);
        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                    APP_NAME ": DCTRL Set Venc Divisors IOCTL Failed!!!\r\n");
        }
#endif
    }

    status = LpbkApp_dispConfigDctrlPipe(appObj);

    if((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
       ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)))
    {
        if(appObj->testPrms.encDrvId[0] == FVID2_LCD_CTRL_DRV)
        {
            /* Reconfigure video PLL clock to match LCD required clock */
            pixelClk = appObj->lcdPanelInfo.modeInfo.pixelClock *
                       vencDivisors.divisorPCD;
            status = LpbkApp_dispConfigPllAndClkSrc(appObj, pixelClk);
            if(status != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
        else if(appObj->testPrms.encDrvId[0] == FVID2_VID_ENC_SII9022A_DRV)
        {
            /* Reconfigure video PLL clock to match Sil9022a clock */
            if(appObj->testPrms.boardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
            {
                pixelClk = mInfo->pixelClock * 3;
            }
            else
            {
                pixelClk = mInfo->pixelClock;
            }
            status = LpbkApp_dispConfigPllAndClkSrc(appObj, pixelClk);
            if(status != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
    }

    return (status);
}

static Int32 LpbkApp_dispConfigDctrlPipe(LpbkApp_dispObj *appObj)
{
    Vps_DssDispcOvlyPipeConfig *ovlpipecfg;
    UInt32           instCnt;
    DispApp_InstObj *instObj;
    Int32 status = FVID2_SOK;

    for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        ovlpipecfg = &instObj->ovlpipeconfig;

        ovlpipecfg->pipeLine    = instObj->instId;
        ovlpipecfg->globalAlpha = 0xFF;
        /* Z-order is in order GFX - 3, VID3 -2 ,VID2 - 1 and VID1 - 0 */
        ovlpipecfg->zorder = instObj->instId;

        if(ovlpipecfg->pipeLine == VPS_DSS_DISPC_PIPE_GFX1)
        {
            /* 50 % blending selected - 0xFF is opaque and 0x00 is
             * transparent */
            ovlpipecfg->globalAlpha = 0x7F;

            /* For tda3xx platform we have only 3 pipeline - so Z-order 2
             * is max */
            if(TRUE == Bsp_platformIsTda3xxFamilyBuild())
            {
                ovlpipecfg->zorder = 2;
            }
        }

        ovlpipecfg->zorderEnable     = 1;
        ovlpipecfg->preMultiplyAlpha = 0;

        status += Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS,
            ovlpipecfg,
            NULL);

        if(status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Set Pipeline params IOCTL Failed!!!\r\n");
            break;
        }
    }
    return status;
}

/**
 *  LpbkApp_dispCallback
 *  \brief Driver callback function.
 */
static Int32 LpbkApp_dispCallback(
    Fvid2_Handle handle,
    Ptr appData,
    Ptr reserved)
{
    Int32 status = FVID2_SOK;
    DispApp_InstObj *instObj = (DispApp_InstObj *) appData;

    GT_assert(BspAppTrace, appData != NULL);

    Semaphore_post(*(instObj->appObj->semHandle));

    instObj->appObj->callBackCount++;

    return (status);
}

/**
 *  LpbkApp_dispInitParams
 *  Initialize the global variables and frame pointers.
 */
static void LpbkApp_dispInitParams(LpbkApp_dispObj *appObj)
{
    UInt32 instCnt;
    Vps_DispDssParams *dssPrms;
    DispApp_InstObj   *instObj;

    appObj->callBackCount = 0U;
    appObj->lcdCtrlhdl    = NULL;

    for(instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->inDataFmt = appObj->testPrms.inDataFmt[instCnt];

#if 0
        if(Fvid2_isDataFmtSemiPlanar(instObj->inDataFmt))
        {
            instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsUtils_align(appObj->maxWidth, VPS_BUFFER_ALIGNMENT);
            instObj->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX];
        }
        else if(Fvid2_isDataFmtYuv422I(instObj->inDataFmt))
        {
            instObj->pitch[FVID2_YUV_INT_ADDR_IDX] =
                VpsUtils_align(appObj->maxWidth * 2U, VPS_BUFFER_ALIGNMENT);
        }
        else if(Fvid2_isDataFmtRgb16bit(instObj->inDataFmt))
        {
            instObj->pitch[FVID2_YUV_INT_ADDR_IDX] =
                VpsUtils_align(appObj->maxWidth * 2U, VPS_BUFFER_ALIGNMENT);
        }
        else if(Fvid2_isDataFmtRgb24bit(instObj->inDataFmt))
        {
            /* Align the pitch to BPP boundary as well since the pitch
             * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
             * bytes (1 pixel) */
            instObj->pitch[FVID2_RGB_ADDR_IDX] =
                VpsUtils_align(appObj->maxWidth * 3U,
                               (VPS_BUFFER_ALIGNMENT * 3U));
        }
        else if(Fvid2_isDataFmtRgb32bit(instObj->inDataFmt))
        {
            /* Align the pitch to BPP boundary as well since the pitch
             * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
             * bytes (1 pixel) */
            instObj->pitch[FVID2_RGB_ADDR_IDX] =
                VpsUtils_align(appObj->maxWidth * 4U,
                               (VPS_BUFFER_ALIGNMENT));
        }
#endif
        instObj->pitch[0U] = appObj->testPrms.displayPitch;
        instObj->pitch[1U] = appObj->testPrms.displayPitch;
        instObj->pitch[2U] = appObj->testPrms.displayPitch;

        instObj->inWidth      = appObj->testPrms.inWidth[instCnt];
        instObj->inHeight     = appObj->testPrms.inHeight[instCnt];
        instObj->isFieldMerge = appObj->testPrms.isFieldMerge[instCnt];
        instObj->inScanFormat = appObj->testPrms.inScanFormat[instCnt];
        instObj->posx         = appObj->testPrms.posx[instCnt];
        instObj->posy         = appObj->testPrms.posy[instCnt];
        instObj->instId       = appObj->testPrms.instId[instCnt];
        instObj->drvHandle    = NULL;

        Fvid2CbParams_init(&instObj->cbPrms);
        instObj->cbPrms.cbFxn   = &LpbkApp_dispCallback;
        instObj->cbPrms.appData = instObj;
        instObj->appObj         = appObj;

        VpsDispCreateParams_init(&instObj->createPrms);

        dssPrms = &instObj->dssPrms;

        VpsDispDssParams_init(&instObj->dssPrms);
        dssPrms->inFmt.chNum           = 0U;
        dssPrms->inFmt.width           = instObj->inWidth;
        dssPrms->inFmt.height          = instObj->inHeight;
        dssPrms->inFmt.pitch[0U]       = instObj->pitch[0U];
        dssPrms->inFmt.pitch[1U]       = instObj->pitch[1U];
        dssPrms->inFmt.pitch[2U]       = instObj->pitch[2U];
        dssPrms->inFmt.fieldMerged[0U] = instObj->isFieldMerge;
        dssPrms->inFmt.fieldMerged[1U] = FALSE;
        dssPrms->inFmt.fieldMerged[2U] = FALSE;
        dssPrms->inFmt.dataFormat      = instObj->inDataFmt;
        dssPrms->inFmt.scanFormat      = instObj->inScanFormat;
        dssPrms->inFmt.bpp             = FVID2_BPP_BITS16;
        dssPrms->inFmt.reserved        = NULL;
        dssPrms->tarWidth              = dssPrms->inFmt.width;
        dssPrms->tarHeight             = dssPrms->inFmt.height;
        dssPrms->posX                  = instObj->posx;
        dssPrms->posY                  = instObj->posy;

        VpsDssDispcVidConfig_init(&instObj->vidCfg);
        VpsDssDispcGfxConfig_init(&instObj->gfxCfg);

        instObj->vidCfg.pipeCfg.scEnable = TRUE;
        if(Vps_dispIsVidInst(instObj->instId))
        {
            dssPrms->vidCfg = &instObj->vidCfg;
        }
        if(Vps_dispIsGfxInst(instObj->instId))
        {
            dssPrms->gfxCfg = &instObj->gfxCfg;
        }
    }

    return;
}

static Int32 LpbkApp_dispDeConfigOffChipHdmi(
    LpbkApp_dispObj *appObj,
    UInt32 encInst)
{
    Int32 status = FVID2_SOK;
    if(FVID2_SOK == status)
    {
        if(NULL != appObj->hdmiHandle)
        {
            status = Fvid2_stop(appObj->hdmiHandle, NULL);
            if(FVID2_SOK != status)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Error: Off-chip HDMI stop failed!!\r\n");
            }
        }
    }

    if(NULL != appObj->hdmiHandle)
    {
        /* Close HDMI transmitter */
        status += Fvid2_delete(appObj->hdmiHandle, NULL);
        appObj->hdmiHandle = NULL;
    }

    return status;
}

static Int32  LpbkApp_dispConfigOffChipHdmi(
    LpbkApp_dispObj *appObj,
    UInt32 encInst)
{
    Int32  status = FVID2_SOK;
    UInt32 vidEncInstId, vidEncI2cInstId, vidEncI2cAddr;
    UInt32 vidEncDrvId;
    Bsp_VidEncCreateParams encCreateParams;
    Bsp_Sii9022aHpdParams  hpdPrms;
    Bsp_Sii9022aHdmiChipId hdmiId;
    Bsp_VidEncConfigParams modePrms;
    Bsp_VidEncCreateStatus encCreateStatus;

    vidEncDrvId = appObj->testPrms.encDrvId[encInst];

    vidEncInstId = Bsp_boardGetVideoDeviceInstId(
        vidEncDrvId,
        FVID2_VPS_DCTRL_DRV,
        VPS_DSS_DISPC_OVLY_DPI1);

    vidEncI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        vidEncDrvId,
        FVID2_VPS_DCTRL_DRV,
        VPS_DSS_DISPC_OVLY_DPI1);

    vidEncI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        vidEncDrvId,
        FVID2_VPS_DCTRL_DRV,
        VPS_DSS_DISPC_OVLY_DPI1);

    /* Power on Video Encoder */
    status = Bsp_boardPowerOnDevice(vidEncDrvId, vidEncInstId, TRUE);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device Power On failed\r\n");
    }

    /* select Video Encoder at board level mux */
    status = Bsp_boardSelectDevice(vidEncDrvId, vidEncInstId);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
    }

    /* Perform any reset needed at board level */
    status = Bsp_boardResetDevice(vidEncDrvId, vidEncInstId);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device reset failed\r\n");
    }

    /* Select specific mode */
    status = Bsp_boardSelectMode(
        vidEncDrvId,
        vidEncInstId,
        appObj->testPrms.boardMode);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
    }

    status = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                VPS_DSS_DISPC_OVLY_DPI1,
                                appObj->testPrms.boardMode);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Pin Muxing Failed \r\n");
    }

    if(FVID2_SOK == status)
    {
        /* Open HDMI Tx */
        encCreateParams.deviceI2cInstId     = vidEncI2cInstId;
        encCreateParams.deviceI2cAddr       = vidEncI2cAddr;
        encCreateParams.inpClk              = 0u;
        encCreateParams.hotPlugGpioIntrLine = 0u;
        encCreateParams.clkEdge             = FALSE;

        appObj->hdmiHandle = Fvid2_create(
            FVID2_VID_ENC_SII9022A_DRV,
            0u,
            &encCreateParams,
            &encCreateStatus,
            NULL);
        if(NULL == appObj->hdmiHandle)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: SII9022 create failed!!\r\n");
            status = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == status)
    {
        status = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID,
            &hdmiId,
            NULL);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Could not get detailed chip ID!!\r\n");
        }
        else
        {
            GT_4trace(
                BspAppTrace, GT_DEBUG,
                APP_NAME
                "\r\nhdmiId.deviceId = %d,hdmiId.deviceProdRevId = %d, \
             hdmiId.hdcpRevTpi = %d,hdmiId.tpiRevId = %d\r\n",
                hdmiId.deviceId, \
                hdmiId.deviceProdRevId, hdmiId.hdcpRevTpi,
                hdmiId.tpiRevId);
        }
    }

    if(FVID2_SOK == status)
    {
        status = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_SII9022A_QUERY_HPD,
            &hpdPrms,
            NULL);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Could not detect HPD!!\r\n");
        }
        else
        {
            GT_3trace(
                BspAppTrace, GT_DEBUG,
                APP_NAME
                "\r\nhpdPrms.busError= %d, \
                 hpdPrms.hpdEvtPending= %d,hpdPrms.hpdStatus= %d\r\n", \
                hpdPrms.busError, hpdPrms.hpdEvtPending,
                hpdPrms.hpdStatus);
        }
    }

    if(FVID2_SOK == status)
    {
        BspVidEncConfigParams_init(&modePrms);
        modePrms.standard = appObj->testPrms.standard[encInst];
        modePrms.videoIfMode = FVID2_VIFM_SCH_DS_AVID_VSYNC;
        modePrms.videoIfWidth = FVID2_VIFW_24BIT;
        modePrms.videoDataFormat = FVID2_DF_RGB24_888;

        status = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_VID_ENC_SET_MODE,
            &modePrms,
            NULL);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Could not set mode!!\r\n");
        }
    }

    if((FVID2_SOK != status) && (NULL != appObj->hdmiHandle))
    {
        /* Close HDMI transmitter */
        status += Fvid2_delete(appObj->hdmiHandle, NULL);
        appObj->hdmiHandle = NULL;
    }

    return status;
}

static void LpbkApp_dispConfigLcd(LpbkApp_dispObj *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 lcdCtrlInstId, lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    UInt32 lcdCtrlDrvId;
    UInt32 brightVal;
    UInt32 syncMode;
    UInt32 instId = VPS_DSS_DISPC_OVLY_DPI1;
    if (appObj->testPrms.vencId[0U] == VPS_DCTRL_DSS_VENC_LCD3)
    {
        instId = VPS_DSS_DISPC_OVLY_DPI3;
    }

    lcdCtrlDrvId = FVID2_LCD_CTRL_DRV;

    lcdCtrlInstId = Bsp_boardGetVideoDeviceInstId(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        instId);

    lcdCtrlI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        instId);

    lcdCtrlI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        instId);

    status = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                instId,
                                appObj->testPrms.boardMode);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Pin Muxing Failed \r\n");
    }

    /* Power on LCD controller */
    status = Bsp_boardPowerOnDevice(lcdCtrlDrvId, lcdCtrlInstId, TRUE);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device Power On failed\r\n");
    }

    /* select lcd Controller at board level mux */
    status = Bsp_boardSelectDevice(lcdCtrlDrvId, lcdCtrlInstId);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
    }

    /* Perform any reset needed at board level */
    status = Bsp_boardResetDevice(lcdCtrlDrvId, lcdCtrlInstId);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device reset failed\r\n");
    }

    /* Select specific mode */
    status = Bsp_boardSelectMode(
        lcdCtrlDrvId,
        lcdCtrlInstId,
        appObj->testPrms.boardMode);
    if(FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
    }

    /* After TLC is powered on, some delay to get it stabilized */
    BspOsal_sleep(5);

    appObj->lcdCtrlCreatePrms.deviceI2cAddr[0]   = lcdCtrlI2cAddr;
    appObj->lcdCtrlCreatePrms.deviceResetGpio[0] = 0;
    appObj->lcdCtrlCreatePrms.deviceI2cInstId    = lcdCtrlI2cInstId;
    appObj->lcdCtrlCreatePrms.numDevices         = 1;

    appObj->lcdCtrlhdl = Fvid2_create(
        FVID2_LCD_CTRL_DRV,
        0,
        &appObj->lcdCtrlCreatePrms,
        NULL,
        NULL);

    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_POWER_ON,
        NULL,
        NULL);

    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Lcd powering on Failed!!!\r\n");
    }

    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT,
        NULL,
        NULL);

    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Enabling backlight failed!!!\r\n");
    }

    syncMode = BSP_LCD_CTRL_MODE_DE;

    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC,
        &syncMode,
        NULL);

    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Selecting sync mode failed!!!\r\n");
    }

    /* Brightness Value is 75% */
    brightVal = 75;

    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS,
        &brightVal,
        NULL);
    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Controlling LCD brightness Failed!!!\r\n");
    }

    /* Get the LCD timings */
    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_GET_PANEL_INFO,
        &appObj->lcdPanelInfo,
        NULL);
    if(status != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Get LCD timing failed!!!\r\n");
    }

/* This will configure Venc with LCD timings and enable the color bar */
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)

    *(UInt32 *) 0x4810a000 = 0x4003B023;
    *(UInt32 *) 0x4810a004 = 0x1FD01E24;
    *(UInt32 *) 0x4810a008 = 0x02DC020C;
    *(UInt32 *) 0x4810a00C = 0x00DA004A;
    *(UInt32 *) 0x4810a010 = 0x020C1E6C;
    *(UInt32 *) 0x4810a014 = 0x02001F88;
    *(UInt32 *) 0x4810a018 = 0x00200000;
    *(UInt32 *) 0x4810a01C = 0x1B6C0C77;
    *(UInt32 *) 0x4810a020 = 0x1C0C0C30;
    *(UInt32 *) 0x4810a024 = 0x1C0C0C30;
    *(UInt32 *) 0x4810a028 = 0x842EE672;
    *(UInt32 *) 0x4810a02C = 0x3F000018;
    *(UInt32 *) 0x4810a030 = 0xD0320100;
    *(UInt32 *) 0x4810a034 = 0x000002E8;
    *(UInt32 *) 0x4810a038 = 0x000C39E7;
    *(UInt32 *) 0x4810a03C = 0xD0320100;
    *(UInt32 *) 0x4810a040 = 0x0001A64B;
    *(UInt32 *) 0x4810a044 = 0x002D0000;
    *(UInt32 *) 0x4810a048 = 0x05000000;
    *(UInt32 *) 0x4810a04C = 0x00003000;
    *(UInt32 *) 0x4810a050 = 0x00000000;
    *(UInt32 *) 0x4810a054 = 0xD0320100;
    *(UInt32 *) 0x4810a058 = 0x0001A64B;
    *(UInt32 *) 0x4810a05C = 0x002D0000;
    *(UInt32 *) 0x4810a060 = 0x05000000;
    *(UInt32 *) 0x4810a064 = 0x00003000;
    *(UInt32 *) 0x4810a068 = 0x00000000;
    *(UInt32 *) 0x4810a06C = 0x00000000;
    *(UInt32 *) 0x4810a070 = 0x00000000;
    *(UInt32 *) 0x4810a074 = 0x00000000;

#endif
}

static void LpbkApp_dispTurnOffLcd(LpbkApp_dispObj *appObj)
{
    Int32 status = FVID2_SOK;

    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT,
        NULL,
        NULL);

    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Disable backlight failed!!!\r\n");
    }

    status = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_POWER_OFF,
        NULL,
        NULL);

    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Lcd powering Off Failed!!!\r\n");
    }

    status = Fvid2_delete(appObj->lcdCtrlhdl, NULL);
    if(status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": LCD Ctrl handle delete failed!!!\r\n");
    }
    return;
}

