/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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
 */

/*
 *  \file   platform.h
 *
 *  \brief  platform API declarations.
 *
 *   This file contains the API prototypes for platform specific functions
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/csl/soc.h>
#include <stdint.h>

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
#define MMCSD_BASE                       (SOC_MMC1_BASE)

/*HSMMCSD DMA EVENT SOURCE NUMBER*/
#define EDMA_DREQ_MMC1_TX (60U)
#define EDMA_DREQ_MMC1_RX (61U)
#define EDMA_DREQ_MMC2_TX (46U)
#define EDMA_DREQ_MMC2_RX (47U)
#define EDMA_DREQ_MMC3_TX (76U)
#define EDMA_DREQ_MMC3_RX (77U)
#define EDMA_DREQ_MMC4_TX (56U)
#define EDMA_DREQ_MMC4_RX (57U)
#endif

#if defined (SOC_TDA3XX)
#define MMCSD_BASE                       (SOC_MMC4_BASE)

/*HSMMCSD DMA EVENT SOURCE NUMBER*/
#define EDMA_DREQ_MMC4_TX (60U)
#define EDMA_DREQ_MMC4_RX (61U)
#endif

#define MMCSD_DMA_BASE                   (SOC_EDMA_TC0_BASE)

/* Todo : please cross check before use */
#define MMCSD_IN_FREQ                    (96000000) /* 96MHz */
#define MMCSD_INIT_FREQ                  (400000)   /* 400kHz */

#define MMCSD_BLK_SIZE                   (512)
#define MMCSD_OCR                        (SD_OCR_VDD_3P0_3P1 | \
                                          SD_OCR_VDD_3P1_3P2)

/*Selected EDMA CH for HSMMCSD RX Event*/
#define EDMA_MMCSD_CH   (61U)

/*SBL MAGIC STRING PATTERN*/
#define SBL_REGRESSION_MAGIC_STRING_P1 (0xAAAA5555U)
#define SBL_REGRESSION_MAGIC_STRING_P2 (0x55335533U)
#define SBL_REGRESSION_MAGIC_STRING_P3 (0xBBFFBBFFU)
#define SBL_REGRESSION_MAGIC_STRING_P4 (0x11001100U)

/*DV - DIE ID Registers*/
#define DV_DIE_ID0  (0x4ae0c200)
#define DV_DIE_ID1  (0x4ae0c208)
#define DV_DIE_ID2  (0x4ae0c20C)
#define DV_DIE_ID3  (0x4ae0c210)

/* Todo : please cross check before use */
/*Pad config constant values */
#define PULLUDENABLE_ENABLE         (0U)
#define PULLUDENABLE_DISABLE        (1U)
#define PULLTYPESELECT_PULL_UP      (1U)
#define PULLTYPESELECT_PULL_DOWN    (0U)
#define INPUTENABLE_ENABLE          (1U)
#define INPUTENABLE_DISABLE         (0U)
#define SLEWCONTROL_FAST_SLEW       (0U)
#define SLEWCONTROL_SLOW_SLEW       (1U)
#define WAKEUPENABLE_ENABLE         (1U)
#define WAKEUPENABLE_DISABLE        (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*Data type to define the pad configuration*/
typedef struct {
    uint32_t pin_num;
    uint8_t  muxmode;
    uint8_t  pullud_enable;
    uint8_t  pull_typeselect;
    uint8_t  input_enable;
    uint8_t  slewcontrol;
    uint8_t  wakeup_enable;
}pad_config_t;

/* ============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */

/*Regression Test static table*/

/*-------------------------------
 * Test Result
 * -------------------------------
 * SBL Regression Test Magic string
 * -------------------------------
 * Test number track register
 * -------------------------------*/
typedef struct
{
    uint32_t sbl_regression_tc_result_reg;
    uint32_t sbl_regression_tc_pass_reg;
    uint32_t sbl_regression_magic_string_r1;
    uint32_t sbl_regression_magic_string_r2;
    uint32_t sbl_regression_magic_string_r3;
    uint32_t sbl_regression_magic_string_r4;
    uint32_t sbl_regression_tc_track_reg;
    uint32_t sbl_regression_tc_fail_reg;
}sbl_regression_log_bfr_t;

