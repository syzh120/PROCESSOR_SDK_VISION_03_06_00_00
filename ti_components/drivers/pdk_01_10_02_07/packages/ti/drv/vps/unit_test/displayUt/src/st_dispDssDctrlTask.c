/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file st_dispDssDctrlTask.c
 *
 *  \brief
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <st_dispDss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 st_dispDssDctrlCreate(st_DispDssAppObj *appObj);
Int32 st_dispDssDctrlConfig(st_DispDssAppObj *appObj);
Int32 st_dispDssDctrlDelete(st_DispDssAppObj *appObj);
Int32 st_dispDssConfigDctrlPipe(st_DispDssAppObj *appObj);
static Int32 st_dispDssPLLInit(void);
static Int32 st_dispDssConfigureVideoPllAndClkSrc(Uint32 pixelClk, UInt32 vencId);
static Int32 st_dispDssConfigureLCD(st_DispDssAppObj *appObj, UInt32 encInst);
static Int32 st_dispDssTurnoffLCD(st_DispDssAppObj *appObj, UInt32 encInst);
static Int32 st_dispDssConfigureOffChipHdmi(st_DispDssAppObj *appObj, UInt32 encInst);
static Int32 st_dispDssDeconfigureOffChipHdmi(st_DispDssAppObj *appObj, UInt32 encInst);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern Semaphore_Handle      gStDispDssMasterTaskSem;
extern Semaphore_Handle      gStDispDssDctrlTaskSem;
extern Queue_Handle          gDctrlmsgQueue;
extern st_DispDssAppObj      gAppDispDssObj[VPS_DISP_INST_MAX];
UInt32 gTestVal0 = 0;
extern st_DispDssTestCfg     gDispDssTestCfg;
extern st_DispDssTestInstCfg gDispDssTestInstCfg[VPS_DISP_INST_MAX];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_dispDssDctrlTestTask
 */
void st_dispDssDctrlTestTask(UArg arg0, UArg arg1)
{
    Int32  retVal = FVID2_SOK;
    st_DispDssMsgObj       *dCtrlTskmsgObj;
    st_DispDssAppObj       *appObj;
    UInt32 flag = 1U;
    // UInt32                  instId;

    // appObj = (st_DispDssAppObj *)arg0;
    appObj = &gAppDispDssObj[0];
    appObj->taskResult = FVID2_SOK;
    // appObj = &gAppDispDssObj[3];

    while (1)
    {
        if ((!flag) | (appObj->taskResult != FVID2_SOK))
        {
            Semaphore_post(gStDispDssMasterTaskSem);
            Semaphore_pend(gStDispDssDctrlTaskSem, BIOS_WAIT_FOREVER);
        }
        dCtrlTskmsgObj = Queue_get(gDctrlmsgQueue);
        flag           = 0;

        // instId = dCtrlTskmsgObj->value;

        // appObj = (st_DispDssAppObj *)&gAppDispDssObj[instId];

        switch (dCtrlTskmsgObj->cmd)
        {
            case CREATE:
                retVal = st_dispDssDctrlCreate(appObj);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(appObj->traceMask, GT_ERR,
                              "DCTRL Create failed\r\n"); \
                    appObj->taskResult = FVID2_EFAIL;
                }

                break;

            case CONTROL:
                retVal = st_dispDssDctrlConfig(appObj);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(appObj->traceMask, GT_ERR,
                              "DCTRL Control phase failed\r\n");
                    appObj->taskResult = FVID2_EFAIL;
                }
                break;

            case DELETE:
                retVal = st_dispDssDctrlDelete(appObj);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(appObj->traceMask, GT_ERR,
                              "DCTRL Delete phase failed\r\n");
                    appObj->taskResult = FVID2_EFAIL;
                }
                break;
        }
    }
}

Int32 st_dispDssDctrlCreate(st_DispDssAppObj *appObj)
{
    Int32 retVal = FVID2_SOK;

    /* Create DCTRL handle, used for common driver configuration */
    appObj->dctrlHandle = Fvid2_create(
        FVID2_VPS_DCTRL_DRV,
        VPS_DCTRL_INST_0,
        NULL,                           /* NULL for VPS_DCTRL_INST_0 */
        NULL,                           /* NULL for VPS_DCTRL_INST_0 */
        NULL);                          /* NULL for VPS_DCTRL_INST_0 */
    if (NULL == appObj->dctrlHandle)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL Create Failed!!!\r\n");
        return FVID2_EFAIL;
    }

    return retVal;
}

