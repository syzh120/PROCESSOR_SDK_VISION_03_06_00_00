/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015-2017
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
 *  \brief    This file contains common utility functions used by the apps
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
#include <ti/csl/cslr_synctimer.h>


#include "app_utils.h"
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include "ti/board/board.h"
#include <ti/drv/uart/UART_stdio.h>
#else
#include "uartStdio.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APPUTILS_UART_INPUT             (STD_ON)

/** brief Counter ID - 0U for Counter 32Khz */
#define APPUTILS_CFG_COUNTER_ID         ((CounterType) 0x0U)
/** brief Counter frequency */
#define APPUTILS_CFG_COUNTER_FREQ       (32000U)
/** brief Overflow count value for 32bit counter */
#define APPUTILS_COUNTER_MAX_COUNT      (0xFFFFFFFFU)

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define PAD_UART1_RXD                   (CTRL_CORE_PAD_IO_UART1_RXD)
#define PAD_UART1_TXD                   (CTRL_CORE_PAD_IO_UART1_TXD)
#define PAD_UART3_RXD                   (CTRL_CORE_PAD_IO_SPI1_SCLK)
#define PAD_UART3_TXD                   (CTRL_CORE_PAD_IO_SPI1_CS0)
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOUNLOCK CTRL_CORE_MMR_LOCK_5_TOUNLOCK
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOLOCK CTRL_CORE_MMR_LOCK_5_TOLOCK
#elif defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define PAD_UART1_RXD                   (0x3E0U)
#define PAD_UART1_TXD                   (0X3E4U)
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
#define PAD_UART1_RXD                   (CTRL_CORE_PAD_UART1_RXD)
#define PAD_UART1_TXD                   (CTRL_CORE_PAD_UART1_TXD)
#endif

#define CM_L3INSTR_L3_3_CLKCTRL             (0x4A008E20U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_LOCAL   (0x4A008E28U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Counters related typedefs */
typedef int16_t   CounterType;
typedef uint32_t  TickType;
typedef TickType *TickRefType;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if !defined (SOC_AM572x) && !defined (SOC_AM571x) && !defined (SOC_AM574x)
static void AppUtils_setPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg);
static void AppUtils_init(void);

int32_t GetCounterValue(CounterType CounterID, TickRefType Value);
int32_t GetElapsedValue(CounterType CounterID,
                        TickRefType Value,
                        TickRefType ElapsedValue);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AppUtils_defaultInit(void)
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    Board_initCfg boardCfg;

    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO |
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#else
    /* set timer and DCAN to free running mode */
    AppUtils_init();

#if defined (SOC_TDA3XX)
    /* Set UART3 pin mux */
    AppUtils_setPinmuxRegs(PAD_UART3_RXD, 0x40001U);
    AppUtils_setPinmuxRegs(PAD_UART3_TXD, (uint32_t) 0x1);
#else
    /* Set UART1 pin mux */
    AppUtils_setPinmuxRegs(PAD_UART1_RXD, 0x40000U);
    AppUtils_setPinmuxRegs(PAD_UART1_TXD, (uint32_t) 0x0);
#endif

    UARTStdioInit();
#endif

    return;
}

void AppUtils_printf(const char *pStr, ...)
{
    static char tempBuf[400];
    va_list     vaArgP;

    /* Start the varargs processing. */
    va_start(vaArgP, pStr);

    vsnprintf(&tempBuf[0U], sizeof (tempBuf), pStr, vaArgP);
#if defined (SOC_AM574x)|| defined (SOC_AM572x) || defined (SOC_AM571x)
    UART_printf("%s", &tempBuf[0U]);
#else
    UARTPrintf("%s", &tempBuf[0U]);
#endif
    /* End the varargs processing. */
    va_end(vaArgP);

    return;
}

#if !defined (SOC_AM572x) && !defined (SOC_AM571x) && !defined (SOC_AM574x)
char AppUtils_getChar(void)
{
    char ch;

#if (APPUTILS_UART_INPUT == STD_ON)
    ch = UARTGetc();
#else
    scanf("%c", &ch);
#endif

    return (ch);
}

int32_t AppUtils_getCharTimeout(char *ch, uint32_t msec)
{
    int32_t  retVal = -1;
#if (APPUTILS_UART_INPUT == STD_ON)
    uint32_t startCount, elaspsedCount, cycleDelay;
    int32_t  status;

    status     = GetCounterValue(APPUTILS_CFG_COUNTER_ID, &startCount);
    cycleDelay = (msec * APPUTILS_CFG_COUNTER_FREQ) / 1000U;
    do
    {
        retVal = UARTGetcNonBlocking((uint8_t *) ch);
        if (retVal == 0U)
        {
            retVal = 0U;
            break;
        }
        retVal = -1;
        status = GetElapsedValue(
            APPUTILS_CFG_COUNTER_ID,
            &startCount,
            &elaspsedCount);
    } while ((0U == status) && (elaspsedCount <= cycleDelay));
#else
    /* Timeout not supported by stdio scanf */
    scanf("%c", &ch);
    retVal = 0;
#endif

    return (retVal);
}

