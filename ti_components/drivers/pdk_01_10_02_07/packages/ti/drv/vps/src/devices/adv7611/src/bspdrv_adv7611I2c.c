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
 *  \file bspdrv_adv7611I2c.c
 *
 *  \brief ADV7611 video decoder FVID2 driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <adv7611/src/bspdrv_adv7611Priv.h>
#include <ti/drv/vps/include/boards/bsp_board.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

#define ADV7611_NUM_WR_BYTE             (3U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_adv7611SetupVideo(Bsp_Adv7611HandleObj            *pObj,
                                   const Bsp_VidDecVideoModeParams *pPrm);
static Int32 Bsp_adv7611ProgramEdid(Bsp_Adv7611HandleObj            *pObj,
                                    const Bsp_VidDecVideoModeParams *pPrm,
                                    UInt32                           enable);

static Int32 Bsp_adv7611PowerDown(Bsp_Adv7611HandleObj *pObj, UInt32 powerDown);
static Int32 Bsp_adv7611OutputEnable(Bsp_Adv7611HandleObj *pObj, UInt32 enable);

static Int32 Bsp_adv7611ConfigI2cAddr(Bsp_Adv7611HandleObj *pObj);
static Int32 Bsp_adv7611ProgramDefault(Bsp_Adv7611HandleObj *pObj);
static Int32 Bsp_adv7611DetectVideo(Bsp_Adv7611HandleObj *pObj,
                                    UInt32                timeout);

static Int32 Bsp_adv7611I2cRead8(const Bsp_Adv7611HandleObj *pObj,
                                 UInt32                      i2cInstId,
                                 UInt32                      i2cDevAddr,
                                 const UInt8                *regAddr,
                                 UInt8                      *regVal,
                                 UInt32                      numRegs);
static Int32 Bsp_adv7611I2cWrite8(const Bsp_Adv7611HandleObj *pObj,
                                  UInt32                      i2cInstId,
                                  UInt32                      i2cDevAddr,
                                  const UInt8                *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                      numRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Default power-up sequence */
static UInt8       gAdv7611DefaultConfig[][ADV7611_NUM_WR_BYTE] =
{
    /* I2C Address, Register Offset, Value */
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_ALSB_CONTROL,     0x01},
    {BSP_ADV7611_HDMI_I2C_ADDR, BSP_ADV7611_REG_HDMI_REG_48H,        0x40},
    {BSP_ADV7611_HDMI_I2C_ADDR, BSP_ADV7611_REG_HDMI_MUTE_MASK_15_8, 0xBE},
    {BSP_ADV7611_HDMI_I2C_ADDR, BSP_ADV7611_REG_HDMI_REG_02H,        0xFF},
    {BSP_ADV7611_CP_I2C_ADDR,   BSP_ADV7611_REG_CP_CLMP_FREEZE,      0x00}, /* Undocumented register*/
    {BSP_ADV7611_HDMI_I2C_ADDR, 0x9B,                                0x03}, /* Undocumented register*/
    {BSP_ADV7611_HDMI_I2C_ADDR, 0x6F,                                0x0C}, /* Undocumented register*/
    {BSP_ADV7611_HDMI_I2C_ADDR, 0x85,                                0x1F}, /* Undocumented register*/
    {BSP_ADV7611_HDMI_I2C_ADDR, 0x87,                                0x70}, /* Undocumented register*/
    {BSP_ADV7611_HDMI_I2C_ADDR, BSP_ADV7611_REG_HDMI_REG_03H,        0x98},
    {BSP_ADV7611_HDMI_I2C_ADDR, BSP_ADV7611_REG_HDMI_REG_4CH,        0x44},
    {BSP_ADV7611_CP_I2C_ADDR,   BSP_ADV7611_REG_CP_REG_3EH,          0x00},
    {BSP_ADV7611_CP_I2C_ADDR,   BSP_ADV7611_REG_CP_PRE_GAIN_CTRL,    0x80},
    {BSP_ADV7611_HDMI_I2C_ADDR, BSP_ADV7611_REG_HDMI_REG_02H,        0xFE},
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_PRIMARY_MODE,     0x06},
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_VIDEO_STANDARD,   0x02},
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_REG_0C,           0x42},
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_REG_14,           0x7F},
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_LLC_DLL,          0x83},
    {BSP_ADV7611_IO_I2C_ADDR,   BSP_ADV7611_REG_IO_REG_33,           0x40},
    {BSP_ADV7611_CP_I2C_ADDR,   BSP_ADV7611_REG_CP_REG_69H,          0x14},
};

