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
 *  \file     sbl_tda3xx_priv.c
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
#include <sbl_tda3xx_priv.h>
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

void SBLConfigTIEVMPad(void)
{
#if defined (BOOTMODE_QSPI)
    SBLLibQSPISetPinMux();
#elif defined (BOOTMODE_NOR)
    SBLLibGPMCSetPinMux();
#elif defined (BOOTMODE_QSPI_SD)
    SBLLibMMCSDSetPinMux(MMC4_INST);
#endif
    /* MMC and RGMII require same pins to be configured. Thus RGMII pin mux
     * configuration is done after copying App Image in QSPI_SD boot-mode
     */
#if !defined (BOOTMODE_QSPI_SD)
    SBLLibRGMIISetPinMux();
#endif
}

int32_t SBLLoadAppImage(sbllibAppImageParseParams_t *imageParams)
{
    int32_t retVal = STW_SOK;
    #if defined (BOOTMODE_QSPI)
    retVal = SBLUtilsQspiBootRprc(imageParams);
    #elif defined (BOOTMODE_NOR)
    retVal = SBLUtilsNorBootRprc(imageParams);
    #elif defined (BOOTMODE_QSPI_SD)
    retVal = SBLUtilsQspiSDBootRprc(imageParams);
    #elif defined (BOOTMODE_UART)
    /* No need to call Boot function */
    #else
    #error Unsupported Boot Mode!!
    #endif
    return retVal;
}

uint32_t SBLGetOppId(uint32_t packageType)
{
    /* Default value is OPP_NOM */
    uint32_t oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
    if (packageType == SBLLIB_SILICON_PACKAGE_TYPE_15X15)
    {
#if (OPP_MODE == SBL_OPP_HIGH)
    #if (SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ == 0U)
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
    #else
        oppId = SBLLIB_PRCM_DPLL_OPP_HIGH;
    #endif
#elif (OPP_MODE == SBL_OPP_OD)
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
#else
        oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
#endif
    }
    else
    {
        /* 12x12 TDA3xx packageType currently supports only OPP_NOM */
        oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
    }
    return oppId;
}

void SBLPrintOppWarning(uint32_t packageType)
{
    if (packageType == SBLLIB_SILICON_PACKAGE_TYPE_15X15)
    {
#if (OPP_MODE == SBL_OPP_HIGH)
    #if (SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ == 0U)
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_IMP_INFO,
            "\n SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ != 1: Falling back to OPP_OD \n");
    #endif
#endif
    }
}

uint32_t SBLIsTesocEnabled(void)
{
    uint32_t isTesocEnabled = FALSE;

#if (SBL_LIB_CONFIG_ENABLE_TESOC == 1)
    if (SBLLibGetSiliconRev() >= 3U)
    {
        isTesocEnabled = TRUE;
    }
#endif
    return isTesocEnabled;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