typedef enum
{
    REGRESSIONTEST_PASS         = 0x50415353,
    REGRESSIONTEST_FAIL         = 0x4641494C,
    REGRESSIONTEST_TIMEOUT      = 0x50415858,
    REGRESSIONTEST_LASTTESTCASE = 0x4C415354
}regressiontest_result_t;

/**
 * \brief  Enum to select the Silicon Package Type of SoC.
 */
typedef enum platformSiliconPackageType
{
    PLATFORM_SILICON_PACKAGE_TYPE_UNKNOWN = 0,
    /**< Silicon Package type is Invalid */
    PLATFORM_SILICON_PACKAGE_TYPE_12X12 = 1,
    /**< Silicon Package type is 12x12 */
    PLATFORM_SILICON_PACKAGE_TYPE_15X15 = 2,
    /**< Silicon Package type is 15x15 */
    PLATFORM_SILICON_PACKAGE_TYPE_17X17 = 3,
    /**< Silicon Package type is 17x17 */
    PLATFORM_SILICON_PACKAGE_TYPE_23X23 = 4
                                          /**< Silicon Package type is 23x23 */
} platformSiliconPackageType_t;

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/
extern sbl_regression_log_bfr_t sbl_regression_log_bfr;

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/

void PlatformI2C1SetPinMux(void);
void PlatformI2C4SetPinMux(void);

void PlatformGPIOClockEnable(void);
void PlatformGPMCClockEnable(void);
void PlatformGPMCPinCtrl(void);
void PlatformGPMCSetPinMux(void);

void PlatformMCSPI1PrcmEnable(void);
void PlatformMCSPI1SetPinMux(void);
void PlatformMCSPI2PrcmEnable(void);
void PlatformMCSPI2SetPinMux(void);
void PlatformMCSPI3SetPinMux(void);
void PlatformMCSPI4SetPinMux(void);
void PlatformMCASP3SetPinMux(void);
void PlatformMCASP3PrcmEnable(void);
void PlatformEDMAWkupDepEnable(void);

#ifdef REGRESSION_MODE
void regressiontest_log_result(regressiontest_result_t arg);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
void PlatformPCIESS1ClockEnable(void);

void PlatformPCIESS1PllConfig(void);

void PlatformPCIESS1Reset(void);

void PlatformPCIESS1CtrlConfig(void);

void PlatformPCIESS1PhyConfig(void);
#endif

#if defined (SOC_TDA2PX)
void PlatformDCAN1PadConfig(void);
#endif

uint32_t PlatformGetSiliconRev(void);

uint32_t PlatformGetFtRev(void);

int32_t PlatformUARTSetPinMux(UART_INST_t num);
void PlatformQSPISetPinMux(void);
void PlatformUnlockMMR(void);
void PlatformLockMMR(void);
void PlatformMMC1SetPinMux(void);
void PlatformGPMCSetPinMuxAddrLines(void);
void PlatformI2C2SetPinMux(void);
void PlatformVIN1SetPinMux(void);
void PlatformVIN2SetPinMux(void);
void PlatformLCDSetPinMux(void);
void PlatformRGMIISetPinMux(void);
void PlatformRGMII0SetPinMux(void);
void PlatformRGMII1SetPinMux(void);
void PlatformUART1SetPinMux(void);
void PlatformUART3SetPinMux(void);
void PlatformUART4SetPinMux(void);
void PlatformMMCSD1SetPinMux(void);
void PlatformMMCSD3SetPinMux(void);
void PlatformMMCSD4SetPinMux(void);
int32_t PlatformMMCSDSetPinMux(MMC_INST_t num);
void PlatformUART2SetPinMux(void);
void PlatformUartConsoleSetPinMux(void);
void PlatformGPIOInputOutputSetPinMux(void);
void PlatformGPIO1SetPinMux(void);
void PlatformGPIO4SetPinMux(void);
uint32_t PlatformGetQspiMode(void);
void PlatformDCAN1PrcmEnable(void);
void PlatformDCAN2PrcmEnable(void);
void PlatformDcanMessageRamInit(uint32_t instance);
void PlatformDCAN2SetPinMux(void);
void PlatformMCANSetPinMux(void);
void PlatformDCAN1SetPinMux(void);
void PlatformUnlockControlIODSS(void);
void PlatformI2C3SetPinMux(void);
void PlatformI2C5PrcmEnable(void);
void PlatformI2C5SetPinMux(void);
void PlatformTDA2xxMCSetPinMux(void);
void PlatformMMCSD2SetPinMux(void);
void PlatformDCAN1RXSetPinMux(void);
void PlatformDCAN2RXSetPinMux(void);
int32_t PlatformDcanClkConfig(uint32_t instance);

