/*
 *  Copyright (c) Texas Instruments Incorporated 2012
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
 *  \file st_uart.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the UART UT applications.
 */

#ifndef ST_UART_H_
#define ST_UART_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/utils/Load.h>

#include <ti/csl/soc.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>

#include <ti/sdo/edma3/drv/edma3_drv.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* UART string starts from 0 - need to add +1 for print */
#define ST_UART_DEVID_OFFSET            (1U)

#define ST_INSTANCE_ID_INV              (0xFFFFU)

#define ST_INSTANCE_ID_UART1            (BSP_DEVICE_UART_INST_ID_0)
#define ST_INSTANCE_NAME_UART1          "/uart0"
#define ST_INSTANCE_ID_UART2            (BSP_DEVICE_UART_INST_ID_1)
#define ST_INSTANCE_NAME_UART2          "/uart1"
#define ST_INSTANCE_ID_UART3            (BSP_DEVICE_UART_INST_ID_2)
#define ST_INSTANCE_NAME_UART3          "/uart2"

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
#define ST_INSTANCE_ID_UART4            (BSP_DEVICE_UART_INST_ID_3)
#define ST_INSTANCE_NAME_UART4          "/uart3"
#define ST_INSTANCE_ID_UART5            (BSP_DEVICE_UART_INST_ID_4)
#define ST_INSTANCE_NAME_UART5          "/uart4"
#define ST_INSTANCE_ID_UART6            (BSP_DEVICE_UART_INST_ID_5)
#define ST_INSTANCE_NAME_UART6          "/uart5"
#else
#define ST_INSTANCE_ID_UART4            (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART4          "/invalid"
#define ST_INSTANCE_ID_UART5            (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART5          "/invalid"
#define ST_INSTANCE_ID_UART6            (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART6          "/invalid"
#endif  /* Tda2xx || TI814x */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#define ST_INSTANCE_ID_UART7            (BSP_DEVICE_UART_INST_ID_6)
#define ST_INSTANCE_NAME_UART7          "/uart6"
#define ST_INSTANCE_ID_UART8            (BSP_DEVICE_UART_INST_ID_7)
#define ST_INSTANCE_NAME_UART8          "/uart7"
#define ST_INSTANCE_ID_UART9            (BSP_DEVICE_UART_INST_ID_8)
#define ST_INSTANCE_NAME_UART9          "/uart8"
#define ST_INSTANCE_ID_UART10           (BSP_DEVICE_UART_INST_ID_9)
#define ST_INSTANCE_NAME_UART10         "/uart9"
#else
#define ST_INSTANCE_ID_UART7            (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART7          "/invalid"
#define ST_INSTANCE_ID_UART8            (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART8          "/invalid"
#define ST_INSTANCE_ID_UART9            (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART9          "/invalid"
#define ST_INSTANCE_ID_UART10           (ST_INSTANCE_ID_INV)
#define ST_INSTANCE_NAME_UART10         "/invalid"
#endif  /* Tda2xx */

#define ST_UART_INST_MAX                (CSL_UART_PER_CNT)
#define ST_UART_MAX_HANDLE_PER_INST     (3U)
#define ST_UART_MAX_CH_PER_HANDLE       (2U)
#define ST_UART_MAX_CH_PER_INST         (ST_UART_MAX_HANDLE_PER_INST * ST_UART_MAX_CH_PER_HANDLE)

/* Maximum number of handle for memory allocation. */
#define ST_UART_MAX_HANDLE              (ST_UART_MAX_HANDLE_PER_INST * \
                                         ST_UART_INST_MAX)

/* Maximum number of channels for memory allocation. */
#define ST_UART_MAX_CH                  (ST_UART_MAX_CH_PER_INST * \
                                         ST_UART_INST_MAX)

/* Application name string used in print statements. */
#define APP_NAME                        "ST_UART"

#define UART_ST_TX_TEST_STRING                                              \
                "This is the test string used for UART TX tests!!"          \
                " ABCDEFGHIJKLMNOPQRSTUVWXYZ"                               \
                " abcdefghijklmnopqrstuvwxyz"                               \
                " 12345678900987654321"

