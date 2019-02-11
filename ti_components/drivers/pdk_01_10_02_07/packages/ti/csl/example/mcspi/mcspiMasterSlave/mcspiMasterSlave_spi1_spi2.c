 /*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   mcspiMasterSlave_spi1_spi2.c
 *
 *  \brief This file contains the Master application which demonstrates McSPI master
 *         mode of operation with default configuration settings.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <stdio.h>
#include <ti/csl/csl_mcspi.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/common/inc/app_utils.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define HSI2C_SLAVE_ADDR 0x21
#define SEL_UART3_SPI2   0x0E
#define UART_SEL1_3      0x0C
#define I2C_INT_NUM      56

#define MCSPI_POLLED_MODE      0

#define HSI2C_EN_SPI2      ((uint8_t) 0x40U)
#define HSI2C_ZERO      ((uint8_t) 0x00U)

#define MCSPI_OUT_FREQ              (1000000U)
#define MCSPI_IN_CLK                (48000000U)
#define McSPI_DATA_COUNT            256U // Data Count Transaction

#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
#define MCSPI1_BASE_ADDRESS         (CSL_MPU_MCSPI1_REGS)
#define MCSPI2_BASE_ADDRESS         (CSL_MPU_MCSPI2_REGS)
#undef SOC_I2C1_BASE
#define SOC_I2C1_BASE CSL_MPU_I2C1_REGS
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define MCSPI1_BASE_ADDRESS         (SOC_MCSPI1_BASE)
#define MCSPI2_BASE_ADDRESS         (SOC_MCSPI2_BASE)
#endif

/** \brief EDMA3 channel for SPI1 Channel 0 Tx and Rx*/
#define MCSPI1_TX_EVENT                  (34U)
#define MCSPI1_RX_EVENT                  (35U)

/** \brief EDMA3 channel for SPI2 Channel 0 Tx and Rx*/
#define MCSPI2_TX_EVENT                  (42U)
#define MCSPI2_RX_EVENT                  (43U)

/** \brief MCSPI Tx/Rx buffer base address */
#define MCSPI1_TX0_REG                   (SOC_MCSPI1_BASE + (0x138U))
#define MCSPI1_RX0_REG                   (SOC_MCSPI1_BASE + (0x13CU))

#define MCSPI2_TX0_REG                   (SOC_MCSPI2_BASE + (0x138U))
#define MCSPI2_RX0_REG                   (SOC_MCSPI2_BASE + (0x13CU))

/** \brief MCSPI Channel number*/
#define MCSPI_CH_NUM                    (0U)

#define EVT_QUEQUE_NUM                  (0U)
#define DUMMY_CH_NUM                    (5U)

#define EDMA_TDA2XX_U_BASE              (SOC_EDMA_TPCC_BASE_VIRT)

#define EDMA3CC_PaRAM_BASE            (0x4000)
#define EDMA3CC_OPT(n)                (EDMA3CC_PaRAM_BASE + 0x0 + (0x20 * n))

#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (35U)

#define EDMA3_ERROR_INT_A15                              (14)
#define EDMA3_ERROR_INT_A15_1                            (15)
#define EDMA3_ERROR_INT_M4                               (36)
#define EDMA3_ERROR_INT_M4_1                             (37)

#define EDMA3_CC_REGION_A15                             (0U)
#define EDMA3_CC_REGION_M4                              (1U)

#define MCSPI_MASTERSLAVE_POLLED_MODE_TEST   ('1')
#define MCSPI_MASTERSLAVE_DMA_MODE_TEST      ('2')
#define EXIT(opt)                   (('x' == opt) || ('X' == opt))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t dataToSlave;

uint32_t          gChNum  = 0;
uint32_t          length = 0;
uint8_t           dataFromSlave;
uint8_t           rxBuffer[McSPI_DATA_COUNT + 10];
uint8_t           txBuffer[McSPI_DATA_COUNT + 10];
uint8_t           txSlvBuffer[McSPI_DATA_COUNT + 10];
uint8_t           rxSlvBuffer[McSPI_DATA_COUNT + 10];

static void(*cb_Fxn[EDMA3_NUM_TCC]) (uint32_t tcc,
                                     uint32_t status);

volatile uint8_t  flagTx    = 0;
volatile uint8_t  flagRx    = 0;
volatile uint8_t  flagSlvTx = 0;
volatile uint8_t  flagSlvRx = 0;
char              gMainMenuOption;

/*To use UARTConfigPuts function for prints*/
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t uartBaseAddr = CSL_MPU_UART1_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void McSPI1SetUp(void);
static void McSPI2SetUp(void);
static void McSPIMSTransfer(uint16_t length);
static void McSPIVerifyData(void);
static void McSPIInitializeBuffers(void);
static void sampleDelay(int32_t delay);
static void McSPIMSPolledModeTransfer(uint16_t length);
static void McSPIMasterSlaveAppTest(void);
static void mainMenu(char *option);
static void McSPIConfigureDma(uint32_t length);

static void McSpi1TxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength);
static void McSpi1RxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength,
                                 uint32_t destBidxFlag);
static void McSpi2TxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength);
static void McSpi2RxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength,
                                 uint32_t destBidxFlag);

static void CallBack_McSPI1(uint32_t tccNum, uint32_t status);
static void CallBack_McSPI2(uint32_t tccNum, uint32_t status);

static void TxDummyPaRAMConfEnable(void);
static void Edma3ErrorHandlerIsr_McSPI1(void *dummy);
static void Edma3ErrorHandlerIsr_McSPI2(void *dummy);

static void Edma3ComplHandlerIsr(void *dummy);

static void RequestEDMA3Channels(void);
static void EDMA3IntConfigure(void);
static void EDMA3Initialize(void);

void padConfig_prcmEnable();

