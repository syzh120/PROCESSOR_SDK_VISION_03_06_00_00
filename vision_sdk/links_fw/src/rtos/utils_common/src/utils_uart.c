/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_uart.c
 *
 * \brief  This file has the implementataion for UART
 *
 * \version 0.0 (Jun 2013) : [NN] First version
 * \version 0.1 (Jul 2013) : [NN] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <stdlib.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/sysbios/syncs/SyncSem.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <src/rtos/utils_common/include/utils_uart.h>

/**
 *  GIO_Params_init will initialize the async packet to 2.
 */
#define UART_ASYNC_IOM_PACKET_MAX                                           (2U)

/**
 *******************************************************************************
 * \brief Buffer to read from UART console
 *******************************************************************************
 */
/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#pragma DATA_ALIGN(uartReadBuffer, 128);
static char       uartReadBuffer[UART_BUFFER_SIZE];

/**
 *******************************************************************************
 * \brief UART handle for input stream
 *******************************************************************************
 */
GIO_Handle       uartRxHandle;

/**
 *******************************************************************************
 * \brief UART handle for output stream
 *******************************************************************************
 */
GIO_Handle       uartTxHandle;

/**
 *******************************************************************************
 * \brief Global to check whether UART is initialized or not
 *******************************************************************************
 */
static Bool    InitDone  = FALSE;

/**
 *******************************************************************************
 *
 * \brief Return TRUE if UART init is done
 *
 * \return  TRUE if UART init is done, else FALSE
 *
 *******************************************************************************
 */

Bool System_isUartInitDone(void)
{
    return InitDone;
}

/**
 *******************************************************************************
 *
 * \brief Initializes the UART and sets the GIO handles for the Tx and Rx
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_uartInit(void)
{
    Uart_ChanParams chanParams;
    Error_Block eb;
    GIO_Params  ioParams;
    static char uartName[16]; /* device name MUST be global or static variable */
    static DEV_Struct uartDevObj;
    static GIO_Struct uartTxObj;
    static GIO_Struct uartRxObj;
    static SyncSem_Struct uartTxSyncSemObj;
    static SyncSem_Struct uartRxSyncSemObj;
    static Semaphore_Struct uartTxSemObj;
    static Semaphore_Struct uartRxSemObj;
    static IOM_Packet       uartTxIomObj[UART_ASYNC_IOM_PACKET_MAX];
    static IOM_Packet       uartRxIomObj[UART_ASYNC_IOM_PACKET_MAX];
    DEV_Params    devParams;
    Uart_Params   uartParams;
    SyncSem_Params syncSemParams;
    Semaphore_Params semParams;

    Int32 devId;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    Uart_init();

    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        strcpy(uartName, "/uart0");
        devId = 0;
    }
    else
    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        if(Bsp_boardGetId() == BSP_BOARD_TDA3XX_AR12XX_RADAR)
        {
            strcpy(uartName, "/uart1");
            Bsp_boardSelectDevice(BSP_DRV_ID_UART, BSP_DEVICE_UART_INST_ID_1);
            devId = 1;
        }
        else
        {
            strcpy(uartName, "/uart2");
            devId = 2;
        }
    }
    else
    {
        /* default */
        strcpy(uartName, "/uart0");
        devId = 0;
    }

    uartParams              = Uart_PARAMS;
    uartParams.opMode       = UART_OPMODE_INTERRUPT;
    uartParams.hwiNumber    = 8u;
    uartParams.rxThreshold  = UART_RXTRIGLVL_8;
    uartParams.txThreshold  = UART_TXTRIGLVL_56;
    uartParams.baudRate     = UART_BAUDRATE_115_2K;
    uartParams.prcmDevId    = 0;
    /* INVARIANT_CONDITION.UNREACH
    * MISRAC_2004_Rule_13.7
    * MISRAC_WAIVER:
    * Code is currently unreachable.
    * This is kept to ensure future updates to modes.
    */
    if(uartParams.opMode == UART_OPMODE_POLLED)
    {
        printf(" SYSTEM: UART: POLLED Mode is Selected \n");
    }
    else if(uartParams.opMode == UART_OPMODE_INTERRUPT)
    {
        printf(" SYSTEM: UART: INTERRUPT Mode is Selected \n");
    }
    else
    {
        /* MISRA WARNING */
    }
    uartParams.enableCache = (Bool)FALSE;

    /* initialise the edma library and get the EDMA handle */
    chanParams.hEdma = NULL;

    /* If cross bar events are being used then make isCrossBarIntEn = TRUE and
     * choose appropriate interrupt number to be mapped (assign it to
     * intNumToBeMapped)
     */
    chanParams.crossBarEvtParam.isCrossBarIntEn = (Bool)FALSE;

    chanParams.crossBarEvtParam.intNumToBeMapped = 0xFFU;

    ioParams.chanParams = (Ptr)&chanParams;

    DEV_Params_init(&devParams);
    devParams.deviceParams = &uartParams;
    devParams.initFxn = NULL;
    devParams.devid = devId;

