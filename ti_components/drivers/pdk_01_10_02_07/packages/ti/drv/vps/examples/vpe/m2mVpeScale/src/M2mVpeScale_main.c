/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file M2mVpeScale_main.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <M2mVpeScale_utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define APP_TSK_STACK_SIZE              (10U * 1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void App_mainTestTask(void);
extern Task_Handle App_m2mVpeCreateTsk(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(AppMainTskStack, 32)
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
#endif
/* Test application stack. */
static UInt8     AppMainTskStack[APP_TSK_STACK_SIZE];

/* Test complete semaphore used to sync between test task and main task. */
Semaphore_Handle AppTestCompleteSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define PDK_RAW_BOOT
static Board_STATUS M2mVpeApp_boardInit(void)
{
    Board_STATUS ret;
    Board_initCfg boardCfg;

#ifdef PDK_RAW_BOOT
    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_MODULE_CLOCK;
#endif

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

    M2mVpeApp_boardInit();

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
    tskPrms.stack     = AppMainTskStack;
    tskPrms.stackSize = APP_TSK_STACK_SIZE;
    Task_create((Task_FuncPtr) App_mainTestTask, &tskPrms, NULL);

    BIOS_start();

    return (0);
}

/**
 *  App_mainTestTask
 *  Application test task.
 */
static void App_mainTestTask(void)
{
    UInt32           scCnt;
    Int32            userInput = 0;
    Int32            retVal = FVID2_SOK;
    UInt32           isI2cInitReq, isI2cDeInitReq;
    Semaphore_Params semPrms;
    Task_Handle      m2mVpeTaskHandle;

    /* Create semaphore */
    Semaphore_Params_init(&semPrms);
    AppTestCompleteSem = Semaphore_create(0, &semPrms, NULL);
    if (NULL == AppTestCompleteSem)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* System init */
        isI2cInitReq = isI2cDeInitReq = TRUE;
        retVal       = BspUtils_appDefaultInit(isI2cInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System Init Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
        BspUtils_tilerInit();
        BspUtils_tilerDebugLogEnable(FALSE);
#endif

        for (scCnt = 0U; scCnt < VPS_M2M_SCALER_ID_MAX; scCnt++)
        {
            BspUtils_appSetVpeLazyLoad(VPS_M2M_INST_VPE1, scCnt, TRUE);
        }

        while (1U)
        {
            /* Create test task */
            m2mVpeTaskHandle = App_m2mVpeCreateTsk();
            if (NULL == m2mVpeTaskHandle)
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
                retVal = BSP_EFAIL;
            }
            if (FVID2_SOK == retVal)
            {
                /* Register the task to the load module for calculating the load
                **/
                BspUtils_prfLoadRegister(m2mVpeTaskHandle, APP_NAME ":");

                /* Wait for test to complete */
                Semaphore_pend(AppTestCompleteSem, BIOS_WAIT_FOREVER);

                /* UnRegister the task from the load module */
                BspUtils_prfLoadUnRegister(m2mVpeTaskHandle);

                /* Delete the task */
                Task_delete(&m2mVpeTaskHandle);

                GT_0trace(
                    BspAppTrace, GT_INFO,
                    "Enter 0 to exit or any other key (in UART console) to continue testing...\r\n");
                if (BspUtils_uartGetNum(&userInput,
                        BSP_UTILS_UART_RX_DEFAULT_TIMEOUT) != BSP_SOK)
                {
                    /* Exit the app */
                    userInput = -1;
                }
            }
            if ((0 == userInput) || (retVal != FVID2_SOK))
            {
                break;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        for (scCnt = 0U; scCnt < VPS_M2M_SCALER_ID_MAX; scCnt++)
        {
            BspUtils_appSetVpeLazyLoad(VPS_M2M_INST_VPE1, scCnt, FALSE);
        }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
        BspUtils_tilerDeInit();
#endif

        /* System de-init */
        retVal = BspUtils_appDefaultDeInit(isI2cDeInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System De-Init Failed!!!\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        Semaphore_delete(&AppTestCompleteSem);
        GT_1trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": Max stack used for main task (init sequence): %d bytes\r\n",
            BspOsal_getTaskStackUsage(NULL));
        GT_1trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Max system stack used (ISR): %d bytes\r\n",
                  BspOsal_getSystemStackUsage());
        BspUtils_appPrintMemStatus();

        GT_0trace(BspAppTrace, GT_INFO, APP_NAME "Test Successfull!!\r\n");
    }
    return;
}

