/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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
 */

/**
 *   Component:       staterware
 *
 *   Filename:          platform.c
 *
 *   Description:       This file has generic function for board specific
 *                      configurations
 *
 *   Author:                vinothr
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <platformPriv.h>
#include <ti/drv/pm/pmhal.h>

/****************************************************************************
 *                       MACRO DEFINITIONS
 ****************************************************************************/

/** \brief Enables the MMR region lock  */
/**<  Note : Only if required Enable the macro to lock the MMR region
 *    In the code if unlock MMR and lock MMR is not taken care properly ,
 *    by enabling this macro will result in hang while configuring pinmux ,
 *    PRCM etc.,
 */
/* #define PLATFORM_MMR_REG_LOCK_ENABLE*/

/* ============================================================================
 * FUNCTIONS
 * =============================================================================
 */

/*
 * \brief cntrl_core_pad_configuration function to program the pad
 * properties
 *
 *
 * \param[in]   baseAdd - Base address of pad config register
 * \param[in]       pad_config - property of the pad to be configured.
 *
 * \return           error status.If error has occured it returns a non zero
 *                   value.
 *                   If no error has occured then return status will be zero. .
 *
 */
void cntrl_core_pad_configuration(uint32_t            baseAdd,
                                  const pad_config_t *pad_config)
{
    uint32_t reg_val;

    PlatformUnlockMMR();
    reg_val = HW_RD_REG32(baseAdd + (pad_config->pin_num));

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)

    if (pad_config->pullud_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_MASK;
        reg_val |= (uint32_t) pad_config->pullud_enable <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_SHIFT;
    }
    if (pad_config->pull_typeselect != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_MASK;
        reg_val |= (uint32_t) pad_config->pull_typeselect <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_SHIFT;
    }
    if (pad_config->input_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_MASK;
        reg_val |= (uint32_t) pad_config->input_enable <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_SHIFT;
    }
    if (pad_config->slewcontrol != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_MASK;
        reg_val |= (uint32_t) pad_config->slewcontrol <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_SHIFT;
    }
    if (pad_config->wakeup_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_MASK;
        reg_val |= (uint32_t) pad_config->wakeup_enable <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_SHIFT;
    }
#elif defined (SOC_TDA3XX)

    if (pad_config->pullud_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_PULLUDENABLE_MASK;
        reg_val |= (uint32_t) pad_config->pullud_enable <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_PULLUDENABLE_SHIFT;
    }
    if (pad_config->pull_typeselect != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_PULLTYPESELECT_MASK;
        reg_val |= (uint32_t) pad_config->pull_typeselect <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_PULLTYPESELECT_SHIFT;
    }
    if (pad_config->input_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_INPUTENABLE_MASK;
        reg_val |= (uint32_t) pad_config->input_enable <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_INPUTENABLE_SHIFT;
    }
    if (pad_config->slewcontrol != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_SLEWCONTROL_MASK;
        reg_val |= (uint32_t) pad_config->slewcontrol <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_SLEWCONTROL_SHIFT;
    }
/* Todo : Please check before use - Why
 * CTRL_CORE_PAD_IO_GPMC_AD0_WAKEUPENABLE_MASK is undefined for TDA3XX */
#if 0
    if (pad_config->wakeup_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_WAKEUPENABLE_MASK;
        reg_val |= (uint32_t) pad_config->wakeup_enable <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_WAKEUPENABLE_SHIFT;
    }
#endif
#endif
    HW_WR_REG32(baseAdd + (pad_config->pin_num), reg_val);

    /* IO input glitches may occur when switching pull type and
     * mux mode simultaneously. To avoid such glitches it is expected
     * two separate register writes to transition to the desired state */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    reg_val &= ~((uint32_t) CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_MASK);
    reg_val |= (uint32_t) pad_config->muxmode <<
               CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_SHIFT;
#elif defined (SOC_TDA3XX)
    reg_val &= ~((uint32_t) CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_MASK);

    reg_val |= (uint32_t) pad_config->muxmode <<
               CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_SHIFT;
#endif

    HW_WR_REG32(baseAdd + (pad_config->pin_num), reg_val);
    PlatformLockMMR();
}

/*
 * \brief configure_pad function to program all the pad. Get
 * called at boot-up time
 *
 *
 * \param[in]   pad_array - List of pad to be configured at boot time
 *
 * \return              none
 *
 */
void configure_pad(const pad_config_t *pad_array, uint32_t elements)
{
    uint32_t i;

    for (i = 0; i < elements; ++i)
    {
        cntrl_core_pad_configuration(SOC_CORE_PAD_IO_REGISTERS_BASE,
                                     &pad_array[i]);
    }
}

void PlatformUnlockMMR(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /* unlock MMR1 space for region 0x0100 to 0x079F */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_1,
        CTRL_CORE_MMR_LOCK_1_MMR_LOCK_1_TOUNLOCK);
    /* unlock MMR2 space for region 0x07A0 to 0x0D9F */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_2,
        CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOUNLOCK);
    /* unlock MMR3 space for region 0x0DA0 to 0x0FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_3,
        CTRL_CORE_MMR_LOCK_3_MMR_LOCK_3_TOUNLOCK);
    /* unlock MMR4 space for region 0x1000 to 0x13FF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_4,
        CTRL_CORE_MMR_LOCK_4_MMR_LOCK_4_TOUNLOCK);
    /* unlock MMR5 space for region 0x1400 to 0x1FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOUNLOCK);
#elif defined (SOC_TDA3XX)
    /* unlock MMR1 space for region 0x0100 to 0x079F */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_1,
        CTRL_CORE_MMR_LOCK_1_TOUNLOCK);
    /* unlock MMR2 space for region 0x07A0 to 0x0D9F */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_2,
        CTRL_CORE_MMR_LOCK_2_TOUNLOCK);
    /* unlock MMR3 space for region 0x0DA0 to 0x0FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_3,
        CTRL_CORE_MMR_LOCK_3_TOUNLOCK);
    /* unlock MMR4 space for region 0x1000 to 0x13FF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_4,
        CTRL_CORE_MMR_LOCK_4_TOUNLOCK);
    /* unlock MMR5 space for region 0x1400 to 0x1FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_TOUNLOCK);
#endif
} /* PlatformUnlockMMR */

