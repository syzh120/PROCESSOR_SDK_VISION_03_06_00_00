/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file     mcan_evm_loopback_app_main.c
 *
 *  \brief    This file contains MCAN sample code.
 *
 *  \details  MCAN operational mode is set to CAN-FD. This test will need
 *            two MCAN nodes present two different EVM connected to each other..
 *            Arbitration bit-rate and data phase bit-rate is set to 1Mbit/s and
 *            5Mbit/s receptively.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_mcan.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_mcan.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#if defined (SOC_TDA2PX)
/* For TDA2Px MCAN address is in bit band region. So use the virtual address. */
#define APP_MCAN_MODULE                          (SOC_MCAN_BASE_VIRT)
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define APP_MCAN_MODULE                          (SOC_MCAN_BASE)
#endif

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

#if defined (SOC_TDA2PX)
#define APP_MCAN_INT0_M4                                  (78U)
#define APP_MCAN_INT1_M4                                  (79U)
#define APP_MCAN_ECC_INT_M4                               (75U)
#define APP_MCAN_TS_INT_M4                                (72U)
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define APP_MCAN_INT0_M4                                  (34U)
#define APP_MCAN_INT1_M4                                  (35U)
#define APP_MCAN_ECC_INT_M4                               (36U)
#define APP_MCAN_TS_INT_M4                                (37U)
#endif

#if defined (__TI_ARM_V7M4__)
    #define APP_MCAN_INT0                     (APP_MCAN_INT0_M4)
    #define APP_MCAN_INT1                     (APP_MCAN_INT1_M4)
    #define APP_MCAN_ECC_INT                  (APP_MCAN_ECC_INT_M4)
    #define APP_MCAN_TS_INT                   (APP_MCAN_TS_INT_M4)
    #define XBAR_CPU                          (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define XBAR_MCAN_INT0                       (CSL_XBAR_INST_IPU1_IRQ_34)
    #define XBAR_MCAN_INT1                       (CSL_XBAR_INST_IPU1_IRQ_35)
    #define XBAR_MCAN_ECC                        (CSL_XBAR_INST_IPU1_IRQ_36)
    #define XBAR_MCAN_TS                         (CSL_XBAR_INST_IPU1_IRQ_37)
    #define XBAR_INTR0_SOURCE                    (CSL_XBAR_MCAN_IRQ_INT0)
    #define XBAR_INTR1_SOURCE                    (CSL_XBAR_MCAN_IRQ_INT1)
    #define XBAR_INTR_ECC_SOURCE                 (CSL_XBAR_MCAN_IRQ_PARITY)
    #define XBAR_INTR_TS_SOURCE                  (CSL_XBAR_MCAN_IRQ_TS)
#elif defined (_TMS320C6X)
    /* Not yet supported */
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t          gMcanAppdataSize[16] =
{0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
volatile uint32_t gMcanIsrIntr0Flag = 1U;
volatile uint32_t gMcanIsrIntr1Flag = 1U;
MCAN_ECCErrStatus gMcaneccErr;

#if defined (SOC_TDA2PX)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

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
 * \brief   This function will configure X-BAR for MCAN interrupts
 *
 * \param   none.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanXBarConfig(void);

/**
 * \brief   This is Interrupt Service Routine for MCAN interrupt 0.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void App_mcanIntr0ISR(void *handle);

/**
 * \brief   This is Interrupt Service Routine for MCAN interrupt 1.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void App_mcanIntr1ISR(void *handle);

/**
 * \brief   This is Interrupt Service Routine for MCAN ECC interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void App_mcanECCIntrISR(void *handle);

/**
 * \brief   This is Interrupt Service Routine for MCAN TimeStamp interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void App_mcanTSIntrISR(void *handle);

/**
 * \brief   This API will MCAN Rx Msg.
 *
 * \param   rxMsg           received message object.
 *
 * \retval  none.
 */
static void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg);

/**
 * \brief   This API will MCAN Tx Msg.
 *
 * \param   txMsg           message object to be transmitted.
 *
 * \retval  none.
 */
static void App_mcanPrintTxMsg(const MCAN_TxBufElement *txMsg);

