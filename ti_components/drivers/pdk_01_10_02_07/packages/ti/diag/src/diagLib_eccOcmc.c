/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file     diagLib_eccOcmc.c
 * \brief    This file contains internal functions ECC OCMC tests.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <diagLib_eccOcmc.h>
#include <diagLib_utils.h>
/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/**
 * \brief   Base address of OCMC module
 */
#define DIAGLIB_OCMC_RAM_INST_0             (SOC_OCMC_RAM1_CFG_BASE)
/**
 * \brief   Default addresses of EDMA
 */
#define DIAGLIB_EDMA_INST_0                 (SOC_EDMA_TPCC_BASE_VIRT)
#define DIAGLIB_OCMC_RAM_ECC_ERR_THRSH_VAL  (0x1U)
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/* ========================================================================== */
static int32_t ocmcEccConfig(const DiagLib_EccOcmcTestParams_t *testParams,
            DiagLib_EccObj_t *eccObj, uint32_t secAutoCorrectEn,
            uint32_t eccErrIntEn);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t ocmcSecErrTest(const DiagLib_EccOcmcTestParams_t *testParams,
            DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout)
{

    uint32_t *test_Addr    = NULL;
    uint32_t volatile testVal;
    uint32_t secAutoCorrectEn = 1U;
    uint32_t eccErrIntEn  = 0U;
    int32_t status = STW_SOK;
    uint32_t timeStart, elapsedTime = 0U;

    status = ocmcEccConfig(testParams, eccObj, (uint32_t) TRUE,
        (uint32_t) FALSE);

    if (status == STW_SOK)
    {
        eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
        OCMCIntEnable(DIAGLIB_OCMC_RAM_INST_0, 0, OCMC_ECC_SEC_ERROR_FOUND);
        /*Configure ERR count to trigger an interrupt*/
        OCMCEccErrTraceConfig(DIAGLIB_OCMC_RAM_INST_0,
                              DIAGLIB_OCMC_RAM_ECC_ERR_THRSH_VAL,
                              0U, 0U, 0U);

        /* Disable ECC and read data from the addr
        * Toggle a single bit and write it back */
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_NON_ECC_DATA_ACCESS,
                                        0U, 0U, 0U);

        test_Addr    = (uint32_t *) testParams->eccOcmcRamErrAddr;
        testVal      = *test_Addr;
        testVal      = testVal ^ 0x00010000U;
        *test_Addr = testVal;

        /* Enable ECC and read back from the address */
        if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
        {
            /*Configure OCMC to Full ECC mode*/
            OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_FULL_ECC_ENABLE,
                          secAutoCorrectEn, eccErrIntEn, 0U);
        }
        else if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK)
        {
            /*Configure OCMC to block ECC mode*/
            OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_BLOCK_ECC_ENABLE,
                          secAutoCorrectEn, eccErrIntEn, 0U);

            /*Enable 0 block*/
            OCMCRAMBlockEnableCtrl(DIAGLIB_OCMC_RAM_INST_0, 1U, 0U);
        }
        else
        {
            status = STW_EINVALID_PARAMS;
        }

        if (status == STW_SOK)
        {
            testVal = *test_Addr;

            if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
            {
                status = eccObj->testState;
            }
            else if (errChkMode == DIAGLIB_ECC_POLLED_MODE)
            {
                timeStart = DiagLibUtils_getCurTimeInMsec();
                /* Wait for the raw interrupt status to be set */
                do
                {
                    /* Get the time elapsed from the start of polling */
                    elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);

                    if (OCMCIntStatusRawGet(DIAGLIB_OCMC_RAM_INST_0, 0U,
                                        OCMC_ECC_SEC_ERROR_FOUND) != 0U)
                    {
                        break;
                    }
                }
                while(elapsedTime <= timeout);

                if(elapsedTime <= timeout)
                {
                    ocmcSecISR(testParams, eccObj);
                }
                else
                {
                    eccObj->testState = DIAGLIB_ECC_TEST_TIMEOUT;
                }

            }
            else
            {
                eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
                status = STW_EINVALID_PARAMS;
            }
        }
        else
        {
            eccObj->testState = status;
        }
    }
    else
    {
        eccObj->testState = status;
    }
    return status;
}

