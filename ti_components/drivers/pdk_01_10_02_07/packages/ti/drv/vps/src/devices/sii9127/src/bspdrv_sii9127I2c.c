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
 *  \file bspdrv_sii9127I2c.c
 *
 *  \brief SII9127 video decoder FVID2 driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sii9127/src/bspdrv_sii9127Priv.h>

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

static Int32 Bsp_sii9127SetupVideo(Bsp_Sii9127HandleObj      *pObj,
                                   const Bsp_VidDecVideoModeParams *pPrm,
                                   const Bsp_Sii9127AviInfoFrame   *pAviInfo);

static Int32 Bsp_sii9127PowerDown(Bsp_Sii9127HandleObj *pObj, UInt32 powerDown);
static Int32 Bsp_sii9127OutputEnable(Bsp_Sii9127HandleObj *pObj, UInt32 enable);

static Int32 Bsp_sii9127UpdateRegCache(Bsp_Sii9127HandleObj *pObj);

static Int32 Bsp_sii9127ReadAviInfo(Bsp_Sii9127HandleObj    *pObj,
                                    Bsp_Sii9127AviInfoFrame *pAviInfo);
static Int32 Bsp_sii9127DetectVideo(Bsp_Sii9127HandleObj    *pObj,
                                    Bsp_Sii9127AviInfoFrame *pAviInfo,
                                    UInt32                   timeout);
static Int32 Bsp_sii9127SelectTmdsCore(Bsp_Sii9127HandleObj *pObj,
                                       UInt32                coreId);

static Int32 Bsp_sii9127I2cRead8(const Bsp_Sii9127HandleObj *pObj,
                                 UInt32                i2cInstId,
                                 UInt32                i2cDevAddr,
                                 const UInt8          *regAddr,
                                 UInt8                *regVal,
                                 UInt32                numRegs);
static Int32 Bsp_sii9127I2cWrite8(const Bsp_Sii9127HandleObj *pObj,
                                  UInt32                i2cInstId,
                                  UInt32                i2cDevAddr,
                                  const UInt8          *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                numRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Resets the SII9127.
 *
 *  This API
 *      - Disable output
 *      - Power-ON of all module
 *      - Manual reset of SII9127 and then setup in auto reset mode
 *      - Select default TMDS core
 */
Int32 Bsp_sii9127Reset(Bsp_Sii9127HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8 regAddr[8];
    UInt8 regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 delay;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    Bsp_sii9127ResetRegCache(pObj);

    /* Disable outputs */
    retVal = Bsp_sii9127Stop(pObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device stop failed\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Normal operation */
        retVal = Bsp_sii9127PowerDown(pObj, (UInt32) FALSE);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device power-up failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;
        devAddr     = pCreatePrms->deviceI2cAddr[0];

        numRegs          = 0;
        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_SRST0;
        regVal[numRegs]  = 0x2FU;  /* reset AAC, HDCP, ACR, audio FIFO, SW */
        numRegs++;

        retVal += Bsp_sii9127I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            numRegs);

        delay = 50U;
        /* wait for reset to be effective */
        BspOsal_sleep(delay);

        /* remove reset and setup in auto-reset mode */
        numRegs          = 0;
        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_SRST0;
        regVal[numRegs]  = 0x10U;  /* auto-reset SW */
        numRegs++;

        retVal += Bsp_sii9127I2cWrite8(pObj,
                                       pCreatePrms->deviceI2cInstId,
                                       devAddr,
                                       &regAddr[0],
                                       &regVal[0],
                                       numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        /* select TDMS core */
        retVal = Bsp_sii9127SelectTmdsCore(pObj,
                                           BSP_SII9127_CORE_ID_DEFAULT);
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9127UpdateRegCache(pObj);
    }

    if (FVID2_SOK == retVal)
    {
        /* Reset zone control sequence.
         * Write factory registers with default values. This is to fix
         * the issue with detecting height */
        devAddr = BSP_SII9127_COLOR_GAMUT_I2C_ADDR;
        numRegs = 0;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_FACTORY_A87;
        regVal[numRegs]  = 0x03U;
        numRegs++;
        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_FACTORY_A81;
        regVal[numRegs]  = 0x10U;
        numRegs++;
        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_FACTORY_A88;
        regVal[numRegs]  = 0x40U;
        numRegs++;

        retVal = Bsp_sii9127I2cWrite8(
                    pObj,
                    pCreatePrms->deviceI2cInstId,
                    devAddr,
                    &regAddr[0],
                    &regVal[0],
                    numRegs);
    }

    return (retVal);
}

/**
 *  \brief Gets SII9127 Chip ID and revision ID.
 */
Int32 Bsp_sii9127GetChipId(Bsp_Sii9127HandleObj   *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus *pStatus)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8 regAddr[8];
    UInt8 regVal[8];
    UInt32 numRegs;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pStatus) ||
        (NULL == pPrm) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));

        pCreatePrms = &pObj->createPrms;

        numRegs = 0;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VND_IDL;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VND_IDH;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DEV_IDL;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DEV_IDH;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DEV_REV;
        regVal[numRegs]  = 0;
        numRegs++;

        retVal = Bsp_sii9127I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            regAddr,
            regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        pStatus->chipId          = ((UInt32) regVal[3] << 8) | regVal[2];
        pStatus->chipRevision    = regVal[4];
        pStatus->firmwareVersion = ((UInt32) regVal[1] << 8) | regVal[0];
    }

    return (retVal);
}

