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
 *  \file bspdrv_ar0140I2c.c
 *
 *  \brief AR0140 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ar0140/src/bspdrv_ar0140Priv.h>
#include <ar0140/src/bspdrv_ar0140Dcc.h>
#include <ar0140/src/bspdrv_ar0140Dcc_1pass.h>
#include <ar0140/src/bspdrv_ar0140_default_setup.h>
#include <ar0140/src/bspdrv_ar0140Reg.h>
#include <ar0140/src/bspdrv_ar0140_1280x720_60fps_WDR.h>
#include <ar0140/src/bspdrv_ar0140_tida00262_1280x800_30fps_wdr.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Maximum Gains supported */
#define BSP_AR0140_ANALOG_MAX_GAIN  (57U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const UInt8  gBspDrvAr0140DccCfg[BSP_AR0140_DCC_CFG_NUM_ELEM] = BSP_DRV_AR0140DCC_CFG;
static const UInt8  gBspDrvAr0140DccCfg1[BSP_AR0140_1PASS_DCC_CFG_NUM_ELEM] = BSP_DRV_AR0140_1PASSDCC_CFG;

static Bsp_VidSensorConfigRegs gBsp_AR0140SensorsDefault[] = BSP_AR0140SENSORS_DEFAULT;
static Bsp_VidSensorConfigRegs gBsp_AR0140SensorsWdr[] = BSP_AR0140SENSORS_WDR;
static Bsp_VidSensorConfigRegs gBsp_AR0140SensorFrameSize1650X1450[] = \
 BSP_AR0140_1650X1450_SENSORS;

