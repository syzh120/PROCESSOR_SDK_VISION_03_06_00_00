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
 *  \details  mcan operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_mcan.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_mcan.h>
#include <st_mcan.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_MCAN_STD_ID_MASK              (0x7FFU << 18U)
#define APP_MCAN_EXT_ID_MASK              (0x1FFFFFFFU)

/**
 * \brief  Mask and shift for Tx Buffers elements.
 */
#define MCANSS_TX_BUFFER_ELEM_ID_SHIFT                           (0U)
#define MCANSS_TX_BUFFER_ELEM_ID_MASK                            (0x1FFFFFFFU)
#define MCANSS_TX_BUFFER_ELEM_RTR_SHIFT                          (29U)
#define MCANSS_TX_BUFFER_ELEM_RTR_MASK                           (0x20000000U)
#define MCANSS_TX_BUFFER_ELEM_XTD_SHIFT                          (30U)
#define MCANSS_TX_BUFFER_ELEM_XTD_MASK                           (0x40000000U)
#define MCANSS_TX_BUFFER_ELEM_ESI_SHIFT                          (31U)
#define MCANSS_TX_BUFFER_ELEM_ESI_MASK                           (0x80000000U)
#define MCANSS_TX_BUFFER_ELEM_DLC_SHIFT                          (16U)
#define MCANSS_TX_BUFFER_ELEM_DLC_MASK                           (0x000F0000U)
#define MCANSS_TX_BUFFER_ELEM_BRS_SHIFT                          (20U)
#define MCANSS_TX_BUFFER_ELEM_BRS_MASK                           (0x00100000U)
#define MCANSS_TX_BUFFER_ELEM_FDF_SHIFT                          (21U)
#define MCANSS_TX_BUFFER_ELEM_FDF_MASK                           (0x00200000U)
#define MCANSS_TX_BUFFER_ELEM_EFC_SHIFT                          (23U)
#define MCANSS_TX_BUFFER_ELEM_EFC_MASK                           (0x00800000U)
#define MCANSS_TX_BUFFER_ELEM_MM_SHIFT                           (24U)
#define MCANSS_TX_BUFFER_ELEM_MM_MASK                            (0xFF000000U)


#define EDMA3_CC_REGION_M4                                (1U)
#ifdef __TI_ARM_V7M4__
    #define XBAR_CPU                          (CSL_XBAR_IRQ_CPU_ID_IPU1)
    /* DMA configuration related macros */
    #define EDMA3_CC_XFER_COMPLETION_INT       (38U)
    #define EDMA3_CC_REGION                    (EDMA3_CC_REGION_M4)
    #define XBAR_DMA_INST                      (CSL_XBAR_INST_IPU1_IRQ_38)
    #define XBAR_DMA_INTR_SOURCE               (CSL_XBAR_EDMA_TPCC_IRQ_REGION1)
#endif

