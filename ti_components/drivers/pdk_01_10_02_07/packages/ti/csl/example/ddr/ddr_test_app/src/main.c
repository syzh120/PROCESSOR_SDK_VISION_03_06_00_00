/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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

/*
 * main.c
 */
#include "stdint.h"
#include "stdlib.h"
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>

#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/example/utils/common/inc/app_utils.h>
#include <ti/csl/arch/csl_arch.h>

/* Application header files */
#include <sample.h>

static void PlatformEDMAWkupDepEnable(void);
static void padConfig_prcmEnable();

#if defined (SOC_TDA3XX) || defined (SOC_TDA2EX)
#define DDR_BASE_ADDRESS  (0x80000000U)
#else
#define EMIF1_DDR_BASE_ADDRESS  (0x80000000U) /* EMIF1 DDR Base address */
#define EMIF2_DDR_BASE_ADDRESS  (0xA0000000U) /* EMIF2 DDR Base address */
#endif

uint32_t          edma_ch_num  = 1;
uint32_t          edma_tcc_num = 1;

uint32_t          edma_evtq_num = 0;

volatile uint32_t transfer_complete = 0;
uint32_t          region        = EDMA3_CC_REGION;
uint32_t          interrupt_num = EDMA3_CC_XFER_COMPLETION_INT;
#define EDMA_U_BASE (SOC_EDMA_TPCC_BASE_VIRT)

#if defined (__TI_ARM_V7M4__)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuffm, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuffm[BUFFER_SIZE];
#elif defined (__ARM_ARCH_7A__)
signed char __attribute__((section(".my_sect_ddr"))) _srcBuffm[MAX_BUFFER_SIZE];
#endif

uint32_t          base_address = EDMA_U_BASE;
uint32_t          ddr_base_address;
unsigned char     ddr_val;
uint32_t          gEnableAutorun = 0;
int8_t gMainMenuOption;
int32_t           gTestStatus = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif


void isrEdmaCompletion(void *handle);

static void padConfig_prcmEnable()
{
    AppUtils_setUartConsolePinMux();
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
}

static void PlatformEDMAWkupDepEnable(void)
{
    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC1_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC1_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC2_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC2_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPCC_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPCC_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }
}

int main(void)
{
    int32_t  getCharRetVal;
    int8_t   option;
    uint32_t testID = 0;

    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\r\nDDR Stress Test Application", -1);

    UARTConfigPuts(uartBaseAddr,
        "\r\nEnter any character for User Input else wait for few secs for AutoRun Option \r\n",
        -1);

    getCharRetVal = UARTConfigGetcTimeout(uartBaseAddr, &option, 10000U);
    if (STW_EFAIL == getCharRetVal)
    {
        /* Timeout - Enable Auto run Option */
        UARTConfigPuts(uartBaseAddr,"\r\nUART read timeout (10 sec). Enable Auto Run !!\r\n", -1);
        gEnableAutorun = 1;
    }

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    /* Do EDMA init Done once in the beginning of application */
    EDMAsetRegion(region);
    EDMA3Init(base_address, 0);

#if defined (__ARM_ARCH_7A__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,
                         EDMA3_CC_XFER_COMPLETION_INT_XBAR_INST,
                         CSL_XBAR_EDMA_TPCC_IRQ_REGION0);
#elif defined (__TI_ARM_V7M4__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,
                         EDMA3_CC_XFER_COMPLETION_INT_XBAR_INST,
                         CSL_XBAR_EDMA_TPCC_IRQ_REGION1);
#endif

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) isrEdmaCompletion, NULL);

    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);

    while (1)
    {
        if (gEnableAutorun == 0)
        {
#if defined (SOC_TDA3XX) || (defined (SOC_TDA2EX))
            ddr_base_address = DDR_BASE_ADDRESS; /* DDR BANK */
#else
            UARTConfigPuts(uartBaseAddr,"\r\nEnter the EMIF number to test:", -1);
            UARTConfigPuts(uartBaseAddr,"\r\nEnter 1 for EMIF1 and 2 for EMIF2:", -1);
            ddr_val = UARTConfigGetNum(uartBaseAddr);
            if (ddr_val == 1)
            {
                ddr_base_address = EMIF1_DDR_BASE_ADDRESS; /* DDR BANK 1 */
            }
            else if (ddr_val == 2)
            {
                ddr_base_address = EMIF2_DDR_BASE_ADDRESS;  /*DDR  BANK 2 */
            }
            else
            {
                UARTConfigPuts(uartBaseAddr,"\r\nEnter valid EMIF number for DDR test \r\n", -1);
                continue;
            }
#endif
        }
        else
        {
            testID++;
            if (testID == 1)
            {
#if !defined (SOC_TDA3XX) && !(defined (SOC_TDA2EX))
                UARTConfigPuts(uartBaseAddr,"\r\nDDR test - EMIF1 \r\n", -1);
                ddr_base_address = EMIF1_DDR_BASE_ADDRESS; /* DDR BANK 1 */
#else
                ddr_base_address = DDR_BASE_ADDRESS;       /* DDR BANK 1 */
#endif
            }
            else
            {
#if !defined (SOC_TDA3XX) && !(defined (SOC_TDA2EX))
                UARTConfigPuts(uartBaseAddr,"\r\nDDR test - EMIF2 \r\n", -1);
                ddr_base_address = EMIF2_DDR_BASE_ADDRESS; /* DDR BANK 1 */
#endif
            }
        }

        if (edma_mem_test1(ddr_base_address, edma_ch_num, edma_tcc_num,
                           edma_evtq_num, MAX_ACOUNT,
                           MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr," \r\nDDR-- Full memory read/write test is complete \r\n", -1);
        }

        if (edma_mem_test2(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                           MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr," \r\nDDR-- Random memory read/write test is complete \r\n",
                     -1);
        }
        if (edma_mem_test3(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                           MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr,"\r\nDDR-- Sequential memory read/write test is complete \r\n",
                     -1);
            UARTConfigPuts(uartBaseAddr,
                "==============================================================\r\n",
                -1);
        }
        if (edma_mem_test4(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                           MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr,"\r\nDDR-- Sequential increment pattern test is complete \r\n",
                     -1);
            UARTConfigPuts(uartBaseAddr,
                "==============================================================\r\n",
                -1);
        }
        if (gEnableAutorun == 0)
        {
            break;
        }
        else
        {
#if defined (SOC_TDA3XX) || (defined (SOC_TDA2EX))
            if (testID == 1)
            {
                break;
            }
#else
            if (testID == 2)
            {
                break;
            }
#endif
        }
    }

    if (gTestStatus == STW_SOK)
    {
        //StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
        UARTConfigPuts(uartBaseAddr,"\r\nDDR Stress Test Pass", -1);
    }
    else
    {
        //StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
        UARTConfigPuts(uartBaseAddr,"\r\nDDR Stress Test Fail", -1);
    }

    /* Disable the EDMA interrupt */
    Intc_SystemDisable(interrupt_num);
    Intc_IntUnregister(interrupt_num);

    return 0;
}

void isrEdmaCompletion(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(base_address, edma_tcc_num);
}