/**
 *  \brief Sets the required video standard and output formats depending
 *  on requested parameters.
 *
 *  For SII9127 below parameters in Bsp_VidDecVideoModeParams are ignored
 *  and any value set by user for these parameters is not effective.
 *
 *  videoIfWidth
 *  standard
 *  videoIfMode
 *  videoSystem
 *  videoCropEnable
 *
 *  Depending on video data format SII9127 is configured as below
 *
 *  videoDataFormat =
 *  FVID2_DF_YUV422P   : 16-bit YUV422 single CH embedded sync auto-detect mode
 *  FVID2_DF_YUV444P   : 24-bit YUV444 single CH discrete sync auto-detect mode
 *  FVID2_DF_RGB24_888 : 24-bit RGB24  single CH discrete sync auto-detect mode
 */
Int32 Bsp_sii9127SetVideoMode(Bsp_Sii9127HandleObj      *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9127AviInfoFrame aviInfo;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if (NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Reset device */

        retVal = Bsp_sii9127Reset(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device reset failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Detect video source properties */
        retVal = Bsp_sii9127DetectVideo(
            pObj,
            &aviInfo,
            pPrm->videoAutoDetectTimeout);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Detect video failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        if ((FVID2_STD_480I == pPrm->standard) ||
            (FVID2_STD_576I == pPrm->standard) ||
            (FVID2_STD_D1 == pPrm->standard) ||
            (FVID2_STD_NTSC == pPrm->standard) ||
            (FVID2_STD_PAL == pPrm->standard))
        {
            aviInfo.pixelRepeat = BSP_SII9127_AVI_INFO_PIXREP_2X;
        }

        /* Setup video processing path based on detected source */
        retVal = Bsp_sii9127SetupVideo(pObj, pPrm, &aviInfo);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Setup video failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(&pObj->modePrms, pPrm, sizeof (pObj->modePrms));
    }

    return (retVal);
}

/**
 *  \brief Gets the video status of the detected video.
 */
Int32 Bsp_sii9127GetVideoStatus(Bsp_Sii9127HandleObj        *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus       *pStatus)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[16];
    UInt8  regVal[16];
    UInt32 numRegs;
    UInt32 hRes, vRes, dePix, deLin, xclkInPclk;
    UInt32 sysStat, vidStat;
    UInt32 t_line;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pStatus) || (NULL == pPrm))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));

        pCreatePrms = &pObj->createPrms;

        numRegs = 0;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_H_RESL;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_H_RESH;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_V_RESL;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_V_RESH;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DE_PIXL;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DE_PIXH;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DE_LINL;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_DE_LINH;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_XPCNT1;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_XPCNT2;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_STAT;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_SII9127_REG_STATE;
        regVal[numRegs]  = 0;
        numRegs++;

        retVal = Bsp_sii9127I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[0],
            regAddr,
            regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        /* Horizontal resolution */
        hRes = ((UInt32) regVal[1] << 8) | regVal[0];
        /* Vertical resolution */
        vRes = ((UInt32) regVal[3] << 8) | regVal[2];

        /* Horizontal active data resolution */
        dePix = ((UInt32) regVal[5] << 8) | regVal[4];
        /* Vertical active data resolution */
        deLin = ((UInt32) regVal[7] << 8) | regVal[6];

        /* Number of xclks per 2048 video clocks */
        xclkInPclk = ((UInt32) regVal[9] << 8) | regVal[8];

        /* Video status */
        vidStat = regVal[10];

        /* System status */
        sysStat = regVal[11];

        if (sysStat & BSP_SII9127_VID_DETECT)
        {
            pStatus->isVideoDetect = (UInt32) TRUE;

            if (vidStat & BSP_SII9127_VID_INTERLACE)
            {
                pStatus->isInterlaced = (UInt32) TRUE;
            }

            pStatus->frameWidth  = dePix;
            pStatus->frameHeight = deLin;

            /* Time interval in usecs for each line */
            t_line = (hRes * xclkInPclk * 1000U) /
                     (BSP_SII9127_FXTAL_KHZ * 2048U);

            /* time interval in usecs for each frame/field */
            pStatus->frameInterval = t_line * vRes;
        }
    }

    return (retVal);
}

