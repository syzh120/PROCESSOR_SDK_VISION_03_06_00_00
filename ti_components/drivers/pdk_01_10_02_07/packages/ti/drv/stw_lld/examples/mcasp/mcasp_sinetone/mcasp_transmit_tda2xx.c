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

/**
 * @file mcaspTransmit.c
 *
 * This file contains the McASP application to generate sine tone.
 * Enable MACRO DEBUG in case for checking I2C read and write values
 *
 */

/******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_mcasp.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/platform/platform.h>

#if (defined (__ARM_ARCH_7A__) || defined (_TMS320C6X))
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#endif

#include "audio_codec.h"
/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/
/* Change MACRO DEBUG to 1 in case for checking I2C read and write values */
#define DEBUG                             (0)

#define SOC_MCASP_3_FIFO_REGS             (SOC_MCASP3_CFG_BASE + 0x1000)

/*
** Values which are configurable
*/
/* Slot size to send/receive data */
#define SLOT_SIZE                         (32U)

/* Word size to send/receive data. Word size <= Slot size */
#define WORD_SIZE                         (32U)

/* Number of channels, L & R */
#define NUM_I2S_CHANNELS                  (2U)

/* Number of serializer */
#define NUM_OF_SERIALIZER                 (1U)

/* Number of samples to be used per audio buffer */
#define NUM_SAMPLES_PER_AUDIO_BUF         (96U)

/* Specify where the parameter set starting is */
#define PAR_ID_START                      (72U)

/* McASP Serializer 0 for Transmit */
#define MCASP_XSER_TX_0                   (0U)

/*
** Below Macros are calculated based on the above inputs
*/
#define I2S_SLOTS                         ((1 << NUM_I2S_CHANNELS) - 1)

#define BYTES_PER_SAMPLE                  ((WORD_SIZE >> 3) \
                                           * NUM_OF_SERIALIZER)

#define AUDIO_BUF_SIZE                    (NUM_SAMPLES_PER_AUDIO_BUF \
                                           * BYTES_PER_SAMPLE)

#define PAR_TX_START                      (PAR_ID_START)

/*
** EMDA paRAM set size
*/
#define SIZE_PARAMSET                     (32U)

/*
** Definitions which are configurable depending on the application requirement
*/
#define MCASP_ACLKX_CLKXDIV_VALUE         (0x6U)
#define MCASP_AHCLKX_HCLKXDIV_VALUE       (0x9U)

/*
** Audio Codec I2C slave address
*/
#if defined (SOC_TDA2EX)
#define AUDIO_CODEC_SLAVE_ADDR            (0x19)
#else
/*
 * In case of TDA2xx rev G or higher boards, if SW8 pin 2 is on, the codec
 * address will be 0x19 and if SW8 pin 2 is off, the codec address will be 0x18.
 * On lower version of boards codec address is fixed at 0x18.
 *
 * If the 10 Inch LCD is connected then the address 0x18 conflicts with the
 * STM touch screen. So on Rev G and above use 0x19 as default address for codec
 *
 * To determine the address of codec app will probe 0x19 first, if this fails
 * probe 0x18 for alternate address assuming 10 inch LCD is not connected.
 *
 */
#define AUDIO_CODEC_SLAVE_ADDR            (0x19)
#define AUDIO_CODEC_SLAVE_ADDR_1          (0x18)
#endif

#define GPIO_IO_EXPANDER_SLAVE_ADDR       (0x26)

/*
** EDMA completion interrupt number
*/
#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (38U)

#ifdef __ARM_ARCH_7A__
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#elif defined _TMS320C6X
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_DSP
#endif

#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK     (0x00FF0000U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT    (0x00000010U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL (0x00000000U)

#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK     (0x000000FFU)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT    (0x00000000U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL (0x00000000U)

#define EDMA3_MAX_CROSS_BAR_EVENTS_TI814X             (230U)

#define EDMA3_EVENT_MUX_REG_BASE_ADDR                 (0x4a002c78)

/*
** Definitions which are configurable depending on the core to be used
*/
#define EDMA3_CHA_MCASP3_TX               (5)

