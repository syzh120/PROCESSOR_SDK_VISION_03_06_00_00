/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *   \file    main.c
 *
 *   \brief   Test application for NOR read and write
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include <ti/csl/csl_types.h>
#include "device.h"
#include "nor.h"
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_gpmc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define BUF_SIZE (32 * 1024)
#define GPMC_CS0 0
#define FLASH_BLOCK_SIZE (128 * 1024)

#if !defined (__ARM_ARCH_7A__) && !defined (BUILD_GCC)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuffm, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t       _srcBuffm[FLASH_BLOCK_SIZE];
#else
uint8_t __attribute__((section(".my_sect_ddr"))) _srcBuffm[FLASH_BLOCK_SIZE];
#endif

/*To use UARTConfigPuts function for prints*/
#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
uint32_t uartBaseAddr = CSL_MPU_UART1_REGS;
#endif
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
signed char  *srcBuffm;
unsigned int  NORStart = NOR_BASE;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void NorTest(void);
static int32_t local_DEBUGprintString(const char *s);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
 void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /*Pad configurations */
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD,0x00000000);
    /*Pad configurations*/
    /*GPMC Data lines AD0-AD15*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD0,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD1,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD2,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD3,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD4,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD5,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD6,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD7,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD8,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD9,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD10,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD11,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD12,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD13,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD14,0x00050000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_AD15,0x00050000);
    /*GPMC Add lines A0-A27*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A0,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A1,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A2,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A3,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A4,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A5,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A6,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A7,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A8,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A9,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A10,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A11,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A12,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A13,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A14,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A15,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A16,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A17,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A18,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A19,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A20,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A21,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A22,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A23,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A24,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A25,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A26,0x00040000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A27,0x00040000);
   /*GPMC chip select*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_CS0,0x00060000);
     /*GPMC control lines*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_ADVN_ALE,0x00060000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_OEN_REN,0x00070000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_WEN,0x00070000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_BEN0,0x00070000);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_WAIT0,0x000F0000);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
/*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /*Pad configurations*/
    /*GPMC Data lines AD0-AD15*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD0,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD1,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD2,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD3,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD4,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD5,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD6,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD7,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD8,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD9,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD10,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD11,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD12,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD13,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD14,0x00050000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_AD15,0x00050000);
    /*GPMC Add lines A0-A27*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A1,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A2,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A3,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A4,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A5,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A6,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A7,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A8,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A9,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A10,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A11,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A12,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A13,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A14,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A15,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A16,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A17,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A18,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A19,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A20,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A21,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A22,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A23,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A24,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A25,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A26,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A27,0x00040000);
   /*GPMC chip select*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_CS0,0x00060000);
     /*GPMC control lines*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_ADVN_ALE,0x00060000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_OEN_REN,0x00070000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_WEN,0x00070000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_BEN0,0x00070000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_WAIT0,0x000F0000);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /*Pad configurations*/
    /*GPMC Data lines AD0-AD15*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD1,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD2,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD3,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD4,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD5,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD6,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD7,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD8,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD9,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD10,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD11,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD12,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD13,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD14,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_AD15,0x00040000);
    /*GPMC Add lines A0-A27*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D16,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D17,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D18,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D19,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D20,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D21,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D22,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D23,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D8,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D9,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D10,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D11,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D12,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D13,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D14,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VIN1A_D15,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_CTSN,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RTSN,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART2_CTSN,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART2_RTSN,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D8,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D9,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D10,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D11,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D12,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D13,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D14,0x00040003);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_VOUT1_D15,0x00040003);
   /*GPMC chip select*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS0,0x00040000);
     /*GPMC control lines*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_ADVN_ALE,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_OEN_REN,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_WEN,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_BEN0,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_WAIT0,0x00040000);
#endif
}

static int32_t local_DEBUGprintString(const char *s)
{
#if !defined (__ARM_ARCH_7A__)
    printf(s);
#else
    UARTConfigPuts(uartBaseAddr,(char *)s, -1);
#endif
    return TRUE;
}

GPMC_Config_t GPMC_ConfigNorDefault = {
    /* SysConfig - ROM Code defaults */
    0x0,           /*0x0008,*/
    /* IRQEnable - ROM Code defaults */
    0x0000,
    /* TimeOutControl - ROM Code defaults */
    0xf01f0000,
    /* Config - ROM Code defaults */
    0x000a0000,
    {
        0x00001010,
        0x001e1e01,
        0x00090907,
        0xf071d0b,
        0x001c1f1f,
        0x8f070080,
        0x00000f48,
    },
};

