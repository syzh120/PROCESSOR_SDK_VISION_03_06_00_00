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
 *  \file bspdrv_ov1063xI2c.c
 *
 *  \brief OV1063x sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov1063x/src/bspdrv_ov1063xPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Bsp_VidSensorConfigRegs
    gBsp_Ov1063xLvdsSensorsDefault[BSP_OV1063X_NUM_REGS];
extern Bsp_VidSensorConfigRegs     gBsp_Ov1063xSensorsDefault[
    BSP_OV1063X_NUM_REGS];

static const UInt32 nHCropMapping[][2] =
{
    {BSP_OV1063X_HOR_CROP_0, 0x00},
    {BSP_OV1063X_HOR_CROP_1, 0x04},
    {BSP_OV1063X_HOR_CROP_2, 0x08},
};

static const UInt32 nResMapping[][3] =
{
    {FVID2_STD_CIF,     352,  288},
    {FVID2_STD_720P_60, 1280, 720},
    {FVID2_STD_720P_50, 1280, 720},
    {FVID2_STD_VGA_60,  640,  480},
    {FVID2_STD_VGA_72,  640,  480},
    {FVID2_STD_VGA_75,  640,  480},
    {FVID2_STD_VGA_85,  640,  480},
    {FVID2_STD_WXGA_60, 1280, 800},
    {FVID2_STD_WXGA_75, 1280, 800},
    {FVID2_STD_WXGA_85, 1280, 800},
};

static const UInt32 nRestoPllMapping[][5] =
{
    {FVID2_STD_720P_60, FVID2_FPS_30, 3, 40, 1},
    {FVID2_STD_720P_50, FVID2_FPS_30, 3, 40, 1},
    {FVID2_STD_WXGA_60, FVID2_FPS_30, 3, 46, 1},
    {FVID2_STD_WXGA_75, FVID2_FPS_30, 3, 46, 1},
    {FVID2_STD_WXGA_85, FVID2_FPS_30, 3, 46, 1},
};

static const Bsp_VidSensorFeatures gBspOv1063xSensorFeatures =
{
    0,                             /* SensorId */
    0U,                            /* Chip Id, read from register */
    0U,                            /* Revision Id, read from register */
    0U,                            /* firmware version, read from register */
    FVID2_DF_BAYER_BGGR,           /* Bayer format */
    BSP_OV1063X_ACTIVE_PIXELS_H,   /* Active Width */
    BSP_OV1063X_ACTIVE_PIXELS_V,   /* Active Height */
    TRUE,                          /* isEmbededDataSupported */
    TRUE,                          /* isManualExposureSupported */
    FALSE,                         /* isEepromDataSupported */
    TRUE,                          /* isSoftStandbySupported */
    TRUE,                          /* isFlipSupported */
    FALSE,                         /* isManualAnalogGainSupported */
    FALSE,                         /* isWdrModeSupported */
    FALSE,                         /* isSetCfgSupported */
    FALSE,                         /* isDccCfgSupported */
    FALSE                          /* isOnePassWdrSupported */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Get OV10630 chip ID and Manufacturer ID
 */
Int32 Bsp_ov1063xGetChipId(Bsp_Ov1063xHandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus)
{
    Int32  status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreateArgs;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    UInt32 numRegs;
    UInt32 idx;

    if ((pStatus == NULL) || (pPrm == NULL))
    {
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));

        pCreateArgs = &pObj->createPrms;

        if (pPrm->deviceNum >= pCreateArgs->numDevicesAtPort)
        {
            status = FVID2_EBADARGS;
        }
    }
    if (status == FVID2_SOK)
    {
        numRegs = 0;

        regAddr[numRegs]  = BSP_OV1063X_CHIP_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV1063X_CHIP_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV1063X_MAN_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV1063X_MAN_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        status = Bsp_deviceRead16(pCreateArgs->deviceI2cInstId,
                                  pCreateArgs->deviceI2cAddr[0],
                                  regAddr,
                                  regValue,
                                  numRegs);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        for (idx = 0; idx < numRegs; idx++)
        {
            regValue[idx] = regValue[idx] & 0x00FFU;
        }

        pStatus->chipId          = ((UInt32) regValue[0] << 8) | regValue[1];
        pStatus->chipRevision    = 0;
        pStatus->firmwareVersion = ((UInt32) regValue[2] << 8) | regValue[3];
    }

    return status;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov1063xRegWrite(Bsp_Ov1063xHandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;
        status      = Bsp_deviceWrite16_Custom(pCreatePrms->deviceI2cInstId,
                                               pCreatePrms->deviceI2cAddr[0],
                                               pPrm->regAddr,
                                               pPrm->regValue16,
                                               pPrm->numRegs);
    }

    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov1063xRegRead(Bsp_Ov1063xHandleObj       *pObj,
                         Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;
        status      = Bsp_deviceRead16_Custom(pCreatePrms->deviceI2cInstId,
                                              pCreatePrms->deviceI2cAddr[0],
                                              pPrm->regAddr,
                                              pPrm->regValue16,
                                              pPrm->numRegs);
    }

    return (status);
}