#define EDMA3_CC_REGION_A15               (0U)
#define EDMA3_CC_REGION_DSP               (2U)

#define EDMA3_CC_QUEUE                    (0U)

#define MCASP3_RX_DMA_XBAR_INST           (132U)
#define MCASP3_TX_DMA_XBAR_INST           (133U)

#define I2S_MODE                          (2U)

/******************************************************************************
**                      STRUCTURE DEFINITIONS
******************************************************************************/
typedef struct {
    volatile unsigned int TPCC_EVTMUX[32];
} IntmuxRegs;

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void EDMA3IntSetup(void);
static void I2SDMAParamInit(void);
static void McASPI2SConfigure(void);
static void I2SDataTxActivate(void);
static void EDMA3CCComplIsr(void *dummy);

/*I2C Init*/
void i2c_init(LLD_Hsi2cInstId_t instId);

/*I2C De-Init*/
void i2c_deinit();

LLD_hsi2cErrorCode_t I2CWrite(uint8_t address, uint8_t data);
LLD_hsi2cErrorCode_t I2CWrite1(uint8_t address, uint8_t data);
LLD_hsi2cErrorCode_t I2C_Read(uint8_t address, uint8_t *data);
LLD_hsi2cErrorCode_t I2CWriteBf(uint8_t regAddr, uint8_t bfPosition,
                                uint8_t bfSize,
                                uint8_t bfData);

/*Dac Init*/
static void aic31InitDac();

/*Codec Init*/
static void aic31MdCreateChan();

static LLD_hsi2cErrorCode_t updateAudioCodecAddr(void);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
******************************************************************************/

typedef volatile IntmuxRegs *IntmuxRegsOvly;

/* I2C transfer buffer */
uint8_t        data_tx[4];

/* I2C Receive buffer */
uint8_t        data_rx[4];

int16_t        _sineWavePattern[] =
{
    0x0000, 0x0000, 0x10b4, 0x10b4, 0x2120, 0x2120, 0x30fb, 0x30fb, 0x3fff,
    0x3fff, 0x4dea, 0x4dea, 0x5a81, 0x5a81, 0x658b, 0x658b,
    0x6ed8, 0x6ed8, 0x763f, 0x763f, 0x7ba1, 0x7ba1, 0x7ee5, 0x7ee5, 0x7ffd,
    0x7ffd, 0x7ee5, 0x7ee5, 0x7ba1, 0x7ba1, 0x76ef, 0x76ef,
    0x6ed8, 0x6ed8, 0x658b, 0x658b, 0x5a81, 0x5a81, 0x4dea, 0x4dea, 0x3fff,
    0x3fff, 0x30fb, 0x30fb, 0x2120, 0x2120, 0x10b4, 0x10b4,
    0x0000, 0x0000, 0xef4c, 0xef4c, 0xdee0, 0xdee0, 0xcf06, 0xcf06, 0xc002,
    0xc002, 0xb216, 0xb216, 0xa57f, 0xa57f, 0x9a75, 0x9a75,
    0x9128, 0x9128, 0x89c1, 0x89c1, 0x845f, 0x845f, 0x811b, 0x811b, 0x8002,
    0x8002, 0x811b, 0x811b, 0x845f, 0x845f, 0x89c1, 0x89c1,
    0x9128, 0x9128, 0x9a76, 0x9a76, 0xa57f, 0xa57f, 0xb216, 0xb216, 0xc002,
    0xc002, 0xcf06, 0xcf06, 0xdee0, 0xdee0, 0xef4c, 0xef4c
};

/*
** McASP transmit buffers.
*/
static uint8_t txBuf0[AUDIO_BUF_SIZE];

/*
** I2C instance zero handle
*/
hsI2cHandle    i2cHandle;

/*
** I2C instance one handle
*/
hsI2cHandle    i2cHandle1;

uint8_t        audioCodecSlaveAddr = (uint8_t) AUDIO_CODEC_SLAVE_ADDR;
/******************************************************************************
**                      INTERNAL CONSTATNT DEFINITIONS
******************************************************************************/

