/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#include <ti/drv/pm/include/pmic/pmhal_tps659039.h>
#elif defined (SOC_TDA2PX)
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp87565.h>
#else
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#endif
#include <ti/drv/pm/pmlib.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/csl_i2c.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/include/pm_utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))
/**
 * \brief Macro to find the number of elements of the array.
 */

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define SBL_UTILS_I2C_SYSTEM_CLOCK       (96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define SBL_UTILS_I2C_INTERNAL_CLOCK     (9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define SBL_UTILS_I2C_OUTPUT_CLOCK       (400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define SBL_UTILS_I2C_TIMEOUT_COUNT      (4000U)

/** Write Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_WRITE              (1U)

/** Read Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_READ               (2U)

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

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t PmUtUtilsI2cInit(void);

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
static int32_t PmUtUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
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
static int32_t PmUtUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                     const uint8_t *regAddr,
                                     const uint8_t *regValue,
                                     uint32_t numRegs);
#ifdef __cplusplus
}
#endif
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmUtUtilsI2cWaitForBB(uint32_t i2cNum);

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
static int32_t PmUtUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

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
static int32_t PmUtUtilsI2cWrite(uint32_t i2cNum,
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
static int32_t PmUtUtilsI2cRead(uint32_t i2cNum,
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
static int32_t PmUtUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

static int32_t SblUtilsConfigGangedVdRails(const pmhalPrcmVdId_t *gangedVdRails,
                                           uint32_t           numGangedRails,
                                           uint32_t           oppId);
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

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalI2cCommOperations_t gPmicI2cfunc = {
    &PmUtUtilsI2cInit,
    &PmUtUtilsI2cReadByte,
    &PmUtUtilsI2cWriteByte,
    NULL,
    NULL
};

/**
 * \brief Holds the root clock frequencies specific for a given platform
 */
static uint32_t                      *gRootClkFreqList;

/**
 * \brief Holds the voltage domains information whose rails are shared
 */
static pmlibBoardVdRailShare_t       *gVdRailShareList;

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock] = used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *       ] = defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
static moduleClockList_t              cpuClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
#ifdef SOC_TDA2PX
        1000000000U,
#else
        750000000U
#endif
    },
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        600000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_HYD_GCLK,
        425600000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_HYD_GCLK,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_HYD_GCLK,
        532000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_CORE_GCLK,
        425600000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_CORE_GCLK,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_CORE_GCLK,
        532000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GENERIC,
        425600000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GENERIC,
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
        700000000U
    },
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
#ifdef SOC_TDA2PX
        1000000000U,
#else
        750000000U
#endif
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
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        535000000U
    },
#ifndef __ARM_ARCH_7A__
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1500000000U
    },
#endif
#endif
    {
        PMHAL_PRCM_MOD_IVA,
        PMHAL_PRCM_CLK_GENERIC,
        430000000U
    },
    {
        PMHAL_PRCM_MOD_IVA,
        PMHAL_PRCM_CLK_GENERIC,
        388333333U
    },
    {
        PMHAL_PRCM_MOD_IVA,
        PMHAL_PRCM_CLK_GENERIC,
        532000000U
    },
#ifndef __ARM_ARCH_7A__
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1176000000U
    },
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        750000000U
    },
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        500000000U
    },
#endif
    {
        PMHAL_PRCM_MOD_IPU1,
        PMHAL_PRCM_CLK_GENERIC,
        212800000U
    },
    {
        PMHAL_PRCM_MOD_IPU1,
        PMHAL_PRCM_CLK_GENERIC,
        212800U
    }
};

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock] = used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *       ] = defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
static moduleClockList_t              cpuBypClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_HYD_GCLK,
        425600000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_CORE_GCLK,
        425600000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GENERIC,
        425600000U
    },
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
    {
        PMHAL_PRCM_MOD_IVA,
        PMHAL_PRCM_CLK_GENERIC,
        430000000U
    },
#ifndef __ARM_ARCH_7A__
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1176000000U
    },
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1500000000U
    },
#endif
    {
        PMHAL_PRCM_MOD_IPU1,
        PMHAL_PRCM_CLK_GENERIC,
        212800000U
    },
};

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock] = used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *       ] = defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
#ifndef SOC_TDA2EX
static moduleClockList_t              moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_GFCLK,
     266000000},
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE4,           PMHAL_PRCM_CLK_ABE_GICLK,
     451584000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE1,           PMHAL_PRCM_CLK_CLKOUTMUX1_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE2,           PMHAL_PRCM_CLK_CLKOUTMUX2_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE3,           PMHAL_PRCM_CLK_L3INIT_60M_FCLK,
     60000000},
    {PMHAL_PRCM_MOD_IO_SRCOMP_CORE,
     PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK, 20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON,      PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON,      PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON,      PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,         PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_DSP1,                    PMHAL_PRCM_CLK_DSP1_GFCLK,
     600000000},
    {PMHAL_PRCM_MOD_DSP1,                    PMHAL_PRCM_CLK_DSP1_GFCLK,
     700000000},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_DSP1,                    PMHAL_PRCM_CLK_DSP1_GFCLK,
     750000000},
