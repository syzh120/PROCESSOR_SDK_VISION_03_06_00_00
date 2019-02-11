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
 * main.c
 */

#include <stdint.h>
#include <stdio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_uart.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/****************************************************************************/
/*                      INTERNAL MACROS                                     */
/****************************************************************************/
/* EDMA3 Event queue number. */
#define EVT_QUEUE_NUM                       (0U)

/* PaRAM Set number for Dummy Transfer. */
#define DUMMY_CH_NUM                        (5U)

/* EDMA3 TPCC region. */
#define EDMA3_CC_REGION                         (1U)

/* EDMA3 interrupt number. */
#define EDMA3_CC_XFER_COMPLETION_INT            (34U)
#define XBAR_INST_CC_XFER_COMPLETION            (CSL_XBAR_INST_IPU1_IRQ_34)
#define XBAR_INTR_SOURCE_CC_XFER_COMPLETION     (CSL_XBAR_EDMA_TPCC_IRQ_REGION1)
/* EDMA3 error interrupt number. */
#define EDMA3_CC_XFER_ERROR_INT                 (35U)
#define XBAR_INST_CC_XFER_ERROR                 (CSL_XBAR_INST_IPU1_IRQ_34)
#define XBAR_INTR_SOURCE_CC_XFER_ERROR          (CSL_XBAR_EDMA_TPCC_IRQ_REGION1)

/******************* Transmit related definitions  **************************/
/*
** Transmit DMA Threshold Value. This is set in TX_DMA_THRESHOLD register.
*/
#define TX_DMA_THRESHOLD                    (5U)

/*
** Transmit Trigger Space value. Use this if TX Trigger Level granularity
** is selected to be 1.
*/
#define TX_TRIGGER_SPACE_GRAN_1             (8U)

/* Number of bytes transmitted by EDMA per TX event sent by UART. */
#define TX_BYTES_PER_EVENT                  (8U)

/******************* Receive related definitions  ***************************/
/* Receiver Buffer Size. */
#define RX_BUFFER_SIZE                      (50U)

/* Receive DMA Threshold Value. */
#define RX_DMA_THRESHOLD                    (8U)

/* Number of bytes to be received from the user. */
#define NUM_RX_BYTES              (8)

/******************* DMA XBAR related definitions  ***************************/
/* DMA XBAR Instance for UART1/UART3 Tx/RX. Refer TRM for DMA XBAR instance
 *numbers.*/
/* Wrapper Definitions. */
#define EDMA3_UART_TX_CHA_NUM               (26U)
#define EDMA3_UART_RX_CHA_NUM               (27U)

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#define DMA_XBAR_INST_TX                    CSL_XBAR_INST_DMA_SYSTEM_DREQ_26
#define DMA_XBAR_INST_RX                    CSL_XBAR_INST_DMA_SYSTEM_DREQ_27
#define DMA_XBAR_INST_TX_SRC                CSL_XBAR_DMA_UART1_DREQ_TX
#define DMA_XBAR_INST_RX_SRC                CSL_XBAR_DMA_UART1_DREQ_RX
#elif defined (SOC_TDA3XX)
#define DMA_XBAR_INST_TX                    CSL_XBAR_INST_DMA_EDMA_DREQ_26
#define DMA_XBAR_INST_RX                    CSL_XBAR_INST_DMA_EDMA_DREQ_27
#define DMA_XBAR_INST_TX_SRC                CSL_XBAR_DMA_UART3_DREQ_TX
#define DMA_XBAR_INST_RX_SRC                CSL_XBAR_DMA_UART3_DREQ_RX
#endif

/****************************************************************************/
/*                      LOCAL FUNCTION PROTOTYPES                           */
/****************************************************************************/
static void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum);
static void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum);

static void Edma3INTCConfigure(void);
static void UartInitialize(void);
static void UartFIFOConfigure(void);
static void UartBaudRateSet(void);
static void callback(uint32_t tccNum);
static void Edma3CompletionIsr(void *handle);
static void TxDummyPaRAMConfEnable(void);
static void Edma3ErrorIsr(void *handle);
static void EdmaEvtConfigure(void);
static void padConfig_prcmEnable(void);
static void PlatformEDMAWkupDepEnable(void);

