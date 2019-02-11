/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  @file   qspi.c
 *
 *  @brief  This file contains the Flash driver using QSPI hal.
 *
 */

/*_______________________________ Include Files _____________________________*/
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_cmd_init.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/pm/pmhal.h>

#define QSPI_READ_DEVICEID_MAX_WORDS   (20U)

static uint32_t getNumAddrBytesFromBits(uint32_t numBits);
static uint32_t getNumDummyBytesFromBits(uint32_t numBits);
static uint32_t getMemSetupReadType(uint32_t cmdRegDataType);
static void mem1cpy(void *dstAddr, uint32_t *srcAddr, uint32_t length);
static void QSPI_executeWriteCmd(QSPI_FlashCmd_t flashCmd);
static void QSPI_executeWriteAddrBytesCmd(QSPI_FlashCmd_t flashCmd);
static void QSPI_executeWriteDummyBytesCmd(QSPI_FlashCmd_t flashCmd);
static void QSPI_executeWrite32BitDataCmd(QSPI_FlashCmd_t flashCmd,
                                          const uint32_t *data);
static void QSPI_executeRead32BitDataCmd(QSPI_FlashCmd_t flashCmd,
                                         uint32_t       *data);
static void QSPI_executeWriteDataCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data);
static void QSPI_executeReadDataCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data);

#if (QSPI_FLASH_RESET_AT_INIT == 1)
static void QSPI_ResetModule(void);
#endif

QSPI_FlashDevInfo_t gQspiFlashDevInfo;
uint32_t gQspiCmdInitDone = 0U;

#define QSPI_FLASH_SPANSION_MFGID   (0x01U)
#define QSPI_FLASH_MICRON_MFGID     (0x20U)
#define QSPI_FLASH_WINBOND_MFGID    (0xEFU)
#define QSPI_FLASH_ISSI_MFGID       (0x9DU)

#define QSPI_FLASH_JDEC_SIZE_64MBIT   (0x17U)
#define QSPI_FLASH_JDEC_SIZE_128MBIT  (0x18U)
#define QSPI_FLASH_JDEC_SIZE_256MBIT  (0x19U)
#define QSPI_FLASH_JDEC_SIZE_512MBIT  (0x20U)
#define QSPI_FLASH_JDEC_SIZE_1GBIT    (0x21U)
#define QSPI_FLASH_JDEC_SIZE_2GBIT    (0x22U)

/**
 * \brief This function configures memory mapped address for different
 *        chip select in control module.
 *
 * \param     MMPT_S    Memory map switch value
 * \param     chipSelect    External Chip Select value from enum
 *                          qspi_ChipSelect_e
 *
 * \return    None
 */
