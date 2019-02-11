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
 * \file  qspi.c
 * \brief      This file contains the function prototypes for the device
 *             abstraction layer for QSPI. It also contains some
 *             related macro definitions and enum definitions.
 *
 *             The QSPI module support single, dual and quad read mode
 *             in interrupt and polling mode using QSPI data registers
 *             and also support memory mapped mode.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include <stdint.h>
#include <string.h>
/*LDRA_ANALYSIS*/
#include <ti/csl/csl_qspi.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/hw_types.h>


/* ========================================================================== */
/*                             Macros                                  */
/* ========================================================================== */

#define QSPI_SPI_SETUP_REG(n)   (QSPI_SPI_SETUP0_REG + ((n) * 0x4U))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is setting Idle mode field
 *  of QSPI Sysconfig register" */
void QSPIconfigIdleMode(uint32_t baseAdd, uint32_t idleMode)
{
    /* Set the idle mode value */
    HW_WR_FIELD32(baseAdd + QSPI_SYSCONFIG,
                  QSPI_SYSCONFIG_IDLE_MODE,
                  idleMode);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is sets DCLK_DIV feild in
 *  SPICC register and enables clock." */
void QSPISetClockControl(uint32_t baseAdd, qspi_ClockFreq_e in_ClockSettings)
{
    uint32_t lv_clkDivider;
    /* select 128/192MHz from L4 QSPI CLK CTRL register */

    /* get qspi CC register divider value */
    lv_clkDivider = (uint32_t) in_ClockSettings & QSPI_CLKDIVIDER_MASK;

    /* wait for the QSPI to be idle */
    QSPIWaitIdle(baseAdd);

    /* turn off QSPI data clock */
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF);

    /* clear QSPI clock divider*/
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV,
        0U);

    /* update QSPI clock divider*/
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV,
        lv_clkDivider);

    /* enable QSPI data clock */
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON);
}

void QSPIsetDeviceControl(uint32_t baseAdd, uint32_t value)
{
    /* wait for the QSPI to be idle */
    QSPIWaitIdle(baseAdd);
    HW_WR_REG32(baseAdd + QSPI_SPI_DC_REG, value);
}

uint32_t QSPIgetDeviceControl(uint32_t baseAdd)
{
    uint32_t devCtrlVal;

    devCtrlVal =  HW_RD_REG32(baseAdd + QSPI_SPI_DC_REG);

    return devCtrlVal;
}

void QSPIsetCommandReg(uint32_t baseAdd, uint32_t cmd)
{
    /* wait for the QSPI to be idle */
    QSPIWaitIdle(baseAdd);
    HW_WR_REG32(baseAdd + QSPI_SPI_CMD_REG, cmd);
}

uint32_t QSPIgetCommandReg(uint32_t baseAdd)
{
    uint32_t cmdRegVal;

    cmdRegVal = HW_RD_REG32(baseAdd + QSPI_SPI_CMD_REG);

    return cmdRegVal;
}

uint32_t QSPIgetStatus(uint32_t baseAdd)
{
    uint32_t cmdRegStatus;

    cmdRegStatus = HW_RD_REG32(baseAdd + QSPI_SPI_STATUS_REG);

    return cmdRegStatus;
}

uint32_t QSPIgetStatusWordCount(uint32_t baseAdd)
{
    return ((QSPIgetStatus(baseAdd) &
             QSPI_SPI_STATUS_REG_WDCNT_MASK) >> QSPI_SPI_STATUS_REG_WDCNT_SHIFT);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. Here we waits till busy bit in
 * QSPI status register is reset" */
void QSPIWaitIdle(uint32_t baseAdd)
{
    /* wait while QSPI is busy */
    while ((QSPIgetStatus(baseAdd) & QSPI_SPI_STATUS_REG_BUSY_MASK) ==
           QSPI_SPI_STATUS_REG_BUSY_BUSY)
    {
        /*Do nothing */
    }
}

/*TI_INSPECTED 1 D 1: MISRA-C:2012_R.2.7
 * "Reason - Ensured procedure parameter is used" */
void QSPIwriteData(uint32_t baseAdd, const uint32_t *data, int32_t length)
{
    const uint32_t *pData;
    pData = data;

    if(pData != ((void *) NULL))
    {
        HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG, *pData);
        if (length > 1)
        {
            /*TI_INSPECTED 567 S : MISRAC_2012_R.18.1
             * "Reason - Pointer arithmetic needed here" */
            pData++;
            HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG_1, *pData);
        }
        if (length > 2)
        {
            /*TI_INSPECTED 567 S : MISRAC_2012_R.18.1
             * "Reason - Pointer arithmetic needed here" */
            pData++;
            HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG_2, *pData);
        }
        if (length > 3)
        {
            /*TI_INSPECTED 567 S : MISRAC_2012_R.18.1
             * "Reason - Pointer arithmetic needed here" */
            pData++;
            HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG_3, *pData);
        }
    }
}