Int32 st_dispDssDctrlConfig(st_DispDssAppObj *appObj)
{
    Int32                        retVal = FVID2_SOK;
    Vps_DctrlConfig             *dctrlCfg;
    UInt32                       testInstcfgID;
    UInt32                       numEdges;
    UInt32                       lcd1BlenderFlag = 0;
    UInt32                       lcd2BlenderFlag = 0;
    UInt32                       lcd3BlenderFlag = 0;
    UInt32                       hdmiBlenderFlag = 0;
    UInt32                       lcd1BlenderEdge = 0;
    UInt32                       lcd2BlenderEdge = 0;
    UInt32                       lcd3BlenderEdge = 0;
    UInt32                       hdmiBlenderEdge = 0;
    UInt32                       testInstEdgeID  = 0;
    UInt32                       numVencs        = 0;
    UInt32                       vencCfgId;
    UInt32                       vencId[VPS_DCTRL_MAX_VENC] = {0};
    Fvid2_ModeInfo               vencModeInfo[VPS_DCTRL_MAX_VENC];
    Vps_DssDispcAdvLcdTdmConfig  dispcAdvLcdTdmConfig;
    Vps_DctrlOutputInfo          dCtrlOutInfo;
    UInt32                       pixelClk, sdVencEnable;
    Vps_DctrlSDVencVideoStandard vidStd;

    memcpy(&dCtrlOutInfo, &gDispDssTestInstCfg[0].dCtrlOutInfo,
           sizeof (Vps_DctrlOutputInfo));

    dctrlCfg          = &appObj->dctrlCfg;
    dctrlCfg->useCase = VPS_DCTRL_USERSETTINGS;

    retVal = st_dispDssPLLInit();
    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "DSS PLL Init Failed!!!\r\n");
        return FVID2_EFAIL;
    }

    /* Get the heap status at the start */
    for (testInstcfgID = 0; testInstcfgID < gDispDssTestCfg.numInst;
         testInstcfgID++)
    {
        switch (gDispDssTestInstCfg[testInstcfgID].videoNode)
        {
            case VID1:
                dctrlCfg->edgeInfo[testInstcfgID].startNode =
                    VPS_DCTRL_DSS_VID1_INPUT_PATH;
                break;

            case VID2:
                dctrlCfg->edgeInfo[testInstcfgID].startNode =
                    VPS_DCTRL_DSS_VID2_INPUT_PATH;
                break;

            case VID3:
                dctrlCfg->edgeInfo[testInstcfgID].startNode =
                    VPS_DCTRL_DSS_VID3_INPUT_PATH;
                break;

            case GFX1:
                dctrlCfg->edgeInfo[testInstcfgID].startNode =
                    VPS_DCTRL_DSS_GFX1_INPUT_PATH;
                break;
        }

    #if defined (SOC_TDA2EX)
        if ((Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_17x17) &&
            (gDispDssTestInstCfg[testInstcfgID].overlayNode == LCD1) &&
            (gDispDssTestInstCfg[testInstcfgID].dispNode == DPI1))
        {
            gDispDssTestInstCfg[testInstcfgID].overlayNode = LCD3;
            gDispDssTestInstCfg[testInstcfgID].panelCfg.vencId = VPS_DCTRL_DSS_VENC_LCD3;
            gDispDssTestInstCfg[testInstcfgID].dCtrlOutInfo.vencId = VPS_DCTRL_DSS_VENC_LCD3;
            dCtrlOutInfo.vencId = VPS_DCTRL_DSS_VENC_LCD3;
            gDispDssTestInstCfg[testInstcfgID].dispNode = DPI3;
        }
    #endif
        switch (gDispDssTestInstCfg[testInstcfgID].overlayNode)
        {
            case LCD1:
                dctrlCfg->edgeInfo[testInstcfgID].endNode =
                    VPS_DCTRL_DSS_LCD1_BLENDER;
                break;

            case LCD2:
                dctrlCfg->edgeInfo[testInstcfgID].endNode =
                    VPS_DCTRL_DSS_LCD2_BLENDER;
                break;

            case LCD3:
                dctrlCfg->edgeInfo[testInstcfgID].endNode =
                    VPS_DCTRL_DSS_LCD3_BLENDER;
                break;

            case HDMI:
                dctrlCfg->edgeInfo[testInstcfgID].endNode =
                    VPS_DCTRL_DSS_HDMI_BLENDER;
                break;
        }
    }

    numEdges = gDispDssTestCfg.numInst;

    for (testInstcfgID = 0; testInstcfgID < gDispDssTestCfg.numInst;
         testInstcfgID++)
    {
        switch (gDispDssTestInstCfg[testInstcfgID].overlayNode)
        {
            case LCD1:
                if (!lcd1BlenderFlag)
                {
                    numEdges             = numEdges + 1;
                    lcd1BlenderEdge      = numEdges - 1;
                    numVencs             = numVencs + 1;
                    vencId[numVencs - 1] = VPS_DCTRL_DSS_VENC_LCD1;
                    if (gDispDssTestInstCfg[testInstcfgID].encDrvId == ENC_ID_LCD)
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = FVID2_LCD_CTRL_DRV;
                    }
                    else if(gDispDssTestInstCfg[testInstcfgID].encDrvId == ENC_ID_SIL9022A)
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = FVID2_VID_ENC_SII9022A_DRV;
                    }
                    else
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = 0;
                    }
                    appObj->testPrms.boardMode[numVencs - 1] = gDispDssTestInstCfg[testInstcfgID].boardMode;
                    appObj->testPrms.standard[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].mInfo.standard;
                    appObj->testPrms.isSdVenc[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].isSdVenc;
                    memcpy(&vencModeInfo[numVencs - 1],
                           &gDispDssTestInstCfg[numVencs - 1].mInfo,
                           sizeof (Fvid2_ModeInfo));
                }
                dctrlCfg->edgeInfo[lcd1BlenderEdge].startNode =
                    VPS_DCTRL_DSS_LCD1_BLENDER;
                testInstEdgeID  = lcd1BlenderEdge;
                lcd1BlenderFlag = 1;
                break;

            case LCD2:
                if (!lcd2BlenderFlag)
                {
                    numEdges             = numEdges + 1;
                    lcd2BlenderEdge      = numEdges - 1;
                    numVencs             = numVencs + 1;
                    vencId[numVencs - 1] = VPS_DCTRL_DSS_VENC_LCD2;
                    if (gDispDssTestInstCfg[testInstcfgID].encDrvId == ENC_ID_LCD)
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = FVID2_LCD_CTRL_DRV;
                    }
                    else if(gDispDssTestInstCfg[testInstcfgID].encDrvId == ENC_ID_SIL9022A)
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = FVID2_VID_ENC_SII9022A_DRV;
                    }
                    else
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = 0;
                    }
                    appObj->testPrms.boardMode[numVencs - 1] = gDispDssTestInstCfg[testInstcfgID].boardMode;
                    appObj->testPrms.standard[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].mInfo.standard;
                    appObj->testPrms.isSdVenc[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].isSdVenc;
                    memcpy(&vencModeInfo[numVencs - 1],
                           &gDispDssTestInstCfg[numVencs - 1].mInfo,
                           sizeof (Fvid2_ModeInfo));
                }
                dctrlCfg->edgeInfo[lcd2BlenderEdge].startNode =
                    VPS_DCTRL_DSS_LCD2_BLENDER;
                testInstEdgeID  = lcd2BlenderEdge;
                lcd2BlenderFlag = 1;
                break;

            case LCD3:
                if (!lcd3BlenderFlag)
                {
                    numEdges             = numEdges + 1;
                    lcd3BlenderEdge      = numEdges - 1;
                    numVencs             = numVencs + 1;
                    vencId[numVencs - 1] = VPS_DCTRL_DSS_VENC_LCD3;
                    if (gDispDssTestInstCfg[testInstcfgID].encDrvId == ENC_ID_LCD)
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = FVID2_LCD_CTRL_DRV;
                    }
                    else if(gDispDssTestInstCfg[testInstcfgID].encDrvId == ENC_ID_SIL9022A)
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = FVID2_VID_ENC_SII9022A_DRV;
                    }
                    else
                    {
                        appObj->testPrms.encDrvId[numVencs - 1] = 0;
                    }
                    appObj->testPrms.boardMode[numVencs - 1] = gDispDssTestInstCfg[testInstcfgID].boardMode;
                    appObj->testPrms.standard[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].mInfo.standard;
                    appObj->testPrms.isSdVenc[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].isSdVenc;
                    memcpy(&vencModeInfo[numVencs - 1],
                           &gDispDssTestInstCfg[numVencs - 1].mInfo,
                           sizeof (Fvid2_ModeInfo));
                }
                dctrlCfg->edgeInfo[lcd3BlenderEdge].startNode =
                    VPS_DCTRL_DSS_LCD3_BLENDER;
                testInstEdgeID  = lcd3BlenderEdge;
                lcd3BlenderFlag = 1;
                break;

            case HDMI:
                if (!hdmiBlenderFlag)
                {
                    numEdges             = numEdges + 1;
                    hdmiBlenderEdge      = numEdges - 1;
                    numVencs             = numVencs + 1;
                    vencId[numVencs - 1] = VPS_DCTRL_DSS_VENC_HDMI;
                    appObj->testPrms.encDrvId[numVencs - 1] = 0;
                    appObj->testPrms.boardMode[numVencs - 1] = gDispDssTestInstCfg[testInstcfgID].boardMode;
                    appObj->testPrms.standard[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].mInfo.standard;
                    appObj->testPrms.isSdVenc[numVencs - 1] = (Fvid2_Standard)gDispDssTestInstCfg[testInstcfgID].isSdVenc;
                    memcpy(&vencModeInfo[numVencs - 1],
                           &gDispDssTestInstCfg[numVencs - 1].mInfo,
                           sizeof (Fvid2_ModeInfo));
                }
                dctrlCfg->edgeInfo[hdmiBlenderEdge].startNode =
                    VPS_DCTRL_DSS_HDMI_BLENDER;
                testInstEdgeID  = hdmiBlenderEdge;
                hdmiBlenderFlag = 1;
                break;
        }

        switch (gDispDssTestInstCfg[testInstcfgID].dispNode)
        {
            case DPI1:
                dctrlCfg->edgeInfo[testInstEdgeID].endNode =
                    VPS_DCTRL_DSS_DPI1_OUTPUT;
                appObj->testPrms.dispNodeId[numVencs - 1] = VPS_DSS_DISPC_OVLY_DPI1;
                break;

            case DPI2:
                dctrlCfg->edgeInfo[testInstEdgeID].endNode =
                    VPS_DCTRL_DSS_DPI2_OUTPUT;
                appObj->testPrms.dispNodeId[numVencs - 1] = VPS_DSS_DISPC_OVLY_DPI1;
                GT_0trace(appObj->traceMask, GT_INFO,
                          "No output is expected : DPI2!!\r\n");
                break;

            case DPI3:
                dctrlCfg->edgeInfo[testInstEdgeID].endNode =
                    VPS_DCTRL_DSS_DPI3_OUTPUT;
            #if defined (SOC_TDA2EX)
                /* TDA2Ex 17x17 Evm LCD output is expected on DPI3. */
                if (Bsp_platformGetPackageType() != BSP_PLATFORM_PACKAGE_TYPE_17x17)
                {
                    GT_0trace(appObj->traceMask, GT_INFO,
                              "No output is expected : DPI3!!\r\n");
                    appObj->testPrms.dispNodeId[numVencs - 1] = VPS_DSS_DISPC_OVLY_DPI1;
                }
                else
                {
                    appObj->testPrms.dispNodeId[numVencs - 1] = VPS_DSS_DISPC_OVLY_DPI3;
                }
            #else
                appObj->testPrms.dispNodeId[numVencs - 1] = VPS_DSS_DISPC_OVLY_DPI1;
                GT_0trace(appObj->traceMask, GT_INFO,
                          "No output is expected : DPI3!!\r\n");
            #endif
                break;

            case HDMIOUT:
                dctrlCfg->edgeInfo[testInstEdgeID].endNode =
                    VPS_DCTRL_DSS_HDMI_OUTPUT;
                appObj->testPrms.dispNodeId[numVencs - 1] = VPS_DSS_DISPC_OVLY_HDMI;
                break;
        }
    }

    dctrlCfg->numEdges          = numEdges;
    dctrlCfg->vencInfo.numVencs = numVencs;
    appObj->testPrms.numEnc     = numVencs;

    for (vencCfgId = 0; vencCfgId < numVencs; vencCfgId++)
    {
        if ((appObj->testPrms.encDrvId[vencCfgId] == FVID2_LCD_CTRL_DRV) ||
            (appObj->testPrms.encDrvId[vencCfgId] == FVID2_VID_ENC_SII9022A_DRV))
        {
            retVal = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                        appObj->testPrms.dispNodeId[vencCfgId],
                                        appObj->testPrms.boardMode[vencCfgId]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(appObj->traceMask, GT_ERR, "Pin Muxing Failed \r\n");
            }
        }
        if (appObj->testPrms.encDrvId[vencCfgId] == FVID2_LCD_CTRL_DRV)
        {
            /* Configure LCD only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = st_dispDssConfigureLCD(appObj, vencCfgId);
            #if defined (SOC_TDA2PX)
                /* For TDA2Px DPI to HDMI converter is connected, so configure the
                * the standard timing of 1080P. */
                vencModeInfo[numVencs - 1].standard = FVID2_STD_1080P_60;
                Fvid2_getModeInfo(&vencModeInfo[numVencs - 1]);
                vencModeInfo[numVencs - 1].scanFormat   = FVID2_SF_PROGRESSIVE;
                vencModeInfo[numVencs - 1].pixelClock   = 148500U;
                vencModeInfo[numVencs - 1].fps          = 60U;
                vencModeInfo[numVencs - 1].hFrontPorch  = 88U;
                vencModeInfo[numVencs - 1].hBackPorch   = 148U;
                vencModeInfo[numVencs - 1].hSyncLen     = 44U;
                vencModeInfo[numVencs - 1].vFrontPorch  = 4U;
                vencModeInfo[numVencs - 1].vBackPorch   = 36U;
                vencModeInfo[numVencs - 1].vSyncLen     = 5U;
                /* Configure custom timings */
                BspUtils_memcpy(
                    &appObj->lcdPanelInfo.modeInfo, &vencModeInfo[numVencs - 1],
                    sizeof (Fvid2_ModeInfo));
                appObj->lcdPanelInfo.videoIfWidth    = FVID2_VIFW_24BIT;
                appObj->lcdPanelInfo.videoDataFormat = FVID2_DF_RGB24_888;
                appObj->lcdPanelInfo.videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                appObj->lcdPanelInfo.vsPolarity       = FVID2_POL_HIGH;
                appObj->lcdPanelInfo.hsPolarity       = FVID2_POL_HIGH;
                appObj->lcdPanelInfo.actVidPolarity   = FVID2_POL_HIGH;
                appObj->lcdPanelInfo.fidPolarity      = FVID2_POL_HIGH;
                appObj->lcdPanelInfo.pixelClkPolarity = FVID2_POL_HIGH;
            #else
                memcpy(&vencModeInfo[numVencs - 1],
                    &appObj->lcdPanelInfo.modeInfo,
                    sizeof (Fvid2_ModeInfo));
            #endif
            }
        }
        else if (appObj->testPrms.encDrvId[vencCfgId] == FVID2_VID_ENC_SII9022A_DRV )
        {
            /* Configure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = st_dispDssConfigureOffChipHdmi(appObj, vencCfgId);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(appObj->traceMask, GT_ERR,
                        UT_NAME ": Configuring Off-Chip HDMI Failed !!!\r\n");
                }
            }
        }

        dctrlCfg->vencInfo.modeInfo[vencCfgId].vencId = vencId[vencCfgId];
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[vencCfgId].mInfo);
        memcpy(&dctrlCfg->vencInfo.modeInfo[vencCfgId].mInfo,
               &vencModeInfo[vencCfgId], sizeof (Fvid2_ModeInfo));
    }

    dctrlCfg->vencInfo.tiedVencs = 0u;

    /* This IOCTL should be called before SET_CONFIG_IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_VENC_OUTPUT,
        &dCtrlOutInfo,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL Set Venc Output IOCTL Failed!!!\r\n");
        return retVal;
    }

    /* For BT656 output configure the custom CPR coefficients.
     * Currently configuring the default BT601 coefficients.
     * Enable the CSC and Disable the CPR. */
    if (dCtrlOutInfo.dvoFormat == VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
    {
        Vps_DssVencCprCoeff getCoeff = {0};
        Vps_DssVencCprCoeff coeff = {
            0, (UInt32) FALSE, (UInt32) TRUE,
            77,            150,            29,
            -((Int16) 44), -((Int16) 87),  131,
            131,           -((Int16) 110), -((Int16) 21)};
        getCoeff.vencId = dCtrlOutInfo.vencId;
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_GET_CPR_COEFF,
            &getCoeff,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                    UT_NAME ": DCTRL Get CPR Coeff IOCTL Failed!!!\r\n");
        }

        coeff.vencId = dCtrlOutInfo.vencId;
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_SET_CPR_COEFF,
            &coeff,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                    UT_NAME ": DCTRL Set CPR Coeff IOCTL Failed!!!\r\n");
        }
    }

    if (VPS_DCTRL_DSS_VENC_HDMI != vencId[0U])
    {
        if (gDispDssTestInstCfg[0].dispcAdvLcdTdmConfig.tdmEnable == TRUE)
        {
            if (appObj->testPrms.boardMode[0] != BSP_BOARD_MODE_VIDEO_8BIT_TDM)
            {
                GT_0trace(appObj->traceMask, GT_INFO,
                            "No output is expected : TDM mode (not 8 bit)\r\n");
            }
            memcpy(&dispcAdvLcdTdmConfig,
                &gDispDssTestInstCfg[0].dispcAdvLcdTdmConfig,
                sizeof (Vps_DssDispcAdvLcdTdmConfig));
        }
        else
        {
            /* clear TDM configuration */
            VpsDssDispcAdvLcdTdmConfig_init(&dispcAdvLcdTdmConfig);
            dispcAdvLcdTdmConfig.vencId = vencId[0U];
        }
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_TDM_PARAMS,
            &dispcAdvLcdTdmConfig,
            NULL);
    }

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL Set Adv Venc TDM PRM IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_CONFIG,
        dctrlCfg,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
    }

    for (vencCfgId = 0; vencCfgId < numVencs; vencCfgId++)
    {
        if (appObj->testPrms.encDrvId[vencCfgId] == FVID2_LCD_CTRL_DRV)
        {
            /*
            * Due to HW bug, polarity cannot be set by vencInfo.pixelClkPolarity
            * So need to change the register SMA_SW_1 which mirrors some fields of
            * the control register. Only to be called for LCD, not for HDMI.
            */
            if (Bsp_platformIsTda2xxFamilyBuild() &&
                (Bsp_platformGetSocId() != BSP_PLATFORM_SOC_ID_TDA2EX) &&
                (FVID2_POL_LOW == appObj->lcdPanelInfo.pixelClkPolarity))
            {
                Bsp_platformSetLcdClkPolarity(dCtrlOutInfo.vencId, FVID2_POL_LOW);
            }
        }
        if (appObj->testPrms.isSdVenc[vencCfgId] == TRUE)
        {
            pixelClk = 54000U;
            retVal = st_dispDssConfigureVideoPllAndClkSrc(pixelClk, vencId[vencCfgId]);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(appObj->traceMask, GT_ERR,
                UT_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
            sdVencEnable = TRUE;
            /* SD-VENC Power on and Configure IOCTL's */
            retVal = Fvid2_control(
                appObj->dctrlHandle,
                IOCTL_VPS_DCTRL_ENABLE_SDVENC,
                &sdVencEnable,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(appObj->traceMask, GT_ERR,
                        UT_NAME ": Enabling SD-VENC IOCTL Failed!!!\r\n");
            }
            VpsDctrlSDVencVideoStandard_init(&vidStd);
            vidStd.videoStandard = appObj->testPrms.standard[vencCfgId];
            /* SD-VENC Configure the Mode IOCTL's */
            retVal = Fvid2_control(
                appObj->dctrlHandle,
                IOCTL_VPS_DCTRL_SET_SDVENC_MODE,
                &vidStd,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(appObj->traceMask, GT_ERR,
                        UT_NAME ": Set SD-VENC Mode IOCTL Failed!!!\r\n");
            }
        }
        else if (appObj->testPrms.encDrvId[vencCfgId] == FVID2_LCD_CTRL_DRV)
        {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
            Vps_DctrlVencDivisorInfo    vencDivisors;
#endif
            UInt32                      instNum, lcdInstFound = FALSE;

            for (instNum = 0; instNum < gDispDssTestCfg.numInst; instNum++)
            {
                /* This function is called only for LCD overlay. Find the instance
                * which has LCD overlay and get panal config from this */
                if ((gDispDssTestInstCfg[instNum].panelCfg.vencId == VPS_DCTRL_DSS_VENC_LCD1) ||
                    (gDispDssTestInstCfg[instNum].panelCfg.vencId == VPS_DCTRL_DSS_VENC_LCD2) ||
                    (gDispDssTestInstCfg[instNum].panelCfg.vencId == VPS_DCTRL_DSS_VENC_LCD3))
                {
                    lcdInstFound = TRUE;
                    break;
                }
            }

            if(lcdInstFound == FALSE)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                        UT_NAME ": Error finding pipe connected to LCD overlay\r\n");
            }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
            /* Setting LCD and PCD values */
            vencDivisors.vencId     = vencId[vencCfgId];
            vencDivisors.divisorLCD = 1;
            vencDivisors.divisorPCD = 1;
            pixelClk = appObj->lcdPanelInfo.modeInfo.pixelClock;
            /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
            * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed to
            * output 29.232 * 4 MHz and set PCD as 4. */
            if (29232U == appObj->lcdPanelInfo.modeInfo.pixelClock)
            {
                pixelClk = pixelClk * 4U;
                vencDivisors.divisorPCD = 4U;
            }

            /* Configure Default frequency */
            if (gDispDssTestInstCfg[instNum].dispcAdvLcdTdmConfig.tdmEnable == FALSE)
            {
                if (gDispDssTestInstCfg[instNum].dCtrlOutInfo.dvoFormat ==
                    VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
                {
                    pixelClk = 27000 * 4U;
                    vencDivisors.divisorPCD = 4U;
                }
                else if (gDispDssTestInstCfg[instNum].dCtrlOutInfo.dvoFormat ==
                        VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
                {
                    pixelClk = 74250;
                    vencDivisors.divisorPCD = 1U;
                }
                else
                {
                    /* Keep pixel clk from lcd panel info */
                }
            }
            else
            {
                /* For TDM mode output cant be seen. Showing example configuration,
                * with the 7 inch LCD timings. If multiplied generically,
                * might exceed the pixel clk limit of 192 MHz. */
                if (gDispDssTestInstCfg[instNum].dispcAdvLcdTdmConfig.tdmParallelMode == 0x2)
                {
                    /* 12 bit parallel interface */
                    if (gDispDssTestInstCfg[instNum].dssPrms.inFmt.dataFormat ==
                        FVID2_DF_BGR24_888)
                    {
                        /* 2 clock per pixel, effective pix clk 29232 * 2. */
                        pixelClk = 29232 * 4;
                        vencDivisors.divisorPCD = 2;
                    }
                    else if (gDispDssTestInstCfg[instNum].dssPrms.inFmt.dataFormat ==
                            FVID2_DF_BGR16_565)
                    {
                        /* 2 clock per pixel, effective pix clk 29232 * 2. */
                        pixelClk = 29232 * 4;
                        vencDivisors.divisorPCD = 2;
                    }
                }
                else if (gDispDssTestInstCfg[instNum].dispcAdvLcdTdmConfig.tdmParallelMode ==
                        0x0)
                {
                    /* 8 bit parallel interface */
                    if (gDispDssTestInstCfg[instNum].dssPrms.inFmt.dataFormat ==
                        FVID2_DF_BGR24_888)
                    {
                        /* 3 clock per pixel, effective pix clk 29232 * 3. */
                        /* It should be 29232 * 6 = 175392, This cant be locked.
                        * Locking to nearest frequency */
                        pixelClk = 175400;
                        vencDivisors.divisorPCD = 2;
                    }
                    else if (gDispDssTestInstCfg[instNum].dssPrms.inFmt.dataFormat ==
                            FVID2_DF_BGR16_565)
                    {
                        /* 2 clock per pixel, effective pix clk 29232 * 2. */
                        pixelClk = 29232 * 4;
                        vencDivisors.divisorPCD = 2;
                    }
                }
                else if (gDispDssTestInstCfg[instNum].dispcAdvLcdTdmConfig.tdmParallelMode ==
                        0x3)
                {
                    /* 16 bit parallel interface */
                    if (gDispDssTestInstCfg[instNum].dssPrms.inFmt.dataFormat ==
                        FVID2_DF_BGR24_888)
                    {
                        /* 2 clock per pixel, effective pix clk 29232 * 1.5. */
                        /* It should be 29232 * 6 = 175392, This cant be locked.
                        * Locking to nearest frequency */
                        pixelClk = 175400;
                        vencDivisors.divisorPCD = 4;
                    }
                    else if (gDispDssTestInstCfg[instNum].dssPrms.inFmt.dataFormat ==
                            FVID2_DF_BGR16_565)
                    {
                        /* 1 clock per pixel, effective pix clk 29232. */
                        pixelClk = (29232 * 4);
                        vencDivisors.divisorPCD = 4;
                    }
                }
            }
            retVal = Fvid2_control(
                appObj->dctrlHandle,
                IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS,
                &vencDivisors,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(appObj->traceMask, GT_ERR,
                        UT_NAME ": DCTRL Set Venc Divisors IOCTL Failed!!!\r\n");
            }
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
            /* TDA3xx doesnot support PCD. Configure pixel clk as given from
            * LCD panel info except in below cases */
            pixelClk = appObj->lcdPanelInfo.modeInfo.pixelClock;
            if (gDispDssTestInstCfg[instNum].dCtrlOutInfo.dvoFormat ==
                VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
            {
                pixelClk = 27000;
            }
            else if (gDispDssTestInstCfg[instNum].dCtrlOutInfo.dvoFormat ==
                    VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
            {
                pixelClk = 74250;
            }
#endif

            /* Reconfigure video PLL clock to match LCD required clock */
            retVal = st_dispDssConfigureVideoPllAndClkSrc(pixelClk, vencId[vencCfgId]);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(appObj->traceMask, GT_ERR,
                          UT_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
        else if (appObj->testPrms.encDrvId[vencCfgId] == FVID2_VID_ENC_SII9022A_DRV)
        {
            /* Reconfigure video PLL clock to match Sil9022a clock */
            if (appObj->testPrms.boardMode[vencCfgId] == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
            {
                pixelClk = dctrlCfg->vencInfo.modeInfo[vencCfgId].mInfo.pixelClock * 3;
            }
            else
            {
                pixelClk = dctrlCfg->vencInfo.modeInfo[vencCfgId].mInfo.pixelClock;
            }
            retVal = st_dispDssConfigureVideoPllAndClkSrc(pixelClk, vencId[vencCfgId]);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(appObj->traceMask, GT_ERR,
                          UT_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
    }
    return (retVal);
}

static Int32 st_dispDssConfigureLCD(st_DispDssAppObj *appObj, UInt32 encInst)
{
    Int32  retVal = FVID2_SOK;
    UInt32 lcdCtrlInstId;
#if defined (SOC_TDA2PX)
#else
    UInt32 lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    UInt32 brightVal;
    UInt32 syncMode;
#endif

    UInt32 lcdCtrlDrvId;
    lcdCtrlDrvId = FVID2_LCD_CTRL_DRV;

    lcdCtrlInstId = Bsp_boardGetVideoDeviceInstId(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        appObj->testPrms.dispNodeId[encInst]);

    /* Power on LCD controller */
    retVal = Bsp_boardPowerOnDevice(lcdCtrlDrvId, lcdCtrlInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device Power On failed\r\n");
    }

    /* select lcd Controller at board level mux */
    retVal = Bsp_boardSelectDevice(lcdCtrlDrvId, lcdCtrlInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device select failed\r\n");
    }

    /* Perform any reset needed at board level */
    retVal = Bsp_boardResetDevice(lcdCtrlDrvId, lcdCtrlInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device reset failed\r\n");
    }

    /* Select specific mode */
    retVal = Bsp_boardSelectMode(
        lcdCtrlDrvId,
        lcdCtrlInstId,
        appObj->testPrms.boardMode[encInst]);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device select mode failed\r\n");
    }

    /* After TLC is powered on, some delay to get it stabilized */
    BspOsal_sleep(5);

#if defined (SOC_TDA2PX)
#else
    lcdCtrlI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        appObj->testPrms.dispNodeId[encInst]);

    lcdCtrlI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        appObj->testPrms.dispNodeId[encInst]);

    appObj->lcdCtrlCreatePrms.deviceI2cAddr[0]   = lcdCtrlI2cAddr;
    appObj->lcdCtrlCreatePrms.deviceResetGpio[0] = 0;
    appObj->lcdCtrlCreatePrms.deviceI2cInstId    = lcdCtrlI2cInstId;
    appObj->lcdCtrlCreatePrms.numDevices         = 1;

    appObj->lcdCtrlhdl[encInst] = Fvid2_create(
        FVID2_LCD_CTRL_DRV,
        0,
        &appObj->lcdCtrlCreatePrms,
        NULL,
        NULL);

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_POWER_ON,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Lcd powering on Failed!!!\r\n");
        return retVal;
    }

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Enabling backlight failed!!!\r\n");
        return retVal;
    }

    syncMode = BSP_LCD_CTRL_MODE_DE;

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC,
        &syncMode,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Selecting sync mode failed!!!\r\n");
        return retVal;
    }

    /* Brightness Value is 75% */
    brightVal = 75;

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS,
        &brightVal,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Controlling LCD brightness Failed!!!\r\n");
        return retVal;
    }

    /* Get the LCD timings */
    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_GET_PANEL_INFO,
        &appObj->lcdPanelInfo,
        NULL);
    if (retVal != BSP_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Get LCD timing failed!!!\r\n");
    }
