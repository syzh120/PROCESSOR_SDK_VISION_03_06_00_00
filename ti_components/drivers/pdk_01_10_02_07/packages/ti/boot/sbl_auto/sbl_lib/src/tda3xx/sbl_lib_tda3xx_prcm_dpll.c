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
 *  \file     sbl_lib_tda3xx_prcm_dpll.c
 *
 *  \brief    This file contains the structure for all DPLL Divider elements for
 *            TDA3xx platform. This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>

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

/* Arrays given below are defined for 20 MHz */
static pmhalPrcmPllPostDivValue_t dpllCore15X15PostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  4 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 8 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 4 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 44},  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 4 },  /* Div_h14_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H21, 11},  /* Div_h21_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H22, 5 },  /* Div_h22_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H23, 10},  /* Div_h23_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllCore12X12PostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  6 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 8 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 4 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 44},  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 6 },  /* Div_h14_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H21, 11},  /* Div_h21_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H22, 5 },  /* Div_h22_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H23, 10},  /* Div_h23_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllPerPostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  8},  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  3},  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 6},  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 8},  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 8},  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 4}   /* Div_h14_clkcfg */
};

#if (SBLLIB_DDR_TYPE_DDR2 == SBL_LIB_CONFIG_DDR_TYPE)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED)
static pmhalPrcmPllPostDivValue_t dpllDdr2PostDiv400MHzCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 4 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 31},  /* Div_h12_clkcfg */
};
    #else
static pmhalPrcmPllPostDivValue_t dpllDdr2PostDiv333MHzCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 4 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 31},  /* Div_h12_clkcfg */
};
    #endif
#else
static pmhalPrcmPllPostDivValue_t dpllDdr3PostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 8 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 31},  /* Div_h12_clkcfg */
};
#endif

#if (SBLLIB_DDR_TYPE_LPDDR2 == SBL_LIB_CONFIG_DDR_TYPE_12X12)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED_12X12)
static pmhalPrcmPllPostDivValue_t dpllLpDdr2PostDiv400MHzCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 4 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 31},  /* Div_h12_clkcfg */
};
    #else
static pmhalPrcmPllPostDivValue_t dpllLpDdr2PostDiv333MHzCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 4 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 31},  /* Div_h12_clkcfg */
};
    #endif
#endif

static pmhalPrcmPllPostDivValue_t dpllGmac15X15PostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  4 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  4 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 40},  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 8 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 4 },  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 25}   /* Div_h13_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllGmac12X12PostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  4 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  6 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 40},  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 8 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 6 }  /* Div_h13_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllCore15X15PostDivCfgOppOd_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  4 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 8 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 4 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 44},  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 3 },  /* Div_h14_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H21, 11},  /* Div_h21_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H22, 5 },  /* Div_h22_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H23, 10},  /* Div_h23_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllCore15X15PostDivCfgOppHigh_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  2 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  4 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 8 },  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 4 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 44},  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 3 },  /* Div_h14_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H21, 11},  /* Div_h21_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H22, 5 },  /* Div_h22_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H23, 10},  /* Div_h23_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllGmac15X15PostDivCfgOppOd_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  4 },  /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  3 },  /* Div_m3_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 40},  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 8 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 3 },  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 25}   /* Div_h14_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllGmac15X15PostDivCfgOppHigh_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2,  4 },  /* Div_m2_clkcfg  */
#if (SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ == (1U))
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  2 },  /* Div_m3_clkcfg  */
#else
    {PMHAL_PRCM_DPLL_POST_DIV_M3,  3 },  /* Div_m3_clkcfg  */
#endif
    {PMHAL_PRCM_DPLL_POST_DIV_H11, 40},  /* Div_h11_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H12, 8 },  /* Div_h12_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H13, 3 },  /* Div_h13_clkcfg */
    {PMHAL_PRCM_DPLL_POST_DIV_H14, 25}   /* Div_h13_clkcfg */
};

static pmhalPrcmPllPostDivValue_t dpllEveVidDsp15X15PostDivCfgOppNom_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2, 1},    /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3, 2}     /* Div_m3_clkcfg  */
};

static pmhalPrcmPllPostDivValue_t dpllEveVidDsp15X15PostDivCfgOppOd_20[] =
{
    {PMHAL_PRCM_DPLL_POST_DIV_M2, 2},    /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3, 2}     /* Div_m3_clkcfg  */
};

