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
 *  \file st_uartParser.c
 *
 *  \brief User interface for UART driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on UART driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_uart.h>
#include <testInput/st_uartConfig.h>
#include <testInput/st_uartTestCases.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define ST_TSK_STACK_SIZE               (10u * 1024u)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 st_uartRunTestCase(st_UartUtObj          *utObj,
                                st_UartTestCaseParams *testPrms);
static Int32 st_uartCreateRxTxTestTasks(st_UartUtObj                *utObj,
                                        const st_UartTestCaseParams *testPrms);
static void st_uartTestTask(UArg arg0, UArg arg1);

static Int32 st_uartGetTestCaseIdx(UInt32 testCaseId, Bool isSearchForward);
static const st_UartHandleCfg *st_uartGetUartHandleCfg(
                                            st_UartHandleCfgId handleCfgId);
static const st_UartChCfg *st_uartGetUartChCfg(st_UartChCfgId chCfgId);
static Bool st_uartCheckIfTestToBeSkipped(st_UartUtObj                *utObj,
                                          const st_UartTestCaseParams *testPrms,
                                          UInt32                      testType);
static Int32 st_uartDisplayTestInfo(st_UartUtObj *utObj);
static Int32 st_uartGenerateTestReports(st_UartUtObj *utObj);

static Int32 st_uartInitUartAppObj(const st_UartUtObj          *utObj,
                                   const st_UartTestCaseParams *testPrms,
                                   st_UartHandleObj            *hObj,
                                   UInt32                      taskCnt);

static Void st_uartMenuSettings(st_UartUtObj *utObj);
static Void st_uartMenuMainShow(st_UartUtObj *utObj);
static Void st_uartMenuSettingsShow(st_UartUtObj *utObj);
static Void st_uartMenuCurrentSettingsShow(st_UartUtObj *utObj);
static Void st_uartSetDefaultCfg(st_UartUtObj *utObj);
static Int32 st_uartDetectBoard(st_UartUtObj *utObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* UART Test application stack. */
#pragma DATA_ALIGN(gStUartTestTskStack, 32)
#pragma DATA_SECTION(gStUartTestTskStack, ".bss:taskStackSection")
static UInt8 gStUartTestTskStack[ST_UART_MAX_HANDLE][ST_TSK_STACK_SIZE];

/* UART application object per driver handle. */
static st_UartHandleObj  gStUartObjs[ST_UART_MAX_HANDLE];

/* UART task complete semaphore */
static Semaphore_Handle gStUartTaskCompleteSem;

/* UART UT object. */
st_UartUtObj gUartUtObj;

/* Flag used to stop TX transfer in case of RX_TX test case. Till user
 * gives RX data, this flag will ensure TX keeps transmitting till that time. */
volatile Bool gUartUtStopTx = FALSE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_uartParser
 */
Int32 st_uartParser(void)
{
    char   option, inputStr[10];
    Bool   done;
    Int32  retVal = BSP_SOK;
    Int32  testCaseIdx, startIdx;
    UInt32 testCnt, testType, testCaseId;
    UInt32 startTime, endTime, startTime1, endTime1;
    UInt32 hrs, mins, secs, durationInSecs;
    BspUtils_MemHeapStatus startHeapStat;
    st_UartUtObj           *utObj;
    st_UartTestCaseParams  *testPrms;

    utObj = &gUartUtObj;
    st_uartSetDefaultCfg(utObj);
    st_resetTestResult();

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    startTime        = BspOsal_getCurTimeInMsec();
    done             = FALSE;
    utObj->skipCount = utObj->disableCount = 0u;
    while (!done)
    {
        st_uartMenuMainShow(utObj);

        BspOsal_scanf("%s", inputStr);
        option = inputStr[0u];
        GT_0trace(utObj->traceMask, GT_INFO, " \r\n");

        testType = ST_TT_SANITY;
        switch (option)
        {
            case 's':
                st_uartMenuSettings(utObj);
                break;

            case 'q':
                done = TRUE;
                break;

            case '1':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Manual testing - Enter Test Case Id: \r\n");
                BspOsal_scanf("%s", inputStr);
                testCaseId = (UInt32) atoi(inputStr);

                /* Find the test case to run */
                testCaseIdx = st_uartGetTestCaseIdx(testCaseId, FALSE);
                if (testCaseIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              " Test case ID not found\r\n");
                }
                else
                {
                    testPrms = &gStUartTestCasePrms[testCaseIdx];

                    retVal = st_uartRunTestCase(utObj, testPrms);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  " Failed to run test case!!\r\n");
                    }
                }
                break;

            case '4':
                testType |= ST_TT_FULL;
            case '3':
                testType |= ST_TT_REGRESSION;
            case '2':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Enter Start Test Case Id "
                    "(Enter 0 to start from first): \r\n");
                BspOsal_scanf("%s", inputStr);
                testCaseId = (UInt32) atoi(inputStr);
                startIdx   = st_uartGetTestCaseIdx(testCaseId, TRUE);
                if (startIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                              " Test case ID not found\r\n");
                    continue;
                }

                /* Run all test cases one after the other depending on selected
                 * flag */
                startTime1       = BspOsal_getCurTimeInMsec();
                utObj->skipCount = utObj->disableCount = 0u;

                for (testCnt = startIdx;
                     testCnt < ST_UART_NUM_TESTCASES;
                     testCnt++)
                {
                    testPrms = &gStUartTestCasePrms[testCnt];

                    /* Check whether to execute test or not */
                    if (st_uartCheckIfTestToBeSkipped(utObj, testPrms, testType))
                    {
                        continue;       /* Skip test */
                    }

                    retVal = st_uartRunTestCase(utObj, testPrms);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  " Failed to run test case!!\r\n");
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj,
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1 = BspOsal_getCurTimeInMsec();
                durationInSecs = ((endTime1 - startTime1) / 1000u);
                hrs = durationInSecs / (60u * 60u);
                mins = (durationInSecs / 60u) - (hrs * 60u);
                secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
                GT_3trace(utObj->traceMask, GT_INFO,
                          " |TOTAL TEST DURATION|: %d hrs %d mins %d secs\r\n",
                          hrs, mins, secs);
                break;

            case '5':
                testType = ST_TT_PERFORMANCE;
                startIdx = st_uartGetTestCaseIdx(0u, TRUE);
                if (startIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                              " Test case ID not found\r\n");
                    continue;
                }

                /* Run all test cases one after the other depending on selected
                 * flag */
                startTime1       = BspOsal_getCurTimeInMsec();
                utObj->skipCount = utObj->disableCount = 0u;
                for (testCnt = startIdx;
                     testCnt < ST_UART_NUM_TESTCASES;
                     testCnt++)
                {
                    testPrms = &gStUartTestCasePrms[testCnt];

                    /* Check whether to execute test or not */
                    if (st_uartCheckIfTestToBeSkipped(utObj, testPrms, testType))
                    {
                        continue;       /* Skip test */
                    }

                    retVal = st_uartRunTestCase(utObj, testPrms);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  " Failed to run test case!!\r\n");
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj,
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1 = BspOsal_getCurTimeInMsec();
                durationInSecs = ((endTime1 - startTime1) / 1000u);
                hrs = durationInSecs / (60u * 60u);
                mins = (durationInSecs / 60u) - (hrs * 60u);
                secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
                GT_3trace(utObj->traceMask, GT_INFO,
                          " |TOTAL TEST DURATION|: %d hrs %d mins %d secs\r\n",
                          hrs, mins, secs);
                break;

            case 'd':
                /* Display test info */
                st_uartDisplayTestInfo(utObj);
                break;

            case 'g':
                /* Generate test report */
                st_uartGenerateTestReports(utObj);
                break;

            default:
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Invalid option try again!!\r\n");
                break;
        }
    }

    /* check for leak */
    st_uartCheckHeapStat(&startHeapStat, utObj->traceMask);

    /* Print test results */
    st_printTestResult(utObj, utObj->skipCount, utObj->disableCount);
    st_uartDisplayTestInfo(utObj);
    st_uartGenerateTestReports(utObj);

    endTime = BspOsal_getCurTimeInMsec();
    durationInSecs = ((endTime - startTime) / 1000u);
    hrs = durationInSecs / (60u * 60u);
    mins = (durationInSecs / 60u) - (hrs * 60u);
    secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
    GT_3trace(utObj->traceMask, GT_INFO,
              " |TOTAL UT DURATION|: %d hrs %d mins %d secs\r\n",
              hrs, mins, secs);

    return (retVal);
}

