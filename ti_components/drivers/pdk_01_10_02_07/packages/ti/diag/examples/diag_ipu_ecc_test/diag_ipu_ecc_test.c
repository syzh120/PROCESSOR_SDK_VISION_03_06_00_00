/*
 *  Copyright (c) Texas Instruments Incorporated 2015-2017
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
 *  \file     diag_ipu_ecc_test.c
 *
 *  \brief    This file contains IPU ECC test code for diagLib.
 *            This example is for IPU.
 *
 *  \details  ECC functionality is tested for various modules.
 *
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/example/utils/common/inc/app_utils.h>
#include <ti/diag/diagLib_ecc.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/**
 *  \brief Macros for IPU definitions.
 */

#define DIAGLIB_APP_IPU_INST_0          (SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE)

#define IPU_L2RAM_SEC_ERR_INT             (84U)
#define IPU_L2RAM_DED_ERR_INT             (85U)
#define IPU_L1DATA_SEC_ERR_INT            (82U)
#define IPU_L1DATA_DED_ERR_INT            (83U)
#define IPU_L1TAG_SEC_ERR_INT             (80U)
#define IPU_L1TAG_DED_ERR_INT             (81U)

#define DIAGLIB_APP_DDRM4_ADDR              (0x84000000U)
#define DIAGLIB_APP_DDRM4_ADDR1             (0x84040000U)
#define DIAGLIB_IPU_L2RAM_ECC_TEST_ADDR     (0x55024020U)
#define DIAGLIB_IPU_L2RAM_ECC_TEST_ADDR1    (0x55024030U)
#define DIAGLIB_IPU_L1DATA_ECC_TEST_ADDR    (0x90000014U)
#define DIAGLIB_IPU_L1DATA_ECC_TEST_ADDR1   (0x90000024U)
#define DIAGLIB_IPU_L1TAG_ECC_TEST_ADDR     (0x90000000U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*To use UARTConfigPuts function for prints*/
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

static volatile DiagLib_EccTestParams_t gEccTestParams;
static volatile DiagLib_EccObj_t        gEccObj;
static volatile int32_t gTestStatus;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void ipuAMMUSetPolicy(void);
static void isrECC(void *handle);
static void eccEnableIntr(uint32_t intrNum, uint32_t enable);
static int32_t eccTestStart(DiagLib_EccTestParams_t *testParams,
                            DiagLib_EccObj_t        *eccObj);
static int32_t ipuEccTest(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
    AppUtils_setUartConsolePinMux();
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
}

int main(void)
{
    int32_t retVal = STW_SOK;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    ipuAMMUSetPolicy();
    DiagLibEccTestParams_init((DiagLib_EccTestParams_t *) &(gEccTestParams));

    retVal = ipuEccTest();
    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t ipuEccTest(void)
{
    int32_t retVal = STW_SOK;

    gEccTestParams.eccErrCheckMode = DIAGLIB_ECC_INTERRUPT_MODE;

    UNICACHEWriteBackAndInvalidateAll(DIAGLIB_APP_IPU_INST_0,
                                      UNICACHE_WAIT_INFINITE);
    UNICACHEEnable(DIAGLIB_APP_IPU_INST_0);

    eccEnableIntr(IPU_L2RAM_SEC_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L2RAM_SEC;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L2RAM_ECC_TEST_ADDR;

    /* IPU L2 RAM SEC Err Test */
    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L2 RAM SEC Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L2 RAM SEC Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L2RAM_SEC_ERR_INT, FALSE);

    /* DED Error will generate hard fault. Register the interrupt handler
     * for HF interrupt insted of DED ERR INT */
    eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L2RAM_DED;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L2RAM_ECC_TEST_ADDR1;

    /* IPU L2 RAM DED Err Test */
    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L2 RAM DED Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L2 RAM DED Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, FALSE);

    eccEnableIntr(IPU_L2RAM_SEC_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L2RAM_CODE;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L2RAM_ECC_TEST_ADDR;

    /* IPU L2 RAM ECC Code Err Test */
    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L2 RAM ECC Code Err Test interrupt mode successful\r\n",
                 -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L2 RAM ECC Code Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L2RAM_SEC_ERR_INT, FALSE);

    /* IPU L1 Data SEC Err Test */
    eccEnableIntr(IPU_L1DATA_SEC_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L1DATA_SEC;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L1DATA_ECC_TEST_ADDR;

    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 Data SEC Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 Data SEC Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L1DATA_SEC_ERR_INT, FALSE);

    /* DED Error will generate hard fault. Register the interrupt handler
     * for HF interrupt insted of DED ERR INT */
    eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L1DATA_DED;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L1DATA_ECC_TEST_ADDR1;

    /* IPU L1 Data DED Err Test */
    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 Data DED Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 Data DED Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, FALSE);

    /* IPU L1 ECC Code Err Test */
    eccEnableIntr(IPU_L1DATA_SEC_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L1DATA_CODE;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L1DATA_ECC_TEST_ADDR;

    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 DATA ECC Code Err Test interrupt mode successful\r\n",
                 -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 DATA ECC Code Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L1DATA_SEC_ERR_INT, FALSE);

    /* IPU L1 Tag SEC Err Test */
    eccEnableIntr(IPU_L1TAG_SEC_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L1TAG_SEC;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L1TAG_ECC_TEST_ADDR;

    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 TAG SEC Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 TAG SEC Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L1TAG_SEC_ERR_INT, FALSE);

    /* IPU L1 Tag DED Err Test */
    eccEnableIntr(IPU_L1TAG_DED_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L1TAG_DED;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L1TAG_ECC_TEST_ADDR;

    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 TAG DED Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 TAG DED Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L1TAG_DED_ERR_INT, FALSE);

    /* IPU L1 Tag Code Err Test */
    eccEnableIntr(IPU_L1TAG_SEC_ERR_INT, TRUE);
    gEccTestParams.testType = DIAGLIB_ECC_TEST_IPU_L1TAG_CODE;
    gEccTestParams.ipuPrm.eccIpuRamErrAddr = DIAGLIB_IPU_L1TAG_ECC_TEST_ADDR;

    retVal = eccTestStart((DiagLib_EccTestParams_t *) &gEccTestParams,
                          (DiagLib_EccObj_t *) &gEccObj);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 TAG Code Err Test interrupt mode successful\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"IPU L1 TAG Code Err test interrupt mode failed\r\n", -1);
    }
    eccEnableIntr(IPU_L1TAG_SEC_ERR_INT, FALSE);

    return retVal;
}

