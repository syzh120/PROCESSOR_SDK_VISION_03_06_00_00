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
 *  \file   mcaspTransmit.c
 *
 *  \brief  This file contains the McASP application, designed to meet specific
 *           requirements -
 *           1. Showcase bit clock of 10MHz
 *           2. Data output on two data lines
 *           3. The McASP to output the data on the lines and observe the same on the CRO.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_mcasp.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM571x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define SOC_MCASP_CFG_BASE CSL_MPU_MCASP3_CFG_REGS
#define SOC_MCASP_BASE CSL_MPU_MCASP3_REGS
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
#define SOC_MCASP_CFG_BASE SOC_MCASP3_CFG_BASE
#define SOC_MCASP_BASE SOC_MCASP3_BASE
#endif
#define SOC_MCASP_3_FIFO_REGS (SOC_MCASP_CFG_BASE + 0x1000)
#define MCASP_RX_DMA_XBAR_INST            (132U)
#define MCASP_TX_DMA_XBAR_INST            (133U)
#else
#define SOC_MCASP_CFG_BASE SOC_MCASP1_CFG_BASE
#define SOC_MCASP_BASE SOC_MCASP1_BASE
#define SOC_MCASP_1_FIFO_REGS (SOC_MCASP_CFG_BASE + 0x1000)
#define MCASP_RX_DMA_XBAR_INST            (128U)
#define MCASP_TX_DMA_XBAR_INST            (129U)
#endif

/*
** Values which are configurable
*/
/* Slot size to send/receive data */
#define SLOT_SIZE                         (32U)

/* Word size to send/receive data. Word size <= Slot size */
#define WORD_SIZE                         (32U)

/* Number of channels, L & R */
#define NUM_I2S_CHANNELS                  (2U)

/* Number of samples to be used per audio buffer */
#define NUM_SAMPLES_PER_AUDIO_BUF         (2000U)

/* Number of buffers used per tx/rx */
#define NUM_BUF                           (3U)

/* Number of linked parameter set used per tx/rx */
#define NUM_PAR                           (2U)

/* Specify where the parameter set starting is */
#define PAR_ID_START                      (72U)

/* Number of samples in loop buffer */
#define NUM_SAMPLES_LOOP_BUF              (10U)

/* McASP Serializer 0 for Transmit */
#define MCASP_XSER_TX_0                   (0U)

/* McASP Serializer 1 for Transmit */
#define MCASP_XSER_TX_1                   (1U)

/*
** Below Macros are calculated based on the above inputs
*/

#define I2S_SLOTS                         ((1 << NUM_I2S_CHANNELS) - 1)

#define BYTES_PER_SAMPLE                  ((WORD_SIZE >> 3) \
                                           * NUM_I2S_CHANNELS)

#define AUDIO_BUF_SIZE                    (NUM_SAMPLES_PER_AUDIO_BUF \
                                           * BYTES_PER_SAMPLE)

#define TX_DMA_INT_ENABLE                 (EDMA3CC_OPT_TCC_SET            \
                                               (EDMA3_CHA_MCASP_TX) | (1  \
                                                                       << \
                                                                       EDMA_TPCC_OPT_TCINTEN_SHIFT))

#define PAR_TX_START                      (PAR_ID_START)

/*
** Definitions which are not configurable
*/
#define SIZE_PARAMSET                     (32U)
#define OPT_FIFO_WIDTH                    (0x02 << 8U)

/*
** Definitions which are configurable depending on the core to be used(ARM here)
*/
#define EDMA3_CHA_MCASP_RX               (4)
#define EDMA3_CHA_MCASP_TX               (5)

#define EDMA3_CC_REGION_A15               (0U)
#define EDMA3_CC_REGION_M4                (1U)

#define EDMA3_CC_QUEUE                    (0U)

#define EDMA3_CC_XFER_COMPLETION_INT_A15  (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4   (34U)

