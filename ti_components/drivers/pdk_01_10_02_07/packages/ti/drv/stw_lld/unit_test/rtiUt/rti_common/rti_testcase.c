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
 *  \file     rti_testcase.c
 *
 *  \brief    Source file containing the PCIe IP related configuration
 *            functions. These functions will be called by example
 *            applications.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Test-case header files */
#include<stdint.h>
#include<string.h>
#include <ti/csl/csl_rti.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <st_rti.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API return the status of the last system Reset.
 *
 * \param   none.
 *
 * \retval  status          Last device reset status.
 *                          values given by enum #deviceLastResetStaus_t
 */
deviceLastResetStaus_t DeviceGetLastResetStatus(void);

/**
 * \brief   This API to select clock source for RTI module.
 *
 * \param   rtiModule       RTI module instance
 *
 * \param   rtiClockSource  RTI module clock source
 *                          Values given by enum #rtiClockSource_t
 *
 * \retval  none.
 */
void RTISetClockSource(uint32_t rtiModule, uint32_t rtiClockSource);

/**
 * \brief   This API to select suspend lines for RTI module.
 *
 * \param   rtiModule       RTI module instance
 *
 * \param   deviceCore      Device core to which suspend lines for given RTI
 *                          module needs to be tied off.
 *                          Values given by enum #rtiSuspendLineCore_t.
 *
 * * \retval  none.
 */
void RTISetSuspendLine(uint32_t rtiModule,
                            rtiSuspendLineCore_t deviceCore);

#ifdef __TI_ARM_V7M4__
/**
 * \brief   AMMU config - needed for AVVREGRESSION.
 *
 * \param   None.
 *
 * \return  None
 */
void AMMU_config(void);
#endif
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
deviceLastResetStaus_t DeviceGetLastResetStatus(void)
{
    deviceLastResetStaus_t status;
	if((HW_RD_REG32(SOC_DEVICE_PRM_BASE + SOC_DEVICE_PRM_BASE_PRM_RSTST)
        & SOC_DEVICE_PRM_BASE_PRM_RSTST_SECURE_WDT_RST_MASK) ==
        		SOC_DEVICE_PRM_BASE_PRM_RSTST_SECURE_WDT_RST_MASK)
	{
		status = DEVICE_LAST_RESET_STATUS_WDT_GENERATED;
	}
	else
	{
		status = DEVICE_LAST_RESET_STATUS_NOT_WDT_GENERATED;
	}
    return status;
}

void RTISetClockSource(uint32_t rtiModule, uint32_t rtiClockSource)
{
	/*		Unlock MMR Lock1		*/
	HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_1,
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_1_UNLOCK);
    /*		Select clock source as sysclk1/4		*/
    switch(rtiModule){
        case SOC_RTI1_BASE:
            HW_WR_FIELD32(CONTROL_CORE_SEC_OCPINTF +
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL,
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL_RTI_1_CLKSEL,
                    rtiClockSource);
        break;
        case SOC_RTI2_BASE:
            HW_WR_FIELD32(CONTROL_CORE_SEC_OCPINTF +
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL,
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL_RTI_2_CLKSEL,
                    rtiClockSource);
        break;
        case SOC_RTI3_BASE:
            HW_WR_FIELD32(CONTROL_CORE_SEC_OCPINTF +
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL,
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL_RTI_3_CLKSEL,
                    rtiClockSource);
        break;
        case SOC_RTI4_BASE:
            HW_WR_FIELD32(CONTROL_CORE_SEC_OCPINTF +
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL,
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL_RTI_4_CLKSEL,
                    rtiClockSource);
        break;
        case SOC_RTI5_BASE:
            HW_WR_FIELD32(CONTROL_CORE_SEC_OCPINTF +
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL,
                    CONTROL_CORE_SEC_OCPINTF_PRCM_CLKSEL_CONTROL_RTI_5_CLKSEL,
                    rtiClockSource);
        break;
        default:
        {
        }
    }
	/*		Lock MMR Lock1		*/
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_1,
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_1_LOCK);
}

void RTISetSuspendLine(uint32_t rtiModule,
                            rtiSuspendLineCore_t deviceCore)
{
    switch(rtiModule){
        case SOC_RTI1_BASE:
            HW_WR_REG32(SOC_I_DRM_BASE + SOC_I_DRM_BASE_SUSPEND_CTRL20,
                        deviceCore);
        break;
        case SOC_RTI2_BASE:
            HW_WR_REG32(SOC_I_DRM_BASE + SOC_I_DRM_BASE_SUSPEND_CTRL21,
                        deviceCore);
        break;
        case SOC_RTI3_BASE:
            HW_WR_REG32(SOC_I_DRM_BASE + SOC_I_DRM_BASE_SUSPEND_CTRL22,
                        deviceCore);
        break;
        case SOC_RTI4_BASE:
            HW_WR_REG32(SOC_I_DRM_BASE + SOC_I_DRM_BASE_SUSPEND_CTRL23,
                        deviceCore);
        break;
        case SOC_RTI5_BASE:
            HW_WR_REG32(SOC_I_DRM_BASE + SOC_I_DRM_BASE_SUSPEND_CTRL24,
                        deviceCore);
        break;
        default:
        {
        }
    }
}

#ifdef __TI_ARM_V7M4__
void AMMU_config(void)
{
    uint32_t regAddr;

    /*---------------- Setup the UNICACHE MMU -----------------*/
    /*Large Page Translations */
    /* Clear Policy Register- to avoid any conflict */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x840;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;

    /* Logical Address */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x800;
    HW_WR_REG32(regAddr,         0x40000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x80000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0xA0000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x60000000); regAddr += 0x4;

    /* Physical Address */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x820;
    HW_WR_REG32(regAddr,         0x40000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x80000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x80000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x40000000); regAddr += 0x4;

    /* Policy Register */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x840;
    HW_WR_REG32(regAddr,         0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x000B0007); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000007); regAddr += 0x4;

    /*Medium Page*/
    /* Clear Policy Register- to avoid any conflict */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x8E0;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;

    /* Medium page Physical Address */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x860;
    HW_WR_REG32(regAddr,         0x00300000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00340000); regAddr += 0x4;

    /* Medium page Virtual Address */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x8A0;
    HW_WR_REG32(regAddr,         0x40300000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x40340000); regAddr += 0x4;

    /* Policy Register */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x8E0;
    HW_WR_REG32(regAddr,         0x00030003); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00030003); regAddr += 0x4;

     /*Small Page*/
    /* Clear Policy Register- to avoid any conflict */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0xA20;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0); regAddr += 0x4;

    /* Small page Physical Address */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x920;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x40000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00004000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00008000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0000C000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;

    /* Small page Virtual Address */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x9A0;
    HW_WR_REG32(regAddr,         0x55020000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x55080000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x55024000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x55028000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x5502C000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;

    /* Policy Register */
    regAddr = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0xA20;
    HW_WR_REG32(regAddr,         0x0001000B); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0000000B); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x0001000B); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
}
#endif
