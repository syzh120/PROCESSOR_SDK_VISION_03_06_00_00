/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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

/*
 * main_ipu.c
 */
#include <stdio.h>
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_ocmc_ecc.h>
#include <ti/csl/csl_emif.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#if defined (SOC_AM574x)
#include <ti/osal/osal.h>
#include <ti/board/board.h>
#endif

#include "ecc_emif.h"
#include "ecc_ocmc.h"

/* ----------------- Constant definitions ----------------- */

/* The following statements define Menu options */
#define EMIF_ECC_TEST                  ('1')
#define OCMC_RAM_ECC_TEST              ('2')

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define IPU_ECC_TEST                   ('3')

#define IPU_L2RAM_SEC_ERR_TEST         ('1')
#define IPU_L2RAM_DED_ERR_TEST         ('2')
#define IPU_L2RAM_CODE_ERR_TEST        ('3')
#define IPU_L1DATA_SEC_ERR_TEST        ('4')
#define IPU_L1DATA_DED_ERR_TEST        ('5')
#define IPU_L1DATA_CODE_ERR_TEST       ('6')
#define IPU_L1TAG_SEC_ERR_TEST         ('7')
#define IPU_L1TAG_DED_ERR_TEST         ('8')
#define IPU_L1TAG_CODE_ERR_TEST        ('9')
#endif

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#ifndef SOC_IPU1_UNICACHE_MMU_BASE
#define SOC_IPU1_UNICACHE_MMU_BASE CSL_MPU_IPU1_TARGET_UNICACHE_MMU_REGS
#endif
#define IPU_APP_INST                      (CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS)

/** \brief IPU instance used */
#define IPU_L2RAM_ECC_START_ADDR                (0x55020000)
#define IPU_L2RAM_ECC_END_ADDR                  (0x55030000)

#define IPU_L1DATA_ECC_START_ADDR               (0x90000000)
#define IPU_L1DATA_ECC_END_ADDR                 (0x90010000)

#define IPU_L2RAM_SEC_ERR_INT             (84U)
#define IPU_L2RAM_DED_ERR_INT             (85U)
#define IPU_L1DATA_SEC_ERR_INT            (82U)
#define IPU_L1DATA_DED_ERR_INT            (83U)
#define IPU_L1TAG_SEC_ERR_INT             (80U)
#define IPU_L1TAG_DED_ERR_INT             (81U)

#define IPU_L2RAM_ECC_TEST_ADDR               (0x55024015)
#define IPU_L2RAM_ECC_TEST_ADDR1              (0x55024025)
#define IPU_L1DATA_ECC_TEST_ADDR              (0x90000014)
#define IPU_L1DATA_ECC_TEST_ADDR2             (0x90000024)
#define IPU_L1TAG_ECC_TEST_ADDR               (0x90000000)
#define IPU_L1TAG_SEC_ERR_TEST_ADDR           (0x90002000)
#define IPU_L1TAG_DED_ERR_TEST_ADDR           (0x90006000)
#define IPU_L1TAG_CODE_ERR_TEST_ADDR          (0x9000E000)

#define IPU_UNICACHE_SIZE                     (0x10000)
#define IPU_RAM_BASE_ADDR                     (0x00000000)

#define IPU_VECTOR_TABLE_SIZE             (NUM_ELEMENTS_VECTOR_TABLE * 4U)
#define IPU_VECTOR_TABLE_ADDRESS          (0x55020000U)
#define IPU_TARGET_VECTOR_TABLE_ADDRESS   (0x40300000U)
#endif

#define L2RAM_PATTERN_DATA                (0xFF)

#define HARD_FAULT_INT                   (EXCEPTION_M4_HARD_FAULT_NUM_3)

/* ------------------------------------------------------- */

/* ----------------- Function prototypes ----------------- */

static void mainMenu(char *option);

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
static void ammuConfigIPUEcc(void);
static void mainSubMenuIpuEccTest(char *option);
int32_t ipuEccTest(void);
static int32_t ipuL2RamSecErrTest(char option);
static int32_t ipuL2RamDedErrTest(char option);
static int32_t ipuL2RamCodeErrTest(char option);
static int32_t ipuL1DataSecErrTest(char option);
static int32_t ipuL1DataDedErrTest(char option);
static int32_t ipuL1DataCodeErrTest(char option);
static int32_t ipuL1TagSecErrTest(char option);
static int32_t ipuL1TagDedErrTest(char option);
static int32_t ipuL1TagCodeErrTest(char option);

