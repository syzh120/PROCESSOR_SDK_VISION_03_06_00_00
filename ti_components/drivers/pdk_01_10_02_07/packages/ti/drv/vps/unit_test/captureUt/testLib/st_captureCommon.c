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
 *  \file st_captureCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_capture.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static Int32 st_captDetectVideo(st_CaptApp_Obj     *appObj,
                                st_CaptApp_InstObj *instObj,
                                const st_CaptUtObj *utObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static UInt32 glbTestCounter = 0;
static UInt32 glbPassCounter = 0;
static UInt32 glbFailCounter = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Create and configure video decoder.
 */
Int32 st_captCreateVidDec(st_CaptApp_Obj     *appObj,
                          st_CaptApp_InstObj *instObj,
                          const st_CaptUtObj *utObj,
                          UInt32              instanceCnt)
{
    Int32  retVal;
    UInt32 decInstId, decI2cInstId, decI2cAddr;
    Vps_CaptCreateParams  *pVipCreatePrms;
    Bsp_VidDecChipIdParams decChipIdPrms;
    Bsp_VidDecChipIdStatus decChipIdStatus;
    Bsp_VidDecCreateStatus decCreateStatus;

    pVipCreatePrms = &instObj->createPrms;

    decInstId = Bsp_boardGetVideoDeviceInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    decI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    decI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);

    /* Power on video decoder */
    retVal = Bsp_boardPowerOnDevice(instObj->decDrvId, decInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(utObj->traceMask, GT_ERR, "Device power-on failed\r\n");
    }
    if (FVID2_SOK == retVal)
    {
        /* select video decoder at board level mux */
        retVal = Bsp_boardSelectDevice(instObj->decDrvId, decInstId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR, "Device select failed\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Perform any reset needed at board level */
        retVal = Bsp_boardResetDevice(instObj->decDrvId, decInstId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR, "Device reset failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Select specific mode */
        retVal = Bsp_boardSelectMode(
            instObj->decDrvId,
            decInstId,
            appObj->testPrms->testConfig.boardMode);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR, "Device select mode failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        instObj->decCreatePrms.deviceI2cInstId    = decI2cInstId;
        instObj->decCreatePrms.numDevicesAtPort   = 1U;
        instObj->decCreatePrms.deviceI2cAddr[0]   = decI2cAddr;
        instObj->decCreatePrms.deviceResetGpio[0] = BSP_VID_DEC_GPIO_NONE;
        instObj->decHandle = Fvid2_create(
            instObj->decDrvId,
            decInstId,
            &instObj->decCreatePrms,
            &decCreateStatus,
            NULL);
        GT_assert(utObj->traceMask, instObj->decHandle != NULL);

        decChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->decHandle,
            IOCTL_BSP_VID_DEC_GET_CHIP_ID,
            &decChipIdPrms,
            &decChipIdStatus);
        GT_assert(utObj->traceMask, (retVal == FVID2_SOK));

        instObj->decVideoModePrms.videoIfWidth =
            pVipCreatePrms->videoIfWidth;
        instObj->decVideoModePrms.videoDataFormat =
            appObj->testPrms->testInstPrms[instanceCnt].vipParams.inDataFmt;
        instObj->decVideoModePrms.standard =
            appObj->testPrms->testInstPrms[instanceCnt].standard;
        instObj->decVideoModePrms.videoIfMode = pVipCreatePrms->videoIfMode;
        instObj->decVideoModePrms.videoSystem =
            BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT;
        instObj->decVideoModePrms.videoAutoDetectTimeout =
            FVID2_TIMEOUT_FOREVER;
        instObj->decVideoModePrms.videoCropEnable = FALSE;

        GT_6trace(utObj->traceMask, GT_INFO,
                  UT_NAME ": VIP %d: VID DEC %04x (0x%02x): %04x:%04x:%04x\r\n",
                  instObj->instId,
                  instObj->decDrvId,
                  instObj->decCreatePrms.deviceI2cAddr[0],
                  decChipIdStatus.chipId,
                  decChipIdStatus.chipRevision,
                  decChipIdStatus.firmwareVersion);

        st_captDetectVideo(appObj, instObj, utObj);
    }
    return (retVal);
}

/**
 *  \brief Create and configure video sensor.
 */
Int32 st_captCreateVidSensor(st_CaptApp_Obj     *appObj,
                             st_CaptApp_InstObj *instObj,
                             const st_CaptUtObj *utObj,
                             UInt32              instanceCnt)
{
    Int32  retVal;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr, boardId;
    Bsp_VidSensorChipIdParams sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus sensorChipIdStatus;
    Bsp_VidSensorCreateStatus sensorCreateStatus;
    Vps_CaptCreateParams     *pVipCreatePrms;

    pVipCreatePrms = &instObj->createPrms;

    sensorInstId = Bsp_boardGetVideoDeviceInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    sensorI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);

    GT_3trace(utObj->traceMask, GT_DEBUG,
              " Sensor Inst ID-%d-Sensor I2C Inst ID %d,sensorI2cAddr: 0x%x\r\n",
              sensorInstId,
              sensorI2cInstId, sensorI2cAddr);

    /* Power on video sensor at board level mux */
    retVal = Bsp_boardPowerOnDevice(instObj->decDrvId, sensorInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(utObj->traceMask, GT_ERR, "Device power-on failed\r\n");
    }
    if (FVID2_SOK == retVal)
    {
        /* select video sensor at board level mux */
        retVal = Bsp_boardSelectDevice(instObj->decDrvId, sensorInstId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR, "Device select failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Select specific mode */
        retVal = Bsp_boardSelectMode(
            instObj->decDrvId,
            sensorInstId,
            appObj->testPrms->testConfig.boardMode);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR, "Device select mode failed\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        boardId = Bsp_boardGetId();

        if ((BSP_BOARD_MULTIDES == boardId) &&
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId))
        {
            retVal = BspUtils_appConfSerDeSer(instObj->decDrvId, sensorInstId);
            if (retVal != FVID2_SOK)
            {
                GT_1trace(
                    utObj->traceMask, GT_ERR,
                    UT_NAME
                    ": Configuring MultiDes instance %d failed!!!\r\n",
                    sensorInstId);
            }
        }

        instObj->sensorCreatePrms.deviceI2cInstId    = sensorI2cInstId;
        instObj->sensorCreatePrms.numDevicesAtPort   = 1U;
        instObj->sensorCreatePrms.deviceI2cAddr[0]   = sensorI2cAddr;
        instObj->sensorCreatePrms.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
        instObj->sensorCreatePrms.sensorCfg          = NULL;
        instObj->sensorCreatePrms.numSensorCfg       = 0U;
        instObj->decHandle = Fvid2_create(
            instObj->decDrvId,
            sensorInstId,
            &instObj->sensorCreatePrms,
            &sensorCreateStatus,
            NULL);
        GT_assert(utObj->traceMask, instObj->decHandle != NULL);

        sensorChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->decHandle,
            IOCTL_BSP_VID_SENSOR_GET_CHIP_ID,
            &sensorChipIdPrms,
            &sensorChipIdStatus);
        GT_assert(utObj->traceMask, (retVal == FVID2_SOK));

        GT_6trace(
            utObj->traceMask, GT_INFO,
            UT_NAME
            ": VIP %d: VID SENSOR %04x (0x%02x): %04x:%04x:%04x\r\n",
            instObj->instId,
            instObj->decDrvId,
            instObj->sensorCreatePrms.deviceI2cAddr[0],
            sensorChipIdStatus.chipId,
            sensorChipIdStatus.chipRevision,
            sensorChipIdStatus.firmwareVersion);

        /* Configure sensor in UYVY 8-bit 1280x720 @ 30FPS, OV only supports
         * 1280x720 @ 30FPS and VIP expects data in UYVY .
         * FOR MULDES_OV_DRV this IOCTL does nothing and returns SUCCESS. */
        if (((FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
             (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
             (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId)) &&
            (FVID2_SOK == retVal))
        {
            Bsp_VidSensorConfigParams configParams;
            configParams.videoIfWidth = pVipCreatePrms->videoIfWidth;
            configParams.dataformat   = FVID2_DF_YUV422I_UYVY;
            configParams.standard     =
                appObj->testPrms->testInstPrms[instanceCnt].standard;
            configParams.fps = FVID2_FPS_30;
            retVal           =
                Fvid2_control(instObj->decHandle,
                              IOCTL_BSP_VID_SENSOR_SET_CONFIG,
                              &configParams,
                              NULL);
            GT_assert(utObj->traceMask, (retVal == FVID2_SOK));
        }

        /* start sensor, right now only OV sensor driver is implemented */
        if (((FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
             (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
             (FVID2_VID_SENSOR_APT_AR0132_DRV == instObj->decDrvId) ||
             (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId)) &&
            (FVID2_SOK == retVal))
        {
            retVal = Fvid2_control(instObj->decHandle, FVID2_START, NULL, NULL);
            GT_assert(utObj->traceMask, (retVal == FVID2_SOK));
        }
    }

    return (retVal);
}

static Int32 st_captDetectVideo(st_CaptApp_Obj     *appObj,
                                st_CaptApp_InstObj *instObj,
                                const st_CaptUtObj *utObj)
{
    Int32  retVal;
    UInt32 chId, repeatCnt;
    Bsp_VidDecVideoStatusParams videoStatusPrms;
    Bsp_VidDecVideoStatus       videoStatus;

    GT_1trace(utObj->traceMask, GT_INFO,
              UT_NAME ": Detect video in progress for inst %d !!!\r\n",
              instObj->instId);

    retVal = Fvid2_control(
        instObj->decHandle,
        IOCTL_BSP_VID_DEC_SET_VIDEO_MODE,
        &instObj->decVideoModePrms,
        NULL);
    GT_assert(utObj->traceMask, (retVal == FVID2_SOK));

    for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
    {
        repeatCnt = 5;
        while (--repeatCnt != 0)
        {
            videoStatusPrms.channelNum = chId;
            retVal = Fvid2_control(
                instObj->decHandle,
                IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS,
                &videoStatusPrms,
                &videoStatus);
            GT_assert(utObj->traceMask, (retVal == FVID2_SOK));

            if (videoStatus.isVideoDetect)
            {
                GT_5trace(
                    utObj->traceMask, GT_INFO,
                    UT_NAME
                    ": Detected video at CH%d (%dx%d@%dHz, %d)!!!\r\n",
                    chId,
                    videoStatus.frameWidth,
                    videoStatus.frameHeight,
                    (1000000U / videoStatus.frameInterval),
                    videoStatus.isInterlaced);
                break;
            }
            BspOsal_sleep(100);
        }
    }

    GT_0trace(utObj->traceMask, GT_INFO, UT_NAME ": Detect video Done !!!\r\n");

    return (FVID2_SOK);
}

/**
 *  \brief Allocate and queue frames to driver
 */
Int32 st_captAllocAndQueueFrames(st_CaptApp_Obj     *appObj,
                                 st_CaptApp_InstObj *instObj,
                                 UInt32              fieldMerged,
                                 const st_CaptUtObj *utObj)

{
    Int32               retVal = FVID2_SOK;
    UInt32              streamId, chId, frmId, idx;
    UInt32              bufSize;
    UInt32              yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format       *fmt;
    Fvid2_Frame        *frm;
    Fvid2_FrameList     frmList;
    Vps_CaptVipOutInfo *outInfo;
    Char fileStr[50U];

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
        {
            outInfo = &instObj->vipPrms.outStreamInfo[streamId];
            fmt     = &instObj->allocFmt[streamId];
            Fvid2Format_init(fmt);

            /* base index for instObj->frames[] */
            idx =
                (VPS_CAPT_CH_PER_PORT_MAX * ST_CAPT_APP_FRAMES_PER_CH
                 * streamId) + (ST_CAPT_APP_FRAMES_PER_CH * chId);

            if (idx >= ST_CAPT_APP_MAX_FRAMES_PER_HANDLE)
            {
                idx = 0U;
            }
            frm = &instObj->frames[idx];

            /* fill format with channel specific values  */
            fmt->chNum  = Vps_captMakeChNum(instObj->instId, streamId, chId);
            fmt->width  = appObj->maxWidth;
            fmt->height = appObj->maxHeight + ST_CAPT_APP_PADDING_LINES;
            if (fieldMerged)
            {
                fmt->height *= 2;
            }
            fmt->pitch[0]       = outInfo->outFmt.pitch[0];
            fmt->pitch[1]       = outInfo->outFmt.pitch[1];
            fmt->pitch[2]       = outInfo->outFmt.pitch[2];
            fmt->fieldMerged[0] = FALSE;
            fmt->fieldMerged[1] = FALSE;
            fmt->fieldMerged[2] = FALSE;
            fmt->dataFormat     = outInfo->outFmt.dataFormat;
            fmt->scanFormat     = FVID2_SF_PROGRESSIVE;
            fmt->bpp = FVID2_BPP_BITS8; /* ignored */

            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                BspUtils_memClearOnAlloc(TRUE);
            }

            /*
             * alloc memory based on 'format'
             * Allocated frame info is put in frames[]
             * ST_CAPT_APP_FRAMES_PER_CH is the number of buffers per channel to
             * allocate
             */
            retVal = BspUtils_memFrameAlloc(fmt, frm, ST_CAPT_APP_FRAMES_PER_CH);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": Capture Frame Alloc Failed!!!\r\n");
                break;
            }

            snprintf(fileStr, sizeof (fileStr),
                     "captureOption%dInst%dCh%dStr%d",
                     (unsigned int)appObj->testPrms->testConfig.testCaseId, 
                     (unsigned int)instObj->instId,
                     (unsigned int)chId,
                     (unsigned int)streamId);
            BspUtils_memFrameGetSize(fmt, &bufSize, NULL);
            BspUtils_appPrintSaveRawCmd(
                fileStr,
                frm[0].addr[0][0],
                outInfo->outFmt.dataFormat,
                fmt->width,
                fmt->height,
                (ST_CAPT_APP_FRAMES_PER_CH * bufSize));

            for (frmId = 0U; frmId < ST_CAPT_APP_FRAMES_PER_CH; frmId++)
            {
                frm[frmId].fid        = FVID2_FID_FRAME;
                frm[frmId].appData    = instObj;
                frmList.frames[frmId] = &frm[frmId];

                if (TRUE == fieldMerged)
                {
                    /* Since BspUtils_memFrameAlloc is setting the address
                     * for only top field, set addresses for bottom fields. */
                    if (Fvid2_isDataFmtYuv422I(fmt->dataFormat))
                    {
                        yFld1Offset = (UInt32) frm[frmId].addr[0U][0U] +
                                      fmt->pitch[0U];
                        frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                    }
                    if (Fvid2_isDataFmtSemiPlanar(fmt->dataFormat))
                    {
                        yFld1Offset =
                            (UInt32) frm[frmId].addr[0U][0U] + fmt->pitch[0U];
                        cbCrFld0Offset =
                            (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                                      (fmt->pitch[0U] * appObj->maxHeight * 2U));
                        cbCrFld1Offset =
                            (UInt32) (cbCrFld0Offset + fmt->pitch[0U]);
                        frm[frmId].addr[0U][1U] = (Ptr) cbCrFld0Offset;
                        frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                        frm[frmId].addr[1U][1U] = (Ptr) cbCrFld1Offset;
                    }
                }
            }

            /* Set number of frame in frame list */
            frmList.numFrames = ST_CAPT_APP_FRAMES_PER_CH;

            /*
             * queue the frames in frmList
             * All allocate frames are queued here as an example.
             * In general atleast 2 frames per channel need to queued
             * before starting capture,
             * else frame will get dropped until frames are queued
             */
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": Capture Queue Failed!!!\r\n");
                break;
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  st_captCbFxn
 *  \brief Driver callback function.
 */
Int32 st_captCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32               retVal = FVID2_SOK;
    UInt32              streamId;
    st_CaptApp_InstObj *instObj = (st_CaptApp_InstObj *) appData;
    Fvid2_FrameList     frmList;

    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        retVal = Fvid2_dequeue(
            instObj->drvHandle,
            &frmList,
            streamId,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK == retVal)
        {
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(instObj->appObj->traceMask, GT_ERR,
                          UT_NAME ": Capture Queue Failed!!!\r\n");
            }
        }
    }

    instObj->appObj->callBackCount++;

    return (retVal);
}

