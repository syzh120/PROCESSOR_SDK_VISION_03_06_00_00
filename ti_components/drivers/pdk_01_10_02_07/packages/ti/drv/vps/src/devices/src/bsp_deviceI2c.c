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
 *  \file bsp_deviceI2C.c
 *
 *  \brief File containing the BSP device I2C functions.
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
static Int32 BSP_deviceI2cTimeoutHandle(GIO_Handle i2cHandle, UInt32 slaveAddr);
static Int32 BSP_deviceI2cRecoverBus(GIO_Handle i2cHandle);

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
    String                     i2cDevName;
    GIO_Struct                *i2cGioStruct;

/*
 * GIO Parameters Initialization
 */
    Error_Block                eb;
    GIO_Params                 ioParams;
    SyncSem_Params             syncSemParams;
    Semaphore_Params           semParams;
    Error_init(&eb);
    GIO_Params_init(&ioParams);
    lld_hsi2c_datatfr_params_t i2cParams;
    ioParams.chanParams = (void *) &i2cParams;

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
        switch (i2cInstId)
        {
            case BSP_DEVICE_I2C_INST_ID_0:
                i2cDevName = "i2c0";
                break;
            case BSP_DEVICE_I2C_INST_ID_1:
                i2cDevName = "i2c1";
                break;
            case BSP_DEVICE_I2C_INST_ID_2:
                i2cDevName = "i2c2";
                break;
            case BSP_DEVICE_I2C_INST_ID_3:
                i2cDevName = "i2c3";
                break;
            case BSP_DEVICE_I2C_INST_ID_4:
                i2cDevName = "i2c4";
                break;
            default:
                retVal = BSP_EFAIL;
                break;
        }

        if (retVal == BSP_SOK)
        {
            Semaphore_Params_init(&semParams);
            semParams.mode = Semaphore_Mode_BINARY;
            Semaphore_construct(&gBspDevObj.i2cSemStruct[i2cInstId], 0,
                                &semParams);

            SyncSem_Params_init(&syncSemParams);
            syncSemParams.sem =
                Semaphore_handle(&gBspDevObj.i2cSemStruct[i2cInstId]);
            SyncSem_construct(&gBspDevObj.i2cSyncSemStruct[i2cInstId],
                              &syncSemParams,
                              &eb);

            ioParams.sync =
                SyncSem_Handle_upCast(SyncSem_handle(&gBspDevObj.
                                                     i2cSyncSemStruct[
                                                         i2cInstId]));

            GT_assert(BspDeviceTrace,
                      (ioParams.numPackets <= I2C_ASYNC_IOM_PACKET_MAX));
            ioParams.packets = &(gBspDevObj.i2cIomPacket[i2cInstId][0]);
            BspUtils_memset(ioParams.packets, 0,                            (ioParams.numPackets * sizeof (IOM_Packet)));

            GIO_construct(&gBspDevObj.i2cGioStruct[i2cInstId], i2cDevName,
                          (UInt) GIO_INPUT, &ioParams, &eb);
            gBspDevObj.i2cHndl[i2cInstId] = GIO_handle(
                &gBspDevObj.i2cGioStruct[i2cInstId]);
            GT_assert(BspDeviceTrace, (NULL != gBspDevObj.i2cHndl[i2cInstId]));
            gBspDevObj.i2cHndlLock[i2cInstId] =
                BspOsal_semCreate((Int32) 1, (Bool) TRUE);
            if (NULL == gBspDevObj.i2cHndlLock[i2cInstId])
            {
                i2cGioStruct = GIO_struct(gBspDevObj.i2cHndl[i2cInstId]);
                GIO_destruct(i2cGioStruct);
                gBspDevObj.i2cHndl[i2cInstId] = NULL;
                retVal = BSP_EFAIL;
            }
        }
        if (retVal != BSP_SOK)
        {
            break;
        }
    }

    return (retVal);
}