/**
 *  \brief Starts SII9127.
 */
Int32 Bsp_sii9127Start(Bsp_Sii9127HandleObj *pObj)
{
    Int32 retVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Enable output */
    retVal = Bsp_sii9127OutputEnable(pObj, (UInt32)TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output enable failed\r\n");
    }

    return retVal;
}

/**
 *  \brief Stops SII9127.
 */
Int32 Bsp_sii9127Stop(Bsp_Sii9127HandleObj *pObj)
{
    Int32 retVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Disable output */
    retVal = Bsp_sii9127OutputEnable(pObj, (UInt32) FALSE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output disable failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_sii9127RegWrite(Bsp_Sii9127HandleObj    *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;
        retVal      = Bsp_sii9127I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            pPrm->regAddr,
            pPrm->regValue8,
            pPrm->numRegs);
    }

    return (retVal);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_sii9127RegRead(Bsp_Sii9127HandleObj    *pObj,
                         Bsp_VidDecRegRdWrParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pCreatePrms = &pObj->createPrms;
        BspUtils_memset(pPrm->regValue8, 0, pPrm->numRegs);
        retVal = Bsp_sii9127I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            pPrm->regAddr,
            pPrm->regValue8,
            pPrm->numRegs);
    }

    return (retVal);
}

/**
 *  \brief Reset regsiter cache.
 */
Int32 Bsp_sii9127ResetRegCache(Bsp_Sii9127HandleObj *pObj)
{
#ifdef BSP_SII9127_USE_REG_CACHE
    BspUtils_memset(pObj->regCache, 0, sizeof (pObj->regCache));

    /* for now hard code default values in registers 0x0 to 0x7 */
    pObj->regCache[0][0] = 0x01;
    pObj->regCache[0][1] = 0x00;
    pObj->regCache[0][2] = 0x35;
    pObj->regCache[0][3] = 0x91;
    pObj->regCache[0][4] = 0x03;
    pObj->regCache[0][5] = 0x00;
    pObj->regCache[0][6] = 0x1F; /* assume signal is detected */
    pObj->regCache[0][7] = 0x00;
#endif

    return (FVID2_SOK);
}

/**
 *  \brief Setup video processing path based on detected source
 *
 *  pAviInfoFrame - input source properties
 *  pPrm - user required parameters
 */
