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
 * \file     diagLib_eccIpu.c
 * \brief    This file contains internal functions ECC IPU L1 & L2 tests.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/arch/csl_arch.h>


#include <diagLib_eccIpu.h>
/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/**
 * \brief   Base address of IPU module
 */
#define DIAGLIB_IPU_INST_0                  (SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE)
#define DIAGLIB_IPU_L1TAG_SEC_ERR_INT               (80U)
#define DIAGLIB_IPU_L1TAG_DED_ERR_INT               (81U)
#define DIAGLIB_IPU_L1DATA_SEC_ERR_INT              (82U)
#define DIAGLIB_IPU_L1DATA_DED_ERR_INT              (83U)
#define DIAGLIB_IPU_L2RAM_SEC_ERR_INT               (84U)
#define DIAGLIB_IPU_L2RAM_DED_ERR_INT               (85U)
#define DIAGLIB_IPU_L1DATA_ECC_START_ADDR           (0x90000000U)
#define DIAGLIB_IPU_L1DATA_ECC_END_ADDR             (0x90008000U)
#define PATTERN_DATA                                (0xFFFFFFFFU)
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/* ========================================================================== */
static void ipuEccConfig(uint32_t memType, uint32_t *testAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t ipuL2RamErrTest(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t errType)
{
    int32_t status = STW_SOK;
    uint8_t volatile *test_Addr = NULL;
    uint8_t volatile testVal;
    eccIpuMemCfgPrm_t cfgPrm;
    uint32_t i;

    /* Set the ECC IPU configuration depending on errType */
    if ((DIAGLIB_IPU_ECC_ERR_SEC == errType) || (DIAGLIB_IPU_ECC_ERR_CODE == errType))
    {
        cfgPrm.errAutoCorrectEnable = (uint32_t)TRUE;
        cfgPrm.sRespHFEnable        = (uint32_t)FALSE;
    }
    else
    {
        cfgPrm.errAutoCorrectEnable = (uint32_t)FALSE;
        cfgPrm.sRespHFEnable        = (uint32_t)TRUE;
    }

    cfgPrm.dataMask       = (uint32_t)FALSE;
    cfgPrm.eccCodeMask    = (uint32_t)TRUE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L2RAM;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
    /* Intialize eccObj values */
    for (i = 0; i < DIAGLIB_ECC_L2RAM_BYTES; i++)
    {
        eccObj->eccL2RamTestVal[i] = 0x00U;
    }

    /* Do the memory initialization */
    ipuEccConfig(ECC_IPU_MEM_TYPE_L2RAM, (uint32_t *)testParams->eccIpuRamErrAddr);
    ECCIPUMemConfig(DIAGLIB_IPU_INST_0, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    test_Addr = (uint8_t *) testParams->eccIpuRamErrAddr;

    /* Modify the testVal by introducing single bit error */
    testVal          = test_Addr[0];

    /* Store the original value before modifying */
    for (i = 0; i < DIAGLIB_ECC_L2RAM_BYTES; i++)
    {
        eccObj->eccL2RamTestVal[i] = test_Addr[i];
    }

    /* Bit modification depending on errType */
    if (DIAGLIB_IPU_ECC_ERR_SEC == errType)
    {
        /* For SEC test, any random 1-bit may be flipped */
        testVal = testVal ^ 0x10U;
    }
    else if (DIAGLIB_IPU_ECC_ERR_CODE == errType)
    {
        /* This generates 3 bit err in data and 1 bit err in ECC code
         * as per logic.
         * Bit 0,1 & 2 are toggled.
         * So Code Error + SEC Error Occurs when we do a read after ECC Enabled
         * This means Error in ECC Code ( Code Error) and
         * 1 bit Error in ECC code ( SEC Error)
         */
        testVal = testVal ^ 0x07U;
    }
    else
    {
        /* For DED test, any random 2-bits may be flipped */
        testVal = testVal ^ 0x30U;
    }

    *test_Addr = testVal;

    /* Read back the address where single bit error was introduced */
    testVal = *test_Addr;

    status = eccObj->testState;
    return status;
}

int32_t ipuL1DataErrTest(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t errType)
{
    int32_t status = STW_SOK;
    uint32_t volatile *test_Addr = NULL;
    uint32_t volatile testVal;
    uint32_t byteCount;
    eccIpuMemCfgPrm_t cfgPrm;

    if ((DIAGLIB_IPU_ECC_ERR_SEC == errType) || (DIAGLIB_IPU_ECC_ERR_CODE == errType))
    {
        cfgPrm.errAutoCorrectEnable = (uint32_t)TRUE;
        cfgPrm.sRespHFEnable        = (uint32_t)FALSE;
    }
    else
    {
        cfgPrm.errAutoCorrectEnable = (uint32_t)FALSE;
        cfgPrm.sRespHFEnable        = (uint32_t)TRUE;
    }

    cfgPrm.dataMask       = (uint32_t)FALSE;
    cfgPrm.eccCodeMask    = (uint32_t)TRUE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1DATA;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
    test_Addr = (uint32_t *) testParams->eccIpuRamErrAddr;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1DATA, NULL);
    ECCIPUMemConfig(DIAGLIB_IPU_INST_0, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    testVal          = test_Addr[0];

    /* Modify the testVal for introducing ECC error */
    if (DIAGLIB_IPU_ECC_ERR_SEC == errType)
    {
        /* For SEC test, any random 1-bit may be flipped */
        testVal          = testVal & 0xFFFEFFFFU;
    }
    else if (DIAGLIB_IPU_ECC_ERR_CODE == errType)
    {
        /* This generates 3 bit err in data and 1 bit err in ECC code as per
         * logic testVal is 0xFFFFFFF8 instead of 0xFFFFFFFF
         * So Code Error + SEC Error Occurs when we do a read after ECC Enabled
         * This means Error in ECC Code ( Code Error) and
         * 1 bit Error in ECC code ( SEC Error)
         */
        testVal          = testVal & 0xFFFFFFF8U;
    }
    else
    {
        /* DED Error - Any random 2-bits can be flipped */
        testVal          = testVal & 0xFFFCFFFFU;
    }

    *test_Addr = testVal;

    /* Read back the address where single bit error was introduced */
    testVal = *test_Addr;

    byteCount =
        DIAGLIB_IPU_L1DATA_ECC_END_ADDR - DIAGLIB_IPU_L1DATA_ECC_START_ADDR;
    UNICACHEInvalidate(DIAGLIB_IPU_INST_0, DIAGLIB_IPU_L1DATA_ECC_START_ADDR,
                        byteCount, UNICACHE_WAIT_INFINITE);
    status = eccObj->testState;
    return status;
}

int32_t ipuL1TagErrTest(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t errType)
{
    int32_t status = STW_SOK;
    uint32_t *test_Addr = NULL;
    uint32_t volatile testVal;
    eccIpuMemCfgPrm_t cfgPrm;
    uint32_t byteCount;

    if ((DIAGLIB_IPU_ECC_ERR_SEC == errType) || (DIAGLIB_IPU_ECC_ERR_CODE == errType))
    {
        cfgPrm.errAutoCorrectEnable = (uint32_t)TRUE;
    }
    else
    {
        cfgPrm.errAutoCorrectEnable = (uint32_t)FALSE;
    }
    cfgPrm.sRespHFEnable        = (uint32_t)FALSE;
    cfgPrm.dataMask       = (uint32_t)FALSE;
    cfgPrm.eccCodeMask    = (uint32_t)FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1TAG;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
    test_Addr = (uint32_t *) testParams->eccIpuRamErrAddr;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1TAG, NULL);
    ECCIPUMemConfig(DIAGLIB_IPU_INST_0, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    /* Flush the cache & Invalidate all cache line*/
    UNICACHEInvalidateAll(DIAGLIB_IPU_INST_0, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll.
     * This ensures cache contains exactly 1 valid entry */
    testVal = *(volatile uint32_t *) test_Addr;

    /* Disable ECC for L1TAG */
    ECCIPUMemEnableEcc(DIAGLIB_IPU_INST_0, (uint32_t) FALSE,
        ECC_IPU_MEM_TYPE_L1TAG);

    /* dirty bit for all cache line is set as 0 */
    UNICACHEInvalidateAll(DIAGLIB_IPU_INST_0, UNICACHE_WAIT_INFINITE);

    if(errType == DIAGLIB_IPU_ECC_ERR_SEC)
    {
        /* To introduce one bit error in Tag Address: Addr[31:13]
         * Read the data from 0x90002000 instead of 0x90000000
         */
        testVal = *(volatile uint32_t *) (test_Addr + 0x2000U);
    }
    else if(errType == DIAGLIB_IPU_ECC_ERR_CODE)
    {
        /* To introduce code error in Tag Address: Addr[31:13]
         * Read the data from 0x9000E000 instead of 0x90000000
         */
        testVal = *(volatile uint32_t *) (test_Addr + 0xE000U);
    }
    else
    {
        /* To introduce two bit error in Tag Address: Addr[31:13]
         * Read the data from 0x90006000 instead of 0x90000000
         */
        testVal = *(volatile uint32_t *) (test_Addr + 0x6000U);
    }


    ECCIPUMemEnableEcc(DIAGLIB_IPU_INST_0, (uint32_t) TRUE,
        ECC_IPU_MEM_TYPE_L1TAG);
    testVal = *(volatile uint32_t *) test_Addr;

    byteCount =
        DIAGLIB_IPU_L1DATA_ECC_END_ADDR - DIAGLIB_IPU_L1DATA_ECC_START_ADDR;
    UNICACHEInvalidate(DIAGLIB_IPU_INST_0, DIAGLIB_IPU_L1DATA_ECC_START_ADDR,
                        byteCount, UNICACHE_WAIT_INFINITE);
    status = eccObj->testState;
    return status;
}

void ipuL2RamSecErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus;
    uint32_t errAddr = 0x0U;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                        ECC_IPU_MEM_TYPE_L2RAM);

    /* Check if the correct errStatus has occurred */
    if (ECC_IPU_ERR_ONEBIT == (errStatus & ECC_IPU_ERR_ONEBIT))
    {
        ECCIPUMemGetErrInfo(DIAGLIB_IPU_INST_0, &errAddr,
                                                ECC_IPU_MEM_TYPE_L2RAM);

        if (errAddr == (testParams->eccIpuRamErrAddr & 0xFFFFFFF0U))
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
        ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0, errStatus,
                                        ECC_IPU_MEM_TYPE_L2RAM);
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}

void ipuL2RamDedErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus, i;
    eccIpuMemCfgPrm_t cfgPrm;
    uint32_t errAddr = 0x0U;
    uint8_t *test_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = (uint32_t)FALSE;
    cfgPrm.sRespHFEnable        = (uint32_t)TRUE;
    cfgPrm.dataMask       = (uint32_t)FALSE;
    cfgPrm.eccCodeMask    = (uint32_t)FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L2RAM;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                        ECC_IPU_MEM_TYPE_L2RAM);
    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0, errStatus,
                                                ECC_IPU_MEM_TYPE_L2RAM);

    /* Check if the correct errStatus has occurred */
    if(ECC_IPU_ERR_TWOBIT == (errStatus & ECC_IPU_ERR_TWOBIT))
    {
        ECCIPUMemGetErrInfo(DIAGLIB_IPU_INST_0, &errAddr,
                                                    ECC_IPU_MEM_TYPE_L2RAM);
        /* Restore the original value */
        ECCIPUMemConfig(DIAGLIB_IPU_INST_0, (const eccIpuMemCfgPrm_t *) &cfgPrm);

        test_Addr = (uint8_t *) testParams->eccIpuRamErrAddr;
        for (i = 0; i < DIAGLIB_ECC_L2RAM_BYTES; i++)
        {
            test_Addr[i] = eccObj->eccL2RamTestVal[i];
        }

        if (errAddr == (testParams->eccIpuRamErrAddr & 0xFFFFFFF0U))
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}