#define APP_TX_SRC_ADDR                          (0x80000000U)
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
extern volatile uint32_t gMcanECCIntrFlag;
extern MCAN_ECCErrStatus gMcaneccErr;
extern volatile uint32_t gMcanIsrIntr0Status;
extern volatile uint32_t gMcanIsrIntr1Status;
extern volatile uint32_t gMcanExtTSIntrFlag;
extern MCAN_BitTimingParams canFDBitTimings[];
volatile uint32_t    rxBuffNum;
extern uint32_t autoRunEnable;
volatile uint32_t isrPrintEnable = (uint32_t)TRUE;
uint32_t objSize[8] = {4, 5, 6, 7, 8, 10, 14, 18};
uint32_t dataSize[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

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
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanConfig(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains MCAN Tx Test
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanTxTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains MCAN Tx Test for performance test
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
int32_t App_mcanPerfTxTest(st_mcanTestcaseParams_t *testParams);


/**
 * \brief   This function will check TC pass/fail criteria apart from Tx/Rx
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanCheckTCResultsMisc(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will check received message against transferred.
 *
 * \param   txMsg       Tx Message.
 * \param   rxMsg       Rx Message.
 *
 * \retval  status      Check status.
 */
static int32_t App_mcanTxRxMessageCheck(MCAN_TxBufElement txMsg,
                                        MCAN_RxBufElement rxMsg);

/**
 * \brief   This function will check received message against transferred.
 *
 * \param   rxMsg       Read Rx Message.
 * \param   status      Interrupt Status.
 *
 * \retval  status      Check status.
 */
static int32_t App_mcanReadRxMSG(MCAN_RxBufElement *rxMsg,
                                 uint32_t status);

/**
 * \brief   This function will configure receiver or other things depending on
 *          TC parameters.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanTCEntrySetup(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will configure receiver or other things for next TC.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanTCExitSetup(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will send a message to change the receiver side
 *          application baud-rate.
 *
 * \param   idx         'canFDBitTimings' array index.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanChangeBaudrateMSG(uint32_t idx);

/**
 * \brief   This function will check transmitted message against Tx Event Entry.
 *
 * \param   txMsg       Tx Message.
 * \param   rxMsg       Tx Event Message.
 *
 * \retval  status      Check status.
 */
static int32_t App_mcanTxEventMessageCheck(MCAN_TxBufElement txMsg,
                                           MCAN_TxEventFIFOElement txEventMsg);

/**
 * \brief   This function contains MCAN ECC Test
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanECCTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains code for MCAN ECC Self Test/Diagnostic mode
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanECCSelfTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function used CAN message to DDR. CAN be used for any memory.
 *
 * \param   addr            Address where message to be written.
 * \param   elem            Tx Element.
 *
 * \retval  none.
 */
static void App_mcanWriteDDR(uint32_t addr, const MCAN_TxBufElement *elem);

/**
 * \brief   This function contains test code for DMA usage with MCAN
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanDMATest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for DMA configuration for with MCAN Rx
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  none.
 */
static void DMARxConfigure(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for DMA configuration for with MCAN Tx
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  none.
 */
static void DMATxConfigure(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN State transition
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanStateTransnTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Ext Time Stamp Interrupt
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanExtTSIntrTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanTxRxPinStateTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanClkStpReqTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanTSRstTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This Interrupt Service Routine for EDMA completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppEdmaCompletionISR(void *handle);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanBusMonTest(st_mcanTestcaseParams_t *testParams);

extern int32_t mcanClockEnable(void);

extern int32_t mcanTestFunc(st_mcanTestcaseParams_t *testParams);

extern void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg);

extern void App_mcanPrintTxMsg(const MCAN_TxBufElement *txMsg);

extern int32_t App_mcanXBarConfig(void);

extern void App_mcanIntr0ISR(void *handle);

extern void App_mcanIntr1ISR(void *handle);

extern void App_mcanECCIntrISR(void *handle);

extern void App_mcanTSIntrISR(void *handle);

extern int32_t mcanClockEnable(void);

extern void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg);

extern int32_t mcanClockEnableandPADConfig(void);

extern uint32_t App_getBitConfigParamId(const MCAN_BitTimingParams *bitTimings);

extern void App_delayFunc(uint32_t timeout);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_mcanTxApp_main(st_mcanTestcaseParams_t *testParams)
{
    int32_t                    configStatus = STW_SOK;

    mcanBaseAddr = testParams->mcanConfigParams.mcanModule;
    configStatus += mcanClockEnableandPADConfig();
    if(configStatus != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Clock and PAD Configuration...");
    }
    configStatus += App_mcanXBarConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in X-Bar Configuration...");
    }

    /* Reset MCAN Module */
    MCAN_reset(mcanBaseAddr);
    while (MCAN_isInReset(mcanBaseAddr) == (uint32_t)TRUE)
    {
    }
    configStatus += App_mcanConfig(testParams);
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Configuration...");
    }

    configStatus += App_mcanTCEntrySetup(testParams);
    if(configStatus != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN TC Entry Configuration...TC cannot be Run...");
    }
    else
    {
        isrPrintEnable = (uint32_t)TRUE;
        switch (testParams->testcaseId)
        {
            case 10:
                testParams->testResult = App_mcanECCTest(testParams);
            break;
            case 11:
                testParams->testResult = App_mcanECCSelfTest(testParams);
            break;
            case 12:
                testParams->testResult = App_mcanECCSelfTest(testParams);
            break;
            case 13:
                testParams->testResult = App_mcanDMATest(testParams);
            break;
            case 15:
                testParams->testResult = App_mcanStateTransnTest(testParams);
            break;
            case 16:
                testParams->testResult = App_mcanExtTSIntrTest(testParams);
            break;
            case 17:
                testParams->testResult = App_mcanTxRxPinStateTest(testParams);
            break;
            case 18:
                testParams->testResult = App_mcanClkStpReqTest(testParams);
            break;
            case 19:
                testParams->testResult = App_mcanTSRstTest(testParams);
            break;
            case 20:
                testParams->testResult = App_mcanBusMonTest(testParams);
            break;
            default:
                testParams->testResult = App_mcanTxTest(testParams);
            break;
        }
        testParams->testResult += App_mcanCheckTCResultsMisc(testParams);
        configStatus += App_mcanTCExitSetup(testParams);
        if(configStatus != STW_SOK)
        {
            UARTConfigPrintf(uartBaseAddr, "\nError in MCAN TC Exit Configuration...");
        }
    }

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

void App_mcanWriteDDR(uint32_t addr, const MCAN_TxBufElement *elem)
{
    uint32_t regVal;
    uint32_t loopCnt = 0U;

    regVal = 0U;
    regVal |= (uint32_t)(elem->id << MCANSS_TX_BUFFER_ELEM_ID_SHIFT);
    regVal |= (uint32_t)(elem->rtr << MCANSS_TX_BUFFER_ELEM_RTR_SHIFT);
    regVal |= (uint32_t)(elem->xtd << MCANSS_TX_BUFFER_ELEM_XTD_SHIFT);
    regVal |= (uint32_t)(elem->esi << MCANSS_TX_BUFFER_ELEM_ESI_SHIFT);
    HW_WR_REG32(addr, regVal);
    addr += 4U;

    regVal = 0U;
    regVal |= (uint32_t)(elem->dlc << MCANSS_TX_BUFFER_ELEM_DLC_SHIFT);
    regVal |= (uint32_t)(elem->brs << MCANSS_TX_BUFFER_ELEM_BRS_SHIFT);
    regVal |= (uint32_t)(elem->fdf << MCANSS_TX_BUFFER_ELEM_FDF_SHIFT);
    regVal |= (uint32_t)(elem->efc << MCANSS_TX_BUFFER_ELEM_EFC_SHIFT);
    regVal |= (uint32_t)(elem->mm << MCANSS_TX_BUFFER_ELEM_MM_SHIFT);
    HW_WR_REG32(addr, regVal);
    addr += 4U;

    loopCnt = 0U;
    while(loopCnt < dataSize[elem->dlc])
    {
        regVal  = 0U;
        regVal |= elem->data[(loopCnt / 4U)];
        regVal |= (elem->data[(loopCnt / 4U) + 1U] << 8U);
        regVal |= (elem->data[(loopCnt / 4U) + 2U] << 16U);
        regVal |= (elem->data[(loopCnt / 4U) + 3U] << 24U);
        HW_WR_REG32(addr, regVal);
        addr += 4U;
        loopCnt += 4U;
    }
}

static int32_t App_mcanConfig(st_mcanTestcaseParams_t *testParams)
{
    uint32_t                   fdoe, loopCnt;
    int32_t                    configStatus = STW_SOK;
    MCAN_RevisionId            revId;

    /* Reset MCAN SS */
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
    configStatus += MCAN_init(mcanBaseAddr, testParams->mcanConfigParams.initParams);
    if(configStatus != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\nMCAN Initialization FAILED...\n", -1);
    }
    /* Configure MCAN module */
    configStatus += MCAN_config(mcanBaseAddr, testParams->mcanConfigParams.configParams);
    if(configStatus != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\nMCAN Configuration FAILED...\n", -1);
    }
    /* Configure Bit timings */
    configStatus += MCAN_setBitTime(mcanBaseAddr, testParams->mcanConfigParams.bitTimings);
    if(configStatus != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\nMCAN Bit Time Configuration FAILED...\n", -1);
    }
    /* Set Extended ID Mask */
    configStatus += MCAN_setExtIDAndMask(mcanBaseAddr, 0x1FFFFFFFU);
    if(configStatus != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\nMCAN Bit Time Configuration FAILED...\n", -1);
    }
    /* Configure Message RAM Sections */
    configStatus += MCAN_msgRAMConfig(mcanBaseAddr, testParams->mcanConfigParams.ramConfig);
    if(configStatus != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "\nMCAN Message RAM Configuration FAILED...\n", -1);
    }
    for(loopCnt = 0U ; loopCnt < testParams->mcanConfigParams.stdIdFiltNum; loopCnt++)
    {
        /* Configure Standard ID filter element */
        MCAN_addStdMsgIDFilter(mcanBaseAddr, 0U, &testParams->mcanConfigParams.stdIDFilter[0U]);
    }
    for(loopCnt = 0U ; loopCnt < testParams->mcanConfigParams.extIdFiltNum; loopCnt++)
    {
        /* Configure Standard ID filter element */
        MCAN_addExtMsgIDFilter(mcanBaseAddr, 0U, &testParams->mcanConfigParams.extIDFilter[0U]);
    }
    /* Configure ECC */
    MCAN_eccConfig(mcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
    /* Enable loopback if autoRunEnable is set/TRUE */
    if ((autoRunEnable == (uint32_t)TRUE) &&
        ((testParams->mcanConfigParams.mcanTestType &
          MCAN_TEST_TYPE_INTERNAL_LOOBACK) ==
          MCAN_TEST_TYPE_INTERNAL_LOOBACK))
    {
        MCAN_lpbkModeEnable(mcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, TRUE);
    }
    /* Enable loopback only if internal loopback is set as test mode */
    if (testParams->mcanConfigParams.mcanTestType == MCAN_TEST_TYPE_INTERNAL_LOOBACK)
    {
        MCAN_lpbkModeEnable(mcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, TRUE);
    }
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
    {}
    return configStatus;
}

static int32_t App_mcanTxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = STW_SOK, testStatus = STW_SOK;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, intrMask, txBufNum;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;

    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != STW_SOK)
            {
                UARTConfigPuts(uartBaseAddr, "\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufNum ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOSize +
                    testParams->mcanConfigParams.ramConfig->txBufNum);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }
    for (iterationCnt = 0U ;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         iterationCnt++)
    {
        for (loopCnt = 0U ;
             loopCnt < testParams->mcanConfigParams.txMsgNum ;
             loopCnt++)
        {
            MCAN_getTxFIFOQueStatus(mcanBaseAddr, &txFIFOStatus);
            if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
            {
                txBufNum = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
            }
            else
            {
                txBufNum = txFIFOStatus.putIdx;
            }
            /* Calculate Rx Interrupt Mask */
            if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
            {
                intrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG;
            }
            else
            {
                if(testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum == MCAN_RX_FIFO_NUM_0)
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO0_NEW_MSG;
                }
                else
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO1_NEW_MSG;
                }

            }
            switch (testParams->testcaseId)
            {
                case 1004:
                    intrMask = MCAN_INTR_SRC_HIGH_PRIO_MSG;
                break;
                default:
                break;
            }
            UARTConfigPrintf(uartBaseAddr, "\nSending Message with following details:\n");
            App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(mcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufNum,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(mcanBaseAddr, txBufNum);
            if (STW_SOK != configStatus)
            {
                UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
            }
            while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
            {}
            gMcanIsrIntr0Flag = 1U;
            while (!((gMcanIsrIntr0Status & intrMask) == intrMask))
            {
            }
            gMcanIsrIntr0Flag = 1U;
            /* Checking for Errors */
            MCAN_getErrCounters(mcanBaseAddr, &errCounter);
            if ((0U == errCounter.recErrCnt) &&
                (0U == errCounter.canErrLogCnt))
            {
                MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                    configStatus += App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
                    if(configStatus != STW_SOK)
                    {
                        UARTConfigPrintf(uartBaseAddr, "\nUnable to read received message(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    configStatus += App_mcanTxRxMessageCheck(
                                    testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                                    rxMsg);
                    /* Check if Message is stored into appropriate Rx Buffer */
                    if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
                    {
                        if(rxBuffNum != testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum)
                        {
                           testStatus += STW_EFAIL;
                        }
                    }
                    if(configStatus != STW_SOK)
                    {
                        testStatus += STW_EFAIL;
                        UARTConfigPrintf(uartBaseAddr, "\nTransmitted and received message does not match(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    else
                    {
                        testStatus += STW_SOK;
                        UARTConfigPrintf(uartBaseAddr,
                            "\nMessage successfully transferred/received(Iteration Count:Message Number): (%d,%d).\n",
                            (iterationCnt + 1U), (loopCnt + 1U));
                    }
                }
                else
                {
                    testStatus += STW_EFAIL;
                    UARTConfigPrintf(uartBaseAddr, "\nError in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                }
            }
            else
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nError Counters: Error in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }
            gMcanIsrIntr0Status = 0U;
        }
    }

    return testStatus;
}

static int32_t App_mcanReadRxMSG(MCAN_RxBufElement *rxMsg,
                                 uint32_t status)
{
    uint32_t    readBuffNum, bitPos;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_RxNewDataStatus newDataStatus;
    int32_t retStatus = STW_EFAIL;

    if((status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                    MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        MCAN_getNewDataStatus(mcanBaseAddr, &newDataStatus);
        for(readBuffNum = 0U ; readBuffNum < 64U ; readBuffNum++)
        {
            if(readBuffNum < 32U)
            {
                status = newDataStatus.statusLow;
                bitPos = 1U << readBuffNum;
                newDataStatus.statusLow = (0U | bitPos);
            }
            else
            {
                status = newDataStatus.statusHigh;
                bitPos = 1U << (readBuffNum - 32U);
                newDataStatus.statusHigh = (0U | bitPos);
            }
            MCAN_clearNewDataStatus(mcanBaseAddr, &newDataStatus);

            rxBuffNum = readBuffNum;
            if(bitPos == (status & bitPos))
            {
                MCAN_readMsgRam(mcanBaseAddr,
                                MCAN_MEM_TYPE_BUF,
                                readBuffNum,
                                MCAN_RX_FIFO_NUM_0,
                                rxMsg);
                if (isrPrintEnable == (uint32_t)TRUE)
                {
                    UARTConfigPrintf(uartBaseAddr, "\nRx Buffer: Received message with following details:");
                }
                retStatus = STW_SOK;
                break;
            }
        }
    }
    else if(((status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
        ((status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
    {
        retStatus = STW_SOK;
        readBuffNum = 0U;
        if(((status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
            UARTConfigPrintf(uartBaseAddr, "\nRx FIFO 0: Received message with following details:");
        }
        else
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
            UARTConfigPrintf(uartBaseAddr, "\nRx FIFO 1: Received message with following details:");
        }
        MCAN_getRxFIFOStatus(mcanBaseAddr, &fifoStatus);
        MCAN_readMsgRam(mcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        rxMsg);
        (void) MCAN_writeRxFIFOAck(mcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);
    }
    if (isrPrintEnable == (uint32_t)TRUE)
    {
        App_mcanPrintRxMsg(rxMsg);
    }

    return retStatus;
}

static int32_t App_mcanTxRxMessageCheck(MCAN_TxBufElement txMsg,
                                        MCAN_RxBufElement rxMsg)
{
    uint32_t msgMask, loopCnt;
    int32_t retStatus;

    /* Check/Compare Rx message with Tx message */
    if(txMsg.xtd == 1U)
    {
        msgMask = APP_MCAN_EXT_ID_MASK;
    }
    else
    {
        msgMask = APP_MCAN_STD_ID_MASK;
    }
    if (((txMsg.id & msgMask) == (rxMsg.id & msgMask)) &&
        (txMsg.rtr == rxMsg.rtr) &&
        (txMsg.xtd == rxMsg.xtd) &&
        (txMsg.esi == rxMsg.esi) &&
        (txMsg.dlc == rxMsg.dlc) &&
        (txMsg.brs == rxMsg.brs) &&
        (txMsg.fdf == rxMsg.fdf))
    {
        for (loopCnt = 0U;
             loopCnt < gMcanAppdataSize[rxMsg.dlc];
             loopCnt++)
        {
            if (txMsg.data[loopCnt] != rxMsg.data[loopCnt])
            {
                break;
            }
        }
        if(loopCnt == gMcanAppdataSize[rxMsg.dlc])
        {
            retStatus = STW_SOK;
        }
        else
        {
            retStatus = STW_EFAIL;
        }
    }
    else
    {
        retStatus = STW_EFAIL;
    }

    return retStatus;
}

static int32_t App_mcanTCEntrySetup(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = STW_SOK, configStatus = STW_SOK;
    uint32_t    configId;

     UARTConfigPuts(uartBaseAddr, "\nIn TC Entry Config Func...\n", -1);
    configId = App_getBitConfigParamId(testParams->mcanConfigParams.bitTimings);
    /* send a message to change baud-rate of receiver and this is valid only for
       B2B and not for loop back */
    if((configId != 0U) && (configId != 0xFFFFFFFFU))
    {
        /* change Tx baud-rate to default */
        /* Put MCAN in SW initialization mode */
        MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
        while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
        {}
        /* Configure Bit timings */
        configStatus += MCAN_setBitTime(mcanBaseAddr, &canFDBitTimings[0U]);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nDEFAULT MCAN Bit Time Configuration FAILED...\n", -1);
        }
        /* Take MCAN out of the SW initialization mode */
        MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
        while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
        {}
        status += App_mcanChangeBaudrateMSG(configId);
        /* change Tx baud-rate to configured by TC */
        /* Put MCAN in SW initialization mode */
        MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
        while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
        {}
        /* Configure Bit timings */
        configStatus += MCAN_setBitTime(mcanBaseAddr, &canFDBitTimings[configId]);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nCONFIGURRED MCAN Bit Time Configuration FAILED...\n", -1);
        }
        /* Take MCAN out of the SW initialization mode */
        MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
        while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
        {}
    }
    switch (testParams->testcaseId)
    {
        case 4:
            MCAN_extTSCounterConfig(mcanBaseAddr, 0xFFFF);
            MCAN_extTSCounterEnable(mcanBaseAddr, (uint32_t)TRUE);
        break;
        case 16:
            MCAN_extTSCounterConfig(mcanBaseAddr, 0x3FFF);
            MCAN_extTSCounterEnable(mcanBaseAddr, (uint32_t)TRUE);
        break;
        case 1003:
            MCAN_extTSCounterConfig(mcanBaseAddr, 0xFFFF);
            MCAN_extTSCounterEnable(mcanBaseAddr, (uint32_t)TRUE);
        break;
        default:
        break;
    }
    UARTConfigPuts(uartBaseAddr, "\nExiting TC Entry Config Func...\n", -1);

    return status;
}

static int32_t App_mcanTCExitSetup(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = STW_SOK;
    uint32_t    configId;

    UARTConfigPuts(uartBaseAddr, "\nIn TC Exit Config Func...\n", -1);
    configId = App_getBitConfigParamId(testParams->mcanConfigParams.bitTimings);
    /* send a message to change baud-rate of receiver and this is valid only for
       B2B and not for loop back */
    if((configId != 0U) && (configId != 0xFFFFFFFFU))
    {
        status += App_mcanChangeBaudrateMSG(0U);

    }
    UARTConfigPuts(uartBaseAddr, "\nExiting TC Exit Config Func...\n", -1);

    return status;
}

static int32_t App_mcanChangeBaudrateMSG(uint32_t idx)
{
    int32_t configStatus = STW_SOK;
    MCAN_RxBufElement    rxMsg;
    MCAN_TxBufElement    txMsg;
    MCAN_RxNewDataStatus newDataStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_ProtocolStatus protStatus;
    uint32_t    readBuffNum, bitPos, status;
    MCAN_RxFIFOStatus fifoStatus;

    UARTConfigPrintf(uartBaseAddr, "\n===============Sending Change Baud-rate message to Receiver===============\n");
    /* Message will be sent using Tx buffer 1 */
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
    if(idx == 0U)
    {
        txMsg.id =  (0x16 << 18);
    }
    else
    {
        txMsg.id =  (0x44 << 18);
    }
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = 1U;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 0U;
    txMsg.mm = 0xAAU;
    txMsg.data[0U] = (uint8_t)(idx & 0xFFU);
    /* Enable Transmission interrupt */
    configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                                             1U,
                                             (uint32_t)TRUE);
    if(configStatus != STW_SOK)
    {
         UARTConfigPuts(uartBaseAddr, "\nError in enabling Transmission Interrupt...\n", -1);
    }
    /* Always writing to Tx Buffer number 1 for echoing back */
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
    while (!(MCAN_INTR_SRC_TRANS_COMPLETE ==
            (gMcanIsrIntr1Status & MCAN_INTR_SRC_TRANS_COMPLETE)))
    {
    }
    gMcanIsrIntr1Flag = 1U;
    while (!((((gMcanIsrIntr1Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                        MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ||
             ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                        MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ||
             ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                        MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))))
    {
    }
    App_delayFunc(50U);
    gMcanIsrIntr1Flag = 1U;
    /* Checking for Errors */
    MCAN_getErrCounters(mcanBaseAddr, &errCounter);
    if ((0U != errCounter.recErrCnt) &&
        (0U != errCounter.canErrLogCnt))
    {
        configStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "\nError Counters: Error in transmission/reception\n");
    }
    MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
    /* Checking for Errors */
    if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
         (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
        ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
         (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
        (0U == protStatus.pxe))
    {
        UARTConfigPrintf(uartBaseAddr, "\nMessage successfully transferred.\n");
    }
    else
    {
        configStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "\nError in transmission message.\n");
    }
    if((gMcanIsrIntr1Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        MCAN_getNewDataStatus(mcanBaseAddr, &newDataStatus);
        MCAN_clearNewDataStatus(mcanBaseAddr, &newDataStatus);
        for(readBuffNum = 0U ; readBuffNum < 64U ; readBuffNum++)
        {
            if(readBuffNum < 32U)
            {
                status = newDataStatus.statusLow;
                bitPos = 1U << readBuffNum;
            }
            else
            {
                status = newDataStatus.statusHigh;
                bitPos = 1U << (readBuffNum - 32U);
            }

            if(bitPos == (status & bitPos))
            {
                MCAN_readMsgRam(mcanBaseAddr,
                                MCAN_MEM_TYPE_BUF,
                                readBuffNum,
                                MCAN_RX_FIFO_NUM_0,
                                &rxMsg);
                UARTConfigPrintf(uartBaseAddr, "\nRx Buffer: Received message.");
            }
        }
    }
    else if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
        ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
    {
        readBuffNum = 0U;
        if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
            UARTConfigPrintf(uartBaseAddr, "\nRx FIFO 0: Received message.");

        }
        else
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
            UARTConfigPrintf(uartBaseAddr, "\nRx FIFO 1: Received message.");
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

    }
    configStatus += App_mcanTxRxMessageCheck(txMsg, rxMsg);

    /* Revert configuration done by this  function to send the baud-rate change message */
    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_0);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        MCAN_INTR_LINE_NUM_1,
                        0U);
    /* Enable Transmission interrupt */
    configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                                             1U,
                                             (uint32_t)FALSE);
    if(configStatus != STW_SOK)
    {
         UARTConfigPuts(uartBaseAddr, "\nRerverting Config: Error in disabling Transmission Interrupt...\n", -1);
    }
    if(configStatus != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\n===============Change in Baud-rate for Receiver FAILED===============\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "\n===============Change in Baud-rate for Receiver is SUCCESSFUL===============\n");
    }
    /* Wait for sometime, this could be needed by receiver to change the baud rate */
    App_delayFunc(50U);

    return configStatus;
}

static int32_t App_mcanCheckTCResultsMisc(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = STW_SOK;
    uint32_t iterationCnt, loopCnt, oldTimeStamp = 0U;
    MCAN_TxEventFIFOElement txEventElem;
    MCAN_TxEventFIFOStatus txEventFIFOStatus;

    switch (testParams->testcaseId)
    {
        case 1:
            for (iterationCnt = 0U ;
             iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
             iterationCnt++)
            {
                for (loopCnt = 0U ;
                     loopCnt < testParams->mcanConfigParams.txMsgNum ;
                     loopCnt++)
                {
                    MCAN_getTxEventFIFOStatus(mcanBaseAddr, &txEventFIFOStatus);
                    MCAN_readTxEventFIFO(mcanBaseAddr, &txEventElem);
                    MCAN_writeTxEventFIFOAck(mcanBaseAddr, txEventFIFOStatus.getIdx);

                    if(App_mcanTxEventMessageCheck(
                        testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                        txEventElem) == STW_SOK)
                    {
                        oldTimeStamp = txEventElem.txts;
                        status += STW_SOK;
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element matches with transmitted message.\n", -1);
                    }
                    else
                    {
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element does not matche with transmitted message.\n", -1);
                        status += STW_EFAIL;
                    }
                }
            }
        break;
        case 4:
            for (iterationCnt = 0U ;
             iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
             iterationCnt++)
            {
                for (loopCnt = 0U ;
                     loopCnt < testParams->mcanConfigParams.txMsgNum ;
                     loopCnt++)
                {
                    MCAN_getTxEventFIFOStatus(mcanBaseAddr, &txEventFIFOStatus);
                    MCAN_readTxEventFIFO(mcanBaseAddr, &txEventElem);
                    MCAN_writeTxEventFIFOAck(mcanBaseAddr, txEventFIFOStatus.getIdx);

                    if ((App_mcanTxEventMessageCheck(
                        testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                        txEventElem) == STW_SOK)  &&
                        (oldTimeStamp != txEventElem.txts))
                    {
                        oldTimeStamp = txEventElem.txts;
                        status += STW_SOK;
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element matches with transmitted message.\n", -1);
                    }
                    else
                    {
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element does not matche with transmitted message.\n", -1);
                        status += STW_EFAIL;
                    }
                }
            }
        break;
        case 1000:
            for (iterationCnt = 0U ;
             iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
             iterationCnt++)
            {
                for (loopCnt = 0U ;
                     loopCnt < testParams->mcanConfigParams.txMsgNum ;
                     loopCnt++)
                {
                    MCAN_getTxEventFIFOStatus(mcanBaseAddr, &txEventFIFOStatus);
                    MCAN_readTxEventFIFO(mcanBaseAddr, &txEventElem);
                    MCAN_writeTxEventFIFOAck(mcanBaseAddr, txEventFIFOStatus.getIdx);

                    if(App_mcanTxEventMessageCheck(
                        testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                        txEventElem) == STW_SOK)
                    {
                        oldTimeStamp = txEventElem.txts;
                        status += STW_SOK;
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element matches with transmitted message.\n", -1);
                    }
                    else
                    {
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element does not matche with transmitted message.\n", -1);
                        status += STW_EFAIL;
                    }
                }
            }
        break;
        case 1003:
            for (iterationCnt = 0U ;
             iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
             iterationCnt++)
            {
                for (loopCnt = 0U ;
                     loopCnt < testParams->mcanConfigParams.txMsgNum ;
                     loopCnt++)
                {
                    MCAN_getTxEventFIFOStatus(mcanBaseAddr, &txEventFIFOStatus);
                    MCAN_readTxEventFIFO(mcanBaseAddr, &txEventElem);
                    MCAN_writeTxEventFIFOAck(mcanBaseAddr, txEventFIFOStatus.getIdx);

                    if ((App_mcanTxEventMessageCheck(
                        testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                        txEventElem) == STW_SOK)  &&
                        (oldTimeStamp != txEventElem.txts))
                    {
                        oldTimeStamp = txEventElem.txts;
                        status += STW_SOK;
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element matches with transmitted message.\n", -1);
                    }
                    else
                    {
                        UARTConfigPuts(uartBaseAddr, "Tx Event FIFO element does not matche with transmitted message.\n", -1);
                        status += STW_EFAIL;
                    }
                }
            }
        break;
        default:
        break;
    }

    return status;
}

static int32_t App_mcanTxEventMessageCheck(MCAN_TxBufElement txMsg,
                                           MCAN_TxEventFIFOElement txEventMsg)
{
    int32_t retStatus = STW_SOK;

    if ((txMsg.id == txEventMsg.id) &&
        (txMsg.rtr == txEventMsg.rtr) &&
        (txMsg.xtd == txEventMsg.xtd) &&
        (txMsg.esi == txEventMsg.esi) &&
        (txMsg.dlc == txEventMsg.dlc) &&
        (txMsg.brs == txEventMsg.brs) &&
        (txMsg.fdf == txEventMsg.fdf) &&
        (txMsg.mm == txEventMsg.mm))
    {
        retStatus += STW_SOK;
    }
    else
    {
        retStatus += STW_EFAIL;
    }

    return retStatus;
}

int32_t App_mcanPerfTxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = STW_SOK, testStatus = STW_SOK;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, intrMask, txBufNum;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t ts1, ts2, tsDiff, numOfMsgPerSec, hwUtiln;

    isrPrintEnable = (uint32_t)FALSE;
    mcanBaseAddr = testParams->mcanConfigParams.mcanModule;
    configStatus += mcanClockEnableandPADConfig();
    if(configStatus != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Clock and PAD Configuration...");
    }
    configStatus += App_mcanXBarConfig();
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in X-Bar Configuration...");
    }

    /* Reset MCAN Module */
    MCAN_reset(mcanBaseAddr);
    while (MCAN_isInReset(mcanBaseAddr) == (uint32_t)TRUE)
    {
    }
    configStatus += App_mcanConfig(testParams);
    if (STW_SOK != configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN Configuration...");
    }

    configStatus += App_mcanTCEntrySetup(testParams);
    if(configStatus != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN TC Entry Configuration...TC cannot be Run...");
    }
    else
    {
    }
    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != STW_SOK)
            {
                UARTConfigPuts(uartBaseAddr, "\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufNum ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOSize +
                    testParams->mcanConfigParams.ramConfig->txBufNum);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }

    /* capture time stamp before triggering Tx */
    ts1 = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    for (iterationCnt = 0U ;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         iterationCnt++)
    {
        for (loopCnt = 0U ;
             loopCnt < testParams->mcanConfigParams.txMsgNum ;
             loopCnt++)
        {
            MCAN_getTxFIFOQueStatus(mcanBaseAddr, &txFIFOStatus);
            if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
            {
                txBufNum = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
            }
            else
            {
                txBufNum = txFIFOStatus.putIdx;
            }
            /* Calculate Rx Interrupt Mask */
            if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
            {
                intrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG;
            }
            else
            {
                if(testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum == MCAN_RX_FIFO_NUM_0)
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO0_NEW_MSG;
                }
                else
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO1_NEW_MSG;
                }

            }
            switch (testParams->testcaseId)
            {
                case 5:
                    intrMask = MCAN_INTR_SRC_HIGH_PRIO_MSG;
                break;
                case 1004:
                    intrMask = MCAN_INTR_SRC_HIGH_PRIO_MSG;
                break;
                default:
                break;
            }
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(mcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufNum,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(mcanBaseAddr, txBufNum);
            if (STW_SOK != configStatus)
            {
                UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
            }
            while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
            {}
            gMcanIsrIntr0Flag = 1U;
            while (!((gMcanIsrIntr0Status & intrMask) == intrMask))
            {
            }
            gMcanIsrIntr0Flag = 1U;
            /* Checking for Errors */
            MCAN_getErrCounters(mcanBaseAddr, &errCounter);
            if ((0U == errCounter.recErrCnt) &&
                (0U == errCounter.canErrLogCnt))
            {
                MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                    configStatus += App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
                    if(configStatus != STW_SOK)
                    {
                        UARTConfigPrintf(uartBaseAddr, "\nUnable to read received message(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    configStatus += App_mcanTxRxMessageCheck(
                                    testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                                    rxMsg);
                    /* Check if Message is stored into appropriate Rx Buffer */
                    if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
                    {
                        if(rxBuffNum != testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum)
                        {
                           testStatus += STW_EFAIL;
                        }
                    }
                    if(configStatus != STW_SOK)
                    {
                        testStatus += STW_EFAIL;
                        UARTConfigPrintf(uartBaseAddr, "\nTransmitted and received message does not match(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    else
                    {
                        testStatus += STW_SOK;
                    }
                }
                else
                {
                    testStatus += STW_EFAIL;
                    UARTConfigPrintf(uartBaseAddr, "\nError in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                }
            }
            else
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nError Counters: Error in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }
            gMcanIsrIntr0Status = 0U;
        }
    }
    /* capture time stamp After Tx completion */
    ts2 = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    tsDiff = ts2 - ts1;
    numOfMsgPerSec = (testParams->mcanConfigParams.txMSGInterationCnt *
                      testParams->mcanConfigParams.txMsgNum * MCAN_APP_32K_CNT_FREQ_KHZ) / tsDiff;
    numOfMsgPerSec *= 2U;
    UARTConfigPrintf(uartBaseAddr, "\nTime Stamp: %d=>%d\n", ts1, ts2);
    UARTConfigPrintf(uartBaseAddr, "\nThroughPut: %d Msg/sec\n", numOfMsgPerSec);
    hwUtiln = ((numOfMsgPerSec * 100) / MCAN_THEOROTICAL_MAX);
    UARTConfigPrintf(uartBaseAddr, "HW Utilization: %d", hwUtiln);
    testParams->testResult += App_mcanCheckTCResultsMisc(testParams);
    configStatus += App_mcanTCExitSetup(testParams);
    if(configStatus != STW_SOK)
    {
        UARTConfigPrintf(uartBaseAddr, "\nError in MCAN TC Exit Configuration...");
    }
    if(hwUtiln < 70U)
    {
        testParams->testResult += STW_EFAIL;
        testStatus += STW_EFAIL;
    }
    testParams->isRun      = STW_SOK;
    UARTConfigPrintf(uartBaseAddr, "\nTX Test Result: %d", testStatus);

    return testStatus;
}

static int32_t App_mcanECCTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = STW_SOK, testStatus = STW_SOK;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, intrMask, txBufNum;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t startAddr, elemSize, elemAddr;

    gMcanECCIntrFlag = 1U;
    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != STW_SOK)
            {
                UARTConfigPuts(uartBaseAddr, "\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
            /* Enable Transmission Cancellation interrupt */
            configStatus += MCAN_getTxBufCancellationIntrEnable(mcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != STW_SOK)
            {
                UARTConfigPuts(uartBaseAddr, "\nMCAN Tx Cancellation Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufNum ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOSize +
                    testParams->mcanConfigParams.ramConfig->txBufNum);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
        /* Enable Transmission Cancellation interrupt */
        configStatus += MCAN_getTxBufCancellationIntrEnable(mcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nMCAN Tx Cancellation Interrupt Enable FAILED...\n", -1);
        }
    }
    /* Enable ECC Interrupts */
    MCAN_eccEnableIntr(mcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, TRUE);
    MCAN_eccEnableIntr(mcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, TRUE);
    if (testParams->mcanConfigParams.txMsg[0U].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
    {
        loopCnt = 0U;
        startAddr = testParams->mcanConfigParams.ramConfig->txStartAddr;
        elemSize  = objSize[testParams->mcanConfigParams.ramConfig->txBufElemSize];
        elemSize *= 4U;
        elemAddr  = startAddr + (elemSize * testParams->mcanConfigParams.txMsg[0U].bufferNum);
        /* Access data bytes of the message */
        elemAddr += 12U;
        elemAddr += MCAN_MCAN_MSG_MEM;
        elemAddr += mcanBaseAddr;

        MCAN_getTxFIFOQueStatus(mcanBaseAddr, &txFIFOStatus);
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                    MCAN_MEM_TYPE_BUF)
        {
            txBufNum = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
        }
        else
        {
            txBufNum = txFIFOStatus.putIdx;
        }
        /* Calculate Rx Interrupt Mask */
        if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
        {
            intrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG;
        }
        else
        {
            if(testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum == MCAN_RX_FIFO_NUM_0)
            {
                intrMask = MCAN_INTR_SRC_RX_FIFO0_NEW_MSG;
            }
            else
            {
                intrMask = MCAN_INTR_SRC_RX_FIFO1_NEW_MSG;
            }

        }
        switch (testParams->testcaseId)
        {
            case 1004:
                intrMask = MCAN_INTR_SRC_HIGH_PRIO_MSG;
            break;
            default:
            break;
        }
        /* SEC error test */
        {
            UARTConfigPrintf(uartBaseAddr, "\nSending Message with following details:\n");
            App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(mcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufNum,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Disable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 0U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 0U;
            MCAN_eccConfig(mcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            UARTConfigPrintf(uartBaseAddr, "Before single Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Introduce single bit error */
            HW_WR_REG32(elemAddr, HW_RD_REG32(elemAddr)^0x8U);
            UARTConfigPrintf(uartBaseAddr, "After single Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Enable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 1U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 1U;
            MCAN_eccConfig(mcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            App_delayFunc(1U);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(mcanBaseAddr, txBufNum);
            if (STW_SOK != configStatus)
            {
                UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
            }
            while (gMcanECCIntrFlag)
            {
            }
            gMcanECCIntrFlag = 1U;
            while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
            {}
            gMcanIsrIntr0Flag = 1U;
            while (!((gMcanIsrIntr0Status & intrMask) == intrMask))
            {
            }
            gMcanIsrIntr0Flag = 1U;
            /* Check for ECC Error */
            if ((gMcaneccErr.secErr == 1U) &&
                (gMcaneccErr.dedErr != 1U) &&
                (gMcaneccErr.row == ((elemAddr - (MCAN_MCAN_MSG_MEM + mcanBaseAddr))/4)) &&
                (gMcaneccErr.bit1 == 3U))
            {
                UARTConfigPrintf(uartBaseAddr, "\nECC SEC Error location matched.\n");
            }
            else
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nECC SEC Error location does not match.\n");
            }
            /* Checking for Errors */
            MCAN_getErrCounters(mcanBaseAddr, &errCounter);
            if ((0U == errCounter.recErrCnt) &&
                (0U == errCounter.canErrLogCnt))
            {
                MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                    configStatus += App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
                    if(configStatus != STW_SOK)
                    {
                        UARTConfigPrintf(uartBaseAddr, "\nUnable to read received message(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    configStatus += App_mcanTxRxMessageCheck(
                                    testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                                    rxMsg);
                    /* Check if Message is stored into appropriate Rx Buffer */
                    if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
                    {
                        if(rxBuffNum != testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum)
                        {
                           testStatus += STW_EFAIL;
                        }
                    }
                    if(configStatus != STW_SOK)
                    {
                        testStatus += STW_EFAIL;
                        UARTConfigPrintf(uartBaseAddr, "\nTransmitted and received message does not match(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    else
                    {
                        testStatus += STW_SOK;
                        UARTConfigPrintf(uartBaseAddr,
                            "\nMessage successfully transferred/received(Iteration Count:Message Number): (%d,%d).\n",
                            (iterationCnt + 1U), (loopCnt + 1U));
                    }
                }
                else
                {
                    testStatus += STW_EFAIL;
                    UARTConfigPrintf(uartBaseAddr, "\nError in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                }
            }
            else
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nError Counters: Error in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }
            gMcanIsrIntr0Status = 0U;
        }
        /* DED error test */
        {
            UARTConfigPrintf(uartBaseAddr, "\nSending Message with following details:\n");
            App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(mcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufNum,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Disable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 0U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 0U;
            MCAN_eccConfig(mcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            UARTConfigPrintf(uartBaseAddr, "Before Double Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Introduce Double bit error */
            HW_WR_REG32(elemAddr, HW_RD_REG32(elemAddr)^0xAU);
            UARTConfigPrintf(uartBaseAddr, "After Double Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Enable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 1U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 1U;
            MCAN_eccConfig(mcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            App_delayFunc(1U);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(mcanBaseAddr, txBufNum);
            if (STW_SOK != configStatus)
            {
                UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
            }
            while (gMcanECCIntrFlag)
            {
            }
            gMcanECCIntrFlag = 1U;
            /* Insert some delay */
            App_delayFunc(1000);
            if (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(mcanBaseAddr))
            {
                UARTConfigPrintf(uartBaseAddr, "\nTransmission of corrupted message stopped.\n");
            }
            else
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nSent out Corrupted Message.\n");
            }
            /* cancel transmission of corrupted message */
            MCAN_txBufCancellationReq(mcanBaseAddr, txBufNum);
            while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_CANCEL_FINISH) ==
                                MCAN_INTR_SRC_TRANS_CANCEL_FINISH))
            {}
            gMcanIsrIntr0Flag = 1U;
            UARTConfigPrintf(uartBaseAddr, "\nTx Buffer Transmission Cancellation Interrupt Happened.\n");
            /* Take MCAN out of the SW initialization mode */
            MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
            while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
            {}
            /* Check for ECC Error */
            if ((gMcaneccErr.secErr != 1U) &&
                (gMcaneccErr.dedErr == 1U) &&
                (gMcaneccErr.row == ((elemAddr - (MCAN_MCAN_MSG_MEM + mcanBaseAddr))/4)))
            {
                UARTConfigPrintf(uartBaseAddr, "\nECC DED Error location matched.\n");
            }
            else
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nECC DED Error location does not match.\n");
            }
            gMcanIsrIntr0Status = 0U;
        }
    }
    return testStatus;
}

static int32_t App_mcanECCSelfTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  testStatus = STW_SOK;
    uint32_t accessAddr, secErrFlag = 0U, dedErrFlag = 0U;

    gMcanECCIntrFlag = 1U;
    /* Enable ECC Interrupts */
    MCAN_eccEnableIntr(mcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, TRUE);
    MCAN_eccEnableIntr(mcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, TRUE);
    MCAN_eccForceError(mcanBaseAddr, testParams->mcanConfigParams.eccFrcParams);
    if (testParams->mcanConfigParams.eccFrcParams->errType == MCAN_ECC_ERR_TYPE_SEC)
    {
        secErrFlag = 1U;
        UARTConfigPrintf(uartBaseAddr, "SEC Error Test:\n");
    }
    if (testParams->mcanConfigParams.eccFrcParams->errType == MCAN_ECC_ERR_TYPE_DED)
    {
        dedErrFlag = 1U;
        UARTConfigPrintf(uartBaseAddr, "DED Error Test:\n");
    }
    accessAddr = mcanBaseAddr;
    accessAddr += MCAN_MCAN_MSG_MEM;
    accessAddr += (testParams->mcanConfigParams.eccFrcParams->rowNum * 4U);
    HW_RD_REG32(accessAddr);
    while (gMcanECCIntrFlag)
    {
    }
    gMcanECCIntrFlag = 1U;
    /* Check for ECC Error */
    if ((gMcaneccErr.secErr == secErrFlag) &&
        (gMcaneccErr.dedErr == dedErrFlag) &&
        (gMcaneccErr.row == testParams->mcanConfigParams.eccFrcParams->rowNum))
    {
        if (secErrFlag == 1U)
        {
            if (gMcaneccErr.bit1 != testParams->mcanConfigParams.eccFrcParams->bit1)
            {
                testStatus += STW_EFAIL;
                UARTConfigPrintf(uartBaseAddr, "\nECC SEC Error bit location match failed.\n");
            }
        }
        UARTConfigPrintf(uartBaseAddr, "\nECC Error location matched.\n");
    }
    else
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "\nECC Error location does not match.\n");
    }

    return testStatus;
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
    uint32_t edmaRegion;
    uint32_t buffAddReqMem = 0x82000000, destAddr;
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

static int32_t App_mcanDMATest(st_mcanTestcaseParams_t *testParams)
{
    uint32_t ddrAddr = 0x80000000U, eleAddr, loopCnt, innerLoopCnt;
    uint32_t ddrTxAddr, ddrRxAddr, txData, rxData;
    int32_t testStatus = STW_SOK;

    UARTConfigPrintf(uartBaseAddr, "\nDMA Tx Side Test Application\n");
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMSGInterationCnt;
         loopCnt++)
    {
        /* Full CAN FD message supported only i.e. 18 words */
        eleAddr = ddrAddr + (loopCnt * 18U * 4U);
        App_mcanWriteDDR(eleAddr, &testParams->mcanConfigParams.txMsg[0U].txElem);
    }
    HW_WR_REG32(0x82000000, 0x1U);
    HW_WR_REG32(0x82000040, 0x1U);
    DMATxConfigure(testParams);

    App_delayFunc(100U);
    UARTConfigPrintf(uartBaseAddr, "\nSending Data:\n");
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                        edmaChannelNumber,
                        EDMA3_TRIG_MODE_EVENT);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                        edmaChannelNumber,
                        EDMA3_TRIG_MODE_MANUAL);
    edmaTransferComplete = 1U;
    while(edmaTransferComplete)
    {
    }
    edmaTransferComplete = 1U;
    DMARxConfigure(testParams);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                        edmaChannelNumber,
                        EDMA3_TRIG_MODE_EVENT);

    UARTConfigPrintf(uartBaseAddr, "\nReceiving Data:\n");
    while(edmaTransferComplete)
    {
    }

    /* Check for Tx and Rx data available in DDR */
    ddrTxAddr = APP_TX_SRC_ADDR;
    ddrRxAddr = APP_RX_SRC_ADDR;
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         loopCnt++)
    {
        for (innerLoopCnt = 2U ; innerLoopCnt < 18U ; innerLoopCnt++)
        {
            txData = HW_RD_REG32((ddrTxAddr + (loopCnt * 18U * 4U) + (innerLoopCnt * 4U)));
            rxData = HW_RD_REG32((ddrRxAddr + (loopCnt * 18U* 4U) + (innerLoopCnt * 4U)));
            if (txData != rxData)
            {
                break;
            }
        }
        if (innerLoopCnt < 18U)
        {
            break;
        }
    }
    if (loopCnt < testParams->mcanConfigParams.txMSGInterationCnt)
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "Received Data does not match with  Sent data.\n");
        UARTConfigPrintf(uartBaseAddr, "Message Number: %d and Word Number: %d\n", loopCnt, innerLoopCnt);
        UARTConfigPrintf(uartBaseAddr, "Tx Addr: 0x%x and Rx Addr: 0x%x\n", ((ddrTxAddr + (loopCnt * 18U * 4U) + (innerLoopCnt * 4U))), ((ddrRxAddr + (loopCnt * 18U * 4U) + (innerLoopCnt * 4U))));
        UARTConfigPrintf(uartBaseAddr, "Tx Data: 0x%x and Rx Data: 0x%x\n", txData, rxData);
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "Received Data matched with  Sent data.\n");
    }

    return testStatus;
}

