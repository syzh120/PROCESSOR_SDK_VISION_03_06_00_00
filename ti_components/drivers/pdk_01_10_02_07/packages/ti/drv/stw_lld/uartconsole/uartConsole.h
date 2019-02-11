/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file   uartConsole.h
 *
 * \brief  This file contains the prototypes of the UART Console APIs.
 */

#ifndef UART_CONSOLE_H_
#define UART_CONSOLE_H_

#include <ti/csl/csl_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ZebuConfig 0

#define BAUD_RATE_115200          (115200U)
#define BAUD_RATE_3686400         (3686400U)
#define UART_MODULE_INPUT_CLK     (48000000U)

/* For UARTConsole to work on Zebu change the baud rate and oper mode */
#if ZebuConfig
#define BAUD_RATE                 (BAUD_RATE_3686400)
#else
#define BAUD_RATE                 (BAUD_RATE_115200)
#endif

#if defined (ZebuConfig)
#define OPER_MODE                 (UART13x_OPER_MODE)
#else
#define OPER_MODE                 (UART16x_OPER_MODE)
#endif

#define UART_LCR_NB_STOP_1BIT   (0x0U)
#define UART_LCR_CHAR_LENGTH_8BIT   (0x3U)

void UARTConsolePutc(uint8_t data);
uint8_t UARTConsoleGetc(void);
void UARTConsoleInit(UART_INST_t num);
uint32_t UART_Init(UART_INST_t num);
uint32_t UARTConsoleConfigInit(UART_INST_t num,
                               uint32_t    baudRate,
                               uint32_t    operMode,
                               uint32_t    parity,
                               uint32_t    wordLen,
                               uint32_t    stopBit);
void UARTConsoleWaitUntilTransmitComplete(void);
int8_t UARTConsoleGetcNonBlocking(void);
#ifdef __cplusplus
}
#endif
#endif