/*
 *  Callback function, recieved when overflow occues in VIP
 */
Int32 st_captOverflowCbFxn(st_CaptApp_InstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(BspCaptUtTrace, (instObj != NULL));

    instObj->overflowCount++;

    /* Most of the time VIP recovers automatically. This is to give
     * some time to VIP to recover automatically
     */
    if (instObj->overflowCount > ST_CAPT_MAX_CONTI_OF_INTERRUPTS)
    {
        /* This is to stop the VIP. This will set the S/W reset bit in the
         * FIQ registers of VIP parser. This is not a blocking IOCTL.
         */
        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_VPS_CAPT_RESET_VIP_PORT,
            NULL,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(instObj->appObj->traceMask, GT_ERR,
                      UT_NAME ": Capture Stop Failed!!!\r\n");
        }

        // BspOsal_semPost(overflowSem);
    }
    return retVal;
}

/**
 *  st_captSubFrmCbFxn
 *  \brief Driver sub frame callback function.
 */
Int32 st_captSubFrmCbFxn(Fvid2_Handle handle, Fvid2_Frame *subFrame)
{
    Int32 retVal = FVID2_SOK;
    st_CaptApp_InstObj *instObj;
    Vps_CaptRtParams   *rtPrms;

    GT_assert(BspCaptUtTrace, (handle != NULL));
    GT_assert(BspCaptUtTrace, (subFrame != NULL));
    GT_assert(BspCaptUtTrace, (subFrame->appData != NULL));
    instObj = subFrame->appData;

    if (instObj->cbIdx > 0u)
    {
        instObj->sfLogInfo[instObj->sfCbIdx].eofTimeStamp =
            instObj->cbLogInfo[instObj->cbIdx - 1u].timeStamp;
        instObj->sfLogInfo[instObj->sfCbIdx].eofTimeStampDiff =
            instObj->cbLogInfo[instObj->cbIdx - 1u].timeStampDiff;
        instObj->sfLogInfo[instObj->sfCbIdx].eofIdx = instObj->cbIdx - 1u;
    }
    instObj->sfLogInfo[instObj->sfCbIdx].timeStamp =
        BspOsal_getCurTimeInMsec() -
        instObj->appObj->startTime;
    if (instObj->sfCbIdx == 0u)
    {
        instObj->sfLogInfo[instObj->sfCbIdx].timeStampDiff =
            instObj->sfLogInfo[instObj->sfCbIdx].timeStamp;
    }
    else
    {
        instObj->sfLogInfo[instObj->sfCbIdx].timeStampDiff =
            instObj->sfLogInfo[instObj->sfCbIdx].timeStamp -
            instObj->sfLogInfo[instObj->sfCbIdx - 1u].timeStamp;
    }
    instObj->sfLogInfo[instObj->sfCbIdx].frmAddress =
        (UInt32) subFrame->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_INT_ADDR_IDX];
    instObj->sfLogInfo[instObj->sfCbIdx].fid         = subFrame->fid;
    instObj->sfLogInfo[instObj->sfCbIdx].subFrameNum =
        subFrame->subFrameInfo->subFrameNum;
    instObj->sfLogInfo[instObj->sfCbIdx].numOutLines =
        subFrame->subFrameInfo->numOutLines;
    rtPrms = subFrame->perFrameCfg;
    GT_assert(instObj->appObj->traceMask, (rtPrms != NULL));
    instObj->sfLogInfo[instObj->sfCbIdx].capturedOutWidth =
        rtPrms->capturedOutWidth;
    instObj->sfLogInfo[instObj->sfCbIdx].capturedOutHeight =
        rtPrms->capturedOutHeight;

    instObj->sfCbIdx++;
    if (instObj->sfCbIdx >= ST_CAPT_LOG_MAX)
    {
        instObj->sfCbIdx = 0;
    }

    instObj->appObj->subFrmCallBackCount++;

    return (retVal);
}

