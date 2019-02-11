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

/**
 *   Component:       staterware
 *
 *   Filename:          platform_tda3xx_pad_config.c
 *
 *   Description:       This file has generic function to configure pad
 *
 *   Author:                vinothr
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <platformPriv.h>

/* ============================================================================
 * FUNCTIONS
 * =============================================================================
 */

void PlatformGPMCSetPinMux(void)
{
    /* Arrary define the PAD properties of GPMC pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t gpmc_pad_config[] = {
        /*GPMC Data lines AD0-AD15*/
        {CTRL_CORE_PAD_IO_GPMC_AD0,
         CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_GPMC_AD0_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD1,
         CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_GPMC_AD1_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD2,
         CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_GPMC_AD2_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD3,
         CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_GPMC_AD3_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD4,
         CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_GPMC_AD4_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD5,
         CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_GPMC_AD5_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD6,
         CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_GPMC_AD6_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD7,
         CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_GPMC_AD7_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD8,
         CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_GPMC_AD8_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD9,
         CTRL_CORE_PAD_IO_GPMC_AD9_MUXMODE_GPMC_AD9_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD10,
         CTRL_CORE_PAD_IO_GPMC_AD10_MUXMODE_GPMC_AD10_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD11,
         CTRL_CORE_PAD_IO_GPMC_AD11_MUXMODE_GPMC_AD11_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD12,
         CTRL_CORE_PAD_IO_GPMC_AD12_MUXMODE_GPMC_AD12_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD13,
         CTRL_CORE_PAD_IO_GPMC_AD13_MUXMODE_GPMC_AD13_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD14,
         CTRL_CORE_PAD_IO_GPMC_AD14_MUXMODE_GPMC_AD14_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_AD15,
         CTRL_CORE_PAD_IO_GPMC_AD15_MUXMODE_GPMC_AD15_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},

        /*GPMC Add lines A0-A27*/
        {CTRL_CORE_PAD_IO_VOUT1_D16,
         CTRL_CORE_PAD_IO_VOUT1_D16_MUXMODE_GPMC_A0_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D17,
         CTRL_CORE_PAD_IO_VOUT1_D17_MUXMODE_GPMC_A1_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D18,
         CTRL_CORE_PAD_IO_VOUT1_D18_MUXMODE_GPMC_A2_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D19,
         CTRL_CORE_PAD_IO_VOUT1_D19_MUXMODE_GPMC_A3_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D20,
         CTRL_CORE_PAD_IO_VOUT1_D20_MUXMODE_GPMC_A4_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D21,
         CTRL_CORE_PAD_IO_VOUT1_D21_MUXMODE_GPMC_A5_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D22,
         CTRL_CORE_PAD_IO_VOUT1_D22_MUXMODE_GPMC_A6_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D23,
         CTRL_CORE_PAD_IO_VOUT1_D23_MUXMODE_GPMC_A7_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D8,
         CTRL_CORE_PAD_IO_VIN1A_D8_MUXMODE_GPMC_A8_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D9,
         CTRL_CORE_PAD_IO_VIN1A_D9_MUXMODE_GPMC_A9_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D10,
         CTRL_CORE_PAD_IO_VIN1A_D10_MUXMODE_GPMC_A10_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D11,
         CTRL_CORE_PAD_IO_VIN1A_D11_MUXMODE_GPMC_A11_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D12,
         CTRL_CORE_PAD_IO_VIN1A_D12_MUXMODE_GPMC_A12_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D13,
         CTRL_CORE_PAD_IO_VIN1A_D13_MUXMODE_GPMC_A13_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D14,
         CTRL_CORE_PAD_IO_VIN1A_D14_MUXMODE_GPMC_A14_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VIN1A_D15,
         CTRL_CORE_PAD_IO_VIN1A_D15_MUXMODE_GPMC_A15_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_UART1_CTSN,
         CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_GPMC_A16_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_UART1_RTSN,
         CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_GPMC_A17_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_UART2_CTSN,
         CTRL_CORE_PAD_IO_UART2_CTSN_MUXMODE_GPMC_A18_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_UART2_RTSN,
         CTRL_CORE_PAD_IO_UART2_RTSN_MUXMODE_GPMC_A19_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D8,
         CTRL_CORE_PAD_IO_VOUT1_D8_MUXMODE_GPMC_A20_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D9,
         CTRL_CORE_PAD_IO_VOUT1_D9_MUXMODE_GPMC_A21_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D10,
         CTRL_CORE_PAD_IO_VOUT1_D10_MUXMODE_GPMC_A22_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D11,
         CTRL_CORE_PAD_IO_VOUT1_D11_MUXMODE_GPMC_A23_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D12,
         CTRL_CORE_PAD_IO_VOUT1_D12_MUXMODE_GPMC_A24_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D13,
         CTRL_CORE_PAD_IO_VOUT1_D13_MUXMODE_GPMC_A25_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D14,
         CTRL_CORE_PAD_IO_VOUT1_D14_MUXMODE_GPMC_A26_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D15,
         CTRL_CORE_PAD_IO_VOUT1_D15_MUXMODE_GPMC_A27_3,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},

        /*GPMC chip select*/
        {CTRL_CORE_PAD_IO_GPMC_CS0,
         CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_GPMC_CS0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},

        /*GPMC control lines*/
        {CTRL_CORE_PAD_IO_GPMC_ADVN_ALE,
         CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_MUXMODE_GPMC_ADVN_ALE_0,
         0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_OEN_REN,
         CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_GPMC_OEN_REN_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_WEN,
         CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_GPMC_WEN_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_BEN0,
         CTRL_CORE_PAD_IO_GPMC_BEN0_MUXMODE_GPMC_BEN0_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_WAIT0,
         CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_GPMC_WAIT0_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
    };

    /*configure the GPMC pad*/
    configure_pad(gpmc_pad_config, sizeof (gpmc_pad_config) /
                  sizeof (gpmc_pad_config[0]));
}