void PlatformLockMMR(void)
{
#ifdef PLATFORM_MMR_REG_LOCK_ENABLE
    /* Lock MMR1 space for region 0x0100 to 0x079F */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_1,
        CTRL_CORE_MMR_LOCK_1_TOLOCK);
    /* Lock MMR2 space for region 0x07A0 to 0x0D9F */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_2,
        CTRL_CORE_MMR_LOCK_2_TOLOCK);
    /* Lock MMR3 space for region 0x0DA0 to 0x0FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_3,
        CTRL_CORE_MMR_LOCK_3_TOLOCK);
    /* Lock MMR4 space for region 0x1000 to 0x13FF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_4,
        CTRL_CORE_MMR_LOCK_4_TOLOCK);
    /* Lock MMR5 space for region 0x1400 to 0x1FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_TOLOCK);
#endif
} /* PlatformLockMMR */

/*Todo : Please check before use for TDA3XX*/
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/**
 * \brief       This API provides the FT Rev Value.
 *
 * \param       None.
 *
 * \return      FT Revision.
 *
 **/
uint32_t PlatformGetFtRev(void)
{
    uint32_t ftRev;

    ftRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_STD_FUSE_DIE_ID_2);

    /* FT revision is found in bits [15:8] */
    ftRev &= (uint32_t) 0x0000FF00U;

    ftRev = (ftRev >> 0x8);

    return (ftRev);
}

void PlatformUnlockControlIODSS(void)
{
    uint32_t tmpVar;
    /*Unlock CTRL_CORE_CONTROL_IO_2 for DSS access*/
    tmpVar = HW_RD_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_CONTROL_IO_2 +
                         (uint32_t) 0x100);
    tmpVar |= 0x00000001U;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_CONTROL_IO_2 +
                (uint32_t) 0x100, tmpVar);
}

#endif

void PlatformEDMAWkupDepEnable(void)
{
    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC1_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC1_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC2_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC2_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPCC_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPCC_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
void PlatformGPMCClockEnable(void)
{
    /* Set the access to the GPMC registers - Enable GPMC Clock */
    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_GPMC_CLKCTRL, 0x1);

    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        CM_L3MAIN1_GPMC_CLKCTRL) & (0x00030000U)) != 0x0)
    {
        ;
    }
}

void PlatformGPIOClockEnable(void)
{
    /* Set the access to the GPMC registers - Enable GPMC Clock */
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO2_CLKCTRL, 0x101);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_GPIO2_CLKCTRL) & (0x00030000U)) != 0x0)
    {
        ;
    }
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO3_CLKCTRL, 0x101);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_GPIO3_CLKCTRL) & (0x00030000U)) != 0x0)
    {
        ;
    }
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO4_CLKCTRL, 0x101);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_GPIO4_CLKCTRL) & (0x00030000U)) != 0x0)
    {
        ;
    }
}

void wait(int32_t count)
{
    volatile int32_t i = count;
    while (i > 0)
    {
        i--;
    }
}

#ifdef REGRESSION_MODE

void regressiontest_log_result(regressiontest_result_t arg)
{
    sbl_regression_log_bfr.sbl_regression_tc_result_reg = arg;
}

#endif

#endif

int32_t PlatformDcanClkConfig(uint32_t instance)
{
    int32_t retVal = 0;

    /* Configure the Control module - Clock in NO_SLEEP mode
     * This is optional and if not done RAMINIT will succeed but RAMINIT.DONE
     * bit won't be set for DCAN1.
     */
    /*Force Wake-up clock domain l4cfg*/
    retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4CFG,
                                   PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP,
                                   PM_TIMEOUT_INFINITE);

    if (instance == 0)
    {
        /*Configure the DCAN1 module - Clock in SW_WAKE mode */
        /*Force Wake-up clock domain wkupaon*/
        retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_WKUPAON,
                                        PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                        PM_TIMEOUT_INFINITE);
    }
    else
    {
        /*Configure the DCAN2 module - Clock in SW_WAKE mode */
        /*Force Wake-up clock domain l4per2*/
        retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER2,
                                        PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                        PM_TIMEOUT_INFINITE);
    }

    return retVal;
}

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */

void HAL_CTRL_UnlockMMR(void)
{
    PlatformUnlockMMR();
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
uint32_t CTRLGetSiliconRev(void)
{
    uint32_t siliconRev;
    siliconRev = PlatformGetSiliconRev();

    return (siliconRev);
}

uint32_t CTRLGetFtRev(void)
{
    uint32_t ftRev;
    ftRev = PlatformGetFtRev();

    return (ftRev);
}

void HAL_CTRL_Control_IO_DSS(void)
{
    PlatformUnlockControlIODSS();
}

void EDMAModuleClkConfig(void)
{
    PlatformEDMAWkupDepEnable();
}

void GPMC_clock_enable(void)
{
    PlatformGPMCClockEnable();
}

void GPIO_clock_enable(void)
{
    PlatformGPIOClockEnable();
}

#endif
