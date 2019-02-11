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
 *  \file st_uartCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_uart.h>

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

static void st_vpsSetDefaultChPrms(const st_UartHandleObj *hObj,
                                   st_UartChObj           *chObj,
                                   UInt32                  chNum);
static Int32 st_uartGetExpectedBps(const st_UartHandleObj *hObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static UInt32        glbTestCounter = 0;
static UInt32        glbPassCounter = 0;
static UInt32        glbFailCounter = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_uartInitVariables
 *  Initialize the global variables and frame pointers.
 */
Int32 st_uartInitVariables(st_UartHandleObj *hObj)
{
    Int32              retVal = BSP_SOK;
    Int32              chCnt;
    st_UartChObj      *chObj;
    char              *tempPtr;
    UInt32             inStrLen, strCopied;
    hObj->prfTsHandle      = NULL;
    hObj->completedLoopCnt = 0u;
    for (chCnt = 0u; chCnt < ST_UART_MAX_CH_PER_HANDLE; chCnt++)
    {
        /* Init channel params */
        chObj = &hObj->txChObj[chCnt];
        st_vpsSetDefaultChPrms(hObj, chObj, chCnt);

        /* Alloc TX buffer and copy the test string */
        chObj->inBuffer =
            BspUtils_memAlloc(ST_UART_TX_BUF_SIZE, CACHE_LINESIZE);
        GT_assert(hObj->traceMask, (chObj->inBuffer != NULL));

        /* String fill the entire buffer with valid user string */
        tempPtr = chObj->inBuffer;
        strCopied = 0U;
        inStrLen = strlen(UART_ST_TX_TEST_STRING);
        while (1U)
        {
            if ((strCopied + inStrLen + 1U) < ST_UART_TX_BUF_SIZE)
            {
                strcpy(tempPtr, UART_ST_TX_TEST_STRING);
            }
            else
            {
                strncpy(
                    tempPtr,
                    UART_ST_TX_TEST_STRING,
                    (ST_UART_TX_BUF_SIZE - strCopied));
                break;
            }
            tempPtr += inStrLen;
            strCopied += inStrLen;
        }

        chObj->submitBuffer =
            BspUtils_memAlloc(ST_UART_TX_BUF_SIZE, CACHE_LINESIZE);
        GT_assert(hObj->traceMask, (chObj->submitBuffer != NULL));
    }
    for (chCnt = 0u; chCnt < ST_UART_MAX_CH_PER_HANDLE; chCnt++)
    {
        /* Init channel params */
        chObj = &hObj->rxChObj[chCnt];
        st_vpsSetDefaultChPrms(hObj, chObj, chCnt);

        /* Alloc RX buffer and memset to zero */
        chObj->inBuffer =
            BspUtils_memAlloc(ST_UART_RX_BUF_SIZE, CACHE_LINESIZE);
        GT_assert(hObj->traceMask, (chObj->inBuffer != NULL));
        memset(chObj->inBuffer, 0, ST_UART_RX_BUF_SIZE);

        chObj->submitBuffer =
            BspUtils_memAlloc(ST_UART_RX_BUF_SIZE, CACHE_LINESIZE);
        GT_assert(hObj->traceMask, (chObj->submitBuffer != NULL));
    }

    hObj->prfTsHandle = BspUtils_prfTsCreate(APP_NAME);
    GT_assert(hObj->traceMask, (hObj->prfTsHandle != NULL));

    if (BSP_SOK != retVal)
    {
        st_uartFreeVariables(hObj);
    }

    /* Print channel info */
    st_uartPrintChPrms(hObj);

    return (retVal);
}

/**
 *  st_uartFreeVariables
 *  Free the allocated handles and buffers.
 */
void st_uartFreeVariables(st_UartHandleObj *hObj)
{
    Int32              chCnt;
    st_UartChObj      *chObj;

    if (NULL != hObj->prfTsHandle)
    {
        BspUtils_prfTsDelete(hObj->prfTsHandle);
        hObj->prfTsHandle = NULL;
    }
    for (chCnt = 0u; chCnt < ST_UART_MAX_CH_PER_HANDLE; chCnt++)
    {
        chObj = &hObj->txChObj[chCnt];
        BspUtils_memFree(chObj->inBuffer, ST_UART_TX_BUF_SIZE);
        chObj->inBuffer = NULL;
        BspUtils_memFree(chObj->submitBuffer, ST_UART_TX_BUF_SIZE);
        chObj->submitBuffer = NULL;
    }
    for (chCnt = 0u; chCnt < ST_UART_MAX_CH_PER_HANDLE; chCnt++)
    {
        chObj = &hObj->rxChObj[chCnt];
        BspUtils_memFree(chObj->inBuffer, ST_UART_RX_BUF_SIZE);
        chObj->inBuffer = NULL;
        BspUtils_memFree(chObj->submitBuffer, ST_UART_RX_BUF_SIZE);
        chObj->submitBuffer = NULL;
    }

    return;
}

/**
 *  st_uartPrintChPrms
 *  \brief Prints the channel parameter.
 */
void st_uartPrintChPrms(const st_UartHandleObj *hObj)
{
    UInt32             chCnt;
    const st_UartChObj *chObj;
    static char        printBuf[ST_UART_PRINT_BUFSIZE];

    GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Device ID         : %d\r\n", (hObj->devId + ST_UART_DEVID_OFFSET));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Instance          : %s\r\n", hObj->devName);
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Op Mode           : %s\r\n",
        st_uartGetOpModeString(hObj->handleCfg.uartPrms.opMode));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Baud Rate         : %s\r\n",
        st_uartGetBaudRateString(hObj->handleCfg.uartPrms.baudRate));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Stop Bits         : %s\r\n",
        st_uartGetStopBitsString(hObj->handleCfg.uartPrms.stopBits));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Char Length       : %s\r\n",
        st_uartGetCharLenString(hObj->handleCfg.uartPrms.charLen));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Parity            : %s\r\n",
        st_uartGetParityString(hObj->handleCfg.uartPrms.parity));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Flow Control      : %s\r\n",
        st_uartGetFcTypeString(hObj->handleCfg.uartPrms.fc.fcType));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " RX Flow Control   : %s\r\n",
        st_uartGetFcParamRxString(hObj->handleCfg.uartPrms.fc.fcParamRx));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " TX Flow Control   : %s\r\n",
        st_uartGetFcParamTxString(hObj->handleCfg.uartPrms.fc.fcParamTx));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " Chunk Size        : %d\r\n", hObj->handleCfg.uartPrms.chunkSize);
    GT_1trace(hObj->traceMask, GT_INFO1,
        " RX Threshold      : %s\r\n",
        st_uartGetRxThresholdString(hObj->handleCfg.uartPrms.rxThreshold));
    GT_1trace(hObj->traceMask, GT_INFO1,
        " TX Threshold      : %s\r\n",
        st_uartGetTxThresholdString(hObj->handleCfg.uartPrms.txThreshold));

    GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(hObj->traceMask, GT_INFO1, " Ch.No | BytesToTransfer\r\n");
    GT_0trace(hObj->traceMask, GT_INFO1, " -----------------------\r\n");
    for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
    {
        chObj = &hObj->txChObj[chCnt];
        snprintf(
            printBuf, sizeof (printBuf),
            " TX %0.2d   %5d",
            chObj->chId, chObj->chCfg.maxBytesPerSubmit);

        GT_1trace(hObj->traceMask, GT_INFO1, "%s\r\n", printBuf);
    }
    for (chCnt = 0u; chCnt < hObj->rxNumCh; chCnt++)
    {
        chObj = &hObj->rxChObj[chCnt];
        snprintf(
            printBuf, sizeof (printBuf),
            " RX %0.2d   %5d",
            chObj->chId, chObj->chCfg.maxBytesPerSubmit);

        GT_1trace(hObj->traceMask, GT_INFO1, "%s\r\n", printBuf);
    }

    GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");

    return;
}

