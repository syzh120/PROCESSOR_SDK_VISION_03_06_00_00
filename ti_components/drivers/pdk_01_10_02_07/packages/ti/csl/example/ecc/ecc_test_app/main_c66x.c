/* =============================================================================
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated
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
 * main_c66x.c
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
#include <ti/board/board.h>
#endif

#include "ecc_emif.h"
#include "ecc_ocmc.h"

/* ----------------- Constant definitions ----------------- */

/* The following statements define Menu options */
#define EMIF_ECC_TEST                  ('1')
#define OCMC_RAM_ECC_TEST              ('2')
#define DSP_ECC_TEST                   ('3')

/** \brief DSP Test case options */
#define DSP_L1P_CACHE_TEST              ('1')
#define DSP_L1P_DMA_TEST                ('2')
#define DSP_L2_L1D_ACCESS_ERROR_TEST    ('3')
#define DSP_L2_L1P_ACCESS_ERROR_TEST    ('4')
#define DSP_L2_DMA_ACCESS_ERROR_TEST    ('5')
#define DSP_L2_VICTIM_ACCESS_ERROR_TEST ('6')
#define DSP_L1D_DMA_TEST                ('7')
#define DSP_L1D_TAG_TEST                ('8')
#define DSP_L2_TAG_TEST                 ('9')
#define DSP_L1P_TAG_TEST                ('a')
#define DSP_ECC_RUN_ALL                 ('b')

#define EXIT(opt)      (('x' == opt) || ('X' == opt))

#define DSP_IRQ_111                      (111U)
#define DSP_IRQ_112                      (112U)
#define DSP_IRQ_113                      (113U)
#define DSP_IRQ_116                      (116U)
#define DSP_IRQ_117                      (117U)
#define DSP_ECC_NUM_BYTES                (128U)

/* ------------------------------------------------------- */

/* ----------------- Function prototypes ----------------- */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
/* main menu function not defined for tda builds. */
#else
static void mainMenu(char *option);
#endif
int32_t dspEccTest(void);
static int32_t dspEccL1PCacheTest(void);
static int32_t dspEccL1PDmaTest(void);
#if defined (SOC_TDA2PX)
static int32_t dspEccL1DDmaTest(void);
static void    dspEccL1DDmaErrHandler(void *handle);
static int32_t dspEccL1DTagTest(void);
static void    dspEccL1DTagErrHandler(void *handle);
static int32_t dspEccL2TagTest(void);
static void    dspEccL2TagErrHandler(void *handle);
static int32_t dspEccL1PTagTest(void);
static void    dspEccL1PTagErrHandler(void *handle);
#endif
static int32_t dspEccL2L1DAccessErrTest(void);
static int32_t dspEccL2L1PAccessErrTest(void);
static int32_t dspEccL2DmaAccessErrTest(void);
static int32_t dspEccL2VictimAccessErrTest(void);

/* ------------------------------------------------------- */

/* ----------------- Global variables ----------------- */

volatile uint32_t  gErrStatus = 0;

/* Global variables are defined which are used to generate accesses to
 * different ways of the L2 cache line.
 */
 /** \brief Global variables are defined which are used to generate accesses to
  *         different ways of the L2 cache line.
  */
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec1")
#else
#pragma DATA_SECTION(dummyVar1, ".my_l2_data_sec1")
#endif
volatile uint32_t dummyVar1 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec2")
#else
#pragma DATA_SECTION(dummyVar2, ".my_l2_data_sec2")
#endif
volatile uint32_t dummyVar2 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec3")
#else
#pragma DATA_SECTION(dummyVar3, ".my_l2_data_sec3")
#endif
volatile uint32_t dummyVar3 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec4")
#else
#pragma DATA_SECTION(dummyVar4, ".my_l2_data_sec4")
#endif
volatile uint32_t dummyVar4 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec5")
#else
#pragma DATA_SECTION(dummyVar5, ".my_l2_data_sec5")
#endif

uint32_t           gInterruptNum = (EMIF_ECC_ERR_INT);

volatile uint32_t *gTest_Addr    = NULL;
volatile uint32_t *gTest_Addr1   = NULL;
volatile uint32_t  gTestVal      = 0;
volatile uint32_t  gEvictStat    = 0;

volatile uint32_t dummyVar5 = 0U;
volatile uint32_t gInterruptRecd = 0U;
volatile uint32_t gCurrEccTest = 0U;

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
 * and IPU ECC test.
 * The OCMC err test & EMIF err test functions are in thier respective
 * separate c files and are used by all cores.
 * Once the class of tests are selected, then the submenu options for
 * the chosen class, are processed.
 */
int main(void)
{
    int32_t           retVal   = STW_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#else
    char mainMenuOption;
#endif
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
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
    /* For TDA Builds calling only the DSP ECC tests. */
    dspEccTest();
#else
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
        else if (DSP_ECC_TEST == mainMenuOption) {
            /* Handle dsp ECC test menu */
            retVal = dspEccTest();
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\n  ECC test exiting...", -1);
            break;
        }
    };