/* MISRA.CAST.CONST
 * MISRAC_2004 Rule_11.5
 * MISRAC_WAIVER:
 * External package errors like bios which are not
 * part of VSDK package can't be fixed
 */
    DEV_construct(&uartDevObj, uartName, (Ptr)&Uart_IOMFXNS, &devParams, &eb);

    SyncSem_Params_init(&syncSemParams);

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&uartTxSemObj, 0, &semParams);

    syncSemParams.sem = Semaphore_handle(&uartTxSemObj);

    SyncSem_construct(&uartTxSyncSemObj, &syncSemParams, &eb);

    ioParams.sync =
        SyncSem_Handle_upCast(
            SyncSem_handle(
                &uartTxSyncSemObj
            )
        )
        ;

    if(ioParams.numPackets > UART_ASYNC_IOM_PACKET_MAX)
    {
        UTILS_assert(ioParams.numPackets <= UART_ASYNC_IOM_PACKET_MAX);
    }
    memset(&uartTxIomObj[0], 0, ioParams.numPackets * sizeof (IOM_Packet));
    ioParams.packets = &uartTxIomObj[0];

    /* create the required channels(TX/RX) for the UART demo */
    GIO_construct(&uartTxObj, uartName, (UInt32)GIO_OUTPUT, &ioParams, &eb);

    SyncSem_Params_init(&syncSemParams);

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&uartRxSemObj, 0, &semParams);

    syncSemParams.sem = Semaphore_handle(&uartRxSemObj);

    SyncSem_construct(&uartRxSyncSemObj, &syncSemParams, &eb);

    ioParams.sync =
        SyncSem_Handle_upCast(
            SyncSem_handle(
                &uartRxSyncSemObj
            )
        )
        ;

    memset(&uartRxIomObj[0], 0, ioParams.numPackets * sizeof (IOM_Packet));
    ioParams.packets = &uartRxIomObj[0];

    GIO_construct(&uartRxObj, uartName, (UInt32)GIO_INPUT, &ioParams, &eb);

    uartTxHandle = GIO_handle(&uartTxObj);
    uartRxHandle = GIO_handle(&uartRxObj);
    /* INVARIANT_CONDITION.UNREACH
    * MISRAC_2004_Rule_13.7
    * MISRAC_WAIVER:
    * Code is currently unreachable.
    * This is kept to ensure future updates by the called function.
    */
    if ((NULL == uartRxHandle) || (NULL == uartTxHandle))
    {
        printf(" SYSTEM: UART: ERROR: GIO_create(%s) Failed !!!\n", uartName);
    }
    else
    {
        InitDone = (Bool)TRUE;
    }
}

/**
 *******************************************************************************
 *
 * \brief Prints the string in UART console , System_uartInit must succeed
 *        Before a call to this function
 *
 * \param  string     [IN] Input string
 *
 * \return  None
 *
 *******************************************************************************
 */
void uartPrint(char *string)
{
    size_t len;
    Int32    status  = IOM_COMPLETED;
    if(InitDone == (Bool)TRUE)
    {
        len = strlen(string);

        /* Transmit the string*/
        status = GIO_write(uartTxHandle, string, &len);

        if (IOM_COMPLETED != status)
        {
            printf(" SYSTEM: UART: ERROR: GIO_write failed (status = %d) !!! \n",status);
        }
    }
    else
    {
        /*
        printf("\n System_uartInit needs to be called prior to any uartprint");
        */
    }
}

