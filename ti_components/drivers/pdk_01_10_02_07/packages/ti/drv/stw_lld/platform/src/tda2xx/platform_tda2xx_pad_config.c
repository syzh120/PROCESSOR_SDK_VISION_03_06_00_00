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
 *   Filename:          platform_tda2xx_pad_config.c
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
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* None */

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
        {CTRL_CORE_PAD_GPMC_AD0,
         CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_GPMC_AD0_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD1,
         CTRL_CORE_PAD_GPMC_AD1_GPMC_AD1_MUXMODE_GPMC_AD1_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD2,
         CTRL_CORE_PAD_GPMC_AD2_GPMC_AD2_MUXMODE_GPMC_AD2_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD3,
         CTRL_CORE_PAD_GPMC_AD3_GPMC_AD3_MUXMODE_GPMC_AD3_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD4,
         CTRL_CORE_PAD_GPMC_AD4_GPMC_AD4_MUXMODE_GPMC_AD4_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD5,
         CTRL_CORE_PAD_GPMC_AD5_GPMC_AD5_MUXMODE_GPMC_AD5_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD6,
         CTRL_CORE_PAD_GPMC_AD6_GPMC_AD6_MUXMODE_GPMC_AD6_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD7,
         CTRL_CORE_PAD_GPMC_AD7_GPMC_AD7_MUXMODE_GPMC_AD7_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD8,
         CTRL_CORE_PAD_GPMC_AD8_GPMC_AD8_MUXMODE_GPMC_AD8_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD9,
         CTRL_CORE_PAD_GPMC_AD9_GPMC_AD9_MUXMODE_GPMC_AD9_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD10,
         CTRL_CORE_PAD_GPMC_AD10_GPMC_AD10_MUXMODE_GPMC_AD10_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD11,
         CTRL_CORE_PAD_GPMC_AD11_GPMC_AD11_MUXMODE_GPMC_AD11_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD12,
         CTRL_CORE_PAD_GPMC_AD12_GPMC_AD12_MUXMODE_GPMC_AD12_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD13,
         CTRL_CORE_PAD_GPMC_AD13_GPMC_AD13_MUXMODE_GPMC_AD13_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD14,
         CTRL_CORE_PAD_GPMC_AD14_GPMC_AD14_MUXMODE_GPMC_AD14_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_AD15,
         CTRL_CORE_PAD_GPMC_AD15_GPMC_AD15_MUXMODE_GPMC_AD15_0,
         0xff, 0xff, INPUTENABLE_ENABLE,
         0xff, 0xff},

        /*GPMC Add lines A0-A27*/
        {CTRL_CORE_PAD_GPMC_A0,
         CTRL_CORE_PAD_GPMC_A0_GPMC_A0_MUXMODE_GPMC_A0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A1,
         CTRL_CORE_PAD_GPMC_A1_GPMC_A1_MUXMODE_GPMC_A1_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A2,
         CTRL_CORE_PAD_GPMC_A2_GPMC_A2_MUXMODE_GPMC_A2_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A3,
         CTRL_CORE_PAD_GPMC_A3_GPMC_A3_MUXMODE_GPMC_A3_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A4,
         CTRL_CORE_PAD_GPMC_A4_GPMC_A4_MUXMODE_GPMC_A4_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A5,
         CTRL_CORE_PAD_GPMC_A5_GPMC_A5_MUXMODE_GPMC_A5_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A6,
         CTRL_CORE_PAD_GPMC_A6_GPMC_A6_MUXMODE_GPMC_A6_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A7,
         CTRL_CORE_PAD_GPMC_A7_GPMC_A7_MUXMODE_GPMC_A7_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A8,
         CTRL_CORE_PAD_GPMC_A8_GPMC_A8_MUXMODE_GPMC_A8_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A9,
         CTRL_CORE_PAD_GPMC_A9_GPMC_A9_MUXMODE_GPMC_A9_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A10,
         CTRL_CORE_PAD_GPMC_A10_GPMC_A10_MUXMODE_GPMC_A10_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A11,
         CTRL_CORE_PAD_GPMC_A11_GPMC_A11_MUXMODE_GPMC_A11_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A12,
         CTRL_CORE_PAD_GPMC_A12_GPMC_A12_MUXMODE_GPMC_A12_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A13,
         CTRL_CORE_PAD_GPMC_A13_GPMC_A13_MUXMODE_GPMC_A13_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A14,
         CTRL_CORE_PAD_GPMC_A14_GPMC_A14_MUXMODE_GPMC_A14_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A15,
         CTRL_CORE_PAD_GPMC_A15_GPMC_A15_MUXMODE_GPMC_A15_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A16,
         CTRL_CORE_PAD_GPMC_A16_GPMC_A16_MUXMODE_GPMC_A16_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A17,
         CTRL_CORE_PAD_GPMC_A17_GPMC_A17_MUXMODE_GPMC_A17_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A18,
         CTRL_CORE_PAD_GPMC_A18_GPMC_A18_MUXMODE_GPMC_A18_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A19,
         CTRL_CORE_PAD_GPMC_A19_GPMC_A19_MUXMODE_GPMC_A19_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A20,
         CTRL_CORE_PAD_GPMC_A20_GPMC_A20_MUXMODE_GPMC_A20_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A21,
         CTRL_CORE_PAD_GPMC_A21_GPMC_A21_MUXMODE_GPMC_A21_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A22,
         CTRL_CORE_PAD_GPMC_A22_GPMC_A22_MUXMODE_GPMC_A22_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A23,
         CTRL_CORE_PAD_GPMC_A23_GPMC_A23_MUXMODE_GPMC_A23_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A24,
         CTRL_CORE_PAD_GPMC_A24_GPMC_A24_MUXMODE_GPMC_A24_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A25,
         CTRL_CORE_PAD_GPMC_A25_GPMC_A25_MUXMODE_GPMC_A25_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A26,
         CTRL_CORE_PAD_GPMC_A26_GPMC_A26_MUXMODE_GPMC_A26_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A27,
         CTRL_CORE_PAD_GPMC_A27_GPMC_A27_MUXMODE_GPMC_A27_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},

        /*GPMC chip select*/
        {CTRL_CORE_PAD_GPMC_CS0,
         CTRL_CORE_PAD_GPMC_CS0_GPMC_CS0_MUXMODE_GPMC_CS0_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},

        /*GPMC control lines*/
        {CTRL_CORE_PAD_GPMC_ADVN_ALE,
         CTRL_CORE_PAD_GPMC_ADVN_ALE_GPMC_ADVN_ALE_MUXMODE_GPMC_ADVN_ALE_0,
         0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_OEN_REN,
         CTRL_CORE_PAD_GPMC_OEN_REN_GPMC_OEN_REN_MUXMODE_GPMC_OEN_REN_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_WEN,
         CTRL_CORE_PAD_GPMC_WEN_GPMC_WEN_MUXMODE_GPMC_WEN_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_BEN0,
         CTRL_CORE_PAD_GPMC_BEN0_GPMC_BEN0_MUXMODE_GPMC_BEN0_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_WAIT0,
         CTRL_CORE_PAD_GPMC_WAIT0_GPMC_WAIT0_MUXMODE_GPMC_WAIT0_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
    };

    /*configure the GPMC pad*/
    configure_pad(gpmc_pad_config, sizeof (gpmc_pad_config) /
                  sizeof (gpmc_pad_config[0]));
}

