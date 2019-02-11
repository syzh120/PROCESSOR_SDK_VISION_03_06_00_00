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
 *  \file st_vpeParser.c
 *
 *  \brief User interface for VPE driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on VPE driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_vpe.h>
#include <testInput/st_vpeConfig.h>
#include <testInput/st_vpeTestCases.h>

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

static Int32 st_vpeRunTestCase(st_VpeUtObj          *utObj,
                               st_VpeTestCaseParams *testPrms);
static Int32 st_vpeCreateTestTasks(st_VpeUtObj                *utObj,
                                   const st_VpeTestCaseParams *testPrms);
static void st_vpeTestTask(UArg arg0, UArg arg1);

static Int32 st_vpeGetTestCaseIdx(UInt32 testCaseId,
                                  Bool   isSearchForward);
static const st_VpeHandleCfg *st_vpeGetVpeHandleCfg(
    st_VpeHandleCfgId handleCfgId);
static const st_VpeChCfg *st_vpeGetVpeChCfg(st_VpeChCfgId chCfgId);
static Bool st_vpeCheckIfTestToBeSkipped(st_VpeUtObj                *utObj,
                                         const st_VpeTestCaseParams *testPrms,
                                         UInt32                      testType);
static Int32 st_vpeRunLoadFreeBufTestCases(st_VpeUtObj *utObj,
                                           UInt32       testCaseType);
static Int32 st_vpeDisplayTestInfo(st_VpeUtObj *utObj);
static Int32 st_vpeGenerateTestReports(st_VpeUtObj *utObj);

static Int32 st_vpeInitVpeAppObj(const st_VpeUtObj          *utObj,
                                 const st_VpeTestCaseParams *testPrms,
                                 st_VpeHandleObj            *hObj,
                                 UInt32                      taskCnt);

static Void st_vpeMenuSettings(st_VpeUtObj *utObj);
static Void st_vpeMenuMainShow(st_VpeUtObj *utObj);
static Void st_vpeMenuSettingsShow(st_VpeUtObj *utObj);
static Void st_vpeMenuCurrentSettingsShow(st_VpeUtObj *utObj);
static Void st_vpeSetDefaultCfg(st_VpeUtObj *utObj);
static Int32 st_vpeDetectBoard(st_VpeUtObj *utObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* VPE Test application stack. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gStVpeTestTskStack, 32)
#pragma DATA_SECTION(gStVpeTestTskStack, ".bss:taskStackSection")
#endif
static UInt8            gStVpeTestTskStack[ST_VPE_MAX_HANDLE][ST_TSK_STACK_SIZE
];

/* VPE application object per driver handle. */
static st_VpeHandleObj  gStVpeObjs[ST_VPE_MAX_HANDLE];

/* VPE task complete semaphore */
static Semaphore_Handle gStVpeTaskCompleteSem;

/* VPE UT object. */
st_VpeUtObj gVpeUtObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_vpeParser
 */