void SetupI2C(void);
void SetupI2CTransmit(void);
uint32_t I2CRead();
void configure_board_mux();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /* Power on SPI2*/
    HW_WR_REG32(0x4a0097f8, 0x02);
    while (HW_RD_REG32(0x4a0097f8) != 0x02U)
        {
            ;
        }
    /*Pad configurations */
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_SCLK,0x000C0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_D1,0x000C0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_D0,0x000C0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_CS0,0x00060000);
#if defined (SOC_AM574x) || defined (SOC_AM572x)
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_CS1,0x00060000);
#endif
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI2_SCLK,0x000C0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI2_D1,0x000C0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI2_D0,0x000C0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_SPI2_CS0,0x00060000);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /* Power on SPI2*/
    HW_WR_REG32(0x4a0097f8, 0x02);
    while (HW_RD_REG32(0x4a0097f8) != 0x02U)
        {
            ;
        }
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI1_SCLK,0x000C0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI1_D1,0x000C0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI1_D0,0x000C0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI1_CS0,0x00060000);
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI1_CS1,0x00060000);
#endif
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI2_SCLK,0x000C0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI2_D1,0x000C0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI2_D0,0x000C0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_SPI2_CS0,0x00060000);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*MCSPI1 prcm*/
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL, 0x02);
    while (HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL) !=
           0x02U)
        {
            ;
        }
    /*MCSPI2 prcm*/
     HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL, 0x02);
    while (HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL) !=
           0x02U)
        {
            ;
        }
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_TXD,0x00000000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_D0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_D1,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI2_CS0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI2_SCLK,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI2_D0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI2_D1,0x00040000);
#endif
}
static void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}

int main(void)
{

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    AppUtils_defaultInit();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM571x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
   configure_board_mux();
#endif

    UARTConfigPuts(uartBaseAddr,"\nMasterSlave (SPI1 to SPI2) Application Started",-1);
    UARTConfigPuts(uartBaseAddr,"\nConnect McSPI1 and McSPI2 instances spi pins",-1);
    UARTConfigPuts(uartBaseAddr,"\nThe Mode of transfer is Polled Mode",-1);

    while (1)
    {
        mainMenu(&gMainMenuOption);
		if ((MCSPI_MASTERSLAVE_POLLED_MODE_TEST == gMainMenuOption) ||
            (MCSPI_MASTERSLAVE_DMA_MODE_TEST == gMainMenuOption))
        {
            McSPIMasterSlaveAppTest();
        }
		else
        {
            UARTConfigPuts(uartBaseAddr,"\r\n MCSPI MasterSlave(SPI1 to SPI2) Application Test exiting...", -1);
            break;
        }
    }

    return 0;
}

static void McSPIMasterSlaveAppTest(void)
{
    if (MCSPI_MASTERSLAVE_POLLED_MODE_TEST == gMainMenuOption)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n MCSPI MasterSlave Polled Mode Test ", -1);
    }
    if (MCSPI_MASTERSLAVE_DMA_MODE_TEST == gMainMenuOption)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n MCSPI MasterSlave DMA Mode Test", -1);

#if defined (__ARM_ARCH_7A__)
        EDMAsetRegion(EDMA3_CC_REGION_A15);
#endif
#if defined (__TI_ARM_V7M4__)
        EDMAsetRegion(EDMA3_CC_REGION_M4);
#endif

        EDMA3Init(EDMA_TDA2XX_U_BASE, 0);

        /* Initialize the EDMA3 instance.*/
        EDMA3Initialize();

        /* Request EDMA3CC for Tx and Rx channels for SPI0. */
        RequestEDMA3Channels();
    }

    /* Do the necessary set up configurations for McSPI.*/
    McSPI1SetUp();
    McSPI2SetUp();

    McSPIInitializeBuffers();
    if (MCSPI_MASTERSLAVE_DMA_MODE_TEST == gMainMenuOption)
    {
        McSPIConfigureDma(McSPI_DATA_COUNT);
    }
    McSPIMSTransfer(McSPI_DATA_COUNT);

    /* Verify whether the data written by Master and the one read by
     * Slave are Equal */
    McSPIVerifyData();
}

void configure_board_mux()
{
    uint32_t i2cReadValue    = 0;
    uint32_t verifyReadValue = 0;
    /* In order to select UART3 set UART_SEL1_3 pin to low
     * and SEL_UART3_SPI2 pin to low using I2C */

    /* Set up I2C communication with I/O expander U57 using I2C1 */
    SetupI2C();

    /* Read the pins of I/O expander */
    i2cReadValue = I2CRead();

    /* To select SPI2 P16 (Bit No: 14 should be 1 */
    if ((i2cReadValue & (0x1 << 14)) == 0)
    {
        dataToSlave = i2cReadValue | (0x1 << 14);
        SetupI2CTransmit();
        verifyReadValue = I2CRead();
        if ((verifyReadValue & (0x1 << 14)) == 0)
        {
            UARTConfigPuts(uartBaseAddr,"\nSetting SEL_UART3_SPI2 to High to select SPI2 Failed",-1);
        }
    }
}

/*
** This function will call the necessary McSPI APIs which will configure the
** McSPI controller.
*/
static void McSPI1SetUp(void)
{
    uint32_t status = 1U; // FALSE

    /* Reset the McSPI instance.*/
    McSPIReset(MCSPI1_BASE_ADDRESS);

    /* CLOCKACTIVITY bit - OCP and Functional clocks are maintained           */
    /* SIDLEMODE     bit - Ignore the idle request and configure in normal mode
     */
    /* AUTOIDLE      bit - Disable (OCP clock is running free, no gating)     */
    MCSPISysConfigSetup(MCSPI1_BASE_ADDRESS, MCSPI_CLOCKS_OCP_ON_FUNC_ON,
                        MCSPI_SIDLEMODE_NO, MCSPI_WAKEUP_DISABLE,
                        MCSPI_AUTOIDLE_OFF);

    /* Enable chip select pin.*/
    McSPICSEnable(MCSPI1_BASE_ADDRESS);

    /* Enable master mode of operation.*/
    McSPIMasterModeEnable(MCSPI1_BASE_ADDRESS);

    /* Perform the necessary configuration for master mode. */
    status = McSPIMasterModeConfig(MCSPI1_BASE_ADDRESS, MCSPI_SINGLE_CH,
                                   MCSPI_TX_RX_MODE,
                                   MCSPI_DATA_LINE_COMM_MODE_6,
                                   gChNum);

    if (0 == status)
    {
        UARTConfigPuts(uartBaseAddr,"\nMcSPI1 - Communication not supported by SPIDAT[1:0]",-1);
    }

    /* Configure the McSPI bus clock depending on clock mode. */
    McSPIClkConfig(MCSPI1_BASE_ADDRESS, MCSPI_IN_CLK, MCSPI_OUT_FREQ, gChNum,
                   MCSPI_CLK_MODE_0);

    /* Configure the word length.*/
    McSPIWordLengthSet(MCSPI1_BASE_ADDRESS, MCSPI_WORD_LENGTH(8), gChNum);

    /* Set polarity of SPIEN to low.*/
    McSPICSPolarityConfig(MCSPI1_BASE_ADDRESS,
                          (MCSPI_CH0CONF_EPOL_ACTIVELOW <<
                           MCSPI_CH0CONF_EPOL_SHIFT), gChNum);

    /* Enable the transmitter FIFO of McSPI peripheral.*/
    McSPITxFIFOConfig(MCSPI1_BASE_ADDRESS, MCSPI_TX_FIFO_ENABLE, gChNum);

    /* Enable the receiver FIFO of McSPI peripheral.*/
    McSPIRxFIFOConfig(MCSPI1_BASE_ADDRESS, MCSPI_RX_FIFO_ENABLE, gChNum);
}