#endif
    {PMHAL_PRCM_MOD_DSP2,                    PMHAL_PRCM_CLK_DSP2_GFCLK,
     600000000},
    {PMHAL_PRCM_MOD_DSP2,                    PMHAL_PRCM_CLK_DSP2_GFCLK,
     700000000},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_DSP2,                    PMHAL_PRCM_CLK_DSP2_GFCLK,
     750000000},
#endif
    {PMHAL_PRCM_MOD_BB2D,                    PMHAL_PRCM_CLK_BB2D_GFCLK,
     354666666},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_CEC_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_PHY_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_DSS_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
     22579200},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
     22579200},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
     22579200},
    {PMHAL_PRCM_MOD_EVE1,                    PMHAL_PRCM_CLK_EVE1_GFCLK,
     535000000},
    {PMHAL_PRCM_MOD_EVE1,                    PMHAL_PRCM_CLK_EVE1_GFCLK,
     650000000},
    {PMHAL_PRCM_MOD_EVE2,                    PMHAL_PRCM_CLK_EVE2_GFCLK,
     535000000},
    {PMHAL_PRCM_MOD_EVE2,                    PMHAL_PRCM_CLK_EVE2_GFCLK,
     650000000},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_EVE3,                    PMHAL_PRCM_CLK_EVE3_GFCLK,
     535000000},
    {PMHAL_PRCM_MOD_EVE3,                    PMHAL_PRCM_CLK_EVE3_GFCLK,
     650000000},
    {PMHAL_PRCM_MOD_EVE4,                    PMHAL_PRCM_CLK_EVE4_GFCLK,
     535000000},
    {PMHAL_PRCM_MOD_EVE4,                    PMHAL_PRCM_CLK_EVE4_GFCLK,
     650000000},