static void ipuEccConfig(uint32_t memType);
static void ipuEccInit();
void isrIpuL2RamSecErr();
void isrIpuL2RamDedErr();
void isrIpuL1DataSecErr();
void isrIpuL1DataDedErr();
void isrIpuL1TagSecErr();
void isrIpuL1TagDedErr();

uint32_t gIpuErrAddr;
#endif

/* --------------------------------------------------- */

/* ----------------- Global variables ----------------- */

volatile uint32_t  gErrStatus = 0;

uint32_t           gInterruptNum = HARD_FAULT_INT;

extern void CPUDisableCPSRABit(void);

volatile uint32_t *gTest_Addr    = NULL;
volatile uint32_t *gTest_Addr1   = NULL;
volatile uint8_t  *gIpuTest_Addr = NULL;
volatile uint32_t  gTestVal      = 0;
volatile uint32_t  gEvictStat    = 0;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif
#if defined (SOC_AM574x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif
/* --------------------------------------------------- */

/* The main code here initializes the platform and processes
 * commands through UART port.
 * The menu commands are hierarchical and starts with the main menu with
 * the class of tests. The test classes include OCMC ecc test, EMIF ecc test
 * and DSP ECC test.
 * The OCMC err test & EMIF err test functions are in thier respective
 * separate c files and are used by all cores.
 * Once the class of tests are selected, then the submenu options for
 * the chosen class, are processed.
 */
int main(void)
{
    int32_t           retVal   = STW_SOK;
    char mainMenuOption;
#if defined (SOC_AM574x)
    /* Initialize board */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO |
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif

    /* Do main command line processing */
    while (1)
    {
        mainMenu(&mainMenuOption);

        if (EMIF_ECC_TEST == mainMenuOption)
        {
            /* Handle emif ECC test menu */
            retVal = emifEccTest();
        }
        else if (OCMC_RAM_ECC_TEST == mainMenuOption)
        {
            /* Handle ocmc ECC test menu */
            retVal = ocmcRamEccTest();
        }
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        else if (IPU_ECC_TEST == mainMenuOption)
        {
            /* Handle ipu ECC test menu */
            retVal = ipuEccTest();
        }
#endif
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\n  ECC test exiting...", -1);
            break;
        }
    };
    return retVal;
}

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/* Do IPU ecc test specific command processing */
int32_t ipuEccTest(void)
{
    int32_t retVal = STW_SOK;
    char    mainSubMenuOption;

    while (1)
    {
        mainSubMenuIpuEccTest(&mainSubMenuOption);

        ipuEccInit();

        if (IPU_L2RAM_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL2RamSecErrTest(mainSubMenuOption);
        }
        else if (IPU_L2RAM_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL2RamDedErrTest(mainSubMenuOption);
        }
        else if (IPU_L2RAM_CODE_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL2RamCodeErrTest(mainSubMenuOption);
        }
        else if (IPU_L1DATA_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1DataSecErrTest(mainSubMenuOption);
        }
        else if (IPU_L1DATA_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1DataDedErrTest(mainSubMenuOption);
        }
        else if (IPU_L1DATA_CODE_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1DataCodeErrTest(mainSubMenuOption);
        }
        else if (IPU_L1TAG_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1TagSecErrTest(mainSubMenuOption);
        }
        else if (IPU_L1TAG_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1TagDedErrTest(mainSubMenuOption);
        }
        else if (IPU_L1TAG_CODE_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1TagCodeErrTest(mainSubMenuOption);
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\n IPU ECC test exiting...", -1);
            break;
        }
    }
    return retVal;
}

#endif

