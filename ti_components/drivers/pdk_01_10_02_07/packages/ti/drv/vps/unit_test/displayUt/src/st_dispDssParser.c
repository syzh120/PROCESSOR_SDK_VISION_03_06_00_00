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
 *  \file st_dssParser.c
 *
 *  \brief User interface for DSS driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on DSS driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <st_dispDss.h>
#include <displayUtTestInput_gblcfg.h>
#include <displayUtTestInput_instcfg.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define ST_TSK_STACK_SIZE               (10u * 1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
// static Int32 st_dispDssRunTestCase(st_DispDssUtObj *utObj);
static Int32 st_dispDssRunTestCase(st_DispDssUtObj   *utObj,
                                   st_DispDssTestCfg *testPrms);
static Int32 st_dispDssCreateTestTasks(st_DispDssUtObj *utObj);
static Int32 st_dispDssInitAppObj(const st_DispDssUtObj *utObj,
                                  st_DispDssAppObj      *appObj,
                                  UInt32                 taskCnt);
static Void st_dispDssMenuSettingsShow(st_DispDssUtObj *utObj);
static Void st_dispDssMenuCurrentSettingsShow(st_DispDssUtObj *utObj);
static Int32 st_dispDssDetectBoard(st_DispDssUtObj *utObj);
static Void st_dispDssMenuSettings(st_DispDssUtObj *utObj);
static Void st_dispDssMenuMainShow(st_DispDssUtObj *utObj);
static Void st_dispDssSetDefaultCfg(st_DispDssUtObj *utObj);
static Int32 st_dispDssGetTestCaseIdx(st_DispDssUtObj *utObj,
                                      UInt32           testCaseId,
                                      Bool             isSearchForward);
static Bool st_dispDssCheckIfTestToBeSkipped(st_DispDssUtObj         *utObj,
                                             const st_DispDssTestCfg *testPrms,
                                             UInt32                   testType);
static Int32 st_dispDssGenerateTestReports(st_DispDssUtObj *utObj);
static Int32 st_dispDssDisplayTestInfo(st_DispDssUtObj *utObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* DSS Test application stack. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gStDispDssTestTskStack, 32)
#pragma DATA_SECTION(gStDispDssTestTskStack, ".bss:taskStackSection")
#endif
static UInt8          gStDispDssTestTskStack[ST_DISP_DSS_TASK_MAX][
    ST_TSK_STACK_SIZE];

/* DSS task complete semaphore */
Queue_Handle          gVidPpl1msgQueue;
Queue_Handle          gVidPpl2msgQueue;
Queue_Handle          gVidPpl3msgQueue;
Queue_Handle          gGfxPpl1msgQueue;
Queue_Handle          gDctrlmsgQueue;

/* Dss UT object. */
st_DispDssUtObj       gStDispDssObj;

st_DispDssAppObj      gAppDispDssObj[ST_DISP_DSS_TASK_MAX];

st_DispDssTestCfg     gDispDssTestCfg;
st_DispDssTestInstCfg gDispDssTestInstCfg[VPS_DISP_INST_MAX];

UInt32 gTestVal = 0;

Semaphore_Handle      gStDispDssMasterTaskSem;
Semaphore_Handle      gStDispDssDctrlTaskSem;
Semaphore_Handle      gStDispDssVidPpl1TaskSem;
Semaphore_Handle      gStDispDssVidPpl2TaskSem;
Semaphore_Handle      gStDispDssVidPpl3TaskSem;
Semaphore_Handle      gStDispDssGfxPpl1TaskSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_dispDssParser
 */
