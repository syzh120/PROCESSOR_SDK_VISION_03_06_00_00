/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     sbl_utils_tda2xx.c
 *
 *  \brief    This file contains the SBL Utility layer valid for TDA2xx SOC
 *            family.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#if defined (SOC_TDA2XX)
#include <ti/drv/pm/include/pmic/pmhal_tps659039.h>
#elif defined (SOC_TDA2PX)
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp87565.h>
#else
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#endif
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/csl_wd_timer.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda2xx.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <sbl_utils_priv.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_API.h>
#include <ti/csl/arch/csl_arch.h>

#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
#include <ti/drv/pm/include/pmic/pmhal_tps659039.h>
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SBL_UTILS_NUM_ENTRIES_POWER_DOMAIN_STATE_TABLE \
    (sizeof (gPowerDomainStateTable) / sizeof (gPowerDomainStateTable[0]))

#define SBL_UTILS_NUM_ENTRIES_CLOCK_DOMAIN_STATE_TABLE \
    (sizeof (gClockDomainStateTable) / sizeof (gClockDomainStateTable[0]))

#define SBL_UTILS_NUM_ENTRIES_MODULE_ENABLE_TABLE \
    (sizeof (gModuleEnableTable) / sizeof (gModuleEnableTable[0]))

/* MPU System interrupt number used for WDT */
#define WD_TIMER_DELAY_INT    (uint16_t) (80U)

/* WDT overflow value for 3 mins at 36KHz functional clock */
#define SBL_WD_TIMER_OVF_VALUE  (0xFFA81BFFU)

/* WDT delay event value for 2 mins */
#define SBL_WD_TIMER_DLY_VALUE   (0xFFA81BFFU + 0x3A9800U)

/* Device Package read Shift */
#define SBL_UTILS_TDA2XX_PACKAGE_BIT_SHIFT (16U)

/* Device Package read Mask */
#define SBL_UTILS_TDA2XX_PACKAGE_BIT_MASK  (0x30000U)

/* Package Type 1: Corresponds to 17x17 package */
#define SBL_UTILS_TDA2XX_PACKAGE_TYPE_0 (1U)

/* Package Type 2: Corresponds to 23x23 package */
#define SBL_UTILS_TDA2XX_PACKAGE_TYPE_1 (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the gang to which a voltage rail is connected.
 *
 */
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

/**
 * \brief  Structure to define the voltage rail and the corresponding gang
 *         Number to which it is connected.
 *
 */
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

/**
 * \brief   This function is used to provide delay while doing MMCSD LDO power
 *          configuration.
 *
 * \param   delay    Delay needed in micro-seconds.
 *
 * \retval  None.
 */
static inline void SblDelay(uint32_t delay);

/**
 * \brief   This function performs MMCSD LDO power configuration.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblUtilsMMCSDLdoPowerOn(void);

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

/**
 * \brief   This function copies data from NOR memory using EDMA.
 *
 * \param   dstAddr             Destination Address
 * \param   srcOffsetAddr       NOR Source Offset Address
 * \param   length              The length of data block to be copied.
 * \param   edmaChNum           EDMA channel number used for transfer.
 *
 * \return  None
 */
static void SblUtilsNorReadEdma(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length,
                                uint32_t edmaChNum);
/**
 * \brief   This function configures the voltage for the ganged rails.
 *
 * \param   gangedVdRails       pointer to the array of ganged voltage rail ids.
 * \param   numGangedRails      Number of ganged voltage rails.
 * \param   oppId               opp to be configured.
 *
 * \return  None
 */
