/*
 *  Copyright (C) 2014-2017 Texas Instruments Incorporated
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
 *  \file   Bsp_i2cUtilityMain.c
 *
 *  \brief  This file contains the sample code to demonstrate the usage of the
 *          I2C driver implemented for SYS/BIOS.
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
#include <xdc/runtime/System.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define I2C_APP_TSK_STACK_MAIN          (10U * 1024U)
/* Test application task priority */
#define I2C_APP_TSK_PRI_MAIN            (10U)

#define APP_NAME                        "I2C_UTILITY_APP"

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void I2cApp_createTsk(void);
static void I2cApp_tskMain(UArg arg0, UArg arg1);

extern void start_i2c_utility(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gI2cAppTskStackMain, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gI2cAppTskStackMain, ".bss:taskStackSection")
/* Test application stack */
static UInt8 gI2cAppTskStackMain[I2C_APP_TSK_STACK_MAIN];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
Int32 main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    I2cApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void I2cApp_createTsk(void)
{
    Task_Params tskPrms;
    Task_Handle tskHandle;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority  = I2C_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gI2cAppTskStackMain;
    tskPrms.stackSize = sizeof (gI2cAppTskStackMain);
    tskHandle         = Task_create(I2cApp_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (tskHandle != NULL));

    return;
}

/*
 * Test task main
 */
static void I2cApp_tskMain(UArg arg0, UArg arg1)
{
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": I2C Utility Application - STARTS !!!\r\n");

    BspUtils_appDefaultSerialInit(TRUE);

    /* Run I2C utility application */
    start_i2c_utility();

    BspUtils_appDefaultSerialDeInit(TRUE);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": I2C Utility Application - DONE !!!\r\n");
    return;
}