Int32 st_vpeParser(void)
{
    char   option, inputStr[10];
    Bool   done;
    Int32  retVal = FVID2_SOK, tempRetVal;
    Int32  testCaseIdx, startIdx;
    UInt32 testCnt, testType, testCaseId;
    UInt32 startTime, endTime, startTime1, endTime1;
    UInt32 hrs, mins;
    BspUtils_MemHeapStatus startHeapStat;
    st_VpeUtObj           *utObj;
    st_VpeTestCaseParams  *testPrms;
    Uint32 uartTimeout = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

    utObj = &gVpeUtObj;
    st_vpeSetDefaultCfg(utObj);
    st_resetTestResult();

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    /* Load the buffers by default */
    retVal = st_vpeRunLoadFreeBufTestCases(
        utObj,
        ST_VPE_TCT_LOAD_BUFFER);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(utObj->traceMask, GT_ERR,
                  "Failed to run load buffer test cases!!\r\n");
    }

    startTime        = BspOsal_getCurTimeInMsec();
    done             = FALSE;
    utObj->skipCount = utObj->disableCount = 0u;
    while (!done)
    {
        st_vpeMenuMainShow(utObj);

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
                st_vpeMenuSettings(utObj);
                break;

            case 'x':
                done = TRUE;
                break;

            case '1':
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Manual testing - Enter Test Case Id: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                testCaseId = (UInt32) atoi(inputStr);

                /* Find the test case to run */
                testCaseIdx = st_vpeGetTestCaseIdx(testCaseId, FALSE);
                if (testCaseIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Test case ID not found\r\n");
                }
                else
                {
                    testPrms = &gStVpeTestCasePrms[testCaseIdx];

                    retVal = st_vpeRunTestCase(utObj, testPrms);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  "Failed to run test case!!\r\n");
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
                        "Enter Start Test Case Id "
                        "(Enter 0 to start from first): \r\n");
                    BspUtils_uartGetStr(
                        inputStr,
                        sizeof(inputStr),
                        BSP_UTILS_UART_RX_WAIT_FOREVER);
                    testCaseId = (UInt32) atoi(inputStr);
                }
                startIdx   = st_vpeGetTestCaseIdx(testCaseId, TRUE);
                if (startIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                              "Test case ID not found\r\n");
                    continue;
                }

                /* Run all test cases one after the other depending on selected
                 * flag */
                startTime1       = BspOsal_getCurTimeInMsec();
                utObj->skipCount = utObj->disableCount = 0u;

                for (testCnt = startIdx; testCnt < ST_VPE_NUM_TESTCASES;
                     testCnt++)
                {
                    testPrms = &gStVpeTestCasePrms[testCnt];

                    /* Check whether to execute test or not */
                    if (st_vpeCheckIfTestToBeSkipped(utObj, testPrms, testType))
                    {
                        continue;       /* Skip test */
                    }

                    retVal = st_vpeRunTestCase(utObj, testPrms);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  "Failed to run test case!!\r\n");
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj,
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1 = BspOsal_getCurTimeInMsec();
                hrs      = (endTime1 - startTime1) / (1000u * 60u * 60u);
                mins     =
                    ((endTime1 - startTime1) / (1000u * 60u)) - (hrs * 60u);
                GT_2trace(utObj->traceMask, GT_INFO,
                          "|TOTAL TEST DURATION|: %d hrs %d mins\r\n", hrs, mins);
                break;

            case '5':
                testType = ST_TT_PERFORMANCE;
                startIdx = st_vpeGetTestCaseIdx(0u, TRUE);
                if (startIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                              "Test case ID not found\r\n");
                    continue;
                }

                /* Run all test cases one after the other depending on selected
                 * flag */
                startTime1       = BspOsal_getCurTimeInMsec();
                utObj->skipCount = utObj->disableCount = 0u;
                for (testCnt = startIdx;
                     testCnt < ST_VPE_NUM_TESTCASES;
                     testCnt++)
                {
                    testPrms = &gStVpeTestCasePrms[testCnt];

                    /* Check whether to execute test or not */
                    if (st_vpeCheckIfTestToBeSkipped(utObj, testPrms, testType))
                    {
                        continue;       /* Skip test */
                    }

                    retVal = st_vpeRunTestCase(utObj, testPrms);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(utObj->traceMask, GT_ERR,
                                  "Failed to run test case!!\r\n");
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj,
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1 = BspOsal_getCurTimeInMsec();
                hrs      = (endTime1 - startTime1) / (1000u * 60u * 60u);
                mins     =
                    ((endTime1 - startTime1) / (1000u * 60u)) - (hrs * 60u);
                GT_2trace(utObj->traceMask, GT_INFO,
                          "|TOTAL TEST DURATION|: %d hrs %d mins\r\n",
                          hrs, mins);
                break;

            case '6':
                /* Free the already allocated buffers */
                retVal = st_vpeRunLoadFreeBufTestCases(
                    utObj,
                    ST_VPE_TCT_FREE_BUFFER);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Failed to run free buffer test cases!!\r\n");
                }

                retVal = st_vpeRunLoadFreeBufTestCases(
                    utObj,
                    ST_VPE_TCT_LOAD_BUFFER);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Failed to run load buffer test cases!!\r\n");
                }
                break;

            case 'd':
                /* Display test info */
                st_vpeDisplayTestInfo(utObj);
                break;

            case 'g':
                /* Generate test report */
                st_vpeGenerateTestReports(utObj);
                break;

            default:
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Invalid option try again!!\r\n");
                break;
        }
    }

    /* Free the allocated buffers at the end */
    retVal = st_vpeRunLoadFreeBufTestCases(
        utObj,
        ST_VPE_TCT_FREE_BUFFER);
    if (FVID2_SOK != retVal)
    {
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_FAIL);
        GT_0trace(utObj->traceMask, GT_ERR,
                  "Failed to run free buffer test cases!!\r\n");
    }

    /* check for leak */
    st_vpeCheckHeapStat(&startHeapStat, utObj->traceMask);

    /* Print test results */
    st_printTestResult(utObj, utObj->skipCount, utObj->disableCount);
    st_vpeDisplayTestInfo(utObj);
    st_vpeGenerateTestReports(utObj);

    endTime = BspOsal_getCurTimeInMsec();
    hrs     = (endTime - startTime) / (1000u * 60u * 60u);
    mins    = ((endTime - startTime) / (1000u * 60u)) - (hrs * 60u);
    GT_2trace(utObj->traceMask, GT_INFO,
              "|TOTAL UT DURATION|: %d hrs %d mins\r\n", hrs, mins);

    return (retVal);
}