Int32 st_dispDssParser(void)
{
    char   option;
    Int32  retVal = FVID2_SOK;
    BspUtils_MemHeapStatus startHeapStat;
    st_DispDssUtObj           *utObj;

    UInt32 mainMenuTimeout = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;
    char   userInput;
    Int32  tempRetVal;
    UInt32 bufCfgId;
    Bool   done;
    UInt32 testCnt, testType;
    Int32  testCaseId;
    Int32  testCaseIdx, startIdx;
    UInt32 startTime1, endTime1;
    st_DispDssTestCfg *testPrms;
    UInt32 hrs, mins;
    Int32  instID;
    Bsp_PlatformInitParams platInitPrms;
    Bsp_PlatformSocId      platformSocId;

    utObj = &gStDispDssObj;

    utObj->traceMask = (GT_INFO | GT_TraceState_Enable);

    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    utObj->yuyv422BufCnt = 0u;

    BspPlatformInitParams_init(&platInitPrms);
    retVal = Bsp_platformInit(&platInitPrms);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(utObj->traceMask, GT_ERR, "Platform Init failed!!\r\n");
    }

    GT_0trace(BspAppTrace, GT_INFO, "Do you want to load all buffers now y|n\r\n");
    tempRetVal = BspUtils_uartGetChar(
                    &userInput, BSP_UTILS_UART_RX_DEFAULT_TIMEOUT);
    if ((tempRetVal == FVID2_SOK) && ((userInput == 'y') || (userInput == 'Y')))
    {
        for (bufCfgId = 0;
            bufCfgId <
            (sizeof (gDispDssLoadBufCfg) / sizeof (st_DispDssLoadBufCfg));
            bufCfgId++)
        {
            retVal = st_dispDssLoadBuf(utObj, &gDispDssLoadBufCfg[bufCfgId]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                        "Load buffer failed!!\r\n");
            }
        }
    }

    done = FALSE;
    utObj->skipCount = utObj->disableCount = 0u;

    st_dispDssSetDefaultCfg(utObj);
    platformSocId = Bsp_platformGetSocId();

    while (!done)
    {
        st_dispDssMenuMainShow(utObj);

        retVal = BspUtils_uartGetChar(&option,mainMenuTimeout);
        if (retVal == BSP_ETIMEOUT)
        {
            option = '4';
        }

        testType = ST_TT_SANITY;
        switch (option)
        {
            case 's':
                st_dispDssMenuSettings(utObj);
                break;

            case 'x':
                done = TRUE;
                break;

            case '1':
                /* Test execution started. Change main menu timeout to
                   wait forever for next run. */
                mainMenuTimeout = BSP_UTILS_UART_RX_WAIT_FOREVER;
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Manual testing - Enter Test Case Id: \r\n");
                BspUtils_uartGetNum(&testCaseId,BSP_UTILS_UART_RX_WAIT_FOREVER);

                /* Find the test case to run */
                testCaseIdx = st_dispDssGetTestCaseIdx(
                    utObj,
                    testCaseId,
                    FALSE);
                if (testCaseIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Test case ID not found\r\n");
                }
                else
                {
                    memcpy(&gDispDssTestCfg,
                           &gTestDispDssTestCfg[testCaseIdx],
                           sizeof (st_DispDssTestCfg));

                    for (instID = 0; instID < gDispDssTestCfg.numInst;
                         instID++)
                    {
                        memcpy(
                            &gDispDssTestInstCfg[instID],
                            &gTestDispDssTestInstCfg[testCaseIdx][instID],
                            sizeof (st_DispDssTestInstCfg));
                    }
                    /* Check whether test case is disabled */
                    if ((FALSE == gDispDssTestCfg.enableTest) &&
                        (gDispDssTestInstCfg[0].platformSocId & platformSocId))
                    {
                        GT_assert(utObj->traceMask,
                                  (NULL != gDispDssTestCfg.testCaseName));
                        GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
                        GT_1trace(utObj->traceMask, GT_INFO,
                                  "|TEST DISABLED|:: %d ::\r\n",
                                  gDispDssTestCfg.testCaseId);
                        GT_1trace(utObj->traceMask, GT_INFO,
                                  "|TEST PARAM|:: %s ::\r\n",
                                  gDispDssTestCfg.testCaseName);
                        if (NULL != gDispDssTestCfg.disableReason)
                        {
                            GT_1trace(utObj->traceMask, GT_INFO,
                                      "|TEST DISABLE REASON|:: %s ::\r\n",
                                      gDispDssTestCfg.disableReason);
                        }
                        else
                        {
                            GT_0trace(
                                utObj->traceMask, GT_INFO,
                                "|TEST DISABLE REASON|:: Not Provided!! ::\r\n");
                        }
                    }
                    if (gDispDssTestInstCfg[0].platformSocId & platformSocId)
                    {
                        retVal = st_dispDssRunTestCase(utObj,
                                                       &gDispDssTestCfg);
                        if (FVID2_SOK != retVal)
                        {
                            GT_0trace(utObj->traceMask, GT_ERR,
                                      "Failed to run test case!!\r\n");
                        }
                    }
                }
                break;
            case '4':
                testType |= ST_TT_FULL;
            case '3':
                testType |= ST_TT_REGRESSION;
            case '2':
                /* Test execution started. Change main menu timeout to
                   wait forever for next run. */
                mainMenuTimeout = BSP_UTILS_UART_RX_WAIT_FOREVER;
                GT_0trace(
                    utObj->traceMask, GT_INFO,
                    "Enter Start Test Case Id (Enter 0 to start from first): \r\n");
                retVal = BspUtils_uartGetNum(&testCaseId,BSP_UTILS_UART_RX_DEFAULT_TIMEOUT);
                if (retVal == BSP_ETIMEOUT)
                {
                    testCaseId = 0;
                }
                startIdx   = st_dispDssGetTestCaseIdx(utObj, testCaseId,
                                                      TRUE);
                if (startIdx < 0)
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                              "Test case ID not found\r\n");
                    continue;
                }

                /* Run all test cases one after the other depending on
                 * selected
                 * flag */
                startTime1       = Clock_getTicks();
                utObj->skipCount = utObj->disableCount = 0u;

                for (testCnt = startIdx; testCnt < utObj->numTescases;
                     testCnt++)
                {
                    memcpy(&gDispDssTestCfg, &gTestDispDssTestCfg[testCnt],
                           sizeof (st_DispDssTestCfg));

                    for (instID = 0; instID < gDispDssTestCfg.numInst;
                         instID++)
                    {
                        memcpy(&gDispDssTestInstCfg[instID],
                               &gTestDispDssTestInstCfg[testCnt][instID],
                               sizeof (st_DispDssTestInstCfg));
                    }

                    testPrms = &gTestDispDssTestCfg[testCnt];

                    if (gDispDssTestInstCfg[0].platformSocId & platformSocId)
                    {
                        /* Check whether to execute test or not */
                        if (st_dispDssCheckIfTestToBeSkipped(utObj, testPrms,
                                                             testType))
                        {
                            continue;   /* Skip test */
                        }

                        retVal = st_dispDssRunTestCase(utObj, testPrms);
                        if (FVID2_SOK != retVal)
                        {
                            GT_0trace(utObj->traceMask, GT_ERR,
                                      "Failed to run test case!!\r\n");
                        }
                    }
                }

                /* Print test results */
                st_printTestResult(
                    utObj,
                    utObj->skipCount,
                    utObj->disableCount);

                endTime1 = Clock_getTicks();
                hrs      = (endTime1 - startTime1) / (1000u * 60u * 60u);
                mins     =
                    ((endTime1 - startTime1) / (1000u * 60u)) - (hrs * 60u);
                GT_2trace(utObj->traceMask, GT_INFO,
                          "|TOTAL TEST DURATION|: %d hrs %d mins\r\n", hrs,
                          mins);
                break;

            case 'd':
                /* Display test info */
                st_dispDssDisplayTestInfo(utObj);
                break;

            case 'g':
                /* Generate test report */
                st_dispDssGenerateTestReports(utObj);
                break;

            default:
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Invalid option try again!!\r\n");
                break;
        }
    }
    utObj->yuyv422BufCnt = 0u;

    for (bufCfgId = 0;
         bufCfgId <
         (sizeof (gDispDssLoadBufCfg) / sizeof (st_DispDssLoadBufCfg));
         bufCfgId++)
    {
        retVal = st_dispDssFreeBuf(utObj, &gDispDssLoadBufCfg[bufCfgId]);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR,
                      "Free buffer failed!!\r\n");
        }
    }
    /* check for leak */
    st_dispDssCheckHeapStat(&startHeapStat, utObj->traceMask);
    return (retVal);
}

