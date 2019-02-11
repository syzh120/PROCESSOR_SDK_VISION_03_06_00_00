/*
 *  Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file   sbl_mflash_uart_console.c
 *
 * \brief  This file contains the UART Console APIs used in SBL MFlash.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/csl_uart.h>
#include <sbl_mflash_uart_console.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */



/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t gUartBaseAddress;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SBLMFlashUARTPuts(const char *pTxBuffer, int32_t numBytesToWrite)
{
    uint32_t count = 0;
    uint32_t flag  = 0;

    if (numBytesToWrite < 0)
    {
        flag = 1U;
    }

    while ((char) '\0' != *pTxBuffer)
    {
        /* Checks if data is a newline character. */
        if ((char) '\n' == *pTxBuffer)
        {
            /* Ensuring applicability to serial console.*/
            SBLMFlashUARTPutc((uint8_t) '\r');
            SBLMFlashUARTPutc((uint8_t) '\n');
        }
        else
        {
            SBLMFlashUARTPutc((uint8_t) *pTxBuffer);
        }
        pTxBuffer++;
        count++;
        if ((0U == flag) && (count == (uint32_t) numBytesToWrite))
        {
            break;
        }
    }
    /* Returns the number of bytes written onto the transmitter FIFO. */
    return count;
}

void SBLMFlashUARTPutHexNum(uint32_t hexValue)
{
    uint8_t  num[8]   = {0};
    uint32_t quotient = 0;
    uint32_t dividend = 0;
    int32_t  count    = 0;

    dividend = hexValue;

    do
    {
        quotient   = dividend / 16U;
        num[count] = (uint8_t) (dividend % 16U);
        if (0U == quotient)
        {
            break;
        }
        count++;
        dividend = quotient;
    } while (count < 8);

    /* If we exceed limit, reduce and print from actual digits */
    if (count == 8)
    {
        count--;
    }

    SBLMFlashUARTPutc((uint8_t) '0');
    SBLMFlashUARTPutc((uint8_t) 'x');

    while (count >= 0)
    {
        /* Checking for alphanumeric numbers. */
        if ((16U - num[count]) <= 6U)
        {
            /* Printing alphanumeric numbers. */
            SBLMFlashUARTPutc(num[count] + 0x37U);
            count--;
        }
        else
        {
            /* Printing numbers in the range 0 to 9. */
            SBLMFlashUARTPutc(num[count] + 0x30U);
            count--;
        }
    }
}

int32_t SBLMFlashUARTGetNum(void)
{
    char    rxByte;
    int32_t sign  = 1;
    int32_t value = 0;

    rxByte = (char) SBLMFlashUARTGetc();

    /* Accounting for negative numbers.*/
    if ((char) '-' == rxByte)
    {
        SBLMFlashUARTPutc((uint8_t) '-');
        sign = -(int32_t) 1;
    }
    else
    {
        SBLMFlashUARTPutc((uint8_t) rxByte);
        value = (value * 10) + ((int32_t) rxByte - 0x30);
    }


    rxByte = (char) SBLMFlashUARTGetc();

    /* Echoing the typed characters to the serial console.*/
    SBLMFlashUARTPutc((uint8_t) rxByte);

    /*
    ** Loop till the entered character is a carriage return.
    ** Pressing the 'Enter' key on the keyboard executes a
    ** carriage return on the serial console.
    */
    while((char) '\r' != rxByte)
    {
        /*
        ** Subtracting 0x30 to convert the representation of the digit
        ** from ASCII to hexadecimal.
        */
        value = (value * 10) + ((int32_t) rxByte - 0x30);

        rxByte = (char) SBLMFlashUARTGetc();

        /* Echoing the typed characters to the serial console.*/
        SBLMFlashUARTPutc((uint8_t) rxByte);
    }

    /* Accounting for the sign of the number.*/
    value = value * sign;

    return value;
}

