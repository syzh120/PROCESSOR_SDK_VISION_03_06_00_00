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
 *  \file st_uartTestCase.c
 *
 *  \brief Code for testing UART driver.
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

static Int32 st_uartCreatePhase(st_UartHandleObj *hObj);
static Int32 st_uartDeletePhase(st_UartHandleObj *hObj);
static Int32 st_uartRxTxRunPhase(st_UartHandleObj *hObj, UInt32 openCloseCnt);

static Int32 st_uartOpenChannels(st_UartHandleObj *hObj);
static Int32 st_uartCloseChannels(st_UartHandleObj *hObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 st_uartCreateDevice(st_UartHandleObj *hObj)
{
    Int32 retVal = BSP_SOK;
    Int   gioStatus  = IOM_COMPLETED;
    IOM_Fxns   *iomFxns;
    Error_Block eb;

    Error_init(&eb);

    iomFxns   = (IOM_Fxns *) &Uart_IOMFXNS;
    gioStatus = GIO_addDevice(
                    hObj->devName,
                    iomFxns,
                    NULL,
                    hObj->devId,
                    &hObj->handleCfg.uartPrms);
    if (IOM_COMPLETED == gioStatus)
    {
        GT_2trace(hObj->traceMask, GT_INFO1,
                  " %s: UART driver created for instance %d!!\r\n",
                  APP_NAME, (hObj->devId + ST_UART_DEVID_OFFSET));
    }
    else
    {
        GT_0trace(hObj->traceMask, GT_ERR, " UART driver create failed!!\r\n");
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

Int32 st_uartDeleteDevice(st_UartHandleObj *hObj)
{
    Int32 retVal = BSP_SOK;
    Int   gioStatus  = IOM_COMPLETED;

    gioStatus = GIO_removeDevice(hObj->devName);
    if (IOM_COMPLETED == gioStatus)
    {
        GT_2trace(hObj->traceMask, GT_INFO1,
                  " %s: UART driver deleted for instance %d!!\r\n",
                  APP_NAME, (hObj->devId + ST_UART_DEVID_OFFSET));
    }
    else
    {
        GT_0trace(hObj->traceMask, GT_ERR, " UART driver delete failed!!\r\n");
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  st_uartRxTxTestCase
 *  UART test function for default RX, TX or RX+TX functionality.
 */
Int32 st_uartRxTxTestCase(st_UartHandleObj *hObj)
{
    Int32  retVal = BSP_SOK, tempRetVal;
    Bool   createFlag;
    UInt32 openCloseCnt;

    if (hObj->handleCfg.openCloseCnt > 1u)
    {
        GT_2trace(hObj->traceMask, GT_INFO,
                  " %s: |Open/Close Test Case: %d times|\r\n",
                  APP_NAME, hObj->handleCfg.openCloseCnt);
    }
    openCloseCnt = 0u;
    while (openCloseCnt < hObj->handleCfg.openCloseCnt)
    {
        /* Create phase */
        createFlag = FALSE;
        retVal     = st_uartCreatePhase(hObj);
        if (BSP_SOK != retVal)
        {
            GT_0trace(hObj->traceMask, GT_ERR, " Create phase failed\r\n");
        }
        else
        {
            createFlag = TRUE;
        }

        if (BSP_SOK == retVal)
        {
            retVal = st_uartRxTxRunPhase(hObj, openCloseCnt);
            if (BSP_SOK != retVal)
            {
                GT_0trace(hObj->traceMask, GT_ERR, " Run phase failed!!\r\n");
            }
        }

        if (TRUE == createFlag)
        {
            /* Delete phase */
            tempRetVal = st_uartDeletePhase(hObj);
            if (BSP_SOK != tempRetVal)
            {
                retVal = tempRetVal;
                GT_0trace(hObj->traceMask, GT_ERR, " Delete phase failed\r\n");
            }
        }

        if (BSP_SOK != retVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      " Open/Close failed @ %d count\r\n", openCloseCnt);
            break;
        }

        openCloseCnt++;
        if ((openCloseCnt > 0u) &&
            ((openCloseCnt % (OPEN_CLOSE_CNT_OC / 10u)) == 0u))
        {
            GT_2trace(hObj->traceMask, GT_INFO,
                      " %s: Open/Close Test Count: %d\r\n",
                      APP_NAME, openCloseCnt);
        }
    }

    if (BSP_SOK == retVal)
    {
        GT_2trace(hObj->traceMask, GT_INFO,
                  " %s: UART Test Case %d Successful!!\r\n",
                  APP_NAME, hObj->testPrms->testCaseId);
    }
    else
    {
        GT_2trace(hObj->traceMask, GT_INFO,
                  " %s: UART Test Case %d Failed!!\r\n",
                  APP_NAME, hObj->testPrms->testCaseId);
    }

    return (retVal);
}

/**
 *  st_uartCreatePhase
 *  Performs all create time operations.
 */
static Int32 st_uartCreatePhase(st_UartHandleObj *hObj)
{
    Int32        retVal = BSP_SOK;
    Bool         initVarFlag;

    /* Initialize and allocate handles */
    initVarFlag = FALSE;
    retVal      = st_uartInitVariables(hObj);
    if (BSP_SOK == retVal)
    {
        initVarFlag = TRUE;
    }

    if (BSP_SOK == retVal)
    {
        retVal = st_uartOpenChannels(hObj);
    }

    /*
     * Deallocate resource/close handles if error occurs
     */
    if (BSP_SOK != retVal)
    {
        if (TRUE == initVarFlag)
        {
            /* Free allocated handles */
            st_uartFreeVariables(hObj);
        }
    }

    return (retVal);
}

/**
 *  st_uartDeletePhase
 *  Performs all delete time operations.
 */
static Int32 st_uartDeletePhase(st_UartHandleObj *hObj)
{
    Int32 retVal = BSP_SOK;

    st_uartCloseChannels(hObj);

    /* Free allocated handles */
    st_uartFreeVariables(hObj);

    return (retVal);
}

/**
 *  st_uartRxTxRunPhase
 *  Performs all run time operations.
 */
static Int32 st_uartRxTxRunPhase(st_UartHandleObj *hObj, UInt32 openCloseCnt)
{
    Int32  retVal = BSP_SOK;
    UInt32 startTime, endTime, randomWaitTime;
    Int32  chCnt;
    SizeT  txSubmitBufLen, rxSubmitBufLen, txLen, reminder;
    st_UartChObj   *chObj;
    UInt32 bytesToTx[ST_UART_MAX_CH];

    /* Print test case info to UART console at the start before starting
     * performance timers */
    if (openCloseCnt == 0U)
    {
        for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
        {
            chObj = &hObj->txChObj[chCnt];
            GT_assert(hObj->traceMask, (chObj->chHandle != NULL));

            startTime = BspOsal_getCurTimeInMsec();
            if (NULL != hObj->testPrms->reqId)
            {
                snprintf(chObj->submitBuffer, ST_UART_TX_BUF_SIZE,
                     " \r\n|TEST START|:: %d ::\r\n"
                     "|TEST PARAM|:: %s ::\r\n"
                     "|SR|:: %s ::\r\n \r\n",
                     hObj->testPrms->testCaseId, hObj->testPrms->testCaseName,
                     hObj->testPrms->reqId);
            }
            else
            {
                snprintf(chObj->submitBuffer, ST_UART_TX_BUF_SIZE,
                     " \r\n|TEST START|:: %d ::\r\n"
                     "|TEST PARAM|:: %s ::\r\n \r\n",
                     hObj->testPrms->testCaseId, hObj->testPrms->testCaseName);
            }

            txLen = txSubmitBufLen = strlen(chObj->submitBuffer);
            retVal = GIO_submit(
                         chObj->chHandle,
                         IOM_WRITE,
                         chObj->submitBuffer,
                         &txSubmitBufLen,
                         NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART write submit failed!!\r\n");
                break;
            }

            if (txSubmitBufLen != txLen)
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART write returned with less than buffer length!!\r\n");
            }
        }
    }

    if (TRUE == hObj->handleCfg.prfEnable)
    {
        /* Start the load calculation */
        BspUtils_prfLoadCalcStart();
        BspUtils_prfTsBegin(hObj->prfTsHandle);
    }
    /* Get fresh timestamp */
    startTime = BspOsal_getCurTimeInMsec();

    for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
    {
        chObj = &hObj->txChObj[chCnt];

        bytesToTx[chCnt] = chObj->chCfg.maxBytesPerSubmit;
        if (ST_UART_BPS_RAMP_UP == chObj->chCfg.bytesPerSubmitId)
        {
            bytesToTx[chCnt] = 1U;
        }
    }

    while (1U)
    {
        if ((hObj->txNumCh > 0U) &&
            (ST_UART_TCT_RX_TX == hObj->testPrms->testCaseType))
        {
            /* Wait for RX task to complete */
            if ((TRUE == gUartUtStopTx) &&
                (hObj->completedLoopCnt >= hObj->handleCfg.loopCnt))
            {
                break;
            }
        }
        else
        {
            if (hObj->completedLoopCnt >= hObj->handleCfg.loopCnt)
            {
                break;
            }
        }

        for (chCnt = 0u; chCnt < hObj->rxNumCh; chCnt++)
        {
            chObj = &hObj->rxChObj[chCnt];
            GT_assert(hObj->traceMask, (chObj->chHandle != NULL));
            GT_assert(hObj->traceMask, (chObj->submitBuffer != NULL));

            while (1U)
            {
                rxSubmitBufLen = chObj->chCfg.maxBytesPerSubmit;
                memset(chObj->submitBuffer, 0x00U, rxSubmitBufLen);

                /* UART RX */
                retVal = GIO_submit(
                             chObj->chHandle,
                             IOM_READ,
                             chObj->submitBuffer,
                             &rxSubmitBufLen,
                             NULL);
                if (BSP_SOK != retVal)
                {
                    if ((IOM_ETIMEOUT == retVal) &&
                        (UART_OPMODE_POLLED == hObj->handleCfg.uartPrms.opMode))
                    {
                        GT_1trace(hObj->traceMask, GT_INFO,
                            " UART read timed-out in polled mode. "
                            "Received %d bytes!!\r\n", rxSubmitBufLen);
                        if (rxSubmitBufLen > 0)
                        {
                            chObj->submitBuffer[rxSubmitBufLen] = '\r';
                            rxSubmitBufLen++;
                            chObj->submitBuffer[rxSubmitBufLen] = '\n';
                            rxSubmitBufLen++;
                            chObj->submitBuffer[rxSubmitBufLen] = NULL;
                            rxSubmitBufLen++;

                            GT_2trace(hObj->traceMask, GT_INFO1,
                                " RX CH %d Received: %s", chCnt,
                                chObj->submitBuffer);
                        }

                        GT_0trace(hObj->traceMask, GT_INFO,
                            " Trying again...\r\n");
                        retVal = BSP_SOK;
                        continue;
                    }
                    else
                    {
                        GT_0trace(hObj->traceMask, GT_ERR,
                            " UART read submit failed!!\r\n");
                        break;
                    }
                }

                /* Loop only in case of timeout */
                break;
            }

            chObj->submittedRequestRx++;
            chObj->bytesRx += rxSubmitBufLen;

            chObj->submitBuffer[rxSubmitBufLen] = '\r';
            rxSubmitBufLen++;
            chObj->submitBuffer[rxSubmitBufLen] = '\n';
            rxSubmitBufLen++;
            chObj->submitBuffer[rxSubmitBufLen] = NULL;
            rxSubmitBufLen++;

            if (ST_UART_TCT_RX_TO_TX == hObj->testPrms->testCaseType)
            {
                bytesToTx[chCnt] = rxSubmitBufLen;
            }

            if (DEF_RX_BYTESPERSUBMIT == chObj->chCfg.maxBytesPerSubmit)
            {
                Int32 cmpResult;

                cmpResult = memcmp(
                                chObj->submitBuffer,
                                UART_ST_RX_TEST_STRING,
                                chObj->chCfg.maxBytesPerSubmit);
                if (cmpResult != 0)
                {
                    GT_0trace(hObj->traceMask, GT_ERR,
                        " Warning: UART read string did not match!!\r\n");
                }
            }

            GT_2trace(hObj->traceMask, GT_INFO1,
                " RX CH %d Received: %s", chCnt, chObj->submitBuffer);
        }

        for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
        {
            chObj = &hObj->txChObj[chCnt];
            GT_assert(hObj->traceMask, (chObj->chHandle != NULL));
            GT_assert(hObj->traceMask, (chObj->inBuffer != NULL));
            GT_assert(hObj->traceMask, (chObj->submitBuffer != NULL));

            if (ST_UART_TCT_RX_TO_TX == hObj->testPrms->testCaseType)
            {
                txSubmitBufLen = bytesToTx[chCnt];
                GT_assert(hObj->traceMask,
                    (hObj->rxChObj[chCnt].submitBuffer != NULL));
                memcpy(
                    chObj->submitBuffer,
                    hObj->rxChObj[chCnt].submitBuffer,
                    txSubmitBufLen);
                txLen = txSubmitBufLen;
            }
            else
            {
                txSubmitBufLen = sprintf(chObj->submitBuffer, "Loop_%0.5d: ",
                                            hObj->completedLoopCnt + 1U);
                memcpy(&chObj->submitBuffer[txSubmitBufLen],
                       chObj->inBuffer,
                       bytesToTx[chCnt]);
                txSubmitBufLen += bytesToTx[chCnt];
                /* Driver has this limitation now.
                 * It can transfer only multiple of TX threshold bytes */
                if ((UART_OPMODE_DMAINTERRUPT ==
                        hObj->handleCfg.uartPrms.opMode) &&
                    (txSubmitBufLen > hObj->handleCfg.uartPrms.txThreshold))
                {
                    /* Make it multiple of 56 bytes so that performance
                     * number is proper */
                    reminder =
                        txSubmitBufLen % hObj->handleCfg.uartPrms.txThreshold;
                    txSubmitBufLen -= reminder;
                    txSubmitBufLen -= 2U;       /* for below line break chars */
                }
                chObj->submitBuffer[txSubmitBufLen] = '\r';
                txSubmitBufLen++;
                chObj->submitBuffer[txSubmitBufLen] = '\n';
                txSubmitBufLen++;
                txLen = txSubmitBufLen;
            }

            /* UART TX */
            retVal = GIO_submit(
                         chObj->chHandle,
                         IOM_WRITE,
                         chObj->submitBuffer,
                         &txSubmitBufLen,
                         NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART write submit failed!!\r\n");
                break;
            }

            if (txSubmitBufLen != txLen)
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART write returned with less than buffer length!!\r\n");
            }

            if (TRUE == hObj->handleCfg.randomModeEnable)
            {
                randomWaitTime =
                    hObj->completedLoopCnt % ST_UART_MAX_RANDOM_TIMEOUT;
                Task_sleep(randomWaitTime);
            }

            chObj->submittedRequestTx++;
            chObj->bytesTx += txLen;

            if (ST_UART_BPS_RAMP_UP == chObj->chCfg.bytesPerSubmitId)
            {
                bytesToTx[chCnt] += chObj->chCfg.incrementFactor;
                if (bytesToTx[chCnt] > chObj->chCfg.maxBytesPerSubmit)
                {
                    bytesToTx[chCnt] = 1U;
                }
            }
            if (ST_UART_BPS_RAMP_DOWN == chObj->chCfg.bytesPerSubmitId)
            {
                if (bytesToTx[chCnt] <= chObj->chCfg.incrementFactor)
                {
                    bytesToTx[chCnt] = chObj->chCfg.maxBytesPerSubmit;
                }
                else
                {
                    bytesToTx[chCnt] -= chObj->chCfg.incrementFactor;
                }
            }
        }
        hObj->completedLoopCnt++;
    }

    /* Set the TX end flag from RX task */
    if (hObj->rxNumCh > 0U)
    {
        gUartUtStopTx = TRUE;
    }

    if (TRUE == hObj->handleCfg.prfEnable)
    {
        BspUtils_prfTsEnd(
            hObj->prfTsHandle,
            (hObj->handleCfg.loopCnt * hObj->txNumCh));
    }

    if (BSP_SOK == retVal)
    {
        endTime = BspOsal_getCurTimeInMsec();

        if (TRUE == hObj->handleCfg.prfEnable)
        {
            /* Calculate performance number */
            st_uartCalcPerformance(hObj, (endTime - startTime));

            /* Stop the load calculation */
            BspUtils_prfLoadCalcStop();
            /* Print the load */
            BspUtils_prfLoadPrintAll(TRUE);
            /* print the fps based on TimeStamp */
            BspUtils_prfTsPrint(hObj->prfTsHandle, TRUE);

            /* Reset the load */
            BspUtils_prfLoadCalcReset();
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Print the status */
        if (hObj->traceMask == (GT_INFO1 | GT_TraceState_Enable))
        {
            st_uartPrintStatus(hObj, FALSE);
        }
    }

    /* Print test case ended to UART console */
    if (openCloseCnt == (hObj->handleCfg.openCloseCnt - 1U))
    {
        for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
        {
            chObj = &hObj->txChObj[chCnt];
            GT_assert(hObj->traceMask, (chObj->chHandle != NULL));

            endTime = BspOsal_getCurTimeInMsec();
            snprintf(chObj->submitBuffer, ST_UART_TX_BUF_SIZE,
                     " \r\n|TEST END|:: %d ::\r\n", hObj->testPrms->testCaseId);

            txSubmitBufLen = strlen(chObj->submitBuffer);
            retVal = GIO_submit(
                         chObj->chHandle,
                         IOM_WRITE,
                         chObj->submitBuffer,
                         &txSubmitBufLen,
                         NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART write submit failed!!\r\n");
                break;
            }

            if (txSubmitBufLen != strlen(chObj->submitBuffer))
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART write returned with less than buffer length!!\r\n");
            }
        }
    }

    return (retVal);
}

static Int32 st_uartOpenChannels(st_UartHandleObj *hObj)
{
    Int32 retVal = BSP_SOK;
    Int32 chCnt;
    st_UartChObj   *chObj;
    GIO_Params      ioParams;
    Error_Block     eb;

    Error_init(&eb);

    for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
    {
        GIO_Params_init(&ioParams);
        chObj = &hObj->txChObj[chCnt];

        chObj->chCfg.chPrms.hEdma = NULL;
        if (UART_OPMODE_DMAINTERRUPT == hObj->handleCfg.uartPrms.opMode)
        {
            chObj->chCfg.chPrms.hEdma = gEdmaHandle;
        }

        ioParams.chanParams = &chObj->chCfg.chPrms;
        chObj->chHandle =
            GIO_create(hObj->devName, GIO_OUTPUT, &ioParams, &eb);
        if (TRUE != Error_check(&eb))
        {
            GT_2trace(hObj->traceMask, GT_INFO1,
                  " %s: UART TX channel created for instance %d!!\r\n",
                  APP_NAME, (hObj->devId + ST_UART_DEVID_OFFSET));
        }
        else
        {
            GT_0trace(hObj->traceMask, GT_ERR,
                " UART TX channel creation failed!!\r\n");
            retVal = BSP_EFAIL;
            break;
        }
    }

    if (BSP_SOK == retVal)
    {
        for (chCnt = 0u; chCnt < hObj->rxNumCh; chCnt++)
        {
            GIO_Params_init(&ioParams);
            chObj = &hObj->rxChObj[chCnt];

            chObj->chCfg.chPrms.hEdma = NULL;
            if (UART_OPMODE_DMAINTERRUPT == hObj->handleCfg.uartPrms.opMode)
            {
                chObj->chCfg.chPrms.hEdma = gEdmaHandle;
            }

            ioParams.chanParams = &chObj->chCfg.chPrms;
            chObj->chHandle =
                GIO_create(hObj->devName, GIO_INPUT, &ioParams, &eb);
            if (TRUE != Error_check(&eb))
            {
                GT_2trace(hObj->traceMask, GT_INFO1,
                      " %s: UART RX channel created for instance %d!!\r\n",
                      APP_NAME, (hObj->devId + ST_UART_DEVID_OFFSET));
            }
            else
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART RX channel creation failed!!\r\n");
                retVal = BSP_EFAIL;
                break;
            }
        }
    }

    if (BSP_SOK != retVal)
    {
        st_uartCloseChannels(hObj);
    }

    return (retVal);
}

static Int32 st_uartCloseChannels(st_UartHandleObj *hObj)
{
    Int32 retVal = BSP_SOK;
    Int32 chCnt;
    st_UartChObj   *chObj;

    for (chCnt = 0u; chCnt < hObj->txNumCh; chCnt++)
    {
        chObj = &hObj->txChObj[chCnt];
        if (NULL != chObj->chHandle)
        {
            GIO_delete(&chObj->chHandle);
            if (NULL == chObj->chHandle)
            {
                GT_2trace(hObj->traceMask, GT_INFO1,
                      " %s: UART TX channel deleted for instance %d!!\r\n",
                      APP_NAME, (hObj->devId + ST_UART_DEVID_OFFSET));
            }
            else
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART TX channel deletion failed!!\r\n");
                retVal = BSP_EFAIL;
            }
        }
    }

    for (chCnt = 0u; chCnt < hObj->rxNumCh; chCnt++)
    {
        chObj = &hObj->rxChObj[chCnt];
        if (NULL != chObj->chHandle)
        {
            GIO_delete(&chObj->chHandle);
            if (NULL == chObj->chHandle)
            {
                GT_2trace(hObj->traceMask, GT_INFO1,
                      " %s: UART RX channel deleted for instance %d!!\r\n",
                      APP_NAME, (hObj->devId + ST_UART_DEVID_OFFSET));
            }
            else
            {
                GT_0trace(hObj->traceMask, GT_ERR,
                    " UART RX channel deletion failed!!\r\n");
                retVal = BSP_EFAIL;
            }
        }
    }

    return (retVal);
}
