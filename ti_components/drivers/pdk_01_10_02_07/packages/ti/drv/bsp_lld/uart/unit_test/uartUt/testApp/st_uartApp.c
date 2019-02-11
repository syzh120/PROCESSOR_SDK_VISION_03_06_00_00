/*
 *  Copyright (c) Texas Instruments Incorporated 2012
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
 */

/**
 *  \file st_uartApp.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Core.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <xdc/runtime/Error.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>

#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define ST_TSK_STACK_SIZE               (10u * 1024u)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void st_uartMainTsk(void);
static void st_uartEdmaInit(void);
static Int32 st_uartDefaultInit(UInt32 isI2cInitReq);
static Int32 st_uartDefaultDeInit(UInt32 isI2cDeInitReq);

extern Int32 st_uartParser(void);
extern EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gStUartMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gStUartMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8 gStUartMainTskStack[ST_TSK_STACK_SIZE];

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle gEdmaHandle;

/**
 *  \brief I2C Device Init Params used for storing init Params handle,
 *  Semaphore handle, etc.
 */
static I2c_DevInitParams gI2cDevInitParams[BSP_DEVICE_I2C_INST_ID_MAX];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  main
 *  Application main function.
 */
Int32 main(void)
{
    Task_Params tskPrms;
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    Task_Params_init(&tskPrms);
    tskPrms.stack     = gStUartMainTskStack;
    tskPrms.stackSize = ST_TSK_STACK_SIZE;
    Task_create((Task_FuncPtr) st_uartMainTsk, &tskPrms, NULL);

    BIOS_start();

    return (0);
}

/**
 *  st_uartMainTsk
 *  Application test task.
 */
static void st_uartMainTsk(void)
{
    Int32       retVal;

    /* System init */
    retVal = st_uartDefaultInit(TRUE);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System Init Failed!!!\n");
        return;
    }

    /* Invoke UART test parser */
    st_uartParser();

    /* System de-init */
    retVal = st_uartDefaultDeInit(TRUE);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System De-Init Failed!!!\n");
        return;
    }

    GT_0trace(BspAppTrace, GT_INFO, "Test Application Complete!!\n");

    return;
}

/**
 *  st_uartEdmaInit
 *  Function to initialize the edma driver and get the handle to the
 *  edma driver
 */
static void st_uartEdmaInit(void)
{
    EDMA3_DRV_Result edmaResult = 0;
    UInt32 coreId;

    gEdmaHandle = edma3init(0, &edmaResult);

    coreId = Core_getId();
    GT_1trace(BspAppTrace, GT_INFO, " Core Id = %d\n", coreId);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        GT_0trace(BspAppTrace, GT_ERR, " EDMA driver initialization FAIL\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO, " EDMA driver initialization PASS\n");
    }

    return;
}

/**
 *  st_uartDefaultInit
 *  \brief Application utils function to call all the default init functions.
 */
