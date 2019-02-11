/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - www.ti.com
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
 *  \defgroup CSL_QSPI QSPI
 *
 *  @{
 */
 /**
 * \file       qspi.h
 *
 * \brief      This file contains the function prototypes for the device
 *             abstraction layer for QSPI. It also contains some
 *             related macro definitions and enum definitions.
 *
 *             The QSPI module support single, dual and quad read mode
 *             in interrupt and polling mode using QSPI data registers
 *             and also support memory mapped mode.
 *
 * \details    Programming sequence of QSPI is as follows:
 *             -# Enable the functional clock for required QSPI instance.
 *             -# Perform the pin multiplexing for required QSPI instance.
 *             -# Set the QSPI idle mode using the API #QSPIconfigIdleMode.
 *             -# Set Device Control register - clock polarity, phase, CS polarity and data
*                 delay depending on silicon Revision #QSPIsetDeviceControl
 *             -# sets Memory Map Setup register #QSPISetMemoryMapSetup.
 *             -# selects the memory mapped mode in SPI switch register and
 *                configures mapped address for different chip select in
 *                control module using #QSPISetMAddrSpace
 *             -# Read data from QSPI data registers using the API
 *                #QSPIreadData.
 *             -# Write data into QSPI data registers by using the API
 *                #QSPIwriteData.
 *             -# returns the status of the interrupts #QSPIintStatus
 *
 **/

#ifndef QSPI_H_
#define QSPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/src/ip/qspi/V1/hw_qspi.h>

/* ========================================================================== */
/*                                 Macros & Typedefs                          */
/* ========================================================================== */

/* ========================================================================== */
/*                         Deprecated Macros                                  */
/* ========================================================================== */
/* Instead of using these Macros, we can use HW Macros. So these Macros are
 * Deprecated and also Undefined the Macro QSPI_H_BACKWARD_COMPATIBLE_CHG which
 * fixes MISRAC Issue: 67 X: MISRAC_2012_D.4.5: Identifier is typographically
 * ambiguous*/
#ifdef QSPI_H_BACKWARD_COMPATIBLE_CHG
 /* \name Values that can be used by the application for configuration via APIs
*  @{
*/
#define QSPI__SPI_STATUS_REG__BUSY__BUSY    (QSPI_SPI_STATUS_REG_BUSY_BUSY)
#define QSPI__SPI_STATUS_REG__BUSY__IDLE    (QSPI_SPI_STATUS_REG_BUSY_IDLE)

#define QSPI__SPI_CLOCK_CNTRL_REG__CLKEN__DCLOCK_OFF \
                                     (QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF)
#define QSPI__SPI_CLOCK_CNTRL_REG__CLKEN__DCLOCK_ON \
                                      (QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON)

#define QSPI__SPI_DC_REG__CKP__DATA_ACTIVE     (QSPI_SPI_DC_REG_CKP_DATA_ACTIVE)
#define QSPI__SPI_DC_REG__CKP__DATA_INACTIVE   \
                                             (QSPI_SPI_DC_REG_CKP_DATA_INACTIVE)

#define QSPI__SPI_DC_REG__CSP__ACTIVE_LOW      (QSPI_SPI_DC_REG_CSP_ACTIVE_LOW)
#define QSPI__SPI_DC_REG__CSP__ACTIVE_HIGH     (QSPI_SPI_DC_REG_CSP_ACTIVE_HIGH)

#define QSPI__SPI_DC_REG__CKPH__CKP_1_SHIFT_OUT_FALLING_EDGE \
                            (QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE)
#define QSPI__SPI_DC_REG__CKPH__CKP_1_SHIFT_OUT_RISING_EDGE \
                            (QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_RISING_EDGE)
#define QSPI__SPI_DC_REG__CKPH__CKP_0_SHIFT_OUT_FALLING_EDGE \
                            (QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_FALLING_EDGE)
#define QSPI__SPI_DC_REG__CKPH__CKP_0_SHIFT_OUT_RISING_EDGE \
                            (QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_RISING_EDGE)

#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_0 \
                                        (QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_0)
#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_1 \
                                        (QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_1)
#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_2 \
                                        (QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_2)
#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_3 \
                                        (QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_3)

#define QSPI__SPI_CMD_REG__CSNUM__CS_0      (QSPI_SPI_CMD_REG_CSNUM_CS_0)
#define QSPI__SPI_CMD_REG__CSNUM__CS_1      (QSPI_SPI_CMD_REG_CSNUM_CS_1)
#define QSPI__SPI_CMD_REG__CSNUM__CS_2      (QSPI_SPI_CMD_REG_CSNUM_CS_2)
#define QSPI__SPI_CMD_REG__CSNUM__CS_3      (QSPI_SPI_CMD_REG_CSNUM_CS_3)

#define QSPI__SPI_CMD_REG__FIRQ__FRAME_COUNT_IRQ_DISABLE \
                                (QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE)
#define QSPI__SPI_CMD_REG__FIRQ__FRAME_COUNT_IRQ_ENABLE \
                                (QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_ENABLE)

#define QSPI__SPI_CMD_REG__WIRQ__WORD_COUNT_IRQ_DISABLE \
                                (QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE)
#define QSPI__SPI_CMD_REG__WIRQ__WORD_COUNT_IRQ_ENABLE \
                                 (QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_ENABLE)

#define QSPI__SPI_SETUP0_REG__NUM_A_BYTES__THREE_BYTES   \
                                   (QSPI_SPI_SETUP0_REG_NUM_A_BYTES_THREE_BYTES)
#define QSPI__SPI_SETUP0_REG__NUM_A_BYTES__TWO_BYTES     \
                                   (QSPI_SPI_SETUP0_REG_NUM_A_BYTES_TWO_BYTES)
#define QSPI__SPI_SETUP0_REG__NUM_A_BYTES__ONE_BYTES     \
                                   (QSPI_SPI_SETUP0_REG_NUM_A_BYTES_ONE_BYTE)

#define QSPI__SPI_SETUP0_REG__NUM_D_BYTES__USE_8_BITS    \
                                   (QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS)
#define QSPI__SPI_SETUP0_REG__NUM_D_BYTES__USE_16_BITS   \
                                   (QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS)
#define QSPI__SPI_SETUP0_REG__NUM_D_BYTES__USE_24_BITS   \
                                   (QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS)
/* @} */
#endif

/* \brief Values of QSPI flash clock frequency is combination of input clock
 *  select value and Clock divider value (QSPI_CLKSWITCH + QSPI_CLKDIVIDER)*/
/**
 * \brief Mask value to get input clock select value
 *      0 - 128 MHz input clock
 *      1 - 192 MHz input clock
 *      2 - 76.8 MHz input clock
 */
#define QSPI_CLKSWITCH_MASK  (0xF0000U)

/**
 * \brief Shift value to get input clock select value
 */
#define QSPI_CLKSWITCH_SHIFT (16U)

/**
 * \brief Mask value to get input clock divider value to be set in QSPI IP
 *      internal divider
 */
#define QSPI_CLKDIVIDER_MASK  (0x0FFFFU)

/**
 * \brief Shift value to get input clock divider value
 */
#define QSPI_CLKDIVIDER_SHIFT (0U)

/* ========================================================================== */
/*                             Enum Definitions                               */
/* ========================================================================== */
/**
 * \brief Enumerates the values used to represent QSPI device type
 */
typedef enum {
    DEVICE_TYPE_QSPI4 = 0x01U,
    /**< 4 Bit Quad Fast read at 48 MHz.This is used for flash auto detect */
    DEVICE_TYPE_QSPI1 = 0x02U,
    /**< 1 Bit Normal read at 12 MHz. This is used for flash auto detect */
    DEVICE_TYPE_MICRON_QSPI4       = 0x11U,
    /**< 4 bit (Quad) read from Micron Flash*/
    DEVICE_TYPE_MICRON_QSPI1       = 0x12U,
    /**< 1 bit read from Micron Flash*/
    DEVICE_TYPE_MICRON_1GBIT_QSPI4 = 0x13U,
    /**< 4 bit read from 1 GigaBit Micron Flash*/
    DEVICE_TYPE_MICRON_1GBIT_QSPI1 = 0x14U,
    /**< 1 bit read from 1 GigaBit Micron Flash*/
    DEVICE_TYPE_WINBOND_QSPI4      = 0x21U,
    /**< 4 bit (Quad) read from Winbond Flash*/
    DEVICE_TYPE_WINBOND_QSPI1      = 0x22U,
    /**< 1 bit read from Winbond Flash*/
    DEVICE_TYPE_ISSI_QSPI4         = 0x31U,
    /**< 4 bit (Quad) read from ISSI Flash*/
    DEVICE_TYPE_ISSI_QSPI1         = 0x32U,
    /**< 1 bit read from ISSI Flash*/
    DEVICE_TYPE_SPANSION_QSPI4     = 0x41U,
    /**< 4 bit (Quad) read from Spansion Flash*/
    DEVICE_TYPE_SPANSION_QSPI1     = 0x42U,
    /**< 1 bit read from Spansion Flash*/
    DEVICE_TYPE_CUSTOM             = 0xF0U
    /**< Custom Flash Mode*/
} qspi_DeviceType_e;

/**
 * \brief Enumerates the values used to represent QSPI flash clock frequency
 */
typedef enum {
    QSPI_SCLK_FREQ_64MHz   = 0x00001U,
    /**< Selects QSPI SCLK Freq as 64 MHz clock*/
    QSPI_SCLK_FREQ_32MHz   = 0x00003U,
    /**< Selects QSPI SCLK Freq as 32 MHz clock*/
    QSPI_SCLK_FREQ_16MHz   = 0x00007U,
    /**< Selects QSPI SCLK Freq as 16 MHz clock*/
    QSPI_SCLK_FREQ_96MHz   = 0x10001U,
    /**< Selects QSPI SCLK Freq as 96 MHz clock*/
    QSPI_SCLK_FREQ_48MHz   = 0x10003U,
    /**< Selects QSPI SCLK Freq as 48 MHz clock*/
    QSPI_SCLK_FREQ_24MHz   = 0x10007U,
    /**< Selects QSPI SCLK Freq as 24 MHz clock*/
    QSPI_SCLK_FREQ_12MHz   = 0x1000FU,
    /**< Selects QSPI SCLK Freq as 12 MHz clock*/
    QSPI_SCLK_FREQ_76_8MHz = 0x20000U
    /**< Selects QSPI SCLK Freq as 76.8 MHz clock*/
} qspi_ClockFreq_e;

/**
 * \brief Enumerates the values used to represent Chip select value
 */
typedef enum {
    QSPI_MMR = 0,
    /**< Configuration port registers*/
    QSPI_CS0 = 1,
    /**< select chip select 0*/
    QSPI_CS1 = 2,
    /**< select chip select 1*/
    QSPI_CS2 = 3,
    /**< select chip select 2*/
    QSPI_CS3 = 4
    /**< select chip select 3*/
} qspi_ChipSelect_e;

/**
 * \brief Enumerates the values used to represent QSPI commands
 */
typedef enum {
    QSPI_CMD_READ_24       = 0x03U,
    /**< Read command for 3 or 4 Byte Address*/
    QSPI_CMD_READ          = 0x13U,
    /**< Normal Read command for 4 Byte Address*/
    QSPI_CMD_RDSR          = 0x05U,
    /**< Command to Read Status Register-1*/
    QSPI_CMD_RDSR2         = 0x07U,
    /**< Command to Read Status Register-2*/
    QSPI_CMD_RDCR          = 0x35U,
    /**< Command to Read Configuration Register-1*/
    QSPI_CMD_WREN          = 0x06U,
    /**< Write enable command*/
    QSPI_CMD_WRREG         = 0x01U,
    /**< Write register command*/
    QSPI_CMD_WRITE_24      = 0x02U,
    /**< Write command for 3 or 4 Byte Address*/
    QSPI_CMD_WRITE         = 0x12U,
    /**< Normal write command for 4 Byte Address*/
    QSPI_CMD_FAST_READ_24  = 0x0BU,
    /**< Fast read command for 3 or 4 Byte Address*/
    QSPI_CMD_FAST_READ     = 0x0CU,
    /**< Fast read command for 4 Byte Address*/
    QSPI_CMD_FAST_DREAD_24 = 0x3BU,
    /**< Fast dual read command for 3 or 4 Byte Address*/
    QSPI_CMD_FAST_DREAD    = 0x3CU,
    /**< Fast dual read command for 4 Byte Address*/
    QSPI_CMD_FAST_QREAD_24 = 0x6BU,
    /**< Fast quad read command for 3 or 4 Byte Address*/
    QSPI_CMD_FAST_QREAD    = 0x6CU,
    /**< Fast quad read command for 4 Byte Address*/
    QSPI_CMD_MFGID         = 0x90U,
    /**< Read manufacturer Id command*/
    QSPI_CMD_BLKERASE_24   = 0xD8U,
    /**< Block Erase(64 kB or 256 kB) command for 3 or 4 Byte Address*/
    QSPI_CMD_BLKERASE      = 0xDCU,
    /**< Block Erase(64 kB or 256 kB) command for 4 Byte Address*/
    QSPI_CMD_PAGEERASE     = 0x21U,
    /**< 4 kB Sector Erase command for 4 Byte Address*/
    QSPI_CMD_PAGEERASE_24  = 0x20U,
    /**< 4 kB Sector Erase command for 3 or 4 Byte Address*/
    QSPI_CMD_FULLERASE     = 0x60U,
    /**< Full Flash Erase command*/

    /* Spansion flash commands */
    QSPI_CMD_SPANSION_RESET     = 0xF0U,
    /**< Spansion Flash: Software Reset command*/

    /* Micron flash commands */
    QSPI_CMD_MICRON_READ_24     = 0x03U,
    /**< Micron Flash: Read command for 3 or 4 Byte Address*/
    QSPI_CMD_MICRON_RDSR        = 0x05U,
    /**< Micron Flash: Command to Read Status Register-1*/
    QSPI_CMD_MICRON_QREAD_24    = 0x6BU,
    /**< Micron Flash: Fast quad read command for 3 or 4 Byte Address*/
    QSPI_CMD_MICRON_WRITE_24    = 0x02U,
    /**< Micron Flash: Write command for 4 Byte Address*/
    QSPI_CMD_MICRON_MFGID       = 0x9EU,
    /**< Micron Flash: Read manufacturer Id command*/
    QSPI_CMD_MICRON_WREN        = 0x06U,
    /**< Micron Flash: Write enable command*/
    QSPI_CMD_MICRON_BLKERASE_24 = 0xD8U,
    /**< Micron Flash: Block Erase(64 kB or 256 kB) command for 3 or 4 Byte
     *   Address*/
    QSPI_CMD_MICRON_FULLERASE   = 0xC7U,
    /**< Micron Flash: Full Flash Erase command*/
    QSPI_CMD_MICRON_RDNVCR      = 0xB5U,
    /**< Micron Flash: Command to Read Non Volatile Configuration Register*/
    QSPI_CMD_MICRON_WRNVCR      = 0xB1U,
    /**< Micron Flash: Command to Write Non Volatile Configuration Register*/
    QSPI_CMD_MICRON_RDEVCR      = 0x65U,
    /**< Micron Flash: Command to Read Enhanced Volatile Configuration Register
     */
    QSPI_CMD_MICRON_WREVCR      = 0x61U,
    /**< Micron Flash: Command to Write Enhanced Volatile Configuration Register
     */
    /* Commands specific to micron 1G bit flash */
    QSPI_CMD_MICRON_1GBIT_FULLERASE   = 0xC4U,
    /**< Micron 1G Bit Flash: Full Flash Erase command*/

    /* Winbond specific commands */
    QSPI_CMD_WINBOND_RDSR2 = 0x35U,
    /**< Winbond Flash: Command to Read Status Register-2*/
    QSPI_CMD_WINBOND_WRSR2 = 0x31U,
    /**< Winbond Flash: Command to Write Status Register-2*/

    /* Reset Commands common for Micron, Winbond and ISSI Flashes */
    QSPI_CMD_RESET_ENABLE  = 0x66U,
    /**< Reset Enable command*/
    QSPI_CMD_RESET_DEVICE  = 0x99U,
    /**< Reset Memory command*/

    QSPI_CMD_JDEC_DEVICE_ID  = 0x9FU
    /**< Command to detect flash Device Id*/
} qspi_ReadCommand_e;

/**
 * \brief  This enumerates the flags for
 *         word or frame interrupt for QSPI module
 */
typedef enum qspiIntrMask
{
    QSPI_INTR_MASK_FRAME = QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK,
    /**< Interrupt mask for frame interrupt. */
    QSPI_INTR_MASK_WORD = QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK
    /**< Interrupt mask for word interrupt . */
} qspiIntrMask_t;


/**
 * \brief  Enumerates the four possible clock modes for QSPI.
 *         Each mode has different values of clock phase(CKPH)
 *         and clock polarity(CKP)
 */
typedef enum qspiClkMode
{
    QSPI_CLK_MODE_0 = (QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_FALLING_EDGE
                      << QSPI_SPI_DC_REG_CKPH0_SHIFT) |
                      (QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE <<
                       QSPI_SPI_DC_REG_CKP0_SHIFT),
    /**< Mode 0 - Clock polarity = 0, clock phase = 0*/
    QSPI_CLK_MODE_1 = (QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_RISING_EDGE
                      << QSPI_SPI_DC_REG_CKPH0_SHIFT) |
                      (QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE <<
                       QSPI_SPI_DC_REG_CKP0_SHIFT),
    /**< Mode 1 - clock polarity = 0, clock phase = 1*/
    QSPI_CLK_MODE_2 = (QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_RISING_EDGE
                      << QSPI_SPI_DC_REG_CKPH0_SHIFT) |
                      (QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE <<
                       QSPI_SPI_DC_REG_CKP0_SHIFT),
    /**< Mode 2 - clock polarity = 1, clock phase = 0*/
    QSPI_CLK_MODE_3 = (QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_FALLING_EDGE
                      << QSPI_SPI_DC_REG_CKPH0_SHIFT) |
                      (QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE <<
                       QSPI_SPI_DC_REG_CKP0_SHIFT)
    /**<Mode 3 - clock polarity = 1, clock phase = 1*/
}qspiClkMode_t;

/**
 * \brief   Enumerates the different chip selects available
 *          to QSPI. QSPI module have four chip selects to
 *          connect to four external devices.
 */
typedef enum qspiChipSelect
{
    QSPI_CHIP_SELECT_CS0 = 0x0U,
    /**< Chip select 0 */
    QSPI_CHIP_SELECT_CS1 = 0x1U,
    /**< Chip select 1 */
    QSPI_CHIP_SELECT_CS2 = 0x2U,
    /**< Chip select 2 */
    QSPI_CHIP_SELECT_CS3 = 0x3U
    /** Chip select 3 */
} qspiChipSelect_t;

/**
 * /brief  Enumerates the polarities for different chip select
 *         available. (Chip Select 0 to Chip Select 3)
 */
typedef enum qspiCsPol
{
    QSPI_CS_POL_ACTIVE_LOW = QSPI_SPI_DC_REG_CSP0_ACTIVE_LOW,
    /**< Chip select polarity active low */
    QSPI_CS_POL_ACTIVE_HIGH = QSPI_SPI_DC_REG_CSP0_ACTIVE_HIGH
    /**< Chip select polarity active high */
} qspiCsPol_t;

/**
 *  \brief   Enumerates the value of Data delay value for
 *           each chip select. Data is output on the same cycle as
 *           CS_N goes active, or 1, 2 or 3 DCLK cycles after the
 *           CS_N goes active depending on the data delay provided.
 */
typedef enum qspiDataDelay
{
    QSPI_DATA_DELAY_0 = QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_0,
    /**<Data is output on the same cycle as the CS N goes active. */
    QSPI_DATA_DELAY_1 = QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_1,
    /**<Data is output 1 DCLK cycle after the CS N goes active. */
    QSPI_DATA_DELAY_2 = QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_2,
    /**<Data is output 2 DCLK cycle after the CS N goes active. */
    QSPI_DATA_DELAY_3 = QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_3
    /**<Data is output 3 DCLK cycle after the CS N goes active. */
} qspiDataDelay_t;

/**
 *  \brief  Enumerates the number of Address bytes to be sent before
 *          transfer in memory mapped mode for each chip select
 */
typedef enum qspiMemMapNumAddrBytes
{
    QSPI_MEM_MAP_NUM_ADDR_BYTES_ONE =
        QSPI_SPI_SETUP0_REG_NUM_A_BYTES_ONE_BYTE,
    /**< One address byte for Chip Select N*/
    QSPI_MEM_MAP_NUM_ADDR_BYTES_TWO =
        QSPI_SPI_SETUP0_REG_NUM_A_BYTES_TWO_BYTES,
    /**< Two address bytes for chip select N */
    QSPI_MEM_MAP_NUM_ADDR_BYTES_THREE =
        QSPI_SPI_SETUP0_REG_NUM_A_BYTES_THREE_BYTES,
    /**< Three address bytes for chip select N */
    QSPI_MEM_MAP_NUM_ADDR_BYTES_FOUR =
        QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES
    /**< Four address bytes for Chip select N */
} qspiMemMapNumAddrBytes_t;

/**
 *  \brief   This enumerates the values for switch to be set in the
 *           QSPI switch register for selection between config port
 *           and memory mapped port.
 *           If 0 (default) config port has is selected to control
 *           config of core SPI module module.
 *           If 1, Memory Mapped Protocol Translator is selected to
 *           control config port of core SPI module.
 */
typedef enum qspiMemMapPortSel
{
    QSPI_MEM_MAP_PORT_SEL_CFG_PORT =
        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
    /** < config port is selected to control config of core
          SPI module. */
    QSPI_MEM_MAP_PORT_SEL_MEM_MAP_PORT =
        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT
    /** < Memory Mapped Protocol Translator is selected to
          control config port of core SPI module.*/
} qspiMemMapPortSel_t;

/**
 * \brief  This enum Enumerates the different read types for each chip
 *         select for transfer in memory mapped mode.
 */
typedef enum qspiMemMapReadType
{
    QSPI_MEM_MAP_READ_TYPE_NORMAL =
        QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ,
    /**< Normal read type for Chip select 0
     *   Normal means single read mode.
     */
    QSPI_MEM_MAP_READ_TYPE_DUAL =
        QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ,
    /**< Dual read type for chip select 0 */
    QSPI_MEM_MAP_READ_TYPE_NORMAL_READTYPE =
        QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ_TYPE,
    /**< Normal read type for Chip select 0 */
    QSPI_MEM_MAP_READ_TYPE_QUAD =
        QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ
    /**< Quad read type for chip select 1 */
} qspiMemMapReadType_t;

/**
 *
 * \brief   Enumerates the various transfer commands to be set in the
 *          command register for transfer using configuration registers.
 */
typedef enum qspiCfgModeTxCmd
{
    QSPI_CFG_MODE_TX_CMD_FOUR_PIN_READ_SINGLE =
        QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE,
    /**< Four Pin single read command .*/
    QSPI_CFG_MODE_TX_CMD_FOUR_PIN_WRITE_SINGLE =
        QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE,
    /**<Four pin single write command .*/
    QSPI_CFG_MODE_TX_CMD_FOUR_PIN_READ_DUAL =
        QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL,
    /**< Four pin dual read command.*/
    QSPI_CFG_MODE_TX_CMD_THREE_PIN_READ_SINGLE =
        QSPI_SPI_CMD_REG_CMD_THREE_PIN_READ_SINGLE,
    /**< Three pin single read command.*/
    QSPI_CFG_MODE_TX_CMD_THREE_PIN_WRITE_SINGLE =
        QSPI_SPI_CMD_REG_CMD_THREE_PIN_WRITE_SINGLE,
    /**< Three pin single write command.*/
    QSPI_CFG_MODE_TX_CMD_SIX_PIN_READ_QUAD =
        QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD
    /**< Six pin quad read command.*/
} qspiCfgModeTxCmd_t;
/* ========================================================================== */
/*                             Structure Definitions                          */
/* ========================================================================== */
/* MISRAC doesn't allow Unions so Undefined the Macro
 * QSPI_H_BACKWARD_COMPATIBLE_CHG which fixes MISRAC Issue: 74 S:
 * MISRAC_2012_R.19.2: Union declared" */
#ifdef QSPI_H_BACKWARD_COMPATIBLE_CHG
/*
 *  \brief Register bitfield definition for Command register.
 *
*/
typedef struct
{
    uint32_t frameLength : 12;
    /**< Frame Length. */
    uint32_t res1        : 2;
    uint32_t wirq        : 1;
    /**< Word Completion Interrupt. */
    uint32_t firq        : 1;
    /**< Frame Completion Interrupt. */
    uint32_t trCmd       : 3;
    /**< Transfer command. */
    uint32_t wordLength  : 7;
    /**< Word Length. */
    uint32_t res2        : 2;
    uint32_t cs          : 2;
    /**< chip Select. */
}HAL_QSPI_Command_t;

/*
 * \brief Union to access Command register value and bit fields
 *
*/
typedef union
{
    uint32_t           reg;
    /**< 32 bit command register. */
    HAL_QSPI_Command_t regFields;
    /**< structure to access register bit fields. */
}HAL_QSPI_Command_reg;

/*
 * \brief Register bitfield definition for Device Control register.
 *
*/
typedef struct
{
    uint32_t CKP0  : 1;
    /**<  Clock polarity for chip select 0. */
    uint32_t CSP0  : 1;
    /**<  Chip select polarity for chip select 0. */
    uint32_t CKPH0 : 1;
    /**<  Clock phase for chip select 0. */
    uint32_t DD0   : 2;
    /**<  Data Delay For chip select 0. */
    uint32_t res0  : 3;
    /**<  Reserved bits. */
    uint32_t CKP1  : 1;
    /**<  Clock polarity for chip select 1. */
    uint32_t CSP1  : 1;
    /**<  Chip select polarity for chip select 1. */
    uint32_t CKPH1 : 1;
    /**<  Clock phase for chip select 1. */
    uint32_t DD1   : 2;
    /**<  Data Delay For chip select 1. */
    uint32_t res1  : 3;
    /**<  Reserved bits. */
    uint32_t CKP2  : 1;
    /**<  Clock polarity for chip select 2. */
    uint32_t CSP2  : 1;
    /**<  Chip select polarity for chip select 2. */
    uint32_t CKPH2 : 1;
    /**<  Clock phase for chip select 2. */
    uint32_t DD2   : 2;
    /**<  Data Delay For chip select 2. */
    uint32_t res2  : 3;
    /**<  Reserved bits. */
    uint32_t CKP3  : 1;
    /**<  Clock polarity for chip select 3. */
    uint32_t CSP3  : 1;
    /**<  Chip select polarity for chip select 3. */
    uint32_t CKPH3 : 1;
    /**<  Clock phase for chip select 3. */
    uint32_t DD3   : 2;
    /**<  Data Delay For chip select 3. */
    uint32_t res3  : 3;
    /**<  Reserved bits. */
}HAL_QSPI_DeviceControl_t;

/*
 * \brief Union to access Device Control register value and bit fields
 *
*/
typedef union
{
    uint32_t                 reg;
    /**<  32 bit Device Control register. */
    HAL_QSPI_DeviceControl_t regFields;
    /**<  structure to access register bit fields. */
}HAL_QSPI_DeviceControl_reg;

/*
 * \brief Register bitfield definition for Memory Map Setup register.
 *
*/
typedef struct
{
    uint32_t readCmd       : 8;
    /**<  Read command. */
    uint32_t numAddBytes   : 2;
    /**<  Number of Address Bytes (0 = 1 Byte; 1 = 2 Bytes; 2 = 3 Bytes; 3 = 4
     *Bytes). */
    uint32_t numDummyBytes : 2;
    /**<  Number of Dummy bytes for Fast Read ( 1 = use 8 Bits; 2 = Use 16 Bits;
     *3 = Use 24 Bits). */
    uint32_t readType      : 2;
    /**<  Read Type Single Dual or Quad Read Mode. */
    uint32_t res1          : 2;
    uint32_t writeCmd      : 8;
    /**<  Write command. */
    uint32_t numDummyBits  : 6;
    /**<  Number of Dummy bits to use if Dummy Bytes is 0. */
    uint32_t res2          : 2;
}HAL_QSPI_MemMapSetup_t;

/*
 * \brief Union to access Memory Map Setup register value and bit fields
 *
*/
typedef union
{
    uint32_t               reg;
    /**<  32 bit Memory Map Setup register. */
    HAL_QSPI_MemMapSetup_t regFields;
    /**<  structure to access register bit fields. */
}HAL_QSPI_MemMapSetup_reg;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief This function configures the idle mode of the QSPI
 *
 * \param     baseAdd   QSPI base address.
 * \param     idleMode  Idle mode to be configured. Possible values are
 *                      0x0: Force-idle. An idle request is acknowledged
 *                           unconditionally
 *                      0x1: No-idle. An idle request is never acknowledged
 *                      0x2: Smart-idle. Acknowledgement to an idle request is
 *                           given based on the internal activity of the module
 * \return    None
 */
void QSPIconfigIdleMode(uint32_t baseAdd, uint32_t idleMode);

/**
 *  \brief This function sets DCLK_DIV feild in SPICC register and enables clock.
 *
 * \param     baseAdd           QSPI base address.
 * \param     in_ClockSettings  Clock Settings based on enum qspi_ClockFreq_e.
 *
 * \return    None
 */
void QSPISetClockControl(uint32_t baseAdd, qspi_ClockFreq_e in_ClockSettings);

/**
 *  \brief This function sets Device Control register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     value     Value to be written to Device Control register
 *
 * \return    None
 */
void QSPIsetDeviceControl(uint32_t baseAdd, uint32_t value);

/**
 *  \brief This function returns value of device control register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Deivce Control register value
 */
uint32_t QSPIgetDeviceControl(uint32_t baseAdd);

/**
 *  \brief This function sets Command register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     cmd       Value to be written to Command register
 *
 * \return    None
 */
void QSPIsetCommandReg(uint32_t baseAdd, uint32_t cmd);

/**
 *  \brief This function returns value of Command register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Command register value
 */
uint32_t QSPIgetCommandReg(uint32_t baseAdd);

/**
 *  \brief This function returns value of Status register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Status register value
 */
uint32_t QSPIgetStatus(uint32_t baseAdd);

/**
 *  \brief This function returns Word count value of Status register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Word count field in Status register
 */
uint32_t QSPIgetStatusWordCount(uint32_t baseAdd);

/**
 *  \brief This function is blocking and waits till busy bit in status register is
 *  reset.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    None
 */
void QSPIWaitIdle(uint32_t baseAdd);

/**
 *  \brief This function writes to data register: data, data1, data2, data3
 *
 * \param     baseAdd   QSPI base address.
 * \param     data      pointer to source address.
 * \param     length    number of words to be written - accepted values from 1
 *                      to 4.
 *
 * \return    None
 */
void QSPIwriteData(uint32_t baseAdd, const uint32_t *data, int32_t length);

/**
 *  \brief This function reads value of data register: data, data1, data2, data3
 *
 * \param     baseAdd   QSPI base address.
 * \param     data      pointer to destination address.
 * \param     length    number of words to be read - accepted values from 1
 *                      to 4.
 *
 * \return    None
 */
void QSPIreadData(uint32_t baseAdd, uint32_t *data, int32_t length);

/**
 *  \brief This function sets Memory Map Setup register.
 *
 * \param     baseAdd       QSPI base address.
 * \param     value         Value to be written to Memory Map Setup register
 * \param     chipSelect    External Chip Select value - supported values 0 to 3
 *                          for cs0 to cs3 respectively
 *
 * \return    None
 */
void QSPISetMemoryMapSetup(uint32_t baseAdd, uint32_t value,
                           uint32_t chipSelect);

/**
 *  \brief This function returns value of Memory Map Setup register.
 *
 * \param     baseAdd       QSPI base address.
 * \param     chipSelect    External Chip Select value - supported values 0 to 3
 *                          for cs0 to cs3 respectively
 *
 * \return    Memory Map Setup register value
 */
uint32_t QSPIgetMemoryMapSetup(uint32_t baseAdd, uint32_t chipSelect);

/**
 * \brief This function selects the memory mapped mode in SPI switch register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     MMPT_S    Memory map switch value
 *
 * \return    None
 */
void QSPISetMAddrSpace(uint32_t baseAdd, uint8_t MMPT_S);

/**
 * \brief This Function enables only specified QSPI interrupts
 *
 * \param   baseAdd    QSPI base address.
 * \param   intFlag    mask value for the interrupts to be enabled.
 *
 * \returns None.
 *
 */
void QSPIintEnable(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief This Function disables only specified QSPI interrupts
 *
 * \param   baseAdd    QSPI base address.
 * \param   intFlag    mask value for the interrupts to be enabled.
 *
 * \returns None.
 *
 */
void QSPIintDisable(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief This function gets the status of enabled interrupts
 *
 * \param     baseAdd   QSPI base address.
 *
 * \returns all the enabled interrupts.
 *
 */
uint32_t QSPIgetEnabledIntStatus(uint32_t baseAdd);

/**
 * \brief This function returns the status of interrupts.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \returns all the interrupt status.
 *
 */
uint32_t QSPIintStatus(uint32_t baseAdd);

/**
 * \brief This Function clears the interrupts.
 *
 * \param   baseAdd    QSPI base address.
 * \param   intFlag    mask value for the interrupts to be cleared.
 *
 * \returns None.
 *
 */
void QSPIintClear(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief This function returns the raw status of interrupts.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \returns all the raw interrupt status.
 *
 */
uint32_t QSPIintRawStatus(uint32_t baseAdd);

/**
 * \brief This Function clears the raw status of interrupts.
 *
 * \param   baseAdd    QSPI base address.
 * \param   intFlag    mask value for the raw status interrupts to be cleared.
 *
 * \returns None.
 *
 */
void QSPIintRawStatusClear(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief   This function configures the QSPI to work in different clock modes
 *          for each output chip select.
 *
 * \details The combination of Clock phase
 *          and clock polarity creates the SPI mode. Most serial flash
 *          devices support only mode 0 and mode 3. Changing the clock polarity
 *          also swaps the transmit/receive clock edge relationship.
 *          If a slave device states that it receives data on the
 *          rising edge and transmits on the falling edge of the clock,
 *          then it can only support mode 0 or 3.
 *          This can only be done if QSPI module is not busy.
 *
 *          The 4 possible modes are :
 *
 *          CKP             CKPH         Description
 *          0               0            Data input captured on rising edge of
 *                                       qspi1_sclk clock. Data output generated
 *                                       on falling edge of qspi1_sclk clock
 *          0               1            Data input captured on falling edge of
 *                                       qspi1_sclk clock. Data output generate
 *                                       on rising edge of qspi1_sclk clock
 *          1               0            Data input captured on falling edge of
 *                                       qspi1_sclk clock. Data output generated
 *                                       on rising edge of qspi1_sclk clock
 *          1               1            Data input captured on rising edge of
 *                                       qspi1_sclk clock. Data output generated
 *                                       on falling edge of qspi1_sclk clock
 *
 * \param  baseAddr        Base Address of QSPI module registers.
 * \param  chipSelect      chipSelect for which the mode is to be configured.
 *                         Supported values according to enum
 *                         #qspiChipSelect_t.
 * \param  clkMode       Mode required to be selected.
 *                         Supported values given by enum #qspiClkMode_t
 */
void QSPISetClkMode(uint32_t baseAddr,
                    uint32_t chipSelect,
                    uint32_t clkMode);


/**
 * \brief   This function configures the chip select polarity for
 *          a selected chip select.
 *          This can only be done if QSPI module is not busy.
 *
 * \param   baseAddr            Base Address for QSPI module registers.
 * \param   chipSelect          chip select for which polarity is to be
 *                              configured. Supported values are
 *                              according to enum
 *                              #qspiChipSelect_t.
 * \param   csPol               Polarity value of the chip select
 *                              selected.
 *                              Supported values are given by the enum
 *                              #qspiCsPol_t
 */
void QSPISetCsPol(uint32_t baseAddr,
                  uint32_t chipSelect,
                  uint32_t csPol);

/**
 * \brief   This function configures the Data delay for each chip select.
 *          This can only be done if QSPI module is not busy.
 *
 * \param   baseAddr     Base Address for QSPI module registers.
 * \param   chipSelect   chip select for which polarity is to be configured.
 *                       Supported values are according to enum
 *                       #qspiChipSelect_t.
 * \param   dataDelay    Value of Data Delay.
 *                       Supported values are
 *                       given by enum #qspiDataDelay_t
 */
void QSPISetDataDelay(uint32_t baseAddr,
                      uint32_t chipSelect,
                      uint32_t dataDelay);

/**
 * \brief   Set the QSPI clock register divider value.
 *
 * \details This function sets the QSPI clock control register
 *          with serial data clock divider ratio (DCLK_DIV)
 *          according to the input clock provided and the output clock
 *          required.
 *          DCLK_DIV = ((input clock) / (output clock)) - 1.
 *          This function also enables the clock for QSPI module.
 *          This can only be done if QSPI module is not busy.
 *
 * \param   baseAddr      Base Address for QSPI module registers.
 * \param   clkDividerVal clock divider value to be set.
 */
void QSPISetPreScaler(uint32_t baseAddr, uint32_t clkDividerVal);

/**
 * \brief   Set number of address bytes for memory mapped mode.
 *
 * \details This function configures the number af Address Bytes to be
 *          sent for memory mapped protocol translator for selected chip
 *          select.By default, the device uses 3 address bytes.
 *          This can only be done if QSPI module is not busy.
 *
 * \param   baseAddr           Base Address for QSPI module registers.
 * \param   chipSelect         chip select for which polarity is to be
 *                             configured.
 *                             Supported values are according to enum
 *                             #qspiChipSelect_t.
 * \param   numAddrBytes    Number of Address bytes to be sent for
 *                          memory mapped protocol translator.
 *                          Supported values are :
 *                          for each chip select given by enum
 *                          #qspiMemMapNumAddrBytes_t.
 */
void QSPISetMemMapNumAddrBytes(uint32_t baseAddr,
                               uint32_t chipSelect,
                               uint32_t numAddrBytes);

/**
 * \brief    Set Memory address space
 *
 * \details  This function selects the memory mapped mode in
 *           SPI switch register and configures mapped address
 *           for different chip select in control module.
 *           It provides a functionality for
 *           remapping the memory mapped address space to one of
 *           the four supported chip selects or to the
 *           configuration registers.
 *
 * \param    baseAddr            Base Address for QSPI module registers
 * \param    memMappedPortSwitch Switch for selection of memory mapped port
 *                               and configuration port.
 *                               Supported values are given by enum
 *                               qspiMemMapPortSel_t.
 * \param    chipSelect    chip select for which polarity is to be configured.
 *                         Supported values given by #qspiChipSelect_t.
 */
void QSPISetMemAddrSpace(uint32_t baseAddr,
                         uint32_t chipSelect,
                         uint32_t memMappedPortSwitch);

/**
 * \brief    Set Read Command in memory mapped mode.
 *
 * \details  This function configures the read command for memory
 *           mapped protocol translator in memory mapped SPI setup register.
 *           The command send is according to the slave device connected.
 *           By default, the device uses a read command of 0x3.
 *           This can only be done if QSPI module is not busy.
 *
 * \param    baseAddr      Base Address for QSPI module registers.
 * \param    chipSelect    chip select for which polarity is to be configured.
 *                         Supported values are according to enum
 *                         #qspiChipSelect_t.
 * \param    readCmd       Read Command to be sent to the flash device.
 *                         This command is specific to the flash device being
 *                         used.
 */
void QSPISetMemMapReadCmd(uint32_t baseAddr,
                          uint32_t chipSelect,
                          uint32_t readCmd);

/**
 * \brief   Set read type in memory mapped mode.
 *
 * \details This function configures the read type for QSPI in memory mapped
 *          mode for selected chip select.Determines if the read command
 *          is a single, dual or quad read mode.
 *          This can only be done if QSPI module is not busy.
 *
 * \param   baseAddr       Base Address for QSPI module registers.
 * \param   chipSelect     chip select for which polarity is to be configured.
 *                         Supported values are according to enum
 *                         #qspiChipSelect_t.
 * \param   readType       Read type to be chosen.
 *                         Supported values are given by enum
 *                         #qspiMemMapReadType_t.
 */

void QSPISetMemMapReadType(uint32_t baseAddr,
                           uint32_t chipSelect,
                           uint32_t readType);

/**
 * \brief   Set Number of dummy bits for memory mapped mode.
 *
 * \details This function configures the number of Dummy Bits to be
 *          sent for memory mapped protocol translator for selected chip
 *          select for fast read mode.
 *          This can only be done if QSPI module is not busy.
 *
 * \param   baseAddr        Base Address for QSPI module registers.
 * \param   chipSelect      chip select for which polarity is to be configured.
 *                          Supported values are according to enum
 *                          #qspiChipSelect_t.
 * \param   numDummyBits    Number of Dummy Bits to be sent for
 *                          memory mapped protocol translator.
 *                          User can pass any value from 0 to 32 bits.
 */
void QSPISetMemMapNumDummyBits(uint32_t baseAddr,
                               uint32_t chipSelect,
                               uint32_t numDummyBits);

/**
 * \brief    Set Transfer Command
 *
 * \details  This function sets the transfer command in the command
 *           for transfer of data in configuration mode.
 *
 * \param    baseAddr         Base Address of QSPI module registers
 * \param    qspitxcmd        The transfer commnand to be set for initiating the
 *                            qspi transfer in config mode.
 */
void QSPISetCfgModeTxCmd(uint32_t baseAddr, uint32_t qspitxcmd);

/**
 * \brief    Set write command in memory mapped mode.
 *
 * \details  This function configures the write command for memory
 *           mapped protocol translator in memory mapped SPI setup register.
 *           The command send is according to the slave device connected.
 *           By default, the device uses a write command of 0x2.
 *           This can only be done if QSPI module is not busy.
 *
 * \param    baseAddr      Base Address for QSPI module registers.
 * \param    chipSelect    chip select for which polarity is to be configured.
 *                         Supported values are according to enum
 *                         #qspiChipSelect_t.
 * \param    writeCmd      Write Command to be sent to the flash device.
 *                         This command is specific to the flash device being
 *                         used.
 */
void QSPISetMemMapWriteCmd(uint32_t baseAddr,
                           uint32_t chipSelect,
                           uint32_t writeCmd);
#ifdef __cplusplus
}
#endif

#endif
 /** @} */
/********************************* End of file ******************************/

