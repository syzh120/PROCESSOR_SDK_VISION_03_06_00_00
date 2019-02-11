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
 *  \file bspdrv_pga450.c
 *
 *  \brief PGA450 Ultra-sonic sensor driver file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/sysbios/syncs/SyncSem.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_pga450.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Various commands and field definition */
#define BSP_PGA450_BREAK_FIELD          (0x00U)
#define BSP_PGA450_SYNC_FIELD           (0x55U)

#define BSP_PGA450_DETECT_CMD           (0x00U)
#define BSP_PGA450_START_MEASURE_CMD    (0x01U)
#define BSP_PGA450_GET_MEASUREMENT_CMD  (0x02U)
#define BSP_PGA450_UPDATE_EEPROM_CMD    (0x03U)

#define BSP_PGA450_CMD_SHIFT            (0x04U)
#define BSP_PGA450_CMD_MASK             (0xF0U)
#define BSP_PGA450_ADDRESS_SHIFT        (0x00U)
#define BSP_PGA450_ADDRESS_MASK         (0x0FU)

#define BSP_PGA450_DETECT_DUMMY_1       (0x12U)
#define BSP_PGA450_DETECT_DUMMY_2       (0x34U)
#define BSP_PGA450_DETECT_CHECKSUM      (0xB9U)

#define BSP_PGA450_CMD_RESPONSE_DELAY   (4U)
#define BSP_PGA450_MEASUREMENT_DELAY    (8U)

/**
 *  \brief This is the RX GIO_submit timeout - assuming at the max 3 bytes
 *  needs to be received with some room (so total 10 bytes).
 *  Note: This doesn't include the processing time wait requried by sensor,
 *  that has to be a separate wait before calling UART driver read.
 *  Also this assumes 19.2K baud rate and timeout clock of 425 MHz used in M4.
 */
#define BSP_PGA450_UART_RX_TIMEOUT      (0x300000U)

/*
 *  GIO_Params_init will initialize the async packet to 2.
 */
#define BSP_PGA450_ASYNC_IOM_PACKET_MAX                                     (2U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief PGA450 global driver object.
 */