/**
 *  st_vpeRunTestCase
 */
static Int32 st_vpeRunTestCase(st_VpeUtObj          *utObj,
                               st_VpeTestCaseParams *testPrms)
{
    char  inputStr[10];
    Int32 retVal = FVID2_SOK;

    testPrms->isRun = TRUE;
    switch (testPrms->testCaseType)
    {
        case ST_VPE_TCT_LOAD_BUFFER:
            /* NULL pointer check */
            GT_assert(utObj->traceMask, (NULL != testPrms->loadBufCfg));

            retVal = st_vpeLoadBuf(utObj, testPrms->loadBufCfg);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          "Load buffer failed!!\r\n");
            }
            break;

        case ST_VPE_TCT_FREE_BUFFER:
            /* NULL pointer check */
            GT_assert(utObj->traceMask, (NULL != testPrms->loadBufCfg));

            retVal = st_vpeFreeBuf(utObj, testPrms->loadBufCfg);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, "Free buffer failed!!\r\n");
            }
            break;

        case ST_VPE_TCT_MAIN:
            /* Create all test tasks */
            retVal = st_vpeCreateTestTasks(utObj, testPrms);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, "VPE test failed!!\r\n");
            }

            /* Store the test result */
            testPrms->testResult = retVal;
            break;

        case ST_VPE_TCT_HALT:
            /* NULL pointer check */
            GT_assert(utObj->traceMask, (NULL != testPrms->testCaseName));
            GT_1trace(utObj->traceMask, GT_INFO,
                      "\r\nUser Input Halt: %s\r\n", testPrms->testCaseName);
            BspUtils_uartGetStr(
                inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
            break;

        default:
            GT_1trace(utObj->traceMask, GT_INFO,
                "Invalid test case type: %d!!\r\n", testPrms->testCaseType);
            retVal = FVID2_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  st_vpeCreateTestTasks
 */
static Int32 st_vpeCreateTestTasks(st_VpeUtObj                *utObj,
                                   const st_VpeTestCaseParams *testPrms)
{
    char                   tempString[200u];
    Int32                  retVal = FVID2_SOK, testResult = FVID2_SOK;
    UInt32                 taskCnt, createdTsk, scCnt;
    UInt32                 startTime, endTime, hrs, mins, secs, msecs;
    BspUtils_MemHeapStatus startHeapStat;
    st_VpeHandleObj       *hObj;
    Task_Params            tskPrms[ST_VPE_MAX_HANDLE];
    Task_Handle            tskHandle[ST_VPE_MAX_HANDLE];
    Semaphore_Params       semPrms;
    UInt32                 taskCntVpe = 0;

    /* NULL pointer check */
    GT_assert(utObj->traceMask, (NULL != testPrms));
    GT_assert(utObj->traceMask, (testPrms->numHandles <= ST_VPE_MAX_HANDLE));
    GT_assert(utObj->traceMask, (NULL != testPrms->testCaseName));

    startTime = BspOsal_getCurTimeInMsec();
    GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
    GT_1trace(utObj->traceMask, GT_INFO,
              "|TEST START|:: %d ::\r\n", testPrms->testCaseId);
    GT_2trace(utObj->traceMask, GT_INFO,
              "|TEST PARAM|:: %s (Start Time= %dms) ::\r\n",
              testPrms->testCaseName, startTime);
    if (NULL != testPrms->reqId)
    {
        GT_1trace(utObj->traceMask, GT_INFO,
                  "|SR|:: %s ::\r\n", testPrms->reqId);
    }
    startTime = BspOsal_getCurTimeInMsec();   /* Reset time to exclude print */

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    Semaphore_Params_init(&semPrms);
    gStVpeTaskCompleteSem = Semaphore_create(0u, &semPrms, NULL);
    if (NULL == gStVpeTaskCompleteSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
    }

    memset(&gStVpeObjs, 0u, sizeof (gStVpeObjs));
    memset(&tskHandle, 0u, sizeof (tskHandle));
    if (FVID2_SOK == retVal)
    {
        createdTsk = 0u;
        for (taskCnt = 0u; taskCnt < testPrms->numHandles; taskCnt++)
        {
            hObj   = &gStVpeObjs[taskCntVpe];
            retVal = st_vpeInitVpeAppObj(utObj, testPrms, hObj, taskCnt);
            if (FVID2_SOK != retVal)
            {
                break;
            }

            for (scCnt = 0u; scCnt < VPS_M2M_SCALER_ID_MAX; scCnt++)
            {
                retVal = BspUtils_appSetVpeLazyLoad(
                    hObj->drvInst,
                    scCnt,
                    testPrms->lazyLoadingEnable);
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
            if (FVID2_SOK != retVal)
            {
                break;
            }

            /* Create individual tasks */
            Task_Params_init(&tskPrms[taskCnt]);
            tskPrms[taskCnt].stack     = &gStVpeTestTskStack[taskCntVpe][0u];
            tskPrms[taskCnt].stackSize = ST_TSK_STACK_SIZE;
            tskPrms[taskCnt].arg0      = (UArg) hObj;
            tskHandle[taskCnt]         = Task_create(
                (Task_FuncPtr) st_vpeTestTask,
                &tskPrms[taskCnt],
                NULL);
            if (NULL == tskHandle[taskCnt])
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "%s: Task create failed\r\n", __FUNCTION__);
                retVal = FVID2_EALLOC;
                break;
            }

            createdTsk++;
            taskCntVpe++;
            sprintf(tempString, "ST_VPE Task %d", (unsigned int) taskCnt);
            BspUtils_prfLoadRegister(tskHandle[taskCnt], tempString);
        }
    }

    if (FVID2_SOK == retVal)
    {
        for (taskCnt = 0u; taskCnt < createdTsk; taskCnt++)
        {
            /* Wait for display tasks to complete */
            Semaphore_pend(gStVpeTaskCompleteSem, BIOS_WAIT_FOREVER);
        }
    }

    for (taskCnt = 0u; taskCnt < taskCntVpe; taskCnt++)
    {
        testResult += gStVpeObjs[taskCnt].testResult;
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

    if (NULL != gStVpeTaskCompleteSem)
    {
        Semaphore_delete(&gStVpeTaskCompleteSem);
    }

    /* check for leak */
    st_vpeCheckHeapStat(&startHeapStat, utObj->traceMask);

    endTime = BspOsal_getCurTimeInMsec();
    hrs     = (endTime - startTime) / (1000u * 60u * 60u);
    mins    = ((endTime - startTime) / (1000u * 60u)) - (hrs * 60u);
    secs    = ((endTime - startTime) / 1000u) - (((hrs * 60u) + mins) * 60u);
    msecs   = (endTime - startTime) -
              (((hrs * 60u * 60u) + (mins * 60u) + secs) * 1000u);
    GT_4trace(utObj->traceMask, GT_INFO,
              "|TEST DURATION|:: %d:%0.2d:%0.2d:%0.3d ::\r\n",
              hrs, mins, secs, msecs);

    sprintf(tempString, "%s (End Time= %dms)",
            testPrms->testCaseName, (unsigned int) endTime);
    st_logTestResult(utObj, testResult, testPrms->testCaseId, tempString);

    return (testResult);
}

/**
 *  st_vpeTestTask
 */
static void st_vpeTestTask(UArg arg0, UArg arg1)
{
    Int32 retVal;
    st_VpeHandleObj *hObj;

    /* Run the test */
    hObj = (st_VpeHandleObj *) arg0;

    /* Run the display test */
    retVal = st_vpeMainTestCase(hObj);

    hObj->testResult = retVal;

    /* Test complete. Signal it */
    Semaphore_post(gStVpeTaskCompleteSem);

    return;
}

/**
 *  st_vpeGetTestCaseIdx
 */
static Int32 st_vpeGetTestCaseIdx(UInt32 testCaseId,
                                  Bool   isSearchForward)
{
    Int32  testCaseIdx = -1;
    UInt32 testCnt;
    const st_VpeTestCaseParams *testPrms;

    testPrms = &gStVpeTestCasePrms[0u];
    for (testCnt = 0u; testCnt < ST_VPE_NUM_TESTCASES; testCnt++)
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
 *  st_vpeGetVpeHandleCfg
 */
static const st_VpeHandleCfg *st_vpeGetVpeHandleCfg(
    st_VpeHandleCfgId handleCfgId)
{
    UInt32 index;
    const st_VpeHandleCfg *handleCfg = NULL;

    /* Search in handle table */
    for (index = 0u; index < VPE_MAX_HANDLE_CFG; index++)
    {
        if (gStVpeHandleCfg[index].handleCfgId == handleCfgId)
        {
            handleCfg = &gStVpeHandleCfg[index];
            break;
        }
    }

    return (handleCfg);
}

static const st_VpeChCfg *st_vpeGetVpeChCfg(st_VpeChCfgId chCfgId)
{
    UInt32 index;
    const st_VpeChCfg *chCfg = NULL;

    /* Search in channel table */
    for (index = 0u; index < VPE_MAX_CH_CFG; index++)
    {
        if (gStVpeChCfg[index].chCfgId == chCfgId)
        {
            chCfg = &gStVpeChCfg[index];
            break;
        }
    }

    return (chCfg);
}

/**
 *  st_vpeCheckIfTestToBeSkipped
 */
static Bool st_vpeCheckIfTestToBeSkipped(st_VpeUtObj                *utObj,
                                         const st_VpeTestCaseParams *testPrms,
                                         UInt32                      testType)
{
    Bool   skipTest = FALSE;
    UInt32 chCnt, hCnt, chIdx;
    const st_VpeChCfg *chCfg;

    /* Check whether test case is disabled */
    if (FALSE == testPrms->enableTest)
    {
        GT_assert(utObj->traceMask,
                  (NULL != testPrms->testCaseName));
        GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
        GT_1trace(utObj->traceMask, GT_INFO,
                  "|TEST DISABLED|:: %d ::\r\n", testPrms->testCaseId);
        GT_1trace(utObj->traceMask, GT_INFO,
                  "|TEST PARAM|:: %s ::\r\n", testPrms->testCaseName);
        if (NULL != testPrms->disableReason)
        {
            GT_1trace(utObj->traceMask, GT_INFO,
                      "|TEST DISABLE REASON|:: %s ::\r\n",
                      testPrms->disableReason);
        }
        else
        {
            GT_0trace(utObj->traceMask, GT_INFO,
                      "|TEST DISABLE REASON|:: Not Provided!! ::\r\n");
        }

        utObj->disableCount++;
        skipTest = TRUE;        /* Skip test */
    }

    /* Check if this is halt test case used to get user input */
    if ((FALSE == skipTest) &&
        (TRUE == utObj->sysCtrl.skipHaltTests) &&
        (ST_VPE_TCT_HALT == testPrms->testCaseType))
    {
        skipTest = TRUE;        /* Skip test */
    }

    /* Skip load/free test cases for automated testing as we have already
     * loaded the buffers. */
    if ((FALSE == skipTest) &&
        ((ST_VPE_TCT_LOAD_BUFFER == testPrms->testCaseType) ||
         (ST_VPE_TCT_FREE_BUFFER == testPrms->testCaseType)))
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

    if (FALSE == skipTest)
    {
        /* Skip non YUV422I output for TI814x build as this is not supported */
        if (TRUE == Bsp_platformIsTI814xFamilyBuild())
        {
            chIdx = 0u;
            for (hCnt = 0u; hCnt < testPrms->numHandles; hCnt++)
            {
                for (chCnt = 0u; chCnt < testPrms->numCh[hCnt]; chCnt++)
                {
                    GT_assert(utObj->traceMask, (chIdx < ST_VPE_MAX_CH));
                    chCfg = st_vpeGetVpeChCfg(testPrms->chCfgId[chIdx]);
                    GT_assert(utObj->traceMask, (NULL != chCfg));

                    if (chCfg->outDataFmt != FVID2_DF_YUV422I_YUYV)
                    {
                        utObj->skipCount++;
                        skipTest = TRUE;    /* Skip test */
                        break;
                    }
                    chIdx++;
                }

                if (TRUE == skipTest)
                {
                    break;
                }
            }
        }
    }

    return (skipTest);
}

/**
 *  st_vpeRunLoadFreeBufTestCases
 */
static Int32 st_vpeRunLoadFreeBufTestCases(st_VpeUtObj *utObj,
                                           UInt32       testCaseType)
{
    Int32  retVal = FVID2_SOK;
    UInt32 testCnt;
    st_VpeTestCaseParams *testPrms;

    /* Run all load/free buffer test cases one after the other */
    for (testCnt = 0u; testCnt < ST_VPE_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStVpeTestCasePrms[testCnt];

        /* Check whether to execute test or not */
        if (FALSE == testPrms->enableTest)
        {
            continue;       /* Skip test */
        }

        /* Ignore non-load/free test cases */
        if (testCaseType != testPrms->testCaseType)
        {
            continue;       /* Skip test */
        }

        retVal = st_vpeRunTestCase(utObj, testPrms);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR,
                "Failed to run test case!!\r\n");
        }
    }

    return (retVal);
}