static const UInt8 gEdid1080p60[] =
{
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x52, 0x74, 0x01, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x80, 0x29, 0x1A, 0x78,
    0x0A, 0xE5, 0xB5, 0xA3, 0x55, 0x49, 0x99, 0x27, 0x13, 0x50, 0x54, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38,
    0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x80, 0x68, 0x21, 0x00, 0x00, 0x1E,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x54,
    0x45, 0x53, 0x54, 0x20, 0x54, 0x56, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE8, 0x02, 0x03, 0x17, 0x70,
    0x41, 0x10, 0x26, 0x09, 0x57, 0x03, 0x15, 0x07, 0x50, 0x83, 0x01, 0x00,
    0x00, 0x65, 0x03, 0x0C, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x25,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Resets the ADV7611.
 *
 *  This API
 *      - Disable output
 *      - Power-ON of all module
 *      - Manual reset of ADV7611 and then setup in auto reset mode
 *      - Select default TMDS core
 */
Int32 Bsp_adv7611Reset(Bsp_Adv7611HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[4];
    UInt8  regVal[4];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 delay;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Disable outputs */
    retVal = Bsp_adv7611Stop(pObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device stop failed\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Normal operation */
        retVal = Bsp_adv7611PowerDown(pObj, (UInt32) FALSE);
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
        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_FF;
        regVal[numRegs]  = 0x01U;   /* Self clearing */
        numRegs++;

        retVal += Bsp_adv7611I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            numRegs);

        delay = 50U;
        /* wait for reset to be effective */
        BspOsal_sleep(delay);
    }

    return (retVal);
}

/**
 *  \brief Gets ADV7611 Chip ID and revision ID.
 */
Int32 Bsp_adv7611GetChipId(Bsp_Adv7611HandleObj         *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[4];
    UInt8  regVal[4];
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

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_RD_INFO_H;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_RD_INFO_L;
        regVal[numRegs]  = 0;
        numRegs++;

        retVal = Bsp_adv7611I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[pPrm->deviceNum],
            regAddr,
            regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        pStatus->chipId          = ((UInt32) regVal[0] << 8) | regVal[1];
        pStatus->chipRevision    = 0x00U;
        pStatus->firmwareVersion = 0x00U;
    }

    return (retVal);
}

/**
 *  \brief Sets the required video standard and output formats depending
 *  on requested parameters.
 *
 *  For ADV7611 below parameters in Bsp_VidDecVideoModeParams are ignored
 *  and any value set by user for these parameters is not effective.
 *
 *  videoIfWidth
 *  standard
 *  videoIfMode
 *  videoSystem
 *  videoCropEnable
 *
 *  Depending on video data format ADV7611 is configured as below
 *
 *  videoDataFormat =
 *  FVID2_DF_YUV422P   : 8/16-bit YUV422 single CH embedded sync mode
 *  FVID2_DF_RGB24_888 : 24-bit RGB24  single CH discrete sync mode
 */