uint32_t SBLMFlashUARTGetHexNum(void)
{
    char     rxByte;
    uint32_t value = 0;
    uint32_t loopIndex;
    uint32_t byteCount = 0;
    uint32_t loopBreak = 0;

    for (loopIndex = 0U; loopIndex < 2U; loopIndex++)
    {
        /* Receiving bytes from the host machine through serial console. */
        rxByte = (char) SBLMFlashUARTGetc();

        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if ((char) '\r' == rxByte)
        {
            loopBreak = 1U;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if (loopBreak != 1U)
        {
            if (((char) 'A' <= rxByte) && (rxByte <= (char) 'F'))
            {
                /* Echoing the typed characters to the serial console.*/
                SBLMFlashUARTPutc((uint8_t) rxByte);
                value = (value * 16U) + ((uint32_t) rxByte - 0x37U);
                byteCount++;
            }
            /*
            ** Checking if the character entered is one among the alphanumeric
            ** character set a,b,c...f
            */
            else if (((char) 'a' <= rxByte) && (rxByte <= (char) 'f'))
            {
                SBLMFlashUARTPutc((uint8_t) rxByte);
                value = (value * 16U) + ((uint32_t) rxByte - 0x57U);
                byteCount++;
            }
            /*
            ** Checking if the character entered is one among the decimal
            ** number set 0,1,2,3,....9
            */
            else if (((char) '0' <= rxByte) && (rxByte <= (char) '9'))
            {
                SBLMFlashUARTPutc((uint8_t) rxByte);
                value = (value * 16U) + ((uint32_t) rxByte - 0x30U);
                byteCount++;
            }
            /*
            ** Checking if the character is either a 'x'(lower-case) or an 'X'
            ** (upper-case).
            */
            else if (((char) 'x' == rxByte) || ((char) 'X' == rxByte))
            {
                SBLMFlashUARTPutc((uint8_t) rxByte);
                value     = 0;
                loopBreak = 1U;
            }
            else
            {
                /* Nothing to be done here */
            }
        }

        if (loopBreak == 1U)
        {
            break;
        }
    }

    if (0U == value)
    {
        byteCount = 0;
    }

    do
    {
        rxByte = (char) SBLMFlashUARTGetc();

        if ((char) '\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if (((char) 'A' <= rxByte) && (rxByte <= (char) 'F'))
        {
            SBLMFlashUARTPutc((uint8_t) rxByte);
            value = (value * 16U) + ((uint32_t) rxByte - 0x37U);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if (((char) 'a' <= rxByte) && (rxByte <= (char) 'f'))
        {
            SBLMFlashUARTPutc((uint8_t) rxByte);
            value = (value * 16U) + ((uint32_t) rxByte - 0x57U);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if (((char) '0' <= rxByte) && (rxByte <= (char) '9'))
        {
            SBLMFlashUARTPutc((uint8_t) rxByte);
            value = (value * 16U) + ((uint32_t) rxByte - 0x30U);
            byteCount++;
        }
        /*
        ** Not receiving any other character other than the one belonging
        ** to the above three categories.
        */
        else
        {
            /* Intentionally left empty. */
        }
    } while (byteCount < 8U);
    return value;
}

void SBLMFlashUARTPutc(uint8_t byteTx)
{
    SBLMFlashUARTConsolePutc(byteTx);
}

uint8_t SBLMFlashUARTGetc(void)
{
    return (SBLMFlashUARTConsoleGetc());
}

int8_t SBLMFlashUARTGetcNonBlocking(void)
{
    return (SBLMFlashUARTConsoleGetcNonBlocking());
}

int32_t SBLMFlashUARTConsoleConfigInit(UART_INST_t num,
                                        uint32_t    baudRate,
                                        uint32_t    operMode,
                                        uint32_t    parity,
                                        uint32_t    wordLen,
                                        uint32_t    stopBit)
{
    uint32_t divisorValue = 0, fifoConfig = 0;
    int32_t     retVal       = STW_SOK;

    switch (num)
    {
        case UART1_INST:
            gUartBaseAddress = SOC_UART1_BASE;
            break;
        case UART2_INST:
            gUartBaseAddress = SOC_UART2_BASE;
            break;
        case UART3_INST:
            gUartBaseAddress = SOC_UART3_BASE;
            break;
#if defined (SOC_TDA2PX)
        case UART4_INST:
        case UART5_INST:
        case UART6_INST:
        case UART7_INST:
        case UART8_INST:
        case UART9_INST:
        case UART10_INST:
            retVal = STW_EFAIL;
            break;
#endif
        default:
            retVal = STW_EFAIL;
            break;
    }

    if (retVal == STW_SOK)
    {
        /* Performing a module reset. */
        UARTModuleReset(gUartBaseAddress);

        /* Performing FIFO configurations. */
        /*
        ** - Transmit Trigger Level Granularity is 4
        ** - Receiver Trigger Level Granularity is 4
        ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
        **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
        ** - The Receiver Trigger Level is 16.
        ** - Clear the Transmit FIFO.
        ** - Clear the Receiver FIFO.
        ** - DMA Mode enabling shall happen through SCR register.
        ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
        **   DMA Mode. Effectively DMA Mode is disabled.
        */
        fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                      UART_TRIG_LVL_GRANULARITY_4,
                                      UART_FCR_TX_TRIG_LVL_56,
                                      UART_FCR_RX_TRIG_LVL_16,
                                      1U,
                                      1U,
                                      UART_DMA_EN_PATH_SCR,
                                      UART_DMA_MODE_0_ENABLE);

        /* Configuring the FIFO settings. */
        UARTFIFOConfig(gUartBaseAddress, fifoConfig);

        /* Performing Baud Rate settings. */
        /* Computing the Divisor Value. */
        divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                             baudRate,
                                             operMode,
                                             UART_MIR_OVERSAMPLING_RATE_42);
        /* Programming the Divisor Latches. */
        UARTDivisorLatchWrite(gUartBaseAddress, divisorValue);

        /* Switching to Configuration Mode B. */
        UARTRegConfigModeEnable(gUartBaseAddress, UART_REG_CONFIG_MODE_B);

        /* Programming the Line Characteristics. */
        UARTLineCharacConfig(gUartBaseAddress,
                             (wordLen | stopBit),
                             parity);

        /* Disabling write access to Divisor Latches. */
        UARTDivisorLatchDisable(gUartBaseAddress);

        /* Disabling Break Control. */
        UARTBreakCtl(gUartBaseAddress, UART_BREAK_COND_DISABLE);

        /* Uart enable */
        UARTOperatingModeSelect(gUartBaseAddress, operMode);

        /* Debug */
        UARTOperatingModeSelect(gUartBaseAddress, operMode);
    }
    return retVal;
}

void SBLMFlashUARTConsolePutc(uint8_t data)
{
    UARTCharPut(gUartBaseAddress, data);
}

uint8_t SBLMFlashUARTConsoleGetc(void)
{
    return (uint8_t) UARTCharGet(gUartBaseAddress);
}

int8_t SBLMFlashUARTConsoleGetcNonBlocking(void)
{
    return UARTCharGetNonBlocking(gUartBaseAddress);
}

uint8_t SBLMFlashUARTConsoleFIFOGets(uint8_t *buf, uint8_t num)
{
    uint32_t i = 0;
    /* Read num characters from FIFO*/
    for(i = 0; i < num; i++)
    {
        *buf = (uint8_t)UARTFIFOCharGet(gUartBaseAddress);
        buf++;
    }
    return num;
}

uint32_t SBLMFlashUARTRxFIFOLevelGet(void)
{
  return UARTRxFIFOLevelGet(gUartBaseAddress);
}


void SBLLibUARTSetClock(uint32_t fUartClock)
{
    /* calculating the CM_L4PER_UART3_CLKCTRL register address */
    uint32_t regAddr = SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART3_CLKCTRL;

    /* shifting the clock to correct bit */
    uint32_t shiftedClock = fUartClock << CM_L4PER_UART3_CLKCTRL_CLKSEL_SHIFT;

    uint32_t mask = CM_L4PER_UART3_CLKCTRL_CLKSEL_MASK;

    /* Getting the old value stoerd in  the register */
    uint32_t oldValue = HW_RD_REG32(regAddr);

    /* Calculating the new value to be stored in the register */
    uint32_t newValue = (oldValue & (~mask)) | (mask & shiftedClock);

    /* Writing the new value to the register */
    HW_WR_REG32(regAddr, newValue);
}