/**
 * \brief   This API will load the register from ECC memory bank.
 *
 * \param   txMsg           message object to be transmitted.
 *
 * \return  None.
 */
static void APP_mcanTxTest(MCAN_TxBufElement *txMsg);

/**
 * \brief   This API will load the register from ECC memory bank.
 *
 * \param   txMsg           message object to be transmitted
 *                          (Needed for Message validation).
 *
 * \return  None.
 */
static void APP_mcanRxTest(const MCAN_TxBufElement *txMsg);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations- UART  */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /*Pad configurations - MCAN */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RXD,0x0006000C);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_TXD,0x0004000C);
#elif defined (SOC_TDA2PX)
    /*Pad configurations- UART  */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /*Pad configurations - MCAN */
    /* Configure mcan_tx, mcan_rx pads on dcan1_tx and dcan1_rx pads */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE+CTRL_CORE_CONTROL_SPARE_RW,
        CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN,
        CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_MCAN_DCAN1_PADS);

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_TX,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_RX,0x00040000);

    /* Enable MCAN clock. */
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE+CM_WKUPAON_ADC_CLKCTRL,
        CM_WKUPAON_ADC_CLKCTRL_MODULEMODE,
        CM_WKUPAON_ADC_CLKCTRL_MODULEMODE_ENABLE);
    while (CM_WKUPAON_ADC_CLKCTRL_IDLEST_FUNC !=
                HW_RD_FIELD32(SOC_WKUPAON_CM_BASE+CM_WKUPAON_ADC_CLKCTRL,
                CM_WKUPAON_ADC_CLKCTRL_IDLEST))
    {
        /* wait for module to be enabled */
    }
#endif
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                    UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);

}

int32_t main(void)
{
    int32_t                    configStatus = STW_EFAIL;
    uint32_t                   mode         = 0U, loopCnt = 0U;
    MCAN_TxBufElement          txMsg;
    uint32_t                   postDivider;

#if defined (SOC_TDA2PX)
    /* Wait for SBL running on A15 to finish all UART prints. */
    volatile int32_t          delayVal = 0x0FFFFFU;
    while (delayVal != 0)
    {
        delayVal --;
    }
#endif

    /* Do Pad Config for UART */
    padConfig_prcmEnable();
    UARTConfigPuts(uartBaseAddr, "\n Starting Application...\n", -1);
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* Configure MCAN io clock */
    /* Set the post div value of 25. MCAN HSDIV registers is part of Control
     * module registers, which needs an adjustment value to be subtracted for
     * the HS dividers to properly divide the DPLL outputs to have the right
     * frequency values.
     */
    postDivider = 24U;
    /* Set the postDividers reg */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLKHSDIV,
                  postDivider);
    /* Select the mux value */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL,
                  1U);
    /* Select the Toggle sequence 010 */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL,
                  0U);
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL,
                  1U);
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL,
                  0U);
    /* Re Select the mux value */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL,
                  0U);
    /* Enable the HSDIV post div clock */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE+CTRL_CORE_SEC_SMA_SW_17,
                  CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN,
                  1U);
#elif defined (SOC_TDA2PX)
    postDivider = 24U;
    /* Set the postDividers reg */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV,
                  postDivider);
    /* Select the mux value */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_TENABLEDIV,
                  1U);
    /* Select the Toggle sequence 010 */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_LATCH_EN,
                  0U);
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_LATCH_EN,
                  1U);
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_LATCH_EN,
                  0U);
    /* Enable the HSDIV post div clock */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_EN,
                  1U);