static UInt32 gBspVidSensorAr0140GainsTable[BSP_AR0140_ANALOG_MAX_GAIN][3] =
{
    {1000,  0x00, 0x0},
    {1062,  0x00, 0x1},
    {1125,  0x00, 0x2},
    {1187,  0x00, 0x3},
    {1250,  0x00, 0x4},
    {1312,  0x00, 0x5},
    {1375,  0x00, 0x6},
    {1250,  0x00, 0x7},
    {1437,  0x00, 0x8},
    {1562,  0x00, 0x9},
    {1625,  0x00, 0xa},
    {1687,  0x00, 0xb},
    {1750,  0x00, 0xc},
    {1812,  0x00, 0xd},
    {1875,  0x00, 0xe},
    {1937,  0x00, 0xf},

    {2000,  0x01, 0x0},
    {2125,  0x01, 0x1},
    {2250,  0x01, 0x2},
    {2375,  0x01, 0x3},
    {2500,  0x01, 0x4},
    {2625,  0x01, 0x5},
    {2750,  0x01, 0x6},
    {2875,  0x01, 0x7},
    {3000,  0x01, 0x8},
    {3125,  0x01, 0x9},
    {3250,  0x01, 0xa},
    {3375,  0x01, 0xb},
    {3500,  0x01, 0xc},
    {3625,  0x01, 0xd},
    {3750,  0x01, 0xe},
    {3875,  0x01, 0xf},

    {4000,  0x02, 0x0},
    {4250,  0x02, 0x1},
    {4500,  0x02, 0x2},
    {4750,  0x02, 0x3},
    {5000,  0x02, 0x4},
    {5250,  0x02, 0x5},
    {5500,  0x02, 0x6},
    {5750,  0x02, 0x7},
    {6000,  0x02, 0x8},
    {6250,  0x02, 0x9},
    {6500,  0x02, 0xa},
    {6750,  0x02, 0xb},
    {7000,  0x02, 0xc},
    {7250,  0x02, 0xd},
    {7500,  0x02, 0xe},
    {7750,  0x02, 0xf},

    {8000,  0x03, 0x0},
    {8500,  0x03, 0x1},
    {9000,  0x03, 0x2},
    {9500,  0x03, 0x3},
    {10000, 0x03, 0x4},
    {10500, 0x03, 0x5},
    {11000, 0x03, 0x6},
    {11500, 0x03, 0x7},
    {12000, 0x03, 0x8}
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_ar0140I2cReadReg(const Bsp_ar0140HandleObj *pObj,
                                  const UInt16              *regAddr,
                                  UInt16                    *regVal,
                                  UInt32                     numRegs);

/*
 * Get AR0140 chip ID and Manufacturer ID
 */
Int32 Bsp_ar0140GetChipId(Bsp_ar0140HandleObj             *pObj,
                          const Bsp_VidSensorChipIdParams *pPrm,
                          Bsp_VidSensorChipIdStatus       *pStatus)
{
    Int32  status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreateArgs;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    UInt32 numRegs;

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

        regAddr[numRegs]  = BSP_AR0140_CHIP_ID_REG;
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
        pStatus->chipId = regValue[0U];
    }
    return status;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ar0140RegWrite(Bsp_ar0140HandleObj              *pObj,
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
        status      = Bsp_deviceWrite16(pCreatePrms->deviceI2cInstId,
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
Int32 Bsp_ar0140RegRead(const Bsp_ar0140HandleObj        *pObj,
                        const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    UInt32 numRegs;

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
        for(numRegs = 0; ((numRegs < pPrm->numRegs) &&
                          (FVID2_SOK == status)); numRegs++)
        {
            status = Bsp_ar0140I2cReadReg(pObj,
                        &pPrm->regAddr[numRegs],
                        &pPrm->regValue16[numRegs],
                        1U);
        }
    }
    return (status);
}

Int32 Bsp_ar0140SensorStartStop(const Bsp_ar0140HandleObj *pObj,
                                UInt32                     bStartSensor)
{
    Int32 status = FVID2_SOK;
    UInt16 regAddr, regValue;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    regAddr = 0x301AU;
    if (TRUE == bStartSensor)
    {
        regValue = 0x10DCU;
    }
    else
    {
        regValue = 0x10D8U;
    }

    status = Bsp_deviceWrite16(pObj->createPrms.deviceI2cInstId,
                               pObj->createPrms.deviceI2cAddr[0],
                               &regAddr,
                               &regValue,
                               1U);

    BspOsal_sleep((UInt32) BSP_AR0140_SENSOR_DLY_IN_MS_AFTER_RESET);

    return (status);
}

/* AR0140 Sensor Software reset  */
Int32 Bsp_ar0140SoftwareReset(const Bsp_ar0140HandleObj *pObj)
{
    return FVID2_SOK;
}

/**
 *  \brief Set the Configuration
 */
Int32 Bsp_ar0140SensorSetConfig(
    Bsp_ar0140HandleObj             *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms)
{
    Int32  status = FVID2_SOK;
    UInt32 numRegs;
    Bsp_VidSensorConfigRegs *sensorRegs = NULL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != cfgPrms));

    if ((FVID2_VIFW_12BIT != cfgPrms->videoIfWidth) &&
        (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV != pObj->nDrvId))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        pObj->sensorConfig.videoIfWidth = cfgPrms->videoIfWidth;
    }

    /* Only two resolutions are supported */
    if (FVID2_STD_WXGA_30 != cfgPrms->standard)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (pObj->wdrEnable)
        {
            /* We have already set TIDA00262 default, set Linear mode now */
            sensorRegs = gBsp_AR0140SensorsWdr;
            numRegs    = (sizeof (gBsp_AR0140SensorsWdr) /
                          sizeof (gBsp_AR0140SensorsWdr[0]));

            status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);
        }
        else
        {
            /* Set the Linear mode settings */
            sensorRegs = gBsp_AR0140SensorsDefault;
            numRegs    = (sizeof (gBsp_AR0140SensorsDefault) /
                          sizeof (gBsp_AR0140SensorsDefault[0]));

            status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);
        }

        if ((FVID2_SOK == status) &&
            (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pObj->nDrvId))
        {
            sensorRegs = gBsp_AR0140SensorFrameSize1650X1450;
            numRegs    = (sizeof (gBsp_AR0140SensorFrameSize1650X1450) /
                          sizeof (gBsp_AR0140SensorFrameSize1650X1450[0]));

            status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);
        }

        if (FVID2_SOK == status)
        {
            pObj->sensorConfig.dataformat   = FVID2_DF_BAYER_GRBG;
            pObj->sensorConfig.standard     = FVID2_STD_WXGA_30;
            pObj->outputHeight              = 800U;
            pObj->sensorConfig.fps          = FVID2_FPS_30;
            pObj->sensorConfig.videoIfWidth = FVID2_VIFW_12BIT;
            pObj->sensorConfig.bpp          = FVID2_BPP_BITS12;

            /* Calculate Max Integration time */
            if (pObj->wdrEnable)
            {
                if ((BSP_AR0140_EXP_RATIO_MULTIPLIER *
                     BSP_AR0140_DEFAULT_EXP_RATIO) >
                    (pObj->outputHeight -
                     BSP_AR0140_COARD_INTG_TIME_FRAME_SUBTRACT))
                {
                    pObj->maxCoarseIntgTime =
                        pObj->outputHeight -
                        BSP_AR0140_COARD_INTG_TIME_FRAME_SUBTRACT;
                }
                else
                {
                    pObj->maxCoarseIntgTime =
                        BSP_AR0140_EXP_RATIO_MULTIPLIER *
                        BSP_AR0140_DEFAULT_EXP_RATIO;
                }
            }
            else
            {
                pObj->maxCoarseIntgTime = pObj->outputHeight - 1U;
            }
        }
    }

    /* Hard coding it as of now, need to read it from register,
     * Hard Coding since I2C read is not working properly */
    pObj->lineIntgTimeInMs = 22.22267f;
    pObj->pixIntgTimeInMs  = 0.0134f;

    return (status);
}