/*
** This function will call the necessary McSPI APIs which will configure the
** McSPI controller.
*/
static void McSPI2SetUp(void)
{
    uint32_t status = 1U; // FALSE

    /* Reset the McSPI instance.*/
    McSPIReset(MCSPI2_BASE_ADDRESS);

    /* CLOCKACTIVITY bit - OCP and Functional clocks are maintained           */
    /* SIDLEMODE     bit - Ignore the idle request and configure in normal mode
     */
    /* AUTOIDLE      bit - Disable (OCP clock is running free, no gating)     */
    MCSPISysConfigSetup(MCSPI2_BASE_ADDRESS, MCSPI_CLOCKS_OCP_ON_FUNC_ON,
                        MCSPI_SIDLEMODE_NO, MCSPI_WAKEUP_DISABLE,
                        MCSPI_AUTOIDLE_OFF);

    /* Enable chip select pin.*/
    McSPICSEnable(MCSPI2_BASE_ADDRESS);

    /* Enable slave mode of operation.*/
    McSPISlaveModeEnable(MCSPI2_BASE_ADDRESS);

    /* Configure the Pin Direction.*/
    status = MCSPIPinDirSet(MCSPI2_BASE_ADDRESS, MCSPI_TX_RX_MODE,
                            MCSPI_DATA_LINE_COMM_MODE_6, gChNum);

    if (1 == status)
    {
        UARTConfigPuts(uartBaseAddr,"\nMcSPI2 - Communication not supported by SPIDAT[1:0]", -1);
    }

    /* Configure the word length.*/
    McSPIWordLengthSet(MCSPI2_BASE_ADDRESS, MCSPI_WORD_LENGTH(8), gChNum);

    /* Set polarity of SPIEN to low.*/
    McSPICSPolarityConfig(MCSPI2_BASE_ADDRESS,
                          (MCSPI_CH0CONF_EPOL_ACTIVELOW <<
                           MCSPI_CH0CONF_EPOL_SHIFT), gChNum);

    /* Enable the transmitter FIFO of McSPI peripheral.*/
    McSPITxFIFOConfig(MCSPI2_BASE_ADDRESS, MCSPI_TX_FIFO_ENABLE, gChNum);

    /* Enable the receiver FIFO of McSPI peripheral.*/
    McSPIRxFIFOConfig(MCSPI2_BASE_ADDRESS, MCSPI_RX_FIFO_ENABLE, gChNum);
}

static void McSPIConfigureDma(uint32_t length)
{
    /* DMA PaRAM Configuration for McSPI1 */
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpi1TxEdmaParamSet(MCSPI1_TX_EVENT, MCSPI1_TX_EVENT, txBuffer,
                         length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpi1RxEdmaParamSet(MCSPI1_RX_EVENT, MCSPI1_RX_EVENT, rxBuffer,
                         length, TRUE);

    /* DMA PaRAM Configuration for McSPI2 */
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpi2TxEdmaParamSet(MCSPI2_TX_EVENT, MCSPI2_TX_EVENT, txSlvBuffer,
                         length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpi2RxEdmaParamSet(MCSPI2_RX_EVENT, MCSPI2_RX_EVENT, rxSlvBuffer,
                         length, TRUE);

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI2_TX_EVENT] = &CallBack_McSPI2;
    cb_Fxn[MCSPI2_RX_EVENT] = &CallBack_McSPI2;

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI1_TX_EVENT] = &CallBack_McSPI1;
    cb_Fxn[MCSPI1_RX_EVENT] = &CallBack_McSPI1;

    /* Set the word count field with the data length to be transferred.*/
    McSPIWordCountSet(MCSPI1_BASE_ADDRESS, length);
    /* Set the word count field with the data length to be transferred.*/
    McSPIWordCountSet(MCSPI2_BASE_ADDRESS, length);
    /* Enable the Tx/Rx DMA events for McSPI. */
    McSPIDMAEnable(MCSPI1_BASE_ADDRESS,
                   (MCSPI_DMA_RX_EVENT | MCSPI_DMA_TX_EVENT),
                   MCSPI_CH_NUM);
    /* Enable the Tx/Rx DMA events for McSPI. */
    McSPIDMAEnable(MCSPI2_BASE_ADDRESS,
                   (MCSPI_DMA_RX_EVENT | MCSPI_DMA_TX_EVENT),
                   MCSPI_CH_NUM);
}

static void McSPIInitializeBuffers(void)
{
    uint32_t index = 0;

    for (index = 0; index < McSPI_DATA_COUNT; index++)
    {
        /* Initialize the txBuffer McSPI1 with a known pattern of data */
        txBuffer[index] = (uint8_t) index;
        /* Initialize the rxBuffer McSPI1 with 0 */
        rxBuffer[index] = (uint8_t) 0;
    }
    for (index = 0; index < McSPI_DATA_COUNT; index++)
    {
        /* Initialize the txBuffer McSPI1 with a known pattern of data */
        txSlvBuffer[index] = (uint8_t) index;
        /* Initialize the rxBuffer McSPI1 with 0 */
        rxSlvBuffer[index] = 0;
    }
}