#endif
    return retVal;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
/* main menu function not defined for tda builds. */
#else
/* The following routine handles main menu options*/
static void mainMenu(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. EMIF ECC TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. OCMC RAM ECC TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n3. DSP ECC TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (EMIF_ECC_TEST == *option ||
            OCMC_RAM_ECC_TEST == *option ||
            DSP_ECC_TEST == *option ||
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
#endif

/* The following routine handles DSP sub menu */
static void dspSubMenu(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** DSP ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. DSP L1P CACHE TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. DSP L1P DMA TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n3. DSP L2 L1D ACCESS ERROR TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n4. DSP L2 L1P ACCESS ERROR TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n5. DSP L2 DMA ACCESS ERROR TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n6. DSP L2 VICTIM ACCESS ERROR TEST", -1);
    #if defined (SOC_TDA2PX)
        UARTConfigPuts(uartBaseAddr, "\r\n7. DSP L1D DMA TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n8. DSP L1D Tag TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n9. DSP L2 Tag TEST", -1);
        UARTConfigPuts(uartBaseAddr, "\r\na. DSP L1P Tag TEST", -1);
    #endif
        UARTConfigPuts(uartBaseAddr, "\r\nb. Run All Back to Back", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if((DSP_L1P_CACHE_TEST              == *option) ||
           (DSP_L1P_DMA_TEST                == *option) ||
           (DSP_L2_L1D_ACCESS_ERROR_TEST    == *option) ||
           (DSP_L2_L1P_ACCESS_ERROR_TEST    == *option) ||
           (DSP_L2_DMA_ACCESS_ERROR_TEST    == *option) ||
           (DSP_L2_VICTIM_ACCESS_ERROR_TEST == *option) ||
           (DSP_L1D_DMA_TEST                == *option) ||
           (DSP_L1D_TAG_TEST                == *option) ||
           (DSP_L2_TAG_TEST                 == *option) ||
           (DSP_L1P_TAG_TEST                == *option) ||
           (DSP_ECC_RUN_ALL == *option) ||
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

/* The following routine run DSP ECC test based on commandline input */
int32_t dspEccTest(void) {
    int32_t retVal = STW_SOK;
    volatile uint32_t testDone = 1;
    char dspSubMenuOption;

    while(testDone) {
        dspSubMenu(&dspSubMenuOption);
        switch (dspSubMenuOption)
        {
            case DSP_L1P_CACHE_TEST:
                gCurrEccTest = DSP_L1P_CACHE_TEST;
                retVal = dspEccL1PCacheTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_CACHE_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_CACHE_TEST: Fail!!", -1);
                }
                break;
            case DSP_L1P_DMA_TEST:
                gCurrEccTest = DSP_L1P_DMA_TEST;
                retVal = dspEccL1PDmaTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_DMA_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_DMA_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_L1D_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_L1D_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1DAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_L1P_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_L1P_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1PAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_DMA_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_DMA_ACCESS_ERROR_TEST;
                retVal = dspEccL2DmaAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_VICTIM_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_VICTIM_ACCESS_ERROR_TEST;
                retVal = dspEccL2VictimAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
        #if defined (SOC_TDA2PX)
            case DSP_L1D_DMA_TEST:
                gCurrEccTest = DSP_L1D_DMA_TEST;
                retVal = dspEccL1DDmaTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1D_DMA_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1D_DMA_TEST: Fail!!", -1);
                }
                break;
            case DSP_L1D_TAG_TEST:
                gCurrEccTest = DSP_L1D_TAG_TEST;
                retVal = dspEccL1DTagTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1D_TAG_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1D_TAG_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_TAG_TEST:
                gCurrEccTest = DSP_L2_TAG_TEST;
                retVal = dspEccL2TagTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_TAG_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_TAG_TEST: Fail!!", -1);
                }
                break;
            case DSP_L1P_TAG_TEST:
                gCurrEccTest = DSP_L1P_TAG_TEST;
                retVal = dspEccL1PTagTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_TAG_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_TAG_TEST: Fail!!", -1);
                }
                break;
        #endif
            case DSP_ECC_RUN_ALL:
                gCurrEccTest = DSP_L1P_CACHE_TEST;
                retVal = dspEccL1PCacheTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_CACHE_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_CACHE_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L1P_DMA_TEST;
                retVal = dspEccL1PDmaTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_DMA_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L1P_DMA_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_L1D_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1DAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_L1P_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1PAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_DMA_ACCESS_ERROR_TEST;
                retVal = dspEccL2DmaAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_VICTIM_ACCESS_ERROR_TEST;
                retVal = dspEccL2VictimAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            default :
                UARTConfigPuts(uartBaseAddr, "\r\n  ECC test exiting...", -1);
                testDone = 0U;
                break;
        }
    }
    return retVal;
}

#ifdef __cplusplus
#pragma FUNC_CANNOT_INLINE;
#pragma CODE_SECTION(".my_l1p_code_sec1")
#else
#pragma FUNC_CANNOT_INLINE (dummyAdd)
#pragma CODE_SECTION(dummyAdd, ".my_l1p_code_sec1")
#endif

/* Dummy Add function */
int32_t dummyAdd ( int32_t a, int32_t b)
{
    return a + b;
}

#ifdef __cplusplus
#pragma FUNC_CANNOT_INLINE;
#pragma CODE_SECTION(".my_l1p_code_sec2")
#else
#pragma FUNC_CANNOT_INLINE (dummySub);
#pragma CODE_SECTION(dummySub, ".my_l1p_code_sec2")
#endif
/* Dummy Subtract function */
int32_t dummySub (int32_t a, int32_t b)
{
    return a - b;
}

/* Interrupt handler for DSP ECC L1 PDMA error
 * Sets global flag based on error info
 */
static void dspEccL1PDmaErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if ((STW_SOK == retVal) && (1U == errStatus.l1PDmaAccessErr))
    {
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L1P, &eccDspInfo);
        if (eccDspInfo.errRamOrCache == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1P DMA Error @ address = 0x%x", eccDspInfo.errAddress);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        else
        {
            gInterruptRecd = 0U;
        }
    }
    gInterruptRecd = 1U;
}

