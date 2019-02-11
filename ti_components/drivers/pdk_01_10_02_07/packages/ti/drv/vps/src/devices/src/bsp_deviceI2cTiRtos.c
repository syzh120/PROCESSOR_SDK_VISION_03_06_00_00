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
 *  \file bsp_deviceI2cTiRtos.c
 *
 *  \brief File containing the BSP device I2C functions based on TI RTOS driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bsp_devicePriv.h>

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

static Int32 Bsp_deviceI2cLock(UInt32 i2cInstId, Bool lock);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Bsp_DeviceObj gBspDevObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_deviceI2cInit(void)
{
    Int32                      retVal = BSP_SOK;
    UInt32                     instCnt, i2cInstId;
    const Bsp_BoardI2cData    *i2cData;
    Bsp_BoardI2cInstData      *i2cInstData;
    I2C_Params                 i2cOpenPrms;
    I2C_Params_init(&i2cOpenPrms);

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspDeviceTrace, (NULL != i2cData));
    GT_assert(BspDeviceTrace,
              (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));
    GT_assert(BspDeviceTrace, (NULL != i2cData->instData));

    Bsp_deviceI2cDebugEnable(FALSE);

    for (instCnt = 0U; instCnt < BSP_DEVICE_I2C_INST_ID_MAX; instCnt++)
    {
        gBspDevObj.i2cHndl[instCnt]     = NULL;
        gBspDevObj.i2cHndlLock[instCnt] = NULL;
    }

    for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
    {
        i2cInstData = &i2cData->instData[instCnt];
        i2cInstId   = i2cInstData->instId;

        gBspDevObj.i2cHndl[i2cInstId] = I2C_open(i2cInstId, &i2cOpenPrms);
        GT_assert(BspDeviceTrace, (NULL != gBspDevObj.i2cHndl[i2cInstId]));
        gBspDevObj.i2cHndlLock[i2cInstId] =
            BspOsal_semCreate((Int32) 1, (Bool) TRUE);
        if (NULL == gBspDevObj.i2cHndlLock[i2cInstId])
        {
            I2C_close(gBspDevObj.i2cHndl[i2cInstId]);
            gBspDevObj.i2cHndl[i2cInstId] = NULL;
            retVal = BSP_EFAIL;
            break;
        }
    }

    return (retVal);
}

Int32 Bsp_deviceI2cDeInit(void)
{
    Int32       retVal = BSP_SOK;
    UInt32      instCnt;

    for (instCnt = 0U; instCnt < BSP_DEVICE_I2C_INST_ID_MAX; instCnt++)
    {
        if (NULL != gBspDevObj.i2cHndl[instCnt])
        {
            I2C_close(gBspDevObj.i2cHndl[instCnt]);
            gBspDevObj.i2cHndl[instCnt] = NULL;
            if (NULL != gBspDevObj.i2cHndlLock[instCnt])
            {
                BspOsal_semDelete(&gBspDevObj.i2cHndlLock[instCnt]);
                gBspDevObj.i2cHndlLock[instCnt] = NULL;
            }
        }
    }

    return (retVal);
}

Int32 Bsp_deviceI2cProbeAll(UInt32 i2cInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 slaveAddress, counter;

    GT_assert(BspDeviceTrace, (i2cInstId < BSP_DEVICE_I2C_INST_ID_MAX));

    /* Bsp_i2cCreate should have been called for this instance
     * for its proper initialization. */
    if (NULL != gBspDevObj.i2cHndl[i2cInstId])
    {
        for (counter = 0U; counter < 128U; counter++)
        {
            slaveAddress = counter;
            /* Probing 0x18 STM LCD/Touch Controller address results in I2C
             * bus hang as the touch screen controller expects the host to
             * to read the touch data after addressing it.
             */
            if (((0x18U == slaveAddress) &&
                 (BSP_DEVICE_I2C_INST_ID_0 == i2cInstId)))
            {
                /* do nothing */
            }
            else
            {
                if (I2C_control(
                        gBspDevObj.i2cHndl[i2cInstId],
                        I2C_CMD_PROBE,
                        &slaveAddress) == I2C_STATUS_SUCCESS)
                {
                    GT_2trace(BspDeviceTrace, GT_INFO,
                              "I2C%d: Passed for address 0x%x !!! \r\n",
                              i2cInstId,
                              slaveAddress);
                }
            }
        }
    }

    return (retVal);
}