static pmhalPrcmPllPostDivValue_t dpllEveVidDsp15X15PostDivCfgOppHigh_20[] =
{
#if (SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ == (1U))
    {PMHAL_PRCM_DPLL_POST_DIV_M2, 2},    /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3, 3}     /* Div_m3_clkcfg  */
#else
    {PMHAL_PRCM_DPLL_POST_DIV_M2, 5},    /* Div_m2_clkcfg  */
    {PMHAL_PRCM_DPLL_POST_DIV_M3, 2}     /* Div_m3_clkcfg  */
#endif
};

static pmhalPrcmDpllConfig_t      dpllCore15X15CfgOppNom_20 =
{
    266,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllCore15X15PostDivCfgOppNom_20,
    (sizeof (dpllCore15X15PostDivCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllCore15X15CfgOppOd_20 =
{
    266,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllCore15X15PostDivCfgOppOd_20,
    (sizeof (dpllCore15X15PostDivCfgOppOd_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllCore15X15CfgOppHigh_20 =
{
    266,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllCore15X15PostDivCfgOppHigh_20,
    (sizeof (dpllCore15X15PostDivCfgOppHigh_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllCore12X12CfgOppNom_20 =
{
    266,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllCore12X12PostDivCfgOppNom_20,
    (sizeof (dpllCore12X12PostDivCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllPerCfgOppNom_20 =
{
    192,                                                                        /*
                                                                                 * *Multiplier
                                                                                 **/
    4,                                                                          /*
                                                                                 * *Divider
                                                                                 **/
    0,                                                                          /*
                                                                                 * *DutyCycleCorrector
                                                                                 **/
    dpllPerPostDivCfgOppNom_20,
    (sizeof (dpllPerPostDivCfgOppNom_20) / sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

#if (SBLLIB_DDR_TYPE_DDR2 == SBL_LIB_CONFIG_DDR_TYPE)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED)
static pmhalPrcmDpllConfig_t      dpllDdr2CfgOppNom400MHz_20 =
{
    200,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllDdr2PostDiv400MHzCfgOppNom_20,
    (sizeof (dpllDdr2PostDiv400MHzCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};
    #else
static pmhalPrcmDpllConfig_t      dpllDdr2CfgOppNom333MHz_20 =
{
    166,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllDdr2PostDiv333MHzCfgOppNom_20,
    (sizeof (dpllDdr2PostDiv333MHzCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};
    #endif
#else
static pmhalPrcmDpllConfig_t      dpllDdr3CfgOppNom532MHz_20 =
{
    266,                                                                         /*
                                                                                  * *Multiplier
                                                                                  **/
    4,                                                                           /*
                                                                                  * *Divider
                                                                                  **/
    0,                                                                           /*
                                                                                  * *DutyCycleCorrector
                                                                                  **/
    dpllDdr3PostDivCfgOppNom_20,
    (sizeof (dpllDdr3PostDivCfgOppNom_20) / sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};
#endif

#if (SBLLIB_DDR_TYPE_LPDDR2 == SBL_LIB_CONFIG_DDR_TYPE_12X12)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED_12X12)
static pmhalPrcmDpllConfig_t      dpllLpDdr2CfgOppNom400MHz_20 =
{
    200,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllLpDdr2PostDiv400MHzCfgOppNom_20,
    (sizeof (dpllLpDdr2PostDiv400MHzCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};
    #else
static pmhalPrcmDpllConfig_t      dpllLpDdr2CfgOppNom333MHz_20 =
{
    166,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllLpDdr2PostDiv333MHzCfgOppNom_20,
    (sizeof (dpllLpDdr2PostDiv333MHzCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};
    #endif
#endif

static pmhalPrcmDpllConfig_t      dpllGmac15X15CfgOppNom_20 =
{
    250,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllGmac15X15PostDivCfgOppNom_20,
    (sizeof (dpllGmac15X15PostDivCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllGmac15X15CfgOppOd_20 =
{
    250,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllGmac15X15PostDivCfgOppOd_20,
    (sizeof (dpllGmac15X15PostDivCfgOppOd_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllGmac15X15CfgOppHigh_20 =
{
    250,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllGmac15X15PostDivCfgOppHigh_20,
    (sizeof (dpllGmac15X15PostDivCfgOppHigh_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllGmac12X12CfgOppNom_20 =
{
    250,                                  /* Multiplier */
    4,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllGmac12X12PostDivCfgOppNom_20,
    (sizeof (dpllGmac12X12PostDivCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllEveVidDsp15X15CfgOppNom_20 =
{
    238,                                  /* Multiplier */
    7,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllEveVidDsp15X15PostDivCfgOppNom_20,
    (sizeof (dpllEveVidDsp15X15PostDivCfgOppNom_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllEveVidDsp15X15CfgOppOd_20 =
{
    238,                                  /* Multiplier */
    7,                                    /* Divider */
    0,                                    /* DutyCycleCorrector */
    dpllEveVidDsp15X15PostDivCfgOppOd_20,
    (sizeof (dpllEveVidDsp15X15PostDivCfgOppOd_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t      dpllEveVidDsp15X15CfgOppHigh_20 =
{
#if (SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ == (1U))
    225,                                   /* Multiplier */
    4,                                     /* Divider */
#else
    149,                                   /* Multiplier */
    3,                                     /* Divider */
#endif
    0,                                     /* DutyCycleCorrector */
    dpllEveVidDsp15X15PostDivCfgOppHigh_20,
    (sizeof (dpllEveVidDsp15X15PostDivCfgOppHigh_20) /
     sizeof (pmhalPrcmPllPostDivValue_t)),
    0
};

static pmhalPrcmDpllConfig_t     *pDpllCore15X15Cfg_20[] =
{
    &dpllCore15X15CfgOppNom_20,
    &dpllCore15X15CfgOppNom_20,
    &dpllCore15X15CfgOppOd_20,
    &dpllCore15X15CfgOppHigh_20
};

static pmhalPrcmDpllConfig_t     *pDpllCore12X12Cfg_20[] =
{
    &dpllCore12X12CfgOppNom_20,
    &dpllCore12X12CfgOppNom_20,
    &dpllCore12X12CfgOppNom_20,
    &dpllCore12X12CfgOppNom_20
};

#if (SBLLIB_DDR_TYPE_DDR2 == SBL_LIB_CONFIG_DDR_TYPE)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED)
static pmhalPrcmDpllConfig_t     *pDpllDdr2Cfg400MHz_20[] =
{
    &dpllDdr2CfgOppNom400MHz_20,
    &dpllDdr2CfgOppNom400MHz_20,
    &dpllDdr2CfgOppNom400MHz_20,
    &dpllDdr2CfgOppNom400MHz_20
};
    #else
static pmhalPrcmDpllConfig_t     *pDpllDdr2Cfg333MHz_20[] =
{
    &dpllDdr2CfgOppNom333MHz_20,
    &dpllDdr2CfgOppNom333MHz_20,
    &dpllDdr2CfgOppNom333MHz_20,
    &dpllDdr2CfgOppNom333MHz_20
};
    #endif
#else
static pmhalPrcmDpllConfig_t     *pDpllDdr3Cfg532MHz_20[] =
{
    &dpllDdr3CfgOppNom532MHz_20,
    &dpllDdr3CfgOppNom532MHz_20,
    &dpllDdr3CfgOppNom532MHz_20,
    &dpllDdr3CfgOppNom532MHz_20
};
#endif

#if (SBLLIB_DDR_TYPE_LPDDR2 == SBL_LIB_CONFIG_DDR_TYPE_12X12)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED_12X12)
static pmhalPrcmDpllConfig_t     *pDpllLpDdr2Cfg400MHz_20[] =
{
    &dpllLpDdr2CfgOppNom400MHz_20,
    &dpllLpDdr2CfgOppNom400MHz_20,
    &dpllLpDdr2CfgOppNom400MHz_20,
    &dpllLpDdr2CfgOppNom400MHz_20
};
    #else
static pmhalPrcmDpllConfig_t     *pDpllLpDdr2Cfg333MHz_20[] =
{
    &dpllLpDdr2CfgOppNom333MHz_20,
    &dpllLpDdr2CfgOppNom333MHz_20,
    &dpllLpDdr2CfgOppNom333MHz_20,
    &dpllLpDdr2CfgOppNom333MHz_20
};
    #endif
#endif

static pmhalPrcmDpllConfig_t     *pDpllGmac15X15Cfg_20[] =
{
    &dpllGmac15X15CfgOppNom_20,
    &dpllGmac15X15CfgOppNom_20,
    &dpllGmac15X15CfgOppOd_20,
    &dpllGmac15X15CfgOppHigh_20
};

static pmhalPrcmDpllConfig_t     *pDpllGmac12X12Cfg_20[] =
{
    &dpllGmac12X12CfgOppNom_20,
    &dpllGmac12X12CfgOppNom_20,
    &dpllGmac12X12CfgOppNom_20,
    &dpllGmac12X12CfgOppNom_20
};

static pmhalPrcmDpllConfig_t     *pDpllPerCfg_20[] =
{
    &dpllPerCfgOppNom_20,
    &dpllPerCfgOppNom_20,
    &dpllPerCfgOppNom_20,
    &dpllPerCfgOppNom_20
};

static pmhalPrcmDpllConfig_t     *pDpllEveVidDsp15x15Cfg_20[] =
{
    &dpllEveVidDsp15X15CfgOppNom_20,
    &dpllEveVidDsp15X15CfgOppNom_20,
    &dpllEveVidDsp15X15CfgOppOd_20,
    &dpllEveVidDsp15X15CfgOppHigh_20
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SBLLibGetDpllStructure(uint32_t                dpllId,
                               uint32_t                sysClk,
                               uint32_t                opp,
                               pmhalPrcmDpllConfig_t **dpllCfg)
{
    uint32_t siliconPackageType;
    int32_t  retVal = STW_SOK;

    if (PMHAL_PRCM_SYSCLK_20_MHZ == sysClk)
    {
        siliconPackageType = SBLLibGetSiliconPackageType();
        switch (dpllId)
        {
            case PMHAL_PRCM_DPLL_CORE:
                if (SBLLIB_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
                {
                    *dpllCfg = pDpllCore12X12Cfg_20[opp];
                }
                else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 ==
                      * siliconPackageType */
                {
                    *dpllCfg = pDpllCore15X15Cfg_20[opp];
                }
                break;
            case PMHAL_PRCM_DPLL_DDR:
                if (SBLLIB_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
                {
#if (SBLLIB_DDR_TYPE_LPDDR2 == SBL_LIB_CONFIG_DDR_TYPE_12X12)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED_12X12)
                    *dpllCfg = pDpllLpDdr2Cfg400MHz_20[opp];
    #else
                    /* Default to LPDDR2 333MHz */
                    *dpllCfg = pDpllLpDdr2Cfg333MHz_20[opp];
    #endif
#else
                    /* Wrong DDR type */
                    retVal = STW_EFAIL;
#endif
                }
                else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 ==
                      * siliconPackageType */
                {
#if (SBLLIB_DDR_TYPE_DDR2 == SBL_LIB_CONFIG_DDR_TYPE)
    #if (SBLLIB_DDR_SPEED_400MHZ == SBL_LIB_CONFIG_DDR_SPEED)
                    *dpllCfg = pDpllDdr2Cfg400MHz_20[opp];
    #else
                    /* Default to DDR2 333MHz */
                    *dpllCfg = pDpllDdr2Cfg333MHz_20[opp];
    #endif
#else
                    /* Default to DDR3 532MHz */
                    *dpllCfg = pDpllDdr3Cfg532MHz_20[opp];
#endif
                }
                break;
            case PMHAL_PRCM_DPLL_DSP_GMAC:
                if (SBLLIB_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
                {
                    *dpllCfg = pDpllGmac12X12Cfg_20[opp];
                }
                else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 ==
                      * siliconPackageType */
                {
                    *dpllCfg = pDpllGmac15X15Cfg_20[opp];
                }
                break;
            case PMHAL_PRCM_DPLL_EVE_VID_DSP:
                if (SBLLIB_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
                {
                    /* EVE VID DSP DPLL configuration not currently
                     * supported for 12x12 */
                    retVal = STW_EFAIL;
                }
                else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 ==
                      * siliconPackageType */
                {
                    *dpllCfg = pDpllEveVidDsp15x15Cfg_20[opp];
                }
                break;
            case PMHAL_PRCM_DPLL_PER:
                *dpllCfg = pDpllPerCfg_20[opp];
                break;
            default:
                /* To remove MISRA C error */
                break;
        }
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

#ifdef __cplusplus
}
#endif