/**
 *  \brief Free frames
 */
Int32 st_captFreeFrames(st_CaptApp_Obj     *appObj,
                        st_CaptApp_InstObj *instObj,
                        UInt32              fieldMerged,
                        const st_CaptUtObj *utObj)

{
    Int32         retVal = FVID2_SOK;
    UInt32        streamId, chId, idx;
    Fvid2_Format *fmt;
    Fvid2_Frame  *frm;
    Char          fileStr[50U];
    Char          fileNameString[100U];
    UInt32        bufSize, bytesWritten;

    GT_assert(utObj->traceMask,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));

    /* for every stream and channel in a capture handle */
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
        {
            fmt = &instObj->allocFmt[streamId];

            /* base index for instObj->frames[] */
            idx =
                (VPS_CAPT_CH_PER_PORT_MAX * ST_CAPT_APP_FRAMES_PER_CH
                 * streamId) + (ST_CAPT_APP_FRAMES_PER_CH * chId);

            if (idx >= ST_CAPT_APP_MAX_FRAMES_PER_HANDLE)
            {
                idx = 0U;
            }
            frm = &instObj->frames[idx];

            /* Save buffer to SD card if present */
            snprintf(fileStr, sizeof (fileStr),
                     "captureUtTC%dInst%dCh%dStr%d",
                     (unsigned int)appObj->testPrms->testConfig.testCaseId,
                     (unsigned int)instObj->instId, 
                     (unsigned int)chId, 
                     (unsigned int)streamId);
            BspUtils_memFrameGetSize(fmt, &bufSize, NULL);
            BspUtils_appGetFileName(
                fileNameString, sizeof (fileNameString), fileStr,
                fmt->dataFormat, fmt->width, fmt->height);
            BspUtils_appSaveFileToSd(
                    fileNameString,
                    "/captUtVipOutBuff",
                    frm[0].addr[0][0],
                    (ST_CAPT_APP_FRAMES_PER_CH * bufSize),
                    &bytesWritten);

            retVal |= BspUtils_memFrameFree(fmt, frm, ST_CAPT_APP_FRAMES_PER_CH);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": Capture Frame Free Failed!!!\r\n");
            }
        }
    }

    return (retVal);
}

