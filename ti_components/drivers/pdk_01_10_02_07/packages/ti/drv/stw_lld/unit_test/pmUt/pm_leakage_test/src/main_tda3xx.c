/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 * \file main.c
 *
 * \brief     Power management Leakage Test for Continental Configuration
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/cslr_cache.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc/tda3xx/cslr_soc.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/pm/src/pmhal/prcm/common/hw_pmhal_data.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define SBL_UTILS_I2C_SYSTEM_CLOCK       ((uint32_t) 96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define SBL_UTILS_I2C_INTERNAL_CLOCK     ((uint32_t) 9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define SBL_UTILS_I2C_OUTPUT_CLOCK       ((uint32_t) 400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define SBL_UTILS_I2C_TIMEOUT_COUNT      ((uint32_t) 4000U)

/** Write Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_WRITE              ((uint32_t) 1U)

/** Read Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_READ               ((uint32_t) 2U)

#define PMHAL_PRCM_MOD_MIN (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)
#define PMHAL_PRCM_MOD_MAX (PMHAL_PRCM_MOD_COUNT - 1U)

//#define CUSTOM_BOARD1 /* Radar */
#define CUSTOM_BOARD2   /* DM */

/** DSS DSS_DESHDCP_CLKEN register setting */
#define REG_CTRL_CORE_CONTROL_IO_2      ( \
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_CONTROL_IO_2)

#define TIMEOUT_VAL                      (10000U)
/**< \brief Timeout value to wait for event */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**<
 *  \brief Function to configure always enabled for all the modules.
 *
 *  \param  None
 *
 *  \return None
 */
void alwaysEnabledConfig(void);

/**<
 *  \brief Function to set module states.
 *
 *  \param  None
 *
 *  \return None
 */
void setModuleStates(void);

/**<
 *  \brief Function to set power domain for leakage by configuring the clock
 *         domain to sw-wkup.
 *
 *  \param  None
 *
 *  \return None
 */
void setPowerDomainStatesForLeakage(void);

/**<
 *  \brief Function to set PLL state to low power
 *
 *  \param  None
 *
 *  \return None
 */
void setPllStates(void);

/**<
 *  \brief Function to set special power down registers for certain modules
 */
void modulePowerDownProgram(void);

/**<
 *  \brief Pad configuration for the LED Configuration.
 */
void ledPadIoConf(void);

extern void cntrl_core_pad_configuration(uint32_t            baseAdd,
                                         const pad_config_t *pad_config);

void programPllsOn();

/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t SblUtilsI2cInit(void);

/**
 * \brief   This function reads a byte from the PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be read.
 * \param   regValue    Pointer to the location where the read value will be
 *                      placed.
 * \param   numRegs     Number of registers to be read.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   uint8_t *regValue,
                                   uint32_t numRegs);

/**
 * \brief   This function writes a byte of data to the register of PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be written.
 * \param   regValue    Pointer to the location where the write value will be
 *                      placed.
 * \param   numRegs     Number of registers to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    const uint8_t *regValue,
                                    uint32_t numRegs);
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWaitForBB(uint32_t i2cNum);

/**
 * \brief  Poll for the given flags and return when any of the flags is set or
 *         timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   flags       Flag to be waited for.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

/**
 * \brief  Write the given number of bytes to the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   data        Data to be written.
 * \param   count       Number of Bytes to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWrite(uint32_t i2cNum,
                                uint8_t slaveAddr, const uint8_t data[],
                                uint8_t count);

/**
 * \brief  Read one byte from the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   value       Data to be read is returned.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cRead(uint32_t i2cNum,
                               uint8_t  slaveAddr,
                               uint8_t *value);

/**
 * \brief Check the status of the transfer and handle the error conditions.
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 * \param   xfr     Transfer Type. Can be any one of SBL_UTILS_I2C_WRITE or
 *                  SBL_UTILS_I2C_READ.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

const char     *voltageDomain_t_names[] =
{
    "PMHAL_PRCM_VD_CORE",
    "PMHAL_PRCM_VD_DSPEVE"
};

pmhalPrcmVdId_t gVoltId = PMHAL_PRCM_VD_CORE;

void printTemp();
int32_t configVoltageRails();

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalI2cCommOperations_t gPmicI2cfunc = {
    &SblUtilsI2cInit,
    &SblUtilsI2cReadByte,
    &SblUtilsI2cWriteByte,
    NULL,
    NULL
};

pmErrCode_t     finalSuccess = PM_SUCCESS;

pmlibSysConfigPowerStateParams_t gInputTable[] =
{
    {PMHAL_PRCM_MOD_CRC,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSP1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSP2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSS,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EVE1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_CPGMAC,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER5,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER6,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER7,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER8,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,      PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP, PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DLL_AGING,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L3_INSTR,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_2,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_OCP_WP_NOC,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPMC,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_1,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_EDMA,            PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM1,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPCC,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TPTC2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_CFG,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPINLOCK,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MAILBOX1,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MAILBOX2,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC6,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC7,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER4,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC5,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_ELM,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ESM,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI4,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART2,               PMLIB_SYS_CONFIG_DISABLED      },
    /*{PMHAL_PRCM_MOD_UART3,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},*/
    #if defined (CUSTOM_BOARD1)
    {PMHAL_PRCM_MOD_GPIO2,               PMLIB_SYS_CONFIG_DISABLED      },
    #else
    {PMHAL_PRCM_MOD_GPIO3,               PMLIB_SYS_CONFIG_DISABLED      },
    #endif
    {PMHAL_PRCM_MOD_GPIO4,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCAN2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_ADC,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PWMSS1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_QSPI,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC3,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VIP1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_ISS,                 PMLIB_SYS_CONFIG_DISABLED      },
    /*{PMHAL_PRCM_MOD_DEBUG_LOGIC,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},*/
    {PMHAL_PRCM_MOD_COUNTER_32K,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCAN1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_WKUP,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TESOC,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI2,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI3,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI4,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI5,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_CAMERARX,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER1,             PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_L4_PER2,             PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_L4_PER3,             PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_DLL,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EMIF1,               PMLIB_SYS_CONFIG_AUTO_CG       }
};

const uint32_t  numTableEntries = sizeof (gInputTable) /
                                  sizeof (pmlibSysConfigPowerStateParams_t);

pmhalPrcmCdId_t clockDomainsForLeakage[] =
{
#if defined (CUSTOM_BOARD1) || defined (CUSTOM_BOARD2)
#if defined(CUSTOM_BOARD2)
    PMHAL_PRCM_CD_CUSTEFUSE,
    PMHAL_PRCM_CD_DSP1,
    PMHAL_PRCM_CD_EVE1,
    PMHAL_PRCM_CD_CAM,
    PMHAL_PRCM_CD_ISS
#endif
#if defined(CUSTOM_BOARD1)
    PMHAL_PRCM_CD_CUSTEFUSE,
    PMHAL_PRCM_CD_DSP1,
    PMHAL_PRCM_CD_DSP2
#endif
#else
    PMHAL_PRCM_CD_CUSTEFUSE,
    PMHAL_PRCM_CD_DSP1,
    PMHAL_PRCM_CD_EVE1,
    PMHAL_PRCM_CD_CAM,
    PMHAL_PRCM_CD_ISS
#endif
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    const pmlibSysConfigPowerStateParams_t uartDisable[1] =
    {
        {PMHAL_PRCM_MOD_UART3, PMLIB_SYS_CONFIG_DISABLED}
    };
    const pmlibSysConfigPowerStateParams_t uartEnable[1] =
    {
        {PMHAL_PRCM_MOD_UART3, PMLIB_SYS_CONFIG_ALWAYS_ENABLED}
    };
    const pmlibSysConfigPowerStateParams_t gpioEnable[] =
    {
#if defined (CUSTOM_BOARD1)
        {PMHAL_PRCM_MOD_GPIO3, PMLIB_SYS_CONFIG_ALWAYS_ENABLED}
#else
        {PMHAL_PRCM_MOD_GPIO2, PMLIB_SYS_CONFIG_ALWAYS_ENABLED}
#endif
    };
    volatile uint32_t loopForEver = 1U;
    int32_t           retVal      = 0;
    volatile uint32_t clkValue = 0;
    /* Program the OPP NOM AVS */
    configVoltageRails();
    /* DSS */
    HW_WR_REG32(0x4a009100, 0x2);
    /* APLL_PCIE to force Idle */
    HW_WR_REG32(0x4a00821C, 0x2);
    /* DPLL_USB to auto idle low power stop mode */
    HW_WR_REG32(0x4a008188, 0x1);

    programPllsOn();
    /* Enable DSS clock */
    HW_WR_REG32(REG_CTRL_CORE_CONTROL_IO_2,
                HW_RD_REG32(REG_CTRL_CORE_CONTROL_IO_2) | 0x1);
    if (retVal == 0)
    {
        retVal =
            (int32_t) PMLIBSysConfigSetPowerState(uartEnable, (uint32_t) 1U,
                                                  PM_TIMEOUT_INFINITE,
                                                  NULL);
    }
    PlatformUART3SetPinMux();
    UARTStdioInit();

    ledPadIoConf();
    printf("\nPM Leakage Test App");
    if (retVal == 0)
    {
        retVal =
            (int32_t) PMLIBSysConfigSetPowerState(gpioEnable, (uint32_t) 1U,
                                                  PM_TIMEOUT_INFINITE,
                                                  NULL);
    }
    if (retVal == 0)
    {
        #if defined (CUSTOM_BOARD1)
        HW_WR_REG32(0x48057000 + 0x134, 0xFFFF9FFF); /* GPIO3_13 OE */
        HW_WR_REG32(0x48057000 + 0x13C, 0xFFFFDFFF); /* GPIO3_13 Dataout */
        #else
        HW_WR_REG32(0x48055000 + 0x134, 0xFFFF9FFF); /* GPIO2_13 OE */
        HW_WR_REG32(0x48055000 + 0x13C, 0xFFFFBFFF); /* GPIO2_13 Dataout */
        #endif
        printf("\n------------------------------------------------------");
        printf("\n Enabling all modules first");
        printf("\n------------------------------------------------------\n");
        alwaysEnabledConfig();
    }
    printf("\n------------------------------------------------------");
    printf("\n Setting Module states");
    printf("\n------------------------------------------------------\n");
    modulePowerDownProgram();
    setModuleStates();

    printf("\n------------------------------------------------------");
    printf("\n Setting Power Domain states");
    printf("\n------------------------------------------------------\n");
    setPowerDomainStatesForLeakage();

    printf("\n------------------------------------------------------");
    printf("\n Setting DPLL states");
    printf("\n------------------------------------------------------\n");
    setPllStates();

    printTemp();

    printf("\n------------------------------------------------------");
    printf("\n Putting IPU to clock gate and switching off UART");
    printf("\n------------------------------------------------------\n");

    if (retVal == 0)
    {
        retVal = PMLIBSysConfigSetPowerState(uartDisable, 1U,
                                             PM_TIMEOUT_INFINITE, NULL);
    }
    PMHALPdmSetPDState(PMHAL_PRCM_PD_L3INIT,
                       PMHAL_PRCM_PD_STATE_OFF,
                       PM_TIMEOUT_NOWAIT);
    /* PCIE Clock domain to HW_AUTO. This is required to make PD_L3INIT
     * power off */
    HW_WR_REG32(0x4a0093A0, 0x3);
    if (retVal == 0)
    {
        /* Enable UNICACHE for IPU*/
        /* If using gels form vision sdk please enable default conf in
         *  DRA7xx_multicore_reset    */

        HW_WR_FIELD32(
            SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE + IPU_UNICACHE_CONFIG,
            IPU_UNICACHE_CONFIG_BYPASS,
            IPU_UNICACHE_CONFIG_BYPASS_NORMAL);
        /* Set IPU_PD to On Active
         * Lets not put IPU  to PD retention as ipu being the master core in
         * VisionSDK  */

        retVal = (int32_t) PMHALPdmSetPDState(PMHAL_PRCM_PD_IPU,
                                              PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                                              PM_TIMEOUT_NOWAIT);

        retVal += (int32_t) PMHALCMSetCdClockMode(
            PMHAL_PRCM_CD_IPU,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);

        retVal += (int32_t) PMHALCMSetCdClockMode(
            PMHAL_PRCM_CD_IPU1,
            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
            PM_TIMEOUT_NOWAIT);
    }
    if (retVal == 0)
    {
        /*
         * This is required as the force override bit CTRL_CORE_SEC_IPU_WAKEUP
         * does not set the right values for the PRCM registers and when the
         * override is lifted then cores are left in a bad power and reset
         ****state.
         */
        retVal = (int32_t) PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                                             PM_TIMEOUT_NOWAIT);
        retVal += (int32_t) PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST,
                                              PM_TIMEOUT_NOWAIT);
        retVal += (int32_t) PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                               PMHAL_PRCM_MODULE_MODE_AUTO,
                                               PM_TIMEOUT_NOWAIT);
    }

    if (retVal == 0)
    {
        retVal = (int32_t) PMHALPdmSetLastPDStatus(
            PMHAL_PRCM_PD_IPU,
            PMHAL_PRCM_PD_STATE_ON_ACTIVE);
        retVal += (int32_t) PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);
    }
    if (retVal == 0)
    {
        #if defined(CUSTOM_BOARD1)
        HW_WR_REG32(0x48057000 + 0x13C, 0xFFFF9FFF); /* GPIO3_14 Dataout */
        #else
        HW_WR_REG32(0x48055000 + 0x13C, 0xFFFFFFFF); /* GPIO2_14 Dataout */
        #endif

        while (loopForEver)
        {
            PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
        }
    }

    printf("\n------------------------------------------------------");
    printf("\n Error Should not have reached here for leakage measurement ");
    printf("\n------------------------------------------------------");
    return 0;
}