Int32 Bsp_deviceI2cProbeDevice(UInt32 i2cInstId, UInt8 slaveAddress)
{
    Int32 retVal = BSP_EFAIL;
    /* Underneath i2c control API from the driver typecasts the
     * slave address to uint32_t, to initialize 32-bit I2C
     * Slave Address register, hence it is dangerous to pass
     * the address of 8 bit value to the i2c driver.
     * This can to be addressed locally as below
     * with zero change in the Bsp_deviceI2cProbeDevice API
     */
    UInt32 slaveAddr32 = (UInt32) slaveAddress;

    GT_assert(BspDeviceTrace, (i2cInstId < BSP_DEVICE_I2C_INST_ID_MAX));

    /* Bsp_i2cCreate should have been called for this instance
     * for its proper initialization. */
    if (NULL != gBspDevObj.i2cHndl[i2cInstId])
    {
        if (I2C_control(
                gBspDevObj.i2cHndl[i2cInstId],
                I2C_CMD_PROBE,
                &slaveAddr32) == I2C_STATUS_SUCCESS)
        {
            retVal = BSP_SOK;
        }
    }

    return (retVal);
}

Int32 Bsp_deviceI2cDebugEnable(UInt32 enable)
{
    gBspDevObj.i2cDebugEnable = enable;

    return (BSP_SOK);
}