void PlatformGPMCSetPinMuxAddrLines(void)
{
    /*Todo configure the GPMC pad for ADDR Lines*/
}

void PlatformMMC1SetPinMux(void)
{
    /*Todo configure the mmc1 pad*/
}

void PlatformI2C2SetPinMux(void)
{
    /*Todo configure the i2c2 pad*/
}

void PlatformVIN1SetPinMux(void)
{
    /*Todo configure the vin1 pad*/
}

void PlatformVIN2SetPinMux(void)
{
    /*Todo configure the vin2 pad*/
}

void PlatformLCDSetPinMux(void)
{
    /*Todo configure the vin2 pad*/
}

/*
 * rgmii0_txc
 * rgmii0_txctl
 * rgmii0_txd[3]
 * rgmii0_txd[2]
 * rgmii0_txd[1]
 * rgmii0_txd[0]
 * rgmii0_rxc
 * rgmii0_rxctl
 * rgmii0_rxd[3]
 * rgmii0_rxd[2]
 * rgmii0_rxd[1]
 * rgmii0_rxd[0]
 */
void PlatformRGMII0SetPinMux(void)
{
    /* Arrary define the PAD properties of rgmii pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t rgmii_pad_config[] = {
        /* MDIO (2 pads) */

        {CTRL_CORE_PAD_IO_MDIO_MCLK,
         CTRL_CORE_PAD_IO_MDIO_MCLK_MUXMODE_MDIO_MCLK_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_MDIO_D,
         CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_MDIO_D_0, PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, WAKEUPENABLE_DISABLE},

        /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
        /*RGMI*/
        {CTRL_CORE_PAD_IO_RGMII0_TXC,
         CTRL_CORE_PAD_IO_RGMII0_TXC_MUXMODE_RGMII0_TXC_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_TXCTL,
         CTRL_CORE_PAD_IO_RGMII0_TXCTL_MUXMODE_RGMII0_TXCTL_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_TXD0,
         CTRL_CORE_PAD_IO_RGMII0_TXD0_MUXMODE_RGMII0_TXD0_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_TXD1,
         CTRL_CORE_PAD_IO_RGMII0_TXD1_MUXMODE_RGMII0_TXD1_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_TXD2,
         CTRL_CORE_PAD_IO_RGMII0_TXD2_MUXMODE_RGMII0_TXD2_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_TXD3,
         CTRL_CORE_PAD_IO_RGMII0_TXD3_MUXMODE_RGMII0_TXD3_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_RXC,
         CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_RGMII0_RXC_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_RXCTL,
         CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_RGMII0_RXCTL_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_RXD0,
         CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_RGMII0_RXD0_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_RXD1,
         CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_RGMII0_RXD1_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_RXD2,
         CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_RGMII0_RXD2_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_IO_RGMII0_RXD3,
         CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_RGMII0_RXD3_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},
    };

    /*configure the vin2 pad*/
    configure_pad(rgmii_pad_config, sizeof (rgmii_pad_config) /
                  sizeof (rgmii_pad_config[0]));
}

