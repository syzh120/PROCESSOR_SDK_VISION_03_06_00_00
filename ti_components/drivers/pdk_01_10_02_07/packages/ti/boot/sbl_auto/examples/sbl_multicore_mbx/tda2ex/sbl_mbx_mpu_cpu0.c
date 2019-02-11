/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \file     sbl_mbx_mpu_cpu0.c
 *
 *  \brief    This file contains SBL multi-core mailbox binary for MPU CPU0.
 *
 *  \details   MPU CPU0 sends message to IPU1 CPU0, IPU1 CPU1 and DSP1. Each
 *             core sends an acknowledgement after receiving message.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/soc.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define MPU_CPU0_MAILBOX_MSG                           ((uint32_t) 0xFF33BB00U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t uartBaseAddr = SOC_UART1_BASE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
}


int main()
{
    uint32_t msg          = 0U;
    uint32_t ipu1Cpu0Flag = 0U;
    uint32_t ipu1Cpu1Flag = 0U;
    uint32_t dsp1Flag     = 0U;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\r\n Multi-core Mailbox Application: MPU Core0 Master core \r\n ",
             -1);

    /* Send message to IPU1 CPU0(MBX2_Q0) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                              MPU_CPU0_MAILBOX_MSG)) ;

    /* Send message to IPU1 CPU1(MBX2_Q1) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                              MPU_CPU0_MAILBOX_MSG)) ;

    /* Send message to DSP1(MBX2_Q2) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2,
                              MPU_CPU0_MAILBOX_MSG)) ;

    while ((ipu1Cpu0Flag != 1U) ||
           (ipu1Cpu1Flag != 1U) ||
           (dsp1Flag != 1U))
    {
        /* Read message from IPU1 CPU0 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3, &msg))
        {
            UARTConfigPuts(uartBaseAddr," \r\n IPU1 CPU0 booted-up successfully \r\n", -1);
            ipu1Cpu0Flag = 1U;
        }

        /* Read message from IPU1 CPU1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_4, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n IPU1 CPU1 booted-up successfully \r\n", -1);
            ipu1Cpu1Flag = 1U;
        }

        /* Read message from DSP1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n DSP1 booted-up successfully \r\n", -1);
            dsp1Flag = 1U;
        }
    }
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
