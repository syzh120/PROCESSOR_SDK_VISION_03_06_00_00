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
 *  \file   mcspiSample_io.c
 *
 *  \brief  McSPI communication between the McSPI1 and McSPI2
 *
 *          This file demonstrates the use of McSPI communication between
 *          McSPI1 instance and McSPI2 instance.
 *          McSPI1 is master and McSPI2 is slave.
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <xdc/std.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/IHeap.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <xdc/runtime/Memory.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/csl/soc.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPES                         */
/* ========================================================================== */
EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);
static void createStream(UInt32 InstNum);
static void initialize_mcspi1_buf(void);
static void initialize_mcspi2_buf(void);
static void mcspi1task(void);
static void mcspi2task(void);
static UInt32 verify_data(void);

/* ========================================================================== */
/*                            MACRO DEFINITONS                                */
/* ========================================================================== */
#define BUFLEN              1024 /* Buffer size                               */
#define BUFALIGN            128  /* Alignment of buffer for use of L2 cache   */
#define ITERATION_CNT       100  /* Number of Iterations                      */
#define NUM_BUFS            3    /* Num Bufs to be issued and reclaimed       */
#define IOBUFLEN            32U
#define NUMIOREQ            ((BUFLEN / 4) + 1U)
/* ========================================================================== */
/*                              GLOBAL VARIABLES                              */
/* ========================================================================== */
extern HeapMem_Handle myHeap;
extern Int32          gMcspiOpMode;

EDMA3_DRV_Handle      gEdmaHandle;
Task_Params           spi2task_params;

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gSpi2TskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gSpi2TskStack, ".bss")
/* stack for McSPI2 task */
static UInt8          gSpi2TskStack[0x8000];

/* handle to the input and output streams   */
GIO_Handle mcspiHandle_mcspi1 = NULL;
GIO_Handle mcspiHandle_mcspi2 = NULL;

/* Semaphores used for syncronization */
Semaphore_Handle      mcspi1Sem, mcspi2Sem, mcspiSlvSem, mcspiSlavePrimeSem;

/* Global SPI init config data structure    */
Mcspi_Params          spiParams;

/*
 * Buffers placed in external memory are aligned on a 128 bytes boundary.
 * In addition, the buffer should be of a size multiple of 128 bytes for
 * the cache to work optimally.
 */
/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(rxbuf0, BUFALIGN);
Ptr rxbuf0[NUM_BUFS];

/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(txbuf0, BUFALIGN);
Ptr txbuf0[NUM_BUFS];

/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(rxbuf1, BUFALIGN);
Ptr rxbuf1[NUM_BUFS];

/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(txbuf1, BUFALIGN);
Ptr txbuf1[NUM_BUFS];

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */
static void createStream(UInt32 InstNum)
{
    GIO_Params       ioParams;
    Mcspi_ChanParams chanParams;
    Error_Block      eb;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    /* initialze chanParams */
    Mcspi_ChanParams_init(&chanParams);

    /* update the edma Handle                                                 */
    chanParams.hEdma = gEdmaHandle;
    chanParams.chipSelTimeControl = MCSPI_CLK_CYCLE0;
    chanParams.fifoEnable         = (UInt32) TRUE;
    chanParams.spiChipSelectHold  = (UInt32) TRUE;
    chanParams.chanNum = 0;

    /* If cross bar events are being used then make isCrossBarIntEn = TRUE and
     * choose appropriate interrupt number to be mapped (assign it to
     * intNumToBeMapped)
     */
    /* Cross bar evt disabled */
    chanParams.crossBarEvtParam.isCrossBarIntEn  = (UInt32) FALSE;
    chanParams.crossBarEvtParam.intNumToBeMapped = 0xFF;  /* Invalid number */

    ioParams.chanParams = (Ptr) & chanParams;
    ioParams.model      = GIO_Model_ISSUERECLAIM;
    ioParams.numPackets = NUM_BUFS + 1;

    if (InstNum == 0U)
    {
        /* Pass the DMA channels to be used for SPI DMA mode. */
        chanParams.useAppSpecifiedDmaEvtNumbers = TRUE;
        chanParams.rxDmaEventNumber = (UInt32) CSL_EDMA3_CHA0_MCSPI0_RX;
        chanParams.txDmaEventNumber = (UInt32) CSL_EDMA3_CHA0_MCSPI0_TX;
        mcspiHandle_mcspi1 = GIO_create("/mcspi0", GIO_INOUT, &ioParams, &eb);
        if (mcspiHandle_mcspi1 == NULL)
        {
            System_printf("\r\nCreate input stream FAILED.\r\n");
            BIOS_exit(0);
        }
    }
    else
    {
        mcspiHandle_mcspi2 = GIO_create("/mcspi1", GIO_INOUT, &ioParams, &eb);
        if (mcspiHandle_mcspi2 == NULL)
        {
            System_printf("\r\nCreate input stream FAILED.\r\n");
            BIOS_exit(0);
        }
    }
}

