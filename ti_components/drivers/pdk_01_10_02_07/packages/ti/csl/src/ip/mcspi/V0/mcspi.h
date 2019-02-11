/*
 *  Copyright (C) 2013 - 2017 Texas Instruments Incorporated - www.ti.com
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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_MCSPI McSPI
 *
 *  @{
 */
/**
 * \file       mcspi.h
 *
 * \brief      This file contains the function prototypes for the device
 *             abstraction layer for MCSPI. It also contains necessary
 *             structure, enum and macro definitions.
 *
 * \details    Programming sequence of MCSPI is as follows:
 *             -# MCSPI can be put into reset by calling the API
 *                McSPIReset.
 *             -# MCSPI CS can be enabled by calling the API McSPICSEnable.
 *             -# Polarity of CS can be configured by calling the API
 *                McSPICSPolarityConfig.
 *             -# Master Mode configurations by calling the API
 *                McSPIMasterModeConfig.
 *             -# MCSPI output clock can be configured by calling the API
 *                McSPIClkConfig.
 *             -# Word length of MCSPI can be configured by calling the API
 *                McSPIWordLengthSet.
 *             -# Transmit Fifo can be enabled/disabled by calling the API
 *                McSPITxFIFOConfig.
 *             -# Receive Fifo can be enabled/disabled by calling the API
 *                McSPIRxFIFOConfig.
 *             -# Assert the CS of MCSPI by calling the API McSPICSAssert.
 *             -# Deassert the CS of MCSPI by calling the API McSPICSDeAssert.
 *             -# MCSPI interrupts can be enabled by calling the API
 *                McSPIIntEnable and disabled by calling the API
 *                McSPIIntDisable.
 *             -# MCSPI channel can be enabled by calling the API
 *                McSPIChannelEnable and disabled by calling the API
 *                McSPIChannelDisable.
 *             -# Status on MCSPI interrupts can be checked by calling the API
 *                McSPIIntStatusGet.
 *             -# MCSPI interrupts status can be cleared by calling the API
 *                McSPIIntStatusClear.
 *             -# Data to be transmitted is to be written to the transmit
 *                register by calling the API McSPITransmitData.
 *             -# Received data into the MCSPI receive register can be read
 *                by calling the API McSPIReceiveData.
 *
 **/

#ifndef MCSPI_H_
#define MCSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_mcspi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * \name Values used to determine the channel number used for McSPI
 * communication.
 * @{
 */
/**
 * \brief McSPI channel 0 is used for data communication
 */
#define MCSPI_CHANNEL_0                (0U)

/**
 * \brief McSPI channel 1 is used for data communication
 */
#define MCSPI_CHANNEL_1                (1U)

/**
 * \brief McSPI channel 2 is used for data communication
 */
#define MCSPI_CHANNEL_2                (2U)

/**
 * \brief McSPI channel 3 is used for data communication
 */
#define MCSPI_CHANNEL_3                (3U)
/* @} */

/*
 * \name Values of polarity and phase of SPICLK that are used to configure the
 * clock value in various modes of operation.
 * @{
 */
/**
 * \brief McSPI clock Mode 0 is selected
 *        SPICLK is active high and sampling occurs on the rising edge
 */
#define MCSPI_CLK_MODE_0            (((uint32_t) MCSPI_CH0CONF_POL_ACTIVEHIGH \
                                      << MCSPI_CH0CONF_POL_SHIFT) |           \
                                     MCSPI_CH0CONF_PHA_ODD)

/**
 * \brief McSPI clock Mode 1 is selected
 *        SPICLK is active high and sampling occurs on the falling edge
 */
#define MCSPI_CLK_MODE_1            (((uint32_t) MCSPI_CH0CONF_POL_ACTIVEHIGH \
                                      << MCSPI_CH0CONF_POL_SHIFT) |           \
                                     MCSPI_CH0CONF_PHA_EVEN)

/**
 * \brief McSPI clock Mode 2 is selected
 *        SPICLK is active low and sampling occurs on the falling edge
 */
#define MCSPI_CLK_MODE_2            (((uint32_t) MCSPI_CH0CONF_POL_ACTIVELOW << \
                                      MCSPI_CH0CONF_POL_SHIFT) |                \
                                     MCSPI_CH0CONF_PHA_ODD)

/**
 * \brief McSPI clock Mode 3 is selected
 *        SPICLK is active low and sampling occurs on the rising edge
 */
#define MCSPI_CLK_MODE_3            (((uint32_t) MCSPI_CH0CONF_POL_ACTIVELOW << \
                                      MCSPI_CH0CONF_POL_SHIFT) |                \
                                     MCSPI_CH0CONF_PHA_EVEN)
/* @} */

/*
 * \name McSPI Register Offset for MCSPI_CHxCONF, MCSPI_CHxSTAT, MCSPI_CHxCTRL,
 * MCSPI_TXx and MCSPI_RXx register set.
 * @{
 */
/**
 * \brief McSPI Register Offset for MCSPI_CHxCONF, MCSPI_CHxSTAT, MCSPI_CHxCTRL,
 *        MCSPI_TXx and MCSPI_RXx register sets
 */
#define MCSPI_REG_OFFSET            (0x14U)

/**
 * \brief Base address of McSPI Channel configuration : MCSPI_CHCONF(x)
 */
#define MCSPI_CHCONF(x)             ((uint32_t) MCSPI_CH0CONF + \
                                     (uint32_t) ((uint32_t) MCSPI_REG_OFFSET * \
                                     ((uint32_t) (x))))

/**
 * \brief Base address of McSPI Channel status : McSPI_CHSTAT(x)
 */
#define MCSPI_CHSTAT(x)             ((uint32_t) MCSPI_CH0STAT + \
                                     (uint32_t) ((uint32_t) MCSPI_REG_OFFSET * \
                                     ((uint32_t) (x))))

/**
 * \brief Base address of McSPI_CHCTRL(x) which is used to enable channel
 */
#define MCSPI_CHCTRL(x)             ((uint32_t) MCSPI_CH0CTRL + \
                                     (uint32_t) ((uint32_t) MCSPI_REG_OFFSET * \
                                     ((uint32_t) (x))))

/**
 * \brief Base address of McSPI_CHTX(x) which is used to store data to be
 *        transmitted
 */
#define MCSPI_CHTX(x)               ((uint32_t) MCSPI_TX0 + \
                                     (uint32_t) ((uint32_t) MCSPI_REG_OFFSET * \
                                     ((uint32_t) (x))))

/**
 * \brief Base address of McSPI_CHRX(x) which is used to store data to be
 *        received
 */