/**
 *  st_uartRunTestCase
 */
static Int32 st_uartRunTestCase(st_UartUtObj          *utObj,
                                st_UartTestCaseParams *testPrms)
{
    char  inputStr[10];
    Int32 retVal = BSP_SOK;

    testPrms->isRun = TRUE;
    switch (testPrms->testCaseType)
    {
        case ST_UART_TCT_TX:
        case ST_UART_TCT_RX:
        case ST_UART_TCT_RX_TO_TX:
        case ST_UART_TCT_RX_TX:
            /* Create all test tasks */
            retVal = st_uartCreateRxTxTestTasks(utObj, testPrms);
            if (BSP_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                    " UART RX/TX test failed!!\r\n");
            }

            /* Store the test result */
            testPrms->testResult = retVal;
            break;

        case ST_UART_TCT_HALT:
            /* NULL pointer check */
            GT_assert(utObj->traceMask, (NULL != testPrms->testCaseName));
            GT_1trace(utObj->traceMask, GT_INFO,
                      "\r\n User Input Halt: %s\r\n", testPrms->testCaseName);
            BspOsal_scanf("%s", inputStr);
            break;

        default:
            GT_1trace(utObj->traceMask, GT_INFO,
                      " Invalid test case type: %d!!\r\n",
                      testPrms->testCaseType);
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  st_uartCreateRxTxTestTasks
 */
static Int32 st_uartCreateRxTxTestTasks(st_UartUtObj                *utObj,
                                        const st_UartTestCaseParams *testPrms)
{
    char                   tempString[ST_UART_PRINT_BUFSIZE];
    Int32                  retVal = BSP_SOK, testResult = BSP_SOK;
    UInt32                 devId, devCnt, taskCnt, createdTsk;
    UInt32                 startTime, endTime, hrs, mins, secs, msecs;
    UInt32                 durationInMsecs, durationInSecs;
    BspUtils_MemHeapStatus startHeapStat;
    st_UartHandleObj       *hObj;
    Task_Params            tskPrms[ST_UART_MAX_HANDLE];
    Task_Handle            tskHandle[ST_UART_MAX_HANDLE];
    Semaphore_Params       semPrms;
    UInt32                 taskCntUart = 0;
    Bool                   isDevIdCreated[ST_UART_INST_MAX];

    /* NULL pointer check */
    GT_assert(utObj->traceMask, (NULL != testPrms));
    GT_assert(utObj->traceMask, (testPrms->numHandles <= ST_UART_MAX_HANDLE));
    GT_assert(utObj->traceMask, (NULL != testPrms->testCaseName));

    startTime = BspOsal_getCurTimeInMsec();
    GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
    GT_1trace(utObj->traceMask, GT_INFO,
              " |TEST START|:: %d ::\r\n", testPrms->testCaseId);
    GT_1trace(utObj->traceMask, GT_INFO,
              " |TEST PARAM|:: %s ::\r\n", testPrms->testCaseName);

    memset(&tskHandle, 0u, sizeof (tskHandle));
    memset(&gStUartObjs, 0u, sizeof (gStUartObjs));

    if (NULL != testPrms->reqId)
    {
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |SR|:: %s ::\r\n", testPrms->reqId);
    }
    if (NULL != testPrms->userInfo)
    {
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |User Info|:: %s ::\r\n", testPrms->userInfo);
    }
    GT_0trace(utObj->traceMask, GT_INFO, " \r\n");

    startTime = BspOsal_getCurTimeInMsec();   /* Reset time to exclude print */

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    Semaphore_Params_init(&semPrms);
    gStUartTaskCompleteSem = Semaphore_create(0u, &semPrms, NULL);
    if (NULL == gStUartTaskCompleteSem)
    {
        GT_0trace(utObj->traceMask, GT_ERR, " Sem create failed!!!\r\n");
        retVal = BSP_EALLOC;
    }

    for (devCnt = 0u; devCnt < ST_UART_INST_MAX; devCnt++)
    {
        isDevIdCreated[devCnt] = FALSE;
    }
    if (ST_UART_TCT_RX_TX == testPrms->testCaseType)
    {
        gUartUtStopTx = FALSE;
    }

    if (BSP_SOK == retVal)
    {
        createdTsk = 0u;
        for (taskCnt = 0u; taskCnt < testPrms->numHandles; taskCnt++)
        {
            hObj   = &gStUartObjs[taskCntUart];
            retVal = st_uartInitUartAppObj(utObj, testPrms, hObj, taskCnt);
            if (BSP_SOK != retVal)
            {
                break;
            }

            /* Create UART instances if not done so */
            devId = testPrms->devId[taskCnt];
            GT_assert(utObj->traceMask, (devId < ST_UART_INST_MAX));
            if (FALSE == isDevIdCreated[devId])
            {
                retVal = st_uartEnableUartInstance(utObj, devId);
                retVal += st_uartCreateDevice(hObj);
                if (BSP_SOK != retVal)
                {
                    break;
                }
                isDevIdCreated[devId] = TRUE;
            }

            /* Create individual tasks */
            Task_Params_init(&tskPrms[taskCnt]);
            tskPrms[taskCnt].stack     = &gStUartTestTskStack[taskCntUart][0u];
            tskPrms[taskCnt].stackSize = ST_TSK_STACK_SIZE;
            tskPrms[taskCnt].arg0      = (UArg) hObj;
            tskHandle[taskCnt]         = Task_create(
                (Task_FuncPtr) st_uartTestTask,
                &tskPrms[taskCnt],
                NULL);
            if (NULL == tskHandle[taskCnt])
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                    " Task create failed!!!\r\n");
                retVal = BSP_EALLOC;
                break;
            }

            createdTsk++;
            taskCntUart++;
            snprintf(tempString, sizeof (tempString),
                    " ST_UART Task %d", taskCnt);
            BspUtils_prfLoadRegister(tskHandle[taskCnt], tempString);
        }
    }

    if (BSP_SOK == retVal)
    {
        for (taskCnt = 0u; taskCnt < createdTsk; taskCnt++)
        {
            /* Wait for all tasks to complete */
            Semaphore_pend(gStUartTaskCompleteSem, BIOS_WAIT_FOREVER);
        }
    }

    /* Delete already created UART instances */
    for (taskCnt = 0u; taskCnt < testPrms->numHandles; taskCnt++)
    {
        hObj = &gStUartObjs[taskCnt];
        devId = testPrms->devId[taskCnt];
        GT_assert(utObj->traceMask, (devId < ST_UART_INST_MAX));
        if (TRUE == isDevIdCreated[devId])
        {
            testResult += st_uartDeleteDevice(hObj);
            testResult += st_uartDisableUartInstance(utObj, devId);
            isDevIdCreated[devId] = FALSE;
        }
    }

    for (taskCnt = 0u; taskCnt < taskCntUart; taskCnt++)
    {
        testResult += gStUartObjs[taskCnt].testResult;
    }
    /* Store the local error value */
    testResult += retVal;

    /* Fail is pass in case of negative tests. Change return value. */
    if (testPrms->testType & ST_TT_NEGATIVE)
    {
        if (BSP_SOK == testResult)
        {
            testResult = BSP_EFAIL;
        }
        else
        {
            testResult = BSP_SOK;
        }
    }

    /* Delete the created task */
    for (taskCnt = 0u; taskCnt < testPrms->numHandles; taskCnt++)
    {
        if (NULL != tskHandle[taskCnt])
        {
            BspUtils_prfLoadUnRegister(tskHandle[taskCnt]);
            Task_delete(&tskHandle[taskCnt]);
            tskHandle[taskCnt] = NULL;
        }
    }

    if (NULL != gStUartTaskCompleteSem)
    {
        Semaphore_delete(&gStUartTaskCompleteSem);
    }

    /* check for leak */
    st_uartCheckHeapStat(&startHeapStat, utObj->traceMask);

    endTime = BspOsal_getCurTimeInMsec();
    durationInMsecs = (endTime - startTime);
    durationInSecs = (durationInMsecs / 1000u);
    hrs = durationInSecs / (60u * 60u);
    mins = (durationInSecs / 60u) - (hrs * 60u);
    secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
    msecs = durationInMsecs - ((hrs * 60u * 60u) + (mins * 60u) + secs) * 1000u;
    GT_4trace(utObj->traceMask, GT_INFO,
              " |TEST DURATION|:: %d:%0.2d:%0.2d:%0.3d ::\r\n",
              hrs, mins, secs, msecs);

    snprintf(tempString, sizeof (tempString), "%s", testPrms->testCaseName);
    st_logTestResult(utObj, testResult, testPrms->testCaseId, tempString);

    return (testResult);
}

