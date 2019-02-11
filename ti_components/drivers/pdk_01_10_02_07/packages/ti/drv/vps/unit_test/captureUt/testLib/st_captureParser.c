/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file st_captureParser.c
 *
 *  \brief User interface for CAPTURE driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on CAPTURE driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_capture.h>
#include <testInput/st_captureTestCases.h>

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

static Int32 st_captRunTestCase(st_CaptUtObj          *utObj,
                                st_CaptApp_TestParams *testPrms);
static void st_captTestTask(UArg arg0, UArg arg1);

static Int32 st_captGetTestCaseIdx(UInt32 testCaseId, Bool isSearchForward);
static Bool st_captCheckIfTestToBeSkipped(st_CaptUtObj                *utObj,
                                          const st_CaptApp_TestParams *testPrms,
                                          UInt32                       testType);
static Int32 st_captDisplayTestInfo(st_CaptUtObj *utObj);
static Int32 st_captGenerateTestReports(st_CaptUtObj *utObj);

static Int32 st_captInitCaptAppObj(const st_CaptUtObj          *utObj,
                                   const st_CaptApp_TestParams *testPrms,
                                   st_CaptApp_Obj              *appObj,
                                   UInt32                       taskCnt);

static Void st_captMenuSettings(st_CaptUtObj *utObj);
static Void st_captMenuMainShow(st_CaptUtObj *utObj);
static Void st_captMenuSettingsShow(st_CaptUtObj *utObj);
static Void st_captMenuCurrentSettingsShow(st_CaptUtObj *utObj);
static Void st_captSetDefaultCfg(st_CaptUtObj *utObj);
static Int32 st_captDetectBoard(st_CaptUtObj *utObj);
static Int32 st_captCreateTestTasks(st_CaptUtObj                *utObj,
                                    const st_CaptApp_TestParams *testPrms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* CAPTURE Test application stack. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gStCaptTestTskStack, 32)
#pragma DATA_SECTION(gStCaptTestTskStack, ".bss:taskStackSection")
#endif
static UInt8            gStCaptTestTskStack[VPS_CAPT_INST_MAX][
    ST_TSK_STACK_SIZE];

/* CAPTURE application object per driver handle. */
static st_CaptApp_Obj   gStCaptAppObjs[VPS_CAPT_INST_MAX];

/* CAPTURE task complete semaphore */
static Semaphore_Handle gStCaptTaskCompleteSem;

/* CAPTURE UT object. */
st_CaptUtObj            gCaptUtObj;

static volatile UInt32  gExitApp;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_captParser
 */
Int32 st_captParser(void)
{
    char   option, inputStr[10];
    Bool   done;
    Int32  retVal = BSP_SOK, tempRetVal;
    Int32  testCaseIdx, startIdx;
    UInt32 testCnt, testType, testCaseId;
    UInt32 startTime, endTime, startTime1, endTime1;
    UInt32 hrs, mins, secs, durationInSecs;
    BspUtils_MemHeapStatus startHeapStat;
    st_CaptUtObj          *utObj;
    st_CaptApp_TestParams *testPrms;
    Uint32 uartTimeout = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

    utObj = &gCaptUtObj;
    st_captSetDefaultCfg(utObj);
    st_resetTestResult();

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    startTime        = BspOsal_getCurTimeInMsec();
    done             = FALSE;
    utObj->skipCount = utObj->disableCount = 0u;
    while (!done)
    {
        st_captMenuMainShow(utObj);

        tempRetVal = BspUtils_uartGetChar(&option, uartTimeout);
        if (tempRetVal != BSP_SOK)
        {
            /* Auto-run: Full test and exit */
            option = '4';
            done = TRUE;
        }
        else
        {
            /* Disable autorun if user enters any value */
            uartTimeout = BSP_UTILS_UART_RX_WAIT_FOREVER;
        }

        GT_0trace(utObj->traceMask, GT_INFO, " \r\n");

        testType = ST_TT_SANITY;
        switch (option)
        {
            case 's':
                st_captMenuSettings(utObj);
                break;

            case 'q':
                done = TRUE;
                break;

            case '1':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Manual testing - Enter Test Case Id: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                testCaseId = (UInt32) atoi(inputStr);

                /* Find the test case to run */
                testCaseIdx = st_captGetTestCaseIdx(testCaseId, FALSE);
                if (testCaseIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              " Test case ID not found\r\n");
                }
                else
                {
                    testPrms = &gStCaptTestCasePrms[testCaseIdx];

                    retVal = st_captRunTestCase(utObj, testPrms);
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
                testCaseId = 0U;
                if (tempRetVal == BSP_SOK)
                {
                    /* Auto run */
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        " Enter Start Test Case Id "
                        "(Enter 0 to start from first): \r\n");
                    BspUtils_uartGetStr(
                        inputStr,
                        sizeof(inputStr),
                        BSP_UTILS_UART_RX_WAIT_FOREVER);
                    testCaseId = (UInt32) atoi(inputStr);
                }
                startIdx   = st_captGetTestCaseIdx(testCaseId, TRUE);
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
                     testCnt < ST_CAPT_NUM_TESTCASES;
                     testCnt++)
                {
                    testPrms = &gStCaptTestCasePrms[testCnt];

                    /* Check whether to execute test or not */
                    if (st_captCheckIfTestToBeSkipped(utObj, testPrms, testType))
                    {
                        continue;       /* Skip test */
                    }

                    retVal = st_captRunTestCase(utObj, testPrms);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  " Failed to run test case!!\r\n");
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1       = BspOsal_getCurTimeInMsec();
                durationInSecs = ((endTime1 - startTime1) / 1000u);
                hrs  = durationInSecs / (60u * 60u);
                mins = (durationInSecs / 60u) - (hrs * 60u);
                secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
                GT_3trace(utObj->traceMask, GT_INFO,
                          " |TOTAL TEST DURATION|: %d hrs %d mins %d secs\r\n",
                          hrs, mins, secs);
                break;

            case '5':
                testType = ST_TT_PERFORMANCE;
                startIdx = st_captGetTestCaseIdx(0u, TRUE);
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
                     testCnt < ST_CAPT_NUM_TESTCASES;
                     testCnt++)
                {
                    testPrms = &gStCaptTestCasePrms[testCnt];

                    /* Check whether to execute test or not */
                    if (st_captCheckIfTestToBeSkipped(utObj, testPrms, testType))
                    {
                        continue;       /* Skip test */
                    }

                    retVal = st_captRunTestCase(utObj, testPrms);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  " Failed to run test case!!\r\n");
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1       = BspOsal_getCurTimeInMsec();
                durationInSecs = ((endTime1 - startTime1) / 1000u);
                hrs  = durationInSecs / (60u * 60u);
                mins = (durationInSecs / 60u) - (hrs * 60u);
                secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
                GT_3trace(utObj->traceMask, GT_INFO,
                          " |TOTAL TEST DURATION|: %d hrs %d mins %d secs\r\n",
                          hrs, mins, secs);
                break;

            case 'd':
                /* Display test info */
                st_captDisplayTestInfo(utObj);
                break;

            case 'g':
                /* Generate test report */
                st_captGenerateTestReports(utObj);
                break;

            default:
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Invalid option try again!!\r\n");
                break;
        }
    }

    /* check for leak */
    st_captCheckHeapStat(&startHeapStat, utObj->traceMask);

    /* Print test results */
    st_printTestResult(utObj->skipCount, utObj->disableCount);
    st_captDisplayTestInfo(utObj);
    st_captGenerateTestReports(utObj);

    endTime        = BspOsal_getCurTimeInMsec();
    durationInSecs = ((endTime - startTime) / 1000u);
    hrs  = durationInSecs / (60u * 60u);
    mins = (durationInSecs / 60u) - (hrs * 60u);
    secs = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
    GT_3trace(utObj->traceMask, GT_INFO,
              " |TOTAL UT DURATION|: %d hrs %d mins %d secs\r\n",
              hrs, mins, secs);

    return (retVal);
}