/*
** Default paRAM for Transmit section. This will be transmitting from
** a loop buffer.
*/
static EDMA3CCPaRAMEntry const txDefaultPar = {
    (uint32_t) EDMA3CC_OPT_TCC_SET(EDMA3_CHA_MCASP3_TX),
    (uint32_t) txBuf0,                                /* source address */
    (uint16_t) (4),                                   /* aCnt */
    (uint16_t) (AUDIO_BUF_SIZE / 4),                  /* bCnt */
    (uint32_t) (SOC_MCASP3_BASE),                     /* dest address */
    (uint16_t) (4),                                   /* source bIdx */
    (uint16_t) (0),                                   /* dest bIdx */
    (uint16_t) (PAR_TX_START * SIZE_PARAMSET),        /* link address */
    (uint16_t) (1),                                   /* bCnt reload value */
    (uint16_t) (0),                                   /* source cIdx */
    (uint16_t) (0),                                   /* dest cIdx */
    (uint16_t) (1)                                    /* cCnt */
};

/******************************************************************************
**                          FUNCTION DEFINITIONS
******************************************************************************/

/* I2C instance Init */
void i2c_init(LLD_Hsi2cInstId_t instId)
{
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;

    initPar.opMode       = HSI2C_OPMODE_POLLED;
    initPar.i2cBusFreq   = I2C_NORMAL;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, instId, &initPar);

    if (HSI2C_INST_0 == instId)
    {
        i2cHandle = lld_i2c_open(instId, NULL, NULL);
    }
#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX))
    if (HSI2C_INST_1 == instId)
    {
        i2cHandle1 = lld_i2c_open(instId, NULL, NULL);
    }
#elif (defined (SOC_TDA2EX))
    if (HSI2C_INST_4 == instId)
    {
        i2cHandle1 = lld_i2c_open(instId, NULL, NULL);
    }
#endif
}

/* I2C close and deinit */
void i2c_deinit()
{
    lld_i2c_close(&i2cHandle);

    lld_i2c_deinit(HSI2C_INST_0);

    lld_i2c_close(&i2cHandle1);
#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX))
    lld_i2c_deinit(HSI2C_INST_1);
#elif (defined (SOC_TDA2EX))
    lld_i2c_deinit(HSI2C_INST_4);
#endif
}

/* I2C write function */
LLD_hsi2cErrorCode_t I2CWrite(uint8_t address, uint8_t data)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    i2cXferParams.bufLen = 2;
    i2cXferParams.buffer = &data_tx[0];

    data_tx[0] = address;
    data_tx[1] = data;

#if DEBUG
    UARTPuts("\r\n i2c write:   address :  ", -1);
    UARTPutHexNum(data_tx[0]);
    UARTPuts("  data :  ", -1);
    UARTPutHexNum(data_tx[1]);
#endif

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START
                          | LLD_HSI2C_STOP;
    i2cXferParams.slaveAddr = audioCodecSlaveAddr;
    i2cXferParams.timeout   = 0xFFFFFF;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\nI2c write failed ", -1);
    }
#if DEBUG
    else
    {
        UARTPuts("\r\nI2c write successful ", -1);
    }
#endif

    return retVal;
}

LLD_hsi2cErrorCode_t I2CWrite1(uint8_t address, uint8_t data)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    hsI2cHandle                ioexpi2cHandle;

    i2cXferParams.bufLen = 2;
    i2cXferParams.buffer = &data_tx[0];

    data_tx[0] = address;
    data_tx[1] = data;

#if DEBUG
    UARTPuts("\r\n i2c write:   address :  ", -1);
    UARTPutHexNum(data_tx[0]);
    UARTPuts("  data :  ", -1);
    UARTPutHexNum(data_tx[1]);
#endif

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START
                          | LLD_HSI2C_STOP;
    i2cXferParams.slaveAddr = (uint8_t) GPIO_IO_EXPANDER_SLAVE_ADDR;
    i2cXferParams.timeout   = 0x4000;

#if defined (SOC_TDA2PX)
    /* For TDA2PX both io expander and the codec are on i2c0 */
    ioexpi2cHandle = i2cHandle;
#else
    ioexpi2cHandle = i2cHandle1;
#endif
    retVal = lld_i2c_transfer(ioexpi2cHandle, &i2cXferParams);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\nI2c write failed ", -1);
    }
