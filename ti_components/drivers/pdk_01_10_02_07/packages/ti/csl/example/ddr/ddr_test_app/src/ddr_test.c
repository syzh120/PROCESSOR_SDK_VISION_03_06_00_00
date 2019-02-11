/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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

/*
 * dma_test.c
 */

#include "stdint.h"
#include "stdlib.h"
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#include <ti/csl/arch/csl_arch.h>
/* Application header files */
#include <sample.h>

#define DDR_TEST_ADDRESS        (0x85000000U)
#define DDR_SIZE                (0x1FFFFFFFU)
#define DDR_TEST_COUNT          (0x2U)
#define DDR_RAND_TEST_COUNT     (0x5U)
#define DDR_TEST_SIZE           (0x1000U)
#define DDR_TEST_PATTERN        (0x55)

extern signed char       _srcBuffm[BUFFER_SIZE];
signed char             *srcBuffm;

extern volatile uint32_t transfer_complete;
extern uint32_t          base_address;
uint32_t ddr_start_addr;
extern uint32_t          gEnableAutorun;
extern int32_t           gTestStatus;
extern uint32_t          uartBaseAddr;
/*
 * Get DDR Size
 *
 */

void getDDRSize(uint32_t *dsize)
{
    UARTConfigPuts(uartBaseAddr,"\r\nEnter the size of DDR memory in hex(without 0x): ", -1);
    *dsize = UARTConfigGetHexNum(uartBaseAddr);
}

/*
 * Get User input
 *
 */
void getUserInput(uint32_t *test_num, uint32_t *start_addr, uint32_t *rand_cnt)
{
    UARTConfigPuts(uartBaseAddr,"\r\nHow many times should the test be repeated(enter a number):",
             -1);
    *test_num = UARTConfigGetNum(uartBaseAddr);

    UARTConfigPuts(uartBaseAddr,
        "\r\nEnter the start address of the memory to be tested in hex(without 0x):",
        -1);
    *start_addr = UARTConfigGetHexNum(uartBaseAddr);

    UARTConfigPuts(uartBaseAddr,
        "\r\nHow many times random mem test is to be repeated(enter a number):",
        -1);
    *rand_cnt = UARTConfigGetNum(uartBaseAddr);
}

/*
 * Get User input
 *
 */
void getUserInput2(uint32_t *dsize, uint32_t *test_num, uint32_t *start_addr,
                   uint8_t *pattern)
{
    UARTConfigPuts(uartBaseAddr,"\r\nHow many times should the test be repeated(enter a number):",
             -1);
    *test_num = UARTConfigGetNum(uartBaseAddr);

    UARTConfigPuts(uartBaseAddr,
        "\r\nEnter the start address of the memory to be tested in hex(without 0x):",
        -1);
    *start_addr = UARTConfigGetHexNum(uartBaseAddr);

    UARTConfigPuts(uartBaseAddr,
        "\r\nEnter the size of the DDR memory to be tested in hex(without 0x): ",
        -1);
    *dsize = UARTConfigGetHexNum(uartBaseAddr);

    UARTConfigPuts(uartBaseAddr,"\r\nEnter the pattern used to be tested in hex(without 0x):", -1);
    *pattern = UARTConfigGetHexNum(uartBaseAddr);
}

static uint32_t getSrcBufPhyAddr(uint32_t srcAddr)
{
#if (defined (__TI_ARM_V7M4__))
    srcAddr = srcAddr + 0x40000000;
#endif
    return srcAddr;
}

/*
 * DDR Test
 * Full memory read/write
 */