/* The following routine handles main menu options*/
static void mainMenu(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. EMIF ECC TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. OCMC RAM ECC TEST", -1);
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        UARTConfigPuts(uartBaseAddr, "\r\n3. IPU L2RAM ECC TEST", -1);
#endif
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (EMIF_ECC_TEST == *option ||
            OCMC_RAM_ECC_TEST == *option ||
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
            IPU_ECC_TEST == *option ||
#endif
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nEnter Valid option\r\n", -1);
        }
    }
}

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/* Configures AMMU configuration for IPU ECC test */
static void ammuConfigIPUEcc(void)
{
    ammuPageConfig_t      pageConfig       = {0U};
    ammuPolicyRegParams_t pagePolicyParams = {0U};
    uint32_t policyReg;
    /* This function configures the MMU to put the app code in non cacheble
     * region, also reconfigure the MMCU and copies the Vector table to 0x40300000
     * address */
    /*
     * Configure medium page for code region
     */
    /* 0th medium page mapping: P.A. 0x84000000 V.A. 0x84000000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_256KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 0;
    pageConfig.logicalAddress        = 0x84000000U;
    pageConfig.physicalAddress       = 0x84000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st medium page mapping: P.A. 0x84040000 V.A. 0x84040000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_256KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 1;
    pageConfig.logicalAddress        = 0x84040000U;
    pageConfig.physicalAddress       = 0x84040000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /*
     * Configure Small pages
     */
    /* 0th small page mapping: P.A. 0x40300000U V.A. 0x00000000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 0;
    pageConfig.logicalAddress        = 0x00000000U;
    pageConfig.physicalAddress       = 0x40300000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd small page mapping: P.A. 0x55020000U V.A. 0x55020000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 2;
    pageConfig.logicalAddress        = 0x55020000U;
    pageConfig.physicalAddress       = 0x55020000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd small page mapping: P.A. 0x55024000U V.A. 0x55024000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 3;
    pageConfig.logicalAddress        = 0x55024000U;
    pageConfig.physicalAddress       = 0x55024000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 4th small page mapping: P.A. 0x55028000U V.A. 0x55028000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 4;
    pageConfig.logicalAddress        = 0x55028000U;
    pageConfig.physicalAddress       = 0x55028000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 5th small page mapping: P.A. 0x90000000U V.A. 0x90000000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 5;
    pageConfig.logicalAddress        = 0x90000000U;
    pageConfig.physicalAddress       = 0x90000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 6th small page mapping: P.A. 0x90004000U V.A. 0x90004000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 6;
    pageConfig.logicalAddress        = 0x90004000U;
    pageConfig.physicalAddress       = 0x90004000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 7th small page mapping: P.A. 0x90008000U V.A. 0x90008000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 7;
    pageConfig.logicalAddress        = 0x90008000U;
    pageConfig.physicalAddress       = 0x90008000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 8th small page mapping: P.A. 0x9000C000U V.A. 0x9000C000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1AllocateWrite = AMMU_L1_ALLOCATE_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x000F0003; */
    pageConfig.ammuPageNum           = 8;
    pageConfig.logicalAddress        = 0x9000C000U;
    pageConfig.physicalAddress       = 0x9000C000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* Copy Vector table to 0x40300000U */
    memcpy((void *)IPU_TARGET_VECTOR_TABLE_ADDRESS ,(void *)IPU_VECTOR_TABLE_ADDRESS ,
            IPU_VECTOR_TABLE_SIZE);
}

/* Function handles options under IPU Submenu
 */
static void mainSubMenuIpuEccTest(char *option)
{
    ammuConfigIPUEcc();
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** IPU ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. IPU L2RAM SEC test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. IPU L2RAM DED test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n3. IPU L2RAM CODE ERROR test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n4. IPU L1DATA SEC test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n5. IPU L1DATA DED test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n6. IPU L1DATA CODE ERROR test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n7. IPU L1TAG SEC test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n8. IPU L1TAG DED test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n9. IPU L1TAG CODE ERROR test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect IPU ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (IPU_L2RAM_SEC_ERR_TEST == *option ||
            IPU_L2RAM_DED_ERR_TEST == *option ||
            IPU_L2RAM_CODE_ERR_TEST == *option ||
            IPU_L1DATA_SEC_ERR_TEST == *option ||
            IPU_L1DATA_DED_ERR_TEST == *option ||
            IPU_L1DATA_CODE_ERR_TEST == *option ||
            IPU_L1TAG_SEC_ERR_TEST == *option ||
            IPU_L1TAG_DED_ERR_TEST == *option ||
            IPU_L1TAG_CODE_ERR_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nEnter Valid option\r\n", -1);
        }
    }
}

/* Interrupt handler for IPU L2 SRAM Single error 
 * Just checks and clears error status as the correction happens
 * automatically
 */
void isrIpuL2RamSecErr()
{
    int32_t retVal = STW_SOK;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L2RAM);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrAddr,
                                     ECC_IPU_MEM_TYPE_L2RAM);
    if (retVal != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n NULL Pointer Detected : gIpuErrAddr", -1);
    }
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          gErrStatus,
                          ECC_IPU_MEM_TYPE_L2RAM);
}

/* Interrupt handler for IPU L2 SRAM Double bit error 
 * This writes back the original pattern to fix error
 * NOTE: In real application this may need to be handled as a serious
 * error based on application needs.
 */