void modulePowerDownProgram(void)
{
    #if 0
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE4);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE1);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE2);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE3);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_IO_SRCOMP_CORE);
    #endif
}

void setPllStates(void)
{
    pmhalPrcmNodeId_t        dpllId;
    pmhalPrcmDpllPowerMode_t dpllMode;
    int32_t status = (int32_t) PM_SUCCESS;
    /* Ensure the DPLLs are switched off when the modules go to low power */

    for (dpllId = PMHAL_PRCM_DPLL_MIN; dpllId <= PMHAL_PRCM_DPLL_MAX;
         dpllId++)
    {
        if ((dpllId != PMHAL_PRCM_DPLL_PER) && (dpllId != PMHAL_PRCM_DPLL_DDR))
        {
            PMHALCMDpllGetOperatingMode(dpllId, &dpllMode);
            if ((dpllMode != PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE) ||
                (dpllMode != PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE))
            {
                status = PMHALCMDpllSetOperationMode(
                    dpllId,
                    PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE,
                    PM_TIMEOUT_NOWAIT);
                if (PM_CM_DPLL_POWER_MODE_NOT_SUPPORTED == status)
                {
                    status = PMHALCMDpllSetOperationMode(
                        dpllId,
                        PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE,
                        PM_TIMEOUT_NOWAIT);
                }
            }
        }
    }
    for (dpllId = PMHAL_PRCM_DPLL_MIN; dpllId <= PMHAL_PRCM_DPLL_MAX;
         dpllId++)
    {
        if ((dpllId != PMHAL_PRCM_DPLL_PER) && (dpllId != PMHAL_PRCM_DPLL_DDR))
        {
            printf((char *) pmhalNodeList_names[dpllId]);
            PMHALCMDpllGetOperatingMode(dpllId, &dpllMode);
            if ((dpllMode == PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE) ||
                (dpllMode == PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE))
            {
                printf(": Set Operation Mode PASS\n");
            }
            else
            {
                printf(": Set Operation Mode FAIL\n");
            }
        }
    }
    for (dpllId = PMHAL_PRCM_DPLL_MIN; dpllId <= PMHAL_PRCM_DPLL_MAX;
         dpllId++)
    {
        uint32_t id;
        id = PMUtilsGetDpllId(dpllId);
        /* Hard coding here as the API does not support any other mode than
         * auto idle disable to support Errata i810 */
        HW_WR_FIELD32(pmhalDpllElems[id].pllAutoIdleRegAddr,
                      PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE, 0x1);
    }
}