static Int32 Bsp_sii9127SetupVideo(Bsp_Sii9127HandleObj      *pObj,
                                   const Bsp_VidDecVideoModeParams *pPrm,
                                   const Bsp_Sii9127AviInfoFrame   *pAviInfo)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[32];
    UInt8  regVal[32];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 insSavEav, cscR2Y, upSmp, downSmp, chMap;
    UInt32 cscY2R, outColorSpace, isBT709, inPixRep;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pPrm));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];

    outColorSpace = BSP_SII9127_COLOR_FORMAT_YUV;
    if (FVID2_DF_RGB24_888 == pPrm->videoDataFormat)
    {
        outColorSpace = BSP_SII9127_COLOR_FORMAT_RGB;
    }

    inPixRep = pAviInfo->pixelRepeat;
    if (inPixRep > BSP_SII9127_AVI_INFO_PIXREP_4X)
    {
        inPixRep = 0;
        GT_0trace(BspDeviceTrace, GT_ERR, "Invalid pixel repeat mode\r\n");
        retVal = FVID2_EFAIL;
    }

    isBT709 = 1U;
    if (BSP_SII9127_AVI_INFO_CMETRIC_ITU601 == pAviInfo->colorImetric)
    {
        isBT709 = 0;
    }

    cscR2Y    = 0;
    upSmp     = 0;
    downSmp   = 0;
    cscY2R    = 0;
    insSavEav = 0;

    switch (pAviInfo->colorSpace)
    {
        case BSP_SII9127_AVI_INFO_COLOR_RGB444:
            switch (pPrm->videoDataFormat)
            {
                case FVID2_DF_YUV422P:
                    cscR2Y    = 1U;
                    downSmp   = 1U;
                    insSavEav = 1U;
                    break;

                case FVID2_DF_YUV444P:
                    cscR2Y = 1U;
                    break;

                case FVID2_DF_RGB24_888:
                    break;

                default:
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid data format\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
            }
            break;

        case BSP_SII9127_AVI_INFO_COLOR_YUV444:
            switch (pPrm->videoDataFormat)
            {
                case FVID2_DF_YUV422P:
                    downSmp   = 1U;
                    insSavEav = 1U;
                    break;

                case FVID2_DF_YUV444P:
                    break;

                case FVID2_DF_RGB24_888:
                    cscY2R = 1U;
                    break;

                default:
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid data format\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
            }
            break;

        case BSP_SII9127_AVI_INFO_COLOR_YUV422:
            switch (pPrm->videoDataFormat)
            {
                case FVID2_DF_YUV422P:
                    insSavEav = 1U;
                    break;

                case FVID2_DF_YUV444P:
                    upSmp = 1U;
                    break;

                case FVID2_DF_RGB24_888:
                    upSmp  = 1U;
                    cscY2R = 1U;
                    break;

                default:
                    GT_0trace(BspDeviceTrace, GT_ERR, "Invalid data format\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
            }
            break;

        default:
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid color space\r\n");
            retVal = FVID2_EFAIL;
            break;
    }

    numRegs = 0;

    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_MODE;
    regVal[numRegs]  = (UInt8) ((insSavEav << 7) /* 1: SAV2EAV enable   , 0: disable */
                       | ((UInt32)0 << 6)       /* 1: Mux Y/C          , 0: No MUX  */
                       | ((UInt32)1U << 5)       /* 1: Dither enable    , 0: disable */
                       | ((UInt32)1U << 4)       /* 1: R2Y compress     , 0: bypass  */
                       | (cscR2Y << 3)  /* 1: Enable R2Y CSC   , 0: bypass  */
                       | (upSmp << 2)   /* 1: YUV422 to YUV444 , 0: bypass  */
                       | (downSmp << 1)) /* 1: YUV444 to YUV422 , 0: bypass  */
    ;
    numRegs++;

    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_MODE2;
    regVal[numRegs]  = (UInt8) (((UInt32)0 << 6)               /* 0: Dither to 8bits, 1: 10bits,
                                               * 2: 12bits  */
                       | ((UInt32)0 << 5)             /* 0: EVNODD LOW if field 0 is
                                               * even, 1: HIGH */
                       | ((UInt32)1 << 3)             /* 1: Y2R compress     , 0:
                                               * bypass           */
                       | (cscY2R << 2)        /* 1: Y2R CSC          , 0:
                                               * bypass           */
                       | (outColorSpace << 1) /* 0: Output format RGB, 1: YUV
                                               *          */
                       | ((UInt32)1 << 0))             /* 1: Range clip enable, 0:
                                               * disable          */
    ;
    numRegs++;

    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_CTRL;
    regVal[numRegs]  = (UInt8) (((UInt32)0 << 7)         /* 0: Do not invert VSYNC, 1: invert */
                       | ((UInt32)0 << 6)       /* 0: Do not invert HSYNC, 1: invert */
                       | (isBT709 << 2) /* 0: Y2R BT601          , 1: BT709  */
                       | ((UInt32)0 << 1)       /* 0: 8bits RGB or YUV   , 1: YUV422 >
                                         * 8 bits */
                       | (isBT709 << 0)) /* 0: R2Y BT601          , 1: BT709  */
    ;
    numRegs++;

    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_SYS_CTRL1;
    regVal[numRegs]  = (UInt8) ((inPixRep << 6)   /* 0: Output pixel clock divided 1x,
                                          * 1: 1/2x, 3: 1/4x */
                       | (inPixRep << 4) /* 0: Input pixel replicate 1x, 1:2x,
                                          * 3:4x            */
                       | ((UInt32)1 << 2)        /* 0: 12-bit mode         , 1: 24-bit
                                          * mode      */
                       | ((UInt32)0 << 1)        /* 0: Normal output clock , 1: Invert
                                          * clock     */
                       | ((UInt32)1 << 0))        /* 0: Power down          , 1: Normal
                                          * operation */
    ;
    numRegs++;

    /*     Q[23:16]  Q[15:8]  Q[7:0]
     *  0:     R        G       B
     *  1:     R        B       G
     *  2:     G        R       B
     *  3:     G        B       R
     *  4:     B        R       G
     *  5:     B        G       R
     *
     * On Vision Card
     *  Q4-Q10  =>  D0 D7   ->  Read / CbCr
     *  Q16-Q23 =>  D8 D16  ->  Green / Y
     *  Q28-Q35 =>  D17 D23 ->  Blue
     */
    chMap = 0x05U;
    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_VID_CH_MAP;
    regVal[numRegs]  = (UInt8) chMap;
    numRegs++;

    if (FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9127I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            numRegs);
    }

    return (retVal);
}

