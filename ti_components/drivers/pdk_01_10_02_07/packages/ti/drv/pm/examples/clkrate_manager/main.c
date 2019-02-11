/*
 *  Copyright (C) 2014-17 Texas Instruments Incorporated
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
 *  \file main_tda2xx.c
 *
 *  \brief Clock Rate Manager Library Example Application
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_i2c.h>
#include <ti/drv/pm/include/pmlib_sysconfig.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/pmlib_clkrate.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm_modinc.h>
#include <ti/drv/pm/include/prcm/hw_pmhal_data_names.h>
#include <ti/drv/pm/include/prcm/pmhal_cm.h>
#include <ti/drv/pm/include/prcm/pmhal_mm.h>
#include <ti/drv/pm/include/prcm/pmhal_vm.h>
#include <ti/drv/pm/include/prcm/pmhal_pmic.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/prcm/pmhal_i2cComm.h>
#if defined (SOC_TDA2PX)
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp87565.h>
#endif
#if defined (SOC_TDA2XX)
#include <ti/drv/pm/include/pmic/pmhal_tps659039.h>
#endif
#if defined (SOC_TDA2EX)
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#endif
#if defined (SOC_TDA3XX)
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8731.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#endif
#include "app_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))
/**
 * \brief Macro to find the number of elements of the array.
 */

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define PM_TEST_UTILS_I2C_SYSTEM_CLOCK       (96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define PM_TEST_UTILS_I2C_INTERNAL_CLOCK     (9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define PM_TEST_UTILS_I2C_OUTPUT_CLOCK       (400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define PM_TEST_UTILS_I2C_TIMEOUT_COUNT      (4000U)

/** Write Flag used when checking for the transfer status. */
#define PM_TEST_UTILS_I2C_WRITE              (1U)

/** Read Flag used when checking for the transfer status. */
#define PM_TEST_UTILS_I2C_READ               (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Structure contains variables used by the example for automated
 *        debugging and testing
 */
typedef struct
{
    pmhalPrcmModuleId_t modId;
    /**< module Id */
    pmhalPrcmClockId_t  clkId;
    /**< clock Id */
    uint32_t            clkRate;
    /**< clock rate for setting */
}moduleClockList_t;

#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
typedef enum sblUtilsVdGangNum
{
    SBLUTILS_VD_NOT_GANGED = 0,
    /**< Voltage rail is not ganged. Connected individually from PMIC output. */
    SBLUTILS_VD_GANG_1     = 1,
    /**< Voltage rail is ganged. All the voltage rails with same gang id are
     *  connected to same output of PMIC (LDO/SMPS).
     */
    SBLUTILS_VD_GANG_2     = 2,
    /**< Voltage rail is ganged. All the voltage rails with same gang id are
     *  connected to same output of PMIC (LDO/SMPS).
     */
    SBLUTILS_VD_GANG_MAX   = SBLUTILS_VD_GANG_2,
    /**< Maximum number of ganged voltage rails */
}sblUtilsVdGangNum_t;

typedef struct sblUtilsVdInfo
{
    pmhalPrcmVdId_t         vdId;
    /**< Voltage domain id. */
    sblUtilsVdGangNum_t     gangId;
    /**< The gang id to which the voltage domain is connected. */
}sblUtilsVdInfo_t;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t PmTestUtilsI2cInit(void);

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
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
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
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                       const uint8_t *regAddr,
                                       const uint8_t *regValue,
                                       uint32_t numRegs);
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cWaitForBB(uint32_t i2cNum);

/**
 * \brief  Poll for the given flags and return when any of the flags is set or
 *         timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   flags       Flag to be waited for.
 *
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

/**
 * \brief  Write the given number of bytes to the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   data        Data to be written.
 * \param   count       Number of Bytes to be written.
 *
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cWrite(uint32_t i2cNum,
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
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cRead(uint32_t i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t *value);

/**
 * \brief Check the status of the transfer and handle the error conditions.
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 * \param   xfr     Transfer Type. Can be any one of PM_TEST_UTILS_I2C_WRITE or
 *                  PM_TEST_UTILS_I2C_READ.
 *
 * \retval  status      Pass or fail value of the operations. PM_SUCCESS - If Pass
 *                      PM_FAIL - If Fail
 */
static int32_t PmTestUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
static int32_t SblUtilsConfigGangedVdRails(const pmhalPrcmVdId_t *gangedVdRails,
                                           uint32_t           numGangedRails,
                                           uint32_t           oppId);
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA2EX)
/* Table mapping from SMPS/LDO to Voltage Rails on the device */
pmhalLP8733RegulatorMap_t         gJ6Eco17x17LP8733RegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MPU */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_IVA */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_GPU */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MMC13V3 */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_SHV5.
     * This is not connected  for J6 Eco 17X17 Evm. */
    {
        NULL,
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    }
};
#endif