void st_logTestResult(Int32  testResult,
                      UInt32 testCaseId,
                      char  *testcaseInfo)
{
    if (BSP_SOK == testResult)
    {
        glbPassCounter++;
        GT_1trace(BspCaptUtTrace, GT_INFO,
                  " |TEST RESULT|PASS|%d|\r\n", testCaseId);
    }
    else
    {
        glbFailCounter++;
        GT_1trace(BspCaptUtTrace, GT_INFO,
                  " |TEST RESULT|FAIL|%d|\r\n", testCaseId);
    }

    glbTestCounter++;
    GT_1trace(BspCaptUtTrace, GT_INFO,
              " |TEST INFO|:: %s ::\r\n", testcaseInfo);
    GT_1trace(BspCaptUtTrace, GT_INFO,
              " |TEST END|:: %d ::\r\n", testCaseId);

    return;
}

void st_printTestResult(UInt32 skipCount, UInt32 disableCount)
{
    GT_0trace(BspCaptUtTrace, GT_INFO,
              "\r\n *********Test Case Statistics*****************");
    GT_1trace(BspCaptUtTrace, GT_INFO,
              "\r\n      Total Test Case         : %d",
              (glbTestCounter + skipCount + disableCount));
    GT_1trace(BspCaptUtTrace, GT_INFO,
              "\r\n      Total Test Case Executed: %d", glbTestCounter);
    GT_1trace(BspCaptUtTrace, GT_INFO,
              "\r\n      Total Test Case Passed  : %d", glbPassCounter);
    GT_1trace(BspCaptUtTrace, GT_INFO,
              "\r\n      Total Test Case Failed  : %d", glbFailCounter);
    GT_1trace(BspCaptUtTrace, GT_INFO,
              "\r\n      Total Test Case Skipped : %d", skipCount);
    GT_1trace(BspCaptUtTrace, GT_INFO,
              "\r\n      Total Test Case Disabled: %d", disableCount);
    GT_0trace(BspCaptUtTrace, GT_INFO,
              "\r\n *********************************************\r\n \r\n");

    return;
}