void setPowerDomainStatesForLeakage(void)
{
    uint32_t    size = sizeof (clockDomainsForLeakage) /
                       sizeof (pmhalPrcmCdId_t);
    uint32_t    count  = 0U;
    pmErrCode_t status = PM_SUCCESS;

    for (count = 0U; count < size; count++)
    {
        status =
            (pmErrCode_t) PMHALCMSetCdClockMode(
                clockDomainsForLeakage[count],
                PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                PM_TIMEOUT_NOWAIT);
        printf((char *)
                 pmhalClkDomain_t_names[clockDomainsForLeakage[count]]);
        if (status != PM_SUCCESS)
        {
            printf(": FAIL\n");
        }
        else
        {
            printf(": PASS\n");
        }
    }
}

void alwaysEnabledConfig(void)
{
    pmlibSysConfigPowerStateParams_t inputTable;
    pmlibSysConfigErrReturn_t        resultReturn;
    pmhalPrcmModuleId_t idx;
    pmlibSysConfigPowerState_t       pwrSt;
    pmErrCode_t status = PM_SUCCESS;
    pwrSt = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
    for (idx = (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MIN;
         idx <= (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MAX;
         idx = (pmhalPrcmModuleId_t) ((uint32_t) idx + 1U))
    {
        if (idx == PMHAL_PRCM_MOD_IPU1)
        {
            continue;
        }
        PMLIBSysConfigPowerStateParams_init(&inputTable, (uint32_t) 1U);
        inputTable.modId    = idx;
        inputTable.pwrState = pwrSt;

        printf((char *) pmhalNodeList_names[idx]);
        printf(": ");
        status = PMLIBSysConfigSetPowerState(&inputTable, (uint32_t) 1U,
                                             PM_TIMEOUT_INFINITE,
                                             &resultReturn);
        if (PM_SUCCESS == status)
        {
            printf("PASS\n");
        }
        else
        {
            if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                resultReturn.failCause)
            {
                printf(
                    "No Valid Module Mode, Cannot be enabled from software\n");
                printf("Optional Clocks if any have been enabled\n");
            }
            else
            {
                printf(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ");
                UARTPutNum(resultReturn.failCause);
                printf("\n");
                finalSuccess = PM_FAIL;
            }
        }
    }
}

void programPllsOn()
{
    static pmhalPrcmPllPostDivValue_t dpllCore15X15PostDivCfgOppNom_20[] =
    {
        {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },   /* Div_m2_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_M3,  4 },   /* Div_m3_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_H11, 8 },   /* Div_h11_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H12, 4 },   /* Div_h12_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H13, 44},   /* Div_h13_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H14, 4 },   /* Div_h14_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H21, 11},   /* Div_h21_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H22, 5 },   /* Div_h22_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H23, 10},   /* Div_h23_clkcfg */
    };
    static pmhalPrcmPllPostDivValue_t dpllPerPostDivCfgOppNom_20[] =
    {
        {PMHAL_PRCM_DPLL_POST_DIV_M2,  8},  /* Div_m2_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_M3,  3},  /* Div_m3_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_H11, 6},  /* Div_h11_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H12, 8},  /* Div_h12_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H13, 8},  /* Div_h13_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H14, 4}   /* Div_h14_clkcfg */
    };
    static pmhalPrcmPllPostDivValue_t dpllGmac15X15PostDivCfgOppNom_20[] =
    {
        {PMHAL_PRCM_DPLL_POST_DIV_M2,  4 },  /* Div_m2_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_M3,  4 },  /* Div_m3_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_H11, 40},  /* Div_h11_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H12, 8 },  /* Div_h12_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H13, 4 },  /* Div_h13_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_H14, 25}   /* Div_h13_clkcfg */
    };
    static pmhalPrcmPllPostDivValue_t dpllEveVidDsp15X15PostDivCfgOppNom_20[] =
    {
        {PMHAL_PRCM_DPLL_POST_DIV_M2, 1},    /* Div_m2_clkcfg  */
        {PMHAL_PRCM_DPLL_POST_DIV_M3, 2}     /* Div_m3_clkcfg  */
    };
    static pmhalPrcmDpllConfig_t      dpllCore15X15CfgOppNom_20 =
    {
        266,                                  /* Multiplier */
        4,                                    /* Divider */
        0,                                    /* DutyCycleCorrector */
        dpllCore15X15PostDivCfgOppNom_20,
        (sizeof (dpllCore15X15PostDivCfgOppNom_20) /
         sizeof (pmhalPrcmPllPostDivValue_t)),
        0
    };
    static pmhalPrcmDpllConfig_t      dpllPerCfgOppNom_20 =
    {
        192,
        4,
        0,
        dpllPerPostDivCfgOppNom_20,
        (sizeof (dpllPerPostDivCfgOppNom_20) /
         sizeof (pmhalPrcmPllPostDivValue_t)),
        0
    };
    static pmhalPrcmDpllConfig_t      dpllGmac15X15CfgOppNom_20 =
    {
        250,                                  /* Multiplier */
        4,                                    /* Divider */
        0,                                    /* DutyCycleCorrector */
        dpllGmac15X15PostDivCfgOppNom_20,
        (sizeof (dpllGmac15X15PostDivCfgOppNom_20) /
         sizeof (pmhalPrcmPllPostDivValue_t)),
        0
    };
    static pmhalPrcmDpllConfig_t      dpllEveVidDsp15X15CfgOppNom_20 =
    {
        238,                                  /* Multiplier */
        7,                                    /* Divider */
        0,                                    /* DutyCycleCorrector */
        dpllEveVidDsp15X15PostDivCfgOppNom_20,
        (sizeof (dpllEveVidDsp15X15PostDivCfgOppNom_20) /
         sizeof (pmhalPrcmPllPostDivValue_t)),
        0
    };
    PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_CORE,
                         &dpllCore15X15CfgOppNom_20,
                         PM_TIMEOUT_INFINITE);
    PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PER,
                         &dpllPerCfgOppNom_20,
                         PM_TIMEOUT_INFINITE);
    PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DSP_GMAC,
                         &dpllGmac15X15CfgOppNom_20,
                         PM_TIMEOUT_INFINITE);
    PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                         &dpllEveVidDsp15X15CfgOppNom_20,
                         PM_TIMEOUT_INFINITE);
}

