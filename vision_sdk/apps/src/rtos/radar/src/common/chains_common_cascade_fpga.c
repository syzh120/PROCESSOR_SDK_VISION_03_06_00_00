/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *  \file chains_common_cascade_fpga.c
 *
 *  \brief Cascade Radar sample application FPGA Utilities.
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/common/chains_radar.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_gpio.h>

#define CHAINS_COMMON_CASCADE_FPGA0_NRST_BASE         (SOC_GPIO3_BASE)
#define CHAINS_COMMON_CASCADE_FPGA0_NRST_PAD          (CTRL_CORE_PAD_VIN1A_FLD0)
#define CHAINS_COMMON_CASCADE_FPGA0_NRST_PIN          (1U)

#define CHAINS_COMMON_CASCADE_FPGA1_NRST_BASE         (SOC_GPIO3_BASE)
#define CHAINS_COMMON_CASCADE_FPGA1_NRST_PAD          (CTRL_CORE_PAD_VIN2A_FLD0)
#define CHAINS_COMMON_CASCADE_FPGA1_NRST_PIN          (30U)

#define CHAINS_COMMON_CASCADE_FPGA2_NRST_BASE         (SOC_GPIO2_BASE)
#define CHAINS_COMMON_CASCADE_FPGA2_NRST_PAD          (CTRL_CORE_PAD_GPMC_A11)
#define CHAINS_COMMON_CASCADE_FPGA2_NRST_PIN          (1U)

#define CHAINS_COMMON_CASCADE_FPGA2_MUX_BASE          (SOC_GPIO2_BASE)
#define CHAINS_COMMON_CASCADE_FPGA2_MUX_PAD           (CTRL_CORE_PAD_GPMC_CS1)
#define CHAINS_COMMON_CASCADE_FPGA2_MUX_PIN           (18U)

#define CHAINS_COMMON_CASCADE_FPGA3_NRST_BASE         (SOC_GPIO6_BASE)
#define CHAINS_COMMON_CASCADE_FPGA3_NRST_PAD          (CTRL_CORE_PAD_GPIO6_16)
#define CHAINS_COMMON_CASCADE_FPGA3_NRST_PIN          (16U)

Int32 ChainsCommon_fpgaPowerUp(UInt32 fpgaNum)
{
    Int32 retVal = BSP_SOK;
    UInt32 fpgaCResetPad;
    UInt32 fpgaCResetGpioBase;
    UInt32 fpgaCResetGpioNum;
    pad_config_t gpio_pad_config[] =
    {
        {
            0,
            0xE,
            PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
            SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE
        }
    };

    if (Bsp_boardGetBaseBoardRev() >= BSP_BOARD_REV_E)
    {
        switch(fpgaNum)
        {
            case 0U:
                fpgaCResetPad = CTRL_CORE_PAD_MCASP1_ACLKX;
                fpgaCResetGpioBase = SOC_GPIO7_BASE;
                fpgaCResetGpioNum = 31U;
                break;
            case 1U:
                fpgaCResetPad = CTRL_CORE_PAD_MCASP1_FSX;
                fpgaCResetGpioBase = SOC_GPIO7_BASE;
                fpgaCResetGpioNum = 30U;
                break;
            case 2U:
                fpgaCResetPad = CTRL_CORE_PAD_MCASP3_ACLKX;
                fpgaCResetGpioBase = SOC_GPIO5_BASE;
                fpgaCResetGpioNum = 13U;
                break;
            case 3U:
                fpgaCResetPad = CTRL_CORE_PAD_MCASP3_FSX;
                fpgaCResetGpioBase = SOC_GPIO5_BASE;
                fpgaCResetGpioNum = 14U;
                break;
            default:
                Vps_printf("CHAINS_COMMON_CASCADE_FPGA: Incorrect FPGA Number!!\r\n");
                retVal = BSP_EFAIL;
                break;
        }
    }
    else
    {
        fpgaCResetPad = CTRL_CORE_PAD_UART2_TXD;
        fpgaCResetGpioBase = SOC_GPIO7_BASE;
        fpgaCResetGpioNum = 27U;
    }

    gpio_pad_config[0].pin_num = fpgaCResetPad;
    configure_pad(gpio_pad_config, sizeof (gpio_pad_config) /
              sizeof (gpio_pad_config[0]));
    GPIOModuleEnable(fpgaCResetGpioBase);
    GPIODirModeSet(
            fpgaCResetGpioBase,
            fpgaCResetGpioNum,
            GPIO_DIR_OUTPUT);

    GPIOPinWrite(fpgaCResetGpioBase,
                 fpgaCResetGpioNum,1);
    BspOsal_sleep(100);
    GPIOPinWrite(fpgaCResetGpioBase,
                 fpgaCResetGpioNum,0);
    BspOsal_sleep(100);
    GPIOPinWrite(fpgaCResetGpioBase,
                 fpgaCResetGpioNum,1);

    return retVal;
}

Int32 ChainsCommon_fpgaStart(UInt32 fpgaNum)
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
            padNum      = CHAINS_COMMON_CASCADE_FPGA1_NRST_PAD;
            baseAddr    = CHAINS_COMMON_CASCADE_FPGA1_NRST_BASE;
            pinNum      = CHAINS_COMMON_CASCADE_FPGA1_NRST_PIN;
            break;
        case 1:
            padNum      = CHAINS_COMMON_CASCADE_FPGA2_NRST_PAD;
            baseAddr    = CHAINS_COMMON_CASCADE_FPGA2_NRST_BASE;
            pinNum      = CHAINS_COMMON_CASCADE_FPGA2_NRST_PIN;
            muxReqd = 1;
            muxPadNum   = CHAINS_COMMON_CASCADE_FPGA2_MUX_PAD;
            muxBaseAddr = CHAINS_COMMON_CASCADE_FPGA2_MUX_BASE;
            muxPinNum   = CHAINS_COMMON_CASCADE_FPGA2_MUX_PIN;
            break;
        case 2:
            padNum      = CHAINS_COMMON_CASCADE_FPGA3_NRST_PAD;
            baseAddr    = CHAINS_COMMON_CASCADE_FPGA3_NRST_BASE;
            pinNum      = CHAINS_COMMON_CASCADE_FPGA3_NRST_PIN;
            break;
        case 3:
            padNum      = CHAINS_COMMON_CASCADE_FPGA0_NRST_PAD;
            baseAddr    = CHAINS_COMMON_CASCADE_FPGA0_NRST_BASE;
            pinNum      = CHAINS_COMMON_CASCADE_FPGA0_NRST_PIN;
            break;
        default:
            Vps_printf("CHAINS_COMMON_CASCADE_FPGA: Incorrect FPGA Number!!\r\n");
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