void QSPI_ConfMAddrSpace(uint8_t MMPT_S, qspi_ChipSelect_e chipSelect)
{
    /* set MAddrSpace in control module for CS0*/
    HW_WR_FIELD32(
        (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CONTROL_IO_2,
        CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS,
        chipSelect);
}

void QSPI_SelClockFrequency(qspi_ClockFreq_e in_ClockSettings)
{
    int32_t                    retVal = STW_SOK;
    uint32_t                   dividerValue;
    uint32_t                   mulValue;
    uint32_t                   hsdivValue;
    Bool                       configHsDiv = FALSE;
    pmhalPrcmPllPostDivValue_t divConfig;
    pmhalPrcmNodeId_t          dpllId   = PMHAL_PRCM_DPLL_PER;
    pmhalPrcmNodeId_t          clkSelId = PMHAL_PRCM_MUX_UNDEF;

    mulValue     = PMHALCMDpllGetMultiplier(dpllId);
    dividerValue = PMHALCMDpllGetDivider(dpllId);

    if (((in_ClockSettings & QSPI_CLKSWITCH_MASK) >> QSPI_CLKSWITCH_SHIFT) == 0)
    {
        /* set QSPI clock source as FUNC_128M_CLK from DPLL_PER at 128 MHz */
        divConfig.postDivId = PMHAL_PRCM_DPLL_POST_DIV_H11;
        PMHALCMDpllGetPostDiv(dpllId, &divConfig, 1U);
        hsdivValue = (20U * 2U * mulValue) / ((dividerValue + 1U) * 256U);
        if (hsdivValue != divConfig.configValue)
        {
            /* Configure DPLL PER H11 outout to be 256MHz, There is a fixed
             * divider to convert to 128MHz. */
            divConfig.configValue = hsdivValue;
            configHsDiv           = TRUE;
        }
        clkSelId = PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX;
    }
    else if (((in_ClockSettings & QSPI_CLKSWITCH_MASK) >>
              QSPI_CLKSWITCH_SHIFT) == 1U)
    {
        /* set QSPI clock source as PER_QSPI_CLK from DPLL_PER at 192MHz */
        divConfig.postDivId = PMHAL_PRCM_DPLL_POST_DIV_H13;
        PMHALCMDpllGetPostDiv(dpllId, &divConfig, 1U);
        hsdivValue = (20U * 2U * mulValue) / ((dividerValue + 1U) * 192U);
        if (hsdivValue != divConfig.configValue)
        {
            /* Configure DPLL PER H13 outout to be 196MHz. */
            divConfig.configValue = hsdivValue;
            configHsDiv           = TRUE;
        }
        clkSelId = PMHAL_PRCM_DPLL_PER;
    }
    else if (((in_ClockSettings & QSPI_CLKSWITCH_MASK) >>
              QSPI_CLKSWITCH_SHIFT) == 2U)
    {
        /* set QSPI clock source as PER_QSPI_CLK from DPLL_PER at 76.8MHz */
        divConfig.postDivId = PMHAL_PRCM_DPLL_POST_DIV_H13;
        PMHALCMDpllGetPostDiv(dpllId, &divConfig, 1U);
        hsdivValue = (20U * 2U * mulValue * 10U) / ((dividerValue + 1U) * 768U);
        if (hsdivValue != divConfig.configValue)
        {
            /* Configure DPLL PER H13 outout to be 196MHz. */
            divConfig.configValue = hsdivValue;
            configHsDiv           = TRUE;
        }
        clkSelId = PMHAL_PRCM_DPLL_PER;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_SOK)
    {
        if (configHsDiv == TRUE)
        {
            PMHALCMDpllSetPostDiv(dpllId, &divConfig, 1U);
        }
        PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_QSPI_GFCLK, 1U);
        PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_QSPI_GFCLK_MUX, clkSelId);
    }
}

int32_t QSPI_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    int32_t retVal = STW_SOK;

    if ((flashCmd.numDataWords != 0) && (NULL == data))
    {
        retVal = STW_EBADARGS;
    }
    if (retVal == STW_SOK)
    {
        /* Write Command */
        QSPI_executeWriteCmd(flashCmd);

        /* Write Address Bytes */
        if (flashCmd.numAddrBits != 0)
        {
            QSPI_executeWriteAddrBytesCmd(flashCmd);
        }

        /* Write dummy Bytes */
        if (flashCmd.numAddrDummyBits != 0)
        {
            QSPI_executeWriteDummyBytesCmd(flashCmd);
        }
        /* Read or Write data */
        if (flashCmd.numDataWords != 0)
        {
            if (flashCmd.dataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE)
            {
                QSPI_executeWrite32BitDataCmd(flashCmd, data);
            }
            else
            {
                QSPI_executeRead32BitDataCmd(flashCmd, data);
            }
        }
    }
    return retVal;
}