/* This is used for comparing the received input */
#define UART_ST_RX_TEST_STRING                                                          \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE ** "     \
    "BIOSPSP UART SAMPLE APPLICATION. **  THIS FILE CONTAINS 1000 BYTES OR MORE **  "   \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE **  "    \
    "BIOSPSP UART SAMPLE APPLICATION. ** THIS FILE CONTAINS 1000 BYTES OR MORE **  "    \
    "BIOSPSP UART SAMPLE APPLICATION. **  THIS FILE CONTAINS 1000 BYTES OR MORE ** "    \
    "BIOSPSP UART SAMPLE APPLICATION. **** THIS IS END OF DEMONSTRATION ****"

/* Expected performance - in percentage of UART baudrate */
#define ST_UART_EXPECTED_PERFORMANCE    (80U)

/* Default values */
#define ST_UART_USE_DEF                 (0xFAFAFAFAU)
#define DEF_UART_OPMODE                 (UART_OPMODE_POLLED)
#define DEF_UART_BAUDRATE               (UART_BAUDRATE_115_2K)
#define DEF_UART_CHARLEN                (UART_CHARLEN_8)
#define DEF_UART_STOPBITS               (UART_NUMSTOPBITS_1)
#define DEF_UART_PARITY                 (UART_PARITY_NO)
#define DEF_UART_FCTYPE                 (UART_FCTYPE_NONE)
#define DEF_UART_FCPARAMRX              (UART_FCPARAM_RXNONE)
#define DEF_UART_FCPARAMTX              (UART_FCPARAM_TXNONE)
#define DEF_UART_CHUNKSIZE              (BSP_UART_FIFO_SIZE)
#define DEF_UART_RXTRIGLVL              (UART_RXTRIGLVL_8)
#define DEF_UART_TXTRIGLVL              (UART_TXTRIGLVL_56)
#define DEF_UART_POLLEDMODE_TIMEOUT     (0xFFFFFFFFU)
#define DEF_LOOP_CNT_EVM                (1U)
#define DEF_LOOP_CNT                    (1U)    /* For Zebu/Sim */
#define DEF_LOOP_CNT_PERFORMANCE        (1000U)
#define DEF_LOOP_CNT_RANDOMMODE         (500U)
#define DEF_OPEN_CLOSE_CNT              (1U)
#define DEF_TX_BYTESPERSUBMIT           (strlen(UART_ST_TX_TEST_STRING))
#define DEF_RX_BYTESPERSUBMIT           (strlen(UART_ST_RX_TEST_STRING))
#define DEF_INCREMENT_FACTOR            (1U)

#define ST_UART_SOC_ID_TDA2XX               (BSP_PLATFORM_SOC_ID_TDA2XX |      \
                                                BSP_PLATFORM_SOC_ID_DRA75X)

#define ST_UART_SOC_ID_TDA2XX_2PX           (ST_UART_SOC_ID_TDA2XX |           \
                                                BSP_PLATFORM_SOC_ID_TDA2PX)

#define ST_UART_SOC_ID_TDA2XX_2PX_2EX       (ST_UART_SOC_ID_TDA2XX_2PX |       \
                                                BSP_PLATFORM_SOC_ID_TDA2EX)

#define ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X   (ST_UART_SOC_ID_TDA2XX_2PX_2EX |\
                                                BSP_PLATFORM_SOC_ID_TI814X)

#define ST_UART_SOC_ID_TDA3XX               (BSP_PLATFORM_SOC_ID_TDA3XX)

#define DEF_SOC_ID                          (ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X |\
                                                ST_UART_SOC_ID_TDA3XX)

/* Count used for open/close test cases */
#define LOOP_CNT_OC                     (1U)
#define OPEN_CLOSE_CNT_OC               (125U)
#define TX_BYTESPERSUBMIT_OC            (100U)
#define RX_BYTESPERSUBMIT_OC            (8U)

/* Timeout every X seconds - assumes timer clock is 425MHz */
#define POLLEDMODE_TIMEOUT_2SEC         (425000000U * 2U)
#define POLLEDMODE_TIMEOUT_10SEC        (0xFFFFFFFEU)   /* Boundary condition */

/* Loop count used for timestamp test cases */
#define LOOP_CNT_TIMESTAMP              (10U)

#define ST_UART_TEST                    (0x00000001)
#define ST_UART_CTRL_TEST               (0x00000010)