#endif
    return retVal;
}

static Int32 st_dispDssTurnoffLCD(st_DispDssAppObj *appObj, UInt32 encInst)
{
    Int32 retVal = FVID2_SOK;

#if defined (SOC_TDA2PX)
#else
    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Disable backlight failed!!!\r\n");

        return retVal;
    }

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl[encInst],
        IOCTL_BSP_LCDCTRL_POWER_OFF,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Lcd powering Off Failed!!!\r\n");

        return retVal;
    }

    /* Delete LCD controller handle */
    retVal = Fvid2_delete(appObj->lcdCtrlhdl[encInst], NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": LCD controller handle delete failed!!!\r\n");

        return retVal;
    }
#endif
    return retVal;
}

static Int32 st_dispDssConfigureOffChipHdmi(st_DispDssAppObj *appObj, UInt32 encInst)
{
    Int32  retVal = FVID2_SOK;
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
    retVal = Bsp_boardPowerOnDevice(vidEncDrvId, vidEncInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device Power On failed\r\n");
    }

    /* select Video Encoder at board level mux */
    retVal = Bsp_boardSelectDevice(vidEncDrvId, vidEncInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device select failed\r\n");
    }

    /* Perform any reset needed at board level */
    retVal = Bsp_boardResetDevice(vidEncDrvId, vidEncInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device reset failed\r\n");
    }

    /* Select specific mode */
    retVal = Bsp_boardSelectMode(
        vidEncDrvId,
        vidEncInstId,
        appObj->testPrms.boardMode[encInst]);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR, "Device select mode failed\r\n");
    }

    if (FVID2_SOK == retVal)
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
        if (NULL == appObj->hdmiHandle)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Error: SII9022 create failed!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID,
            &hdmiId,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Error: Could not get detailed chip ID!!\r\n");
        }
        else
        {
            GT_4trace(appObj->traceMask, GT_DEBUG,
                UT_NAME "\r\nhdmiId.deviceId = %d,hdmiId.deviceProdRevId = %d, \
                hdmiId.hdcpRevTpi = %d,hdmiId.tpiRevId = %d\r\n",hdmiId.deviceId,
                hdmiId.deviceProdRevId, hdmiId.hdcpRevTpi, hdmiId.tpiRevId);
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_SII9022A_QUERY_HPD,
            &hpdPrms,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Error: Could not detect HPD!!\r\n");
        }
        else
        {
            GT_3trace(appObj->traceMask, GT_DEBUG,
                UT_NAME "\r\nhpdPrms.busError= %d, hpdPrms.hpdEvtPending= %d, \
                hpdPrms.hpdStatus= %d\r\n", hpdPrms.busError,
                hpdPrms.hpdEvtPending, hpdPrms.hpdStatus);
        }
    }

    if (FVID2_SOK == retVal)
    {

        BspVidEncConfigParams_init(&modePrms);
        modePrms.standard = appObj->testPrms.standard[encInst];
        modePrms.videoIfMode = FVID2_VIFM_SCH_DS_AVID_VSYNC;
        modePrms.videoIfWidth = FVID2_VIFW_24BIT;
        modePrms.videoDataFormat = FVID2_DF_RGB24_888;

        retVal = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_VID_ENC_SET_MODE,
            &modePrms,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Error: Could not set mode!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_start(appObj->hdmiHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Error: Off-chip HDMI start failed!!\r\n");
        }
    }

    if ((FVID2_SOK != retVal) && (NULL != appObj->hdmiHandle))
    {
        /* Close HDMI transmitter */
        retVal += Fvid2_delete(appObj->hdmiHandle, NULL);
        appObj->hdmiHandle = NULL;
    }

    return retVal;

}