static int32_t App_mcanStateTransnTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = STW_SOK, testStatus = STW_SOK;
    uint32_t loopCnt      = 1U, txBufNum;
    MCAN_ProtocolStatus protStatus;

    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != STW_SOK)
            {
                UARTConfigPuts(uartBaseAddr, "\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
                testStatus += STW_EFAIL;
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufNum ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOSize +
                    testParams->mcanConfigParams.ramConfig->txBufNum);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(mcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != STW_SOK)
        {
            UARTConfigPuts(uartBaseAddr, "\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
            testStatus += STW_EFAIL;
        }
    }

    loopCnt = 0U;
    txBufNum = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
    UARTConfigPrintf(uartBaseAddr, "\nSending Message with following details:\n");
    App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);

    UARTConfigPrintf(uartBaseAddr, "\nCurrent State: Error Active\n");
    /* Write message to Msg RAM */
    MCAN_writeMsgRam(mcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0U].storageId,
                     txBufNum,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_ERR_PASSIVE) ==
                                MCAN_INTR_SRC_ERR_PASSIVE))
    {
        loopCnt++;
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(mcanBaseAddr, txBufNum);
        if (STW_SOK != configStatus)
        {
            UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
            testStatus += STW_EFAIL;
        }
        App_delayFunc(50);
    }
    gMcanIsrIntr0Status = 0U;
    MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
    if ((protStatus.errPassive == 1U) && (protStatus.busOffStatus != 1U))
    {
        UARTConfigPrintf(uartBaseAddr, "\nCurrent State: Error Passive\n");
        UARTConfigPrintf(uartBaseAddr, "Message transmitted unsuccessfully: %d\n", loopCnt);

    }

    while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_BUS_OFF_STATUS) ==
                                MCAN_INTR_SRC_BUS_OFF_STATUS))
    {
        loopCnt++;
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(mcanBaseAddr, txBufNum);
        if (STW_SOK != configStatus)
        {
            UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
        }
        App_delayFunc(50);
    }
    gMcanIsrIntr0Status = 0U;
    MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
    if ((protStatus.errPassive == 1U) &&
        (protStatus.busOffStatus == 1U) &&
        (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(mcanBaseAddr)))
    {
        UARTConfigPrintf(uartBaseAddr, "\nCurrent State: Bus Off\n");
        UARTConfigPrintf(uartBaseAddr, "Message transmitted unsuccessfully: %d\n", loopCnt);

    }
    loopCnt = 0U;
    /* Clear pending Tx request */
    MCAN_txBufCancellationReq(mcanBaseAddr, 0U);
    while ((MCAN_txBufCancellationStatus(mcanBaseAddr)  & (0x1 << 0)) != (0x1 << 0))
    {
    }
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(mcanBaseAddr))
    {}
    /* wait for 129 occurrences of Bus Idle (129 × 11 consecutive recessive bits)
       before resuming normal operation. */
    App_delayFunc(50U);
    MCAN_getProtocolStatus(mcanBaseAddr, &protStatus);
    if ((protStatus.errPassive == 0U) &&
        (protStatus.busOffStatus == 0U) &&
        (protStatus.warningStatus == 0U))
    {
        UARTConfigPrintf(uartBaseAddr, "\nCurrent State: Error Active\n");
        UARTConfigPrintf(uartBaseAddr, "Message transmitted Successfully: %d\n", loopCnt);
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "\nCurrent State is not Error Active\n");
        testStatus += STW_EFAIL;
    }

    return testStatus;
}

