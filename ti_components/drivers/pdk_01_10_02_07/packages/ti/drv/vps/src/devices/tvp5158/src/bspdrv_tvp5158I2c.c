/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bspdrv_tvp5158I2c.c
 *
 *  \brief TVP5158 video decoder FVID2 driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <tvp5158/src/bspdrv_tvp5158Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_tvp5158SelectWrite(Bsp_Tvp5158HandleObj *pObj,
                                    UInt32                devId,
                                    UInt32                coreId);
static Int32 Bsp_tvp5158VbusWrite(Bsp_Tvp5158HandleObj *pObj,
                                  UInt32                devId,
                                  UInt32                vbusAddr,
                                  UInt8                 val,
                                  UInt32                len);
static Int32 Bsp_tvp5158VbusRead(Bsp_Tvp5158HandleObj *pObj,
                                 UInt32                devId,
                                 UInt32                vbusAddr,
                                 UInt8                *val);

static Int32 Bsp_tvp5158PatchDownload(Bsp_Tvp5158HandleObj *pObj, UInt32 devId);
static Int32 Bsp_tvp5158OutputEnable(Bsp_Tvp5158HandleObj *pObj, UInt32 enable);

#ifdef BSP_TVP5158_ENABLE_NF
static Int32 Bsp_tvp5158NfEnableAll(Bsp_Tvp5158HandleObj *pObj, Bool enable);
#endif

#ifdef BSP_TVP5158_ENABLE_FIRMWARE_PATCHES
static Int32 Bsp_tvp5158OfmReset(Bsp_Tvp5158HandleObj *pObj);
static Int32 Bsp_tvp5158SetExtendedSettings(Bsp_Tvp5158HandleObj *pObj);
static Int32 Bsp_tvp5158SetIndirectRegisters(Bsp_Tvp5158HandleObj *pObj);
#endif

static Int32 Bsp_tvp5158SetAudioVolume(Bsp_Tvp5158HandleObj *pObj,
                                       UInt32                coreId,
                                       UInt32                audioVolume);

static Int32 Bsp_tvp5158PrintChipId(Bsp_Tvp5158HandleObj *pObj);

#if 0
static Int32 Bsp_tvp5158CheckVideoSettings(UInt32 interleaveMode,
                                           UInt32 chMuxNum,
                                           UInt32 vidResSel,
                                           UInt32 outputType);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* reset TVP5158 OFM logic  */