/**
 *  st_uartTestTask
 */
static void st_uartTestTask(UArg arg0, UArg arg1)
{
    Int32 retVal;
    st_UartHandleObj *hObj;

    /* Run the test */
    hObj = (st_UartHandleObj *) arg0;

    /* Run the Tx test */
    retVal = st_uartRxTxTestCase(hObj);

    hObj->testResult = retVal;

    /* Test complete. Signal it */
    Semaphore_post(gStUartTaskCompleteSem);

    return;
}

/**
 *  st_uartGetTestCaseIdx
 */
static Int32 st_uartGetTestCaseIdx(UInt32 testCaseId, Bool isSearchForward)
{
    Int32  testCaseIdx = -1;
    UInt32 testCnt;
    const st_UartTestCaseParams *testPrms;

    testPrms = &gStUartTestCasePrms[0u];
    for (testCnt = 0u; testCnt < ST_UART_NUM_TESTCASES; testCnt++)
    {
        if (TRUE == isSearchForward)
        {
            if (testPrms->testCaseId >= testCaseId)
            {
                testCaseIdx = testCnt;
                break;
            }
        }
        else
        {
            if (testPrms->testCaseId == testCaseId)
            {
                testCaseIdx = testCnt;
                break;
            }
        }
        testPrms++;
    }

    return (testCaseIdx);
}

/**
 *  st_uartGetUartHandleCfg
 */
static const st_UartHandleCfg *st_uartGetUartHandleCfg(
                                        st_UartHandleCfgId handleCfgId)
{
    UInt32 index;
    const st_UartHandleCfg *handleCfg = NULL;

    /* Search in handle table */
    for (index = 0u; index < UART_MAX_HANDLE_CFG; index++)
    {
        if (gStUartHandleCfg[index].handleCfgId == handleCfgId)
        {
            handleCfg = &gStUartHandleCfg[index];
            break;
        }
    }

    return (handleCfg);
}