static void McSPIMSTransfer(uint16_t length)
{
    /* Enable the McSPI channel for communication.*/
    McSPIChannelEnable(MCSPI2_BASE_ADDRESS, gChNum);

    /* SPIEN line is forced to low state.*/
    McSPICSAssert(MCSPI2_BASE_ADDRESS, gChNum);

    /* Enable the McSPI channel for communication.*/
    McSPIChannelEnable(MCSPI1_BASE_ADDRESS, gChNum);

    /* SPIEN line is forced to low state.*/
    McSPICSAssert(MCSPI1_BASE_ADDRESS, gChNum);
    if (MCSPI_MASTERSLAVE_DMA_MODE_TEST == gMainMenuOption)
    {
        /* For DMA mode wait for EDMA ISR to happen */
        while ((0 == flagTx) || (flagRx == 0) || (0 == flagSlvTx) ||
               (flagSlvRx == 0)) ;
    }
    else
    {
        McSPIMSPolledModeTransfer(length);
    }

    /* Force SPIEN line to the inactive state.*/
    McSPICSDeAssert(MCSPI1_BASE_ADDRESS, gChNum);

    /* Disable the McSPI channel.*/
    McSPIChannelDisable(MCSPI1_BASE_ADDRESS, gChNum);

    /* Force SPIEN line to the inactive state.*/
    McSPICSDeAssert(MCSPI2_BASE_ADDRESS, gChNum);

    /* Disable the McSPI channel.*/
    McSPIChannelDisable(MCSPI2_BASE_ADDRESS, gChNum);
}

static void McSPIMSPolledModeTransfer(uint16_t length)
{
    uint32_t          channelStatus = 0;
    volatile uint32_t timeout1      = 0xFFFFU;
    uint8_t          *p_rx;
    uint8_t          *p_tx;
    uint8_t          *p_rxSlv;
    uint8_t          *p_txSlv;

    p_tx    = txBuffer;
    p_rx    = rxBuffer;
    p_txSlv = txSlvBuffer;
    p_rxSlv = rxSlvBuffer;

    while (0 != length)
    {
        timeout1      = 0xFFFF;
        channelStatus = McSPIChannelStatusGet(MCSPI2_BASE_ADDRESS, gChNum);
        while (0 == (channelStatus & MCSPI_CH0STAT_TXS_MASK))
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(MCSPI2_BASE_ADDRESS, gChNum);
            --timeout1;
            if (0 == timeout1)
            {
                UARTConfigPuts(uartBaseAddr,"\nMcSPI2 TX Timed out!!",1);
                while (1) ;
            }
        }
        McSPITransmitData(MCSPI2_BASE_ADDRESS, (uint32_t) (*p_txSlv++), gChNum);

        timeout1      = 0xFFFF;
        channelStatus = McSPIChannelStatusGet(MCSPI1_BASE_ADDRESS, gChNum);
        while (0 == (channelStatus & MCSPI_CH0STAT_TXS_MASK))
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(MCSPI1_BASE_ADDRESS, gChNum);
            --timeout1;
            if (0 == timeout1)
            {
                UARTConfigPuts(uartBaseAddr,"\nMcSPI1 TX Timed out!!",-1);
                while (1) ;
            }
        }
        McSPITransmitData(MCSPI1_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);

        timeout1      = 0xFFFF;
        channelStatus = McSPIChannelStatusGet(MCSPI1_BASE_ADDRESS, gChNum);
        while (0 == (channelStatus & MCSPI_CH0STAT_RXS_MASK))
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(MCSPI1_BASE_ADDRESS, gChNum);
            --timeout1;
            if (0 == timeout1)
            {
                UARTConfigPuts(uartBaseAddr,"\nMcSPI1 RX Timed out!!",1);
                while (1) ;
            }
        }
        *p_rx++ = (uint8_t)  McSPIReceiveData(MCSPI1_BASE_ADDRESS, gChNum);

        timeout1      = 0xFFFF;
        channelStatus = McSPIChannelStatusGet(MCSPI2_BASE_ADDRESS, gChNum);
        while (0 == (channelStatus & MCSPI_CH0STAT_RXS_MASK))
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(MCSPI2_BASE_ADDRESS, gChNum);
            --timeout1;
            if (0 == timeout1)
            {
                UARTConfigPuts(uartBaseAddr,"\nMcSPI2 RX Timed out!!",-1);
                while (1) ;
            }
        }
        *p_rxSlv++ = (uint8_t)  McSPIReceiveData(MCSPI2_BASE_ADDRESS, gChNum);

        length--;
    }
}

/*
** This function will verify the data written to and read from flash and print
** the appropriate message.
*/
static void McSPIVerifyData(void)
{
    uint32_t index = 0;
    uint32_t error = 0;

    for (index = 0; index < McSPI_DATA_COUNT; index++)
    {
        if ((rxSlvBuffer[index] != txBuffer[index]) ||
            (txSlvBuffer[index] != rxBuffer[index]))
        {
            UARTConfigPuts(uartBaseAddr,"\nData Mismatch found at index : \r",-1);
            error = 1;
            break;
        }
    }

    if (error == 0)
    {
        UARTConfigPuts(uartBaseAddr,"\nThe data written by Master and the one read by Slave are Equal",-1);
    }
}

/*
** This function configures the power supply for EDMA3 Channel Controller 0
** and Transfer Controller 0, registers the EDMA interrupts in AINTC.
*/
static void EDMA3Initialize(void)
{
    /* Configuring the AINTC to receive EDMA3 Interrupts */
    EDMA3IntConfigure();
}