#if DEBUG
    else
    {
        UARTPuts("\r\nI2c write successful ", -1);
    }
#endif

    return retVal;
}

LLD_hsi2cErrorCode_t I2C_Read(uint8_t address, uint8_t *data)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    i2cXferParams.bufLen = 1;
    i2cXferParams.buffer = &data_tx[0];

    data_tx[0] = address; /*address byte msb*/

    i2cXferParams.flags =
        LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START /*|
                                                              *LLD_HSI2C_STOP*/;
    i2cXferParams.slaveAddr = audioCodecSlaveAddr;
    i2cXferParams.timeout   = 0xFFFFFF;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\nI2c write failed ", -1);
    }
#if DEBUG
    else
    {
        UARTPuts("\r\nI2c write successful ", -1);
    }
#endif

    i2cXferParams.buffer = &data_rx[0];
    i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if DEBUG
    UARTPuts("\r\n i2c read :   address :  ", -1);
    UARTPutHexNum(data_tx[0]);
    UARTPuts("  data :  ", -1);
    UARTPutHexNum(data_rx[0]);
#endif

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\nI2c read failed ", -1);
    }
#if DEBUG
    else
    {
        UARTPuts("\r\nI2c read successful ", -1);
        *data = data_rx[0];
    }
#endif

    return retVal;
}

LLD_hsi2cErrorCode_t I2CWriteBf(uint8_t regAddr, uint8_t bfPosition,
                                uint8_t bfSize,
                                uint8_t bfData)
{
    uint8_t regData = 0;              /* Temporary Register data      */
    uint8_t mask    = 0;              /* Bit field mask               */
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    /*Read data from regAddr*/
    retVal = I2C_Read(regAddr, &regData);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\nI2c read failed ", -1);
    }

    mask    = ((1 << bfSize) - 1) << bfPosition;
    regData = (regData & (uint8_t) (~(mask)));
    regData = (regData | (uint8_t) (bfData << bfPosition));

    /* Write the modified data back into the register                 */
    retVal = I2CWrite(regAddr, regData);

    return retVal;
}

/**
 *
 *  \brief  This function writes the initialization values for Aic31 DAC
 *          registers. This function should be called to initialize the
 *          registers of the DAC.
 *
 *  \return None
 */
static void aic31InitDac()
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint8_t gain = 0x24;

    /* Write the initialization values for the DAC registers                  */
    retVal = I2CWriteBf((uint8_t) Aic31_P0_REG7, (uint8_t) 1, (uint8_t) 4,
                        (uint8_t) 5);

    /* power up the left and right DACs                                       */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG37,
                                         (uint8_t) 0xE0));

    /* select the DAC L1 R1 Paths                                             */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG41,
                                         (uint8_t) 0x02));

    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG42,
                                         (uint8_t) 0x6C));

    /* unmute the DAC                                                         */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG43,
                                         (uint8_t) 0x00));
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG44,
                                         (uint8_t) 0x00));

    /* DAC L to HPL OUT Is connected                                          */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG47,
                                         (uint8_t) 0x80));
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG51,
                                         (uint8_t) 0x09));

    /* DAC R to HPROUT is connected                                           */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG64,
                                         (uint8_t) 0x80));
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG65,
                                         (uint8_t) 0x09));

    /* DACL1 connected to LINE1 LOUT                                          */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG82,
                                         (uint8_t) 0x80));
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG86,
                                         (uint8_t) 0x09));

    /* DACR1 connected to LINE1 ROUT                                          */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG92,
                                         (uint8_t) 0x80));
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG93,
                                         (uint8_t) 0x09));

    /* Left/Right DAC digital volume gain                                     */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_LEFT_DAC_VOL_CTRL_ADDR,
                                         /*(uint8_t) gain*/ gain));
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t)
                                         Aic31_RIGHT_DAC_VOL_CTRL_ADDR,
                                         /*(uint8_t) gain*/ gain));

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\nDAC Initialization failed ", -1);
    }
    else
    {
        UARTPuts("\r\nDAC Initialization successful", -1);
    }
}

