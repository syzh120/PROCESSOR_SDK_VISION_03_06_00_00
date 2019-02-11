/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file     diagLib_mcspi.c
 * \brief    This file contains MCSPI software test APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <diagLib_utils.h>
#include <ti/diag/diagLib_mcspi.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* Default MCSPI In clock in Hz */
#define DIAGLIB_MCSPI_IN_CLK            (48000000U)
/* Default FIFO threshold in bytes */
#define DIAGLIB_MCSPI_FIFO_THR          (32U)
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static int32_t DiagLib_mcspiChkParams(const DiagLib_McspiTestParams_t
                                                            *testParams);
static void DiagLib_mcspiInitializeBuffers(const DiagLib_McspiTestParams_t
                                                            *testParams);
static int32_t DiagLib_mcspiConfigureDma(const DiagLib_McspiTestParams_t
                                                            *testParams);
static int32_t DiagLib_mcspiTxEdmaParamSet(const DiagLib_McspiTestParams_t
                                                            *testParams);
static int32_t DiagLib_mcspiRxEdmaParamSet(const DiagLib_McspiTestParams_t
                                                            *testParams);
static int32_t DiagLib_mcspiTransfer(const DiagLib_McspiTestParams_t
                                *testParams, DiagLib_McspiObj_t *mcspiObj);
static int32_t DiagLib_mcspiPolledTransfer(const DiagLib_McspiTestParams_t
                                                            *testParams);
static int32_t DiagLib_mcspiVerifyData(const DiagLib_McspiTestParams_t
                                                            *testParams);
/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */
/* ========================================================================== */
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibMcspiTestParams_init(DiagLib_McspiTestParams_t *testParams)
{
    if (NULL != testParams)
    {
        testParams->baseAddr            = SOC_MCSPI1_BASE;
        testParams->chNumber            = MCSPI_CHANNEL_0;
        testParams->spiOutClk           = DIAGLIB_MCSPI_DEFAULT_CLK_OUT;
        testParams->spiClkMode          = MCSPI_CLK_MODE_0;
        testParams->wordLen             = MCSPI_WORD_LENGTH_MAX;
        testParams->transferMode        = DIAGLIB_MCSPI_POLLED_MODE;
        testParams->dataCount           = DIAGLIB_MCSPI_FIFO_THR;
        testParams->txBuffer            = NULL;
        testParams->rxBuffer            = NULL;
        testParams->timeout             = DIAGLIB_UTILS_DEFAULT_TIMEOUT;
        testParams->mcspiTxEdmaChNum    = CSL_EDMA3_CHA0_MCSPI0_TX;
        testParams->mcspiRxEdmaChNum    = CSL_EDMA3_CHA0_MCSPI0_RX;
        testParams->mcspiEdmaEvtqNum    = 0U;
        testParams->performCacheOps     = (uint32_t)FALSE;
        testParams->internalLpbk        = (uint32_t)TRUE;
    }
}