qspi_DeviceType_e QSPI_getFlashType(qspi_DeviceType_e inDeviceType)
{
    QSPI_FlashCmd_t   flashIdCmd = {0};
    uint32_t          data[3], devCtrlInfo = 0U;
    qspi_DeviceType_e outDeviceType = DEVICE_TYPE_MICRON_QSPI4;
    if ((inDeviceType == DEVICE_TYPE_QSPI1) ||
        (inDeviceType == DEVICE_TYPE_QSPI4))
    {
        /* Auto detect the flash type and return appropriate device type. */
        /* Configure QSPI at mode 3 at 12 MHz to work with all flashes */
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKP0,
                       QSPI_SPI_DC_REG_CKP_DATA_ACTIVE);
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CSP0,
                       QSPI_SPI_DC_REG_CSP_ACTIVE_LOW);
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKPH0,
                       QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE);

        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_DD0,
                       QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_0);

        QSPIsetDeviceControl(SOC_QSPI_ADDRSP0_BASE, devCtrlInfo);

        QSPI_SelClockFrequency(QSPI_SCLK_FREQ_12MHz);
        QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, QSPI_SCLK_FREQ_12MHz);

        flashIdCmd.numCmdBits = 8;
        flashIdCmd.cmd        = QSPI_CMD_JDEC_DEVICE_ID;
        flashIdCmd.dataType   =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashIdCmd.numDataWords       = 3;
        flashIdCmd.numPerDataWordbits = 8;

        QSPI_executeCmd(flashIdCmd, &data[0]);

        /* Check for the Manufacture ID */
        if (data[0] == QSPI_FLASH_SPANSION_MFGID)
        {
            if (inDeviceType == DEVICE_TYPE_QSPI1)
            {
                outDeviceType = DEVICE_TYPE_SPANSION_QSPI1;
            }
            else
            {
                outDeviceType = DEVICE_TYPE_SPANSION_QSPI4;
            }
        }
        else if ((data[0] == QSPI_FLASH_MICRON_MFGID) &&
                 (data[2] <= QSPI_FLASH_JDEC_SIZE_128MBIT))
        {
            if (inDeviceType == DEVICE_TYPE_QSPI1)
            {
                outDeviceType = DEVICE_TYPE_MICRON_QSPI1;
            }
            else
            {
                outDeviceType = DEVICE_TYPE_MICRON_QSPI4;
            }
        }
        else if ((data[0] == QSPI_FLASH_MICRON_MFGID) &&
                 (data[2] >  QSPI_FLASH_JDEC_SIZE_128MBIT))
        {
            if (inDeviceType == DEVICE_TYPE_QSPI1)
            {
                outDeviceType = DEVICE_TYPE_MICRON_1GBIT_QSPI1;
            }
            else
            {
                outDeviceType = DEVICE_TYPE_MICRON_1GBIT_QSPI4;
            }
        }
        else if (data[0] == QSPI_FLASH_WINBOND_MFGID)
        {
            if (inDeviceType == DEVICE_TYPE_QSPI1)
            {
                outDeviceType = DEVICE_TYPE_WINBOND_QSPI1;
            }
            else
            {
                outDeviceType = DEVICE_TYPE_WINBOND_QSPI4;
            }
        }
        else if (data[0] == QSPI_FLASH_ISSI_MFGID)
        {
            if (inDeviceType == DEVICE_TYPE_QSPI1)
            {
                outDeviceType = DEVICE_TYPE_ISSI_QSPI1;
            }
            else
            {
                outDeviceType = DEVICE_TYPE_ISSI_QSPI4;
            }
        }
        else
        {
            /* return same value in output */
            outDeviceType = inDeviceType;
        }
    }
    else
    {
        /* skip autodetect and return same value in output */
        outDeviceType = inDeviceType;
    }
    return (outDeviceType);
}

/*_____________________________________________________________________________
 * FUNCTION:     QSPI_Initialize
 *
 * DESCRIPTION:  Initializes the QSPI Device.
 *
 * PARAMETERS:   ipDeviceDesc
 *                   IO:  Device Descriptor
 *
 * RETURNS:      QSPI_FLASH_SUCCESS if the QSPI initialized successfully
 *
 *               QSPI_FLASH_FAIL:
 *
 * NOTES:
 *
 *____________________________________________________________________________*/
uint32_t QSPI_Initialize(qspi_DeviceType_e DeviceType)
{
    int32_t             retVal;
    qspi_DeviceType_e   flashType;
    QSPI_FlashDevInfo_t localFlashDevInfo;

    if (DeviceType != DEVICE_TYPE_CUSTOM)
    {
        if (gQspiCmdInitDone == 0U)
        {
        #if (QSPI_FLASH_RESET_AT_INIT == 1)
            QSPI_ResetModule();
        #endif

            /* Update the device type based on actual flash present on board */
            flashType = QSPI_getFlashType(DeviceType);

            /* Default initialize for device type passed */
            retVal = QSPI_GetDefaultFlashDevInfo(flashType, &localFlashDevInfo);

            if (retVal == STW_SOK)
            {
                QSPI_ConfigFlashDevInfo(flashType, &localFlashDevInfo);
            }
            gQspiCmdInitDone = 1U;
        }
    }
    return QSPI_FLASH_SUCCESS;
} /* QSPI_Initialize */

static uint32_t getMemSetupReadType(uint32_t cmdRegDataType)
{
    uint32_t localReadType;
    if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
    }
    else if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ;
    }
    else if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ;
    }
    else
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
    }
    return localReadType;
}