#define MCSPI_CHRX(x)               ((uint32_t) MCSPI_RX0 + \
                                     (uint32_t) ((uint32_t) MCSPI_REG_OFFSET * \
                                     ((uint32_t) (x))))
/* @} */

/*
 * \name Values of minumum & maximum word lengths that is valid for SPI channel
 * config.
 * @{
 */
/**
 * \brief Minumum word lengths that is valid for McSPI channel configuration
 */
#define MCSPI_WORD_LENGTH_MIN            ((uint32_t) 4U)

/**
 * \brief Maximum word lengths that is valid for McSPI channel configuration
 */
#define MCSPI_WORD_LENGTH_MAX            ((uint32_t) 32U)
/* @} */

/*
 * \name Values used to set the word length for McSPI communication.
 * 'n' can take values only between 4 <= n <= 32.
 * @{
 */
/**
 * \brief Values used to set the word length for McSPI communication
 *        'n' can take values only between 4 <= n <= 32.
 */
#define MCSPI_WORD_LENGTH(n)        ((((uint32_t) (n)) - \
                                      (uint32_t) 1U) << MCSPI_CH0CONF_WL_SHIFT)
/* @} */

/*
 * \name Values used to configure the chip select time control(TCS).
 * @{
 */
/**
 * \brief chip select time control(TCS) configuration : Zero interface clock
 *        cycle between CS toggling and first or last edge of SPI clock
 */
#define MCSPI_CS_TCS_0PNT5_CLK      ((uint32_t) MCSPI_CH0CONF_TCS0_ZEROCYCLEDLY \
                                     << MCSPI_CH0CONF_TCS0_SHIFT)

/**
 * \brief chip select time control(TCS) configuration : One interface clock
 *        cycle between CS toggling and first or last edge of SPI clock
 */
#define MCSPI_CS_TCS_1PNT5_CLK      ((uint32_t) MCSPI_CH0CONF_TCS0_ONECYCLEDLY \
                                     << MCSPI_CH0CONF_TCS0_SHIFT)

/**
 * \brief chip select time control(TCS) configuration : Two interface clock
 *        cycles between CS toggling and first or last edge of SPI clock
 */
#define MCSPI_CS_TCS_2PNT5_CLK      ((uint32_t) MCSPI_CH0CONF_TCS0_TWOCYCLEDLY \
                                     << MCSPI_CH0CONF_TCS0_SHIFT)

/**
 * \brief chip select time control(TCS) configuration : Three interface clock
 *        cycles between CS toggling and first or last edge of SPI clock
 */
#define MCSPI_CS_TCS_3PNT5_CLK      ((uint32_t)                          \
                                     MCSPI_CH0CONF_TCS0_THREECYCLEDLY << \
                                     MCSPI_CH0CONF_TCS0_SHIFT)
/* @} */

/*
 * \name Value used to set the polarity for start bit for McSPI communication.
 * @{
 */
/**
 * \brief Low polarity is set for start bit for McSPI communication.
 */
#define MCSPI_START_BIT_POL_LOW     (MCSPI_CH0CONF_SBPOL_LOWLEVEL)

/**
 * \brief High polarity is set for start bit for McSPI communication.
 */
#define MCSPI_START_BIT_POL_HIGH    (MCSPI_CH0CONF_SBPOL_HIGHLEVEL)
/* @} */

/*
 * \name Values used to determine transmit/receive modes of McSPI peripheral in
 * master mode.
 * @{
 */
/**
 * \brief Transmit-receive mode of McSPI peripheral in master mode is configured
 */
#define MCSPI_TX_RX_MODE            ((uint32_t) MCSPI_CH0CONF_TRM_TRANSRECEI << \
                                     MCSPI_CH0CONF_TRM_SHIFT)

/**
 * \brief Only Receive mode of McSPI peripheral in master mode is configured
 */
#define MCSPI_RX_ONLY_MODE          ((uint32_t) MCSPI_CH0CONF_TRM_RECEIVONLY << \
                                     MCSPI_CH0CONF_TRM_SHIFT)

/**
 * \brief Only Transmit mode of McSPI peripheral in master mode is configured
 */
#define MCSPI_TX_ONLY_MODE          ((uint32_t) MCSPI_CH0CONF_TRM_TRANSONLY << \
                                     MCSPI_CH0CONF_TRM_SHIFT)
/* @} */

/*
 * \name Values used to configure communication on data line pins.
 * @{
 */
/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 0 (SPIDAT[0]) selected for reception
 *        Data line 1 (SPIDAT[1]) selected for transmission
 *        Data Line 0 (SPIDAT[0]) selected for transmission
 */
#define MCSPI_DATA_LINE_COMM_MODE_0  (((uint32_t) MCSPI_CH0CONF_IS_LINE0 <<     \
                                       MCSPI_CH0CONF_IS_SHIFT) |                \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_ENABLED << \
                                       MCSPI_CH0CONF_DPE1_SHIFT) |              \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_ENABLED << \
                                       MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 0 (SPIDAT[0]) selected for reception
 *        Data line 1 (SPIDAT[1]) selected for transmission
 *        No transmission on Data Line 0 (SPIDAT[0])
 */
#define MCSPI_DATA_LINE_COMM_MODE_1  (((uint32_t) MCSPI_CH0CONF_IS_LINE0 <<     \
                                       MCSPI_CH0CONF_IS_SHIFT) |                \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_ENABLED << \
                                       MCSPI_CH0CONF_DPE1_SHIFT) |              \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_DISABLED   \
                                       << MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 0 (SPIDAT[0]) selected for reception
 *        No transmission on Data Line 1 (SPIDAT[1])
 *        Data line 0 (SPIDAT[0]) selected for transmission
 */
#define MCSPI_DATA_LINE_COMM_MODE_2  (((uint32_t) MCSPI_CH0CONF_IS_LINE0 <<     \
                                       MCSPI_CH0CONF_IS_SHIFT) |                \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_DISABLED   \
                                       << MCSPI_CH0CONF_DPE1_SHIFT) |           \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_ENABLED << \
                                       MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 0 (SPIDAT[0]) selected for reception
 *        No transmission on Data Line 1 (SPIDAT[1])
 *        No transmission on Data Line 0 (SPIDAT[0])
 */
#define MCSPI_DATA_LINE_COMM_MODE_3  (((uint32_t) MCSPI_CH0CONF_IS_LINE0 <<   \
                                       MCSPI_CH0CONF_IS_SHIFT) |              \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_DISABLED \
                                       << MCSPI_CH0CONF_DPE1_SHIFT) |         \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_DISABLED \
                                       << MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 1 (SPIDAT[1]) selected for reception
 *        Data line 1 (SPIDAT[1]) selected for transmission
 *        Data Line 0 (SPIDAT[0]) selected for transmission
 */