#if defined (SOC_TDA2PX)
static void dspEccL1DDmaErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t   errStatus = {0U};
    eccDspL1DErrInfo_t  eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if ((STW_SOK == retVal) && ((1U == errStatus.l1DDataCorrectableError) ||
                                (1U == errStatus.l1DDataNonCorrectableError)))
    {
        ECCDspGetL1DErrInfo(&eccDspInfo);
        if (eccDspInfo.dataCErrStat == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Correctable Data Error @ Address = 0x%x bank = 0x%x Byte = 0x%x BitPos = 0x%x",
                eccDspInfo.dataCErrAddr, eccDspInfo.dataCErrBank, eccDspInfo.dataCErrByte, eccDspInfo.dataCErrBitPos);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if ((eccDspInfo.dataCErrStat == 2U) || (eccDspInfo.dataCErrStat == 3U))
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Data Multiple Correctable Errors occoured");
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Correctable Data Error @ Address = 0x%x bank = 0x%x Byte = 0x%x BitPos = 0x%x",
                eccDspInfo.dataCErrAddr, eccDspInfo.dataCErrBank, eccDspInfo.dataCErrByte, eccDspInfo.dataCErrBitPos);
            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if (eccDspInfo.dataNCErrStat == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Non Correctable Data Error @ Address = 0x%x bank = 0x%x Byte = 0x%x",
                eccDspInfo.dataNCErrAddr, eccDspInfo.dataNCErrBank, eccDspInfo.dataNCErrByte);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if (eccDspInfo.dataNCErrStat == 2U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Data Multiple Non Correctable Errors occoured");
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Non Correctable Data Error @ Address = 0x%x bank = 0x%x Byte = 0x%x",
                eccDspInfo.dataNCErrAddr, eccDspInfo.dataNCErrBank, eccDspInfo.dataNCErrByte);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
    }
}

static void dspEccL1DTagErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t   errStatus = {0U};
    eccDspL1DErrInfo_t  eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if ((STW_SOK == retVal) && ((1U == errStatus.l1DTagCorrectableError) ||
                                (1U == errStatus.l1DTagNonCorrectableError)))
    {
        ECCDspGetL1DErrInfo(&eccDspInfo);
        if (eccDspInfo.tagCErrStat == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Correctable Tag Error @ Address = 0x%x bank = 0x%x Chan = 0x%x BitPos = 0x%x",
                eccDspInfo.tagCErrAddr, eccDspInfo.tagCErrBank, eccDspInfo.tagCErrChan, eccDspInfo.tagCErrBitPos);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if ((eccDspInfo.tagCErrStat == 2U) || (eccDspInfo.tagCErrStat == 3U))
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D tag Multiple Correctable Errors occoured");
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Correctable tag Error @ Address = 0x%x bank = 0x%x Chan = 0x%x BitPos = 0x%x",
                eccDspInfo.tagCErrAddr, eccDspInfo.tagCErrBank, eccDspInfo.tagCErrChan, eccDspInfo.tagCErrBitPos);
            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if (eccDspInfo.tagNCErrStat == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Non Correctable tag Error @ Address = 0x%x bank = 0x%x Chan = 0x%x",
                eccDspInfo.tagNCErrAddr, eccDspInfo.tagNCErrBank, eccDspInfo.tagNCErrChan);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if ((eccDspInfo.tagNCErrStat == 2U) || (eccDspInfo.tagNCErrStat == 3U))
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D tag Multiple Non Correctable Errors occoured");
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Non Correctable tag Error @ Address = 0x%x bank = 0x%x Chan = 0x%x",
                eccDspInfo.tagNCErrAddr, eccDspInfo.tagNCErrBank, eccDspInfo.tagNCErrChan);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
    }
}