static uint32_t getNumAddrBytesFromBits(uint32_t numBits)
{
    uint32_t numBytes;
    if (numBits <= 8U)
    {
        numBytes = (uint32_t) 0U;
    }
    else if (numBits <= 16U)
    {
        numBytes = 1U;
    }
    else if (numBits <= 24U)
    {
        numBytes = 2U;
    }
    else if (numBits <= 32U)
    {
        numBytes = 3U;
    }
    else
    {
        numBytes = (uint32_t) 0U;
    }
    return numBytes;
}

static uint32_t getNumDummyBytesFromBits(uint32_t numBits)
{
    uint32_t numBytes;
    if (numBits == 8U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
    }
    else if (numBits == 16U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS;
    }
    else if (numBits == 24U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS;
    }
    else
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS;
    }
    return numBytes;
}

uint32_t QSPI_GetDeviceId(void)
{
#if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
    uint32_t deviceId[3U];
    QSPI_GetDeviceIdExtended((uint32_t) 3, &deviceId[0U]);
    return ((uint32_t) ((deviceId[2U] << 16U) | deviceId[0U]));
#else
    uint32_t deviceId[2U];
    QSPI_GetDeviceIdExtended((uint32_t) 2, &deviceId[0U]);
    return ((uint32_t) ((deviceId[1U] << 16U) | deviceId[0U]));
#endif
}

int32_t QSPI_GetDeviceIdExtended(uint32_t numSpiWords, uint32_t *data)
{
    int32_t  retval;
    uint32_t deviceId[QSPI_READ_DEVICEID_MAX_WORDS] = {0};
    if (gQspiFlashDevInfo.idCmd.numDataWords > QSPI_READ_DEVICEID_MAX_WORDS)
    {
        gQspiFlashDevInfo.idCmd.numDataWords = QSPI_READ_DEVICEID_MAX_WORDS;
    }
    /* Always read full id command but return numWords */
    retval = QSPI_executeCmd(gQspiFlashDevInfo.idCmd, &deviceId[0]);
    if (numSpiWords > QSPI_READ_DEVICEID_MAX_WORDS)
    {
        numSpiWords = QSPI_READ_DEVICEID_MAX_WORDS;
    }
    /* Copy the number of data words passed as parameter */
    mem1cpy((void *) data, &deviceId[0], numSpiWords * 4U);
    return retval;
}

static void mem1cpy(void *dstAddr, uint32_t *srcAddr, uint32_t length)
{
    uint32_t  i;
    uint32_t *DAddr = (uint32_t *) (dstAddr);
    uint32_t *SAddr = (uint32_t *) (srcAddr);
    uint8_t  *DAddr_byte, *SAddr_byte;
    void     *DAddr_byteTmp, *SAddr_byteTmp;

    /*Do a word read*/
    for (i = 0U; i < (length / 4U); i++)
    {
        *DAddr = *SAddr;
        DAddr++;
        SAddr++;
    }

    /*Do a byte write*/
    if ((length % 4U) != 0U)
    {
        DAddr_byteTmp = (void *) DAddr;
        SAddr_byteTmp = (void *) SAddr;
        DAddr_byte    = (uint8_t *) DAddr_byteTmp;
        SAddr_byte    = (uint8_t *) SAddr_byteTmp;
        for (i = 0U; i < (length % 4U); ++i)
        {
            *DAddr_byte = *SAddr_byte;
            DAddr_byte++;
            SAddr_byte++;
        }
    }
}

/*_____________________________________________________________________________
 * FUNCTION:     QSPI_ReadSectors
 *
 * DESCRIPTION:  Reads one or several sectors from the QSPI Memory described
 *               in the Device Descriptor.
 *
 * PARAMETERS:   ipDeviceDesc
 *                   Device Descriptor
 *               ipReadDesc
 *                   Indicate where from and how many sectors to read
 *
 * RETURNS:      QSPI_FLASH_SUCCESS if the QSPI Device Sector(s) could be read
 *
 *____________________________________________________________________________*/
uint32_t QSPI_ReadSectors(void    *dstAddr,
                          uint32_t srcOffsetAddr,
                          uint32_t length)
{
    uint32_t address = SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr;

    /* Read from QSPI */
    mem1cpy(dstAddr, (uint32_t *) address, length);

    return QSPI_FLASH_SUCCESS;
}