#define MCSPI_DATA_LINE_COMM_MODE_4  (((uint32_t) MCSPI_CH0CONF_IS_LINE1 <<     \
                                       MCSPI_CH0CONF_IS_SHIFT) |                \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_ENABLED << \
                                       MCSPI_CH0CONF_DPE1_SHIFT) |              \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_ENABLED << \
                                       MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 1 (SPIDAT[1]) selected for reception
 *        Data line 1 (SPIDAT[1]) selected for transmission
 *        No transmission on Data Line 0 (SPIDAT[0])
 */
#define MCSPI_DATA_LINE_COMM_MODE_5  (((uint32_t) MCSPI_CH0CONF_IS_LINE1 <<     \
                                       MCSPI_CH0CONF_IS_SHIFT) |                \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_ENABLED << \
                                       MCSPI_CH0CONF_DPE1_SHIFT) |              \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_DISABLED   \
                                       << MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 1 (SPIDAT[1]) selected for reception
 *        No transmission on Data Line 1 (SPIDAT[1])
 *        Data line 0 (SPIDAT[0]) selected for transmission
 */
#define MCSPI_DATA_LINE_COMM_MODE_6  (((uint32_t) MCSPI_CH0CONF_IS_LINE1 <<     \
                                       MCSPI_CH0CONF_IS_SHIFT) |                \
                                      ((uint32_t) MCSPI_CH0CONF_DPE1_DISABLED   \
                                       << MCSPI_CH0CONF_DPE1_SHIFT) |           \
                                      ((uint32_t) MCSPI_CH0CONF_DPE0_ENABLED << \
                                       MCSPI_CH0CONF_DPE0_SHIFT))

/**
 * \brief Communication on Data line pins is configured as :
 *        Data line 1 (SPIDAT[1]) selected for reception
 *        No transmission on Data Line 1 (SPIDAT[1])
 *        No transmission on Data Line 0 (SPIDAT[0])
 */
#define MCSPI_DATA_LINE_COMM_MODE_7   (((uint32_t) MCSPI_CH0CONF_IS_LINE1 <<   \
                                        MCSPI_CH0CONF_IS_SHIFT) |              \
                                       ((uint32_t) MCSPI_CH0CONF_DPE1_DISABLED \
                                        << MCSPI_CH0CONF_DPE1_SHIFT) |         \
                                       ((uint32_t) MCSPI_CH0CONF_DPE0_DISABLED \
                                        << MCSPI_CH0CONF_DPE0_SHIFT))
/* @} */

/*
 * \name Values used to enable/disable the Tx/Rx FIFOs of McSPI peripheral.
 * @{
 */
/**
 * \brief McSPI peripheral Rx FIFO is enabled
 */
#define MCSPI_RX_FIFO_ENABLE         ((uint32_t) MCSPI_CH0CONF_FFER_FFENABLED \
                                      <<                                      \
                                      MCSPI_CH0CONF_FFER_SHIFT)

/**
 * \brief McSPI peripheral Rx FIFO is disabled
 */
#define MCSPI_RX_FIFO_DISABLE        ((uint32_t) MCSPI_CH0CONF_FFER_FFDISABLED \
                                      << MCSPI_CH0CONF_FFER_SHIFT)

/**
 * \brief McSPI peripheral Tx FIFO is enabled
 */
#define MCSPI_TX_FIFO_ENABLE         ((uint32_t) MCSPI_CH0CONF_FFEW_FFENABLED \
                                      << MCSPI_CH0CONF_FFEW_SHIFT)

/**
 * \brief McSPI peripheral Tx FIFO is disabled
 */
#define MCSPI_TX_FIFO_DISABLE        ((uint32_t) MCSPI_CH0CONF_FFEW_FFDISABLED \
                                      << MCSPI_CH0CONF_FFEW_SHIFT)
/* @} */

/*
 * \name Values used to enable/disable the read/write DMA events of McSPI
 * peripheral.
 * @{
 */
/**
 * \brief McSPI peripheral read DMA event is enabled
 */
#define MCSPI_DMA_RX_EVENT           ((uint32_t) MCSPI_CH0CONF_DMAR_ENABLED << \
                                      MCSPI_CH0CONF_DMAR_SHIFT)

/**
 * \brief McSPI peripheral write DMA event is enabled
 */
#define MCSPI_DMA_TX_EVENT           ((uint32_t) MCSPI_CH0CONF_DMAW_ENABLED << \
                                      MCSPI_CH0CONF_DMAW_SHIFT)
/* @} */

/*
 * \name Values that can be passed to enable/disable/clear status of  the
 * various interrupts of McSPI peripheral.
 * These macros can also be used to check the status obtained from
 * 'McSPIIntStatusGet' API.
 * @{
 */
/**
 * \brief Mask value of TX Empty interrupt enable of McSPI peripheral for the
 *        corresponding channel
 */
#define MCSPI_INT_TX_EMPTY(chan)     ((uint32_t)                               \
                                      MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_MASK << \
                                      ((chan) * 4))

/**
 * \brief Mask value of TX Underflow interrupt enable of McSPI peripheral for
 *        the corresponding channel
 */
#define MCSPI_INT_TX_UNDERFLOW(chan) ((uint32_t)                                \
                                      MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_MASK \
                                      << ((chan) * (uint32_t) 4))

/**
 * \brief Mask value of RX Full interrupt enable of McSPI peripheral for
 *        the corresponding channel
 */
#define MCSPI_INT_RX_FULL(chan)      ((uint32_t)                              \
                                      MCSPI_IRQENABLE_RX0_FULL_ENABLE_MASK << \
                                      ((chan) * 4))

/**
 * \brief Mask value of RX Overflow interrupt status of McSPI peripheral
 */
#define MCSPI_INT_RX0_OVERFLOW       ((uint32_t) \
                                      MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK)

/**
 * \brief Mask value of End of word count interrupt enable of McSPI peripheral
 */
#define MCSPI_INT_EOWKE              ((uint32_t)                               \
                                      MCSPI_IRQENABLE_EOW_ENABLE_IRQENABLED << \
                                      MCSPI_IRQENABLE_EOW_ENABLE_SHIFT)
/* @} */

/*
 * \name Values used to enable initial delay for first transfer from McSPI
 * peripheral.
 * @{
 */
/**
 * \brief No delay is configured for first spi transfer from McSPI peripheral.
 */
#define MCSPI_INITDLY_0              ((uint32_t)                         \
                                      MCSPI_MODULCTRL_INITDLY_NODELAY << \
                                      MCSPI_MODULCTRL_INITDLY_SHIFT)