int32_t ocmcDedErrTest(const DiagLib_EccOcmcTestParams_t *testParams,
                            DiagLib_EccObj_t *eccObj, uint32_t errChkMode)
{

    uint32_t *test_Addr    = NULL;
    uint32_t volatile testVal;
    uint32_t secAutoCorrectEn = 0U;
    uint32_t eccErrIntEn  = 0U;
    uint32_t nonEccReadEn = 0U;
    int32_t status = STW_SOK;

    status = ocmcEccConfig(testParams, eccObj, (uint32_t) FALSE,
        (uint32_t) FALSE);
    if (status == STW_SOK)
    {
        eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
        OCMCIntEnable(DIAGLIB_OCMC_RAM_INST_0, 0U, OCMC_ECC_DED_ERROR_FOUND);
        /*Configure ERR count to trigger an interrupt*/
        OCMCEccErrTraceConfig(DIAGLIB_OCMC_RAM_INST_0,
                              0U, DIAGLIB_OCMC_RAM_ECC_ERR_THRSH_VAL,
                              0U, 0U);

        /* Disable ECC and read data from the addr
        * Toggle 2 bits and write it back */
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_NON_ECC_DATA_ACCESS,
                                            0U, 0U, 0U);

        test_Addr    = (uint32_t *) testParams->eccOcmcRamErrAddr;
        testVal      = *test_Addr;
        eccObj->eccTestVal = testVal;
        testVal      = testVal ^ 0x00030000U;
        *test_Addr = testVal;

        /* Enable ECC and read back from the address */
        if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
        {
            /*Configure OCMC to Full ECC mode*/
            OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_FULL_ECC_ENABLE,
                          secAutoCorrectEn, eccErrIntEn, nonEccReadEn);
        }
        else if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK)
        {
            /*Configure OCMC to block ECC mode*/
            OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_BLOCK_ECC_ENABLE,
                          secAutoCorrectEn, eccErrIntEn, nonEccReadEn);

            /*Enable 0 block*/
            OCMCRAMBlockEnableCtrl(DIAGLIB_OCMC_RAM_INST_0, 1U, 0U);
        }
        else
        {
            status = STW_EINVALID_PARAMS;
        }

        /* Read the memory to trigger interrupt */
        HW_RD_REG32(test_Addr);

        if (status == STW_SOK)
        {
            testVal = *test_Addr;

            status = eccObj->testState;
        }
        else
        {
            eccObj->testState = status;
        }
    }
    else
    {
        eccObj->testState = status;
    }
    return status;
}

int32_t ocmcAddrErrTest(const DiagLib_EccOcmcTestParams_t *testParams,
                            DiagLib_EccObj_t *eccObj, uint32_t errChkMode)
{

    uint32_t *test_Addr    = NULL;
    uint32_t volatile testVal;
    uint32_t secAutoCorrectEn = 0U;
    uint32_t eccErrIntEn  = 0U;
    uint32_t nonEccReadEn = 0U;
    int32_t status = STW_SOK;

    status = ocmcEccConfig(testParams, eccObj, (uint32_t) FALSE,
        (uint32_t) TRUE);
    if (status == STW_SOK)
    {
       eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
        OCMCIntEnable(DIAGLIB_OCMC_RAM_INST_0, 0U, OCMC_ECC_ADDR_ERROR_FOUND);
        /*Configure ERR count to trigger an interrupt*/
        OCMCEccErrTraceConfig(DIAGLIB_OCMC_RAM_INST_0,
                              0U, 0U, DIAGLIB_OCMC_RAM_ECC_ERR_THRSH_VAL,
                              0U);

        /* Disable ECC for addresses and read code from the addr
        * Manipulate the code and write back */
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_NON_ECC_CODE_ACCESS,
                                            0U, 0U, 0U);

        test_Addr    = (uint32_t *) testParams->eccOcmcRamErrAddr;
        eccObj->eccTestVal =  *(uint32_t *) test_Addr;

        /* Address err: This Modifies Bit 0 0f ECC bits */
        testVal       = eccObj->eccTestVal ^ 0x112U;
        *(uint32_t *) test_Addr = testVal;

        /* Enable ECC and read back from the address */
        if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
        {
            /*Configure OCMC to Full ECC mode*/
            OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_FULL_ECC_ENABLE,
                         secAutoCorrectEn, eccErrIntEn, nonEccReadEn);
        }
        else if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK)
        {
            /*Configure OCMC to block ECC mode*/
            OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_BLOCK_ECC_ENABLE,
                        secAutoCorrectEn, eccErrIntEn, nonEccReadEn);

            /*Enable 0 block*/
            OCMCRAMBlockEnableCtrl(DIAGLIB_OCMC_RAM_INST_0, 1U, 0U);
        }
        else
        {
            status = STW_EINVALID_PARAMS;
        }

        /* Read the memory to trigger interrupt */
		HW_RD_REG32(test_Addr);

        if (status == STW_SOK)
        {
            testVal    = *(uint32_t *) test_Addr;

            status = eccObj->testState;
        }
        else
        {
            eccObj->testState = status;
        }
    }
    else
    {
        eccObj->testState = status;
    }

    return status;

}