#if defined (__ARM_ARCH_7A__)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#elif defined (__TI_ARM_V7M4__)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M4
#endif

#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK (0x00FF0000U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT (0x00000010U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL (0x00000000U)

#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK (0x000000FFU)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT (0x00000000U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL (0x00000000U)

#define EDMA3_MAX_CROSS_BAR_EVENTS_TI814X (230U)

#define EDMA3_EVENT_MUX_REG_BASE_ADDR               (0x4a002c78)

/*
** Definitions which are configurable depending on the application requirement
*/
#define MCASP_ACLKX_CLKXDIV_VALUE         (0x2U)
#define MCASP_AHCLKX_HCLKXDIV_VALUE       (0x5U)

#define HSI2C_SLAVE_ADDR                  (0x26)

#if defined (SOC_AM571x)
#define SOC_I2Cx_BASE                  (CSL_MPU_I2C5_REGS)
#elif defined (SOC_TDA2EX) || defined (SOC_DRA72x)
#define SOC_I2Cx_BASE                  (SOC_I2C5_BASE)
#elif defined (SOC_AM574x) || defined (SOC_AM572x)
#define SOC_I2Cx_BASE                  (CSL_MPU_I2C2_REGS)
#else
#define SOC_I2Cx_BASE                  (SOC_I2C2_BASE)
#endif

/* ========================================================================== */
/*                          Function prototypes                              */
/* ========================================================================== */
static void I2SDMAParamInit(void);
static void McASPI2SConfigure(void);
static void I2SDataTxActivate(void);
void SetupI2C(uint8_t addr);
void SetupI2CTransmit(void);
void Configure_Edma_xbar();
void padConfig_prcmEnable();
void sampleConfigScr(unsigned int eventNum,
                    unsigned int chanNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global counters to keep track of errors. Can be removed before releasing  */
uint32_t                       complInterruptCounter = 0x00;
uint32_t                       errInterruptCounter   = 0x00;

uint8_t                        dataToSlave;
uint8_t                        dataFromSlave;

/*
** Transmit buffers. If any new buffer is to be added, define it here and
** update the NUM_BUF.
*/
static uint8_t                 txBuf0[AUDIO_BUF_SIZE];
static uint8_t                 txBuf1[AUDIO_BUF_SIZE];
static uint8_t                 txBuf2[AUDIO_BUF_SIZE];

/*
** The offset of the paRAM ID sent, from starting of the paRAM set.
*/
static volatile uint16_t       parOffSent = 0;

typedef struct  {
    volatile unsigned int TPCC_EVTMUX[32];
} IntmuxRegs;

typedef volatile IntmuxRegs *IntmuxRegsOvly;

/* Array of transmit buffer pointers */
static uint32_t const          txBufPtr[NUM_BUF] =
{
    (uint32_t) txBuf0,
    (uint32_t) txBuf1,
    (uint32_t) txBuf2
};

/*
** Default paRAM for Transmit section. This will be transmitting from
** a loop buffer.
*/
static EDMA3CCPaRAMEntry const txDefaultPar =
{
    (uint32_t) (OPT_FIFO_WIDTH),               /* Opt field */
    (uint32_t) txBuf0,                         /* source address */
    (uint16_t) (BYTES_PER_SAMPLE),             /* aCnt */
    (uint16_t) (NUM_SAMPLES_LOOP_BUF),         /* bCnt */
    (uint32_t) (SOC_MCASP_BASE),               /* dest address */
    (uint16_t) (BYTES_PER_SAMPLE),             /* source bIdx */
    (uint16_t) (0),                            /* dest bIdx */
    (uint16_t) (PAR_TX_START * SIZE_PARAMSET), /* link address */
    (uint16_t) (0),                            /* bCnt reload value */
    (uint16_t) (0),                            /* source cIdx */
    (uint16_t) (0),                            /* dest cIdx */
    (uint16_t) 1                               /* cCnt */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /* Power on McASP instance 3 */
    HW_WR_REG32(0x4a009868, 0x02);
    while ((HW_RD_REG32(0x4a009868)) != 0x02U)
        {
            ;
        }
    /* Pad mux configuration for McASP instance 3 */
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_MCASP3_ACLKX,0xc0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_XREF_CLK2,0x40003);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_MCASP3_FSX,0xc0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_MCASP3_AXR0,0xc0000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_MCASP3_AXR1,0xc0000);
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
     /* Power on McASP instance 3 */
    HW_WR_REG32(0x4a009868, 0x02);
    while ((HW_RD_REG32(0x4a009868)) != 0x02U)
        {
            ;
        }
    /* Pad mux configuration for McASP instance 3 */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_MCASP3_ACLKX,0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_XREF_CLK2,0x40003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_MCASP3_FSX,0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_MCASP3_AXR0,0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_MCASP3_AXR1,0xc0000);