/*
** EDMA3 completion Interrupt Service Routine(ISR).
*/
static void Edma3ComplHandlerIsr(void *dummy)
{
    uint32_t          pendingIrqs;
    volatile uint32_t isIPR  = 0;
    volatile uint32_t isIPRH = 0;

    uint32_t          indexl;
    uint32_t          Cnt = 0;

    indexl = 1;

    isIPR  = EDMA3GetIntrStatus(EDMA_TDA2XX_U_BASE);
    isIPRH = EDMA3IntrStatusHighGet(EDMA_TDA2XX_U_BASE);

    if (isIPR)
    {
        while ((Cnt < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (indexl != 0))
        {
            indexl = 0;

            pendingIrqs = EDMA3GetIntrStatus(EDMA_TDA2XX_U_BASE);

            while (pendingIrqs)
            {
                if ((pendingIrqs & 1) == TRUE)
                {
                    /**
                     * If the user has not given any callback function
                     * while requesting the TCC, its TCC specific bit
                     * in the IPR register will NOT be cleared.
                     */
                    /* Here write to ICR to clear the corresponding IPR bits. */
                    EDMA3ClrIntr(EDMA_TDA2XX_U_BASE, indexl);

                    (*cb_Fxn[indexl])(indexl, EDMA3_XFER_COMPLETE);
                }

                ++indexl;

                pendingIrqs >>= 1;
            }
            Cnt++;
        }
    }

    indexl = 32;

    if (isIPRH)
    {
        while ((Cnt < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (indexl != 0))
        {
            indexl = 32;

            pendingIrqs = EDMA3IntrStatusHighGet(EDMA_TDA2XX_U_BASE);

            while (pendingIrqs)
            {
                if ((pendingIrqs & 1) == TRUE)
                {
                    /**
                     * If the user has not given any callback function
                     * while requesting the TCC, its TCC specific bit
                     * in the IPR register will NOT be cleared.
                     */
                    /* Here write to ICR to clear the corresponding IPR bits. */
                    EDMA3ClrIntr(EDMA_TDA2XX_U_BASE, indexl);

                    (*cb_Fxn[indexl])(indexl, EDMA3_XFER_COMPLETE);
                }

                ++indexl;

                pendingIrqs >>= 1;
            }
            Cnt++;
        }
    }
}

/* EDMA3 Error Handler */
static void Edma3ErrorHandlerIsr_McSPI1(void *dummy)
{
    volatile uint32_t pendingIrqs   = 0;
    volatile uint32_t pendingHIrqs  = 0;
    uint32_t          txEventHighNo = 0;
    uint32_t          rxEventHighNo = 0;

    pendingIrqs  = EDMA3GetErrIntrStatus(EDMA_TDA2XX_U_BASE);
    pendingHIrqs = EDMA3ErrIntrHighStatusGet(EDMA_TDA2XX_U_BASE);

    if (pendingIrqs)
    {
        txEventHighNo = MCSPI1_TX_EVENT & 0x1F;
        rxEventHighNo = MCSPI1_RX_EVENT & 0x1F;

        if ((pendingIrqs & (0x01 << txEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI1_TX_EVENT);

            /* Disable McSPI Transmit event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI1_TX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagTx = 1;
        }
        else if ((pendingIrqs & (0x01 << rxEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI1_RX_EVENT);

            /* Disable McSPI Receive event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI1_RX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagRx = 1;
        }
    }
    else if (pendingHIrqs)
    {
        txEventHighNo = MCSPI1_TX_EVENT - 32;
        rxEventHighNo = MCSPI1_RX_EVENT - 32;

        if ((pendingHIrqs & (0x01 << txEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI1_TX_EVENT);

            /* Disable McSPI Transmit event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI1_TX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagTx = 1;
        }
        else if ((pendingIrqs & (0x01 << rxEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI1_RX_EVENT);

            /* Disable McSPI Receive event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI1_RX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagRx = 1;
        }
    }
    else
    {
        /* Events has to be cross bar mapped */
    }
}

/* EDMA3 Error Handler */
static void Edma3ErrorHandlerIsr_McSPI2(void *dummy)
{
    volatile uint32_t pendingIrqs   = 0;
    volatile uint32_t pendingHIrqs  = 0;
    uint32_t          txEventHighNo = 0;
    uint32_t          rxEventHighNo = 0;

    pendingIrqs  = EDMA3GetErrIntrStatus(EDMA_TDA2XX_U_BASE);
    pendingHIrqs = EDMA3ErrIntrHighStatusGet(EDMA_TDA2XX_U_BASE);

    if (pendingIrqs)
    {
        txEventHighNo = MCSPI2_TX_EVENT & 0x1F;
        rxEventHighNo = MCSPI2_RX_EVENT & 0x1F;

        if ((pendingIrqs & (0x01 << txEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI2_TX_EVENT);

            /* Disable McSPI Transmit event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI2_TX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagTx = 1;
        }
        else if ((pendingIrqs & (0x01 << rxEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI2_RX_EVENT);

            /* Disable McSPI Receive event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI2_RX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagRx = 1;
        }
    }
    else if (pendingHIrqs)
    {
        txEventHighNo = MCSPI2_TX_EVENT - 32;
        rxEventHighNo = MCSPI2_RX_EVENT - 32;

        if ((pendingHIrqs & (0x01 << txEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI2_TX_EVENT);

            /* Disable McSPI Transmit event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI2_TX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagTx = 1;
        }
        else if ((pendingIrqs & (0x01 << rxEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TDA2XX_U_BASE, MCSPI2_RX_EVENT);

            /* Disable McSPI Receive event */
            McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TDA2XX_U_BASE, MCSPI2_RX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagRx = 1;
        }
    }
    else
    {
        /* Events has to be cross bar mapped */
    }
}

/*
** Call back function. Here we disable the Tx/Rx DMA events of McSPI
** peripheral.
*/
static void CallBack_McSPI1(uint32_t tccNum, uint32_t status)
{
    if (tccNum == MCSPI1_TX_EVENT)
    {
        flagTx = 1;

        /* Disable McSPI Transmit event */
        McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                        MCSPI_CH_NUM);
    }

    if (tccNum == MCSPI1_RX_EVENT)
    {
        flagRx = 1;

        /* Disable McSPI Receive event */
        McSPIDMADisable(MCSPI1_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                        MCSPI_CH_NUM);
    }
}

/*
** Call back function. Here we disable the Tx/Rx DMA events of McSPI
** peripheral.
*/
static void CallBack_McSPI2(uint32_t tccNum, uint32_t status)
{
    if (tccNum == MCSPI2_TX_EVENT)
    {
        flagSlvTx = 1;

        /* Disable McSPI Transmit event */
        McSPIDMADisable(MCSPI2_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                        MCSPI_CH_NUM);
    }

    if (tccNum == MCSPI2_RX_EVENT)
    {
        flagSlvRx = 1;

        /* Disable McSPI Receive event */
        McSPIDMADisable(MCSPI2_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                        MCSPI_CH_NUM);
    }
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Receive
** event of channel 0 of McSPI1 instance. The corresponding EDMA3 channel
** is also enabled for reception.
*/
static void McSpi1RxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength,
                                 uint32_t destBidxFlag)
{
    EDMA3CCPaRAMEntry paramSet = {0};

    /* Fill the PaRAM Set with Receive specific information.*/

    /* srcAddr holds address of SPI Rx FIFO.*/
    paramSet.srcAddr = (uint32_t) (MCSPI1_RX0_REG);

    /* destAddr is address of memory location named buffer.*/
    paramSet.destAddr = (uint32_t) buffer;

    /* aCnt holds the number of bytes in an array.*/
    paramSet.aCnt = 1;

    /* bCnt holds the number of such arrays to be transferred.*/
    paramSet.bCnt = buffLength;

    /* cCnt holds the number of frames of aCnt*bBcnt bytes to be transferred.*/
    paramSet.cCnt = 1;

    /* The srcBidx should not be incremented since it is a h/w register.*/
    paramSet.srcBIdx = 0;

    if (TRUE == destBidxFlag)
    {
        /* The destBidx should be incremented for every byte.*/
        paramSet.destBIdx = 1;
    }
    else
    {
        /* The destBidx should not be incremented.*/
        paramSet.destBIdx = 0;
    }

    /* A sync Transfer Mode. */
    /* srCIdx and destCIdx set to zero since ASYNC Mode is used.*/
    paramSet.srcCIdx  = 0;
    paramSet.destCIdx = 0;

    /* Linking transfers in EDMA3 are not used.*/
    paramSet.linkAddr = 0xFFFF;

    paramSet.bCntReload = 0;

    paramSet.opt = 0x00000000;

    /* Set TCC field in OPT with the tccNum.*/
    paramSet.opt |= ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) &
                     EDMA_TPCC_OPT_TCC_MASK);

    /* EDMA3 Interrupt is enabled and Intermediate Interrupt Disabled.*/
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRam Set to EDMA3.*/
    EDMA3SetPaRAM(EDMA_TDA2XX_U_BASE, chNum, &paramSet);

    /* EDMA3 Transfer is Enabled.*/
    EDMA3EnableTransfer(EDMA_TDA2XX_U_BASE, chNum, EDMA3_TRIG_MODE_EVENT);
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Receive
** event of channel 0 of McSPI2 instance. The corresponding EDMA3 channel
** is also enabled for reception.
*/
static void McSpi2RxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength,
                                 uint32_t destBidxFlag)
{
    EDMA3CCPaRAMEntry paramSet = {0};

    /* Fill the PaRAM Set with Receive specific information.*/

    /* srcAddr holds address of SPI Rx FIFO.*/
    paramSet.srcAddr = (uint32_t) (MCSPI2_RX0_REG);

    /* destAddr is address of memory location named buffer.*/
    paramSet.destAddr = (uint32_t) buffer;

    /* aCnt holds the number of bytes in an array.*/
    paramSet.aCnt = 1;

    /* bCnt holds the number of such arrays to be transferred.*/
    paramSet.bCnt = buffLength;

    /* cCnt holds the number of frames of aCnt*bBcnt bytes to be transferred.*/
    paramSet.cCnt = 1;

    /* The srcBidx should not be incremented since it is a h/w register.*/
    paramSet.srcBIdx = 0;

    if (TRUE == destBidxFlag)
    {
        /* The destBidx should be incremented for every byte.*/
        paramSet.destBIdx = 1;
    }
    else
    {
        /* The destBidx should not be incremented.*/
        paramSet.destBIdx = 0;
    }

    /* A sync Transfer Mode. */
    /* srCIdx and destCIdx set to zero since ASYNC Mode is used.*/
    paramSet.srcCIdx  = 0;
    paramSet.destCIdx = 0;

    /* Linking transfers in EDMA3 are not used.*/
    paramSet.linkAddr = 0xFFFF;

    paramSet.bCntReload = 0;

    paramSet.opt = 0x00000000;

    /* Set TCC field in OPT with the tccNum.*/
    paramSet.opt |= ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) &
                     EDMA_TPCC_OPT_TCC_MASK);

    /* EDMA3 Interrupt is enabled and Intermediate Interrupt Disabled.*/
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRam Set to EDMA3.*/
    EDMA3SetPaRAM(EDMA_TDA2XX_U_BASE, chNum, &paramSet);

    /* EDMA3 Transfer is Enabled.*/
    EDMA3EnableTransfer(EDMA_TDA2XX_U_BASE, chNum, EDMA3_TRIG_MODE_EVENT);
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Transmit
** Channel 0 of SPI1 instance. The corresponding EDMA3 channel is also enabled
** for transmission.
*/
static void McSpi1TxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength)
{
    EDMA3CCPaRAMEntry paramSet = {0};

    /* Fill the PaRAM Set with transfer specific information. */

    /* srcAddr holds address of memory location buffer. */
    paramSet.srcAddr = (uint32_t) buffer;

    /* destAddr holds address of McSPI_TX register. */
    paramSet.destAddr = (uint32_t) (MCSPI1_TX0_REG);

    /* aCnt holds the number of bytes in an array. */
    paramSet.aCnt = 1;

    /* bCnt holds the number of such arrays to be transferred. */
    paramSet.bCnt = buffLength;

    /* cCnt holds the number of frames of aCnt*bBcnt bytes to be transferred. */
    paramSet.cCnt = 1;

    /*
    ** The srcBidx should be incremented by aCnt number of bytes since the
    ** source used here is memory.
    */
    paramSet.srcBIdx  = 1;
    paramSet.destBIdx = 0;

    /* Async Transfer Mode is set in OPT.*/
    /* srCIdx and destCIdx set to zero since ASYNC Mode is used. */
    paramSet.srcCIdx  = 0;
    paramSet.destCIdx = 0;

    /* Linking transfers in EDMA3 are not used. */
    paramSet.linkAddr   = (EDMA3CC_OPT(DUMMY_CH_NUM));
    paramSet.bCntReload = 0;

    paramSet.opt = 0x00000000;

    /* SAM and DAM fields both are set to 0 */

    /* Set TCC field in OPT with the tccNum. */
    paramSet.opt |= ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) &
                     EDMA_TPCC_OPT_TCC_MASK);

    /* EDMA3 Interrupt is enabled and Intermediate Interrupt Disabled.*/
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRam Set to EDMA3.*/
    EDMA3SetPaRAM(EDMA_TDA2XX_U_BASE, chNum, &paramSet);

    /* Dummy param set is enabled */
    TxDummyPaRAMConfEnable();

    /* EDMA3 Transfer is Enabled. */
    EDMA3EnableTransfer(EDMA_TDA2XX_U_BASE, chNum, EDMA3_TRIG_MODE_EVENT);
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Transmit
** Channel 0 of SPI2 instance. The corresponding EDMA3 channel is also enabled
** for transmission.
*/
static void McSpi2TxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                 volatile uint8_t *buffer,
                                 uint16_t buffLength)
{
    EDMA3CCPaRAMEntry paramSet = {0};

    /* Fill the PaRAM Set with transfer specific information. */

    /* srcAddr holds address of memory location buffer. */
    paramSet.srcAddr = (uint32_t) buffer;

    /* destAddr holds address of McSPI_TX register. */
    paramSet.destAddr = (uint32_t) (MCSPI2_TX0_REG);

    /* aCnt holds the number of bytes in an array. */
    paramSet.aCnt = 1;

    /* bCnt holds the number of such arrays to be transferred. */
    paramSet.bCnt = buffLength;

    /* cCnt holds the number of frames of aCnt*bBcnt bytes to be transferred. */
    paramSet.cCnt = 1;

    /*
    ** The srcBidx should be incremented by aCnt number of bytes since the
    ** source used here is memory.
    */
    paramSet.srcBIdx  = 1;
    paramSet.destBIdx = 0;

    /* Async Transfer Mode is set in OPT.*/
    /* srCIdx and destCIdx set to zero since ASYNC Mode is used. */
    paramSet.srcCIdx  = 0;
    paramSet.destCIdx = 0;

    /* Linking transfers in EDMA3 are not used. */
    paramSet.linkAddr   = (EDMA3CC_OPT(DUMMY_CH_NUM));
    paramSet.bCntReload = 0;

    paramSet.opt = 0x00000000;

    /* SAM and DAM fields both are set to 0 */

    /* Set TCC field in OPT with the tccNum. */
    paramSet.opt |= ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) &
                     EDMA_TPCC_OPT_TCC_MASK);

    /* EDMA3 Interrupt is enabled and Intermediate Interrupt Disabled.*/
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRam Set to EDMA3.*/
    EDMA3SetPaRAM(EDMA_TDA2XX_U_BASE, chNum, &paramSet);

    /* Dummy param set is enabled */
    TxDummyPaRAMConfEnable();

    /* EDMA3 Transfer is Enabled. */
    EDMA3EnableTransfer(EDMA_TDA2XX_U_BASE, chNum, EDMA3_TRIG_MODE_EVENT);
}

