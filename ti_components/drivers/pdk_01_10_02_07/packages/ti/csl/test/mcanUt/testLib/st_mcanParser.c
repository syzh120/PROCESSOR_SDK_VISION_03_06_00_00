/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *
 */

/**
 *  \file st_mcanParser.c
 *
 *  \brief User interface for mcans driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on mcan driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <st_mcanTestCases.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define DEBUG_FLAG        (0U)

#define IPU_APP_INST                      (CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Parse the testcase data
 *
 * \param   None.
 *
 * \return  None
 */
int32_t mcanParser(void);

/**
 * \brief   Get the index of the testcase to run from st_mcanTestcases.h.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  None
 */
int32_t mcanGetTestcaseIdx(uint32_t testcaseId);

/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void mcanRunTestcase(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_mcanShowMainMenu(void);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_mcanShowMainMenu(void);

/**
 * \brief   Print mcan system setings.
 *
 * \param   tcIdx Testcase index for which setting is to be print.
 *
 * \return  None
 */
void st_mcanPrintSettings(uint32_t tcIdx);

/**
 * \brief   Print mcan testcases.
 *
 * \return  None
 */
void st_mcanPrintTCs(void);

/**
 * \brief   Print mcan testcase details.
 *
 * \return  None
 */
void st_mcanPrintTCDetails(uint32_t testId);

/**
 * \brief   Initialize  mcan testcase details.
 *
 * \return  None
 */
void st_mcanTCResultInit(void);

/**
 * \brief   Prints mcan Test Case Statistics.
 *
 * \return  None
 */
void st_mcanPrintTCStats(void);

/**
 * \brief   Prints mcan Test Case Results.
 *
 * \return  None
 */
void st_mcanPrintTCResults(void);

extern int32_t st_mcanefm_main(st_mcanTestcaseParams_t *testParams);

extern int32_t st_mcanRxApp_main(void);

extern int32_t st_mcanPerfRxApp_main(void);

/**
 * \brief   Print messages on UART console.
 *
 * \param   None.
 *
 * \return  None
 */
void st_mcanUARTConfig(void);

extern int32_t st_mcanTxApp_main(st_mcanTestcaseParams_t *testParams);
extern int32_t App_mcanPerfTxTest(st_mcanTestcaseParams_t *testParams);
extern void st_mcanDMARxApp(st_mcanTestcaseParams_t *testParams);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t autoRunEnable = (uint32_t)FALSE;
extern uint32_t                uartBaseAddr;
//extern st_mcanTestcaseParams_t gmcanTestcaseParams[];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t mcanParser(void)
{
    uint32_t testcaseId;
    uint32_t numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t  testcaseIdx, testIp = 1U;
#ifdef _TMS320C6X
    int32_t dspCore;
#endif
    char option;
    st_mcanTestcaseParams_t *testParams;
    volatile uint32_t debugFlag = DEBUG_FLAG;

    /* Enable Uni-cache for IPU */
#ifdef __TI_ARM_V7M4__
    UNICACHEEnable(IPU_APP_INST);
#endif

    st_mcanUARTConfig();
    while(debugFlag);
#ifdef _TMS320C6X
    /* SOC_DSP_SYSTEM_BASE + DSP_HWINFO FOR DSP1 or DSP2 */
    if(HW_RD_REG32(0x1d00000U + 0x4U )==0x0)
    {
        dspCore = 1;
    }
    else
    {
        dspCore = 2;
    }
#endif
    st_mcanTCResultInit();

    while (!done)
    {
        autoRunEnable = (uint32_t)FALSE;
        st_mcanShowMainMenu();
        UARTConfigPrintf(uartBaseAddr, "\nEnter your choice: ");
        option = UARTConfigGetc(uartBaseAddr);

        UARTConfigPrintf(uartBaseAddr, "%c\n", option);
        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch (option)
        {
            case '1':
                UARTConfigPrintf(uartBaseAddr, "\nEnter testcase ID to run: ");
                testIp = UARTConfigGetNum(uartBaseAddr);
                testcaseIdx = mcanGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    UARTConfigPrintf(uartBaseAddr, "Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gmcanTestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gmcanTestcaseParams[testcaseIdx];
                    #ifdef __TI_ARM_V7M4__
                    if (IPU == testParams->cpuID)
                    {
                        totalTCRun++;
                        mcanRunTestcase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                    #elif defined (_TMS320C6X)
                    if ((DSP1 == testParams->cpuID) &&
                        (dspCore == 1U))
                    {
                        totalTCRun++;
                        mcanRunTestcase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                    if ((DSP2 == testParams->cpuID) &&
                        (dspCore == 2U))
                    {
                        totalTCRun++;
                        mcanRunTestcase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                #endif
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%u/%u\n", totalTCRun,
                       MCAN_NUM_TESTCASES);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%u\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%u\n", numTCFail);
            break;
            case '2':
                for (testcaseId = 1;
                     testcaseId < MCAN_NUM_TESTCASES;
                     testcaseId++)
                {
                    testParams = &gmcanTestcaseParams[testcaseId];
                    if (TEST_ENABLE == testParams->enableTest &&
                        (ST_TT_SANITY == (testParams->testType & ST_TT_SANITY)))
                    {
                        if (ST_TT_SANITY ==
                            (testParams->testType & ST_TT_SANITY))
                        {
                            #ifdef __TI_ARM_V7M4__
                            if (IPU == testParams->cpuID)
                            {
                                totalTCRun++;
                                mcanRunTestcase(testParams);
                                if (STW_SOK == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                            #elif defined (_TMS320C6X)
                            if ((DSP1 == testParams->cpuID) &&
                                (dspCore == 1U))
                            {
                                totalTCRun++;
                                mcanRunTestcase(testParams);
                                if (STW_SOK == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                            if ((DSP2 == testParams->cpuID) &&
                                (dspCore == 2U))
                            {
                                totalTCRun++;
                                mcanRunTestcase(testParams);
                                if (STW_SOK == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                            #endif
                        }
                    }
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%u/%u\n", totalTCRun,
                       (MCAN_NUM_TESTCASES - 1));
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%u\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%u\n", numTCFail);
                st_mcanPrintTCResults();
            break;
            case '3':
                for (testcaseId = 1;
                     testcaseId < MCAN_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = mcanGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        UARTConfigPrintf(uartBaseAddr, "Invalid test case Id.\n");
                    }
                    else if (TEST_ENABLE ==
                             gmcanTestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gmcanTestcaseParams[testcaseIdx];
                        if (ST_TT_REGRESSION ==
                            (testParams->testType & ST_TT_REGRESSION))
                        {
                            totalTCRun++;
                            mcanRunTestcase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail--;
                            }
                        }
                    }
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%d/%d\n", totalTCRun,
                       MCAN_NUM_TESTCASES);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%d\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%d\n", numTCFail);
            break;
            case '4':
                for (testcaseId = 1;
                     testcaseId < MCAN_NUM_TESTCASES;
                     testcaseId++)
                {
                    testParams = &gmcanTestcaseParams[testcaseId];
                    if (TEST_ENABLE ==
                             testParams->enableTest)
                    {
#ifdef __TI_ARM_V7M4__
                        if (IPU == testParams->cpuID)
                        {
                            totalTCRun++;
                            mcanRunTestcase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
#elif defined (_TMS320C6X)
                        if ((DSP1 == testParams->cpuID) &&
                            (dspCore == 1U))
                        {
                            totalTCRun++;
                            mcanRunTestcase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
                        if ((DSP2 == testParams->cpuID) &&
                            (dspCore == 2U))
                        {
                            totalTCRun++;
                            mcanRunTestcase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
#endif
                    }
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%u/%u\n", totalTCRun,
                       (MCAN_NUM_TESTCASES - 1));
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%u\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%u\n", numTCFail);
                st_mcanPrintTCResults();
            break;
            case '5':
                done = 1;
                for (testcaseId = 1;
                     testcaseId < MCAN_NUM_TESTCASES;
                     testcaseId++)
                {
                    testParams = &gmcanTestcaseParams[testcaseId];
                    if ((TEST_ENABLE == testParams->enableTest) &&
                        (ST_TT_PERFORMANCE ==
                                (testParams->testType & ST_TT_PERFORMANCE)))
                    {
#ifdef __TI_ARM_V7M4__
                        if (IPU == testParams->cpuID)
                        {
                            totalTCRun++;
                            UARTConfigPrintf(uartBaseAddr, "\n|TEST START|:: %u ::\n", testParams->testcaseId);
                            UARTConfigPrintf(uartBaseAddr, "|TEST PARAM|:: %s ::\n", testParams->testCaseName);
                            UARTConfigPrintf(uartBaseAddr, "|SR|:: %s ::\n", testParams->reqId);

                            UARTConfigPrintf(uartBaseAddr, "Testcase Settings:\n");
                            UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
                            UARTConfigPrintf(uartBaseAddr, "Module                                              :0x%x\n",
                                   testParams->mcanConfigParams.mcanModule);
                            UARTConfigPrintf(uartBaseAddr, "=========================RUNNING==============================\n");
                            testParams->testResult = App_mcanPerfTxTest(testParams);
                            testParams->isRun      = STW_SOK;
                            UARTConfigPrintf(uartBaseAddr, "\n======================FINISHED==========================\n");
                            if (testParams->testResult == STW_SOK)
                                UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
                            else
                                UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

                            UARTConfigPrintf(uartBaseAddr, "|TEST INFO|:: %s ::\n", testParams->testCaseName);
                            UARTConfigPrintf(uartBaseAddr, "|TEST END|:: %u ::\n", testParams->testcaseId);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
#elif defined (_TMS320C6X)
                        if ((DSP1 == testParams->cpuID) &&
                            (dspCore == 1U))
                        {
                            totalTCRun++;
                            UARTConfigPrintf(uartBaseAddr, "\n|TEST START|:: %u ::\n", testParams->testcaseId);
                            UARTConfigPrintf(uartBaseAddr, "|TEST PARAM|:: %s ::\n", testParams->testCaseName);
                            UARTConfigPrintf(uartBaseAddr, "|SR|:: %s ::\n", testParams->reqId);

                            UARTConfigPrintf(uartBaseAddr, "Testcase Settings:\n");
                            UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
                            UARTConfigPrintf(uartBaseAddr, "Module                                              :0x%x\n",
                                   testParams->mcanConfigParams.mcanModule);
                            UARTConfigPrintf(uartBaseAddr, "=========================RUNNING==============================\n");
                            testParams->testResult = App_mcanPerfTxTest(testParams);
                            testParams->isRun      = STW_SOK;
                            UARTConfigPrintf(uartBaseAddr, "\n======================FINISHED==========================\n");
                            if (testParams->testResult == STW_SOK)
                                UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
                            else
                                UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

                            UARTConfigPrintf(uartBaseAddr, "|TEST INFO|:: %s ::\n", testParams->testCaseName);
                            UARTConfigPrintf(uartBaseAddr, "|TEST END|:: %u ::\n", testParams->testcaseId);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
                        if ((DSP2 == testParams->cpuID) &&
                            (dspCore == 2U))
                        {
                            totalTCRun++;
                            UARTConfigPrintf(uartBaseAddr, "\n|TEST START|:: %u ::\n", testParams->testcaseId);
                            UARTConfigPrintf(uartBaseAddr, "|TEST PARAM|:: %s ::\n", testParams->testCaseName);
                            UARTConfigPrintf(uartBaseAddr, "|SR|:: %s ::\n", testParams->reqId);

                            UARTConfigPrintf(uartBaseAddr, "Testcase Settings:\n");
                            UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
                            UARTConfigPrintf(uartBaseAddr, "Module                                              :0x%x\n",
                                   testParams->mcanConfigParams.mcanModule);
                            UARTConfigPrintf(uartBaseAddr, "=========================RUNNING==============================\n");
                            testParams->testResult = App_mcanPerfTxTest(testParams);
                            testParams->isRun      = STW_SOK;
                            UARTConfigPrintf(uartBaseAddr, "\n======================FINISHED==========================\n");
                            if (testParams->testResult == STW_SOK)
                                UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
                            else
                                UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

                            UARTConfigPrintf(uartBaseAddr, "|TEST INFO|:: %s ::\n", testParams->testCaseName);
                            UARTConfigPrintf(uartBaseAddr, "|TEST END|:: %u ::\n", testParams->testcaseId);

                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
#endif
                    }
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%u/%u\n", totalTCRun,
                       (MCAN_NUM_TESTCASES - 1));
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%u\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%u\n", numTCFail);
                st_mcanPrintTCResults();
            break;
            case '6':
                done = 1;
                testcaseIdx = mcanGetTestcaseIdx(13U);
                if (testcaseIdx < 0)
                {
                    UARTConfigPrintf(uartBaseAddr, "Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gmcanTestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gmcanTestcaseParams[testcaseIdx];
                    #ifdef __TI_ARM_V7M4__
                    if (IPU == testParams->cpuID)
                    {
                        totalTCRun++;
                        mcanRunTestcase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                    #elif defined (_TMS320C6X)
                    if ((DSP1 == testParams->cpuID) &&
                        (dspCore == 1U))
                    {
                        totalTCRun++;
                        mcanRunTestcase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                    if ((DSP2 == testParams->cpuID) &&
                        (dspCore == 2U))
                    {
                        totalTCRun++;
                        mcanRunTestcase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                #endif
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%u/%u\n", totalTCRun,
                       MCAN_NUM_TESTCASES);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%u\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%u\n", numTCFail);
            break;
            case '7':
                done = 1;
                testcaseIdx = mcanGetTestcaseIdx(13U);
                if (testcaseIdx < 0)
                {
                    UARTConfigPrintf(uartBaseAddr, "Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gmcanTestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gmcanTestcaseParams[testcaseIdx];
                    #ifdef __TI_ARM_V7M4__
                    if (IPU == testParams->cpuID)
                    {
                        st_mcanDMARxApp(testParams);
                    }
                    #elif defined (_TMS320C6X)
                    if ((DSP1 == testParams->cpuID) &&
                        (dspCore == 1U))
                    {
                        st_mcanDMARxApp(testParams);
                    }
                    if ((DSP2 == testParams->cpuID) &&
                        (dspCore == 2U))
                    {
                        st_mcanDMARxApp(testParams);
                    }
                #endif
                }
                UARTConfigPrintf(uartBaseAddr, "\nmcan: Total Testcases run:%u/%u\n", totalTCRun,
                       MCAN_NUM_TESTCASES);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Passed:%u\n", numTCPass);
                UARTConfigPrintf(uartBaseAddr, "mcan: Number of Testcases Failed:%u\n", numTCFail);
            break;
            case 'd':
                st_mcanPrintTCs();
            break;
            case 'r':
                st_mcanRxApp_main();
            break;
            case 'p':
                st_mcanPerfRxApp_main();
            break;
            case 't':
                UARTConfigPrintf(uartBaseAddr, "\nEnter testcase ID: ");
                scanf("%d", &testIp);
                testcaseIdx = mcanGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    UARTConfigPrintf(uartBaseAddr, "Invalid test case Id.");
                }
                else
                {
                    st_mcanPrintTCDetails(testcaseIdx);
                }
                break;
            case 'g':
                st_mcanPrintTCResults();
            break;
            case 'q':
                UARTConfigPrintf(uartBaseAddr, "Exiting mcan UT.\n");
                done = 1;
            break;
        }
    }

    if(0U == numTCFail)
    {
        UARTConfigPrintf(uartBaseAddr, "\nAll Test-cases have PASSED.\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "\nSome of the Test-cases have FAILED.\n");
    }
    /*for(testcaseId = 1; testcaseId <= MCAN_NUM_TESTCASES ; testcaseId++)
     * {
     *  testcaseIdx = mcanGetTestcaseIdx(testcaseId);
     *  if(testcaseIdx < 0)
     *  {
     *      UARTConfigPrintf(uartBaseAddr, "Invalid test case Id.");
     *  }
     *  else
     *  {
     *      testParams = &gmcanTestcaseParams[testcaseIdx];
     *      mcanRunTestcase(testParams);
     *  }
     * }*/
    return 0;
}

int32_t mcanGetTestcaseIdx(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const st_mcanTestcaseParams_t *testParams;

    testParams = &gmcanTestcaseParams[0u];
    for (testCnt = 1; testCnt < MCAN_NUM_TESTCASES; testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}

void mcanRunTestcase(st_mcanTestcaseParams_t *testParams)
{
    UARTConfigPrintf(uartBaseAddr, "\n|TEST START|:: %u ::\n", testParams->testcaseId);
    UARTConfigPrintf(uartBaseAddr, "|TEST PARAM|:: %s ::\n", testParams->testCaseName);
    UARTConfigPrintf(uartBaseAddr, "|SR|:: %s ::\n", testParams->reqId);

    UARTConfigPrintf(uartBaseAddr, "Testcase Settings:\n");
    UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
    UARTConfigPrintf(uartBaseAddr, "Module                                              :0x%x\n",
           testParams->mcanConfigParams.mcanModule);
    UARTConfigPrintf(uartBaseAddr, "=========================RUNNING==============================\n");
    st_mcanTxApp_main(testParams);
    testParams->isRun      = STW_SOK;
    UARTConfigPrintf(uartBaseAddr, "\n======================FINISHED==========================\n");
    if (testParams->testResult == STW_SOK)
        UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
    else
        UARTConfigPrintf(uartBaseAddr, "|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

    UARTConfigPrintf(uartBaseAddr, "|TEST INFO|:: %s ::\n", testParams->testCaseName);
    UARTConfigPrintf(uartBaseAddr, "|TEST END|:: %u ::\n", testParams->testcaseId);
}

void st_mcanShowMainMenu(void)
{
    UARTConfigPrintf(uartBaseAddr, "\n=============\n");
    UARTConfigPrintf(uartBaseAddr, "mcan UT Select\n");
    UARTConfigPrintf(uartBaseAddr, "=============\n");
    st_mcanPrintSettings(0);
    UARTConfigPrintf(uartBaseAddr, "\nMCAN UT main menu:\n");
    UARTConfigPrintf(uartBaseAddr, "1: Manual testing (select specific test case to run)\n");
    UARTConfigPrintf(uartBaseAddr, "2. Sanity testing.\n");
    UARTConfigPrintf(uartBaseAddr, "3: Regression testing.\n");
    UARTConfigPrintf(uartBaseAddr, "4: Full testing.\n");
    UARTConfigPrintf(uartBaseAddr, "5: Performance testing.\n");
    UARTConfigPrintf(uartBaseAddr, "6: DMA Tx Application.\n");
    UARTConfigPrintf(uartBaseAddr, "7: DMA Rx Application.\n");
    UARTConfigPrintf(uartBaseAddr, "r: Receiver Side Application.\n");
    UARTConfigPrintf(uartBaseAddr, "p: Performance Receiver Side Application.\n");
    UARTConfigPrintf(uartBaseAddr, "d: Display test cases.\n");
    UARTConfigPrintf(uartBaseAddr, "t: Display test case Details.\n");
    UARTConfigPrintf(uartBaseAddr, "g: Generate test report.\n");
    UARTConfigPrintf(uartBaseAddr, "s: System Settings.\n");
    UARTConfigPrintf(uartBaseAddr, "q: Quit.\n");
}

void st_mcanPrintSettings(uint32_t tcIdx)
{
    st_mcanTestcaseParams_t *testParams;

    testParams = &gmcanTestcaseParams[tcIdx];
    if (tcIdx == 0U)
    {
        UARTConfigPrintf(uartBaseAddr, "Current System Settings:\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "Testcase Settings:\n");
    }
    UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
    UARTConfigPrintf(uartBaseAddr, "Module                                              :0x%x\n",
           testParams->mcanConfigParams.mcanModule);
}

void st_mcanPrintTCs(void)
{
    uint32_t loopCnt;
    const st_mcanTestcaseParams_t *testParams;

    UARTConfigPrintf(uartBaseAddr, "mcan Testcase:\n");
    UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
    UARTConfigPrintf(uartBaseAddr, "TC Id\tTC name\n");
    UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
    for (loopCnt = 1; loopCnt < MCAN_NUM_TESTCASES; loopCnt++)
    {
        testParams = &gmcanTestcaseParams[loopCnt];
        UARTConfigPrintf(uartBaseAddr, "%d\t%s\n", testParams->testcaseId, testParams->testCaseName);
    }
    UARTConfigPrintf(uartBaseAddr, "--------------------------------------------------------------\n");
}

void st_mcanPrintTCDetails(uint32_t testId)
{
    const st_mcanTestcaseParams_t *testParams;

    testParams = &gmcanTestcaseParams[testId];
    UARTConfigPrintf(uartBaseAddr, "Testcase Id : %d\n", testParams->testcaseId);
    UARTConfigPrintf(uartBaseAddr, "Testcase Name : %s", testParams->testCaseName);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase Enabled(0-Disabled/1-Enabled) : %d",
           testParams->enableTest);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase Req. Id : %s", testParams->reqId);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase User Info. : %s", testParams->userInfo);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase Disable Reason : %s", testParams->disableReason);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase CPU ID : %d", testParams->cpuID);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase Type : %d", testParams->testType);
    UARTConfigPrintf(uartBaseAddr, "\nTestcase Print Enable(0-Disabled/1-Enabled) : %d\n",
           testParams->printEnable);
}

void st_mcanTCResultInit(void)
{
    uint32_t loopCnt;
    st_mcanTestcaseParams_t *testParams;

    for (loopCnt = 1; loopCnt < MCAN_NUM_TESTCASES; loopCnt++)
    {
        testParams             = &gmcanTestcaseParams[loopCnt];
        testParams->isRun      = STW_EFAIL;
        testParams->testResult = STW_EFAIL;
    }
}

void st_mcanPrintTCStats(void)
{}

void st_mcanPrintTCResults(void)
{
    uint32_t loopCnt, testCnt = 1;
    int32_t  testcaseIdx;
    st_mcanTestcaseParams_t *testParams;
    char    *testResult;
#if !(defined (AVV_TEST_AUTO_BUILD))
    char *testType, *adequacy, *passFailCriteria;
#endif

    UARTConfigPrintf(uartBaseAddr,
        "-----------------------------------------------------------------------------------------------------------\r\n");
    UARTConfigPrintf(uartBaseAddr,
        "ID\t         Description\t\t\t                         Status\r\n");
    UARTConfigPrintf(uartBaseAddr,
        "-----------------------------------------------------------------------------------------------------------\r\n");
    for (loopCnt = 1; loopCnt < MCAN_NUM_TESTCASES; loopCnt++)
    {
        testParams = &gmcanTestcaseParams[loopCnt];
        testcaseIdx = testParams->testcaseId;
        if (STW_SOK == testParams->testResult)
        {
            testResult = "PASS";
        }
        else if (STW_SOK == testParams->isRun)
        {
            testResult = "FAIL";
        }
        else
        {
            testResult = "NRY";
        }
        UARTConfigPrintf(uartBaseAddr,
            "%d\t         %s\t                         %s\r\n",
            testcaseIdx, testParams->testCaseName, testResult);
    }

            UARTConfigPrintf(uartBaseAddr,
        "\n-----------------------------------------------------------------------------------------------------------\r\n");
#if !(defined (AVV_TEST_AUTO_BUILD))
    UARTConfigPrintf(uartBaseAddr, "S.No;ID;Requirement Mapping;Description;IR;Category;Test Adequacy;Enable/Disable;Test Result;\r\n");
    UARTConfigPrintf(uartBaseAddr, "------------------------------------------------------------\r\n");
    for (loopCnt = 1; loopCnt < MCAN_NUM_TESTCASES; loopCnt++)
    {
        testParams = &gmcanTestcaseParams[loopCnt];
        testcaseIdx = testParams->testcaseId;
        if (STW_SOK == testParams->testResult)
        {
            testResult = "PASS";
        }
        else if (STW_SOK == testParams->isRun)
        {
            testResult = "FAIL";
        }
        else
        {
            testResult = "NRY";
        }
        switch (testParams->testType)
        {
            case 1:
                testType = "Sanity";
                break;
            case 2:
                testType = "Regression";
                break;
            case 4:
                testType = "Full Testing";
                break;
            case 8:
                testType = "Functional";
                break;
            case 16:
                testType = "Stress";
                break;
            case 32:
                testType = "Negative";
                break;
            case 64:
                testType = "Performance";
                break;
            case 128:
                testType = "Misc.";
                break;
            case 256:
                testType = "API";
                break;
            default:
                testType = "INVALID";
                break;
        }
        if (testParams->testType & ST_TT_STRESS)
        {
            adequacy = "Stress";
        }
        else if (testParams->testType & ST_TT_NEGATIVE)
        {
            adequacy = "Negative";
        }
        else if (testParams->testType & ST_TT_PERFORMANCE)
        {
            adequacy = "Performance";
        }
        else if (testParams->testType & ST_TT_MISC)
        {
            adequacy = "Misc";
        }
        else
        {
            adequacy = "Functional";
        }
        passFailCriteria = testParams->passFailCriteria;
        if (NULL == passFailCriteria)
        {
            passFailCriteria = "";
        }

        UARTConfigPrintf(uartBaseAddr, "%d;ST_MCAN_TC%05d;%s;%s;%s;;%s;%s%s;;\n", testCnt++,
                   testcaseIdx, testParams->reqId, testParams->testCaseName,
                   passFailCriteria, testType, adequacy, testResult);
    }
#endif
}

void st_mcanUARTConfig(void)
{
    /* Do Pad Config for UART */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations- UART  */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /*Pad configurations - MCAN */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RXD,0x0006000C);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_TXD,0x0004000C);
#elif defined (SOC_TDA2PX)
    /*Pad configurations- UART  */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
#endif
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                    UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
    UARTConfigPuts(uartBaseAddr, "\n UART Config Done...\n", -1);
}