void ipuL2RamCodeErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus, i;
    eccIpuMemCfgPrm_t cfgPrm;
    uint32_t errAddr = 0x0U;
    uint8_t *test_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = (uint32_t)TRUE;
    cfgPrm.sRespHFEnable        = (uint32_t)FALSE;
    cfgPrm.dataMask       = (uint32_t)FALSE;
    cfgPrm.eccCodeMask    = (uint32_t)FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L2RAM;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                        ECC_IPU_MEM_TYPE_L2RAM);
    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0, errStatus,
                            ECC_IPU_MEM_TYPE_L2RAM);

    /* Check if the correct errStatus has occurred */
    if ((ECC_IPU_ERR_CODE == (errStatus & ECC_IPU_ERR_CODE)) &&
        (ECC_IPU_ERR_ONEBIT == (errStatus & ECC_IPU_ERR_ONEBIT)))
    {
        ECCIPUMemGetErrInfo(DIAGLIB_IPU_INST_0, &errAddr,
                                                ECC_IPU_MEM_TYPE_L2RAM);
        /* Restore the original value */
        ECCIPUMemConfig(DIAGLIB_IPU_INST_0, (const eccIpuMemCfgPrm_t *) &cfgPrm);

        test_Addr = (uint8_t *) testParams->eccIpuRamErrAddr;
        for (i = 0; i < DIAGLIB_ECC_L2RAM_BYTES; i++)
        {
            test_Addr[i] = eccObj->eccL2RamTestVal[i];
        }
        if (errAddr == (testParams->eccIpuRamErrAddr & 0xFFFFFFF0U))
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}