Int32 Bsp_adv7611SetVideoMode(Bsp_Adv7611HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32 retVal = FVID2_SOK;

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
        retVal = Bsp_adv7611Reset(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device reset failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Configure the I2C address */
        retVal = Bsp_adv7611ConfigI2cAddr(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "I2C Address Config failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Program recommended settings */
        retVal = Bsp_adv7611ProgramDefault(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Default settings failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Program internal EDID */
        retVal = Bsp_adv7611ProgramEdid(pObj, pPrm, (UInt32) TRUE);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "EDID programming failed\r\n");
        }
    }

    if ((FVID2_SOK == retVal) &&
        (FVID2_STD_AUTO_DETECT == pPrm->standard))
    {
        /* Detect video source properties */
        retVal = Bsp_adv7611DetectVideo(
            pObj,
            pPrm->videoAutoDetectTimeout);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Detect video failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Setup video processing path based on detected source */
        retVal = Bsp_adv7611SetupVideo(pObj, pPrm);
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
Int32 Bsp_adv7611GetVideoStatus(Bsp_Adv7611HandleObj              *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[16];
    UInt8  regVal[16];
    UInt32 numRegs;
    UInt32 vidStat, rb1, rb2, rb3, rb4;
    UInt32 blkLength, t_line;

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

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_HDMI_LVL_RAW_STATUS_3;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_12;
        regVal[numRegs]  = 0;
        numRegs++;

        retVal = Bsp_adv7611I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr[0],
            regAddr,
            regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        vidStat = regVal[0];
        if (BSP_ADV7611_VID_DETECT_MASK ==
            (vidStat & BSP_ADV7611_VID_DETECT_MASK))
        {
            pStatus->isVideoDetect = (UInt32) TRUE;
        }

        vidStat = regVal[1];
        if (BSP_ADV7611_VID_INTERLACE_MASK ==
            (vidStat & BSP_ADV7611_VID_INTERLACE_MASK))
        {
            pStatus->isInterlaced = (UInt32) TRUE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* CP block STDI status registeres */
        numRegs          = 0;
        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_1;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_2;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_3;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_4;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_5;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_6_1;
        regVal[numRegs]  = 0;
        numRegs++;

        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_CP_SYNC_DET_CTRL_CH1_RB_6_2;
        regVal[numRegs]  = 0;
        numRegs++;

        retVal = Bsp_adv7611I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            (UInt32) BSP_ADV7611_CP_I2C_ADDR,
            regAddr,
            regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        rb1 = regVal[0];
        rb2 = regVal[1];
        rb3 = regVal[2];
        rb4 = regVal[3];

        /* Check if the status is valid */
        if ((rb3 & BSP_ADV7611_CH1_STDI_DVALID_MASK) ==
            BSP_ADV7611_CH1_STDI_DVALID_MASK)
        {
            /* Number of 28.6363 MHz clock cycles (XTAL frequency) in a
             * block of eight lines */
            blkLength = (((UInt32) rb3 & ((UInt32) 0x3FU)) << 8) | rb4;
            /* Time interval in usecs for each line */
            t_line = (blkLength * 1000000U) / BSP_ADV7611_XTAL_FREQ_HZ;

            pStatus->frameWidth  = (t_line / 8U);   /* Frame width in usec */
            pStatus->frameHeight = (((UInt32) rb1 << 8) | rb2) + 1U;
            /* time interval in usecs for each frame/field */
            pStatus->frameInterval = (t_line * pStatus->frameHeight) / 8U;
        }
    }

    return (retVal);
}

/**
 *  \brief Starts ADV7611.
 */
Int32 Bsp_adv7611Start(Bsp_Adv7611HandleObj *pObj)
{
    Int32 retVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Enable output */
    retVal = Bsp_adv7611OutputEnable(pObj, (UInt32) TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output enable failed\r\n");
    }

    return retVal;
}

/**
 *  \brief Stops ADV7611.
 */
Int32 Bsp_adv7611Stop(Bsp_Adv7611HandleObj *pObj)
{
    Int32 retVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Disable output */
    retVal = Bsp_adv7611OutputEnable(pObj, (UInt32) FALSE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output disable failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_adv7611RegWrite(Bsp_Adv7611HandleObj          *pObj,
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
        retVal      = Bsp_adv7611I2cWrite8(
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
Int32 Bsp_adv7611RegRead(Bsp_Adv7611HandleObj    *pObj,
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
        retVal = Bsp_adv7611I2cRead8(
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
 *  \brief Setup video processing path based on requested format
 *
 *  pPrm - user required parameters
 */
static Int32 Bsp_adv7611SetupVideo(Bsp_Adv7611HandleObj            *pObj,
                                   const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[8];
    UInt8  regVal[8], chMap;
    UInt32 numRegs;
    UInt32 devAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pPrm));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];

    numRegs = 0;

    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_03;
    if (FVID2_DF_YUV422P == pPrm->videoDataFormat)
    {
        if (FVID2_VIFW_8BIT == pPrm->videoIfWidth)
        {
            regVal[numRegs] = BSP_ADV7611_OP_FMT_8_BIT_SDR_ITU_656;
            chMap           = BSP_ADV7611_OP_CH_SEL_VR_UCRCB_YG;
        }
        else
        {
            /* Default to 16-bit YUV422 */
            regVal[numRegs] = BSP_ADV7611_OP_FMT_16_BIT_SDR_ITU_656;
            chMap           = BSP_ADV7611_OP_CH_SEL_VR_YG_UCRCB;
        }
    }
    else
    {
        /* Default to 24-bit RGB */
        regVal[numRegs] = BSP_ADV7611_OP_FMT_24_BIT_SDR_444;
        chMap           = BSP_ADV7611_OP_CH_SEL_VR_YG_UCRCB;
    }
    numRegs++;

    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_04;
    regVal[numRegs]  = chMap;
    numRegs++;

    /* The D3 TDA3 Starter Kit baseboard does not need to invert clock polarity. */
    if (BSP_BOARD_TDA3XX_D3_SK != Bsp_boardGetId())
    {
        regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_06;
        regVal[numRegs]  = 0xA1U;       /* Invert clock polarity */
        numRegs++;
    }

    retVal = Bsp_adv7611I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

/**
 *  \brief Program internal EDID RAM
 *
 *  pPrm - user required parameters
 */
static Int32 Bsp_adv7611ProgramEdid(Bsp_Adv7611HandleObj            *pObj,
                                    const Bsp_VidDecVideoModeParams *pPrm,
                                    UInt32                           enable)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[8];
    UInt8  regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 loopTimeout, loopCnt;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pPrm));

    pCreatePrms = &pObj->createPrms;

    /* Enable Auto Hot Plug Assert (HPA) so that transmitter can re-read
     * the new EDID once EDID is ready */
    devAddr          = BSP_ADV7611_HDMI_I2C_ADDR;
    numRegs          = 0;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_HDMI_REG_6CH;
    if ((UInt32) TRUE == enable)
    {
        regVal[numRegs] = 0xA0U;
    }
    else
    {
        regVal[numRegs] = 0xA2U;
    }
    numRegs++;
    retVal += Bsp_adv7611I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    /* Program 1080p60 EDID to internal EDID RAM */
    if ((UInt32) TRUE == enable)
    {
        devAddr = BSP_ADV7611_EDID_I2C_ADDR;
        numRegs = 1U;
        for (loopCnt = 0U; loopCnt < sizeof (gEdid1080p60); loopCnt++)
        {
            regAddr[0] = (UInt8) loopCnt;
            regVal[0]  = gEdid1080p60[loopCnt];
            retVal    += Bsp_adv7611I2cWrite8(
                pObj,
                pCreatePrms->deviceI2cInstId,
                devAddr,
                &regAddr[0],
                &regVal[0],
                numRegs);
        }
    }

    /* Enable/disable EDID */
    devAddr          = BSP_ADV7611_KSV_I2C_ADDR;
    numRegs          = 0;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_KSV_HDCP_EDID_CTRL;
    if ((UInt32) TRUE == enable)
    {
        regVal[numRegs] = 0x01U;        /* Enable EDID */
    }
    else
    {
        regVal[numRegs] = 0x00U;        /* Disable EDID */
    }
    numRegs++;
    retVal += Bsp_adv7611I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    if ((FVID2_SOK == retVal) && ((UInt32) TRUE == enable))
    {
        /* Check if EDID is really enabled internally by ADV7611.
         * It needs sometime to calculate the checksum */
        loopTimeout = 1U;
        loopCnt     = 100U;
        while ((loopCnt > 0U) && (FVID2_SOK == retVal))
        {
            devAddr = BSP_ADV7611_KSV_I2C_ADDR;
            numRegs = 0;

            regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_KSV_EDID_DEBUG_2;
            regVal[numRegs]  = 0;
            numRegs++;
            retVal = Bsp_adv7611I2cRead8(
                pObj,
                pCreatePrms->deviceI2cInstId,
                devAddr,
                &regAddr[0],
                &regVal[0],
                numRegs);
            if (FVID2_SOK == retVal)
            {
                if ((regVal[0] & 0x01U) != 0U)
                {
                    break;
                }
            }

            BspOsal_sleep(loopTimeout);
            loopCnt--;
        }

        if (0U == loopCnt)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Enabling Internal EDID failed!!\r\n");
            retVal = FVID2_ETIMEOUT;
        }
    }

    return (retVal);
}

/**
 *  \brief Power ON/OFF ADV7611.
 */
static Int32 Bsp_adv7611PowerDown(Bsp_Adv7611HandleObj *pObj, UInt32 powerDown)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[8];
    UInt8  regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];

    numRegs          = 0;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_0B;
    if ((UInt32) TRUE == powerDown)
    {
        regVal[numRegs] = 0x47U;
    }
    else
    {
        regVal[numRegs] = 0x44U;
    }
    numRegs++;

    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_0C;
    if ((UInt32) TRUE == powerDown)
    {
        regVal[numRegs] = 0x6FU;
    }
    else
    {
        regVal[numRegs] = 0x42U;
    }
    numRegs++;

    retVal = Bsp_adv7611I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

/**
 *  \brief Enable output port.
 */
static Int32 Bsp_adv7611OutputEnable(Bsp_Adv7611HandleObj *pObj, UInt32 enable)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[8];
    UInt8  regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];

    numRegs          = 0;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_REG_15;
    if ((UInt32) TRUE == enable)
    {
        /* Set TRI_AUDIO, TRI_SYNCS, TRI_LLC, TRI_PIX to 0 */
        regVal[numRegs] = 0x00U;
    }
    else
    {
        /* Set TRI_AUDIO, TRI_SYNCS, TRI_LLC, TRI_PIX to 1 */
        regVal[numRegs] = 0xBEU;
    }
    numRegs++;

    retVal = Bsp_adv7611I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