#define ST_UART_TX_BUF_SIZE             (50U * 1024U)
#define ST_UART_RX_BUF_SIZE             (100U * 1024U)

#define ST_UART_PRINT_BUFSIZE           (300U)

/* In ms */
#define ST_UART_MAX_RANDOM_TIMEOUT      (100U)

/* Used for alignedment of DMA buffer */
#define CACHE_LINESIZE                  (128U)
#define CACHE_LINESIZE_MASK             (~0x7FU)

/**
 *  \brief Test types.
 */
typedef enum
{
    ST_TT_SANITY      = 0x01,
    ST_TT_REGRESSION  = 0x02,
    ST_TT_FULL        = 0x04,
    ST_TT_FUNCTIONAL  = 0x08,
    ST_TT_STRESS      = 0x10,
    ST_TT_NEGATIVE    = 0x20,
    ST_TT_PERFORMANCE = 0x40,
    ST_TT_MISC        = 0x80,
    ST_TT_API         = 0x100
} st_TestType;

/**
 *  \brief Test case types.
 */
typedef enum
{
    ST_UART_TCT_TX = 0,
    ST_UART_TCT_RX,
    ST_UART_TCT_RX_TO_TX,
    ST_UART_TCT_RX_TX,
    ST_UART_TCT_API,
    ST_UART_TCT_IOCTL,
    ST_UART_TCT_HALT
} st_UartTestCaseType;

/**
 *  UART UT channel config IDs.
 */
typedef enum
{
    ST_UART_CCID_NONE,
    /**< No channel configuration. */
    ST_UART_CCID_DEFAULT,
    ST_UART_CCID_RAMP_UP,
    ST_UART_CCID_RAMP_DOWN,
    ST_UART_CCID_RX_OPEN_CLOSE,
    ST_UART_CCID_TX_OPEN_CLOSE
} st_UartChCfgId;

/**
 *  UART UT handle config IDs.
 */