void QSPI_ReadSectors_edma(void    *dstAddr,
                           uint32_t srcOffsetAddr,
                           uint32_t length,
                           uint32_t edma_ch_num)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          bCntValue = 1U;
    uint32_t          remBytes  = 0;
    uint32_t          aCntValue = length;
    uint32_t          addr      = (uint32_t) (dstAddr);
    uint32_t          max_acnt  = 0x7FF0U;
    if (length > max_acnt)
    {
        bCntValue = (length / max_acnt);
        remBytes  = (length % max_acnt);
        aCntValue = max_acnt;
    }

    /* Compute QSPI address and size */
    edmaParam.opt      = 0;
    edmaParam.srcAddr  = SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr;
    edmaParam.destAddr = addr;
    edmaParam.aCnt     = aCntValue;
    edmaParam.bCnt     = bCntValue;
    edmaParam.cCnt     = 1;
    edmaParam.srcBIdx  = aCntValue;
    edmaParam.destBIdx = aCntValue;
    edmaParam.srcCIdx  = 0;
    edmaParam.destCIdx = 0;
    edmaParam.linkAddr = 0xFFFF;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((edma_ch_num <<
           EDMA_TPCC_OPT_TCC_SHIFT) &
          EDMA_TPCC_OPT_TCC_MASK) | EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edma_ch_num, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edma_ch_num,
                        EDMA3_TRIG_MODE_MANUAL);

    while ((EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
            ((uint32_t) 1U << edma_ch_num)) == 0U)
    {
        /* Do Nothing - Misra fix */
    }
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edma_ch_num);
    if (remBytes != 0)
    {
        /* Compute QSPI address and size */
        edmaParam.opt     = 0;
        edmaParam.srcAddr =
            (SOC_QSPI_ADDRSP1_BASE +
             (bCntValue * max_acnt) + srcOffsetAddr);
        edmaParam.destAddr = (addr + (max_acnt * bCntValue));
        edmaParam.aCnt     = remBytes;
        edmaParam.bCnt     = 1;
        edmaParam.cCnt     = 1;
        edmaParam.srcBIdx  = remBytes;
        edmaParam.destBIdx = remBytes;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFF;
        edmaParam.opt     |=
            (EDMA_TPCC_OPT_TCINTEN_MASK |
             ((edma_ch_num << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edma_ch_num, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edma_ch_num,
                            EDMA3_TRIG_MODE_MANUAL);

        while ((EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                ((uint32_t) 1U << edma_ch_num)) == 0U)
        {
            /* Do Nothing - Misra fix */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edma_ch_num);
    }
}

/*_____________________________________________________________________________
 * FUNCTION:     QSPI_WriteSectors (not implemented)
 *
 * DESCRIPTION:  Writes one or several sectors to the QSPI Memory.
 *
 * PARAMETERS:   ipDeviceDesc
 *                   Device Descriptor
 *               ipWriteDesc
 *                   Indicate where to and how many sectors to write
 *
 * RETURNS:      QSPI_FLASH_FAIL/QSPI_FLASH_SUCCESS
 *
 *____________________________________________________________________________*/
/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 * Note: write in memory map mode is not supported by driver. This is because
 * Most of the flashes require write enable (WE) command to be sent before
 * sending the write command. This puts a restriction on mem mapped write that
 * after every word write, switch to cfg mode and send WE command.
 * This is in effecient and also the IP was not designed for the mem mapped
 * write operations.
 */
uint32_t QSPI_WriteSectorsNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                      uint32_t length)
{
    return QSPI_FLASH_FAIL;
}

uint32_t QSPI_WriteSectors(uint32_t dstOffsetAddr, uint32_t srcAddr,
                           uint32_t length)
{
    uint32_t retVal;
    retVal = QSPI_WriteSectorsNonBlocking(dstOffsetAddr, srcAddr, length);
    return retVal;
}

void QSPI_ReadCfgMode(uint32_t dstAddr, uint32_t srcOffsetAddr,
                      uint32_t length)
{
    gQspiFlashDevInfo.readCmd.numDataWords = length;
    gQspiFlashDevInfo.readCmd.addr         = srcOffsetAddr;
    QSPI_executeRdWrDataCmd(gQspiFlashDevInfo.readCmd, (uint32_t *) dstAddr);
    gQspiFlashDevInfo.readCmd.numDataWords = 0;
    gQspiFlashDevInfo.readCmd.addr         = 0;
    return;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_WriteCfgModeNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                  uint32_t length)
{
    gQspiFlashDevInfo.writeCmd.numDataWords = length;
    gQspiFlashDevInfo.writeCmd.addr         = dstOffsetAddr;
    QSPI_executeRdWrDataCmd(gQspiFlashDevInfo.writeCmd, (uint32_t *) srcAddr);
    gQspiFlashDevInfo.writeCmd.numDataWords = 0;
    gQspiFlashDevInfo.writeCmd.addr         = 0;
}

