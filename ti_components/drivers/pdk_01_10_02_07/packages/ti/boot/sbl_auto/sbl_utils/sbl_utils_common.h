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
 *  \defgroup SBL_COMMON_UTILS SBL Common Utilities
 *
 *  @{
 */
/**
 *  \file     sbl_utils_common.h
 *
 *  \brief    This file contains the SBL Utility layer common for all platforms.
 *            This also contains some related macros, structures and enums.
 */

#ifndef SBL_UTILS_COMMON_H_
#define SBL_UTILS_COMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/pmhal.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro contains the base address of NOR memory.
 */
#define SBL_UTILS_NOR_BASE                             ((uint32_t) 0x08000000U)

/**
 * \brief  This macro contains the offset at which App Image is present in
 *         NOR memory.
 */
#define SBL_UTILS_APP_IMAGE_OFFSET_NOR                 ((uint32_t) 0x00080000U)

/**
 * \brief  This macro contains the offset at which App Image is present in
 *         QSPI flash.
 */
#define SBL_UTILS_APP_IMAGE_OFFSET_QSPI                ((uint32_t) 0x00080000U)

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define SBL_UTILS_I2C_SYSTEM_CLOCK       ((uint32_t) 96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define SBL_UTILS_I2C_INTERNAL_CLOCK     ((uint32_t) 9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define SBL_UTILS_I2C_OUTPUT_CLOCK       ((uint32_t) 400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define SBL_UTILS_I2C_TIMEOUT_COUNT      ((uint32_t) 4000U)

/** Write Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_WRITE              ((uint32_t) 1U)

/** Read Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_READ               ((uint32_t) 2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief This structure defines the Power Domain's configuration for
 *         configuring state of Power domain
 */
typedef struct sblutilsPowerDomainStateConfig
{
    uint32_t    domainId;
    /**< Power Domain Id, refer to enum pmhalPrcmPdId_t for values */
    uint32_t    powerDomainState;
    /**< State for which power domain should be configured,
     *   refer to enum pmhalPrcmPdState_t for values
     */
    const char *powerDomainName;
    /**< Power domain name */
} sblutilsPowerDomainStateConfig_t;

/**
 *  \brief This structure defines the Clock Domain's configuration for
 *         configuring state of clock domain
 */
typedef struct sblutilsClockDomainStateConfig
{
    int32_t     domainId;
    /**< Clock Domain Id, refer to enum pmhalPrcmCdId_t for values */
    uint32_t    clockDomainState;
    /**< State for which clock domain should be configured,
     *   refer to enum pmhalPrcmCdClkTrnModes_t for values
     */
    const char *clockDomainName;
    /**< Clock domain name */
} sblutilsClockDomainStateConfig_t;

/**
 *  \brief This structure defines the Module's configuration for enabling
 *         Module mode.
 */
typedef struct sblutilsModuleEnableConfig
{
    uint32_t    moduleId;
    /**< Module Id, refer to enum pmhalPrcmModuleId_t for values */
    uint32_t    moduleEnableMode;
    /**< Mode in which module should be configured,
     *   refer to enum pmhalPrcmModuleSModuleMode_t for values
     */
    const char *moduleName;
    /**< Module name */
} sblutilsModuleEnableConfig_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function parses and copies the App Image from QSPI flash
 *          in QSPI boot mode.
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \return  status       Whether image is parsed and copied correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLUtilsQspiBootRprc(sbllibAppImageParseParams_t *imageParams);

/**
 * \brief   This function copies data from QSPI flash. It uses EDMA for complete
 *          transfer.
 *
 * \param   dstAddr       Destination Address
 * \param   srcOffsetAddr QSPI Source Offset Address
 * \param   length        The length of data block to be copied.
 *
 * \return  status        Whether copy is done successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t SBLUtilsQspiReadSectors(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length);

/**
 * \brief   This function parses and copies the App Image from MMCSD card
 *          in QSPI_SD boot mode.
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \return  status       Whether image is parsed and copied correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLUtilsQspiSDBootRprc(sbllibAppImageParseParams_t *imageParams);

/**
 * \brief   This function parses and copies the App Image from MMCSD card
 *          in SD boot mode.
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \return  status       Whether image is parsed and copied correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLUtilsSDBootRprc(sbllibAppImageParseParams_t *imageParams);

/**
 * \brief   This function copies data from MMCSD card. It uses EDMA when data
 *          to be read is more than 512 bytes.
 *
 * \param   dstbuff      Destination Buffer Address
 * \param   srcFileAddr  Source File Address
 * \param   numBytes     The number of bytes of data to be read.
 *
 * \return  status       Whether copy is done successfully.
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 *
 * \note    This API does not use the source file pointer parameter. It is a
 *          dummy added to maintain compatibility with Read Function prototype.
 */
int32_t SBLUtilsSDFileRead(void    *dstbuff,
                           uint32_t srcFileAddr,
                           uint32_t numBytes);

/**
 * \brief   This function moves the file read head by n bytes.
 *
 * \param   filePtr     File read pointer
 * \param   numBytes    Number of bytes of data by which read head is moved.
 *
 * \return  None
 *
 * \note    This API does not use the source file pointer parameter. It is a
 *          dummy added to maintain compatibility with Read Function prototype.
 */
void SBLUtilsSDFileSeek(uint32_t *filePtr, uint32_t numBytes);

/**
 * \brief   This function parses and copies the App Image from NOR memory in
 *          NOR boot mode.
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \return  status       Whether image is parsed and copied correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLUtilsNorBootRprc(sbllibAppImageParseParams_t *imageParams);

/**
 * \brief   This function copies data from NOR memory. It uses EDMA for complete
 *          transfer.
 *
 * \param   dstAddr       Destination Address
 * \param   srcOffsetAddr NOR Source Offset Address
 * \param   length        The length of data block to be copied.
 *
 * \return  status        Whether copy is done successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t SBLUtilsNorRead(void    *dstAddr,
                        uint32_t srcOffsetAddr,
                        uint32_t length);

/**
 * \brief   This function moves the read head by n bytes.
 *
 * \param   srcAddr     Read head pointer.
 * \param   numBytes    Number of bytes of data by which read head is moved.
 *
 * \return  None
 */
void SBLUtilsNorFileSeek(uint32_t *srcAddr, uint32_t numBytes);

/**
 * \brief   This API triggers an EDMA transfer from source address to
 *          destination address.
 *
 * \param   srcAddr         Source Address.
 * \param   destAddr        Destination Address.
 * \param   dataSize        Size of the data that needs to be copied.
 * \param   edmaChannelNum  EDMA Channel Number.
 * \param   edmaTccNum      EDMA TCC Number.
 * \param   edmaEvtqNum     EDMA Event Queue Number.
 * \param   paramSetNum     EDMA Param Set Number.
 *
 * \return  None.
 */
void SBLUtilsTriggerEDMAPolledMode(uint32_t srcAddr,
                                   uint32_t destAddr,
                                   uint32_t dataSize,
                                   uint32_t edmaChannelNum,
                                   uint32_t edmaTccNum,
                                   uint32_t edmaEvtqNum,
                                   uint32_t paramSetNum);

/**
 * \brief   This is the wrapper function for configuring Power domains.
 *
 * \return  None
 */
int32_t SBLUtilsConfigPowerDomains(void);

/**
 * \brief   This is the wrapper function for configuring DPLL. This function
 *          is implemented such that the error messages are printed on
 *          UART Console in case DPLL is not configured correctly.
 *
 * \param   oppId   The OPP for which the DPLLs should be configured.
 *
 * \return  None
 */
void SBLUtilsConfigMultiOppDpll(uint32_t oppId);

/**
 * \brief   This is the wrapper function for configuring DPLL. This function
 *          configures the DPLLs which usually donot support multiple OPPs.
 *          This function is implemented such that the error messages are
 *          printed on UART Console in case DPLL is not configured correctly.
 *
 * \return  None
 */
void SBLUtilsConfigSingleOppDpll(void);

/**
 * \brief   This is the wrapper function for configuring clock domains. This
 *          function is implemented such that the error messages are printed on
 *          UART Console in case Clock Domain is not configured correctly.
 *
 * \return  None
 */
void SBLUtilsConfigClockDomains(void);

/**
 * \brief   This is the wrapper function for enabling modules. This function
 *          is implemented such that the error messages are printed on
 *          UART Console in case modules are not enabled correctly.
 *
 * \return  None
 */
void SBLUtilsConfigModules(void);

/**
 * \brief   This is a wrapper function for configuring the AVS of Voltage
 *          rails of the device. This function returns the error status based
 *          on whether the voltage rails are configured correctly.
 *
 * \param   oppId   The OPP for which the voltage should be set for the
 *                  voltage rails.
 *
 * \return  PM_SUCCESS if opp is proper and voltage can be configured
 *          PM_FAIL/PM_TIMEOUT/PM_BADARGS otherwise.
 */
int32_t SBLUtilsConfigAllVoltageRails(uint32_t oppId);

/**
 * \brief   This function reads the 32K Timer value. This API is used to
 *          measure SBL boot time.
 *
 * \return  timerVal            Current Value of the 32K Counter
 */
uint32_t SBLUtilsRead32KTimer(void);

/**
 * \brief   This function initializes the UART terminal for the given instance.
 *
 * \param   uartInstance     Instance for which UART should be initialized.
 *                           Refer enum UART_INST_t for details.
 *
 * \return  status           Whether UART is initialized correctly
 *                           STW_SOK   : Success
 *                           STW_EFAIL : Failure
 *
 * \note    This API currently supports only UART3 instance.
 */
int32_t SBLUtilsPrintfInit(UART_INST_t uartInstance);

/**
 * \brief   This function does the PRCM configuration for given UART instance.
 *
 * \param   uartInstance     Instance for which PRCM should be configured.
 *                           Refer enum UART_INST_t for details.
 *
 * \return  status           Whether UART PRCM is done correctly
 *                           STW_SOK   : Success
 *                           STW_EFAIL : Failure
 *
 * \note    This API currently supports only UART3 instance.
 */
int32_t SBLUtilsUartPrcm(UART_INST_t uartInstance);

/**
 * \brief   This function copies data from DDR memory using EDMA.
 *
 * \param   dstAddr   Destination Address
 * \param   srcAddr   DDR Source Address
 * \param   length    The length of data block to be copied.
 *
 * \return  status    Whether data is copied correctly
 *                    STW_SOK   : Success
 *                    STW_EFAIL : Failure
 */
int32_t SBLUtilsDDRReadEdma(void    *dstAddr,
                            uint32_t srcAddr,
                            uint32_t length);

/**
 * \brief   This function gets the DDR address where App Image is copied before
 *          parsing. This might differ depending on the silicon package type.
 *
 * \return  ddrAddress     Address where app image should be copied
 */
uint32_t SBLUtilsGetDDRAppCopyAddress(void);

/**
 * \brief   This function configures and enables the EMIF ECC using parameters
 *          from SBL config file.
 *
 * \return  status       ECC enable status.
 *                       STW_SOK   : ECC enabled successfully
 *                       STW_EFAIL : Failed to enable ECC
 */
int32_t SBLUtilsEmifECCConfigure(void);

/**
 * \brief   This function pre-fills the ECC memory with the known pattern
 *          present at source address.
 *
 * \param   eccMemStartAddr Start address of memory for which ECC is enabled
 * \param   srcBuffAddr     Address of the source buffer
 * \param   memSize         Size of the memory
 *
 * \return  None
 *
 * \note    This API does not initialize and de-initialize the EDMA. This
 *          should be taken care by caller. Also the srcBuffer size should be
 *          equal to EDMA ACount value used in this API's implementation which
 *          is 128 bytes currently.
 */
void SBLUtilsPreFillECCMemory(const void *eccMemStartAddr,
                              const void *srcBuffAddr,
                              uint32_t    memSize);

/**
 * \brief   This function initializes the DSP L2 RAM to zero.
 *
 * \param   dspCoreId       DSP Core Id.
 *                          SBLLIB_CORE_ID_DSP1: DSP1
 *                          SBLLIB_CORE_ID_DSP2: DSP2
 *
 * \return  None.
 */
void SBLUtilsInitDspL2RAM(uint32_t dspCoreId);

#ifdef __cplusplus
}

#endif

#endif
/* @} */