void setModuleStates(void)
{
    uint32_t                  i = 0U;
    pmhalPrcmModuleId_t       idx;
    pmErrCode_t               status = PM_SUCCESS;
    pmlibSysConfigErrReturn_t resultReturn[sizeof (gInputTable) /
                                           sizeof (
                                               pmlibSysConfigPowerStateParams_t)
    ];

    status =
        PMLIBSysConfigSetPowerState(gInputTable, (uint32_t) numTableEntries,
                                    PM_TIMEOUT_INFINITE,
                                    resultReturn);
    if (PM_SUCCESS == status)
    {
        printf("All Module Power Status Success... Printing Pass status\r\n");
    }

    /* Need an extra step for CD_L4SEC and CD_L3INIT to disable */
    status = (pmErrCode_t) PMHALCMSetCdClockMode(
        PMHAL_PRCM_CD_L3INIT,
        PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
        PM_TIMEOUT_INFINITE);

    for (i = 0U; i < numTableEntries; i++)
    {
        idx = gInputTable[i].modId;
        if (idx < PMHAL_PRCM_MOD_COUNT)
        {
            printf((char *) pmhalNodeList_names[idx]);
        }
        printf(": ");
        if (PMLIB_SYS_CONFIG_ALWAYS_ENABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                printf("PMLIB_SYS_CONFIG_ALWAYS_ENABLED PASS\r\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                printf(
                    "No Valid Module Mode, Cannot be enabled from software\r\n");
                printf("Optional Clocks if any have been enabled\r\n");
            }
            else
            {
                printf(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ");
                UARTPutNum(resultReturn[i].failCause);
                printf("\r\n");
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_DISABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                printf("PMLIB_SYS_CONFIG_DISABLED PASS\r\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED ==
                     resultReturn[i].failCause)
            {
                printf(
                    "No Valid Module Mode, Cannot be disabled from software\r\n");
                printf("Optional Clocks if any have been disabled\r\n");
            }
            else if (PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES ==
                     resultReturn[i].failCause)
            {
                printf("Module has dependencies\r\n");
            }
            else
            {
                printf(
                    "PMLIB_SYS_CONFIG_DISABLED FAIL :Error Code Returned : ");
                UARTPutNum(resultReturn[i].failCause);
                printf("\r\n");
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_AUTO_CG == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                printf("PMLIB_SYS_CONFIG_AUTO_CG PASS\r\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                printf(
                    "No Valid Module Mode, Cannot be enabled from software\r\n");
                printf("Optional Clocks if any have been enabled\r\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG ==
                     resultReturn[i].failCause)
            {
                printf(
                    "No Valid CLKCTLR Register. Cannot be auto clock gated\r\n");
            }
            else
            {
                printf(
                    "PMLIB_SYS_CONFIG_AUTO_CG FAIL :Error Code Returned : ");
                UARTPutNum(resultReturn[i].failCause);
                printf("\r\n");
                finalSuccess = PM_FAIL;
            }
        }
    }
}

void ledPadIoConf(void)
{
#if defined (CUSTOM_BOARD1)
    pad_config_t pad_config;
    /* GPIO3_13 */
    pad_config.pin_num         = CTRL_CORE_PAD_IO_VOUT1_D20;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /* GPIO3_14 */
    pad_config.pin_num         = CTRL_CORE_PAD_IO_VOUT1_D21;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
#elif defined(CUSTOM_BOARD2)
    pad_config_t pad_config;
    /* GPIO2_13 */
    pad_config.pin_num         = CTRL_CORE_PAD_IO_VIN1A_D10;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
    /* GPIO2_14 */
    pad_config.pin_num         = CTRL_CORE_PAD_IO_VIN1A_D11;
    pad_config.muxmode         = 14;
    pad_config.input_enable    = INPUTENABLE_DISABLE;
    pad_config.pullud_enable   = PULLUDENABLE_ENABLE;
    pad_config.pull_typeselect = PULLTYPESELECT_PULL_UP;
    pad_config.wakeup_enable   = WAKEUPENABLE_DISABLE;
    pad_config.slewcontrol     = SLEWCONTROL_FAST_SLEW;
    cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE, &pad_config);
#endif
}

void printTemp()
{
    pmhalBgapRange_t currTempRange = {0, 0};
    int32_t          retVal        = PM_SUCCESS;

    printf("\r\n----------------------------------------");
    printf("\r\n Measure the Current Temperature");
    printf("\r\n----------------------------------------");
    printf("\r\nVoltage Domain: ");
    printf("%s", voltageDomain_t_names[gVoltId]);
    retVal = PMHALBgapGetCurrTemperature(gVoltId, &currTempRange);

    if (PM_SUCCESS == retVal)
    {
        printf(
            "\r\nCurrent Temperature Range in Degrees C = [%u.%u , %u.%u]",
            currTempRange.minTemp / 1000, (currTempRange.minTemp % 1000),
            currTempRange.maxTemp / 1000, (currTempRange.maxTemp % 1000));
    }
    else
    {
        printf("\r\nGet Current Temperature Failed!!");
    }
}

pmhalLP8733RegulatorMap_t gCustomBoardLP8733RegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) 0x1,
        #if defined (CUSTOM_BOARD1)
        (uint8_t) 0x59U
        #else
        (uint8_t) 0x60U
        #endif
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) 0x1,
        #if defined (CUSTOM_BOARD1)
        (uint8_t) 0x59U
        #else
        (uint8_t) 0x60U
        #endif
    }
};