void ocmcSecISR(const DiagLib_EccOcmcTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj)
{

    uint32_t i;
    uint32_t test_Addr = NULL;
    uint32_t eccErrAddr = 0U;
    uint32_t eccErrBitMask[4] = {0};

    /* Initialize the errBitMask to 0 */
    for (i = 0U; i < 4U; i++)
    {
        eccErrBitMask[i] = 0U;
    }
    /* Get the Err Trace for SEC error */
    test_Addr = testParams->eccOcmcRamErrAddr;
    eccErrAddr = OCMCEccErrTraceAddrGet(DIAGLIB_OCMC_RAM_INST_0,
                                         OCMC_ECC_SEC_ERR);

    eccErrBitMask[0] = OCMCSecEccErrDistributionStatusGet(
        DIAGLIB_OCMC_RAM_INST_0,
        OCMC_ECC_SEC_ERR_DIST_0);
    eccErrBitMask[1] = OCMCSecEccErrDistributionStatusGet(
        DIAGLIB_OCMC_RAM_INST_0,
        OCMC_ECC_SEC_ERR_DIST_1);
    eccErrBitMask[2] = OCMCSecEccErrDistributionStatusGet(
        DIAGLIB_OCMC_RAM_INST_0,
        OCMC_ECC_SEC_ERR_DIST_2);
    eccErrBitMask[3] = OCMCSecEccErrDistributionStatusGet(
        DIAGLIB_OCMC_RAM_INST_0,
        OCMC_ECC_SEC_ERR_DIST_3);

    OCMCEccErrClearTraceHist(DIAGLIB_OCMC_RAM_INST_0,
                             OCMC_CLEAR_SEC_ERROR_HIST |
                             OCMC_CLEAR_SEC_BIT_DIST_HIST);

    OCMCIntStatusEnableClear(DIAGLIB_OCMC_RAM_INST_0,
                             0U,
                             OCMC_ECC_SEC_ERROR_FOUND);
    OCMCIntDisable(DIAGLIB_OCMC_RAM_INST_0, 0U, OCMC_INTERRUPT_ALL);

    /* Compare the error address with the test address */
    for (i = 0; i < 4U; i++)
    {
        if (eccErrBitMask[i])
        {
            if (((eccErrAddr << 4U) + DIAGLIB_OCMC_RAM_START_ADDR + (i*4U))
                                                                == test_Addr)
            {
                eccObj->testState = DIAGLIB_ECC_TEST_PASS;
            }
            else
            {
                eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
                break;
            }
        }
    }
    if (eccObj->testState != DIAGLIB_ECC_TEST_PASS)
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}

void ocmcDedISR(const DiagLib_EccOcmcTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj)
{

    uint32_t *test_Addr = NULL;
    uint32_t eccErrAddr = 0U;

    /* Get the Err Trace for DED error */
    eccErrAddr = OCMCEccErrTraceAddrGet(DIAGLIB_OCMC_RAM_INST_0,
                                         OCMC_ECC_DED_ERR);

    OCMCEccErrClearTraceHist(DIAGLIB_OCMC_RAM_INST_0,
                             OCMC_CLEAR_DED_ERROR_HIST);

    OCMCIntStatusEnableClear(DIAGLIB_OCMC_RAM_INST_0, 0U,
                             OCMC_ECC_DED_ERROR_FOUND);

    /* Disable ECC and write back the original value before intorducing
     * DED err since DED error is not self-corrected */
    OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_NON_ECC_DATA_ACCESS, 0U, 0U, 0U);

    test_Addr    = (uint32_t *) testParams->eccOcmcRamErrAddr;
    test_Addr[0] = eccObj->eccTestVal;

    if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_FULL_ECC_ENABLE, 0U, 1U, 0U);
    }
    else if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_BLOCK_ECC_ENABLE, 0U, 1U, 0U);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(DIAGLIB_OCMC_RAM_INST_0, 1U, 0U);
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
    }
    OCMCIntDisable(DIAGLIB_OCMC_RAM_INST_0, 0U, OCMC_INTERRUPT_ALL);

    if (eccObj->testState != DIAGLIB_ECC_TEST_INVALID_PARAMS)
    {
        /* Compare the error address offset with the test address */
        if (((eccErrAddr << 4U) + DIAGLIB_OCMC_RAM_START_ADDR) ==
                        (testParams->eccOcmcRamErrAddr & 0xFFFFFFF0U))
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
}