void PlatformQSPISetPinMux(void)
{
    /* Arrary define the PAD properties of qspi1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t qspi_pad_config[7] = {
        {CTRL_CORE_PAD_IO_GPMC_CS6,
         CTRL_CORE_PAD_IO_GPMC_CS6_MUXMODE_QSPI1_SCLK_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_UART1_RTSN,
         CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_QSPI1_RTCLK_8,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_CS1,
         CTRL_CORE_PAD_IO_GPMC_CS1_MUXMODE_QSPI1_CS0_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_CS5,
         CTRL_CORE_PAD_IO_GPMC_CS5_MUXMODE_QSPI1_D0_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_CS4,
         CTRL_CORE_PAD_IO_GPMC_CS4_MUXMODE_QSPI1_D1_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_CS3,
         CTRL_CORE_PAD_IO_GPMC_CS3_MUXMODE_QSPI1_D2_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_GPMC_CS2,
         CTRL_CORE_PAD_IO_GPMC_CS2_MUXMODE_QSPI1_D3_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
    };

    /*configure the uart1 pad*/
    configure_pad(qspi_pad_config, sizeof (qspi_pad_config) /
                  sizeof (qspi_pad_config[0]));
}

/* ************** Legacy functions -let to clean-it up ********************* */

/* Configuring PAD in any module or application */

void PlatformI2C1SetPinMux(void)
{
    /*Todo configure the I2C1_SDA pad*/
    /*Todo configure the I2C1_SCL pad*/
}

void PlatformI2C4SetPinMux(void)
{
    /*Todo configure the I2C4_SDA pad*/
    /*Todo configure the I2C4_SCL pad*/
}

void PlatformUART1SetPinMux(void)
{
    /* Arrary define the PAD properties of uart1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t uart1_pad_config[2] = {
        {CTRL_CORE_PAD_IO_UART1_RXD,
         CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_UART1_RXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_UART1_TXD,
         CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_UART1_TXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the uart1 pad*/
    configure_pad(uart1_pad_config, sizeof (uart1_pad_config) /
                  sizeof (uart1_pad_config[0]));
}

void PlatformUART2SetPinMux(void)
{
    /* Arrary define the PAD properties of uart2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t uart2_pad_config[2] = {
        {CTRL_CORE_PAD_IO_UART2_TXD,
         CTRL_CORE_PAD_IO_UART2_TXD_MUXMODE_UART2_TXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_UART2_RXD,
         CTRL_CORE_PAD_IO_UART2_RXD_MUXMODE_UART2_RXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the uart2 pad*/
    configure_pad(uart2_pad_config, sizeof (uart2_pad_config) /
                  sizeof (uart2_pad_config[0]));
}

void PlatformUART3SetPinMux(void)
{
    /* Arrary define the PAD properties of uart3 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t uart3_pad_config[2] = {
        {CTRL_CORE_PAD_IO_SPI1_CS0,
         CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_UART3_TXD_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI1_SCLK,
         CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_UART3_RXD_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the uart3 pad*/
    configure_pad(uart3_pad_config, sizeof (uart3_pad_config) /
                  sizeof (uart3_pad_config[0]));
}

void PlatformUartConsoleSetPinMux(void)
{
    PlatformUARTSetPinMux(UART3_INST);
}

int32_t PlatformUARTSetPinMux(UART_INST_t num)
{
    int32_t retStatus = 0;
    switch (num)
    {
        case UART1_INST:
            PlatformUART1SetPinMux();
            break;
        case UART2_INST:
            PlatformUART2SetPinMux();
            break;
        case UART3_INST:
            PlatformUART3SetPinMux();
            break;
        default:
            retStatus = (-(int32_t)1);
            break;
    }

    return retStatus;
}

void PlatformMMCSD4SetPinMux(void)
{
    /* Arrary define the PAD properties of MMCSD4 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mmcsd4_pad_config[6] = {
        {CTRL_CORE_PAD_IO_RGMII0_RXC,
         CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_MMC4_CLK_5,
         0xff, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_IO_RGMII0_RXCTL,
         CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_MMC4_CMD_5,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_IO_RGMII0_RXD3,
         CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_MMC4_DAT0_5,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_IO_RGMII0_RXD2,
         CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_MMC4_DAT1_5,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_IO_RGMII0_RXD1,
         CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_MMC4_DAT2_5,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_IO_RGMII0_RXD0,
         CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_MMC4_DAT3_5,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
    };

    /*configure the MMCSD4 pad*/
    configure_pad(mmcsd4_pad_config, sizeof (mmcsd4_pad_config) /
                  sizeof (mmcsd4_pad_config[0]));
}