int32_t configVoltageRails()
{
    int32_t retVal = PM_SUCCESS;
    int32_t vdId;
    const pmhalPmicOperations_t *pmicOps;

    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALI2CCommRegister(&gPmicI2cfunc);
#if defined(CUSTOM_BOARD1) || defined(CUSTOM_BOARD2)
    pmicOps = PMHALLP8733GetPMICOps();
    PMHALLP8733ConfigureRegulatorMap(gCustomBoardLP8733RegulatorTable);
#else
    pmicOps = PMHALTps65917GetPMICOps();
#endif
    retVal = PMHALPmicRegister(pmicOps);

#if defined(CUSTOM_BOARD2)
    {
        uint8_t regAddr = 0x17U;
        uint8_t regValue = 0U;
        SblUtilsI2cInit();
        // PG_FAULT
        SblUtilsI2cReadByte(1U, PMHAL_LP8733_CHIP_ADDRESS_1, &regAddr, &regValue, 1U);
        regValue = regValue | 0xF;
        SblUtilsI2cWriteByte(1U, PMHAL_LP8733_CHIP_ADDRESS_1, &regAddr, &regValue, 1U);
        // PGOOD_CTRL_2
        regAddr = 0x16U;
        regValue = 0U;
        SblUtilsI2cReadByte(1U, PMHAL_LP8733_CHIP_ADDRESS_1, &regAddr, &regValue, 1U);
        regValue = regValue & 0xFE;
        SblUtilsI2cWriteByte(1U, PMHAL_LP8733_CHIP_ADDRESS_1, &regAddr, &regValue, 1U);
    }
#endif
    /* Set the voltage for PMHAL_PRCM_VD_CORE and PMHAL_PRCM_VD_DSPEVE. */
    for (vdId = (int32_t) PMHAL_PRCM_VD_MIN;
         vdId < (int32_t) PMHAL_PRCM_VD_COUNT;
         vdId++)
    {
        retVal += PMHALVMSetOpp((pmhalPrcmVdId_t) vdId,
                                (pmhalVmOppId_t) PMHAL_VM_OPP_NOM,
                                PM_TIMEOUT_INFINITE);
    }
    return retVal;
}

