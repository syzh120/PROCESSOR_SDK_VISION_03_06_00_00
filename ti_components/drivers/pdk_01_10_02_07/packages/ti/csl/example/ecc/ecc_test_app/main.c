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
 * main.c
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
#include <ti/csl/arch/a15/mmu_a15.h>

/* MMU table */
__attribute__((aligned(16384)))
mmuA15ModuleTable_t gMmuTable;

#if defined (SOC_AM574x)
#include <ti/board/board.h>
#endif

#include "ecc_emif.h"
#include "ecc_ocmc.h"

/* ----------------- Constant definitions ----------------- */

/* The following statements define Menu options */
#define EMIF_ECC_TEST                  ('1')
#define OCMC_RAM_ECC_TEST              ('2')
#if (defined (SOC_TDA2EX) || defined (SOC_DRA72x)) && defined (__ARM_ARCH_7A__)
#define MPU_L2CACHE_TEST               ('3')

#define MPU_L2CACHE_SEC_ERR_TEST       ('1')
#define MPU_L2CACHE_DED_ERR_TEST       ('2')

/* Defines MPU error interrupt */
#define MPU_CLUSTER_IRQ_AXIERR_INT       (3U)
#endif

/* The following defines Fault interrupt for double bit errors */
#if defined (__TI_ARM_V7M4__)
#define HARD_FAULT_INT                   (EXCEPTION_M4_HARD_FAULT_NUM_3)
#elif defined (__ARM_ARCH_7A__)
#define ABORT_INT                        (160U)
#endif

/* --------------------------------------------------- */

/* ----------------- Function prototypes ----------------- */
static void mainMenu(char *option);

#if (defined (SOC_TDA2EX) || defined (SOC_DRA72x)) && defined (__ARM_ARCH_7A__)
int32_t mpuL2cacheTest(void);
static void mainSubMenuMpuL2cacheTest(char *option);
void isrMpuL2CacheDedErr(void);
static int32_t mpuL2CacheSecErrTest(void);
static int32_t mpuL2CacheDedErrTest(void);
#endif

/* --------------------------------------------------- */

/* ----------------- Global variables ----------------- */

volatile uint32_t  gErrStatus = 0;

#if defined (__ARM_ARCH_7A__)
uint32_t           gInterruptNum = ABORT_INT;
#endif

extern void CPUDisableCPSRABit(void);

