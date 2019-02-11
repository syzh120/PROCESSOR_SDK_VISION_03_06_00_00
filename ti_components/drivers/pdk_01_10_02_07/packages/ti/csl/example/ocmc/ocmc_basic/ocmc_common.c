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
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_ocmc_ecc.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#include "ocmc_common.h"

uint32_t *write_addr = NULL;
uint32_t *read_addr  = NULL;
uint32_t  nextVal;
uint32_t  gValue[cBufSizeInWord];
extern uint32_t uartBaseAddr;

void uart_reg_read_print(uint32_t addr, char *mess)
{
    uint32_t val = 0;

    UARTConfigPuts(uartBaseAddr, mess, -1);
    val = HW_RD_REG32(addr);
    UARTConfigPutHexNum(uartBaseAddr, val);
}

void uart_val_print(uint32_t val, char *mess)
{
    UARTConfigPuts(uartBaseAddr, mess, -1);
    UARTConfigPutHexNum(uartBaseAddr, val);
}

uint32_t readSubFrame(uint32_t size, uint32_t *readPointer)
{
    uint32_t i   = 0;
    uint32_t val = 0;

    for (i = 0; i < size; i++)
    {
        val = *readPointer++;
        uart_val_print(val, " ");
    }

    return 0;
}

uint32_t writeSubFrame(uint32_t size, uint32_t *writePointer, uint32_t *value)
{
    uint32_t i = 0;
    for (i = 0; i < size; i++)
    {
        *writePointer++ = *value++;
    }

    return 0;
}

uint32_t fillBuffer(uint32_t *value, uint32_t startValue, uint32_t size)
{
    uint32_t i = 0;

    for (i = 0; i < size; i++)
    {
        *(value + i) = startValue + i;
    }

    return (startValue + i);
}

