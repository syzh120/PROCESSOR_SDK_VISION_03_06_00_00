/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *
 */

/**
 *  \file     sbl_utils_tda3xx_i2c.c
 *
 *  \brief    This file contains the APIs needed for I2C communication
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda3xx.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda3xx_i2c.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static LLD_hsi2cErrorCode_t SblUtilsI2cRawWrite8(hsI2cObjHandle i2cHandle,
                                                 uint32_t       i2cInstId,
                                                 uint32_t       i2cDevAddr,
                                                 uint8_t       *regValue,
                                                 uint32_t       numRegs);

static LLD_hsi2cErrorCode_t SblUtilsI2cRawRead8(hsI2cObjHandle i2cHandle,
                                                uint32_t       i2cInstId,
                                                uint32_t       i2cDevAddr,
                                                uint8_t       *regValue,
                                                uint32_t       numRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t gDeviceI2cInitDone = (uint32_t) FALSE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SBLUtilsConfigDevice(uint32_t deviceId)
{
    LLD_hsi2cErrorCode_t  retVal = LLD_HSI2C_SUCCESS;
    hsI2cHandle           i2cHandle;
    hsI2cObjHandle        i2cObjHandle;
    lld_hsi2c_initParam_t initPrms;
    uint8_t  regValue[3];
    uint32_t i2cInst, ioExpAddr, numRegs;

    /* Initialize the I2C */
    initPrms.opMode       = HSI2C_OPMODE_POLLED;
    initPrms.is10BitAddr  = 0;
    initPrms.isMasterMode = 1;
    initPrms.i2cBusFreq   = I2C_NORMAL;
    initPrms.i2cIntNum    = CSL_INTC_EVENTID_I2CINT1;
    i2cInst = HSI2C_INST_0;
    retVal  = lld_i2c_init(&i2cObjHandle, (LLD_Hsi2cInstId_t) i2cInst,
                           &initPrms);
    i2cHandle = lld_i2c_open((LLD_Hsi2cInstId_t) i2cInst, NULL, NULL);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, "Failed to open I2C Handle");
        SBLLibAbortBoot();
    }

    /* Initialize I/O Expander */
    if ((uint32_t) FALSE == gDeviceI2cInitDone)
    {
        i2cInst   = HSI2C_INST_0;
        ioExpAddr = 0x23U;
        numRegs   = 0x3U;

        /* Config Default Values */
        regValue[0U] = 0x5BU;
        regValue[1U] = 0xD0U;
        regValue[2U] = 0xFFU;
        SBLUtilsWriteOutputPort(i2cHandle, i2cInst, ioExpAddr, regValue,
                                numRegs);

        /* Select pins as Output */
        regValue[0U] = 0x0U;
        regValue[1U] = 0x0U;
        regValue[2U] = 0x0U;
        SBLUtilsWritePortConfig(i2cHandle, i2cInst, ioExpAddr, regValue,
                                numRegs);
        gDeviceI2cInitDone = (uint32_t) TRUE;
    }

    /* Read IO Expander values */
    i2cInst   = HSI2C_INST_0;
    ioExpAddr = 0x23U;
    numRegs   = 0x3U;
    SBLUtilsReadOutputPort(i2cHandle, i2cInst, ioExpAddr, regValue, numRegs);
    if (SBL_UTILS_DEVICE_ID_MMC4 == deviceId)
    {
        regValue[0U] |= (uint8_t) (0x80U);
        regValue[0U] &= (uint8_t) ~(0x40U);
    }
    else if (SBL_UTILS_DEVICE_ID_EMAC0PHY == deviceId)
    {
        regValue[0U] &= (uint8_t) ~(0x80U);
        regValue[0U] |= (uint8_t) (0x40U);
    }
    else if ((SBL_UTILS_DEVICE_ID_UART1 == deviceId) ||
             (SBL_UTILS_DEVICE_ID_UART2 == deviceId))
    {
        regValue[0U] |= (uint8_t) (0x01U);
        regValue[1U] |= (uint8_t) (0x02U);
        if (SBL_UTILS_DEVICE_ID_UART1 == deviceId)
        {
            regValue[1U] &= (uint8_t) ~(0x04U);
        }
    }
    else
    {
        retVal = LLD_HSI2C_FAIL;
    }

    SBLUtilsWriteOutputPort(i2cHandle, i2cInst, ioExpAddr, regValue, numRegs);

    return retVal;
}

int32_t SBLUtilsWritePortConfig(hsI2cObjHandle i2cHandle,
                                uint32_t       i2cInstId,
                                uint32_t       i2cDevAddr,
                                const uint8_t *regValue,
                                uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[numRegs + 1U];

    if ((NULL == regValue) || (0U == numRegs))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = 0x8CU;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = SblUtilsI2cRawWrite8(
            i2cHandle,
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t SBLUtilsWriteOutputPort(hsI2cObjHandle i2cHandle,
                                uint32_t       i2cInstId,
                                uint32_t       i2cDevAddr,
                                const uint8_t *regValue,
                                uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[numRegs + 1U];

    if ((NULL == regValue) || (0U == numRegs))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = 0x84U;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = SblUtilsI2cRawWrite8(
            i2cHandle,
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t SBLUtilsReadOutputPort(hsI2cObjHandle i2cHandle,
                               uint32_t       i2cInstId,
                               uint32_t       i2cDevAddr,
                               uint8_t       *regValue,
                               uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = ((uint8_t) 0x84U +
                              (uint8_t) cnt);
            retVal = SblUtilsI2cRawWrite8(
                i2cHandle,
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = SblUtilsI2cRawRead8(
                    i2cHandle,
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static LLD_hsi2cErrorCode_t SblUtilsI2cRawWrite8(hsI2cObjHandle i2cHandle,
                                                 uint32_t       i2cInstId,
                                                 uint32_t       i2cDevAddr,
                                                 uint8_t       *regValue,
                                                 uint32_t       numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cParams;

    if ((NULL == regValue) ||
        (0U == numRegs) ||
        (NULL == i2cHandle))
    {
        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.buffer    = regValue;
        i2cParams.bufLen    = numRegs;
        i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
        i2cParams.timeout   = 0xFFFFFF;

        retVal = lld_i2c_transfer(i2cHandle, &i2cParams);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }
    return (retVal);
}

static LLD_hsi2cErrorCode_t SblUtilsI2cRawRead8(hsI2cObjHandle i2cHandle,
                                                uint32_t       i2cInstId,
                                                uint32_t       i2cDevAddr,
                                                uint8_t       *regValue,
                                                uint32_t       numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cParams;

    if ((NULL == regValue) ||
        (0U == numRegs) ||
        (NULL == i2cHandle))
    {
        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.bufLen    = numRegs;
        i2cParams.timeout   = 0xFFFFFF;
        i2cParams.buffer    = (uint8_t *) regValue;
        i2cParams.flags     = (LLD_HSI2C_DEFAULT_READ);

        retVal = lld_i2c_transfer(i2cHandle, &i2cParams);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    return (retVal);
}