void ipuL1DataSecOrCodeErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus;
    uint32_t errAddr = 0x0U;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                    ECC_IPU_MEM_TYPE_L1DATA);
    /* Check if the correct errStatus has occurred */
    if (ECC_IPU_ERR_ONEBIT == (errStatus & ECC_IPU_ERR_ONEBIT))
    {
        ECCIPUMemGetErrInfo(DIAGLIB_IPU_INST_0, &errAddr,
                                                ECC_IPU_MEM_TYPE_L1DATA);
        ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0,
                              errStatus,
                              ECC_IPU_MEM_TYPE_L1DATA);

        if (errAddr == testParams->eccIpuRamErrAddr)
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }

}

void ipuL1DataDedErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus;
    uint32_t *test_Addr = NULL;
    eccIpuMemCfgPrm_t cfgPrm;
    uint32_t errAddr = 0x0U;

    cfgPrm.errAutoCorrectEnable = (uint32_t)FALSE;
    cfgPrm.sRespHFEnable        = (uint32_t)TRUE;
    cfgPrm.dataMask       = (uint32_t)FALSE;
    cfgPrm.eccCodeMask    = (uint32_t)FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1DATA;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                    ECC_IPU_MEM_TYPE_L1DATA);
    if (ECC_IPU_ERR_TWOBIT == (errStatus & ECC_IPU_ERR_TWOBIT))
    {
        ECCIPUMemGetErrInfo(DIAGLIB_IPU_INST_0, &errAddr,
                                                ECC_IPU_MEM_TYPE_L1DATA);

        ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0, ECC_IPU_ERR_TWOBIT,
                                                ECC_IPU_MEM_TYPE_L1DATA);
        ECCIPUMemConfig(DIAGLIB_IPU_INST_0, (const eccIpuMemCfgPrm_t *) &cfgPrm);

        test_Addr = (uint32_t *) errAddr;
        test_Addr[0] = PATTERN_DATA;

        if (errAddr == testParams->eccIpuRamErrAddr)
        {
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}

