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

/*
 * \file platform_tda3xx.c
 *
 * \brief  Contains board specific configurations
 *
 */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/

/* Todo : Define GPMC MUX Val */

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

/******************************************************************************
**                      EXTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
#ifdef REGRESSION_MODE
sbl_regression_log_bfr_t sbl_regression_log_bfr  __attribute__ ((section(
                                                                     ".sbl_reg_log_bfr")));
#endif

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/**
 * \brief       This API provides the Silicon Rev Value.
 *
 * \param       None.
 *
 * \return      Silicon Revision.
 *
 * \note        For TDA3xx
 *              0: Silicon Rev 1.0
 *              1: Silicon Rev 1.0A
 *              2: Silicon Rev 2.0
 **/
uint32_t PlatformGetSiliconRev(void)
{
    uint32_t siliconRev;

    siliconRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE + CTRL_WKUP_STD_FUSE_DIE_ID_3);

    siliconRev = siliconRev & 0x0000001FU;

    return (siliconRev);
}

void PlatformMCSPI1PrcmEnable(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL, 0x02);
    while (HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL) !=
           0x02U)
    {
        ;
    }
}

void PlatformMCSPI2PrcmEnable(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL, 0x02);
    while (HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL) !=
           0x02U)
    {
        ;
    }
}

void PlatformGPMCPinCtrl(void)
{
    /* Todo : GPMC PinCtrl */
}

void PlatformGPMCConfig(void)
{
    /* Todo : GPMC config */
}

uint32_t PlatformGetQspiMode(void)
{
    uint32_t qspiMode = 0U;
    if (PlatformGetSiliconPackageType() == PLATFORM_SILICON_PACKAGE_TYPE_12X12)
    {
        qspiMode = 3U;
    }
    return qspiMode;
}

void PlatformDCAN1PrcmEnable(void)
{
    /*CM_WKUPAON_DCAN1_CLKCTRL*/
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                  CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE,
                  CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                          CM_WKUPAON_DCAN1_CLKCTRL_IDLEST)) ==
           CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }
}

void PlatformDCAN2PrcmEnable(void)
{
    /*CM_WKUPAON_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                  CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
                  CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                          CM_L4PER2_DCAN2_CLKCTRL_IDLEST)) ==
           CM_L4PER2_DCAN2_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }
}

void PlatformDcanMessageRamInit(uint32_t instance)
{
    uint32_t status = 0U;

    switch (instance)
    {
        case 0U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);

            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_CLEAR);
            break;

        case 1U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_CLEAR);
            break;

        default:
            break;
    }
}

uint32_t PlatformGetSiliconPackageType(void)
{
    uint32_t packageType, regVal;

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
    return packageType;
}

void PlatformMCASP1PrcmEnable(void)
{
    HW_WR_REG32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL, 0x02);
    while ((HW_RD_REG32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL)) !=
           0x02U)
    {
        ;
    }
}

int32_t PlatformGetRCOscFreq(uint32_t *freqHz)
{
    int32_t status = STW_EFAIL;

    if(PlatformGetSiliconRev() >= 2U)
    {
        *freqHz = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                CTRL_CORE_RC_OSC_FREQUENCY,
                                CTRL_CORE_RC_OSC_FREQUENCY_CALIBRATION_VAL);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }

    return status;
}