Int32 Bsp_deviceI2cDeInit(void)
{
    Int32       retVal = BSP_SOK;
    UInt32      instCnt;
    GIO_Struct *i2cGioStruct;

    for (instCnt = 0U; instCnt < BSP_DEVICE_I2C_INST_ID_MAX; instCnt++)
    {
        if (NULL != gBspDevObj.i2cHndl[instCnt])
        {
            i2cGioStruct = GIO_struct(gBspDevObj.i2cHndl[instCnt]);
            GIO_destruct(i2cGioStruct);
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
    UInt32 slaveAddr, counter;

    GT_assert(BspDeviceTrace, (i2cInstId < BSP_DEVICE_I2C_INST_ID_MAX));

    /* Bsp_i2cCreate should have been called for this instance
     * for its proper initialization. */
    if (NULL != gBspDevObj.i2cHndl[i2cInstId])
    {
        for (counter = 0U; counter < 128U; counter++)
        {
            slaveAddr = counter;
            /* Due to hardware bug where I2c line is pulled low when
             * device at 0x48 addr is probed in case of TI811X
             * Probing 0x18 STM LCD/Touch Controller address results in I2C
             * bus hang as the touch screen controller expects the host to
             * to read the touch data after addressing it.
             */
            if (((BSP_PLATFORM_SOC_ID_TI811X == Bsp_platformGetSocId()) &&
                 ((0x48U == slaveAddr) &&
                  (BSP_DEVICE_I2C_INST_ID_2 == i2cInstId))) ||
                ((0x18U == slaveAddr) &&
                 (BSP_DEVICE_I2C_INST_ID_0 == i2cInstId)))
            {
                /* do nothing */
            }
            else
            {
                if (GIO_control(gBspDevObj.i2cHndl[i2cInstId], IOCTL_I2C_PROBE,
                                &slaveAddr) == 0)
                {
                    GT_2trace(BspDeviceTrace, GT_INFO,
                              "I2C%d: Passed for address 0x%x !!! \r\n",
                              i2cInstId,
                              slaveAddr);
                }
            }
        }
    }
    return (retVal);
}

Int32 Bsp_deviceI2cProbeDevice(UInt32 i2cInstId, UInt8 slaveAddr)
{
    Int32 retVal = BSP_EFAIL;

    GT_assert(BspDeviceTrace, (i2cInstId < BSP_DEVICE_I2C_INST_ID_MAX));

    /* Bsp_i2cCreate should have been called for this instance
     * for its proper initialization. */
    if (NULL != gBspDevObj.i2cHndl[i2cInstId])
    {
        if (GIO_control(gBspDevObj.i2cHndl[i2cInstId], IOCTL_I2C_PROBE,
                        &slaveAddr) == 0)
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
    UInt32 regId;
    UInt8  tempRegAddr;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.bufLen    = 1;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                tempRegAddr      = regAddr[regId];
                i2cParams.buffer = &tempRegAddr;
                i2cParams.flags
                    = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);

                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         * Recover the bus.
                         */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                }
                if (retVal == BSP_SOK)
                {
                    i2cParams.buffer = &regValue[regId];
                    i2cParams.flags
                        = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START |
                           LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY);

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        IOM_READ,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);

                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[
                                    i2cInstId],
                                i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_3trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId]);
                    }
                }

                if ((gBspDevObj.i2cDebugEnable == (UInt32) TRUE) &&
                    (retVal == BSP_SOK))
                {
                    GT_4trace(BspDeviceTrace, GT_INFO,
                              " Read8 I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId],
                              regValue[regId]);
                }
                if (retVal != BSP_SOK)
                {
                    break;
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt32 start, end, diff;

    if ((NULL == regValue) || (0U == numRegs))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.bufLen    = numRegs;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;
            i2cParams.buffer    = (UInt8 *) regValue;
            i2cParams.flags     = (LLD_HSI2C_DEFAULT_READ);

            GT_assert(BspDeviceTrace,
                      (NULL != gBspDevObj.i2cHndl[i2cInstId]));
            retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                IOM_READ,
                                &i2cParams,
                                &i2cParams.bufLen,
                                NULL);
            if (BSP_SOK != retVal)
            {
                if (retVal == IOM_ETIMEOUT)
                {
                    BSP_deviceI2cTimeoutHandle(gBspDevObj.i2cHndl[i2cInstId],
                                               i2cDevAddr);
                }
                if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                {
                    /* GIO_Submit with Big timeout returned bus busy. Recover
                     *the bus. */
                    BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                }
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: DEV 0x%02x: RD ERROR !!!\r\n",
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
                            " RawRead8 I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \r\n",
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
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.buffer    = buffer;
            i2cParams.bufLen    = 2;
            i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                buffer[0] = regAddr[regId];
                buffer[1] = regValue[regId];

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);
                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x ... ERROR !!! \r\n",
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
                        " Write8 I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x \r\n",
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
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt32 start, end, diff;

    if ((NULL == regValue) || (0U == numRegs))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  "I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.buffer    = regValue;
            i2cParams.bufLen    = numRegs;
            i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            GT_assert(BspDeviceTrace,
                      (NULL != gBspDevObj.i2cHndl[i2cInstId]));
            retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                (UInt32) IOM_WRITE,
                                &i2cParams,
                                &i2cParams.bufLen,
                                NULL);
            if (BSP_SOK != retVal)
            {
                if (retVal == IOM_ETIMEOUT)
                {
                    BSP_deviceI2cTimeoutHandle(gBspDevObj.i2cHndl[i2cInstId],
                                               i2cDevAddr);
                }
                if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                {
                    /* GIO_Submit with Big timeout returned bus busy. Recover
                     *the bus. */
                    BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                }
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: DEV 0x%02x: ERROR !!! \r\n", i2cInstId,
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
                GT_0trace(BspDeviceTrace, GT_INFO, " \r\n");
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cParams.bufLen = 2;
                i2cParams.buffer = (UInt8 *) buffer;
                buffer[0]        = (UInt8) (regAddr[regId] >> 8);
                buffer[1]        = (UInt8) (regAddr[regId] & 0xFFU);
                i2cParams.flags
                    = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);

                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                }
                if (retVal == BSP_SOK)
                {
                    i2cParams.buffer = (UInt8 *) buffer;
                    buffer[0]        = (UInt8) (regValue[regId] >> 8U);
                    buffer[1]        = (UInt8) (regValue[regId] & 0xFFU);
                    i2cParams.bufLen = 2;
                    i2cParams.flags
                        = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START |
                           LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY);

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        IOM_READ,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);
                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[
                                    i2cInstId],
                                i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_3trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId]);
                    }
                }
                if ((gBspDevObj.i2cDebugEnable == TRUE) && (retVal == BSP_SOK))
                {
                    GT_4trace(BspDeviceTrace, GT_INFO,
                              " Read16 I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x\r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId],
                              regValue[regId]);
                }
                if (retVal != BSP_SOK)
                {
                    break;
                }
                else
                {
                    regValue[regId] = (((UInt16) buffer[0]) & 0x00FFU) |
                                      ((UInt16) (((UInt16) buffer[1]) <<
                                                 8) & 0xFF00U);
                }
            }
            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[4];
    UInt32 start, end, diff;
    UInt32 bufVal;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                /*buffer[0] = regAddr[regId];
                 * buffer[1] = regValue[regId];*/
                i2cParams.buffer = buffer;
                buffer[0]        = (UInt8) (regAddr[regId] >> 8);
                bufVal           = ((UInt32) regAddr[regId] & 0xFFU);
                buffer[1]        = (UInt8) (bufVal);
                buffer[2]        = (UInt8) (regValue[regId] >> 8);
                bufVal           = ((UInt32) regValue[regId] & 0xFFU);
                buffer[3]        = (UInt8) (bufVal);
                /*buffer[2]           = regValue[regId] && 0xFF;
                 * buffer[3]           = regValue[regId] >> 8;*/
                i2cParams.bufLen = 4;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);

                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \r\n",
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
                        " Write16 I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \r\n",
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
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cParams.bufLen = 1;
                i2cParams.buffer = (UInt8 *) buffer;
                buffer[0]        = (UInt8) (regAddr[regId] & 0xFFU);
                i2cParams.flags
                    = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);

                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                }
                if (retVal == BSP_SOK)
                {
                    i2cParams.buffer = (UInt8 *) buffer;
                    buffer[0]        = (UInt8) (regValue[regId] >> 8);
                    buffer[1]        = (UInt8) (regValue[regId] & 0xFFU);
                    i2cParams.bufLen = 2;
                    i2cParams.flags
                        = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START |
                           LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY);

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        IOM_READ,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);
                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[
                                    i2cInstId],
                                i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_3trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId]);
                    }
                }
                if ((gBspDevObj.i2cDebugEnable == TRUE) && (retVal == BSP_SOK))
                {
                    GT_4trace(
                        BspDeviceTrace, GT_INFO,
                        " Read16_Custom I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x \r\n",
                        i2cInstId,
                        i2cDevAddr,
                        regAddr[regId],
                        regValue[regId]);
                }
                if (retVal != BSP_SOK)
                {
                    break;
                }
                else
                {
                    regValue[regId] = (((UInt16) buffer[1]) & 0x00FFU) |
                                      ((UInt16) (((UInt16) buffer[0]) <<
                                                 8) & 0xFF00U);
                }
            }

            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[4];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                /*buffer[0] = regAddr[regId];
                 * buffer[1] = regValue[regId];*/
                i2cParams.buffer = buffer;
                buffer[0]        = (UInt8) (regAddr[regId] & 0xFFU);
                buffer[1]        = (UInt8) (regValue[regId] >> 8);
                buffer[2]        = (UInt8) (regValue[regId] & 0xFFU);
                i2cParams.bufLen = 3;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);
                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \r\n",
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
                        " Write16_Custom I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \r\n",
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
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[4];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cParams.buffer = buffer;
                buffer[0]        = (UInt8) ((regAddr[regId] >> 8U) & 0xFFU);
                buffer[1]        = (UInt8) (regAddr[regId] & 0xFFU);
                buffer[2]        = regValue[regId] & 0xFFU;
                i2cParams.bufLen = 3;

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);
                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_4trace(
                        BspDeviceTrace, GT_ERR,
                        " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \r\n",
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
                        " Write16_Custom I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \r\n",
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
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
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
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
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

            i2cParams.slaveAddr = i2cDevAddr;
            i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

            for (regId = 0; regId < numRegs; regId++)
            {
                i2cParams.bufLen = 2;
                i2cParams.buffer = (UInt8 *) buffer;
                buffer[0]        = (UInt8) (regAddr[regId] >> 8);
                buffer[1]        = (UInt8) (regAddr[regId] & 0xFFU);
                i2cParams.flags
                    = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

                GT_assert(BspDeviceTrace,
                          (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                    (UInt32) IOM_WRITE,
                                    &i2cParams,
                                    &i2cParams.bufLen,
                                    NULL);

                if (retVal != BSP_SOK)
                {
                    if (retVal == IOM_ETIMEOUT)
                    {
                        BSP_deviceI2cTimeoutHandle(
                            gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                    }
                    if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                    {
                        /* GIO_Submit with Big timeout returned bus busy.
                         *Recover the bus. */
                        BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[i2cInstId]);
                    }
                    GT_3trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId]);
                }
                if (retVal == BSP_SOK)
                {
                    i2cParams.buffer = (UInt8 *) buffer;
                    buffer[0]        = (UInt8) (regValue[regId] >> 8U);
                    buffer[1]        = (UInt8) (regValue[regId] & 0xFFU);
                    i2cParams.bufLen = 2;
                    i2cParams.flags
                        = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START |
                           LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY);

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        IOM_READ,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);
                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[
                                    i2cInstId],
                                i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_3trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId]);
                    }
                }
                if ((gBspDevObj.i2cDebugEnable == TRUE) && (retVal == BSP_SOK))
                {
                    GT_4trace(BspDeviceTrace, GT_INFO,
                              " Read16 I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x\r\n",
                              i2cInstId,
                              i2cDevAddr,
                              regAddr[regId],
                              regValue[regId]);
                }
                if (retVal != BSP_SOK)
                {
                    break;
                }
                else
                {
                    regValue[regId] = (((UInt16) buffer[1]) & 0x00FFU) |
                                      ((UInt16) (((UInt16) buffer[0]) <<
                                                 8) & 0xFF00U);
                }
            }
            /* Get end ticks */
            end  = BspOsal_getCurTimeInMsec();
            diff = end - start;
            if (retVal != BSP_SOK)
            {
                GT_2trace(BspDeviceTrace, GT_ERR,
                          " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId, diff);
            }

            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceSetBusSpeed(UInt32 i2cInstId, Bsp_I2cBitRate i2cBusFreq)
{
    Int32               retVal = BSP_SOK;
    lld_i2c_busspeed    i2cBusSpeed;

    if ((i2cBusFreq != BSP_I2C_BITRATE_100KHZ) &&
        (i2cBusFreq != BSP_I2C_BITRATE_400KHZ))
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Illegal Params ... ERROR !!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        switch (i2cBusFreq)
        {
            case BSP_I2C_BITRATE_100KHZ:
                i2cBusSpeed = I2C_NORMAL;
                break;

            case BSP_I2C_BITRATE_400KHZ:
                i2cBusSpeed = I2C_FAST;
                break;

            default:
                i2cBusSpeed = I2C_FAST;
                break;
        }

        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);
        if (retVal == BSP_SOK)
        {
            retVal = GIO_control(gBspDevObj.i2cHndl[i2cInstId],
                                 IOCTL_I2C_SET_BUS_FREQUENCY,
                                 (Ptr) &i2cBusSpeed);
            if (retVal != IOM_COMPLETED)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Error in I2C set frequency IOCTL\r\n");
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
            "I2C%d: Instance NOT enabled during init ... ERROR !!! \r\n",
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

static Int32 BSP_deviceI2cTimeoutHandle(GIO_Handle i2cHandle, UInt32 slaveAddr)
{
    Int32 retVal = BSP_SOK;
#ifndef BSP_I2CTIMEOUT_CTRLRESET_DISABLE
    if (NULL == i2cHandle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Illegal Params ... ERROR !!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = GIO_control(i2cHandle, IOCTL_I2C_RESET_CONTROLLER, NULL);
        if (retVal == BSP_SOK)
        {
            retVal = GIO_control(i2cHandle, IOCTL_I2C_PROBE, &slaveAddr);
        }
    }
#endif
    return (retVal);
}

static Int32 BSP_deviceI2cRecoverBus(GIO_Handle i2cHandle)
{
    Int32  retVal = BSP_SOK;
#ifndef BSP_I2CBUS_RECOVER_DISABLE
    UInt32 delay = 100U;
    if (NULL == i2cHandle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Illegal Params ... ERROR !!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        GIO_control(i2cHandle, IOCTL_I2C_RECOVER_BUS, &delay);
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Bus busy detected recover I2C bus !!!\r\n");
    }
#endif
    return (retVal);
}

Int32 Bsp_deviceReadAddr8Data16(UInt32       i2cInstId,
                                UInt32       i2cDevAddr,
                                const UInt8 *regAddr,
                                UInt16      *regValue,
                                UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            if (0 == GIO_control(gBspDevObj.i2cHndl[i2cInstId], IOCTL_I2C_PROBE,
                                 &i2cDevAddr))
            {
                /* Get start ticks */
                start = BspOsal_getCurTimeInMsec();
                i2cParams.slaveAddr = i2cDevAddr;
                i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

                for (regId = 0; regId < numRegs; regId++)
                {
                    i2cParams.bufLen = 1;
                    i2cParams.buffer = (UInt8 *) buffer;
                    buffer[0]        = regAddr[regId];
                    i2cParams.flags
                        = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START |
                           LLD_HSI2C_STOP);

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        (UInt32) IOM_WRITE,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);

                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_3trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId]);
                    }
                    if (retVal == BSP_SOK)
                    {
                        i2cParams.buffer = (UInt8 *) buffer;
                        i2cParams.bufLen = 2;
                        i2cParams.flags
                            = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START |
                               LLD_HSI2C_STOP |
                               LLD_HSI2C_IGNORE_BUS_BUSY);

                        GT_assert(BspDeviceTrace,
                                  (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                        retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                            IOM_READ,
                                            &i2cParams,
                                            &i2cParams.bufLen,
                                            NULL);
                        if (retVal != BSP_SOK)
                        {
                            if (retVal == IOM_ETIMEOUT)
                            {
                                BSP_deviceI2cTimeoutHandle(
                                    gBspDevObj.i2cHndl[
                                        i2cInstId],
                                    i2cDevAddr);
                            }
                            if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                            {
                                /* GIO_Submit with Big timeout returned bus
                                 * busy.
                                 *Recover the bus. */
                                BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                            i2cInstId]);
                            }
                            GT_3trace(
                                BspDeviceTrace, GT_ERR,
                                " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                                i2cInstId,
                                i2cDevAddr,
                                regAddr[regId]);
                        }
                    }
                    if ((gBspDevObj.i2cDebugEnable == TRUE) &&
                        (retVal == BSP_SOK))
                    {
                        GT_4trace(
                            BspDeviceTrace, GT_INFO,
                            " Read16 I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId],
                            regValue[regId]);
                    }
                    if (retVal != BSP_SOK)
                    {
                        break;
                    }
                    else
                    {
                        regValue[regId] = (((UInt16) buffer[1]) & 0x00FFU) |
                                          ((UInt16) (((UInt16) buffer[0]) <<
                                                     8) & 0xFF00U);
                    }
                }
                /* Get end ticks */
                end  = BspOsal_getCurTimeInMsec();
                diff = end - start;
                if (retVal != BSP_SOK)
                {
                    GT_2trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId,
                              diff);
                }
            }
            else
            {
                retVal = BSP_EFAIL;
            }
            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceWriteAddr8Data16(UInt32        i2cInstId,
                                 UInt32        i2cDevAddr,
                                 const UInt8  *regAddr,
                                 const UInt16 *regValue,
                                 UInt32        numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[4];
    UInt32 start, end, diff;
    UInt32 bufVal;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            if (0 == GIO_control(gBspDevObj.i2cHndl[i2cInstId], IOCTL_I2C_PROBE,
                                 &i2cDevAddr))
            {
                /* Get start ticks */
                start = BspOsal_getCurTimeInMsec();
                i2cParams.slaveAddr = i2cDevAddr;
                i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
                i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

                for (regId = 0; regId < numRegs; regId++)
                {
                    i2cParams.buffer = buffer;
                    bufVal           = ((UInt32) regAddr[regId] & 0xFFU);
                    buffer[0]        = (UInt8) (bufVal);
                    buffer[1]        = (UInt8) (regValue[regId] >> 8);
                    bufVal           = ((UInt32) regValue[regId] & 0xFFU);
                    buffer[2]        = (UInt8) (bufVal);
                    i2cParams.bufLen = 3;

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        (UInt32) IOM_WRITE,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);

                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_4trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x ... ERROR !!! \r\n",
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
                            " Write16 I2C%d: DEV 0x%02x: WR 0x%04x = 0x%04x \r\n",
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
                              " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId,
                              diff);
                }
            }
            else
            {
                retVal = BSP_EFAIL;
            }
            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}