/**
 *  st_uartCalcPerformance
 */
Int32 st_uartCalcPerformance(st_UartHandleObj *hObj, UInt32 durationMs)
{
    UInt32       chCnt;
    UInt32       percentTx, percentRx, expectedBps;
    UInt64       totalTxBytes, totalRxBytes;
    st_UartChObj *chObj;

    totalTxBytes = 0u;
    for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
    {
        chObj    = &hObj->txChObj[chCnt];
        totalTxBytes  += chObj->bytesTx;
    }
    totalRxBytes = 0u;
    for (chCnt = 0u; chCnt < hObj->rxNumCh; chCnt++)
    {
        chObj    = &hObj->rxChObj[chCnt];
        totalRxBytes  += chObj->bytesRx;
    }

    /* Calculate performance */
    hObj->txBps = (UInt32)
        ((totalTxBytes * (UInt64) 1000) / (UInt64) durationMs);
    hObj->rxBps = (UInt32)
        ((totalRxBytes * (UInt64) 1000) / (UInt64) durationMs);

    expectedBps = st_uartGetExpectedBps(hObj);
    percentTx = (hObj->txBps * 100) / expectedBps;
    percentRx = (hObj->rxBps * 100) / expectedBps;
    GT_0trace(hObj->traceMask, GT_INFO, " \r\n");
    if (hObj->txBps > 0)
    {
        GT_4trace(
            hObj->traceMask, GT_INFO,
            " %s: TX Performance (Bytes Per Second): %d BP/s (%d%c) \r\n",
            APP_NAME, hObj->txBps, percentTx, '%');
        if (percentTx < ST_UART_EXPECTED_PERFORMANCE)
        {
            GT_5trace(
                hObj->traceMask, GT_INFO,
                " %s: Warning: TX Performance (%d%c) is less than expected "
                "(%d%c)!!\r\n",
                APP_NAME, percentTx, '%', ST_UART_EXPECTED_PERFORMANCE, '%');
        }
        if (percentTx > 100U)
        {
            GT_4trace(
                hObj->traceMask, GT_INFO,
                " %s: Warning: TX Performance (%d%c) is more than 100%c!!\r\n",
                APP_NAME, percentTx, '%', '%');
        }
    }
    if (hObj->rxBps > 0)
    {
        GT_4trace(
            hObj->traceMask, GT_INFO,
            " %s: RX Performance (Bytes Per Second): %d BP/s (%d%c) \r\n",
            APP_NAME, hObj->rxBps, percentRx, '%');
        if (percentRx < ST_UART_EXPECTED_PERFORMANCE)
        {
            GT_5trace(
                hObj->traceMask, GT_INFO,
                " %s: Warning: RX Performance (%d%c) is less than expected "
                "(%d%c)!!\r\n",
                APP_NAME, percentRx, '%', ST_UART_EXPECTED_PERFORMANCE, '%');
        }
        if (percentRx > 100U)
        {
            GT_4trace(
                hObj->traceMask, GT_INFO,
                " %s: Warning: RX Performance (%d%c) is more than 100%c!!\r\n",
                APP_NAME, percentRx, '%', '%');
        }
    }

    return (BSP_SOK);
}