/**
 * \brief   This function gets the silicon package type of the SoC.
 *
 * \param   None
 *
 * \return  packageType   Refer enum #platformSiliconPackageType_t for details.
 */
uint32_t PlatformGetSiliconPackageType(void);

#if defined (SOC_TDA3XX)
/**
 * \brief   This function read/returns the RC Oscillator Frequency.
 *
 * \param   freqHz   RC Oscillator Frequency in Hertz. This will be updated only
 *                   if TDA3xx Silicon Revision is 2.0 and above
 *
 * \return  status   Return status of the API.
 *                   Return TRUE if successful i.e. for SR2.0 and above
 *                   Otherwise returns FALSE.
 * \note    This API return RC Oscillator frequency only for SR2.0 and above.
  */
int32_t PlatformGetRCOscFreq(uint32_t *freqHz);

void PlatformClkOut2SetPinMux(void);
#endif
/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */
void UART_PAD_CONFIG(void);
void cntrl_core_qspi_pad_config(void);
void HAL_CTRL_UnlockMMR(void);
void I2C1_Pin_Mux(void);
void I2C2_Pin_Mux(void);
void I2C4_Pin_Mux(void);
uint32_t CTRLGetFtRev(void);
uint32_t CTRLGetSiliconRev(void);
void EDMAModuleClkConfig(void);
void GPMC_clock_enable(void);
void GPIO_clock_enable(void);
void MCSPI1_pad_mux_config(void);
void GPMC_pin_Ctrl(void);
void cntrl_core_gpmc_pad_config(void);
void cntrl_core_mmc1_pad_config(void);
void cntrl_core_gpmc_pad_config_addr_lines(void);
void cntrl_core_i2c2_pad_config(void);
void cntrl_core_vin1_pad_config(void);
void cntrl_core_vin2_pad_config(void);
void cntrl_core_lcd_pad_config(void);
void cntrl_core_rgmii_pad_config(void);
void cntrl_core_uart1_pad_config(void);
int32_t Uart_Pin_Mux(UART_INST_t num);
void Uart1_Pin_Mux(void);
void Uart3_Pin_Mux(void);
void Uart4_Pin_Mux(void);
void MMCSD1_Pin_Mux(void);
void MMCSD3_Pin_Mux(void);
void MMCSD4_Pin_Mux(void);
int32_t MMCSD_Pin_Mux(MMC_INST_t num);
void MCASP3_pad_mux_config(void);
void MCSPI2_pad_mux_config(void);
void MCSPI1_prcm_enable(void);
void MCSPI2_prcm_enable(void);
void PlatformGPMCConfig(void);
void GPMC_config(void);
void PCIESS1ClockEnable(void);
void PCIESS1PllConfig(void);
void PCIESS1Reset(void);
void PCIESS1CtrlConfig(void);
void MCASP3_prcm_enable(void);
void PlatformMCASP1SetPinMux(void);
void PlatformMCASP1PrcmEnable(void);
void HAL_CTRL_Control_IO_DSS(void);
void HAL_CTRL_ConfigurePadsQspi(void);
void PCIESS1PhyConfig(void);

#ifdef __cplusplus
}
#endif
#endif