static const st_UartChCfg *st_uartGetUartChCfg(st_UartChCfgId chCfgId)
{
    UInt32 index;
    const st_UartChCfg *chCfg = NULL;

    /* Search in channel table */
    for (index = 0u; index < UART_MAX_CH_CFG; index++)
    {
        if (gStUartChCfg[index].chCfgId == chCfgId)
        {
            chCfg = &gStUartChCfg[index];
            break;
        }
    }

    return (chCfg);
}

/**
 *  st_uartCheckIfTestToBeSkipped
 */
static Bool st_uartCheckIfTestToBeSkipped(st_UartUtObj                *utObj,
                                          const st_UartTestCaseParams *testPrms,
                                          UInt32                      testType)
{
    Bool                skipTest = FALSE;
    Bsp_PlatformSocId   socId;

    socId = Bsp_platformGetSocId();

    /* Check whether test case is disabled */
    if (FALSE == testPrms->enableTest)
    {
        GT_assert(utObj->traceMask,
                  (NULL != testPrms->testCaseName));
        GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |TEST DISABLED|:: %d ::\r\n", testPrms->testCaseId);
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |TEST PARAM|:: %s ::\r\n", testPrms->testCaseName);
        if (NULL != testPrms->disableReason)
        {
            GT_1trace(utObj->traceMask, GT_INFO,
                      " |TEST DISABLE REASON|:: %s ::\r\n",
                      testPrms->disableReason);
        }
        else
        {
            GT_0trace(utObj->traceMask, GT_INFO,
                      " |TEST DISABLE REASON|:: Not Provided!! ::\r\n");
        }

        utObj->disableCount++;
        skipTest = TRUE;        /* Skip test */
    }

    /* Check if this is halt test case used to get user input */
    if ((FALSE == skipTest) &&
        (TRUE == utObj->sysCtrl.skipHaltTests) &&
        (ST_UART_TCT_HALT == testPrms->testCaseType))
    {
        skipTest = TRUE;        /* Skip test */
    }

    /* Check if SOC is applicable */
    if ((FALSE == skipTest) && !(socId & testPrms->socId))
    {
        skipTest = TRUE;        /* Skip test */
    }

    /* Check if this is RX test cases */
    if ((FALSE == skipTest) &&
        (TRUE == utObj->sysCtrl.skipRxTests) &&
        ((ST_UART_TCT_RX == testPrms->testCaseType) ||
            (ST_UART_TCT_RX_TO_TX == testPrms->testCaseType) ||
            (ST_UART_TCT_RX_TX == testPrms->testCaseType)))
    {
        skipTest = TRUE;        /* Skip test */
    }

    /* Check if this is TX test cases */
    if ((FALSE == skipTest) &&
        (TRUE == utObj->sysCtrl.skipTxOnlyTests) &&
        (ST_UART_TCT_TX == testPrms->testCaseType))
    {
        skipTest = TRUE;        /* Skip test */
    }

    /* Ignore test case depending on test flag and
     * selected option */
    if ((FALSE == skipTest) &&
        (ST_TT_MISC != testPrms->testType))
    {
        if (!(testType & testPrms->testType))
        {
            utObj->skipCount++;
            skipTest = TRUE;    /* Skip test */
        }
    }

    return (skipTest);
}

/**
 *  st_uartDisplayTestInfo
 */
static Int32 st_uartDisplayTestInfo(st_UartUtObj *utObj)
{
    UInt32                  sCnt, testCnt;
    char                   *runStatus;
    st_UartTestCaseParams  *testPrms;
    static char            *enableDisableName[] = {"Disabled", "Enabled"};
    static char             printBuf[ST_UART_PRINT_BUFSIZE];
    Bsp_PlatformSocId       socId;

    socId = Bsp_platformGetSocId();

    /* Display test info */
    sCnt = 1;
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "S.No        ID         Description                                    "
        "                             Status    Auto Run\r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "----------------------------------------------------------------------"
        "-----------------------------------------------\r\n");
    for (testCnt = 0u; testCnt < ST_UART_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStUartTestCasePrms[testCnt];

        /* Check if this is halt test case used to get user input */
        if (ST_UART_TCT_HALT == testPrms->testCaseType)
        {
            continue;       /* Skip */
        }

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (!(socId & testPrms->socId))
            {
                runStatus = "NA";
            }
            else if (FALSE == testPrms->enableTest)
            {
                runStatus = "NRQ";
            }
        }
        else
        {
            if (BSP_SOK == testPrms->testResult)
            {
                runStatus = "PASS";
            }
            else
            {
                runStatus = "FAIL";
            }
        }

        snprintf(printBuf, sizeof (printBuf),
                 " %3d  %s_TC%0.5d  %-75.75s  %-8.8s  %-8.8s",
                 sCnt,
                 APP_NAME,
                 testPrms->testCaseId,
                 testPrms->testCaseName,
                 runStatus,
                 enableDisableName[testPrms->enableTest]);
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    return (BSP_SOK);
}

/**
 *  st_uartGenerateTestReports
 */
static Int32 st_uartGenerateTestReports(st_UartUtObj *utObj)
{
    UInt32                      sCnt, testCnt;
    char                       *runStatus, *category, *adequacy;
    st_UartTestCaseParams      *testPrms;
    static char                 printBuf[ST_UART_PRINT_BUFSIZE];
    Bsp_PlatformSocId           socId;

    socId = Bsp_platformGetSocId();

    sCnt = 1;
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "S.No;ID;Requirement Mapping;Description;IR;Category;"
        "Test Adequacy;Test Result;\r\n");
    for (testCnt = 0u; testCnt < ST_UART_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStUartTestCasePrms[testCnt];

        /* Check if this is halt test case used to get user input */
        if (ST_UART_TCT_HALT == testPrms->testCaseType)
        {
            continue;       /* Skip */
        }

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (!(socId & testPrms->socId))
            {
                runStatus = "NA";
            }
            else if (FALSE == testPrms->enableTest)
            {
                runStatus = "NRQ";
            }
        }
        else
        {
            if (BSP_SOK == testPrms->testResult)
            {
                runStatus = "PASS";
            }
            else
            {
                runStatus = "FAIL";
            }
        }

        if (testPrms->testType & ST_TT_FULL)
        {
            category = "Full";
        }
        else if (testPrms->testType & ST_TT_REGRESSION)
        {
            category = "Regression";
        }
        else
        {
            category = "Sanity";
        }

        if (testPrms->testType & ST_TT_STRESS)
        {
            adequacy = "Stress";
        }
        else if (testPrms->testType & ST_TT_NEGATIVE)
        {
            adequacy = "Negative";
        }
        else if (testPrms->testType & ST_TT_PERFORMANCE)
        {
            adequacy = "Performance";
        }
        else if (testPrms->testType & ST_TT_MISC)
        {
            adequacy = "Misc";
        }
        else
        {
            adequacy = "Functional";
        }

        snprintf(printBuf, sizeof (printBuf),
                 "%d;%s_TC%0.5d;%s;%s;;%s;%s;%s",
                 sCnt,
                 APP_NAME,
                 testPrms->testCaseId,
                 testPrms->reqId,
                 testPrms->testCaseName,
                 category,
                 adequacy,
                 runStatus);
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    return (BSP_SOK);
}

