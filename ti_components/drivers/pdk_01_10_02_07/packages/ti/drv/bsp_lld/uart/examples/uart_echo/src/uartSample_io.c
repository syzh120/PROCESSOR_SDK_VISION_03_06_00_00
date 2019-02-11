/*
 *  Copyright (C) 2012-2017 Texas Instruments Incorporated
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
 * \file      uartSample_io.c
 *
 * \brief     This file contains the test / demo code to demonstrate the
 *            UART driver implemented for SYS/BIOS 6.
 *
 */

/* ========================================================================== */
/*                              INCLUDE FILES                                 */
/* ========================================================================== */
#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>

/* ========================================================================== */
/*                            EXTERNAL VARIABLES                              */
/* ========================================================================== */

/* UART handle for input stream                                               */
extern GIO_Handle uartRxHandle;

/* UART handle for output stream                                              */
extern GIO_Handle uartTxHandle;

/* ========================================================================== */
/*                             MACRO DEFINITIONS                              */
/* ========================================================================== */

#define SIZEOF_UART_START_STRING    (200U)

#define APP_UART_NUM_BYTES          (1000U)

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */

/**
 * \brief   Variable to hold the starting message printing string.
 *
 * \note    Buffer alignement is required only when working in DMA Mode.
 */
#pragma DATA_ALIGN(uartTestStringStart, 128);
static char       uartTestStringStart[SIZEOF_UART_START_STRING];

/**
 * \brief   Variable to hold the user supplied 1000 bytes
 *
 * \note    Buffer alignement is required only when working in DMA Mode.
 */
#pragma DATA_ALIGN(uartBuffer, 128);
static char       uartBuffer[1000];

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/**
 * \brief    Function to demonstrate the UART functionality.This function
 *           requests the user to input 1000 bytes and reads the same and
 *           tranmits the same back to the user.
 *
 * \param    None
 *
 * \return   None
 *
 */
void UartApp_startUartSample(void)
{
    size_t len    = 0, totalLen = 0;
    char  *string = NULL;
    Int    status = IOM_COMPLETED;

    System_printf(
        "\r\nStart of UART sample application, "
        "check the serial Terminal to proceed \r\n");

    string = "** UART Demo Starts:  INPUT a file of size 1000 bytes **";
    /* Copy to start string to Cache aligned buffer */
    strncpy(uartTestStringStart, string, (sizeof (uartTestStringStart) - 1U));

    /* calculate the length of data */
    len = strlen(uartTestStringStart);

    /* Transmit the string */
    status = GIO_write(uartTxHandle, &uartTestStringStart, &len);
    if (IOM_COMPLETED != status)
    {
        /* Report Error */
        System_printf("\r\nGIO_write failed. returned : %d \r\n", status);
    }

    /* Now the user will input a string of APP_UART_NUM_BYTES bytes.
     * Hence submit a read request for APP_UART_NUM_BYTES bytes and loop
     * till we receive that many bytes */
    while (1U)
    {
        len    = APP_UART_NUM_BYTES - totalLen;
        status = GIO_read(uartRxHandle, &uartBuffer[totalLen], &len);
        if (IOM_COMPLETED != status)
        {
            /* Report Error */
            System_printf("\r\nGIO_read failed. returned : %d \r\n", status);
        }
        totalLen += len;
        if (totalLen >= APP_UART_NUM_BYTES)
        {
            break;
        }
    }

    /* Echo the input data to User for verification */
    len    = totalLen;
    status = GIO_write(uartTxHandle, &uartBuffer, &len);
    if (IOM_COMPLETED != status)
    {
        /* Report Error */
        System_printf("\r\nGIO_write failed. returned : %d \r\n", status);
    }

    return;
}
