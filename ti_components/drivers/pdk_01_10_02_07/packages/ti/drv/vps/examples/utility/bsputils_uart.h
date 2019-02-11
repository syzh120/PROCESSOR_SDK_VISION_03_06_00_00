/*
 *  Copyright (c) Texas Instruments Incorporated 2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */

/**
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_UART_API Application UART helper APIs
 *  @{
 */

/**
 *  \file bsputils_uart.h
 *
 *  \brief Header file to use application level uart helper functions.
 */

#ifndef BSPUTILS_UART_H_
#define BSPUTILS_UART_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Uart default timeout */
#define BSP_UTILS_UART_RX_DEFAULT_TIMEOUT   (10U)
/** \brief Timeout value to be passed to have blocking uart read */
#define BSP_UTILS_UART_RX_WAIT_FOREVER      (0xFFFFFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initiates Uart module.
 *
 *  This API should be called before calling read or print functions.
 */
void BspUtils_uartInit(void);

/**
 *  \brief Deinitiates Uart module.
 *
 */
void BspUtils_uartDeinit(void);

/**
 *  \brief Returns if the UART initialization is done.
 *
 *  \return TRUE if initialization is done, else FALSE
 */
Bool BspUtils_isUartInitDone(void);

/**
 *  \brief Prints the string on UART console.
 *
 *  \param string   [IN] String to be printed
 *
 */
void BspUtils_uartPrint(char *string);

/**
 *  \brief Reads string from UART console. This breaks on carraige return or
 *  timeout or char read exceeds the buffer size. This will also terminate the
 *  string with NULL character.
 *
 * \param  pRxBuffer       [OUT] Character read from UART
 *
 * \param  bufSize         [IN] Length of the pRxBuffer in Bytes
 *
 * \param  timeoutVal      [IN] Timeout value in seconds. Pass
 *                              BSP_UTILS_UART_RX_WAIT_FOREVER to wait
 *                              forever.
 *
 * \return  None
 */
Int32 BspUtils_uartGetStr(char *pRxBuffer, UInt32 bufSize, UInt32 timeoutVal);

/**
 *  \brief Reads a char from UART console.
 *
 * \param  pRxBuffer       [OUT] Character read from UART
 *
 * \param  timeoutVal      [IN] Timeout value in seconds. Pass
 *                              BSP_UTILS_UART_RX_WAIT_FOREVER to wait
 *                              forever.
 *
 * \return  None
 */
Int32 BspUtils_uartGetChar(char *pRxBuffer, UInt32 timeoutVal);

/**
 * \brief Reads integer from the UART console
 *        BspUtils_uartInit needs to be called prior to any uarRead
 *
 * \param  pInt            [OUT] Character read from UART
 *
 * \param  timeoutVal      [IN] timeout value in seconds
 *
 * \return BSP_SOK upon success or return error
 */
Int32 BspUtils_uartGetNum(Int32 *pInt, UInt32 timeoutVal);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_APP_H_ */

/* @} */
