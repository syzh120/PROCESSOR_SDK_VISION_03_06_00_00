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
 *  \file utils_fpga.c
 *
 *  \brief Cascade Radar sample application FPGA Utilities.
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <CascadeFlashFpga_main.h>

#define UTILS_FPGA_CRESET_BASE        (SOC_GPIO7_BASE)
#define UTILS_FPGA_CRESET_PAD         (CTRL_CORE_PAD_UART2_TXD)
#define UTILS_FPGA_CRESET_PIN         (27U)

#define UTILS_FPGA0_NRST_BASE         (SOC_GPIO3_BASE)
#define UTILS_FPGA0_NRST_PAD          (CTRL_CORE_PAD_VIN1A_FLD0)
#define UTILS_FPGA0_NRST_PIN          (1U)

#define UTILS_FPGA1_NRST_BASE         (SOC_GPIO3_BASE)
#define UTILS_FPGA1_NRST_PAD          (CTRL_CORE_PAD_VIN2A_FLD0)
#define UTILS_FPGA1_NRST_PIN          (30U)

#define UTILS_FPGA2_NRST_BASE         (SOC_GPIO2_BASE)
#define UTILS_FPGA2_NRST_PAD          (CTRL_CORE_PAD_GPMC_A11)
#define UTILS_FPGA2_NRST_PIN          (1U)

#define UTILS_FPGA2_MUX_BASE          (SOC_GPIO2_BASE)
#define UTILS_FPGA2_MUX_PAD           (CTRL_CORE_PAD_GPMC_CS1)
#define UTILS_FPGA2_MUX_PIN           (18U)

#define UTILS_FPGA3_NRST_BASE         (SOC_GPIO6_BASE)
#define UTILS_FPGA3_NRST_PAD          (CTRL_CORE_PAD_GPIO6_16)
#define UTILS_FPGA3_NRST_PIN          (16U)

void Utils_fgpaPowerUp(void)
{
    pad_config_t gpio_pad_config[] =
    {
        {
            UTILS_FPGA_CRESET_PAD,
            0xE,
            PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
            SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE
        }
    };
	configure_pad(gpio_pad_config, sizeof (gpio_pad_config) /
              sizeof (gpio_pad_config[0]));
	GPIOModuleEnable(UTILS_FPGA_CRESET_BASE);
	GPIODirModeSet(
			UTILS_FPGA_CRESET_BASE,
			UTILS_FPGA_CRESET_PIN,
			GPIO_DIR_OUTPUT);

	GPIOPinWrite(UTILS_FPGA_CRESET_BASE,
                 UTILS_FPGA_CRESET_PIN,1);
	BspOsal_sleep(100);
	GPIOPinWrite(UTILS_FPGA_CRESET_BASE,
                 UTILS_FPGA_CRESET_PIN,0);
	BspOsal_sleep(100);
	GPIOPinWrite(UTILS_FPGA_CRESET_BASE,
                 UTILS_FPGA_CRESET_PIN,1);
}

Int32 Utils_fpgaStart(UInt32 fpgaNum)
{
    Int32 retVal = BSP_SOK;
    UInt32 padNum = 0;
    UInt32 baseAddr = 0;
    UInt32 pinNum = 0;
    UInt32 muxPadNum = 0;
    UInt32 muxBaseAddr = 0;
    UInt32 muxPinNum = 0;
    UInt32 muxReqd = 0;
    pad_config_t gpio_pad_config[] =
    {
        {
            0,
            0xE,
            PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
            SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE
        }
    };
	switch (fpgaNum)
    {
        case 0:
            padNum      = UTILS_FPGA0_NRST_PAD;
            baseAddr    = UTILS_FPGA0_NRST_BASE;
            pinNum      = UTILS_FPGA0_NRST_PIN;
            break;
        case 1:
            padNum      = UTILS_FPGA1_NRST_PAD;
            baseAddr    = UTILS_FPGA1_NRST_BASE;
            pinNum      = UTILS_FPGA1_NRST_PIN;
            break;
        case 2:
            padNum      = UTILS_FPGA2_NRST_PAD;
            baseAddr    = UTILS_FPGA2_NRST_BASE;
            pinNum      = UTILS_FPGA2_NRST_PIN;
            muxReqd = 1;
            muxPadNum   = UTILS_FPGA2_MUX_PAD;
            muxBaseAddr = UTILS_FPGA2_MUX_BASE;
            muxPinNum   = UTILS_FPGA2_MUX_PIN;
            break;
        case 3:
            padNum      = UTILS_FPGA3_NRST_PAD;
            baseAddr    = UTILS_FPGA3_NRST_BASE;
            pinNum      = UTILS_FPGA3_NRST_PIN;
            break;
        default:
            GT_0trace(BspAppTrace, GT_INFO,
                " UTILS_FPGA: Incorrect FPGA Number!!\r\n");
            retVal = BSP_EFAIL;
    }
    if (retVal == BSP_SOK)
    {
        if (muxReqd == 1)
        {
            gpio_pad_config[0].pin_num = muxPadNum;
            configure_pad(gpio_pad_config, sizeof (gpio_pad_config) /
              sizeof (gpio_pad_config[0]));
            GPIOModuleEnable(muxBaseAddr);
            GPIODirModeSet(
                    muxBaseAddr,
                    muxPinNum,
                    GPIO_DIR_OUTPUT);

            GPIOPinWrite(muxBaseAddr,
                         muxPinNum,0);
        }
        gpio_pad_config[0].pin_num = padNum;
        configure_pad(gpio_pad_config, sizeof (gpio_pad_config) /
              sizeof (gpio_pad_config[0]));
        GPIOModuleEnable(baseAddr);
        GPIODirModeSet(
                baseAddr,
                pinNum,
                GPIO_DIR_OUTPUT);

        GPIOPinWrite(baseAddr,
                     pinNum,1);
        BspOsal_sleep(100);
        GPIOPinWrite(baseAddr,
                     pinNum,0);
        BspOsal_sleep(100);
        GPIOPinWrite(baseAddr,
                     pinNum,1);
    }
    return retVal;
}
