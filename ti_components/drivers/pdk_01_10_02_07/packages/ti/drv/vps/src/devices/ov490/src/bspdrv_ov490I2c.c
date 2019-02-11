/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file bspdrv_ov490I2c.c
 *
 *  \brief OV490 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov490/src/bspdrv_ov490Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Bsp_VidSensorConfigRegs gBsp_Ov490SensorsDefault[BSP_OV490_NUM_REGS];

static const Bsp_VidSensorFeatures gBspOv490SensorFeatures =
{
    0,                          /* SensorId */
    0U,                         /* Chip Id, read from register */
    0U,                         /* Revision Id, read from register */
    0U,                         /* firmware version, read from register */
    FVID2_DF_BAYER_BGGR,        /* Bayer format */
    BSP_OV490_ACTIVE_PIXELS_H,  /* Active Width */
    BSP_OV490_ACTIVE_PIXELS_V,  /* Active Height */
    TRUE,                       /* isEmbededDataSupported */
    TRUE,                       /* isManualExposureSupported */
    FALSE,                      /* isEepromDataSupported */
    TRUE,                       /* isSoftStandbySupported */
    TRUE,                       /* isFlipSupported */
    FALSE,                      /* isManualAnalogGainSupported */
    FALSE,                      /* isWdrModeSupported */
    FALSE,                      /* isSetCfgSupported */
    FALSE,                      /* isDccCfgSupported */
    FALSE                       /* isOnePassWdrSupported */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov490I2cWrite32(const Bsp_Ov490HandleObj  *pObj,
                          UInt32                    addr,
                          UInt8                     val)
{
    Int32 status = FVID2_SOK;
    UInt16 regAddr;
    UInt32 tempVal;
    UInt8 bankHigh;
    UInt8 bankLow;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    tempVal = (addr >> 24U) & 0xffU;
    bankHigh = (UInt8) tempVal;
    tempVal = (addr >> 16U) & 0xffU;
    bankLow  = (UInt8) tempVal;

    /* High bank */
    regAddr = BSP_OV490_BANK_HIGH;
    status  = Bsp_deviceWrite_Custom_16A8D(pObj->createPrms.deviceI2cInstId,
                                           pObj->createPrms.deviceI2cAddr[0],
                                           &regAddr,
                                           &bankHigh,
                                           1U);

    if (FVID2_SOK == status)
    {
        /* Low Bank */
        regAddr = BSP_OV490_BANK_LOW;
        status  = Bsp_deviceWrite_Custom_16A8D(pObj->createPrms.deviceI2cInstId,
                                               pObj->createPrms.deviceI2cAddr[0],
                                               &regAddr,
                                               &bankLow,
                                               1U);
    }

    if (FVID2_SOK == status)
    {
        /* Actual Value */
        tempVal = addr & 0xffffU;
        regAddr = (UInt16) (tempVal);
        status  = Bsp_deviceWrite_Custom_16A8D(pObj->createPrms.deviceI2cInstId,
                                               pObj->createPrms.deviceI2cAddr[0],
                                               &regAddr,
                                               &val,
                                               1U);
    }

    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov490I2cRead32(const Bsp_Ov490HandleObj   *pObj,
                         UInt32                     addr,
                         UInt8                      *val)
{
    Int32 status = FVID2_SOK;
    UInt16 regAddr;
    UInt32 tempVal;
    UInt8 bankHigh;
    UInt8 bankLow;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if (NULL == val)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        tempVal  = (addr >> 24U) & 0xffU;
        bankHigh = (UInt8) (tempVal);
        tempVal  = (addr >> 16U) & 0xffU;
        bankLow  = (UInt8) (tempVal);

        /* High bank */
        regAddr = BSP_OV490_BANK_HIGH;
        status  = Bsp_deviceWrite_Custom_16A8D(pObj->createPrms.deviceI2cInstId,
                                               pObj->createPrms.deviceI2cAddr[0],
                                               &regAddr,
                                               &bankHigh,
                                               1U);
    }

    if (FVID2_SOK == status)
    {
        /* Low Bank */
        regAddr = BSP_OV490_BANK_LOW;
        status  = Bsp_deviceWrite_Custom_16A8D(pObj->createPrms.deviceI2cInstId,
                                               pObj->createPrms.deviceI2cAddr[0],
                                               &regAddr,
                                               &bankLow,
                                               1U);
    }

    if (FVID2_SOK == status)
    {
        /* Actual Value */
        tempVal = addr & 0xffffU;
        regAddr = (UInt16) (tempVal);
        status = Bsp_deviceReadAddr16Data8(pObj->createPrms.deviceI2cInstId,
                                           pObj->createPrms.deviceI2cAddr[0],
                                           &regAddr,
                                           val,
                                           1U);
    }

    return (status);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov490RegWrite(const Bsp_Ov490HandleObj            *pObj,
                        const Bsp_VidSensorRegRdWrParams    *pPrm)
{
    Int32 status = FVID2_SOK;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        status = Bsp_deviceWrite_Custom_16A8D(pObj->createPrms.deviceI2cInstId,
                                              pObj->createPrms.deviceI2cAddr[0],
                                              pPrm->regAddr,
                                              pPrm->regValue8,
                                              pPrm->numRegs);
    }

    return (status);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov490RegWrite32(const Bsp_Ov490HandleObj          *pObj,
                          const Bsp_VidSensorRegRdWrParams  *pPrm)
{
    Int32 status = FVID2_SOK;
    UInt32 i;
    UInt32 regAddr;
    UInt32 tempVal;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (1U == (pPrm->numRegs%2U)) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    for (i = 0; (FVID2_SOK == status) && (i < pPrm->numRegs); i++)
    {
        /* High bank */
        tempVal = ((UInt32) pPrm->regAddr[i]) << 16U;
        regAddr = tempVal & ((UInt32) pPrm->regAddr[i + 1U]);
        status  = Bsp_ov490I2cWrite32(pObj, regAddr, pPrm->regValue8[i]);
    }

    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov490RegRead(const Bsp_Ov490HandleObj     *pObj,
                       const Bsp_VidSensorRegRdWrParams   *pPrm)
{
    Int32 status = FVID2_SOK;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        status      = Bsp_deviceReadAddr16Data8(pObj->createPrms.deviceI2cInstId,
                                                pObj->createPrms.deviceI2cAddr[0],
                                                pPrm->regAddr,
                                                pPrm->regValue8,
                                                pPrm->numRegs);
    }

    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov490RegRead32(const Bsp_Ov490HandleObj   *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    UInt32 i;
    UInt32 regAddr;
    UInt32 tempVal;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (1U == (pPrm->numRegs%2U)) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\r\n");
        status = FVID2_EBADARGS;
    }

    for (i = 0; (FVID2_SOK == status) && (i < pPrm->numRegs); i++)
    {
        /* High bank */
        tempVal = (UInt32)(pPrm->regAddr[i]) << 16U;
        regAddr = tempVal & ((UInt32)pPrm->regAddr[i + 1U]);
        status  = Bsp_ov490I2cRead32(pObj, regAddr, &pPrm->regValue8[i]);
    }

    return (status);
}

/*
 * Get OV490 chip ID and Manufacturer ID
 */
Int32 Bsp_ov490GetChipId(const Bsp_Ov490HandleObj           *pObj,
                         Bsp_VidSensorChipIdStatus          *pStatus)
{
    Int32  status = FVID2_SOK;
    UInt8 regValue[4];

    if (pStatus == NULL)
    {
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));
    }
    if (status == FVID2_SOK)
    {
        status = Bsp_ov490I2cRead32(pObj, BSP_OV490_PID, &regValue[0]);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        status = Bsp_ov490I2cRead32(pObj, BSP_OV490_VER, &regValue[1]);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        status = Bsp_ov490I2cRead32(pObj, BSP_OV490_MAN_HIGH, &regValue[2]);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        status = Bsp_ov490I2cRead32(pObj, BSP_OV490_MAN_LOW, &regValue[3]);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        pStatus->chipId = (UInt32) BSP_OV490_VERSION(((UInt32) regValue[0]), ((UInt32) regValue[1]));
        pStatus->chipRevision = 0;
        pStatus->firmwareVersion = (UInt32) ((((UInt32) regValue[2]) << 8U) | (((UInt32) regValue[3]) & 0xffU));
    }

    return status;
}