Int32 Bsp_tvp5158Reset(Bsp_Tvp5158HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 devCnt, deviceID;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /*
     * calling reset for every device connected to the port starting
     * from cascade device
     */
    pCreatePrms = &pObj->createPrms;
    for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
    {
        deviceID = (pCreatePrms->numDevicesAtPort - (UInt32) 1) - devCnt;
        retVal   = Bsp_tvp5158PatchDownload(pObj, deviceID);
        if(retVal != FVID2_SOK)
        {
            GT_1trace(BspDeviceTrace, GT_ERR,
                      "Patch download failed for device %d\r\n", deviceID);
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief Get TP5158 chip ID, revision ID and firmware patch ID.
 */
Int32 Bsp_tvp5158GetChipId(Bsp_Tvp5158HandleObj         *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pStatus) ||
       (NULL == pPrm) ||
       (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, 0, sizeof(*pStatus));

        pCreatePrms = &pObj->createPrms;
        numRegs     = 0;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_CHIP_ID_MSB;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_CHIP_ID_LSB;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_ROM_VERSION;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_RAM_VERSION_0;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_RAM_VERSION_1;
        regValue[numRegs] = 0;
        numRegs++;

        retVal = Bsp_deviceRead8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        pStatus->chipId          = ((UInt32) regValue[0] << 8) | regValue[1];
        pStatus->chipRevision    = regValue[2];
        pStatus->firmwareVersion = ((UInt32) regValue[3] << 8) | (regValue[4]);
    }

    return (retVal);
}

/**
 *  \brief Set TVP5158 mode based on input parameters.
 *
 *  - mux mode - line or pixel or no-mux
 *  - number of channels
 *  - resolution
 *  - 8/16-bit data width
 *  - NTSC/PAL standard
 *  - cascade mode of operation
 */
Int32 Bsp_tvp5158SetVideoMode(Bsp_Tvp5158HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt32 devCnt, deviceID;
    UInt8  regAddr[9];
    UInt8  regValue[9];
    UInt32 numRegs;
    UInt32 interleaveMode, chMuxNum, vidResSel, outputType;
    UInt32 cascadeEnable, chIdEnable, vdetEnable, videoCropEnable;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;

        #ifdef BSP_TVP5158_ENABLE_FIRMWARE_PATCHES
        retVal = Bsp_tvp5158Reset(pObj);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Reset failed\r\n");
        }
        #endif

        #ifdef BSP_TVP5158_ENABLE_NF
        if(FVID2_SOK == retVal)
        {
            retVal = Bsp_tvp5158NfEnableAll(pObj, TRUE);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "NF enable all failed\r\n");
            }
        }
        #endif
        if(FVID2_SOK == retVal)
        {
            BspUtils_memcpy(&pObj->modePrms, pPrm, sizeof(*pPrm));
        }
    }

    if(FVID2_SOK == retVal)
    {
        /*
         * for each TVP5158 device starting from cascade slave device do ...
         */
        for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
        {
            deviceID = (pCreatePrms->numDevicesAtPort - (UInt32) 1) - devCnt;
            /* Set default settings */
            chIdEnable    = (UInt32) FALSE;
            vdetEnable    = (UInt32) FALSE;
            cascadeEnable = (UInt32) FALSE;

            if(TRUE == pPrm->videoCropEnable)
            {
                videoCropEnable = (UInt32) TRUE;
            }
            else
            {
                videoCropEnable = (UInt32) FALSE;
            }

            interleaveMode = BSP_TVP5158_LINE_INTERLEAVED_MODE;
            chMuxNum       = BSP_TVP5158_4CH_MUX;
            vidResSel      = BSP_TVP5158_RES_D1;
            outputType     = BSP_TVP5158_OUT_TYPE_8BIT;

            /* select mux mode, vdet mode based on 'videoIfMode' */
            switch(pPrm->videoIfMode)
            {
                case FVID2_VIFM_SCH_ES:
                    interleaveMode = BSP_TVP5158_NON_INTERLEAVED_MODE;
                    vdetEnable     = (UInt32) TRUE;
                    break;

                case FVID2_VIFM_MCH_PIXEL_MUX_ES:
                    interleaveMode = BSP_TVP5158_PIXEL_INTERLEAVED_MODE;
                    chIdEnable     = (UInt32) TRUE;
                    vdetEnable     = (UInt32) TRUE;
                    break;

                case FVID2_VIFM_MCH_LINE_MUX_ES:
                    interleaveMode = BSP_TVP5158_LINE_INTERLEAVED_MODE;
                    break;

                case FVID2_VIFM_MCH_LINE_MUX_SPLIT_LINE_ES:
                    interleaveMode = BSP_TVP5158_LINE_INTERLEAVED_HYBRID_MODE;
                    break;

                default:
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid IF mode\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
            }

            /*
             * set number of channels to mux and video resolution based on
             * 'standard'
             */
            switch(pPrm->standard)
            {
                case FVID2_STD_MUX_2CH_D1:
                    chMuxNum  = BSP_TVP5158_2CH_MUX;
                    vidResSel = BSP_TVP5158_RES_D1;
                    break;

                case FVID2_STD_MUX_4CH_D1:
                    chMuxNum  = BSP_TVP5158_4CH_MUX;
                    vidResSel = BSP_TVP5158_RES_D1;
                    break;

                case FVID2_STD_MUX_4CH_CIF:
                    chMuxNum  = BSP_TVP5158_4CH_MUX;
                    vidResSel = BSP_TVP5158_RES_CIF;
                    break;

                case FVID2_STD_MUX_4CH_HALF_D1:
                    chMuxNum  = BSP_TVP5158_4CH_MUX;
                    vidResSel = BSP_TVP5158_RES_HALF_D1;
                    break;

                case FVID2_STD_MUX_8CH_CIF:
                    chMuxNum  = BSP_TVP5158_8CH_MUX;
                    vidResSel = BSP_TVP5158_RES_CIF;
                    /* if cascade device set cascade mode to TRUE */
                    if(deviceID > 0)
                    {
                        cascadeEnable = (UInt32) TRUE;
                    }
                    break;

                case FVID2_STD_MUX_8CH_HALF_D1:
                    chMuxNum  = BSP_TVP5158_8CH_MUX;
                    vidResSel = BSP_TVP5158_RES_HALF_D1;
                    /* if cascade device set cascade mode to TRUE */
                    if(deviceID > 0)
                    {
                        cascadeEnable = (UInt32) TRUE;
                    }
                    break;

                case FVID2_STD_CIF:
                    chMuxNum  = BSP_TVP5158_1CH_MUX;
                    vidResSel = BSP_TVP5158_RES_CIF;
                    break;

                case FVID2_STD_HALF_D1:
                    chMuxNum  = BSP_TVP5158_1CH_MUX;
                    vidResSel = BSP_TVP5158_RES_HALF_D1;
                    break;

                case FVID2_STD_D1:
                    chMuxNum  = BSP_TVP5158_1CH_MUX;
                    vidResSel = BSP_TVP5158_RES_D1;
                    break;

                default:
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid standard\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
            }

            /* set 8/16-bit mode */
            switch(pPrm->videoIfWidth)
            {
                case FVID2_VIFW_8BIT:
                    outputType = BSP_TVP5158_OUT_TYPE_8BIT;
                    break;

                case FVID2_VIFW_16BIT:
                    outputType = BSP_TVP5158_OUT_TYPE_16BIT;
                    break;

                default:
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid IF width\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
            }

            if(retVal == FVID2_SOK)
            {
                /*
                 * validate if setup combination's are valid
                 */
                #if 0
                /* cascade ON but number of device < 2 */
                if(cascadeEnable && pCreatePrms->numDevicesAtPort == 1)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR,
                              "Can't have one device in cascade mode\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
                }

                /* only YUV422 can be the video format */
                if(pPrm->videoDataFormat != FVID2_DF_YUV422P)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid data format\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
                }

                /* check video setup combinations are valid or not */
                retVal = Bsp_tvp5158CheckVideoSettings(
                    interleaveMode,
                    chMuxNum,
                    vidResSel,
                    outputType);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR,
                              "Invalid video settings\r\n");
                    break;
                }
                #endif

                /* fill the register addr/value pairs */
                numRegs = 0;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_AVD_OUT_CTRL_1;
                regValue[numRegs] =
                    (UInt8) ((interleaveMode << 6) |
                            (chMuxNum << 4) |
                            (outputType << 3) |
                            (cascadeEnable << 2) |
                            (vidResSel << 0));
                numRegs++;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_AVD_OUT_CTRL_2;
                regValue[numRegs] =
                    (UInt8) (((videoCropEnable & 0x1U) << 6) |
                            ((UInt32) 1 << 4) | /* 1: dithering enable */
                            (chIdEnable << 2) |
                            (chIdEnable << 1) |
                            (vdetEnable << 0));
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_OFM_MODE_CTRL;
                /* 1: OSC out enabled  */
                regValue[numRegs] = (UInt8) ((UInt32) 1 << 5);
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_AUTO_SW_MASK;
                /* No mask for autoswitch  */
                regValue[numRegs] = 0xFFU;
                numRegs++;

                /* select decoder cores to which the selectings should apply */
                retVal = Bsp_tvp5158SelectWrite(pObj, deviceID,
                                                BSP_TVP5158_CORE_ALL);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
                }
            }
            if(retVal == FVID2_SOK)
            {
                /* apply the settings */
                retVal = Bsp_deviceWrite8(
                    pCreatePrms->deviceI2cInstId,
                    pCreatePrms->deviceI2cAddr[deviceID],
                    &regAddr[0],
                    &regValue[0],
                    numRegs);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
                }
            }
            if(retVal != FVID2_SOK)
            {
                break;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        #ifdef BSP_TVP5158_ENABLE_FIRMWARE_PATCHES
        UInt32 delay;
        Bsp_tvp5158SetExtendedSettings(pObj);
        delay = 20U;
        BspOsal_sleep(delay);
        Bsp_tvp5158OfmReset(pObj);
        #endif
    }

    return (retVal);
}

/**
 *  \brief Gets the video status of the detected video.
 *
 *  Can be called for each channel
 */
