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
 *  \file bspdrv_pga460.c
 *
 *  \brief PGA460 Ultra-sonic sensor driver file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>

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
#include <ti/drv/vps/include/devices/bsp_pga460.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Various commands and field definition */
#define BSP_PGA460_BREAK_FIELD          (0x00U)
#define BSP_PGA460_SYNC_FIELD           (0x55U)

#define BSP_PGA460_DETECT_CMD           (0x00U)
#define BSP_PGA460_START_MEASURE_CMD    (0x01U)
#define BSP_PGA460_GET_MEASUREMENT_CMD  (0x02U)
#define BSP_PGA460_UPDATE_EEPROM_CMD    (0x03U)

#define BSP_PGA460_CMD_SHIFT            (0x04U)
#define BSP_PGA460_CMD_MASK             (0xF0U)
#define BSP_PGA460_ADDRESS_SHIFT        (0x00U)
#define BSP_PGA460_ADDRESS_MASK         (0x0FU)

#define BSP_PGA460_DETECT_DUMMY_1       (0x12U)
#define BSP_PGA460_DETECT_DUMMY_2       (0x34U)
#define BSP_PGA460_DETECT_CHECKSUM      (0xB9U)

#define BSP_PGA460_CMD_RESPONSE_DELAY   (4U)
#define BSP_PGA460_MEASUREMENT_DELAY    (8U)

#define BSP_PGA460_UART_RX_TIMEOUT      (0x20000U)

/*
 *  GIO_Params_init will initialize the async packet to 2.
 */
#define BSP_PGA460_ASYNC_IOM_PACKET_MAX                                     (2U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* New variables */
/* Misc Variables */
static uint8_t gSyncByte = 0x55U;    /* data uint8_t to clock in UART baud rate of PGA460 */
static uint8_t gChecksumInput[44];  /* data uint8_t array for checksum calculator */
static uint8_t gNumObj = 1U;         /* number of objects to detect */
static uint8_t gRegAddr = 0x00U;     /*data uint8_t for Register Address */
static uint8_t gRegData = 0x00U;     /* data uint8_t for Register Data */
static uint8_t gUartAddr = 0U;       /* PGA460 device address (0-8). Assume '0' for single device demo. */
static uint8_t gTempOrNoise = 0U;    /* data uint8_t to determine if temp or noise measurement is to be performed */

/* List User registers by name with default settings for MA40H1SR */
static uint8_t gUSER_DATA1 = 0x00U;
static uint8_t gUSER_DATA2 = 0x00U;
static uint8_t gUSER_DATA3 = 0x00U;
static uint8_t gUSER_DATA4 = 0x00U;
static uint8_t gUSER_DATA5 = 0x00U;
static uint8_t gUSER_DATA6 = 0x00U;
static uint8_t gUSER_DATA7 = 0x00U;
static uint8_t gUSER_DATA8 = 0x00U;
static uint8_t gUSER_DATA9 = 0x00U;
static uint8_t gUSER_DATA10 = 0x00U;
static uint8_t gUSER_DATA11 = 0x00U;
static uint8_t gUSER_DATA12 = 0x00U;
static uint8_t gUSER_DATA13 = 0x00U;
static uint8_t gUSER_DATA14 = 0x00U;
static uint8_t gUSER_DATA15 = 0x00U;
static uint8_t gUSER_DATA16 = 0x00U;
static uint8_t gUSER_DATA17 = 0x00U;
static uint8_t gUSER_DATA18 = 0x00U;
static uint8_t gUSER_DATA19 = 0x00U;
static uint8_t gUSER_DATA20 = 0x00U;
static uint8_t gTVGAIN0 = 0x00U;
static uint8_t gTVGAIN1 = 0x00U;
static uint8_t gTVGAIN2 = 0x00U;
static uint8_t gTVGAIN3 = 0x00U;
static uint8_t gTVGAIN4 = 0x00U;
static uint8_t gTVGAIN5 = 0x00U;
static uint8_t gTVGAIN6 = 0x00U;
static uint8_t gINIT_GAIN = 0x7FU;
static uint8_t gFREQUENCY  = 0x32U;
static uint8_t gDEADTIME = 0x80U;
static uint8_t gPULSE_P1 = 0x04U;
static uint8_t gPULSE_P2 = 0x14U;
static uint8_t gCURR_LIM_P1 = 0x03U;
static uint8_t gCURR_LIM_P2 = 0xD5U;
static uint8_t gREC_LENGTH = 0x07U;
static uint8_t gFREQ_DIAG = 0x33U;
static uint8_t gSAT_FDIAG_TH = 0xEEU;
static uint8_t gFVOLT_DEC = 0x7CU;
static uint8_t gDECPL_TEMP = 0x0FU;
static uint8_t gDSP_SCALE = 0x00U;
static uint8_t gTEMP_TRIM = 0x00U;
static uint8_t gP1_GAIN_CTRL = 0x12U;
static uint8_t gP2_GAIN_CTRL = 0x18U;