static int32_t App_mcanExtTSIntrTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = STW_SOK;

    gMcanExtTSIntrFlag = 1U;
    /* Enable External Time Stamp Interrupt */
    MCAN_extTSEnableIntr(mcanBaseAddr, TRUE);

    UARTConfigPrintf(uartBaseAddr, "Waiting for 1st Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
    gMcanExtTSIntrFlag = 1U;
    UARTConfigPrintf(uartBaseAddr, "Waiting for 2nd Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
    gMcanExtTSIntrFlag = 1U;
    UARTConfigPrintf(uartBaseAddr, "Waiting for 3rd Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
    gMcanExtTSIntrFlag = 1U;
    /* Disable External Time Stamp Interrupt */
    MCAN_extTSEnableIntr(mcanBaseAddr, FALSE);

    return testStatus;
}

static int32_t App_mcanTxRxPinStateTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = STW_SOK;

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(mcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(mcanBaseAddr))
    {}

    if (MCAN_getRxPinState(mcanBaseAddr) == 1U)
    {
        UARTConfigPrintf(uartBaseAddr, "Rx Pin Mode: Recessive\n");
    }
    else
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "Rx Pin Mode: Dominant\n");
    }
    UARTConfigPrintf(uartBaseAddr, "Setting Rx PAD into Dominant mode.\n");
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* rx PAD */
    HW_WR_REG32(0x4A0035C0U, 0x0000CU);