Int32 Bsp_tvp5158GetVideoStatus(Bsp_Tvp5158HandleObj              *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    UInt32 devId, chId, std, regVal;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pStatus) || (NULL == pPrm))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, 0, sizeof(*pStatus));
        pCreatePrms = &pObj->createPrms;

        /* Identify channel/core number and device number from channelNum */
        devId = pPrm->channelNum / BSP_TVP5158_CH_PER_DEVICE_MAX;
        chId  = pPrm->channelNum % BSP_TVP5158_CH_PER_DEVICE_MAX;

        /* There can be at max 2 TVP5158 devices per port */
        if(devId >= BSP_TVP5158_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device ID\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        numRegs = 0;

        /* select appropiate core */
        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_DEC_RD_EN;
        regVal            =  (UInt32) 1U << chId;
        regValue[numRegs] = (UInt8) (regVal);
        numRegs++;

        retVal = Bsp_deviceWrite8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[devId],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* read retVal */
        numRegs = 0;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_STATUS_1;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_STATUS_2;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_VID_STD_STATUS;
        regValue[numRegs] = 0;
        numRegs++;

        retVal = Bsp_deviceRead8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[devId],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        if((((UInt32) regValue[0] & BSP_TVP5158_HSYNC_LOCKED) != 0U) &&
           (((UInt32) regValue[0] & BSP_TVP5158_VSYNC_LOCKED) != 0U) &&
           (((UInt32) regValue[1] & BSP_TVP5158_SIGNAL_DETECT) != 0U))
        {
            pStatus->isVideoDetect = (UInt32) TRUE;
        }

        if(pStatus->isVideoDetect)
        {
            /* since input to TVP5158 is always interlaced */
            pStatus->isInterlaced = (UInt32) TRUE;

            /* 60Hz, i.e 16.667msec per field */
            pStatus->frameInterval = 16667U;
            /* is 50Hz or 60Hz ? */
            if((regValue[0] & BSP_TVP5158_SIGNAL_60HZ))
            {
                /* 50Hz, i.e 20msec per field */
                pStatus->frameInterval = 20000U;
            }

            /* frame width is always 720 pixels */
            pStatus->frameWidth  = BSP_TVP5158_NTSC_PAL_WIDTH;
            pStatus->frameHeight = 0;

            /* video standard */
            std = ((UInt32) regValue[2] & BSP_TVP5158_VID_STD_MASK);
            if((std == BSP_TVP5158_VID_STD_PAL_BDGHIN) ||
               (std == BSP_TVP5158_VID_STD_PAL_M) ||
               (std == BSP_TVP5158_VID_STD_PAL_COMB_N) ||
               (std == BSP_TVP5158_VID_STD_PAL_60))
            {
                /* PAL standard */
                pStatus->frameHeight = BSP_TVP5158_PAL_HEIGHT;
            }
            if((std == BSP_TVP5158_VID_STD_NTSC_MJ) ||      /* NTSC (M,J) */
               (std == BSP_TVP5158_VID_STD_NTSC_4_43))      /* NTSC 4.43 */
            {
                /* NTSC standard */
                pStatus->frameHeight = BSP_TVP5158_NTSC_HEIGHT;
            }
        }
    }

    return (retVal);
}

/**
 *  \brief Starts TVP5158.
 */
