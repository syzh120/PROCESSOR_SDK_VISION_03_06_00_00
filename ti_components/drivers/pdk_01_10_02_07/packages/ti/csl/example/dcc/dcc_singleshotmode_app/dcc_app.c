/*
 *   Copyright (c) Texas Instruments Incorporated 2015-2016
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
 *  \file     dcc_app.c
 *
 *  \brief    This file contains DCC test code for single shot mode.
 *            DPLLDSP_GMAC_H12 clock is used as clock to be tested against
 *            SYS_CLK1 which is reference clock.
 *
 *  \details  DCC operational mode is set to single shot mode.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dcc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_dcc.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_DCC_MODULE_INST             (SOC_DCC4_BASE)
#define APP_DCC_MODE                    (DCC_OPERATION_MODE_SINGLE_SHOT2)
#define APP_DCC_CLK_SRC0                (DCC_CLK_SRC0_SYS_CLK1)
#define APP_DCC_CLK_SRC1                (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12)
#define APP_DCC_CLK_SRC1_DRIFT          (5U)
#define APP_SYS_CLK1_FREQ_KHZ           ((uint32_t) 20000)
#define DCC_SRC0_COUNT_MAX              (0xFFFFFU)
#define DCC_SRC0_VALID_MAX              (0x0FFFFU)
#define DCC_SRC1_COUNT_MAX              (0xFFFFFU)
#define APP_DCC_DPLL_POST_DIV_MAX       (64U)

#define APP_DCC_ERROR_INT_M4                 (44U)
#define APP_DCC_DONE_INT_M4                  (45U)
#ifdef BUILD_IPU1
    #define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INST_DONE                  (CSL_XBAR_INST_IPU1_IRQ_45)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_DCC4_IRQ_ERROR)
    #define APP_XBAR_INTR_SOURCE_DONE           (CSL_XBAR_DCC4_IRQ_DONE)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t isrFlag = 0U, lastIntr = 2;

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   intrType        Interrupt for which crossbar is to be configured.
 *                          Refer enum #dccIntrType_t.
 *
 * \retval  status          Configuration status.
 */
static uint32_t DCCAppXBarConfig(uint32_t intrType);

/**
 * \brief   This Interrupt Service Routine for DCC error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DCCAppErrorIntrISR(void *handle);

/**
 * \brief   This Interrupt Service Routine for DCC DONE interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DCCAppDoneIntrISR(void *handle);

/**
 * \brief   This function returns reference clock frequency.
 *
 * \param   refClk          Clock whose frequency to be calculated.
 *
 * \retval  frequency       Frequency of the given clock in KHz.
 */
static uint32_t DCCAppGetTestClkfreqKHz(uint32_t refClk);

/**
 * \brief   This function changes the test clock frequency.
 *
 * \param   None
 *
 * \retval  status          Configuration status.
 */
static int32_t DCCAppTestClkFreqChange(void);

/**
 * \brief   This function returns seed value for COUNT1.
 *
 * \param   refClkFreq      Reference clock frequency in KHz.
 * \param   testClkFreq     Test clock frequency in KHz.
 * \param   refClkRatioNum  Reference clock ratio number.
 * \param   testClkRatioNum Test clock ratio number.
 * \param   drfitPer        Allowed drift in test clock in percentage.
 * \param   configParams    DCC configuration parameters.
 *                          Refer enum #dccConfigParams_t.
 *
 * \retval  None.
 */
static void DCCAppSetSeedVals(uint32_t           refClkFreq,
                              uint32_t           testClkFreq,
                              uint32_t           refClkRatioNum,
                              uint32_t           testClkRatioNum,
                              uint32_t           drfitPer,
                              dccConfigParams_t *configParams);

/**
 * \brief   This function returns least integral ratio for given clocks.
 *
 * \param   refClkFreq      Reference clock frequency in KHz.
 * \param   testClkFreq     Test clock frequency in KHz.
 * \param   refClkRatioNum  Reference clock ratio number.
 * \param   testClkRatioNum Test clock ratio number.
 *
 * \retval  None.
 */
static void DCCAppGetClkRatio(uint32_t  refClkFreq,
                              uint32_t  testClkFreq,
                              uint32_t *refClkRatioNum,
                              uint32_t *testClkRatioNum);

/**
 * \brief   This function is used for misc configuration needed by DCC App.
 *
 * \param   none.
 *
 * \retval  none.
 */
void DCCAppMiscConfig(uint32_t clksrc);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
#endif
}

