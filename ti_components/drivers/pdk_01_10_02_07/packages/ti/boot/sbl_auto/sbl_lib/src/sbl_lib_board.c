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
 *  \file     sbl_lib_board.c
 *
 *  \brief    This file contains the SBL Library APIs related to TDAxxx
 *            silicon and the respective TI TDAxxx EVM.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SBLLibGetSiliconRev(void)
{
    return PlatformGetSiliconRev();
}

uint32_t SBLLibGetSiliconPackageType(void)
{
    uint32_t packageType, regVal;

#if defined (SOC_TDA3XX)
    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                           CTRL_CORE_BOOTSTRAP,
                           CTRL_CORE_BOOTSTRAP_SYSBOOT_7);

    if (0x1U == regVal)
    {
        packageType = SBLLIB_SILICON_PACKAGE_TYPE_12X12;
    }
    else
    {
        packageType = SBLLIB_SILICON_PACKAGE_TYPE_15X15;
    }

#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                           CTRL_WKUP_STD_FUSE_DIE_ID_2,
                           CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE);

    if (0x1U == regVal)
    {
        packageType = SBLLIB_SILICON_PACKAGE_TYPE_17X17;
    }
    else if (0x2U == regVal)
    {
        packageType = SBLLIB_SILICON_PACKAGE_TYPE_23X23;
    }
#if defined (SOC_TDA2PX)
    else if (0x3U == regVal)
    {
        packageType = SBLLIB_SILICON_PACKAGE_TYPE_23X23_HPP;
    }
#endif
    else
    {
        packageType = SBLLIB_SILICON_PACKAGE_TYPE_UNKNOWN;
    }
#endif

    return packageType;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
void SBLLibUnlockControlIODSS(void)
{
    PlatformUnlockControlIODSS();
}

void SBLLibI2C3SetPinMux(void)
{
    PlatformI2C3SetPinMux();
}

void SBLLibI2C4SetPinMux(void)
{
    I2C4_Pin_Mux();
}

void SBLLibI2C5SetPinMux(void)
{
    PlatformI2C5SetPinMux();
}

void SBLLibTDA2xxMCSetPinMux(void)
{
    PlatformTDA2xxMCSetPinMux();
}

uint32_t SBLLibGetFtRev(void)
{
    return PlatformGetFtRev();
}

#endif

void SBLLibConfigureUARTPinMux(UART_INST_t uartInstance)
{
    PlatformUARTSetPinMux(uartInstance);
}

void SBLLibMMCSDSetPinMux(MMC_INST_t mmcInstance)
{
    PlatformMMCSDSetPinMux(mmcInstance);
}

void SBLLibRGMIISetPinMux(void)
{
    PlatformRGMIISetPinMux();
}

void SBLLibGPMCSetPinMux(void)
{
    PlatformGPMCSetPinMux();
}

void SBLLibQSPISetPinMux(void)
{
    PlatformQSPISetPinMux();
}

void SBLLibLockControlModuleMMR(void)
{
    PlatformLockMMR();
}

void SBLLibUnlockControlModuleMMR(void)
{
    PlatformUnlockMMR();
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