void ocmcAddrISR(const DiagLib_EccOcmcTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj)
{

    uint32_t *test_Addr = NULL;
    uint32_t eccErrAddr = 0U;

    /* Get the Err Trace for DED error */
    eccErrAddr = OCMCEccErrTraceAddrGet(DIAGLIB_OCMC_RAM_INST_0,
                                         OCMC_ECC_ADDR_ERR);

    OCMCEccErrClearTraceHist(DIAGLIB_OCMC_RAM_INST_0,
                             OCMC_CLEAR_ADDR_ERROR_HIST);

    OCMCIntStatusEnableClear(DIAGLIB_OCMC_RAM_INST_0, 0U,
                             OCMC_ECC_ADDR_ERROR_FOUND);

    /* Disable ECC for code and write back the original value before
     * intorducing DED err since DED error is not self-corrected */
    OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_NON_ECC_CODE_ACCESS, 0U, 0U, 0U);

    test_Addr    = (uint32_t *) testParams->eccOcmcRamErrAddr;
    test_Addr[0] = eccObj->eccTestVal;

    if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_FULL_ECC_ENABLE, 0U, 1U, 0U);
    }
    else if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_BLOCK_ECC_ENABLE, 0U, 1U, 0U);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(DIAGLIB_OCMC_RAM_INST_0, 1U, 0U);
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
    }
    OCMCIntDisable(DIAGLIB_OCMC_RAM_INST_0, 0U, OCMC_INTERRUPT_ALL);

    if (eccObj->testState != DIAGLIB_ECC_TEST_INVALID_PARAMS)
    {
        /* Compare the error address offset with the test address */
        if (((eccErrAddr << 4U) + DIAGLIB_OCMC_RAM_START_ADDR) ==
                                (testParams->eccOcmcRamErrAddr& 0xFFFFFFF0U))
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
}
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t ocmcEccConfig(const DiagLib_EccOcmcTestParams_t *testParams,
            DiagLib_EccObj_t *eccObj, uint32_t secAutoCorrectEn,
            uint32_t eccErrIntEn)
{
    int32_t retVal = STW_SOK;
    uint32_t *test_Addr = NULL;
    uint32_t testVal[4];
    uint32_t i, j = 0U;
    uint32_t tempAddr;

    EDMA3CCPaRAMEntry edmaParam;
    uint16_t aCnt = 16U;
    uint16_t bCnt = 1U;
    uint16_t cCnt = 1U;


    OCMCSoftReset(DIAGLIB_OCMC_RAM_INST_0);

    /* Disable ECC and read the data from the test address */
    OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_NON_ECC_DATA_ACCESS,
                                        0U, 0U, 0U);
    tempAddr = testParams->eccOcmcRamErrAddr;
    test_Addr = (uint32_t *) tempAddr;

    for (i = tempAddr; i < (tempAddr+ 0x10U); i += 4U)
    {
        testVal[j] = test_Addr[j];
        j++;
    }

    /* Enable ECC and initialize the address with the read data */
    if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0U);
    }
    else if (testParams->eccOcmcMode == DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(DIAGLIB_OCMC_RAM_INST_0, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0U);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(DIAGLIB_OCMC_RAM_INST_0, 1U, 0U);
    }
    else
    {
        retVal = STW_EINVALID_PARAMS;
    }

    /* EDMA is used for writing the data since ECC calculation is for 128bits
     * and writing 32 bits at once results in a different ECC value than
     * intended */

    EDMA3RequestChannel(DIAGLIB_EDMA_INST_0, EDMA3_CHANNEL_TYPE_DMA,
            testParams->eccOcmcEdmaChNum, testParams->eccOcmcEdmaTccNum,
            testParams->eccOcmcEdmaEvtqNum);

    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t)testVal;
    edmaParam.destAddr = tempAddr;
    edmaParam.aCnt     = aCnt;
    edmaParam.bCnt     = bCnt;
    edmaParam.cCnt     = cCnt;
    edmaParam.srcBIdx  = (int16_t)aCnt;
    edmaParam.destBIdx = (int16_t)aCnt;
    edmaParam.srcCIdx  = (int16_t)aCnt;
    edmaParam.destCIdx = (int16_t)aCnt;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |= EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
            ((testParams->eccOcmcEdmaTccNum << EDMA3_OPT_TCC_SHIFT) &
             EDMA3_OPT_TCC_MASK);

    EDMA3SetPaRAM(DIAGLIB_EDMA_INST_0, testParams->eccOcmcEdmaChNum, &edmaParam);

    /*
     * Transfer is done in a sync mode
     */
        EDMA3EnableTransfer(DIAGLIB_EDMA_INST_0, testParams->eccOcmcEdmaChNum,
                                                    EDMA3_TRIG_MODE_MANUAL);

        while (0U == (EDMA3GetIntrStatus(DIAGLIB_EDMA_INST_0) &
                    ((uint32_t) 1U << testParams->eccOcmcEdmaChNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(DIAGLIB_EDMA_INST_0, testParams->eccOcmcEdmaChNum);
    OCMCEccErrClearTraceHist(DIAGLIB_OCMC_RAM_INST_0, 0xFU);

    OCMCIntStatusEnableClear(DIAGLIB_OCMC_RAM_INST_0, 0U, 0x7U);
    return retVal;
}