/* AR0140 Sensor Config  */
Int32 Bsp_ar0140SensorConfig(
    Bsp_ar0140HandleObj     *pObj,
    Bsp_VidSensorConfigRegs *sensorConfig,
    UInt32                   numSensorConfigEntries)
{
    Bsp_VidSensorConfigRegs *sensorConfiguration = NULL;
    UInt16 nAddr, nValue, nRead;
    UInt32 nIndex, nArraySize;
    Int32 status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;
    UInt32 mirrorMode_maskVal,flipMode_maskVal;
    volatile UInt32          wait;

    /* Check for sensor configuration to be used */
    if (sensorConfig != NULL)
    {
        /* User provided configuration  */
        sensorConfiguration = (Bsp_VidSensorConfigRegs *) sensorConfig;
        nArraySize          = numSensorConfigEntries;
    }
    else
    {
        if (pObj->nDrvId == FVID2_VID_SENSOR_APT_AR0140_DRV)
        {
            /* Use the default configuration if user has passed NULL */
            sensorConfiguration =
                (Bsp_VidSensorConfigRegs *) gBsp_AR0140SensorsDefault;

            nArraySize =
                (sizeof (gBsp_AR0140SensorsDefault) /
                 sizeof (gBsp_AR0140SensorsDefault[0]));
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
        for (nIndex = 0; ((FVID2_SOK == status) && (nIndex < nArraySize));
             nIndex++)
        {
            /* For AR0140 sensor the address is 16-bit long */
            nAddr = sensorConfiguration[nIndex].regAddr & (UInt16)0xFFFFU;

            /* For AR0140 sensor the value is 16-bit long */
            nValue = (sensorConfiguration[nIndex].regValue & (UInt16) 0xFFFFU);

            numRegs = 1U;

            /* Change the exposure ratio */
            if ((UInt16) 0x3082 == nAddr)
            {
                nValue &= ((UInt16) ~((UInt16) 0x000CU));
                if (BSP_AR0140_DEFAULT_EXP_RATIO == 32U)
                {
                    nValue |= (UInt16) (((UInt16) 0x3U) << 2);
                }
                else if (BSP_AR0140_DEFAULT_EXP_RATIO == 16U)
                {
                    nValue |= (UInt16) (((UInt16) 0x2U) << 2);
                }
                else if (BSP_AR0140_DEFAULT_EXP_RATIO == 8U)
                {
                    nValue |= (UInt16) (((UInt16) 0x1U) << 2);
                }
                else /* 4x exposure ration */
                {
                    nValue |= (UInt16) (((UInt16) 0x0U) << 2);
                }
            }

            /* READ_MODE - control vertical flip / horizontal mirror */
            if (0x3040U == nAddr)
            {
                mirrorMode_maskVal = BSP_AR0140_MIRROR_MODE_ENABLE_MASK;
                flipMode_maskVal = BSP_AR0140_FLIP_MODE_ENABLE_MASK;
                nValue &= ((UInt16) ~((uint16_t)mirrorMode_maskVal | (uint16_t)flipMode_maskVal));
                if (TRUE == pObj->flipPrms.hFlip)
                {
                    nValue |= ((uint16_t)mirrorMode_maskVal);
                }
                if (TRUE == pObj->flipPrms.vFlip)
                {
                    nValue |= ((uint16_t)flipMode_maskVal);
                }
            }

            if ((sensorConfiguration[nIndex].regMask == BSP_VID_SENSOR_DLY_REG_MASK) &&
                ((UInt16)BSP_VID_SENSOR_DLY_REG == nAddr))
            {
                BspOsal_sleep((UInt32) nValue);
            }
            else
            {
                status = Bsp_deviceWrite16(nI2cInstId,
                                           nDeviceAddr,
                                           &nAddr,
                                           &nValue,
                                           numRegs);

                if (0 != sensorConfiguration[nIndex].regMask)
                {
                    wait = (UInt32) 1000U * (UInt32) sensorConfiguration[nIndex].
                           regMask;
                    while (wait--)
                    {
                        ;
                    }
                }

                #if 1
                if (FVID2_SOK == status)
                {
                    status = Bsp_ar0140I2cReadReg(
                        pObj,
                        &nAddr,
                        &nRead,
                        numRegs);

                    /*GT_3trace(BspDeviceTrace, GT_ERR,
                     *  "Address 0x%x v 0x%x r 0x%x\r\n",
                     *  nAddr, nValue, nRead);*/
                }
                #endif
            }
        }

        /* Hard coding it as of now, need to read it from register,
         * Hard Coding since I2C read is not working properly */
        pObj->lineIntgTimeInMs = 22.22267f;
        pObj->pixIntgTimeInMs  = 0.0134f;
    }

    return (status);
}

Int32 Bsp_ar0140SetExpParams(const Bsp_ar0140HandleObj         *pObj,
                             const Bsp_VidSensorExposureParams *expPrms)
{

    Int32  status = FVID2_SOK;
    UInt16 nAddr, nValue;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    Float32 lineIntgTime;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == expPrms)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        nAddr = 0x3012U;

        lineIntgTime = expPrms->exposureTime / pObj->lineIntgTimeInMs;
        nValue       = (UInt16) lineIntgTime;

        /* For WDR mode, max exposure lines are 816 */
        if (nValue > pObj->maxCoarseIntgTime)
        {
            nValue = pObj->maxCoarseIntgTime;
        }

        /* TODO: How to calculate fine integration time */
        status = Bsp_deviceWrite16(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue,
                                   (UInt32) 1);
    }

    return (status);
}