static void dspEccL2TagErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t       errStatus = {0U};
    eccDspL2TagErrInfo_t    eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if ((STW_SOK == retVal) && ((1U == errStatus.l2TagNonCorrectableError) ||
                                (1U == errStatus.l2TagCorrectableError)))
    {
        ECCDspGetL2TagErrInfo(&eccDspInfo);
        if (eccDspInfo.tagCErrStat == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Correctable Tag Error @ Address = 0x%x bank = 0x%x Chan = 0x%x BitPos = 0x%x",
                eccDspInfo.tagCErrAddr, eccDspInfo.tagCErrBank, eccDspInfo.tagCErrChan, eccDspInfo.tagCErrBitPos);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if ((eccDspInfo.tagCErrStat == 2U) || (eccDspInfo.tagCErrStat == 3U))
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D tag Multiple Correctable Errors occoured");
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Correctable tag Error @ Address = 0x%x bank = 0x%x Chan = 0x%x BitPos = 0x%x",
                eccDspInfo.tagCErrAddr, eccDspInfo.tagCErrBank, eccDspInfo.tagCErrChan, eccDspInfo.tagCErrBitPos);
            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if (eccDspInfo.tagNCErrStat == 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Non Correctable tag Error @ Address = 0x%x bank = 0x%x",
                eccDspInfo.tagNCErrAddr, eccDspInfo.tagNCErrBank);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        if ((eccDspInfo.tagNCErrStat == 2U) || (eccDspInfo.tagNCErrStat == 3U))
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D tag Multiple Non Correctable Errors occoured");
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1D Non Correctable tag Error @ Address = 0x%x bank = 0x%x",
                eccDspInfo.tagNCErrAddr, eccDspInfo.tagNCErrBank);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
    }
}

static void dspEccL1PTagErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t       errStatus = {0U};
    eccDspL1PTagErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if ((STW_SOK == retVal) && (1U == errStatus.l1PTagNonCorrectableError))
    {
        ECCDspGetL1PTagErrInfo(&eccDspInfo);
        if (eccDspInfo.tagNCErrStat >= 1U)
        {
            UARTConfigPrintf(uartBaseAddr, "\r\nDSP L1P Non Correctable Tag Error @ Address = 0x%x",
                eccDspInfo.tagNCErrAddr);

            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
    }
}
#endif

/* Function Disables and unregisters interrupt handlers */
static void dspEccL2unregisterIntr(void)
{
    Intc_SystemDisable(DSP_IRQ_116);
    Intc_IntUnregister(DSP_IRQ_116);
    Intc_SystemDisable(DSP_IRQ_117);
    Intc_IntUnregister(DSP_IRQ_117);
}

/* Interrupt handler for DSP ECC L2 Uncorrectable error
 * Sets global flag based on error info and clears interrupt
 * If error info does not match expected, prints error.
 */
static void dspEccL2UnCorrErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if (STW_SOK == retVal)
    {
        switch(gCurrEccTest)
        {
            case DSP_L2_L1D_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1DAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            case DSP_L2_L1P_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1PAccessErr)
                {
                    gInterruptRecd = 1U;
                    /* Invalidate L1P */
                    DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE,
                                              DSPICFG_MEM_L1P);
                    /* Configure Cache size of L1P as disabled. */
                    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
                    /* Disable ECC for L2 */
                    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                                 ECC_DISABLE,
                                 1000U);
                    dspEccL2unregisterIntr();
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            case DSP_L2_DMA_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2DmaAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            case DSP_L2_VICTIM_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2VictimsErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            default :
                UARTConfigPuts(uartBaseAddr, "\r\nError Recieved for incorrect test!!", -1);
                gInterruptRecd = 0U;
        }
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L2, &eccDspInfo);
        ECCDspIntrClrErrStatus(&errStatus);

        UARTConfigPrintf(uartBaseAddr,"\r\nDSP L2 Uncorrectable Error @ address = 0x%x",
                     eccDspInfo.errAddress);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Ram(1)/Cache(0) = %d",
                     eccDspInfo.errRamOrCache);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Bit Position = %d",
                     eccDspInfo.errL2BitPosition);
        UARTConfigPrintf(uartBaseAddr,
            "\r\n             @ Single Bit(0)/Double Bit(1)/Parity(3) = %d",
            eccDspInfo.errL2Type);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ L2 Cache error in Way %d",
            eccDspInfo.errL2way);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Correctable Parity Error Count = %d",
            eccDspInfo.errL2CorrectableCount);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Non-Correctable Parity Error count = %d",
            eccDspInfo.errL2NonCorrectableCount);
    }
}

/* Interrupt handler for DSP ECC L2 Correctable error
 * Sets global flag based on error info and clears interrupt
 * If error info does not match expected, prints error.
 */