static int32_t SblUtilsConfigGangedVdRails(const pmhalPrcmVdId_t *gangedVdRails,
                                           uint32_t           numGangedRails,
                                           uint32_t           oppId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global variable for referencing the App Image File Pointer */
FIL      gAppImageSDFilePtr;

/* Buffer for initializing DSP L2 RAM */
__attribute__((aligned(1024)))
uint32_t gDspL2RamInitData[1024U] = {0U};

/* Variable to store the size of pad config object. */
uint32_t gPadDelayConfigSize;
/* Variable to store the pointer to pad config object. */
sblutilsPadDelayConfig_t *gPadDelayConfigObj;
/* Variable to store the pointer to calculated delay config value object. */
sblutilsDelayConfigRegValue_t *gPadDelayConfigRegValueObj;

/*
 * Table containing Power Domain enable Configuration which should be configured
 * for different Power Domains
 */
static const sblutilsPowerDomainStateConfig_t gPowerDomainStateTable[] = {
#if defined (SOC_TDA2PX)
    {PMHAL_PRCM_PD_ISS,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "ISS"      },
#endif
    {PMHAL_PRCM_PD_CAM,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CAM"      },
    {PMHAL_PRCM_PD_CORE,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CORE"     },
    {PMHAL_PRCM_PD_CUSTEFUSE, PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CUSTEFUSE"},
    {PMHAL_PRCM_PD_DSP1,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSP1"     },
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    {PMHAL_PRCM_PD_DSP2,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSP2"     },
#endif
    {PMHAL_PRCM_PD_DSS,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSS"      },
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    {PMHAL_PRCM_PD_EVE1,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE1"     },
    {PMHAL_PRCM_PD_EVE2,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE2"     },
#endif
#if defined (SOC_TDA2XX)
    {PMHAL_PRCM_PD_EVE3,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE3"     },
    {PMHAL_PRCM_PD_EVE4,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE4"     },
#endif
    {PMHAL_PRCM_PD_GPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "GPU"      },
    {PMHAL_PRCM_PD_IPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "IPU"      },
    {PMHAL_PRCM_PD_IVA,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "IVA"      },
    {PMHAL_PRCM_PD_L3INIT,    PMHAL_PRCM_PD_STATE_ON_ACTIVE, "L3INIT"   },
    {PMHAL_PRCM_PD_L4PER,     PMHAL_PRCM_PD_STATE_ON_ACTIVE, "L4PER"    },
    {PMHAL_PRCM_PD_MPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "MPU"      },
    {PMHAL_PRCM_PD_VPE,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "VPE"      }
};

/*
 * Table containing Clock Domain State Configuration which should be
 * configured for different clock domains
 */
static const sblutilsClockDomainStateConfig_t gClockDomainStateTable[] = {
    {PMHAL_PRCM_CD_L4CFG,   PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP,
     "L4CFG"},
    {PMHAL_PRCM_CD_L3MAIN1, PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
     "L3MAIN1"},
    {PMHAL_PRCM_CD_EMIF,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EMIF"},
    {PMHAL_PRCM_CD_IPU,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "IPU"},
    {PMHAL_PRCM_CD_CAM,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "CAM"},
    {PMHAL_PRCM_CD_DSS,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DSS"},
    {PMHAL_PRCM_CD_L3INIT,  PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L3INIT"},
    {PMHAL_PRCM_CD_GMAC,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "GMAC"},
#if defined (SOC_TDA2EX)
    {PMHAL_PRCM_CD_L4PER,   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L4PER"},
#endif
    {PMHAL_PRCM_CD_L4PER2,  PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L4PER2"},
    {PMHAL_PRCM_CD_L4PER3,  PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L4PER3"},
    {PMHAL_PRCM_CD_WKUPAON, PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "WKUPAON"},
    {PMHAL_PRCM_CD_DMA,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DMA"},
    {PMHAL_PRCM_CD_IVA,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "IVA"},
    {PMHAL_PRCM_CD_MPU,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "MPU"},
    {PMHAL_PRCM_CD_VPE,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "VPE"},
    {PMHAL_PRCM_CD_PCIE,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "PCIE"},
    {PMHAL_PRCM_CD_EMU,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EMU"},
    {PMHAL_PRCM_CD_DSP1,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DSP1"},
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    {PMHAL_PRCM_CD_DSP2,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DSP2"},
    {PMHAL_PRCM_CD_EVE1,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EVE1"},
    {PMHAL_PRCM_CD_EVE2,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EVE2"},
#endif
#if defined (SOC_TDA2XX)
    {PMHAL_PRCM_CD_EVE3,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EVE3"},
    {PMHAL_PRCM_CD_EVE4,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EVE4"},
#endif
#if defined (SOC_TDA2PX)
    {PMHAL_PRCM_CD_ISS,     PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "ISS"},
#endif
};

/*
 * Table containing Module enable Configuration which should be configured
 * for different modules
 * I2C1 is already enabled during AVS voltage configuration in function
 * SBLUtilsConfigAllVoltageRails.
 */
static const sblutilsModuleEnableConfig_t     gModuleEnableTable[] =
{
    {PMHAL_PRCM_MOD_VIP1,        PMHAL_PRCM_MODULE_MODE_AUTO,    "VIP1"},
    {PMHAL_PRCM_MOD_DSS,         PMHAL_PRCM_MODULE_MODE_ENABLED, "DSS" },
    {PMHAL_PRCM_MOD_VPE,         PMHAL_PRCM_MODULE_MODE_AUTO,    "VPE" },
    {PMHAL_PRCM_MOD_OCMC_RAM1,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "OCMC RAM1"},
#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    {PMHAL_PRCM_MOD_CAL,         PMHAL_PRCM_MODULE_MODE_AUTO,    "CAL" },
#endif
#if defined (SOC_TDA2EX)
    {PMHAL_PRCM_MOD_I2C1,        PMHAL_PRCM_MODULE_MODE_ENABLED, "I2C1"},
#endif
    {PMHAL_PRCM_MOD_I2C2,        PMHAL_PRCM_MODULE_MODE_ENABLED, "I2C2"},
    {PMHAL_PRCM_MOD_I2C3,        PMHAL_PRCM_MODULE_MODE_ENABLED, "I2C3"},
    {PMHAL_PRCM_MOD_I2C4,        PMHAL_PRCM_MODULE_MODE_ENABLED, "I2C4"},
#if defined (SOC_TDA2PX) || defined (SOC_DRA72x)
    {PMHAL_PRCM_MOD_I2C5,        PMHAL_PRCM_MODULE_MODE_ENABLED, "I2C5"},
#endif
    {PMHAL_PRCM_MOD_MCASP1,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "MCASP1"},
    {PMHAL_PRCM_MOD_MCSPI1,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "MCSPI1"},
    {PMHAL_PRCM_MOD_QSPI,        PMHAL_PRCM_MODULE_MODE_ENABLED, "QSPI"},
    {PMHAL_PRCM_MOD_TPCC,        PMHAL_PRCM_MODULE_MODE_AUTO,    "TPCC"},
    {PMHAL_PRCM_MOD_TPTC1,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "TPTC1"},
    {PMHAL_PRCM_MOD_TPTC2,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "TPTC2"},
    {PMHAL_PRCM_MOD_DMM,         PMHAL_PRCM_MODULE_MODE_AUTO,    "DMM" },
    {PMHAL_PRCM_MOD_EMIF1,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "EMIF1"},
    {PMHAL_PRCM_MOD_EMIF_OCP_FW, PMHAL_PRCM_MODULE_MODE_AUTO,
     "EMIF OCP FW"},
    {PMHAL_PRCM_MOD_GPMC,        PMHAL_PRCM_MODULE_MODE_AUTO,    "GPMC"},
    {PMHAL_PRCM_MOD_MMU_EDMA,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MMU_EDMA"},
    {PMHAL_PRCM_MOD_MMU_PCIESS,  PMHAL_PRCM_MODULE_MODE_AUTO,
     "MMU PCIESS"},
    {PMHAL_PRCM_MOD_L3_MAIN_1,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "L3MAIN1"},
    {PMHAL_PRCM_MOD_L3_MAIN_2,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "L3MAIN2"},
    {PMHAL_PRCM_MOD_L4_CFG,      PMHAL_PRCM_MODULE_MODE_AUTO,
     "L4CFG"},
    {PMHAL_PRCM_MOD_L4_PER1,     PMHAL_PRCM_MODULE_MODE_AUTO,
     "L4PER1"},
    {PMHAL_PRCM_MOD_L4_PER2,     PMHAL_PRCM_MODULE_MODE_AUTO,
     "L4PER2"},
    {PMHAL_PRCM_MOD_L4_PER3,     PMHAL_PRCM_MODULE_MODE_AUTO,
     "L4PER3"},
    {PMHAL_PRCM_MOD_MAILBOX1,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX1"},
    {PMHAL_PRCM_MOD_MAILBOX2,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX2"},
    {PMHAL_PRCM_MOD_MAILBOX3,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX3"},
    {PMHAL_PRCM_MOD_MAILBOX4,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX4"},
    {PMHAL_PRCM_MOD_MAILBOX5,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX5"},
    {PMHAL_PRCM_MOD_MAILBOX6,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX6"},
    {PMHAL_PRCM_MOD_MAILBOX7,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX7"},
    {PMHAL_PRCM_MOD_MAILBOX8,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX8"},
    {PMHAL_PRCM_MOD_MAILBOX9,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX9"},
    {PMHAL_PRCM_MOD_MAILBOX10,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX10"},
    {PMHAL_PRCM_MOD_MAILBOX11,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX11"},
    {PMHAL_PRCM_MOD_MAILBOX12,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX12"},
    {PMHAL_PRCM_MOD_MAILBOX13,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "MAILBOX13"},
    {PMHAL_PRCM_MOD_SPINLOCK,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "SPINLOCK"},
    {PMHAL_PRCM_MOD_TIMER1,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER1"},
    {PMHAL_PRCM_MOD_TIMER2,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER2"},
    {PMHAL_PRCM_MOD_TIMER3,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER3"},
    {PMHAL_PRCM_MOD_TIMER4,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER4"},
    {PMHAL_PRCM_MOD_TIMER5,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER5"},
    {PMHAL_PRCM_MOD_TIMER6,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER6"},
    {PMHAL_PRCM_MOD_TIMER7,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER7"},
    {PMHAL_PRCM_MOD_TIMER8,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER8"},
    {PMHAL_PRCM_MOD_TIMER9,      PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER9"},
    {PMHAL_PRCM_MOD_TIMER10,     PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER10"},
    {PMHAL_PRCM_MOD_TIMER11,     PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER11"},
    {PMHAL_PRCM_MOD_TIMER12,     PMHAL_PRCM_MODULE_MODE_AUTO,
     "TIMER12"},
    {PMHAL_PRCM_MOD_TIMER13,     PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER13"},
    {PMHAL_PRCM_MOD_TIMER14,     PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER14"},
    {PMHAL_PRCM_MOD_TIMER15,     PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER15"},
    {PMHAL_PRCM_MOD_TIMER16,     PMHAL_PRCM_MODULE_MODE_ENABLED,
     "TIMER16"},
    {PMHAL_PRCM_MOD_WD_TIMER2,   PMHAL_PRCM_MODULE_MODE_ENABLED,
     "WDTIMER2"},
    {PMHAL_PRCM_MOD_GPIO1,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO1"},
    {PMHAL_PRCM_MOD_GPIO2,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO2"},
    {PMHAL_PRCM_MOD_GPIO3,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO3"},
    {PMHAL_PRCM_MOD_GPIO4,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO4"},
    {PMHAL_PRCM_MOD_GPIO5,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO5"},
    {PMHAL_PRCM_MOD_GPIO6,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO6"},
    {PMHAL_PRCM_MOD_GPIO7,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO7"},
    {PMHAL_PRCM_MOD_GPIO8,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "GPIO8"},
    {PMHAL_PRCM_MOD_MMC1,        PMHAL_PRCM_MODULE_MODE_ENABLED, "MMC1"},
    {PMHAL_PRCM_MOD_CPGMAC,      PMHAL_PRCM_MODULE_MODE_ENABLED, "GMAC"},
    {PMHAL_PRCM_MOD_DSP1,        PMHAL_PRCM_MODULE_MODE_AUTO,    "DSP1"},
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    {PMHAL_PRCM_MOD_EMIF2,       PMHAL_PRCM_MODULE_MODE_AUTO,
     "EMIF2"},
    {PMHAL_PRCM_MOD_VIP2,        PMHAL_PRCM_MODULE_MODE_AUTO,    "VIP2"},
#endif
#if defined (SOC_TDA2XX)
    {PMHAL_PRCM_MOD_VIP3,        PMHAL_PRCM_MODULE_MODE_AUTO,    "VIP3"},
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    {PMHAL_PRCM_MOD_OCMC_RAM2,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "OCMC RAM2"},
    {PMHAL_PRCM_MOD_OCMC_RAM3,   PMHAL_PRCM_MODULE_MODE_AUTO,
     "OCMC RAM3"},
    {PMHAL_PRCM_MOD_OCMC_ROM,    PMHAL_PRCM_MODULE_MODE_AUTO,
     "OCMC ROM"},
    {PMHAL_PRCM_MOD_DSP2,        PMHAL_PRCM_MODULE_MODE_AUTO,    "DSP2"},
    {PMHAL_PRCM_MOD_EVE1,        PMHAL_PRCM_MODULE_MODE_AUTO,    "EVE1"},
    {PMHAL_PRCM_MOD_EVE2,        PMHAL_PRCM_MODULE_MODE_AUTO,    "EVE2"},
#endif
#if defined (SOC_TDA2XX)
    {PMHAL_PRCM_MOD_EVE3,        PMHAL_PRCM_MODULE_MODE_AUTO,    "EVE3"},
    {PMHAL_PRCM_MOD_EVE4,        PMHAL_PRCM_MODULE_MODE_AUTO,    "EVE4"},
#endif
#if defined (SOC_TDA2PX)
    {PMHAL_PRCM_MOD_ISS,         PMHAL_PRCM_MODULE_MODE_AUTO,    "ISS" },
#endif
};

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalI2cCommOperations_t         gPmicI2cfunc = {
    &SblUtilsI2cInit,
    &SblUtilsI2cReadByte,
    &SblUtilsI2cWriteByte,
    NULL,
    NULL
};

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

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SBLUtilsGetDDRAppCopyAddress(void)
{
    uint32_t ddrAddress = SBL_LIB_APP_IMAGE_DDR_ADDRESS;
    return ddrAddress;
}

uint32_t SBLUtilsGetEmif1Size(void)
{
    uint32_t emif1Size = SBL_LIB_CONFIG_EMIF_SIZE;

    return emif1Size;
}

void SBLUtilsGetECCAddrRangePrms(emifEccAddrRangeCfgPrm_t *addrRangeParams)
{
    uint32_t range1Type, range1StartAddr, range1EndAddr;
    uint32_t range2Type, range2StartAddr, range2EndAddr;

    range1Type      = SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE;
    range1StartAddr = SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1;
    range1EndAddr   = SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1;
    range2Type      = SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE;
    range2StartAddr = SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2;
    range2EndAddr   = SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2;

    /* Configure EMIF ECC address parameters */
    addrRangeParams[0U].addrRangeType = range1Type;
    addrRangeParams[0U].startAddr     = range1StartAddr;
    addrRangeParams[0U].endAddr       = range1EndAddr;
    addrRangeParams[0U].addrRangeNum  = EMIF_ECC_ADDR_RANGE_NUM_1;
    if (0U != range1StartAddr)
    {
        addrRangeParams[0U].enableAddrRange = (uint32_t) TRUE;
    }

    addrRangeParams[1U].addrRangeType = range2Type;
    addrRangeParams[1U].startAddr     = range2StartAddr;
    addrRangeParams[1U].endAddr       = range2EndAddr;
    addrRangeParams[1U].addrRangeNum  = EMIF_ECC_ADDR_RANGE_NUM_2;
    if (0U != range2StartAddr)
    {
        addrRangeParams[1U].enableAddrRange = (uint32_t) TRUE;
    }
}

void SBLUtilsInitDspL2RAM(uint32_t dspCoreId)
{
    uint32_t edmaChNum   = 1U;
    uint32_t edmaTccNum  = 1U;
    uint32_t edmaEvtqNum = 0U;
    uint32_t paramSetNum = 1U;
    uint32_t destAddr    = 0U;
    uint32_t index       = 0U;
    uint32_t loopCount   = 288U; /* Size of L2 RAM in KB */

    if (SBLLIB_CORE_ID_DSP1 == dspCoreId)
    {
        destAddr = SOC_DSP1_L2_SRAM_BASE;
    }
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    else if (SBLLIB_CORE_ID_DSP2 == dspCoreId)
    {
        destAddr = SOC_DSP2_L2_SRAM_BASE;
    }
#endif
    else
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Tried to initialize L2 RAM with wrong DSP Id \n");
    }

    for (index = 0U; index < loopCount; index++)
    {
        SBLUtilsTriggerEDMAPolledMode((uint32_t) (&gDspL2RamInitData[0U]),
                                      destAddr + (index * 1024U),
                                      1024U,
                                      edmaChNum,
                                      edmaTccNum,
                                      edmaEvtqNum,
                                      paramSetNum);
    }
}

int32_t SBLUtilsConfigAllVoltageRails(uint32_t oppId)
{
    pmErrCode_t         retVal = PM_SUCCESS;
    uint32_t            siliconRev;
    pmhalPrcmVdId_t     gangedVdRails[PMHAL_PRCM_VD_MAX] = {0};
    uint32_t            index, gangNum, numGangedRails;
    uint32_t            numVdConfigured = 0U, vdInfoSize;
    sblUtilsVdInfo_t   *vdInfoObj = NULL;

    const pmhalPmicOperations_t *pmicOps;
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
    if(SBLLIB_SILICON_PACKAGE_TYPE_17X17 == SBLLibGetSiliconPackageType())
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
#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
        pmicOps = PMHALTps659039GetPMICOps();
#else
        pmicOps = PMHALTps65917GetPMICOps();
#endif
    }
#endif

    retVal = PMHALPmicRegister(pmicOps);

    /* Get the VD rail info based on the current board */
#if defined (SOC_TDA2EX)
    if(SBLLIB_SILICON_PACKAGE_TYPE_17X17 != SBLLibGetSiliconPackageType())
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
    for (index=0; (index<vdInfoSize) && (retVal == PM_SUCCESS); index++)
    {
        if (vdInfoObj[index].gangId == SBLUTILS_VD_NOT_GANGED)
        {
            #if defined (SOC_TDA2PX)
            if ((vdInfoObj[index].vdId == PMHAL_PRCM_VD_MPU) ||
               (vdInfoObj[index].vdId == PMHAL_PRCM_VD_GPU))
            {
                pmicOps = PMHALLP87565GetPMICOps();
            }
            else
            {
                pmicOps = PMHALTps65917GetPMICOps();
            }
            retVal = (pmErrCode_t) PMHALPmicRegister(pmicOps);
            #endif
            if (retVal == PM_SUCCESS)
            {
                if (vdInfoObj[index].vdId == PMHAL_PRCM_VD_CORE)
                {
                    /* Do not perform CORE AVS for ES1.0 Samples */
                    siliconRev = SBLLibGetSiliconRev();
                    if (0U != siliconRev)
                    {
                        /* VD_CORE can only support OPP_NOM */
                        retVal = PMHALVMSetOpp(PMHAL_PRCM_VD_CORE,
                                                PMHAL_VM_OPP_NOM,
                                                PM_TIMEOUT_INFINITE);
                    }
                }
                else
                {
                   #if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
                    if (vdInfoObj[index].vdId == PMHAL_PRCM_VD_MPU)
                    {
                        uint32_t avsVolt = PMHALVMGetAVS0EfuseVoltage(vdInfoObj[index].vdId, oppId);
                        if (avsVolt < 1120U)
                        {
                            /* On the cascade TDA board, the AVS voltage for MPU
                             * cannot go below 1.12 V as the sense and reset circuit will trigger
                             * a device reset.
                             */
                        }
                        else
                        {
                            retVal = PMHALVMSetOpp(vdInfoObj[index].vdId, oppId, PM_TIMEOUT_INFINITE);
                        }
                    }
                    else
                    {
                        retVal = PMHALVMSetOpp(vdInfoObj[index].vdId, oppId, PM_TIMEOUT_INFINITE);
                    }
                    #else
                    retVal = PMHALVMSetOpp(vdInfoObj[index].vdId, oppId, PM_TIMEOUT_INFINITE);
                    #endif
                    numVdConfigured++;
                }
            }
        }
    }

    /* Configure Ganged rails */
    for (gangNum = SBLUTILS_VD_GANG_1;
         (((gangNum <= SBLUTILS_VD_GANG_MAX) && (numVdConfigured <= vdInfoSize))
         && (retVal == PM_SUCCESS));
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
            retVal = SblUtilsConfigGangedVdRails(&gangedVdRails[0],
                                                  numGangedRails,
                                                  oppId);
        }
    }

    SblUtilsMMCSDLdoPowerOn();

    return ((int32_t) retVal);
}

int32_t SBLUtilsConfigPowerDomains(void)
{
    int32_t  retVal   = STW_SOK;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < SBL_UTILS_NUM_ENTRIES_POWER_DOMAIN_STATE_TABLE;
         tblIndex++)
    {
        retVal += PMHALPdmSetPDState(
            (pmhalPrcmPdId_t) gPowerDomainStateTable[tblIndex].domainId,
            (pmhalPrcmPdState_t) gPowerDomainStateTable[tblIndex].
            powerDomainState,
            PM_TIMEOUT_NOWAIT);
    }
    return retVal;
}

void SBLUtilsConfigClockDomains(void)
{
    int32_t  retVal   = STW_SOK;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < SBL_UTILS_NUM_ENTRIES_CLOCK_DOMAIN_STATE_TABLE;
         tblIndex++)
    {
        retVal = PMHALCMSetCdClockMode(
            (pmhalPrcmCdId_t) gClockDomainStateTable[tblIndex].domainId,
            (pmhalPrcmCdClkTrnModes_t) gClockDomainStateTable[tblIndex].
            clockDomainState,
            PM_TIMEOUT_NOWAIT);

        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Clock Domain Config Error - ");
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         gClockDomainStateTable[tblIndex].clockDomainName);
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, " \n");
        }
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n Clock Domain Configuration Completed \n");
}

void SBLUtilsConfigModules(void)
{
    int32_t  retVal   = STW_SOK;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < SBL_UTILS_NUM_ENTRIES_MODULE_ENABLE_TABLE;
         tblIndex++)
    {
        if (PMHAL_PRCM_MOD_DSS == gModuleEnableTable[tblIndex].moduleId)
        {
            /*MMR Enable*/
            SBLLibUnlockControlIODSS();

            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_DSS);
        }
        if (PMHAL_PRCM_MOD_MMC1 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
                                   PMHAL_PRCM_DPLL_PER);
            PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_MMC1_FCLK, (uint32_t) 2U);
        }
        if (PMHAL_PRCM_MOD_GPIO1 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO1);
        }
        if (PMHAL_PRCM_MOD_GPIO2 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO2);
        }
        if (PMHAL_PRCM_MOD_GPIO3 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO3);
        }
        if (PMHAL_PRCM_MOD_GPIO4 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO4);
        }
        if (PMHAL_PRCM_MOD_GPIO5 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO5);
        }
        if (PMHAL_PRCM_MOD_GPIO6 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO6);
        }
        if (PMHAL_PRCM_MOD_GPIO7 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO7);
        }
        if (PMHAL_PRCM_MOD_GPIO8 == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO8);
        }
#if defined (SOC_TDA2PX)
        if (PMHAL_PRCM_MOD_ISS == gModuleEnableTable[tblIndex].moduleId)
        {
            PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_ISS_GFCLK_MUX,
                                   PMHAL_PRCM_DPLL_CORE);
            PMHALResetRelease(PMHAL_PRCM_RG_EVE3_RST, PM_TIMEOUT_NOWAIT);
        }
#endif

        retVal = PMHALModuleModeSet(
            (pmhalPrcmModuleId_t) gModuleEnableTable[tblIndex].moduleId,
            (pmhalPrcmModuleSModuleMode_t) gModuleEnableTable[tblIndex].
            moduleEnableMode,
            PM_TIMEOUT_INFINITE);

        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Module Enable Error - ");
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         gModuleEnableTable[tblIndex].moduleName);
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, " \n");
        }
    }
    if (STW_SOK == retVal)
    {
        /* Selects the divider value for generating the Thermal
         * Sensor clock from WKUPAON_ICLK source. The divider
         * has to be selected so as to guarantee a frequency
         * between 1MHz and 2MHz.
         */
        PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
                                   (uint32_t) 16U);
    }
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n Module Enable Configuration Completed \n");
}

void SBLUtilsScaleIODelay(uint32_t bootMode)
{
    volatile uint32_t dummyRead = 0U, siliconRev = 0U;

    /* Unlock the MMR_LOCK1 */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_MMR_LOCK_1,
                UNLOCK_MMR_LOCK1);

    /* Unlock the MMR_LOCK5 */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_MMR_LOCK_5,
                UNLOCK_MMR_LOCK5);

    /* Unlock the global lock */
    HW_WR_REG32(SOC_DELAYLINE_BASE + CONFIG_REG_8,
                CONFIG_REG_8_UNLOCK_GLOBAL_LOCK);

    /*
     * Update config_reg2 based on actual sysclk1 frequency.
     * Take sysclock1 period in ps and divide by 5 and write to register.
     * This ensures calibration logic assumes the correct clock reference.
     */
    HW_WR_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_2,
                  CONFIG_REG_2_REFCLK_PERIOD,
                  REFCLK_PERIOD_L4ICLK_66_5_MHZ);

    /* Trigger the recalibration */
    HW_WR_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_0,
                  CONFIG_REG_0_CALIBRATION_START,
                  0x1);

    /*
     * Read CALIBRATION_START until it is read as 0,
     * indicating recalibration is complete.
     */
    while ((uint32_t) 0U != HW_RD_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_0,
                                          CONFIG_REG_0_CALIBRATION_START))
    {}

    /*
     * Isolate all the IO.
     */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS,
                0xC200000U);

    HW_WR_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE_OVERRIDE);

    while ((uint32_t) 0x1U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_ISOIN,
                  0x1);

    dummyRead = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                              CTRL_CORE_SMA_SW_0,
                              CTRL_CORE_SMA_SW_0_ISOIN);

    HW_WR_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE_NOOVERRIDE);

    while ((uint32_t) 0x0U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    /* Update delay mechanism for each IO with recalibrated values */
    HW_WR_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_0,
                  CONFIG_REG_0_ROM_READ,
                  0x1);

    /*
     * Read ROM_READ until it is read as 0,
     * indicating reload is complete.
     */
    while ((uint32_t) 0U != HW_RD_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_0,
                                          CONFIG_REG_0_ROM_READ))
    {}

    /* Get the pad config array object and size of it. */
    gPadDelayConfigObj = SBLUtilsGetPadDelayConfigStruct(&gPadDelayConfigSize,
                                                         bootMode);
    if (gPadDelayConfigObj != NULL)
    {
        /* Calculate and update the config values in pad config array object*/
        gPadDelayConfigRegValueObj = SBLUtilsGetDelayConfigRegValStruct(
            gPadDelayConfigObj, gPadDelayConfigSize);
        /* Configure PAD mux for SoC along with Virtual and Manual Mode Delays */
        SBLUtilsConfigPadMux(gPadDelayConfigObj,
                            gPadDelayConfigRegValueObj,
                            gPadDelayConfigSize);
    }

    siliconRev = SBLLibGetSiliconRev();
    /* Disable RGMII half cycle delay for TDA2xx ES2.0 silicon */
    if (2U <= siliconRev)
    {
#if defined (SOC_TDA2XX)
#if !defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
        HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                      CTRL_CORE_SMA_SW_1,
                      CTRL_CORE_SMA_SW_1_RGMII2_ID_MODE_N,
                      0x1U);

        HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                      CTRL_CORE_SMA_SW_1,
                      CTRL_CORE_SMA_SW_1_RGMII1_ID_MODE_N,
                      0x1U);
#endif
#endif
    }

    /*
     * Remove all IOs from isolation.
     */
    HW_WR_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE_OVERRIDE);

    while ((uint32_t) 0x1U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_ISOIN,
                  0x0U);

    dummyRead = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                              CTRL_CORE_SMA_SW_0,
                              CTRL_CORE_SMA_SW_0_ISOIN);

    HW_WR_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
                  PRM_IO_PMCTRL_ISOCLK_OVERRIDE_NOOVERRIDE);

    while ((uint32_t) 0x0U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    /* Lock the MMR_LOCK1 */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_1,
                LOCK_MMR_LOCK1);

    /* Lock the MMR_LOCK5 */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_5,
                LOCK_MMR_LOCK5);

    /* Lock the global lock */
    HW_WR_REG32(SOC_DELAYLINE_BASE + CONFIG_REG_8,
                CONFIG_REG_8_LOCK_GLOBAL_LOCK);

    /* Dummy read to remove compiler warning */
    dummyRead = dummyRead;
}

void SBLUtilsWDTimerBegin(void)
{
    uint32_t wdtIsr = (uint32_t) &SBLUtilsWDTimerIsr;

    /* Stop the WDT */
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /* Write the counter value for 3 mins */
    WDTIMERCounterSet(SOC_WD_TIMER2_BASE, SBL_WD_TIMER_OVF_VALUE);

    /* Write the counter load value for 3 mins */
    WDTIMERReloadSet(SOC_WD_TIMER2_BASE, SBL_WD_TIMER_OVF_VALUE);

    /* Enable prescaler & set the prescaler value */
    WDTIMERPreScalerClkEnable(SOC_WD_TIMER2_BASE, WD_TIMER_PRESCALER_CLK_DIV_1);

    /* Set the DLY interrupt count value to 2 mins */
    WDTIMERDelaySet(SOC_WD_TIMER2_BASE, SBL_WD_TIMER_DLY_VALUE);

    /* Enable DLY interrupt */
    WDTIMERIntEnable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Register WDT DLY event interrupt */
    Intc_IntRegister(WD_TIMER_DELAY_INT, (IntrFuncPtr) wdtIsr, 0U);

    /* Set the priority for wdtimer DLY event in AINTC */
    Intc_IntPrioritySet(WD_TIMER_DELAY_INT, (uint16_t) 1U, (uint8_t) 0U);

    /* Enable the wdtimer DLY interrupt in AINTC */
    Intc_SystemEnable(WD_TIMER_DELAY_INT);

    /* Start the WDT */
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

void SBLUtilsWDTimerIsr(void *ptr)
{
    /* Stop the WDT */
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /* Clear DLY interrupt status bit */
    WDTIMERIntStatusClear(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Enable DLY interrupt */
    WDTIMERIntEnable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Trigger reload */
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x1010);
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x0101);

    /* Start the WDT */
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

void SBLUtilsWDTimerEnd(void)
{
    /* Stop the WDT */
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /* Trigger reload */
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x1010);
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x0101);

    /* Disable DLY interrupt */
    WDTIMERIntDisable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Disable the WDT DLY interrupt in AINTC */
    Intc_SystemDisable(WD_TIMER_DELAY_INT);

    /* Unregister the wdtimer DLY interrupt from system vector table */
    Intc_IntUnregister(WD_TIMER_DELAY_INT);

    /* Start the WDT */
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

int32_t SBLUtilsConfigStaticDependency(void)
{
    int32_t         pmError;
    pmhalPrcmCdId_t clockDomain = 0U;

    for (clockDomain = (PMHAL_PRCM_CD_LOWER_BOUND + 1U);
         clockDomain < PMHAL_PRCM_CD_COUNT;
         clockDomain++)
    {
        /* Do not care much about the return value here because not
         * not all clock domains are masters */
        PMHALStaticDepDisableAllSlaveDep(clockDomain);
    }

    pmError  = PMHALStaticDepEnable(PMHAL_PRCM_CD_MPU, PMHAL_PRCM_CD_EMIF);
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_MPU, PMHAL_PRCM_CD_L3MAIN1);
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_IPU1, PMHAL_PRCM_CD_L3MAIN1);
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_IPU2, PMHAL_PRCM_CD_L3MAIN1);
#endif
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_DSP1, PMHAL_PRCM_CD_L3MAIN1);
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_DSP2, PMHAL_PRCM_CD_L3MAIN1);
#endif
    return pmError;
}

int32_t SBLUtilsNorRead(void    *dstAddr,
                        uint32_t srcOffsetAddr,
                        uint32_t length)
{
    /* Read from NOR memory */
    SblUtilsNorReadEdma(dstAddr, srcOffsetAddr, length, (uint32_t) 1U);

    return STW_SOK;
}

void SBLUtilsNorFileSeek(uint32_t *srcAddr, uint32_t numBytes)
{
    *(srcAddr) = numBytes;
}

int32_t SBLUtilsNorBootRprc(sbllibAppImageParseParams_t *imageParams)
{
    imageParams->appImageOffset = SBL_UTILS_APP_IMAGE_OFFSET_NOR;

    SBLLibRegisterImageCopyCallback(&SBLUtilsNorRead,
                                    &SBLUtilsDDRReadEdma,
                                    &SBLUtilsNorFileSeek);

    return (SBLLibMultiCoreImageParseV2(imageParams));
}

int32_t SBLUtilsQspiReadSectors(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length)
{
    /* Read from QSPI */
    QSPI_ReadSectors_edma(dstAddr, srcOffsetAddr, length, (uint32_t) 1U);

    return STW_SOK;
}

int32_t SBLUtilsQspiBootRprc(sbllibAppImageParseParams_t *imageParams)
{
    uint32_t          deviceId, mfgId, devId;
    qspi_DeviceType_e deviceType = DEVICE_TYPE_QSPI4;
    char devIdStr[10] = {0}, mfgIdStr[10] = {0};

    QSPI_Initialize(deviceType);

    /* Print the Device ID & Manufacturer ID */
    deviceId = QSPI_GetDeviceId();
    mfgId    = deviceId & 0xFFU;
    devId    = (deviceId & 0xFF0000U) >> 16U;

    SBLLibConvertHexToString(mfgId, mfgIdStr);
    SBLLibConvertHexToString(devId, devIdStr);

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n Manufacturer ID - ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, mfgIdStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n Device ID - ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, devIdStr);

    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                        QSPI_CS0);

    SBLLibRegisterImageCopyCallback(&SBLUtilsQspiReadSectors,
                                    &SBLUtilsDDRReadEdma,
                                    &QSPI_seek);
    imageParams->appImageOffset = SBL_UTILS_APP_IMAGE_OFFSET_QSPI;

    return (SBLLibMultiCoreImageParseV2(imageParams));
}

int32_t SBLUtilsSDFileRead(void    *dstbuff,
                           uint32_t srcFileAddr,
                           uint32_t numBytes)
{
    uint8_t *buffPtr   = (uint8_t *) dstbuff;
    uint32_t bytesRead = 0U;
    int32_t  retVal    = STW_SOK;
    FRESULT  fresult   = FR_OK;

    f_lseek(&gAppImageSDFilePtr, srcFileAddr);

    fresult = f_read(&gAppImageSDFilePtr,
                     (void *) buffPtr,
                     numBytes,
                     (UINT *) &bytesRead);
    if ((FR_OK != fresult) || (bytesRead != numBytes))
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

void SBLUtilsSDFileSeek(uint32_t *filePtr, uint32_t numBytes)
{
    *filePtr = numBytes;

    f_lseek(&gAppImageSDFilePtr, numBytes);
}

int32_t SBLUtilsSDBootRprc(sbllibAppImageParseParams_t *imageParams)
{
    int32_t    retVal   = STW_EFAIL;
    char      *filename = "AppImage";
    FRESULT    fresult;
    MMC_INST_t num = MMC1_INST;

    if (0 != HSMMCSDInit(num))
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, "\n No valid SD card \n");
        retVal = STW_EFAIL;
    }
    else
    {
        fresult = f_open(&gAppImageSDFilePtr, filename, (BYTE) FA_READ);
        if (FR_OK != fresult)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n SD Boot - File open fails \n");
            retVal = STW_EFAIL;
        }
        else
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n SD Boot - file open completed successfully \n");

            SBLLibRegisterImageCopyCallback(&SBLUtilsSDFileRead,
                                            &SBLUtilsDDRReadEdma,
                                            &SBLUtilsSDFileSeek);
            imageParams->appImageOffset = 0U;

            retVal = SBLLibMultiCoreImageParseV2(imageParams);

            f_close(&gAppImageSDFilePtr);
        }
    }
    return retVal;
}

int32_t SBLUtilsUartPrcm(UART_INST_t uartInstance)
{
    int32_t retVal = STW_SOK;

    retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER2,
                                   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                   PM_TIMEOUT_INFINITE);

    if (UART1_INST == uartInstance)
    {
        /* Enable UART1 module */
        retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_UART1,
                                     PMHAL_PRCM_MODULE_MODE_ENABLED,
                                     PM_TIMEOUT_INFINITE);
    }
    else if (UART3_INST == uartInstance)
    {
        /* Enable UART3 module */
        retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                     PMHAL_PRCM_MODULE_MODE_ENABLED,
                                     PM_TIMEOUT_INFINITE);
    }
    else if (UART4_INST == uartInstance)
    {
        /* Enable UART4 module */
        retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_UART4,
                                     PMHAL_PRCM_MODULE_MODE_ENABLED,
                                     PM_TIMEOUT_INFINITE);
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

void SBLUtilsConfigMultiOppDpll(uint32_t oppId)
{
    pmhalPrcmDpllConfig_t *dpllParams;
    int32_t  retVal = STW_SOK;
    pmhalPrcmSysClkVal_t sysClkFreq = PMHALCMGetSysClockFreqEnum();

    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_COREAON,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

    /* Configure DPLL MPU */
    SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_MPU,
                           sysClkFreq,
                           oppId,
                           &dpllParams);
    retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_MPU,
                                  dpllParams,
                                  PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL MPU not configured Correctly \n");
        SBLLibAbortBoot();
    }

    /* Configure DPLL DSP */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_DSP,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DSP,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL DSP not configured Correctly \n");
        SBLLibAbortBoot();
    }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    /* Configure DPLL EVE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_EVE,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_EVE,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL EVE not configured Correctly \n");
        SBLLibAbortBoot();
    }
#endif

    /* Configure DPLL IVA */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_IVA,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_IVA,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL IVA not configured Correctly \n");
        SBLLibAbortBoot();
    }

    /* Configure DPLL GPU */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_GPU,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_GPU,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL GPU not configured Correctly \n");
        SBLLibAbortBoot();
    }

}

void SBLUtilsConfigSingleOppDpll(void)
{
    pmhalPrcmDpllConfig_t *dpllParams;
    int32_t  retVal = STW_SOK;
    pmhalPrcmSysClkVal_t sysClkFreq = PMHALCMGetSysClockFreqEnum();

    /* Configure DPLL DDR */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_DDR,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DDR,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL DDR not configured Correctly \n");
        SBLLibAbortBoot();
    }

    /* Configure DPLL GMAC */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_GMAC,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_GMAC,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL GMAC not configured Correctly \n");
        SBLLibAbortBoot();
    }

    /* Configure DPLL ABE */
    HW_WR_FIELD32(
        SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_PLL_SYS,
        CM_CLKSEL_ABE_PLL_SYS_CLKSEL,
        CM_CLKSEL_ABE_PLL_SYS_CLKSEL_SEL_SYS_CLK2);

    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_ABE,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_ABE,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL ABE not configured Correctly \n");
        SBLLibAbortBoot();
    }

    /* Configure DPLL PCIE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_PCIE_REF,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PCIE_REF,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL PCIE not configured Correctly \n");
        SBLLibAbortBoot();
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n DPLL Configuration Completed \n");
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
static inline void SblDelay(uint32_t delay)
{
    uint32_t i;
    for (i = 0; i < (1000U * delay); ++i)
    {}
}

static void SblUtilsMMCSDLdoPowerOn(void)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                         CTRL_CORE_CONTROL_PBIAS);

    regVal &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS,
                regVal);

    /* Wait 10 micro-seconds */
    SblDelay(10U);

    regVal &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS,
                regVal);

    /* Enable SDCARD_BIAS_VMODE */
    regVal |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK;

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS,
                regVal);

    regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                         CTRL_CORE_CONTROL_PBIAS);

    regVal |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS,
                regVal);

    /* Wait 150 micro-seconds */
    SblDelay(150U);

    regVal |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS,
                regVal);

    /* Wait 150 micro-seconds */
    SblDelay(150U);
}