/**
 *  st_uartInitUartAppObj
 */
static Int32 st_uartInitUartAppObj(const st_UartUtObj          *utObj,
                                   const st_UartTestCaseParams *testPrms,
                                   st_UartHandleObj            *hObj,
                                   UInt32                      taskCnt)
{
    Int32 retVal = BSP_SOK;
    Int32 txChIdx, rxChIdx, tempCnt, chCnt, reminder;
    const st_UartHandleCfg *handleCfg;
    const st_UartChCfg     *chCfg;
    st_UartChObj           *chObj;

    /* Assign platform type, board and CPU revisions */
    hObj->platformId = utObj->platformId;
    hObj->cpuRev     = utObj->cpuRev;
    hObj->boardId    = utObj->boardId;

    /* Copy user params */
    hObj->testPrms = testPrms;
    hObj->taskId   = taskCnt;
    hObj->devId    = testPrms->devId[taskCnt];
    hObj->devName  = testPrms->devName[taskCnt];
    hObj->txNumCh  = testPrms->txNumCh[taskCnt];
    hObj->rxNumCh  = testPrms->rxNumCh[taskCnt];

    /* Get and copy the handle configuration */
    handleCfg = st_uartGetUartHandleCfg(testPrms->handleCfgId[taskCnt]);
    GT_assert(utObj->traceMask, (NULL != handleCfg));
    memcpy(&hObj->handleCfg, handleCfg, sizeof (st_UartHandleCfg));

    GT_assert(hObj->traceMask, (hObj->txNumCh <= ST_UART_MAX_CH_PER_HANDLE));
    GT_assert(hObj->traceMask, (hObj->rxNumCh <= ST_UART_MAX_CH_PER_HANDLE));

    if (USE_DEF_BAUDRATE == hObj->handleCfg.uartPrms.baudRate)
    {
        hObj->handleCfg.uartPrms.baudRate = utObj->sysCtrl.baudRate;
    }
    if (USE_DEF_CHARLEN == hObj->handleCfg.uartPrms.charLen)
    {
        hObj->handleCfg.uartPrms.charLen = utObj->sysCtrl.charLen;
    }
    if (USE_DEF_FCPARAMRX == hObj->handleCfg.uartPrms.fc.fcParamRx)
    {
        hObj->handleCfg.uartPrms.fc.fcParamRx = utObj->sysCtrl.fcParamRx;
    }
    if (USE_DEF_FCPARAMTX == hObj->handleCfg.uartPrms.fc.fcParamTx)
    {
        hObj->handleCfg.uartPrms.fc.fcParamTx = utObj->sysCtrl.fcParamTx;
    }
    if (USE_DEF_FCTYPE == hObj->handleCfg.uartPrms.fc.fcType)
    {
        hObj->handleCfg.uartPrms.fc.fcType = utObj->sysCtrl.fcType;
    }
    if (USE_DEF_STOPBITS == hObj->handleCfg.uartPrms.stopBits)
    {
        hObj->handleCfg.uartPrms.stopBits = utObj->sysCtrl.stopBits;
    }
    if (USE_DEF_OPMODE == hObj->handleCfg.uartPrms.opMode)
    {
        hObj->handleCfg.uartPrms.opMode = utObj->sysCtrl.opMode;
    }
    if (USE_DEF_PARITY == hObj->handleCfg.uartPrms.parity)
    {
        hObj->handleCfg.uartPrms.parity = utObj->sysCtrl.parity;
    }
    if (USE_DEF_RXTRIGLVL == hObj->handleCfg.uartPrms.rxThreshold)
    {
        hObj->handleCfg.uartPrms.rxThreshold = utObj->sysCtrl.rxThreshold;
    }
    if (USE_DEF_TXTRIGLVL == hObj->handleCfg.uartPrms.txThreshold)
    {
        hObj->handleCfg.uartPrms.txThreshold = utObj->sysCtrl.txThreshold;
    }
    if (USE_DEF_CHUNKSIZE == hObj->handleCfg.uartPrms.chunkSize)
    {
        hObj->handleCfg.uartPrms.chunkSize = utObj->sysCtrl.chunkSize;
    }
    if (USE_DEF_POLLEDMODE_TIMEOUT ==
        hObj->handleCfg.uartPrms.polledModeTimeout)
    {
        hObj->handleCfg.uartPrms.polledModeTimeout =
            utObj->sysCtrl.polledModeTimeout;
    }
    if (USE_DEF_LP_CNT == hObj->handleCfg.loopCnt)
    {
        hObj->handleCfg.loopCnt = utObj->sysCtrl.loopCnt;
    }
    if (USE_DEF_OC_CNT == hObj->handleCfg.openCloseCnt)
    {
        hObj->handleCfg.openCloseCnt = utObj->sysCtrl.openCloseCnt;
    }
    hObj->traceMask = (GT_INFO1 | GT_TraceState_Enable);
    if (FALSE == testPrms->printEnable)
    {
        /* Restrict the number of prints when print is disabled */
        hObj->traceMask = (GT_INFO | GT_TraceState_Enable);
    }
    hObj->sysCtrl = &utObj->sysCtrl;

    /* Get the TX start channel index */
    txChIdx = 0u;
    for (tempCnt = 0u; tempCnt < taskCnt; tempCnt++)
    {
        txChIdx += testPrms->txNumCh[tempCnt];
    }
    GT_assert(utObj->traceMask, (txChIdx < ST_UART_MAX_CH));
    GT_assert(utObj->traceMask,
              ((txChIdx + testPrms->txNumCh[taskCnt]) <= ST_UART_MAX_CH));
    hObj->txStartChIdx = txChIdx;
    /* Get and copy the TX channel configuration */
    for (chCnt = 0u; chCnt < testPrms->txNumCh[taskCnt]; chCnt++)
    {
        chCfg = st_uartGetUartChCfg(testPrms->txChCfgId[txChIdx + chCnt]);
        GT_assert(utObj->traceMask, (NULL != chCfg));

        chObj = &hObj->txChObj[chCnt];
        memcpy(&chObj->chCfg, chCfg, sizeof (st_UartChCfg));
        if (USE_DEF_BYTESPERSUBMIT == chObj->chCfg.maxBytesPerSubmit)
        {
            chObj->chCfg.maxBytesPerSubmit = utObj->sysCtrl.txBytesPerSubmit;
            /* Driver has this limitation now.
             * It can transfer only multiple of TX threshold bytes */
            if (UART_OPMODE_DMAINTERRUPT == hObj->handleCfg.uartPrms.opMode)
            {
                reminder = chObj->chCfg.maxBytesPerSubmit %
                                hObj->handleCfg.uartPrms.txThreshold;
                chObj->chCfg.maxBytesPerSubmit -= reminder;
            }
        }
    }

    /* Get the RX start channel index */
    rxChIdx = 0u;
    for (tempCnt = 0u; tempCnt < taskCnt; tempCnt++)
    {
        rxChIdx += testPrms->rxNumCh[tempCnt];
    }
    GT_assert(utObj->traceMask, (rxChIdx < ST_UART_MAX_CH));
    GT_assert(utObj->traceMask,
              ((rxChIdx + testPrms->rxNumCh[taskCnt]) <= ST_UART_MAX_CH));
    hObj->rxStartChIdx = rxChIdx;
    /* Get and copy the RX channel configuration */
    for (chCnt = 0u; chCnt < testPrms->rxNumCh[taskCnt]; chCnt++)
    {
        chCfg = st_uartGetUartChCfg(testPrms->rxChCfgId[rxChIdx + chCnt]);
        GT_assert(utObj->traceMask, (NULL != chCfg));

        chObj = &hObj->rxChObj[chCnt];
        memcpy(&chObj->chCfg, chCfg, sizeof (st_UartChCfg));
        if (USE_DEF_BYTESPERSUBMIT == chObj->chCfg.maxBytesPerSubmit)
        {
            chObj->chCfg.maxBytesPerSubmit = utObj->sysCtrl.rxBytesPerSubmit;
            /* Driver has this limitation now.
             * It can transfer only multiple of RX threshold bytes */
            if (UART_OPMODE_DMAINTERRUPT == hObj->handleCfg.uartPrms.opMode)
            {
                reminder = chObj->chCfg.maxBytesPerSubmit %
                                hObj->handleCfg.uartPrms.rxThreshold;;
                chObj->chCfg.maxBytesPerSubmit -= reminder;
            }
        }
    }

    return (retVal);
}