/****************************************************************************/
/*                      GLOBAL VARIABLES                                    */
/****************************************************************************/
static void(*cb_Fxn[EDMA3_NUM_TCC]) (uint32_t tcc);
unsigned char     intent[] =
    "The application echoes the characters that you type on the console.\r\n";
unsigned char     welcome[]  = "StarterWare UART DMA application.\r\n";
unsigned char     enter[]    = "Please Enter 08 bytes from keyboard.\r\n";
volatile uint32_t clBackFlag = 0;

unsigned char     rxBuffer[RX_BUFFER_SIZE];
/*
** Transmit Trigger Space value. This is applicable only when UART FIFO mode
** is used. Refer to the comments of the API UARTFIFOConfig() to find the
** possible values of TX Trigger Space.
*/
uint32_t          txTrigSpace = TX_TRIGGER_SPACE_GRAN_1;

/*
** Number of bytes transmitted by EDMA per TX event sent by UART.
** In UART FIFO mode, this should be equal to the TX Trigger Space value.
*/
uint32_t          txBytesPerEvent = TX_BYTES_PER_EVENT;

/*
** Receive DMA Thresold Level. This applies to both UART FIFO and Non-FIFO
** modes of operation. For FIFO mode, refer to the comments of the API
** UARTFIFOConfig() to find the possible values of RX Trigger Level.
** For Non-FIFO mode, this value is 1.
*/
uint32_t          rxTrigLevel = RX_DMA_THRESHOLD;

/* Transmit DMA Threshold Level. This is set in TX_DMA_THRESHOLD register. */
uint32_t          txThreshLevel = TX_DMA_THRESHOLD;
uint32_t          uartBaseAddr;
/****************************************************************************/
/*                   LOCAL FUNCTION DEFINITIONS                             */
/****************************************************************************/

static void padConfig_prcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,
        0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,
        0x00000000);
#endif
#if defined (SOC_TDA3XX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,
        0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,
        0x00000001);
#endif
}

static void PlatformEDMAWkupDepEnable(void)
{
    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC1_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC1_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC2_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC2_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPCC_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPCC_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }
}

int main(void)
{
    uint32_t numByteChunks           = 0;
    unsigned char           *pBuffer = NULL;
    uint32_t remainBytes = 0;

    uartBaseAddr = SOC_UART1_BASE;

#if defined (SOC_TDA3XX)
    uartBaseAddr = SOC_UART3_BASE;
#endif

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    /* Do EDMA init Done once in the beginning of application */
    EDMAsetRegion(EDMA3_CC_REGION);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, EVT_QUEUE_NUM);

    /* Configuring the AINTC to receive EDMA3 interrupts. */
    Edma3INTCConfigure();

    /* Initializing the UART for use. */
    UartInitialize();

    /* Configure the DMA crossbar for UART TX and RX events. */
    EdmaEvtConfigure();

    /* Request DMA Channel and TCC for UART Transmit*/
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_TX_CHA_NUM, EDMA3_UART_TX_CHA_NUM,
                        EVT_QUEUE_NUM);

    /* Registering Callback Function for TX*/
    cb_Fxn[EDMA3_UART_TX_CHA_NUM] = &callback;

    /* Request DMA Channel and TCC for UART Receive */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_RX_CHA_NUM, EDMA3_UART_RX_CHA_NUM,
                        EVT_QUEUE_NUM);

    /* Registering Callback Function for RX*/
    cb_Fxn[EDMA3_UART_RX_CHA_NUM] = &callback;

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof (welcome) - 1) / txBytesPerEvent;
    remainBytes   = (sizeof (welcome) - 1) % txBytesPerEvent;

    /* Configuring EDMA PaRAM sets to transmit 'welcome' message. */
    UARTTxEDMAPaRAMSetConfig(welcome,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = welcome + (sizeof (welcome) - 1) - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof (intent) - 1) / txBytesPerEvent;
    remainBytes   = (sizeof (intent) - 1) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring EDMA PaRAM sets to transmit data. */
    UARTTxEDMAPaRAMSetConfig(intent,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = intent + (sizeof (intent) - 1) - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof (enter) - 1) / txBytesPerEvent;
    remainBytes   = (sizeof (enter) - 1) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring EDMA PaRAM sets to transmit 'enter' message. */
    UARTTxEDMAPaRAMSetConfig(enter,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = enter + (sizeof (enter) - 1) - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /********************* Receiving Data from User *************************/

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring the PaRAM set for reception. */
    UARTRxEDMAPaRAMSetConfig(rxBuffer,
                             NUM_RX_BYTES,
                             EDMA3_UART_RX_CHA_NUM,
                             0xFFFF,
                             EDMA3_UART_RX_CHA_NUM);

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_UART_RX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /******************* Echoing received bytes *****************************/

    numByteChunks = (NUM_RX_BYTES) / txBytesPerEvent;
    remainBytes   = (NUM_RX_BYTES) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring the PaRAM set to transmit the bytes that were received. */
    UARTTxEDMAPaRAMSetConfig(rxBuffer,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = rxBuffer + NUM_RX_BYTES - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /******************* Freeing of allocated channels **********************/

    /* Free EDMA3 Channels for TX and RX */
    EDMA3FreeChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                     EDMA3_UART_TX_CHA_NUM, EDMA3_TRIG_MODE_EVENT,
                     EDMA3_UART_TX_CHA_NUM, EVT_QUEUE_NUM);

    EDMA3FreeChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                     EDMA3_UART_RX_CHA_NUM, EDMA3_TRIG_MODE_EVENT,
                     EDMA3_UART_RX_CHA_NUM, EVT_QUEUE_NUM);

    return 0;
}