static void dspEccL2CorrErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if (STW_SOK == retVal)
    {
        switch(gCurrEccTest)
        {
            case DSP_L2_L1D_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1DAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            case DSP_L2_L1P_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1PAccessErr)
                {
                    gInterruptRecd = 1U;
                    /* Invalidate L1P */
                    DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE,
                                              DSPICFG_MEM_L1P);
                    /* Configure Cache size of L1P as disabled. */
                    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
                    /* Disable ECC for L2 */
                    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                                 ECC_DISABLE,
                                 1000U);
                    dspEccL2unregisterIntr();
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            case DSP_L2_DMA_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2DmaAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            case DSP_L2_VICTIM_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2VictimsErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTConfigPuts(uartBaseAddr, "\r\nError Not generated", -1);
                }
                break;
            default :
                UARTConfigPuts(uartBaseAddr, "\r\nError Recieved for incorrect test!!", -1);
                gInterruptRecd = 0U;
        }
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L2, &eccDspInfo);
        ECCDspIntrClrErrStatus(&errStatus);

        UARTConfigPrintf(uartBaseAddr,"\r\nDSP L2 Correctable Error @ address = 0x%x",
                     eccDspInfo.errAddress);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Ram(1)/Cache(0) = %d",
                     eccDspInfo.errRamOrCache);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Bit Position = %d",
                     eccDspInfo.errL2BitPosition);
        UARTConfigPrintf(uartBaseAddr,
            "\r\n             @ Single Bit(0)/Double Bit(1)/Parity(3) = %d",
            eccDspInfo.errL2Type);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ L2 Cache error in Way %d",
            eccDspInfo.errL2way);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Correctable Parity Error Count = %d",
            eccDspInfo.errL2CorrectableCount);
        UARTConfigPrintf(uartBaseAddr,"\r\n             @ Non-Correctable Parity Error count = %d",
            eccDspInfo.errL2NonCorrectableCount);
    }
}

/* Function performs DSP ECC L1P Cache test by injection of error in cache
 */
static int32_t dspEccL1PCacheTest(void)
{
    int32_t retVal = STW_SOK;
    volatile int32_t dummyTotal = 0U;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L1P Cache Access Error Test", -1);

    /* Configure Cache size of L1P as 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_4K);
    /* Enable ECC for L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Initializing the cache line with the code. This function is placed
     * such that the corrupting function call falls exactly in the same
     * L1P cache line. Dummy add is placed in my_l1p_code_sec1 which is in
     * 0x80000400 which will fill a particular L1P cache line. Since the
     * addition operation is called the op code which will fill the cache line
     * is add.
     */
    dummyTotal = dummyAdd(3, 4);
    /* Suspend the ECC operation to corrupt the cache line */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L1P, 1000U);
    /* Corrupting the Cache line. Since the operation is sub, this will change
     * one bit of the cache line which up till now contained add. The same
     * cache line being corrupted is maintained by placing dummySub at
     * 0x81000400. Since L1P is direct mapped this will replace dummyAdd.
     */
    dummyTotal = dummySub(3, 4);
    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Access the same corrupted cache line to cause a ECC L1P error */
    dummyTotal = dummySub(3, 4);

    ECCDspIntrGetErrStatus(&errStatus);

    if (errStatus.l1PProgramFetchErr == 1U)
    {
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L1P, &eccDspInfo);
        if (eccDspInfo.errRamOrCache == 0U)
        {
            retVal = STW_SOK;

            UARTConfigPrintf(uartBaseAddr,"\r\nDSP L1P Cache Error @ address = 0x%x",
                     eccDspInfo.errAddress);

            ECCDspIntrClrErrStatus(&errStatus);
            DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L1P);
        }
        else
        {
            retVal = STW_EFAIL;
        }
    }
    else
    {
        retVal = STW_EFAIL;
    }

    /* Disable ECC */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_DISABLE,
                 1000U);
    /* Reconfigure L1P cache to the default value of 32K */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    ECCDspIntrClrErrStatus(&errStatus);
    return retVal;
}

/* Function performs DSP ECC L1P DMA test by injection of error through
 * DMA
 */
static int32_t dspEccL1PDmaTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;
    gInterruptRecd = 0U;
    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L1P DMA Access Error Test", -1);
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_113,
                     (IntrFuncPtr) dspEccL1PDmaErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_113, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_113);

    /* Configure Cache size of L1P as 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Fill the initialization pattern to some location in L2. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L2. This will be used
     * to test the L1P EDC for DMA access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A1A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }

    /* Enable ECC for L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Initialize memory using IDMA. Copy the contents from L2 to L1P. */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L1P_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L1P, 1000U);

    /* Corrupt memory using IDMA. Copy the corrupted array from L2 to L1P */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L1P_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Read the corrupted data to cause a ECC error interrupt.
     * IDMA read from L1P to L2.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L1P_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_DISABLE,
                 1000U);
    /* Reconfigure L1P cache to the default value of 32K */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    return retVal;
}