static void initialize_mcspi1_buf(void)
{
    Error_Block  eb;
    Int32        count = 0;
    IHeap_Handle iheap;
    UInt32       tempCount = 0;

    iheap = HeapMem_Handle_to_xdc_runtime_IHeap(myHeap);
    Error_init(&eb);

    /* Allocate buffers for the GIO buffer exchanges for McSPI1               */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        rxbuf0[count] = (Ptr) Memory_calloc(iheap, BUFLEN, BUFALIGN, &eb);
        if (NULL == rxbuf0[count])
        {
            System_printf("\r\nMEM_calloc failed.\r\n");
        }

        txbuf0[count] = (Ptr) Memory_calloc(iheap, BUFLEN, BUFALIGN, &eb);
        if (NULL == txbuf0[count])
        {
            System_printf("\r\nMEM_calloc failed.\r\n");
        }
    }

    /* Fill the buffers with known data and transmit the same and check if the*
     * same pattern is received at McSPI2 Buffers                             */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        for (tempCount = 0; tempCount < BUFLEN; tempCount++)
        {
            ((Uint8 *) txbuf0[count])[tempCount] = (tempCount % 0x100);
        }
    }

    /* Cache writeback after buffer initialization with CPU access */
    BspOsal_cacheWbInvAll();
}

static void initialize_mcspi2_buf(void)
{
    Error_Block  eb;
    Int32        count = 0;
    IHeap_Handle iheap;
    UInt32       tempCount = 0;

    iheap = HeapMem_Handle_to_xdc_runtime_IHeap(myHeap);
    Error_init(&eb);

    /* Allocate buffers for the GIO buffer exchanges for McSPI2               */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        rxbuf1[count] = (Ptr) Memory_calloc(iheap, BUFLEN, BUFALIGN, &eb);
        if (NULL == rxbuf1[count])
        {
            System_printf("\r\nMEM_calloc failed.\r\n");
        }

        txbuf1[count] = (Ptr) Memory_calloc(iheap, BUFLEN, BUFALIGN, &eb);
        if (NULL == txbuf1[count])
        {
            System_printf("\r\nMEM_calloc failed.\r\n");
        }
    }

    /* Fill the buffers with known data and transmit the same and check if the*
     * same pattern is received at McSPI1 Buffers */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        for (tempCount = 0; tempCount < BUFLEN; tempCount++)
        {
            ((Uint8 *) txbuf1[count])[tempCount] = (tempCount % 0x100);
        }
    }

    /* Cache writeback after buffer initialization with CPU access */
    BspOsal_cacheWbInvAll();
}