static int32_t SblUtilsI2cInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    #if defined(CUSTOM_BOARD1) || defined (CUSTOM_BOARD2)
    uint32_t baseAddr = SOC_I2C2_BASE;
    #else
    uint32_t baseAddr = SOC_I2C1_BASE;
    #endif
    /* Force Wake-up clock domain L4PER1 */
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER1,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_NOWAIT);

    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C2,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /*
     * Do a soft reset so we can clear any incorrect state and
     * configure to suit the PMIC communication.
     */
    I2CSoftReset(baseAddr);

    /*
     * Ensure that the reset is completed. The RDONE bit is set
     * only when the I2C is enabled, so enable I2C before
     * checking for the reset completion.
     */
    I2CMasterEnable(baseAddr);

    timeout = 50U;  /* Approximately 50ms */
    while ((I2CSystemStatusGet(baseAddr) !=
            I2C_SYSS_RDONE_RSTCOMP)
           && (timeout > 0))
    {
        PMUtilsMinDelayMS((uint32_t) 1U);
        timeout--;
    }

    if (timeout == 0)
    {
        status = STW_EFAIL;
    }

    if (status == STW_SOK)
    {
        /* Disable I2C so we can configure for the PMIC communication. */
        I2CMasterEnable(baseAddr);

        /* Configure the I2C BUS clock frequency (I2C_SCL). */
        I2CMasterInitExpClk(baseAddr,
                            SBL_UTILS_I2C_SYSTEM_CLOCK,
                            SBL_UTILS_I2C_INTERNAL_CLOCK,
                            SBL_UTILS_I2C_OUTPUT_CLOCK);

        /*
         * The PMIC communication is always as a master so we don't have
         * to configure the I2C own address. However, it doesn't hurt.
         */
        I2COwnAddressSet(baseAddr, 0,
                         I2C_OWN_ADDR_0);

        /*
         * Make sure the I2C is not in Forced Idle Mode by setting it to No
         * Idle mode.
         */
        I2CSyscInit(baseAddr,
                    (uint32_t) (I2C_AUTOIDLE_DISABLE |
                                I2C_CUT_OFF_BOTH_CLK |
                                I2C_ENAWAKEUP_DISABLE |
                                I2C_NO_IDLE_MODE));

        /*
         * Configure the I2C:
         *    Select Fast/Standard Mode
         *    Select normal mode (vs. start byte mode)
         *    Select 7-bit slave address mode
         *
         * Note that this API writes the 32-bit value passed to the I2C_CON
         * register; the config bits not mentioned below is set to zero.
         */
        I2CConfig(baseAddr, I2C_CFG_N0RMAL_MODE |
                  I2C_CFG_7BIT_SLAVE_ADDR |
                  I2C_OPMODE_FAST_STAND_MODE);

        /* PMIC Comm uses polling mode; disable all the interrupts. */
        I2CMasterIntDisableEx(baseAddr, I2C_INT_ALL);

        /*
         * Bypass the Tx/Rx FIFO. For PRCM access we always read one byte
         * at a time so FIFO is bypassed.
         */
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_TX_MODE);
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_RX_MODE);
        I2CFIFOClear(baseAddr, I2C_TX_MODE);
        I2CFIFOClear(baseAddr, I2C_RX_MODE);

        /* Enable I2C module. */
        I2CMasterEnable(baseAddr);

        /*
         * This is required to ensure that the I2C communication continues
         * even if A15 (the master core) is debug halted on a breakpoint.
         */
        I2CMasterEnableFreeRun(baseAddr);
    }

    /* Clear status register  */
    I2CMasterIntClearEx(baseAddr, I2C_INT_ALL);

    return status;
}