void isrIpuL2RamDedErr()
{
    uint8_t           i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gIpuTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.sRespHFEnable        = TRUE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L2RAM;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L2RAM);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrAddr,
                                     ECC_IPU_MEM_TYPE_L2RAM);
    if (retVal != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n NULL Pointer Detected : gIpuErrAddr", -1);
    }

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          gErrStatus,
                          ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    gIpuTest_Addr = (uint8_t *) (gIpuErrAddr);
    for (i = 0; i < 8; i++)
    {
        gIpuTest_Addr[i] = L2RAM_PATTERN_DATA;
    }

    /* As sys response interrupt is enabled , will not service
     * IPU_L2RAM_DED_ERR_INT */
    Intc_IntClrPend(IPU_L2RAM_DED_ERR_INT);
}

/* ISR handler for IPU L1D Single bit error
 * Just checks and clears error status as the correction happens
 * automatically
 */
void isrIpuL1DataSecErr()
{
    int32_t retVal = STW_SOK;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST,
                                       ECC_IPU_MEM_TYPE_L1DATA);
    /* To store Err info only while reading cache memory
     * but not to store Err info during Evict*/
    if (gEvictStat == 0)
    {
        retVal = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrAddr,
                                     ECC_IPU_MEM_TYPE_L1DATA);
        if (retVal != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\r\n NULL Pointer Detected : gIpuErrAddr", -1);
        }
    }
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          gErrStatus,
                          ECC_IPU_MEM_TYPE_L1DATA);
}

/* Interrupt handler for IPU L1D Double bit error
 * This writes back the original pattern to fix error
 * NOTE: In real application this may need to be handled as a serious
 * error based on application needs.
 */
void isrIpuL1DataDedErr()
{
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.sRespHFEnable        = TRUE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L1DATA;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L1DATA);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrAddr,
                                     ECC_IPU_MEM_TYPE_L1DATA);
    if (retVal != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n NULL Pointer Detected : gIpuErrAddr", -1);
    }

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          gErrStatus,
                          ECC_IPU_MEM_TYPE_L1DATA);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    gTest_Addr    = (uint32_t *) (gIpuErrAddr);
    gTest_Addr[0] = PATTERN_DATA;

    /* As sys response interrupt is enabled , will not service
     * IPU_L1DATA_DED_ERR_INT */
    Intc_IntClrPend(IPU_L1DATA_DED_ERR_INT);
}

/* Interrupt handler for IPU L1Tag single bit error
 * Just checks and clears error status as the correction happens
 * automatically
 */
void isrIpuL1TagSecErr()
{
    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L1TAG);

    if (ECC_IPU_ERR_CODE == (gErrStatus & ECC_IPU_ERR_CODE))
    {
        UNICACHEInvalidateCacheLine(IPU_APP_INST,
                                    IPU_L1TAG_CODE_ERR_TEST_ADDR);

        UNICACHEPreloadCacheLine(IPU_APP_INST,
                                 IPU_L1TAG_CODE_ERR_TEST_ADDR);
    }
    else if (ECC_IPU_ERR_ONEBIT == (gErrStatus & ECC_IPU_ERR_ONEBIT))
    {
        UNICACHEInvalidateCacheLine(IPU_APP_INST,
                                    IPU_L1TAG_ECC_TEST_ADDR);

        UNICACHEPreloadCacheLine(IPU_APP_INST,
                                 IPU_L1TAG_ECC_TEST_ADDR);
    }
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          gErrStatus,
                          ECC_IPU_MEM_TYPE_L1TAG);
}

/* Interrupt handler for IPU L1D Tag Double bit error
 * It checks the error and clear error status
 * NOTE: In real application this may need to be handled as a serious
 * error based on application needs.
 */
void isrIpuL1TagDedErr()
{
    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEInvalidateCacheLine(IPU_APP_INST,
                                IPU_L1TAG_DED_ERR_TEST_ADDR);

    UNICACHEPreloadCacheLine(IPU_APP_INST,
                             IPU_L1TAG_DED_ERR_TEST_ADDR);

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          gErrStatus,
                          ECC_IPU_MEM_TYPE_L1TAG);
}

/* Function to initialize IPU ECC
 */
static void ipuEccInit()
{
    /* Clear older IPU L2RAM ECC Err status */
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L2RAM);

    /* Clear older IPU L1DATA ECC Err status */
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1DATA);

    /* Clear older IPU L1TAG ECC Err status */
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);

    /* Disable ECC for IPU L2RAM */
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L2RAM);

    /* Disable ECC for IPU L1DATA */
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);

    /* Disable ECC for IPU L1TAG */
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);
}