#elif defined (SOC_TDA2PX)
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_RX,0x00000000);
#endif
    if (MCAN_getRxPinState(mcanBaseAddr) == 1U)
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "Rx Pin Mode: Recessive\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "Rx Pin Mode: Dominant\n");
    }
    UARTConfigPrintf(uartBaseAddr, "Setting Tx PAD into Dominant mode.\n");
    MCAN_setTxPinState(mcanBaseAddr, 0x2);
    if (MCAN_getTxPinState(mcanBaseAddr) == 0x2U)
    {
        UARTConfigPrintf(uartBaseAddr, "Tx Pin Mode: Dominant\n");
    }
    else
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "Rx Pin Mode: Recessive\n");
    }
    UARTConfigPrintf(uartBaseAddr, "Setting Tx PAD into Recessive mode.\n");
    MCAN_setTxPinState(mcanBaseAddr, 0x3);
    if (MCAN_getTxPinState(mcanBaseAddr) == 0x3U)
    {
        UARTConfigPrintf(uartBaseAddr, "Tx Pin Mode: Recessive\n");
    }
    else
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "Rx Pin Mode: Dominant\n");
    }

    return testStatus;
}

static int32_t App_mcanClkStpReqTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = STW_SOK;

    UARTConfigPrintf(uartBaseAddr, "Asserting Clock Stop Request..\n");
    MCAN_addClockStopRequest(mcanBaseAddr, TRUE);
    while (MCAN_getClkStopAck(mcanBaseAddr) != 1U)
    {
    }
    UARTConfigPrintf(uartBaseAddr, "Clock Stop Request ACKed!!\n");
    if (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(mcanBaseAddr))
    {
        UARTConfigPrintf(uartBaseAddr, "MCAN is in SW Init Mode.\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "MCAN is in not SW Init Mode.\n");
        testStatus += STW_EFAIL;
    }

    return testStatus;
}

