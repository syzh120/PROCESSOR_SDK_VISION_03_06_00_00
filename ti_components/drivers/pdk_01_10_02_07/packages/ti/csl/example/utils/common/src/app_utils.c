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
 *  \file     app_utils.c
 *
 *  \brief    This file contains common utility functions used by the PDK apps
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/example/utils/i2c/inc/i2c.h>

#include "app_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APPUTILS_UART_INPUT             (STD_ON)

/** brief Counter frequency */
#define APPUTILS_CFG_COUNTER_FREQ       (32000U)
/** brief Overflow count value for 32bit counter */
#define APPUTILS_COUNTER_MAX_COUNT      (0xFFFFFFFFU)

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define CTRL_CORE_PAD_UART1_RXD         (0x1bcU)
#define CTRL_CORE_PAD_UART1_TXD         (0x1c0U)
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOUNLOCK CTRL_CORE_MMR_LOCK_5_TOUNLOCK
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOLOCK CTRL_CORE_MMR_LOCK_5_TOLOCK
#else
#undef CTRL_CORE_PAD_UART1_RXD
#define CTRL_CORE_PAD_UART1_RXD         (0x3e0U)
#undef CTRL_CORE_PAD_UART1_TXD
#define CTRL_CORE_PAD_UART1_TXD         (0x3e4U)

#endif

#define CM_L3INSTR_L3_3_CLKCTRL         (0x4A008E20U)
#undef CM_L3INSTR_L3_INSTR_CLKCTRL
#define CM_L3INSTR_L3_INSTR_CLKCTRL     (0x4A008E28U)

#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
#undef SOC_I2C1_BASE
#define SOC_I2C1_BASE CSL_MPU_I2C1_REGS
#undef SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE
#define SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS
#undef SOC_I_DRM_BASE
#define SOC_I_DRM_BASE CSL_MPU_I_DRM_REGS
#undef SOC_IPU1_UNICACHE_MMU_BASE
#define SOC_IPU1_UNICACHE_MMU_BASE CSL_MPU_IPU2_TARGET_UNICACHE_MMU_REGS
#undef SOC_CORE_PAD_IO_REGISTERS_BASE
#define SOC_CORE_PAD_IO_REGISTERS_BASE CSL_MPU_CORE_PAD_IO_REGISTERS_REGS
#endif

/** brief Overflow count value for 32bit counter */
#define APPUTILS_APP_COUNTER_MAX_COUNT     (0xFFFFFFFFU)

/** \brief Offset of DRM SUSPEND_CTRL31 register */
//#define DRM_SUSPEND_CTRL31                 (0x27CU)
/** \brief DRM_SUSPEND_CTRL31 is mapped to COUNTER_32K Suspend Output line */
#define DRM_SUSPEND_CTRL_COUNTER_32K       (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL31)

#if defined (SOC_TDA3XX)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU_C0             (0x3U)
#else
/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0             (0x5U)
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void AppUtils_setBoardMux(void);
static void AppUtils_setPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AppUtils_defaultInit(void)
{
    /* Set UART1 pin mux */
    AppUtils_setPinmuxRegs(CTRL_CORE_PAD_UART1_RXD, 0x40000U);
    AppUtils_setPinmuxRegs(CTRL_CORE_PAD_UART1_TXD, (uint32_t) 0x0);

    AppUtils_setBoardMux();

    return;
} 

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x200U + (1U * 4U))
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief Offset of DRM SUSPEND_CTRL2 register */
#define DRM_SUSPEND_CTRL2               (0x200U + (2U * 4U))
/** \brief DRM_SUSPEND_CTRL2 is mapped to DCAN2 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN2          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL2)

/** \brief Offset of DRM SUSPEND_CTRL31 register */
#define DRM_SUSPEND_CTRL31               (0x200U + (31 * 4U))
/** \brief DRM_SUSPEND_CTRL31 is mapped to 32Ktimer Suspend Output line */
#define DRM_SUSPEND_CTRL_32KTIMER       (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL31)