void PlatformGPMCSetPinMuxAddrLines(void)
{
    /* Arrary define the PAD properties of GPMC pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t gpmc_pad_config[] = {
        /*GPMC Add lines A19-A27*/
        {CTRL_CORE_PAD_GPMC_A19,
         CTRL_CORE_PAD_GPMC_A19_GPMC_A19_MUXMODE_GPMC_A19_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A20,
         CTRL_CORE_PAD_GPMC_A20_GPMC_A20_MUXMODE_GPMC_A20_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A21,
         CTRL_CORE_PAD_GPMC_A21_GPMC_A21_MUXMODE_GPMC_A21_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A22,
         CTRL_CORE_PAD_GPMC_A22_GPMC_A22_MUXMODE_GPMC_A22_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A23,
         CTRL_CORE_PAD_GPMC_A23_GPMC_A23_MUXMODE_GPMC_A23_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A24,
         CTRL_CORE_PAD_GPMC_A24_GPMC_A24_MUXMODE_GPMC_A24_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A25,
         CTRL_CORE_PAD_GPMC_A25_GPMC_A25_MUXMODE_GPMC_A25_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A26,
         CTRL_CORE_PAD_GPMC_A26_GPMC_A26_MUXMODE_GPMC_A26_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A27,
         CTRL_CORE_PAD_GPMC_A27_GPMC_A27_MUXMODE_GPMC_A27_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
    };

    /*configure the GPMC pad*/
    configure_pad(gpmc_pad_config, sizeof (gpmc_pad_config) /
                  sizeof (gpmc_pad_config[0]));
}

void PlatformMMC1SetPinMux(void)
{
    /* Arrary define the PAD properties of mmc1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mmc1_pad_config[] = {
        {CTRL_CORE_PAD_MMC1_CLK,
         CTRL_CORE_PAD_MMC1_CLK_MMC1_CLK_MUXMODE_MMC1_CLK_0, 0xff, 0xff,
         0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_CMD,
         CTRL_CORE_PAD_MMC1_CMD_MMC1_CMD_MUXMODE_MMC1_CMD_0, 0xff, 0xff,
         0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT0,
         CTRL_CORE_PAD_MMC1_DAT0_MMC1_DAT0_MUXMODE_MMC1_DAT0_0, 0xff, 0xff,
         0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT1,
         CTRL_CORE_PAD_MMC1_DAT1_MMC1_DAT1_MUXMODE_MMC1_DAT1_0, 0xff, 0xff,
         0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT2,
         CTRL_CORE_PAD_MMC1_DAT2_MMC1_DAT2_MUXMODE_MMC1_DAT2_0, 0xff, 0xff,
         0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT3,
         CTRL_CORE_PAD_MMC1_DAT3_MMC1_DAT3_MUXMODE_MMC1_DAT3_0, 0xff, 0xff,
         0xff, 0xff, 0xff},
    };

    /*configure the mmc1 pad*/
    configure_pad(mmc1_pad_config, sizeof (mmc1_pad_config) /
                  sizeof (mmc1_pad_config[0]));
}

void PlatformI2C2SetPinMux(void)
{
    /* Arrary define the PAD properties of i2c2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t i2c2_pad_config[] = {
        {CTRL_CORE_PAD_I2C2_SDA,
         CTRL_CORE_PAD_I2C2_SDA_I2C2_SDA_MUXMODE_I2C2_SDA_0, 0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_I2C2_SCL,
         CTRL_CORE_PAD_I2C2_SCL_I2C2_SCL_MUXMODE_I2C2_SCL_0, 0xff, 0xff, 0xff,
         0xff, 0xff},
    };

    /*configure the i2c2 pad*/
    configure_pad(i2c2_pad_config, sizeof (i2c2_pad_config) /
                  sizeof (i2c2_pad_config[0]));
}

