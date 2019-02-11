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
 *  \file bsputils_uart.c
 *
 *  \brief This file has the implementataion for UART print fxn on top of BSP
 *  UART driver
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <stdio.h>
#include <string.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/sysbios/syncs/SyncSem.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* UART RX Task sleep in mSec */
#define BSPUTILS_UART_RX_SLEEP   (500U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    /** \brief UART handle for input stream */
    GIO_Handle       uartRxHandle;
    /** \brief UART handle for output stream */
    GIO_Handle       uartTxHandle;
    /** \brief UART device object for static allocation */
    DEV_Struct       uartDevObj;
    /** \brief UART output stream GIO object for static allocation */
    GIO_Struct       uartTxObj;
    /** \brief UART input stream GIO object for static allocation */
    GIO_Struct       uartRxObj;
    /** \brief UART output stream Sync sem object for static allocation */
    SyncSem_Struct   uartTxSyncSemObj;
    /** \brief UART input stream Sync sem object for static allocation */
    SyncSem_Struct   uartRxSyncSemObj;
    /** \brief UART output stream Semaphore object for static allocation */
    Semaphore_Struct uartTxSemObj;
    /** \brief UART input stream Semaphore object for static allocation */
    Semaphore_Struct uartRxSemObj;
    /** \brief To check whether UART is initialized or not */
    Bool             uartInitDone;
    /** \brief UART device name string */
    char             uartName[16];
}BspUtils_uartObj;

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
    Uart_ChanParams  chanParams;
    Error_Block      eb;
    GIO_Params       ioParams;
    DEV_Params       devParams;
    Uart_Params      uartParams;
    SyncSem_Params   syncSemParams;
    Semaphore_Params semParams;
    UInt64           tempTimeStampVal;

    Int32 devId;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    Uart_init();

    if (Bsp_platformIsTda2xxFamilyBuild())
    {
        if (Bsp_boardGetId() == BSP_BOARD_MONSTERCAM)
        {
            strcpy(gBspUtilsUartObj.uartName, "/uart2");
            devId = 2;
        }
        else
        {
            strcpy(gBspUtilsUartObj.uartName, "/uart0");
            devId = 0;
        }
    }
    else
    if (Bsp_platformIsTda3xxFamilyBuild())
    {
        strcpy(gBspUtilsUartObj.uartName, "/uart2");
        devId = 2;
    }
    else
    {
        /* default */
        strcpy(gBspUtilsUartObj.uartName, "/uart0");
        devId = 0;
    }

    uartParams             = Uart_PARAMS;
    uartParams.opMode      = UART_OPMODE_POLLED;
    uartParams.hwiNumber   = 8u;
    uartParams.rxThreshold = UART_RXTRIGLVL_8;
    uartParams.txThreshold = UART_TXTRIGLVL_56;
    uartParams.baudRate    = UART_BAUDRATE_115_2K;
    uartParams.prcmDevId   = 0;
    /* Timeout value for 1 sec in terms of number of ticks */
    tempTimeStampVal = BspOsal_getTimestampFreq();
    if ((tempTimeStampVal & (UInt64) 0xFFFFFFFF00000000U) != (UInt64) 0)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Timeout value out of range!!\r\n");
        /* defaulting to max timeout supported */
        tempTimeStampVal = 0xFFFFFFF0U;
    }
    uartParams.polledModeTimeout = (UInt32) (tempTimeStampVal);

    uartParams.enableCache = (Bool) FALSE;

    /* initialise the edma library and get the EDMA handle */
    chanParams.hEdma = NULL;

    /* If cross bar events are being used then make isCrossBarIntEn = TRUE and
     * choose appropriate interrupt number to be mapped (assign it to
     * intNumToBeMapped)
     */
    chanParams.crossBarEvtParam.isCrossBarIntEn = (Bool) FALSE;

    chanParams.crossBarEvtParam.intNumToBeMapped = 0xFFU;

    ioParams.chanParams = (Ptr) & chanParams;

    DEV_Params_init(&devParams);
    devParams.deviceParams = &uartParams;
    devParams.initFxn      = NULL;
    devParams.devid        = devId;

    DEV_construct(&gBspUtilsUartObj.uartDevObj, gBspUtilsUartObj.uartName,
                  (Ptr) & Uart_IOMFXNS,
                  &devParams,
                  &eb);

    SyncSem_Params_init(&syncSemParams);

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&gBspUtilsUartObj.uartTxSemObj, 0, &semParams);

    syncSemParams.sem = Semaphore_handle(&gBspUtilsUartObj.uartTxSemObj);

    SyncSem_construct(&gBspUtilsUartObj.uartTxSyncSemObj, &syncSemParams, &eb);

    ioParams.sync =
        SyncSem_Handle_upCast(SyncSem_handle(&gBspUtilsUartObj.uartTxSyncSemObj));

    /* create the required channels(TX/RX) for the UART demo */
    GIO_construct(&gBspUtilsUartObj.uartTxObj, gBspUtilsUartObj.uartName,
                  (UInt32) GIO_OUTPUT,
                  &ioParams,
                  &eb);

    SyncSem_Params_init(&syncSemParams);

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&gBspUtilsUartObj.uartRxSemObj, 0, &semParams);

    syncSemParams.sem = Semaphore_handle(&gBspUtilsUartObj.uartRxSemObj);

    SyncSem_construct(&gBspUtilsUartObj.uartRxSyncSemObj, &syncSemParams, &eb);

    ioParams.sync =
        SyncSem_Handle_upCast(SyncSem_handle(&gBspUtilsUartObj.uartRxSyncSemObj));

    GIO_construct(&gBspUtilsUartObj.uartRxObj, gBspUtilsUartObj.uartName,
                  (UInt32) GIO_INPUT,
                  &ioParams,
                  &eb);

    gBspUtilsUartObj.uartTxHandle = GIO_handle(&gBspUtilsUartObj.uartTxObj);
    gBspUtilsUartObj.uartRxHandle = GIO_handle(&gBspUtilsUartObj.uartRxObj);

    if ((NULL != gBspUtilsUartObj.uartRxHandle) &&
        (NULL != gBspUtilsUartObj.uartTxHandle))
    {
        gBspUtilsUartObj.uartInitDone = (Bool) TRUE;
    }
}

