/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file   uartStdio.c
 *
 *  \brief  This file contains functions which interface interactively
 *          with the user through the serial console to perform some
 *          utility operations.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdarg.h>
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_uart.h>
#include <ti/csl/soc.h>
#include "uart.h"
#include "uartStdio.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BAUD_RATE_115200                (115200U)
#define BAUD_RATE_3686400               (3686400U)
#define UART_MODULE_INPUT_CLK           (48000000U)

#define BAUD_RATE                       (BAUD_RATE_115200)
#define OPER_MODE                       (UART16x_OPER_MODE)

/* Parameterized macro to configure the FIFO settings. */
#define UART_FIFO_CONFIG(txGra, rxGra, txTrig, rxTrig, txClr, rxClr, dmaEnPath,\
                         dmaMode)                                              \
    ((uint32_t)                                                                  \
     ((((txGra) & 0xF) << 26) |                                                \
      (((rxGra) & 0xF) << 22) |                                                \
      (((txTrig) & 0xFF) << 14) |                                              \
      (((rxTrig) & 0xFF) << 6) |                                               \
      (((txClr) & 0x1) << 5) |                                                 \
      (((rxClr) & 0x1) << 4) |                                                 \
      (((dmaEnPath) & 0x1) << 3) |                                             \
      ((dmaMode) & 0x7)))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static uint32_t UART_Init(uint32_t baseAddr);

static void UARTModuleReset(uint32_t baseAdd);
static uint32_t UARTOperatingModeSelect(uint32_t baseAdd, uint32_t modeFlag);
static uint32_t UARTDivisorValCompute(uint32_t moduleClk,
                                    uint32_t baudRate,
                                    uint32_t modeFlag,
                                    uint32_t mirOverSampRate);
static uint32_t UARTDivisorLatchWrite(uint32_t baseAdd, uint32_t divisorValue);
static void UARTDivisorLatchDisable(uint32_t baseAdd);
static uint32_t UARTRegConfigModeEnable(uint32_t baseAdd, uint32_t modeFlag);
static void UARTBreakCtl(uint32_t baseAdd, uint32_t breakState);
static void UARTLineCharacConfig(uint32_t baseAdd,
                                 uint32_t wLenStbFlag,
                                 uint32_t parityFlag);

static uint32_t UARTFIFOConfig(uint32_t baseAdd, uint32_t fifoConfig);
static uint32_t UARTEnhanFuncEnable(uint32_t baseAdd);
static void UARTEnhanFuncBitValRestore(uint32_t baseAdd, uint32_t enhanFnBitVal);

static uint32_t UARTSubConfigTCRTLRModeEn(uint32_t baseAdd);
static void UARTTCRTLRBitValRestore(uint32_t baseAdd, uint32_t tcrTlrBitVal);

static int8_t UARTCharGet(uint32_t baseAdd);
static int32_t UARTCharGetNonBlocking(uint32_t baseAdd, uint8_t *retChar);
static uint32_t UARTCharsAvail(uint32_t baseAdd);

static void UARTCharPut(uint32_t baseAdd, uint8_t byteTx);

static void UARTFIFORegisterWrite(uint32_t baseAdd, uint32_t fcrValue);
static uint32_t UARTIsTransmitterEmpty(uint32_t baseAdd);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* A mapping from an integer between 0 and 15 to its ASCII character
 * equivalent. */
static const char *const g_pcHex = "0123456789abcdef";

static uint32_t gUartBaseAddr;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief   This function initializes the specified UART instance for use for
 *          console operations.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void UARTStdioInit(void)
{
#if defined (SOC_TDA3XX)
    uint32_t baseAddr = SOC_UART3_BASE;
#else
    uint32_t baseAddr = SOC_UART1_BASE;
#endif
    uint8_t  retChar;

    UART_Init(baseAddr);

    /* flush any junk characters in UART FIFO */
    while (1U)
    {
        if (TRUE == UARTCharsAvail(baseAddr))
        {
            UARTCharGetNonBlocking(baseAddr, &retChar);
        }
        else
        {
            break;
        }
    }

    return;
}

/**
 * \brief  This function writes data from a specified buffer onto the
 *         transmitter FIFO of UART.
 *
 * \param  pTxBuffer        Pointer to a buffer in the transmitter.
 * \param  numBytesToWrite  Number of bytes to be transmitted to the
 *                          transmitter FIFO. The user has the freedom to not
 *                          specify any valid value for this if he wants to
 *                          print until the occurence of a NULL character.
 *                          In this case, he has to pass a negative value as
 *                          this parameter.
 *
 * \return  Number of bytes written to the transmitter FIFO.
 *
 * \note   1> Whenever a null character(\0) is encountered in the
 *            data to be transmitted, the transmission is stopped. \n
 *         2> Whenever the transmitter data has a new line character(\n),
 *            it is interpreted as a new line(\n) + carraige return(\r)
 *            characters. This is because the serial console interprets a
 *            new line character as it is and does not introduce a carraige
 *            return. \n
 *
 *         Some example function calls of this function are: \n
 *
 *         UARTPuts(txArray, -2): This shall print the contents of txArray[]
 *         until the occurence of a NULL character. \n
 *
 *         UARTPuts("Hello World", 8): This shall print the first 8 characters
 *         of the string shown. \n
 *
 *         UARTPuts("Hello World", 20): This shall print the string shown until
 *         the occurence of the NULL character. Here, the NULL character is
 *         encountered earlier than the length of 20 bytes.\n
 *
 */
uint32_t UARTPuts(const char *pTxBuffer, int32_t numBytesToWrite)
{
    uint32_t count = 0;
    uint32_t flag  = 0;

    if (numBytesToWrite < 0)
    {
        flag = 1;
    }

    while ((int8_t) '\0' != *pTxBuffer)
    {
        /* Checks if data is a newline character. */
        if ((int8_t) '\n' == *pTxBuffer)
        {
            /* Ensuring applicability to serial console.*/
            UARTPutc('\r');
            UARTPutc('\n');
        }
        else
        {
            UARTPutc((uint8_t) *pTxBuffer);
        }
        pTxBuffer++;
        count++;
        if ((0 == flag) && (count == numBytesToWrite))
        {
            break;
        }
    }

    /* Returns the number of bytes written onto the transmitter FIFO. */
    return count;
}

