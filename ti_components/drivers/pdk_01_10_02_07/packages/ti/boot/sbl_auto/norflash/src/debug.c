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

#include <stdlib.h>
#include <stdint.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/boot/sbl_auto/norflash/src/debug.h>
#include <ti/boot/sbl_auto/norflash/nor_flash.h>

/* Debug print function For A15 use UART For M4 use stdio */
uint32_t DEBUG_printString(const char *s)
{
    if (gNor_InitPrms.norFlashInitPrintFxnPtr != NULL)
    {
        gNor_InitPrms.norFlashInitPrintFxnPtr(s);
    }
    return NOR_FLASH_SUCCESS;
}

void DEBUG_ConvertHexToString(uint32_t hexValue, char *stringValue,
                              int32_t maxLimitCount)
{
    uint32_t quotient = 0, tempVar;
    uint32_t dividend = 0;
    /* Count starts from two because of '0x' */
    int32_t  count         = 0, tmpCount = 0;
    char     tmpString[10] = {0};

    dividend           = hexValue;
    stringValue[count] = (char) '0';
    count++;
    stringValue[count] = (char) 'x';
    count++;
    do
    {
        quotient = dividend / 16U;
        tmpString[tmpCount] = (char) (dividend % 16U);
        if (0U == quotient)
        {
            break;
        }
        tmpCount++;
        dividend = quotient;
    } while (tmpCount < maxLimitCount);

    /* If we exceed limit, reduce and print from actual digits */
    if (tmpCount == maxLimitCount)
    {
        tmpCount--;
    }
    while (tmpCount >= 0)
    {
        /* Checking for alphanumeric numbers. */
        if ((16U - ((uint32_t) tmpString[tmpCount])) <= 6U)
        {
            /* Alphanumeric numbers. */
            tempVar  = (uint32_t) tmpString[tmpCount];
            tempVar += (uint32_t) '7';
            stringValue[count] = (char) tempVar;
            tmpCount--;
            count++;
        }
        else
        {
            /* Numbers in the range 0 to 9. */
            tempVar  = (uint32_t) tmpString[tmpCount];
            tempVar += (uint32_t) '0';
            stringValue[count] = (char) tempVar;
            tmpCount--;
            count++;
        }
    }
}