Int32 Bsp_tvp5158Start(Bsp_Tvp5158HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    retVal = Bsp_tvp5158OutputEnable(pObj, (UInt32) TRUE);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output enable failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief Stops TVP5158.
 */
Int32 Bsp_tvp5158Stop(Bsp_Tvp5158HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    retVal = Bsp_tvp5158OutputEnable(pObj, (UInt32) FALSE);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output disable failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_tvp5158RegWrite(Bsp_Tvp5158HandleObj          *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pPrm) ||
       (NULL == pPrm->regAddr) ||
       (NULL == pPrm->regValue8) ||
       (0U == pPrm->numRegs) ||
       (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;
        retVal      = Bsp_deviceWrite8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            pPrm->regAddr,
            pPrm->regValue8,
            pPrm->numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_tvp5158RegRead(Bsp_Tvp5158HandleObj    *pObj,
                         Bsp_VidDecRegRdWrParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pPrm) ||
       (NULL == pPrm->regAddr) ||
       (NULL == pPrm->regValue8) ||
       (0U == pPrm->numRegs) ||
       (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;
        retVal      = Bsp_deviceRead8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            pPrm->regAddr,
            pPrm->regValue8,
            pPrm->numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
        }
    }

    return (retVal);
}

/*
 * \brief Set video color related parameters.
 */
Int32 Bsp_tvp5158SetVideoColor(Bsp_Tvp5158HandleObj        *pObj,
                               const Bsp_VidDecColorParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    UInt32 devId, chId;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;

        devId = pPrm->channelNum / BSP_TVP5158_CH_PER_DEVICE_MAX;
        chId  = pPrm->channelNum % BSP_TVP5158_CH_PER_DEVICE_MAX;
        chId  = (UInt32) 1 << chId;

        /* There can be at max 2 TVP5158 devices per port */
        if(devId >= BSP_TVP5158_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device ID\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        numRegs = 0;

        /* set core ID */
        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_DEC_WR_EN;
        regValue[numRegs] = (UInt8) (chId);
        numRegs++;

        /* set video processing parameters */
        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_Y_BRIGHTNESS;
        if(pPrm->videoBrightness == BSP_VID_DEC_DEFAULT)
        {
            regValue[numRegs] = 128U;
            numRegs++;
        }
        else if(pPrm->videoBrightness == BSP_VID_DEC_NO_CHANGE)
        {
            /* No change */
        }
        else
        {
            regValue[numRegs] = pPrm->videoBrightness;
            numRegs++;
        }

        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_Y_CONTRAST;
        if(pPrm->videoContrast == BSP_VID_DEC_DEFAULT)
        {
            regValue[numRegs] = 128U;
            numRegs++;
        }
        else if(pPrm->videoContrast == BSP_VID_DEC_NO_CHANGE)
        {
            /* No change */
        }
        else
        {
            regValue[numRegs] = pPrm->videoContrast;
            numRegs++;
        }

        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_C_SATURATION;
        if(pPrm->videoSaturation == BSP_VID_DEC_DEFAULT)
        {
            regValue[numRegs] = 128U;
            numRegs++;
        }
        else if(pPrm->videoSaturation == BSP_VID_DEC_NO_CHANGE)
        {
            /* No change */
        }
        else
        {
            regValue[numRegs] = pPrm->videoSaturation;
            numRegs++;
        }

        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_C_HUE;
        if(pPrm->videoHue == BSP_VID_DEC_DEFAULT)
        {
            regValue[numRegs] = 128U;
            numRegs++;
        }
        else if(pPrm->videoHue == BSP_VID_DEC_NO_CHANGE)
        {
            /* No change */
        }
        else
        {
            regValue[numRegs] = pPrm->videoHue;
            numRegs++;
        }

        /* write to TVP5158 */
        retVal = Bsp_deviceWrite8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[devId],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Set video noise filter related parameters.
 */
Int32 Bsp_tvp5158SetVideoNf(Bsp_Tvp5158HandleObj           *pObj,
                            const Bsp_Tvp5158VideoNfParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    UInt32 devId, chId, regVal, blkWidthUV;
    Bsp_VidDecCreateParams *pCreatePrms;
    Bool   flag;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;

        devId = pPrm->channelNum / BSP_TVP5158_CH_PER_DEVICE_MAX;
        chId  = pPrm->channelNum % BSP_TVP5158_CH_PER_DEVICE_MAX;
        chId  = (UInt32) 1 << chId;

        /* There can be at max 2 TVP5158 devices per port */
        if(devId >= BSP_TVP5158_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device ID\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        numRegs = 0;

        /* set core ID */
        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_DEC_WR_EN;
        regValue[numRegs] = (UInt8) (chId);
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_NR_MAX_NOISE;
        regValue[numRegs] = pPrm->maxNoise;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_NR_CTRL;

        flag       = (Bool) (!(Bool) (pPrm->nfEnable));
        blkWidthUV = 1U;
        /* Block width UV, 0: 128pixels, 1: 256pixels
         * Block width  Y, 0: 256pixels, 1: 512pixels
         */
        regVal =
            ((((UInt32) flag & 0x1U) << 0) |
             (((UInt32) (pPrm->colorKillerEnable & 0x1U)) << (UInt32) 4U) |
             (blkWidthUV << 3U) |
             ((UInt32)0 << 2U));

        regValue[numRegs] = (UInt8) (regVal);
        numRegs++;

        /* write to TVP5158 */
        retVal = Bsp_deviceWrite8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[devId],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Set audio related parameters.
 */
Int32 Bsp_tvp5158SetAudioMode(Bsp_Tvp5158HandleObj             *pObj,
                              const Bsp_Tvp5158AudioModeParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    UInt32 devId, regVal;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;
        devId       = pPrm->deviceNum;

        /* There can be at max 2 TVP5158 devices per port */
        if(devId >= pCreatePrms->numDevicesAtPort)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device ID\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* select all core's */
        retVal = Bsp_tvp5158SelectWrite(pObj, devId,
                                        BSP_TVP5158_CORE_ALL);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        numRegs = 0;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_AUDIO_SAMPLE_HZ;
        regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_16KHZ;
        if(pPrm->samplingHz == 8000)
        {
            regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_8KHZ;
        }
        if(pPrm->samplingHz == 16000)
        {
            regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_16KHZ;
        }
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_AUDIO_MIXER;
        switch(pPrm->tdmChannelNum)
        {
            case 0:
                regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_TDM_2CH;
                break;
            case 1:
                regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_TDM_4CH;
                break;
            case 2:
                regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_TDM_8CH;
                break;
            case 3:
                regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_TDM_12CH;
                break;
            case 4:
                regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_TDM_16CH;
                break;
            default:
                /* Default to 4 channel mode */
                regValue[numRegs] = (UInt8) BSP_TVP5158_AUDIO_TDM_4CH;
                break;
        }
        numRegs++;

        regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_AUDIO_CASCADE;
        regValue[numRegs] = (UInt8) (pPrm->cascadeStage & 0x03U);
        numRegs++;

        /* Added check for tdmChannelNum also, along with cascade stage */
        regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_AUDIO_CTRL;
        if((pPrm->cascadeStage > 0) ||
           (pPrm->tdmChannelNum > BSP_TVP5158_AUDIO_TDM_4CH))
        {
            regVal = (UInt32)  ((UInt32) 0U
                                /* 0: SD_M disable, 1: SD_M enable */
                                | ((UInt32) 0U << 7U)
                                /* 0: SD_R disable, 1: SD_R enable */
                                | (BSP_TVP5158_AUDIO_CTRL_SD_R_ENABLE << 6U)
                                /* 0: Slave mode, 1: Master mode */
                                | ((UInt32) (pPrm->masterModeEnable &
                                             0x1U) << 5U)
                                /* 0: I2S mode, 1: DSP mode */
                                | ((UInt32) (pPrm->dspModeEnable & 0x1U) << 4U)
                                /* 0: 256fs, 1: 64fs */
                                | ((UInt32) 0U << 3U)
                                /* 0: 16-bit PCM, 1: 8-bit ulaw, 2:8-bit Alaw */
                                | ((UInt32) (pPrm->ulawEnable & 0x1U) << 2U)
                                /* 0: SD_R only, 1: SD_R + SD_M */
                                | ((UInt32) 0U << 0U));
            regValue[numRegs] = (UInt8) regVal;
        }
        else
        {
            regVal = (UInt32)  ((UInt32) 0U
                                /* 0: SD_M disable, 1: SD_M enable */
                                | ((UInt32) 0U << 7U)
                                /* 0: SD_R disable, 1: SD_R enable */
                                | (BSP_TVP5158_AUDIO_CTRL_SD_R_ENABLE << 6U)
                                /* 0: Slave mode, 1: Master mode */
                                | ((UInt32) (pPrm->masterModeEnable &
                                             0x1U) << 5U)
                                /* 0: I2S mode, 1: DSP mode */
                                | ((UInt32) (pPrm->dspModeEnable & 0x1U) << 4U)
                                /* 0: 256fs, 1: 64fs */
                                | (BSP_TVP5158_AUDIO_CTRL_64_FS << 3U)
                                /* 0: 16-bit PCM, 1: 8-bit ulaw, 2:8-bit Alaw */
                                | ((UInt32) (pPrm->ulawEnable & 0x1U) << 2U)
                                /* 0: SD_R only, 1: SD_R + SD_M */
                                | ((UInt32) 0U << 0U));
            regValue[numRegs] = (UInt8) regVal;
        }
        numRegs++;

        /* write to TVP5158 */
        retVal = Bsp_deviceWrite8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[devId],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_tvp5158SetAudioVolume(
            pObj,
            BSP_TVP5158_CORE_ALL,
            pPrm->audioVolume);
    }

    return (retVal);
}

#ifdef BSP_TVP5158_ENABLE_FIRMWARE_PATCHES
/**
 *  \brief Soft-reset of TVP5158
 */
static Int32 Bsp_tvp5158OfmReset(Bsp_Tvp5158HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    Int32  devCnt, deviceID;
    UInt32 delay;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
    {
        deviceID = ((Int32) pCreatePrms->numDevicesAtPort - (Int32) 1) - devCnt;
        /* select all TVP5158 cores */
        retVal = Bsp_tvp5158SelectWrite(pObj, (UInt32) deviceID,
                                        BSP_TVP5158_CORE_ALL);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
        }
        else
        {
            /* do OFM reset */
            numRegs = 0;

            regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_MISC_OFM_CTRL;
            regValue[numRegs] = 0x01U;
            numRegs++;

            retVal = Bsp_deviceWrite8(
                pCreatePrms->deviceI2cInstId,
                pCreatePrms->deviceI2cAddr[deviceID],
                &regAddr[0],
                &regValue[0],
                numRegs);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
            }
        }
        if(retVal != FVID2_SOK)
        {
            break;
        }
        else
        {
            delay = 20U;
            /* wait for reset to be effective */
            BspOsal_sleep(delay);
        }
    }

    return (retVal);
}
#endif

/**
 *  \brief Select TVP5158 core.
 *
 *  devId - device for which to apply this
 *  value - 0x1: Core0, 0x2: Core1, 0x4: Core2, 0x8: Core3,
 *          BSP_TVP5158_CORE_ALL: All Core's
 */
static Int32 Bsp_tvp5158SelectWrite(Bsp_Tvp5158HandleObj *pObj,
                                    UInt32                devId,
                                    UInt32                coreId)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    numRegs     = 0;

    regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_DEC_WR_EN;
    regValue[numRegs] = (UInt8) (coreId);
    numRegs++;

    retVal = Bsp_deviceWrite8(
        pCreatePrms->deviceI2cInstId,
        pCreatePrms->deviceI2cAddr[devId],
        &regAddr[0],
        &regValue[0],
        numRegs);
    if(retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief Write to VBUS
 */
static Int32 Bsp_tvp5158VbusWrite(Bsp_Tvp5158HandleObj *pObj,
                                  UInt32                devId,
                                  UInt32                vbusAddr,
                                  UInt8                 val,
                                  UInt32                len)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt32 regVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    numRegs     = 0;

    /* set VBUS address */
    regAddr[numRegs]  = 0xE8U;
    regVal            = ((vbusAddr >> 0) & 0xFFU);
    regValue[numRegs] = (UInt8) (regVal);
    numRegs++;

    regAddr[numRegs]  = 0xE9U;
    regVal            = ((vbusAddr >> 8) & 0xFFU);
    regValue[numRegs] = (UInt8) (regVal);
    numRegs++;

    regAddr[numRegs]  = 0xEAU;
    regVal            = ((vbusAddr >> 16) & 0xFFU);
    regValue[numRegs] = (UInt8) (regVal);
    numRegs++;

    if(len > 0U)
    {
        /* set VBUS address value, if required */
        regAddr[numRegs]  = 0xE0U;
        regValue[numRegs] = val;
        numRegs++;
    }

    retVal = Bsp_deviceWrite8(
        pCreatePrms->deviceI2cInstId,
        pCreatePrms->deviceI2cAddr[devId],
        &regAddr[0],
        &regValue[0],
        numRegs);
    if(retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief Read from TVP5158 VBUS
 */
static Int32 Bsp_tvp5158VbusRead(Bsp_Tvp5158HandleObj *pObj,
                                 UInt32                devId,
                                 UInt32                vbusAddr,
                                 UInt8                *val)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;

    /* set VBUS address */
    retVal = Bsp_tvp5158VbusWrite(pObj, devId, vbusAddr, 0, 0);
    if(retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Vbus write failed\r\n");
    }

    if(FVID2_SOK == retVal)
    {
        /* read VBUS address value */
        numRegs = 0;

        regAddr[numRegs]  = 0xE0U;
        regValue[numRegs] = 0;
        numRegs++;

        retVal = Bsp_deviceRead8(
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[devId],
            &regAddr[0],
            &regValue[0],
            numRegs);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        *val = regValue[0];
    }

    return (retVal);
}

/**
 *  \brief Download patch to TVP5158.
 */
static Int32 Bsp_tvp5158PatchDownload(Bsp_Tvp5158HandleObj *pObj, UInt32 devId)
{
    Int32        retVal = FVID2_SOK;
    UInt8        vbusStatus;
    UInt32       wrSize, len, delay, vbusStat;
    const UInt8 *patchAddr;
    UInt32       patchSize, skipLoad = FALSE;
    static UInt8 patchData[256];
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;

    patchAddr = gBspTvp5158Patch;
    patchSize = sizeof(gBspTvp5158Patch);

    /* select all TVP5158 core's */
    retVal = Bsp_tvp5158SelectWrite(pObj, devId, BSP_TVP5158_CORE_ALL);
    if(retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_tvp5158VbusRead(pObj, devId, 0xB00060U, &vbusStatus);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Vbus read failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* if no patch download then return from here */
#ifdef BSP_TVP5158_NO_PATCH_DOWNLOAD
        {
            #ifdef BSP_TVP5158_DEBUG
            GT_1trace(
                BspDeviceTrace, GT_INFO,
                " TVP5158: 0x%02x: NO Patch downloaded, using ROM firmware.\r\n",
                pCreatePrms->deviceI2cAddr[devId]);
            Bsp_tvp5158PrintChipId(pObj);
            #endif
            skipLoad = (UInt32)TRUE;
        }
#endif

        /* if force patch download then then skip checking of patch
         * load retVal */
#ifndef BSP_TVP5158_FORCE_PATCH_DOWNLOAD
        if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
        {
            if((UInt32) vbusStatus & 0x2U)
            {
                #ifdef BSP_TVP5158_DEBUG
                GT_1trace(BspDeviceTrace, GT_INFO,
                          " TVP5158: 0x%02x: Patch is already running.\r\n",
                          pCreatePrms->deviceI2cAddr[devId]);
                Bsp_tvp5158PrintChipId(pObj);
                #endif
                skipLoad = (UInt32)TRUE;    /* patch already running */
            }
        }
#endif
        if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
        {
#ifdef BSP_TVP5158_DEBUG
            GT_1trace(BspDeviceTrace, GT_INFO,
                      " TVP5158: 0x%02x: Downloading patch ... \r\n",
                      pCreatePrms->deviceI2cAddr[devId]);
#endif

            /* select all TVP5158 core's */
            retVal = Bsp_tvp5158SelectWrite(pObj, devId,
                                            BSP_TVP5158_CORE_ALL);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
            }
        }
    }

    if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
    {
        /* keep firmware in reset state */
        vbusStat   = (UInt32) vbusStatus | 0x1U;
        vbusStatus = (UInt8) vbusStat;
        len        = 1U;
        retVal     = Bsp_tvp5158VbusWrite(pObj, devId, 0xB00060U, vbusStatus,
                                          len);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Vbus write failed\r\n");
        }
    }

    if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
    {
        /* download patch */
        retVal = Bsp_tvp5158VbusWrite(pObj, devId, 0x400000U, 0, 0);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Vbus write failed\r\n");
        }
    }

    if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
    {
        BspUtils_memset(patchData, (UInt8) 0xE1, sizeof(patchData));
        while(patchSize)
        {
            if(patchSize < sizeof(patchData))
            {
                wrSize = patchSize;
            }
            else
            {
                wrSize = sizeof(patchData);
            }

            retVal = Bsp_deviceWrite8(
                pCreatePrms->deviceI2cInstId,
                pCreatePrms->deviceI2cAddr[devId],
                patchData,
                patchAddr,
                wrSize);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
                break;
            }

            patchAddr += wrSize;
            patchSize -= wrSize;
        }
    }

    if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
    {
        /* keep in reset and apply patch */
        vbusStat   = (UInt32) vbusStatus | 0x3U;
        vbusStatus = (UInt8) vbusStat;
        len        = 1U;
        retVal     = Bsp_tvp5158VbusWrite(pObj, devId, 0xB00060U, vbusStatus,
                                          len);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Vbus write failed\r\n");
        }
    }

    if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
    {
        /* release from reset */
        vbusStat   = (UInt32) vbusStatus & ((UInt32) (~((UInt32) 0x1U)));
        vbusStatus = (UInt8) vbusStat;
        len        = 1U;
        retVal     = Bsp_tvp5158VbusWrite(pObj, devId, 0xB00060U, vbusStatus,
                                          len);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Vbus write failed\r\n");
        }
    }

    if((FVID2_SOK == retVal) && ((UInt32)FALSE == skipLoad))
    {
        delay = 300U;
        /* wait for patch to get applied */
        BspOsal_sleep(delay);

        #ifdef BSP_TVP5158_DEBUG
        GT_1trace(BspDeviceTrace, GT_INFO,
                  " TVP5158: 0x%02x: Downloading patch ... DONE !!!\r\n",
                  pCreatePrms->deviceI2cAddr[devId]);

        Bsp_tvp5158PrintChipId(pObj);
        #endif
    }

    return (retVal);
}