void ipuL1TagSecOrCodeErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                    ECC_IPU_MEM_TYPE_L1TAG);
    if (ECC_IPU_ERR_ONEBIT == (errStatus & ECC_IPU_ERR_ONEBIT))
    {
        UNICACHEInvalidateCacheLine(DIAGLIB_IPU_INST_0,
                                testParams->eccIpuRamErrAddr);
        UNICACHEPreloadCacheLine(DIAGLIB_IPU_INST_0,
                                testParams->eccIpuRamErrAddr);
        UNICACHEWaitCacheMaint(DIAGLIB_IPU_INST_0, UNICACHE_WAIT_INFINITE);
        eccObj->testState = DIAGLIB_ECC_TEST_PASS;
    }
    else if (ECC_IPU_ERR_CODE == (errStatus & ECC_IPU_ERR_CODE))
    {
        UNICACHEInvalidateCacheLine(DIAGLIB_IPU_INST_0,
                                testParams->eccIpuRamErrAddr + 0xE000U);
        UNICACHEPreloadCacheLine(DIAGLIB_IPU_INST_0,
                                testParams->eccIpuRamErrAddr + 0xE000U);
        UNICACHEWaitCacheMaint(DIAGLIB_IPU_INST_0, UNICACHE_WAIT_INFINITE);
        eccObj->testState = DIAGLIB_ECC_TEST_PASS;
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0,
                          errStatus,
                          ECC_IPU_MEM_TYPE_L1TAG);
}