int32_t DiagLib_mcspiStartTest(const DiagLib_McspiTestParams_t *testParams,
                                                DiagLib_McspiObj_t *mcspiObj)
{
    int32_t status = STW_SOK;

    status = DiagLib_mcspiChkParams(testParams);

    if(status == STW_SOK)
    {
        /* Reset the McSPI instance.*/
        McSPIReset(testParams->baseAddr);

        /* CLOCKACTIVITY bit - OCP and Functional clocks are maintained */
        /* SIDLEMODE     bit - Ignore idle request & configure in normal mode
        */
        /* AUTOIDLE      bit - Disable (OCP clock is running free, no gating) */
        MCSPISysConfigSetup(testParams->baseAddr, MCSPI_CLOCKS_OCP_ON_FUNC_ON,
                            MCSPI_SIDLEMODE_NO, MCSPI_WAKEUP_DISABLE,
                            MCSPI_AUTOIDLE_OFF);

        /* Enable chip select pin.*/
        McSPICSEnable(testParams->baseAddr);

        /* Enable master mode of operation.*/
        McSPIMasterModeEnable(testParams->baseAddr);

        if(testParams->internalLpbk == (uint32_t)TRUE)
        {
            /* Perform the necessary configuration for master mode. */
            if( McSPIMasterModeConfig(testParams->baseAddr, MCSPI_SINGLE_CH,
                                           MCSPI_TX_RX_MODE,
                                           MCSPI_DATA_LINE_COMM_MODE_4,
                                           testParams->chNumber) == FALSE)
            {
                status = STW_EFAIL;
            }
        }
        else
        {
            if( McSPIMasterModeConfig(testParams->baseAddr, MCSPI_SINGLE_CH,
                                           MCSPI_TX_RX_MODE,
                                           MCSPI_DATA_LINE_COMM_MODE_6,
                                           testParams->chNumber) == FALSE)
            {
                status = STW_EFAIL;
            }
        }
    }

    if(status == STW_SOK)
    {
        /* Configure the McSPI bus clock depending on clock mode. */
        McSPIClkConfig(testParams->baseAddr, DIAGLIB_MCSPI_IN_CLK,
                        testParams->spiOutClk, testParams->chNumber,
                        testParams->spiClkMode);
        /* Configure the word length.*/
        McSPIWordLengthSet(testParams->baseAddr,
                MCSPI_WORD_LENGTH(testParams->wordLen), testParams->chNumber);
        /* Set polarity of SPIEN to low.*/
        McSPICSPolarityConfig(testParams->baseAddr,
                    (uint32_t) MCSPI_CH0CONF_EPOL_ACTIVELOW << MCSPI_CH0CONF_EPOL_SHIFT,
                    testParams->chNumber);

        /* Enable the transmitter FIFO of McSPI peripheral.*/
        McSPITxFIFOConfig(testParams->baseAddr, MCSPI_TX_FIFO_ENABLE,
                                                testParams->chNumber);

        /* Enable the receiver FIFO of McSPI peripheral.*/
        McSPIRxFIFOConfig(testParams->baseAddr, MCSPI_RX_FIFO_ENABLE,
                                                testParams->chNumber);

        DiagLib_mcspiInitializeBuffers(testParams);
    }

    if(status == STW_SOK)
    {
        if (testParams->transferMode == DIAGLIB_MCSPI_DMA_MODE)
        {
            /* Request DMA Channel and TCC for SPI Transmit*/
            EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                    testParams->mcspiTxEdmaChNum, testParams->mcspiTxEdmaChNum,
                    testParams->mcspiEdmaEvtqNum);

            /* Request DMA Channel and TCC for SPI Receive*/
            EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                    testParams->mcspiRxEdmaChNum, testParams->mcspiRxEdmaChNum,
                    testParams->mcspiEdmaEvtqNum);

            /* DMA PaRAM Configuration for McSPI */
            status = DiagLib_mcspiConfigureDma(testParams);
        }
    }

    if(status == STW_SOK)
    {
        /* Start the MCSPI data transfer */
        status = DiagLib_mcspiTransfer(testParams, mcspiObj);
    }

    mcspiObj->testState = status;
    return status;
}

int32_t DiagLib_mcspiISR(const DiagLib_McspiTestParams_t *testParams,
                                                DiagLib_McspiObj_t *mcspiObj)
{
    int32_t status = STW_SOK;

    uint32_t isIPR  = 0;
    uint32_t isIPRH = 0;

    isIPR  = EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT);
    isIPRH = EDMA3IntrStatusHighGet(SOC_EDMA_TPCC_BASE_VIRT);

    if (isIPR)
    {
        if(isIPR == ((uint32_t)1U << testParams->mcspiRxEdmaChNum))
        {
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, testParams->mcspiRxEdmaChNum);
        }
        else
        {
            status = DIAGLIB_MCSPI_TEST_FAIL;
        }
    }
    else if (isIPRH)
    {
        if(isIPRH == ((uint32_t)1U << (testParams->mcspiRxEdmaChNum - 32U)))
        {
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, testParams->mcspiRxEdmaChNum);
        }
        else
        {
            status = DIAGLIB_MCSPI_TEST_FAIL;
        }
    }
    else
    {
        status = DIAGLIB_MCSPI_TEST_FAIL;
    }

    /* Disable the Tx/Rx DMA events of McSPI peripheral */
    McSPIDMADisable(testParams->baseAddr, MCSPI_CH0CONF_DMAW_MASK,
                                                testParams->chNumber);
    McSPIDMADisable(testParams->baseAddr, MCSPI_CH0CONF_DMAR_MASK,
                                                testParams->chNumber);

    /* Force SPIEN line to the inactive state.*/
    McSPICSDeAssert(testParams->baseAddr, testParams->chNumber);

    /* Disable the McSPI channel.*/
    McSPIChannelDisable(testParams->baseAddr, testParams->chNumber);

    /* Verify whether the data written by Master and the one read by
     * Slave are Equal */
    if(status == STW_SOK)
    {
        status = DiagLib_mcspiVerifyData(testParams);
    }

    mcspiObj->testState = status;
    return status;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t DiagLib_mcspiChkParams(const DiagLib_McspiTestParams_t
                                                            *testParams)
{
    int32_t status = STW_SOK;

    if(testParams->spiOutClk > DIAGLIB_MCSPI_IN_CLK)
    {
        status = STW_EINVALID_PARAMS;
    }

    /* Supported word length is from 4bits to 32bits */
    if((testParams->wordLen < MCSPI_WORD_LENGTH_MIN) ||
            (testParams->wordLen > MCSPI_WORD_LENGTH_MAX))
    {
        status = STW_EINVALID_PARAMS;
    }
    if((testParams->txBuffer == NULL) || (testParams->rxBuffer == NULL))
    {
        status = STW_EINVALID_PARAMS;
    }

    return status;
}