Int32 Bsp_ov1063xSensorStartStop(const Bsp_Ov1063xHandleObj *pObj,
                                 UInt32                      bStartSensor)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegValue[3];
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        /* MSB of address 0x0100 */
        nRegValue[0] = (UInt8) ((UInt16) ((BSP_OV1063X_OPERATING_MODE_REG) &
                                           0xFFFFU) >> 8);
        /* LSB of address 0x0100 */
        nRegValue[1] = (UInt8) ((BSP_OV1063X_OPERATING_MODE_REG) & 0x00FFU);

        if ((UInt32) TRUE == bStartSensor)
        {
            nRegValue[2] = 0x01U;
        }
        else
        {
            nRegValue[2] = 0x00;
        }
        numRegs = 3U;

        status = Bsp_deviceRawWrite8(nI2cInstId,
                                     nDeviceAddr,
                                     nRegValue,
                                     numRegs);
        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return status;
}

/* OV1063x Sensor Software reset  */
Int32 Bsp_ov1063xSoftwareReset(const Bsp_Ov1063xHandleObj *pObj)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegValue[3];
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt16 nRegAddr16;
    UInt16 nRegValue16;
    UInt32 numRegs, delay;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        /* MSB of address 0x0103 */
        nRegValue[0] = (UInt8) ((UInt16) ((BSP_OV1063X_SOFTWARE_RESET_REG) &
                                           0xFFFFU) >> 8);
        /* LSB of address 0x0103 */
        nRegValue[1] = (UInt8) ((BSP_OV1063X_SOFTWARE_RESET_REG) & 0x00FFU);
        /* Reset value 0x01 */
        nRegValue[2] = 0x01U;
        numRegs      = 3U;
        status       = Bsp_deviceRawWrite8(nI2cInstId,
                                           nDeviceAddr,
                                           nRegValue,
                                           numRegs);
        if (status == FVID2_SOK)
        {
            nRegAddr16 = BSP_OV1063X_SOFTWARE_RESET_REG;
            do
            {
                numRegs = 1U;
                status  = Bsp_deviceRead16(nI2cInstId,
                                           nDeviceAddr,
                                           &nRegAddr16,
                                           &nRegValue16,
                                           numRegs);
                if (status != FVID2_SOK)
                {
                    status = FVID2_ETIMEOUT;
                    break;
                }
                delay = 1U;
                BspOsal_sleep(delay);
            } while (nRegValue16 != 0);
        }
        else
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return status;
}

Int32 Bsp_ov1063xGetSensorFeatures(const Bsp_Ov1063xHandleObj *pObj,
                                   Bsp_VidSensorFeatures      *pSenFeature)
{
    Int32  status = FVID2_SOK;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    UInt32 numRegs;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 idx;

    if ((pObj == NULL) || (pSenFeature == NULL))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(pSenFeature, &gBspOv1063xSensorFeatures,
                        sizeof (Bsp_VidSensorFeatures));

        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        numRegs     = 0;

        regAddr[numRegs]  = BSP_OV1063X_CHIP_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV1063X_CHIP_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV1063X_MAN_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV1063X_MAN_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        status = Bsp_deviceRead16(nI2cInstId,
                                  nDeviceAddr,
                                  regAddr,
                                  regValue,
                                  numRegs);

        if (status == FVID2_SOK)
        {
            for (idx = 0; idx < numRegs; idx++)
            {
                regValue[idx] = regValue[idx] & 0x00FFU;
            }

            pSenFeature->chipId = ((UInt32) regValue[0] << 8) |
                                  regValue[1];
            pSenFeature->chipRevision    = 0;
            pSenFeature->firmwareVersion = ((UInt32) regValue[2] << 8) |
                                           regValue[3];

            if ((regValue[0] == BSP_VID_SENSOR_OV10635_PID_MSB) &&
                (regValue[1] == BSP_VID_SENSOR_OV10635_PID_LSB))
            {
                pSenFeature->sensorId = BSP_VID_SENSOR_OV10635;
            }
            if ((regValue[0] == BSP_VID_SENSOR_OV10630_PID_MSB) &&
                (regValue[1] == BSP_VID_SENSOR_OV10630_PID_LSB))
            {
                pSenFeature->sensorId = BSP_VID_SENSOR_OV10630;
            }
        }
        else
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return (status);
}

