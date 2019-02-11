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

/*
 * main.c
 */
#include <stdint.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/example/edma/edma_test/sample.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_edma.h>

static void edma_wait_for_transfer_completion(uint32_t tcc_num);

extern signed char  _srcBuff1[MAX_BUFFER_SIZE];
extern signed char  _dstBuff1[MAX_BUFFER_SIZE];

extern signed char *srcBuff1;
extern signed char *dstBuff1;

extern uint32_t          uartBaseAddr;

extern uint32_t     base_address;
extern int32_t      gTestStatus;
int32_t dma_polled(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                   uint32_t aCnt, uint32_t bCnt,
                   uint32_t cCnt)
{
    volatile uint32_t i, count;
	volatile int32_t error = STW_SOK;
    EDMA3CCPaRAMEntry edmaParam;

    srcBuff1 = (signed char *) (_srcBuff1);
    dstBuff1 = (signed char *) (_dstBuff1);

    UARTConfigPuts(uartBaseAddr,"\r\nDma Polled Mode test", -1);

    /*
     * Initialize the source address with a pattern
     * initialize dst address with zero/another pattern (optional)
     */
    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuff1[count] = (int) 0xAA;

        dstBuff1[count] = 0;
    }

#if defined (__ARM_ARCH_7A__)
    CSL_a15WbDataCache((void *)_srcBuff1, MAX_BUFFER_SIZE);
    CSL_a15WbDataCache((void *)_dstBuff1, MAX_BUFFER_SIZE);
#endif
    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num, tcc_num,
                        evtq_num);

    edmaParam.opt      = 0;
    edmaParam.srcAddr  = (uint32_t) srcBuff1;
    edmaParam.destAddr = (uint32_t) dstBuff1;
    edmaParam.aCnt     = aCnt;
    edmaParam.bCnt     = bCnt;
    edmaParam.cCnt     = cCnt;
    edmaParam.srcBIdx  = aCnt;
    edmaParam.destBIdx = aCnt;
    edmaParam.srcCIdx  = aCnt;
    edmaParam.destCIdx = aCnt;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
         ((tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

    EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

    /*
     * Transfer is done in a sync mode
     * Number of triggers required are bCnt * cCnt
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
        edma_wait_for_transfer_completion(tcc_num);
        EDMA3ClrIntr(base_address, tcc_num);
    }

#if defined (__ARM_ARCH_7A__)
    CSL_a15InvDataCache((void *)_srcBuff1, MAX_BUFFER_SIZE);
    CSL_a15InvDataCache((void *)_dstBuff1, MAX_BUFFER_SIZE);
#endif

    for (i = 0; i < (aCnt * bCnt * cCnt); i++)
    {
        if (srcBuff1[i] != dstBuff1[i])
        {
            error = STW_EFAIL;
            UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address", -1);
            gTestStatus = STW_EFAIL;
            break;
        }
    }

    return error;
}

static void edma_wait_for_transfer_completion(uint32_t tcc_num)
{
    if(tcc_num < 32)
    {
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << tcc_num)) !=
            (0x1 << tcc_num)) ;
    }
    else
    {
        while ((EDMA3IntrStatusHighGet(base_address) &
               (0x1 << (tcc_num - 32))) !=
               (0x1 << (tcc_num - 32))) ;
    }
}