Int32 Bsp_deviceReadAddr16Data8(UInt32       i2cInstId,
                                UInt32       i2cDevAddr,
                                const UInt16 *regAddr,
                                UInt8        *regValue,
                                UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    UInt8  buffer[2];
    UInt32 start, end, diff;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_2trace(BspDeviceTrace, GT_ERR,
                  " I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\r\n",
                  i2cInstId,
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_deviceI2cLock(i2cInstId, (Bool) TRUE);

        if (retVal == BSP_SOK)
        {
            if (0 == GIO_control(gBspDevObj.i2cHndl[i2cInstId], IOCTL_I2C_PROBE,
                                 &i2cDevAddr))
            {
                /* Get start ticks */
                start = BspOsal_getCurTimeInMsec();
                i2cParams.slaveAddr = i2cDevAddr;
                i2cParams.timeout   = BSP_OSAL_WAIT_FOREVER;

                for (regId = 0; regId < numRegs; regId++)
                {
                    i2cParams.bufLen = 2;
                    i2cParams.buffer = (UInt8 *) buffer;
                    buffer[0]        = (UInt8) (regAddr[regId] >> 8);
                    buffer[1]        = (UInt8) (regAddr[regId] & 0xFFU);
                    i2cParams.flags  =
                        (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

                    GT_assert(BspDeviceTrace,
                              (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                    retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                        (UInt32) IOM_WRITE,
                                        &i2cParams,
                                        &i2cParams.bufLen,
                                        NULL);

                    if (retVal != BSP_SOK)
                    {
                        if (retVal == IOM_ETIMEOUT)
                        {
                            BSP_deviceI2cTimeoutHandle(
                                gBspDevObj.i2cHndl[i2cInstId], i2cDevAddr);
                        }
                        if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                        {
                            /* GIO_Submit with Big timeout returned bus busy.
                             *Recover the bus. */
                            BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                        i2cInstId]);
                        }
                        GT_3trace(
                            BspDeviceTrace, GT_ERR,
                            " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId]);
                    }
                    if (retVal == BSP_SOK)
                    {
                        i2cParams.buffer = (UInt8 *) buffer;
                        i2cParams.bufLen = 1;
                        i2cParams.flags
                            = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START |
                               LLD_HSI2C_STOP |
                               LLD_HSI2C_IGNORE_BUS_BUSY);

                        GT_assert(BspDeviceTrace,
                                  (NULL != gBspDevObj.i2cHndl[i2cInstId]));
                        retVal = GIO_submit(gBspDevObj.i2cHndl[i2cInstId],
                                            IOM_READ,
                                            &i2cParams,
                                            &i2cParams.bufLen,
                                            NULL);
                        if (retVal != BSP_SOK)
                        {
                            if (retVal == IOM_ETIMEOUT)
                            {
                                BSP_deviceI2cTimeoutHandle(
                                    gBspDevObj.i2cHndl[
                                        i2cInstId],
                                    i2cDevAddr);
                            }
                            if (retVal == LLD_HSI2C_BUS_BUSY_ERR)
                            {
                                /* GIO_Submit with Big timeout returned bus
                                 * busy.
                                 *Recover the bus. */
                                BSP_deviceI2cRecoverBus(gBspDevObj.i2cHndl[
                                                            i2cInstId]);
                            }
                            GT_3trace(
                                BspDeviceTrace, GT_ERR,
                                " I2C%d: DEV 0x%02x: RD 0x%04x ... ERROR !!!\r\n",
                                i2cInstId,
                                i2cDevAddr,
                                regAddr[regId]);
                        }
                    }
                    if ((gBspDevObj.i2cDebugEnable == TRUE) &&
                        (retVal == BSP_SOK))
                    {
                        GT_4trace(
                            BspDeviceTrace, GT_INFO,
                            " Read16 I2C%d: DEV 0x%02x: RD 0x%04x = 0x%04x\r\n",
                            i2cInstId,
                            i2cDevAddr,
                            regAddr[regId],
                            regValue[regId]);
                    }
                    if (retVal != BSP_SOK)
                    {
                        break;
                    }
                    else
                    {
                        regValue[regId] = (UInt8) buffer[0];
                    }
                }
                /* Get end ticks */
                end  = BspOsal_getCurTimeInMsec();
                diff = end - start;
                if (retVal != BSP_SOK)
                {
                    GT_2trace(BspDeviceTrace, GT_ERR,
                              " I2C%d: Error timeout %d ms!!!\r\n", i2cInstId,
                              diff);
                }
            }
            else
            {
                retVal = BSP_EFAIL;
            }
            Bsp_deviceI2cLock(i2cInstId, FALSE);
        }
    }

    return (retVal);
}
