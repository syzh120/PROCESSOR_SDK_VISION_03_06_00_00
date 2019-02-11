/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file bspdrv_ov2775I2c.c
 *
 *  \brief OV2775 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov2775/src/bspdrv_ov2775Priv.h>
#include <ov2775/src/bspdrv_ov2775Dcc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const UInt8 gBspDrvOv2775DccCfg[BSP_OV2775_DCC_CFG_NUM_ELEM] = BSP_DRV_OV2775DCC_CFG;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Get OV2775 chip ID and Manufacturer ID
 */
Int32 Bsp_ov2775GetChipId(Bsp_ov2775HandleObj            *pObj,
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

        regAddr[numRegs]  = BSP_OV2775_CHIP_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2775_CHIP_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV2775_CHIP_ID_REV_ID;
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
        pStatus->chipId       = ((UInt32) regValue[0] << 8) | regValue[1];
        pStatus->chipRevision = regValue[2U];
    }

    return status;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov2775RegWrite(Bsp_ov2775HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32  status = FVID2_SOK;
    UInt8  regVal;
    UInt32 numRegs;
    UInt16 regValTmp;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;
        for (numRegs = 0; ((numRegs < pPrm->numRegs) &&
                           (FVID2_SOK == status)); numRegs++)
        {
            regValTmp = pPrm->regValue16[numRegs] & (UInt16) 0xFFU;
            regVal    = (UInt8) regValTmp;

            status = Bsp_deviceWrite_Custom_16A8D(
                pCreatePrms->deviceI2cInstId,
                pCreatePrms->deviceI2cAddr[0],
                pPrm->regAddr,
                &regVal,
                1U);
        }
    }
    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov2775RegRead(const Bsp_ov2775HandleObj       *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm)
{
    UInt32 numRegs;
    UInt16 regValue, regValueTemp;
    Int32  status = FVID2_SOK;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        for (numRegs = 0; ((numRegs < pPrm->numRegs) &&
                           (FVID2_SOK == status)); numRegs++)
        {
            status = Bsp_deviceRead16(
                pObj->createPrms.deviceI2cInstId,
                pObj->createPrms.deviceI2cAddr[0],
                &pPrm->regAddr[numRegs],
                (UInt16 *) &regValue,
                (UInt32) 1U);

            regValueTemp = (regValue & (UInt16) 0x00FF);
            pPrm->regValue16[numRegs] = regValueTemp;
        }
    }

    return (status);
}

Int32 Bsp_ov2775SensorStartStop(const Bsp_ov2775HandleObj *pObj,
                                 UInt32                      bStartSensor)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegVal8;
    UInt16 nRegValue16;
    UInt16 nRegAddr16;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        nRegAddr16  = BSP_OV2775_SOFTWARE_RESET_REG;
        numRegs     = 1U;

        status = Bsp_deviceRead16(
            nI2cInstId,
            nDeviceAddr,
            &nRegAddr16,
            &nRegValue16,
            numRegs);
        if ((UInt32) TRUE == bStartSensor)
        {
            nRegValue16 = nRegValue16 | (UInt16) 0x1U;
        }
        else
        {
            nRegValue16 = nRegValue16 & (UInt16) 0xFEU;
        }
        numRegs = 1U;

        nRegVal8 = (UInt8) nRegValue16;

        status = Bsp_deviceWrite_Custom_16A8D(
            nI2cInstId,
            nDeviceAddr,
            &nRegAddr16,
            &nRegVal8,
            numRegs);
        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    return status;
}

/* OV2775 Sensor Software reset  */
Int32 Bsp_ov2775SoftwareReset(const Bsp_ov2775HandleObj *pObj)
{
    Int32 status = FVID2_SOK;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    return status;
}