static void aic31MdCreateChan()
{
    uint8_t tempData            = 0;
    uint8_t pllPValue           = 0;
    uint8_t pllRValue           = 0;
    uint8_t pllJValue           = 0;
    uint8_t pllDLowValue        = 0;
    uint8_t pllDHighValue       = 0;
    uint8_t dualRate            = 0;
    uint8_t sampleRateDiv       = 0;
    uint8_t fsRef               = 0;
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    /* Select Register Page 0 of Aic31                            */
    retVal = I2CWrite(Aic31_PAGE_SELECT_ADDR, Aic31_PAGE_0);

    /* Reset the Aic31                                            */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal | I2CWrite(Aic31_P0_REG1, (uint8_t) 0x80));

    /* Configure the audio serial data interface mode             */
    tempData = (0U << 6U);

    /* configure the slot width                                   */
    tempData |= (3U << 4U);

    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite(Aic31_SERIAL_INTERFACEB_ADDR, tempData));

    /* Configure sampleRateDiv and dualRate                        */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG2, (uint8_t) 0,
                                           (uint8_t) 4,
                                           (uint8_t)
                                           sampleRateDiv));

    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG7, (uint8_t) 5,
                                           (uint8_t) 1,
                                           (uint8_t) dualRate));

    /* enable the PLL                                             */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG3, (uint8_t) 7,
                                           (uint8_t) 1,
                                           (uint8_t) 1));

    /* select the MCLK as the input for the PLL and CLKDIV(N = 16)*/
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG102,
                                           (uint8_t) 4, (uint8_t) 2,
                                           (uint8_t) 0x00));

    /* select the PLL_IN as codec input                           */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG101,
                                           (uint8_t) 0, (uint8_t) 1,
                                           (uint8_t) 0x00));

    /* selec the GPIO to output the divided PLL_IN clock(test purpose)*/
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG98,
                                         (uint8_t) 0x20));

    /* Write to PLL programming register A                            */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG3, (uint8_t) 0,
                                           (uint8_t) 3,
                                           pllPValue));

    /* Write to PLL programming register B                            */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG4, (uint8_t) 2,
                                           (uint8_t) 6,
                                           pllJValue));

    /* write the high and low bits of the D value                     */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal | I2CWrite(Aic31_P0_REG5, pllDHighValue));

    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWrite((uint8_t) Aic31_P0_REG6,
                                         (uint8_t) (pllDLowValue << 2)));

    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG11,
                                           (uint8_t) 0, (uint8_t) 4,
                                           pllRValue));

    /* Write to codec datapath setup register                         */
    retVal =
        (LLD_hsi2cErrorCode_t) (retVal |
                                I2CWriteBf((uint8_t) Aic31_P0_REG7, (uint8_t) 7,
                                           (uint8_t) 1,
                                           fsRef));

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\r\n Codec Init failed ", -1);
    }
    else
    {
        UARTPuts("\r\n Codec Init successful ", -1);
    }

    /* Initialize DAC*/
    aic31InitDac();
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
    int16_t          *sineToneDataPtr = NULL;
    int32_t          *temp;
    uint32_t          i = 0;
    EDMA3CCPaRAMEntry paramSet;

    /* Initialize TX Buffers
     *
     * These patterns are seen/output on serializer0 and serializer1
     */

    sineToneDataPtr = _sineWavePattern;

    temp = (int32_t *) txBuf0;

    for (i = 0; i < (AUDIO_BUF_SIZE / 4); i++)
    {
        *temp = (int32_t) (*sineToneDataPtr);

        temp++;
        sineToneDataPtr++;
    }

    /* Initialize the 1st paRAM set for transmit */
    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHA_MCASP3_TX, &paramSet);

    /*Set Link parameters*/
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, PAR_TX_START, &paramSet);
}