/* Function to configure IPU ECC
 */
static void ipuEccConfig(uint32_t memType)
{
    uint32_t i;

    /* Make sure the Cache is empty before priming */
    UNICACHEWriteBackAll(IPU_APP_INST,
                         UNICACHE_WAIT_INFINITE);
    UNICACHEInvalidateAll(IPU_APP_INST,
                          UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(IPU_APP_INST);
    UNICACHEEnable(IPU_APP_INST);

    /* Enable ECC for IPU L2RAM / L1DATA / L1TAG */
    ECCIPUMemEnableEcc(IPU_APP_INST,
                       TRUE,
                       ECC_IPU_MEM_TYPE_L2RAM);
    ECCIPUMemEnableEcc(IPU_APP_INST,
                       TRUE,
                       ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(IPU_APP_INST,
                       TRUE,
                       ECC_IPU_MEM_TYPE_L1TAG);

    if ((memType == ECC_IPU_MEM_TYPE_L1DATA) ||
        (memType == ECC_IPU_MEM_TYPE_L1TAG))
    {
        /* Prefill the DDR Memory which is cached (64 KB)*/
        for (i = IPU_L1DATA_ECC_START_ADDR; i < IPU_L1DATA_ECC_END_ADDR; i += 4)
        {
            *(uint32_t *) i = PATTERN_DATA;
        }
    }
    else
    {
        /* Prefill the IPU RAM (64 KB)*/
        for (i = IPU_L2RAM_ECC_START_ADDR; i < IPU_L2RAM_ECC_END_ADDR; i += 4)
        {
            *(uint32_t *) i = PATTERN_DATA;
        }
    }

    /* To ensure DDR and L2RAM are written with PATTERN_DATA */
    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Clear IPU L2RAM/ L1DATA / L1TAG ECC Err status which is caused during
     * intialisation*/
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1DATA);

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);

    /* Clear Pending Interrupts of IPU L2RAM/ L1DATA / L1TAG ECC Erors which is
     * caused during cache intialisation*/
    Intc_IntClrPend(IPU_L2RAM_SEC_ERR_INT);
    Intc_IntClrPend(IPU_L2RAM_DED_ERR_INT);
    Intc_IntClrPend(IPU_L1DATA_SEC_ERR_INT);
    Intc_IntClrPend(IPU_L1DATA_DED_ERR_INT);
    Intc_IntClrPend(IPU_L1TAG_SEC_ERR_INT);
    Intc_IntClrPend(IPU_L1TAG_DED_ERR_INT);
}

/* Function performs IPU L2 RAM single bit error test
 * Inserts single bit error and waits for handler to finish
 */
static int32_t ipuL2RamSecErrTest(char option)
{
    uint8_t           testVal, i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus    = 0;
    gIpuTest_Addr = NULL;
    gIpuErrAddr   = 0x0;

    cfgPrm.errAutoCorrectEnable = TRUE;
    cfgPrm.sRespHFEnable        = FALSE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L2RAM;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(IPU_APP_INST);

    /* Enable The L2 RAM SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L2RAM_SEC_ERR_INT, (IntrFuncPtr) isrIpuL2RamSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L2RAM_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L2RAM_SEC_ERR_INT);

    gIpuTest_Addr = (uint8_t *) (IPU_L2RAM_ECC_TEST_ADDR);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L2RAM);

    testVal          = gIpuTest_Addr[0];
    testVal          = testVal & 0xEF;
    gIpuTest_Addr[0] = testVal;

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L2RAM);

    testVal = gIpuTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L2RAM_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L2RAM_SEC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM SEC ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM SEC ERR Test Pass!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM SEC ERR Occured at Address \r\n ", -1);
        for (i = 0; i < 8; i++)
        {
            UARTConfigPutHexNum(uartBaseAddr, gIpuErrAddr + i);
            UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        }
    }

    return retVal;
}

/* Function performs IPU L2 RAM double bit error test
 * Inserts double bit error and waits for handler to finish
 */
static int32_t ipuL2RamDedErrTest(char option)
{
    uint8_t           testVal, i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus    = 0;
    gIpuTest_Addr = NULL;
    gIpuErrAddr   = 0;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.sRespHFEnable        = TRUE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = TRUE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L2RAM;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(IPU_APP_INST);

    Intc_Init();
    Intc_IntEnable(0);

    /* Register The HF interrupt */
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrIpuL2RamDedErr,
                     NULL);

    Intc_SystemEnable(gInterruptNum);

    gIpuTest_Addr = (uint8_t *) (IPU_L2RAM_ECC_TEST_ADDR1);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    testVal          = gIpuTest_Addr[0];
    testVal          = testVal & 0xCF;
    gIpuTest_Addr[0] = testVal;

    testVal = gIpuTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM DED ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM DED ERR Test Pass!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM DED ERR Occured at Address \r\n ", -1);
        for (i = 0; i < 8; i++)
        {
            UARTConfigPutHexNum(uartBaseAddr, gIpuErrAddr + i);
            UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        }
    }

    return retVal;
}