/**
 * \brief 4 SPI bus clock delays is configured for first spi transfer from McSPI
 *        peripheral.
 */
#define MCSPI_INITDLY_4              ((uint32_t)                         \
                                      MCSPI_MODULCTRL_INITDLY_4CLKDLY << \
                                      MCSPI_MODULCTRL_INITDLY_SHIFT)

/**
 * \brief 8 SPI bus clock delays is configured for first spi transfer from McSPI
 *        peripheral.
 */
#define MCSPI_INITDLY_8              ((uint32_t)                         \
                                      MCSPI_MODULCTRL_INITDLY_8CLKDLY << \
                                      MCSPI_MODULCTRL_INITDLY_SHIFT)

/**
 * \brief 16 SPI bus clock delays is configured for first spi transfer from
 *        McSPI peripheral.
 */
#define MCSPI_INITDLY_16             ((uint32_t)                          \
                                      MCSPI_MODULCTRL_INITDLY_16CLKDLY << \
                                      MCSPI_MODULCTRL_INITDLY_SHIFT)

/**
 * \brief 32 SPI bus clock delays is configured for first spi transfer from
 *        McSPI peripheral.
 */
#define MCSPI_INITDLY_32             ((uint32_t)                          \
                                      MCSPI_MODULCTRL_INITDLY_32CLKDLY << \
                                      MCSPI_MODULCTRL_INITDLY_SHIFT)
/* @} */

/*
 * \name Values used to check the status of McSPI channel status registers and
 * FIFO.
 * @{
 */
/**
 * \brief McSPI channel status if Rx buffer is full
 */
#define MCSPI_CH_STAT_RXS_FULL       ((uint32_t) MCSPI_CH0STAT_RXS_FULL << \
                                      MCSPI_CH0STAT_RXS_SHIFT)

/**
 * \brief McSPI channel status if Tx buffer is empty
 */
#define MCSPI_CH_STAT_TXS_EMPTY      ((uint32_t) MCSPI_CH0STAT_TXS_EMPTY << \
                                      MCSPI_CH0STAT_TXS_SHIFT)

/**
 * \brief McSPI channel status if End of Transfer is completed
 */
#define MCSPI_CH_STAT_EOT            ((uint32_t) MCSPI_CH0STAT_EOT_COMPLETED << \
                                      MCSPI_CH0STAT_EOT_SHIFT)

/**
 * \brief McSPI channel status if Tx FIFO buffer is empty
 */
#define MCSPI_CH_TXFFE               ((uint32_t) MCSPI_CH0STAT_TXFFE_EMPTY << \
                                      MCSPI_CH0STAT_TXFFE_SHIFT)

/**
 * \brief McSPI channel status if Tx FIFO buffer is full
 */
#define MCSPI_CH_TXFFF               ((uint32_t) MCSPI_CH0STAT_TXFFF_FULL << \
                                      MCSPI_CH0STAT_TXFFF_SHIFT)

/**
 * \brief McSPI channel status if Rx FIFO buffer is empty
 */
#define MCSPI_CH_RXFFE               ((uint32_t) MCSPI_CH0STAT_RXFFE_EMPTY << \
                                      MCSPI_CH0STAT_RXFFE_SHIFT)

/**
 * \brief McSPI channel status if Rx FIFO buffer is full
 */
#define MCSPI_CH_RXFFF               ((uint32_t) MCSPI_CH0STAT_RXFFF_FULL << \
                                      MCSPI_CH0STAT_RXFFF_SHIFT)
/* @} */

/*
 * \name Value used to enable/disable multiple word ocp access.
 * @{
 */
/**
 * \brief Multiple word ocp access is enabled
 */
#define MCSPI_MOA_ENABLE            ((uint32_t) MCSPI_MODULCTRL_MOA_MULTIACCES \
                                     << MCSPI_MODULCTRL_MOA_SHIFT)

/**
 * \brief Multiple word ocp access is disabled
 */
#define MCSPI_MOA_DISABLE           ((uint32_t)                           \
                                     MCSPI_MODULCTRL_MOA_NOMULTIACCESS << \
                                     MCSPI_MODULCTRL_MOA_SHIFT)
/* @} */

/*
 * \name Value used to configure to single/multiple channel.
 * @{
 */
/**
 * \brief Single channel is configured for MCSPI Peripheral
 */
#define MCSPI_SINGLE_CH            ((uint32_t) MCSPI_MODULCTRL_SINGLE_SINGLE << \
                                    MCSPI_MODULCTRL_SINGLE_SHIFT)

/**
 * \brief Multi channel is configured for MCSPI Peripheral
 */
#define MCSPI_MULTI_CH            ((uint32_t) MCSPI_MODULCTRL_SINGLE_MULTI << \
                                   MCSPI_MODULCTRL_SINGLE_SHIFT)
/* @} */

/*
 * \name Value used to configure the Chip select Polarity
 * @{
 */
/**
 * \brief Chip select is held high during active state
 */
#define MCSPI_CS_POL_HIGH          ((uint32_t) MCSPI_CH0CONF_EPOL_ACTIVEHIGH << \
                                    MCSPI_CH0CONF_EPOL_SHIFT)

/**
 * \brief Chip select is held low during active state
 */
#define MCSPI_CS_POL_LOW           ((uint32_t) MCSPI_CH0CONF_EPOL_ACTIVELOW << \
                                    MCSPI_CH0CONF_EPOL_SHIFT)
/* @} */

/*
 * \name Value used to enable/disable FDAA operation of McSPI peripheral.
 * @{
 */
/**
 * \brief FDAA operation of McSPI peripheral is disabled
 */
#define MCSPI_FDAA_DISABLE           ((uint32_t)                          \
                                      MCSPI_MODULCTRL_FDAA_SHADOWREGEN << \
                                      MCSPI_MODULCTRL_FDAA_SHIFT)

/**
 * \brief FDAA operation of McSPI peripheral is enabled
 */
#define MCSPI_FDAA_ENABLE            ((uint32_t)                          \
                                      MCSPI_MODULCTRL_FDAA_NOSHADOWREG << \
                                      MCSPI_MODULCTRL_FDAA_SHIFT)
/* @} */

/*
 * \name Values used to configure the SYSCONFIG
 * @{
 */
/**
 * \brief Both OCP and Functional clock is switched off
 */
#define MCSPI_CLOCKS_OCP_OFF_FUNC_OFF ((uint32_t)                            \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_NONE << \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT)

/**
 * \brief OCP clock is maintained but Functional clock is switched off
 */
#define MCSPI_CLOCKS_OCP_ON_FUNC_OFF  ((uint32_t)                           \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_OCP << \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT)