/**
 *  st_vpeDisplayTestInfo
 */
static Int32 st_vpeDisplayTestInfo(st_VpeUtObj *utObj)
{
    UInt32      sCnt, testCnt;
    char                       *runStatus;
    st_VpeTestCaseParams       *testPrms;
    static char                *enableDisableName[] = {"Disabled", "Enabled"};
    static char printBuf[300];

    /* Display test info */
    sCnt = 1;
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "S.No        ID       Description                                     "
        "                             Status    Auto Run\r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "---------------------------------------------------------------------"
        "-----------------------------------------------\r\n");
    for (testCnt = 0u; testCnt < ST_VPE_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStVpeTestCasePrms[testCnt];

        /* Skip load/free test cases */
        if ((ST_VPE_TCT_LOAD_BUFFER == testPrms->testCaseType) ||
            (ST_VPE_TCT_FREE_BUFFER == testPrms->testCaseType))
        {
            continue;
        }

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (FALSE == testPrms->enableTest)
            {
                runStatus = "NRQ";
            }
        }
        else
        {
            if (FVID2_SOK == testPrms->testResult)
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
                 " %3d  %s_TC%4d  %-75.75s  %-8.8s  %-8.8s",
#else
                 " %3d  %s_TC%0.4d  %-75.75s  %-8.8s  %-8.8s",
#endif
                 (unsigned int) sCnt,
                 (char *) APP_NAME,
                 (unsigned int) testPrms->testCaseId,
                 testPrms->testCaseName,
                 runStatus,
                 enableDisableName[testPrms->enableTest]);
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    return (FVID2_SOK);
}