/* Function performs IPU L2 RAM code error test
 * Inserts 3 bit error, which results in 1 bit ECC code error
 * and waits for handler to finish
 */
static int32_t ipuL2RamCodeErrTest(char option)
{
    uint8_t           testVal, i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus    = 0;
    gIpuTest_Addr = NULL;
    gIpuErrAddr   = 0x0;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.sRespHFEnable        = FALSE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L2RAM;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(IPU_APP_INST);

    /* Enable The L2 RAM SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L2RAM_SEC_ERR_INT, (IntrFuncPtr) isrIpuL2RamSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L2RAM_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L2RAM_SEC_ERR_INT);

    gIpuTest_Addr = (uint8_t *) (IPU_L2RAM_ECC_TEST_ADDR);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L2RAM);

    testVal = gIpuTest_Addr[0];

    /* This generates 3 bit err in data and 1 bit err in ECC code as per logic
     * testVal is 0xF8 instead of 0xFF
     * So Code Error + SEC Error Occurs when we do a read after ECC Enabled
     * This means Error in ECC Code ( Code Error) and
     * 1 bit Error in ECC code ( SEC Error)
     */
    testVal          = testVal & 0xF8;
    gIpuTest_Addr[0] = testVal;

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L2RAM);

    testVal = gIpuTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L2RAM_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L2RAM_SEC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM CODE ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM CODE ERR Test Pass!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L2RAM CODE ERR Occured at Address \r\n ", -1);
        for (i = 0; i < 8; i++)
        {
            UARTConfigPutHexNum(uartBaseAddr, gIpuErrAddr + i);
            UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        }
    }
    return retVal;
}

/* Function performs IPU L1D RAM single error test
 * Inserts single bit error and waits for handler to finish
 */
static int32_t ipuL1DataSecErrTest(char option)
{
    uint32_t          testVal;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus  = 0;
    gEvictStat  = 0;
    gTest_Addr  = NULL;
    gIpuErrAddr = 0x0;

    cfgPrm.errAutoCorrectEnable = TRUE;
    cfgPrm.sRespHFEnable        = FALSE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L1DATA;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1DATA);

    /* Enable The L1 DATA SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L1DATA_SEC_ERR_INT, (IntrFuncPtr) isrIpuL1DataSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L1DATA_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L1DATA_SEC_ERR_INT);

    gTest_Addr = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR);

    /* This address is used to make cache line dirty without generating
     * additional ECC error*/
    gTest_Addr1 = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR + 0x4);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);

    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFEFFFF;
    gTest_Addr[0] = testVal;

    /* dirty bit for all cache line is set as 0 */
    UNICACHEWriteBackAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1DATA);

    testVal = gTest_Addr[0];

    /* we write to different memory location on same cache line to set dirty bit
     * to '1'. This is needed to ensure writeback occurs*/
    gTest_Addr1[0] = testVal;

    while (gErrStatus == 0) ;

    gEvictStat = 1;

    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(IPU_APP_INST);

    testVal = gTest_Addr[0];

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L1DATA_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L1DATA_SEC_ERR_INT);

    Intc_IntDisable();

    if ((gErrStatus != 0) && (testVal == 0xFFFFFFFF))
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data SEC ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data SEC ERR Test Pass!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data SEC ERR Occured at Address \r\n ", -1);
        UARTConfigPutHexNum(uartBaseAddr, gIpuErrAddr);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
    }

    return retVal;
}

/* Function performs IPU L1D RAM double bit error test
 * Inserts double bit error and waits for handler to finish
 */