/**
 *  st_dispDssCreateTestTasks
 */
static Int32 st_dispDssCreateTestTasks(st_DispDssUtObj *utObj)
{
    char                   tempString[300u];
    Int32                  retVal = FVID2_SOK;
    UInt32                 taskCnt, createdTsk;
    UInt32                 startTime, endTime, hrs, mins, secs, msecs;
    BspUtils_MemHeapStatus startHeapStat;
    st_DispDssAppObj      *appObj;
    Task_Params            tskPrms[ST_DISP_DSS_TASK_MAX];
    Task_Handle            tskHandle[ST_DISP_DSS_TASK_MAX];
    Semaphore_Params       semPrms[ST_DISP_DSS_TASK_MAX + 1];
    UInt32                 taskCntdispDss = 0;
    st_DispDssMsgObj       dctrlmsgObj;
    st_DispDssMsgObj       vidPpl1msgObj;
    st_DispDssMsgObj       vidPpl2msgObj;
    st_DispDssMsgObj       vidPpl3msgObj;
    st_DispDssMsgObj       gfxPpl1msgObj;
    UInt32                 cnt, cmd, testInstId, instId, flag = TRUE;
    char                  *val;
    UInt32                 loopCount[10] = {0};
    UInt32                 execTimeInMsecs = 0U;
    Int32                  testResult = FVID2_SOK;
    UInt32                 testFlag   = TRUE;
    UInt32                 dispFrmCount = 0U;
    UInt32                 openCloseCnt;
    UInt32                 startStopCnt;
    UInt32                 testErrorInstID    = 100;
    UInt32                 tesInstloopCnt[4]  = {0};
    UInt32                 tesInstloopCntFlag = FALSE;
    UInt32                 maxloopCnt         = 0;
    /* NULL pointer check */
    GT_assert(utObj->traceMask, (gDispDssTestCfg.numInst <= VPS_DISP_INST_MAX));
    GT_assert(utObj->traceMask, (NULL != gDispDssTestCfg.testCaseName));

    startTime = Clock_getTicks();
    GT_0trace(utObj->traceMask, GT_INFO, " \r\n");
    GT_1trace(utObj->traceMask, GT_INFO,
              "|TEST START|:: %d ::\r\n", gDispDssTestCfg.testCaseId);
    GT_2trace(utObj->traceMask, GT_INFO,
              "|TEST PARAM|:: %s (Start Time= %dms) ::\r\n",
              gDispDssTestCfg.testCaseName, startTime);
    /* Get the heap status at the start */
    BspUtils_memGetHeapStat(&startHeapStat);

    startTime = Clock_getTicks();   /* Reset time to exclude print */

    /* Create TimeStamp object */
    utObj->prfTsHandle = BspUtils_prfTsCreate(UT_NAME);
    GT_assert(utObj->traceMask, (utObj->prfTsHandle != NULL));
    for (testInstId = 0; testInstId < gDispDssTestCfg.numInst;
         testInstId++)
    {
        if (maxloopCnt < gDispDssTestInstCfg[testInstId].loopCnt)
            maxloopCnt = gDispDssTestInstCfg[testInstId].loopCnt;
    }
    Semaphore_Params_init(&semPrms[0]);
    semPrms[0].mode         = Semaphore_Mode_BINARY;
    gStDispDssMasterTaskSem = Semaphore_create(0u, &semPrms[0], NULL);
    if (NULL == gStDispDssMasterTaskSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gStDispDssMasterTaskSem != NULL));
    }

    Semaphore_Params_init(&semPrms[1]);
    semPrms[1].mode        = Semaphore_Mode_BINARY;
    gStDispDssDctrlTaskSem = Semaphore_create(0u, &semPrms[1], NULL);
    if (NULL == gStDispDssDctrlTaskSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gStDispDssDctrlTaskSem != NULL));
    }

    Semaphore_Params_init(&semPrms[2]);
    semPrms[2].mode          = Semaphore_Mode_BINARY;
    gStDispDssVidPpl1TaskSem = Semaphore_create(0u, &semPrms[2], NULL);
    if (NULL == gStDispDssVidPpl1TaskSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gStDispDssVidPpl1TaskSem != NULL));
    }

    Semaphore_Params_init(&semPrms[3]);
    semPrms[3].mode          = Semaphore_Mode_BINARY;
    gStDispDssVidPpl2TaskSem = Semaphore_create(0u, &semPrms[3], NULL);
    if (NULL == gStDispDssVidPpl2TaskSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gStDispDssVidPpl2TaskSem != NULL));
    }

    Semaphore_Params_init(&semPrms[4]);
    semPrms[4].mode          = Semaphore_Mode_BINARY;
    gStDispDssVidPpl3TaskSem = Semaphore_create(0u, &semPrms[4], NULL);
    if (NULL == gStDispDssVidPpl3TaskSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gStDispDssVidPpl3TaskSem != NULL));
    }

    Semaphore_Params_init(&semPrms[5]);
    semPrms[5].mode          = Semaphore_Mode_BINARY;
    gStDispDssGfxPpl1TaskSem = Semaphore_create(0u, &semPrms[5], NULL);
    if (NULL == gStDispDssGfxPpl1TaskSem)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Sem create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gStDispDssGfxPpl1TaskSem != NULL));
    }

    gDctrlmsgQueue = Queue_create(NULL, NULL);

    if (NULL == gDctrlmsgQueue)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Queue create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gDctrlmsgQueue != NULL));
    }

    gVidPpl1msgQueue = Queue_create(NULL, NULL);

    if (NULL == gVidPpl1msgQueue)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Queue create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gVidPpl1msgQueue != NULL));
    }

    gVidPpl2msgQueue = Queue_create(NULL, NULL);

    if (NULL == gVidPpl2msgQueue)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Queue create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gVidPpl2msgQueue != NULL));
    }

    gVidPpl3msgQueue = Queue_create(NULL, NULL);

    if (NULL == gVidPpl3msgQueue)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Queue create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gVidPpl3msgQueue != NULL));
    }

    gGfxPpl1msgQueue = Queue_create(NULL, NULL);

    if (NULL == gGfxPpl1msgQueue)
    {
        GT_1trace(utObj->traceMask, GT_ERR,
                  "%s: Queue create failed\r\n", __FUNCTION__);
        retVal = FVID2_EALLOC;
        GT_assert(utObj->traceMask, (gGfxPpl1msgQueue != NULL));
    }

    memset(&gAppDispDssObj, 0u, sizeof (gAppDispDssObj));
    memset(&tskHandle, 0u, sizeof (tskHandle));
    if (FVID2_SOK == retVal)
    {
        createdTsk = 0u;
        for (taskCnt = 0u; taskCnt < ST_DISP_DSS_TASK_MAX; taskCnt++)
        {
            appObj = &gAppDispDssObj[taskCntdispDss];
            retVal = st_dispDssInitAppObj(utObj, appObj, taskCnt);
            if (FVID2_SOK != retVal)
            {
                break;
            }

            /* Create individual tasks */
            Task_Params_init(&tskPrms[taskCnt]);
            tskPrms[taskCnt].stack =
                &gStDispDssTestTskStack[taskCntdispDss][0u];
            tskPrms[taskCnt].stackSize = ST_TSK_STACK_SIZE;
            tskPrms[taskCnt].arg0      = (UArg) appObj;

            switch (taskCnt)
            {
                case 0:
                    tskHandle[taskCnt] = Task_create(
                        (Task_FuncPtr) st_dispDssDctrlTestTask,
                        &tskPrms[taskCnt],
                        NULL);

                    break;

                case 1:
                    tskHandle[taskCnt] = Task_create(
                        (Task_FuncPtr) st_dispDssVidPpl1TestTask,
                        &tskPrms[taskCnt],
                        NULL);

                    break;

                case 2:
                    tskHandle[taskCnt] = Task_create(
                        (Task_FuncPtr) st_dispDssVidPpl2TestTask,
                        &tskPrms[taskCnt],
                        NULL);

                    break;

                case 3:
                    tskHandle[taskCnt] = Task_create(
                        (Task_FuncPtr) st_dispDssVidPpl3TestTask,
                        &tskPrms[taskCnt],
                        NULL);

                    break;

                case 4:
                    tskHandle[taskCnt] = Task_create(
                        (Task_FuncPtr) st_dispDssGfxPpl1TestTask,
                        &tskPrms[taskCnt],
                        NULL);

                    break;
            }

            if (NULL == tskHandle[taskCnt])
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "%s: Task create failed\r\n", __FUNCTION__);
                retVal = FVID2_EALLOC;
                break;
            }

            createdTsk++;
            taskCntdispDss++;
            sprintf(tempString, "ST_DISPDSS Task %d", (int) taskCnt);
            BspUtils_prfLoadRegister(tskHandle[taskCnt], tempString);
        }
    }

    cnt          = 0;
    openCloseCnt = 1u;
    startStopCnt = 1u;

    while (1)
    {
        switch (cnt)
        {
            case 0:
                cmd = 0;
                val = "CREATE";
                break;

            case 1:
                cmd = 4;
                val = "CONTROL";
                break;

            case 2:
                cmd = 7;
                val = "ALLOC_AND_QUEUE";
                break;

            case 3:
                cmd = 2;
                val = "START";
                break;

            case 4:
                cmd = 3;
                val = "STOP";
                break;

            case 5:
            default:
                cmd = 1;
                val = "DELETE";
                break;
        }
        if (cnt == 0)
        {
            dctrlmsgObj.cmd = cmd;
            dctrlmsgObj.val = val;
            Queue_put(gDctrlmsgQueue, (Queue_Elem *) (&dctrlmsgObj));

            if (openCloseCnt > 1)
            {
                Semaphore_post(gStDispDssDctrlTaskSem);
            }

            Semaphore_pend(gStDispDssMasterTaskSem, BIOS_WAIT_FOREVER);

            if (gAppDispDssObj[0].taskResult != FVID2_SOK)
            {
                testResult = gAppDispDssObj[0].taskResult;
                goto EndLabel;
            }

            dctrlmsgObj.cmd = 4;
            dctrlmsgObj.val = "CONTROL";
            Queue_put(gDctrlmsgQueue, (Queue_Elem *) (&dctrlmsgObj));
            Semaphore_post(gStDispDssDctrlTaskSem);
            Semaphore_pend(gStDispDssMasterTaskSem, BIOS_WAIT_FOREVER);

            if (gAppDispDssObj[0].taskResult != FVID2_SOK)
            {
                cmd        = 1;
                testResult = gAppDispDssObj[0].taskResult;
                goto DctrlEndLabel;
            }
        }

        if ((cmd == 2) && (flag == TRUE))
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      UT_NAME ": Starting display ... !!!\r\n");
            GT_0trace(BspAppTrace, GT_INFO,
                      UT_NAME ": Display in progress ... DO NOT HALT !!!\r\n");

            /* Start the load calculation */
            BspUtils_prfLoadCalcStart();
            BspUtils_prfTsBegin(utObj->prfTsHandle);
        }

        if (cmd == 1)
        {
            for (testInstId = 0; testInstId < gDispDssTestCfg.numInst;
                 testInstId++)
            {
                instId = (gDispDssTestInstCfg[testInstId].videoNode) + 1;

                /* Print the driver status */
                BspUtils_appPrintDispStatus(
                    gAppDispDssObj[instId].instObj.drvHandle,
                    gAppDispDssObj[instId].instObj.instId,
                    execTimeInMsecs);
            }
        }
        if (flag == TRUE)
        {
            gTestVal++;
            for (testInstId = 0; testInstId < gDispDssTestCfg.numInst;
                 testInstId++)
            {
                switch (gDispDssTestInstCfg[testInstId].videoNode)
                {
                    case VID1:
                        if ((cmd == 3) && (tesInstloopCnt[testInstId] == 0))
                        {
                            break;
                        }
                        vidPpl1msgObj.cmd = cmd;
                        vidPpl1msgObj.val = val;
                        Queue_put(gVidPpl1msgQueue,
                                  (Queue_Elem *) (&vidPpl1msgObj));
                        Semaphore_post(gStDispDssVidPpl1TaskSem);
                        Semaphore_pend(gStDispDssMasterTaskSem,
                                       BIOS_WAIT_FOREVER);
                        testResult = gAppDispDssObj[1].taskResult;
                        if (cmd == 3)
                        {
                            tesInstloopCnt[testInstId] = 2;
                        }
                        break;

                    case VID2:
                        if ((cmd == 3) && (tesInstloopCnt[testInstId] == 0))
                        {
                            break;
                        }
                        vidPpl2msgObj.cmd = cmd;
                        vidPpl2msgObj.val = val;
                        Queue_put(gVidPpl2msgQueue,
                                  (Queue_Elem *) (&vidPpl2msgObj));
                        Semaphore_post(gStDispDssVidPpl2TaskSem);
                        Semaphore_pend(gStDispDssMasterTaskSem,
                                       BIOS_WAIT_FOREVER);
                        testResult = gAppDispDssObj[2].taskResult;
                        if (cmd == 3)
                        {
                            tesInstloopCnt[testInstId] = 2;
                        }
                        break;

                    case VID3:
                        if ((cmd == 3) && (tesInstloopCnt[testInstId] == 0))
                        {
                            break;
                        }
                        vidPpl3msgObj.cmd = cmd;
                        vidPpl3msgObj.val = val;
                        Queue_put(gVidPpl3msgQueue,
                                  (Queue_Elem *) (&vidPpl3msgObj));
                        Semaphore_post(gStDispDssVidPpl3TaskSem);
                        Semaphore_pend(gStDispDssMasterTaskSem,
                                       BIOS_WAIT_FOREVER);
                        testResult = gAppDispDssObj[3].taskResult;
                        if (cmd == 3)
                        {
                            tesInstloopCnt[testInstId] = 2;
                        }
                        break;

                    case GFX1:
                        if ((cmd == 3) && (tesInstloopCnt[testInstId] == 0))
                        {
                            break;
                        }
                        gfxPpl1msgObj.cmd = cmd;
                        gfxPpl1msgObj.val = val;
                        Queue_put(gGfxPpl1msgQueue,
                                  (Queue_Elem *) (&gfxPpl1msgObj));
                        Semaphore_post(gStDispDssGfxPpl1TaskSem);
                        Semaphore_pend(gStDispDssMasterTaskSem,
                                       BIOS_WAIT_FOREVER);
                        testResult = gAppDispDssObj[4].taskResult;
                        if (cmd == 3)
                        {
                            tesInstloopCnt[testInstId] = 2;
                        }
                        break;
                }

                if (testErrorInstID == testInstId)
                {
                    goto DctrlEndLabel;
                }
                if ((!testFlag) & (testInstId == (gDispDssTestCfg.numInst - 1)))
                {
                    testFlag = TRUE;
                    break;
                }

                if ((testResult != FVID2_SOK) & (cmd == 0))
                {
                    if (testInstId == 0)
                    {
                        cmd = 1;
                        goto DctrlEndLabel;
                    }
                    else
                    {
                        cnt             = 5;
                        testFlag        = FALSE;
                        testErrorInstID = testInstId - 1;
                        break;
                    }
                }
                else if (testResult != FVID2_SOK)
                {
                    cnt      = 5;
                    testFlag = FALSE;
                    break;
                }
            }
        }

        if (!testFlag)
            continue;

        if (cmd == 0)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      UT_NAME ": Display create complete!!\r\n");
        }
        if ((tesInstloopCntFlag == TRUE) && (cmd == 3))
        {
            if (startStopCnt < utObj->sysCtrl.startStopCnt)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          UT_NAME ": Stopping display ... DONE !!!\r\n");

                cnt = 3;

                startStopCnt++;
                tesInstloopCntFlag = FALSE;
                for (testInstId = 0; testInstId < gDispDssTestCfg.numInst;
                     testInstId++)
                {
                    instId = (gDispDssTestInstCfg[testInstId].videoNode) + 1;
                    loopCount[instId]          = 0;
                    tesInstloopCnt[testInstId] = 0;
                }
                continue;
            }
            else
            {
                /* Stop the load calculation */
                BspUtils_prfLoadCalcStop();

                BspUtils_prfTsEnd(
                    utObj->prfTsHandle,
                    (dispFrmCount));

                GT_0trace(BspAppTrace, GT_INFO,
                          UT_NAME ": Stopping display ... DONE !!!\r\n");
            }
        }
        else if ((tesInstloopCntFlag == FALSE) && (cmd == 3))
        {
            flag = FALSE;
            cnt--;
        }