static Int32 st_uartDefaultInit(UInt32 isI2cInitReq)
{
    Int32                   retVal = BSP_SOK;
    UInt32                  instCnt;
    Bsp_CommonInitParams    commonInitPrms;
    Bsp_BoardInitParams     boardInitPrms;
    Bsp_PlatformInitParams  platInitPrms;
    Bsp_DeviceInitParams    deviceInitPrms;
    lld_hsi2c_initParam_t   i2cInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
    const Bsp_BoardI2cData *i2cData;
    Bsp_BoardI2cInstData   *i2cInstData;
    Error_Block eb;

    Error_init(&eb);

    /* initialise the edma library and get the EDMA handle */
    st_uartEdmaInit();

    Uart_init();

    BspCommonInitParams_init(&commonInitPrms);
    retVal += Bsp_commonInit(&commonInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common Init failed!!\n");
    }

    BspBoardInitParams_init(&boardInitPrms);
    /* Override board detection if I2C is disabled */
    if (((Bool) TRUE) != ((Bool) isI2cInitReq))
    {
        boardInitPrms.boardId      = BSP_BOARD_UNKNOWN;
        boardInitPrms.baseBoardRev = BSP_BOARD_REV_UNKNOWN;
        boardInitPrms.dcBoardRev   = BSP_BOARD_REV_UNKNOWN;
    }
    retVal += Bsp_boardInit(&boardInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Board Init failed!!\n");
    }

    BspPlatformInitParams_init(&platInitPrms);
    retVal += Bsp_platformInit(&platInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Platform Init failed!!\n");
    }

    retVal += Fvid2_init(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 Init failed!!\n");
    }

    /* Override I2C init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));
        GT_assert(BspAppTrace, (NULL != i2cData->instData));

        for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
        {
            i2cInstData = &i2cData->instData[instCnt];
            GT_assert(BspAppTrace,
                      (i2cInstData->instId < BSP_DEVICE_I2C_INST_ID_MAX));
            i2cInitParams[instCnt].opMode       = HSI2C_OPMODE_INTERRUPT;
            i2cInitParams[instCnt].isMasterMode = TRUE;
            i2cInitParams[instCnt].is10BitAddr  = FALSE;
            i2cInitParams[instCnt].i2cBusFreq   =
                (lld_i2c_busspeed) i2cInstData->busClkKHz;
            i2cInitParams[instCnt].i2cIntNum      = i2cInstData->intNum;
            i2cInitParams[instCnt].i2cOwnAddr     = 0xCC;
            gI2cDevInitParams[instCnt].initParams = &i2cInitParams[instCnt];
            gI2cDevInitParams[instCnt].hsi2c_sem  =
                BspOsal_semCreate((Int32) 1, (Bool) TRUE);
            gI2cDevInitParams[instCnt].instId = i2cInstData->instId;
        }

        if (i2cData->numInst > 0)
        {
            retVal = I2c_GlobalInit(i2cData->numInst, &gI2cDevInitParams[0U]);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Error: I2C Init failed!!\n");
            }
        }

        BspDeviceInitParams_init(&deviceInitPrms);
        deviceInitPrms.isI2cProbingReq = FALSE;
        retVal += Bsp_deviceInit(&deviceInitPrms);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device Init failed!!\n");
        }
    }

    retVal += BspUtils_memInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App MEM Utils Init failed!!\n");
    }

    retVal += BspUtils_prfInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App PRF Utils Init failed!!\n");
    }

    retVal += BspUtils_appInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils Init failed!!\n");
    }

    /* Print BSP version string and platform info*/
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Build time            : [%s %s]\r\n", __TIME__, __DATE__);
    GT_1trace(BspAppTrace, GT_INFO,
              " BSP Version           : [%s]\r\n", Bsp_getVersionString());
    Bsp_platformPrintInfo();
    Bsp_boardPrintInfo();
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return (retVal);
}

/**
 *  st_uartDefaultDeInit
 *  \brief Application utils function to call all the default de-init
 *  functions.
 */
static Int32 st_uartDefaultDeInit(UInt32 isI2cDeInitReq)
{
    Int32  retVal = BSP_SOK;
    const Bsp_BoardI2cData *i2cData;
    UInt32 instCnt;

    retVal += BspUtils_appDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils De-Init failed!!\n");
    }

    retVal += BspUtils_prfDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App PRF Utils De-Init failed!!\n");
    }

    retVal += BspUtils_memDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App MEM Utils De-Init failed!!\n");
    }

    /* Override I2C de-init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cDeInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cDeInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));

        retVal += Bsp_deviceDeInit(NULL);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device De-Init failed!!\n");
        }
        if (i2cData->numInst > 0)
        {
            for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
            {
                BspOsal_semDelete(&(gI2cDevInitParams[instCnt].hsi2c_sem));
            }
            retVal += I2c_GlobalDeInit(NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Error: I2C De-Init failed!!\n");
            }
        }
    }

    retVal += Fvid2_deInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 De-Init failed!!\n");
    }

    retVal += Bsp_platformDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: BSP Platform De-Init failed!!\n");
    }

    retVal += Bsp_boardDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Board De-Init failed!!\n");
    }

    retVal += Bsp_commonDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common De-Init failed!!\n");
    }

    return (retVal);
}
