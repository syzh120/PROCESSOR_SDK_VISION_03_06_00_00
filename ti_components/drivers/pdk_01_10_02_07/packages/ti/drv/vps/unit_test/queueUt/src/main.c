/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file main.c
 *
 *  \brief Queue Unit Test
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_utilsQue.h>
#include <ti/drv/vps/include/common/bsp_config.h>


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void QueueTest_createTsk(void);
static void QueueTest_tskMain(UArg arg0, UArg arg1);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gQueueTestTskStackMain, 32)
#pragma DATA_SECTION(gQueueTestTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8             gQueueTestTskStackMain[1024];
/* Test application queue */
static UInt32            myQueue[4] = {0};
static Task_Handle       gTskHandle;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    QueueTest_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void QueueTest_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = 10;
    tskPrms.stack         = gQueueTestTskStackMain;
    tskPrms.stackSize     = sizeof (gQueueTestTskStackMain);
    tskPrms.arg0          = NULL;
    gTskHandle = Task_create(QueueTest_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gTskHandle != NULL));

    return;
}

/*
 * Test task main
 */
static void QueueTest_tskMain(UArg arg0, UArg arg1)
{
    Int32 retVal = BSP_SOK;
    BspUtils_QueHandle queHandle;
    UInt32 i = 0U, element;
    UInt32 *readElem;
    UInt32 iterCnt = 100000U;
    Semaphore_Object* semWr;
    Semaphore_Object* semRd;
    UInt32 maxElements = 4U;
    retVal = BspUtils_queCreate(&queHandle,
                                maxElements,
                                &myQueue,
                                BSPUTILS_QUE_FLAG_BLOCK_QUE
                                );
    if (retVal == BSP_SOK)
    {
        for (i = 0U; i < iterCnt; i++)
        {
            element = i;
            retVal = BspUtils_quePut(&queHandle,
                             &element,
                             BSP_OSAL_WAIT_FOREVER);
            if (retVal == BSP_SOK)
            {
                retVal = BspUtils_queGet(&queHandle,
                                 (Ptr*)&readElem, 1U, BSP_OSAL_WAIT_FOREVER);
            }
            if ((retVal != BSP_SOK) || (*readElem != i))
            {
                break;
            }
            else
            {
                if (i%5000 == 0)
                {
                    GT_1trace(BspAppTrace, GT_INFO, " QUEUE TEST: Iteration %d\r\n",
                        i);
                }
            }
        }
    }
    semWr = (Semaphore_Object*)(queHandle.semWr);
    semRd = (Semaphore_Object*)(queHandle.semRd);
    if ((i == iterCnt) &&
        (Semaphore_getCount(semWr) == maxElements) &&
        (Semaphore_getCount(semRd) == 0U))
    {
        GT_0trace(BspAppTrace, GT_INFO,
        " QUEUE TEST: Passed ...\n\r");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
        " QUEUE TEST: Failed ...\n\r");
    }
    BspOsal_sleep(500);

    return;
}