Int32 Bsp_ar0140SetGainParams(const Bsp_ar0140HandleObj     *pObj,
                              const Bsp_VidSensorGainParams *gainPrms)
{
    Int32  status = FVID2_SOK;
    UInt32 cnt;
    UInt16 nAddr, nValue;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr, gain;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == gainPrms)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        gain = gainPrms->analogGain;

        /* Sensor support at max 10x analog gain */
        for (cnt = 0; cnt < BSP_AR0140_ANALOG_MAX_GAIN; cnt++)
        {
            if (gain <= gBspVidSensorAr0140GainsTable[cnt][0])
            {
                nAddr = BSP_AR0140_ANALOG_GAIN_REG;

                nValue = (UInt16)
                         ((gBspVidSensorAr0140GainsTable[cnt][1] &
                           (UInt32) 0x7) << 4);
                nValue |= (UInt16)
                          ((gBspVidSensorAr0140GainsTable[cnt][2] &
                            (UInt32) 0xF) << 0);

                status = Bsp_deviceWrite16(nI2cInstId,
                                           nDeviceAddr,
                                           &nAddr,
                                           &nValue,
                                           (UInt32) 1);
                break;
            }
        }
    }

    return (status);
}

Int32 Bsp_ar0140SensorGetExposureRatio(
    const Bsp_ar0140HandleObj   *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms)
{
    Int32 status = FVID2_SOK;

    if ((pObj == NULL) || (NULL == expRatioPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* TODO: Read exposure ratio from register */
        expRatioPrms->exposureRatio = BSP_AR0140_DEFAULT_EXP_RATIO;
    }

    return (status);
}

Int32 Bsp_ar0140SensorSetWdrParams(
    Bsp_ar0140HandleObj          *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms)
{
    Int32  status = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == wdrPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pObj->wdrEnable = wdrPrms->wdrMode;
    }

    return (status);
}