/**
 * \brief Functional clock is maintained but OCP clock is switched off
 */
#define MCSPI_CLOCKS_OCP_OFF_FUNC_ON  ((uint32_t)                            \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_FUNC << \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT)

/**
 * \brief Both OCP and Functional clock is maintained
 */
#define MCSPI_CLOCKS_OCP_ON_FUNC_ON   ((uint32_t)                            \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_BOTH << \
                                       MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT)

/**
 * \brief Force Idle Mode is requested for MCSPI peripheral
 */
#define MCSPI_SIDLEMODE_FORCE         ((uint32_t)                         \
                                       MCSPI_SYSCONFIG_SIDLEMODE_FORCE << \
                                       MCSPI_SYSCONFIG_SIDLEMODE_SHIFT)

/**
 * \brief No Idle Mode is requested for MCSPI peripheral
 */
#define MCSPI_SIDLEMODE_NO            ((uint32_t) MCSPI_SYSCONFIG_SIDLEMODE_NO \
                                       << MCSPI_SYSCONFIG_SIDLEMODE_SHIFT)

/**
 * \brief Smart Idle Mode is requested for MCSPI peripheral
 */
#define MCSPI_SIDLEMODE_SMART_IDLE    ((uint32_t)                         \
                                       MCSPI_SYSCONFIG_SIDLEMODE_SMART << \
                                       MCSPI_SYSCONFIG_SIDLEMODE_SHIFT)

/*TI_INSPECTED 67 X : MISRAC_2012_D.4.5
 * "Reason - LDRA tool issue : Not able to understand unique Identifier with
 *  "-" " */
/**
 * \brief Wake-up feature control is enabled
 */
#define MCSPI_WAKEUP_ENABLE           ((uint32_t) MCSPI_SYSCONFIG_ENAWAKEUP_ON \
                                       << MCSPI_SYSCONFIG_ENAWAKEUP_SHIFT)

/**
 * \brief Wake-up feature control is disabled
 */
#define MCSPI_WAKEUP_DISABLE          ((uint32_t)                            \
                                       MCSPI_SYSCONFIG_ENAWAKEUP_NOWAKEUP << \
                                       MCSPI_SYSCONFIG_ENAWAKEUP_SHIFT)

/**
 * \brief Auromatic OCP clock gating is configured for MCSPI peripheral
 */
#define MCSPI_AUTOIDLE_ON             ((uint32_t) MCSPI_SYSCONFIG_AUTOIDLE_ON \
                                       << MCSPI_SYSCONFIG_AUTOIDLE_SHIFT)

/**
 * \brief OCP clock is configured as free running state for MCSPI peripheral
 */
#define MCSPI_AUTOIDLE_OFF            ((uint32_t) MCSPI_SYSCONFIG_AUTOIDLE_OFF \
                                       << MCSPI_SYSCONFIG_AUTOIDLE_SHIFT)
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief     Configures the clock.
 *
 * \details   This API will configure the clkD and extClk fields to generate
 *            required spi clock depending on the type of granularity. It will
 *            also set the phase and polarity of spiClk by the clkMode field.
 *
 * \param  baseAddr       Memory Address of the McSPI instance used.
 * \param  spiInClk       Clock frequency given to the McSPI module.
 * \param  spiOutClk      Clock frequency on the McSPI bus.
 * \param  chNum          Channel number of the McSPI instance used.
 * \param  clkMode        Clock mode used.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 *         'clkMode' can take the following values.\n
 *         MCSPI_CLK_MODE_n - McSPI clock mode n.\n
 *
 *         For clkMode 0 <= n <= 3.\n
 *
 * \return none.
 *
 * \note:  1) clkMode depends on phase and polarity of McSPI clock.\n
 *         2) To pass the desired value for clkMode please refer the
 *            McSPI_CH(i)CONF register.\n
 *         3) Please understand the polarity and phase of the slave device
 *            connected and accordingly set the clkMode.\n
 *         4) McSPIClkConfig does not have any significance in slave mode
 *            because the clock signal required for communication is generated
 *            by the master device.
 **/
extern void McSPIClkConfig(uint32_t baseAddr,
                           uint32_t spiInClk,
                           uint32_t spiOutClk,
                           uint32_t chNum,
                           uint32_t clkMode);
/**
 * \brief     Configure the word length.
 *
 * \brief  This API will configure the length of McSPI word used for
 *         communication.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  wordLength     Length of a data word used for McSPI communication.
 * \param  chNum          Channel number of the McSPI instance used.\n
 *
 *         'wordLength' can take the following values.\n
 *          MCSPI_WORD_LENGTH(n)  - McSPI word length is n bits int32_t.\n
 *
 *          For wordLength 4 <= n <= 32.\n
 *
 *          'chNum' can take the following values.\n
 *          MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *          For chNum n can vary from 0-3.\n
 *
 * \return none.
 *
 * \note:  wordLength can vary from 4-32 bits length. To program the
 *         required value of wordLength please refer the MCSPI_CH(i)CONF
 *         register.\n
 **/
extern void McSPIWordLengthSet(uint32_t baseAddr,
                               uint32_t wordLength,
                               uint32_t chNum);

/**
 * \brief  This API will enable the chip select pin.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 *
 * \return none.
 *
 * \note:  Modification of CS polarity, SPI clock phase and polarity
 *        is not allowed when CS is enabled.
 **/
extern void McSPICSEnable(uint32_t baseAddr);

/**
 * \brief  This API will disable the chip select pin.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 *
 * \return none.
 **/
extern void McSPICSDisable(uint32_t baseAddr);