/**
 *  st_captRunTestCase
 */
static Int32 st_captRunTestCase(st_CaptUtObj          *utObj,
                                st_CaptApp_TestParams *testPrms)
{
    char  inputStr[10];
    Int32 retVal = BSP_SOK;

    testPrms->isRun = TRUE;

    switch (testPrms->testConfig.testCaseType)
    {
        case ST_CAPT_TCT_DETECT:
        case ST_CAPT_TCT_MAIN:
        case ST_CAPT_TCT_NON_MUX_FRAME:
        case ST_CAPT_TCT_MUX_FRAME:

            /* Create all test tasks */
            retVal = st_captCreateTestTasks(utObj, testPrms);
            if (BSP_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          " CAPTURE test failed!!\r\n");
            }

            /* Store the test result */
            testPrms->testResult = retVal;
            break;

        case ST_CAPT_TCT_HALT:
            /* NULL pointer check */
            GT_assert(utObj->traceMask,
                      (NULL != testPrms->testConfig.testDescStr));
            GT_1trace(utObj->traceMask, GT_INFO,
                      "\r\n User Input Halt: %s\r\n",
                      testPrms->testConfig.testDescStr);
            BspUtils_uartGetStr(
                inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
            break;

        default:
            GT_1trace(utObj->traceMask, GT_INFO,
                      " Invalid test case type: %d!!\r\n",
                      testPrms->testConfig.testCaseType);
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  st_captCreateTestTasks
 */
static Int32 st_captCreateTestTasks(st_CaptUtObj                *utObj,
                                    const st_CaptApp_TestParams *testPrms)
{
    Int32                  retVal  = BSP_SOK, testResult = BSP_SOK;
    UInt32                 taskCnt = 0, createdTsk;
    UInt32                 startTime, endTime, hrs, mins, secs, msecs;
    UInt32                 durationInMsecs, durationInSecs;
    BspUtils_MemHeapStatus startHeapStat;
    st_CaptApp_Obj        *appObj;
    Task_Params            tskPrms[VPS_CAPT_INST_MAX];
    Task_Handle            tskHandle[VPS_CAPT_INST_MAX];
    Semaphore_Params       semPrms;
    UInt32                 taskCntCapt = 0;
    char tempString[200u];

    /* NULL pointer check */
    GT_assert(utObj->traceMask, (NULL != testPrms));
    GT_assert(utObj->traceMask,
              (testPrms->testConfig.numHandles <= VPS_CAPT_INST_MAX));
    GT_assert(utObj->traceMask, (NULL != testPrms->testConfig.testDescStr));

    startTime = BspOsal_getCurTimeInMsec();
    GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
    GT_1trace(utObj->traceMask, GT_INFO,
              " |TEST START|:: %d ::\r\n", testPrms->testConfig.testCaseId);
    GT_1trace(utObj->traceMask, GT_INFO,
              " |TEST PARAM|:: %s ::\r\n", testPrms->testConfig.testDescStr);
    if (NULL != testPrms->testConfig.swReqtId)
    {
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |SR|:: %s ::\r\n", testPrms->testConfig.swReqtId);
    }
    if (NULL != testPrms->testConfig.userInfo)
    {
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |User Info|:: %s ::\r\n", testPrms->testConfig.userInfo);
    }
    GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
    if (testPrms->testConfig.testCaseType == ST_CAPT_TCT_DETECT)
    {
        GT_0trace(utObj->traceMask, GT_INFO,
                  "|TEST CASE|:: ST_CAPT_TCT_DETECT ::\r\n");
    }
    else if (testPrms->testConfig.testCaseType == ST_CAPT_TCT_MAIN)
    {
        GT_0trace(utObj->traceMask, GT_INFO,
                  "|TEST CASE|:: ST_CAPT_TCT_MAIN ::\r\n");
    }
    else if (testPrms->testConfig.testCaseType == ST_CAPT_TCT_NON_MUX_FRAME)
    {
        GT_0trace(utObj->traceMask, GT_INFO,
                  "|TEST CASE|:: ST_CAPT_TCT_NON_MUX_FRAME ::\r\n");
    }
    else if (testPrms->testConfig.testCaseType == ST_CAPT_TCT_MUX_FRAME)
    {
        GT_0trace(utObj->traceMask, GT_INFO,
                  "|TEST CASE|:: ST_CAPT_TCT_MUX_FRAME ::\r\n");
    }

    startTime = BspOsal_getCurTimeInMsec();   /* Reset time to exclude print */

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    Semaphore_Params_init(&semPrms);
    gStCaptTaskCompleteSem = Semaphore_create(0u, &semPrms, NULL);
    if (NULL == gStCaptTaskCompleteSem)
    {
        GT_0trace(utObj->traceMask, GT_ERR, " Sem create failed!!!\r\n");
        retVal = BSP_EALLOC;
    }

    memset(&gStCaptAppObjs, 0u, sizeof (gStCaptAppObjs));
    memset(&tskHandle, 0u, sizeof (tskHandle));
    if (BSP_SOK == retVal)
    {
        createdTsk = 0u;

        for (taskCnt = 0u; taskCnt < testPrms->testConfig.numHandles; taskCnt++)
        {
            appObj = &gStCaptAppObjs[taskCntCapt];

            retVal = st_captInitCaptAppObj(utObj, testPrms, appObj, taskCnt);
            if (BSP_SOK != retVal)
            {
                break;
            }

            /* Create individual tasks */
            Task_Params_init(&tskPrms[taskCnt]);
            tskPrms[taskCnt].stack     = &gStCaptTestTskStack[taskCntCapt][0u];
            tskPrms[taskCnt].stackSize = ST_TSK_STACK_SIZE;
            tskPrms[taskCnt].arg0      = (UArg) appObj;
            tskPrms[taskCnt].arg1      = (UArg) utObj;
            tskHandle[taskCnt]         = Task_create(
                (Task_FuncPtr) st_captTestTask,
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
            taskCntCapt++;
            snprintf(tempString, sizeof (tempString),
                     " ST_CAPTURE Task %d", (unsigned int) taskCnt);
            BspUtils_prfLoadRegister(tskHandle[taskCnt], tempString);
        }
    }

    if (BSP_SOK == retVal)
    {
        for (taskCnt = 0u; taskCnt < createdTsk; taskCnt++)
        {
            /* Wait for all tasks to complete */
            Semaphore_pend(gStCaptTaskCompleteSem, BIOS_WAIT_FOREVER);
        }
    }

    for (taskCnt = 0u; taskCnt < taskCntCapt; taskCnt++)
    {
        testResult += gStCaptAppObjs[taskCnt].testResult;
    }
    /* Store the local error value */
    testResult += retVal;

    /* Fail is pass in case of negative tests. Change return value. */
    if (testPrms->testConfig.testType & ST_TT_NEGATIVE)
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
    for (taskCnt = 0u; taskCnt < testPrms->testConfig.numHandles; taskCnt++)
    {
        if (NULL != tskHandle[taskCnt])
        {
            BspUtils_prfLoadUnRegister(tskHandle[taskCnt]);
            Task_delete(&tskHandle[taskCnt]);
            tskHandle[taskCnt] = NULL;
        }
    }

    if (NULL != gStCaptTaskCompleteSem)
    {
        Semaphore_delete(&gStCaptTaskCompleteSem);
    }

    /* check for leak */
    st_captCheckHeapStat(&startHeapStat, utObj->traceMask);

    endTime         = BspOsal_getCurTimeInMsec();
    durationInMsecs = (endTime - startTime);
    durationInSecs  = (durationInMsecs / 1000u);
    hrs   = durationInSecs / (60u * 60u);
    mins  = (durationInSecs / 60u) - (hrs * 60u);
    secs  = durationInSecs - (hrs * 60u * 60u) - (mins * 60u);
    msecs = durationInMsecs - ((hrs * 60u * 60u) + (mins * 60u) + secs) * 1000u;
    GT_4trace(utObj->traceMask, GT_INFO,
              " |TEST DURATION|:: %d:%0.2d:%0.2d:%0.3d ::\r\n",
              hrs, mins, secs, msecs);

    snprintf(tempString, sizeof (tempString), "%s",
             testPrms->testConfig.testDescStr);
    st_logTestResult(testResult, testPrms->testConfig.testCaseId, tempString);

    return (testResult);
}

/**
 *  st_captTestTask
 */
static void st_captTestTask(UArg arg0, UArg arg1)
{
    Int32           retVal;
    st_CaptApp_Obj *appObj;
    st_CaptUtObj   *utObj;

    /* Run the test */
    appObj = (st_CaptApp_Obj *) arg0;
    utObj  = (st_CaptUtObj *) arg1;

    /* Run the Tx test */
    retVal = st_captMainTestCase(appObj, utObj);

    appObj->testResult = retVal;

    /* Test complete. Signal it */
    Semaphore_post(gStCaptTaskCompleteSem);

    return;
}

#if 0 // TBD
/*
 *  Reset task
 * When overflow occurs, this task will run.
 * It will stop the driver, reset it and again start it.
 */

static void st_captTskReset(UArg arg0, UArg arg1)

{
    st_CaptApp_Obj        *appObj = (st_CaptApp_Obj *) arg0;
    st_CaptApp_InstObj    *instObj;
    UInt32 captInstCnt = 0;
    Int32 retVal;
    st_CaptApp_TestParams *testPrms;

    GT_assert(BspCaptUtTrace, (appObj != NULL));

    overflowSem = BspOsal_semCreate(0, FALSE);
    GT_assert(BspCaptUtTrace, (overflowSem != NULL));

    testPrms = appObj->testPrms;

    while (1U)
    {
        /* Wait for overflow to occur */
        BspOsal_semWait(overflowSem, BSP_OSAL_WAIT_FOREVER);
        if ((UInt32) TRUE == gExitApp)
        {
            BspOsal_semDelete(&overflowSem);
            break;
        }
        for (captInstCnt = 0; captInstCnt < testPrms->testConfig.numHandles;
             captInstCnt++)
        {
            Vps_CaptOverflowCheckParams overflowCheckParams;
            /* For all instances, check if the overflow has occured on that
             *instance. */
            instObj = &appObj->instObj[captInstCnt];
            retVal  = Fvid2_control(
                instObj->drvHandle,
                IOCTL_VPS_CAPT_CHECK_OVERFLOW,
                &overflowCheckParams,
                NULL);
            /* If overflow has occured, initiate the reset sequence */
            if (TRUE == overflowCheckParams.isOverflowOccured)
            {
                /* Count is reset befor the reset. If overflow
                 * occurs in reset, then it will be lost otherwise*/
                instObj->overflowCount = 0;
                /*Stop the driver*/
                retVal = Fvid2_stop(instObj->drvHandle, NULL);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspCaptUtTrace, GT_ERR,
                              UT_NAME ": Capture Stop Failed!!!\r\n");
                }
                if (FVID2_SOK == retVal)
                {
                    /* Reset the VIP */
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_VPS_CAPT_RESET_VIP,
                        NULL,
                        NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(BspCaptUtTrace, GT_ERR,
                                  UT_NAME ": Capture Reset Failed!!!\r\n");
                    }
                }
                if (FVID2_SOK == retVal)
                {
                    /* Restart the driver */
                    retVal = Fvid2_start(instObj->drvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(BspCaptUtTrace, GT_ERR,
                                  UT_NAME ": Capture Start Failed!!!\r\n");
                    }
                }

                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }
    }
    return;
}

#endif

/**
 *  st_captGetTestCaseIdx
 */
static Int32 st_captGetTestCaseIdx(UInt32 testCaseId, Bool isSearchForward)
{
    Int32  testCaseIdx = -1;
    UInt32 testCnt;
    const st_CaptApp_TestParams *testPrms;

    testPrms = &gStCaptTestCasePrms[0u];
    for (testCnt = 0u; testCnt < ST_CAPT_NUM_TESTCASES; testCnt++)
    {
        if (TRUE == isSearchForward)
        {
            if (testPrms->testConfig.testCaseId >= testCaseId)
            {
                testCaseIdx = testCnt;
                break;
            }
        }
        else
        {
            if (testPrms->testConfig.testCaseId == testCaseId)
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
 *  st_captCheckIfTestToBeSkipped
 */
static Bool st_captCheckIfTestToBeSkipped(st_CaptUtObj                *utObj,
                                          const st_CaptApp_TestParams *testPrms,
                                          UInt32                       testType)
{
    Bool   skipTest = FALSE;
    st_CaptApp_TestInstParams testInstPrms;
    UInt32 instId, strmId, numStreams;

    /* Check whether test case is disabled */
    if (FALSE == testPrms->testConfig.testEnable)
    {
        GT_assert(utObj->traceMask,
                  (NULL != testPrms->testConfig.testDescStr));
        GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |TEST DISABLED|:: %d ::\r\n",
                  testPrms->testConfig.testCaseId);
        GT_1trace(utObj->traceMask, GT_INFO,
                  " |TEST PARAM|:: %s ::\r\n", testPrms->testConfig.testDescStr);
        if (NULL != testPrms->testConfig.disableReason)
        {
            GT_1trace(utObj->traceMask, GT_INFO,
                      " |TEST DISABLE REASON|:: %s ::\r\n",
                      testPrms->testConfig.disableReason);
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
        (ST_CAPT_TCT_HALT == testPrms->testConfig.testCaseType))
    {
        skipTest = TRUE;        /* Skip test */
    }

    for (instId = 0; instId < testPrms->testConfig.numHandles; instId++)
    {
        testInstPrms =
            (st_CaptApp_TestInstParams) (testPrms->testInstPrms[instId]);

        /* Check if this is Discrete Sync test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipDiscSyncTests))
        {
            if ((testInstPrms.createParams.videoIfMode >=
                 FVID2_VIFM_SCH_DS_HSYNC_VBLK) &&
                (testInstPrms.createParams.videoIfMode <=
                 FVID2_VIFM_SCH_DS_AVID_VSYNC))
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is Embedded Sync test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipEmbSyncTests))
        {
            if ((testInstPrms.createParams.videoIfMode <=
                 FVID2_VIFM_MCH_PIXEL_MUX_ES) ||
                (testInstPrms.createParams.videoIfMode ==
                 FVID2_VIFM_MCH_LINE_MUX_SPLIT_LINE_ES))
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is Slice/Sub-Frame mode Sync test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipSliceModeTests))
        {
            /* Check for every stream if subFrame mode is enabled. */
            numStreams = testInstPrms.createParams.numStream;
            for (strmId = 0; strmId < numStreams; strmId++)
            {
                if (TRUE == testInstPrms.outStrmParams[strmId].subFrameEnable)
                {
                    skipTest = TRUE;            /* Skip test */
                }
                if (skipTest == TRUE)
                {
                    break;
                }
            }
        }

        /* Check if this is Tvp5158 Sync test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipTvp5158Tests))
        {
            if (testInstPrms.decDrvId == FVID2_VID_DEC_TVP5158_DRV)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is ADV7611 Sync test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipADV7611Tests))
        {
            if (testInstPrms.decDrvId == FVID2_VID_DEC_ADV7611_DRV)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is SII9127 Sync test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipSII9127Tests))
        {
            if (testInstPrms.decDrvId == FVID2_VID_DEC_SII9127_DRV)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is Aptina Sensor test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipAptinaSensorTests))
        {
            if (testInstPrms.decDrvId == FVID2_VID_SENSOR_APT_AR0132_DRV)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is Aptina Sensor test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipAptinaSensorTests))
        {
            if (testInstPrms.decDrvId == FVID2_VID_SENSOR_APT_AR0132_DRV)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is OV Sensor test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipOVSensorTests))
        {
            if ((testInstPrms.decDrvId == FVID2_VID_SENSOR_OV10630_DRV) ||
                (testInstPrms.decDrvId == FVID2_VID_SENSOR_LI_OV1063X_DRV) ||
                (testInstPrms.decDrvId == FVID2_VID_SENSOR_MULDES_OV1063X_DRV))
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is Interlaced test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipInterlacedTests))
        {
            if (testInstPrms.standard == FVID2_STD_1080I_60)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }

        /* Check if this is Progressive test cases */
        if ((FALSE == skipTest) &&
            (TRUE == utObj->sysCtrl.skipProgressiveTests))
        {
            if (testInstPrms.standard == FVID2_STD_1080P_60)
            {
                skipTest = TRUE;            /* Skip test */
            }
        }
        if (skipTest == TRUE)
        {
            break;
        }
    }

    return (skipTest);
}

/**
 *  st_captDisplayTestInfo
 */
static Int32 st_captDisplayTestInfo(st_CaptUtObj *utObj)
{
    UInt32      sCnt, testCnt;
    char                   *runStatus;
    st_CaptApp_TestParams  *testPrms;
    static char            *enableDisableName[] = {"Disabled", "Enabled"};
    static char printBuf[ST_CAPT_PRINT_BUFSIZE];

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
    for (testCnt = 0u; testCnt < ST_CAPT_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStCaptTestCasePrms[testCnt];

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (FALSE == testPrms->testConfig.testEnable)
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
#if defined(__GNUC__) && !defined(__ti__)
                " %3d  %s_TC%5d  %-75.75s  %-8.8s  %-8.8s",
#else
                 " %3d  %s_TC%0.5d  %-75.75s  %-8.8s  %-8.8s",
#endif
                 (unsigned int) sCnt,
                 (char *) UT_NAME,
                 (unsigned int) testPrms->testConfig.testCaseId,
                 testPrms->testConfig.testDescStr,
                 runStatus,
                 (char *) enableDisableName[testPrms->testConfig.testEnable]);
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    return (BSP_SOK);
}

/**
 *  st_captGenerateTestReports
 */
static Int32 st_captGenerateTestReports(st_CaptUtObj *utObj)
{
    UInt32                  sCnt, testCnt;
    char                   *runStatus, *category, *adequacy;
    st_CaptApp_TestParams  *testPrms;
    static char             printBuf[ST_CAPT_PRINT_BUFSIZE];
    Int32                   anyTestFail = FALSE;

    sCnt = 1;
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "S.No;ID;Requirement Mapping;Description;IR;Category;"
        "Test Adequacy;Test Result;\r\n");
    for (testCnt = 0u; testCnt < ST_CAPT_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStCaptTestCasePrms[testCnt];

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (FALSE == testPrms->testConfig.testEnable)
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
                anyTestFail = TRUE;
                runStatus = "FAIL";
            }
        }

        if (testPrms->testConfig.testType & ST_TT_FULL)
        {
            category = "Full";
        }
        else if (testPrms->testConfig.testType & ST_TT_REGRESSION)
        {
            category = "Regression";
        }
        else
        {
            category = "Sanity";
        }

        if (testPrms->testConfig.testType & ST_TT_STRESS)
        {
            adequacy = "Stress";
        }
        else if (testPrms->testConfig.testType & ST_TT_NEGATIVE)
        {
            adequacy = "Negative";
        }
        else if (testPrms->testConfig.testType & ST_TT_PERFORMANCE)
        {
            adequacy = "Performance";
        }
        else if (testPrms->testConfig.testType & ST_TT_MISC)
        {
            adequacy = "Misc";
        }
        else
        {
            adequacy = "Functional";
        }

        snprintf(printBuf, sizeof (printBuf),
#if defined(__GNUC__) && !defined(__ti__)
                 "%d;%s_TC%5d;%s;%s;;%s;%s;%s",
#else
                 "%d;%s_TC%0.5d;%s;%s;;%s;%s;%s",
#endif
                 (int) sCnt,
                 (char *) UT_NAME,
                 (unsigned int) testPrms->testConfig.testCaseId,
                 testPrms->testConfig.swReqtId,
                 testPrms->testConfig.testDescStr,
                 category,
                 adequacy,
                 runStatus);
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }

    if (TRUE == anyTestFail)
    {
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_FAIL);
    }
    else
    {
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_PASS);
    }

    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    return (BSP_SOK);
}