static void AppUtils_setBoardMux(void)
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t retVal;
    uint8_t  regValue[4];

    I2C_init(SOC_I2C1_BASE);

    /*
     * Configure IO Expander
     */
    /* Enable UART1; all others to default */
    regValue[0] = 0x84U;
    regValue[1] = 0x5BU;
    regValue[2] = 0xD2U;
    regValue[3] = 0xC5U;
    retVal      = I2C_deviceRawWrite8(SOC_I2C1_BASE, 0x23, &regValue[0], 4);
    if (retVal != STW_SOK)
    {
        printf("I2C write to IO Expander failed!!\n");
    }

    /* Set all pins as output */
    regValue[0] = 0x8CU;
    regValue[1] = 0x00U;
    regValue[2] = 0x00U;
    regValue[3] = 0x00U;
    retVal      = I2C_deviceRawWrite8(SOC_I2C1_BASE, 0x23, &regValue[0], 4);
    if (retVal != STW_SOK)
    {
        printf("I2C write to IO Expander failed!!\n");
    }
    
    /* Enable UART1; all others to default */
    regValue[0] = 0x84U;
    regValue[1] = 0x5BU;
    regValue[2] = 0xD2U;
    regValue[3] = 0x00U;
    retVal      = I2C_deviceRawWrite8(SOC_I2C1_BASE, 0x23, &regValue[0], 4);
    if (retVal != STW_SOK)
    {
        printf("I2C write to IO Expander failed!!\n");
    }
    /* Enable MCSPI1; all others to default */
    regValue[0] = 0x84U;
    regValue[1] = 0x5BU;
    regValue[2] = 0xD3U;
    regValue[3] = 0xFFU;
    retVal      = I2C_deviceRawWrite8(SOC_I2C1_BASE, 0x23, &regValue[0], 4);
    if (retVal != STW_SOK)
    {
        printf("I2C write to IO Expander failed!!\n");
    }
#endif
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
   uint32_t retVal;
   uint8_t  regValue[2];
   
    I2C_init(SOC_I2C1_BASE);
/*Configure IO expander for MMC2*/
    regValue[0] = 0x84U;
    regValue[1] = 0x4AU;
    regValue[1] = (uint8_t) ((uint32_t) regValue[1U] & ((uint32_t) (~0x04U)));
    retVal      = I2C_deviceRawWrite8(SOC_I2C1_BASE, 0x21, &regValue[0], 2);
    if (retVal != STW_SOK)
    {
        printf("I2C write to IO Expander failed!!\n");
    }
#endif
    return;
}

static void AppUtils_setPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg)
{
    uint32_t tmpRegVal;

    /* Unlock MMR_5 for pin muxing */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOUNLOCK);

    tmpRegVal = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + baseAddrOffset);

    tmpRegVal &= ~(0xF000FU);
    tmpRegVal |= (ioPinCfg & 0xF000FU);

    HW_WR_REG32((SOC_CORE_PAD_IO_REGISTERS_BASE + baseAddrOffset), tmpRegVal);

    /* Lock MMR_5 for pin muxing */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOLOCK);

    return;
}

void AppUtils_setUartConsolePinMux()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    AppUtils_setPinmuxRegs(CTRL_CORE_PAD_UART1_RXD, 0x00040000);
    AppUtils_setPinmuxRegs(CTRL_CORE_PAD_UART1_TXD, 0x00000000);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    AppUtils_setPinmuxRegs(CTRL_CORE_PAD_IO_SPI1_SCLK, 0x00040001);
    AppUtils_setPinmuxRegs(CTRL_CORE_PAD_IO_SPI1_CS0, 0x00000001);
#endif
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
int32_t AppUtils_appGet32KCounterValue(uint32_t *value)
{
    *value = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    return STW_SOK;
}

int32_t AppUtils_appGetElapsedValue(uint32_t  value,
                                    uint32_t *elapsedValue)
{
    uint32_t currVal;

    currVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    if (currVal < value)
    {
        /* Counter overflow occured */
        currVal       = (APPUTILS_APP_COUNTER_MAX_COUNT - value) + currVal + 1U;
        *elapsedValue = currVal;
    }
    else
    {
        *elapsedValue = currVal - value;
    }

    return STW_SOK;
}

void AppUtils_appConfig32KCounterSuspendState(void)
{
#if defined (SOC_TDA3XX) && !(defined (__TI_ARM_V7M4__))
    /* Suspend Input Line : IPU_C0
     * Suspend Output Line : DRM_SUSPEND_CTRL_COUNTER_32K
     * This makes sure when M4 is halt, 32K Counter is not halted
     */
    HW_WR_REG32(DRM_SUSPEND_CTRL_COUNTER_32K,
                (((uint32_t) DRM_SUSPEND_SRC_IPU_C0 << 4U) | 0x0U));

#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /* As L3_INSTR is not connected to EVE1_P1 , so we cant able to configure
     * DRM_SUSPEND_CTRL_COUNTER_32K for EVE
     */
#if defined (__TI_ARM_V7M4__) || defined (_TMS320C6X)
    /* Suspend Input Line : MPU_C0
     * Suspend Output Line : DRM_SUSPEND_CTRL_COUNTER_32K
     * This makes sure when A15 is halt, 32K Counter is not halted
     */
    HW_WR_REG32(DRM_SUSPEND_CTRL_COUNTER_32K,
                (((uint32_t) DRM_SUSPEND_SRC_MPU_C0 << 4U) | 0x0U));
#endif
#endif
}

#endif

/* OS layer functions implementations */