typedef struct
{
    BspOsal_SemHandle lock;
    /**< Global driver lock. */
    DEV_Struct        uartDevStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Device Object */
    Int32             isUartDevAdded[BSP_DEVICE_UART_INST_ID_MAX];
    /**< Flag set to TRUE when UART instance is added. */
    GIO_Handle        uartTxHandle[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART TX Channel handle. */
    GIO_Handle        uartRxHandle[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART RX Channel handle. */
    GIO_Struct        uartTxStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Tx Channel Handle Object */
    GIO_Struct        uartRxStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Rx Channel Handle Object */
    SyncSem_Struct    uartTxSyncSemStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Tx Channel Sync Sem Object */
    SyncSem_Struct    uartRxSyncSemStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Rx Channel Sync Sem Object */
    Semaphore_Struct  uartTxSemStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Tx Channel Semaphore Object */
    Semaphore_Struct  uartRxSemStruct[BSP_DEVICE_UART_INST_ID_MAX];
    /**< UART Rx Channel Semaphore Object */
    IOM_Packet        uartRxIomPacket[BSP_DEVICE_UART_INST_ID_MAX][
        BSP_PGA450_ASYNC_IOM_PACKET_MAX];
    /**< UART Tx Channel IOM Object */
    IOM_Packet        uartTxIomPacket[BSP_DEVICE_UART_INST_ID_MAX][
        BSP_PGA450_ASYNC_IOM_PACKET_MAX];
    /**< UART Rx Channel IOM Object */
} Bsp_Pga450Obj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all instances.
 */
static Bsp_Pga450Obj gBspPga450Obj;

static char         *gBspPga450UartDevName[BSP_DEVICE_UART_INST_ID_MAX] =
{
    "/uart0", "/uart1", "/uart2", "/uart3", "/uart4",
    "/uart5", "/uart6", "/uart7", "/uart8", "/uart9"
};

static Uart_Params   gBspPga450UartPrms =
{
    TRUE,                       /* cacheEnable                    */
    BSP_UART_FIFO_SIZE,         /* chunksize                      */
    TRUE,                       /* fifoEnable                     */
    UART_OPMODE_POLLED,         /* opMode                         */
    FALSE,                      /* loopbackEnabled                */
    UART_BAUDRATE_19_2K,        /* baudRate                       */
    UART_NUMSTOPBITS_1,         /* stopBits                       */
    UART_CHARLEN_8,             /* charLen                        */
    UART_PARITY_NO,             /* parity                         */
    UART_RXTRIGLVL_8,           /* rxThreshold                    */
    UART_TXTRIGLVL_56,          /* txThreshold                    */
    {
        /* fc                             */
        UART_FCTYPE_NONE,
        UART_FCPARAM_TXNONE,
        UART_FCPARAM_RXNONE
    },
    0,                          /* edmaRxTC                       */
    0,                          /* edmaTxTC                       */
    0,                          /* hwiNumber                      */
    BSP_PGA450_UART_RX_TIMEOUT, /* polledModeTimeout              */
    FALSE,                      /* PRCM control disabled          */
    UART_PLLDOMAIN_0,           /* PLL domain used by the driver  */
    NULL,                       /* prcmHandle                     */
    0                           /* prcm device ID                 */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Bsp_pga450FlushUartRx(UInt32 uartInstId);

static Int32 Bsp_pga450CreateUartDriver(const Bsp_Pga450InitParams *initPrms);
static Int32 Bsp_pga450DeleteUartDriver(void);

static UInt8 Bsp_pga450MakeCmdField(UInt8 cmd, UInt8 address);

static Int32 Bsp_pga450Lock(void);
static Int32 Bsp_pga450Unlock(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_pga450Init(const Bsp_Pga450InitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    Int32 initValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != initPrms));

    /* Memset global object */
    BspUtils_memset(&gBspPga450Obj, 0, sizeof (gBspPga450Obj));

    /* Create global lock */
    initValue          = (Int32) 1;
    gBspPga450Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspPga450Obj.lock)
    {
        retVal = BSP_EALLOC;
    }

    if (BSP_SOK == retVal)
    {
        /* Create all UART drivers */
        retVal = Bsp_pga450CreateUartDriver(initPrms);
    }

    /* Deinit incase of error */
    if (BSP_SOK != retVal)
    {
        Bsp_pga450DeInit();
    }

    return (retVal);
}

Int32 Bsp_pga450DeInit(void)
{
    /* Delete all created UART driver */
    Bsp_pga450DeleteUartDriver();

    if (NULL != gBspPga450Obj.lock)
    {
        /* Delete semaphore's. */
        BspOsal_semDelete(&gBspPga450Obj.lock);
        gBspPga450Obj.lock = NULL;
    }

    return (BSP_SOK);
}

Int32 Bsp_pga450ProbeDevice(UInt32 uartInstId, UInt8 deviceId)
{
    Int32  isDetected = FALSE, retVal = BSP_SOK;
    UInt8  txBuffer[10], rxBuffer[10];
    Int    status;
    size_t len;

    /* Check params */
    if (uartInstId >= BSP_DEVICE_UART_INST_ID_MAX)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid UART Instance!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (uartInstId >= BSP_PGA450_MAX_DEVICE)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid device ID!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        if ((NULL == gBspPga450Obj.uartTxHandle[uartInstId]) ||
            (NULL == gBspPga450Obj.uartRxHandle[uartInstId]))
        {
            GT_0trace(
                BspDeviceTrace, GT_ERR,
                " UART TX/RX channel not created. Check UART instance!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        Bsp_pga450Lock();

        /* Flush any stale data */
        Bsp_pga450FlushUartRx(uartInstId);

        /* Send detect command */
        txBuffer[0] = BSP_PGA450_BREAK_FIELD;
        txBuffer[1] = BSP_PGA450_SYNC_FIELD;
        txBuffer[2] = Bsp_pga450MakeCmdField((UInt8) BSP_PGA450_DETECT_CMD,
                                             deviceId);
        txBuffer[3] = 0x00U;
        len         = 4U;
        status      = GIO_write(
            gBspPga450Obj.uartTxHandle[uartInstId],
            &txBuffer,
            &len);
        if (IOM_COMPLETED != status)
        {
            GT_1trace(BspDeviceTrace, GT_ERR,
                      "\r\nGIO_write failed. returned : %d \r\n", status);
            retVal = BSP_EFAIL;
        }

        if (BSP_SOK == retVal)
        {
            /* Wait for some time for PGA450 to respond */
            BspOsal_sleep((UInt32) BSP_PGA450_CMD_RESPONSE_DELAY);

            len    = 3U;
            status = GIO_read(
                gBspPga450Obj.uartRxHandle[uartInstId],
                &rxBuffer[0U],
                &len);
            if (IOM_COMPLETED != status)
            {
                /* Timed out */
                GT_0trace(BspDeviceTrace, GT_DEBUG, "RX timed out!!\r\n");
                retVal = BSP_EFAIL;
            }
        }

        if (BSP_SOK == retVal)
        {
            /* Parse the received bytes */
            if ((BSP_PGA450_DETECT_DUMMY_1 == rxBuffer[0]) &&
                (BSP_PGA450_DETECT_DUMMY_2 == rxBuffer[1]) &&
                (BSP_PGA450_DETECT_CHECKSUM == rxBuffer[2]))
            {
                isDetected = TRUE;
            }
            else
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Invalid bytes received!!\r\n");
            }
        }

        Bsp_pga450Unlock();
    }

    return (isDetected);
}

Int32 Bsp_pga450GetMeasurement(UInt32 uartInstId,
                               UInt8  deviceId,
                               UInt8  distMode)
{
    Int32  measuredDist = (-((Int32) 1)), retVal = BSP_SOK;
    UInt8  txBuffer[10], rxBuffer[10];
    UInt32 temp1, temp2;
    Int    status;
    size_t len;

    /* Check params */
    if (uartInstId >= BSP_DEVICE_UART_INST_ID_MAX)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid UART Instance!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (uartInstId >= BSP_PGA450_MAX_DEVICE)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid device ID!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        if ((NULL == gBspPga450Obj.uartTxHandle[uartInstId]) ||
            (NULL == gBspPga450Obj.uartRxHandle[uartInstId]))
        {
            GT_0trace(
                BspDeviceTrace, GT_ERR,
                " UART TX/RX channel not created. Check UART instance!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        Bsp_pga450Lock();

        /* Flush any stale data */
        Bsp_pga450FlushUartRx(uartInstId);

        /* Send start measurement command */
        txBuffer[0] = BSP_PGA450_BREAK_FIELD;
        txBuffer[1] = BSP_PGA450_SYNC_FIELD;
        txBuffer[2] = Bsp_pga450MakeCmdField(
            (UInt8) BSP_PGA450_START_MEASURE_CMD, deviceId);
        txBuffer[3] = distMode;
        txBuffer[4] = 0x00U;
        len         = 5U;
        status      = GIO_write(
            gBspPga450Obj.uartTxHandle[uartInstId],
            &txBuffer,
            &len);
        if (IOM_COMPLETED != status)
        {
            GT_1trace(BspDeviceTrace, GT_ERR,
                      "\r\nGIO_write failed. returned : %d \r\n", status);
            retVal = BSP_EFAIL;
        }

        if (BSP_SOK == retVal)
        {
            /* Wait for some time to PGA450 to finish the measurement */
            BspOsal_sleep((UInt32) BSP_PGA450_MEASUREMENT_DELAY);

            /* Send get measurement command */
            txBuffer[0] = BSP_PGA450_BREAK_FIELD;
            txBuffer[1] = BSP_PGA450_SYNC_FIELD;
            txBuffer[2] = Bsp_pga450MakeCmdField(
                (UInt8) BSP_PGA450_GET_MEASUREMENT_CMD,
                deviceId);
            txBuffer[3] = 0x00U;
            len         = 4U;
            status      = GIO_write(
                gBspPga450Obj.uartTxHandle[uartInstId],
                &txBuffer,
                &len);
            if (IOM_COMPLETED != status)
            {
                GT_1trace(BspDeviceTrace, GT_ERR,
                          "\r\nGIO_write failed. returned : %d \r\n", status);
                retVal = BSP_EFAIL;
            }
        }

        if (BSP_SOK == retVal)
        {
            /* Wait for some time for PGA450 to respond */
            BspOsal_sleep((UInt32) BSP_PGA450_CMD_RESPONSE_DELAY);

            len    = 3U;
            status = GIO_read(
                gBspPga450Obj.uartRxHandle[uartInstId],
                &rxBuffer[0U],
                &len);
            if (IOM_COMPLETED != status)
            {
                /* Timed out */
                GT_0trace(BspDeviceTrace, GT_ERR, "RX timed out!!\r\n");
                retVal = BSP_EFAIL;
            }
        }

        if (BSP_SOK == retVal)
        {
            /* Calculate distance */
            temp1 =
                (((UInt32) rxBuffer[0U]) << 8U) | ((UInt32) rxBuffer[1U]);
            temp2        = (1715U * temp1) / 100000U;
            measuredDist = (Int32) temp2;
        }

        Bsp_pga450Unlock();
    }

    return (measuredDist);
}

static void Bsp_pga450FlushUartRx(UInt32 uartInstId)
{
    Int    status;
    size_t len;
    UInt8  rxBuffer[10];

    while (1U)
    {
        len    = 1U;
        status = GIO_read(
            gBspPga450Obj.uartRxHandle[uartInstId],
            &rxBuffer[0U],
            &len);
        if (IOM_ETIMEOUT == status)
        {
            /* Timed out */
            break;
        }

        if (IOM_COMPLETED == status)
        {
            GT_0trace(BspDeviceTrace, GT_DEBUG,
                      "Flushed stale data in UART!!\r\n");
        }
    }

    return;
}

static Int32 Bsp_pga450CreateUartDriver(const Bsp_Pga450InitParams *initPrms)
{
    Int32            retVal = BSP_SOK;
    UInt32           instCnt, uartInstId;
    IOM_Fxns        *iomFxns;
    GIO_Params       ioParams;
    DEV_Params       uartDevParams;
    SyncSem_Params   syncSemParams;
    Semaphore_Params semParams;
    Error_Block      eb;
    Uart_ChanParams  chPrms;

    /* Check for NULL pointers and range check */
    GT_assert(BspDeviceTrace, (NULL != initPrms));
    GT_assert(BspDeviceTrace,
              (initPrms->numUartInst <= BSP_PGA450_MAX_UART_INST));
    GT_assert(BspDeviceTrace,
              (initPrms->numUartInst <= BSP_DEVICE_UART_INST_ID_MAX));

    /* Add device instance */
    for (instCnt = 0U; instCnt < initPrms->numUartInst; instCnt++)
    {
        uartInstId = initPrms->uartInstId[instCnt];
        GT_assert(BspDeviceTrace, (uartInstId < BSP_DEVICE_UART_INST_ID_MAX));

        DEV_Params_init(&uartDevParams);
        uartDevParams.deviceParams = &gBspPga450UartPrms;
        uartDevParams.initFxn      = NULL;
        uartDevParams.devid        = uartInstId;

        Error_init(&eb);
        iomFxns = (IOM_Fxns *) &Uart_IOMFXNS;

        DEV_construct(&gBspPga450Obj.uartDevStruct[instCnt],
                      gBspPga450UartDevName[uartInstId], iomFxns,
                      &uartDevParams,
                      &eb);

        gBspPga450Obj.isUartDevAdded[instCnt] = TRUE;
    }

    if (BSP_SOK == retVal)
    {
        /* Create TX and RX channel */
        for (instCnt = 0U; instCnt < initPrms->numUartInst; instCnt++)
        {
            uartInstId = initPrms->uartInstId[instCnt];
            GT_assert(BspDeviceTrace,
                      (uartInstId < BSP_DEVICE_UART_INST_ID_MAX));

            /* Create TX channel */
            Error_init(&eb);
            GIO_Params_init(&ioParams);
            chPrms.hEdma        = NULL;
            ioParams.chanParams = &chPrms;

            Semaphore_Params_init(&semParams);
            semParams.mode = Semaphore_Mode_BINARY;
            Semaphore_construct(&gBspPga450Obj.uartTxSemStruct[uartInstId], 0,
                                &semParams);

            SyncSem_Params_init(&syncSemParams);
            syncSemParams.sem = Semaphore_handle(
                &gBspPga450Obj.uartTxSemStruct[uartInstId]);
            SyncSem_construct(&gBspPga450Obj.uartTxSyncSemStruct[uartInstId],
                              &syncSemParams,
                              &eb);

            ioParams.sync =
                SyncSem_Handle_upCast(SyncSem_handle(&gBspPga450Obj.
                                                     uartTxSyncSemStruct[
                                                         uartInstId]));

            GT_assert(BspDeviceTrace,
                      (ioParams.numPackets <= BSP_PGA450_ASYNC_IOM_PACKET_MAX));
            ioParams.packets = &(gBspPga450Obj.uartTxIomPacket[uartInstId][0]);
            BspUtils_memset(ioParams.packets, 0,
                            (ioParams.numPackets * sizeof (IOM_Packet)));

            GIO_construct(&gBspPga450Obj.uartTxStruct[uartInstId],
                          gBspPga450UartDevName[uartInstId], (UInt) GIO_OUTPUT,
                          &ioParams,
                          &eb);
            gBspPga450Obj.uartTxHandle[uartInstId] = GIO_handle(
                &gBspPga450Obj.uartTxStruct[uartInstId]);
            if ((Bool) TRUE == Error_check(&eb))
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          " UART TX channel creation failed!!\r\n");
                retVal = BSP_EFAIL;
            }
            if (BSP_SOK == retVal)
            {
                /* Create RX channel */
                Error_init(&eb);
                GIO_Params_init(&ioParams);
                chPrms.hEdma        = NULL;
                ioParams.chanParams = &chPrms;

                Semaphore_Params_init(&semParams);
                semParams.mode = Semaphore_Mode_BINARY;
                Semaphore_construct(&gBspPga450Obj.uartRxSemStruct[uartInstId],
                                    0,
                                    &semParams);

                SyncSem_Params_init(&syncSemParams);
                syncSemParams.sem = Semaphore_handle(
                    &gBspPga450Obj.uartRxSemStruct[uartInstId]);
                SyncSem_construct(
                    &gBspPga450Obj.uartRxSyncSemStruct[uartInstId],
                    &syncSemParams,
                    &eb);

                ioParams.sync =
                    SyncSem_Handle_upCast(SyncSem_handle(&gBspPga450Obj.
                                                         uartRxSyncSemStruct[
                                                             uartInstId]));

                GT_assert(BspDeviceTrace,
                          (ioParams.numPackets <=
                           BSP_PGA450_ASYNC_IOM_PACKET_MAX));
                ioParams.packets =
                    &(gBspPga450Obj.uartRxIomPacket[uartInstId][0]);
                BspUtils_memset(ioParams.packets, 0,
                                (ioParams.numPackets * sizeof (IOM_Packet)));

                GIO_construct(&gBspPga450Obj.uartRxStruct[uartInstId],
                              gBspPga450UartDevName[uartInstId],
                              (UInt) GIO_INPUT, &ioParams,
                              &eb);
                gBspPga450Obj.uartRxHandle[uartInstId] = GIO_handle(
                    &gBspPga450Obj.uartRxStruct[uartInstId]);
                if ((Bool) TRUE == Error_check(&eb))
                {
                    GT_0trace(BspDeviceTrace, GT_ERR,
                              " UART RX channel creation failed!!\r\n");
                    retVal = BSP_EFAIL;
                }
            }
            if (BSP_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

static Int32 Bsp_pga450DeleteUartDriver(void)
{
    Int32       retVal = BSP_SOK;
    UInt32      instCnt;
    GIO_Struct *uartGioStruct;

    /* Delete TX and RX channel */
    for (instCnt = 0U; instCnt < BSP_DEVICE_UART_INST_ID_MAX; instCnt++)
    {
        if (NULL != gBspPga450Obj.uartTxHandle[instCnt])
        {
            uartGioStruct = GIO_struct(gBspPga450Obj.uartTxHandle[instCnt]);
            GIO_destruct(uartGioStruct);
            gBspPga450Obj.uartTxHandle[instCnt] = NULL;
        }
        if (NULL != gBspPga450Obj.uartRxHandle[instCnt])
        {
            uartGioStruct = GIO_struct(gBspPga450Obj.uartRxHandle[instCnt]);
            GIO_destruct(uartGioStruct);
            gBspPga450Obj.uartRxHandle[instCnt] = NULL;
        }
    }

    /* Delete device instance */
    for (instCnt = 0U; instCnt < BSP_DEVICE_UART_INST_ID_MAX; instCnt++)
    {
        if (TRUE == gBspPga450Obj.isUartDevAdded[instCnt])
        {
            DEV_destruct(&gBspPga450Obj.uartDevStruct[instCnt]);
            gBspPga450Obj.isUartDevAdded[instCnt] = FALSE;
        }
    }

    return (retVal);
}

static UInt8 Bsp_pga450MakeCmdField(UInt8 cmd, UInt8 address)
{
    UInt8  cmdField;
    UInt32 temp;

    temp  = ((UInt32) cmd << BSP_PGA450_CMD_SHIFT) & BSP_PGA450_CMD_MASK;
    temp |=
        ((UInt32) address <<
         BSP_PGA450_ADDRESS_SHIFT) & BSP_PGA450_ADDRESS_MASK;
    cmdField = (UInt8) temp;

    return (cmdField);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_pga450Lock(void)
{
    BspOsal_semWait(gBspPga450Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (BSP_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_pga450Unlock(void)
{
    BspOsal_semPost(gBspPga450Obj.lock);

    return (BSP_SOK);
}