/**
 *  stCapt_scaledOutRes
 *  Returns the scaled output resolution if Scalar is enabled.
 */
void stCapt_scaledOutRes(st_CaptApp_TestParams *testPrms,
                         st_CaptApp_Resoultion *resolution,
                         UInt32                 instanceCnt)
{
    UInt32 index;

    resolution->width =
        testPrms->testInstPrms[instanceCnt].vipParams.inWidth;
    resolution->height =
        testPrms->testInstPrms[instanceCnt].vipParams.inHeight;

    for (index = 0;
         index < testPrms->testInstPrms[instanceCnt].createParams.numStream;
         index++)
    {
        if (TRUE == \
            testPrms->testInstPrms[instanceCnt].outStrmParams[index].scEnable)
        {
            resolution->width =
                testPrms->testInstPrms[instanceCnt].outStrmParams[index].
                outWidth;
            resolution->height =
                testPrms->testInstPrms[instanceCnt].outStrmParams[index].
                outHeight;
            break;
        }
    }
}

/**
 *  stCapt_advScCfgInit
 *  Initialize the Advanced Scalar Configuration Parameters.
 */
void stCapt_advScCfgInit(Vps_ScAdvConfig *scAdvCfg)
{
    scAdvCfg->inFrameMode   = FVID2_SF_PROGRESSIVE;
    scAdvCfg->outFrameMode  = FVID2_SF_PROGRESSIVE;
    scAdvCfg->fidPol        = FVID2_FIDPOL_NORMAL;
    scAdvCfg->selfGenFid    = VPS_SC_SELF_GEN_FID_DISABLE;
    scAdvCfg->biLinIntpType = VPS_SC_BINTP_ORIGINAL;
    scAdvCfg->hsDcmType     = VPS_SC_HST_DCM_AUTO;
    scAdvCfg->hPolyBypass   = FALSE;
    scAdvCfg->vsType        = VPS_SC_VST_AUTO;
    scAdvCfg->phInfoMode    = VPS_SC_SET_PHASE_INFO_DEFAULT;
    scAdvCfg->polyphasePhInfo.rowAccInc     = 0;
    scAdvCfg->polyphasePhInfo.rowAccOffset  = 0;
    scAdvCfg->polyphasePhInfo.rowAccOffsetB = 0;
    scAdvCfg->ravPhInfo.ravScFactor         = 0;
    scAdvCfg->ravPhInfo.ravRowAccInit       = 0;
    scAdvCfg->ravPhInfo.ravRowAccInitB      = 0;
    scAdvCfg->arg = NULL;
}