DctrlEndLabel:

        if (cmd == 1)
        {
            dctrlmsgObj.cmd = 1;
            dctrlmsgObj.val = "DELETE";
            Queue_put(gDctrlmsgQueue, (Queue_Elem *) (&dctrlmsgObj));
            Semaphore_post(gStDispDssDctrlTaskSem);
            Semaphore_pend(gStDispDssMasterTaskSem, BIOS_WAIT_FOREVER);
            if (openCloseCnt < utObj->sysCtrl.openCloseCnt)
            {
                cnt          = 0;
                startStopCnt = 1u;
                openCloseCnt++;
                tesInstloopCntFlag = FALSE;
                for (testInstId = 0; testInstId < gDispDssTestCfg.numInst;
                     testInstId++)
                {
                    instId = (gDispDssTestInstCfg[testInstId].videoNode) + 1;
                    loopCount[instId]          = 0;
                    tesInstloopCnt[testInstId] = 0;
                }
                continue;
            }
            else
            {
                break;
            }
        }

        if (cmd == 2)
        {
            flag = FALSE;
        }

        if (flag == FALSE)
        {
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                /* check status every sec */
                BspOsal_sleep(1000);
            }
            else
            {
                BspOsal_sleep(1);
            }

            for (testInstId = 0; testInstId < gDispDssTestCfg.numInst;
                 testInstId++)
            {
                instId = (gDispDssTestInstCfg[testInstId].videoNode) + 1;

                if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
                {
                    loopCount[instId]++;
                }
                else
                {
                    if (loopCount[instId] !=
                        gAppDispDssObj[instId].callBackCount)
                    {
                        GT_1trace(gAppDispDssObj[instId].traceMask, GT_INFO,
                                  UT_NAME ": Displayed %d frames!!\r\n",
                                  gAppDispDssObj[instId].callBackCount);

                        loopCount[instId] =
                            gAppDispDssObj[instId].callBackCount;
                    }
                }

                if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
                {
                    if (gAppDispDssObj[instId].callBackCount >
                        utObj->sysCtrl.loopCnt)
                    {
                        flag = TRUE;
                    }
                }
                else
                {
                    if (loopCount[instId] >
                        gDispDssTestInstCfg[testInstId].loopCnt)
                    {
                        if (tesInstloopCnt[testInstId] == 0)
                        {
                            flag = TRUE;
                            tesInstloopCnt[testInstId] = 1;
                        }
                        dispFrmCount = gAppDispDssObj[instId].callBackCount;
                    }
                    if (loopCount[instId] > maxloopCnt)
                    {
                        tesInstloopCntFlag = TRUE;
                    }
                }
            }
        }

        if (flag)
        {
            cnt++;
        }
    }