#else
    /* Power on McASP instance 1 */
    HW_WR_REG32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL, 0x02);
    while ((HW_RD_REG32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL)) !=0x02U)
        {
            ;
        }
    /* Pad mux configuration for McASP instance 1 */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_DE,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_FLD,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D0,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D1,0x00040001);
#endif

#if defined (SOC_AM571x)
    /* Pad mux configuration for I2C instance 5 */
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_MCASP1_AXR0,0x5000A);
#elif defined (SOC_TDA2EX) || defined (SOC_DRA72x)
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_MCASP1_AXR0,0x5000A);
#elif defined (SOC_AM574x) || defined (SOC_AM572x)
    /* Pad mux configuration for I2C instance 2 */
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_I2C2_SDA,0x00);
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
    /* Pad mux configuration for I2C instance 2 */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_I2C2_SDA,0x00);
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* Pad mux configuration for I2C instance 2 */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_I2C2_SDA,0x00);
#endif

}

void SetupI2C(uint8_t addr)
{
    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2Cx_BASE);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2Cx_BASE, 24000000,
                        8000000, 100000);

    I2CMasterEnableFreeRun(SOC_I2Cx_BASE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2Cx_BASE, addr);

    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2Cx_BASE);
}

void SetupI2CTransmit(void)
{
    /* Set data count */
    I2CSetDataCount(SOC_I2Cx_BASE, 2);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2Cx_BASE, I2C_CFG_MST_TX);

    /*Enable transmit ready and stop condition interrupt*/
    I2CMasterIntEnableEx(SOC_I2Cx_BASE,
                         I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    /*Generate start conndition*/
    I2CMasterStart(SOC_I2Cx_BASE);

    /*Wait for transmit interrupt to occur*/
    while (I2CMasterIntStatusEx(SOC_I2Cx_BASE, I2C_INT_TRANSMIT_READY) != 0x10) ;

    /*Disable transmit ready and stop condition interrupt*/
    I2CMasterIntDisableEx(SOC_I2Cx_BASE, I2C_INT_TRANSMIT_READY);

    I2CMasterIntDisableEx(SOC_I2Cx_BASE, I2C_INT_STOP_CONDITION);

    /* Send first command word and then the data */
    I2CMasterDataPut(SOC_I2Cx_BASE, 0x00);
    I2CMasterDataPut(SOC_I2Cx_BASE, 0x00);
}