void QSPI_WriteCfgMode(uint32_t dstOffsetAddr, uint32_t srcAddr,
                       uint32_t length)
{
    QSPI_WriteCfgModeNonBlocking(dstOffsetAddr, srcAddr, length);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

uint32_t QSPI_FlashStatus(void)
{
    uint32_t data;
    QSPI_executeCmd(gQspiFlashDevInfo.flashStatusCmd, &data);
    return (data & 0xFFU);
}

void QSPI_WriteEnable(void)
{
    QSPI_executeCmd(gQspiFlashDevInfo.writeEnableCmd, NULL);
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_QuadEnableNonBlocking(void)
{
    uint32_t data, cmdInfo = 0U;
    uint32_t sr1, cr;
    QSPI_WriteEnable();
    /* Read Ststus register 1 */
    data = QSPI_CMD_RDSR;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, QSPI_CR_FLEN_2_WORDS);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &sr1, (int32_t) 1);
    /* Read Command Register */
    data = QSPI_CMD_RDCR;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, QSPI_CR_FLEN_2_WORDS);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &cr, (int32_t) 1);

    /* Set Configuration register 2nd bit to 1 for Quad enable */
    cr |= 0x2U;
    /* write CR register */
    data = ((uint32_t) QSPI_CMD_WRREG << 16U) | (sr1 << 8U) | cr;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, QSPI_CR_FLEN_1_WORD);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_24_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
}

void QSPI_QuadEnable(void)
{
    QSPI_QuadEnableNonBlocking();
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 * In some flashes (Ex: Spansion flashes used in TI EVMs) the sectors are
 * organized as a hybrid combination of 4-kB and 64-kB sectors, and when the
 * sub sector erase is executed on 64-kB sector the API returns with success
 * without erasing. Since this is flash dpecific driver will not check for this.
 * Application calling this API should make sure that this API is called only
 * for the supported sectors.
 */
void QSPI_FlashSubSectorEraseNonBlocking(uint32_t offsetAddr)
{
    gQspiFlashDevInfo.subSectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.subSectorEraseCmd.addr         = offsetAddr;
    QSPI_executeCmd(gQspiFlashDevInfo.subSectorEraseCmd, NULL);
    gQspiFlashDevInfo.subSectorEraseCmd.addr = 0;
}

void QSPI_FlashSubSectorErase(uint32_t offsetAddr)
{
    QSPI_FlashSubSectorEraseNonBlocking(offsetAddr);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashBlockEraseNonBlocking(uint32_t blkNo)
{
    gQspiFlashDevInfo.sectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.sectorEraseCmd.addr         = blkNo * QSPIFLASH_BLOCKSIZE;
    QSPI_executeCmd(gQspiFlashDevInfo.sectorEraseCmd, NULL);
    gQspiFlashDevInfo.sectorEraseCmd.addr = 0;
}

void QSPI_FlashBlockErase(uint32_t blkNo)
{
    QSPI_FlashBlockEraseNonBlocking(blkNo);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashFullEraseNonBlocking(void)
{
    QSPI_executeCmd(gQspiFlashDevInfo.fullEraseCmd, NULL);
}

void QSPI_FlashFullErase(void)
{
    QSPI_FlashFullEraseNonBlocking();
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

void QSPI_seek(uint32_t *srcAddr, uint32_t location)
{
    *srcAddr = location;
}

#if (QSPI_FLASH_RESET_AT_INIT == 1)
static void QSPI_ResetModule(void)
{
    /* QSPI module doesnot have module soft reset.
     * So disable and enable the clock to the module. */
    HW_WR_FIELD32(
        (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
        CM_L4PER2_QSPI_CLKCTRL_MODULEMODE,
        CM_L4PER2_QSPI_CLKCTRL_MODULEMODE_DISABLED);

    HW_WR_FIELD32(
        (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
        CM_L4PER2_QSPI_CLKCTRL_MODULEMODE,
        CM_L4PER2_QSPI_CLKCTRL_MODULEMODE_ENABLED);
}

#endif

void QSPI_ConfigFlashDevInfo(qspi_DeviceType_e          flashType,
                             const QSPI_FlashDevInfo_t *flashDevInfo)
{
    uint32_t memSetupInfo = 0U, devCtrlInfo = 0U;
    uint32_t numAddBytes, numDummyBytes, readType, numDummyBits;

    QSPI_SetDefaultFlashDevInfo(flashType, flashDevInfo);

    /*
     * Set Device Control register - clock polarity, phase, CS polarity and data
     * delay depending on silicon Revision
     */
    devCtrlInfo = QSPIgetDeviceControl(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CSP0,
                   QSPI_SPI_DC_REG_CSP_ACTIVE_LOW);

    HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_DD0,
                   gQspiFlashDevInfo.dataDelay);

    if (3U == gQspiFlashDevInfo.qspiMode)
    {
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKP0,
                       QSPI_SPI_DC_REG_CKP_DATA_ACTIVE);
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKPH0,
                       QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE);
    }
    else
    {
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKP0,
                       QSPI_SPI_DC_REG_CKP_DATA_INACTIVE);
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKPH0,
                       QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_FALLING_EDGE);
    }
    QSPIsetDeviceControl(SOC_QSPI_ADDRSP0_BASE, devCtrlInfo);

    /* Set Clock Control register */
    QSPI_SelClockFrequency(gQspiFlashDevInfo.qspifrequency);
    QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, gQspiFlashDevInfo.qspifrequency);

    /* Set Memory Map Setup registers */
    numAddBytes = getNumAddrBytesFromBits(
        gQspiFlashDevInfo.readCmd.numAddrBits);

    numDummyBytes = getNumDummyBytesFromBits(
        gQspiFlashDevInfo.readCmd.numAddrDummyBits);

    readType = getMemSetupReadType(
        gQspiFlashDevInfo.readCmd.dataType);

    if (numDummyBytes != QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS)
    {
        numDummyBits = 0;
    }
    else
    {
        numDummyBits = gQspiFlashDevInfo.readCmd.numAddrDummyBits;
    }

    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_RCMD,
                   gQspiFlashDevInfo.readCmd.cmd);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_NUM_A_BYTES, numAddBytes);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_NUM_D_BYTES,
                   numDummyBytes);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_READ_TYPE, readType);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_WCMD,
                   gQspiFlashDevInfo.writeCmd.cmd);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_NUM_D_BITS, numDummyBits);

    QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetupInfo,
                          gQspiFlashDevInfo.qspiCs);

    if (NULL != gQspiFlashDevInfo.qspiFlashInitFxn)
    {
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                            QSPI_MMR);
        gQspiFlashDevInfo.qspiFlashInitFxn(flashType);
    }
}