EndLabel:

    /* Print the load */
    BspUtils_prfLoadPrintAll(TRUE);

    /* print the fps based on TimeStamp */
    BspUtils_prfTsPrint(utObj->prfTsHandle, TRUE);

    /* Reset the load */
    BspUtils_prfLoadCalcReset();

    /* Delete the created task */
    for (taskCnt = 0u; taskCnt < ST_DISP_DSS_TASK_MAX; taskCnt++)
    {
        if (NULL != tskHandle[taskCnt])
        {
            BspUtils_prfLoadUnRegister(tskHandle[taskCnt]);
            Task_delete(&tskHandle[taskCnt]);
            tskHandle[taskCnt] = NULL;
        }
    }

    Semaphore_delete(&gStDispDssGfxPpl1TaskSem);
    Semaphore_delete(&gStDispDssVidPpl3TaskSem);
    Semaphore_delete(&gStDispDssVidPpl2TaskSem);
    Semaphore_delete(&gStDispDssVidPpl1TaskSem);
    Semaphore_delete(&gStDispDssDctrlTaskSem);
    Semaphore_delete(&gStDispDssMasterTaskSem);

    if (NULL != utObj->prfTsHandle)
    {
        BspUtils_prfTsDelete(utObj->prfTsHandle);
        utObj->prfTsHandle = NULL;
    }

    if (NULL != gVidPpl1msgQueue)
    {
        Queue_delete(&gVidPpl1msgQueue);
    }

    if (NULL != gVidPpl2msgQueue)
    {
        Queue_delete(&gVidPpl2msgQueue);
    }

    if (NULL != gVidPpl3msgQueue)
    {
        Queue_delete(&gVidPpl3msgQueue);
    }

    if (NULL != gGfxPpl1msgQueue)
    {
        Queue_delete(&gGfxPpl1msgQueue);
    }

    if (NULL != gDctrlmsgQueue)
    {
        Queue_delete(&gDctrlmsgQueue);
    }
    /* check for leak */
    st_dispDssCheckHeapStat(&startHeapStat, utObj->traceMask);

    if (FVID2_SOK == testResult)
    {
        GT_2trace(utObj->traceMask, GT_INFO,
                  "%s: Display DSS Test Case %d Successful!!\r\n",
                  UT_NAME, gDispDssTestCfg.testCaseId);
    }
    else
    {
        GT_2trace(utObj->traceMask, GT_INFO,
                  "%s: Display DSS Test Case %d Failed!!\r\n",
                  UT_NAME, gDispDssTestCfg.testCaseId);
    }

    endTime = Clock_getTicks();
    hrs     = (endTime - startTime) / (1000u * 60u * 60u);
    mins    = ((endTime - startTime) / (1000u * 60u)) - (hrs * 60u);
    secs    = ((endTime - startTime) / 1000u) - (((hrs * 60u) + mins) * 60u);
    msecs   = (endTime - startTime) -
              (((hrs * 60u * 60u) + (mins * 60u) + secs) * 1000u);
    GT_4trace(utObj->traceMask, GT_INFO,
              "|TEST DURATION|:: %d:%0.2d:%0.2d:%0.3d ::\r\n",
              hrs, mins, secs, msecs);

    sprintf(tempString, "%s (End Time= %dms)",
            gDispDssTestCfg.testCaseName, (unsigned int ) endTime);

    st_logTestResult(utObj, testResult, gDispDssTestCfg.testCaseId,
                     gDispDssTestCfg.testCaseName);

    return testResult;
}