#endif
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     266000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     451584000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMAC_MAIN_CLK,
     125000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMII_250MHZ_CLK,
     250000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_RMII_50MHZ_CLK,
     50000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_RGMII_5MHZ_CLK,
     5000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     425600000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     500000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     425600000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     500000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_I2C5,                    PMHAL_PRCM_CLK_IPU_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C5,                    PMHAL_PRCM_CLK_IPU_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     56448000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     20000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     10000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     24000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     22579200},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_UART6,                   PMHAL_PRCM_CLK_UART6_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART6,                   PMHAL_PRCM_CLK_UART6_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_IPU1,                    PMHAL_PRCM_CLK_IPU1_GFCLK,
     212800000},
    {PMHAL_PRCM_MOD_IPU2,                    PMHAL_PRCM_CLK_IPU2_GFCLK,
     212800000},
    {PMHAL_PRCM_MOD_IVA,                     PMHAL_PRCM_CLK_IVA_GCLK,
     388333333},
    {PMHAL_PRCM_MOD_IVA,                     PMHAL_PRCM_CLK_IVA_GCLK,
     430000000},
    {PMHAL_PRCM_MOD_IVA,                     PMHAL_PRCM_CLK_IVA_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_SL2,                     PMHAL_PRCM_CLK_IVA_GCLK,
     388333333},
    {PMHAL_PRCM_MOD_SL2,                     PMHAL_PRCM_CLK_IVA_GCLK,
     430000000},
    {PMHAL_PRCM_MOD_SL2,                     PMHAL_PRCM_CLK_IVA_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,          PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     128000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     32000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_L3INIT_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     128000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     32000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_L3INIT_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MLB_SS,                  PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK,
     266000000},
    {PMHAL_PRCM_MOD_SATA,                    PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SATA,                    PMHAL_PRCM_CLK_L3INIT_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_SATA,                    PMHAL_PRCM_CLK_SATA_REF_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_OCP2SCP1,                PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCP2SCP3,                PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
     960000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
     960000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS3,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS3,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS4,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS4,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_L3_MAIN_2,               PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_OCP_WP_NOC,              PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPMC,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMU_EDMA,                PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMU_EDMA,                PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MMU_PCIESS,              PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMU_PCIESS,              PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCMC_RAM1,               PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_OCMC_RAM1,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCMC_RAM2,               PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_OCMC_RAM2,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCMC_RAM3,               PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_OCMC_RAM3,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCMC_ROM,                PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SPARE_IVA2,              PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_VCP1,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_VCP2,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SPARE_CME,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_HDMI,              PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_ICM,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SATA2,             PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN4,          PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN5,          PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN6,          PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL1,         PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL2,         PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL3,         PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TPCC,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TPTC1,                   PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TPTC2,                   PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_CFG,                  PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_CFG,                  PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCP2SCP2,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SAR_ROM,                 PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SAR_ROM,                 PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC,   PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM, PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP,  PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPINLOCK,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SPINLOCK,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_IO_DELAY_BLOCK,          PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_IO_DELAY_BLOCK,          PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX1,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX1,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX10,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX10,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX11,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX11,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX12,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX12,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX13,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX13,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX2,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX2,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX3,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX3,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX4,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX4,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX5,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX5,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX6,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX6,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX7,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX7,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX8,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX8,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX9,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX9,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C1,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C1,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C1,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C2,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C2,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C2,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C3,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C3,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C3,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C4,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C4,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C4,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_L4_PER1,                 PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_PER1,                 PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_ELM,                     PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_ELM,                     PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMHAL_PRCM_CLK_PER_12M_GFCLK,
     12000000},
    {PMHAL_PRCM_MOD_MCSPI1,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI1,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI1,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCSPI2,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI2,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI2,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCSPI3,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI3,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI3,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCSPI4,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI4,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI4,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_UART2_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_UART2_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_UART3_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_UART3_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_UART4_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_UART4_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_UART5_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_UART5_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_GPIO2,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO2,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO2,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO3,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO3,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO3,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO4,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO4,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO4,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO5,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO5,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO5,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO6,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO6,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO6,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO7,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO7,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO7,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO8,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO8,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO8,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     24000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     12000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     24000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     12000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_DCAN2,                   PMHAL_PRCM_CLK_DCAN2_SYS_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DCAN2,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_PER2,                 PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART7,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART7,                   PMHAL_PRCM_CLK_UART7_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART7,                   PMHAL_PRCM_CLK_UART7_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART8,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART8,                   PMHAL_PRCM_CLK_UART8_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART8,                   PMHAL_PRCM_CLK_UART8_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART9,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART9,                   PMHAL_PRCM_CLK_UART9_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART9,                   PMHAL_PRCM_CLK_UART9_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_PRUSS1,                  PMHAL_PRCM_CLK_ICSS_CLK,
     200000000},
    {PMHAL_PRCM_MOD_PRUSS1,                  PMHAL_PRCM_CLK_ICSS_IEP_CLK,
     200000000},
    {PMHAL_PRCM_MOD_PRUSS1,                  PMHAL_PRCM_CLK_PER_192M_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_PRUSS2,                  PMHAL_PRCM_CLK_ICSS_CLK,
     200000000},
    {PMHAL_PRCM_MOD_PRUSS2,                  PMHAL_PRCM_CLK_ICSS_IEP_CLK,
     200000000},
    {PMHAL_PRCM_MOD_PRUSS2,                  PMHAL_PRCM_CLK_PER_192M_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     56448000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     20000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     10000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     24000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     22579200},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PWMSS1,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PWMSS2,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PWMSS3,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     128000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     32000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_L4_PER3,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_PER3,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_AES1,                    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_AES2,                    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DES3DES,                 PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DES3DES,                 PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_DMA_CRYPTO,              PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DMA_CRYPTO,              PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_FPKA,                    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_FPKA,                    PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_RNG,                     PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_RNG,                     PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SHA2MD51,                PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SHA2MD52,                PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
     34322580},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
     34322580},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_RTCSS,                   PMHAL_PRCM_CLK_RTC_AUX_CLK,
     32786},
    {PMHAL_PRCM_MOD_RTCSS,                   PMHAL_PRCM_CLK_RTC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_VIP1,                    PMHAL_PRCM_CLK_VIP1_GCLK,
     266000000},
    {PMHAL_PRCM_MOD_VIP2,                    PMHAL_PRCM_CLK_VIP2_GCLK,
     266000000},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_VIP3,                    PMHAL_PRCM_CLK_VIP3_GCLK,
     266000000},
#endif
    {PMHAL_PRCM_MOD_VPE,                     PMHAL_PRCM_CLK_VPE_GCLK,
     266000000},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_ADC,                     PMHAL_PRCM_CLK_ADC_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_ADC,                     PMHAL_PRCM_CLK_ADC_L3_GICLK,
     266000000},