static int32_t App_mcanTSRstTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = STW_SOK;
    uint32_t oldTimeStamp, timeStamp;

    timeStamp = MCAN_getTSCounterVal(mcanBaseAddr);
    UARTConfigPrintf(uartBaseAddr, "TS at (t) ms: %d\n", timeStamp);
    App_delayFunc(10);
    oldTimeStamp = timeStamp;
    timeStamp = MCAN_getTSCounterVal(mcanBaseAddr);
    UARTConfigPrintf(uartBaseAddr, "TS at (t + 10) ms: %d\n", timeStamp);

    /* reset TS counter */
    MCAN_resetTSCounter(mcanBaseAddr);
    oldTimeStamp = timeStamp;
    timeStamp = MCAN_getTSCounterVal(mcanBaseAddr);
    /* wrap around condition is not taken care */
    if (timeStamp < oldTimeStamp)
    {
        UARTConfigPrintf(uartBaseAddr, "TS Counter Reset done!!\n");
    }
    else
    {
        testStatus += STW_EFAIL;
    }


    return testStatus;
}

static int32_t App_mcanBusMonTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = STW_SOK, testStatus = STW_SOK;
    MCAN_RxBufElement rxMsg;

    /* Enable Interrupts */
    MCAN_enableIntr(mcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    gMcanIsrIntr0Status = 0U;
    UARTConfigPrintf(uartBaseAddr, "Send message over the CAN network(TDA3xx MCAN and only one another node).\n");
    UARTConfigPrintf(uartBaseAddr, "Same message shall be received by MCAN but transmitter node shall get ACK Error.\n");
    while  (!(((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                    MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ||
            ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
            ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)))
    {
    }
    /* Disable Interrupt Line */
    MCAN_enableIntrLine(mcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        0U);
    UARTConfigPrintf(uartBaseAddr, "Message received:\n");
    configStatus += App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
    if(configStatus != STW_SOK)
    {
        testStatus += STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "\nUnable to read received message.\n");
    }
    gMcanIsrIntr0Status = 0U;

    return testStatus;
}