/* OV2775 Sensor Config  */
Int32 Bsp_ov2775SensorConfig(
    Bsp_ov2775HandleObj          *pObj,
    const Bsp_VidSensorConfigRegs *sensorConfig)
{
    UInt8           nValue;
    UInt16          nAddr;
    UInt32          nIndex;
    Int32           status = FVID2_SOK;
    UInt32          nI2cInstId;
    UInt32          nDeviceAddr   = 0U;
    UInt32          loopBreakFlag = 0U;
    UInt32          nValueTemp;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
    }

    if (FVID2_SOK == status)
    {
        nIndex = 0U;
        while (TRUE)
        {
            /* For OV2775 sensor the address is 16-bit long */
            nAddr = sensorConfig[nIndex].regAddr & (UInt16)0xFFFFU;

            /* For OV2775 sensor the value is 8-bit long */
            nValueTemp =
                ((UInt32) sensorConfig[nIndex].regValue & (UInt32) 0xFFU);
            nValue = (UInt8) nValueTemp;

            if (0x30C0U == nAddr)
            {
                UInt8 tempVal = (UInt8) BSP_OV2775_READ_MODE_MIRROR_ENABLE_MASK |
                                BSP_OV2775_READ_MODE_FLIP_ENABLE_MASK;
                tempVal = (UInt8) ~(tempVal);
                nValue &= tempVal;
                if (TRUE == pObj->flipPrms.hFlip)
                {
                    nValue |= BSP_OV2775_READ_MODE_MIRROR_ENABLE_MASK;
                }
                if (TRUE == pObj->flipPrms.vFlip)
                {
                    nValue |= BSP_OV2775_READ_MODE_FLIP_ENABLE_MASK;
                }
            }

            if (0x3252U == nAddr)
            {
                UInt8 tempVal = (UInt8) BSP_OV2775_ISP_CTRL2_MIRROR_ENABLE_MASK |
                            BSP_OV2775_ISP_CTRL2_FLIP_ENABLE_MASK;
                tempVal = (UInt8) ~(tempVal);
                nValue &= tempVal;
                if (TRUE == pObj->flipPrms.hFlip)
                {
                    nValue |= BSP_OV2775_ISP_CTRL2_MIRROR_ENABLE_MASK;
                }
                if (TRUE == pObj->flipPrms.vFlip)
                {
                    nValue |= BSP_OV2775_ISP_CTRL2_FLIP_ENABLE_MASK;
                }
            }

            if (0x30A91U == nAddr)
            {
                if (TRUE == pObj->flipPrms.hFlip)
                {
                    nValue += 1U;
                    GT_0trace(
                        BspDeviceTrace, GT_ERR, "Set horizontal flip \n");
                }
            }

            if (nAddr == 0xFFFFU)
            {
                GT_1trace(
                    BspDeviceTrace, GT_ERR, ": end sensor config script at index: %d\n", nIndex);
                loopBreakFlag = 1U;
            }
            else if ((sensorConfig[nIndex].regMask ==
                      BSP_VID_SENSOR_DLY_REG_MASK) &&
                     ((UInt16) BSP_VID_SENSOR_DLY_REG == nAddr))
            {
                GT_1trace(
                    BspDeviceTrace, GT_ERR, ": wait for %dms\n", nValue);
                BspOsal_sleep((UInt32) nValue);
                nIndex ++;
            }
            else
            {
                status = Bsp_deviceWrite_Custom_16A8D(
                    nI2cInstId,
                    nDeviceAddr,
                    &(nAddr),
                    (const UInt8 *) &(nValue),
                    (UInt32) 0x1U);

                if (FVID2_SOK != status)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_ERR, ": Could not write to "
                        "Reg at addr 0x%x, Value 0x%x, Slave Addr 0x%x, I2c 0x%x\n"
                        , nAddr, nValue,
                        nDeviceAddr,
                        nI2cInstId);
                    loopBreakFlag = 1U;
                }
                if (loopBreakFlag != 1U)
                {
                    nIndex++;
                }
            }
            if (loopBreakFlag == 1U)
            {
                break;
            }
        }
    }
    else
    {
        GT_1trace(
            BspDeviceTrace, GT_ERR,
            ": No I2C Ack from sensor OV 2775 At address %d"
            " Aborting this test\n",
            nDeviceAddr);
    }

    if ((FVID2_SOK != status)  && (pObj != NULL))
    {
        pObj->wdrMode = BSP_VID_SENSOR_WDR_DISABLED;
    }

    return (status);
}

Int32 Bsp_ov2775SensorGetExposureRatio(
    const Bsp_ov2775HandleObj  *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms)
{
    Int32 status = FVID2_SOK;

    if ((pObj == NULL) || (NULL == expRatioPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        expRatioPrms->exposureRatio = 16;
    }

    return (status);
}

Int32 Bsp_ov2775SensorSetWdrParams(
    Bsp_ov2775HandleObj         *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms)
{
    Int32  status = FVID2_SOK;
    UInt16 regVal;
    UInt16 regAddr;
    Bsp_VidSensorRegRdWrParams rdWrPrms;

    if ((pObj == NULL) || (NULL == wdrPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        regAddr = (UInt16) 0x3190U;

        rdWrPrms.regAddr    = &regAddr;
        rdWrPrms.regValue16 = &regVal;
        rdWrPrms.numRegs    = 1U;
        rdWrPrms.deviceNum  = 0U;

        status = Bsp_ov2775RegRead(pObj, &rdWrPrms);

        if (FVID2_SOK == status)
        {
            regVal &= (UInt8) ~BSP_OV2775_OUTPUT_DATA_FMT_MASK;
            switch (wdrPrms->wdrMode) {
                case BSP_VID_SENSOR_WDR_DISABLED:
                    regVal |= BSP_OV2775_OUTPUT_DATA_FMT_LINEAR;
                    break;
                case BSP_VID_SENSOR_WDR_MODE_1PASS:
                case BSP_VID_SENSOR_WDR_MODE_2PASS:
                    regVal |= BSP_OV2775_OUTPUT_DATA_FMT_2x12_COMB;
                    break;
                default:
                    regVal |= BSP_OV2775_OUTPUT_DATA_FMT_LINEAR;
                    break;
            }

            status = Bsp_ov2775RegWrite(pObj, &rdWrPrms);
        }
    }
    return (status);
}

Int32 Bsp_ov2775SensorGetDccParams(
    const Bsp_ov2775HandleObj *pObj,
    Bsp_VidSensorDccParams     *dccPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == dccPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        dccPrms->dccCameraId = BSP_OV2775_DCC_CAMERA_ID;
        dccPrms->dccCfgSize  = sizeof (gBspDrvOv2775DccCfg);
        dccPrms->pDccCfg     = gBspDrvOv2775DccCfg;

    }

    return (status);
}

Int32 Bsp_ov2775SensorSetFps(
    const Bsp_ov2775HandleObj *pObj,
    const UInt32               *pFps)
{
    Int32  status = FVID2_SOK;

    return (status);
}