static void mcspi1task(void)
{
    UInt32          size  = 0;
    UInt32          count = 0;
    UInt32          i, iterations = 0;
    Int             status = IOM_COMPLETED;
    UInt32          tempBuffAddr;
    Mcspi_DataParam issueDataparam[NUM_BUFS][NUMIOREQ];
    Mcspi_DataParam reclaimDataparam[NUM_BUFS];

    /* Call createStream function to create I/O streams                       */
    createStream(0U);

    initialize_mcspi1_buf();

    for (count = 0; count < NUM_BUFS; count++)
    {
        /* In case of multiple bufs make sure that previous reclaim happened at
         * McSPI2 */
        Semaphore_pend(mcspi2Sem, BIOS_WAIT_FOREVER);
        /* For Polled Mode transfer driver cannot synchronize between transfers
         * on McSPI1 and McSPI2. McSPI2 (Slave) Tx should be having valid data
         * before writing to McSPI1 (Master) Tx to ensure data integrity. In
         * case of Interrupt and DMA mode driver task need not do the
         * synchronization, hence single issue is done for whole buffer */
        if (gMcspiOpMode == MCSPI_OPMODE_POLLED)
        {
            size       = 4;
            iterations = BUFLEN / 4U;
        }
        else
        {
            size       = IOBUFLEN;
            iterations = BUFLEN / IOBUFLEN;
        }
        if (gMcspiOpMode == MCSPI_OPMODE_INTERRUPT)
        {
            /* Wait for the slave iop priming */
            Semaphore_pend(mcspiSlavePrimeSem, BIOS_WAIT_FOREVER);
        }
        for (i = 0; i < iterations; i++)
        {
            if (gMcspiOpMode != MCSPI_OPMODE_INTERRUPT)
            {
                /* pend of Sem to make sure slave Tx is written before Master */
                Semaphore_pend(mcspiSlvSem, BIOS_WAIT_FOREVER);
            }
            issueDataparam[count][i].bufLen = size;

            tempBuffAddr  = (UInt32) rxbuf0[count];
            tempBuffAddr += (i * issueDataparam[count][i].bufLen);
            issueDataparam[count][i].inBuffer = (UInt8 *) (tempBuffAddr);
            tempBuffAddr  = (UInt32) txbuf0[count];
            tempBuffAddr += (i * issueDataparam[count][i].bufLen);
            issueDataparam[count][i].outBuffer = (UInt8 *) (tempBuffAddr);

            /* Issue the first & second empty buffers to the input stream */
            status =
                GIO_issue(mcspiHandle_mcspi1, &issueDataparam[count][i], size,
                          NULL);

            if (status != IOM_PENDING && status != IOM_COMPLETED)
            {
                System_printf("\r\nFailed to issue empty buffer to stream\r\n");
            }
            /* Reclaim is done after every issue and buffers are not primed. If
             * the buffers are primed next transfer is initialized as soon as
             * the first one is completed. We wont be able to ensure transfer
             * initializaton on Slave before master for second buffer */
            status =
                GIO_reclaim(mcspiHandle_mcspi1, (Ptr *) &reclaimDataparam, NULL,
                            NULL);
            if (IOM_COMPLETED != status)
            {
                System_printf("Iteration %d\r\n", count);

                System_printf(
                    "Error reclaiming empty buffer from the streams %x"
                    " error = 0x%d\r\n",
                    ((Uint8) (reclaimDataparam->outBuffer[count])),
                    status);
                break;
            }
            if (gMcspiOpMode == MCSPI_OPMODE_INTERRUPT)
            {
                Task_yield();
            }
        }
        if (gMcspiOpMode == MCSPI_OPMODE_INTERRUPT)
        {
            Task_yield();
        }
        /* Post Sem for telling reclaim done on McSPI1 */
        Semaphore_post(mcspi1Sem);
    }
}

static void mcspi2task(void)
{
    UInt32          size  = 0;
    UInt32          count = 0;
    UInt32          i, iterations = 0;
    Int             status = IOM_COMPLETED;
    UInt32          tempBuffAddr;
    Mcspi_DataParam issueDataparam[NUM_BUFS][NUMIOREQ];
    Mcspi_DataParam reclaimDataparam[NUM_BUFS];

    /* Call createStream function to create I/O streams                       */
    createStream(1U);

    initialize_mcspi2_buf();

    for (count = 0; count < NUM_BUFS; count++)
    {
        /* In case of multiple bufs make sure that previous reclaim happened at
         * McSPI1 */
        Semaphore_pend(mcspi1Sem, BIOS_WAIT_FOREVER);
        if (gMcspiOpMode == MCSPI_OPMODE_POLLED)
        {
            size       = 4;
            iterations = BUFLEN / 4U;
        }
        else
        {
            size       = IOBUFLEN;
            iterations = BUFLEN / IOBUFLEN;
        }

        if (gMcspiOpMode == MCSPI_OPMODE_INTERRUPT)
        {
            /* In case of Interrupt mode prime one iop */
            tempBuffAddr = (UInt32) rxbuf1[count];
            issueDataparam[count][0].inBuffer = (UInt8 *) (tempBuffAddr);
            tempBuffAddr = (UInt32) txbuf1[count];
            issueDataparam[count][0].outBuffer = (UInt8 *) (tempBuffAddr);
            issueDataparam[count][0].bufLen    = size;

            status =
                GIO_issue(mcspiHandle_mcspi2, &issueDataparam[count][0], size,
                          NULL);
            if (status != IOM_PENDING && status != IOM_COMPLETED)
            {
                System_printf("\r\nFailed to issue empty buffer to stream\r\n");
            }
            /* Initialize loopcount to 1 as one issue is already done. */
            i = 1;
            /* Post sem to indicate that priming in slave is done */
            Semaphore_post(mcspiSlavePrimeSem);
        }
        else
        {
            i = 0;
        }

        for (; i < iterations; i++)
        {
            issueDataparam[count][i].bufLen = size;
            tempBuffAddr  = (UInt32) rxbuf1[count];
            tempBuffAddr += (i * issueDataparam[count][i].bufLen);
            issueDataparam[count][i].inBuffer = (UInt8 *) (tempBuffAddr);
            tempBuffAddr  = (UInt32) txbuf1[count];
            tempBuffAddr += (i * issueDataparam[count][i].bufLen);
            issueDataparam[count][i].outBuffer = (UInt8 *) (tempBuffAddr);

            /* Post Sem for Issue of Slave transfer. Post is done before
             * GIO_issue as in case of polled mode GIO_issue is blocking and
             * needs McSPI1 task to run, to go for completion but task switch
             * wont happen till First Tx is written to slave */
            if (gMcspiOpMode != MCSPI_OPMODE_INTERRUPT)
            {
                Semaphore_post(mcspiSlvSem);
            }
            /* Issue the first & second empty buffers to the input stream */
            status =
                GIO_issue(mcspiHandle_mcspi2, &issueDataparam[count][i], size,
                          NULL);

            if (status != IOM_PENDING && status != IOM_COMPLETED)
            {
                System_printf("\r\nFailed to issue empty buffer to stream\r\n");
            }

            /* Reclaim is done after every issue and buffers are not primed. If
             * *the buffers are primed next transfer is initialized as soon as
             * the first one is completed. We wont be able to ensure transfer
             *initializaton on Slave before master for second buffer */
            status =
                GIO_reclaim(mcspiHandle_mcspi2, (Ptr *) &reclaimDataparam, NULL,
                            NULL);
            if (IOM_COMPLETED != status)
            {
                System_printf("Iteration %d\r\n", count);

                System_printf(
                    "Error reclaiming empty buffer from the streams %x"
                    " error = 0x%d\r\n",
                    ((Uint8) (reclaimDataparam->outBuffer[count])),
                    status);
                break;
            }
        }
        if (gMcspiOpMode == MCSPI_OPMODE_INTERRUPT)
        {
            /* Reclaim the last buffer in case of interrupt mode */
            status =
                GIO_reclaim(mcspiHandle_mcspi2, (Ptr *) &reclaimDataparam, NULL,
                            NULL);
        }
        /* Post Sem for telling reclaim done on McSPI2 */
        Semaphore_post(mcspi2Sem);
    }
}

