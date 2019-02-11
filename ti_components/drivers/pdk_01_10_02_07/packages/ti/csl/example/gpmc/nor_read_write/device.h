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
 * \file  device.h
 * \brief      
 */
#ifndef DEVICE_H_
#define DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* GPMC MMR */
#define GPMC_BASE                     0x50000000
#define GPMC_SYSCONFIG_OFF            0x10
#define GPMC_IRQSTS_OFF               0x18
#define GPMC_IRQENABLE_OFF            0x1c
#define GPMC_TIMEOUTCTRL_OFF          0x40
#define GPMC_CONFIG_OFF               0x50
#define GPMC_CONFIG_CS0_BASE          (GPMC_BASE + 0x60)
#define GPMC_CS_CONFIG_SIZE           0x30
#define GPMC_MAX_CS                   7

#define GPMC_CONFIG1_OFF              0x00
#define GPMC_CONFIG2_OFF              0x04
#define GPMC_CONFIG3_OFF              0x08
#define GPMC_CONFIG4_OFF              0x0C
#define GPMC_CONFIG5_OFF              0x10
#define GPMC_CONFIG6_OFF              0x14
#define GPMC_CONFIG7_OFF              0x18

/* NOR Base address */
#define NOR_BASE                      0x08000000

/* GPMC Chip Select configuration passed to gpmc_SetCSConfig */
typedef struct {
    uint32_t Config1;
    uint32_t Config2;
    uint32_t Config3;
    uint32_t Config4;
    uint32_t Config5;
    uint32_t Config6;
    uint32_t Config7;
} GPMC_CsConfig_t;

/* GPMC Configuration passed to GPMC_SetConfig in order to configure the GPMC
 * The structure is also used by the CHFLASH Configuration Header */
typedef struct
{
    uint32_t SysConfig;
    uint32_t IrqEnable;
    uint32_t TimeOutControl;
    uint32_t Config;
    uint32_t ChipSelectConfig[GPMC_MAX_CS];
    uint32_t PrefetchConfig1;
    uint32_t PrefetchConfig2;
    uint32_t PrefetchControl;
}GPMC_Config_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void GPMC_Init(GPMC_Config_t *cfg, uint8_t cs);

#ifdef __cplusplus
}
#endif

#endif
/********************************* End of file ******************************/