/**
 *  st_uartPrintStatus
 */
Int32 st_uartPrintStatus(st_UartHandleObj *hObj, Bool rtPrintEnable)
{
    Int32        retVal = BSP_SOK;
    UInt32       chCnt;
    st_UartChObj *chObj;
    Uart_Stats  uartStat;
    Error_Block eb;

    Error_init(&eb);

    for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
    {
        chObj = &hObj->txChObj[chCnt];
        GT_assert(hObj->traceMask, (NULL != chObj->chHandle));

        GIO_control(chObj->chHandle, IOCTL_UART_GET_STATS, &uartStat);
        if (TRUE != Error_check(&eb))
        {
            GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");
            GT_1trace(hObj->traceMask, GT_INFO1,
                " Ch.No %d TX Statistics\r\n", chCnt);
            GT_0trace(hObj->traceMask, GT_INFO1,
                " ----------------------\r\n");
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxBytes       : %d\r\n", uartStat.rxBytes);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of txBytes       : %d\r\n", uartStat.txBytes);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of overrun       : %d\r\n", uartStat.overrun);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxTimeout     : %d\r\n", uartStat.rxTimeout);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxFramingError: %d\r\n", uartStat.rxFramingError);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxBreakError  : %d\r\n", uartStat.rxBreakError);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxParityError : %d\r\n", uartStat.rxParityError);
            if (uartStat.overrun > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Overrun has occurred!!\r\n");
            }
            if (uartStat.rxTimeout > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Timeout has occurred!!\r\n");
            }
            if (uartStat.rxFramingError > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Framing Error has occurred!!\r\n");
            }
            if (uartStat.rxBreakError > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Break Error has occurred!!\r\n");
            }
            if (uartStat.rxParityError > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Parity Error has occurred!!\r\n");
            }
        }
        else
        {
            retVal = BSP_EFAIL;
            GT_0trace(hObj->traceMask, GT_ERR,
                " Uart get stat IOCTL failed for TX channel!!\r\n");
        }
    }

    for (chCnt = 0u; chCnt < hObj->rxNumCh; chCnt++)
    {
        chObj = &hObj->rxChObj[chCnt];
        GT_assert(hObj->traceMask, (NULL != chObj->chHandle));

        GIO_control(chObj->chHandle, IOCTL_UART_GET_STATS, &uartStat);
        if (TRUE != Error_check(&eb))
        {
            GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");
            GT_1trace(hObj->traceMask, GT_INFO1,
                " Ch.No %d RX Statistics\r\n", chCnt);
            GT_0trace(hObj->traceMask, GT_INFO1,
                " -----------------------\r\n");
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxBytes       : %d\r\n", uartStat.rxBytes);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of txBytes       : %d\r\n", uartStat.txBytes);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of overrun       : %d\r\n", uartStat.overrun);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxTimeout     : %d\r\n", uartStat.rxTimeout);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxFramingError: %d\r\n", uartStat.rxFramingError);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxBreakError  : %d\r\n", uartStat.rxBreakError);
            GT_1trace(hObj->traceMask, GT_INFO1,
                " No of rxParityError : %d\r\n", uartStat.rxParityError);

            if (uartStat.overrun > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Overrun has occurred!!\r\n");
            }
            if (uartStat.rxTimeout > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Timeout has occurred!!\r\n");
            }
            if (uartStat.rxFramingError > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Framing Error has occurred!!\r\n");
            }
            if (uartStat.rxBreakError > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Break Error has occurred!!\r\n");
            }
            if (uartStat.rxParityError > 0U)
            {
                GT_0trace(hObj->traceMask, GT_INFO1,
                    " Warning: RX Parity Error has occurred!!\r\n");
            }
        }
        else
        {
            retVal = BSP_EFAIL;
            GT_0trace(hObj->traceMask, GT_ERR,
                " Uart get stat IOCTL failed for RX channel!!\r\n");
        }
    }

    GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");

    return (retVal);
}