int32_t edma_mem_test1(uint32_t ddr_address, uint32_t ch_num, uint32_t tcc_num,
                       uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    signed char      *dst_addr;
    uint32_t          blk_size = DDR_SIZE;
    static int32_t    buf_size = BUFFER_SIZE;
    int32_t           i, retVal = STW_SOK, count;

    dst_addr = (signed char *) ddr_address;
    srcBuffm = (signed char *) (_srcBuffm);
    EDMA3CCPaRAMEntry edmaParam;

    UARTConfigPuts(uartBaseAddr,"\r\n********************************************************\r\n", -1);
    UARTConfigPuts(uartBaseAddr,"Running DDR test case 1-- Full memory read/write ", -1);

    UARTConfigPuts(uartBaseAddr,"\r\nSize of DDR is ", -1);
    UARTConfigPutHexNum(uartBaseAddr,blk_size);

    /*
     * Initialize the source address with a pattern
     * initialize dst address with zero/another pattern (optional)
     */

    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuffm[count] = (int) 0x55;
    }

    count = 0;

    while (blk_size != 0)
    {
        EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                            tcc_num,
                            evtq_num);

        edmaParam.opt     = 0;
        edmaParam.srcAddr = (uint32_t) srcBuffm;
        /* To change virtual address to physical*/
        edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
        edmaParam.destAddr = (uint32_t) (dst_addr);
        edmaParam.aCnt     = aCnt;
        edmaParam.bCnt     = bCnt;
        edmaParam.cCnt     = cCnt;
        edmaParam.srcBIdx  = 0;
        edmaParam.destBIdx = 0;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFFU;
        edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                              ((tcc_num <<
                                EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

        /*
         * Transfer is done in A-sync mode
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
            if (srcBuffm[i] != dst_addr[i])
            {
                retVal = STW_EFAIL;
                UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address\r\n", -1);
                UARTConfigPuts(uartBaseAddr,"Value at src address ", -1);
                UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &srcBuffm[i]);
                UARTConfigPuts(uartBaseAddr," is:", -1);
                UARTConfigPutHexNum(uartBaseAddr,srcBuffm[i]);
                UARTConfigPuts(uartBaseAddr,"\r\nValue at dst address ", -1);
                UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
                UARTConfigPuts(uartBaseAddr," is:", -1);
                UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                break;
            }
        }

        if (retVal == STW_EFAIL)
        {
            UARTConfigPuts(uartBaseAddr," \r\nEDMA TEST failed at address ", -1);
            UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
            gTestStatus = STW_EFAIL;
            break;
        }

        dst_addr += buf_size;
        blk_size -= buf_size;
        count++;

        if (count == 0x1FFF)
        {
            count = 0;
            UARTConfigPuts(uartBaseAddr,"\r\ndst address ", -1);
            UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &dst_addr[0]);
        }

        if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
        {
            aCnt     = blk_size;
            buf_size = blk_size;
        }
    }

    return retVal;
}

/*
 * DDR Test
 * Random memory read/write
 */

int32_t edma_mem_test2(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    uint32_t          i, count, flag = 0;
    int32_t           retVal = STW_SOK;
    signed char      *dst_addr;
    uint32_t          ddr_max_size = DDR_SIZE, randCnt;
    static int32_t    buf_size     = BUFFER_SIZE;
    uint32_t          test_num, randVal, tempCnt = 0;
    uint32_t          seedVal;
    uint32_t          num, numBlocks, tempVal;
    uint32_t          ddr_end_addr, rnd_ddr_addr;

    EDMA3CCPaRAMEntry edmaParam;

    UARTConfigPuts(uartBaseAddr,
        "\r\n****************************************************************",
        -1);
    UARTConfigPuts(uartBaseAddr,"\r\nRunning DDR test case 2 -- Random memory read/write\r\n ", -1);

    if (gEnableAutorun == 0)
    {
        getUserInput(&test_num, &ddr_start_addr, &randCnt);
    }
    else
    {
        test_num       = DDR_TEST_COUNT;
        ddr_start_addr = DDR_TEST_ADDRESS;
        randCnt        = DDR_RAND_TEST_COUNT;
    }

    dst_addr = (signed char *) ddr_start_addr;
    srcBuffm = (signed char *) (_srcBuffm);

    ddr_end_addr = (ddr_start_addr & 0xf0000000) + ddr_max_size;

    numBlocks = (ddr_max_size + 1) / buf_size;

    /*
     * Initialize the source address with a pattern
     *
     */
    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuffm[count] = (int) 0xAA;
    }

    for (num = 0; num < test_num; num++)
    {
        dst_addr = (signed char *) ddr_start_addr;

        while (randCnt)
        {
            EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                                tcc_num,
                                evtq_num);
            edmaParam.opt     = 0;
            edmaParam.srcAddr = (uint32_t) srcBuffm;
            /* To change virtual address to physical*/
            edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
            edmaParam.destAddr = (uint32_t) dst_addr;
            edmaParam.aCnt     = aCnt;
            edmaParam.bCnt     = bCnt;
            edmaParam.cCnt     = cCnt;
            edmaParam.srcBIdx  = 0;
            edmaParam.destBIdx = 0;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFFU;
            edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                                  ((tcc_num <<
                                    EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
            EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

            /*
             * Transfer is done in a sync mode
             * Number of triggers required are bCnt * cCnt
             */
            for (i = 0; i < (bCnt * cCnt); i++)
            {
                transfer_complete = 0;
                EDMA3EnableTransfer(base_address, ch_num,
                                    EDMA3_TRIG_MODE_MANUAL);
                while (transfer_complete != 1) ;
            }
            for (i = 0; i < (aCnt * bCnt * cCnt); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = STW_EFAIL;
                    UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address\r\n",
                             -1);
                    UARTConfigPuts(uartBaseAddr,"Value at src address ", -1);
                    UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutHexNum(uartBaseAddr,srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr,"\r\nValue at dst address ", -1);
                    UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                    break;
                }
            }
            if (retVal == STW_EFAIL)
            {
                UARTConfigPuts(uartBaseAddr," \r\n DDR TEST failed at address: ", -1);
                UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                gTestStatus = STW_EFAIL;
                break;
            }
            tempCnt = 0;
            do
            {
                tempCnt++;
                if (tempCnt > 10)
                    break;
                flag = 1;
                seedVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
                srand(seedVal);
                randVal      = rand() % numBlocks;
                tempVal      = buf_size * randVal;
                rnd_ddr_addr = ddr_start_addr + tempVal;
                if (((uint32_t) (rnd_ddr_addr) < ddr_end_addr) &&
                    ((uint32_t) (rnd_ddr_addr) > ddr_start_addr))
                {
                    dst_addr = (signed char *) rnd_ddr_addr;
                    flag     = 0;
                }
            } while (flag);
            UARTConfigPuts(uartBaseAddr,"\r\n Random DDR address ", -1);
            UARTConfigPutHexNum(uartBaseAddr,(uint32_t) rnd_ddr_addr);
            UARTConfigPuts(uartBaseAddr," size :", -1);
            UARTConfigPutHexNum(uartBaseAddr,buf_size);
            randCnt--;
        }
        UARTConfigPuts(uartBaseAddr,"\r\nTest count number ", -1);
        UARTConfigPutHexNum(uartBaseAddr,num);
    }

    return retVal;
}