/*
** Initializes the DMA parameters.
** The TX basic paRAM set (channel) is 12.
**
** The TX paRAM sets will be initialized to transmit from the loop buffer.
** The size of the loop buffer can be configured.
** The transfer completion interrupt will not be enabled for paRAM set 1;
** paRAM set 1 will be linked to linked paRAM set starting (PAR_TX_START) of TX.
** All other paRAM sets will be linked to itself.
** and further transmission only happens via linked paRAM set.
** For example, if the PAR_TX_START value is 72, and the number of paRAMS is 2,
** So transmission paRAM set linking will be initialized as 1-->72-->73, 73->73.
*/
static void I2SDMAParamInit(void)
{
    EDMA3CCPaRAMEntry paramSet;
    int i = 0;

    /* Initialize TX Buffers
     *
     * These patterns are seen/output on serializer0 and serializer1
     */
    for (i = 0; i < (AUDIO_BUF_SIZE / 4); i++)
    {
        if (0 == (i % 2))
        {
            int index;
            for (index = 0; index < 4; index++)
            {
                /* '0xF0' data pattern that yields freq of 1.38MHz */
                txBuf0[4 * i + index] = 0xF0U;
                txBuf1[4 * i + index] = 0xF0U;
                txBuf2[4 * i + index] = 0xF0U;
            }
        }
        else
        {
            int index;
            for (index = 0; index < 4; index++)
            {
                /* '0xCC' data pattern that yields freq of 2.77MHz */
                txBuf0[4 * i + index] = 0xCCU;
                txBuf1[4 * i + index] = 0xCCU;
                txBuf2[4 * i + index] = 0xCCU;
            }
        }
    }

    /* Initialize the 1st paRAM set for transmit */
    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHA_MCASP_TX, &paramSet);

    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);
    /* Enable Intr for Link Channel */
    paramSet.opt     |= TX_DMA_INT_ENABLE;
    paramSet.srcAddr  = txBufPtr[1];
    paramSet.linkAddr = (PAR_TX_START * SIZE_PARAMSET);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, (PAR_TX_START), &paramSet);

    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);
    paramSet.srcAddr = txBufPtr[2];
    /* Self Link here */
    paramSet.linkAddr = ((PAR_TX_START + 1) * SIZE_PARAMSET);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, (PAR_TX_START + 1), &paramSet);
}

/*
** Configures the McASP Transmit Section in I2S mode.
*/
static void McASPI2SConfigure(void)
{
    McASPTxReset(SOC_MCASP_CFG_BASE);

    /* Enable the FIFOs for DMA transfer */
    McASPWriteFifoEnable(SOC_MCASP_CFG_BASE, 2, 1);

    /* Set I2S format in the transmitter/receiver format units */
    McASPTxFmtI2SSet(SOC_MCASP_CFG_BASE, WORD_SIZE, SLOT_SIZE,
                     MCASP_TX_MODE_DMA);

    McASPTxFrameSyncCfg(SOC_MCASP_CFG_BASE, 2, MCASP_TX_FS_WIDTH_WORD,
                        MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE |
                        MCASP_TX_FS_INTERNAL);

    /* configure the clock for transmitter */
    McASPTxClkCfg(SOC_MCASP_CFG_BASE, MCASP_TX_CLK_INTERNAL,
                  ((MCASP_ACLKX_CLKXDIV_VALUE &
                    MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((MCASP_AHCLKX_HCLKXDIV_VALUE &
                    MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    McASPTxClkPolaritySet(SOC_MCASP_CFG_BASE, MCASP_TX_CLK_POL_FALL_EDGE);

    McASPTxClkCheckConfig(SOC_MCASP_CFG_BASE, MCASP_TX_CLKCHCK_DIV32,
                          0x00, 0xFF);

    /* Enable the transmitter/receiver slots. I2S uses 2 slots */
    McASPTxTimeSlotSet(SOC_MCASP_CFG_BASE, I2S_SLOTS);

    /*
    ** Set the serializers
    */
    McASPSerializerTxSet(SOC_MCASP_CFG_BASE, MCASP_XSER_TX_0);
    McASPSerializerTxSet(SOC_MCASP_CFG_BASE, MCASP_XSER_TX_1);

    /*
    ** Configure the McASP pins
    ** Output - Frame Sync, Clock, Serializer Rx and Serializer Tx
    **          (Clocks generated internally)
    */
    McASPPinMcASPSet(SOC_MCASP_CFG_BASE, (MCASP_PIN_AFSR |
                                          MCASP_PIN_ACLKR | MCASP_PIN_AFSX |
                                          MCASP_PIN_AHCLKX |
                                          MCASP_PIN_ACLKX |
                                          MCASP_PIN_AMUTE |
                                          MCASP_PIN_AXR(MCASP_XSER_TX_0) |
                                          MCASP_PIN_AXR(MCASP_XSER_TX_1)));

    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AFSR);
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_ACLKR);

    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AFSX);

    /* Configure high clock as Output */
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AHCLKX);

    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_ACLKX);

    /* Both Serializers used to output data out */
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_0));
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_1));
}

