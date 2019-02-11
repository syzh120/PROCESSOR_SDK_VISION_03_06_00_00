/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file  mailbox_receiver.c
 * \brief This acts as mailbox receiver
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include "mailbox_app.h"
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define INTERRUPT_MODE  (0)
#define POLLED_MODE     (1)

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
/* Receiver Will run on A15 */
#define IRQ_CFG_REQUIRED        (0U)
#define MAILBOX_BASE_ADDRESS    CSL_MPU_MAILBOX2_REGS
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
/* Receiver Will run on A15 */
#define MAILBOX_IRQ_NO          (26U)
#define IRQ_CFG_REQUIRED        (1U)
#define IRQ_XBAR_CPU_ID         CSL_XBAR_IRQ_CPU_ID_MPU
#define IRQ_XBAR_INST_NO        XBAR_INST_MPU_IRQ_26
#define IRQ_XBAR_INDEX          CSL_XBAR_MAILBOX2_IRQ_USER0
#define MAILBOX_BASE_ADDRESS    SOC_MAILBOX2_BASE
#endif

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/* Receiver Will run on M4 */
#define MAILBOX_IRQ_NO          (50U)
#define IRQ_CFG_REQUIRED        (1U)
#define IRQ_XBAR_CPU_ID         CSL_XBAR_IRQ_CPU_ID_IPU1
#define IRQ_XBAR_INST_NO        XBAR_INST_IPU1_IRQ_50
#define IRQ_XBAR_INDEX          CSL_XBAR_MAILBOX2_IRQ_USER0
#define MAILBOX_BASE_ADDRESS    SOC_MAILBOX2_BASE
#endif

#define MAILBOX_USER            (0U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*To use UARTConfigPuts function for prints*/
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

volatile uint32_t gMsg  = 0, gMsgStatus = MESSAGE_INVALID;
volatile uint32_t gDone = 1;
uint32_t          gOpMode = 1;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if IRQ_CFG_REQUIRED
void mailboxisr(void *handle);
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
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

int main(void)
{
    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\nReceiver: Mailbox Application", -1);
#if IRQ_CFG_REQUIRED
    UARTConfigPuts(uartBaseAddr,
        "\r\nReceiver: Enter Operating mode\r\n0 - For Interrupt Mode\
         \r\n1 - For polled Mode\r\n$> ", -1);
    gOpMode = UARTConfigGetNum(uartBaseAddr);

    if ((gOpMode != POLLED_MODE) && (gOpMode != INTERRUPT_MODE))
    {
        UARTConfigPuts(uartBaseAddr,
		    "\r\nReceiver: Invalid Input. Defaulting to Interrupt Mode", -1);
        gOpMode = POLLED_MODE;
    }

    if (gOpMode == POLLED_MODE)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nReceiver:  Polled Mode", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\nReceiver: Interrupt Mode", -1);

        /* XBar configuration */
        CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID,IRQ_XBAR_INST_NO,
		                     IRQ_XBAR_INDEX);

        /* Register Mailbox interrupt for A15 */
        Intc_Init();
        Intc_IntEnable(0);
        Intc_IntRegister(MAILBOX_IRQ_NO, (IntrFuncPtr) mailboxisr, NULL);
        Intc_IntPrioritySet(MAILBOX_IRQ_NO, 1, 0);
        Intc_SystemEnable(MAILBOX_IRQ_NO);
#endif
        MailboxEnableNewMsgInt(MAILBOX_BASE_ADDRESS, MAILBOX_USER,
                            MAILBOX_QUEUE_0);
#if IRQ_CFG_REQUIRED
    }
#endif

    while (gDone)
    {
        if (gOpMode == POLLED_MODE)
        {
            while (gMsgStatus == MESSAGE_INVALID)
            {
                gMsgStatus =
                    MailboxGetMessage(MAILBOX_BASE_ADDRESS, MAILBOX_QUEUE_0,
                                        (uint32_t *) &gMsg);
            }
        }
        if (gMsgStatus == MESSAGE_VALID)
        {
            if (gMsg == MAILBOX_APP_A15_MSG)
            {
                UARTConfigPuts(uartBaseAddr,"\nReceiver: A15 Core is up", -1);
            }
            if (gMsg == MAILBOX_APP_DSP_MSG)
            {
                UARTConfigPuts(uartBaseAddr,"\nReceiver: DSP Core is up", -1);
            }
            if (gMsg == MAILBOX_APP_M4_MSG)
            {
                UARTConfigPuts(uartBaseAddr,"\nReceiver: M4 Core is up", -1);
            }
            gMsg       = 0;
            gMsgStatus = MESSAGE_INVALID;
        }
    }
    return 0;
}

#if IRQ_CFG_REQUIRED
void mailboxisr(void *handle)
{
    gMsgStatus = MailboxGetMessage(MAILBOX_BASE_ADDRESS, MAILBOX_QUEUE_0,
                                  (uint32_t *) &gMsg);

    /* clear mlb intr */
    MailboxClrNewMsgStatus(MAILBOX_BASE_ADDRESS, MAILBOX_USER, MAILBOX_QUEUE_0);
}
#endif
/********************************* End of file ******************************/