void PlatformVIN1SetPinMux(void)
{
    pad_config_t vin1_pad_config[] = {
        /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
        /*GPMC Data lines AD0-AD15*/
        {CTRL_CORE_PAD_VIN1A_CLK0,
         CTRL_CORE_PAD_VIN1A_CLK0_VIN1A_CLK0_MUXMODE_VIN1A_CLK0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_DE0,
         CTRL_CORE_PAD_VIN1A_DE0_VIN1A_DE0_MUXMODE_VIN1A_DE0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_HSYNC0,
         CTRL_CORE_PAD_VIN1A_HSYNC0_VIN1A_HSYNC0_MUXMODE_VIN1A_HSYNC0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_VSYNC0,
         CTRL_CORE_PAD_VIN1A_VSYNC0_VIN1A_VSYNC0_MUXMODE_VIN1A_VSYNC0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D0,
         CTRL_CORE_PAD_VIN1A_D0_VIN1A_D0_MUXMODE_VIN1A_D0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D1,
         CTRL_CORE_PAD_VIN1A_D1_VIN1A_D1_MUXMODE_VIN1A_D1_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D2,
         CTRL_CORE_PAD_VIN1A_D2_VIN1A_D2_MUXMODE_VIN1A_D2_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D3,
         CTRL_CORE_PAD_VIN1A_D3_VIN1A_D3_MUXMODE_VIN1A_D3_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D4,
         CTRL_CORE_PAD_VIN1A_D4_VIN1A_D4_MUXMODE_VIN1A_D4_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D5,
         CTRL_CORE_PAD_VIN1A_D5_VIN1A_D5_MUXMODE_VIN1A_D5_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D6,
         CTRL_CORE_PAD_VIN1A_D6_VIN1A_D6_MUXMODE_VIN1A_D6_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D7,
         CTRL_CORE_PAD_VIN1A_D7_VIN1A_D7_MUXMODE_VIN1A_D7_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D8,
         CTRL_CORE_PAD_VIN1A_D8_VIN1A_D8_MUXMODE_VIN1A_D8_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D9,
         CTRL_CORE_PAD_VIN1A_D9_VIN1A_D9_MUXMODE_VIN1A_D9_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D10,
         CTRL_CORE_PAD_VIN1A_D10_VIN1A_D10_MUXMODE_VIN1A_D10_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D11,
         CTRL_CORE_PAD_VIN1A_D11_VIN1A_D11_MUXMODE_VIN1A_D11_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D12,
         CTRL_CORE_PAD_VIN1A_D12_VIN1A_D12_MUXMODE_VIN1A_D12_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D13,
         CTRL_CORE_PAD_VIN1A_D13_VIN1A_D13_MUXMODE_VIN1A_D13_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D14,
         CTRL_CORE_PAD_VIN1A_D14_VIN1A_D14_MUXMODE_VIN1A_D14_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D15,
         CTRL_CORE_PAD_VIN1A_D15_VIN1A_D15_MUXMODE_VIN1A_D15_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D16,
         CTRL_CORE_PAD_VIN1A_D16_VIN1A_D16_MUXMODE_VIN1A_D16_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D17,
         CTRL_CORE_PAD_VIN1A_D17_VIN1A_D17_MUXMODE_VIN1A_D17_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D18,
         CTRL_CORE_PAD_VIN1A_D18_VIN1A_D18_MUXMODE_VIN1A_D18_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D19,
         CTRL_CORE_PAD_VIN1A_D19_VIN1A_D19_MUXMODE_VIN1A_D19_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D20,
         CTRL_CORE_PAD_VIN1A_D20_VIN1A_D20_MUXMODE_VIN1A_D20_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D21,
         CTRL_CORE_PAD_VIN1A_D21_VIN1A_D21_MUXMODE_VIN1A_D21_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D22,
         CTRL_CORE_PAD_VIN1A_D22_VIN1A_D22_MUXMODE_VIN1A_D22_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN1A_D23,
         CTRL_CORE_PAD_VIN1A_D23_VIN1A_D23_MUXMODE_VIN1A_D23_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
    };

    /*configure the vin1 pad*/
    configure_pad(vin1_pad_config, sizeof (vin1_pad_config) /
                  sizeof (vin1_pad_config[0]));
}

void PlatformVIN2SetPinMux(void)
{
    pad_config_t vin2_pad_config[] = {
        /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
        /*GPMC Data lines AD0-AD15*/
        {CTRL_CORE_PAD_VIN2A_CLK0,
         CTRL_CORE_PAD_VIN2A_CLK0_VIN2A_CLK0_MUXMODE_VIN2A_CLK0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_DE0,
         CTRL_CORE_PAD_VIN2A_DE0_VIN2A_DE0_MUXMODE_VIN2A_DE0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_HSYNC0,
         CTRL_CORE_PAD_VIN2A_HSYNC0_VIN2A_HSYNC0_MUXMODE_VIN2A_HSYNC0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_VSYNC0,
         CTRL_CORE_PAD_VIN2A_VSYNC0_VIN2A_VSYNC0_MUXMODE_VIN2A_VSYNC0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D0,
         CTRL_CORE_PAD_VIN2A_D0_VIN2A_D0_MUXMODE_VIN2A_D0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D1,
         CTRL_CORE_PAD_VIN2A_D1_VIN2A_D1_MUXMODE_VIN2A_D1_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D2,
         CTRL_CORE_PAD_VIN2A_D2_VIN2A_D2_MUXMODE_VIN2A_D2_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D3,
         CTRL_CORE_PAD_VIN2A_D3_VIN2A_D3_MUXMODE_VIN2A_D3_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D4,
         CTRL_CORE_PAD_VIN2A_D4_VIN2A_D4_MUXMODE_VIN2A_D4_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D5,
         CTRL_CORE_PAD_VIN2A_D5_VIN2A_D5_MUXMODE_VIN2A_D5_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D6,
         CTRL_CORE_PAD_VIN2A_D6_VIN2A_D6_MUXMODE_VIN2A_D6_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D7,
         CTRL_CORE_PAD_VIN2A_D7_VIN2A_D7_MUXMODE_VIN2A_D7_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D8,
         CTRL_CORE_PAD_VIN2A_D8_VIN2A_D8_MUXMODE_VIN2A_D8_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D9,
         CTRL_CORE_PAD_VIN2A_D9_VIN2A_D9_MUXMODE_VIN2A_D9_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D10,
         CTRL_CORE_PAD_VIN2A_D10_VIN2A_D10_MUXMODE_VIN2A_D10_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D11,
         CTRL_CORE_PAD_VIN2A_D11_VIN2A_D11_MUXMODE_VIN2A_D11_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D12,
         CTRL_CORE_PAD_VIN2A_D12_VIN2A_D12_MUXMODE_VIN2A_D12_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D13,
         CTRL_CORE_PAD_VIN2A_D13_VIN2A_D13_MUXMODE_VIN2A_D13_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D14,
         CTRL_CORE_PAD_VIN2A_D14_VIN2A_D14_MUXMODE_VIN2A_D14_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D15,
         CTRL_CORE_PAD_VIN2A_D15_VIN2A_D15_MUXMODE_VIN2A_D15_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D16,
         CTRL_CORE_PAD_VIN2A_D16_VIN2A_D16_MUXMODE_VIN2A_D16_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D17,
         CTRL_CORE_PAD_VIN2A_D17_VIN2A_D17_MUXMODE_VIN2A_D17_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D18,
         CTRL_CORE_PAD_VIN2A_D18_VIN2A_D18_MUXMODE_VIN2A_D18_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D19,
         CTRL_CORE_PAD_VIN2A_D19_VIN2A_D19_MUXMODE_VIN2A_D19_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D20,
         CTRL_CORE_PAD_VIN2A_D20_VIN2A_D20_MUXMODE_VIN2A_D20_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D21,
         CTRL_CORE_PAD_VIN2A_D21_VIN2A_D21_MUXMODE_VIN2A_D21_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D22,
         CTRL_CORE_PAD_VIN2A_D22_VIN2A_D22_MUXMODE_VIN2A_D22_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VIN2A_D23,
         CTRL_CORE_PAD_VIN2A_D23_VIN2A_D23_MUXMODE_VIN2A_D23_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
    };

    /*configure the vin2 pad*/
    configure_pad(vin2_pad_config, sizeof (vin2_pad_config) /
                  sizeof (vin2_pad_config[0]));
}

void PlatformLCDSetPinMux(void)
{
    pad_config_t lcd_pad_config[] = {
        /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
        /*LCD*/
        {CTRL_CORE_PAD_VOUT1_CLK,
         CTRL_CORE_PAD_VOUT1_CLK_VOUT1_CLK_MUXMODE_VOUT1_CLK_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_DE,
         CTRL_CORE_PAD_VOUT1_DE_VOUT1_DE_MUXMODE_VOUT1_DE_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_HSYNC,
         CTRL_CORE_PAD_VOUT1_HSYNC_VOUT1_HSYNC_MUXMODE_VOUT1_HSYNC_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_VSYNC,
         CTRL_CORE_PAD_VOUT1_VSYNC_VOUT1_VSYNC_MUXMODE_VOUT1_VSYNC_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D0,
         CTRL_CORE_PAD_VOUT1_D0_VOUT1_D0_MUXMODE_VOUT1_D0_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D1,
         CTRL_CORE_PAD_VOUT1_D1_VOUT1_D1_MUXMODE_VOUT1_D1_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D2,
         CTRL_CORE_PAD_VOUT1_D2_VOUT1_D2_MUXMODE_VOUT1_D2_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D3,
         CTRL_CORE_PAD_VOUT1_D3_VOUT1_D3_MUXMODE_VOUT1_D3_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D4,
         CTRL_CORE_PAD_VOUT1_D4_VOUT1_D4_MUXMODE_VOUT1_D4_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D5,
         CTRL_CORE_PAD_VOUT1_D5_VOUT1_D5_MUXMODE_VOUT1_D5_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D6,
         CTRL_CORE_PAD_VOUT1_D6_VOUT1_D6_MUXMODE_VOUT1_D6_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D7,
         CTRL_CORE_PAD_VOUT1_D7_VOUT1_D7_MUXMODE_VOUT1_D7_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D8,
         CTRL_CORE_PAD_VOUT1_D8_VOUT1_D8_MUXMODE_VOUT1_D8_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D9,
         CTRL_CORE_PAD_VOUT1_D9_VOUT1_D9_MUXMODE_VOUT1_D9_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D10,
         CTRL_CORE_PAD_VOUT1_D10_VOUT1_D10_MUXMODE_VOUT1_D10_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D11,
         CTRL_CORE_PAD_VOUT1_D11_VOUT1_D11_MUXMODE_VOUT1_D11_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D12,
         CTRL_CORE_PAD_VOUT1_D12_VOUT1_D12_MUXMODE_VOUT1_D12_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D13,
         CTRL_CORE_PAD_VOUT1_D13_VOUT1_D13_MUXMODE_VOUT1_D13_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D14,
         CTRL_CORE_PAD_VOUT1_D14_VOUT1_D14_MUXMODE_VOUT1_D14_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D15,
         CTRL_CORE_PAD_VOUT1_D15_VOUT1_D15_MUXMODE_VOUT1_D15_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D16,
         CTRL_CORE_PAD_VOUT1_D16_VOUT1_D16_MUXMODE_VOUT1_D16_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D17,
         CTRL_CORE_PAD_VOUT1_D17_VOUT1_D17_MUXMODE_VOUT1_D17_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D18,
         CTRL_CORE_PAD_VOUT1_D18_VOUT1_D18_MUXMODE_VOUT1_D18_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D19,
         CTRL_CORE_PAD_VOUT1_D19_VOUT1_D19_MUXMODE_VOUT1_D19_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D20,
         CTRL_CORE_PAD_VOUT1_D20_VOUT1_D20_MUXMODE_VOUT1_D20_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D21,
         CTRL_CORE_PAD_VOUT1_D21_VOUT1_D21_MUXMODE_VOUT1_D21_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D22,
         CTRL_CORE_PAD_VOUT1_D22_VOUT1_D22_MUXMODE_VOUT1_D22_0, 0xff,
         0xff, 0xff, 0xff, 0xff},
        {CTRL_CORE_PAD_VOUT1_D23,
         CTRL_CORE_PAD_VOUT1_D23_VOUT1_D23_MUXMODE_VOUT1_D23_0, 0xff,
         0xff, 0xff, 0xff, 0xff}
    };

    /*configure the vin2 pad*/
    configure_pad(lcd_pad_config, sizeof (lcd_pad_config) /
                  sizeof (lcd_pad_config[0]));
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
    pad_config_t rgmii0_pad_config[] = {
        /* MDIO (2 pads) */

        {CTRL_CORE_PAD_MDIO_MCLK,
         CTRL_CORE_PAD_MDIO_MCLK_MDIO_MCLK_MUXMODE_MDIO_MCLK_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_MDIO_D,
         CTRL_CORE_PAD_MDIO_D_MDIO_D_MUXMODE_MDIO_D_0, PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, WAKEUPENABLE_DISABLE},

        /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
        /*RGMI*/
        {CTRL_CORE_PAD_RGMII0_TXC,
         CTRL_CORE_PAD_RGMII0_TXC_RGMII0_TXC_MUXMODE_RGMII0_TXC_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_TXCTL,
         CTRL_CORE_PAD_RGMII0_TXCTL_RGMII0_TXCTL_MUXMODE_RGMII0_TXCTL_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_TXD0,
         CTRL_CORE_PAD_RGMII0_TXD0_RGMII0_TXD0_MUXMODE_RGMII0_TXD0_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_TXD1,
         CTRL_CORE_PAD_RGMII0_TXD1_RGMII0_TXD1_MUXMODE_RGMII0_TXD1_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_TXD2,
         CTRL_CORE_PAD_RGMII0_TXD2_RGMII0_TXD2_MUXMODE_RGMII0_TXD2_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_TXD3,
         CTRL_CORE_PAD_RGMII0_TXD3_RGMII0_TXD3_MUXMODE_RGMII0_TXD3_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_RXC,
         CTRL_CORE_PAD_RGMII0_RXC_RGMII0_RXC_MUXMODE_RGMII0_RXC_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_RXCTL,
         CTRL_CORE_PAD_RGMII0_RXCTL_RGMII0_RXCTL_MUXMODE_RGMII0_RXCTL_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_RXD0,
         CTRL_CORE_PAD_RGMII0_RXD0_RGMII0_RXD0_MUXMODE_RGMII0_RXD0_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_RXD1,
         CTRL_CORE_PAD_RGMII0_RXD1_RGMII0_RXD1_MUXMODE_RGMII0_RXD1_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_RXD2,
         CTRL_CORE_PAD_RGMII0_RXD2_RGMII0_RXD2_MUXMODE_RGMII0_RXD2_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_RGMII0_RXD3,
         CTRL_CORE_PAD_RGMII0_RXD3_RGMII0_RXD3_MUXMODE_RGMII0_RXD3_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},
    };
    /*configure the rgmii0 pad*/
    configure_pad(rgmii0_pad_config, sizeof (rgmii0_pad_config) /
                  sizeof (rgmii0_pad_config[0]));
}

void PlatformRGMII1SetPinMux(void)
{
    pad_config_t rgmii1_pad_config[] = {
        /* MDIO (2 pads) */

        {CTRL_CORE_PAD_MDIO_MCLK,
         CTRL_CORE_PAD_MDIO_MCLK_MDIO_MCLK_MUXMODE_MDIO_MCLK_0,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_MDIO_D,
         CTRL_CORE_PAD_MDIO_D_MDIO_D_MUXMODE_MDIO_D_0, PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, WAKEUPENABLE_DISABLE},

        /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
        /*RGMI*/
        {CTRL_CORE_PAD_VIN2A_D12,
         CTRL_CORE_PAD_VIN2A_D12_VIN2A_D12_MUXMODE_RGMII1_TXC_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D13,
         CTRL_CORE_PAD_VIN2A_D13_VIN2A_D13_MUXMODE_RGMII1_TXCTL_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D17,
         CTRL_CORE_PAD_VIN2A_D17_VIN2A_D17_MUXMODE_RGMII1_TXD0_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D16,
         CTRL_CORE_PAD_VIN2A_D16_VIN2A_D16_MUXMODE_RGMII1_TXD1_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D15,
         CTRL_CORE_PAD_VIN2A_D15_VIN2A_D15_MUXMODE_RGMII1_TXD2_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D14,
         CTRL_CORE_PAD_VIN2A_D14_VIN2A_D14_MUXMODE_RGMII1_TXD3_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D18,
         CTRL_CORE_PAD_VIN2A_D18_VIN2A_D18_MUXMODE_RGMII1_RXC_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D19,
         CTRL_CORE_PAD_VIN2A_D19_VIN2A_D19_MUXMODE_RGMII1_RXCTL_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D23,
         CTRL_CORE_PAD_VIN2A_D23_VIN2A_D23_MUXMODE_RGMII1_RXD0_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D22,
         CTRL_CORE_PAD_VIN2A_D22_VIN2A_D22_MUXMODE_RGMII1_RXD1_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D21,
         CTRL_CORE_PAD_VIN2A_D21_VIN2A_D21_MUXMODE_RGMII1_RXD2_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},

        {CTRL_CORE_PAD_VIN2A_D20,
         CTRL_CORE_PAD_VIN2A_D20_VIN2A_D20_MUXMODE_RGMII1_RXD3_3,
         PULLUDENABLE_ENABLE,
         PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff,
         WAKEUPENABLE_DISABLE},
    };

    /*configure the rgmii1 pad*/
    configure_pad(rgmii1_pad_config, sizeof (rgmii1_pad_config) /
                  sizeof (rgmii1_pad_config[0]));
}

void PlatformQSPISetPinMux(void)
{
    /* Arrary define the PAD properties of uart1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t qspi_pad_config[7] = {
        {CTRL_CORE_PAD_GPMC_A18,
         CTRL_CORE_PAD_GPMC_A18_GPMC_A18_MUXMODE_QSPI1_SCLK_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A13,
         CTRL_CORE_PAD_GPMC_A13_GPMC_A13_MUXMODE_QSPI1_RTCLK_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_CS2,
         CTRL_CORE_PAD_GPMC_CS2_GPMC_CS2_MUXMODE_QSPI1_CS0_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A17,
         CTRL_CORE_PAD_GPMC_A17_GPMC_A17_MUXMODE_QSPI1_D0_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A16,
         CTRL_CORE_PAD_GPMC_A16_GPMC_A16_MUXMODE_QSPI1_D1_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A15,
         CTRL_CORE_PAD_GPMC_A15_GPMC_A15_MUXMODE_QSPI1_D2_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A14,
         CTRL_CORE_PAD_GPMC_A14_GPMC_A14_MUXMODE_QSPI1_D3_1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
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
    /* Arrary define the PAD properties of I2C1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t i2c1_pad_config[2] = {
        {CTRL_CORE_PAD_I2C1_SDA,
         CTRL_CORE_PAD_I2C1_SDA_I2C1_SDA_MUXMODE_I2C1_SDA_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_I2C1_SCL,
         CTRL_CORE_PAD_I2C1_SCL_I2C1_SCL_MUXMODE_I2C1_SCL_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the I2C1 pad*/
    configure_pad(i2c1_pad_config, sizeof (i2c1_pad_config) /
                  sizeof (i2c1_pad_config[0]));
}

void PlatformI2C3SetPinMux(void)
{
    pad_config_t pad_config;

    /* I2C3_SDA */
    pad_config.pin_num         = CTRL_CORE_PAD_GPIO6_14;
    pad_config.muxmode         = 9;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;

    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* I2C3_SCL */
    pad_config.pin_num         = CTRL_CORE_PAD_GPIO6_15;
    pad_config.muxmode         = 9;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;

    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
}

void PlatformI2C4SetPinMux(void)
{
    /* Arrary define the PAD properties of I2C4 pins*/
    /* Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t i2c4_pad_config[2] = {
        {CTRL_CORE_PAD_MCASP4_ACLKX,
         CTRL_CORE_PAD_MCASP4_ACLKX_MCASP4_ACLKX_MUXMODE_I2C4_SDA_4,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MCASP4_FSX,
         CTRL_CORE_PAD_MCASP4_FSX_MCASP4_FSX_MUXMODE_I2C4_SCL_4,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the I2C4 pad*/
    configure_pad(i2c4_pad_config, sizeof (i2c4_pad_config) /
                  sizeof (i2c4_pad_config[0]));
}

void PlatformI2C5SetPinMux(void)
{
    pad_config_t pad_config;
#if defined (SOC_TDA2XX)
    /* I2C5_SDA */
    pad_config.pin_num         = CTRL_CORE_PAD_GPMC_A5;
    pad_config.muxmode         = 7;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;

    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* I2C5_SCL */
    pad_config.pin_num         = CTRL_CORE_PAD_GPMC_A4;
    pad_config.muxmode         = 7;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;

    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
#elif defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    /* I2C5_SDA */
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR0;
    pad_config.muxmode         = 0xA;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;

    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* I2C5_SCL */
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR1;
    pad_config.muxmode         = 0xA;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;

    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

#endif
}

void PlatformUART2SetPinMux(void)
{
    /* Arrary define the PAD properties of uart2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t uart2_pad_config[2] = {
        {CTRL_CORE_PAD_UART2_TXD,
         CTRL_CORE_PAD_UART2_TXD_UART2_TXD_MUXMODE_UART2_TXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_UART2_RXD,
         CTRL_CORE_PAD_UART2_RXD_UART2_RXD_MUXMODE_UART2_RXD_0,
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
#if defined (TDA2XX_MC_BUILD)
    pad_config_t uart3_pad_config[2] = {
        {CTRL_CORE_PAD_UART3_TXD,
         CTRL_CORE_PAD_UART3_TXD_UART3_TXD_MUXMODE_UART3_TXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_UART3_RXD,
         CTRL_CORE_PAD_UART3_RXD_UART3_RXD_MUXMODE_UART3_RXD_0,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
    };
#else
    pad_config_t uart3_pad_config[2] = {
        {CTRL_CORE_PAD_UART2_RTSN,
         CTRL_CORE_PAD_UART2_RTSN_UART2_RTSN_MUXMODE_UART3_TXD_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_UART2_CTSN,
         CTRL_CORE_PAD_UART2_CTSN_UART2_CTSN_MUXMODE_UART3_RXD_2,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
    };
#endif

    /*configure the uart3 pad*/
    configure_pad(uart3_pad_config, sizeof (uart3_pad_config) /
                  sizeof (uart3_pad_config[0]));
}

void PlatformUART4SetPinMux(void)
{
    /* Arrary define the PAD properties of uart4 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t uart4_pad_config[4] = {
        {CTRL_CORE_PAD_RGMII0_TXD3,
         CTRL_CORE_PAD_RGMII0_TXD3_RGMII0_TXD3_MUXMODE_UART4_RXD_8,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_RGMII0_TXD2,
         CTRL_CORE_PAD_RGMII0_TXD2_RGMII0_TXD2_MUXMODE_UART4_TXD_8,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_RGMII0_TXD1,
         CTRL_CORE_PAD_RGMII0_TXD1_RGMII0_TXD1_MUXMODE_UART4_CTSN_8,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_RGMII0_TXD0,
         CTRL_CORE_PAD_RGMII0_TXD0_RGMII0_TXD0_MUXMODE_UART4_RTSN_8,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the uart4 pad*/
    configure_pad(uart4_pad_config, sizeof (uart4_pad_config) /
                  sizeof (uart4_pad_config[0]));
}

void PlatformUART1SetPinMux(void)
{
    /* Arrary define the PAD properties of uart1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t uart1_pad_config[2] = {
        {CTRL_CORE_PAD_UART1_RXD,
         CTRL_CORE_PAD_UART1_RXD_UART1_RXD_MUXMODE_UART1_RXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_UART1_TXD,
         CTRL_CORE_PAD_UART1_TXD_UART1_TXD_MUXMODE_UART1_TXD_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the uart1 pad*/
    configure_pad(uart1_pad_config, sizeof (uart1_pad_config) /
                  sizeof (uart1_pad_config[0]));
}

void PlatformUartConsoleSetPinMux(void)
{
    PlatformUARTSetPinMux(UART1_INST);
}

int32_t PlatformUARTSetPinMux(UART_INST_t num)
{
    int32_t retStatus = 0;
    switch (num)
    {
        case UART1_INST:
            PlatformUART1SetPinMux();
            break;
        case UART3_INST:
            PlatformUART3SetPinMux();
            break;
        case UART4_INST:
            PlatformUART4SetPinMux();
            break;
        default:
            retStatus = (-(int32_t) 1);
            break;
    }

    return retStatus;
}

void PlatformTDA2xxMCSetPinMux(void)
{
    pad_config_t pad_config;

    /* UART1_CTSN  => (gpio7_24) CAM_S1_GPIO_0*/
    pad_config.pin_num         = CTRL_CORE_PAD_UART1_CTSN;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* UART1_RTSN  => (gpio7_25) CAM_S1_GPIO_0*/
    pad_config.pin_num         = CTRL_CORE_PAD_UART1_RTSN;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* I2C2_SDA  => HDMI_SDA*/
    pad_config.pin_num         = CTRL_CORE_PAD_I2C2_SDA;
    pad_config.muxmode         = 1;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* I2C2_SCL  => HDMI_SCL*/
    pad_config.pin_num         = CTRL_CORE_PAD_I2C2_SCL;
    pad_config.muxmode         = 1;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* GPIO6_11  => (GPIO6_11) CAM_S1_RESET*/
    pad_config.pin_num         = CTRL_CORE_PAD_GPIO6_11;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /* CTRL_CORE_PAD_MCASP1_AXR4  => (gpio5_6) CAM_S2_RESET*/
    pad_config.pin_num         = CTRL_CORE_PAD_I2C2_SCL;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /*VIN5A Configuration*/
    /*CAM_S1_D7*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_CLK;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D6*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_CMD;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D5*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT0;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D4*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT1;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D3*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT2;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D2*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT3;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D1*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT4;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D0*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT5;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D8*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP5_AXR1;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D9*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP5_AXR0;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D10*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP5_FSX;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D11*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP5_ACLKX;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D12*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP4_AXR1;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D13*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP4_AXR0;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D14*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP4_FSX;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_D15*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP4_ACLKX;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_HS*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT6;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_VS*/
    pad_config.pin_num         = CTRL_CORE_PAD_MMC3_DAT7;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_PCLK*/
    pad_config.pin_num         = CTRL_CORE_PAD_GPIO6_10;
    pad_config.muxmode         = 9;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S1_RESET*/
    pad_config.pin_num         = CTRL_CORE_PAD_GPIO6_11;
    pad_config.muxmode         = 0;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_GPIO_2*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP2_AXR4;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /*VIN6A Configuration*/
    /*CAM_S2_RESET -> MCASP1_AXR4 (gpio5_6)*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR4;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_PCLK -> XREF_CLK1 (vin6a_clk0)*/
    pad_config.pin_num         = CTRL_CORE_PAD_XREF_CLK1;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_VS -> MCASP1_AXR0 (vin6a_vsync0)*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR0;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_HS -> MCASP1_AXR1 (vin6a_hsync0)*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR1;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_GPIO_0 -> MCASP1_AXR5 (gpio5_7)*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR5;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_GPIO_1 -> MCASP1_AXR6 (gpio5_8)*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR6;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_GPIO_2 -> MCASP1_AXR7 (gpio5_9)*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR7;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /*CAM_S2_D7*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP2_ACLKX;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D6*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP2_FSX;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D5*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP2_AXR2;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D4*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP2_AXR3;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D3*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP3_ACLKX;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D2*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP3_FSX;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D1*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP3_AXR0;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D0*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP3_AXR1;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);

    /*CAM_S2_D8*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR15;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D9*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR14;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D10*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR13;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D11*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR12;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D12*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR11;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D13*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR10;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D14*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR9;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /*CAM_S2_D15*/
    pad_config.pin_num         = CTRL_CORE_PAD_MCASP1_AXR8;
    pad_config.muxmode         = 7;
    pad_config.input_enable    = INPUTENABLE_ENABLE;
    pad_config.pullud_enable   = PULLUDENABLE_DISABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_DOWN;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_SLOW_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
}

void PlatformMMCSD1SetPinMux(void)
{
    /* Arrary define the PAD properties of MMCSD1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mmcsd1_pad_config[6] = {
        {CTRL_CORE_PAD_MMC1_CLK,
         CTRL_CORE_PAD_MMC1_CLK_MMC1_CLK_MUXMODE_MMC1_CLK_0,
         0xff, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_CMD,
         CTRL_CORE_PAD_MMC1_CMD_MMC1_CMD_MUXMODE_MMC1_CMD_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT0,
         CTRL_CORE_PAD_MMC1_DAT0_MMC1_DAT0_MUXMODE_MMC1_DAT0_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT1,
         CTRL_CORE_PAD_MMC1_DAT1_MMC1_DAT1_MUXMODE_MMC1_DAT1_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT2,
         CTRL_CORE_PAD_MMC1_DAT2_MMC1_DAT2_MUXMODE_MMC1_DAT2_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC1_DAT3,
         CTRL_CORE_PAD_MMC1_DAT3_MMC1_DAT3_MUXMODE_MMC1_DAT3_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
    };

    /*configure the MMCSD1 pad*/
    configure_pad(mmcsd1_pad_config, sizeof (mmcsd1_pad_config) /
                  sizeof (mmcsd1_pad_config[0]));
}

void PlatformMMCSD2SetPinMux(void)
{
    /* Arrary define the PAD properties of MMCSD1 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mmcsd2_pad_config[10] = {
        {CTRL_CORE_PAD_GPMC_A19,
         CTRL_CORE_PAD_GPMC_A19_GPMC_A19_MUXMODE_MMC2_DAT4_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A20,
         CTRL_CORE_PAD_GPMC_A20_GPMC_A20_MUXMODE_MMC2_DAT5_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A21,
         CTRL_CORE_PAD_GPMC_A21_GPMC_A21_MUXMODE_MMC2_DAT6_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A22,
         CTRL_CORE_PAD_GPMC_A22_GPMC_A22_MUXMODE_MMC2_DAT7_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A23,
         CTRL_CORE_PAD_GPMC_A23_GPMC_A23_MUXMODE_MMC2_CLK_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A24,
         CTRL_CORE_PAD_GPMC_A24_GPMC_A24_MUXMODE_MMC2_DAT0_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A25,
         CTRL_CORE_PAD_GPMC_A25_GPMC_A25_MUXMODE_MMC2_DAT1_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A26,
         CTRL_CORE_PAD_GPMC_A26_GPMC_A26_MUXMODE_MMC2_DAT2_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_A27,
         CTRL_CORE_PAD_GPMC_A27_GPMC_A27_MUXMODE_MMC2_DAT3_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPMC_CS1,
         CTRL_CORE_PAD_GPMC_CS1_GPMC_CS1_MUXMODE_MMC2_CMD_1,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         0xff, 0xff},
    };

    /*configure the MMCSD1 pad*/
    configure_pad(mmcsd2_pad_config, sizeof (mmcsd2_pad_config) /
                  sizeof (mmcsd2_pad_config[0]));
}

void PlatformMMCSD3SetPinMux(void)
{
    /* Arrary define the PAD properties of MMCSD3 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mmcsd3_pad_config[6] = {
        {CTRL_CORE_PAD_MMC3_CLK,
         CTRL_CORE_PAD_MMC3_CLK_MMC3_CLK_MUXMODE_MMC3_CLK_0,
         0xff, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC3_CMD,
         CTRL_CORE_PAD_MMC3_CMD_MMC3_CMD_MUXMODE_MMC3_CMD_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC3_DAT0,
         CTRL_CORE_PAD_MMC3_DAT0_MMC3_DAT0_MUXMODE_MMC3_DAT0_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC3_DAT1,
         CTRL_CORE_PAD_MMC3_DAT1_MMC3_DAT1_MUXMODE_MMC3_DAT1_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC3_DAT2,
         CTRL_CORE_PAD_MMC3_DAT2_MMC3_DAT2_MUXMODE_MMC3_DAT2_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_MMC3_DAT3,
         CTRL_CORE_PAD_MMC3_DAT3_MMC3_DAT3_MUXMODE_MMC3_DAT3_0,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
    };

    /*configure the MMCSD3 pad*/
    configure_pad(mmcsd3_pad_config, sizeof (mmcsd3_pad_config) /
                  sizeof (mmcsd3_pad_config[0]));
}

void PlatformMMCSD4SetPinMux(void)
{
    /* Arrary define the PAD properties of MMCSD4 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t mmcsd4_pad_config[6] = {
        {CTRL_CORE_PAD_UART1_CTSN,
         CTRL_CORE_PAD_UART1_CTSN_UART1_CTSN_MUXMODE_MMC4_CLK_3,
         0xff, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_UART1_RTSN,
         CTRL_CORE_PAD_UART1_RTSN_UART1_RTSN_MUXMODE_MMC4_CMD_3,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_UART2_RXD,
         CTRL_CORE_PAD_UART2_RXD_UART2_RXD_MUXMODE_MMC4_DAT0_3,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_UART2_TXD,
         CTRL_CORE_PAD_UART2_TXD_UART2_TXD_MUXMODE_MMC4_DAT1_3,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_UART2_CTSN,
         CTRL_CORE_PAD_UART2_CTSN_UART2_CTSN_MUXMODE_MMC4_DAT2_3,
         0xff, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE, 0xff, 0xff},
        {CTRL_CORE_PAD_UART2_RTSN,
         CTRL_CORE_PAD_UART2_RTSN_UART2_RTSN_MUXMODE_MMC4_DAT3_3,
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
        case MMC1_INST:
            PlatformMMCSD1SetPinMux();
            break;
        case MMC4_INST:
            PlatformMMCSD4SetPinMux();
            break;
        default:
            retStatus = (-(int32_t) 1);
            break;
    }

    return retStatus;
}

void PlatformMCASP3SetPinMux(void)
{
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE +
                CTRL_CORE_PAD_MCASP3_ACLKX, 0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE +
                CTRL_CORE_PAD_XREF_CLK2, 0x40003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE +
                CTRL_CORE_PAD_MCASP3_FSX, 0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE +
                CTRL_CORE_PAD_MCASP3_AXR0, 0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE +
                CTRL_CORE_PAD_MCASP3_AXR1, 0xc0000);
}

void PlatformMCSPI1SetPinMux(void)
{
#ifndef SOC_TDA2EX
    /* Remove pad config of CS1 for tda2ex.
     * TODO: Check if this can be removed for tda2xx.
     * STW Examples donot use this pin */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI1_CS1,
                0x60000);
#endif
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI1_CS0,
                0x60000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI1_SCLK,
                0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI1_D1, 0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI1_D0, 0xc0000);
}