int main(void)
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    uint32_t           baseAddr = CSL_MPU_GPMC_CONF_REGS_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t           baseAddr = SOC_GPMC_CONF_REGS_BASE;
#endif
    Nor_InitPrms_t     Nor_InitPrms;

    /*MMC1 PAD Configuration*/
    padConfig_prcmEnable();

    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);

    GPMC_Init(&GPMC_ConfigNorDefault, GPMC_CS0);

    /* FOLLOWING IS NOR CHIP-SELECT CONFIGURATION */

    /* Select the chip-select base address, chip addr needs to be given */
    GPMCBaseAddrSet(baseAddr, GPMC_CHIP_SELECT_0, 0x00000008);

    /* Select the chip-select mask address */
    GPMCMaskAddrSet(baseAddr, GPMC_CHIP_SELECT_0, GPMC_CS_SIZE_64MB);

    UARTConfigPuts(uartBaseAddr,"\nNOR Flash Test App", -1);

    /* Initialize function pointer Default */
    NOR_InitParmsDefault(&Nor_InitPrms);

    Nor_InitPrms.norFlashInitPrintFxnPtr =
        (NOR_FlashInitPrintFxnPtr) (&local_DEBUGprintString);
    /* Initialize function pointer Default */
    NOR_Init(&Nor_InitPrms);

    /* Function to Test NOR Flash */
    NorTest();

    return 0;
}