#if defined (SOC_TDA2PX)
static int32_t dspEccL1DDmaTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;
    gInterruptRecd = 0U;
    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L1D DMA Access Error Test", -1);
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_111,
                     (IntrFuncPtr) dspEccL1DDmaErrHandler, NULL);
    Intc_IntRegister((uint16_t) DSP_IRQ_112,
                     (IntrFuncPtr) dspEccL1DDmaErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_111, (uint16_t) 1, (uint8_t) 0);
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_112, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_111);
    Intc_SystemEnable((uint16_t) DSP_IRQ_112);

    /* Configure L1D Cache as disabled */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Fill the initialization pattern to some location in L2. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L2. This will be used
     * to test the L1D EDC for DMA access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A1A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }

    /* Enable ECC for L1D */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1D,
                 ECC_ENABLE,
                 1000U);

    /* Initialize memory using IDMA. Copy the contents from L2 to L1P. */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L1D_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L1D, 1000U);

    /* Corrupt memory using IDMA. Copy the corrupted array from L2 to L1P */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L1D_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1D,
                 ECC_ENABLE,
                 1000U);

    /* Read the corrupted data to cause a ECC error interrupt.
     * IDMA read from L1P to L2.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L1D_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Read the corrupted data again to cause the ECC error again. */
    UARTConfigPuts(uartBaseAddr, "\r\nReading corrupted data again to generate the error second time.", -1);
    gInterruptRecd = 0U;

    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L1D_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1D,
                 ECC_DISABLE,
                 1000U);
    /* Reconfigure L1D cache to the default value of 32K */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_32K);

    Intc_SystemDisable(DSP_IRQ_111);
    Intc_IntUnregister(DSP_IRQ_111);
    Intc_SystemDisable(DSP_IRQ_112);
    Intc_IntUnregister(DSP_IRQ_112);
    return retVal;
}

static int32_t dspEccL1DTagTest(void)
{
    int32_t retVal = STW_SOK;
    gInterruptRecd = 0U;
    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L1D Tag Test", -1);
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_111,
                     (IntrFuncPtr) dspEccL1DTagErrHandler, NULL);
    Intc_IntRegister((uint16_t) DSP_IRQ_112,
                     (IntrFuncPtr) dspEccL1DTagErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_111, (uint16_t) 1, (uint8_t) 0);
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_112, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_111);
    Intc_SystemEnable((uint16_t) DSP_IRQ_112);

    /* Configure Cache size of L1D as enabled 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_4K);
    /* Configure Cache size of L2 as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_DISABLED);
    /* Configure Cache size of L1P as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Enable the ECC operation on L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1D, ECC_ENABLE, 1000U);

    /* TODO: Add code to generate the L1D Tag Ecc error. */

    /* Disable the ECC operation on L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1D, ECC_DISABLE, 1000U);
    /* Configure Cache size of L1D as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);

    Intc_SystemDisable(DSP_IRQ_111);
    Intc_IntUnregister(DSP_IRQ_111);
    Intc_SystemDisable(DSP_IRQ_112);
    Intc_IntUnregister(DSP_IRQ_112);
    return retVal;
}

static int32_t dspEccL2TagTest(void)
{
    int32_t retVal = STW_SOK;
    gInterruptRecd = 0U;
    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L2 Tag Test", -1);
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_111,
                     (IntrFuncPtr) dspEccL2TagErrHandler, NULL);
    Intc_IntRegister((uint16_t) DSP_IRQ_112,
                     (IntrFuncPtr) dspEccL2TagErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_111, (uint16_t) 1, (uint8_t) 0);
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_112, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_111);
    Intc_SystemEnable((uint16_t) DSP_IRQ_112);

    /* Configure Cache size of L2 as enabled 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_32K);

    /* Enable the ECC operation on L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2, ECC_ENABLE, 1000U);

    /* TODO: Add code to generate the L2 Tag Ecc error. */

    /* Disable the ECC operation on L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2, ECC_DISABLE, 1000U);
    /* Configure Cache size of L2 as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_DISABLED);

    Intc_SystemDisable(DSP_IRQ_111);
    Intc_IntUnregister(DSP_IRQ_111);
    Intc_SystemDisable(DSP_IRQ_112);
    Intc_IntUnregister(DSP_IRQ_112);
    return retVal;
}

static int32_t dspEccL1PTagTest(void)
{
    int32_t retVal = STW_SOK;
    gInterruptRecd = 0U;
    volatile int32_t dummyTotal = 0U;

    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L1P Tag Test", -1);
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_111,
                     (IntrFuncPtr) dspEccL1PTagErrHandler, NULL);
    Intc_IntRegister((uint16_t) DSP_IRQ_112,
                     (IntrFuncPtr) dspEccL1PTagErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_111, (uint16_t) 1, (uint8_t) 0);
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_112, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_111);
    Intc_SystemEnable((uint16_t) DSP_IRQ_112);

    /* Configure Cache size of L1D as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Configure Cache size of L2 as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_DISABLED);
    /* Configure Cache size of L1P as enabled 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_4K);
    /* Enable the ECC operation on L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P, ECC_ENABLE, 1000U);

    /* TODO: Add code to generate the L1P Tag Ecc error. */

    /* Disable the ECC operation on L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P, ECC_DISABLE, 1000U);
    /* Configure Cache size of L1P as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);

    Intc_SystemDisable(DSP_IRQ_111);
    Intc_IntUnregister(DSP_IRQ_111);
    Intc_SystemDisable(DSP_IRQ_112);
    Intc_IntUnregister(DSP_IRQ_112);
    return retVal;
}
#endif

/* Function enables and register interrupt handler
 */