/*
 * DDR Test
 * Sequential memory read/write
 */

int32_t edma_mem_test3(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    uint32_t          i, count;
    int32_t           retVal = STW_SOK;
    signed char      *dst_addr;
    uint32_t          blk_size = 0, bsize = 0;
    static int32_t    buf_size = BUFFER_SIZE;
    static uint32_t   test_num;
    uint8_t           pattern;

    uint32_t          num;

    EDMA3CCPaRAMEntry edmaParam;

    UARTConfigPuts(uartBaseAddr,
        "\r\n****************************************************************",
        -1);
    UARTConfigPuts(uartBaseAddr,"\r\nRunning DDR test case 3 -- Sequential memory read/write\r\n ", -1);

    if (gEnableAutorun == 0)
    {
        getUserInput2(&bsize, &test_num, &ddr_start_addr, &pattern);
    }
    else
    {
        bsize          = DDR_TEST_SIZE;
        test_num       = DDR_TEST_COUNT;
        ddr_start_addr = DDR_TEST_ADDRESS;
        pattern        = DDR_TEST_PATTERN;
    }

    dst_addr = (signed char *) ddr_start_addr;
    srcBuffm = (signed char *) (_srcBuffm);

    /*
     * Initialize the source address with a pattern
     *
     */
    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuffm[count] = (int) pattern;
    }

    for (num = 0; num < test_num; num++)
    {
        dst_addr = (signed char *) ddr_start_addr;
        blk_size = bsize;

        while (blk_size != 0)
        {
            EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                                tcc_num,
                                evtq_num);
            edmaParam.opt     = 0;
            edmaParam.srcAddr = (uint32_t) srcBuffm;

            /* To change virtual address to physical*/
            edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
            edmaParam.destAddr = (uint32_t) dst_addr;
            edmaParam.aCnt     = aCnt;
            edmaParam.bCnt     = bCnt;
            edmaParam.cCnt     = cCnt;
            edmaParam.srcBIdx  = 0;
            edmaParam.destBIdx = 0;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFFU;
            edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                                  ((tcc_num <<
                                    EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
            EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

            /*
             * Transfer is done in a sync mode
             * Number of triggers required are bCnt * cCnt
             */
            for (i = 0; i < (bCnt * cCnt); i++)
            {
                transfer_complete = 0;
                EDMA3EnableTransfer(base_address, ch_num,
                                    EDMA3_TRIG_MODE_MANUAL);
                while (transfer_complete != 1) ;
            }

            for (i = 0; i < (aCnt * bCnt * cCnt); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = STW_EFAIL;
                    UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address\r\n",
                             -1);
                    UARTConfigPuts(uartBaseAddr,"Value at src address ", -1);
                    UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutHexNum(uartBaseAddr,srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr,"\r\nValue at dst address ", -1);
                    UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                    break;
                }
            }

            if (retVal == STW_EFAIL)
            {
                UARTConfigPuts(uartBaseAddr," \r\nEDMA TEST failed at address: ", -1);
                UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                gTestStatus = STW_EFAIL;
                break;
            }

            dst_addr += buf_size;
            blk_size -= buf_size;

            if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
            {
                buf_size = blk_size;
            }
        }

        UARTConfigPuts(uartBaseAddr,"\r\nTest count number ", -1);
        UARTConfigPutHexNum(uartBaseAddr,num);
    }

    return retVal;
}