static UInt32 verify_data(void)
{
    volatile Int32 count, tempCount;
    UInt8         *srcBuff0, *dstBuff0;
    UInt8         *srcBuff1, *dstBuff1;
    UInt32         retVal = 0U;
    for (count = 0U; count < NUM_BUFS; count++)
    {
        srcBuff0 = rxbuf0[count];
        dstBuff0 = txbuf0[count];
        srcBuff1 = rxbuf1[count];
        dstBuff1 = txbuf1[count];
        for (tempCount = 0; tempCount < BUFLEN; tempCount++)
        {
            if (srcBuff0[tempCount] != dstBuff1[tempCount])
            {
                System_printf(
                    "Error matching master receive data at location %d\r\n",
                    tempCount);
                retVal = 1U;
                break;
            }
        }
        for (tempCount = 0; tempCount < BUFLEN; tempCount++)
        {
            if (srcBuff1[tempCount] != dstBuff0[tempCount])
            {
                System_printf(
                    "Error matching slave receive data at location %d\r\n",
                    tempCount);
                retVal = 1U;
                break;
            }
        }
    }
    return retVal;
}

void start_spi_sample(void)
{
    Semaphore_Params semParams;
    EDMA3_DRV_Result edmaResult = 0;
    UInt32           initVal    = 1U;

    gEdmaHandle = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("\r\nEDMA driver initialization FAIL\r\n");
    }
    else
    {
        System_printf("\r\nEDMA driver initialization PASS.\r\n");
    }

    /* Initialize Semaphores used for Synchronization */
    Semaphore_Params_init(&semParams);
    mcspi1Sem          = Semaphore_create(initVal, &semParams, NULL);
    mcspi2Sem          = Semaphore_create(initVal, &semParams, NULL);
    mcspiSlvSem        = Semaphore_create(0U, &semParams, NULL);
    mcspiSlavePrimeSem = Semaphore_create(0U, &semParams, NULL);

    assert(mcspi1Sem != NULL);
    assert(mcspi2Sem != NULL);
    assert(mcspiSlvSem != NULL);
    assert(mcspiSlavePrimeSem != NULL);

    Task_Params_init(&spi2task_params);

    spi2task_params.stack     = gSpi2TskStack;
    spi2task_params.stackSize = sizeof (gSpi2TskStack);
    /* Create aniother task for McSPI2 transfer */
    Task_create((Task_FuncPtr) mcspi2task, &spi2task_params, NULL);

    /* Continue McSPI1 transfer in current task */
    mcspi1task();

    /* McSPI1 reclaim is completed, Wait till Buffer reclaim is completed on
     * McSPI2 */
    Semaphore_pend(mcspi2Sem, BIOS_WAIT_FOREVER);

    /* Cache writeback before buffer verification. */
    BspOsal_cacheWbInvAll();

    if (verify_data() == 0)
    {
        System_printf("Data varification passed \r\n");
        System_printf("McSPI Master Slave application Passed\r\n");
    }
    else
    {
        System_printf("McSPI Master Slave application Failed\r\n");
    }
}
