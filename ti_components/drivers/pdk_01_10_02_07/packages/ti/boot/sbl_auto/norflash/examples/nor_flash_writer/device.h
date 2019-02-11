/*
 * TI Booting and Flashing Utilities
 *
 * Provides device differentiation for the project files. This file MUST
 * be modified to match the device specifics.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <ti/boot/sbl_auto/norflash/nor_flash.h>
#include <ti/boot/sbl_auto/norflash/src/debug.h>

/* Prevent C++ name mangling */
#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
 * Global Macro Declarations                                *
 ***********************************************************/

#ifdef USE_SRAM
/* using ocmc0 for custom heap (and not ccs heap) */
#define SRAM_HEAP_START 0x40300000U
#define SRAM_HEAP_SIZE  (200U * 1024U)
#define DEVICE_DDR2_RAM_END (SRAM_HEAP_START + SRAM_HEAP_SIZE)
#define DEVICE_DDR2_START_ADDR  (SRAM_HEAP_START)
#else
/* using DDR for custom heap */
#define DDR_HEAP_START 0x90000000U
#define DDR_HEAP_SIZE   (64U * 1024U * 1024U)
#define DEVICE_DDR2_RAM_END (DDR_HEAP_START + DDR_HEAP_SIZE)
#define DEVICE_DDR2_START_ADDR  (DDR_HEAP_START)
#endif

/* Control Module MMR */
#define CM_BASE                     ((UInt32) 0x48180000)
#define CM_ALWON_MOD_OFF            ((UInt32) 0x1400)  /* 1KB */
#define CM_ALWON_GPMC_CLKCTRL_OFF   ((UInt32) 0x1D0)
/* PRCM Bits */
#define MODULEMODE_SWCTRL           ((UInt32) 0x2)

/* GPMC MMR
 */
#define GPMC_BASE               ((UInt32) 0x50000000)
#define GPMC_SYSCONFIG_OFF      ((UInt32) 0x10)
#define GPMC_IRQSTS_OFF         ((UInt32) 0x18)
#define GPMC_IRQENABLE_OFF      ((UInt32) 0x1c)
#define GPMC_TIMEOUTCTRL_OFF    ((UInt32) 0x40)
#define GPMC_CONFIG_OFF         ((UInt32) 0x50)
#define GPMC_CONFIG_CS0_BASE    (GPMC_BASE + 0x60U)
#define GPMC_CS_CONFIG_SIZE     ((UInt32) 0x30)
#define GPMC_MAX_CS             ((UInt32) 7)

#define GPMC_CONFIG1_OFF        ((UInt32) 0x00)
#define GPMC_CONFIG2_OFF        ((UInt32) 0x04)
#define GPMC_CONFIG3_OFF        ((UInt32) 0x08)
#define GPMC_CONFIG4_OFF        ((UInt32) 0x0C)
#define GPMC_CONFIG5_OFF        ((UInt32) 0x10)
#define GPMC_CONFIG6_OFF        ((UInt32) 0x14)
#define GPMC_CONFIG7_OFF        ((UInt32) 0x18)

/**** PAD CFG MMR */
#define CFG_MOD_BASE    ((UInt32) 0x48140000)
#define TIM7_OUT_OFF    ((UInt32) (0xb34))  /* a12 */
#define UART1_CTSN_OFF  ((UInt32) (0xadc))  /* a13 */
#define UART1_RTSN_OFF  ((UInt32) (0xad8))  /* a14 */
#define UART2_RTSN_OFF  ((UInt32) (0xae8))  /* a15 */
#define SC1_RST_OFF     ((UInt32) (0xb10))  /* a15 */
#define UART2_CTSN_OFF  ((UInt32) (0xaec))  /* a16 */
#define UART0_RIN_OFF   ((UInt32) (0xacc))  /* a17 */
#define UART0_DCDN_OFF  ((UInt32) (0xac8))  /* a18 */
#define UART0_DSRN_OFF  ((UInt32) (0xac4))  /* a19 */
#define UART0_DTRN_OFF  ((UInt32) (0xac0))  /* a20 */
#define SPI_SCS3_OFF    ((UInt32) (0xaa4))  /* a21 */
#define SPI_SC2_OFF     ((UInt32) (0xaa0))  /* a22 */
#define GPO_IO6_OFF     ((UInt32) (0xca0))  /* a23 */
#define TIM6_OUT_OFF    ((UInt32) (0xb30))  /* a24 */
#define SC0_DATA_OFF    ((UInt32) (0xafc))  /* a25 */
#define GPMC_A27_OFF    ((UInt32) (0xba0))  /* a27 */

#define GPMC_PAD_DEF    ((UInt32) (0x1))