static void DiagLib_mcspiInitializeBuffers(const DiagLib_McspiTestParams_t *testParams)
{
    uint32_t index = 0;

    for (index = 0; index < testParams->dataCount; index++)
    {
        /* Initialize the txBuffer & rxBuffer with a known pattern of data */
        testParams->txBuffer[index] = index;
        testParams->rxBuffer[index] = 0x60U;
    }

    /* Write back from cache and invalidate cache to complete the transfer */
    if(testParams->performCacheOps == (uint32_t)TRUE)
    {
        BspOsal_cacheWbAll();
    }

}

static int32_t DiagLib_mcspiConfigureDma(const DiagLib_McspiTestParams_t
                                                            *testParams)
{
    int32_t status = STW_SOK;
    uint16_t wordCnt = testParams->dataCount /
                            (testParams->wordLen / (uint16_t)8U);

    /* Configure the read data parameters of McSPI for Edma transmit.*/
    status = DiagLib_mcspiTxEdmaParamSet(testParams);

    if(status == STW_SOK)
    {
        /* Configure the read data parameters of McSPI for Edma receive.*/
        status = DiagLib_mcspiRxEdmaParamSet(testParams);
    }

    if(status == STW_SOK)
    {
        /* Set the word count field with the data length to be transferred.*/
        McSPIWordCountSet(testParams->baseAddr, wordCnt);

        McSPIFIFOTrigLvlSet(testParams->baseAddr, DIAGLIB_MCSPI_FIFO_THR,
                                DIAGLIB_MCSPI_FIFO_THR, MCSPI_TX_RX_MODE);

        /* Enable the Tx/Rx DMA events for McSPI. */
        McSPIDMAEnable(testParams->baseAddr,
                       MCSPI_DMA_RX_EVENT | MCSPI_DMA_TX_EVENT,
                       testParams->chNumber);
    }
    return status;
}

/*
 * This function is used to set the PaRAM entries of EDMA3 for the given
 * Transmit Channel of SPIx instance.
 * The corresponding EDMA3 channel is also enabled for transmission.
 */