int32_t PlatformMMCSDSetPinMux(MMC_INST_t num)
{
    int32_t retStatus = 0;
    switch (num)
    {
        case MMC4_INST:
            PlatformMMCSD4SetPinMux();
            break;
        default:
            retStatus = (-(int32_t)1);
            break;
    }

    return retStatus;
}

void PlatformMCSPI1SetPinMux(void)
{
    /* Arrary define the PAD properties of McSPI1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mcspi1_pad_config[4] = {
        {CTRL_CORE_PAD_IO_SPI1_CS0,
         CTRL_CORE_PAD_IO_SPI1_CS0_MUXMODE_SPI1_CS0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI1_SCLK,
         CTRL_CORE_PAD_IO_SPI1_SCLK_MUXMODE_SPI1_SCLK_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI1_D0,
         CTRL_CORE_PAD_IO_SPI1_D0_MUXMODE_SPI1_D0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI1_D1,
         CTRL_CORE_PAD_IO_SPI1_D1_MUXMODE_SPI1_D1_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the McSPI1 pad*/
    configure_pad(mcspi1_pad_config, sizeof (mcspi1_pad_config) /
                  sizeof (mcspi1_pad_config[0]));
}

void PlatformMCSPI2SetPinMux(void)
{
    /* Arrary define the PAD properties of McSPI2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mcspi2_pad_config[4] = {
        {CTRL_CORE_PAD_IO_SPI2_CS0,
         CTRL_CORE_PAD_IO_SPI2_CS0_MUXMODE_SPI2_CS0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI2_SCLK,
         CTRL_CORE_PAD_IO_SPI2_SCLK_MUXMODE_SPI2_SCLK_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI2_D0,
         CTRL_CORE_PAD_IO_SPI2_D0_MUXMODE_SPI2_D0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_SPI2_D1,
         CTRL_CORE_PAD_IO_SPI2_D1_MUXMODE_SPI2_D1_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the McSPI1 pad*/
    configure_pad(mcspi2_pad_config, sizeof (mcspi2_pad_config) /
                  sizeof (mcspi2_pad_config[0]));
}

void PlatformMCSPI3SetPinMux(void)
{
    /* Arrary define the PAD properties of McSPI3 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mcspi3_pad_config[4] = {
        {CTRL_CORE_PAD_IO_GPMC_AD8,
         CTRL_CORE_PAD_IO_GPMC_AD8_MUXMODE_SPI3_CS0_4,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_GPMC_AD7,
         CTRL_CORE_PAD_IO_GPMC_AD7_MUXMODE_SPI3_SCLK_4,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_GPMC_AD6,
         CTRL_CORE_PAD_IO_GPMC_AD6_MUXMODE_SPI3_D0_4,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_GPMC_AD5,
         CTRL_CORE_PAD_IO_GPMC_AD5_MUXMODE_SPI3_D1_4,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the McSPI3 pad*/
    configure_pad(mcspi3_pad_config, sizeof (mcspi3_pad_config) /
                  sizeof (mcspi3_pad_config[0]));
}

void PlatformMCSPI4SetPinMux(void)
{
    /* Arrary define the PAD properties of McSPI3 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mcspi4_pad_config[4] = {
        {CTRL_CORE_PAD_IO_UART1_RTSN,
         CTRL_CORE_PAD_IO_UART1_RTSN_MUXMODE_SPI4_CS0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_UART1_CTSN,
         CTRL_CORE_PAD_IO_UART1_CTSN_MUXMODE_SPI4_SCLK,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_UART1_TXD,
         CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_SPI4_D0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_UART1_RXD,
         CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_SPI4_D1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the McSPI4 pad*/
    configure_pad(mcspi4_pad_config, sizeof (mcspi4_pad_config) /
                  sizeof (mcspi4_pad_config[0]));
}

void PlatformGPIOInputOutputSetPinMux(void)
{
    PlatformGPIO4SetPinMux();
}