/* OV1063x Sensor Config  */
Int32 Bsp_ov1063xSensorConfig(
    const Bsp_Ov1063xHandleObj *pObj,
    Bsp_VidSensorConfigRegs    *sensorConfig,
    UInt32
    numSensorConfigEntries)
{
    Bsp_VidSensorConfigRegs *sensorConfiguration = NULL;
    UInt16 nAddr;
    UInt8  nRegValue[5];
    UInt32 nValue, nMask;
    UInt32 nIndex, nArraySize;
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 regValue;
    UInt32 numRegs;

    /* Check for sensor configuration to be used */
    if (sensorConfig != NULL)
    {
        /* User provided configuration  */
        sensorConfiguration = (Bsp_VidSensorConfigRegs *) sensorConfig;
        nArraySize          = numSensorConfigEntries;
    }
    else
    {
        if ((pObj->nDrvId == FVID2_VID_SENSOR_OV1063X_DRV) ||
            (pObj->nDrvId == FVID2_VID_SENSOR_LI_OV1063X_DRV))
        {
            /* Use the default configuration if user has passed NULL */
            sensorConfiguration =
                (Bsp_VidSensorConfigRegs *) gBsp_Ov1063xSensorsDefault;

            nArraySize =
                (sizeof (gBsp_Ov1063xSensorsDefault) /
                 sizeof (gBsp_Ov1063xSensorsDefault[0]));
        }
        else if (pObj->nDrvId == FVID2_VID_SENSOR_MULDES_OV1063X_DRV)
        {
            /* Default configuration for LVDS OV is different */
            sensorConfiguration =
                (Bsp_VidSensorConfigRegs *) gBsp_Ov1063xLvdsSensorsDefault;

            nArraySize =
                (sizeof (gBsp_Ov1063xLvdsSensorsDefault) /
                 sizeof (gBsp_Ov1063xLvdsSensorsDefault[0]));
        }
        else
        {
            status = FVID2_EBADARGS;
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid Driver ID!!\r\n");
        }
    }

    nI2cInstId  = pObj->createPrms.deviceI2cInstId;
    nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

    if (FVID2_SOK == status)
    {
        for (nIndex = 0; nIndex < nArraySize; nIndex++)
        {
            /* For OV/LI sensor the address is 16-bit long */
            nAddr = sensorConfiguration[nIndex].regAddr & (UInt16) 0xFFFFU;

            /* SC_CMMN_SCCB_ID register => Bit[7:1] is slave address of the
             * sensor and Bit[0] is 1
             * slave address of the sensor for OV(0x30) and LI sensor(0x37) is
             * different */
            if ((nAddr == 0x300CU) &&
                (pObj->nDrvId == FVID2_VID_SENSOR_LI_OV1063X_DRV))
            {
                /* For LI/OV sensor the value is 8-bit long */
                nValue = (((pObj->createPrms.deviceI2cAddr[0] << (UInt32) 1U) |
                           (UInt32) 0x1U) & (UInt32) 0x00FFU);
            }
            else
            {
                /* For LI/OV sensor the value is 8-bit long */
                nValue = ((UInt32) sensorConfiguration[nIndex].regValue &
                          0x00FFU);
            }

            /* For OV sensor the mask is 8-bit long */
            nMask = ((UInt32) sensorConfiguration[nIndex].regMask & 0x00FFU);

            /* MSB of the address */
            nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
            /* LSB of the address */
            nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
            /* Data */

            if (nMask != 0)
            {
                regValue     = ((nValue & 0xFFU) & nMask);
                nRegValue[2] = (UInt8) (regValue);
            }
            else
            {
                regValue     = (nValue & 0xFFU);
                nRegValue[2] = (UInt8) (regValue);
            }
            numRegs = 3U;
            status  = Bsp_deviceRawWrite8(nI2cInstId,
                                          nDeviceAddr,
                                          nRegValue,
                                          numRegs);
        }
    }

    return (status);
}