/*
** This function allocates EDMA3 channels to McSPI0 for trasmisssion and
** reception purposes.
*/
static void RequestEDMA3Channels(void)
{
    /* Request DMA Channel and TCC for SPI Transmit*/
    EDMA3RequestChannel(EDMA_TDA2XX_U_BASE, EDMA3_CHANNEL_TYPE_DMA, \
                        MCSPI1_TX_EVENT, MCSPI1_TX_EVENT, EVT_QUEQUE_NUM);

    /* Request DMA Channel and TCC for SPI Receive*/
    EDMA3RequestChannel(EDMA_TDA2XX_U_BASE, EDMA3_CHANNEL_TYPE_DMA, \
                        MCSPI1_RX_EVENT, MCSPI1_RX_EVENT, EVT_QUEQUE_NUM);

    /* Request DMA Channel and TCC for SPI Transmit*/
    EDMA3RequestChannel(EDMA_TDA2XX_U_BASE, EDMA3_CHANNEL_TYPE_DMA, \
                        MCSPI2_TX_EVENT, MCSPI2_TX_EVENT, EVT_QUEQUE_NUM);

    /* Request DMA Channel and TCC for SPI Receive*/
    EDMA3RequestChannel(EDMA_TDA2XX_U_BASE, EDMA3_CHANNEL_TYPE_DMA, \
                        MCSPI2_RX_EVENT, MCSPI2_RX_EVENT, EVT_QUEQUE_NUM);
}