/**
 *  st_uartCheckHeapStat
 */
Int32 st_uartCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                           UInt32                        traceMask)
{
    Int32 retVal = BSP_SOK;
    BspUtils_MemHeapStatus curStat;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL != heapStat));

    BspUtils_memGetHeapStat(&curStat);

    if (heapStat->freeSysHeapSize != curStat.freeSysHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  " %s: Warning: Memory leak (%d bytes) in System Heap!!\r\n",
                  APP_NAME,
                  (heapStat->freeSysHeapSize - curStat.freeSysHeapSize));
        retVal = BSP_EFAIL;
    }
    if (heapStat->freeBufHeapSize != curStat.freeBufHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  " %s: Warning: Memory leak (%d bytes) in Buffer Heap!!\r\n",
                  APP_NAME,
                  (heapStat->freeBufHeapSize - curStat.freeBufHeapSize));
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

void st_logTestResult(const st_UartUtObj *utObj,
                      Int32              testResult,
                      UInt32             testCaseId,
                      char              *testcaseInfo)
{
    if (BSP_SOK == testResult)
    {
        glbPassCounter++;
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |TEST RESULT|PASS|%d|\r\n", testCaseId);
    }
    else
    {
        glbFailCounter++;
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |TEST RESULT|FAIL|%d|\r\n", testCaseId);
    }

    glbTestCounter++;
    GT_1trace(utObj->traceMask, GT_INFO,
              " |TEST INFO|:: %s ::\r\n", testcaseInfo);
    GT_1trace(utObj->traceMask, GT_INFO,
              " |TEST END|:: %d ::\r\n", testCaseId);

    return;
}

void st_printTestResult(const st_UartUtObj *utObj,
                        UInt32             skipCount,
                        UInt32             disableCount)
{
    GT_0trace(utObj->traceMask, GT_INFO,
              "\r\n *********Test Case Statistics*****************");
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case         : %d",
              (glbTestCounter + skipCount + disableCount));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Executed: %d", glbTestCounter);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Passed  : %d", glbPassCounter);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Failed  : %d", glbFailCounter);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Skipped : %d", skipCount);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Disabled: %d", disableCount);
    GT_0trace(utObj->traceMask, GT_INFO,
              "\r\n *********************************************\r\n \r\n");

    return;
}

void st_resetTestResult(void)
{
    glbTestCounter = 0;
    glbPassCounter = 0;
    glbFailCounter = 0;

    return;
}

const char *st_uartGetOpModeString(Int32 opMode)
{
    const char *opModeStr = NULL;

    switch (opMode)
    {
        case UART_OPMODE_POLLED:
            opModeStr = "POLLED";
            break;

        case UART_OPMODE_INTERRUPT:
            opModeStr = "INTERRUPT";
            break;

        case UART_OPMODE_DMAINTERRUPT:
            opModeStr = "DMA";
            break;

        default:
            opModeStr = "INVALID";
            break;
    }

    return (opModeStr);
}