typedef enum
{
    ST_UART_HCID_NONE,
    ST_UART_HCID_DEFAULT,
    ST_UART_HCID_POLLED_DEFAULT,
    ST_UART_HCID_POLLED_BAUDRATE_2400,
    ST_UART_HCID_POLLED_BAUDRATE_4800,
    ST_UART_HCID_POLLED_BAUDRATE_9600,
    ST_UART_HCID_POLLED_BAUDRATE_19200,
    ST_UART_HCID_POLLED_BAUDRATE_38400,
    ST_UART_HCID_POLLED_BAUDRATE_57600,
    ST_UART_HCID_POLLED_BAUDRATE_115200,
    ST_UART_HCID_POLLED_BAUDRATE_3686400,
    ST_UART_HCID_POLLED_STOPBITS_1,
    ST_UART_HCID_POLLED_STOPBITS_1_5,
    ST_UART_HCID_POLLED_STOPBITS_2,
    ST_UART_HCID_POLLED_PARITY_NONE,
    ST_UART_HCID_POLLED_PARITY_EVEN,
    ST_UART_HCID_POLLED_PARITY_ODD,
    ST_UART_HCID_POLLED_PARITY_FORCED0,
    ST_UART_HCID_POLLED_PARITY_FORCED1,
    ST_UART_HCID_POLLED_CHARLEN_5,
    ST_UART_HCID_POLLED_CHARLEN_6,
    ST_UART_HCID_POLLED_CHARLEN_7,
    ST_UART_HCID_POLLED_CHARLEN_8,
    ST_UART_HCID_POLLED_OPEN_CLOSE,
    ST_UART_HCID_POLLED_PERFORMANCE,
    ST_UART_HCID_POLLED_FIFO_ENABLE,
    ST_UART_HCID_POLLED_FIFO_DISABLE,
    ST_UART_HCID_POLLED_TIMEOUT_2SEC,
    ST_UART_HCID_POLLED_TIMEOUT_10SEC,
    ST_UART_HCID_POLLED_RANDOMLOOPCNT_ENABLE,
    ST_UART_HCID_POLLED_CHUNKSIZE_1,
    ST_UART_HCID_POLLED_CHUNKSIZE_32,
    ST_UART_HCID_POLLED_CHUNKSIZE_64,
    ST_UART_HCID_POLLED_CHUNKSIZE_INVALID,

    ST_UART_HCID_INTERRUPT_DEFAULT,
    ST_UART_HCID_INTERRUPT_BAUDRATE_2400,
    ST_UART_HCID_INTERRUPT_BAUDRATE_4800,
    ST_UART_HCID_INTERRUPT_BAUDRATE_9600,
    ST_UART_HCID_INTERRUPT_BAUDRATE_19200,
    ST_UART_HCID_INTERRUPT_BAUDRATE_38400,
    ST_UART_HCID_INTERRUPT_BAUDRATE_57600,
    ST_UART_HCID_INTERRUPT_BAUDRATE_115200,
    ST_UART_HCID_INTERRUPT_BAUDRATE_3686400,
    ST_UART_HCID_INTERRUPT_STOPBITS_1,
    ST_UART_HCID_INTERRUPT_STOPBITS_1_5,
    ST_UART_HCID_INTERRUPT_STOPBITS_2,
    ST_UART_HCID_INTERRUPT_PARITY_NONE,
    ST_UART_HCID_INTERRUPT_PARITY_EVEN,
    ST_UART_HCID_INTERRUPT_PARITY_ODD,
    ST_UART_HCID_INTERRUPT_PARITY_FORCED0,
    ST_UART_HCID_INTERRUPT_PARITY_FORCED1,
    ST_UART_HCID_INTERRUPT_CHARLEN_5,
    ST_UART_HCID_INTERRUPT_CHARLEN_6,
    ST_UART_HCID_INTERRUPT_CHARLEN_7,
    ST_UART_HCID_INTERRUPT_CHARLEN_8,
    ST_UART_HCID_INTERRUPT_OPEN_CLOSE,
    ST_UART_HCID_INTERRUPT_PERFORMANCE,
    ST_UART_HCID_INTERRUPT_FIFO_ENABLE,
    ST_UART_HCID_INTERRUPT_FIFO_DISABLE,
    ST_UART_HCID_INTERRUPT_RXTRIGLVL_8,
    ST_UART_HCID_INTERRUPT_RXTRIGLVL_16,
    ST_UART_HCID_INTERRUPT_RXTRIGLVL_56,
    ST_UART_HCID_INTERRUPT_RXTRIGLVL_60,
    ST_UART_HCID_INTERRUPT_TXTRIGLVL_8,
    ST_UART_HCID_INTERRUPT_TXTRIGLVL_16,
    ST_UART_HCID_INTERRUPT_TXTRIGLVL_32,
    ST_UART_HCID_INTERRUPT_TXTRIGLVL_56,
    ST_UART_HCID_INTERRUPT_RANDOMLOOPCNT_ENABLE,
    ST_UART_HCID_INTERRUPT_CHUNKSIZE_1,
    ST_UART_HCID_INTERRUPT_CHUNKSIZE_32,
    ST_UART_HCID_INTERRUPT_CHUNKSIZE_64,
    ST_UART_HCID_INTERRUPT_CHUNKSIZE_INVALID,

    ST_UART_HCID_DMA_DEFAULT,
    ST_UART_HCID_DMA_BAUDRATE_2400,
    ST_UART_HCID_DMA_BAUDRATE_4800,
    ST_UART_HCID_DMA_BAUDRATE_9600,
    ST_UART_HCID_DMA_BAUDRATE_19200,
    ST_UART_HCID_DMA_BAUDRATE_38400,
    ST_UART_HCID_DMA_BAUDRATE_57600,
    ST_UART_HCID_DMA_BAUDRATE_115200,
    ST_UART_HCID_DMA_BAUDRATE_3686400,
    ST_UART_HCID_DMA_STOPBITS_1,
    ST_UART_HCID_DMA_STOPBITS_1_5,
    ST_UART_HCID_DMA_STOPBITS_2,
    ST_UART_HCID_DMA_PARITY_NONE,
    ST_UART_HCID_DMA_PARITY_EVEN,
    ST_UART_HCID_DMA_PARITY_ODD,
    ST_UART_HCID_DMA_PARITY_FORCED0,
    ST_UART_HCID_DMA_PARITY_FORCED1,
    ST_UART_HCID_DMA_CHARLEN_5,
    ST_UART_HCID_DMA_CHARLEN_6,
    ST_UART_HCID_DMA_CHARLEN_7,
    ST_UART_HCID_DMA_CHARLEN_8,
    ST_UART_HCID_DMA_OPEN_CLOSE,
    ST_UART_HCID_DMA_PERFORMANCE,
    ST_UART_HCID_DMA_FIFO_ENABLE,
    ST_UART_HCID_DMA_FIFO_ENABLE_PERFORMANCE,
    ST_UART_HCID_DMA_FIFO_DISABLE,
    ST_UART_HCID_DMA_FIFO_DISABLE_PERFORMANCE,
    ST_UART_HCID_DMA_RXTRIGLVL_8,
    ST_UART_HCID_DMA_RXTRIGLVL_16,
    ST_UART_HCID_DMA_RXTRIGLVL_56,
    ST_UART_HCID_DMA_RXTRIGLVL_60,
    ST_UART_HCID_DMA_TXTRIGLVL_8,
    ST_UART_HCID_DMA_TXTRIGLVL_16,
    ST_UART_HCID_DMA_TXTRIGLVL_32,
    ST_UART_HCID_DMA_TXTRIGLVL_56,
    ST_UART_HCID_DMA_RANDOMLOOPCNT_ENABLE,
    ST_UART_HCID_DMA_CHUNKSIZE_1,
    ST_UART_HCID_DMA_CHUNKSIZE_32,
    ST_UART_HCID_DMA_CHUNKSIZE_64,
    ST_UART_HCID_DMA_CHUNKSIZE_INVALID,

    ST_UART_HCID_MISC_TIMESTAMP
} st_UartHandleCfgId;