Int32 Bsp_ov1063xSetFlipParams(const Bsp_Ov1063xHandleObj    *pObj,
                               const Bsp_VidSensorFlipParams *pPrm)
{
    UInt8  nRegValue[5];
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;
    UInt16 nAddr, nValue;

    nI2cInstId  = pObj->createPrms.deviceI2cInstId;
    nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
    numRegs     = 3U;

    nAddr  = (UInt16) 0x381D;
    nValue = (UInt16) 0x40;
    if (pPrm->hFlip)
    {
        nValue |= (UInt16) 0x3; /* enable H flip in sensor */
    }

    /* MSB of the address */
    nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
    /* LSB of the address */
    nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
    /* Data */
    nRegValue[2] = (UInt8) (nValue);

    status += Bsp_deviceRawWrite8(nI2cInstId,
                                  nDeviceAddr,
                                  nRegValue,
                                  numRegs);

    nAddr  = (UInt16) 0x381C;
    nValue = 0;
    if (pPrm->vFlip)
    {
        nValue |= (UInt16) (((UInt16) 0x3) << 6); /* enable V flip in sensor */
    }

    /* MSB of the address */
    nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
    /* LSB of the address */
    nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
    /* Data */
    nRegValue[2] = (UInt8) (nValue);

    status += Bsp_deviceRawWrite8(nI2cInstId,
                                  nDeviceAddr,
                                  nRegValue,
                                  numRegs);

    nAddr  = (UInt16) 0x6900;
    nValue = (UInt16) 0xC;
    if (pPrm->hFlip)
    {
        nValue |= (UInt16) (1); /* when hFlip is ON,
                                 * this bit needs to be set
                                 * to get correct colors
                                 */
    }

    /* MSB of the address */
    nRegValue[0] = (UInt8) ((UInt16) (nAddr & 0xFFFFU) >> 8);
    /* LSB of the address */
    nRegValue[1] = (UInt8) (nAddr & 0x00FFU);
    /* Data */
    nRegValue[2] = (UInt8) (nValue);

    status += Bsp_deviceRawWrite8(nI2cInstId,
                                  nDeviceAddr,
                                  nRegValue,
                                  numRegs);

    return status;
}