void ipuL1TagDedErrISR(const DiagLib_EccIpuTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj)
{
    uint32_t errStatus;

    errStatus = ECCIPUMemGetErrStatus(DIAGLIB_IPU_INST_0,
                                    ECC_IPU_MEM_TYPE_L1TAG);
    if (ECC_IPU_ERR_TWOBIT == (errStatus & ECC_IPU_ERR_TWOBIT))
    {
        UNICACHEInvalidateCacheLine(DIAGLIB_IPU_INST_0,
                                testParams->eccIpuRamErrAddr + 0x6000U);
        UNICACHEPreloadCacheLine(DIAGLIB_IPU_INST_0,
                                testParams->eccIpuRamErrAddr + 0x6000U);
        UNICACHEWaitCacheMaint(DIAGLIB_IPU_INST_0, UNICACHE_WAIT_INFINITE);
        eccObj->testState = DIAGLIB_ECC_TEST_PASS;
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0,
                          errStatus,
                          ECC_IPU_MEM_TYPE_L1TAG);
}
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void ipuEccConfig(uint32_t memType, uint32_t *testAddr)
{
    uint32_t i, j = 0U;
    uint32_t testVal[2] = {0x00U, 0x00U};
    uint32_t tempAddr = (uint32_t)testAddr;

    /* Disable ECC for IPU L2RAM / L1DATA / L1TAG */
    ECCIPUMemEnableEcc(DIAGLIB_IPU_INST_0, (uint32_t) FALSE,
        ECC_IPU_MEM_TYPE_L2RAM);
    ECCIPUMemEnableEcc(DIAGLIB_IPU_INST_0, (uint32_t) FALSE,
        ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(DIAGLIB_IPU_INST_0, (uint32_t) FALSE,
        ECC_IPU_MEM_TYPE_L1TAG);

    /* Disable Cache to access L2 RAM directly */
    UNICACHEDisable(DIAGLIB_IPU_INST_0);

    Intc_IntDisable();

    /* Read an entire line, 256bits of existing data from L2 RAM */
    if (memType == ECC_IPU_MEM_TYPE_L2RAM)
    {

        for (i = tempAddr; i < (tempAddr + 0x8U); i += 4U)
        {
            testVal[j] = testAddr[j];
            j++;
        }
    }
    else
    {
        UNICACHEEnable(DIAGLIB_IPU_INST_0);
    }

    /* Enable ECC for IPU L2RAM / L1DATA / L1TAG */
    ECCIPUMemEnableEcc(DIAGLIB_IPU_INST_0, (uint32_t) TRUE, memType);

    j = 0U;
    if ((memType == ECC_IPU_MEM_TYPE_L1DATA) ||
                        (memType == ECC_IPU_MEM_TYPE_L1TAG))
    {
        for (i = DIAGLIB_IPU_L1DATA_ECC_START_ADDR;
                                i < DIAGLIB_IPU_L1DATA_ECC_END_ADDR; i += 4U)
        {
            *(uint32_t *) i = PATTERN_DATA;
        }
    }
    /* Initialize the read data back into L2 RAM */
    else
    {
        for (i = tempAddr; i < (tempAddr + 0x8U); i += 4U)
        {
            testAddr[j] = testVal[j];
            j++;
        }
    }

    /* Clear IPU L2RAM/ L1DATA / L1TAG ECC Err status which is caused during
     * intialisation*/
    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1DATA);

    ECCIPUMemClrErrStatus(DIAGLIB_IPU_INST_0,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);

    /* Clear Pending Interrupts of IPU L2RAM/ L1DATA / L1TAG ECC Erors which is
     * caused during cache intialisation*/
    Intc_IntClrPend(DIAGLIB_IPU_L2RAM_SEC_ERR_INT);
    Intc_IntClrPend(DIAGLIB_IPU_L2RAM_DED_ERR_INT);
    Intc_IntClrPend(DIAGLIB_IPU_L1DATA_SEC_ERR_INT);
    Intc_IntClrPend(DIAGLIB_IPU_L1DATA_DED_ERR_INT);
    Intc_IntClrPend(DIAGLIB_IPU_L1TAG_SEC_ERR_INT);
    Intc_IntClrPend(DIAGLIB_IPU_L1TAG_DED_ERR_INT);

    Intc_IntEnable(0);
}
