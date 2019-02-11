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
 * \file    uartSample_main.c
 *
 * \brief   This file contains the test / demo code to demonstrate the
 *          UART driver implemented for SYS/BIOS 6
 */

/* ========================================================================== */
/*                              INCLUDE FILES                                 */
/* ========================================================================== */

#include <xdc/std.h>
#include <stdio.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/hal/Core.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>

/* ========================================================================== */
/*                            EXTERNAL VARIABLES                              */
/* ========================================================================== */

/* ========================================================================== */
/*                            EXTERNAL REFERENCES                             */
/* ========================================================================== */

void UartApp_startUartSample(void);
EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);

/* ========================================================================== */
/*                             MACRO DEFINITIONS                              */
/* ========================================================================== */

#define UART_NUM_IOP         (1U)

/* ========================================================================== */
/*                           LOCAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */

static void UartApp_edmaInit(void);
static void UartApp_tskHeartBeat(void);

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */


UInt32                   gIsI2cInitReq;

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle         gEdmaHandle;

/* UART handle for input stream                                               */
GIO_Handle               uartRxHandle;

/* UART handle for output stream                                              */
GIO_Handle               uartTxHandle;

Uart_Params              uartParams;

/* Global function prototypes */
void UartApp_userInit(void);

static Char *const       devName[] = {"/uart0", "/uart1", "/uart0"};
extern const IOM_Fxns    Uart_IOMFXNS;
Int devid;

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/**
 *  \brief  Int32 main(void)
 *
 *   Main function of the sample application. This function enables
 *   the uart instance in the power sleep controller and also
 *   enables the pinmux for the Uart 0 instance.
 *
 *  \param  None
 *  \return None
 */
Int32 main(void)
{
    System_printf("\r\nUart Sample Main\r\n");

    BIOS_start();

    return (0);
}

/**
 * \brief      Entry point for the main task. This creates the required channels
 *             and calls the required functions for demonstrating the UART
 *             driver
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
void UartApp_sampleTask(UArg arg1, UArg arg2)
{
    Uart_ChanParams        chanParams;
    Error_Block            eb;
    GIO_Params             ioParams;
    Bsp_PlatformInitParams platInitPrms;

    Error_init(&eb);
#if defined (SOC_TDA3XX)
    System_printf("\r\nEnter the uart instance to use: 0, 1 or 2\r\n");
    scanf("%d", &devid);
    if ((devid < 0) || (devid > 2))
    {
        System_printf("\r\nInvalid Input defaulting to instance 0\r\n");
        devid = 0;
    }
#else
    devid = 0;
#endif

    GIO_addDevice(devName[devid], (xdc_Ptr) & Uart_IOMFXNS, &UartApp_userInit,
                  devid, (xdc_Ptr) & uartParams);

    /* isPinMuxSettingReq parameter will be initialised to TRUE */
    BspPlatformInitParams_init(&platInitPrms);

    /* Call the EVM specific initialization function                          */
    Bsp_platformInit(&platInitPrms);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);
    /* initialise the edma library and get the EDMA handle                    */
    UartApp_edmaInit();

    /* update the edma Handle                                                 */
    chanParams.hEdma = gEdmaHandle;

    /* If cross bar events are being used then make isCrossBarIntEn = TRUE and
     * choose appropriate interrupt number to be mapped (assign it to
     * intNumToBeMapped)
     */
    /* Cross bar evt disabled */
    chanParams.crossBarEvtParam.isCrossBarIntEn  = (UInt32) FALSE;
    chanParams.crossBarEvtParam.intNumToBeMapped = 0xFF;  /* Invalid number */

    ioParams.chanParams = (Ptr) & chanParams;

    /* create the required channels(TX/RX) for the UART demo                  */
    uartTxHandle = GIO_create(devName[devid], GIO_OUTPUT, &ioParams, &eb);
    uartRxHandle = GIO_create(devName[devid], GIO_INPUT, &ioParams, &eb);

    if ((NULL == uartRxHandle) || (NULL == uartTxHandle))
    {
        System_printf("\r\nUART : GIO_create Failed.......!\r\n\n");
    }
    else
    {
        /* Run the uart sample application                                    */
        UartApp_startUartSample();

        /* Stream Deletion */
        GIO_delete(&uartTxHandle); /* TX Channel deletion */
        GIO_delete(&uartRxHandle); /* RX Channel deletion */

        BspUtils_appDefaultSerialDeInit(gIsI2cInitReq);

        /* Start the HeartBeat Prints                                         */
        UartApp_tskHeartBeat();
    }
}

/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
static void UartApp_edmaInit(void)
{
    EDMA3_DRV_Result edmaResult = 0;

    gEdmaHandle = edma3init(0, &edmaResult);
    UInt coreId = 2;

    coreId = Core_getId();
    System_printf("\r\nCore Id = %d\r\n", coreId);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("\r\nEDMA driver initialization FAIL\r\n");
    }
    else
    {
        System_printf("\r\nEDMA driver initialization PASS.\r\n");
    }
}

/*
 * UART0 init function called when creating the driver.
 */
void UartApp_userInit(void)
{
    Int32 retVal = FVID2_SOK;
    Uart_init();

    uartParams             = Uart_PARAMS;
    uartParams.opMode      = UART_OPMODE_INTERRUPT;
    uartParams.hwiNumber   = 8;
    uartParams.rxThreshold = UART_RXTRIGLVL_8;
    uartParams.txThreshold = UART_TXTRIGLVL_56;
    uartParams.baudRate = UART_BAUDRATE_115_2K;
    uartParams.prcmDevId = 0;

    if (UART_OPMODE_POLLED == uartParams.opMode)
    {
        System_printf("Uart is configured in Polled mode \r\n");
    }
    else if (UART_OPMODE_INTERRUPT == uartParams.opMode)
    {
        System_printf("Uart is configured in Interrupt mode \r\n");
    }
    else if (UART_OPMODE_DMAINTERRUPT == uartParams.opMode)
    {
        System_printf("Uart is configured in dma mode \r\n");
    }
    else
    {
        System_printf("Error: unknown mode of operation!!!!!!!!!! \r\n");
    }

    /* System init */
    gIsI2cInitReq = TRUE;
    retVal       = BspUtils_appDefaultSerialInit(gIsI2cInitReq);
    if (retVal != FVID2_SOK)
    {
        System_printf("Error: : System Init Failed!!!\r\n");
    }

    /* Set the pin Mux */
    Bsp_boardSetPinMux(BSP_DRV_ID_UART, devid, BSP_BOARD_MODE_DEFAULT);

    /* Set the board muxes */
    Bsp_boardSelectDevice(BSP_DRV_ID_UART, devid);
}

Ptr NULLIOM_Params = NULL;

void user_prcm_init(void)
{
    /* Do Nothing */
}

/**
 * \brief      Function to print an log to the console every one second(Approx)
 *
 * \param      None
 *
 * \return     None
 *
 */
static void UartApp_tskHeartBeat(void)
{
    static Uint32 counter = 0;

    while (counter < 0xFFFFFFFF)
    {
        Task_sleep(1000U);

        System_printf("\r\n\r\n!!! PSP HrtBt %d", counter);
        counter++;
    }
}