void PlatformMCSPI2SetPinMux(void)
{
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI2_CS0,
                0x60000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI2_SCLK,
                0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI2_D1, 0xc0000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_SPI2_D0, 0xc0000);
}

void PlatformMCSPI3SetPinMux(void)
{
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_RGMII0_TXCTL,
                0x60007);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_UART3_RXD,
                0xc0007);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_UART3_TXD,
                0xc0007);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_RGMII0_TXC,
                0xc0007);
}

void PlatformMCSPI4SetPinMux(void)
{
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A11,
                0x60008);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A8,
                0xc0008);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A9,
                0xc0008);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A10,
                0xc0008);
}

void PlatformGPIOInputOutputSetPinMux(void)
{
    PlatformGPIO1SetPinMux();
}

void PlatformGPIO1SetPinMux(void)
{
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_DCAN1_TX,
                (0x60000U | CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_MUXMODE_GPIO1_14_14));
}

void PlatformDCAN2SetPinMux(void)
{
    /* Arrary define the PAD properties of uart2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan2_pad_config[2] = {
        {CTRL_CORE_PAD_GPIO6_14,
         CTRL_CORE_PAD_GPIO6_14_GPIO6_14_MUXMODE_DCAN2_TX_2,
         0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_GPIO6_15,
         CTRL_CORE_PAD_GPIO6_15_GPIO6_15_MUXMODE_DCAN2_RX_2,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan2 pad*/
    configure_pad(dcan2_pad_config, sizeof (dcan2_pad_config) /
                  sizeof (dcan2_pad_config[0]));
}

