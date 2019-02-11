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
 *  \file     sbl_tda2xx_priv.c
 *
 *  \brief    This file contains the private API layer specific to the SBL
 *            application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <sbl_tda2xx_priv.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** OPP Configuration*/
#define SBL_OPP_LOW                   (0)
#define SBL_OPP_NOM                   (1)
#define SBL_OPP_OD                    (2)
#define SBL_OPP_HIGH                  (3)
#define SBL_OPP_PLUS                  (4)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if defined (SOC_TDA2XX)
/**
 * \brief    This API tells if the silicon supports Multiple OPPs.
 *
 * \param    None.
 *
 * \return   TRUE:  Silicon supports multiple OPPs.
 *           FALSE: Silicon does not support Multiple OPPs.
 *
 **/
static uint32_t SblIsMultiOppSupported(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLConfigTIEVMPad(void)
{
    SBLLibMMCSDSetPinMux(MMC1_INST);

#if defined (BOOTMODE_QSPI)
    SBLLibQSPISetPinMux();
#elif defined (BOOTMODE_NOR)
    SBLLibGPMCSetPinMux();
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    SBLLibRGMIISetPinMux();
#endif
}

void SBLConfigTIMCEVMPad(void)
{
    SBLLibI2C3SetPinMux();
    SBLLibI2C4SetPinMux();
    SBLLibI2C5SetPinMux();

    SBLLibMMCSDSetPinMux(MMC1_INST);
#if defined (BOOTMODE_QSPI)
    SBLLibQSPISetPinMux();
#elif defined (BOOTMODE_NOR)
    SBLLibGPMCSetPinMux();
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    SBLLibRGMIISetPinMux();
#endif

    /* Monster Cam board specific pad configuration */
    SBLLibTDA2xxMCSetPinMux();
}

void SBLConfigRVPPad(void)
{
    SBLLibI2C3SetPinMux();
    SBLLibI2C4SetPinMux();
    SBLLibI2C5SetPinMux();

    SBLLibMMCSDSetPinMux(MMC1_INST);
#if defined (BOOTMODE_QSPI)
    SBLLibQSPISetPinMux();
#elif defined (BOOTMODE_NOR)
    SBLLibGPMCSetPinMux();
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    SBLLibRGMIISetPinMux();
#endif

    /* Monster Cam board specific pad configuration */
    SBLLibTDA2xxMCSetPinMux();
}

int32_t SBLLoadAppImage(sbllibAppImageParseParams_t *imageParams)
{
    int32_t retVal = STW_SOK;
    #if defined (BOOTMODE_QSPI)
    retVal = SBLUtilsQspiBootRprc(imageParams);
    #elif defined (BOOTMODE_NOR)
    retVal = SBLUtilsNorBootRprc(imageParams);
    #elif defined (BOOTMODE_SD)
    retVal = SBLUtilsSDBootRprc(imageParams);
    #elif defined (BOOTMODE_UART)  && (defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA2XX))
    ;
    #else
    #error Unsupported Boot Mode!!
    #endif
    return retVal;
}

uint32_t SBLGetOppId(void)
{
    /* Default value is OPP_NOM */
    uint32_t oppId = SBLLIB_PRCM_DPLL_OPP_NOM;

#if defined (SOC_TDA2XX)
    uint32_t oppVal = FALSE;

    /* Check if Multi-OPP is supported */
    oppVal = SblIsMultiOppSupported();

    if (TRUE == oppVal)
    {
    #if (OPP_MODE == SBL_OPP_HIGH)
        oppId = SBLLIB_PRCM_DPLL_OPP_HIGH;
    #elif (OPP_MODE == SBL_OPP_OD)
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
    #elif (OPP_MODE == SBL_OPP_LOW)
        if (SBLLIB_SILICON_PACKAGE_TYPE_17X17 == SBLLibGetSiliconPackageType())
        {
            oppId = SBLLIB_PRCM_DPLL_OPP_LOW;
        }
    #else
        oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
    #endif
    }

#else

#if (OPP_MODE == SBL_OPP_HIGH)
    oppId = SBLLIB_PRCM_DPLL_OPP_HIGH;
#elif (OPP_MODE == SBL_OPP_OD)
    #if defined (SOC_TDA2EX)
    if (SBLLIB_SILICON_PACKAGE_TYPE_17X17 == SBLLibGetSiliconPackageType())
    {
        /* OPP OD not supported for TDA2ex 17x17 package. */
        oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
    }
    else
    {
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
    }
    #else
    oppId = SBLLIB_PRCM_DPLL_OPP_OD;
    #endif
#elif (OPP_MODE == SBL_OPP_PLUS)
    #if defined (SOC_TDA2PX)
    oppId = SBLLIB_PRCM_DPLL_OPP_PLUS;
    #elif defined (SOC_TDA2EX)
    oppId = SBLLIB_PRCM_DPLL_OPP_PLUS;
    #endif
#else
    oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
#endif

#endif

    return oppId;
}

uint32_t SBLGetBootMode(void)
{
    /* Default return QSPI bootmode. */
    uint32_t bootMode = SBLLIB_BOOT_MODE_QSPI;
#if defined (BOOTMODE_NOR)
    bootMode = SBLLIB_BOOT_MODE_NOR;
#elif defined (BOOTMODE_QSPI)
    bootMode = SBLLIB_BOOT_MODE_QSPI;
#elif defined (BOOTMODE_SD)
    bootMode = SBLLIB_BOOT_MODE_SD;
#endif
    return bootMode;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

#if defined (SOC_TDA2XX)
static uint32_t SblIsMultiOppSupported(void)
{
    uint32_t retVal = FALSE;
    uint32_t siliconRev, ftRev;

    siliconRev = SBLLibGetSiliconRev();

    if (0U != siliconRev)
    {
        retVal = (uint32_t) TRUE;
    }
    else
    {
        ftRev = SBLLibGetFtRev();
        if (ftRev >= 11U)
        {
            retVal = (uint32_t) TRUE;
        }
    }
    return (retVal);
}

#endif