/**
 *  \brief Enable TVP5158 output port.
 */
static Int32 Bsp_tvp5158OutputEnable(Bsp_Tvp5158HandleObj *pObj, UInt32 enable)
{
    Int32  retVal = FVID2_SOK;
    UInt32 devCnt, deviceID;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;

    /* for all devices starting from cascade device do ... */
    for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
    {
        deviceID = (pCreatePrms->numDevicesAtPort - (UInt32) 1) - devCnt;
        /* select all TVP5158 cores */
        retVal = Bsp_tvp5158SelectWrite(pObj, deviceID,
                                        BSP_TVP5158_CORE_ALL);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
        }
        else
        {
            /* read register for output enable */
            numRegs           = 0;
            regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_OFM_MODE_CTRL;
            regValue[numRegs] = 0;
            numRegs++;

            retVal = Bsp_deviceRead8(
                pCreatePrms->deviceI2cInstId,
                pCreatePrms->deviceI2cAddr[deviceID],
                &regAddr[0],
                &regValue[0],
                numRegs);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
            }
        }
        if(retVal == FVID2_SOK)
        {
            /* set bit or reset bit to enable or disable output */
            if(enable)
            {
                regValue[0] |= (UInt8) BSP_TVP5158_OUT_ENABLE;
            }
            else
            {
                regValue[0] &= (UInt8) (~BSP_TVP5158_OUT_ENABLE);
            }

            /* write register */
            retVal = Bsp_deviceWrite8(
                pCreatePrms->deviceI2cInstId,
                pCreatePrms->deviceI2cAddr[deviceID],
                &regAddr[0],
                &regValue[0],
                numRegs);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
            }
        }
        if(retVal != FVID2_SOK)
        {
            break;
        }
    }

    return (retVal);
}