static uint8_t gP1_THR_0 = 0xB0U;
static uint8_t gP1_THR_1 = 0x88U;
static uint8_t gP1_THR_2 = 0x88U;
static uint8_t gP1_THR_3 = 0x88U;
static uint8_t gP1_THR_4 = 0x88U;
static uint8_t gP1_THR_5 = 0x88U;
static uint8_t gP1_THR_6 = 0xFBU;
static uint8_t gP1_THR_7 = 0xDEU;
static uint8_t gP1_THR_8 = 0xF7U;
static uint8_t gP1_THR_9 = 0xBDU;
static uint8_t gP1_THR_10 = 0xEFU;
static uint8_t gP1_THR_11 = 0x7FU;
static uint8_t gP1_THR_12 = 0x7FU;
static uint8_t gP1_THR_13 = 0x7FU;
static uint8_t gP1_THR_14 = 0x7FU;
static uint8_t gP1_THR_15 = 0x07U;
static uint8_t gP2_THR_0 = 0xB0U;
static uint8_t gP2_THR_1 = 0x88U;
static uint8_t gP2_THR_2 = 0x88U;
static uint8_t gP2_THR_3 = 0x88U;
static uint8_t gP2_THR_4 = 0x88U;
static uint8_t gP2_THR_5 = 0x88U;
static uint8_t gP2_THR_6 = 0xFBU;
static uint8_t gP2_THR_7 = 0xDEU;
static uint8_t gP2_THR_8 = 0xF7U;
static uint8_t gP2_THR_9 = 0xBDU;
static uint8_t gP2_THR_10 = 0xEFU;
static uint8_t gP2_THR_11 = 0x7FU;
static uint8_t gP2_THR_12 = 0x7FU;
static uint8_t gP2_THR_13 = 0x7FU;
static uint8_t gP2_THR_14 = 0x7FU;
static uint8_t gP2_THR_15 = 0x07U;

static uint8_t gUMR = 0x05U;
static uint8_t gSRW = 0x0AU;
static uint8_t gTVGBW = 0x0EU;
static uint8_t gTHRBW = 0x10U;
/*Broadcast*/
static uint8_t gBC_P1BL = 0x11U;

/**
 *  \brief PGA460 global driver object.
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
        BSP_PGA460_ASYNC_IOM_PACKET_MAX];
    /**< UART Tx Channel IOM Object */
    IOM_Packet        uartTxIomPacket[BSP_DEVICE_UART_INST_ID_MAX][
        BSP_PGA460_ASYNC_IOM_PACKET_MAX];
    /**< UART Rx Channel IOM Object */
} Bsp_Pga460Obj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all instances.
 */
static Bsp_Pga460Obj gBspPga460Obj;

static char         *gBspPga460UartDevName[BSP_DEVICE_UART_INST_ID_MAX] =
{
    "/uart0", "/uart1", "/uart2", "/uart3", "/uart4",
    "/uart5", "/uart6", "/uart7", "/uart8", "/uart9"
};

