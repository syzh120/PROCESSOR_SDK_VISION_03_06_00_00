/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *   \file    device.c
 *
 *   \brief   API's
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "device.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define MAX_DELAY   0x900

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void UTIL_waitLoop(uint32_t loopcnt)
{
    uint32_t i;
    for (i = 0; i < loopcnt; i++)
    {
        asm ("   NOP");
    }
}

void GPMC_Write(uint32_t offset, uint32_t val)
{
    *(volatile uint32_t *) (GPMC_BASE + offset) = val;
}

void GPMC_CSWrite(uint8_t cs, uint32_t offset, uint32_t val)
{
    *(volatile uint32_t *) (GPMC_CONFIG_CS0_BASE +
                            (GPMC_CS_CONFIG_SIZE * cs) + offset) = val;
}

uint32_t GPMC_Read(uint32_t offset)
{
    return (*(volatile uint32_t *) (GPMC_BASE + offset));
}

/* make sure compiler doesnt optimize this function */
uint32_t DEVICE_Delay(uint32_t delay)
{
    UTIL_waitLoop(delay * 0x100);
    return 0;
}

/*********************************************************************
 *
 * GPMC_Init - Initialize GPMC based on CS and config values
 *
 *********************************************************************/
void GPMC_Init(GPMC_Config_t *cfg, uint8_t cs)
{
    uint8_t i;

    /* program global GPMC regs */
    GPMC_Write(GPMC_SYSCONFIG_OFF, cfg->SysConfig);
    GPMC_Write(GPMC_IRQENABLE_OFF, cfg->IrqEnable);
    GPMC_Write(GPMC_TIMEOUTCTRL_OFF, cfg->TimeOutControl);
    GPMC_Write(GPMC_CONFIG_OFF, cfg->Config);

    /* program GPMC CS specific registers */
    /* disable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, 0x00000000);
    DEVICE_Delay(MAX_DELAY);

    /* program new set of config values (1 to 7) */
    for (i = 0; i < GPMC_MAX_CS; i++) {
        GPMC_CSWrite(cs, (i * 4), cfg->ChipSelectConfig[i]);
    }

    /* enable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, (cfg->ChipSelectConfig[6] | 0x40));
    DEVICE_Delay(MAX_DELAY);
}
/***************************** End Of File ***********************************/