static int32_t DiagLib_mcspiTxEdmaParamSet(const DiagLib_McspiTestParams_t
                                                                *testParams)
{
    volatile uint32_t destAddr = NULL;
    int32_t status = STW_SOK;

    switch(testParams->chNumber)
    {
        case MCSPI_CHANNEL_0:
        {
            destAddr = testParams->baseAddr + MCSPI_TX0;
            break;
        }
        case MCSPI_CHANNEL_1:
        {
            destAddr = testParams->baseAddr + MCSPI_TX1;
            break;
        }
        case MCSPI_CHANNEL_2:
        {
            destAddr = testParams->baseAddr + MCSPI_TX2;
            break;
        }
        case MCSPI_CHANNEL_3:
        {
            destAddr = testParams->baseAddr + MCSPI_TX3;
            break;
        }
        default:
        {
            status = STW_EBADARGS;
            break;
        }
    }

    if(status == STW_SOK)
    {
        /* Fill the PaRAM Set with transfer specific information. */
        EDMA3CCPaRAMEntry paramSet = {0U};

        /* srcAddr holds address of memory location buffer. */
        paramSet.srcAddr = (uint32_t) testParams->txBuffer;

        /* destAddr holds address of McSPI_TX register. */
        paramSet.destAddr = destAddr;

        /* aCnt holds the number of bytes in an array. */
        paramSet.aCnt = testParams->wordLen / 0x8U;

        /* bCnt holds the number of such arrays to be transferred. */
        paramSet.bCnt = DIAGLIB_MCSPI_FIFO_THR / paramSet.aCnt;

        /* cCnt is number of frames of aCnt*bBcnt bytes to be transferred */
        paramSet.cCnt = testParams->dataCount / DIAGLIB_MCSPI_FIFO_THR;

        /*
        ** The srcBidx should be incremented by 4bytes since the
        ** source used here is 32bit int array.
        */
        paramSet.srcBIdx  = 4U;
        paramSet.destBIdx = 0U;

        /* Async Transfer Mode is set in OPT.*/
        /* srCIdx and destCIdx set to zero since ASYNC Mode is used. */
        paramSet.srcCIdx  = 4U * paramSet.bCnt;
        paramSet.destCIdx = 0U;

        /* Linking transfers in EDMA3 are not used. */
        paramSet.linkAddr = 0xFFFFU;
        paramSet.bCntReload = 0U;

        paramSet.opt = 0x00000000U;

        /* Set TCC field in OPT with the tccNum. */
        paramSet.opt |= (testParams->mcspiTxEdmaChNum <<
                        EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK;

        paramSet.opt |= (uint32_t)1U << EDMA_TPCC_OPT_SYNCDIM_SHIFT;

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, testParams->mcspiTxEdmaChNum,
                                                            &paramSet);

        /* EDMA3 Transfer is Enabled. */
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, testParams->mcspiTxEdmaChNum,
                                                        EDMA3_TRIG_MODE_EVENT);
    }
    return status;
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Receive
** event of channel 0 of McSPI1 instance. The corresponding EDMA3 channel
** is also enabled for reception.
*/
static int32_t DiagLib_mcspiRxEdmaParamSet(const DiagLib_McspiTestParams_t
                                                                *testParams)
{
    int32_t status = STW_SOK;
    volatile uint32_t srcAddr = NULL;

    switch(testParams->chNumber)
    {
        case MCSPI_CHANNEL_0:
        {
            srcAddr = testParams->baseAddr + MCSPI_RX0;
            break;
        }
        case MCSPI_CHANNEL_1:
        {
            srcAddr = testParams->baseAddr + MCSPI_RX1;
            break;
        }
        case MCSPI_CHANNEL_2:
        {
            srcAddr = testParams->baseAddr + MCSPI_RX2;
            break;
        }
        case MCSPI_CHANNEL_3:
        {
            srcAddr = testParams->baseAddr + MCSPI_RX3;
            break;
        }
        default:
        {
            status = STW_EBADARGS;
            break;
        }
    }

    if(status == STW_SOK)
    {
        EDMA3CCPaRAMEntry paramSet = {0U};

        /* Fill the PaRAM Set with Receive specific information.*/

        /* srcAddr holds address of SPI Rx FIFO.*/
        paramSet.srcAddr = srcAddr;

        /* destAddr is address of memory location named buffer.*/
        paramSet.destAddr = (uint32_t) testParams->rxBuffer;

        /* aCnt holds the number of bytes in an array.*/
        paramSet.aCnt = testParams->wordLen / 0x8U;

        /* bCnt holds the number of such arrays to be transferred.*/
        paramSet.bCnt = DIAGLIB_MCSPI_FIFO_THR / paramSet.aCnt;

        /* cCnt is number of frames of aCnt*bBcnt bytes to be transferred.*/
        paramSet.cCnt = testParams->dataCount / DIAGLIB_MCSPI_FIFO_THR;

        /* The srcBidx should not be incremented since it is a h/w register.*/
        paramSet.srcBIdx = 0U;

        /* The destBidx should be incremented for every aCnt bytes.*/
        paramSet.destBIdx = 4U;

        /* Async Transfer Mode. */
        /* srCIdx and destCIdx set to zero since ASYNC Mode is used.*/
        paramSet.srcCIdx  = 0U;
        paramSet.destCIdx = 4U * paramSet.bCnt;

        /* Linking transfers in EDMA3 are not used.*/
        paramSet.linkAddr = 0xFFFFU;

        paramSet.bCntReload = 0U;

        paramSet.opt = 0x00000000U;

        /* Set TCC field in OPT with the tccNum.*/
        paramSet.opt |= (testParams->mcspiRxEdmaChNum <<
                        EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK;
        paramSet.opt |= (uint32_t)1U << EDMA_TPCC_OPT_TCINTEN_SHIFT;
        paramSet.opt |= (uint32_t)1U << EDMA_TPCC_OPT_SYNCDIM_SHIFT;

        /* Now write the PaRam Set to EDMA3.*/
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, testParams->mcspiRxEdmaChNum,
                                                            &paramSet);

        /* EDMA3 Transfer is Enabled.*/
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, testParams->mcspiRxEdmaChNum,
                                                        EDMA3_TRIG_MODE_EVENT);
    }

    return status;
}