/**
 *  st_vpeGenerateTestReports
 */
static Int32 st_vpeGenerateTestReports(st_VpeUtObj *utObj)
{
    UInt32      sCnt, testCnt;
    char                       *runStatus, *category, *adequacy;
    st_VpeTestCaseParams       *testPrms;
    static char printBuf[300];
    Int32       anyTestFail = FALSE;

    sCnt = 1;
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "S.No;ID;Requirement Mapping;Description;IR;Category;"
        "Test Adequacy;Test Result;\r\n");
    for (testCnt = 0u; testCnt < ST_VPE_NUM_TESTCASES; testCnt++)
    {
        testPrms = &gStVpeTestCasePrms[testCnt];

        /* Skip load/free test cases */
        if ((ST_VPE_TCT_LOAD_BUFFER == testPrms->testCaseType) ||
            (ST_VPE_TCT_FREE_BUFFER == testPrms->testCaseType))
        {
            continue;
        }

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (FALSE == testPrms->enableTest)
            {
                runStatus = "NRQ";
            }
        }
        else
        {
            if (FVID2_SOK == testPrms->testResult)
            {
                runStatus = "PASS";
            }
            else
            {
                anyTestFail = TRUE;
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
#if defined(__GNUC__) && !defined(__ti__)
                 "%d;%s_TC%4d;%s;%s;;%s;%s;%s",
#else
                 "%d;%s_TC%0.4d;%s;%s;;%s;%s;%s",
#endif
                 (unsigned int) sCnt,
                 (char *) APP_NAME,
                 (unsigned int) testPrms->testCaseId,
                 testPrms->reqId,
                 testPrms->testCaseName,
                 category,
                 adequacy,
                 runStatus);
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    if (TRUE == anyTestFail)
    {
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_FAIL);
    }
    else
    {
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_PASS);
    }

    return (FVID2_SOK);
}