/**
 *  UART UT bytes per transfer type.
 */
typedef enum
{
    ST_UART_BPS_FIXED,
    ST_UART_BPS_RAMP_UP,
    ST_UART_BPS_RAMP_DOWN
} st_UartBytesPerSubmitId;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* Forward declaration. */
typedef struct st_SystemCtrl_t st_SystemCtrl;

/**
 *  \brief Test parameters for a channel.
 */
typedef struct
{
    st_UartChCfgId              chCfgId;
    /**< Channel configuration ID. */
    Uart_ChanParams             chPrms;
    /**< UART driver channel parameter. */
    st_UartBytesPerSubmitId     bytesPerSubmitId;
    /**< Bytes per submit ID. */
    UInt32                      maxBytesPerSubmit;
    /**< Max number of bytes to transfer per driver call. This is equal to the
     *   bytes to receive in case of RX channel. */
    UInt32                      incrementFactor;
    /**< Number of bytes to increment/decrement per submit in case of
     *   ramp up/down. */
} st_UartChCfg;

/**
 *  \brief Test parameters for a handle.
 */
typedef struct
{
    st_UartHandleCfgId handleCfgId;
    /**< Channel configuration ID. */
    Uart_Params       uartPrms;
    /**< UART instance parameter. */

    UInt32            loopCnt;
    /**< Loop count for the app. */
    UInt32            openCloseCnt;
    /**< Number of times to do open/close operation. */
    Bool              timeStampEnable;
    /**< Bool for the timestamp print or not. */
    Bool              prfEnable;
    /**< Enable performance prints. */
    Bool              randomModeEnable;
    /**< Enable random TX mode. */
} st_UartHandleCfg;

/**
 *  \brief Test case parameter structure.
 */
typedef struct
{
    Bool                    enableTest;
    /**< Whether test case should be executed or not. */
    UInt32                  testCaseId;
    /**< Tesd case ID. */
    st_UartTestCaseType     testCaseType;
    /**< Type of test case to run. */
    char                   *reqId;
    /**< Requirements covered by this test case. */
    char                   *testCaseName;
    /**< Test case name. */
    char                   *userInfo;
    /**< Test case user Info. */
    char                   *disableReason;
    /**< Reason string for disabling a test case. */

    UInt32                  numHandles;
    /**< Number of handles to test. */
    UInt32                  devId[ST_UART_MAX_HANDLE];
    /**< Uart device instance number for back reference. */
    char                   *devName[ST_UART_MAX_HANDLE];
    /**< Instance ID of the driver. */
    st_UartHandleCfgId      handleCfgId[ST_UART_MAX_HANDLE];
    /**< UART handle config IDs for each of the handle. */

    UInt32                  txNumCh[ST_UART_MAX_HANDLE];
    /**< TX Number of channels per handle to test. */
    st_UartChCfgId          txChCfgId[ST_UART_MAX_CH];
    /**< UART TX channel config IDs for all the handles.
     *   Handle 0 channel configs will be first (0 to (numCh[0] - 1)),
     *   (numCh[0] to (numCh[1] - 1)) and so on. */
    UInt32                  rxNumCh[ST_UART_MAX_HANDLE];
    /**< RX Number of channels per handle to test. */
    st_UartChCfgId          rxChCfgId[ST_UART_MAX_CH];
    /**< UART RX channel config IDs for all the handles.
     *   Handle 0 channel configs will be first (0 to (numCh[0] - 1)),
     *   (numCh[0] to (numCh[1] - 1)) and so on. */

    Bool                    printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    UInt32                  testType;
    /**< Type of test  - like BFT, stress etc... */
    UInt32                  socId;
    /**< Or of all applicable SOC ID - used for disabling test case */

    /*
     * Below variables are initialized in code and not in table!!
     */
    Bool                    isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32                   testResult;
    /**< Test result. */
} st_UartTestCaseParams;