/**
 *  \brief Deinitiates Uart module.
 *
 */
void BspUtils_uartDeinit(void)
{
    GIO_Struct *uartGioStruct;

    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        if (NULL != gBspUtilsUartObj.uartTxHandle)
        {
            uartGioStruct = GIO_struct(gBspUtilsUartObj.uartTxHandle);
            GIO_destruct(uartGioStruct);
            gBspUtilsUartObj.uartTxHandle = NULL;
        }
        if (NULL != gBspUtilsUartObj.uartRxHandle)
        {
            uartGioStruct = GIO_struct(gBspUtilsUartObj.uartRxHandle);
            GIO_destruct(uartGioStruct);
            gBspUtilsUartObj.uartRxHandle = NULL;
        }
        DEV_destruct(&gBspUtilsUartObj.uartDevObj);
        gBspUtilsUartObj.uartInitDone = FALSE;
    }
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
    size_t len;
    Int32  status;

    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        GT_assert(BspAppTrace, (NULL != gBspUtilsUartObj.uartTxHandle));
        len = strlen(string);

        /* Transmit the string*/
        status = GIO_write(gBspUtilsUartObj.uartTxHandle, string, &len);
        GT_assert(BspAppTrace, (IOM_COMPLETED == status));
    }
}

Int32 BspUtils_uartGetStr(char *pRxBuffer, UInt32 bufSize, UInt32 timeoutVal)
{
    size_t nLen = 1U;
    Int32  retVal, bspRetVal = BSP_SOK;
    UInt32 readBufLen = 0;
    Bool   loopBreak  = FALSE;
    char   tempChar;

    GT_assert(BspAppTrace, (NULL != pRxBuffer));

    if (bufSize > 0U)
    {
        /* Terminate with null char in case of error */
        pRxBuffer[0U] = (char) '\0';
    }

    /* Need at least two char to hold a string */
    if ((gBspUtilsUartObj.uartInitDone == (Bool) TRUE) && (bufSize > 1U))
    {
        GT_assert(BspAppTrace, (NULL != gBspUtilsUartObj.uartRxHandle));
        while (loopBreak != (Bool) TRUE)
        {
            nLen = 1U;
            retVal = GIO_read(gBspUtilsUartObj.uartRxHandle, &tempChar, &nLen);
            if (retVal == IOM_COMPLETED)
            {
                /* Break when CR or Esc char is pressed.
                 * 0xD  - ASCII value of Carriage Return.
                 * 0x1B - ASCII value of ESC character.
                 */
                if ((((char) 0xD) == tempChar) || (((char) 0x1B) == tempChar))
                {
                    tempChar = (char) '\0';
                    loopBreak = (Bool) TRUE;
                }

                pRxBuffer[readBufLen] = tempChar;
                readBufLen++;
                if ((readBufLen >= (bufSize - 1U)) &&
                    (loopBreak == (Bool) FALSE))
                    /* Handle already terminated case */
                {
                    pRxBuffer[readBufLen] = (char) '\0';
                    loopBreak = (Bool) TRUE;
                }
            }
            else
            {
                if (retVal == IOM_ETIMEOUT)
                {
                    if (timeoutVal != BSP_UTILS_UART_RX_WAIT_FOREVER)
                    {
                        timeoutVal -= 1U;
                        if (timeoutVal == 0)
                        {
                            bspRetVal = BSP_ETIMEOUT;
                            loopBreak = (Bool) TRUE;
                        }
                    }
                }
                else
                {
                    bspRetVal = BSP_EFAIL;
                    loopBreak = (Bool) TRUE;
                }
            }
        }
    }
    else
    {
        bspRetVal = BSP_EFAIL;
    }

    return bspRetVal;
}

Int32 BspUtils_uartGetChar(char *pRxBuffer, UInt32 timeoutVal)
{
    size_t nLen = 1U;
    Int32  retVal, bspRetVal = BSP_SOK;
    Bool   loopBreak  = FALSE;

    GT_assert(BspAppTrace, (NULL != pRxBuffer));

    if (gBspUtilsUartObj.uartInitDone == (Bool) TRUE)
    {
        GT_assert(BspAppTrace, (NULL != gBspUtilsUartObj.uartRxHandle));
        while (loopBreak != (Bool) TRUE)
        {
            nLen = 1U;
            retVal = GIO_read(gBspUtilsUartObj.uartRxHandle, pRxBuffer, &nLen);
            if (retVal != IOM_COMPLETED)
            {
                if (retVal == IOM_ETIMEOUT)
                {
                    if (timeoutVal != BSP_UTILS_UART_RX_WAIT_FOREVER)
                    {
                        timeoutVal -= 1U;
                        if (timeoutVal == 0)
                        {
                            bspRetVal = BSP_ETIMEOUT;
                            loopBreak = (Bool) TRUE;
                        }
                    }
                }
                else
                {
                    bspRetVal = BSP_EFAIL;
                    loopBreak = (Bool) TRUE;
                }
            }
            else
            {
                loopBreak = (Bool) TRUE;
            }
        }
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