void QSPIreadData(uint32_t baseAdd, uint32_t *data, int32_t length)
{
    uint32_t *pData;
    pData = data;

    if(pData != ((void *) NULL))
    {
        *pData = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG);
        if (length > 1)
        {
            /*TI_INSPECTED 567 S : MISRAC_2012_R.18.1
             * "Reason - Pointer arithmetic needed here" */
            pData++;
            /*TI_INSPECTED 8 D: MISRAC_2012_R.2.2
             * "Reason - LDRA tool issue not able to understand Pointer
             *  arithmetic" */
            *pData = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG_1);
        }
        if (length > 2)
        {
            /*TI_INSPECTED 567 S : MISRAC_2012_R.18.1
             * "Reason - Pointer arithmetic needed here" */
            pData++;
            *pData = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG_2);
        }
        if (length > 3)
        {
            /*TI_INSPECTED 567 S : MISRAC_2012_R.18.1
             * "Reason - Pointer arithmetic needed here" */
            pData++;
            *pData = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG_3);
        }
    }
}

/*TI_INSPECTED 1 D 1: MISRA-C:2012_R.2.7
 * "Reason - Ensured procedure parameter is used" */
void QSPISetMemoryMapSetup(uint32_t baseAdd, uint32_t value,
                           uint32_t chipSelect)
{
    HW_WR_REG32(baseAdd + QSPI_SPI_SETUP0_REG + (4U * chipSelect), value);
}

uint32_t QSPIgetMemoryMapSetup(uint32_t baseAdd, uint32_t chipSelect)
{
    uint32_t memMapSetUpRegVal;

    memMapSetUpRegVal = HW_RD_REG32
                            (baseAdd + QSPI_SPI_SETUP0_REG + (4U * chipSelect));

    return memMapSetUpRegVal;
}

/*TI_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is setting MMPT_S field
 *  of QSPI_SPI_SWITCH_REG register" */
void QSPISetMAddrSpace(uint32_t baseAdd, uint8_t MMPT_S)
{
    /* Set to MMPT_S value */
    HW_WR_FIELD32(baseAdd + QSPI_SPI_SWITCH_REG,
                  QSPI_SPI_SWITCH_REG_MMPT_S,
                  MMPT_S);
}

void QSPIintEnable(uint32_t baseAdd, uint32_t intFlag)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAdd + QSPI_INTR_ENABLE_SET_REG);

    regVal |= intFlag;

    HW_WR_REG32(baseAdd + QSPI_INTR_ENABLE_SET_REG, regVal);
}

void QSPIintDisable(uint32_t baseAdd, uint32_t intFlag)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAdd + QSPI_INTR_ENABLE_CLEAR_REG);

    regVal |= intFlag;

    HW_WR_REG32(baseAdd + QSPI_INTR_ENABLE_CLEAR_REG, regVal);
}

uint32_t QSPIgetEnabledIntStatus(uint32_t baseAdd)
{
    uint32_t enabledIntStatus;

    enabledIntStatus = HW_RD_REG32(baseAdd + QSPI_INTR_ENABLE_SET_REG);

    return enabledIntStatus;
}