const char *st_uartGetBaudRateString(Int32 baudRate)
{
    const char *baudRateStr = NULL;

    switch (baudRate)
    {
        case UART_BAUDRATE_2_4K:
            baudRateStr = "2400";
            break;

        case UART_BAUDRATE_4_8K:
            baudRateStr = "4800";
            break;

        case UART_BAUDRATE_9_6K:
            baudRateStr = "9600";
            break;

        case UART_BAUDRATE_19_2K:
            baudRateStr = "19200";
            break;

        case UART_BAUDRATE_38_4K:
            baudRateStr = "38400";
            break;

        case UART_BAUDRATE_57_6K:
            baudRateStr = "57600";
            break;

        case UART_BAUDRATE_115_2K:
            baudRateStr = "115200";
            break;

        case UART_BAUDRATE_3686_4K:
            baudRateStr = "3686400";
            break;

        default:
            baudRateStr = "INVALID";
            break;
    }

    return (baudRateStr);
}

const char *st_uartGetCharLenString(Int32 charLen)
{
    const char *charLenStr = NULL;

    switch (charLen)
    {
        case UART_CHARLEN_5:
            charLenStr = "5 Bits";
            break;

        case UART_CHARLEN_6:
            charLenStr = "6 Bits";
            break;

        case UART_CHARLEN_7:
            charLenStr = "7 Bits";
            break;

        case UART_CHARLEN_8:
            charLenStr = "8 Bits";
            break;

        default:
            charLenStr = "INVALID";
            break;
    }

    return (charLenStr);
}

const char *st_uartGetStopBitsString(Int32 stopBits)
{
    const char *stopBitsStr = NULL;

    switch (stopBits)
    {
        case UART_NUMSTOPBITS_1:
            stopBitsStr = "1";
            break;

        case UART_NUMSTOPBITS_1_5:
            stopBitsStr = "1.5";
            break;

        case UART_NUMSTOPBITS_2:
            stopBitsStr = "2";
            break;

        default:
            stopBitsStr = "INVALID";
            break;
    }

    return (stopBitsStr);
}

const char *st_uartGetParityString(Int32 parity)
{
    const char *parityStr = NULL;

    switch (parity)
    {
        case UART_PARITY_NO:
            parityStr = "NONE";
            break;

        case UART_PARITY_ODD:
            parityStr = "ODD";
            break;

        case UART_PARITY_EVEN:
            parityStr = "EVEN";
            break;

        case UART_PARITY_FORCED0:
            parityStr = "FORCED 0";
            break;

        case UART_PARITY_FORCED1:
            parityStr = "FORCED 1";
            break;

        default:
            parityStr = "INVALID";
            break;
    }

    return (parityStr);
}

const char *st_uartGetFcTypeString(Int32 fcType)

{
    const char *fcTypeStr = NULL;

    switch (fcType)
    {
        case UART_FCTYPE_NONE:
            fcTypeStr = "NONE";
            break;

        case UART_FCTYPE_SW:
            fcTypeStr = "SW";
            break;

        case UART_FCTYPE_HW:
            fcTypeStr = "HW";
            break;

        default:
            fcTypeStr = "INVALID";
            break;
    }

    return (fcTypeStr);
}

const char *st_uartGetFcParamRxString(Int32 fcParamRx)
{
    const char *fcParamRxStr = NULL;

    switch (fcParamRx)
    {
        case UART_FCPARAM_RXNONE:
            fcParamRxStr = "NONE";
            break;

        case UART_FCPARAM_RXXONXOFF_2:
            fcParamRxStr = "XONXOFF_2";
            break;

        case UART_FCPARAM_RXXONXOFF_1:
            fcParamRxStr = "XONXOFF_1";
            break;

        case UART_FCPARAM_RXXONXOFF_12:
            fcParamRxStr = "XONXOFF_12";
            break;

        case UART_FCPARAM_AUTO_RTS:
            fcParamRxStr = "AUTO RTS";
            break;

        default:
            fcParamRxStr = "INVALID";
            break;
    }

    return (fcParamRxStr);
}