/*
** Configures the McASP Transmit Section in I2S mode.
*/
static void McASPI2SConfigure(void)
{
    McASPTxReset(SOC_MCASP3_CFG_BASE);

    /* Enable the FIFOs for DMA transfer */
    McASPWriteFifoEnable(SOC_MCASP_3_FIFO_REGS, 1, 1);

    /* Set the mask assuming integer format for 32 bit word*/
    McASPTxFmtMaskSet(SOC_MCASP3_CFG_BASE, 0xFFFFFFFF);

    /* Set I2S format in the transmitter/receiver format units */
    McASPTxFmtSet(SOC_MCASP3_CFG_BASE, (MCASP_TX_SYNC_DELAY_0BIT |
                                        MCASP_TX_BITSTREAM_MSB_FIRST |
                                        MCASP_TX_SLOTSIZE_32BITS |
                                        MCASP_TX_ROT_RIGHT_20BITS));

    McASPTxFrameSyncCfg(SOC_MCASP3_CFG_BASE, I2S_MODE, MCASP_TX_FS_WIDTH_WORD,
                        MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE |
                        MCASP_TX_FS_INTERNAL);

    /* configure the clock for transmitter */
    McASPTxClkCfg(SOC_MCASP3_CFG_BASE, MCASP_TX_CLK_INTERNAL,
                  ((MCASP_ACLKX_CLKXDIV_VALUE & MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((MCASP_AHCLKX_HCLKXDIV_VALUE &
                    MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    McASPTxClkPolaritySet(SOC_MCASP3_CFG_BASE, MCASP_TX_CLK_POL_FALL_EDGE);

    McASPTxClkCheckConfig(SOC_MCASP3_CFG_BASE, MCASP_TX_CLKCHCK_DIV32, 0x00,
                          0xFF);

    /* Enable the transmitter/receiver slots. I2S uses 2 slots */
    McASPTxTimeSlotSet(SOC_MCASP3_CFG_BASE, I2S_SLOTS);

    /*
    ** Set the serializers
    */
    McASPSerializerTxSet(SOC_MCASP3_CFG_BASE, MCASP_XSER_TX_0);

    /*
    ** Configure the McASP pins
    ** Output - Frame Sync, Clock, Serializer Rx and Serializer Tx
    **          (Clocks generated internally)
    */
    McASPPinMcASPSet(SOC_MCASP3_CFG_BASE,
                     (MCASP_PIN_AFSX
                      | MCASP_PIN_AHCLKX | MCASP_PIN_ACLKX | MCASP_PIN_AMUTE
                      | MCASP_PIN_AXR(MCASP_XSER_TX_0)
                     ));

    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AFSR);
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_ACLKR);

    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AFSX);

    /* Configure high clock as Output */
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AHCLKX);

    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_ACLKX);

    /* Both Serializers used to output data out */
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_0));
}

/*
** Sets up the interrupts for EDMA in AINTC
*/
static void EDMA3IntSetup(void)
{
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

#ifdef __ARM_ARCH_7A__
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 7,
                   EDMA_TPCC_IRQ_REGION0);

#elif defined (_TMS320C6X)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1, 7,
                   EDMA_TPCC_IRQ_REGION2);
#endif

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT,
                     (IntrFuncPtr) EDMA3CCComplIsr,
                     NULL);
    Intc_IntPrioritySet(EDMA3_CC_XFER_COMPLETION_INT, 1, 0);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT);
}

/*
** Activates the data transmission/reception
** The DMA parameters shall be ready before calling this function.
*/
static void I2SDataTxActivate(void)
{
    /* Start the clocks */
    McASPTxClkStart(SOC_MCASP3_CFG_BASE, MCASP_TX_CLK_INTERNAL);

    /* Enable EDMA for the transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHA_MCASP3_TX,
                        EDMA3_TRIG_MODE_EVENT);

    /* Activate the  serializers */
    McASPTxSerActivate(SOC_MCASP3_CFG_BASE);

    /* make sure that the XDATA bit is cleared to zero */
    while (McASPTxStatusGet(SOC_MCASP3_CFG_BASE) & MCASP_TX_STAT_DATAREADY) ;

    /* Activate the state machines */
    McASPTxEnable(SOC_MCASP3_CFG_BASE);
}