/**
 * \brief Holds the root clock frequencies specific for a given platform
 */
static uint32_t         *gRootClkFreqList;

/**
 * \brief Holds the voltage domains information whose rails are shared
 */
static pmlibBoardVdRailShare_t           *gVdRailShareList;

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
static moduleClockList_t cpuClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_HYD_GCLK,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GENERIC,
        532000000U
    },
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        600000000U
    },
#ifndef SOC_TDA2EX
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        650000000U
    },
#if defined (SOC_TDA2XX)
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1500000000U
    },
#endif
#endif
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1176000000U
    }
};
#endif
#if defined(SOC_TDA3XX)
static moduleClockList_t cpuClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_IPU1,
        PMHAL_PRCM_CLK_GENERIC,
        212800000U
    }
};
#endif

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
static moduleClockList_t cpuBypClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        700000000U
    },
#ifndef SOC_TDA2EX
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        650000000U
    },
#endif
};
#endif
#if defined(SOC_TDA3XX)
static moduleClockList_t cpuBypClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        500000000U
    }
};
#endif

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
static moduleClockList_t moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_DSS,    PMHAL_PRCM_CLK_DSS_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_CPGMAC, PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     451584000},
    {PMHAL_PRCM_MOD_I2C5,   PMHAL_PRCM_CLK_IPU_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MCASP1, PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     56448000},
    {PMHAL_PRCM_MOD_TIMER5, PMHAL_PRCM_CLK_TIMER5_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_DCAN1,  PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     22579200},
    {PMHAL_PRCM_MOD_GPIO1,  PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
};
#endif
#if defined(SOC_TDA2EX)
static moduleClockList_t moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_DSS,         PMHAL_PRCM_CLK_DSS_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_CPGMAC,      PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER10,     PMHAL_PRCM_CLK_TIMER10_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCSPI4,      PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART2,       PMHAL_PRCM_CLK_UART2_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC4,        PMHAL_PRCM_CLK_MMC4_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_COUNTER_32K, PMHAL_PRCM_CLK_FUNC_32K_CLK,
     32786},
    {PMHAL_PRCM_MOD_I2C6,        PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
};
#endif
#if defined(SOC_TDA3XX)
static moduleClockList_t moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_MCASP1, PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     24000000},
    {PMHAL_PRCM_MOD_MCASP1, PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     5000000},
    {PMHAL_PRCM_MOD_TIMER7, PMHAL_PRCM_CLK_TIMER7_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_I2C2,   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO2,  PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_DCAN2,  PMHAL_PRCM_CLK_DCAN2_SYS_CLK,
     20000000},
    {PMHAL_PRCM_MOD_QSPI,   PMHAL_PRCM_CLK_QSPI_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_TIMER1, PMHAL_PRCM_CLK_TIMER1_GFCLK,
     10000000}
};
#endif
/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalI2cCommOperations_t gPmicI2cfunc = {
    &PmTestUtilsI2cInit,
    &PmTestUtilsI2cReadByte,
    &PmTestUtilsI2cWriteByte,
    NULL,
    NULL
};