/*
** This function configures the AINTC to receive EDMA3 interrupts.
*/
static void EDMA3IntConfigure(void)
{
#ifdef _TMS320C6X
    /* Initialize DSP interrupt controller and enable interrupts */
    IntDSPINTCInit();
    IntGlobalEnable();

    /* Map EDMA events to DSP interrupts */
    IntRegister(4, Edma3ComplHandlerIsr);
    IntEventMap(4, SYS_INT_EDMACOMPINT);
    IntEnable(4);

    IntRegister(5, Edma3ErrorHandlerIsr);
    IntEventMap(5, SYS_INT_EDMAERRINT);
    IntEnable(5);
#else
    /* TODO Move to macro */
#ifdef __ARM_ARCH_7A__
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,7,CSL_XBAR_EDMA_TPCC_IRQ_REGION0);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,9,CSL_XBAR_EDMA_TPCC_IRQ_ERR);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,10,CSL_XBAR_EDMA_TPCC_IRQ_ERR);
#elif defined (__TI_ARM_V7M4__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,13,CSL_XBAR_EDMA_TPCC_IRQ_REGION1);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,14,CSL_XBAR_EDMA_TPCC_IRQ_ERR);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,15,CSL_XBAR_EDMA_TPCC_IRQ_ERR);
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* TODO Move to Macro and verify */
#if defined (__ARM_ARCH_7A__)
    /* Cortex A15 interrupt configuration        */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_A15, Edma3ComplHandlerIsr,
                     NULL);
    Intc_IntPrioritySet(EDMA3_CC_XFER_COMPLETION_INT_A15, 1, 0);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_A15);

    Intc_IntRegister(EDMA3_ERROR_INT_A15, Edma3ErrorHandlerIsr_McSPI1, NULL);
    Intc_IntRegister(EDMA3_ERROR_INT_A15_1, Edma3ErrorHandlerIsr_McSPI2, NULL);

    Intc_IntPrioritySet(EDMA3_ERROR_INT_A15, 1, 0);
    Intc_SystemEnable(EDMA3_ERROR_INT_A15);
    Intc_SystemEnable(EDMA3_ERROR_INT_A15_1);