static void NorTest(void)
{
    NOR_InfoHandle    hNorInfo;
    uint32_t          baseAddress = 0;
    uint32_t          blockSize, blockAddr;
    uint32_t          count, i, k;
    uint32_t          flash_size;
    volatile uint32_t dstOffsetAddr;
    uint32_t          offset_addr, buf_size;
    signed char      *dst_addr;
    volatile uint32_t norTest = 0;
    uint32_t          retVal  = TRUE;

    srcBuffm = (signed char *) (_srcBuffm);

    while (1) {
        UARTConfigPuts(uartBaseAddr,
            "\nEnter the testcase number\n1: Read Manufacturer ID and Device ID of NOR\n2: Erase, Write/Read and Verify 1 block of NOR flash\n3: Erase, Write/Read and Verify entire NOR flash\nAny other number to quit\n",
            -1);
        norTest = UARTConfigGetNum(uartBaseAddr);
        UARTConfigPuts(uartBaseAddr,"\n", -1);
        if (norTest == 1)
        {
            UARTConfigPuts(uartBaseAddr,
                "Running Test Case 1: Read Manufacturer ID and Device ID of NOR\n",
                -1);
            /* Initialize NOR Flash */
            hNorInfo = NOR_open(NORStart, 2 /* 16 Bit */);
            if (hNorInfo == NULL)
            {
                UARTConfigPuts(uartBaseAddr,"\tERROR: NOR Initialization failed.\r\n", -1);
                retVal = FALSE;
                break;
            }
            else
            {
                UARTConfigPuts(uartBaseAddr,"\nTest Passed.\n", -1);
            }
        }
        else if (norTest == 2)
        {
            UARTConfigPuts(uartBaseAddr,
                "\nRunning Test Case 2:Erase, Write/Read and Verify 1 block of NOR flash\n",
                -1);
            hNorInfo = NOR_open(NORStart, 2 /* 16 Bit */);
            if (hNorInfo == NULL)
            {
                UARTConfigPuts(uartBaseAddr,"\tERROR: NOR Initialization failed.\r\n", -1);
                retVal = FALSE;
                break;
            }
            /* Get NOR block size */
            NOR_getBlockInfo(hNorInfo, NORStart, &blockSize,
                             &blockAddr);

            /* Set base address to start putting data at */
            baseAddress = hNorInfo->flashBase;

            /*Erase the entire NOR Flash*/
            if (NOR_erase(hNorInfo, baseAddress, FLASH_BLOCK_SIZE) != TRUE)
            {
                UARTConfigPuts(uartBaseAddr,"\tERROR: Erasing NOR failed.\r\n", -1);
                retVal = FALSE;
                break;
            }

            /*
             * Initialize the source address with a pattern
             * initialize dst address with zero/another pattern (optional)
             */

            for (count = 0U; count < (FLASH_BLOCK_SIZE); count++)
            {
                srcBuffm[count] = (int) 0x55;
            }
            offset_addr = baseAddress;

            dstOffsetAddr = offset_addr;
            dst_addr      = (signed char *) dstOffsetAddr;

            /* Write the data pattern to the flash */
            if (NOR_writeBytes(hNorInfo, dstOffsetAddr, FLASH_BLOCK_SIZE,
                               (uint32_t) srcBuffm) != TRUE)
            {
                UARTConfigPuts(uartBaseAddr,"\tERROR: Writing NOR failed.\n", -1);
                retVal = FALSE;
                break;
            }

            for (i = 0; i < (FLASH_BLOCK_SIZE); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = FALSE;
                    UARTConfigPuts(uartBaseAddr,"\nError matching value at src and dst address\n",
                             -1);
                    UARTConfigPuts(uartBaseAddr,"Value at src address ", -1);
                    UARTConfigPutNum(uartBaseAddr,(uint32_t) &srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutNum(uartBaseAddr,srcBuffm[i]);
                    UARTConfigPuts(uartBaseAddr,"\nValue at dst address ", -1);
                    UARTConfigPutNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
                    UARTConfigPuts(uartBaseAddr," is:", -1);
                    UARTConfigPutNum(uartBaseAddr,dst_addr[i]);
                    break;
                }
            }
            if (retVal == FALSE)
            {
                UARTConfigPuts(uartBaseAddr,"\nError testing block : ", -1);
                UARTConfigPuts(uartBaseAddr,"\nTest Failed.\n", -1);
                break;
            }
            else
            {
                UARTConfigPuts(uartBaseAddr,"\nTest Passed.\n", -1);
            }
        }
        else if (norTest == 3)
        {
            UARTConfigPuts(uartBaseAddr,
                "\nRunning Test Case 3: Erase, Write/Read and Verify entire NOR flash",
                -1);
            hNorInfo = NOR_open(NORStart, 2 /* 16 Bit */);
            if (hNorInfo == NULL)
            {
                UARTConfigPuts(uartBaseAddr,"\tERROR: NOR Initialization failed.\r\n", -1);
                retVal = FALSE;
                break;
            }
            /* Get NOR block size */
            NOR_getBlockInfo(hNorInfo, NORStart, &blockSize,
                             &blockAddr);

            UARTConfigPuts(uartBaseAddr,"NOR Init Done\n", -1);

            /* Set base address to start putting data at */
            baseAddress = hNorInfo->flashBase;

            /*Erase the entire NOR Flash*/
            if (NOR_erase(hNorInfo, baseAddress,
                          hNorInfo->flashSize) != TRUE)
            {
                UARTConfigPuts(uartBaseAddr,"\tERROR: Erasing NOR failed.\r\n", -1);
                retVal = FALSE;
                break;
            }

            /*
             * Initialize the source address with a pattern
             * initialize dst address with zero/another pattern (optional)
             */

            for (count = 0U; count < (FLASH_BLOCK_SIZE); count++)
            {
                srcBuffm[count] = (int) 0x55;
            }

            /* Write the data pattern to the flash */
            flash_size  = hNorInfo->flashSize;
            offset_addr = baseAddress;
            buf_size    = FLASH_BLOCK_SIZE;
            k           = 0;
            while (flash_size != 0)
            {
                dstOffsetAddr = offset_addr;
                dst_addr      = (signed char *) dstOffsetAddr;

                /* Write the data pattern to the flash */
                if (NOR_writeBytes(hNorInfo, dstOffsetAddr, FLASH_BLOCK_SIZE,
                                   (uint32_t) srcBuffm) != TRUE)
                {
                    UARTConfigPuts(uartBaseAddr,"\tERROR: Writing NOR failed.\n", -1);
                    retVal = FALSE;
                    break;
                }

                for (i = 0; i < (FLASH_BLOCK_SIZE); i++)
                {
                    if (srcBuffm[i] != dst_addr[i])
                    {
                        retVal = FALSE;
                        UARTConfigPuts(uartBaseAddr,
                            "\nError matching value at src and dst address\n",
                            -1);
                        UARTConfigPuts(uartBaseAddr,"Value at src address ", -1);
                        UARTConfigPutNum(uartBaseAddr,(uint32_t) &srcBuffm[i]);
                        UARTConfigPuts(uartBaseAddr," is:", -1);
                        UARTConfigPutNum(uartBaseAddr,srcBuffm[i]);
                        UARTConfigPuts(uartBaseAddr,"\nValue at dst address ", -1);
                        UARTConfigPutNum(uartBaseAddr,(uint32_t) &dst_addr[i]);
                        UARTConfigPuts(uartBaseAddr," is:", -1);
                        UARTConfigPutNum(uartBaseAddr,dst_addr[i]);
                        break;
                    }
                }
                if (retVal == FALSE)
                {
                    UARTConfigPuts(uartBaseAddr,"\nError testing block num: ", -1);
                    UARTConfigPutNum(uartBaseAddr,k);
                    break;
                }
                offset_addr += buf_size;
                flash_size  -= buf_size;

                UARTConfigPuts(uartBaseAddr,"Testing block no. ", -1);
                UARTConfigPutNum(uartBaseAddr,k++);
                UARTConfigPuts(uartBaseAddr," Completed\n", -1);
            }
            if (retVal == FALSE)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if (retVal == FALSE)
    {
        UARTConfigPuts(uartBaseAddr,"\nTest Failed Exitting.\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\nExiting the nor test\n", -1);
    }
}
/***************************** End Of File ***********************************/