int main(void)
{
    int32_t           configStatus;
    uint32_t          xBarStatus, testClkFreq, refClkRatioNum,
                      testClkRatioNum, refClkFreq;
    dccConfigParams_t configParams;

    /* Do Pad Config for UART */
    padConfig_prcmEnable();
    /* Initialize the UART Instance */
   /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
    UARTConfigPuts(uartBaseAddr,"\nStarting application...\n", -1);

    refClkFreq = APP_SYS_CLK1_FREQ_KHZ;
    /* Get the test clock frequency */
    testClkFreq = DCCAppGetTestClkfreqKHz(APP_DCC_CLK_SRC1);
    if (0U == testClkFreq)
    {
        UARTConfigPuts(uartBaseAddr,"Error in calculating Frequency.\n", -1);
    }
    /* Get clock ratio */
    DCCAppGetClkRatio(refClkFreq,
                      testClkFreq,
                      &refClkRatioNum,
                      &testClkRatioNum);

    DCCAppMiscConfig(APP_DCC_CLK_SRC1);
    /* Initialize DCC configuration parameters */
    configParams.mode    = APP_DCC_MODE;
    configParams.clkSrc0 = APP_DCC_CLK_SRC0;
    configParams.clkSrc1 = APP_DCC_CLK_SRC1;
    configParams.alternateClkSrc1 = FALSE;
    /* Get the seed values for given clock selections and allowed drift */
    DCCAppSetSeedVals(refClkFreq,
                      testClkFreq,
                      refClkRatioNum,
                      testClkRatioNum,
                      APP_DCC_CLK_SRC1_DRIFT,
                      &configParams);

    /* Configure XBar and interrupt */
    Intc_Init();
    xBarStatus  = DCCAppXBarConfig(DCC_INTERRUPTS_ERROR);
    xBarStatus |= DCCAppXBarConfig(DCC_INTERRUPTS_DONE);
    if (TRUE == xBarStatus)
    {
        /* Enable DCC module */
        HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER3_DCC4_CLKCTRL,
                    CM_L4PER3_DCC4_CLKCTRL_MODULEMODE,
                    CM_L4PER3_DCC4_CLKCTRL_MODULEMODE_ENABLE);
        while (CM_L4PER3_DCC4_CLKCTRL_IDLEST_FUNC !=
            HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER3_DCC4_CLKCTRL,
                            CM_L4PER3_DCC4_CLKCTRL_IDLEST))
        {
            /* Wait till DCC module is enabled */
        }

        UARTConfigPuts(uartBaseAddr,"Module enabled.\n", -1);
        /* Configure DCC module */
        configStatus = DCCSetConfig(APP_DCC_MODULE_INST, &configParams);
        if (STW_EFAIL == configStatus)
        {
            UARTConfigPuts(uartBaseAddr,"ERROR in DCC configuration.\n", -1);
        }
        else
        {
            /* Enable DCC interrupts */
            DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_ERROR);
            DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
            /* Enable DCC operation/module */
            DCCEnable(APP_DCC_MODULE_INST, TRUE);
            /* Wait here till interrupt is generated */
            while (0U == isrFlag) ;
            if (1U == lastIntr)
            {
                isrFlag = 0U;
                /* Change test clock frequency */
                if (FALSE == DCCAppTestClkFreqChange())
                {
                    /* Error in configuration */
                }
                /* Configure DCC module */
                configStatus = DCCSetConfig(APP_DCC_MODULE_INST,
                                            &configParams);
                if (STW_EFAIL == configStatus)
                {
                    UARTConfigPuts(uartBaseAddr,"ERROR in DCC configuration.\n", -1);
                }
                else
                {
                    /* Enable DCC interrupts */
                    DCCEnableIntr(APP_DCC_MODULE_INST,
                                  DCC_INTERRUPTS_ERROR);
                    DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
                    /* Enable DCC operation/module */
                    DCCEnable(APP_DCC_MODULE_INST, TRUE);
                    /* Wait here till interrupt is generated */
                    while (0U == isrFlag) ;
                    isrFlag = 0U;
                    if (0U == lastIntr)
                    {
                        UARTConfigPuts(uartBaseAddr,"Application successfully executed.\n",
                                 -1);
                    }
                    else
                    {
                        UARTConfigPuts(uartBaseAddr,"Try to run application again.\n",
                                 -1);
                    }
                }
            }
            else
            {
                UARTConfigPuts(uartBaseAddr,"Try to run application again.\n", -1);
            }
        }
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static uint32_t DCCAppXBarConfig(uint32_t intrType)
{
    uint32_t status = FALSE;

    /* Configure Cross bar instance and interrupt */
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
                CSL_xbarIrqConfigure(APP_XBAR_CPU,APP_XBAR_INST_ERROR,APP_XBAR_INTR_SOURCE_ERROR);
                /* Successfully configured CrossBar */
                status = TRUE;
            if (TRUE == status)
            {
                /* Enable Error interrupt for DCC */
                Intc_IntEnable(APP_DCC_ERROR_INT_M4);

                /* Register ISR */
                Intc_IntRegister(APP_DCC_ERROR_INT_M4,
                                 (IntrFuncPtr) DCCAppErrorIntrISR, 0);
                Intc_IntPrioritySet(APP_DCC_ERROR_INT_M4, 1, 0);
                Intc_SystemEnable(APP_DCC_ERROR_INT_M4);
            }
            break;
        case DCC_INTERRUPTS_DONE:
                CSL_xbarIrqConfigure(APP_XBAR_CPU,APP_XBAR_INST_DONE,APP_XBAR_INTR_SOURCE_DONE);
                /* Successfully configured CrossBar */
                status = TRUE;
            if (TRUE == status)
            {
                /* Enable Done and Error interrupt for DCC */
                Intc_IntEnable(APP_DCC_DONE_INT_M4);

                /* Register ISR */
                Intc_IntRegister(APP_DCC_DONE_INT_M4,
                                 (IntrFuncPtr) DCCAppDoneIntrISR, 0);
                Intc_IntPrioritySet(APP_DCC_DONE_INT_M4, 1, 0);
                Intc_SystemEnable(APP_DCC_DONE_INT_M4);
            }
            break;
        default:
            status = FALSE;
            break;
    }
    return status;
}