void PlatformGPIO4SetPinMux(void)
{
    /* Arrary define the PAD properties of GPIO4 pins 9 & 10*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t gpio4_pad_config[2] = {
        {CTRL_CORE_PAD_IO_DCAN1_TX,
         CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_GPIO4_9_14,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_IO_DCAN1_RX,
         CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_GPIO4_10_14,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the gpio4 pad*/
    configure_pad(gpio4_pad_config, sizeof (gpio4_pad_config) /
                  sizeof (gpio4_pad_config[0]));
}

void PlatformDCAN1SetPinMux(void)
{
    /* Arrary define the PAD properties of dcan1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan1_pad_config[2] = {
        {CTRL_CORE_PAD_IO_DCAN1_TX,
         CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_DCAN1_TX_0,
         0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_DCAN1_RX,
         CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_DCAN1_RX_0,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan1 pad*/
    configure_pad(dcan1_pad_config, sizeof (dcan1_pad_config) /
                  sizeof (dcan1_pad_config[0]));
}

void PlatformDCAN2SetPinMux(void)
{
    /* Arrary define the PAD properties of uart1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan2_pad_config[2] = {
        {CTRL_CORE_PAD_IO_UART1_RXD,
         CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_DCAN2_TX_12,
         0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_UART1_TXD,
         CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_DCAN2_RX_12,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan2 pad*/
    configure_pad(dcan2_pad_config, sizeof (dcan2_pad_config) /
                  sizeof (dcan2_pad_config[0]));
}

void PlatformMCANSetPinMux(void)
{
    /* Arrary define the PAD properties of uart1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan2_pad_config[2] = {
        {CTRL_CORE_PAD_IO_UART1_RXD,
         CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_DCAN2_TX_12,
         0xff, 0xff, 0xff,
         0x0, 0xff},
        {CTRL_CORE_PAD_IO_UART1_TXD,
         CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_DCAN2_RX_12,
         0xff, 0xff, 0xff,
         0x0, 0xff},
    };
    /*configure the dcan2 pad*/
    configure_pad(dcan2_pad_config, sizeof (dcan2_pad_config) /
                  sizeof (dcan2_pad_config[0]));
}

void PlatformDCAN1RXSetPinMux(void)
{
    /* Arrary define the PAD properties of dcan1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan1_pad_config[1] = {
        {CTRL_CORE_PAD_IO_DCAN1_RX,
         CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_GPIO4_10_14,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan1 pad*/
    configure_pad(dcan1_pad_config, sizeof (dcan1_pad_config) /
                  sizeof (dcan1_pad_config[0]));
}

void PlatformDCAN2RXSetPinMux(void)
{
    /* Arrary define the PAD properties of uart1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan2_pad_config[1] = {
        {CTRL_CORE_PAD_IO_UART1_TXD,
         CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_GPIO4_14_14,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan2 pad*/
    configure_pad(dcan2_pad_config, sizeof (dcan2_pad_config) /
                  sizeof (dcan2_pad_config[0]));
}

void PlatformMCASP1SetPinMux(void)
{
    /* Array define the PAD properties of GPMC pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mcasp_pad_config[] = {
        /*GPMC Data lines AD0-AD15*/
        {CTRL_CORE_PAD_IO_VOUT1_DE,
         CTRL_CORE_PAD_IO_VOUT1_DE_MUXMODE_MCASP1_ACLKX_1,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_FLD,
         CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_MCASP1_FSX_1,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D0,
         CTRL_CORE_PAD_IO_VOUT1_D0_MUXMODE_MCASP1_AXR0_1,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_IO_VOUT1_D1,
         CTRL_CORE_PAD_IO_VOUT1_D1_MUXMODE_MCASP1_AXR1_1,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
    };

    /*configure the MCASP pad*/
    configure_pad(mcasp_pad_config, sizeof (mcasp_pad_config) /
                  sizeof (mcasp_pad_config[0]));
}

void PlatformClkOut2SetPinMux(void)
{
    /* Arrary define the PAD properties of VIN1A pin*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t clkOout2_pad_config[1] = {
        {CTRL_CORE_PAD_IO_VIN1A_FLD0,
        CTRL_CORE_PAD_IO_VIN1A_FLD0_MUXMODE_CLKOUT2,
        0xff, 0xff, 0xff,
        0xff, 0xff},
    };
    /*configure the dcan2 pad*/
    configure_pad(clkOout2_pad_config, sizeof (clkOout2_pad_config) /
                  sizeof (clkOout2_pad_config[0]));
}

void PlatformRGMIISetPinMux(void)
{
    PlatformRGMII0SetPinMux();
}