static Uart_Params   gBspPga460UartPrms =
{
    TRUE,                       /* cacheEnable                    */
    BSP_UART_FIFO_SIZE,         /* chunksize                      */
    TRUE,                       /* fifoEnable                     */
    UART_OPMODE_POLLED,         /* opMode                         */
    FALSE,                      /* loopbackEnabled                */
    UART_BAUDRATE_57_6K,        /* baudRate                       */
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
    BSP_PGA460_UART_RX_TIMEOUT, /* polledModeTimeout              */
    FALSE,                      /* PRCM control disabled          */
    UART_PLLDOMAIN_0,           /* PLL domain used by the driver  */
    NULL,                       /* prcmHandle                     */
    0                           /* prcm device ID                 */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Bsp_pga460FlushUartRx(UInt32 uartInstId);
static void Bsp_pga460FlushUartRx_custom(UInt32 uartInstId, UInt8 flush);

static Int32 Bsp_pga460CreateUartDriver(const Bsp_Pga460InitParams *initPrms);
static Int32 Bsp_pga460DeleteUartDriver(void);
static Int32 Bsp_pga460Lock(void);
static Int32 Bsp_pga460Unlock(void);
static uint8_t calcChecksum(uint8_t cmd);
static Int32 initThreshold(UInt32 uartInstId);
static Int32 initTVG(UInt32 uartInstId);

/* New functions from USM_depth_sense.c */
static uint8_t calcChecksum(uint8_t cmd)
{
        int8_t checksumLoops = 0;


        switch(cmd & 0x001FU)
        {
        case 0 : /*P1BL*/
        case 1U : /*P2BL*/
        case 2U : /*P1LO*/
        case 3U : /*P2LO*/
        case 17U : /*BC_P1BL*/
        case 18U : /*BC_P2BL*/
        case 19U : /*BC_P1LO*/
        case 20U : /*BC_P2LO*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gNumObj;
                checksumLoops = 2;
        break;
        case 4U : /*TNLM*/
        case 21U : /*TNLM*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gTempOrNoise;
                checksumLoops = 2;
        break;
        case 5U : /*UMR*/
        case 6U : /*TNLR*/
        case 7U : /*TEDD*/
        case 8U : /*SD*/
        case 11U : /*EEBR*/
        case 13U : /*TVGBR*/
        case 15U : /*THRBR*/
                gChecksumInput[0] = cmd;
                checksumLoops = 1;
        break;
        case 9U : /*RR*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gRegAddr;
                checksumLoops = 2;
        break;
        case 10U : /*RW*/
        case 22U : /*BC_RW*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gRegAddr;
                gChecksumInput[2] = gRegData;
                checksumLoops = 3;
        break;
        case 14U : /*gTVGBW*/
        case 24U : /*BC_TVGBW*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gTVGAIN0;
                gChecksumInput[2] = gTVGAIN1;
                gChecksumInput[3] = gTVGAIN2;
                gChecksumInput[4] = gTVGAIN3;
                gChecksumInput[5] = gTVGAIN4;
                gChecksumInput[6] = gTVGAIN5;
                gChecksumInput[7] = gTVGAIN6;
                checksumLoops = 8;
        break;
        case 16U : /*gTHRBW*/
        case 25U : /*BC_THRBW*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gP1_THR_0;
                gChecksumInput[2] = gP1_THR_1;
                gChecksumInput[3] = gP1_THR_2;
                gChecksumInput[4] = gP1_THR_3;
                gChecksumInput[5] = gP1_THR_4;
                gChecksumInput[6] = gP1_THR_5;
                gChecksumInput[7] = gP1_THR_6;
                gChecksumInput[8] = gP1_THR_7;
                gChecksumInput[9] = gP1_THR_8;
                gChecksumInput[10] = gP1_THR_9;
                gChecksumInput[11] = gP1_THR_10;
                gChecksumInput[12] = gP1_THR_11;
                gChecksumInput[13] = gP1_THR_12;
                gChecksumInput[14] = gP1_THR_13;
                gChecksumInput[15] = gP1_THR_14;
                gChecksumInput[16] = gP1_THR_15;
                gChecksumInput[17] = gP2_THR_0;
                gChecksumInput[18] = gP2_THR_1;
                gChecksumInput[19] = gP2_THR_2;
                gChecksumInput[20] = gP2_THR_3;
                gChecksumInput[21] = gP2_THR_4;
                gChecksumInput[22] = gP2_THR_5;
                gChecksumInput[23] = gP2_THR_6;
                gChecksumInput[24] = gP2_THR_7;
                gChecksumInput[25] = gP2_THR_8;
                gChecksumInput[26] = gP2_THR_9;
                gChecksumInput[27] = gP2_THR_10;
                gChecksumInput[28] = gP2_THR_11;
                gChecksumInput[29] = gP2_THR_12;
                gChecksumInput[30] = gP2_THR_13;
                gChecksumInput[31] = gP2_THR_14;
                gChecksumInput[32] = gP2_THR_15;
                checksumLoops = 33;
        break;
        case 12U : /*EEBW*/
        case 23U : /*BC_EEBW*/
                gChecksumInput[0] = cmd;
                gChecksumInput[1] = gUSER_DATA1;
                gChecksumInput[2] = gUSER_DATA2;
                gChecksumInput[3] = gUSER_DATA3;
                gChecksumInput[4] = gUSER_DATA4;
                gChecksumInput[5] = gUSER_DATA5;
                gChecksumInput[6] = gUSER_DATA6;
                gChecksumInput[7] = gUSER_DATA7;
                gChecksumInput[8] = gUSER_DATA8;
                gChecksumInput[9] = gUSER_DATA9;
                gChecksumInput[10] = gUSER_DATA10;
                gChecksumInput[11] = gUSER_DATA11;
                gChecksumInput[12] = gUSER_DATA12;
                gChecksumInput[13] = gUSER_DATA13;
                gChecksumInput[14] = gUSER_DATA14;
                gChecksumInput[15] = gUSER_DATA15;
                gChecksumInput[16] = gUSER_DATA16;
                gChecksumInput[17] = gUSER_DATA17;
                gChecksumInput[18] = gUSER_DATA18;
                gChecksumInput[19] = gUSER_DATA19;
                gChecksumInput[20] = gUSER_DATA20;
                gChecksumInput[21] = gTVGAIN0;
                gChecksumInput[22] = gTVGAIN1;
                gChecksumInput[23] = gTVGAIN2;
                gChecksumInput[24] = gTVGAIN3;
                gChecksumInput[25] = gTVGAIN4;
                gChecksumInput[26] = gTVGAIN5;
                gChecksumInput[27] = gTVGAIN6;
                gChecksumInput[28] = gINIT_GAIN;
                gChecksumInput[29] = gFREQUENCY;
                gChecksumInput[30] = gDEADTIME;
                gChecksumInput[31] = gPULSE_P1;
                gChecksumInput[32] = gPULSE_P2;
                gChecksumInput[33] = gCURR_LIM_P1;
                gChecksumInput[34] = gCURR_LIM_P2;
                gChecksumInput[35] = gREC_LENGTH;
                gChecksumInput[36] = gFREQ_DIAG;
                gChecksumInput[37] = gSAT_FDIAG_TH;
                gChecksumInput[38] = gFVOLT_DEC;
                gChecksumInput[39] = gDECPL_TEMP;
                gChecksumInput[40] = gDSP_SCALE;
                gChecksumInput[41] = gTEMP_TRIM;
                gChecksumInput[42] = gP1_GAIN_CTRL;
                gChecksumInput[43] = gP2_GAIN_CTRL;
                checksumLoops = 44;
        break;
        default:
        break;
        }

        gChecksumInput[0] = gChecksumInput[0] + (uint8_t)(gUartAddr << 5U);

        uint16_t carry = 0;
        int8_t i;

        for (i = 0; i < checksumLoops; i++)
        {
                if ((gChecksumInput[i] + carry) < carry)
                {
                        carry = carry + gChecksumInput[i] + 1U;
                }
                else
                {
                        carry = carry + gChecksumInput[i];
                }

                if (carry > 0xFFU)
                {
                  carry = carry - 255U;
                }
        }
        carry = ((uint16_t)(~carry)) & 0x00FFU;
        return (uint8_t)carry;
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_pga460Init(const Bsp_Pga460InitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    Int32 initValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != initPrms));

    /* Memset global object */
    BspUtils_memset(&gBspPga460Obj, 0, sizeof (gBspPga460Obj));

    /* Create global lock */
    initValue          = (Int32) 1;
    gBspPga460Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspPga460Obj.lock)
    {
        retVal = BSP_EALLOC;
    }

    if (BSP_SOK == retVal)
    {
        /* Create all UART drivers */
        retVal = Bsp_pga460CreateUartDriver(initPrms);
    }

    /* Deinit incase of error */
    if (BSP_SOK != retVal)
    {
        Bsp_pga460DeInit();
    }

    return (retVal);
}