/**
 *  \brief UART channel object.
 */
typedef struct
{
    UInt32              chId;
    /**< Channel ID. */
    st_UartChCfg        chCfg;
    /**< Channel configuration. */

    GIO_Handle          chHandle;
    /**< Channel handle. */
    char               *inBuffer;
    /**< Input buffer. */
    char               *submitBuffer;
    /**< TX or RX buffer. */

    UInt32              submittedRequestTx;
    /**< Number of submitted TX request. */
    UInt32              submittedRequestRx;
    /**< Number of submitted RX request. */
    UInt64              bytesTx;
    /**< Number of bytes transferred for this run. This is used in performance
     *   calculation. */
    UInt64              bytesRx;
    /**< Number of bytes received for this run. This is used in performance
     *   calculation. */
} st_UartChObj;

/**
 *  \brief UART handle object.
 */
typedef struct
{
    const st_UartTestCaseParams *testPrms;
    /**< Pointer to test params for reference. */
    UInt32                      taskId;
    /**< Task ID. */
    Int32                       testResult;
    /**< Test Result. Based on this testbench will print Pass/Fail. */
    UInt32                      txBps;
    /**< Bytes per second transferred for this run. */
    UInt32                      rxBps;
    /**< Bytes per second received for this run. */

    UInt32                      devId;
    /**< Uart device instance number for back reference. */
    char                       *devName;
    /**< Instance ID of the driver to open. */
    st_UartHandleCfg            handleCfg;
    /**< Handle configuration. */

    const st_SystemCtrl        *sysCtrl;
    /**< Pointer to system control. */
    UInt32                      traceMask;
    /**< Masks for the debug prints. */

    UInt32                      txStartChIdx;
    /**< TX Index into the channel config for all the handles. */
    UInt32                      txNumCh;
    /**< TX Number of channels for this handle. */
    st_UartChObj                txChObj[ST_UART_MAX_CH_PER_HANDLE];
    /**< TX Channel object. */

    UInt32                      rxStartChIdx;
    /**< RX Index into the channel config for all the handles. */
    UInt32                      rxNumCh;
    /**< RX Number of channels for this handle. */
    st_UartChObj                rxChObj[ST_UART_MAX_CH_PER_HANDLE];
    /**< RX Channel object. */

    BspUtils_PrfTsHndl         *prfTsHandle;
    /**< Performance utils handle. */

    UInt32                      completedLoopCnt;
    /**< Total number of completed frames. */

    Bsp_PlatformId              platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev          cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId                 boardId;
    /**< Board identifier. */
} st_UartHandleObj;

/**
 *  \brief Structure used for UART UT control parameters.
 */