Int32 Bsp_ov490SensorStartStop(const Bsp_Ov490HandleObj *pObj,
                               UInt32                   bStartSensor)
{
    Int32  status = FVID2_SOK;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    return status;
}

/* OV490 Sensor Software reset  */
Int32 Bsp_ov490SoftwareReset(const Bsp_Ov490HandleObj *pObj)
{
    Int32  status = FVID2_SOK;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    /* Software reset unsupported */

    return status;
}

Int32 Bsp_ov490GetSensorFeatures(const Bsp_Ov490HandleObj   *pObj,
                                 Bsp_VidSensorFeatures      *pSenFeature)
{
    Int32  status = FVID2_SOK;
    Bsp_VidSensorChipIdStatus pStatus;

    if ((pObj == NULL) || (pSenFeature == NULL))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(pSenFeature, &gBspOv490SensorFeatures,
                        sizeof (Bsp_VidSensorFeatures));

        status = Bsp_ov490GetChipId(pObj, &pStatus);

        if (status == FVID2_SOK)
        {
            pSenFeature->chipId          = pStatus.chipId;
            pSenFeature->chipRevision    = pStatus.chipRevision;
            pSenFeature->firmwareVersion = pStatus.firmwareVersion;

            if (pStatus.chipId == BSP_OV490_VERSION_VAL) {
                pSenFeature->sensorId = BSP_VID_SENSOR_OV490;
            }
            else
            {
                GT_1trace(BspDeviceTrace,
                          GT_ERR,
                          "Incorrect version: %d !! \r\n",
                          pStatus.chipId);
                pSenFeature->sensorId = BSP_VID_SENSOR_MAX;
            }
        }
        else
        {
            status = FVID2_ETIMEOUT;
        }
    }

    return (status);
}