/**
 *  \brief Power ON/OFF SII9127.
 */
static Int32 Bsp_sii9127PowerDown(Bsp_Sii9127HandleObj *pObj, UInt32 powerDown)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8 regAddr[8];
    UInt8 regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];

    numRegs          = 0;
    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_SYS_CTRL1;
    regVal[numRegs]  = 0;
    numRegs++;

    retVal = Bsp_sii9127I2cRead8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        regVal,
        numRegs);
    if (FVID2_SOK == retVal)
    {
        if ((UInt32)TRUE == powerDown)
        {
            regVal[0] = 0x04U;  /* power down  */
        }
        else
        {
            regVal[0] = 0x05U;  /* normal operation */
        }

        retVal = Bsp_sii9127I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            numRegs);
    }

    return (retVal);
}

/**
 *  \brief Enable output port.
 */
static Int32 Bsp_sii9127OutputEnable(Bsp_Sii9127HandleObj *pObj, UInt32 enable)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8 regAddr[8];
    UInt8 regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0] +
                  BSP_SII9127_I2C_PORT1_OFFSET;

    numRegs          = 0;
    regAddr[numRegs] = BSP_SII9127_REG_SYS_PWR_DWN_2;
    regVal[numRegs]  = 0x43U;          /* Enable all expect outputs */
    if ((UInt32)TRUE == enable)
    {
        /* Enable outputs  */
        regValue = (UInt32)regVal[numRegs];
        regValue |= ((UInt32)1 << (UInt32)2);
        regVal[numRegs] = (UInt8)regValue;
    }
    numRegs++;

    regAddr[numRegs] = BSP_SII9127_REG_SYS_PWR_DWN;
    regVal[numRegs]  = 0xADU;          /* Enable all expect outputs */
    if ((UInt32)TRUE == enable)
    {
        regValue = (UInt32)regVal[numRegs];
        regValue |= ((UInt32)1 << (UInt32)6);
        regVal[numRegs] = (UInt8)(regValue);  /* Enable outputs  */
    }
    numRegs++;

    retVal = Bsp_sii9127I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

