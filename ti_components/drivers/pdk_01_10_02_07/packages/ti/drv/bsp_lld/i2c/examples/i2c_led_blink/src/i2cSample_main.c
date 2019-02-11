/*
 *  Copyright (C) 2010-2017 Texas Instruments Incorporated
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

/** \file   i2csample_main.c
 *
 *  \brief  This file contains the sample code to demonstrate the usage of the
 *          I2C driver implemented for SYS/BIOS. More Robust Example is
 *          CaptureVIP Video Example.
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>

/* ========================================================================== */
/*                            MACRO DEFINTIONS                                */
/* ========================================================================== */
#define I2C0_INT_NUM                    (41)
#define POLLED_MODE 1

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */

/*
 * I2C0 init params. To be filled in user_i2c_init function which
 * is called before driver creation
 * DevInitParams needs to be Global as this will be needed by Task CFG File
 *
 */

I2c_DevInitParams        devInitParams;
lld_hsi2c_initParam_t    gI2cInitParams;

/* ========================================================================== */
/*                           IMPORTED FUNCTION PROTOTYPES
 *                       */
/* ========================================================================== */
extern void start_i2c_sample(void);
extern BspOsal_SemHandle hsi2c_sem0;
void echo(void);

/* ========================================================================== */
/*                           LOCAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */

static void tskHeartBeat(void);

Int32 main(void)
{
    BIOS_start();

    return (0);
}

void echo(void)
{
    Bsp_PlatformInitParams platInitPrms;
    BspPlatformInitParams_init(&platInitPrms);
    Bsp_platformInit(&platInitPrms);

    System_printf("\r\nI2C Sample Application\r\n");

    /* Run I2C sample application */
    start_i2c_sample();

    /* Start the Heart Beat Print */
    tskHeartBeat();

    return;
}

/*
 * I2C0 init function called when creating the driver.
 */
void user_i2c_init(void)
{
    gI2cInitParams.i2cIntNum  = I2C0_INT_NUM;
    gI2cInitParams.i2cBusFreq = I2C_NORMAL;

    /* configure I2c mode */
    gI2cInitParams.opMode       = HSI2C_OPMODE_INTERRUPT;
    gI2cInitParams.i2cOwnAddr   = 0;
    gI2cInitParams.is10BitAddr  = 0;
    gI2cInitParams.isMasterMode = 1;
    devInitParams.initParams    = &gI2cInitParams;
    devInitParams.hsi2c_sem     = hsi2c_sem0;

    if (HSI2C_OPMODE_POLLED == gI2cInitParams.opMode)
    {
        System_printf("I2c is configured in polled mode \r\n");
    }
    else if (HSI2C_OPMODE_INTERRUPT == gI2cInitParams.opMode)
    {
        System_printf("I2c is configured in interrupt mode \r\n");
    }
    else
    {
        System_printf("Error: unknown mode of operation!!!!!!!!!!\r\n");
    }
}

Ptr NULLIOM_Params = NULL;

static void tskHeartBeat(void)
{
    static UInt32 counter = 0;

    while (counter < 0xFFFFFFFF)
    {
        Task_sleep(1000U);    /* Add large delay */
        System_printf("\r\n\r\n!!! JGS HrtBt %d", counter);

        counter++;
    }
}