void PlatformDCAN1SetPinMux(void)
{
    /* Arrary define the PAD properties of uart2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan1_pad_config[2] = {
        {CTRL_CORE_PAD_DCAN1_TX,
         CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_MUXMODE_DCAN1_TX_0,
         0xff, 0xff, 0xff,
         0xff, 0xff},
        {CTRL_CORE_PAD_WAKEUP0,
         CTRL_CORE_PAD_WAKEUP0_WAKEUP0_MUXMODE_DCAN1_RX_1,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan1 pad*/
    configure_pad(dcan1_pad_config, sizeof (dcan1_pad_config) /
                  sizeof (dcan1_pad_config[0]));
}

void PlatformRGMIISetPinMux(void)
{
    PlatformRGMII0SetPinMux();
}

void PlatformDCAN1RXSetPinMux(void)
{
    /* Arrary define the PAD properties of uart2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan1_pad_config[1] = {
        {CTRL_CORE_PAD_WAKEUP0,
         CTRL_CORE_PAD_WAKEUP0_WAKEUP0_MUXMODE_DRIVEROFF_0XF,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan1 pad*/
    configure_pad(dcan1_pad_config, sizeof (dcan1_pad_config) /
                  sizeof (dcan1_pad_config[0]));
}

void PlatformDCAN2RXSetPinMux(void)
{
    /* Arrary define the PAD properties of uart2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t dcan2_pad_config[1] = {
        {CTRL_CORE_PAD_GPIO6_15,
         CTRL_CORE_PAD_GPIO6_15_GPIO6_15_MUXMODE_DRIVEROFF_0XF,
         0xff, 0xff, 0xff,
         0xff, 0xff},
    };
    /*configure the dcan2 pad*/
    configure_pad(dcan2_pad_config, sizeof (dcan2_pad_config) /
                  sizeof (dcan2_pad_config[0]));
}

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */

void HAL_CTRL_ConfigurePadsQspi(void)
{
    cntrl_core_qspi_pad_config();
} /* HAL_CTRL_ConfigurePadsQspi */

void UART_PAD_CONFIG(void)
{
    PlatformUART1SetPinMux();
}

void cntrl_core_uart1_pad_config(void)
{
    PlatformUART1SetPinMux();
}

void Uart1_Pin_Mux(void)
{
    PlatformUART1SetPinMux();
}

void Uart3_Pin_Mux(void)
{
    PlatformUART3SetPinMux();
}

void Uart4_Pin_Mux(void)
{
    PlatformUART4SetPinMux();
}

int32_t Uart_Pin_Mux(UART_INST_t num)
{
    int32_t retStatus = 0;
    switch (num)
    {
        case UART1_INST:
            Uart1_Pin_Mux();
            break;
        case UART2_INST:
            break;
        case UART3_INST:
            Uart3_Pin_Mux();
            break;
        case UART4_INST:
            Uart4_Pin_Mux();
            break;
        default:
            retStatus = (-(int32_t) 1);
            break;
    }

    return retStatus;
}

void cntrl_core_qspi_pad_config(void)
{
    PlatformQSPISetPinMux();
}

void cntrl_core_gpmc_pad_config(void)
{
    PlatformGPMCSetPinMux();
}