/**
 * \brief  This function reads data from the receiver FIFO to a buffer
 *         in the receiver.
 *
 * \param  pRxBuffer        Pointer to a buffer in the receiver.
 * \param  numBytesToRead   The number of bytes the receiver buffer can hold.
 *                          However, if the user wishes not to specify this
 *                          parameter, he has freedom to do so. In that case,
 *                          the user has to pass a negative value for this
 *                          parameter.
 *
 * \return  Number of bytes read from the receiver FIFO.
 *
 * \note   The two exit points for this function are:
 *         1> To enter an ESC character or a carraige return character('Enter'
 *            key on the Keyboard).\n
 *         2> Specify a limit to the number of bytes to be read. \n
 *
 *         Some example function calls of this function are:
 *
 *         UARTGets(rxBuffer, -2): This reads characters from
 *         the receiver FIFO of UART until the occurence of a carriage return
 *         ('Enter' key on the keyboard pressed) or an ESC character.
 *
 *         UARTGets(rxBuffer, 12): This reads characters until
 *         12 characters have been read or until an occurence of a carriage
 *         return or an ESC character, whichever occurs first.
 */
uint32_t UARTGets(char *pRxBuffer, int32_t numBytesToRead)
{
    int32_t  count = 0;
    uint32_t flag  = 0;

    if (numBytesToRead < 0)
    {
        flag = 1;
    }
    do
    {
        *pRxBuffer = (char) UARTGetc();

        /*
        ** 0xD - ASCII value of Carriage Return.
        ** 0x1B - ASCII value of ESC character.
        */
        if (0xD == *pRxBuffer || 0x1B == *pRxBuffer)
        {
            *pRxBuffer = (uint8_t) '\0';
            break;
        }

        /* Echoing the typed character back to the serial console. */
        UARTPutc((uint8_t) *pRxBuffer);
        pRxBuffer++;
        count++;
        if (0 == flag && (count == numBytesToRead))
        {
            break;
        }
    } while (1);

    return count;
}

/**
 *  \brief   This function prints the specified numbers(positive or negative)
 *           on the serial console.
 *
 *  \param   value     The number to be printed on the serial console.
 *
 *  \return  None.
 *
 *  \note    The numbers that this function can print should lie in the
 *           following range:
 *           [-2^(31)] to [2^(31) - 1] i.e.
 *           0x80000000 to  0x7FFFFFFF
 *
 */
void UARTPutNum(int32_t value)
{
    char     num[10]  = {0};
    uint32_t quotient = 0;
    uint32_t dividend = 0;
    int32_t  count    = 0;

    if (value < 0)
    {
        UARTPutc('-');
        /*
        ** Making the negative number as positive.
        ** This is done to simplify further processing and printing.
        */
        value = -value;
    }

    dividend = value;
    do
    {
        quotient   = dividend / 10;
        num[count] = (uint8_t) (dividend % 10);
        if (0 == quotient)
        {
            break;
        }
        count++;
        dividend = quotient;
    } while (count < 10);

    /* If we exceed limit, reduce and print from actual digits */
    if (count == 10)
    {
        count--;
    }

    /* Printing the digits. */
    do
    {
        /* We add 0x30 to a digit to obtain its respective ASCII value.*/
        UARTPutc(num[count--] + 0x30);
    } while (count >= 0);

    return;
}

/**
 * \brief  This function is used to print hexadecimal numbers on the serial
 *         console.
 *
 * \param  hexValue   The Hexadecimal number to be printed.
 *
 * \return None
 */