#endif
    UARTConfigPuts(uartBaseAddr, "MCAN Clock Configuration Successful.\n", -1);

    UARTConfigPuts(uartBaseAddr,"MCAN Node Type:\n", -1);
    UARTConfigPuts(uartBaseAddr,"1. Transmitter Side.\n", -1);
    UARTConfigPuts(uartBaseAddr,"2. Receiver Side.\n", -1);
    UARTConfigPuts(uartBaseAddr,"Enter type of the node:\n", -1);
    mode = UARTConfigGetNum(uartBaseAddr);

    /* CrossBar Configuration */
    configStatus = App_mcanXBarConfig();

    if (STW_SOK == configStatus)
    {
        /* Enable MCAN module */
        HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER2_DCAN2_CLKCTRL,
                      CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
                      CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);
        while (CM_L4PER2_DCAN2_CLKCTRL_IDLEST_FUNC !=
               HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER2_DCAN2_CLKCTRL,
                             CM_L4PER2_DCAN2_CLKCTRL_IDLEST))
        {
            /* Wait till MCAN module is enabled */
        }
    }

    /* Initialize message to transmit */
    txMsg.id  = (uint32_t)((uint32_t)(0x4U) << 18U);
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = 0xFU;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 1U;
    txMsg.mm  = 0xAAU;
    for (loopCnt = 0; loopCnt < MCAN_MAX_PAYLOAD_BYTES; loopCnt++)
    {
        txMsg.data[loopCnt] = loopCnt;
    }

    configStatus = App_mcanConfig();
    if (STW_SOK == configStatus)
    {
        switch (mode)
        {
            case 1:
                /* This is transmitter side application */
                UARTConfigPuts(uartBaseAddr, "\nTransmitter Side application:\n", -1);
                UARTConfigPuts(uartBaseAddr,
                    "This test will send 15  messages with various payload varying from 1byte to 64bytes.\n",
                    -1);
                UARTConfigPuts(uartBaseAddr, "Message Object:\n", -1);
                App_mcanPrintTxMsg(&txMsg);
                APP_mcanTxTest(&txMsg);
                break;
            case 2:
                /* This is receiver side application */
                UARTConfigPuts(uartBaseAddr, "\nReceiver Side application:\n", -1);
                UARTConfigPuts(uartBaseAddr,
                    "This test will receive 15  messages with various payload varying from 1byte to 64bytes.\n",
                    -1);
                APP_mcanRxTest(&txMsg);
                break;
            default:
                UARTConfigPuts(uartBaseAddr,"Wrong option...\n", -1);
                break;
        }
    }
    UARTConfigPuts(uartBaseAddr,"\n Application is completed.\n", -1);

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t App_mcanXBarConfig(void)
{
    int32_t configStatus = STW_SOK;

    Intc_Init();

    /* XBar configuration */
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_INT0, XBAR_INTR0_SOURCE);
    Intc_IntEnable(APP_MCAN_INT0_M4);
    Intc_IntRegister(APP_MCAN_INT0_M4,
                     (IntrFuncPtr) App_mcanIntr0ISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_INT0_M4, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_INT0_M4);

    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_INT1, XBAR_INTR1_SOURCE);
    Intc_IntEnable(APP_MCAN_INT1_M4);
    Intc_IntRegister(APP_MCAN_INT1_M4,
                     (IntrFuncPtr) App_mcanIntr1ISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_INT1_M4, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_INT1_M4);

    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_ECC, XBAR_INTR_ECC_SOURCE);
    Intc_IntEnable(APP_MCAN_ECC_INT);
    Intc_IntRegister(APP_MCAN_ECC_INT,
                     (IntrFuncPtr) App_mcanECCIntrISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_ECC_INT, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_ECC_INT);

    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_TS, XBAR_INTR_TS_SOURCE);
    Intc_IntEnable(APP_MCAN_TS_INT);
    Intc_IntRegister(APP_MCAN_TS_INT,
                     (IntrFuncPtr) App_mcanTSIntrISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_TS_INT, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_TS_INT);

    UARTConfigPuts(uartBaseAddr,"CrossBar Configuration done.\n", -1);

    return configStatus;
}

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
    stdFiltelem.sfid2 = 0x0U;
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
    MCAN_getRevisionId(APP_MCAN_MODULE, &revId);
    UARTConfigPuts(uartBaseAddr, "MCANSS Revision ID:\n", -1);
    UARTConfigPuts(uartBaseAddr, "scheme:\n", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.scheme);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    UARTConfigPuts(uartBaseAddr, "Business Unit:", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.bu);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    UARTConfigPuts(uartBaseAddr, "Module ID:", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.modId);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    UARTConfigPuts(uartBaseAddr, "RTL Revision:", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.rtlRev);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    UARTConfigPuts(uartBaseAddr, "Major Revision:", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.major);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    UARTConfigPuts(uartBaseAddr, "Custom Revision:", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.custom);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    UARTConfigPuts(uartBaseAddr, "Minor Revision:", -1);
    UARTConfigPutHexNum(uartBaseAddr, revId.minor);
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    /* Enable Auto wakeup */
    fdoe = MCAN_isFDOpEnable(APP_MCAN_MODULE);
    if ((uint32_t)TRUE == fdoe)
    {
        UARTConfigPuts(uartBaseAddr, "CAN-FD operation is enabled through E-Fuse.\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "CAN-FD operation is disabled through E-Fuse.\n", -1);
    }
    /* wait for memory initialization to happen */
    while (FALSE == MCAN_isMemInitDone(APP_MCAN_MODULE))
    {}
    /* Get endianess value */
    UARTConfigPuts(uartBaseAddr, "Endianess Value: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, MCAN_getEndianVal(APP_MCAN_MODULE));
    UARTConfigPuts(uartBaseAddr, " \n", -1);
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(APP_MCAN_MODULE, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(APP_MCAN_MODULE))
    {}
    /* Initialize MCAN module */
    MCAN_init(APP_MCAN_MODULE, &initParams);
    /* Configure MCAN module */
    MCAN_config(APP_MCAN_MODULE, &configParams);
    /* Configure Bit timings */
    MCAN_setBitTime(APP_MCAN_MODULE, &bitTimes);
    /* Set Extended ID Mask */
    MCAN_setExtIDAndMask(APP_MCAN_MODULE, APP_MCAN_EXT_ID_AND_MASK);
    /* Configure Message RAM Sections */
    MCAN_msgRAMConfig(APP_MCAN_MODULE, &msgRAMConfigParams);
    /* Configure Standard ID filter element */
    MCAN_addStdMsgIDFilter(APP_MCAN_MODULE, 0U, &stdFiltelem);
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(APP_MCAN_MODULE, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(APP_MCAN_MODULE))
    {}
    return configStatus;
}

static void App_mcanIntr0ISR(void *handle)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(APP_MCAN_MODULE);
    MCAN_clearIntrStatus(APP_MCAN_MODULE, intrStatus);
    if (MCAN_INTR_SRC_TRANS_COMPLETE ==
        (intrStatus & MCAN_INTR_SRC_TRANS_COMPLETE))
    {
        gMcanIsrIntr0Flag = 0U;
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\nInterrupt Status: ", -1);
        UARTConfigPutHexNum(uartBaseAddr, intrStatus);
        UARTConfigPuts(uartBaseAddr, " \n", -1);
    }
}