/*
** Activates the data transmission/reception
** The DMA parameters shall be ready before calling this function.
*/
static void I2SDataTxActivate(void)
{
    /* Start the clocks */
    McASPTxClkStart(SOC_MCASP_CFG_BASE, MCASP_TX_CLK_INTERNAL);

    /* Enable EDMA for the transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHA_MCASP_TX,
                        EDMA3_TRIG_MODE_EVENT);

    /* Activate the  serializers */
    McASPTxSerActivate(SOC_MCASP_CFG_BASE);

    /* make sure that the XDATA bit is cleared to zero */
    while (McASPTxStatusGet(SOC_MCASP_CFG_BASE) & MCASP_TX_STAT_DATAREADY) ;

    /* Activate the state machines */
    McASPTxEnable(SOC_MCASP_CFG_BASE);
}

void sampleConfigScr(unsigned int eventNum,
                     unsigned int chanNum)
{
    unsigned int   scrChanOffset = 0;
    unsigned int   scrRegOffset  = 0;
    unsigned int   xBarEvtNum    = 0;
    IntmuxRegsOvly scrEvtMux     =
        (IntmuxRegsOvly) (EDMA3_EVENT_MUX_REG_BASE_ADDR);

    if ((eventNum < EDMA3_MAX_CROSS_BAR_EVENTS_TI814X) &&
        (chanNum < EDMA3_NUM_TCC))
    {
        scrRegOffset  = chanNum / 2;
        scrChanOffset = chanNum - (scrRegOffset * 2);
        xBarEvtNum    = (eventNum + 1);

        switch (scrChanOffset)
        {
            case 0:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] &=
                    ~(INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    (xBarEvtNum & INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                break;
            case 1:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] &=
                    ~(INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK);
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT) &
                     (INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK));
                break;
            default:
                break;
        }
    }
}

void Configure_Edma_xbar()
{
    sampleConfigScr(MCASP_RX_DMA_XBAR_INST, EDMA3_CHA_MCASP_TX);
}

/*
** The main function. Application starts here.
*/
int main(void)
{
    uint32_t loopHere = 1;

    /*pad config and prcm enable*/
    padConfig_prcmEnable();

    SetupI2C(HSI2C_SLAVE_ADDR);

    /*Clear 6th bit i.e VIN6_SEL_S0 line*/
    SetupI2CTransmit();

#if defined (__ARM_ARCH_7A__)
    EDMAsetRegion(EDMA3_CC_REGION_A15);
#elif defined (__TI_ARM_V7M4__)
    EDMAsetRegion(EDMA3_CC_REGION_M4);
#endif

    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CC_QUEUE);

    Configure_Edma_xbar();

    /* Request EDMA channels */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_CHA_MCASP_TX,
                        EDMA3_CHA_MCASP_TX,
                        EDMA3_CC_QUEUE);

    /* Initialize the DMA parameters */
    I2SDMAParamInit();

    /* Configure the McASP for I2S */
    McASPI2SConfigure();

    /* Activate the audio transmission and reception */
    I2SDataTxActivate();

    /*
    ** Loop forever.
    */
    while (loopHere) ;

    return 0;
}
/***************************** End Of File ***********************************/