#ifdef BSP_TVP5158_ENABLE_NF
static Int32 Bsp_tvp5158NfEnableAll(Bsp_Tvp5158HandleObj *pObj, Bool enable)
{
    Int32 retVal = FVID2_SOK;
    Int32 devCnt, chId, deviceID;
    Bsp_Tvp5158VideoNfParams nfParams;
    Bsp_VidDecCreateParams  *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    deviceID    = 0;
    pCreatePrms = &pObj->createPrms;

    nfParams.nfEnable          = enable;
    nfParams.colorKillerEnable = enable;
    nfParams.maxNoise          = 0;

    /* for all devices starting from cascade device do ... */
    for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
    {
        deviceID = (pCreatePrms->numDevicesAtPort - (UInt32) 1) - devCnt;
        for(chId = 0U; chId < BSP_TVP5158_CH_PER_DEVICE_MAX; chId++)
        {
            nfParams.channelNum = chId;

            /* Max noise: 0..63 */
            if(chId == 0)
            {
                nfParams.maxNoise = 0;
            }
            if(chId == 1)
            {
                nfParams.maxNoise = 16;
            }
            if(chId == 2)
            {
                nfParams.maxNoise = 32;
            }
            if(chId == 3)
            {
                nfParams.maxNoise = 63;
            }

            retVal = Bsp_tvp5158SetVideoNf(pObj, &nfParams);
            if(retVal != FVID2_SOK)
            {
                break;
            }
        }

        if(retVal != FVID2_SOK)
        {
            break;
        }
    }

    return (retVal);
}

#endif