/**
 *  st_captInitCaptAppObj
 */
static Int32 st_captInitCaptAppObj(const st_CaptUtObj          *utObj,
                                   const st_CaptApp_TestParams *testPrms,
                                   st_CaptApp_Obj              *appObj,
                                   UInt32                       taskCnt)
{
    Int32  retVal = BSP_SOK;
    UInt32 streamId, chId, instCnt, plId;
    Vps_CaptCreateParams      *prms;
    Vps_CaptVipParams         *vipPrms;
    Vps_CaptVipScParams       *scPrms;
    Vps_CaptVipOutInfo        *outInfo;
    st_CaptApp_InstObj        *instObj;
    st_CaptApp_CreateParams    utCreatePrms;
    st_CaptApp_VipParams       utVipPrms;
    st_CaptApp_OutStreamParams utOutStrmPrms;
    st_CaptApp_TestConfig      utTestCfgPrms;

    // TBD : use memcpy

    /* Assign platform type, board and CPU revisions */
    appObj->platformId = utObj->platformId;
    appObj->cpuRev     = utObj->cpuRev;
    appObj->boardId    = utObj->boardId;

    /* Copy user params */
    appObj->testPrms = (st_CaptApp_TestParams *) testPrms;
    appObj->taskId   = taskCnt;

    appObj->traceMask = (GT_INFO1 | GT_TraceState_Enable);
    if (FALSE == testPrms->testConfig.printEnable)
    {
        /* Restrict the number of prints when print is disabled */
        appObj->traceMask = (GT_INFO | GT_TraceState_Enable);
    }
    appObj->sysCtrl = &utObj->sysCtrl;

    appObj->maxWidth            = 1280u;
    appObj->maxHeight           = 720u;
    appObj->totalFldCount       = 0u;
    appObj->totalCpuLoad        = 0u;
    appObj->cpuLoadCount        = 0u;
    appObj->callBackCount       = 0u;
    appObj->subFrmCallBackCount = 0;

    utTestCfgPrms = testPrms->testConfig;

    utTestCfgPrms.strStpCntVal = DEF_START_STOP_CNT;

    for (instCnt = 0u;
         instCnt < utTestCfgPrms.numHandles;
         instCnt++)
    {
        instObj            = &appObj->instObj[instCnt];
        instObj->instId    = testPrms->testInstPrms[instCnt].instId;
        instObj->decDrvId  = testPrms->testInstPrms[instCnt].decDrvId;
        instObj->drvHandle = NULL;
        Fvid2CbParams_init(&instObj->cbPrms);
        instObj->cbPrms.cbFxn   = &st_captCbFxn;
        instObj->cbPrms.appData = instObj;
        instObj->appObj         = appObj;
        instObj->cbIdx          = 0u;
        instObj->sfCbIdx        = 0u;

        prms = &instObj->createPrms;
        VpsCaptCreateParams_init(&instObj->createPrms);
        utCreatePrms       = (testPrms->testInstPrms[instCnt].createParams);
        prms->videoIfMode  = utCreatePrms.videoIfMode;
        prms->videoIfWidth = utCreatePrms.videoIfWidth;
        prms->bufCaptMode  = utCreatePrms.bufCaptMode;
        prms->numCh        = utCreatePrms.numCh;
        prms->numStream    = utCreatePrms.numStream;

        vipPrms = &instObj->vipPrms;
        VpsCaptVipParams_init(&instObj->vipPrms);
        utVipPrms = (testPrms->testInstPrms[instCnt].vipParams);
        vipPrms->inFmt.chNum           = 0u;
        vipPrms->inFmt.width           = utVipPrms.inWidth;
        vipPrms->inFmt.height          = utVipPrms.inHeight;
        vipPrms->inFmt.pitch[0u]       = 0u;
        vipPrms->inFmt.pitch[1u]       = 0u;
        vipPrms->inFmt.pitch[2u]       = 0u;
        vipPrms->inFmt.fieldMerged[0u] = FALSE;
        vipPrms->inFmt.fieldMerged[1u] = FALSE;
        vipPrms->inFmt.fieldMerged[2u] = FALSE;
        vipPrms->inFmt.dataFormat      = utVipPrms.inDataFmt;
        vipPrms->inFmt.scanFormat      = utVipPrms.inScanFormat;
        vipPrms->inFmt.bpp      = utVipPrms.inBPP;
        vipPrms->inFmt.reserved = NULL;
        vipPrms->scPrms         = &instObj->scPrms;
        VpsCaptVipScParams_init(&instObj->scPrms);
        scPrms = &instObj->scPrms;
        scPrms->inCropCfg.cropStartX   = utVipPrms.cropStartX;
        scPrms->inCropCfg.cropStartY   = utVipPrms.cropStartY;
        scPrms->inCropCfg.cropWidth    = utVipPrms.cropWidth;
        scPrms->inCropCfg.cropHeight   = utVipPrms.cropHeight;
        scPrms->scCfg.bypass           = FALSE;
        scPrms->scCfg.nonLinear        = utVipPrms.nonLinear;
        scPrms->scCfg.stripSize        = utVipPrms.stripSize;
        scPrms->scCfg.enableEdgeDetect = TRUE;
        scPrms->scCfg.enablePeaking    = TRUE;

        scPrms->scCfg.advCfg    = NULL;
        scPrms->scCoeffCfg      = NULL;
        scPrms->enableCoeffLoad = FALSE;

        if ((TRUE == utVipPrms.enableScAdvCfg) &&
            (NULL != utVipPrms.advCfg))
        {
            st_CaptApp_AdvScConfig *utAdvCfg;
            utAdvCfg = (st_CaptApp_AdvScConfig *) utVipPrms.advCfg;
            scPrms->scCfg.advCfg = (&instObj->scAdvCfg);
            stCapt_advScCfgInit(scPrms->scCfg.advCfg);
            {
                st_CaptApp_Resoultion resolution;
                stCapt_scaledOutRes((st_CaptApp_TestParams *) testPrms,
                                    &resolution,
                                    instCnt);
                scPrms->scCfg.advCfg->tarWidth  = resolution.width;
                scPrms->scCfg.advCfg->tarHeight = resolution.height;
            }
            scPrms->scCfg.advCfg->srcWidth =
                utVipPrms.inWidth;
            scPrms->scCfg.advCfg->srcHeight =
                utVipPrms.inHeight;

            scPrms->scCfg.advCfg->cropStartX =
                utVipPrms.cropStartX;
            scPrms->scCfg.advCfg->cropStartY =
                utVipPrms.cropStartY;
            scPrms->scCfg.advCfg->cropWidth =
                utVipPrms.cropWidth;
            scPrms->scCfg.advCfg->cropHeight =
                utVipPrms.cropHeight;

            scPrms->scCfg.advCfg->inFrameMode     = utAdvCfg->inFrameMode;
            scPrms->scCfg.advCfg->outFrameMode    = utAdvCfg->outFrameMode;
            scPrms->scCfg.advCfg->fidPol          = utAdvCfg->fidPol;
            scPrms->scCfg.advCfg->selfGenFid      = utAdvCfg->selfGenFid;
            scPrms->scCfg.advCfg->biLinIntpType   = utAdvCfg->biLinIntpType;
            scPrms->scCfg.advCfg->hsDcmType       = utAdvCfg->hsDcmType;
            scPrms->scCfg.advCfg->hPolyBypass     = utAdvCfg->hPolyBypass;
            scPrms->scCfg.advCfg->vsType          = utAdvCfg->vsType;
            scPrms->scCfg.advCfg->defConfFactor   = 0u;
            scPrms->scCfg.advCfg->edgeDetectCfg   = NULL;
            scPrms->scCfg.advCfg->peakingCfg      = NULL;
            scPrms->scCfg.advCfg->phInfoMode      = utAdvCfg->phInfoMode;
            scPrms->scCfg.advCfg->polyphasePhInfo = utAdvCfg->polyphasePhInfo;
            scPrms->scCfg.advCfg->ravPhInfo       = utAdvCfg->ravPhInfo;
            scPrms->scCfg.advCfg->arg = NULL;
        }

        vipPrms->vipPortCfg = NULL;

        Bsp_platformSetVipClkInversion(instObj->instId, FALSE);
        if ((FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
            (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId))
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;

            /* Enable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = TRUE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1280U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 720U;
        }
        else if (FVID2_VID_SENSOR_APT_AR0132_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;

            /* Enable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = TRUE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1280U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 720U;
        }
        else if (FVID2_VID_DEC_SII9127_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;

            /* Disable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = FALSE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1920U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 1080U;
        }
        else if (FVID2_VID_DEC_ADV7611_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_LOW;

            /* Disable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = FALSE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1920U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 1080U;
        }
        else if (FVID2_VID_DEC_TVP5158_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.comCfg.pixClkEdgePol = FVID2_EDGE_POL_FALLING;
            Bsp_platformSetVipClkInversion(instObj->instId, TRUE);
        }
        else if (FVID2_VID_DEC_DS90UH926_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol     = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol      = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.hsyncPol      = FVID2_POL_LOW;
            instObj->vipPortCfg.comCfg.pixClkEdgePol = FVID2_EDGE_POL_FALLING;
            Bsp_platformSetVipClkInversion(instObj->instId, TRUE);
        }

        vipPrms->cscCfg = NULL;

        for (streamId = 0u;
             streamId < utCreatePrms.numStream;
             streamId++)
        {
            utOutStrmPrms =
                (testPrms->testInstPrms[instCnt].outStrmParams[streamId]);
            for (chId = 0u; chId < VPS_CAPT_CH_PER_PORT_MAX; chId++)
            {
                prms->chNumMap[streamId][chId] =
                    Vps_captMakeChNum(instObj->instId, streamId, chId);
            }
            outInfo = &vipPrms->outStreamInfo[streamId];
            outInfo->outFmt.chNum = 0u;
            outInfo->outFmt.width =
                utOutStrmPrms.outWidth;
            outInfo->outFmt.height =
                utOutStrmPrms.outHeight;
            outInfo->outFmt.fieldMerged[0u] = FALSE;
            outInfo->outFmt.fieldMerged[1u] = FALSE;
            outInfo->outFmt.fieldMerged[2u] = FALSE;
            outInfo->outFmt.dataFormat      =
                utOutStrmPrms.outDataFmt;
            outInfo->outFmt.scanFormat =
                utOutStrmPrms.outScanFormat;
            outInfo->outFmt.bpp =
                utOutStrmPrms.outBPP;
            outInfo->outFmt.pitch[0u] = 0u;
            outInfo->outFmt.pitch[1u] = 0u;
            outInfo->outFmt.pitch[2u] = 0u;
            if (Fvid2_isDataFmtSemiPlanar(outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth, VPS_BUFFER_ALIGNMENT);
                outInfo->outFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                    outInfo->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX];
            }
            else if (Fvid2_isDataFmtYuv422I(outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth * 2u, VPS_BUFFER_ALIGNMENT);
            }
            else
            {
                /* Align the pitch to BPP boundary as well since the pitch
                 * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
                 * bytes (1 pixel) */
                outInfo->outFmt.pitch[FVID2_RGB_ADDR_IDX] =
                    VpsUtils_align(
                        appObj->maxWidth * 3u, (VPS_BUFFER_ALIGNMENT * 3u));
            }

            outInfo->bufFmt  = utOutStrmPrms.bufFmt;
            outInfo->memType = utOutStrmPrms.memType;
            for (plId = 0u; plId < FVID2_MAX_PLANES; plId++)
            {
                outInfo->maxOutWidth[plId] =
                    utOutStrmPrms.maxOutWidth[plId];
                outInfo->maxOutHeight[plId] =
                    utOutStrmPrms.maxOutHeight[plId];
            }

            outInfo->scEnable = FALSE;
            if (ST_CAPT_SC_ENABLE_ALL ==
                utOutStrmPrms.scEnable)
            {
                outInfo->scEnable = TRUE;
            }
            if ((0u == streamId) &&
                (ST_CAPT_SC_ENABLE_0 ==
                 utOutStrmPrms.scEnable))
            {
                outInfo->scEnable = TRUE;
            }
            if ((1u == streamId) &&
                (ST_CAPT_SC_ENABLE_1 ==
                 utOutStrmPrms.scEnable))
            {
                outInfo->scEnable = TRUE;
            }

            outInfo->subFrmPrms.subFrameEnable =
                utOutStrmPrms.subFrameEnable;
            outInfo->subFrmPrms.numLinesPerSubFrame = 0u;
            outInfo->subFrmPrms.subFrameCb          = NULL;
            if (TRUE == utOutStrmPrms.subFrameEnable)
            {
                UInt32 numSlices, numLines;
                numSlices = utOutStrmPrms.numSlicesPerFrame;
                numLines  =
                    (UInt32) (utVipPrms.inHeight / numSlices);
                outInfo->subFrmPrms.numLinesPerSubFrame = numLines;
                outInfo->subFrmPrms.subFrameCb          = st_captSubFrmCbFxn;
            }
        }

        {
            UInt32 vipInst;
            vipInst =
                Vps_captGetVipId(testPrms->testInstPrms[instCnt].instId);
            instObj->maxOutWidth[0u] =
                utTestCfgPrms.maxSizeRegs[vipInst].maxSizeRegWidth[0u];
            instObj->maxOutHeight[0u] =
                utTestCfgPrms.maxSizeRegs[vipInst].maxSizeRegHeight[0u];
            instObj->maxOutWidth[1u] =
                utTestCfgPrms.maxSizeRegs[vipInst].maxSizeRegWidth[1u];
            instObj->maxOutHeight[1u] =
                utTestCfgPrms.maxSizeRegs[vipInst].maxSizeRegHeight[1u];
            instObj->maxOutWidth[2u] =
                utTestCfgPrms.maxSizeRegs[vipInst].maxSizeRegWidth[2u];
            instObj->maxOutHeight[2u] =
                utTestCfgPrms.maxSizeRegs[vipInst].maxSizeRegHeight[2u];
        }
    }
    return (retVal);
}

