/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 *  \file st_dispDssVidPpl1Task.c
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

void st_dispDssInitParams(st_DispDssAppObj *appObj);
static Int32 st_dispDssCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved);
static Int32 st_dispDssGetTestInstcfgID(st_DispDssAppObj *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Semaphore_Handle      gStDispDssMasterTaskSem;
extern Semaphore_Handle      gStDispDssVidPpl1TaskSem;
extern Queue_Handle          gVidPpl1msgQueue;
extern st_DispDssTestCfg     gDispDssTestCfg;
extern st_DispDssTestInstCfg gDispDssTestInstCfg[VPS_DISP_INST_MAX];
UInt32 gTestVal1 = 0;
extern st_DispDssAppObj      gAppDispDssObj[VPS_DISP_INST_MAX];
extern st_DispDssUtObj       gStDispDssObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_dispDssVidPpl1TestTask
 */
void st_dispDssVidPpl1TestTask(UArg arg0, UArg arg1)
{
    Int32  retVal = FVID2_SOK;
    st_DispDssMsgObj       *vidPpl1TskmsgObj;
    st_DispDssAppObj       *appObj;
    st_DispDssInstObj *instObj;
    UInt32 flag    = 1;
    UInt32 msgFlag = 1;

    appObj             = (st_DispDssAppObj *) arg0;
    appObj->taskId     = VPS_DISP_INST_DSS_VID1 + 1;
    instObj            = &appObj->instObj;
    appObj->taskResult = FVID2_SOK;

    Semaphore_pend(gStDispDssVidPpl1TaskSem, BIOS_WAIT_FOREVER);

    while (1)
    {
        if ((!flag) | (appObj->taskResult != FVID2_SOK))
        {
            Semaphore_post(gStDispDssMasterTaskSem);
            Semaphore_pend(gStDispDssVidPpl1TaskSem, BIOS_WAIT_FOREVER);
        }

        if (msgFlag)
        {
            vidPpl1TskmsgObj = Queue_get(gVidPpl1msgQueue);
            flag = 0;

            switch (vidPpl1TskmsgObj->cmd)
            {
                case CREATE:

                    retVal = st_dispDssCreatePhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "Create phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }

                    break;

                case CONTROL:
                    retVal = st_dispDssControlPhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "Control phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case ALLOC_AND_QUEUE:
                    retVal = st_dispDssAllocAndQueuePhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "ALLOC_AND_QUEUE phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case START:
                    retVal = Fvid2_start(instObj->drvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  UT_NAME ": Display Start Failed!!!\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case STOP:
                    retVal = Fvid2_stop(instObj->drvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  UT_NAME ": Display Stop Failed!!!\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case DELETE:
                    retVal = st_dispDssDeletePhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "Delete phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

Int32 st_dispDssCreatePhase(st_DispDssAppObj *appObj)
{
    Int32 retVal = FVID2_SOK;
    st_DispDssInstObj *instObj;

    st_dispDssInitParams(appObj);

    instObj = &appObj->instObj;

    instObj->drvHandle = Fvid2_create(
        FVID2_VPS_DISP_DRV,
        instObj->instId,
        &instObj->createPrms,
        &instObj->createStatus,
        &instObj->cbPrms);
    if ((NULL == instObj->drvHandle) ||
        (instObj->createStatus.retVal != FVID2_SOK))
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Display Create Failed!!!\r\n");
        return FVID2_EFAIL;
    }

    BspUtils_appPrintDispCreateStatus(&instObj->createStatus);

    return retVal;
}

void st_dispDssInitParams(st_DispDssAppObj *appObj)
{
    UInt32 testInstcfgID;
    st_DispDssInstObj *instObj;

    instObj = &appObj->instObj;

    appObj->maxWidth  = ST_DISP_DSS_BUF_WIDTH;
    appObj->maxHeight = ST_DISP_DSS_BUF_HEIGHT;

    testInstcfgID = st_dispDssGetTestInstcfgID(appObj);

    switch (gDispDssTestInstCfg[testInstcfgID].videoNode)
    {
        case VID1:
            appObj->instObj.instId = VPS_DISP_INST_DSS_VID1;
            break;

        case VID2:
            appObj->instObj.instId = VPS_DISP_INST_DSS_VID2;
            break;

        case VID3:
            appObj->instObj.instId = VPS_DISP_INST_DSS_VID3;
            break;

        case GFX1:
            appObj->instObj.instId = VPS_DISP_INST_DSS_GFX1;
            break;
    }

    appObj->instObj.encDrvId = FVID2_LCD_CTRL_DRV;

    appObj->instObj.frameSwitchRate =
        gDispDssTestInstCfg[testInstcfgID].frameSwitchRate;

    memcpy(&appObj->instObj.dssPrms.inFmt,
           &gDispDssTestInstCfg[testInstcfgID].dssPrms.inFmt,
           sizeof (Fvid2_Format));
    appObj->instObj.dssPrms.tarWidth =
        gDispDssTestInstCfg[testInstcfgID].dssPrms.tarWidth;
    appObj->instObj.dssPrms.tarHeight =
        gDispDssTestInstCfg[testInstcfgID].dssPrms.tarHeight;
    appObj->instObj.dssPrms.posX =
        gDispDssTestInstCfg[testInstcfgID].dssPrms.posX;
    appObj->instObj.dssPrms.posY =
        gDispDssTestInstCfg[testInstcfgID].dssPrms.posY;
    appObj->instObj.dssPrms.memType =
        gDispDssTestInstCfg[testInstcfgID].dssPrms.memType;

    if (Vps_dispIsVidInst(appObj->instObj.instId))
    {
        appObj->instObj.dssPrms.vidCfg = &appObj->instObj.vidCfg;

        memcpy(&appObj->instObj.dssPrms.vidCfg->pipeCfg,
               &gDispDssTestInstCfg[testInstcfgID].vidCfg.pipeCfg,
               sizeof (Vps_DssDispcVidPipeConfig));
        if (gDispDssTestInstCfg[testInstcfgID].vidadvDmaCfg.burstSize == 3)
        {
            appObj->instObj.dssPrms.vidCfg->advDmaCfg = NULL;
        }
        else
        {
            appObj->instObj.dssPrms.vidCfg->advDmaCfg =
                &appObj->instObj.advDmaCfg;
            memcpy(appObj->instObj.dssPrms.vidCfg->advDmaCfg,
                   &gDispDssTestInstCfg[testInstcfgID].vidadvDmaCfg,
                   sizeof (Vps_DssDispcAdvDmaConfig));
        }

        if (gDispDssTestInstCfg[testInstcfgID].vidvc1Cfg.enable == 0)
        {
            appObj->instObj.dssPrms.vidCfg->vc1Cfg = NULL;
        }
        else
        {
            appObj->instObj.dssPrms.vidCfg->vc1Cfg = &appObj->instObj.vc1Cfg;
            memcpy(appObj->instObj.dssPrms.vidCfg->vc1Cfg,
                   &gDispDssTestInstCfg[testInstcfgID].vidvc1Cfg,
                   sizeof (Vps_DssDispcVidVC1Config));
        }
    }
    else
    {
        appObj->instObj.dssPrms.vidCfg = NULL;
    }

    if (Vps_dispIsGfxInst(appObj->instObj.instId))
    {
        appObj->instObj.dssPrms.gfxCfg = &appObj->instObj.gfxCfg;

        memcpy(&appObj->instObj.dssPrms.gfxCfg->pipeCfg,
               &gDispDssTestInstCfg[testInstcfgID].gfxCfg.pipeCfg,
               sizeof (Vps_DssDispcGfxPipeConfig));

        if (gDispDssTestInstCfg[testInstcfgID].gfxadvDmaCfg.burstSize == 3)
        {
            appObj->instObj.dssPrms.gfxCfg->advDmaCfg = NULL;
        }
        else
        {
            appObj->instObj.dssPrms.gfxCfg->advDmaCfg =
                &appObj->instObj.advDmaCfg;
            memcpy(appObj->instObj.dssPrms.gfxCfg->advDmaCfg,
                   &gDispDssTestInstCfg[testInstcfgID].gfxadvDmaCfg,
                   sizeof (Vps_DssDispcAdvDmaConfig));
        }
    }
    else
    {
        appObj->instObj.dssPrms.gfxCfg = NULL;
    }

    memcpy(&appObj->instObj.ovlpipeconfig,
           &gDispDssTestInstCfg[testInstcfgID].ovlpipecfg,
           sizeof (Vps_DssDispcOvlyPipeConfig));
    appObj->instObj.videoNode   = gDispDssTestInstCfg[testInstcfgID].videoNode;
    appObj->instObj.overlayNode =
        gDispDssTestInstCfg[testInstcfgID].overlayNode;
    appObj->instObj.dispNode = gDispDssTestInstCfg[testInstcfgID].dispNode;
    memcpy(&appObj->instObj.mInfo, &gDispDssTestInstCfg[testInstcfgID].mInfo,
           sizeof (Fvid2_ModeInfo));

    appObj->testPrms.testCaseId   = gDispDssTestCfg.testCaseId;
    appObj->testPrms.testCaseName = gDispDssTestCfg.testCaseName;
    appObj->testPrms.numHandles   = gDispDssTestCfg.numInst;
    memcpy(&appObj->panelCfg, &gDispDssTestInstCfg[testInstcfgID].panelCfg,
           sizeof (Vps_DssDispcOvlyPanelConfig));

    VpsDispCreateParams_init(&appObj->instObj.createPrms);

    Fvid2CbParams_init(&appObj->instObj.cbPrms);
    instObj->cbPrms.cbFxn   = &st_dispDssCbFxn;
    instObj->cbPrms.appData = appObj;
    instObj->appObj         = appObj;
    appObj->dctrlHandle     = gAppDispDssObj[0].dctrlHandle;
    memcpy(&appObj->dctrlCfg, &gAppDispDssObj[0].dctrlCfg,
           sizeof (Vps_DctrlConfig));

    instObj->inDataFmt =
        (Fvid2_DataFormat) appObj->instObj.dssPrms.inFmt.dataFormat;

    if (Fvid2_isDataFmtSemiPlanar(instObj->inDataFmt))
    {
        instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            appObj->instObj.dssPrms.inFmt.pitch[0];
        instObj->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            appObj->instObj.dssPrms.inFmt.pitch[1];
    }
    else if (Fvid2_isDataFmtYuv422I(instObj->inDataFmt))
    {
        instObj->pitch[FVID2_YUV_INT_ADDR_IDX] =
            appObj->instObj.dssPrms.inFmt.pitch[0];
    }
    else if (Fvid2_isDataFmtRgb16bit(instObj->inDataFmt))
    {
        instObj->pitch[FVID2_YUV_INT_ADDR_IDX] =
            appObj->instObj.dssPrms.inFmt.pitch[0];
    }
    else if (Fvid2_isDataFmtRgb24bit(instObj->inDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        instObj->pitch[FVID2_RGB_ADDR_IDX] =
            appObj->instObj.dssPrms.inFmt.pitch[0];
    }
    else if (Fvid2_isDataFmtRgb32bit(instObj->inDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        instObj->pitch[FVID2_RGB_ADDR_IDX] =
            appObj->instObj.dssPrms.inFmt.pitch[0];
    }

    instObj->inWidth      = appObj->instObj.dssPrms.inFmt.width;
    instObj->inHeight     = appObj->instObj.dssPrms.inFmt.height;
    instObj->isFieldMerge = appObj->instObj.dssPrms.inFmt.fieldMerged[0];
    instObj->inScanFormat = appObj->instObj.dssPrms.inFmt.scanFormat;
    instObj->posx         = appObj->instObj.dssPrms.posX;
    instObj->posy         = appObj->instObj.dssPrms.posY;

    /* Get the required buffer info */
    appObj->bufInfo = st_dispDssGetBufInfo(
        appObj,
        instObj->inDataFmt,
        instObj->inScanFormat,
        instObj->isFieldMerge,
        instObj->pitch[0]);
    if (NULL == appObj->bufInfo)
    {
        GT_1trace(appObj->traceMask, GT_ERR,
                  "%s: Get buffer info failed\r\n", __FUNCTION__);
    }
    else if (NULL == appObj->bufInfo->bufAddr)
    {
        UInt32 bufCfgId;
        /* The Buffer was not loaded in the beginning, Load it now. */
        if(FVID2_SOK == st_dispDssGetBufCfgId(instObj->inDataFmt, &bufCfgId))
        {
            st_dispDssLoadBuf(&gStDispDssObj, &gDispDssLoadBufCfg[bufCfgId]);
        }
    }
    else
    {
        /* Do nothing */
    }

    appObj->bufferIndex = 0;
    return;
}

Int32 st_dispDssDeletePhase(st_DispDssAppObj *appObj)
{
    Int32              retVal = FVID2_SOK;
    st_DispDssInstObj *instObj;
    Fvid2_FrameList    frmList;
    Vps_DctrlConfig   *dctrlCfg;
    Fvid2_ModeInfo    *mInfo;

    dctrlCfg                    = &appObj->dctrlCfg;
    dctrlCfg->useCase           = 0;
    dctrlCfg->numEdges          = 0;
    dctrlCfg->vencInfo.numVencs = 0;
    dctrlCfg->vencInfo.modeInfo[0u].vencId = 0;
    mInfo                        = &dctrlCfg->vencInfo.modeInfo[0u].mInfo;
    mInfo->standard              = 0;
    mInfo->width                 = 0;
    mInfo->height                = 0;
    mInfo->scanFormat            = 0;
    mInfo->pixelClock            = 0u;
    mInfo->fps                   = 0u;
    mInfo->hFrontPorch           = 0u;
    mInfo->hBackPorch            = 0u;
    mInfo->hSyncLen              = 0u;
    mInfo->vFrontPorch           = 0u;
    mInfo->vBackPorch            = 0u;
    mInfo->vSyncLen              = 0u;
    dctrlCfg->vencInfo.tiedVencs = 0u;

    instObj = &appObj->instObj;

    /* Dequeue all the request from the driver */
    while (1u)
    {
        retVal = Fvid2_dequeue(
            instObj->drvHandle,
            &frmList,
            0u,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": Display Delete Failed!!!\r\n");
        return retVal;
    }

    GT_0trace(appObj->traceMask, GT_INFO,
              UT_NAME ": Display delete complete!!\r\n");

    return retVal;
}

Int32 st_dispDssControlPhase(st_DispDssAppObj *appObj)
{
    Int32  retVal = FVID2_SOK;
    st_DispDssInstObj           *instObj;
    Vps_DssDispcOvlyPanelConfig *panelCfg;

    instObj  = &appObj->instObj;
    panelCfg = &appObj->panelCfg;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_OVLY_PARAMS,
        panelCfg,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
        return retVal;
    }

    retVal = st_dispDssConfigDctrlPipe(appObj);

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_VPS_DISP_SET_DSS_PARAMS,
        &instObj->dssPrms,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(appObj->traceMask, GT_ERR,
                  UT_NAME ": DSS Set Params IOCTL Failed!!!\r\n");
        return retVal;
    }

    return retVal;
}

Int32 st_dispDssUpdateFrameList(st_DispDssAppObj *appObj,
                                Fvid2_FrameList  *frmList)
{
    Int32  retVal = FVID2_SOK;
    UInt32 index;
    UInt32 yFld1Offset;
    UInt32 cbCrFld0Offset;
    UInt32 cbCrFld1Offset;
    Fvid2_Frame       *frm;
    st_DispDssInstObj *instObj;

    instObj = &appObj->instObj;

    frm = &instObj->frames[0u];

    index = appObj->bufferIndex;

    frm[index].fid     = FVID2_FID_FRAME;
    frm[index].appData = instObj;

    if (appObj->instObj.dssPrms.inFmt.fieldMerged[0] == FALSE)
    {
        if (FVID2_DF_YUV422I_YUYV == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] =
                appObj->bufInfo->yBufAddrEven[index];
        }
        else if (FVID2_DF_BGR24_888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgrBufAddr[index];
        }
        else if (FVID2_DF_ABGR32_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->abgrBufAddr[index];
        }
        else if (FVID2_DF_YUV422I_UYVY == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->uyvyBufAddr[index];
        }
        else if (FVID2_DF_BGRA32_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgraBufAddr[index];
        }
        else if (FVID2_DF_XBGR24_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->xbgrBufAddr[index];
        }
        else if (FVID2_DF_BGRX24_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgrxBufAddr[index];
        }
        else if (FVID2_DF_BGR16_565 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgr16565BufAddr[index];
        }
        else if (FVID2_DF_BGR16_565_A8 == appObj->bufInfo->bufCfg.dataFmt)
        {
            if (FVID2_DF_BGR16_565 == appObj->instObj.inDataFmt)
            {
                frm[index].addr[0][0] = appObj->bufInfo->bgr16565BufAddr[index];
            }
            else if ((FVID2_DF_BGR16_565_A8 == appObj->instObj.inDataFmt)
            || (FVID2_DF_RGB16_565_A8 == appObj->instObj.inDataFmt))
            {
                frm[index].addr[0][0] = appObj->bufInfo->bgr16565BufAddr[index];
                frm[index].addr[0][1] = appObj->bufInfo->yBufAddrOdd[index];
            }
        }
        else if (FVID2_DF_YUV420SP_UV == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->yBufAddrEven[index];
            frm[index].addr[0][1] = appObj->bufInfo->cBufAddrEven[index];
            frm[index].addr[1][0] = appObj->bufInfo->yBufAddrOdd[index];
            frm[index].addr[1][1] = appObj->bufInfo->cBufAddrOdd[index];
        }
        /* Not Tested*/
        else if (FVID2_DF_YUV422SP_UV == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->yBufAddrEven[index];
            frm[index].addr[0][1] = appObj->bufInfo->cBufAddrEven[index];
        }
    }
    else
    {
        if (FVID2_DF_YUV422I_YUYV == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] =
                appObj->bufInfo->yBufAddrEven[index];
            yFld1Offset = ((UInt32) appObj->bufInfo->yBufAddrEven[index] +
                           appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_BGR24_888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgrBufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->bgrBufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_ABGR32_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->abgrBufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->abgrBufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_YUV422I_UYVY == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->uyvyBufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->uyvyBufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_BGRA32_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgraBufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->bgraBufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_XBGR24_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->xbgrBufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->xbgrBufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_BGRX24_8888 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgrxBufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->bgrxBufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_BGR16_565 == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->bgr16565BufAddr[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->bgr16565BufAddr[index] +
                 appObj->bufInfo->bufCfg.pitch);
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
        }
        else if (FVID2_DF_YUV420SP_UV == appObj->bufInfo->bufCfg.dataFmt)
        {
            frm[index].addr[0][0] = appObj->bufInfo->yBufAddrEven[index];
            yFld1Offset           =
                ((UInt32) appObj->bufInfo->yBufAddrEven[index] +
                 appObj->bufInfo->bufCfg.pitch);
            cbCrFld0Offset = ((UInt32) appObj->bufInfo->yBufAddrEven[index] +
                              (appObj->bufInfo->bufCfg.pitch *
                               appObj->bufInfo->bufCfg.height));
            cbCrFld1Offset = ((UInt32) cbCrFld0Offset +
                              appObj->bufInfo->bufCfg.pitch);

            frm[index].addr[0][1] = (Ptr) cbCrFld0Offset;
            frm[index].addr[1][0] = (Ptr) yFld1Offset;
            frm[index].addr[1][1] = (Ptr) cbCrFld1Offset;
        }
    }

    frmList->numFrames  = 1u;
    frmList->frames[0u] = &frm[index];

    appObj->submittedFrames++;

    if (0u == (appObj->submittedFrames % instObj->frameSwitchRate))
    {
        appObj->bufferIndex++;
    }

    if (appObj->bufferIndex == appObj->bufInfo->bufCfg.numBuffers)
    {
        appObj->bufferIndex = 0u;
    }

    return (retVal);
}

Int32 st_dispDssAllocAndQueuePhase(st_DispDssAppObj *appObj)
{
    Int32              retVal = FVID2_SOK;
    UInt32             frmId;
    Fvid2_FrameList    frmList;
    st_DispDssInstObj *instObj;

    instObj = &appObj->instObj;

    for (frmId = 0u; frmId < ST_DISP_DSS_MAX_FRAMES_PER_HANDLE; frmId++)
    {
        st_dispDssUpdateFrameList(appObj, &frmList);

        /*
         * queue the frames in frmList
         * All allocate frames are queued here as an example.
         * In general atleast 2 frames per channel need to queued
         * before starting display,
         * else frame will get dropped until frames are queued
         */
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0u);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Display Queue Failed!!!\r\n");
            break;
        }
    }

    return (retVal);
}

/**
 *  st_dispDssCbFxn
 *  \brief Driver callback function.
 */
static Int32 st_dispDssCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32              retVal = FVID2_SOK;
    st_DispDssAppObj  *appObj = (st_DispDssAppObj *) appData;;
    st_DispDssInstObj *instObj;
    Fvid2_FrameList    frmList;

    instObj = &appObj->instObj;

    retVal = Fvid2_dequeue(
        instObj->drvHandle,
        &frmList,
        0u,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        st_dispDssUpdateFrameList(appObj, &frmList);

        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0u);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(appObj->traceMask, GT_ERR,
                      UT_NAME ": Display Queue Failed!!!\r\n");
        }
    }

    instObj->appObj->callBackCount++;

    return (retVal);
}

static Int32 st_dispDssGetTestInstcfgID(st_DispDssAppObj *appObj)
{
    UInt32 instID, testInstcfgID = 0U;

    for (instID = 0; instID < gDispDssTestCfg.numInst; instID++)
    {
        if (gDispDssTestInstCfg[instID].videoNode == (appObj->taskId - 1))
        {
            testInstcfgID = instID;
            break;
        }
    }

    return testInstcfgID;
}