Int32 Bsp_ar0140SensorGetDccParams(
    const Bsp_ar0140HandleObj *pObj,
    Bsp_VidSensorDccParams    *dccPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == dccPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        dccPrms->dccCameraId = BSP_AR0140_DCC_CAMERA_ID;
        switch (pObj->wdrEnable)
        {
            case BSP_VID_SENSOR_WDR_MODE_1PASS:
                dccPrms->dccCfgSize  = sizeof (gBspDrvAr0140DccCfg1);
                dccPrms->pDccCfg     = gBspDrvAr0140DccCfg1;
                break;
            case BSP_VID_SENSOR_WDR_MODE_2PASS:
            case 0:
            default:
                dccPrms->dccCfgSize  = sizeof (gBspDrvAr0140DccCfg);
                dccPrms->pDccCfg     = gBspDrvAr0140DccCfg;
                break;
        }
    }

    return (status);
}

static Int32 Bsp_ar0140I2cReadReg(const Bsp_ar0140HandleObj *pObj,
                                  const UInt16              *regAddr,
                                  UInt16                    *regVal,
                                  UInt32                     numRegs)
{
    Int32  status = FVID2_SOK;
    UInt32 cnt;
    UInt8  nValue[4];
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        for (cnt = 0; cnt < numRegs; cnt++)
        {
            /* Convert Registers address and value into 8bit array */
            nValue[0U] = (UInt8) ((regAddr[cnt] >> 8U) & (UInt8) 0xFF);
            nValue[1U] = (UInt8) ((regAddr[cnt] >> 0U) & (UInt8) 0xFF);

            status = Bsp_deviceRawWrite8(nI2cInstId,
                                         nDeviceAddr,
                                         nValue,
                                         (UInt32) 2);

            if (FVID2_SOK == status)
            {
                status = Bsp_deviceRawRead8(nI2cInstId,
                                            nDeviceAddr,
                                            &nValue[2U],
                                            (UInt32) 2);

                regVal[cnt] =
                    (UInt16)((UInt16)((nValue[2U] & (UInt16) 0xFF) << 8U) |
                             ((UInt16)(nValue[3U] & (UInt16) 0xFF)));
            }
        }
    }

    return (status);
}

Int32 Bsp_ar0140SensorSetFps(
                const Bsp_ar0140HandleObj *pObj,
                const UInt32 *pFps)
{
    Int32  status = FVID2_SOK;
    UInt16 nAddr, nValue;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == pFps)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        switch (*pFps)
        {
            case FVID2_FPS_30:
                nAddr = 0x300CU;
                nValue = 0x0672U;
                break;
            case FVID2_FPS_15:
                nAddr = 0x300CU;
                nValue = (0x0672U * 2U);
                break;
            default:
                break;
        }

        status = Bsp_deviceWrite16(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue,
                                   (UInt32) 1);
    }

    return (status);
}
