/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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

/** Test Case Description **/
/**
 * There are two big buffers of size (PING_PONG_NUM_COLUMNS *
 * PING_PONG_NUM_ROWS).
 * Both are present in DDR and are known as pingpongSrcBuf and pingpongDestBuf.
 * There are two small buffers of size (PING_PONG_L1D_BUFFER_SIZE). They are
 * known as
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

#include <stdint.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/example/edma/edma_test/sample.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_edma.h>

/**
 * Number of columns in the bigger source buffer.
 */
#define PING_PONG_NUM_COLUMNS           (72U)
/**
 * Number of columns in the bigger source buffer.
 */
#define PING_PONG_NUM_ROWS                (48U)
/* ACNT is equal to number of columns. */
#define PING_PONG_ACNT                          PING_PONG_NUM_COLUMNS
/* BCNT is equal to number of rows which will be transferred in one shot. */
#define PING_PONG_BCNT                          (8U)
/* CCNT is equal to 1. */
#define PING_PONG_CCNT                          (1U)

/* Number of times DMA will be triggered. */
#define PING_PONG_NUM_TRIGGERS           (PING_PONG_NUM_ROWS / PING_PONG_BCNT)

/* Size of bigger buffers in DDR. */
#define PING_PONG_DDR_BUFFER_SIZE     (PING_PONG_NUM_COLUMNS * \
                                       PING_PONG_NUM_ROWS)
/* Size of smaller buffers in IRAM. */
#define PING_PONG_L1D_BUFFER_SIZE     (PING_PONG_ACNT * PING_PONG_BCNT)