static void dspEccL2registerIntr(void)
{
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_116,
                     (IntrFuncPtr) dspEccL2CorrErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_116, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_116);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_117,
                     (IntrFuncPtr) dspEccL2UnCorrErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_117, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_117);
}

/* Function runs DSP ECC L2 L1D access error test
 */
static int32_t dspEccL2L1DAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;
    gInterruptRecd = 0U;
    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L2 L1D Cache Access Error Test", -1);
    dspEccL2registerIntr();

    /* Configure Cache size of L1D as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Fill the initialization pattern to some location in L2. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L2. This will be used
     * to test the L2 EDC for L1D access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A5A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }
    /* In this test the L2 memory is filled with a fixed pattern with ECC
     * ECC enabled and then corrupted with ECC disabled. The L1D cache is then
     * enabled and the L2 region is read from CPU which causes the L1D
     * cache line access. This causes the ECC error to be triggered for L1D read
     * causing an L2 SRAM ECC error.
     */
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Initialize L2 memory using IDMA with the right pattern */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* Corrupt memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE  + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Configure Cache size of L1D as 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_32K);

    /* This read will cause the L1D Access error to be set. This is always
     * uncorrectable.
     */
    HW_RD_REG32(SOC_DSP_L2_BASE  + 0x8200 + (4U*16U));

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    dspEccL2unregisterIntr();
    return retVal;
}

#ifdef __cplusplus
#pragma FUNC_CANNOT_INLINE;
#pragma CODE_SECTION(".my_l2_code_sec1")
#else
#pragma FUNC_CANNOT_INLINE(dummyCodeL2First);
#pragma CODE_SECTION(dummyCodeL2First, ".my_l2_code_sec1")
#endif
/* dummy function to be placed first in L2
 */
uint32_t dummyCodeL2First(int32_t a, int32_t b)
{
    uint32_t returnVal;
    if (a > b)
    {
        returnVal = 1U;
    }
    else
    {
        returnVal = 0U;
    }
    return returnVal;
}

#ifdef __cplusplus
#pragma FUNC_CANNOT_INLINE;
#pragma CODE_SECTION(".my_l2_code_sec2")
#else
#pragma FUNC_CANNOT_INLINE(dummyCodeL2Second);
#pragma CODE_SECTION(dummyCodeL2Second, ".my_l2_code_sec2")
#endif
/* dummy function to be placed Second in L2
 */
uint32_t dummyCodeL2Second(int32_t a, int32_t b)
{
    uint32_t returnVal;
    if (a > b)
    {
        /* Note how the difference between the two function is only 1 bit,
         * 5 vs 1.
         */
        returnVal = 5U;
    }
    else
    {
        returnVal = 0U;
    }
    return returnVal;
}

/* Function performs DSP ECC L2 L1P Access error test
 */
static int32_t dspEccL2L1PAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    volatile uint32_t dummyVal = 0U;
    gInterruptRecd = 0U;

    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L2 L1P Cache Access Error Test", -1);

    /* Configure Cache size of L1P as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    dspEccL2unregisterIntr();
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Memory Scubbing. Generate the ECC codes for the L2 SRAM by writing one
     * cache line size of data corresponding to the dummyCodeL2First function
     * location with in L2 SRAM. The opcodes in this location are read and
     * written back by the IDMA to generate the ECC codes.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                (uint32_t)&dummyCodeL2First);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST,
                (uint32_t)&dummyCodeL2First);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT,
                DSPICFG_L2_CACHE_LINE_SIZE);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Memory Scubbing.  Generate the ECC codes for the L2 SRAM by writing one
     * cache line size of data corresponding to the dummyCodeL2Second function
     * location with in L2 SRAM. The opcodes in this location are read and
     * written back by the IDMA to generate the ECC codes.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                (uint32_t)&dummyCodeL2Second);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST,
                (uint32_t)&dummyCodeL2Second);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT,
                DSPICFG_L2_CACHE_LINE_SIZE);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* Memory Corruption. Copy the dummyCodeL2Second function contents to
     * dummyCodeL2First. These two functions differ by only 1 bit in terms
     * of their return values which causes the ECC error to be triggered when
     * read by L1P later.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                (uint32_t)&dummyCodeL2Second);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST,
                (uint32_t)&dummyCodeL2First);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT,
                DSPICFG_L2_CACHE_LINE_SIZE);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Clear interrupts generated during scrubbing */
    retVal = ECCDspIntrGetErrStatus(&errStatus);
    ECCDspIntrClrErrStatus(&errStatus);

    /* Register interrupt handler */
    dspEccL2registerIntr();

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Configure Cache size of L1P as 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    /* The call to this function will lead to an ECC error as the L1P will
     * try to read the cache line corresponding to the corrupted dummyCodeL2First
     * function.
     */
    dummyVal = dummyCodeL2First(3U, 5U);
    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Since 3 < 5 the value is always 0 */
    retVal += dummyVal;

    /* Disable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    /* Clear interrupts generated during scrubbing */
    retVal = ECCDspIntrGetErrStatus(&errStatus);
    ECCDspIntrClrErrStatus(&errStatus);
    DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L1P);
    return retVal;
}