/**
 * \brief  This API will configure the chip select polarity.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  spiEnPol       Polarity of CS line.
 * \param  chNum          Channel number of the McSPI instance used.\n
 *
 *        'spiEnPol' can take the following values.\n
 *         MCSPI_CHnCONF_EPOL_ACTIVEHIGH - SPIEN pin is held high during the
 *         active state.\n
 *         MCSPI_CHnCONF_EPOL_ACTIVELOW - SPIEN pin is held low during the
 *         active state.\n
 *
 *         where n is the channel number. 0 <= n <= 4 \n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPICSPolarityConfig(uint32_t baseAddr,
                                  uint32_t spiEnPol,
                                  uint32_t chNum);

/**
 * \brief  This API will configure the chip select time control.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  csTimeControl   Chip Select time control.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'csTimeControl' can take the following values.\n
 *         MCSPI_CH0CONF_TCS0_ZEROCYCLEDLY\n
 *         MCSPI_CH0CONF_TCS0_ONECYCLEDLY\n
 *         MCSPI_CH0CONF_TCS0_TWOCYCLEDLY\n
 *         MCSPI_CH0CONF_TCS0_THREECYCLEDLY\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPICSTimeControlSet(uint32_t baseAddr,
                                  uint32_t csTimeControl,
                                  uint32_t chNum);

/**
 * \brief  This API will activate the chip select line.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPICSAssert(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will deactivate the chip select line.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPICSDeAssert(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will enable start bit.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPIStartBitEnable(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will configure the polarity of start bit.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  startBitPol     Polarity of start bit.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'startBitPol' can take the following values.\n
 *         MCSPI_START_BIT_POL_LOW  - Polarity of start bit is held low
 *                                    during transmission.\n
 *         MCSPI_START_BIT_POL_HIGH - Polarity of start bit is held high
 *                                    during transmission.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPIStartBitPolarityConfig(uint32_t baseAddr,
                                        uint32_t startBitPol,
                                        uint32_t chNum);

/**
 * \brief  This API will disable the start bit mode of McSPI peripheral.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPIStartBitDisable(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will enable the McSPI controller in master mode.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 *
 * \return none.
 **/
extern void McSPIMasterModeEnable(uint32_t baseAddr);

/**
 * \brief  This call will enable the McSPI controller in Slave mode.\n
 *
 * \param  baseAddr      baseAddr of the McSPI instance used.\n
 *
 * \return none.
 **/
extern void McSPISlaveModeEnable(uint32_t baseAddr);

/**
 * \brief  This API will enable the McSPI controller in master mode and
 *         configure other parameters required for master mode.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  channelMode     Single/Multi channel.
 * \param  trMode          Transmit/Receive mode used in master
 *                         configuration.
 * \param  pinMode         Interface mode and pin assignment.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'channelMode' can take the following values.\n
 *         MCSPI_MODULCTRL_SINGLE_SINGLE - Single channel mode is used.\n
 *         MCSPI_MODULCTRL_SINGLE_MULTI  - Multi channel mode is used.\n
 *
 *         'trMode' can take the following values.\n
 *         MCSPI_TX_RX_MODE   - Enable McSPI in TX and RX modes.\n
 *         MCSPI_RX_ONLY_MODE - Enable McSPI only in RX mode.\n
 *         MCSPI_TX_ONLY_MODE - Enable McSPI only in TX mode.\n
 *
 *         'pinMode' can take the following values.\n
 *         MCSPI_DATA_LINE_COMM_MODE_n - Mode n configuration for SPIDAT[1:0].\n
 *
 *         For pinMode 0 <= n <= 7.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return 'retVal' which states if the combination of trMode and pinMode chosen
 *          by the user is supported for communication on SPIDAT[1:0] pins.\n
 *          TRUE  - Communication supported by SPIDAT[1:0].\n
 *          FALSE - Communication not supported by SPIDAT[1:0].\n
 *
 * \note   Please refer the description about IS,DPE1,DPE0 and TRM bits for
 *         proper configuration of SPIDAT[1:0].\n
 **/
extern uint32_t McSPIMasterModeConfig(uint32_t baseAddr,
                                      uint32_t channelMode,
                                      uint32_t trMode,
                                      uint32_t pinMode,
                                      uint32_t chNum);

/**
 * \brief  This API will enable the channel of McSPI controller.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *      'chNum' can take the following values.\n
 *      MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *      For chNum 0 <= n <= 3.\n
 *
 * \return none.
 *
 * \note:  Please ensure to enable only channel 0 in slave mode.\n
 *         Channels other than 0 are not valid in slave mode.
 **/