static Int32 Bsp_sii9127UpdateRegCache(Bsp_Sii9127HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

#ifdef BSP_SII9127_USE_REG_CACHE
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8 numRegs = 0xf8;
    UInt32 devAddr[2];
    UInt8 regAddr[8];
    UInt8 regVal[8];

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr[0]  = pCreatePrms->deviceI2cAddr[0];
    devAddr[1]  = pCreatePrms->deviceI2cAddr[0] + BSP_SII9127_I2C_PORT1_OFFSET;

    Bsp_sii9127ResetRegCache(pObj);

    regAddr[0] = 0;
    regAddr[1] = 1;

    /* dummy read to make next read io work */
    retVal = Bsp_deviceRead8(
        pCreatePrms->deviceI2cInstId,
        devAddr[0],
        regAddr,
        regVal,
        2);
    retVal |= Bsp_deviceRawRead8(
        pCreatePrms->deviceI2cInstId,
        devAddr[0],
        &pObj->regCache[0][8],
        numRegs);

    retVal |= Bsp_deviceRawRead8(
        pCreatePrms->deviceI2cInstId,
        devAddr[1],
        &pObj->regCache[1][8],
        numRegs);
#endif

    return (retVal);
}

/**
 *  \brief Read AVI packet info and parse information from it
 *
 *  pAviInfo - parsed information returned by this API
 */
static Int32 Bsp_sii9127ReadAviInfo(Bsp_Sii9127HandleObj    *pObj,
                                    Bsp_Sii9127AviInfoFrame *pAviInfo)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[32];
    UInt8  regVal[32];
    UInt8  numRegs;
    UInt32 devAddr;
    UInt8  aviAddr;
    UInt8 *aviData;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pAviInfo));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0] +
                  BSP_SII9127_I2C_PORT1_OFFSET;
    numRegs     = 0;

    /* Read AVI Info Frame */
    for (aviAddr =  BSP_SII9127_REG_AVI_TYPE;
         aviAddr <=  BSP_SII9127_REG_AVI_DBYTE15;
         aviAddr++)
    {
        regAddr[numRegs] = aviAddr;
        regVal[numRegs]  = 0;
        numRegs++;
    }

    retVal = Bsp_sii9127I2cRead8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        regVal,
        (UInt32) numRegs);

    if (FVID2_SOK == retVal)
    {
        if ((regVal[0] == BSP_SII9127_AVI_INFO_PACKET_CODE) &&
            (regVal[1] == BSP_SII9127_AVI_INFO_VERSION_CODE) &&
            (regVal[2] == BSP_SII9127_AVI_INFO_PACKET_LENGTH))
        {
            /*
             * Valid AVI packet recevied
             */
            retVal = FVID2_SOK;

            aviData = &regVal[3]; /* point to start of AVI data checksum */

            /*
             * parse information
             */
            pAviInfo->colorSpace   = ((aviData[1] >> 5U) & 0x3U);
            pAviInfo->colorImetric = ((aviData[2] >> 6U) & 0x3U);
            pAviInfo->pixelRepeat  = ((aviData[5] >> 0U) & 0xFU);
        }
        else
        {
            retVal = FVID2_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  \brief Wait until video is detected and the get video properties
 */
static Int32 Bsp_sii9127DetectVideo(Bsp_Sii9127HandleObj    *pObj,
                                    Bsp_Sii9127AviInfoFrame *pAviInfo,
                                    UInt32                   timeout)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecVideoStatus vidStatus;
    Bsp_VidDecVideoStatusParams vidStatusPrm;
    UInt32 loopTimeout, curTimeout = 0;
    UInt32 isVideoDetect = FALSE;
    UInt32 delay = 100U;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pAviInfo));

    vidStatusPrm.channelNum = 0;

    timeout     = 1000U; /* hard code for now */
    loopTimeout = 250U;  /* check video retVal every 50 OS ticks */

    BspOsal_sleep(delay);

    while (1)
    {
        retVal = Bsp_sii9127GetVideoStatus(pObj, &vidStatusPrm, &vidStatus);
        if (retVal == FVID2_SOK)
        {
            if (vidStatus.isVideoDetect)
            {
                isVideoDetect = (UInt32)TRUE;
            }
            else
            {
                BspOsal_sleep(loopTimeout);
                if (timeout != ((UInt32) FVID2_TIMEOUT_FOREVER))
                {
                    curTimeout += loopTimeout;
                    if (curTimeout >= timeout)
                    {
                        retVal = FVID2_ETIMEOUT;
                    }
                }
            }
        }
        if((isVideoDetect == (UInt32)TRUE) || (retVal != FVID2_SOK))
        {
            break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Video detected, read AVI info */
        retVal = Bsp_sii9127ReadAviInfo(pObj, pAviInfo);

#ifndef BSP_SII9127_USE_AVI_FRAME_INFO
        /* Hardcode AVI frame info */
        pAviInfo->colorSpace   = BSP_SII9127_AVI_INFO_COLOR_RGB444;
        pAviInfo->colorImetric = BSP_SII9127_AVI_INFO_CMETRIC_ITU709;
        pAviInfo->pixelRepeat  = BSP_SII9127_AVI_INFO_PIXREP_NONE;
        retVal = FVID2_SOK;
#endif
    }

    return (retVal);
}

