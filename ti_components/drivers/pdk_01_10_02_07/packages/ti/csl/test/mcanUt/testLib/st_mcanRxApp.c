/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \file     st_mcanNormalMode.c
 *
 *  \brief    This file contains mcan test code.
 *
 *  \details
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_mcan.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_mcan.h>
#include <st_mcan.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_MCAN_RX_MODULE_ADDR                         (DEF_MCAN_MODULE)

#define APP_MCAN_STD_ID_FILT_START_ADDR          (0U)
#define APP_MCAN_STD_ID_FILTER_NUM               (1U)
#define APP_MCAN_EXT_ID_FILT_START_ADDR          (48U)
#define APP_MCAN_EXT_ID_FILTER_NUM               (1U)
#define APP_MCAN_TX_EVENT_START_ADDR             (100U)
#define APP_MCAN_TX_EVENT_SIZE                   (5U)
#define APP_MCAN_TX_BUFF_START_ADDR              (148U)
#define APP_MCAN_TX_BUFF_SIZE                    (5U)
#define APP_MCAN_TX_FIFO_SIZE                    (5U)
#define APP_MCAN_FIFO_0_START_ADDR               (548U)
#define APP_MCAN_FIFO_0_NUM                      (5U)
#define APP_MCAN_FIFO_1_START_ADDR               (748U)
#define APP_MCAN_FIFO_1_NUM                      (5U)
#define APP_MCAN_RX_BUFF_START_ADDR              (948U)

#define APP_MCAN_EXT_ID_AND_MASK                 (0x1FFFFFFFU)

#define EDMA3_CC_REGION_M4                                (1U)
#ifdef __TI_ARM_V7M4__
    #define XBAR_CPU                          (CSL_XBAR_IRQ_CPU_ID_IPU1)
    /* DMA configuration related macros */
    #define EDMA3_CC_XFER_COMPLETION_INT       (38U)
    #define EDMA3_CC_REGION                    (EDMA3_CC_REGION_M4)
    #define XBAR_DMA_INST                      (CSL_XBAR_INST_IPU1_IRQ_38)
    #define XBAR_DMA_INTR_SOURCE               (CSL_XBAR_EDMA_TPCC_IRQ_REGION1)
#endif

#define APP_TX_SRC_ADDR                          (0x81000000U)
#define APP_RX_SRC_ADDR                          (0x81000000U)

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* MCAN Tx DMA Event */
    #define DMA_EVENT_SOURCE_TX                (CSL_XBAR_DMA_DCAN2_DREQ_IF1)
    /* MCAN Rx Filter Event */
    #define DMA_EVENT_SOURCE_RX                (CSL_XBAR_DMA_DCAN2_DREQ_IF2)
#elif defined (SOC_TDA2PX)
    /* MCAN Tx DMA Event */
    #define DMA_EVENT_SOURCE_TX                (CSL_XBAR_DMA_MCAN_DREQ_TX)
    /* MCAN Rx Filter Event */
    #define DMA_EVENT_SOURCE_RX                (CSL_XBAR_DMA_MCAN_DREQ_RX_FE1)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern uint32_t                mcanBaseAddr;
extern uint32_t                uartBaseAddr;
extern uint32_t          gMcanAppdataSize[16];
extern volatile uint32_t gMcanIsrIntr0Flag;
extern volatile uint32_t gMcanIsrIntr1Flag;
extern volatile uint32_t gMcanIsrIntr0Status;
extern volatile uint32_t gMcanIsrIntr1Status;
extern MCAN_ECCErrStatus gMcaneccErr;
extern MCAN_BitTimingParams canFDBitTimings[];
extern volatile uint32_t isrPrintEnable;

static volatile uint32_t edmaTransferComplete = 1U;
static uint32_t edmaEvtqNumber, edmaTCCNumber, edmaChannelNumber,
                  edmaInterruptNumber;
static uint32_t edmaEvtqNumberCh2, edmaTCCNumberCh2, edmaChannelNumberCh2;
static EDMA3CCPaRAMEntry edmaParam;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function will configure MCAN module
 *
 * \param   none.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanConfig(void);

/**
 * \brief   This function contains test code for DMA configuration for with MCAN Tx
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  none.
 */
static void DMATxConfigure(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This Interrupt Service Routine for EDMA completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppEdmaCompletionISR(void *handle);

int32_t st_mcanPerfRxApp_main(void);

extern int32_t mcanClockEnable(void);

extern int32_t mcanTestFunc(st_mcanTestcaseParams_t *testParams);

extern void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg);

extern void App_mcanPrintTxMsg(const MCAN_TxBufElement *txMsg);

extern int32_t App_mcanXBarConfig(void);

extern void App_mcanIntr0ISR(void *handle);

extern void App_mcanIntr1ISR(void *handle);

extern void App_mcanECCIntrISR(void *handle);

extern void App_mcanTSIntrISR(void *handle);

extern int32_t mcanClockEnableandPADConfig(void);

void st_mcanDMARxApp(st_mcanTestcaseParams_t *testParams);