#elif defined (__TI_ARM_V7M4__)
    /* M4 interrupt configuration           */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_M4,
                     (IntrFuncPtr) Edma3ComplHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_M4);

    Intc_IntRegister(EDMA3_ERROR_INT_M4,
                     (IntrFuncPtr) Edma3ErrorHandlerIsr_McSPI1,
                     NULL);
    Intc_IntRegister(EDMA3_ERROR_INT_M4_1,
                     (IntrFuncPtr) Edma3ErrorHandlerIsr_McSPI2,
                     NULL);

    Intc_SystemEnable(EDMA3_ERROR_INT_M4);
    Intc_SystemEnable(EDMA3_ERROR_INT_M4_1);

#endif

#endif
}

/*
** This configures the PaRAM set for the Dummy Transfer.
*/
static void TxDummyPaRAMConfEnable(void)
{
    EDMA3CCPaRAMEntry dummyPaRAMSet;

    EDMA3GetPaRAM(EDMA_TDA2XX_U_BASE, DUMMY_CH_NUM, &dummyPaRAMSet);

    dummyPaRAMSet.aCnt       = 1;
    dummyPaRAMSet.bCnt       = 0;
    dummyPaRAMSet.cCnt       = 0;
    dummyPaRAMSet.srcAddr    = 0;
    dummyPaRAMSet.destAddr   = 0;
    dummyPaRAMSet.srcBIdx    = 0;
    dummyPaRAMSet.destBIdx   = 0;
    dummyPaRAMSet.srcCIdx    = 0;
    dummyPaRAMSet.destCIdx   = 0;
    dummyPaRAMSet.linkAddr   = 0xFFFFU;
    dummyPaRAMSet.bCntReload = 0;
    dummyPaRAMSet.opt        = 0;

    EDMA3SetPaRAM(EDMA_TDA2XX_U_BASE, DUMMY_CH_NUM, &dummyPaRAMSet);
}

void SetupI2C(void)
{
    /* Do a software reset */
    I2CSoftReset(SOC_I2C1_BASE);

    /* Enable i2c module */
    I2CMasterEnable(SOC_I2C1_BASE);

    while (!I2CSystemStatusGet(SOC_I2C1_BASE)) ;
    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C1_BASE);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C1_BASE, 24000000, 8000000, 100000);

    I2COwnAddressSet(SOC_I2C1_BASE, 0, I2C_OWN_ADDR_0);

    I2CSyscInit(SOC_I2C1_BASE, 0x08);

    /* Set Rx and Tx FIFO threshold value and reset the fifo */
    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_TX_MODE);

    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_RX_MODE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C1_BASE, HSI2C_SLAVE_ADDR);

    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2C1_BASE);

    /* Enable free run mode */
    I2CMasterEnableFreeRun(SOC_I2C1_BASE);
}

uint32_t I2CRead()
{
    uint8_t  i2cReadByte[2];
    uint32_t i2cReadVal;
    uint32_t temp1;
    uint32_t temp2;

    /* Set i2cReadByte count */
    I2CSetDataCount(SOC_I2C1_BASE, 2);

    /*
    ** Configure i2c as master-Receiver and to generate stop condition
    */
    I2CMasterControl(SOC_I2C1_BASE,
                    I2C_CFG_MST_RX | I2C_CFG_STOP | I2C_CFG_START);

    /* Wait for receive interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                    I2C_INT_RECV_READY) != I2C_INT_RECV_READY) ;

    /* Disable transmit ready */
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_RECV_READY);

    /* Read i2cReadByte */
    i2cReadByte[0] = I2CMasterDataGet(SOC_I2C1_BASE);

    sampleDelay(50);

    /* Wait for receive interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                    I2C_INT_RECV_READY) != I2C_INT_RECV_READY) ;

    /* Disable transmit ready */
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_RECV_READY);

    i2cReadByte[1] = I2CMasterDataGet(SOC_I2C1_BASE);

    I2CFlushFifo(SOC_I2C1_BASE);

    /* Clear all interrupt status */
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_ALL);

    /* Clear i2cReadByte buffer length */
    I2CSetDataCount(SOC_I2C1_BASE, 0);

    temp1 = i2cReadByte[0];
    temp2 = i2cReadByte[1];

    i2cReadVal = (temp1 | (temp2 << 8));

    return i2cReadVal;
}

void SetupI2CTransmit(void)
{
    uint8_t *i2cReadByte = (uint8_t *) (&dataToSlave);
    /* Set data count */
    I2CSetDataCount(SOC_I2C1_BASE, 2);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2C1_BASE,
                    I2C_CFG_MST_TX | I2C_CON_STP_STP | I2C_CFG_START);

    /* Wait for transmit interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                    I2C_INT_TRANSMIT_READY) != 0x10) ;

    /* Disable transmit ready and stop condition interrupt */
    I2CMasterIntClearEx(SOC_I2C1_BASE,
                        I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    I2CMasterDataPut(SOC_I2C1_BASE, i2cReadByte[0]);

    /* Wait for transmit interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                    I2C_INT_TRANSMIT_READY) != 0x10) ;

    /* Disable transmit ready and stop condition interrupt */
    I2CMasterIntClearEx(SOC_I2C1_BASE,
                        I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    I2CMasterDataPut(SOC_I2C1_BASE, i2cReadByte[1]);

    sampleDelay(50);

    I2CFlushFifo(SOC_I2C1_BASE);

    /*Clear all interrupt status*/
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_ALL);

    /*Clear data buffer length*/
    I2CSetDataCount(SOC_I2C1_BASE, 0);
}

static void mainMenu(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n**** MCSPI MasterSlave (SPI1 to SPI2) Application Test ****", -1);
        UARTConfigPuts(uartBaseAddr,"\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n1. MCSPI MasterSlave Polled Mode test - SPI1 to SPI2", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n2. MCSPI MasterSlave DMA Mode test - SPI1 to SPI2", -1);
        UARTConfigPuts(uartBaseAddr,"\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr,"\r\nSelect MCSPI MasterSlave(SPI1 to SPI2) Application Test : ", -1);

        /* Get option */
        UARTConfigGets(uartBaseAddr,option, 1);

        if ((MCSPI_MASTERSLAVE_POLLED_MODE_TEST == *option) ||
            (MCSPI_MASTERSLAVE_DMA_MODE_TEST == *option) || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr,"\nEnter Valid option\n", -1);
        }
    }
}
/********************************* End Of File ******************************/