uint32_t QSPIintStatus(uint32_t baseAdd)
{
    uint32_t intStatus;

    intStatus = HW_RD_REG32(baseAdd + QSPI_INTR_STATUS_ENABLED_CLEAR);

    return intStatus;
}

 /*TI_INSPECTED 1 D 1: MISRA-C:2012_R.2.7
 * "Reason - Ensured procedure parameter is used" */
void QSPIintClear(uint32_t baseAdd, uint32_t intFlag)
{
    HW_WR_REG32(baseAdd + QSPI_INTR_STATUS_ENABLED_CLEAR, intFlag);
}

uint32_t QSPIintRawStatus(uint32_t baseAdd)
{
    uint32_t intRawStatus;

    intRawStatus = HW_RD_REG32(baseAdd + QSPI_INTR_STATUS_RAW_SET);

    return intRawStatus;
}

/*TI_INSPECTED 1 D 1: MISRA-C:2012_R.2.7
 * "Reason - Ensured procedure parameter is used" */
void QSPIintRawStatusClear(uint32_t baseAdd, uint32_t intFlag)
{
    HW_WR_REG32(baseAdd + QSPI_INTR_STATUS_RAW_SET, intFlag);
}


void QSPISetClkMode(uint32_t baseAddr, uint32_t chipSelect, uint32_t clkMode)
{
    /* read value of the device control register */
    uint32_t regVal;

    regVal = QSPIgetDeviceControl(baseAddr);

    /* Set the values of clock phase and clock polarity in the device
     * Control register for chip Select passed as the parameter to function.
     */
    /* The clock mode for different chip select are at a separation of
     * 8 bits in the device control register.
     * So 8U has been multiplied to the chip select value.
     */
    regVal &= (uint32_t)(~((QSPI_CLK_MODE_3) << (8U * chipSelect)));
    regVal |= (clkMode << (8U * chipSelect));

    QSPIsetDeviceControl(baseAddr, regVal);
}

void QSPISetCsPol(uint32_t baseAddr, uint32_t chipSelect, uint32_t csPol)
{
    /* Read value of device control register */
    uint32_t regVal;

    regVal = QSPIgetDeviceControl(baseAddr);

    /* Set the chip select polarity for the required chip Select */
    /* The polarity for different chip select are at a separation of
     * 8 bits in the device control register.
     * So 8U has been multiplied to the chip select value.
     */
    regVal &= (uint32_t)(~((QSPI_CS_POL_ACTIVE_HIGH) << (QSPI_SPI_DC_REG_CSP0_SHIFT +
                                     (8U * chipSelect))));
    regVal |= (csPol << (QSPI_SPI_DC_REG_CSP0_SHIFT +
                                     (8U * chipSelect)));
    /* Set the value of the device control register to configure chip
     * polarity
     */
    QSPIsetDeviceControl(baseAddr, regVal);
}

void QSPISetDataDelay(uint32_t baseAddr,
                      uint32_t chipSelect,
                      uint32_t dataDelay)
{
    /* Read the value of device control register */
    uint32_t regVal;

    regVal = QSPIgetDeviceControl(baseAddr);

    /** Set the Data Delay value for the required chip Select */
    /* The Data delay for different chip select are at a separation of
     * 8 bits in the device control register.
     * So 8U has been multiplied to the chip select value.
     */
    regVal &= (uint32_t)(~((QSPI_DATA_DELAY_3) << (QSPI_SPI_DC_REG_DD0_SHIFT +
                            (8U * chipSelect))));
    regVal |= (dataDelay << (QSPI_SPI_DC_REG_DD0_SHIFT +
                            (8U * chipSelect)));

    /* Set the value of the device control register to configure data
       delay */
    QSPIsetDeviceControl(baseAddr, regVal);
}

void QSPISetPreScaler(uint32_t baseAddr, uint32_t clkDividerVal)
{
    /* Read the value of Clock control register */
    uint32_t regVal =
        HW_RD_REG32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG);
    /* wait for QSPI to be idle */
    QSPIWaitIdle(baseAddr);

    /* turn off QSPI data clock */
    HW_SET_FIELD32(regVal, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF);
   /* Set the value of QSPI clock control register */
    HW_WR_REG32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, regVal);

    /* Set the QSPI clock divider bit field value*/
    HW_SET_FIELD32(regVal, QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV,
        clkDividerVal);
    /* Set the value of QSPI clock control register */
    HW_WR_REG32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, regVal);

    /* Enable the QSPI data clock */
    HW_SET_FIELD32(regVal, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
                QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON);
    /* Set the value of QSPI clock control register */
    HW_WR_REG32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, regVal);
}