struct st_SystemCtrl_t
{
    Uart_OpMode         opMode;
    /**< Default operating mode. */
    Uart_BaudRate       baudRate;
    /**< Default Baudrate. */
    Uart_CharLen        charLen;
    /**< Default Character Length. */
    Uart_NumStopBits    stopBits;
    /**< Default number of stop bits. */
    Uart_Parity         parity;
    /**< Default parity. */
    Uart_FcType         fcType;
    /**< Default flow control type. */
    Uart_FcParamRx      fcParamRx;
    /**< Default RTS flow control. */
    Uart_FcParamTx      fcParamTx;
    /**< Default CTS flow control. */
    UInt32              chunkSize;
    /**< Default chunksize in FIFO mode. */
    Uart_RxTrigLvl      rxThreshold;
    /**< Default RX trigger level. */
    Uart_TxTrigLvl      txThreshold;
    /**< Default TX trigger level. */
    UInt32              rxBytesPerSubmit;
    /**< Default bytes to RX per submit call. */
    UInt32              txBytesPerSubmit;
    /**< Default bytes to TX per submit call. */
    UInt32              polledModeTimeout;
    /**< Timeout used in polled mode  */

    UInt32              loopCnt;
    /**< Default loop count. */
    UInt32              openCloseCnt;
    /**< Number of times to do open/close operation. */
    UInt32              rtPrintEnable;
    /**< Enables runtime remote prints like VENC underflow status etc. */

    Bool                skipRxTests;
    /**< Flag to skip all RX test cases so that all TX test cases could be
     *   auto run without user intervention. */
    Bool                skipTxOnlyTests;
    /**< Flag to skip all TX only test cases so that all RX test cases could be
     *   auto run in case all TX test cases is already run by setting
     *   skipRxTests to SKIP earlier. */
    Bool                skipHaltTests;
    /**< Flag to skip the halt test cases. */
};

/**
 *  \brief Structure used for UART UT object common for all the tasks.
 */
typedef struct
{
    st_SystemCtrl      sysCtrl;
    /**< System control information. */

    UInt32             skipCount;
    /**< Number of test cases skipped because of platform/user settings. */
    UInt32             disableCount;
    /**< Number of test cases disabled because of any bug etc. */

    UInt32             traceMask;
    /**< Masks for the debug prints. */

    Bsp_PlatformId     platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId        boardId;
    /**< Board identifier. */
} st_UartUtObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Parser functions
 */
Int32 st_uartParser(void);

/*
 * UART test case functions
 */
Int32 st_uartRxTxTestCase(st_UartHandleObj *hObj);

/*
 * UART generic test case functions
 */
Int32 st_uartCreateDevice(st_UartHandleObj *hObj);
Int32 st_uartDeleteDevice(st_UartHandleObj *hObj);

/*
 * UART platform specific functions
 */
Int32 st_uartEnableUartInstance(const st_UartUtObj *utObj, Int32 devId);
Int32 st_uartDisableUartInstance(const st_UartUtObj *utObj, Int32 devId);

/*
 * UART common functions
 */
Int32 st_uartInitVariables(st_UartHandleObj *hObj);
void st_uartFreeVariables(st_UartHandleObj *hObj);

void st_uartPrintChPrms(const st_UartHandleObj *hObj);
Int32 st_uartCalcPerformance(st_UartHandleObj *hObj, UInt32 durationMs);
Int32 st_uartPrintStatus(st_UartHandleObj *hObj, Bool rtPrintEnable);
Int32 st_uartCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                           UInt32                        traceMask);

void st_logTestResult(const st_UartUtObj *utObj,
                      Int32              testResult,
                      UInt32             testCaseId,
                      char              *testcaseInfo);
void st_printTestResult(const st_UartUtObj *utObj,
                        UInt32             skipCount,
                        UInt32             disableCount);
void st_resetTestResult(void);

const char *st_uartGetOpModeString(Int32 opMode);
const char *st_uartGetBaudRateString(Int32 baudRate);
const char *st_uartGetCharLenString(Int32 charLen);
const char *st_uartGetStopBitsString(Int32 stopBits);
const char *st_uartGetParityString(Int32 parity);
const char *st_uartGetFcTypeString(Int32 fcType);
const char *st_uartGetFcParamRxString(Int32 fcParamRx);
const char *st_uartGetFcParamTxString(Int32 fcParamTx);
const char *st_uartGetRxThresholdString(Int32 rxThreshold);
const char *st_uartGetTxThresholdString(Int32 txThreshold);

static inline UInt32 st_uartGetMax(UInt32 a, UInt32 b)
{
    UInt32 max;

    max = a;
    if (b > a)
    {
        max = b;
    }

    return (max);
}

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

extern EDMA3_DRV_Handle         gEdmaHandle;
extern volatile Bool            gUartUtStopTx;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ST_UART_H_ */
