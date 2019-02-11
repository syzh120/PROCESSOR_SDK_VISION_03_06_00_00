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
 * \file   uartStdio.h
 *
 * \brief  This file contains the prototypes of the UART standard I/O APIs.
 */

#ifndef UARTSTDIO_H_
#define UARTSTDIO_H_

#include <stdarg.h>
#include <ti/csl/csl_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                    MACRO DEFINITIONS
****************************************************************************/

#define UART_NUM_BYTES_CUSTOM           (-((int32_t) 1))

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern uint32_t UARTPuts(const char *pTxBuffer, int32_t numBytesToWrite);
extern uint32_t UARTGets(char *pRxBuffer, int32_t numBytesToRead);
extern int32_t UARTwrite(const char *pcBuf, uint32_t len);
extern void UARTprintf(const char *pcString, ...);
extern void UARTvprintf(const char *pcString, va_list vaArgP);
extern void UARTPutHexNum(uint32_t hexValue);
extern void UARTPutc(uint8_t byteTx);
extern uint32_t UARTGetHexNum(void);
extern uint8_t UARTGetc(void);
extern void UARTPutNum(int32_t value);
extern void UARTStdioInit(void);
extern int32_t UARTGetNum(void);
extern void UARTWaitUntilTransmitComplete(void);
extern int8_t UARTGetcNonBlocking(void);

#ifdef __cplusplus
}
#endif
#endif