void QSPISetMemMapNumAddrBytes(uint32_t baseAddr,
                               uint32_t chipSelect,
                               uint32_t numAddrBytes)
{
    uint32_t addr = baseAddr + QSPI_SPI_SETUP_REG(chipSelect);
    HW_WR_FIELD32(addr, QSPI_SPI_SETUP0_REG_NUM_A_BYTES, numAddrBytes);
}

void QSPISetMemAddrSpace(uint32_t baseAddr,
                         uint32_t chipSelect,
                         uint32_t memMappedPortSwitch)
{
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG,
        QSPI_SPI_SWITCH_REG_MMPT_S, memMappedPortSwitch);
}

void QSPISetMemMapReadCmd(uint32_t baseAddr,
                          uint32_t chipSelect,
                          uint32_t readCmd)
{
    uint32_t addr = baseAddr + QSPI_SPI_SETUP_REG(chipSelect);
    HW_WR_FIELD32(addr, QSPI_SPI_SETUP0_REG_RCMD, readCmd);
}

void QSPISetMemMapReadType(uint32_t baseAddr,
                           uint32_t chipSelect,
                           uint32_t readType)
{
    uint32_t addr = baseAddr + QSPI_SPI_SETUP_REG(chipSelect);
    HW_WR_FIELD32(addr, QSPI_SPI_SETUP0_REG_READ_TYPE, readType);
}

void QSPISetMemMapNumDummyBits(uint32_t baseAddr,
                               uint32_t chipSelect,
                               uint32_t numDummyBits)
{
    uint32_t addr = baseAddr + QSPI_SPI_SETUP_REG(chipSelect);
    /* Read the value of setup register for given chip select */
    uint32_t regVal = HW_RD_REG32(addr);
    uint32_t numDummyBytes;
    /* set number of dummy bits or bytes in setup register for transfer of
     * data in memory mapped mode
     */
    numDummyBytes = numDummyBits / 8U;
    numDummyBits = numDummyBits % 8U;
    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP0_REG_NUM_D_BITS, numDummyBits);
    HW_SET_FIELD32(regVal,
                QSPI_SPI_SETUP0_REG_NUM_D_BYTES,
                numDummyBytes);
    HW_WR_REG32(addr, regVal);
}

void QSPISetCfgModeTxCmd(uint32_t baseAddr, uint32_t qspitxcmd)
{
    uint32_t regVal, fieldVal;

    /* wait for QSPI to be idle */
    QSPIWaitIdle(baseAddr);

    /* Read value of the qspi command register */
    regVal = QSPIgetCommandReg(baseAddr);

    /* Set value of all the fields for qspi command */
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspitxcmd);
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FIRQ,
        qspitxcmd);
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WIRQ,
        qspitxcmd);
    fieldVal = HW_GET_FIELD(qspitxcmd, QSPI_SPI_CMD_REG_WLEN);
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN,
        ((fieldVal - 1U) << QSPI_SPI_CMD_REG_WLEN_SHIFT));
    fieldVal = HW_GET_FIELD(qspitxcmd, QSPI_SPI_CMD_REG_FLEN);
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FLEN,
        ((fieldVal - 1U) << QSPI_SPI_CMD_REG_FLEN_SHIFT));
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CSNUM, qspitxcmd);

    /* Set the value of QSPI command in the command register */
    QSPIsetCommandReg(baseAddr, regVal);
}

void QSPISetMemMapWriteCmd(uint32_t baseAddr,
                           uint32_t chipSelect,
                           uint32_t writeCmd)
{
    uint32_t addr = baseAddr + QSPI_SPI_SETUP_REG(chipSelect);
    HW_WR_FIELD32(addr, QSPI_SPI_SETUP0_REG_WCMD, writeCmd);
}
/********************************* End of file ******************************/