uint32_t QSPI_DeInitialize(void)
{
    gQspiCmdInitDone = 0;

    return QSPI_FLASH_SUCCESS;
}

static void QSPI_executeWriteCmd(QSPI_FlashCmd_t flashCmd)
{
    uint32_t frameLength = 0U, cmdInfo = 0U;

    if (flashCmd.numAddrBits != 0)
    {
        frameLength++;
    }
    if (flashCmd.numAddrDummyBits != 0)
    {
        frameLength++;
    }
    if (flashCmd.numDataWords != 0)
    {
        frameLength = frameLength + flashCmd.numDataWords;
    }

    /* Write Command */
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, frameLength);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WIRQ,
                   QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FIRQ,
                   QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                   (flashCmd.numCmdBits - 1U));
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CSNUM,
                   QSPI_SPI_CMD_REG_CSNUM_CS_0);

    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &flashCmd.cmd, (int32_t) 1);
    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
}

static void QSPI_executeWriteAddrBytesCmd(QSPI_FlashCmd_t flashCmd)
{
    uint32_t cmdInfo = 0U;

    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &flashCmd.addr, (int32_t) 1);
    cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                   (flashCmd.numAddrBits - 1U));

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
}

static void QSPI_executeWriteDummyBytesCmd(QSPI_FlashCmd_t flashCmd)
{
    uint32_t cmdInfo = 0U;
    uint32_t localData;

    localData = 0U;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &localData, (int32_t) 1);
    cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                   (flashCmd.numAddrDummyBits - 1U));

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
}

static void QSPI_executeWrite32BitDataCmd(QSPI_FlashCmd_t flashCmd,
                                          const uint32_t *data)
{
    uint32_t cmdInfo = 0U;
    uint32_t i;

    for (i = 0; i < flashCmd.numDataWords; i++)
    {
        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);
        cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                       flashCmd.dataType);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                       (flashCmd.numPerDataWordbits - 1U));

        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        data++;
    }
}