/**
 *******************************************************************************
 *
 * \brief Reads the Input message from the UART console
 *        System_uartInit needs to be called prior to any uarRead
 *
 * \param  pOption     [OUT] Character read from UART
 *
 * \return  None
 *
 *******************************************************************************
 */
Void uartRead(Int8 *pOption)
{
    Int32   nStatus  = IOM_COMPLETED;
    size_t  nLen    = 1u ;

    nStatus = GIO_read(uartRxHandle, &uartReadBuffer, &nLen);
    if (IOM_COMPLETED != nStatus)
    {
        printf(" SYSTEM: UART: ERROR: GIO_read failed (status = %d) !!! \n",nStatus);
    }

    /* copy only one char */
    *pOption = (Int8)uartReadBuffer[nLen - 1U];
}

/**
 *******************************************************************************
 *
 * \brief This function enables creating a UART device apart from the one used
 *        for console IO.
 *
 * \param  uartDevId     Name of the uart device getting used. Can be of the form
 *                      "/uart0" or "/uart1" etc.
 * \param  uartDeviceObj   Pointer to the object created by the API.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Utils_uartCreateDevice(UInt32 uartDevId, DEV_Struct *uartDeviceObj)
{
    Uart_Params   uartParams;
    Error_Block eb;
    DEV_Params    devParams;
    static char uartDeviceName[16]; /* device name MUST be global or static variable */

    if (System_isUartInitDone() == FALSE)
    {
        Uart_init();
    }
    Error_init(&eb);

    uartParams              = Uart_PARAMS;
    uartParams.opMode       = UART_OPMODE_INTERRUPT;
    uartParams.hwiNumber    = 8u;
    uartParams.rxThreshold  = UART_RXTRIGLVL_8;
    uartParams.txThreshold  = UART_TXTRIGLVL_56;
    uartParams.baudRate     = UART_BAUDRATE_115_2K;
    uartParams.prcmDevId    = 0;
    /* INVARIANT_CONDITION.UNREACH
    * MISRAC_2004_Rule_13.7
    * MISRAC_WAIVER:
    * Code is currently unreachable.
    * This is kept to ensure future updates to modes.
    */
    if(uartParams.opMode == UART_OPMODE_POLLED)
    {
        printf(" SYSTEM: UART: POLLED Mode is Selected \n");
    }
    else if(uartParams.opMode == UART_OPMODE_INTERRUPT)
    {
        printf(" SYSTEM: UART: INTERRUPT Mode is Selected \n");
    }
    else
    {
        /* MISRA WARNING */
    }
    uartParams.enableCache = (Bool)FALSE;

    DEV_Params_init(&devParams);
    devParams.deviceParams = &uartParams;
    devParams.initFxn = NULL;
    devParams.devid = uartDevId;

    switch(uartDevId)
    {
        case 0:strcpy(uartDeviceName, "/uart0"); break;
        case 1U:strcpy(uartDeviceName, "/uart1"); break;
        case 2U:strcpy(uartDeviceName, "/uart2"); break;
        case 3U:strcpy(uartDeviceName, "/uart3"); break;
        case 4U:strcpy(uartDeviceName, "/uart4"); break;
        case 5U:strcpy(uartDeviceName, "/uart5"); break;
        case 6U:strcpy(uartDeviceName, "/uart6"); break;
        case 7U:strcpy(uartDeviceName, "/uart7"); break;
        case 8U:strcpy(uartDeviceName, "/uart8"); break;
        case 9U:strcpy(uartDeviceName, "/uart9"); break;
        default:
            Vps_printf(" UTILS_UART: Unsupported Dev ID selected !!\n");
            UTILS_assert(0U);
            break;
    }

/* MISRA.CAST.CONST
 * MISRAC_2004 Rule_11.5
 * MISRAC_WAIVER:
 * External package errors like bios which are not
 * part of VSDK package can't be fixed
 */
    DEV_construct(uartDeviceObj, uartDeviceName, (Ptr)&Uart_IOMFXNS, &devParams, &eb);
}

/**
 *******************************************************************************
 *
 * \brief This function enables deleting a UART device apart from the one used
 *        for console IO.
 *
 * \param  uartDeviceObj   Pointer to the object deleted by the API.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Utils_uartDeleteDevice(DEV_Struct *uartDeviceObj)
{
    DEV_destruct(uartDeviceObj);
}