/* Function performs DSP ECC L2 DMA access error test
 */
static int32_t dspEccL2DmaAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;

    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L2 DMA Access Error Test", -1);

    gInterruptRecd = 0U;

    dspEccL2registerIntr();
    /* Fill the initialization pattern to some location in L2. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L2. This will be used
     * to test the L2 EDC for DMA access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A1A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Initialize memory using IDMA. Write the test pattern to L2 location */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* Corrupt memory using IDMA. Write the same test pattern with 1 bit error
     * to the same L2 location.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE  + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /*
     * This read will cause an error in the L2 DMA read error field. The error
     * should be a single bit error at the 26th bit and it is correctable.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE  + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE  + 0x8300);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    dspEccL2unregisterIntr();
    return retVal;
}

/* Function performs DSP ECC L2 Victim access error test
 */
static int32_t dspEccL2VictimAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U, address = 0U;
    eccDspErrStatus_t errStatus = {0U};
    gInterruptRecd = 0U;

    /* Configure Cache size of L1P as 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);

    /* Clear interrupts generated during scrubbing */
    retVal = ECCDspIntrGetErrStatus(&errStatus);
    ECCDspIntrClrErrStatus(&errStatus);

    UARTConfigPuts(uartBaseAddr, "\r\nDSP ECC L2 Victim Access Error Test", -1);

    dspEccL2registerIntr();
    /* Initialize DDR memory with the cache line size. This will lead to
     * 5 memory locations with below contents:
     * 0x82000400 - 11111111 00000000 00000000 ..... 128 bytes
     * 0x83000400 - 11111111 00000000 00000000 ..... 128 bytes
     * 0x84000400 - 11111111 00000000 00000000 ..... 128 bytes
     * 0x85000400 - 11111111 00000000 00000000 ..... 128 bytes
     * 0x86000400 - 11011111 00000000 00000000 ..... 128 bytes
     */
    address = (uint32_t)&dummyVar1;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar2;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar3;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar4;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar5;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    HW_WR_REG32((uint32_t)&dummyVar1, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar2, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar3, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar4, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar5, 0x11011111);

    /* Configure Cache size of L1D as disabled. We do not want the L1D to getarccoords
     * allocated.
     */
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Configure Cache size of L2 as 32K Cache. */
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_32K);
    /* Make the initialized DDR regions cachable. The variables are such that
     * they fall in the same L2 Cache set. Since the L2 cache supports 4 ways
     * each variable access will cause all 4 ways to be populated for the same
     * set.
     */
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar1,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar2,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar3,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar4,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar5,
                  DSPICFG_MAR_PC);
    /* Enable ECC for L2 */
    retVal = ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Fill up the L2 cache Ways */
    HW_RD_REG32((uint32_t)&dummyVar1);
    HW_RD_REG32((uint32_t)&dummyVar2);
    HW_RD_REG32((uint32_t)&dummyVar3);
    HW_RD_REG32((uint32_t)&dummyVar4);

    /* Suspend the ECC operation to corrupt L1P SRAM */
    retVal = ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* This will replace first way with least recently used policy. L2 cache
     * is read and write allocate.
     */
    HW_WR_REG32((uint32_t)&dummyVar5, 0x11011111);

    /* Re-enable the ECC operation */
    retVal = ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* This will generate an L2 Victim error at the 20th bit which is
     * correctable. The written value is then read by the L2 cache flush. This
     * mismatches with the previously stored ECC value for 0x11111111 and causes
     * the ECC error.
     */
    retVal = DSPICFGCacheWriteBackInvalidateAll(SOC_DSP_ICFG_BASE,
                                                DSPICFG_MEM_L2);

     /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC for L2 */
    retVal = ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_32K);
    /* Configure Cache size of L2 as 32K Cache. */
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_DISABLED);
    /* Configure Cache size of L1P as 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    dspEccL2unregisterIntr();
    return retVal;
}
