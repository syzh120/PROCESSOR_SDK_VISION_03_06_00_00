/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file st_qspiNegativeTestCase.c
 *
 *  \brief QSPI UT for Negative test case
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_qspiCommon.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t gStQspiDataPtrCheck = 0;
extern QSPI_FlashDevInfo_t gStQspiFlashDevInfo;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void st_qspiTest_RdNullDataCheck(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;

    retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Init fails \r\n");
    }

    if(retVal == STW_SOK)
    {
        QSPISetMAddrSpace(
            SOC_QSPI_ADDRSP0_BASE,
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace(
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

        gStQspiFlashDevInfo.readCmd.numDataWords = 1;
        gStQspiFlashDevInfo.readCmd.addr = testCfg.offsetAddr;

        gStQspiDataPtrCheck = 1;

        retVal = st_qspiTest_executeCmd(gStQspiFlashDevInfo.readCmd, NULL);

        gStQspiDataPtrCheck = 0;

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Read fails \r\n");
        }
    }

    st_qspiTest_deInitFlash();

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Test Pass for Null Data Read\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Quick Flash Test Fail for Null Data Read\r\n");
        testPrms->testResult = STW_EFAIL;
    }
}

void st_qspiTest_WrNullDataCheck(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;

    retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Init fails \r\n");
    }

    if(retVal == STW_SOK)
    {
        QSPI_WriteEnable();

        QSPISetMAddrSpace(
            SOC_QSPI_ADDRSP0_BASE,
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace(
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

        gStQspiFlashDevInfo.writeCmd.numDataWords = 1;
        gStQspiFlashDevInfo.writeCmd.addr = testCfg.offsetAddr;

        gStQspiDataPtrCheck = 1;

        st_qspiTest_executeCmd(gStQspiFlashDevInfo.writeCmd, NULL);

        gStQspiDataPtrCheck = 0;

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Write fails \r\n");
        }
    }

    st_qspiTest_deInitFlash();

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash DeInit Fails \r\n");
    }

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Test Pass for Null Data Write\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Flash Test Fail for Null Data Write\r\n");
        testPrms->testResult = STW_EFAIL;
    }
}

void st_qspiTest_RdCorruptionCheckFor16BitData(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;
    int32_t loopCnt;

    for(loopCnt = 0U; loopCnt < testPrms->loopCnt; loopCnt++)
    {
        if ((testPrms->testType & ST_TT_STRESS) == ST_TT_STRESS)
        {
            printf("\r\n QSPI Flash Stress Test - %d \r\n", loopCnt);
        }

        retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Init fails \r\n");
        }
        else
        {
            printf("QSPI Flash Init Complete \r\n");
        }

        if(loopCnt == 0)
        {
            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_eraseFlash(testCfg.eraseType,
                                                testCfg.eraseBlockNo,
                                                testCfg.eraseSectorNo);
                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Erase fails \r\n");
                }
            }

            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_writeRandomTestPattern();

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Write Test Pattern fails \r\n");
                }
            }

            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_writeFlash(testCfg.flashSize,
                                                testCfg.dataWidth,
                                                testCfg.offsetAddr);

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Write fails \r\n");
                }
                else
                {
                    printf("QSPI Write to Flash Complete \r\n");
                }
            }
        }

        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_readFlashWithCheck(testCfg.flashSize,
                                                    testCfg.dataWidth,
                                                    testCfg.enableReadMemMapMode,
                                                    testCfg.offsetAddr,
                                                    testCfg.dataTransferMode);

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash Read fails \r\n");
            }
            else
            {
                printf("QSPI Read from Flash Complete \r\n");
            }
        }


        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_verifyFlashData(testCfg.flashSize,
                                                 testCfg.enableReadMemMapMode);

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash Data Mismatch \r\n");
            }
        }

        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_deInitFlash();

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash DeInit Fails \r\n");
            }
            else
            {
                printf("QSPI Flash DeInit Complete \r\n");
            }
        }
    }

    if(retVal == STW_SOK)
    {
        printf("QSPI Quick Flash Test Pass\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Quick Flash Test Fail\r\n");
        testPrms->testResult = STW_EFAIL;
    }

}
