/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file utils_pinmux.c
 *
 *  \brief Cascade Radar sample application pin mux configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CascadeRadar_main.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CascadeRadar_InitPadMuxAR12 (void)
{
    /* GPIO2_2_AWR1_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A12,     /* gpio2_2 */
                            0x8);
    /* GPIO2_9_AWR2_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A19,     /* gpio2_9 */
                            0x8);
    /* GPIO2_10_AWR3_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A20,     /* gpio2_10 */
                            0x8);
    /* GPIO2_11_AWR4_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A21,    /* gpio2_11 */
                            0x8);
    /* GPIO2_12_AWR_WARM_RST */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A22,     /* gpio2_12 */
                            0x8);
    /* GPIO2_13_AWR_SOP2 */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A23,     /* 0x18 - gpio2_13 */
                            0x8);
    /* GPIO2_22_AWR_SOP0 */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_CLK,     /* gpio2_22 */
                            0x8);
    /* GPIO2_25_AWR_SOP1 */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_WEN,     /* gpio2_25 */
                            0x8);
    /* GPIO7_24_AWR1_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART1_CTSN,   /* gpio7_24 */
                            0xC);
    /* GPIO5_10_AWR2_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,     /* SPI Int */
                            0xC);
    /* GPIO5_11_AWR3_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,     /* SPI Int */
                            0xC);
    /* GPIO7_25_AWR4_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART1_RTSN,   /* gpio7_25 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_DAT2,     /* SPI3 */
                            0x6);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_DAT0,     /* SPI3 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_DAT1,     /* SPI3 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_CMD,     /* SPI3 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_CS0,     /* SPI1 */
                            0x6);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_CS1,     /* SPI1 */
                            0x6);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_SCLK,     /* SPI1 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_D0,     /* SPI1 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_D1,     /* SPI1 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART2_CTSN,   /* TDA_GPIO1_16_UART3_SELECTA */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART2_RTSN,   /* TDA_GPIO1_17_UART3_SELECTB */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_UART3_RXD,   /* UART3_RXD */
                            0xE);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_UART3_TXD,   /* UART3_TXD */
                            0xE);

    if (Bsp_boardGetBaseBoardRev() >= BSP_BOARD_REV_E)
    {
        /* SPI2_AWR2_CS0N */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_CS0,    /* SPI2 */
                                0x6);
        /* SPI2_AWR2_SCLK */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,   /* SPI2 */
                                0xC);
        /* SPI2_AWR2_MOSI */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_D0,     /* SPI2 */
                                0xC);
        /* SPI2_AWR2_MISO */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_D1,     /* SPI2 */
                                0xC);
        /* SPI4_AWR4_CS0N */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT7,     /* SPI4 */
                                0x6);
        /* SPI4_AWR4_SCLK */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT4,     /* SPI4 */
                                0xC);
        /* SPI4_AWR4_MOSI */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT5,     /* SPI4 */
                                0xC);
        /* SPI4_AWR4_MISO */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT6,     /* SPI4 */
                                0xC);
    }
    else
    {
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT3,     /* SPI3 */
                                0x6);
    }
}

void CascadeRadar_InitPadMuxVip (void)
{
    /* Need to re-config Pin for the UART1_RTSN as this is over written by the
     * BSP App Utils.
     */
    pad_config_t gpio_pad_config[] = {
        {CTRL_CORE_PAD_UART1_RTSN,     /* gpio7_25 */
          0xE,
          PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
          SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE}
    };
    /* Re-configure the gpio pad */
    configure_pad(gpio_pad_config, sizeof (gpio_pad_config) /
              sizeof (gpio_pad_config[0]));

    /* VIN1A */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_DE0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                               (UInt32) CTRL_CORE_PAD_VIN1A_VSYNC0,
                               BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #ifndef CASCADE_RADAR_VIP_ONLY_TEST
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #else
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D12,
                              0);
    #endif
    /* VIP2A */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_DE0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #ifndef CASCADE_RADAR_VIP_ONLY_TEST
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #else
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                              0);
    #endif
    /* VIN3A */
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_CS3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_A10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_A9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #ifndef CASCADE_RADAR_VIP_ONLY_TEST
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #else
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD12,
                              0);
    #endif
    /* VIN4A */
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_GPIO6_15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_ACLKR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_FSR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #ifndef CASCADE_RADAR_VIP_ONLY_TEST
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_ACLKR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_FSR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    #else
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                              0);
    #endif
}