static int32_t ipuL1DataDedErrTest(char option)
{
    uint32_t          testVal;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus  = 0;
    gTest_Addr  = NULL;
    gIpuErrAddr = 0x0;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.sRespHFEnable        = TRUE;
    cfgPrm.dataMask    = TRUE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L1DATA;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1DATA);

    Intc_Init();
    Intc_IntEnable(0);

    /* Register The HF interrupt */
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrIpuL1DataDedErr,
                     NULL);

    Intc_SystemEnable(gInterruptNum);

    gTest_Addr = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR2);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFCFFFF;
    gTest_Addr[0] = testVal;

    testVal = gTest_Addr[0];

    while (gErrStatus == 0) ;

    UNICACHEDisable(IPU_APP_INST);

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data DED ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data DED ERR Test Pass!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data DED ERR Occured at Address \r\n ", -1);
        UARTConfigPutHexNum(uartBaseAddr, gIpuErrAddr);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
    }

    return retVal;
}

/* Function performs IPU L1D RAM code error test
 * Inserts 3 bit error, which results in 1 bit ECC code error
 * and waits for handler to finish
 */
static int32_t ipuL1DataCodeErrTest(char option)
{
    uint32_t          testVal;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus  = 0;
    gEvictStat  = 0;
    gTest_Addr  = NULL;
    gIpuErrAddr = 0x0;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.sRespHFEnable        = FALSE;
    cfgPrm.dataMask    = FALSE;
    cfgPrm.eccCodeMask = FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L1DATA;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1DATA);

    /* Enable The L1 DATA SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L1DATA_SEC_ERR_INT, (IntrFuncPtr) isrIpuL1DataSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L1DATA_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L1DATA_SEC_ERR_INT);

    gTest_Addr = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR);

    /* This address is used to make cache line dirty without generating
     * additional ECC error*/
    gTest_Addr1 = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR + 0x4);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);

    testVal = gTest_Addr[0];

    /* This generates 3 bit err in data and 1 bit err in ECC code as per logic
     * testVal is 0xFFFFFFF8 instead of 0xFFFFFFFF
     * So Code Error + SEC Error Occurs when we do a read after ECC Enabled
     * This means Error in ECC Code ( Code Error) and
     * 1 bit Error in ECC code ( SEC Error)
     */
    testVal       = testVal & 0xFFFFFFF8;
    gTest_Addr[0] = testVal;

    /* dirty bit for all cache line is set as 0 */
    UNICACHEWriteBackAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1DATA);

    testVal = gTest_Addr[0];

    /* we write to different memory location on same cache line to set dirty bit
     * to '1'. This is needed to ensure writeback occurs*/
    gTest_Addr1[0] = testVal;

    while (gErrStatus == 0) ;

    gEvictStat = 1;

    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(IPU_APP_INST);

    testVal = gTest_Addr[0];

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L1DATA_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L1DATA_SEC_ERR_INT);

    Intc_IntDisable();

    if ((gErrStatus != 0) && (testVal == 0xFFFFFFF8))
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data CODE ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data CODE ERR Test Pass!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Data CODE ERR Occured at Address \r\n ", -1);
        UARTConfigPutHexNum(uartBaseAddr, gIpuErrAddr);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
    }

    return retVal;
}


/* Function performs IPU L1 Tag single error test
 * Inserts single bit error and waits for handler to finish
 */
static int32_t ipuL1TagSecErrTest(char option)
{
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus = 0;

    cfgPrm.errAutoCorrectEnable = TRUE;
    /* For L1Tag : sRespHFEnable is ignored */
    cfgPrm.sRespHFEnable = FALSE;
    cfgPrm.dataMask      = FALSE;
    cfgPrm.eccCodeMask   = FALSE;
    cfgPrm.memType       = ECC_IPU_MEM_TYPE_L1TAG;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1TAG);

    /* Enable The L1 TAG SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L1TAG_SEC_ERR_INT, (IntrFuncPtr) isrIpuL1TagSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L1TAG_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L1TAG_SEC_ERR_INT);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    /* Flush the cache & Invalidate all cache line*/
    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll. This ensures cache contains
     * exactly 1 valid entry */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_ECC_TEST_ADDR);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll. This ensures cache contains
     * exactly 1 valid entry
     *
     * To introduce one bit error in Tag Address: Addr[31:13]
     * Read the data from 0x90002000 instead of 0x90000000
     */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_SEC_ERR_TEST_ADDR);

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1TAG);

    /* Read the data from these address to generate SEC TAG Error
     * IPU_L1TAG_ECC_TEST_ADDR : IPU_L1TAG_ECC_TEST_ADDR+0x1F  /
     * IPU_L1TAG_SEC_ERR_TEST_ADDR : IPU_L1TAG_SEC_ERR_TEST_ADDR+0x1F
     */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_SEC_ERR_TEST_ADDR);

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L1TAG_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L1TAG_SEC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Tag SEC ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Tag SEC ERR Test Pass!! \r\n", -1);
    }

    return retVal;
}