Int32 Bsp_deviceRead8(UInt32       i2cInstId,
                      UInt32       i2cDevAddr,
                      const UInt8 *regAddr,
                      UInt8       *regValue,
                      UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    UInt8  tempRegAddr;
    I2C_Transaction i2cXferPrms;
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);
            i2cXferPrms.slaveAddress = i2cDevAddr;
            for (regId = 0; regId < numRegs; regId++)
            {
                tempRegAddr             = regAddr[regId];
                i2cXferPrms.writeBuf    = &tempRegAddr;
                i2cXferPrms.writeCount  = 1U;
                i2cXferPrms.readBuf     = &regValue[regId];
                i2cXferPrms.readCount   = 1U;
                i2cXferPrms.timeout     = 5000U;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                    break;
                }

                if (gBspDevObj.i2cDebugEnable == (UInt32) TRUE)
                {
                    GT_4trace(BspDeviceTrace, GT_INFO,
                              " Read8 I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId],
                              regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceRawRead8(UInt32 i2cInstId,
                         UInt32 i2cDevAddr,
                         UInt8 *regValue,
                         UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt32 start, end, diff;

    if ((NULL == regValue) || (0U == numRegs))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            i2cXferPrms.slaveAddress = i2cDevAddr;
            i2cXferPrms.writeBuf     = NULL;
            i2cXferPrms.writeCount   = 0U;
            i2cXferPrms.readBuf      = regValue;
            i2cXferPrms.readCount    = numRegs;
            i2cXferPrms.timeout     = 5000U;

            GT_assert(BspDeviceTrace,
                      (NULL != gBspDevObj.i2cHndl[i2cInstId]));
            status =
                I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
            if (status == FALSE)
            {
                retVal = BSP_EFAIL;
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: DEV 0x%02x: RD ERROR !!!\n",
                          i2cInstId,
                          i2cDevAddr);
            }

            if (gBspDevObj.i2cDebugEnable == TRUE)
            {
                if (BSP_SOK == retVal)
                {
                    for (regId = 0; regId < numRegs; regId++)
                    {
                        GT_4trace(
                            BspDeviceTrace, GT_INFO,
                            " RawRead8 I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \n",
                            i2cInstId,
                            i2cDevAddr,
                            0x8U + regId,
                            regValue[regId]);
                    }
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceWrite8(UInt32       i2cInstId,
                       UInt32       i2cDevAddr,
                       const UInt8 *regAddr,
                       const UInt8 *regValue,
                       UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 2U;
                i2cXferPrms.readBuf      = NULL;
                i2cXferPrms.readCount    = 0U;
                i2cXferPrms.timeout     = 5000U;

                buffer[0] = regAddr[regId];
                buffer[1] = regValue[regId];

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x ... ERROR !!! \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                    break;
                }

                if ((gBspDevObj.i2cDebugEnable == TRUE) && (BSP_SOK == retVal))
                {
                    for (regId = 0; regId < numRegs; regId++)
                    {
                        GT_4trace(
                            BspDeviceTrace, GT_INFO,
                            " RawRead8 I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \n",
                            i2cInstId,
                            i2cDevAddr,
                            0x8U + regId,
                            regValue[regId]);
                    }
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }
            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceRawWrite8(UInt32 i2cInstId,
                          UInt32 i2cDevAddr,
                          UInt8 *regValue,
                          UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt32 start, end, diff;

    if ((NULL == regValue) || (0U == numRegs))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  "I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (BSP_SOK == retVal)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            i2cXferPrms.slaveAddress = i2cDevAddr;
            i2cXferPrms.writeBuf     = regValue;
            i2cXferPrms.writeCount   = numRegs;
            i2cXferPrms.readBuf      = NULL;
            i2cXferPrms.readCount    = 0U;
            i2cXferPrms.timeout      = 5000U;

            GT_assert(BspDeviceTrace,
                      (NULL != gBspDevObj.i2cHndl[i2cInstId]));
            status =
                I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
            if (status == FALSE)
            {
                retVal = BSP_EFAIL;
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: DEV 0x%02x: ERROR !!! \n", i2cInstId,
                          i2cDevAddr);
            }

            if (gBspDevObj.i2cDebugEnable == TRUE)
            {
                GT_2trace(BspDeviceTrace, GT_INFO,
                          " RawWrite8 I2C%d: DEV 0x%02x: ", i2cInstId,
                          i2cDevAddr);
                for (regId = 0; regId < numRegs; regId++)
                {
                    GT_1trace(BspDeviceTrace, GT_INFO,
                              " 0x%02x", regValue[regId]);
                }
                GT_0trace(BspDeviceTrace, GT_INFO, " \n");
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceRead16(UInt32        i2cInstId,
                       UInt32        i2cDevAddr,
                       const UInt16 *regAddr,
                       UInt16       *regValue,
                       UInt32        numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[2], rdBuffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 2U;
                i2cXferPrms.readBuf      = rdBuffer;
                i2cXferPrms.readCount    = 2U;
                i2cXferPrms.timeout      = 5000U;

                buffer[0]        = regAddr[regId] >> 8;
                buffer[1]        = regAddr[regId] & 0xFFU;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                    break;
                }

                regValue[regId] =
                    (((UInt16) rdBuffer[0]) & 0x00FFU) |
                        ((UInt16) (((UInt16) rdBuffer[1]) << 8) & 0xFF00U);

                if (gBspDevObj.i2cDebugEnable == TRUE)
                {
                    GT_4trace(BspDeviceTrace, GT_INFO,
                              " Read16 I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId],
                              regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceWrite16(UInt32        i2cInstId,
                        UInt32        i2cDevAddr,
                        const UInt16 *regAddr,
                        const UInt16 *regValue,
                        UInt32        numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[4];
    UInt32 start, end, diff;
    UInt32 bufVal;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 4U;
                i2cXferPrms.readBuf      = NULL;
                i2cXferPrms.readCount    = 0U;
                i2cXferPrms.timeout      = 5000U;

                buffer[0]        = regAddr[regId] >> 8;
                bufVal           = ((UInt32) regAddr[regId] & 0xFFU);
                buffer[1]        = (UInt8) (bufVal);
                buffer[2]        = regValue[regId] >> 8;
                bufVal           = ((UInt32) regValue[regId] & 0xFFU);
                buffer[3]        = (UInt8) (bufVal);

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                    break;
                }

                if (gBspDevObj.i2cDebugEnable == TRUE)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_INFO,
                        " Write16 I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

/* Address is 8-bit and Data is 16-bit long. */
Int32 Bsp_deviceRead16_Custom(UInt32        i2cInstId,
                              UInt32        i2cDevAddr,
                              const UInt16 *regAddr,
                              UInt16       *regValue,
                              UInt32        numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[2], rdBuffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 1U;
                i2cXferPrms.readBuf      = rdBuffer;
                i2cXferPrms.readCount    = 2U;
                i2cXferPrms.timeout      = 5000U;

                buffer[0] = regAddr[regId] & 0xFFU;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                    break;
                }

                regValue[regId] =
                    (((UInt16) buffer[1]) & 0x00FFU) |
                        ((UInt16) (((UInt16) buffer[0]) << 8) & 0xFF00U);
                if (gBspDevObj.i2cDebugEnable == TRUE)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_INFO,
                        " Read16_Custom I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

/* Address is 8-bit and Data is 16-bit long. */
Int32 Bsp_deviceWrite16_Custom(UInt32 i2cInstId, UInt32 i2cDevAddr,
                               const UInt16 *regAddr,
                               const UInt16 *regValue, UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[4];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 3U;
                i2cXferPrms.readBuf      = NULL;
                i2cXferPrms.readCount    = 0U;
                i2cXferPrms.timeout      = 5000U;

                buffer[0]        = regAddr[regId] & 0xFFU;
                buffer[1]        = regValue[regId] >> 8;
                buffer[2]        = regValue[regId] & 0xFFU;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                    break;
                }

                if (gBspDevObj.i2cDebugEnable == TRUE)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_INFO,
                        " Write16_Custom I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

/* Address is 16-bit and Data is 8-bit long. */
Int32 Bsp_deviceWrite_Custom_16A8D(UInt32        i2cInstId,
                                   UInt32        i2cDevAddr,
                                   const UInt16 *regAddr,
                                   const UInt8  *regValue,
                                   UInt32        numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[4];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 3U;
                i2cXferPrms.readBuf      = NULL;
                i2cXferPrms.readCount    = 0U;
                i2cXferPrms.timeout      = 5000U;

                buffer[0]        = (regAddr[regId] >> 8U) & 0xFFU;
                buffer[1]        = regAddr[regId] & 0xFFU;
                buffer[2]        = regValue[regId] & 0xFFU;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                    break;
                }

                if (gBspDevObj.i2cDebugEnable == TRUE)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_INFO,
                        " Write16_Custom I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceRead16Msb(UInt32        i2cInstId,
                          UInt32        i2cDevAddr,
                          const UInt16 *regAddr,
                          UInt16       *regValue,
                          UInt32        numRegs)
{
    Int32  retVal = BSP_SOK;
    bool   status;
    UInt32 regId;
    I2C_Transaction i2cXferPrms;
    UInt8  buffer[2], rdBuffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            /* Get start ticks */
            start = BspOsal_getCurTimeInMsec();

            /* I2C transfer parameter default initializations */
            I2C_transactionInit(&i2cXferPrms);

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cXferPrms.slaveAddress = i2cDevAddr;
                i2cXferPrms.writeBuf     = buffer;
                i2cXferPrms.writeCount   = 2U;
                i2cXferPrms.readBuf      = rdBuffer;
                i2cXferPrms.readCount    = 2U;
                i2cXferPrms.timeout      = 5000U;

                buffer[0]        = regAddr[regId] >> 8;
                buffer[1]        = regAddr[regId] & 0xFFU;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                status =
                    I2C_transfer(gBspDevObj.i2cHndl[i2cInstId], &i2cXferPrms);
                if (status == FALSE)
                {
                    retVal = BSP_EFAIL;
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                    break;
                }

                regValue[regId] =
                    (((UInt16) rdBuffer[1]) & 0x00FFU) |
                        ((UInt16) (((UInt16) rdBuffer[0]) << 8) & 0xFF00U);

                if (gBspDevObj.i2cDebugEnable == TRUE)
                {
                    GT_4trace(BspDeviceTrace, GT_INFO,
                              " Read16 I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId],
                              regValue[regId]);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

static Int32 Bsp_deviceI2cLock(UInt32 i2cInstId, Bool lock)
{
    Int32 retVal = BSP_SOK;

    if (i2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
    {
        retVal = BSP_EFAIL;
    }
    else if ((NULL == gBspDevObj.i2cHndl[i2cInstId]) ||
             (NULL == gBspDevObj.i2cHndlLock[i2cInstId]))
    {
        GT_1trace(
            BspDeviceTrace, GT_ERR,
            "I2C%d: Instance NOT enabled during init ... ERROR !!! \n",
            i2cInstId);
        retVal = BSP_EFAIL;
    }
    else
    {
        if (lock)
        {
            BspOsal_semWait(
                gBspDevObj.i2cHndlLock[i2cInstId],
                BSP_OSAL_WAIT_FOREVER);
        }
        else
        {
            BspOsal_semPost(gBspDevObj.i2cHndlLock[i2cInstId]);
        }
    }

    return (retVal);
}