/* Main menu 0 string */
static char gStUartMenuMain0[] =
{
    "\r\n "
    "\r\n ============="
    "\r\n UART UT Select"
    "\r\n ============="
    "\r\n "
};

/* Main menu string */
static char gStUartMenuMain[] =
{
    "\r\n 1: Manual testing (select specific test case to run)"
    "\r\n 2: Sanity (BFT) testing"
    "\r\n 3: Regression testing"
    "\r\n 4: Full testing"
    "\r\n 5: Performance testing"
    "\r\n d: Display test cases"
    "\r\n g: Generate test report"
    "\r\n "
    "\r\n s: System Settings"
    "\r\n "
    "\r\n q: Quit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

static char gStUartMenuSettings0[] = {
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
};

static char gStUartMenuSettings1[] = {
    "\r\n "
    "\r\n o: Op Mode"
    "\r\n b: Baudrate"
    "\r\n l: Character Length"
    "\r\n s: Stop Bits"
    "\r\n p: Parity"
    "\r\n f: Flow Control"
    "\r\n r: RX Flow Control"
    "\r\n t: TX Flow Control"
    "\r\n c: Chunk Size"
    "\r\n 1: RX Threshold"
    "\r\n 2: TX Threshold"
    "\r\n 3: RX Bytes Per Submit"
    "\r\n 4: TX Bytes Per Submit"
    "\r\n 5: Polled Mode Timeout"
    "\r\n 6: Skip RX Test Case"
    "\r\n 7: Skip TX Only Test Case"
    "\r\n h: Skip Halt Test Case"
    "\r\n i: Execution Loop Count"
    "\r\n 8: Open/Close Count"
    "\r\n e: Runtime Print Enable"
    "\r\n "
    "\r\n q: Quit "
    "\r\n"
};

/**
 *  st_uartMenuSettings
 */
static Void st_uartMenuSettings(st_UartUtObj *utObj)
{
    char           option, inputStr[10];
    Bool           done = FALSE;
    Int32          value;
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    st_uartMenuSettingsShow(utObj);

    while (!done)
    {
        GT_0trace(utObj->traceMask, GT_INFO, " Enter Choice: \r\n");
        BspOsal_scanf("%s", inputStr);
        option = inputStr[0u];

        switch (option)
        {
            case 'o':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Op Mode [0: Polled, 1: Interrupt, 2: DMA]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 0:
                        sysCtrl->opMode = UART_OPMODE_POLLED;
                        break;

                    case 1:
                        sysCtrl->opMode = UART_OPMODE_INTERRUPT;
                        break;

                    case 2:
                        sysCtrl->opMode = UART_OPMODE_DMAINTERRUPT;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 'b':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Baudrate [2400, 4800, 9600, 19200, 38400, "
                          "57600, 115200, 3686400]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 2400:
                        sysCtrl->baudRate = UART_BAUDRATE_2_4K;
                        break;

                    case 4800:
                        sysCtrl->baudRate = UART_BAUDRATE_4_8K;
                        break;

                    case 9600:
                        sysCtrl->baudRate = UART_BAUDRATE_9_6K;
                        break;

                    case 19200:
                        sysCtrl->baudRate = UART_BAUDRATE_19_2K;
                        break;

                    case 38400:
                        sysCtrl->baudRate = UART_BAUDRATE_38_4K;
                        break;

                    case 57600:
                        sysCtrl->baudRate = UART_BAUDRATE_57_6K;
                        break;

                    case 115200:
                        sysCtrl->baudRate = UART_BAUDRATE_115_2K;
                        break;

                    case 3686400:
                        sysCtrl->baudRate = UART_BAUDRATE_3686_4K;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 'l':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Character Length [5, 6, 7, 8]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 5:
                        sysCtrl->charLen = UART_CHARLEN_5;
                        break;

                    case 6:
                        sysCtrl->charLen = UART_CHARLEN_6;
                        break;

                    case 7:
                        sysCtrl->charLen = UART_CHARLEN_7;
                        break;

                    case 8:
                        sysCtrl->charLen = UART_CHARLEN_8;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 's':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Stop Bits [0: STOPBITS_1, 1: STOPBITS_1.5,"
                          " 2: STOPBITS_2]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 0:
                        sysCtrl->stopBits = UART_NUMSTOPBITS_1;
                        break;

                    case 1:
                        sysCtrl->stopBits = UART_NUMSTOPBITS_1_5;
                        break;

                    case 2:
                        sysCtrl->stopBits = UART_NUMSTOPBITS_2;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 'p':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Parity [0: NONE, 1: ODD, 2: EVEN,"
                          " 3: FORCED0, 4: FORCED1]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 0:
                        sysCtrl->parity = UART_PARITY_NO;
                        break;

                    case 1:
                        sysCtrl->parity = UART_PARITY_ODD;
                        break;

                    case 2:
                        sysCtrl->parity = UART_PARITY_EVEN;
                        break;

                    case 3:
                        sysCtrl->parity = UART_PARITY_FORCED0;
                        break;

                    case 4:
                        sysCtrl->parity = UART_PARITY_FORCED1;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 'f':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Flow Control [0: NONE, 1: SW, 2: HW]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 0:
                        sysCtrl->fcType = UART_FCTYPE_NONE;
                        break;

                    case 1:
                        sysCtrl->fcType = UART_FCTYPE_SW;
                        break;

                    case 2:
                        sysCtrl->fcType = UART_FCTYPE_HW;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 'r':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " RX Flow Control [0: NONE, 1: XON_XOFF_2,"
                          " 2: XON_XOFF_1, 3: XON_XOFF_12, 4: AUTO_RTS]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 0:
                        sysCtrl->fcParamRx = UART_FCPARAM_RXNONE;
                        break;

                    case 1:
                        sysCtrl->fcParamRx = UART_FCPARAM_RXXONXOFF_2;
                        break;

                    case 2:
                        sysCtrl->fcParamRx = UART_FCPARAM_RXXONXOFF_1;
                        break;

                    case 3:
                        sysCtrl->fcParamRx = UART_FCPARAM_RXXONXOFF_12;
                        break;

                    case 4:
                        sysCtrl->fcParamRx = UART_FCPARAM_AUTO_RTS;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 't':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " TX Flow Control [0: NONE, 1: XON_XOFF_2,"
                          " 2: XON_XOFF_1, 3: XON_XOFF_12, 4: AUTO_CTS]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 0:
                        sysCtrl->fcParamTx = UART_FCPARAM_TXNONE;
                        break;

                    case 1:
                        sysCtrl->fcParamTx = UART_FCPARAM_TXXONXOFF_2;
                        break;

                    case 2:
                        sysCtrl->fcParamTx = UART_FCPARAM_TXXONXOFF_1;
                        break;

                    case 3:
                        sysCtrl->fcParamTx = UART_FCPARAM_TXXONXOFF_12;
                        break;

                    case 4:
                        sysCtrl->fcParamTx = UART_FCPARAM_AUTO_CTS;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case 'c':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Chunksize: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);
                sysCtrl->chunkSize = value;
                break;

            case '1':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " RX Threshold [8, 16, 56, 60]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 8:
                        sysCtrl->rxThreshold = UART_RXTRIGLVL_8;
                        break;

                    case 16:
                        sysCtrl->rxThreshold = UART_RXTRIGLVL_16;
                        break;

                    case 56:
                        sysCtrl->rxThreshold = UART_RXTRIGLVL_56;
                        break;

                    case 60:
                        sysCtrl->rxThreshold = UART_RXTRIGLVL_60;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case '2':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " TX Threshold [8, 16, 32, 56]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                switch (value)
                {
                    case 8:
                        sysCtrl->txThreshold = UART_TXTRIGLVL_8;
                        break;

                    case 16:
                        sysCtrl->txThreshold = UART_TXTRIGLVL_16;
                        break;

                    case 32:
                        sysCtrl->txThreshold = UART_TXTRIGLVL_32;
                        break;

                    case 56:
                        sysCtrl->txThreshold = UART_TXTRIGLVL_56;
                        break;

                    default:
                        GT_0trace(utObj->traceMask, GT_INFO,
                                  " Invalid Option!!\r\n");
                        break;
                }
                break;

            case '3':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " RX bytes per submit: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                if (value > ST_UART_RX_BUF_SIZE)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                        " Value provided is more than RX buffer size!!\r\n");
                }
                else if (value != USE_DEF_BYTESPERSUBMIT)
                {
                    sysCtrl->rxBytesPerSubmit = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        " This matches with default flag, give another value\r\n");
                }
                break;

            case '4':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " TX bytes per submit: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                if (value > ST_UART_TX_BUF_SIZE)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                        " Value provided is more than TX buffer size!!\r\n");
                }
                else if (value != USE_DEF_BYTESPERSUBMIT)
                {
                    sysCtrl->txBytesPerSubmit = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        " This matches with default flag, give another value\r\n");
                }
                break;

            case '5':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Polled Mode Timeout: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                if (value != USE_DEF_POLLEDMODE_TIMEOUT)
                {
                    sysCtrl->polledModeTimeout = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        " This matches with default flag, give another value\r\n");
                }
                break;

            case '6':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip RX Test [0: Enable, 1: Skip]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                sysCtrl->skipRxTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipRxTests = TRUE;
                }
                break;

            case '7':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip TX Only Test [0: Enable, 1: Skip]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                sysCtrl->skipTxOnlyTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipTxOnlyTests = TRUE;
                }
                break;

            case 'h':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip Halt Test Enable [0: Enable, 1: Skip]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                sysCtrl->skipHaltTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipHaltTests = TRUE;
                }
                break;

            case 'i':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Loop count in frames: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                if (value != USE_DEF_LP_CNT)
                {
                    sysCtrl->loopCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        " This matches with default flag, give another value\r\n");
                }
                break;

            case '8':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Open/close count: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                if (value != USE_DEF_OC_CNT)
                {
                    sysCtrl->openCloseCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        " This matches with default flag, give another value\r\n");
                }
                break;

            case 'e':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Runtime Print Enable [0: Disable, 1: Enable]: \r\n");
                BspOsal_scanf("%s", inputStr);
                value = atoi(inputStr);

                sysCtrl->rtPrintEnable = FALSE;
                if (1 == value)
                {
                    sysCtrl->rtPrintEnable = TRUE;
                }
                break;

            case 'q':
                done = TRUE;
                break;
        }
        fflush(stdin);
    }

    return;
}