extern void App_delayFunc(uint32_t timeout);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_mcanRxApp_main(void)
{
    uint32_t             loopCnt    = 1U, chkCnt = 0U;
    MCAN_RxBufElement    rxMsg;
    MCAN_TxBufElement    txMsg;
    MCAN_RxNewDataStatus newDataStatus;
    MCAN_ErrCntStatus    errCounter;
    int32_t              configStatus = STW_SOK, dataStatus = STW_SOK;
    int32_t              status = STW_SOK;
    volatile uint32_t runFlag = 1U;
    MCAN_ProtocolStatus protStatus;
    uint32_t    readBuffNum, bitPos, msgId;
    MCAN_RxFIFOStatus fifoStatus;

    isrPrintEnable = (uint32_t)TRUE;
    mcanBaseAddr = APP_MCAN_RX_MODULE_ADDR;
    status = mcanClockEnableandPADConfig();
    if(status != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Clock and PAD Configuration...");
    }
    configStatus += App_mcanXBarConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in X-Bar Configuration...");
    }

    configStatus += App_mcanConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Configuration...");
    }

    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_enableIntr(mcanBaseAddr,
                    MCAN_INTR_SRC_RES_ADDR_ACCESS, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_1);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        MCAN_INTR_LINE_NUM_1,
                        1U);
    loopCnt = 0U;

    memset(&rxMsg, 0, sizeof (rxMsg));

    while (runFlag)
    {
        while (gMcanIsrIntr1Flag)
        {}
        gMcanIsrIntr1Flag = 1U;
        /* Checking for Errors */
        MCAN_getErrCounters(mcanBaseAddr, &errCounter);
        if ((0U == errCounter.recErrCnt) &&
            (0U == errCounter.canErrLogCnt))
        {
            if((gMcanIsrIntr1Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                    MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
            {
                MCAN_getNewDataStatus(mcanBaseAddr, &newDataStatus);
                MCAN_clearNewDataStatus(mcanBaseAddr, &newDataStatus);
                for(readBuffNum = 0U ; readBuffNum < 64U ; readBuffNum++)
                {
                    if(readBuffNum < 32U)
                    {
                        dataStatus = newDataStatus.statusLow;
                        bitPos = 1U << readBuffNum;
                    }
                    else
                    {
                        dataStatus = newDataStatus.statusHigh;
                        bitPos = 1U << (readBuffNum - 32U);
                    }

                    if(bitPos == (dataStatus & bitPos))
                    {
                        MCAN_readMsgRam(mcanBaseAddr,
                                        MCAN_MEM_TYPE_BUF,
                                        readBuffNum,
                                        MCAN_RX_FIFO_NUM_0,
                                        &rxMsg);
                        loopCnt++;
                        UARTConfigPrintf(uartBaseAddr, "\nRx Buffer: Received (%dth) message with following details:", loopCnt);
                        App_mcanPrintRxMsg(&rxMsg);

                        /* Echo back the received message */
                        /* Copying Rx message into Tx message */
                        txMsg.id = rxMsg.id;
                        txMsg.rtr = rxMsg.rtr;
                        txMsg.xtd = rxMsg.xtd;
                        txMsg.esi = rxMsg.esi;
                        txMsg.dlc = rxMsg.dlc;
                        txMsg.brs = rxMsg.brs;
                        txMsg.fdf = rxMsg.fdf;
                        txMsg.efc = 0U;
                        txMsg.mm = 0xAAU;
                        for (chkCnt = 0U;
                             chkCnt < gMcanAppdataSize[rxMsg.dlc];
                             chkCnt++)
                        {
                            txMsg.data[chkCnt] = rxMsg.data[chkCnt];
                        }
                        /* Enable Transmission interrupt */
                        configStatus = MCAN_txBufTransIntrEnable(mcanBaseAddr,
                                                                 1U,
                                                                 (uint32_t)TRUE);
                        if(configStatus != STW_SOK)
                        {
                             UARTConfigPuts(uartBaseAddr, "\nError in enabling Transmission Interrupt...\n", -1);
                        }
                        /* Always writing to Tx Buffer number 0 for echoing back */
                        MCAN_writeMsgRam(mcanBaseAddr,
                                         MCAN_MEM_TYPE_BUF,
                                         1U,
                                         (const MCAN_TxBufElement*) &txMsg);
                        /* Add request for transmission */
                        configStatus += MCAN_txBufAddReq(mcanBaseAddr, 1U);
                        if (STW_SOK != configStatus)
                        {
                            UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
                        }
                        while (gMcanIsrIntr1Flag)
                        {
                            if (MCAN_INTR_SRC_TRANS_COMPLETE ==
                                (gMcanIsrIntr1Status & MCAN_INTR_SRC_TRANS_COMPLETE))
                            {
                                break;
                            }
                            gMcanIsrIntr1Flag = 1U;
                        }
                        gMcanIsrIntr1Flag = 1U;
                        MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                        /* Checking for Errors */
                        if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                             (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                            ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                             (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                            (0U == protStatus.pxe))
                        {
                            UARTConfigPrintf(uartBaseAddr, 
                                "\n(%dth) Message successfully transferred.\n",
                                loopCnt);
                        }
                        else
                        {
                            UARTConfigPrintf(uartBaseAddr, "\nError in transmission (%dth) message.\n",
                                       loopCnt);
                        }
                    }
                }
            }
            else if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                            MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
                ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                            MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
            {
                readBuffNum = 0U;
                loopCnt++;
                if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                            MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
                {
                    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
                    UARTConfigPrintf(uartBaseAddr, "\nRx FIFO 0: Received (%dth) message with following details:", loopCnt);

                }
                else
                {
                    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
                    UARTConfigPrintf(uartBaseAddr, "\nRx FIFO 1: Received (%dth) message with following details:", loopCnt);
                }
                MCAN_getRxFIFOStatus(mcanBaseAddr, &fifoStatus);
                MCAN_readMsgRam(mcanBaseAddr,
                                MCAN_MEM_TYPE_FIFO,
                                fifoStatus.getIdx,
                                (uint32_t)fifoStatus.num,
                                &rxMsg);
                (void) MCAN_writeRxFIFOAck(mcanBaseAddr,
                                           (uint32_t)fifoStatus.num,
                                           fifoStatus.getIdx);
                App_mcanPrintRxMsg(&rxMsg);

                /* Echo back the received message */
                /* Copying Rx message into Tx message */
                txMsg.id = rxMsg.id;
                txMsg.rtr = rxMsg.rtr;
                txMsg.xtd = rxMsg.xtd;
                txMsg.esi = rxMsg.esi;
                txMsg.dlc = rxMsg.dlc;
                txMsg.brs = rxMsg.brs;
                txMsg.fdf = rxMsg.fdf;
                txMsg.efc = 0U;
                txMsg.mm = 0xAAU;
                for (chkCnt = 0U;
                     chkCnt < gMcanAppdataSize[rxMsg.dlc];
                     chkCnt++)
                {
                    txMsg.data[chkCnt] = rxMsg.data[chkCnt];
                }
                /* Enable Transmission interrupt */
                configStatus = MCAN_txBufTransIntrEnable(mcanBaseAddr,
                                                         1U,
                                                         (uint32_t)TRUE);
                if(configStatus != STW_SOK)
                {
                     UARTConfigPuts(uartBaseAddr, "\nError in enabling Transmission Interrupt...\n", -1);
                }
                /* Always writing to Tx Buffer number 0 for echoing back */
                MCAN_writeMsgRam(mcanBaseAddr,
                                 MCAN_MEM_TYPE_BUF,
                                 1U,
                                 (const MCAN_TxBufElement*) &txMsg);
                /* Add request for transmission */
                configStatus += MCAN_txBufAddReq(mcanBaseAddr, 1U);
                if (STW_SOK != configStatus)
                {
                    UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
                }
                while (gMcanIsrIntr1Flag)
                {
                    if (MCAN_INTR_SRC_TRANS_COMPLETE ==
                        (gMcanIsrIntr1Status & MCAN_INTR_SRC_TRANS_COMPLETE))
                    {
                        break;
                    }
                }
                gMcanIsrIntr1Flag = 1U;
                MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                    UARTConfigPrintf(uartBaseAddr, 
                        "\n(%dth) Message successfully transferred.\n",
                        loopCnt);
                }
                else
                {
                    UARTConfigPrintf(uartBaseAddr, "\nError in transmission (%dth) message.\n",
                               loopCnt);
                }
            }
            else
            {
                status = STW_EFAIL;
            }
            if(STW_SOK == status)
            {
                /* Change baud-rate from default */
                msgId = ((rxMsg.id >> 18) & 0x7FF);
                if ((msgId == 0x44) && (rxMsg.xtd == 0U))
                {
                    /* Put MCAN in SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
                    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
                    {}
                    /* Change baud-rate */
                    MCAN_setBitTime(mcanBaseAddr, (const MCAN_BitTimingParams *)&canFDBitTimings[rxMsg.data[0U]]);
                    /* Take MCAN out of the SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
                    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
                    {}
                }
                /* Change baud-rate to default */
                if ((msgId == 0x16) && (rxMsg.xtd == 0U))
                {
                    /* Put MCAN in SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
                    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
                    {}
                    /* Change baud-rate */
                    MCAN_setBitTime(mcanBaseAddr, (const MCAN_BitTimingParams *)&canFDBitTimings[0U]);
                    /* Take MCAN out of the SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
                    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
                    {}
                }
            }
        }
        else
        {
        }
        gMcanIsrIntr1Status = 0U;
    }
    return 0;
}


int32_t st_mcanPerfRxApp_main(void)
{
    uint32_t             loopCnt    = 1U, chkCnt = 0U;
    MCAN_RxBufElement    rxMsg;
    MCAN_TxBufElement    txMsg;
    MCAN_RxNewDataStatus newDataStatus;
    MCAN_ErrCntStatus    errCounter;
    int32_t              configStatus = STW_SOK, status = STW_SOK;
    volatile uint32_t runFlag = 1U;
    MCAN_ProtocolStatus protStatus;
    uint32_t    readBuffNum, bitPos, dataStatus, msgId;
    MCAN_RxFIFOStatus fifoStatus;

    isrPrintEnable = (uint32_t)FALSE;
    mcanBaseAddr = APP_MCAN_RX_MODULE_ADDR;
    status = mcanClockEnableandPADConfig();
    if(status != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Clock and PAD Configuration...");
    }
    configStatus += App_mcanXBarConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in X-Bar Configuration...");
    }

    configStatus += App_mcanConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Configuration...");
    }

    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_enableIntr(mcanBaseAddr,
                    MCAN_INTR_SRC_RES_ADDR_ACCESS, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_1);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        MCAN_INTR_LINE_NUM_1,
                        1U);
    loopCnt = 0U;

    memset(&rxMsg, 0, sizeof (rxMsg));

    while (runFlag)
    {
        while (gMcanIsrIntr1Flag)
        {}
        gMcanIsrIntr1Flag = 1U;
        /* Checking for Errors */
        MCAN_getErrCounters(mcanBaseAddr, &errCounter);
        if ((0U == errCounter.recErrCnt) &&
            (0U == errCounter.canErrLogCnt))
        {
            if((gMcanIsrIntr1Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                    MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
            {
                MCAN_getNewDataStatus(mcanBaseAddr, &newDataStatus);
                MCAN_clearNewDataStatus(mcanBaseAddr, &newDataStatus);
                for(readBuffNum = 0U ; readBuffNum < 64U ; readBuffNum++)
                {
                    if(readBuffNum < 32U)
                    {
                        dataStatus = newDataStatus.statusLow;
                        bitPos = 1U << readBuffNum;
                    }
                    else
                    {
                        dataStatus = newDataStatus.statusHigh;
                        bitPos = 1U << (readBuffNum - 32U);
                    }

                    if(bitPos == (dataStatus & bitPos))
                    {
                        MCAN_readMsgRam(mcanBaseAddr,
                                        MCAN_MEM_TYPE_BUF,
                                        readBuffNum,
                                        MCAN_RX_FIFO_NUM_0,
                                        &rxMsg);
                        loopCnt++;

                        /* Echo back the received message */
                        /* Copying Rx message into Tx message */
                        txMsg.id = rxMsg.id;
                        txMsg.rtr = rxMsg.rtr;
                        txMsg.xtd = rxMsg.xtd;
                        txMsg.esi = rxMsg.esi;
                        txMsg.dlc = rxMsg.dlc;
                        txMsg.brs = rxMsg.brs;
                        txMsg.fdf = rxMsg.fdf;
                        txMsg.efc = 0U;
                        txMsg.mm = 0xAAU;
                        for (chkCnt = 0U;
                             chkCnt < gMcanAppdataSize[rxMsg.dlc];
                             chkCnt++)
                        {
                            txMsg.data[chkCnt] = rxMsg.data[chkCnt];
                        }
                        /* Enable Transmission interrupt */
                        configStatus = MCAN_txBufTransIntrEnable(mcanBaseAddr,
                                                                 1U,
                                                                 (uint32_t)TRUE);
                        if(configStatus != STW_SOK)
                        {
                             UARTConfigPuts(uartBaseAddr, "\nError in enabling Transmission Interrupt...\n", -1);
                        }
                        /* Always writing to Tx Buffer number 0 for echoing back */
                        MCAN_writeMsgRam(mcanBaseAddr,
                                         MCAN_MEM_TYPE_BUF,
                                         1U,
                                         (const MCAN_TxBufElement*) &txMsg);
                        /* Add request for transmission */
                        configStatus += MCAN_txBufAddReq(mcanBaseAddr, 1U);
                        if (STW_SOK != configStatus)
                        {
                            UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
                        }
                        while (gMcanIsrIntr1Flag)
                        {
                            if (MCAN_INTR_SRC_TRANS_COMPLETE ==
                                (gMcanIsrIntr1Status & MCAN_INTR_SRC_TRANS_COMPLETE))
                            {
                                break;
                            }
                            gMcanIsrIntr1Flag = 1U;
                        }
                        gMcanIsrIntr1Flag = 1U;
                        MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                        /* Checking for Errors */
                        if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                             (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                            ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                             (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                            (0U == protStatus.pxe))
                        {
                        }
                        else
                        {
                            UARTConfigPrintf(uartBaseAddr, "\nError in transmission (%dth) message.\n",
                                       loopCnt);
                        }
                    }
                }
            }
            else if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                            MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
                ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                            MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
            {
                readBuffNum = 0U;
                loopCnt++;
                if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                            MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
                {
                    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;

                }
                else
                {
                    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
                }
                MCAN_getRxFIFOStatus(mcanBaseAddr, &fifoStatus);
                MCAN_readMsgRam(mcanBaseAddr,
                                MCAN_MEM_TYPE_FIFO,
                                fifoStatus.getIdx,
                                (uint32_t)fifoStatus.num,
                                &rxMsg);
                (void) MCAN_writeRxFIFOAck(mcanBaseAddr,
                                           (uint32_t)fifoStatus.num,
                                           fifoStatus.getIdx);
                App_mcanPrintRxMsg(&rxMsg);

                /* Echo back the received message */
                /* Copying Rx message into Tx message */
                txMsg.id = rxMsg.id;
                txMsg.rtr = rxMsg.rtr;
                txMsg.xtd = rxMsg.xtd;
                txMsg.esi = rxMsg.esi;
                txMsg.dlc = rxMsg.dlc;
                txMsg.brs = rxMsg.brs;
                txMsg.fdf = rxMsg.fdf;
                txMsg.efc = 0U;
                txMsg.mm = 0xAAU;
                for (chkCnt = 0U;
                     chkCnt < gMcanAppdataSize[rxMsg.dlc];
                     chkCnt++)
                {
                    txMsg.data[chkCnt] = rxMsg.data[chkCnt];
                }
                /* Enable Transmission interrupt */
                configStatus = MCAN_txBufTransIntrEnable(mcanBaseAddr,
                                                         1U,
                                                         (uint32_t)TRUE);
                if(configStatus != STW_SOK)
                {
                     UARTConfigPuts(uartBaseAddr, "\nError in enabling Transmission Interrupt...\n", -1);
                }
                /* Always writing to Tx Buffer number 0 for echoing back */
                MCAN_writeMsgRam(mcanBaseAddr,
                                 MCAN_MEM_TYPE_BUF,
                                 1U,
                                 (const MCAN_TxBufElement*) &txMsg);
                /* Add request for transmission */
                configStatus += MCAN_txBufAddReq(mcanBaseAddr, 1U);
                if (STW_SOK != configStatus)
                {
                    UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
                }
                while (gMcanIsrIntr1Flag)
                {
                    if (MCAN_INTR_SRC_TRANS_COMPLETE ==
                        (gMcanIsrIntr1Status & MCAN_INTR_SRC_TRANS_COMPLETE))
                    {
                        break;
                    }
                }
                gMcanIsrIntr1Flag = 1U;
                MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                }
                else
                {
                    UARTConfigPrintf(uartBaseAddr, "\nError in transmission (%dth) message.\n",
                               loopCnt);
                }
            }
            else
            {
                status = STW_EFAIL;
            }
            if(STW_SOK != status)
            {
                /* Change baud-rate from default */
                msgId = ((rxMsg.id >> 18) & 0x7FF);
                if ((msgId == 0x44) && (rxMsg.xtd == 0U))
                {
                    /* Put MCAN in SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
                    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
                    {}
                    /* Change baud-rate */
                    MCAN_setBitTime(mcanBaseAddr, (const MCAN_BitTimingParams *)&canFDBitTimings[rxMsg.data[0U]]);
                    /* Take MCAN out of the SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
                    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
                    {}
                }
                /* Change baud-rate to default */
                if ((msgId == 0x16) && (rxMsg.xtd == 0U))
                {
                    /* Put MCAN in SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
                    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
                    {}
                    /* Change baud-rate */
                    MCAN_setBitTime(mcanBaseAddr, (const MCAN_BitTimingParams *)&canFDBitTimings[0U]);
                    /* Take MCAN out of the SW initialization mode */
                    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
                    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
                    {}
                }
            }
        }
        else
        {
        }
        gMcanIsrIntr1Status = 0U;
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static int32_t App_mcanConfig(void)
{
    uint32_t                   fdoe;
    int32_t                    configStatus = STW_SOK;
    MCAN_RevisionId            revId;
    MCAN_InitParams            initParams;
    MCAN_ConfigParams          configParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_StdMsgIDFilterElement stdFiltelem;
    MCAN_BitTimingParams       bitTimes;

    /* Initialize MCAN Init params */
    initParams.fdMode          = 0x1U;
    initParams.brsEnable       = 0x1U;
    initParams.txpEnable       = 0x0U;
    initParams.efbi            = 0x0U;
    initParams.pxhddisable     = 0x0U;
    initParams.darEnable       = 0x1U;
    initParams.wkupReqEnable   = 0x1U;
    initParams.autoWkupEnable  = 0x1U;
    initParams.emulationEnable = 0x1U;
    initParams.emulationFAck   = 0x0U;
    initParams.clkStopFAck     = 0x0U;
    initParams.wdcPreload      = 0xFFU;
    initParams.tdcEnable       = 0x1U;
    initParams.tdcConfig.tdcf  = 0xAU;
    initParams.tdcConfig.tdco  = 0x6U;
    /* Initialize MCAN Config params */
    configParams.monEnable         = 0x0U;
    configParams.asmEnable         = 0x0U;
    configParams.tsPrescalar       = 0xFU;
    configParams.tsSelect          = 0x0U;
    configParams.timeoutSelect     = MCAN_TIMEOUT_SELECT_CONT;
    configParams.timeoutPreload    = 0xFFFFU;
    configParams.timeoutCntEnable  = 0x0U;
    configParams.filterConfig.rrfs = 0x1U;
    configParams.filterConfig.rrfe = 0x1U;
    configParams.filterConfig.anfe = 0x1U;
    configParams.filterConfig.anfs = 0x1U;
    /* Initialize Message RAM Sections Configuration Parameters */
    msgRAMConfigParams.flssa                = APP_MCAN_STD_ID_FILT_START_ADDR;
    msgRAMConfigParams.lss                  = APP_MCAN_STD_ID_FILTER_NUM;
    msgRAMConfigParams.flesa                = APP_MCAN_EXT_ID_FILT_START_ADDR;
    msgRAMConfigParams.lse                  = APP_MCAN_EXT_ID_FILTER_NUM;
    msgRAMConfigParams.txStartAddr          = APP_MCAN_TX_BUFF_START_ADDR;
    msgRAMConfigParams.txBufNum             = APP_MCAN_TX_BUFF_SIZE;
    msgRAMConfigParams.txFIFOSize           = 0U;
    msgRAMConfigParams.txBufMode            = 0U;
    msgRAMConfigParams.txBufElemSize        = MCAN_ELEM_SIZE_64BYTES;
    msgRAMConfigParams.txEventFIFOStartAddr = APP_MCAN_TX_EVENT_START_ADDR;
    msgRAMConfigParams.txEventFIFOSize      = APP_MCAN_TX_BUFF_SIZE;
    msgRAMConfigParams.txEventFIFOWaterMark = 3U;
    msgRAMConfigParams.rxFIFO0startAddr     = APP_MCAN_FIFO_0_START_ADDR;
    msgRAMConfigParams.rxFIFO0size          = APP_MCAN_FIFO_0_NUM;
    msgRAMConfigParams.rxFIFO0waterMark     = 3U;
    msgRAMConfigParams.rxFIFO0OpMode        = 0U;
    msgRAMConfigParams.rxFIFO1startAddr     = APP_MCAN_FIFO_1_START_ADDR;
    msgRAMConfigParams.rxFIFO1size          = APP_MCAN_FIFO_1_NUM;
    msgRAMConfigParams.rxFIFO1waterMark     = 3U;
    msgRAMConfigParams.rxFIFO1OpMode        = 0U;
    msgRAMConfigParams.rxBufStartAddr       = APP_MCAN_RX_BUFF_START_ADDR;
    msgRAMConfigParams.rxBufElemSize        = MCAN_ELEM_SIZE_64BYTES;
    msgRAMConfigParams.rxFIFO0ElemSize      = MCAN_ELEM_SIZE_64BYTES;
    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_ELEM_SIZE_64BYTES;
    /* Initialize Tx Buffer Config params */
    stdFiltelem.sfid2 = (0x7U << 6U);
    stdFiltelem.sfid1 = 0x4U;
    stdFiltelem.sfec  = 0x7U;
    stdFiltelem.sft   = 0x0U;
    /* Initialize bit timings
     * Configuring 1Mbps and 5Mbps as nominal and data bit-rate respectively */
    bitTimes.nomRatePrescalar   = 0x7U;
    bitTimes.nomTimeSeg1        = 0x5U;
    bitTimes.nomTimeSeg2        = 0x2U;
    bitTimes.nomSynchJumpWidth  = 0x0U;
    bitTimes.dataRatePrescalar  = 0x1U;
    bitTimes.dataTimeSeg1       = 0x3U;
    bitTimes.dataTimeSeg2       = 0x2U;
    bitTimes.dataSynchJumpWidth = 0x0U;

    /* Get MCANSS Revision ID */
    MCAN_getRevisionId(mcanBaseAddr, &revId);
    UARTConfigPrintf(uartBaseAddr, "MCANSS Revision ID:\n");
    UARTConfigPrintf(uartBaseAddr, "scheme:0x%x\n", revId.scheme);
    UARTConfigPrintf(uartBaseAddr, "Business Unit:0x%x\n", revId.bu);
    UARTConfigPrintf(uartBaseAddr, "Module ID:0x%x\n", revId.modId);
    UARTConfigPrintf(uartBaseAddr, "RTL Revision:0x%x\n", revId.rtlRev);
    UARTConfigPrintf(uartBaseAddr, "Major Revision:0x%x\n", revId.major);
    UARTConfigPrintf(uartBaseAddr, "Custom Revision:0x%x\n", revId.custom);
    UARTConfigPrintf(uartBaseAddr, "Minor Revision:0x%x\n", revId.minor);
    /* Enable Auto wakeup */
    fdoe = MCAN_isFDOpEnable(mcanBaseAddr);
    if ((uint32_t)TRUE == fdoe)
    {
        UARTConfigPrintf(uartBaseAddr, "CAN-FD operation is enabled through E-Fuse.\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "CAN-FD operation is disabled through E-Fuse.\n");
    }
    /* wait for memory initialization to happen */
    while (FALSE == MCAN_isMemInitDone(mcanBaseAddr))
    {}
    /* Get endianess value */
    UARTConfigPrintf(uartBaseAddr, "Endianess Value: 0x%x\n", MCAN_getEndianVal(mcanBaseAddr));
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
    {}
    /* Initialize MCAN module */
    MCAN_init(mcanBaseAddr, &initParams);
    /* Configure MCAN module */
    MCAN_config(mcanBaseAddr, &configParams);
    /* Configure Bit timings */
    MCAN_setBitTime(mcanBaseAddr, &bitTimes);
    /* Set Extended ID Mask */
    MCAN_setExtIDAndMask(mcanBaseAddr, APP_MCAN_EXT_ID_AND_MASK);
    /* Configure Message RAM Sections */
    MCAN_msgRAMConfig(mcanBaseAddr, &msgRAMConfigParams);
    /* Configure Standard ID filter element */
    MCAN_addStdMsgIDFilter(mcanBaseAddr, 0U, &stdFiltelem);
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
    {}
    return configStatus;
}

static void AppEdmaCompletionISR(void *handle)
{
    edmaTransferComplete = 0U;
    //MCAN_txBuffAddReq(APP_MCAN_MODULE, 0U);
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTCCNumber);
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTCCNumberCh2);
}

static void DMATxConfigure(st_mcanTestcaseParams_t *testParams)
{
    uint32_t edmaRegion, destAddr;
    uint32_t buffAddReqMem = 0x82000000;
    uint32_t          chain_param =
        (EDMA3_OPT_TCCHEN_MASK |
         EDMA3_OPT_ITCCHEN_MASK |
         EDMA3_OPT_TCINTEN_MASK);

    /* Enable TPTC1 Clocks */
    HW_WR_REG32(0x4a008778, 0x1U);
    edmaRegion = EDMA3_CC_REGION;
    EDMAsetRegion(edmaRegion);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
    edmaInterruptNumber = EDMA3_CC_XFER_COMPLETION_INT;
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_DMA_INST, XBAR_DMA_INTR_SOURCE);
    {
        /* Successfully configured CrossBar */
        Intc_Init();
        Intc_IntEnable(edmaInterruptNumber);
        Intc_IntRegister(edmaInterruptNumber, (IntrFuncPtr) AppEdmaCompletionISR,
                         0);
        Intc_IntPrioritySet(edmaInterruptNumber, 1, 0);
        Intc_SystemEnable(edmaInterruptNumber);
    }
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    destAddr = (uint32_t) mcanBaseAddr +
                         (uint32_t) testParams->mcanConfigParams.ramConfig->txStartAddr;
#elif defined (SOC_TDA2PX)
    /* For J6P, MCAN address is a virtual address which needs to be converted
       physical address for DMA
    */
    destAddr = (uint32_t) mcanBaseAddr +
                         (uint32_t) testParams->mcanConfigParams.ramConfig->txStartAddr;
    destAddr -= 0x20000000U;
#endif
    /* Configure EDMA parameters */
    edmaChannelNumber  = 16U;
    edmaEvtqNumber     = 0x0U;
    edmaTCCNumber      = 16U;
    edmaChannelNumberCh2  = 0x2U;
    edmaEvtqNumberCh2     = 0x0U;
    edmaTCCNumberCh2      = 0x2U;
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t) APP_TX_SRC_ADDR;
    edmaParam.destAddr = destAddr;
    /* Supporting only fill CAN FD message:64bytes data and 8 bytes header */
    edmaParam.aCnt     = (uint32_t) (72U);
    edmaParam.bCnt     = testParams->mcanConfigParams.txMSGInterationCnt;
    edmaParam.cCnt     = 1U;
    edmaParam.srcBIdx  = edmaParam.aCnt;
    edmaParam.destBIdx = 0U;
    edmaParam.srcCIdx  = 0U;
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
   edmaParam.opt     |=
        (
         ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    /* Configure EDMA */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumber,
                        edmaTCCNumber,
                        edmaEvtqNumber);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);
    /* Configure the MCAN TX event. */
    CSL_xbarDmaConfigure(CSL_XBAR_DMA_CPU_ID_EDMA,
                   (edmaChannelNumber + 1),
                   DMA_EVENT_SOURCE_TX);
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    destAddr = (uint32_t) mcanBaseAddr + (uint32_t) MCAN_TXBAR;
#elif defined (SOC_TDA2PX)
    /* For J6P, MCAN address is a virtual address which needs to be converted
       physical address for DMA
    */
    destAddr = (uint32_t) mcanBaseAddr + (uint32_t) MCAN_TXBAR;
    destAddr -= 0x20000000U;
#endif
    /* Configure EDMA parameters */
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  =  buffAddReqMem;
    edmaParam.destAddr = destAddr;
    edmaParam.aCnt     = 4U;
    edmaParam.bCnt     = testParams->mcanConfigParams.txMSGInterationCnt;
    edmaParam.cCnt     = 1U;
    edmaParam.srcBIdx  = 0U;
    edmaParam.destBIdx = 0U;
    edmaParam.srcCIdx  = 0U;
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA3_OPT_TCINTEN_MASK |
        ((edmaTCCNumberCh2 << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumberCh2,
                        edmaTCCNumberCh2,
                        edmaEvtqNumberCh2);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumberCh2, &edmaParam);
    /*Set params for chain transfer. Chain two channels*/
    EDMA3ChainChannel(SOC_EDMA_TPCC_BASE_VIRT,
                      edmaChannelNumber,
                      edmaChannelNumberCh2,
                      chain_param);
}

static void DMARxConfigure(st_mcanTestcaseParams_t *testParams)
{
    uint32_t edmaRegion, srcAddr;
    uint32_t buffAddReqMem = 0x82000040;
    uint32_t          chain_param =
        (EDMA3_OPT_TCCHEN_MASK |
         EDMA3_OPT_ITCCHEN_MASK |
         EDMA3_OPT_TCINTEN_MASK);

    /* Enable TPTC1 Clocks */
    HW_WR_REG32(0x4a008778, 0x1U);
    edmaRegion = EDMA3_CC_REGION;
    EDMAsetRegion(edmaRegion);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
    edmaInterruptNumber = EDMA3_CC_XFER_COMPLETION_INT;
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_DMA_INST, XBAR_DMA_INTR_SOURCE);
    {
        /* Successfully configured CrossBar */
        Intc_Init();
        Intc_IntEnable(edmaInterruptNumber);
        Intc_IntRegister(edmaInterruptNumber, (IntrFuncPtr) AppEdmaCompletionISR,
                         0);
        Intc_IntPrioritySet(edmaInterruptNumber, 1, 0);
        Intc_SystemEnable(edmaInterruptNumber);
    }
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    srcAddr = (uint32_t) mcanBaseAddr +
                         (uint32_t) testParams->mcanConfigParams.ramConfig->rxBufStartAddr;
#elif defined (SOC_TDA2PX)
    /* For J6P, MCAN address is a virtual address which needs to be converted
       physical address for DMA
    */
    srcAddr = (uint32_t) mcanBaseAddr +
                         (uint32_t) testParams->mcanConfigParams.ramConfig->rxBufStartAddr;
    srcAddr -= 0x20000000U;
#endif
    /* Configure EDMA parameters */
    edmaChannelNumber  = 17U;
    edmaEvtqNumber     = 0x0U;
    edmaTCCNumber      = 17U;
    edmaChannelNumberCh2  = 0x3U;
    edmaEvtqNumberCh2     = 0x0U;
    edmaTCCNumberCh2      = 0x3U;
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = srcAddr;
    edmaParam.destAddr = (uint32_t) APP_RX_SRC_ADDR;
    edmaParam.aCnt     = (uint32_t) (72U);
    edmaParam.bCnt     = testParams->mcanConfigParams.txMSGInterationCnt;
    edmaParam.cCnt     = 1U;
    edmaParam.srcBIdx  = 0U;
    edmaParam.destBIdx = edmaParam.aCnt;
    edmaParam.srcCIdx  = 0U;
    edmaParam.destCIdx = edmaParam.aCnt * edmaParam.bCnt;
    edmaParam.linkAddr = 0xFFFFU;
   edmaParam.opt     |=
        (
         ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    /* Configure EDMA */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumber,
                        edmaTCCNumber,
                        edmaEvtqNumber);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);
    /* Configure the MCAN TX event. */
    CSL_xbarDmaConfigure(CSL_XBAR_DMA_CPU_ID_EDMA,
                   (edmaChannelNumber + 1),
                   DMA_EVENT_SOURCE_RX);
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    srcAddr = (uint32_t) mcanBaseAddr + (uint32_t) MCAN_NDAT1;
#elif defined (SOC_TDA2PX)
    /* For J6P, MCAN address is a virtual address which needs to be converted
       physical address for DMA
    */
    srcAddr = (uint32_t) mcanBaseAddr + (uint32_t) MCAN_NDAT1;
    srcAddr -= 0x20000000U;
#endif
    /* Configure EDMA parameters */
    edmaParam.opt      = 0U;
    edmaParam.srcAddr =  buffAddReqMem;
    edmaParam.destAddr  = srcAddr;
    edmaParam.aCnt     = 4U;
    edmaParam.bCnt     = testParams->mcanConfigParams.txMSGInterationCnt;
    edmaParam.cCnt     = 1U;
    edmaParam.srcBIdx  = 0U;
    edmaParam.destBIdx = 0U;
    edmaParam.srcCIdx  = 0U;
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA3_OPT_TCINTEN_MASK |
        ((edmaTCCNumberCh2 << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumberCh2,
                        edmaTCCNumberCh2,
                        edmaEvtqNumberCh2);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumberCh2, &edmaParam);
    /*Set params for chain transfer. Chain two channels*/
    EDMA3ChainChannel(SOC_EDMA_TPCC_BASE_VIRT,
                      edmaChannelNumber,
                      edmaChannelNumberCh2,
                      chain_param);
}


void st_mcanDMARxApp(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = STW_SOK, configStatus = STW_SOK;

    isrPrintEnable = (uint32_t)TRUE;
    mcanBaseAddr = APP_MCAN_RX_MODULE_ADDR;
    status = mcanClockEnableandPADConfig();
    if(status != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Clock and PAD Configuration...");
    }
    configStatus += App_mcanXBarConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in X-Bar Configuration...");
    }

    configStatus += App_mcanConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Configuration...");
    }

    UARTConfigPrintf(uartBaseAddr, "\nDMA Rx Side Test Application\n");
    HW_WR_REG32(0x82000000, 0x1U);
    HW_WR_REG32(0x82000040, 0x1U);
    UARTConfigPrintf(uartBaseAddr, "\nReceiving Data:\n");
    DMARxConfigure(testParams);

    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                        edmaChannelNumber,
                        EDMA3_TRIG_MODE_EVENT);
    while(edmaTransferComplete)
    {
    }
    edmaTransferComplete = 1U;
    App_delayFunc(1000U);
    UARTConfigPrintf(uartBaseAddr, "\nSending Data:\n");
    DMATxConfigure(testParams);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                        edmaChannelNumber,
                        EDMA3_TRIG_MODE_EVENT);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                        edmaChannelNumber,
                        EDMA3_TRIG_MODE_MANUAL);

    while(edmaTransferComplete)
    {
    }
}