static void DCCAppErrorIntrISR(void *handle)
{
    UARTConfigPuts(uartBaseAddr,"In ISR...\n", -1);
    UARTConfigPuts(uartBaseAddr,"ERROR interrupt generated.\n", -1);
    DCCClearIntrStatus(APP_DCC_MODULE_INST, DCC_INTERRUPTS_ERROR);
    isrFlag  = 1U;
    lastIntr = 0U;
}

static void DCCAppDoneIntrISR(void *handle)
{
    UARTConfigPuts(uartBaseAddr,"In ISR...\n", -1);
    UARTConfigPuts(uartBaseAddr,"DONE interrupt generated.\n", -1);
    DCCClearIntrStatus(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
    isrFlag  = 1U;
    lastIntr = 1U;
}

static uint32_t DCCAppGetTestClkfreqKHz(uint32_t refClk)
{
    uint32_t multilpier = 1, divider = 1, postDivider;
    uint32_t clkFreqKHz = 0U;

    multilpier = 250U;
    divider    = 4U;
    postDivider = HW_RD_FIELD32(SOC_CKGEN_CM_CORE_AON_BASE+CM_DIV_H12_DPLL_DSP_GMAC,
                                CM_DIV_H12_DPLL_DSP_GMAC_DIVHS);
    clkFreqKHz  = (2 * multilpier * APP_SYS_CLK1_FREQ_KHZ / (postDivider)
                   / (divider + 1));
    return clkFreqKHz;
}

static void DCCAppSetSeedVals(uint32_t           refClkFreq,
                              uint32_t           testClkFreq,
                              uint32_t           refClkRatioNum,
                              uint32_t           testClkRatioNum,
                              uint32_t           drfitPer,
                              dccConfigParams_t *configParams)
{
    uint32_t maxFreqKHz, maxCntLimit;
    uint32_t maxRefCnt, minRefCnt;
    uint64_t mulVar;

    /* Find maximum frequency between test and reference clock */
    if (refClkFreq > testClkFreq)
    {
        maxFreqKHz  = refClkFreq;
        maxCntLimit = DCC_SRC0_COUNT_MAX;
    }
    else
    {
        maxFreqKHz  = testClkFreq;
        maxCntLimit = DCC_SRC1_COUNT_MAX;
    }
    /* Calculate seed values for 0% drift */
    if (maxFreqKHz == refClkFreq)
    {
        configParams->seedSrc0 = maxCntLimit / refClkRatioNum;
        configParams->seedSrc0 = configParams->seedSrc0 * refClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc0) *
                  (uint32_t) (testClkRatioNum));
        configParams->seedSrc1   = (uint32_t) (mulVar / refClkRatioNum);
        configParams->seedValid0 = refClkRatioNum;
    }
    else
    {
        configParams->seedSrc1 = maxCntLimit / testClkRatioNum;
        configParams->seedSrc1 = configParams->seedSrc1 * testClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc1) *
                  (uint32_t) (refClkRatioNum));
        configParams->seedSrc0   = (uint32_t) (mulVar / testClkRatioNum);
        configParams->seedValid0 = 1U;
    }
    /* Applying allowed drift */
    if (((DCC_SRC0_COUNT_MAX + DCC_SRC0_VALID_MAX) <
         (configParams->seedSrc0 * (100U + drfitPer) / 100U)))
    {
        /* Seed values with drift exceeds maximum range */
        UARTConfigPuts(uartBaseAddr,"Seed values with drift exceeds allowed range.\n", -1);
        UARTConfigPuts(uartBaseAddr,"Application will run with 0% allowed drift.\n", -1);
    }
    else if (100U < drfitPer)
    {
        /* Error percentage is greater than 100 */
        UARTConfigPuts(uartBaseAddr,"Wrong drift percentage. Not applying drift.\n", -1);
        UARTConfigPuts(uartBaseAddr,"Application will run with 0% allowed drift.\n", -1);
    }
    else
    {
        maxRefCnt = (configParams->seedSrc0 * (100U + drfitPer) / 100U);
        minRefCnt = (configParams->seedSrc0 * (100U - drfitPer) / 100U);
        if (DCC_SRC0_VALID_MAX < (maxRefCnt - minRefCnt))
        {
            UARTConfigPuts(uartBaseAddr,"Seed value for valid count exceeds allowed range.\n", -1);
            UARTConfigPuts(uartBaseAddr,"Application will run with 0% allowed drift.\n", -1);
        }
        else
        {
            if (maxRefCnt == minRefCnt)
            {
                configParams->seedValid0 = 1U;
            }
            else
            {
                configParams->seedSrc0   = minRefCnt;
                configParams->seedValid0 = (maxRefCnt - minRefCnt);
            }
        }
    }
    UARTConfigPuts(uartBaseAddr,"Seed values calculation done.\n", -1);
}