volatile uint32_t *gTest_Addr    = NULL;
volatile uint32_t *gTest_Addr1   = NULL;
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
 * and MPU ECC test.
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
#if defined (__ARM_ARCH_7A__)
    /* Initialize MMU module */
    MMUA15Init();

    /* Set MAIR to inner and outer write through cacheable
     * Note: without this setting the subquanta writes may fail
     */
    MMUA15SetMAIR(&gMmuTable, MMU_A15_ATTR_INDEX_2, 0xBB);
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
#if (defined (SOC_TDA2EX) || defined (SOC_DRA72x)) && defined (__ARM_ARCH_7A__)
        else if (MPU_L2CACHE_TEST == mainMenuOption)
        {
            retVal = mpuL2cacheTest();
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

/* The following routine handles main menu options*/
static void mainMenu(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. EMIF ECC TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. OCMC RAM ECC TEST", -1);
#if (defined (SOC_TDA2EX) || defined (SOC_DRA72x)) && defined (__ARM_ARCH_7A__)
        UARTConfigPuts(uartBaseAddr, "\r\n3. MPU L2CACHE ECC TEST", -1);
#endif
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (EMIF_ECC_TEST == *option ||
            OCMC_RAM_ECC_TEST == *option ||
#if (defined (SOC_TDA2EX) || defined (SOC_DRA72x)) && defined (__ARM_ARCH_7A__)
            MPU_L2CACHE_TEST == *option ||
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

#if (defined (SOC_TDA2EX) || defined (SOC_DRA72x)) && defined (__ARM_ARCH_7A__)
/* The following routine runs MPU cache test
 * based on commandline input
 */
int32_t mpuL2cacheTest(void)
{
    int32_t retVal = STW_SOK;
    char    mainSubMenuOption;

    while (1)
    {
        mainSubMenuMpuL2cacheTest(&mainSubMenuOption);

        if (MPU_L2CACHE_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = mpuL2CacheSecErrTest();
        }
        else if (MPU_L2CACHE_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = mpuL2CacheDedErrTest();
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\n  MPU L2Cache ECC test exiting...", -1);
            break;
        }
    }
    return retVal;
}

/* The following routine handles Mpu submenu */
static void mainSubMenuMpuL2cacheTest(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\n\n**** MPU L2Cache ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\n1. MPU L2CACHE SEC test", -1);
        UARTConfigPuts(uartBaseAddr, "\n2. MPU L2CACHE DED test", -1);
        UARTConfigPuts(uartBaseAddr, "\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\nSelect MPU L2Cache ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (MPU_L2CACHE_SEC_ERR_TEST == *option ||
            MPU_L2CACHE_DED_ERR_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\nEnter Valid option\n", -1);
        }
    }
}

/* Interrupt handler for Mpu L2 Cache Double bit error
 * Just checks error status
 */
void isrMpuL2CacheDedErr()
{
    gErrStatus = ECCA15GetEccErrStatus();
}

/* The following routine is meant to injects Single errors to test ECC
 * But currently only enables and disables ECC, see notes below
 */
static int32_t mpuL2CacheSecErrTest()
{
    int32_t  retVal       = STW_SOK;
    uint32_t cacheEnabled = 0;

    /* As software cannot inject A15 ECC Errors, this sequence code
     * helps to enable A15 ECC.
     * Here we are not testing A15 ECC for 1 bit Error
     */
    UARTConfigPuts(uartBaseAddr, "\r\nsoftware cannot inject A15 ECC Errors.", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nHere we are not testing A15 ECC for 1 bit Error.", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nAdded only for reference on how to enable A15 ECC.", -1);
    ECCA15Enable();

    /* Check if cache is already enabled */
    cacheEnabled = CACHEA15GetEnabled();

    /* In case cache is disabled, invalidate and enable it */
    if (CACHE_A15_TYPE_ALL != cacheEnabled)
    {
        CACHEA15InvalidateL1DAll();

        CACHEA15InvalidateL1IAll();

        CACHEA15Enable(CACHE_A15_TYPE_ALL);
    }

    /* System code which is to be executed with A15 ECC Enable*/

    /* Disable cache */
    CACHEA15Disable(CACHE_A15_TYPE_ALL);

    return retVal;
}

/* The following routine is meant to inject double bit errors to test ECC
 * But currently only enables and disables ECC, see notes below
 */
static int32_t mpuL2CacheDedErrTest()
{
    int32_t  retVal       = STW_SOK;
    uint32_t cacheEnabled = 0;

    gErrStatus = 0;

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(MPU_CLUSTER_IRQ_AXIERR_INT,
                     (IntrFuncPtr) isrMpuL2CacheDedErr,
                     NULL);

    /* As software cannot inject A15 ECC Errors, this sequence code
     * helps to enable A15 ECC.
     * Here we are not testing A15 ECC for 2 bit Error
     */
    UARTConfigPuts(uartBaseAddr, "\r\nsoftware cannot inject A15 ECC Errors.", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nHere we are not testing A15 ECC for 1 bit Error.", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nAdded only for reference on how to enable A15 ECC.", -1);

    ECCA15Enable();

    /* Check if cache is already enabled */
    cacheEnabled = CACHEA15GetEnabled();

    /* In case cache is disabled, invalidate and enable it */
    if (CACHE_A15_TYPE_ALL != cacheEnabled)
    {
        CACHEA15InvalidateL1DAll();

        CACHEA15InvalidateL1IAll();

        CACHEA15Enable(CACHE_A15_TYPE_ALL);
    }

    /* System code which is to be executed with A15 ECC Enable*/

    /* Disable cache */
    CACHEA15Disable(CACHE_A15_TYPE_ALL);

    /* Unregister the interrupt */
    Intc_IntUnregister(MPU_CLUSTER_IRQ_AXIERR_INT);

    Intc_IntDisable();

    return retVal;
}

#endif