static Int32 st_dispDssDeconfigureOffChipHdmi(st_DispDssAppObj *appObj, UInt32 encInst)
{
    Int32 retVal = FVID2_SOK;

    if (NULL != appObj->hdmiHandle)
    {
        retVal = Fvid2_stop(appObj->hdmiHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Error: Off-chip HDMI stop failed!!\r\n");
        }
    }

    if (NULL != appObj->hdmiHandle)
    {
        /* Close HDMI transmitter */
        retVal += Fvid2_delete(appObj->hdmiHandle, NULL);
        appObj->hdmiHandle = NULL;
    }

    return (retVal);

}

Int32 st_dispDssConfigDctrlPipe(st_DispDssAppObj *appObj)
{
    Vps_DssDispcOvlyPipeConfig *ovlpipecfg;
    Int32 retVal = FVID2_SOK;
    st_DispDssInstObj          *instObj;

    instObj    = &appObj->instObj;
    ovlpipecfg = &instObj->ovlpipeconfig;

    retVal += Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS,
        ovlpipecfg,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
    }

    return retVal;
}

Int32 st_dispDssDctrlDelete(st_DispDssAppObj *appObj)
{
    Int32 retVal = FVID2_SOK;
    Vps_DctrlConfig *dctrlCfg;
    UInt32 encInst, sdVencEnable;

    /* Turn Off the Video Encoders/LCD controllers if required */
    for (encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        if (appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
        {
            /* Turn off LCD controller only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = st_dispDssTurnoffLCD(appObj, encInst);
            }
        }
        else if (appObj->testPrms.encDrvId[encInst] == FVID2_VID_ENC_SII9022A_DRV )
        {
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = st_dispDssDeconfigureOffChipHdmi(appObj, encInst);
            }
        }
        else if (appObj->testPrms.isSdVenc[encInst] == TRUE)
        {
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                sdVencEnable = FALSE;
                /* SD-VENC Power off */
                retVal = Fvid2_control(
                    appObj->dctrlHandle,
                    IOCTL_VPS_DCTRL_ENABLE_SDVENC,
                    &sdVencEnable,
                    NULL);
            }
        }
    }
    dctrlCfg = &appObj->dctrlCfg;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        NULL);

    /* Delete DCTRL handle */
    retVal = Fvid2_delete(appObj->dctrlHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL handle delete failed!!!\r\n");
        return retVal;
    }

    return retVal;
}