/**
 *  st_dispDssInitAppObj
 */
static Int32 st_dispDssInitAppObj(const st_DispDssUtObj *utObj,
                                  st_DispDssAppObj      *appObj,
                                  UInt32                 taskCnt)
{
    Int32 retVal = FVID2_SOK;

    /* Assign platform type, board and CPU revisions */
    appObj->platformId = utObj->platformId;
    appObj->cpuRev     = utObj->cpuRev;
    appObj->boardId    = utObj->boardId;
    appObj->traceMask  = (GT_INFO | GT_TraceState_Enable);;

    /* Copy user params */
    appObj->testPrms.testCaseId   = gDispDssTestCfg.testCaseId;
    appObj->testPrms.testCaseName = gDispDssTestCfg.testCaseName;
    appObj->testPrms.numHandles   = gDispDssTestCfg.numInst;

    return (retVal);
}

/* Main menu 0 string */
static char gStDispDssMenuMain0[] =
{
    "\r\n "
    "\r\n ====================="
    "\r\n Display DSS UT Select"
    "\r\n ====================="
    "\r\n "
};

/* Main menu string */
static char gStDispDssMenuMain[] =
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

static char gStDispDssMenuSettings0[] = {
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
};

static char gStDispDssMenuSettings1[] = {
    "\r\n "
    "\r\n 1: Skip Halt Test Case"
    "\r\n 2: Execution Loop Count"
    "\r\n 3: Start/Stop Count"
    "\r\n 4: Open/Close Count"
    "\r\n r: Runtime Print"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
};