static void QSPI_executeRead32BitDataCmd(QSPI_FlashCmd_t flashCmd,
                                         uint32_t       *data)
{
    uint32_t cmdInfo = 0U;
    uint32_t i;

    for (i = 0; i < flashCmd.numDataWords; i++)
    {
        cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                       flashCmd.dataType);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                       (flashCmd.numPerDataWordbits - 1U));

        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        QSPIreadData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);
        data++;
    }
}

static void QSPI_executeWriteDataCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    uint32_t cmdInfo = 0U;
    uint32_t i;

    for (i = 0; i < flashCmd.numDataWords; i++)
    {
        if (flashCmd.numPerDataWordbits <= 32U)
        {
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE,
                          data,
                          (int32_t) 1);
            if (flashCmd.numPerDataWordbits == 8U)
            {
                data = (uint32_t *) ((uint8_t *) data + 1);
            }
            else if (flashCmd.numPerDataWordbits == 16U)
            {
                data = (uint32_t *) ((uint16_t *) data + 1);
            }
            else
            {
                data++;
            }
        }
        else
        {
            if (flashCmd.numPerDataWordbits == 128U)
            {
                QSPIwriteData(SOC_QSPI_ADDRSP0_BASE,
                              data,
                              (int32_t) 4);
                data = data + 4;
            }
            else
            {
                QSPIwriteData(SOC_QSPI_ADDRSP0_BASE,
                              data,
                              (int32_t) 2);
                data = data + 2;
            }
        }

        cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                       flashCmd.dataType);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                       (flashCmd.numPerDataWordbits - 1U));

        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
    }
}

static void QSPI_executeReadDataCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    uint32_t cmdInfo = 0U;
    uint32_t i;
    uint32_t localData;     /* Needed as QSPIreadData API always read 32-bit,
                               so it could corrupt user pointer if data width is
                               less than 32 and buffer allocated by user is
                               not multiple of 32-bit */

    for (i = 0; i < flashCmd.numDataWords; i++)
    {
        cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                       flashCmd.dataType);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                       (flashCmd.numPerDataWordbits - 1U));

        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

        if (flashCmd.numPerDataWordbits <= 32U)
        {
            QSPIreadData(SOC_QSPI_ADDRSP0_BASE,
                         &localData,
                         (int32_t) 1);
            if (flashCmd.numPerDataWordbits == 8U)
            {
                *((uint8_t *) data) = (uint8_t) localData;
                data = (uint32_t *) ((uint8_t *) data + 1);
            }
            else if (flashCmd.numPerDataWordbits == 16U)
            {
                *((uint16_t *) data) = (uint16_t) localData;
                data = (uint32_t *) ((uint16_t *) data + 1);
            }
            else
            {
                *data = localData;
                data++;
            }
        }
        else
        {
            if (flashCmd.numPerDataWordbits == 128U)
            {
                QSPIreadData(SOC_QSPI_ADDRSP0_BASE,
                             data,
                             (int32_t) 4);
                data = data + 4;
            }
            else
            {
                QSPIreadData(SOC_QSPI_ADDRSP0_BASE,
                             data,
                             (int32_t) 2);
                data = data + 2;
            }
        }
    }
}

int32_t QSPI_executeRdWrDataCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    int32_t retVal = STW_SOK;

    if ((flashCmd.numDataWords != 0) && (NULL == data))
    {
        retVal = STW_EBADARGS;
    }
    if (retVal == STW_SOK)
    {
        /* Write Command */
        QSPI_executeWriteCmd(flashCmd);

        /* Write Address Bytes */
        if (flashCmd.numAddrBits != 0)
        {
            QSPI_executeWriteAddrBytesCmd(flashCmd);
        }

        /* Write dummy Bytes */
        if (flashCmd.numAddrDummyBits != 0)
        {
            QSPI_executeWriteDummyBytesCmd(flashCmd);
        }
        /* Read or Write data */
        if (flashCmd.numDataWords != 0)
        {
            if (flashCmd.dataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE)
            {
                QSPI_executeWriteDataCmd(flashCmd, data);
            }
            else
            {
                QSPI_executeReadDataCmd(flashCmd, data);
            }
        }
    }
    return retVal;
}

