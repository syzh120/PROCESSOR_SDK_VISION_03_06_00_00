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
 *  \file     sbl_utils_tda3xx_ammu_config.h
 *
 *  \brief    This file contains the macros for the AMMU configuration that
 *            is programmed by the SBL.
 */

#ifndef SBL_UTILS_TDA3XX_AMMU_CONFIG_H_
#define SBL_UTILS_TDA3XX_AMMU_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/arch/csl_arch.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * Large Page 0 is mapped by RBL from P.A. 0x08000000 to L.A. 0x08000000
 * SBL maps below large pages
 */
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE1_PHY_ADDR     ((uint32_t) 0x40000000U)
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE1_VIRTUAL_ADDR ((uint32_t) 0x40000000U)
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE1_POLICY       ((uint32_t) 0x00000007U)

#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE2_PHY_ADDR     ((uint32_t) 0x80000000U)
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE2_VIRTUAL_ADDR ((uint32_t) 0x80000000U)
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE2_POLICY       ((uint32_t) 0x000F0007U)

#ifdef TDA3XX_AMMU_CONFIG_MAP_DDR_1GB
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_PHY_ADDR     ((uint32_t) 0xA0000000U)
#else
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_PHY_ADDR     ((uint32_t) 0x80000000U)
#endif

#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_VIRTUAL_ADDR ((uint32_t) 0xA0000000U)
#define SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_POLICY       ((uint32_t) 0x00000007U)

/*
 * Medium Page 0 is mapped by RBL from P.A. 0x40300000 to L.A. 0x00300000
 * SBL maps below medium pages
 */
#define SBL_UTILS_TDA3XX_AMMU_MED_PAGE1_PHY_ADDR     ((uint32_t) 0x55020000U)
#define SBL_UTILS_TDA3XX_AMMU_MED_PAGE1_VIRTUAL_ADDR ((uint32_t) 0x00000000U)
#define SBL_UTILS_TDA3XX_AMMU_MED_PAGE1_POLICY       ((uint32_t) 0x00010009U)

/*
 * Small Page 1 is mapped by Design from P.A. 0x55080000 to L.A. 0x40000000
 * SBL change the policy register of this page and maps below small pages
 */
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE0_PHY_ADDR     ((uint32_t) 0x43300000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE0_VIRTUAL_ADDR ((uint32_t) 0x63300000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE0_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE1_PHY_ADDR     ((uint32_t) 0x55080000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE1_VIRTUAL_ADDR ((uint32_t) 0x40000000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE1_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE2_PHY_ADDR     ((uint32_t) 0x43304000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE2_VIRTUAL_ADDR ((uint32_t) 0x63304000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE2_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE3_PHY_ADDR     ((uint32_t) 0x42081000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE3_VIRTUAL_ADDR ((uint32_t) 0x62081000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE3_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE4_PHY_ADDR     ((uint32_t) 0x4208B000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE4_VIRTUAL_ADDR ((uint32_t) 0x6208B000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE4_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE5_PHY_ADDR     ((uint32_t) 0x4208C000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE5_VIRTUAL_ADDR ((uint32_t) 0x6208C000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE5_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE6_PHY_ADDR     ((uint32_t) 0x4883A000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE6_VIRTUAL_ADDR ((uint32_t) 0x6883A000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE6_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE7_PHY_ADDR     ((uint32_t) 0x420A0000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE7_VIRTUAL_ADDR ((uint32_t) 0x620A0000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE7_POLICY       ((uint32_t) 0x0000000BU)

#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE8_PHY_ADDR     ((uint32_t) 0x42086000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE8_VIRTUAL_ADDR ((uint32_t) 0x62086000U)
#define SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE8_POLICY       ((uint32_t) 0x0000000BU)

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

/* None */

#ifdef __cplusplus
}

#endif

#endif