#if !defined (__ARM_ARCH_7A__) && !defined (BUILD_GCC)

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_pingpongSrcBuf, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char  _pingpongSrcBuf[PING_PONG_DDR_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_pingpongDestBuf, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char  _pingpongDestBuf[PING_PONG_DDR_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstL1DBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char  _dstL1DBuff1[PING_PONG_L1D_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstL1DBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char  _dstL1DBuff2[PING_PONG_L1D_BUFFER_SIZE];

#else
signed char __attribute__((section(".my_sect_ddr"))) _pingpongSrcBuf[
    PING_PONG_DDR_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _pingpongDestBuf[
    PING_PONG_DDR_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstL1DBuff1[
    PING_PONG_L1D_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstL1DBuff2[
    PING_PONG_L1D_BUFFER_SIZE];
#endif

/* Pointers for all those buffers */
signed char *pingpongSrcBuf;
signed char *pingpongDestBuf;
signed char *pingpongSrcBufCopy;
signed char *pingpongDestBufCopy;

signed char *dstL1DBuff1;
signed char *dstL1DBuff2;

/* Local MemCopy function */
void edma3MemCpy(volatile void *dst, const void *src, uint32_t len)
{
    uint32_t        i = 0U;
    const uint32_t *sr;
    uint32_t       *ds;

    sr = (const uint32_t *) src;
    ds = (uint32_t *) dst;

    for (i = 0; i < len / 4; i++)
    {
        *ds = *sr;
        ds++;
        sr++;
    }

    return;
}

void process_ping_pong_buffer(unsigned short buff_id)
{
    /**
     * Copy the L1D ping-pong buffers from L1D to DDR using CPU.
     * This is kind of dummy processing routine.
     */
    if (buff_id == 1U)
    {
        /* Copy pong buffer */

        edma3MemCpy((void *) (pingpongDestBufCopy),
                    (const void *) (dstL1DBuff2),
                    PING_PONG_L1D_BUFFER_SIZE);
    }
    else
    {
        /* Copy ping buffer */
        edma3MemCpy((void *) (pingpongDestBufCopy),
                    (const void *) (dstL1DBuff1),
                    PING_PONG_L1D_BUFFER_SIZE);
    }

    /* Adjust the pointer. */
    pingpongDestBufCopy += PING_PONG_L1D_BUFFER_SIZE;
}

extern volatile uint32_t transfer_complete;

extern uint32_t          base_address;
extern int32_t           gTestStatus;

extern uint32_t          uartBaseAddr;

int32_t dma_ping_pong_test(uint32_t chId, uint32_t tcc, uint32_t evtq_num,
                           uint32_t lChId1, uint32_t lChId2)
{
    EDMA3CCPaRAMEntry paramSet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int32_t i;
    uint32_t      count;
    int32_t       Istestpassed = 0U;
    uint32_t      BRCnt        = 0;
    int32_t       srcbidx = 0, desbidx = 0;
    int32_t       srccidx = 0, descidx = 0;
    /* Number of triggers for EDMA3. */
    uint32_t      numenabled = PING_PONG_NUM_TRIGGERS;

    UARTConfigPuts(uartBaseAddr,"\r\nDMA Ping Pong test", -1);
    pingpongSrcBuf      = (signed char *) (_pingpongSrcBuf);
    pingpongDestBuf     = (signed char *) (_pingpongDestBuf);
    pingpongSrcBufCopy  = pingpongSrcBuf;
    pingpongDestBufCopy = pingpongDestBuf;
    dstL1DBuff1         = (signed char *) (_dstL1DBuff1);
    dstL1DBuff2         = (signed char *) (_dstL1DBuff2);
    /* Initalize source buffer for PING_PONG_DDR_BUFFER_SIZE bytes of data */
    for (count = 0U; count < PING_PONG_DDR_BUFFER_SIZE; count++)
    {
        pingpongSrcBuf[count] = (count % 0xFF);
    }

    /* Set B count reload as B count. */
    BRCnt = PING_PONG_BCNT;

    /* Setting up the SRC/DES Index */
    srcbidx =  PING_PONG_ACNT;
    desbidx =  PING_PONG_ACNT;

    /* AB Sync Transfer Mode */
    srccidx = (PING_PONG_ACNT *  PING_PONG_BCNT);
    descidx = (PING_PONG_ACNT *  PING_PONG_BCNT);

    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, chId, tcc,
                        evtq_num);

    /**
     * Fill the PaRAM Sets associated with all these channels with transfer
     * specific information.
     */
    paramSet.srcBIdx  = srcbidx;
    paramSet.destBIdx = desbidx;
    paramSet.srcCIdx  = srccidx;
    paramSet.destCIdx = descidx;

    paramSet.aCnt = PING_PONG_ACNT;
    paramSet.bCnt = PING_PONG_BCNT;
    paramSet.cCnt = PING_PONG_CCNT;

    /* For AB-synchronized transfers, BCNTRLD is not used. */
    paramSet.bCntReload = BRCnt;

    /* Src & Dest are in INCR modes */
    paramSet.opt &= 0xFFFFFFFCU;
    /* Program the TCC */
    paramSet.opt |= ((tcc << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);

    /* Enable Intermediate & Final transfer completion interrupt */
    paramSet.opt |= (EDMA3_OPT_ITCINTEN_MASK);
    paramSet.opt |= (EDMA3_OPT_TCINTEN_MASK);

    /* AB Sync Transfer Mode */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_SYNCDIM_SHIFT);

    /* Program the source and dest addresses for master DMA channel */
    paramSet.srcAddr  = (uint32_t) pingpongSrcBuf;
    paramSet.destAddr = (uint32_t) dstL1DBuff1;

    EDMA3SetPaRAM(base_address, chId, &paramSet);

    /* write the same thing to first link channel. */
    EDMA3SetPaRAM(base_address, lChId1, &paramSet);

    /* Now modify the dest addresses and write the param set to the
     * second link channel.
     */
    paramSet.destAddr = (uint32_t) dstL1DBuff2;
    EDMA3SetPaRAM(base_address, lChId2, &paramSet);

    /* Do the linking now.
     * Master DMA channel is linked to IInd Link channel.
     * IInd Link channel is linked to Ist Link channel.
     * Ist Link channel is again linked to IInd Link channel.
     */
    EDMA3LinkChannel(base_address, chId, lChId2);
    EDMA3LinkChannel(base_address, lChId2, lChId1);
    EDMA3LinkChannel(base_address, lChId1, lChId2);

    /*
     * - Algorithm used in the ping pong copy:
     * 1. Application starts EDMA of first image stripe into ping buffer in L1D.
     * 2. Application waits for ping EDMA to finish.
     * 3. Application starts EDMA of next image stripe into pong buffer in L1D.
     * 4. Application starts processing ping buffer.
     * 5. Application waits for pong EDMA to finish.
     * 6. Application starts EDMA of next image stripe into ping buffer in L1D.
     * 7. Application starts processing pong buffer.
     * 8. Repeat from step 3, until image exhausted.
     * - EDMA re-programming should be minimized to reduce overhead (PaRAM
     *  accesses via slow config bus), i.e. use 2 reload PaRAM entries, and
     *  only change src address fields.
     */

    transfer_complete = 0;

    /* Step 1 */
    EDMA3EnableTransfer(base_address, chId, EDMA3_TRIG_MODE_MANUAL);

    /**
     * Every time a transfer is triggered, numenabled is decremented.
     */
    numenabled--;
    /**
     * Every time a transfer is triggered, pingpongSrcBufCopy is
     * incremented to point it to correct source address.
     */
    pingpongSrcBufCopy += PING_PONG_L1D_BUFFER_SIZE;
    /* Need to activate next param till numenabled is exhausted. */
    for (i = 0; numenabled; i++)
    {
        /* Step 2 */
        /* Wait for the Completion ISR. */
        while (transfer_complete == 0U) ;

        transfer_complete = 0;

        /*
         * Now modify the source buffer in the param set
         * loaded to the master dma channel and trigger
         * the transfer again..
         */
        EDMA3QdmaSetPaRAMEntry(base_address, chId, EDMA3CC_PARAM_ENTRY_SRC,
                               (uint32_t) pingpongSrcBufCopy);
        /* Step 3 */
        EDMA3EnableTransfer(base_address, chId, EDMA3_TRIG_MODE_MANUAL);
        /**
         * Every time a transfer is triggered, numenabled is decremented.
         */
        numenabled--;

        /**
         * Every time a transfer is triggered, pingpongSrcBufCopy is
         * incremented to point it to correct source address.
         */
        pingpongSrcBufCopy += PING_PONG_L1D_BUFFER_SIZE;

        /**
         * Step 4, copy the ping buffer to the dest buffer in
         * DDR (using CPU), as a part of processing.
         */
        process_ping_pong_buffer(0U);

        /* Step 5 */
        /* Wait for the Completion ISR. */
        while (transfer_complete == 0U) ;

        /**
         * Last row will be transferred by the Pong buffer.
         * So this step should be jumped over.
         * Check for that...
         */
        if (numenabled)
        {
            transfer_complete = 0;

            /* Step 6 */
            /*
             * Now modify the source buffer in the param set
             * again and trigger the transfer...
             */
            EDMA3QdmaSetPaRAMEntry(base_address, chId, EDMA3CC_PARAM_ENTRY_SRC,
                                   (uint32_t) pingpongSrcBufCopy);
            EDMA3EnableTransfer(base_address, chId, EDMA3_TRIG_MODE_MANUAL);
            /**
             * Every time a transfer is triggered, numenabled is decremented.
             */
            numenabled--;

            /**
             * Every time a transfer is triggered, pingpongSrcBufCopy is
             * incremented to point it to correct source address.
             */
            pingpongSrcBufCopy += PING_PONG_L1D_BUFFER_SIZE;
        }

        /**
         * Step 7, copy the pong buffer to the dest buffer in
         * DDR (using CPU), as a part of processing.
         */
        process_ping_pong_buffer(1U);

        /* Wait for the Completion ISR. */
        while (transfer_complete == 0U) ;
    }

    /* Match the Source and Destination Buffers. */
    for (i = 0; i < PING_PONG_DDR_BUFFER_SIZE; i++)
    {
        if (pingpongSrcBuf[i] != pingpongDestBuf[i])
        {
            Istestpassed = STW_EFAIL;
            UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address", -1);
            gTestStatus = STW_EFAIL;
            break;
        }
    }
    if (i == PING_PONG_DDR_BUFFER_SIZE)
    {
        Istestpassed = STW_SOK;
    }

    return Istestpassed;
}