/**
 *  st_uartMenuMainShow
 */
static Void st_uartMenuMainShow(st_UartUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStUartMenuMain0);
    st_uartMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStUartMenuMain);

    return;
}

/**
 *  st_uartMenuSettingsShow
 */
static Void st_uartMenuSettingsShow(st_UartUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStUartMenuSettings0);
    st_uartMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStUartMenuSettings1);

    return;
}

/**
 *  st_uartMenuCurrentSettingsShow
 */
static Void st_uartMenuCurrentSettingsShow(st_UartUtObj *utObj)
{
    static char   *enableDisableName[] = {"OFF", "ON"};
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    GT_0trace(utObj->traceMask, GT_INFO, "\r\n Current System Settings:");
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ------------------------");
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Op Mode                : %s",
              st_uartGetOpModeString(sysCtrl->opMode));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Baud Rate              : %s",
              st_uartGetBaudRateString(sysCtrl->baudRate));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Character Length       : %s",
              st_uartGetCharLenString(sysCtrl->charLen));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Stop Bits              : %s",
              st_uartGetStopBitsString(sysCtrl->stopBits));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Parity                 : %s",
              st_uartGetParityString(sysCtrl->parity));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Flow Control           : %s",
              st_uartGetFcTypeString(sysCtrl->fcType));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n RX Flow Control        : %s",
              st_uartGetFcParamRxString(sysCtrl->fcParamRx));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n TX Flow Control        : %s",
              st_uartGetFcParamTxString(sysCtrl->fcParamTx));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Chunk Size             : %d",sysCtrl->chunkSize);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n RX Threshold           : %s",
              st_uartGetRxThresholdString(sysCtrl->rxThreshold));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n TX Threshold           : %s",
              st_uartGetTxThresholdString(sysCtrl->txThreshold));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n RX Bytes per Submit    : %d", sysCtrl->rxBytesPerSubmit);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n TX Bytes per Submit    : %d", sysCtrl->txBytesPerSubmit);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Polled Mode Timeout    : 0x%0.8X",
              sysCtrl->polledModeTimeout);

    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip RX Test Cases     : %s",
              enableDisableName[sysCtrl->skipRxTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Halt Test Cases   : %s",
              enableDisableName[sysCtrl->skipHaltTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Loop Count             : %d", sysCtrl->loopCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Open/Close Count       : %d", sysCtrl->openCloseCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Runtime Print          : %s",
              enableDisableName[sysCtrl->rtPrintEnable]);
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ");

    return;
}

