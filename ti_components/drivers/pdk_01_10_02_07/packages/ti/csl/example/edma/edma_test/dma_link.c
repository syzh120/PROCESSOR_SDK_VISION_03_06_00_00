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

extern signed char       _srcBuff1[MAX_BUFFER_SIZE];
extern signed char       _dstBuff1[MAX_BUFFER_SIZE];
extern signed char       _srcBuff2[MAX_BUFFER_SIZE];
extern signed char       _dstBuff2[MAX_BUFFER_SIZE];
extern signed char       _srcBuff3[MAX_BUFFER_SIZE];
extern signed char       _dstBuff3[MAX_BUFFER_SIZE];

extern signed char      *srcBuff1;
extern signed char      *dstBuff1;
extern signed char      *srcBuff2;
extern signed char      *dstBuff2;
extern signed char      *srcBuff3;
extern signed char      *dstBuff3;

extern volatile uint32_t transfer_complete;

extern uint32_t          base_address;
extern int32_t           gTestStatus;

extern uint32_t          uartBaseAddr;

int32_t dma_link_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                      uint32_t edma_paRAMId2, uint32_t edma_paRAMId3,
                      uint32_t aCnt, uint32_t bCnt,
                      uint32_t cCnt)
{
    int32_t           count;

    volatile uint32_t i;
	volatile int32_t  error = STW_SOK;

    EDMA3CCPaRAMEntry edmaParam;

    srcBuff1 = (signed char *) (_srcBuff1);
    dstBuff1 = (signed char *) (_dstBuff1);

    srcBuff2 = (signed char *) (_srcBuff2);
    dstBuff2 = (signed char *) (_dstBuff2);

    srcBuff3 = (signed char *) (_srcBuff3);
    dstBuff3 = (signed char *) (_dstBuff3);

    UARTConfigPuts(uartBaseAddr,"\r\nDma Link test", -1);

    /*
     * Initialize the source address with a pattern
     * Initialize source and destination buffers
     */

    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuff1[count] = (int) 0xAA;
        srcBuff2[count] = (int) 0xBB;
        srcBuff3[count] = (int) 0xCC;

        dstBuff1[count] = 0;
        dstBuff2[count] = 0;
        dstBuff3[count] = 0;
    }

    /*Set params for channel 1*/
    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num, tcc_num,
                        evtq_num);

    edmaParam.opt        = 0;
    edmaParam.srcAddr    = (uint32_t) srcBuff1;
    edmaParam.destAddr   = (uint32_t) dstBuff1;
    edmaParam.aCnt       = aCnt;
    edmaParam.bCnt       = bCnt;
    edmaParam.cCnt       = cCnt;
    edmaParam.srcBIdx    = aCnt;
    edmaParam.destBIdx   = aCnt;
    edmaParam.srcCIdx    = aCnt;
    edmaParam.destCIdx   = aCnt;
    edmaParam.bCntReload = bCnt;
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt       |=
        (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
         ((tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

    /*channel ch_num is been set to use same PaRAM set number as ch_num. i.e
     *paRAMID=ch_num */
    EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

    /*Set second set of parameters for link transfer*/
    edmaParam.opt        = 0;
    edmaParam.srcAddr    = (uint32_t) srcBuff2;
    edmaParam.destAddr   = (uint32_t) dstBuff2;
    edmaParam.aCnt       = aCnt;
    edmaParam.bCnt       = bCnt;
    edmaParam.cCnt       = cCnt;
    edmaParam.srcBIdx    = aCnt;
    edmaParam.destBIdx   = aCnt;
    edmaParam.srcCIdx    = aCnt;
    edmaParam.destCIdx   = aCnt;
    edmaParam.bCntReload = bCnt;
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt       |= (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK);

    /**
     * Setting the parameter for edma_paRAMId2.
     * The PaRAM set with ID edma_paRAMId2 is used for linking with channel
     * ch_num
     */
    EDMA3SetPaRAM(base_address, edma_paRAMId2, &edmaParam);

    /*Set third set of parameters for link transfer*/
    edmaParam.opt        = 0;
    edmaParam.srcAddr    = (uint32_t) srcBuff3;
    edmaParam.destAddr   = (uint32_t) dstBuff3;
    edmaParam.aCnt       = aCnt;
    edmaParam.bCnt       = bCnt;
    edmaParam.cCnt       = cCnt;
    edmaParam.srcBIdx    = aCnt;
    edmaParam.destBIdx   = aCnt;
    edmaParam.srcCIdx    = aCnt;
    edmaParam.destCIdx   = aCnt;
    edmaParam.bCntReload = bCnt;
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt       |= (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK);

    /**
     * Setting the parameter for edma_paRAMId3.
     * The PaRAM set with ID edma_paRAMId3 is linked with paRAMset ID2
     */
    EDMA3SetPaRAM(base_address, edma_paRAMId3, &edmaParam);

    /*PaRAM set with id edma_paRAMId2 is set to link with channel ch_num*/
    EDMA3LinkChannel(base_address, ch_num, edma_paRAMId2);

    /*PaRAM set with id edma_paRAMId3 is set to link with paramset with ID
     *edma_paRAMId2*/
    EDMA3LinkChannel(base_address, edma_paRAMId2, edma_paRAMId3);

    /**
     * Transfer is done in a sync mode
     * Number of triggers required are bCnt * cCnt
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        transfer_complete = 0;
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1) ;
    }

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

    /**
     * Now the transfer on Master channel is finished.
     * Trigger next (LINK) param.
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        transfer_complete = 0;
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1) ;
    }

    for (i = 0; i < (aCnt * bCnt * cCnt); i++)
    {
        if (srcBuff2[i] != dstBuff2[i])
        {
            error = STW_EFAIL;
            UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address", -1);
            gTestStatus = STW_EFAIL;
            break;
        }
    }

    /**
     * Now the transfer on Master channel is finished.
     * Trigger next (LINK) param.
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        transfer_complete = 0;
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1) ;
    }

    for (i = 0; i < (aCnt * bCnt * cCnt); i++)
    {
        if (srcBuff3[i] != dstBuff3[i])
        {
            error = STW_EFAIL;
            UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address", -1);
            gTestStatus = STW_EFAIL;
            break;
        }
    }

    return error;
}

