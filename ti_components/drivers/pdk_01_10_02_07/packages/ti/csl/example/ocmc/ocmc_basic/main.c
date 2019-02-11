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

#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_ocmc_ecc.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

static void uart_val_print(uint32_t val, char *mess)
{
    UARTConfigPuts(uartBaseAddr, mess, -1);
    UARTConfigPutHexNum(uartBaseAddr, val);
}

int main(void)
{
    uint32_t  virtStartAddr;
    uint32_t  val = 0;
    uint32_t *read_addr;
    uint32_t  msgfromSender;

    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);

    while (1)
    {
        /* Send virtual start address cmd*/
        val = 0x2233;

        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &virtStartAddr))) ;

        /*Wait for message from M4 for 1st slice*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &msgfromSender))) ;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
        uart_val_print(virtStartAddr, "\r\nVirtual start addr A15 = ");
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        uart_val_print(virtStartAddr, "\r\nVirtual start addr C66x = ");
#endif
        read_addr = (uint32_t *) (virtStartAddr);
        UARTConfigPuts(uartBaseAddr, "\r\n 1st slice = ", -1);
        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        /* Read 1st slice complete - send message */
        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);

        /*Wait for message from M4 for 2nd slice*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &msgfromSender))) ;
        UARTConfigPuts(uartBaseAddr, "\r\n 2nd slice = ", -1);
        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        /* Read 2nd slice complete - send message */
        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);

        /*Wait for message from M4 for 3rd slice*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &msgfromSender))) ;
        UARTConfigPuts(uartBaseAddr, "\r\n 3rd slice = ", -1);
        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        /* Read 3rd slice complete - send message */
        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);
    }
}