extern void McSPIChannelEnable(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will disable the channel of McSPI controller.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPIChannelDisable(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will reset the McSPI peripheral.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 *
 * \return none.
 **/
extern void McSPIReset(uint32_t baseAddr);

/**
 * \brief  This API will enable the McSPI turbo mode of operation.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 *
 * \note
 **/
extern void McSPITurboModeEnable(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will disable the McSPI turbo mode of operation.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return none.
 **/
extern void McSPITurboModeDisable(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will enable/disable the Tx FIFOs of McSPI peripheral.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  txFifo          FIFO used for transmit mode.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'txFifo' can take the following values.\n
 *         MCSPI_TX_FIFO_ENABLE  - Enables the transmitter FIFO of McSPI.\n
 *         MCSPI_TX_FIFO_DISABLE - Disables the transmitter FIFO of McSPI.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return none.
 *
 * \note:  Enabling FIFO is restricted to only 1 channel.
 **/
extern void McSPITxFIFOConfig(uint32_t baseAddr,
                              uint32_t txFifo,
                              uint32_t chNum);

/**
 * \brief  This API will enable/disable the Rx FIFOs of McSPI peripheral.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  rxFifo          FIFO used for receive mode.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'rxFifo' can take the following values.\n
 *         MCSPI_RX_FIFO_ENABLE - Enables the receiver FIFO of McSPI.\n
 *         MCSPI_RX_FIFO_DISABLE - Disables the receiver FIFO of McSPI.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return none.
 *
 * \note:  Enabling FIFO is restricted to only 1 channel.
 **/
extern void McSPIRxFIFOConfig(uint32_t baseAddr,
                              uint32_t rxFifo,
                              uint32_t chNum);

/**
 * \brief  This API will set the transfer levels used by FIFO depending on
 *         the various McSPI transmit/receive modes.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  afl             Buffer almost full value.
 * \param  ael             Buffer almost empty value.
 * \param  trMode          Transmit/Receive modes used.\n
 *
 *         'trMode' can take the following values.\n
 *         MCSPI_TX_RX_MODE   - Enable McSPI in TX and RX modes.\n
 *         MCSPI_RX_ONLY_MODE - Enable McSPI only in RX mode.\n
 *         MCSPI_TX_ONLY_MODE - Enable McSPI only in TX mode.\n
 *
 * \return none.
 *
 * \note   Values for afl and ael will have varying values depending on
 *         trMode. If trMode is MCSPI_TX_RX_MODE then afl and ael can take
 *         values ranging from 0-19. If trMode is MCSPI_RX_ONLY_MODE/
 *         MCSPI_TX_ONLY_MODE then afl and ael can take values from 0-39.\n
 *
 *         While configuring mode of operation using trMode please ensure the
 *         same value of trMode is used while using API's McSPIMasterModeConfig
 *         and McSPISlaveModeConfig. Mismatch while using trMode for different
 *         APIs can result in unpredictable behaviour.\n
 *
 *         For 'ael' and 'afl' please send level values for both of the fields
 *         and do not send the value which has to be written into the register
 *         for the corresponding level value.
 *         For e.g. if 'ael' or 'afl' has to be 1 byte, then pass the parameter
 *         'ael' or 'afl' as 1 and not 0 because the value which has to be
 *         written into register is manipulated inside the driver itself.\n
 **/
extern void McSPIFIFOTrigLvlSet(uint32_t baseAddr,
                                uint8_t  afl,
                                uint8_t  ael,
                                uint32_t trMode);

/**
 * \brief  This API will set the McSPI word counter value.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  wCnt           Word count.
 *
 * \return none.
 **/
extern void McSPIWordCountSet(uint32_t baseAddr, uint16_t wCnt);

/**
 * \brief  This API will enable the DMA read/write events of McSPI.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  dmaFlags        Variable used to enable DMA mode for
 *                         Rx/Tx events.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'dmaFlags' can take the following values.\n
 *         MCSPI_DMA_RX_EVENT  - To enable DMA mode for Rx events.\n
 *         MCSPI_DMA_TX_EVENT  - To enable DMA mode for Tx events.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return none.
 **/
extern void McSPIDMAEnable(uint32_t baseAddr,
                           uint32_t dmaFlags,
                           uint32_t chNum);

/**
 * \brief  This API will disable the DMA read/write events of McSPI.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  dmaFlags        Variable used to disable DMA mode for
 *                         Rx/Tx events.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'dmaFlags' can take the following values.\n
 *         MCSPI_DMA_RX_EVENT - To disable DMA mode for Rx events.\n
 *         MCSPI_DMA_TX_EVENT - To disable DMA mode for Tx events.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return none.
 **/
extern void McSPIDMADisable(uint32_t baseAddr,
                            uint32_t dmaFlags,
                            uint32_t chNum);

/**
 * \brief  This API will enable the McSPI Interrupts.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  intFlags        Represents the various interrupts to be enabled.
 *
 * \return none.
 *
 * \note   Please ensure the proper channel number is passed while using the
 *         macros.
 **/
extern void McSPIIntEnable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief  This API will disable the McSPI Interrupts.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  intFlags        Represents the various interrupts to be disabled.
 *
 *         'intFlags' can take the following values.\n
 *         MCSPI_INT_TX_EMPTY(chan) - Transmitter register empty interrupt.\n
 *         MCSPI_INT_TX_UNDERFLOW(chan) - Transmitter register underflow
 *                                        interrupt.\n
 *         MCSPI_INT_RX_FULL(chan) - Receiver register full interrupt.\n
 *         MCSPI_INT_RX0_OVERFLOW - Receiver register 0 overflow interrupt.\n
 *         MCSPI_INT_EOWKE - End of word count interrupt.\n
 *
 *         'chan' stands for channel number.
 *         Please specify the proper channel number while passing the macros.
 *         0 <= chan <= 3 \n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return none.
 *
 * \note   Please ensure the proper channel number is passed while using the
 *         macros.
 **/
extern void McSPIIntDisable(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief  This API will set initial delay for first transfer from McSPI
 *         peripheral.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  initDelay       Delay used for first transfer.\n
 *
 *         'initDelay' can take the following values.\n
 *         MCSPI_INITDLY_0  - No delay for first transfer.\n
 *         MCSPI_INITDLY_4  - Delay of 4 SPI Clock.\n
 *         MCSPI_INITDLY_8  - Delay of 8 SPI Clock.\n
 *         MCSPI_INITDLY_16 - Delay of 16 SPI Clock.\n
 *         MCSPI_INITDLY_32 - Delay of 32 SPI Clock.\n
 *
 * \return none.
 *
 * \note:  Please note that this option is available only in single master mode.
 **/
extern void McSPIInitDelayConfig(uint32_t baseAddr, uint32_t initDelay);

/**
 * \brief  This API will put the data on to the McSPI Channel
 *         transmit register.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  txData          32 bit data sent by the user which is put on
 *                         to the MCSPI_TX register.
 * \param  chNum           Channel number of the McSPI instance used.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return none.
 **/
extern void McSPITransmitData(uint32_t baseAddr,
                              uint32_t txData,
                              uint32_t chNum);

/**
 * \brief  This API will return the data present in the MCSPI_RX register.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel number of the McSPI instance used.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum n can range from 0-3.\n
 *
 * \return This API will return the data received in the MCSPI_RX register.
 **/
extern uint32_t McSPIReceiveData(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will return the status of the McSPI peripheral interrupts.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 *
 * \return This API will return the status of the McSPI peripheral interrupts.
 *         User can use the following macros to check the status \n
 *         MCSPI_INT_TX_EMPTY(chan) - Transmitter register empty for channel n
 *         MCSPI_INT_TX_UNDERFLOW(chan) - Transmitter register underflow for
 *                                        channel n \n
 *         MCSPI_INT_RX_FULL(chan) - Receiver register full for channel n \n
 *         MCSPI_INT_RX0_OVERFLOW - Receiver register overflow for channel 0 \n
 *         MCSPI_INT_EOWKE - End of word count interrupt \n
 *         where 0 <= chan <= 3
 *
 **/
extern uint32_t McSPIIntStatusGet(uint32_t baseAddr);

/**
 * \brief  This API will clear the status of McSPI Interrupts.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  intFlags        Represents the various interrupts to be cleared.
 *
 * \return none.
 *
 * \note   Please ensure the proper channel number is used while passing the
 *         macros passed.\n
 **/
extern void McSPIIntStatusClear(uint32_t baseAddr, uint32_t intFlags);

/**
 * \brief  This API will return the status of the McSPI channel currently in
 *         use.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum           Channel used for communication.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 * \return This API will return the status of the McSPI channel status
 *         register.
 *         User can use the following macros to check the status \n
 *         MCSPI_CH_STAT_RXS_FULL - Receiver register is full \n
 *         MCSPI_CH_STAT_TXS_EMPTY - Transmitter register is full \n
 *         MCSPI_CH_STAT_EOT - End of transfer status \n
 *         MCSPI_CH_TXFFE - FIFO transmit buffer empty status \n
 *         MCSPI_CH_TXFFF - FIFO transmit buffer full status \n
 *         MCSPI_CH_RXFFE - FIFO receive buffer empty status \n
 *         MCSPI_CH_RXFFF - FIFO receive buffer full status \n
 **/
extern uint32_t McSPIChannelStatusGet(uint32_t baseAddr, uint32_t chNum);

/**
 * \brief  This API will enable/disable multiple word OCP access for McSPI
 *         peripheral.
 *
 * \param  baseAddr        Memory Address of the McSPI instance used.
 * \param  moa             Used to enable/disable MOA in McSPI peripheral.\n
 *
 *         'moa' can take the following values.\n
 *         MCSPI_MOA_ENABLE  - Enable MOA.\n
 *         MCSPI_MOA_DISABLE - Disable MOA.\n
 *
 * \return none.
 **/
extern void McSPIMultipleWordAccessConfig(uint32_t baseAddr, uint32_t moa);

/**
 * \brief  This API will enable/disable the FIFO DMA address 256-bit aligned
 *         feature of McSPI peripheral.
 *
 * \param  baseAddr       Memory Address of the McSPI instance used.
 * \param  fdaa           Used to enable/disable FDAA in McSPI peripheral.\n
 *
 *        'fdaa' can take the following values.\n
 *        MCSPI_FDAA_ENABLE  - Enable FDAA.\n
 *        MCSPI_FDAA_DISABLE - Disable FDAA.\n
 *
 * \return none.
 **/
extern void McSPIFIFODatManagementConfig(uint32_t baseAddr, uint32_t fdaa);

/**
 * \brief  MCSPISysConfigSetup() description for void
 *         MCSPISysConfigSetup(). This call will setup the SYSCONFIG register
 *         of the McSPI peripheral.
 *
 * \param  baseAddr       Memory Address of the McSPI instance used.
 * \param  clockActivity  Clocks activity maintained during wake-up mode period.
 * \param  sidleMode      Power management configuration.
 * \param  wakeUp         Wake-up feature control.\n
 * \param  autoIdle       Internal OCP Clock gating.
 *
 *         'clockActivity' can take the following values.\n
 *         MCSPI_CLOCKS_OCP_OFF_FUNC_OFF - OCP and functional clocks may be
 *                                         switched off.\n
 *         MCSPI_CLOCKS_OCP_ON_FUNC_OFF  - OCP clock is maintained. Functional
 *                                         clock may be switched off.\n
 *         MCSPI_CLOCKS_OCP_OFF_FUNC_ON  - Functional clock is maintained. OCP
 *                                         clock may be switched off.\n
 *         MCSPI_CLOCKS_OCP_ON_FUNC_ON   - OCP and functional clocks are
 *                                         maintained.\n
 *
 *         'sidleMode' can take the following values.\n
 *         MCSPI_SIDLEMODE_FORCE
 *         MCSPI_SIDLEMODE_NO
 *         MCSPI_SIDLEMODE_SMART_IDLE
 *
 *         'wakeUp' can take the following values.\n
 *         MCSPI_WAKEUP_ENABLE  - Wake-up capability is enabled.\n
 *         MCSPI_WAKEUP_DISABLE - Wake-up capability is disabled.\n
 *
 *         'autoIdle' can take the following values.\n
 *         MCSPI_AUTOIDLE_ON  - Automatic OCP clock gating strategy applied.\n
 *         MCSPI_AUTOIDLE_OFF - OCP clock free-running.\n
 *
 * \return none.
 **/
extern void MCSPISysConfigSetup(uint32_t baseAddr,
                                uint32_t clockActivity,
                                uint32_t sidleMode,
                                uint32_t wakeUp,
                                uint32_t autoIdle);

/**
 * \brief  MCSPIPinDirSet() description for
 *         void MCSPIPinDirSet(). This call will configure the Pin Direction
 *         and the transfer mode depending on the user sent values.
 *
 * \param baseAddr        Memory Address of the McSPI instance used.
 * \param  trMode         Transmit/Receive mode used in master
 *                        configuration.
 * \param  pinMode        Interface mode and pin assignment.
 * \param  chNum          Channel number of the McSPI instance used.\n
 *
 *         'trMode' can take the following values.\n
 *         MCSPI_TX_RX_MODE   - Enable McSPI in TX and RX modes.\n
 *         MCSPI_RX_ONLY_MODE - Enable McSPI only in RX mode.\n
 *         MCSPI_TX_ONLY_MODE - Enable McSPI only in TX mode.\n
 *
 *         'pinMode' can take the following values.\n
 *         MCSPI_DATA_LINE_COMM_MODE_n - Mode n configuration for SPIDAT[1:0].\n
 *
 *         For pinMode 0 <= n <= 7.\n
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 * \return 'retVal' which states if the combination of trMode and pinMode chosen
 *         by the user is supported for communication on SPIDAT[1:0] pins.\n
 *         0  - Communication supported by SPIDAT[1:0].\n
 *         1  - Communication not supported by SPIDAT[1:0].\n
 *
 * \note   Please refer the description about IS,DPE1,DPE0 and TRM bits for
 *         proper configuration of SPIDAT[1:0].\n
 **/
extern uint32_t MCSPIPinDirSet(uint32_t baseAddr,
                               uint32_t trMode,
                               uint32_t pinMode,
                               uint32_t chNum);

/**
 * \brief  MCSPISingleChModeEnable() description for
 *         void MCSPISingleChModeEnable(). This call will configure McSPI to
 *         work in single channel mode.
 * \param  baseAddr        Base address of the McSPI instance used.
 *
 *
 **/
extern void MCSPISingleChModeEnable(uint32_t baseAddr);

/**
 * \brief  MCSPIMultiChModeEnable() description for
 *         void MCSPIMultiChModeEnable(). This call will configure McSPI to
 *         work in Multi channel mode.
 * \param  baseAddr        Base address of the McSPI instance used.
 *
 *
 **/
extern void MCSPIMultiChModeEnable(uint32_t baseAddr);

/**
 * \brief McSPISetSlaveChipSel() description for
 *     void McSPISetSlaveChipSel(). This call will activate the
 *     user specified chip select line.
 *
 * \param baseAddr        Memory Address of the McSPI instance used.
 * \param  chNum          Channel number of the McSPI instance used.
 * \param  slaveChipSel   slave select signal detection.
 *
 *         'chNum' can take the following values.\n
 *         MCSPI_CHANNEL_n - Channel n is used for communication.\n
 *
 *         For chNum 0 <= n <= 3.\n
 *
 *         'slaveChipSel' can take the following values.\n
 *         MCSPI_SPIEN_0 - Detection enabled only on SPIEN[0].\n
 *         MCSPI_SPIEN_1 - Detection enabled only on SPIEN[1].\n
 *         MCSPI_SPIEN_2 - Detection enabled only on SPIEN[2].\n
 *         MCSPI_SPIEN_3 - Detection enabled only on SPIEN[3].\n
 *
 * \return none.
 **/
extern void McSPISetSlaveChipSel(uint32_t baseAddr,
                                 uint32_t chNum,
                                 uint32_t slaveChipSel);

#ifdef __cplusplus
}
#endif
#endif  /* MCSPI_H_ */
 /** @} */
/********************************* End of file ******************************/
