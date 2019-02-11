/*
* dma_ping_pong_test.c
*
* EDMA3 ping-pong buffers based data copy test case, using a DMA and a link
* channel.
*
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
*
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

#include "sample.h"

/** Test Case Description **/
/**
* There are two big buffers of size (PING_PONG_NUM_COLUMNS * PING_PONG_NUM_ROWS).
* Both are present in DDR and are known as pingpongSrcBuf and pingpongDestBuf.
* There are two small buffers of size (PING_PONG_L1D_BUFFER_SIZE). They are known as
* ping buffer and pong buffer.
* The pingpongSrcBuf is divided into chunks, each having size of
* PING_PONG_L1D_BUFFER_SIZE. Data is being transferred from pingpongSrcBuf
* to either ping or pong buffers, using EDMA3. Logic behind using two ping pong
* buffers is that one can be processed by DSP while the other is used by EDMA3
* for data movement. So ping and pong are alternately used by EDMA3 and DSP.
* Also, to simulate the real world scenario, as a part of DSP processing,
* I am copying data from ping/pong buffers to pingpongDestBuf.
* In the end, I compare pingpongSrcBuf and pingpongDestBuf to check whether
* the algorithm has worked fine.
*/
/**
* Number of columns in the bigger source buffer.
*/
#define PING_PONG_NUM_COLUMNS           (72u)

/**
* Number of columns in the bigger source buffer.
*/
#define PING_PONG_NUM_ROWS                (48u)

/* ACNT is equal to number of columns. */
#define PING_PONG_ACNT                          PING_PONG_NUM_COLUMNS
/* BCNT is equal to number of rows which will be transferred in one shot. */
#define PING_PONG_BCNT                          (8u)
/* CCNT is equal to 1. */
#define PING_PONG_CCNT                          (1u)

/* Number of times DMA will be triggered. */
#define PING_PONG_NUM_TRIGGERS           (PING_PONG_NUM_ROWS/PING_PONG_BCNT)

/* Size of bigger buffers in DDR. */
#define PING_PONG_DDR_BUFFER_SIZE     (PING_PONG_NUM_COLUMNS*PING_PONG_NUM_ROWS)
/* Size of smaller buffers in IRAM. */
#define PING_PONG_L1D_BUFFER_SIZE     (PING_PONG_ACNT*PING_PONG_BCNT)