/**
 *  st_dispDssMenuSettings
 */
static Void st_dispDssMenuSettings(st_DispDssUtObj *utObj)
{
    char           option;
    Bool           done = FALSE;
    Int32          value;
    st_SystemCtrl *sysCtrl = &utObj->sysCtrl;

    st_dispDssMenuSettingsShow(utObj);

    while (!done)
    {
        GT_0trace(utObj->traceMask, GT_INFO, " Enter Choice: \r\n");
        BspUtils_uartGetChar(&option, BSP_UTILS_UART_RX_WAIT_FOREVER);

        switch (option)
        {
            case '1':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Skip Halt Test Enable [0: Enable, 1: Skip]: \r\n");
                BspUtils_uartGetNum(&value, BSP_UTILS_UART_RX_WAIT_FOREVER);

                sysCtrl->skipHaltTests = FALSE;
                if (1 == value)
                {
                    sysCtrl->skipHaltTests = TRUE;
                }
                break;

            case '2':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Loop count in frames: \r\n");
                BspUtils_uartGetNum(&value, BSP_UTILS_UART_RX_WAIT_FOREVER);

                if (value != USE_DEF_LP_CNT)
                {
                    sysCtrl->loopCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, give another value\r\n");
                }
                break;

            case '3':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Start/stop count: \r\n");
                BspUtils_uartGetNum(&value, BSP_UTILS_UART_RX_WAIT_FOREVER);

                if (value != USE_DEF_SS_CNT)
                {
                    sysCtrl->startStopCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, give another value\r\n");
                }
                break;

            case '4':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Open/close count: \r\n");
                BspUtils_uartGetNum(&value, BSP_UTILS_UART_RX_WAIT_FOREVER);

                if (value != USE_DEF_OC_CNT)
                {
                    sysCtrl->openCloseCnt = value;
                }
                else
                {
                    GT_0trace(
                        utObj->traceMask, GT_INFO,
                        "This matches with default flag, give another value\r\n");
                }
                break;

            case 'r':
                GT_0trace(utObj->traceMask, GT_INFO,
                          " Runtime Print Enable [0: Disable, 1: Enable]: \r\n");
                BspUtils_uartGetNum(&value, BSP_UTILS_UART_RX_WAIT_FOREVER);

                sysCtrl->rtPrintEnable = FALSE;
                if (1 == value)
                {
                    sysCtrl->rtPrintEnable = TRUE;
                }
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
 *  st_dispDssMenuMainShow
 */
static Void st_dispDssMenuMainShow(st_DispDssUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStDispDssMenuMain0);
    st_dispDssMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStDispDssMenuMain);

    return;
}

/**
 *  st_dispDssMenuSettingsShow
 */
static Void st_dispDssMenuSettingsShow(st_DispDssUtObj *utObj)
{
    GT_0trace(utObj->traceMask, GT_INFO, gStDispDssMenuSettings0);
    st_dispDssMenuCurrentSettingsShow(utObj);
    GT_0trace(utObj->traceMask, GT_INFO, gStDispDssMenuSettings1);

    return;
}

/**
 *  st_dispDssMenuCurrentSettingsShow
 */
static Void st_dispDssMenuCurrentSettingsShow(st_DispDssUtObj *utObj)
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
              "\r\n Runtime Print          : %s",
              enableDisableName[sysCtrl->rtPrintEnable]);
    GT_0trace(utObj->traceMask, GT_INFO, "\r\n ");

    return;
}

/**
 *  st_dispDssSetDefaultCfg
 */
static Void st_dispDssSetDefaultCfg(st_DispDssUtObj *utObj)
{
    UInt32 testCnt;
    st_DispDssTestCfg *testPrms;

    utObj->traceMask  = (GT_INFO1 | GT_TraceState_Enable);
    utObj->platformId = BSP_PLATFORM_ID_UNKNOWN;
    utObj->cpuRev     = BSP_PLATFORM_CPU_REV_1_0;
    utObj->boardId    = BSP_BOARD_UNKNOWN;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        st_dispDssDetectBoard(utObj);
    }

    utObj->sysCtrl.skipHaltTests = TRUE;
    utObj->sysCtrl.loopCnt       = DEF_LOOP_CNT;
    if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
    {
        utObj->sysCtrl.loopCnt = DEF_LOOP_CNT_EVM;
    }
    utObj->sysCtrl.startStopCnt  = DEF_START_STOP_CNT;
    utObj->sysCtrl.openCloseCnt  = DEF_OPEN_CLOSE_CNT;
    utObj->sysCtrl.rtPrintEnable = FALSE;
    utObj->numTescases           = sizeof (gTestDispDssTestCfg) /
                                   sizeof (st_DispDssTestCfg);

    /* Mark all test cases as not run and set result to PASS */
    for (testCnt = 0u; testCnt < utObj->numTescases; testCnt++)
    {
        testPrms             = &gTestDispDssTestCfg[testCnt];
        testPrms->isRun      = FALSE;
        testPrms->testResult = FVID2_SOK;
    }

    return;
}

