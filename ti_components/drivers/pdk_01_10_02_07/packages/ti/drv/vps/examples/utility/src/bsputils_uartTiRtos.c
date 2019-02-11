/*
 *  Copyright (c) Texas Instruments Incorporated 2015-2017
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
 *  \file bsputils_uartTiRtos.c
 *
 *  \brief This file has the implementataion for UART print fxn on top of TI
 *  RTOS UART driver
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#include <ti/drv/uart/UART_stdio.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
#define UART_INSTANCE 0
#endif
#if defined (SOC_TDA3XX)
#define UART_INSTANCE 2
#endif

/* UART RX Task sleep in mSec */
#define BSPUTILS_UART_RX_SLEEP   (500U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    /** \brief To check whether UART is initialized or not */
    Bool             uartInitDone;
} BspUtils_uartObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Bsp Utils Global UART Object */
static BspUtils_uartObj gBspUtilsUartObj = {0};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief Return TRUE if UART init is done
 *
 * \return  TRUE if UART init is done, else FALSE
 */
Bool BspUtils_isUartInitDone(void)
{
    return (gBspUtilsUartObj.uartInitDone);
}

/**
 * \brief Initializes the UART and sets the GIO handles for the Tx and Rx
 *
 * \return  None
 */
void BspUtils_uartInit(void)
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /* AM devices use board library to initialize the UART Stdio
     * hence no other initializations are required */
#else
    UART_stdioInit(UART_INSTANCE);
#endif

    gBspUtilsUartObj.uartInitDone = (Bool) TRUE;

    return;
}

/**
 *  \brief Deinitiates Uart module.
 *
 */
void BspUtils_uartDeinit(void)
{
    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        /* TODO: Added deinit once uart console implements deinit */
        gBspUtilsUartObj.uartInitDone = FALSE;
    }

    return;
}

/**
 * \brief Prints the string in UART console , BspUtils_uartInit must succeed
 *        Before a call to this function
 *
 * \param  string     [IN] Input string
 *
 * \return  None
 */
void BspUtils_uartPrint(char *string)
{
    GT_assert(BspAppTrace, (NULL != string));

    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        UART_printf("%s", string);
    }

    return;
}

Int32 BspUtils_uartGetStr(char *pRxBuffer, UInt32 bufSize, UInt32 timeoutVal)
{
    Int32  bspRetVal = BSP_SOK;

    GT_assert(BspAppTrace, (NULL != pRxBuffer));

    /* TODO: Implement timeout once the support is added in the UART driver */
    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        UART_gets(pRxBuffer, (int32_t) bufSize);
    }
    else
    {
        bspRetVal = BSP_EFAIL;
    }

    return bspRetVal;
}

Int32 BspUtils_uartGetChar(char *pRxBuffer, UInt32 timeoutVal)
{
    Int32  bspRetVal = BSP_SOK;

    GT_assert(BspAppTrace, (NULL != pRxBuffer));

    /* TODO: Implement timeout once the support is added in the UART driver */
    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        *pRxBuffer = UART_getc();
    }
    else
    {
        bspRetVal = BSP_EFAIL;
    }

    return bspRetVal;
}

/**
 * \brief Reads integer from the UART console
 *        BspUtils_uartInit needs to be called prior to any uarRead
 *
 * \param  pInt            [OUT] Character read from UART
 *
 * \return BSP_SOK upon success or return error
 */
Int32 BspUtils_uartGetNum(Int32 *pInt, UInt32 timeoutVal)
{
    char   tempBuff[15];
    Int32  retVal;
    Int32  sign  = 1;
    Int32  value = 0;
    UInt32 tempBuffCnt = 0U;
    Bool   loopBreak = FALSE;

    /* TODO: Implement timeout once the support is added in the UART driver */
    retVal = BspUtils_uartGetStr(tempBuff, sizeof(tempBuff), timeoutVal);
    if (retVal == BSP_SOK)
    {
        if ((char) '-' == tempBuff[0])
        {
            sign = -1;
            tempBuffCnt = 1U;
        }

        while (loopBreak != (Bool) TRUE)
        {
            if ((char) '\0' == tempBuff[tempBuffCnt])
            {
                loopBreak = (Bool) TRUE;
            }
            else if (((int32_t) tempBuff[tempBuffCnt] < 0x30) ||
                     ((int32_t) tempBuff[tempBuffCnt] > 0x39))
            {
                /* Check if the char is in valid range */
                value = 0;
                loopBreak = (Bool) TRUE;
                retVal = BSP_EFAIL;
            }
            else
            {
                /* valid char */
            }
            if(loopBreak == (Bool) FALSE)
            {
                /* Subtracting 0x30 to convert the representation of the digit
                * from ASCII to hexadecimal. */
                value = (value * 10) + ((int32_t) tempBuff[tempBuffCnt] - 0x30);
                tempBuffCnt++;
            }
        }

        *pInt = value * sign;
    }

    return retVal;
}