void UARTPutHexNum(uint32_t hexValue)
{
    uint8_t  num[8]   = {0};
    uint32_t quotient = 0;
    uint32_t dividend = 0;
    int32_t  count    = 0;

    dividend = hexValue;

    do
    {
        quotient   = dividend / 16;
        num[count] = (uint8_t) (dividend % 16);
        if (0 == quotient)
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

    UARTPutc('0');
    UARTPutc('x');

    while (count >= 0)
    {
        /* Checking for alphanumeric numbers. */
        if ((16 - num[count]) <= 6)
        {
            /* Printing alphanumeric numbers. */
            UARTPutc(num[count--] + 0x37);
        }
        else
        {
            /* Printing numbers in the range 0 to 9. */
            UARTPutc(num[count--] + 0x30);
        }
    }

    return;
}

/**
 *  \brief   This function reads the numbers typed on the serial console.
 *
 *  \return  The value entered on the serial console.
 *
 *  \note   The numbers that this function can recieve should lie in the
 *           following range:
 *           [-2^(31)] to [2^(31) - 1] i.e.
 *           0x80000000 to  0x7FFFFFFF
 */
int32_t UARTGetNum(void)
{
    char    rxByte;
    int32_t sign  = 1;
    int32_t value = 0;

    rxByte = (char) UARTGetc();

    /* Accounting for negative numbers.*/
    if ((int8_t) '-' == rxByte)
    {
        UARTPutc('-');
        sign = -1;
    }
    else
    {
        UARTPutc((uint8_t) rxByte);
        value = value * 10 + (rxByte - 0x30);
    }

    do
    {
        rxByte = (char) UARTGetc();

        /* Echoing the typed characters to the serial console.*/
        UARTPutc((uint8_t) rxByte);
        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if ((int8_t) '\r' == rxByte)
        {
            break;
        }
        /*
        ** Subtracting 0x30 to convert the representation of the digit
        ** from ASCII to hexadecimal.
        */
        value = value * 10 + (rxByte - 0x30);
    } while (1);

    /* Accounting for the sign of the number.*/
    value = value * sign;

    return value;
}

/**
 *  \brief   This function receives hexadecimal numbers entered on the serial
 *           console of the host machine.
 *
 *  \param   None
 *
 *  \return  The hexadecimal number entered on the serial console of the host
 *           machine.
 *
 *  \note    1> The points below explain the ways of entering hexadecimal
 *              numbers:\n
 *              - 0xABCDEF12 - Hexadecimal number preceded by a '0x'.\n
 *              - 0XABCDEF12 - Hexadecimal number preceded by a '0X'.\n
 *              - 0xabcdef12 - Lower-case alphanumeric numbers are allowed.\n
 *              - 0xaBcDeF12 - Intermixing of lower-case and upper-case
 *                             alphanumeric numbers is allowed.\n
 *              - abcdef12   - A preceding '0x' or '0X' is not requried.
 *                             The entered number shall be treated as a
 *                             hexadecimal number.\n
 *              - 12345678   - Interpreted as 0x12345678 and not decimal
 *                             12345678.\n
 *              - xABCDEF12  - A preceding '0' is not required.\n
 *           2> This function does not take into consideration any character
 *              other than a hexadecimal character after reception.\n
 *              Example: Characters in the range G,H,I,...Z or g,h,...,z
 *              are not taken into consideration.\n
 *           3> The maximum value that can be returned by this function
 *              is 0xFFFFFFFF. The reception exits after eight characters have
 *              been received.\n
 *           4> To input a  number lesser that eight characters (Ex: 0x1AB),
 *              press the 'Enter' key after entering the number.\n
 */
uint32_t UARTGetHexNum(void)
{
    char     rxByte;
    uint32_t value = 0;
    uint32_t loopIndex;
    uint32_t byteCount = 0;

    for (loopIndex = 0; loopIndex < 2; loopIndex++)
    {
        /* Receiving bytes from the host machine through serial console. */
        rxByte = (char) UARTGetc();

        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if ((int8_t) '\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if (((int8_t) 'A' <= rxByte) && (rxByte <= (int8_t) 'F'))
        {
            /* Echoing the typed characters to the serial console.*/
            UARTPutc((uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x37);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if (((int8_t) 'a' <= rxByte) && (rxByte <= (int8_t) 'f'))
        {
            UARTPutc((uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x57);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if (((int8_t) '0' <= rxByte) && (rxByte <= (int8_t) '9'))
        {
            UARTPutc((uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x30);
            byteCount++;
        }
        /*
        ** Checking if the character is either a 'x'(lower-case) or an 'X'
        ** (upper-case).
        */
        else if (((int8_t) 'x' == rxByte) || ((int8_t) 'X' == rxByte))
        {
            UARTPutc((uint8_t) rxByte);
            value = 0;
            break;
        }
    }

    if (0 == value)
    {
        byteCount = 0;
    }

    do
    {
        rxByte = (char) UARTGetc();

        if ((int8_t) '\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if (((int8_t) 'A' <= rxByte) && (rxByte <= (int8_t) 'F'))
        {
            UARTPutc((uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x37);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if (((int8_t) 'a' <= rxByte) && (rxByte <= (int8_t) 'f'))
        {
            UARTPutc((uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x57);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if (((int8_t) '0' <= rxByte) && (rxByte <= (int8_t) '9'))
        {
            UARTPutc((uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x30);
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
    } while (byteCount < 8);

    return value;
}

/**
 * \brief   This function writes a byte on the serial console.
 *
 * \param   byteTx   The byte to be transmitted.
 *
 * \return  None.
 */
void UARTPutc(uint8_t byteTx)
{
    UARTCharPut(gUartBaseAddr, byteTx);
}

/**
 *  \brief   This function reads a byte entered on the serial console.
 *
 *  \return  Returns the entered byte typecasted as an unsigned character.
 */
uint8_t UARTGetc(void)
{
    return (UARTCharGet(gUartBaseAddr));
}

/**
 *  \brief   This function reads a byte entered on the serial console in a
 *           non-blocking way.
 *  \param   retChar - Entered byte typecasted as an unsigned character.
 *
 *  \return  Returns -1 if no char read. 0 if a char is read.
 */
int32_t UARTGetcNonBlocking(uint8_t *retChar)
{
    return (UARTCharGetNonBlocking(gUartBaseAddr, retChar));
}

/**
 *  \brief   This function waits indefinitely until UART THR and Transmitter
 *           Shift Registers are empty.
 *
 *  \param   None.
 *
 *  \return  None.
 */
void UARTWaitUntilTransmitComplete(void)
{
    /*
    ** Waits indefinitely until the THR and Transmitter Shift Registers are
    ** empty.
    */
    while ((uint32_t) (TRUE) != UARTIsTransmitterEmpty(gUartBaseAddr))
    {
        /* Do nothing - Busy wait */
    }
}

/**
 *  Writes a string of characters to the UART output.
 *
 *  \param pcBuf points to a buffer containing the string to transmit.
 *  \param ulLen is the length of the string to transmit.
 *
 *  This function will transmit the string to the UART output.  The number of
 *  characters transmitted is determined by the \e ulLen parameter.  This
 *  function does no interpretation or translation of any characters.  Since
 *  the output is sent to a UART, any LF (/n) characters encountered will be
 *  replaced with a CRLF pair.
 *
 *  Besides using the \e ulLen parameter to stop transmitting the string, if a
 *  null character (0) is encountered, then no more characters will be
 *  transmitted and the function will return.
 *
 *  In non-buffered mode, this function is blocking and will not return until
 *  all the characters have been written to the output FIFO.  In buffered mode,
 *  the characters are written to the UART transmit buffer and the call returns
 *  immediately.  If insufficient space remains in the transmit buffer,
 *  additional characters are discarded.
 *
 *  \return Returns the count of characters written.
 */
int32_t UARTWrite(const char *pcBuf, uint32_t ulLen)
{
    uint32_t uIdx;

    /* Send the characters */
    for (uIdx = 0; uIdx < ulLen; uIdx++)
    {
        /* If the character to the UART is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if (pcBuf[uIdx] == (int8_t) '\n')
        {
            UARTPutc('\r');
        }

        /* Send the character to the UART output. */
        UARTPutc(pcBuf[uIdx]);
    }

    /* Return the number of characters written. */
    return (uIdx);
}

/**
 *  A simple UART based printf function supporting \%c, \%d, \%p, \%s, \%u,
 *  \%x, and \%X.
 *
 *  \param pcString is the format string.
 *  \param ... are the optional arguments, which depend on the contents of the
 *  format string.
 *
 *  This function is very similar to the C library <tt>fprintf()</tt> function.
 *  All of its output will be sent to the UART.  Only the following formatting
 *  characters are supported:
 *
 *  - \%c to print a character
 *  - \%d to print a decimal value
 *  - \%s to print a string
 *  - \%u to print an unsigned decimal value
 *  - \%x to print a hexadecimal value using lower case letters
 *  - \%X to print a hexadecimal value using lower case letters (not upper case
 *  letters as would typically be used)
 *  - \%p to print a pointer as a hexadecimal value
 *  - \%\% to print out a \% character
 *
 *  For \%s, \%d, \%u, \%p, \%x, and \%X, an optional number may reside
 *  between the \% and the format character, which specifies the minimum number
 *  of characters to use for that value; if preceded by a 0 then the extra
 *  characters will be filled with zeros instead of spaces.  For example,
 *  ``\%8d'' will use eight characters to print the decimal value with spaces
 *  added to reach eight; ``\%08d'' will use eight characters as well but will
 *  add zeroes instead of spaces.
 *
 *  The type of the arguments after \e pcString must match the requirements of
 *  the format string.  For example, if an integer was passed where a string
 *  was expected, an error of some kind will most likely occur.
 *
 *  \return None.
 */
void UARTPrintf(const char *pcString, ...)
{
    uint32_t ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg;
    char    *pcStr, pcBuf[16], cFill;
    va_list  vaArgP;

    /* Start the varargs processing. */
    va_start(vaArgP, pcString);

    /* Loop while there are more characters in the string. */
    while (*pcString)
    {
        /* Find the first non-% character, or the end of the string. */
        for (ulIdx = 0;
             (pcString[ulIdx] != (int8_t) '%') &&
             (pcString[ulIdx] != (int8_t) '\0');
             ulIdx++)
        {}

        /* Write this portion of the string. */
        UARTWrite(pcString, ulIdx);

        /* Skip the portion of the string that was written. */
        pcString += ulIdx;

        /* See if the next character is a %. */
        if (*pcString == (int8_t) '%')
        {
            /* Skip the %. */
            pcString++;

            /* Set the digit count to zero, and the fill character to space
             * (i.e. to the defaults). */
            ulCount = 0;
            cFill   = (uint8_t) ' ';

            /* It may be necessary to get back here to process more characters.
             * Goto's aren't pretty, but effective.  I feel extremely dirty for
             * using not one but two of the beasts. */
again:

            /* Determine how to handle the next character. */
            switch (*pcString++)
            {
                /* Handle the digit characters. */
                case (uint8_t) '0':
                case (uint8_t) '1':
                case (uint8_t) '2':
                case (uint8_t) '3':
                case (uint8_t) '4':
                case (uint8_t) '5':
                case (uint8_t) '6':
                case (uint8_t) '7':
                case (uint8_t) '8':
                case (uint8_t) '9':
                {
                    /* If this is a zero, and it is the first digit, then the
                     * fill character is a zero instead of a space. */
                    if ((pcString[-1] == (int8_t) '0') && (ulCount == 0))
                    {
                        cFill = (uint8_t) '0';
                    }

                    /* Update the digit count. */
                    ulCount *= 10;
                    ulCount += pcString[-1] - (int8_t) '0';

                    /* Get the next character. */
                    goto again;
                }

                /* Handle the %c command. */
                case (uint8_t) 'c':
                {
                    /* Get the value from the varargs. */
                    ulValue = va_arg(vaArgP, uint32_t);

                    /* Print out the character. */
                    UARTWrite((char *) &ulValue, 1);

                    /* This command has been handled. */
                    break;
                }

                /* Handle the %d command. */
                case (uint8_t) 'd':
                {
                    /* Get the value from the varargs. */
                    ulValue = va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* If the value is negative, make it positive and indicate
                     * that a minus sign is needed. */
                    if ((int32_t) ulValue < 0)
                    {
                        /* Make the value positive. */
                        ulValue = -(int32_t) ulValue;

                        /* Indicate that the value is negative. */
                        ulNeg = 1;
                    }
                    else
                    {
                        /* Indicate that the value is positive so that a minus
                         * sign isn't inserted. */
                        ulNeg = 0;
                    }

                    /* Set the base to 10. */
                    ulBase = 10;

                    /* Convert the value to ASCII. */
                    goto convert;
                }

                /* Handle the %s command. */
                case (uint8_t) 's':
                {
                    /* Get the string pointer from the varargs. */
                    pcStr = va_arg(vaArgP, char *);

                    /* Determine the length of the string. */
                    for (ulIdx = 0; pcStr[ulIdx] != (int8_t) '\0'; ulIdx++)
                    {}

                    /* Write the string. */
                    UARTWrite(pcStr, ulIdx);

                    /* Write any required padding spaces */
                    if (ulCount > ulIdx)
                    {
                        ulCount -= ulIdx;
                        while (ulCount--)
                        {
                            UARTWrite(" ", 1);
                        }
                    }
                    /* This command has been handled. */
                    break;
                }

                /* Handle the %u command. */
                case (uint8_t) 'u':
                {
                    /* Get the value from the varargs. */
                    ulValue = va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* Set the base to 10. */
                    ulBase = 10;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    ulNeg = 0;

                    /* Convert the value to ASCII. */
                    goto convert;
                }

                /* Handle the %x and %X commands.  Note that they are treated
                 * identically; i.e. %X will use lower case letters for a-f
                 * instead of the upper case letters is should use.  We also
                 * alias %p to %x. */
                case (uint8_t) 'x':
                case (uint8_t) 'X':
                case (uint8_t) 'p':
                {
                    /* Get the value from the varargs. */
                    ulValue = va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* Set the base to 16. */
                    ulBase = 16;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    ulNeg = 0;

                    /* Determine the number of digits in the string version of
                     * the value. */
convert:
                    for (ulIdx = 1;
                         (((ulIdx * ulBase) <= ulValue) &&
                          (((ulIdx * ulBase) / ulBase) == ulIdx));
                         ulIdx *= ulBase)
                    {
                        ulCount--;
                    }

                    /* If the value is negative, reduce the count of padding
                     * characters needed. */
                    if (ulNeg)
                    {
                        ulCount--;
                    }

                    /* If the value is negative and the value is padded with
                     * zeros, then place the minus sign before the padding. */
                    if (ulNeg && (cFill == (int8_t) '0'))
                    {
                        /* Place the minus sign in the output buffer. */
                        pcBuf[ulPos++] = (uint8_t) '-';

                        /* The minus sign has been placed, so turn off the
                         * negative flag. */
                        ulNeg = 0;
                    }

                    /* Provide additional padding at the beginning of the
                     * string conversion if needed. */
                    if ((ulCount > 1) && (ulCount < 16))
                    {
                        for (ulCount--; ulCount; ulCount--)
                        {
                            pcBuf[ulPos++] = cFill;
                        }
                    }

                    /* If the value is negative, then place the minus sign
                     * before the number. */
                    if (ulNeg)
                    {
                        /* Place the minus sign in the output buffer. */
                        pcBuf[ulPos++] = (uint8_t) '-';
                    }

                    /* Convert the value into a string. */
                    for (; ulIdx; ulIdx /= ulBase)
                    {
                        pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase];
                    }

                    /* Write the string. */
                    UARTWrite(pcBuf, ulPos);

                    /* This command has been handled. */
                    break;
                }

                /* Handle the %% command. */
                case (uint8_t) '%':
                {
                    /* Simply write a single %. */
                    UARTWrite(pcString - 1, 1);

                    /* This command has been handled. */
                    break;
                }

                /* Handle all other commands. */
                default:
                {
                    /* Indicate an error. */
                    UARTWrite("ERROR", 5);

                    /* This command has been handled. */
                    break;
                }
            }
        }
    }

    /* End the varargs processing. */
    va_end(vaArgP);

    return;
}

static uint32_t UART_Init(uint32_t baseAddr)
{
    uint32_t divisorValue = 0, fifoConfig = 0;

    gUartBaseAddr = baseAddr;

    /* Performing a module reset. */
    UARTModuleReset(gUartBaseAddr);

    /* Performing FIFO configurations. */
    /*
    ** - Transmit Trigger Level Granularity is 4
    ** - Receiver Trigger Level Granularity is 1
    ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
    **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
    ** - The Receiver Trigger Level is 1.
    ** - Clear the Transmit FIFO.
    ** - Clear the Receiver FIFO.
    ** - DMA Mode enabling shall happen through SCR register.
    ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
    **   DMA Mode. Effectively DMA Mode is disabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  UART_FCR_TX_TRIG_LVL_56,
                                  1,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_0_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(gUartBaseAddr, fifoConfig);

    /* Performing Baud Rate settings. */
    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE,
                                         OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);
    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(gUartBaseAddr, divisorValue);

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(gUartBaseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(gUartBaseAddr,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(gUartBaseAddr);

    /* Disabling Break Control. */
    UARTBreakCtl(gUartBaseAddr, UART_BREAK_COND_DISABLE);

    /* Uart enable */
    UARTOperatingModeSelect(gUartBaseAddr, OPER_MODE);

    /* Debug */
    UARTOperatingModeSelect(gUartBaseAddr, OPER_MODE);

    return (1);
}

static void UARTModuleReset(uint32_t baseAdd)
{
    /* Performing Software Reset of the module. */
    HW_WR_FIELD32(baseAdd + UART_SYSC, UART_SYSC_SOFTRESET,
                  UART_SYSC_SOFTRESET_SOFTRESET_VALUE_1);

    /* Wait until the process of Module Reset is complete. */
    while (0 == HW_RD_FIELD32(baseAdd + UART_SYSS, UART_SYSS_RESETDONE))
    {
        /* Do nothing - Busy wait */
    }
}

static void UARTCharPut(uint32_t baseAdd, uint8_t byteTx)
{
    uint32_t lcrRegValue = 0;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    /*
    ** Waits indefinitely until the THR and Transmitter Shift Registers are
    ** empty.
    */
    while (((uint32_t) UART_LSR_TX_SR_E_MASK |
            (uint32_t) UART_LSR_TX_FIFO_E_MASK) !=
           (HW_RD_REG32(baseAdd + UART_LSR) &
            ((uint32_t) UART_LSR_TX_SR_E_MASK |
             (uint32_t) UART_LSR_TX_FIFO_E_MASK)))
    {
        /* Do nothing - Busy wait */
    }

    HW_WR_REG32(baseAdd + UART_THR, (uint32_t) byteTx);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);
}

static int8_t UARTCharGet(uint32_t baseAdd)
{
    uint32_t lcrRegValue = 0;
    int8_t   retVal      = 0;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    /* Waits indefinitely until a byte arrives in the RX FIFO(or RHR). */
    while ((uint32_t) UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 ==
           (HW_RD_REG32(baseAdd + UART_LSR) &
            UART_LSR_RX_FIFO_E_MASK))
    {
        /* Do nothing - Busy wait */
    }

    retVal = (int8_t) HW_RD_REG32(baseAdd + UART_RHR);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return retVal;
}

static int32_t UARTCharGetNonBlocking(uint32_t baseAdd, uint8_t *retChar)
{
    uint32_t lcrRegValue = 0;
    int32_t retVal      = -1;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    /* Checking if the RX FIFO(or RHR) has atleast one byte of data. */
    if ((uint32_t) UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 !=
        (HW_RD_REG32(baseAdd + UART_LSR) &
         UART_LSR_RX_FIFO_E_MASK))
    {
        if (((void *) 0) != retChar)
        {
            *retChar = (int8_t) HW_RD_REG32(baseAdd + UART_RHR);
            retVal = 0;
        }
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return retVal;
}

static uint32_t UARTCharsAvail(uint32_t baseAdd)
{
    uint32_t lcrRegValue = 0;
    uint32_t retVal      = FALSE;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    /* Checking if the RHR(or RX FIFO) has atleast one byte to be read. */
    if ((uint32_t) UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 !=
        (HW_RD_REG32(baseAdd + UART_LSR) &
         UART_LSR_RX_FIFO_E_MASK))
    {
        retVal = (uint32_t) TRUE;
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return retVal;
}

static uint32_t UARTRegConfigModeEnable(uint32_t baseAdd, uint32_t modeFlag)
{
    uint32_t lcrRegValue = 0;

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAdd + UART_LCR);

    switch (modeFlag)
    {
        case UART_REG_CONFIG_MODE_A:
        case UART_REG_CONFIG_MODE_B:
            HW_WR_REG32(baseAdd + UART_LCR, modeFlag & 0xFFU);
            break;

        case UART_REG_OPERATIONAL_MODE:
            HW_WR_REG32(baseAdd + UART_LCR, HW_RD_REG32(baseAdd + UART_LCR)
                        & 0x7FU);
            break;

        default:
            break;
    }

    return lcrRegValue;
}

static uint32_t UARTOperatingModeSelect(uint32_t baseAdd, uint32_t modeFlag)
{
    uint32_t operMode = 0;

    operMode = HW_RD_REG32(baseAdd + UART_MDR1) & UART_MDR1_MODE_SELECT_MASK;

    /* Programming the MODESELECT field in MDR1. */
    HW_WR_FIELD32(baseAdd + UART_MDR1, UART_MDR1_MODE_SELECT,
                  modeFlag >> UART_MDR1_MODE_SELECT_SHIFT);

    return operMode;
}

static uint32_t UARTIsTransmitterEmpty(uint32_t baseAdd)
{
    uint32_t lcrRegValue = 0, retVal = FALSE;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    if (((uint32_t) UART_LSR_TX_SR_E_MASK |
         (uint32_t) UART_LSR_TX_FIFO_E_MASK) ==
        (HW_RD_REG32(baseAdd + UART_LSR) &
         ((uint32_t) UART_LSR_TX_SR_E_MASK |
          (uint32_t) UART_LSR_TX_FIFO_E_MASK)))
    {
        retVal = (uint32_t) TRUE;
    }
    else
    {
        retVal = (uint32_t) FALSE;
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return retVal;
}

static uint32_t UARTFIFOConfig(uint32_t baseAdd, uint32_t fifoConfig)
{
    uint32_t txGra = (fifoConfig & UART_FIFO_CONFIG_TXGRA) >> 26;
    uint32_t rxGra = (fifoConfig & UART_FIFO_CONFIG_RXGRA) >> 22;

    uint32_t txTrig = (fifoConfig & UART_FIFO_CONFIG_TXTRIG) >> 14;
    uint32_t rxTrig = (fifoConfig & UART_FIFO_CONFIG_RXTRIG) >> 6;

    uint32_t txClr = (fifoConfig & UART_FIFO_CONFIG_TXCLR) >> 5;
    uint32_t rxClr = (fifoConfig & UART_FIFO_CONFIG_RXCLR) >> 4;

    uint32_t dmaEnPath = (fifoConfig & UART_FIFO_CONFIG_DMAENPATH) >> 3;
    uint32_t dmaMode   = (fifoConfig & UART_FIFO_CONFIG_DMAMODE);

    uint32_t enhanFnBitVal = 0;
    uint32_t tcrTlrBitVal  = 0;
    uint32_t tlrValue      = 0;
    uint32_t fcrValue      = 0;

    /* Setting the EFR[4] bit to 1. */
    enhanFnBitVal = UARTEnhanFuncEnable(baseAdd);

    tcrTlrBitVal = UARTSubConfigTCRTLRModeEn(baseAdd);

    /* Enabling FIFO mode of operation. */
    fcrValue |= UART_FCR_FIFO_EN_MASK;

    /* Setting the Receiver FIFO trigger level. */
    if (UART_TRIG_LVL_GRANULARITY_1 != rxGra)
    {
        /* Clearing the RXTRIGGRANU1 bit in SCR. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_RX_TRIG_GRANU1,
                      UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_0);

        /* Clearing the RX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAdd + UART_TLR, UART_TLR_RX_FIFO_TRIG_DMA,
                      0);

        fcrValue &= ~(UART_FCR_RX_FIFO_TRIG_MASK);

        /*
        ** Checking if 'rxTrig' matches with the RX Trigger level values
        ** in FCR.
        */
        if ((UART_FCR_RX_TRIG_LVL_8 == rxTrig) ||
            (UART_FCR_RX_TRIG_LVL_16 == rxTrig) ||
            (UART_FCR_RX_TRIG_LVL_56 == rxTrig) ||
            (UART_FCR_RX_TRIG_LVL_60 == rxTrig))
        {
            fcrValue |= rxTrig & UART_FCR_RX_FIFO_TRIG_MASK;
        }
        else
        {
            /* RX Trigger level will be a multiple of 4. */
            /* Programming the RX_FIFO_TRIG_DMA field of TLR register. */
            HW_WR_FIELD32(baseAdd + UART_TLR, UART_TLR_RX_FIFO_TRIG_DMA,
                          rxTrig);
        }
    }
    else
    {
        /* 'rxTrig' now has the 6-bit RX Trigger level value. */

        rxTrig &= 0x003FU;

        /* Collecting the bits rxTrig[5:2]. */
        tlrValue = (rxTrig & 0x003CU) >> 2;

        /* Collecting the bits rxTrig[1:0] and writing to 'fcrValue'. */
        fcrValue |= (rxTrig & 0x0003U) << UART_FCR_RX_FIFO_TRIG_SHIFT;

        /* Setting the RXTRIGGRANU1 bit of SCR register. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_RX_TRIG_GRANU1,
                      UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_1);

        /* Programming the RX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAdd + UART_TLR, UART_TLR_RX_FIFO_TRIG_DMA, tlrValue);
    }

    /* Setting the Transmitter FIFO trigger level. */
    if (UART_TRIG_LVL_GRANULARITY_1 != txGra)
    {
        /* Clearing the TXTRIGGRANU1 bit in SCR. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_TX_TRIG_GRANU1,
                      UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_0);

        /* Clearing the TX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAdd + UART_TLR, UART_TLR_TX_FIFO_TRIG_DMA,
                      0);

        fcrValue &= ~(UART_FCR_TX_FIFO_TRIG_MASK);

        /*
        ** Checking if 'txTrig' matches with the TX Trigger level values
        ** in FCR.
        */
        if ((UART_FCR_TX_TRIG_LVL_8 == (txTrig)) ||
            (UART_FCR_TX_TRIG_LVL_16 == (txTrig)) ||
            (UART_FCR_TX_TRIG_LVL_32 == (txTrig)) ||
            (UART_FCR_TX_TRIG_LVL_56 == (txTrig)))
        {
            fcrValue |= txTrig & UART_FCR_TX_FIFO_TRIG_MASK;
        }
        else
        {
            /* TX Trigger level will be a multiple of 4. */
            /* Programming the TX_FIFO_TRIG_DMA field of TLR register. */
            HW_WR_FIELD32(baseAdd + UART_TLR, UART_TLR_TX_FIFO_TRIG_DMA,
                          txTrig);
        }
    }
    else
    {
        /* 'txTrig' now has the 6-bit TX Trigger level value. */

        txTrig &= 0x003FU;

        /* Collecting the bits txTrig[5:2]. */
        tlrValue = (txTrig & 0x003CU) >> 2;

        /* Collecting the bits txTrig[1:0] and writing to 'fcrValue'. */
        fcrValue |= (txTrig & 0x0003U) << UART_FCR_TX_FIFO_TRIG_SHIFT;

        /* Setting the TXTRIGGRANU1 bit of SCR register. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_TX_TRIG_GRANU1,
                      UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_1);

        /* Programming the TX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAdd + UART_TLR, UART_TLR_TX_FIFO_TRIG_DMA, tlrValue);
    }

    if (UART_DMA_EN_PATH_FCR == dmaEnPath)
    {
        /* Configuring the UART DMA Mode through FCR register. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_DMA_MODE_CTL,
                      UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_0);

        dmaMode &= 0x1U;

        /* Clearing the bit corresponding to the DMA_MODE in 'fcrValue'. */
        fcrValue &= ~(UART_FCR_DMA_MODE_MASK);

        /* Setting the DMA Mode of operation. */
        fcrValue |= dmaMode << UART_FCR_DMA_MODE_SHIFT;
    }
    else
    {
        dmaMode &= 0x3U;

        /* Configuring the UART DMA Mode through SCR register. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_DMA_MODE_CTL,
                      UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_1);

        /* Programming the DMAMODE2 field in SCR. */
        HW_WR_FIELD32(baseAdd + UART_SCR, UART_SCR_DMA_MODE_2, dmaMode);
    }

    /* Programming the bits which clear the RX and TX FIFOs. */
    fcrValue |= rxClr << UART_FCR_RX_FIFO_CLEAR_SHIFT;
    fcrValue |= txClr << UART_FCR_TX_FIFO_CLEAR_SHIFT;

    /* Writing 'fcrValue' to the FIFO Control Register(FCR). */
    UARTFIFORegisterWrite(baseAdd, fcrValue);

    /* Restoring the value of TCRTLR bit in MCR. */
    UARTTCRTLRBitValRestore(baseAdd, tcrTlrBitVal);

    /* Restoring the value of EFR[4] to the original value. */
    UARTEnhanFuncBitValRestore(baseAdd, enhanFnBitVal);

    return fcrValue;
}

static uint32_t UARTDivisorValCompute(uint32_t moduleClk,
                                    uint32_t baudRate,
                                    uint32_t modeFlag,
                                    uint32_t mirOverSampRate)
{
    uint32_t divisorValue = 0;

    modeFlag &= UART_MDR1_MODE_SELECT_MASK;

    switch (modeFlag)
    {
        case UART16x_OPER_MODE:
        case UART_SIR_OPER_MODE:
            divisorValue = (moduleClk) / (16U * baudRate);
            break;

        case UART13x_OPER_MODE:
            divisorValue = (moduleClk) / (13U * baudRate);
            break;

        case UART_MIR_OPER_MODE:
            divisorValue = (moduleClk) / (mirOverSampRate * baudRate);
            break;

        case UART_FIR_OPER_MODE:
            divisorValue = 0;
            break;

        default:
            break;
    }

    return divisorValue;
}

static uint32_t UARTDivisorLatchWrite(uint32_t baseAdd, uint32_t divisorValue)
{
    volatile uint32_t enhanFnBitVal = 0;
    volatile uint32_t sleepMdBitVal = 0;
    volatile uint32_t lcrRegValue   = 0;
    volatile uint32_t operMode      = 0;
    uint32_t          divRegVal     = 0;

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of EFR[4] and later setting it. */
    enhanFnBitVal = HW_RD_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN);
    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN,
                  UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Operational Mode. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    /*
    ** Collecting the current value of IER[4](SLEEPMODE bit) and later
    ** clearing it.
    */
    sleepMdBitVal = HW_RD_FIELD32(baseAdd + UART_IER, UART_IER_SLEEP_MODE);

    HW_WR_FIELD32(baseAdd + UART_IER, UART_IER_SLEEP_MODE, 0);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of Divisor Latch Registers. */
    divRegVal  = HW_RD_REG32(baseAdd + UART_DLL) & 0xFFU;
    divRegVal |= (HW_RD_REG32(baseAdd + UART_DLH) & 0x3FU) << 8;

    /* Switch the UART instance to Disabled state. */
    operMode = UARTOperatingModeSelect(baseAdd,
                                       (uint32_t) UART_MDR1_MODE_SELECT_MASK);

    /* Writing to Divisor Latch Low(DLL) register. */
    HW_WR_REG32(baseAdd + UART_DLL, divisorValue & 0x00FFU);

    /* Writing to Divisor Latch High(DLH) register. */
    HW_WR_REG32(baseAdd + UART_DLH, (divisorValue & 0x3F00U) >> 8);

    /* Restoring the Operating Mode of UART. */
    UARTOperatingModeSelect(baseAdd, operMode);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Operational Mode. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_OPERATIONAL_MODE);

    /* Restoring the value of IER[4] to its original value. */
    HW_WR_FIELD32(baseAdd + UART_IER, UART_IER_SLEEP_MODE, sleepMdBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4] to its original value. */
    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

    /* Restoring the value of LCR Register. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return divRegVal;
}

static void UARTDivisorLatchDisable(uint32_t baseAdd)
{
    /* Disabling access to Divisor Latch registers by clearing LCR[7] bit. */
    HW_WR_FIELD32(baseAdd + UART_LCR, UART_LCR_DIV_EN,
                  UART_LCR_DIV_EN_DIV_EN_VALUE_0);
}

static void UARTLineCharacConfig(uint32_t baseAdd,
                                 uint32_t wLenStbFlag,
                                 uint32_t parityFlag)
{
    uint32_t lcrRegValue;

    lcrRegValue = HW_RD_REG32(baseAdd + UART_LCR);
    /* Clearing the CHAR_LENGTH and NB_STOP fields in LCR.*/
    lcrRegValue &= ~(UART_LCR_NB_STOP_MASK | UART_LCR_CHAR_LENGTH_MASK);

    /* Programming the CHAR_LENGTH and NB_STOP fields in LCR. */
    lcrRegValue |= wLenStbFlag & (UART_LCR_NB_STOP_MASK |
                                  UART_LCR_CHAR_LENGTH_MASK);

    /* Clearing the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR. */
    lcrRegValue &= ~(UART_LCR_PARITY_TYPE2_MASK |
                     UART_LCR_PARITY_TYPE1_MASK |
                     UART_LCR_PARITY_EN_MASK);

    /* Programming the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR.*/
    lcrRegValue |= parityFlag & (UART_LCR_PARITY_TYPE2_MASK |
                                 UART_LCR_PARITY_TYPE1_MASK |
                                 UART_LCR_PARITY_EN_MASK);
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);
}

static void UARTBreakCtl(uint32_t baseAdd, uint32_t breakState)
{
    /* Programming the BREAK_EN bit in LCR. */
    HW_WR_FIELD32(baseAdd + UART_LCR, UART_LCR_BREAK_EN,
                  breakState >> UART_LCR_BREAK_EN_SHIFT);
}

static uint32_t UARTEnhanFuncEnable(uint32_t baseAdd)
{
    uint32_t enhanFnBitVal = 0;
    uint32_t lcrRegValue   = 0;

    /* Enabling Configuration Mode B of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of ENHANCEDEN bit of EFR. */
    enhanFnBitVal = HW_RD_REG32(baseAdd + UART_EFR) & UART_EFR_ENHANCED_EN_MASK;

    /* Setting the ENHANCEDEN bit in EFR register. */
    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN,
                  UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Programming LCR with the collected value. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return enhanFnBitVal;
}

static uint32_t UARTSubConfigTCRTLRModeEn(uint32_t baseAdd)
{
    uint32_t enhanFnBitVal = 0;
    uint32_t tcrTlrValue   = 0;
    uint32_t lcrRegValue   = 0;

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of EFR[4] and later setting it. */
    enhanFnBitVal = HW_RD_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN);

    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN,
                  UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode A. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_A);

    /* Collecting the bit value of MCR[6]. */
    tcrTlrValue = HW_RD_REG32(baseAdd + UART_MCR) & UART_MCR_TCR_TLR_MASK;

    /* Setting the TCRTLR bit in Modem Control Register(MCR). */
    HW_WR_FIELD32(baseAdd + UART_MCR, UART_MCR_TCR_TLR,
                  UART_MCR_TCR_TLR_TCR_TLR_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4] to its original value. */
    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    return tcrTlrValue;
}

static void UARTFIFORegisterWrite(uint32_t baseAdd, uint32_t fcrValue)
{
    uint32_t divLatchRegVal = 0;
    uint32_t enhanFnBitVal  = 0;
    uint32_t lcrRegValue    = 0;

    /* Switching to Register Configuration Mode A of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_A);

    /* Clearing the contents of Divisor Latch Registers. */
    divLatchRegVal = UARTDivisorLatchWrite(baseAdd, 0x0000);

    /* Set the EFR[4] bit to 1. */
    enhanFnBitVal = UARTEnhanFuncEnable(baseAdd);

    /* Writing the 'fcrValue' to the FCR register. */
    HW_WR_REG32(baseAdd + UART_FCR, fcrValue);

    /* Restoring the value of EFR[4] to its original value. */
    UARTEnhanFuncBitValRestore(baseAdd, enhanFnBitVal);

    /* Programming the Divisor Latch Registers with the collected value. */
    UARTDivisorLatchWrite(baseAdd, divLatchRegVal);

    /* Reinstating LCR with its original value. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);
}

static void UARTTCRTLRBitValRestore(uint32_t baseAdd, uint32_t tcrTlrBitVal)
{
    uint32_t enhanFnBitVal = 0;
    uint32_t lcrRegValue   = 0;

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of EFR[4] and later setting it. */
    enhanFnBitVal = HW_RD_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN);

    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN,
                  UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Configuration Mode A of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_A);

    /* Programming MCR[6] with the corresponding bit value in 'tcrTlrBitVal'. */
    HW_WR_FIELD32(baseAdd + UART_MCR, UART_MCR_TCR_TLR, tcrTlrBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4] to its original value. */
    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);
}

static void UARTEnhanFuncBitValRestore(uint32_t baseAdd, uint32_t enhanFnBitVal)
{
    uint32_t lcrRegValue = 0;

    /* Enabling Configuration Mode B of operation. */
    lcrRegValue = UARTRegConfigModeEnable(baseAdd, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4]. */
    HW_WR_FIELD32(baseAdd + UART_EFR, UART_EFR_ENHANCED_EN,
                  enhanFnBitVal >> UART_EFR_ENHANCED_EN_SHIFT);

    /* Programming LCR with the collected value. */
    HW_WR_REG32(baseAdd + UART_LCR, lcrRegValue);
}
