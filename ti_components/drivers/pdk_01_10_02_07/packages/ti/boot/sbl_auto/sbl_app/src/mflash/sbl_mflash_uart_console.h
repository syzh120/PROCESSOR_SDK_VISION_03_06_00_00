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
/**
 * \file   sbl_mflash_uart_console.h
 *
 * \brief  This file contains the UART Console APIs used in SBL MFlash.
 */
#ifndef SBL_MFLASH_UART_CONSOLE_H_
#define SBL_MFLASH_UART_CONSOLE_H_
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  This macro defines the various baud rates used
 */
#define BAUD_RATE_115200			(115200U)
#define BAUD_RATE_3000000			(3000000U)
#define BAUD_RATE_3686400			(3686400U)
#define BAUD_RATE_921600			(921600U)
/**
 * \brief  This macro defines the clock to which the UART is configured
 */
#define UART_MODULE_INPUT_CLK		(48000000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

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
 *         SBLMFlashUARTPuts(txArray, -2): This shall print the contents of
 *		   txArray[] until the occurence of a NULL character. \n
 *
 *         SBLMFlashUARTPuts("Hello World", 8): This shall print the first 8
 *		   characters of the string shown. \n
 *
 *         SBLMFlashUARTPuts("Hello World", 20): This shall print the string
 *		   shown until the occurence of the NULL character. Here, the NULL
 *		   character is encountered earlier than the length of 20 bytes.\n
 *
 */
uint32_t SBLMFlashUARTPuts(const char *pTxBuffer,
								  int32_t numBytesToWrite);

/**
 * \brief  This function is used to print hexadecimal numbers on the serial
 *         console.
 *
 * \param  hexValue   The Hexadecimal number to be printed.
 *
 * \return None
 */
void SBLMFlashUARTPutHexNum(uint32_t hexValue);

/**
 * \brief   This function writes a byte on the serial console.
 *
 * \param   byteTx   The byte to be transmitted.
 *
 * \return  None.
 */
void SBLMFlashUARTPutc(uint8_t byteTx);

/**
 * \brief   This function reads a byte entered on the serial console.
 *
 * \param   none
 *
 * \return  Returns the entered byte typecasted as an unsigned character.
 */
uint8_t SBLMFlashUARTGetc(void);

/**
 * \brief   This function reads the numbers typed on the serial console.
 *
 * \return  The value entered on the serial console.
 *
 * \note   The numbers that this function can recieve should lie in the
 *          following range:
 *          [-2^(31)] to [2^(31) - 1] i.e.
 *          0x80000000 to  0x7FFFFFFF
 *
 */
int32_t SBLMFlashUARTGetNum(void);

/**
 * \brief   This function receives hexadecimal numbers entered on the serial
 *          console of the host machine.
 *
 * \param   None
 *
 * \return  The hexadecimal number entered on the serial console of the host
 *          machine.
 *
 * \note    1> The points below explain the ways of entering hexadecimal
 *             numbers:\n
 *             - 0xABCDEF12 - Hexadecimal number preceded by a '0x'.\n
 *             - 0XABCDEF12 - Hexadecimal number preceded by a '0X'.\n
 *             - 0xabcdef12 - Lower-case alphanumeric numbers are allowed.\n
 *             - 0xaBcDeF12 - Intermixing of lower-case and upper-case
 *                            alphanumeric numbers is allowed.\n
 *             - abcdef12   - A preceding '0x' or '0X' is not requried.
 *                            The entered number shall be treated as a
 *                            hexadecimal number.\n
 *             - 12345678   - Interpreted as 0x12345678 and not decimal
 *                            12345678.\n
 *             - xABCDEF12  - A preceding '0' is not required.\n
 *          2> This function does not take into consideration any character
 *             other than a hexadecimal character after reception.\n
 *             Example: Characters in the range G,H,I,...Z or g,h,...,z
 *             are not taken into consideration.\n
 *          3> The maximum value that can be returned by this function
 *             is 0xFFFFFFFF. The reception exits after eight characters have
 *             been received.\n
 *          4> To input a  number lesser that eight characters (Ex: 0x1AB),
 *             press the 'Enter' key after entering the number.\n
 */
uint32_t SBLMFlashUARTGetHexNum(void);

/**
 *  \brief   This function reads a byte entered on the Uart console in a
 *           non-blocking way.
 *
 *  \param 	none
 *
 *  \return  Returns -1 if no char read. 0 if a char is read.
 */
int8_t SBLMFlashUARTGetcNonBlocking(void);

/*
** \brief 	A wrapper function for putting charcater on Uart Console.
*
*  \param 	data 	The byte value to be transmitted
*
*  \return  none
*/
void SBLMFlashUARTConsolePutc(uint8_t data);

/*
** \brief	A wrapper function for getting character from Uart Console in a
*			blocking way.
*
*  \param   none
*
*  \return  The character read from the UART
*/
uint8_t SBLMFlashUARTConsoleGetc(void);

/**
 * \brief   This API reads the num bytes present at the top of the RX FIFO.
 *          However before reading the data from FIFO, it does not check
 *          whether FIFO has fresh data or not.
 *
 * \param   num     	Memory address of the target buffer.
 * \param   baudRate 	Number of bytes to be read from FIFO
 * \param 	operMode	The operation mode of the UART used to calculate divisor
 * \param   parity		The parity for the UART, could be odd, even or none
 * \param   wordLen		The word length in UART communication
 * \param   stopBit		The bit to be sent at the end of each word
 *
 * \return  STW_SOK if UART is configured without any error,
 *          Else returns error code.
 */
int32_t SBLMFlashUARTConsoleConfigInit(UART_INST_t num,
						uint32_t    baudRate,
						uint32_t    operMode,
						uint32_t    parity,
						uint32_t    wordLen,
						uint32_t    stopBit);

/**
 *  \brief   This function reads a byte entered on the Uart console in a
 *           non-blocking way.
 *
 *  \return  Returns -1 if no char read else character if a char is read.
 */
int8_t SBLMFlashUARTConsoleGetcNonBlocking(void);

/**
 * \brief   This API reads the num bytes present at the top of the RX FIFO.
 *          However before reading the data from FIFO, it does not check
 *          whether FIFO has fresh data or not.
 *
 * \param   buf     Memory address of the target buffer.
 * \param   num     Number of bytes to be read from FIFO
 *
 * \return  The data read from the FIFO.
 *
 * \note    1) Since this API does not check whether RX FIFO(RHR) has fresh
 *             data before reading the same, the application should ensure
 *             that RX FIFO has data before calling this API.
 *          2) If the RX FIFO did not have any fresh data and this API is
 *             called, this API would return an unknown value.\n
 */
uint8_t SBLMFlashUARTConsoleFIFOGets(uint8_t *buf, uint8_t num);

/**
 * \brief   This function reads the number of bytes in the FIFO
 *			presently
 *
 * \param   none
 *
 * \return  The number of new bytes in the FIFO
 *
 */
uint32_t SBLMFlashUARTRxFIFOLevelGet(void);

/**
 * \brief   This function set the value of CM_L4PER_UART3_CLKCTRL
 * 			register to set the clock value used to configure the UART.
 *			Current clock values supported are 48Mhz and 192Mhz.
 *
 * \param   fUartClock     The clock to be used.
 *
 * \return  none
 */
void SBLLibUARTSetClock(uint32_t fUartClock);

#ifdef __cplusplus
}
#endif

#endif