static int32_t DCCAppTestClkFreqChange(void)
{
    uint32_t postDivider;
    uint32_t status = TRUE;

    postDivider = HW_RD_FIELD32(SOC_CKGEN_CM_CORE_AON_BASE+CM_DIV_H12_DPLL_DSP_GMAC,
                                CM_DIV_H12_DPLL_DSP_GMAC_DIVHS);
    postDivider++;
    /* Make sure the post div value doesnot go beyond max allowed value. */
    postDivider %= APP_DCC_DPLL_POST_DIV_MAX;

    HW_WR_FIELD32(SOC_CKGEN_CM_CORE_AON_BASE+CM_DIV_H12_DPLL_DSP_GMAC,
                  CM_DIV_H12_DPLL_DSP_GMAC_DIVHS,
                  postDivider);
    UARTConfigPuts(uartBaseAddr,"Frequency configuration successful.\n", -1);
    return status;
}

static void DCCAppGetClkRatio(uint32_t  refClkFreq,
                              uint32_t  testClkFreq,
                              uint32_t *refClkRatioNum,
                              uint32_t *testClkRatioNum)
{
    uint32_t loopCnt, hcf = 1U;

    for (loopCnt = 1;
         (loopCnt <= refClkFreq) || (loopCnt <= testClkFreq);
         loopCnt++)
    {
        if ((refClkFreq % loopCnt == 0) && (testClkFreq % loopCnt == 0))
        {
            hcf = loopCnt;
        }
    }
    *refClkRatioNum  = (refClkFreq / hcf);
    *testClkRatioNum = (testClkFreq / hcf);
}

void DCCAppMiscConfig(uint32_t clksrc)
{
    if (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12 == clksrc)
    {
        /* Enable CPGMAC for DPLLCORE_M2 */
        HW_WR_FIELD32(SOC_L3INIT_CM_CORE_BASE+CM_GMAC_GMAC_CLKCTRL,
                      CM_GMAC_GMAC_CLKCTRL_MODULEMODE,
                      CM_GMAC_GMAC_CLKCTRL_MODULEMODE_ENABLED);
        while (CM_GMAC_GMAC_CLKCTRL_IDLEST_FUNC !=
               HW_RD_FIELD32(SOC_L3INIT_CM_CORE_BASE+CM_GMAC_GMAC_CLKCTRL,
                             CM_GMAC_GMAC_CLKCTRL_IDLEST))
        {
            /* Wait till CPGMAC module is enabled */
        }

        UARTConfigPuts(uartBaseAddr,"Misc Config done.\n", -1);
    }
}
/********************************* End of file ******************************/