/* Function performs IPU L1 Tag doble bit error test
 * Inserts double bit error and waits for handler to finish
 */
static int32_t ipuL1TagDedErrTest(char option)
{
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus = 0;

    cfgPrm.errAutoCorrectEnable = FALSE;
    /* For L1Tag : sRespHFEnable is ignored */
    cfgPrm.sRespHFEnable = FALSE;
    cfgPrm.dataMask      = FALSE;
    cfgPrm.eccCodeMask   = FALSE;
    cfgPrm.memType       = ECC_IPU_MEM_TYPE_L1TAG;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1TAG);

    /* Enable The L1 TAG DED ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L1TAG_DED_ERR_INT, (IntrFuncPtr) isrIpuL1TagDedErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L1TAG_DED_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L1TAG_DED_ERR_INT);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    /* Flush the cache & Invalidate all cache line*/
    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll. This ensures cache contains
     * exactly 1 valid entry */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_ECC_TEST_ADDR);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll. This ensures cache contains
     * exactly 1 valid entry
     *
     * To introduce two bit error in Tag Address: Addr[31:13]
     * Read the data from 0x90006000 instead of 0x90000000
     */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_DED_ERR_TEST_ADDR);

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1TAG);

    /* Read the data from these address to generate DED TAG Error
     * IPU_L1TAG_ECC_TEST_ADDR : IPU_L1TAG_ECC_TEST_ADDR+0x1F  /
     * IPU_L1TAG_DED_ERR_TEST_ADDR : IPU_L1TAG_DED_ERR_TEST_ADDR+0x1F
     */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_ECC_TEST_ADDR);

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L1TAG_DED_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L1TAG_DED_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Tag DED ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Tag DED ERR Test Pass!! \r\n", -1);
    }

    return retVal;
}


/* Function performs IPU L1 Tag code error test
 * Inserts 3 bit error, which results in 1 bit ECC code error
 * and waits for handler to finish
 */
static int32_t ipuL1TagCodeErrTest(char option)
{
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus = 0;

    cfgPrm.errAutoCorrectEnable = FALSE;
    /* For L1Tag : sRespHFEnable is ignored */
    cfgPrm.sRespHFEnable = FALSE;
    cfgPrm.dataMask      = FALSE;
    cfgPrm.eccCodeMask   = FALSE;
    cfgPrm.memType       = ECC_IPU_MEM_TYPE_L1TAG;

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1TAG);

    /* Enable The L1 TAG SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L1TAG_SEC_ERR_INT, (IntrFuncPtr) isrIpuL1TagSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L1TAG_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L1TAG_SEC_ERR_INT);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    /* Flush the cache & Invalidate all cache line*/
    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll. This ensures cache contains
     * exactly 1 valid entry */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_ECC_TEST_ADDR);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);

    UNICACHEInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Read data is preceded by InvalidateAll. This ensures cache contains
     * exactly 1 valid entry
     *
     * To introduce three bit error in Tag Address: Addr[31:13]
     * Read the data from 0x9000E000 instead of 0x90000000
     *
     * This generates 3 bit err in data and 1 bit err in ECC code as per logic
     * Read the data from 0x9000E000 instead of 0x90000000
     * So Code Error + SEC Error Occurs when we do a read after ECC Enabled
     * This means Error in ECC Code ( Code Error) and
     * 1 bit Error in ECC code ( SEC Error)
     */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_CODE_ERR_TEST_ADDR);

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1TAG);

    /* Read the data from these address to generate CODE + SEC TAG Error
     * IPU_L1TAG_ECC_TEST_ADDR : IPU_L1TAG_ECC_TEST_ADDR+0x1F  /
     * IPU_L1TAG_CODE_ERR_TEST_ADDR : IPU_L1TAG_CODE_ERR_TEST_ADDR+0x1F
     */
    gTestVal = *(volatile unsigned int *) (IPU_L1TAG_ECC_TEST_ADDR);

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L1TAG_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L1TAG_SEC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Tag CODE ERR Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- IPU L1Tag CODE ERR Test Pass!! \r\n", -1);
    }

    return retVal;
}

#endif