static void App_mcanIntr1ISR(void *handle)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(APP_MCAN_MODULE);
    MCAN_clearIntrStatus(APP_MCAN_MODULE, intrStatus);
    if (MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG ==
        (intrStatus & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG))
    {
        gMcanIsrIntr1Flag = 0U;
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\nInterrupt Status: ", -1);
        UARTConfigPutHexNum(uartBaseAddr, intrStatus);
        UARTConfigPuts(uartBaseAddr, " \n", -1);
    }
}

static void App_mcanECCIntrISR(void *handle)
{
    MCAN_eccGetErrorStatus(APP_MCAN_MODULE, &gMcaneccErr);
    if (1U == gMcaneccErr.secErr)
    {
        MCAN_eccClearErrorStatus(APP_MCAN_MODULE, MCAN_ECC_ERR_TYPE_SEC);
        MCAN_eccWriteEOI(APP_MCAN_MODULE, MCAN_ECC_ERR_TYPE_SEC);
    }
    if (1U == gMcaneccErr.dedErr)
    {
        MCAN_eccClearErrorStatus(APP_MCAN_MODULE, MCAN_ECC_ERR_TYPE_DED);
        MCAN_eccWriteEOI(APP_MCAN_MODULE, MCAN_ECC_ERR_TYPE_DED);
    }
    UARTConfigPuts(uartBaseAddr, "ECC interrupt happened.\n", -1);
}

static void App_mcanTSIntrISR(void *handle)
{
    UARTConfigPuts(uartBaseAddr, "Time Stamp overflow happened.\n", -1);
}