void sampleConfigScr(unsigned int eventNum, unsigned int chanNum) {
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

/*Configure EDMA Xbar*/
void Configure_Edma_xbar()
{
    sampleConfigScr(MCASP3_RX_DMA_XBAR_INST, EDMA3_CHA_MCASP3_TX);
}

/*Pin Mux and Clk config*/
void pinMuxClkConfig(void)
{
    /*Unlock the Control registers */
    PlatformUnlockMMR();

    /* Pad mux configuration for McASP instance 2 */
    PlatformMCASP3SetPinMux();

    /* Power on McASP instance 2*/
    PlatformMCASP3PrcmEnable();
#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX))
    /* Pad mux configuration for I2C instance 2 */
    PlatformI2C2SetPinMux();
#elif (defined (SOC_TDA2EX))
    /* Pad mux configuration for I2C instance 5 */
    PlatformI2C5SetPinMux();
#endif

    PlatformUART1SetPinMux();
}

/*Edma Config*/
void edmaConfig(void)
{
#if defined (__ARM_ARCH_7A__)
    EDMAsetRegion(EDMA3_CC_REGION_A15);
#elif defined (_TMS320C6X)
    EDMAsetRegion(EDMA3_CC_REGION_DSP);
#endif

    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CC_QUEUE);

    Configure_Edma_xbar();

    EDMA3IntSetup();

    /* Request EDMA channels */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_CHA_MCASP3_TX, EDMA3_CHA_MCASP3_TX,
                        EDMA3_CC_QUEUE);
}

static LLD_hsi2cErrorCode_t updateAudioCodecAddr(void)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    retVal = lld_i2c_probe(i2cHandle, AUDIO_CODEC_SLAVE_ADDR);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
#ifdef AUDIO_CODEC_SLAVE_ADDR_1
        retVal = lld_i2c_probe(i2cHandle, AUDIO_CODEC_SLAVE_ADDR_1);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nProbe to audio codec failed ", -1);
            retVal = LLD_HSI2C_FAIL;
        }
        else
        {
            /* Use the Alternate Audio Codec Addr */
            audioCodecSlaveAddr = AUDIO_CODEC_SLAVE_ADDR_1;
        }
#else
        UARTPuts("\r\nProbe to audio codec failed ", -1);
        retVal = LLD_HSI2C_FAIL;

#endif
    }
    else
    {
        /* Use the default Audio Codec Addr */
        audioCodecSlaveAddr = AUDIO_CODEC_SLAVE_ADDR;
    }

    return retVal;
}

/*
** The
** main function. Application starts here.
*/
int main(void)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    /*Pin Mux and Clk config*/
    pinMuxClkConfig();

    UARTStdioInit();

    UARTPuts("\r\nMcASP Sinetone application ", -1);

    /*I2C instance 0 init*/
    i2c_init(HSI2C_INST_0);

#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX))
    /*I2C instance 1 init*/
    i2c_init(HSI2C_INST_1);
#elif (defined (SOC_TDA2EX))
    /*I2C instance 1 init*/
    i2c_init(HSI2C_INST_4);
#endif

    retVal = updateAudioCodecAddr();
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        /* Cannot Probe the audio codec */
        while (1) ;
    }
    /*Clear 6th bit i.e VIN6_SEL_S0 line of IO Expander*/
    I2CWrite1(0x00, 0x00);
    UARTPuts("\r\nGPIO Expander configured ", -1);

    /*Edma Config*/
    edmaConfig();

    /*Init Codec and DAC*/
    aic31MdCreateChan();

    /* Initialize the DMA parameters */
    I2SDMAParamInit();
    UARTPuts("\r\nI2S DMA PAram init done ", -1);

    /* Configure the McASP*/
    McASPI2SConfigure();
    UARTPuts("\r\nMcASP Confgiured ", -1);

    /* Activate the audio transmission and reception */
    I2SDataTxActivate();

    /*De-initialize I2C*/
    i2c_deinit();

    /* Data Transfer happens infinitely even though application ends
     * here. Removed while loop as compiler issues warning of non
     * returnable main function
     */
    return 0;
}

/*
** EDMA transfer completion ISR
*/
static void EDMA3CCComplIsr(void *dummy)
{
    /* Check if transmit DMA completed */
    if (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) & (1 << EDMA3_CHA_MCASP3_TX))
    {
        /* Clear the interrupt status for the first channel */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHA_MCASP3_TX);
    }
}

/***************************** End Of File ***********************************/
