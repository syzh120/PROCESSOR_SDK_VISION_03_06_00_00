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
 *  \file     sbl_tda2xx_priv.h
 *
 *  \brief    This file contains the platform specific private layer of
 *            Secondary Bootloader(SBL) for TDA2xx SOC family.
 *            This also contains some related macros.
 */

#ifndef SBL_TDA2XX_PRIV_H_
#define SBL_TDA2XX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>

#ifdef __cplusplus
extern "C" {
#endif

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
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function does the PAD configuration for TI EVM.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLConfigTIEVMPad(void);

/**
 * \brief   This function does the PAD configuration for TI Monster Cam EVM.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLConfigTIMCEVMPad(void);

/**
 * \brief   This function does the PAD configuration for RVP
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLConfigRVPPad(void);

/**
 * \brief   This function copies the App Image from corresponding source
 *          depending on Boot Mode.
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \return  status       Whether Image is copied correctly
 *                       SUCCESS : Success
 *                       FAIL : Failure
 */
int32_t SBLLoadAppImage(sbllibAppImageParseParams_t *imageParams);

/**
 * \brief   This function returns the OPP ID for which the SBL has been
 *          compiled.
 *
 * \param   None.
 *
 * \return  oppId       The OPP ID for which the SBL has been compiled is
 *                      returned.
 */
uint32_t SBLGetOppId(void);

/**
 * \brief   This function returns the Boot Mode for which the SBL has been
 *          compiled.
 *
 * \param   None.
 *
 * \return  bootMode    The Boot Mode for which the SBL has been compiled is
 *                      returned.
 */
uint32_t SBLGetBootMode(void);
#ifdef __cplusplus
}

#endif

#endif