#ifdef BSP_TVP5158_ENABLE_FIRMWARE_PATCHES
static Int32 Bsp_tvp5158SetExtendedSettings(Bsp_Tvp5158HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    Int32  deviceID, devCnt;
    UInt8  regAddr[32];
    UInt8  regValue[32];
    UInt32 numRegs, regVal;
    UInt8  autoSwitchMode;
    Bsp_VidDecCreateParams    *pCreatePrms;
    Bsp_VidDecVideoModeParams *pVidModePrm;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    deviceID    = 0;
    pCreatePrms = &pObj->createPrms;
    pVidModePrm = &pObj->modePrms;

    /* 0: Auto switch mode, 1: force NTSC mode, 2: force PAL mode */
    autoSwitchMode = 0x00; /* default */
    if(pVidModePrm->videoSystem == BSP_VID_DEC_VIDEO_SYSTEM_NTSC)
    {
        autoSwitchMode = (UInt8) 0x01;
    }
    else if(pVidModePrm->videoSystem == BSP_VID_DEC_VIDEO_SYSTEM_PAL)
    {
        autoSwitchMode = (UInt8) 0x02;
    }
    else
    {
        /* Already auto switch is set */
    }

    if(retVal == FVID2_SOK)
    {
        #ifdef BSP_TVP5158_ENABLE_COMB_FILTER_SETUP
        Bsp_tvp5158SetIndirectRegisters(pObj);
        #endif

        /* for all devices starting from cascade device do ... */
        for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
        {
            deviceID =
                ((Int32) pCreatePrms->numDevicesAtPort - (Int32) 1) - devCnt;
            retVal = Bsp_tvp5158SelectWrite(pObj, 0, BSP_TVP5158_CORE_ALL);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
            }
            if(retVal == FVID2_SOK)
            {
                numRegs = 0;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_VID_STD_SELECT;
                regValue[numRegs] = (UInt8) (autoSwitchMode);
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_OP_MODE_CTRL;
                /* New V-Bit control algorithm (number of active lines per frame
                 * is constant as total LPF varies) */
                regValue[numRegs] = 0x08U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_FV_DEC_CTRL;
                /* Adaptive BOP/EOP control for TI816x enabled and F and V bits
                 * decoded from line count */
                regValue[numRegs] = 0x03U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_FV_CTRL;
                /* V-PLL fast-lock disabled and windowed VSYNC pipe disabled */
                regValue[numRegs] = 0x06U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_FBIT_DURATION;
                /* Maximum field duration set to 788 for NTSC and 938 for PAL */
                regValue[numRegs] = 0x60U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_ESYNC_OFFSET_1;
                /* Default V-bit position relative to F-bit Moving line position
                 * of Embedded F and V bit signals to offset from 656 standard
                 * to patch for DVD player offset issue */
                regValue[numRegs] = 0x02U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_ESYNC_OFFSET_2;
                /* Default V-bit position relative to F-bit */
                regValue[numRegs] = 0x00U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_MIN_F1_ACT;
                /* Minimum F1_to_active set to 8 lines */
                regValue[numRegs] = 0x08U;
                numRegs++;

                regAddr[numRegs] = (UInt8) BSP_TVP5158_REG_Y_CTRL_2;
                /*peaking Gain 0: default, 1: 0.5, 2:1, 3:2 */
                regValue[numRegs] = 0x01U;
                #ifdef BSP_TVP5158_ENABLE_COMB_FILTER_SETUP
                /*Apply Comb filter settings */
                regVal = (UInt32) regValue[numRegs] | 0x20U;
                regValue[numRegs] = (UInt8) regVal;
                #endif

                numRegs++;

                #if 0
                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_Y_BRIGHTNESS;
                regValue[numRegs] = 0x1cU;   /* decrease brightness */
                numRegs++;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_Y_CONTRAST;
                regValue[numRegs] = 0x89U;   /* increase contrast */
                numRegs++;
                #endif

                retVal = Bsp_deviceWrite8(
                    pCreatePrms->deviceI2cInstId,
                    pCreatePrms->deviceI2cAddr[deviceID],
                    &regAddr[0],
                    &regValue[0],
                    numRegs);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
                }
            }
            if(retVal == FVID2_SOK)
            {
                numRegs = 0;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_Y_CTRL_1;
                regValue[numRegs] = 0;
                numRegs++;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_Y_CTRL_2;
                regValue[numRegs] = 0;
                numRegs++;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_C_CTRL_1;
                regValue[numRegs] = 0;
                numRegs++;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_C_CTRL_2;
                regValue[numRegs] = 0;
                numRegs++;

                retVal = Bsp_deviceRead8(
                    pCreatePrms->deviceI2cInstId,
                    pCreatePrms->deviceI2cAddr[deviceID],
                    &regAddr[0],
                    &regValue[0],
                    numRegs);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
                }
            }
            if(retVal == FVID2_SOK)
            {
                #ifdef BSP_TVP5158_VERBOSE_DEBUG
                GT_2trace(BspDeviceTrace, GT_INFO,
                          " TVP5158: 0x%02x: Y Procesing Control 1 = 0x%02x\r\n",
                          pCreatePrms->deviceI2cAddr[deviceID], regValue[0]);
                GT_2trace(BspDeviceTrace, GT_INFO,
                          " TVP5158: 0x%02x: Y Procesing Control 2 = 0x%02x\r\n",
                          pCreatePrms->deviceI2cAddr[deviceID], regValue[1]);
                GT_2trace(BspDeviceTrace, GT_INFO,
                          " TVP5158: 0x%02x: C Procesing Control 1 = 0x%02x\r\n",
                          pCreatePrms->deviceI2cAddr[deviceID], regValue[2]);
                GT_2trace(BspDeviceTrace, GT_INFO,
                          " TVP5158: 0x%02x: C Procesing Control 2 = 0x%02x\r\n",
                          pCreatePrms->deviceI2cAddr[deviceID], regValue[3]);
                #endif
            }
            if(retVal != FVID2_SOK)
            {
                break;
            }
        }
    }
    return (retVal);
}

static Int32 Bsp_tvp5158SetIndirectRegisters(Bsp_Tvp5158HandleObj *pObj)
{
    Int32                   retVal = FVID2_SOK;
    UInt32                  devCnt, numRegs, i, len, vbusValue, deviceID;
    volatile UInt32         vbusAddr;
    volatile UInt8          vbusVal8;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;

    for(devCnt = 0; devCnt < pCreatePrms->numDevicesAtPort; devCnt++)
    {
        deviceID = (pCreatePrms->numDevicesAtPort - (UInt32) 1) - devCnt;
        retVal   = Bsp_tvp5158SelectWrite(pObj, deviceID,
                                          BSP_TVP5158_CORE_ALL);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
        }

        if(retVal == FVID2_SOK)
        {
            numRegs = (sizeof(gBspTvp5158VbusAddrValueSet) /
                       sizeof(gBspTvp5158VbusAddrValueSet[0])) / 2U;

            for(i = 0; i < numRegs; i++)
            {
                /* 24-bit Vbus Addr */
                vbusAddr = (gBspTvp5158VbusAddrValueSet[2U * i] & 0xFFFFFFU);
                if(vbusAddr == 0xFFFFFFU)
                {
                    retVal = FVID2_EFAIL;
                }
                if(retVal == FVID2_SOK)
                {
                    /* 8-bit Vbus value */
                    vbusValue =
                        (UInt32) ((gBspTvp5158VbusAddrValueSet[(2U * i) +
                                                               1U]) &
                                  ((0xFFU)));
                    vbusVal8 = (UInt8) vbusValue;

                    len = 1U;

                    retVal = Bsp_tvp5158VbusWrite(pObj,
                                                  deviceID,
                                                  vbusAddr,
                                                  vbusVal8,
                                                  len);
                    if(retVal != FVID2_SOK)
                    {
                        GT_0trace(BspDeviceTrace, GT_ERR,
                                  "Vbus write failed\r\n");
                    }
                }
                #ifdef BSP_TVP5158_VERBOSE_DEBUG
                if(retVal == FVID2_SOK)
                {
                    /* read back and print */
                    vbusVal8 = 0;

                    retVal = Bsp_tvp5158VbusRead(
                        pObj,
                        deviceID,
                        vbusAddr,
                        &vbusVal8);
                    if(retVal != FVID2_SOK)
                    {
                        GT_0trace(BspDeviceTrace, GT_ERR, "Vbus read failed\r\n");
                    }
                }
                if(retVal == FVID2_SOK)
                {
                    GT_3trace(BspDeviceTrace, GT_INFO,
                              " TVP5158: 0x%02x: VBUS 0x%08x = 0x%02x\r\n",
                              pCreatePrms->deviceI2cAddr[deviceID], vbusAddr,
                              vbusVal8);
                }
                #endif

                if(retVal != FVID2_SOK)
                {
                    break;
                }
            }
        }

        if(retVal != FVID2_SOK)
        {
            break;
        }
    }

    return (retVal);
}
#endif

/**
 *  \brief   Set audio volume.
 *
 *  When coreId is BSP_TVP5158_CORE_ALL, same volume is set for all channels.
 */
