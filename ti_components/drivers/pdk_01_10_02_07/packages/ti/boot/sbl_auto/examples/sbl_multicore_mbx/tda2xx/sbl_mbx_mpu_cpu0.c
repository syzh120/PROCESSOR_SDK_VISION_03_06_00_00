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

/*
 * main.c
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

#define MPU_MBX_MAGIC_STR  0xFF33BB00

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

int main(void) {
    uint32_t msg = 0;
    uint32_t IPU1_CPU0_Flag = 0;
    uint32_t IPU1_CPU1_Flag = 0;
    uint32_t IPU2_CPU0_Flag = 0;
    uint32_t IPU2_CPU1_Flag = 0;
    uint32_t DSP1_Flag      = 0;
    uint32_t DSP2_Flag      = 0;
    uint32_t EVE1_Flag      = 0;
    uint32_t EVE2_Flag      = 0;
    uint32_t EVE3_Flag      = 0;
    uint32_t EVE4_Flag      = 0;
    uint32_t MPU_CPU1_Flag  = 0;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();


    UARTConfigPuts(uartBaseAddr,"\r\nMulticore Mailbox app - MPU-Core0 Master core \r\n ", -1);

    /* Send message to IPU1_CPU0(MBX2_Q0) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to IPU1_CPU1(MBX2_Q1) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to IPU2_CPU0(MBX2_Q2) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to IPU2_CPU1(MBX2_Q3) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to DSP1(MBX2_Q4) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_4,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to DSP2(MBX2_Q5) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to EVE1(MBX2_Q6) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_6,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to EVE2(MBX2_Q7) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_7,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to EVE3(MBX2_Q8) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_8,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to EVE4(MBX2_Q9) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_9,
                              MPU_MBX_MAGIC_STR)) ;

    /* Send message to MPU_CPU1(MBX2_Q10) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_10,
                              MPU_MBX_MAGIC_STR)) ;

    while (1)
    {
        /* Read message from IPU1_CPU0 */
        if (!IPU1_CPU0_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX3_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr," \r\n IPU1_CPU0 boot-up successfully \r\n", -1);

            IPU1_CPU0_Flag = 1;
        }

        /* Read message from IPU1_CPU1 */
        if (!IPU1_CPU1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX4_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n IPU1_CPU1 boot-up successfully \r\n", -1);
            IPU1_CPU1_Flag = 1;
        }

        /* Read message from IPU2_CPU0 */

        if (!IPU2_CPU0_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX5_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n IPU2_CPU0 boot-up successfully \r\n", -1);
            IPU2_CPU0_Flag = 1;
        }

        /* Read message from IPU2_CPU1 */
        if (!IPU2_CPU1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX6_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n IPU2_CPU1 boot-up successfully \r\n", -1);
            IPU2_CPU1_Flag = 1;
        }

        /* Read message from DSP1 */
        if (!DSP1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX7_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n DSP1 boot-up successfully \r\n", -1);
            DSP1_Flag = 1;
        }

        /* Read message from DSP2 */
        if (!DSP2_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX8_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n DSP2 boot-up successfully \r\n", -1);
            DSP2_Flag = 1;
        }

        /* Read message from EVE1 */
        if (!EVE1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX9_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n EVE1 boot-up successfully \r\n", -1);
            EVE1_Flag = 1;
        }

        /* Read message from EVE2 */
        if (!EVE2_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX10_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n EVE2 boot-up successfully \r\n", -1);
            EVE2_Flag = 1;
        }

        /* Read message from EVE3 */
        if (!EVE3_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX11_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n EVE3 boot-up successfully \r\n", -1);
            EVE3_Flag = 1;
        }

        /* Read message from EVE4 */
        if (!EVE4_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX12_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n EVE4 boot-up successfully \r\n", -1);
            EVE4_Flag = 1;
        }

        /* Read message from MPU_CPU1 */
        if (!MPU_CPU1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_11, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n MPU CPU1 boot-up successfully \r\n", -1);
            MPU_CPU1_Flag = 1;
        }
    }
    return 0;
}