/**
 *  st_vpeInitVpeAppObj
 */
static Int32 st_vpeInitVpeAppObj(const st_VpeUtObj          *utObj,
                                 const st_VpeTestCaseParams *testPrms,
                                 st_VpeHandleObj            *hObj,
                                 UInt32                      taskCnt)
{
    Int32 retVal = FVID2_SOK;
    Int32 chIdx, tempCnt, chCnt;
    const st_VpeHandleCfg *handleCfg;
    const st_VpeChCfg     *chCfg;
    st_VpeChObj           *chObj;

    /* Assign platform type, board and CPU revisions */
    hObj->platformId = utObj->platformId;
    hObj->cpuRev     = utObj->cpuRev;
    hObj->boardId    = utObj->boardId;

    /* Copy user params */
    hObj->testPrms = testPrms;
    hObj->taskId   = taskCnt;
    hObj->drvInst  = testPrms->drvInst[taskCnt];
    hObj->numCh    = testPrms->numCh[taskCnt];

    /* Get and copy the handle configuration */
    handleCfg = st_vpeGetVpeHandleCfg(testPrms->handleCfgId[taskCnt]);
    GT_assert(utObj->traceMask, (NULL != handleCfg));
    memcpy(&hObj->handleCfg, handleCfg, sizeof (st_VpeHandleCfg));

    /* Get the start channel index */
    chIdx = 0u;
    for (tempCnt = 0u; tempCnt < taskCnt; tempCnt++)
    {
        chIdx += testPrms->numCh[tempCnt];
    }
    GT_assert(utObj->traceMask, (chIdx < ST_VPE_MAX_CH));
    GT_assert(utObj->traceMask,
              ((chIdx + testPrms->numCh[taskCnt]) <= ST_VPE_MAX_CH));
    hObj->startChIdx = chIdx;

    /* Get and copy the channel configuration */
    for (chCnt = 0u; chCnt < testPrms->numCh[taskCnt]; chCnt++)
    {
        chCfg = st_vpeGetVpeChCfg(testPrms->chCfgId[chIdx + chCnt]);
        GT_assert(utObj->traceMask, (NULL != chCfg));

        chObj = &hObj->chObj[chCnt];
        memcpy(&chObj->chCfg, chCfg, sizeof (st_VpeChCfg));
    }

    /* Set the default values */
    if (USE_DEF_QLEN == hObj->handleCfg.chInQueueLength)
    {
        hObj->handleCfg.chInQueueLength = utObj->sysCtrl.chInQueueLength;
    }
    if (USE_DEF_LP_CNT == hObj->handleCfg.loopCnt)
    {
        hObj->handleCfg.loopCnt = utObj->sysCtrl.loopCnt;
    }
    if (USE_DEF_SS_CNT == hObj->handleCfg.startStopCnt)
    {
        hObj->handleCfg.startStopCnt = utObj->sysCtrl.startStopCnt;
    }
    if (USE_DEF_OC_CNT == hObj->handleCfg.openCloseCnt)
    {
        hObj->handleCfg.openCloseCnt = utObj->sysCtrl.openCloseCnt;
    }
    if (USE_DEF_FSR == hObj->handleCfg.frameSwitchRate)
    {
        hObj->handleCfg.frameSwitchRate = utObj->sysCtrl.frameSwitchRate;
    }
    hObj->traceMask = (GT_INFO1 | GT_TraceState_Enable);
    if (FALSE == testPrms->printEnable)
    {
        /* Restrict the number of prints when print is disabled */
        hObj->traceMask = (GT_INFO | GT_TraceState_Enable);
    }
    hObj->sysCtrl = &utObj->sysCtrl;

    return (retVal);
}