static Int32 Bsp_tvp5158SetAudioVolume(Bsp_Tvp5158HandleObj *pObj,
                                       UInt32                coreId,
                                       UInt32                audioVolume)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[8];
    UInt8  regValue[8];
    UInt32 numRegs;
    UInt32 devId, chId, numDev, vol;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    if(coreId == BSP_TVP5158_CORE_ALL)
    {
        /* setup all channels for all devices */
        devId  = 0;
        chId   = BSP_TVP5158_CORE_ALL;
        numDev = pCreatePrms->numDevicesAtPort;
    }
    else
    {
        devId  = coreId / BSP_TVP5158_CH_PER_DEVICE_MAX;
        chId   = coreId % BSP_TVP5158_CH_PER_DEVICE_MAX;
        numDev = 1U;
    }

    /* There can be at max 2 TVP5158 devices per port */
    if(devId >= BSP_TVP5158_DEV_PER_PORT_MAX)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device ID\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        vol = audioVolume & 0xFU;
        while(numDev--)
        {
            retVal = Bsp_tvp5158SelectWrite(pObj, devId, BSP_TVP5158_CORE_ALL);
            if(retVal != FVID2_SOK)
            {
                GT_0trace(BspDeviceTrace, GT_ERR, "Device select failed\r\n");
            }

            if(retVal == FVID2_SOK)
            {
                numRegs = 0;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_AUDIO_GAIN_1;
                regValue[numRegs] = 0;
                numRegs++;

                regAddr[numRegs]  = (UInt8) BSP_TVP5158_REG_AUDIO_GAIN_2;
                regValue[numRegs] = 0;
                numRegs++;

                retVal = Bsp_deviceRead8(
                    pCreatePrms->deviceI2cInstId,
                    pCreatePrms->deviceI2cAddr[devId],
                    &regAddr[0],
                    &regValue[0],
                    numRegs);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Device read failed\r\n");
                }
            }

            if(retVal == FVID2_SOK)
            {
                if(chId == BSP_TVP5158_CORE_ALL)
                {
                    regValue[0] = regValue[1] = (UInt8) ((vol << 4) | (vol << 0));
                }
                else if(chId == 0)
                {
                    regValue[0] &= 0xF0U;
                    regValue[0] |= (UInt8) (vol << 0);
                }
                else if(chId == 1U)
                {
                    regValue[0] &= 0x0FU;
                    regValue[0] |= (UInt8) (vol << 4);
                }
                else if(chId == 2U)
                {
                    regValue[1] &= 0xF0U;
                    regValue[1] |= (UInt8) (vol << 0);
                }
                else if(chId == 3U)
                {
                    regValue[1] &= 0x0FU;
                    regValue[1] |= (UInt8) (vol << 4);
                }
                else
                {
                    /* This won't happen as chId is modulo of 4 */
                }
            }

            if(retVal == FVID2_SOK)
            {
                retVal = Bsp_deviceWrite8(
                    pCreatePrms->deviceI2cInstId,
                    pCreatePrms->deviceI2cAddr[devId],
                    &regAddr[0],
                    &regValue[0],
                    numRegs);
                if(retVal != FVID2_SOK)
                {
                    GT_0trace(BspDeviceTrace, GT_ERR, "Device write failed\r\n");
                }
                else
                {
                    devId++;
                }
            }
            if(retVal != FVID2_SOK)
            {
                break;
            }
        }
    }

    return (retVal);
}

static Int32 Bsp_tvp5158PrintChipId(Bsp_Tvp5158HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecChipIdParams vidDecChipIdArgs;
    Bsp_VidDecChipIdStatus vidDecChipIdStatus;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    vidDecChipIdArgs.deviceNum = 0;
    retVal = Bsp_tvp5158GetChipId(pObj, &vidDecChipIdArgs, &vidDecChipIdStatus);

    GT_4trace(BspDeviceTrace, GT_INFO,
              " TVP5158: 0x%02x: %04x:%04x:%04x\r\n",
              pObj->createPrms.deviceI2cAddr[0],
              vidDecChipIdStatus.chipId,
              vidDecChipIdStatus.chipRevision,
              vidDecChipIdStatus.firmwareVersion);

    return (retVal);
}

#if 0
/**
 *  \brief check if the video settings combinations are valid
 */
static Int32 Bsp_tvp5158CheckVideoSettings(UInt32 interleaveMode,
                                           UInt32 chMuxNum,
                                           UInt32 vidResSel,
                                           UInt32 outputType)
{
    Int32 retVal = FVID2_SOK;

    switch(interleaveMode)
    {
        case BSP_TVP5158_NON_INTERLEAVED_MODE:
            if(chMuxNum != BSP_TVP5158_1CH_MUX)
            {
                retVal = FVID2_EBADARGS;
            }
            if(outputType != BSP_TVP5158_OUT_TYPE_8BIT)
            {
                retVal = FVID2_EBADARGS;
            }
            if(vidResSel != BSP_TVP5158_RES_D1)
            {
                retVal = FVID2_EBADARGS;
            }
            break;

        case BSP_TVP5158_PIXEL_INTERLEAVED_MODE:
            if((chMuxNum != BSP_TVP5158_2CH_MUX) ||
               (chMuxNum != BSP_TVP5158_4CH_MUX))
            {
                retVal = FVID2_EBADARGS;
            }
            if(outputType != BSP_TVP5158_OUT_TYPE_8BIT)
            {
                retVal = FVID2_EBADARGS;
            }
            if(vidResSel != BSP_TVP5158_RES_D1)
            {
                retVal = FVID2_EBADARGS;
            }
            break;

        case BSP_TVP5158_LINE_INTERLEAVED_MODE:
            if((chMuxNum != BSP_TVP5158_2CH_MUX) ||
               (chMuxNum != BSP_TVP5158_4CH_MUX) ||
               (chMuxNum != BSP_TVP5158_8CH_MUX))
            {
                retVal = FVID2_EBADARGS;
            }
            if(chMuxNum == BSP_TVP5158_4CH_MUX)
            {
                if((vidResSel == BSP_TVP5158_RES_CIF) &&
                   (outputType == BSP_TVP5158_OUT_TYPE_16BIT))
                {
                    retVal = FVID2_EBADARGS;
                }
            }
            else
            {
                if(outputType != BSP_TVP5158_OUT_TYPE_8BIT)
                {
                    retVal = FVID2_EBADARGS;
                }
            }
            break;

        case BSP_TVP5158_LINE_INTERLEAVED_HYBRID_MODE:
            if((chMuxNum != BSP_TVP5158_4CH_MUX) ||
               (chMuxNum != BSP_TVP5158_8CH_MUX))
            {
                retVal = FVID2_EBADARGS;
            }
            if((vidResSel != BSP_TVP5158_RES_HALF_D1 ||
                (vidResSel != BSP_TVP5158_RES_CIF))
               {
                   retVal = FVID2_EBADARGS;
               }
               if(outputType != BSP_TVP5158_OUT_TYPE_8BIT)
               {
                   retVal = FVID2_EBADARGS;
               }
               if((chMuxNum == BSP_TVP5158_8CH_MUX) &&
                  (vidResSel == BSP_TVP5158_RES_HALF_D1))
               {
                   retVal = FVID2_EBADARGS;
               }
               break;

               default:
                   retVal = FVID2_EBADARGS;
                   break;
               }

               return (retVal);
               }
#endif