/* Main menu 0 string */
static char gStCaptMenuMain0[] =
{
    "\r\n "
    "\r\n ============="
    "\r\n CAPTURE UT Select"
    "\r\n ============="
    "\r\n "
};

/* Main menu string */
static char gStCaptMenuMain[] =
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

static char gStCaptMenuSettings0[] = {
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
};

static char gStCaptMenuSettings1[] = {
    "\r\n "
    "\r\n 1: Skip Discrete Sync Test Cases"
    "\r\n 2: Skip Embedded Sync Test Cases"
    "\r\n 3: Skip Slice/Sub-Frame mode Test Cases"
    "\r\n 4: Skip TVP5158 Test Cases"
    "\r\n 5: Skip ADV7611 Test Cases"
    "\r\n 6: Skip SII9127 Test Cases"
    "\r\n 7: Skip Sensor related Test Cases"
    "\r\n 8: Skip Aptina Sensor Test Cases"
    "\r\n 9: Skip OV Sensor Test Cases"
    "\r\n 10: Skip Multideserialiser Camera OV sensor Test Cases"
    "\r\n 11: Skip Interlaced capture Test Cases"
    "\r\n 12: Skip Progressive capture Test Cases"
    "\r\n 13: Skip 720p capture Test Cases"
    "\r\n 14: Skip 1080p capture Test Cases"
    "\r\n 15: waitForBufSaveRDisplay"
    "\r\n i: Execution Loop Count"
    "\r\n 16: Open/Close Count"
    "\r\n 17: Start/Stop Count"
    "\r\n e: Runtime Print Enable"
    "\r\n "
    "\r\n q: Quit "
    "\r\n"
};
/**
 *  st_captMenuSettings
 */