/* OV490 Sensor Config  */
Int32 Bsp_ov490SensorConfig(const Bsp_Ov490HandleObj    *pObj,
                            Bsp_VidSensorConfigRegs     *sensorConfig,
                            UInt32                      numSensorConfigEntries)
{
    Bsp_VidSensorConfigRegs *sensorConfiguration = NULL;
    UInt32 nIndex, nArraySize;
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt16 nAddr;
    UInt8 nValue, nMask;
    UInt8 nRegValue;

    if ((pObj->nDrvId != FVID2_VID_SENSOR_OV490_DRV) &&
        (pObj->nDrvId != FVID2_VID_SENSOR_MULDES_OV490_DRV))
    {
        status = FVID2_EBADARGS;
        GT_0trace(BspDeviceTrace, GT_ERR, "Invalid Driver ID!!\r\n");
    } else {
        /* Check for sensor configuration to be used */
        if (sensorConfig != NULL)
        {
            /* User provided configuration  */
            sensorConfiguration = (Bsp_VidSensorConfigRegs *) sensorConfig;
            nArraySize          = numSensorConfigEntries;
        }
        else
        {
            /* Use the default configuration if user has passed NULL */
            sensorConfiguration =
                (Bsp_VidSensorConfigRegs *) gBsp_Ov490SensorsDefault;

            nArraySize =
                (sizeof (gBsp_Ov490SensorsDefault) /
                 sizeof (gBsp_Ov490SensorsDefault[0]));
        }

        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
    }

    if (FVID2_SOK == status)
    {
        for (nIndex = 0; nIndex < nArraySize; nIndex++)
        {
            nAddr = sensorConfiguration[nIndex].regAddr;
            nValue = (UInt8) (sensorConfiguration[nIndex].regValue & 0x00FFU);
            nMask = (UInt8) (sensorConfiguration[nIndex].regMask & 0x00FFU);

            if (nMask != 0)
            {
                nRegValue = ((nValue & 0xFFU) & nMask);
            }
            else
            {
                nRegValue = (nValue & 0xFFU);
            }
            status  = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                                   nDeviceAddr,
                                                   &nAddr,
                                                   &nRegValue,
                                                   1U);
        }
    }

    return (status);
}

Int32 Bsp_ov490SetConfig(const Bsp_Ov490HandleObj           *pObj,
                         const Bsp_VidSensorConfigParams    *configParams)
{
    Int32  status = FVID2_SOK;

    if ((pObj == NULL) || (configParams == NULL))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }
    return status;
}