/*
** This function configures and sets the EDMA PaRAM set values for
** transferring data to UART TX FIFO.
*/
static void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    /* Fill the PaRAM Set with transfer specific information */
    paramSet.srcAddr  = (uint32_t) txBuffer;
    paramSet.destAddr = (uint32_t) uartBaseAddr;

    paramSet.aCnt    = (uint32_t) 1;
    paramSet.bCnt    = (uint32_t) txBytesPerEvent;
    paramSet.cCnt    = (uint32_t) (length / txBytesPerEvent);
    paramSet.srcBIdx = (uint32_t) 1;
    paramSet.srcCIdx = (uint32_t) txBytesPerEvent;

    /* The destination indexes should not increment since it is a h/w register.
    **/
    paramSet.destBIdx = (uint32_t) 0;
    paramSet.destCIdx = (uint32_t) 0;

    paramSet.linkAddr   = (uint32_t) linkAddr;
    paramSet.bCntReload = (uint32_t) 0;

    /* OPT PaRAM entries. */
    paramSet.opt = (uint32_t) 0x0;

    /* Source and Destination addressing modes are Incremental. */

    /* AB Synchronized Transfer. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_SYNCDIM_SHIFT);

    /* Setting the Transfer Complete Code(TCC). */
    paramSet.opt |=
        ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);

    /* Enabling the Completion Interrupt. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRAM Set */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, chNum, &paramSet);
}

/*
** This function configures and sets the EDMA PaRAM set values for
** receiving data from UART RX FIFO.
*/
static void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    /* Fill the PaRAM Set with transfer specific information */
    paramSet.srcAddr  = (uint32_t) uartBaseAddr;
    paramSet.destAddr = (uint32_t) rxBuffer;

    paramSet.aCnt     = (uint32_t) 1;
    paramSet.bCnt     = (uint32_t) (rxTrigLevel);
    paramSet.cCnt     = (uint32_t) (length / rxTrigLevel);
    paramSet.destBIdx = (uint32_t) 1;
    paramSet.destCIdx = (uint32_t) rxTrigLevel;

    paramSet.srcBIdx = (uint32_t) 0;
    paramSet.srcCIdx = (uint32_t) 0;

    paramSet.linkAddr   = (uint32_t) linkAddr;
    paramSet.bCntReload = (uint32_t) 0;

    /* OPT PaRAM Entries. */
    paramSet.opt = (uint32_t) 0x0;

    /* Source and Destination addressing modes are Incremental. */

    /* Enable AB Synchronized Transfer. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_SYNCDIM_SHIFT);

    /* Setting the Transfer Complete Code(TCC). */
    paramSet.opt |=
        ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);

    /* Enabling the Completion Interrupt. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRAM Set */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, chNum, &paramSet);
}

/*
** This configures the PaRAM set for the Dummy Transfer.
*/

