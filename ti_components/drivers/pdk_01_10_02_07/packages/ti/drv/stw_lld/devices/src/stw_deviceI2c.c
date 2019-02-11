/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file stw_device_i2c.c
 *
 *  \brief File containing the STW device I2C functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/devices/stw_deviceIoexp.h>
#include <stw_deviceI2cPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static deviceI2cObj_t gDevObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
LLD_hsi2cErrorCode_t DEVICEI2cInit(const deviceInitParams_t *pPrm)
{
    LLD_hsi2cErrorCode_t  retVal = LLD_HSI2C_SUCCESS;
    uint32_t instCnt;
    LLD_Hsi2cInstId_t     i2cInstId;
    const boardI2cData_t *i2cData;
    boardI2cInstData_t   *i2cInstData;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;

    initPar.opMode       = pPrm->i2cOpMode;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    i2cData = BOARDGetI2cData();
    if ((NULL != i2cData) &&
        (i2cData->numInst <= HSI2C_INST_MAX) &&
        (NULL != i2cData->pInstData))
    {
        DEVICEI2cDebugEnable((uint32_t) FALSE);

        for (instCnt = 0U; instCnt < HSI2C_INST_MAX; instCnt++)
        {
            gDevObj.i2cHndl[instCnt] = NULL;
        }

        for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
        {
            i2cInstData        = &i2cData->pInstData[instCnt];
            i2cInstId          = i2cInstData->instId;
            initPar.i2cBusFreq = i2cInstData->busClkKHz;
            initPar.i2cIntNum  = i2cInstData->intNum;
            if (initPar.opMode != HSI2C_OPMODE_DMA)
            {
                initPar.edmaParam = (void *)NULL;
            }

            retVal = lld_i2c_init(&i2cObjHandle, i2cInstId, &initPar);

            gDevObj.i2cHndl[i2cInstId] = lld_i2c_open(i2cInstId, NULL, NULL);
        }
    }
    else
    {
        UARTPuts("\r\nDevice Init: NULL i2cData pointer", (-((int32_t) 1)));
        retVal = LLD_HSI2C_FAIL;
    }
    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cDeInit(void)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t instCnt;

    for (instCnt = 0U; instCnt < HSI2C_INST_MAX; instCnt++)
    {
        if (NULL != gDevObj.i2cHndl[instCnt])
        {
            lld_i2c_close(&gDevObj.i2cHndl[instCnt]);
            lld_i2c_deinit((LLD_Hsi2cInstId_t) instCnt);
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cProbeAll(uint32_t i2cInstId)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t slaveAddr, counter;

    /* Stw_i2cCreate should have been called for this instance
     * for its proper initialization. */
    if ((i2cInstId < HSI2C_INST_MAX) && (NULL != gDevObj.i2cHndl[i2cInstId]))
    {
        for (counter = 0U; counter < 128U; counter++)
        {
            slaveAddr = counter;
            /* Probing 0x18 STM LCD Controller address results in I2c hang */
            if ((DEVICE_I2C_INST_ID_0 == i2cInstId) &&
                ((uint32_t) 0x18 == slaveAddr))
            {
                /* Do Nothing */
            }
            else
            {
                if (lld_i2c_probe(gDevObj.i2cHndl[i2cInstId],
                                  (uint8_t) slaveAddr) == 0)
                {
                    UARTPuts("\r\nI2C", (-((int32_t) 1)));
                    UARTPutNum((int32_t) i2cInstId);
                    UARTPuts(" Passed for address ", (-((int32_t) 1)));
                    UARTPutHexNum(slaveAddr);
                    UARTPuts("!!! \r\n", (-((int32_t) 1)));
                }
            }
        }
    }
    else
    {
        UARTPuts("\r\n DEVICEI2cProbeAll: I2c handle is NULL for InstId ", (-((int32_t) 1)));
        UARTPutNum((int32_t) i2cInstId);
        retVal = LLD_HSI2C_FAIL;
    }
    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cProbeDevice(uint32_t i2cInstId,
                                          uint8_t  slaveAddr)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    if ((i2cInstId < HSI2C_INST_MAX) && (NULL != gDevObj.i2cHndl[i2cInstId]))
    {
        retVal = lld_i2c_probe(gDevObj.i2cHndl[i2cInstId], slaveAddr);
    }
    else
    {
        UARTPuts("\r\n DEVICEI2cProbeDevice: I2c handle is NULL for InstId ", (-((int32_t) 1)));
        UARTPutNum((int32_t) i2cInstId);
        retVal = LLD_HSI2C_FAIL;
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cRead8(uint32_t       i2cInstId,
                                    uint32_t       i2cDevAddr,
                                    const uint8_t *regAddr,
                                    uint8_t       *regValue,
                                    uint32_t       numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    uint32_t regId;
    uint8_t tempRegAddr;
    lld_hsi2c_datatfr_params_t i2cParams;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0)
        || (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        UARTPuts("\r\nI2C", (-((int32_t) 1)));
        UARTPutHexNum(i2cInstId);
        UARTPuts("DEV", (-((int32_t) 1)));
        UARTPutHexNum(i2cDevAddr);
        UARTPuts("Illegal Params ... ERROR !!!\r\n", (-((int32_t) 1)));
        retVal = LLD_HSI2C_FAIL;
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.bufLen    = 1;
        i2cParams.timeout   = 0xFFFFFF;

        for (regId = 0; regId < numRegs; regId++)
        {
            tempRegAddr      = regAddr[regId];
            i2cParams.buffer = &tempRegAddr;
            i2cParams.flags
                = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

            retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId], &i2cParams);

            if (retVal != LLD_HSI2C_SUCCESS)
            {
                UARTPuts("\r\nI2C", (-((int32_t) 1)));
                UARTPutHexNum(i2cInstId);
                UARTPuts("\r\nDEV", (-((int32_t) 1)));
                UARTPutHexNum(i2cDevAddr);
                UARTPuts("RD", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regAddr[regId]);
                UARTPuts(" ERROR !!!", (-((int32_t) 1)));
            }

            if (retVal == LLD_HSI2C_SUCCESS)
            {
                i2cParams.buffer = &regValue[regId];
                i2cParams.flags
                    = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                       LLD_HSI2C_START |
                       LLD_HSI2C_STOP |
                       LLD_HSI2C_IGNORE_BUS_BUSY);

                retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId],
                                          &i2cParams);

                if (retVal != LLD_HSI2C_SUCCESS)
                {
                    UARTPuts("\r\nI2C", (-((int32_t) 1)));
                    UARTPutHexNum(i2cInstId);
                    UARTPuts("\r\nDEV", (-((int32_t) 1)));
                    UARTPutHexNum(i2cDevAddr);
                    UARTPuts("RD", (-((int32_t) 1)));
                    UARTPutHexNum((uint32_t) regAddr[regId]);
                    UARTPuts(" ERROR !!!", (-((int32_t) 1)));
                }
            }
            if ((gDevObj.i2cDebugEnable == (uint32_t) TRUE) &&
                (retVal == LLD_HSI2C_SUCCESS))
            {
                UARTPuts("\r\nRead8 -", (-((int32_t) 1)));
                UARTPuts(" I2C:", (-((int32_t) 1)));
                UARTPutHexNum(i2cInstId);
                UARTPuts(" DEV:", (-((int32_t) 1)));
                UARTPutHexNum(i2cDevAddr);
                UARTPuts(" RD", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regAddr[regId]);
                UARTPuts("=", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regValue[regId]);
            }
            if (retVal != LLD_HSI2C_SUCCESS)
            {
                break;
            }
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cRawRead8(uint32_t i2cInstId,
                                       uint32_t i2cDevAddr,
                                       uint8_t *regValue,
                                       uint32_t numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint32_t regId;

    if ((NULL == regValue) || (0U == numRegs) ||
        (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        UARTPuts("\r\nI2C", (-((int32_t) 1)));
        UARTPutHexNum(i2cInstId);
        UARTPuts("DEV", (-((int32_t) 1)));
        UARTPutHexNum(i2cDevAddr);
        UARTPuts("Illegal Params ... ERROR !!!\r\n", (-((int32_t) 1)));

        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.bufLen    = numRegs;
        i2cParams.timeout   = 0xFFFFFF;
        i2cParams.buffer    = (uint8_t *) regValue;
        i2cParams.flags     = (LLD_HSI2C_DEFAULT_READ);

        retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId], &i2cParams);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C", (-((int32_t) 1)));
            UARTPutHexNum(i2cInstId);
            UARTPuts("DEV", (-((int32_t) 1)));
            UARTPutHexNum(i2cDevAddr);
            UARTPuts("RD ERROR !!!\r\n", (-((int32_t) 1)));
        }

        if (gDevObj.i2cDebugEnable == TRUE)
        {
            if (LLD_HSI2C_SUCCESS == retVal)
            {
                for (regId = 0; regId < numRegs; regId++)
                {
                    UARTPuts("\r\n RawRead8 -", (-((int32_t) 1)));
                    UARTPuts(" I2C:", (-((int32_t) 1)));
                    UARTPutHexNum(i2cInstId);
                    UARTPuts(" DEV:", (-((int32_t) 1)));
                    UARTPutHexNum(i2cDevAddr);
                    UARTPuts(" RD", (-((int32_t) 1)));
                    UARTPutHexNum(0x8U + regId);
                    UARTPuts("=", (-((int32_t) 1)));
                    UARTPutHexNum((uint32_t) regValue[regId]);
                }
            }
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cWrite8(uint32_t       i2cInstId,
                                     uint32_t       i2cDevAddr,
                                     const uint8_t *regAddr,
                                     const uint8_t *regValue,
                                     uint32_t       numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    uint32_t regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint8_t buffer[2];

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0)
        || (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        UARTPuts("\r\nI2C", (-((int32_t) 1)));
        UARTPutHexNum(i2cInstId);
        UARTPuts("DEV", (-((int32_t) 1)));
        UARTPutHexNum(i2cDevAddr);
        UARTPuts("Illegal Params ... ERROR !!!\r\n", (-((int32_t) 1)));
        retVal = LLD_HSI2C_FAIL;
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.buffer    = buffer;
        i2cParams.bufLen    = 2;
        i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
        i2cParams.timeout   = 0xFFFFFF;

        for (regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = regAddr[regId];
            buffer[1] = regValue[regId];

            retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId],
                                      &i2cParams);
            if (retVal != LLD_HSI2C_SUCCESS)
            {
                UARTPuts("\r\nI2C", (-((int32_t) 1)));
                UARTPutHexNum(i2cInstId);
                UARTPuts("DEV", (-((int32_t) 1)));
                UARTPutHexNum(i2cDevAddr);
                UARTPuts("WR", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regAddr[regId]);
                UARTPuts("=", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regValue[regId]);
                UARTPuts(" ERROR !!!\r\n", (-((int32_t) 1)));
                break;
            }

            if (gDevObj.i2cDebugEnable == TRUE)
            {
                UARTPuts("\r\n Write8 -", (-((int32_t) 1)));
                UARTPuts(" I2C:", (-((int32_t) 1)));
                UARTPutHexNum(i2cInstId);
                UARTPuts(" DEV:", (-((int32_t) 1)));
                UARTPutHexNum(i2cDevAddr);
                UARTPuts(" WR", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regAddr[regId]);
                UARTPuts("=", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regValue[regId]);
            }
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cRawWrite8(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint32_t regId;

    if ((NULL == regValue) || (0U == numRegs) ||
        (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        UARTPuts("\r\nI2C", (-((int32_t) 1)));
        UARTPutHexNum(i2cInstId);
        UARTPuts("DEV", (-((int32_t) 1)));
        UARTPutHexNum(i2cDevAddr);
        UARTPuts("Illegal Params ... ERROR !!!\r\n", (-((int32_t) 1)));
        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.buffer    = regValue;
        i2cParams.bufLen    = numRegs;
        i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
        i2cParams.timeout   = 0xFFFFFF;

        retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId], &i2cParams);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C", (-((int32_t) 1)));
            UARTPutHexNum(i2cInstId);
            UARTPuts("DEV", (-((int32_t) 1)));
            UARTPutHexNum(i2cDevAddr);
            UARTPuts("Illegal Params ... ERROR !!!\r\n", (-((int32_t) 1)));
        }
        if (gDevObj.i2cDebugEnable == TRUE)
        {
            UARTPuts("\r\n RawWrite8 -", (-((int32_t) 1)));
            UARTPuts(" I2C:", (-((int32_t) 1)));
            UARTPutHexNum(i2cInstId);
            UARTPuts(" DEV:", (-((int32_t) 1)));
            UARTPutHexNum(i2cDevAddr);
            for (regId = 0; regId < numRegs; regId++)
            {
                UARTPuts("-", (-((int32_t) 1)));
                UARTPutHexNum((uint32_t) regValue[regId]);
            }
        }
    }
    return (retVal);
}

int32_t DEVICEI2cDebugEnable(uint32_t enable)
{
    gDevObj.i2cDebugEnable = enable;

    return (STW_SOK);
}