/**
 *  st_dispDssDetectBoard
 */
static Int32 st_dispDssDetectBoard(st_DispDssUtObj *utObj)
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

/**
 *  st_dispDssRunTestCase
 */
static Int32 st_dispDssRunTestCase(st_DispDssUtObj   *utObj,
                                   st_DispDssTestCfg *testPrms)
{
    char  inputStr[10];
    Int32 retVal = FVID2_SOK;

    testPrms->isRun = TRUE;
    switch (testPrms->testCaseType)
    {
        case ST_DISP_DSS_TCT_MAIN:
            /* Create all test tasks */
            retVal = st_dispDssCreateTestTasks(utObj);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          "Display Dss test failed!!\r\n");
            }

            /* Store the test result */
            testPrms->testResult = retVal;
            break;

        case ST_DISP_DSS_TCT_HALT:
            /* NULL pointer check */
            GT_assert(utObj->traceMask, (NULL != testPrms->testCaseName));
            GT_1trace(utObj->traceMask, GT_INFO,
                      "\r\nUser Input Halt: %s\r\n", testPrms->testCaseName);
            BspUtils_uartGetStr(inputStr, 10, BSP_UTILS_UART_RX_WAIT_FOREVER);
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
 *  st_dispDssGetTestCaseIdx
 */
static Int32 st_dispDssGetTestCaseIdx(st_DispDssUtObj *utObj,
                                      UInt32           testCaseId,
                                      Bool             isSearchForward)
{
    Int32  testCaseIdx = -1;
    UInt32 testCnt;
    const st_DispDssTestCfg *testPrms;

    testPrms = &gTestDispDssTestCfg[0u];
    for (testCnt = 0u; testCnt < utObj->numTescases; testCnt++)
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
 *  st_dispDssCheckIfTestToBeSkipped
 */
static Bool st_dispDssCheckIfTestToBeSkipped(st_DispDssUtObj         *utObj,
                                             const st_DispDssTestCfg *testPrms,
                                             UInt32                   testType)
{
    Bool skipTest = FALSE;
    Bsp_PlatformSocId platformSocId;

    platformSocId = Bsp_platformGetSocId();

    /* Check whether test case is disabled */
    if ((FALSE == gDispDssTestCfg.enableTest) &&
        (gDispDssTestInstCfg[0].platformSocId & platformSocId))
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
        (ST_DISP_DSS_TCT_HALT == testPrms->testCaseType))
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
 *  st_dispDssDisplayTestInfo
 */
static Int32 st_dispDssDisplayTestInfo(st_DispDssUtObj *utObj)
{
    UInt32             sCnt, testCnt;
    char              *runStatus;
    st_DispDssTestCfg *testPrms;
    static char       *enableDisableName[] = {"Disabled", "Enabled"};
    static char        printBuf[300];
    Bsp_PlatformSocId  platformSocId;

    platformSocId = Bsp_platformGetSocId();

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
    for (testCnt = 0u; testCnt < utObj->numTescases; testCnt++)
    {
        testPrms = &gTestDispDssTestCfg[testCnt];

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (!(gTestDispDssTestInstCfg[testCnt][0].platformSocId &
                  platformSocId))
            {
                runStatus = "NA";
            }
            if (FALSE == testPrms->enableTest)
            {
                runStatus = "BLK";
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
                 (char *) UT_NAME,
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
 *  st_dispDssGenerateTestReports
 */
static Int32 st_dispDssGenerateTestReports(st_DispDssUtObj *utObj)
{
    UInt32             sCnt, testCnt;
    char              *runStatus, *category, *adequacy;
    st_DispDssTestCfg *testPrms;
    static char        printBuf[300];
    Bsp_PlatformSocId  platformSocId;

    platformSocId = Bsp_platformGetSocId();

    sCnt = 1;
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        utObj->traceMask, GT_INFO,
        "S.No;ID;Requirement Mapping;Description;Test Result;IR;Category;"
        "Test Adequacy;\r\n");
    for (testCnt = 0u; testCnt < utObj->numTescases; testCnt++)
    {
        testPrms = &gTestDispDssTestCfg[testCnt];

        runStatus = "NRY";
        if (FALSE == testPrms->isRun)
        {
            if (!(gTestDispDssTestInstCfg[testCnt][0].platformSocId &
                  platformSocId))
            {
                runStatus = "NA";
            }
            else if (FALSE == testPrms->enableTest)
            {
                runStatus = "BLK";
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
                 "%d;%s_TC%4d;%s;%s;%s;%s;%s;%s",
#else
                 "%d;%s_TC%0.4d;%s;%s;%s;%s;%s;%s",
#endif
                 (unsigned int) sCnt,
                 (char *) UT_NAME,
                 (unsigned int) testPrms->testCaseId,
                 testPrms->reqId,
                 testPrms->testCaseName,
                 testPrms->disableReason,
                 category,
                 adequacy,
                 runStatus
                 );
        GT_1trace(utObj->traceMask, GT_INFO, "%s\r\n", printBuf);

        sCnt++;
    }
    GT_0trace(utObj->traceMask, GT_INFO1, " \r\n");

    return (FVID2_SOK);
}

