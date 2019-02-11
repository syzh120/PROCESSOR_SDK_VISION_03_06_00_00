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

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

#define MMCSD_BASE               (SOC_MMCHS_1_REGS)
#define MMCSD_DMA_BASE           (SOC_EDMA30TC_0_REGS)

#define MMCSD_IN_FREQ            96000000 /* 96MHz */
#define MMCSD_INIT_FREQ          400000   /* 400kHz */

#define MMCSD_BLK_SIZE           512
#define MMCSD_OCR                (SD_OCR_VDD_3P0_3P1 | SD_OCR_VDD_3P1_3P2)

/*HSMMCSD0 DMA EVENT SOURCE NUMBER*/
#define EDMA_DREQ_MMC1_TX (24U)
#define EDMA_DREQ_MMC1_RX (25U)

/*Selected EDMA CH for HSMMCSD RX Event*/
#define EDMA_MMCSD_CH (25U)

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/
void PlatformMCASP2SetPinMux(void);
void PlatformMCASP5SetPinMux(void);
void PlatformMCASP2PrcmEnable(void);
void PlatformMCSPI0SetPinMux(void);
void PlatformMCSPI1SetPinMux(void);
void PlatformEDMAPrcmEnable(void);
void PlatformUARTClockEnable(void);
void PlatformUARTSetPinMux(void);
void PlatformI2CClockEnable(void);
void PlatformI2CSetPinMux(void);
void PlatformXBARIntMux(uint32_t xbarIntNum, uint32_t XBARNum);
void PlatformGPMCPinCtrl(void);
void PlatformGPIOClockEnable(void);
void PlatformGPMCClockEnable(void);
void PlatformMCSPI0PrcmEnable(void);
void PlatformMCSPI1PrcmEnable(void);
void PlatformUartConsoleSetPinMux(void);

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */
void GPMCClockEnable(void);
void GPIO_clock_enable(void);
void MCASP2_pad_mux_config(void);
void MCASP5_pad_mux_config(void);
void MCSPI0_pad_mux_config(void);
void MCSPI1_pad_mux_config(void);
void MCASP2_prcm_enable(void);
void MCASP_3_4_5_prcm_enable(void);
void MCSPI0_1_2_3_prcm_enable(void);
void EDMA_prcm_enable(void);
void UART_clock_enable(void);
void UART_pad_mux_config(void);
void I2C_pad_mux_config(void);
void I2C_clock_enable(void);
void XBAR_Int_Mux(uint32_t xbarIntNum, uint32_t XBARNum);
void GPMC_pin_Ctrl(void);
void GPMC_clock_enable(void);

#ifdef __cplusplus
}
#endif
#endif