int32_t gTestStatus = PM_SUCCESS;
const pmhalPmicOperations_t *pmicOperations;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void ClkRateLibCpuTest(void)
{
    pmErrCode_t status;

    uint32_t    idx;
    AppUtils_printf("\r\nClkrate Manager Cpu Set and Get Frequency test: \r\n");
    uint32_t    size = VSIZE_TYPE(cpuClockTestList, moduleClockList_t);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        #if defined (SOC_TDA2PX)
        if ((cpuClockTestList[idx].modId == PMHAL_PRCM_MOD_MPU) || 
           (cpuClockTestList[idx].modId == PMHAL_PRCM_MOD_GPU))
        {
            pmicOperations = PMHALLP87565GetPMICOps();
        }
        else
        {
            pmicOperations = PMHALTps65917GetPMICOps();
        }
        status = (pmErrCode_t) PMHALPmicRegister(pmicOperations);
        #endif
        status = PMLIBClkRateGet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            AppUtils_printf(
                "\r\nthe Clock Rate passed for ModID %s ClkId %s is %u Hz",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            AppUtils_printf(
                "\r\nGetClockRate failed for ModID %s ClkId %s ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId]);
            gTestStatus = PM_FAIL;
        }
        status = PMLIBClkRateSet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 cpuClockTestList[idx].clkRate);
        if (status == PM_SUCCESS)
        {
            AppUtils_printf("\r\nClockSET for ModID %s ClkId %s Passed",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        else if (status == PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ)
        {
            AppUtils_printf("\r\nClockSET for ModID %s ClkId %s Passed",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        else
        {
            AppUtils_printf("\r\nClockSET for ModID %s ClkId %s Failed: %d",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId],
                       status);
            gTestStatus = PM_FAIL;
        }
        status = PMLIBClkRateGet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 &clkGetRate);
        if (status == PM_SUCCESS)
        {
            AppUtils_printf(
                "\r\nAfter Clock Rate Set, the Clock Rate for ModID %s ClkId %s is %u Hz  \r\n ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            AppUtils_printf(
                "\r\nAfter Clock Rate Set, Get ClockRate failed for ModID %s ClkId %s \r\n",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId]);
            gTestStatus = PM_FAIL;
        }
    }
    AppUtils_printf("\r\nClkrate Manager Cpu Set and Get Frequency test Completed!!\r\n");
}