static void App_mcanPrintTxMsg(const MCAN_TxBufElement *txMsg)
{
    uint32_t loopCnt;

    UARTConfigPuts(uartBaseAddr, "\nMessage ID: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->id);

    UARTConfigPuts(uartBaseAddr, "\nMessage Remote Transmission Request: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->rtr);

    UARTConfigPuts(uartBaseAddr, "\nMessage Extended Frame ID(0:11Bit ID/1:29bit ID): ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->xtd);

    UARTConfigPuts(uartBaseAddr,
        "\nMessage Error State Indicator(0:Error Active/1:Error Passive): ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->esi);

    UARTConfigPuts(uartBaseAddr, "\nMessage Data Length Code: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->dlc);

    UARTConfigPuts(uartBaseAddr, "\nMessage BRS: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->brs);

    UARTConfigPuts(uartBaseAddr, "\nMessage CAN FD format: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->fdf);

    UARTConfigPuts(uartBaseAddr, "\nMessage Store Tx Events: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->efc);

    UARTConfigPuts(uartBaseAddr, "\nMessage Marker: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, txMsg->mm);

    for (loopCnt = 0U; loopCnt < gMcanAppdataSize[txMsg->dlc]; loopCnt++)
    {
        UARTConfigPuts(uartBaseAddr, "\nMessage DataByte", -1);
        UARTConfigPutNum(uartBaseAddr, loopCnt);
        UARTConfigPuts(uartBaseAddr, ": ", -1);
        UARTConfigPutHexNum(uartBaseAddr, txMsg->data[loopCnt]);
    }
}

static void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg)
{
    uint32_t loopCnt;

    UARTConfigPuts(uartBaseAddr, "\nMessage ID: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->id);
    UARTConfigPuts(uartBaseAddr, "\nMessage Remote Transmission Request: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->rtr);
    UARTConfigPuts(uartBaseAddr, "\nMessage Extended Frame ID(0:11Bit ID/1:29bit ID): ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->xtd);
    UARTConfigPuts(uartBaseAddr, "\nMessage Error State Indicator(0:Error Active/1:Error Passive): ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->esi);
    UARTConfigPuts(uartBaseAddr, "\nMessage TimeStamp: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->rxts);
    UARTConfigPuts(uartBaseAddr, "\nMessage Data Length Code: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->dlc);
    UARTConfigPuts(uartBaseAddr, "\nMessage BRS: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->brs);
    UARTConfigPuts(uartBaseAddr, "\nMessage CAN FD format: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->fdf);
    UARTConfigPuts(uartBaseAddr, "\nMessage Filter Index: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->fidx);
    UARTConfigPuts(uartBaseAddr, "\nMessage Accept Non-matching Frame: ", -1);
    UARTConfigPutHexNum(uartBaseAddr, rxMsg->anmf);
    for (loopCnt = 0U; loopCnt < gMcanAppdataSize[rxMsg->dlc]; loopCnt++)
    {
        UARTConfigPuts(uartBaseAddr, "\nMessage DataByte", -1);
        UARTConfigPutNum(uartBaseAddr, loopCnt);
        UARTConfigPuts(uartBaseAddr, ": ", -1);
        UARTConfigPutHexNum(uartBaseAddr, rxMsg->data[loopCnt]);
    }
}

static void APP_mcanTxTest(MCAN_TxBufElement *txMsg)
{
    int32_t  configStatus = STW_EFAIL, testStatus = STW_SOK;
    uint32_t loopCnt      = 1U;
    MCAN_ProtocolStatus protStatus;

    /* Enable Interrupts */
    MCAN_enableIntr(APP_MCAN_MODULE, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_enableIntr(APP_MCAN_MODULE,
                    MCAN_INTR_SRC_RES_ADDR_ACCESS, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(APP_MCAN_MODULE,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_0);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(APP_MCAN_MODULE,
                        MCAN_INTR_LINE_NUM_0,
                        1U);
    /* Enable Transmission interrupt */
    configStatus = MCAN_txBufTransIntrEnable(APP_MCAN_MODULE,
                                             1U,
                                             (uint32_t)TRUE);
    for (loopCnt = 1U; loopCnt < 16U; loopCnt++)
    {
        txMsg->dlc = loopCnt;
        /* Write message to Msg RAM */
        MCAN_writeMsgRam(APP_MCAN_MODULE,
                         MCAN_MEM_TYPE_BUF,
                         1U,
                         txMsg);
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(APP_MCAN_MODULE, 1U);
        if (STW_SOK != configStatus)
        {
            UARTConfigPuts(uartBaseAddr, "\nError in Adding Transmission Request...\n", -1);
        }
        while (gMcanIsrIntr0Flag)
        {}
        gMcanIsrIntr0Flag = 1U;
        MCAN_getProtocolStatus(APP_MCAN_MODULE, &protStatus);
        /* Checking for Errors */
        if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
             (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
            ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
             (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
            (0U == protStatus.pxe))
        {
            UARTConfigPuts(uartBaseAddr,
                "\nMessage successfully transferred with payload Bytes:", -1);
            UARTConfigPutNum(uartBaseAddr, gMcanAppdataSize[txMsg->dlc]);
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\nError in transmission with payload Bytes:", -1);
            UARTConfigPutNum(uartBaseAddr, gMcanAppdataSize[txMsg->dlc]);
            testStatus = STW_EFAIL;
        }
    }
    if (STW_EFAIL == testStatus)
    {
        UARTConfigPuts(uartBaseAddr, "\nTx Test FAILED...\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\nTx Test PASSED...\n", -1);
    }
}

static void APP_mcanRxTest(const MCAN_TxBufElement *txMsg)
{
    uint32_t             loopCnt    = 1U, chkCnt = 0U, errFlag = 0U;
    int32_t              testStatus = STW_SOK;
    MCAN_RxBufElement    rxMsg;
    MCAN_RxNewDataStatus newDataStatus;
    MCAN_ErrCntStatus    errCounter;

    /* Enable Interrupts */
    MCAN_enableIntr(APP_MCAN_MODULE, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_enableIntr(APP_MCAN_MODULE,
                    MCAN_INTR_SRC_RES_ADDR_ACCESS, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(APP_MCAN_MODULE,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_1);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(APP_MCAN_MODULE,
                        MCAN_INTR_LINE_NUM_1,
                        1U);
    for (loopCnt = 1U; loopCnt < 16U; loopCnt++)
    {
        while (gMcanIsrIntr1Flag)
        {}
        gMcanIsrIntr1Flag = 1U;
        /* Checking for Errors */
        MCAN_getErrCounters(APP_MCAN_MODULE, &errCounter);
        if ((0U == errCounter.recErrCnt) &&
            (0U == errCounter.canErrLogCnt))
        {
            MCAN_getNewDataStatus(APP_MCAN_MODULE, &newDataStatus);
            MCAN_clearNewDataStatus(APP_MCAN_MODULE, &newDataStatus);
            MCAN_readMsgRam(APP_MCAN_MODULE,
                            MCAN_MEM_TYPE_BUF,
                            0U,
                            0U,
                            &rxMsg);
            errFlag = 0U;
            for (chkCnt = 0U; chkCnt < gMcanAppdataSize[rxMsg.dlc]; chkCnt++)
            {
                if (txMsg->data[chkCnt] != rxMsg.data[chkCnt])
                {
                    errFlag = 1U;
                    break;
                }
            }
            if (0U == errFlag)
            {
                UARTConfigPuts(uartBaseAddr,
                    "\nMessage successfully received with payload Bytes: ", -1);
                UARTConfigPutNum(uartBaseAddr, gMcanAppdataSize[rxMsg.dlc]);
            }
            else
            {
                UARTConfigPuts(uartBaseAddr,
                    "\nWrong data received in message with payload Bytes: ", -1);
                UARTConfigPutNum(uartBaseAddr, gMcanAppdataSize[rxMsg.dlc]);
                testStatus = STW_EFAIL;
            }
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\nError in reception with payload Bytes:", -1);
            UARTConfigPutNum(uartBaseAddr, gMcanAppdataSize[txMsg->dlc]);
            testStatus = STW_EFAIL;
        }
    }
    UARTConfigPuts(uartBaseAddr, "\nReceived last message with following details:", -1);
    App_mcanPrintRxMsg(&rxMsg);
    if (STW_EFAIL == testStatus)
    {
        UARTConfigPuts(uartBaseAddr, "\nRx Test FAILED...\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\nRx Test PASSED...\n", -1);
    }
}