/* Main menu 0 string */
static char gStVpeMenuMain0[] =
{
    "\r\n "
    "\r\n ============="
    "\r\n VPE UT Select"
    "\r\n ============="
    "\r\n "
};

/* Main menu string */
static char gStVpeMenuMain[] =
{
    "\r\n 1: Manual testing (select specific test case to run)"
    "\r\n 2: Sanity (BFT) testing"
    "\r\n 3: Regression testing"
    "\r\n 4: Full testing"
    "\r\n 5: Performance testing"
    "\r\n 6: Reload different set of buffers"
    "\r\n d: Display test cases"
    "\r\n g: Generate test report"
    "\r\n "
    "\r\n s: System Settings"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

static char gStVpeMenuSettings0[] = {
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
};

static char gStVpeMenuSettings1[] = {
    "\r\n "
    "\r\n 1: Skip Halt Test Case"
    "\r\n 2: Execution Loop Count"
    "\r\n 3: Start/Stop Count"
    "\r\n 4: Open/Close Count"
    "\r\n 5: Channel In Q Length"
    "\r\n s: Frame Switch Rate"
    "\r\n r: Runtime Print"
    "\r\n f: File I/O Enable"
    "\r\n p: File Path"
    "\r\n "
    "\r\n x: Exit "
    "\r\n"
};

/**
 *  st_vpeMenuSettings
 */
static Void st_vpeMenuSettings(st_VpeUtObj *utObj)
{
    char           option, inputStr[10];
    Bool           done = FALSE;
    Int32          value;
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    st_vpeMenuSettingsShow(utObj);

    while (!done)
    {
        GT_0trace(utObj->traceMask, GT_INFO, " Enter Choice: \r\n");
        BspUtils_uartGetStr(
            inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
        option = inputStr[0u];

        switch (option)
        {
            case '1':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip Halt Test Enable [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->skipHaltTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipHaltTests = TRUE;
                }
                break;

            case '2':
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
                        "This matches with default flag, "
                        "give another value\r\n");
                }
                break;

            case '3':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Start/stop count: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                if (value != USE_DEF_SS_CNT)
                {
                    sysCtrl->startStopCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, "
                        "give another value\r\n");
                }
                break;

            case '4':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Open/close count: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                if (value != USE_DEF_OC_CNT)
                {
                    sysCtrl->openCloseCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, "
                        "give another value\r\n");
                }
                break;

            case '5':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Channel Input Q Lenght: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                if (value != USE_DEF_OC_CNT)
                {
                    sysCtrl->chInQueueLength = USE_DEF_QLEN;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, "
                        "give another value\r\n");
                }
                break;

            case 's':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Frame switch rate in frames: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                if (value != USE_DEF_FSR)
                {
                    sysCtrl->frameSwitchRate = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, "
                        "give another value\r\n");
                }
                break;

            case 'r':
                GT_0trace(utObj->traceMask, GT_INFO,
                    " Runtime Print Enable [0: Disable, 1: Enable]:\r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->rtPrintEnable = FALSE;
                if (1 == value)
                {
                    sysCtrl->rtPrintEnable = TRUE;
                }
                break;

            case 'f':
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    " Output File I/O Enable [0: Disable, 1: Enable]: \r\n");
                BspUtils_uartGetStr(
                    inputStr, sizeof(inputStr), BSP_UTILS_UART_RX_WAIT_FOREVER);
                value = atoi(inputStr);

                sysCtrl->fileIoEnable = FALSE;
                if (1 == value)
                {
                    sysCtrl->fileIoEnable = TRUE;
                }
                break;

            case 'p':
                GT_1trace(utObj->traceMask, GT_INFO,
                          " Output File Path (Max %d char): \r\n",
                          ST_VPE_MAX_FILE_PATH_STRING);
                BspUtils_uartGetStr(
                    sysCtrl->filePath,
                    sizeof(sysCtrl->filePath),
                    BSP_UTILS_UART_RX_WAIT_FOREVER);
                break;

            case 'x':
                done = TRUE;
                break;
        }
        fflush(stdin);
    }

    return;
}

