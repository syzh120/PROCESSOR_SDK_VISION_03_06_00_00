/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_mmu.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#if defined (__TI_ARM_V7M4__)
#define MMU_FAULT_INT_NUM       (33)
#elif defined (__ARM_ARCH_7A__)
#define MMU_FAULT_INT_NUM       (28)
#endif

/*DSP Entry Point*/
#define DSP_ENTRY_POINT (0x8B000000)

#define DSP1BOOTADDR            (SOC_CTRL_MODULE_CORE_BASE + 0x55C)
#define DSP1BOOTADDRVALUE       (SOC_DSP1_L2_SRAM_BASE - 0x40000000)

#if defined (__TI_ARM_V7M4__)
#define IRQ_XBAR_CPU_ID         CSL_XBAR_IRQ_CPU_ID_IPU1
#define IRQ_XBAR_INST_NO        CSL_XBAR_INST_IPU1_IRQ_33
#define IRQ_XBAR_INDEX          CSL_XBAR_DSP1_IRQ_MMU0
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
void dspMmuFaultIsr();
int32_t DSP1SystemReset();
void DSP1BringUp(uint32_t EntryPoint);

volatile uint8_t mmuFault      = 0;
volatile int8_t  waitForMmuInt = 1;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

int main()
{
    volatile int8_t keepMainActive = 0;
    volatile int8_t done           = 1;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

#if defined (__TI_ARM_V7M4__)
    /* XBar configuration */
    CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID,IRQ_XBAR_INST_NO,
		                     IRQ_XBAR_INDEX);
#endif

#if defined (__ARM_ARCH_7A__)
    UARTConfigPuts(uartBaseAddr,"\r\n\r\nFrom A15", -1);
#elif defined (__TI_ARM_V7M4__)
    UARTConfigPuts(uartBaseAddr,"\r\n\r\nFrom M4", -1);
#endif
    UARTConfigPuts(uartBaseAddr,"\r\nDSP MMU fault test", -1);

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(MMU_FAULT_INT_NUM, (IntrFuncPtr) dspMmuFaultIsr, NULL);
    Intc_IntPrioritySet(MMU_FAULT_INT_NUM, 1, 0);
    Intc_SystemEnable(MMU_FAULT_INT_NUM);

    while (waitForMmuInt)
    {
        keepMainActive++;
    }

    while (done) ;

    return 0;
}

void dspMmuFaultIsr()
{
    uint32_t msgToDsp = (uint32_t) 'A';

    waitForMmuInt = 0;
#if defined (__ARM_ARCH_7A__)
    UARTConfigPuts(uartBaseAddr,"\r\n\r\nFrom A15 ISR", -1);
#elif defined (__TI_ARM_V7M4__)
    UARTConfigPuts(uartBaseAddr,"\r\n\r\nFrom M4 ISR", -1);
#endif
    UARTConfigPuts(uartBaseAddr,"\r\nMMU fault occurred", -1);

    /*Reset DSP1 Core*/
    DSP1SystemReset();

    MMUIrqClearStatus(SOC_DSP1_MMU0CFG_BASE, MMU_INT_All);
#if defined (__ARM_ARCH_7A__)
    UARTConfigPuts(uartBaseAddr,"\r\nDSP accessed fault address configured in DSP MMU from A15", -1);
#elif defined (__TI_ARM_V7M4__)
    UARTConfigPuts(uartBaseAddr,"\r\nDSP accessed fault address configured in DSP MMU from M4", -1);
#endif
    MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0, msgToDsp);

    /*Release DSP cores out of reset*/
    DSP1BringUp(DSP_ENTRY_POINT);
    UARTConfigPuts(uartBaseAddr,"\r\nDSP is out of reset", -1);
}

int32_t DSP1SystemReset()
{
    uint32_t CPU_PRM_BASE;
    uint32_t RM_CPU_RSTCTRL;
    uint32_t RM_CPU_RSTST;
    uint32_t tmpRegVal;

    CPU_PRM_BASE   = SOC_DSP1_PRM_BASE;
    RM_CPU_RSTCTRL = RM_DSP1_RSTCTRL;
    RM_CPU_RSTST   = RM_DSP1_RSTST;

    /*Assert the DSP1*/
    HW_WR_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL, 0x3);

    /*Check the Reset status & clear*/
    if ((HW_RD_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL) & 0x3) == 0x3)
    {
        HW_WR_REG32(CPU_PRM_BASE + RM_CPU_RSTST, 0x3);
    }

    /*Clear reset for MMU, Cache & Slave interface OCP port*/
    tmpRegVal  = HW_RD_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL);
    tmpRegVal &= ~0x2;
    HW_WR_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL, tmpRegVal);

    while ((HW_RD_REG32(CPU_PRM_BASE + RM_CPU_RSTST) & 0x2) != 0x2) ;

    return 0;
}

/**
 * \brief   DSP1BringUp function assert reset(CPU & DSP SS) , set the entry
 *          point & release the CPU from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void DSP1BringUp(uint32_t EntryPoint)
{
    uint8_t i;

    /*Set the Entry point*/
    if (EntryPoint == 0)
    {
        HW_WR_REG32(DSP1BOOTADDR, (DSP1BOOTADDRVALUE >> 0xA));
        for (i = 0; i < 8; i++) {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + 4 * i, 0x12); /*Write Self
                                                               * Branch
                                                               *Instruction*/
        }
    }
    else
    {
        HW_WR_REG32(DSP1BOOTADDR, (EntryPoint >> 0xA));
    }

    /*Bring-out of Reset*/
    HW_WR_REG32(SOC_DSP1_PRM_BASE + RM_DSP1_RSTCTRL, 0x0);
    while ((HW_RD_REG32(SOC_DSP1_PRM_BASE + RM_DSP1_RSTST) & 0x3) != 0x3)

        /*Check the Status of DSP1 Module mode*/
        while ((HW_RD_REG32(SOC_DSP1_CM_CORE_AON_BASE +
                            CM_DSP1_DSP1_CLKCTRL) & 0x30000) != 0x0) ;
}