Int32 Bsp_pga460DeInit(void)
{
    /* Delete all created UART driver */
    Bsp_pga460DeleteUartDriver();

    if (NULL != gBspPga460Obj.lock)
    {
        /* Delete semaphore's. */
        BspOsal_semDelete(&gBspPga460Obj.lock);
        gBspPga460Obj.lock = NULL;
    }

    return (BSP_SOK);
}

Int32 Bsp_pga460ProbeDevice(UInt32 uartInstId, UInt8 deviceId)
{
    Int32  isDetected = FALSE, retVal = BSP_SOK;

    /* Check params */
    if (uartInstId >= BSP_DEVICE_UART_INST_ID_MAX)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid UART Instance!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (uartInstId >= BSP_PGA460_MAX_DEVICE)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid device ID!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        if ((NULL == gBspPga460Obj.uartTxHandle[uartInstId]) ||
            (NULL == gBspPga460Obj.uartRxHandle[uartInstId]))
        {
            GT_0trace(
                BspDeviceTrace, GT_ERR,
                " UART TX/RX channel not created. Check UART instance!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (retVal == BSP_SOK)
    {
        isDetected = TRUE;
    }

    return (isDetected);
}

Int32 Bsp_pga460InitMeasurement(UInt32 uartInstId)
{
    Int32  retVal = BSP_SOK;

    Bsp_pga460Lock();

    /* Flush any stale data */
    Bsp_pga460FlushUartRx(uartInstId);

    retVal = initThreshold(uartInstId);
    gTHRBW |= 0b00100000U;

    if (BSP_SOK == retVal)
    {
        retVal = initThreshold(uartInstId);
    }

    gTHRBW |= 0b01100000U;

    if (BSP_SOK == retVal)
    {
        retVal = initThreshold(uartInstId);
    }

    gTHRBW &= 0b11011111U;

    if (BSP_SOK == retVal)
    {
        retVal = initThreshold(uartInstId);
    }

    if (BSP_SOK == retVal)
    {
        initTVG(uartInstId);
    }

    gSRW |= 0b00100000U;

    if (BSP_SOK == retVal)
    {
        initTVG(uartInstId);
    }

    gSRW |= 0b01000000U;

    if (BSP_SOK == retVal)
    {
        initTVG(uartInstId);
    }

    gSRW &= 0b11011111U;

    if (BSP_SOK == retVal)
    {
        initTVG(uartInstId);
    }

    /* Flush any stale data */
    Bsp_pga460FlushUartRx(uartInstId);

    Bsp_pga460Unlock();

    return (retVal);
}

void Bsp_pga460SendBroadcast(UInt32 uartInstId,
                             UInt8  deviceId,
                             UInt8  firstBroadcast)
{
    Int32  retVal = BSP_SOK;
    UInt8  txBuffer[4];
    Int    status;
    size_t len;

    /* Check params */
    if (uartInstId >= BSP_DEVICE_UART_INST_ID_MAX)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid UART Instance!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (uartInstId >= BSP_PGA460_MAX_DEVICE)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid device ID!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        if ((NULL == gBspPga460Obj.uartTxHandle[uartInstId]) ||
            (NULL == gBspPga460Obj.uartRxHandle[uartInstId]))
        {
            GT_0trace(
                BspDeviceTrace, GT_ERR,
                " UART channels not created. Check UART instance!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        Bsp_pga460Lock();

        /* Flush any stale data */
        if (firstBroadcast == 1U)
        {
            Bsp_pga460FlushUartRx(uartInstId);
        }
        else
        {
            Bsp_pga460FlushUartRx_custom(uartInstId, 1U);
        }
        BspOsal_sleep((UInt32)2);

        /* Send start measurement command */
        txBuffer[0] = gSyncByte;
        txBuffer[1] = gBC_P1BL;
        txBuffer[2] = gNumObj;
        txBuffer[3] = calcChecksum(gBC_P1BL);

        len         = 4U;

        status      = GIO_write(
            gBspPga460Obj.uartTxHandle[uartInstId],
            &txBuffer,
            &len);

        if (IOM_COMPLETED != status)
        {
            GT_1trace(BspDeviceTrace, GT_ERR,
                      "\r\nGIO_write failed. returned : %d \r\n", status);
            retVal = BSP_EFAIL;
        }

        BspOsal_sleep((UInt32)7);

        Bsp_pga460Unlock();
    }
    return;
}

Int32 Bsp_pga460GetMeasurement(UInt32 uartInstId,
                               UInt8  deviceId)
{
    Int32  measuredDist = (-((int32_t) 1)), retVal = BSP_SOK;
    UInt8  rxBuffer[28];
    UInt8  txBuffer[2];
    UInt32 temp1;
    Int    status;
    size_t len;

    /* Check params */
    if (uartInstId >= BSP_DEVICE_UART_INST_ID_MAX)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid UART Instance!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (uartInstId >= BSP_PGA460_MAX_DEVICE)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, " Invalid device ID!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        if ((NULL == gBspPga460Obj.uartTxHandle[uartInstId]) ||
            (NULL == gBspPga460Obj.uartRxHandle[uartInstId]))
        {
            GT_0trace(
                BspDeviceTrace, GT_ERR,
                " UART channels not created. Check UART instance!!\r\n");
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        Bsp_pga460Lock();

        /* Flush any stale data */
        if (deviceId == 0)
        {
            Bsp_pga460FlushUartRx_custom(uartInstId, 4U);
        }
        else
        {
            Bsp_pga460FlushUartRx_custom(uartInstId, 1U);
        }

        BspOsal_sleep((UInt32)2);
        gUMR = (gUMR & 0b00011111U) |  (uint8_t)(deviceId << 5U);

        txBuffer[0] = gSyncByte;
        txBuffer[1] = gUMR;

        len         = 2U;
        status      = GIO_write(
            gBspPga460Obj.uartTxHandle[uartInstId],
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
            len    = ((size_t) 3U) + (((size_t) gNumObj) * ((size_t) 4U));
            /* Taking around 5 ms */
            status = GIO_read(
                gBspPga460Obj.uartRxHandle[uartInstId],
                &rxBuffer[0U],
                &len);
            if (IOM_COMPLETED != status)
            {
                /* Timed out */
                GT_0trace(BspDeviceTrace, GT_ERR, "RX timed out!!\r\n");
                measuredDist = 0;
                retVal = BSP_EFAIL;
            }
        }

        if (BSP_SOK == retVal)
        {
            /* Calculate distance */
            temp1 =
                ((UInt32) rxBuffer[3U] << 8U) | (UInt32) rxBuffer[4U];
            measuredDist = (Int32) temp1;
        }

        Bsp_pga460Unlock();
    }
    return (measuredDist);
}

static void Bsp_pga460FlushUartRx(UInt32 uartInstId)
{
    Int    status;
    size_t len;
    UInt8  rxBuffer[10];

    while (1U)
    {
        len    = 1U;
        status = GIO_read(
            gBspPga460Obj.uartRxHandle[uartInstId],
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

static void Bsp_pga460FlushUartRx_custom(UInt32 uartInstId, UInt8 flush)
{
    Int    status;
    size_t len;
    UInt8  i, rxBuffer[10];

    for (i = 0U; i < flush; i++)
    {
        len    = 1U;
        status = GIO_read(
            gBspPga460Obj.uartRxHandle[uartInstId],
            &rxBuffer[0U],
            &len);

        if (IOM_COMPLETED == status)
        {
            GT_0trace(BspDeviceTrace, GT_DEBUG,
                      "Flushed stale data in UART!!\r\n");
        }
    }
    return;
}

static Int32 Bsp_pga460CreateUartDriver(const Bsp_Pga460InitParams *initPrms)
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
              (initPrms->numUartInst <= BSP_PGA460_MAX_UART_INST));
    GT_assert(BspDeviceTrace,
              (initPrms->numUartInst <= BSP_DEVICE_UART_INST_ID_MAX));

    /* Add device instance */
    for (instCnt = 0U; instCnt < initPrms->numUartInst; instCnt++)
    {
        uartInstId = initPrms->uartInstId[instCnt];
        GT_assert(BspDeviceTrace, (uartInstId < BSP_DEVICE_UART_INST_ID_MAX));

        DEV_Params_init(&uartDevParams);
        uartDevParams.deviceParams = &gBspPga460UartPrms;
        uartDevParams.initFxn      = NULL;
        uartDevParams.devid        = uartInstId;

        Error_init(&eb);
        iomFxns = (IOM_Fxns *) &Uart_IOMFXNS;

        DEV_construct(&gBspPga460Obj.uartDevStruct[instCnt],
                      gBspPga460UartDevName[uartInstId], iomFxns,
                      &uartDevParams,
                      &eb);

        gBspPga460Obj.isUartDevAdded[instCnt] = TRUE;
    }

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
        Semaphore_construct(&gBspPga460Obj.uartTxSemStruct[uartInstId], 0,
                                &semParams);

        SyncSem_Params_init(&syncSemParams);
        syncSemParams.sem = Semaphore_handle(
            &gBspPga460Obj.uartTxSemStruct[uartInstId]);
        SyncSem_construct(&gBspPga460Obj.uartTxSyncSemStruct[uartInstId],
                          &syncSemParams,
                          &eb);

        ioParams.sync =
            SyncSem_Handle_upCast(SyncSem_handle(&gBspPga460Obj.
                                                 uartTxSyncSemStruct[
                                                     uartInstId]));

        GT_assert(BspDeviceTrace,
                  (ioParams.numPackets <= BSP_PGA460_ASYNC_IOM_PACKET_MAX));
        ioParams.packets = &(gBspPga460Obj.uartTxIomPacket[uartInstId][0]);
        BspUtils_memset(ioParams.packets, 0,
                        ioParams.numPackets * sizeof (IOM_Packet));

        GIO_construct(&gBspPga460Obj.uartTxStruct[uartInstId],
                      gBspPga460UartDevName[uartInstId], (UInt) GIO_OUTPUT,
                      &ioParams,
                      &eb);
        gBspPga460Obj.uartTxHandle[uartInstId] = GIO_handle(
            &gBspPga460Obj.uartTxStruct[uartInstId]);
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
            Semaphore_construct(&gBspPga460Obj.uartRxSemStruct[uartInstId],
                                0,
                                &semParams);
            SyncSem_Params_init(&syncSemParams);
            syncSemParams.sem = Semaphore_handle(
                &gBspPga460Obj.uartRxSemStruct[uartInstId]);
            SyncSem_construct(
                &gBspPga460Obj.uartRxSyncSemStruct[uartInstId],
                &syncSemParams,
                &eb);

            ioParams.sync =
                SyncSem_Handle_upCast(SyncSem_handle(&gBspPga460Obj.
                                                     uartRxSyncSemStruct[
                                                        uartInstId]));

            GT_assert(BspDeviceTrace,
                      (ioParams.numPackets <=
                       BSP_PGA460_ASYNC_IOM_PACKET_MAX));
            ioParams.packets =
                &(gBspPga460Obj.uartRxIomPacket[uartInstId][0]);
            BspUtils_memset(ioParams.packets, 0,
                            ioParams.numPackets * sizeof (IOM_Packet));

            GIO_construct(&gBspPga460Obj.uartRxStruct[uartInstId],
                          gBspPga460UartDevName[uartInstId],
                          (UInt) GIO_INPUT, &ioParams,
                          &eb);
            gBspPga460Obj.uartRxHandle[uartInstId] = GIO_handle(
                &gBspPga460Obj.uartRxStruct[uartInstId]);
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

    return (retVal);
}

static Int32 Bsp_pga460DeleteUartDriver(void)
{
    Int32       retVal = BSP_SOK;
    UInt32      instCnt;
    GIO_Struct *uartGioStruct;

    /* Delete TX and RX channel */
    for (instCnt = 0U; instCnt < BSP_DEVICE_UART_INST_ID_MAX; instCnt++)
    {
        if (NULL != gBspPga460Obj.uartTxHandle[instCnt])
        {
            uartGioStruct = GIO_struct(gBspPga460Obj.uartTxHandle[instCnt]);
            GIO_destruct(uartGioStruct);
            gBspPga460Obj.uartTxHandle[instCnt] = NULL;
        }
        if (NULL != gBspPga460Obj.uartRxHandle[instCnt])
        {
            uartGioStruct = GIO_struct(gBspPga460Obj.uartRxHandle[instCnt]);
            GIO_destruct(uartGioStruct);
            gBspPga460Obj.uartRxHandle[instCnt] = NULL;
        }
    }

    /* Delete device instance */
    for (instCnt = 0U; instCnt < BSP_DEVICE_UART_INST_ID_MAX; instCnt++)
    {
        if (TRUE == gBspPga460Obj.isUartDevAdded[instCnt])
        {
            DEV_destruct(&gBspPga460Obj.uartDevStruct[instCnt]);
            gBspPga460Obj.isUartDevAdded[instCnt] = FALSE;
        }
    }

    return (retVal);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_pga460Lock(void)
{
    BspOsal_semWait(gBspPga460Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (BSP_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_pga460Unlock(void)
{
    BspOsal_semPost(gBspPga460Obj.lock);

    return (BSP_SOK);
}

static Int32 initThreshold(UInt32 uartInstId) {

    Int32  retVal = BSP_SOK;
    Int    status;
    size_t len;

        gP1_THR_0 = 0x44U;
        gP1_THR_1 = 0x44U;
        gP1_THR_2 = 0x44U;
        gP1_THR_3 = 0x44U;
        gP1_THR_4 = 0x55U;
        gP1_THR_5 = 0x55U;
        gP1_THR_6 = 0xFCU;
        gP1_THR_7 = 0xCEU;
        gP1_THR_8 = 0x62U;
        gP1_THR_9 = 0x08U;
        gP1_THR_10 = 0x63U;
        gP1_THR_11 = 0x20U;
        gP1_THR_12 = 0x2CU;
        gP1_THR_13 = 0x36U;
        gP1_THR_14 = 0x36U;
        gP1_THR_15 = 0x07U;

        gP2_THR_0 = 0x22U;
        gP2_THR_1 = 0x22U;
        gP2_THR_2 = 0x22U;
        gP2_THR_3 = 0x22U;
        gP2_THR_4 = 0x22U;
        gP2_THR_5 = 0x22U;
        gP2_THR_6 = 0x31U;
        gP2_THR_7 = 0x8CU;
        gP2_THR_8 = 0x63U;
        gP2_THR_9 = 0x18U;
        gP2_THR_10 = 0xC6U;
        gP2_THR_11 = 0x30U;
        gP2_THR_12 = 0x30U;
        gP2_THR_13 = 0x30U;
        gP2_THR_14 = 0x30U;
        gP2_THR_15 = 0x07U;

        /* Send detect command */
        uint8_t buf16[35] = {gSyncByte, gTHRBW, gP1_THR_0, gP1_THR_1, gP1_THR_2, gP1_THR_3, gP1_THR_4, gP1_THR_5, gP1_THR_6,
                                  gP1_THR_7, gP1_THR_8, gP1_THR_9, gP1_THR_10, gP1_THR_11, gP1_THR_12, gP1_THR_13, gP1_THR_14, gP1_THR_15,
                                  gP2_THR_0, gP2_THR_1, gP2_THR_2, gP2_THR_3, gP2_THR_4, gP2_THR_5, gP2_THR_6,
                                  gP2_THR_7, gP2_THR_8, gP2_THR_9, gP2_THR_10, gP2_THR_11, gP2_THR_12, gP2_THR_13, gP2_THR_14, gP2_THR_15,
                                  calcChecksum(gTHRBW)};
        len         = 35U;
        status      = GIO_write(
            gBspPga460Obj.uartTxHandle[uartInstId],
            &buf16,
            &len);

        if (IOM_COMPLETED != status)
        {
            GT_1trace(BspDeviceTrace, GT_ERR,
                      "\r\nGIO_write failed. returned : %d \r\n", status);
            retVal = BSP_EFAIL;
        }

        BspOsal_sleep((UInt32)100);

        return retVal;
}

static Int32 initTVG(UInt32 uartInstId)
{
    Int32  retVal = BSP_SOK;
    Int    status;
    size_t len;

    gRegAddr = 0x26U;
    gRegData = 0xCFU;

    uint8_t buf10[5] = {gSyncByte, gSRW, gRegAddr, gRegData, calcChecksum(gSRW)};
    len         = 5U;

    status      = GIO_write(
                  gBspPga460Obj.uartTxHandle[uartInstId],
                  &buf10,
                  &len);

    if (IOM_COMPLETED != status)
    {
        GT_1trace(BspDeviceTrace, GT_ERR,
                  "\r\nGIO_write failed. returned : %d \r\n", status);
        retVal = BSP_EFAIL;
    }

    gTVGAIN0 = 0xAAU;
    gTVGAIN1 = 0xAAU;
    gTVGAIN2 = 0xAAU;
    gTVGAIN3 = 0x82U;
    gTVGAIN4 = 0xCBU;
    gTVGAIN5 = 0x2CU;
    gTVGAIN6 = 0xB0U;

    uint8_t buf14[10] = {gSyncByte, gTVGBW, gTVGAIN0, gTVGAIN1, gTVGAIN2, gTVGAIN3, gTVGAIN4, gTVGAIN5, gTVGAIN6, calcChecksum(gTVGBW)};
    len         = 10U;
    status      = GIO_write(
                  gBspPga460Obj.uartTxHandle[uartInstId],
                  &buf14,
                  &len);
    if (IOM_COMPLETED != status)
    {
        GT_1trace(BspDeviceTrace, GT_ERR,
                  "\r\nGIO_write failed. returned : %d \r\n", status);
        retVal = BSP_EFAIL;
    }

    return retVal;
}
