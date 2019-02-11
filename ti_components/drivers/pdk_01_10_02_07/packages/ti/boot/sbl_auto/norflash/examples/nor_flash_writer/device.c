/*
 * TI816x Booting and Flashing Utilities
 *
 * This file provides low-level init functions.
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

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <device.h>
#include <util.h>

/************************************************************
 * Explicit External Declarations                            *
 ************************************************************/

/************************************************************
 * Local Macro Declarations                                  *
 ************************************************************/
#define MAX_DELAY   ((UInt32) 0x900)

/************************************************************
 * Local Typedef Declarations                                *
 ************************************************************/

/************************************************************
 * Local Function Declarations                               *
 ************************************************************/
void GPMC_Write(UInt32 offset, UInt32 val);
void GPMC_CSWrite(Int8 cs, UInt32 offset, UInt32 val);
UInt32 GPMC_Read(UInt32 offset);
UInt32 DEVICE_Delay(UInt32 delay);
void CM_Write(UInt32 module, UInt32 reg, UInt32 val);
static void nor_pad_config_mux(void);
static Int32 getPlatform(void);
void ti816x_nor_init(void);
void ti814x_nor_init(void);
Int32 evm_nor_init(void);

/************************************************************
 * Local Function Definitions                                *
 ************************************************************/
void GPMC_Write(UInt32 offset, UInt32 val)
{
    HW_WR_REG32(GPMC_BASE + offset, val);
}

void GPMC_CSWrite(Int8 cs, UInt32 offset, UInt32 val)
{
    UInt32 tmpAddr = GPMC_CONFIG_CS0_BASE +
                     (GPMC_CS_CONFIG_SIZE * (UInt32) cs) + offset;
    HW_WR_REG32(tmpAddr, val);
}

UInt32 GPMC_Read(UInt32 offset)
{
    UInt32 tmpVal;

    tmpVal = HW_RD_REG32(GPMC_BASE + offset);
    return (tmpVal);
}

/* make sure compiler doesnt optimize this function */
UInt32 DEVICE_Delay(UInt32 delay)
{
    UTIL_waitLoop(delay * 0x100U);
    return 0U;
}

void CM_Write(UInt32 module, UInt32 reg, UInt32 val)
{
    UInt32 tmpAddr = (CM_BASE + module + reg);
    HW_WR_REG32(tmpAddr, val);
}

/************************************************************
 * Local Variable Definitions                                *
 \***********************************************************/

/* PAD register offsets for GPMC address lines a11 to a26 */
static UInt32 PAD_GPMC_A11ToA26Offsets[] = {
    TIM7_OUT_OFF,     /* a12 */
    UART1_CTSN_OFF,   /* a13 */
    UART1_RTSN_OFF,   /* a14 */
    UART2_RTSN_OFF,   /* a15 */
    SC1_RST_OFF,      /* a15 */
    UART2_CTSN_OFF,   /* a16 */
    UART0_RIN_OFF,    /* a17 */
    UART0_DCDN_OFF,   /* a18 */
    UART0_DSRN_OFF,   /* a19 */
    UART0_DTRN_OFF,   /* a20 */
    SPI_SCS3_OFF,     /* a21 */
    SPI_SC2_OFF,      /* a22 */
    GPO_IO6_OFF,      /* a23 */
    TIM6_OUT_OFF,     /* a24 */
    SC0_DATA_OFF,     /* a25 */
    GPMC_A27_OFF,     /* a27 */
    0xFFFFFFFFU
};

/************************************************************
 * Global Variable Definitions                               *
 ************************************************************/

/************************************************************
 * Global Function Definitions                               *
 ************************************************************/

void PAD_ConfigMux(const UInt32 *addr, UInt32 val)
{
    UInt8  i;
    UInt32 tmpAddr;

    for (i = 0; i < 17U; i++) {
        if (addr[i] == 0xFFFFFFFFU)
        {
            break;
        }
        tmpAddr = (CFG_MOD_BASE + addr[i]);
        HW_WR_REG32(tmpAddr, val);
    }
}

#define INPUT_EN        ((UInt32) 0x1 << 18)
#define PULL_UP_EN      ((UInt32) 0x1 << 17)
#define PULL_DIS        ((UInt32) 0x1 << 16)
#define MODE(x)         ((UInt32) 0x1 << ((x) - (UInt32) 1))

struct nor_pad_config {
    UInt16 offset;
    UInt32 value;
};

/* PAD register offsets and the configuration value */
static struct nor_pad_config nor_pad_cfg[] = {
    {GPMC_D0,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D1,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D2,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D3,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D4,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D5,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D6,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D7,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D8,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D9,      MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D10,     MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D11,     MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D12,     MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D13,     MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D14,     MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_D15,     MODE(1U) | INPUT_EN | PULL_DIS},
    {GPMC_A1,      MODE(2U) | PULL_DIS           },
    {GPMC_A2,      MODE(2U) | PULL_DIS           },
    {GPMC_A3,      MODE(2U) | PULL_DIS           },
    {GPMC_A4,      MODE(2U) | PULL_DIS           },
    {GPMC_A5,      MODE(5U) | PULL_DIS           },
    {GPMC_A6,      MODE(5U) | PULL_DIS           },
    {GPMC_A7,      MODE(5U) | PULL_DIS           },
    {GPMC_A8,      MODE(5U) | PULL_DIS           },
    {GPMC_A9,      MODE(5U) | PULL_DIS           },
    {GPMC_A10,     MODE(5U) | PULL_DIS           },
    {GPMC_A11,     MODE(5U) | PULL_DIS           },
    {GPMC_A12,     MODE(5U) | PULL_DIS           },
    {GPMC_A13,     MODE(2U) | PULL_DIS           },
    {GPMC_A14,     MODE(2U) | PULL_DIS           },
    {GPMC_A15,     MODE(2U) | PULL_DIS           },
    {GPMC_A16,     MODE(1U) | PULL_DIS           },
    {GPMC_A17,     MODE(1U) | PULL_DIS           },
    {GPMC_A18,     MODE(1U) | PULL_DIS           },
    {GPMC_A19,     MODE(1U) | PULL_DIS           },
    {GPMC_A20,     MODE(1U) | PULL_DIS           },
    {GPMC_A21,     MODE(1U) | PULL_DIS           },
    {GPMC_A22,     MODE(3U) | PULL_DIS           },
    {GPMC_A23,     MODE(3U) | PULL_DIS           },
    {GPMC_A24,     MODE(2U) | PULL_DIS           },
    {GPMC_A25,     MODE(8U) | PULL_DIS           },
    {GPMC_CS0_REG, MODE(1U) | PULL_UP_EN         },
    {GPMC_OEN,     MODE(1U) | PULL_UP_EN         },
    {GPMC_WEN,     MODE(1U) | PULL_UP_EN         },
    {0,            0                             },
};