/*
 * DDR Test
 * Sequential increment pattern test
 */

int32_t edma_mem_test4(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    uint32_t          i, count;
    int32_t           retVal = STW_SOK;
    signed char      *dst_addr;
    uint32_t          blk_size = 0, bsize = 0;
    static int32_t    buf_size = BUFFER_SIZE;
    static uint32_t   test_num;
    uint8_t           pattern;

    uint32_t          num;

    EDMA3CCPaRAMEntry edmaParam;

    UARTConfigPuts(uartBaseAddr,
        "\r\n****************************************************************",
        -1);
    UARTConfigPuts(uartBaseAddr,"\r\nRunning DDR test case 4 -- Sequential increment pattern \r\n ",
             -1);

    if (gEnableAutorun == 0)
    {
        getUserInput2(&bsize, &test_num, &ddr_start_addr, &pattern);
    }
    else
    {
        bsize          = DDR_TEST_SIZE;
        test_num       = DDR_TEST_COUNT;
        ddr_start_addr = DDR_TEST_ADDRESS;
        pattern        = DDR_TEST_PATTERN;
    }
    dst_addr = (signed char *) ddr_start_addr;
    srcBuffm = (signed char *) (_srcBuffm);

    for (num = 0; num < test_num; num++)
    {
        dst_addr = (signed char *) ddr_start_addr;
        blk_size = bsize;

        while (blk_size != 0)
        {
            /*
             * Initialize the source address with a Sequential increment pattern
             *
             */
            for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
            {
                srcBuffm[count] = (int) pattern;
                pattern++;
            }

            EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                                tcc_num,
                                evtq_num);
            edmaParam.opt     = 0;
            edmaParam.srcAddr = (uint32_t) srcBuffm;
            /* To change virtual address to physical*/
            edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
            edmaParam.destAddr = (uint32_t) dst_addr;
            edmaParam.aCnt     = aCnt;
            edmaParam.bCnt     = bCnt;
            edmaParam.cCnt     = cCnt;
            edmaParam.srcBIdx  = 0;
            edmaParam.destBIdx = 0;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFFU;
            edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                                  ((tcc_num <<
                                    EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
            EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

            /*
             * Transfer is done in a sync mode
             * Number of triggers required are bCnt * cCnt
             */
            for (i = 0; i < (bCnt * cCnt); i++)
            {
                transfer_complete = 0;
                EDMA3EnableTransfer(base_address, ch_num,
                                    EDMA3_TRIG_MODE_MANUAL);
                while (transfer_complete != 1) ;
            }

            for (i = 0; i < (aCnt * bCnt * cCnt); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = STW_EFAIL;
                    UARTConfigPuts(uartBaseAddr,"\r\nError matching value at src and dst address\r\n",
                             -1);
                    UARTConfigPuts(uartBaseAddr,"Value at src address ", -1);
                    UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutHexNum(uartBaseAddr,srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr,"\r\nValue at dst address ", -1);
                    UARTConfigPutHexNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                    break;
                }
            }

            if (retVal == STW_EFAIL)
            {
                UARTConfigPuts(uartBaseAddr," \r\nEDMA TEST failed at address: ", -1);
                UARTConfigPutHexNum(uartBaseAddr,dst_addr[i]);
                gTestStatus = STW_EFAIL;
                break;
            }

            dst_addr += buf_size;
            blk_size -= buf_size;

            if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
            {
                buf_size = blk_size;
            }
        }

        UARTConfigPuts(uartBaseAddr,"\r\nTest count number ", -1);
        UARTConfigPutHexNum(uartBaseAddr,num);
    }

    return retVal;
}