#endif
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_FUNC_32K_CLK,
     32786},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     22579200},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_IO_SRCOMP_WKUP,
     PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK, 20000000},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER12,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER12,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_TIMER12,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_UART10_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_UART10_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     22579200},
};
#endif
#ifdef SOC_TDA2EX
static moduleClockList_t              moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_GFCLK,
     266000000},
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_ATL,                     PMHAL_PRCM_CLK_ATL_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE4,           PMHAL_PRCM_CLK_ABE_GICLK,
     451584000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE1,           PMHAL_PRCM_CLK_CLKOUTMUX1_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE2,           PMHAL_PRCM_CLK_CLKOUTMUX2_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DUMMY_MODULE3,           PMHAL_PRCM_CLK_L3INIT_60M_FCLK,
     60000000},
    {PMHAL_PRCM_MOD_IO_SRCOMP_CORE,
     PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK, 20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON,      PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON,      PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON,      PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,         PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_DSP1,                    PMHAL_PRCM_CLK_DSP1_GFCLK,
     600000000},
    {PMHAL_PRCM_MOD_DSP1,                    PMHAL_PRCM_CLK_DSP1_GFCLK,
     700000000},
    {PMHAL_PRCM_MOD_DSP1,                    PMHAL_PRCM_CLK_DSP1_GFCLK,
     750000000},
    {PMHAL_PRCM_MOD_BB2D,                    PMHAL_PRCM_CLK_BB2D_GFCLK,
     354666666},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_CEC_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_PHY_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_DSS_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
     22579200},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
     22579200},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DSS,                     PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
     22579200},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     266000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     451584000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMAC_MAIN_CLK,
     125000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_GMII_250MHZ_CLK,
     250000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_RMII_50MHZ_CLK,
     50000000},
    {PMHAL_PRCM_MOD_CPGMAC,                  PMHAL_PRCM_CLK_RGMII_5MHZ_CLK,
     5000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     425600000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     500000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     425600000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     500000000},
    {PMHAL_PRCM_MOD_GPU,                     PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_I2C5,                    PMHAL_PRCM_CLK_IPU_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C5,                    PMHAL_PRCM_CLK_IPU_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     56448000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     20000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     10000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     24000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     22579200},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP1,                  PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER5,                  PMHAL_PRCM_CLK_TIMER5_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER6,                  PMHAL_PRCM_CLK_TIMER6_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER7,                  PMHAL_PRCM_CLK_TIMER7_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER8,                  PMHAL_PRCM_CLK_TIMER8_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_UART6,                   PMHAL_PRCM_CLK_UART6_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART6,                   PMHAL_PRCM_CLK_UART6_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_IPU1,                    PMHAL_PRCM_CLK_IPU1_GFCLK,
     212800000},
    {PMHAL_PRCM_MOD_IPU2,                    PMHAL_PRCM_CLK_IPU2_GFCLK,
     212800000},
    {PMHAL_PRCM_MOD_IVA,                     PMHAL_PRCM_CLK_IVA_GCLK,
     388333333},
    {PMHAL_PRCM_MOD_IVA,                     PMHAL_PRCM_CLK_IVA_GCLK,
     430000000},
    {PMHAL_PRCM_MOD_IVA,                     PMHAL_PRCM_CLK_IVA_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_SL2,                     PMHAL_PRCM_CLK_IVA_GCLK,
     388333333},
    {PMHAL_PRCM_MOD_SL2,                     PMHAL_PRCM_CLK_IVA_GCLK,
     430000000},
    {PMHAL_PRCM_MOD_SL2,                     PMHAL_PRCM_CLK_IVA_GCLK,
     532000000},
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,          PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     128000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_MMC1_GFCLK,
     32000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC1,                    PMHAL_PRCM_CLK_L3INIT_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     128000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_MMC2_GFCLK,
     32000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC2,                    PMHAL_PRCM_CLK_L3INIT_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MLB_SS,                  PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK,
     266000000},
    {PMHAL_PRCM_MOD_OCP2SCP1,                PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCP2SCP3,                PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
     960000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
     960000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS3,             PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_USB_OTG_SS3,             PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     20000000},
    {PMHAL_PRCM_MOD_OCP_WP_NOC,              PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPMC,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L3_MAIN_1,               PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMU_EDMA,                PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMU_EDMA,                PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MMU_PCIESS,              PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMU_PCIESS,              PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCMC_RAM1,               PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_OCMC_RAM1,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCMC_ROM,                PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SPARE_IVA2,              PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_VCP1,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_VCP2,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SPARE_CME,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_HDMI,              PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_ICM,               PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SATA2,             PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN5,          PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN6,          PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL1,         PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL2,         PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL3,         PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TPCC,                    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TPTC1,                   PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TPTC2,                   PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_CFG,                  PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_CFG,                  PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_OCP2SCP2,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SAR_ROM,                 PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SAR_ROM,                 PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC,   PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM, PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP,  PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SPINLOCK,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SPINLOCK,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_IO_DELAY_BLOCK,          PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_IO_DELAY_BLOCK,          PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX1,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX1,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX10,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX10,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX11,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX11,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX12,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX12,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX13,               PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX13,               PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX2,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX2,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX3,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX3,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX4,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX4,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX5,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX5,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX6,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX6,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX7,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX7,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX8,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX8,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MAILBOX9,                PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MAILBOX9,                PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C1,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C1,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C1,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C2,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C2,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C2,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C3,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C3,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C3,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_I2C4,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C4,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C4,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_L4_PER1,                 PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_PER1,                 PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER10,                 PMHAL_PRCM_CLK_TIMER10_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER11,                 PMHAL_PRCM_CLK_TIMER11_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER2,                  PMHAL_PRCM_CLK_TIMER2_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER3,                  PMHAL_PRCM_CLK_TIMER3_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER4,                  PMHAL_PRCM_CLK_TIMER4_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER9,                  PMHAL_PRCM_CLK_TIMER9_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_ELM,                     PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_ELM,                     PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMHAL_PRCM_CLK_PER_12M_GFCLK,
     12000000},
    {PMHAL_PRCM_MOD_MCSPI1,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI1,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI1,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCSPI2,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI2,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI2,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCSPI3,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI3,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI3,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCSPI4,                  PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCSPI4,                  PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MCSPI4,                  PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_UART2_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART2,                   PMHAL_PRCM_CLK_UART2_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_UART3_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART3,                   PMHAL_PRCM_CLK_UART3_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_UART4_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART4,                   PMHAL_PRCM_CLK_UART4_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_UART5_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART5,                   PMHAL_PRCM_CLK_UART5_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_GPIO2,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO2,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO2,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO3,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO3,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO3,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO4,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO4,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO4,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO5,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO5,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO5,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO6,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO6,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO6,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO7,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO7,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO7,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO8,                   PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_GPIO8,                   PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_GPIO8,                   PMHAL_PRCM_CLK_GPIO_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     24000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_MMC3_GFCLK,
     12000000},
    {PMHAL_PRCM_MOD_MMC3,                    PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     24000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_MMC4_GFCLK,
     12000000},
    {PMHAL_PRCM_MOD_MMC4,                    PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_DCAN2,                   PMHAL_PRCM_CLK_DCAN2_SYS_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DCAN2,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_PER2,                 PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART7,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART7,                   PMHAL_PRCM_CLK_UART7_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART7,                   PMHAL_PRCM_CLK_UART7_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART8,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART8,                   PMHAL_PRCM_CLK_UART8_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART8,                   PMHAL_PRCM_CLK_UART8_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART9,                   PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_UART9,                   PMHAL_PRCM_CLK_UART9_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART9,                   PMHAL_PRCM_CLK_UART9_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     56448000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     20000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     10000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     24000000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     22579200},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP2,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP3,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP4,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP5,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP6,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP7,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     56448000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     20000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     10000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     24000000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     22579200},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     225792000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     112896000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     56448000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     28224000},
    {PMHAL_PRCM_MOD_MCASP8,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PWMSS1,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PWMSS2,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PWMSS3,                  PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     128000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     64000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     32000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_QSPI,                    PMHAL_PRCM_CLK_QSPI_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_L4_PER3,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_L4_PER3,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER13,                 PMHAL_PRCM_CLK_TIMER13_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER14,                 PMHAL_PRCM_CLK_TIMER14_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER15,                 PMHAL_PRCM_CLK_TIMER15_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER16,                 PMHAL_PRCM_CLK_TIMER16_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_AES1,                    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_AES2,                    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DES3DES,                 PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DES3DES,                 PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_DMA_CRYPTO,              PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_DMA_CRYPTO,              PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_FPKA,                    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_FPKA,                    PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_RNG,                     PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_RNG,                     PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_SHA2MD51,                PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_SHA2MD52,                PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
     34322580},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_PCIESS1,                 PMHAL_PRCM_CLK_PCIE_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
     34322580},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_SYS_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_32K_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_PCIESS2,                 PMHAL_PRCM_CLK_PCIE_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_RTCSS,                   PMHAL_PRCM_CLK_RTC_AUX_CLK,
     32786},
    {PMHAL_PRCM_MOD_RTCSS,                   PMHAL_PRCM_CLK_RTC_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_LVDSRX,                  PMHAL_PRCM_CLK_LVDSRX_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_LVDSRX,                  PMHAL_PRCM_CLK_LVDSRX_L4_GICLK,
     133000000},
    {PMHAL_PRCM_MOD_VIP1,                    PMHAL_PRCM_CLK_VIP1_GCLK,
     266000000},
    {PMHAL_PRCM_MOD_VPE,                     PMHAL_PRCM_CLK_VPE_GCLK,
     266000000},
    {PMHAL_PRCM_MOD_ADC,                     PMHAL_PRCM_CLK_ADC_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_ADC,                     PMHAL_PRCM_CLK_ADC_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_FUNC_32K_CLK,
     32786},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     20000000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     22579200},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_DCAN1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_GPIO1,                   PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_IO_SRCOMP_WKUP,
     PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK, 20000000},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_KBD,                     PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     10000000},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     22579200},
    {PMHAL_PRCM_MOD_TIMER1,                  PMHAL_PRCM_CLK_TIMER1_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER12,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_TIMER12,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_TIMER12,                 PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_UART10_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_UART10,                  PMHAL_PRCM_CLK_UART10_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     20000000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     56448000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_GICLK,
     28224000},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
    {PMHAL_PRCM_MOD_CAL,                     PMHAL_PRCM_CLK_CAL_GCLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C6,                    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     266000000},
    {PMHAL_PRCM_MOD_I2C6,                    PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_I2C6,                    PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     133000000}
};
#endif

