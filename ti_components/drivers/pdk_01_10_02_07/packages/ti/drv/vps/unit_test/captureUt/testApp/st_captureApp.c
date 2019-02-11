/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file st_captureApp.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/utils/Load.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_lvds.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_wd_timer.h>

#include <testLib/st_capture.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define ST_TSK_STACK_SIZE              (10u * 1024u)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void st_captMainTsk(void);
extern Int32 st_captParser(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gStCaptureMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gStCaptureMainTskStack, ".bss:taskStackSection")
#endif
/* Test application stack. */
static UInt8 gStCaptureMainTskStack[ST_TSK_STACK_SIZE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
static Board_STATUS CaptureApp_boardInit(void)
{
    Board_STATUS ret;
    Board_initCfg boardCfg;

    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_MODULE_CLOCK;

    boardCfg |= BOARD_INIT_UART_STDIO;
    ret = Board_init(boardCfg);
    return (ret);
}
#endif

/**
 *  main
 *  Application main function.
 */
int main(void)
{
    Task_Params tskPrms;
    static Char stdin_buf[BUFSIZ];

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    UInt32                  tempFuncPtr;
    BspOsal_InitParams_t    bspOsalInitPrms = {0};
    CaptureApp_boardInit();
    /* Initialize the UART prints */
    BspUtils_uartInit();
    tempFuncPtr = (UInt32) & BspUtils_uartPrint;
    bspOsalInitPrms.printFxn = (BspOsal_PrintFxn) (tempFuncPtr);
    BspOsal_Init(&bspOsalInitPrms);
#endif

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    Task_Params_init(&tskPrms);
    tskPrms.stack     = gStCaptureMainTskStack;
    tskPrms.stackSize = ST_TSK_STACK_SIZE;
    Task_create((Task_FuncPtr) st_captMainTsk, &tskPrms, NULL);

    BIOS_start();

    return (0);
}

/**
 *  st_captMainTsk
 *  Application test task.
 */
static void st_captMainTsk(void)
{
    Int32 retVal;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
    /* stop the wdtimer */
    WDTIMERDisable(SOC_WD_TIMER2_BASE);
#endif

    /* System init */
    retVal       = BspUtils_appDefaultInit(TRUE);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System Init Failed!!!\r\n");
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_FAIL);
        return;
    }

    /* Invoke CAPTURE test parser */
    st_captParser();

    /* System de-init */
    retVal = BspUtils_appDefaultDeInit(TRUE);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System De-Init Failed!!!\r\n");
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_FAIL);
        return;
    }

    GT_0trace(BspAppTrace, GT_INFO, "Test Application Complete!!\r\n");

    return;
}