Int32 Bsp_ov1063xSetConfig(Bsp_Ov1063xHandleObj            *pObj,
                           const Bsp_VidSensorConfigParams *configParams)
{
    Int32  status = FVID2_SOK;
    UInt32 width;
    UInt32 height;
    UInt32 idx      = 0U;
    UInt32 regCount = 0U;
    UInt32 addrStartY, addrEndY;
    UInt32 ispStartX, ispStartY;
    UInt32 VTS, HTSmin;
    UInt32 horOffset, verOffset;
    UInt32 horSubSampling, verSubSampling;
    UInt32 noRowReadOut, noColReadOut;
    UInt32 horCrop     = 0U;
    UInt32 preDivider  = 3U;
    UInt32 multiplier  = 40U;
    UInt32 sClkDivider = 1U;
    UInt32 sysClk;
    UInt32 minHorBlanking;
    UInt32 minVerBlanking;
    UInt32 analogTiming1, analogTiming2, analogTiming3;
    Bsp_VidSensorConfigRegs sensorConfigReg[50];

    if ((pObj == NULL) || (configParams == NULL))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (status == FVID2_SOK)
    {
        if (pObj->nDrvId == FVID2_VID_SENSOR_MULDES_OV1063X_DRV)
        {
            /* For MULDES_OV1063X this IOCTL is not Implemented yet,
             * Create it self will set it to 720x480 resolution.
             * For now will return SUCCESS */
            status = FVID2_SOK;
            if ((FVID2_DF_YUV422I_YUYV == configParams->dataformat) ||
                (FVID2_DF_YUV422I_UYVY == configParams->dataformat))
            {
                UInt8 nRegValue[4U];
                UInt32 tempRegValue;

                tempRegValue = ((BSP_OV1063X_FORMAT_CONTROL_REG >> 8U) & 0xFFU);
                nRegValue[regCount] = (UInt8) tempRegValue;
                regCount++;
                tempRegValue = (BSP_OV1063X_FORMAT_CONTROL_REG & 0xFFU);
                nRegValue[regCount] = (UInt8) tempRegValue;
                regCount++;

                if (FVID2_DF_YUV422I_YUYV == configParams->dataformat)
                {
                    nRegValue[regCount] = 0x38U;
                }
                else
                {   /* Otherwise FVID2_DF_YUV422I_UYVY */
                    nRegValue[regCount] = 0x3AU;
                }
                regCount++;

                status = Bsp_deviceRawWrite8(pObj->createPrms.deviceI2cInstId,
                                          pObj->createPrms.deviceI2cAddr[0],
                                          nRegValue,
                                          regCount);
            }
        }
    }
    if ((status == FVID2_SOK) &&
        (pObj->nDrvId != FVID2_VID_SENSOR_MULDES_OV1063X_DRV))
    {
        pObj->sensorConfig = *configParams;

        for (idx = 0; idx < (sizeof (nResMapping) / sizeof (nResMapping[0]));
             idx++)
        {
            if (configParams->standard == nResMapping[idx][0])
            {
                width  = nResMapping[idx][1];
                height = nResMapping[idx][2];
                break;
            }
        }

        if (idx == (sizeof (nResMapping) / sizeof (nResMapping[0])))
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Unsupported standard passed as argument \r\n");
            status = FVID2_EBADARGS;
        }
    }
    if ((status == FVID2_SOK) &&
        (pObj->nDrvId != FVID2_VID_SENSOR_MULDES_OV1063X_DRV))
    {
        for (idx = 0; idx <
             (sizeof (nRestoPllMapping) / sizeof (nRestoPllMapping[0])); idx++)
        {
            if ((configParams->standard == nRestoPllMapping[idx][0]) &&
                (configParams->fps == nRestoPllMapping[idx][1]))
            {
                preDivider  = nRestoPllMapping[idx][2];
                multiplier  = nRestoPllMapping[idx][3];
                sClkDivider = nRestoPllMapping[idx][4];
                break;
            }
        }

        if (preDivider != 0)
        {
            sysClk = (((UInt32) BSP_OV1063X_X_CLK / preDivider) * multiplier)
                     / ((UInt32) 2U * (1U + sClkDivider));
        }
        else
        {
            sysClk = (((UInt32) BSP_OV1063X_X_CLK) * multiplier) /
                     ((UInt32) 2U * (1U + sClkDivider));
        }

        analogTiming1 = sysClk / (3U * 1000000U);
        analogTiming2 = (sysClk * 3U) / (4U * 1000000U);
        analogTiming3 = (sysClk / 2U) / 1000000U;

        horSubSampling = (width <=
                          (BSP_OV1063X_ACTIVE_PIXELS_H / 2U)) ?
                         2U : 1U;
        verSubSampling = (height <=
                          (BSP_OV1063X_ACTIVE_PIXELS_V / 2U)) ?
                         2U : 1U;

        /* OV1063x only support three horizontal crop 1312, 768, 656 */
        if ((width * horSubSampling) > (BSP_OV1063X_HOR_CROP_1))
        {
            noColReadOut = BSP_OV1063X_HOR_CROP_0;
        }
        else if ((width * horSubSampling) > (BSP_OV1063X_HOR_CROP_2))
        {
            noColReadOut = BSP_OV1063X_HOR_CROP_1;
        }
        else
        {
            noColReadOut = BSP_OV1063X_HOR_CROP_2;
        }

        noRowReadOut = height * verSubSampling;

        horOffset = (noColReadOut - (width * horSubSampling)) / 2U;
        verOffset =
            ((UInt32) BSP_VID_SENSOR_OV1063X_MAX_LINES_OUTPUT - (height *
                                                                 verSubSampling))
            / 2U;

        ispStartX = (horOffset / 2U) * 2U;
        ispStartY = 2U;

        addrStartY = ((verOffset / 2U) * 2U) - 2U;
        if (verSubSampling > 1U)
        {
            addrEndY = (addrStartY +
                        ((BSP_VID_SENSOR_OV1063X_DUMMY_LINES_BOTTOM +
                          BSP_VID_SENSOR_OV1063X_DUMMY_LINES_TOP) * 2U)
                        + ((noRowReadOut + ispStartY) - 1U));
        }
        else
        {
            addrEndY = (addrStartY +
                        (BSP_VID_SENSOR_OV1063X_DUMMY_LINES_BOTTOM +
                         BSP_VID_SENSOR_OV1063X_DUMMY_LINES_TOP)
                        + ((noRowReadOut + ispStartY) - 1U));
        }

        minHorBlanking = (analogTiming1 + (4U * analogTiming2) +
                          (2U * analogTiming3) + 120U);

        HTSmin = noColReadOut + minHorBlanking;

        if (verSubSampling == 1U)
        {
            /*17820 is a constant provided by Omnivision for VTS calculations */
            minVerBlanking =
                (((UInt32) BSP_OV1063X_VTS_CONST + (12U * HTSmin)) /
                 HTSmin);
        }
        else
        {
            /*17820 is a constant provided by Omnivision for VTS calculations */
            minVerBlanking =
                (((UInt32) BSP_OV1063X_VTS_CONST + (18U * HTSmin)) /
                 HTSmin);
        }

        VTS = minVerBlanking + noRowReadOut;

        /* Observed flickers without the below changes, below one is applicable
         * only
         * for 720P resolution. */
        VTS    = VTS + 6U;
        HTSmin = HTSmin + 4U;

        for (idx = 0; idx <
             (sizeof (nHCropMapping) / sizeof (nHCropMapping[0])); idx++)
        {
            if (noColReadOut == nHCropMapping[idx][0])
            {
                horCrop = nHCropMapping[idx][1];
                break;
            }
        }

        regCount = 0;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_FIFO_RESET_REG;
        sensorConfigReg[regCount].regValue = 0xFF;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_FIFO_RESET_REG_2;
        sensorConfigReg[regCount].regValue = 0xFF;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_FIFO_RESET_REG_1;
        sensorConfigReg[regCount].regValue = 0xFF;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Configure Sensor output interface width(8 or 10 bit) */
        regCount++;
        sensorConfigReg[regCount].regAddr = BSP_OV1063X_INTERFACE_WIDTH_REG;
        switch (configParams->videoIfWidth)
        {
            case FVID2_VIFW_8BIT:
                sensorConfigReg[regCount].regValue = 0x08;
                break;
            case FVID2_VIFW_10BIT:
                sensorConfigReg[regCount].regValue = 0x00;
                break;
            default:
                GT_0trace(
                    BspDeviceTrace, GT_ERR,
                    "Unsupported interface width using 8 BIT as default\r\n");
                sensorConfigReg[regCount].regValue = 0x08;
                break;
        }
        sensorConfigReg[regCount].regMask = 0x00;

        /* Configure YUV422 output format */
        regCount++;
        sensorConfigReg[regCount].regAddr = BSP_OV1063X_FORMAT_CONTROL_REG;
        switch (configParams->dataformat)
        {
            case FVID2_DF_YUV422I_YUYV:
                sensorConfigReg[regCount].regValue = 0x38;
                break;
            case FVID2_DF_YUV422I_YVYU:
                sensorConfigReg[regCount].regValue = 0x39;
                break;
            case FVID2_DF_YUV422I_UYVY:
                sensorConfigReg[regCount].regValue = 0x3A;
                break;
            case FVID2_DF_YUV422I_VYUY:
                sensorConfigReg[regCount].regValue = 0x3B;
                break;
            default:
                GT_0trace(
                    BspDeviceTrace, GT_ERR,
                    "Unsupported dataformat,using default as YUYV format\r\n");
                sensorConfigReg[regCount].regValue = 0x38;
                break;
        }
        sensorConfigReg[regCount].regMask = 0x00;

        /* Configure PLL multiplier */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_PLL_MULTIPLIER_REG;
        sensorConfigReg[regCount].regValue = multiplier;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Configure PLL dividers */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            (UInt32) BSP_OV1063X_PLL_DIVIDER_REG;
        sensorConfigReg[regCount].regValue = (preDivider << 4U) +
                                             sClkDivider;

        sensorConfigReg[regCount].regMask = 0x0;

        /* Disable secondary PLL */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_PCLK_PLL_DISABLE_REG;
        sensorConfigReg[regCount].regValue = 0x01;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Set Horizontal crop */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_Horizontal_CROP_REG;
        sensorConfigReg[regCount].regValue = 0x63U + horCrop;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Setting these values is causing output to be of red color, basically
         * the
         * color balance is goofed up - Using default values for now */
        #if 0
        /* Configure Analog timing 1 */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_ANALOG1_TIMING_CTRL_REG;
        sensorConfigReg[regCount].regValue = analogTiming1;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Configure Analog timing 2 */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_ANALOG2_TIMING_CTRL_REG;
        sensorConfigReg[regCount].regValue = analogTiming2 + 1;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Configure Analog timing 3 */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_ANALOG3_TIMING_CTRL_REG;
        sensorConfigReg[regCount].regValue = analogTiming3 + 1;
        sensorConfigReg[regCount].regMask  = 0x0;
        #endif

        /* Y start address/ Vertical crop start */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_VS_Y_ADDR_START_UPPER_REG;
        sensorConfigReg[regCount].regValue = addrStartY / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_VS_Y_ADDR_START_LOWER_REG;
        sensorConfigReg[regCount].regValue = addrStartY % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Y end address / Vertical crop end */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_VH_Y_ADDR_END_UPPER_REG;
        sensorConfigReg[regCount].regValue = addrEndY / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_VH_Y_ADDR_END_LOWER_REG;
        sensorConfigReg[regCount].regValue = addrEndY % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* DVP Horizontal output size */
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_DVPHO_HORZ_WIDTH_UPPER_REG;
        sensorConfigReg[regCount].regValue = width / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_DVPHO_HORZ_WIDTH_LOWER_REG;
        sensorConfigReg[regCount].regValue = width % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* DVP Vertical output size */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_TIMING_DVPO_UPPER_REG;
        sensorConfigReg[regCount].regValue = height / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_TIMING_DVPO_LOWER_REG;
        sensorConfigReg[regCount].regValue = height % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Line period in unit of pixel period */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_TIMING_HTS_UPPER_REG;
        sensorConfigReg[regCount].regValue = HTSmin / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_TIMING_HTS_LOWER_REG;
        sensorConfigReg[regCount].regValue = HTSmin % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Frame period in unit of Line period */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_TIMING_VTS_UPPER_REG;
        sensorConfigReg[regCount].regValue = VTS / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_TIMING_VTS_LOWER_REG;
        sensorConfigReg[regCount].regValue = VTS % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Horizontal offset of ISP*/
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_HOFFSET_UPPER_REG;
        sensorConfigReg[regCount].regValue = ispStartX / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_HOFFSET_LOWER_REG;
        sensorConfigReg[regCount].regValue = ispStartX % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Vertical offset of ISP*/
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_VOFFSET_UPPER_REG;
        sensorConfigReg[regCount].regValue = ispStartY / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_TIMING_VOFFSET_LOWER_REG;
        sensorConfigReg[regCount].regValue = ispStartY % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Vertical Sub-Sampling*/
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_VER_SUBSAMPLING_ENABLE_REG;
        sensorConfigReg[regCount].regValue = (verSubSampling > 1U) ? 1U : 0;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Horizontal Sub-Sampling*/
        regCount++;
        sensorConfigReg[regCount].regAddr =
            BSP_OV1063X_HOR_SUBSAMPLING_ENABLE_REG;
        sensorConfigReg[regCount].regValue = 0x08 + ((horSubSampling > 1U) ?
                                                     1U : 0);
        sensorConfigReg[regCount].regMask = 0x0;

        /* VTS*/
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_VTS_UPPER_REG;
        sensorConfigReg[regCount].regValue = VTS / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_VTS_LOWER_REG;
        sensorConfigReg[regCount].regValue = VTS % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* HTS*/
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_HTS_UPPER_REG;
        sensorConfigReg[regCount].regValue = HTSmin / 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_HTS_LOWER_REG;
        sensorConfigReg[regCount].regValue = HTSmin % 256U;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Reset FIFO */
        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_FIFO_RESET_REG;
        sensorConfigReg[regCount].regValue = 0xF0;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_FIFO_RESET_REG_2;
        sensorConfigReg[regCount].regValue = 0xF0;
        sensorConfigReg[regCount].regMask  = 0x0;

        regCount++;
        sensorConfigReg[regCount].regAddr  = BSP_OV1063X_FIFO_RESET_REG_1;
        sensorConfigReg[regCount].regValue = 0xF0;
        sensorConfigReg[regCount].regMask  = 0x0;

        /* Total number of registers = array index + 1 */
        regCount = regCount + 1U;
        status   = Bsp_ov1063xSensorConfig(
            pObj,
            &sensorConfigReg[0],
            regCount);
    }
    return status;
}