static Int32 st_dispDssPLLInit(void)
{
    Int32 retVal = FVID2_SOK;
    UInt32 pcd = 1U;

    if (gDispDssTestInstCfg[0].panelCfg.vencId != VPS_DCTRL_DSS_VENC_HDMI)
    {
        if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
        {
            if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
            {
                /* TDA3xx doesnot support pcd */
                pcd = 1U;
            }
            else
            {
                pcd = 4U;
            }
            /* Configure Default pixel clk.
             * Pass default pixel clk for the 7inch LCD for initialization.
             * This will be overridden later */
            retVal = st_dispDssConfigureVideoPllAndClkSrc(29232 * pcd,
                gDispDssTestInstCfg[0].panelCfg.vencId);
        }
    }
    else
    {
        retVal = Bsp_platformEnableHdmiPll(TRUE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      UT_NAME ": Enabling HDMI PLL Failed!!!\r\n");
        }
    }

    return retVal;
}

static Int32 st_dispDssConfigureVideoPllAndClkSrc(Uint32 pixelClk, UInt32 vencId)
{
    Bsp_PlatformSetPllFreq vPllCfg;
    Bsp_PlatformVencSrc    vencClkCfg = {0};
    Int32 retVal = FVID2_SOK;

    if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
    {
        vPllCfg.videoPll = BSP_PLATFORM_PLL_EVE_VID_DSP;
    }
    else
    {
        /* For LCD resolution 800x480@60fps we need 29.232Mhz */
        if (vencId == VPS_DCTRL_DSS_VENC_LCD1)
        {
            vPllCfg.videoPll = BSP_PLATFORM_PLL_VIDEO1;
        }
        else
        {
        #ifdef SOC_TDA2EX
            vPllCfg.videoPll = BSP_PLATFORM_PLL_VIDEO1;
        #else
            vPllCfg.videoPll = BSP_PLATFORM_PLL_VIDEO2;
        #endif
        }
    }

    vPllCfg.pixelClk = pixelClk;
    vPllCfg.chooseMaxorMinMN = (UInt32) BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN;
    retVal = Bsp_platformSetPllFreq(&vPllCfg);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  UT_NAME ": Configuring Pll Failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        if (vencId == VPS_DCTRL_DSS_VENC_LCD1)
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD1;
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT1;
            if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
            {
                vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_EVE_VID_DSP;
            }
        }
        else if (vencId == VPS_DCTRL_DSS_VENC_LCD2)
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD2;
            #ifdef SOC_TDA2EX
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3;
            #else
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO2_CLKOUT3;
            #endif
        }
        else if (vencId == VPS_DCTRL_DSS_VENC_LCD3)
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD3;
            #ifdef SOC_TDA2EX
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3;
            #else
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO2_CLKOUT1;
            #endif
        }
        else
        {
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Bsp_platformSetVencClkSrc(&vencClkCfg);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      UT_NAME ": Setting Venc clock source Failed!!!\r\n");
        }
    }

    return retVal;
}

