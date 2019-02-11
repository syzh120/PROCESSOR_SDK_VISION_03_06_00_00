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
 *  \file   main.c
 *
 *  \brief This file demonstrates UART console input and output.
 *         Expects user to enter an input string and outputs the same
 *         on console.
 *
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* Commented define TESTCASE_ID to test with default settings of
 * BAUD_RATE    = 115200,
 * WORD_LENGTH  = 8Bits,
 * STOP_BIT     = 1,
 * PARITY       = None.
 * Uncomment below define and set to appropriate test case number to test
 * specific configuration.
 */

/*
#define TESTCASE_ID     UART_19
*/

#if (TESTCASE_ID == UART_1)
#define BAUD_RATE       BAUD_RATE_9600
#endif

#if (TESTCASE_ID == UART_2)
#define BAUD_RATE       BAUD_RATE_14400
#endif

#if (TESTCASE_ID == UART_3)
#define BAUD_RATE       BAUD_RATE_19200
#endif

#if (TESTCASE_ID == UART_4)
#define BAUD_RATE       BAUD_RATE_38400
#endif

#if (TESTCASE_ID == UART_5)
#define BAUD_RATE       BAUD_RATE_57600
#endif

#if (TESTCASE_ID == UART_6)
#define BAUD_RATE       BAUD_RATE_115200
#endif

#if (TESTCASE_ID == UART_7)
#define BAUD_RATE       BAUD_RATE_230400
#endif

#if (TESTCASE_ID == UART_8)
#define BAUD_RATE       BAUD_RATE_460800
#define UART_MODE       UART_13x_MODE
#endif

#if (TESTCASE_ID == UART_9)
#define BAUD_RATE       BAUD_RATE_921600
#define UART_MODE       UART_13x_MODE
#endif

#if (TESTCASE_ID == UART_10)
#define WORD_LENGTH     UART_WORD_LENGTH_5
#endif

#if (TESTCASE_ID == UART_11)
#define WORD_LENGTH     UART_WORD_LENGTH_6
#endif

#if (TESTCASE_ID == UART_12)
#define WORD_LENGTH     UART_WORD_LENGTH_7
#endif

#if (TESTCASE_ID == UART_13)
#define WORD_LENGTH     UART_WORD_LENGTH_8
#endif

#if (TESTCASE_ID == UART_14)
#define STOP_BIT        UART_STOP_BIT_1
#endif

#if (TESTCASE_ID == UART_15)
#define STOP_BIT        UART_STOP_BIT_1_5_2
#define WORD_LENGTH     UART_WORD_LENGTH_5
#endif

#if (TESTCASE_ID == UART_16)
#define STOP_BIT        UART_STOP_BIT_1_5_2
#endif

#if (TESTCASE_ID == UART_17)
#define PARITY      UART_NO_PARITY
#endif

#if (TESTCASE_ID == UART_18)
#define PARITY      UART_PARITY_ODD
#endif

#if (TESTCASE_ID == UART_19)
#define PARITY      UART_PARTY_EVEN
#endif

#ifndef BAUD_RATE
#define BAUD_RATE       BAUD_RATE_115200
#endif

#ifndef WORD_LENGTH
#define WORD_LENGTH     UART_WORD_LENGTH_8
#endif

#ifndef STOP_BIT
#define STOP_BIT        UART_STOP_BIT_1
#endif

#ifndef PARITY
#define PARITY          UART_NO_PARITY
#endif

#ifndef UART_MODE
#define UART_MODE       UART_16x_MODE
#endif

#define UART_INST_NUM                    (1U)
uint32_t uartBaseAddr;
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

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
    UARTConfigInit(uartBaseAddr, BAUD_RATE, WORD_LENGTH, STOP_BIT, PARITY,
                    UART_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE, WORD_LENGTH, STOP_BIT, PARITY,
                    UART_MODE);
#endif
}

int main(void)
{
    char     dataBuffer[100];
    uartBaseAddr = SOC_UART1_BASE;

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uartBaseAddr = SOC_UART3_BASE;
#endif
#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
    uartBaseAddr = SOC_UART3_BASE;
#endif

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    /* UART receive and transmit operation */
    UARTConfigPuts(uartBaseAddr, "\nUART Test", -1);

    UARTConfigPuts(uartBaseAddr, "\nEnter some data to transmit:", -1);

    UARTConfigGets(uartBaseAddr, &dataBuffer[0], -1);

    UARTConfigPuts(uartBaseAddr, "\nData Received:", -1);

    UARTConfigPuts(uartBaseAddr, &dataBuffer[0], -1);

    UARTConfigPuts(uartBaseAddr, "\nUART Test Completed", -1);

    return 0;
}
/********************************* End of file ******************************/