static void ipuAMMUSetPolicy(void)
{
    ammuPolicyRegParams_t pagePolicyParams = {0U};
    ammuPageConfig_t      pageConfig       = {0U};
    uint32_t policyReg;

    /* Set Policy Params for medium page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize   = AMMU_PAGE_SIZE_256KB;
    policyReg = AMMUMakePolicyReg(&pagePolicyParams);

    /* medium page mapping: P.A. 0x84000000U V.A. 0x84000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.ammuPageNum     = 0U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = DIAGLIB_APP_DDRM4_ADDR;
    pageConfig.logicalAddress  = DIAGLIB_APP_DDRM4_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = DIAGLIB_APP_DDRM4_ADDR1;
    pageConfig.logicalAddress  = DIAGLIB_APP_DDRM4_ADDR1;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* Set Policy Params for small page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    policyReg = AMMUMakePolicyReg(&pagePolicyParams);

    /* small page mapping: P.A. 0x90000000U V.A. 0x90000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 2U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x90000000U;
    pageConfig.logicalAddress  = 0x90000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* small page mapping: P.A. 0x90004000U V.A. 0x90004000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 3U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x90004000U;
    pageConfig.logicalAddress  = 0x90004000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* small page mapping: P.A. 0x90008000U V.A. 0x90008000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 4U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x90008000U;
    pageConfig.logicalAddress  = 0x90008000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
}

static int32_t eccTestStart(DiagLib_EccTestParams_t *testParams,
                            DiagLib_EccObj_t        *eccObj)
{
    int32_t retVal;

    gTestStatus = DiagLib_eccStartTest(testParams, eccObj);

    while (gTestStatus == DIAGLIB_ECC_TEST_PENDING)
    {}

    retVal = gTestStatus;
    return retVal;
}

static void isrECC(void *handle)
{
    gTestStatus = DiagLib_eccISR((DiagLib_EccTestParams_t *) &gEccTestParams,
                                 (DiagLib_EccObj_t *) &gEccObj);
}

static void eccEnableIntr(uint32_t intrNum, uint32_t enable)
{
    if (TRUE == enable)
    {
        /* Enable the given interrupt */
        Intc_Init();
        Intc_IntEnable(0);

        Intc_IntRegister(intrNum, (IntrFuncPtr) isrECC, NULL);

        Intc_IntPrioritySet(intrNum, 1, 0);
        Intc_SystemEnable(intrNum);
    }
    else
    {
        /* Disable the interrupt */
        Intc_SystemDisable(intrNum);

        /* Unregister the interrupt */
        Intc_IntUnregister(intrNum);

        Intc_IntDisable();
    }
}