/**
 *  st_vpeMenuMainShow
 */
static Void st_vpeMenuMainShow(st_VpeUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStVpeMenuMain0);
    st_vpeMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStVpeMenuMain);

    return;
}

/**
 *  st_vpeMenuSettingsShow
 */
static Void st_vpeMenuSettingsShow(st_VpeUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStVpeMenuSettings0);
    st_vpeMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStVpeMenuSettings1);

    return;
}

/**
 *  st_vpeMenuCurrentSettingsShow
 */
static Void st_vpeMenuCurrentSettingsShow(st_VpeUtObj *utObj)
{
    static char   *enableDisableName[] = {"OFF", "ON"};
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    GT_0trace(utObj->traceMask, GT_INFO, "\r\n Current System Settings:");
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ------------------------");
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Skip Halt Test Cases   : %s",
              enableDisableName[sysCtrl->skipHaltTests]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Loop Count             : %d", sysCtrl->loopCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Start/Stop Count       : %d", sysCtrl->startStopCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Open/Close Count       : %d", sysCtrl->openCloseCnt);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Channel In Q Length    : %d", sysCtrl->chInQueueLength);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Frame Switch Rate      : %d", sysCtrl->frameSwitchRate);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Runtime Print          : %s",
              enableDisableName[sysCtrl->rtPrintEnable]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Output File I/O        : %s",
              enableDisableName[sysCtrl->fileIoEnable]);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n Output File Path       : %s", sysCtrl->filePath);
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ");

    return;
}

/**
 *  st_vpeSetDefaultCfg
 */
static Void st_vpeSetDefaultCfg(st_VpeUtObj *utObj)
{
    UInt32 testCnt;
    st_VpeTestCaseParams *testPrms;

    utObj->traceMask  = (GT_INFO1 | GT_TraceState_Enable);
    utObj->platformId = BSP_PLATFORM_ID_UNKNOWN;
    utObj->cpuRev     = BSP_PLATFORM_CPU_REV_1_0;
    utObj->boardId    = BSP_BOARD_UNKNOWN;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        st_vpeDetectBoard(utObj);
    }

    utObj->sysCtrl.skipHaltTests = TRUE;
    utObj->sysCtrl.loopCnt       = DEF_LOOP_CNT;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        utObj->sysCtrl.loopCnt = DEF_LOOP_CNT_EVM;
    }
    utObj->sysCtrl.startStopCnt    = DEF_START_STOP_CNT;
    utObj->sysCtrl.openCloseCnt    = DEF_OPEN_CLOSE_CNT;
    utObj->sysCtrl.chInQueueLength = DEF_QUEUE_LEN_PER_CH;
    utObj->sysCtrl.frameSwitchRate = DEF_FRAME_SWITCH_RATE;
    utObj->sysCtrl.rtPrintEnable   = FALSE;
    utObj->sysCtrl.fileIoEnable    = FALSE;
    strcpy(utObj->sysCtrl.filePath, "D:\\");

    /* Mark all test cases as not run and set result to PASS */
    for (testCnt = 0u; testCnt < ST_VPE_NUM_TESTCASES; testCnt++)
    {
        testPrms             = &gStVpeTestCasePrms[testCnt];
        testPrms->isRun      = FALSE;
        testPrms->testResult = FVID2_SOK;
    }

    return;
}

/**
 *  st_vpeDetectBoard
 */
static Int32 st_vpeDetectBoard(st_VpeUtObj *utObj)
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

    return (FVID2_SOK);
}