/**
 *  st_uartSetDefaultCfg
 */
static Void st_uartSetDefaultCfg(st_UartUtObj *utObj)
{
    UInt32 testCnt;
    st_UartTestCaseParams *testPrms;

    utObj->traceMask  = (GT_INFO1 | GT_TraceState_Enable);
    utObj->platformId = BSP_PLATFORM_ID_UNKNOWN;
    utObj->cpuRev     = BSP_PLATFORM_CPU_REV_1_0;
    utObj->boardId    = BSP_BOARD_UNKNOWN;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        st_uartDetectBoard(utObj);
    }

    utObj->sysCtrl.opMode = DEF_UART_OPMODE;
    utObj->sysCtrl.baudRate = DEF_UART_BAUDRATE;
    utObj->sysCtrl.charLen = DEF_UART_CHARLEN;
    utObj->sysCtrl.stopBits = DEF_UART_STOPBITS;
    utObj->sysCtrl.parity = DEF_UART_PARITY;
    utObj->sysCtrl.fcType = DEF_UART_FCTYPE;
    utObj->sysCtrl.fcParamRx = DEF_UART_FCPARAMRX;
    utObj->sysCtrl.fcParamTx = DEF_UART_FCPARAMTX;
    utObj->sysCtrl.chunkSize = DEF_UART_CHUNKSIZE;
    utObj->sysCtrl.rxThreshold = DEF_UART_RXTRIGLVL;
    utObj->sysCtrl.txThreshold = DEF_UART_TXTRIGLVL;
    utObj->sysCtrl.rxBytesPerSubmit = DEF_RX_BYTESPERSUBMIT;
    utObj->sysCtrl.txBytesPerSubmit = DEF_TX_BYTESPERSUBMIT;
    utObj->sysCtrl.polledModeTimeout = DEF_UART_POLLEDMODE_TIMEOUT;

    utObj->sysCtrl.skipRxTests = FALSE;
    utObj->sysCtrl.skipHaltTests = FALSE;
    utObj->sysCtrl.loopCnt       = DEF_LOOP_CNT;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        utObj->sysCtrl.loopCnt = DEF_LOOP_CNT_EVM;
    }
    utObj->sysCtrl.openCloseCnt    = DEF_OPEN_CLOSE_CNT;
    utObj->sysCtrl.rtPrintEnable   = FALSE;

    /* Mark all test cases as not run and set result to PASS */
    for (testCnt = 0u; testCnt < ST_UART_NUM_TESTCASES; testCnt++)
    {
        testPrms             = &gStUartTestCasePrms[testCnt];
        testPrms->isRun      = FALSE;
        testPrms->testResult = BSP_SOK;
    }

    return;
}

/**
 *  st_uartDetectBoard
 */
static Int32 st_uartDetectBoard(st_UartUtObj *utObj)
{
    /* Get platform type */
    utObj->platformId = Bsp_platformGetId();
    if ((utObj->platformId == BSP_PLATFORM_ID_UNKNOWN) ||
        (utObj->platformId >= BSP_PLATFORM_ID_MAX))
    {
        utObj->platformId = BSP_PLATFORM_ID_UNKNOWN;
    }

    /* Get CPU version */
    utObj->cpuRev = Bsp_platformGetCpuRev();
    if (utObj->cpuRev >= BSP_PLATFORM_CPU_REV_MAX)
    {
        utObj->cpuRev = BSP_PLATFORM_CPU_REV_UNKNOWN;
    }

    /* Detect board */
    utObj->boardId = Bsp_boardGetId();
    if (utObj->boardId >= BSP_BOARD_MAX)
    {
        utObj->boardId = BSP_BOARD_UNKNOWN;
    }

    return (BSP_SOK);
}