const char *st_uartGetFcParamTxString(Int32 fcParamTx)
{
    const char *fcParamTxStr = NULL;

    switch (fcParamTx)
    {
        case UART_FCPARAM_TXNONE:
            fcParamTxStr = "NONE";
            break;

        case UART_FCPARAM_TXXONXOFF_2:
            fcParamTxStr = "XONXOFF_2";
            break;

        case UART_FCPARAM_TXXONXOFF_1:
            fcParamTxStr = "XONXOFF_1";
            break;

        case UART_FCPARAM_TXXONXOFF_12:
            fcParamTxStr = "XONXOFF_12";
            break;

        case UART_FCPARAM_AUTO_CTS:
            fcParamTxStr = "AUTO CTS";
            break;

        default:
            fcParamTxStr = "INVALID";
            break;
    }

    return (fcParamTxStr);
}

const char *st_uartGetRxThresholdString(Int32 rxThreshold)
{
    const char *rxThresholdStr = NULL;

    switch (rxThreshold)
    {
        case UART_RXTRIGLVL_8:
            rxThresholdStr = "8";
            break;

        case UART_RXTRIGLVL_16:
            rxThresholdStr = "16";
            break;

        case UART_RXTRIGLVL_56:
            rxThresholdStr = "56";
            break;

        case UART_RXTRIGLVL_60:
            rxThresholdStr = "60";
            break;

        default:
            rxThresholdStr = "INVALID";
            break;
    }

    return (rxThresholdStr);
}

const char *st_uartGetTxThresholdString(Int32 txThreshold)
{
    const char *txThresholdStr = NULL;

    switch (txThreshold)
    {
        case UART_TXTRIGLVL_8:
            txThresholdStr = "8";
            break;

        case UART_TXTRIGLVL_16:
            txThresholdStr = "16";
            break;

        case UART_TXTRIGLVL_32:
            txThresholdStr = "32";
            break;

        case UART_TXTRIGLVL_56:
            txThresholdStr = "56";
            break;

        default:
            txThresholdStr = "INVALID";
            break;
    }

    return (txThresholdStr);
}

/**
 *
 *  Sets the default channel parameters.
 */
static void st_vpsSetDefaultChPrms(const st_UartHandleObj *hObj,
                                   st_UartChObj           *chObj,
                                   UInt32                  chNum)
{
    chObj->chId               = chNum;
    chObj->chHandle           = NULL;
    chObj->inBuffer           = NULL;
    chObj->submitBuffer       = NULL;
    chObj->submittedRequestTx = 0u;
    chObj->submittedRequestRx = 0u;
    chObj->bytesTx            = 0u;
    chObj->bytesRx            = 0u;

    return;
}

static Int32 st_uartGetExpectedBps(const st_UartHandleObj *hObj)
{
    UInt32 expectedBps, baudRate, divideFactor;

    switch (hObj->handleCfg.uartPrms.baudRate)
    {
        case UART_BAUDRATE_2_4K:
            baudRate = 2400;
            break;

        case UART_BAUDRATE_4_8K:
            baudRate = 4800;
            break;

        case UART_BAUDRATE_9_6K:
            baudRate = 9600;
            break;

        case UART_BAUDRATE_19_2K:
            baudRate = 19200;
            break;

        case UART_BAUDRATE_38_4K:
            baudRate = 38400;
            break;

        case UART_BAUDRATE_57_6K:
            baudRate = 57600;
            break;

        case UART_BAUDRATE_115_2K:
            baudRate = 115200;
            break;

        case UART_BAUDRATE_3686_4K:
            baudRate = 3686400;
            break;

        default:
            baudRate = 115200;
            GT_0trace(hObj->traceMask, GT_ERR, " Invalid baudrate\r\n");
            break;
    }

    divideFactor = 1;       /* For start bit */
    switch (hObj->handleCfg.uartPrms.charLen)
    {
        case UART_CHARLEN_5:
            divideFactor += 5;
            break;

        case UART_CHARLEN_6:
            divideFactor += 6;
            break;

        case UART_CHARLEN_7:
            divideFactor += 7;
            break;

        case UART_CHARLEN_8:
            divideFactor += 8;
            break;

        default:
            divideFactor += 8;
            GT_0trace(hObj->traceMask, GT_ERR, " Invalid char length\r\n");
            break;
    }

    if (hObj->handleCfg.uartPrms.stopBits == UART_NUMSTOPBITS_1)
    {
        divideFactor += 1;
    }
    else
    {
        divideFactor += 2;
    }

    if (hObj->handleCfg.uartPrms.parity != UART_PARITY_NO)
    {
        divideFactor += 1;
    }

    expectedBps = (baudRate / divideFactor);
    return (expectedBps);
}