static void ClkRateLibCpuBypassFreqTest(void)
{
    pmErrCode_t       status;

    uint32_t          idx;
#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    pmhalPrcmNodeId_t dpllId = PMHAL_PRCM_DPLL_DSP;
#endif
#if defined(SOC_TDA3XX)
    pmhalPrcmNodeId_t dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
#endif
    AppUtils_printf("\r\nClkrate Manager Bypass Freq Test: \r\n");
    uint32_t          size = VSIZE_TYPE(cpuBypClockTestList, moduleClockList_t);
    PMHALCMDpllSetBypassClkSelect(dpllId,
                                  PMHAL_PRCM_DPLL_BYP_CLKINPULOW);
    PMHALCMDpllUnLock(dpllId);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        status = PMLIBClkRateGet(cpuBypClockTestList[idx].modId,
                                 cpuBypClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            AppUtils_printf(
                "\r\nthe Clock Rate passed for ModID %s ClkId %s is %u Hz \r\n ",
                pmhalNodeList_names[cpuBypClockTestList[idx].modId],
                pmhalClockList_names[cpuBypClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            AppUtils_printf(
                "\r\nGetClockRate failed for ModID %s ClkId %s \r\n",
                pmhalNodeList_names[cpuBypClockTestList[idx].modId],
                pmhalClockList_names[cpuBypClockTestList[idx].clkId]);
            gTestStatus = PM_FAIL;
        }
    }
    AppUtils_printf("\r\nClkrate Manager Bypass Freq Test Completed!!\r\n");
}

static void ClkRateLibModuleSetTest(void)
{
    pmErrCode_t status;

    uint32_t    idx;
    AppUtils_printf("\r\nClkrate Manager Module Set Frequency test: \r\n");
    uint32_t    size = VSIZE_TYPE(moduleClockTestList, moduleClockList_t);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        status = PMLIBClkRateGet(moduleClockTestList[idx].modId,
                                 moduleClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            AppUtils_printf(
                "\r\nthe Clock Rate passed for ModID %s ClkId %s with clkrate %u Hz ",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            AppUtils_printf(
                "\r\nGetClockRate failed for ModID %s ClkId %s with errorcode %u",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                status);
            gTestStatus = PM_FAIL;
        }
        status = PMLIBClkRateSet(moduleClockTestList[idx].modId,
                                 moduleClockTestList[idx].clkId,
                                 moduleClockTestList[idx].clkRate);
        if (status == PM_SUCCESS)
        {
            AppUtils_printf(
                "\r\nClockSET for ModID %s ClkId %s Passed for clkRate %u Hz",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else if (status == PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ)
        {
            AppUtils_printf(
                "\r\nClockSET for ModID %s ClkId %s Passed for clkRate %u Hz",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else
        {
            AppUtils_printf(
                "\r\nClockSET for ModID %s ClkId %s Failed for clkRate %u Hz with errorcode %d",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate,
                status);
            gTestStatus = PM_FAIL;
        }
        status = PMLIBClkRateGet(moduleClockTestList[idx].modId,
                                 moduleClockTestList[idx].clkId,
                                 &clkGetRate);
        if (status == PM_SUCCESS)
        {
            if (clkGetRate == moduleClockTestList[idx].clkRate)
            {
                AppUtils_printf(
                    "\r\nAfter Clock Rate Set,Clock Rate for ModID %s ClkId %s is %u Hz \r\n",
                    pmhalNodeList_names[moduleClockTestList[idx].modId],
                    pmhalClockList_names[moduleClockTestList[idx].clkId],
                    clkGetRate);
            }
            else
            {
                AppUtils_printf(
                    "\r\nAfter Clock Rate Set, Clock Rate failed for ModID %s ClkId %s for %u Hz and current rate is %u Hz  \r\n",
                    pmhalNodeList_names[moduleClockTestList[idx].modId],
                    pmhalClockList_names[moduleClockTestList[idx].clkId],
                    moduleClockTestList[idx].clkRate,
                    clkGetRate);
                gTestStatus = PM_FAIL;
            }
        }
        else
        {
            AppUtils_printf(
                "\r\nAfter Clock Rate Set, Get ClockRate failed for ModID %s ClkId %s with errorcode %u\r\n",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                status);
            gTestStatus = PM_FAIL;
        }
    }
    AppUtils_printf("\r\nClkrate Manager module Set Frequency test Completed!!\n\r\n");
}
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined(SOC_TDA2EX)
int32_t INIT(void)
{
    int32_t         retVal = (int32_t) PM_SUCCESS;
    pmhalVmOppId_t  oppId;
    sblUtilsVdInfo_t   *vdInfoObj = NULL;
    uint32_t            numVdConfigured = 0U, vdInfoSize, index;
    uint32_t            gangNum, numGangedRails;
    pmhalPrcmVdId_t     gangedVdRails[PMHAL_PRCM_VD_MAX] = {(pmhalPrcmVdId_t) 0};

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    sblUtilsVdInfo_t vdInfo_tda2xx[PMHAL_PRCM_VD_MAX] = {
        {PMHAL_PRCM_VD_MPU,     SBLUTILS_VD_NOT_GANGED},
        {PMHAL_PRCM_VD_CORE,    SBLUTILS_VD_NOT_GANGED},
        {PMHAL_PRCM_VD_IVAHD,   SBLUTILS_VD_NOT_GANGED},
        {PMHAL_PRCM_VD_DSPEVE,  SBLUTILS_VD_NOT_GANGED},
        {PMHAL_PRCM_VD_GPU,     SBLUTILS_VD_NOT_GANGED},
    };
#else
    sblUtilsVdInfo_t vdInfo_tda2ex[PMHAL_PRCM_VD_MAX] = {
        {PMHAL_PRCM_VD_MPU,     SBLUTILS_VD_NOT_GANGED},
        {PMHAL_PRCM_VD_CORE,    SBLUTILS_VD_NOT_GANGED},
        {PMHAL_PRCM_VD_IVAHD,   SBLUTILS_VD_GANG_1},
        {PMHAL_PRCM_VD_DSPEVE,  SBLUTILS_VD_GANG_1},
        {PMHAL_PRCM_VD_GPU,     SBLUTILS_VD_GANG_1}
    };
    sblUtilsVdInfo_t vdInfo_tda2ex_17x17[PMHAL_PRCM_VD_MAX] = {
        {PMHAL_PRCM_VD_MPU,     SBLUTILS_VD_GANG_1},
        {PMHAL_PRCM_VD_CORE,    SBLUTILS_VD_GANG_1},
        {PMHAL_PRCM_VD_IVAHD,   SBLUTILS_VD_GANG_2},
        {PMHAL_PRCM_VD_DSPEVE,  SBLUTILS_VD_GANG_2},
        {PMHAL_PRCM_VD_GPU,     SBLUTILS_VD_GANG_1}
    };
#endif

    /* Get the build time set OPP value using which set the OPP */
    oppId = (pmhalVmOppId_t) PMHAL_VM_OPP_NOM;

    /* Enable I2C1 for PMIC Communication */
    /*Force Wake-up clock domain l4per*/
    retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                                   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                   PM_TIMEOUT_INFINITE);

    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALI2CCommRegister(&gPmicI2cfunc);
    /*
     * Get the pmic ops and register with the pmic interface.
     */
#ifdef SOC_TDA2XX
    pmicOperations = PMHALTps659039GetPMICOps();
#elif defined (SOC_TDA2PX)
    pmicOperations = PMHALLP87565GetPMICOps();
#else
    if(PLATFORM_SILICON_PACKAGE_TYPE_17X17 == AppUtils_GetSiliconPackageType())
    {
        /* This is J6Eco 17X17 Evm. PMIC used is LP8733/32.
         * Register the regulator map as connected on J6Eco 17X17 Evm.
         */
        PMHALLP8733ConfigureRegulatorMap(gJ6Eco17x17LP8733RegulatorTable);
        pmicOperations = PMHALLP8733GetPMICOps();
    }
    else
    {
        /* This is J6 Eco Evm. PMIC used is Tps65917.
         * Use the default regulator map in present in PM.
         */
        pmicOperations = PMHALTps65917GetPMICOps();
    }
#endif
    retVal = (pmErrCode_t) PMHALPmicRegister(pmicOperations);

    /* Get the VD rail info based on the current board */
#if defined (SOC_TDA2EX)
    if(PLATFORM_SILICON_PACKAGE_TYPE_17X17 != AppUtils_GetSiliconPackageType())
    {
        vdInfoObj  = &vdInfo_tda2ex[0];
        vdInfoSize = sizeof(vdInfo_tda2ex)/sizeof(sblUtilsVdInfo_t);
    }
    else
    {
        vdInfoObj  = &vdInfo_tda2ex_17x17[0];
        vdInfoSize = sizeof(vdInfo_tda2ex_17x17)/sizeof(sblUtilsVdInfo_t);
    }
#else
    vdInfoObj  = &vdInfo_tda2xx[0];
    vdInfoSize = sizeof(vdInfo_tda2xx)/sizeof(sblUtilsVdInfo_t);
#endif
    /* Configure Non Ganged rails */
    for (index=0; index<vdInfoSize; index++)
    {
        if (vdInfoObj[index].gangId == SBLUTILS_VD_NOT_GANGED)
        {
            #if defined (SOC_TDA2PX)
            if ((vdInfoObj[index].vdId == PMHAL_PRCM_VD_MPU) || 
               (vdInfoObj[index].vdId == PMHAL_PRCM_VD_GPU))
            {
                pmicOperations = PMHALLP87565GetPMICOps();
            }
            else
            {
                pmicOperations = PMHALTps65917GetPMICOps();
            }
            retVal = (pmErrCode_t) PMHALPmicRegister(pmicOperations);
            #endif
            if (vdInfoObj[index].vdId == PMHAL_PRCM_VD_CORE)
            {
                /* VD_CORE can only support OPP_NOM */
                retVal |= PMHALVMSetOpp(PMHAL_PRCM_VD_CORE,
                                        PMHAL_VM_OPP_NOM,
                                        PM_TIMEOUT_INFINITE);
            }
            else
            {
                PMHALVMSetOpp(vdInfoObj[index].vdId, oppId, PM_TIMEOUT_INFINITE);
                numVdConfigured++;
            }
        }
    }

    /* Configure Ganged rails */
    for (gangNum = SBLUTILS_VD_GANG_1;
         ((gangNum <= SBLUTILS_VD_GANG_MAX) && (numVdConfigured <= vdInfoSize));
         gangNum++)
    {
        numGangedRails = 0;
        for (index=0; index<vdInfoSize; index++)
        {
            if (vdInfoObj[index].gangId == gangNum)
            {
                gangedVdRails[numGangedRails] = vdInfoObj[index].vdId;
                numGangedRails++;
                numVdConfigured++;
            }
        }
        if(numGangedRails != 0U)
        {
            SblUtilsConfigGangedVdRails(&gangedVdRails[0],
                                             numGangedRails,
                                             oppId);
        }
    }

    gRootClkFreqList = PMLIBBoardConfigGetRootClks();
    gVdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    retVal           = PMLIBClkRateInit(gRootClkFreqList, gVdRailShareList);
    return (int32_t) retVal;
}
#endif
#if defined(SOC_TDA3XX)
int32_t INIT(void)
{
    pmErrCode_t    retVal = PM_SUCCESS;
    pmhalVmOppId_t oppId;
    uint32_t       siliconPackageType;

    /* Get the build time set OPP value using which set the OPP */
    oppId = (pmhalVmOppId_t) PMHAL_VM_OPP_NOM;

    /* Enable I2C1 for PMIC Communication */
    /*Force Wake-up clock domain l4per*/
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER1,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALI2CCommRegister(&gPmicI2cfunc);

    siliconPackageType = AppUtils_GetSiliconPackageType();
    /*
     * Get the pmic ops and register with the pmic interface.
     */
    if (PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType)
    {
        pmicOperations = PMHALTps65917GetPMICOps();
        retVal = PMHALPmicRegister(pmicOperations);
        if (PM_SUCCESS != retVal)
        {
            gTestStatus = PM_SUCCESS;
            pmicOperations = PMHALLP8733GetPMICOps();
            retVal  = PMHALPmicRegister(pmicOperations);
        }
    }
    else
    {
        /* NOTE : Additionally need to program PRCM for I2C2 if configuring more
         * voltage rails than CORE and DSPEVE.
         */
        pmicOperations = PMHALLP8731GetPMICOps();
        retVal = PMHALPmicRegister(pmicOperations);
    }
    if (PM_SUCCESS != retVal)
    {
        AppUtils_printf("\r\nConfigure PMIC failed");
    }

    /* VD_CORE can only support OPP_NOM */
    retVal =
        (pmErrCode_t) ((int32_t) retVal |
                       (int32_t) PMHALVMSetOpp(PMHAL_PRCM_VD_CORE,
                                               oppId,
                                               PM_TIMEOUT_INFINITE));
    /*
     * Set the voltage for PMHAL_PRCM_VD_DSPEVE.
     */
    retVal =
        (pmErrCode_t) ((int32_t) retVal |
                       (int32_t) PMHALVMSetOpp(PMHAL_PRCM_VD_DSPEVE,
                                               oppId,
                                               PM_TIMEOUT_INFINITE));
    gRootClkFreqList = PMLIBBoardConfigGetRootClks();
    gVdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    retVal           = PMLIBClkRateInit(gRootClkFreqList, gVdRailShareList);

    return (int32_t) retVal;
}
#endif

int main(void)
{
    AppUtils_defaultInit();

    AppUtils_printf("\r\nPM ClockRate Test Application");
    INIT();
    /* Functions to Test clkrate manager */
    ClkRateLibCpuTest();
    ClkRateLibCpuBypassFreqTest();
    ClkRateLibModuleSetTest();

    if (gTestStatus == PM_SUCCESS)
    {
        AppUtils_printf("\r\nPM ClockRate Test Pass");
    }
    else
    {
        AppUtils_printf("\r\nPM ClockRate Test Fail");
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t PmTestUtilsI2cInit(void)
{
    int32_t  status = PM_SUCCESS;
    uint32_t timeout;
    uint32_t baseAddr = SOC_I2C1_BASE;

    /* Force Wake-up clock domain L4PER1 */
#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_NOWAIT);
#endif
#if defined(SOC_TDA3XX)
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER1,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_NOWAIT);
#endif

    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
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
        status      = PM_FAIL;
        gTestStatus = PM_FAIL;
    }

    if (status == PM_SUCCESS)
    {
        /* Disable I2C so we can configure for the PMIC communication. */
        I2CMasterEnable(baseAddr);

        /* Configure the I2C BUS clock frequency (I2C_SCL). */
        I2CMasterInitExpClk(baseAddr,
                            PM_TEST_UTILS_I2C_SYSTEM_CLOCK,
                            PM_TEST_UTILS_I2C_INTERNAL_CLOCK,
                            PM_TEST_UTILS_I2C_OUTPUT_CLOCK);

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

static int32_t PmTestUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                      const uint8_t *regAddr,
                                      uint8_t *regValue,
                                      uint32_t numRegs)
{
    int32_t status = PM_SUCCESS;
    status = PmTestUtilsI2cWrite(i2cNum, i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == PM_SUCCESS)
    {
        status = PmTestUtilsI2cRead(i2cNum, i2cDevAddr, regValue);
    }
    else
    {
        *regValue   = 0U;
        gTestStatus = PM_FAIL;
    }
    return status;
}

static int32_t PmTestUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                       const uint8_t *regAddr,
                                       const uint8_t *regValue,
                                       uint32_t numRegs)
{
    uint8_t  data[2];
    uint8_t  count       = (uint8_t) 2U;
    int32_t  status      = PM_SUCCESS;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    data[0] = *regAddr;
    data[1] = *regValue;
    status  = PmTestUtilsI2cWrite(i2cNum, i2cDevAddr, data, count);

    if (status == PM_SUCCESS)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = PmTestUtilsI2cWaitForFlags(i2cNum,
                                            I2C_INT_BUS_FREE |
                                            I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t PmTestUtilsI2cRead(uint32_t i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t *value)
{
    int32_t  status      = PM_SUCCESS;
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
    status = PmTestUtilsI2cCheckXfrStatus(i2cNum,
                                          (uint32_t) PM_TEST_UTILS_I2C_READ);
    if (status == PM_SUCCESS)
    {
        *value = I2CMasterDataGet(baseAddress);
    }
    else
    {
        *value      = 0U;
        gTestStatus = PM_FAIL;
    }

    /* Wait for I2C access ready before returning. */
    if (status == PM_SUCCESS)
    {
        uint32_t flags = I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_FREE;
        status = PmTestUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t PmTestUtilsI2cWrite(uint32_t i2cNum,
                                   uint8_t slaveAddr, const uint8_t data[],
                                   uint8_t count)
{
    int32_t  status = PM_SUCCESS;
    uint32_t rawSt;
    uint8_t  i;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    status = PmTestUtilsI2cWaitForBB(i2cNum);

    if (status == PM_SUCCESS)
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
        for (i = 0; ((i < count) && (status == PM_SUCCESS)); i++)
        {
            /*
             * Check the status to see if the data can be transferred and
             * send data.
             */
            status = PmTestUtilsI2cCheckXfrStatus(
                i2cNum,
                (uint32_t)
                PM_TEST_UTILS_I2C_WRITE);
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
        if (status == PM_SUCCESS)
        {
            status = PmTestUtilsI2cWaitForFlags(i2cNum,
                                                I2C_INT_ADRR_READY_ACESS);
            if (status == PM_SUCCESS)
            {
                rawSt = I2CMasterIntRawStatus(baseAddress);
                if ((rawSt & I2C_INT_NO_ACK) != 0)
                {
                    status      = PM_FAIL;
                    gTestStatus = PM_FAIL;
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

static int32_t PmTestUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
{
    int32_t  status = PM_SUCCESS;
    uint32_t rawSt;
    uint32_t flags = I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                     I2C_INT_ARBITRATION_LOST;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    if (xfr == PM_TEST_UTILS_I2C_WRITE)
    {
        flags |= I2C_INT_TRANSMIT_READY;
    }
    else if (xfr == PM_TEST_UTILS_I2C_READ)
    {
        flags |= I2C_INT_RECV_READY;
    }
    else
    {
        status      = PM_FAIL;
        gTestStatus = PM_FAIL;
    }

    /*
     * Wait for any of the following conditions to occur and
     * handle them in the loop before transmitting data.
     * NACK, AL, XRDY/RRDY, ARDY
     */
    if (status == PM_SUCCESS)
    {
        status = PmTestUtilsI2cWaitForFlags(i2cNum, flags);
    }

    if (status == PM_SUCCESS)
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
            status      = PM_FAIL;
            gTestStatus = PM_FAIL;
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
            status      = PM_FAIL;
            gTestStatus = PM_FAIL;
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
            status      = PM_FAIL;
            gTestStatus = PM_FAIL;
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
        else if (((xfr == PM_TEST_UTILS_I2C_WRITE) &&
                  ((rawSt & I2C_INT_TRANSMIT_READY) != 0)) ||
                 ((xfr == PM_TEST_UTILS_I2C_READ) &&
                  ((rawSt & I2C_INT_RECV_READY) != 0)))
        {
            /*
             * Return success so that the caller can send/receive the data
             * Note that the caller needs to clear the XRDY/RRDY flag as
             * needed.
             */
            status = PM_SUCCESS;
        }
        else
        {
            /*
             * We should not get here...
             */
            status      = PM_FAIL;
            gTestStatus = PM_FAIL;
        }
    }

    return status;
}

static int32_t PmTestUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
{
    int32_t  status = PM_SUCCESS;
    uint32_t timeout;
    uint32_t rawSt;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    timeout = PM_TEST_UTILS_I2C_TIMEOUT_COUNT;

    rawSt = I2CMasterIntRawStatus(baseAddress);

    while (((rawSt & flags) == 0) && (timeout > 0U))
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);
        timeout--;
    }

    if (timeout == 0U)
    {
        status      = PM_FAIL;
        gTestStatus = PM_FAIL;
    }

    return status;
}

static int32_t PmTestUtilsI2cWaitForBB(uint32_t i2cNum)
{
    int32_t  status = PM_SUCCESS;
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
    for (timeout = PM_TEST_UTILS_I2C_TIMEOUT_COUNT; timeout > 0U; --timeout)
    {
        if (I2CMasterBusBusy(baseAddress) == 0)
        {
            break;
        }
        I2CMasterIntClearEx(baseAddress, I2C_INT_BUS_BUSY);
    }

    if (timeout == 0U)
    {
        status      = PM_FAIL;
        gTestStatus = PM_FAIL;
    }

    /*
     * Clear all current interrupts.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    return status;
}

#if defined(SOC_TDA2EX)|| defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
static int32_t SblUtilsConfigGangedVdRails(const pmhalPrcmVdId_t *gangedVdRails,
                                           uint32_t           numGangedRails,
                                           uint32_t           oppId)
{
    int32_t         retVal = PM_SUCCESS;
    uint32_t        vdCount;
    uint32_t        currAvsVolt, maxAvsVolt = 0U;
    uint32_t        configOpp = oppId;
    pmhalPrcmVdId_t maxAvsVdId = PMHAL_PRCM_VD_UNDEF;

    /* Find the maximum AVS voltage on the ganged voltage lines and
     * then set the voltage to that value
     */
    for (vdCount=0; vdCount< numGangedRails; vdCount++)
    {
        if (PMHAL_PRCM_VD_CORE == gangedVdRails[vdCount])
        {
            /* VD_CORE can only support OPP_NOM. If one of the ganged voltage
             * rail is VD_CORE configure the voltage to OPP NOM. */
            configOpp = PMHAL_VM_OPP_NOM;
            break;
        }
    }

    for (vdCount=0; vdCount< numGangedRails; vdCount++)
    {
        currAvsVolt =
            PMHALVMGetAVS0EfuseVoltage(gangedVdRails[vdCount],
                                       (pmhalVmOppId_t) configOpp);

        if (currAvsVolt > maxAvsVolt)
        {
            maxAvsVolt = currAvsVolt;
            maxAvsVdId = gangedVdRails[vdCount];
        }
    }

    retVal += (int32_t)PMHALVMSetOpp(maxAvsVdId,
                            (pmhalVmOppId_t) configOpp, PM_TIMEOUT_INFINITE);

    /* Once the AVS and ABB is done for the voltage rail for which the AVS
     * EFUSE value is the highest. It is important to perform the ABB
     * configuration for the other voltage rails.
     */
    for (vdCount = 0U; vdCount < numGangedRails; vdCount++)
    {
        if (gangedVdRails[vdCount] != maxAvsVdId)
        {
            retVal += PMHALVMEnableABB(gangedVdRails[vdCount],
                                       (pmhalVmOppId_t) configOpp);
        }
        if (PM_SUCCESS != retVal)
        {
            break;
        }
    }

    return retVal;
}
#endif