const pmhalPmicOperations_t *pmicOperations;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void ClkRateLibCpuTest(void)
{
    pmErrCode_t status;
    uint32_t    sTimeCnt, eTimeCnt;
    uint32_t    idx;
    UARTPuts("\n----- PMLIB Clock Rate Set and Get Test ----------", -1);
    uint32_t    size = VSIZE_TYPE(cpuClockTestList, moduleClockList_t);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBClkRateGet(cpuClockTestList[idx].modId,
                                   cpuClockTestList[idx].clkId,
                                   &clkGetRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nGet Time = ,%d, ", eTimeCnt - sTimeCnt);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nGET: PASS: [%s].[%s] = %u Hz ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGET: FAIL: [%s].[%s] ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        if (PMHAL_PRCM_MOD_DSP1 == cpuClockTestList[idx].modId)
        {
            sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        }
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
        status = PMLIBClkRateSet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 cpuClockTestList[idx].clkRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nSet Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (status == PM_SUCCESS)
        {
            UARTprintf("\nSET: PASS [%s].[%s] ",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        else if (status == PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ)
        {
            UARTprintf("\nSET: PASS [%s].[%s] ",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        else if ((cpuClockTestList[idx].modId == PMHAL_PRCM_MOD_IPU1) &&
                 (status == PM_CLOCKRATE_FREQ_NOT_SUPPORTED))
        {
            UARTprintf(
                "\nSET: PASS Negative Test[%s].[%s] = %u Hz not set",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                cpuClockTestList[idx].clkRate);
        }
        else
        {
            UARTprintf("\nSET: FAIL [%s].[%s] Error Code = %d",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId],
                       status);
        }
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBClkRateGet(cpuClockTestList[idx].modId,
                                   cpuClockTestList[idx].clkId,
                                   &clkGetRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nGet Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nGET: AFTER SET: [%s].[%s] = %u Hz ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGET: AFTER SET: FAIL [%s].[%s] \n\n",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
    }
    UARTPuts("\nClkrate Manager CPU Set and Get Frequency test Completed!!", -1);
    UARTPuts("\n---------------------------------------------------------", -1);
}

static void ClkRateLibCpuBypassFreqTest(void)
{
    pmErrCode_t       status;

    uint32_t          idx;
    pmhalPrcmNodeId_t dpllId;
    UARTPuts("\nClkrate Manager Bypass Freq Test: ", -1);
    uint32_t          size = VSIZE_TYPE(cpuBypClockTestList, moduleClockList_t);
    for (dpllId = PMHAL_PRCM_DPLL_MIN; dpllId < PMHAL_PRCM_DPLL_COUNT;
         dpllId = (pmhalPrcmNodeId_t) ((uint32_t) dpllId + 1))
    {
        if (PMHAL_PRCM_DPLL_DSP == dpllId)
        {
            PMHALCMDpllSetBypassClkSelect(dpllId,
                                          PMHAL_PRCM_DPLL_BYP_CLKINPULOW);
            PMHALCMDpllUnLock(dpllId);
        }
    }
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        status = PMLIBClkRateGet(cpuBypClockTestList[idx].modId,
                                 cpuBypClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nGET: PASS: [%s].[%s] = %u Hz ",
                pmhalNodeList_names[cpuBypClockTestList[idx].modId],
                pmhalClockList_names[cpuBypClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGET: FAIL: [%s].[%s] ",
                pmhalNodeList_names[cpuBypClockTestList[idx].modId],
                pmhalClockList_names[cpuBypClockTestList[idx].clkId]);
        }
    }
    UARTPuts("\nClkrate Manager Bypass Freq Test Completed!!", -1);
    UARTPuts("\n---------------------------------------------------------", -1);
}

static void ClkRateLibAllModuleFreqGetTest(void)
{
    pmErrCode_t status;
    uint32_t    sTimeCnt, eTimeCnt;
    uint32_t    idx;

    UARTPuts("\nClkrate Manager All module Get Frequency test: ", -1);
    for (idx = PMHAL_PRCM_MOD_LOWER_BOUND + 1; idx < PMHAL_PRCM_MOD_COUNT;
         idx++)
    {
        uint32_t clkGetRate;
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBClkRateGet((pmhalPrcmModuleId_t) idx,
                                   PMHAL_PRCM_CLK_GENERIC,
                                   &clkGetRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nGet Time = ,%d, ", eTimeCnt - sTimeCnt);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\n %u GET: PASS: [%s].[%s] = %u Hz ",
                idx,
                pmhalNodeList_names[idx],
                "PMHAL_PRCM_CLK_GENERIC",
                clkGetRate);
        }
        else if (((pmhalPrcmModuleId_t) idx == PMHAL_PRCM_MOD_WD_TIMER1) ||
                 ((pmhalPrcmModuleId_t) idx == PMHAL_PRCM_MOD_TIMER12) ||
                 ((pmhalPrcmModuleId_t) idx == PMHAL_PRCM_MOD_SDVENC))
        {
            UARTprintf(
                "\n %u GET: ROOT CLK NOT SUPPORTED [%s].[%s] = %u Hz ",
                idx,
                pmhalNodeList_names[idx],
                "PMHAL_PRCM_CLK_GENERIC",
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\n%u GET: FAIL: [%s].[%s] ",
                idx,
                pmhalNodeList_names[idx],
                "PMHAL_PRCM_CLK_GENERIC");
        }
    }
    UARTPuts("\nClkrate Manager All module Get Frequency test Completed!!", -1);
    UARTPuts("\n---------------------------------------------------------", -1);
}

static void ClkRateLibModuleSetTest(void)
{
    pmErrCode_t status;
    uint32_t    sTimeCnt, eTimeCnt;
    uint32_t    idx;
    UARTPuts("\nClkrate Manager Module Set Frequency test: ", -1);
    uint32_t    size = VSIZE_TYPE(moduleClockTestList, moduleClockList_t);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBClkRateGet(moduleClockTestList[idx].modId,
                                   moduleClockTestList[idx].clkId,
                                   &clkGetRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nGet Time = ,%d, ", eTimeCnt - sTimeCnt);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nGET: PASS: [%s].[%s] = %u Hz ",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGET: FAIL: [%s].[%s] ",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId]);
        }
        #if defined (SOC_TDA2PX)
        if ((moduleClockTestList[idx].modId == PMHAL_PRCM_MOD_MPU) || 
           (moduleClockTestList[idx].modId == PMHAL_PRCM_MOD_GPU))
        {
            pmicOperations = PMHALLP87565GetPMICOps();
        }
        else
        {
            pmicOperations = PMHALTps65917GetPMICOps();
        }
        status = (pmErrCode_t) PMHALPmicRegister(pmicOperations);
        #endif
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBClkRateSet(moduleClockTestList[idx].modId,
                                   moduleClockTestList[idx].clkId,
                                   moduleClockTestList[idx].clkRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nSet Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nSET: PASS [%s].[%s] = %u Hz",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else if (status == PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ)
        {
            UARTprintf(
                "\nSET: PASS [%s].[%s] = %u Hz",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else if ((moduleClockTestList[idx].modId == PMHAL_PRCM_MOD_IPU1) &&
                 (status == PM_CLOCKRATE_FREQ_NOT_SUPPORTED))
        {
            UARTprintf(
                "\nSET: PASS Negative Test[%s].[%s] = %u Hz not set",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else
        {
            UARTprintf(
                "\nSET: FAIL [%s].[%s] = %u Hz: %d",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate,
                status);
        }
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBClkRateGet(moduleClockTestList[idx].modId,
                                   moduleClockTestList[idx].clkId,
                                   &clkGetRate);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("\nGet Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (status == PM_SUCCESS)
        {
            if (clkGetRate == moduleClockTestList[idx].clkRate)
            {
                UARTprintf(
                    "\nGET: AFTER SET: [%s].[%s] = %u Hz ",
                    pmhalNodeList_names[moduleClockTestList[idx].modId],
                    pmhalClockList_names[moduleClockTestList[idx].clkId],
                    clkGetRate);
            }
            else
            {
                UARTprintf(
                    "\nGET: AFTER SET: FAIL [%s].[%s] = %u Hz ",
                    pmhalNodeList_names[moduleClockTestList[idx].modId],
                    pmhalClockList_names[moduleClockTestList[idx].clkId],
                    clkGetRate);
            }
        }
        else
        {
            UARTprintf(
                "\nGET: AFTER SET: FAIL [%s].[%s] \n\n",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId]);
        }
    }
    UARTPuts("\nClkrate Manager module Set Frequency test Completed!!", -1);
    UARTPuts("\n---------------------------------------------------------", -1);
}

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


int32_t INIT(void)
{
    int32_t         retVal = (int32_t) PM_SUCCESS;
    pmhalVmOppId_t  oppId;
    const pmhalPmicOperations_t *pmicOps;
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
#if defined (SOC_TDA2XX)
    /* This is TDA2xx Evm. PMIC used is Tps659039.
     * Use the default regulator map in present in PM.
     */
    pmicOps = PMHALTps659039GetPMICOps();
#elif defined (SOC_TDA2PX)
    /* On the TDA2PX EVM 2 PMICS are used. The registration is repeated for
     * different voltage rails later.
     */
    pmicOps = PMHALLP87565GetPMICOps();
#else
    if(PLATFORM_SILICON_PACKAGE_TYPE_17X17 == PlatformGetSiliconPackageType())
    {
        /* This is J6Eco 17X17 Evm. PMIC used is LP8733/32.
         * Register the regulator map as connected on J6Eco 17X17 Evm.
         */
        PMHALLP8733ConfigureRegulatorMap(gJ6Eco17x17LP8733RegulatorTable);
        pmicOps = PMHALLP8733GetPMICOps();
    }
    else
    {
        /* This is J6 Eco Evm. PMIC used is Tps65917.
         * Use the default regulator map in present in PM.
         */
        pmicOps = PMHALTps65917GetPMICOps();
    }
#endif
    retVal = (pmErrCode_t) PMHALPmicRegister(pmicOps);

    /* Get the VD rail info based on the current board */
#if defined (SOC_TDA2EX)
    if(PLATFORM_SILICON_PACKAGE_TYPE_17X17 != PlatformGetSiliconPackageType())
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
    retVal          = PMLIBClkRateInit(gRootClkFreqList, gVdRailShareList);
    return (int32_t) retVal;
}

int main(void)
{
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER4, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, (uint32_t) TIMER_FREE);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE,
                       (uint32_t) TIMER_AUTORLD_NOCMP_ENABLE);
    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);
    UART_PAD_CONFIG();
    UARTStdioInit();
    UARTPuts("\nPM ClockRate Test App", -1);
    INIT();
    /* Function to Test CPU Idle */
    ClkRateLibCpuTest();
    ClkRateLibCpuBypassFreqTest();
    ClkRateLibAllModuleFreqGetTest();
    ClkRateLibModuleSetTest();
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t PmUtUtilsI2cInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddr = SOC_I2C1_BASE;

    /* Enable I2C1 for PMIC Communication */
    /*Force Wake-up clock domain l4per*/
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

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

static int32_t PmUtUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    uint8_t *regValue,
                                    uint32_t numRegs)
{
    int32_t status = STW_SOK;
    status = PmUtUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == STW_SOK)
    {
        status = PmUtUtilsI2cRead(i2cNum, (uint8_t) i2cDevAddr, regValue);
    }
    else
    {
        *regValue = 0U;
    }
    return status;
}

static int32_t PmUtUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
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
    status  = PmUtUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, data, count);

    if (status == STW_SOK)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = PmUtUtilsI2cWaitForFlags(i2cNum,
                                          I2C_INT_BUS_FREE |
                                          I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t PmUtUtilsI2cRead(uint32_t i2cNum,
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
    status = PmUtUtilsI2cCheckXfrStatus(i2cNum,
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
        status = PmUtUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t PmUtUtilsI2cWrite(uint32_t i2cNum,
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
    status = PmUtUtilsI2cWaitForBB(i2cNum);

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
            status = PmUtUtilsI2cCheckXfrStatus(
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
            status = PmUtUtilsI2cWaitForFlags(i2cNum, I2C_INT_ADRR_READY_ACESS);
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

static int32_t PmUtUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
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
        status = PmUtUtilsI2cWaitForFlags(i2cNum, flags);
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

static int32_t PmUtUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
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

static int32_t PmUtUtilsI2cWaitForBB(uint32_t i2cNum)
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