int32_t AppUtils_getNum(void)
{
    int32_t num;

#if (APPUTILS_UART_INPUT == STD_ON)
    num = UARTGetNum();
#else
    scanf("%d", &num);
#endif

    return (num);
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

static void AppUtils_init(void)
{
    uint32_t regAddr, regVal;

    /*
     * Put all used modules to free running mode
     */
    /* Enable DRM */
    regAddr = CM_L3INSTR_L3_3_CLKCTRL;
    regVal  = 0x1U;
    HW_WR_REG32(regAddr, regVal);   /* Provide L3_3 clock */
    regAddr = CM_L3INSTR_L3_INSTR_CLKCTRL_LOCAL;
    regVal  = 0x1U;
    HW_WR_REG32(regAddr, regVal);   /* Provide L3 instr clock */

    /* Claim ownership of debug registers */
    regAddr = 0x54160050U;
    regVal  = 0x40000000;
    HW_WR_REG32(regAddr, regVal);
    regAddr = 0x54160050U;
    regVal  = 0x80000000U;
    HW_WR_REG32(regAddr, regVal);

    /* Set 32k counter to free running mode */
    regAddr = DRM_SUSPEND_CTRL_32KTIMER;
    regVal  = HW_RD_REG32(regAddr);
    regVal &= ~((uint32_t) 0x00000009U);
    HW_WR_REG32(regAddr, regVal);

    /* Release ownership of debug registers */
    regAddr = 0x54160050U;
    regVal  = 0x00000000;
    HW_WR_REG32(regAddr, regVal);
}

void AppUtils_delay(uint32_t msec)
{
    uint32_t startCount, elaspsedCount, cycleDelay;
    int32_t  status;

    status     = GetCounterValue(APPUTILS_CFG_COUNTER_ID, &startCount);
    cycleDelay = (msec * APPUTILS_CFG_COUNTER_FREQ) / 1000U;
    if (0U == status)
    {
        do
        {
            status = GetElapsedValue(
                APPUTILS_CFG_COUNTER_ID,
                &startCount,
                &elaspsedCount);
        } while ((cycleDelay >= elaspsedCount) && (0U == status));
    }
    return;
}

uint32_t AppUtils_getCurTimeInMsec(void)
{
    uint32_t timerCount, curTimeMsec = 0U;
    int32_t  status;

    status = GetCounterValue(APPUTILS_CFG_COUNTER_ID, &timerCount);
    if (0U == status)
    {
        curTimeMsec = ((timerCount * 1000U) / APPUTILS_CFG_COUNTER_FREQ);
    }

    return (curTimeMsec);
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

/* OS layer functions implementations */
/**
 * \brief Return current count value for OS timer.
 *
 * \param  CounterID  Counter ID.
 * \param  Value      Pointer to variable to return count value.
 *
 * \retval 0U         Counter read is successful.
 */
int32_t GetCounterValue(CounterType CounterID, TickRefType Value)
{
    *Value = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    /* counter starts from zero. Adding one will take care for overflow case */
    *Value = *Value;
    return (int32_t) 0U;
}

/**
 * \brief Return current count value for OS timer.
 *
 * \param  CounterID        Counter ID.
 * \param  Value            Reference value to which current value is compated
 *                          to get elapsed count.
 * \param  ElapsedValue     Pointer to variable to return elapsed count value.
 *
 * \retval 0U               Counter read is successful.
 */
int32_t GetElapsedValue(CounterType CounterID,
                        TickRefType Value,
                        TickRefType ElapsedValue)
{
    TickType currVal;

    currVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    if (currVal < *Value)
    {
        /* Counter overflow occured */
        currVal = (APPUTILS_COUNTER_MAX_COUNT - *Value) + currVal + 1U;
    }
    *ElapsedValue = currVal - *Value;
    return (int32_t) 0U;
}

/**
 * \brief   This function gets the silicon package type of the SoC.
 *
 * \param   None
 *
 * \return  packageType   Refer enum #platformSiliconPackageType_t for details.
 */
uint32_t AppUtils_GetSiliconPackageType(void)
{
    uint32_t packageType;
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t regVal;
    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                           CTRL_CORE_BOOTSTRAP,
                           CTRL_CORE_BOOTSTRAP_SYSBOOT_7);

    if (0x1U == regVal)
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_12X12;
    }
    else
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_15X15;
    }
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
    uint32_t regVal;
    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                           CTRL_WKUP_STD_FUSE_DIE_ID_2,
                           CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE);
    if (0x1U == regVal)
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_17X17;
    }
    else if (0x2U == regVal)
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_23X23;
    }
    else
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_UNKNOWN;
    }
#else
    packageType = PLATFORM_SILICON_PACKAGE_TYPE_UNKNOWN;
#endif
    return packageType;
}
#endif /* !defined (SOC_AM572x) && !defined (SOC_AM571x) */