static int32_t DiagLib_mcspiTransfer(const DiagLib_McspiTestParams_t *testParams,
                                                DiagLib_McspiObj_t *mcspiObj)
{

    int32_t status = STW_SOK;
    /* Enable the McSPI channel for communication.*/
    McSPIChannelEnable(testParams->baseAddr, testParams->chNumber);

    /* SPIEN line is forced to low state.*/
    McSPICSAssert(testParams->baseAddr, testParams->chNumber);

    if (testParams->transferMode == DIAGLIB_MCSPI_POLLED_MODE)
    {
        status = DiagLib_mcspiPolledTransfer(testParams);

        if(status == STW_SOK)
        {
            /* Force SPIEN line to the inactive state.*/
            McSPICSDeAssert(testParams->baseAddr, testParams->chNumber);

            /* Disable the McSPI channel.*/
            McSPIChannelDisable(testParams->baseAddr, testParams->chNumber);

            /* Clear the TX/RX full events */
            McSPIIntStatusClear(testParams->baseAddr,
                        MCSPI_INT_RX_FULL(testParams->chNumber));
            McSPIIntStatusClear(testParams->baseAddr,
                        MCSPI_INT_TX_EMPTY(testParams->chNumber));

            /* Verify whether the data written by Master and the one read by
            * Slave are Equal */
            status = DiagLib_mcspiVerifyData(testParams);
        }
    }
    else
    {
        status = DIAGLIB_MCSPI_TEST_PENDING;
    }

    mcspiObj->testState = status;
    return status;
}

static int32_t DiagLib_mcspiPolledTransfer(const DiagLib_McspiTestParams_t
                                                            *testParams)
{
    int32_t status = STW_SOK;
    uint32_t       *p_rx;
    const uint32_t *p_tx;
    uint16_t length;
    uint32_t timeStart, elapsedTime = 0U;

    p_tx   = testParams->txBuffer;
    p_rx   = testParams->rxBuffer;
    length = testParams->dataCount / (testParams->wordLen / (uint16_t)8U);

    while ((0 != length) && (status == STW_SOK))
    {
        timeStart = DiagLibUtils_getCurTimeInMsec();
        do
        {
            if ((McSPIChannelStatusGet(testParams->baseAddr,
                            testParams->chNumber) & MCSPI_CH0STAT_TXS_MASK)
                            != 0U)
            {
                break;
            }
            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);

        } while(elapsedTime <= testParams->timeout);

        if(elapsedTime > testParams->timeout)
        {
            status = DIAGLIB_MCSPI_TEST_TIMEOUT;
        }

        if(status == STW_SOK)
        {
            McSPITransmitData(testParams->baseAddr, *p_tx,
                                            testParams->chNumber);
            timeStart = DiagLibUtils_getCurTimeInMsec();
            p_tx++;
            elapsedTime = 0U;

            do
            {
                if((McSPIChannelStatusGet(testParams->baseAddr,
                                testParams->chNumber) & MCSPI_CH0STAT_RXS_MASK)
                                != 0U)
                {
                    break;
                }
            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);
            } while(elapsedTime <= testParams->timeout);

            if(elapsedTime > testParams->timeout)
            {
                status = DIAGLIB_MCSPI_TEST_TIMEOUT;
            }
            else
            {
                *p_rx = McSPIReceiveData(testParams->baseAddr,
                                            testParams->chNumber);
                p_rx++;
            }
        }

        length--;
    }
    return status;
}

/*
** This function will verify the data written to and read from flash and print
** the appropriate message.
*/
static int32_t DiagLib_mcspiVerifyData(const DiagLib_McspiTestParams_t *testParams)
{
    int32_t status = STW_SOK;
    uint32_t index = 0;
    uint32_t mask = 0xFFFFFFFFU >> (32U - testParams->wordLen);
    uint32_t noBytes = testParams->wordLen / 8U;

    /* Write back from cache and invalidate cache to complete the transfer */
    if(testParams->performCacheOps == (uint32_t)TRUE)
    {
        BspOsal_cacheWbInvAll();
    }

    for (index = 0; index < (testParams->dataCount / noBytes); index++)
    {
        if ((testParams->rxBuffer[index] & mask) !=
                                    (testParams->txBuffer[index] & mask))
        {
            status = STW_EFAIL;
            break;
        }
    }

    return status;
}