static int32_t SblUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   uint8_t *regValue,
                                   uint32_t numRegs)
{
    int32_t status = STW_SOK;
    status = SblUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == STW_SOK)
    {
        status = SblUtilsI2cRead(i2cNum, (uint8_t) i2cDevAddr, regValue);
    }
    else
    {
        *regValue = 0U;
    }
    return status;
}

static int32_t SblUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    const uint8_t *regValue,
                                    uint32_t numRegs)
{
    uint8_t  data[2];
    uint8_t  count       = (uint8_t) 2U;
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    data[0] = *regAddr;
    data[1] = *regValue;
    status  = SblUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, data, count);

    if (status == STW_SOK)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = SblUtilsI2cWaitForFlags(i2cNum,
                                         I2C_INT_BUS_FREE |
                                         I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t SblUtilsI2cRead(uint32_t i2cNum,
                               uint8_t  slaveAddr,
                               uint8_t *value)
{
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /* Set the slave address */
    I2CMasterSlaveAddrSet(baseAddress,
                          (uint32_t) slaveAddr);

    /* Configure to read 1 data word from the PMIC register.  */
    I2CSetDataCount(baseAddress, (uint32_t) 1U);

    /*
     * Configure i2c as master-receive and enable.
     * Make sure stop condition is generated after the transaction.
     */
    I2CMasterControl(baseAddress,
                     (uint32_t) (I2C_CFG_MST_RX | I2C_CFG_START | I2C_CFG_STOP));

    /* Read the data if the data is ready. */
    status = SblUtilsI2cCheckXfrStatus(i2cNum,
                                       (uint32_t) SBL_UTILS_I2C_READ);
    if (status == STW_SOK)
    {
        *value = I2CMasterDataGet(baseAddress);
    }
    else
    {
        *value = 0U;
    }

    /* Wait for I2C access ready before returning. */
    if (status == STW_SOK)
    {
        uint32_t flags = I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_FREE;
        status = SblUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t SblUtilsI2cWrite(uint32_t i2cNum,
                                uint8_t slaveAddr, const uint8_t data[],
                                uint8_t count)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint8_t  i;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    status = SblUtilsI2cWaitForBB(i2cNum);

    if (status == STW_SOK)
    {
        /* Set the slave address */
        I2CMasterSlaveAddrSet(baseAddress,
                              (uint32_t) slaveAddr);

        /* Configure to send 'count' data words */
        I2CSetDataCount(baseAddress, (uint32_t) count);

        /*
         * Configure i2c as master-transmitter, enable and set start condition.
         * Stop condition is NOT generated as this could be a part of write
         * followed by read (combined format).
         */
        I2CMasterControl(baseAddress,
                         I2C_CFG_MST_TX | I2C_CFG_START);

        /* Transmit 'count' bytes.  */
        for (i = 0; ((i < count) && (status == STW_SOK)); i++)
        {
            /*
             * Check the status to see if the data can be transferred and
             * send data.
             */
            status = SblUtilsI2cCheckXfrStatus(
                i2cNum,
                (uint32_t)
                SBL_UTILS_I2C_WRITE);
            if (status == PM_SUCCESS)
            {
                I2CMasterDataPut(baseAddress, data[i]);
            }

            /* Clear XRDY flags */
            rawSt = I2CMasterIntRawStatus(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_TRANSMIT_READY);
        }

        /*
         * Once we complete writing the 'count' bytes, wait for the
         * ARDY flag to be set. This flag indicates that the I2C
         * is access ready for next transmission. ARDY can also be
         * set if we received NACK so ensure it is not the case.
         */
        if (status == STW_SOK)
        {
            status = SblUtilsI2cWaitForFlags(i2cNum, I2C_INT_ADRR_READY_ACESS);
            if (status == STW_SOK)
            {
                rawSt = I2CMasterIntRawStatus(baseAddress);
                if ((rawSt & I2C_INT_NO_ACK) != 0)
                {
                    status = STW_EFAIL;
                    /* Clear the NACK flag. */
                    I2CMasterIntClearEx(baseAddress,
                                        rawSt & I2C_INT_NO_ACK);
                }

                /* Clear the ARDY flag. */
                I2CMasterIntClearEx(baseAddress,
                                    rawSt & I2C_INT_ADRR_READY_ACESS);
            }
        }
    }

    return status;
}

static int32_t SblUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint32_t flags = I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                     I2C_INT_ARBITRATION_LOST;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    if (xfr == SBL_UTILS_I2C_WRITE)
    {
        flags |= I2C_INT_TRANSMIT_READY;
    }
    else if (xfr == SBL_UTILS_I2C_READ)
    {
        flags |= I2C_INT_RECV_READY;
    }
    else
    {
        status = STW_EFAIL;
    }

    /*
     * Wait for any of the following conditions to occur and
     * handle them in the loop before transmitting data.
     * NACK, AL, XRDY/RRDY, ARDY
     */
    if (status == STW_SOK)
    {
        status = SblUtilsI2cWaitForFlags(i2cNum, flags);
    }

    if (status == STW_SOK)
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);

        /*
         * When I2C is configured as master-transmitter and didn't
         * receive ACK from slave, NACK condition is generated. The
         * following could cause this situation:
         * 1. No receiver is present on the bus with the transmitted
         *    address; board issue
         * 2. Receiver is not ready to communicate with the master
         *    (probably a board/pmic device issue).
         * 3. Receiver gets data or commands it doesn't understand
         *    (incorrect PMIC)
         * 4. Receiver can't receive any more data bytes.
         *
         * NACK can be handled by a master by either generating a
         * STOP condition or a repeated START condition to start
         * a new transfer. In PMIC COMM we generate a STOP
         * condition to abort the transfer and clear the NACK
         * flag.
         *
         * I2C HW clears STT and STP bits in I2C_CON registers.
         */
        if ((rawSt & I2C_INT_NO_ACK) != 0)
        {
            I2CMasterStop(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_NO_ACK);
            status = STW_EFAIL;
        }
        /*
         * Arbitration loss occurs when multiple masters initiate
         * transfer at the same time. Only one master wins and others
         * loose the arbitration. The arbitration loss flag is set
         * if this local host lost the arbitration. After an
         * arbitration loss, the local host can continue to generate
         * clock till the end of the byte transfer on the bus and
         * must restart the transmission. Recovering from arbitration
         * loss slightly complicates the code and this can be added
         * if there is a need. At present we clear the flag  and
         * return error.
         *
         * When arbitration loss occurs, the I2C HW clears the
         * STT, STP and MST bits. The local host switches to the
         * slave mode.
         */
        else if ((rawSt & I2C_INT_ARBITRATION_LOST) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ARBITRATION_LOST);
            status = STW_EFAIL;
        }
        /*
         * ARDY flag is set to indicate that the local host is access
         * ready. We are in the middle of a data transfer and hence
         * it is bad if we get ARDY flag set. For example, if we
         * get NACKed, the ARDY flag is set in the middle of data
         * transfer.
         */
        else if ((rawSt & I2C_INT_ADRR_READY_ACESS) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ADRR_READY_ACESS);
            status = STW_EFAIL;
        }
        /*
         * XRDY flag is set when the TX FIFO is empty or the TX FIFO
         * threshold is not reached. This means the local host can
         * transmit now.
         *
         * RRDY flag is set when the RX FIFO is empty or the RX FIFO
         * threshold is not reached. This means the local host can
         * receive now.
         */
        else if (((xfr == SBL_UTILS_I2C_WRITE) &&
                  ((rawSt & I2C_INT_TRANSMIT_READY) != 0)) ||
                 ((xfr == SBL_UTILS_I2C_READ) &&
                  ((rawSt & I2C_INT_RECV_READY) != 0)))
        {
            /*
             * Return success so that the caller can send/receive the data
             * Note that the caller needs to clear the XRDY/RRDY flag as
             * needed.
             */
            status = STW_SOK;
        }
        else
        {
            /*
             * We should not get here...
             */
            status = STW_EFAIL;
        }
    }

    return status;
}

static int32_t SblUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t rawSt;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    timeout = SBL_UTILS_I2C_TIMEOUT_COUNT;

    rawSt = I2CMasterIntRawStatus(baseAddress);

    while (((rawSt & flags) == 0) && (timeout > 0U))
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);
        timeout--;
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    return status;
}

static int32_t SblUtilsI2cWaitForBB(uint32_t i2cNum)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Clear all current interrupts first.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    for (timeout = SBL_UTILS_I2C_TIMEOUT_COUNT; timeout > 0U; --timeout)
    {
        if (I2CMasterBusBusy(baseAddress) == 0)
        {
            break;
        }
        I2CMasterIntClearEx(baseAddress, I2C_INT_BUS_BUSY);
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    /*
     * Clear all current interrupts.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    return status;
}