/**
 *  \brief Select TMDS core
 */
static Int32 Bsp_sii9127SelectTmdsCore(Bsp_Sii9127HandleObj *pObj,
                                       UInt32                coreId)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8 regAddr[8];
    UInt8 regVal[8], sysSwtchc2;
    UInt32 numRegs;
    UInt32 devAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];
    numRegs     = 0;

    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_SYS_SWTCHC;
    switch (coreId)
    {
        case 0:
            regVal[numRegs] = BSP_SII9127_SEL_DDC_PORT_0;
            sysSwtchc2 = BSP_SII9127_SEL_TMDS_CORE_0;
            break;

        case 1U:
            regVal[numRegs] = BSP_SII9127_SEL_DDC_PORT_1;
            sysSwtchc2 = BSP_SII9127_SEL_TMDS_CORE_1;
            break;

        case 2U:
            regVal[numRegs] = BSP_SII9127_SEL_DDC_PORT_2;
            sysSwtchc2 = BSP_SII9127_SEL_TMDS_CORE_2;
            break;

        case 3U:
            regVal[numRegs] = BSP_SII9127_SEL_DDC_PORT_3;
            sysSwtchc2 = BSP_SII9127_SEL_TMDS_CORE_3;
            break;

        default:
            regVal[numRegs] = BSP_SII9127_SEL_DDC_PORT_0;
            sysSwtchc2 = BSP_SII9127_SEL_TMDS_CORE_0;
            break;
    }
    numRegs++;

    regAddr[numRegs] = (UInt8) BSP_SII9127_REG_SYS_SWTCHC2;
    regVal[numRegs] = sysSwtchc2;
    numRegs++;

    retVal = Bsp_sii9127I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

/**
 *  \brief I2C read wrapper function.
 */
static Int32 Bsp_sii9127I2cRead8(const Bsp_Sii9127HandleObj *pObj,
                                 UInt32                i2cInstId,
                                 UInt32                i2cDevAddr,
                                 const UInt8          *regAddr,
                                 UInt8                *regVal,
                                 UInt32                numRegs)
{
    Int32  retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

#ifdef BSP_SII9127_USE_REG_CACHE
    UInt32 reg, port;

    if (pObj->createPrms.deviceI2cAddr[0] == i2cDevAddr)
    {
        port = 0;
    }
    else
    {
        port = 1;
    }

    for (reg = 0U; reg < numRegs; reg++)
    {
        regVal[reg] = pObj->regCache[port][regAddr[reg]];
    }
#else
    retVal = Bsp_deviceRead8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C read failed\r\n");
    }
#endif

    return (retVal);
}

/**
 *  \brief I2C write wrapper function.
 */
static Int32 Bsp_sii9127I2cWrite8(const Bsp_Sii9127HandleObj *pObj,
                                  UInt32                i2cInstId,
                                  UInt32                i2cDevAddr,
                                  const UInt8          *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                numRegs)
{
    Int32  retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

#ifdef BSP_SII9127_USE_REG_CACHE
    UInt32 reg, port;

    if (pObj->createPrms.deviceI2cAddr[0] == i2cDevAddr)
    {
        port = 0;
    }
    else
    {
        port = 1;
    }

    for (reg = 0U; reg < numRegs; reg++)
    {
        pObj->regCache[port][regAddr[reg]] = regVal[reg];
    }
#endif

    retVal = Bsp_deviceWrite8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C write failed\r\n");
    }

    return (retVal);
}