/*********************************************************************
 *
 * nor_pad_config_mux - configure the pin mux for NOR
 *
 *********************************************************************/
static void nor_pad_config_mux(void)
{
    UInt8  i = 0;
    UInt32 tmpAddr;

    while (nor_pad_cfg[i].offset != 0x0)
    {
        tmpAddr = (CFG_MOD_BASE + nor_pad_cfg[i].offset);
        HW_WR_REG32(tmpAddr, nor_pad_cfg[i].value);
        i++;
    }
}

/*********************************************************************
 *
 * getPlatform - identify the platform based on the Jtag ID
 *
 *********************************************************************/

#define MANUFACTURER_ID_REG     (CFG_MOD_BASE + 0x600U)
#define MANUFACTURER_ID_MASK    ((UInt32) 0xFFFF << 12)

static Int32 getPlatform(void)
{
    UInt32 DevId;

    DevId   = *(UInt32 *) MANUFACTURER_ID_REG;
    DevId   = DevId & MANUFACTURER_ID_MASK;
    DevId >>= 12U;

    return (Int32) DevId;
}

void ti816x_nor_init(void)
{
    /* CONFIGURE PAD - PINMUXING */
    PAD_ConfigMux(PAD_GPMC_A11ToA26Offsets, GPMC_PAD_DEF);
    /* GPMC A23 IS ON GPO_IO6 AND MODE IS 2*/
    HW_WR_REG32(CFG_MOD_BASE + GPO_IO6_OFF, 0x2);
    HW_WR_REG32(GPIO6_A, 0x00000000);      /* GPMC 27 low  gpio 20 */
    HW_WR_REG32(GPIO6_B, 0xffefffffU);     /* GPMC 27 low  gpio 20 */
}

void ti814x_nor_init(void)
{
    nor_pad_config_mux();
    HW_WR_REG32(GPIO1_REG + 0x13CU, 0x0);
    HW_WR_REG32(GPIO1_REG + 0x134U, 0xffbfffffU);
}

/* Manufacturer ID */
#define TI816X 0xB81E
#define TI814X 0xB8F2

Int32 evm_nor_init(void)
{
    Int32 ret = 0;

    HW_WR_REG32(GPIO0_PRCM, 0x102); /*Enable GPIO0 Clock*/
    while ((HW_RD_REG32(GPIO0_PRCM) & 0x3U) != 0x2U)
    {
        /* Busy Loop */
    }

    HW_WR_REG32(GPIO1_PRCM, 0x102); /*Enable GPIO1 Clock*/
    while ((HW_RD_REG32(GPIO1_PRCM) & 0x3U) != 0x2U)
    {
        /* Busy Loop */
    }

    switch (getPlatform()) {
        case TI816X:
            ti816x_nor_init();
            break;

        case TI814X:
            ti814x_nor_init();
            break;

        default:
            ret = (Int32) NOR_FLASH_FAIL;
            break;
    }

    return ret;
}

/*********************************************************************
 *
 * GPMC_Init - Initialize GPMC based on CS and config values
 *
 *********************************************************************/
void GPMC_Init(const GPMC_Config_t *cfg, Int8 cs)
{
    UInt32 i;

#ifdef  ti814x
    /* enable gpmc */
    CM_Write(CM_ALWON_MOD_OFF, CM_ALWON_GPMC_CLKCTRL_OFF, MODULEMODE_SWCTRL);
    DEVICE_Delay(MAX_DELAY);
#endif

    /****** program global GPMC regs *****/
    GPMC_Write(GPMC_SYSCONFIG_OFF, cfg->SysConfig);
    GPMC_Write(GPMC_IRQENABLE_OFF, cfg->IrqEnable);
    GPMC_Write(GPMC_TIMEOUTCTRL_OFF, cfg->TimeOutControl);
    GPMC_Write(GPMC_CONFIG_OFF, cfg->Config);

    /****** program GPMC CS specific registers *****/
    /* disable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, 0x00000000);
    DEVICE_Delay(MAX_DELAY);

    /* program new set of config values (1 to 7) */
    for (i = 0; i < GPMC_MAX_CS; i++) {
        GPMC_CSWrite(cs, (i * 4U), cfg->ChipSelectConfig[i]);
    }

    /* enable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF,
                 (cfg->ChipSelectConfig[6] | (UInt32) 0x40));
    DEVICE_Delay(MAX_DELAY);
}

/***********************************************************
 * End file                                                 *
 ***********************************************************/

/* --------------------------------------------------------------------------
 *  HISTORY
 *      v1.0 completion
 *          Mansoor Ahamed -  23-Apr-2010
 * -----------------------------------------------------------------------------
 * */