static Void st_captMenuSettings(st_CaptUtObj *utObj)
{
    char           option, inputStr[10];
    Bool           done = FALSE;
    Int32          value;
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    st_captMenuSettingsShow(utObj);

    while (!done)
    {
        GT_0trace(utObj->traceMask, GT_INFO, " Enter Choice: \r\n");
        BspUtils_uartGetStr(
            inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
        option = inputStr[0u];

        switch (option)
        {
            case '1':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip Discrete Sync Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipDiscSyncTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipDiscSyncTests = TRUE;
                }
                break;

            case '2':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip Embedded Sync Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipEmbSyncTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipEmbSyncTests = TRUE;
                }
                break;

            case '3':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip Slice/Sub-Frame mode Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipSliceModeTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipSliceModeTests = TRUE;
                }
                break;
            case '4':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip TVP5158 Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipTvp5158Tests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipTvp5158Tests = TRUE;
                }
                break;

            case '5':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip ADV7611 Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipADV7611Tests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipADV7611Tests = TRUE;
                }
                break;

            case '6':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip SII9127 Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipSII9127Tests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipSII9127Tests = TRUE;
                }
                break;
            case '7':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    "  Skip Sensor related Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipSensorTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipSensorTests = TRUE;
                }
                break;

            case '8':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip Aptina Sensor Test Cases[0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipAptinaSensorTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipAptinaSensorTests = TRUE;
                }
                break;

            case '9':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip OV Sensor Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipOVSensorTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipOVSensorTests = TRUE;
                }
                break;
            case 'a':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip Multideserialiser Camera OV sensor Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipMultiDesCamOVSensorTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipMultiDesCamOVSensorTests = TRUE;
                }
                break;

            case 'b':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip Interlaced capture Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipInterlacedTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipInterlacedTests = TRUE;
                }
                break;

            case 'c':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Progressive capture Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipProgressiveTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipProgressiveTests = TRUE;
                }
                break;
            case 'd':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip 720p capture Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skip720pTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skip720pTests = TRUE;
                }
                break;

            case 'e':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Skip 1080p capture Test Cases [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skip1080pTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skip1080pTests = TRUE;
                }
                break;

            case 'f':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " waitForBufSaveRDisplay [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->waitForBufSaveRDisplay = FALSE;
                if (1 == value)
                {
                    sysCtrl->waitForBufSaveRDisplay = TRUE;
                }
                break;
            case 'g':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Open/Close Count [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->openCloseCnt = FALSE;
                if (1 == value)
                {
                    sysCtrl->openCloseCnt = TRUE;
                }
                break;

            case 'h':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Start/Stop Count [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->startStopCnt = FALSE;
                if (1 == value)
                {
                    sysCtrl->startStopCnt = TRUE;
                }
                break;

            case 'i':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Loop count in frames: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
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

            case 'p':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Runtime Print Enable [0: Disable, 1: Enable]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
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
 *  st_captMenuMainShow
 */
static Void st_captMenuMainShow(st_CaptUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStCaptMenuMain0);
    st_captMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStCaptMenuMain);

    return;
}