static Int32 Bsp_adv7611ConfigI2cAddr(Bsp_Adv7611HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[8];
    UInt8  regVal[8];
    UInt32 numRegs;
    UInt32 devAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr[0];

    numRegs          = 0;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_CEC_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8)(BSP_ADV7611_CEC_I2C_ADDR << 1);
    numRegs++;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_INFOFRAME_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8)(BSP_ADV7611_INFOFRAME_I2C_ADDR << 1);
    numRegs++;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_DPLL_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8) (BSP_ADV7611_DPLL_I2C_ADDR << 1);
    numRegs++;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_KSV_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8) (BSP_ADV7611_KSV_I2C_ADDR << 1);
    numRegs++;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_EDID_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8) (BSP_ADV7611_EDID_I2C_ADDR << 1);
    numRegs++;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_HDMI_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8) (BSP_ADV7611_HDMI_I2C_ADDR << 1);
    numRegs++;
    regAddr[numRegs] = (UInt8) BSP_ADV7611_REG_IO_CP_SLAVE_ADDR;
    regVal[numRegs]  = (UInt8) (BSP_ADV7611_CP_I2C_ADDR << 1);
    numRegs++;

    retVal = Bsp_adv7611I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

static Int32 Bsp_adv7611ProgramDefault(Bsp_Adv7611HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecCreateParams *pCreatePrms;
    UInt8  regAddr[30];
    UInt8  regVal[30];
    UInt32 devAddr, cnt;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    for (cnt = 0;
         cnt < (sizeof (gAdv7611DefaultConfig) / ADV7611_NUM_WR_BYTE);
         cnt++)
    {
        devAddr = gAdv7611DefaultConfig[cnt][0];
        if (BSP_ADV7611_IO_I2C_ADDR == devAddr)
        {
            /* Use the address passed from app as this could be different
             * based on board */
            devAddr = pCreatePrms->deviceI2cAddr[0];
        }
        regAddr[0] = gAdv7611DefaultConfig[cnt][1];
        regVal[0]  = gAdv7611DefaultConfig[cnt][2];
        retVal    += Bsp_adv7611I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            (UInt32) 1);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "I2C write to IO Expander failed!!\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Wait until video is detected and the get video properties
 */
static Int32 Bsp_adv7611DetectVideo(Bsp_Adv7611HandleObj *pObj,
                                    UInt32                timeout)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidDecVideoStatus vidStatus;
    Bsp_VidDecVideoStatusParams vidStatusPrm;
    UInt32 loopTimeout, curTimeout = 0;
    UInt32 isVideoDetect = FALSE;
    UInt32 delay         = 100U;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    vidStatusPrm.channelNum = 0;

    timeout     = 1000U; /* hard code for now */
    loopTimeout = 50U;   /* check video retVal every 50 OS ticks */

    BspOsal_sleep(delay);

    while (1)
    {
        retVal = Bsp_adv7611GetVideoStatus(pObj, &vidStatusPrm, &vidStatus);
        if (FVID2_SOK == retVal)
        {
            if (vidStatus.isVideoDetect)
            {
                isVideoDetect = (UInt32) TRUE;
            }
            else
            {
                BspOsal_sleep(loopTimeout);
                if (timeout != (UInt32) FVID2_TIMEOUT_FOREVER)
                {
                    curTimeout += loopTimeout;
                    if (curTimeout >= timeout)
                    {
                        retVal = FVID2_ETIMEOUT;
                    }
                }
            }
        }
        if ((isVideoDetect == (UInt32) TRUE) || (retVal != FVID2_SOK))
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief I2C read wrapper function.
 */
static Int32 Bsp_adv7611I2cRead8(const Bsp_Adv7611HandleObj *pObj,
                                 UInt32                      i2cInstId,
                                 UInt32                      i2cDevAddr,
                                 const UInt8                *regAddr,
                                 UInt8                      *regVal,
                                 UInt32                      numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

    retVal = Bsp_deviceRead8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C read failed\r\n");
    }

    return (retVal);
}

/**
 *  \brief I2C write wrapper function.
 */
static Int32 Bsp_adv7611I2cWrite8(const Bsp_Adv7611HandleObj *pObj,
                                  UInt32                      i2cInstId,
                                  UInt32                      i2cDevAddr,
                                  const UInt8                *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                      numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

    retVal = Bsp_deviceWrite8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C write failed\r\n");
    }

    return (retVal);
}