#define GPIO0_PRCM      ((UInt32) (0x4818155c))
#define GPIO1_PRCM      ((UInt32) (0x48181560))
#define GPIO6_A         ((UInt32) (0x4803213c))
#define GPIO6_B         ((UInt32) (0x48032134))

/*** TI814X ****/
#define GPIO1_REG               ((UInt32) 0x4804C000)

/****NOR PAD CONFIG *****/
#define GPMC_D0                 ((UInt32) 0x0960)
#define GPMC_D1                 ((UInt32) 0x0964)
#define GPMC_D2                 ((UInt32) 0x0968)
#define GPMC_D3                 ((UInt32) 0x096C)
#define GPMC_D4                 ((UInt32) 0x0970)
#define GPMC_D5                 ((UInt32) 0x0974)
#define GPMC_D6                 ((UInt32) 0x0978)
#define GPMC_D7                 ((UInt32) 0x097C)
#define GPMC_D8                 ((UInt32) 0x0980)
#define GPMC_D9                 ((UInt32) 0x0984)
#define GPMC_D10                ((UInt32) 0x0988)
#define GPMC_D11                ((UInt32) 0x098C)
#define GPMC_D12                ((UInt32) 0x0990)
#define GPMC_D13                ((UInt32) 0x0994)
#define GPMC_D14                ((UInt32) 0x0998)
#define GPMC_D15                ((UInt32) 0x099C)

#define GPMC_A1                 ((UInt32) 0x09D0)
#define GPMC_A2                 ((UInt32) 0x09D4)
#define GPMC_A3                 ((UInt32) 0x09D8)
#define GPMC_A4                 ((UInt32) 0x09DC)
#define GPMC_A5                 ((UInt32) 0x0A9C)
#define GPMC_A6                 ((UInt32) 0x0AA0)
#define GPMC_A7                 ((UInt32) 0x0AA4)
#define GPMC_A8                 ((UInt32) 0x0AA8)
#define GPMC_A9                 ((UInt32) 0x0AAC)
#define GPMC_A10                ((UInt32) 0x0AB0)
#define GPMC_A11                ((UInt32) 0x0AB4)
#define GPMC_A12                ((UInt32) 0x0AB8)
#define GPMC_A13                ((UInt32) 0x0B8C)
#define GPMC_A14                ((UInt32) 0x0B90)
#define GPMC_A15                ((UInt32) 0x0B94)
#define GPMC_A16                ((UInt32) 0x09A0)
#define GPMC_A17                ((UInt32) 0x09A4)
#define GPMC_A18                ((UInt32) 0x09A8)
#define GPMC_A19                ((UInt32) 0x09AC)
#define GPMC_A20                ((UInt32) 0x09B0)
#define GPMC_A21                ((UInt32) 0x09B4)
#define GPMC_A22                ((UInt32) 0x09B8)
#define GPMC_A23                ((UInt32) 0x09BC)
#define GPMC_A24                ((UInt32) 0x09EC)
#define GPMC_A25                ((UInt32) 0x09E8)

#define GPMC_A27                ((UInt32) 0x09CC)
#define GPMC_CS0_REG            ((UInt32) 0x09E4)
#define GPMC_OEN                ((UInt32) 0x0A00)
#define GPMC_WEN                ((UInt32) 0x0A04)

/* GPMC register base */

/* GPMC Chip Select configuration passed to gpmc_SetCSConfig */
typedef struct {
    UInt32 Config1;
    UInt32 Config2;
    UInt32 Config3;
    UInt32 Config4;
    UInt32 Config5;
    UInt32 Config6;
    UInt32 Config7;
} GPMC_CsConfig_t;

/* GPMC Configuration passed to GPMC_SetConfig in order to configure the GPMC
 * The structure is also used by the CHFLASH Configuration Header */
typedef struct
{
    UInt32 SysConfig;
    UInt32 IrqEnable;
    UInt32 TimeOutControl;
    UInt32 Config;
    UInt32 ChipSelectConfig[GPMC_MAX_CS];
    UInt32 PrefetchConfig1;
    UInt32 PrefetchConfig2;
    UInt32 PrefetchControl;
#ifdef NAND_SUPPORT
    UInt32 EccConfig;
    UInt32 EccControl;
    UInt32 EccSizeConfig;
#endif
}GPMC_Config_t;

void PAD_ConfigMux(const UInt32 *addr, UInt32 val);
void GPMC_Init(const GPMC_Config_t *cfg, Int8 cs);

#ifdef __cplusplus
}
#endif

#endif /* End DEVICE_H_ */

/***********************************************************
 * End file                                                 *
 ***********************************************************/

/* --------------------------------------------------------------------------
 *  HISTORY
 *     v1.00  -  DJA  -  07-Nov-2007
 *       Initial Release
 * -----------------------------------------------------------------------------
 * */

