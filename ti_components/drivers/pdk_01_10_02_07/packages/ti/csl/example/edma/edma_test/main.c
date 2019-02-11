/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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
 *  \file   main.c
 *
 *  \brief This file demonstrates polled mode of dma transfer mechanism.
 *         Buffers (src and dest) are needed for mem-2-mem data transfers.
 *         This define is for the MAXIMUM size and hence the maximum data
 *         which could be transferred using the sample test case below.
 *
 *  \copyright Copyright (C) 2013 Texas Instruments Incorporated -
 *             http://www.ti.com/
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#if defined (__ARM_ARCH_7A__)
#include <ti/csl/csl_a15.h>
#endif
#include <ti/csl/soc.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/example/edma/edma_test/sample.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#if defined (__ARM_ARCH_7A__)
#define IRQ_XBAR_INST_NO XBAR_INST_MPU_IRQ_12
#elif defined (__TI_ARM_V7M4__)
#define IRQ_XBAR_INST_NO XBAR_INST_IPU1_IRQ_34
#elif defined (_TMS320C6X)
#define IRQ_XBAR_INST_NO XBAR_INST_DSP1_IRQ_38
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM571x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#if defined (_TMS320C6X)
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define EDMA_U_BASE CSL_DSP_EDMA_CC_REGS
#else
#define EDMA_U_BASE SOC_EDMA_CC_BASE
#endif
#else
#define EDMA_U_BASE SOC_EDMA_TPCC_BASE_VIRT
#endif
#endif

#if !defined (__ARM_ARCH_7A__) && !defined (BUILD_GCC)

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuff1[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _dstBuff1[MAX_BUFFER_SIZE];

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuff2[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _dstBuff2[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff3, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuff3[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff3, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _dstBuff3[MAX_BUFFER_SIZE];
#endif
#else
signed char __attribute__((section(".my_sect_ddr"))) _srcBuff1[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstBuff1[MAX_BUFFER_SIZE];
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
signed char __attribute__((section(".my_sect_ddr"))) _srcBuff2[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstBuff2[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _srcBuff3[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstBuff3[MAX_BUFFER_SIZE];
#endif
#endif


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

uint32_t          edma_ch_num   = 1;
uint32_t          edma_tcc_num  = 1;
uint32_t          edma_evtq_num = 0;

uint32_t          region        = EDMA3_CC_REGION;

signed char      *srcBuff1;
signed char      *dstBuff1;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
uint32_t          qdma_ch_num1 = 1;
uint32_t          qdma_ch_num2 = 2;

uint32_t          edma_ch_num2  = 2;
uint32_t          edma_tcc_num2 = 2;

uint32_t          edma_paRAMId2 = 70;
uint32_t          edma_paRAMId3 = 80;

signed char      *srcBuff2;
signed char      *dstBuff2;
signed char      *srcBuff3;
signed char      *dstBuff3;

uint32_t          qdma_paramid1;
uint32_t          qdma_paramid2;
uint32_t          qdma_paramid3;

volatile uint32_t transfer_complete = 0;

uint32_t          interrupt_num = EDMA3_CC_XFER_COMPLETION_INT;
#endif

uint32_t          base_address = EDMA_U_BASE;
int32_t           gTestStatus  = STW_SOK;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
void isrEdmaCompletion(void *handle);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO |
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
}

int main(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#if defined (__TI_ARM_V7M4__) && defined (TDA2XX_BUILD)
    StwUtils_appConfigIPU1DefaultAMMU();
#endif

    qdma_paramid1 = (edma_ch_num + SOC_EDMA3_NUM_DMACH);
    qdma_paramid2 = (edma_ch_num + SOC_EDMA3_NUM_DMACH + 1);
    qdma_paramid3 = (edma_ch_num + SOC_EDMA3_NUM_DMACH + 2);
#endif

    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\nEDMA App", -1);

    EDMAsetRegion(region);

    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(base_address, 0);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#ifdef __ARM_ARCH_7A__
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,IRQ_XBAR_INST_NO,CSL_XBAR_EDMA_TPCC_IRQ_REGION0);
#elif defined (__TI_ARM_V7M4__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,IRQ_XBAR_INST_NO,CSL_XBAR_EDMA_TPCC_IRQ_REGION1);
#elif defined (_TMS320C6X)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1,IRQ_XBAR_INST_NO,CSL_XBAR_EDMA_TPCC_IRQ_REGION2);
#endif

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) isrEdmaCompletion, NULL);

    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);

    if (dma_test(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                 MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nEDMA test First time transfer is complete", -1);
    }

    /* Do a EDMA DeInit and try the same transfer again */
    EDMA3Deinit(base_address, 0);
    EDMA3Init(base_address, 0);

    if (dma_test(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                 MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nEDMA test Second time transfer is complete", -1);
    }

    if (dma_chain_test(edma_ch_num, edma_tcc_num, edma_evtq_num, edma_ch_num2,
                       edma_tcc_num2, edma_evtq_num, MAX_ACOUNT, MAX_BCOUNT,
                       MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nEDMA chain test transfer is complete", -1);
    }

    if (dma_ping_pong_test(edma_ch_num, edma_tcc_num, edma_evtq_num,
                           edma_paRAMId2, edma_paRAMId3) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nDMA ping pong buffer test is complete", -1);
    }

    if (dma_link_test(edma_ch_num, edma_tcc_num, edma_evtq_num, edma_paRAMId2,
                      edma_paRAMId3, MAX_ACOUNT, MAX_BCOUNT,
                      MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nEDMA link test transfer is complete", -1);
    }
    if (qdma_test(qdma_ch_num1, edma_tcc_num, edma_evtq_num, qdma_paramid1,
                  MAX_ACOUNT,
                  MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nQDMA test transfer is complete", -1);
    }

    /* Disable the EDMA interrupt */
    Intc_SystemDisable(interrupt_num);
    Intc_IntUnregister(interrupt_num);
#endif

    if (dma_polled(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                   MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\nEDMA polled test transfer is complete", -1);
    }
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
    if (qdma_link_test(qdma_ch_num2, edma_tcc_num, edma_evtq_num, qdma_paramid2,
                       qdma_paramid3, MAX_ACOUNT,
                       MAX_BCOUNT, MAX_CCOUNT) == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nQDMA link test transfer is complete", -1);
    }
#endif
    EDMA3Deinit(base_address, 0);

    if (gTestStatus == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nEDMA Test Pass", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\nEDMA Test Fail", -1);
    }

    return 0;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
void isrEdmaCompletion(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(base_address, edma_tcc_num);
    EDMA3ClrIntr(base_address, edma_tcc_num2);
}
#endif

/********************************* End of file ******************************/