void cntrl_core_gpmc_pad_config_addr_lines(void)
{
    PlatformGPMCSetPinMuxAddrLines();
}

void cntrl_core_mmc1_pad_config(void)
{
    PlatformMMC1SetPinMux();
}

void cntrl_core_i2c2_pad_config(void)
{
    PlatformI2C2SetPinMux();
}

void cntrl_core_vin1_pad_config(void)
{
    PlatformVIN1SetPinMux();
}

void cntrl_core_vin2_pad_config(void)
{
    PlatformVIN2SetPinMux();
}

void cntrl_core_lcd_pad_config(void)
{
    PlatformLCDSetPinMux();
}

void cntrl_core_rgmii_pad_config(void)
{
    PlatformRGMIISetPinMux();
}

/* ************** Legacy functions -let to clean-it up ********************* */

/* Configuring PAD in any module or application */

void I2C2_Pin_Mux(void)
{
    /* Arrary define the PAD properties of I2C2 pins*/
    /*Pin_num,Muxmode,pullud_enable,pull_typeselect,io,slewrate,wakeupmode*/
    pad_config_t i2c2_pad_config[2] = {
        {CTRL_CORE_PAD_I2C2_SDA,
         CTRL_CORE_PAD_I2C2_SDA_I2C2_SDA_MUXMODE_I2C2_SDA_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_I2C2_SCL,
         CTRL_CORE_PAD_I2C2_SCL_I2C2_SCL_MUXMODE_I2C2_SCL_0,
         PULLUDENABLE_ENABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_DISABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /*configure the I2C2 pad*/
    configure_pad(i2c2_pad_config, sizeof (i2c2_pad_config) /
                  sizeof (i2c2_pad_config[0]));
}

void I2C1_Pin_Mux(void)
{
    PlatformI2C1SetPinMux();
}

void I2C4_Pin_Mux(void)
{
    PlatformI2C4SetPinMux();
}

void MMCSD1_Pin_Mux(void)
{
    PlatformMMCSD1SetPinMux();
}

void MMCSD3_Pin_Mux(void)
{
    PlatformMMCSD3SetPinMux();
}

void MMCSD4_Pin_Mux(void)
{
    PlatformMMCSD4SetPinMux();
}

int32_t MMCSD_Pin_Mux(MMC_INST_t num)
{
    int32_t retStatus = 0;
    switch (num)
    {
        case MMC1_INST:
            PlatformMMCSD1SetPinMux();
            break;
        case MMC4_INST:
            PlatformMMCSD4SetPinMux();
            break;
        default:
            retStatus = (-(int32_t) 1);
            break;
    }

    return retStatus;
}

void MCASP3_pad_mux_config(void)
{
    PlatformMCASP3SetPinMux();
}

void MCSPI1_pad_mux_config(void)
{
    PlatformMCSPI1SetPinMux();
}

void MCSPI2_pad_mux_config(void)
{
    PlatformMCSPI2SetPinMux();
}

#if defined (SOC_TDA2PX)
void PlatformDCAN1PadConfig(void)
{
    /* Configure dcan_tx, dcan_rx pads */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE+CTRL_CORE_CONTROL_SPARE_RW,
        CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN,
        CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_DCAN_PADS);

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_DCAN1_TX,
                (((uint32_t)CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_INPUTENABLE_ENABLE
                  << CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_INPUTENABLE_SHIFT) |
                 ((uint32_t)CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_PULLTYPESELECT_PULL_UP
                  << CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_PULLTYPESELECT_SHIFT)));
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_DCAN1_RX,
                (((uint32_t)CTRL_CORE_PAD_DCAN1_RX_DCAN1_RX_INPUTENABLE_ENABLE
                  << CTRL_CORE_PAD_DCAN1_RX_DCAN1_RX_INPUTENABLE_SHIFT) |
                 ((uint32_t)CTRL_CORE_PAD_DCAN1_RX_DCAN1_RX_PULLTYPESELECT_PULL_UP
                  << CTRL_CORE_PAD_DCAN1_RX_DCAN1_RX_PULLTYPESELECT_SHIFT)));

}
#endif