static int32_t SblUtilsI2cInit(void)
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

static void SblUtilsNorReadEdma(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length,
                                uint32_t edmaChNum)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          bCntValue = 1U;
    uint32_t          remBytes  = 0;
    uint32_t          aCntValue = length;
    uint32_t          addr      = (uint32_t) (dstAddr);
    uint32_t          maxACnt   = 0x7FF0U;
    if (length > maxACnt)
    {
        bCntValue = (length / maxACnt);
        remBytes  = (length % maxACnt);
        aCntValue = maxACnt;
    }

    /* Compute NOR address and size */
    edmaParam.opt      = 0;
    edmaParam.srcAddr  = SBL_UTILS_NOR_BASE + srcOffsetAddr;
    edmaParam.destAddr = addr;
    edmaParam.aCnt     = aCntValue;
    edmaParam.bCnt     = bCntValue;
    edmaParam.cCnt     = 1;
    edmaParam.srcBIdx  = aCntValue;
    edmaParam.destBIdx = aCntValue;
    edmaParam.srcCIdx  = 0;
    edmaParam.destCIdx = 0;
    edmaParam.linkAddr = 0xFFFF;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((edmaChNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK) |
         EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum, EDMA3_TRIG_MODE_MANUAL);

    while (0U ==
           (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
            ((uint32_t) 1U << edmaChNum)))
    {
        /* Busy Loop */
    }
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum);
    if (0U != remBytes)
    {
        /* Compute NOR address and size */
        edmaParam.opt     = 0;
        edmaParam.srcAddr =
            (SBL_UTILS_NOR_BASE + ((bCntValue * maxACnt) + srcOffsetAddr));
        edmaParam.destAddr = (addr + (maxACnt * bCntValue));
        edmaParam.aCnt     = remBytes;
        edmaParam.bCnt     = 1;
        edmaParam.cCnt     = 1;
        edmaParam.srcBIdx  = remBytes;
        edmaParam.destBIdx = remBytes;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFF;
        edmaParam.opt     |=
            (EDMA_TPCC_OPT_TCINTEN_MASK |
             ((edmaChNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (0U ==
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                ((uint32_t) 1U << edmaChNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum);
    }
}

int32_t SBLUtilsDDRReadEdma(void    *dstAddr,
                            uint32_t srcAddr,
                            uint32_t length)
{
    int32_t retVal = STW_SOK;

    if (NULL == dstAddr)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        EDMA3CCPaRAMEntry edmaParam;
        uint32_t          edmaChNum = 1U;
        uint32_t          bCntValue = 1U;
        uint32_t          remBytes  = 0;
        uint32_t          aCntValue = length;
        uint32_t          addr      = (uint32_t) (dstAddr);
        uint32_t          maxACnt   = 0x7FF0U;
        if (length > maxACnt)
        {
            bCntValue = (length / maxACnt);
            remBytes  = (length % maxACnt);
            aCntValue = maxACnt;
        }

        /* Assign EDMA Params for AB sync transfer */
        edmaParam.opt      = 0;
        edmaParam.srcAddr  = (uint32_t) srcAddr;
        edmaParam.destAddr = addr;
        edmaParam.aCnt     = aCntValue;
        edmaParam.bCnt     = bCntValue;
        edmaParam.cCnt     = 1;
        edmaParam.srcBIdx  = aCntValue;
        edmaParam.destBIdx = aCntValue;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFF;
        edmaParam.opt     |=
            (EDMA_TPCC_OPT_TCINTEN_MASK |
             ((edmaChNum <<
               EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK) |
             EDMA_TPCC_OPT_SYNCDIM_MASK);

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (0U ==
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                ((uint32_t) 1U << edmaChNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum);
        if (0U != remBytes)
        {
            /* Assign EDMA Params for remaining bytes */
            edmaParam.opt      = 0;
            edmaParam.srcAddr  = (bCntValue * maxACnt) + (uint32_t) srcAddr;
            edmaParam.destAddr = (addr + (maxACnt * bCntValue));
            edmaParam.aCnt     = remBytes;
            edmaParam.bCnt     = 1;
            edmaParam.cCnt     = 1;
            edmaParam.srcBIdx  = remBytes;
            edmaParam.destBIdx = remBytes;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFF;
            edmaParam.opt     |=
                (EDMA_TPCC_OPT_TCINTEN_MASK |
                 ((edmaChNum <<
                   EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

            EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum, &edmaParam);
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum,
                                EDMA3_TRIG_MODE_MANUAL);

            while (0U ==
                   (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                    ((uint32_t) 1U << edmaChNum)))
            {
                /* Busy Loop */
            }
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaChNum);
        }
    }

    CACHEA15Invalidate(CACHE_A15_TYPE_ALLD, (uint32_t) (dstAddr), length);

    return retVal;
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
                                       configOpp);

        if (currAvsVolt == 0U)
        {
            retVal = PM_VOLTAGE_INVALID;
        }
        if (currAvsVolt > maxAvsVolt)
        {
            maxAvsVolt = currAvsVolt;
            maxAvsVdId = gangedVdRails[vdCount];
        }
    }

    if (maxAvsVdId != PMHAL_PRCM_VD_UNDEF)
    {
        retVal += (int32_t)PMHALVMSetOpp(maxAvsVdId,
                                configOpp, PM_TIMEOUT_INFINITE);
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (retVal == PM_SUCCESS)
    {
        /* Once the AVS and ABB is done for the voltage rail for which the AVS
        * EFUSE value is the highest. It is important to perform the ABB
        * configuration for the other voltage rails.
        */
        for (vdCount = 0U; vdCount < numGangedRails; vdCount++)
        {
            if (gangedVdRails[vdCount] != maxAvsVdId)
            {
                retVal += PMHALVMEnableABB(gangedVdRails[vdCount],
                                        configOpp);
            }
            if (PM_SUCCESS != retVal)
            {
                break;
            }
        }
    }

    return retVal;
}

