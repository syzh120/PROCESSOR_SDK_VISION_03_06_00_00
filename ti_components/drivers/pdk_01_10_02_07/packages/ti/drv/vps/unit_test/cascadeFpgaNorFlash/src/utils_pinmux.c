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

#include <CascadeFlashFpga_main.h>

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

void CascadeFlashFpga_InitPadMuxSPIFlash (void)
{
    pad_config_t gpio_pad_config[] =
    {
        {CTRL_CORE_PAD_MMC3_DAT7,     /* SPI4 - SPI4_CS_MUX */
         0x1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MMC3_CLK,     /* GPIO6_29 */
         0xE,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MCASP2_AXR2,     /* GPIO6_8 */
         0xE,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MCASP1_AXR10,  /* GPIO5_12 */
         0xE,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MCASP1_AXR11,  /* GPIO4_17 */
         0xE,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_UP, INPUTENABLE_ENABLE,
         SLEWCONTROL_SLOW_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MMC3_DAT5,     /* SPI4_MOSI */
         0x1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MMC3_DAT6,     /* SPI4_MISO */
         0x1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
        {CTRL_CORE_PAD_MMC3_DAT4,     /* SPI4_SCLK */
         0x1,
         PULLUDENABLE_DISABLE, PULLTYPESELECT_PULL_DOWN, INPUTENABLE_ENABLE,
         SLEWCONTROL_FAST_SLEW, WAKEUPENABLE_DISABLE},
    };

    /* configure the gpio pad */
    configure_pad(gpio_pad_config, sizeof (gpio_pad_config) /
              sizeof (gpio_pad_config[0]));
}