static void TxDummyPaRAMConfEnable(void)
{
    EDMA3CCPaRAMEntry dummyPaRAMSet;

    dummyPaRAMSet.aCnt       = 1;
    dummyPaRAMSet.bCnt       = 0;
    dummyPaRAMSet.cCnt       = 0;
    dummyPaRAMSet.srcAddr    = 0;
    dummyPaRAMSet.destAddr   = 0;
    dummyPaRAMSet.srcBIdx    = 0;
    dummyPaRAMSet.destBIdx   = 0;
    dummyPaRAMSet.srcCIdx    = 0;
    dummyPaRAMSet.destCIdx   = 0;
    dummyPaRAMSet.linkAddr   = 0xFFFF;
    dummyPaRAMSet.bCntReload = 0;
    dummyPaRAMSet.opt        = 0;

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, DUMMY_CH_NUM, &dummyPaRAMSet);
}

/*
** EDMA Completion Interrupt Service Routine(ISR).
*/
static void Edma3CompletionIsr(void *handle)
{
    volatile uint32_t pendingIrqs;
    uint32_t          index = 1;
    uint32_t          count = 0;

    if (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT))
    {
        /*
        ** Wait for a finite time to monitor the EDMA Completion Interrupt
        ** status.
        */
        while ((count < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (index != 0U))
        {
            index = 0;

            /* Get the Interrupt status. */
            pendingIrqs = EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT);
            while (pendingIrqs)
            {
                if ((pendingIrqs & 1U) == TRUE)
                {
                    /* Clear the interrupt status. */
                    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, index);

                    (*cb_Fxn[index])(index);
                }
                ++index;
                pendingIrqs >>= 1U;
            }
            count++;
        }
    }
}

/*
** This function is used as a callback from EDMA3 Completion Handler.
*/
static void callback(uint32_t tccNum)
{
    /* Disabling DMA Mode of operation in UART. */
    UARTDMADisable(uartBaseAddr);

    /* Disabling DMA transfer on the specified channel. */
    EDMA3DisableTransfer(SOC_EDMA_TPCC_BASE_VIRT, tccNum, EDMA3_TRIG_MODE_EVENT);

    clBackFlag = 1;
}

/*
** EDMA Error Interrupt Service Routine(ISR).
*/

static void Edma3ErrorIsr(void *handle)
{
    volatile uint32_t pendingIrqs = 0;
    uint32_t          evtqueNum   = 0;
    uint32_t          index       = 1;
    uint32_t          Cnt         = 0;

    if ((0 != EDMA3GetErrIntrStatus(SOC_EDMA_TPCC_BASE_VIRT)) ||
        (0 != (EDMA3GetCCErrStatus(SOC_EDMA_TPCC_BASE_VIRT))))
    {
        /* Loop for EDMA3CC_ERR_HANDLER_RETRY_COUNT number of time, breaks
         * when no pending interrupt is found */
        while ((Cnt < EDMA3CC_ERR_HANDLER_RETRY_COUNT) && (index != 0U))
        {
            index       = 0U;
            pendingIrqs = EDMA3GetErrIntrStatus(SOC_EDMA_TPCC_BASE_VIRT);

            while (pendingIrqs)
            {
                /*Process all the pending interrupts*/
                if ((pendingIrqs & 1U) == TRUE)
                {
                    /* Writing to EMCR to clear the corresponding EMR bits.
                     * Also clearing any Secondary events in SER. */
                    EDMA3ClrMissEvt(SOC_EDMA_TPCC_BASE_VIRT, index);
                }
                ++index;
                pendingIrqs >>= 1U;
            }
            index = 0U;

            pendingIrqs = EDMA3GetCCErrStatus(SOC_EDMA_TPCC_BASE_VIRT);
            if (pendingIrqs != 0U)
            {
                /* Process all the pending CC error interrupts. */
                /* Queue threshold error for different event queues. */
                for (evtqueNum = 0U; evtqueNum < EDMA3_0_NUM_EVTQUE;
                     evtqueNum++)
                {
                    if ((pendingIrqs & (1U << evtqueNum)) != 0U)
                    {
                        /* Clear the error interrupt. */
                        EDMA3ClrCCErr(SOC_EDMA_TPCC_BASE_VIRT, (1U << evtqueNum));
                    }
                }

                /* Transfer completion code error. */
                if ((pendingIrqs & (1 << EDMA_TPCC_CCERR_TCERR_SHIFT)) != 0U)
                {
                    EDMA3ClrCCErr(SOC_EDMA_TPCC_BASE_VIRT,
                                  (0x01U << EDMA_TPCC_CCERR_TCERR_SHIFT));
                }
                ++index;
            }

            Cnt++;
        }
    }
}