/* Ping pong source buffer */
#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/* Cache line aligned big source buffer. */
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_pingpongSrcBuf, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#pragma DATA_SECTION(_pingpongSrcBuf, ".my_sect_ddr");
signed char _pingpongSrcBuf[PING_PONG_DDR_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char __attribute__((section(".my_sect_ddr"))) _pingpongSrcBuf[PING_PONG_DDR_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char __attribute__((section(".my_sect_ddr"))) _pingpongSrcBuf[PING_PONG_DDR_BUFFER_SIZE];
#endif
#endif

/**
* Ping pong destination buffer.
* It will be used to copy data from L1D ping/pong buffers to check the
* validity.
*/
#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/* Cache line aligned big destination buffer. */
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_pingpongDestBuf, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#pragma DATA_SECTION(_pingpongDestBuf, ".my_sect_ddr");
signed char _pingpongDestBuf[PING_PONG_DDR_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char __attribute__((section(".my_sect_ddr"))) _pingpongDestBuf[PING_PONG_DDR_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char __attribute__((section(".my_sect_ddr"))) _pingpongDestBuf[PING_PONG_DDR_BUFFER_SIZE];
#endif
#endif


/* These destination buffers are in IRAM. */
#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/* Cache line aligned destination buffer 1 i.e. Ping buffer. */
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_dstL1DBuff1, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#ifdef __TMS470__
#pragma DATA_SECTION(_dstL1DBuff1, ".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstL1DBuff1, ".my_sect_iram");
#endif
signed char _dstL1DBuff1[PING_PONG_L1D_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
#ifdef __TMS470__
signed char __attribute__((section(".my_sect_ddr"))) _dstL1DBuff1[PING_PONG_L1D_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char __attribute__((section(".my_sect_iram"))) _dstL1DBuff1[PING_PONG_L1D_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#endif
#else
#ifdef __TMS470__
signed char __attribute__((section(".my_sect_ddr"))) _dstL1DBuff1[PING_PONG_L1D_BUFFER_SIZE];
#else
signed char __attribute__((section(".my_sect_iram"))) _dstL1DBuff1[PING_PONG_L1D_BUFFER_SIZE];
#endif
#endif
#endif

#ifndef GCC_BUILD
#ifdef EDMA3_ENABLE_DCACHE
/* Cache line aligned destination buffer 2 i.e. Pong buffer. */
/**
* The DATA_ALIGN pragma aligns the symbol to an alignment boundary. The
* alignment boundary is the maximum of the symbol’s default alignment value
* or the value of the constant in bytes. The constant must be a power of 2.
* The syntax of the pragma in C is:
* #pragma DATA_ALIGN (symbol, constant);
*/
#pragma DATA_ALIGN(_dstL1DBuff2, EDMA3_CACHE_LINE_SIZE_IN_BYTES);
#endif  /* #ifdef EDMA3_ENABLE_DCACHE */
#ifdef __TMS470__
#pragma DATA_SECTION(_dstL1DBuff2, ".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstL1DBuff2, ".my_sect_iram");
#endif
signed char _dstL1DBuff2[PING_PONG_L1D_BUFFER_SIZE];
#else
#ifdef EDMA3_ENABLE_DCACHE
signed char __attribute__((section(".my_sect_ddr"))) _dstL1DBuff2[PING_PONG_L1D_BUFFER_SIZE] __attribute__ ((aligned (EDMA3_CACHE_LINE_SIZE_IN_BYTES)));
#else
signed char __attribute__((section(".my_sect_ddr"))) _dstL1DBuff2[PING_PONG_L1D_BUFFER_SIZE];
#endif
#endif

/* Pointers for all those buffers */
signed char *pingpongSrcBuf;
signed char *pingpongDestBuf;
signed char *pingpongSrcBufCopy;
signed char *pingpongDestBufCopy;

signed char *dstL1DBuff1;
signed char *dstL1DBuff2;

extern void *AppSemHandle1;

/** Local MemCpy function */
extern void edma3MemCpy(void *dst, const void *src, uint32_t len);

EDMA3_DRV_Result process_ping_pong_buffer(unsigned short buff_id)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    /**
    * Copy the L1D ping-pong buffers from L1D to DDR using CPU.
    * This is kind of dummy processing routine.
    */
    if (buff_id == 1u)
    {
        /* Copy pong buffer */

        /* Invalidate first if cache is enabled, otherwise CPU will take from cache. */
        /**
        * Since the ping/pong buffers are in IRAM, there is no need of invalidating
        * them. If they are in DDR, invalidate them.
        */
#ifdef EDMA3_ENABLE_DCACHE

        if (result == EDMA3_DRV_SOK)
        {
            result = Edma3_CacheInvalidate((uint32_t)dstL1DBuff2,
                PING_PONG_L1D_BUFFER_SIZE);
        }

#endif  /* EDMA3_ENABLE_DCACHE */

        if (result == EDMA3_DRV_SOK)
        {
            edma3MemCpy((void *)(pingpongDestBufCopy),
                (const void *)(dstL1DBuff2),
                PING_PONG_L1D_BUFFER_SIZE);
        }
    }
    else
    {
        /* Copy ping buffer */

        /* Invalidate first if cache is enabled, otherwise CPU will take from cache. */
#ifdef EDMA3_ENABLE_DCACHE

        if (result == EDMA3_DRV_SOK)
        {
            result = Edma3_CacheInvalidate((uint32_t)dstL1DBuff1,
                PING_PONG_L1D_BUFFER_SIZE);
        }

#endif  /* EDMA3_ENABLE_DCACHE */

        if (result == EDMA3_DRV_SOK)
        {
            edma3MemCpy((void *)(pingpongDestBufCopy),
                (const void *)(dstL1DBuff1),
                PING_PONG_L1D_BUFFER_SIZE);
        }
    }

    /* Adjust the pointer. */
    pingpongDestBufCopy += PING_PONG_L1D_BUFFER_SIZE;

    return result;
}


/**
*  \brief   EDMA3 ping-pong based data copy test case, using a DMA and
*              a link channel.
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result edma3_test_ping_pong_mode(EDMA3_DRV_Handle hEdma)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    EDMA3_DRV_PaRAMRegs paramSet = {0,0,0,0,0,0,0,0,0,0,0,0};
    /* One master channel */
    uint32_t chId = 0;
    /* Two link channels */
    uint32_t lChId1 = 0;
    uint32_t lChId2 = 0;
    uint32_t tcc = 0;
    int i;
    uint32_t count;
    uint32_t Istestpassed = 0u;
    uint32_t BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;
    /* PaRAM Set handle */
    uint32_t phyaddress = 0;
    EDMA3_DRV_ParamentryRegs *param_handle = NULL;
    /* Number of triggers for EDMA3. */
    uint32_t numenabled = PING_PONG_NUM_TRIGGERS;

    pingpongSrcBuf = (signed char*)GLOBAL_ADDR(_pingpongSrcBuf);
    pingpongDestBuf = (signed char*)GLOBAL_ADDR(_pingpongDestBuf);
    pingpongSrcBufCopy = pingpongSrcBuf;
    pingpongDestBufCopy = pingpongDestBuf;
    dstL1DBuff1 = (signed char*)GLOBAL_ADDR(_dstL1DBuff1);
    dstL1DBuff2 = (signed char*)GLOBAL_ADDR(_dstL1DBuff2);


    /* Initalize source buffer for PING_PONG_DDR_BUFFER_SIZE bytes of data */
    for (count = 0u; count < PING_PONG_DDR_BUFFER_SIZE; count++)
    {
        pingpongSrcBuf[count] = (count % 0xFF);
    }


#ifdef EDMA3_ENABLE_DCACHE
    /*
    * Note: These functions are required if the buffer is in DDR.
    * For other cases, where buffer is NOT in DDR, user
    * may or may not require the below functions.
    */
    /* Flush the Source Buffer */
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheFlush((uint32_t)pingpongSrcBuf, PING_PONG_DDR_BUFFER_SIZE);
    }

    /* Invalidate the Destination Buffers */
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheInvalidate((uint32_t)pingpongDestBuf, PING_PONG_DDR_BUFFER_SIZE);
    }

    /**
    * Since the ping/pong buffers are in IRAM, there is no need of invalidating
    * them. If they are in DDR, invalidate them.
    */


    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheInvalidate((uint32_t)dstL1DBuff1, PING_PONG_L1D_BUFFER_SIZE);
    }
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheInvalidate((uint32_t)dstL1DBuff2, PING_PONG_L1D_BUFFER_SIZE);
    }

#endif  /* EDMA3_ENABLE_DCACHE */


    /* Set B count reload as B count. */
    BRCnt = PING_PONG_BCNT;

    /* Setting up the SRC/DES Index */
    srcbidx = (int)PING_PONG_ACNT;
    desbidx = (int)PING_PONG_ACNT;

    /* AB Sync Transfer Mode */
    srccidx = ((int)PING_PONG_ACNT * (int)PING_PONG_BCNT);
    descidx = ((int)PING_PONG_ACNT * (int)PING_PONG_BCNT);

    /* Setup for DMA Channel 1*/
    tcc = EDMA3_DRV_TCC_ANY;
    chId = EDMA3_DRV_DMA_CHANNEL_ANY;

    /* Request any DMA channel and any TCC */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_requestChannel (hEdma, &chId, &tcc,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL);
    }

    /* If successful, allocate the two link channels. */
    if (result == EDMA3_DRV_SOK)
    {
        lChId1 = EDMA3_DRV_LINK_CHANNEL;
        lChId2 = EDMA3_DRV_LINK_CHANNEL;

        result = (
            (EDMA3_DRV_requestChannel (hEdma, &lChId1, NULL,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL))
            ||
            (EDMA3_DRV_requestChannel (hEdma, &lChId2, NULL,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL))
            );
    }


    /**
    * Fill the PaRAM Sets associated with all these channels with transfer
    * specific information.
    */
    if (result == EDMA3_DRV_SOK)
    {
        paramSet.srcBIdx    = srcbidx;
        paramSet.destBIdx   = desbidx;
        paramSet.srcCIdx    = srccidx;
        paramSet.destCIdx   = descidx;

        paramSet.aCnt       = PING_PONG_ACNT;
        paramSet.bCnt       = PING_PONG_BCNT;
        paramSet.cCnt       = PING_PONG_CCNT;

        /* For AB-synchronized transfers, BCNTRLD is not used. */
        paramSet.bCntReload = BRCnt;

        /* Src & Dest are in INCR modes */
        paramSet.opt &= 0xFFFFFFFCu;
        /* Program the TCC */
        paramSet.opt |= ((tcc << OPT_TCC_SHIFT) & OPT_TCC_MASK);

        /* Enable Intermediate & Final transfer completion interrupt */
        paramSet.opt |= (1 << OPT_ITCINTEN_SHIFT);
        paramSet.opt |= (1 << OPT_TCINTEN_SHIFT);

        /* AB Sync Transfer Mode */
        paramSet.opt |= (1 << OPT_SYNCDIM_SHIFT);


        /* Program the source and dest addresses for master DMA channel */
        paramSet.srcAddr    = (uint32_t)(pingpongSrcBuf);
        paramSet.destAddr   = (uint32_t)(dstL1DBuff1);


        /* Write to the master DMA channel first. */
        result = EDMA3_DRV_setPaRAM(hEdma, chId, &paramSet);
    }


    /* If write is successful, write the same thing to first link channel. */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setPaRAM(hEdma, lChId1, &paramSet);
    }


    /**
    * Now modify the dest addresses and write the param set to the
    * second link channel.
    */
    if (result == EDMA3_DRV_SOK)
    {
        paramSet.destAddr   = (uint32_t)(dstL1DBuff2);

        result = EDMA3_DRV_setPaRAM(hEdma, lChId2, &paramSet);
    }



    /**
    * Do the linking now.
    * Master DMA channel is linked to IInd Link channel.
    * IInd Link channel is linked to Ist Link channel.
    * Ist Link channel is again linked to IInd Link channel.
    */
    if (result == EDMA3_DRV_SOK)
    {
        result = (
            (EDMA3_DRV_linkChannel (hEdma, chId, lChId2))
            ||
            (EDMA3_DRV_linkChannel (hEdma, lChId2, lChId1))
            ||
            (EDMA3_DRV_linkChannel (hEdma, lChId1, lChId2))
            );
    }

    /**
    * Save the handle to the master dma channel param set.
    * It will be used later to modify the source address quickly.
    */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_getPaRAMPhyAddr(hEdma, chId, &phyaddress);
    }

    /*
    - Algorithm used in the ping pong copy:
    1. Application starts EDMA of first image stripe into ping buffer in L1D.
    2. Application waits for ping EDMA to finish.
    3. Application starts EDMA of next image stripe into pong buffer in L1D.
    4. Application starts processing ping buffer.
    5. Application waits for pong EDMA to finish.
    6. Application starts EDMA of next image stripe into ping buffer in L1D.
    7. Application starts processing pong buffer.
    8. Repeat from step 3, until image exhausted.
    - EDMA re-programming should be minimized to reduce overhead (PaRAM
    accesses via slow config bus), i.e. use 2 reload PaRAM entries, and
    only change src address fields.
    */

    if (result == EDMA3_DRV_SOK)
    {
        irqRaised1 = 0;
        /* Param address successfully fetched. */
        param_handle = (EDMA3_DRV_ParamentryRegs *)phyaddress;

        /* Step 1 */
        result = EDMA3_DRV_enableTransfer (hEdma, chId,
            EDMA3_DRV_TRIG_MODE_MANUAL);
        /**
        * Every time a transfer is triggered, numenabled is decremented.
        */
        numenabled--;

        /**
        * Every time a transfer is triggered, pingpongSrcBufCopy is
        * incremented to point it to correct source address.
        */
        pingpongSrcBufCopy += PING_PONG_L1D_BUFFER_SIZE;
        /* Step 2 */
        /* Wait for the Completion ISR. */
        edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
        while (irqRaised1 == 0u)
        {
            /* Wait for the Completion ISR. */
            printf ("waiting for interrupt...\n");
        }
    }


    if (result == EDMA3_DRV_SOK)
    {
        /* Need to activate next param till numenabled is exhausted. */
        for (i = 0; numenabled; i++)
        {
            irqRaised1 = 0;

            /*
            * Now modify the source buffer in the param set
            * loaded to the master dma channel and trigger
            * the transfer again..
            */
            param_handle->SRC = (uint32_t)pingpongSrcBufCopy;

            /* Step 3 */
            result = EDMA3_DRV_enableTransfer (hEdma, chId,
                EDMA3_DRV_TRIG_MODE_MANUAL);

            /**
            * Every time a transfer is triggered, numenabled is decremented.
            */
            numenabled--;

            /**
            * Every time a transfer is triggered, pingpongSrcBufCopy is
            * incremented to point it to correct source address.
            */
            pingpongSrcBufCopy += PING_PONG_L1D_BUFFER_SIZE;

            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_ping_pong_mode: EDMA3_DRV_enableTransfer " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }

            /**
            * Step 4, copy the ping buffer to the dest buffer in
            * DDR (using CPU), as a part of processing.
            */
            result = process_ping_pong_buffer(0u);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_ping_pong_mode: process_ping_pong_buffer " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }


            /* Step 5 */
            /* Wait for the Completion ISR. */
            edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
            while (irqRaised1 == 0u)
            {
                /* Wait for the Completion ISR. */
                printf ("waiting for interrupt...\n");
            }

            /* Check the status of the completed transfer */
            if (irqRaised1 < 0)
            {
                /* Some error occured, break from the FOR loop. */
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("\r\nedma3_test: Event Miss Occured!!!\r\n");
#endif  /* EDMA3_DRV_DEBUG */

                /* Clear the error bits first */
                result = EDMA3_DRV_clearErrorBits (hEdma, chId);
                break;
            }


            /**
            * Last row will be transferred by the Pong buffer.
            * So this step should be jumped over.
            * Check for that...
            */
            if (numenabled)
            {
                irqRaised1 = 0;

                /* Step 6 */
                /*
                * Now modify the source buffer in the param set
                * again and trigger the transfer...
                */
                param_handle->SRC = (uint32_t)pingpongSrcBufCopy;

                result = EDMA3_DRV_enableTransfer (hEdma, chId,
                    EDMA3_DRV_TRIG_MODE_MANUAL);
                /**
                * Every time a transfer is triggered, numenabled is decremented.
                */
                numenabled--;

                /**
                * Every time a transfer is triggered, pingpongSrcBufCopy is
                * incremented to point it to correct source address.
                */
                pingpongSrcBufCopy += PING_PONG_L1D_BUFFER_SIZE;

                if (result != EDMA3_DRV_SOK)
                {
#ifdef EDMA3_DRV_DEBUG
                    EDMA3_DRV_PRINTF ("edma3_test_ping_pong_mode: EDMA3_DRV_enableTransfer " \
                        "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
                    break;
                }
            }

            /**
            * Step 7, copy the pong buffer to the dest buffer in
            * DDR (using CPU), as a part of processing.
            */
            result = process_ping_pong_buffer(1u);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_ping_pong_mode: process_ping_pong_buffer " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }
            if (numenabled)
            {
                /* Wait for the Completion ISR. */
                edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
                while (irqRaised1 == 0u)
                {
                    /* Wait for the Completion ISR. */
                    printf ("waiting for interrupt...\n");
                }
            }

            /* Check the status of the completed transfer */
            if (irqRaised1 < 0)
            {
                /* Some error occured, break from the FOR loop. */
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("\r\nedma3_test: Event Miss Occured!!!\r\n");
#endif  /* EDMA3_DRV_DEBUG */

                /* Clear the error bits first */
                result = EDMA3_DRV_clearErrorBits (hEdma, chId);
                break;
            }
        }
    }

    if (EDMA3_DRV_SOK == result)
    {
        /* Match the Source and Destination Buffers. */
        for (i = 0; i < PING_PONG_DDR_BUFFER_SIZE; i++)
        {
            if (pingpongSrcBuf[i] != pingpongDestBuf[i])
            {
                Istestpassed = 0u;
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF("edma3_test_ping_pong_mode: Data write-read matching" \
                    "FAILED at i = %d\r\n", i);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }
        }
        if (i == PING_PONG_DDR_BUFFER_SIZE)
        {
            Istestpassed = 1u;
        }



        /* Free the previously allocated channels. */
        result = (
            (EDMA3_DRV_freeChannel (hEdma, chId))
            ||
            (EDMA3_DRV_freeChannel (hEdma, lChId1))
            ||
            (EDMA3_DRV_freeChannel (hEdma, lChId2))
            );

        if (result != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF("edma3_test_ping_pong_mode: EDMA3_DRV_freeChannel() FAILED, " \
                "error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
        }
    }


    if(Istestpassed == 1u)
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_ping_pong_mode PASSED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
    }
    else
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_ping_pong_mode FAILED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
        result = ((EDMA3_DRV_SOK == result) ?
                    EDMA3_DATA_MISMATCH_ERROR : result);
    }
    return result;
}