void st_resetTestResult(void)
{
    glbTestCounter = 0;
    glbPassCounter = 0;
    glbFailCounter = 0;

    return;
}

/**
 *  st_captCheckHeapStat
 */
Int32 st_captCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                           UInt32                        traceMask)
{
    Int32 retVal = BSP_SOK;
    BspUtils_MemHeapStatus curStat;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL != heapStat));

    BspUtils_memGetHeapStat(&curStat);

    if (heapStat->freeSysHeapSize != curStat.freeSysHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  "%s: Warning: Memory leak (%d bytes) in System Heap!!\r\n",
                  UT_NAME,
                  (heapStat->freeSysHeapSize - curStat.freeSysHeapSize));
        retVal = BSP_EFAIL;
    }
    if (heapStat->freeBufHeapSize != curStat.freeBufHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  "%s: Warning: Memory leak (%d bytes) in Buffer Heap!!\r\n",
                  UT_NAME,
                  (heapStat->freeBufHeapSize - curStat.freeBufHeapSize));
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

void st_captPrintStatistics(st_CaptApp_Obj *appObj,
                            UInt32          execTimeInMsecs)
{
    UInt32 instCnt;
    st_CaptApp_InstObj *instObj;

    GT_0trace(BspCaptUtTrace, GT_INFO, " \r\n");
    GT_0trace(BspCaptUtTrace, GT_INFO, " Execution Statistics \r\n");
    GT_0trace(BspCaptUtTrace, GT_INFO, " ==================== \r\n");
    GT_0trace(BspCaptUtTrace, GT_INFO, " \r\n");
    GT_2trace(BspCaptUtTrace, GT_INFO,
              " Execution time    : %d.%d s \r\n",
              (execTimeInMsecs / 1000), (execTimeInMsecs % 1000));
    GT_2trace(BspCaptUtTrace, GT_INFO,
              " Total field Count : %d (%d fields/sec) \r\n",
              appObj->totalFldCount,
              (appObj->totalFldCount * 1000) / execTimeInMsecs);
    GT_1trace(BspCaptUtTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              appObj->totalCpuLoad / appObj->cpuLoadCount);
    GT_0trace(BspCaptUtTrace, GT_INFO, " \r\n");

    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Print the driver status */
        BspUtils_appPrintCaptStatus(
            instObj->drvHandle,
            instObj->instId,
            instObj->createPrms.numStream,
            instObj->createPrms.numCh,
            execTimeInMsecs);
    }

    GT_0trace(BspCaptUtTrace, GT_INFO, " \r\n");

    return;
}