/*
** This function initializes the UART instance for use.
*/
static void UartInitialize(void)
{
    /* Performing a module reset. */
    UARTModuleReset(uartBaseAddr);

    /* Performing FIFO configurations. */
    UartFIFOConfigure();

    /* Selecting the method of setting the Transmit DMA Threshold value. */
    UARTTxDMAThresholdControl(uartBaseAddr, UART_TX_DMA_THRESHOLD_REG);

    /* Configuring the Transmit DMA Threshold value. */
    UARTTxDMAThresholdValConfig(uartBaseAddr, txThreshLevel);

    /* Performing Baud Rate settings. */
    UartBaudRateSet();

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(uartBaseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(uartBaseAddr,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(uartBaseAddr);

    /* Disabling Break Control. */
    UARTBreakCtl(uartBaseAddr, UART_BREAK_COND_DISABLE);

    /* Switching to UART16x operating mode. */
    UARTOperatingModeSelect(uartBaseAddr, UART16x_OPER_MODE);
}

/*
** A wrapper function performing FIFO configurations.
*/
static void UartFIFOConfigure(void)
{
    uint32_t fifoConfig = 0;

    /*
    ** Transmitter Trigger Level Granularity is 1.
    ** Receiver Trigger Level Granularity is 1.
    ** Transmit Trigger Space set using 'txTrigSpace'.
    ** Receive Trigger level set using 'rxTrigLevel'.
    ** Clear the Trasnmit FIFO.
    ** Clear the Receive FIFO.
    ** DMA Mode enabling shall happen through SCR register.
    ** DMA Mode 1 is enabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_1,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  txTrigSpace,
                                  rxTrigLevel,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_1_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(uartBaseAddr, fifoConfig);
}

/*
** A wrapper function performing Baud Rate settings.
*/
static void UartBaudRateSet(void)
{
    uint32_t divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE_115200,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(uartBaseAddr, divisorValue);
}

/*
** This function configures the AINTC to receive EDMA3 interrupts.
*/
static void Edma3INTCConfigure(void)
{
    /* Crossbar registers are already unlocked, so connect directly */
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,
                            XBAR_INST_CC_XFER_COMPLETION,
                            XBAR_INTR_SOURCE_CC_XFER_COMPLETION);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,
                            XBAR_INST_CC_XFER_ERROR,
                            XBAR_INTR_SOURCE_CC_XFER_ERROR);

    /* Initializing the ARM Interrupt Controller. */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering EDMA3 Channel Controller 0 transfer completion interrupt.  */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT,
                     (IntrFuncPtr) Edma3CompletionIsr,
                     NULL);

    /* Setting the priority for EDMA3CC0 completion interrupt in AINTC. */
    Intc_IntPrioritySet(EDMA3_CC_XFER_COMPLETION_INT, 1, 0);

    /* Enabling the EDMA3CC0 completion interrupt in AINTC. */
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT);

    /* Registering EDMA3 Channel Controller 0 Error Interrupt. */
    Intc_IntRegister(EDMA3_CC_XFER_ERROR_INT, (IntrFuncPtr) Edma3ErrorIsr, NULL);

    /* Setting the priority for EDMA3CC0 Error interrupt in AINTC. */
    Intc_IntPrioritySet(EDMA3_CC_XFER_ERROR_INT, 1, 0);

    /* Enabling the EDMA3CC0 Error interrupt in AINTC. */
    Intc_SystemEnable(EDMA3_CC_XFER_ERROR_INT);
}

/*
** This function configures the DMA crossbar for UART TX and RX events.
*/
static void EdmaEvtConfigure(void)
{
    CSL_xbarDmaConfigure(CSL_XBAR_DMA_CPU_ID_EDMA, DMA_XBAR_INST_TX,
                            DMA_XBAR_INST_TX_SRC);
    CSL_xbarDmaConfigure(CSL_XBAR_DMA_CPU_ID_EDMA, DMA_XBAR_INST_RX,
                            DMA_XBAR_INST_RX_SRC);
}

/******************************** End of file *******************************/