/**
 *  st_captMenuSettingsShow
 */
static Void st_captMenuSettingsShow(st_CaptUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStCaptMenuSettings0);
    st_captMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStCaptMenuSettings1);

    return;
}

/**
 *  st_captMenuCurrentSettingsShow
 */
static Void st_captMenuCurrentSettingsShow(st_CaptUtObj *utObj)
{
    static char   *enableDisableName[] = {"OFF", "ON"};
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    GT_0trace(utObj->traceMask, GT_INFO, "\r\n Current System Settings:");
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ------------------------");
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Discrete Sync Test Cases     : %s",
              enableDisableName[sysCtrl->skipDiscSyncTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Embedded Sync Test Cases   : %s",
              enableDisableName[sysCtrl->skipEmbSyncTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Slice/Sub-Frame mode Test Cases     : %s",
              enableDisableName[sysCtrl->skipSliceModeTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip TVP5158 Test Cases   : %s",
              enableDisableName[sysCtrl->skipTvp5158Tests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip ADV7611 Test Cases     : %s",
              enableDisableName[sysCtrl->skipADV7611Tests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip SII9127 Test Cases   : %s",
              enableDisableName[sysCtrl->skipSII9127Tests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Sensor related Test Cases     : %s",
              enableDisableName[sysCtrl->skipSensorTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Aptina Sensor Test Cases   : %s",
              enableDisableName[sysCtrl->skipAptinaSensorTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip OV Sensor Test Cases     : %s",
              enableDisableName[sysCtrl->skipOVSensorTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Multideserialiser Camera OV sensor Test Cases   : %s",
              enableDisableName[sysCtrl->skipMultiDesCamOVSensorTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Interlaced capture Test Cases     : %s",
              enableDisableName[sysCtrl->skipInterlacedTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Progressive capture Test Cases   : %s",
              enableDisableName[sysCtrl->skipProgressiveTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip 720p capture Test Cases   : %s",
              enableDisableName[sysCtrl->skip720pTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip 1080p capture Test Cases   : %s",
              enableDisableName[sysCtrl->skip1080pTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n waitForBufSaveRDisplay   : %s",
              enableDisableName[sysCtrl->waitForBufSaveRDisplay]);

    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Loop Count             : %d", sysCtrl->loopCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Open/Close Count       : %d", sysCtrl->openCloseCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Start/Stop Count       : %d", sysCtrl->startStopCnt);

    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Runtime Print          : %s",
              enableDisableName[sysCtrl->rtPrintEnable]);
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ");

    return;
}

/**
 *  st_captSetDefaultCfg
 */
static Void st_captSetDefaultCfg(st_CaptUtObj *utObj)
{
    UInt32 testCnt;
    st_CaptApp_TestParams *testPrms;

    utObj->traceMask  = (GT_INFO1 | GT_TraceState_Enable);
    utObj->platformId = BSP_PLATFORM_ID_UNKNOWN;
    utObj->cpuRev     = BSP_PLATFORM_CPU_REV_1_0;
    utObj->boardId    = BSP_BOARD_UNKNOWN;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        st_captDetectBoard(utObj);
    }

    utObj->sysCtrl.skipDiscSyncTests            = FALSE;
    utObj->sysCtrl.skipEmbSyncTests             = FALSE;
    utObj->sysCtrl.skipSliceModeTests           = FALSE;
    utObj->sysCtrl.skipTvp5158Tests             = FALSE;
    utObj->sysCtrl.skipADV7611Tests             = FALSE;
    utObj->sysCtrl.skipSII9127Tests             = FALSE;
    utObj->sysCtrl.skipSensorTests              = FALSE;
    utObj->sysCtrl.skipAptinaSensorTests        = FALSE;
    utObj->sysCtrl.skipOVSensorTests            = FALSE;
    utObj->sysCtrl.skipMultiDesCamOVSensorTests = FALSE;
    utObj->sysCtrl.skipInterlacedTests          = FALSE;
    utObj->sysCtrl.skipProgressiveTests         = FALSE;
    utObj->sysCtrl.skip720pTests          = FALSE;
    utObj->sysCtrl.skip1080pTests         = FALSE;
    utObj->sysCtrl.waitForBufSaveRDisplay = FALSE;

    utObj->sysCtrl.loopCnt = DEF_LOOP_CNT;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        utObj->sysCtrl.loopCnt = DEF_LOOP_CNT_EVM;
    }
    utObj->sysCtrl.openCloseCnt  = DEF_OPEN_CLOSE_CNT;
    utObj->sysCtrl.startStopCnt  = DEF_START_STOP_CNT;
    utObj->sysCtrl.rtPrintEnable = FALSE;

    /* Mark all test cases as not run and set result to PASS */
    for (testCnt = 0u; testCnt < ST_CAPT_NUM_TESTCASES; testCnt++)
    {
        testPrms             = &gStCaptTestCasePrms[testCnt];
        testPrms->isRun      = FALSE;
        testPrms->testResult = BSP_SOK;
    }

    return;
}

/**
 *  st_captDetectBoard
 */
static Int32 st_captDetectBoard(st_CaptUtObj *utObj)
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

